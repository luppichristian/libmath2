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
#include "lm2/geometry3d/lm2_aabb3.h"
#include "lm2/geometry3d/lm2_plane3.h"
#include "lm2/geometry3d/lm2_raycast3.h"

// Test fixture for Raycast3 tests
class Raycast3Test : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Ray Construction Tests (f64)
// =============================================================================

TEST_F(Raycast3Test, RayMake_F64) {
  lm2_v3_f64 origin = lm2_v3_make_f64(1.0, 2.0, 3.0);
  lm2_v3_f64 direction = lm2_v3_make_f64(1.0, 0.0, 0.0);
  lm2_ray3_f64 ray = lm2_ray3_make_f64(origin, direction, 100.0);

  EXPECT_DOUBLE_EQ(ray.origin.x, 1.0);
  EXPECT_DOUBLE_EQ(ray.origin.y, 2.0);
  EXPECT_DOUBLE_EQ(ray.origin.z, 3.0);
  EXPECT_DOUBLE_EQ(ray.direction.x, 1.0);
  EXPECT_DOUBLE_EQ(ray.t_max, 100.0);
}

TEST_F(Raycast3Test, RayFromPoints_F64) {
  lm2_v3_f64 start = lm2_v3_make_f64(0.0, 0.0, 0.0);
  lm2_v3_f64 end = lm2_v3_make_f64(10.0, 0.0, 0.0);
  lm2_ray3_f64 ray = lm2_ray3_from_points_f64(start, end);

  EXPECT_DOUBLE_EQ(ray.origin.x, 0.0);
  EXPECT_NEAR(ray.direction.x, 1.0, EPSILON_F64);
  EXPECT_NEAR(ray.t_max, 10.0, EPSILON_F64);
}

TEST_F(Raycast3Test, RayPointAt_F64) {
  lm2_ray3_f64 ray = lm2_ray3_make_f64(
      lm2_v3_make_f64(0.0, 0.0, 0.0),
      lm2_v3_make_f64(1.0, 0.0, 0.0),
      100.0);

  lm2_v3_f64 point = lm2_ray3_point_at_f64(ray, 5.0);
  EXPECT_NEAR(point.x, 5.0, EPSILON_F64);
  EXPECT_NEAR(point.y, 0.0, EPSILON_F64);
  EXPECT_NEAR(point.z, 0.0, EPSILON_F64);
}

// =============================================================================
// Ray Construction Tests (f32)
// =============================================================================

TEST_F(Raycast3Test, RayMake_F32) {
  lm2_v3_f32 origin = lm2_v3_make_f32(1.0f, 2.0f, 3.0f);
  lm2_v3_f32 direction = lm2_v3_make_f32(1.0f, 0.0f, 0.0f);
  lm2_ray3_f32 ray = lm2_ray3_make_f32(origin, direction, 100.0f);

  EXPECT_FLOAT_EQ(ray.origin.x, 1.0f);
  EXPECT_FLOAT_EQ(ray.t_max, 100.0f);
}

TEST_F(Raycast3Test, RayFromPoints_F32) {
  lm2_v3_f32 start = lm2_v3_make_f32(0.0f, 0.0f, 0.0f);
  lm2_v3_f32 end = lm2_v3_make_f32(10.0f, 0.0f, 0.0f);
  lm2_ray3_f32 ray = lm2_ray3_from_points_f32(start, end);

  EXPECT_NEAR(ray.direction.x, 1.0f, EPSILON_F32);
}

TEST_F(Raycast3Test, RayPointAt_F32) {
  lm2_ray3_f32 ray = lm2_ray3_make_f32(
      lm2_v3_make_f32(0.0f, 0.0f, 0.0f),
      lm2_v3_make_f32(1.0f, 0.0f, 0.0f),
      100.0f);

  lm2_v3_f32 point = lm2_ray3_point_at_f32(ray, 5.0f);
  EXPECT_NEAR(point.x, 5.0f, EPSILON_F32);
}

