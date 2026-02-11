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
#include "lm2/geometry2d/lm2_plane2.h"

// Test fixture for Plane2 tests
class Plane2Test : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Construction Tests (f64)
// =============================================================================

TEST_F(Plane2Test, Make_F64) {
  lm2_v2_f64 normal = lm2_v2_make_f64(1.0, 0.0);
  lm2_plane2_f64 plane = lm2_plane2_make_f64(normal, 5.0);

  EXPECT_DOUBLE_EQ(plane.normal.x, 1.0);
  EXPECT_DOUBLE_EQ(plane.normal.y, 0.0);
  EXPECT_DOUBLE_EQ(plane.distance, 5.0);
}

TEST_F(Plane2Test, Make_NonNormalizedNormal_F64) {
  lm2_v2_f64 normal = lm2_v2_make_f64(3.0, 4.0);  // Length = 5
  lm2_plane2_f64 plane = lm2_plane2_make_f64(normal, 10.0);

  // Normal should be normalized to (0.6, 0.8)
  EXPECT_NEAR(plane.normal.x, 0.6, EPSILON_F64);
  EXPECT_NEAR(plane.normal.y, 0.8, EPSILON_F64);
  EXPECT_NEAR(plane.distance, 2.0, EPSILON_F64);  // Distance scaled by 1/5
}

TEST_F(Plane2Test, FromPointNormal_F64) {
  lm2_v2_f64 point = lm2_v2_make_f64(5.0, 0.0);
  lm2_v2_f64 normal = lm2_v2_make_f64(1.0, 0.0);
  lm2_plane2_f64 plane = lm2_plane2_from_point_normal_f64(point, normal);

  EXPECT_DOUBLE_EQ(plane.normal.x, 1.0);
  EXPECT_DOUBLE_EQ(plane.normal.y, 0.0);
  EXPECT_DOUBLE_EQ(plane.distance, 5.0);
}

TEST_F(Plane2Test, FromPoints_F64) {
  lm2_v2_f64 p0 = lm2_v2_make_f64(0.0, 0.0);
  lm2_v2_f64 p1 = lm2_v2_make_f64(10.0, 0.0);
  lm2_plane2_f64 plane = lm2_plane2_from_points_f64(p0, p1);

  // Normal should be perpendicular (counter-clockwise)
  EXPECT_NEAR(plane.normal.x, 0.0, EPSILON_F64);
  EXPECT_NEAR(plane.normal.y, 1.0, EPSILON_F64);
  EXPECT_NEAR(plane.distance, 0.0, EPSILON_F64);
}

TEST_F(Plane2Test, XAxis_F64) {
  lm2_plane2_f64 plane = lm2_plane2_x_axis_f64();

  EXPECT_DOUBLE_EQ(plane.normal.x, 0.0);
  EXPECT_DOUBLE_EQ(plane.normal.y, 1.0);
  EXPECT_DOUBLE_EQ(plane.distance, 0.0);
}

TEST_F(Plane2Test, YAxis_F64) {
  lm2_plane2_f64 plane = lm2_plane2_y_axis_f64();

  EXPECT_DOUBLE_EQ(plane.normal.x, 1.0);
  EXPECT_DOUBLE_EQ(plane.normal.y, 0.0);
  EXPECT_DOUBLE_EQ(plane.distance, 0.0);
}

// =============================================================================
// Construction Tests (f32)
// =============================================================================

TEST_F(Plane2Test, Make_F32) {
  lm2_v2_f32 normal = lm2_v2_make_f32(1.0f, 0.0f);
  lm2_plane2_f32 plane = lm2_plane2_make_f32(normal, 5.0f);

  EXPECT_FLOAT_EQ(plane.normal.x, 1.0f);
  EXPECT_FLOAT_EQ(plane.normal.y, 0.0f);
  EXPECT_FLOAT_EQ(plane.distance, 5.0f);
}

TEST_F(Plane2Test, FromPointNormal_F32) {
  lm2_v2_f32 point = lm2_v2_make_f32(5.0f, 0.0f);
  lm2_v2_f32 normal = lm2_v2_make_f32(1.0f, 0.0f);
  lm2_plane2_f32 plane = lm2_plane2_from_point_normal_f32(point, normal);

  EXPECT_FLOAT_EQ(plane.normal.x, 1.0f);
  EXPECT_FLOAT_EQ(plane.normal.y, 0.0f);
  EXPECT_FLOAT_EQ(plane.distance, 5.0f);
}

TEST_F(Plane2Test, FromPoints_F32) {
  lm2_v2_f32 p0 = lm2_v2_make_f32(0.0f, 0.0f);
  lm2_v2_f32 p1 = lm2_v2_make_f32(10.0f, 0.0f);
  lm2_plane2_f32 plane = lm2_plane2_from_points_f32(p0, p1);

  EXPECT_NEAR(plane.normal.x, 0.0f, EPSILON_F32);
  EXPECT_NEAR(plane.normal.y, 1.0f, EPSILON_F32);
}

// =============================================================================
// Distance Tests (f64)
// =============================================================================

