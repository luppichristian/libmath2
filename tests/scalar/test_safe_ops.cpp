/*
MIT License

Copyright (c) 2026 Christian Luppi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include "lm2/scalar/lm2_safe_ops.h"

// Test fixture for safe operations tests
class SafeOpsTest : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-6f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Safe Addition Tests - Floating Point
// =============================================================================

TEST_F(SafeOpsTest, Add_F64) {
  EXPECT_DOUBLE_EQ(lm2_add_f64(5.0, 3.0), 8.0);
  EXPECT_DOUBLE_EQ(lm2_add_f64(-5.0, 3.0), -2.0);
  EXPECT_DOUBLE_EQ(lm2_add_f64(-5.0, -3.0), -8.0);
  EXPECT_DOUBLE_EQ(lm2_add_f64(0.0, 0.0), 0.0);
  EXPECT_DOUBLE_EQ(lm2_add_f64(1.5, 2.5), 4.0);
}

TEST_F(SafeOpsTest, Add_F32) {
  EXPECT_FLOAT_EQ(lm2_add_f32(5.0f, 3.0f), 8.0f);
  EXPECT_FLOAT_EQ(lm2_add_f32(-5.0f, 3.0f), -2.0f);
  EXPECT_FLOAT_EQ(lm2_add_f32(-5.0f, -3.0f), -8.0f);
  EXPECT_FLOAT_EQ(lm2_add_f32(0.0f, 0.0f), 0.0f);
}

// =============================================================================
// Safe Addition Tests - Signed Integers
// =============================================================================

TEST_F(SafeOpsTest, Add_I64) {
  EXPECT_EQ(lm2_add_i64(5, 3), 8);
  EXPECT_EQ(lm2_add_i64(-5, 3), -2);
  EXPECT_EQ(lm2_add_i64(-5, -3), -8);
  EXPECT_EQ(lm2_add_i64(0, 0), 0);
}

TEST_F(SafeOpsTest, Add_I32) {
  EXPECT_EQ(lm2_add_i32(5, 3), 8);
  EXPECT_EQ(lm2_add_i32(-5, 3), -2);
  EXPECT_EQ(lm2_add_i32(-5, -3), -8);
}

TEST_F(SafeOpsTest, Add_I16) {
  EXPECT_EQ(lm2_add_i16(5, 3), 8);
  EXPECT_EQ(lm2_add_i16(-5, 3), -2);
  EXPECT_EQ(lm2_add_i16(-5, -3), -8);
}

TEST_F(SafeOpsTest, Add_I8) {
  EXPECT_EQ(lm2_add_i8(5, 3), 8);
  EXPECT_EQ(lm2_add_i8(-5, 3), -2);
  EXPECT_EQ(lm2_add_i8(-5, -3), -8);
}

// =============================================================================
// Safe Addition Tests - Unsigned Integers
// =============================================================================

TEST_F(SafeOpsTest, Add_U64) {
  EXPECT_EQ(lm2_add_u64(5, 3), 8);
  EXPECT_EQ(lm2_add_u64(0, 0), 0);
  EXPECT_EQ(lm2_add_u64(100, 200), 300);
}

TEST_F(SafeOpsTest, Add_U32) {
  EXPECT_EQ(lm2_add_u32(5, 3), 8);
  EXPECT_EQ(lm2_add_u32(0, 0), 0);
}

TEST_F(SafeOpsTest, Add_U16) {
  EXPECT_EQ(lm2_add_u16(5, 3), 8);
  EXPECT_EQ(lm2_add_u16(0, 0), 0);
}

TEST_F(SafeOpsTest, Add_U8) {
  EXPECT_EQ(lm2_add_u8(5, 3), 8);
  EXPECT_EQ(lm2_add_u8(0, 0), 0);
}

// =============================================================================
// Safe Subtraction Tests - Floating Point
// =============================================================================

TEST_F(SafeOpsTest, Sub_F64) {
  EXPECT_DOUBLE_EQ(lm2_sub_f64(5.0, 3.0), 2.0);
  EXPECT_DOUBLE_EQ(lm2_sub_f64(3.0, 5.0), -2.0);
  EXPECT_DOUBLE_EQ(lm2_sub_f64(-5.0, -3.0), -2.0);
  EXPECT_DOUBLE_EQ(lm2_sub_f64(0.0, 0.0), 0.0);
  EXPECT_DOUBLE_EQ(lm2_sub_f64(10.5, 5.5), 5.0);
}

TEST_F(SafeOpsTest, Sub_F32) {
  EXPECT_FLOAT_EQ(lm2_sub_f32(5.0f, 3.0f), 2.0f);
  EXPECT_FLOAT_EQ(lm2_sub_f32(3.0f, 5.0f), -2.0f);
  EXPECT_FLOAT_EQ(lm2_sub_f32(-5.0f, -3.0f), -2.0f);
}

// =============================================================================
// Safe Subtraction Tests - Signed Integers
// =============================================================================

TEST_F(SafeOpsTest, Sub_I64) {
  EXPECT_EQ(lm2_sub_i64(5, 3), 2);
  EXPECT_EQ(lm2_sub_i64(3, 5), -2);
  EXPECT_EQ(lm2_sub_i64(-5, -3), -2);
  EXPECT_EQ(lm2_sub_i64(0, 0), 0);
}

TEST_F(SafeOpsTest, Sub_I32) {
  EXPECT_EQ(lm2_sub_i32(5, 3), 2);
  EXPECT_EQ(lm2_sub_i32(3, 5), -2);
  EXPECT_EQ(lm2_sub_i32(-5, -3), -2);
}

TEST_F(SafeOpsTest, Sub_I16) {
  EXPECT_EQ(lm2_sub_i16(5, 3), 2);
  EXPECT_EQ(lm2_sub_i16(3, 5), -2);
}

TEST_F(SafeOpsTest, Sub_I8) {
  EXPECT_EQ(lm2_sub_i8(5, 3), 2);
  EXPECT_EQ(lm2_sub_i8(3, 5), -2);
}

// =============================================================================
// Safe Subtraction Tests - Unsigned Integers
// =============================================================================

TEST_F(SafeOpsTest, Sub_U64) {
  EXPECT_EQ(lm2_sub_u64(5, 3), 2);
  EXPECT_EQ(lm2_sub_u64(10, 10), 0);
  EXPECT_EQ(lm2_sub_u64(300, 200), 100);
}

TEST_F(SafeOpsTest, Sub_U32) {
  EXPECT_EQ(lm2_sub_u32(5, 3), 2);
  EXPECT_EQ(lm2_sub_u32(10, 10), 0);
}

TEST_F(SafeOpsTest, Sub_U16) {
  EXPECT_EQ(lm2_sub_u16(5, 3), 2);
  EXPECT_EQ(lm2_sub_u16(10, 10), 0);
}

TEST_F(SafeOpsTest, Sub_U8) {
  EXPECT_EQ(lm2_sub_u8(5, 3), 2);
  EXPECT_EQ(lm2_sub_u8(10, 10), 0);
}

// =============================================================================
// Safe Multiplication Tests - Floating Point
// =============================================================================

TEST_F(SafeOpsTest, Mul_F64) {
  EXPECT_DOUBLE_EQ(lm2_mul_f64(5.0, 3.0), 15.0);
  EXPECT_DOUBLE_EQ(lm2_mul_f64(-5.0, 3.0), -15.0);
  EXPECT_DOUBLE_EQ(lm2_mul_f64(-5.0, -3.0), 15.0);
  EXPECT_DOUBLE_EQ(lm2_mul_f64(0.0, 5.0), 0.0);
  EXPECT_DOUBLE_EQ(lm2_mul_f64(2.5, 4.0), 10.0);
}

TEST_F(SafeOpsTest, Mul_F32) {
  EXPECT_FLOAT_EQ(lm2_mul_f32(5.0f, 3.0f), 15.0f);
  EXPECT_FLOAT_EQ(lm2_mul_f32(-5.0f, 3.0f), -15.0f);
  EXPECT_FLOAT_EQ(lm2_mul_f32(-5.0f, -3.0f), 15.0f);
  EXPECT_FLOAT_EQ(lm2_mul_f32(0.0f, 5.0f), 0.0f);
}

// =============================================================================
// Safe Multiplication Tests - Signed Integers
// =============================================================================

TEST_F(SafeOpsTest, Mul_I64) {
  EXPECT_EQ(lm2_mul_i64(5, 3), 15);
  EXPECT_EQ(lm2_mul_i64(-5, 3), -15);
  EXPECT_EQ(lm2_mul_i64(-5, -3), 15);
  EXPECT_EQ(lm2_mul_i64(0, 5), 0);
}

TEST_F(SafeOpsTest, Mul_I32) {
  EXPECT_EQ(lm2_mul_i32(5, 3), 15);
  EXPECT_EQ(lm2_mul_i32(-5, 3), -15);
  EXPECT_EQ(lm2_mul_i32(-5, -3), 15);
}

TEST_F(SafeOpsTest, Mul_I16) {
  EXPECT_EQ(lm2_mul_i16(5, 3), 15);
  EXPECT_EQ(lm2_mul_i16(-5, 3), -15);
}

TEST_F(SafeOpsTest, Mul_I8) {
  EXPECT_EQ(lm2_mul_i8(5, 3), 15);
  EXPECT_EQ(lm2_mul_i8(-5, 3), -15);
}

// =============================================================================
// Safe Multiplication Tests - Unsigned Integers
// =============================================================================

TEST_F(SafeOpsTest, Mul_U64) {
  EXPECT_EQ(lm2_mul_u64(5, 3), 15);
  EXPECT_EQ(lm2_mul_u64(0, 5), 0);
  EXPECT_EQ(lm2_mul_u64(10, 20), 200);
}

TEST_F(SafeOpsTest, Mul_U32) {
  EXPECT_EQ(lm2_mul_u32(5, 3), 15);
  EXPECT_EQ(lm2_mul_u32(0, 5), 0);
}

TEST_F(SafeOpsTest, Mul_U16) {
  EXPECT_EQ(lm2_mul_u16(5, 3), 15);
  EXPECT_EQ(lm2_mul_u16(0, 5), 0);
}

TEST_F(SafeOpsTest, Mul_U8) {
  EXPECT_EQ(lm2_mul_u8(5, 3), 15);
  EXPECT_EQ(lm2_mul_u8(0, 5), 0);
}

// =============================================================================
// Safe Division Tests - Floating Point
// =============================================================================

TEST_F(SafeOpsTest, Div_F64) {
  EXPECT_DOUBLE_EQ(lm2_div_f64(15.0, 3.0), 5.0);
  EXPECT_DOUBLE_EQ(lm2_div_f64(-15.0, 3.0), -5.0);
  EXPECT_DOUBLE_EQ(lm2_div_f64(-15.0, -3.0), 5.0);
  EXPECT_DOUBLE_EQ(lm2_div_f64(0.0, 5.0), 0.0);
  EXPECT_DOUBLE_EQ(lm2_div_f64(10.0, 4.0), 2.5);
}

TEST_F(SafeOpsTest, Div_F32) {
  EXPECT_FLOAT_EQ(lm2_div_f32(15.0f, 3.0f), 5.0f);
  EXPECT_FLOAT_EQ(lm2_div_f32(-15.0f, 3.0f), -5.0f);
  EXPECT_FLOAT_EQ(lm2_div_f32(-15.0f, -3.0f), 5.0f);
  EXPECT_FLOAT_EQ(lm2_div_f32(0.0f, 5.0f), 0.0f);
}

// =============================================================================
// Safe Division Tests - Signed Integers
// =============================================================================

TEST_F(SafeOpsTest, Div_I64) {
  EXPECT_EQ(lm2_div_i64(15, 3), 5);
  EXPECT_EQ(lm2_div_i64(-15, 3), -5);
  EXPECT_EQ(lm2_div_i64(-15, -3), 5);
  EXPECT_EQ(lm2_div_i64(0, 5), 0);
  EXPECT_EQ(lm2_div_i64(10, 4), 2);  // Integer division
}

TEST_F(SafeOpsTest, Div_I32) {
  EXPECT_EQ(lm2_div_i32(15, 3), 5);
  EXPECT_EQ(lm2_div_i32(-15, 3), -5);
  EXPECT_EQ(lm2_div_i32(-15, -3), 5);
}

TEST_F(SafeOpsTest, Div_I16) {
  EXPECT_EQ(lm2_div_i16(15, 3), 5);
  EXPECT_EQ(lm2_div_i16(-15, 3), -5);
}

TEST_F(SafeOpsTest, Div_I8) {
  EXPECT_EQ(lm2_div_i8(15, 3), 5);
  EXPECT_EQ(lm2_div_i8(-15, 3), -5);
}

// =============================================================================
// Safe Division Tests - Unsigned Integers
// =============================================================================

TEST_F(SafeOpsTest, Div_U64) {
  EXPECT_EQ(lm2_div_u64(15, 3), 5);
  EXPECT_EQ(lm2_div_u64(0, 5), 0);
  EXPECT_EQ(lm2_div_u64(200, 10), 20);
}

TEST_F(SafeOpsTest, Div_U32) {
  EXPECT_EQ(lm2_div_u32(15, 3), 5);
  EXPECT_EQ(lm2_div_u32(0, 5), 0);
}

TEST_F(SafeOpsTest, Div_U16) {
  EXPECT_EQ(lm2_div_u16(15, 3), 5);
  EXPECT_EQ(lm2_div_u16(0, 5), 0);
}

TEST_F(SafeOpsTest, Div_U8) {
  EXPECT_EQ(lm2_div_u8(15, 3), 5);
  EXPECT_EQ(lm2_div_u8(0, 5), 0);
}

// =============================================================================
// Edge Case Tests - Near Limits
// =============================================================================

TEST_F(SafeOpsTest, Add_NearLimits_I32) {
  EXPECT_EQ(lm2_add_i32(std::numeric_limits<int32_t>::max() - 10, 5),
            std::numeric_limits<int32_t>::max() - 5);
  EXPECT_EQ(lm2_add_i32(std::numeric_limits<int32_t>::min() + 10, -5),
            std::numeric_limits<int32_t>::min() + 5);
}

TEST_F(SafeOpsTest, Sub_NearLimits_I32) {
  EXPECT_EQ(lm2_sub_i32(std::numeric_limits<int32_t>::max() - 10, 5),
            std::numeric_limits<int32_t>::max() - 15);
  EXPECT_EQ(lm2_sub_i32(std::numeric_limits<int32_t>::min() + 10, 5),
            std::numeric_limits<int32_t>::min() + 5);
}

TEST_F(SafeOpsTest, Mul_SmallValues_I32) {
  EXPECT_EQ(lm2_mul_i32(100, 100), 10000);
  EXPECT_EQ(lm2_mul_i32(-100, 100), -10000);
}

TEST_F(SafeOpsTest, Add_NearLimits_U32) {
  EXPECT_EQ(lm2_add_u32(std::numeric_limits<uint32_t>::max() - 10, 5),
            std::numeric_limits<uint32_t>::max() - 5);
}

TEST_F(SafeOpsTest, Sub_NearLimits_U32) {
  EXPECT_EQ(lm2_sub_u32(100, 50), 50);
  EXPECT_EQ(lm2_sub_u32(50, 50), 0);
}

// =============================================================================
// Edge Case Tests - Special Float Values
// =============================================================================

TEST_F(SafeOpsTest, FloatOperations_LargeNumbers) {
  double large = 1e100;
  EXPECT_DOUBLE_EQ(lm2_add_f64(large, 1.0), large + 1.0);
  EXPECT_DOUBLE_EQ(lm2_mul_f64(large, 2.0), large * 2.0);
}

TEST_F(SafeOpsTest, FloatOperations_SmallNumbers) {
  double small = 1e-100;
  EXPECT_DOUBLE_EQ(lm2_add_f64(small, small), small * 2.0);
  EXPECT_DOUBLE_EQ(lm2_mul_f64(small, 2.0), small * 2.0);
}

// =============================================================================
// Edge Case Tests - Division Edge Cases
// =============================================================================

TEST_F(SafeOpsTest, Div_IntegerTruncation) {
  EXPECT_EQ(lm2_div_i32(7, 2), 3);
  EXPECT_EQ(lm2_div_i32(-7, 2), -3);
  EXPECT_EQ(lm2_div_i32(7, -2), -3);
  EXPECT_EQ(lm2_div_i32(-7, -2), 3);
}

TEST_F(SafeOpsTest, Div_UnsignedTruncation) {
  EXPECT_EQ(lm2_div_u32(7, 2), 3);
  EXPECT_EQ(lm2_div_u32(10, 3), 3);
  EXPECT_EQ(lm2_div_u32(1, 2), 0);
}

// =============================================================================
// Combined Operations Tests
// =============================================================================

TEST_F(SafeOpsTest, CombinedOperations_I32) {
  int32_t a = 10;
  int32_t b = 5;
  int32_t c = 3;

  // (a + b) * c
  int32_t result1 = lm2_mul_i32(lm2_add_i32(a, b), c);
  EXPECT_EQ(result1, 45);

  // (a - b) / c (should be 1 due to integer division of 5/3)
  int32_t result2 = lm2_div_i32(lm2_sub_i32(a, b), c);
  EXPECT_EQ(result2, 1);
}

TEST_F(SafeOpsTest, CombinedOperations_F64) {
  double a = 10.0;
  double b = 5.0;
  double c = 3.0;

  // (a + b) * c
  double result1 = lm2_mul_f64(lm2_add_f64(a, b), c);
  EXPECT_DOUBLE_EQ(result1, 45.0);

  // (a - b) / c
  double result2 = lm2_div_f64(lm2_sub_f64(a, b), c);
  EXPECT_NEAR(result2, 1.666666666666667, EPSILON_F64);
}
