#include <sudoku_map.h>
#include <iostream>
int main()
{
    sudoku_map sudokuMap;
    sudokuMap.generate_new_map();
    std::cout << sudokuMap.print_map();
    std::cout << sudokuMap.print_sudoku(50);
    return 0;
}
