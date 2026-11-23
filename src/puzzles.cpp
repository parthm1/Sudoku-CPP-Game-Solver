#include "sudoku/puzzles.hpp"

#include <algorithm>
#include <cctype>

namespace sudoku {

const std::vector<Puzzle>& puzzles() {
    // These six puzzle grids came from the high-school C++ project.
    static const std::vector<Puzzle> catalog = {
        {"E1", Difficulty::Easy, parseBoard({
            "005040903",
            "690102700",
            "001390600",
            "300060005",
            "000000000",
            "200070008",
            "009036800",
            "006701049",
            "702080500",
        })},
        {"E2", Difficulty::Easy, parseBoard({
            "060080420",
            "015060378",
            "000400060",
            "100604830",
            "306810705",
            "080350000",
            "830940000",
            "072130900",
            "009020610",
        })},
        {"A1", Difficulty::Amateur, parseBoard({
            "000003004",
            "405000100",
            "000910070",
            "230050700",
            "010806020",
            "008030091",
            "040098000",
            "002000908",
            "500300000",
        })},
        {"A2", Difficulty::Amateur, parseBoard({
            "010006009",
            "800730000",
            "340000005",
            "090040010",
            "020601050",
            "080020090",
            "600000031",
            "000073006",
            "400100070",
        })},
        {"H1", Difficulty::Hard, parseBoard({
            "060000750",
            "000036800",
            "002800400",
            "000020005",
            "908000107",
            "300040000",
            "006004200",
            "003610000",
            "079000080",
        })},
        {"H2", Difficulty::Hard, parseBoard({
            "009600201",
            "000003090",
            "000802000",
            "010004672",
            "000000000",
            "427500030",
            "000706000",
            "060400000",
            "308001500",
        })},
    };
    return catalog;
}

const Puzzle* findPuzzle(const std::string& id) {
    std::string normalized = id;
    std::transform(normalized.begin(), normalized.end(), normalized.begin(),
                   [](unsigned char ch) { return static_cast<char>(std::toupper(ch)); });
    const auto& catalog = puzzles();
    const auto it = std::find_if(catalog.begin(), catalog.end(),
                                 [&](const Puzzle& p) { return p.id == normalized; });
    return it == catalog.end() ? nullptr : &*it;
}

Limits limitsFor(Difficulty difficulty) {
    switch (difficulty) {
        case Difficulty::Easy: return {5, 3};
        case Difficulty::Amateur: return {4, 2};
        case Difficulty::Hard: return {3, 1};
    }
    return {0, 0};
}

std::string difficultyName(Difficulty difficulty) {
    switch (difficulty) {
        case Difficulty::Easy: return "Easy";
        case Difficulty::Amateur: return "Amateur";
        case Difficulty::Hard: return "Hard";
    }
    return "Unknown";
}

}  // namespace sudoku
