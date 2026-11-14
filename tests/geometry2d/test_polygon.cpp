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
#include <limits>
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

TEST_F(PolygonTest, EarClippingSupportsClockwiseConcavePolygon_F64) {
  lm2_v2_f64 vertices[] = {
      {0.0, 4.0},
      {2.0, 2.0},
      {4.0, 4.0},
      {4.0, 0.0},
      {0.0, 0.0}
  };
  size_t guarded_indices[11] = {999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 999};
  const size_t count = lm2_polygon_triangulate_ear_clipping_f64(
      lm2_polygon_make_f64(vertices, 5), guarded_indices + 1);

  ASSERT_EQ(count, 3);
  EXPECT_EQ(guarded_indices[0], 999);
  EXPECT_EQ(guarded_indices[10], 999);
  double area = 0.0;
  for (size_t i = 0; i < count; ++i) {
    const size_t a = guarded_indices[1 + i * 3];
    const size_t b = guarded_indices[2 + i * 3];
    const size_t c = guarded_indices[3 + i * 3];
    ASSERT_LT(a, 5);
    ASSERT_LT(b, 5);
    ASSERT_LT(c, 5);
    const double cross = (vertices[b].x - vertices[a].x) * (vertices[c].y - vertices[a].y) -
                         (vertices[b].y - vertices[a].y) * (vertices[c].x - vertices[a].x);
    EXPECT_LT(cross, 0.0);
    area += std::abs(cross) * 0.5;
  }
  EXPECT_NEAR(area, 12.0, EPSILON_F64);
}

TEST_F(PolygonTest, EarClippingSupportsClockwiseConcavePolygon_F32) {
  lm2_v2_f32 vertices[] = {
      {0.0f, 4.0f},
      {2.0f, 2.0f},
      {4.0f, 4.0f},
      {4.0f, 0.0f},
      {0.0f, 0.0f}
  };
  size_t guarded_indices[11] = {999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 999};
  const size_t count = lm2_polygon_triangulate_ear_clipping_f32(
      lm2_polygon_make_f32(vertices, 5), guarded_indices + 1);

  ASSERT_EQ(count, 3);
  EXPECT_EQ(guarded_indices[0], 999);
  EXPECT_EQ(guarded_indices[10], 999);
  float area = 0.0f;
  for (size_t i = 0; i < count; ++i) {
    const size_t a = guarded_indices[1 + i * 3];
    const size_t b = guarded_indices[2 + i * 3];
    const size_t c = guarded_indices[3 + i * 3];
    ASSERT_LT(a, 5);
    ASSERT_LT(b, 5);
    ASSERT_LT(c, 5);
    const float cross = (vertices[b].x - vertices[a].x) * (vertices[c].y - vertices[a].y) -
                        (vertices[b].y - vertices[a].y) * (vertices[c].x - vertices[a].x);
    EXPECT_LT(cross, 0.0f);
    area += std::abs(cross) * 0.5f;
  }
  EXPECT_NEAR(area, 12.0f, EPSILON_F32);
}

TEST_F(PolygonTest, SplitHexagonIntoTrianglesPreservesArea_F64) {
  lm2_v2_f64 vertices[] = {
      { 0, 0},
      { 2, 0},
      { 3, 1},
      { 2, 2},
      { 0, 2},
      {-1, 1}
  };
  lm2_polygon_f64 pieces[4] = {};
  lm2_v2_f64 guarded[14] = {};
  guarded[0] = {99, 99};
  guarded[13] = {99, 99};
  size_t count = lm2_polygon_split_by_max_vertices_f64(
      lm2_polygon_make_f64(vertices, 6), pieces, guarded + 1, 3);
  ASSERT_EQ(count, 4);
  EXPECT_DOUBLE_EQ(guarded[0].x, 99);
  EXPECT_DOUBLE_EQ(guarded[13].x, 99);
  double area = 0.0;
  for (size_t i = 0; i < count; ++i) {
    ASSERT_EQ(pieces[i].vertex_count, 3);
    const lm2_v2_f64* p = pieces[i].vertices;
    const double cross = (p[1].x - p[0].x) * (p[2].y - p[0].y) -
                         (p[1].y - p[0].y) * (p[2].x - p[0].x);
    EXPECT_GT(cross, 0.0);
    area += cross * 0.5;
  }
  EXPECT_NEAR(area, 6.0, EPSILON_F64);
}

