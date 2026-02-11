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
#include "lm2/geometry2d/lm2_circle.h"
#include "lm2/lm2_constants.h"

// Test fixture for Circle tests
class CircleTest : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Construction Tests (f64)
// =============================================================================

TEST_F(CircleTest, Make_F64) {
  lm2_v2_f64 center = lm2_v2_make_f64(3.0, 4.0);
  lm2_circle_f64 circle = lm2_circle_make_f64(center, 5.0);

  EXPECT_DOUBLE_EQ(circle.center.x, 3.0);
  EXPECT_DOUBLE_EQ(circle.center.y, 4.0);
  EXPECT_DOUBLE_EQ(circle.radius, 5.0);
}

TEST_F(CircleTest, MakeCoords_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(1.0, 2.0, 3.0);

  EXPECT_DOUBLE_EQ(circle.center.x, 1.0);
  EXPECT_DOUBLE_EQ(circle.center.y, 2.0);
  EXPECT_DOUBLE_EQ(circle.radius, 3.0);
}

TEST_F(CircleTest, Unit_F64) {
  lm2_circle_f64 circle = lm2_circle_unit_f64();

  EXPECT_DOUBLE_EQ(circle.center.x, 0.0);
  EXPECT_DOUBLE_EQ(circle.center.y, 0.0);
  EXPECT_DOUBLE_EQ(circle.radius, 1.0);
}

// =============================================================================
// Construction Tests (f32)
// =============================================================================

TEST_F(CircleTest, Make_F32) {
  lm2_v2_f32 center = lm2_v2_make_f32(3.0f, 4.0f);
  lm2_circle_f32 circle = lm2_circle_make_f32(center, 5.0f);

  EXPECT_FLOAT_EQ(circle.center.x, 3.0f);
  EXPECT_FLOAT_EQ(circle.center.y, 4.0f);
  EXPECT_FLOAT_EQ(circle.radius, 5.0f);
}

TEST_F(CircleTest, MakeCoords_F32) {
  lm2_circle_f32 circle = lm2_circle_make_coords_f32(1.0f, 2.0f, 3.0f);

  EXPECT_FLOAT_EQ(circle.center.x, 1.0f);
  EXPECT_FLOAT_EQ(circle.center.y, 2.0f);
  EXPECT_FLOAT_EQ(circle.radius, 3.0f);
}

TEST_F(CircleTest, Unit_F32) {
  lm2_circle_f32 circle = lm2_circle_unit_f32();

  EXPECT_FLOAT_EQ(circle.center.x, 0.0f);
  EXPECT_FLOAT_EQ(circle.center.y, 0.0f);
  EXPECT_FLOAT_EQ(circle.radius, 1.0f);
}

// =============================================================================
// Properties Tests (f64)
// =============================================================================

TEST_F(CircleTest, Area_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(0.0, 0.0, 2.0);
  double area = lm2_circle_area_f64(circle);
  double expected = LM2_PI_F64 * 2.0 * 2.0;
  EXPECT_NEAR(area, expected, EPSILON_F64);
}

TEST_F(CircleTest, Circumference_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(0.0, 0.0, 3.0);
  double circumference = lm2_circle_circumference_f64(circle);
  double expected = 2.0 * LM2_PI_F64 * 3.0;
  EXPECT_NEAR(circumference, expected, EPSILON_F64);
}

TEST_F(CircleTest, Diameter_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(0.0, 0.0, 5.0);
  double diameter = lm2_circle_diameter_f64(circle);
  EXPECT_DOUBLE_EQ(diameter, 10.0);
}

// =============================================================================
// Properties Tests (f32)
// =============================================================================

TEST_F(CircleTest, Area_F32) {
  lm2_circle_f32 circle = lm2_circle_make_coords_f32(0.0f, 0.0f, 2.0f);
  float area = lm2_circle_area_f32(circle);
  float expected = LM2_PI_F32 * 2.0f * 2.0f;
  EXPECT_NEAR(area, expected, EPSILON_F32);
}

