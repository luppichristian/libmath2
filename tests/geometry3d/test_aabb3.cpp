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
#include "lm2/geometry3d/lm2_aabb3.h"

// Test fixture for AABB3 tests
class AABB3Test : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-6f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Construction Tests (f64)
// =============================================================================

TEST_F(AABB3Test, FromMinMax_F64) {
  lm2_v3_f64 min = lm2_v3_make_f64(1.0, 2.0, 3.0);
  lm2_v3_f64 max = lm2_v3_make_f64(4.0, 6.0, 9.0);
  lm2_aabb3_f64 aabb = lm2_aabb3_from_min_max_f64(min, max);

  EXPECT_DOUBLE_EQ(aabb.min.x, 1.0);
  EXPECT_DOUBLE_EQ(aabb.min.y, 2.0);
  EXPECT_DOUBLE_EQ(aabb.min.z, 3.0);
  EXPECT_DOUBLE_EQ(aabb.max.x, 4.0);
  EXPECT_DOUBLE_EQ(aabb.max.y, 6.0);
  EXPECT_DOUBLE_EQ(aabb.max.z, 9.0);
}

TEST_F(AABB3Test, FromCenterSize_F64) {
  lm2_v3_f64 center = lm2_v3_make_f64(5.0, 5.0, 5.0);
  lm2_v3_f64 size = lm2_v3_make_f64(4.0, 6.0, 8.0);
  lm2_aabb3_f64 aabb = lm2_aabb3_from_center_size_f64(center, size);

  EXPECT_DOUBLE_EQ(aabb.min.x, 3.0);
  EXPECT_DOUBLE_EQ(aabb.min.y, 2.0);
  EXPECT_DOUBLE_EQ(aabb.min.z, 1.0);
  EXPECT_DOUBLE_EQ(aabb.max.x, 7.0);
  EXPECT_DOUBLE_EQ(aabb.max.y, 8.0);
  EXPECT_DOUBLE_EQ(aabb.max.z, 9.0);
}

TEST_F(AABB3Test, FromCenterExtents_F64) {
  lm2_v3_f64 center = lm2_v3_make_f64(5.0, 5.0, 5.0);
  lm2_v3_f64 extents = lm2_v3_make_f64(2.0, 3.0, 4.0);
  lm2_aabb3_f64 aabb = lm2_aabb3_from_center_extents_f64(center, extents);

  EXPECT_DOUBLE_EQ(aabb.min.x, 3.0);
  EXPECT_DOUBLE_EQ(aabb.min.y, 2.0);
  EXPECT_DOUBLE_EQ(aabb.min.z, 1.0);
  EXPECT_DOUBLE_EQ(aabb.max.x, 7.0);
  EXPECT_DOUBLE_EQ(aabb.max.y, 8.0);
  EXPECT_DOUBLE_EQ(aabb.max.z, 9.0);
}

TEST_F(AABB3Test, FromPositionSize_F64) {
  lm2_v3_f64 pos = lm2_v3_make_f64(1.0, 2.0, 3.0);
  lm2_v3_f64 size = lm2_v3_make_f64(4.0, 5.0, 6.0);
  lm2_aabb3_f64 aabb = lm2_aabb3_from_position_size_f64(pos, size);

  EXPECT_DOUBLE_EQ(aabb.min.x, 1.0);
  EXPECT_DOUBLE_EQ(aabb.min.y, 2.0);
  EXPECT_DOUBLE_EQ(aabb.min.z, 3.0);
  EXPECT_DOUBLE_EQ(aabb.max.x, 5.0);
  EXPECT_DOUBLE_EQ(aabb.max.y, 7.0);
  EXPECT_DOUBLE_EQ(aabb.max.z, 9.0);
}

