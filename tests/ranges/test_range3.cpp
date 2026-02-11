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
#include "lm2/ranges/lm2_range3.h"

// Test fixture for range3 tests
class Range3Test : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-6f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Constructor Tests (f64)
// =============================================================================

TEST_F(Range3Test, FromMinMax_F64) {
  lm2_v3_f64 min = lm2_v3_make_f64(1.0, 2.0, 3.0);
  lm2_v3_f64 max = lm2_v3_make_f64(5.0, 6.0, 7.0);
  lm2_r3_f64 r = lm2_r3_from_min_max_f64(min, max);

  EXPECT_DOUBLE_EQ(r.min.x, 1.0);
  EXPECT_DOUBLE_EQ(r.min.y, 2.0);
  EXPECT_DOUBLE_EQ(r.min.z, 3.0);
  EXPECT_DOUBLE_EQ(r.max.x, 5.0);
  EXPECT_DOUBLE_EQ(r.max.y, 6.0);
  EXPECT_DOUBLE_EQ(r.max.z, 7.0);
}

TEST_F(Range3Test, FromCenterExtents_F64) {
  lm2_v3_f64 center = lm2_v3_make_f64(3.0, 4.0, 5.0);
  lm2_v3_f64 extents = lm2_v3_make_f64(2.0, 1.0, 1.5);
  lm2_r3_f64 r = lm2_r3_from_center_extents_f64(center, extents);

  EXPECT_DOUBLE_EQ(r.min.x, 1.0);  // 3 - 2
  EXPECT_DOUBLE_EQ(r.min.y, 3.0);  // 4 - 1
  EXPECT_DOUBLE_EQ(r.min.z, 3.5);  // 5 - 1.5
  EXPECT_DOUBLE_EQ(r.max.x, 5.0);  // 3 + 2
  EXPECT_DOUBLE_EQ(r.max.y, 5.0);  // 4 + 1
  EXPECT_DOUBLE_EQ(r.max.z, 6.5);  // 5 + 1.5
}

TEST_F(Range3Test, FromCenterSize_F64) {
  lm2_v3_f64 center = lm2_v3_make_f64(5.0, 5.0, 5.0);
  lm2_v3_f64 size = lm2_v3_make_f64(4.0, 2.0, 6.0);
  lm2_r3_f64 r = lm2_r3_from_center_size_f64(center, size);

  EXPECT_DOUBLE_EQ(r.min.x, 3.0);  // 5 - 2
  EXPECT_DOUBLE_EQ(r.min.y, 4.0);  // 5 - 1
  EXPECT_DOUBLE_EQ(r.min.z, 2.0);  // 5 - 3
  EXPECT_DOUBLE_EQ(r.max.x, 7.0);  // 5 + 2
  EXPECT_DOUBLE_EQ(r.max.y, 6.0);  // 5 + 1
  EXPECT_DOUBLE_EQ(r.max.z, 8.0);  // 5 + 3
}

TEST_F(Range3Test, FromPositionSize_F64) {
  lm2_v3_f64 position = lm2_v3_make_f64(2.0, 3.0, 4.0);
  lm2_v3_f64 size = lm2_v3_make_f64(4.0, 5.0, 6.0);
  lm2_r3_f64 r = lm2_r3_from_position_size_f64(position, size);

  EXPECT_DOUBLE_EQ(r.min.x, 2.0);
  EXPECT_DOUBLE_EQ(r.min.y, 3.0);
  EXPECT_DOUBLE_EQ(r.min.z, 4.0);
  EXPECT_DOUBLE_EQ(r.max.x, 6.0);   // 2 + 4
  EXPECT_DOUBLE_EQ(r.max.y, 8.0);   // 3 + 5
  EXPECT_DOUBLE_EQ(r.max.z, 10.0);  // 4 + 6
}

