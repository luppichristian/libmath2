#include <cmath>
#include <cstdint>
#include <gtest/gtest.h>
#include "lm2/geometry3d/lm2_raycast3.h"

TEST(CapsuleRayFarComparison, DistantRayMatchesNearbyRayForTiltedAxes) {
  uint32_t seed = 0x4a392d17u;
  auto value = [&]() {
    seed = seed * 1664525u + 1013904223u;
    return (static_cast<int>((seed >> 8) % 4001u) - 2000) / 1000.0;
  };
  for (int i = 0; i < 10000; ++i) {
    const lm2_v3_f64 start = {value(), value(), value()};
    const lm2_v3_f64 end = {value(), value(), value()};
    const double radius = 0.1 + std::fabs(value());
    const double y = value(), z = value();
    const auto near_ray = lm2_ray3_make_f64({-10, y, z}, {1, 0, 0}, 20);
    const auto far_ray = lm2_ray3_make_f64({-1e200, y, z}, {1, 0, 0}, 2e200);
    const auto near_hit = lm2_raycast_capsule_f64(near_ray, start, end, radius);
    const auto far_hit = lm2_raycast_capsule_f64(far_ray, start, end, radius);
    ASSERT_EQ(far_hit.hit, near_hit.hit) << "sample " << i;
    if (near_hit.hit) {
      EXPECT_NEAR(far_hit.normal.x, near_hit.normal.x, 1e-9) << "sample " << i;
      EXPECT_NEAR(far_hit.normal.y, near_hit.normal.y, 1e-9) << "sample " << i;
      EXPECT_NEAR(far_hit.normal.z, near_hit.normal.z, 1e-9) << "sample " << i;
      EXPECT_NEAR(far_hit.point.x, near_hit.point.x, 1e-9) << "sample " << i;
      EXPECT_NEAR(far_hit.point.y, near_hit.point.y, 1e-9) << "sample " << i;
      EXPECT_NEAR(far_hit.point.z, near_hit.point.z, 1e-9) << "sample " << i;
    }
  }
}

TEST(CapsuleRayFarComparison, DistantFloatRayMatchesNearbyRayForTiltedAxes) {
  uint32_t seed = 0xb77a01a3u;
  auto value = [&]() {
    seed = seed * 1664525u + 1013904223u;
    return (static_cast<int>((seed >> 8) % 4001u) - 2000) / 1000.0f;
  };
  for (int i = 0; i < 10000; ++i) {
    const lm2_v3_f32 start = {value(), value(), value()};
    const lm2_v3_f32 end = {value(), value(), value()};
    const float radius = 0.1f + std::fabs(value());
    const float y = value(), z = value();
    const auto near_ray = lm2_ray3_make_f32({-10, y, z}, {1, 0, 0}, 20);
    const auto far_ray = lm2_ray3_make_f32({-1e30f, y, z}, {1, 0, 0}, 2e30f);
    const auto near_hit = lm2_raycast_capsule_f32(near_ray, start, end, radius);
    const auto far_hit = lm2_raycast_capsule_f32(far_ray, start, end, radius);
    ASSERT_EQ(far_hit.hit, near_hit.hit) << "sample " << i;
    if (near_hit.hit) {
      EXPECT_NEAR(far_hit.normal.x, near_hit.normal.x, 5e-4f) << "sample " << i;
      EXPECT_NEAR(far_hit.normal.y, near_hit.normal.y, 5e-4f) << "sample " << i;
      EXPECT_NEAR(far_hit.normal.z, near_hit.normal.z, 5e-4f) << "sample " << i;
      EXPECT_NEAR(far_hit.point.x, near_hit.point.x, 5e-4f) << "sample " << i;
      EXPECT_NEAR(far_hit.point.y, near_hit.point.y, 5e-4f) << "sample " << i;
      EXPECT_NEAR(far_hit.point.z, near_hit.point.z, 5e-4f) << "sample " << i;
    }
  }
}

