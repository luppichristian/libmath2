#include <gtest/gtest.h>
#include <limits>

#include "lm2/geometry2d/lm2_manifold2.h"

TEST(CircleManifoldScale, SmallF64CirclesAndAabb) {
  constexpr double scale = 1e-200;
  const lm2_circle_f64 a = {
      {0.0, 0.0},
      scale
  };
  lm2_circle_f64 b = {
      {scale, 0.0},
      scale
  };
  lm2_manifold_f64 manifold = {};
  EXPECT_TRUE(lm2_collide_circle_to_circle_f64(a, b));
  lm2_manifold_circle_to_circle_f64(a, b, &manifold);
  ASSERT_EQ(manifold.count, 1);
  EXPECT_DOUBLE_EQ(manifold.depths[0], scale);
  EXPECT_DOUBLE_EQ(manifold.normal.x, 1.0);
  EXPECT_DOUBLE_EQ(manifold.normal.y, 0.0);

  b.center.x = 3.0 * scale;
  EXPECT_FALSE(lm2_collide_circle_to_circle_f64(a, b));
  const lm2_r2_f64 box = lm2_r2_from_min_max_f64({scale * 0.5, -scale}, {scale * 2.0, scale});
  EXPECT_TRUE(lm2_collide_circle_to_aabb_f64(a, box));
}

TEST(CircleManifoldScale, LargeF64CirclesAndAabb) {
  constexpr double scale = 1e200;
  const lm2_circle_f64 a = {
      {0.0, 0.0},
      scale
  };
  lm2_circle_f64 b = {
      {scale, 0.0},
      scale
  };
  lm2_manifold_f64 manifold = {};
  EXPECT_TRUE(lm2_collide_circle_to_circle_f64(a, b));
  lm2_manifold_circle_to_circle_f64(a, b, &manifold);
  ASSERT_EQ(manifold.count, 1);
  EXPECT_DOUBLE_EQ(manifold.depths[0], scale);
  EXPECT_DOUBLE_EQ(manifold.normal.x, 1.0);
  EXPECT_DOUBLE_EQ(manifold.contact_points[0].x, 0.0);
  b.center.x = 2.0 * scale;
  EXPECT_TRUE(lm2_collide_circle_to_circle_f64(a, b));
  lm2_manifold_circle_to_circle_f64(a, b, &manifold);
  EXPECT_EQ(manifold.count, 0);
  b.center.x = 3.0 * scale;
  EXPECT_FALSE(lm2_collide_circle_to_circle_f64(a, b));
  const auto box = lm2_r2_from_min_max_f64({scale * 0.5, -scale}, {scale * 2.0, scale});
  EXPECT_TRUE(lm2_collide_circle_to_aabb_f64(a, box));
  const auto tangent = lm2_r2_from_min_max_f64({scale, -scale}, {scale * 2.0, scale});
  EXPECT_FALSE(lm2_collide_circle_to_aabb_f64(a, tangent));
}

TEST(CircleManifoldScale, SubnormalF64DisplacementKeepsItsDirection) {
  const double scale = std::numeric_limits<double>::denorm_min();
  const lm2_circle_f64 a = {
      {0.0, 0.0},
      2.0 * scale
  };
  const lm2_circle_f64 b = {
      {scale, 0.0},
      2.0 * scale
  };
  lm2_manifold_f64 manifold = {};
  ASSERT_TRUE(lm2_collide_circle_to_circle_f64(a, b));
  lm2_manifold_circle_to_circle_f64(a, b, &manifold);
  ASSERT_EQ(manifold.count, 1);
  EXPECT_DOUBLE_EQ(manifold.depths[0], 3.0 * scale);
  EXPECT_DOUBLE_EQ(manifold.normal.x, 1.0);
  EXPECT_DOUBLE_EQ(manifold.normal.y, 0.0);
}

TEST(CircleManifoldScale, SmallF32CirclesAndAabb) {
  constexpr float scale = 1e-30f;
  const lm2_circle_f32 a = {
      {0.0f, 0.0f},
      scale
  };
  lm2_circle_f32 b = {
      {scale, 0.0f},
      scale
  };
  lm2_manifold_f32 manifold = {};
  EXPECT_TRUE(lm2_collide_circle_to_circle_f32(a, b));
  lm2_manifold_circle_to_circle_f32(a, b, &manifold);
  ASSERT_EQ(manifold.count, 1);
  EXPECT_FLOAT_EQ(manifold.depths[0], scale);
  EXPECT_FLOAT_EQ(manifold.normal.x, 1.0f);
  b.center.x = 3.0f * scale;
  EXPECT_FALSE(lm2_collide_circle_to_circle_f32(a, b));
  const auto box = lm2_r2_from_min_max_f32({scale * 0.5f, -scale}, {scale * 2.0f, scale});
  EXPECT_TRUE(lm2_collide_circle_to_aabb_f32(a, box));
  lm2_manifold_circle_to_aabb_f32(a, box, &manifold);
  ASSERT_EQ(manifold.count, 1);
  EXPECT_FLOAT_EQ(manifold.depths[0], scale * 0.5f);
}

TEST(CircleManifoldScale, LargeF32CirclesAndAabb) {
  constexpr float scale = 1e30f;
  const lm2_circle_f32 a = {
      {0.0f, 0.0f},
      scale
  };
  lm2_circle_f32 b = {
      {scale, 0.0f},
      scale
  };
  lm2_manifold_f32 manifold = {};
  EXPECT_TRUE(lm2_collide_circle_to_circle_f32(a, b));
  lm2_manifold_circle_to_circle_f32(a, b, &manifold);
  ASSERT_EQ(manifold.count, 1);
  EXPECT_FLOAT_EQ(manifold.depths[0], scale);
  EXPECT_FLOAT_EQ(manifold.normal.x, 1.0f);
  b.center.x = 2.0f * scale;
  EXPECT_TRUE(lm2_collide_circle_to_circle_f32(a, b));
  lm2_manifold_circle_to_circle_f32(a, b, &manifold);
  EXPECT_EQ(manifold.count, 0);
  b.center.x = 3.0f * scale;
  EXPECT_FALSE(lm2_collide_circle_to_circle_f32(a, b));
  const auto box = lm2_r2_from_min_max_f32({scale * 0.5f, -scale}, {scale * 2.0f, scale});
  EXPECT_TRUE(lm2_collide_circle_to_aabb_f32(a, box));
  lm2_manifold_circle_to_aabb_f32(a, box, &manifold);
  ASSERT_EQ(manifold.count, 1);
  EXPECT_FLOAT_EQ(manifold.depths[0], scale * 0.5f);
  const auto tangent = lm2_r2_from_min_max_f32({scale, -scale}, {scale * 2.0f, scale});
  EXPECT_FALSE(lm2_collide_circle_to_aabb_f32(a, tangent));
}