TEST_F(Range3Test, Zero_F64) {
  lm2_r3_f64 r = lm2_r3_zero_f64();

  EXPECT_DOUBLE_EQ(r.min.x, 0.0);
  EXPECT_DOUBLE_EQ(r.min.y, 0.0);
  EXPECT_DOUBLE_EQ(r.min.z, 0.0);
  EXPECT_DOUBLE_EQ(r.max.x, 0.0);
  EXPECT_DOUBLE_EQ(r.max.y, 0.0);
  EXPECT_DOUBLE_EQ(r.max.z, 0.0);
}

// =============================================================================
// Scalar Constructor Tests
// =============================================================================

TEST_F(Range3Test, FromScalars_F64) {
  lm2_r3_f64 r = lm2_r3_from_scalars_f64(1.0, 2.0, 3.0, 5.0, 6.0, 7.0);

  EXPECT_DOUBLE_EQ(r.min.x, 1.0);
  EXPECT_DOUBLE_EQ(r.min.y, 2.0);
  EXPECT_DOUBLE_EQ(r.min.z, 3.0);
  EXPECT_DOUBLE_EQ(r.max.x, 5.0);
  EXPECT_DOUBLE_EQ(r.max.y, 6.0);
  EXPECT_DOUBLE_EQ(r.max.z, 7.0);
}

TEST_F(Range3Test, FromScalars_F32) {
  lm2_r3_f32 r = lm2_r3_from_scalars_f32(1.0f, 2.0f, 3.0f, 5.0f, 6.0f, 7.0f);

  EXPECT_FLOAT_EQ(r.min.x, 1.0f);
  EXPECT_FLOAT_EQ(r.min.y, 2.0f);
  EXPECT_FLOAT_EQ(r.min.z, 3.0f);
  EXPECT_FLOAT_EQ(r.max.x, 5.0f);
  EXPECT_FLOAT_EQ(r.max.y, 6.0f);
  EXPECT_FLOAT_EQ(r.max.z, 7.0f);
}

TEST_F(Range3Test, FromScalars_I64) {
  lm2_r3_i64 r = lm2_r3_from_scalars_i64(1, 2, 3, 5, 6, 7);

  EXPECT_EQ(r.min.x, 1);
  EXPECT_EQ(r.min.y, 2);
  EXPECT_EQ(r.min.z, 3);
  EXPECT_EQ(r.max.x, 5);
  EXPECT_EQ(r.max.y, 6);
  EXPECT_EQ(r.max.z, 7);
}

TEST_F(Range3Test, FromScalars_I32) {
  lm2_r3_i32 r = lm2_r3_from_scalars_i32(1, 2, 3, 5, 6, 7);

  EXPECT_EQ(r.min.x, 1);
  EXPECT_EQ(r.min.y, 2);
  EXPECT_EQ(r.min.z, 3);
  EXPECT_EQ(r.max.x, 5);
  EXPECT_EQ(r.max.y, 6);
  EXPECT_EQ(r.max.z, 7);
}

TEST_F(Range3Test, FromScalars_I16) {
  lm2_r3_i16 r = lm2_r3_from_scalars_i16(1, 2, 3, 5, 6, 7);

  EXPECT_EQ(r.min.x, 1);
  EXPECT_EQ(r.min.y, 2);
  EXPECT_EQ(r.min.z, 3);
  EXPECT_EQ(r.max.x, 5);
  EXPECT_EQ(r.max.y, 6);
  EXPECT_EQ(r.max.z, 7);
}

// =============================================================================
// Constructor Tests (f32)
// =============================================================================

TEST_F(Range3Test, FromMinMax_F32) {
  lm2_v3_f32 min = lm2_v3_make_f32(1.0f, 2.0f, 3.0f);
  lm2_v3_f32 max = lm2_v3_make_f32(5.0f, 6.0f, 7.0f);
  lm2_r3_f32 r = lm2_r3_from_min_max_f32(min, max);

  EXPECT_FLOAT_EQ(r.min.x, 1.0f);
  EXPECT_FLOAT_EQ(r.min.y, 2.0f);
  EXPECT_FLOAT_EQ(r.min.z, 3.0f);
  EXPECT_FLOAT_EQ(r.max.x, 5.0f);
  EXPECT_FLOAT_EQ(r.max.y, 6.0f);
  EXPECT_FLOAT_EQ(r.max.z, 7.0f);
}

