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

#pragma once

#include "lm2/lm2_base.h"
#include "lm2/ranges/lm2_range2.h"
#include "lm2/vectors/lm2_vector2.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// AABB2 Corner Enumerations
// =============================================================================

typedef enum lm2_corner2 {
  LM2_CORNER2_TOP_RIGHT,
  LM2_CORNER2_TOP_LEFT,
  LM2_CORNER2_BOTTOM_RIGHT,
  LM2_CORNER2_BOTTOM_LEFT,
} lm2_corner2;

typedef enum lm2_rect_cut {
  LM2_RECT_CUT_LEFT,
  LM2_RECT_CUT_RIGHT,
  LM2_RECT_CUT_TOP,
  LM2_RECT_CUT_BOTTOM,
} lm2_rect_cut;

typedef enum lm2_align {
  LM2_ALIGN_START,
  LM2_ALIGN_CENTER,
  LM2_ALIGN_END,
} lm2_align;

// =============================================================================
// AABB2 Operations for f64
// =============================================================================

// Corner operations
LM2_API lm2_v2_f64 lm2_r2_get_corner_f64(lm2_r2_f64 rect, lm2_corner2 corner);
LM2_API lm2_v2_f64 lm2_r2_get_bottom_left_f64(lm2_r2_f64 rect);
LM2_API lm2_v2_f64 lm2_r2_get_top_right_f64(lm2_r2_f64 rect);
LM2_API lm2_v2_f64 lm2_r2_get_bottom_right_f64(lm2_r2_f64 rect);
LM2_API lm2_v2_f64 lm2_r2_get_top_left_f64(lm2_r2_f64 rect);

// Transform operations
LM2_API lm2_r2_f64 lm2_r2_scale_from_center_f64(lm2_r2_f64 rect, lm2_v2_f64 scale);
LM2_API lm2_r2_f64 lm2_r2_scale_from_min_f64(lm2_r2_f64 rect, lm2_v2_f64 scale);
LM2_API lm2_r2_f64 lm2_r2_scale_from_max_f64(lm2_r2_f64 rect, lm2_v2_f64 scale);
LM2_API lm2_r2_f64 lm2_r2_shrink_vec_f64(lm2_r2_f64 rect, lm2_v2_f64 amount);
LM2_API lm2_r2_f64 lm2_r2_shrink_scalar_f64(lm2_r2_f64 rect, double amount);
LM2_API lm2_r2_f64 lm2_r2_inflate_vec_f64(lm2_r2_f64 rect, lm2_v2_f64 amount);
LM2_API lm2_r2_f64 lm2_r2_inflate_scalar_f64(lm2_r2_f64 rect, double amount);

// Query operations
LM2_API lm2_v2_f64 lm2_r2_get_dim_f64(lm2_r2_f64 rect);
LM2_API int lm2_r2_overlap_rect_f64(lm2_r2_f64 a, lm2_r2_f64 b);
LM2_API int lm2_r2_overlap_point_f64(lm2_r2_f64 rect, lm2_v2_f64 point);
LM2_API int lm2_r2_contains_f64(lm2_r2_f64 rect, lm2_r2_f64 subrect);
LM2_API double lm2_r2_distance_f64(lm2_r2_f64 rect, lm2_v2_f64 point);
LM2_API lm2_v2_f64 lm2_r2_get_closest_point_f64(lm2_r2_f64 rect, lm2_v2_f64 point);
LM2_API double lm2_r2_closest_distance_from_edges_f64(lm2_r2_f64 a, lm2_r2_f64 b);

// Cut operations
LM2_API lm2_r2_f64 lm2_r2_cut_f64(lm2_r2_f64* rect, lm2_rect_cut cut_type, double amount);
LM2_API lm2_r2_f64 lm2_r2_cut_left_f64(lm2_r2_f64* rect, double amount);
LM2_API lm2_r2_f64 lm2_r2_cut_right_f64(lm2_r2_f64* rect, double amount);
LM2_API lm2_r2_f64 lm2_r2_cut_bottom_f64(lm2_r2_f64* rect, double amount);
LM2_API lm2_r2_f64 lm2_r2_cut_top_f64(lm2_r2_f64* rect, double amount);

// Alignment
LM2_API lm2_r2_f64 lm2_r2_align_subrect_f64(lm2_r2_f64 rect, lm2_r2_f64 subrect, lm2_align align_x, lm2_align align_y);

// =============================================================================
// AABB2 Operations for f32
// =============================================================================

// Corner operations
LM2_API lm2_v2_f32 lm2_r2_get_corner_f32(lm2_r2_f32 rect, lm2_corner2 corner);
LM2_API lm2_v2_f32 lm2_r2_get_bottom_left_f32(lm2_r2_f32 rect);
LM2_API lm2_v2_f32 lm2_r2_get_top_right_f32(lm2_r2_f32 rect);
LM2_API lm2_v2_f32 lm2_r2_get_bottom_right_f32(lm2_r2_f32 rect);
LM2_API lm2_v2_f32 lm2_r2_get_top_left_f32(lm2_r2_f32 rect);

