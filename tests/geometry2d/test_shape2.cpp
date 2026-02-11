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
#include "lm2/geometry2d/lm2_shape2.h"

// Test fixture for Shape2 tests
class Shape2Test : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Construction Tests - Circle (f64)
// =============================================================================

TEST_F(Shape2Test, FromCircle_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(5.0, 5.0, 3.0);
  lm2_shape2_f64 shape = lm2_shape2_from_circle_f64(&circle);

  EXPECT_EQ(shape.type, LM2_SHAPE2_CIRCLE);
  EXPECT_NE(shape.data, nullptr);
  EXPECT_EQ(lm2_shape2_get_type_f64(&shape), LM2_SHAPE2_CIRCLE);
}

// =============================================================================
// Construction Tests - Circle (f32)
// =============================================================================

TEST_F(Shape2Test, FromCircle_F32) {
  lm2_circle_f32 circle = lm2_circle_make_coords_f32(5.0f, 5.0f, 3.0f);
  lm2_shape2_f32 shape = lm2_shape2_from_circle_f32(&circle);

  EXPECT_EQ(shape.type, LM2_SHAPE2_CIRCLE);
  EXPECT_NE(shape.data, nullptr);
  EXPECT_EQ(lm2_shape2_get_type_f32(&shape), LM2_SHAPE2_CIRCLE);
}

// =============================================================================
// Construction Tests - Capsule (f64)
// =============================================================================

TEST_F(Shape2Test, FromCapsule_F64) {
  lm2_capsule2_f64 capsule = lm2_capsule2_make_coords_f64(0.0, 0.0, 10.0, 0.0, 2.0);
  lm2_shape2_f64 shape = lm2_shape2_from_capsule_f64(&capsule);

  EXPECT_EQ(shape.type, LM2_SHAPE2_CAPSULE);
  EXPECT_NE(shape.data, nullptr);
  EXPECT_TRUE(lm2_shape2_is_type_f64(&shape, LM2_SHAPE2_CAPSULE));
}

// =============================================================================
// Construction Tests - Capsule (f32)
// =============================================================================

TEST_F(Shape2Test, FromCapsule_F32) {
  lm2_capsule2_f32 capsule = lm2_capsule2_make_coords_f32(0.0f, 0.0f, 10.0f, 0.0f, 2.0f);
  lm2_shape2_f32 shape = lm2_shape2_from_capsule_f32(&capsule);

  EXPECT_EQ(shape.type, LM2_SHAPE2_CAPSULE);
  EXPECT_NE(shape.data, nullptr);
  EXPECT_TRUE(lm2_shape2_is_type_f32(&shape, LM2_SHAPE2_CAPSULE));
}

// =============================================================================
// Construction Tests - AABB2 (f64)
// =============================================================================

TEST_F(Shape2Test, FromAABB2_F64) {
  lm2_aabb2_f64 aabb = lm2_r2_from_position_size_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(10.0, 10.0));
  lm2_shape2_f64 shape = lm2_shape2_from_aabb2_f64(&aabb);

  EXPECT_EQ(shape.type, LM2_SHAPE2_AABB2);
  EXPECT_NE(shape.data, nullptr);
  EXPECT_TRUE(lm2_shape2_is_type_f64(&shape, LM2_SHAPE2_AABB2));
}

// =============================================================================
// Construction Tests - AABB2 (f32)
// =============================================================================

TEST_F(Shape2Test, FromAABB2_F32) {
  lm2_aabb2_f32 aabb = lm2_r2_from_position_size_f32(lm2_v2_make_f32(0.0f, 0.0f), lm2_v2_make_f32(10.0f, 10.0f));
  lm2_shape2_f32 shape = lm2_shape2_from_aabb2_f32(&aabb);

  EXPECT_EQ(shape.type, LM2_SHAPE2_AABB2);
  EXPECT_NE(shape.data, nullptr);
  EXPECT_TRUE(lm2_shape2_is_type_f32(&shape, LM2_SHAPE2_AABB2));
}

// =============================================================================
// Construction Tests - Triangle (f64)
// =============================================================================

