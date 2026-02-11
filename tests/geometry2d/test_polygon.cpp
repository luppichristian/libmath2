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
#include "lm2/geometry2d/lm2_polygon.h"
#include "lm2/lm2_constants.h"
#include "lm2/vectors/lm2_vector_specifics.h"

// Test fixture for Polygon tests
class PolygonTest : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Construction Tests (f64)
// =============================================================================

TEST_F(PolygonTest, Make_F64) {
  std::vector<lm2_v2_f64> vertices = {
      { 0.0,  0.0},
      {10.0,  0.0},
      {10.0, 10.0},
      { 0.0, 10.0}
  };
  lm2_polygon_f64 polygon = lm2_polygon_make_f64(vertices.data(), vertices.size());

  EXPECT_EQ(polygon.vertex_count, 4);
  EXPECT_NE(polygon.vertices, nullptr);
}

TEST_F(PolygonTest, MakeRegular_F64) {
  const size_t num_sides = 6;
  std::vector<lm2_v2_f64> vertices(num_sides);
  lm2_v2_f64 center = lm2_v2_make_f64(5.0, 5.0);
  double radius = 3.0;

  lm2_polygon_make_regular_f64(vertices.data(), num_sides, center, radius);

  // Verify first vertex is at the expected position
  EXPECT_NEAR(vertices[0].x, center.x + radius, EPSILON_F64);
  EXPECT_NEAR(vertices[0].y, center.y, EPSILON_F64);

  // Verify all vertices are at radius distance from center
  for (size_t i = 0; i < num_sides; ++i) {
    lm2_v2_f64 vec = lm2_v2_sub_f64(vertices[i], center);
    double dist = lm2_v2_length_f64(vec);
    EXPECT_NEAR(dist, radius, EPSILON_F64);
  }
}

TEST_F(PolygonTest, MakeRect_F64) {
  lm2_v2_f64 vertices[4];
  lm2_v2_f64 min = lm2_v2_make_f64(0.0, 0.0);
  lm2_v2_f64 max = lm2_v2_make_f64(10.0, 5.0);

  lm2_polygon_make_rect_f64(vertices, min, max);

  EXPECT_DOUBLE_EQ(vertices[0].x, 0.0);
  EXPECT_DOUBLE_EQ(vertices[0].y, 0.0);
  EXPECT_DOUBLE_EQ(vertices[1].x, 10.0);
  EXPECT_DOUBLE_EQ(vertices[2].y, 5.0);
}

// =============================================================================
// Construction Tests (f32)
// =============================================================================

TEST_F(PolygonTest, Make_F32) {
  std::vector<lm2_v2_f32> vertices = {
      { 0.0f,  0.0f},
      {10.0f,  0.0f},
      {10.0f, 10.0f},
      { 0.0f, 10.0f}
  };
  lm2_polygon_f32 polygon = lm2_polygon_make_f32(vertices.data(), vertices.size());

  EXPECT_EQ(polygon.vertex_count, 4);
  EXPECT_NE(polygon.vertices, nullptr);
}

TEST_F(PolygonTest, MakeRegular_F32) {
  const size_t num_sides = 8;
  std::vector<lm2_v2_f32> vertices(num_sides);
  lm2_v2_f32 center = lm2_v2_make_f32(0.0f, 0.0f);
  float radius = 5.0f;

  lm2_polygon_make_regular_f32(vertices.data(), num_sides, center, radius);

  // Verify all vertices are at radius distance from center
  for (size_t i = 0; i < num_sides; ++i) {
    lm2_v2_f32 vec = lm2_v2_sub_f32(vertices[i], center);
    float dist = lm2_v2_length_f32(vec);
    EXPECT_NEAR(dist, radius, EPSILON_F32);
  }
}

TEST_F(PolygonTest, MakeRect_F32) {
  lm2_v2_f32 vertices[4];
  lm2_v2_f32 min = lm2_v2_make_f32(0.0f, 0.0f);
  lm2_v2_f32 max = lm2_v2_make_f32(10.0f, 5.0f);

  lm2_polygon_make_rect_f32(vertices, min, max);

  EXPECT_FLOAT_EQ(vertices[0].x, 0.0f);
  EXPECT_FLOAT_EQ(vertices[2].y, 5.0f);
}

// =============================================================================
// Validation Tests (f64)
// =============================================================================

TEST_F(PolygonTest, Validate_Valid_F64) {
  std::vector<lm2_v2_f64> vertices = {
      { 0.0,  0.0},
      {10.0,  0.0},
      {10.0, 10.0}
  };
  lm2_polygon_f64 polygon = lm2_polygon_make_f64(vertices.data(), vertices.size());

  EXPECT_TRUE(lm2_polygon_validate_f64(polygon));
}

