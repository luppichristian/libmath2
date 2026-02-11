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
#include "lm2/geometry2d/lm2_aabb2.h"

// Test fixture for AABB2 tests
class AABB2Test : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-6f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Corner Operations (f64)
// =============================================================================

TEST_F(AABB2Test, GetCorner_TopRight_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(10.0, 10.0));
  lm2_v2_f64 corner = lm2_r2_get_corner_f64(rect, LM2_CORNER2_TOP_RIGHT);
  EXPECT_DOUBLE_EQ(corner.x, 10.0);
  EXPECT_DOUBLE_EQ(corner.y, 10.0);
}

TEST_F(AABB2Test, GetCorner_TopLeft_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(2.0, 3.0), lm2_v2_make_f64(8.0, 7.0));
  lm2_v2_f64 corner = lm2_r2_get_corner_f64(rect, LM2_CORNER2_TOP_LEFT);
  EXPECT_DOUBLE_EQ(corner.x, 2.0);
  EXPECT_DOUBLE_EQ(corner.y, 7.0);
}

TEST_F(AABB2Test, GetCorner_BottomRight_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(1.0, 2.0), lm2_v2_make_f64(5.0, 6.0));
  lm2_v2_f64 corner = lm2_r2_get_corner_f64(rect, LM2_CORNER2_BOTTOM_RIGHT);
  EXPECT_DOUBLE_EQ(corner.x, 5.0);
  EXPECT_DOUBLE_EQ(corner.y, 2.0);
}

TEST_F(AABB2Test, GetCorner_BottomLeft_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(3.0, 4.0), lm2_v2_make_f64(9.0, 8.0));
  lm2_v2_f64 corner = lm2_r2_get_corner_f64(rect, LM2_CORNER2_BOTTOM_LEFT);
  EXPECT_DOUBLE_EQ(corner.x, 3.0);
  EXPECT_DOUBLE_EQ(corner.y, 4.0);
}

TEST_F(AABB2Test, GetBottomLeft_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(1.0, 2.0), lm2_v2_make_f64(5.0, 6.0));
  lm2_v2_f64 corner = lm2_r2_get_bottom_left_f64(rect);
  EXPECT_DOUBLE_EQ(corner.x, 1.0);
  EXPECT_DOUBLE_EQ(corner.y, 2.0);
}

TEST_F(AABB2Test, GetTopRight_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(1.0, 2.0), lm2_v2_make_f64(5.0, 6.0));
  lm2_v2_f64 corner = lm2_r2_get_top_right_f64(rect);
  EXPECT_DOUBLE_EQ(corner.x, 5.0);
  EXPECT_DOUBLE_EQ(corner.y, 6.0);
}

// =============================================================================
// Corner Operations (f32)
// =============================================================================

TEST_F(AABB2Test, GetCorner_TopRight_F32) {
  lm2_r2_f32 rect = lm2_r2_from_min_max_f32(lm2_v2_make_f32(0.0f, 0.0f), lm2_v2_make_f32(10.0f, 10.0f));
  lm2_v2_f32 corner = lm2_r2_get_corner_f32(rect, LM2_CORNER2_TOP_RIGHT);
  EXPECT_FLOAT_EQ(corner.x, 10.0f);
  EXPECT_FLOAT_EQ(corner.y, 10.0f);
}

// =============================================================================
// Transform Operations - Scale (f64)
// =============================================================================

TEST_F(AABB2Test, ScaleFromCenter_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(4.0, 4.0));
  lm2_v2_f64 scale = lm2_v2_make_f64(2.0, 2.0);
  lm2_r2_f64 scaled = lm2_r2_scale_from_center_f64(rect, scale);

  EXPECT_DOUBLE_EQ(scaled.min.x, -2.0);
  EXPECT_DOUBLE_EQ(scaled.min.y, -2.0);
  EXPECT_DOUBLE_EQ(scaled.max.x, 6.0);
  EXPECT_DOUBLE_EQ(scaled.max.y, 6.0);
}

TEST_F(AABB2Test, ScaleFromMin_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(1.0, 1.0), lm2_v2_make_f64(3.0, 3.0));
  lm2_v2_f64 scale = lm2_v2_make_f64(2.0, 2.0);
  lm2_r2_f64 scaled = lm2_r2_scale_from_min_f64(rect, scale);

  EXPECT_DOUBLE_EQ(scaled.min.x, 1.0);
  EXPECT_DOUBLE_EQ(scaled.min.y, 1.0);
  EXPECT_DOUBLE_EQ(scaled.max.x, 5.0);
  EXPECT_DOUBLE_EQ(scaled.max.y, 5.0);
}

