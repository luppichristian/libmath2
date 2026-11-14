#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>

#include "lm2/geometry2d/lm2_manifold2.h"

TEST(Manifold2PrecisionTest, CircleAABBPreservesSmallOverlapAtLargeCoordinates) {
  constexpr double x = 16777216.0;
  const lm2_r2_f64 box = lm2_r2_from_min_max_f64({x + 1.0, -1.0}, {x + 3.0, 1.0});
  const lm2_circle_f64 circle = lm2_circle_make_coords_f64(x + 0.75, 0.0, 0.5);
  lm2_manifold_f64 hit = {};
  lm2_manifold_circle_to_aabb_f64(circle, box, &hit);
  ASSERT_EQ(hit.count, 1);
  EXPECT_DOUBLE_EQ(hit.depths[0], 0.25);
  EXPECT_DOUBLE_EQ(hit.normal.x, 1.0);
  EXPECT_DOUBLE_EQ(hit.normal.y, 0.0);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].x, x + 1.0);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].y, 0.0);
}

TEST(Manifold2PrecisionTest, AABBAABBPreservesSmallOverlapAtLargeCoordinates) {
  constexpr double x = 16777216.0;
  const lm2_r2_f64 a = lm2_r2_from_min_max_f64({x, 0.0}, {x + 1.0, 1.0});
  const lm2_r2_f64 b = lm2_r2_from_min_max_f64({x + 0.75, 0.0}, {x + 2.0, 1.0});
  lm2_manifold_f64 hit = {};
  lm2_manifold_aabb_to_aabb_f64(a, b, &hit);
  ASSERT_EQ(hit.count, 1);
  EXPECT_DOUBLE_EQ(hit.depths[0], 0.25);
  EXPECT_DOUBLE_EQ(hit.normal.x, 1.0);
  EXPECT_DOUBLE_EQ(hit.normal.y, 0.0);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].x, x + 1.0);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].y, 0.5);
}

TEST(Manifold2PrecisionTest, CircleAABBBoundaryCornerAndInteriorConventions) {
  const lm2_r2_f64 box = lm2_r2_from_min_max_f64({-2.0, -2.0}, {2.0, 2.0});
  lm2_manifold_f64 hit = {};
  lm2_manifold_circle_to_aabb_f64(lm2_circle_make_coords_f64(3.0, 0.0, 1.0), box, &hit);
  EXPECT_EQ(hit.count, 0);  // This manifold excludes exact tangency.

  lm2_manifold_circle_to_aabb_f64(lm2_circle_make_coords_f64(2.3, 2.4, 1.0), box, &hit);
  ASSERT_EQ(hit.count, 1);
  EXPECT_NEAR(hit.depths[0], 0.5, 1e-14);
  EXPECT_NEAR(hit.normal.x, -0.6, 1e-14);
  EXPECT_NEAR(hit.normal.y, -0.8, 1e-14);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].x, 2.0);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].y, 2.0);

  lm2_manifold_circle_to_aabb_f64(lm2_circle_make_coords_f64(0.0, 0.0, 1.0), box, &hit);
  ASSERT_EQ(hit.count, 1);
  EXPECT_DOUBLE_EQ(hit.depths[0], 3.0);
  EXPECT_DOUBLE_EQ(hit.normal.x, 0.0);
  EXPECT_DOUBLE_EQ(hit.normal.y, -1.0);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].x, 0.0);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].y, 2.0);
}

