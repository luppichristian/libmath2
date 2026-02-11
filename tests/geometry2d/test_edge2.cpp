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
#include "lm2/geometry2d/lm2_edge2.h"

// Test fixture for Edge2 tests
class Edge2Test : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Construction Tests (f64)
// =============================================================================

TEST_F(Edge2Test, Make_F64) {
  lm2_v2_f64 start = lm2_v2_make_f64(1.0, 2.0);
  lm2_v2_f64 end = lm2_v2_make_f64(5.0, 6.0);
  lm2_edge2_f64 edge = lm2_edge2_make_f64(start, end);

  EXPECT_DOUBLE_EQ(edge.start.x, 1.0);
  EXPECT_DOUBLE_EQ(edge.start.y, 2.0);
  EXPECT_DOUBLE_EQ(edge.end.x, 5.0);
  EXPECT_DOUBLE_EQ(edge.end.y, 6.0);
}

TEST_F(Edge2Test, MakeCoords_F64) {
  lm2_edge2_f64 edge = lm2_edge2_make_coords_f64(0.0, 0.0, 10.0, 10.0);

  EXPECT_DOUBLE_EQ(edge.start.x, 0.0);
  EXPECT_DOUBLE_EQ(edge.start.y, 0.0);
  EXPECT_DOUBLE_EQ(edge.end.x, 10.0);
  EXPECT_DOUBLE_EQ(edge.end.y, 10.0);
}

// =============================================================================
// Construction Tests (f32)
// =============================================================================

TEST_F(Edge2Test, Make_F32) {
  lm2_v2_f32 start = lm2_v2_make_f32(1.0f, 2.0f);
  lm2_v2_f32 end = lm2_v2_make_f32(5.0f, 6.0f);
  lm2_edge2_f32 edge = lm2_edge2_make_f32(start, end);

  EXPECT_FLOAT_EQ(edge.start.x, 1.0f);
  EXPECT_FLOAT_EQ(edge.start.y, 2.0f);
  EXPECT_FLOAT_EQ(edge.end.x, 5.0f);
  EXPECT_FLOAT_EQ(edge.end.y, 6.0f);
}

TEST_F(Edge2Test, MakeCoords_F32) {
  lm2_edge2_f32 edge = lm2_edge2_make_coords_f32(0.0f, 0.0f, 10.0f, 10.0f);

  EXPECT_FLOAT_EQ(edge.start.x, 0.0f);
  EXPECT_FLOAT_EQ(edge.start.y, 0.0f);
  EXPECT_FLOAT_EQ(edge.end.x, 10.0f);
  EXPECT_FLOAT_EQ(edge.end.y, 10.0f);
}

// =============================================================================
// Length Tests (f64)
// =============================================================================

TEST_F(Edge2Test, Length_F64) {
  lm2_edge2_f64 edge = lm2_edge2_make_coords_f64(0.0, 0.0, 3.0, 4.0);
  double length = lm2_edge2_length_f64(edge);
  EXPECT_DOUBLE_EQ(length, 5.0);  // 3-4-5 triangle
}

TEST_F(Edge2Test, Length_Horizontal_F64) {
  lm2_edge2_f64 edge = lm2_edge2_make_coords_f64(0.0, 5.0, 10.0, 5.0);
  double length = lm2_edge2_length_f64(edge);
  EXPECT_DOUBLE_EQ(length, 10.0);
}

TEST_F(Edge2Test, Length_Vertical_F64) {
  lm2_edge2_f64 edge = lm2_edge2_make_coords_f64(5.0, 0.0, 5.0, 8.0);
  double length = lm2_edge2_length_f64(edge);
  EXPECT_DOUBLE_EQ(length, 8.0);
}

TEST_F(Edge2Test, Length_Zero_F64) {
  lm2_edge2_f64 edge = lm2_edge2_make_coords_f64(5.0, 5.0, 5.0, 5.0);
  double length = lm2_edge2_length_f64(edge);
  EXPECT_DOUBLE_EQ(length, 0.0);
}

TEST_F(Edge2Test, LengthSq_F64) {
  lm2_edge2_f64 edge = lm2_edge2_make_coords_f64(0.0, 0.0, 3.0, 4.0);
  double length_sq = lm2_edge2_length_sq_f64(edge);
  EXPECT_DOUBLE_EQ(length_sq, 25.0);  // 3^2 + 4^2
}

// =============================================================================
// Length Tests (f32)
// =============================================================================

TEST_F(Edge2Test, Length_F32) {
  lm2_edge2_f32 edge = lm2_edge2_make_coords_f32(0.0f, 0.0f, 3.0f, 4.0f);
  float length = lm2_edge2_length_f32(edge);
  EXPECT_FLOAT_EQ(length, 5.0f);
}

