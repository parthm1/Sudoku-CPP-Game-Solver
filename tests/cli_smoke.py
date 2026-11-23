"""Integration smoke tests for the interactive CLI (Python stdlib only).

CMake runs this only if a Python interpreter is available. This is not part
of the Sudoku application itself, which is implemented entirely in C++17.
"""

import pathlib
import subprocess
import sys

binary = pathlib.Path(sys.argv[1])
project_root = pathlib.Path(sys.argv[2])


def run(*args, user_input=None):
    completed = subprocess.run(
        [str(binary), *args], input=user_input, text=True,
        capture_output=True, timeout=15,
    )
    return completed.returncode, completed.stdout + completed.stderr


checks = 0


def expect(condition, description):
    global checks
    checks += 1
    if not condition:
        raise AssertionError(description)
    print(f"[PASS] {description}")


code, output = run("--list")
expect(code == 0 and all(x in output for x in ["E1", "E2", "A1", "A2", "H1", "H2"]),
       "list 6 puzzles")

code, output = run("--validate")
expect(code == 0 and output.count("unique solution") == 6, "six catalog puzzles validate")

for puzzle in ["E1", "E2", "A1", "A2", "H1", "H2"]:
    code, output = run("--solve", puzzle)
    expect(code == 0 and "Solved board:" in output and "capped at 2): 1" in output,
           f"solve built-in puzzle {puzzle}")

code, output = run("--solve-file", str(project_root / "examples" / "puzzle.txt"))
expect(code == 0 and "Solved board:" in output, "solve external puzzle file")

code, output = run("--solve-file", "missing_sudoku_file.txt")
expect(code != 0 and "Cannot open puzzle file" in output, "friendly file not found")

code, output = run("--solve", "zzz")
expect(code == 2 and "Unknown puzzle ID" in output, "unknown puzzle ID")

code, output = run("--puzzle", "E1", user_input="help\n1 1 8\nhint\nsolve\nn\n")
expect(code == 0 and "Correct!" in output and "Hint: row" in output
       and "not counted as a win" in output and "Thanks for playing!" in output,
       "game play, hint, reveal, no replay")

code, output = run("--puzzle", "E1", user_input="0 3 1\n1 3 4\n1 1 8\nnew\nq\n")
expect(code == 0 and "Rows, columns and values must be between 1 and 9" in output
       and "original clue" in output and "Correct!" in output
       and "Choose difficulty" in output, "invalid input, fixed clues, restart")

code, output = run("--puzzle", "H1", user_input="1 1 9\n1 1 9\n1 1 9\nn\n")
expect(code == 0 and "Game over" in output and "Thanks for playing!" in output,
       "mistakes end hard mode and no-replay exits")

# Solve E1 fully with scripted moves and verify no early victory.
rows = [
    "825647913", "693152784", "471398652", "317864295",
    "958213476", "264975138", "149536827", "586721349", "732489561"
]
givens = (project_root / "examples" / "puzzle.txt").read_text().splitlines()
commands = [f"{r+1} {c+1} {rows[r][c]}" for r in range(9) for c in range(9)
            if givens[r][c] == "0"]
code, output = run("--puzzle", "E1", user_input="\n".join(commands) + "\nn\n")
expect(code == 0 and output.count("Correct!") == len(commands)
       and output.count("Congratulations!") == 1 and "Filled: 48/49" in output,
       "full puzzle wins precisely after final move")

print(f"\n{checks} command-line integration checks passed.")
