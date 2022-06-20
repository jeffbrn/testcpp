#include <gtest/gtest.h>
#include "../include/vector.hpp"

namespace MatrixLib {
  namespace {
    class VectorTests : public ::testing::Test {
    };

    TEST_F(VectorTests, TestCreate) {
      Vector<float> v1(3);
      ASSERT_EQ(v1.Dimensions(), 3);
      ASSERT_EQ(v1[1], 0.0f);
      ASSERT_EQ(v1[2], 0.0f);
      ASSERT_EQ(v1[3], 0.0f);

      Vector<int> v2 = { 1, 2, 3, 4 };
      ASSERT_EQ(v2.Dimensions(), 4);
      ASSERT_EQ(v2[1], 1);
      ASSERT_EQ(v2[2], 2);
      ASSERT_EQ(v2[3], 3);
      ASSERT_EQ(v2[4], 4);

      auto v3 = unique_ptr<Vector<int>>(new Vector<int>(v2));
      (*v3)[2] = 11;
      ASSERT_EQ(v3->Dimensions(), 4);
      ASSERT_EQ((*v3)[1], 1);
      ASSERT_EQ((*v3)[2], 11);
      ASSERT_EQ((*v3)[3], 3);
      ASSERT_EQ((*v3)[4], 4);
      ASSERT_EQ(v2[2], 2);

      auto v4 = *v3;
      v4[1] = 10;
      ASSERT_EQ(v4.Dimensions(), 4);
      ASSERT_EQ(v4[1], 10);
      ASSERT_EQ(v4[2], 11);
      ASSERT_EQ(v4[3], 3);
      ASSERT_EQ(v4[4], 4);
      ASSERT_EQ((*v3)[1], 1);

      EXPECT_THROW(new Vector<int>(0), MatrixLibException);
      EXPECT_THROW(new Vector<char *>(1), MatrixLibException);
    }

    TEST_F(VectorTests, TestAssigningVectors) {
      Vector<int> v1 = { 1, 2 };
      Vector<int> v2 = { 3, 4, 5 };
      v2 = v1;
      ASSERT_EQ(v2.Dimensions(), 2);
      ASSERT_EQ(v2[1], 1);
      ASSERT_EQ(v2[2], 2);
    }

    TEST_F(VectorTests, TestGetSets) {
      Vector<int> v1(4);
      v1[4] = 4;
      EXPECT_EQ(v1[4], 4);
      EXPECT_THROW(v1[0], MatrixLibException);
      EXPECT_THROW(v1[5], MatrixLibException);
      EXPECT_THROW(v1[-1], MatrixLibException);
      EXPECT_THROW(v1[0] = 5, MatrixLibException);
      EXPECT_THROW(v1[5] = 5, MatrixLibException);
      EXPECT_THROW(v1[-1] = 5, MatrixLibException);
    }

    TEST_F(VectorTests, TestAddingVectors) {
      Vector<int> v1(3);
      Vector<int> v2 = { 1, 2, 3, 4 };
      EXPECT_THROW(v1 += v2, MatrixLibException);
      EXPECT_THROW(auto v3 = v1 + v2, MatrixLibException);
      Vector<int> v3 = { 1, -2, 3, -4 };
      Vector<int> v4 = { 5, 6, 7, 8 };
      Vector<int> result = { 6, 4, 10, 4 };
      Vector<int> v5 = v3 + v4;
      EXPECT_EQ(v5, result);
    }

    TEST_F(VectorTests, TestEquality) {
      Vector<int> v1(3), v2(3), v3(2);
      EXPECT_EQ(v1, v2);
      EXPECT_NE(v1, v3);
      Vector<float> v4 = { 1.1, 2.2, 3.3 };
      Vector<float> v5 = { 1.1, 2.2, 3.3 };
      Vector<float> v6 = { 1.1, 5.5, 3.3 };
      EXPECT_EQ(v4, v5);
      EXPECT_NE(v4, v6);
    }

    TEST_F(VectorTests, TestSubtractingVectors) {
      Vector<int> v1(3);
      Vector<int> v2 = { 1, 2, 3, 4 };
      EXPECT_THROW(v1 -= v2, MatrixLibException);
      EXPECT_THROW(auto v3 = v1 - v2, MatrixLibException);
      Vector<int> v3 = { 5, 6, 7, 8 };
      Vector<int> v4 = { 1, -2, 3, -4 };
      Vector<int> result = { 4, 8, 4, 12 };
      Vector<int> v5 = v3 - v4;
      EXPECT_EQ(v5, result);
    }

    TEST_F(VectorTests, TestScaling) {
      Vector<int> v1(3);
      v1 *= 100;
      EXPECT_EQ(v1[1], 0);
      EXPECT_EQ(v1[2], 0);
      EXPECT_EQ(v1[3], 0);

      v1 = { 3, 5, 7 };
      auto v2 = v1 * 3;
      EXPECT_EQ(v2[1], 9);
      EXPECT_EQ(v2[2], 15);
      EXPECT_EQ(v2[3], 21);
    }

    TEST_F(VectorTests, TestLength) {
      Vector<int> v1 = { 3, 4 };
      EXPECT_EQ(v1.Length(), 5.0);
    }

    TEST_F(VectorTests, TestDotProduct) {
      Vector<int> v1 = { 1, 3, 5 };
      Vector<int> v2 = { 2, 4, 6 };
      auto chk = 1*2 + 3*4 + 5*6;
      auto result = v1.DotProduct(v2);
      ASSERT_EQ(result, chk);
    }

    TEST_F(VectorTests, TestAngle) {
      Vector<int> v1 = { 0, 1 };
      Vector<int> v2 = { 1, 0 };
      auto result = cos(v1.Angle(v2));
      EXPECT_LE(result, 0.0000001);
      v1 = { 2, 2 };
      v2 = { 3, 3 };
      result = cos(v1.Angle(v2));
      EXPECT_EQ(result, 1);
      v1 = { 0, -5 };
      v2 = { 0, 5 };
      result = cos(v1.Angle(v2));
      EXPECT_EQ(result, -1);
    }

    TEST_F(VectorTests, TestCrossProduct) {
      Vector<int> t1 = { 1, 2 };
      Vector<int> t2 = { 3, 4 };
      EXPECT_THROW(t1*t2, MatrixLibException);
      t1 = { 1, 2 };
      t2 = { 3, 4, 5 };
      EXPECT_THROW(t1*t2, MatrixLibException);
      t1 = { 1, 2, 3, 4 };
      t2 = { 3, 4, 5, 6 };
      EXPECT_THROW(t1*t2, MatrixLibException);
      Vector<int> v1 = { 1, -3, 5 };
      Vector<int> v2 = { -2, 4, -6 };
      Vector<int> expect = { -2, -4, -2 };
      EXPECT_EQ(v1*=v2, expect);
      v1 = { 1, 3, 5 };
      v2 = { 2, 4, 6 };
      expect = { -2, 4, -2 };
      EXPECT_EQ(v1*v2, expect);
      v1 = { 1, 0, 0 };
      v2 = { 0, 1, 0 };
      expect = { 0, 0, 1 };
      EXPECT_EQ(v1*v2, expect);
      v1 = { 0, 0, 1 };
      v2 = { 0, 1, 0 };
      expect = { -1, 0, 0 };
      EXPECT_EQ(v1*v2, expect);
    }

    TEST_F(VectorTests, TestNormalize) {
      Vector<int> v = { 1, -3, 5 };
      auto result = v.Normalize();
      EXPECT_EQ(result.Length(), 1);
    }
  }
}