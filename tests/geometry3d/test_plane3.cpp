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
#include "lm2/geometry3d/lm2_plane3.h"

// Test fixture for Plane3 tests
class Plane3Test : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Construction Tests (f64)
// =============================================================================

TEST_F(Plane3Test, Make_F64) {
  lm2_v3_f64 normal = lm2_v3_make_f64(0.0, 1.0, 0.0);
  lm2_plane3_f64 plane = lm2_plane3_make_f64(normal, 5.0);

  EXPECT_NEAR(plane.normal.x, 0.0, EPSILON_F64);
  EXPECT_NEAR(plane.normal.y, 1.0, EPSILON_F64);
  EXPECT_NEAR(plane.normal.z, 0.0, EPSILON_F64);
  EXPECT_DOUBLE_EQ(plane.distance, 5.0);
}

TEST_F(Plane3Test, MakeNormalizesNormal_F64) {
  // Non-unit normal should be normalized
  lm2_v3_f64 normal = lm2_v3_make_f64(0.0, 2.0, 0.0);
  lm2_plane3_f64 plane = lm2_plane3_make_f64(normal, 5.0);

  EXPECT_NEAR(plane.normal.x, 0.0, EPSILON_F64);
  EXPECT_NEAR(plane.normal.y, 1.0, EPSILON_F64);
  EXPECT_NEAR(plane.normal.z, 0.0, EPSILON_F64);
}

TEST_F(Plane3Test, FromPointNormal_F64) {
  lm2_v3_f64 point = lm2_v3_make_f64(0.0, 5.0, 0.0);
  lm2_v3_f64 normal = lm2_v3_make_f64(0.0, 1.0, 0.0);
  lm2_plane3_f64 plane = lm2_plane3_from_point_normal_f64(point, normal);

  EXPECT_NEAR(plane.normal.x, 0.0, EPSILON_F64);
  EXPECT_NEAR(plane.normal.y, 1.0, EPSILON_F64);
  EXPECT_NEAR(plane.normal.z, 0.0, EPSILON_F64);
  EXPECT_NEAR(plane.distance, 5.0, EPSILON_F64);
}

TEST_F(Plane3Test, FromPoints_F64) {
  // Three points defining the XY plane at z=0
  lm2_v3_f64 p0 = lm2_v3_make_f64(0.0, 0.0, 0.0);
  lm2_v3_f64 p1 = lm2_v3_make_f64(1.0, 0.0, 0.0);
  lm2_v3_f64 p2 = lm2_v3_make_f64(0.0, 1.0, 0.0);

  lm2_plane3_f64 plane = lm2_plane3_from_points_f64(p0, p1, p2);

  // Normal should point in +Z direction
  EXPECT_NEAR(plane.normal.x, 0.0, EPSILON_F64);
  EXPECT_NEAR(plane.normal.y, 0.0, EPSILON_F64);
  EXPECT_NEAR(plane.normal.z, 1.0, EPSILON_F64);
  EXPECT_NEAR(plane.distance, 0.0, EPSILON_F64);
}

TEST_F(Plane3Test, StandardPlanes_F64) {
  // XY plane (normal = +Z)
  lm2_plane3_f64 xy = lm2_plane3_xy_f64();
  EXPECT_NEAR(xy.normal.z, 1.0, EPSILON_F64);
  EXPECT_DOUBLE_EQ(xy.distance, 0.0);

  // XZ plane (normal = +Y)
  lm2_plane3_f64 xz = lm2_plane3_xz_f64();
  EXPECT_NEAR(xz.normal.y, 1.0, EPSILON_F64);
  EXPECT_DOUBLE_EQ(xz.distance, 0.0);

  // YZ plane (normal = +X)
  lm2_plane3_f64 yz = lm2_plane3_yz_f64();
  EXPECT_NEAR(yz.normal.x, 1.0, EPSILON_F64);
  EXPECT_DOUBLE_EQ(yz.distance, 0.0);
}

// =============================================================================
// Construction Tests (f32)
// =============================================================================

