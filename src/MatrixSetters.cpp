#ifndef M_SETTERS_CPP
#define M_SETTERS_CPP

#include "Matrix.hpp"

#include <stdexcept>

template<typename T, typename U>
void Matrix<T, U>::set(const int i, const int j, const T newValue){
    if(i < 0 || j < 0 || i >= numCols || j >= numRows){
        throw std::out_of_range("Set. The value is out of range.");
    }
    M[i][j] = newValue;    
}

#endif