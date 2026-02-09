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
#include "lm2/vectors/lm2_vector3.h"
#include "lm2_range_defines.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// 3D Range (AABB) Type Definitions
// =============================================================================
// A range3 represents a 3D axis-aligned bounding box (AABB) or cube/box
// with minimum and maximum points.

// ---------------------------------------------------------------------------
// lm2_r3f64 - 3D Range (double precision)
// ---------------------------------------------------------------------------
typedef union lm2_r3f64 {
  lm2_v3f64 e[2];
  struct {
    lm2_v3f64 min;
    lm2_v3f64 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v3f64)
} lm2_r3f64;

// Constructors
LM2_API lm2_r3f64 lm2_r3f64_from_min_max(lm2_v3f64 min, lm2_v3f64 max);
LM2_API lm2_r3f64 lm2_r3f64_from_center_extents(lm2_v3f64 center, lm2_v3f64 extents);
LM2_API lm2_r3f64 lm2_r3f64_from_center_size(lm2_v3f64 center, lm2_v3f64 size);
LM2_API lm2_r3f64 lm2_r3f64_from_position_size(lm2_v3f64 position, lm2_v3f64 size);
LM2_API lm2_r3f64 lm2_r3f64_zero(void);

// Operations
LM2_API lm2_r3f64 lm2_r3f64_normalize(lm2_r3f64 r);
LM2_API lm2_r3f64 lm2_r3f64_translate(lm2_r3f64 r, lm2_v3f64 offset);
LM2_API lm2_r3f64 lm2_r3f64_scale(lm2_r3f64 r, double factor);
LM2_API lm2_r3f64 lm2_r3f64_expand(lm2_r3f64 r, double amount);

// Arithmetic operators
LM2_API lm2_r3f64 lm2_r3f64_add(lm2_r3f64 a, lm2_r3f64 b);
LM2_API lm2_r3f64 lm2_r3f64_add_scalar(lm2_r3f64 r, double s);
LM2_API lm2_r3f64 lm2_r3f64_add_vec(lm2_r3f64 r, lm2_v3f64 v);
LM2_API lm2_r3f64 lm2_r3f64_sub(lm2_r3f64 a, lm2_r3f64 b);
LM2_API lm2_r3f64 lm2_r3f64_sub_scalar(lm2_r3f64 r, double s);
LM2_API lm2_r3f64 lm2_r3f64_sub_vec(lm2_r3f64 r, lm2_v3f64 v);
LM2_API lm2_r3f64 lm2_r3f64_mul(lm2_r3f64 a, lm2_r3f64 b);
LM2_API lm2_r3f64 lm2_r3f64_mul_scalar(lm2_r3f64 r, double s);
LM2_API lm2_r3f64 lm2_r3f64_mul_vec(lm2_r3f64 r, lm2_v3f64 v);
LM2_API lm2_r3f64 lm2_r3f64_div(lm2_r3f64 a, lm2_r3f64 b);
LM2_API lm2_r3f64 lm2_r3f64_div_scalar(lm2_r3f64 r, double s);
LM2_API lm2_r3f64 lm2_r3f64_div_vec(lm2_r3f64 r, lm2_v3f64 v);
LM2_API lm2_r3f64 lm2_r3f64_mod(lm2_r3f64 a, lm2_r3f64 b);
LM2_API lm2_r3f64 lm2_r3f64_mod_scalar(lm2_r3f64 r, double s);
LM2_API lm2_r3f64 lm2_r3f64_mod_vec(lm2_r3f64 r, lm2_v3f64 v);

// Scalar function forwards
LM2_API lm2_r3f64 lm2_floor_lm2_r3f64(lm2_r3f64 a);
LM2_API lm2_r3f64 lm2_ceil_lm2_r3f64(lm2_r3f64 a);
LM2_API lm2_r3f64 lm2_round_lm2_r3f64(lm2_r3f64 a);
LM2_API lm2_r3f64 lm2_trunc_lm2_r3f64(lm2_r3f64 a);
LM2_API lm2_r3f64 lm2_abs_lm2_r3f64(lm2_r3f64 a);
LM2_API lm2_r3f64 lm2_floor_multiple_lm2_r3f64(lm2_r3f64 a, lm2_r3f64 b);
LM2_API lm2_r3f64 lm2_ceil_multiple_lm2_r3f64(lm2_r3f64 a, lm2_r3f64 b);
LM2_API lm2_r3f64 lm2_round_multiple_lm2_r3f64(lm2_r3f64 a, lm2_r3f64 b);
LM2_API lm2_r3f64 lm2_trunc_multiple_lm2_r3f64(lm2_r3f64 a, lm2_r3f64 b);
LM2_API lm2_r3f64 lm2_min_lm2_r3f64(lm2_r3f64 a, lm2_r3f64 b);
LM2_API lm2_r3f64 lm2_max_lm2_r3f64(lm2_r3f64 a, lm2_r3f64 b);
LM2_API lm2_r3f64 lm2_clamp_lm2_r3f64(lm2_r3f64 a, lm2_r3f64 b, lm2_r3f64 c);
LM2_API lm2_r3f64 lm2_lerp_lm2_r3f64(lm2_r3f64 a, lm2_r3f64 b, lm2_r3f64 c);

// Queries
LM2_API lm2_r3f64 lm2_r3f64_union(lm2_r3f64 a, lm2_r3f64 b);
LM2_API lm2_r3f64 lm2_r3f64_intersection(lm2_r3f64 a, lm2_r3f64 b);
LM2_API lm2_v3f64 lm2_r3f64_size(lm2_r3f64 r);
LM2_API lm2_v3f64 lm2_r3f64_extents(lm2_r3f64 r);
LM2_API lm2_v3f64 lm2_r3f64_center(lm2_r3f64 r);
LM2_API int lm2_r3f64_contains_point(lm2_r3f64 r, lm2_v3f64 point);
LM2_API int lm2_r3f64_overlaps(lm2_r3f64 a, lm2_r3f64 b);
LM2_API double lm2_r3f64_volume(lm2_r3f64 r);

// ---------------------------------------------------------------------------
// lm2_r3f32 - 3D Range (single precision)
// ---------------------------------------------------------------------------
typedef union lm2_r3f32 {
  lm2_v3f32 e[2];
  struct {
    lm2_v3f32 min;
    lm2_v3f32 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v3f32)
} lm2_r3f32;

// Constructors
LM2_API lm2_r3f32 lm2_r3f32_from_min_max(lm2_v3f32 min, lm2_v3f32 max);
LM2_API lm2_r3f32 lm2_r3f32_from_center_extents(lm2_v3f32 center, lm2_v3f32 extents);
LM2_API lm2_r3f32 lm2_r3f32_from_center_size(lm2_v3f32 center, lm2_v3f32 size);
LM2_API lm2_r3f32 lm2_r3f32_from_position_size(lm2_v3f32 position, lm2_v3f32 size);
LM2_API lm2_r3f32 lm2_r3f32_zero(void);

// Operations
LM2_API lm2_r3f32 lm2_r3f32_normalize(lm2_r3f32 r);
LM2_API lm2_r3f32 lm2_r3f32_translate(lm2_r3f32 r, lm2_v3f32 offset);
LM2_API lm2_r3f32 lm2_r3f32_scale(lm2_r3f32 r, float factor);
LM2_API lm2_r3f32 lm2_r3f32_expand(lm2_r3f32 r, float amount);

