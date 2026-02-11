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
#include "lm2/geometry3d/lm2_shape3.h"

// Test fixture for Shape3 tests
class Shape3Test : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Shape Creation - Sphere (f64)
// =============================================================================

TEST_F(Shape3Test, FromSphere_F64) {
  lm2_sphere_f64 sphere = lm2_sphere_make_coords_f64(1.0, 2.0, 3.0, 5.0);
  lm2_shape3_f64 shape = lm2_shape3_from_sphere_f64(&sphere);

  EXPECT_EQ(shape.type, LM2_SHAPE3_SPHERE);
  EXPECT_NE(shape.data, nullptr);
}

TEST_F(Shape3Test, AsSphere_F64) {
  lm2_sphere_f64 sphere = lm2_sphere_make_coords_f64(1.0, 2.0, 3.0, 5.0);
  lm2_shape3_f64 shape = lm2_shape3_from_sphere_f64(&sphere);

  lm2_sphere_f64* extracted = lm2_shape3_as_sphere_f64(&shape);

  EXPECT_NE(extracted, nullptr);
  EXPECT_DOUBLE_EQ(extracted->center.x, 1.0);
  EXPECT_DOUBLE_EQ(extracted->center.y, 2.0);
  EXPECT_DOUBLE_EQ(extracted->center.z, 3.0);
  EXPECT_DOUBLE_EQ(extracted->radius, 5.0);
}

TEST_F(Shape3Test, AsWrongType_Sphere_F64) {
  lm2_sphere_f64 sphere = lm2_sphere_make_coords_f64(1.0, 2.0, 3.0, 5.0);
  lm2_shape3_f64 shape = lm2_shape3_from_sphere_f64(&sphere);

  // Try to extract as capsule (wrong type)
  lm2_capsule3_f64* capsule = lm2_shape3_as_capsule_f64(&shape);
  EXPECT_EQ(capsule, nullptr);
}

// =============================================================================
// Shape Creation - Sphere (f32)
// =============================================================================

TEST_F(Shape3Test, FromSphere_F32) {
  lm2_sphere_f32 sphere = lm2_sphere_make_coords_f32(1.0f, 2.0f, 3.0f, 5.0f);
  lm2_shape3_f32 shape = lm2_shape3_from_sphere_f32(&sphere);

  EXPECT_EQ(shape.type, LM2_SHAPE3_SPHERE);
}

TEST_F(Shape3Test, AsSphere_F32) {
  lm2_sphere_f32 sphere = lm2_sphere_make_coords_f32(1.0f, 2.0f, 3.0f, 5.0f);
  lm2_shape3_f32 shape = lm2_shape3_from_sphere_f32(&sphere);

  lm2_sphere_f32* extracted = lm2_shape3_as_sphere_f32(&shape);

  EXPECT_NE(extracted, nullptr);
  EXPECT_FLOAT_EQ(extracted->radius, 5.0f);
}

// =============================================================================
// Shape Creation - Capsule (f64)
// =============================================================================

TEST_F(Shape3Test, FromCapsule_F64) {
  lm2_capsule3_f64 capsule = lm2_capsule3_make_coords_f64(0.0, 0.0, 0.0, 10.0, 0.0, 0.0, 2.0);
  lm2_shape3_f64 shape = lm2_shape3_from_capsule_f64(&capsule);

  EXPECT_EQ(shape.type, LM2_SHAPE3_CAPSULE);
  EXPECT_NE(shape.data, nullptr);
}

TEST_F(Shape3Test, AsCapsule_F64) {
  lm2_capsule3_f64 capsule = lm2_capsule3_make_coords_f64(0.0, 0.0, 0.0, 10.0, 0.0, 0.0, 2.0);
  lm2_shape3_f64 shape = lm2_shape3_from_capsule_f64(&capsule);

  lm2_capsule3_f64* extracted = lm2_shape3_as_capsule_f64(&shape);

  EXPECT_NE(extracted, nullptr);
  EXPECT_DOUBLE_EQ(extracted->start.x, 0.0);
  EXPECT_DOUBLE_EQ(extracted->end.x, 10.0);
  EXPECT_DOUBLE_EQ(extracted->radius, 2.0);
}

