/*
MIT License

Copyright (c) 2026 Christian Luppi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <gtest/gtest.h>
#include <cmath>
#include <vector>
#include "lm2/geometry2d/lm2_manifold2.h"

template <typename Manifold>
static void expect_empty_manifold(const Manifold& manifold) {
  EXPECT_EQ(manifold.count, 0);
  EXPECT_EQ(manifold.normal.x, 0);
  EXPECT_EQ(manifold.normal.y, 0);
  for (int i = 0; i < 2; ++i) {
    EXPECT_EQ(manifold.depths[i], 0);
    EXPECT_EQ(manifold.contact_points[i].x, 0);
    EXPECT_EQ(manifold.contact_points[i].y, 0);
  }
}

#define LM2_TEST_TRIANGLE_MANIFOLD_NORMALS(suffix, scalar)                                      \
  TEST(ManifoldTriangleNormals, TriangleFirst_##suffix) {                                       \
    lm2_triangle2_##suffix tri = {                                                              \
        {0, 0},                                                                                 \
        {4, 0},                                                                                 \
        {0, 4} \
    };                                                                                \
    lm2_circle_##suffix circle = lm2_circle_make_coords_##suffix(-0.5, 1, 1);                   \
    lm2_capsule2_##suffix capsule = lm2_capsule2_make_coords_##suffix(-0.5, 0.5, -0.5, 1.5, 1); \
    lm2_r2_##suffix box = lm2_r2_from_min_max_##suffix({-1, 0.5}, {0.5, 1.5});                  \
    lm2_manifold_##suffix manifold = {};                                                        \
    lm2_manifold_triangle_to_circle_##suffix(tri, circle, &manifold);                           \
    ASSERT_GT(manifold.count, 0);                                                               \
    EXPECT_NEAR(manifold.normal.x, -1, 1e-5);                                                   \
    EXPECT_NEAR(manifold.normal.y, 0, 1e-5);                                                    \
    lm2_manifold_triangle_to_capsule_##suffix(tri, capsule, &manifold);                         \
    ASSERT_GT(manifold.count, 0);                                                               \
    EXPECT_NEAR(manifold.normal.x, -1, 1e-5);                                                   \
    EXPECT_NEAR(manifold.normal.y, 0, 1e-5);                                                    \
    lm2_manifold_triangle_to_aabb_##suffix(tri, box, &manifold);                                \
    ASSERT_GT(manifold.count, 0);                                                               \
    EXPECT_NEAR(manifold.normal.x, -1, 1e-5);                                                   \
    EXPECT_NEAR(manifold.normal.y, 0, 1e-5);                                                    \
  }

LM2_TEST_TRIANGLE_MANIFOLD_NORMALS(f32, float)
LM2_TEST_TRIANGLE_MANIFOLD_NORMALS(f64, double)

#undef LM2_TEST_TRIANGLE_MANIFOLD_NORMALS

#define LM2_TEST_SHAPE_PAIR_MANIFOLDS(suffix)                                            \
  TEST(ManifoldShapePairs, OverlapAndSeparation_##suffix) {                              \
    lm2_circle_##suffix circles[] = {                                                    \
        {{-0.75, 0}, 1},                                                                 \
        { {0.75, 0}, 1},                                                                  \
        {   {20, 0}, 1} \
    };                                                                   \
    lm2_capsule2_##suffix capsules[] = {                                                 \
        {{-0.75, -0.5}, {-0.75, 0.5}, 1},                                                \
        { {0.75, -0.5},  {0.75, 0.5}, 1},                                                  \
        {   {20, -0.5},    {20, 0.5}, 1} \
    };                                                     \
    lm2_r2_##suffix boxes[] = {                                                          \
        lm2_r2_from_min_max_##suffix({-1.75, -1}, {0.25, 1}),                            \
        lm2_r2_from_min_max_##suffix({-0.25, -1}, {1.75, 1}),                            \
        lm2_r2_from_min_max_##suffix({19, -1}, {21, 1})};                                \
    lm2_triangle2_##suffix triangles[] = {                                               \
        {{-1.75, -1}, {0.25, -1}, {-0.75, 1}},                                           \
        {{-0.25, -1}, {1.75, -1},  {0.75, 1}},                                            \
        {   {19, -1},   {21, -1},    {20, 1}} \
    };                                                  \
    lm2_v2_##suffix points[][4] = {                                                      \
        {{-1.75, -1}, {0.25, -1}, {0.25, 1}, {-1.75, 1}},                                \
        {{-0.25, -1}, {1.75, -1}, {1.75, 1}, {-0.25, 1}},                                \
        {   {19, -1},   {21, -1},   {21, 1},    {19, 1}} \
    };                                         \
    lm2_polygon_##suffix polys[] = {                                                     \
        {points[0], 4},                                                                  \
        {points[1], 4},                                                                  \
        {points[2], 4} \
    };                                                                 \
    lm2_shape2_##suffix shapes[3][5];                                                    \
    for (int i = 0; i < 3; ++i) {                                                        \
      shapes[i][0] = lm2_shape2_from_circle_##suffix(&circles[i]);                       \
      shapes[i][1] = lm2_shape2_from_capsule_##suffix(&capsules[i]);                     \
      shapes[i][2] = lm2_shape2_from_aabb2_##suffix(&boxes[i]);                          \
      shapes[i][3] = lm2_shape2_from_triangle_##suffix(&triangles[i]);                   \
      shapes[i][4] = lm2_shape2_from_polygon_##suffix(&polys[i]);                        \
    }                                                                                    \
    for (int a = 0; a < 5; ++a) {                                                        \
      for (int b = 0; b < 5; ++b) {                                                      \
        SCOPED_TRACE(::testing::Message() << "shape types " << a << ", " << b);          \
        lm2_manifold_##suffix hit = {};                                                  \
        hit.depths[1] = 99;                                                              \
        hit.contact_points[1] = {99, 99};                                                \
        lm2_manifold_shape_to_shape_##suffix(shapes[0][a], shapes[1][b], &hit);          \
        ASSERT_GE(hit.count, 1);                                                         \
        ASSERT_LE(hit.count, 2);                                                         \
        EXPECT_NEAR(hit.normal.x * hit.normal.x + hit.normal.y * hit.normal.y, 1, 1e-5); \
        EXPECT_GT(hit.normal.x, 0);                                                      \
        for (int i = 0; i < hit.count; ++i) {                                            \
          EXPECT_GT(hit.depths[i], 0);                                                   \
          EXPECT_TRUE(std::isfinite(hit.contact_points[i].x));                           \
          EXPECT_TRUE(std::isfinite(hit.contact_points[i].y));                           \
        }                                                                                \
        if (hit.count == 1) {                                                            \
          EXPECT_EQ(hit.depths[1], 0);                                                   \
          EXPECT_EQ(hit.contact_points[1].x, 0);                                         \
          EXPECT_EQ(hit.contact_points[1].y, 0);                                         \
        }                                                                                \
        lm2_manifold_##suffix miss = {};                                                 \
        miss.count = 2;                                                                  \
        miss.normal = {99, 99};                                                          \
        miss.depths[0] = 99;                                                             \
        miss.depths[1] = 99;                                                             \
        miss.contact_points[0] = {99, 99};                                               \
        miss.contact_points[1] = {99, 99};                                               \
        lm2_manifold_shape_to_shape_##suffix(shapes[0][a], shapes[2][b], &miss);         \
        expect_empty_manifold(miss);                                                     \
      }                                                                                  \
    }                                                                                    \
    lm2_shape2_##suffix unsupported = {LM2_SHAPE2_EDGE, &circles[0]};                    \
    lm2_manifold_##suffix empty = {};                                                    \
    empty.normal = {99, 99};                                                             \
    empty.depths[0] = 99;                                                                \
    empty.contact_points[0] = {99, 99};                                                  \
    lm2_manifold_shape_to_shape_##suffix(unsupported, shapes[0][0], &empty);             \
    expect_empty_manifold(empty);                                                        \
    empty.normal = {99, 99};                                                             \
    empty.depths[0] = 99;                                                                \
    lm2_manifold_shape_to_shape_##suffix(shapes[0][0], unsupported, &empty);             \
    expect_empty_manifold(empty);                                                        \
  }

LM2_TEST_SHAPE_PAIR_MANIFOLDS(f32)
LM2_TEST_SHAPE_PAIR_MANIFOLDS(f64)

#undef LM2_TEST_SHAPE_PAIR_MANIFOLDS

#define LM2_TEST_PLANE_MANIFOLDS(suffix)                                    \
  TEST(ManifoldPlane, PenetrationAndSeparation_##suffix) {                  \
    lm2_plane2_##suffix plane = {                                           \
        {0, 1},                                                             \
        0 \
    };                                                                 \
    lm2_circle_##suffix circle = {                                          \
        {0, 0.5},                                                           \
        1 \
    };                                                                 \
    lm2_manifold_##suffix hit = {};                                         \
    hit.depths[1] = 99;                                                     \
    hit.contact_points[1] = {99, 99};                                       \
    lm2_manifold_circle_to_plane_##suffix(circle, plane, &hit);             \
    ASSERT_EQ(hit.count, 1);                                                \
    EXPECT_EQ(hit.depths[1], 0);                                            \
    EXPECT_EQ(hit.contact_points[1].x, 0);                                  \
    EXPECT_EQ(hit.contact_points[1].y, 0);                                  \
    EXPECT_NEAR(hit.depths[0], 0.5, 1e-5);                                  \
    EXPECT_NEAR(hit.contact_points[0].y, 0, 1e-5);                          \
    EXPECT_NEAR(hit.normal.y, 1, 1e-5);                                     \
    circle.center.y = 1;                                                    \
    lm2_manifold_circle_to_plane_##suffix(circle, plane, &hit);             \
    expect_empty_manifold(hit);                                             \
    circle.center.y = 2;                                                    \
    lm2_manifold_circle_to_plane_##suffix(circle, plane, &hit);             \
    expect_empty_manifold(hit);                                             \
    lm2_capsule2_##suffix capsule = {                                       \
        {-1, 0.5},                                                          \
        { 1, 0.5},                                                           \
        1 \
    };                                                                 \
    lm2_manifold_capsule_to_plane_##suffix(capsule, plane, &hit);           \
    ASSERT_EQ(hit.count, 2);                                                \
    EXPECT_NEAR(hit.depths[0], 0.5, 1e-5);                                  \
    EXPECT_NEAR(hit.depths[1], 0.5, 1e-5);                                  \
    EXPECT_NEAR(hit.contact_points[0].y, 0, 1e-5);                          \
    EXPECT_NEAR(hit.contact_points[1].y, 0, 1e-5);                          \
    capsule.start.y = 2;                                                    \
    capsule.end.y = 2;                                                      \
    lm2_manifold_capsule_to_plane_##suffix(capsule, plane, &hit);           \
    expect_empty_manifold(hit);                                             \
    lm2_r2_##suffix box = lm2_r2_from_min_max_##suffix({-1, -0.5}, {1, 1}); \
    lm2_manifold_aabb_to_plane_##suffix(box, plane, &hit);                  \
    ASSERT_EQ(hit.count, 2);                                                \
    EXPECT_NEAR(hit.depths[0], 0.5, 1e-5);                                  \
    EXPECT_NEAR(hit.depths[1], 0.5, 1e-5);                                  \
    lm2_triangle2_##suffix triangle = {                                     \
        {-1, -0.5},                                                         \
        { 1, -0.5},                                                          \
        { 0,    1} \
    };                                                            \
    lm2_manifold_triangle_to_plane_##suffix(triangle, plane, &hit);         \
    ASSERT_EQ(hit.count, 2);                                                \
    EXPECT_NEAR(hit.depths[0], 0.5, 1e-5);                                  \
    EXPECT_NEAR(hit.depths[1], 0.5, 1e-5);                                  \
    lm2_v2_##suffix vertices[] = {                                          \
        {-1, -0.5},                                                         \
        { 1, -0.5},                                                          \
        { 1,    1},                                                             \
        {-1,    1} \
    };                                                           \
    lm2_polygon_##suffix polygon = {vertices, 4};                           \
    lm2_manifold_polygon_to_plane_##suffix(polygon, plane, &hit);           \
    ASSERT_EQ(hit.count, 2);                                                \
    EXPECT_NEAR(hit.depths[0], 0.5, 1e-5);                                  \
    EXPECT_NEAR(hit.depths[1], 0.5, 1e-5);                                  \
    for (int i = 0; i < 4; ++i) vertices[i].y += 3;                         \
    lm2_manifold_polygon_to_plane_##suffix(polygon, plane, &hit);           \
    expect_empty_manifold(hit);                                             \
  }

LM2_TEST_PLANE_MANIFOLDS(f32)
LM2_TEST_PLANE_MANIFOLDS(f64)

#undef LM2_TEST_PLANE_MANIFOLDS

TEST(ManifoldPrecision, DoubleCircleManifoldPreservesSubFloatOverlap) {
  lm2_circle_f64 a = lm2_circle_make_coords_f64(0, 0, 1);
  lm2_circle_f64 b = lm2_circle_make_coords_f64(1.3, 0, 1);
  lm2_manifold_f64 result = {};
  lm2_manifold_circle_to_circle_f64(a, b, &result);
  ASSERT_EQ(result.count, 1);
  EXPECT_NEAR(result.depths[0], 0.7, 1e-14);
  EXPECT_NEAR(result.normal.x, 1.0, 1e-14);

  // The double-precision predicate detects overlap smaller than one float ULP.
  b.center.x = 2.0 - 1e-8;
  EXPECT_TRUE(lm2_collide_circle_to_circle_f64(a, b));
  lm2_manifold_circle_to_circle_f64(a, b, &result);
  ASSERT_EQ(result.count, 1);
  EXPECT_NEAR(result.depths[0], 1e-8, 1e-15);
  EXPECT_NEAR(result.contact_points[0].x, 1.0 - 1e-8, 1e-15);
  b.center.x = 2.0;
  lm2_manifold_circle_to_circle_f64(a, b, &result);
  expect_empty_manifold(result);
  b.center.x = 0.0;
  lm2_manifold_circle_to_circle_f64(a, b, &result);
  ASSERT_EQ(result.count, 1);
  EXPECT_DOUBLE_EQ(result.normal.x, 0.0);
  EXPECT_DOUBLE_EQ(result.normal.y, 1.0);
  EXPECT_DOUBLE_EQ(result.depths[0], 2.0);
  EXPECT_DOUBLE_EQ(result.contact_points[0].y, -1.0);
}

TEST(ManifoldPrecision, DoubleCircleAabbDistinguishesSubFloatBoundary) {
  lm2_r2_f64 box = lm2_r2_from_min_max_f64({2, -1}, {4, 1});
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(1 - 1e-8, 0, 1);
  EXPECT_FALSE(lm2_collide_circle_to_aabb_f64(circle, box));
  circle.center.x = 1;
  EXPECT_FALSE(lm2_collide_circle_to_aabb_f64(circle, box));
  circle.center.x = 1 + 1e-8;
  EXPECT_TRUE(lm2_collide_circle_to_aabb_f64(circle, box));
  box = lm2_r2_from_min_max_f64({2, 2}, {4, 4});
  circle.center = {1.39, 1.2};
  EXPECT_FALSE(lm2_collide_circle_to_aabb_f64(circle, box));
  circle.center = {1.41, 1.2};
  EXPECT_TRUE(lm2_collide_circle_to_aabb_f64(circle, box));
}

TEST(ManifoldPrecision, DoubleCircleManifoldDiagonalContact) {
  lm2_circle_f64 a = lm2_circle_make_coords_f64(0, 0, 4);
  lm2_circle_f64 b = lm2_circle_make_coords_f64(3, 4, 2);
  lm2_manifold_f64 result = {};
  lm2_manifold_circle_to_circle_f64(a, b, &result);
  ASSERT_EQ(result.count, 1);
  EXPECT_NEAR(result.depths[0], 1, 1e-14);
  EXPECT_NEAR(result.normal.x, 0.6, 1e-14);
  EXPECT_NEAR(result.normal.y, 0.8, 1e-14);
  EXPECT_NEAR(result.contact_points[0].x, 1.8, 1e-14);
  EXPECT_NEAR(result.contact_points[0].y, 2.4, 1e-14);
}

TEST(ManifoldPrecision, DoubleAabbsDistinguishSubFloatGap) {
  lm2_r2_f64 a = lm2_r2_from_min_max_f64({-1, -1}, {1, 1});
  lm2_r2_f64 b = lm2_r2_from_min_max_f64({1 + 1e-8, -1}, {3, 1});
  EXPECT_FALSE(lm2_collide_aabb_to_aabb_f64(a, b));
  b.min.x = 1;
  EXPECT_TRUE(lm2_collide_aabb_to_aabb_f64(a, b));
  b.min.x = 1 - 1e-8;
  EXPECT_TRUE(lm2_collide_aabb_to_aabb_f64(a, b));
}

// Test fixture for Manifold2 tests
class Manifold2Test : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Boolean Collision Tests - Circle to Circle (f64)
// =============================================================================

TEST_F(Manifold2Test, CollideCircleToCircle_Separated_F64) {
  lm2_circle_f64 a = lm2_circle_make_coords_f64(0.0, 0.0, 2.0);
  lm2_circle_f64 b = lm2_circle_make_coords_f64(10.0, 0.0, 2.0);
  EXPECT_FALSE(lm2_collide_circle_to_circle_f64(a, b));
}

TEST_F(Manifold2Test, CollideCircleToCircle_Touching_F64) {
  lm2_circle_f64 a = lm2_circle_make_coords_f64(0.0, 0.0, 2.0);
  lm2_circle_f64 b = lm2_circle_make_coords_f64(4.0, 0.0, 2.0);
  EXPECT_TRUE(lm2_collide_circle_to_circle_f64(a, b));
}

TEST_F(Manifold2Test, CollideCircleToCircle_Overlapping_F64) {
  lm2_circle_f64 a = lm2_circle_make_coords_f64(0.0, 0.0, 3.0);
  lm2_circle_f64 b = lm2_circle_make_coords_f64(4.0, 0.0, 3.0);
  EXPECT_TRUE(lm2_collide_circle_to_circle_f64(a, b));
}

// =============================================================================
// Boolean Collision Tests - Circle to Circle (f32)
// =============================================================================

TEST_F(Manifold2Test, CollideCircleToCircle_Separated_F32) {
  lm2_circle_f32 a = lm2_circle_make_coords_f32(0.0f, 0.0f, 2.0f);
  lm2_circle_f32 b = lm2_circle_make_coords_f32(10.0f, 0.0f, 2.0f);
  EXPECT_FALSE(lm2_collide_circle_to_circle_f32(a, b));
}

TEST_F(Manifold2Test, CollideCircleToCircle_Overlapping_F32) {
  lm2_circle_f32 a = lm2_circle_make_coords_f32(0.0f, 0.0f, 3.0f);
  lm2_circle_f32 b = lm2_circle_make_coords_f32(4.0f, 0.0f, 3.0f);
  EXPECT_TRUE(lm2_collide_circle_to_circle_f32(a, b));
}

// =============================================================================
// Boolean Collision Tests - Circle to AABB (f64)
// =============================================================================

TEST_F(Manifold2Test, CollideCircleToAABB_Separated_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(0.0, 0.0, 2.0);
  lm2_r2_f64 aabb = lm2_r2_from_min_max_f64(lm2_v2_make_f64(10.0, 10.0), lm2_v2_make_f64(15.0, 15.0));
  EXPECT_FALSE(lm2_collide_circle_to_aabb_f64(circle, aabb));
}

TEST_F(Manifold2Test, CollideCircleToAABB_Overlapping_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(5.0, 5.0, 3.0);
  lm2_r2_f64 aabb = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(10.0, 10.0));
  EXPECT_TRUE(lm2_collide_circle_to_aabb_f64(circle, aabb));
}

TEST_F(Manifold2Test, CollideCircleToAABB_CircleInsideAABB_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(5.0, 5.0, 1.0);
  lm2_r2_f64 aabb = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(10.0, 10.0));
  EXPECT_TRUE(lm2_collide_circle_to_aabb_f64(circle, aabb));
}

// =============================================================================
// Boolean Collision Tests - Circle to AABB (f32)
// =============================================================================

TEST_F(Manifold2Test, CollideCircleToAABB_Separated_F32) {
  lm2_circle_f32 circle = lm2_circle_make_coords_f32(0.0f, 0.0f, 2.0f);
  lm2_r2_f32 aabb = lm2_r2_from_min_max_f32(lm2_v2_make_f32(10.0f, 10.0f), lm2_v2_make_f32(15.0f, 15.0f));
  EXPECT_FALSE(lm2_collide_circle_to_aabb_f32(circle, aabb));
}

TEST_F(Manifold2Test, CollideCircleToAABB_Overlapping_F32) {
  lm2_circle_f32 circle = lm2_circle_make_coords_f32(5.0f, 5.0f, 3.0f);
  lm2_r2_f32 aabb = lm2_r2_from_min_max_f32(lm2_v2_make_f32(0.0f, 0.0f), lm2_v2_make_f32(10.0f, 10.0f));
  EXPECT_TRUE(lm2_collide_circle_to_aabb_f32(circle, aabb));
}

// =============================================================================
// Boolean Collision Tests - Circle to Capsule (f64)
// =============================================================================

TEST_F(Manifold2Test, CollideCircleToCapsule_Separated_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(0.0, 0.0, 2.0);
  lm2_capsule2_f64 capsule = lm2_capsule2_make_coords_f64(10.0, 0.0, 15.0, 0.0, 2.0);
  EXPECT_FALSE(lm2_collide_circle_to_capsule_f64(circle, capsule));
}

TEST_F(Manifold2Test, CollideCircleToCapsule_Overlapping_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(0.0, 0.0, 3.0);
  lm2_capsule2_f64 capsule = lm2_capsule2_make_coords_f64(4.0, 0.0, 8.0, 0.0, 2.0);
  EXPECT_TRUE(lm2_collide_circle_to_capsule_f64(circle, capsule));
}

// =============================================================================
// Boolean Collision Tests - Circle to Capsule (f32)
// =============================================================================

TEST_F(Manifold2Test, CollideCircleToCapsule_Separated_F32) {
  lm2_circle_f32 circle = lm2_circle_make_coords_f32(0.0f, 0.0f, 2.0f);
  lm2_capsule2_f32 capsule = lm2_capsule2_make_coords_f32(10.0f, 0.0f, 15.0f, 0.0f, 2.0f);
  EXPECT_FALSE(lm2_collide_circle_to_capsule_f32(circle, capsule));
}

TEST_F(Manifold2Test, CollideCircleToCapsule_Overlapping_F32) {
  lm2_circle_f32 circle = lm2_circle_make_coords_f32(0.0f, 0.0f, 3.0f);
  lm2_capsule2_f32 capsule = lm2_capsule2_make_coords_f32(4.0f, 0.0f, 8.0f, 0.0f, 2.0f);
  EXPECT_TRUE(lm2_collide_circle_to_capsule_f32(circle, capsule));
}

// =============================================================================
// Boolean Collision Tests - Circle to Polygon (f64)
// =============================================================================

TEST_F(Manifold2Test, CollideCircleToPolygon_Separated_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(0.0, 0.0, 2.0);
  std::vector<lm2_v2_f64> vertices = {
      {10.0, 10.0},
      {15.0, 10.0},
      {15.0, 15.0},
      {10.0, 15.0}
  };
  lm2_polygon_f64 polygon = lm2_polygon_make_f64(vertices.data(), vertices.size());
  EXPECT_FALSE(lm2_collide_circle_to_polygon_f64(circle, polygon));
}

TEST_F(Manifold2Test, CollideCircleToPolygon_Overlapping_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(5.0, 5.0, 3.0);
  std::vector<lm2_v2_f64> vertices = {
      { 0.0,  0.0},
      {10.0,  0.0},
      {10.0, 10.0},
      { 0.0, 10.0}
  };
  lm2_polygon_f64 polygon = lm2_polygon_make_f64(vertices.data(), vertices.size());
  EXPECT_TRUE(lm2_collide_circle_to_polygon_f64(circle, polygon));
}

// =============================================================================
// Boolean Collision Tests - Circle to Polygon (f32)
// =============================================================================

TEST_F(Manifold2Test, CollideCircleToPolygon_Overlapping_F32) {
  lm2_circle_f32 circle = lm2_circle_make_coords_f32(5.0f, 5.0f, 3.0f);
  std::vector<lm2_v2_f32> vertices = {
      { 0.0f,  0.0f},
      {10.0f,  0.0f},
      {10.0f, 10.0f},
      { 0.0f, 10.0f}
  };
  lm2_polygon_f32 polygon = lm2_polygon_make_f32(vertices.data(), vertices.size());
  EXPECT_TRUE(lm2_collide_circle_to_polygon_f32(circle, polygon));
}

// =============================================================================
// Boolean Collision Tests - AABB to AABB (f64)
// =============================================================================

TEST_F(Manifold2Test, CollideAABBToAABB_Separated_F64) {
  lm2_r2_f64 a = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(5.0, 5.0));
  lm2_r2_f64 b = lm2_r2_from_min_max_f64(lm2_v2_make_f64(10.0, 10.0), lm2_v2_make_f64(15.0, 15.0));
  EXPECT_FALSE(lm2_collide_aabb_to_aabb_f64(a, b));
}

TEST_F(Manifold2Test, CollideAABBToAABB_Overlapping_F64) {
  lm2_r2_f64 a = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(8.0, 8.0));
  lm2_r2_f64 b = lm2_r2_from_min_max_f64(lm2_v2_make_f64(5.0, 5.0), lm2_v2_make_f64(10.0, 10.0));
  EXPECT_TRUE(lm2_collide_aabb_to_aabb_f64(a, b));
}

TEST_F(Manifold2Test, CollideAABBToAABB_Touching_F64) {
  lm2_r2_f64 a = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(5.0, 5.0));
  lm2_r2_f64 b = lm2_r2_from_min_max_f64(lm2_v2_make_f64(5.0, 5.0), lm2_v2_make_f64(10.0, 10.0));
  EXPECT_TRUE(lm2_collide_aabb_to_aabb_f64(a, b));
}

// =============================================================================
// Boolean Collision Tests - AABB to AABB (f32)
// =============================================================================

TEST_F(Manifold2Test, CollideAABBToAABB_Separated_F32) {
  lm2_r2_f32 a = lm2_r2_from_min_max_f32(lm2_v2_make_f32(0.0f, 0.0f), lm2_v2_make_f32(5.0f, 5.0f));
  lm2_r2_f32 b = lm2_r2_from_min_max_f32(lm2_v2_make_f32(10.0f, 10.0f), lm2_v2_make_f32(15.0f, 15.0f));
  EXPECT_FALSE(lm2_collide_aabb_to_aabb_f32(a, b));
}

TEST_F(Manifold2Test, CollideAABBToAABB_Overlapping_F32) {
  lm2_r2_f32 a = lm2_r2_from_min_max_f32(lm2_v2_make_f32(0.0f, 0.0f), lm2_v2_make_f32(8.0f, 8.0f));
  lm2_r2_f32 b = lm2_r2_from_min_max_f32(lm2_v2_make_f32(5.0f, 5.0f), lm2_v2_make_f32(10.0f, 10.0f));
  EXPECT_TRUE(lm2_collide_aabb_to_aabb_f32(a, b));
}

// =============================================================================
// Boolean Collision Tests - Capsule to Capsule (f64)
// =============================================================================

TEST_F(Manifold2Test, CollideCapsuleToCapsule_Separated_F64) {
  lm2_capsule2_f64 a = lm2_capsule2_make_coords_f64(0.0, 0.0, 5.0, 0.0, 1.0);
  lm2_capsule2_f64 b = lm2_capsule2_make_coords_f64(10.0, 0.0, 15.0, 0.0, 1.0);
  EXPECT_FALSE(lm2_collide_capsule_to_capsule_f64(a, b));
}

TEST_F(Manifold2Test, CollideCapsuleToCapsule_Overlapping_F64) {
  lm2_capsule2_f64 a = lm2_capsule2_make_coords_f64(0.0, 0.0, 5.0, 0.0, 2.0);
  lm2_capsule2_f64 b = lm2_capsule2_make_coords_f64(4.0, 0.0, 8.0, 0.0, 2.0);
  EXPECT_TRUE(lm2_collide_capsule_to_capsule_f64(a, b));
}

// =============================================================================
// Boolean Collision Tests - Capsule to Capsule (f32)
// =============================================================================

TEST_F(Manifold2Test, CollideCapsuleToCapsule_Separated_F32) {
  lm2_capsule2_f32 a = lm2_capsule2_make_coords_f32(0.0f, 0.0f, 5.0f, 0.0f, 1.0f);
  lm2_capsule2_f32 b = lm2_capsule2_make_coords_f32(10.0f, 0.0f, 15.0f, 0.0f, 1.0f);
  EXPECT_FALSE(lm2_collide_capsule_to_capsule_f32(a, b));
}

TEST_F(Manifold2Test, CollideCapsuleToCapsule_Overlapping_F32) {
  lm2_capsule2_f32 a = lm2_capsule2_make_coords_f32(0.0f, 0.0f, 5.0f, 0.0f, 2.0f);
  lm2_capsule2_f32 b = lm2_capsule2_make_coords_f32(4.0f, 0.0f, 8.0f, 0.0f, 2.0f);
  EXPECT_TRUE(lm2_collide_capsule_to_capsule_f32(a, b));
}

// =============================================================================
// Manifold Tests - Circle to Circle (f64)
// =============================================================================

TEST_F(Manifold2Test, ManifoldCircleToCircle_Overlapping_F64) {
  lm2_circle_f64 a = lm2_circle_make_coords_f64(0.0, 0.0, 3.0);
  lm2_circle_f64 b = lm2_circle_make_coords_f64(4.0, 0.0, 3.0);

  lm2_manifold_f64 manifold;
  lm2_manifold_circle_to_circle_f64(a, b, &manifold);

  EXPECT_GT(manifold.count, 0);
  if (manifold.count > 0) {
    EXPECT_GT(manifold.depths[0], 0.0);
  }
}

TEST_F(Manifold2Test, ManifoldCircleToCircle_Separated_F64) {
  lm2_circle_f64 a = lm2_circle_make_coords_f64(0.0, 0.0, 2.0);
  lm2_circle_f64 b = lm2_circle_make_coords_f64(10.0, 0.0, 2.0);

  lm2_manifold_f64 manifold;
  lm2_manifold_circle_to_circle_f64(a, b, &manifold);

  EXPECT_EQ(manifold.count, 0);
}

// =============================================================================
// Manifold Tests - Circle to Circle (f32)
// =============================================================================

TEST_F(Manifold2Test, ManifoldCircleToCircle_Overlapping_F32) {
  lm2_circle_f32 a = lm2_circle_make_coords_f32(0.0f, 0.0f, 3.0f);
  lm2_circle_f32 b = lm2_circle_make_coords_f32(4.0f, 0.0f, 3.0f);

  lm2_manifold_f32 manifold;
  lm2_manifold_circle_to_circle_f32(a, b, &manifold);

  EXPECT_GT(manifold.count, 0);
}

TEST_F(Manifold2Test, ManifoldCircleToCircle_Separated_F32) {
  lm2_circle_f32 a = lm2_circle_make_coords_f32(0.0f, 0.0f, 2.0f);
  lm2_circle_f32 b = lm2_circle_make_coords_f32(10.0f, 0.0f, 2.0f);

  lm2_manifold_f32 manifold;
  lm2_manifold_circle_to_circle_f32(a, b, &manifold);

  EXPECT_EQ(manifold.count, 0);
}

// =============================================================================
// Manifold Tests - Circle to AABB (f64)
// =============================================================================

TEST_F(Manifold2Test, ManifoldCircleToAABB_Overlapping_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(5.0, 5.0, 3.0);
  lm2_r2_f64 aabb = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(10.0, 10.0));

  lm2_manifold_f64 manifold;
  lm2_manifold_circle_to_aabb_f64(circle, aabb, &manifold);

  EXPECT_GT(manifold.count, 0);
}

TEST_F(Manifold2Test, ManifoldCircleToAABB_Separated_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(0.0, 0.0, 2.0);
  lm2_r2_f64 aabb = lm2_r2_from_min_max_f64(lm2_v2_make_f64(10.0, 10.0), lm2_v2_make_f64(15.0, 15.0));

  lm2_manifold_f64 manifold;
  lm2_manifold_circle_to_aabb_f64(circle, aabb, &manifold);

  EXPECT_EQ(manifold.count, 0);
}

// =============================================================================
// Manifold Tests - Circle to AABB (f32)
// =============================================================================

TEST_F(Manifold2Test, ManifoldCircleToAABB_Overlapping_F32) {
  lm2_circle_f32 circle = lm2_circle_make_coords_f32(5.0f, 5.0f, 3.0f);
  lm2_r2_f32 aabb = lm2_r2_from_min_max_f32(lm2_v2_make_f32(0.0f, 0.0f), lm2_v2_make_f32(10.0f, 10.0f));

  lm2_manifold_f32 manifold;
  lm2_manifold_circle_to_aabb_f32(circle, aabb, &manifold);

  EXPECT_GT(manifold.count, 0);
}

TEST_F(Manifold2Test, ManifoldCircleToCircle_AnalyticalValuesAndReversal_F64) {
  lm2_circle_f64 a = lm2_circle_make_coords_f64(0.0, 0.0, 3.0);
  lm2_circle_f64 b = lm2_circle_make_coords_f64(4.0, 0.0, 3.0);
  lm2_manifold_f64 ab = {};
  lm2_manifold_f64 ba = {};

  lm2_manifold_circle_to_circle_f64(a, b, &ab);
  lm2_manifold_circle_to_circle_f64(b, a, &ba);

  ASSERT_EQ(ab.count, 1);
  EXPECT_DOUBLE_EQ(ab.depths[0], 2.0);
  EXPECT_DOUBLE_EQ(ab.contact_points[0].x, 1.0);
  EXPECT_DOUBLE_EQ(ab.contact_points[0].y, 0.0);
  EXPECT_DOUBLE_EQ(ab.normal.x, 1.0);
  EXPECT_DOUBLE_EQ(ab.normal.y, 0.0);
  EXPECT_DOUBLE_EQ(std::hypot(ab.normal.x, ab.normal.y), 1.0);

  ASSERT_EQ(ba.count, 1);
  EXPECT_DOUBLE_EQ(ba.depths[0], ab.depths[0]);
  EXPECT_DOUBLE_EQ(ba.contact_points[0].x, 3.0);
  EXPECT_DOUBLE_EQ(ba.contact_points[0].y, 0.0);
  EXPECT_DOUBLE_EQ(ba.normal.x, -ab.normal.x);
  EXPECT_DOUBLE_EQ(ba.normal.y, -ab.normal.y);
}

TEST_F(Manifold2Test, ManifoldAABBToAABB_AnalyticalValuesAndReversal_F64) {
  lm2_r2_f64 a = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(4.0, 4.0));
  lm2_r2_f64 b = lm2_r2_from_min_max_f64(lm2_v2_make_f64(3.0, 1.0), lm2_v2_make_f64(6.0, 3.0));
  lm2_manifold_f64 ab = {};
  lm2_manifold_f64 ba = {};

  lm2_manifold_aabb_to_aabb_f64(a, b, &ab);
  lm2_manifold_aabb_to_aabb_f64(b, a, &ba);

  ASSERT_EQ(ab.count, 1);
  EXPECT_DOUBLE_EQ(ab.depths[0], 1.0);
  EXPECT_DOUBLE_EQ(ab.contact_points[0].x, 4.0);
  EXPECT_DOUBLE_EQ(ab.contact_points[0].y, 2.0);
  EXPECT_DOUBLE_EQ(ab.normal.x, 1.0);
  EXPECT_DOUBLE_EQ(ab.normal.y, 0.0);
  EXPECT_DOUBLE_EQ(std::hypot(ab.normal.x, ab.normal.y), 1.0);

  ASSERT_EQ(ba.count, 1);
  EXPECT_DOUBLE_EQ(ba.depths[0], ab.depths[0]);
  EXPECT_DOUBLE_EQ(ba.contact_points[0].x, 3.0);
  EXPECT_DOUBLE_EQ(ba.contact_points[0].y, 2.0);
  EXPECT_DOUBLE_EQ(ba.normal.x, -ab.normal.x);
  EXPECT_DOUBLE_EQ(ba.normal.y, -ab.normal.y);
}

TEST_F(Manifold2Test, GenericCircleAABBDispatchMatchesDirectAndReversesNormal_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(0.0, 0.0, 2.0);
  lm2_aabb2_f64 aabb = lm2_r2_from_min_max_f64(lm2_v2_make_f64(1.0, -2.0), lm2_v2_make_f64(4.0, 2.0));
  lm2_manifold_f64 direct = {};
  lm2_manifold_f64 generic = {};
  lm2_manifold_f64 reversed = {};

  lm2_manifold_circle_to_aabb_f64(circle, aabb, &direct);
  lm2_manifold_shape_to_shape_f64(
      lm2_shape2_from_circle_f64(&circle), lm2_shape2_from_aabb2_f64(&aabb), &generic);
  lm2_manifold_shape_to_shape_f64(
      lm2_shape2_from_aabb2_f64(&aabb), lm2_shape2_from_circle_f64(&circle), &reversed);

  ASSERT_EQ(direct.count, 1);
  ASSERT_EQ(generic.count, direct.count);
  ASSERT_EQ(reversed.count, direct.count);
  EXPECT_DOUBLE_EQ(direct.depths[0], 1.0);
  EXPECT_DOUBLE_EQ(direct.contact_points[0].x, 1.0);
  EXPECT_DOUBLE_EQ(direct.contact_points[0].y, 0.0);
  EXPECT_DOUBLE_EQ(generic.depths[0], direct.depths[0]);
  EXPECT_DOUBLE_EQ(generic.contact_points[0].x, direct.contact_points[0].x);
  EXPECT_DOUBLE_EQ(generic.contact_points[0].y, direct.contact_points[0].y);
  EXPECT_DOUBLE_EQ(generic.normal.x, 1.0);
  EXPECT_DOUBLE_EQ(generic.normal.y, 0.0);
  EXPECT_DOUBLE_EQ(reversed.depths[0], direct.depths[0]);
  EXPECT_DOUBLE_EQ(reversed.contact_points[0].x, direct.contact_points[0].x);
  EXPECT_DOUBLE_EQ(reversed.contact_points[0].y, direct.contact_points[0].y);
  EXPECT_DOUBLE_EQ(reversed.normal.x, -generic.normal.x);
  EXPECT_DOUBLE_EQ(reversed.normal.y, -generic.normal.y);
  EXPECT_DOUBLE_EQ(std::hypot(reversed.normal.x, reversed.normal.y), 1.0);
}

TEST_F(Manifold2Test, CircleCapsuleF64PreservesLargeCoordinatePrecision) {
  constexpr double x = 16777217.0;
  const auto capsule = lm2_capsule2_make_coords_f64(x, -1.0, x, 1.0, 0.3);
  auto circle = lm2_circle_make_coords_f64(x + 0.5, 0.0, 0.3);
  EXPECT_TRUE(lm2_collide_circle_to_capsule_f64(circle, capsule));
  circle.center.x = x + 1.0;
  EXPECT_FALSE(lm2_collide_circle_to_capsule_f64(circle, capsule));

  const auto zero_axis = lm2_capsule2_make_coords_f64(x, 0.0, x, 0.0, 0.3);
  circle.center.x = x + 0.5;
  EXPECT_TRUE(lm2_collide_circle_to_capsule_f64(circle, zero_axis));

  const auto unit_capsule = lm2_capsule2_make_coords_f64(0.0, -1.0, 0.0, 1.0, 0.5);
  circle = lm2_circle_make_coords_f64(1.0, 0.0, 0.5);
  EXPECT_FALSE(lm2_collide_circle_to_capsule_f64(circle, unit_capsule));
  circle.center.x = std::nextafter(1.0, 0.0);
  EXPECT_TRUE(lm2_collide_circle_to_capsule_f64(circle, unit_capsule));
}

TEST_F(Manifold2Test, NormalsF64PreserveSmallEdgesAtLargeCoordinates) {
  constexpr double x = 16777216.0;
  lm2_v2_f64 vertices[] = {
      {      x, 0.0},
      {x + 1.0, 0.0},
      {x + 1.0, 1.0},
      {      x, 1.0}
  };
  lm2_v2_f64 normals[4] = {};
  lm2_compute_normals_f64(vertices, normals, 4);
  const lm2_v2_f64 expected[] = {
      { 0.0, -1.0},
      { 1.0,  0.0},
      { 0.0,  1.0},
      {-1.0,  0.0}
  };
  for (int i = 0; i < 4; ++i) {
    EXPECT_DOUBLE_EQ(normals[i].x, expected[i].x);
    EXPECT_DOUBLE_EQ(normals[i].y, expected[i].y);
  }
  lm2_compute_normals_f64(vertices, vertices, 4);
  for (int i = 0; i < 4; ++i) {
    EXPECT_DOUBLE_EQ(vertices[i].x, expected[i].x);
    EXPECT_DOUBLE_EQ(vertices[i].y, expected[i].y);
  }
  lm2_v2_f64 duplicate[] = {
      {0.0, 0.0},
      {0.0, 0.0},
      {1.0, 0.0}
  };
  lm2_v2_f64 duplicate_normals[3] = {};
  lm2_compute_normals_f64(duplicate, duplicate_normals, 3);
  EXPECT_DOUBLE_EQ(duplicate_normals[0].x, 0.0);
  EXPECT_DOUBLE_EQ(duplicate_normals[0].y, 0.0);
}
