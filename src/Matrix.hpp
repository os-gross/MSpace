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
    explicit Matrix(const int &num);
    Matrix(const int &newNumRows, const int &newNumCols);
    template<typename V>
    explicit Matrix(const std::vector<std::vector<V>> &v);
    template<typename V>
    explicit Matrix(const Matrix<V> &another);
    ~Matrix();
    //getters
    [[nodiscard]] size_t getNumRows() const noexcept;
    [[nodiscard]] size_t getNumCols() const noexcept;
    T get(int i, int j) const;
    std::vector<std::vector<T>> getMatrix() const noexcept;
    std::vector<T> getColumn(const int &index)const;
    std::vector<T> getRow(const int &index)const;
    std::vector<T> getDiagonal() const noexcept;
    Matrix<T> getSubMatrix(const int &i1, const int &j1, const int &i2, const int &j2)const;
    //Setters
    Matrix<T>& set(const int &i, const int &j, const T &newValue);
    Matrix<T>& setRow(const int &index, const std::vector<T> &v);
    Matrix<T>& setColumn(const int &index, const std::vector<T> &v);
    //Operators
    bool operator== (const Matrix<T> &another) const noexcept;//equals
    bool operator!= (const Matrix<T> &another) const noexcept;//not equals
    Matrix& operator=(const Matrix<T> &another) noexcept;//assignment
    template<typename V>
    Matrix<T> operator*(const V &scalar) const noexcept;//multiplication by scalar
    Matrix<T> operator/(const T &scalar) const;//division by scalar
    Matrix<T> operator-()const noexcept;//negation
    std::vector<T> operator[](const int &n) const;//index access
    T& operator()(const int &i, const int &j);//double index access
    Matrix<T> operator+ (const Matrix<T> &another) const;//sum
    Matrix<T> operator- (const Matrix<T> &another) const;//subtraction
    Matrix<T> operator* (const Matrix<T> &another) const;//multiplication

    Matrix<T>& removeRow(const int &index);
    Matrix<T>& removeColumn(const int &index);
    template<typename V>
    Matrix<T>& addRow(const std::vector<V> &v, const int &times = 1);
    Matrix<T>& addRow(const int &n = 0, const int &times = 1);
    template<typename V>
    Matrix<T>& addColumn(const std::vector<V> &v, const int &times = 1);
    Matrix<T>& addColumn(const int &n = 0, const int &times = 1);
    Matrix<T>& resize(const int &newNumRows, const int& newNumCols, const int &n = 0);
    Matrix<T>& swapRows(const int &first_index, const int &second_index);
    Matrix<T>& swapColumns(const int &first_index, const int &second_index);
    Matrix<T>& makeIdentity() noexcept;
    Matrix<T>& applyFunction(T (*func)(T));
    Matrix<T>& transpose() noexcept;
    Matrix<T>& mergeVertically(const Matrix<T> &another);
    Matrix<T>& mergeHorizontally(const Matrix<T> &another);

    [[nodiscard]] bool isSquare() const noexcept;
    [[nodiscard]] bool isDiagonal() const noexcept;
    [[nodiscard]] bool isScalar() const noexcept;
    [[nodiscard]] bool isZero() const noexcept;
    [[nodiscard]] bool isIdentity() const noexcept;
    [[nodiscard]] bool isUpperTriangle() const noexcept;
    [[nodiscard]] bool isLowerTriangle() const noexcept;
    [[nodiscard]] bool isTriangle() const noexcept;
    [[nodiscard]] bool isSymmetric() const noexcept;
    [[nodiscard]] bool isOrthogonal() const noexcept;

    TripleDecomposition<T> LUDecompose() const;
    T determinant() const noexcept;
    std::vector<T> solveFor(const std::vector<T> &v) const;
    [[nodiscard]] Matrix<T> inverse() const;

    void print() const{
        for(size_t i = 0; i < numRows; i++){
            for(size_t j = 0; j< numCols; j++){
                std::cout<<M[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
    }
};

#include "MatrixLibrary.hpp"
#endif