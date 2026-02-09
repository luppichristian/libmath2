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
// Rectangle Corner Enumerations
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
// Rectangle Operations for f64
// =============================================================================

// Corner operations
LM2_API lm2_v2f64 lm2_r2f64_get_corner(lm2_r2f64 rect, lm2_corner2 corner);
LM2_API lm2_v2f64 lm2_r2f64_get_bottom_left(lm2_r2f64 rect);
LM2_API lm2_v2f64 lm2_r2f64_get_top_right(lm2_r2f64 rect);
LM2_API lm2_v2f64 lm2_r2f64_get_bottom_right(lm2_r2f64 rect);
LM2_API lm2_v2f64 lm2_r2f64_get_top_left(lm2_r2f64 rect);

// Transform operations
LM2_API lm2_r2f64 lm2_r2f64_scale_from_center(lm2_r2f64 rect, lm2_v2f64 scale);
LM2_API lm2_r2f64 lm2_r2f64_scale_from_min(lm2_r2f64 rect, lm2_v2f64 scale);
LM2_API lm2_r2f64 lm2_r2f64_scale_from_max(lm2_r2f64 rect, lm2_v2f64 scale);
LM2_API lm2_r2f64 lm2_r2f64_shrink_vec(lm2_r2f64 rect, lm2_v2f64 amount);
LM2_API lm2_r2f64 lm2_r2f64_shrink_scalar(lm2_r2f64 rect, double amount);
LM2_API lm2_r2f64 lm2_r2f64_inflate_vec(lm2_r2f64 rect, lm2_v2f64 amount);
LM2_API lm2_r2f64 lm2_r2f64_inflate_scalar(lm2_r2f64 rect, double amount);

// Query operations
LM2_API lm2_v2f64 lm2_r2f64_get_dim(lm2_r2f64 rect);
LM2_API int lm2_r2f64_overlap_rect(lm2_r2f64 a, lm2_r2f64 b);
LM2_API int lm2_r2f64_overlap_point(lm2_r2f64 rect, lm2_v2f64 point);
LM2_API int lm2_r2f64_contains(lm2_r2f64 rect, lm2_r2f64 subrect);
LM2_API double lm2_r2f64_distance(lm2_r2f64 rect, lm2_v2f64 point);
LM2_API lm2_v2f64 lm2_r2f64_get_closest_point(lm2_r2f64 rect, lm2_v2f64 point);
LM2_API double lm2_r2f64_closest_distance_from_edges(lm2_r2f64 a, lm2_r2f64 b);

// Cut operations
LM2_API lm2_r2f64 lm2_r2f64_cut(lm2_r2f64* rect, lm2_rect_cut cut_type, double amount);
LM2_API lm2_r2f64 lm2_r2f64_cut_left(lm2_r2f64* rect, double amount);
LM2_API lm2_r2f64 lm2_r2f64_cut_right(lm2_r2f64* rect, double amount);
LM2_API lm2_r2f64 lm2_r2f64_cut_bottom(lm2_r2f64* rect, double amount);
LM2_API lm2_r2f64 lm2_r2f64_cut_top(lm2_r2f64* rect, double amount);

// Alignment
LM2_API lm2_r2f64 lm2_r2f64_align_subrect(lm2_r2f64 rect, lm2_r2f64 subrect, lm2_align align_x, lm2_align align_y);

// =============================================================================
// Rectangle Operations for f32
// =============================================================================

// Corner operations
LM2_API lm2_v2f32 lm2_r2f32_get_corner(lm2_r2f32 rect, lm2_corner2 corner);
LM2_API lm2_v2f32 lm2_r2f32_get_bottom_left(lm2_r2f32 rect);
LM2_API lm2_v2f32 lm2_r2f32_get_top_right(lm2_r2f32 rect);
LM2_API lm2_v2f32 lm2_r2f32_get_bottom_right(lm2_r2f32 rect);
LM2_API lm2_v2f32 lm2_r2f32_get_top_left(lm2_r2f32 rect);

// Transform operations
LM2_API lm2_r2f32 lm2_r2f32_scale_from_center(lm2_r2f32 rect, lm2_v2f32 scale);
LM2_API lm2_r2f32 lm2_r2f32_scale_from_min(lm2_r2f32 rect, lm2_v2f32 scale);
LM2_API lm2_r2f32 lm2_r2f32_scale_from_max(lm2_r2f32 rect, lm2_v2f32 scale);
LM2_API lm2_r2f32 lm2_r2f32_shrink_vec(lm2_r2f32 rect, lm2_v2f32 amount);
LM2_API lm2_r2f32 lm2_r2f32_shrink_scalar(lm2_r2f32 rect, float amount);
LM2_API lm2_r2f32 lm2_r2f32_inflate_vec(lm2_r2f32 rect, lm2_v2f32 amount);
LM2_API lm2_r2f32 lm2_r2f32_inflate_scalar(lm2_r2f32 rect, float amount);