// Arithmetic operators
LM2_API lm2_r3f32 lm2_r3f32_add(lm2_r3f32 a, lm2_r3f32 b);
LM2_API lm2_r3f32 lm2_r3f32_add_scalar(lm2_r3f32 r, float s);
LM2_API lm2_r3f32 lm2_r3f32_add_vec(lm2_r3f32 r, lm2_v3f32 v);
LM2_API lm2_r3f32 lm2_r3f32_sub(lm2_r3f32 a, lm2_r3f32 b);
LM2_API lm2_r3f32 lm2_r3f32_sub_scalar(lm2_r3f32 r, float s);
LM2_API lm2_r3f32 lm2_r3f32_sub_vec(lm2_r3f32 r, lm2_v3f32 v);
LM2_API lm2_r3f32 lm2_r3f32_mul(lm2_r3f32 a, lm2_r3f32 b);
LM2_API lm2_r3f32 lm2_r3f32_mul_scalar(lm2_r3f32 r, float s);
LM2_API lm2_r3f32 lm2_r3f32_mul_vec(lm2_r3f32 r, lm2_v3f32 v);
LM2_API lm2_r3f32 lm2_r3f32_div(lm2_r3f32 a, lm2_r3f32 b);
LM2_API lm2_r3f32 lm2_r3f32_div_scalar(lm2_r3f32 r, float s);
LM2_API lm2_r3f32 lm2_r3f32_div_vec(lm2_r3f32 r, lm2_v3f32 v);
LM2_API lm2_r3f32 lm2_r3f32_mod(lm2_r3f32 a, lm2_r3f32 b);
LM2_API lm2_r3f32 lm2_r3f32_mod_scalar(lm2_r3f32 r, float s);
LM2_API lm2_r3f32 lm2_r3f32_mod_vec(lm2_r3f32 r, lm2_v3f32 v);

// Scalar function forwards
LM2_API lm2_r3f32 lm2_floor_lm2_r3f32(lm2_r3f32 a);
LM2_API lm2_r3f32 lm2_ceil_lm2_r3f32(lm2_r3f32 a);
LM2_API lm2_r3f32 lm2_round_lm2_r3f32(lm2_r3f32 a);
LM2_API lm2_r3f32 lm2_trunc_lm2_r3f32(lm2_r3f32 a);
LM2_API lm2_r3f32 lm2_abs_lm2_r3f32(lm2_r3f32 a);
LM2_API lm2_r3f32 lm2_floor_multiple_lm2_r3f32(lm2_r3f32 a, lm2_r3f32 b);
LM2_API lm2_r3f32 lm2_ceil_multiple_lm2_r3f32(lm2_r3f32 a, lm2_r3f32 b);
LM2_API lm2_r3f32 lm2_round_multiple_lm2_r3f32(lm2_r3f32 a, lm2_r3f32 b);
LM2_API lm2_r3f32 lm2_trunc_multiple_lm2_r3f32(lm2_r3f32 a, lm2_r3f32 b);
LM2_API lm2_r3f32 lm2_min_lm2_r3f32(lm2_r3f32 a, lm2_r3f32 b);
LM2_API lm2_r3f32 lm2_max_lm2_r3f32(lm2_r3f32 a, lm2_r3f32 b);
LM2_API lm2_r3f32 lm2_clamp_lm2_r3f32(lm2_r3f32 a, lm2_r3f32 b, lm2_r3f32 c);
LM2_API lm2_r3f32 lm2_lerp_lm2_r3f32(lm2_r3f32 a, lm2_r3f32 b, lm2_r3f32 c);

// Queries
LM2_API lm2_r3f32 lm2_r3f32_union(lm2_r3f32 a, lm2_r3f32 b);
LM2_API lm2_r3f32 lm2_r3f32_intersection(lm2_r3f32 a, lm2_r3f32 b);
LM2_API lm2_v3f32 lm2_r3f32_size(lm2_r3f32 r);
LM2_API lm2_v3f32 lm2_r3f32_extents(lm2_r3f32 r);
LM2_API lm2_v3f32 lm2_r3f32_center(lm2_r3f32 r);
LM2_API int lm2_r3f32_contains_point(lm2_r3f32 r, lm2_v3f32 point);
LM2_API int lm2_r3f32_overlaps(lm2_r3f32 a, lm2_r3f32 b);
LM2_API float lm2_r3f32_volume(lm2_r3f32 r);

// ---------------------------------------------------------------------------
// lm2_r3i64 - 3D Range (64-bit signed integer)
// ---------------------------------------------------------------------------
typedef union lm2_r3i64 {
  lm2_v3i64 e[2];
  struct {
    lm2_v3i64 min;
    lm2_v3i64 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v3i64)
} lm2_r3i64;

// Constructors
LM2_API lm2_r3i64 lm2_r3i64_from_min_max(lm2_v3i64 min, lm2_v3i64 max);
LM2_API lm2_r3i64 lm2_r3i64_from_center_extents(lm2_v3i64 center, lm2_v3i64 extents);
LM2_API lm2_r3i64 lm2_r3i64_from_center_size(lm2_v3i64 center, lm2_v3i64 size);
LM2_API lm2_r3i64 lm2_r3i64_from_position_size(lm2_v3i64 position, lm2_v3i64 size);
LM2_API lm2_r3i64 lm2_r3i64_zero(void);

// Operations
LM2_API lm2_r3i64 lm2_r3i64_normalize(lm2_r3i64 r);
LM2_API lm2_r3i64 lm2_r3i64_translate(lm2_r3i64 r, lm2_v3i64 offset);
LM2_API lm2_r3i64 lm2_r3i64_scale(lm2_r3i64 r, int64_t factor);
LM2_API lm2_r3i64 lm2_r3i64_expand(lm2_r3i64 r, int64_t amount);

// Arithmetic operators
LM2_API lm2_r3i64 lm2_r3i64_add(lm2_r3i64 a, lm2_r3i64 b);
LM2_API lm2_r3i64 lm2_r3i64_add_scalar(lm2_r3i64 r, int64_t s);
LM2_API lm2_r3i64 lm2_r3i64_add_vec(lm2_r3i64 r, lm2_v3i64 v);
LM2_API lm2_r3i64 lm2_r3i64_sub(lm2_r3i64 a, lm2_r3i64 b);
LM2_API lm2_r3i64 lm2_r3i64_sub_scalar(lm2_r3i64 r, int64_t s);
LM2_API lm2_r3i64 lm2_r3i64_sub_vec(lm2_r3i64 r, lm2_v3i64 v);
LM2_API lm2_r3i64 lm2_r3i64_mul(lm2_r3i64 a, lm2_r3i64 b);
LM2_API lm2_r3i64 lm2_r3i64_mul_scalar(lm2_r3i64 r, int64_t s);
LM2_API lm2_r3i64 lm2_r3i64_mul_vec(lm2_r3i64 r, lm2_v3i64 v);
LM2_API lm2_r3i64 lm2_r3i64_div(lm2_r3i64 a, lm2_r3i64 b);
LM2_API lm2_r3i64 lm2_r3i64_div_scalar(lm2_r3i64 r, int64_t s);
LM2_API lm2_r3i64 lm2_r3i64_div_vec(lm2_r3i64 r, lm2_v3i64 v);
LM2_API lm2_r3i64 lm2_r3i64_mod(lm2_r3i64 a, lm2_r3i64 b);
LM2_API lm2_r3i64 lm2_r3i64_mod_scalar(lm2_r3i64 r, int64_t s);
LM2_API lm2_r3i64 lm2_r3i64_mod_vec(lm2_r3i64 r, lm2_v3i64 v);

