#include "sudoku/board.hpp"
#include "sudoku/solver.hpp"
#include "sudoku/puzzles.hpp"
#include "sudoku/game.hpp"
#include "expected_solutions.hpp"

#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace sudoku;

namespace {
void check(bool condition, const std::string& message) {
    if (!condition) throw std::runtime_error(message);
}

template <typename Callable>
void expectThrows(Callable function) {
    bool thrown = false;
    try { function(); } catch (const std::invalid_argument&) { thrown = true; }
    check(thrown, "Expected invalid_argument");
}

const Puzzle& fixture() {
    const Puzzle* p = findPuzzle("E1");
    if (!p) throw std::runtime_error("E1 unavailable");
    return *p;
}

Board solvedFixture() {
    auto solved = Solver::solve(fixture().startingBoard);
    check(solved.has_value(), "E1 should solve");
    return *solved;
}

Puzzle oneBlank() {
    Board board = solvedFixture();
    board.at(0, 0) = 0;
    return {"TEST", Difficulty::Easy, board};
}

void testOriginalPuzzles() {
    check(puzzles().size() == 6, "Exactly six original boards expected");
    for (const auto& expected : sudoku_test::originalAnswers()) {
        const Puzzle* puzzle = findPuzzle(expected.id);
        check(puzzle != nullptr, "Puzzle absent");
        check(Solver::isValid(puzzle->startingBoard), "Initial puzzle is invalid");
        check(Solver::countSolutions(puzzle->startingBoard) == 1, "Puzzle must have exactly one solution");
        auto solution = Solver::solve(puzzle->startingBoard);
        check(solution.has_value(), "Puzzle failed to solve");
        check(*solution == parseBoard(expected.rows), "Solution differs from the archived 2022 answer key");
    }
}

void testDifficultyCounts() {
    check(fixture().startingBoard.emptyCount() == 49, "Original E1 blanks");
    check(findPuzzle("E2")->startingBoard.emptyCount() == 42, "Original E2 blanks");
    check(findPuzzle("A1")->startingBoard.emptyCount() == 53, "Original A1 blanks");
    check(findPuzzle("A2")->startingBoard.emptyCount() == 53, "Original A2 blanks");
    check(findPuzzle("H1")->startingBoard.emptyCount() == 55, "Original H1 blanks");
    check(findPuzzle("H2")->startingBoard.emptyCount() == 55, "Original H2 blanks");
}

void testDifficultyLimits() {
    auto e = limitsFor(Difficulty::Easy), a = limitsFor(Difficulty::Amateur), h = limitsFor(Difficulty::Hard);
    check(e.mistakes == 5 && e.hints == 3, "Easy limits");
    check(a.mistakes == 4 && a.hints == 2, "Amateur limits");
    check(h.mistakes == 3 && h.hints == 1, "Hard limits");
}

void testFindPuzzle() {
    check(findPuzzle("a2") == findPuzzle("A2"), "Case-insensitive lookup");
    check(findPuzzle("not-real") == nullptr, "Invalid puzzle lookup");
}

void testParseBoard() {
    const Board b = parseBoard({"000000000",".........","000000000","000000000","000000000","000000000","000000000","000000000","000000009"});
    check(b.emptyCount() == 80 && b.at(8,8) == 9, "Parse blanks and digit");
}

void testInvalidBoardCharacters() {
    expectThrows([] { parseBoard({"00000000x","000000000","000000000","000000000","000000000","000000000","000000000","000000000","000000000"}); });
    expectThrows([] { parseBoard({"00000000","000000000","000000000","000000000","000000000","000000000","000000000","000000000","000000000"}); });
}

void testReadBoard() {
    std::ostringstream source;
    for (int i = 0; i < 9; ++i) source << "000000000\n";
    std::istringstream input(source.str());
    check(readBoard(input).emptyCount() == 81, "Read blank board");
    std::istringstream tooFew("000000000\n");
    expectThrows([&]{ readBoard(tooFew); });
    std::istringstream tooMany(source.str() + "000000000\n");
    expectThrows([&]{ readBoard(tooMany); });
}

void testFormatting() {
    const std::string printed = formatBoard(fixture().startingBoard);
    check(printed.find("1 2 3") != std::string::npos, "Column header");
    check(printed.find(".") != std::string::npos, "Empty cell rendering");
}

void testInvalidClueRow() {
    Board board = fixture().startingBoard;
    board.at(0, 0) = board.at(0, 2);  // duplicate clue on row
    check(!Solver::isValid(board), "Duplicate row detection");
    check(!Solver::solve(board), "Invalid puzzles should not solve");
    check(Solver::countSolutions(board) == 0, "Invalid puzzle must have 0 solutions");
}

void testInvalidClueColumn() {
    Board board = fixture().startingBoard;
    board.at(0, 0) = board.at(1, 0); // duplicate column
    check(!Solver::isValid(board), "Duplicate column detection");
}

void testInvalidClueBox() {
    Board board = fixture().startingBoard;
    board.at(0, 0) = board.at(1, 1); // duplicate in upper-left 3x3 box
    check(!Solver::isValid(board), "Duplicate box detection");
}

void testSolverLeavesCluesUntouched() {
    Board before = fixture().startingBoard;
    auto solution = Solver::solve(before);
    check(solution.has_value() && before == fixture().startingBoard, "Solver must not mutate its argument");
    for (int r = 0; r < 9; ++r)
        for (int c = 0; c < 9; ++c)
            if (before.at(r,c) != 0)
                check(solution->at(r,c) == before.at(r,c), "Solver changed an original clue");
}

void testSolvedBoardUnique() {
    Board b = solvedFixture();
    check(Solver::isValid(b) && b.complete(), "Fully solved board valid");
    check(Solver::countSolutions(b) == 1, "Full board has one solution");
    check(*Solver::solve(b) == b, "Solved board unchanged");
}

void testNoSolutionWhenInvalidValue() {
    Board b = fixture().startingBoard;
    b.at(0, 0) = -1;
    check(!Solver::isValid(b) && !Solver::solve(b), "Out of range digit detection");
}

void testConsistentButUnsolvable() {
    Board b = fixture().startingBoard;
    b.at(0, 1) = 7;  // No immediate conflict, but removes every valid solution.
    check(Solver::isValid(b), "Clues should be locally consistent");
    check(!Solver::solve(b), "Locally valid board may be globally unsolvable");
    check(Solver::countSolutions(b, 2) == 0, "Unsolvable board has 0 solutions");
}

void testAmbiguousPuzzle() {
    Board blank;
    check(Solver::isValid(blank), "Blank board is locally valid");
    check(Solver::countSolutions(blank, 2) == 2, "Blank board has multiple solutions");
    expectThrows([&] { Game game({"AMBIGUOUS", Difficulty::Easy, blank}); });
}

void testBoardBounds() {
    Board board;
    bool thrown = false;
    try { (void)board.at(-1, 9); } catch (const std::out_of_range&) { thrown = true; }
    check(thrown, "Row and col bounds checked independently");
}

void testValidMoveAndVictory() {
    Game game(oneBlank());
    check(game.status() == GameStatus::Playing, "Should start playable");
    const int answer = solvedFixture().at(0, 0);
    check(game.place(0,0,answer) == MoveStatus::Correct, "Correct move accepted");
    check(game.board().complete(), "Board must be full");
    check(game.status() == GameStatus::Won, "Win only after correct full board");
    check(game.filledCount() == 1, "Count from actual board state");
    check(game.place(0,0,answer) == MoveStatus::GameEnded, "No moves after win");
}

void testNotWinUntilLastCell() {
    Board b = solvedFixture();
    b.at(0,0)=0; b.at(0,1)=0;
    Game game({"TWO",Difficulty::Easy,b});
    check(game.place(0,0,solvedFixture().at(0,0)) == MoveStatus::Correct, "Penultimate move");
    check(game.status() == GameStatus::Playing, "Must not win with 1 empty cell");
    check(game.place(0,1,solvedFixture().at(0,1)) == MoveStatus::Correct, "Last move");
    check(game.status() == GameStatus::Won, "Must win after final cell");
}

void testFixedCellAndFilledCell() {
    Game game(fixture());
    check(game.place(0,2,5) == MoveStatus::FixedCell, "Can't overwrite clue");
    const auto solution = game.solution();
    check(game.place(0,0,solution.at(0,0)) == MoveStatus::Correct, "Correct placement");
    check(game.place(0,0,solution.at(0,0)) == MoveStatus::FilledCell, "Can't overwrite filled cell");
    check(game.mistakesRemaining() == 5, "Invalid moves don't use mistake budget");
}

void testInvalidInputsNotPenalized() {
    Game game(fixture());
    check(game.place(-1,0,5) == MoveStatus::InvalidInput, "Negative row rejected");
    check(game.place(0,9,5) == MoveStatus::InvalidInput, "Out of range col rejected");
    check(game.place(0,0,0) == MoveStatus::InvalidInput, "0 value rejected");
    check(game.place(0,0,10) == MoveStatus::InvalidInput, "10 rejected");
    check(game.mistakesRemaining() == 5, "No penalty for malformed move");
}

void testIncorrectMovesDoNotFillCells() {
    Game game(fixture());
    const int correct = game.solution().at(0,0);
    const int wrong = correct == 9 ? 8 : 9;
    check(game.place(0,0,wrong) == MoveStatus::Incorrect, "Wrong answer tracked");
    check(game.board().at(0,0) == 0 && game.filledCount() == 0, "Wrong move leaves board unchanged");
    check(game.mistakesRemaining() == 4, "Wrong move consumes one mistake");
}

void testLossExactlyAtMistakeLimit() {
    const Puzzle& hard = *findPuzzle("H1");
    Game game(hard);
    const int correct = game.solution().at(0,0);
    const int wrong = correct == 9 ? 8 : 9;
    check(game.place(0,0,wrong) == MoveStatus::Incorrect, "1st mistake");
    check(game.status() == GameStatus::Playing, "Still playing at one mistake");
    check(game.place(0,0,wrong) == MoveStatus::Incorrect, "2nd mistake");
    check(game.status() == GameStatus::Playing, "Still playing at two mistakes");
    check(game.place(0,0,wrong) == MoveStatus::Incorrect, "3rd mistake");
    check(game.mistakesRemaining() == 0 && game.status() == GameStatus::Lost, "Lost at zero remaining");
    check(game.place(0,0,correct) == MoveStatus::GameEnded, "Can't play after losing");
}

void testHintsAffectCompletion() {
    Game game(oneBlank());
    auto hint = game.hint();
    check(hint.status == HintStatus::Applied && hint.row == 0 && hint.col == 0, "Hint fills first blank");
    check(hint.value == solvedFixture().at(0,0), "Hint must be correct");
    check(game.filledCount() == 1 && game.board().complete(), "Hint changes board completion");
    check(game.status() == GameStatus::Won, "A finishing hint completes puzzle");
    check(game.hintsRemaining() == 2, "Hint uses one budget unit");
    check(game.hint().status == HintStatus::GameEnded, "Hint forbidden after win");
}

void testHintLimit() {
    Game game(*findPuzzle("H1"));
    check(game.hint().status == HintStatus::Applied, "One hint provided on hard");
    check(game.hint().status == HintStatus::NoneRemaining, "No extra hints allowed on hard");
    check(game.hintsRemaining() == 0, "Hints clamped at zero");
}

void testRevealIsNotWin() {
    Game game(fixture());
    game.reveal();
    check(game.status() == GameStatus::Revealed, "Reveal ends round without win");
    check(game.board() == fixture().startingBoard, "Reveal does not mutate player board");
    check(game.hint().status == HintStatus::GameEnded, "No hints after reveal");
}

void testReplayStateIsFresh() {
    Game first(fixture());
    first.hint();
    first.place(0,1,9);
    Game second(fixture());
    check(second.filledCount() == 0 && second.hintsRemaining() == 3 && second.mistakesRemaining() == 5,
          "New round must reset counters and board");
}

void testInvalidPuzzlesCannotStartGame() {
    Puzzle bad = fixture();
    bad.startingBoard.at(0,0) = 5;
    expectThrows([&] { Game game(bad); });
}

}  // namespace