// Query operations
LM2_API lm2_v2f32 lm2_r2f32_get_dim(lm2_r2f32 rect);
LM2_API int lm2_r2f32_overlap_rect(lm2_r2f32 a, lm2_r2f32 b);
LM2_API int lm2_r2f32_overlap_point(lm2_r2f32 rect, lm2_v2f32 point);
LM2_API int lm2_r2f32_contains(lm2_r2f32 rect, lm2_r2f32 subrect);
LM2_API float lm2_r2f32_distance(lm2_r2f32 rect, lm2_v2f32 point);
LM2_API lm2_v2f32 lm2_r2f32_get_closest_point(lm2_r2f32 rect, lm2_v2f32 point);
LM2_API float lm2_r2f32_closest_distance_from_edges(lm2_r2f32 a, lm2_r2f32 b);

// Cut operations
LM2_API lm2_r2f32 lm2_r2f32_cut(lm2_r2f32* rect, lm2_rect_cut cut_type, float amount);
LM2_API lm2_r2f32 lm2_r2f32_cut_left(lm2_r2f32* rect, float amount);
LM2_API lm2_r2f32 lm2_r2f32_cut_right(lm2_r2f32* rect, float amount);
LM2_API lm2_r2f32 lm2_r2f32_cut_bottom(lm2_r2f32* rect, float amount);
LM2_API lm2_r2f32 lm2_r2f32_cut_top(lm2_r2f32* rect, float amount);

// Alignment
LM2_API lm2_r2f32 lm2_r2f32_align_subrect(lm2_r2f32 rect, lm2_r2f32 subrect, lm2_align align_x, lm2_align align_y);

// =============================================================================
// Rectangle Operations for i64
// =============================================================================

// Corner operations
LM2_API lm2_v2i64 lm2_r2i64_get_corner(lm2_r2i64 rect, lm2_corner2 corner);
LM2_API lm2_v2i64 lm2_r2i64_get_bottom_left(lm2_r2i64 rect);
LM2_API lm2_v2i64 lm2_r2i64_get_top_right(lm2_r2i64 rect);
LM2_API lm2_v2i64 lm2_r2i64_get_bottom_right(lm2_r2i64 rect);
LM2_API lm2_v2i64 lm2_r2i64_get_top_left(lm2_r2i64 rect);

// Transform operations
LM2_API lm2_r2i64 lm2_r2i64_scale_from_center(lm2_r2i64 rect, lm2_v2i64 scale);
LM2_API lm2_r2i64 lm2_r2i64_scale_from_min(lm2_r2i64 rect, lm2_v2i64 scale);
LM2_API lm2_r2i64 lm2_r2i64_scale_from_max(lm2_r2i64 rect, lm2_v2i64 scale);
LM2_API lm2_r2i64 lm2_r2i64_shrink_vec(lm2_r2i64 rect, lm2_v2i64 amount);
LM2_API lm2_r2i64 lm2_r2i64_shrink_scalar(lm2_r2i64 rect, int64_t amount);
LM2_API lm2_r2i64 lm2_r2i64_inflate_vec(lm2_r2i64 rect, lm2_v2i64 amount);
LM2_API lm2_r2i64 lm2_r2i64_inflate_scalar(lm2_r2i64 rect, int64_t amount);

// Query operations
LM2_API lm2_v2i64 lm2_r2i64_get_dim(lm2_r2i64 rect);
LM2_API int lm2_r2i64_overlap_rect(lm2_r2i64 a, lm2_r2i64 b);
LM2_API int lm2_r2i64_overlap_point(lm2_r2i64 rect, lm2_v2i64 point);
LM2_API int lm2_r2i64_contains(lm2_r2i64 rect, lm2_r2i64 subrect);
LM2_API int64_t lm2_r2i64_distance(lm2_r2i64 rect, lm2_v2i64 point);
LM2_API lm2_v2i64 lm2_r2i64_get_closest_point(lm2_r2i64 rect, lm2_v2i64 point);
LM2_API int64_t lm2_r2i64_closest_distance_from_edges(lm2_r2i64 a, lm2_r2i64 b);

