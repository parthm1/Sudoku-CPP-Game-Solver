# Development notes & interview walkthrough

## How the original project worked

The original high-school assignment was a C++ console game, with 12 separate 9×9 arrays: a start board and an answer-key board for each of six puzzles. It selected one of two boards for easy, amateur or hard mode. It kept user mistakes, hint counts and solved progress in global variables. The new project preserves the starting grids but does **not** use the hard-coded answer keys at runtime.

## Why the old progress logic was unreliable

The former `num` variable began at 1 and incremented with correct manual entries, while hints filled squares independently. That meant manually completing a grid could announce victory early, while hints could leave an otherwise completed game unrecognized. The rewritten game checks its live 9×9 board against the solved board after every valid move and hint.

## What the backtracking solver actually does

1. Confirm that the given digits don't violate any row, column or 3×3 box constraints.
2. Choose the empty cell with the smallest set of possible digits (MRV heuristic).
3. Place one candidate and recursively try to solve the rest of the board.
4. If the branch fails, undo the move and try the next candidate.
5. If every cell is filled legally, return a solved board.

A separate traversal counts up to two complete solutions: 0 = impossible, 1 = unique, 2 = ambiguous. Only uniquely solvable built-in boards can start a game.

## What `Game` does

A `Game` instance stores one selected puzzle, the mutable board, its computed solution, difficulty limits and counters. The only legal move is a digit 1–9 in an empty, non-clue cell. A wrong guess increments the mistake counter without adding an incorrect value to the board. On the last allowed mistake, the game ends. Hints populate a valid empty cell and count toward progress. Revealing the full solution forfeits a round; it is not recorded as a win.

## Technical questions you should be able to answer

- Why is a 9×9 array appropriate for representing the Sudoku board?
- What are the row, column and box constraints?
- What does recursive backtracking mean? Why do we undo candidate placements?
- How does MRV reduce search compared to the naive first-empty-cell approach?
- What's the difference between checking if a puzzle has a valid solution and checking that it has a *unique* solution?
- Why is checking the board directly more reliable than counting clicks/moves?
- How would you add a new puzzle, and how could you test it?

## Provenance

The archived high-school source is kept under `archive/` and is explicitly not compiled. The expanded C++17 implementation lives in `include/` and `src/`, with a separate test harness and build configuration. Clearly distinguishing the two versions makes it easy to discuss the project's evolution without implying all features were in the high-school submission.