TEST_F(Plane3Test, Make_F32) {
  lm2_v3_f32 normal = lm2_v3_make_f32(0.0f, 1.0f, 0.0f);
  lm2_plane3_f32 plane = lm2_plane3_make_f32(normal, 5.0f);

  EXPECT_NEAR(plane.normal.x, 0.0f, EPSILON_F32);
  EXPECT_NEAR(plane.normal.y, 1.0f, EPSILON_F32);
  EXPECT_NEAR(plane.normal.z, 0.0f, EPSILON_F32);
  EXPECT_FLOAT_EQ(plane.distance, 5.0f);
}

TEST_F(Plane3Test, FromPointNormal_F32) {
  lm2_v3_f32 point = lm2_v3_make_f32(0.0f, 5.0f, 0.0f);
  lm2_v3_f32 normal = lm2_v3_make_f32(0.0f, 1.0f, 0.0f);
  lm2_plane3_f32 plane = lm2_plane3_from_point_normal_f32(point, normal);

  EXPECT_NEAR(plane.distance, 5.0f, EPSILON_F32);
}

TEST_F(Plane3Test, FromPoints_F32) {
  lm2_v3_f32 p0 = lm2_v3_make_f32(0.0f, 0.0f, 0.0f);
  lm2_v3_f32 p1 = lm2_v3_make_f32(1.0f, 0.0f, 0.0f);
  lm2_v3_f32 p2 = lm2_v3_make_f32(0.0f, 1.0f, 0.0f);

  lm2_plane3_f32 plane = lm2_plane3_from_points_f32(p0, p1, p2);

  EXPECT_NEAR(plane.normal.z, 1.0f, EPSILON_F32);
  EXPECT_NEAR(plane.distance, 0.0f, EPSILON_F32);
}

TEST_F(Plane3Test, StandardPlanes_F32) {
  lm2_plane3_f32 xy = lm2_plane3_xy_f32();
  EXPECT_NEAR(xy.normal.z, 1.0f, EPSILON_F32);

  lm2_plane3_f32 xz = lm2_plane3_xz_f32();
  EXPECT_NEAR(xz.normal.y, 1.0f, EPSILON_F32);

  lm2_plane3_f32 yz = lm2_plane3_yz_f32();
  EXPECT_NEAR(yz.normal.x, 1.0f, EPSILON_F32);
}

// =============================================================================
// Distance and Projection Tests (f64)
// =============================================================================

TEST_F(Plane3Test, DistanceToPoint_F64) {
  // Horizontal plane at y=5
  lm2_plane3_f64 plane = lm2_plane3_from_point_normal_f64(
      lm2_v3_make_f64(0.0, 5.0, 0.0),
      lm2_v3_make_f64(0.0, 1.0, 0.0));

  // Point above the plane
  lm2_v3_f64 above = lm2_v3_make_f64(0.0, 8.0, 0.0);
  double dist = lm2_plane3_distance_to_point_f64(plane, above);
  EXPECT_NEAR(dist, 3.0, EPSILON_F64);

  // Point below the plane
  lm2_v3_f64 below = lm2_v3_make_f64(0.0, 2.0, 0.0);
  dist = lm2_plane3_distance_to_point_f64(plane, below);
  EXPECT_NEAR(dist, -3.0, EPSILON_F64);

  // Point on the plane
  lm2_v3_f64 on = lm2_v3_make_f64(10.0, 5.0, 10.0);
  dist = lm2_plane3_distance_to_point_f64(plane, on);
  EXPECT_NEAR(dist, 0.0, EPSILON_F64);
}

TEST_F(Plane3Test, ProjectPoint_F64) {
  // Horizontal plane at y=5
  lm2_plane3_f64 plane = lm2_plane3_from_point_normal_f64(
      lm2_v3_make_f64(0.0, 5.0, 0.0),
      lm2_v3_make_f64(0.0, 1.0, 0.0));

  lm2_v3_f64 point = lm2_v3_make_f64(10.0, 8.0, 15.0);
  lm2_v3_f64 projected = lm2_plane3_project_point_f64(plane, point);

  EXPECT_NEAR(projected.x, 10.0, EPSILON_F64);
  EXPECT_NEAR(projected.y, 5.0, EPSILON_F64);
  EXPECT_NEAR(projected.z, 15.0, EPSILON_F64);
}

