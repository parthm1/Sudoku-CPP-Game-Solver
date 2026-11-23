#include "sudoku/board.hpp"

#include <cctype>
#include <istream>
#include <sstream>
#include <stdexcept>

namespace sudoku {

int Board::at(int row, int col) const {
    if (row < 0 || row >= kSize || col < 0 || col >= kSize)
        throw std::out_of_range("Board coordinate outside 0-8.");
    return cells.at(row * kSize + col);
}
int& Board::at(int row, int col) {
    if (row < 0 || row >= kSize || col < 0 || col >= kSize)
        throw std::out_of_range("Board coordinate outside 0-8.");
    return cells.at(row * kSize + col);
}
bool Board::operator==(const Board& other) const { return cells == other.cells; }
bool Board::operator!=(const Board& other) const { return !(*this == other); }
bool Board::complete() const { return emptyCount() == 0; }
int Board::emptyCount() const {
    int count = 0;
    for (const int digit : cells) if (digit == 0) ++count;
    return count;
}

Board parseBoard(const std::array<std::string, kSize>& rows) {
    Board board;
    for (int row = 0; row < kSize; ++row) {
        if (rows[row].size() != kSize)
            throw std::invalid_argument("Every puzzle row must contain exactly 9 characters.");
        for (int col = 0; col < kSize; ++col) {
            const char ch = rows[row][col];
            if (ch == '.' || ch == '0') board.at(row, col) = 0;
            else if (ch >= '1' && ch <= '9') board.at(row, col) = ch - '0';
            else throw std::invalid_argument("Only digits 0-9 and '.' are allowed in a puzzle.");
        }
    }
    return board;
}

Board readBoard(std::istream& input) {
    std::array<std::string, kSize> rows;
    int row = 0;
    std::string line;
    while (std::getline(input, line)) {
        std::string compact;
        for (char ch : line) {
            if (!std::isspace(static_cast<unsigned char>(ch))) compact.push_back(ch);
        }
        if (compact.empty()) continue;
        if (row == kSize) throw std::invalid_argument("A puzzle must have exactly 9 nonempty rows.");
        rows[row++] = compact;
    }
    if (row != kSize) throw std::invalid_argument("A puzzle must have exactly 9 nonempty rows.");
    return parseBoard(rows);
}

std::string formatBoard(const Board& board) {
    std::ostringstream out;
    out << "    1 2 3   4 5 6   7 8 9\n";
    for (int row = 0; row < kSize; ++row) {
        if (row % 3 == 0) out << "  +-------+-------+-------+\n";
        out << (row + 1) << " | ";
        for (int col = 0; col < kSize; ++col) {
            const int digit = board.at(row, col);
            out << (digit == 0 ? '.' : static_cast<char>('0' + digit)) << ' ';
            if (col % 3 == 2) out << "| ";
        }
        out << '\n';
    }
    out << "  +-------+-------+-------+\n";
    return out.str();
}

}  // namespace sudoku
