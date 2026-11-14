#include <gtest/gtest.h>
#include "lm2/geometry2d/lm2_manifold2.h"

TEST(ManifoldBooleanF64, TranslatedShapesPreserveOverlapAndGaps) {
  constexpr double x = 16777216.0;
  lm2_v2_f64 a_vertices[] = {
      {    x, 0},
      {x + 1, 0},
      {x + 1, 1},
      {    x, 1}
  };
  lm2_v2_f64 b_vertices[] = {
      {x + 1.25, 0},
      {x + 2.25, 0},
      {x + 2.25, 1},
      {x + 1.25, 1}
  };
  lm2_polygon_f64 a = {a_vertices, 4}, b = {b_vertices, 4};
  const auto box = lm2_r2_from_min_max_f64({x, 0}, {x + 1, 1});
  auto circle = lm2_circle_make_coords_f64(x + 1.5, 0.5, 0.25);
  auto cap = lm2_capsule2_make_coords_f64(x + 1.5, 0, x + 1.5, 1, 0.25);
  auto cap_a = lm2_capsule2_make_coords_f64(x, 0, x, 1, 0.25);
  auto cap_b = lm2_capsule2_make_coords_f64(x + 0.75, 0, x + 0.75, 1, 0.25);
  EXPECT_FALSE(lm2_collide_polygon_to_polygon_f64(a, b));
  EXPECT_FALSE(lm2_collide_aabb_to_polygon_f64(box, b));
  EXPECT_FALSE(lm2_collide_circle_to_polygon_f64(circle, a));
  EXPECT_FALSE(lm2_collide_capsule_to_polygon_f64(cap, a));
  EXPECT_FALSE(lm2_collide_aabb_to_capsule_f64(box, cap));
  EXPECT_FALSE(lm2_collide_capsule_to_capsule_f64(cap_a, cap_b));
  for (auto& vertex : b_vertices) vertex.x -= 0.5;
  circle.center.x -= 0.5;
  cap.start.x -= 0.5;
  cap.end.x -= 0.5;
  cap_b.start.x -= 0.5;
  cap_b.end.x -= 0.5;
  EXPECT_TRUE(lm2_collide_polygon_to_polygon_f64(a, b));
  EXPECT_TRUE(lm2_collide_aabb_to_polygon_f64(box, b));
  EXPECT_TRUE(lm2_collide_circle_to_polygon_f64(circle, a));
  EXPECT_TRUE(lm2_collide_capsule_to_polygon_f64(cap, a));
  EXPECT_TRUE(lm2_collide_aabb_to_capsule_f64(box, cap));
  EXPECT_TRUE(lm2_collide_capsule_to_capsule_f64(cap_a, cap_b));
}

TEST(ManifoldBooleanF64, ClosedContactAndDegenerateCapsules) {
  lm2_v2_f64 vertices[] = {
      {0, 0},
      {2, 0},
      {2, 2},
      {0, 2}
  };
  lm2_polygon_f64 polygon = {vertices, 4};
  auto circle = lm2_circle_make_coords_f64(3, 1, 1);
  auto capsule = lm2_capsule2_make_coords_f64(3, 1, 3, 1, 1);
  auto other = lm2_capsule2_make_coords_f64(5, 1, 5, 1, 1);
  const auto box = lm2_r2_from_min_max_f64({0, 0}, {2, 2});
  EXPECT_TRUE(lm2_collide_circle_to_polygon_f64(circle, polygon));
  EXPECT_TRUE(lm2_collide_capsule_to_polygon_f64(capsule, polygon));
  EXPECT_TRUE(lm2_collide_aabb_to_capsule_f64(box, capsule));
  EXPECT_TRUE(lm2_collide_capsule_to_capsule_f64(capsule, other));
  circle.center = {3, 3};
  EXPECT_FALSE(lm2_collide_circle_to_polygon_f64(circle, polygon));
}

TEST(ManifoldBooleanF64, TriangleWrappersMatchEquivalentPolygons) {
  constexpr double x = 16777216.0;
  lm2_triangle2_f64 tri = {
      {    x, 0},
      {x + 2, 0},
      {    x, 2}
  };
  lm2_triangle2_f64 other = {
      {x + 3, 0},
      {x + 4, 0},
      {x + 3, 1}
  };
  lm2_polygon_f64 polygon = {other, 3};
  auto circle = lm2_circle_make_coords_f64(x + 3, 0, 0.25);
  auto capsule = lm2_capsule2_make_coords_f64(x + 3, 0, x + 3, 1, 0.25);
  auto box = lm2_r2_from_min_max_f64({x + 3, 0}, {x + 4, 1});
  EXPECT_FALSE(lm2_collide_triangle_to_triangle_f64(tri, other));
  EXPECT_FALSE(lm2_collide_triangle_to_circle_f64(tri, circle));
  EXPECT_FALSE(lm2_collide_triangle_to_aabb_f64(tri, box));
  EXPECT_FALSE(lm2_collide_triangle_to_capsule_f64(tri, capsule));
  EXPECT_FALSE(lm2_collide_triangle_to_polygon_f64(tri, polygon));
}

