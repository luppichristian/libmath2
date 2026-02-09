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
#include "lm2/vectors/lm2_vector4.h"
#include "lm2_range_defines.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// 4D Range (AABB) Type Definitions
// =============================================================================
// A range4 represents a 4D axis-aligned bounding box (hyperrectangle)
// with minimum and maximum points.

// ---------------------------------------------------------------------------
// lm2_r4f64 - 4D Range (double precision)
// ---------------------------------------------------------------------------
typedef union lm2_r4f64 {
  lm2_v4f64 e[2];
  struct {
    lm2_v4f64 min;
    lm2_v4f64 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v4f64)
} lm2_r4f64;

// Constructors
LM2_API lm2_r4f64 lm2_r4f64_from_min_max(lm2_v4f64 min, lm2_v4f64 max);
LM2_API lm2_r4f64 lm2_r4f64_from_center_extents(lm2_v4f64 center, lm2_v4f64 extents);
LM2_API lm2_r4f64 lm2_r4f64_from_center_size(lm2_v4f64 center, lm2_v4f64 size);
LM2_API lm2_r4f64 lm2_r4f64_from_position_size(lm2_v4f64 position, lm2_v4f64 size);
LM2_API lm2_r4f64 lm2_r4f64_zero(void);

// Operations
LM2_API lm2_r4f64 lm2_r4f64_normalize(lm2_r4f64 r);
LM2_API lm2_r4f64 lm2_r4f64_translate(lm2_r4f64 r, lm2_v4f64 offset);
LM2_API lm2_r4f64 lm2_r4f64_scale(lm2_r4f64 r, double factor);
LM2_API lm2_r4f64 lm2_r4f64_expand(lm2_r4f64 r, double amount);

// Arithmetic operators
LM2_API lm2_r4f64 lm2_r4f64_add(lm2_r4f64 a, lm2_r4f64 b);
LM2_API lm2_r4f64 lm2_r4f64_add_scalar(lm2_r4f64 r, double s);
LM2_API lm2_r4f64 lm2_r4f64_add_vec(lm2_r4f64 r, lm2_v4f64 v);
LM2_API lm2_r4f64 lm2_r4f64_sub(lm2_r4f64 a, lm2_r4f64 b);
LM2_API lm2_r4f64 lm2_r4f64_sub_scalar(lm2_r4f64 r, double s);
LM2_API lm2_r4f64 lm2_r4f64_sub_vec(lm2_r4f64 r, lm2_v4f64 v);
LM2_API lm2_r4f64 lm2_r4f64_mul(lm2_r4f64 a, lm2_r4f64 b);
LM2_API lm2_r4f64 lm2_r4f64_mul_scalar(lm2_r4f64 r, double s);
LM2_API lm2_r4f64 lm2_r4f64_mul_vec(lm2_r4f64 r, lm2_v4f64 v);
LM2_API lm2_r4f64 lm2_r4f64_div(lm2_r4f64 a, lm2_r4f64 b);
LM2_API lm2_r4f64 lm2_r4f64_div_scalar(lm2_r4f64 r, double s);
LM2_API lm2_r4f64 lm2_r4f64_div_vec(lm2_r4f64 r, lm2_v4f64 v);
LM2_API lm2_r4f64 lm2_r4f64_mod(lm2_r4f64 a, lm2_r4f64 b);
LM2_API lm2_r4f64 lm2_r4f64_mod_scalar(lm2_r4f64 r, double s);
LM2_API lm2_r4f64 lm2_r4f64_mod_vec(lm2_r4f64 r, lm2_v4f64 v);

// Scalar function forwards
LM2_API lm2_r4f64 lm2_floor_lm2_r4f64(lm2_r4f64 a);
LM2_API lm2_r4f64 lm2_ceil_lm2_r4f64(lm2_r4f64 a);
LM2_API lm2_r4f64 lm2_round_lm2_r4f64(lm2_r4f64 a);
LM2_API lm2_r4f64 lm2_trunc_lm2_r4f64(lm2_r4f64 a);
LM2_API lm2_r4f64 lm2_abs_lm2_r4f64(lm2_r4f64 a);
LM2_API lm2_r4f64 lm2_floor_multiple_lm2_r4f64(lm2_r4f64 a, lm2_r4f64 b);
LM2_API lm2_r4f64 lm2_ceil_multiple_lm2_r4f64(lm2_r4f64 a, lm2_r4f64 b);
LM2_API lm2_r4f64 lm2_round_multiple_lm2_r4f64(lm2_r4f64 a, lm2_r4f64 b);
LM2_API lm2_r4f64 lm2_trunc_multiple_lm2_r4f64(lm2_r4f64 a, lm2_r4f64 b);
LM2_API lm2_r4f64 lm2_min_lm2_r4f64(lm2_r4f64 a, lm2_r4f64 b);
LM2_API lm2_r4f64 lm2_max_lm2_r4f64(lm2_r4f64 a, lm2_r4f64 b);
LM2_API lm2_r4f64 lm2_clamp_lm2_r4f64(lm2_r4f64 a, lm2_r4f64 b, lm2_r4f64 c);
LM2_API lm2_r4f64 lm2_lerp_lm2_r4f64(lm2_r4f64 a, lm2_r4f64 b, lm2_r4f64 c);

// Queries
LM2_API lm2_r4f64 lm2_r4f64_union(lm2_r4f64 a, lm2_r4f64 b);
LM2_API lm2_r4f64 lm2_r4f64_intersection(lm2_r4f64 a, lm2_r4f64 b);
LM2_API lm2_v4f64 lm2_r4f64_size(lm2_r4f64 r);
LM2_API lm2_v4f64 lm2_r4f64_extents(lm2_r4f64 r);
LM2_API lm2_v4f64 lm2_r4f64_center(lm2_r4f64 r);
LM2_API int lm2_r4f64_contains_point(lm2_r4f64 r, lm2_v4f64 point);
LM2_API int lm2_r4f64_overlaps(lm2_r4f64 a, lm2_r4f64 b);
LM2_API double lm2_r4f64_hypervolume(lm2_r4f64 r);

// ---------------------------------------------------------------------------
// lm2_r4f32 - 4D Range (single precision)
// ---------------------------------------------------------------------------
typedef union lm2_r4f32 {
  lm2_v4f32 e[2];
  struct {
    lm2_v4f32 min;
    lm2_v4f32 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v4f32)
} lm2_r4f32;

// Constructors
LM2_API lm2_r4f32 lm2_r4f32_from_min_max(lm2_v4f32 min, lm2_v4f32 max);
LM2_API lm2_r4f32 lm2_r4f32_from_center_extents(lm2_v4f32 center, lm2_v4f32 extents);
LM2_API lm2_r4f32 lm2_r4f32_from_center_size(lm2_v4f32 center, lm2_v4f32 size);
LM2_API lm2_r4f32 lm2_r4f32_from_position_size(lm2_v4f32 position, lm2_v4f32 size);
LM2_API lm2_r4f32 lm2_r4f32_zero(void);

// Operations
LM2_API lm2_r4f32 lm2_r4f32_normalize(lm2_r4f32 r);
LM2_API lm2_r4f32 lm2_r4f32_translate(lm2_r4f32 r, lm2_v4f32 offset);
LM2_API lm2_r4f32 lm2_r4f32_scale(lm2_r4f32 r, float factor);
LM2_API lm2_r4f32 lm2_r4f32_expand(lm2_r4f32 r, float amount);