// Cut operations
LM2_API lm2_r2i64 lm2_r2i64_cut(lm2_r2i64* rect, lm2_rect_cut cut_type, int64_t amount);
LM2_API lm2_r2i64 lm2_r2i64_cut_left(lm2_r2i64* rect, int64_t amount);
LM2_API lm2_r2i64 lm2_r2i64_cut_right(lm2_r2i64* rect, int64_t amount);
LM2_API lm2_r2i64 lm2_r2i64_cut_bottom(lm2_r2i64* rect, int64_t amount);
LM2_API lm2_r2i64 lm2_r2i64_cut_top(lm2_r2i64* rect, int64_t amount);

// Alignment
LM2_API lm2_r2i64 lm2_r2i64_align_subrect(lm2_r2i64 rect, lm2_r2i64 subrect, lm2_align align_x, lm2_align align_y);

// =============================================================================
// Rectangle Operations for i32
// =============================================================================

// Corner operations
LM2_API lm2_v2i32 lm2_r2i32_get_corner(lm2_r2i32 rect, lm2_corner2 corner);
LM2_API lm2_v2i32 lm2_r2i32_get_bottom_left(lm2_r2i32 rect);
LM2_API lm2_v2i32 lm2_r2i32_get_top_right(lm2_r2i32 rect);
LM2_API lm2_v2i32 lm2_r2i32_get_bottom_right(lm2_r2i32 rect);
LM2_API lm2_v2i32 lm2_r2i32_get_top_left(lm2_r2i32 rect);

// Transform operations
LM2_API lm2_r2i32 lm2_r2i32_scale_from_center(lm2_r2i32 rect, lm2_v2i32 scale);
LM2_API lm2_r2i32 lm2_r2i32_scale_from_min(lm2_r2i32 rect, lm2_v2i32 scale);
LM2_API lm2_r2i32 lm2_r2i32_scale_from_max(lm2_r2i32 rect, lm2_v2i32 scale);
LM2_API lm2_r2i32 lm2_r2i32_shrink_vec(lm2_r2i32 rect, lm2_v2i32 amount);
LM2_API lm2_r2i32 lm2_r2i32_shrink_scalar(lm2_r2i32 rect, int32_t amount);
LM2_API lm2_r2i32 lm2_r2i32_inflate_vec(lm2_r2i32 rect, lm2_v2i32 amount);
LM2_API lm2_r2i32 lm2_r2i32_inflate_scalar(lm2_r2i32 rect, int32_t amount);

// Query operations
LM2_API lm2_v2i32 lm2_r2i32_get_dim(lm2_r2i32 rect);
LM2_API int lm2_r2i32_overlap_rect(lm2_r2i32 a, lm2_r2i32 b);
LM2_API int lm2_r2i32_overlap_point(lm2_r2i32 rect, lm2_v2i32 point);
LM2_API int lm2_r2i32_contains(lm2_r2i32 rect, lm2_r2i32 subrect);
LM2_API int32_t lm2_r2i32_distance(lm2_r2i32 rect, lm2_v2i32 point);
LM2_API lm2_v2i32 lm2_r2i32_get_closest_point(lm2_r2i32 rect, lm2_v2i32 point);
LM2_API int32_t lm2_r2i32_closest_distance_from_edges(lm2_r2i32 a, lm2_r2i32 b);

// Cut operations
LM2_API lm2_r2i32 lm2_r2i32_cut(lm2_r2i32* rect, lm2_rect_cut cut_type, int32_t amount);
LM2_API lm2_r2i32 lm2_r2i32_cut_left(lm2_r2i32* rect, int32_t amount);
LM2_API lm2_r2i32 lm2_r2i32_cut_right(lm2_r2i32* rect, int32_t amount);
LM2_API lm2_r2i32 lm2_r2i32_cut_bottom(lm2_r2i32* rect, int32_t amount);
LM2_API lm2_r2i32 lm2_r2i32_cut_top(lm2_r2i32* rect, int32_t amount);

// Alignment
LM2_API lm2_r2i32 lm2_r2i32_align_subrect(lm2_r2i32 rect, lm2_r2i32 subrect, lm2_align align_x, lm2_align align_y);

// =============================================================================
// Rectangle Operations for i16
// =============================================================================