TEST_F(AABB2Test, ScaleFromMax_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(1.0, 1.0), lm2_v2_make_f64(3.0, 3.0));
  lm2_v2_f64 scale = lm2_v2_make_f64(2.0, 2.0);
  lm2_r2_f64 scaled = lm2_r2_scale_from_max_f64(rect, scale);

  EXPECT_DOUBLE_EQ(scaled.min.x, -1.0);
  EXPECT_DOUBLE_EQ(scaled.min.y, -1.0);
  EXPECT_DOUBLE_EQ(scaled.max.x, 3.0);
  EXPECT_DOUBLE_EQ(scaled.max.y, 3.0);
}

// =============================================================================
// Transform Operations - Shrink/Inflate (f64)
// =============================================================================

TEST_F(AABB2Test, ShrinkVec_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(10.0, 10.0));
  lm2_v2_f64 amount = lm2_v2_make_f64(1.0, 2.0);
  lm2_r2_f64 shrunk = lm2_r2_shrink_vec_f64(rect, amount);

  EXPECT_DOUBLE_EQ(shrunk.min.x, 1.0);
  EXPECT_DOUBLE_EQ(shrunk.min.y, 2.0);
  EXPECT_DOUBLE_EQ(shrunk.max.x, 9.0);
  EXPECT_DOUBLE_EQ(shrunk.max.y, 8.0);
}

TEST_F(AABB2Test, ShrinkScalar_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(10.0, 10.0));
  lm2_r2_f64 shrunk = lm2_r2_shrink_scalar_f64(rect, 1.5);

  EXPECT_DOUBLE_EQ(shrunk.min.x, 1.5);
  EXPECT_DOUBLE_EQ(shrunk.min.y, 1.5);
  EXPECT_DOUBLE_EQ(shrunk.max.x, 8.5);
  EXPECT_DOUBLE_EQ(shrunk.max.y, 8.5);
}

TEST_F(AABB2Test, InflateVec_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(2.0, 2.0), lm2_v2_make_f64(8.0, 8.0));
  lm2_v2_f64 amount = lm2_v2_make_f64(1.0, 2.0);
  lm2_r2_f64 inflated = lm2_r2_inflate_vec_f64(rect, amount);

  EXPECT_DOUBLE_EQ(inflated.min.x, 1.0);
  EXPECT_DOUBLE_EQ(inflated.min.y, 0.0);
  EXPECT_DOUBLE_EQ(inflated.max.x, 9.0);
  EXPECT_DOUBLE_EQ(inflated.max.y, 10.0);
}

TEST_F(AABB2Test, InflateScalar_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(2.0, 2.0), lm2_v2_make_f64(8.0, 8.0));
  lm2_r2_f64 inflated = lm2_r2_inflate_scalar_f64(rect, 1.0);

  EXPECT_DOUBLE_EQ(inflated.min.x, 1.0);
  EXPECT_DOUBLE_EQ(inflated.min.y, 1.0);
  EXPECT_DOUBLE_EQ(inflated.max.x, 9.0);
  EXPECT_DOUBLE_EQ(inflated.max.y, 9.0);
}

// =============================================================================
// Query Operations (f64)
// =============================================================================

TEST_F(AABB2Test, GetDim_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(1.0, 2.0), lm2_v2_make_f64(5.0, 8.0));
  lm2_v2_f64 dim = lm2_r2_get_dim_f64(rect);
  EXPECT_DOUBLE_EQ(dim.x, 4.0);
  EXPECT_DOUBLE_EQ(dim.y, 6.0);
}

TEST_F(AABB2Test, OverlapRect_True_F64) {
  lm2_r2_f64 a = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(5.0, 5.0));
  lm2_r2_f64 b = lm2_r2_from_min_max_f64(lm2_v2_make_f64(3.0, 3.0), lm2_v2_make_f64(8.0, 8.0));
  EXPECT_TRUE(lm2_r2_overlap_rect_f64(a, b));
}

TEST_F(AABB2Test, OverlapRect_False_F64) {
  lm2_r2_f64 a = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(2.0, 2.0));
  lm2_r2_f64 b = lm2_r2_from_min_max_f64(lm2_v2_make_f64(3.0, 3.0), lm2_v2_make_f64(5.0, 5.0));
  EXPECT_FALSE(lm2_r2_overlap_rect_f64(a, b));
}