TEST_F(CircleTest, Circumference_F32) {
  lm2_circle_f32 circle = lm2_circle_make_coords_f32(0.0f, 0.0f, 3.0f);
  float circumference = lm2_circle_circumference_f32(circle);
  float expected = 2.0f * LM2_PI_F32 * 3.0f;
  EXPECT_NEAR(circumference, expected, EPSILON_F32);
}

TEST_F(CircleTest, Diameter_F32) {
  lm2_circle_f32 circle = lm2_circle_make_coords_f32(0.0f, 0.0f, 5.0f);
  float diameter = lm2_circle_diameter_f32(circle);
  EXPECT_FLOAT_EQ(diameter, 10.0f);
}

// =============================================================================
// Containment Tests (f64)
// =============================================================================

TEST_F(CircleTest, ContainsPoint_Inside_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(0.0, 0.0, 5.0);
  lm2_v2_f64 point = lm2_v2_make_f64(3.0, 0.0);
  EXPECT_TRUE(lm2_circle_contains_point_f64(circle, point));
}

TEST_F(CircleTest, ContainsPoint_Outside_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(0.0, 0.0, 5.0);
  lm2_v2_f64 point = lm2_v2_make_f64(10.0, 0.0);
  EXPECT_FALSE(lm2_circle_contains_point_f64(circle, point));
}

TEST_F(CircleTest, ContainsPoint_OnEdge_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(0.0, 0.0, 5.0);
  lm2_v2_f64 point = lm2_v2_make_f64(5.0, 0.0);
  EXPECT_TRUE(lm2_circle_contains_point_f64(circle, point));
}

TEST_F(CircleTest, ContainsPoint_Center_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(2.0, 3.0, 5.0);
  lm2_v2_f64 point = lm2_v2_make_f64(2.0, 3.0);
  EXPECT_TRUE(lm2_circle_contains_point_f64(circle, point));
}

// =============================================================================
// Containment Tests (f32)
// =============================================================================

TEST_F(CircleTest, ContainsPoint_Inside_F32) {
  lm2_circle_f32 circle = lm2_circle_make_coords_f32(0.0f, 0.0f, 5.0f);
  lm2_v2_f32 point = lm2_v2_make_f32(3.0f, 0.0f);
  EXPECT_TRUE(lm2_circle_contains_point_f32(circle, point));
}

TEST_F(CircleTest, ContainsPoint_Outside_F32) {
  lm2_circle_f32 circle = lm2_circle_make_coords_f32(0.0f, 0.0f, 5.0f);
  lm2_v2_f32 point = lm2_v2_make_f32(10.0f, 0.0f);
  EXPECT_FALSE(lm2_circle_contains_point_f32(circle, point));
}

// =============================================================================
// Circle Overlap Tests (f64)
// =============================================================================

TEST_F(CircleTest, CirclesOverlap_Separated_F64) {
  lm2_circle_f64 a = lm2_circle_make_coords_f64(0.0, 0.0, 2.0);
  lm2_circle_f64 b = lm2_circle_make_coords_f64(10.0, 0.0, 2.0);
  EXPECT_FALSE(lm2_circles_overlap_f64(a, b));
}

TEST_F(CircleTest, CirclesOverlap_Touching_F64) {
  lm2_circle_f64 a = lm2_circle_make_coords_f64(0.0, 0.0, 2.0);
  lm2_circle_f64 b = lm2_circle_make_coords_f64(4.0, 0.0, 2.0);
  EXPECT_TRUE(lm2_circles_overlap_f64(a, b));
}

TEST_F(CircleTest, CirclesOverlap_Intersecting_F64) {
  lm2_circle_f64 a = lm2_circle_make_coords_f64(0.0, 0.0, 3.0);
  lm2_circle_f64 b = lm2_circle_make_coords_f64(4.0, 0.0, 3.0);
  EXPECT_TRUE(lm2_circles_overlap_f64(a, b));
}

