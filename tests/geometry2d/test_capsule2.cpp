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
#include "lm2/geometry2d/lm2_capsule2.h"
#include "lm2/lm2_constants.h"

// Test fixture for Capsule2 tests
class Capsule2Test : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Construction Tests (f64)
// =============================================================================

TEST_F(Capsule2Test, Make_F64) {
  lm2_v2_f64 start = lm2_v2_make_f64(0.0, 0.0);
  lm2_v2_f64 end = lm2_v2_make_f64(10.0, 0.0);
  lm2_capsule2_f64 capsule = lm2_capsule2_make_f64(start, end, 2.0);

  EXPECT_DOUBLE_EQ(capsule.start.x, 0.0);
  EXPECT_DOUBLE_EQ(capsule.start.y, 0.0);
  EXPECT_DOUBLE_EQ(capsule.end.x, 10.0);
  EXPECT_DOUBLE_EQ(capsule.end.y, 0.0);
  EXPECT_DOUBLE_EQ(capsule.radius, 2.0);
}

TEST_F(Capsule2Test, MakeCoords_F64) {
  lm2_capsule2_f64 capsule = lm2_capsule2_make_coords_f64(1.0, 2.0, 5.0, 6.0, 3.0);

  EXPECT_DOUBLE_EQ(capsule.start.x, 1.0);
  EXPECT_DOUBLE_EQ(capsule.start.y, 2.0);
  EXPECT_DOUBLE_EQ(capsule.end.x, 5.0);
  EXPECT_DOUBLE_EQ(capsule.end.y, 6.0);
  EXPECT_DOUBLE_EQ(capsule.radius, 3.0);
}

TEST_F(Capsule2Test, FromCenter_F64) {
  lm2_v2_f64 center = lm2_v2_make_f64(5.0, 5.0);
  lm2_v2_f64 direction = lm2_v2_make_f64(1.0, 0.0);
  lm2_capsule2_f64 capsule = lm2_capsule2_from_center_f64(center, direction, 3.0, 1.5);

  EXPECT_DOUBLE_EQ(capsule.start.x, 2.0);
  EXPECT_DOUBLE_EQ(capsule.start.y, 5.0);
  EXPECT_DOUBLE_EQ(capsule.end.x, 8.0);
  EXPECT_DOUBLE_EQ(capsule.end.y, 5.0);
  EXPECT_DOUBLE_EQ(capsule.radius, 1.5);
}

// =============================================================================
// Construction Tests (f32)
// =============================================================================

TEST_F(Capsule2Test, Make_F32) {
  lm2_v2_f32 start = lm2_v2_make_f32(0.0f, 0.0f);
  lm2_v2_f32 end = lm2_v2_make_f32(10.0f, 0.0f);
  lm2_capsule2_f32 capsule = lm2_capsule2_make_f32(start, end, 2.0f);

  EXPECT_FLOAT_EQ(capsule.start.x, 0.0f);
  EXPECT_FLOAT_EQ(capsule.start.y, 0.0f);
  EXPECT_FLOAT_EQ(capsule.end.x, 10.0f);
  EXPECT_FLOAT_EQ(capsule.end.y, 0.0f);
  EXPECT_FLOAT_EQ(capsule.radius, 2.0f);
}

TEST_F(Capsule2Test, MakeCoords_F32) {
  lm2_capsule2_f32 capsule = lm2_capsule2_make_coords_f32(1.0f, 2.0f, 5.0f, 6.0f, 3.0f);

  EXPECT_FLOAT_EQ(capsule.start.x, 1.0f);
  EXPECT_FLOAT_EQ(capsule.start.y, 2.0f);
  EXPECT_FLOAT_EQ(capsule.end.x, 5.0f);
  EXPECT_FLOAT_EQ(capsule.end.y, 6.0f);
  EXPECT_FLOAT_EQ(capsule.radius, 3.0f);
}

TEST_F(Capsule2Test, FromCenter_F32) {
  lm2_v2_f32 center = lm2_v2_make_f32(5.0f, 5.0f);
  lm2_v2_f32 direction = lm2_v2_make_f32(1.0f, 0.0f);
  lm2_capsule2_f32 capsule = lm2_capsule2_from_center_f32(center, direction, 3.0f, 1.5f);

  EXPECT_FLOAT_EQ(capsule.start.x, 2.0f);
  EXPECT_FLOAT_EQ(capsule.start.y, 5.0f);
  EXPECT_FLOAT_EQ(capsule.end.x, 8.0f);
  EXPECT_FLOAT_EQ(capsule.end.y, 5.0f);
  EXPECT_FLOAT_EQ(capsule.radius, 1.5f);
}

// =============================================================================
// Property Tests (f64)
// =============================================================================