// Scalar function forwards
LM2_API lm2_r3i64 lm2_floor_lm2_r3i64(lm2_r3i64 a);
LM2_API lm2_r3i64 lm2_ceil_lm2_r3i64(lm2_r3i64 a);
LM2_API lm2_r3i64 lm2_round_lm2_r3i64(lm2_r3i64 a);
LM2_API lm2_r3i64 lm2_trunc_lm2_r3i64(lm2_r3i64 a);
LM2_API lm2_r3i64 lm2_abs_lm2_r3i64(lm2_r3i64 a);
LM2_API lm2_r3i64 lm2_floor_multiple_lm2_r3i64(lm2_r3i64 a, lm2_r3i64 b);
LM2_API lm2_r3i64 lm2_ceil_multiple_lm2_r3i64(lm2_r3i64 a, lm2_r3i64 b);
LM2_API lm2_r3i64 lm2_round_multiple_lm2_r3i64(lm2_r3i64 a, lm2_r3i64 b);
LM2_API lm2_r3i64 lm2_trunc_multiple_lm2_r3i64(lm2_r3i64 a, lm2_r3i64 b);
LM2_API lm2_r3i64 lm2_min_lm2_r3i64(lm2_r3i64 a, lm2_r3i64 b);
LM2_API lm2_r3i64 lm2_max_lm2_r3i64(lm2_r3i64 a, lm2_r3i64 b);
LM2_API lm2_r3i64 lm2_clamp_lm2_r3i64(lm2_r3i64 a, lm2_r3i64 b, lm2_r3i64 c);
LM2_API lm2_r3i64 lm2_lerp_lm2_r3i64(lm2_r3i64 a, lm2_r3i64 b, lm2_r3i64 c);

// Queries
LM2_API lm2_r3i64 lm2_r3i64_union(lm2_r3i64 a, lm2_r3i64 b);
LM2_API lm2_r3i64 lm2_r3i64_intersection(lm2_r3i64 a, lm2_r3i64 b);
LM2_API lm2_v3i64 lm2_r3i64_size(lm2_r3i64 r);
LM2_API lm2_v3i64 lm2_r3i64_extents(lm2_r3i64 r);
LM2_API lm2_v3i64 lm2_r3i64_center(lm2_r3i64 r);
LM2_API int lm2_r3i64_contains_point(lm2_r3i64 r, lm2_v3i64 point);
LM2_API int lm2_r3i64_overlaps(lm2_r3i64 a, lm2_r3i64 b);
LM2_API int64_t lm2_r3i64_volume(lm2_r3i64 r);

// ---------------------------------------------------------------------------
// lm2_r3i32 - 3D Range (32-bit signed integer)
// ---------------------------------------------------------------------------
typedef union lm2_r3i32 {
  lm2_v3i32 e[2];
  struct {
    lm2_v3i32 min;
    lm2_v3i32 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v3i32)
} lm2_r3i32;

// Constructors
LM2_API lm2_r3i32 lm2_r3i32_from_min_max(lm2_v3i32 min, lm2_v3i32 max);
LM2_API lm2_r3i32 lm2_r3i32_from_center_extents(lm2_v3i32 center, lm2_v3i32 extents);
LM2_API lm2_r3i32 lm2_r3i32_from_center_size(lm2_v3i32 center, lm2_v3i32 size);
LM2_API lm2_r3i32 lm2_r3i32_from_position_size(lm2_v3i32 position, lm2_v3i32 size);
LM2_API lm2_r3i32 lm2_r3i32_zero(void);

// Operations
LM2_API lm2_r3i32 lm2_r3i32_normalize(lm2_r3i32 r);
LM2_API lm2_r3i32 lm2_r3i32_translate(lm2_r3i32 r, lm2_v3i32 offset);
LM2_API lm2_r3i32 lm2_r3i32_scale(lm2_r3i32 r, int32_t factor);
LM2_API lm2_r3i32 lm2_r3i32_expand(lm2_r3i32 r, int32_t amount);

// Arithmetic operators
LM2_API lm2_r3i32 lm2_r3i32_add(lm2_r3i32 a, lm2_r3i32 b);
LM2_API lm2_r3i32 lm2_r3i32_add_scalar(lm2_r3i32 r, int32_t s);
LM2_API lm2_r3i32 lm2_r3i32_add_vec(lm2_r3i32 r, lm2_v3i32 v);
LM2_API lm2_r3i32 lm2_r3i32_sub(lm2_r3i32 a, lm2_r3i32 b);
LM2_API lm2_r3i32 lm2_r3i32_sub_scalar(lm2_r3i32 r, int32_t s);
LM2_API lm2_r3i32 lm2_r3i32_sub_vec(lm2_r3i32 r, lm2_v3i32 v);
LM2_API lm2_r3i32 lm2_r3i32_mul(lm2_r3i32 a, lm2_r3i32 b);
LM2_API lm2_r3i32 lm2_r3i32_mul_scalar(lm2_r3i32 r, int32_t s);
LM2_API lm2_r3i32 lm2_r3i32_mul_vec(lm2_r3i32 r, lm2_v3i32 v);
LM2_API lm2_r3i32 lm2_r3i32_div(lm2_r3i32 a, lm2_r3i32 b);
LM2_API lm2_r3i32 lm2_r3i32_div_scalar(lm2_r3i32 r, int32_t s);
LM2_API lm2_r3i32 lm2_r3i32_div_vec(lm2_r3i32 r, lm2_v3i32 v);
LM2_API lm2_r3i32 lm2_r3i32_mod(lm2_r3i32 a, lm2_r3i32 b);
LM2_API lm2_r3i32 lm2_r3i32_mod_scalar(lm2_r3i32 r, int32_t s);
LM2_API lm2_r3i32 lm2_r3i32_mod_vec(lm2_r3i32 r, lm2_v3i32 v);

// Scalar function forwards
LM2_API lm2_r3i32 lm2_floor_lm2_r3i32(lm2_r3i32 a);
LM2_API lm2_r3i32 lm2_ceil_lm2_r3i32(lm2_r3i32 a);
LM2_API lm2_r3i32 lm2_round_lm2_r3i32(lm2_r3i32 a);
LM2_API lm2_r3i32 lm2_trunc_lm2_r3i32(lm2_r3i32 a);
LM2_API lm2_r3i32 lm2_abs_lm2_r3i32(lm2_r3i32 a);
LM2_API lm2_r3i32 lm2_floor_multiple_lm2_r3i32(lm2_r3i32 a, lm2_r3i32 b);
LM2_API lm2_r3i32 lm2_ceil_multiple_lm2_r3i32(lm2_r3i32 a, lm2_r3i32 b);
LM2_API lm2_r3i32 lm2_round_multiple_lm2_r3i32(lm2_r3i32 a, lm2_r3i32 b);
LM2_API lm2_r3i32 lm2_trunc_multiple_lm2_r3i32(lm2_r3i32 a, lm2_r3i32 b);
LM2_API lm2_r3i32 lm2_min_lm2_r3i32(lm2_r3i32 a, lm2_r3i32 b);
LM2_API lm2_r3i32 lm2_max_lm2_r3i32(lm2_r3i32 a, lm2_r3i32 b);
LM2_API lm2_r3i32 lm2_clamp_lm2_r3i32(lm2_r3i32 a, lm2_r3i32 b, lm2_r3i32 c);
LM2_API lm2_r3i32 lm2_lerp_lm2_r3i32(lm2_r3i32 a, lm2_r3i32 b, lm2_r3i32 c);

