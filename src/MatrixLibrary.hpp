#ifndef M_ADDONS_CPP
#define M_ADDONS_CPP
#include "Matrix.hpp"

template<typename T>
class Decomposition{
public:
    Matrix<T> first;
    Matrix<T> second;
    Decomposition(const Matrix<T> &m1, const Matrix<T> &m2):first{m1}, second{m2}{};
};

#endif