TEST_F(Edge2Test, Length_Horizontal_F32) {
  lm2_edge2_f32 edge = lm2_edge2_make_coords_f32(0.0f, 5.0f, 10.0f, 5.0f);
  float length = lm2_edge2_length_f32(edge);
  EXPECT_FLOAT_EQ(length, 10.0f);
}

TEST_F(Edge2Test, LengthSq_F32) {
  lm2_edge2_f32 edge = lm2_edge2_make_coords_f32(0.0f, 0.0f, 3.0f, 4.0f);
  float length_sq = lm2_edge2_length_sq_f32(edge);
  EXPECT_FLOAT_EQ(length_sq, 25.0f);
}

// =============================================================================
// Point Equality Tests (f64)
// =============================================================================

TEST_F(Edge2Test, PointsEqual_True_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(1.0, 2.0);
  lm2_v2_f64 b = lm2_v2_make_f64(1.0, 2.0);
  EXPECT_TRUE(lm2_points2_equal_f64(a, b, EPSILON_F64));
}

TEST_F(Edge2Test, PointsEqual_False_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(1.0, 2.0);
  lm2_v2_f64 b = lm2_v2_make_f64(1.1, 2.0);
  EXPECT_FALSE(lm2_points2_equal_f64(a, b, EPSILON_F64));
}

TEST_F(Edge2Test, PointsEqual_WithinEpsilon_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(1.0, 2.0);
  lm2_v2_f64 b = lm2_v2_make_f64(1.0 + 1e-11, 2.0);
  EXPECT_TRUE(lm2_points2_equal_f64(a, b, EPSILON_F64));
}

// =============================================================================
// Point Equality Tests (f32)
// =============================================================================

TEST_F(Edge2Test, PointsEqual_True_F32) {
  lm2_v2_f32 a = lm2_v2_make_f32(1.0f, 2.0f);
  lm2_v2_f32 b = lm2_v2_make_f32(1.0f, 2.0f);
  EXPECT_TRUE(lm2_points2_equal_f32(a, b, EPSILON_F32));
}

TEST_F(Edge2Test, PointsEqual_False_F32) {
  lm2_v2_f32 a = lm2_v2_make_f32(1.0f, 2.0f);
  lm2_v2_f32 b = lm2_v2_make_f32(1.1f, 2.0f);
  EXPECT_FALSE(lm2_points2_equal_f32(a, b, EPSILON_F32));
}

// =============================================================================
// Edge Equality Tests (f64)
// =============================================================================

TEST_F(Edge2Test, EdgesEqual_SameDirection_F64) {
  lm2_edge2_f64 e1 = lm2_edge2_make_coords_f64(0.0, 0.0, 5.0, 5.0);
  lm2_edge2_f64 e2 = lm2_edge2_make_coords_f64(0.0, 0.0, 5.0, 5.0);
  EXPECT_TRUE(lm2_edges2_equal_f64(e1, e2, EPSILON_F64));
}

TEST_F(Edge2Test, EdgesEqual_OppositeDirection_F64) {
  lm2_edge2_f64 e1 = lm2_edge2_make_coords_f64(0.0, 0.0, 5.0, 5.0);
  lm2_edge2_f64 e2 = lm2_edge2_make_coords_f64(5.0, 5.0, 0.0, 0.0);
  EXPECT_TRUE(lm2_edges2_equal_f64(e1, e2, EPSILON_F64));
}

TEST_F(Edge2Test, EdgesEqual_Different_F64) {
  lm2_edge2_f64 e1 = lm2_edge2_make_coords_f64(0.0, 0.0, 5.0, 5.0);
  lm2_edge2_f64 e2 = lm2_edge2_make_coords_f64(1.0, 1.0, 6.0, 6.0);
  EXPECT_FALSE(lm2_edges2_equal_f64(e1, e2, EPSILON_F64));
}

// =============================================================================
// Edge Equality Tests (f32)
// =============================================================================

TEST_F(Edge2Test, EdgesEqual_SameDirection_F32) {
  lm2_edge2_f32 e1 = lm2_edge2_make_coords_f32(0.0f, 0.0f, 5.0f, 5.0f);
  lm2_edge2_f32 e2 = lm2_edge2_make_coords_f32(0.0f, 0.0f, 5.0f, 5.0f);
  EXPECT_TRUE(lm2_edges2_equal_f32(e1, e2, EPSILON_F32));
}

TEST_F(Edge2Test, EdgesEqual_OppositeDirection_F32) {
  lm2_edge2_f32 e1 = lm2_edge2_make_coords_f32(0.0f, 0.0f, 5.0f, 5.0f);
  lm2_edge2_f32 e2 = lm2_edge2_make_coords_f32(5.0f, 5.0f, 0.0f, 0.0f);
  EXPECT_TRUE(lm2_edges2_equal_f32(e1, e2, EPSILON_F32));
}

