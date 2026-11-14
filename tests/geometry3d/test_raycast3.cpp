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

TEST_F(Raycast3Test, SphereRaycastHandlesSmallAndLargeScales) {
  for (double scale : {1e-200, 1e200}) {
    const auto ray = lm2_ray3_make_f64({0, 0, 0}, {1, 0, 0}, 3 * scale);
    const auto hit = lm2_raycast_sphere_f64(ray, {2 * scale, 0, 0}, scale);
    ASSERT_TRUE(hit.hit) << scale;
    EXPECT_NEAR(hit.t / scale, 1.0, 1e-12);
    EXPECT_NEAR(hit.normal.x, -1.0, 1e-12);
    EXPECT_NEAR(hit.normal.y, 0.0, 1e-12);
    EXPECT_NEAR(hit.normal.z, 0.0, 1e-12);
    EXPECT_FALSE(lm2_raycast_sphere_f64(ray, {2 * scale, 2 * scale, 0}, scale).hit);
    const auto tangent = lm2_raycast_sphere_f64(ray, {2 * scale, scale, 0}, scale);
    ASSERT_TRUE(tangent.hit);
    EXPECT_NEAR(tangent.t / scale, 2.0, 1e-12);
    EXPECT_NEAR(tangent.normal.y, -1.0, 1e-12);
    const auto inside = lm2_raycast_sphere_f64(ray, {0, 0, 0}, scale);
    ASSERT_TRUE(inside.hit);
    EXPECT_NEAR(inside.t / scale, 1.0, 1e-12);
  }
  for (float scale : {1e-30f, 1e30f}) {
    const auto ray = lm2_ray3_make_f32({0, 0, 0}, {1, 0, 0}, 3 * scale);
    const auto hit = lm2_raycast_sphere_f32(ray, {2 * scale, 0, 0}, scale);
    ASSERT_TRUE(hit.hit) << scale;
    EXPECT_NEAR(hit.t / scale, 1.0f, 1e-5f);
    EXPECT_NEAR(hit.normal.x, -1.0f, 1e-5f);
    EXPECT_NEAR(hit.normal.y, 0.0f, 1e-5f);
    EXPECT_NEAR(hit.normal.z, 0.0f, 1e-5f);
    EXPECT_FALSE(lm2_raycast_sphere_f32(ray, {2 * scale, 2 * scale, 0}, scale).hit);
    const auto tangent = lm2_raycast_sphere_f32(ray, {2 * scale, scale, 0}, scale);
    ASSERT_TRUE(tangent.hit);
    EXPECT_NEAR(tangent.t / scale, 2.0f, 1e-5f);
    EXPECT_NEAR(tangent.normal.y, -1.0f, 1e-5f);
    const auto inside = lm2_raycast_sphere_f32(ray, {0, 0, 0}, scale);
    ASSERT_TRUE(inside.hit);
    EXPECT_NEAR(inside.t / scale, 1.0f, 1e-5f);
  }
}