TEST_F(AABB3Test, Unit_F64) {
  lm2_aabb3_f64 aabb = lm2_aabb3_unit_f64();

  EXPECT_DOUBLE_EQ(aabb.min.x, 0.0);
  EXPECT_DOUBLE_EQ(aabb.min.y, 0.0);
  EXPECT_DOUBLE_EQ(aabb.min.z, 0.0);
  EXPECT_DOUBLE_EQ(aabb.max.x, 1.0);
  EXPECT_DOUBLE_EQ(aabb.max.y, 1.0);
  EXPECT_DOUBLE_EQ(aabb.max.z, 1.0);
}

// =============================================================================
// Construction Tests (f32)
// =============================================================================

TEST_F(AABB3Test, FromMinMax_F32) {
  lm2_v3_f32 min = lm2_v3_make_f32(1.0f, 2.0f, 3.0f);
  lm2_v3_f32 max = lm2_v3_make_f32(4.0f, 6.0f, 9.0f);
  lm2_aabb3_f32 aabb = lm2_aabb3_from_min_max_f32(min, max);

  EXPECT_FLOAT_EQ(aabb.min.x, 1.0f);
  EXPECT_FLOAT_EQ(aabb.min.y, 2.0f);
  EXPECT_FLOAT_EQ(aabb.min.z, 3.0f);
  EXPECT_FLOAT_EQ(aabb.max.x, 4.0f);
  EXPECT_FLOAT_EQ(aabb.max.y, 6.0f);
  EXPECT_FLOAT_EQ(aabb.max.z, 9.0f);
}

TEST_F(AABB3Test, FromCenterSize_F32) {
  lm2_v3_f32 center = lm2_v3_make_f32(5.0f, 5.0f, 5.0f);
  lm2_v3_f32 size = lm2_v3_make_f32(4.0f, 6.0f, 8.0f);
  lm2_aabb3_f32 aabb = lm2_aabb3_from_center_size_f32(center, size);

  EXPECT_FLOAT_EQ(aabb.min.x, 3.0f);
  EXPECT_FLOAT_EQ(aabb.min.y, 2.0f);
  EXPECT_FLOAT_EQ(aabb.min.z, 1.0f);
  EXPECT_FLOAT_EQ(aabb.max.x, 7.0f);
  EXPECT_FLOAT_EQ(aabb.max.y, 8.0f);
  EXPECT_FLOAT_EQ(aabb.max.z, 9.0f);
}

TEST_F(AABB3Test, Unit_F32) {
  lm2_aabb3_f32 aabb = lm2_aabb3_unit_f32();

  EXPECT_FLOAT_EQ(aabb.min.x, 0.0f);
  EXPECT_FLOAT_EQ(aabb.min.y, 0.0f);
  EXPECT_FLOAT_EQ(aabb.min.z, 0.0f);
  EXPECT_FLOAT_EQ(aabb.max.x, 1.0f);
  EXPECT_FLOAT_EQ(aabb.max.y, 1.0f);
  EXPECT_FLOAT_EQ(aabb.max.z, 1.0f);
}

// =============================================================================
// Properties Tests (f64)
// =============================================================================

TEST_F(AABB3Test, SurfaceArea_F64) {
  lm2_v3_f64 min = lm2_v3_make_f64(0.0, 0.0, 0.0);
  lm2_v3_f64 max = lm2_v3_make_f64(2.0, 3.0, 4.0);
  lm2_aabb3_f64 aabb = lm2_aabb3_from_min_max_f64(min, max);

  // Surface area = 2 * (w*h + w*d + h*d) = 2 * (2*3 + 2*4 + 3*4) = 2 * 26 = 52
  double area = lm2_aabb3_surface_area_f64(aabb);
  EXPECT_NEAR(area, 52.0, EPSILON_F64);
}

