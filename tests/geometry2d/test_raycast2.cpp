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

TEST_F(Raycast2Test, CircleHitHasOutwardUnitNormalAndConsistentPoint_F64) {
  lm2_ray2_f64 ray = lm2_ray2_make_f64(lm2_v2_make_f64(1.0, 2.0), lm2_v2_make_f64(1.0, 0.0), 10.0);
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(6.0, 2.0, 2.0);

  lm2_rayhit2_f64 hit = lm2_raycast_circle_f64(ray, circle);

  ASSERT_TRUE(hit.hit);
  EXPECT_DOUBLE_EQ(hit.t, 3.0);
  EXPECT_DOUBLE_EQ(hit.point.x, ray.origin.x + ray.direction.x * hit.t);
  EXPECT_DOUBLE_EQ(hit.point.y, ray.origin.y + ray.direction.y * hit.t);
  EXPECT_DOUBLE_EQ(hit.normal.x, -1.0);
  EXPECT_DOUBLE_EQ(hit.normal.y, 0.0);
  EXPECT_DOUBLE_EQ(std::hypot(hit.normal.x, hit.normal.y), 1.0);
  EXPECT_LT(hit.normal.x * ray.direction.x + hit.normal.y * ray.direction.y, 0.0);
}

TEST_F(Raycast2Test, CircleHonorsTMaxBoundaryTangentAndDirection_F64) {
  lm2_circle_f64 tangent = lm2_circle_make_coords_f64(5.0, 1.0, 1.0);
  lm2_ray2_f64 boundary = lm2_ray2_make_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(1.0, 0.0), 5.0);
  lm2_rayhit2_f64 hit = lm2_raycast_circle_f64(boundary, tangent);
  ASSERT_TRUE(hit.hit);
  EXPECT_DOUBLE_EQ(hit.t, boundary.t_max);
  EXPECT_DOUBLE_EQ(hit.point.x, 5.0);
  EXPECT_DOUBLE_EQ(hit.point.y, 0.0);
  EXPECT_DOUBLE_EQ(std::hypot(hit.normal.x, hit.normal.y), 1.0);
  EXPECT_DOUBLE_EQ(hit.normal.x, 0.0);
  EXPECT_DOUBLE_EQ(hit.normal.y, -1.0);

  lm2_ray2_f64 too_short = boundary;
  too_short.t_max = 4.999;
  EXPECT_FALSE(lm2_raycast_circle_f64(too_short, tangent).hit);
  lm2_circle_f64 behind = lm2_circle_make_coords_f64(-5.0, 0.0, 1.0);
  EXPECT_FALSE(lm2_raycast_circle_f64(boundary, behind).hit);
}

TEST_F(Raycast2Test, AABBHitNormalIsOutwardAndParallelSlabsAreHandled_F64) {
  lm2_r2_f64 aabb = lm2_r2_from_min_max_f64(lm2_v2_make_f64(5.0, 1.0), lm2_v2_make_f64(8.0, 4.0));
  lm2_ray2_f64 ray = lm2_ray2_make_f64(lm2_v2_make_f64(0.0, 2.0), lm2_v2_make_f64(1.0, 0.0), 5.0);
  lm2_rayhit2_f64 hit = lm2_raycast_aabb_f64(ray, aabb);

  ASSERT_TRUE(hit.hit);
  EXPECT_DOUBLE_EQ(hit.t, ray.t_max);
  EXPECT_DOUBLE_EQ(hit.point.x, ray.origin.x + ray.direction.x * hit.t);
  EXPECT_DOUBLE_EQ(hit.point.y, ray.origin.y + ray.direction.y * hit.t);
  EXPECT_DOUBLE_EQ(hit.normal.x, -1.0);
  EXPECT_DOUBLE_EQ(hit.normal.y, 0.0);
  EXPECT_DOUBLE_EQ(std::hypot(hit.normal.x, hit.normal.y), 1.0);
  EXPECT_LT(hit.normal.x * ray.direction.x + hit.normal.y * ray.direction.y, 0.0);

  lm2_ray2_f64 parallel_outside =
      lm2_ray2_make_f64(lm2_v2_make_f64(0.0, 5.0), lm2_v2_make_f64(1.0, 0.0), 20.0);
  EXPECT_FALSE(lm2_raycast_aabb_f64(parallel_outside, aabb).hit);
}