// =============================================================================
// Shape Creation - Capsule (f32)
// =============================================================================

TEST_F(Shape3Test, FromCapsule_F32) {
  lm2_capsule3_f32 capsule = lm2_capsule3_make_coords_f32(0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 2.0f);
  lm2_shape3_f32 shape = lm2_shape3_from_capsule_f32(&capsule);

  EXPECT_EQ(shape.type, LM2_SHAPE3_CAPSULE);
}

TEST_F(Shape3Test, AsCapsule_F32) {
  lm2_capsule3_f32 capsule = lm2_capsule3_make_coords_f32(0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 2.0f);
  lm2_shape3_f32 shape = lm2_shape3_from_capsule_f32(&capsule);

  lm2_capsule3_f32* extracted = lm2_shape3_as_capsule_f32(&shape);

  EXPECT_NE(extracted, nullptr);
  EXPECT_FLOAT_EQ(extracted->radius, 2.0f);
}

// =============================================================================
// Shape Creation - AABB3 (f64)
// =============================================================================

TEST_F(Shape3Test, FromAABB_F64) {
  lm2_aabb3_f64 aabb = lm2_aabb3_from_min_max_f64(
      lm2_v3_make_f64(0.0, 0.0, 0.0),
      lm2_v3_make_f64(10.0, 10.0, 10.0));
  lm2_shape3_f64 shape = lm2_shape3_from_aabb3_f64(&aabb);

  EXPECT_EQ(shape.type, LM2_SHAPE3_AABB3);
  EXPECT_NE(shape.data, nullptr);
}

TEST_F(Shape3Test, AsAABB_F64) {
  lm2_aabb3_f64 aabb = lm2_aabb3_from_min_max_f64(
      lm2_v3_make_f64(0.0, 0.0, 0.0),
      lm2_v3_make_f64(10.0, 10.0, 10.0));
  lm2_shape3_f64 shape = lm2_shape3_from_aabb3_f64(&aabb);

  lm2_aabb3_f64* extracted = lm2_shape3_as_aabb3_f64(&shape);

  EXPECT_NE(extracted, nullptr);
  EXPECT_DOUBLE_EQ(extracted->min.x, 0.0);
  EXPECT_DOUBLE_EQ(extracted->max.x, 10.0);
}

// =============================================================================
// Shape Creation - AABB3 (f32)
// =============================================================================

TEST_F(Shape3Test, FromAABB_F32) {
  lm2_aabb3_f32 aabb = lm2_aabb3_from_min_max_f32(
      lm2_v3_make_f32(0.0f, 0.0f, 0.0f),
      lm2_v3_make_f32(10.0f, 10.0f, 10.0f));
  lm2_shape3_f32 shape = lm2_shape3_from_aabb3_f32(&aabb);

  EXPECT_EQ(shape.type, LM2_SHAPE3_AABB3);
}

TEST_F(Shape3Test, AsAABB_F32) {
  lm2_aabb3_f32 aabb = lm2_aabb3_from_min_max_f32(
      lm2_v3_make_f32(0.0f, 0.0f, 0.0f),
      lm2_v3_make_f32(10.0f, 10.0f, 10.0f));
  lm2_shape3_f32 shape = lm2_shape3_from_aabb3_f32(&aabb);

  lm2_aabb3_f32* extracted = lm2_shape3_as_aabb3_f32(&shape);

  EXPECT_NE(extracted, nullptr);
  EXPECT_FLOAT_EQ(extracted->max.x, 10.0f);
}

// =============================================================================
// Shape Creation - Triangle (f64)
// =============================================================================

