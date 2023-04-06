#ifndef M_ACCESSORS_CPP
#define M_ACCESSORS_CPP

#include "Matrix.hpp"

#include <stdexcept>

template<typename T, typename U>
Matrix<T,U>::Matrix(const int &num){
    if(num <= 0){
        throw std::out_of_range("Constuctor. The value is out of range.");
    }
    numCols = num;
    numRows = num;
    M = std::vector<std::vector<T>>(numCols, std::vector<T>(numRows, 0));
    for(size_t i = 0; i < numCols; i++) M[i][i] = 1;
}

template<typename T, typename U>
Matrix<T,U>::Matrix(const int &newNumCols,const int &newNumRows){
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
    M.reserve(numCols);
    for(size_t i = 0; i < numRows; i++){
        std::vector<T> temp;
        M.reserve(numRows);
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
    M.reserve(numCols);
    for(size_t i = 0; i < numCols; i++){
        std::vector<T> temp;    
        temp.reserve(numRows);
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
// Getters
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
        throw std::out_of_range("The value is out of range.");
    }
    return M[i][j];
}

template <typename T, typename U>
std::vector<std::vector<T>> Matrix<T, U>::getMatrix() const{
    return M;
}

template<typename T, typename U>
std::vector<T> Matrix<T,U>::getColumn(const int &index)const{
    if(index < 0 || index >= numCols){
        throw std::out_of_range("The value is out of range.");
    }
    std::vector<T> res;
    for(size_t i = 0; i < numRows; i++){
        res.push_back(M[i][index]);
    }
    return std::move(res);
}

template<typename T, typename U>
std::vector<T> Matrix<T,U>::getRow(const int &index)const{
    if(index < 0 || index >= numRows){
        throw std::out_of_range("The value is out of range.");
    }
    return M[index];
}

template<typename T, typename U> 
Matrix<T> Matrix<T,U>::getSubMatrix(const int &i1, const int &j1,const int &i2, const int &j2 )const{
    if(i1 < 0 || i1 >= numCols) throw std::out_of_range("The value is out of range.");
    if(j1 < 0 || j1 >= numRows) throw std::out_of_range("The value is out of range.");
    if(i2 < 0 || i2 >= numCols) throw std::out_of_range("The value is out of range.");
    if(j2 < 0 || j2 >= numRows) throw std::out_of_range("The value is out of range.");
    const int min_i = std::min(i1, i2);
    const int min_j = std::min(j1, j2);
    const int max_i = std::max(i1, i2);
    const int max_j = std::max(j1, j2);
    
    Matrix<T> res(max_i - min_i + 1, max_j - min_j + 1);
    for(size_t i = min_i; i <= max_i; i++){
        for(size_t j = min_j; j <= max_j; j++){
            res(i - min_i, j - min_j) = M[i][j];
        }
    };
    return std::move(res);
}

// Setters
template<typename T, typename U>
void Matrix<T, U>::set(const int &i, const int &j, const T &newValue){
    if(i < 0 || j < 0 || i >= numCols || j >= numRows){
        throw std::out_of_range("Set. The value is out of range.");
    }
    M[i][j] = newValue;    
}
#endif