TEST_F(Plane3Test, ClosestPoint_F64) {
  lm2_plane3_f64 plane = lm2_plane3_from_point_normal_f64(
      lm2_v3_make_f64(0.0, 5.0, 0.0),
      lm2_v3_make_f64(0.0, 1.0, 0.0));

  lm2_v3_f64 point = lm2_v3_make_f64(7.0, 12.0, 3.0);
  lm2_v3_f64 closest = lm2_plane3_closest_point_f64(plane, point);

  EXPECT_NEAR(closest.x, 7.0, EPSILON_F64);
  EXPECT_NEAR(closest.y, 5.0, EPSILON_F64);
  EXPECT_NEAR(closest.z, 3.0, EPSILON_F64);
}

// =============================================================================
// Distance and Projection Tests (f32)
// =============================================================================

TEST_F(Plane3Test, DistanceToPoint_F32) {
  lm2_plane3_f32 plane = lm2_plane3_from_point_normal_f32(
      lm2_v3_make_f32(0.0f, 5.0f, 0.0f),
      lm2_v3_make_f32(0.0f, 1.0f, 0.0f));

  lm2_v3_f32 above = lm2_v3_make_f32(0.0f, 8.0f, 0.0f);
  float dist = lm2_plane3_distance_to_point_f32(plane, above);
  EXPECT_NEAR(dist, 3.0f, EPSILON_F32);
}

TEST_F(Plane3Test, ProjectPoint_F32) {
  lm2_plane3_f32 plane = lm2_plane3_from_point_normal_f32(
      lm2_v3_make_f32(0.0f, 5.0f, 0.0f),
      lm2_v3_make_f32(0.0f, 1.0f, 0.0f));

  lm2_v3_f32 point = lm2_v3_make_f32(10.0f, 8.0f, 15.0f);
  lm2_v3_f32 projected = lm2_plane3_project_point_f32(plane, point);

  EXPECT_NEAR(projected.y, 5.0f, EPSILON_F32);
}

TEST_F(Plane3Test, ClosestPoint_F32) {
  lm2_plane3_f32 plane = lm2_plane3_from_point_normal_f32(
      lm2_v3_make_f32(0.0f, 5.0f, 0.0f),
      lm2_v3_make_f32(0.0f, 1.0f, 0.0f));

  lm2_v3_f32 point = lm2_v3_make_f32(7.0f, 12.0f, 3.0f);
  lm2_v3_f32 closest = lm2_plane3_closest_point_f32(plane, point);

  EXPECT_NEAR(closest.y, 5.0f, EPSILON_F32);
}

// =============================================================================
// Containment Tests (f64)
// =============================================================================

TEST_F(Plane3Test, ContainsPoint_F64) {
  lm2_plane3_f64 plane = lm2_plane3_xy_f64();

  lm2_v3_f64 onPlane = lm2_v3_make_f64(5.0, 7.0, 0.0);
  EXPECT_TRUE(lm2_plane3_contains_point_f64(plane, onPlane, EPSILON_F64));

  lm2_v3_f64 offPlane = lm2_v3_make_f64(5.0, 7.0, 1.0);
  EXPECT_FALSE(lm2_plane3_contains_point_f64(plane, offPlane, EPSILON_F64));
}

TEST_F(Plane3Test, Side_F64) {
  lm2_plane3_f64 plane = lm2_plane3_xy_f64();

  // Point on positive side (normal direction)
  lm2_v3_f64 positive = lm2_v3_make_f64(0.0, 0.0, 5.0);
  EXPECT_GT(lm2_plane3_side_f64(plane, positive), 0.0);

  // Point on negative side
  lm2_v3_f64 negative = lm2_v3_make_f64(0.0, 0.0, -5.0);
  EXPECT_LT(lm2_plane3_side_f64(plane, negative), 0.0);

  // Point on plane
  lm2_v3_f64 on = lm2_v3_make_f64(10.0, 10.0, 0.0);
  EXPECT_NEAR(lm2_plane3_side_f64(plane, on), 0.0, EPSILON_F64);
}

// =============================================================================
// Containment Tests (f32)
// =============================================================================

TEST_F(Plane3Test, ContainsPoint_F32) {
  lm2_plane3_f32 plane = lm2_plane3_xy_f32();

  lm2_v3_f32 onPlane = lm2_v3_make_f32(5.0f, 7.0f, 0.0f);
  EXPECT_TRUE(lm2_plane3_contains_point_f32(plane, onPlane, EPSILON_F32));

  lm2_v3_f32 offPlane = lm2_v3_make_f32(5.0f, 7.0f, 1.0f);
  EXPECT_FALSE(lm2_plane3_contains_point_f32(plane, offPlane, EPSILON_F32));
}