// Transform operations
LM2_API lm2_r2_f32 lm2_r2_scale_from_center_f32(lm2_r2_f32 rect, lm2_v2_f32 scale);
LM2_API lm2_r2_f32 lm2_r2_scale_from_min_f32(lm2_r2_f32 rect, lm2_v2_f32 scale);
LM2_API lm2_r2_f32 lm2_r2_scale_from_max_f32(lm2_r2_f32 rect, lm2_v2_f32 scale);
LM2_API lm2_r2_f32 lm2_r2_shrink_vec_f32(lm2_r2_f32 rect, lm2_v2_f32 amount);
LM2_API lm2_r2_f32 lm2_r2_shrink_scalar_f32(lm2_r2_f32 rect, float amount);
LM2_API lm2_r2_f32 lm2_r2_inflate_vec_f32(lm2_r2_f32 rect, lm2_v2_f32 amount);
LM2_API lm2_r2_f32 lm2_r2_inflate_scalar_f32(lm2_r2_f32 rect, float amount);

// Query operations
LM2_API lm2_v2_f32 lm2_r2_get_dim_f32(lm2_r2_f32 rect);
LM2_API int lm2_r2_overlap_rect_f32(lm2_r2_f32 a, lm2_r2_f32 b);
LM2_API int lm2_r2_overlap_point_f32(lm2_r2_f32 rect, lm2_v2_f32 point);
LM2_API int lm2_r2_contains_f32(lm2_r2_f32 rect, lm2_r2_f32 subrect);
LM2_API float lm2_r2_distance_f32(lm2_r2_f32 rect, lm2_v2_f32 point);
LM2_API lm2_v2_f32 lm2_r2_get_closest_point_f32(lm2_r2_f32 rect, lm2_v2_f32 point);
LM2_API float lm2_r2_closest_distance_from_edges_f32(lm2_r2_f32 a, lm2_r2_f32 b);

// Cut operations
LM2_API lm2_r2_f32 lm2_r2_cut_f32(lm2_r2_f32* rect, lm2_rect_cut cut_type, float amount);
LM2_API lm2_r2_f32 lm2_r2_cut_left_f32(lm2_r2_f32* rect, float amount);
LM2_API lm2_r2_f32 lm2_r2_cut_right_f32(lm2_r2_f32* rect, float amount);
LM2_API lm2_r2_f32 lm2_r2_cut_bottom_f32(lm2_r2_f32* rect, float amount);
LM2_API lm2_r2_f32 lm2_r2_cut_top_f32(lm2_r2_f32* rect, float amount);

// Alignment
LM2_API lm2_r2_f32 lm2_r2_align_subrect_f32(lm2_r2_f32 rect, lm2_r2_f32 subrect, lm2_align align_x, lm2_align align_y);

// =============================================================================
// AABB2 Operations for f64
// =============================================================================

// Corner operations
LM2_API lm2_v2_i64 lm2_r2_get_corner_i64(lm2_r2_i64 rect, lm2_corner2 corner);
LM2_API lm2_v2_i64 lm2_r2_get_bottom_left_i64(lm2_r2_i64 rect);
LM2_API lm2_v2_i64 lm2_r2_get_top_right_i64(lm2_r2_i64 rect);
LM2_API lm2_v2_i64 lm2_r2_get_bottom_right_i64(lm2_r2_i64 rect);
LM2_API lm2_v2_i64 lm2_r2_get_top_left_i64(lm2_r2_i64 rect);

// Transform operations
LM2_API lm2_r2_i64 lm2_r2_scale_from_center_i64(lm2_r2_i64 rect, lm2_v2_i64 scale);
LM2_API lm2_r2_i64 lm2_r2_scale_from_min_i64(lm2_r2_i64 rect, lm2_v2_i64 scale);
LM2_API lm2_r2_i64 lm2_r2_scale_from_max_i64(lm2_r2_i64 rect, lm2_v2_i64 scale);
LM2_API lm2_r2_i64 lm2_r2_shrink_vec_i64(lm2_r2_i64 rect, lm2_v2_i64 amount);
LM2_API lm2_r2_i64 lm2_r2_shrink_scalar_i64(lm2_r2_i64 rect, int64_t amount);
LM2_API lm2_r2_i64 lm2_r2_inflate_vec_i64(lm2_r2_i64 rect, lm2_v2_i64 amount);
LM2_API lm2_r2_i64 lm2_r2_inflate_scalar_i64(lm2_r2_i64 rect, int64_t amount);

