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
#include "lm2/geometry2d/lm2_triangle2.h"

// Test fixture for Triangle2 tests
class Triangle2Test : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Construction Tests (f64)
// =============================================================================

TEST_F(Triangle2Test, Make_F64) {
  lm2_triangle2_f64 tri;
  lm2_v2_f64 a = lm2_v2_make_f64(0.0, 0.0);
  lm2_v2_f64 b = lm2_v2_make_f64(4.0, 0.0);
  lm2_v2_f64 c = lm2_v2_make_f64(0.0, 3.0);
  lm2_triangle2_make_f64(tri, a, b, c);

  EXPECT_DOUBLE_EQ(tri[0].x, 0.0);
  EXPECT_DOUBLE_EQ(tri[0].y, 0.0);
  EXPECT_DOUBLE_EQ(tri[1].x, 4.0);
  EXPECT_DOUBLE_EQ(tri[1].y, 0.0);
  EXPECT_DOUBLE_EQ(tri[2].x, 0.0);
  EXPECT_DOUBLE_EQ(tri[2].y, 3.0);
}

TEST_F(Triangle2Test, MakeCoords_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 4.0, 0.0, 0.0, 3.0);

  EXPECT_DOUBLE_EQ(tri[0].x, 0.0);
  EXPECT_DOUBLE_EQ(tri[0].y, 0.0);
  EXPECT_DOUBLE_EQ(tri[1].x, 4.0);
  EXPECT_DOUBLE_EQ(tri[1].y, 0.0);
  EXPECT_DOUBLE_EQ(tri[2].x, 0.0);
  EXPECT_DOUBLE_EQ(tri[2].y, 3.0);
}

// =============================================================================
// Construction Tests (f32)
// =============================================================================

TEST_F(Triangle2Test, Make_F32) {
  lm2_triangle2_f32 tri;
  lm2_v2_f32 a = lm2_v2_make_f32(0.0f, 0.0f);
  lm2_v2_f32 b = lm2_v2_make_f32(4.0f, 0.0f);
  lm2_v2_f32 c = lm2_v2_make_f32(0.0f, 3.0f);
  lm2_triangle2_make_f32(tri, a, b, c);

  EXPECT_FLOAT_EQ(tri[0].x, 0.0f);
  EXPECT_FLOAT_EQ(tri[0].y, 0.0f);
  EXPECT_FLOAT_EQ(tri[1].x, 4.0f);
  EXPECT_FLOAT_EQ(tri[1].y, 0.0f);
  EXPECT_FLOAT_EQ(tri[2].x, 0.0f);
  EXPECT_FLOAT_EQ(tri[2].y, 3.0f);
}

TEST_F(Triangle2Test, MakeCoords_F32) {
  lm2_triangle2_f32 tri;
  lm2_triangle2_make_coords_f32(tri, 0.0f, 0.0f, 4.0f, 0.0f, 0.0f, 3.0f);

  EXPECT_FLOAT_EQ(tri[0].x, 0.0f);
  EXPECT_FLOAT_EQ(tri[1].x, 4.0f);
  EXPECT_FLOAT_EQ(tri[2].y, 3.0f);
}

// =============================================================================
// Area Tests (f64)
// =============================================================================

TEST_F(Triangle2Test, SignedArea_CCW_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 4.0, 0.0, 0.0, 3.0);
  double area = lm2_triangle2_signed_area_f64(tri);
  EXPECT_DOUBLE_EQ(area, 6.0);  // (4 * 3) / 2 = 6
}

TEST_F(Triangle2Test, SignedArea_CW_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 0.0, 3.0, 4.0, 0.0);
  double area = lm2_triangle2_signed_area_f64(tri);
  EXPECT_DOUBLE_EQ(area, -6.0);
}

TEST_F(Triangle2Test, Area_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 4.0, 0.0, 0.0, 3.0);
  double area = lm2_triangle2_area_f64(tri);
  EXPECT_DOUBLE_EQ(area, 6.0);
}