TEST_F(Range3Test, Zero_F32) {
  lm2_r3_f32 r = lm2_r3_zero_f32();

  EXPECT_FLOAT_EQ(r.min.x, 0.0f);
  EXPECT_FLOAT_EQ(r.min.y, 0.0f);
  EXPECT_FLOAT_EQ(r.min.z, 0.0f);
  EXPECT_FLOAT_EQ(r.max.x, 0.0f);
  EXPECT_FLOAT_EQ(r.max.y, 0.0f);
  EXPECT_FLOAT_EQ(r.max.z, 0.0f);
}

// =============================================================================
// Arithmetic Operations (f64)
// =============================================================================

TEST_F(Range3Test, Add_F64) {
  lm2_r3_f64 a = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(1.0, 2.0, 3.0), lm2_v3_make_f64(4.0, 5.0, 6.0));
  lm2_r3_f64 b = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(0.5, 1.0, 1.5), lm2_v3_make_f64(1.5, 2.0, 2.5));
  lm2_r3_f64 result = lm2_r3_add_f64(a, b);

  EXPECT_DOUBLE_EQ(result.min.x, 1.5);
  EXPECT_DOUBLE_EQ(result.min.y, 3.0);
  EXPECT_DOUBLE_EQ(result.min.z, 4.5);
  EXPECT_DOUBLE_EQ(result.max.x, 5.5);
  EXPECT_DOUBLE_EQ(result.max.y, 7.0);
  EXPECT_DOUBLE_EQ(result.max.z, 8.5);
}

TEST_F(Range3Test, AddScalar_F64) {
  lm2_r3_f64 r = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(1.0, 2.0, 3.0), lm2_v3_make_f64(4.0, 5.0, 6.0));
  lm2_r3_f64 result = lm2_r3_add_s_f64(r, 2.0);

  EXPECT_DOUBLE_EQ(result.min.x, 3.0);
  EXPECT_DOUBLE_EQ(result.min.y, 4.0);
  EXPECT_DOUBLE_EQ(result.min.z, 5.0);
  EXPECT_DOUBLE_EQ(result.max.x, 6.0);
  EXPECT_DOUBLE_EQ(result.max.y, 7.0);
  EXPECT_DOUBLE_EQ(result.max.z, 8.0);
}

TEST_F(Range3Test, AddVector_F64) {
  lm2_r3_f64 r = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(1.0, 2.0, 3.0), lm2_v3_make_f64(4.0, 5.0, 6.0));
  lm2_v3_f64 v = lm2_v3_make_f64(1.0, -1.0, 2.0);
  lm2_r3_f64 result = lm2_r3_add_v_f64(r, v);

  EXPECT_DOUBLE_EQ(result.min.x, 2.0);
  EXPECT_DOUBLE_EQ(result.min.y, 1.0);
  EXPECT_DOUBLE_EQ(result.min.z, 5.0);
  EXPECT_DOUBLE_EQ(result.max.x, 5.0);
  EXPECT_DOUBLE_EQ(result.max.y, 4.0);
  EXPECT_DOUBLE_EQ(result.max.z, 8.0);
}

TEST_F(Range3Test, Sub_F64) {
  lm2_r3_f64 a = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(5.0, 6.0, 7.0), lm2_v3_make_f64(10.0, 12.0, 14.0));
  lm2_r3_f64 b = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(1.0, 2.0, 3.0), lm2_v3_make_f64(3.0, 4.0, 5.0));
  lm2_r3_f64 result = lm2_r3_sub_f64(a, b);

  EXPECT_DOUBLE_EQ(result.min.x, 4.0);
  EXPECT_DOUBLE_EQ(result.min.y, 4.0);
  EXPECT_DOUBLE_EQ(result.min.z, 4.0);
  EXPECT_DOUBLE_EQ(result.max.x, 7.0);
  EXPECT_DOUBLE_EQ(result.max.y, 8.0);
  EXPECT_DOUBLE_EQ(result.max.z, 9.0);
}

