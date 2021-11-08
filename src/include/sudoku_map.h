#ifndef SUDOKU_SUDOKU_MAP_H
#define SUDOKU_SUDOKU_MAP_H

#include <vector>
#include <random>

typedef std::vector < int > single_square_t;

/// a sudoku map
class sudoku_map
{
private:
    std::vector < single_square_t > square_map;

    /// generate numbers between range_from and range_to
    template<typename Type>
    Type gen_random_num(Type range_from, Type range_to)
    {
        std::random_device rand_dev;
        std::mt19937 generator(rand_dev());
        std::uniform_int_distribution<Type> distr(range_from, range_to);
        return distr(generator);
    }

    /// generate numbers, excluding numbers in the without list
    int generate_without(const std::vector < int > & without, int range_from = 1, int range_to = 9);

    /// allocate the square map, filled with 0s
    void allocate_map();

    /// print single line in single square to string stream
    /** @param square square line number (ranging from 1 to 3)
     *  @param line line number (ranging from 1 to 3)
     *  @param StringStream target string stream
     *  @return target string stream **/
    std::stringstream & print_line(int squared_line, int line, std::stringstream & StringStream) const;

public:
    void generate_new_map();
    [[nodiscard]] std::vector < single_square_t > get_map() const { return square_map; }
    [[nodiscard]] std::string print_map() const;
};


#endif //SUDOKU_SUDOKU_MAP_H
