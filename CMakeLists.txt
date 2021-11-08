cmake_minimum_required(VERSION 3.20)
project(sudoku)

set(CMAKE_CXX_STANDARD 20)

add_library(libsudoku STATIC
        src/sudoku_map.cpp      src/include/sudoku_map.h
        src/sudoku_error.cpp    src/include/sudoku_error.h
        )
target_include_directories(libsudoku PUBLIC src/include)
target_compile_definitions(libsudoku PUBLIC "SUDOKU_ERROR_PREFIX=\"(sudoku) \"")

add_executable(sudoku src/main.cpp)
target_include_directories(sudoku PUBLIC src/include)
target_link_libraries(sudoku PUBLIC libsudoku)
