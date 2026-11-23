#include "sudoku/game.hpp"
#include "sudoku/solver.hpp"

#include <stdexcept>

namespace sudoku {

Game::Game(const Puzzle& puzzle)
    : puzzle_(puzzle), board_(puzzle.startingBoard), limits_(limitsFor(puzzle.difficulty)) {
    if (Solver::countSolutions(board_, 2) != 1)
        throw std::invalid_argument("Puzzle must have exactly one valid solution.");
    solution_ = *Solver::solve(board_);
}

MoveStatus Game::place(int row, int col, int value) {
    if (status_ != GameStatus::Playing) return MoveStatus::GameEnded;
    if (row < 0 || row >= kSize || col < 0 || col >= kSize || value < 1 || value > 9)
        return MoveStatus::InvalidInput;
    if (puzzle_.startingBoard.at(row, col) != 0) return MoveStatus::FixedCell;
    if (board_.at(row, col) != 0) return MoveStatus::FilledCell;
    if (value != solution_.at(row, col)) {
        ++mistakesMade_;
        if (mistakesRemaining() == 0) status_ = GameStatus::Lost;
        return MoveStatus::Incorrect;
    }
    board_.at(row, col) = value;
    if (board_ == solution_) status_ = GameStatus::Won;
    return MoveStatus::Correct;
}

HintResult Game::hint() {
    if (status_ != GameStatus::Playing) return {HintStatus::GameEnded};
    if (hintsRemaining() == 0) return {HintStatus::NoneRemaining};
    for (int r = 0; r < kSize; ++r) {
        for (int c = 0; c < kSize; ++c) {
            if (board_.at(r, c) != 0) continue;
            const int answer = solution_.at(r, c);
            board_.at(r, c) = answer;
            ++hintsUsed_;
            if (board_ == solution_) status_ = GameStatus::Won;
            return {HintStatus::Applied, r, c, answer};
        }
    }
    return {HintStatus::NoEmptyCells};
}

void Game::reveal() {
    if (status_ == GameStatus::Playing) status_ = GameStatus::Revealed;
}

int Game::filledCount() const {
    return puzzle_.startingBoard.emptyCount() - board_.emptyCount();
}

}  // namespace sudoku