TEST_F(Raycast2Test, PlaneRejectsBehindAndParallelAndAcceptsTMaxBoundary_F64) {
  lm2_plane2_f64 plane = lm2_plane2_make_f64(lm2_v2_make_f64(2.0, 0.0), 10.0);
  lm2_ray2_f64 boundary = lm2_ray2_make_f64(lm2_v2_make_f64(0.0, 1.0), lm2_v2_make_f64(1.0, 0.0), 5.0);
  lm2_rayhit2_f64 hit = lm2_raycast_plane2_f64(boundary, plane);
  ASSERT_TRUE(hit.hit);
  EXPECT_DOUBLE_EQ(hit.t, boundary.t_max);
  EXPECT_DOUBLE_EQ(hit.point.x, boundary.origin.x + boundary.direction.x * hit.t);
  EXPECT_DOUBLE_EQ(hit.point.y, boundary.origin.y + boundary.direction.y * hit.t);
  EXPECT_DOUBLE_EQ(std::hypot(hit.normal.x, hit.normal.y), 1.0);
  EXPECT_LT(hit.normal.x * boundary.direction.x + hit.normal.y * boundary.direction.y, 0.0);

  lm2_ray2_f64 behind = lm2_ray2_make_f64(lm2_v2_make_f64(6.0, 1.0), lm2_v2_make_f64(1.0, 0.0), 10.0);
  lm2_ray2_f64 parallel = lm2_ray2_make_f64(lm2_v2_make_f64(0.0, 1.0), lm2_v2_make_f64(0.0, 1.0), 10.0);
  EXPECT_FALSE(lm2_raycast_plane2_f64(behind, plane).hit);
  EXPECT_FALSE(lm2_raycast_plane2_f64(parallel, plane).hit);
}

TEST_F(Raycast2Test, GenericCircleDispatchMatchesPrimitive_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(6.0, 2.0, 2.0);
  lm2_ray2_f64 ray = lm2_ray2_make_f64(lm2_v2_make_f64(1.0, 2.0), lm2_v2_make_f64(1.0, 0.0), 10.0);
  lm2_rayhit2_f64 direct = lm2_raycast_circle_f64(ray, circle);
  lm2_rayhit2_f64 generic = lm2_raycast_shape2_f64(ray, lm2_shape2_from_circle_f64(&circle));

  ASSERT_TRUE(generic.hit);
  EXPECT_DOUBLE_EQ(generic.t, direct.t);
  EXPECT_DOUBLE_EQ(generic.point.x, direct.point.x);
  EXPECT_DOUBLE_EQ(generic.point.y, direct.point.y);
  EXPECT_DOUBLE_EQ(generic.normal.x, direct.normal.x);
  EXPECT_DOUBLE_EQ(generic.normal.y, direct.normal.y);
}

TEST_F(Raycast2Test, CircleTangentAtTMaxAndShortRay_F32) {
  auto ray = lm2_ray2_make_f32({0, 0}, {1, 0}, 5.0f);
  const auto circle = lm2_circle_make_coords_f32(5.0f, 1.0f, 1.0f);
  const auto hit = lm2_raycast_circle_f32(ray, circle);
  ASSERT_TRUE(hit.hit);
  EXPECT_FLOAT_EQ(hit.t, 5.0f);
  EXPECT_FLOAT_EQ(hit.point.x, 5.0f);
  EXPECT_FLOAT_EQ(hit.point.y, 0.0f);
  EXPECT_FLOAT_EQ(hit.normal.x, 0.0f);
  EXPECT_FLOAT_EQ(hit.normal.y, -1.0f);
  ray.t_max = 4.999f;
  EXPECT_FALSE(lm2_raycast_circle_f32(ray, circle).hit);
}

TEST_F(Raycast2Test, GenericDispatchAllPrimitives_F64) {
  const auto ray = lm2_ray2_make_f64({0, 0}, {1, 0}, 10);
  auto circle = lm2_circle_make_coords_f64(5, 0, 1);
  auto capsule = lm2_capsule2_make_coords_f64(5, -1, 5, 1, 1);
  auto box = lm2_r2_from_min_max_f64({5, -1}, {7, 1});
  lm2_triangle2_f64 triangle = {
      {5, -1},
      {7,  0},
      {5,  1}
  };
  lm2_v2_f64 vertices[] = {
      {5, -1},
      {7, -1},
      {7,  1},
      {5,  1}
  };
  auto polygon = lm2_polygon_make_f64(vertices, 4);
  auto edge = lm2_edge2_make_coords_f64(5, -1, 5, 1);
  struct Case {
    lm2_shape2_f64 shape;
    lm2_rayhit2_f64 direct;
    double distance;
  };
  const Case cases[] = {
      {lm2_shape2_from_circle_f64(&circle), lm2_raycast_circle_f64(ray, circle), 4},
      {lm2_shape2_from_capsule_f64(&capsule), lm2_raycast_capsule2_f64(ray, capsule), 4},
      {lm2_shape2_from_aabb2_f64(&box), lm2_raycast_aabb_f64(ray, box), 5},
      {lm2_shape2_from_triangle_f64(&triangle), lm2_raycast_triangle2_f64(ray, triangle), 5},
      {lm2_shape2_from_polygon_f64(&polygon), lm2_raycast_polygon_f64(ray, polygon), 5},
      {lm2_shape2_from_edge_f64(&edge), lm2_raycast_segment_f64(ray, edge.start, edge.end), 5},
  };
  for (const auto& c : cases) {
    SCOPED_TRACE(c.shape.type);
    const auto hit = lm2_raycast_shape2_f64(ray, c.shape);
    ASSERT_TRUE(hit.hit);
    ASSERT_TRUE(c.direct.hit);
    EXPECT_NEAR(hit.t, c.distance, 1e-10);
    EXPECT_NEAR(hit.t, c.direct.t, 1e-10);
    EXPECT_NEAR(hit.point.x, c.direct.point.x, 1e-10);
    EXPECT_NEAR(hit.point.y, c.direct.point.y, 1e-10);
    EXPECT_NEAR(hit.normal.x, c.direct.normal.x, 1e-10);
    EXPECT_NEAR(hit.normal.y, c.direct.normal.y, 1e-10);
  }
}

