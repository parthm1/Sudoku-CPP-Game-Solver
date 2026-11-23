# Publishing this project on GitHub

1. Create a new **public** repository such as `Sudoku-CPP-Game-Solver`.
2. Extract the downloaded ZIP archive on your computer.
3. Upload the **contents** of `Sudoku-CPP-Game-Solver`, not the `build/` directory. Preserve subfolders (`src`, `include`, `tests`, `examples`, `.github`, `docs`, `archive`).
4. GitHub's browser file picker may hide `.gitignore` or `.github` because they start with a dot. If necessary, create `.gitignore` manually using **Add file → Create new file**, and preserve the `.github/workflows/build.yml` file by dragging its containing folder.
5. Check that the README renders and that the Actions tab runs the CMake test workflow. The tests are not verified on GitHub until the remote workflow succeeds.
6. Suggested initial commit message: `Add C++ Sudoku game and solver`.

**Do not upload:** `build/`, `.idea/`, other generated compiled files or unrelated archived school assignments.

**Suggested repository description:**
> C++17 Sudoku game and backtracking solver with 6 validated puzzles, three difficulty modes, hints, mistake tracking, and automated tests.