TEST_F(PolygonTest, SplitHexagonIntoTrianglesPreservesArea_F32) {
  lm2_v2_f32 vertices[] = {
      { 0, 0},
      { 2, 0},
      { 3, 1},
      { 2, 2},
      { 0, 2},
      {-1, 1}
  };
  lm2_polygon_f32 pieces[4] = {};
  lm2_v2_f32 guarded[14] = {};
  guarded[0] = {99, 99};
  guarded[13] = {99, 99};
  size_t count = lm2_polygon_split_by_max_vertices_f32(
      lm2_polygon_make_f32(vertices, 6), pieces, guarded + 1, 3);
  ASSERT_EQ(count, 4);
  EXPECT_FLOAT_EQ(guarded[0].x, 99);
  EXPECT_FLOAT_EQ(guarded[13].x, 99);
  float area = 0.0f;
  for (size_t i = 0; i < count; ++i) {
    ASSERT_EQ(pieces[i].vertex_count, 3);
    const lm2_v2_f32* p = pieces[i].vertices;
    const float cross = (p[1].x - p[0].x) * (p[2].y - p[0].y) -
                        (p[1].y - p[0].y) * (p[2].x - p[0].x);
    EXPECT_GT(cross, 0.0f);
    area += cross * 0.5f;
  }
  EXPECT_NEAR(area, 6.0f, EPSILON_F32);
}

TEST_F(PolygonTest, SplitConcavePolygonIntoTrianglesPreservesArea_F64) {
  lm2_v2_f64 vertices[] = {
      {0, 0},
      {4, 0},
      {4, 4},
      {2, 2},
      {0, 4}
  };
  lm2_polygon_f64 pieces[3] = {};
  lm2_v2_f64 guarded[11] = {};
  guarded[0] = {99, 99};
  guarded[10] = {99, 99};
  size_t count = lm2_polygon_split_by_max_vertices_f64(
      lm2_polygon_make_f64(vertices, 5), pieces, guarded + 1, 3);
  ASSERT_EQ(count, 3);
  EXPECT_DOUBLE_EQ(guarded[0].x, 99);
  EXPECT_DOUBLE_EQ(guarded[10].x, 99);
  double area = 0.0;
  for (size_t i = 0; i < count; ++i) {
    ASSERT_EQ(pieces[i].vertex_count, 3);
    const lm2_v2_f64* p = pieces[i].vertices;
    const double cross = (p[1].x - p[0].x) * (p[2].y - p[0].y) -
                         (p[1].y - p[0].y) * (p[2].x - p[0].x);
    EXPECT_GT(cross, 0.0);
    area += cross * 0.5;
  }
  EXPECT_NEAR(area, 12.0, EPSILON_F64);
}

TEST_F(PolygonTest, SplitConcavePolygonIntoTrianglesPreservesArea_F32) {
  lm2_v2_f32 vertices[] = {
      {0, 4},
      {2, 2},
      {4, 4},
      {4, 0},
      {0, 0}
  };
  lm2_polygon_f32 pieces[3] = {};
  lm2_v2_f32 guarded[11] = {};
  guarded[0] = {99, 99};
  guarded[10] = {99, 99};
  size_t count = lm2_polygon_split_by_max_vertices_f32(
      lm2_polygon_make_f32(vertices, 5), pieces, guarded + 1, 4);
  ASSERT_EQ(count, 3);
  EXPECT_FLOAT_EQ(guarded[0].x, 99);
  EXPECT_FLOAT_EQ(guarded[10].x, 99);
  float area = 0.0f;
  for (size_t i = 0; i < count; ++i) {
    ASSERT_EQ(pieces[i].vertex_count, 3);
    const lm2_v2_f32* p = pieces[i].vertices;
    const float cross = (p[1].x - p[0].x) * (p[2].y - p[0].y) -
                        (p[1].y - p[0].y) * (p[2].x - p[0].x);
    EXPECT_LT(cross, 0.0f);
    area += -cross * 0.5f;
  }
  EXPECT_NEAR(area, 12.0f, EPSILON_F32);
}

