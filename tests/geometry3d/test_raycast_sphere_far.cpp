#include <cmath>
#include <gtest/gtest.h>

#include "lm2/geometry3d/lm2_raycast3.h"

TEST(SphereFarRay, DoubleNormalRetainsSurfaceDirection) {
  for (double y : {0.0, 0.25, 0.5}) {
    const lm2_ray3_f64 ray = lm2_ray3_make_f64({-1e200, y, 0.0}, {1.0, 0.0, 0.0}, 2e200);
    const auto hit = lm2_raycast_sphere_f64(ray, {0.0, 0.0, 0.0}, 0.5);
    ASSERT_TRUE(hit.hit);
    EXPECT_DOUBLE_EQ(hit.t, 1e200);
    EXPECT_NEAR(hit.normal.x, -std::sqrt(1.0 - 4.0 * y * y), 1e-14);
    EXPECT_NEAR(hit.normal.y, 2.0 * y, 1e-14);
    EXPECT_DOUBLE_EQ(hit.normal.z, 0.0);
    EXPECT_NEAR(hit.point.x, -0.5 * std::sqrt(1.0 - 4.0 * y * y), 1e-14);
    EXPECT_NEAR(hit.point.y, y, 1e-14);
    EXPECT_DOUBLE_EQ(hit.point.z, 0.0);
  }
}

TEST(SphereFarRay, FloatNormalRetainsSurfaceDirection) {
  for (float y : {0.0f, 0.25f, 0.5f}) {
    const lm2_ray3_f32 ray = lm2_ray3_make_f32({-1e30f, y, 0.0f}, {1.0f, 0.0f, 0.0f}, 2e30f);
    const auto hit = lm2_raycast_sphere_f32(ray, {0.0f, 0.0f, 0.0f}, 0.5f);
    ASSERT_TRUE(hit.hit);
    EXPECT_FLOAT_EQ(hit.t, 1e30f);
    EXPECT_NEAR(hit.normal.x, -std::sqrt(1.0f - 4.0f * y * y), 1e-6f);
    EXPECT_NEAR(hit.normal.y, 2.0f * y, 1e-6f);
    EXPECT_FLOAT_EQ(hit.normal.z, 0.0f);
    EXPECT_NEAR(hit.point.x, -0.5f * std::sqrt(1.0f - 4.0f * y * y), 1e-6f);
    EXPECT_NEAR(hit.point.y, y, 1e-6f);
    EXPECT_FLOAT_EQ(hit.point.z, 0.0f);
  }
}

TEST(SphereFarRay, ExitAndNonunitDirectionKeepOutwardNormals) {
  const auto inside = lm2_ray3_make_f64({0.0, 0.25, 0.0}, {2.0, 0.0, 0.0}, 1.0);
  const auto exit = lm2_raycast_sphere_f64(inside, {0.0, 0.0, 0.0}, 0.5);
  ASSERT_TRUE(exit.hit);
  EXPECT_NEAR(exit.t, std::sqrt(0.1875) / 2.0, 1e-14);
  EXPECT_NEAR(exit.normal.x, std::sqrt(0.75), 1e-14);
  EXPECT_NEAR(exit.normal.y, 0.5, 1e-14);

  const auto far = lm2_ray3_make_f64({0.25, -1e200, 0.0}, {0.0, 2.0, 0.0}, 1e200);
  const auto entry = lm2_raycast_sphere_f64(far, {0.0, 0.0, 0.0}, 0.5);
  ASSERT_TRUE(entry.hit);
  EXPECT_NEAR(entry.normal.x, 0.5, 1e-14);
  EXPECT_NEAR(entry.normal.y, -std::sqrt(0.75), 1e-14);
}
