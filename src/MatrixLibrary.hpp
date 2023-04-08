#ifndef M_ADDONS_CPP
#define M_ADDONS_CPP
#include "Matrix.hpp"

template<typename T>
class DoubleDecomposition{
public:
    Matrix<T> first;
    Matrix<T> second;
    DoubleDecomposition(const Matrix<T> &m1, const Matrix<T> &m2):first{m1}, second{m2}{};
};
template<typename T>
class TripleDecomposition{
public:
    Matrix<T> first;
    Matrix<T> middle;
    Matrix<T> second;
    TripleDecomposition(const Matrix<T> &m1, const Matrix<T> &m2, const Matrix<T> &m3):
    first{m1},middle{m2}, second{m3}{};
};

#endif