// Query operations
LM2_API lm2_v2_i64 lm2_r2_get_dim_i64(lm2_r2_i64 rect);
LM2_API int lm2_r2_overlap_rect_i64(lm2_r2_i64 a, lm2_r2_i64 b);
LM2_API int lm2_r2_overlap_point_i64(lm2_r2_i64 rect, lm2_v2_i64 point);
LM2_API int lm2_r2_contains_i64(lm2_r2_i64 rect, lm2_r2_i64 subrect);
LM2_API int64_t lm2_r2_distance_i64(lm2_r2_i64 rect, lm2_v2_i64 point);
LM2_API lm2_v2_i64 lm2_r2_get_closest_point_i64(lm2_r2_i64 rect, lm2_v2_i64 point);
LM2_API int64_t lm2_r2_closest_distance_from_edges_i64(lm2_r2_i64 a, lm2_r2_i64 b);

// Cut operations
LM2_API lm2_r2_i64 lm2_r2_cut_i64(lm2_r2_i64* rect, lm2_rect_cut cut_type, int64_t amount);
LM2_API lm2_r2_i64 lm2_r2_cut_left_i64(lm2_r2_i64* rect, int64_t amount);
LM2_API lm2_r2_i64 lm2_r2_cut_right_i64(lm2_r2_i64* rect, int64_t amount);
LM2_API lm2_r2_i64 lm2_r2_cut_bottom_i64(lm2_r2_i64* rect, int64_t amount);
LM2_API lm2_r2_i64 lm2_r2_cut_top_i64(lm2_r2_i64* rect, int64_t amount);

// Alignment
LM2_API lm2_r2_i64 lm2_r2_align_subrect_i64(lm2_r2_i64 rect, lm2_r2_i64 subrect, lm2_align align_x, lm2_align align_y);

// =============================================================================
// AABB2 Operations for f32
// =============================================================================

// Corner operations
LM2_API lm2_v2_i32 lm2_r2_get_corner_i32(lm2_r2_i32 rect, lm2_corner2 corner);
LM2_API lm2_v2_i32 lm2_r2_get_bottom_left_i32(lm2_r2_i32 rect);
LM2_API lm2_v2_i32 lm2_r2_get_top_right_i32(lm2_r2_i32 rect);
LM2_API lm2_v2_i32 lm2_r2_get_bottom_right_i32(lm2_r2_i32 rect);
LM2_API lm2_v2_i32 lm2_r2_get_top_left_i32(lm2_r2_i32 rect);

// Transform operations
LM2_API lm2_r2_i32 lm2_r2_scale_from_center_i32(lm2_r2_i32 rect, lm2_v2_i32 scale);
LM2_API lm2_r2_i32 lm2_r2_scale_from_min_i32(lm2_r2_i32 rect, lm2_v2_i32 scale);
LM2_API lm2_r2_i32 lm2_r2_scale_from_max_i32(lm2_r2_i32 rect, lm2_v2_i32 scale);
LM2_API lm2_r2_i32 lm2_r2_shrink_vec_i32(lm2_r2_i32 rect, lm2_v2_i32 amount);
LM2_API lm2_r2_i32 lm2_r2_shrink_scalar_i32(lm2_r2_i32 rect, int32_t amount);
LM2_API lm2_r2_i32 lm2_r2_inflate_vec_i32(lm2_r2_i32 rect, lm2_v2_i32 amount);
LM2_API lm2_r2_i32 lm2_r2_inflate_scalar_i32(lm2_r2_i32 rect, int32_t amount);

// Query operations
LM2_API lm2_v2_i32 lm2_r2_get_dim_i32(lm2_r2_i32 rect);
LM2_API int lm2_r2_overlap_rect_i32(lm2_r2_i32 a, lm2_r2_i32 b);
LM2_API int lm2_r2_overlap_point_i32(lm2_r2_i32 rect, lm2_v2_i32 point);
LM2_API int lm2_r2_contains_i32(lm2_r2_i32 rect, lm2_r2_i32 subrect);
LM2_API int32_t lm2_r2_distance_i32(lm2_r2_i32 rect, lm2_v2_i32 point);
LM2_API lm2_v2_i32 lm2_r2_get_closest_point_i32(lm2_r2_i32 rect, lm2_v2_i32 point);
LM2_API int32_t lm2_r2_closest_distance_from_edges_i32(lm2_r2_i32 a, lm2_r2_i32 b);

// Cut operations
LM2_API lm2_r2_i32 lm2_r2_cut_i32(lm2_r2_i32* rect, lm2_rect_cut cut_type, int32_t amount);
LM2_API lm2_r2_i32 lm2_r2_cut_left_i32(lm2_r2_i32* rect, int32_t amount);
LM2_API lm2_r2_i32 lm2_r2_cut_right_i32(lm2_r2_i32* rect, int32_t amount);
LM2_API lm2_r2_i32 lm2_r2_cut_bottom_i32(lm2_r2_i32* rect, int32_t amount);
LM2_API lm2_r2_i32 lm2_r2_cut_top_i32(lm2_r2_i32* rect, int32_t amount);