TEST(CapsuleRayFarComparison, DiagonalDistantRayRetainsShapeOffsets) {
  uint32_t seed = 0xc3a60179u;
  auto value = [&]() {
    seed = seed * 1664525u + 1013904223u;
    return (static_cast<int>((seed >> 8) % 4001u) - 2000) / 1000.0;
  };
  for (int i = 0; i < 10000; ++i) {
    const lm2_v3_f64 start = {value(), value(), value()};
    const lm2_v3_f64 end = {value(), value(), value()};
    const double radius = 0.1 + std::fabs(value());
    const double z = value();
    const auto near_ray = lm2_ray3_make_f64({-10, -10, z}, {1, 1, 0}, 20);
    const auto far_ray = lm2_ray3_make_f64({-1e200, -1e200, z}, {1, 1, 0}, 2e200);
    const auto near_hit = lm2_raycast_capsule_f64(near_ray, start, end, radius);
    const auto far_hit = lm2_raycast_capsule_f64(far_ray, start, end, radius);
    ASSERT_EQ(far_hit.hit, near_hit.hit) << "sample " << i;
    if (near_hit.hit) {
      EXPECT_NEAR(far_hit.normal.x, near_hit.normal.x, 1e-9) << "sample " << i;
      EXPECT_NEAR(far_hit.normal.y, near_hit.normal.y, 1e-9) << "sample " << i;
      EXPECT_NEAR(far_hit.normal.z, near_hit.normal.z, 1e-9) << "sample " << i;
      EXPECT_NEAR(far_hit.point.x, near_hit.point.x, 1e-9) << "sample " << i;
      EXPECT_NEAR(far_hit.point.y, near_hit.point.y, 1e-9) << "sample " << i;
      EXPECT_NEAR(far_hit.point.z, near_hit.point.z, 1e-9) << "sample " << i;
    }
  }
}

TEST(CapsuleRayFarComparison, DiagonalDistantFloatRayRetainsShapeOffsets) {
  uint32_t seed = 0x58216f91u;
  auto value = [&]() {
    seed = seed * 1664525u + 1013904223u;
    return (static_cast<int>((seed >> 8) % 4001u) - 2000) / 1000.0f;
  };
  for (int i = 0; i < 10000; ++i) {
    const lm2_v3_f32 start = {value(), value(), value()};
    const lm2_v3_f32 end = {value(), value(), value()};
    const float radius = 0.1f + std::fabs(value());
    const float z = value();
    const auto near_ray = lm2_ray3_make_f32({-10, -10, z}, {1, 1, 0}, 20);
    const auto far_ray = lm2_ray3_make_f32({-1e30f, -1e30f, z}, {1, 1, 0}, 2e30f);
    const auto near_hit = lm2_raycast_capsule_f32(near_ray, start, end, radius);
    const auto far_hit = lm2_raycast_capsule_f32(far_ray, start, end, radius);
    ASSERT_EQ(far_hit.hit, near_hit.hit) << "sample " << i;
    if (near_hit.hit) {
      EXPECT_NEAR(far_hit.normal.x, near_hit.normal.x, 5e-4f) << "sample " << i;
      EXPECT_NEAR(far_hit.normal.y, near_hit.normal.y, 5e-4f) << "sample " << i;
      EXPECT_NEAR(far_hit.normal.z, near_hit.normal.z, 5e-4f) << "sample " << i;
      EXPECT_NEAR(far_hit.point.x, near_hit.point.x, 5e-4f) << "sample " << i;
      EXPECT_NEAR(far_hit.point.y, near_hit.point.y, 5e-4f) << "sample " << i;
      EXPECT_NEAR(far_hit.point.z, near_hit.point.z, 5e-4f) << "sample " << i;
    }
  }
}

TEST(CapsuleRayFarComparison, DistantSkewRayRetainsShapeOffsets) {
  uint32_t seed = 0xe0bca012u;
  auto value = [&]() {
    seed = seed * 1664525u + 1013904223u;
    return (static_cast<int>((seed >> 8) % 4001u) - 2000) / 1000.0;
  };
  for (int i = 0; i < 10000; ++i) {
    const lm2_v3_f64 start = {value(), value(), value()};
    const lm2_v3_f64 end = {value(), value(), value()};
    const double radius = 0.1 + std::fabs(value());
    const double z = value();
    const auto near_ray = lm2_ray3_make_f64({-20, -10, z}, {2, 1, 0}, 20);
    const auto far_ray = lm2_ray3_make_f64({-2e200, -1e200, z}, {2, 1, 0}, 2e200);
    const auto near_hit = lm2_raycast_capsule_f64(near_ray, start, end, radius);
    const auto far_hit = lm2_raycast_capsule_f64(far_ray, start, end, radius);
    ASSERT_EQ(far_hit.hit, near_hit.hit) << "sample " << i;
    if (near_hit.hit) {
      EXPECT_NEAR(far_hit.normal.x, near_hit.normal.x, 1e-9) << "sample " << i;
      EXPECT_NEAR(far_hit.normal.y, near_hit.normal.y, 1e-9) << "sample " << i;
      EXPECT_NEAR(far_hit.normal.z, near_hit.normal.z, 1e-9) << "sample " << i;
      EXPECT_NEAR(far_hit.point.x, near_hit.point.x, 1e-9) << "sample " << i;
      EXPECT_NEAR(far_hit.point.y, near_hit.point.y, 1e-9) << "sample " << i;
      EXPECT_NEAR(far_hit.point.z, near_hit.point.z, 1e-9) << "sample " << i;
    }
  }
}
