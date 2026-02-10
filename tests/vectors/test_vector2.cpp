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
#include "lm2/vectors/lm2_vector2.h"

// Test fixture for vector2 tests
class Vector2Test : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-6f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Creation and Initialization Tests (f64)
// =============================================================================

TEST_F(Vector2Test, Make_F64) {
  lm2_v2_f64 v = lm2_v2_make_f64(3.0, 4.0);
  EXPECT_DOUBLE_EQ(v.x, 3.0);
  EXPECT_DOUBLE_EQ(v.y, 4.0);
}

TEST_F(Vector2Test, Splat_F64) {
  lm2_v2_f64 v = lm2_v2_splat_f64(5.0);
  EXPECT_DOUBLE_EQ(v.x, 5.0);
  EXPECT_DOUBLE_EQ(v.y, 5.0);
}

TEST_F(Vector2Test, Zero_F64) {
  lm2_v2_f64 v = lm2_v2_zero_f64();
  EXPECT_DOUBLE_EQ(v.x, 0.0);
  EXPECT_DOUBLE_EQ(v.y, 0.0);
}

// =============================================================================
// Creation and Initialization Tests (f32)
// =============================================================================

TEST_F(Vector2Test, Make_F32) {
  lm2_v2_f32 v = lm2_v2_make_f32(3.0f, 4.0f);
  EXPECT_FLOAT_EQ(v.x, 3.0f);
  EXPECT_FLOAT_EQ(v.y, 4.0f);
}

TEST_F(Vector2Test, Splat_F32) {
  lm2_v2_f32 v = lm2_v2_splat_f32(5.0f);
  EXPECT_FLOAT_EQ(v.x, 5.0f);
  EXPECT_FLOAT_EQ(v.y, 5.0f);
}

TEST_F(Vector2Test, Zero_F32) {
  lm2_v2_f32 v = lm2_v2_zero_f32();
  EXPECT_FLOAT_EQ(v.x, 0.0f);
  EXPECT_FLOAT_EQ(v.y, 0.0f);
}

// =============================================================================
// Arithmetic Operations Tests (f64)
// =============================================================================

TEST_F(Vector2Test, Add_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(1.0, 2.0);
  lm2_v2_f64 b = lm2_v2_make_f64(3.0, 4.0);
  lm2_v2_f64 result = lm2_v2_add_f64(a, b);
  EXPECT_DOUBLE_EQ(result.x, 4.0);
  EXPECT_DOUBLE_EQ(result.y, 6.0);
}

TEST_F(Vector2Test, Sub_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(5.0, 8.0);
  lm2_v2_f64 b = lm2_v2_make_f64(2.0, 3.0);
  lm2_v2_f64 result = lm2_v2_sub_f64(a, b);
  EXPECT_DOUBLE_EQ(result.x, 3.0);
  EXPECT_DOUBLE_EQ(result.y, 5.0);
}

TEST_F(Vector2Test, Mul_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(2.0, 3.0);
  lm2_v2_f64 b = lm2_v2_make_f64(4.0, 5.0);
  lm2_v2_f64 result = lm2_v2_mul_f64(a, b);
  EXPECT_DOUBLE_EQ(result.x, 8.0);
  EXPECT_DOUBLE_EQ(result.y, 15.0);
}

TEST_F(Vector2Test, Div_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(10.0, 20.0);
  lm2_v2_f64 b = lm2_v2_make_f64(2.0, 4.0);
  lm2_v2_f64 result = lm2_v2_div_f64(a, b);
  EXPECT_DOUBLE_EQ(result.x, 5.0);
  EXPECT_DOUBLE_EQ(result.y, 5.0);
}

// =============================================================================
// Scalar Arithmetic Operations Tests (f64)
// =============================================================================

TEST_F(Vector2Test, AddScalar_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(1.0, 2.0);
  lm2_v2_f64 result = lm2_v2_add_s_f64(a, 5.0);
  EXPECT_DOUBLE_EQ(result.x, 6.0);
  EXPECT_DOUBLE_EQ(result.y, 7.0);
}