// =============================================================================
// Ray vs Sphere Tests (f64)
// =============================================================================

TEST_F(Raycast3Test, RaySphere_Hit_F64) {
  lm2_ray3_f64 ray = lm2_ray3_make_f64(
      lm2_v3_make_f64(0.0, 0.0, 0.0),
      lm2_v3_make_f64(1.0, 0.0, 0.0),
      100.0);

  lm2_v3_f64 center = lm2_v3_make_f64(10.0, 0.0, 0.0);
  double radius = 2.0;

  lm2_rayhit3_f64 hit = lm2_raycast_sphere_f64(ray, center, radius);

  EXPECT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 8.0, EPSILON_F64);  // Distance to sphere surface (10 - 2)
  EXPECT_NEAR(hit.point.x, 8.0, EPSILON_F64);
}

TEST_F(Raycast3Test, RaySphere_Miss_F64) {
  lm2_ray3_f64 ray = lm2_ray3_make_f64(
      lm2_v3_make_f64(0.0, 0.0, 0.0),
      lm2_v3_make_f64(1.0, 0.0, 0.0),
      100.0);

  lm2_v3_f64 center = lm2_v3_make_f64(10.0, 10.0, 0.0);
  double radius = 2.0;

  lm2_rayhit3_f64 hit = lm2_raycast_sphere_f64(ray, center, radius);

  EXPECT_FALSE(hit.hit);
}

// =============================================================================
// Ray vs Sphere Tests (f32)
// =============================================================================

TEST_F(Raycast3Test, RaySphere_Hit_F32) {
  lm2_ray3_f32 ray = lm2_ray3_make_f32(
      lm2_v3_make_f32(0.0f, 0.0f, 0.0f),
      lm2_v3_make_f32(1.0f, 0.0f, 0.0f),
      100.0f);

  lm2_v3_f32 center = lm2_v3_make_f32(10.0f, 0.0f, 0.0f);
  float radius = 2.0f;

  lm2_rayhit3_f32 hit = lm2_raycast_sphere_f32(ray, center, radius);

  EXPECT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 8.0f, EPSILON_F32);
}

TEST_F(Raycast3Test, RaySphere_Miss_F32) {
  lm2_ray3_f32 ray = lm2_ray3_make_f32(
      lm2_v3_make_f32(0.0f, 0.0f, 0.0f),
      lm2_v3_make_f32(1.0f, 0.0f, 0.0f),
      100.0f);

  lm2_v3_f32 center = lm2_v3_make_f32(10.0f, 10.0f, 0.0f);
  float radius = 2.0f;

  lm2_rayhit3_f32 hit = lm2_raycast_sphere_f32(ray, center, radius);

  EXPECT_FALSE(hit.hit);
}

// =============================================================================
// Ray vs AABB3 Tests (f64)
// =============================================================================

TEST_F(Raycast3Test, RayAABB_Hit_F64) {
  lm2_ray3_f64 ray = lm2_ray3_make_f64(
      lm2_v3_make_f64(0.0, 0.0, 0.0),
      lm2_v3_make_f64(1.0, 0.0, 0.0),
      100.0);

  lm2_aabb3_f64 aabb = lm2_aabb3_from_min_max_f64(
      lm2_v3_make_f64(5.0, -1.0, -1.0),
      lm2_v3_make_f64(10.0, 1.0, 1.0));

  lm2_rayhit3_f64 hit = lm2_raycast_aabb3_f64(ray, aabb);

  EXPECT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 5.0, EPSILON_F64);
}

TEST_F(Raycast3Test, RayAABB_Miss_F64) {
  lm2_ray3_f64 ray = lm2_ray3_make_f64(
      lm2_v3_make_f64(0.0, 0.0, 0.0),
      lm2_v3_make_f64(1.0, 0.0, 0.0),
      100.0);

  lm2_aabb3_f64 aabb = lm2_aabb3_from_min_max_f64(
      lm2_v3_make_f64(5.0, 5.0, 5.0),
      lm2_v3_make_f64(10.0, 10.0, 10.0));

  lm2_rayhit3_f64 hit = lm2_raycast_aabb3_f64(ray, aabb);

  EXPECT_FALSE(hit.hit);
}