TEST(Manifold2PrecisionTest, AABBAABBIncludesTangencyAndUsesSeparationDepthForContainment) {
  const auto a = lm2_r2_from_min_max_f64({0.0, 0.0}, {10.0, 10.0});
  auto b = lm2_r2_from_min_max_f64({10.0, 2.0}, {12.0, 4.0});
  lm2_manifold_f64 hit = {};
  lm2_manifold_aabb_to_aabb_f64(a, b, &hit);
  ASSERT_EQ(hit.count, 1);
  EXPECT_DOUBLE_EQ(hit.depths[0], 0.0);
  EXPECT_DOUBLE_EQ(hit.normal.x, 1.0);

  b = lm2_r2_from_min_max_f64({1.0, 3.0}, {2.0, 4.0});
  lm2_manifold_aabb_to_aabb_f64(a, b, &hit);
  ASSERT_EQ(hit.count, 1);
  EXPECT_DOUBLE_EQ(hit.depths[0], 2.0);
  EXPECT_DOUBLE_EQ(hit.normal.x, -1.0);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].x, 0.0);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].y, 3.5);

  b = lm2_r2_from_min_max_f64({10.5, 2.0}, {12.0, 4.0});
  lm2_manifold_aabb_to_aabb_f64(a, b, &hit);
  EXPECT_EQ(hit.count, 0);
}

TEST(Manifold2PrecisionTest, CircleCapsulePreservesPrecisionAndContactConventions) {
  constexpr double x = 16777216.0;
  const lm2_capsule2_f64 capsule = {
      {x + 1.0, -1.0},
      {x + 1.0,  1.0},
      0.25
  };
  lm2_manifold_f64 hit = {};
  lm2_manifold_circle_to_capsule_f64(lm2_circle_make_coords_f64(x + 0.5, 0.0, 0.5), capsule, &hit);
  ASSERT_EQ(hit.count, 1);
  EXPECT_DOUBLE_EQ(hit.depths[0], 0.25);
  EXPECT_DOUBLE_EQ(hit.normal.x, 1.0);
  EXPECT_DOUBLE_EQ(hit.normal.y, 0.0);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].x, x + 0.75);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].y, 0.0);

  lm2_manifold_circle_to_capsule_f64(lm2_circle_make_coords_f64(x + 0.25, 0.0, 0.5), capsule, &hit);
  EXPECT_EQ(hit.count, 0);

  lm2_manifold_circle_to_capsule_f64(lm2_circle_make_coords_f64(x + 1.0, 0.0, 0.5), capsule, &hit);
  ASSERT_EQ(hit.count, 1);
  EXPECT_DOUBLE_EQ(hit.depths[0], 0.75);
  EXPECT_DOUBLE_EQ(hit.normal.x, -1.0);
  EXPECT_DOUBLE_EQ(hit.normal.y, 0.0);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].x, x + 1.25);
}

TEST(Manifold2PrecisionTest, CircleCapsuleSupportsPointCapsulesAndEndcaps) {
  lm2_manifold_f64 hit = {};
  lm2_capsule2_f64 capsule = {
      {1.0, 0.0},
      {1.0, 0.0},
      0.25
  };
  lm2_manifold_circle_to_capsule_f64(lm2_circle_make_coords_f64(0.5, 0.0, 0.5), capsule, &hit);
  ASSERT_EQ(hit.count, 1);
  EXPECT_DOUBLE_EQ(hit.depths[0], 0.25);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].x, 0.75);

  lm2_manifold_circle_to_capsule_f64(lm2_circle_make_coords_f64(1.0, 0.0, 0.5), capsule, &hit);
  ASSERT_EQ(hit.count, 1);
  EXPECT_DOUBLE_EQ(hit.normal.x, 0.0);
  EXPECT_DOUBLE_EQ(hit.normal.y, 1.0);
  EXPECT_DOUBLE_EQ(hit.depths[0], 0.75);

  capsule = {
      {1.0, 0.0},
      {1.0, 2.0},
      0.25
  };
  lm2_manifold_circle_to_capsule_f64(lm2_circle_make_coords_f64(1.0, -0.5, 0.5), capsule, &hit);
  ASSERT_EQ(hit.count, 1);
  EXPECT_DOUBLE_EQ(hit.normal.y, 1.0);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].y, -0.25);
}