TEST_F(Range3Test, Mul_F64) {
  lm2_r3_f64 a = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(2.0, 3.0, 4.0), lm2_v3_make_f64(4.0, 5.0, 6.0));
  lm2_r3_f64 b = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(1.0, 2.0, 1.5), lm2_v3_make_f64(2.0, 3.0, 2.0));
  lm2_r3_f64 result = lm2_r3_mul_f64(a, b);

  EXPECT_DOUBLE_EQ(result.min.x, 2.0);
  EXPECT_DOUBLE_EQ(result.min.y, 6.0);
  EXPECT_DOUBLE_EQ(result.min.z, 6.0);
  EXPECT_DOUBLE_EQ(result.max.x, 8.0);
  EXPECT_DOUBLE_EQ(result.max.y, 15.0);
  EXPECT_DOUBLE_EQ(result.max.z, 12.0);
}

TEST_F(Range3Test, MulScalar_F64) {
  lm2_r3_f64 r = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(1.0, 2.0, 3.0), lm2_v3_make_f64(4.0, 5.0, 6.0));
  lm2_r3_f64 result = lm2_r3_mul_s_f64(r, 2.0);

  EXPECT_DOUBLE_EQ(result.min.x, 2.0);
  EXPECT_DOUBLE_EQ(result.min.y, 4.0);
  EXPECT_DOUBLE_EQ(result.min.z, 6.0);
  EXPECT_DOUBLE_EQ(result.max.x, 8.0);
  EXPECT_DOUBLE_EQ(result.max.y, 10.0);
  EXPECT_DOUBLE_EQ(result.max.z, 12.0);
}

TEST_F(Range3Test, DivScalar_F64) {
  lm2_r3_f64 r = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(2.0, 4.0, 6.0), lm2_v3_make_f64(8.0, 10.0, 12.0));
  lm2_r3_f64 result = lm2_r3_div_s_f64(r, 2.0);

  EXPECT_DOUBLE_EQ(result.min.x, 1.0);
  EXPECT_DOUBLE_EQ(result.min.y, 2.0);
  EXPECT_DOUBLE_EQ(result.min.z, 3.0);
  EXPECT_DOUBLE_EQ(result.max.x, 4.0);
  EXPECT_DOUBLE_EQ(result.max.y, 5.0);
  EXPECT_DOUBLE_EQ(result.max.z, 6.0);
}

// =============================================================================
// Operations (f64)
// =============================================================================

TEST_F(Range3Test, Translate_F64) {
  lm2_r3_f64 r = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(1.0, 2.0, 3.0), lm2_v3_make_f64(5.0, 6.0, 7.0));
  lm2_v3_f64 offset = lm2_v3_make_f64(10.0, 20.0, 30.0);
  lm2_r3_f64 result = lm2_r3_translate_f64(r, offset);

  EXPECT_DOUBLE_EQ(result.min.x, 11.0);
  EXPECT_DOUBLE_EQ(result.min.y, 22.0);
  EXPECT_DOUBLE_EQ(result.min.z, 33.0);
  EXPECT_DOUBLE_EQ(result.max.x, 15.0);
  EXPECT_DOUBLE_EQ(result.max.y, 26.0);
  EXPECT_DOUBLE_EQ(result.max.z, 37.0);
}

TEST_F(Range3Test, Scale_F64) {
  lm2_r3_f64 r = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(2.0, 4.0, 6.0), lm2_v3_make_f64(4.0, 8.0, 10.0));
  lm2_r3_f64 result = lm2_r3_scale_f64(r, 2.0);

  // Scale from center: center = (3, 6, 8), size = (2, 4, 4)
  // new size = (4, 8, 8), so new min = (1, 2, 4), new max = (5, 10, 12)
  EXPECT_DOUBLE_EQ(result.min.x, 1.0);
  EXPECT_DOUBLE_EQ(result.min.y, 2.0);
  EXPECT_DOUBLE_EQ(result.min.z, 4.0);
  EXPECT_DOUBLE_EQ(result.max.x, 5.0);
  EXPECT_DOUBLE_EQ(result.max.y, 10.0);
  EXPECT_DOUBLE_EQ(result.max.z, 12.0);
}

