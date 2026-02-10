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
#include "lm2/ranges/lm2_range2.h"

// Test fixture for range2 tests
class Range2Test : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-6f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Constructor Tests (f64)
// =============================================================================

TEST_F(Range2Test, FromMinMax_F64) {
  lm2_v2_f64 min = lm2_v2_make_f64(1.0, 2.0);
  lm2_v2_f64 max = lm2_v2_make_f64(5.0, 6.0);
  lm2_r2_f64 r = lm2_r2_from_min_max_f64(min, max);

  EXPECT_DOUBLE_EQ(r.min.x, 1.0);
  EXPECT_DOUBLE_EQ(r.min.y, 2.0);
  EXPECT_DOUBLE_EQ(r.max.x, 5.0);
  EXPECT_DOUBLE_EQ(r.max.y, 6.0);
}

TEST_F(Range2Test, FromCenterExtents_F64) {
  lm2_v2_f64 center = lm2_v2_make_f64(3.0, 4.0);
  lm2_v2_f64 extents = lm2_v2_make_f64(2.0, 1.0);
  lm2_r2_f64 r = lm2_r2_from_center_extents_f64(center, extents);

  EXPECT_DOUBLE_EQ(r.min.x, 1.0);  // 3 - 2
  EXPECT_DOUBLE_EQ(r.min.y, 3.0);  // 4 - 1
  EXPECT_DOUBLE_EQ(r.max.x, 5.0);  // 3 + 2
  EXPECT_DOUBLE_EQ(r.max.y, 5.0);  // 4 + 1
}

TEST_F(Range2Test, FromCenterSize_F64) {
  lm2_v2_f64 center = lm2_v2_make_f64(5.0, 5.0);
  lm2_v2_f64 size = lm2_v2_make_f64(4.0, 2.0);
  lm2_r2_f64 r = lm2_r2_from_center_size_f64(center, size);

  EXPECT_DOUBLE_EQ(r.min.x, 3.0);  // 5 - 2
  EXPECT_DOUBLE_EQ(r.min.y, 4.0);  // 5 - 1
  EXPECT_DOUBLE_EQ(r.max.x, 7.0);  // 5 + 2
  EXPECT_DOUBLE_EQ(r.max.y, 6.0);  // 5 + 1
}

TEST_F(Range2Test, FromPositionSize_F64) {
  lm2_v2_f64 position = lm2_v2_make_f64(2.0, 3.0);
  lm2_v2_f64 size = lm2_v2_make_f64(4.0, 5.0);
  lm2_r2_f64 r = lm2_r2_from_position_size_f64(position, size);

  EXPECT_DOUBLE_EQ(r.min.x, 2.0);
  EXPECT_DOUBLE_EQ(r.min.y, 3.0);
  EXPECT_DOUBLE_EQ(r.max.x, 6.0);  // 2 + 4
  EXPECT_DOUBLE_EQ(r.max.y, 8.0);  // 3 + 5
}

TEST_F(Range2Test, Zero_F64) {
  lm2_r2_f64 r = lm2_r2_zero_f64();

  EXPECT_DOUBLE_EQ(r.min.x, 0.0);
  EXPECT_DOUBLE_EQ(r.min.y, 0.0);
  EXPECT_DOUBLE_EQ(r.max.x, 0.0);
  EXPECT_DOUBLE_EQ(r.max.y, 0.0);
}

// =============================================================================
// Constructor Tests (f32)
// =============================================================================

TEST_F(Range2Test, FromMinMax_F32) {
  lm2_v2_f32 min = lm2_v2_make_f32(1.0f, 2.0f);
  lm2_v2_f32 max = lm2_v2_make_f32(5.0f, 6.0f);
  lm2_r2_f32 r = lm2_r2_from_min_max_f32(min, max);

  EXPECT_FLOAT_EQ(r.min.x, 1.0f);
  EXPECT_FLOAT_EQ(r.min.y, 2.0f);
  EXPECT_FLOAT_EQ(r.max.x, 5.0f);
  EXPECT_FLOAT_EQ(r.max.y, 6.0f);
}