TEST_F(Capsule2Test, Length_F64) {
  lm2_capsule2_f64 capsule = lm2_capsule2_make_coords_f64(0.0, 0.0, 3.0, 4.0, 1.0);
  double length = lm2_capsule2_length_f64(capsule);
  EXPECT_DOUBLE_EQ(length, 5.0);  // 3-4-5 triangle
}

TEST_F(Capsule2Test, TotalLength_F64) {
  lm2_capsule2_f64 capsule = lm2_capsule2_make_coords_f64(0.0, 0.0, 10.0, 0.0, 2.0);
  double total_length = lm2_capsule2_total_length_f64(capsule);
  EXPECT_DOUBLE_EQ(total_length, 14.0);  // 10 + 2*2
}

TEST_F(Capsule2Test, Area_F64) {
  lm2_capsule2_f64 capsule = lm2_capsule2_make_coords_f64(0.0, 0.0, 10.0, 0.0, 2.0);
  double area = lm2_capsule2_area_f64(capsule);
  // Area = rectangle (length * 2*radius) + circle (pi * radius^2)
  double expected = 10.0 * 2.0 * 2.0 + LM2_PI_F64 * 2.0 * 2.0;
  EXPECT_NEAR(area, expected, EPSILON_F64);
}

TEST_F(Capsule2Test, Perimeter_F64) {
  lm2_capsule2_f64 capsule = lm2_capsule2_make_coords_f64(0.0, 0.0, 10.0, 0.0, 2.0);
  double perimeter = lm2_capsule2_perimeter_f64(capsule);
  // Perimeter = 2 * length + circumference
  double expected = 2.0 * 10.0 + 2.0 * LM2_PI_F64 * 2.0;
  EXPECT_NEAR(perimeter, expected, EPSILON_F64);
}

TEST_F(Capsule2Test, Center_F64) {
  lm2_capsule2_f64 capsule = lm2_capsule2_make_coords_f64(0.0, 0.0, 10.0, 0.0, 2.0);
  lm2_v2_f64 center = lm2_capsule2_center_f64(capsule);
  EXPECT_DOUBLE_EQ(center.x, 5.0);
  EXPECT_DOUBLE_EQ(center.y, 0.0);
}

// =============================================================================
// Property Tests (f32)
// =============================================================================

TEST_F(Capsule2Test, Length_F32) {
  lm2_capsule2_f32 capsule = lm2_capsule2_make_coords_f32(0.0f, 0.0f, 3.0f, 4.0f, 1.0f);
  float length = lm2_capsule2_length_f32(capsule);
  EXPECT_FLOAT_EQ(length, 5.0f);
}

TEST_F(Capsule2Test, TotalLength_F32) {
  lm2_capsule2_f32 capsule = lm2_capsule2_make_coords_f32(0.0f, 0.0f, 10.0f, 0.0f, 2.0f);
  float total_length = lm2_capsule2_total_length_f32(capsule);
  EXPECT_FLOAT_EQ(total_length, 14.0f);
}

TEST_F(Capsule2Test, Area_F32) {
  lm2_capsule2_f32 capsule = lm2_capsule2_make_coords_f32(0.0f, 0.0f, 10.0f, 0.0f, 2.0f);
  float area = lm2_capsule2_area_f32(capsule);
  float expected = 10.0f * 2.0f * 2.0f + LM2_PI_F32 * 2.0f * 2.0f;
  EXPECT_NEAR(area, expected, EPSILON_F32);
}

TEST_F(Capsule2Test, Perimeter_F32) {
  lm2_capsule2_f32 capsule = lm2_capsule2_make_coords_f32(0.0f, 0.0f, 10.0f, 0.0f, 2.0f);
  float perimeter = lm2_capsule2_perimeter_f32(capsule);
  float expected = 2.0f * 10.0f + 2.0f * LM2_PI_F32 * 2.0f;
  EXPECT_NEAR(perimeter, expected, EPSILON_F32);
}

TEST_F(Capsule2Test, Center_F32) {
  lm2_capsule2_f32 capsule = lm2_capsule2_make_coords_f32(0.0f, 0.0f, 10.0f, 0.0f, 2.0f);
  lm2_v2_f32 center = lm2_capsule2_center_f32(capsule);
  EXPECT_FLOAT_EQ(center.x, 5.0f);
  EXPECT_FLOAT_EQ(center.y, 0.0f);
}

// =============================================================================
// Containment Tests (f64)
// =============================================================================

TEST_F(Capsule2Test, ContainsPoint_InsideMiddle_F64) {
  lm2_capsule2_f64 capsule = lm2_capsule2_make_coords_f64(0.0, 0.0, 10.0, 0.0, 2.0);
  lm2_v2_f64 point = lm2_v2_make_f64(5.0, 1.0);
  EXPECT_TRUE(lm2_capsule2_contains_point_f64(capsule, point));
}