TEST_F(Plane2Test, DistanceToPoint_OnPlane_F64) {
  lm2_plane2_f64 plane = lm2_plane2_make_f64(lm2_v2_make_f64(1.0, 0.0), 5.0);
  lm2_v2_f64 point = lm2_v2_make_f64(5.0, 0.0);
  double distance = lm2_plane2_distance_to_point_f64(plane, point);
  EXPECT_NEAR(distance, 0.0, EPSILON_F64);
}

TEST_F(Plane2Test, DistanceToPoint_PositiveSide_F64) {
  lm2_plane2_f64 plane = lm2_plane2_make_f64(lm2_v2_make_f64(1.0, 0.0), 5.0);
  lm2_v2_f64 point = lm2_v2_make_f64(10.0, 0.0);
  double distance = lm2_plane2_distance_to_point_f64(plane, point);
  EXPECT_DOUBLE_EQ(distance, 5.0);
}

TEST_F(Plane2Test, DistanceToPoint_NegativeSide_F64) {
  lm2_plane2_f64 plane = lm2_plane2_make_f64(lm2_v2_make_f64(1.0, 0.0), 5.0);
  lm2_v2_f64 point = lm2_v2_make_f64(2.0, 0.0);
  double distance = lm2_plane2_distance_to_point_f64(plane, point);
  EXPECT_DOUBLE_EQ(distance, -3.0);
}

// =============================================================================
// Distance Tests (f32)
// =============================================================================

TEST_F(Plane2Test, DistanceToPoint_OnPlane_F32) {
  lm2_plane2_f32 plane = lm2_plane2_make_f32(lm2_v2_make_f32(1.0f, 0.0f), 5.0f);
  lm2_v2_f32 point = lm2_v2_make_f32(5.0f, 0.0f);
  float distance = lm2_plane2_distance_to_point_f32(plane, point);
  EXPECT_NEAR(distance, 0.0f, EPSILON_F32);
}

TEST_F(Plane2Test, DistanceToPoint_PositiveSide_F32) {
  lm2_plane2_f32 plane = lm2_plane2_make_f32(lm2_v2_make_f32(1.0f, 0.0f), 5.0f);
  lm2_v2_f32 point = lm2_v2_make_f32(10.0f, 0.0f);
  float distance = lm2_plane2_distance_to_point_f32(plane, point);
  EXPECT_FLOAT_EQ(distance, 5.0f);
}

// =============================================================================
// Projection Tests (f64)
// =============================================================================

TEST_F(Plane2Test, ProjectPoint_F64) {
  lm2_plane2_f64 plane = lm2_plane2_make_f64(lm2_v2_make_f64(1.0, 0.0), 5.0);
  lm2_v2_f64 point = lm2_v2_make_f64(10.0, 5.0);
  lm2_v2_f64 projected = lm2_plane2_project_point_f64(plane, point);

  EXPECT_DOUBLE_EQ(projected.x, 5.0);
  EXPECT_DOUBLE_EQ(projected.y, 5.0);
}

TEST_F(Plane2Test, ProjectPoint_Origin_F64) {
  lm2_plane2_f64 plane = lm2_plane2_make_f64(lm2_v2_make_f64(0.0, 1.0), 0.0);
  lm2_v2_f64 point = lm2_v2_make_f64(5.0, 10.0);
  lm2_v2_f64 projected = lm2_plane2_project_point_f64(plane, point);

  EXPECT_DOUBLE_EQ(projected.x, 5.0);
  EXPECT_DOUBLE_EQ(projected.y, 0.0);
}

TEST_F(Plane2Test, ClosestPoint_F64) {
  lm2_plane2_f64 plane = lm2_plane2_make_f64(lm2_v2_make_f64(1.0, 0.0), 5.0);
  lm2_v2_f64 point = lm2_v2_make_f64(10.0, 5.0);
  lm2_v2_f64 closest = lm2_plane2_closest_point_f64(plane, point);

  EXPECT_DOUBLE_EQ(closest.x, 5.0);
  EXPECT_DOUBLE_EQ(closest.y, 5.0);
}

// =============================================================================
// Projection Tests (f32)
// =============================================================================

TEST_F(Plane2Test, ProjectPoint_F32) {
  lm2_plane2_f32 plane = lm2_plane2_make_f32(lm2_v2_make_f32(1.0f, 0.0f), 5.0f);
  lm2_v2_f32 point = lm2_v2_make_f32(10.0f, 5.0f);
  lm2_v2_f32 projected = lm2_plane2_project_point_f32(plane, point);

  EXPECT_FLOAT_EQ(projected.x, 5.0f);
  EXPECT_FLOAT_EQ(projected.y, 5.0f);
}

TEST_F(Plane2Test, ClosestPoint_F32) {
  lm2_plane2_f32 plane = lm2_plane2_make_f32(lm2_v2_make_f32(1.0f, 0.0f), 5.0f);
  lm2_v2_f32 point = lm2_v2_make_f32(10.0f, 5.0f);
  lm2_v2_f32 closest = lm2_plane2_closest_point_f32(plane, point);

  EXPECT_FLOAT_EQ(closest.x, 5.0f);
  EXPECT_FLOAT_EQ(closest.y, 5.0f);
}

