#ifndef M_TEST_CPP
#define M_TEST_CPP

TEST_F(MatrixTest, MatrixRemoveRow) {
    Matrix<float> m(v1);
    m.removeRow(1);
    
    EXPECT_EQ(m.getNumCols(), 3);
    EXPECT_EQ(m.getNumRows(), 2);
    EXPECT_EQ(m(0, 0), 1);
    EXPECT_EQ(m(0, 1), 2);
    EXPECT_EQ(m(0, 2), 3);
    EXPECT_EQ(m(1, 0), 7);
    EXPECT_EQ(m(1, 1), 8);
    EXPECT_EQ(m(1, 2), 9);

    EXPECT_THROW(m.removeRow(-1), RowIndexOutOfRange);
    EXPECT_THROW(m.removeRow(2), RowIndexOutOfRange);
};

TEST_F(MatrixTest, MatrixRemoveColumn) {
    Matrix<float> m(v1);
    m.removeColumn(1);

    EXPECT_EQ(m.getNumCols(), 2);
    EXPECT_EQ(m.getNumRows(), 3);
    EXPECT_EQ(m(0, 0), 1);
    EXPECT_EQ(m(0, 1), 3);
    EXPECT_EQ(m(1, 0), 4);
    EXPECT_EQ(m(1, 1), 6);
    EXPECT_EQ(m(2, 0), 7);
    EXPECT_EQ(m(2, 1), 9);

    EXPECT_THROW(m.removeColumn(-1), ColumnIndexOutOfRange);
    EXPECT_THROW(m.removeColumn(2), ColumnIndexOutOfRange);
};

TEST_F(MatrixTest, MatrixAddRowVector) {
    Matrix<float> m(v1);
    std::vector<float> v = {10, 11, 12};
    m.addRow(v, 2);
    
    EXPECT_EQ(m.getNumCols(), 3);
    EXPECT_EQ(m.getNumRows(), 5);
    EXPECT_EQ(m(3, 0), 10);
    EXPECT_EQ(m(3, 1), 11);
    EXPECT_EQ(m(3, 2), 12);
    EXPECT_EQ(m(4, 0), 10);
    EXPECT_EQ(m(4, 1), 11);
    EXPECT_EQ(m(4, 2), 12);

    EXPECT_THROW(m.addRow(v, -20), MatrixNegativeValue);
};
TEST_F(MatrixTest, MatrixAddRowNumber) {
    Matrix<float> m(v1);
    m.addRow(69, 2);
    m.addRow(72);
    
    EXPECT_EQ(m.getNumCols(), 3);
    EXPECT_EQ(m.getNumRows(), 6);
    EXPECT_EQ(m(3, 0), 69);
    EXPECT_EQ(m(3, 1), 69);
    EXPECT_EQ(m(3, 2), 69);
    EXPECT_EQ(m(4, 0), 69);
    EXPECT_EQ(m(4, 1), 69);
    EXPECT_EQ(m(4, 2), 69);
    EXPECT_EQ(m(5, 0), 72);
    EXPECT_EQ(m(5, 1), 72);
    EXPECT_EQ(m(5, 2), 72);

    EXPECT_THROW(m.addRow(5, -20), MatrixNegativeValue);
};
TEST_F(MatrixTest, MatrixAddColumnVector) {
    Matrix<float> m(v1);
    std::vector<float> v = {10, 11, 12};
    m.addColumn(v, 2);

    EXPECT_EQ(m.getNumCols(), 5);
    EXPECT_EQ(m.getNumRows(), 3);
    EXPECT_EQ(m(0, 3), 10);
    EXPECT_EQ(m(0, 4), 10);
    EXPECT_EQ(m(1, 3), 11);
    EXPECT_EQ(m(1, 4), 11);
    EXPECT_EQ(m(2, 3), 12);
    EXPECT_EQ(m(2, 4), 12);

    EXPECT_THROW(m.addColumn(v, -20), MatrixNegativeValue);
};
TEST_F(MatrixTest, MatrixAddColumnNumber) {
    Matrix<float> m(v1);
    m.addColumn(69, 2);
    m.addColumn(72);

    EXPECT_EQ(m.getNumCols(), 6);
    EXPECT_EQ(m.getNumRows(), 3);
    EXPECT_EQ(m(0, 3), 69);
    EXPECT_EQ(m(0, 4), 69);
    EXPECT_EQ(m(0, 5), 72);
    EXPECT_EQ(m(1, 3), 69);
    EXPECT_EQ(m(1, 4), 69);
    EXPECT_EQ(m(1, 5), 72);
    EXPECT_EQ(m(2, 3), 69);
    EXPECT_EQ(m(2, 4), 69);
    EXPECT_EQ(m(2, 5), 72);

    EXPECT_THROW(m.addColumn(5, -20), MatrixNegativeValue);
};

