TEST_F(MatrixTest, MatrixEqual){
    Matrix<float> m1(v1);
    Matrix<float> m1_copy(v1);
    Matrix<float> m2(v2);
    EXPECT_TRUE(m1 == m1_copy);
    EXPECT_TRUE(m1 == m1);
    EXPECT_TRUE(m1 != m2);
    EXPECT_FALSE(m1 != m1_copy);
    Matrix<float> m3 = m1;
    EXPECT_EQ(m3, m1);
}

TEST_F(MatrixTest, MatrixOperationsScalar){
    Matrix<float> m1(v1);
    Matrix<float> m2(v2);
    std::vector<std::vector<float>> v_expected = {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};
    EXPECT_EQ((m1 * 2).getMatrix(), v_expected);    
    EXPECT_EQ((2 * m1).getMatrix(), v_expected);
    EXPECT_EQ(m1 / (-1), m2);
    EXPECT_THROW(m1 / 0, MatrixDivisionZero);
}

TEST_F(MatrixTest, MatrixNegation){
    Matrix<float> m1(v1);
    Matrix<float> m2(v2);
    EXPECT_EQ(-m1, m2);
}
TEST_F(MatrixTest, MatrixIndexOperators){
    Matrix<float> m1(v1);
    Matrix<float> m2(v2);
    EXPECT_EQ(m1[0], v1[0]);
    EXPECT_EQ(m2[1], v2[1]);
    EXPECT_EQ(m1(1,1), v1[1][1]);
    EXPECT_EQ(m2(1,2), v2[1][2]);
}

TEST_F(MatrixTest, MatrixAddition){
    Matrix<float> m1(v1);
    Matrix<float> m2(v2);
    auto result = m1 + m2;//result
    EXPECT_EQ(result.getNumRows(), v1.size());
    EXPECT_EQ(result.getNumCols(), v1[0].size());
    for(int i = 0; i < v1.size(); i++){
        for(int j = 0; j < v1[0].size(); j++){
            EXPECT_EQ(result[i][j], v1[i][j] + v2[i][j]);
        }
    }
}

TEST_F(MatrixTest, MatrixSubtraction){
    Matrix<float> m1(v1);
    Matrix<float> m2(v2);
    auto result = m1 - m2;//result
    EXPECT_EQ(result.getNumRows(), v1.size());
    EXPECT_EQ(result.getNumCols(), v1[0].size());
    for(int i = 0; i < v1.size(); i++){
        for(int j = 0; j < v1[0].size(); j++){
            EXPECT_EQ(result[i][j], v1[i][j] - v2[i][j]);
        }
    }
}
TEST_F(MatrixTest, MatrixMultiplication){
    Matrix<float> m1(v1);
    Matrix<float> m2(v2);
    auto result = m1 * m2;//result
    EXPECT_EQ(result.getNumRows(), v1.size());
    EXPECT_EQ(result.getNumCols(), v2[0].size());

    EXPECT_EQ(result[0][0], -30);
    EXPECT_EQ(result[0][1], -36);
    EXPECT_EQ(result[0][2], -42);
    EXPECT_EQ(result[1][0], -66);
    EXPECT_EQ(result[1][1], -81);
    EXPECT_EQ(result[1][2], -96);
    EXPECT_EQ(result[2][0], -102);
    EXPECT_EQ(result[2][1], -126);
    EXPECT_EQ(result[2][2], -150);

    std::vector<std::vector<float>> u = {{0,1}, {0,2}};
    Matrix<float> m3(u);
    EXPECT_THROW(m3* m1, MatrixSizeMismatchException);
}