TEST_F(AABB3Test, Diagonal_F64) {
  lm2_v3_f64 min = lm2_v3_make_f64(0.0, 0.0, 0.0);
  lm2_v3_f64 max = lm2_v3_make_f64(3.0, 4.0, 0.0);
  lm2_aabb3_f64 aabb = lm2_aabb3_from_min_max_f64(min, max);

  double diagonal = lm2_aabb3_diagonal_f64(aabb);
  EXPECT_NEAR(diagonal, 5.0, EPSILON_F64);  // 3-4-5 triangle in XY plane
}

TEST_F(AABB3Test, WidthHeightDepth_F64) {
  lm2_v3_f64 min = lm2_v3_make_f64(1.0, 2.0, 3.0);
  lm2_v3_f64 max = lm2_v3_make_f64(5.0, 8.0, 10.0);
  lm2_aabb3_f64 aabb = lm2_aabb3_from_min_max_f64(min, max);

  EXPECT_DOUBLE_EQ(lm2_aabb3_width_f64(aabb), 4.0);
  EXPECT_DOUBLE_EQ(lm2_aabb3_height_f64(aabb), 6.0);
  EXPECT_DOUBLE_EQ(lm2_aabb3_depth_f64(aabb), 7.0);
}

// =============================================================================
// Properties Tests (f32)
// =============================================================================

TEST_F(AABB3Test, SurfaceArea_F32) {
  lm2_v3_f32 min = lm2_v3_make_f32(0.0f, 0.0f, 0.0f);
  lm2_v3_f32 max = lm2_v3_make_f32(2.0f, 3.0f, 4.0f);
  lm2_aabb3_f32 aabb = lm2_aabb3_from_min_max_f32(min, max);

  float area = lm2_aabb3_surface_area_f32(aabb);
  EXPECT_NEAR(area, 52.0f, EPSILON_F32);
}

TEST_F(AABB3Test, Diagonal_F32) {
  lm2_v3_f32 min = lm2_v3_make_f32(0.0f, 0.0f, 0.0f);
  lm2_v3_f32 max = lm2_v3_make_f32(3.0f, 4.0f, 0.0f);
  lm2_aabb3_f32 aabb = lm2_aabb3_from_min_max_f32(min, max);

  float diagonal = lm2_aabb3_diagonal_f32(aabb);
  EXPECT_NEAR(diagonal, 5.0f, EPSILON_F32);
}

TEST_F(AABB3Test, WidthHeightDepth_F32) {
  lm2_v3_f32 min = lm2_v3_make_f32(1.0f, 2.0f, 3.0f);
  lm2_v3_f32 max = lm2_v3_make_f32(5.0f, 8.0f, 10.0f);
  lm2_aabb3_f32 aabb = lm2_aabb3_from_min_max_f32(min, max);

  EXPECT_FLOAT_EQ(lm2_aabb3_width_f32(aabb), 4.0f);
  EXPECT_FLOAT_EQ(lm2_aabb3_height_f32(aabb), 6.0f);
  EXPECT_FLOAT_EQ(lm2_aabb3_depth_f32(aabb), 7.0f);
}

// =============================================================================
// Corner Operations Tests (f64)
// =============================================================================

TEST_F(AABB3Test, GetCorner_F64) {
  lm2_v3_f64 min = lm2_v3_make_f64(1.0, 2.0, 3.0);
  lm2_v3_f64 max = lm2_v3_make_f64(4.0, 5.0, 6.0);
  lm2_aabb3_f64 aabb = lm2_aabb3_from_min_max_f64(min, max);

  lm2_v3_f64 corner = lm2_aabb3_get_corner_f64(aabb, LM2_CORNER3_MIN_MIN_MIN);
  EXPECT_DOUBLE_EQ(corner.x, 1.0);
  EXPECT_DOUBLE_EQ(corner.y, 2.0);
  EXPECT_DOUBLE_EQ(corner.z, 3.0);

  corner = lm2_aabb3_get_corner_f64(aabb, LM2_CORNER3_MAX_MAX_MAX);
  EXPECT_DOUBLE_EQ(corner.x, 4.0);
  EXPECT_DOUBLE_EQ(corner.y, 5.0);
  EXPECT_DOUBLE_EQ(corner.z, 6.0);

  corner = lm2_aabb3_get_corner_f64(aabb, LM2_CORNER3_MIN_MAX_MIN);
  EXPECT_DOUBLE_EQ(corner.x, 1.0);
  EXPECT_DOUBLE_EQ(corner.y, 5.0);
  EXPECT_DOUBLE_EQ(corner.z, 3.0);
}

