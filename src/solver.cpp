#include "sudoku/solver.hpp"

#include <limits>

namespace sudoku {

bool Solver::canPlace(const Board& board, int row, int col, int value) {
    if (value < 1 || value > 9) return false;
    for (int i = 0; i < kSize; ++i) {
        if (i != col && board.at(row, i) == value) return false;
        if (i != row && board.at(i, col) == value) return false;
    }
    const int top = row / 3 * 3, left = col / 3 * 3;
    for (int r = top; r < top + 3; ++r)
        for (int c = left; c < left + 3; ++c)
            if ((r != row || c != col) && board.at(r, c) == value) return false;
    return true;
}

bool Solver::isValid(const Board& board) {
    for (int r = 0; r < kSize; ++r)
        for (int c = 0; c < kSize; ++c) {
            const int value = board.at(r, c);
            if (value < 0 || value > 9) return false;
            if (value != 0 && !canPlace(board, r, c, value)) return false;
        }
    return true;
}

// Minimum Remaining Values: select the unfilled cell with the fewest candidates.
// -1 means solved, -2 means a blank cell has zero candidates (dead end).
int Solver::bestEmptyCell(const Board& board) {
    int bestIndex = -1, bestCandidates = std::numeric_limits<int>::max();
    for (int r = 0; r < kSize; ++r) {
        for (int c = 0; c < kSize; ++c) {
            if (board.at(r, c) != 0) continue;
            int count = 0;
            for (int digit = 1; digit <= 9; ++digit)
                if (canPlace(board, r, c, digit)) ++count;
            if (count == 0) return -2;
            if (count < bestCandidates) {
                bestCandidates = count;
                bestIndex = r * kSize + c;
            }
        }
    }
    return bestIndex;
}

bool Solver::solveRecursive(Board& board) {
    const int index = bestEmptyCell(board);
    if (index == -1) return true;
    if (index == -2) return false;
    const int row = index / kSize, col = index % kSize;
    for (int digit = 1; digit <= 9; ++digit) {
        if (!canPlace(board, row, col, digit)) continue;
        board.at(row, col) = digit;
        if (solveRecursive(board)) return true;
        board.at(row, col) = 0;
    }
    return false;
}

void Solver::countRecursive(Board& board, int limit, int& count) {
    if (count >= limit) return;
    const int index = bestEmptyCell(board);
    if (index == -1) { ++count; return; }
    if (index == -2) return;
    const int row = index / kSize, col = index % kSize;
    for (int digit = 1; digit <= 9 && count < limit; ++digit) {
        if (!canPlace(board, row, col, digit)) continue;
        board.at(row, col) = digit;
        countRecursive(board, limit, count);
        board.at(row, col) = 0;
    }
}

std::optional<Board> Solver::solve(const Board& board) {
    if (!isValid(board)) return std::nullopt;
    Board candidate = board;
    if (!solveRecursive(candidate)) return std::nullopt;
    return candidate;
}

int Solver::countSolutions(const Board& board, int limit) {
    if (limit <= 0 || !isValid(board)) return 0;
    Board candidate = board;
    int count = 0;
    countRecursive(candidate, limit, count);
    return count;
}

}  // namespace sudoku