TEST_F(Raycast2Test, GenericDispatchAllPrimitives_F32) {
  const auto ray = lm2_ray2_make_f32({0, 0}, {1, 0}, 10);
  auto circle = lm2_circle_make_coords_f32(5, 0, 1);
  auto capsule = lm2_capsule2_make_coords_f32(5, -1, 5, 1, 1);
  auto box = lm2_r2_from_min_max_f32({5, -1}, {7, 1});
  lm2_triangle2_f32 triangle = {
      {5, -1},
      {7,  0},
      {5,  1}
  };
  lm2_v2_f32 vertices[] = {
      {5, -1},
      {7, -1},
      {7,  1},
      {5,  1}
  };
  auto polygon = lm2_polygon_make_f32(vertices, 4);
  auto edge = lm2_edge2_make_coords_f32(5, -1, 5, 1);
  struct Case {
    lm2_shape2_f32 shape;
    lm2_rayhit2_f32 direct;
    float distance;
  };
  const Case cases[] = {
      {lm2_shape2_from_circle_f32(&circle), lm2_raycast_circle_f32(ray, circle), 4},
      {lm2_shape2_from_capsule_f32(&capsule), lm2_raycast_capsule2_f32(ray, capsule), 4},
      {lm2_shape2_from_aabb2_f32(&box), lm2_raycast_aabb_f32(ray, box), 5},
      {lm2_shape2_from_triangle_f32(&triangle), lm2_raycast_triangle2_f32(ray, triangle), 5},
      {lm2_shape2_from_polygon_f32(&polygon), lm2_raycast_polygon_f32(ray, polygon), 5},
      {lm2_shape2_from_edge_f32(&edge), lm2_raycast_segment_f32(ray, edge.start, edge.end), 5},
  };
  for (const auto& c : cases) {
    SCOPED_TRACE(c.shape.type);
    const auto hit = lm2_raycast_shape2_f32(ray, c.shape);
    ASSERT_TRUE(hit.hit);
    ASSERT_TRUE(c.direct.hit);
    EXPECT_NEAR(hit.t, c.distance, 1e-5f);
    EXPECT_NEAR(hit.t, c.direct.t, 1e-5f);
    EXPECT_NEAR(hit.point.x, c.direct.point.x, 1e-5f);
    EXPECT_NEAR(hit.point.y, c.direct.point.y, 1e-5f);
    EXPECT_NEAR(hit.normal.x, c.direct.normal.x, 1e-5f);
    EXPECT_NEAR(hit.normal.y, c.direct.normal.y, 1e-5f);
  }
}

TEST_F(Raycast2Test, AABBAndPlaneBoundaryAndParallel_F32) {
  const auto box = lm2_r2_from_min_max_f32({5, 1}, {8, 4});
  auto ray = lm2_ray2_make_f32({0, 2}, {1, 0}, 5);
  const auto box_hit = lm2_raycast_aabb_f32(ray, box);
  ASSERT_TRUE(box_hit.hit);
  EXPECT_FLOAT_EQ(box_hit.t, 5.0f);
  EXPECT_FLOAT_EQ(box_hit.normal.x, -1.0f);
  EXPECT_FLOAT_EQ(box_hit.normal.y, 0.0f);
  ray.origin.y = 5;
  EXPECT_FALSE(lm2_raycast_aabb_f32(ray, box).hit);

  const auto plane = lm2_plane2_make_f32({2, 0}, 10);
  ray.origin.y = 1;
  const auto plane_hit = lm2_raycast_plane2_f32(ray, plane);
  ASSERT_TRUE(plane_hit.hit);
  EXPECT_FLOAT_EQ(plane_hit.t, 5.0f);
  EXPECT_FLOAT_EQ(plane_hit.normal.x, -1.0f);
  EXPECT_FLOAT_EQ(plane_hit.normal.y, 0.0f);
  ray.direction = {0, 1};
  EXPECT_FALSE(lm2_raycast_plane2_f32(ray, plane).hit);
  ray.direction = {1, 0};
  ray.origin.x = 6;
  EXPECT_FALSE(lm2_raycast_plane2_f32(ray, plane).hit);
}

