#pragma once 

#include "Matrix.hpp"
namespace MSpace{
    template<typename T>
    Matrix<T> transpose(const Matrix<T> &M ){
        Matrix<T> res(M.getNumRows(), M.getNumCols());
        for(size_t i = 0; i < res.getNumCols(); i++){
            for(size_t j = 0; j < res.getNumRows(); j++){
                res.set(j, i, M[i][j]);
            }
        }
        return std::move(res);
    }
}