TEST_F(AABB2Test, OverlapPoint_Inside_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(10.0, 10.0));
  lm2_v2_f64 point = lm2_v2_make_f64(5.0, 5.0);
  EXPECT_TRUE(lm2_r2_overlap_point_f64(rect, point));
}

TEST_F(AABB2Test, OverlapPoint_Outside_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(10.0, 10.0));
  lm2_v2_f64 point = lm2_v2_make_f64(15.0, 15.0);
  EXPECT_FALSE(lm2_r2_overlap_point_f64(rect, point));
}

TEST_F(AABB2Test, Contains_True_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(10.0, 10.0));
  lm2_r2_f64 subrect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(2.0, 2.0), lm2_v2_make_f64(8.0, 8.0));
  EXPECT_TRUE(lm2_r2_contains_f64(rect, subrect));
}

TEST_F(AABB2Test, Contains_False_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(5.0, 5.0));
  lm2_r2_f64 subrect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(2.0, 2.0), lm2_v2_make_f64(8.0, 8.0));
  EXPECT_FALSE(lm2_r2_contains_f64(rect, subrect));
}

TEST_F(AABB2Test, Distance_PointInside_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(10.0, 10.0));
  lm2_v2_f64 point = lm2_v2_make_f64(5.0, 5.0);
  double dist = lm2_r2_distance_f64(rect, point);
  EXPECT_DOUBLE_EQ(dist, 0.0);
}

TEST_F(AABB2Test, Distance_PointOutside_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(10.0, 10.0));
  lm2_v2_f64 point = lm2_v2_make_f64(15.0, 10.0);
  double dist = lm2_r2_distance_f64(rect, point);
  EXPECT_DOUBLE_EQ(dist, 5.0);
}

TEST_F(AABB2Test, GetClosestPoint_Inside_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(10.0, 10.0));
  lm2_v2_f64 point = lm2_v2_make_f64(5.0, 5.0);
  lm2_v2_f64 closest = lm2_r2_get_closest_point_f64(rect, point);
  EXPECT_DOUBLE_EQ(closest.x, 5.0);
  EXPECT_DOUBLE_EQ(closest.y, 5.0);
}

TEST_F(AABB2Test, GetClosestPoint_Outside_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(10.0, 10.0));
  lm2_v2_f64 point = lm2_v2_make_f64(15.0, 5.0);
  lm2_v2_f64 closest = lm2_r2_get_closest_point_f64(rect, point);
  EXPECT_DOUBLE_EQ(closest.x, 10.0);
  EXPECT_DOUBLE_EQ(closest.y, 5.0);
}

// =============================================================================
// Cut Operations (f64)
// =============================================================================

TEST_F(AABB2Test, CutLeft_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(10.0, 10.0));
  lm2_r2_f64 cut = lm2_r2_cut_left_f64(&rect, 3.0);

  EXPECT_DOUBLE_EQ(cut.min.x, 0.0);
  EXPECT_DOUBLE_EQ(cut.max.x, 3.0);
  EXPECT_DOUBLE_EQ(rect.min.x, 3.0);
  EXPECT_DOUBLE_EQ(rect.max.x, 10.0);
}

TEST_F(AABB2Test, CutRight_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(10.0, 10.0));
  lm2_r2_f64 cut = lm2_r2_cut_right_f64(&rect, 3.0);

  EXPECT_DOUBLE_EQ(cut.min.x, 7.0);
  EXPECT_DOUBLE_EQ(cut.max.x, 10.0);
  EXPECT_DOUBLE_EQ(rect.min.x, 0.0);
  EXPECT_DOUBLE_EQ(rect.max.x, 7.0);
}

TEST_F(AABB2Test, CutBottom_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(10.0, 10.0));
  lm2_r2_f64 cut = lm2_r2_cut_bottom_f64(&rect, 2.0);

  EXPECT_DOUBLE_EQ(cut.min.y, 0.0);
  EXPECT_DOUBLE_EQ(cut.max.y, 2.0);
  EXPECT_DOUBLE_EQ(rect.min.y, 2.0);
  EXPECT_DOUBLE_EQ(rect.max.y, 10.0);
}

TEST_F(AABB2Test, CutTop_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(10.0, 10.0));
  lm2_r2_f64 cut = lm2_r2_cut_top_f64(&rect, 2.0);

  EXPECT_DOUBLE_EQ(cut.min.y, 8.0);
  EXPECT_DOUBLE_EQ(cut.max.y, 10.0);
  EXPECT_DOUBLE_EQ(rect.min.y, 0.0);
  EXPECT_DOUBLE_EQ(rect.max.y, 8.0);
}

