#include <gtest/gtest.h>

#include "lm2/geometry2d/lm2_capsule2.h"
#include "lm2/geometry2d/lm2_edge2.h"
#include "lm2/geometry2d/lm2_raycast2.h"

// Edge raycasting uses the same geometry as a zero-radius capsule. Check both
// the equivalence and concrete hit, miss, interval, and origin-on-edge cases.
#define LM2_CHECK_EDGE_RAYCAST(suffix, scalar)                                         \
  TEST(EdgeRaycastTest, MatchesZeroRadiusCapsule_##suffix) {                           \
    lm2_edge2_##suffix edge = lm2_edge2_make_coords_##suffix(5, -2, 5, 2);             \
    lm2_capsule2_##suffix capsule = lm2_capsule2_make_coords_##suffix(5, -2, 5, 2, 0); \
    struct ray_case {                                                                  \
      scalar x, y, t_max;                                                              \
      bool hit;                                                                        \
      scalar t, normal_x, normal_y;                                                    \
    };                                                                                 \
    const ray_case cases[] = {                                                         \
        {0, 0,  5,  true, 5, -1, 0}, /* Hit at the end of the ray. */                   \
        {0, 0,  4, false, 0,  0, 0}, /* Same segment beyond the ray. */                 \
        {0, 3, 10, false, 0,  0, 0}, /* Miss above the segment. */                      \
        {5, 0, 10,  true, 0,  0, 1}, /* Ray starts on the segment. */                   \
    };                                                                                 \
    for (const auto& c : cases) {                                                      \
      auto ray = lm2_ray2_make_##suffix(lm2_v2_make_##suffix(c.x, c.y),                \
                                        lm2_v2_make_##suffix(1, 0),                    \
                                        c.t_max);                                      \
      auto from_edge = lm2_raycast_edge2_##suffix(ray, edge);                          \
      auto from_capsule = lm2_raycast_capsule2_##suffix(ray, capsule);                 \
      EXPECT_EQ(from_edge.hit, c.hit);                                                 \
      EXPECT_EQ(from_capsule.hit, c.hit);                                              \
      if (c.hit) {                                                                     \
        EXPECT_EQ(from_edge.t, c.t);                                                   \
        EXPECT_EQ(from_edge.normal.x, c.normal_x);                                     \
        EXPECT_EQ(from_edge.normal.y, c.normal_y);                                     \
        EXPECT_EQ(from_edge.t, from_capsule.t);                                        \
        EXPECT_EQ(from_edge.point.x, from_capsule.point.x);                            \
        EXPECT_EQ(from_edge.point.y, from_capsule.point.y);                            \
        EXPECT_EQ(from_edge.normal.x, from_capsule.normal.x);                          \
        EXPECT_EQ(from_edge.normal.y, from_capsule.normal.y);                          \
      }                                                                                \
    }                                                                                  \
  }

LM2_CHECK_EDGE_RAYCAST(f32, float)
LM2_CHECK_EDGE_RAYCAST(f64, double)

#undef LM2_CHECK_EDGE_RAYCAST
