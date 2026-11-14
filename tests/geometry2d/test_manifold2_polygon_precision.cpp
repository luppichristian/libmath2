#include <gtest/gtest.h>
#include <cmath>
#include "lm2/geometry2d/lm2_manifold2.h"

TEST(PolygonManifoldF64, TranslatedOverlapPreservesDepthAndContactCoordinates) {
  const double x = 16777216.0;
  lm2_v2_f64 av[] = {
      {    x, 0},
      {x + 4, 0},
      {x + 4, 4},
      {    x, 4}
  };
  lm2_v2_f64 bv[] = {
      {x + 3.5, 1},
      {  x + 5, 1},
      {  x + 5, 3},
      {x + 3.5, 3}
  };
  lm2_polygon_f64 a = {av, 4}, b = {bv, 4};
  lm2_manifold_f64 m;
  lm2_manifold_polygon_to_polygon_f64(a, b, &m);
  ASSERT_EQ(m.count, 2);
  EXPECT_NEAR(m.normal.x, 1, 1e-12);
  EXPECT_NEAR(m.normal.y, 0, 1e-12);
  EXPECT_NEAR(m.depths[0], 0.5, 1e-12);
  EXPECT_NEAR(m.depths[1], 0.5, 1e-12);
  EXPECT_GE(m.contact_points[0].x, x + 3.5);
  EXPECT_LE(m.contact_points[0].x, x + 4);
  EXPECT_GE(m.contact_points[1].x, x + 3.5);
  EXPECT_LE(m.contact_points[1].x, x + 4);
  auto box = lm2_r2_from_min_max_f64({x, 0}, {x + 4, 4});
  lm2_manifold_aabb_to_polygon_f64(box, b, &m);
  ASSERT_EQ(m.count, 2);
  EXPECT_NEAR(m.normal.x, 1, 1e-12);
  EXPECT_NEAR(m.depths[0], 0.5, 1e-12);
}

TEST(PolygonManifoldF64, ExactTangencyAndSeparationHaveNoContacts) {
  lm2_v2_f64 av[] = {
      {0, 0},
      {2, 0},
      {2, 2},
      {0, 2}
  };
  lm2_v2_f64 bv[] = {
      {2, 0},
      {4, 0},
      {4, 2},
      {2, 2}
  };
  lm2_polygon_f64 a = {av, 4}, b = {bv, 4};
  lm2_manifold_f64 m;
  lm2_manifold_polygon_to_polygon_f64(a, b, &m);
  EXPECT_EQ(m.count, 0);
  for (auto& v : bv) v.x += 0.25;
  lm2_manifold_polygon_to_polygon_f64(a, b, &m);
  EXPECT_EQ(m.count, 0);
}

TEST(PolygonManifoldF64, TriangleWrappersFollowPolygonContactConvention) {
  const double x = 16777216.0;
  lm2_triangle2_f64 tri = {
      {    x, 0},
      {x + 4, 0},
      {    x, 4}
  };
  lm2_triangle2_f64 other = {
      {x + 3.5, 0},
      {  x + 5, 0},
      {x + 3.5, 1}
  };
  lm2_polygon_f64 polygon = {other, 3};
  lm2_manifold_f64 a, b;
  lm2_manifold_triangle_to_triangle_f64(tri, other, &a);
  lm2_manifold_triangle_to_polygon_f64(tri, polygon, &b);
  ASSERT_GT(a.count, 0);
  EXPECT_EQ(a.count, b.count);
  EXPECT_NEAR(a.normal.x, b.normal.x, 1e-12);
  EXPECT_NEAR(a.normal.y, b.normal.y, 1e-12);
  auto box = lm2_r2_from_min_max_f64({x + 3.5, 0}, {x + 5, 1});
  lm2_manifold_triangle_to_aabb_f64(tri, box, &a);
  ASSERT_GT(a.count, 0);
  EXPECT_GT(a.normal.x, 0);
}

