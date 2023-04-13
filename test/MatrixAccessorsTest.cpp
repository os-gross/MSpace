TEST_F(MatrixTest, DefaultConstructorThrowsException){
  EXPECT_THROW(Matrix<float> (-3), MatrixNegativeSize);
  EXPECT_THROW(Matrix<float> (2, -3), MatrixNegativeSize);
  EXPECT_THROW(Matrix<float> (-3, -3), MatrixNegativeSize);
  EXPECT_THROW(Matrix<float> (-3, 2), MatrixNegativeSize);
}

TEST_F(MatrixTest, SquareMatrixConstructor) {
  Matrix<float> m(3);
  EXPECT_EQ(m.getNumRows(), 3);
  EXPECT_EQ(m.getNumCols(), 3);
  EXPECT_EQ(m.get(0, 0), 0);
  EXPECT_EQ(m.get(1, 1), 0);
  EXPECT_EQ(m.get(2, 2), 0);
}

TEST_F(MatrixTest, RectangularMatrixConstuctor){
  Matrix<float> m(2,3);
  EXPECT_EQ(m.getNumRows(), 2);
  EXPECT_EQ(m.getNumCols(), 3);
  EXPECT_EQ(m.get(0, 0), 0);
  EXPECT_EQ(m.get(1, 1), 0);
}

TEST_F(MatrixTest, MatrixVectorConstructor) {
  Matrix<float> m(v1);
  EXPECT_EQ(m.getNumRows(), 3);
  EXPECT_EQ(m.getNumCols(), 3);
  EXPECT_EQ(m.get(0, 0), 1);
  EXPECT_EQ(m.get(0, 2), 3);
  EXPECT_EQ(m.get(2, 0), 7);
  EXPECT_EQ(m.get(1, 1), 5);
  EXPECT_EQ(m.get(2, 2), 9);
}

TEST_F(MatrixTest, MatrixCopyConstructor) {
  Matrix<float> m1(v1);
  Matrix<float> m2(m1);
  EXPECT_EQ(m1.getNumRows(), m2.getNumRows());
  EXPECT_EQ(m1.getNumCols(), m2.getNumCols());
  EXPECT_EQ(m1.get(0, 0), m2.get(0, 0));
  EXPECT_EQ(m1.get(0, 2), m2.get(0, 2));
  EXPECT_EQ(m1.get(2, 0), m2.get(2, 0));
  EXPECT_EQ(m1.get(1, 1), m2.get(1, 1));
  EXPECT_EQ(m1.get(2, 2), m2.get(2, 2));
}

TEST_F(MatrixTest, MatrixGetMatrix){
  Matrix<float> m1(v1);
  EXPECT_EQ(m1.getMatrix(),v1);
}

TEST_F(MatrixTest, MatrixGetRow){
  Matrix<float> m1(v1);
  auto vTest = m1.getRow(2);
  EXPECT_EQ(vTest[0], 7);
  EXPECT_EQ(vTest[1], 8);
  EXPECT_EQ(vTest[2], 9);
  EXPECT_THROW(m1.getRow(-20), RowIndexOutOfRange);
  EXPECT_THROW(m1.getRow(4), RowIndexOutOfRange);
}
TEST_F(MatrixTest, MatrixGetColumn){
  Matrix<float> m1(v1);
  auto vTest = m1.getColumn(2);
  EXPECT_EQ(vTest[0], 3);
  EXPECT_EQ(vTest[1], 6);
  EXPECT_EQ(vTest[2], 9);
  EXPECT_THROW(m1.getColumn(-20), ColumnIndexOutOfRange);
  EXPECT_THROW(m1.getColumn(3), ColumnIndexOutOfRange);
}

TEST_F(MatrixTest, MatrixGetDiagonal){
  Matrix<float> m1(v1);
  auto vTest = m1.getDiagonal();
  EXPECT_EQ(vTest[0], 1);
  EXPECT_EQ(vTest[1], 5);
  EXPECT_EQ(vTest[2], 9);
}

TEST_F(MatrixTest, MatrixGetSubmatrix){
  Matrix<float> m1(v1);
  Matrix<float> subM = m1.getSubMatrix(1, 1, 2, 2);
  EXPECT_EQ(subM[0][0], 5);
  EXPECT_EQ(subM[0][1], 6);
  EXPECT_EQ(subM[1][0], 8);
  EXPECT_EQ(subM[1][1], 9);
  EXPECT_EQ(subM.getNumRows(), 2);
  EXPECT_EQ(subM.getNumCols(), 2);
}

TEST_F(MatrixTest, MatrixSet){
  Matrix<float> m1(v1);
  m1.set(0, 0, 200);
  m1.set(2, 2, -200);
  EXPECT_EQ(m1[0][0], 200);
  EXPECT_EQ(m1[2][2], -200);
  EXPECT_THROW(m1.set(-2, 0, 12), RowIndexOutOfRange);
  EXPECT_THROW(m1.set(0, -2, 12), ColumnIndexOutOfRange);
}
TEST_F(MatrixTest, MatrixSetRow){
  Matrix<float> m1(v1);
  std::vector<float> v = {0, 0, 1};
  std::vector<float> u = {0, 0, 1, 4};
  m1.setRow(2, v);

  EXPECT_EQ(m1[2][0], 0);
  EXPECT_EQ(m1[2][1], 0);
  EXPECT_EQ(m1[2][2], 1);
  EXPECT_THROW(m1.setRow(-2, v), RowIndexOutOfRange);
  EXPECT_THROW(m1.setRow(2, u), VectorSizeMissmatch);
}
TEST_F(MatrixTest, MatrixSetColumn){
  Matrix<float> m1(v1);
  std::vector<float> v = {0, 0, 1};
  std::vector<float> u = {0, 0, 1, 4};
  m1.setColumn(2, v);
  EXPECT_EQ(m1[0][2], 0);
  EXPECT_EQ(m1[1][2], 0);
  EXPECT_EQ(m1[2][2], 1);
  EXPECT_THROW(m1.setColumn(-2, v), ColumnIndexOutOfRange);
  EXPECT_THROW(m1.setColumn(2, u), VectorSizeMissmatch);
}