TEST_F(MatrixTest, MatrixResize) {
    Matrix<float> m(v1);
    m.resize(2, 4, 1);

    EXPECT_EQ(m.getNumRows(), 2);
    EXPECT_EQ(m.getNumCols(), 4);
    EXPECT_EQ(m(0, 0), 1);
    EXPECT_EQ(m(0, 1), 2);
    EXPECT_EQ(m(0, 2), 3);
    EXPECT_EQ(m(0, 3), 1);
    EXPECT_EQ(m(1, 0), 4);
    EXPECT_EQ(m(1, 1), 5);
    EXPECT_EQ(m(1, 2), 6);
    EXPECT_EQ(m(1, 3), 1);

    m.resize(0, 0);
    EXPECT_EQ(m.getNumRows(), 0);
    EXPECT_EQ(m.getNumCols(), 0);

    m.resize(1, 0, 9);

    EXPECT_EQ(m.getNumRows(), 0);
    EXPECT_EQ(m.getNumCols(), 0);

    EXPECT_THROW(m.resize(-1, 2, 0), MatrixNegativeSize);
    EXPECT_THROW(m.resize(2, -1, 0), MatrixNegativeSize);
};
TEST_F(MatrixTest, MatrixSwapRows){
    Matrix<float> m(v1);
    m.swapRows(1,2);

    EXPECT_EQ(m(1, 0), 7);
    EXPECT_EQ(m(1, 1), 8);
    EXPECT_EQ(m(1, 2), 9);
    EXPECT_EQ(m(2, 0), 4);
    EXPECT_EQ(m(2, 1), 5);
    EXPECT_EQ(m(2, 2), 6);

    EXPECT_THROW(m.swapRows(-2, 2), RowIndexOutOfRange);
    EXPECT_THROW(m.swapRows(100, 2), RowIndexOutOfRange);
}
TEST_F(MatrixTest, MatrixSwapColumns){
    Matrix<float> m(v1);
    m.swapColumns(1,2);
    
    EXPECT_EQ(m(0, 1), 3);
    EXPECT_EQ(m(1, 1), 6);
    EXPECT_EQ(m(2, 1), 9);
    EXPECT_EQ(m(0, 2), 2);
    EXPECT_EQ(m(1, 2), 5);
    EXPECT_EQ(m(2, 2), 8);

    EXPECT_THROW(m.swapColumns(-2, 2), ColumnIndexOutOfRange);
    EXPECT_THROW(m.swapColumns(100, 2), ColumnIndexOutOfRange);
}

TEST_F(MatrixTest, MatrixLUDecomposition){
    const int count = 1000;
    const int dimension = 5;
    srand(time(NULL));
    for(int k = 0; k < count; k++ ){
        std::vector<std::vector<double>> v;
        for(int i = 0; i < dimension; i++){
            std::vector<double> temp;
            for(int j = 0; j < dimension; j++){
                temp.push_back(rand() % 10000 - 5000);
            }
            v.push_back(temp);
        }
        Matrix<double> m(v);
        auto triple = m.LUDecompose();
        auto res = triple.middle * triple.first * triple.second;
        for(size_t i = 0; i < m.getNumRows(); i++){
            for(size_t j = 0; j < m.getNumCols(); j++){
                ASSERT_NEAR(m[i][j], res[i][j], 1e-9);
            }
        }
    }
}


TEST_F(MatrixTest, MatrixisIdentity){
    Matrix<float> m1(5);
    Matrix<float> m2(10);
    m1.makeIdentity();
    EXPECT_TRUE(m1.isIdentity());
    EXPECT_FALSE(m2.isIdentity());
}

