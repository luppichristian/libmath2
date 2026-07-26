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

TEST_F(PolygonTest, IsCCW_DistinguishesWinding_F64) {
  lm2_v2_f64 ccw_vertices[] = {
      {0.0, 0.0},
      {2.0, 0.0},
      {0.0, 2.0}
  };
  lm2_v2_f64 cw_vertices[] = {
      {0.0, 0.0},
      {0.0, 2.0},
      {2.0, 0.0}
  };

  EXPECT_TRUE(lm2_polygon_is_ccw_f64(lm2_polygon_make_f64(ccw_vertices, 3)));
  EXPECT_FALSE(lm2_polygon_is_ccw_f64(lm2_polygon_make_f64(cw_vertices, 3)));
}

TEST_F(PolygonTest, ConvexAndSimpleClassification_F64) {
  lm2_v2_f64 square[] = {
      {0.0, 0.0},
      {4.0, 0.0},
      {4.0, 4.0},
      {0.0, 4.0}
  };
  lm2_v2_f64 concave[] = {
      {0.0, 0.0},
      {4.0, 0.0},
      {2.0, 1.0},
      {4.0, 4.0},
      {0.0, 4.0}
  };
  lm2_v2_f64 bow_tie[] = {
      {0.0, 0.0},
      {4.0, 4.0},
      {0.0, 4.0},
      {4.0, 0.0}
  };

  EXPECT_TRUE(lm2_polygon_is_convex_f64(lm2_polygon_make_f64(square, 4)));
  EXPECT_TRUE(lm2_polygon_is_simple_f64(lm2_polygon_make_f64(square, 4)));
  EXPECT_FALSE(lm2_polygon_is_convex_f64(lm2_polygon_make_f64(concave, 5)));
  EXPECT_TRUE(lm2_polygon_is_simple_f64(lm2_polygon_make_f64(concave, 5)));
  EXPECT_FALSE(lm2_polygon_is_simple_f64(lm2_polygon_make_f64(bow_tie, 4)));
}

TEST_F(PolygonTest, TransformationsPreserveExpectedGeometry_F64) {
  lm2_v2_f64 vertices[] = {
      {0.0, 0.0},
      {2.0, 0.0},
      {0.0, 2.0}
  };
  lm2_polygon_f64 polygon = lm2_polygon_make_f64(vertices, 3);

  lm2_polygon_translate_f64(polygon, lm2_v2_make_f64(1.0, -1.0));
  lm2_polygon_scale_f64(polygon, lm2_v2_make_f64(1.0, -1.0), 2.0);
  lm2_polygon_rotate_f64(polygon, lm2_v2_make_f64(1.0, -1.0), LM2_PI_F64 * 0.5);

  EXPECT_NEAR(vertices[0].x, 1.0, EPSILON_F64);
  EXPECT_NEAR(vertices[0].y, -1.0, EPSILON_F64);
  EXPECT_NEAR(vertices[1].x, 1.0, EPSILON_F64);
  EXPECT_NEAR(vertices[1].y, 3.0, EPSILON_F64);
  EXPECT_NEAR(vertices[2].x, -3.0, EPSILON_F64);
  EXPECT_NEAR(vertices[2].y, -1.0, EPSILON_F64);
  EXPECT_NEAR(lm2_polygon_area_f64(polygon), 8.0, EPSILON_F64);
}

TEST_F(PolygonTest, InsertThenRemoveVertexRestoresSequence_F64) {
  lm2_v2_f64 vertices[5] = {
      {0.0, 0.0},
      {2.0, 0.0},
      {0.0, 2.0}
  };
  size_t count = 3;
  lm2_polygon_insert_vertex_f64(vertices, &count, 1, lm2_v2_make_f64(1.0, 0.0));
  ASSERT_EQ(count, 4);
  EXPECT_DOUBLE_EQ(vertices[1].x, 1.0);
  EXPECT_DOUBLE_EQ(vertices[2].x, 2.0);

  lm2_polygon_remove_vertex_f64(vertices, &count, 1);
  ASSERT_EQ(count, 3);
  EXPECT_DOUBLE_EQ(vertices[0].x, 0.0);
  EXPECT_DOUBLE_EQ(vertices[1].x, 2.0);
  EXPECT_DOUBLE_EQ(vertices[2].y, 2.0);
}

TEST_F(PolygonTest, EarClippingTriangulatesConcavePolygonWithEqualArea_F64) {
  lm2_v2_f64 vertices[] = {
      {0.0, 0.0},
      {4.0, 0.0},
      {4.0, 4.0},
      {2.0, 2.0},
      {0.0, 4.0}
  };
  lm2_polygon_f64 polygon = lm2_polygon_make_f64(vertices, 5);
  size_t indices[9] = {};

  size_t count = lm2_polygon_triangulate_ear_clipping_f64(polygon, indices);
  ASSERT_EQ(count, 3);
  double triangle_area = 0.0;
  for (size_t i = 0; i < count; ++i) {
    ASSERT_LT(indices[i * 3], 5);
    ASSERT_LT(indices[i * 3 + 1], 5);
    ASSERT_LT(indices[i * 3 + 2], 5);
    lm2_triangle2_f64 triangle = {
        vertices[indices[i * 3]], vertices[indices[i * 3 + 1]], vertices[indices[i * 3 + 2]]};
    triangle_area += lm2_triangle2_area_f64(triangle);
  }
  EXPECT_NEAR(triangle_area, lm2_polygon_area_f64(polygon), EPSILON_F64);
}

TEST_F(PolygonTest, SplitConvexPolygonPreservesAreaAndVertexLimit_F64) {
  lm2_v2_f64 vertices[] = {
      { 0.0, 0.0},
      { 4.0, 0.0},
      { 5.0, 2.0},
      { 2.0, 5.0},
      {-1.0, 2.0}
  };
  lm2_polygon_f64 polygon = lm2_polygon_make_f64(vertices, 5);
  lm2_polygon_f64 pieces[3] = {};
  lm2_v2_f64 buffer[12] = {};

  size_t count = lm2_polygon_split_by_max_vertices_f64(polygon, pieces, buffer, 4);
  ASSERT_EQ(count, 2);
  double area = 0.0;
  for (size_t i = 0; i < count; ++i) {
    EXPECT_GE(pieces[i].vertex_count, 3);
    EXPECT_LE(pieces[i].vertex_count, 4);
    area += lm2_polygon_area_f64(pieces[i]);
  }
  EXPECT_NEAR(area, lm2_polygon_area_f64(polygon), EPSILON_F64);
}