TEST(PolygonManifoldF64, ScalesContainmentAndReversedOrder) {
  for (double scale : {1e-200, 1.0, 1e200}) {
    lm2_v2_f64 av[] = {
        {        0,         0},
        {4 * scale,         0},
        {4 * scale, 4 * scale},
        {        0, 4 * scale}
    };
    lm2_v2_f64 bv[] = {
        {3 * scale,     scale},
        {5 * scale,     scale},
        {5 * scale, 3 * scale},
        {3 * scale, 3 * scale}
    };
    lm2_polygon_f64 a = {av, 4}, b = {bv, 4};
    lm2_manifold_f64 forward, reverse;
    lm2_manifold_polygon_to_polygon_f64(a, b, &forward);
    lm2_manifold_polygon_to_polygon_f64(b, a, &reverse);
    ASSERT_GT(forward.count, 0) << scale;
    ASSERT_GT(reverse.count, 0) << scale;
    EXPECT_NEAR(forward.normal.x, 1, 1e-12);
    EXPECT_NEAR(reverse.normal.x, -1, 1e-12);
    EXPECT_NEAR(forward.depths[0] / scale, 1, 1e-12);
    EXPECT_NEAR(reverse.depths[0] / scale, 1, 1e-12);
    for (auto& v : bv) v.x -= 2 * scale;
    lm2_manifold_polygon_to_polygon_f64(a, b, &forward);
    EXPECT_GT(forward.count, 0);
    EXPECT_GT(forward.depths[0], 0);
  }
}

TEST(PolygonManifoldF64, RotatedOverlapProducesContactsAtDifferentScales) {
  for (const double scale : {1e-6, 1.0, 1e6}) {
    lm2_v2_f64 av[] = {
        {-scale, -scale},
        { scale, -scale},
        { scale,  scale},
        {-scale,  scale}
    };
    lm2_v2_f64 bv[] = {
        { 1.1638144266231854 * scale,  -1.1830598025868905 * scale},
        { 2.7480052163794128 * scale, -0.42366150021089703 * scale},
        { 2.3173855733768142 * scale,  0.47465980258689061 * scale},
        {0.73319478362058711 * scale, -0.28473849978910288 * scale}
    };
    lm2_polygon_f64 a = {av, 4}, b = {bv, 4};
    lm2_manifold_f64 forward, reverse;
    ASSERT_TRUE(lm2_collide_polygon_to_polygon_f64(a, b)) << scale;
    lm2_manifold_polygon_to_polygon_f64(a, b, &forward);
    lm2_manifold_polygon_to_polygon_f64(b, a, &reverse);
    ASSERT_GT(forward.count, 0) << scale;
    ASSERT_GT(reverse.count, 0) << scale;
    EXPECT_NEAR(forward.normal.x, 1.0, 1e-12);
    EXPECT_NEAR(forward.normal.y, 0.0, 1e-12);
    EXPECT_NEAR(reverse.normal.x, -1.0, 1e-12);
    EXPECT_NEAR(reverse.normal.y, 0.0, 1e-12);
    for (const auto& manifold : {forward, reverse}) {
      bool positive_depth = false;
      for (int i = 0; i < manifold.count; ++i) {
        EXPECT_TRUE(std::isfinite(manifold.depths[i]));
        EXPECT_GE(manifold.depths[i], 0.0);
        positive_depth |= manifold.depths[i] > 0.0;
        EXPECT_TRUE(std::isfinite(manifold.contact_points[i].x));
        EXPECT_TRUE(std::isfinite(manifold.contact_points[i].y));
        EXPECT_LE(std::fabs(manifold.contact_points[i].x), scale * (1.0 + 1e-12));
        EXPECT_LE(std::fabs(manifold.contact_points[i].y), scale * (1.0 + 1e-12));
      }
      EXPECT_TRUE(positive_depth);
    }
  }
}