TEST(Manifold2PrecisionTest, CircleCapsuleMatchesFloatConventionsForRepresentativeCases) {
  struct Case {
    float x, y, circle_radius, capsule_radius;
  };
  const Case cases[] = {
      { -0.5f,  0.0f,   0.5f, 0.25f}, // Side overlap.
      {-0.75f,  0.0f,   0.5f, 0.25f}, // Strict tangency.
      {  0.0f,  0.0f,   0.5f, 0.25f}, // Center on segment.
      {  0.0f, -1.0f,   0.5f, 0.25f}, // Center at endpoint.
      {  0.0f, -1.5f,   0.5f, 0.25f}, // Endcap overlap.
      { 0.25f,  0.0f, 0.125f,  1.0f}, // Circle contained in capsule.
      { 0.25f,  0.0f,   2.0f, 0.25f}, // Capsule locally contained in circle.
      {  0.0f,  0.0f,   2.0f, 0.25f}, // Centered containment.
      {  0.0f,  0.0f,   0.0f, 0.25f}, // Zero-radius circle.
      {-0.25f,  0.0f,   0.5f,  0.0f}, // Zero-radius capsule.
      {  0.0f,  0.0f,   0.0f,  0.0f}, // Both radii zero.
  };
  for (const auto& c : cases) {
    SCOPED_TRACE(::testing::Message() << c.x << ", " << c.y << ", " << c.circle_radius << ", " << c.capsule_radius);
    const lm2_capsule2_f32 cap32 = {
        {0.0f, -1.0f},
        {0.0f,  1.0f},
        c.capsule_radius
    };
    const lm2_capsule2_f64 cap64 = {
        {0.0, -1.0},
        {0.0,  1.0},
        c.capsule_radius
    };
    lm2_manifold_f32 m32 = {};
    lm2_manifold_f64 m64 = {};
    lm2_manifold_circle_to_capsule_f32(lm2_circle_make_coords_f32(c.x, c.y, c.circle_radius), cap32, &m32);
    lm2_manifold_circle_to_capsule_f64(lm2_circle_make_coords_f64(c.x, c.y, c.circle_radius), cap64, &m64);
    ASSERT_EQ(m64.count, m32.count);
    if (m64.count) {
      EXPECT_NEAR(m64.depths[0], m32.depths[0], 1e-6);
      EXPECT_NEAR(m64.normal.x, m32.normal.x, 1e-6);
      EXPECT_NEAR(m64.normal.y, m32.normal.y, 1e-6);
      EXPECT_NEAR(m64.contact_points[0].x, m32.contact_points[0].x, 1e-6);
      EXPECT_NEAR(m64.contact_points[0].y, m32.contact_points[0].y, 1e-6);
    }
  }
}

TEST(Manifold2PrecisionTest, CirclePolygonAndTrianglePreserveSmallOverlapAtLargeCoordinates) {
  constexpr double x = 16777216.0;
  lm2_v2_f64 vertices[] = {
      {x + 1.0, -1.0},
      {x + 3.0, -1.0},
      {x + 3.0,  1.0},
      {x + 1.0,  1.0}
  };
  const lm2_polygon_f64 poly = {vertices, 4};
  const lm2_circle_f64 circle = lm2_circle_make_coords_f64(x + 0.75, 0.0, 0.5);
  lm2_manifold_f64 hit = {};
  lm2_manifold_circle_to_polygon_f64(circle, poly, &hit);
  ASSERT_EQ(hit.count, 1);
  EXPECT_DOUBLE_EQ(hit.depths[0], 0.25);
  EXPECT_DOUBLE_EQ(hit.normal.x, 1.0);
  EXPECT_DOUBLE_EQ(hit.normal.y, 0.0);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].x, x + 1.0);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].y, 0.0);

  const lm2_triangle2_f64 tri = {
      {x + 1.0, -1.0},
      {x + 3.0, -1.0},
      {x + 1.0,  1.0}
  };
  lm2_manifold_triangle_to_circle_f64(tri, circle, &hit);
  ASSERT_EQ(hit.count, 1);
  EXPECT_DOUBLE_EQ(hit.depths[0], 0.25);
  EXPECT_DOUBLE_EQ(hit.normal.x, -1.0);
  EXPECT_DOUBLE_EQ(hit.normal.y, 0.0);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].x, x + 1.0);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].y, 0.0);
}