// Alignment
LM2_API lm2_r2_i32 lm2_r2_align_subrect_i32(lm2_r2_i32 rect, lm2_r2_i32 subrect, lm2_align align_x, lm2_align align_y);

// =============================================================================
// AABB2 Operations for i16
// =============================================================================

// Corner operations
LM2_API lm2_v2_i16 lm2_r2_get_corner_i16(lm2_r2_i16 rect, lm2_corner2 corner);
LM2_API lm2_v2_i16 lm2_r2_get_bottom_left_i16(lm2_r2_i16 rect);
LM2_API lm2_v2_i16 lm2_r2_get_top_right_i16(lm2_r2_i16 rect);
LM2_API lm2_v2_i16 lm2_r2_get_bottom_right_i16(lm2_r2_i16 rect);
LM2_API lm2_v2_i16 lm2_r2_get_top_left_i16(lm2_r2_i16 rect);

// Transform operations
LM2_API lm2_r2_i16 lm2_r2_scale_from_center_i16(lm2_r2_i16 rect, lm2_v2_i16 scale);
LM2_API lm2_r2_i16 lm2_r2_scale_from_min_i16(lm2_r2_i16 rect, lm2_v2_i16 scale);
LM2_API lm2_r2_i16 lm2_r2_scale_from_max_i16(lm2_r2_i16 rect, lm2_v2_i16 scale);
LM2_API lm2_r2_i16 lm2_r2_shrink_vec_i16(lm2_r2_i16 rect, lm2_v2_i16 amount);
LM2_API lm2_r2_i16 lm2_r2_shrink_scalar_i16(lm2_r2_i16 rect, int16_t amount);
LM2_API lm2_r2_i16 lm2_r2_inflate_vec_i16(lm2_r2_i16 rect, lm2_v2_i16 amount);
LM2_API lm2_r2_i16 lm2_r2_inflate_scalar_i16(lm2_r2_i16 rect, int16_t amount);

// Query operations
LM2_API lm2_v2_i16 lm2_r2_get_dim_i16(lm2_r2_i16 rect);
LM2_API int lm2_r2_overlap_rect_i16(lm2_r2_i16 a, lm2_r2_i16 b);
LM2_API int lm2_r2_overlap_point_i16(lm2_r2_i16 rect, lm2_v2_i16 point);
LM2_API int lm2_r2_contains_i16(lm2_r2_i16 rect, lm2_r2_i16 subrect);
LM2_API int16_t lm2_r2_distance_i16(lm2_r2_i16 rect, lm2_v2_i16 point);
LM2_API lm2_v2_i16 lm2_r2_get_closest_point_i16(lm2_r2_i16 rect, lm2_v2_i16 point);
LM2_API int16_t lm2_r2_closest_distance_from_edges_i16(lm2_r2_i16 a, lm2_r2_i16 b);

// Cut operations
LM2_API lm2_r2_i16 lm2_r2_cut_i16(lm2_r2_i16* rect, lm2_rect_cut cut_type, int16_t amount);
LM2_API lm2_r2_i16 lm2_r2_cut_left_i16(lm2_r2_i16* rect, int16_t amount);
LM2_API lm2_r2_i16 lm2_r2_cut_right_i16(lm2_r2_i16* rect, int16_t amount);
LM2_API lm2_r2_i16 lm2_r2_cut_bottom_i16(lm2_r2_i16* rect, int16_t amount);
LM2_API lm2_r2_i16 lm2_r2_cut_top_i16(lm2_r2_i16* rect, int16_t amount);

// Alignment
LM2_API lm2_r2_i16 lm2_r2_align_subrect_i16(lm2_r2_i16 rect, lm2_r2_i16 subrect, lm2_align align_x, lm2_align align_y);

// =============================================================================
// AABB2 Operations for i8
// =============================================================================

// Corner operations
LM2_API lm2_v2_i8 lm2_r2_get_corner_i8(lm2_r2_i8 rect, lm2_corner2 corner);
LM2_API lm2_v2_i8 lm2_r2_get_bottom_left_i8(lm2_r2_i8 rect);
LM2_API lm2_v2_i8 lm2_r2_get_top_right_i8(lm2_r2_i8 rect);
LM2_API lm2_v2_i8 lm2_r2_get_bottom_right_i8(lm2_r2_i8 rect);
LM2_API lm2_v2_i8 lm2_r2_get_top_left_i8(lm2_r2_i8 rect);