TEST_F(Plane3Test, Side_F32) {
  lm2_plane3_f32 plane = lm2_plane3_xy_f32();

  lm2_v3_f32 positive = lm2_v3_make_f32(0.0f, 0.0f, 5.0f);
  EXPECT_GT(lm2_plane3_side_f32(plane, positive), 0.0f);

  lm2_v3_f32 negative = lm2_v3_make_f32(0.0f, 0.0f, -5.0f);
  EXPECT_LT(lm2_plane3_side_f32(plane, negative), 0.0f);
}

// =============================================================================
// Transformation Tests (f64)
// =============================================================================

TEST_F(Plane3Test, Flip_F64) {
  lm2_plane3_f64 plane = lm2_plane3_from_point_normal_f64(
      lm2_v3_make_f64(0.0, 5.0, 0.0),
      lm2_v3_make_f64(0.0, 1.0, 0.0));

  lm2_plane3_f64 flipped = lm2_plane3_flip_f64(plane);

  EXPECT_NEAR(flipped.normal.x, 0.0, EPSILON_F64);
  EXPECT_NEAR(flipped.normal.y, -1.0, EPSILON_F64);
  EXPECT_NEAR(flipped.normal.z, 0.0, EPSILON_F64);
  EXPECT_NEAR(flipped.distance, -5.0, EPSILON_F64);
}

TEST_F(Plane3Test, Translate_F64) {
  lm2_plane3_f64 plane = lm2_plane3_xy_f64();
  lm2_v3_f64 offset = lm2_v3_make_f64(0.0, 0.0, 5.0);

  lm2_plane3_f64 translated = lm2_plane3_translate_f64(plane, offset);

  // Normal should remain the same
  EXPECT_NEAR(translated.normal.x, 0.0, EPSILON_F64);
  EXPECT_NEAR(translated.normal.y, 0.0, EPSILON_F64);
  EXPECT_NEAR(translated.normal.z, 1.0, EPSILON_F64);

  // Distance should be updated
  EXPECT_NEAR(translated.distance, 5.0, EPSILON_F64);
}

// =============================================================================
// Transformation Tests (f32)
// =============================================================================

TEST_F(Plane3Test, Flip_F32) {
  lm2_plane3_f32 plane = lm2_plane3_from_point_normal_f32(
      lm2_v3_make_f32(0.0f, 5.0f, 0.0f),
      lm2_v3_make_f32(0.0f, 1.0f, 0.0f));

  lm2_plane3_f32 flipped = lm2_plane3_flip_f32(plane);

  EXPECT_NEAR(flipped.normal.y, -1.0f, EPSILON_F32);
  EXPECT_NEAR(flipped.distance, -5.0f, EPSILON_F32);
}

TEST_F(Plane3Test, Translate_F32) {
  lm2_plane3_f32 plane = lm2_plane3_xy_f32();
  lm2_v3_f32 offset = lm2_v3_make_f32(0.0f, 0.0f, 5.0f);

  lm2_plane3_f32 translated = lm2_plane3_translate_f32(plane, offset);

  EXPECT_NEAR(translated.distance, 5.0f, EPSILON_F32);
}

// =============================================================================
// Complex Scenarios
// =============================================================================

TEST_F(Plane3Test, DiagonalPlane_F64) {
  // Create a diagonal plane
  lm2_v3_f64 normal = lm2_v3_make_f64(1.0, 1.0, 1.0);
  lm2_plane3_f64 plane = lm2_plane3_make_f64(normal, 0.0);

  // Normal should be normalized
  double length = sqrt(plane.normal.x * plane.normal.x +
                       plane.normal.y * plane.normal.y +
                       plane.normal.z * plane.normal.z);
  EXPECT_NEAR(length, 1.0, EPSILON_F64);

  // Test a point on the plane
  lm2_v3_f64 point = lm2_v3_make_f64(1.0, -1.0, 0.0);
  double dist = lm2_plane3_distance_to_point_f64(plane, point);
  EXPECT_NEAR(dist, 0.0, EPSILON_F64);
}