TEST_F(Capsule2Test, ContainsPoint_InsideEnd_F64) {
  lm2_capsule2_f64 capsule = lm2_capsule2_make_coords_f64(0.0, 0.0, 10.0, 0.0, 2.0);
  lm2_v2_f64 point = lm2_v2_make_f64(11.0, 0.0);
  EXPECT_TRUE(lm2_capsule2_contains_point_f64(capsule, point));
}

TEST_F(Capsule2Test, ContainsPoint_Outside_F64) {
  lm2_capsule2_f64 capsule = lm2_capsule2_make_coords_f64(0.0, 0.0, 10.0, 0.0, 2.0);
  lm2_v2_f64 point = lm2_v2_make_f64(5.0, 5.0);
  EXPECT_FALSE(lm2_capsule2_contains_point_f64(capsule, point));
}

TEST_F(Capsule2Test, ContainsPoint_OnEdge_F64) {
  lm2_capsule2_f64 capsule = lm2_capsule2_make_coords_f64(0.0, 0.0, 10.0, 0.0, 2.0);
  lm2_v2_f64 point = lm2_v2_make_f64(5.0, 2.0);
  EXPECT_TRUE(lm2_capsule2_contains_point_f64(capsule, point));
}

// =============================================================================
// Containment Tests (f32)
// =============================================================================

TEST_F(Capsule2Test, ContainsPoint_InsideMiddle_F32) {
  lm2_capsule2_f32 capsule = lm2_capsule2_make_coords_f32(0.0f, 0.0f, 10.0f, 0.0f, 2.0f);
  lm2_v2_f32 point = lm2_v2_make_f32(5.0f, 1.0f);
  EXPECT_TRUE(lm2_capsule2_contains_point_f32(capsule, point));
}

TEST_F(Capsule2Test, ContainsPoint_Outside_F32) {
  lm2_capsule2_f32 capsule = lm2_capsule2_make_coords_f32(0.0f, 0.0f, 10.0f, 0.0f, 2.0f);
  lm2_v2_f32 point = lm2_v2_make_f32(5.0f, 5.0f);
  EXPECT_FALSE(lm2_capsule2_contains_point_f32(capsule, point));
}

// =============================================================================
// Capsule Overlap Tests (f64)
// =============================================================================

TEST_F(Capsule2Test, CapsulesOverlap_Separated_F64) {
  lm2_capsule2_f64 a = lm2_capsule2_make_coords_f64(0.0, 0.0, 5.0, 0.0, 1.0);
  lm2_capsule2_f64 b = lm2_capsule2_make_coords_f64(10.0, 0.0, 15.0, 0.0, 1.0);
  EXPECT_FALSE(lm2_capsule2s_overlap_f64(a, b));
}

TEST_F(Capsule2Test, CapsulesOverlap_Intersecting_F64) {
  lm2_capsule2_f64 a = lm2_capsule2_make_coords_f64(0.0, 0.0, 5.0, 0.0, 2.0);
  lm2_capsule2_f64 b = lm2_capsule2_make_coords_f64(3.0, 0.0, 8.0, 0.0, 2.0);
  EXPECT_TRUE(lm2_capsule2s_overlap_f64(a, b));
}

TEST_F(Capsule2Test, CapsulesOverlap_Parallel_F64) {
  lm2_capsule2_f64 a = lm2_capsule2_make_coords_f64(0.0, 0.0, 5.0, 0.0, 2.0);
  lm2_capsule2_f64 b = lm2_capsule2_make_coords_f64(0.0, 3.0, 5.0, 3.0, 2.0);
  EXPECT_TRUE(lm2_capsule2s_overlap_f64(a, b));
}

// =============================================================================
// Capsule Overlap Tests (f32)
// =============================================================================

TEST_F(Capsule2Test, CapsulesOverlap_Separated_F32) {
  lm2_capsule2_f32 a = lm2_capsule2_make_coords_f32(0.0f, 0.0f, 5.0f, 0.0f, 1.0f);
  lm2_capsule2_f32 b = lm2_capsule2_make_coords_f32(10.0f, 0.0f, 15.0f, 0.0f, 1.0f);
  EXPECT_FALSE(lm2_capsule2s_overlap_f32(a, b));
}

TEST_F(Capsule2Test, CapsulesOverlap_Intersecting_F32) {
  lm2_capsule2_f32 a = lm2_capsule2_make_coords_f32(0.0f, 0.0f, 5.0f, 0.0f, 2.0f);
  lm2_capsule2_f32 b = lm2_capsule2_make_coords_f32(3.0f, 0.0f, 8.0f, 0.0f, 2.0f);
  EXPECT_TRUE(lm2_capsule2s_overlap_f32(a, b));
}