TEST_F(AABB3Test, GetAllCorners_F64) {
  lm2_v3_f64 min = lm2_v3_make_f64(1.0, 2.0, 3.0);
  lm2_v3_f64 max = lm2_v3_make_f64(4.0, 5.0, 6.0);
  lm2_aabb3_f64 aabb = lm2_aabb3_from_min_max_f64(min, max);

  lm2_v3_f64 corners[8];
  lm2_aabb3_get_corners_f64(aabb, corners);

  // Verify first corner (MIN_MIN_MIN)
  EXPECT_DOUBLE_EQ(corners[0].x, 1.0);
  EXPECT_DOUBLE_EQ(corners[0].y, 2.0);
  EXPECT_DOUBLE_EQ(corners[0].z, 3.0);

  // Verify last corner (MAX_MAX_MAX)
  EXPECT_DOUBLE_EQ(corners[7].x, 4.0);
  EXPECT_DOUBLE_EQ(corners[7].y, 5.0);
  EXPECT_DOUBLE_EQ(corners[7].z, 6.0);
}

// =============================================================================
// Corner Operations Tests (f32)
// =============================================================================

TEST_F(AABB3Test, GetCorner_F32) {
  lm2_v3_f32 min = lm2_v3_make_f32(1.0f, 2.0f, 3.0f);
  lm2_v3_f32 max = lm2_v3_make_f32(4.0f, 5.0f, 6.0f);
  lm2_aabb3_f32 aabb = lm2_aabb3_from_min_max_f32(min, max);

  lm2_v3_f32 corner = lm2_aabb3_get_corner_f32(aabb, LM2_CORNER3_MIN_MIN_MIN);
  EXPECT_FLOAT_EQ(corner.x, 1.0f);
  EXPECT_FLOAT_EQ(corner.y, 2.0f);
  EXPECT_FLOAT_EQ(corner.z, 3.0f);

  corner = lm2_aabb3_get_corner_f32(aabb, LM2_CORNER3_MAX_MAX_MAX);
  EXPECT_FLOAT_EQ(corner.x, 4.0f);
  EXPECT_FLOAT_EQ(corner.y, 5.0f);
  EXPECT_FLOAT_EQ(corner.z, 6.0f);
}

// =============================================================================
// Face Operations Tests (f64)
// =============================================================================

TEST_F(AABB3Test, FaceCenter_F64) {
  lm2_v3_f64 min = lm2_v3_make_f64(0.0, 0.0, 0.0);
  lm2_v3_f64 max = lm2_v3_make_f64(4.0, 6.0, 8.0);
  lm2_aabb3_f64 aabb = lm2_aabb3_from_min_max_f64(min, max);

  lm2_v3_f64 center = lm2_aabb3_face_center_f64(aabb, LM2_AABB3_FACE_FRONT);
  EXPECT_DOUBLE_EQ(center.x, 2.0);
  EXPECT_DOUBLE_EQ(center.y, 3.0);
  EXPECT_DOUBLE_EQ(center.z, 8.0);

  center = lm2_aabb3_face_center_f64(aabb, LM2_AABB3_FACE_RIGHT);
  EXPECT_DOUBLE_EQ(center.x, 4.0);
  EXPECT_DOUBLE_EQ(center.y, 3.0);
  EXPECT_DOUBLE_EQ(center.z, 4.0);
}