// Transform operations
LM2_API lm2_r2_i8 lm2_r2_scale_from_center_i8(lm2_r2_i8 rect, lm2_v2_i8 scale);
LM2_API lm2_r2_i8 lm2_r2_scale_from_min_i8(lm2_r2_i8 rect, lm2_v2_i8 scale);
LM2_API lm2_r2_i8 lm2_r2_scale_from_max_i8(lm2_r2_i8 rect, lm2_v2_i8 scale);
LM2_API lm2_r2_i8 lm2_r2_shrink_vec_i8(lm2_r2_i8 rect, lm2_v2_i8 amount);
LM2_API lm2_r2_i8 lm2_r2_shrink_scalar_i8(lm2_r2_i8 rect, int8_t amount);
LM2_API lm2_r2_i8 lm2_r2_inflate_vec_i8(lm2_r2_i8 rect, lm2_v2_i8 amount);
LM2_API lm2_r2_i8 lm2_r2_inflate_scalar_i8(lm2_r2_i8 rect, int8_t amount);

// Query operations
LM2_API lm2_v2_i8 lm2_r2_get_dim_i8(lm2_r2_i8 rect);
LM2_API int lm2_r2_overlap_rect_i8(lm2_r2_i8 a, lm2_r2_i8 b);
LM2_API int lm2_r2_overlap_point_i8(lm2_r2_i8 rect, lm2_v2_i8 point);
LM2_API int lm2_r2_contains_i8(lm2_r2_i8 rect, lm2_r2_i8 subrect);
LM2_API int8_t lm2_r2_distance_i8(lm2_r2_i8 rect, lm2_v2_i8 point);
LM2_API lm2_v2_i8 lm2_r2_get_closest_point_i8(lm2_r2_i8 rect, lm2_v2_i8 point);
LM2_API int8_t lm2_r2_closest_distance_from_edges_i8(lm2_r2_i8 a, lm2_r2_i8 b);

// Cut operations
LM2_API lm2_r2_i8 lm2_r2_cut_i8(lm2_r2_i8* rect, lm2_rect_cut cut_type, int8_t amount);
LM2_API lm2_r2_i8 lm2_r2_cut_left_i8(lm2_r2_i8* rect, int8_t amount);
LM2_API lm2_r2_i8 lm2_r2_cut_right_i8(lm2_r2_i8* rect, int8_t amount);
LM2_API lm2_r2_i8 lm2_r2_cut_bottom_i8(lm2_r2_i8* rect, int8_t amount);
LM2_API lm2_r2_i8 lm2_r2_cut_top_i8(lm2_r2_i8* rect, int8_t amount);

// Alignment
LM2_API lm2_r2_i8 lm2_r2_align_subrect_i8(lm2_r2_i8 rect, lm2_r2_i8 subrect, lm2_align align_x, lm2_align align_y);

// =============================================================================
// AABB2 Operations for i64
// =============================================================================

// Corner operations
LM2_API lm2_v2_u64 lm2_r2_get_corner_u64(lm2_r2_u64 rect, lm2_corner2 corner);
LM2_API lm2_v2_u64 lm2_r2_get_bottom_left_u64(lm2_r2_u64 rect);
LM2_API lm2_v2_u64 lm2_r2_get_top_right_u64(lm2_r2_u64 rect);
LM2_API lm2_v2_u64 lm2_r2_get_bottom_right_u64(lm2_r2_u64 rect);
LM2_API lm2_v2_u64 lm2_r2_get_top_left_u64(lm2_r2_u64 rect);

// Transform operations
LM2_API lm2_r2_u64 lm2_r2_scale_from_center_u64(lm2_r2_u64 rect, lm2_v2_u64 scale);
LM2_API lm2_r2_u64 lm2_r2_scale_from_min_u64(lm2_r2_u64 rect, lm2_v2_u64 scale);
LM2_API lm2_r2_u64 lm2_r2_scale_from_max_u64(lm2_r2_u64 rect, lm2_v2_u64 scale);
LM2_API lm2_r2_u64 lm2_r2_shrink_vec_u64(lm2_r2_u64 rect, lm2_v2_u64 amount);
LM2_API lm2_r2_u64 lm2_r2_shrink_scalar_u64(lm2_r2_u64 rect, uint64_t amount);
LM2_API lm2_r2_u64 lm2_r2_inflate_vec_u64(lm2_r2_u64 rect, lm2_v2_u64 amount);
LM2_API lm2_r2_u64 lm2_r2_inflate_scalar_u64(lm2_r2_u64 rect, uint64_t amount);

// Query operations
LM2_API lm2_v2_u64 lm2_r2_get_dim_u64(lm2_r2_u64 rect);
LM2_API int lm2_r2_overlap_rect_u64(lm2_r2_u64 a, lm2_r2_u64 b);
LM2_API int lm2_r2_overlap_point_u64(lm2_r2_u64 rect, lm2_v2_u64 point);
LM2_API int lm2_r2_contains_u64(lm2_r2_u64 rect, lm2_r2_u64 subrect);
LM2_API uint64_t lm2_r2_distance_u64(lm2_r2_u64 rect, lm2_v2_u64 point);
LM2_API lm2_v2_u64 lm2_r2_get_closest_point_u64(lm2_r2_u64 rect, lm2_v2_u64 point);
LM2_API uint64_t lm2_r2_closest_distance_from_edges_u64(lm2_r2_u64 a, lm2_r2_u64 b);