TEST_F(Range3Test, Expand_F64) {
  lm2_r3_f64 r = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(2.0, 3.0, 4.0), lm2_v3_make_f64(6.0, 7.0, 8.0));
  lm2_r3_f64 result = lm2_r3_expand_f64(r, 1.0);

  EXPECT_DOUBLE_EQ(result.min.x, 1.0);
  EXPECT_DOUBLE_EQ(result.min.y, 2.0);
  EXPECT_DOUBLE_EQ(result.min.z, 3.0);
  EXPECT_DOUBLE_EQ(result.max.x, 7.0);
  EXPECT_DOUBLE_EQ(result.max.y, 8.0);
  EXPECT_DOUBLE_EQ(result.max.z, 9.0);
}

// =============================================================================
// Scalar Functions (f64)
// =============================================================================

TEST_F(Range3Test, Floor_F64) {
  lm2_r3_f64 r = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(1.7, 2.3, 3.9), lm2_v3_make_f64(4.1, 5.5, 6.2));
  lm2_r3_f64 result = lm2_r3_floor_f64(r);

  EXPECT_DOUBLE_EQ(result.min.x, 1.0);
  EXPECT_DOUBLE_EQ(result.min.y, 2.0);
  EXPECT_DOUBLE_EQ(result.min.z, 3.0);
  EXPECT_DOUBLE_EQ(result.max.x, 4.0);
  EXPECT_DOUBLE_EQ(result.max.y, 5.0);
  EXPECT_DOUBLE_EQ(result.max.z, 6.0);
}

TEST_F(Range3Test, Ceil_F64) {
  lm2_r3_f64 r = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(1.1, 2.3, 3.5), lm2_v3_make_f64(4.9, 5.1, 6.7));
  lm2_r3_f64 result = lm2_r3_ceil_f64(r);

  EXPECT_DOUBLE_EQ(result.min.x, 2.0);
  EXPECT_DOUBLE_EQ(result.min.y, 3.0);
  EXPECT_DOUBLE_EQ(result.min.z, 4.0);
  EXPECT_DOUBLE_EQ(result.max.x, 5.0);
  EXPECT_DOUBLE_EQ(result.max.y, 6.0);
  EXPECT_DOUBLE_EQ(result.max.z, 7.0);
}

TEST_F(Range3Test, Abs_F64) {
  lm2_r3_f64 r = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(-2.0, -3.0, -4.0), lm2_v3_make_f64(5.0, -1.0, 6.0));
  lm2_r3_f64 result = lm2_r3_abs_f64(r);

  EXPECT_DOUBLE_EQ(result.min.x, 2.0);
  EXPECT_DOUBLE_EQ(result.min.y, 3.0);
  EXPECT_DOUBLE_EQ(result.min.z, 4.0);
  EXPECT_DOUBLE_EQ(result.max.x, 5.0);
  EXPECT_DOUBLE_EQ(result.max.y, 1.0);
  EXPECT_DOUBLE_EQ(result.max.z, 6.0);
}

TEST_F(Range3Test, Min_F64) {
  lm2_r3_f64 a = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(1.0, 5.0, 3.0), lm2_v3_make_f64(8.0, 10.0, 12.0));
  lm2_r3_f64 b = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(2.0, 4.0, 4.0), lm2_v3_make_f64(7.0, 9.0, 15.0));
  lm2_r3_f64 result = lm2_r3_min_f64(a, b);

  EXPECT_DOUBLE_EQ(result.min.x, 1.0);
  EXPECT_DOUBLE_EQ(result.min.y, 4.0);
  EXPECT_DOUBLE_EQ(result.min.z, 3.0);
  EXPECT_DOUBLE_EQ(result.max.x, 7.0);
  EXPECT_DOUBLE_EQ(result.max.y, 9.0);
  EXPECT_DOUBLE_EQ(result.max.z, 12.0);
}