TEST_F(Shape3Test, FromTriangle_F64) {
  lm2_triangle3_f64 tri;
  lm2_triangle3_make_coords_f64(tri, 0.0, 0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 4.0, 0.0);

  lm2_shape3_f64 shape = lm2_shape3_from_triangle_f64(&tri);

  EXPECT_EQ(shape.type, LM2_SHAPE3_TRIANGLE);
  EXPECT_NE(shape.data, nullptr);
}

TEST_F(Shape3Test, AsTriangle_F64) {
  lm2_triangle3_f64 tri;
  lm2_triangle3_make_coords_f64(tri, 0.0, 0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 4.0, 0.0);

  lm2_shape3_f64 shape = lm2_shape3_from_triangle_f64(&tri);

  lm2_triangle3_f64* extracted = lm2_shape3_as_triangle_f64(&shape);

  EXPECT_NE(extracted, nullptr);
  EXPECT_DOUBLE_EQ((*extracted)[0].x, 0.0);
  EXPECT_DOUBLE_EQ((*extracted)[1].x, 3.0);
  EXPECT_DOUBLE_EQ((*extracted)[2].y, 4.0);
}

// =============================================================================
// Shape Creation - Triangle (f32)
// =============================================================================

TEST_F(Shape3Test, FromTriangle_F32) {
  lm2_triangle3_f32 tri;
  lm2_triangle3_make_coords_f32(tri, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 4.0f, 0.0f);

  lm2_shape3_f32 shape = lm2_shape3_from_triangle_f32(&tri);

  EXPECT_EQ(shape.type, LM2_SHAPE3_TRIANGLE);
}

TEST_F(Shape3Test, AsTriangle_F32) {
  lm2_triangle3_f32 tri;
  lm2_triangle3_make_coords_f32(tri, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 4.0f, 0.0f);

  lm2_shape3_f32 shape = lm2_shape3_from_triangle_f32(&tri);

  lm2_triangle3_f32* extracted = lm2_shape3_as_triangle_f32(&shape);

  EXPECT_NE(extracted, nullptr);
  EXPECT_FLOAT_EQ((*extracted)[1].x, 3.0f);
}

// =============================================================================
// Shape Creation - Edge (f64)
// =============================================================================

TEST_F(Shape3Test, FromEdge_F64) {
  lm2_edge3_f64 edge = lm2_edge3_make_coords_f64(0.0, 0.0, 0.0, 10.0, 0.0, 0.0);

  lm2_shape3_f64 shape = lm2_shape3_from_edge_f64(&edge);

  EXPECT_EQ(shape.type, LM2_SHAPE3_EDGE);
  EXPECT_NE(shape.data, nullptr);
}

TEST_F(Shape3Test, AsEdge_F64) {
  lm2_edge3_f64 edge = lm2_edge3_make_coords_f64(0.0, 0.0, 0.0, 10.0, 0.0, 0.0);

  lm2_shape3_f64 shape = lm2_shape3_from_edge_f64(&edge);

  lm2_edge3_f64* extracted = lm2_shape3_as_edge_f64(&shape);

  EXPECT_NE(extracted, nullptr);
  EXPECT_DOUBLE_EQ(extracted->start.x, 0.0);
  EXPECT_DOUBLE_EQ(extracted->end.x, 10.0);
}

// =============================================================================
// Shape Creation - Edge (f32)
// =============================================================================

TEST_F(Shape3Test, FromEdge_F32) {
  lm2_edge3_f32 edge = lm2_edge3_make_coords_f32(0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f);

  lm2_shape3_f32 shape = lm2_shape3_from_edge_f32(&edge);

  EXPECT_EQ(shape.type, LM2_SHAPE3_EDGE);
}

TEST_F(Shape3Test, AsEdge_F32) {
  lm2_edge3_f32 edge = lm2_edge3_make_coords_f32(0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f);

  lm2_shape3_f32 shape = lm2_shape3_from_edge_f32(&edge);

  lm2_edge3_f32* extracted = lm2_shape3_as_edge_f32(&shape);

  EXPECT_NE(extracted, nullptr);
  EXPECT_FLOAT_EQ(extracted->end.x, 10.0f);
}