// Cut operations
LM2_API lm2_r2_u64 lm2_r2_cut_u64(lm2_r2_u64* rect, lm2_rect_cut cut_type, uint64_t amount);
LM2_API lm2_r2_u64 lm2_r2_cut_left_u64(lm2_r2_u64* rect, uint64_t amount);
LM2_API lm2_r2_u64 lm2_r2_cut_right_u64(lm2_r2_u64* rect, uint64_t amount);
LM2_API lm2_r2_u64 lm2_r2_cut_bottom_u64(lm2_r2_u64* rect, uint64_t amount);
LM2_API lm2_r2_u64 lm2_r2_cut_top_u64(lm2_r2_u64* rect, uint64_t amount);

// Alignment
LM2_API lm2_r2_u64 lm2_r2_align_subrect_u64(lm2_r2_u64 rect, lm2_r2_u64 subrect, lm2_align align_x, lm2_align align_y);

// =============================================================================
// AABB2 Operations for i32
// =============================================================================

// Corner operations
LM2_API lm2_v2_u32 lm2_r2_get_corner_u32(lm2_r2_u32 rect, lm2_corner2 corner);
LM2_API lm2_v2_u32 lm2_r2_get_bottom_left_u32(lm2_r2_u32 rect);
LM2_API lm2_v2_u32 lm2_r2_get_top_right_u32(lm2_r2_u32 rect);
LM2_API lm2_v2_u32 lm2_r2_get_bottom_right_u32(lm2_r2_u32 rect);
LM2_API lm2_v2_u32 lm2_r2_get_top_left_u32(lm2_r2_u32 rect);

// Transform operations
LM2_API lm2_r2_u32 lm2_r2_scale_from_center_u32(lm2_r2_u32 rect, lm2_v2_u32 scale);
LM2_API lm2_r2_u32 lm2_r2_scale_from_min_u32(lm2_r2_u32 rect, lm2_v2_u32 scale);
LM2_API lm2_r2_u32 lm2_r2_scale_from_max_u32(lm2_r2_u32 rect, lm2_v2_u32 scale);
LM2_API lm2_r2_u32 lm2_r2_shrink_vec_u32(lm2_r2_u32 rect, lm2_v2_u32 amount);
LM2_API lm2_r2_u32 lm2_r2_shrink_scalar_u32(lm2_r2_u32 rect, uint32_t amount);
LM2_API lm2_r2_u32 lm2_r2_inflate_vec_u32(lm2_r2_u32 rect, lm2_v2_u32 amount);
LM2_API lm2_r2_u32 lm2_r2_inflate_scalar_u32(lm2_r2_u32 rect, uint32_t amount);

// Query operations
LM2_API lm2_v2_u32 lm2_r2_get_dim_u32(lm2_r2_u32 rect);
LM2_API int lm2_r2_overlap_rect_u32(lm2_r2_u32 a, lm2_r2_u32 b);
LM2_API int lm2_r2_overlap_point_u32(lm2_r2_u32 rect, lm2_v2_u32 point);
LM2_API int lm2_r2_contains_u32(lm2_r2_u32 rect, lm2_r2_u32 subrect);
LM2_API uint32_t lm2_r2_distance_u32(lm2_r2_u32 rect, lm2_v2_u32 point);
LM2_API lm2_v2_u32 lm2_r2_get_closest_point_u32(lm2_r2_u32 rect, lm2_v2_u32 point);
LM2_API uint32_t lm2_r2_closest_distance_from_edges_u32(lm2_r2_u32 a, lm2_r2_u32 b);

// Cut operations
LM2_API lm2_r2_u32 lm2_r2_cut_u32(lm2_r2_u32* rect, lm2_rect_cut cut_type, uint32_t amount);
LM2_API lm2_r2_u32 lm2_r2_cut_left_u32(lm2_r2_u32* rect, uint32_t amount);
LM2_API lm2_r2_u32 lm2_r2_cut_right_u32(lm2_r2_u32* rect, uint32_t amount);
LM2_API lm2_r2_u32 lm2_r2_cut_bottom_u32(lm2_r2_u32* rect, uint32_t amount);
LM2_API lm2_r2_u32 lm2_r2_cut_top_u32(lm2_r2_u32* rect, uint32_t amount);

// Alignment
LM2_API lm2_r2_u32 lm2_r2_align_subrect_u32(lm2_r2_u32 rect, lm2_r2_u32 subrect, lm2_align align_x, lm2_align align_y);

// =============================================================================
// AABB2rations for u32
// =============================================================================