// Arithmetic operators
LM2_API lm2_r4f32 lm2_r4f32_add(lm2_r4f32 a, lm2_r4f32 b);
LM2_API lm2_r4f32 lm2_r4f32_add_scalar(lm2_r4f32 r, float s);
LM2_API lm2_r4f32 lm2_r4f32_add_vec(lm2_r4f32 r, lm2_v4f32 v);
LM2_API lm2_r4f32 lm2_r4f32_sub(lm2_r4f32 a, lm2_r4f32 b);
LM2_API lm2_r4f32 lm2_r4f32_sub_scalar(lm2_r4f32 r, float s);
LM2_API lm2_r4f32 lm2_r4f32_sub_vec(lm2_r4f32 r, lm2_v4f32 v);
LM2_API lm2_r4f32 lm2_r4f32_mul(lm2_r4f32 a, lm2_r4f32 b);
LM2_API lm2_r4f32 lm2_r4f32_mul_scalar(lm2_r4f32 r, float s);
LM2_API lm2_r4f32 lm2_r4f32_mul_vec(lm2_r4f32 r, lm2_v4f32 v);
LM2_API lm2_r4f32 lm2_r4f32_div(lm2_r4f32 a, lm2_r4f32 b);
LM2_API lm2_r4f32 lm2_r4f32_div_scalar(lm2_r4f32 r, float s);
LM2_API lm2_r4f32 lm2_r4f32_div_vec(lm2_r4f32 r, lm2_v4f32 v);
LM2_API lm2_r4f32 lm2_r4f32_mod(lm2_r4f32 a, lm2_r4f32 b);
LM2_API lm2_r4f32 lm2_r4f32_mod_scalar(lm2_r4f32 r, float s);
LM2_API lm2_r4f32 lm2_r4f32_mod_vec(lm2_r4f32 r, lm2_v4f32 v);

// Scalar function forwards
LM2_API lm2_r4f32 lm2_floor_lm2_r4f32(lm2_r4f32 a);
LM2_API lm2_r4f32 lm2_ceil_lm2_r4f32(lm2_r4f32 a);
LM2_API lm2_r4f32 lm2_round_lm2_r4f32(lm2_r4f32 a);
LM2_API lm2_r4f32 lm2_trunc_lm2_r4f32(lm2_r4f32 a);
LM2_API lm2_r4f32 lm2_abs_lm2_r4f32(lm2_r4f32 a);
LM2_API lm2_r4f32 lm2_floor_multiple_lm2_r4f32(lm2_r4f32 a, lm2_r4f32 b);
LM2_API lm2_r4f32 lm2_ceil_multiple_lm2_r4f32(lm2_r4f32 a, lm2_r4f32 b);
LM2_API lm2_r4f32 lm2_round_multiple_lm2_r4f32(lm2_r4f32 a, lm2_r4f32 b);
LM2_API lm2_r4f32 lm2_trunc_multiple_lm2_r4f32(lm2_r4f32 a, lm2_r4f32 b);
LM2_API lm2_r4f32 lm2_min_lm2_r4f32(lm2_r4f32 a, lm2_r4f32 b);
LM2_API lm2_r4f32 lm2_max_lm2_r4f32(lm2_r4f32 a, lm2_r4f32 b);
LM2_API lm2_r4f32 lm2_clamp_lm2_r4f32(lm2_r4f32 a, lm2_r4f32 b, lm2_r4f32 c);
LM2_API lm2_r4f32 lm2_lerp_lm2_r4f32(lm2_r4f32 a, lm2_r4f32 b, lm2_r4f32 c);

// Queries
LM2_API lm2_r4f32 lm2_r4f32_union(lm2_r4f32 a, lm2_r4f32 b);
LM2_API lm2_r4f32 lm2_r4f32_intersection(lm2_r4f32 a, lm2_r4f32 b);
LM2_API lm2_v4f32 lm2_r4f32_size(lm2_r4f32 r);
LM2_API lm2_v4f32 lm2_r4f32_extents(lm2_r4f32 r);
LM2_API lm2_v4f32 lm2_r4f32_center(lm2_r4f32 r);
LM2_API int lm2_r4f32_contains_point(lm2_r4f32 r, lm2_v4f32 point);
LM2_API int lm2_r4f32_overlaps(lm2_r4f32 a, lm2_r4f32 b);
LM2_API float lm2_r4f32_hypervolume(lm2_r4f32 r);

// ---------------------------------------------------------------------------
// lm2_r4i64 - 4D Range (64-bit signed integer)
// ---------------------------------------------------------------------------
typedef union lm2_r4i64 {
  lm2_v4i64 e[2];
  struct {
    lm2_v4i64 min;
    lm2_v4i64 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v4i64)
} lm2_r4i64;

// Constructors
LM2_API lm2_r4i64 lm2_r4i64_from_min_max(lm2_v4i64 min, lm2_v4i64 max);
LM2_API lm2_r4i64 lm2_r4i64_from_center_extents(lm2_v4i64 center, lm2_v4i64 extents);
LM2_API lm2_r4i64 lm2_r4i64_from_center_size(lm2_v4i64 center, lm2_v4i64 size);
LM2_API lm2_r4i64 lm2_r4i64_from_position_size(lm2_v4i64 position, lm2_v4i64 size);
LM2_API lm2_r4i64 lm2_r4i64_zero(void);

// Operations
LM2_API lm2_r4i64 lm2_r4i64_normalize(lm2_r4i64 r);
LM2_API lm2_r4i64 lm2_r4i64_translate(lm2_r4i64 r, lm2_v4i64 offset);
LM2_API lm2_r4i64 lm2_r4i64_scale(lm2_r4i64 r, int64_t factor);
LM2_API lm2_r4i64 lm2_r4i64_expand(lm2_r4i64 r, int64_t amount);

// Arithmetic operators
LM2_API lm2_r4i64 lm2_r4i64_add(lm2_r4i64 a, lm2_r4i64 b);
LM2_API lm2_r4i64 lm2_r4i64_add_scalar(lm2_r4i64 r, int64_t s);
LM2_API lm2_r4i64 lm2_r4i64_add_vec(lm2_r4i64 r, lm2_v4i64 v);
LM2_API lm2_r4i64 lm2_r4i64_sub(lm2_r4i64 a, lm2_r4i64 b);
LM2_API lm2_r4i64 lm2_r4i64_sub_scalar(lm2_r4i64 r, int64_t s);
LM2_API lm2_r4i64 lm2_r4i64_sub_vec(lm2_r4i64 r, lm2_v4i64 v);
LM2_API lm2_r4i64 lm2_r4i64_mul(lm2_r4i64 a, lm2_r4i64 b);
LM2_API lm2_r4i64 lm2_r4i64_mul_scalar(lm2_r4i64 r, int64_t s);
LM2_API lm2_r4i64 lm2_r4i64_mul_vec(lm2_r4i64 r, lm2_v4i64 v);
LM2_API lm2_r4i64 lm2_r4i64_div(lm2_r4i64 a, lm2_r4i64 b);
LM2_API lm2_r4i64 lm2_r4i64_div_scalar(lm2_r4i64 r, int64_t s);
LM2_API lm2_r4i64 lm2_r4i64_div_vec(lm2_r4i64 r, lm2_v4i64 v);
LM2_API lm2_r4i64 lm2_r4i64_mod(lm2_r4i64 a, lm2_r4i64 b);
LM2_API lm2_r4i64 lm2_r4i64_mod_scalar(lm2_r4i64 r, int64_t s);
LM2_API lm2_r4i64 lm2_r4i64_mod_vec(lm2_r4i64 r, lm2_v4i64 v);