TEST_F(Raycast2Test, CircleF64PreservesFineAndLargeCoordinateDistances) {
  const auto fine_ray = lm2_ray2_make_f64({0, 0}, {1, 0}, 10);
  const auto fine_circle = lm2_circle_make_coords_f64(5.00000001, 0, 1);
  const auto fine_hit = lm2_raycast_circle_f64(fine_ray, fine_circle);
  ASSERT_TRUE(fine_hit.hit);
  EXPECT_NEAR(fine_hit.t, 4.00000001, 1e-12);
  EXPECT_NEAR(fine_hit.point.x, 4.00000001, 1e-12);
  EXPECT_NEAR(fine_hit.normal.x, -1.0, 1e-12);
  EXPECT_NEAR(fine_hit.normal.y, 0.0, 1e-12);
  auto too_short = fine_ray;
  too_short.t_max = 4.0;
  EXPECT_FALSE(lm2_raycast_circle_f64(too_short, fine_circle).hit);

  const auto large_ray = lm2_ray2_make_f64({16777216, 0}, {1, 0}, 10);
  const auto large_circle = lm2_circle_make_coords_f64(16777221.25, 0, 1);
  const auto large_hit = lm2_raycast_circle_f64(large_ray, large_circle);
  ASSERT_TRUE(large_hit.hit);
  EXPECT_DOUBLE_EQ(large_hit.t, 4.25);
  EXPECT_DOUBLE_EQ(large_hit.point.x, 16777220.25);
  EXPECT_DOUBLE_EQ(large_hit.normal.x, -1.0);
}

TEST_F(Raycast2Test, AABBF64PreservesFineAndLargeCoordinateDistances) {
  const auto fine_ray = lm2_ray2_make_f64({0, 0}, {1, 0}, 10);
  const auto fine_box = lm2_r2_from_min_max_f64({5.00000001, -1}, {6, 1});
  const auto fine_hit = lm2_raycast_aabb_f64(fine_ray, fine_box);
  ASSERT_TRUE(fine_hit.hit);
  EXPECT_NEAR(fine_hit.t, 5.00000001, 1e-12);
  EXPECT_NEAR(fine_hit.point.x, 5.00000001, 1e-12);
  EXPECT_DOUBLE_EQ(fine_hit.normal.x, -1.0);
  EXPECT_DOUBLE_EQ(fine_hit.normal.y, 0.0);
  auto too_short = fine_ray;
  too_short.t_max = 5.0;
  EXPECT_FALSE(lm2_raycast_aabb_f64(too_short, fine_box).hit);

  const auto large_ray = lm2_ray2_make_f64({16777216, 0}, {1, 0}, 10);
  const auto large_box = lm2_r2_from_min_max_f64({16777221.25, -1}, {16777223, 1});
  const auto large_hit = lm2_raycast_aabb_f64(large_ray, large_box);
  ASSERT_TRUE(large_hit.hit);
  EXPECT_DOUBLE_EQ(large_hit.t, 5.25);
  EXPECT_DOUBLE_EQ(large_hit.point.x, 16777221.25);
  EXPECT_DOUBLE_EQ(large_hit.normal.x, -1.0);
}

TEST_F(Raycast2Test, CircleAndAABBF64InsideOriginsPreserveExistingResults) {
  const auto ray = lm2_ray2_make_f64({0, 0}, {1, 0}, 10);
  const auto circle = lm2_circle_make_coords_f64(0, 0, 1);
  const auto circle_hit = lm2_raycast_circle_f64(ray, circle);
  ASSERT_TRUE(circle_hit.hit);
  EXPECT_DOUBLE_EQ(circle_hit.t, 0.0);
  EXPECT_DOUBLE_EQ(circle_hit.point.x, 0.0);
  EXPECT_DOUBLE_EQ(circle_hit.normal.x, 0.0);
  EXPECT_DOUBLE_EQ(circle_hit.normal.y, 0.0);
  const auto box = lm2_r2_from_min_max_f64({-1, -1}, {1, 1});
  const auto box_hit = lm2_raycast_aabb_f64(ray, box);
  ASSERT_TRUE(box_hit.hit);
  EXPECT_DOUBLE_EQ(box_hit.t, 0.0);
  EXPECT_DOUBLE_EQ(box_hit.point.x, 0.0);
  EXPECT_DOUBLE_EQ(box_hit.normal.x, -1.0);
  EXPECT_DOUBLE_EQ(box_hit.normal.y, 0.0);
}

TEST_F(Raycast2Test, AABBF64ReturnsEntryNormalsOnEachFaceAndCorner) {
  const auto box = lm2_r2_from_min_max_f64({-1, -1}, {1, 1});
  struct Case {
    lm2_ray2_f64 ray;
    double nx;
    double ny;
    double t;
  };
  const Case cases[] = {
      { lm2_ray2_make_f64({-3, 0},                           {1, 0}, 2), -1,  0,                  2},
      {  lm2_ray2_make_f64({3, 0},                          {-1, 0}, 2),  1,  0,                  2},
      { lm2_ray2_make_f64({0, -3},                           {0, 1}, 2),  0, -1,                  2},
      {  lm2_ray2_make_f64({0, 3},                          {0, -1}, 2),  0,  1,                  2},
      {lm2_ray2_make_f64({-3, -3}, {std::sqrt(0.5), std::sqrt(0.5)}, 3), -1,  0, 2 * std::sqrt(2.0)},
  };
  for (const auto& c : cases) {
    const auto hit = lm2_raycast_aabb_f64(c.ray, box);
    ASSERT_TRUE(hit.hit);
    EXPECT_NEAR(hit.t, c.t, 1e-12);
    EXPECT_DOUBLE_EQ(hit.normal.x, c.nx);
    EXPECT_DOUBLE_EQ(hit.normal.y, c.ny);
  }
  const auto parallel = lm2_ray2_make_f64({-3, 2}, {1, 0}, 10);
  const auto miss = lm2_raycast_aabb_f64(parallel, box);
  EXPECT_FALSE(miss.hit);
  EXPECT_DOUBLE_EQ(miss.t, 0.0);
  EXPECT_DOUBLE_EQ(miss.point.x, 0.0);
  EXPECT_DOUBLE_EQ(miss.normal.x, 0.0);
}

