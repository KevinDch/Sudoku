#include <sudoku_map.h>
#include <sstream>
#include <sudoku_error.h>

/// check if num is in range
/**
 * @param num number
 * @param range_start range start point
 * @param range_stop  range end point
 * @return if num is in range, RT
 */
inline bool if_in_range(int num, int range_start = 1, int range_stop = 9)
{
    return (num >= range_start) && (num <= range_stop);
}

void sudoku_map::generate_new_map()
{
    allocate_map();
}

int sudoku_map::generate_without(const std::vector<int> &without, int range_from, int range_to)
{
    if (without.empty())
    {
        return gen_random_num(range_from, range_to);
    }

    int num = *without.begin();
    while (std::find(without.begin(), without.end(), num) != without.end())
    {
        num = gen_random_num(range_from, range_to);
    }

    return num;
}

void sudoku_map::allocate_map()
{
    for (int i = 0; i < 9; i++)
    {
        single_square_t singleSquare;

        for (int j = 0; j < 9; j++)
        {
            singleSquare.emplace_back(0);
        }

        square_map.emplace_back(singleSquare);
    }
}

std::string sudoku_map::print_map() const
{
    std::stringstream StringStream;

    for (int square_line = 1; square_line <= 3; square_line++)
    {
        for (int line = 1; line <= 3; line++)
        {
            print_line(square_line, line, StringStream);
            StringStream << std::endl;
        }
    }

    return StringStream.str();
}

std::stringstream &
sudoku_map::print_line(int squared_line,
                       int line,
                       std::stringstream &StringStream) const
{
    return print_line_undefined_type(squared_line, line, StringStream, square_map);
}

std::string sudoku_map::print_sudoku(int difficulty) const
{
    single_prt_map_t char_square_map;
    std::stringstream StringStream;

    convert_to_char(char_square_map);
    set_blank(char_square_map, difficulty);

    for (int square_line = 1; square_line <= 3; square_line++)
    {
        for (int line = 1; line <= 3; line++)
        {
            print_line_undefined_type(square_line,
                                      line,
                                      StringStream,
                                      char_square_map);
            StringStream << std::endl;
        }
    }

    return StringStream.str();
}

sudoku_map::single_prt_map_t & sudoku_map::convert_to_char(single_prt_map_t & _map) const
{
    for (int square = 0; square < 9; square++)
    {
        single_prt_square_t singleSquare;

        for (int position = 0; position < 9; position++)
        {
            singleSquare.emplace_back('0' + square_map[square][position]);
        }

        _map.emplace_back(singleSquare);
    }

    return _map;
}

sudoku_map::single_prt_map_t &sudoku_map::set_blank(
        sudoku_map::single_prt_map_t &_map, int difficulty) const
{
    auto if_blank = [&](int difficulty, const sudoku_map* _this)->bool
    {
        auto num = _this->gen_random_num(0, 99);
        return difficulty > num;
    };

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if(if_blank(difficulty, this))
            {
                _map[i][j] = ' ';
            }
        }
    }
}