// Scalar function forwards
LM2_API lm2_r4i64 lm2_floor_lm2_r4i64(lm2_r4i64 a);
LM2_API lm2_r4i64 lm2_ceil_lm2_r4i64(lm2_r4i64 a);
LM2_API lm2_r4i64 lm2_round_lm2_r4i64(lm2_r4i64 a);
LM2_API lm2_r4i64 lm2_trunc_lm2_r4i64(lm2_r4i64 a);
LM2_API lm2_r4i64 lm2_abs_lm2_r4i64(lm2_r4i64 a);
LM2_API lm2_r4i64 lm2_floor_multiple_lm2_r4i64(lm2_r4i64 a, lm2_r4i64 b);
LM2_API lm2_r4i64 lm2_ceil_multiple_lm2_r4i64(lm2_r4i64 a, lm2_r4i64 b);
LM2_API lm2_r4i64 lm2_round_multiple_lm2_r4i64(lm2_r4i64 a, lm2_r4i64 b);
LM2_API lm2_r4i64 lm2_trunc_multiple_lm2_r4i64(lm2_r4i64 a, lm2_r4i64 b);
LM2_API lm2_r4i64 lm2_min_lm2_r4i64(lm2_r4i64 a, lm2_r4i64 b);
LM2_API lm2_r4i64 lm2_max_lm2_r4i64(lm2_r4i64 a, lm2_r4i64 b);
LM2_API lm2_r4i64 lm2_clamp_lm2_r4i64(lm2_r4i64 a, lm2_r4i64 b, lm2_r4i64 c);
LM2_API lm2_r4i64 lm2_lerp_lm2_r4i64(lm2_r4i64 a, lm2_r4i64 b, lm2_r4i64 c);

// Queries
LM2_API lm2_r4i64 lm2_r4i64_union(lm2_r4i64 a, lm2_r4i64 b);
LM2_API lm2_r4i64 lm2_r4i64_intersection(lm2_r4i64 a, lm2_r4i64 b);
LM2_API lm2_v4i64 lm2_r4i64_size(lm2_r4i64 r);
LM2_API lm2_v4i64 lm2_r4i64_extents(lm2_r4i64 r);
LM2_API lm2_v4i64 lm2_r4i64_center(lm2_r4i64 r);
LM2_API int lm2_r4i64_contains_point(lm2_r4i64 r, lm2_v4i64 point);
LM2_API int lm2_r4i64_overlaps(lm2_r4i64 a, lm2_r4i64 b);
LM2_API int64_t lm2_r4i64_hypervolume(lm2_r4i64 r);

// ---------------------------------------------------------------------------
// lm2_r4i32 - 4D Range (32-bit signed integer)
// ---------------------------------------------------------------------------
typedef union lm2_r4i32 {
  lm2_v4i32 e[2];
  struct {
    lm2_v4i32 min;
    lm2_v4i32 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v4i32)
} lm2_r4i32;

// Constructors
LM2_API lm2_r4i32 lm2_r4i32_from_min_max(lm2_v4i32 min, lm2_v4i32 max);
LM2_API lm2_r4i32 lm2_r4i32_from_center_extents(lm2_v4i32 center, lm2_v4i32 extents);
LM2_API lm2_r4i32 lm2_r4i32_from_center_size(lm2_v4i32 center, lm2_v4i32 size);
LM2_API lm2_r4i32 lm2_r4i32_from_position_size(lm2_v4i32 position, lm2_v4i32 size);
LM2_API lm2_r4i32 lm2_r4i32_zero(void);

// Operations
LM2_API lm2_r4i32 lm2_r4i32_normalize(lm2_r4i32 r);
LM2_API lm2_r4i32 lm2_r4i32_translate(lm2_r4i32 r, lm2_v4i32 offset);
LM2_API lm2_r4i32 lm2_r4i32_scale(lm2_r4i32 r, int32_t factor);
LM2_API lm2_r4i32 lm2_r4i32_expand(lm2_r4i32 r, int32_t amount);

// Arithmetic operators
LM2_API lm2_r4i32 lm2_r4i32_add(lm2_r4i32 a, lm2_r4i32 b);
LM2_API lm2_r4i32 lm2_r4i32_add_scalar(lm2_r4i32 r, int32_t s);
LM2_API lm2_r4i32 lm2_r4i32_add_vec(lm2_r4i32 r, lm2_v4i32 v);
LM2_API lm2_r4i32 lm2_r4i32_sub(lm2_r4i32 a, lm2_r4i32 b);
LM2_API lm2_r4i32 lm2_r4i32_sub_scalar(lm2_r4i32 r, int32_t s);
LM2_API lm2_r4i32 lm2_r4i32_sub_vec(lm2_r4i32 r, lm2_v4i32 v);
LM2_API lm2_r4i32 lm2_r4i32_mul(lm2_r4i32 a, lm2_r4i32 b);
LM2_API lm2_r4i32 lm2_r4i32_mul_scalar(lm2_r4i32 r, int32_t s);
LM2_API lm2_r4i32 lm2_r4i32_mul_vec(lm2_r4i32 r, lm2_v4i32 v);
LM2_API lm2_r4i32 lm2_r4i32_div(lm2_r4i32 a, lm2_r4i32 b);
LM2_API lm2_r4i32 lm2_r4i32_div_scalar(lm2_r4i32 r, int32_t s);
LM2_API lm2_r4i32 lm2_r4i32_div_vec(lm2_r4i32 r, lm2_v4i32 v);
LM2_API lm2_r4i32 lm2_r4i32_mod(lm2_r4i32 a, lm2_r4i32 b);
LM2_API lm2_r4i32 lm2_r4i32_mod_scalar(lm2_r4i32 r, int32_t s);
LM2_API lm2_r4i32 lm2_r4i32_mod_vec(lm2_r4i32 r, lm2_v4i32 v);

// Scalar function forwards
LM2_API lm2_r4i32 lm2_floor_lm2_r4i32(lm2_r4i32 a);
LM2_API lm2_r4i32 lm2_ceil_lm2_r4i32(lm2_r4i32 a);
LM2_API lm2_r4i32 lm2_round_lm2_r4i32(lm2_r4i32 a);
LM2_API lm2_r4i32 lm2_trunc_lm2_r4i32(lm2_r4i32 a);
LM2_API lm2_r4i32 lm2_abs_lm2_r4i32(lm2_r4i32 a);
LM2_API lm2_r4i32 lm2_floor_multiple_lm2_r4i32(lm2_r4i32 a, lm2_r4i32 b);
LM2_API lm2_r4i32 lm2_ceil_multiple_lm2_r4i32(lm2_r4i32 a, lm2_r4i32 b);
LM2_API lm2_r4i32 lm2_round_multiple_lm2_r4i32(lm2_r4i32 a, lm2_r4i32 b);
LM2_API lm2_r4i32 lm2_trunc_multiple_lm2_r4i32(lm2_r4i32 a, lm2_r4i32 b);
LM2_API lm2_r4i32 lm2_min_lm2_r4i32(lm2_r4i32 a, lm2_r4i32 b);
LM2_API lm2_r4i32 lm2_max_lm2_r4i32(lm2_r4i32 a, lm2_r4i32 b);
LM2_API lm2_r4i32 lm2_clamp_lm2_r4i32(lm2_r4i32 a, lm2_r4i32 b, lm2_r4i32 c);
LM2_API lm2_r4i32 lm2_lerp_lm2_r4i32(lm2_r4i32 a, lm2_r4i32 b, lm2_r4i32 c);

