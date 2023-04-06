#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>, bool>>
class Matrix {
private:
        size_t numCols;
        size_t numRows;
        std::vector<std::vector<T>> M;    
public:
    Matrix(const int &num);
    Matrix(const int &newNumCols, const int &newNumRows);
    template<typename V>
    Matrix(const std::vector<std::vector<V>> &v);
    template<typename V>
    Matrix(const Matrix<V> &another);
    ~Matrix();
    //getters
    size_t getNumCols() const;
    size_t getNumRows() const;
    T get(int i, int j) const;
    std::vector<std::vector<T>> getMatrix() const;
    std::vector<T> getColumn(const int &index)const;
    std::vector<T> getRow(const int &index)const;
    Matrix<T> getSubMatrix(const int &i1, const int &j1, const int &i2, const int &j2)const;
    //Setters
    void set(const int &i, const int &j, const T &newValue);
    //Operators
    bool operator== (const Matrix<T> &another) const;//equals
    bool operator!= (const Matrix<T> &another) const;//not equals
    Matrix<T>& operator=(const Matrix<T> &another);//asigment
    template<typename V>
    Matrix<T> operator*(const V &scalar) const;//mupltiplication by scalar
    Matrix<T> operator/(const T &scalar) const;//division by scalar
    Matrix<T> operator-()const;//negation
    std::vector<T> operator[](const int &n) const;//index access
    T& operator()(const int &i, const int &j);//double index access
    Matrix<T> operator+ (const Matrix<T> &another) const;//sum
    Matrix<T> operator- (const Matrix<T> &another) const;//substraction
    Matrix<T> operator* (const Matrix<T> &another) const;//multiplication

    /// TODO:
    void deleteColumn() const;
    void deleteRow() const;

    void print(const std::string &caption = "") const{
        std::cout<<"--------------"<<std::endl;
        std::cout<<caption<<std::endl;
        for(size_t i = 0; i < numCols; i++){
            for(size_t j = 0; j< numRows; j++){
                std::cout<<M[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
    }
};

#include "MatrixAccessors.cpp"
#include "MatrixOperators.cpp"

