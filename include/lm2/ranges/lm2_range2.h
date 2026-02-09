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
#include "lm2/vectors/lm2_vector2.h"
#include "lm2_range_defines.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// 2D Range (AABB) Type Definitions
// =============================================================================
// A range2 represents a 2D axis-aligned bounding box (AABB) or rectangle
// with minimum and maximum points.

// ---------------------------------------------------------------------------
// lm2_r2f64 - 2D Range (double precision)
// ---------------------------------------------------------------------------
typedef union lm2_r2f64 {
  lm2_v2f64 e[2];
  struct {
    lm2_v2f64 min;
    lm2_v2f64 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v2f64)
} lm2_r2f64;

// Constructors
LM2_API lm2_r2f64 lm2_r2f64_from_min_max(lm2_v2f64 min, lm2_v2f64 max);
LM2_API lm2_r2f64 lm2_r2f64_from_center_extents(lm2_v2f64 center, lm2_v2f64 extents);
LM2_API lm2_r2f64 lm2_r2f64_from_center_size(lm2_v2f64 center, lm2_v2f64 size);
LM2_API lm2_r2f64 lm2_r2f64_from_position_size(lm2_v2f64 position, lm2_v2f64 size);
LM2_API lm2_r2f64 lm2_r2f64_zero(void);

// Operations
LM2_API lm2_r2f64 lm2_r2f64_normalize(lm2_r2f64 r);
LM2_API lm2_r2f64 lm2_r2f64_translate(lm2_r2f64 r, lm2_v2f64 offset);
LM2_API lm2_r2f64 lm2_r2f64_scale(lm2_r2f64 r, double factor);
LM2_API lm2_r2f64 lm2_r2f64_expand(lm2_r2f64 r, double amount);

// Arithmetic operators
LM2_API lm2_r2f64 lm2_r2f64_add(lm2_r2f64 a, lm2_r2f64 b);
LM2_API lm2_r2f64 lm2_r2f64_add_scalar(lm2_r2f64 r, double s);
LM2_API lm2_r2f64 lm2_r2f64_add_vec(lm2_r2f64 r, lm2_v2f64 v);
LM2_API lm2_r2f64 lm2_r2f64_sub(lm2_r2f64 a, lm2_r2f64 b);
LM2_API lm2_r2f64 lm2_r2f64_sub_scalar(lm2_r2f64 r, double s);
LM2_API lm2_r2f64 lm2_r2f64_sub_vec(lm2_r2f64 r, lm2_v2f64 v);
LM2_API lm2_r2f64 lm2_r2f64_mul(lm2_r2f64 a, lm2_r2f64 b);
LM2_API lm2_r2f64 lm2_r2f64_mul_scalar(lm2_r2f64 r, double s);
LM2_API lm2_r2f64 lm2_r2f64_mul_vec(lm2_r2f64 r, lm2_v2f64 v);
LM2_API lm2_r2f64 lm2_r2f64_div(lm2_r2f64 a, lm2_r2f64 b);
LM2_API lm2_r2f64 lm2_r2f64_div_scalar(lm2_r2f64 r, double s);
LM2_API lm2_r2f64 lm2_r2f64_div_vec(lm2_r2f64 r, lm2_v2f64 v);
LM2_API lm2_r2f64 lm2_r2f64_mod(lm2_r2f64 a, lm2_r2f64 b);
LM2_API lm2_r2f64 lm2_r2f64_mod_scalar(lm2_r2f64 r, double s);
LM2_API lm2_r2f64 lm2_r2f64_mod_vec(lm2_r2f64 r, lm2_v2f64 v);

// Scalar function forwards
LM2_API lm2_r2f64 lm2_floor_lm2_r2f64(lm2_r2f64 a);
LM2_API lm2_r2f64 lm2_ceil_lm2_r2f64(lm2_r2f64 a);
LM2_API lm2_r2f64 lm2_round_lm2_r2f64(lm2_r2f64 a);
LM2_API lm2_r2f64 lm2_trunc_lm2_r2f64(lm2_r2f64 a);
LM2_API lm2_r2f64 lm2_abs_lm2_r2f64(lm2_r2f64 a);
LM2_API lm2_r2f64 lm2_floor_multiple_lm2_r2f64(lm2_r2f64 a, lm2_r2f64 b);
LM2_API lm2_r2f64 lm2_ceil_multiple_lm2_r2f64(lm2_r2f64 a, lm2_r2f64 b);
LM2_API lm2_r2f64 lm2_round_multiple_lm2_r2f64(lm2_r2f64 a, lm2_r2f64 b);
LM2_API lm2_r2f64 lm2_trunc_multiple_lm2_r2f64(lm2_r2f64 a, lm2_r2f64 b);
LM2_API lm2_r2f64 lm2_min_lm2_r2f64(lm2_r2f64 a, lm2_r2f64 b);
LM2_API lm2_r2f64 lm2_max_lm2_r2f64(lm2_r2f64 a, lm2_r2f64 b);
LM2_API lm2_r2f64 lm2_clamp_lm2_r2f64(lm2_r2f64 a, lm2_r2f64 b, lm2_r2f64 c);
LM2_API lm2_r2f64 lm2_lerp_lm2_r2f64(lm2_r2f64 a, lm2_r2f64 b, lm2_r2f64 c);

// Queries
LM2_API lm2_r2f64 lm2_r2f64_union(lm2_r2f64 a, lm2_r2f64 b);
LM2_API lm2_r2f64 lm2_r2f64_intersection(lm2_r2f64 a, lm2_r2f64 b);
LM2_API lm2_v2f64 lm2_r2f64_size(lm2_r2f64 r);
LM2_API lm2_v2f64 lm2_r2f64_extents(lm2_r2f64 r);
LM2_API lm2_v2f64 lm2_r2f64_center(lm2_r2f64 r);
LM2_API int lm2_r2f64_contains_point(lm2_r2f64 r, lm2_v2f64 point);
LM2_API int lm2_r2f64_overlaps(lm2_r2f64 a, lm2_r2f64 b);
LM2_API double lm2_r2f64_area(lm2_r2f64 r);

// ---------------------------------------------------------------------------
// lm2_r2f32 - 2D Range (single precision)
// ---------------------------------------------------------------------------
typedef union lm2_r2f32 {
  lm2_v2f32 e[2];
  struct {
    lm2_v2f32 min;
    lm2_v2f32 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v2f32)
} lm2_r2f32;

// Constructors
LM2_API lm2_r2f32 lm2_r2f32_from_min_max(lm2_v2f32 min, lm2_v2f32 max);
LM2_API lm2_r2f32 lm2_r2f32_from_center_extents(lm2_v2f32 center, lm2_v2f32 extents);
LM2_API lm2_r2f32 lm2_r2f32_from_center_size(lm2_v2f32 center, lm2_v2f32 size);
LM2_API lm2_r2f32 lm2_r2f32_from_position_size(lm2_v2f32 position, lm2_v2f32 size);
LM2_API lm2_r2f32 lm2_r2f32_zero(void);

// Operations
LM2_API lm2_r2f32 lm2_r2f32_normalize(lm2_r2f32 r);
LM2_API lm2_r2f32 lm2_r2f32_translate(lm2_r2f32 r, lm2_v2f32 offset);
LM2_API lm2_r2f32 lm2_r2f32_scale(lm2_r2f32 r, float factor);
LM2_API lm2_r2f32 lm2_r2f32_expand(lm2_r2f32 r, float amount);