TEST_F(Vector2Test, SubScalar_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(10.0, 8.0);
  lm2_v2_f64 result = lm2_v2_sub_s_f64(a, 3.0);
  EXPECT_DOUBLE_EQ(result.x, 7.0);
  EXPECT_DOUBLE_EQ(result.y, 5.0);
}

TEST_F(Vector2Test, MulScalar_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(2.0, 3.0);
  lm2_v2_f64 result = lm2_v2_mul_s_f64(a, 4.0);
  EXPECT_DOUBLE_EQ(result.x, 8.0);
  EXPECT_DOUBLE_EQ(result.y, 12.0);
}

TEST_F(Vector2Test, DivScalar_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(10.0, 20.0);
  lm2_v2_f64 result = lm2_v2_div_s_f64(a, 2.0);
  EXPECT_DOUBLE_EQ(result.x, 5.0);
  EXPECT_DOUBLE_EQ(result.y, 10.0);
}

// =============================================================================
// Arithmetic Operations Tests (f32)
// =============================================================================

TEST_F(Vector2Test, Add_F32) {
  lm2_v2_f32 a = lm2_v2_make_f32(1.0f, 2.0f);
  lm2_v2_f32 b = lm2_v2_make_f32(3.0f, 4.0f);
  lm2_v2_f32 result = lm2_v2_add_f32(a, b);
  EXPECT_FLOAT_EQ(result.x, 4.0f);
  EXPECT_FLOAT_EQ(result.y, 6.0f);
}

TEST_F(Vector2Test, Sub_F32) {
  lm2_v2_f32 a = lm2_v2_make_f32(5.0f, 8.0f);
  lm2_v2_f32 b = lm2_v2_make_f32(2.0f, 3.0f);
  lm2_v2_f32 result = lm2_v2_sub_f32(a, b);
  EXPECT_FLOAT_EQ(result.x, 3.0f);
  EXPECT_FLOAT_EQ(result.y, 5.0f);
}

TEST_F(Vector2Test, Mul_F32) {
  lm2_v2_f32 a = lm2_v2_make_f32(2.0f, 3.0f);
  lm2_v2_f32 b = lm2_v2_make_f32(4.0f, 5.0f);
  lm2_v2_f32 result = lm2_v2_mul_f32(a, b);
  EXPECT_FLOAT_EQ(result.x, 8.0f);
  EXPECT_FLOAT_EQ(result.y, 15.0f);
}

TEST_F(Vector2Test, Div_F32) {
  lm2_v2_f32 a = lm2_v2_make_f32(10.0f, 20.0f);
  lm2_v2_f32 b = lm2_v2_make_f32(2.0f, 4.0f);
  lm2_v2_f32 result = lm2_v2_div_f32(a, b);
  EXPECT_FLOAT_EQ(result.x, 5.0f);
  EXPECT_FLOAT_EQ(result.y, 5.0f);
}

// =============================================================================
// Unary Operations Tests (f64)
// =============================================================================

TEST_F(Vector2Test, Neg_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(3.0, -4.0);
  lm2_v2_f64 result = lm2_v2_neg_f64(a);
  EXPECT_DOUBLE_EQ(result.x, -3.0);
  EXPECT_DOUBLE_EQ(result.y, 4.0);
}

TEST_F(Vector2Test, Floor_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(3.7, -2.3);
  lm2_v2_f64 result = lm2_v2_floor_f64(a);
  EXPECT_DOUBLE_EQ(result.x, 3.0);
  EXPECT_DOUBLE_EQ(result.y, -3.0);
}

TEST_F(Vector2Test, Ceil_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(3.2, -2.8);
  lm2_v2_f64 result = lm2_v2_ceil_f64(a);
  EXPECT_DOUBLE_EQ(result.x, 4.0);
  EXPECT_DOUBLE_EQ(result.y, -2.0);
}

TEST_F(Vector2Test, Round_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(3.5, 2.4);
  lm2_v2_f64 result = lm2_v2_round_f64(a);
  EXPECT_DOUBLE_EQ(result.x, 4.0);
  EXPECT_DOUBLE_EQ(result.y, 2.0);
}

TEST_F(Vector2Test, Trunc_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(3.7, -2.8);
  lm2_v2_f64 result = lm2_v2_trunc_f64(a);
  EXPECT_DOUBLE_EQ(result.x, 3.0);
  EXPECT_DOUBLE_EQ(result.y, -2.0);
}

