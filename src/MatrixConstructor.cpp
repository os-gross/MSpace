#ifndef M_CONSTUCTORS_CPP
#define M_CONSTUCTORS_CPP

#include "Matrix.hpp"

#include <stdexcept>

template<typename T, typename U>
Matrix<T,U>::Matrix(const int num){
    if(num <= 0){
        throw std::out_of_range("Constuctor. The value is out of range.");
    }
    numCols = num;
    numRows = num;
    M = std::vector<std::vector<T>>(numCols, std::vector<T>(numRows, 0));
    for(size_t i = 0; i < numCols; i++) M[i][i] = 1;
}

template<typename T, typename U>
Matrix<T,U>::Matrix(const int newNumCols,const int newNumRows){
    if(newNumCols <= 0 || newNumRows <= 0){
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
template<typename V>
Matrix<T, U>::Matrix(const std::vector<std::vector<V>> &v){
    numCols = v[0].size();
    numRows = v.size();
    
    for(size_t i = 0; i < numRows; i++){
        std::vector<T> temp;
        for(size_t j = 0; j < numCols; j++){
            temp.push_back(static_cast<T>(v[i][j]));
        }
        M.push_back(temp);
    }
}

template<typename T, typename U>
template<typename V>
Matrix<T, U>::Matrix(const Matrix<V> &another){
    numCols = another.getNumCols();
    numRows = another.getNumRows();
    for(size_t i = 0; i < numCols; i++){
        std::vector<T> temp;    
        for(size_t j = 0; j < numRows; j++){
            temp.push_back(static_cast<T>(another[i][j]));
        }
        M.push_back(temp);
    }
}
//Destructor
template<typename T, typename U>
Matrix<T, U>::~Matrix(){
    //initially empty
};
#endif