#include <gtest/gtest.h>
#include <vector>
#include "../src/Matrix.hpp"


class MatrixTest : public ::testing::Test {
protected:
  void SetUp() override {
    v1 = {{1,2,3},
          {4,5,6},
          {7,8,9}
    };
    v2 = {{-1, -2, -3},
          {-4, -5, -6},
          {-7, -8, -9}
    };
  }

  std::vector<std::vector<float>> v1;
  std::vector<std::vector<float>> v2;
};

#include "MatrixAccessorsTest.cpp"
#include "MatrixOperatorsTest.cpp"
#include "MatrixTest.cpp"



int main(int argc, char** argv) {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}