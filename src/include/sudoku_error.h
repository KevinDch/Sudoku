/** @file
 *
 * This file defines runtime error class and relevant operations
 */


#ifndef SUDOKU_SUDOKU_ERROR_H
#define SUDOKU_SUDOKU_ERROR_H

#include <exception>

#include <string>
#include <utility>
#include <cstring>

#define SUDOKU_UNKNOWN_ERROR        0xA00001    /* Unknown error */

/// Filesystem Error
class sudoku_error : public std::exception
{
private:
    unsigned int error_code;
    error_t _errno;

public:
    /// Generate a error with error code
    /** @param _code Your error code **/
    explicit sudoku_error(unsigned int _code) noexcept : error_code(_code), _errno(errno) {}

    /// Return explanation of current error
    [[nodiscard]] const char * what() const noexcept override;

    /// Return the explanation of errno snapshoted when the current error is generated
    [[nodiscard]] const char * what_errno() const noexcept { return strerror(_errno); };

    /// Return the errno snashoted when the current error is generated
    [[nodiscard]] error_t my_errno() const noexcept { return _errno; }

    /// Return the error code of current error
    [[nodiscard]] unsigned int my_errcode() const noexcept { return error_code; }
};

#endif //SUDOKU_SUDOKU_ERROR_H