TEST(Manifold2PrecisionTest, CirclePolygonMatchesFloatConventions) {
  lm2_v2_f32 v32[] = {
      {-2.0f, -2.0f},
      { 2.0f, -2.0f},
      { 2.0f,  2.0f},
      {-2.0f,  2.0f}
  };
  lm2_v2_f64 v64[] = {
      {-2.0, -2.0},
      { 2.0, -2.0},
      { 2.0,  2.0},
      {-2.0,  2.0}
  };
  const lm2_polygon_f32 p32 = {v32, 4};
  const lm2_polygon_f64 p64 = {v64, 4};
  struct Case {
    float x, y, radius;
  };
  const Case cases[] = {
      { 2.5f, 0.0f, 1.0f},
      { 2.6f, 2.8f, 2.0f},
      { 3.0f, 0.0f, 1.0f},
      { 4.0f, 0.0f, 1.0f},
      { 0.0f, 0.0f, 0.5f},
      {1.75f, 0.0f, 0.5f},
      { 2.0f, 0.0f, 0.5f},
      { 0.0f, 0.0f, 0.0f},
  };
  for (const auto& c : cases) {
    SCOPED_TRACE(::testing::Message() << c.x << ", " << c.y << ", " << c.radius);
    lm2_manifold_f32 m32 = {};
    lm2_manifold_f64 m64 = {};
    lm2_manifold_circle_to_polygon_f32(lm2_circle_make_coords_f32(c.x, c.y, c.radius), p32, &m32);
    lm2_manifold_circle_to_polygon_f64(lm2_circle_make_coords_f64(c.x, c.y, c.radius), p64, &m64);
    ASSERT_EQ(m64.count, m32.count);
    if (m64.count) {
      EXPECT_NEAR(m64.depths[0], m32.depths[0], 1e-5);
      EXPECT_NEAR(m64.normal.x, m32.normal.x, 1e-5);
      EXPECT_NEAR(m64.normal.y, m32.normal.y, 1e-5);
      EXPECT_NEAR(m64.contact_points[0].x, m32.contact_points[0].x, 1e-5);
      EXPECT_NEAR(m64.contact_points[0].y, m32.contact_points[0].y, 1e-5);
    }
  }
}

TEST(Manifold2PrecisionTest, CapsulePolygonTranslatedOverlapAndWrappers) {
  constexpr double x = 16777216.0;
  lm2_v2_f64 vertices[] = {
      {x + 1.0, -1.0},
      {x + 3.0, -1.0},
      {x + 3.0,  1.0},
      {x + 1.0,  1.0}
  };
  const lm2_polygon_f64 poly = {vertices, 4};
  const lm2_capsule2_f64 capsule = {
      {x + 0.5, -0.5},
      {x + 0.5,  0.5},
      0.75
  };
  lm2_manifold_f64 hit = {};
  lm2_manifold_capsule_to_polygon_f64(capsule, poly, &hit);
  ASSERT_EQ(hit.count, 1);
  EXPECT_DOUBLE_EQ(hit.depths[0], 0.25);
  EXPECT_DOUBLE_EQ(hit.normal.x, 1.0);
  EXPECT_DOUBLE_EQ(hit.normal.y, 0.0);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].x, x + 1.25);

  const lm2_r2_f64 box = lm2_r2_from_min_max_f64({x + 1.0, -1.0}, {x + 3.0, 1.0});
  lm2_manifold_f64 reverse = {};
  lm2_manifold_aabb_to_capsule_f64(box, capsule, &reverse);
  ASSERT_EQ(reverse.count, hit.count);
  EXPECT_DOUBLE_EQ(reverse.depths[0], hit.depths[0]);
  EXPECT_DOUBLE_EQ(reverse.normal.x, -hit.normal.x);
  EXPECT_DOUBLE_EQ(reverse.normal.y, -hit.normal.y);
  EXPECT_DOUBLE_EQ(reverse.contact_points[0].x, hit.contact_points[0].x);

  const lm2_triangle2_f64 tri = {
      {x + 1.0, -1.0},
      {x + 3.0, -1.0},
      {x + 1.0,  1.0}
  };
  lm2_manifold_triangle_to_capsule_f64(tri, capsule, &reverse);
  ASSERT_EQ(reverse.count, 1);
  EXPECT_DOUBLE_EQ(reverse.depths[0], 0.25);
  EXPECT_DOUBLE_EQ(reverse.normal.x, -1.0);
}

