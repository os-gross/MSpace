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
    std::vector<int> v = {10, 11, 12};
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
    std::vector<int> v = {10, 11, 12};
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

TEST_F(MatrixTest, MatrixMakeIsIdentity){
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

TEST_F(MatrixTest, MatrixMerge){
    Matrix<double> m1(v1);
    Matrix<double> m2(3);
    Matrix<double> m3(v2);
    Matrix<double> m4(3);
    Matrix<double> m5(v3);
    Matrix<double> m6(4, 5);
    m2.makeIdentity();
    m4.makeIdentity();
    m1.mergeVertically(m2);
    m3.mergeHorizontally(m4);
    EXPECT_EQ(m1[0][0], 1);
    EXPECT_EQ(m1[0][1], 2);
    EXPECT_EQ(m1[0][2], 3);
    EXPECT_EQ(m1[0][3], 1);
    EXPECT_EQ(m1[0][4], 0);
    EXPECT_EQ(m1[0][5], 0);

    EXPECT_EQ(m3[0][0], -1);
    EXPECT_EQ(m3[1][0], -4);
    EXPECT_EQ(m3[2][0], -7);
    EXPECT_EQ(m3[3][0], 1);
    EXPECT_EQ(m3[4][0], 0);
    EXPECT_EQ(m3[5][0], 0);
    
    EXPECT_THROW(m5.mergeVertically(m6), MatrixSizeMismatchException);
    EXPECT_THROW(m5.mergeHorizontally(m6), MatrixSizeMismatchException);
}

TEST_F(MatrixTest, MatrixIsSquare){
    Matrix<double> m(5);
    Matrix<double> z(3, 2);
    EXPECT_TRUE(m.isSquare());
    EXPECT_FALSE(z.isSquare());
}
TEST_F(MatrixTest, MatrixIsDiagonal){
    Matrix<double> m(5);
    EXPECT_FALSE(m.isDiagonal());
    m.makeIdentity();
    EXPECT_TRUE(m.isDiagonal());
}

TEST_F(MatrixTest, MatrixIsScalar){
    Matrix<double> m(5);
    EXPECT_FALSE(m.isScalar());
    m.makeIdentity();
    EXPECT_TRUE(m.isScalar());
}
TEST_F(MatrixTest, MatrixIsZero){
    Matrix<double> m(5);
    EXPECT_TRUE(m.isZero());
    m.makeIdentity();
    EXPECT_FALSE(m.isZero());
}

TEST_F(MatrixTest, MatrixIsTriangle){
    Matrix<float> m1(v1);
    auto res = m1.LUDecompose();
    EXPECT_TRUE(res.first.isLowerTriangle());
    EXPECT_FALSE(res.first.isUpperTriangle());
    EXPECT_TRUE(res.first.isTriangle());
    EXPECT_FALSE(res.second.isLowerTriangle());
    EXPECT_TRUE(res.second.isUpperTriangle());
    EXPECT_TRUE(res.second.isTriangle());
}

TEST_F(MatrixTest, MatrixIsSymmetric){
    Matrix<double> m(5);
    m = 5 * m.makeIdentity().set(1, 2, 10).set(2,1,10);
    EXPECT_TRUE(m.isSymmetric());
    m.set(3,2, -5);
    EXPECT_FALSE(m.isSymmetric());
}
TEST_F(MatrixTest, MatrixIsOrthogonal){
    Matrix<double> m(3);
    EXPECT_FALSE(m.isOrthogonal());
    m.set(0, 0, -1).set(1,1,-1).set(2,2,-1);
    EXPECT_TRUE(m.isOrthogonal());
}

TEST_F(MatrixTest, MatrixSaveInFile){
    Matrix<double> m(3, 4);
    m.saveInFile("m.txt");
    std::ifstream file("m.txt");
    std::string str;
    while(std::getline(file, str, '\n')){
        EXPECT_EQ(str, "0,0,0,0");
    }
    file.close();
    remove("m.txt");
}

TEST_F(MatrixTest, MatrixNorms){
    Matrix<double> m(v1);
    EXPECT_NEAR(m.frobeniusNorm(),16.881943016, 1e-6 );
    // EXPECT_NEAR(m.spectralNorm(),16.881943016, 1e-6 );
    EXPECT_NEAR(m.L1Norm(),45, 1e-6);
    EXPECT_NEAR(m.infinityNorm(), 24, 1e-6);
    // EXPECT_NEAR(m.L2_1Norm(),17, 1e-6);
}