TEST_F(Range2Test, FromCenterExtents_F32) {
  lm2_v2_f32 center = lm2_v2_make_f32(3.0f, 4.0f);
  lm2_v2_f32 extents = lm2_v2_make_f32(2.0f, 1.0f);
  lm2_r2_f32 r = lm2_r2_from_center_extents_f32(center, extents);

  EXPECT_FLOAT_EQ(r.min.x, 1.0f);
  EXPECT_FLOAT_EQ(r.min.y, 3.0f);
  EXPECT_FLOAT_EQ(r.max.x, 5.0f);
  EXPECT_FLOAT_EQ(r.max.y, 5.0f);
}

TEST_F(Range2Test, Zero_F32) {
  lm2_r2_f32 r = lm2_r2_zero_f32();

  EXPECT_FLOAT_EQ(r.min.x, 0.0f);
  EXPECT_FLOAT_EQ(r.min.y, 0.0f);
  EXPECT_FLOAT_EQ(r.max.x, 0.0f);
  EXPECT_FLOAT_EQ(r.max.y, 0.0f);
}

// =============================================================================
// Constructor Tests (i64)
// =============================================================================

TEST_F(Range2Test, FromMinMax_I64) {
  lm2_v2_i64 min = lm2_v2_make_i64(1, 2);
  lm2_v2_i64 max = lm2_v2_make_i64(5, 6);
  lm2_r2_i64 r = lm2_r2_from_min_max_i64(min, max);

  EXPECT_EQ(r.min.x, 1);
  EXPECT_EQ(r.min.y, 2);
  EXPECT_EQ(r.max.x, 5);
  EXPECT_EQ(r.max.y, 6);
}

TEST_F(Range2Test, Zero_I64) {
  lm2_r2_i64 r = lm2_r2_zero_i64();

  EXPECT_EQ(r.min.x, 0);
  EXPECT_EQ(r.min.y, 0);
  EXPECT_EQ(r.max.x, 0);
  EXPECT_EQ(r.max.y, 0);
}

// =============================================================================
// Arithmetic Operations (f64)
// =============================================================================

TEST_F(Range2Test, Add_F64) {
  lm2_r2_f64 a = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(1.0, 2.0), lm2_v2_make_f64(3.0, 4.0));
  lm2_r2_f64 b = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(0.5, 1.0), lm2_v2_make_f64(1.5, 2.0));
  lm2_r2_f64 result = lm2_r2_add_f64(a, b);

  EXPECT_DOUBLE_EQ(result.min.x, 1.5);
  EXPECT_DOUBLE_EQ(result.min.y, 3.0);
  EXPECT_DOUBLE_EQ(result.max.x, 4.5);
  EXPECT_DOUBLE_EQ(result.max.y, 6.0);
}

TEST_F(Range2Test, AddScalar_F64) {
  lm2_r2_f64 r = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(1.0, 2.0), lm2_v2_make_f64(3.0, 4.0));
  lm2_r2_f64 result = lm2_r2_add_s_f64(r, 2.0);

  EXPECT_DOUBLE_EQ(result.min.x, 3.0);
  EXPECT_DOUBLE_EQ(result.min.y, 4.0);
  EXPECT_DOUBLE_EQ(result.max.x, 5.0);
  EXPECT_DOUBLE_EQ(result.max.y, 6.0);
}

TEST_F(Range2Test, AddVector_F64) {
  lm2_r2_f64 r = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(1.0, 2.0), lm2_v2_make_f64(3.0, 4.0));
  lm2_v2_f64 v = lm2_v2_make_f64(1.0, -1.0);
  lm2_r2_f64 result = lm2_r2_add_v_f64(r, v);

  EXPECT_DOUBLE_EQ(result.min.x, 2.0);
  EXPECT_DOUBLE_EQ(result.min.y, 1.0);
  EXPECT_DOUBLE_EQ(result.max.x, 4.0);
  EXPECT_DOUBLE_EQ(result.max.y, 3.0);
}

TEST_F(Range2Test, Sub_F64) {
  lm2_r2_f64 a = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(5.0, 6.0), lm2_v2_make_f64(8.0, 10.0));
  lm2_r2_f64 b = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(1.0, 2.0), lm2_v2_make_f64(3.0, 4.0));
  lm2_r2_f64 result = lm2_r2_sub_f64(a, b);

  EXPECT_DOUBLE_EQ(result.min.x, 4.0);
  EXPECT_DOUBLE_EQ(result.min.y, 4.0);
  EXPECT_DOUBLE_EQ(result.max.x, 5.0);
  EXPECT_DOUBLE_EQ(result.max.y, 6.0);
}