// Corner operations
LM2_API lm2_v2i16 lm2_r2i16_get_corner(lm2_r2i16 rect, lm2_corner2 corner);
LM2_API lm2_v2i16 lm2_r2i16_get_bottom_left(lm2_r2i16 rect);
LM2_API lm2_v2i16 lm2_r2i16_get_top_right(lm2_r2i16 rect);
LM2_API lm2_v2i16 lm2_r2i16_get_bottom_right(lm2_r2i16 rect);
LM2_API lm2_v2i16 lm2_r2i16_get_top_left(lm2_r2i16 rect);

// Transform operations
LM2_API lm2_r2i16 lm2_r2i16_scale_from_center(lm2_r2i16 rect, lm2_v2i16 scale);
LM2_API lm2_r2i16 lm2_r2i16_scale_from_min(lm2_r2i16 rect, lm2_v2i16 scale);
LM2_API lm2_r2i16 lm2_r2i16_scale_from_max(lm2_r2i16 rect, lm2_v2i16 scale);
LM2_API lm2_r2i16 lm2_r2i16_shrink_vec(lm2_r2i16 rect, lm2_v2i16 amount);
LM2_API lm2_r2i16 lm2_r2i16_shrink_scalar(lm2_r2i16 rect, int16_t amount);
LM2_API lm2_r2i16 lm2_r2i16_inflate_vec(lm2_r2i16 rect, lm2_v2i16 amount);
LM2_API lm2_r2i16 lm2_r2i16_inflate_scalar(lm2_r2i16 rect, int16_t amount);

// Query operations
LM2_API lm2_v2i16 lm2_r2i16_get_dim(lm2_r2i16 rect);
LM2_API int lm2_r2i16_overlap_rect(lm2_r2i16 a, lm2_r2i16 b);
LM2_API int lm2_r2i16_overlap_point(lm2_r2i16 rect, lm2_v2i16 point);
LM2_API int lm2_r2i16_contains(lm2_r2i16 rect, lm2_r2i16 subrect);
LM2_API int16_t lm2_r2i16_distance(lm2_r2i16 rect, lm2_v2i16 point);
LM2_API lm2_v2i16 lm2_r2i16_get_closest_point(lm2_r2i16 rect, lm2_v2i16 point);
LM2_API int16_t lm2_r2i16_closest_distance_from_edges(lm2_r2i16 a, lm2_r2i16 b);

// Cut operations
LM2_API lm2_r2i16 lm2_r2i16_cut(lm2_r2i16* rect, lm2_rect_cut cut_type, int16_t amount);
LM2_API lm2_r2i16 lm2_r2i16_cut_left(lm2_r2i16* rect, int16_t amount);
LM2_API lm2_r2i16 lm2_r2i16_cut_right(lm2_r2i16* rect, int16_t amount);
LM2_API lm2_r2i16 lm2_r2i16_cut_bottom(lm2_r2i16* rect, int16_t amount);
LM2_API lm2_r2i16 lm2_r2i16_cut_top(lm2_r2i16* rect, int16_t amount);

// Alignment
LM2_API lm2_r2i16 lm2_r2i16_align_subrect(lm2_r2i16 rect, lm2_r2i16 subrect, lm2_align align_x, lm2_align align_y);

// =============================================================================
// Rectangle Operations for i8
// =============================================================================

// Corner operations
LM2_API lm2_v2i8 lm2_r2i8_get_corner(lm2_r2i8 rect, lm2_corner2 corner);
LM2_API lm2_v2i8 lm2_r2i8_get_bottom_left(lm2_r2i8 rect);
LM2_API lm2_v2i8 lm2_r2i8_get_top_right(lm2_r2i8 rect);
LM2_API lm2_v2i8 lm2_r2i8_get_bottom_right(lm2_r2i8 rect);
LM2_API lm2_v2i8 lm2_r2i8_get_top_left(lm2_r2i8 rect);

// Transform operations
LM2_API lm2_r2i8 lm2_r2i8_scale_from_center(lm2_r2i8 rect, lm2_v2i8 scale);
LM2_API lm2_r2i8 lm2_r2i8_scale_from_min(lm2_r2i8 rect, lm2_v2i8 scale);
LM2_API lm2_r2i8 lm2_r2i8_scale_from_max(lm2_r2i8 rect, lm2_v2i8 scale);
LM2_API lm2_r2i8 lm2_r2i8_shrink_vec(lm2_r2i8 rect, lm2_v2i8 amount);
LM2_API lm2_r2i8 lm2_r2i8_shrink_scalar(lm2_r2i8 rect, int8_t amount);
LM2_API lm2_r2i8 lm2_r2i8_inflate_vec(lm2_r2i8 rect, lm2_v2i8 amount);
LM2_API lm2_r2i8 lm2_r2i8_inflate_scalar(lm2_r2i8 rect, int8_t amount);