TEST_F(Shape2Test, FromTriangle_F64) {
  lm2_triangle2_f64 triangle;
  lm2_triangle2_make_coords_f64(triangle, 0.0, 0.0, 10.0, 0.0, 5.0, 10.0);
  lm2_shape2_f64 shape = lm2_shape2_from_triangle_f64(&triangle);

  EXPECT_EQ(shape.type, LM2_SHAPE2_TRIANGLE);
  EXPECT_NE(shape.data, nullptr);
  EXPECT_TRUE(lm2_shape2_is_type_f64(&shape, LM2_SHAPE2_TRIANGLE));
}

// =============================================================================
// Construction Tests - Triangle (f32)
// =============================================================================

TEST_F(Shape2Test, FromTriangle_F32) {
  lm2_triangle2_f32 triangle;
  lm2_triangle2_make_coords_f32(triangle, 0.0f, 0.0f, 10.0f, 0.0f, 5.0f, 10.0f);
  lm2_shape2_f32 shape = lm2_shape2_from_triangle_f32(&triangle);

  EXPECT_EQ(shape.type, LM2_SHAPE2_TRIANGLE);
  EXPECT_NE(shape.data, nullptr);
  EXPECT_TRUE(lm2_shape2_is_type_f32(&shape, LM2_SHAPE2_TRIANGLE));
}

// =============================================================================
// Construction Tests - Polygon (f64)
// =============================================================================

TEST_F(Shape2Test, FromPolygon_F64) {
  std::vector<lm2_v2_f64> vertices = {
      { 0.0,  0.0},
      {10.0,  0.0},
      {10.0, 10.0},
      { 0.0, 10.0}
  };
  lm2_polygon_f64 polygon = lm2_polygon_make_f64(vertices.data(), vertices.size());
  lm2_shape2_f64 shape = lm2_shape2_from_polygon_f64(&polygon);

  EXPECT_EQ(shape.type, LM2_SHAPE2_POLYGON);
  EXPECT_NE(shape.data, nullptr);
  EXPECT_TRUE(lm2_shape2_is_type_f64(&shape, LM2_SHAPE2_POLYGON));
}

// =============================================================================
// Construction Tests - Polygon (f32)
// =============================================================================

TEST_F(Shape2Test, FromPolygon_F32) {
  std::vector<lm2_v2_f32> vertices = {
      { 0.0f,  0.0f},
      {10.0f,  0.0f},
      {10.0f, 10.0f},
      { 0.0f, 10.0f}
  };
  lm2_polygon_f32 polygon = lm2_polygon_make_f32(vertices.data(), vertices.size());
  lm2_shape2_f32 shape = lm2_shape2_from_polygon_f32(&polygon);

  EXPECT_EQ(shape.type, LM2_SHAPE2_POLYGON);
  EXPECT_NE(shape.data, nullptr);
  EXPECT_TRUE(lm2_shape2_is_type_f32(&shape, LM2_SHAPE2_POLYGON));
}

// =============================================================================
// Construction Tests - Edge (f64)
// =============================================================================

TEST_F(Shape2Test, FromEdge_F64) {
  lm2_edge2_f64 edge = lm2_edge2_make_coords_f64(0.0, 0.0, 10.0, 10.0);
  lm2_shape2_f64 shape = lm2_shape2_from_edge_f64(&edge);

  EXPECT_EQ(shape.type, LM2_SHAPE2_EDGE);
  EXPECT_NE(shape.data, nullptr);
  EXPECT_TRUE(lm2_shape2_is_type_f64(&shape, LM2_SHAPE2_EDGE));
}

// =============================================================================
// Construction Tests - Edge (f32)
// =============================================================================

TEST_F(Shape2Test, FromEdge_F32) {
  lm2_edge2_f32 edge = lm2_edge2_make_coords_f32(0.0f, 0.0f, 10.0f, 10.0f);
  lm2_shape2_f32 shape = lm2_shape2_from_edge_f32(&edge);

  EXPECT_EQ(shape.type, LM2_SHAPE2_EDGE);
  EXPECT_NE(shape.data, nullptr);
  EXPECT_TRUE(lm2_shape2_is_type_f32(&shape, LM2_SHAPE2_EDGE));
}