TEST_F(Triangle2Test, Area_CW_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 0.0, 3.0, 4.0, 0.0);
  double area = lm2_triangle2_area_f64(tri);
  EXPECT_DOUBLE_EQ(area, 6.0);  // Always positive
}

// =============================================================================
// Area Tests (f32)
// =============================================================================

TEST_F(Triangle2Test, SignedArea_CCW_F32) {
  lm2_triangle2_f32 tri;
  lm2_triangle2_make_coords_f32(tri, 0.0f, 0.0f, 4.0f, 0.0f, 0.0f, 3.0f);
  float area = lm2_triangle2_signed_area_f32(tri);
  EXPECT_FLOAT_EQ(area, 6.0f);
}

TEST_F(Triangle2Test, Area_F32) {
  lm2_triangle2_f32 tri;
  lm2_triangle2_make_coords_f32(tri, 0.0f, 0.0f, 4.0f, 0.0f, 0.0f, 3.0f);
  float area = lm2_triangle2_area_f32(tri);
  EXPECT_FLOAT_EQ(area, 6.0f);
}

// =============================================================================
// Perimeter Tests (f64)
// =============================================================================

TEST_F(Triangle2Test, Perimeter_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 3.0, 0.0, 0.0, 4.0);
  double perimeter = lm2_triangle2_perimeter_f64(tri);
  EXPECT_DOUBLE_EQ(perimeter, 12.0);  // 3 + 4 + 5
}

// =============================================================================
// Perimeter Tests (f32)
// =============================================================================

TEST_F(Triangle2Test, Perimeter_F32) {
  lm2_triangle2_f32 tri;
  lm2_triangle2_make_coords_f32(tri, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 4.0f);
  float perimeter = lm2_triangle2_perimeter_f32(tri);
  EXPECT_FLOAT_EQ(perimeter, 12.0f);
}

// =============================================================================
// Winding Order Tests (f64)
// =============================================================================

TEST_F(Triangle2Test, Winding_CCW_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 4.0, 0.0, 0.0, 3.0);
  lm2_winding_order winding = lm2_triangle2_winding_f64(tri);
  EXPECT_EQ(winding, LM2_WINDING_COUNTERCLOCKWISE);
}

TEST_F(Triangle2Test, Winding_CW_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 0.0, 3.0, 4.0, 0.0);
  lm2_winding_order winding = lm2_triangle2_winding_f64(tri);
  EXPECT_EQ(winding, LM2_WINDING_CLOCKWISE);
}

TEST_F(Triangle2Test, Winding_Degenerate_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 1.0, 1.0, 2.0, 2.0);
  lm2_winding_order winding = lm2_triangle2_winding_f64(tri);
  EXPECT_EQ(winding, LM2_WINDING_NONE);
}

// =============================================================================
// Winding Order Tests (f32)
// =============================================================================

TEST_F(Triangle2Test, Winding_CCW_F32) {
  lm2_triangle2_f32 tri;
  lm2_triangle2_make_coords_f32(tri, 0.0f, 0.0f, 4.0f, 0.0f, 0.0f, 3.0f);
  lm2_winding_order winding = lm2_triangle2_winding_f32(tri);
  EXPECT_EQ(winding, LM2_WINDING_COUNTERCLOCKWISE);
}

TEST_F(Triangle2Test, Winding_CW_F32) {
  lm2_triangle2_f32 tri;
  lm2_triangle2_make_coords_f32(tri, 0.0f, 0.0f, 0.0f, 3.0f, 4.0f, 0.0f);
  lm2_winding_order winding = lm2_triangle2_winding_f32(tri);
  EXPECT_EQ(winding, LM2_WINDING_CLOCKWISE);
}

// =============================================================================
// Classification Tests (f64)
// =============================================================================

TEST_F(Triangle2Test, IsDegenerate_True_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 1.0, 1.0, 2.0, 2.0);
  EXPECT_TRUE(lm2_triangle2_is_degenerate_f64(tri, EPSILON_F64));
}