// Query operations
LM2_API lm2_v2i8 lm2_r2i8_get_dim(lm2_r2i8 rect);
LM2_API int lm2_r2i8_overlap_rect(lm2_r2i8 a, lm2_r2i8 b);
LM2_API int lm2_r2i8_overlap_point(lm2_r2i8 rect, lm2_v2i8 point);
LM2_API int lm2_r2i8_contains(lm2_r2i8 rect, lm2_r2i8 subrect);
LM2_API int8_t lm2_r2i8_distance(lm2_r2i8 rect, lm2_v2i8 point);
LM2_API lm2_v2i8 lm2_r2i8_get_closest_point(lm2_r2i8 rect, lm2_v2i8 point);
LM2_API int8_t lm2_r2i8_closest_distance_from_edges(lm2_r2i8 a, lm2_r2i8 b);

// Cut operations
LM2_API lm2_r2i8 lm2_r2i8_cut(lm2_r2i8* rect, lm2_rect_cut cut_type, int8_t amount);
LM2_API lm2_r2i8 lm2_r2i8_cut_left(lm2_r2i8* rect, int8_t amount);
LM2_API lm2_r2i8 lm2_r2i8_cut_right(lm2_r2i8* rect, int8_t amount);
LM2_API lm2_r2i8 lm2_r2i8_cut_bottom(lm2_r2i8* rect, int8_t amount);
LM2_API lm2_r2i8 lm2_r2i8_cut_top(lm2_r2i8* rect, int8_t amount);

// Alignment
LM2_API lm2_r2i8 lm2_r2i8_align_subrect(lm2_r2i8 rect, lm2_r2i8 subrect, lm2_align align_x, lm2_align align_y);

// =============================================================================
// Rectangle Operations for u64
// =============================================================================

// Corner operations
LM2_API lm2_v2u64 lm2_r2u64_get_corner(lm2_r2u64 rect, lm2_corner2 corner);
LM2_API lm2_v2u64 lm2_r2u64_get_bottom_left(lm2_r2u64 rect);
LM2_API lm2_v2u64 lm2_r2u64_get_top_right(lm2_r2u64 rect);
LM2_API lm2_v2u64 lm2_r2u64_get_bottom_right(lm2_r2u64 rect);
LM2_API lm2_v2u64 lm2_r2u64_get_top_left(lm2_r2u64 rect);

// Transform operations
LM2_API lm2_r2u64 lm2_r2u64_scale_from_center(lm2_r2u64 rect, lm2_v2u64 scale);
LM2_API lm2_r2u64 lm2_r2u64_scale_from_min(lm2_r2u64 rect, lm2_v2u64 scale);
LM2_API lm2_r2u64 lm2_r2u64_scale_from_max(lm2_r2u64 rect, lm2_v2u64 scale);
LM2_API lm2_r2u64 lm2_r2u64_shrink_vec(lm2_r2u64 rect, lm2_v2u64 amount);
LM2_API lm2_r2u64 lm2_r2u64_shrink_scalar(lm2_r2u64 rect, uint64_t amount);
LM2_API lm2_r2u64 lm2_r2u64_inflate_vec(lm2_r2u64 rect, lm2_v2u64 amount);
LM2_API lm2_r2u64 lm2_r2u64_inflate_scalar(lm2_r2u64 rect, uint64_t amount);

// Query operations
LM2_API lm2_v2u64 lm2_r2u64_get_dim(lm2_r2u64 rect);
LM2_API int lm2_r2u64_overlap_rect(lm2_r2u64 a, lm2_r2u64 b);
LM2_API int lm2_r2u64_overlap_point(lm2_r2u64 rect, lm2_v2u64 point);
LM2_API int lm2_r2u64_contains(lm2_r2u64 rect, lm2_r2u64 subrect);
LM2_API uint64_t lm2_r2u64_distance(lm2_r2u64 rect, lm2_v2u64 point);
LM2_API lm2_v2u64 lm2_r2u64_get_closest_point(lm2_r2u64 rect, lm2_v2u64 point);
LM2_API uint64_t lm2_r2u64_closest_distance_from_edges(lm2_r2u64 a, lm2_r2u64 b);