TEST_F(Range3Test, Max_F64) {
  lm2_r3_f64 a = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(1.0, 5.0, 3.0), lm2_v3_make_f64(8.0, 10.0, 12.0));
  lm2_r3_f64 b = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(2.0, 4.0, 4.0), lm2_v3_make_f64(7.0, 9.0, 15.0));
  lm2_r3_f64 result = lm2_r3_max_f64(a, b);

  EXPECT_DOUBLE_EQ(result.min.x, 2.0);
  EXPECT_DOUBLE_EQ(result.min.y, 5.0);
  EXPECT_DOUBLE_EQ(result.min.z, 4.0);
  EXPECT_DOUBLE_EQ(result.max.x, 8.0);
  EXPECT_DOUBLE_EQ(result.max.y, 10.0);
  EXPECT_DOUBLE_EQ(result.max.z, 15.0);
}

// =============================================================================
// Query Functions (f64)
// =============================================================================

TEST_F(Range3Test, Size_F64) {
  lm2_r3_f64 r = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(1.0, 2.0, 3.0), lm2_v3_make_f64(5.0, 7.0, 9.0));
  lm2_v3_f64 size = lm2_r3_size_f64(r);

  EXPECT_DOUBLE_EQ(size.x, 4.0);
  EXPECT_DOUBLE_EQ(size.y, 5.0);
  EXPECT_DOUBLE_EQ(size.z, 6.0);
}

TEST_F(Range3Test, Extents_F64) {
  lm2_r3_f64 r = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(1.0, 2.0, 3.0), lm2_v3_make_f64(5.0, 8.0, 11.0));
  lm2_v3_f64 extents = lm2_r3_extents_f64(r);

  EXPECT_DOUBLE_EQ(extents.x, 2.0);
  EXPECT_DOUBLE_EQ(extents.y, 3.0);
  EXPECT_DOUBLE_EQ(extents.z, 4.0);
}

TEST_F(Range3Test, Center_F64) {
  lm2_r3_f64 r = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(2.0, 4.0, 6.0), lm2_v3_make_f64(8.0, 10.0, 12.0));
  lm2_v3_f64 center = lm2_r3_center_f64(r);

  EXPECT_DOUBLE_EQ(center.x, 5.0);
  EXPECT_DOUBLE_EQ(center.y, 7.0);
  EXPECT_DOUBLE_EQ(center.z, 9.0);
}

TEST_F(Range3Test, Volume_F64) {
  lm2_r3_f64 r = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(1.0, 2.0, 3.0), lm2_v3_make_f64(5.0, 6.0, 7.0));
  double volume = lm2_r3_volume_f64(r);

  EXPECT_DOUBLE_EQ(volume, 64.0);  // (5-1) * (6-2) * (7-3) = 4 * 4 * 4
}

TEST_F(Range3Test, ContainsPoint_F64) {
  lm2_r3_f64 r = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(1.0, 2.0, 3.0), lm2_v3_make_f64(5.0, 6.0, 7.0));

  lm2_v3_f64 inside = lm2_v3_make_f64(3.0, 4.0, 5.0);
  lm2_v3_f64 outside = lm2_v3_make_f64(7.0, 8.0, 9.0);
  lm2_v3_f64 on_edge = lm2_v3_make_f64(1.0, 3.0, 5.0);

  EXPECT_TRUE(lm2_r3_contains_point_f64(r, inside));
  EXPECT_FALSE(lm2_r3_contains_point_f64(r, outside));
  EXPECT_TRUE(lm2_r3_contains_point_f64(r, on_edge));
}

TEST_F(Range3Test, Overlaps_F64) {
  lm2_r3_f64 a = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(1.0, 1.0, 1.0), lm2_v3_make_f64(5.0, 5.0, 5.0));
  lm2_r3_f64 overlapping = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(3.0, 3.0, 3.0), lm2_v3_make_f64(7.0, 7.0, 7.0));
  lm2_r3_f64 non_overlapping = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(6.0, 6.0, 6.0), lm2_v3_make_f64(10.0, 10.0, 10.0));

  EXPECT_TRUE(lm2_r3_overlaps_f64(a, overlapping));
  EXPECT_FALSE(lm2_r3_overlaps_f64(a, non_overlapping));
}