// Arithmetic operators
LM2_API lm2_r2f32 lm2_r2f32_add(lm2_r2f32 a, lm2_r2f32 b);
LM2_API lm2_r2f32 lm2_r2f32_add_scalar(lm2_r2f32 r, float s);
LM2_API lm2_r2f32 lm2_r2f32_add_vec(lm2_r2f32 r, lm2_v2f32 v);
LM2_API lm2_r2f32 lm2_r2f32_sub(lm2_r2f32 a, lm2_r2f32 b);
LM2_API lm2_r2f32 lm2_r2f32_sub_scalar(lm2_r2f32 r, float s);
LM2_API lm2_r2f32 lm2_r2f32_sub_vec(lm2_r2f32 r, lm2_v2f32 v);
LM2_API lm2_r2f32 lm2_r2f32_mul(lm2_r2f32 a, lm2_r2f32 b);
LM2_API lm2_r2f32 lm2_r2f32_mul_scalar(lm2_r2f32 r, float s);
LM2_API lm2_r2f32 lm2_r2f32_mul_vec(lm2_r2f32 r, lm2_v2f32 v);
LM2_API lm2_r2f32 lm2_r2f32_div(lm2_r2f32 a, lm2_r2f32 b);
LM2_API lm2_r2f32 lm2_r2f32_div_scalar(lm2_r2f32 r, float s);
LM2_API lm2_r2f32 lm2_r2f32_div_vec(lm2_r2f32 r, lm2_v2f32 v);
LM2_API lm2_r2f32 lm2_r2f32_mod(lm2_r2f32 a, lm2_r2f32 b);
LM2_API lm2_r2f32 lm2_r2f32_mod_scalar(lm2_r2f32 r, float s);
LM2_API lm2_r2f32 lm2_r2f32_mod_vec(lm2_r2f32 r, lm2_v2f32 v);

// Scalar function forwards
LM2_API lm2_r2f32 lm2_floor_lm2_r2f32(lm2_r2f32 a);
LM2_API lm2_r2f32 lm2_ceil_lm2_r2f32(lm2_r2f32 a);
LM2_API lm2_r2f32 lm2_round_lm2_r2f32(lm2_r2f32 a);
LM2_API lm2_r2f32 lm2_trunc_lm2_r2f32(lm2_r2f32 a);
LM2_API lm2_r2f32 lm2_abs_lm2_r2f32(lm2_r2f32 a);
LM2_API lm2_r2f32 lm2_floor_multiple_lm2_r2f32(lm2_r2f32 a, lm2_r2f32 b);
LM2_API lm2_r2f32 lm2_ceil_multiple_lm2_r2f32(lm2_r2f32 a, lm2_r2f32 b);
LM2_API lm2_r2f32 lm2_round_multiple_lm2_r2f32(lm2_r2f32 a, lm2_r2f32 b);
LM2_API lm2_r2f32 lm2_trunc_multiple_lm2_r2f32(lm2_r2f32 a, lm2_r2f32 b);
LM2_API lm2_r2f32 lm2_min_lm2_r2f32(lm2_r2f32 a, lm2_r2f32 b);
LM2_API lm2_r2f32 lm2_max_lm2_r2f32(lm2_r2f32 a, lm2_r2f32 b);
LM2_API lm2_r2f32 lm2_clamp_lm2_r2f32(lm2_r2f32 a, lm2_r2f32 b, lm2_r2f32 c);
LM2_API lm2_r2f32 lm2_lerp_lm2_r2f32(lm2_r2f32 a, lm2_r2f32 b, lm2_r2f32 c);

// Queries
LM2_API lm2_r2f32 lm2_r2f32_union(lm2_r2f32 a, lm2_r2f32 b);
LM2_API lm2_r2f32 lm2_r2f32_intersection(lm2_r2f32 a, lm2_r2f32 b);
LM2_API lm2_v2f32 lm2_r2f32_size(lm2_r2f32 r);
LM2_API lm2_v2f32 lm2_r2f32_extents(lm2_r2f32 r);
LM2_API lm2_v2f32 lm2_r2f32_center(lm2_r2f32 r);
LM2_API int lm2_r2f32_contains_point(lm2_r2f32 r, lm2_v2f32 point);
LM2_API int lm2_r2f32_overlaps(lm2_r2f32 a, lm2_r2f32 b);
LM2_API float lm2_r2f32_area(lm2_r2f32 r);

// ---------------------------------------------------------------------------
// lm2_r2i64 - 2D Range (64-bit signed integer)
// ---------------------------------------------------------------------------
typedef union lm2_r2i64 {
  lm2_v2i64 e[2];
  struct {
    lm2_v2i64 min;
    lm2_v2i64 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v2i64)
} lm2_r2i64;

// Constructors
LM2_API lm2_r2i64 lm2_r2i64_from_min_max(lm2_v2i64 min, lm2_v2i64 max);
LM2_API lm2_r2i64 lm2_r2i64_from_center_extents(lm2_v2i64 center, lm2_v2i64 extents);
LM2_API lm2_r2i64 lm2_r2i64_from_center_size(lm2_v2i64 center, lm2_v2i64 size);
LM2_API lm2_r2i64 lm2_r2i64_from_position_size(lm2_v2i64 position, lm2_v2i64 size);
LM2_API lm2_r2i64 lm2_r2i64_zero(void);

// Operations
LM2_API lm2_r2i64 lm2_r2i64_normalize(lm2_r2i64 r);
LM2_API lm2_r2i64 lm2_r2i64_translate(lm2_r2i64 r, lm2_v2i64 offset);
LM2_API lm2_r2i64 lm2_r2i64_scale(lm2_r2i64 r, int64_t factor);
LM2_API lm2_r2i64 lm2_r2i64_expand(lm2_r2i64 r, int64_t amount);

// Arithmetic operators
LM2_API lm2_r2i64 lm2_r2i64_add(lm2_r2i64 a, lm2_r2i64 b);
LM2_API lm2_r2i64 lm2_r2i64_add_scalar(lm2_r2i64 r, int64_t s);
LM2_API lm2_r2i64 lm2_r2i64_add_vec(lm2_r2i64 r, lm2_v2i64 v);
LM2_API lm2_r2i64 lm2_r2i64_sub(lm2_r2i64 a, lm2_r2i64 b);
LM2_API lm2_r2i64 lm2_r2i64_sub_scalar(lm2_r2i64 r, int64_t s);
LM2_API lm2_r2i64 lm2_r2i64_sub_vec(lm2_r2i64 r, lm2_v2i64 v);
LM2_API lm2_r2i64 lm2_r2i64_mul(lm2_r2i64 a, lm2_r2i64 b);
LM2_API lm2_r2i64 lm2_r2i64_mul_scalar(lm2_r2i64 r, int64_t s);
LM2_API lm2_r2i64 lm2_r2i64_mul_vec(lm2_r2i64 r, lm2_v2i64 v);
LM2_API lm2_r2i64 lm2_r2i64_div(lm2_r2i64 a, lm2_r2i64 b);
LM2_API lm2_r2i64 lm2_r2i64_div_scalar(lm2_r2i64 r, int64_t s);
LM2_API lm2_r2i64 lm2_r2i64_div_vec(lm2_r2i64 r, lm2_v2i64 v);
LM2_API lm2_r2i64 lm2_r2i64_mod(lm2_r2i64 a, lm2_r2i64 b);
LM2_API lm2_r2i64 lm2_r2i64_mod_scalar(lm2_r2i64 r, int64_t s);
LM2_API lm2_r2i64 lm2_r2i64_mod_vec(lm2_r2i64 r, lm2_v2i64 v);