// Cut operations
LM2_API lm2_r2u64 lm2_r2u64_cut(lm2_r2u64* rect, lm2_rect_cut cut_type, uint64_t amount);
LM2_API lm2_r2u64 lm2_r2u64_cut_left(lm2_r2u64* rect, uint64_t amount);
LM2_API lm2_r2u64 lm2_r2u64_cut_right(lm2_r2u64* rect, uint64_t amount);
LM2_API lm2_r2u64 lm2_r2u64_cut_bottom(lm2_r2u64* rect, uint64_t amount);
LM2_API lm2_r2u64 lm2_r2u64_cut_top(lm2_r2u64* rect, uint64_t amount);

// Alignment
LM2_API lm2_r2u64 lm2_r2u64_align_subrect(lm2_r2u64 rect, lm2_r2u64 subrect, lm2_align align_x, lm2_align align_y);

// =============================================================================
// Rectangle Operations for u32
// =============================================================================

// Corner operations
LM2_API lm2_v2u32 lm2_r2u32_get_corner(lm2_r2u32 rect, lm2_corner2 corner);
LM2_API lm2_v2u32 lm2_r2u32_get_bottom_left(lm2_r2u32 rect);
LM2_API lm2_v2u32 lm2_r2u32_get_top_right(lm2_r2u32 rect);
LM2_API lm2_v2u32 lm2_r2u32_get_bottom_right(lm2_r2u32 rect);
LM2_API lm2_v2u32 lm2_r2u32_get_top_left(lm2_r2u32 rect);

// Transform operations
LM2_API lm2_r2u32 lm2_r2u32_scale_from_center(lm2_r2u32 rect, lm2_v2u32 scale);
LM2_API lm2_r2u32 lm2_r2u32_scale_from_min(lm2_r2u32 rect, lm2_v2u32 scale);
LM2_API lm2_r2u32 lm2_r2u32_scale_from_max(lm2_r2u32 rect, lm2_v2u32 scale);
LM2_API lm2_r2u32 lm2_r2u32_shrink_vec(lm2_r2u32 rect, lm2_v2u32 amount);
LM2_API lm2_r2u32 lm2_r2u32_shrink_scalar(lm2_r2u32 rect, uint32_t amount);
LM2_API lm2_r2u32 lm2_r2u32_inflate_vec(lm2_r2u32 rect, lm2_v2u32 amount);
LM2_API lm2_r2u32 lm2_r2u32_inflate_scalar(lm2_r2u32 rect, uint32_t amount);

// Query operations
LM2_API lm2_v2u32 lm2_r2u32_get_dim(lm2_r2u32 rect);
LM2_API int lm2_r2u32_overlap_rect(lm2_r2u32 a, lm2_r2u32 b);
LM2_API int lm2_r2u32_overlap_point(lm2_r2u32 rect, lm2_v2u32 point);
LM2_API int lm2_r2u32_contains(lm2_r2u32 rect, lm2_r2u32 subrect);
LM2_API uint32_t lm2_r2u32_distance(lm2_r2u32 rect, lm2_v2u32 point);
LM2_API lm2_v2u32 lm2_r2u32_get_closest_point(lm2_r2u32 rect, lm2_v2u32 point);
LM2_API uint32_t lm2_r2u32_closest_distance_from_edges(lm2_r2u32 a, lm2_r2u32 b);

// Cut operations
LM2_API lm2_r2u32 lm2_r2u32_cut(lm2_r2u32* rect, lm2_rect_cut cut_type, uint32_t amount);
LM2_API lm2_r2u32 lm2_r2u32_cut_left(lm2_r2u32* rect, uint32_t amount);
LM2_API lm2_r2u32 lm2_r2u32_cut_right(lm2_r2u32* rect, uint32_t amount);
LM2_API lm2_r2u32 lm2_r2u32_cut_bottom(lm2_r2u32* rect, uint32_t amount);
LM2_API lm2_r2u32 lm2_r2u32_cut_top(lm2_r2u32* rect, uint32_t amount);

// Alignment
LM2_API lm2_r2u32 lm2_r2u32_align_subrect(lm2_r2u32 rect, lm2_r2u32 subrect, lm2_align align_x, lm2_align align_y);

// =============================================================================
// Rectangle Operations for u16
// =============================================================================

// Corner operations
LM2_API lm2_v2u16 lm2_r2u16_get_corner(lm2_r2u16 rect, lm2_corner2 corner);
LM2_API lm2_v2u16 lm2_r2u16_get_bottom_left(lm2_r2u16 rect);
LM2_API lm2_v2u16 lm2_r2u16_get_top_right(lm2_r2u16 rect);
LM2_API lm2_v2u16 lm2_r2u16_get_bottom_right(lm2_r2u16 rect);
LM2_API lm2_v2u16 lm2_r2u16_get_top_left(lm2_r2u16 rect);

