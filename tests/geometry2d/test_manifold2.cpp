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
