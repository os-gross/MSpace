#include "Matrix.hpp"
//equals
template<typename T, typename U>
bool Matrix<T, U>::operator== (const Matrix<T> &another) const noexcept{
    return M == another.getMatrix();
}
//not equals
template<typename T, typename U>
bool Matrix<T, U>::operator!= (const Matrix<T> &another) const noexcept{
    return M != another.getMatrix();
}
//assignment
template<typename T, typename U>
Matrix<T, U>& Matrix<T, U>::operator= (const Matrix<T> &another) noexcept{
    if(another != *this){
        numRows = another.numRows;
        numCols = another.numCols;
        M = another.getMatrix();
    }
    return *this;
}
//multiplication by scalar M * n
template<typename T, typename U>
template<typename V>
Matrix<T> Matrix<T, U>::operator*(const V &scalar) const noexcept{
    Matrix<T> res(numRows, numCols);

    for(size_t j = 0; j < numRows; j++){
        for(size_t i = 0; i < numCols; i++){
            res.set(i, j, M[i][j] * static_cast<T>(scalar));
        }
    }

    return res;
}
//multiplication by scalar n * M
template<typename V, typename T>
Matrix<T> operator*(const V& scalar, const Matrix<T>& matrix) noexcept{
    return matrix * scalar;
}
//division by scalar
template<typename T, typename U>
Matrix<T> Matrix<T, U>::operator/(const T &scalar) const{
    if(scalar == 0) throw MatrixDivisionZero();
    Matrix<T> res(numRows, numCols);
    for(size_t j = 0; j < numRows; j++){
        for(size_t i = 0; i < numCols; i++){
            res.set(i, j, M[i][j] / static_cast<T>(scalar));
        }
    }
    return res;
}
//negation
template<typename T, typename U>
Matrix<T> Matrix<T, U>::operator-()const noexcept{
    Matrix<T> res(numRows, numCols);
    for(size_t i = 0; i < numRows; i++){
        for(size_t j =0; j< numCols; j++){
            res.set(i, j, -M[i][j]);
        }
    }
    return res;
}
// index operator
template<typename T, typename U>
std::vector<T> Matrix<T, U>::operator[](const int &n) const{
    if( n < 0 || n >= numRows) throw RowIndexOutOfRange();
    return M[n];
}

template<typename T, typename U>
T& Matrix<T, U>::operator()(const int &i, const int &j){
    if(i < 0 || i >= numRows) throw RowIndexOutOfRange();
    if(j < 0 || j >= numCols) throw ColumnIndexOutOfRange();
    return M[i][j];
}
//addtion of two matrices
template<typename T, typename U>
Matrix<T> Matrix<T, U>::operator+ (const Matrix<T> &another) const{
    if(numCols != another.getNumCols() || numRows != another.getNumRows()){
        throw MatrixSizeMismatchException();
    }
    Matrix<T> res(numRows, numCols);
    for(size_t i = 0; i < numRows; i++){
        for(size_t j =0; j< numCols; j++){
            res.set(i, j, M[i][j] + another[i][j]);
        }
    }
    return res;
}
//substraction of two matrices
template<typename T, typename U>
Matrix<T> Matrix<T, U>::operator- (const Matrix<T> &another) const{
    return (*this) + (-another);
}
//multiplication of two matrices
template<typename T, typename U>
Matrix<T> Matrix<T, U>::operator* (const Matrix<T> &another) const{
    if(numCols != another.getNumRows()) throw MatrixSizeMismatchException();
    Matrix<T> res(numRows, another.getNumCols()); 
    for(size_t i = 0; i < numRows; i++){
        for(size_t j = 0; j < another.getNumCols(); j++){
            res.set(i, j, 0);
            for(size_t k = 0; k < numCols; k++ ){
                res.set(i, j, res.get(i, j) + M[i][k] * another.get(k, j));
            }
        }
    }
    return res;
}