// Scalar function forwards
LM2_API lm2_r2i64 lm2_floor_lm2_r2i64(lm2_r2i64 a);
LM2_API lm2_r2i64 lm2_ceil_lm2_r2i64(lm2_r2i64 a);
LM2_API lm2_r2i64 lm2_round_lm2_r2i64(lm2_r2i64 a);
LM2_API lm2_r2i64 lm2_trunc_lm2_r2i64(lm2_r2i64 a);
LM2_API lm2_r2i64 lm2_abs_lm2_r2i64(lm2_r2i64 a);
LM2_API lm2_r2i64 lm2_floor_multiple_lm2_r2i64(lm2_r2i64 a, lm2_r2i64 b);
LM2_API lm2_r2i64 lm2_ceil_multiple_lm2_r2i64(lm2_r2i64 a, lm2_r2i64 b);
LM2_API lm2_r2i64 lm2_round_multiple_lm2_r2i64(lm2_r2i64 a, lm2_r2i64 b);
LM2_API lm2_r2i64 lm2_trunc_multiple_lm2_r2i64(lm2_r2i64 a, lm2_r2i64 b);
LM2_API lm2_r2i64 lm2_min_lm2_r2i64(lm2_r2i64 a, lm2_r2i64 b);
LM2_API lm2_r2i64 lm2_max_lm2_r2i64(lm2_r2i64 a, lm2_r2i64 b);
LM2_API lm2_r2i64 lm2_clamp_lm2_r2i64(lm2_r2i64 a, lm2_r2i64 b, lm2_r2i64 c);
LM2_API lm2_r2i64 lm2_lerp_lm2_r2i64(lm2_r2i64 a, lm2_r2i64 b, lm2_r2i64 c);

// Queries
LM2_API lm2_r2i64 lm2_r2i64_union(lm2_r2i64 a, lm2_r2i64 b);
LM2_API lm2_r2i64 lm2_r2i64_intersection(lm2_r2i64 a, lm2_r2i64 b);
LM2_API lm2_v2i64 lm2_r2i64_size(lm2_r2i64 r);
LM2_API lm2_v2i64 lm2_r2i64_extents(lm2_r2i64 r);
LM2_API lm2_v2i64 lm2_r2i64_center(lm2_r2i64 r);
LM2_API int lm2_r2i64_contains_point(lm2_r2i64 r, lm2_v2i64 point);
LM2_API int lm2_r2i64_overlaps(lm2_r2i64 a, lm2_r2i64 b);
LM2_API int64_t lm2_r2i64_area(lm2_r2i64 r);

// ---------------------------------------------------------------------------
// lm2_r2i32 - 2D Range (32-bit signed integer)
// ---------------------------------------------------------------------------
typedef union lm2_r2i32 {
  lm2_v2i32 e[2];
  struct {
    lm2_v2i32 min;
    lm2_v2i32 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v2i32)
} lm2_r2i32;

// Constructors
LM2_API lm2_r2i32 lm2_r2i32_from_min_max(lm2_v2i32 min, lm2_v2i32 max);
LM2_API lm2_r2i32 lm2_r2i32_from_center_extents(lm2_v2i32 center, lm2_v2i32 extents);
LM2_API lm2_r2i32 lm2_r2i32_from_center_size(lm2_v2i32 center, lm2_v2i32 size);
LM2_API lm2_r2i32 lm2_r2i32_from_position_size(lm2_v2i32 position, lm2_v2i32 size);
LM2_API lm2_r2i32 lm2_r2i32_zero(void);

// Operations
LM2_API lm2_r2i32 lm2_r2i32_normalize(lm2_r2i32 r);
LM2_API lm2_r2i32 lm2_r2i32_translate(lm2_r2i32 r, lm2_v2i32 offset);
LM2_API lm2_r2i32 lm2_r2i32_scale(lm2_r2i32 r, int32_t factor);
LM2_API lm2_r2i32 lm2_r2i32_expand(lm2_r2i32 r, int32_t amount);

// Arithmetic operators
LM2_API lm2_r2i32 lm2_r2i32_add(lm2_r2i32 a, lm2_r2i32 b);
LM2_API lm2_r2i32 lm2_r2i32_add_scalar(lm2_r2i32 r, int32_t s);
LM2_API lm2_r2i32 lm2_r2i32_add_vec(lm2_r2i32 r, lm2_v2i32 v);
LM2_API lm2_r2i32 lm2_r2i32_sub(lm2_r2i32 a, lm2_r2i32 b);
LM2_API lm2_r2i32 lm2_r2i32_sub_scalar(lm2_r2i32 r, int32_t s);
LM2_API lm2_r2i32 lm2_r2i32_sub_vec(lm2_r2i32 r, lm2_v2i32 v);
LM2_API lm2_r2i32 lm2_r2i32_mul(lm2_r2i32 a, lm2_r2i32 b);
LM2_API lm2_r2i32 lm2_r2i32_mul_scalar(lm2_r2i32 r, int32_t s);
LM2_API lm2_r2i32 lm2_r2i32_mul_vec(lm2_r2i32 r, lm2_v2i32 v);
LM2_API lm2_r2i32 lm2_r2i32_div(lm2_r2i32 a, lm2_r2i32 b);
LM2_API lm2_r2i32 lm2_r2i32_div_scalar(lm2_r2i32 r, int32_t s);
LM2_API lm2_r2i32 lm2_r2i32_div_vec(lm2_r2i32 r, lm2_v2i32 v);
LM2_API lm2_r2i32 lm2_r2i32_mod(lm2_r2i32 a, lm2_r2i32 b);
LM2_API lm2_r2i32 lm2_r2i32_mod_scalar(lm2_r2i32 r, int32_t s);
LM2_API lm2_r2i32 lm2_r2i32_mod_vec(lm2_r2i32 r, lm2_v2i32 v);

// Scalar function forwards
LM2_API lm2_r2i32 lm2_floor_lm2_r2i32(lm2_r2i32 a);
LM2_API lm2_r2i32 lm2_ceil_lm2_r2i32(lm2_r2i32 a);
LM2_API lm2_r2i32 lm2_round_lm2_r2i32(lm2_r2i32 a);
LM2_API lm2_r2i32 lm2_trunc_lm2_r2i32(lm2_r2i32 a);
LM2_API lm2_r2i32 lm2_abs_lm2_r2i32(lm2_r2i32 a);
LM2_API lm2_r2i32 lm2_floor_multiple_lm2_r2i32(lm2_r2i32 a, lm2_r2i32 b);
LM2_API lm2_r2i32 lm2_ceil_multiple_lm2_r2i32(lm2_r2i32 a, lm2_r2i32 b);
LM2_API lm2_r2i32 lm2_round_multiple_lm2_r2i32(lm2_r2i32 a, lm2_r2i32 b);
LM2_API lm2_r2i32 lm2_trunc_multiple_lm2_r2i32(lm2_r2i32 a, lm2_r2i32 b);
LM2_API lm2_r2i32 lm2_min_lm2_r2i32(lm2_r2i32 a, lm2_r2i32 b);
LM2_API lm2_r2i32 lm2_max_lm2_r2i32(lm2_r2i32 a, lm2_r2i32 b);
LM2_API lm2_r2i32 lm2_clamp_lm2_r2i32(lm2_r2i32 a, lm2_r2i32 b, lm2_r2i32 c);
LM2_API lm2_r2i32 lm2_lerp_lm2_r2i32(lm2_r2i32 a, lm2_r2i32 b, lm2_r2i32 c);