TEST_F(AABB2Test, Cut_Generic_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(10.0, 10.0));
  lm2_r2_f64 cut = lm2_r2_cut_f64(&rect, LM2_RECT_CUT_LEFT, 4.0);

  EXPECT_DOUBLE_EQ(cut.min.x, 0.0);
  EXPECT_DOUBLE_EQ(cut.max.x, 4.0);
  EXPECT_DOUBLE_EQ(rect.min.x, 4.0);
}

// =============================================================================
// Alignment Operations (f64)
// =============================================================================

TEST_F(AABB2Test, AlignSubrect_CenterCenter_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(10.0, 10.0));
  lm2_r2_f64 subrect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(2.0, 2.0));
  lm2_r2_f64 aligned = lm2_r2_align_subrect_f64(rect, subrect, LM2_ALIGN_CENTER, LM2_ALIGN_CENTER);

  EXPECT_DOUBLE_EQ(aligned.min.x, 4.0);
  EXPECT_DOUBLE_EQ(aligned.min.y, 4.0);
  EXPECT_DOUBLE_EQ(aligned.max.x, 6.0);
  EXPECT_DOUBLE_EQ(aligned.max.y, 6.0);
}

TEST_F(AABB2Test, AlignSubrect_StartStart_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(5.0, 5.0), lm2_v2_make_f64(15.0, 15.0));
  lm2_r2_f64 subrect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(2.0, 2.0));
  lm2_r2_f64 aligned = lm2_r2_align_subrect_f64(rect, subrect, LM2_ALIGN_START, LM2_ALIGN_START);

  EXPECT_DOUBLE_EQ(aligned.min.x, 5.0);
  EXPECT_DOUBLE_EQ(aligned.min.y, 5.0);
  EXPECT_DOUBLE_EQ(aligned.max.x, 7.0);
  EXPECT_DOUBLE_EQ(aligned.max.y, 7.0);
}

TEST_F(AABB2Test, AlignSubrect_EndEnd_F64) {
  lm2_r2_f64 rect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(10.0, 10.0));
  lm2_r2_f64 subrect = lm2_r2_from_min_max_f64(lm2_v2_make_f64(0.0, 0.0), lm2_v2_make_f64(2.0, 2.0));
  lm2_r2_f64 aligned = lm2_r2_align_subrect_f64(rect, subrect, LM2_ALIGN_END, LM2_ALIGN_END);

  EXPECT_DOUBLE_EQ(aligned.min.x, 8.0);
  EXPECT_DOUBLE_EQ(aligned.min.y, 8.0);
  EXPECT_DOUBLE_EQ(aligned.max.x, 10.0);
  EXPECT_DOUBLE_EQ(aligned.max.y, 10.0);
}

// =============================================================================
// F32 Sample Tests
// =============================================================================

TEST_F(AABB2Test, GetDim_F32) {
  lm2_r2_f32 rect = lm2_r2_from_min_max_f32(lm2_v2_make_f32(1.0f, 2.0f), lm2_v2_make_f32(5.0f, 8.0f));
  lm2_v2_f32 dim = lm2_r2_get_dim_f32(rect);
  EXPECT_FLOAT_EQ(dim.x, 4.0f);
  EXPECT_FLOAT_EQ(dim.y, 6.0f);
}

TEST_F(AABB2Test, OverlapRect_True_F32) {
  lm2_r2_f32 a = lm2_r2_from_min_max_f32(lm2_v2_make_f32(0.0f, 0.0f), lm2_v2_make_f32(5.0f, 5.0f));
  lm2_r2_f32 b = lm2_r2_from_min_max_f32(lm2_v2_make_f32(3.0f, 3.0f), lm2_v2_make_f32(8.0f, 8.0f));
  EXPECT_TRUE(lm2_r2_overlap_rect_f32(a, b));
}

TEST_F(AABB2Test, ScaleFromCenter_F32) {
  lm2_r2_f32 rect = lm2_r2_from_min_max_f32(lm2_v2_make_f32(0.0f, 0.0f), lm2_v2_make_f32(4.0f, 4.0f));
  lm2_v2_f32 scale = lm2_v2_make_f32(2.0f, 2.0f);
  lm2_r2_f32 scaled = lm2_r2_scale_from_center_f32(rect, scale);

  EXPECT_FLOAT_EQ(scaled.min.x, -2.0f);
  EXPECT_FLOAT_EQ(scaled.min.y, -2.0f);
  EXPECT_FLOAT_EQ(scaled.max.x, 6.0f);
  EXPECT_FLOAT_EQ(scaled.max.y, 6.0f);
}
