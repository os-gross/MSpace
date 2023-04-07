#ifndef MATRIX_CPP
#define MATRIX_CPP
#include "Matrix.hpp"

template<typename T, typename U>
void Matrix<T, U>::removeRow(const int &index){
    if(index < 0 || index >= numRows) throw RowIndexOutOfRange();
    M.erase(M.begin() + index);
    numRows--;
}
template<typename T, typename U>
void Matrix<T, U>::removeColumn(const int &index){
    if(index < 0 || index >= numCols) throw ColumnIndexOutOfRange();
    for(size_t i = 0; i < numRows; i++) M[i].erase(M[i].begin() + index);
    numCols--;
};
template<typename T, typename U>
template<typename V>
void Matrix<T, U>::addRow(const std::vector<V> &v, const int &times){
    if(times < 0){
        throw MatrixNegativeValue();
    }
    
    numRows += times;
    M.insert(M.end(), times, v);
}
template<typename T, typename U>
void Matrix<T, U>::addRow(const int &n, const int &times){
    if(times < 0){
        throw MatrixNegativeValue();
    }
    std::vector<T> v(numCols, n);
    numRows += times;
    M.insert(M.end(), times, v);

}
template<typename T, typename U>
template<typename V>
void Matrix<T, U>::addColumn(const std::vector<V> &v, const int &times){
    if(times < 0){
        throw MatrixNegativeValue();
    }
    numCols += times;
    for(size_t i = 0; i < numRows; i++) M[i].insert(M[i].end(), times, v[i]);
}
template<typename T, typename U>
void Matrix<T, U>::addColumn(const int &n, const int &times){
    if(times < 0){
        throw MatrixNegativeValue();
    }

    numCols += times;
    for(size_t i = 0; i < numRows; i++) M[i].insert(M[i].end(), times, n);
}

template<typename T, typename U>
void Matrix<T, U>::resize(const int &newNumRows, const int& newNumCols, const int &n){
    if(newNumCols < 0 || newNumRows < 0 ) throw MatrixNegativeSize();
    if(newNumCols == 0 || newNumRows == 0) {
        numCols = 0;
        numRows = 0;
        M.clear();
        return;
    }   
    std::vector<std::vector<T>> newM(newNumRows, std::vector<T>(newNumCols, n));

    size_t min_i = numRows < newNumRows? numRows : newNumRows; 
    size_t min_j = numCols < newNumCols? numCols : newNumCols; 

    for(size_t i = 0; i < min_i; i++){
        for(size_t j = 0; j < min_j; j++){
            newM[i][j] = M[i][j];
        }
    }
    numRows = newNumRows;
    numCols = newNumCols;
    M = newM;
}
template<typename T, typename U>
void Matrix<T, U>::swapRows(const int &first_index, const int &second_index){
    if(first_index < 0 || first_index >= numRows) throw RowIndexOutOfRange();
    if(second_index < 0 || second_index >= numRows) throw RowIndexOutOfRange();
    std::swap(M[first_index], M[second_index]);
}

template<typename T, typename U>
void Matrix<T, U>::swapColumns(const int &first_index, const int &second_index){
    if(first_index < 0 || first_index >= numCols) throw ColumnIndexOutOfRange();
    if(second_index < 0 || second_index >= numCols) throw ColumnIndexOutOfRange();
    for(size_t i = 0; i < numRows; i++) 
        std::swap(M[i][first_index], M[i][second_index]);
}

#endif