#include <gtest/gtest.h>
#include <cmath>
#include "lm2/geometry2d/lm2_raycast2.h"
#include "lm2/geometry3d/lm2_raycast3.h"

TEST(CapsuleRayExtremeTest, DistantTangentDoesNotCollapseAxis) {
  const auto ray64 = lm2_ray3_make_f64({-1e200, 0.5, 0}, {1, 0, 0}, 2e200);
  const auto hit64 = lm2_raycast_capsule_f64(ray64, {0, -1, 0}, {0, 1, 0}, 0.5);
  ASSERT_TRUE(hit64.hit);
  EXPECT_DOUBLE_EQ(hit64.t, 1e200);
  EXPECT_NEAR(hit64.normal.x, -1.0, 1e-12);
  EXPECT_NEAR(hit64.normal.y, 0.0, 1e-12);

  const auto ray32 = lm2_ray3_make_f32({-1e30f, 0.5f, 0}, {1, 0, 0}, 2e30f);
  const auto hit32 = lm2_raycast_capsule_f32(ray32, {0, -1, 0}, {0, 1, 0}, 0.5f);
  ASSERT_TRUE(hit32.hit);
  EXPECT_FLOAT_EQ(hit32.t, 1e30f);
  EXPECT_NEAR(hit32.normal.x, -1.0f, 1e-5f);
  EXPECT_NEAR(hit32.normal.y, 0.0f, 1e-5f);

  const auto ray2d64 = lm2_ray2_make_f64({-1e200, 0.5}, {1, 0}, 2e200);
  const auto capsule64 = lm2_capsule2_make_coords_f64(0, -1, 0, 1, 0.5);
  const auto hit2d64 = lm2_raycast_capsule2_f64(ray2d64, capsule64);
  ASSERT_TRUE(hit2d64.hit);
  EXPECT_DOUBLE_EQ(hit2d64.t, 1e200);
  EXPECT_NEAR(hit2d64.normal.x, -1.0, 1e-12);

  const auto ray2d32 = lm2_ray2_make_f32({-1e30f, 0.5f}, {1, 0}, 2e30f);
  const auto capsule32 = lm2_capsule2_make_coords_f32(0, -1, 0, 1, 0.5f);
  const auto hit2d32 = lm2_raycast_capsule2_f32(ray2d32, capsule32);
  ASSERT_TRUE(hit2d32.hit);
  EXPECT_FLOAT_EQ(hit2d32.t, 1e30f);
  EXPECT_NEAR(hit2d32.normal.x, -1.0f, 1e-5f);
}

TEST(CapsuleRayExtremeTest, NegativeMaxDistanceIsEmptyForCircleAndSphere) {
  const auto ray2d64 = lm2_ray2_make_f64({0, 0}, {1, 0}, -1);
  const auto ray2d32 = lm2_ray2_make_f32({0, 0}, {1, 0}, -1);
  EXPECT_FALSE(lm2_raycast_circle_f64(ray2d64, lm2_circle_make_coords_f64(0, 0, 1)).hit);
  EXPECT_FALSE(lm2_raycast_circle_f32(ray2d32, lm2_circle_make_coords_f32(0, 0, 1)).hit);
  const auto ray3d64 = lm2_ray3_make_f64({0, 0, 0}, {0, 0, 0}, -1);
  const auto ray3d32 = lm2_ray3_make_f32({0, 0, 0}, {0, 0, 0}, -1);
  EXPECT_FALSE(lm2_raycast_sphere_f64(ray3d64, {0, 0, 0}, 1).hit);
  EXPECT_FALSE(lm2_raycast_sphere_f32(ray3d32, {0, 0, 0}, 1).hit);
}

TEST(CapsuleRayExtremeTest, DistantSideTangencyCapAndMiss) {
  const auto tangent64 = lm2_ray3_make_f64({-1e200, 0, 0.5}, {1, 0, 0}, 2e200);
  const auto hit64 = lm2_raycast_capsule_f64(tangent64, {0, -1, 0}, {0, 1, 0}, 0.5);
  ASSERT_TRUE(hit64.hit);
  EXPECT_NEAR(hit64.normal.z, 1.0, 1e-12);
  const auto cap64 = lm2_ray3_make_f64({-1e200, 1.25, 0}, {1, 0, 0}, 2e200);
  const auto cap_hit64 = lm2_raycast_capsule_f64(cap64, {0, -1, 0}, {0, 1, 0}, 0.5);
  ASSERT_TRUE(cap_hit64.hit);
  EXPECT_NEAR(cap_hit64.normal.x, -std::sqrt(0.75), 1e-12);
  EXPECT_NEAR(cap_hit64.normal.y, 0.5, 1e-12);
  const auto miss64 = lm2_ray3_make_f64({-1e200, 0, 0.6}, {1, 0, 0}, 2e200);
  EXPECT_FALSE(lm2_raycast_capsule_f64(miss64, {0, -1, 0}, {0, 1, 0}, 0.5).hit);

  const auto tangent32 = lm2_ray3_make_f32({-1e30f, 0, 0.5f}, {1, 0, 0}, 2e30f);
  const auto hit32 = lm2_raycast_capsule_f32(tangent32, {0, -1, 0}, {0, 1, 0}, 0.5f);
  ASSERT_TRUE(hit32.hit);
  EXPECT_NEAR(hit32.normal.z, 1.0f, 1e-5f);
  const auto cap32 = lm2_ray3_make_f32({-1e30f, 1.25f, 0}, {1, 0, 0}, 2e30f);
  const auto cap_hit32 = lm2_raycast_capsule_f32(cap32, {0, -1, 0}, {0, 1, 0}, 0.5f);
  ASSERT_TRUE(cap_hit32.hit);
  EXPECT_NEAR(cap_hit32.normal.x, -std::sqrt(0.75f), 1e-5f);
  EXPECT_NEAR(cap_hit32.normal.y, 0.5f, 1e-5f);
  const auto miss32 = lm2_ray3_make_f32({-1e30f, 0, 0.6f}, {1, 0, 0}, 2e30f);
  EXPECT_FALSE(lm2_raycast_capsule_f32(miss32, {0, -1, 0}, {0, 1, 0}, 0.5f).hit);
}