// Queries
LM2_API lm2_r2i32 lm2_r2i32_union(lm2_r2i32 a, lm2_r2i32 b);
LM2_API lm2_r2i32 lm2_r2i32_intersection(lm2_r2i32 a, lm2_r2i32 b);
LM2_API lm2_v2i32 lm2_r2i32_size(lm2_r2i32 r);
LM2_API lm2_v2i32 lm2_r2i32_extents(lm2_r2i32 r);
LM2_API lm2_v2i32 lm2_r2i32_center(lm2_r2i32 r);
LM2_API int lm2_r2i32_contains_point(lm2_r2i32 r, lm2_v2i32 point);
LM2_API int lm2_r2i32_overlaps(lm2_r2i32 a, lm2_r2i32 b);
LM2_API int32_t lm2_r2i32_area(lm2_r2i32 r);

// ---------------------------------------------------------------------------
// lm2_r2i16 - 2D Range (16-bit signed integer)
// ---------------------------------------------------------------------------
typedef union lm2_r2i16 {
  lm2_v2i16 e[2];
  struct {
    lm2_v2i16 min;
    lm2_v2i16 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v2i16)
} lm2_r2i16;

// Constructors
LM2_API lm2_r2i16 lm2_r2i16_from_min_max(lm2_v2i16 min, lm2_v2i16 max);
LM2_API lm2_r2i16 lm2_r2i16_from_center_extents(lm2_v2i16 center, lm2_v2i16 extents);
LM2_API lm2_r2i16 lm2_r2i16_from_center_size(lm2_v2i16 center, lm2_v2i16 size);
LM2_API lm2_r2i16 lm2_r2i16_from_position_size(lm2_v2i16 position, lm2_v2i16 size);
LM2_API lm2_r2i16 lm2_r2i16_zero(void);

// Operations
LM2_API lm2_r2i16 lm2_r2i16_normalize(lm2_r2i16 r);
LM2_API lm2_r2i16 lm2_r2i16_translate(lm2_r2i16 r, lm2_v2i16 offset);
LM2_API lm2_r2i16 lm2_r2i16_scale(lm2_r2i16 r, int16_t factor);
LM2_API lm2_r2i16 lm2_r2i16_expand(lm2_r2i16 r, int16_t amount);

// Arithmetic operators
LM2_API lm2_r2i16 lm2_r2i16_add(lm2_r2i16 a, lm2_r2i16 b);
LM2_API lm2_r2i16 lm2_r2i16_add_scalar(lm2_r2i16 r, int16_t s);
LM2_API lm2_r2i16 lm2_r2i16_add_vec(lm2_r2i16 r, lm2_v2i16 v);
LM2_API lm2_r2i16 lm2_r2i16_sub(lm2_r2i16 a, lm2_r2i16 b);
LM2_API lm2_r2i16 lm2_r2i16_sub_scalar(lm2_r2i16 r, int16_t s);
LM2_API lm2_r2i16 lm2_r2i16_sub_vec(lm2_r2i16 r, lm2_v2i16 v);
LM2_API lm2_r2i16 lm2_r2i16_mul(lm2_r2i16 a, lm2_r2i16 b);
LM2_API lm2_r2i16 lm2_r2i16_mul_scalar(lm2_r2i16 r, int16_t s);
LM2_API lm2_r2i16 lm2_r2i16_mul_vec(lm2_r2i16 r, lm2_v2i16 v);
LM2_API lm2_r2i16 lm2_r2i16_div(lm2_r2i16 a, lm2_r2i16 b);
LM2_API lm2_r2i16 lm2_r2i16_div_scalar(lm2_r2i16 r, int16_t s);
LM2_API lm2_r2i16 lm2_r2i16_div_vec(lm2_r2i16 r, lm2_v2i16 v);
LM2_API lm2_r2i16 lm2_r2i16_mod(lm2_r2i16 a, lm2_r2i16 b);
LM2_API lm2_r2i16 lm2_r2i16_mod_scalar(lm2_r2i16 r, int16_t s);
LM2_API lm2_r2i16 lm2_r2i16_mod_vec(lm2_r2i16 r, lm2_v2i16 v);

// Scalar function forwards
LM2_API lm2_r2i16 lm2_floor_lm2_r2i16(lm2_r2i16 a);
LM2_API lm2_r2i16 lm2_ceil_lm2_r2i16(lm2_r2i16 a);
LM2_API lm2_r2i16 lm2_round_lm2_r2i16(lm2_r2i16 a);
LM2_API lm2_r2i16 lm2_trunc_lm2_r2i16(lm2_r2i16 a);
LM2_API lm2_r2i16 lm2_abs_lm2_r2i16(lm2_r2i16 a);
LM2_API lm2_r2i16 lm2_floor_multiple_lm2_r2i16(lm2_r2i16 a, lm2_r2i16 b);
LM2_API lm2_r2i16 lm2_ceil_multiple_lm2_r2i16(lm2_r2i16 a, lm2_r2i16 b);
LM2_API lm2_r2i16 lm2_round_multiple_lm2_r2i16(lm2_r2i16 a, lm2_r2i16 b);
LM2_API lm2_r2i16 lm2_trunc_multiple_lm2_r2i16(lm2_r2i16 a, lm2_r2i16 b);
LM2_API lm2_r2i16 lm2_min_lm2_r2i16(lm2_r2i16 a, lm2_r2i16 b);
LM2_API lm2_r2i16 lm2_max_lm2_r2i16(lm2_r2i16 a, lm2_r2i16 b);
LM2_API lm2_r2i16 lm2_clamp_lm2_r2i16(lm2_r2i16 a, lm2_r2i16 b, lm2_r2i16 c);
LM2_API lm2_r2i16 lm2_lerp_lm2_r2i16(lm2_r2i16 a, lm2_r2i16 b, lm2_r2i16 c);

// Queries
LM2_API lm2_r2i16 lm2_r2i16_union(lm2_r2i16 a, lm2_r2i16 b);
LM2_API lm2_r2i16 lm2_r2i16_intersection(lm2_r2i16 a, lm2_r2i16 b);
LM2_API lm2_v2i16 lm2_r2i16_size(lm2_r2i16 r);
LM2_API lm2_v2i16 lm2_r2i16_extents(lm2_r2i16 r);
LM2_API lm2_v2i16 lm2_r2i16_center(lm2_r2i16 r);
LM2_API int lm2_r2i16_contains_point(lm2_r2i16 r, lm2_v2i16 point);
LM2_API int lm2_r2i16_overlaps(lm2_r2i16 a, lm2_r2i16 b);
LM2_API int16_t lm2_r2i16_area(lm2_r2i16 r);

// ---------------------------------------------------------------------------
// lm2_r2i8 - 2D Range (8-bit signed integer)
// ---------------------------------------------------------------------------
typedef union lm2_r2i8 {
  lm2_v2i8 e[2];
  struct {
    lm2_v2i8 min;
    lm2_v2i8 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v2i8)
} lm2_r2i8;

