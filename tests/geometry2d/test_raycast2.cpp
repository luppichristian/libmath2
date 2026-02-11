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
#include <vector>
#include "lm2/geometry2d/lm2_raycast2.h"

// Test fixture for Raycast2 tests
class Raycast2Test : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Ray Construction Tests (f64)
// =============================================================================

TEST_F(Raycast2Test, Make_F64) {
  lm2_v2_f64 origin = lm2_v2_make_f64(0.0, 0.0);
  lm2_v2_f64 direction = lm2_v2_make_f64(1.0, 0.0);
  lm2_ray2_f64 ray = lm2_ray2_make_f64(origin, direction, 10.0);

  EXPECT_DOUBLE_EQ(ray.origin.x, 0.0);
  EXPECT_DOUBLE_EQ(ray.origin.y, 0.0);
  EXPECT_DOUBLE_EQ(ray.direction.x, 1.0);
  EXPECT_DOUBLE_EQ(ray.direction.y, 0.0);
  EXPECT_DOUBLE_EQ(ray.t_max, 10.0);
}

TEST_F(Raycast2Test, FromPoints_F64) {
  lm2_v2_f64 start = lm2_v2_make_f64(0.0, 0.0);
  lm2_v2_f64 end = lm2_v2_make_f64(10.0, 0.0);
  lm2_ray2_f64 ray = lm2_ray2_from_points_f64(start, end);

  EXPECT_DOUBLE_EQ(ray.origin.x, 0.0);
  EXPECT_DOUBLE_EQ(ray.origin.y, 0.0);
  EXPECT_NEAR(ray.direction.x, 1.0, EPSILON_F64);
  EXPECT_NEAR(ray.direction.y, 0.0, EPSILON_F64);
  EXPECT_DOUBLE_EQ(ray.t_max, 10.0);
}

TEST_F(Raycast2Test, PointAt_F64) {
  lm2_v2_f64 origin = lm2_v2_make_f64(0.0, 0.0);
  lm2_v2_f64 direction = lm2_v2_make_f64(1.0, 0.0);
  lm2_ray2_f64 ray = lm2_ray2_make_f64(origin, direction, 10.0);

  lm2_v2_f64 point = lm2_ray2_point_at_f64(ray, 5.0);
  EXPECT_DOUBLE_EQ(point.x, 5.0);
  EXPECT_DOUBLE_EQ(point.y, 0.0);
}

// =============================================================================
// Ray Construction Tests (f32)
// =============================================================================

TEST_F(Raycast2Test, Make_F32) {
  lm2_v2_f32 origin = lm2_v2_make_f32(0.0f, 0.0f);
  lm2_v2_f32 direction = lm2_v2_make_f32(1.0f, 0.0f);
  lm2_ray2_f32 ray = lm2_ray2_make_f32(origin, direction, 10.0f);

  EXPECT_FLOAT_EQ(ray.origin.x, 0.0f);
  EXPECT_FLOAT_EQ(ray.direction.x, 1.0f);
  EXPECT_FLOAT_EQ(ray.t_max, 10.0f);
}

TEST_F(Raycast2Test, FromPoints_F32) {
  lm2_v2_f32 start = lm2_v2_make_f32(0.0f, 0.0f);
  lm2_v2_f32 end = lm2_v2_make_f32(10.0f, 0.0f);
  lm2_ray2_f32 ray = lm2_ray2_from_points_f32(start, end);

  EXPECT_FLOAT_EQ(ray.origin.x, 0.0f);
  EXPECT_NEAR(ray.direction.x, 1.0f, EPSILON_F32);
  EXPECT_FLOAT_EQ(ray.t_max, 10.0f);
}

TEST_F(Raycast2Test, PointAt_F32) {
  lm2_v2_f32 origin = lm2_v2_make_f32(0.0f, 0.0f);
  lm2_v2_f32 direction = lm2_v2_make_f32(1.0f, 0.0f);
  lm2_ray2_f32 ray = lm2_ray2_make_f32(origin, direction, 10.0f);

  lm2_v2_f32 point = lm2_ray2_point_at_f32(ray, 5.0f);
  EXPECT_FLOAT_EQ(point.x, 5.0f);
  EXPECT_FLOAT_EQ(point.y, 0.0f);
}

// =============================================================================
// Ray vs Circle Tests (f64)
// =============================================================================

TEST_F(Raycast2Test, RayVsCircle_Hit_F64) {
  lm2_ray2_f64 ray = lm2_ray2_make_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(1.0, 0.0), 20.0);
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(10.0, 0.0, 2.0);

  lm2_rayhit2_f64 hit = lm2_raycast_circle_f64(ray, circle);

  EXPECT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 8.0, EPSILON_F64);
  EXPECT_NEAR(hit.point.x, 8.0, EPSILON_F64);
  EXPECT_NEAR(hit.point.y, 0.0, EPSILON_F64);
}