TEST_F(Vector2Test, Abs_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(-3.0, 4.0);
  lm2_v2_f64 result = lm2_v2_abs_f64(a);
  EXPECT_DOUBLE_EQ(result.x, 3.0);
  EXPECT_DOUBLE_EQ(result.y, 4.0);
}

TEST_F(Vector2Test, Sign_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(-3.0, 4.0);
  lm2_v2_f64 result = lm2_v2_sign_f64(a);
  EXPECT_DOUBLE_EQ(result.x, -1.0);
  EXPECT_DOUBLE_EQ(result.y, 1.0);
}

TEST_F(Vector2Test, Sign0_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(-3.0, 0.0);
  lm2_v2_f64 result = lm2_v2_sign0_f64(a);
  EXPECT_DOUBLE_EQ(result.x, -1.0);
  EXPECT_DOUBLE_EQ(result.y, 0.0);
}

TEST_F(Vector2Test, Saturate_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(-0.5, 1.5);
  lm2_v2_f64 result = lm2_v2_saturate_f64(a);
  EXPECT_DOUBLE_EQ(result.x, 0.0);
  EXPECT_DOUBLE_EQ(result.y, 1.0);
}

TEST_F(Vector2Test, Fract_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(3.7, 2.3);
  lm2_v2_f64 result = lm2_v2_fract_f64(a);
  EXPECT_NEAR(result.x, 0.7, EPSILON_F64);
  EXPECT_NEAR(result.y, 0.3, EPSILON_F64);
}

TEST_F(Vector2Test, Sqrt_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(4.0, 9.0);
  lm2_v2_f64 result = lm2_v2_sqrt_f64(a);
  EXPECT_DOUBLE_EQ(result.x, 2.0);
  EXPECT_DOUBLE_EQ(result.y, 3.0);
}

// =============================================================================
// Unary Operations Tests (f32)
// =============================================================================

TEST_F(Vector2Test, Neg_F32) {
  lm2_v2_f32 a = lm2_v2_make_f32(3.0f, -4.0f);
  lm2_v2_f32 result = lm2_v2_neg_f32(a);
  EXPECT_FLOAT_EQ(result.x, -3.0f);
  EXPECT_FLOAT_EQ(result.y, 4.0f);
}

TEST_F(Vector2Test, Floor_F32) {
  lm2_v2_f32 a = lm2_v2_make_f32(3.7f, -2.3f);
  lm2_v2_f32 result = lm2_v2_floor_f32(a);
  EXPECT_FLOAT_EQ(result.x, 3.0f);
  EXPECT_FLOAT_EQ(result.y, -3.0f);
}

TEST_F(Vector2Test, Ceil_F32) {
  lm2_v2_f32 a = lm2_v2_make_f32(3.2f, -2.8f);
  lm2_v2_f32 result = lm2_v2_ceil_f32(a);
  EXPECT_FLOAT_EQ(result.x, 4.0f);
  EXPECT_FLOAT_EQ(result.y, -2.0f);
}

TEST_F(Vector2Test, Abs_F32) {
  lm2_v2_f32 a = lm2_v2_make_f32(-3.0f, 4.0f);
  lm2_v2_f32 result = lm2_v2_abs_f32(a);
  EXPECT_FLOAT_EQ(result.x, 3.0f);
  EXPECT_FLOAT_EQ(result.y, 4.0f);
}

TEST_F(Vector2Test, Sqrt_F32) {
  lm2_v2_f32 a = lm2_v2_make_f32(4.0f, 9.0f);
  lm2_v2_f32 result = lm2_v2_sqrt_f32(a);
  EXPECT_FLOAT_EQ(result.x, 2.0f);
  EXPECT_FLOAT_EQ(result.y, 3.0f);
}

// =============================================================================
// Binary Operations Tests (f64)
// =============================================================================

TEST_F(Vector2Test, Min_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(3.0, 7.0);
  lm2_v2_f64 b = lm2_v2_make_f64(5.0, 2.0);
  lm2_v2_f64 result = lm2_v2_min_f64(a, b);
  EXPECT_DOUBLE_EQ(result.x, 3.0);
  EXPECT_DOUBLE_EQ(result.y, 2.0);
}