// Queries
LM2_API lm2_r3i32 lm2_r3i32_union(lm2_r3i32 a, lm2_r3i32 b);
LM2_API lm2_r3i32 lm2_r3i32_intersection(lm2_r3i32 a, lm2_r3i32 b);
LM2_API lm2_v3i32 lm2_r3i32_size(lm2_r3i32 r);
LM2_API lm2_v3i32 lm2_r3i32_extents(lm2_r3i32 r);
LM2_API lm2_v3i32 lm2_r3i32_center(lm2_r3i32 r);
LM2_API int lm2_r3i32_contains_point(lm2_r3i32 r, lm2_v3i32 point);
LM2_API int lm2_r3i32_overlaps(lm2_r3i32 a, lm2_r3i32 b);
LM2_API int32_t lm2_r3i32_volume(lm2_r3i32 r);

// ---------------------------------------------------------------------------
// lm2_r3i16 - 3D Range (16-bit signed integer)
// ---------------------------------------------------------------------------
typedef union lm2_r3i16 {
  lm2_v3i16 e[2];
  struct {
    lm2_v3i16 min;
    lm2_v3i16 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v3i16)
} lm2_r3i16;

// Constructors
LM2_API lm2_r3i16 lm2_r3i16_from_min_max(lm2_v3i16 min, lm2_v3i16 max);
LM2_API lm2_r3i16 lm2_r3i16_from_center_extents(lm2_v3i16 center, lm2_v3i16 extents);
LM2_API lm2_r3i16 lm2_r3i16_from_center_size(lm2_v3i16 center, lm2_v3i16 size);
LM2_API lm2_r3i16 lm2_r3i16_from_position_size(lm2_v3i16 position, lm2_v3i16 size);
LM2_API lm2_r3i16 lm2_r3i16_zero(void);

// Operations
LM2_API lm2_r3i16 lm2_r3i16_normalize(lm2_r3i16 r);
LM2_API lm2_r3i16 lm2_r3i16_translate(lm2_r3i16 r, lm2_v3i16 offset);
LM2_API lm2_r3i16 lm2_r3i16_scale(lm2_r3i16 r, int16_t factor);
LM2_API lm2_r3i16 lm2_r3i16_expand(lm2_r3i16 r, int16_t amount);

// Arithmetic operators
LM2_API lm2_r3i16 lm2_r3i16_add(lm2_r3i16 a, lm2_r3i16 b);
LM2_API lm2_r3i16 lm2_r3i16_add_scalar(lm2_r3i16 r, int16_t s);
LM2_API lm2_r3i16 lm2_r3i16_add_vec(lm2_r3i16 r, lm2_v3i16 v);
LM2_API lm2_r3i16 lm2_r3i16_sub(lm2_r3i16 a, lm2_r3i16 b);
LM2_API lm2_r3i16 lm2_r3i16_sub_scalar(lm2_r3i16 r, int16_t s);
LM2_API lm2_r3i16 lm2_r3i16_sub_vec(lm2_r3i16 r, lm2_v3i16 v);
LM2_API lm2_r3i16 lm2_r3i16_mul(lm2_r3i16 a, lm2_r3i16 b);
LM2_API lm2_r3i16 lm2_r3i16_mul_scalar(lm2_r3i16 r, int16_t s);
LM2_API lm2_r3i16 lm2_r3i16_mul_vec(lm2_r3i16 r, lm2_v3i16 v);
LM2_API lm2_r3i16 lm2_r3i16_div(lm2_r3i16 a, lm2_r3i16 b);
LM2_API lm2_r3i16 lm2_r3i16_div_scalar(lm2_r3i16 r, int16_t s);
LM2_API lm2_r3i16 lm2_r3i16_div_vec(lm2_r3i16 r, lm2_v3i16 v);
LM2_API lm2_r3i16 lm2_r3i16_mod(lm2_r3i16 a, lm2_r3i16 b);
LM2_API lm2_r3i16 lm2_r3i16_mod_scalar(lm2_r3i16 r, int16_t s);
LM2_API lm2_r3i16 lm2_r3i16_mod_vec(lm2_r3i16 r, lm2_v3i16 v);

// Scalar function forwards
LM2_API lm2_r3i16 lm2_floor_lm2_r3i16(lm2_r3i16 a);
LM2_API lm2_r3i16 lm2_ceil_lm2_r3i16(lm2_r3i16 a);
LM2_API lm2_r3i16 lm2_round_lm2_r3i16(lm2_r3i16 a);
LM2_API lm2_r3i16 lm2_trunc_lm2_r3i16(lm2_r3i16 a);
LM2_API lm2_r3i16 lm2_abs_lm2_r3i16(lm2_r3i16 a);
LM2_API lm2_r3i16 lm2_floor_multiple_lm2_r3i16(lm2_r3i16 a, lm2_r3i16 b);
LM2_API lm2_r3i16 lm2_ceil_multiple_lm2_r3i16(lm2_r3i16 a, lm2_r3i16 b);
LM2_API lm2_r3i16 lm2_round_multiple_lm2_r3i16(lm2_r3i16 a, lm2_r3i16 b);
LM2_API lm2_r3i16 lm2_trunc_multiple_lm2_r3i16(lm2_r3i16 a, lm2_r3i16 b);
LM2_API lm2_r3i16 lm2_min_lm2_r3i16(lm2_r3i16 a, lm2_r3i16 b);
LM2_API lm2_r3i16 lm2_max_lm2_r3i16(lm2_r3i16 a, lm2_r3i16 b);
LM2_API lm2_r3i16 lm2_clamp_lm2_r3i16(lm2_r3i16 a, lm2_r3i16 b, lm2_r3i16 c);
LM2_API lm2_r3i16 lm2_lerp_lm2_r3i16(lm2_r3i16 a, lm2_r3i16 b, lm2_r3i16 c);

// Queries
LM2_API lm2_r3i16 lm2_r3i16_union(lm2_r3i16 a, lm2_r3i16 b);
LM2_API lm2_r3i16 lm2_r3i16_intersection(lm2_r3i16 a, lm2_r3i16 b);
LM2_API lm2_v3i16 lm2_r3i16_size(lm2_r3i16 r);
LM2_API lm2_v3i16 lm2_r3i16_extents(lm2_r3i16 r);
LM2_API lm2_v3i16 lm2_r3i16_center(lm2_r3i16 r);
LM2_API int lm2_r3i16_contains_point(lm2_r3i16 r, lm2_v3i16 point);
LM2_API int lm2_r3i16_overlaps(lm2_r3i16 a, lm2_r3i16 b);
LM2_API int16_t lm2_r3i16_volume(lm2_r3i16 r);

// ---------------------------------------------------------------------------
// lm2_r3i8 - 3D Range (8-bit signed integer)
// ---------------------------------------------------------------------------
typedef union lm2_r3i8 {
  lm2_v3i8 e[2];
  struct {
    lm2_v3i8 min;
    lm2_v3i8 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v3i8)
} lm2_r3i8;

// Constructors
LM2_API lm2_r3i8 lm2_r3i8_from_min_max(lm2_v3i8 min, lm2_v3i8 max);
LM2_API lm2_r3i8 lm2_r3i8_from_center_extents(lm2_v3i8 center, lm2_v3i8 extents);
LM2_API lm2_r3i8 lm2_r3i8_from_center_size(lm2_v3i8 center, lm2_v3i8 size);
LM2_API lm2_r3i8 lm2_r3i8_from_position_size(lm2_v3i8 position, lm2_v3i8 size);
LM2_API lm2_r3i8 lm2_r3i8_zero(void);