TEST_F(Raycast2Test, CircleF64ResolvesRadiusAtLargeRelativeDistance) {
  const auto ray = lm2_ray2_make_f64({0, 0}, {1, 0}, 100000010);
  const auto circle = lm2_circle_make_coords_f64(100000000, 0, 1);
  const auto hit = lm2_raycast_circle_f64(ray, circle);
  ASSERT_TRUE(hit.hit);
  EXPECT_DOUBLE_EQ(hit.t, 99999999.0);
  EXPECT_DOUBLE_EQ(hit.point.x, 99999999.0);
  EXPECT_DOUBLE_EQ(hit.normal.x, -1.0);
  EXPECT_DOUBLE_EQ(hit.normal.y, 0.0);
  const auto offset_circle = lm2_circle_make_coords_f64(100000000, 0.5, 1);
  const auto offset_hit = lm2_raycast_circle_f64(ray, offset_circle);
  ASSERT_TRUE(offset_hit.hit);
  EXPECT_NEAR(offset_hit.t, 100000000.0 - std::sqrt(0.75), 2e-8);
  EXPECT_NEAR(offset_hit.normal.x, -std::sqrt(0.75), 2e-8);
  EXPECT_NEAR(offset_hit.normal.y, -0.5, 2e-8);
  EXPECT_FALSE(lm2_raycast_circle_f64(ray, lm2_circle_make_coords_f64(100000000, 1.1, 1)).hit);
}

TEST_F(Raycast2Test, PolygonAndTriangleF64RetainLargeCoordinatePrecision) {
  constexpr double x = 16777217.0;  // Not representable in a float.
  const auto ray = lm2_ray2_make_f64({0.0, 0.0}, {1.0, 0.0}, x + 4.0);
  lm2_v2_f64 vertices[] = {
      {      x, -1.0},
      {x + 2.0, -1.0},
      {x + 2.0,  1.0},
      {      x,  1.0}
  };
  lm2_polygon_f64 polygon = {vertices, 4};
  lm2_triangle2_f64 triangle = {
      {      x, -1.0},
      {x + 2.0,  0.0},
      {      x,  1.0}
  };

  const auto polygon_hit = lm2_raycast_polygon_f64(ray, polygon);
  ASSERT_TRUE(polygon_hit.hit);
  EXPECT_DOUBLE_EQ(polygon_hit.t, x);
  EXPECT_DOUBLE_EQ(polygon_hit.normal.x, -1.0);
  EXPECT_DOUBLE_EQ(polygon_hit.normal.y, 0.0);

  const auto triangle_hit = lm2_raycast_triangle2_f64(ray, triangle);
  ASSERT_TRUE(triangle_hit.hit);
  EXPECT_DOUBLE_EQ(triangle_hit.t, x);
  EXPECT_DOUBLE_EQ(triangle_hit.normal.x, -1.0);
  EXPECT_DOUBLE_EQ(triangle_hit.normal.y, 0.0);
}

TEST_F(Raycast2Test, CircleRaycastHandlesSmallAndLargeScales) {
  for (double scale : {1e-200, 1e200}) {
    const auto ray = lm2_ray2_make_f64({0, 0}, {1, 0}, 3 * scale);
    const auto hit = lm2_raycast_circle_f64(ray, lm2_circle_make_coords_f64(2 * scale, 0, scale));
    ASSERT_TRUE(hit.hit) << scale;
    EXPECT_NEAR(hit.t / scale, 1.0, 1e-12);
    EXPECT_NEAR(hit.normal.x, -1.0, 1e-12);
    EXPECT_NEAR(hit.normal.y, 0.0, 1e-12);
    EXPECT_FALSE(lm2_raycast_circle_f64(ray, lm2_circle_make_coords_f64(2 * scale, 2 * scale, scale)).hit);
    const auto tangent = lm2_raycast_circle_f64(ray, lm2_circle_make_coords_f64(2 * scale, scale, scale));
    ASSERT_TRUE(tangent.hit);
    EXPECT_NEAR(tangent.t / scale, 2.0, 1e-12);
    EXPECT_NEAR(tangent.normal.y, -1.0, 1e-12);
    const auto inside = lm2_raycast_circle_f64(ray, lm2_circle_make_coords_f64(0, 0, scale));
    ASSERT_TRUE(inside.hit);
    EXPECT_DOUBLE_EQ(inside.t, 0.0);
  }
  for (float scale : {1e-30f, 1e30f}) {
    const auto ray = lm2_ray2_make_f32({0, 0}, {1, 0}, 3 * scale);
    const auto hit = lm2_raycast_circle_f32(ray, lm2_circle_make_coords_f32(2 * scale, 0, scale));
    ASSERT_TRUE(hit.hit) << scale;
    EXPECT_NEAR(hit.t / scale, 1.0f, 1e-5f);
    EXPECT_NEAR(hit.normal.x, -1.0f, 1e-5f);
    EXPECT_NEAR(hit.normal.y, 0.0f, 1e-5f);
    EXPECT_FALSE(lm2_raycast_circle_f32(ray, lm2_circle_make_coords_f32(2 * scale, 2 * scale, scale)).hit);
    const auto tangent = lm2_raycast_circle_f32(ray, lm2_circle_make_coords_f32(2 * scale, scale, scale));
    ASSERT_TRUE(tangent.hit);
    EXPECT_NEAR(tangent.t / scale, 2.0f, 1e-5f);
    EXPECT_NEAR(tangent.normal.y, -1.0f, 1e-5f);
    const auto inside = lm2_raycast_circle_f32(ray, lm2_circle_make_coords_f32(0, 0, scale));
    ASSERT_TRUE(inside.hit);
    EXPECT_FLOAT_EQ(inside.t, 0.0f);
  }
}