// Constructors
LM2_API lm2_r2i8 lm2_r2i8_from_min_max(lm2_v2i8 min, lm2_v2i8 max);
LM2_API lm2_r2i8 lm2_r2i8_from_center_extents(lm2_v2i8 center, lm2_v2i8 extents);
LM2_API lm2_r2i8 lm2_r2i8_from_center_size(lm2_v2i8 center, lm2_v2i8 size);
LM2_API lm2_r2i8 lm2_r2i8_from_position_size(lm2_v2i8 position, lm2_v2i8 size);
LM2_API lm2_r2i8 lm2_r2i8_zero(void);

// Operations
LM2_API lm2_r2i8 lm2_r2i8_normalize(lm2_r2i8 r);
LM2_API lm2_r2i8 lm2_r2i8_translate(lm2_r2i8 r, lm2_v2i8 offset);
LM2_API lm2_r2i8 lm2_r2i8_scale(lm2_r2i8 r, int8_t factor);
LM2_API lm2_r2i8 lm2_r2i8_expand(lm2_r2i8 r, int8_t amount);

// Arithmetic operators
LM2_API lm2_r2i8 lm2_r2i8_add(lm2_r2i8 a, lm2_r2i8 b);
LM2_API lm2_r2i8 lm2_r2i8_add_scalar(lm2_r2i8 r, int8_t s);
LM2_API lm2_r2i8 lm2_r2i8_add_vec(lm2_r2i8 r, lm2_v2i8 v);
LM2_API lm2_r2i8 lm2_r2i8_sub(lm2_r2i8 a, lm2_r2i8 b);
LM2_API lm2_r2i8 lm2_r2i8_sub_scalar(lm2_r2i8 r, int8_t s);
LM2_API lm2_r2i8 lm2_r2i8_sub_vec(lm2_r2i8 r, lm2_v2i8 v);
LM2_API lm2_r2i8 lm2_r2i8_mul(lm2_r2i8 a, lm2_r2i8 b);
LM2_API lm2_r2i8 lm2_r2i8_mul_scalar(lm2_r2i8 r, int8_t s);
LM2_API lm2_r2i8 lm2_r2i8_mul_vec(lm2_r2i8 r, lm2_v2i8 v);
LM2_API lm2_r2i8 lm2_r2i8_div(lm2_r2i8 a, lm2_r2i8 b);
LM2_API lm2_r2i8 lm2_r2i8_div_scalar(lm2_r2i8 r, int8_t s);
LM2_API lm2_r2i8 lm2_r2i8_div_vec(lm2_r2i8 r, lm2_v2i8 v);
LM2_API lm2_r2i8 lm2_r2i8_mod(lm2_r2i8 a, lm2_r2i8 b);
LM2_API lm2_r2i8 lm2_r2i8_mod_scalar(lm2_r2i8 r, int8_t s);
LM2_API lm2_r2i8 lm2_r2i8_mod_vec(lm2_r2i8 r, lm2_v2i8 v);

// Scalar function forwards
LM2_API lm2_r2i8 lm2_floor_lm2_r2i8(lm2_r2i8 a);
LM2_API lm2_r2i8 lm2_ceil_lm2_r2i8(lm2_r2i8 a);
LM2_API lm2_r2i8 lm2_round_lm2_r2i8(lm2_r2i8 a);
LM2_API lm2_r2i8 lm2_trunc_lm2_r2i8(lm2_r2i8 a);
LM2_API lm2_r2i8 lm2_abs_lm2_r2i8(lm2_r2i8 a);
LM2_API lm2_r2i8 lm2_floor_multiple_lm2_r2i8(lm2_r2i8 a, lm2_r2i8 b);
LM2_API lm2_r2i8 lm2_ceil_multiple_lm2_r2i8(lm2_r2i8 a, lm2_r2i8 b);
LM2_API lm2_r2i8 lm2_round_multiple_lm2_r2i8(lm2_r2i8 a, lm2_r2i8 b);
LM2_API lm2_r2i8 lm2_trunc_multiple_lm2_r2i8(lm2_r2i8 a, lm2_r2i8 b);
LM2_API lm2_r2i8 lm2_min_lm2_r2i8(lm2_r2i8 a, lm2_r2i8 b);
LM2_API lm2_r2i8 lm2_max_lm2_r2i8(lm2_r2i8 a, lm2_r2i8 b);
LM2_API lm2_r2i8 lm2_clamp_lm2_r2i8(lm2_r2i8 a, lm2_r2i8 b, lm2_r2i8 c);
LM2_API lm2_r2i8 lm2_lerp_lm2_r2i8(lm2_r2i8 a, lm2_r2i8 b, lm2_r2i8 c);

// Queries
LM2_API lm2_r2i8 lm2_r2i8_union(lm2_r2i8 a, lm2_r2i8 b);
LM2_API lm2_r2i8 lm2_r2i8_intersection(lm2_r2i8 a, lm2_r2i8 b);
LM2_API lm2_v2i8 lm2_r2i8_size(lm2_r2i8 r);
LM2_API lm2_v2i8 lm2_r2i8_extents(lm2_r2i8 r);
LM2_API lm2_v2i8 lm2_r2i8_center(lm2_r2i8 r);
LM2_API int lm2_r2i8_contains_point(lm2_r2i8 r, lm2_v2i8 point);
LM2_API int lm2_r2i8_overlaps(lm2_r2i8 a, lm2_r2i8 b);
LM2_API int8_t lm2_r2i8_area(lm2_r2i8 r);

// ---------------------------------------------------------------------------
// lm2_r2u64 - 2D Range (64-bit unsigned integer)
// ---------------------------------------------------------------------------
typedef union lm2_r2u64 {
  lm2_v2u64 e[2];
  struct {
    lm2_v2u64 min;
    lm2_v2u64 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v2u64)
} lm2_r2u64;

// Constructors
LM2_API lm2_r2u64 lm2_r2u64_from_min_max(lm2_v2u64 min, lm2_v2u64 max);
LM2_API lm2_r2u64 lm2_r2u64_from_center_extents(lm2_v2u64 center, lm2_v2u64 extents);
LM2_API lm2_r2u64 lm2_r2u64_from_center_size(lm2_v2u64 center, lm2_v2u64 size);
LM2_API lm2_r2u64 lm2_r2u64_from_position_size(lm2_v2u64 position, lm2_v2u64 size);
LM2_API lm2_r2u64 lm2_r2u64_zero(void);

// Operations
LM2_API lm2_r2u64 lm2_r2u64_normalize(lm2_r2u64 r);
LM2_API lm2_r2u64 lm2_r2u64_translate(lm2_r2u64 r, lm2_v2u64 offset);
LM2_API lm2_r2u64 lm2_r2u64_scale(lm2_r2u64 r, uint64_t factor);
LM2_API lm2_r2u64 lm2_r2u64_expand(lm2_r2u64 r, uint64_t amount);

