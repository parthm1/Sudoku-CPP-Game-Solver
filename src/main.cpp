#include "sudoku/board.hpp"
#include "sudoku/game.hpp"
#include "sudoku/puzzles.hpp"
#include "sudoku/solver.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

namespace {
using namespace sudoku;

std::string lowercase(std::string s) {
    const auto first = s.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    const auto last = s.find_last_not_of(" \t\r\n");
    s = s.substr(first, last - first + 1);
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return s;
}

void showHelp() {
    std::cout << "\nSUDOKU - C++ EDITION\n\n"
              << "Commands during a game:\n"
              << "  row col value    e.g. 1 2 9 (rows/columns 1-9)\n"
              << "  hint             reveal the value in an empty cell\n"
              << "  solve            show the solved grid and end this round\n"
              << "  new              start another round\n"
              << "  quit             exit the application\n"
              << "  help             show these commands\n\n"
              << "Command-line options:\n"
              << "  --list           list the six original puzzles\n"
              << "  --puzzle E1      play a specified puzzle (E1/E2/A1/A2/H1/H2)\n"
              << "  --solve E1       solve a built-in puzzle\n"
              << "  --solve-file F   solve a 9-line puzzle from a text file\n"
              << "  --validate       verify every bundled puzzle has one solution\n"
              << "  --help           show this help\n\n"
              << "A dot or zero denotes an empty square.\n";
}

void listPuzzles() {
    std::cout << "Original 2022 Sudoku puzzle collection:\n";
    for (const Puzzle& puzzle : puzzles()) {
        std::cout << "  " << puzzle.id << "  " << difficultyName(puzzle.difficulty)
                  << "  " << puzzle.startingBoard.emptyCount() << " empty cells\n";
    }
}

int showSolution(const Board& board) {
    if (!Solver::isValid(board)) {
        std::cerr << "Invalid puzzle: clues conflict with Sudoku rules.\n";
        return 1;
    }
    const auto solved = Solver::solve(board);
    if (!solved) {
        std::cerr << "No solution exists for this puzzle.\n";
        return 1;
    }
    std::cout << "Original board:\n" << formatBoard(board)
              << "\nSolved board:\n" << formatBoard(*solved)
              << "Solutions found (capped at 2): " << Solver::countSolutions(board, 2) << "\n";
    return 0;
}

const Puzzle* randomPuzzle(Difficulty mode, std::mt19937& engine) {
    std::vector<const Puzzle*> choices;
    for (const auto& p : puzzles()) if (p.difficulty == mode) choices.push_back(&p);
    std::uniform_int_distribution<std::size_t> choose(0, choices.size() - 1);
    return choices[choose(engine)];
}

bool chooseDifficulty(Difficulty& result) {
    std::string input;
    while (true) {
        std::cout << "\nChoose difficulty: [E]asy, [A]mateur, [H]ard, or [Q]uit: ";
        if (!std::getline(std::cin, input)) return false;
        input = lowercase(input);
        if (input == "e" || input == "easy") { result = Difficulty::Easy; return true; }
        if (input == "a" || input == "amateur" || input == "medium") {
            result = Difficulty::Amateur; return true;
        }
        if (input == "h" || input == "hard") { result = Difficulty::Hard; return true; }
        if (input == "q" || input == "quit" || input == "exit") return false;
        std::cout << "Please enter E, A, H or Q.\n";
    }
}

enum class RoundAction { Another, New, Quit };

RoundAction runRound(Game& game) {
    std::cout << "\n=== " << difficultyName(game.puzzle().difficulty) << " puzzle "
              << game.puzzle().id << " ===\n"
              << "Each row, column and 3x3 box must contain 1-9 exactly once.\n"
              << "Enter 'help' to see all commands.\n";
    while (game.status() == GameStatus::Playing) {
        std::cout << "\n" << formatBoard(game.board())
                  << "Filled: " << game.filledCount() << "/" << game.puzzle().startingBoard.emptyCount()
                  << " | Mistakes left: " << game.mistakesRemaining()
                  << " | Hints left: " << game.hintsRemaining() << "\n"
                  << "Move or command: ";
        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cout << "\nInput ended. Goodbye!\n";
            return RoundAction::Quit;
        }
        const std::string command = lowercase(line);
        if (command == "quit" || command == "q" || command == "exit") {
            std::cout << "Goodbye!\n";
            return RoundAction::Quit;
        }
        if (command == "new" || command == "restart") return RoundAction::New;
        if (command == "help" || command == "?") { showHelp(); continue; }
        if (command == "solve") {
            game.reveal();
            std::cout << "\nSolution revealed (not counted as a win):\n"
                      << formatBoard(game.solution());
            break;
        }
        if (command == "hint") {
            const HintResult hint = game.hint();
            switch (hint.status) {
                case HintStatus::Applied:
                    std::cout << "Hint: row " << hint.row + 1 << ", column " << hint.col + 1
                              << " is " << hint.value << ".\n";
                    break;
                case HintStatus::NoneRemaining: std::cout << "No hints remaining.\n"; break;
                case HintStatus::GameEnded: std::cout << "This round has ended.\n"; break;
                case HintStatus::NoEmptyCells: std::cout << "No empty cells remain.\n"; break;
            }
            continue;
        }
        std::istringstream parts(command);
        std::string first;
        if (!(parts >> first)) { std::cout << "Enter a move or type help.\n"; continue; }
        if (first == "place" || first == "move") {
            // Strip the command and parse the same three-number format.
            std::string rest;
            std::getline(parts, rest);
            parts.clear();
            parts.str(rest);
        } else {
            parts.clear();
            parts.str(command);
        }
        int row, col, value;
        std::string extra;
        if (!(parts >> row >> col >> value) || (parts >> extra)) {
            std::cout << "Use: row col value (for example: 1 2 9).\n";
            continue;
        }
        if (row < 1 || row > 9 || col < 1 || col > 9 || value < 1 || value > 9) {
            std::cout << "Rows, columns and values must be between 1 and 9.\n";
            continue;
        }
        switch (game.place(row - 1, col - 1, value)) {
            case MoveStatus::Correct: std::cout << "Correct!\n"; break;
            case MoveStatus::Incorrect: std::cout << "Incorrect. One mistake used.\n"; break;
            case MoveStatus::InvalidInput:
                std::cout << "Rows, columns and values must be between 1 and 9.\n"; break;
            case MoveStatus::FixedCell: std::cout << "That is an original clue; it cannot change.\n"; break;
            case MoveStatus::FilledCell: std::cout << "That square is already filled.\n"; break;
            case MoveStatus::GameEnded: std::cout << "This round has ended.\n"; break;
        }
    }
    if (game.status() == GameStatus::Won) {
        std::cout << "\n*** Congratulations! You solved the complete puzzle! ***\n"
                  << formatBoard(game.board());
    } else if (game.status() == GameStatus::Lost) {
        std::cout << "\nNo mistakes remaining. Game over.\n"
                  << "Correct solution:\n" << formatBoard(game.solution());
    }
    return RoundAction::Another;
}