// Queries
LM2_API lm2_r4i32 lm2_r4i32_union(lm2_r4i32 a, lm2_r4i32 b);
LM2_API lm2_r4i32 lm2_r4i32_intersection(lm2_r4i32 a, lm2_r4i32 b);
LM2_API lm2_v4i32 lm2_r4i32_size(lm2_r4i32 r);
LM2_API lm2_v4i32 lm2_r4i32_extents(lm2_r4i32 r);
LM2_API lm2_v4i32 lm2_r4i32_center(lm2_r4i32 r);
LM2_API int lm2_r4i32_contains_point(lm2_r4i32 r, lm2_v4i32 point);
LM2_API int lm2_r4i32_overlaps(lm2_r4i32 a, lm2_r4i32 b);
LM2_API int32_t lm2_r4i32_hypervolume(lm2_r4i32 r);

// ---------------------------------------------------------------------------
// lm2_r4i16 - 4D Range (16-bit signed integer)
// ---------------------------------------------------------------------------
typedef union lm2_r4i16 {
  lm2_v4i16 e[2];
  struct {
    lm2_v4i16 min;
    lm2_v4i16 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v4i16)
} lm2_r4i16;

// Constructors
LM2_API lm2_r4i16 lm2_r4i16_from_min_max(lm2_v4i16 min, lm2_v4i16 max);
LM2_API lm2_r4i16 lm2_r4i16_from_center_extents(lm2_v4i16 center, lm2_v4i16 extents);
LM2_API lm2_r4i16 lm2_r4i16_from_center_size(lm2_v4i16 center, lm2_v4i16 size);
LM2_API lm2_r4i16 lm2_r4i16_from_position_size(lm2_v4i16 position, lm2_v4i16 size);
LM2_API lm2_r4i16 lm2_r4i16_zero(void);

// Operations
LM2_API lm2_r4i16 lm2_r4i16_normalize(lm2_r4i16 r);
LM2_API lm2_r4i16 lm2_r4i16_translate(lm2_r4i16 r, lm2_v4i16 offset);
LM2_API lm2_r4i16 lm2_r4i16_scale(lm2_r4i16 r, int16_t factor);
LM2_API lm2_r4i16 lm2_r4i16_expand(lm2_r4i16 r, int16_t amount);

// Arithmetic operators
LM2_API lm2_r4i16 lm2_r4i16_add(lm2_r4i16 a, lm2_r4i16 b);
LM2_API lm2_r4i16 lm2_r4i16_add_scalar(lm2_r4i16 r, int16_t s);
LM2_API lm2_r4i16 lm2_r4i16_add_vec(lm2_r4i16 r, lm2_v4i16 v);
LM2_API lm2_r4i16 lm2_r4i16_sub(lm2_r4i16 a, lm2_r4i16 b);
LM2_API lm2_r4i16 lm2_r4i16_sub_scalar(lm2_r4i16 r, int16_t s);
LM2_API lm2_r4i16 lm2_r4i16_sub_vec(lm2_r4i16 r, lm2_v4i16 v);
LM2_API lm2_r4i16 lm2_r4i16_mul(lm2_r4i16 a, lm2_r4i16 b);
LM2_API lm2_r4i16 lm2_r4i16_mul_scalar(lm2_r4i16 r, int16_t s);
LM2_API lm2_r4i16 lm2_r4i16_mul_vec(lm2_r4i16 r, lm2_v4i16 v);
LM2_API lm2_r4i16 lm2_r4i16_div(lm2_r4i16 a, lm2_r4i16 b);
LM2_API lm2_r4i16 lm2_r4i16_div_scalar(lm2_r4i16 r, int16_t s);
LM2_API lm2_r4i16 lm2_r4i16_div_vec(lm2_r4i16 r, lm2_v4i16 v);
LM2_API lm2_r4i16 lm2_r4i16_mod(lm2_r4i16 a, lm2_r4i16 b);
LM2_API lm2_r4i16 lm2_r4i16_mod_scalar(lm2_r4i16 r, int16_t s);
LM2_API lm2_r4i16 lm2_r4i16_mod_vec(lm2_r4i16 r, lm2_v4i16 v);

// Scalar function forwards
LM2_API lm2_r4i16 lm2_floor_lm2_r4i16(lm2_r4i16 a);
LM2_API lm2_r4i16 lm2_ceil_lm2_r4i16(lm2_r4i16 a);
LM2_API lm2_r4i16 lm2_round_lm2_r4i16(lm2_r4i16 a);
LM2_API lm2_r4i16 lm2_trunc_lm2_r4i16(lm2_r4i16 a);
LM2_API lm2_r4i16 lm2_abs_lm2_r4i16(lm2_r4i16 a);
LM2_API lm2_r4i16 lm2_floor_multiple_lm2_r4i16(lm2_r4i16 a, lm2_r4i16 b);
LM2_API lm2_r4i16 lm2_ceil_multiple_lm2_r4i16(lm2_r4i16 a, lm2_r4i16 b);
LM2_API lm2_r4i16 lm2_round_multiple_lm2_r4i16(lm2_r4i16 a, lm2_r4i16 b);
LM2_API lm2_r4i16 lm2_trunc_multiple_lm2_r4i16(lm2_r4i16 a, lm2_r4i16 b);
LM2_API lm2_r4i16 lm2_min_lm2_r4i16(lm2_r4i16 a, lm2_r4i16 b);
LM2_API lm2_r4i16 lm2_max_lm2_r4i16(lm2_r4i16 a, lm2_r4i16 b);
LM2_API lm2_r4i16 lm2_clamp_lm2_r4i16(lm2_r4i16 a, lm2_r4i16 b, lm2_r4i16 c);
LM2_API lm2_r4i16 lm2_lerp_lm2_r4i16(lm2_r4i16 a, lm2_r4i16 b, lm2_r4i16 c);

// Queries
LM2_API lm2_r4i16 lm2_r4i16_union(lm2_r4i16 a, lm2_r4i16 b);
LM2_API lm2_r4i16 lm2_r4i16_intersection(lm2_r4i16 a, lm2_r4i16 b);
LM2_API lm2_v4i16 lm2_r4i16_size(lm2_r4i16 r);
LM2_API lm2_v4i16 lm2_r4i16_extents(lm2_r4i16 r);
LM2_API lm2_v4i16 lm2_r4i16_center(lm2_r4i16 r);
LM2_API int lm2_r4i16_contains_point(lm2_r4i16 r, lm2_v4i16 point);
LM2_API int lm2_r4i16_overlaps(lm2_r4i16 a, lm2_r4i16 b);
LM2_API int16_t lm2_r4i16_hypervolume(lm2_r4i16 r);

// ---------------------------------------------------------------------------
// lm2_r4i8 - 4D Range (8-bit signed integer)
// ---------------------------------------------------------------------------
typedef union lm2_r4i8 {
  lm2_v4i8 e[2];
  struct {
    lm2_v4i8 min;
    lm2_v4i8 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v4i8)
} lm2_r4i8;

