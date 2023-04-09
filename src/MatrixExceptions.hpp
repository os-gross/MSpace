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
class MatrixDivisionZero : public std::exception {
public:
    const char* what() const noexcept override {
        return "Division by zero. It is impossible to divide the matrix by zero.";
    }
};
class MatrixNegativeValue : public std::exception {
public:
    const char* what() const noexcept override {
        return "The provided value is negative. It is impossible to perform the action.";
    }
};

class MatrixNotSquared : public std::exception{
public:
    const char * what() const noexcept override{
        return "Impossible to perform the action. The matrix is not squared.";
    }
};
class DeterminantIsZero : public std::exception{
public:
    const char * what() const noexcept override{
        return "The determinant equals zero. This means that the matrix does not have unique solutions and an inverse.";
    }
};



#endif