TEST_F(Range2Test, Mul_F64) {
  lm2_r2_f64 a = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(2.0, 3.0), lm2_v2_make_f64(4.0, 5.0));
  lm2_r2_f64 b = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(1.0, 2.0), lm2_v2_make_f64(2.0, 3.0));
  lm2_r2_f64 result = lm2_r2_mul_f64(a, b);

  EXPECT_DOUBLE_EQ(result.min.x, 2.0);
  EXPECT_DOUBLE_EQ(result.min.y, 6.0);
  EXPECT_DOUBLE_EQ(result.max.x, 8.0);
  EXPECT_DOUBLE_EQ(result.max.y, 15.0);
}

TEST_F(Range2Test, MulScalar_F64) {
  lm2_r2_f64 r = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(1.0, 2.0), lm2_v2_make_f64(3.0, 4.0));
  lm2_r2_f64 result = lm2_r2_mul_s_f64(r, 2.0);

  EXPECT_DOUBLE_EQ(result.min.x, 2.0);
  EXPECT_DOUBLE_EQ(result.min.y, 4.0);
  EXPECT_DOUBLE_EQ(result.max.x, 6.0);
  EXPECT_DOUBLE_EQ(result.max.y, 8.0);
}

TEST_F(Range2Test, Div_F64) {
  lm2_r2_f64 a = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(10.0, 20.0), lm2_v2_make_f64(30.0, 40.0));
  lm2_r2_f64 b = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(2.0, 4.0), lm2_v2_make_f64(5.0, 8.0));
  lm2_r2_f64 result = lm2_r2_div_f64(a, b);

  EXPECT_DOUBLE_EQ(result.min.x, 5.0);
  EXPECT_DOUBLE_EQ(result.min.y, 5.0);
  EXPECT_DOUBLE_EQ(result.max.x, 6.0);
  EXPECT_DOUBLE_EQ(result.max.y, 5.0);
}

TEST_F(Range2Test, DivScalar_F64) {
  lm2_r2_f64 r = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(2.0, 4.0), lm2_v2_make_f64(6.0, 8.0));
  lm2_r2_f64 result = lm2_r2_div_s_f64(r, 2.0);

  EXPECT_DOUBLE_EQ(result.min.x, 1.0);
  EXPECT_DOUBLE_EQ(result.min.y, 2.0);
  EXPECT_DOUBLE_EQ(result.max.x, 3.0);
  EXPECT_DOUBLE_EQ(result.max.y, 4.0);
}

// =============================================================================
// Scalar Functions (f64)
// =============================================================================

TEST_F(Range2Test, Floor_F64) {
  lm2_r2_f64 r = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(1.7, 2.3), lm2_v2_make_f64(3.9, 4.1));
  lm2_r2_f64 result = lm2_r2_floor_f64(r);

  EXPECT_DOUBLE_EQ(result.min.x, 1.0);
  EXPECT_DOUBLE_EQ(result.min.y, 2.0);
  EXPECT_DOUBLE_EQ(result.max.x, 3.0);
  EXPECT_DOUBLE_EQ(result.max.y, 4.0);
}

TEST_F(Range2Test, Ceil_F64) {
  lm2_r2_f64 r = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(1.1, 2.3), lm2_v2_make_f64(3.5, 4.9));
  lm2_r2_f64 result = lm2_r2_ceil_f64(r);

  EXPECT_DOUBLE_EQ(result.min.x, 2.0);
  EXPECT_DOUBLE_EQ(result.min.y, 3.0);
  EXPECT_DOUBLE_EQ(result.max.x, 4.0);
  EXPECT_DOUBLE_EQ(result.max.y, 5.0);
}

TEST_F(Range2Test, Abs_F64) {
  lm2_r2_f64 r = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(-2.0, -3.0), lm2_v2_make_f64(4.0, -1.0));
  lm2_r2_f64 result = lm2_r2_abs_f64(r);

  EXPECT_DOUBLE_EQ(result.min.x, 2.0);
  EXPECT_DOUBLE_EQ(result.min.y, 3.0);
  EXPECT_DOUBLE_EQ(result.max.x, 4.0);
  EXPECT_DOUBLE_EQ(result.max.y, 1.0);
}