TEST_F(Vector2Test, Max_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(3.0, 7.0);
  lm2_v2_f64 b = lm2_v2_make_f64(5.0, 2.0);
  lm2_v2_f64 result = lm2_v2_max_f64(a, b);
  EXPECT_DOUBLE_EQ(result.x, 5.0);
  EXPECT_DOUBLE_EQ(result.y, 7.0);
}

TEST_F(Vector2Test, MinAbs_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(-5.0, 3.0);
  lm2_v2_f64 b = lm2_v2_make_f64(2.0, -7.0);
  lm2_v2_f64 result = lm2_v2_min_abs_f64(a, b);
  EXPECT_DOUBLE_EQ(result.x, 2.0);
  EXPECT_DOUBLE_EQ(result.y, 3.0);
}

TEST_F(Vector2Test, MaxAbs_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(-5.0, 3.0);
  lm2_v2_f64 b = lm2_v2_make_f64(2.0, -7.0);
  lm2_v2_f64 result = lm2_v2_max_abs_f64(a, b);
  EXPECT_DOUBLE_EQ(result.x, -5.0);
  EXPECT_DOUBLE_EQ(result.y, -7.0);
}

TEST_F(Vector2Test, Mod_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(7.0, 10.0);
  lm2_v2_f64 b = lm2_v2_make_f64(3.0, 4.0);
  lm2_v2_f64 result = lm2_v2_mod_f64(a, b);
  EXPECT_DOUBLE_EQ(result.x, 1.0);
  EXPECT_DOUBLE_EQ(result.y, 2.0);
}

TEST_F(Vector2Test, Pow_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(2.0, 3.0);
  lm2_v2_f64 b = lm2_v2_make_f64(3.0, 2.0);
  lm2_v2_f64 result = lm2_v2_pow_f64(a, b);
  EXPECT_DOUBLE_EQ(result.x, 8.0);
  EXPECT_DOUBLE_EQ(result.y, 9.0);
}

TEST_F(Vector2Test, FloorMultiple_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(17.5, 23.0);
  lm2_v2_f64 b = lm2_v2_make_f64(5.0, 10.0);
  lm2_v2_f64 result = lm2_v2_floor_multiple_f64(a, b);
  EXPECT_DOUBLE_EQ(result.x, 15.0);
  EXPECT_DOUBLE_EQ(result.y, 20.0);
}

TEST_F(Vector2Test, CeilMultiple_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(17.5, 23.0);
  lm2_v2_f64 b = lm2_v2_make_f64(5.0, 10.0);
  lm2_v2_f64 result = lm2_v2_ceil_multiple_f64(a, b);
  EXPECT_DOUBLE_EQ(result.x, 20.0);
  EXPECT_DOUBLE_EQ(result.y, 30.0);
}

TEST_F(Vector2Test, RoundMultiple_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(17.5, 22.0);
  lm2_v2_f64 b = lm2_v2_make_f64(5.0, 10.0);
  lm2_v2_f64 result = lm2_v2_round_multiple_f64(a, b);
  EXPECT_DOUBLE_EQ(result.x, 20.0);
  EXPECT_DOUBLE_EQ(result.y, 20.0);
}

TEST_F(Vector2Test, TruncMultiple_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(17.5, 23.0);
  lm2_v2_f64 b = lm2_v2_make_f64(5.0, 10.0);
  lm2_v2_f64 result = lm2_v2_trunc_multiple_f64(a, b);
  EXPECT_DOUBLE_EQ(result.x, 15.0);
  EXPECT_DOUBLE_EQ(result.y, 20.0);
}

// =============================================================================
// Binary Operations Tests (f32)
// =============================================================================

TEST_F(Vector2Test, Min_F32) {
  lm2_v2_f32 a = lm2_v2_make_f32(3.0f, 7.0f);
  lm2_v2_f32 b = lm2_v2_make_f32(5.0f, 2.0f);
  lm2_v2_f32 result = lm2_v2_min_f32(a, b);
  EXPECT_FLOAT_EQ(result.x, 3.0f);
  EXPECT_FLOAT_EQ(result.y, 2.0f);
}

