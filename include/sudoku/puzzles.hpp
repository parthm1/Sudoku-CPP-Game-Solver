#pragma once

#include "sudoku/board.hpp"

#include <string>
#include <vector>

namespace sudoku {

enum class Difficulty { Easy, Amateur, Hard };

struct Puzzle {
    std::string id;   // E1 / E2 / A1 / A2 / H1 / H2
    Difficulty difficulty;
    Board startingBoard;
};

struct Limits {
    int mistakes;
    int hints;
};

const std::vector<Puzzle>& puzzles();
const Puzzle* findPuzzle(const std::string& id);
Limits limitsFor(Difficulty difficulty);
std::string difficultyName(Difficulty difficulty);

}  // namespace sudoku