// =============================================================================
// Extraction Tests - Circle (f64)
// =============================================================================

TEST_F(Shape2Test, AsCircle_ValidCircle_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(5.0, 5.0, 3.0);
  lm2_shape2_f64 shape = lm2_shape2_from_circle_f64(&circle);

  lm2_circle_f64* extracted = lm2_shape2_as_circle_f64(&shape);
  EXPECT_NE(extracted, nullptr);
  if (extracted) {
    EXPECT_DOUBLE_EQ(extracted->center.x, 5.0);
    EXPECT_DOUBLE_EQ(extracted->center.y, 5.0);
    EXPECT_DOUBLE_EQ(extracted->radius, 3.0);
  }
}

TEST_F(Shape2Test, AsCircle_WrongType_F64) {
  lm2_capsule2_f64 capsule = lm2_capsule2_make_coords_f64(0.0, 0.0, 10.0, 0.0, 2.0);
  lm2_shape2_f64 shape = lm2_shape2_from_capsule_f64(&capsule);

  lm2_circle_f64* extracted = lm2_shape2_as_circle_f64(&shape);
  EXPECT_EQ(extracted, nullptr);
}

// =============================================================================
// Extraction Tests - Circle (f32)
// =============================================================================

TEST_F(Shape2Test, AsCircle_ValidCircle_F32) {
  lm2_circle_f32 circle = lm2_circle_make_coords_f32(5.0f, 5.0f, 3.0f);
  lm2_shape2_f32 shape = lm2_shape2_from_circle_f32(&circle);

  lm2_circle_f32* extracted = lm2_shape2_as_circle_f32(&shape);
  EXPECT_NE(extracted, nullptr);
  if (extracted) {
    EXPECT_FLOAT_EQ(extracted->center.x, 5.0f);
    EXPECT_FLOAT_EQ(extracted->radius, 3.0f);
  }
}

// =============================================================================
// Extraction Tests - Capsule (f64)
// =============================================================================

TEST_F(Shape2Test, AsCapsule_ValidCapsule_F64) {
  lm2_capsule2_f64 capsule = lm2_capsule2_make_coords_f64(0.0, 0.0, 10.0, 0.0, 2.0);
  lm2_shape2_f64 shape = lm2_shape2_from_capsule_f64(&capsule);

  lm2_capsule2_f64* extracted = lm2_shape2_as_capsule_f64(&shape);
  EXPECT_NE(extracted, nullptr);
  if (extracted) {
    EXPECT_DOUBLE_EQ(extracted->start.x, 0.0);
    EXPECT_DOUBLE_EQ(extracted->end.x, 10.0);
    EXPECT_DOUBLE_EQ(extracted->radius, 2.0);
  }
}

TEST_F(Shape2Test, AsCapsule_WrongType_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(5.0, 5.0, 3.0);
  lm2_shape2_f64 shape = lm2_shape2_from_circle_f64(&circle);

  lm2_capsule2_f64* extracted = lm2_shape2_as_capsule_f64(&shape);
  EXPECT_EQ(extracted, nullptr);
}

// =============================================================================
// Extraction Tests - Capsule (f32)
// =============================================================================

TEST_F(Shape2Test, AsCapsule_ValidCapsule_F32) {
  lm2_capsule2_f32 capsule = lm2_capsule2_make_coords_f32(0.0f, 0.0f, 10.0f, 0.0f, 2.0f);
  lm2_shape2_f32 shape = lm2_shape2_from_capsule_f32(&capsule);

  lm2_capsule2_f32* extracted = lm2_shape2_as_capsule_f32(&shape);
  EXPECT_NE(extracted, nullptr);
  if (extracted) {
    EXPECT_FLOAT_EQ(extracted->radius, 2.0f);
  }
}

// =============================================================================
// Type Query Tests (f64)
// =============================================================================