// =============================================================================
// Type Query Tests (f64)
// =============================================================================

TEST_F(Shape3Test, IsType_F64) {
  lm2_sphere_f64 sphere = lm2_sphere_make_coords_f64(1.0, 2.0, 3.0, 5.0);
  lm2_shape3_f64 shape = lm2_shape3_from_sphere_f64(&sphere);

  EXPECT_TRUE(lm2_shape3_is_type_f64(&shape, LM2_SHAPE3_SPHERE));
  EXPECT_FALSE(lm2_shape3_is_type_f64(&shape, LM2_SHAPE3_CAPSULE));
  EXPECT_FALSE(lm2_shape3_is_type_f64(&shape, LM2_SHAPE3_AABB3));
  EXPECT_FALSE(lm2_shape3_is_type_f64(&shape, LM2_SHAPE3_TRIANGLE));
  EXPECT_FALSE(lm2_shape3_is_type_f64(&shape, LM2_SHAPE3_EDGE));
}

TEST_F(Shape3Test, GetType_F64) {
  lm2_capsule3_f64 capsule = lm2_capsule3_make_coords_f64(0.0, 0.0, 0.0, 10.0, 0.0, 0.0, 2.0);
  lm2_shape3_f64 shape = lm2_shape3_from_capsule_f64(&capsule);

  lm2_shape3_type type = lm2_shape3_get_type_f64(&shape);
  EXPECT_EQ(type, LM2_SHAPE3_CAPSULE);
}

// =============================================================================
// Type Query Tests (f32)
// =============================================================================

TEST_F(Shape3Test, IsType_F32) {
  lm2_sphere_f32 sphere = lm2_sphere_make_coords_f32(1.0f, 2.0f, 3.0f, 5.0f);
  lm2_shape3_f32 shape = lm2_shape3_from_sphere_f32(&sphere);

  EXPECT_TRUE(lm2_shape3_is_type_f32(&shape, LM2_SHAPE3_SPHERE));
  EXPECT_FALSE(lm2_shape3_is_type_f32(&shape, LM2_SHAPE3_CAPSULE));
}

TEST_F(Shape3Test, GetType_F32) {
  lm2_aabb3_f32 aabb = lm2_aabb3_from_min_max_f32(
      lm2_v3_make_f32(0.0f, 0.0f, 0.0f),
      lm2_v3_make_f32(10.0f, 10.0f, 10.0f));
  lm2_shape3_f32 shape = lm2_shape3_from_aabb3_f32(&aabb);

  lm2_shape3_type type = lm2_shape3_get_type_f32(&shape);
  EXPECT_EQ(type, LM2_SHAPE3_AABB3);
}

// =============================================================================
// Multiple Shape Type Tests (f64)
// =============================================================================

TEST_F(Shape3Test, MultipleShapes_F64) {
  // Create multiple shapes of different types
  lm2_sphere_f64 sphere = lm2_sphere_make_coords_f64(0.0, 0.0, 0.0, 5.0);
  lm2_capsule3_f64 capsule = lm2_capsule3_make_coords_f64(0.0, 0.0, 0.0, 10.0, 0.0, 0.0, 2.0);
  lm2_aabb3_f64 aabb = lm2_aabb3_from_min_max_f64(
      lm2_v3_make_f64(0.0, 0.0, 0.0),
      lm2_v3_make_f64(5.0, 5.0, 5.0));

  lm2_shape3_f64 shapes[3];
  shapes[0] = lm2_shape3_from_sphere_f64(&sphere);
  shapes[1] = lm2_shape3_from_capsule_f64(&capsule);
  shapes[2] = lm2_shape3_from_aabb3_f64(&aabb);

  // Verify types
  EXPECT_EQ(lm2_shape3_get_type_f64(&shapes[0]), LM2_SHAPE3_SPHERE);
  EXPECT_EQ(lm2_shape3_get_type_f64(&shapes[1]), LM2_SHAPE3_CAPSULE);
  EXPECT_EQ(lm2_shape3_get_type_f64(&shapes[2]), LM2_SHAPE3_AABB3);

  // Verify extraction
  EXPECT_NE(lm2_shape3_as_sphere_f64(&shapes[0]), nullptr);
  EXPECT_NE(lm2_shape3_as_capsule_f64(&shapes[1]), nullptr);
  EXPECT_NE(lm2_shape3_as_aabb3_f64(&shapes[2]), nullptr);

  // Verify incorrect extraction
  EXPECT_EQ(lm2_shape3_as_capsule_f64(&shapes[0]), nullptr);
  EXPECT_EQ(lm2_shape3_as_aabb3_f64(&shapes[1]), nullptr);
  EXPECT_EQ(lm2_shape3_as_sphere_f64(&shapes[2]), nullptr);
}

