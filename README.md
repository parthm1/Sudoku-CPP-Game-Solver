# Sudoku — C++ Puzzle Game & Backtracking Solver

A command-line Sudoku game and puzzle solver in **C++17**, based on a project I originally began in high school. It features six Sudoku puzzles across three difficulty levels, hint and mistake systems, and a recursive backtracking solver.

This repository contains the archived high-school source along with a separate, expanded implementation in `src/` and `include/`. The solver, modular architecture, and automated tests are features of the expanded implementation rather than the archived assignment.

## Highlights

- **Playable 9×9 Sudoku** with easy, amateur and hard modes, each with two preserved puzzles.
- **Backtracking solver** with a *minimum remaining values* (MRV) search heuristic.
- **Puzzle validation** that detects conflicting clues, unsolvable boards and multiple solutions.
- **Hints** that reveal an empty square, enforce per-difficulty limits and count toward completion.
- **Mistake limits**, immutable starting clues, input validation, precise win/loss detection and clean replay.
- **Solve mode** for the six bundled puzzles or any 9-line Sudoku text file.
- **28 C++ unit tests**, command-line integration tests and CTest integration.
- CMake project configured for **Windows, macOS and Linux**, with a GitHub Actions workflow for Windows and Ubuntu.

### Puzzle difficulty

| Level | Puzzles | Mistakes allowed | Hints available |
|---|---|---:|---:|
| Easy | E1, E2 | 5 | 3 |
| Amateur | A1, A2 | 4 | 2 |
| Hard | H1, H2 | 3 | 1 |

All six original puzzles were checked to have **exactly one solution**. Their solutions were cross-checked against the archived answer keys from the original 2022 source.

## Preview

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

**Move format:** `row column value` using coordinates 1–9, for example `1 1 8`. Type `hint`, `solve`, `new`, `help` or `quit` for other actions.

## Build and run

### Requirements

- C++17-compatible compiler (e.g., MSVC, GCC or Clang)
- CMake 3.16 or later
- Python 3 is **optional** and used only for additional command-line integration tests

### Windows (Visual Studio with C++ tools)

In the **Developer PowerShell for Visual Studio** or a terminal configured with a C++ compiler, from the repository directory:

```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\Release\sudoku.exe
```

With a single-configuration generator (e.g., MinGW Makefiles), the executable may instead be at `build\sudoku.exe`.

If `cmake` reports that no C++ compiler is found, install a C++ compiler / Visual Studio's **Desktop development with C++** workload, then try again.

**Windows shortcut:** Once CMake and a C++ compiler are installed, you may also double-click `run_windows.bat` in the extracted project folder to configure, compile and start the game.

### macOS / Linux

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/sudoku
```

### Commands

| Example | Effect |
|---|---|
| `sudoku` | Start the interactive game and choose a level |
| `sudoku --list` | List all six included puzzles |
| `sudoku --puzzle E1` | Play puzzle E1 directly |
| `sudoku --solve H2` | Solve the bundled hard puzzle H2 |
| `sudoku --solve-file examples/puzzle.txt` | Solve a puzzle supplied in a text file |
| `sudoku --validate` | Verify all six puzzles have exactly one solution |
| `sudoku --help` | Show controls and options |

On Windows, prepend the correct compiled executable path shown in the build instructions. On macOS/Linux, use `./build/sudoku`.

### Format of external puzzle files

An external puzzle file should contain exactly **9 nonempty rows**, each with **9 characters**. Digits `1`–`9` represent givens; `0` or `.` represents an empty square. Spaces within a row are allowed. Example:

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

See [`examples/puzzle.txt`](examples/puzzle.txt).

## Automated tests

From the project directory:

```bash
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

`tests/test_sudoku.cpp` contains **28 self-contained C++ tests** (no external testing framework required). They cover the six original solution keys, solver logic, invalid and ambiguous boards, fixed clues, invalid input, mistake limits, hints, victory and replay state. If Python 3 is available, CTest also runs [`tests/cli_smoke.py`](tests/cli_smoke.py) to simulate complete sessions and test command-line operations.

A GitHub Actions workflow is included in `.github/workflows/build.yml` to build and run CTest on Ubuntu and Windows after the repository is published.

## Design and implementation

| Component | Responsibility |
|---|---|
| `board.hpp` / `board.cpp` | 9×9 board representation, parsing and pretty-printing |
| `solver.hpp` / `solver.cpp` | Sudoku rule checking and recursive MRV backtracking |
| `puzzles.hpp` / `puzzles.cpp` | Six original starting grids, IDs and difficulty limits |
| `game.hpp` / `game.cpp` | Game state, hint / mistake rules, win / loss tracking |
| `main.cpp` | Interactive console UI and CLI operations |
| `tests/` | Unit and end-to-end command-line tests |

**Why MRV?** Instead of taking the first empty square, the solver picks the square with the fewest possible digits, reducing unnecessary search in many Sudoku puzzles. It fills a candidate, continues recursively, and backtracks when a branch cannot produce a valid board. A separate routine counts up to two solutions to check uniqueness.

**How a win is detected:** The game compares its **actual filled board** to the valid solved board, rather than counting the number of moves. Hints change the real board, so they cannot cause false progress or premature completion.

## Project background

This project began as a high-school C++ Sudoku game with six hand-authored puzzles and three difficulty levels. The archived source is available at [`archive/original_2022_main.cpp`](archive/original_2022_main.cpp); it is retained for reference and is **not** part of the current build.

The playable code in `src/` and `include/` uses modular board and game components, computes solutions with backtracking, handles hints and replay correctly, and includes automated tests. These features describe the **current repository**, not necessarily the original school submission.

## Limitations and future work

- The playable game uses the original **six** hand-authored puzzles; it does not generate new random puzzles.
- Difficulty names are inherited from the original project and are not based on a formal solving-complexity rating.
- The interface is terminal-based rather than graphical.
- The solver accepts a custom puzzle file; it validates and solves but does not attempt OCR or image recognition.

## Author

**Parth Madan** — York University, Honours BSc Computer Science

Based on my high-school Sudoku project. See the archived source and current project files for implementation details.