TEST_F(Triangle2Test, IsDegenerate_False_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 4.0, 0.0, 0.0, 3.0);
  EXPECT_FALSE(lm2_triangle2_is_degenerate_f64(tri, EPSILON_F64));
}

TEST_F(Triangle2Test, IsRight_True_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 3.0, 0.0, 0.0, 4.0);
  EXPECT_TRUE(lm2_triangle2_is_right_f64(tri, EPSILON_F64));
}

TEST_F(Triangle2Test, IsRight_False_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 4.0, 0.0, 2.0, 3.0);
  EXPECT_FALSE(lm2_triangle2_is_right_f64(tri, EPSILON_F64));
}

TEST_F(Triangle2Test, IsEquilateral_True_F64) {
  lm2_triangle2_f64 tri;
  double side = 2.0;
  double h = side * std::sqrt(3.0) / 2.0;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, side, 0.0, side / 2.0, h);
  EXPECT_TRUE(lm2_triangle2_is_equilateral_f64(tri, 1e-6));
}

TEST_F(Triangle2Test, IsEquilateral_False_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 3.0, 0.0, 0.0, 4.0);
  EXPECT_FALSE(lm2_triangle2_is_equilateral_f64(tri, EPSILON_F64));
}

TEST_F(Triangle2Test, IsIsosceles_True_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 4.0, 0.0, 2.0, 3.0);
  EXPECT_TRUE(lm2_triangle2_is_isosceles_f64(tri, 1e-6));
}

TEST_F(Triangle2Test, IsIsosceles_False_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 3.0, 0.0, 0.0, 4.0);
  EXPECT_FALSE(lm2_triangle2_is_isosceles_f64(tri, EPSILON_F64));
}

TEST_F(Triangle2Test, IsScalene_True_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 3.0, 0.0, 1.0, 4.0);
  EXPECT_TRUE(lm2_triangle2_is_scalene_f64(tri, EPSILON_F64));
}

TEST_F(Triangle2Test, IsScalene_False_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 4.0, 0.0, 2.0, 3.0);
  EXPECT_FALSE(lm2_triangle2_is_scalene_f64(tri, 1e-6));
}

TEST_F(Triangle2Test, Classify_Right_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 3.0, 0.0, 0.0, 4.0);
  lm2_triangle2_type type = lm2_triangle2_classify_f64(tri, EPSILON_F64);
  EXPECT_EQ(type, LM2_TRIANGLE2_RIGHT);
}

TEST_F(Triangle2Test, Classify_Degenerate_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 1.0, 1.0, 2.0, 2.0);
  lm2_triangle2_type type = lm2_triangle2_classify_f64(tri, EPSILON_F64);
  EXPECT_EQ(type, LM2_TRIANGLE2_DEGENERATE);
}

// =============================================================================
// Classification Tests (f32)
// =============================================================================

TEST_F(Triangle2Test, IsDegenerate_True_F32) {
  lm2_triangle2_f32 tri;
  lm2_triangle2_make_coords_f32(tri, 0.0f, 0.0f, 1.0f, 1.0f, 2.0f, 2.0f);
  EXPECT_TRUE(lm2_triangle2_is_degenerate_f32(tri, EPSILON_F32));
}

TEST_F(Triangle2Test, IsRight_True_F32) {
  lm2_triangle2_f32 tri;
  lm2_triangle2_make_coords_f32(tri, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 4.0f);
  EXPECT_TRUE(lm2_triangle2_is_right_f32(tri, EPSILON_F32));
}

// =============================================================================
// Point Containment Tests (f64)
// =============================================================================

TEST_F(Triangle2Test, ContainsPoint_Inside_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 10.0, 0.0, 5.0, 10.0);
  lm2_v2_f64 point = lm2_v2_make_f64(5.0, 5.0);
  EXPECT_TRUE(lm2_triangle2_contains_point_f64(tri, point));
}