TEST_F(Raycast2Test, CircleRaycastHandlesSubnormalScales) {
  const double radius64 = std::numeric_limits<double>::min() / 8.0;
  const auto ray64 = lm2_ray2_make_f64({0.0, 0.0}, {1.0, 0.0}, 4.0 * radius64);
  const auto hit64 = lm2_raycast_circle_f64(ray64, lm2_circle_make_coords_f64(2.0 * radius64, 0.0, radius64));
  ASSERT_TRUE(hit64.hit);
  EXPECT_DOUBLE_EQ(hit64.t, radius64);
  EXPECT_DOUBLE_EQ(hit64.normal.x, -1.0);

  const float radius32 = std::numeric_limits<float>::min() / 8.0f;
  const auto ray32 = lm2_ray2_make_f32({0.0f, 0.0f}, {1.0f, 0.0f}, 4.0f * radius32);
  const auto hit32 = lm2_raycast_circle_f32(ray32, lm2_circle_make_coords_f32(2.0f * radius32, 0.0f, radius32));
  ASSERT_TRUE(hit32.hit);
  EXPECT_FLOAT_EQ(hit32.t, radius32);
  EXPECT_FLOAT_EQ(hit32.normal.x, -1.0f);
}

TEST_F(Raycast2Test, CapsuleRaycastHandlesSmallAndLargeScales) {
  for (double s : {1e-200, 1e200}) {
    const auto ray = lm2_ray2_make_f64({0, 0}, {1, 0}, 4 * s);
    const auto capsule = lm2_capsule2_make_coords_f64(2 * s, -s, 2 * s, s, s / 2);
    const auto hit = lm2_raycast_capsule2_f64(ray, capsule);
    ASSERT_TRUE(hit.hit);
    EXPECT_NEAR(hit.t / s, 1.5, 1e-12);
    EXPECT_NEAR(hit.normal.x, -1.0, 1e-12);
  }
  for (float s : {1e-30f, 1e30f}) {
    const auto ray = lm2_ray2_make_f32({0, 0}, {1, 0}, 4 * s);
    const auto capsule = lm2_capsule2_make_coords_f32(2 * s, -s, 2 * s, s, s / 2);
    const auto hit = lm2_raycast_capsule2_f32(ray, capsule);
    ASSERT_TRUE(hit.hit);
    EXPECT_NEAR(hit.t / s, 1.5f, 1e-5f);
    EXPECT_NEAR(hit.normal.x, -1.0f, 1e-5f);
  }
}

TEST_F(Raycast2Test, PolygonF64ClipsParallelTangentAndDistanceBoundaries) {
  lm2_v2_f64 vertices[] = {
      {5.0, -1.0},
      {7.0, -1.0},
      {7.0,  1.0},
      {5.0,  1.0}
  };
  lm2_polygon_f64 polygon = {vertices, 4};
  auto ray = lm2_ray2_make_f64({0.0, 0.0}, {1.0, 0.0}, 5.0);
  const auto hit = lm2_raycast_polygon_f64(ray, polygon);
  ASSERT_TRUE(hit.hit);
  EXPECT_DOUBLE_EQ(hit.t, 5.0);
  EXPECT_DOUBLE_EQ(hit.point.x, 5.0);
  EXPECT_DOUBLE_EQ(hit.normal.x, -1.0);
  EXPECT_DOUBLE_EQ(hit.normal.y, 0.0);

  ray.t_max = std::nextafter(5.0, 0.0);
  EXPECT_FALSE(lm2_raycast_polygon_f64(ray, polygon).hit);
  ray.t_max = 10.0;
  ray.origin.y = 2.0;
  EXPECT_FALSE(lm2_raycast_polygon_f64(ray, polygon).hit);
  ray.origin.y = 1.0;
  EXPECT_TRUE(lm2_raycast_polygon_f64(ray, polygon).hit);
  ray.origin = {6.0, 0.0};
  EXPECT_FALSE(lm2_raycast_polygon_f64(ray, polygon).hit);
}