// Arithmetic operators
LM2_API lm2_r2u64 lm2_r2u64_add(lm2_r2u64 a, lm2_r2u64 b);
LM2_API lm2_r2u64 lm2_r2u64_add_scalar(lm2_r2u64 r, uint64_t s);
LM2_API lm2_r2u64 lm2_r2u64_add_vec(lm2_r2u64 r, lm2_v2u64 v);
LM2_API lm2_r2u64 lm2_r2u64_sub(lm2_r2u64 a, lm2_r2u64 b);
LM2_API lm2_r2u64 lm2_r2u64_sub_scalar(lm2_r2u64 r, uint64_t s);
LM2_API lm2_r2u64 lm2_r2u64_sub_vec(lm2_r2u64 r, lm2_v2u64 v);
LM2_API lm2_r2u64 lm2_r2u64_mul(lm2_r2u64 a, lm2_r2u64 b);
LM2_API lm2_r2u64 lm2_r2u64_mul_scalar(lm2_r2u64 r, uint64_t s);
LM2_API lm2_r2u64 lm2_r2u64_mul_vec(lm2_r2u64 r, lm2_v2u64 v);
LM2_API lm2_r2u64 lm2_r2u64_div(lm2_r2u64 a, lm2_r2u64 b);
LM2_API lm2_r2u64 lm2_r2u64_div_scalar(lm2_r2u64 r, uint64_t s);
LM2_API lm2_r2u64 lm2_r2u64_div_vec(lm2_r2u64 r, lm2_v2u64 v);
LM2_API lm2_r2u64 lm2_r2u64_mod(lm2_r2u64 a, lm2_r2u64 b);
LM2_API lm2_r2u64 lm2_r2u64_mod_scalar(lm2_r2u64 r, uint64_t s);
LM2_API lm2_r2u64 lm2_r2u64_mod_vec(lm2_r2u64 r, lm2_v2u64 v);

// Scalar function forwards
LM2_API lm2_r2u64 lm2_floor_lm2_r2u64(lm2_r2u64 a);
LM2_API lm2_r2u64 lm2_ceil_lm2_r2u64(lm2_r2u64 a);
LM2_API lm2_r2u64 lm2_round_lm2_r2u64(lm2_r2u64 a);
LM2_API lm2_r2u64 lm2_trunc_lm2_r2u64(lm2_r2u64 a);
LM2_API lm2_r2u64 lm2_abs_lm2_r2u64(lm2_r2u64 a);
LM2_API lm2_r2u64 lm2_floor_multiple_lm2_r2u64(lm2_r2u64 a, lm2_r2u64 b);
LM2_API lm2_r2u64 lm2_ceil_multiple_lm2_r2u64(lm2_r2u64 a, lm2_r2u64 b);
LM2_API lm2_r2u64 lm2_round_multiple_lm2_r2u64(lm2_r2u64 a, lm2_r2u64 b);
LM2_API lm2_r2u64 lm2_trunc_multiple_lm2_r2u64(lm2_r2u64 a, lm2_r2u64 b);
LM2_API lm2_r2u64 lm2_min_lm2_r2u64(lm2_r2u64 a, lm2_r2u64 b);
LM2_API lm2_r2u64 lm2_max_lm2_r2u64(lm2_r2u64 a, lm2_r2u64 b);
LM2_API lm2_r2u64 lm2_clamp_lm2_r2u64(lm2_r2u64 a, lm2_r2u64 b, lm2_r2u64 c);
LM2_API lm2_r2u64 lm2_lerp_lm2_r2u64(lm2_r2u64 a, lm2_r2u64 b, lm2_r2u64 c);

// Queries
LM2_API lm2_r2u64 lm2_r2u64_union(lm2_r2u64 a, lm2_r2u64 b);
LM2_API lm2_r2u64 lm2_r2u64_intersection(lm2_r2u64 a, lm2_r2u64 b);
LM2_API lm2_v2u64 lm2_r2u64_size(lm2_r2u64 r);
LM2_API lm2_v2u64 lm2_r2u64_extents(lm2_r2u64 r);
LM2_API lm2_v2u64 lm2_r2u64_center(lm2_r2u64 r);
LM2_API int lm2_r2u64_contains_point(lm2_r2u64 r, lm2_v2u64 point);
LM2_API int lm2_r2u64_overlaps(lm2_r2u64 a, lm2_r2u64 b);
LM2_API uint64_t lm2_r2u64_area(lm2_r2u64 r);

// ---------------------------------------------------------------------------
// lm2_r2u32 - 2D Range (32-bit unsigned integer)
// ---------------------------------------------------------------------------
typedef union lm2_r2u32 {
  lm2_v2u32 e[2];
  struct {
    lm2_v2u32 min;
    lm2_v2u32 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v2u32)
} lm2_r2u32;

// Constructors
LM2_API lm2_r2u32 lm2_r2u32_from_min_max(lm2_v2u32 min, lm2_v2u32 max);
LM2_API lm2_r2u32 lm2_r2u32_from_center_extents(lm2_v2u32 center, lm2_v2u32 extents);
LM2_API lm2_r2u32 lm2_r2u32_from_center_size(lm2_v2u32 center, lm2_v2u32 size);
LM2_API lm2_r2u32 lm2_r2u32_from_position_size(lm2_v2u32 position, lm2_v2u32 size);
LM2_API lm2_r2u32 lm2_r2u32_zero(void);

// Operations
LM2_API lm2_r2u32 lm2_r2u32_normalize(lm2_r2u32 r);
LM2_API lm2_r2u32 lm2_r2u32_translate(lm2_r2u32 r, lm2_v2u32 offset);
LM2_API lm2_r2u32 lm2_r2u32_scale(lm2_r2u32 r, uint32_t factor);
LM2_API lm2_r2u32 lm2_r2u32_expand(lm2_r2u32 r, uint32_t amount);

// Arithmetic operators
LM2_API lm2_r2u32 lm2_r2u32_add(lm2_r2u32 a, lm2_r2u32 b);
LM2_API lm2_r2u32 lm2_r2u32_add_scalar(lm2_r2u32 r, uint32_t s);
LM2_API lm2_r2u32 lm2_r2u32_add_vec(lm2_r2u32 r, lm2_v2u32 v);
LM2_API lm2_r2u32 lm2_r2u32_sub(lm2_r2u32 a, lm2_r2u32 b);
LM2_API lm2_r2u32 lm2_r2u32_sub_scalar(lm2_r2u32 r, uint32_t s);
LM2_API lm2_r2u32 lm2_r2u32_sub_vec(lm2_r2u32 r, lm2_v2u32 v);
LM2_API lm2_r2u32 lm2_r2u32_mul(lm2_r2u32 a, lm2_r2u32 b);
LM2_API lm2_r2u32 lm2_r2u32_mul_scalar(lm2_r2u32 r, uint32_t s);
LM2_API lm2_r2u32 lm2_r2u32_mul_vec(lm2_r2u32 r, lm2_v2u32 v);
LM2_API lm2_r2u32 lm2_r2u32_div(lm2_r2u32 a, lm2_r2u32 b);
LM2_API lm2_r2u32 lm2_r2u32_div_scalar(lm2_r2u32 r, uint32_t s);
LM2_API lm2_r2u32 lm2_r2u32_div_vec(lm2_r2u32 r, lm2_v2u32 v);
LM2_API lm2_r2u32 lm2_r2u32_mod(lm2_r2u32 a, lm2_r2u32 b);
LM2_API lm2_r2u32 lm2_r2u32_mod_scalar(lm2_r2u32 r, uint32_t s);
LM2_API lm2_r2u32 lm2_r2u32_mod_vec(lm2_r2u32 r, lm2_v2u32 v);