TEST_F(Edge2Test, EdgesEqual_Different_F32) {
  lm2_edge2_f32 e1 = lm2_edge2_make_coords_f32(0.0f, 0.0f, 5.0f, 5.0f);
  lm2_edge2_f32 e2 = lm2_edge2_make_coords_f32(1.0f, 1.0f, 6.0f, 6.0f);
  EXPECT_FALSE(lm2_edges2_equal_f32(e1, e2, EPSILON_F32));
}

// =============================================================================
// Edge Intersection Tests (f64)
// =============================================================================
// NOTE: lm2_edge2_intersection_f64/f32 functions are not yet implemented in the API
// TODO: Implement edge intersection computation or use lm2_edges2_intersect_f64/f32

/*
TEST_F(Edge2Test, EdgeIntersection_Crossing_F64) {
  lm2_edge2_f64 e1 = lm2_edge2_make_coords_f64(0.0, 0.0, 10.0, 10.0);
  lm2_edge2_f64 e2 = lm2_edge2_make_coords_f64(0.0, 10.0, 10.0, 0.0);
  lm2_v2_f64 intersection;
  bool result = lm2_edge2_intersection_f64(e1, e2, &intersection);

  EXPECT_TRUE(result);
  EXPECT_NEAR(intersection.x, 5.0, EPSILON_F64);
  EXPECT_NEAR(intersection.y, 5.0, EPSILON_F64);
}

TEST_F(Edge2Test, EdgeIntersection_Parallel_F64) {
  lm2_edge2_f64 e1 = lm2_edge2_make_coords_f64(0.0, 0.0, 10.0, 0.0);
  lm2_edge2_f64 e2 = lm2_edge2_make_coords_f64(0.0, 5.0, 10.0, 5.0);
  lm2_v2_f64 intersection;
  bool result = lm2_edge2_intersection_f64(e1, e2, &intersection);

  EXPECT_FALSE(result);
}

TEST_F(Edge2Test, EdgeIntersection_NonIntersecting_F64) {
  lm2_edge2_f64 e1 = lm2_edge2_make_coords_f64(0.0, 0.0, 5.0, 0.0);
  lm2_edge2_f64 e2 = lm2_edge2_make_coords_f64(10.0, 0.0, 15.0, 0.0);
  lm2_v2_f64 intersection;
  bool result = lm2_edge2_intersection_f64(e1, e2, &intersection);

  EXPECT_FALSE(result);
}

TEST_F(Edge2Test, EdgeIntersection_TShape_F64) {
  lm2_edge2_f64 e1 = lm2_edge2_make_coords_f64(0.0, 0.0, 10.0, 0.0);
  lm2_edge2_f64 e2 = lm2_edge2_make_coords_f64(5.0, -5.0, 5.0, 5.0);
  lm2_v2_f64 intersection;
  bool result = lm2_edge2_intersection_f64(e1, e2, &intersection);

  EXPECT_TRUE(result);
  EXPECT_NEAR(intersection.x, 5.0, EPSILON_F64);
  EXPECT_NEAR(intersection.y, 0.0, EPSILON_F64);
}

// =============================================================================
// Edge Intersection Tests (f32)
// =============================================================================

TEST_F(Edge2Test, EdgeIntersection_Crossing_F32) {
  lm2_edge2_f32 e1 = lm2_edge2_make_coords_f32(0.0f, 0.0f, 10.0f, 10.0f);
  lm2_edge2_f32 e2 = lm2_edge2_make_coords_f32(0.0f, 10.0f, 10.0f, 0.0f);
  lm2_v2_f32 intersection;
  bool result = lm2_edge2_intersection_f32(e1, e2, &intersection);

  EXPECT_TRUE(result);
  EXPECT_NEAR(intersection.x, 5.0f, EPSILON_F32);
  EXPECT_NEAR(intersection.y, 5.0f, EPSILON_F32);
}

TEST_F(Edge2Test, EdgeIntersection_Parallel_F32) {
  lm2_edge2_f32 e1 = lm2_edge2_make_coords_f32(0.0f, 0.0f, 10.0f, 0.0f);
  lm2_edge2_f32 e2 = lm2_edge2_make_coords_f32(0.0f, 5.0f, 10.0f, 5.0f);
  lm2_v2_f32 intersection;
  bool result = lm2_edge2_intersection_f32(e1, e2, &intersection);

  EXPECT_FALSE(result);
}

TEST_F(Edge2Test, EdgeIntersection_NonIntersecting_F32) {
  lm2_edge2_f32 e1 = lm2_edge2_make_coords_f32(0.0f, 0.0f, 5.0f, 0.0f);
  lm2_edge2_f32 e2 = lm2_edge2_make_coords_f32(10.0f, 0.0f, 15.0f, 0.0f);
  lm2_v2_f32 intersection;
  bool result = lm2_edge2_intersection_f32(e1, e2, &intersection);

  EXPECT_FALSE(result);
}
*/