// Transform operations
LM2_API lm2_r2u16 lm2_r2u16_scale_from_center(lm2_r2u16 rect, lm2_v2u16 scale);
LM2_API lm2_r2u16 lm2_r2u16_scale_from_min(lm2_r2u16 rect, lm2_v2u16 scale);
LM2_API lm2_r2u16 lm2_r2u16_scale_from_max(lm2_r2u16 rect, lm2_v2u16 scale);
LM2_API lm2_r2u16 lm2_r2u16_shrink_vec(lm2_r2u16 rect, lm2_v2u16 amount);
LM2_API lm2_r2u16 lm2_r2u16_shrink_scalar(lm2_r2u16 rect, uint16_t amount);
LM2_API lm2_r2u16 lm2_r2u16_inflate_vec(lm2_r2u16 rect, lm2_v2u16 amount);
LM2_API lm2_r2u16 lm2_r2u16_inflate_scalar(lm2_r2u16 rect, uint16_t amount);

// Query operations
LM2_API lm2_v2u16 lm2_r2u16_get_dim(lm2_r2u16 rect);
LM2_API int lm2_r2u16_overlap_rect(lm2_r2u16 a, lm2_r2u16 b);
LM2_API int lm2_r2u16_overlap_point(lm2_r2u16 rect, lm2_v2u16 point);
LM2_API int lm2_r2u16_contains(lm2_r2u16 rect, lm2_r2u16 subrect);
LM2_API uint16_t lm2_r2u16_distance(lm2_r2u16 rect, lm2_v2u16 point);
LM2_API lm2_v2u16 lm2_r2u16_get_closest_point(lm2_r2u16 rect, lm2_v2u16 point);
LM2_API uint16_t lm2_r2u16_closest_distance_from_edges(lm2_r2u16 a, lm2_r2u16 b);

// Cut operations
LM2_API lm2_r2u16 lm2_r2u16_cut(lm2_r2u16* rect, lm2_rect_cut cut_type, uint16_t amount);
LM2_API lm2_r2u16 lm2_r2u16_cut_left(lm2_r2u16* rect, uint16_t amount);
LM2_API lm2_r2u16 lm2_r2u16_cut_right(lm2_r2u16* rect, uint16_t amount);
LM2_API lm2_r2u16 lm2_r2u16_cut_bottom(lm2_r2u16* rect, uint16_t amount);
LM2_API lm2_r2u16 lm2_r2u16_cut_top(lm2_r2u16* rect, uint16_t amount);

// Alignment
LM2_API lm2_r2u16 lm2_r2u16_align_subrect(lm2_r2u16 rect, lm2_r2u16 subrect, lm2_align align_x, lm2_align align_y);

// =============================================================================
// Rectangle Operations for u8
// =============================================================================

// Corner operations
LM2_API lm2_v2u8 lm2_r2u8_get_corner(lm2_r2u8 rect, lm2_corner2 corner);
LM2_API lm2_v2u8 lm2_r2u8_get_bottom_left(lm2_r2u8 rect);
LM2_API lm2_v2u8 lm2_r2u8_get_top_right(lm2_r2u8 rect);
LM2_API lm2_v2u8 lm2_r2u8_get_bottom_right(lm2_r2u8 rect);
LM2_API lm2_v2u8 lm2_r2u8_get_top_left(lm2_r2u8 rect);

// Transform operations
LM2_API lm2_r2u8 lm2_r2u8_scale_from_center(lm2_r2u8 rect, lm2_v2u8 scale);
LM2_API lm2_r2u8 lm2_r2u8_scale_from_min(lm2_r2u8 rect, lm2_v2u8 scale);
LM2_API lm2_r2u8 lm2_r2u8_scale_from_max(lm2_r2u8 rect, lm2_v2u8 scale);
LM2_API lm2_r2u8 lm2_r2u8_shrink_vec(lm2_r2u8 rect, lm2_v2u8 amount);
LM2_API lm2_r2u8 lm2_r2u8_shrink_scalar(lm2_r2u8 rect, uint8_t amount);
LM2_API lm2_r2u8 lm2_r2u8_inflate_vec(lm2_r2u8 rect, lm2_v2u8 amount);
LM2_API lm2_r2u8 lm2_r2u8_inflate_scalar(lm2_r2u8 rect, uint8_t amount);