// Constructors
LM2_API lm2_r4i8 lm2_r4i8_from_min_max(lm2_v4i8 min, lm2_v4i8 max);
LM2_API lm2_r4i8 lm2_r4i8_from_center_extents(lm2_v4i8 center, lm2_v4i8 extents);
LM2_API lm2_r4i8 lm2_r4i8_from_center_size(lm2_v4i8 center, lm2_v4i8 size);
LM2_API lm2_r4i8 lm2_r4i8_from_position_size(lm2_v4i8 position, lm2_v4i8 size);
LM2_API lm2_r4i8 lm2_r4i8_zero(void);

// Operations
LM2_API lm2_r4i8 lm2_r4i8_normalize(lm2_r4i8 r);
LM2_API lm2_r4i8 lm2_r4i8_translate(lm2_r4i8 r, lm2_v4i8 offset);
LM2_API lm2_r4i8 lm2_r4i8_scale(lm2_r4i8 r, int8_t factor);
LM2_API lm2_r4i8 lm2_r4i8_expand(lm2_r4i8 r, int8_t amount);

// Arithmetic operators
LM2_API lm2_r4i8 lm2_r4i8_add(lm2_r4i8 a, lm2_r4i8 b);
LM2_API lm2_r4i8 lm2_r4i8_add_scalar(lm2_r4i8 r, int8_t s);
LM2_API lm2_r4i8 lm2_r4i8_add_vec(lm2_r4i8 r, lm2_v4i8 v);
LM2_API lm2_r4i8 lm2_r4i8_sub(lm2_r4i8 a, lm2_r4i8 b);
LM2_API lm2_r4i8 lm2_r4i8_sub_scalar(lm2_r4i8 r, int8_t s);
LM2_API lm2_r4i8 lm2_r4i8_sub_vec(lm2_r4i8 r, lm2_v4i8 v);
LM2_API lm2_r4i8 lm2_r4i8_mul(lm2_r4i8 a, lm2_r4i8 b);
LM2_API lm2_r4i8 lm2_r4i8_mul_scalar(lm2_r4i8 r, int8_t s);
LM2_API lm2_r4i8 lm2_r4i8_mul_vec(lm2_r4i8 r, lm2_v4i8 v);
LM2_API lm2_r4i8 lm2_r4i8_div(lm2_r4i8 a, lm2_r4i8 b);
LM2_API lm2_r4i8 lm2_r4i8_div_scalar(lm2_r4i8 r, int8_t s);
LM2_API lm2_r4i8 lm2_r4i8_div_vec(lm2_r4i8 r, lm2_v4i8 v);
LM2_API lm2_r4i8 lm2_r4i8_mod(lm2_r4i8 a, lm2_r4i8 b);
LM2_API lm2_r4i8 lm2_r4i8_mod_scalar(lm2_r4i8 r, int8_t s);
LM2_API lm2_r4i8 lm2_r4i8_mod_vec(lm2_r4i8 r, lm2_v4i8 v);

// Scalar function forwards
LM2_API lm2_r4i8 lm2_floor_lm2_r4i8(lm2_r4i8 a);
LM2_API lm2_r4i8 lm2_ceil_lm2_r4i8(lm2_r4i8 a);
LM2_API lm2_r4i8 lm2_round_lm2_r4i8(lm2_r4i8 a);
LM2_API lm2_r4i8 lm2_trunc_lm2_r4i8(lm2_r4i8 a);
LM2_API lm2_r4i8 lm2_abs_lm2_r4i8(lm2_r4i8 a);
LM2_API lm2_r4i8 lm2_floor_multiple_lm2_r4i8(lm2_r4i8 a, lm2_r4i8 b);
LM2_API lm2_r4i8 lm2_ceil_multiple_lm2_r4i8(lm2_r4i8 a, lm2_r4i8 b);
LM2_API lm2_r4i8 lm2_round_multiple_lm2_r4i8(lm2_r4i8 a, lm2_r4i8 b);
LM2_API lm2_r4i8 lm2_trunc_multiple_lm2_r4i8(lm2_r4i8 a, lm2_r4i8 b);
LM2_API lm2_r4i8 lm2_min_lm2_r4i8(lm2_r4i8 a, lm2_r4i8 b);
LM2_API lm2_r4i8 lm2_max_lm2_r4i8(lm2_r4i8 a, lm2_r4i8 b);
LM2_API lm2_r4i8 lm2_clamp_lm2_r4i8(lm2_r4i8 a, lm2_r4i8 b, lm2_r4i8 c);
LM2_API lm2_r4i8 lm2_lerp_lm2_r4i8(lm2_r4i8 a, lm2_r4i8 b, lm2_r4i8 c);

// Queries
LM2_API lm2_r4i8 lm2_r4i8_union(lm2_r4i8 a, lm2_r4i8 b);
LM2_API lm2_r4i8 lm2_r4i8_intersection(lm2_r4i8 a, lm2_r4i8 b);
LM2_API lm2_v4i8 lm2_r4i8_size(lm2_r4i8 r);
LM2_API lm2_v4i8 lm2_r4i8_extents(lm2_r4i8 r);
LM2_API lm2_v4i8 lm2_r4i8_center(lm2_r4i8 r);
LM2_API int lm2_r4i8_contains_point(lm2_r4i8 r, lm2_v4i8 point);
LM2_API int lm2_r4i8_overlaps(lm2_r4i8 a, lm2_r4i8 b);
LM2_API int8_t lm2_r4i8_hypervolume(lm2_r4i8 r);

// ---------------------------------------------------------------------------
// lm2_r4u64 - 4D Range (64-bit unsigned integer)
// ---------------------------------------------------------------------------
typedef union lm2_r4u64 {
  lm2_v4u64 e[2];
  struct {
    lm2_v4u64 min;
    lm2_v4u64 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v4u64)
} lm2_r4u64;

// Constructors
LM2_API lm2_r4u64 lm2_r4u64_from_min_max(lm2_v4u64 min, lm2_v4u64 max);
LM2_API lm2_r4u64 lm2_r4u64_from_center_extents(lm2_v4u64 center, lm2_v4u64 extents);
LM2_API lm2_r4u64 lm2_r4u64_from_center_size(lm2_v4u64 center, lm2_v4u64 size);
LM2_API lm2_r4u64 lm2_r4u64_from_position_size(lm2_v4u64 position, lm2_v4u64 size);
LM2_API lm2_r4u64 lm2_r4u64_zero(void);

// Operations
LM2_API lm2_r4u64 lm2_r4u64_normalize(lm2_r4u64 r);
LM2_API lm2_r4u64 lm2_r4u64_translate(lm2_r4u64 r, lm2_v4u64 offset);
LM2_API lm2_r4u64 lm2_r4u64_scale(lm2_r4u64 r, uint64_t factor);
LM2_API lm2_r4u64 lm2_r4u64_expand(lm2_r4u64 r, uint64_t amount);