TEST_F(AABB3Test, FaceNormal_F64) {
  lm2_v3_f64 normal = lm2_aabb3_face_normal_f64(LM2_AABB3_FACE_FRONT);
  EXPECT_DOUBLE_EQ(normal.x, 0.0);
  EXPECT_DOUBLE_EQ(normal.y, 0.0);
  EXPECT_DOUBLE_EQ(normal.z, 1.0);

  normal = lm2_aabb3_face_normal_f64(LM2_AABB3_FACE_RIGHT);
  EXPECT_DOUBLE_EQ(normal.x, 1.0);
  EXPECT_DOUBLE_EQ(normal.y, 0.0);
  EXPECT_DOUBLE_EQ(normal.z, 0.0);

  normal = lm2_aabb3_face_normal_f64(LM2_AABB3_FACE_TOP);
  EXPECT_DOUBLE_EQ(normal.x, 0.0);
  EXPECT_DOUBLE_EQ(normal.y, 1.0);
  EXPECT_DOUBLE_EQ(normal.z, 0.0);
}

// =============================================================================
// Face Operations Tests (f32)
// =============================================================================

TEST_F(AABB3Test, FaceCenter_F32) {
  lm2_v3_f32 min = lm2_v3_make_f32(0.0f, 0.0f, 0.0f);
  lm2_v3_f32 max = lm2_v3_make_f32(4.0f, 6.0f, 8.0f);
  lm2_aabb3_f32 aabb = lm2_aabb3_from_min_max_f32(min, max);

  lm2_v3_f32 center = lm2_aabb3_face_center_f32(aabb, LM2_AABB3_FACE_FRONT);
  EXPECT_FLOAT_EQ(center.x, 2.0f);
  EXPECT_FLOAT_EQ(center.y, 3.0f);
  EXPECT_FLOAT_EQ(center.z, 8.0f);
}

TEST_F(AABB3Test, FaceNormal_F32) {
  lm2_v3_f32 normal = lm2_aabb3_face_normal_f32(LM2_AABB3_FACE_BACK);
  EXPECT_FLOAT_EQ(normal.x, 0.0f);
  EXPECT_FLOAT_EQ(normal.y, 0.0f);
  EXPECT_FLOAT_EQ(normal.z, -1.0f);
}

// =============================================================================
// Tests - Containment (f64)
// =============================================================================

TEST_F(AABB3Test, ContainsPoint_F64) {
  lm2_v3_f64 min = lm2_v3_make_f64(0.0, 0.0, 0.0);
  lm2_v3_f64 max = lm2_v3_make_f64(10.0, 10.0, 10.0);
  lm2_aabb3_f64 aabb = lm2_aabb3_from_min_max_f64(min, max);

  lm2_v3_f64 inside = lm2_v3_make_f64(5.0, 5.0, 5.0);
  EXPECT_TRUE(lm2_aabb3_contains_point_f64(aabb, inside));

  lm2_v3_f64 outside = lm2_v3_make_f64(15.0, 5.0, 5.0);
  EXPECT_FALSE(lm2_aabb3_contains_point_f64(aabb, outside));

  lm2_v3_f64 onEdge = lm2_v3_make_f64(10.0, 10.0, 10.0);
  EXPECT_TRUE(lm2_aabb3_contains_point_f64(aabb, onEdge));
}

TEST_F(AABB3Test, Overlaps_F64) {
  lm2_aabb3_f64 a = lm2_aabb3_from_min_max_f64(
      lm2_v3_make_f64(0.0, 0.0, 0.0),
      lm2_v3_make_f64(10.0, 10.0, 10.0));

  lm2_aabb3_f64 b = lm2_aabb3_from_min_max_f64(
      lm2_v3_make_f64(5.0, 5.0, 5.0),
      lm2_v3_make_f64(15.0, 15.0, 15.0));

  EXPECT_TRUE(lm2_aabb3_overlaps_f64(a, b));

  lm2_aabb3_f64 c = lm2_aabb3_from_min_max_f64(
      lm2_v3_make_f64(20.0, 20.0, 20.0),
      lm2_v3_make_f64(30.0, 30.0, 30.0));

  EXPECT_FALSE(lm2_aabb3_overlaps_f64(a, c));
}

