#ifndef M_GETTERS_CPP
#define M_GETTERS_CPP

#include "Matrix.hpp"

#include <stdexcept>

template <typename T, typename U>
size_t Matrix<T, U>::getNumCols() const {
    return numCols;
}

template <typename T, typename U>
size_t Matrix<T, U>::getNumRows() const {
    return numRows;
}

template <typename T, typename U>
T Matrix<T, U>::get(int i, int j) const {
    if(i < 0 || j < 0 || i >= numCols || j >= numRows){
        throw std::out_of_range("Get. The value is out of range.");
    }
    return M[i][j];
}

template <typename T, typename U>
std::vector<std::vector<T>> Matrix<T, U>::getMatrix() const{
    return M;
}

#endif