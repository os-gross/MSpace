#include "Matrix.hpp"

template<typename T, typename U>
Matrix<T>& Matrix<T, U>::removeRow(const int &index){
    if(index < 0 || index >= numRows) throw RowIndexOutOfRange();
    M.erase(M.begin() + index);
    numRows--;
    return *this;
}
template<typename T, typename U>
Matrix<T>& Matrix<T, U>::removeColumn(const int &index){
    if(index < 0 || index >= numCols) throw ColumnIndexOutOfRange();
    for(size_t i = 0; i < numRows; i++) M[i].erase(M[i].begin() + index);
    numCols--;
    return *this;
}
template<typename T, typename U>
template<typename V>
Matrix<T>& Matrix<T, U>::addRow(const std::vector<V> &v, const int &times){
    if(times < 0){
        throw MatrixNegativeValue();
    }
    std::vector<T> converted(v.size());
    for(size_t i = 0; i < v.size(); i++)
        converted[i] = static_cast<T>(v[i]);
    
    numRows += times;
    M.insert(M.end(), times, converted);
    return *this;
}
template<typename T, typename U>
Matrix<T>& Matrix<T, U>::addRow(const int &n, const int &times){
    if(times < 0){
        throw MatrixNegativeValue();
    }
    std::vector<T> v(numCols, n);
    numRows += times;
    M.insert(M.end(), times, v);
    return *this;
}
template<typename T, typename U>
template<typename V>
Matrix<T>& Matrix<T, U>::addColumn(const std::vector<V> &v, const int &times){
    if(times < 0){
        throw MatrixNegativeValue();
    }
    std::vector<T> converted(v.size());
    for(size_t i = 0; i < v.size(); i++)
        converted[i] = static_cast<T>(v[i]);

    numCols += times;
    for(size_t i = 0; i < numRows; i++) M[i].insert(M[i].end(), times, converted[i]);
    return *this;
}
template<typename T, typename U>
Matrix<T>& Matrix<T, U>::addColumn(const int &n, const int &times){
    if(times < 0){
        throw MatrixNegativeValue();
    }
    numCols += times;
    for(size_t i = 0; i < numRows; i++) M[i].insert(M[i].end(), times, n);
    return *this;
}

template<typename T, typename U>
Matrix<T>& Matrix<T, U>::resize(const int &newNumRows, const int& newNumCols, const int &n){
    if(newNumCols < 0 || newNumRows < 0 ) throw MatrixNegativeSize();
    if(newNumCols == 0 || newNumRows == 0) {
        numCols = 0;
        numRows = 0;
        M.clear();
        return *this;
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
    return *this;
}
template<typename T, typename U>
Matrix<T>& Matrix<T, U>::swapRows( const int &first_index,  const int &second_index) {
    if(first_index < 0 || first_index >= numRows) throw RowIndexOutOfRange();
    if(second_index < 0 || second_index >= numRows) throw RowIndexOutOfRange();
    std::swap(M[first_index], M[second_index]);
    return *this;
}

template<typename T, typename U>
Matrix<T>& Matrix<T, U>::swapColumns(const int &first_index, const int &second_index){
    if(first_index < 0 || first_index >= numCols) throw ColumnIndexOutOfRange();
    if(second_index < 0 || second_index >= numCols) throw ColumnIndexOutOfRange();
    for(size_t i = 0; i < numRows; i++)
        std::swap(M[i][first_index], M[i][second_index]);
    return *this;
}
template<typename T, typename U>
Matrix<T>& Matrix<T, U>::applyFunction(T (*func)(T)){
    for(size_t i = 0; i < numRows; i++){
        for(size_t j =0; j < numCols; j++)
            M[i][j] = func(M[i][j]);
    }
    return *this;
}
template<typename T, typename U>
Matrix<T>& Matrix<T, U>::makeIdentity() noexcept {
    for(size_t i = 0; i < numRows; i++){
        for(size_t j = 0; j < numCols; j++) 
            if(i == j) M[i][j] = 1;
            else M[i][j] = 0;
    }
    return *this;
}

template<typename T, typename U>
Matrix<T>& Matrix<T, U>::transpose() noexcept{
    Matrix<T> temp(numCols, numRows);
    for(size_t i = 0; i<numRows; i++){
        for(size_t j = 0; j < numCols; j++)
            temp(j, i) = M[i][j];
    }
    *this = temp;
    return *this;
}

template<typename T, typename U>
Matrix<T>& Matrix<T, U>::mergeVertically(const Matrix<T> &another){
    if(numRows != another.getNumRows()) throw MatrixSizeMismatchException();
    for(size_t i = 0; i < another.getNumCols(); i++)
        addColumn(another.getColumn(i));
    return *this;
}

template<typename T, typename U>
Matrix<T>& Matrix<T, U>::mergeHorizontally(const Matrix<T> &another){
    if(numCols != another.getNumCols()) throw MatrixSizeMismatchException();
    for(size_t i = 0; i < another.getNumRows(); i++)
        addRow(another.getRow(i));
    return *this;
}


template<typename T, typename U>
bool Matrix<T, U>::isSquare() const noexcept{
    if(numRows == 0 || numCols == 0) return false;
    return numCols == numRows;
}

template<typename T, typename U>
bool Matrix<T, U>::isDiagonal() const noexcept{
    if(!isSquare()) return false;
    for(size_t i = 0; i < numRows; i++){
        for(size_t j = 0; j < numCols; j++){
            if(i == j && M[i][j] == 0) return false;
            if(i != j && M[i][j] != 0) return false;
        }
    }
    return true;
}

template<typename T, typename U>
bool Matrix<T, U>::isScalar() const noexcept{
    if(!isDiagonal()) return false;
    if(numRows == 1 && M[0][0] != 0) return true; 
    for(size_t i = 1; i < numRows; i++){
        if(M[i][i] != M[i-1][i-1]) return false;
    }
    return true;
}

template<typename T, typename U>
bool Matrix<T, U>::isZero() const noexcept{
    for(size_t i = 0; i < numRows; i++){
        for(size_t j = 0; j < numCols; j++){
            if(M[i][j] != 0) return false;
        }
    }
    return true;
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
bool Matrix<T, U>::isSymmetric() const noexcept{
    if(!isSquare()) return false;
    for(size_t i = 0; i < numRows; i++){
        for(size_t j = i; j < numCols; j++){
            if(M[i][j] != M[j][i]) return false;
        }
    }
    return true;
}

template<typename T, typename U>
bool Matrix<T, U>::isOrthogonal() const noexcept{
    if(!isSquare()) return false;
    Matrix<T> copy = *this;
    Matrix<T> identity(numRows);
    copy.transpose();
    identity.makeIdentity();
    return (copy * *this) == identity;
}