// =============================================================================
// Multiple Shape Type Tests (f32)
// =============================================================================

TEST_F(Shape3Test, MultipleShapes_F32) {
  lm2_sphere_f32 sphere = lm2_sphere_make_coords_f32(0.0f, 0.0f, 0.0f, 5.0f);
  lm2_edge3_f32 edge = lm2_edge3_make_coords_f32(0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f);
  lm2_triangle3_f32 tri;
  lm2_triangle3_make_coords_f32(tri, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 4.0f, 0.0f);

  lm2_shape3_f32 shapes[3];
  shapes[0] = lm2_shape3_from_sphere_f32(&sphere);
  shapes[1] = lm2_shape3_from_edge_f32(&edge);
  shapes[2] = lm2_shape3_from_triangle_f32(&tri);

  EXPECT_EQ(lm2_shape3_get_type_f32(&shapes[0]), LM2_SHAPE3_SPHERE);
  EXPECT_EQ(lm2_shape3_get_type_f32(&shapes[1]), LM2_SHAPE3_EDGE);
  EXPECT_EQ(lm2_shape3_get_type_f32(&shapes[2]), LM2_SHAPE3_TRIANGLE);
}

// =============================================================================
// Edge Cases
// =============================================================================

TEST_F(Shape3Test, AllShapeTypes_F64) {
  // Verify all shape type enums work correctly
  lm2_sphere_f64 sphere = lm2_sphere_make_coords_f64(0.0, 0.0, 0.0, 1.0);
  lm2_capsule3_f64 capsule = lm2_capsule3_make_coords_f64(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0);
  lm2_aabb3_f64 aabb = lm2_aabb3_unit_f64();
  lm2_triangle3_f64 tri;
  lm2_triangle3_make_coords_f64(tri, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  lm2_edge3_f64 edge = lm2_edge3_make_coords_f64(0.0, 0.0, 0.0, 1.0, 0.0, 0.0);

  lm2_shape3_f64 shape_sphere = lm2_shape3_from_sphere_f64(&sphere);
  lm2_shape3_f64 shape_capsule = lm2_shape3_from_capsule_f64(&capsule);
  lm2_shape3_f64 shape_aabb = lm2_shape3_from_aabb3_f64(&aabb);
  lm2_shape3_f64 shape_triangle = lm2_shape3_from_triangle_f64(&tri);
  lm2_shape3_f64 shape_edge = lm2_shape3_from_edge_f64(&edge);

  // All should have valid types
  EXPECT_EQ(shape_sphere.type, LM2_SHAPE3_SPHERE);
  EXPECT_EQ(shape_capsule.type, LM2_SHAPE3_CAPSULE);
  EXPECT_EQ(shape_aabb.type, LM2_SHAPE3_AABB3);
  EXPECT_EQ(shape_triangle.type, LM2_SHAPE3_TRIANGLE);
  EXPECT_EQ(shape_edge.type, LM2_SHAPE3_EDGE);
}
