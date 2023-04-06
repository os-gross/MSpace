#include <gtest/gtest.h>
#include <vector>
#include "../src/MSpace.hpp"

TEST(Matrix, MatrixConstructorTest) {
  std::vector<std::vector<float>> v =
    {{1.0, 0, 5.25},
    {2.0, -10, 6.335},
    {4.22, -0.44, 2.25},
    {16, 1000e-2, 3.14} };

    EXPECT_NO_THROW(Matrix<double> squared_matrix(3);
    Matrix<double> regular_matrix(3, 4);
    regular_matrix.set(0, 2, 0.1414141);
    Matrix<float> same_type_vector_matrix(v);
    Matrix<double> float_to_double_vector_matrix(v);
    Matrix<int> float_to_int_vector_matrix(v);
    Matrix<double> same_type_copied_matrix(regular_matrix);
    Matrix<int> double_to_int_copied_matrix(regular_matrix);
    );
    EXPECT_THROW(Matrix<int> throw_matrix(-5), MatrixNegativeSize);
    EXPECT_THROW(Matrix<int> throw_matrix(-5, -10), MatrixNegativeSize);
  };

TEST(Matrix, MatrixGettersTest) {
  std::vector<std::vector<float>> v =
    {{1.0, 0, 5.25},
    {2.0, -10, 6.335},
    {4.22, -0.44, 2.25},
    {16, 1000e-2, 3.14} };
  std::vector<float> v_column_1 = {0, -10, -0.44, 1000e-2};
  std::vector<float> v_row_2 = {2.0, -10, 6.335};
  std::vector<std::vector<float>> v_sub = 
  { {2.0, -10},
    {4.22, -0.44}};
  Matrix<float> matrix(v);
  Matrix<float> sub_matrix(v_sub);
  EXPECT_EQ(matrix.getNumCols(), 3);
  EXPECT_EQ(matrix.getNumRows(), 4);
  EXPECT_EQ(matrix.getMatrix(), v);
  EXPECT_EQ(matrix.getColumn(1), v_column_1);
  EXPECT_EQ(matrix.getRow(1), v_row_2);
  EXPECT_EQ(matrix.getSubMatrix(1, 0, 2, 1), sub_matrix);
  EXPECT_EQ(matrix.getSubMatrix(2, 1, 1, 0), sub_matrix);
  EXPECT_THROW(matrix.getSubMatrix(1, 0, -2, 1), ColumnIndexOutOfRange);
  EXPECT_THROW(matrix.getSubMatrix(1, 0, 2, -1), RowIndexOutOfRange);
  EXPECT_THROW(matrix.getSubMatrix(200, 0, 2, 1), ColumnIndexOutOfRange);
}

TEST(Matrix, MatrixSettersTest){
  std::vector<std::vector<float>> v =
    {{1.0, 0, 5.25},
    {2.0, -10, 6.335},
    {4.22, -0.44, 2.25},
    {16, 1000e-2, 3.14}};
  Matrix<double> matrix(v);
}

TEST(Matrix, MatrixOperatorsTest){
    std::vector<std::vector<int>> v =
    {{1, 0 ,0, 0},
     {0, 2, 0, 0},
     {0, 0, 3, 0},
     {0, 0, 0, 4}
    };
    Matrix<int> matrix(v);
    Matrix<int> matrix_copy(v);
    Matrix<int> matrix_changed(v);
    matrix_changed.set(0, 0, 10);
    EXPECT_TRUE(matrix == matrix);// equals test
    EXPECT_TRUE(matrix == matrix_copy);
    EXPECT_TRUE(matrix != matrix_changed);// not equals test

    Matrix<int> copy = matrix;// asigment test
    EXPECT_EQ(matrix, copy); 

    int scalar = 5;
    for(size_t i = 0; i < copy.getNumCols(); i++){
        for(size_t j =0; j< copy.getNumRows(); j++ )
            copy.set(i, j, copy[i][j] * scalar);
        
    }
    EXPECT_EQ(matrix * scalar, copy);// multlication test 
    EXPECT_EQ(scalar * matrix, copy);
    EXPECT_EQ(copy / scalar, matrix);// division test
    copy = copy /scalar;

    for(size_t i = 0; i < copy.getNumCols(); i++){
        for(size_t j =0; j< copy.getNumRows(); j++ ){
            copy.set(i, j, -copy[i][j]);
        }
    }
    EXPECT_EQ(-matrix, copy);// negation test
    copy = -copy;

    EXPECT_EQ(matrix[0], v[0]);// index acess
    EXPECT_EQ(matrix(0, 0), v[0][0]);// double index access
    EXPECT_THROW(matrix[-10], RowIndexOutOfRange);
    EXPECT_THROW(matrix(-1, -1), ColumnIndexOutOfRange);
    EXPECT_THROW(matrix(1, -1), RowIndexOutOfRange);
    EXPECT_THROW(matrix(-1, 1), ColumnIndexOutOfRange);

    std::vector<std::vector<double>> v1 = {{1,2,3}, {4,5,6}, {7,8,9}};
    std::vector<std::vector<double>> v2 = {{1,0,2}, {0,3,0}, {4,0,5}};
    std::vector<std::vector<double>> v_sum = {{2,2,5}, {4,8,6}, {11,8,14}};
    std::vector<std::vector<double>> v_sub = {{0,2,1}, {4,2,6}, {3,8,4}};
    std::vector<std::vector<double>> v_mult = {{13,6,17}, {28,15,38}, {43,24,59}};

    Matrix<double> matrix_v1(v1);
    Matrix<double> matrix_v2(v2);
    Matrix<double> matrix_v_sum(v_sum);
    Matrix<double> matrix_v_sub(v_sub);
    Matrix<double> matrix_v_mult(v_mult);

    EXPECT_EQ(matrix_v1 + matrix_v2, matrix_v_sum);//addition
    EXPECT_EQ(matrix_v1 - matrix_v2, matrix_v_sub);//subtraction
    EXPECT_EQ(matrix_v1 * matrix_v2, matrix_v_mult);//multiplication

}




int main(int argc, char** argv) {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