TEST_F(Vector2Test, Max_F32) {
  lm2_v2_f32 a = lm2_v2_make_f32(3.0f, 7.0f);
  lm2_v2_f32 b = lm2_v2_make_f32(5.0f, 2.0f);
  lm2_v2_f32 result = lm2_v2_max_f32(a, b);
  EXPECT_FLOAT_EQ(result.x, 5.0f);
  EXPECT_FLOAT_EQ(result.y, 7.0f);
}

TEST_F(Vector2Test, Pow_F32) {
  lm2_v2_f32 a = lm2_v2_make_f32(2.0f, 3.0f);
  lm2_v2_f32 b = lm2_v2_make_f32(3.0f, 2.0f);
  lm2_v2_f32 result = lm2_v2_pow_f32(a, b);
  EXPECT_FLOAT_EQ(result.x, 8.0f);
  EXPECT_FLOAT_EQ(result.y, 9.0f);
}

// =============================================================================
// Interpolation Operations Tests (f64)
// =============================================================================

TEST_F(Vector2Test, Clamp_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(-1.0, 5.0);
  lm2_v2_f64 min = lm2_v2_make_f64(0.0, 0.0);
  lm2_v2_f64 max = lm2_v2_make_f64(3.0, 4.0);
  lm2_v2_f64 result = lm2_v2_clamp_f64(a, min, max);
  EXPECT_DOUBLE_EQ(result.x, 0.0);
  EXPECT_DOUBLE_EQ(result.y, 4.0);
}

TEST_F(Vector2Test, Lerp_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(0.0, 0.0);
  lm2_v2_f64 b = lm2_v2_make_f64(10.0, 20.0);
  lm2_v2_f64 t = lm2_v2_make_f64(0.5, 0.25);
  lm2_v2_f64 result = lm2_v2_lerp_f64(a, b, t);
  EXPECT_DOUBLE_EQ(result.x, 5.0);
  EXPECT_DOUBLE_EQ(result.y, 5.0);
}

TEST_F(Vector2Test, Smoothstep_F64) {
  lm2_v2_f64 edge0 = lm2_v2_make_f64(0.0, 0.0);
  lm2_v2_f64 edge1 = lm2_v2_make_f64(1.0, 1.0);
  lm2_v2_f64 x = lm2_v2_make_f64(0.5, 0.0);
  lm2_v2_f64 result = lm2_v2_smoothstep_f64(edge0, edge1, x);
  EXPECT_DOUBLE_EQ(result.x, 0.5);
  EXPECT_DOUBLE_EQ(result.y, 0.0);
}

TEST_F(Vector2Test, Alpha_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(5.0, 10.0);
  lm2_v2_f64 b = lm2_v2_make_f64(10.0, 20.0);
  lm2_v2_f64 c = lm2_v2_make_f64(7.5, 15.0);
  lm2_v2_f64 result = lm2_v2_alpha_f64(a, b, c);
  EXPECT_DOUBLE_EQ(result.x, 0.5);
  EXPECT_DOUBLE_EQ(result.y, 0.5);
}

// =============================================================================
// Interpolation Operations Tests (f32)
// =============================================================================

TEST_F(Vector2Test, Clamp_F32) {
  lm2_v2_f32 a = lm2_v2_make_f32(-1.0f, 5.0f);
  lm2_v2_f32 min = lm2_v2_make_f32(0.0f, 0.0f);
  lm2_v2_f32 max = lm2_v2_make_f32(3.0f, 4.0f);
  lm2_v2_f32 result = lm2_v2_clamp_f32(a, min, max);
  EXPECT_FLOAT_EQ(result.x, 0.0f);
  EXPECT_FLOAT_EQ(result.y, 4.0f);
}

TEST_F(Vector2Test, Lerp_F32) {
  lm2_v2_f32 a = lm2_v2_make_f32(0.0f, 0.0f);
  lm2_v2_f32 b = lm2_v2_make_f32(10.0f, 20.0f);
  lm2_v2_f32 t = lm2_v2_make_f32(0.5f, 0.25f);
  lm2_v2_f32 result = lm2_v2_lerp_f32(a, b, t);
  EXPECT_FLOAT_EQ(result.x, 5.0f);
  EXPECT_FLOAT_EQ(result.y, 5.0f);
}