// =============================================================================
// Ray vs AABB3 Tests (f32)
// =============================================================================

TEST_F(Raycast3Test, RayAABB_Hit_F32) {
  lm2_ray3_f32 ray = lm2_ray3_make_f32(
      lm2_v3_make_f32(0.0f, 0.0f, 0.0f),
      lm2_v3_make_f32(1.0f, 0.0f, 0.0f),
      100.0f);

  lm2_aabb3_f32 aabb = lm2_aabb3_from_min_max_f32(
      lm2_v3_make_f32(5.0f, -1.0f, -1.0f),
      lm2_v3_make_f32(10.0f, 1.0f, 1.0f));

  lm2_rayhit3_f32 hit = lm2_raycast_aabb3_f32(ray, aabb);

  EXPECT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 5.0f, EPSILON_F32);
}

// =============================================================================
// Ray vs Triangle Tests (f64)
// =============================================================================

TEST_F(Raycast3Test, RayTriangle_Hit_F64) {
  lm2_ray3_f64 ray = lm2_ray3_make_f64(
      lm2_v3_make_f64(1.0, 1.0, 5.0),
      lm2_v3_make_f64(0.0, 0.0, -1.0),
      100.0);

  // Triangle in XY plane at z=0
  lm2_v3_f64 v0 = lm2_v3_make_f64(0.0, 0.0, 0.0);
  lm2_v3_f64 v1 = lm2_v3_make_f64(4.0, 0.0, 0.0);
  lm2_v3_f64 v2 = lm2_v3_make_f64(0.0, 4.0, 0.0);

  lm2_rayhit3_f64 hit = lm2_raycast_triangle_f64(ray, v0, v1, v2);

  EXPECT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 5.0, EPSILON_F64);
  EXPECT_NEAR(hit.point.z, 0.0, EPSILON_F64);
}

TEST_F(Raycast3Test, RayTriangle_Miss_F64) {
  lm2_ray3_f64 ray = lm2_ray3_make_f64(
      lm2_v3_make_f64(10.0, 10.0, 5.0),
      lm2_v3_make_f64(0.0, 0.0, -1.0),
      100.0);

  lm2_v3_f64 v0 = lm2_v3_make_f64(0.0, 0.0, 0.0);
  lm2_v3_f64 v1 = lm2_v3_make_f64(4.0, 0.0, 0.0);
  lm2_v3_f64 v2 = lm2_v3_make_f64(0.0, 4.0, 0.0);

  lm2_rayhit3_f64 hit = lm2_raycast_triangle_f64(ray, v0, v1, v2);

  EXPECT_FALSE(hit.hit);
}

// =============================================================================
// Ray vs Triangle Tests (f32)
// =============================================================================

TEST_F(Raycast3Test, RayTriangle_Hit_F32) {
  lm2_ray3_f32 ray = lm2_ray3_make_f32(
      lm2_v3_make_f32(1.0f, 1.0f, 5.0f),
      lm2_v3_make_f32(0.0f, 0.0f, -1.0f),
      100.0f);

  lm2_v3_f32 v0 = lm2_v3_make_f32(0.0f, 0.0f, 0.0f);
  lm2_v3_f32 v1 = lm2_v3_make_f32(4.0f, 0.0f, 0.0f);
  lm2_v3_f32 v2 = lm2_v3_make_f32(0.0f, 4.0f, 0.0f);

  lm2_rayhit3_f32 hit = lm2_raycast_triangle_f32(ray, v0, v1, v2);

  EXPECT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 5.0f, EPSILON_F32);
}

// =============================================================================
// Ray vs Plane Tests (f64)
// =============================================================================