// Arithmetic operators
LM2_API lm2_r4u64 lm2_r4u64_add(lm2_r4u64 a, lm2_r4u64 b);
LM2_API lm2_r4u64 lm2_r4u64_add_scalar(lm2_r4u64 r, uint64_t s);
LM2_API lm2_r4u64 lm2_r4u64_add_vec(lm2_r4u64 r, lm2_v4u64 v);
LM2_API lm2_r4u64 lm2_r4u64_sub(lm2_r4u64 a, lm2_r4u64 b);
LM2_API lm2_r4u64 lm2_r4u64_sub_scalar(lm2_r4u64 r, uint64_t s);
LM2_API lm2_r4u64 lm2_r4u64_sub_vec(lm2_r4u64 r, lm2_v4u64 v);
LM2_API lm2_r4u64 lm2_r4u64_mul(lm2_r4u64 a, lm2_r4u64 b);
LM2_API lm2_r4u64 lm2_r4u64_mul_scalar(lm2_r4u64 r, uint64_t s);
LM2_API lm2_r4u64 lm2_r4u64_mul_vec(lm2_r4u64 r, lm2_v4u64 v);
LM2_API lm2_r4u64 lm2_r4u64_div(lm2_r4u64 a, lm2_r4u64 b);
LM2_API lm2_r4u64 lm2_r4u64_div_scalar(lm2_r4u64 r, uint64_t s);
LM2_API lm2_r4u64 lm2_r4u64_div_vec(lm2_r4u64 r, lm2_v4u64 v);
LM2_API lm2_r4u64 lm2_r4u64_mod(lm2_r4u64 a, lm2_r4u64 b);
LM2_API lm2_r4u64 lm2_r4u64_mod_scalar(lm2_r4u64 r, uint64_t s);
LM2_API lm2_r4u64 lm2_r4u64_mod_vec(lm2_r4u64 r, lm2_v4u64 v);

// Scalar function forwards
LM2_API lm2_r4u64 lm2_floor_lm2_r4u64(lm2_r4u64 a);
LM2_API lm2_r4u64 lm2_ceil_lm2_r4u64(lm2_r4u64 a);
LM2_API lm2_r4u64 lm2_round_lm2_r4u64(lm2_r4u64 a);
LM2_API lm2_r4u64 lm2_trunc_lm2_r4u64(lm2_r4u64 a);
LM2_API lm2_r4u64 lm2_abs_lm2_r4u64(lm2_r4u64 a);
LM2_API lm2_r4u64 lm2_floor_multiple_lm2_r4u64(lm2_r4u64 a, lm2_r4u64 b);
LM2_API lm2_r4u64 lm2_ceil_multiple_lm2_r4u64(lm2_r4u64 a, lm2_r4u64 b);
LM2_API lm2_r4u64 lm2_round_multiple_lm2_r4u64(lm2_r4u64 a, lm2_r4u64 b);
LM2_API lm2_r4u64 lm2_trunc_multiple_lm2_r4u64(lm2_r4u64 a, lm2_r4u64 b);
LM2_API lm2_r4u64 lm2_min_lm2_r4u64(lm2_r4u64 a, lm2_r4u64 b);
LM2_API lm2_r4u64 lm2_max_lm2_r4u64(lm2_r4u64 a, lm2_r4u64 b);
LM2_API lm2_r4u64 lm2_clamp_lm2_r4u64(lm2_r4u64 a, lm2_r4u64 b, lm2_r4u64 c);
LM2_API lm2_r4u64 lm2_lerp_lm2_r4u64(lm2_r4u64 a, lm2_r4u64 b, lm2_r4u64 c);

// Queries
LM2_API lm2_r4u64 lm2_r4u64_union(lm2_r4u64 a, lm2_r4u64 b);
LM2_API lm2_r4u64 lm2_r4u64_intersection(lm2_r4u64 a, lm2_r4u64 b);
LM2_API lm2_v4u64 lm2_r4u64_size(lm2_r4u64 r);
LM2_API lm2_v4u64 lm2_r4u64_extents(lm2_r4u64 r);
LM2_API lm2_v4u64 lm2_r4u64_center(lm2_r4u64 r);
LM2_API int lm2_r4u64_contains_point(lm2_r4u64 r, lm2_v4u64 point);
LM2_API int lm2_r4u64_overlaps(lm2_r4u64 a, lm2_r4u64 b);
LM2_API uint64_t lm2_r4u64_hypervolume(lm2_r4u64 r);

// ---------------------------------------------------------------------------
// lm2_r4u32 - 4D Range (32-bit unsigned integer)
// ---------------------------------------------------------------------------
typedef union lm2_r4u32 {
  lm2_v4u32 e[2];
  struct {
    lm2_v4u32 min;
    lm2_v4u32 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v4u32)
} lm2_r4u32;

// Constructors
LM2_API lm2_r4u32 lm2_r4u32_from_min_max(lm2_v4u32 min, lm2_v4u32 max);
LM2_API lm2_r4u32 lm2_r4u32_from_center_extents(lm2_v4u32 center, lm2_v4u32 extents);
LM2_API lm2_r4u32 lm2_r4u32_from_center_size(lm2_v4u32 center, lm2_v4u32 size);
LM2_API lm2_r4u32 lm2_r4u32_from_position_size(lm2_v4u32 position, lm2_v4u32 size);
LM2_API lm2_r4u32 lm2_r4u32_zero(void);

// Operations
LM2_API lm2_r4u32 lm2_r4u32_normalize(lm2_r4u32 r);
LM2_API lm2_r4u32 lm2_r4u32_translate(lm2_r4u32 r, lm2_v4u32 offset);
LM2_API lm2_r4u32 lm2_r4u32_scale(lm2_r4u32 r, uint32_t factor);
LM2_API lm2_r4u32 lm2_r4u32_expand(lm2_r4u32 r, uint32_t amount);

// Arithmetic operators
LM2_API lm2_r4u32 lm2_r4u32_add(lm2_r4u32 a, lm2_r4u32 b);
LM2_API lm2_r4u32 lm2_r4u32_add_scalar(lm2_r4u32 r, uint32_t s);
LM2_API lm2_r4u32 lm2_r4u32_add_vec(lm2_r4u32 r, lm2_v4u32 v);
LM2_API lm2_r4u32 lm2_r4u32_sub(lm2_r4u32 a, lm2_r4u32 b);
LM2_API lm2_r4u32 lm2_r4u32_sub_scalar(lm2_r4u32 r, uint32_t s);
LM2_API lm2_r4u32 lm2_r4u32_sub_vec(lm2_r4u32 r, lm2_v4u32 v);
LM2_API lm2_r4u32 lm2_r4u32_mul(lm2_r4u32 a, lm2_r4u32 b);
LM2_API lm2_r4u32 lm2_r4u32_mul_scalar(lm2_r4u32 r, uint32_t s);
LM2_API lm2_r4u32 lm2_r4u32_mul_vec(lm2_r4u32 r, lm2_v4u32 v);
LM2_API lm2_r4u32 lm2_r4u32_div(lm2_r4u32 a, lm2_r4u32 b);
LM2_API lm2_r4u32 lm2_r4u32_div_scalar(lm2_r4u32 r, uint32_t s);
LM2_API lm2_r4u32 lm2_r4u32_div_vec(lm2_r4u32 r, lm2_v4u32 v);
LM2_API lm2_r4u32 lm2_r4u32_mod(lm2_r4u32 a, lm2_r4u32 b);
LM2_API lm2_r4u32 lm2_r4u32_mod_scalar(lm2_r4u32 r, uint32_t s);
LM2_API lm2_r4u32 lm2_r4u32_mod_vec(lm2_r4u32 r, lm2_v4u32 v);

