
# Sudoku — C++ Game & Backtracking Solver

A command-line Sudoku game and puzzle solver built in **C++17**. Play through six Sudoku puzzles, choose between three difficulty levels, use hints, or solve custom puzzles with a recursive backtracking algorithm.

This project began as a high-school programming assignment. The original source code is preserved in [`archive/`](archive/), alongside the expanded implementation with a Sudoku solver, modular components, and automated tests.

## Features

- **Three difficulty levels:** Easy, Amateur, and Hard, with two puzzles per level.
- **Interactive gameplay:** Enter numbers, receive hints, track mistakes, and start new games.
- **Backtracking solver:** Solves Sudoku puzzles using recursive backtracking and the Minimum Remaining Values (MRV) heuristic.
- **Puzzle validation:** Detects conflicting clues, unsolvable puzzles, and puzzles with multiple solutions.
- **Custom puzzles:** Solve Sudoku boards provided through a text file.
- **Automated testing:** 28 C++ tests covering game logic, puzzle validation, and solver functionality.

### Difficulty Levels

| Difficulty | Puzzles | Mistakes Allowed | Hints Available |
|------------|---------|------------------|-----------------|
| Easy | E1, E2 | 5 | 3 |
| Amateur | A1, A2 | 4 | 2 |
| Hard | H1, H2 | 3 | 1 |

All six built-in puzzles have been verified to have exactly one solution.

## Getting Started

### Requirements

- A C++17-compatible compiler (MSVC, GCC, or Clang)
- CMake 3.16 or newer
- Visual Studio 2022, VS Code, or another compatible development environment

No external C++ libraries are required.

### Windows — Visual Studio 2022

1. Download or clone this repository.
2. Open **Visual Studio 2022**.
3. Select **File → Open → Folder**.
4. Select the project folder containing `CMakeLists.txt`.
5. Wait for Visual Studio to configure the CMake project.
6. Select `sudoku.exe` as the startup target.
7. Press **Ctrl + F5** to build and run the game.

Alternatively, build from a Developer PowerShell for Visual Studio:

```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\Release\sudoku.exe
```

For single-configuration generators, the executable may be located at `build\sudoku.exe` instead.

**Quick start:** You can also run `run_windows.bat` to configure, compile, and launch the game automatically, provided CMake and a C++ compiler are installed.

### macOS / Linux

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/sudoku
```

## How to Play

Start the game and select a difficulty level.

The game displays a 9×9 Sudoku board containing fixed numbers and empty cells. Fill the empty cells using Sudoku rules:

- Each row must contain digits 1–9 without repetition.
- Each column must contain digits 1–9 without repetition.
- Each 3×3 box must contain digits 1–9 without repetition.

### Game Preview

```text
SUDOKU | C++ Game & Solver

=== Easy puzzle E1 ===

    1 2 3   4 5 6   7 8 9
  +-------+-------+-------+
1 | . . 5 | . 4 . | 9 . 3 |
2 | 6 9 . | 1 . 2 | 7 . . |
3 | . . 1 | 3 9 . | 6 . . |
  +-------+-------+-------+
4 | 3 . . | . 6 . | . . 5 |
5 | . . . | . . . | . . . |
6 | 2 . . | . 7 . | . . 8 |
  +-------+-------+-------+
7 | . . 9 | . 3 6 | 8 . . |
8 | . . 6 | 7 . 1 | . 4 9 |
9 | 7 . 2 | . 8 . | 5 . . |
  +-------+-------+-------+

Filled: 0/49 | Mistakes left: 5 | Hints left: 3