TEST_F(Raycast3Test, RayPlane_Hit_F64) {
  lm2_ray3_f64 ray = lm2_ray3_make_f64(
      lm2_v3_make_f64(0.0, 5.0, 0.0),
      lm2_v3_make_f64(0.0, -1.0, 0.0),
      100.0);

  lm2_v3_f64 planePoint = lm2_v3_make_f64(0.0, 0.0, 0.0);
  lm2_v3_f64 planeNormal = lm2_v3_make_f64(0.0, 1.0, 0.0);

  lm2_rayhit3_f64 hit = lm2_raycast_plane_f64(ray, planePoint, planeNormal);

  EXPECT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 5.0, EPSILON_F64);
  EXPECT_NEAR(hit.point.y, 0.0, EPSILON_F64);
}

TEST_F(Raycast3Test, RayPlane_Parallel_F64) {
  // Ray parallel to plane
  lm2_ray3_f64 ray = lm2_ray3_make_f64(
      lm2_v3_make_f64(0.0, 5.0, 0.0),
      lm2_v3_make_f64(1.0, 0.0, 0.0),
      100.0);

  lm2_v3_f64 planePoint = lm2_v3_make_f64(0.0, 0.0, 0.0);
  lm2_v3_f64 planeNormal = lm2_v3_make_f64(0.0, 1.0, 0.0);

  lm2_rayhit3_f64 hit = lm2_raycast_plane_f64(ray, planePoint, planeNormal);

  EXPECT_FALSE(hit.hit);
}

// =============================================================================
// Ray vs Plane Tests (f32)
// =============================================================================

TEST_F(Raycast3Test, RayPlane_Hit_F32) {
  lm2_ray3_f32 ray = lm2_ray3_make_f32(
      lm2_v3_make_f32(0.0f, 5.0f, 0.0f),
      lm2_v3_make_f32(0.0f, -1.0f, 0.0f),
      100.0f);

  lm2_v3_f32 planePoint = lm2_v3_make_f32(0.0f, 0.0f, 0.0f);
  lm2_v3_f32 planeNormal = lm2_v3_make_f32(0.0f, 1.0f, 0.0f);

  lm2_rayhit3_f32 hit = lm2_raycast_plane_f32(ray, planePoint, planeNormal);

  EXPECT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 5.0f, EPSILON_F32);
}

// =============================================================================
// Ray vs Capsule Tests (f64)
// =============================================================================

TEST_F(Raycast3Test, RayCapsule_Hit_F64) {
  lm2_ray3_f64 ray = lm2_ray3_make_f64(
      lm2_v3_make_f64(0.0, 5.0, 0.0),
      lm2_v3_make_f64(0.0, -1.0, 0.0),
      100.0);

  lm2_v3_f64 start = lm2_v3_make_f64(-5.0, 0.0, 0.0);
  lm2_v3_f64 end = lm2_v3_make_f64(5.0, 0.0, 0.0);
  double radius = 2.0;

  lm2_rayhit3_f64 hit = lm2_raycast_capsule_f64(ray, start, end, radius);

  EXPECT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 3.0, EPSILON_F64);  // 5 - 2 (radius)
}

TEST_F(Raycast3Test, RayCapsule_Miss_F64) {
  lm2_ray3_f64 ray = lm2_ray3_make_f64(
      lm2_v3_make_f64(0.0, 5.0, 10.0),
      lm2_v3_make_f64(0.0, -1.0, 0.0),
      100.0);

  lm2_v3_f64 start = lm2_v3_make_f64(-5.0, 0.0, 0.0);
  lm2_v3_f64 end = lm2_v3_make_f64(5.0, 0.0, 0.0);
  double radius = 2.0;

  lm2_rayhit3_f64 hit = lm2_raycast_capsule_f64(ray, start, end, radius);

  EXPECT_FALSE(hit.hit);
}

