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
    const int dimension = 5;
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


TEST_F(MatrixTest, MatrixQRDecomposition){
    const int count = 1'000;
    const int dimension = 5;
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
        Matrix<double> Q(dimension);
        Matrix<double> R(dimension);

        bool exceptionCaugth = false;
        try{
            auto result = m.QRDecompose();
            Q = result.first;
            R = result.second;
        } catch(DeterminantIsZero){
            exceptionCaugth = true;
        }
        if(exceptionCaugth) continue;
        auto res = Q*R;
        for(size_t i = 0; i < m.getNumRows(); i++){
            for(size_t j = 0; j < m.getNumCols(); j++){
                ASSERT_NEAR(res[i][j], m[i][j], 1e-9);
            }
        }
    }
}