// Operations
LM2_API lm2_r3i8 lm2_r3i8_normalize(lm2_r3i8 r);
LM2_API lm2_r3i8 lm2_r3i8_translate(lm2_r3i8 r, lm2_v3i8 offset);
LM2_API lm2_r3i8 lm2_r3i8_scale(lm2_r3i8 r, int8_t factor);
LM2_API lm2_r3i8 lm2_r3i8_expand(lm2_r3i8 r, int8_t amount);

// Arithmetic operators
LM2_API lm2_r3i8 lm2_r3i8_add(lm2_r3i8 a, lm2_r3i8 b);
LM2_API lm2_r3i8 lm2_r3i8_add_scalar(lm2_r3i8 r, int8_t s);
LM2_API lm2_r3i8 lm2_r3i8_add_vec(lm2_r3i8 r, lm2_v3i8 v);
LM2_API lm2_r3i8 lm2_r3i8_sub(lm2_r3i8 a, lm2_r3i8 b);
LM2_API lm2_r3i8 lm2_r3i8_sub_scalar(lm2_r3i8 r, int8_t s);
LM2_API lm2_r3i8 lm2_r3i8_sub_vec(lm2_r3i8 r, lm2_v3i8 v);
LM2_API lm2_r3i8 lm2_r3i8_mul(lm2_r3i8 a, lm2_r3i8 b);
LM2_API lm2_r3i8 lm2_r3i8_mul_scalar(lm2_r3i8 r, int8_t s);
LM2_API lm2_r3i8 lm2_r3i8_mul_vec(lm2_r3i8 r, lm2_v3i8 v);
LM2_API lm2_r3i8 lm2_r3i8_div(lm2_r3i8 a, lm2_r3i8 b);
LM2_API lm2_r3i8 lm2_r3i8_div_scalar(lm2_r3i8 r, int8_t s);
LM2_API lm2_r3i8 lm2_r3i8_div_vec(lm2_r3i8 r, lm2_v3i8 v);
LM2_API lm2_r3i8 lm2_r3i8_mod(lm2_r3i8 a, lm2_r3i8 b);
LM2_API lm2_r3i8 lm2_r3i8_mod_scalar(lm2_r3i8 r, int8_t s);
LM2_API lm2_r3i8 lm2_r3i8_mod_vec(lm2_r3i8 r, lm2_v3i8 v);

// Scalar function forwards
LM2_API lm2_r3i8 lm2_floor_lm2_r3i8(lm2_r3i8 a);
LM2_API lm2_r3i8 lm2_ceil_lm2_r3i8(lm2_r3i8 a);
LM2_API lm2_r3i8 lm2_round_lm2_r3i8(lm2_r3i8 a);
LM2_API lm2_r3i8 lm2_trunc_lm2_r3i8(lm2_r3i8 a);
LM2_API lm2_r3i8 lm2_abs_lm2_r3i8(lm2_r3i8 a);
LM2_API lm2_r3i8 lm2_floor_multiple_lm2_r3i8(lm2_r3i8 a, lm2_r3i8 b);
LM2_API lm2_r3i8 lm2_ceil_multiple_lm2_r3i8(lm2_r3i8 a, lm2_r3i8 b);
LM2_API lm2_r3i8 lm2_round_multiple_lm2_r3i8(lm2_r3i8 a, lm2_r3i8 b);
LM2_API lm2_r3i8 lm2_trunc_multiple_lm2_r3i8(lm2_r3i8 a, lm2_r3i8 b);
LM2_API lm2_r3i8 lm2_min_lm2_r3i8(lm2_r3i8 a, lm2_r3i8 b);
LM2_API lm2_r3i8 lm2_max_lm2_r3i8(lm2_r3i8 a, lm2_r3i8 b);
LM2_API lm2_r3i8 lm2_clamp_lm2_r3i8(lm2_r3i8 a, lm2_r3i8 b, lm2_r3i8 c);
LM2_API lm2_r3i8 lm2_lerp_lm2_r3i8(lm2_r3i8 a, lm2_r3i8 b, lm2_r3i8 c);

// Queries
LM2_API lm2_r3i8 lm2_r3i8_union(lm2_r3i8 a, lm2_r3i8 b);
LM2_API lm2_r3i8 lm2_r3i8_intersection(lm2_r3i8 a, lm2_r3i8 b);
LM2_API lm2_v3i8 lm2_r3i8_size(lm2_r3i8 r);
LM2_API lm2_v3i8 lm2_r3i8_extents(lm2_r3i8 r);
LM2_API lm2_v3i8 lm2_r3i8_center(lm2_r3i8 r);
LM2_API int lm2_r3i8_contains_point(lm2_r3i8 r, lm2_v3i8 point);
LM2_API int lm2_r3i8_overlaps(lm2_r3i8 a, lm2_r3i8 b);
LM2_API int8_t lm2_r3i8_volume(lm2_r3i8 r);

// ---------------------------------------------------------------------------
// lm2_r3u64 - 3D Range (64-bit unsigned integer)
// ---------------------------------------------------------------------------
typedef union lm2_r3u64 {
  lm2_v3u64 e[2];
  struct {
    lm2_v3u64 min;
    lm2_v3u64 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v3u64)
} lm2_r3u64;

// Constructors
LM2_API lm2_r3u64 lm2_r3u64_from_min_max(lm2_v3u64 min, lm2_v3u64 max);
LM2_API lm2_r3u64 lm2_r3u64_from_center_extents(lm2_v3u64 center, lm2_v3u64 extents);
LM2_API lm2_r3u64 lm2_r3u64_from_center_size(lm2_v3u64 center, lm2_v3u64 size);
LM2_API lm2_r3u64 lm2_r3u64_from_position_size(lm2_v3u64 position, lm2_v3u64 size);
LM2_API lm2_r3u64 lm2_r3u64_zero(void);

// Operations
LM2_API lm2_r3u64 lm2_r3u64_normalize(lm2_r3u64 r);
LM2_API lm2_r3u64 lm2_r3u64_translate(lm2_r3u64 r, lm2_v3u64 offset);
LM2_API lm2_r3u64 lm2_r3u64_scale(lm2_r3u64 r, uint64_t factor);
LM2_API lm2_r3u64 lm2_r3u64_expand(lm2_r3u64 r, uint64_t amount);

