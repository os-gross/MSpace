#include "Matrix.hpp"

template<typename T, typename U>
Matrix<T,U>::Matrix(const int &num){
    if(num <= 0){
        throw MatrixNegativeSize();
    }
    numCols = num;
    numRows = num;
    M = std::vector<std::vector<T>>(numRows, std::vector<T>(numCols, 0));
}

template<typename T, typename U>
Matrix<T,U>::Matrix(const int &newNumRows,const int &newNumCols){
    if(newNumCols <= 0 || newNumRows <= 0){
        throw MatrixNegativeSize();
    }
    numRows = newNumRows;
    numCols = newNumCols;
    M = std::vector<std::vector<T>>(numRows, std::vector<T>(numCols, 0));
}

template<typename T, typename U>
template<typename V>
Matrix<T, U>::Matrix(const std::vector<std::vector<V>> &v){
    numRows = v.size();
    numCols = v[0].size();
    M.reserve(numCols);
    for(size_t i = 0; i < numRows; i++){
        std::vector<T> temp;
        M.reserve(numRows);
        for(size_t j = 0; j < numCols; j++){
            temp.push_back(static_cast<T>(v[i][j]));
        }
        M.push_back(temp);
    }
}

template<typename T, typename U>
template<typename V>
Matrix<T, U>::Matrix(const Matrix<V> &another) {
    numRows = another.getNumRows();
    numCols = another.getNumCols();
    M.reserve(numRows);
    for (size_t i = 0; i < numRows; i++) {
        std::vector<T> temp;
        temp.reserve(numCols);
        for (size_t j = 0; j < numCols; j++) {
            temp.push_back(static_cast<T>(another[i][j]));
        }
        M.push_back(temp);
    }
}

template<typename T, typename U>
Matrix<T, U>::Matrix(const std::string &fileName){
    
}
//Destructor
template<typename T, typename U>
Matrix<T, U>::~Matrix()= default;
// Getters
template <typename T, typename U>
size_t Matrix<T, U>::getNumRows() const noexcept {
    return numRows;
}

template <typename T, typename U>
size_t Matrix<T, U>::getNumCols() const noexcept{
    return numCols;
}

template <typename T, typename U>
T Matrix<T, U>::getTolerance() const noexcept{
    return tolerance;
}

template <typename T, typename U>
T Matrix<T, U>::get(int i, int j) const {
    if(i < 0 || i >= numRows) throw RowIndexOutOfRange();
    if(j < 0 || j >= numCols) throw ColumnIndexOutOfRange();
    return M[i][j];
}

template <typename T, typename U>
std::vector<std::vector<T>> Matrix<T, U>::getMatrix() const noexcept{
    return M;
}
template<typename T, typename U>
std::vector<T> Matrix<T,U>::getRow(const int &index)const{
    if(index < 0 || index >= numRows){
        throw RowIndexOutOfRange();    
    }
    return M[index];
}
template<typename T, typename U>
std::vector<T> Matrix<T,U>::getColumn(const int &index)const{
    if(index < 0 || index >= numCols){
        throw ColumnIndexOutOfRange();
    }
    std::vector<T> res;
    for(size_t i = 0; i < numRows; i++){
        res.push_back(M[i][index]);
    }
    return res;

}
template<typename T, typename U>
std::vector<T> Matrix<T,U>::getDiagonal()const noexcept{
    std::vector<T> res;
    size_t min = std::min(numRows, numCols);
    res.reserve(min);
    for(size_t i = 0; i < min; i++){
       res.push_back(M[i][i]);
    }
    return res;
}

template<typename T, typename U> 
Matrix<T> Matrix<T,U>::getSubMatrix(const int &i1, const int &j1,const int &i2, const int &j2 )const{
    if(i1 < 0 || i1 >= numRows) throw RowIndexOutOfRange();
    if(j1 < 0 || j1 >= numCols) throw ColumnIndexOutOfRange();
    if(i2 < 0 || i2 >= numRows)  throw RowIndexOutOfRange();
    if(j2 < 0 || j2 >= numCols) throw ColumnIndexOutOfRange();
    const int min_i = std::min(i1, i2);
    const int min_j = std::min(j1, j2);
    const int max_i = std::max(i1, i2);
    const int max_j = std::max(j1, j2);
    
    Matrix<T> res(max_i - min_i + 1, max_j - min_j + 1);
    for(size_t i = min_i; i <= max_i; i++){
        for(size_t j = min_j; j <= max_j; j++){
            res(i - min_i, j - min_j) = M[i][j];
        }
    }
    return res;
}

// Setters
template<typename T, typename U>
Matrix<T>& Matrix<T, U>::set(const int &i, const int &j, const T &newValue){
    if(i < 0 || i >= numRows) throw RowIndexOutOfRange();
    if(j < 0 || j >= numCols) throw ColumnIndexOutOfRange();
    M[i][j] = newValue;
    return *this;
}

template<typename T, typename U>
Matrix<T>& Matrix<T, U>::setRow(const int &index, const std::vector<T> &v){
    if(index < 0 || index >= numRows) throw RowIndexOutOfRange();
    if( v.size() != numCols) throw VectorSizeMissmatch();
    for(size_t i = 0; i < numCols; i++) set(index, i, v[i]);
    return *this;
}

template<typename T, typename U>
Matrix<T>& Matrix<T, U>::setColumn(const int &index, const std::vector<T> &v){
    if(index < 0 || index >= numCols) throw ColumnIndexOutOfRange();
    if(v.size() != numRows) throw VectorSizeMissmatch();
    for(size_t i = 0; i < numRows; i++) set(i, index, v[i]);
    return *this;
}

template<typename T, typename U>
Matrix<T>& Matrix<T, U>::setTolerance(const T &newTolerance){
    if(newTolerance < 0) throw NegativeTolerance();
    tolerance = newTolerance;
    return *this;
}