TEST_F(PolygonTest, Validate_NullPointer_F64) {
  lm2_polygon_f64 polygon;
  polygon.vertices = nullptr;
  polygon.vertex_count = 3;

  EXPECT_FALSE(lm2_polygon_validate_f64(polygon));
}

TEST_F(PolygonTest, Validate_TooFewVertices_F64) {
  std::vector<lm2_v2_f64> vertices = {
      { 0.0, 0.0},
      {10.0, 0.0}
  };
  lm2_polygon_f64 polygon = lm2_polygon_make_f64(vertices.data(), vertices.size());

  EXPECT_FALSE(lm2_polygon_validate_f64(polygon));
}

// =============================================================================
// Validation Tests (f32)
// =============================================================================

TEST_F(PolygonTest, Validate_Valid_F32) {
  std::vector<lm2_v2_f32> vertices = {
      { 0.0f,  0.0f},
      {10.0f,  0.0f},
      {10.0f, 10.0f}
  };
  lm2_polygon_f32 polygon = lm2_polygon_make_f32(vertices.data(), vertices.size());

  EXPECT_TRUE(lm2_polygon_validate_f32(polygon));
}

// =============================================================================
// Area Tests (f64)
// =============================================================================

TEST_F(PolygonTest, SignedArea_CCW_F64) {
  std::vector<lm2_v2_f64> vertices = {
      { 0.0,  0.0},
      {10.0,  0.0},
      {10.0, 10.0},
      { 0.0, 10.0}
  };
  lm2_polygon_f64 polygon = lm2_polygon_make_f64(vertices.data(), vertices.size());
  double area = lm2_polygon_signed_area_f64(polygon);

  EXPECT_DOUBLE_EQ(area, 100.0);
}

TEST_F(PolygonTest, SignedArea_CW_F64) {
  std::vector<lm2_v2_f64> vertices = {
      { 0.0,  0.0},
      { 0.0, 10.0},
      {10.0, 10.0},
      {10.0,  0.0}
  };
  lm2_polygon_f64 polygon = lm2_polygon_make_f64(vertices.data(), vertices.size());
  double area = lm2_polygon_signed_area_f64(polygon);

  EXPECT_DOUBLE_EQ(area, -100.0);
}

TEST_F(PolygonTest, Area_F64) {
  std::vector<lm2_v2_f64> vertices = {
      { 0.0,  0.0},
      {10.0,  0.0},
      {10.0, 10.0},
      { 0.0, 10.0}
  };
  lm2_polygon_f64 polygon = lm2_polygon_make_f64(vertices.data(), vertices.size());
  double area = lm2_polygon_area_f64(polygon);

  EXPECT_DOUBLE_EQ(area, 100.0);
}

// =============================================================================
// Area Tests (f32)
// =============================================================================

TEST_F(PolygonTest, SignedArea_CCW_F32) {
  std::vector<lm2_v2_f32> vertices = {
      { 0.0f,  0.0f},
      {10.0f,  0.0f},
      {10.0f, 10.0f},
      { 0.0f, 10.0f}
  };
  lm2_polygon_f32 polygon = lm2_polygon_make_f32(vertices.data(), vertices.size());
  float area = lm2_polygon_signed_area_f32(polygon);

  EXPECT_FLOAT_EQ(area, 100.0f);
}

TEST_F(PolygonTest, Area_F32) {
  std::vector<lm2_v2_f32> vertices = {
      { 0.0f,  0.0f},
      {10.0f,  0.0f},
      {10.0f, 10.0f},
      { 0.0f, 10.0f}
  };
  lm2_polygon_f32 polygon = lm2_polygon_make_f32(vertices.data(), vertices.size());
  float area = lm2_polygon_area_f32(polygon);

  EXPECT_FLOAT_EQ(area, 100.0f);
}

// =============================================================================
// Winding Order Tests (f64)
// =============================================================================

TEST_F(PolygonTest, WindingOrder_CCW_F64) {
  std::vector<lm2_v2_f64> vertices = {
      { 0.0,  0.0},
      {10.0,  0.0},
      {10.0, 10.0},
      { 0.0, 10.0}
  };
  lm2_polygon_f64 polygon = lm2_polygon_make_f64(vertices.data(), vertices.size());
  lm2_winding_order winding = lm2_polygon_winding_order_f64(polygon);

  EXPECT_EQ(winding, LM2_WINDING_COUNTERCLOCKWISE);
}

TEST_F(PolygonTest, WindingOrder_CW_F64) {
  std::vector<lm2_v2_f64> vertices = {
      { 0.0,  0.0},
      { 0.0, 10.0},
      {10.0, 10.0},
      {10.0,  0.0}
  };
  lm2_polygon_f64 polygon = lm2_polygon_make_f64(vertices.data(), vertices.size());
  lm2_winding_order winding = lm2_polygon_winding_order_f64(polygon);

  EXPECT_EQ(winding, LM2_WINDING_CLOCKWISE);
}