float square(float number){
    return number * number;
}
TEST_F(MatrixTest, MatrixisApplyFunction){
    Matrix<float> m(v1);
    m.applyFunction(square);
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][1], 4);
    EXPECT_EQ(m[0][2], 9);
    EXPECT_EQ(m[1][0], 16);
    EXPECT_EQ(m[1][1], 25);
    EXPECT_EQ(m[1][2], 36);
    EXPECT_EQ(m[2][0], 49);
    EXPECT_EQ(m[2][1], 64);
    EXPECT_EQ(m[2][2], 81);
}

TEST_F(MatrixTest, MatrixisTriangle){
    Matrix<float> m1(v1);
    auto res = m1.LUDecompose();
    EXPECT_TRUE(res.first.isLowerTriangle());
    EXPECT_FALSE(res.first.isUpperTriangle());
    EXPECT_TRUE(res.first.isTriangle());
    EXPECT_FALSE(res.second.isLowerTriangle());
    EXPECT_TRUE(res.second.isUpperTriangle());
    EXPECT_TRUE(res.second.isTriangle());
}

TEST_F(MatrixTest, MatrixDetermiannt){
    Matrix<double> m1(v1), m2(v2), m3(v3), m4(v4), m5(v5), m6(v6), m7(v7);
    EXPECT_NEAR(m1.determinant(), 0, 1e-9);
    EXPECT_NEAR(m2.determinant(), 0, 1e-9);
    EXPECT_NEAR(m3.determinant(), -270, 1e-9);
    EXPECT_NEAR(m4.determinant(), 0, 1e-9);
    EXPECT_NEAR(m5.determinant(), 5824, 1e-9);
    EXPECT_NEAR(m6.determinant(), -1, 1e-9);
    EXPECT_NEAR(m7.determinant(), -1, 1e-9);
}
TEST_F(MatrixTest, MatrixSolveFor){
    Matrix<double> m1(v1), m2(v2), m3(v3), m4(v4), m5(v5), m6(v6), m7(v7);
    std::vector<double> v = {1, 0, 0};
    EXPECT_THROW(m1.solveFor(v), DeterminantIsZero);
    EXPECT_THROW(m2.solveFor(v), DeterminantIsZero);
    auto res3 = m3.solveFor(v);
    EXPECT_DOUBLE_EQ(res3[0], -2);
    EXPECT_NEAR(res3[1], 1.5, 1e-9);
    EXPECT_NEAR(res3[2], 0, 1e-9);
    EXPECT_THROW(m4.solveFor(v), DeterminantIsZero);
    auto res5 = m5.solveFor(v);
    EXPECT_NEAR(res5[0], 0.0178571429, 1e-9);
    EXPECT_NEAR(res5[1], 0.0552884615, 1e-9);
    EXPECT_NEAR(res5[2], 0.1040521978, 1e-9);
    auto res6 = m6.solveFor(v);
    EXPECT_NEAR(res6[0], 1, 1e-9);
    EXPECT_NEAR(res6[1], 0, 1e-9);
    EXPECT_NEAR(res6[2], 0, 1e-9);
    auto res7 = m7.solveFor(v);
    EXPECT_NEAR(res7[0], -1, 1e-9);
    EXPECT_NEAR(res7[1], 0, 1e-9);
    EXPECT_NEAR(res7[2], 0, 1e-9);
}
TEST_F(MatrixTest, MatrixInverse){
    const int count = 1'000;
    const int dimension = 10;
    const int range = 1000;
    const int shift = 500;
    srand(time(NULL));
    for(int k = 0; k < count; k++ ){
        std::vector<std::vector<double>> v;
        for(int i = 0; i < dimension; i++){ 
            std::vector<double> temp;
            for(int j = 0; j < dimension; j++){
                temp.push_back(rand() % range - shift);
            }
            v.push_back(temp);
        }
        Matrix<double> m(v);
        Matrix<double> identity(dimension);
        identity.makeIdentity();
        Matrix<double> inverse(dimension);

        bool exceptionCaugth = false;
        try{
            inverse = m.inverse();
        } catch(DeterminantIsZero){
            exceptionCaugth = true;
        }
        if(exceptionCaugth) continue;

        auto res = m * inverse;
        for(size_t i = 0; i < m.getNumRows(); i++){
            for(size_t j = 0; j < m.getNumCols(); j++){
                ASSERT_NEAR(res[i][j], identity[i][j], 1e-9);
            }
        }
    }
}



#endif