#ifndef M_CONSTUCTORS_CPP
#define M_CONSTUCTORS_CPP

#include "Matrix.hpp"

#include <stdexcept>

template<typename T, typename U>
Matrix<T,U>::Matrix(){
    numCols = 0;
    numRows = 0;
    M = 0;
}

template<typename T, typename U>
Matrix<T,U>::Matrix(const size_t num){
    if(num < 0){
        throw std::out_of_range("Constuctor. The value is out of range.");
    }
    numCols = num;
    numRows = num;
    M = std::vector<std::vector<T>>(numCols, std::vector<T>(numRows, 0));
    for(size_t i = 0; i < numCols; i++) M[i][i] = 1;
}

template<typename T, typename U>
Matrix<T,U>::Matrix(const size_t newNumCols,const size_t newNumRows){
    if(newNumCols < 0 || newNumRows < 0){
        throw std::out_of_range("Constructor. The value is out of range.");
    }

    numCols = newNumCols;
    numRows = newNumRows;
    M = std::vector<std::vector<T>>(numCols, std::vector<T>(numRows, 0));
    for(size_t i = 0; i < numCols; i++){
        for(size_t j = 0; j < numRows; j++){
           if(i == j) M[i][j] = 1;
        }
    }
}

template<typename T, typename U>
Matrix<T, U>::Matrix(const std::vector<std::vector<T>> &v){
    numCols = v.size();
    numRows = v[0].size();
    M = v;
}


template<typename T, typename U>
Matrix<T, U>::Matrix(const Matrix<T> &another){
    numCols = another.getNumCols();
    numRows = another.getNumRows();
    M = another.getMatrix();
}



template<typename T, typename U>
Matrix<T, U>::~Matrix(){
    //initially emptys
};


#endif