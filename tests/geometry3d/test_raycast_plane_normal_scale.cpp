#include <gtest/gtest.h>
#include <cmath>
#include <limits>

#include "lm2/geometry3d/lm2_raycast3.h"

TEST(RaycastPlaneNormalScale, DoubleNormalMagnitudeDoesNotChangeThePlane) {
  const lm2_ray3_f64 ray = lm2_ray3_make_f64({0, 5, 0}, {0, -1, 0}, 10);
  for (double scale : {1e-200, 1e-10, 1.0, 1e200}) {
    const auto hit = lm2_raycast_plane_f64(ray, {0, 0, 0}, {0, scale, 0});
    ASSERT_TRUE(hit.hit) << scale;
    EXPECT_DOUBLE_EQ(hit.t, 5.0);
    EXPECT_DOUBLE_EQ(hit.point.y, 0.0);
    EXPECT_DOUBLE_EQ(hit.normal.y, 1.0);
  }
  EXPECT_FALSE(lm2_raycast_plane_f64(ray, {0, 0, 0}, {0, 0, 0}).hit);
  const auto parallel = lm2_ray3_make_f64({0, 5, 0}, {1, 0, 0}, 10);
  EXPECT_FALSE(lm2_raycast_plane_f64(parallel, {0, 0, 0}, {0, 1e200, 0}).hit);
}

TEST(RaycastPlaneNormalScale, FloatNormalMagnitudeDoesNotChangeThePlane) {
  const lm2_ray3_f32 ray = lm2_ray3_make_f32({0, 5, 0}, {0, -1, 0}, 10);
  for (float scale : {1e-30f, 1e-7f, 1.0f, 1e30f}) {
    const auto hit = lm2_raycast_plane_f32(ray, {0, 0, 0}, {0, scale, 0});
    ASSERT_TRUE(hit.hit) << scale;
    EXPECT_FLOAT_EQ(hit.t, 5.0f);
    EXPECT_FLOAT_EQ(hit.point.y, 0.0f);
    EXPECT_FLOAT_EQ(hit.normal.y, 1.0f);
  }
  EXPECT_FALSE(lm2_raycast_plane_f32(ray, {0, 0, 0}, {0, 0, 0}).hit);
  const auto parallel = lm2_ray3_make_f32({0, 5, 0}, {1, 0, 0}, 10);
  EXPECT_FALSE(lm2_raycast_plane_f32(parallel, {0, 0, 0}, {0, 1e30f, 0}).hit);
}

TEST(RaycastPlaneNormalScale, FiniteExtremeNormalComponentsRemainUnitLength) {
  const auto ray64 = lm2_ray3_make_f64({0, 1, 0}, {0, -1, 0}, 2);
  for (double component : {std::numeric_limits<double>::max(), std::numeric_limits<double>::denorm_min()}) {
    const auto hit = lm2_raycast_plane_f64(ray64, {0, 0, 0}, {component, component, 0});
    ASSERT_TRUE(hit.hit) << component;
    EXPECT_DOUBLE_EQ(hit.t, 1.0);
    EXPECT_NEAR(hit.normal.x, std::sqrt(0.5), 1e-15);
    EXPECT_NEAR(hit.normal.y, std::sqrt(0.5), 1e-15);
  }
  const auto ray32 = lm2_ray3_make_f32({0, 1, 0}, {0, -1, 0}, 2);
  for (float component : {std::numeric_limits<float>::max(), std::numeric_limits<float>::denorm_min()}) {
    const auto hit = lm2_raycast_plane_f32(ray32, {0, 0, 0}, {component, component, 0});
    ASSERT_TRUE(hit.hit) << component;
    EXPECT_FLOAT_EQ(hit.t, 1.0f);
    EXPECT_NEAR(hit.normal.x, std::sqrt(0.5f), 1e-6f);
    EXPECT_NEAR(hit.normal.y, std::sqrt(0.5f), 1e-6f);
  }
}