// Arithmetic operators
LM2_API lm2_r3u64 lm2_r3u64_add(lm2_r3u64 a, lm2_r3u64 b);
LM2_API lm2_r3u64 lm2_r3u64_add_scalar(lm2_r3u64 r, uint64_t s);
LM2_API lm2_r3u64 lm2_r3u64_add_vec(lm2_r3u64 r, lm2_v3u64 v);
LM2_API lm2_r3u64 lm2_r3u64_sub(lm2_r3u64 a, lm2_r3u64 b);
LM2_API lm2_r3u64 lm2_r3u64_sub_scalar(lm2_r3u64 r, uint64_t s);
LM2_API lm2_r3u64 lm2_r3u64_sub_vec(lm2_r3u64 r, lm2_v3u64 v);
LM2_API lm2_r3u64 lm2_r3u64_mul(lm2_r3u64 a, lm2_r3u64 b);
LM2_API lm2_r3u64 lm2_r3u64_mul_scalar(lm2_r3u64 r, uint64_t s);
LM2_API lm2_r3u64 lm2_r3u64_mul_vec(lm2_r3u64 r, lm2_v3u64 v);
LM2_API lm2_r3u64 lm2_r3u64_div(lm2_r3u64 a, lm2_r3u64 b);
LM2_API lm2_r3u64 lm2_r3u64_div_scalar(lm2_r3u64 r, uint64_t s);
LM2_API lm2_r3u64 lm2_r3u64_div_vec(lm2_r3u64 r, lm2_v3u64 v);
LM2_API lm2_r3u64 lm2_r3u64_mod(lm2_r3u64 a, lm2_r3u64 b);
LM2_API lm2_r3u64 lm2_r3u64_mod_scalar(lm2_r3u64 r, uint64_t s);
LM2_API lm2_r3u64 lm2_r3u64_mod_vec(lm2_r3u64 r, lm2_v3u64 v);

// Scalar function forwards
LM2_API lm2_r3u64 lm2_floor_lm2_r3u64(lm2_r3u64 a);
LM2_API lm2_r3u64 lm2_ceil_lm2_r3u64(lm2_r3u64 a);
LM2_API lm2_r3u64 lm2_round_lm2_r3u64(lm2_r3u64 a);
LM2_API lm2_r3u64 lm2_trunc_lm2_r3u64(lm2_r3u64 a);
LM2_API lm2_r3u64 lm2_abs_lm2_r3u64(lm2_r3u64 a);
LM2_API lm2_r3u64 lm2_floor_multiple_lm2_r3u64(lm2_r3u64 a, lm2_r3u64 b);
LM2_API lm2_r3u64 lm2_ceil_multiple_lm2_r3u64(lm2_r3u64 a, lm2_r3u64 b);
LM2_API lm2_r3u64 lm2_round_multiple_lm2_r3u64(lm2_r3u64 a, lm2_r3u64 b);
LM2_API lm2_r3u64 lm2_trunc_multiple_lm2_r3u64(lm2_r3u64 a, lm2_r3u64 b);
LM2_API lm2_r3u64 lm2_min_lm2_r3u64(lm2_r3u64 a, lm2_r3u64 b);
LM2_API lm2_r3u64 lm2_max_lm2_r3u64(lm2_r3u64 a, lm2_r3u64 b);
LM2_API lm2_r3u64 lm2_clamp_lm2_r3u64(lm2_r3u64 a, lm2_r3u64 b, lm2_r3u64 c);
LM2_API lm2_r3u64 lm2_lerp_lm2_r3u64(lm2_r3u64 a, lm2_r3u64 b, lm2_r3u64 c);

// Queries
LM2_API lm2_r3u64 lm2_r3u64_union(lm2_r3u64 a, lm2_r3u64 b);
LM2_API lm2_r3u64 lm2_r3u64_intersection(lm2_r3u64 a, lm2_r3u64 b);
LM2_API lm2_v3u64 lm2_r3u64_size(lm2_r3u64 r);
LM2_API lm2_v3u64 lm2_r3u64_extents(lm2_r3u64 r);
LM2_API lm2_v3u64 lm2_r3u64_center(lm2_r3u64 r);
LM2_API int lm2_r3u64_contains_point(lm2_r3u64 r, lm2_v3u64 point);
LM2_API int lm2_r3u64_overlaps(lm2_r3u64 a, lm2_r3u64 b);
LM2_API uint64_t lm2_r3u64_volume(lm2_r3u64 r);

// ---------------------------------------------------------------------------
// lm2_r3u32 - 3D Range (32-bit unsigned integer)
// ---------------------------------------------------------------------------
typedef union lm2_r3u32 {
  lm2_v3u32 e[2];
  struct {
    lm2_v3u32 min;
    lm2_v3u32 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v3u32)
} lm2_r3u32;

// Constructors
LM2_API lm2_r3u32 lm2_r3u32_from_min_max(lm2_v3u32 min, lm2_v3u32 max);
LM2_API lm2_r3u32 lm2_r3u32_from_center_extents(lm2_v3u32 center, lm2_v3u32 extents);
LM2_API lm2_r3u32 lm2_r3u32_from_center_size(lm2_v3u32 center, lm2_v3u32 size);
LM2_API lm2_r3u32 lm2_r3u32_from_position_size(lm2_v3u32 position, lm2_v3u32 size);
LM2_API lm2_r3u32 lm2_r3u32_zero(void);

// Operations
LM2_API lm2_r3u32 lm2_r3u32_normalize(lm2_r3u32 r);
LM2_API lm2_r3u32 lm2_r3u32_translate(lm2_r3u32 r, lm2_v3u32 offset);
LM2_API lm2_r3u32 lm2_r3u32_scale(lm2_r3u32 r, uint32_t factor);
LM2_API lm2_r3u32 lm2_r3u32_expand(lm2_r3u32 r, uint32_t amount);

// Arithmetic operators
LM2_API lm2_r3u32 lm2_r3u32_add(lm2_r3u32 a, lm2_r3u32 b);
LM2_API lm2_r3u32 lm2_r3u32_add_scalar(lm2_r3u32 r, uint32_t s);
LM2_API lm2_r3u32 lm2_r3u32_add_vec(lm2_r3u32 r, lm2_v3u32 v);
LM2_API lm2_r3u32 lm2_r3u32_sub(lm2_r3u32 a, lm2_r3u32 b);
LM2_API lm2_r3u32 lm2_r3u32_sub_scalar(lm2_r3u32 r, uint32_t s);
LM2_API lm2_r3u32 lm2_r3u32_sub_vec(lm2_r3u32 r, lm2_v3u32 v);
LM2_API lm2_r3u32 lm2_r3u32_mul(lm2_r3u32 a, lm2_r3u32 b);
LM2_API lm2_r3u32 lm2_r3u32_mul_scalar(lm2_r3u32 r, uint32_t s);
LM2_API lm2_r3u32 lm2_r3u32_mul_vec(lm2_r3u32 r, lm2_v3u32 v);
LM2_API lm2_r3u32 lm2_r3u32_div(lm2_r3u32 a, lm2_r3u32 b);
LM2_API lm2_r3u32 lm2_r3u32_div_scalar(lm2_r3u32 r, uint32_t s);
LM2_API lm2_r3u32 lm2_r3u32_div_vec(lm2_r3u32 r, lm2_v3u32 v);
LM2_API lm2_r3u32 lm2_r3u32_mod(lm2_r3u32 a, lm2_r3u32 b);
LM2_API lm2_r3u32 lm2_r3u32_mod_scalar(lm2_r3u32 r, uint32_t s);
LM2_API lm2_r3u32 lm2_r3u32_mod_vec(lm2_r3u32 r, lm2_v3u32 v);

