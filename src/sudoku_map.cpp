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
    bool add_starting = ((squared_line == 1) && (line == 1));
    bool add_finish = ((squared_line == 3) && (line == 3));

    switch (squared_line)
    {
        case 1:
            squared_line = 0;
            break;

        case 2:
            squared_line = 3;
            break;

        case 3:
            squared_line = 6;
            break;

        default:
            throw sudoku_error(SUDOKU_UNKNOWN_ERROR);

    }

    switch (line)
    {
        case 1:

            if (add_starting)
            {
                StringStream << "╔═══╤═══╤═══╦═══╤═══╤═══╦═══╤═══╤═══╗\n";
            }

                        // square 1, line 1
            StringStream << "║ " << square_map[squared_line + 0][0] << " │"
                         << " " << square_map[squared_line + 0][1] << " |"
                         << " " << square_map[squared_line + 0][2] << " ║"
                        // square 2, line 1
                        << " " << square_map[squared_line + 1][0] << " │"
                        << " " << square_map[squared_line + 1][1] << " |"
                        << " " << square_map[squared_line + 1][2] << " ║"
                        // square 3, line 1
                        << " " << square_map[squared_line + 2][0] << " │"
                        << " " << square_map[squared_line + 2][1] << " |"
                        << " " << square_map[squared_line + 2][2] << " ║"
                        ;
            break;

        case 2:
            StringStream << "╟───┼───┼───╫───┼───┼───╫───┼───┼───╢\n"
                         // square 1, line 2
                         << "║ " << square_map[squared_line + 0][3] << " │"
                         << " " << square_map[squared_line + 0][4] << " |"
                         << " " << square_map[squared_line + 0][5] << " ║"
                         // square 2, line 2
                         << " " << square_map[squared_line + 1][3] << " │"
                         << " " << square_map[squared_line + 1][4] << " |"
                         << " " << square_map[squared_line + 1][5] << " ║"
                         // square 3, line 2
                         << " " << square_map[squared_line + 2][3] << " │"
                         << " " << square_map[squared_line + 2][4] << " |"
                         << " " << square_map[squared_line + 2][5] << " ║"
                    ;
            break;

        case 3:
            StringStream << "╟───┼───┼───╫───┼───┼───╫───┼───┼───╢\n"
                         // square 1, line 3
                         << "║ " << square_map[squared_line + 0][6] << " │"
                         << " " << square_map[squared_line + 0][7] << " |"
                         << " " << square_map[squared_line + 0][8] << " ║"
                         // square 2, line 3
                         << " " << square_map[squared_line + 1][6] << " │"
                         << " " << square_map[squared_line + 1][7] << " |"
                         << " " << square_map[squared_line + 1][8] << " ║"
                         // square 3, line 3
                         << " " << square_map[squared_line + 2][6] << " │"
                         << " " << square_map[squared_line + 2][7] << " |"
                         << " " << square_map[squared_line + 2][8] << " ║\n";
            if (add_finish)
            {
                StringStream << "╚═══╧═══╧═══╩═══╧═══╧═══╩═══╧═══╧═══╝";
            }
            else
            {
                StringStream << "╠═══╪═══╪═══╬═══╪═══╪═══╬═══╪═══╪═══╣";
            }

            break;

        default:
            throw sudoku_error(SUDOKU_UNKNOWN_ERROR);
    }

    return StringStream;
}
