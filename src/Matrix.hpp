#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include "MatrixExceptions.hpp"

template<typename T>
class QRDecomposition;
template<typename T>
class PLUDecomposition;

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>, bool>>
class Matrix {
private:
        size_t numRows;
        size_t numCols;
        std::vector<std::vector<T>> M;

        T tolerance = static_cast<T>(1e-9);
public:
    explicit Matrix(const int &num);
    Matrix(const int &newNumRows, const int &newNumCols);
    template<typename V>
    explicit Matrix(const std::vector<std::vector<V>> &v);
    template<typename V>
    explicit Matrix(const Matrix<V> &another);
    ~Matrix();
    Matrix(const std::string &fileName);
    //getters
    [[nodiscard]] size_t getNumRows() const noexcept;
    [[nodiscard]] size_t getNumCols() const noexcept;
    [[nodiscard]] T getTolerance() const noexcept;
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
    Matrix<T>& setTolerance(const T &newtolerance);
    //Operators
    bool operator==(const Matrix<T> &another) const noexcept;//equals
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
    Matrix<T>& power(int n);

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

    void saveInFile(const std::string &fileName) const;

    [[nodiscard]] T frobeniusNorm() const noexcept;
    [[nodiscard]] T spectralNorm() const noexcept;
    [[nodiscard]] T L1Norm() const noexcept;
    [[nodiscard]] T infinityNorm() const noexcept;
    [[nodiscard]] T L2_1Norm() const noexcept;

    [[nodiscard]] PLUDecomposition<T> LUDecompose() const;
    [[nodiscard]] QRDecomposition<T> QRDecompose() const;
    [[nodiscard]] T determinant() const noexcept;
    [[nodiscard]] int rank() const noexcept;
    [[nodiscard]] std::vector<T> solveFor(const std::vector<T> &v) const;
    [[nodiscard]] Matrix<T> inverse() const;
    [[nodiscard]] std::vector<T> eigen() const;

    void print(){
        for(const auto &row: M){
            for(const auto &value:row)
                std::cout<<value<<" ";
            std::cout<<'\n';
        }
    }
};

#include "MatrixLibrary.hpp"
#endif