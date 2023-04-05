#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>, bool>>
class Matrix {
private:
        size_t numCols;
        size_t numRows;

        std::vector<std::vector<double>> M;    
public:
    Matrix();
    Matrix(const size_t num);
    Matrix(const size_t newNumCols, const size_t newNumRows);
    Matrix(const std::vector<std::vector<T>> &v);
    Matrix(const Matrix<T> &another);
    ~Matrix();
    //getters
    size_t getNumCols() const;
    size_t getNumRows() const;
    T get(int i, int j) const;
    std::vector<std::vector<T>> getMatrix() const;
    
    void set(const int i, const int j, const T newValue);

    void print(void) const{
        std::cout<<"--------------"<<std::endl;
        for(size_t i = 0; i < numCols; i++){
            for(size_t j = 0; j< numRows; j++){
                std::cout<<M[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
        std::cout<<"--------------"<<std::endl;
    }

    //Operators
    Matrix<T>& operator=(const Matrix<T> &another);//asigment
    template<typename V>
    Matrix<T> operator*(const V &scalar) const;//mupltiplication by scalar
    Matrix<T> operator/(const T &scalar) const;//division by scalar
    Matrix<T> operator-()const;                 //negation
    std::vector<T> operator[](const int &n) const;//index access
    T operator()(const int &i, const int &j) const;//double index access
    Matrix<T> operator+ (const Matrix<T> &another) const;//sum
    Matrix<T> operator- (const Matrix<T> &another) const;//substraction
    Matrix<T> operator* (const Matrix<T> &another) const;//multiplication
    bool operator== (const Matrix<T> &another) const;//equals
    bool operator!= (const Matrix<T> &another) const;//not equals

    template<typename U>
    operator Matrix<U>()const;
};

#include "MatrixConstructor.cpp"
#include "MatrixOperators.cpp"
#include "MatrixGetters.cpp"
#include "MatrixSetters.cpp"