// =============================================================================
// Integer Vector Operations Tests (i32)
// =============================================================================

TEST_F(Vector2Test, Make_I32) {
  lm2_v2_i32 v = lm2_v2_make_i32(3, 4);
  EXPECT_EQ(v.x, 3);
  EXPECT_EQ(v.y, 4);
}

TEST_F(Vector2Test, Add_I32) {
  lm2_v2_i32 a = lm2_v2_make_i32(1, 2);
  lm2_v2_i32 b = lm2_v2_make_i32(3, 4);
  lm2_v2_i32 result = lm2_v2_add_i32(a, b);
  EXPECT_EQ(result.x, 4);
  EXPECT_EQ(result.y, 6);
}

TEST_F(Vector2Test, Sub_I32) {
  lm2_v2_i32 a = lm2_v2_make_i32(5, 8);
  lm2_v2_i32 b = lm2_v2_make_i32(2, 3);
  lm2_v2_i32 result = lm2_v2_sub_i32(a, b);
  EXPECT_EQ(result.x, 3);
  EXPECT_EQ(result.y, 5);
}

TEST_F(Vector2Test, Mul_I32) {
  lm2_v2_i32 a = lm2_v2_make_i32(2, 3);
  lm2_v2_i32 b = lm2_v2_make_i32(4, 5);
  lm2_v2_i32 result = lm2_v2_mul_i32(a, b);
  EXPECT_EQ(result.x, 8);
  EXPECT_EQ(result.y, 15);
}

TEST_F(Vector2Test, Div_I32) {
  lm2_v2_i32 a = lm2_v2_make_i32(10, 20);
  lm2_v2_i32 b = lm2_v2_make_i32(2, 4);
  lm2_v2_i32 result = lm2_v2_div_i32(a, b);
  EXPECT_EQ(result.x, 5);
  EXPECT_EQ(result.y, 5);
}

TEST_F(Vector2Test, Neg_I32) {
  lm2_v2_i32 a = lm2_v2_make_i32(3, -4);
  lm2_v2_i32 result = lm2_v2_neg_i32(a);
  EXPECT_EQ(result.x, -3);
  EXPECT_EQ(result.y, 4);
}

TEST_F(Vector2Test, Abs_I32) {
  lm2_v2_i32 a = lm2_v2_make_i32(-3, 4);
  lm2_v2_i32 result = lm2_v2_abs_i32(a);
  EXPECT_EQ(result.x, 3);
  EXPECT_EQ(result.y, 4);
}

TEST_F(Vector2Test, Min_I32) {
  lm2_v2_i32 a = lm2_v2_make_i32(3, 7);
  lm2_v2_i32 b = lm2_v2_make_i32(5, 2);
  lm2_v2_i32 result = lm2_v2_min_i32(a, b);
  EXPECT_EQ(result.x, 3);
  EXPECT_EQ(result.y, 2);
}

TEST_F(Vector2Test, Max_I32) {
  lm2_v2_i32 a = lm2_v2_make_i32(3, 7);
  lm2_v2_i32 b = lm2_v2_make_i32(5, 2);
  lm2_v2_i32 result = lm2_v2_max_i32(a, b);
  EXPECT_EQ(result.x, 5);
  EXPECT_EQ(result.y, 7);
}

TEST_F(Vector2Test, MulScalar_I32) {
  lm2_v2_i32 a = lm2_v2_make_i32(2, 3);
  lm2_v2_i32 result = lm2_v2_mul_s_i32(a, 4);
  EXPECT_EQ(result.x, 8);
  EXPECT_EQ(result.y, 12);
}

TEST_F(Vector2Test, Clamp_I32) {
  lm2_v2_i32 a = lm2_v2_make_i32(-1, 5);
  lm2_v2_i32 min = lm2_v2_make_i32(0, 0);
  lm2_v2_i32 max = lm2_v2_make_i32(3, 4);
  lm2_v2_i32 result = lm2_v2_clamp_i32(a, min, max);
  EXPECT_EQ(result.x, 0);
  EXPECT_EQ(result.y, 4);
}