// Scalar function forwards
LM2_API lm2_r3u32 lm2_floor_lm2_r3u32(lm2_r3u32 a);
LM2_API lm2_r3u32 lm2_ceil_lm2_r3u32(lm2_r3u32 a);
LM2_API lm2_r3u32 lm2_round_lm2_r3u32(lm2_r3u32 a);
LM2_API lm2_r3u32 lm2_trunc_lm2_r3u32(lm2_r3u32 a);
LM2_API lm2_r3u32 lm2_abs_lm2_r3u32(lm2_r3u32 a);
LM2_API lm2_r3u32 lm2_floor_multiple_lm2_r3u32(lm2_r3u32 a, lm2_r3u32 b);
LM2_API lm2_r3u32 lm2_ceil_multiple_lm2_r3u32(lm2_r3u32 a, lm2_r3u32 b);
LM2_API lm2_r3u32 lm2_round_multiple_lm2_r3u32(lm2_r3u32 a, lm2_r3u32 b);
LM2_API lm2_r3u32 lm2_trunc_multiple_lm2_r3u32(lm2_r3u32 a, lm2_r3u32 b);
LM2_API lm2_r3u32 lm2_min_lm2_r3u32(lm2_r3u32 a, lm2_r3u32 b);
LM2_API lm2_r3u32 lm2_max_lm2_r3u32(lm2_r3u32 a, lm2_r3u32 b);
LM2_API lm2_r3u32 lm2_clamp_lm2_r3u32(lm2_r3u32 a, lm2_r3u32 b, lm2_r3u32 c);
LM2_API lm2_r3u32 lm2_lerp_lm2_r3u32(lm2_r3u32 a, lm2_r3u32 b, lm2_r3u32 c);

// Queries
LM2_API lm2_r3u32 lm2_r3u32_union(lm2_r3u32 a, lm2_r3u32 b);
LM2_API lm2_r3u32 lm2_r3u32_intersection(lm2_r3u32 a, lm2_r3u32 b);
LM2_API lm2_v3u32 lm2_r3u32_size(lm2_r3u32 r);
LM2_API lm2_v3u32 lm2_r3u32_extents(lm2_r3u32 r);
LM2_API lm2_v3u32 lm2_r3u32_center(lm2_r3u32 r);
LM2_API int lm2_r3u32_contains_point(lm2_r3u32 r, lm2_v3u32 point);
LM2_API int lm2_r3u32_overlaps(lm2_r3u32 a, lm2_r3u32 b);
LM2_API uint32_t lm2_r3u32_volume(lm2_r3u32 r);

// ---------------------------------------------------------------------------
// lm2_r3u16 - 3D Range (16-bit unsigned integer)
// ---------------------------------------------------------------------------
typedef union lm2_r3u16 {
  lm2_v3u16 e[2];
  struct {
    lm2_v3u16 min;
    lm2_v3u16 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v3u16)
} lm2_r3u16;

// Constructors
LM2_API lm2_r3u16 lm2_r3u16_from_min_max(lm2_v3u16 min, lm2_v3u16 max);
LM2_API lm2_r3u16 lm2_r3u16_from_center_extents(lm2_v3u16 center, lm2_v3u16 extents);
LM2_API lm2_r3u16 lm2_r3u16_from_center_size(lm2_v3u16 center, lm2_v3u16 size);
LM2_API lm2_r3u16 lm2_r3u16_from_position_size(lm2_v3u16 position, lm2_v3u16 size);
LM2_API lm2_r3u16 lm2_r3u16_zero(void);

// Operations
LM2_API lm2_r3u16 lm2_r3u16_normalize(lm2_r3u16 r);
LM2_API lm2_r3u16 lm2_r3u16_translate(lm2_r3u16 r, lm2_v3u16 offset);
LM2_API lm2_r3u16 lm2_r3u16_scale(lm2_r3u16 r, uint16_t factor);
LM2_API lm2_r3u16 lm2_r3u16_expand(lm2_r3u16 r, uint16_t amount);

// Arithmetic operators
LM2_API lm2_r3u16 lm2_r3u16_add(lm2_r3u16 a, lm2_r3u16 b);
LM2_API lm2_r3u16 lm2_r3u16_add_scalar(lm2_r3u16 r, uint16_t s);
LM2_API lm2_r3u16 lm2_r3u16_add_vec(lm2_r3u16 r, lm2_v3u16 v);
LM2_API lm2_r3u16 lm2_r3u16_sub(lm2_r3u16 a, lm2_r3u16 b);
LM2_API lm2_r3u16 lm2_r3u16_sub_scalar(lm2_r3u16 r, uint16_t s);
LM2_API lm2_r3u16 lm2_r3u16_sub_vec(lm2_r3u16 r, lm2_v3u16 v);
LM2_API lm2_r3u16 lm2_r3u16_mul(lm2_r3u16 a, lm2_r3u16 b);
LM2_API lm2_r3u16 lm2_r3u16_mul_scalar(lm2_r3u16 r, uint16_t s);
LM2_API lm2_r3u16 lm2_r3u16_mul_vec(lm2_r3u16 r, lm2_v3u16 v);
LM2_API lm2_r3u16 lm2_r3u16_div(lm2_r3u16 a, lm2_r3u16 b);
LM2_API lm2_r3u16 lm2_r3u16_div_scalar(lm2_r3u16 r, uint16_t s);
LM2_API lm2_r3u16 lm2_r3u16_div_vec(lm2_r3u16 r, lm2_v3u16 v);
LM2_API lm2_r3u16 lm2_r3u16_mod(lm2_r3u16 a, lm2_r3u16 b);
LM2_API lm2_r3u16 lm2_r3u16_mod_scalar(lm2_r3u16 r, uint16_t s);
LM2_API lm2_r3u16 lm2_r3u16_mod_vec(lm2_r3u16 r, lm2_v3u16 v);

// Scalar function forwards
LM2_API lm2_r3u16 lm2_floor_lm2_r3u16(lm2_r3u16 a);
LM2_API lm2_r3u16 lm2_ceil_lm2_r3u16(lm2_r3u16 a);
LM2_API lm2_r3u16 lm2_round_lm2_r3u16(lm2_r3u16 a);
LM2_API lm2_r3u16 lm2_trunc_lm2_r3u16(lm2_r3u16 a);
LM2_API lm2_r3u16 lm2_abs_lm2_r3u16(lm2_r3u16 a);
LM2_API lm2_r3u16 lm2_floor_multiple_lm2_r3u16(lm2_r3u16 a, lm2_r3u16 b);
LM2_API lm2_r3u16 lm2_ceil_multiple_lm2_r3u16(lm2_r3u16 a, lm2_r3u16 b);
LM2_API lm2_r3u16 lm2_round_multiple_lm2_r3u16(lm2_r3u16 a, lm2_r3u16 b);
LM2_API lm2_r3u16 lm2_trunc_multiple_lm2_r3u16(lm2_r3u16 a, lm2_r3u16 b);
LM2_API lm2_r3u16 lm2_min_lm2_r3u16(lm2_r3u16 a, lm2_r3u16 b);
LM2_API lm2_r3u16 lm2_max_lm2_r3u16(lm2_r3u16 a, lm2_r3u16 b);
LM2_API lm2_r3u16 lm2_clamp_lm2_r3u16(lm2_r3u16 a, lm2_r3u16 b, lm2_r3u16 c);
LM2_API lm2_r3u16 lm2_lerp_lm2_r3u16(lm2_r3u16 a, lm2_r3u16 b, lm2_r3u16 c);

// Queries
LM2_API lm2_r3u16 lm2_r3u16_union(lm2_r3u16 a, lm2_r3u16 b);
LM2_API lm2_r3u16 lm2_r3u16_intersection(lm2_r3u16 a, lm2_r3u16 b);
LM2_API lm2_v3u16 lm2_r3u16_size(lm2_r3u16 r);
LM2_API lm2_v3u16 lm2_r3u16_extents(lm2_r3u16 r);
LM2_API lm2_v3u16 lm2_r3u16_center(lm2_r3u16 r);
LM2_API int lm2_r3u16_contains_point(lm2_r3u16 r, lm2_v3u16 point);
LM2_API int lm2_r3u16_overlaps(lm2_r3u16 a, lm2_r3u16 b);
LM2_API uint16_t lm2_r3u16_volume(lm2_r3u16 r);

