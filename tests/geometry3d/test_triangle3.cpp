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
#include "lm2/geometry3d/lm2_triangle3.h"

// Test fixture for Triangle3 tests
class Triangle3Test : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Construction Tests (f64)
// =============================================================================

TEST_F(Triangle3Test, Make_F64) {
  lm2_triangle3_f64 tri;
  lm2_v3_f64 a = lm2_v3_make_f64(0.0, 0.0, 0.0);
  lm2_v3_f64 b = lm2_v3_make_f64(3.0, 0.0, 0.0);
  lm2_v3_f64 c = lm2_v3_make_f64(0.0, 4.0, 0.0);

  lm2_triangle3_make_f64(tri, a, b, c);

  EXPECT_DOUBLE_EQ(tri[0].x, 0.0);
  EXPECT_DOUBLE_EQ(tri[0].y, 0.0);
  EXPECT_DOUBLE_EQ(tri[0].z, 0.0);
  EXPECT_DOUBLE_EQ(tri[1].x, 3.0);
  EXPECT_DOUBLE_EQ(tri[1].y, 0.0);
  EXPECT_DOUBLE_EQ(tri[1].z, 0.0);
  EXPECT_DOUBLE_EQ(tri[2].x, 0.0);
  EXPECT_DOUBLE_EQ(tri[2].y, 4.0);
  EXPECT_DOUBLE_EQ(tri[2].z, 0.0);
}

TEST_F(Triangle3Test, MakeCoords_F64) {
  lm2_triangle3_f64 tri;
  lm2_triangle3_make_coords_f64(tri, 0.0, 0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 4.0, 0.0);

  EXPECT_DOUBLE_EQ(tri[0].x, 0.0);
  EXPECT_DOUBLE_EQ(tri[1].x, 3.0);
  EXPECT_DOUBLE_EQ(tri[2].y, 4.0);
}

// =============================================================================
// Construction Tests (f32)
// =============================================================================

TEST_F(Triangle3Test, Make_F32) {
  lm2_triangle3_f32 tri;
  lm2_v3_f32 a = lm2_v3_make_f32(0.0f, 0.0f, 0.0f);
  lm2_v3_f32 b = lm2_v3_make_f32(3.0f, 0.0f, 0.0f);
  lm2_v3_f32 c = lm2_v3_make_f32(0.0f, 4.0f, 0.0f);

  lm2_triangle3_make_f32(tri, a, b, c);

  EXPECT_FLOAT_EQ(tri[0].x, 0.0f);
  EXPECT_FLOAT_EQ(tri[1].x, 3.0f);
  EXPECT_FLOAT_EQ(tri[2].y, 4.0f);
}

TEST_F(Triangle3Test, MakeCoords_F32) {
  lm2_triangle3_f32 tri;
  lm2_triangle3_make_coords_f32(tri, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 4.0f, 0.0f);

  EXPECT_FLOAT_EQ(tri[0].z, 0.0f);
  EXPECT_FLOAT_EQ(tri[2].y, 4.0f);
}

// =============================================================================
// Properties Tests (f64)
// =============================================================================

TEST_F(Triangle3Test, Area_F64) {
  lm2_triangle3_f64 tri;
  // Right triangle with legs 3 and 4, area = 0.5 * 3 * 4 = 6
  lm2_triangle3_make_coords_f64(tri, 0.0, 0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 4.0, 0.0);

  double area = lm2_triangle3_area_f64(tri);
  EXPECT_NEAR(area, 6.0, EPSILON_F64);
}

TEST_F(Triangle3Test, Perimeter_F64) {
  lm2_triangle3_f64 tri;
  // 3-4-5 right triangle, perimeter = 12
  lm2_triangle3_make_coords_f64(tri, 0.0, 0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 4.0, 0.0);

  double perimeter = lm2_triangle3_perimeter_f64(tri);
  EXPECT_NEAR(perimeter, 12.0, EPSILON_F64);
}

