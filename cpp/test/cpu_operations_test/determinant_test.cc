// The MIT License (MIT)
//
// Copyright (c) 2016 Northeastern University
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// This file tests the CpuOperations::Determinant() function by checking to
// see if the determinant is correctly determined for the matrix passed, and the
// function returns an appropriate error message if the matrix is not a square
// or is empty.

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