// =============================================================================
// Ray vs Capsule Tests (f32)
// =============================================================================

TEST_F(Raycast3Test, RayCapsule_Hit_F32) {
  lm2_ray3_f32 ray = lm2_ray3_make_f32(
      lm2_v3_make_f32(0.0f, 5.0f, 0.0f),
      lm2_v3_make_f32(0.0f, -1.0f, 0.0f),
      100.0f);

  lm2_v3_f32 start = lm2_v3_make_f32(-5.0f, 0.0f, 0.0f);
  lm2_v3_f32 end = lm2_v3_make_f32(5.0f, 0.0f, 0.0f);
  float radius = 2.0f;

  lm2_rayhit3_f32 hit = lm2_raycast_capsule_f32(ray, start, end, radius);

  EXPECT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 3.0f, EPSILON_F32);
}

// =============================================================================
// Ray vs Edge Tests (f64)
// =============================================================================

TEST_F(Raycast3Test, RayEdge_CloseApproach_F64) {
  lm2_ray3_f64 ray = lm2_ray3_make_f64(
      lm2_v3_make_f64(0.0, 0.0, 5.0),
      lm2_v3_make_f64(0.0, 0.0, -1.0),
      100.0);

  lm2_v3_f64 edgeStart = lm2_v3_make_f64(-5.0, 0.0, 0.0);
  lm2_v3_f64 edgeEnd = lm2_v3_make_f64(5.0, 0.0, 0.0);

  lm2_rayhit3_f64 hit = lm2_raycast_edge_f64(ray, edgeStart, edgeEnd, 0.1);

  EXPECT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 5.0, EPSILON_F64);
}

// =============================================================================
// Ray vs Edge Tests (f32)
// =============================================================================

TEST_F(Raycast3Test, RayEdge_CloseApproach_F32) {
  lm2_ray3_f32 ray = lm2_ray3_make_f32(
      lm2_v3_make_f32(0.0f, 0.0f, 5.0f),
      lm2_v3_make_f32(0.0f, 0.0f, -1.0f),
      100.0f);

  lm2_v3_f32 edgeStart = lm2_v3_make_f32(-5.0f, 0.0f, 0.0f);
  lm2_v3_f32 edgeEnd = lm2_v3_make_f32(5.0f, 0.0f, 0.0f);

  lm2_rayhit3_f32 hit = lm2_raycast_edge_f32(ray, edgeStart, edgeEnd, 0.1f);

  EXPECT_TRUE(hit.hit);
  EXPECT_NEAR(hit.t, 5.0f, EPSILON_F32);
}

// =============================================================================
// Edge Cases
// =============================================================================

TEST_F(Raycast3Test, RayOriginInsideSphere_F64) {
  // Ray starting inside sphere
  lm2_ray3_f64 ray = lm2_ray3_make_f64(
      lm2_v3_make_f64(0.0, 0.0, 0.0),
      lm2_v3_make_f64(1.0, 0.0, 0.0),
      100.0);

  lm2_v3_f64 center = lm2_v3_make_f64(0.0, 0.0, 0.0);
  double radius = 5.0;

  lm2_rayhit3_f64 hit = lm2_raycast_sphere_f64(ray, center, radius);

  // Should hit the sphere (exiting)
  EXPECT_TRUE(hit.hit);
}

TEST_F(Raycast3Test, RayTooShort_F64) {
  // Ray with t_max too small to reach target
  lm2_ray3_f64 ray = lm2_ray3_make_f64(
      lm2_v3_make_f64(0.0, 0.0, 0.0),
      lm2_v3_make_f64(1.0, 0.0, 0.0),
      5.0  // Only reaches to x=5
  );

  lm2_v3_f64 center = lm2_v3_make_f64(10.0, 0.0, 0.0);
  double radius = 2.0;

  lm2_rayhit3_f64 hit = lm2_raycast_sphere_f64(ray, center, radius);

  EXPECT_FALSE(hit.hit);
}