TEST(ManifoldBooleanF64, DegenerateTriangleAndBoxAreFiniteGeometry) {
  lm2_triangle2_f64 point = {
      {1, 1},
      {1, 1},
      {1, 1}
  };
  lm2_triangle2_f64 line = {
      {0, 0},
      {2, 0},
      {1, 0}
  };
  lm2_triangle2_f64 separate_line = {
      {3, 0},
      {4, 0},
      {5, 0}
  };
  auto far_circle = lm2_circle_make_coords_f64(10, 10, 0.5);
  auto far_capsule = lm2_capsule2_make_coords_f64(10, 10, 11, 10, 0.5);
  auto point_box = lm2_r2_from_min_max_f64({1, 0}, {1, 0});
  auto far_point_box = lm2_r2_from_min_max_f64({3, 0}, {3, 0});
  EXPECT_FALSE(lm2_collide_triangle_to_circle_f64(point, far_circle));
  EXPECT_FALSE(lm2_collide_triangle_to_capsule_f64(point, far_capsule));
  EXPECT_FALSE(lm2_collide_triangle_to_triangle_f64(line, separate_line));
  EXPECT_TRUE(lm2_collide_triangle_to_aabb_f64(line, point_box));
  EXPECT_FALSE(lm2_collide_triangle_to_aabb_f64(line, far_point_box));
}

TEST(ManifoldBooleanF64, CrossingSegmentsAndPolygonEdgesTouch) {
  auto horizontal = lm2_capsule2_make_coords_f64(-2, 0, 2, 0, 0);
  auto vertical = lm2_capsule2_make_coords_f64(0, -2, 0, 2, 0);
  auto box = lm2_r2_from_min_max_f64({-1, -1}, {1, 1});
  lm2_v2_f64 vertices[] = {
      {-1, -1},
      { 1, -1},
      { 1,  1},
      {-1,  1}
  };
  lm2_v2_f64 touching[] = {
      {1, -1},
      {3, -1},
      {3,  1},
      {1,  1}
  };
  lm2_polygon_f64 polygon = {vertices, 4}, other = {touching, 4};
  EXPECT_TRUE(lm2_collide_capsule_to_capsule_f64(horizontal, vertical));
  EXPECT_TRUE(lm2_collide_capsule_to_polygon_f64(horizontal, polygon));
  EXPECT_TRUE(lm2_collide_aabb_to_capsule_f64(box, horizontal));
  EXPECT_TRUE(lm2_collide_polygon_to_polygon_f64(polygon, other));
  EXPECT_TRUE(lm2_collide_aabb_to_polygon_f64(box, other));
}

TEST(ManifoldBooleanF64, ConvexPolygonsAtSmallAndLargeScales) {
  for (double scale : {1e-200, 1e200}) {
    lm2_v2_f64 square[] = {
        {    0,     0},
        {scale,     0},
        {scale, scale},
        {    0, scale}
    };
    lm2_v2_f64 outside[] = {
        {2 * scale,     0},
        {3 * scale,     0},
        {3 * scale, scale},
        {2 * scale, scale}
    };
    lm2_v2_f64 touching[] = {
        {    scale,     0},
        {2 * scale,     0},
        {2 * scale, scale},
        {    scale, scale}
    };
    lm2_polygon_f64 a = {square, 4}, b = {outside, 4}, c = {touching, 4};
    auto near_circle = lm2_circle_make_coords_f64(scale * 1.25, scale * 0.5, scale * 0.5);
    auto far_circle = lm2_circle_make_coords_f64(scale * 2, scale * 0.5, scale * 0.5);
    EXPECT_FALSE(lm2_collide_polygon_to_polygon_f64(a, b));
    EXPECT_TRUE(lm2_collide_polygon_to_polygon_f64(a, c));
    EXPECT_TRUE(lm2_collide_circle_to_polygon_f64(near_circle, a));
    EXPECT_FALSE(lm2_collide_circle_to_polygon_f64(far_circle, a));
  }
}