// Scalar function forwards
LM2_API lm2_r2u32 lm2_floor_lm2_r2u32(lm2_r2u32 a);
LM2_API lm2_r2u32 lm2_ceil_lm2_r2u32(lm2_r2u32 a);
LM2_API lm2_r2u32 lm2_round_lm2_r2u32(lm2_r2u32 a);
LM2_API lm2_r2u32 lm2_trunc_lm2_r2u32(lm2_r2u32 a);
LM2_API lm2_r2u32 lm2_abs_lm2_r2u32(lm2_r2u32 a);
LM2_API lm2_r2u32 lm2_floor_multiple_lm2_r2u32(lm2_r2u32 a, lm2_r2u32 b);
LM2_API lm2_r2u32 lm2_ceil_multiple_lm2_r2u32(lm2_r2u32 a, lm2_r2u32 b);
LM2_API lm2_r2u32 lm2_round_multiple_lm2_r2u32(lm2_r2u32 a, lm2_r2u32 b);
LM2_API lm2_r2u32 lm2_trunc_multiple_lm2_r2u32(lm2_r2u32 a, lm2_r2u32 b);
LM2_API lm2_r2u32 lm2_min_lm2_r2u32(lm2_r2u32 a, lm2_r2u32 b);
LM2_API lm2_r2u32 lm2_max_lm2_r2u32(lm2_r2u32 a, lm2_r2u32 b);
LM2_API lm2_r2u32 lm2_clamp_lm2_r2u32(lm2_r2u32 a, lm2_r2u32 b, lm2_r2u32 c);
LM2_API lm2_r2u32 lm2_lerp_lm2_r2u32(lm2_r2u32 a, lm2_r2u32 b, lm2_r2u32 c);

// Queries
LM2_API lm2_r2u32 lm2_r2u32_union(lm2_r2u32 a, lm2_r2u32 b);
LM2_API lm2_r2u32 lm2_r2u32_intersection(lm2_r2u32 a, lm2_r2u32 b);
LM2_API lm2_v2u32 lm2_r2u32_size(lm2_r2u32 r);
LM2_API lm2_v2u32 lm2_r2u32_extents(lm2_r2u32 r);
LM2_API lm2_v2u32 lm2_r2u32_center(lm2_r2u32 r);
LM2_API int lm2_r2u32_contains_point(lm2_r2u32 r, lm2_v2u32 point);
LM2_API int lm2_r2u32_overlaps(lm2_r2u32 a, lm2_r2u32 b);
LM2_API uint32_t lm2_r2u32_area(lm2_r2u32 r);

// ---------------------------------------------------------------------------
// lm2_r2u16 - 2D Range (16-bit unsigned integer)
// ---------------------------------------------------------------------------
typedef union lm2_r2u16 {
  lm2_v2u16 e[2];
  struct {
    lm2_v2u16 min;
    lm2_v2u16 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v2u16)
} lm2_r2u16;

// Constructors
LM2_API lm2_r2u16 lm2_r2u16_from_min_max(lm2_v2u16 min, lm2_v2u16 max);
LM2_API lm2_r2u16 lm2_r2u16_from_center_extents(lm2_v2u16 center, lm2_v2u16 extents);
LM2_API lm2_r2u16 lm2_r2u16_from_center_size(lm2_v2u16 center, lm2_v2u16 size);
LM2_API lm2_r2u16 lm2_r2u16_from_position_size(lm2_v2u16 position, lm2_v2u16 size);
LM2_API lm2_r2u16 lm2_r2u16_zero(void);

// Operations
LM2_API lm2_r2u16 lm2_r2u16_normalize(lm2_r2u16 r);
LM2_API lm2_r2u16 lm2_r2u16_translate(lm2_r2u16 r, lm2_v2u16 offset);
LM2_API lm2_r2u16 lm2_r2u16_scale(lm2_r2u16 r, uint16_t factor);
LM2_API lm2_r2u16 lm2_r2u16_expand(lm2_r2u16 r, uint16_t amount);

// Arithmetic operators
LM2_API lm2_r2u16 lm2_r2u16_add(lm2_r2u16 a, lm2_r2u16 b);
LM2_API lm2_r2u16 lm2_r2u16_add_scalar(lm2_r2u16 r, uint16_t s);
LM2_API lm2_r2u16 lm2_r2u16_add_vec(lm2_r2u16 r, lm2_v2u16 v);
LM2_API lm2_r2u16 lm2_r2u16_sub(lm2_r2u16 a, lm2_r2u16 b);
LM2_API lm2_r2u16 lm2_r2u16_sub_scalar(lm2_r2u16 r, uint16_t s);
LM2_API lm2_r2u16 lm2_r2u16_sub_vec(lm2_r2u16 r, lm2_v2u16 v);
LM2_API lm2_r2u16 lm2_r2u16_mul(lm2_r2u16 a, lm2_r2u16 b);
LM2_API lm2_r2u16 lm2_r2u16_mul_scalar(lm2_r2u16 r, uint16_t s);
LM2_API lm2_r2u16 lm2_r2u16_mul_vec(lm2_r2u16 r, lm2_v2u16 v);
LM2_API lm2_r2u16 lm2_r2u16_div(lm2_r2u16 a, lm2_r2u16 b);
LM2_API lm2_r2u16 lm2_r2u16_div_scalar(lm2_r2u16 r, uint16_t s);
LM2_API lm2_r2u16 lm2_r2u16_div_vec(lm2_r2u16 r, lm2_v2u16 v);
LM2_API lm2_r2u16 lm2_r2u16_mod(lm2_r2u16 a, lm2_r2u16 b);
LM2_API lm2_r2u16 lm2_r2u16_mod_scalar(lm2_r2u16 r, uint16_t s);
LM2_API lm2_r2u16 lm2_r2u16_mod_vec(lm2_r2u16 r, lm2_v2u16 v);

// Scalar function forwards
LM2_API lm2_r2u16 lm2_floor_lm2_r2u16(lm2_r2u16 a);
LM2_API lm2_r2u16 lm2_ceil_lm2_r2u16(lm2_r2u16 a);
LM2_API lm2_r2u16 lm2_round_lm2_r2u16(lm2_r2u16 a);
LM2_API lm2_r2u16 lm2_trunc_lm2_r2u16(lm2_r2u16 a);
LM2_API lm2_r2u16 lm2_abs_lm2_r2u16(lm2_r2u16 a);
LM2_API lm2_r2u16 lm2_floor_multiple_lm2_r2u16(lm2_r2u16 a, lm2_r2u16 b);
LM2_API lm2_r2u16 lm2_ceil_multiple_lm2_r2u16(lm2_r2u16 a, lm2_r2u16 b);
LM2_API lm2_r2u16 lm2_round_multiple_lm2_r2u16(lm2_r2u16 a, lm2_r2u16 b);
LM2_API lm2_r2u16 lm2_trunc_multiple_lm2_r2u16(lm2_r2u16 a, lm2_r2u16 b);
LM2_API lm2_r2u16 lm2_min_lm2_r2u16(lm2_r2u16 a, lm2_r2u16 b);
LM2_API lm2_r2u16 lm2_max_lm2_r2u16(lm2_r2u16 a, lm2_r2u16 b);
LM2_API lm2_r2u16 lm2_clamp_lm2_r2u16(lm2_r2u16 a, lm2_r2u16 b, lm2_r2u16 c);
LM2_API lm2_r2u16 lm2_lerp_lm2_r2u16(lm2_r2u16 a, lm2_r2u16 b, lm2_r2u16 c);

// Queries
LM2_API lm2_r2u16 lm2_r2u16_union(lm2_r2u16 a, lm2_r2u16 b);
LM2_API lm2_r2u16 lm2_r2u16_intersection(lm2_r2u16 a, lm2_r2u16 b);
LM2_API lm2_v2u16 lm2_r2u16_size(lm2_r2u16 r);
LM2_API lm2_v2u16 lm2_r2u16_extents(lm2_r2u16 r);
LM2_API lm2_v2u16 lm2_r2u16_center(lm2_r2u16 r);
LM2_API int lm2_r2u16_contains_point(lm2_r2u16 r, lm2_v2u16 point);
LM2_API int lm2_r2u16_overlaps(lm2_r2u16 a, lm2_r2u16 b);
LM2_API uint16_t lm2_r2u16_area(lm2_r2u16 r);