TEST_F(Raycast2Test, PolygonF64ClippingHandlesVerySmallAndLargeScales) {
  for (double scale : {1e-200, 1e200}) {
    lm2_v2_f64 vertices[] = {
        {    scale, -scale},
        {3 * scale, -scale},
        {3 * scale,  scale},
        {    scale,  scale}
    };
    lm2_polygon_f64 polygon = {vertices, 4};
    auto ray = lm2_ray2_make_f64({0.0, 0.0}, {1.0, 0.0}, 4 * scale);
    const auto hit = lm2_raycast_polygon_f64(ray, polygon);
    ASSERT_TRUE(hit.hit) << scale;
    EXPECT_DOUBLE_EQ(hit.t, scale);
    EXPECT_DOUBLE_EQ(hit.normal.x, -1.0);
    EXPECT_DOUBLE_EQ(hit.normal.y, 0.0);
  }
}

TEST_F(Raycast2Test, CapsuleF64RetainsLargeCoordinatePrecision) {
  constexpr double x = 16777217.0;
  auto ray = lm2_ray2_make_f64({0.0, 0.0}, {1.0, 0.0}, x + 4.0);
  auto capsule = lm2_capsule2_make_coords_f64(x + 1.0, -1.0, x + 1.0, 1.0, 1.0);
  const auto hit = lm2_raycast_capsule2_f64(ray, capsule);
  ASSERT_TRUE(hit.hit);
  EXPECT_DOUBLE_EQ(hit.t, x);
  EXPECT_NEAR(hit.normal.x, -1.0, 1e-12);
  EXPECT_NEAR(hit.normal.y, 0.0, 1e-12);
  ray.t_max = std::nextafter(x, 0.0);
  EXPECT_FALSE(lm2_raycast_capsule2_f64(ray, capsule).hit);
}

TEST_F(Raycast2Test, CapsuleF64HandlesInsideDegenerateAndSegmentCases) {
  auto capsule = lm2_capsule2_make_coords_f64(0.0, -2.0, 0.0, 2.0, 1.0);
  auto ray = lm2_ray2_make_f64({0.0, 0.0}, {1.0, 0.0}, 5.0);
  const auto inside = lm2_raycast_capsule2_f64(ray, capsule);
  ASSERT_TRUE(inside.hit);
  EXPECT_DOUBLE_EQ(inside.t, 0.0);
  EXPECT_DOUBLE_EQ(inside.normal.x, 0.0);
  EXPECT_DOUBLE_EQ(inside.normal.y, 1.0);

  capsule = lm2_capsule2_make_coords_f64(5.0, 0.0, 5.0, 0.0, 1.0);
  const auto point_capsule = lm2_raycast_capsule2_f64(ray, capsule);
  ASSERT_TRUE(point_capsule.hit);
  EXPECT_DOUBLE_EQ(point_capsule.t, 4.0);
  EXPECT_DOUBLE_EQ(point_capsule.normal.x, -1.0);

  const auto segment = lm2_raycast_segment_f64(ray, {5.0, -1.0}, {5.0, 1.0});
  ASSERT_TRUE(segment.hit);
  EXPECT_DOUBLE_EQ(segment.t, 5.0);
  EXPECT_DOUBLE_EQ(segment.normal.x, -1.0);
  EXPECT_DOUBLE_EQ(segment.normal.y, 0.0);

  ray = lm2_ray2_make_f64({10.0, 0.0}, {-1.0, 0.0}, 5.0);
  const auto reverse = lm2_raycast_segment_f64(ray, {5.0, -1.0}, {5.0, 1.0});
  ASSERT_TRUE(reverse.hit);
  EXPECT_DOUBLE_EQ(reverse.normal.x, 1.0);
  EXPECT_DOUBLE_EQ(reverse.normal.y, 0.0);
}

TEST_F(Raycast2Test, CapsuleF64HandlesTangenciesCapsAndReversedEndpoints) {
  auto capsule = lm2_capsule2_make_coords_f64(0.0, -2.0, 0.0, 2.0, 1.0);
  auto ray = lm2_ray2_make_f64({0.0, -5.0}, {0.0, 1.0}, 2.0);
  auto hit = lm2_raycast_capsule2_f64(ray, capsule);
  ASSERT_TRUE(hit.hit);
  EXPECT_DOUBLE_EQ(hit.t, 2.0);
  EXPECT_DOUBLE_EQ(hit.normal.x, 0.0);
  EXPECT_DOUBLE_EQ(hit.normal.y, -1.0);

  ray = lm2_ray2_make_f64({-5.0, 3.0}, {1.0, 0.0}, 5.0);
  hit = lm2_raycast_capsule2_f64(ray, capsule);
  ASSERT_TRUE(hit.hit);
  EXPECT_DOUBLE_EQ(hit.t, 5.0);
  EXPECT_DOUBLE_EQ(hit.normal.x, 0.0);
  EXPECT_DOUBLE_EQ(hit.normal.y, 1.0);
  ray.t_max = std::nextafter(5.0, 0.0);
  EXPECT_FALSE(lm2_raycast_capsule2_f64(ray, capsule).hit);

  capsule = lm2_capsule2_make_coords_f64(0.0, 2.0, 0.0, -2.0, 1.0);
  ray.t_max = 5.0;
  const auto reversed = lm2_raycast_capsule2_f64(ray, capsule);
  ASSERT_TRUE(reversed.hit);
  EXPECT_DOUBLE_EQ(reversed.t, hit.t);
  EXPECT_DOUBLE_EQ(reversed.normal.x, hit.normal.x);
  EXPECT_DOUBLE_EQ(reversed.normal.y, hit.normal.y);
}