bool playAgain() {
    while (true) {
        std::cout << "\nPlay another puzzle? [y/n]: ";
        std::string reply;
        if (!std::getline(std::cin, reply)) return false;
        reply = lowercase(reply);
        if (reply == "y" || reply == "yes") return true;
        if (reply == "n" || reply == "no" || reply == "q") return false;
        std::cout << "Please enter y or n.\n";
    }
}

int interactive(const Puzzle* firstPuzzle = nullptr) {
    std::mt19937 engine(std::random_device{}());
    std::cout << "\nSUDOKU | C++ Game & Solver\n";
    const Puzzle* selected = firstPuzzle;
    while (true) {
        if (!selected) {
            Difficulty chosen = Difficulty::Easy;
            if (!chooseDifficulty(chosen)) break;
            selected = randomPuzzle(chosen, engine);
        }
        Game game(*selected);
        selected = nullptr;
        const RoundAction outcome = runRound(game);
        if (outcome == RoundAction::Quit) return 0;
        if (outcome == RoundAction::New) continue;
        if (!playAgain()) break;
    }
    std::cout << "Thanks for playing!\n";
    return 0;
}

}  // namespace

int main(int argc, char* argv[]) {
    using namespace sudoku;
    try {
        if (argc == 1) return interactive();
        const std::string action = argv[1];
        if (action == "--help" && argc == 2) { showHelp(); return 0; }
        if (action == "--list" && argc == 2) { listPuzzles(); return 0; }
        if (action == "--validate" && argc == 2) {
            bool good = true;
            for (const Puzzle& puzzle : puzzles()) {
                const int count = Solver::countSolutions(puzzle.startingBoard, 2);
                std::cout << puzzle.id << ": " << (count == 1 ? "unique solution" : "INVALID") << '\n';
                if (count != 1) good = false;
            }
            return good ? 0 : 1;
        }
        if (action == "--solve-file" && argc == 3) {
            std::ifstream source(argv[2]);
            if (!source) { std::cerr << "Cannot open puzzle file: " << argv[2] << '\n'; return 1; }
            return showSolution(readBoard(source));
        }
        if ((action == "--puzzle" || action == "--solve") && argc == 3) {
            const Puzzle* puzzle = findPuzzle(argv[2]);
            if (!puzzle) { std::cerr << "Unknown puzzle ID. Try --list.\n"; return 2; }
            if (action == "--solve") return showSolution(puzzle->startingBoard);
            return interactive(puzzle);
        }
        std::cerr << "Unknown arguments. Try --help.\n";
        return 2;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
