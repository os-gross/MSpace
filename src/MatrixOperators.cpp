#ifndef M_OPERATORS_CPP
#define M_OPERATORS_CPP

#include "Matrix.hpp"
//assignment
template<typename T, typename U>
Matrix<T>& Matrix<T, U>::operator= (const Matrix<T> &another){
    if(another != this){
        numCols = another.numCols;
        numRows = another.numRows;
        M = another.getMatrix();
    };
    return *this;
}
//multiplication by scalar M * n
template<typename T, typename U>
template<typename V>
Matrix<T> Matrix<T, U>::operator*(const V &scalar) const{
    Matrix<T> res(numCols, numRows);

    for(size_t i = 0; i < numCols; i++){
        for(size_t j = 0; j< numRows; j++){
            res.set(i, j, M[i][j] * static_cast<T>(scalar));
        }
    }
    return std::move(res);
}
//multiplication by scalar n * M
template<typename V, typename T>
Matrix<T> operator*(const V& scalar, const Matrix<T>& matrix) {
    return matrix * scalar;
}
//division by scalar
template<typename T, typename U>
Matrix<T> Matrix<T, U>::operator/(const T &scalar) const{
    Matrix<T> res(numCols, numRows);

    for(size_t i = 0; i < numCols; i++){
        for(size_t j = 0; j< numRows; j++){
            res.set(i, j, M[i][j] / scalar);
        }
    }
    return std::move(res);
}
//negation
template<typename T, typename U>
Matrix<T> Matrix<T, U>::operator-()const{
    Matrix<T> res(numCols, numRows);
    for(size_t i = 0; i < numCols; i++){
        for(size_t j =0; j< numRows; j++){
            res.set(i, j, -M[i][j]);
        }
    }
    return std::move(res);
}
// index operator
template<typename T, typename U>
std::vector<T> Matrix<T, U>::operator[](const int &n) const{
    if( n < 0 || n >= numCols) throw std::out_of_range("[]. The value is out of range.");
    return M[n];
};


template<typename T, typename U>
T Matrix<T, U>::operator()(const int &i, const int &j) const{
    if(i < 0 || i >= numCols || j < 0 || j >= numRows){
         throw std::out_of_range("The value is out of range.");
         return 0;
    }
    return M[i][j];

};
//addtion of two matrices
template<typename T, typename U>
Matrix<T> Matrix<T, U>::operator+ (const Matrix<T> &another) const{
    if(numCols != another.getNumCols()) throw std::out_of_range("-----");
    if(numRows != another.getNumRows()) throw std::out_of_range("-----");

    Matrix<T> res(numCols, numRows);
    for(size_t i = 0; i < numCols; i++){
        for(size_t j =0; j< numRows; j++){
            res.set(i, j, M[i][j] + another[i][j]);
        }
    }
    return std::move(res);
};
//substraction of two matrices
template<typename T, typename U>
Matrix<T> Matrix<T, U>::operator- (const Matrix<T> &another) const{
    return (*this) + (-another);
};
//multiplication of two matrices
template<typename T, typename U>
Matrix<T> Matrix<T, U>::operator* (const Matrix<T> &another) const{
    if(numRows != another.getNumCols()) throw std::out_of_range("-----");
    Matrix<T> res(numCols, another.getNumRows()); 

    for(size_t i = 0; i < numCols; i++){
        for(size_t j = 0; j < another.getNumRows(); j++){
            res.set(i, j, 0);
            for(size_t k = 0; k < numRows; k++ ){
                res.set(i, j, res[i][j] + M[i][k] * another[k][j]);
            }
        }
    }
    return std::move(res);
};

template<typename T, typename U>
bool Matrix<T, U>::operator== (const Matrix<T> &another) const{
    return M == another.getMatrix();
};

template<typename T, typename U>
bool Matrix<T, U>::operator!= (const Matrix<T> &another) const{
    return M != another.getMatrix();
};


#endif