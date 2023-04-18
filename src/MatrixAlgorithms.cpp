#include "Matrix.hpp"

template<typename T, typename U>
PLUDecomposition<T> Matrix<T, U>::LUDecompose() const{
    if(!isSquare()) throw MatrixNotSquared();
    const int n = numRows;
    Matrix<T> upper(*this);
    Matrix<T> lower(n);
    Matrix<T> permutation(n);
    lower.makeIdentity();
    permutation.makeIdentity();
    for (size_t i = 0; i < n; i++){
        if(upper[i][i] == 0){ // if pivot equals zero, we swap the rows
            int maxRow = static_cast<int>(i); // take initial row
            T maxValue = upper[i][i];         // take pivot's value
            for(size_t j = i + 1; j < n; j++ ){
                T val = abs(upper[j][i]);   
                if(val > maxValue){         // swap rowf if row with bigger value is found
                    maxValue = val;
                    maxRow = static_cast<int>(j);
                }
            }
            if(maxRow != i ){ // if i == maxRow don't swap.
                upper.swapRows(maxRow, i);// swap rows in upper matrix
                permutation.swapRows(maxRow, i); // swap rows in permutaion matrix
                for(size_t j = 0; j < i; j++){ // swap values(!!!) in lower matrix
                    T temp = lower[maxRow][j];
                    lower(maxRow, j) = lower[i][j];
                    lower(i, j) = temp;
                }
                    
            }
        }
        for(size_t j = i + 1; j < n; j++){
            T value = upper[j][i]/upper[i][i];
            lower(j, i) = value;
            for(size_t k = 0; k < n; k++){
                upper(j ,k) -= value*upper[i][k];
            }
        }
    }
    PLUDecomposition<T> res{permutation, lower, upper};
    return res;
}

template<typename T, typename U>
QRDecomposition<T> Matrix<T, U>::QRDecompose() const{
    Matrix<T> Q(numRows);
    Matrix<T> R(numRows, numCols);
    for(size_t i = 0; i < getNumCols(); i++){
       std::vector<T> u_i = getColumn(i);
       for(size_t j = 0; j < i && j < R.getNumRows(); j++){
            std::vector<T> e_i = Q.getColumn(j);
            T product = dotProduct(u_i, e_i);
        for(size_t k = 0; k < u_i.size(); k++)
            u_i[k] -= product * e_i[k];
        R(j, i) = product;
       }
        T norm = euclideanNorm(u_i);

       if(norm == 0) {
            Q.addColumn(i, 0);
            R.addColumn(i, 0);
            continue;
       }
        if(i < Q.getNumCols()){
            for(size_t j = 0; j < Q.getNumRows(); j++)
                Q(j, i) = u_i[j] / norm;
        }
        if(i < R.getNumRows() && i < R.getNumCols()) R(i, i) = dotProduct(Q.getColumn(i), u_i);
    }
    QRDecomposition<T> res{Q, R};
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
    PLUDecomposition<T> triple = this->LUDecompose();
    if(*this == triple.P){ // when in P=A in A=LPU we get infinite reccursion. 
        std::vector<T> diagonal = getDiagonal();
        T sum = 0;
        for(size_t i = 0; i < diagonal.size(); i++) sum += diagonal[i];
        const int numOfSwaps = diagonal.size() - sum - 1;
        return pow(-1, numOfSwaps);
    }
    return triple.L.determinant() * triple.U.determinant();
}

template<typename T, typename U>
int Matrix<T, U>::rank() const noexcept{
    Matrix<T> copy(*this);
    int rank = 0; 
    int n = numRows;
    int m = numCols;
    for (int i = 0; i < n; i++) { 
        if (rank >= m) break; 
        if(copy[rank][i] == 0){
            int swap_row = -1;
            for(int j = rank + 1; j < m; j++){
                if(copy[j][i] != 0){
                    swap_row = j;
                    break;
                }
            }
            if(swap_row != -1) copy.swapRows(rank, swap_row);
            else continue;
        }
        for (int j = rank + 1; j < m; j++) {
            double ratio = copy[j][i] / copy[rank][i];
            for (int k = 0; k < n; k++) 
                copy(j,k) -= ratio * copy[rank][k];
        }
        rank++; 
    }
    return rank;
}


template<typename T, typename U>
std::vector<T> Matrix<T, U>::solveFor(const std::vector<T> &v) const {
    if(numRows != numCols) throw MatrixNotSquared();
    PLUDecomposition<T> triple = LUDecompose();
    Matrix<T> lower = triple.L;
    Matrix<T> upper = triple.U;
    const int n = lower.getNumRows();
    std::vector<T> y(n);
    std::vector<T> x(n);
    for(size_t i = 0; i < n; i++) {
        T sum = 0;
        for(size_t j = 0; j < i; j++) 
            sum += y[j] * lower[i][j];
    
        if(lower[i][i] == 0)
            throw DeterminantIsZero();
        y[i] = (v[i] - sum)/lower[i][i];
    }
    for(int i = n - 1 ; i >= 0; i--) {
        T sum = 0;
        for(int j = n - 1; j >= i; j--) 
            sum += x[j] * upper[i][j];  
        if(upper[i][i] == 0)
            throw DeterminantIsZero();
        x[i] = (y[i] - sum)/upper[i][i];
    }
    return x;
}

template<typename T, typename U>
Matrix<T> Matrix<T, U>::inverse() const{
    if(numRows != numCols) throw MatrixNotSquared();
    PLUDecomposition<T> triple = LUDecompose();
    Matrix<T> lower = triple.L;
    Matrix<T> upper = triple.U;
    const int n = lower.getNumRows();
    Matrix<T> res(n);
    int count = 0;
    while(count != n){
        std::vector<T> y(n);
        std::vector<T> x(n);
        std::vector<T> v(n, 0);
        v[count] = 1;
        for(size_t i = 0; i < n; i++) {
            T sum = 0;
            for(size_t j = 0; j < i; j++) 
                sum += y[j] * lower[i][j];
        
            if(abs(lower[i][i]) < static_cast<T>(1e-15))
                throw DeterminantIsZero();
            y[i] = (v[i] - sum)/lower[i][i];
        }
        for(int i = n - 1 ; i >= 0; i--) {
            T sum = 0;
            for(int j = n - 1; j >= i; j--) 
                sum += x[j] * upper[i][j];  
            if(upper[i][i] < static_cast<T>(1e-15))
                throw DeterminantIsZero();
            x[i] = (y[i] - sum)/upper[i][i];
        }
        res.setColumn(count, x);
        count++;
    }
    return res;
}

template<typename T, typename U>
std::vector<T> Matrix<T, U>::eigen() const{
    Matrix<T> A(*this);
    int count = 0;
    while(count != 100){
        auto q = A.QRDecompose().Q;
        auto q_t(q);
        Matrix<T> A_K = q_t.transpose() * A * q;
        auto res = A_K - A;
        if (euclideanNorm((A_K - A).getDiagonal()) < tolerance) break;
        A = A_K;
        count++;
    }
    return A.getDiagonal();
}