// =============================================================================
// Containment Tests (f64)
// =============================================================================

TEST_F(Plane2Test, ContainsPoint_True_F64) {
  lm2_plane2_f64 plane = lm2_plane2_make_f64(lm2_v2_make_f64(1.0, 0.0), 5.0);
  lm2_v2_f64 point = lm2_v2_make_f64(5.0, 0.0);
  EXPECT_TRUE(lm2_plane2_contains_point_f64(plane, point, EPSILON_F64));
}

TEST_F(Plane2Test, ContainsPoint_False_F64) {
  lm2_plane2_f64 plane = lm2_plane2_make_f64(lm2_v2_make_f64(1.0, 0.0), 5.0);
  lm2_v2_f64 point = lm2_v2_make_f64(10.0, 0.0);
  EXPECT_FALSE(lm2_plane2_contains_point_f64(plane, point, EPSILON_F64));
}

TEST_F(Plane2Test, ContainsPoint_WithinEpsilon_F64) {
  lm2_plane2_f64 plane = lm2_plane2_make_f64(lm2_v2_make_f64(1.0, 0.0), 5.0);
  lm2_v2_f64 point = lm2_v2_make_f64(5.0 + 1e-11, 0.0);
  EXPECT_TRUE(lm2_plane2_contains_point_f64(plane, point, EPSILON_F64));
}

// =============================================================================
// Side Tests (f64)
// =============================================================================

TEST_F(Plane2Test, Side_Positive_F64) {
  lm2_plane2_f64 plane = lm2_plane2_make_f64(lm2_v2_make_f64(1.0, 0.0), 5.0);
  lm2_v2_f64 point = lm2_v2_make_f64(10.0, 0.0);
  double side = lm2_plane2_side_f64(plane, point);
  EXPECT_GT(side, 0.0);
}

TEST_F(Plane2Test, Side_Negative_F64) {
  lm2_plane2_f64 plane = lm2_plane2_make_f64(lm2_v2_make_f64(1.0, 0.0), 5.0);
  lm2_v2_f64 point = lm2_v2_make_f64(2.0, 0.0);
  double side = lm2_plane2_side_f64(plane, point);
  EXPECT_LT(side, 0.0);
}

TEST_F(Plane2Test, Side_OnPlane_F64) {
  lm2_plane2_f64 plane = lm2_plane2_make_f64(lm2_v2_make_f64(1.0, 0.0), 5.0);
  lm2_v2_f64 point = lm2_v2_make_f64(5.0, 0.0);
  double side = lm2_plane2_side_f64(plane, point);
  EXPECT_NEAR(side, 0.0, EPSILON_F64);
}

// =============================================================================
// Transformation Tests (f64)
// =============================================================================

TEST_F(Plane2Test, Flip_F64) {
  lm2_plane2_f64 plane = lm2_plane2_make_f64(lm2_v2_make_f64(1.0, 0.0), 5.0);
  lm2_plane2_f64 flipped = lm2_plane2_flip_f64(plane);

  EXPECT_DOUBLE_EQ(flipped.normal.x, -1.0);
  EXPECT_DOUBLE_EQ(flipped.normal.y, 0.0);
  EXPECT_DOUBLE_EQ(flipped.distance, -5.0);
}

TEST_F(Plane2Test, Translate_F64) {
  lm2_plane2_f64 plane = lm2_plane2_make_f64(lm2_v2_make_f64(1.0, 0.0), 5.0);
  lm2_v2_f64 offset = lm2_v2_make_f64(3.0, 0.0);
  lm2_plane2_f64 translated = lm2_plane2_translate_f64(plane, offset);

  EXPECT_DOUBLE_EQ(translated.normal.x, 1.0);
  EXPECT_DOUBLE_EQ(translated.normal.y, 0.0);
  EXPECT_DOUBLE_EQ(translated.distance, 8.0);
}

// =============================================================================
// Transformation Tests (f32)
// =============================================================================

TEST_F(Plane2Test, Flip_F32) {
  lm2_plane2_f32 plane = lm2_plane2_make_f32(lm2_v2_make_f32(1.0f, 0.0f), 5.0f);
  lm2_plane2_f32 flipped = lm2_plane2_flip_f32(plane);

  EXPECT_FLOAT_EQ(flipped.normal.x, -1.0f);
  EXPECT_FLOAT_EQ(flipped.normal.y, 0.0f);
  EXPECT_FLOAT_EQ(flipped.distance, -5.0f);
}

TEST_F(Plane2Test, Translate_F32) {
  lm2_plane2_f32 plane = lm2_plane2_make_f32(lm2_v2_make_f32(1.0f, 0.0f), 5.0f);
  lm2_v2_f32 offset = lm2_v2_make_f32(3.0f, 0.0f);
  lm2_plane2_f32 translated = lm2_plane2_translate_f32(plane, offset);

  EXPECT_FLOAT_EQ(translated.normal.x, 1.0f);
  EXPECT_FLOAT_EQ(translated.normal.y, 0.0f);
  EXPECT_FLOAT_EQ(translated.distance, 8.0f);
}
