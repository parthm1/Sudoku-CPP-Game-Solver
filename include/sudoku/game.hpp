#pragma once

#include "sudoku/puzzles.hpp"

#include <optional>

namespace sudoku {

enum class GameStatus { Playing, Won, Lost, Revealed };
enum class MoveStatus { Correct, InvalidInput, FixedCell, FilledCell, Incorrect, GameEnded };
enum class HintStatus { Applied, NoneRemaining, GameEnded, NoEmptyCells };

struct HintResult {
    HintStatus status;
    int row = -1;
    int col = -1;
    int value = 0;
};

class Game {
public:
    explicit Game(const Puzzle& puzzle);

    MoveStatus place(int row, int col, int value); // 0-based row/column
    HintResult hint();
    void reveal(); // Revealing solution ends the round without a win.

    const Board& board() const { return board_; }
    const Board& solution() const { return solution_; }
    const Puzzle& puzzle() const { return puzzle_; }
    int mistakesRemaining() const { return limits_.mistakes - mistakesMade_; }
    int hintsRemaining() const { return limits_.hints - hintsUsed_; }
    int filledCount() const;
    GameStatus status() const { return status_; }

private:
    Puzzle puzzle_;
    Board board_;
    Board solution_;
    Limits limits_;
    int mistakesMade_ = 0;
    int hintsUsed_ = 0;
    GameStatus status_ = GameStatus::Playing;
};

}  // namespace sudoku
