#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>
#include <cmath>
#include "MatrixExceptions.hpp"

template<typename T>
class DoubleDecomposition;
template<typename T>
class TripleDecomposition;

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>, bool>>
class Matrix {
private:
        size_t numRows;
        size_t numCols;
        std::vector<std::vector<T>> M;
public:
    Matrix(const int &num);
    Matrix(const int &newNumRows, const int &newNumCols);
    template<typename V>
    Matrix(const std::vector<std::vector<V>> &v);
    template<typename V>
    Matrix(const Matrix<V> &another);
    ~Matrix();
    //getters
    size_t getNumRows() const noexcept;
    size_t getNumCols() const noexcept;
    T get(int i, int j) const;
    std::vector<std::vector<T>> getMatrix() const noexcept;
    std::vector<T> getColumn(const int &index)const;
    std::vector<T> getRow(const int &index)const;
    std::vector<T> getDiagonal() const noexcept;
    Matrix<T> getSubMatrix(const int &i1, const int &j1, const int &i2, const int &j2)const;
    //Setters
    void set(const int &i, const int &j, const T &newValue);
    //Operators
    bool operator== (const Matrix<T> &another) const noexcept;//equals
    bool operator!= (const Matrix<T> &another) const noexcept;//not equals
    Matrix<T>& operator=(const Matrix<T> &another) noexcept;//asigment
    template<typename V>
    Matrix<T> operator*(const V &scalar) const noexcept;//mupltiplication by scalar
    Matrix<T> operator/(const T &scalar) const;//division by scalar
    Matrix<T> operator-()const noexcept;//negation
    std::vector<T> operator[](const int &n) const;//index access
    T& operator()(const int &i, const int &j);//double index access
    Matrix<T> operator+ (const Matrix<T> &another) const;//sum
    Matrix<T> operator- (const Matrix<T> &another) const;//substraction
    Matrix<T> operator* (const Matrix<T> &another) const;//multiplication

    void removeColumn(const int &index);
    void removeRow(const int &index);
    template<typename V>
    void addRow(const std::vector<V> &v, const int &times = 1);
    void addRow(const int &n = 0, const int &times = 1);
    template<typename V>
    void addColumn(const std::vector<V> &v, const int &times = 1);
    void addColumn(const int &n = 0, const int &times = 1);
    void resize(const int &newNumCols, const int& newNumRows, const int &n = 0);
    void swapRows(const int &first_index, const int &second_index);
    void swapColumns(const int &first_index, const int &second_index);
    void makeIdentity() noexcept;
    void transpose() noexcept;

    bool isIdentity() const noexcept;
    bool isUpperTriangle() const noexcept;
    bool isLowerTriangle() const noexcept;
    bool isTriangle() const noexcept;

    TripleDecomposition<T> LUDecompose() const;
    T determinant() const noexcept;


    void print() const{
        for(size_t i = 0; i < numRows; i++){
            for(size_t j = 0; j< numCols; j++){
                std::cout<<M[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
    }
};

#include "MatrixOperators.cpp"
#include "MatrixAccessors.cpp"
#include "MatrixLibrary.hpp"
#include "Matrix.cpp"
#endif