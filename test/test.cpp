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
    v3 = {{1, 2},
        {3, 4}};

    v4 = {{2, 4, 6},
          {8, 10, 12},
          {14, 16, 18}
    };

    v5 = {{-2, 0, 2},
          {0, 2, 0},
          {2, 0, -2}
    };

    v6 = {{1, 0, 0},
          {0, 0, 1},
          {0, 1, 0}
    };

    v7 = {{-1, 0, 0},
          {0, -1, 0},
          {0, 0, -1}
    };
  }

  std::vector<std::vector<float>> v1;
  std::vector<std::vector<float>> v2;
  std::vector<std::vector<float>> v3;
  std::vector<std::vector<float>> v4;
  std::vector<std::vector<float>> v5;
  std::vector<std::vector<float>> v6;
  std::vector<std::vector<float>> v7;
};

#include "MatrixAccessorsTest.cpp"
#include "MatrixOperatorsTest.cpp"
#include "MatrixTest.cpp"



int main(int argc, char** argv) {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}