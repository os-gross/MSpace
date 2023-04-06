#ifndef MATRIX_CPP
#define MATRIX_CPP
#include "Matrix.hpp"

template<typename T, typename U>
void Matrix<T, U>::removeColumn(const int &index){
    if(index < 0 || index >= numCols) throw std::out_of_range("The value is out of range.");
    for(size_t i = 0; i < numRows; i++) M[i].erase(index);
};
template<typename T, typename U>
void Matrix<T, U>::removeRow(const int &index){
    if(index < 0 || index >= numRows) throw std::out_of_range("The value is out of range.");
    M.erase(index);
}

#endif