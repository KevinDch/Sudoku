/** @file
 *
 * This file implements error class and relevant operations
 */

#include <sudoku_error.h>

const char *sudoku_error::what() const noexcept
{
    switch (error_code)
    {
        case SUDOKU_UNKNOWN_ERROR:
            return SUDOKU_ERROR_PREFIX "Unknown error";

//        default:
//            return SUDOKU_ERROR_PREFIX "Unknown error";
    }
}

