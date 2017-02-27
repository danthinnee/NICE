#include <stdio.h>
#include <iostream>
#include "Eigen/Dense"
#include "gtest/gtest.h"
#include "include/cpu_operations.h"
#include "include/matrix.h"
#include "include/vector.h"

template<class T>
class DeterminantTest : public ::testing::Test {
 public:
  Nice::Matrix<T> input;
  T output;
  T correct;

  void GetDeterminant() {
    output = Nice::CpuOperations<T>::Determinant(input);
  }
};


typedef ::testing::Types<float, double> MyTypes;
TYPED_TEST_CASE(DeterminantTest, MyTypes);

TYPED_TEST(DeterminantTest, DeterminantFunctionality) {
  this->input.setRandom(3, 3);
  this->input << 5, 4, 6,
                 2, 1, 1,
                 8, 6, 3;
  this->correct = 17;
  this->GetDeterminant();
  EXPECT_NEAR(this->output, this->correct, 0.0001);
}

TYPED_TEST(DeterminantTest, SingularMatrix) {
  this->input.setConstant(2, 2, 10);
  this->GetDeterminant();
  EXPECT_NEAR(this->output, 0, 0.0001);
}

TYPED_TEST(DeterminantTest, NonSquareMatrix) {
  this->input.setRandom(2, 3);
  ASSERT_DEATH(this->GetDeterminant(), "MATRIX IS NOT A SQUARE MATRIX!");
}

TYPED_TEST(DeterminantTest, EmptyMatrix) {
  ASSERT_DEATH(this->GetDeterminant(), "EMPTY MATRIX AS ARGUMENT!");
}
