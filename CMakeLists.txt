cmake_minimum_required(VERSION 3.16)
project(SudokuCPP VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(sudoku_core
    src/board.cpp
    src/solver.cpp
    src/puzzles.cpp
    src/game.cpp
)
target_include_directories(sudoku_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(MSVC)
    target_compile_options(sudoku_core PRIVATE /W4)
else()
    target_compile_options(sudoku_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(sudoku src/main.cpp)
target_link_libraries(sudoku PRIVATE sudoku_core)

include(CTest)
if(BUILD_TESTING)
    add_executable(sudoku_tests tests/test_sudoku.cpp)
    target_link_libraries(sudoku_tests PRIVATE sudoku_core)
    add_test(NAME sudoku_unit_tests COMMAND sudoku_tests)
    add_test(NAME original_puzzle_validation COMMAND sudoku --validate)
    add_test(NAME solve_example_file COMMAND sudoku --solve-file
        ${CMAKE_CURRENT_SOURCE_DIR}/examples/puzzle.txt)

    find_package(Python3 COMPONENTS Interpreter QUIET)
    if(Python3_Interpreter_FOUND)
        add_test(NAME command_line_integration
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/cli_smoke.py
                    $<TARGET_FILE:sudoku> ${CMAKE_CURRENT_SOURCE_DIR})
    endif()
endif()
