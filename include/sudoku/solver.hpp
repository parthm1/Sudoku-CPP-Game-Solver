#pragma once

#include "sudoku/board.hpp"

#include <optional>

namespace sudoku {

class Solver {
public:
    // Checks nonzero givens for conflicts in rows, columns and 3x3 boxes.
    static bool isValid(const Board& board);
    // Returns one solution, or nullopt if clues conflict or no solution exists.
    static std::optional<Board> solve(const Board& board);
    // Counts up to 'limit' solutions; limit=2 is enough to check uniqueness.
    static int countSolutions(const Board& board, int limit = 2);

private:
    static bool canPlace(const Board& board, int row, int col, int value);
    static int bestEmptyCell(const Board& board);
    static bool solveRecursive(Board& board);
    static void countRecursive(Board& board, int limit, int& count);
};

}  // namespace sudoku