TEST_F(Triangle3Test, Normal_F64) {
  lm2_triangle3_f64 tri;
  // Triangle in XY plane, normal should be +Z
  lm2_triangle3_make_coords_f64(tri, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  lm2_v3_f64 normal = lm2_triangle3_normal_f64(tri);
  EXPECT_NEAR(normal.x, 0.0, EPSILON_F64);
  EXPECT_NEAR(normal.y, 0.0, EPSILON_F64);
  EXPECT_NEAR(normal.z, 1.0, EPSILON_F64);
}

TEST_F(Triangle3Test, Centroid_F64) {
  lm2_triangle3_f64 tri;
  lm2_triangle3_make_coords_f64(tri, 0.0, 0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 3.0, 0.0);

  lm2_v3_f64 centroid = lm2_triangle3_centroid_f64(tri);
  EXPECT_NEAR(centroid.x, 1.0, EPSILON_F64);
  EXPECT_NEAR(centroid.y, 1.0, EPSILON_F64);
  EXPECT_NEAR(centroid.z, 0.0, EPSILON_F64);
}

// =============================================================================
// Properties Tests (f32)
// =============================================================================

TEST_F(Triangle3Test, Area_F32) {
  lm2_triangle3_f32 tri;
  lm2_triangle3_make_coords_f32(tri, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 4.0f, 0.0f);

  float area = lm2_triangle3_area_f32(tri);
  EXPECT_NEAR(area, 6.0f, EPSILON_F32);
}

TEST_F(Triangle3Test, Perimeter_F32) {
  lm2_triangle3_f32 tri;
  lm2_triangle3_make_coords_f32(tri, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 4.0f, 0.0f);

  float perimeter = lm2_triangle3_perimeter_f32(tri);
  EXPECT_NEAR(perimeter, 12.0f, EPSILON_F32);
}

TEST_F(Triangle3Test, Normal_F32) {
  lm2_triangle3_f32 tri;
  lm2_triangle3_make_coords_f32(tri, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

  lm2_v3_f32 normal = lm2_triangle3_normal_f32(tri);
  EXPECT_NEAR(normal.z, 1.0f, EPSILON_F32);
}

TEST_F(Triangle3Test, Centroid_F32) {
  lm2_triangle3_f32 tri;
  lm2_triangle3_make_coords_f32(tri, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f);

  lm2_v3_f32 centroid = lm2_triangle3_centroid_f32(tri);
  EXPECT_NEAR(centroid.x, 1.0f, EPSILON_F32);
  EXPECT_NEAR(centroid.y, 1.0f, EPSILON_F32);
}

// =============================================================================
// Classification Tests (f64)
// =============================================================================

TEST_F(Triangle3Test, IsDegenerate_F64) {
  lm2_triangle3_f64 tri;
  // Collinear points (degenerate triangle)
  lm2_triangle3_make_coords_f64(tri, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 2.0, 0.0, 0.0);

  EXPECT_TRUE(lm2_triangle3_is_degenerate_f64(tri, EPSILON_F64));

  // Normal triangle
  lm2_triangle3_make_coords_f64(tri, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  EXPECT_FALSE(lm2_triangle3_is_degenerate_f64(tri, EPSILON_F64));
}

TEST_F(Triangle3Test, IsRight_F64) {
  lm2_triangle3_f64 tri;
  // 3-4-5 right triangle
  lm2_triangle3_make_coords_f64(tri, 0.0, 0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 4.0, 0.0);

  EXPECT_TRUE(lm2_triangle3_is_right_f64(tri, EPSILON_F64));

  // Equilateral triangle (not right)
  double s = sqrt(3.0) / 2.0;
  lm2_triangle3_make_coords_f64(tri, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.5, s, 0.0);
  EXPECT_FALSE(lm2_triangle3_is_right_f64(tri, EPSILON_F64));
}

TEST_F(Triangle3Test, IsIsosceles_F64) {
  lm2_triangle3_f64 tri;
  // Isosceles triangle (two equal sides)
  lm2_triangle3_make_coords_f64(tri, 0.0, 0.0, 0.0, 2.0, 0.0, 0.0, 1.0, 2.0, 0.0);

  EXPECT_TRUE(lm2_triangle3_is_isosceles_f64(tri, EPSILON_F64));
}

TEST_F(Triangle3Test, IsEquilateral_F64) {
  lm2_triangle3_f64 tri;
  // Equilateral triangle
  double s = sqrt(3.0) / 2.0;
  lm2_triangle3_make_coords_f64(tri, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.5, s, 0.0);

  EXPECT_TRUE(lm2_triangle3_is_equilateral_f64(tri, 1e-6));
}

TEST_F(Triangle3Test, IsScalene_F64) {
  lm2_triangle3_f64 tri;
  // Scalene triangle (all sides different)
  lm2_triangle3_make_coords_f64(tri, 0.0, 0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 4.0, 0.0);

  EXPECT_TRUE(lm2_triangle3_is_scalene_f64(tri, EPSILON_F64));
}

TEST_F(Triangle3Test, Classify_F64) {
  lm2_triangle3_f64 tri;

  // Right triangle
  lm2_triangle3_make_coords_f64(tri, 0.0, 0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 4.0, 0.0);
  EXPECT_EQ(lm2_triangle3_classify_f64(tri, EPSILON_F64), LM2_TRIANGLE3_RIGHT);

  // Equilateral triangle
  double s = sqrt(3.0) / 2.0;
  lm2_triangle3_make_coords_f64(tri, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.5, s, 0.0);
  EXPECT_EQ(lm2_triangle3_classify_f64(tri, 1e-6), LM2_TRIANGLE3_EQUILATERAL);
}

// =============================================================================
// Classification Tests (f32)
// =============================================================================

TEST_F(Triangle3Test, IsDegenerate_F32) {
  lm2_triangle3_f32 tri;
  lm2_triangle3_make_coords_f32(tri, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f);

  EXPECT_TRUE(lm2_triangle3_is_degenerate_f32(tri, EPSILON_F32));
}

TEST_F(Triangle3Test, IsRight_F32) {
  lm2_triangle3_f32 tri;
  lm2_triangle3_make_coords_f32(tri, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 4.0f, 0.0f);

  EXPECT_TRUE(lm2_triangle3_is_right_f32(tri, EPSILON_F32));
}

TEST_F(Triangle3Test, IsEquilateral_F32) {
  lm2_triangle3_f32 tri;
  float s = sqrt(3.0f) / 2.0f;
  lm2_triangle3_make_coords_f32(tri, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, s, 0.0f);

  EXPECT_TRUE(lm2_triangle3_is_equilateral_f32(tri, 1e-4f));
}

// =============================================================================
// Containment Tests (f64)
// =============================================================================

TEST_F(Triangle3Test, ContainsPoint_F64) {
  lm2_triangle3_f64 tri;
  lm2_triangle3_make_coords_f64(tri, 0.0, 0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 4.0, 0.0);

  // Point inside
  lm2_v3_f64 inside = lm2_v3_make_f64(1.0, 1.0, 0.0);
  EXPECT_TRUE(lm2_triangle3_contains_point_f64(tri, inside, EPSILON_F64));

  // Point outside
  lm2_v3_f64 outside = lm2_v3_make_f64(5.0, 5.0, 0.0);
  EXPECT_FALSE(lm2_triangle3_contains_point_f64(tri, outside, EPSILON_F64));

  // Point on edge
  lm2_v3_f64 onEdge = lm2_v3_make_f64(2.0, 0.0, 0.0);
  EXPECT_TRUE(lm2_triangle3_contains_point_f64(tri, onEdge, EPSILON_F64));

  // Point at vertex
  lm2_v3_f64 atVertex = lm2_v3_make_f64(0.0, 0.0, 0.0);
  EXPECT_TRUE(lm2_triangle3_contains_point_f64(tri, atVertex, EPSILON_F64));
}

TEST_F(Triangle3Test, TrianglesOverlap_F64) {
  lm2_triangle3_f64 t1, t2;

  // Overlapping triangles
  lm2_triangle3_make_coords_f64(t1, 0.0, 0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 4.0, 0.0);
  lm2_triangle3_make_coords_f64(t2, 1.0, 1.0, 0.0, 5.0, 1.0, 0.0, 1.0, 5.0, 0.0);

  EXPECT_TRUE(lm2_triangle3_overlaps_f64(t1, t2, EPSILON_F64));

  // Non-overlapping triangles
  lm2_triangle3_make_coords_f64(t2, 10.0, 10.0, 0.0, 14.0, 10.0, 0.0, 10.0, 14.0, 0.0);
  EXPECT_FALSE(lm2_triangle3_overlaps_f64(t1, t2, EPSILON_F64));
}

// =============================================================================
// Containment Tests (f32)
// =============================================================================

TEST_F(Triangle3Test, ContainsPoint_F32) {
  lm2_triangle3_f32 tri;
  lm2_triangle3_make_coords_f32(tri, 0.0f, 0.0f, 0.0f, 4.0f, 0.0f, 0.0f, 0.0f, 4.0f, 0.0f);

  lm2_v3_f32 inside = lm2_v3_make_f32(1.0f, 1.0f, 0.0f);
  EXPECT_TRUE(lm2_triangle3_contains_point_f32(tri, inside, EPSILON_F32));

  lm2_v3_f32 outside = lm2_v3_make_f32(5.0f, 5.0f, 0.0f);
  EXPECT_FALSE(lm2_triangle3_contains_point_f32(tri, outside, EPSILON_F32));
}

TEST_F(Triangle3Test, TrianglesOverlap_F32) {
  lm2_triangle3_f32 t1, t2;

  lm2_triangle3_make_coords_f32(t1, 0.0f, 0.0f, 0.0f, 4.0f, 0.0f, 0.0f, 0.0f, 4.0f, 0.0f);
  lm2_triangle3_make_coords_f32(t2, 1.0f, 1.0f, 0.0f, 5.0f, 1.0f, 0.0f, 1.0f, 5.0f, 0.0f);

  EXPECT_TRUE(lm2_triangle3_overlaps_f32(t1, t2, EPSILON_F32));
}

// =============================================================================
// Edge Operations Tests (f64)
// =============================================================================

TEST_F(Triangle3Test, SharedEdge_F64) {
  lm2_triangle3_f64 t1, t2;

  // Two triangles sharing an edge
  lm2_triangle3_make_coords_f64(t1, 0.0, 0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 3.0, 0.0);
  lm2_triangle3_make_coords_f64(t2, 3.0, 0.0, 0.0, 3.0, 3.0, 0.0, 0.0, 3.0, 0.0);

  lm2_edge3_result_f64 result = lm2_triangle3_shared_edge_f64(t1, t2, EPSILON_F64);
  EXPECT_TRUE(result.exists);

  // Two triangles with no shared edge
  lm2_triangle3_make_coords_f64(t2, 10.0, 10.0, 0.0, 13.0, 10.0, 0.0, 10.0, 13.0, 0.0);
  result = lm2_triangle3_shared_edge_f64(t1, t2, EPSILON_F64);
  EXPECT_FALSE(result.exists);
}

// =============================================================================
// Edge Operations Tests (f32)
// =============================================================================

TEST_F(Triangle3Test, SharedEdge_F32) {
  lm2_triangle3_f32 t1, t2;

  lm2_triangle3_make_coords_f32(t1, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f);
  lm2_triangle3_make_coords_f32(t2, 3.0f, 0.0f, 0.0f, 3.0f, 3.0f, 0.0f, 0.0f, 3.0f, 0.0f);

  lm2_edge3_result_f32 result = lm2_triangle3_shared_edge_f32(t1, t2, EPSILON_F32);
  EXPECT_TRUE(result.exists);
}

// =============================================================================
// 3D Triangle Tests
// =============================================================================

TEST_F(Triangle3Test, Triangle3D_Normal_F64) {
  lm2_triangle3_f64 tri;
  // Triangle not in a standard plane
  lm2_triangle3_make_coords_f64(tri, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 1.0);

  lm2_v3_f64 normal = lm2_triangle3_normal_f64(tri);

  // Normal should be normalized
  double length = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
  EXPECT_NEAR(length, 1.0, EPSILON_F64);
}