// Scalar function forwards
LM2_API lm2_r4u32 lm2_floor_lm2_r4u32(lm2_r4u32 a);
LM2_API lm2_r4u32 lm2_ceil_lm2_r4u32(lm2_r4u32 a);
LM2_API lm2_r4u32 lm2_round_lm2_r4u32(lm2_r4u32 a);
LM2_API lm2_r4u32 lm2_trunc_lm2_r4u32(lm2_r4u32 a);
LM2_API lm2_r4u32 lm2_abs_lm2_r4u32(lm2_r4u32 a);
LM2_API lm2_r4u32 lm2_floor_multiple_lm2_r4u32(lm2_r4u32 a, lm2_r4u32 b);
LM2_API lm2_r4u32 lm2_ceil_multiple_lm2_r4u32(lm2_r4u32 a, lm2_r4u32 b);
LM2_API lm2_r4u32 lm2_round_multiple_lm2_r4u32(lm2_r4u32 a, lm2_r4u32 b);
LM2_API lm2_r4u32 lm2_trunc_multiple_lm2_r4u32(lm2_r4u32 a, lm2_r4u32 b);
LM2_API lm2_r4u32 lm2_min_lm2_r4u32(lm2_r4u32 a, lm2_r4u32 b);
LM2_API lm2_r4u32 lm2_max_lm2_r4u32(lm2_r4u32 a, lm2_r4u32 b);
LM2_API lm2_r4u32 lm2_clamp_lm2_r4u32(lm2_r4u32 a, lm2_r4u32 b, lm2_r4u32 c);
LM2_API lm2_r4u32 lm2_lerp_lm2_r4u32(lm2_r4u32 a, lm2_r4u32 b, lm2_r4u32 c);

// Queries
LM2_API lm2_r4u32 lm2_r4u32_union(lm2_r4u32 a, lm2_r4u32 b);
LM2_API lm2_r4u32 lm2_r4u32_intersection(lm2_r4u32 a, lm2_r4u32 b);
LM2_API lm2_v4u32 lm2_r4u32_size(lm2_r4u32 r);
LM2_API lm2_v4u32 lm2_r4u32_extents(lm2_r4u32 r);
LM2_API lm2_v4u32 lm2_r4u32_center(lm2_r4u32 r);
LM2_API int lm2_r4u32_contains_point(lm2_r4u32 r, lm2_v4u32 point);
LM2_API int lm2_r4u32_overlaps(lm2_r4u32 a, lm2_r4u32 b);
LM2_API uint32_t lm2_r4u32_hypervolume(lm2_r4u32 r);

// ---------------------------------------------------------------------------
// lm2_r4u16 - 4D Range (16-bit unsigned integer)
// ---------------------------------------------------------------------------
typedef union lm2_r4u16 {
  lm2_v4u16 e[2];
  struct {
    lm2_v4u16 min;
    lm2_v4u16 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v4u16)
} lm2_r4u16;

// Constructors
LM2_API lm2_r4u16 lm2_r4u16_from_min_max(lm2_v4u16 min, lm2_v4u16 max);
LM2_API lm2_r4u16 lm2_r4u16_from_center_extents(lm2_v4u16 center, lm2_v4u16 extents);
LM2_API lm2_r4u16 lm2_r4u16_from_center_size(lm2_v4u16 center, lm2_v4u16 size);
LM2_API lm2_r4u16 lm2_r4u16_from_position_size(lm2_v4u16 position, lm2_v4u16 size);
LM2_API lm2_r4u16 lm2_r4u16_zero(void);

// Operations
LM2_API lm2_r4u16 lm2_r4u16_normalize(lm2_r4u16 r);
LM2_API lm2_r4u16 lm2_r4u16_translate(lm2_r4u16 r, lm2_v4u16 offset);
LM2_API lm2_r4u16 lm2_r4u16_scale(lm2_r4u16 r, uint16_t factor);
LM2_API lm2_r4u16 lm2_r4u16_expand(lm2_r4u16 r, uint16_t amount);

// Arithmetic operators
LM2_API lm2_r4u16 lm2_r4u16_add(lm2_r4u16 a, lm2_r4u16 b);
LM2_API lm2_r4u16 lm2_r4u16_add_scalar(lm2_r4u16 r, uint16_t s);
LM2_API lm2_r4u16 lm2_r4u16_add_vec(lm2_r4u16 r, lm2_v4u16 v);
LM2_API lm2_r4u16 lm2_r4u16_sub(lm2_r4u16 a, lm2_r4u16 b);
LM2_API lm2_r4u16 lm2_r4u16_sub_scalar(lm2_r4u16 r, uint16_t s);
LM2_API lm2_r4u16 lm2_r4u16_sub_vec(lm2_r4u16 r, lm2_v4u16 v);
LM2_API lm2_r4u16 lm2_r4u16_mul(lm2_r4u16 a, lm2_r4u16 b);
LM2_API lm2_r4u16 lm2_r4u16_mul_scalar(lm2_r4u16 r, uint16_t s);
LM2_API lm2_r4u16 lm2_r4u16_mul_vec(lm2_r4u16 r, lm2_v4u16 v);
LM2_API lm2_r4u16 lm2_r4u16_div(lm2_r4u16 a, lm2_r4u16 b);
LM2_API lm2_r4u16 lm2_r4u16_div_scalar(lm2_r4u16 r, uint16_t s);
LM2_API lm2_r4u16 lm2_r4u16_div_vec(lm2_r4u16 r, lm2_v4u16 v);
LM2_API lm2_r4u16 lm2_r4u16_mod(lm2_r4u16 a, lm2_r4u16 b);
LM2_API lm2_r4u16 lm2_r4u16_mod_scalar(lm2_r4u16 r, uint16_t s);
LM2_API lm2_r4u16 lm2_r4u16_mod_vec(lm2_r4u16 r, lm2_v4u16 v);

// Scalar function forwards
LM2_API lm2_r4u16 lm2_floor_lm2_r4u16(lm2_r4u16 a);
LM2_API lm2_r4u16 lm2_ceil_lm2_r4u16(lm2_r4u16 a);
LM2_API lm2_r4u16 lm2_round_lm2_r4u16(lm2_r4u16 a);
LM2_API lm2_r4u16 lm2_trunc_lm2_r4u16(lm2_r4u16 a);
LM2_API lm2_r4u16 lm2_abs_lm2_r4u16(lm2_r4u16 a);
LM2_API lm2_r4u16 lm2_floor_multiple_lm2_r4u16(lm2_r4u16 a, lm2_r4u16 b);
LM2_API lm2_r4u16 lm2_ceil_multiple_lm2_r4u16(lm2_r4u16 a, lm2_r4u16 b);
LM2_API lm2_r4u16 lm2_round_multiple_lm2_r4u16(lm2_r4u16 a, lm2_r4u16 b);
LM2_API lm2_r4u16 lm2_trunc_multiple_lm2_r4u16(lm2_r4u16 a, lm2_r4u16 b);
LM2_API lm2_r4u16 lm2_min_lm2_r4u16(lm2_r4u16 a, lm2_r4u16 b);
LM2_API lm2_r4u16 lm2_max_lm2_r4u16(lm2_r4u16 a, lm2_r4u16 b);
LM2_API lm2_r4u16 lm2_clamp_lm2_r4u16(lm2_r4u16 a, lm2_r4u16 b, lm2_r4u16 c);
LM2_API lm2_r4u16 lm2_lerp_lm2_r4u16(lm2_r4u16 a, lm2_r4u16 b, lm2_r4u16 c);