int main() {
    const std::vector<std::pair<std::string, std::function<void()>>> cases = {
        {"six original puzzles are uniquely solvable and match answer keys",testOriginalPuzzles},
        {"original difficulty counts",testDifficultyCounts},
        {"difficulty limits",testDifficultyLimits},
        {"puzzle ID lookup",testFindPuzzle},
        {"parse board",testParseBoard},
        {"reject invalid input characters",testInvalidBoardCharacters},
        {"read board file",testReadBoard},
        {"board formatting",testFormatting},
        {"row conflicts",testInvalidClueRow},
        {"column conflicts",testInvalidClueColumn},
        {"box conflicts",testInvalidClueBox},
        {"solver preserves original clues",testSolverLeavesCluesUntouched},
        {"solved board is valid",testSolvedBoardUnique},
        {"reject invalid cell values",testNoSolutionWhenInvalidValue},
        {"consistent but unsolvable board",testConsistentButUnsolvable},
        {"ambiguous board is rejected",testAmbiguousPuzzle},
        {"board coordinates are validated",testBoardBounds},
        {"win only on complete board",testValidMoveAndVictory},
        {"no premature victory",testNotWinUntilLastCell},
        {"fixed and filled cells",testFixedCellAndFilledCell},
        {"out-of-range moves",testInvalidInputsNotPenalized},
        {"wrong answers preserve board",testIncorrectMovesDoNotFillCells},
        {"mistake limit ends game",testLossExactlyAtMistakeLimit},
        {"hint triggers completion",testHintsAffectCompletion},
        {"hint limit enforced",testHintLimit},
        {"revealing solution is not a win",testRevealIsNotWin},
        {"replay resets game state",testReplayStateIsFresh},
        {"invalid puzzle rejected",testInvalidPuzzlesCannotStartGame},
    };
    int passed = 0;
    for (const auto& test : cases) {
        try {
            test.second();
            std::cout << "[PASS] " << test.first << '\n';
            ++passed;
        } catch (const std::exception& error) {
            std::cerr << "[FAIL] " << test.first << " : " << error.what() << '\n';
        }
    }
    std::cout << "\n" << passed << "/" << cases.size() << " tests passed.\n";
    return passed == static_cast<int>(cases.size()) ? 0 : 1;
}