TEST_F(Range2Test, Min_F64) {
  lm2_r2_f64 a = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(1.0, 5.0), lm2_v2_make_f64(3.0, 8.0));
  lm2_r2_f64 b = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(2.0, 4.0), lm2_v2_make_f64(4.0, 7.0));
  lm2_r2_f64 result = lm2_r2_min_f64(a, b);

  EXPECT_DOUBLE_EQ(result.min.x, 1.0);
  EXPECT_DOUBLE_EQ(result.min.y, 4.0);
  EXPECT_DOUBLE_EQ(result.max.x, 3.0);
  EXPECT_DOUBLE_EQ(result.max.y, 7.0);
}

TEST_F(Range2Test, Max_F64) {
  lm2_r2_f64 a = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(1.0, 5.0), lm2_v2_make_f64(3.0, 8.0));
  lm2_r2_f64 b = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(2.0, 4.0), lm2_v2_make_f64(4.0, 7.0));
  lm2_r2_f64 result = lm2_r2_max_f64(a, b);

  EXPECT_DOUBLE_EQ(result.min.x, 2.0);
  EXPECT_DOUBLE_EQ(result.min.y, 5.0);
  EXPECT_DOUBLE_EQ(result.max.x, 4.0);
  EXPECT_DOUBLE_EQ(result.max.y, 8.0);
}

TEST_F(Range2Test, Clamp_F64) {
  lm2_r2_f64 value = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(0.5, 5.0), lm2_v2_make_f64(3.5, 12.0));
  lm2_r2_f64 min_val = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(1.0, 1.0), lm2_v2_make_f64(2.0, 2.0));
  lm2_r2_f64 max_val = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(3.0, 8.0), lm2_v2_make_f64(5.0, 10.0));
  lm2_r2_f64 result = lm2_r2_clamp_f64(value, min_val, max_val);

  EXPECT_DOUBLE_EQ(result.min.x, 1.0);
  EXPECT_DOUBLE_EQ(result.min.y, 5.0);
  EXPECT_DOUBLE_EQ(result.max.x, 3.5);
  EXPECT_DOUBLE_EQ(result.max.y, 10.0);
}

TEST_F(Range2Test, Lerp_F64) {
  lm2_r2_f64 a = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(2.0, 2.0));
  lm2_r2_f64 b = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(10.0, 10.0), lm2_v2_make_f64(20.0, 20.0));
  lm2_r2_f64 t = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(0.5, 0.25), lm2_v2_make_f64(0.5, 0.75));
  lm2_r2_f64 result = lm2_r2_lerp_f64(a, b, t);

  EXPECT_DOUBLE_EQ(result.min.x, 5.0);   // 0 + 0.5 * (10 - 0)
  EXPECT_DOUBLE_EQ(result.min.y, 2.5);   // 0 + 0.25 * (10 - 0)
  EXPECT_DOUBLE_EQ(result.max.x, 11.0);  // 2 + 0.5 * (20 - 2)
  EXPECT_DOUBLE_EQ(result.max.y, 15.5);  // 2 + 0.75 * (20 - 2)
}

// =============================================================================
// Query Functions (f64)
// =============================================================================

TEST_F(Range2Test, Size_F64) {
  lm2_r2_f64 r = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(1.0, 2.0), lm2_v2_make_f64(5.0, 7.0));
  lm2_v2_f64 size = lm2_r2_size_f64(r);

  EXPECT_DOUBLE_EQ(size.x, 4.0);
  EXPECT_DOUBLE_EQ(size.y, 5.0);
}

TEST_F(Range2Test, Extents_F64) {
  lm2_r2_f64 r = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(1.0, 2.0), lm2_v2_make_f64(5.0, 8.0));
  lm2_v2_f64 extents = lm2_r2_extents_f64(r);

  EXPECT_DOUBLE_EQ(extents.x, 2.0);
  EXPECT_DOUBLE_EQ(extents.y, 3.0);
}

TEST_F(Range2Test, Center_F64) {
  lm2_r2_f64 r = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(2.0, 4.0), lm2_v2_make_f64(8.0, 10.0));
  lm2_v2_f64 center = lm2_r2_center_f64(r);

  EXPECT_DOUBLE_EQ(center.x, 5.0);
  EXPECT_DOUBLE_EQ(center.y, 7.0);
}

TEST_F(Range2Test, Area_F64) {
  lm2_r2_f64 r = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(1.0, 2.0), lm2_v2_make_f64(5.0, 6.0));
  double area = lm2_r2_area_f64(r);

  EXPECT_DOUBLE_EQ(area, 16.0);  // (5-1) * (6-2) = 4 * 4
}

