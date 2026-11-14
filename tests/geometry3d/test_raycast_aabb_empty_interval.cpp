#include <gtest/gtest.h>

#include "lm2/geometry2d/lm2_raycast2.h"
#include "lm2/geometry3d/lm2_raycast3.h"

TEST(RaycastAabbEmptyInterval, StationaryInsideWithNegativeMaximumIsMiss) {
  const auto b2d = lm2_r2_from_min_max_f64({-1, -1}, {1, 1});
  const auto b2f = lm2_r2_from_min_max_f32({-1, -1}, {1, 1});
  const auto b3d = lm2_r3_from_min_max_f64({-1, -1, -1}, {1, 1, 1});
  const auto b3f = lm2_r3_from_min_max_f32({-1, -1, -1}, {1, 1, 1});

  EXPECT_FALSE(lm2_raycast_aabb_f64(lm2_ray2_make_f64({0, 0}, {0, 0}, -1), b2d).hit);
  EXPECT_FALSE(lm2_raycast_aabb_f32(lm2_ray2_make_f32({0, 0}, {0, 0}, -1), b2f).hit);
  EXPECT_FALSE(lm2_raycast_aabb3_f64(lm2_ray3_make_f64({0, 0, 0}, {0, 0, 0}, -1), b3d).hit);
  EXPECT_FALSE(lm2_raycast_aabb3_f32(lm2_ray3_make_f32({0, 0, 0}, {0, 0, 0}, -1), b3f).hit);

  EXPECT_TRUE(lm2_raycast_aabb_f64(lm2_ray2_make_f64({0, 0}, {0, 0}, 0), b2d).hit);
  EXPECT_TRUE(lm2_raycast_aabb_f32(lm2_ray2_make_f32({0, 0}, {0, 0}, 0), b2f).hit);
  EXPECT_TRUE(lm2_raycast_aabb3_f64(lm2_ray3_make_f64({0, 0, 0}, {0, 0, 0}, 0), b3d).hit);
  EXPECT_TRUE(lm2_raycast_aabb3_f32(lm2_ray3_make_f32({0, 0, 0}, {0, 0, 0}, 0), b3f).hit);
}
