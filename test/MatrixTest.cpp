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
    Matrix<double> m1(v1), m2(v2), m3(v3), m4(v4), m5(v5), m6(v6), m7(v7);
    TripleDecomposition<double> triple1 = m1.LUDecompose();
    TripleDecomposition<double> triple2 = m2.LUDecompose();
    TripleDecomposition<double> triple3 = m3.LUDecompose();
    TripleDecomposition<double> triple4 = m4.LUDecompose();
    TripleDecomposition<double> triple5 = m5.LUDecompose();
    TripleDecomposition<double> triple6 = m6.LUDecompose();
    TripleDecomposition<double> triple7 = m7.LUDecompose();
    auto res1 = triple1.first * triple1.middle * triple1.second;
    auto res2 = triple2.first * triple2.middle * triple2.second;
    auto res3 = triple3.first * triple3.middle * triple3.second;
    auto res4 = triple4.first * triple4.middle * triple4.second;
    auto res5 = triple5.first * triple5.middle * triple5.second;
    auto res6 = triple6.first * triple6.middle * triple6.second;
    auto res7 = triple7.first * triple7.middle * triple7.second;
    for(size_t i = 0; i < m1.getNumRows(); i++){
        for(size_t j = 0; j < m1.getNumCols(); j++){
            ASSERT_DOUBLE_EQ(m1[i][j], res1[i][j]);
            ASSERT_DOUBLE_EQ(m2[i][j], res2[i][j]);
            ASSERT_DOUBLE_EQ(m3[i][j], res3[i][j]);
            ASSERT_DOUBLE_EQ(m4[i][j], res4[i][j]);
            ASSERT_DOUBLE_EQ(m5[i][j], res5[i][j]);
            ASSERT_DOUBLE_EQ(m6[i][j], res6[i][j]);
            ASSERT_DOUBLE_EQ(m7[i][j], res7[i][j]);
        }

        
    }
    m7.resize(3,4);
    EXPECT_THROW(m7.LUDecompose(), MatrixNotSquared);
}


TEST_F(MatrixTest, MatrixisIdentity){
    Matrix<float> m1(5);
    Matrix<float> m2(10);
    m1.makeIdentity();
    EXPECT_TRUE(m1.isIdentity());
    EXPECT_FALSE(m2.isIdentity());
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
    ASSERT_DOUBLE_EQ(m1.determinant(), 0);
    ASSERT_DOUBLE_EQ(m2.determinant(), 0);
    ASSERT_DOUBLE_EQ(m3.determinant(), -270);
    ASSERT_DOUBLE_EQ(m4.determinant(), 0);
    ASSERT_DOUBLE_EQ(m5.determinant(), 5824);
    ASSERT_DOUBLE_EQ(m6.determinant(), -1);
    ASSERT_DOUBLE_EQ(m7.determinant(), -1);
}
#endif