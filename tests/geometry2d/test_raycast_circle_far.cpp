#include <cmath>
#include <gtest/gtest.h>

#include "lm2/geometry2d/lm2_raycast2.h"

TEST(RaycastCircleFar, F64NormalsRemainUnitAtExtremeDistances) {
  const auto circle = lm2_circle_make_coords_f64(0.0, 0.0, 0.5);
  for (double y : {0.0, 0.25, -0.25, 0.5, -0.5}) {
    const auto ray = lm2_ray2_make_f64({-1e200, y}, {1.0, 0.0}, 2e200);
    const auto hit = lm2_raycast_circle_f64(ray, circle);
    ASSERT_TRUE(hit.hit) << y;
    EXPECT_DOUBLE_EQ(hit.t, 1e200);
    EXPECT_NEAR(hit.normal.x, -std::sqrt(1.0 - 4.0 * y * y), 1e-14);
    EXPECT_NEAR(hit.normal.y, 2.0 * y, 1e-14);
    EXPECT_NEAR(std::hypot(hit.normal.x, hit.normal.y), 1.0, 1e-14);
    EXPECT_NEAR(hit.point.x, -0.5 * std::sqrt(1.0 - 4.0 * y * y), 1e-14);
    EXPECT_NEAR(hit.point.y, y, 1e-14);
  }
  const auto reverse = lm2_ray2_make_f64({1e200, 0.25}, {-2.0, 0.0}, 1e200);
  const auto hit = lm2_raycast_circle_f64(reverse, circle);
  ASSERT_TRUE(hit.hit);
  EXPECT_NEAR(hit.normal.x, std::sqrt(0.75), 1e-14);
  EXPECT_NEAR(hit.normal.y, 0.5, 1e-14);
  const auto translated = lm2_circle_make_coords_f64(1e9, 0.25, 0.5);
  const auto translated_hit = lm2_raycast_circle_f64(lm2_ray2_make_f64({-1e200, 0.5}, {1.0, 0.0}, 2e200), translated);
  ASSERT_TRUE(translated_hit.hit);
  EXPECT_NEAR(translated_hit.point.x, 1e9 - 0.5 * std::sqrt(0.75), 2e-7);
  EXPECT_DOUBLE_EQ(translated_hit.point.y, 0.5);
  const auto point_hit = lm2_raycast_circle_f64(lm2_ray2_make_f64({-1e200, 0.0}, {1.0, 0.0}, 2e200),
                                                lm2_circle_make_coords_f64(0.0, 0.0, 0.0));
  ASSERT_TRUE(point_hit.hit);
  EXPECT_DOUBLE_EQ(point_hit.normal.x, 0.0);
  EXPECT_DOUBLE_EQ(point_hit.normal.y, 0.0);
  EXPECT_DOUBLE_EQ(point_hit.point.x, 0.0);
}

TEST(RaycastCircleFar, F32NormalsRemainUnitAtExtremeDistances) {
  const auto circle = lm2_circle_make_coords_f32(0.0f, 0.0f, 0.5f);
  for (float y : {0.0f, 0.25f, -0.25f, 0.5f, -0.5f}) {
    const auto ray = lm2_ray2_make_f32({-1e30f, y}, {1.0f, 0.0f}, 2e30f);
    const auto hit = lm2_raycast_circle_f32(ray, circle);
    ASSERT_TRUE(hit.hit) << y;
    EXPECT_FLOAT_EQ(hit.t, 1e30f);
    EXPECT_NEAR(hit.normal.x, -std::sqrt(1.0f - 4.0f * y * y), 1e-6f);
    EXPECT_NEAR(hit.normal.y, 2.0f * y, 1e-6f);
    EXPECT_NEAR(std::hypot(hit.normal.x, hit.normal.y), 1.0f, 1e-6f);
    EXPECT_NEAR(hit.point.x, -0.5f * std::sqrt(1.0f - 4.0f * y * y), 1e-6f);
    EXPECT_NEAR(hit.point.y, y, 1e-6f);
  }
  const auto reverse = lm2_ray2_make_f32({1e30f, 0.25f}, {-2.0f, 0.0f}, 1e30f);
  const auto hit = lm2_raycast_circle_f32(reverse, circle);
  ASSERT_TRUE(hit.hit);
  EXPECT_NEAR(hit.normal.x, std::sqrt(0.75f), 1e-6f);
  EXPECT_NEAR(hit.normal.y, 0.5f, 1e-6f);
  const auto translated = lm2_circle_make_coords_f32(4096.0f, 0.25f, 0.5f);
  const auto translated_hit = lm2_raycast_circle_f32(lm2_ray2_make_f32({-1e30f, 0.5f}, {1.0f, 0.0f}, 2e30f), translated);
  ASSERT_TRUE(translated_hit.hit);
  EXPECT_NEAR(translated_hit.point.x, 4096.0f - 0.5f * std::sqrt(0.75f), 5e-4f);
  EXPECT_FLOAT_EQ(translated_hit.point.y, 0.5f);
  const auto point_hit = lm2_raycast_circle_f32(lm2_ray2_make_f32({-1e30f, 0.0f}, {1.0f, 0.0f}, 2e30f),
                                                lm2_circle_make_coords_f32(0.0f, 0.0f, 0.0f));
  ASSERT_TRUE(point_hit.hit);
  EXPECT_FLOAT_EQ(point_hit.normal.x, 0.0f);
  EXPECT_FLOAT_EQ(point_hit.normal.y, 0.0f);
  EXPECT_FLOAT_EQ(point_hit.point.x, 0.0f);
}

TEST(RaycastCircleFar, ObliqueRaysUseOrientedLocalChord) {
  const auto c64 = lm2_circle_make_coords_f64(0, 0, 0.5);
  const auto r64 = lm2_ray2_make_f64({-60000000.0 + 0.2, -80000000.0 - 0.15}, {0.6, 0.8}, 2e8);
  const auto h64 = lm2_raycast_circle_f64(r64, c64);
  ASSERT_TRUE(h64.hit);
  const double chord64 = std::sqrt(0.25 - 0.25 * 0.25);
  EXPECT_NEAR(h64.point.x, 0.8 * 0.25 - 0.6 * chord64, 1e-7);
  EXPECT_NEAR(h64.point.y, -0.6 * 0.25 - 0.8 * chord64, 1e-7);
  EXPECT_NEAR(std::hypot(h64.normal.x, h64.normal.y), 1.0, 1e-12);

  const auto c32 = lm2_circle_make_coords_f32(0, 0, 0.5f);
  const auto r32 = lm2_ray2_make_f32({-6000.0f + 0.2f, -8000.0f - 0.15f}, {0.6f, 0.8f}, 2e4f);
  const auto h32 = lm2_raycast_circle_f32(r32, c32);
  ASSERT_TRUE(h32.hit);
  const float chord32 = std::sqrt(0.25f - 0.25f * 0.25f);
  EXPECT_NEAR(h32.point.x, 0.8f * 0.25f - 0.6f * chord32, 1e-3f);
  EXPECT_NEAR(h32.point.y, -0.6f * 0.25f - 0.8f * chord32, 1e-3f);
  EXPECT_NEAR(std::hypot(h32.normal.x, h32.normal.y), 1.0f, 1e-5f);
}