// Queries
LM2_API lm2_r4u16 lm2_r4u16_union(lm2_r4u16 a, lm2_r4u16 b);
LM2_API lm2_r4u16 lm2_r4u16_intersection(lm2_r4u16 a, lm2_r4u16 b);
LM2_API lm2_v4u16 lm2_r4u16_size(lm2_r4u16 r);
LM2_API lm2_v4u16 lm2_r4u16_extents(lm2_r4u16 r);
LM2_API lm2_v4u16 lm2_r4u16_center(lm2_r4u16 r);
LM2_API int lm2_r4u16_contains_point(lm2_r4u16 r, lm2_v4u16 point);
LM2_API int lm2_r4u16_overlaps(lm2_r4u16 a, lm2_r4u16 b);
LM2_API uint16_t lm2_r4u16_hypervolume(lm2_r4u16 r);

// ---------------------------------------------------------------------------
// lm2_r4u8 - 4D Range (8-bit unsigned integer)
// ---------------------------------------------------------------------------
typedef union lm2_r4u8 {
  lm2_v4u8 e[2];
  struct {
    lm2_v4u8 min;
    lm2_v4u8 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v4u8)
} lm2_r4u8;

// Constructors
LM2_API lm2_r4u8 lm2_r4u8_from_min_max(lm2_v4u8 min, lm2_v4u8 max);
LM2_API lm2_r4u8 lm2_r4u8_from_center_extents(lm2_v4u8 center, lm2_v4u8 extents);
LM2_API lm2_r4u8 lm2_r4u8_from_center_size(lm2_v4u8 center, lm2_v4u8 size);
LM2_API lm2_r4u8 lm2_r4u8_from_position_size(lm2_v4u8 position, lm2_v4u8 size);
LM2_API lm2_r4u8 lm2_r4u8_zero(void);

// Operations
LM2_API lm2_r4u8 lm2_r4u8_normalize(lm2_r4u8 r);
LM2_API lm2_r4u8 lm2_r4u8_translate(lm2_r4u8 r, lm2_v4u8 offset);
LM2_API lm2_r4u8 lm2_r4u8_scale(lm2_r4u8 r, uint8_t factor);
LM2_API lm2_r4u8 lm2_r4u8_expand(lm2_r4u8 r, uint8_t amount);

// Arithmetic operators
LM2_API lm2_r4u8 lm2_r4u8_add(lm2_r4u8 a, lm2_r4u8 b);
LM2_API lm2_r4u8 lm2_r4u8_add_scalar(lm2_r4u8 r, uint8_t s);
LM2_API lm2_r4u8 lm2_r4u8_add_vec(lm2_r4u8 r, lm2_v4u8 v);
LM2_API lm2_r4u8 lm2_r4u8_sub(lm2_r4u8 a, lm2_r4u8 b);
LM2_API lm2_r4u8 lm2_r4u8_sub_scalar(lm2_r4u8 r, uint8_t s);
LM2_API lm2_r4u8 lm2_r4u8_sub_vec(lm2_r4u8 r, lm2_v4u8 v);
LM2_API lm2_r4u8 lm2_r4u8_mul(lm2_r4u8 a, lm2_r4u8 b);
LM2_API lm2_r4u8 lm2_r4u8_mul_scalar(lm2_r4u8 r, uint8_t s);
LM2_API lm2_r4u8 lm2_r4u8_mul_vec(lm2_r4u8 r, lm2_v4u8 v);
LM2_API lm2_r4u8 lm2_r4u8_div(lm2_r4u8 a, lm2_r4u8 b);
LM2_API lm2_r4u8 lm2_r4u8_div_scalar(lm2_r4u8 r, uint8_t s);
LM2_API lm2_r4u8 lm2_r4u8_div_vec(lm2_r4u8 r, lm2_v4u8 v);
LM2_API lm2_r4u8 lm2_r4u8_mod(lm2_r4u8 a, lm2_r4u8 b);
LM2_API lm2_r4u8 lm2_r4u8_mod_scalar(lm2_r4u8 r, uint8_t s);
LM2_API lm2_r4u8 lm2_r4u8_mod_vec(lm2_r4u8 r, lm2_v4u8 v);

// Scalar function forwards
LM2_API lm2_r4u8 lm2_floor_lm2_r4u8(lm2_r4u8 a);
LM2_API lm2_r4u8 lm2_ceil_lm2_r4u8(lm2_r4u8 a);
LM2_API lm2_r4u8 lm2_round_lm2_r4u8(lm2_r4u8 a);
LM2_API lm2_r4u8 lm2_trunc_lm2_r4u8(lm2_r4u8 a);
LM2_API lm2_r4u8 lm2_abs_lm2_r4u8(lm2_r4u8 a);
LM2_API lm2_r4u8 lm2_floor_multiple_lm2_r4u8(lm2_r4u8 a, lm2_r4u8 b);
LM2_API lm2_r4u8 lm2_ceil_multiple_lm2_r4u8(lm2_r4u8 a, lm2_r4u8 b);
LM2_API lm2_r4u8 lm2_round_multiple_lm2_r4u8(lm2_r4u8 a, lm2_r4u8 b);
LM2_API lm2_r4u8 lm2_trunc_multiple_lm2_r4u8(lm2_r4u8 a, lm2_r4u8 b);
LM2_API lm2_r4u8 lm2_min_lm2_r4u8(lm2_r4u8 a, lm2_r4u8 b);
LM2_API lm2_r4u8 lm2_max_lm2_r4u8(lm2_r4u8 a, lm2_r4u8 b);
LM2_API lm2_r4u8 lm2_clamp_lm2_r4u8(lm2_r4u8 a, lm2_r4u8 b, lm2_r4u8 c);
LM2_API lm2_r4u8 lm2_lerp_lm2_r4u8(lm2_r4u8 a, lm2_r4u8 b, lm2_r4u8 c);

// Queries
LM2_API lm2_r4u8 lm2_r4u8_union(lm2_r4u8 a, lm2_r4u8 b);
LM2_API lm2_r4u8 lm2_r4u8_intersection(lm2_r4u8 a, lm2_r4u8 b);
LM2_API lm2_v4u8 lm2_r4u8_size(lm2_r4u8 r);
LM2_API lm2_v4u8 lm2_r4u8_extents(lm2_r4u8 r);
LM2_API lm2_v4u8 lm2_r4u8_center(lm2_r4u8 r);
LM2_API int lm2_r4u8_contains_point(lm2_r4u8 r, lm2_v4u8 point);
LM2_API int lm2_r4u8_overlaps(lm2_r4u8 a, lm2_r4u8 b);
LM2_API uint8_t lm2_r4u8_hypervolume(lm2_r4u8 r);

// Default range4 type (float-based)
typedef lm2_r4f32 lm2_r4;

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// C++ operator overloads and constructors (must be outside extern "C")
#ifndef LM2_NO_CPP_OPERATORS
#  include "lm2_range_operators.h"
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4f64, lm2_v4f64)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4f32, lm2_v4f32)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4i64, lm2_v4i64)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4i32, lm2_v4i32)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4i16, lm2_v4i16)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4i8, lm2_v4i8)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4u64, lm2_v4u64)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4u32, lm2_v4u32)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4u16, lm2_v4u16)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4u8, lm2_v4u8)
#endif