TEST_F(Range2Test, ContainsPoint_F64) {
  lm2_r2_f64 r = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(1.0, 2.0), lm2_v2_make_f64(5.0, 6.0));

  lm2_v2_f64 inside = lm2_v2_make_f64(3.0, 4.0);
  lm2_v2_f64 outside = lm2_v2_make_f64(7.0, 8.0);
  lm2_v2_f64 on_edge = lm2_v2_make_f64(1.0, 3.0);

  EXPECT_TRUE(lm2_r2_contains_point_f64(r, inside));
  EXPECT_FALSE(lm2_r2_contains_point_f64(r, outside));
  EXPECT_TRUE(lm2_r2_contains_point_f64(r, on_edge));
}

TEST_F(Range2Test, Overlaps_F64) {
  lm2_r2_f64 a = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(1.0, 1.0), lm2_v2_make_f64(5.0, 5.0));
  lm2_r2_f64 overlapping = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(3.0, 3.0), lm2_v2_make_f64(7.0, 7.0));
  lm2_r2_f64 non_overlapping = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(6.0, 6.0), lm2_v2_make_f64(10.0, 10.0));

  EXPECT_TRUE(lm2_r2_overlaps_f64(a, overlapping));
  EXPECT_FALSE(lm2_r2_overlaps_f64(a, non_overlapping));
}

TEST_F(Range2Test, Union_F64) {
  lm2_r2_f64 a = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(1.0, 2.0), lm2_v2_make_f64(5.0, 6.0));
  lm2_r2_f64 b = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(3.0, 4.0), lm2_v2_make_f64(7.0, 8.0));
  lm2_r2_f64 result = lm2_r2_union_f64(a, b);

  EXPECT_DOUBLE_EQ(result.min.x, 1.0);
  EXPECT_DOUBLE_EQ(result.min.y, 2.0);
  EXPECT_DOUBLE_EQ(result.max.x, 7.0);
  EXPECT_DOUBLE_EQ(result.max.y, 8.0);
}

TEST_F(Range2Test, Intersection_F64) {
  lm2_r2_f64 a = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(1.0, 1.0), lm2_v2_make_f64(5.0, 5.0));
  lm2_r2_f64 b = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(3.0, 3.0), lm2_v2_make_f64(7.0, 7.0));
  lm2_r2_f64 result = lm2_r2_intersection_f64(a, b);

  EXPECT_DOUBLE_EQ(result.min.x, 3.0);
  EXPECT_DOUBLE_EQ(result.min.y, 3.0);
  EXPECT_DOUBLE_EQ(result.max.x, 5.0);
  EXPECT_DOUBLE_EQ(result.max.y, 5.0);
}

// =============================================================================
// Integer Type Tests (i32)
// =============================================================================

TEST_F(Range2Test, ArithmeticOps_I32) {
  lm2_r2_i32 a = lm2_r2_from_min_max_i32(
      lm2_v2_make_i32(1, 2), lm2_v2_make_i32(5, 6));
  lm2_r2_i32 b = lm2_r2_from_min_max_i32(
      lm2_v2_make_i32(2, 3), lm2_v2_make_i32(4, 5));

  lm2_r2_i32 add_result = lm2_r2_add_i32(a, b);
  EXPECT_EQ(add_result.min.x, 3);
  EXPECT_EQ(add_result.min.y, 5);
  EXPECT_EQ(add_result.max.x, 9);
  EXPECT_EQ(add_result.max.y, 11);

  lm2_r2_i32 mul_result = lm2_r2_mul_s_i32(a, 2);
  EXPECT_EQ(mul_result.min.x, 2);
  EXPECT_EQ(mul_result.min.y, 4);
  EXPECT_EQ(mul_result.max.x, 10);
  EXPECT_EQ(mul_result.max.y, 12);
}

TEST_F(Range2Test, ContainsPoint_I32) {
  lm2_r2_i32 r = lm2_r2_from_min_max_i32(
      lm2_v2_make_i32(0, 0), lm2_v2_make_i32(10, 10));

  lm2_v2_i32 inside = lm2_v2_make_i32(5, 5);
  lm2_v2_i32 outside = lm2_v2_make_i32(15, 15);

  EXPECT_TRUE(lm2_r2_contains_point_i32(r, inside));
  EXPECT_FALSE(lm2_r2_contains_point_i32(r, outside));
}