TEST_F(Raycast2Test, RayVsCircle_Miss_F64) {
  lm2_ray2_f64 ray = lm2_ray2_make_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(1.0, 0.0), 20.0);
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(10.0, 5.0, 2.0);

  lm2_rayhit2_f64 hit = lm2_raycast_circle_f64(ray, circle);

  EXPECT_FALSE(hit.hit);
}

TEST_F(Raycast2Test, RayVsCircle_OriginInside_F64) {
  lm2_ray2_f64 ray = lm2_ray2_make_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(1.0, 0.0), 20.0);
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(0.0, 0.0, 5.0);

  lm2_rayhit2_f64 hit = lm2_raycast_circle_f64(ray, circle);

  EXPECT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 0.0, EPSILON_F64);
}

// =============================================================================
// Ray vs Circle Tests (f32)
// =============================================================================

TEST_F(Raycast2Test, RayVsCircle_Hit_F32) {
  lm2_ray2_f32 ray = lm2_ray2_make_f32(lm2_v2_make_f32(0.0f, 0.0f), lm2_v2_make_f32(1.0f, 0.0f), 20.0f);
  lm2_circle_f32 circle = lm2_circle_make_coords_f32(10.0f, 0.0f, 2.0f);

  lm2_rayhit2_f32 hit = lm2_raycast_circle_f32(ray, circle);

  EXPECT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 8.0f, EPSILON_F32);
}

TEST_F(Raycast2Test, RayVsCircle_Miss_F32) {
  lm2_ray2_f32 ray = lm2_ray2_make_f32(lm2_v2_make_f32(0.0f, 0.0f), lm2_v2_make_f32(1.0f, 0.0f), 20.0f);
  lm2_circle_f32 circle = lm2_circle_make_coords_f32(10.0f, 5.0f, 2.0f);

  lm2_rayhit2_f32 hit = lm2_raycast_circle_f32(ray, circle);

  EXPECT_FALSE(hit.hit);
}

// =============================================================================
// Ray vs AABB Tests (f64)
// =============================================================================

TEST_F(Raycast2Test, RayVsAABB_Hit_F64) {
  lm2_ray2_f64 ray = lm2_ray2_make_f64(lm2_v2_make_f64(0.0, 5.0), lm2_v2_make_f64(1.0, 0.0), 20.0);
  lm2_r2_f64 aabb = lm2_r2_from_min_max_f64(lm2_v2_make_f64(5.0, 0.0), lm2_v2_make_f64(10.0, 10.0));

  lm2_rayhit2_f64 hit = lm2_raycast_aabb_f64(ray, aabb);

  EXPECT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 5.0, EPSILON_F64);
  EXPECT_NEAR(hit.point.x, 5.0, EPSILON_F64);
  EXPECT_NEAR(hit.point.y, 5.0, EPSILON_F64);
}

TEST_F(Raycast2Test, RayVsAABB_Miss_F64) {
  lm2_ray2_f64 ray = lm2_ray2_make_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(1.0, 0.0), 4.0);
  lm2_r2_f64 aabb = lm2_r2_from_min_max_f64(lm2_v2_make_f64(5.0, 5.0), lm2_v2_make_f64(10.0, 10.0));

  lm2_rayhit2_f64 hit = lm2_raycast_aabb_f64(ray, aabb);

  EXPECT_FALSE(hit.hit);
}

// =============================================================================
// Ray vs AABB Tests (f32)
// =============================================================================

TEST_F(Raycast2Test, RayVsAABB_Hit_F32) {
  lm2_ray2_f32 ray = lm2_ray2_make_f32(lm2_v2_make_f32(0.0f, 5.0f), lm2_v2_make_f32(1.0f, 0.0f), 20.0f);
  lm2_r2_f32 aabb = lm2_r2_from_min_max_f32(lm2_v2_make_f32(5.0f, 0.0f), lm2_v2_make_f32(10.0f, 10.0f));

  lm2_rayhit2_f32 hit = lm2_raycast_aabb_f32(ray, aabb);

  EXPECT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 5.0f, EPSILON_F32);
}

TEST_F(Raycast2Test, RayVsAABB_Miss_F32) {
  lm2_ray2_f32 ray = lm2_ray2_make_f32(lm2_v2_make_f32(0.0f, 0.0f), lm2_v2_make_f32(1.0f, 0.0f), 4.0f);
  lm2_r2_f32 aabb = lm2_r2_from_min_max_f32(lm2_v2_make_f32(5.0f, 5.0f), lm2_v2_make_f32(10.0f, 10.0f));

  lm2_rayhit2_f32 hit = lm2_raycast_aabb_f32(ray, aabb);

  EXPECT_FALSE(hit.hit);
}

// =============================================================================
// Ray vs Capsule Tests (f64)
// =============================================================================

TEST_F(Raycast2Test, RayVsCapsule_Hit_F64) {
  lm2_ray2_f64 ray = lm2_ray2_make_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(1.0, 0.0), 20.0);
  lm2_capsule2_f64 capsule = lm2_capsule2_make_coords_f64(10.0, -5.0, 10.0, 5.0, 2.0);

  lm2_rayhit2_f64 hit = lm2_raycast_capsule2_f64(ray, capsule);

  EXPECT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 8.0, EPSILON_F64);
}