TEST_F(PolygonTest, TriangulationAndSplitRejectOverflowingVertexCount) {
  lm2_v2_f64 vertex64 = {0, 0};
  lm2_v2_f32 vertex32 = {0, 0};
  lm2_polygon_f64 polygon64 = {&vertex64, std::numeric_limits<size_t>::max()};
  lm2_polygon_f32 polygon32 = {&vertex32, std::numeric_limits<size_t>::max()};
  size_t index = 123;
  lm2_polygon_f64 out64 = {nullptr, 123};
  lm2_polygon_f32 out32 = {nullptr, 123};

  EXPECT_EQ(lm2_polygon_triangulate_ear_clipping_f64(polygon64, &index), 0);
  EXPECT_EQ(lm2_polygon_triangulate_ear_clipping_f32(polygon32, &index), 0);
  EXPECT_EQ(lm2_polygon_split_by_max_vertices_f64(polygon64, &out64, &vertex64, 3), 0);
  EXPECT_EQ(lm2_polygon_split_by_max_vertices_f32(polygon32, &out32, &vertex32, 3), 0);
  EXPECT_EQ(index, 123);
  EXPECT_EQ(out64.vertex_count, 123);
  EXPECT_EQ(out32.vertex_count, 123);

  polygon64.vertex_count = std::numeric_limits<size_t>::max() / (3 * sizeof(lm2_v2_f64)) + 3;
  EXPECT_EQ(lm2_polygon_split_by_max_vertices_f64(polygon64, &out64, &vertex64, 3), 0);
  EXPECT_EQ(out64.vertex_count, 123);
}

TEST_F(PolygonTest, SplitCollinearBoundaryVerticesProducesNondegenerateTriangles_F64) {
  lm2_v2_f64 vertices[] = {
      {0, 0},
      {2, 0},
      {4, 0},
      {4, 3},
      {0, 3}
  };
  lm2_polygon_f64 pieces[3] = {};
  lm2_v2_f64 buffer[9] = {};
  size_t count = lm2_polygon_split_by_max_vertices_f64(
      lm2_polygon_make_f64(vertices, 5), pieces, buffer, 3);
  ASSERT_EQ(count, 3);
  double area = 0.0;
  for (size_t i = 0; i < count; ++i) {
    ASSERT_EQ(pieces[i].vertex_count, 3);
    const lm2_v2_f64* p = pieces[i].vertices;
    double cross = (p[1].x - p[0].x) * (p[2].y - p[0].y) -
                   (p[1].y - p[0].y) * (p[2].x - p[0].x);
    EXPECT_GT(cross, 0.0);
    area += cross * 0.5;
  }
  EXPECT_NEAR(area, 12.0, EPSILON_F64);
}