TEST(Manifold2PrecisionTest, CapsulePolygonMatchesFloatForShallowAndDeepContacts) {
  lm2_v2_f32 v32[] = {
      {-2.0f, -2.0f},
      { 2.0f, -2.0f},
      { 2.0f,  2.0f},
      {-2.0f,  2.0f}
  };
  lm2_v2_f64 v64[] = {
      {-2.0, -2.0},
      { 2.0, -2.0},
      { 2.0,  2.0},
      {-2.0,  2.0}
  };
  const lm2_polygon_f32 p32 = {v32, 4};
  const lm2_polygon_f64 p64 = {v64, 4};
  struct Case {
    float ax, ay, bx, by, radius;
  };
  const Case cases[] = {
      {2.5f,   -1, 2.5f, 1,    1},
      {2.5f, 2.5f,    3, 3,    1},
      {   3,   -1,    3, 1,    1},
      {  -1,    0,    1, 0, 0.5f},
      {  -3,    0,    3, 0, 0.5f},
      {  -1,   -3,   -1, 3, 0.5f},
      {  -3,   -3,    3, 3, 0.5f},
      {  -1,    0,    1, 0,    0},
      {   4,    0,    5, 0, 0.5f},
  };
  for (const auto& c : cases) {
    SCOPED_TRACE(::testing::Message() << c.ax << ", " << c.ay << ", " << c.bx << ", " << c.by << ", " << c.radius);
    const lm2_capsule2_f32 c32 = {
        {c.ax, c.ay},
        {c.bx, c.by},
        c.radius
    };
    const lm2_capsule2_f64 c64 = {
        {c.ax, c.ay},
        {c.bx, c.by},
        c.radius
    };
    lm2_manifold_f32 m32 = {};
    lm2_manifold_f64 m64 = {};
    lm2_manifold_capsule_to_polygon_f32(c32, p32, &m32);
    lm2_manifold_capsule_to_polygon_f64(c64, p64, &m64);
    ASSERT_EQ(m64.count, m32.count);
    if (m64.count) {
      EXPECT_NEAR(m64.normal.x, m32.normal.x, 1e-5);
      EXPECT_NEAR(m64.normal.y, m32.normal.y, 1e-5);
      for (int i = 0; i < m64.count; ++i) {
        EXPECT_NEAR(m64.depths[i], m32.depths[i], 1e-5);
        EXPECT_NEAR(m64.contact_points[i].x, m32.contact_points[i].x, 1e-5);
        if (c.ax == 2.5f && c.ay == -1.0f && c.bx == 2.5f && c.by == 1.0f) {
          // Parallel segments have a continuum of equally valid witness pairs.
          EXPECT_GE(m64.contact_points[i].y, -1.0);
          EXPECT_LE(m64.contact_points[i].y, 1.0);
        } else {
          EXPECT_NEAR(m64.contact_points[i].y, m32.contact_points[i].y, 1e-5);
        }
      }
    }
  }
}