// =============================================================================
// Tests - Containment (f32)
// =============================================================================

TEST_F(AABB3Test, ContainsPoint_F32) {
  lm2_v3_f32 min = lm2_v3_make_f32(0.0f, 0.0f, 0.0f);
  lm2_v3_f32 max = lm2_v3_make_f32(10.0f, 10.0f, 10.0f);
  lm2_aabb3_f32 aabb = lm2_aabb3_from_min_max_f32(min, max);

  lm2_v3_f32 inside = lm2_v3_make_f32(5.0f, 5.0f, 5.0f);
  EXPECT_TRUE(lm2_aabb3_contains_point_f32(aabb, inside));

  lm2_v3_f32 outside = lm2_v3_make_f32(15.0f, 5.0f, 5.0f);
  EXPECT_FALSE(lm2_aabb3_contains_point_f32(aabb, outside));
}

TEST_F(AABB3Test, Overlaps_F32) {
  lm2_aabb3_f32 a = lm2_aabb3_from_min_max_f32(
      lm2_v3_make_f32(0.0f, 0.0f, 0.0f),
      lm2_v3_make_f32(10.0f, 10.0f, 10.0f));

  lm2_aabb3_f32 b = lm2_aabb3_from_min_max_f32(
      lm2_v3_make_f32(5.0f, 5.0f, 5.0f),
      lm2_v3_make_f32(15.0f, 15.0f, 15.0f));

  EXPECT_TRUE(lm2_aabb3_overlaps_f32(a, b));
}

// =============================================================================
// Transformations Tests (f64)
// =============================================================================

TEST_F(AABB3Test, Translate_F64) {
  lm2_aabb3_f64 aabb = lm2_aabb3_from_min_max_f64(
      lm2_v3_make_f64(0.0, 0.0, 0.0),
      lm2_v3_make_f64(5.0, 5.0, 5.0));

  lm2_v3_f64 offset = lm2_v3_make_f64(10.0, 20.0, 30.0);
  lm2_aabb3_f64 translated = lm2_aabb3_translate_f64(aabb, offset);

  EXPECT_DOUBLE_EQ(translated.min.x, 10.0);
  EXPECT_DOUBLE_EQ(translated.min.y, 20.0);
  EXPECT_DOUBLE_EQ(translated.min.z, 30.0);
  EXPECT_DOUBLE_EQ(translated.max.x, 15.0);
  EXPECT_DOUBLE_EQ(translated.max.y, 25.0);
  EXPECT_DOUBLE_EQ(translated.max.z, 35.0);
}

TEST_F(AABB3Test, Scale_F64) {
  lm2_aabb3_f64 aabb = lm2_aabb3_from_min_max_f64(
      lm2_v3_make_f64(0.0, 0.0, 0.0),
      lm2_v3_make_f64(5.0, 5.0, 5.0));

  lm2_v3_f64 scale = lm2_v3_make_f64(2.0, 3.0, 4.0);
  lm2_aabb3_f64 scaled = lm2_aabb3_scale_f64(aabb, scale);

  EXPECT_DOUBLE_EQ(scaled.min.x, 0.0);
  EXPECT_DOUBLE_EQ(scaled.min.y, 0.0);
  EXPECT_DOUBLE_EQ(scaled.min.z, 0.0);
  EXPECT_DOUBLE_EQ(scaled.max.x, 10.0);
  EXPECT_DOUBLE_EQ(scaled.max.y, 15.0);
  EXPECT_DOUBLE_EQ(scaled.max.z, 20.0);
}