// ---------------------------------------------------------------------------
// lm2_r3u8 - 3D Range (8-bit unsigned integer)
// ---------------------------------------------------------------------------
typedef union lm2_r3u8 {
  lm2_v3u8 e[2];
  struct {
    lm2_v3u8 min;
    lm2_v3u8 max;
  };
  _LM2_RANGE_SUBSCRIPT_OP(lm2_v3u8)
} lm2_r3u8;

// Constructors
LM2_API lm2_r3u8 lm2_r3u8_from_min_max(lm2_v3u8 min, lm2_v3u8 max);
LM2_API lm2_r3u8 lm2_r3u8_from_center_extents(lm2_v3u8 center, lm2_v3u8 extents);
LM2_API lm2_r3u8 lm2_r3u8_from_center_size(lm2_v3u8 center, lm2_v3u8 size);
LM2_API lm2_r3u8 lm2_r3u8_from_position_size(lm2_v3u8 position, lm2_v3u8 size);
LM2_API lm2_r3u8 lm2_r3u8_zero(void);

// Operations
LM2_API lm2_r3u8 lm2_r3u8_normalize(lm2_r3u8 r);
LM2_API lm2_r3u8 lm2_r3u8_translate(lm2_r3u8 r, lm2_v3u8 offset);
LM2_API lm2_r3u8 lm2_r3u8_scale(lm2_r3u8 r, uint8_t factor);
LM2_API lm2_r3u8 lm2_r3u8_expand(lm2_r3u8 r, uint8_t amount);

// Arithmetic operators
LM2_API lm2_r3u8 lm2_r3u8_add(lm2_r3u8 a, lm2_r3u8 b);
LM2_API lm2_r3u8 lm2_r3u8_add_scalar(lm2_r3u8 r, uint8_t s);
LM2_API lm2_r3u8 lm2_r3u8_add_vec(lm2_r3u8 r, lm2_v3u8 v);
LM2_API lm2_r3u8 lm2_r3u8_sub(lm2_r3u8 a, lm2_r3u8 b);
LM2_API lm2_r3u8 lm2_r3u8_sub_scalar(lm2_r3u8 r, uint8_t s);
LM2_API lm2_r3u8 lm2_r3u8_sub_vec(lm2_r3u8 r, lm2_v3u8 v);
LM2_API lm2_r3u8 lm2_r3u8_mul(lm2_r3u8 a, lm2_r3u8 b);
LM2_API lm2_r3u8 lm2_r3u8_mul_scalar(lm2_r3u8 r, uint8_t s);
LM2_API lm2_r3u8 lm2_r3u8_mul_vec(lm2_r3u8 r, lm2_v3u8 v);
LM2_API lm2_r3u8 lm2_r3u8_div(lm2_r3u8 a, lm2_r3u8 b);
LM2_API lm2_r3u8 lm2_r3u8_div_scalar(lm2_r3u8 r, uint8_t s);
LM2_API lm2_r3u8 lm2_r3u8_div_vec(lm2_r3u8 r, lm2_v3u8 v);
LM2_API lm2_r3u8 lm2_r3u8_mod(lm2_r3u8 a, lm2_r3u8 b);
LM2_API lm2_r3u8 lm2_r3u8_mod_scalar(lm2_r3u8 r, uint8_t s);
LM2_API lm2_r3u8 lm2_r3u8_mod_vec(lm2_r3u8 r, lm2_v3u8 v);

// Scalar function forwards
LM2_API lm2_r3u8 lm2_floor_lm2_r3u8(lm2_r3u8 a);
LM2_API lm2_r3u8 lm2_ceil_lm2_r3u8(lm2_r3u8 a);
LM2_API lm2_r3u8 lm2_round_lm2_r3u8(lm2_r3u8 a);
LM2_API lm2_r3u8 lm2_trunc_lm2_r3u8(lm2_r3u8 a);
LM2_API lm2_r3u8 lm2_abs_lm2_r3u8(lm2_r3u8 a);
LM2_API lm2_r3u8 lm2_floor_multiple_lm2_r3u8(lm2_r3u8 a, lm2_r3u8 b);
LM2_API lm2_r3u8 lm2_ceil_multiple_lm2_r3u8(lm2_r3u8 a, lm2_r3u8 b);
LM2_API lm2_r3u8 lm2_round_multiple_lm2_r3u8(lm2_r3u8 a, lm2_r3u8 b);
LM2_API lm2_r3u8 lm2_trunc_multiple_lm2_r3u8(lm2_r3u8 a, lm2_r3u8 b);
LM2_API lm2_r3u8 lm2_min_lm2_r3u8(lm2_r3u8 a, lm2_r3u8 b);
LM2_API lm2_r3u8 lm2_max_lm2_r3u8(lm2_r3u8 a, lm2_r3u8 b);
LM2_API lm2_r3u8 lm2_clamp_lm2_r3u8(lm2_r3u8 a, lm2_r3u8 b, lm2_r3u8 c);
LM2_API lm2_r3u8 lm2_lerp_lm2_r3u8(lm2_r3u8 a, lm2_r3u8 b, lm2_r3u8 c);

// Queries
LM2_API lm2_r3u8 lm2_r3u8_union(lm2_r3u8 a, lm2_r3u8 b);
LM2_API lm2_r3u8 lm2_r3u8_intersection(lm2_r3u8 a, lm2_r3u8 b);
LM2_API lm2_v3u8 lm2_r3u8_size(lm2_r3u8 r);
LM2_API lm2_v3u8 lm2_r3u8_extents(lm2_r3u8 r);
LM2_API lm2_v3u8 lm2_r3u8_center(lm2_r3u8 r);
LM2_API int lm2_r3u8_contains_point(lm2_r3u8 r, lm2_v3u8 point);
LM2_API int lm2_r3u8_overlaps(lm2_r3u8 a, lm2_r3u8 b);
LM2_API uint8_t lm2_r3u8_volume(lm2_r3u8 r);

// Default range3 type (float-based)
typedef lm2_r3f32 lm2_r3;

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// C++ operator overloads and constructors (must be outside extern "C")
#ifndef LM2_NO_CPP_OPERATORS
#  include "lm2_range_operators.h"
_LM2_DEFINE_RANGE3_OPERATORS(lm2_r3f64, lm2_v3f64)
_LM2_DEFINE_RANGE3_OPERATORS(lm2_r3f32, lm2_v3f32)
_LM2_DEFINE_RANGE3_OPERATORS(lm2_r3i64, lm2_v3i64)
_LM2_DEFINE_RANGE3_OPERATORS(lm2_r3i32, lm2_v3i32)
_LM2_DEFINE_RANGE3_OPERATORS(lm2_r3i16, lm2_v3i16)
_LM2_DEFINE_RANGE3_OPERATORS(lm2_r3i8, lm2_v3i8)
_LM2_DEFINE_RANGE3_OPERATORS(lm2_r3u64, lm2_v3u64)
_LM2_DEFINE_RANGE3_OPERATORS(lm2_r3u32, lm2_v3u32)
_LM2_DEFINE_RANGE3_OPERATORS(lm2_r3u16, lm2_v3u16)
_LM2_DEFINE_RANGE3_OPERATORS(lm2_r3u8, lm2_v3u8)
#endif