TEST_F(PolygonTest, SplitCollinearBoundaryVerticesProducesNondegenerateTriangles_F32) {
  lm2_v2_f32 vertices[] = {
      {0, 0},
      {2, 0},
      {4, 0},
      {4, 3},
      {0, 3}
  };
  lm2_polygon_f32 pieces[3] = {};
  lm2_v2_f32 buffer[9] = {};
  size_t count = lm2_polygon_split_by_max_vertices_f32(
      lm2_polygon_make_f32(vertices, 5), pieces, buffer, 3);
  ASSERT_EQ(count, 3);
  float area = 0.0f;
  for (size_t i = 0; i < count; ++i) {
    ASSERT_EQ(pieces[i].vertex_count, 3);
    const lm2_v2_f32* p = pieces[i].vertices;
    float cross = (p[1].x - p[0].x) * (p[2].y - p[0].y) -
                  (p[1].y - p[0].y) * (p[2].x - p[0].x);
    EXPECT_GT(cross, 0.0f);
    area += cross * 0.5f;
  }
  EXPECT_NEAR(area, 12.0f, EPSILON_F32);
}

TEST_F(PolygonTest, TriangulatesConcavePolygonWithCollinearBoundary_F64) {
  lm2_v2_f64 vertices[] = {
      {0, 0},
      {2, 0},
      {4, 0},
      {4, 4},
      {2, 2},
      {0, 4}
  };
  size_t indices[12] = {};
  size_t count = lm2_polygon_triangulate_ear_clipping_f64(lm2_polygon_make_f64(vertices, 6), indices);
  ASSERT_EQ(count, 4);
  double area = 0.0;
  for (size_t i = 0; i < count; ++i) {
    ASSERT_LT(indices[i * 3], 6);
    ASSERT_LT(indices[i * 3 + 1], 6);
    ASSERT_LT(indices[i * 3 + 2], 6);
    lm2_v2_f64 a = vertices[indices[i * 3]];
    lm2_v2_f64 b = vertices[indices[i * 3 + 1]];
    lm2_v2_f64 c = vertices[indices[i * 3 + 2]];
    double cross = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    EXPECT_GT(cross, 0.0);
    area += cross * 0.5;
  }
  EXPECT_NEAR(area, 12.0, EPSILON_F64);
}

TEST_F(PolygonTest, TriangulatesConcavePolygonWithCollinearBoundary_F32) {
  lm2_v2_f32 vertices[] = {
      {0, 4},
      {2, 2},
      {4, 4},
      {4, 0},
      {2, 0},
      {0, 0}
  };
  size_t indices[12] = {};
  size_t count = lm2_polygon_triangulate_ear_clipping_f32(lm2_polygon_make_f32(vertices, 6), indices);
  ASSERT_EQ(count, 4);
  float area = 0.0f;
  for (size_t i = 0; i < count; ++i) {
    ASSERT_LT(indices[i * 3], 6);
    ASSERT_LT(indices[i * 3 + 1], 6);
    ASSERT_LT(indices[i * 3 + 2], 6);
    lm2_v2_f32 a = vertices[indices[i * 3]];
    lm2_v2_f32 b = vertices[indices[i * 3 + 1]];
    lm2_v2_f32 c = vertices[indices[i * 3 + 2]];
    float cross = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    EXPECT_LT(cross, 0.0f);
    area += -cross * 0.5f;
  }
  EXPECT_NEAR(area, 12.0f, EPSILON_F32);
}

TEST_F(PolygonTest, SignedAreaIsIndependentOfLargeTranslation) {
  lm2_v2_f64 vertices64[] = {
      {    1e9,     1e9},
      {1e9 + 1,     1e9},
      {1e9 + 1, 1e9 + 1},
      {    1e9, 1e9 + 1}
  };
  lm2_v2_f32 vertices32[] = {
      {    1e5f,     1e5f},
      {1e5f + 1,     1e5f},
      {1e5f + 1, 1e5f + 1},
      {    1e5f, 1e5f + 1}
  };
  lm2_polygon_f64 p64 = lm2_polygon_make_f64(vertices64, 4);
  lm2_polygon_f32 p32 = lm2_polygon_make_f32(vertices32, 4);
  EXPECT_DOUBLE_EQ(lm2_polygon_signed_area_f64(p64), 1.0);
  EXPECT_FLOAT_EQ(lm2_polygon_signed_area_f32(p32), 1.0f);
  lm2_polygon_reverse_winding_f64(p64);
  lm2_polygon_reverse_winding_f32(p32);
  EXPECT_DOUBLE_EQ(lm2_polygon_signed_area_f64(p64), -1.0);
  EXPECT_FLOAT_EQ(lm2_polygon_signed_area_f32(p32), -1.0f);
}

