#include <gtest/gtest.h>

#include "lm2/geometry2d/lm2_manifold2.h"

#define LM2_AABB_CONTACT_CASES(suffix)                                            \
  TEST(AABBManifoldContact, OverlapAndTouch_##suffix) {                           \
    const lm2_r2_##suffix a = lm2_r2_from_scalars_##suffix(0, 0, 10, 10);         \
    const lm2_r2_##suffix x_box = lm2_r2_from_scalars_##suffix(9, 8, 11, 9.5);    \
    const lm2_r2_##suffix y_box = lm2_r2_from_scalars_##suffix(8, 9, 9.5, 11);    \
    const lm2_r2_##suffix tangent = lm2_r2_from_scalars_##suffix(10, 8, 12, 9.5); \
    lm2_manifold_##suffix m = {};                                                 \
    lm2_manifold_aabb_to_aabb_##suffix(a, x_box, &m);                             \
    ASSERT_EQ(m.count, 1);                                                        \
    EXPECT_DOUBLE_EQ(m.depths[0], 1);                                             \
    EXPECT_DOUBLE_EQ(m.normal.x, 1);                                              \
    EXPECT_DOUBLE_EQ(m.normal.y, 0);                                              \
    EXPECT_DOUBLE_EQ(m.contact_points[0].x, 10);                                  \
    EXPECT_DOUBLE_EQ(m.contact_points[0].y, 8.75);                                \
    lm2_manifold_aabb_to_aabb_##suffix(x_box, a, &m);                             \
    ASSERT_EQ(m.count, 1);                                                        \
    EXPECT_DOUBLE_EQ(m.depths[0], 1);                                             \
    EXPECT_DOUBLE_EQ(m.normal.x, -1);                                             \
    EXPECT_DOUBLE_EQ(m.normal.y, 0);                                              \
    EXPECT_DOUBLE_EQ(m.contact_points[0].x, 9);                                   \
    EXPECT_DOUBLE_EQ(m.contact_points[0].y, 8.75);                                \
    lm2_manifold_aabb_to_aabb_##suffix(a, y_box, &m);                             \
    ASSERT_EQ(m.count, 1);                                                        \
    EXPECT_DOUBLE_EQ(m.depths[0], 1);                                             \
    EXPECT_DOUBLE_EQ(m.normal.x, 0);                                              \
    EXPECT_DOUBLE_EQ(m.normal.y, 1);                                              \
    EXPECT_DOUBLE_EQ(m.contact_points[0].x, 8.75);                                \
    EXPECT_DOUBLE_EQ(m.contact_points[0].y, 10);                                  \
    lm2_manifold_aabb_to_aabb_##suffix(y_box, a, &m);                             \
    ASSERT_EQ(m.count, 1);                                                        \
    EXPECT_DOUBLE_EQ(m.depths[0], 1);                                             \
    EXPECT_DOUBLE_EQ(m.normal.x, 0);                                              \
    EXPECT_DOUBLE_EQ(m.normal.y, -1);                                             \
    EXPECT_DOUBLE_EQ(m.contact_points[0].x, 8.75);                                \
    EXPECT_DOUBLE_EQ(m.contact_points[0].y, 9);                                   \
    lm2_manifold_aabb_to_aabb_##suffix(a, tangent, &m);                           \
    ASSERT_EQ(m.count, 1);                                                        \
    EXPECT_DOUBLE_EQ(m.depths[0], 0);                                             \
    EXPECT_DOUBLE_EQ(m.normal.x, 1);                                              \
    EXPECT_DOUBLE_EQ(m.normal.y, 0);                                              \
    EXPECT_DOUBLE_EQ(m.contact_points[0].x, 10);                                  \
    EXPECT_DOUBLE_EQ(m.contact_points[0].y, 8.75);                                \
  }

LM2_AABB_CONTACT_CASES(f64)
LM2_AABB_CONTACT_CASES(f32)

#undef LM2_AABB_CONTACT_CASES