TEST(Manifold2PrecisionTest, PointCapsulePolygonMatchesCircle) {
  lm2_v2_f64 vertices[] = {
      {-2.0, -2.0},
      { 2.0, -2.0},
      { 2.0,  2.0},
      {-2.0,  2.0}
  };
  const lm2_polygon_f64 polygon = {vertices, 4};
  for (const lm2_v2_f64 center : {
           lm2_v2_f64 {0.5, 0},
           lm2_v2_f64 {2.5, 0},
           lm2_v2_f64 {  3, 0}
  }) {
    const lm2_capsule2_f64 capsule = {center, center, 1.0};
    const lm2_circle_f64 circle = lm2_circle_make_coords_f64(center.x, center.y, 1.0);
    lm2_manifold_f64 cap = {}, circ = {};
    lm2_manifold_capsule_to_polygon_f64(capsule, polygon, &cap);
    lm2_manifold_circle_to_polygon_f64(circle, polygon, &circ);
    ASSERT_EQ(cap.count, circ.count);
    if (cap.count) {
      EXPECT_DOUBLE_EQ(cap.normal.x, circ.normal.x);
      EXPECT_DOUBLE_EQ(cap.normal.y, circ.normal.y);
      EXPECT_DOUBLE_EQ(cap.depths[0], circ.depths[0]);
      EXPECT_DOUBLE_EQ(cap.contact_points[0].x, circ.contact_points[0].x);
      EXPECT_DOUBLE_EQ(cap.contact_points[0].y, circ.contact_points[0].y);
    }
  }
}

TEST(Manifold2PrecisionTest, CapsulePolygonAgreesWithFloatAwayFromTangency) {
  lm2_v2_f32 vertices32[] = {
      {-2, -2},
      { 2, -2},
      { 2,  2},
      {-2,  2}
  };
  lm2_v2_f64 vertices64[] = {
      {-2, -2},
      { 2, -2},
      { 2,  2},
      {-2,  2}
  };
  const lm2_polygon_f32 polygon32 = {vertices32, 4};
  const lm2_polygon_f64 polygon64 = {vertices64, 4};
  uint32_t state = 0x739a1f57u;
  auto random_coordinate = [&state]() {
    state = state * 1664525u + 1013904223u;
    return static_cast<float>(static_cast<int>(state % 801u) - 400) / 40.0f;
  };
  for (int sample = 0; sample < 5000; ++sample) {
    const lm2_v2_f32 start = {random_coordinate(), random_coordinate()};
    const lm2_v2_f32 end = {random_coordinate(), random_coordinate()};
    const float radius = 0.5f + static_cast<float>(state % 121u) / 40.0f;
    const lm2_capsule2_f32 capsule32 = {start, end, radius};
    const lm2_capsule2_f64 capsule64 = {
        {start.x, start.y},
        {  end.x,   end.y},
        radius
    };
    lm2_manifold_f32 manifold32 = {};
    lm2_manifold_f64 manifold64 = {};
    lm2_manifold_capsule_to_polygon_f32(capsule32, polygon32, &manifold32);
    lm2_manifold_capsule_to_polygon_f64(capsule64, polygon64, &manifold64);
    // At tangency, the two precision levels can round to opposite sides.
    if ((manifold32.count && manifold32.depths[0] < 1e-4f) ||
        (manifold64.count && manifold64.depths[0] < 1e-4)) continue;
    ASSERT_EQ(manifold64.count > 0, manifold32.count > 0) << "sample " << sample;
    ASSERT_GE(manifold64.count, 0);
    ASSERT_LE(manifold64.count, 2);
    if (manifold64.count) {
      EXPECT_NEAR(std::hypot(manifold64.normal.x, manifold64.normal.y), 1.0, 1e-12);
      for (int i = 0; i < manifold64.count; ++i) EXPECT_GE(manifold64.depths[i], 0.0);
    }
  }
}