TEST_F(PolygonTest, CentroidIsIndependentOfLargeTranslationAndWinding) {
  lm2_v2_f64 vertices64[] = {
      {    1e9,     1e9},
      {1e9 + 1,     1e9},
      {1e9 + 1, 1e9 + 1},
      {    1e9, 1e9 + 1}
  };
  lm2_v2_f32 vertices32[] = {
      {    1e5f,     1e5f},
      {1e5f + 1,     1e5f},
      {1e5f + 1, 1e5f + 1},
      {    1e5f, 1e5f + 1}
  };
  lm2_polygon_f64 p64 = lm2_polygon_make_f64(vertices64, 4);
  lm2_polygon_f32 p32 = lm2_polygon_make_f32(vertices32, 4);
  for (int winding = 0; winding < 2; ++winding) {
    lm2_v2_f64 c64 = lm2_polygon_centroid_f64(p64);
    lm2_v2_f32 c32 = lm2_polygon_centroid_f32(p32);
    EXPECT_DOUBLE_EQ(c64.x, 1e9 + 0.5);
    EXPECT_DOUBLE_EQ(c64.y, 1e9 + 0.5);
    EXPECT_FLOAT_EQ(c32.x, 1e5f + 0.5f);
    EXPECT_FLOAT_EQ(c32.y, 1e5f + 0.5f);
    lm2_polygon_reverse_winding_f64(p64);
    lm2_polygon_reverse_winding_f32(p32);
  }
}

TEST_F(PolygonTest, TriangulatesAndSplitsTranslatedConcavePolygons) {
  lm2_v2_f64 vertices64[] = {
      {    1e9,     1e9},
      {1e9 + 4,     1e9},
      {1e9 + 4, 1e9 + 4},
      {1e9 + 2, 1e9 + 2},
      {    1e9, 1e9 + 4}
  };
  lm2_v2_f32 vertices32[] = {
      {    1e5f,     1e5f},
      {1e5f + 4,     1e5f},
      {1e5f + 4, 1e5f + 4},
      {1e5f + 2, 1e5f + 2},
      {    1e5f, 1e5f + 4}
  };
  lm2_polygon_f64 p64 = lm2_polygon_make_f64(vertices64, 5);
  lm2_polygon_f32 p32 = lm2_polygon_make_f32(vertices32, 5);
  for (int winding = 0; winding < 2; ++winding) {
    size_t indices64[9] = {};
    size_t indices32[9] = {};
    lm2_polygon_f64 pieces64[3] = {};
    lm2_polygon_f32 pieces32[3] = {};
    lm2_v2_f64 buffer64[9] = {};
    lm2_v2_f32 buffer32[9] = {};
    ASSERT_EQ(lm2_polygon_triangulate_ear_clipping_f64(p64, indices64), 3);
    ASSERT_EQ(lm2_polygon_triangulate_ear_clipping_f32(p32, indices32), 3);
    ASSERT_EQ(lm2_polygon_split_by_max_vertices_f64(p64, pieces64, buffer64, 4), 3);
    ASSERT_EQ(lm2_polygon_split_by_max_vertices_f32(p32, pieces32, buffer32, 4), 3);
    double area64 = 0.0;
    float area32 = 0.0f;
    for (size_t i = 0; i < 3; ++i) {
      ASSERT_EQ(pieces64[i].vertex_count, 3);
      ASSERT_EQ(pieces32[i].vertex_count, 3);
      area64 += lm2_polygon_area_f64(pieces64[i]);
      area32 += lm2_polygon_area_f32(pieces32[i]);
    }
    EXPECT_DOUBLE_EQ(area64, 12.0);
    EXPECT_FLOAT_EQ(area32, 12.0f);
    lm2_polygon_reverse_winding_f64(p64);
    lm2_polygon_reverse_winding_f32(p32);
  }
}