// ---------------------------------------------------------------------------
// lm2_r2u8 - 2D Range (8-bit unsigned integer)
// ---------------------------------------------------------------------------
typedef union lm2_r2u8 {
  lm2_v2u8 e[2];
  struct {
    lm2_v2u8 min;
    lm2_v2u8 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v2u8)
} lm2_r2u8;

// Constructors
LM2_API lm2_r2u8 lm2_r2u8_from_min_max(lm2_v2u8 min, lm2_v2u8 max);
LM2_API lm2_r2u8 lm2_r2u8_from_center_extents(lm2_v2u8 center, lm2_v2u8 extents);
LM2_API lm2_r2u8 lm2_r2u8_from_center_size(lm2_v2u8 center, lm2_v2u8 size);
LM2_API lm2_r2u8 lm2_r2u8_from_position_size(lm2_v2u8 position, lm2_v2u8 size);
LM2_API lm2_r2u8 lm2_r2u8_zero(void);

// Operations
LM2_API lm2_r2u8 lm2_r2u8_normalize(lm2_r2u8 r);
LM2_API lm2_r2u8 lm2_r2u8_translate(lm2_r2u8 r, lm2_v2u8 offset);
LM2_API lm2_r2u8 lm2_r2u8_scale(lm2_r2u8 r, uint8_t factor);
LM2_API lm2_r2u8 lm2_r2u8_expand(lm2_r2u8 r, uint8_t amount);

// Arithmetic operators
LM2_API lm2_r2u8 lm2_r2u8_add(lm2_r2u8 a, lm2_r2u8 b);
LM2_API lm2_r2u8 lm2_r2u8_add_scalar(lm2_r2u8 r, uint8_t s);
LM2_API lm2_r2u8 lm2_r2u8_add_vec(lm2_r2u8 r, lm2_v2u8 v);
LM2_API lm2_r2u8 lm2_r2u8_sub(lm2_r2u8 a, lm2_r2u8 b);
LM2_API lm2_r2u8 lm2_r2u8_sub_scalar(lm2_r2u8 r, uint8_t s);
LM2_API lm2_r2u8 lm2_r2u8_sub_vec(lm2_r2u8 r, lm2_v2u8 v);
LM2_API lm2_r2u8 lm2_r2u8_mul(lm2_r2u8 a, lm2_r2u8 b);
LM2_API lm2_r2u8 lm2_r2u8_mul_scalar(lm2_r2u8 r, uint8_t s);
LM2_API lm2_r2u8 lm2_r2u8_mul_vec(lm2_r2u8 r, lm2_v2u8 v);
LM2_API lm2_r2u8 lm2_r2u8_div(lm2_r2u8 a, lm2_r2u8 b);
LM2_API lm2_r2u8 lm2_r2u8_div_scalar(lm2_r2u8 r, uint8_t s);
LM2_API lm2_r2u8 lm2_r2u8_div_vec(lm2_r2u8 r, lm2_v2u8 v);
LM2_API lm2_r2u8 lm2_r2u8_mod(lm2_r2u8 a, lm2_r2u8 b);
LM2_API lm2_r2u8 lm2_r2u8_mod_scalar(lm2_r2u8 r, uint8_t s);
LM2_API lm2_r2u8 lm2_r2u8_mod_vec(lm2_r2u8 r, lm2_v2u8 v);

// Scalar function forwards
LM2_API lm2_r2u8 lm2_floor_lm2_r2u8(lm2_r2u8 a);
LM2_API lm2_r2u8 lm2_ceil_lm2_r2u8(lm2_r2u8 a);
LM2_API lm2_r2u8 lm2_round_lm2_r2u8(lm2_r2u8 a);
LM2_API lm2_r2u8 lm2_trunc_lm2_r2u8(lm2_r2u8 a);
LM2_API lm2_r2u8 lm2_abs_lm2_r2u8(lm2_r2u8 a);
LM2_API lm2_r2u8 lm2_floor_multiple_lm2_r2u8(lm2_r2u8 a, lm2_r2u8 b);
LM2_API lm2_r2u8 lm2_ceil_multiple_lm2_r2u8(lm2_r2u8 a, lm2_r2u8 b);
LM2_API lm2_r2u8 lm2_round_multiple_lm2_r2u8(lm2_r2u8 a, lm2_r2u8 b);
LM2_API lm2_r2u8 lm2_trunc_multiple_lm2_r2u8(lm2_r2u8 a, lm2_r2u8 b);
LM2_API lm2_r2u8 lm2_min_lm2_r2u8(lm2_r2u8 a, lm2_r2u8 b);
LM2_API lm2_r2u8 lm2_max_lm2_r2u8(lm2_r2u8 a, lm2_r2u8 b);
LM2_API lm2_r2u8 lm2_clamp_lm2_r2u8(lm2_r2u8 a, lm2_r2u8 b, lm2_r2u8 c);
LM2_API lm2_r2u8 lm2_lerp_lm2_r2u8(lm2_r2u8 a, lm2_r2u8 b, lm2_r2u8 c);

// Queries
LM2_API lm2_r2u8 lm2_r2u8_union(lm2_r2u8 a, lm2_r2u8 b);
LM2_API lm2_r2u8 lm2_r2u8_intersection(lm2_r2u8 a, lm2_r2u8 b);
LM2_API lm2_v2u8 lm2_r2u8_size(lm2_r2u8 r);
LM2_API lm2_v2u8 lm2_r2u8_extents(lm2_r2u8 r);
LM2_API lm2_v2u8 lm2_r2u8_center(lm2_r2u8 r);
LM2_API int lm2_r2u8_contains_point(lm2_r2u8 r, lm2_v2u8 point);
LM2_API int lm2_r2u8_overlaps(lm2_r2u8 a, lm2_r2u8 b);
LM2_API uint8_t lm2_r2u8_area(lm2_r2u8 r);

// Default range2 type (float-based)
typedef lm2_r2f32 lm2_r2;

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// C++ operator overloads and constructors (must be outside extern "C")
#ifndef LM2_NO_CPP_OPERATORS
#  include "lm2_range_operators.h"
_LM2_DEFINE_RANGE2_OPERATORS(lm2_r2f64, lm2_v2f64)
_LM2_DEFINE_RANGE2_OPERATORS(lm2_r2f32, lm2_v2f32)
_LM2_DEFINE_RANGE2_OPERATORS(lm2_r2i64, lm2_v2i64)
_LM2_DEFINE_RANGE2_OPERATORS(lm2_r2i32, lm2_v2i32)
_LM2_DEFINE_RANGE2_OPERATORS(lm2_r2i16, lm2_v2i16)
_LM2_DEFINE_RANGE2_OPERATORS(lm2_r2i8, lm2_v2i8)
_LM2_DEFINE_RANGE2_OPERATORS(lm2_r2u64, lm2_v2u64)
_LM2_DEFINE_RANGE2_OPERATORS(lm2_r2u32, lm2_v2u32)
_LM2_DEFINE_RANGE2_OPERATORS(lm2_r2u16, lm2_v2u16)
_LM2_DEFINE_RANGE2_OPERATORS(lm2_r2u8, lm2_v2u8)
#endif
