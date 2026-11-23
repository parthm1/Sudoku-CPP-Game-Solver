#pragma once

#include <array>
#include <iosfwd>
#include <string>
#include <vector>

namespace sudoku {

constexpr int kSize = 9;

struct Board {
    std::array<int, kSize * kSize> cells{};

    int at(int row, int col) const;
    int& at(int row, int col);
    bool operator==(const Board& other) const;
    bool operator!=(const Board& other) const;
    bool complete() const;
    int emptyCount() const;
};

// Rows must contain nine characters each: 1-9 for clues, 0 or . for blanks.
Board parseBoard(const std::array<std::string, kSize>& rows);
Board readBoard(std::istream& input);
std::string formatBoard(const Board& board);

}  // namespace sudoku