// Query operations
LM2_API lm2_v2u8 lm2_r2u8_get_dim(lm2_r2u8 rect);
LM2_API int lm2_r2u8_overlap_rect(lm2_r2u8 a, lm2_r2u8 b);
LM2_API int lm2_r2u8_overlap_point(lm2_r2u8 rect, lm2_v2u8 point);
LM2_API int lm2_r2u8_contains(lm2_r2u8 rect, lm2_r2u8 subrect);
LM2_API uint8_t lm2_r2u8_distance(lm2_r2u8 rect, lm2_v2u8 point);
LM2_API lm2_v2u8 lm2_r2u8_get_closest_point(lm2_r2u8 rect, lm2_v2u8 point);
LM2_API uint8_t lm2_r2u8_closest_distance_from_edges(lm2_r2u8 a, lm2_r2u8 b);

// Cut operations
LM2_API lm2_r2u8 lm2_r2u8_cut(lm2_r2u8* rect, lm2_rect_cut cut_type, uint8_t amount);
LM2_API lm2_r2u8 lm2_r2u8_cut_left(lm2_r2u8* rect, uint8_t amount);
LM2_API lm2_r2u8 lm2_r2u8_cut_right(lm2_r2u8* rect, uint8_t amount);
LM2_API lm2_r2u8 lm2_r2u8_cut_bottom(lm2_r2u8* rect, uint8_t amount);
LM2_API lm2_r2u8 lm2_r2u8_cut_top(lm2_r2u8* rect, uint8_t amount);

// Alignment
LM2_API lm2_r2u8 lm2_r2u8_align_subrect(lm2_r2u8 rect, lm2_r2u8 subrect, lm2_align align_x, lm2_align align_y);

// =============================================================================
// Segment Intersection Functions for All Vector Types
// =============================================================================

LM2_API int lm2_segments_intersect_lm2_v2f64(lm2_v2f64 a0, lm2_v2f64 a1, lm2_v2f64 b0, lm2_v2f64 b1);
LM2_API int lm2_segments_intersect_lm2_v2f32(lm2_v2f32 a0, lm2_v2f32 a1, lm2_v2f32 b0, lm2_v2f32 b1);
LM2_API int lm2_segments_intersect_lm2_v2i64(lm2_v2i64 a0, lm2_v2i64 a1, lm2_v2i64 b0, lm2_v2i64 b1);
LM2_API int lm2_segments_intersect_lm2_v2i32(lm2_v2i32 a0, lm2_v2i32 a1, lm2_v2i32 b0, lm2_v2i32 b1);
LM2_API int lm2_segments_intersect_lm2_v2i16(lm2_v2i16 a0, lm2_v2i16 a1, lm2_v2i16 b0, lm2_v2i16 b1);
LM2_API int lm2_segments_intersect_lm2_v2i8(lm2_v2i8 a0, lm2_v2i8 a1, lm2_v2i8 b0, lm2_v2i8 b1);
LM2_API int lm2_segments_intersect_lm2_v2u64(lm2_v2u64 a0, lm2_v2u64 a1, lm2_v2u64 b0, lm2_v2u64 b1);
LM2_API int lm2_segments_intersect_lm2_v2u32(lm2_v2u32 a0, lm2_v2u32 a1, lm2_v2u32 b0, lm2_v2u32 b1);
LM2_API int lm2_segments_intersect_lm2_v2u16(lm2_v2u16 a0, lm2_v2u16 a1, lm2_v2u16 b0, lm2_v2u16 b1);
LM2_API int lm2_segments_intersect_lm2_v2u8(lm2_v2u8 a0, lm2_v2u8 a1, lm2_v2u8 b0, lm2_v2u8 b1);

// =============================================================================
// Convenience typedefs
// =============================================================================

// The range2 types are the rectangle types (rectangles are AABBs)
typedef lm2_r2f64 lm2_rect2f64;
typedef lm2_r2f32 lm2_rect2f32;
typedef lm2_r2i64 lm2_rect2i64;
typedef lm2_r2i32 lm2_rect2i32;
typedef lm2_r2i16 lm2_rect2i16;
typedef lm2_r2i8 lm2_rect2i8;
typedef lm2_r2u64 lm2_rect2u64;
typedef lm2_r2u32 lm2_rect2u32;
typedef lm2_r2u16 lm2_rect2u16;
typedef lm2_r2u8 lm2_rect2u8;

// Default rectangle type (float-based)
typedef lm2_r2f32 lm2_rect2;

// #############################################################################
LM2_HEADER_END;
// Note: C++ operators are defined in lm2_range2.h since rectangles are range2 types