// Corner operations
LM2_API lm2_v2_u16 lm2_r2_get_corner_u16(lm2_r2_u16 rect, lm2_corner2 corner);
LM2_API lm2_v2_u16 lm2_r2_get_bottom_left_u16(lm2_r2_u16 rect);
LM2_API lm2_v2_u16 lm2_r2_get_top_right_u16(lm2_r2_u16 rect);
LM2_API lm2_v2_u16 lm2_r2_get_bottom_right_u16(lm2_r2_u16 rect);
LM2_API lm2_v2_u16 lm2_r2_get_top_left_u16(lm2_r2_u16 rect);

// Transform operations
LM2_API lm2_r2_u16 lm2_r2_scale_from_center_u16(lm2_r2_u16 rect, lm2_v2_u16 scale);
LM2_API lm2_r2_u16 lm2_r2_scale_from_min_u16(lm2_r2_u16 rect, lm2_v2_u16 scale);
LM2_API lm2_r2_u16 lm2_r2_scale_from_max_u16(lm2_r2_u16 rect, lm2_v2_u16 scale);
LM2_API lm2_r2_u16 lm2_r2_shrink_vec_u16(lm2_r2_u16 rect, lm2_v2_u16 amount);
LM2_API lm2_r2_u16 lm2_r2_shrink_scalar_u16(lm2_r2_u16 rect, uint16_t amount);
LM2_API lm2_r2_u16 lm2_r2_inflate_vec_u16(lm2_r2_u16 rect, lm2_v2_u16 amount);
LM2_API lm2_r2_u16 lm2_r2_inflate_scalar_u16(lm2_r2_u16 rect, uint16_t amount);

// Query operations
LM2_API lm2_v2_u16 lm2_r2_get_dim_u16(lm2_r2_u16 rect);
LM2_API int lm2_r2_overlap_rect_u16(lm2_r2_u16 a, lm2_r2_u16 b);
LM2_API int lm2_r2_overlap_point_u16(lm2_r2_u16 rect, lm2_v2_u16 point);
LM2_API int lm2_r2_contains_u16(lm2_r2_u16 rect, lm2_r2_u16 subrect);
LM2_API uint16_t lm2_r2_distance_u16(lm2_r2_u16 rect, lm2_v2_u16 point);
LM2_API lm2_v2_u16 lm2_r2_get_closest_point_u16(lm2_r2_u16 rect, lm2_v2_u16 point);
LM2_API uint16_t lm2_r2_closest_distance_from_edges_u16(lm2_r2_u16 a, lm2_r2_u16 b);

// Cut operations
LM2_API lm2_r2_u16 lm2_r2_cut_u16(lm2_r2_u16* rect, lm2_rect_cut cut_type, uint16_t amount);
LM2_API lm2_r2_u16 lm2_r2_cut_left_u16(lm2_r2_u16* rect, uint16_t amount);
LM2_API lm2_r2_u16 lm2_r2_cut_right_u16(lm2_r2_u16* rect, uint16_t amount);
LM2_API lm2_r2_u16 lm2_r2_cut_bottom_u16(lm2_r2_u16* rect, uint16_t amount);
LM2_API lm2_r2_u16 lm2_r2_cut_top_u16(lm2_r2_u16* rect, uint16_t amount);

// Alignment
LM2_API lm2_r2_u16 lm2_r2_align_subrect_u16(lm2_r2_u16 rect, lm2_r2_u16 subrect, lm2_align align_x, lm2_align align_y);

// =============================================================================
// AABB2 Operations for u8
// =============================================================================

// Corner operations
LM2_API lm2_v2_u8 lm2_r2_get_corner_u8(lm2_r2_u8 rect, lm2_corner2 corner);
LM2_API lm2_v2_u8 lm2_r2_get_bottom_left_u8(lm2_r2_u8 rect);
LM2_API lm2_v2_u8 lm2_r2_get_top_right_u8(lm2_r2_u8 rect);
LM2_API lm2_v2_u8 lm2_r2_get_bottom_right_u8(lm2_r2_u8 rect);
LM2_API lm2_v2_u8 lm2_r2_get_top_left_u8(lm2_r2_u8 rect);

// Transform operations
LM2_API lm2_r2_u8 lm2_r2_scale_from_center_u8(lm2_r2_u8 rect, lm2_v2_u8 scale);
LM2_API lm2_r2_u8 lm2_r2_scale_from_min_u8(lm2_r2_u8 rect, lm2_v2_u8 scale);
LM2_API lm2_r2_u8 lm2_r2_scale_from_max_u8(lm2_r2_u8 rect, lm2_v2_u8 scale);
LM2_API lm2_r2_u8 lm2_r2_shrink_vec_u8(lm2_r2_u8 rect, lm2_v2_u8 amount);
LM2_API lm2_r2_u8 lm2_r2_shrink_scalar_u8(lm2_r2_u8 rect, uint8_t amount);
LM2_API lm2_r2_u8 lm2_r2_inflate_vec_u8(lm2_r2_u8 rect, lm2_v2_u8 amount);
LM2_API lm2_r2_u8 lm2_r2_inflate_scalar_u8(lm2_r2_u8 rect, uint8_t amount);