TEST_F(Raycast2Test, RayVsCapsule_Miss_F64) {
  lm2_ray2_f64 ray = lm2_ray2_make_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(1.0, 0.0), 20.0);
  lm2_capsule2_f64 capsule = lm2_capsule2_make_coords_f64(10.0, 5.0, 10.0, 10.0, 1.0);

  lm2_rayhit2_f64 hit = lm2_raycast_capsule2_f64(ray, capsule);

  EXPECT_FALSE(hit.hit);
}

// =============================================================================
// Ray vs Capsule Tests (f32)
// =============================================================================

TEST_F(Raycast2Test, RayVsCapsule_Hit_F32) {
  lm2_ray2_f32 ray = lm2_ray2_make_f32(lm2_v2_make_f32(0.0f, 0.0f), lm2_v2_make_f32(1.0f, 0.0f), 20.0f);
  lm2_capsule2_f32 capsule = lm2_capsule2_make_coords_f32(10.0f, -5.0f, 10.0f, 5.0f, 2.0f);

  lm2_rayhit2_f32 hit = lm2_raycast_capsule2_f32(ray, capsule);

  EXPECT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 8.0f, EPSILON_F32);
}

// =============================================================================
// Ray vs Triangle Tests (f64)
// =============================================================================

TEST_F(Raycast2Test, RayVsTriangle_Hit_F64) {
  lm2_ray2_f64 ray = lm2_ray2_make_f64(lm2_v2_make_f64(5.0, 0.0), lm2_v2_make_f64(0.0, 1.0), 20.0);
  lm2_triangle2_f64 triangle;
  lm2_triangle2_make_coords_f64(triangle, 0.0, 5.0, 10.0, 5.0, 5.0, 10.0);

  lm2_rayhit2_f64 hit = lm2_raycast_triangle2_f64(ray, triangle);

  EXPECT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 5.0, EPSILON_F64);
}

TEST_F(Raycast2Test, RayVsTriangle_Miss_F64) {
  lm2_ray2_f64 ray = lm2_ray2_make_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(1.0, 0.0), 3.0);
  lm2_triangle2_f64 triangle;
  lm2_triangle2_make_coords_f64(triangle, 10.0, 5.0, 15.0, 5.0, 12.5, 10.0);

  lm2_rayhit2_f64 hit = lm2_raycast_triangle2_f64(ray, triangle);

  EXPECT_FALSE(hit.hit);
}

// =============================================================================
// Ray vs Triangle Tests (f32)
// =============================================================================

TEST_F(Raycast2Test, RayVsTriangle_Hit_F32) {
  lm2_ray2_f32 ray = lm2_ray2_make_f32(lm2_v2_make_f32(5.0f, 0.0f), lm2_v2_make_f32(0.0f, 1.0f), 20.0f);
  lm2_triangle2_f32 triangle;
  lm2_triangle2_make_coords_f32(triangle, 0.0f, 5.0f, 10.0f, 5.0f, 5.0f, 10.0f);

  lm2_rayhit2_f32 hit = lm2_raycast_triangle2_f32(ray, triangle);

  EXPECT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 5.0f, EPSILON_F32);
}

// =============================================================================
// Ray vs Plane Tests (f64)
// =============================================================================

TEST_F(Raycast2Test, RayVsPlane_Hit_F64) {
  lm2_ray2_f64 ray = lm2_ray2_make_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(1.0, 0.0), 20.0);
  lm2_plane2_f64 plane = lm2_plane2_make_f64(lm2_v2_make_f64(1.0, 0.0), 10.0);

  lm2_rayhit2_f64 hit = lm2_raycast_plane2_f64(ray, plane);

  EXPECT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 10.0, EPSILON_F64);
}

TEST_F(Raycast2Test, RayVsPlane_Parallel_F64) {
  lm2_ray2_f64 ray = lm2_ray2_make_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(1.0, 0.0), 20.0);
  lm2_plane2_f64 plane = lm2_plane2_make_f64(lm2_v2_make_f64(0.0, 1.0), 5.0);

  lm2_rayhit2_f64 hit = lm2_raycast_plane2_f64(ray, plane);

  EXPECT_FALSE(hit.hit);
}

// =============================================================================
// Ray vs Plane Tests (f32)
// =============================================================================

TEST_F(Raycast2Test, RayVsPlane_Hit_F32) {
  lm2_ray2_f32 ray = lm2_ray2_make_f32(lm2_v2_make_f32(0.0f, 0.0f), lm2_v2_make_f32(1.0f, 0.0f), 20.0f);
  lm2_plane2_f32 plane = lm2_plane2_make_f32(lm2_v2_make_f32(1.0f, 0.0f), 10.0f);

  lm2_rayhit2_f32 hit = lm2_raycast_plane2_f32(ray, plane);

  EXPECT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 10.0f, EPSILON_F32);
}