TEST(CapsuleRayExtremeTest, DistantDiagonalAxisRetainsAxialCoordinates) {
  const auto miss64 = lm2_ray3_make_f64({-1e200, 1.5, 0}, {1, 0, 0}, 2e200);
  EXPECT_FALSE(lm2_raycast_capsule_f64(miss64, {-1, -1, 0}, {1, 1, 0}, 0.25).hit);
  const auto cap64 = lm2_ray3_make_f64({-1e200, 1.25, 0}, {1, 0, 0}, 2e200);
  const auto hit64 = lm2_raycast_capsule_f64(cap64, {-1, -1, 0}, {1, 1, 0}, 0.25);
  ASSERT_TRUE(hit64.hit);
  EXPECT_NEAR(hit64.normal.x, 0.0, 1e-12);
  EXPECT_NEAR(hit64.normal.y, 1.0, 1e-12);

  const auto miss32 = lm2_ray3_make_f32({-1e30f, 1.5f, 0}, {1, 0, 0}, 2e30f);
  EXPECT_FALSE(lm2_raycast_capsule_f32(miss32, {-1, -1, 0}, {1, 1, 0}, 0.25f).hit);
  const auto cap32 = lm2_ray3_make_f32({-1e30f, 1.25f, 0}, {1, 0, 0}, 2e30f);
  const auto hit32 = lm2_raycast_capsule_f32(cap32, {-1, -1, 0}, {1, 1, 0}, 0.25f);
  ASSERT_TRUE(hit32.hit);
  EXPECT_NEAR(hit32.normal.x, 0.0f, 1e-5f);
  EXPECT_NEAR(hit32.normal.y, 1.0f, 1e-5f);
}

TEST(CapsuleRayExtremeTest, DistantCircleAndSphereRetainSurfaceNormals) {
  for (double y : {0.0, 0.25}) {
    const auto ray2 = lm2_ray2_make_f64({-1e200, y}, {1, 0}, 2e200);
    const auto hit2 = lm2_raycast_circle_f64(ray2, lm2_circle_make_coords_f64(0, 0, 0.5));
    ASSERT_TRUE(hit2.hit);
    EXPECT_NEAR(hit2.normal.x, y == 0 ? -1.0 : -std::sqrt(0.75), 1e-12);
    EXPECT_NEAR(hit2.normal.y, y * 2.0, 1e-12);
    const auto ray3 = lm2_ray3_make_f64({-1e200, y, 0}, {1, 0, 0}, 2e200);
    const auto hit3 = lm2_raycast_sphere_f64(ray3, {0, 0, 0}, 0.5);
    ASSERT_TRUE(hit3.hit);
    EXPECT_NEAR(hit3.normal.x, y == 0 ? -1.0 : -std::sqrt(0.75), 1e-12);
    EXPECT_NEAR(hit3.normal.y, y * 2.0, 1e-12);
  }
  for (float y : {0.0f, 0.25f}) {
    const auto ray2 = lm2_ray2_make_f32({-1e30f, y}, {1, 0}, 2e30f);
    const auto hit2 = lm2_raycast_circle_f32(ray2, lm2_circle_make_coords_f32(0, 0, 0.5f));
    ASSERT_TRUE(hit2.hit);
    EXPECT_NEAR(hit2.normal.x, y == 0 ? -1.0f : -std::sqrt(0.75f), 1e-5f);
    EXPECT_NEAR(hit2.normal.y, y * 2.0f, 1e-5f);
    const auto ray3 = lm2_ray3_make_f32({-1e30f, y, 0}, {1, 0, 0}, 2e30f);
    const auto hit3 = lm2_raycast_sphere_f32(ray3, {0, 0, 0}, 0.5f);
    ASSERT_TRUE(hit3.hit);
    EXPECT_NEAR(hit3.normal.x, y == 0 ? -1.0f : -std::sqrt(0.75f), 1e-5f);
    EXPECT_NEAR(hit3.normal.y, y * 2.0f, 1e-5f);
  }
}
