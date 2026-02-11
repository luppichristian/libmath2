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
#include "lm2/geometry3d/lm2_edge3.h"
#include "lm2/geometry3d/lm2_plane3.h"
#include "lm2/geometry3d/lm2_raycast3.h"

// Test fixture for Edge3 tests
class Edge3Test : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Construction Tests (f64)
// =============================================================================

TEST_F(Edge3Test, Make_F64) {
  lm2_v3_f64 start = lm2_v3_make_f64(1.0, 2.0, 3.0);
  lm2_v3_f64 end = lm2_v3_make_f64(4.0, 5.0, 6.0);
  lm2_edge3_f64 edge = lm2_edge3_make_f64(start, end);

  EXPECT_DOUBLE_EQ(edge.start.x, 1.0);
  EXPECT_DOUBLE_EQ(edge.start.y, 2.0);
  EXPECT_DOUBLE_EQ(edge.start.z, 3.0);
  EXPECT_DOUBLE_EQ(edge.end.x, 4.0);
  EXPECT_DOUBLE_EQ(edge.end.y, 5.0);
  EXPECT_DOUBLE_EQ(edge.end.z, 6.0);
}

TEST_F(Edge3Test, MakeCoords_F64) {
  lm2_edge3_f64 edge = lm2_edge3_make_coords_f64(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

  EXPECT_DOUBLE_EQ(edge.start.x, 1.0);
  EXPECT_DOUBLE_EQ(edge.start.y, 2.0);
  EXPECT_DOUBLE_EQ(edge.start.z, 3.0);
  EXPECT_DOUBLE_EQ(edge.end.x, 4.0);
  EXPECT_DOUBLE_EQ(edge.end.y, 5.0);
  EXPECT_DOUBLE_EQ(edge.end.z, 6.0);
}

TEST_F(Edge3Test, FromRay_F64) {
  lm2_ray3_f64 ray = lm2_ray3_make_f64(
      lm2_v3_make_f64(0.0, 0.0, 0.0),
      lm2_v3_make_f64(1.0, 0.0, 0.0),
      10.0);

  lm2_edge3_f64 edge = lm2_edge3_from_ray_f64(ray);

  EXPECT_DOUBLE_EQ(edge.start.x, 0.0);
  EXPECT_DOUBLE_EQ(edge.start.y, 0.0);
  EXPECT_DOUBLE_EQ(edge.start.z, 0.0);
  EXPECT_NEAR(edge.end.x, 10.0, EPSILON_F64);
  EXPECT_NEAR(edge.end.y, 0.0, EPSILON_F64);
  EXPECT_NEAR(edge.end.z, 0.0, EPSILON_F64);
}

TEST_F(Edge3Test, FromPlane_F64) {
  lm2_plane3_f64 plane = lm2_plane3_xy_f64();
  lm2_v3_f64 center = lm2_v3_make_f64(5.0, 5.0, 0.0);
  lm2_v3_f64 direction = lm2_v3_make_f64(1.0, 0.0, 0.0);

  lm2_edge3_f64 edge = lm2_edge3_from_plane_f64(plane, center, direction, 10.0);

  // Edge should be on the plane, centered at (5,5,0), extending 5 units in each direction along X
  EXPECT_NEAR(edge.start.x, 0.0, EPSILON_F64);
  EXPECT_NEAR(edge.start.y, 5.0, EPSILON_F64);
  EXPECT_NEAR(edge.start.z, 0.0, EPSILON_F64);
  EXPECT_NEAR(edge.end.x, 10.0, EPSILON_F64);
  EXPECT_NEAR(edge.end.y, 5.0, EPSILON_F64);
  EXPECT_NEAR(edge.end.z, 0.0, EPSILON_F64);
}

// =============================================================================
// Construction Tests (f32)
// =============================================================================

TEST_F(Edge3Test, Make_F32) {
  lm2_v3_f32 start = lm2_v3_make_f32(1.0f, 2.0f, 3.0f);
  lm2_v3_f32 end = lm2_v3_make_f32(4.0f, 5.0f, 6.0f);
  lm2_edge3_f32 edge = lm2_edge3_make_f32(start, end);

  EXPECT_FLOAT_EQ(edge.start.x, 1.0f);
  EXPECT_FLOAT_EQ(edge.end.x, 4.0f);
}

TEST_F(Edge3Test, MakeCoords_F32) {
  lm2_edge3_f32 edge = lm2_edge3_make_coords_f32(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);

  EXPECT_FLOAT_EQ(edge.start.z, 3.0f);
  EXPECT_FLOAT_EQ(edge.end.z, 6.0f);
}

// =============================================================================
// Properties Tests (f64)
// =============================================================================

TEST_F(Edge3Test, Length_F64) {
  // 3-4-5 triangle in XY plane, extended to 3D
  lm2_edge3_f64 edge = lm2_edge3_make_coords_f64(0.0, 0.0, 0.0, 3.0, 4.0, 0.0);

  double length = lm2_edge3_length_f64(edge);
  EXPECT_NEAR(length, 5.0, EPSILON_F64);
}

TEST_F(Edge3Test, LengthSquared_F64) {
  lm2_edge3_f64 edge = lm2_edge3_make_coords_f64(0.0, 0.0, 0.0, 3.0, 4.0, 0.0);

  double lengthSq = lm2_edge3_length_sq_f64(edge);
  EXPECT_DOUBLE_EQ(lengthSq, 25.0);
}

TEST_F(Edge3Test, Length3D_F64) {
  // Pythagorean quadruple: 2-3-6-7
  lm2_edge3_f64 edge = lm2_edge3_make_coords_f64(0.0, 0.0, 0.0, 2.0, 3.0, 6.0);

  double length = lm2_edge3_length_f64(edge);
  EXPECT_NEAR(length, 7.0, EPSILON_F64);
}

// =============================================================================
// Properties Tests (f32)
// =============================================================================

TEST_F(Edge3Test, Length_F32) {
  lm2_edge3_f32 edge = lm2_edge3_make_coords_f32(0.0f, 0.0f, 0.0f, 3.0f, 4.0f, 0.0f);

  float length = lm2_edge3_length_f32(edge);
  EXPECT_NEAR(length, 5.0f, EPSILON_F32);
}

TEST_F(Edge3Test, LengthSquared_F32) {
  lm2_edge3_f32 edge = lm2_edge3_make_coords_f32(0.0f, 0.0f, 0.0f, 3.0f, 4.0f, 0.0f);

  float lengthSq = lm2_edge3_length_sq_f32(edge);
  EXPECT_FLOAT_EQ(lengthSq, 25.0f);
}

// =============================================================================
// Comparison Tests (f64)
// =============================================================================

TEST_F(Edge3Test, PointsEqual_F64) {
  lm2_v3_f64 a = lm2_v3_make_f64(1.0, 2.0, 3.0);
  lm2_v3_f64 b = lm2_v3_make_f64(1.0, 2.0, 3.0);
  lm2_v3_f64 c = lm2_v3_make_f64(1.0, 2.0, 3.1);

  EXPECT_TRUE(lm2_points3_equal_f64(a, b, EPSILON_F64));
  EXPECT_FALSE(lm2_points3_equal_f64(a, c, EPSILON_F64));
}

TEST_F(Edge3Test, EdgesEqual_F64) {
  lm2_edge3_f64 e1 = lm2_edge3_make_coords_f64(0.0, 0.0, 0.0, 5.0, 5.0, 5.0);
  lm2_edge3_f64 e2 = lm2_edge3_make_coords_f64(0.0, 0.0, 0.0, 5.0, 5.0, 5.0);
  lm2_edge3_f64 e3 = lm2_edge3_make_coords_f64(5.0, 5.0, 5.0, 0.0, 0.0, 0.0);  // Same edge, reversed
  lm2_edge3_f64 e4 = lm2_edge3_make_coords_f64(0.0, 0.0, 0.0, 5.0, 5.0, 6.0);  // Different edge

  EXPECT_TRUE(lm2_edges3_equal_f64(e1, e2, EPSILON_F64));
  EXPECT_TRUE(lm2_edges3_equal_f64(e1, e3, EPSILON_F64));  // Should be equal regardless of direction
  EXPECT_FALSE(lm2_edges3_equal_f64(e1, e4, EPSILON_F64));
}

// =============================================================================
// Comparison Tests (f32)
// =============================================================================

TEST_F(Edge3Test, PointsEqual_F32) {
  lm2_v3_f32 a = lm2_v3_make_f32(1.0f, 2.0f, 3.0f);
  lm2_v3_f32 b = lm2_v3_make_f32(1.0f, 2.0f, 3.0f);

  EXPECT_TRUE(lm2_points3_equal_f32(a, b, EPSILON_F32));
}

TEST_F(Edge3Test, EdgesEqual_F32) {
  lm2_edge3_f32 e1 = lm2_edge3_make_coords_f32(0.0f, 0.0f, 0.0f, 5.0f, 5.0f, 5.0f);
  lm2_edge3_f32 e2 = lm2_edge3_make_coords_f32(0.0f, 0.0f, 0.0f, 5.0f, 5.0f, 5.0f);

  EXPECT_TRUE(lm2_edges3_equal_f32(e1, e2, EPSILON_F32));
}

// =============================================================================
// Intersection Tests (f64)
// =============================================================================

TEST_F(Edge3Test, EdgesIntersect_Coplanar_F64) {
  // Two edges that intersect in 3D space (crossing)
  lm2_edge3_f64 e1 = lm2_edge3_make_coords_f64(0.0, 0.0, 0.0, 10.0, 0.0, 0.0);
  lm2_edge3_f64 e2 = lm2_edge3_make_coords_f64(5.0, -5.0, 0.0, 5.0, 5.0, 0.0);

  EXPECT_TRUE(lm2_edges3_intersect_f64(e1, e2, EPSILON_F64));
}

TEST_F(Edge3Test, EdgesIntersect_NonIntersecting_F64) {
  // Two edges that don't intersect (skew lines)
  lm2_edge3_f64 e1 = lm2_edge3_make_coords_f64(0.0, 0.0, 0.0, 10.0, 0.0, 0.0);
  lm2_edge3_f64 e2 = lm2_edge3_make_coords_f64(0.0, 5.0, 5.0, 10.0, 5.0, 5.0);

  EXPECT_FALSE(lm2_edges3_intersect_f64(e1, e2, EPSILON_F64));
}

TEST_F(Edge3Test, EdgesIntersect_Parallel_F64) {
  // Parallel edges that don't intersect
  lm2_edge3_f64 e1 = lm2_edge3_make_coords_f64(0.0, 0.0, 0.0, 10.0, 0.0, 0.0);
  lm2_edge3_f64 e2 = lm2_edge3_make_coords_f64(0.0, 5.0, 0.0, 10.0, 5.0, 0.0);

  EXPECT_FALSE(lm2_edges3_intersect_f64(e1, e2, EPSILON_F64));
}

// =============================================================================
// Intersection Tests (f32)
// =============================================================================

TEST_F(Edge3Test, EdgesIntersect_Coplanar_F32) {
  lm2_edge3_f32 e1 = lm2_edge3_make_coords_f32(0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f);
  lm2_edge3_f32 e2 = lm2_edge3_make_coords_f32(5.0f, -5.0f, 0.0f, 5.0f, 5.0f, 0.0f);

  EXPECT_TRUE(lm2_edges3_intersect_f32(e1, e2, EPSILON_F32));
}

TEST_F(Edge3Test, EdgesIntersect_NonIntersecting_F32) {
  lm2_edge3_f32 e1 = lm2_edge3_make_coords_f32(0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f);
  lm2_edge3_f32 e2 = lm2_edge3_make_coords_f32(0.0f, 5.0f, 5.0f, 10.0f, 5.0f, 5.0f);

  EXPECT_FALSE(lm2_edges3_intersect_f32(e1, e2, EPSILON_F32));
}

// =============================================================================
// Distance Tests (f64)
// =============================================================================

TEST_F(Edge3Test, PointToEdgeDistance_F64) {
  // Edge from (0,0,0) to (10,0,0)
  lm2_edge3_f64 edge = lm2_edge3_make_coords_f64(0.0, 0.0, 0.0, 10.0, 0.0, 0.0);

  // Point directly above middle of edge
  lm2_v3_f64 point = lm2_v3_make_f64(5.0, 5.0, 0.0);
  double distSq = lm2_point_to_edge3_distance_sq_f64(point, edge);
  EXPECT_NEAR(distSq, 25.0, EPSILON_F64);  // Distance = 5, squared = 25

  // Point at end of edge
  lm2_v3_f64 endPoint = lm2_v3_make_f64(10.0, 0.0, 0.0);
  distSq = lm2_point_to_edge3_distance_sq_f64(endPoint, edge);
  EXPECT_NEAR(distSq, 0.0, EPSILON_F64);
}

TEST_F(Edge3Test, EdgeToEdgeDistance_F64) {
  // Two parallel edges
  lm2_edge3_f64 e1 = lm2_edge3_make_coords_f64(0.0, 0.0, 0.0, 10.0, 0.0, 0.0);
  lm2_edge3_f64 e2 = lm2_edge3_make_coords_f64(0.0, 5.0, 0.0, 10.0, 5.0, 0.0);

  double distSq = lm2_edge3_to_edge3_distance_sq_f64(e1, e2);
  EXPECT_NEAR(distSq, 25.0, EPSILON_F64);  // Distance = 5, squared = 25

  // Two intersecting edges
  lm2_edge3_f64 e3 = lm2_edge3_make_coords_f64(0.0, 0.0, 0.0, 10.0, 0.0, 0.0);
  lm2_edge3_f64 e4 = lm2_edge3_make_coords_f64(5.0, -5.0, 0.0, 5.0, 5.0, 0.0);

  distSq = lm2_edge3_to_edge3_distance_sq_f64(e3, e4);
  EXPECT_NEAR(distSq, 0.0, EPSILON_F64);
}

// =============================================================================
// Distance Tests (f32)
// =============================================================================

TEST_F(Edge3Test, PointToEdgeDistance_F32) {
  lm2_edge3_f32 edge = lm2_edge3_make_coords_f32(0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f);
  lm2_v3_f32 point = lm2_v3_make_f32(5.0f, 5.0f, 0.0f);

  float distSq = lm2_point_to_edge3_distance_sq_f32(point, edge);
  EXPECT_NEAR(distSq, 25.0f, EPSILON_F32);
}

TEST_F(Edge3Test, EdgeToEdgeDistance_F32) {
  lm2_edge3_f32 e1 = lm2_edge3_make_coords_f32(0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f);
  lm2_edge3_f32 e2 = lm2_edge3_make_coords_f32(0.0f, 5.0f, 0.0f, 10.0f, 5.0f, 0.0f);

  float distSq = lm2_edge3_to_edge3_distance_sq_f32(e1, e2);
  EXPECT_NEAR(distSq, 25.0f, EPSILON_F32);
}

// =============================================================================
// Edge Cases
// =============================================================================

TEST_F(Edge3Test, ZeroLengthEdge_F64) {
  lm2_v3_f64 point = lm2_v3_make_f64(5.0, 5.0, 5.0);
  lm2_edge3_f64 edge = lm2_edge3_make_f64(point, point);

  EXPECT_DOUBLE_EQ(lm2_edge3_length_f64(edge), 0.0);
  EXPECT_DOUBLE_EQ(lm2_edge3_length_sq_f64(edge), 0.0);
}

TEST_F(Edge3Test, VerticalEdge_F64) {
  // Edge along Z axis
  lm2_edge3_f64 edge = lm2_edge3_make_coords_f64(0.0, 0.0, 0.0, 0.0, 0.0, 10.0);

  double length = lm2_edge3_length_f64(edge);
  EXPECT_DOUBLE_EQ(length, 10.0);

  // Point on the edge
  lm2_v3_f64 onEdge = lm2_v3_make_f64(0.0, 0.0, 5.0);
  double distSq = lm2_point_to_edge3_distance_sq_f64(onEdge, edge);
  EXPECT_NEAR(distSq, 0.0, EPSILON_F64);
}