// =============================================================================
// Winding Order Tests (f32)
// =============================================================================

TEST_F(PolygonTest, WindingOrder_CCW_F32) {
  std::vector<lm2_v2_f32> vertices = {
      { 0.0f,  0.0f},
      {10.0f,  0.0f},
      {10.0f, 10.0f},
      { 0.0f, 10.0f}
  };
  lm2_polygon_f32 polygon = lm2_polygon_make_f32(vertices.data(), vertices.size());
  lm2_winding_order winding = lm2_polygon_winding_order_f32(polygon);

  EXPECT_EQ(winding, LM2_WINDING_COUNTERCLOCKWISE);
}

// =============================================================================
// Perimeter Tests (f64)
// =============================================================================

TEST_F(PolygonTest, Perimeter_F64) {
  std::vector<lm2_v2_f64> vertices = {
      { 0.0,  0.0},
      {10.0,  0.0},
      {10.0, 10.0},
      { 0.0, 10.0}
  };
  lm2_polygon_f64 polygon = lm2_polygon_make_f64(vertices.data(), vertices.size());
  double perimeter = lm2_polygon_perimeter_f64(polygon);

  EXPECT_DOUBLE_EQ(perimeter, 40.0);  // 4 * 10
}

// =============================================================================
// Perimeter Tests (f32)
// =============================================================================

TEST_F(PolygonTest, Perimeter_F32) {
  std::vector<lm2_v2_f32> vertices = {
      { 0.0f,  0.0f},
      {10.0f,  0.0f},
      {10.0f, 10.0f},
      { 0.0f, 10.0f}
  };
  lm2_polygon_f32 polygon = lm2_polygon_make_f32(vertices.data(), vertices.size());
  float perimeter = lm2_polygon_perimeter_f32(polygon);

  EXPECT_FLOAT_EQ(perimeter, 40.0f);
}

// =============================================================================
// Point Containment Tests (f64)
// =============================================================================

TEST_F(PolygonTest, ContainsPoint_Inside_F64) {
  std::vector<lm2_v2_f64> vertices = {
      { 0.0,  0.0},
      {10.0,  0.0},
      {10.0, 10.0},
      { 0.0, 10.0}
  };
  lm2_polygon_f64 polygon = lm2_polygon_make_f64(vertices.data(), vertices.size());
  lm2_v2_f64 point = lm2_v2_make_f64(5.0, 5.0);

  EXPECT_TRUE(lm2_polygon_contains_point_f64(polygon, point));
}

TEST_F(PolygonTest, ContainsPoint_Outside_F64) {
  std::vector<lm2_v2_f64> vertices = {
      { 0.0,  0.0},
      {10.0,  0.0},
      {10.0, 10.0},
      { 0.0, 10.0}
  };
  lm2_polygon_f64 polygon = lm2_polygon_make_f64(vertices.data(), vertices.size());
  lm2_v2_f64 point = lm2_v2_make_f64(15.0, 5.0);

  EXPECT_FALSE(lm2_polygon_contains_point_f64(polygon, point));
}

TEST_F(PolygonTest, ContainsPoint_OnEdge_F64) {
  std::vector<lm2_v2_f64> vertices = {
      { 0.0,  0.0},
      {10.0,  0.0},
      {10.0, 10.0},
      { 0.0, 10.0}
  };
  lm2_polygon_f64 polygon = lm2_polygon_make_f64(vertices.data(), vertices.size());
  lm2_v2_f64 point = lm2_v2_make_f64(5.0, 0.0);

  EXPECT_TRUE(lm2_polygon_contains_point_f64(polygon, point));
}

// =============================================================================
// Point Containment Tests (f32)
// =============================================================================

TEST_F(PolygonTest, ContainsPoint_Inside_F32) {
  std::vector<lm2_v2_f32> vertices = {
      { 0.0f,  0.0f},
      {10.0f,  0.0f},
      {10.0f, 10.0f},
      { 0.0f, 10.0f}
  };
  lm2_polygon_f32 polygon = lm2_polygon_make_f32(vertices.data(), vertices.size());
  lm2_v2_f32 point = lm2_v2_make_f32(5.0f, 5.0f);

  EXPECT_TRUE(lm2_polygon_contains_point_f32(polygon, point));
}

TEST_F(PolygonTest, ContainsPoint_Outside_F32) {
  std::vector<lm2_v2_f32> vertices = {
      { 0.0f,  0.0f},
      {10.0f,  0.0f},
      {10.0f, 10.0f},
      { 0.0f, 10.0f}
  };
  lm2_polygon_f32 polygon = lm2_polygon_make_f32(vertices.data(), vertices.size());
  lm2_v2_f32 point = lm2_v2_make_f32(15.0f, 5.0f);

  EXPECT_FALSE(lm2_polygon_contains_point_f32(polygon, point));
}