Move or command: 1 1 8
Correct!
```

### Controls

Enter a move using the format:

```text
row column number
```

For example, `1 1 8` places the number 8 in row 1, column 1.

| Command | Description |
|---------|-------------|
| `1 1 8` | Enter a number into a cell |
| `hint` | Reveal a correct value in an empty cell |
| `solve` | Display the completed solution and end the round |
| `new` | Start another puzzle |
| `help` | Display available commands |
| `quit` | Exit the game |

Original clues cannot be modified. Incorrect answers count toward the mistake limit, while hints are limited according to difficulty.

## Sudoku Solver

The application includes a recursive **backtracking algorithm** that solves Sudoku puzzles.

Rather than trying numbers randomly, the solver:

1. Identifies an empty cell.
2. Determines which numbers are valid for that cell.
3. Uses the **Minimum Remaining Values (MRV)** heuristic to select the cell with the fewest valid candidates.
4. Tries a candidate and recursively continues solving the puzzle.
5. Backtracks when a candidate leads to an invalid solution.

This approach reduces unnecessary searching compared with always choosing the first empty cell.

The solver can also check whether a puzzle has no solution, exactly one solution, or multiple solutions.

### Command-Line Options

| Command | Description |
|---------|-------------|
| `sudoku` | Start the interactive game |
| `sudoku --list` | List available puzzles |
| `sudoku --puzzle E1` | Play a specific puzzle |
| `sudoku --solve H2` | Solve a built-in puzzle |
| `sudoku --solve-file examples/puzzle.txt` | Solve a custom Sudoku puzzle |
| `sudoku --validate` | Validate all six built-in puzzles |
| `sudoku --help` | Display command-line help |

Replace `sudoku` with the appropriate executable path for your operating system, such as `./build/sudoku` on macOS/Linux or `.\build\Release\sudoku.exe` on Windows.

### Custom Puzzle Format

Custom puzzles must contain nine nonempty rows of nine cells each.

- Digits `1–9` represent existing numbers.
- `0` or `.` represents an empty cell.
- Spaces within rows are permitted.

Example:

```text
005040903
690102700
001390600
300060005
000000000
200070008
009036800
006701049
702080500
```

A sample puzzle is available in [`examples/puzzle.txt`](examples/puzzle.txt).

## Project Structure

```text
Sudoku-CPP-Game-Solver/
|
|-- archive/
|   |-- original_2022_main.cpp
|   |-- README.md
|
|-- docs/
|-- examples/
|   |-- puzzle.txt
|
|-- include/sudoku/
|   |-- board.hpp
|   |-- game.hpp
|   |-- puzzles.hpp
|   |-- solver.hpp
|
|-- src/
|   |-- board.cpp
|   |-- game.cpp
|   |-- main.cpp
|   |-- puzzles.cpp
|   |-- solver.cpp
|
|-- tests/
|   |-- test_sudoku.cpp
|   |-- cli_smoke.py
|   |-- expected_solutions.hpp
|
|-- CMakeLists.txt
|-- README.md
|-- run_windows.bat
```

### Main Components

| Component | Responsibility |
|-----------|----------------|
| `board.cpp` | Board representation, input parsing, and display |
| `game.cpp` | Gameplay, hints, mistakes, and win/loss conditions |
| `puzzles.cpp` | Built-in Sudoku puzzles and difficulty settings |
| `solver.cpp` | Sudoku validation and recursive backtracking solver |
| `main.cpp` | Console interface and command-line operations |
| `tests/` | Automated tests for gameplay and solver functionality |

## Testing

The project includes **28 self-contained C++ tests** covering:

- Correct solutions for all six original puzzles
- Backtracking and solution validation
- Invalid and unsolvable puzzles
- Detection of multiple solutions
- Input validation and fixed starting cells
- Hints and mistake limits
- Victory conditions and game-state resets

Run the automated tests after building the project:

```bash
ctest --test-dir build -C Release --output-on-failure
```

Python 3 is optional and is used only for the additional command-line integration checks in [`tests/cli_smoke.py`](tests/cli_smoke.py).

The application itself does not require Python.

## Project Background

This project originated as a high-school C++ Sudoku game containing six puzzles and three difficulty levels.

The [original source code](archive/original_2022_main.cpp) is preserved in the repository for reference.

The current implementation in `src/` and `include/` expands on that foundation with a backtracking solver, reusable components, improved game-state handling, and automated tests.

The archived high-school version is not part of the current build.

## Limitations

- The playable game contains six predefined puzzles rather than generating new ones.
- Difficulty levels are inherited from the original project and are not based on formal computational difficulty ratings.
- The game uses a text-based console interface rather than a graphical interface.

## Technologies Used

- **Language:** C++17
- **Build System:** CMake
- **Algorithms:** Recursive Backtracking, Minimum Remaining Values (MRV)
- **Concepts:** Arrays, Recursion, Input Validation, Object-Oriented Programming, Game-State Management
- **Testing:** CTest, C++ Unit Tests, Python CLI Integration Tests

## Author

**Parth Madan**

Honours BSc Computer Science — York University

[GitHub Profile](https://github.com/parthm1)