TEST_F(Range3Test, Union_F64) {
  lm2_r3_f64 a = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(1.0, 2.0, 3.0), lm2_v3_make_f64(5.0, 6.0, 7.0));
  lm2_r3_f64 b = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(3.0, 4.0, 5.0), lm2_v3_make_f64(7.0, 8.0, 9.0));
  lm2_r3_f64 result = lm2_r3_union_f64(a, b);

  EXPECT_DOUBLE_EQ(result.min.x, 1.0);
  EXPECT_DOUBLE_EQ(result.min.y, 2.0);
  EXPECT_DOUBLE_EQ(result.min.z, 3.0);
  EXPECT_DOUBLE_EQ(result.max.x, 7.0);
  EXPECT_DOUBLE_EQ(result.max.y, 8.0);
  EXPECT_DOUBLE_EQ(result.max.z, 9.0);
}

TEST_F(Range3Test, Intersection_F64) {
  lm2_r3_f64 a = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(1.0, 1.0, 1.0), lm2_v3_make_f64(5.0, 5.0, 5.0));
  lm2_r3_f64 b = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(3.0, 3.0, 3.0), lm2_v3_make_f64(7.0, 7.0, 7.0));
  lm2_r3_f64 result = lm2_r3_intersection_f64(a, b);

  EXPECT_DOUBLE_EQ(result.min.x, 3.0);
  EXPECT_DOUBLE_EQ(result.min.y, 3.0);
  EXPECT_DOUBLE_EQ(result.min.z, 3.0);
  EXPECT_DOUBLE_EQ(result.max.x, 5.0);
  EXPECT_DOUBLE_EQ(result.max.y, 5.0);
  EXPECT_DOUBLE_EQ(result.max.z, 5.0);
}

// =============================================================================
// Integer Type Tests (i32)
// =============================================================================

TEST_F(Range3Test, ArithmeticOps_I32) {
  lm2_r3_i32 a = lm2_r3_from_min_max_i32(
      lm2_v3_make_i32(1, 2, 3), lm2_v3_make_i32(5, 6, 7));
  lm2_r3_i32 b = lm2_r3_from_min_max_i32(
      lm2_v3_make_i32(2, 3, 4), lm2_v3_make_i32(4, 5, 6));

  lm2_r3_i32 add_result = lm2_r3_add_i32(a, b);
  EXPECT_EQ(add_result.min.x, 3);
  EXPECT_EQ(add_result.min.y, 5);
  EXPECT_EQ(add_result.min.z, 7);
  EXPECT_EQ(add_result.max.x, 9);
  EXPECT_EQ(add_result.max.y, 11);
  EXPECT_EQ(add_result.max.z, 13);

  lm2_r3_i32 mul_result = lm2_r3_mul_s_i32(a, 2);
  EXPECT_EQ(mul_result.min.x, 2);
  EXPECT_EQ(mul_result.min.y, 4);
  EXPECT_EQ(mul_result.min.z, 6);
  EXPECT_EQ(mul_result.max.x, 10);
  EXPECT_EQ(mul_result.max.y, 12);
  EXPECT_EQ(mul_result.max.z, 14);
}

TEST_F(Range3Test, ContainsPoint_I32) {
  lm2_r3_i32 r = lm2_r3_from_min_max_i32(
      lm2_v3_make_i32(0, 0, 0), lm2_v3_make_i32(10, 10, 10));

  lm2_v3_i32 inside = lm2_v3_make_i32(5, 5, 5);
  lm2_v3_i32 outside = lm2_v3_make_i32(15, 15, 15);

  EXPECT_TRUE(lm2_r3_contains_point_i32(r, inside));
  EXPECT_FALSE(lm2_r3_contains_point_i32(r, outside));
}