TEST_F(Raycast3Test, CapsuleRaycastHandlesSmallAndLargeScales) {
  for (double s : {1e-200, 1e200}) {
    const auto ray = lm2_ray3_make_f64({0, 0, 0}, {1, 0, 0}, 4 * s);
    const auto hit = lm2_raycast_capsule_f64(ray, {2 * s, -s, 0}, {2 * s, s, 0}, s / 2);
    ASSERT_TRUE(hit.hit) << s;
    EXPECT_NEAR(hit.t / s, 1.5, 1e-12);
    EXPECT_NEAR(hit.normal.x, -1.0, 1e-12);
    EXPECT_NEAR(hit.normal.y, 0.0, 1e-12);
    EXPECT_FALSE(lm2_raycast_capsule_f64(ray, {2 * s, -s, 2 * s}, {2 * s, s, 2 * s}, s / 2).hit);
    const auto cap = lm2_raycast_capsule_f64(ray, {2 * s, 0, 0}, {3 * s, 0, 0}, s / 2);
    ASSERT_TRUE(cap.hit);
    EXPECT_NEAR(cap.t / s, 1.5, 1e-12);
    const auto inner_ray = lm2_ray3_make_f64({2 * s, 0, 0}, {1, 0, 0}, s);
    const auto exit = lm2_raycast_capsule_f64(inner_ray, {2 * s, -s, 0}, {2 * s, s, 0}, s / 2);
    ASSERT_TRUE(exit.hit);
    EXPECT_NEAR(exit.t / s, 0.5, 1e-12);
  }
  for (float s : {1e-30f, 1e30f}) {
    const auto ray = lm2_ray3_make_f32({0, 0, 0}, {1, 0, 0}, 4 * s);
    const auto hit = lm2_raycast_capsule_f32(ray, {2 * s, -s, 0}, {2 * s, s, 0}, s / 2);
    ASSERT_TRUE(hit.hit) << s;
    EXPECT_NEAR(hit.t / s, 1.5f, 1e-5f);
    EXPECT_NEAR(hit.normal.x, -1.0f, 1e-5f);
    EXPECT_NEAR(hit.normal.y, 0.0f, 1e-5f);
    EXPECT_FALSE(lm2_raycast_capsule_f32(ray, {2 * s, -s, 2 * s}, {2 * s, s, 2 * s}, s / 2).hit);
    const auto cap = lm2_raycast_capsule_f32(ray, {2 * s, 0, 0}, {3 * s, 0, 0}, s / 2);
    ASSERT_TRUE(cap.hit);
    EXPECT_NEAR(cap.t / s, 1.5f, 1e-5f);
    const auto inner_ray = lm2_ray3_make_f32({2 * s, 0, 0}, {1, 0, 0}, s);
    const auto exit = lm2_raycast_capsule_f32(inner_ray, {2 * s, -s, 0}, {2 * s, s, 0}, s / 2);
    ASSERT_TRUE(exit.hit);
    EXPECT_NEAR(exit.t / s, 0.5f, 1e-5f);
  }
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

TEST_F(Raycast3Test, SphereBoundaryTangentHasOutwardUnitNormalAndConsistentPoint_F64) {
  lm2_ray3_f64 ray = lm2_ray3_make_f64(
      lm2_v3_make_f64(0.0, 0.0, 0.0), lm2_v3_make_f64(1.0, 0.0, 0.0), 5.0);
  lm2_v3_f64 center = lm2_v3_make_f64(5.0, 1.0, 0.0);
  lm2_rayhit3_f64 hit = lm2_raycast_sphere_f64(ray, center, 1.0);

  ASSERT_TRUE(hit.hit);
  EXPECT_DOUBLE_EQ(hit.t, ray.t_max);
  EXPECT_DOUBLE_EQ(hit.point.x, ray.origin.x + ray.direction.x * hit.t);
  EXPECT_DOUBLE_EQ(hit.point.y, ray.origin.y + ray.direction.y * hit.t);
  EXPECT_DOUBLE_EQ(hit.point.z, ray.origin.z + ray.direction.z * hit.t);
  EXPECT_DOUBLE_EQ(hit.normal.x, 0.0);
  EXPECT_DOUBLE_EQ(hit.normal.y, -1.0);
  EXPECT_DOUBLE_EQ(hit.normal.z, 0.0);
  EXPECT_DOUBLE_EQ(std::sqrt(hit.normal.x * hit.normal.x + hit.normal.y * hit.normal.y +
                             hit.normal.z * hit.normal.z),
                   1.0);

  ray.t_max = 4.999;
  EXPECT_FALSE(lm2_raycast_sphere_f64(ray, center, 1.0).hit);
  lm2_ray3_f64 forward = lm2_ray3_make_f64(
      lm2_v3_make_f64(0.0, 0.0, 0.0), lm2_v3_make_f64(1.0, 0.0, 0.0), 10.0);
  EXPECT_FALSE(lm2_raycast_sphere_f64(forward, lm2_v3_make_f64(-5.0, 0.0, 0.0), 1.0).hit);
}

TEST_F(Raycast3Test, AABBAcceptsTMaxBoundaryAndRejectsParallelOutside_F64) {
  lm2_aabb3_f64 aabb = lm2_aabb3_from_min_max_f64(
      lm2_v3_make_f64(5.0, -1.0, -1.0), lm2_v3_make_f64(8.0, 1.0, 1.0));
  lm2_ray3_f64 boundary = lm2_ray3_make_f64(
      lm2_v3_make_f64(0.0, 0.0, 0.0), lm2_v3_make_f64(1.0, 0.0, 0.0), 5.0);
  lm2_rayhit3_f64 hit = lm2_raycast_aabb3_f64(boundary, aabb);

  ASSERT_TRUE(hit.hit);
  EXPECT_DOUBLE_EQ(hit.t, boundary.t_max);
  EXPECT_DOUBLE_EQ(hit.point.x, boundary.origin.x + boundary.direction.x * hit.t);
  EXPECT_DOUBLE_EQ(hit.point.y, boundary.origin.y + boundary.direction.y * hit.t);
  EXPECT_DOUBLE_EQ(hit.point.z, boundary.origin.z + boundary.direction.z * hit.t);
  EXPECT_DOUBLE_EQ(hit.normal.x, -1.0);
  EXPECT_DOUBLE_EQ(hit.normal.y, 0.0);
  EXPECT_DOUBLE_EQ(hit.normal.z, 0.0);

  lm2_ray3_f64 parallel_outside = lm2_ray3_make_f64(
      lm2_v3_make_f64(0.0, 2.0, 0.0), lm2_v3_make_f64(1.0, 0.0, 0.0), 20.0);
  EXPECT_FALSE(lm2_raycast_aabb3_f64(parallel_outside, aabb).hit);
}

TEST_F(Raycast3Test, AABBAcceptsTMaxBoundary_F32) {
  lm2_aabb3_f32 aabb = lm2_aabb3_from_min_max_f32(
      lm2_v3_make_f32(5.0f, -1.0f, -1.0f), lm2_v3_make_f32(8.0f, 1.0f, 1.0f));
  lm2_ray3_f32 ray = lm2_ray3_make_f32(
      lm2_v3_make_f32(0.0f, 0.0f, 0.0f), lm2_v3_make_f32(1.0f, 0.0f, 0.0f), 5.0f);
  lm2_rayhit3_f32 hit = lm2_raycast_aabb3_f32(ray, aabb);

  ASSERT_TRUE(hit.hit);
  EXPECT_FLOAT_EQ(hit.t, ray.t_max);
  EXPECT_FLOAT_EQ(hit.normal.x, -1.0f);
}

TEST_F(Raycast3Test, PlaneReturnsSuppliedOutwardDirectionAsUnitNormal_F64) {
  lm2_ray3_f64 ray = lm2_ray3_make_f64(
      lm2_v3_make_f64(5.0, 1.0, 2.0), lm2_v3_make_f64(-1.0, 0.0, 0.0), 5.0);
  lm2_rayhit3_f64 hit = lm2_raycast_plane_f64(
      ray, lm2_v3_make_f64(0.0, 0.0, 0.0), lm2_v3_make_f64(2.0, 0.0, 0.0));

  ASSERT_TRUE(hit.hit);
  EXPECT_DOUBLE_EQ(hit.t, ray.t_max);
  EXPECT_DOUBLE_EQ(hit.point.x, ray.origin.x + ray.direction.x * hit.t);
  EXPECT_DOUBLE_EQ(hit.point.y, ray.origin.y + ray.direction.y * hit.t);
  EXPECT_DOUBLE_EQ(hit.point.z, ray.origin.z + ray.direction.z * hit.t);
  EXPECT_DOUBLE_EQ(hit.normal.x, 1.0);
  EXPECT_DOUBLE_EQ(hit.normal.y, 0.0);
  EXPECT_DOUBLE_EQ(hit.normal.z, 0.0);
}

TEST_F(Raycast3Test, PlaneReturnsSuppliedOutwardDirectionAsUnitNormal_F32) {
  lm2_ray3_f32 ray = lm2_ray3_make_f32(
      lm2_v3_make_f32(5.0f, 0.0f, 0.0f), lm2_v3_make_f32(-1.0f, 0.0f, 0.0f), 5.0f);
  lm2_rayhit3_f32 hit = lm2_raycast_plane_f32(
      ray, lm2_v3_make_f32(0.0f, 0.0f, 0.0f), lm2_v3_make_f32(3.0f, 0.0f, 0.0f));

  ASSERT_TRUE(hit.hit);
  EXPECT_FLOAT_EQ(hit.normal.x, 1.0f);
  EXPECT_FLOAT_EQ(hit.normal.y, 0.0f);
  EXPECT_FLOAT_EQ(hit.normal.z, 0.0f);
}

TEST_F(Raycast3Test, GenericSphereDispatchMatchesPrimitive_F64) {
  lm2_sphere_f64 sphere = lm2_sphere_make_coords_f64(5.0, 0.0, 0.0, 1.0);
  lm2_ray3_f64 ray = lm2_ray3_make_f64(
      lm2_v3_make_f64(0.0, 0.0, 0.0), lm2_v3_make_f64(1.0, 0.0, 0.0), 10.0);
  lm2_rayhit3_f64 direct = lm2_raycast_sphere_f64(ray, sphere.center, sphere.radius);
  lm2_rayhit3_f64 generic = lm2_raycast_shape3_f64(ray, lm2_shape3_from_sphere_f64(&sphere));

  ASSERT_TRUE(generic.hit);
  EXPECT_DOUBLE_EQ(generic.t, direct.t);
  EXPECT_DOUBLE_EQ(generic.point.x, direct.point.x);
  EXPECT_DOUBLE_EQ(generic.point.y, direct.point.y);
  EXPECT_DOUBLE_EQ(generic.point.z, direct.point.z);
  EXPECT_DOUBLE_EQ(generic.normal.x, direct.normal.x);
  EXPECT_DOUBLE_EQ(generic.normal.y, direct.normal.y);
  EXPECT_DOUBLE_EQ(generic.normal.z, direct.normal.z);
}

TEST_F(Raycast3Test, SphereTangentAtTMaxAndShortRay_F32) {
  auto ray = lm2_ray3_make_f32({0, 0, 0}, {1, 0, 0}, 5.0f);
  const auto hit = lm2_raycast_sphere_f32(ray, {5, 1, 0}, 1.0f);
  ASSERT_TRUE(hit.hit);
  EXPECT_FLOAT_EQ(hit.t, 5.0f);
  EXPECT_FLOAT_EQ(hit.point.x, 5.0f);
  EXPECT_FLOAT_EQ(hit.point.y, 0.0f);
  EXPECT_FLOAT_EQ(hit.point.z, 0.0f);
  EXPECT_FLOAT_EQ(hit.normal.x, 0.0f);
  EXPECT_FLOAT_EQ(hit.normal.y, -1.0f);
  EXPECT_FLOAT_EQ(hit.normal.z, 0.0f);
  ray.t_max = 4.999f;
  EXPECT_FALSE(lm2_raycast_sphere_f32(ray, {5, 1, 0}, 1.0f).hit);
}

TEST_F(Raycast3Test, GenericDispatchAllPrimitives_F64) {
  const auto ray = lm2_ray3_make_f64({0, 0, 0}, {1, 0, 0}, 10);
  auto sphere = lm2_sphere_make_coords_f64(5, 0, 0, 1);
  auto capsule = lm2_capsule3_make_coords_f64(5, -1, 0, 5, 1, 0, 1);
  auto box = lm2_aabb3_from_min_max_f64({5, -1, -1}, {7, 1, 1});
  lm2_triangle3_f64 triangle = {
      {5, -1, -1},
      {5,  1, -1},
      {5,  0,  1}
  };
  auto edge = lm2_edge3_make_coords_f64(5, -1, 0, 5, 1, 0);
  struct Case {
    lm2_shape3_f64 shape;
    lm2_rayhit3_f64 direct;
    double distance;
  };
  const Case cases[] = {
      {lm2_shape3_from_sphere_f64(&sphere), lm2_raycast_sphere_f64(ray, sphere.center, sphere.radius), 4},
      {lm2_shape3_from_capsule_f64(&capsule), lm2_raycast_capsule_f64(ray, capsule.start, capsule.end, capsule.radius), 4},
      {lm2_shape3_from_aabb3_f64(&box), lm2_raycast_aabb3_f64(ray, box), 5},
      {lm2_shape3_from_triangle_f64(&triangle), lm2_raycast_triangle_f64(ray, triangle[0], triangle[1], triangle[2]), 5},
      {lm2_shape3_from_edge_f64(&edge), lm2_raycast_edge_f64(ray, edge.start, edge.end, LM2_RAYCAST3_EPSILON_F64), 5},
  };
  for (const auto& c : cases) {
    SCOPED_TRACE(c.shape.type);
    const auto hit = lm2_raycast_shape3_f64(ray, c.shape);
    ASSERT_TRUE(hit.hit);
    ASSERT_TRUE(c.direct.hit);
    EXPECT_NEAR(hit.t, c.distance, 1e-10);
    EXPECT_NEAR(hit.t, c.direct.t, 1e-10);
    EXPECT_NEAR(hit.point.x, c.direct.point.x, 1e-10);
    EXPECT_NEAR(hit.point.y, c.direct.point.y, 1e-10);
    EXPECT_NEAR(hit.point.z, c.direct.point.z, 1e-10);
    EXPECT_NEAR(hit.normal.x, c.direct.normal.x, 1e-10);
    EXPECT_NEAR(hit.normal.y, c.direct.normal.y, 1e-10);
    EXPECT_NEAR(hit.normal.z, c.direct.normal.z, 1e-10);
  }
}

TEST_F(Raycast3Test, GenericDispatchAllPrimitives_F32) {
  const auto ray = lm2_ray3_make_f32({0, 0, 0}, {1, 0, 0}, 10);
  auto sphere = lm2_sphere_make_coords_f32(5, 0, 0, 1);
  auto capsule = lm2_capsule3_make_coords_f32(5, -1, 0, 5, 1, 0, 1);
  auto box = lm2_aabb3_from_min_max_f32({5, -1, -1}, {7, 1, 1});
  lm2_triangle3_f32 triangle = {
      {5, -1, -1},
      {5,  1, -1},
      {5,  0,  1}
  };
  auto edge = lm2_edge3_make_coords_f32(5, -1, 0, 5, 1, 0);
  struct Case {
    lm2_shape3_f32 shape;
    lm2_rayhit3_f32 direct;
    float distance;
  };
  const Case cases[] = {
      {lm2_shape3_from_sphere_f32(&sphere), lm2_raycast_sphere_f32(ray, sphere.center, sphere.radius), 4},
      {lm2_shape3_from_capsule_f32(&capsule), lm2_raycast_capsule_f32(ray, capsule.start, capsule.end, capsule.radius), 4},
      {lm2_shape3_from_aabb3_f32(&box), lm2_raycast_aabb3_f32(ray, box), 5},
      {lm2_shape3_from_triangle_f32(&triangle), lm2_raycast_triangle_f32(ray, triangle[0], triangle[1], triangle[2]), 5},
      {lm2_shape3_from_edge_f32(&edge), lm2_raycast_edge_f32(ray, edge.start, edge.end, LM2_RAYCAST3_EPSILON_F32), 5},
  };
  for (const auto& c : cases) {
    SCOPED_TRACE(c.shape.type);
    const auto hit = lm2_raycast_shape3_f32(ray, c.shape);
    ASSERT_TRUE(hit.hit);
    ASSERT_TRUE(c.direct.hit);
    EXPECT_NEAR(hit.t, c.distance, 1e-5f);
    EXPECT_NEAR(hit.t, c.direct.t, 1e-5f);
    EXPECT_NEAR(hit.point.x, c.direct.point.x, 1e-5f);
    EXPECT_NEAR(hit.point.y, c.direct.point.y, 1e-5f);
    EXPECT_NEAR(hit.point.z, c.direct.point.z, 1e-5f);
    EXPECT_NEAR(hit.normal.x, c.direct.normal.x, 1e-5f);
    EXPECT_NEAR(hit.normal.y, c.direct.normal.y, 1e-5f);
    EXPECT_NEAR(hit.normal.z, c.direct.normal.z, 1e-5f);
  }
}

TEST_F(Raycast3Test, SphereOriginInsideAndBehind_F32) {
  const auto ray = lm2_ray3_make_f32({0, 0, 0}, {1, 0, 0}, 10);
  const auto inside = lm2_raycast_sphere_f32(ray, {0, 0, 0}, 2);
  ASSERT_TRUE(inside.hit);
  EXPECT_FLOAT_EQ(inside.t, 2.0f);
  EXPECT_FLOAT_EQ(inside.point.x, 2.0f);
  EXPECT_FLOAT_EQ(inside.normal.x, 1.0f);
  EXPECT_FLOAT_EQ(inside.normal.y, 0.0f);
  EXPECT_FLOAT_EQ(inside.normal.z, 0.0f);
  EXPECT_FALSE(lm2_raycast_sphere_f32(ray, {-5, 0, 0}, 1).hit);
}

// Exercise the same geometric boundaries in both supported precisions.
#define LM2_RAYCAST3_BOUNDARY_TESTS(suffix, scalar, vec, big, small_direction, tolerance)                       \
  TEST_F(Raycast3Test, AABBEntryFacesAndShallowDirection_##suffix) {                                            \
    const auto box = lm2_r3_from_min_max_##suffix(vec {-100, -1, -1}, vec {100, 1, 1});                         \
    auto ray = lm2_ray3_make_##suffix(vec {50, -5, 0}, vec {0, 1, 0}, 4);                                       \
    auto hit = lm2_raycast_aabb3_##suffix(ray, box);                                                            \
    ASSERT_TRUE(hit.hit);                                                                                       \
    EXPECT_NEAR(hit.t, 4, tolerance);                                                                           \
    EXPECT_NEAR(hit.normal.x, 0, tolerance);                                                                    \
    EXPECT_NEAR(hit.normal.y, -1, tolerance);                                                                   \
    EXPECT_NEAR(hit.normal.z, 0, tolerance);                                                                    \
    ray = lm2_ray3_make_##suffix(vec {0, 1, 0}, vec {0, -1, 0}, 1);                                             \
    hit = lm2_raycast_aabb3_##suffix(ray, box);                                                                 \
    ASSERT_TRUE(hit.hit);                                                                                       \
    EXPECT_NEAR(hit.t, 0, tolerance);                                                                           \
    EXPECT_NEAR(hit.normal.y, 1, tolerance);                                                                    \
    const scalar shallow = (scalar)(small_direction);                                                           \
    const scalar distance = (scalar)1 / shallow;                                                                \
    const auto far_box = lm2_r3_from_min_max_##suffix(vec {1, distance - 100, -1}, vec {2, distance + 100, 1}); \
    ray = lm2_ray3_make_##suffix(vec {0, 0, 0}, vec {shallow, 1, 0}, distance + 100);                           \
    hit = lm2_raycast_aabb3_##suffix(ray, far_box);                                                             \
    ASSERT_TRUE(hit.hit);                                                                                       \
    EXPECT_NEAR(hit.t, distance, (scalar)1);                                                                    \
    EXPECT_NEAR(hit.normal.x, -1, tolerance);                                                                   \
  }                                                                                                             \
  TEST_F(Raycast3Test, SphereFarDistanceAndZeroLengthRay_##suffix) {                                            \
    const scalar distance = (scalar)(big);                                                                      \
    auto ray = lm2_ray3_make_##suffix(vec {0, 0, 0}, vec {1, 0, 0}, distance + 10);                             \
    auto hit = lm2_raycast_sphere_##suffix(ray, vec {distance, 0, 0}, 1);                                       \
    ASSERT_TRUE(hit.hit);                                                                                       \
    EXPECT_NEAR(hit.t, distance - 1, tolerance);                                                                \
    EXPECT_NEAR(hit.normal.x, -1, tolerance);                                                                   \
    ray = lm2_ray3_from_points_##suffix(vec {0, 0, 0}, vec {0, 0, 0});                                          \
    hit = lm2_raycast_sphere_##suffix(ray, vec {0, 0, 0}, 1);                                                   \
    ASSERT_TRUE(hit.hit);                                                                                       \
    EXPECT_NEAR(hit.t, 0, tolerance);                                                                           \
    EXPECT_FALSE(lm2_raycast_sphere_##suffix(ray, vec {3, 0, 0}, 1).hit);                                       \
  }                                                                                                             \
  TEST_F(Raycast3Test, CapsuleEndpointLimitAndInsideAxis_##suffix) {                                            \
    const vec start {0, -2, 0}, end {0, 2, 0};                                                                  \
    auto ray = lm2_ray3_make_##suffix(vec {-5, 0, 0}, vec {1, 0, 0}, 4);                                        \
    auto hit = lm2_raycast_capsule_##suffix(ray, start, end, 1);                                                \
    ASSERT_TRUE(hit.hit);                                                                                       \
    EXPECT_NEAR(hit.t, 4, tolerance);                                                                           \
    EXPECT_NEAR(hit.normal.x, -1, tolerance);                                                                   \
    ray = lm2_ray3_make_##suffix(vec {0, 0, 0}, vec {0, 1, 0}, 5);                                              \
    hit = lm2_raycast_capsule_##suffix(ray, start, end, 1);                                                     \
    ASSERT_TRUE(hit.hit);                                                                                       \
    EXPECT_NEAR(hit.t, 3, tolerance);                                                                           \
    EXPECT_NEAR(hit.normal.y, 1, tolerance);                                                                    \
    ray = lm2_ray3_from_points_##suffix(vec {0, 0, 0}, vec {0, 0, 0});                                          \
    hit = lm2_raycast_capsule_##suffix(ray, start, end, 1);                                                     \
    ASSERT_TRUE(hit.hit);                                                                                       \
    EXPECT_NEAR(hit.t, 0, tolerance);                                                                           \
  }                                                                                                             \
  TEST_F(Raycast3Test, EdgeParallelAndDegenerateClosestApproach_##suffix) {                                     \
    auto ray = lm2_ray3_make_##suffix(vec {0, 0, 0}, vec {1, 0, 0}, 10);                                        \
    auto hit = lm2_raycast_edge_##suffix(ray, vec {5, 0, 0}, vec {8, 0, 0}, 0);                                 \
    ASSERT_TRUE(hit.hit);                                                                                       \
    EXPECT_NEAR(hit.t, 5, tolerance);                                                                           \
    EXPECT_NEAR(hit.normal.x, 0, tolerance);                                                                    \
    hit = lm2_raycast_edge_##suffix(ray, vec {5, 1, 0}, vec {5, 1, 0}, 1);                                      \
    ASSERT_TRUE(hit.hit);                                                                                       \
    EXPECT_NEAR(hit.t, 5, tolerance);                                                                           \
    ray.t_max = 4;                                                                                              \
    EXPECT_FALSE(lm2_raycast_edge_##suffix(ray, vec {5, 0, 0}, vec {8, 0, 0}, 0).hit);                          \
  }                                                                                                             \
  TEST_F(Raycast3Test, TriangleAcceptsSurfaceAndEdgeHits_##suffix) {                                            \
    const vec a {0, 0, 0}, b {2, 0, 0}, c {0, 2, 0};                                                            \
    auto ray = lm2_ray3_make_##suffix(vec {1, 1, 3}, vec {0, 0, -1}, 3);                                        \
    auto hit = lm2_raycast_triangle_##suffix(ray, a, b, c);                                                     \
    ASSERT_TRUE(hit.hit);                                                                                       \
    EXPECT_NEAR(hit.t, 3, tolerance);                                                                           \
    EXPECT_NEAR(hit.normal.z, 1, tolerance);                                                                    \
    ray = lm2_ray3_make_##suffix(vec {0.5, 0.5, 0}, vec {0, 0, 1}, 1);                                          \
    hit = lm2_raycast_triangle_##suffix(ray, a, b, c);                                                          \
    ASSERT_TRUE(hit.hit);                                                                                       \
    EXPECT_NEAR(hit.t, 0, tolerance);                                                                           \
  }

LM2_RAYCAST3_BOUNDARY_TESTS(f64, double, lm2_v3_f64, 100000000.0, 5e-10, 1e-9)
LM2_RAYCAST3_BOUNDARY_TESTS(f32, float, lm2_v3_f32, 10000.0f, 5e-7f, 1e-5f)
#undef LM2_RAYCAST3_BOUNDARY_TESTS

TEST_F(Raycast3Test, AABBHandlesSubnormalDirectionComponent_F64) {
  const auto box = lm2_r3_from_min_max_f64({-1, 1, -1}, {1, 2, 1});
  const auto ray = lm2_ray3_make_f64({0, 0, 0}, {1e-320, 1, 0}, 1);
  const auto hit = lm2_raycast_aabb3_f64(ray, box);
  ASSERT_TRUE(hit.hit);
  EXPECT_DOUBLE_EQ(hit.t, 1);
  EXPECT_DOUBLE_EQ(hit.point.x, ray.direction.x);
  EXPECT_DOUBLE_EQ(hit.point.y, 1);
  EXPECT_DOUBLE_EQ(hit.normal.y, -1);
}

TEST_F(Raycast3Test, AABBHandlesSubnormalDirectionComponent_F32) {
  const auto box = lm2_r3_from_min_max_f32({-1, 1, -1}, {1, 2, 1});
  const auto ray = lm2_ray3_make_f32({0, 0, 0}, {1e-40f, 1, 0}, 1);
  const auto hit = lm2_raycast_aabb3_f32(ray, box);
  ASSERT_TRUE(hit.hit);
  EXPECT_FLOAT_EQ(hit.t, 1);
  EXPECT_FLOAT_EQ(hit.point.x, ray.direction.x);
  EXPECT_FLOAT_EQ(hit.point.y, 1);
  EXPECT_FLOAT_EQ(hit.normal.y, -1);
}

#define LM2_RAYCAST3_CAPSULE_AND_EDGE_EXTRA(suffix, type, vec, tol)              \
  TEST_F(Raycast3Test, CapsuleEndcapsInteriorAndDegenerateAxis_##suffix) {       \
    const vec start {0, -2, 0}, end {0, 2, 0};                                   \
    auto ray = lm2_ray3_make_##suffix(vec {-5, 3, 0}, vec {1, 0, 0}, 5);         \
    auto hit = lm2_raycast_capsule_##suffix(ray, start, end, 1);                 \
    ASSERT_TRUE(hit.hit);                                                        \
    EXPECT_NEAR(hit.t, 5, tol);                                                  \
    EXPECT_NEAR(hit.normal.y, 1, tol);                                           \
    ray = lm2_ray3_make_##suffix(vec {0, 2.5, 0}, vec {1, 0, 0}, 2);             \
    hit = lm2_raycast_capsule_##suffix(ray, start, end, 1);                      \
    ASSERT_TRUE(hit.hit);                                                        \
    EXPECT_NEAR(hit.t, std::sqrt((type)0.75), tol);                              \
    ray = lm2_ray3_make_##suffix(vec {2, -5, 0}, vec {0, 1, 0}, 10);             \
    EXPECT_FALSE(lm2_raycast_capsule_##suffix(ray, start, end, 1).hit);          \
    ray = lm2_ray3_make_##suffix(vec {-3, 0, 0}, vec {1, 0, 0}, 2);              \
    hit = lm2_raycast_capsule_##suffix(ray, vec {0, 0, 0}, vec {0, 0, 0}, 1);    \
    ASSERT_TRUE(hit.hit);                                                        \
    EXPECT_NEAR(hit.t, 2, tol);                                                  \
  }                                                                              \
  TEST_F(Raycast3Test, EdgeClosestPointsRespectRayAndSegmentEnds_##suffix) {     \
    auto ray = lm2_ray3_make_##suffix(vec {0, 0, 0}, vec {1, 0, 0}, 4);          \
    auto hit = lm2_raycast_edge_##suffix(ray, vec {5, -1, 0}, vec {5, 1, 0}, 1); \
    ASSERT_TRUE(hit.hit);                                                        \
    EXPECT_NEAR(hit.t, 4, tol);                                                  \
    EXPECT_NEAR(hit.normal.x, -1, tol);                                          \
    ray.t_max = 10;                                                              \
    hit = lm2_raycast_edge_##suffix(ray, vec {8, 0, 0}, vec {5, 0, 0}, 0);       \
    ASSERT_TRUE(hit.hit);                                                        \
    EXPECT_NEAR(hit.t, 5, tol);                                                  \
    ray = lm2_ray3_from_points_##suffix(vec {0, 0, 0}, vec {0, 0, 0});           \
    hit = lm2_raycast_edge_##suffix(ray, vec {-1, 1, 0}, vec {1, 1, 0}, 1);      \
    ASSERT_TRUE(hit.hit);                                                        \
    EXPECT_NEAR(hit.t, 0, tol);                                                  \
  }

LM2_RAYCAST3_CAPSULE_AND_EDGE_EXTRA(f64, double, lm2_v3_f64, 1e-9)
LM2_RAYCAST3_CAPSULE_AND_EDGE_EXTRA(f32, float, lm2_v3_f32, 1e-5f)
#undef LM2_RAYCAST3_CAPSULE_AND_EDGE_EXTRA

TEST_F(Raycast3Test, CapsuleRetainsRadiusAtLongDistance_F64) {
  auto ray = lm2_ray3_make_f64({-1e8, 0, 0}, {1, 0, 0}, 1e8 + 1);
  auto hit = lm2_raycast_capsule_f64(ray, {0, -2, 0}, {0, 2, 0}, 1);
  ASSERT_TRUE(hit.hit);
  EXPECT_DOUBLE_EQ(hit.t, 1e8 - 1);
  EXPECT_DOUBLE_EQ(hit.normal.x, -1);
}

TEST_F(Raycast3Test, CapsuleRetainsRadiusAtLongDistance_F32) {
  auto ray = lm2_ray3_make_f32({-10000, 0, 0}, {1, 0, 0}, 10001);
  auto hit = lm2_raycast_capsule_f32(ray, {0, -2, 0}, {0, 2, 0}, 1);
  ASSERT_TRUE(hit.hit);
  EXPECT_FLOAT_EQ(hit.t, 9999);
  EXPECT_FLOAT_EQ(hit.normal.x, -1);
}

TEST_F(Raycast3Test, EdgeNearParallelIntersection_F64) {
  auto ray = lm2_ray3_make_f64({0, 0, 0}, {1, 0, 0}, 1e9);
  auto hit = lm2_raycast_edge_f64(ray, {0, 1, 0}, {1e9, 0, 0}, 0);
  ASSERT_TRUE(hit.hit);
  EXPECT_DOUBLE_EQ(hit.t, 1e9);
}

TEST_F(Raycast3Test, EdgeNearParallelIntersection_F32) {
  auto ray = lm2_ray3_make_f32({0, 0, 0}, {1, 0, 0}, 1e5f);
  auto hit = lm2_raycast_edge_f32(ray, {0, 1, 0}, {1e5f, 0, 0}, 0);
  ASSERT_TRUE(hit.hit);
  EXPECT_FLOAT_EQ(hit.t, 1e5f);
}

TEST_F(Raycast3Test, CapsuleHandlesSubnormalDirectionComponent_F64) {
  auto ray = lm2_ray3_make_f64({0, 0, 0}, {1e-320, 1, 0}, 2);
  auto hit = lm2_raycast_capsule_f64(ray, {0, 2, 0}, {0, 4, 0}, 1);
  ASSERT_TRUE(hit.hit);
  EXPECT_DOUBLE_EQ(hit.t, 1);
  EXPECT_DOUBLE_EQ(hit.point.x, ray.direction.x);
  EXPECT_DOUBLE_EQ(hit.normal.y, -1);
}

TEST_F(Raycast3Test, CapsuleHandlesSubnormalDirectionComponent_F32) {
  auto ray = lm2_ray3_make_f32({0, 0, 0}, {1e-40f, 1, 0}, 2);
  auto hit = lm2_raycast_capsule_f32(ray, {0, 2, 0}, {0, 4, 0}, 1);
  ASSERT_TRUE(hit.hit);
  EXPECT_FLOAT_EQ(hit.t, 1);
  EXPECT_FLOAT_EQ(hit.point.x, ray.direction.x);
  EXPECT_FLOAT_EQ(hit.normal.y, -1);
}