TEST_F(Triangle2Test, ContainsPoint_Outside_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 10.0, 0.0, 5.0, 10.0);
  lm2_v2_f64 point = lm2_v2_make_f64(15.0, 5.0);
  EXPECT_FALSE(lm2_triangle2_contains_point_f64(tri, point));
}

TEST_F(Triangle2Test, ContainsPoint_OnVertex_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 10.0, 0.0, 5.0, 10.0);
  lm2_v2_f64 point = lm2_v2_make_f64(0.0, 0.0);
  EXPECT_TRUE(lm2_triangle2_contains_point_f64(tri, point));
}

TEST_F(Triangle2Test, ContainsPoint_OnEdge_F64) {
  lm2_triangle2_f64 tri;
  lm2_triangle2_make_coords_f64(tri, 0.0, 0.0, 10.0, 0.0, 5.0, 10.0);
  lm2_v2_f64 point = lm2_v2_make_f64(5.0, 0.0);
  EXPECT_TRUE(lm2_triangle2_contains_point_f64(tri, point));
}

// =============================================================================
// Point Containment Tests (f32)
// =============================================================================

TEST_F(Triangle2Test, ContainsPoint_Inside_F32) {
  lm2_triangle2_f32 tri;
  lm2_triangle2_make_coords_f32(tri, 0.0f, 0.0f, 10.0f, 0.0f, 5.0f, 10.0f);
  lm2_v2_f32 point = lm2_v2_make_f32(5.0f, 5.0f);
  EXPECT_TRUE(lm2_triangle2_contains_point_f32(tri, point));
}

TEST_F(Triangle2Test, ContainsPoint_Outside_F32) {
  lm2_triangle2_f32 tri;
  lm2_triangle2_make_coords_f32(tri, 0.0f, 0.0f, 10.0f, 0.0f, 5.0f, 10.0f);
  lm2_v2_f32 point = lm2_v2_make_f32(15.0f, 5.0f);
  EXPECT_FALSE(lm2_triangle2_contains_point_f32(tri, point));
}

// =============================================================================
// Triangle Overlap Tests (f64)
// =============================================================================

TEST_F(Triangle2Test, Overlaps_True_F64) {
  lm2_triangle2_f64 t1, t2;
  lm2_triangle2_make_coords_f64(t1, 0.0, 0.0, 5.0, 0.0, 0.0, 5.0);
  lm2_triangle2_make_coords_f64(t2, 2.0, 2.0, 8.0, 2.0, 2.0, 8.0);
  EXPECT_TRUE(lm2_triangle2_overlaps_f64(t1, t2));
}

TEST_F(Triangle2Test, Overlaps_False_F64) {
  lm2_triangle2_f64 t1, t2;
  lm2_triangle2_make_coords_f64(t1, 0.0, 0.0, 5.0, 0.0, 0.0, 5.0);
  lm2_triangle2_make_coords_f64(t2, 10.0, 10.0, 15.0, 10.0, 10.0, 15.0);
  EXPECT_FALSE(lm2_triangle2_overlaps_f64(t1, t2));
}

// =============================================================================
// Triangle Overlap Tests (f32)
// =============================================================================

TEST_F(Triangle2Test, Overlaps_True_F32) {
  lm2_triangle2_f32 t1, t2;
  lm2_triangle2_make_coords_f32(t1, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 5.0f);
  lm2_triangle2_make_coords_f32(t2, 2.0f, 2.0f, 8.0f, 2.0f, 2.0f, 8.0f);
  EXPECT_TRUE(lm2_triangle2_overlaps_f32(t1, t2));
}

TEST_F(Triangle2Test, Overlaps_False_F32) {
  lm2_triangle2_f32 t1, t2;
  lm2_triangle2_make_coords_f32(t1, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 5.0f);
  lm2_triangle2_make_coords_f32(t2, 10.0f, 10.0f, 15.0f, 10.0f, 10.0f, 15.0f);
  EXPECT_FALSE(lm2_triangle2_overlaps_f32(t1, t2));
}