TEST_F(Raycast2Test, AABBF64SurfaceOriginReturnsTheOutwardFaceNormal) {
  const auto box = lm2_r2_from_min_max_f64({0, 0}, {1, 1});
  struct Case {
    lm2_v2_f64 origin, direction, normal;
  };
  const Case cases[] = {
      {{0, 0.5},  {1, 0}, {-1, 0}},
      {{0, 0.5}, {-1, 0}, {-1, 0}},
      {{1, 0.5}, {-1, 0},  {1, 0}},
      {{1, 0.5},  {1, 0},  {1, 0}},
      {{0.5, 0},  {0, 1}, {0, -1}},
      {{0.5, 0}, {0, -1}, {0, -1}},
      {{0.5, 1}, {0, -1},  {0, 1}},
      {{0.5, 1},  {0, 1},  {0, 1}},
      {{1, 0.5},  {0, 1},  {1, 0}},
  };
  for (const auto& c : cases) {
    const auto hit = lm2_raycast_aabb_f64(lm2_ray2_make_f64(c.origin, c.direction, 1), box);
    ASSERT_TRUE(hit.hit);
    EXPECT_DOUBLE_EQ(hit.t, 0.0);
    EXPECT_DOUBLE_EQ(hit.normal.x, c.normal.x);
    EXPECT_DOUBLE_EQ(hit.normal.y, c.normal.y);
  }
}

TEST_F(Raycast2Test, AABBF32SurfaceOriginReturnsTheOutwardFaceNormal) {
  const auto box = lm2_r2_from_min_max_f32({0, 0}, {1, 1});
  struct Case {
    lm2_v2_f32 origin, direction, normal;
  };
  const Case cases[] = {
      {{0, 0.5f},  {1, 0}, {-1, 0}},
      {{0, 0.5f}, {-1, 0}, {-1, 0}},
      {{1, 0.5f}, {-1, 0},  {1, 0}},
      {{1, 0.5f},  {1, 0},  {1, 0}},
      {{0.5f, 0},  {0, 1}, {0, -1}},
      {{0.5f, 0}, {0, -1}, {0, -1}},
      {{0.5f, 1}, {0, -1},  {0, 1}},
      {{0.5f, 1},  {0, 1},  {0, 1}},
      {{1, 0.5f},  {0, 1},  {1, 0}},
  };
  for (const auto& c : cases) {
    const auto hit = lm2_raycast_aabb_f32(lm2_ray2_make_f32(c.origin, c.direction, 1), box);
    ASSERT_TRUE(hit.hit);
    EXPECT_FLOAT_EQ(hit.t, 0.0f);
    EXPECT_FLOAT_EQ(hit.normal.x, c.normal.x);
    EXPECT_FLOAT_EQ(hit.normal.y, c.normal.y);
  }
}

TEST_F(Raycast2Test, AABBF64HandlesSubnormalDirectionWithoutOverflow) {
  const auto box = lm2_r2_from_min_max_f64({-1, 1}, {1, 2});
  const auto ray = lm2_ray2_make_f64({0, 0}, {1e-320, 1}, 1);
  const auto hit = lm2_raycast_aabb_f64(ray, box);
  ASSERT_TRUE(hit.hit);
  EXPECT_DOUBLE_EQ(hit.t, 1.0);
  EXPECT_DOUBLE_EQ(hit.point.x, ray.direction.x);
  EXPECT_DOUBLE_EQ(hit.point.y, 1.0);
  EXPECT_DOUBLE_EQ(hit.normal.x, 0.0);
  EXPECT_DOUBLE_EQ(hit.normal.y, -1.0);
}

TEST_F(Raycast2Test, AABBF64ShallowDirectionCanHitAtLongDistance) {
  const auto box = lm2_r2_from_min_max_f64({1, 1e10}, {2, 1e10 + 10});
  const auto ray = lm2_ray2_make_f64({0, 0}, {1e-10, 1}, 1e10);
  const auto hit = lm2_raycast_aabb_f64(ray, box);
  ASSERT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 1e10, 1e-5);
  EXPECT_DOUBLE_EQ(hit.normal.x, -1.0);
}

TEST_F(Raycast2Test, AABBF64CanCrossSubnormalWidthSlab) {
  const double step = 1e-320;
  const auto box = lm2_r2_from_min_max_f64({2 * step, 1}, {3 * step, 3});
  const auto ray = lm2_ray2_make_f64({0, 0}, {step, 1}, 3);
  const auto hit = lm2_raycast_aabb_f64(ray, box);
  ASSERT_TRUE(hit.hit);
  EXPECT_DOUBLE_EQ(hit.t, 2.0);
  EXPECT_DOUBLE_EQ(hit.point.x, 2 * step);
  EXPECT_DOUBLE_EQ(hit.point.y, 2.0);
  EXPECT_DOUBLE_EQ(hit.normal.x, -1.0);
}
