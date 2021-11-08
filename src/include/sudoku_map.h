#ifndef SUDOKU_SUDOKU_MAP_H
#define SUDOKU_SUDOKU_MAP_H

#include <vector>
#include <random>
#include <sudoku_error.h>
#include <sstream>

/// a sudoku map
class sudoku_map
{
private:
    typedef std::vector < int > single_square_t;
    typedef std::vector < char > single_prt_square_t;
    typedef std::vector < single_prt_square_t > single_prt_map_t;

    std::vector < single_square_t > square_map;

    /// convert square_map to single_prt_map_t (char type map)
    /// @param _map pre-defined single_prt_map_t
    /// @return reference of pre-defined single_prt_map_t (_map)
    single_prt_map_t & convert_to_char(single_prt_map_t & _map) const;

    /// set blank in single_prt_map_t
    /// @param _map pre-defined single_prt_map_t
    /// @param difficulty difficulty (1-100)
    /// @return reference of pre-defined single_prt_map_t (_map)
    single_prt_map_t & set_blank(single_prt_map_t & _map, int difficulty) const;

    /// generate numbers between range_from and range_to
    /**
     *  @param range_from range start
     *  @param range_to range finish
     *  @return random number **/
    template<typename Type>
    Type gen_random_num(Type range_from, Type range_to) const;

    /// generate numbers, excluding numbers in the without list
    /** @param without without list
     *  @param range_from range start
     *  @param range_to range finish
     *  @return random number **/
    int generate_without(const std::vector < int > & without,
                         int range_from = 1, int range_to = 9);

    /// allocate the square map, filled with 0s
    /** @param none
     *  @return none **/
    void allocate_map();

    /// print single line in single square to string stream
    /** @param square square line number (ranging from 1 to 3)
     *  @param line line number (ranging from 1 to 3)
     *  @param StringStream target string stream
     *  @return target string stream **/
    std::stringstream & print_line(int squared_line,
                                   int line,
                                   std::stringstream & StringStream) const;

    /// print single line in single square to string stream with random blank positions
    /** @param square square line number (ranging from 1 to 3)
     *  @param line line number (ranging from 1 to 3)
     *  @param StringStream target string stream
     *  @param _square_map char type square map
     *  @return target string stream **/
    template<typename Type>
    static std::stringstream & print_line_undefined_type(
            int squared_line, int line,
            std::stringstream & StringStream,
            const std::vector < std::vector < Type > > & _square_map);

public:
    /// generate a new sudoku map
    void generate_new_map();

    /// get sudoku map
    /// @return sudoku map (solved)
    [[nodiscard]] std::vector < single_square_t > get_map() const { return square_map; }

    /// print sudoku map (solved)
    /// @return sudoku map
    [[nodiscard]] std::string print_map() const;

    /// print sudoku map (unsolved)
    /// @param difficulty difficulty (1-100)
    /// @return sudoku map
    [[nodiscard]] std::string print_sudoku(int difficulty) const;
};

template<typename Type>
Type sudoku_map::gen_random_num(Type range_from, Type range_to) const
{
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<Type> distr(range_from, range_to);
    return distr(generator);
}

template<typename Type>
std::stringstream &sudoku_map::print_line_undefined_type(
        int squared_line,
        int line,
        std::stringstream &StringStream,
        const std::vector < std::vector < Type > > &_square_map)
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
            StringStream << "║ " << _square_map[squared_line + 0][0] << " │"
                         << " " << _square_map[squared_line + 0][1] << " |"
                         << " " << _square_map[squared_line + 0][2] << " ║"
                         // square 2, line 1
                         << " " << _square_map[squared_line + 1][0] << " │"
                         << " " << _square_map[squared_line + 1][1] << " |"
                         << " " << _square_map[squared_line + 1][2] << " ║"
                         // square 3, line 1
                         << " " << _square_map[squared_line + 2][0] << " │"
                         << " " << _square_map[squared_line + 2][1] << " |"
                         << " " << _square_map[squared_line + 2][2] << " ║"
                    ;
            break;

        case 2:
            StringStream << "╟───┼───┼───╫───┼───┼───╫───┼───┼───╢\n"
                         // square 1, line 2
                         << "║ " << _square_map[squared_line + 0][3] << " │"
                         << " " << _square_map[squared_line + 0][4] << " |"
                         << " " << _square_map[squared_line + 0][5] << " ║"
                         // square 2, line 2
                         << " " << _square_map[squared_line + 1][3] << " │"
                         << " " << _square_map[squared_line + 1][4] << " |"
                         << " " << _square_map[squared_line + 1][5] << " ║"
                         // square 3, line 2
                         << " " << _square_map[squared_line + 2][3] << " │"
                         << " " << _square_map[squared_line + 2][4] << " |"
                         << " " << _square_map[squared_line + 2][5] << " ║"
                    ;
            break;

        case 3:
            StringStream << "╟───┼───┼───╫───┼───┼───╫───┼───┼───╢\n"
                         // square 1, line 3
                         << "║ " << _square_map[squared_line + 0][6] << " │"
                         << " " << _square_map[squared_line + 0][7] << " |"
                         << " " << _square_map[squared_line + 0][8] << " ║"
                         // square 2, line 3
                         << " " << _square_map[squared_line + 1][6] << " │"
                         << " " << _square_map[squared_line + 1][7] << " |"
                         << " " << _square_map[squared_line + 1][8] << " ║"
                         // square 3, line 3
                         << " " << _square_map[squared_line + 2][6] << " │"
                         << " " << _square_map[squared_line + 2][7] << " |"
                         << " " << _square_map[squared_line + 2][8] << " ║\n";
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


#endif //SUDOKU_SUDOKU_MAP_H
