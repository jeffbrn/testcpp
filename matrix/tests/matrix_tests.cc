#include <gtest/gtest.h>
#include "../include/matrix.hpp"

using namespace std;

namespace MatrixLib {
  namespace {
    class MatrixTests : public ::testing::Test {
    };

    TEST_F(MatrixTests, TestCreate) {
      EXPECT_THROW(new Matrix<int>(0, 1), MatrixLibException);
      EXPECT_THROW(new Matrix<int>(1, 0), MatrixLibException);
      EXPECT_THROW(new Matrix<int>(0, 0), MatrixLibException);
      EXPECT_THROW(new Matrix<char *>(1, 1), MatrixLibException);

      Matrix<int> m1 = { {1, 2}, {3,4} };
      cout << m1 << endl;
    }
  }
}