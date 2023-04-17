#ifndef M_ADDONS_CPP
#define M_ADDONS_CPP
#include "Matrix.hpp"

template<typename T>
class QRDecomposition{
public:
    Matrix<T> Q;
    Matrix<T> R;
    QRDecomposition(const Matrix<T> &m1, const Matrix<T> &m2):Q{m1}, R{m2}{};
};
template<typename T>
class PLUDecomposition{
public:
    Matrix<T> P;
    Matrix<T> L;
    Matrix<T> U;
    PLUDecomposition(const Matrix<T> &m1, const Matrix<T> &m2, const Matrix<T> &m3):
    P{m1},L{m2},U{m3}{};
};

#endif