TEST_F(Shape2Test, IsType_Circle_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(5.0, 5.0, 3.0);
  lm2_shape2_f64 shape = lm2_shape2_from_circle_f64(&circle);

  EXPECT_TRUE(lm2_shape2_is_type_f64(&shape, LM2_SHAPE2_CIRCLE));
  EXPECT_FALSE(lm2_shape2_is_type_f64(&shape, LM2_SHAPE2_CAPSULE));
  EXPECT_FALSE(lm2_shape2_is_type_f64(&shape, LM2_SHAPE2_AABB2));
  EXPECT_FALSE(lm2_shape2_is_type_f64(&shape, LM2_SHAPE2_TRIANGLE));
  EXPECT_FALSE(lm2_shape2_is_type_f64(&shape, LM2_SHAPE2_POLYGON));
  EXPECT_FALSE(lm2_shape2_is_type_f64(&shape, LM2_SHAPE2_EDGE));
}

TEST_F(Shape2Test, IsType_Capsule_F64) {
  lm2_capsule2_f64 capsule = lm2_capsule2_make_coords_f64(0.0, 0.0, 10.0, 0.0, 2.0);
  lm2_shape2_f64 shape = lm2_shape2_from_capsule_f64(&capsule);

  EXPECT_FALSE(lm2_shape2_is_type_f64(&shape, LM2_SHAPE2_CIRCLE));
  EXPECT_TRUE(lm2_shape2_is_type_f64(&shape, LM2_SHAPE2_CAPSULE));
}

// =============================================================================
// Type Query Tests (f32)
// =============================================================================

TEST_F(Shape2Test, IsType_Circle_F32) {
  lm2_circle_f32 circle = lm2_circle_make_coords_f32(5.0f, 5.0f, 3.0f);
  lm2_shape2_f32 shape = lm2_shape2_from_circle_f32(&circle);

  EXPECT_TRUE(lm2_shape2_is_type_f32(&shape, LM2_SHAPE2_CIRCLE));
  EXPECT_FALSE(lm2_shape2_is_type_f32(&shape, LM2_SHAPE2_CAPSULE));
}

TEST_F(Shape2Test, GetType_AllTypes_F64) {
  lm2_circle_f64 circle = lm2_circle_make_coords_f64(5.0, 5.0, 3.0);
  lm2_shape2_f64 shape_circle = lm2_shape2_from_circle_f64(&circle);
  EXPECT_EQ(lm2_shape2_get_type_f64(&shape_circle), LM2_SHAPE2_CIRCLE);

  lm2_capsule2_f64 capsule = lm2_capsule2_make_coords_f64(0.0, 0.0, 10.0, 0.0, 2.0);
  lm2_shape2_f64 shape_capsule = lm2_shape2_from_capsule_f64(&capsule);
  EXPECT_EQ(lm2_shape2_get_type_f64(&shape_capsule), LM2_SHAPE2_CAPSULE);

  lm2_edge2_f64 edge = lm2_edge2_make_coords_f64(0.0, 0.0, 10.0, 10.0);
  lm2_shape2_f64 shape_edge = lm2_shape2_from_edge_f64(&edge);
  EXPECT_EQ(lm2_shape2_get_type_f64(&shape_edge), LM2_SHAPE2_EDGE);
}

TEST_F(Shape2Test, GetType_AllTypes_F32) {
  lm2_circle_f32 circle = lm2_circle_make_coords_f32(5.0f, 5.0f, 3.0f);
  lm2_shape2_f32 shape_circle = lm2_shape2_from_circle_f32(&circle);
  EXPECT_EQ(lm2_shape2_get_type_f32(&shape_circle), LM2_SHAPE2_CIRCLE);

  lm2_capsule2_f32 capsule = lm2_capsule2_make_coords_f32(0.0f, 0.0f, 10.0f, 0.0f, 2.0f);
  lm2_shape2_f32 shape_capsule = lm2_shape2_from_capsule_f32(&capsule);
  EXPECT_EQ(lm2_shape2_get_type_f32(&shape_capsule), LM2_SHAPE2_CAPSULE);
}