TEST_F(CircleTest, CirclesOverlap_OneInsideOther_F64) {
  lm2_circle_f64 a = lm2_circle_make_coords_f64(0.0, 0.0, 10.0);
  lm2_circle_f64 b = lm2_circle_make_coords_f64(2.0, 0.0, 2.0);
  EXPECT_TRUE(lm2_circles_overlap_f64(a, b));
}

// =============================================================================
// Circle Overlap Tests (f32)
// =============================================================================

TEST_F(CircleTest, CirclesOverlap_Separated_F32) {
  lm2_circle_f32 a = lm2_circle_make_coords_f32(0.0f, 0.0f, 2.0f);
  lm2_circle_f32 b = lm2_circle_make_coords_f32(10.0f, 0.0f, 2.0f);
  EXPECT_FALSE(lm2_circles_overlap_f32(a, b));
}

TEST_F(CircleTest, CirclesOverlap_Intersecting_F32) {
  lm2_circle_f32 a = lm2_circle_make_coords_f32(0.0f, 0.0f, 3.0f);
  lm2_circle_f32 b = lm2_circle_make_coords_f32(4.0f, 0.0f, 3.0f);
  EXPECT_TRUE(lm2_circles_overlap_f32(a, b));
}

// =============================================================================
// Circle Contains Circle Tests (f64)
// =============================================================================

TEST_F(CircleTest, CircleContainsCircle_CompletelyInside_F64) {
  lm2_circle_f64 a = lm2_circle_make_coords_f64(0.0, 0.0, 10.0);
  lm2_circle_f64 b = lm2_circle_make_coords_f64(0.0, 0.0, 5.0);
  EXPECT_TRUE(lm2_circle_contains_circle_f64(a, b));
}

TEST_F(CircleTest, CircleContainsCircle_PartiallyInside_F64) {
  lm2_circle_f64 a = lm2_circle_make_coords_f64(0.0, 0.0, 5.0);
  lm2_circle_f64 b = lm2_circle_make_coords_f64(4.0, 0.0, 3.0);
  EXPECT_FALSE(lm2_circle_contains_circle_f64(a, b));
}

TEST_F(CircleTest, CircleContainsCircle_Outside_F64) {
  lm2_circle_f64 a = lm2_circle_make_coords_f64(0.0, 0.0, 2.0);
  lm2_circle_f64 b = lm2_circle_make_coords_f64(10.0, 0.0, 2.0);
  EXPECT_FALSE(lm2_circle_contains_circle_f64(a, b));
}

TEST_F(CircleTest, CircleContainsCircle_Same_F64) {
  lm2_circle_f64 a = lm2_circle_make_coords_f64(0.0, 0.0, 5.0);
  lm2_circle_f64 b = lm2_circle_make_coords_f64(0.0, 0.0, 5.0);
  EXPECT_TRUE(lm2_circle_contains_circle_f64(a, b));
}

// =============================================================================
// Circle Contains Circle Tests (f32)
// =============================================================================

TEST_F(CircleTest, CircleContainsCircle_CompletelyInside_F32) {
  lm2_circle_f32 a = lm2_circle_make_coords_f32(0.0f, 0.0f, 10.0f);
  lm2_circle_f32 b = lm2_circle_make_coords_f32(0.0f, 0.0f, 5.0f);
  EXPECT_TRUE(lm2_circle_contains_circle_f32(a, b));
}

TEST_F(CircleTest, CircleContainsCircle_Outside_F32) {
  lm2_circle_f32 a = lm2_circle_make_coords_f32(0.0f, 0.0f, 2.0f);
  lm2_circle_f32 b = lm2_circle_make_coords_f32(10.0f, 0.0f, 2.0f);
  EXPECT_FALSE(lm2_circle_contains_circle_f32(a, b));
}