TEST_F(AABB3Test, Expand_F64) {
  lm2_aabb3_f64 aabb = lm2_aabb3_from_min_max_f64(
      lm2_v3_make_f64(5.0, 5.0, 5.0),
      lm2_v3_make_f64(10.0, 10.0, 10.0));

  lm2_v3_f64 amount = lm2_v3_make_f64(1.0, 2.0, 3.0);
  lm2_aabb3_f64 expanded = lm2_aabb3_expand_f64(aabb, amount);

  EXPECT_DOUBLE_EQ(expanded.min.x, 4.0);
  EXPECT_DOUBLE_EQ(expanded.min.y, 3.0);
  EXPECT_DOUBLE_EQ(expanded.min.z, 2.0);
  EXPECT_DOUBLE_EQ(expanded.max.x, 11.0);
  EXPECT_DOUBLE_EQ(expanded.max.y, 12.0);
  EXPECT_DOUBLE_EQ(expanded.max.z, 13.0);
}

// =============================================================================
// Transformations Tests (f32)
// =============================================================================

TEST_F(AABB3Test, Translate_F32) {
  lm2_aabb3_f32 aabb = lm2_aabb3_from_min_max_f32(
      lm2_v3_make_f32(0.0f, 0.0f, 0.0f),
      lm2_v3_make_f32(5.0f, 5.0f, 5.0f));

  lm2_v3_f32 offset = lm2_v3_make_f32(10.0f, 20.0f, 30.0f);
  lm2_aabb3_f32 translated = lm2_aabb3_translate_f32(aabb, offset);

  EXPECT_FLOAT_EQ(translated.min.x, 10.0f);
  EXPECT_FLOAT_EQ(translated.min.y, 20.0f);
  EXPECT_FLOAT_EQ(translated.min.z, 30.0f);
  EXPECT_FLOAT_EQ(translated.max.x, 15.0f);
  EXPECT_FLOAT_EQ(translated.max.y, 25.0f);
  EXPECT_FLOAT_EQ(translated.max.z, 35.0f);
}

TEST_F(AABB3Test, Scale_F32) {
  lm2_aabb3_f32 aabb = lm2_aabb3_from_min_max_f32(
      lm2_v3_make_f32(0.0f, 0.0f, 0.0f),
      lm2_v3_make_f32(5.0f, 5.0f, 5.0f));

  lm2_v3_f32 scale = lm2_v3_make_f32(2.0f, 3.0f, 4.0f);
  lm2_aabb3_f32 scaled = lm2_aabb3_scale_f32(aabb, scale);

  EXPECT_FLOAT_EQ(scaled.min.x, 0.0f);
  EXPECT_FLOAT_EQ(scaled.min.y, 0.0f);
  EXPECT_FLOAT_EQ(scaled.min.z, 0.0f);
  EXPECT_FLOAT_EQ(scaled.max.x, 10.0f);
  EXPECT_FLOAT_EQ(scaled.max.y, 15.0f);
  EXPECT_FLOAT_EQ(scaled.max.z, 20.0f);
}

TEST_F(AABB3Test, Expand_F32) {
  lm2_aabb3_f32 aabb = lm2_aabb3_from_min_max_f32(
      lm2_v3_make_f32(5.0f, 5.0f, 5.0f),
      lm2_v3_make_f32(10.0f, 10.0f, 10.0f));

  lm2_v3_f32 amount = lm2_v3_make_f32(1.0f, 2.0f, 3.0f);
  lm2_aabb3_f32 expanded = lm2_aabb3_expand_f32(aabb, amount);

  EXPECT_FLOAT_EQ(expanded.min.x, 4.0f);
  EXPECT_FLOAT_EQ(expanded.min.y, 3.0f);
  EXPECT_FLOAT_EQ(expanded.min.z, 2.0f);
  EXPECT_FLOAT_EQ(expanded.max.x, 11.0f);
  EXPECT_FLOAT_EQ(expanded.max.y, 12.0f);
  EXPECT_FLOAT_EQ(expanded.max.z, 13.0f);
}