TEST_F(PolygonTest, SplitCopiesInputThatAlreadyFits) {
  lm2_v2_f64 vertices64[] = {
      {0, 0},
      {3, 0},
      {0, 2}
  };
  lm2_v2_f32 vertices32[] = {
      {0, 0},
      {3, 0},
      {0, 2}
  };
  lm2_v2_f64 output64[3] = {};
  lm2_v2_f32 output32[3] = {};
  lm2_polygon_f64 out64 = {};
  lm2_polygon_f32 out32 = {};
  ASSERT_EQ(lm2_polygon_split_by_max_vertices_f64(lm2_polygon_make_f64(vertices64, 3), &out64, output64, 3), 1);
  ASSERT_EQ(lm2_polygon_split_by_max_vertices_f32(lm2_polygon_make_f32(vertices32, 3), &out32, output32, 3), 1);
  ASSERT_EQ(out64.vertices, output64);
  ASSERT_EQ(out32.vertices, output32);
  ASSERT_EQ(out64.vertex_count, 3);
  ASSERT_EQ(out32.vertex_count, 3);
  for (size_t i = 0; i < 3; ++i) {
    EXPECT_DOUBLE_EQ(output64[i].x, vertices64[i].x);
    EXPECT_DOUBLE_EQ(output64[i].y, vertices64[i].y);
    EXPECT_FLOAT_EQ(output32[i].x, vertices32[i].x);
    EXPECT_FLOAT_EQ(output32[i].y, vertices32[i].y);
  }
  output64[0].x = 7;
  output32[0].x = 7;
  EXPECT_DOUBLE_EQ(vertices64[0].x, 0);
  EXPECT_FLOAT_EQ(vertices32[0].x, 0);
}

TEST_F(PolygonTest, SplitDoesNotModifyOutputsWhenTriangulationIsIncomplete) {
  // This degenerate polygon cannot yield nonzero-area triangles.
  lm2_v2_f64 vertices64[] = {
      {0, 0},
      {1, 0},
      {2, 0},
      {3, 0}
  };
  lm2_v2_f32 vertices32[] = {
      {0, 0},
      {1, 0},
      {2, 0},
      {3, 0}
  };
  lm2_polygon_f64 out64[2] = {
      {nullptr, 123},
      {nullptr, 123}
  };
  lm2_polygon_f32 out32[2] = {
      {nullptr, 123},
      {nullptr, 123}
  };
  lm2_v2_f64 buffer64[6];
  lm2_v2_f32 buffer32[6];
  for (size_t i = 0; i < 6; ++i) {
    buffer64[i] = {99, 99};
    buffer32[i] = {99, 99};
  }
  EXPECT_EQ(lm2_polygon_split_by_max_vertices_f64(lm2_polygon_make_f64(vertices64, 4), out64, buffer64, 3), 0);
  EXPECT_EQ(lm2_polygon_split_by_max_vertices_f32(lm2_polygon_make_f32(vertices32, 4), out32, buffer32, 3), 0);
  for (size_t i = 0; i < 2; ++i) {
    EXPECT_EQ(out64[i].vertices, nullptr);
    EXPECT_EQ(out64[i].vertex_count, 123);
    EXPECT_EQ(out32[i].vertices, nullptr);
    EXPECT_EQ(out32[i].vertex_count, 123);
  }
  for (size_t i = 0; i < 6; ++i) {
    EXPECT_DOUBLE_EQ(buffer64[i].x, 99);
    EXPECT_DOUBLE_EQ(buffer64[i].y, 99);
    EXPECT_FLOAT_EQ(buffer32[i].x, 99);
    EXPECT_FLOAT_EQ(buffer32[i].y, 99);
  }
}
