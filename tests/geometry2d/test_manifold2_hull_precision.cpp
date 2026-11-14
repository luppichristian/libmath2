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
#include "lm2/geometry2d/lm2_manifold2.h"

TEST(ConvexHullPrecisionTest, F64PreservesUnitSquareAtLargeCoordinates) {
  constexpr double x = 16777216.0;
  lm2_v2_f64 points[] = {
      {      x, 0.0},
      {x + 1.0, 0.0},
      {x + 1.0, 1.0},
      {      x, 1.0}
  };
  lm2_v2_f64 hull[4] = {};
  ASSERT_EQ(lm2_convex_hull_f64(points, 4, hull, 4), 4);
  bool found[4] = {};
  for (const auto& vertex : hull) {
    if (vertex.x == x && vertex.y == 0.0) found[0] = true;
    if (vertex.x == x + 1.0 && vertex.y == 0.0) found[1] = true;
    if (vertex.x == x + 1.0 && vertex.y == 1.0) found[2] = true;
    if (vertex.x == x && vertex.y == 1.0) found[3] = true;
  }
  for (bool present : found) EXPECT_TRUE(present);

  lm2_polygon_f64 polygon = {points, 4};
  lm2_v2_f64 normals[4] = {};
  lm2_make_convex_polygon_f64(&polygon, normals);
  ASSERT_EQ(polygon.vertex_count, 4u);
  EXPECT_DOUBLE_EQ(lm2_polygon_area_f64(polygon), 1.0);
  for (const auto& normal : normals) EXPECT_NEAR(std::hypot(normal.x, normal.y), 1.0, 1e-12);
}

TEST(ConvexHullPrecisionTest, F64IncludesPointsBeyondBackendLimit) {
  lm2_v2_f64 points[] = {
      {  0,   0},
      {  1,   0},
      {  1,   1},
      {  0,   1},
      {0.2, 0.2},
      {0.3, 0.3},
      {0.4, 0.4},
      {0.5, 0.5},
      { 10,   0}
  };
  lm2_v2_f64 hull[9] = {};
  const int count = lm2_convex_hull_f64(points, 9, hull, 9);
  ASSERT_GE(count, 3);
  bool found = false;
  for (int i = 0; i < count; ++i) {
    if (hull[i].x == 10.0 && hull[i].y == 0.0) found = true;
  }
  EXPECT_TRUE(found);
}

TEST(ConvexHullPrecisionTest, F64HandlesVerySmallAndLargeSquares) {
  for (double scale : {1e-200, 1e200}) {
    lm2_v2_f64 points[] = {
        {    0,     0},
        {scale,     0},
        {scale, scale},
        {    0, scale}
    };
    lm2_v2_f64 hull[4] = {};
    EXPECT_EQ(lm2_convex_hull_f64(points, 4, hull, 4), 4) << "scale " << scale;
  }
}

TEST(ConvexHullPrecisionTest, F64HandlesDuplicatesCollinearPointsAndBoundedOutput) {
  lm2_v2_f64 collinear[] = {
      {  1,   1},
      {  0,   0},
      {  2,   2},
      {  1,   1},
      {1.5, 1.5}
  };
  lm2_v2_f64 hull[5] = {};
  ASSERT_EQ(lm2_convex_hull_f64(collinear, 5, hull, 5), 2);
  EXPECT_DOUBLE_EQ(hull[0].x, 2.0);
  EXPECT_DOUBLE_EQ(hull[0].y, 2.0);
  EXPECT_DOUBLE_EQ(hull[1].x, 0.0);
  EXPECT_DOUBLE_EQ(hull[1].y, 0.0);

  lm2_v2_f64 square[] = {
      {0, 0},
      {1, 0},
      {1, 1},
      {0, 1}
  };
  lm2_v2_f64 bounded[] = {
      { 0,  0},
      { 0,  0},
      {42, 43}
  };
  ASSERT_EQ(lm2_convex_hull_f64(square, 4, bounded, 2), 2);
  EXPECT_DOUBLE_EQ(bounded[0].x, 1.0);
  EXPECT_DOUBLE_EQ(bounded[0].y, 0.0);
  EXPECT_DOUBLE_EQ(bounded[1].x, 1.0);
  EXPECT_DOUBLE_EQ(bounded[1].y, 1.0);
  EXPECT_DOUBLE_EQ(bounded[2].x, 42.0);
  EXPECT_DOUBLE_EQ(bounded[2].y, 43.0);

  ASSERT_EQ(lm2_convex_hull_f64(square, 4, square, 4), 4);
  EXPECT_DOUBLE_EQ(square[0].x, 1.0);
  EXPECT_DOUBLE_EQ(square[0].y, 0.0);
  EXPECT_DOUBLE_EQ(square[3].x, 0.0);
  EXPECT_DOUBLE_EQ(square[3].y, 0.0);
}

TEST(ConvexHullPrecisionTest, F64RetainsMoreThanEightExtremeVertices) {
  lm2_v2_f64 points[12];
  for (int i = 0; i < 12; ++i) {
    const double angle = i * (2.0 * std::acos(-1.0) / 12.0);
    points[i] = {std::cos(angle), std::sin(angle)};
  }
  lm2_v2_f64 normals[12] = {};
  lm2_polygon_f64 polygon = {points, 12};
  lm2_make_convex_polygon_f64(&polygon, normals);
  ASSERT_EQ(polygon.vertex_count, 12u);
  for (const auto& normal : normals) EXPECT_NEAR(std::hypot(normal.x, normal.y), 1.0, 1e-12);
  EXPECT_NEAR(lm2_polygon_area_f64(polygon), 3.0, 1e-12);
}

TEST(ConvexHullPrecisionTest, F64HullContainsDeterministicPointSets) {
  uint32_t state = 0x71534a2bu;
  for (int sample = 0; sample < 100; ++sample) {
    lm2_v2_f64 points[20];
    for (auto& point : points) {
      state = state * 1664525u + 1013904223u;
      point.x = static_cast<int>(state % 101u) - 50;
      state = state * 1664525u + 1013904223u;
      point.y = static_cast<int>(state % 101u) - 50;
    }
    lm2_v2_f64 hull[20] = {};
    const int count = lm2_convex_hull_f64(points, 20, hull, 20);
    ASSERT_GE(count, 3) << "sample " << sample;
    ASSERT_LE(count, 20);
    for (int i = 0; i < count; ++i) {
      const auto a = hull[i];
      const auto b = hull[(i + 1) % count];
      for (const auto point : points) {
        const double cross = (b.x - a.x) * (point.y - a.y) - (b.y - a.y) * (point.x - a.x);
        EXPECT_GE(cross, 0.0) << "sample " << sample << ", edge " << i;
      }
    }
  }
}
