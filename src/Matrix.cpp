#ifndef MATRIX_CPP
#define MATRIX_CPP
#include "Matrix.hpp"

template<typename T, typename U>
void Matrix<T, U>::removeRow(const int &index){
    if(index < 0 || index >= numRows) throw RowIndexOutOfRange();
    M.erase(M.begin() + index);
    numRows--;
}
template<typename T, typename U>
void Matrix<T, U>::removeColumn(const int &index){
    if(index < 0 || index >= numCols) throw ColumnIndexOutOfRange();
    for(size_t i = 0; i < numRows; i++) M[i].erase(M[i].begin() + index);
    numCols--;
};
template<typename T, typename U>
template<typename V>
void Matrix<T, U>::addRow(const std::vector<V> &v, const int &times){
    if(times < 0){
        throw MatrixNegativeValue();
    }
    
    numRows += times;
    M.insert(M.end(), times, v);
}
template<typename T, typename U>
void Matrix<T, U>::addRow(const int &n, const int &times){
    if(times < 0){
        throw MatrixNegativeValue();
    }
    std::vector<T> v(numCols, n);
    numRows += times;
    M.insert(M.end(), times, v);

}
template<typename T, typename U>
template<typename V>
void Matrix<T, U>::addColumn(const std::vector<V> &v, const int &times){
    if(times < 0){
        throw MatrixNegativeValue();
    }
    numCols += times;
    for(size_t i = 0; i < numRows; i++) M[i].insert(M[i].end(), times, v[i]);
}
template<typename T, typename U>
void Matrix<T, U>::addColumn(const int &n, const int &times){
    if(times < 0){
        throw MatrixNegativeValue();
    }

    numCols += times;
    for(size_t i = 0; i < numRows; i++) M[i].insert(M[i].end(), times, n);
}

template<typename T, typename U>
void Matrix<T, U>::resize(const int &newNumRows, const int& newNumCols, const int &n){
    if(newNumCols < 0 || newNumRows < 0 ) throw MatrixNegativeSize();
    if(newNumCols == 0 || newNumRows == 0) {
        numCols = 0;
        numRows = 0;
        M.clear();
        return;
    }   
    std::vector<std::vector<T>> newM(newNumRows, std::vector<T>(newNumCols, n));

    size_t min_i = numRows < newNumRows? numRows : newNumRows; 
    size_t min_j = numCols < newNumCols? numCols : newNumCols; 

    for(size_t i = 0; i < min_i; i++){
        for(size_t j = 0; j < min_j; j++){
            newM[i][j] = M[i][j];
        }
    }
    numRows = newNumRows;
    numCols = newNumCols;
    M = newM;
}
template<typename T, typename U>
void Matrix<T, U>::swapRows( const int &first_index,  const int &second_index) {
    if(first_index < 0 || first_index >= numRows) throw RowIndexOutOfRange();
    if(second_index < 0 || second_index >= numRows) throw RowIndexOutOfRange();
    std::swap(M[first_index], M[second_index]);
}

template<typename T, typename U>
void Matrix<T, U>::swapColumns(const int &first_index, const int &second_index){
    if(first_index < 0 || first_index >= numCols) throw ColumnIndexOutOfRange();
    if(second_index < 0 || second_index >= numCols) throw ColumnIndexOutOfRange();
    for(size_t i = 0; i < numRows; i++)
        std::swap(M[i][first_index], M[i][second_index]);
}
template<typename T, typename U>
void Matrix<T, U>::makeIdentity() noexcept {
    for(size_t i = 0; i < numRows; i++){
        for(size_t j = 0; j < numCols; j++) 
            if(i == j) M[i][j] = 1;
            else M[i][j] = 0;
    }
}

template<typename T, typename U>
void Matrix<T, U>::transpose() noexcept{
    Matrix<T> temp(numCols, numRows);
    for(size_t i = 0; i<numRows; i++){
        for(size_t j = 0; j < numCols; j++)
            temp(j, i) = M[i][j];
    }
    *this = temp;
}

template<typename T, typename U>
bool Matrix<T, U>::isIdentity() const noexcept{
    for(size_t i = 0; i < numRows; i++){
        if(M[i][i] != 1) return false;
        for(size_t j = 0; j < numCols; j++){
            if(i == j) continue;
            if(M[i][j] != 0) return false;
        }
    }
    return true;
}

template<typename T, typename U>
bool Matrix<T, U>::isUpperTriangle() const noexcept{
    for(size_t i = 1; i < numRows; i++){ 
        for(size_t j = 0; j < i; j++){
            if(M[i][j] != 0) return false;
        }
    }
    return true;
}

template<typename T, typename U>
bool Matrix<T, U>::isLowerTriangle() const noexcept {
    for (size_t i = 0; i < numRows; i++) {
        for (size_t j = i + 1; j < numCols; j++) 
            if (M[i][j] != 0) {
                return false; 
        }
    }
    return true;
}

template<typename T, typename U>
bool Matrix<T, U>::isTriangle() const noexcept{
    return isUpperTriangle() || isLowerTriangle();
}

template<typename T, typename U>
TripleDecomposition<T> Matrix<T, U>::LUDecompose() const{
    if(numRows != numCols) throw MatrixNotSquared();
    const int n = numRows;
    Matrix<T> upper(*this);
    Matrix<T> lower(n);
    Matrix<T> P(n);
    lower.makeIdentity();
    P.makeIdentity();
    for (size_t i = 0; i < n; i++){
        if(upper[i][i] == 0){
            int maxRow = i;
            T maxValue = upper[i][i];
            for(size_t j = i + 1; j < n; j++ ){
                T val = abs(upper[j][i]);
                if(val > maxValue){
                    maxValue = val;
                    maxRow = j;
                }
            };
            if(maxRow != i ){
                upper.swapRows(maxRow, i);
                P.swapRows(maxRow, i);
            }
        }
        for(size_t j = i + 1; j < n; j++){
            T value = upper[j][i]/upper[i][i];
            lower(j, i) = value;
            for(size_t k = 0; k < n; k++){
                upper(j ,k) = upper[j][k] - value*upper[i][k];
            }
        }
    }
    TripleDecomposition<T> res{lower, P, upper};
    return res;
}
template<typename T, typename U>
T Matrix<T, U>::determinant() const noexcept{
    if(isTriangle()){
       T sum = 1;
       for(size_t i = 0; i < numRows; i++)
            sum *= M[i][i];
       return sum;
    }
    TripleDecomposition<T> triple = this->LUDecompose();
    if(*this == triple.middle){ // when in P=A in A=LPU we get infinite reccursion. 
        std::vector<T> diagonal = getDiagonal();
        T sum = 0;
        for(size_t i = 0; i < diagonal.size(); i++) sum += diagonal[i];
        const int numOfSwaps = diagonal.size() - sum - 1;
        return pow(-1, numOfSwaps);
    }
    return triple.first.determinant() * triple.second.determinant();
}

#endif