// Query operations
LM2_API lm2_v2_u8 lm2_r2_get_dim_u8(lm2_r2_u8 rect);
LM2_API int lm2_r2_overlap_rect_u8(lm2_r2_u8 a, lm2_r2_u8 b);
LM2_API int lm2_r2_overlap_point_u8(lm2_r2_u8 rect, lm2_v2_u8 point);
LM2_API int lm2_r2_contains_u8(lm2_r2_u8 rect, lm2_r2_u8 subrect);
LM2_API uint8_t lm2_r2_distance_u8(lm2_r2_u8 rect, lm2_v2_u8 point);
LM2_API lm2_v2_u8 lm2_r2_get_closest_point_u8(lm2_r2_u8 rect, lm2_v2_u8 point);
LM2_API uint8_t lm2_r2_closest_distance_from_edges_u8(lm2_r2_u8 a, lm2_r2_u8 b);

// Cut operations
LM2_API lm2_r2_u8 lm2_r2_cut_u8(lm2_r2_u8* rect, lm2_rect_cut cut_type, uint8_t amount);
LM2_API lm2_r2_u8 lm2_r2_cut_left_u8(lm2_r2_u8* rect, uint8_t amount);
LM2_API lm2_r2_u8 lm2_r2_cut_right_u8(lm2_r2_u8* rect, uint8_t amount);
LM2_API lm2_r2_u8 lm2_r2_cut_bottom_u8(lm2_r2_u8* rect, uint8_t amount);
LM2_API lm2_r2_u8 lm2_r2_cut_top_u8(lm2_r2_u8* rect, uint8_t amount);

// Alignment
LM2_API lm2_r2_u8 lm2_r2_align_subrect_u8(lm2_r2_u8 rect, lm2_r2_u8 subrect, lm2_align align_x, lm2_align align_y);

// =============================================================================
// Segment Intersection Functions for All Vector Types
// =============================================================================

LM2_API int lm2_segments_intersect_f64(lm2_v2_f64 a0, lm2_v2_f64 a1, lm2_v2_f64 b0, lm2_v2_f64 b1);
LM2_API int lm2_segments_intersect_f32(lm2_v2_f32 a0, lm2_v2_f32 a1, lm2_v2_f32 b0, lm2_v2_f32 b1);
LM2_API int lm2_segments_intersect_i64(lm2_v2_i64 a0, lm2_v2_i64 a1, lm2_v2_i64 b0, lm2_v2_i64 b1);
LM2_API int lm2_segments_intersect_i32(lm2_v2_i32 a0, lm2_v2_i32 a1, lm2_v2_i32 b0, lm2_v2_i32 b1);
LM2_API int lm2_segments_intersect_i16(lm2_v2_i16 a0, lm2_v2_i16 a1, lm2_v2_i16 b0, lm2_v2_i16 b1);
LM2_API int lm2_segments_intersect_i8(lm2_v2_i8 a0, lm2_v2_i8 a1, lm2_v2_i8 b0, lm2_v2_i8 b1);
LM2_API int lm2_segments_intersect_u64(lm2_v2_u64 a0, lm2_v2_u64 a1, lm2_v2_u64 b0, lm2_v2_u64 b1);
LM2_API int lm2_segments_intersect_u32(lm2_v2_u32 a0, lm2_v2_u32 a1, lm2_v2_u32 b0, lm2_v2_u32 b1);
LM2_API int lm2_segments_intersect_u16(lm2_v2_u16 a0, lm2_v2_u16 a1, lm2_v2_u16 b0, lm2_v2_u16 b1);
LM2_API int lm2_segments_intersect_u8(lm2_v2_u8 a0, lm2_v2_u8 a1, lm2_v2_u8 b0, lm2_v2_u8 b1);

// =============================================================================
// Convenience typedefs
// =============================================================================

// The range2 types are the AABB2 types (axis-aligned bounding boxes)
typedef lm2_r2_f64 lm2_aabb2_f64;
typedef lm2_r2_f32 lm2_aabb2_f32;
typedef lm2_r2_i64 lm2_aabb2_i64;
typedef lm2_r2_i32 lm2_aabb2_i32;
typedef lm2_r2_i16 lm2_aabb2_i16;
typedef lm2_r2_i8 lm2_aabb2_i8;
typedef lm2_r2_u64 lm2_aabb2_u64;
typedef lm2_r2_u32 lm2_aabb2_u32;
typedef lm2_r2_u16 lm2_aabb2_u16;
typedef lm2_r2_u8 lm2_aabb2_u8;

// Default AABB2 type (float-based)
typedef lm2_r2_f32 lm2_aabb2;

// #############################################################################
LM2_HEADER_END;