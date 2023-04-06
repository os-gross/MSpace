#ifndef M_EXCEPTIONS_CPP
#define M_EXCEPTIONS_CPP
#include <stdexcept>
#include <exception>

class MatrixNegativeSize: public std::exception{
public: 
    const char* what() const noexcept override{
            return "The provided value is not positive. Impossible to allocate memory.";
        }
};
class ColumnIndexOutOfRange: public std::exception{
public: 
    const char* what() const noexcept override{
            return "Index for the column is out range. The value must be in range [0, numCols).";
        }
};
class RowIndexOutOfRange : public std::exception {
public:
    const char* what() const noexcept override {
        return "Index for the row is out of range. The value must be in range [0, numRows).";
    }
};
class MatrixSizeMismatchException : public std::exception {
public:
    const char* what() const noexcept override {
        return "The sizes of the matrices do not match. Impossible to perform operation on matrices with different sizes.";
    }
};

#endif