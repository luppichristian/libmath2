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
// lm2_r4_f64 - 4D Range (double precision)
// ---------------------------------------------------------------------------
typedef union lm2_r4_f64 {
  lm2_v4_f64 e[2];
  double e2[8];
  struct {
    lm2_v4_f64 min;
    lm2_v4_f64 max;
  };
  _LM2_SUBSCRIPT_OP(lm2_v4_f64, 2)
} lm2_r4_f64;

// Constructors
LM2_API lm2_r4_f64 lm2_r4_from_min_max_f64(lm2_v4_f64 min, lm2_v4_f64 max);
LM2_API lm2_r4_f64 lm2_r4_from_center_extents_f64(lm2_v4_f64 center, lm2_v4_f64 extents);
LM2_API lm2_r4_f64 lm2_r4_from_center_size_f64(lm2_v4_f64 center, lm2_v4_f64 size);
LM2_API lm2_r4_f64 lm2_r4_from_position_size_f64(lm2_v4_f64 position, lm2_v4_f64 size);
LM2_API lm2_r4_f64 lm2_r4_zero_f64(void);

// Operations
LM2_API lm2_r4_f64 lm2_r4_normalize_f64(lm2_r4_f64 r);
LM2_API lm2_r4_f64 lm2_r4_translate_f64(lm2_r4_f64 r, lm2_v4_f64 offset);
LM2_API lm2_r4_f64 lm2_r4_scale_f64(lm2_r4_f64 r, double factor);
LM2_API lm2_r4_f64 lm2_r4_expand_f64(lm2_r4_f64 r, double amount);

// Arithmetic operators
LM2_API lm2_r4_f64 lm2_r4_add_f64(lm2_r4_f64 a, lm2_r4_f64 b);
LM2_API lm2_r4_f64 lm2_r4_add_s_f64(lm2_r4_f64 r, double s);
LM2_API lm2_r4_f64 lm2_r4_add_v_f64(lm2_r4_f64 r, lm2_v4_f64 v);
LM2_API lm2_r4_f64 lm2_r4_sub_f64(lm2_r4_f64 a, lm2_r4_f64 b);
LM2_API lm2_r4_f64 lm2_r4_sub_s_f64(lm2_r4_f64 r, double s);
LM2_API lm2_r4_f64 lm2_r4_sub_v_f64(lm2_r4_f64 r, lm2_v4_f64 v);
LM2_API lm2_r4_f64 lm2_r4_mul_f64(lm2_r4_f64 a, lm2_r4_f64 b);
LM2_API lm2_r4_f64 lm2_r4_mul_s_f64(lm2_r4_f64 r, double s);
LM2_API lm2_r4_f64 lm2_r4_mul_v_f64(lm2_r4_f64 r, lm2_v4_f64 v);
LM2_API lm2_r4_f64 lm2_r4_div_f64(lm2_r4_f64 a, lm2_r4_f64 b);
LM2_API lm2_r4_f64 lm2_r4_div_s_f64(lm2_r4_f64 r, double s);
LM2_API lm2_r4_f64 lm2_r4_div_v_f64(lm2_r4_f64 r, lm2_v4_f64 v);
LM2_API lm2_r4_f64 lm2_r4_mod_f64(lm2_r4_f64 a, lm2_r4_f64 b);
LM2_API lm2_r4_f64 lm2_r4_mod_s_f64(lm2_r4_f64 r, double s);
LM2_API lm2_r4_f64 lm2_r4_mod_v_f64(lm2_r4_f64 r, lm2_v4_f64 v);

// Scalar function forwards
LM2_API lm2_r4_f64 lm2_r4_floor_f64(lm2_r4_f64 a);
LM2_API lm2_r4_f64 lm2_r4_ceil_f64(lm2_r4_f64 a);
LM2_API lm2_r4_f64 lm2_r4_round_f64(lm2_r4_f64 a);
LM2_API lm2_r4_f64 lm2_r4_trunc_f64(lm2_r4_f64 a);
LM2_API lm2_r4_f64 lm2_r4_abs_f64(lm2_r4_f64 a);
LM2_API lm2_r4_f64 lm2_r4_floor_multiple_f64(lm2_r4_f64 a, lm2_r4_f64 b);
LM2_API lm2_r4_f64 lm2_r4_ceil_multiple_f64(lm2_r4_f64 a, lm2_r4_f64 b);
LM2_API lm2_r4_f64 lm2_r4_round_multiple_f64(lm2_r4_f64 a, lm2_r4_f64 b);
LM2_API lm2_r4_f64 lm2_r4_trunc_multiple_f64(lm2_r4_f64 a, lm2_r4_f64 b);
LM2_API lm2_r4_f64 lm2_r4_min_f64(lm2_r4_f64 a, lm2_r4_f64 b);
LM2_API lm2_r4_f64 lm2_r4_max_f64(lm2_r4_f64 a, lm2_r4_f64 b);
LM2_API lm2_r4_f64 lm2_r4_clamp_f64(lm2_r4_f64 a, lm2_r4_f64 b, lm2_r4_f64 c);
LM2_API lm2_r4_f64 lm2_r4_lerp_f64(lm2_r4_f64 a, lm2_r4_f64 b, lm2_r4_f64 c);

// Queries
LM2_API lm2_r4_f64 lm2_r4_union_f64(lm2_r4_f64 a, lm2_r4_f64 b);
LM2_API lm2_r4_f64 lm2_r4_intersection_f64(lm2_r4_f64 a, lm2_r4_f64 b);
LM2_API lm2_v4_f64 lm2_r4_size_f64(lm2_r4_f64 r);
LM2_API lm2_v4_f64 lm2_r4_extents_f64(lm2_r4_f64 r);
LM2_API lm2_v4_f64 lm2_r4_center_f64(lm2_r4_f64 r);
LM2_API int lm2_r4_contains_point_f64(lm2_r4_f64 r, lm2_v4_f64 point);
LM2_API int lm2_r4_overlaps_f64(lm2_r4_f64 a, lm2_r4_f64 b);
LM2_API double lm2_r4_hypervolume_f64(lm2_r4_f64 r);

// ---------------------------------------------------------------------------
// lm2_r4_f32 - 4D Range (single precision)
// ---------------------------------------------------------------------------
typedef union lm2_r4_f32 {
  lm2_v4_f32 e[2];
  float e2[8];
  struct {
    lm2_v4_f32 min;
    lm2_v4_f32 max;
  };
  _LM2_SUBSCRIPT_OP(lm2_v4_f32, 2)
} lm2_r4_f32;

// Constructors
LM2_API lm2_r4_f32 lm2_r4_from_min_max_f32(lm2_v4_f32 min, lm2_v4_f32 max);
LM2_API lm2_r4_f32 lm2_r4_from_center_extents_f32(lm2_v4_f32 center, lm2_v4_f32 extents);
LM2_API lm2_r4_f32 lm2_r4_from_center_size_f32(lm2_v4_f32 center, lm2_v4_f32 size);
LM2_API lm2_r4_f32 lm2_r4_from_position_size_f32(lm2_v4_f32 position, lm2_v4_f32 size);
LM2_API lm2_r4_f32 lm2_r4_zero_f32(void);

// Operations
LM2_API lm2_r4_f32 lm2_r4_normalize_f32(lm2_r4_f32 r);
LM2_API lm2_r4_f32 lm2_r4_translate_f32(lm2_r4_f32 r, lm2_v4_f32 offset);
LM2_API lm2_r4_f32 lm2_r4_scale_f32(lm2_r4_f32 r, float factor);
LM2_API lm2_r4_f32 lm2_r4_expand_f32(lm2_r4_f32 r, float amount);

// Arithmetic operators
LM2_API lm2_r4_f32 lm2_r4_add_f32(lm2_r4_f32 a, lm2_r4_f32 b);
LM2_API lm2_r4_f32 lm2_r4_add_s_f32(lm2_r4_f32 r, float s);
LM2_API lm2_r4_f32 lm2_r4_add_v_f32(lm2_r4_f32 r, lm2_v4_f32 v);
LM2_API lm2_r4_f32 lm2_r4_sub_f32(lm2_r4_f32 a, lm2_r4_f32 b);
LM2_API lm2_r4_f32 lm2_r4_sub_s_f32(lm2_r4_f32 r, float s);
LM2_API lm2_r4_f32 lm2_r4_sub_v_f32(lm2_r4_f32 r, lm2_v4_f32 v);
LM2_API lm2_r4_f32 lm2_r4_mul_f32(lm2_r4_f32 a, lm2_r4_f32 b);
LM2_API lm2_r4_f32 lm2_r4_mul_s_f32(lm2_r4_f32 r, float s);
LM2_API lm2_r4_f32 lm2_r4_mul_v_f32(lm2_r4_f32 r, lm2_v4_f32 v);
LM2_API lm2_r4_f32 lm2_r4_div_f32(lm2_r4_f32 a, lm2_r4_f32 b);
LM2_API lm2_r4_f32 lm2_r4_div_s_f32(lm2_r4_f32 r, float s);
LM2_API lm2_r4_f32 lm2_r4_div_v_f32(lm2_r4_f32 r, lm2_v4_f32 v);
LM2_API lm2_r4_f32 lm2_r4_mod_f32(lm2_r4_f32 a, lm2_r4_f32 b);
LM2_API lm2_r4_f32 lm2_r4_mod_s_f32(lm2_r4_f32 r, float s);
LM2_API lm2_r4_f32 lm2_r4_mod_v_f32(lm2_r4_f32 r, lm2_v4_f32 v);

// Scalar function forwards
LM2_API lm2_r4_f32 lm2_r4_floor_f32(lm2_r4_f32 a);
LM2_API lm2_r4_f32 lm2_r4_ceil_f32(lm2_r4_f32 a);
LM2_API lm2_r4_f32 lm2_r4_round_f32(lm2_r4_f32 a);
LM2_API lm2_r4_f32 lm2_r4_trunc_f32(lm2_r4_f32 a);
LM2_API lm2_r4_f32 lm2_r4_abs_f32(lm2_r4_f32 a);
LM2_API lm2_r4_f32 lm2_r4_floor_multiple_f32(lm2_r4_f32 a, lm2_r4_f32 b);
LM2_API lm2_r4_f32 lm2_r4_ceil_multiple_f32(lm2_r4_f32 a, lm2_r4_f32 b);
LM2_API lm2_r4_f32 lm2_r4_round_multiple_f32(lm2_r4_f32 a, lm2_r4_f32 b);
LM2_API lm2_r4_f32 lm2_r4_trunc_multiple_f32(lm2_r4_f32 a, lm2_r4_f32 b);
LM2_API lm2_r4_f32 lm2_r4_min_f32(lm2_r4_f32 a, lm2_r4_f32 b);
LM2_API lm2_r4_f32 lm2_r4_max_f32(lm2_r4_f32 a, lm2_r4_f32 b);
LM2_API lm2_r4_f32 lm2_r4_clamp_f32(lm2_r4_f32 a, lm2_r4_f32 b, lm2_r4_f32 c);
LM2_API lm2_r4_f32 lm2_r4_lerp_f32(lm2_r4_f32 a, lm2_r4_f32 b, lm2_r4_f32 c);

// Queries
LM2_API lm2_r4_f32 lm2_r4_union_f32(lm2_r4_f32 a, lm2_r4_f32 b);
LM2_API lm2_r4_f32 lm2_r4_intersection_f32(lm2_r4_f32 a, lm2_r4_f32 b);
LM2_API lm2_v4_f32 lm2_r4_size_f32(lm2_r4_f32 r);
LM2_API lm2_v4_f32 lm2_r4_extents_f32(lm2_r4_f32 r);
LM2_API lm2_v4_f32 lm2_r4_center_f32(lm2_r4_f32 r);
LM2_API int lm2_r4_contains_point_f32(lm2_r4_f32 r, lm2_v4_f32 point);
LM2_API int lm2_r4_overlaps_f32(lm2_r4_f32 a, lm2_r4_f32 b);
LM2_API float lm2_r4_hypervolume_f32(lm2_r4_f32 r);

// ---------------------------------------------------------------------------
// lm2_r4_i64 - 4D Range (64-bit signed integer)
// ---------------------------------------------------------------------------
typedef union lm2_r4_i64 {
  lm2_v4_i64 e[2];
  int64_t e2[8];
  struct {
    lm2_v4_i64 min;
    lm2_v4_i64 max;
  };
  _LM2_SUBSCRIPT_OP(lm2_v4_i64, 2)
} lm2_r4_i64;

// Constructors
LM2_API lm2_r4_i64 lm2_r4_from_min_max_i64(lm2_v4_i64 min, lm2_v4_i64 max);
LM2_API lm2_r4_i64 lm2_r4_from_center_extents_i64(lm2_v4_i64 center, lm2_v4_i64 extents);
LM2_API lm2_r4_i64 lm2_r4_from_center_size_i64(lm2_v4_i64 center, lm2_v4_i64 size);
LM2_API lm2_r4_i64 lm2_r4_from_position_size_i64(lm2_v4_i64 position, lm2_v4_i64 size);
LM2_API lm2_r4_i64 lm2_r4_zero_i64(void);

// Operations
LM2_API lm2_r4_i64 lm2_r4_normalize_i64(lm2_r4_i64 r);
LM2_API lm2_r4_i64 lm2_r4_translate_i64(lm2_r4_i64 r, lm2_v4_i64 offset);
LM2_API lm2_r4_i64 lm2_r4_scale_i64(lm2_r4_i64 r, int64_t factor);
LM2_API lm2_r4_i64 lm2_r4_expand_i64(lm2_r4_i64 r, int64_t amount);

// Arithmetic operators
LM2_API lm2_r4_i64 lm2_r4_add_i64(lm2_r4_i64 a, lm2_r4_i64 b);
LM2_API lm2_r4_i64 lm2_r4_add_s_i64(lm2_r4_i64 r, int64_t s);
LM2_API lm2_r4_i64 lm2_r4_add_v_i64(lm2_r4_i64 r, lm2_v4_i64 v);
LM2_API lm2_r4_i64 lm2_r4_sub_i64(lm2_r4_i64 a, lm2_r4_i64 b);
LM2_API lm2_r4_i64 lm2_r4_sub_s_i64(lm2_r4_i64 r, int64_t s);
LM2_API lm2_r4_i64 lm2_r4_sub_v_i64(lm2_r4_i64 r, lm2_v4_i64 v);
LM2_API lm2_r4_i64 lm2_r4_mul_i64(lm2_r4_i64 a, lm2_r4_i64 b);
LM2_API lm2_r4_i64 lm2_r4_mul_s_i64(lm2_r4_i64 r, int64_t s);
LM2_API lm2_r4_i64 lm2_r4_mul_v_i64(lm2_r4_i64 r, lm2_v4_i64 v);
LM2_API lm2_r4_i64 lm2_r4_div_i64(lm2_r4_i64 a, lm2_r4_i64 b);
LM2_API lm2_r4_i64 lm2_r4_div_s_i64(lm2_r4_i64 r, int64_t s);
LM2_API lm2_r4_i64 lm2_r4_div_v_i64(lm2_r4_i64 r, lm2_v4_i64 v);
LM2_API lm2_r4_i64 lm2_r4_mod_i64(lm2_r4_i64 a, lm2_r4_i64 b);
LM2_API lm2_r4_i64 lm2_r4_mod_s_i64(lm2_r4_i64 r, int64_t s);
LM2_API lm2_r4_i64 lm2_r4_mod_v_i64(lm2_r4_i64 r, lm2_v4_i64 v);

// Scalar function forwards
LM2_API lm2_r4_i64 lm2_r4_floor_i64(lm2_r4_i64 a);
LM2_API lm2_r4_i64 lm2_r4_ceil_i64(lm2_r4_i64 a);
LM2_API lm2_r4_i64 lm2_r4_round_i64(lm2_r4_i64 a);
LM2_API lm2_r4_i64 lm2_r4_trunc_i64(lm2_r4_i64 a);
LM2_API lm2_r4_i64 lm2_r4_abs_i64(lm2_r4_i64 a);
LM2_API lm2_r4_i64 lm2_r4_floor_multiple_i64(lm2_r4_i64 a, lm2_r4_i64 b);
LM2_API lm2_r4_i64 lm2_r4_ceil_multiple_i64(lm2_r4_i64 a, lm2_r4_i64 b);
LM2_API lm2_r4_i64 lm2_r4_round_multiple_i64(lm2_r4_i64 a, lm2_r4_i64 b);
LM2_API lm2_r4_i64 lm2_r4_trunc_multiple_i64(lm2_r4_i64 a, lm2_r4_i64 b);
LM2_API lm2_r4_i64 lm2_r4_min_i64(lm2_r4_i64 a, lm2_r4_i64 b);
LM2_API lm2_r4_i64 lm2_r4_max_i64(lm2_r4_i64 a, lm2_r4_i64 b);
LM2_API lm2_r4_i64 lm2_r4_clamp_i64(lm2_r4_i64 a, lm2_r4_i64 b, lm2_r4_i64 c);
LM2_API lm2_r4_i64 lm2_r4_lerp_i64(lm2_r4_i64 a, lm2_r4_i64 b, lm2_r4_i64 c);

// Queries
LM2_API lm2_r4_i64 lm2_r4_union_i64(lm2_r4_i64 a, lm2_r4_i64 b);
LM2_API lm2_r4_i64 lm2_r4_intersection_i64(lm2_r4_i64 a, lm2_r4_i64 b);
LM2_API lm2_v4_i64 lm2_r4_size_i64(lm2_r4_i64 r);
LM2_API lm2_v4_i64 lm2_r4_extents_i64(lm2_r4_i64 r);
LM2_API lm2_v4_i64 lm2_r4_center_i64(lm2_r4_i64 r);
LM2_API int lm2_r4_contains_point_i64(lm2_r4_i64 r, lm2_v4_i64 point);
LM2_API int lm2_r4_overlaps_i64(lm2_r4_i64 a, lm2_r4_i64 b);
LM2_API int64_t lm2_r4_hypervolume_i64(lm2_r4_i64 r);

// ---------------------------------------------------------------------------
// lm2_r4_i32 - 4D Range (32-bit signed integer)
// ---------------------------------------------------------------------------
typedef union lm2_r4_i32 {
  lm2_v4_i32 e[2];
  int32_t e2[8];
  struct {
    lm2_v4_i32 min;
    lm2_v4_i32 max;
  };
  _LM2_SUBSCRIPT_OP(lm2_v4_i32, 2)
} lm2_r4_i32;

// Constructors
LM2_API lm2_r4_i32 lm2_r4_from_min_max_i32(lm2_v4_i32 min, lm2_v4_i32 max);
LM2_API lm2_r4_i32 lm2_r4_from_center_extents_i32(lm2_v4_i32 center, lm2_v4_i32 extents);
LM2_API lm2_r4_i32 lm2_r4_from_center_size_i32(lm2_v4_i32 center, lm2_v4_i32 size);
LM2_API lm2_r4_i32 lm2_r4_from_position_size_i32(lm2_v4_i32 position, lm2_v4_i32 size);
LM2_API lm2_r4_i32 lm2_r4_zero_i32(void);

// Operations
LM2_API lm2_r4_i32 lm2_r4_normalize_i32(lm2_r4_i32 r);
LM2_API lm2_r4_i32 lm2_r4_translate_i32(lm2_r4_i32 r, lm2_v4_i32 offset);
LM2_API lm2_r4_i32 lm2_r4_scale_i32(lm2_r4_i32 r, int32_t factor);
LM2_API lm2_r4_i32 lm2_r4_expand_i32(lm2_r4_i32 r, int32_t amount);

// Arithmetic operators
LM2_API lm2_r4_i32 lm2_r4_add_i32(lm2_r4_i32 a, lm2_r4_i32 b);
LM2_API lm2_r4_i32 lm2_r4_add_s_i32(lm2_r4_i32 r, int32_t s);
LM2_API lm2_r4_i32 lm2_r4_add_v_i32(lm2_r4_i32 r, lm2_v4_i32 v);
LM2_API lm2_r4_i32 lm2_r4_sub_i32(lm2_r4_i32 a, lm2_r4_i32 b);
LM2_API lm2_r4_i32 lm2_r4_sub_s_i32(lm2_r4_i32 r, int32_t s);
LM2_API lm2_r4_i32 lm2_r4_sub_v_i32(lm2_r4_i32 r, lm2_v4_i32 v);
LM2_API lm2_r4_i32 lm2_r4_mul_i32(lm2_r4_i32 a, lm2_r4_i32 b);
LM2_API lm2_r4_i32 lm2_r4_mul_s_i32(lm2_r4_i32 r, int32_t s);
LM2_API lm2_r4_i32 lm2_r4_mul_v_i32(lm2_r4_i32 r, lm2_v4_i32 v);
LM2_API lm2_r4_i32 lm2_r4_div_i32(lm2_r4_i32 a, lm2_r4_i32 b);
LM2_API lm2_r4_i32 lm2_r4_div_s_i32(lm2_r4_i32 r, int32_t s);
LM2_API lm2_r4_i32 lm2_r4_div_v_i32(lm2_r4_i32 r, lm2_v4_i32 v);
LM2_API lm2_r4_i32 lm2_r4_mod_i32(lm2_r4_i32 a, lm2_r4_i32 b);
LM2_API lm2_r4_i32 lm2_r4_mod_s_i32(lm2_r4_i32 r, int32_t s);
LM2_API lm2_r4_i32 lm2_r4_mod_v_i32(lm2_r4_i32 r, lm2_v4_i32 v);

// Scalar function forwards
LM2_API lm2_r4_i32 lm2_r4_floor_i32(lm2_r4_i32 a);
LM2_API lm2_r4_i32 lm2_r4_ceil_i32(lm2_r4_i32 a);
LM2_API lm2_r4_i32 lm2_r4_round_i32(lm2_r4_i32 a);
LM2_API lm2_r4_i32 lm2_r4_trunc_i32(lm2_r4_i32 a);
LM2_API lm2_r4_i32 lm2_r4_abs_i32(lm2_r4_i32 a);
LM2_API lm2_r4_i32 lm2_r4_floor_multiple_i32(lm2_r4_i32 a, lm2_r4_i32 b);
LM2_API lm2_r4_i32 lm2_r4_ceil_multiple_i32(lm2_r4_i32 a, lm2_r4_i32 b);
LM2_API lm2_r4_i32 lm2_r4_round_multiple_i32(lm2_r4_i32 a, lm2_r4_i32 b);
LM2_API lm2_r4_i32 lm2_r4_trunc_multiple_i32(lm2_r4_i32 a, lm2_r4_i32 b);
LM2_API lm2_r4_i32 lm2_r4_min_i32(lm2_r4_i32 a, lm2_r4_i32 b);
LM2_API lm2_r4_i32 lm2_r4_max_i32(lm2_r4_i32 a, lm2_r4_i32 b);
LM2_API lm2_r4_i32 lm2_r4_clamp_i32(lm2_r4_i32 a, lm2_r4_i32 b, lm2_r4_i32 c);
LM2_API lm2_r4_i32 lm2_r4_lerp_i32(lm2_r4_i32 a, lm2_r4_i32 b, lm2_r4_i32 c);

// Queries
LM2_API lm2_r4_i32 lm2_r4_union_i32(lm2_r4_i32 a, lm2_r4_i32 b);
LM2_API lm2_r4_i32 lm2_r4_intersection_i32(lm2_r4_i32 a, lm2_r4_i32 b);
LM2_API lm2_v4_i32 lm2_r4_size_i32(lm2_r4_i32 r);
LM2_API lm2_v4_i32 lm2_r4_extents_i32(lm2_r4_i32 r);
LM2_API lm2_v4_i32 lm2_r4_center_i32(lm2_r4_i32 r);
LM2_API int lm2_r4_contains_point_i32(lm2_r4_i32 r, lm2_v4_i32 point);
LM2_API int lm2_r4_overlaps_i32(lm2_r4_i32 a, lm2_r4_i32 b);
LM2_API int32_t lm2_r4_hypervolume_i32(lm2_r4_i32 r);

// ---------------------------------------------------------------------------
// lm2_r4_i16 - 4D Range (16-bit signed integer)
// ---------------------------------------------------------------------------
typedef union lm2_r4_i16 {
  lm2_v4_i16 e[2];
  int16_t e2[8];
  struct {
    lm2_v4_i16 min;
    lm2_v4_i16 max;
  };
  _LM2_SUBSCRIPT_OP(lm2_v4_i16, 2)
} lm2_r4_i16;

// Constructors
LM2_API lm2_r4_i16 lm2_r4_from_min_max_i16(lm2_v4_i16 min, lm2_v4_i16 max);
LM2_API lm2_r4_i16 lm2_r4_from_center_extents_i16(lm2_v4_i16 center, lm2_v4_i16 extents);
LM2_API lm2_r4_i16 lm2_r4_from_center_size_i16(lm2_v4_i16 center, lm2_v4_i16 size);
LM2_API lm2_r4_i16 lm2_r4_from_position_size_i16(lm2_v4_i16 position, lm2_v4_i16 size);
LM2_API lm2_r4_i16 lm2_r4_zero_i16(void);

// Operations
LM2_API lm2_r4_i16 lm2_r4_normalize_i16(lm2_r4_i16 r);
LM2_API lm2_r4_i16 lm2_r4_translate_i16(lm2_r4_i16 r, lm2_v4_i16 offset);
LM2_API lm2_r4_i16 lm2_r4_scale_i16(lm2_r4_i16 r, int16_t factor);
LM2_API lm2_r4_i16 lm2_r4_expand_i16(lm2_r4_i16 r, int16_t amount);

// Arithmetic operators
LM2_API lm2_r4_i16 lm2_r4_add_i16(lm2_r4_i16 a, lm2_r4_i16 b);
LM2_API lm2_r4_i16 lm2_r4_add_s_i16(lm2_r4_i16 r, int16_t s);
LM2_API lm2_r4_i16 lm2_r4_add_v_i16(lm2_r4_i16 r, lm2_v4_i16 v);
LM2_API lm2_r4_i16 lm2_r4_sub_i16(lm2_r4_i16 a, lm2_r4_i16 b);
LM2_API lm2_r4_i16 lm2_r4_sub_s_i16(lm2_r4_i16 r, int16_t s);
LM2_API lm2_r4_i16 lm2_r4_sub_v_i16(lm2_r4_i16 r, lm2_v4_i16 v);
LM2_API lm2_r4_i16 lm2_r4_mul_i16(lm2_r4_i16 a, lm2_r4_i16 b);
LM2_API lm2_r4_i16 lm2_r4_mul_s_i16(lm2_r4_i16 r, int16_t s);
LM2_API lm2_r4_i16 lm2_r4_mul_v_i16(lm2_r4_i16 r, lm2_v4_i16 v);
LM2_API lm2_r4_i16 lm2_r4_div_i16(lm2_r4_i16 a, lm2_r4_i16 b);
LM2_API lm2_r4_i16 lm2_r4_div_s_i16(lm2_r4_i16 r, int16_t s);
LM2_API lm2_r4_i16 lm2_r4_div_v_i16(lm2_r4_i16 r, lm2_v4_i16 v);
LM2_API lm2_r4_i16 lm2_r4_mod_i16(lm2_r4_i16 a, lm2_r4_i16 b);
LM2_API lm2_r4_i16 lm2_r4_mod_s_i16(lm2_r4_i16 r, int16_t s);
LM2_API lm2_r4_i16 lm2_r4_mod_v_i16(lm2_r4_i16 r, lm2_v4_i16 v);

// Scalar function forwards
LM2_API lm2_r4_i16 lm2_r4_floor_i16(lm2_r4_i16 a);
LM2_API lm2_r4_i16 lm2_r4_ceil_i16(lm2_r4_i16 a);
LM2_API lm2_r4_i16 lm2_r4_round_i16(lm2_r4_i16 a);
LM2_API lm2_r4_i16 lm2_r4_trunc_i16(lm2_r4_i16 a);
LM2_API lm2_r4_i16 lm2_r4_abs_i16(lm2_r4_i16 a);
LM2_API lm2_r4_i16 lm2_r4_floor_multiple_i16(lm2_r4_i16 a, lm2_r4_i16 b);
LM2_API lm2_r4_i16 lm2_r4_ceil_multiple_i16(lm2_r4_i16 a, lm2_r4_i16 b);
LM2_API lm2_r4_i16 lm2_r4_round_multiple_i16(lm2_r4_i16 a, lm2_r4_i16 b);
LM2_API lm2_r4_i16 lm2_r4_trunc_multiple_i16(lm2_r4_i16 a, lm2_r4_i16 b);
LM2_API lm2_r4_i16 lm2_r4_min_i16(lm2_r4_i16 a, lm2_r4_i16 b);
LM2_API lm2_r4_i16 lm2_r4_max_i16(lm2_r4_i16 a, lm2_r4_i16 b);
LM2_API lm2_r4_i16 lm2_r4_clamp_i16(lm2_r4_i16 a, lm2_r4_i16 b, lm2_r4_i16 c);
LM2_API lm2_r4_i16 lm2_r4_lerp_i16(lm2_r4_i16 a, lm2_r4_i16 b, lm2_r4_i16 c);

// Queries
LM2_API lm2_r4_i16 lm2_r4_union_i16(lm2_r4_i16 a, lm2_r4_i16 b);
LM2_API lm2_r4_i16 lm2_r4_intersection_i16(lm2_r4_i16 a, lm2_r4_i16 b);
LM2_API lm2_v4_i16 lm2_r4_size_i16(lm2_r4_i16 r);
LM2_API lm2_v4_i16 lm2_r4_extents_i16(lm2_r4_i16 r);
LM2_API lm2_v4_i16 lm2_r4_center_i16(lm2_r4_i16 r);
LM2_API int lm2_r4_contains_point_i16(lm2_r4_i16 r, lm2_v4_i16 point);
LM2_API int lm2_r4_overlaps_i16(lm2_r4_i16 a, lm2_r4_i16 b);
LM2_API int16_t lm2_r4_hypervolume_i16(lm2_r4_i16 r);

// ---------------------------------------------------------------------------
// lm2_r4_i8 - 4D Range (8-bit signed integer)
// ---------------------------------------------------------------------------
typedef union lm2_r4_i8 {
  lm2_v4_i8 e[2];
  int8_t e2[8];
  struct {
    lm2_v4_i8 min;
    lm2_v4_i8 max;
  };
  _LM2_SUBSCRIPT_OP(lm2_v4_i8, 2)
} lm2_r4_i8;

// Constructors
LM2_API lm2_r4_i8 lm2_r4_from_min_max_i8(lm2_v4_i8 min, lm2_v4_i8 max);
LM2_API lm2_r4_i8 lm2_r4_from_center_extents_i8(lm2_v4_i8 center, lm2_v4_i8 extents);
LM2_API lm2_r4_i8 lm2_r4_from_center_size_i8(lm2_v4_i8 center, lm2_v4_i8 size);
LM2_API lm2_r4_i8 lm2_r4_from_position_size_i8(lm2_v4_i8 position, lm2_v4_i8 size);
LM2_API lm2_r4_i8 lm2_r4_zero_i8(void);

// Operations
LM2_API lm2_r4_i8 lm2_r4_normalize_i8(lm2_r4_i8 r);
LM2_API lm2_r4_i8 lm2_r4_translate_i8(lm2_r4_i8 r, lm2_v4_i8 offset);
LM2_API lm2_r4_i8 lm2_r4_scale_i8(lm2_r4_i8 r, int8_t factor);
LM2_API lm2_r4_i8 lm2_r4_expand_i8(lm2_r4_i8 r, int8_t amount);

// Arithmetic operators
LM2_API lm2_r4_i8 lm2_r4_add_i8(lm2_r4_i8 a, lm2_r4_i8 b);
LM2_API lm2_r4_i8 lm2_r4_add_s_i8(lm2_r4_i8 r, int8_t s);
LM2_API lm2_r4_i8 lm2_r4_add_v_i8(lm2_r4_i8 r, lm2_v4_i8 v);
LM2_API lm2_r4_i8 lm2_r4_sub_i8(lm2_r4_i8 a, lm2_r4_i8 b);
LM2_API lm2_r4_i8 lm2_r4_sub_s_i8(lm2_r4_i8 r, int8_t s);
LM2_API lm2_r4_i8 lm2_r4_sub_v_i8(lm2_r4_i8 r, lm2_v4_i8 v);
LM2_API lm2_r4_i8 lm2_r4_mul_i8(lm2_r4_i8 a, lm2_r4_i8 b);
LM2_API lm2_r4_i8 lm2_r4_mul_s_i8(lm2_r4_i8 r, int8_t s);
LM2_API lm2_r4_i8 lm2_r4_mul_v_i8(lm2_r4_i8 r, lm2_v4_i8 v);
LM2_API lm2_r4_i8 lm2_r4_div_i8(lm2_r4_i8 a, lm2_r4_i8 b);
LM2_API lm2_r4_i8 lm2_r4_div_s_i8(lm2_r4_i8 r, int8_t s);
LM2_API lm2_r4_i8 lm2_r4_div_v_i8(lm2_r4_i8 r, lm2_v4_i8 v);
LM2_API lm2_r4_i8 lm2_r4_mod_i8(lm2_r4_i8 a, lm2_r4_i8 b);
LM2_API lm2_r4_i8 lm2_r4_mod_s_i8(lm2_r4_i8 r, int8_t s);
LM2_API lm2_r4_i8 lm2_r4_mod_v_i8(lm2_r4_i8 r, lm2_v4_i8 v);

// Scalar function forwards
LM2_API lm2_r4_i8 lm2_r4_floor_i8(lm2_r4_i8 a);
LM2_API lm2_r4_i8 lm2_r4_ceil_i8(lm2_r4_i8 a);
LM2_API lm2_r4_i8 lm2_r4_round_i8(lm2_r4_i8 a);
LM2_API lm2_r4_i8 lm2_r4_trunc_i8(lm2_r4_i8 a);
LM2_API lm2_r4_i8 lm2_r4_abs_i8(lm2_r4_i8 a);
LM2_API lm2_r4_i8 lm2_r4_floor_multiple_i8(lm2_r4_i8 a, lm2_r4_i8 b);
LM2_API lm2_r4_i8 lm2_r4_ceil_multiple_i8(lm2_r4_i8 a, lm2_r4_i8 b);
LM2_API lm2_r4_i8 lm2_r4_round_multiple_i8(lm2_r4_i8 a, lm2_r4_i8 b);
LM2_API lm2_r4_i8 lm2_r4_trunc_multiple_i8(lm2_r4_i8 a, lm2_r4_i8 b);
LM2_API lm2_r4_i8 lm2_r4_min_i8(lm2_r4_i8 a, lm2_r4_i8 b);
LM2_API lm2_r4_i8 lm2_r4_max_i8(lm2_r4_i8 a, lm2_r4_i8 b);
LM2_API lm2_r4_i8 lm2_r4_clamp_i8(lm2_r4_i8 a, lm2_r4_i8 b, lm2_r4_i8 c);
LM2_API lm2_r4_i8 lm2_r4_lerp_i8(lm2_r4_i8 a, lm2_r4_i8 b, lm2_r4_i8 c);

// Queries
LM2_API lm2_r4_i8 lm2_r4_union_i8(lm2_r4_i8 a, lm2_r4_i8 b);
LM2_API lm2_r4_i8 lm2_r4_intersection_i8(lm2_r4_i8 a, lm2_r4_i8 b);
LM2_API lm2_v4_i8 lm2_r4_size_i8(lm2_r4_i8 r);
LM2_API lm2_v4_i8 lm2_r4_extents_i8(lm2_r4_i8 r);
LM2_API lm2_v4_i8 lm2_r4_center_i8(lm2_r4_i8 r);
LM2_API int lm2_r4_contains_point_i8(lm2_r4_i8 r, lm2_v4_i8 point);
LM2_API int lm2_r4_overlaps_i8(lm2_r4_i8 a, lm2_r4_i8 b);
LM2_API int8_t lm2_r4_hypervolume_i8(lm2_r4_i8 r);

// ---------------------------------------------------------------------------
// lm2_r4_u64 - 4D Range (64-bit unsigned integer)
// ---------------------------------------------------------------------------
typedef union lm2_r4_u64 {
  lm2_v4_u64 e[2];
  uint64_t e2[8];
  struct {
    lm2_v4_u64 min;
    lm2_v4_u64 max;
  };
  _LM2_SUBSCRIPT_OP(lm2_v4_u64, 2)
} lm2_r4_u64;

// Constructors
LM2_API lm2_r4_u64 lm2_r4_from_min_max_u64(lm2_v4_u64 min, lm2_v4_u64 max);
LM2_API lm2_r4_u64 lm2_r4_from_center_extents_u64(lm2_v4_u64 center, lm2_v4_u64 extents);
LM2_API lm2_r4_u64 lm2_r4_from_center_size_u64(lm2_v4_u64 center, lm2_v4_u64 size);
LM2_API lm2_r4_u64 lm2_r4_from_position_size_u64(lm2_v4_u64 position, lm2_v4_u64 size);
LM2_API lm2_r4_u64 lm2_r4_zero_u64(void);

// Operations
LM2_API lm2_r4_u64 lm2_r4_normalize_u64(lm2_r4_u64 r);
LM2_API lm2_r4_u64 lm2_r4_translate_u64(lm2_r4_u64 r, lm2_v4_u64 offset);
LM2_API lm2_r4_u64 lm2_r4_scale_u64(lm2_r4_u64 r, uint64_t factor);
LM2_API lm2_r4_u64 lm2_r4_expand_u64(lm2_r4_u64 r, uint64_t amount);

// Arithmetic operators
LM2_API lm2_r4_u64 lm2_r4_add_u64(lm2_r4_u64 a, lm2_r4_u64 b);
LM2_API lm2_r4_u64 lm2_r4_add_s_u64(lm2_r4_u64 r, uint64_t s);
LM2_API lm2_r4_u64 lm2_r4_add_v_u64(lm2_r4_u64 r, lm2_v4_u64 v);
LM2_API lm2_r4_u64 lm2_r4_sub_u64(lm2_r4_u64 a, lm2_r4_u64 b);
LM2_API lm2_r4_u64 lm2_r4_sub_s_u64(lm2_r4_u64 r, uint64_t s);
LM2_API lm2_r4_u64 lm2_r4_sub_v_u64(lm2_r4_u64 r, lm2_v4_u64 v);
LM2_API lm2_r4_u64 lm2_r4_mul_u64(lm2_r4_u64 a, lm2_r4_u64 b);
LM2_API lm2_r4_u64 lm2_r4_mul_s_u64(lm2_r4_u64 r, uint64_t s);
LM2_API lm2_r4_u64 lm2_r4_mul_v_u64(lm2_r4_u64 r, lm2_v4_u64 v);
LM2_API lm2_r4_u64 lm2_r4_div_u64(lm2_r4_u64 a, lm2_r4_u64 b);
LM2_API lm2_r4_u64 lm2_r4_div_s_u64(lm2_r4_u64 r, uint64_t s);
LM2_API lm2_r4_u64 lm2_r4_div_v_u64(lm2_r4_u64 r, lm2_v4_u64 v);
LM2_API lm2_r4_u64 lm2_r4_mod_u64(lm2_r4_u64 a, lm2_r4_u64 b);
LM2_API lm2_r4_u64 lm2_r4_mod_s_u64(lm2_r4_u64 r, uint64_t s);
LM2_API lm2_r4_u64 lm2_r4_mod_v_u64(lm2_r4_u64 r, lm2_v4_u64 v);

// Scalar function forwards
LM2_API lm2_r4_u64 lm2_r4_floor_u64(lm2_r4_u64 a);
LM2_API lm2_r4_u64 lm2_r4_ceil_u64(lm2_r4_u64 a);
LM2_API lm2_r4_u64 lm2_r4_round_u64(lm2_r4_u64 a);
LM2_API lm2_r4_u64 lm2_r4_trunc_u64(lm2_r4_u64 a);
LM2_API lm2_r4_u64 lm2_r4_abs_u64(lm2_r4_u64 a);
LM2_API lm2_r4_u64 lm2_r4_floor_multiple_u64(lm2_r4_u64 a, lm2_r4_u64 b);
LM2_API lm2_r4_u64 lm2_r4_ceil_multiple_u64(lm2_r4_u64 a, lm2_r4_u64 b);
LM2_API lm2_r4_u64 lm2_r4_round_multiple_u64(lm2_r4_u64 a, lm2_r4_u64 b);
LM2_API lm2_r4_u64 lm2_r4_trunc_multiple_u64(lm2_r4_u64 a, lm2_r4_u64 b);
LM2_API lm2_r4_u64 lm2_r4_min_u64(lm2_r4_u64 a, lm2_r4_u64 b);
LM2_API lm2_r4_u64 lm2_r4_max_u64(lm2_r4_u64 a, lm2_r4_u64 b);
LM2_API lm2_r4_u64 lm2_r4_clamp_u64(lm2_r4_u64 a, lm2_r4_u64 b, lm2_r4_u64 c);
LM2_API lm2_r4_u64 lm2_r4_lerp_u64(lm2_r4_u64 a, lm2_r4_u64 b, lm2_r4_u64 c);

// Queries
LM2_API lm2_r4_u64 lm2_r4_union_u64(lm2_r4_u64 a, lm2_r4_u64 b);
LM2_API lm2_r4_u64 lm2_r4_intersection_u64(lm2_r4_u64 a, lm2_r4_u64 b);
LM2_API lm2_v4_u64 lm2_r4_size_u64(lm2_r4_u64 r);
LM2_API lm2_v4_u64 lm2_r4_extents_u64(lm2_r4_u64 r);
LM2_API lm2_v4_u64 lm2_r4_center_u64(lm2_r4_u64 r);
LM2_API int lm2_r4_contains_point_u64(lm2_r4_u64 r, lm2_v4_u64 point);
LM2_API int lm2_r4_overlaps_u64(lm2_r4_u64 a, lm2_r4_u64 b);
LM2_API uint64_t lm2_r4_hypervolume_u64(lm2_r4_u64 r);

// ---------------------------------------------------------------------------
// lm2_r4_u32 - 4D Range (32-bit unsigned integer)
// ---------------------------------------------------------------------------
typedef union lm2_r4_u32 {
  lm2_v4_u32 e[2];
  uint32_t e2[8];
  struct {
    lm2_v4_u32 min;
    lm2_v4_u32 max;
  };
  _LM2_SUBSCRIPT_OP(lm2_v4_u32, 2)
} lm2_r4_u32;

// Constructors
LM2_API lm2_r4_u32 lm2_r4_from_min_max_u32(lm2_v4_u32 min, lm2_v4_u32 max);
LM2_API lm2_r4_u32 lm2_r4_from_center_extents_u32(lm2_v4_u32 center, lm2_v4_u32 extents);
LM2_API lm2_r4_u32 lm2_r4_from_center_size_u32(lm2_v4_u32 center, lm2_v4_u32 size);
LM2_API lm2_r4_u32 lm2_r4_from_position_size_u32(lm2_v4_u32 position, lm2_v4_u32 size);
LM2_API lm2_r4_u32 lm2_r4_zero_u32(void);

// Operations
LM2_API lm2_r4_u32 lm2_r4_normalize_u32(lm2_r4_u32 r);
LM2_API lm2_r4_u32 lm2_r4_translate_u32(lm2_r4_u32 r, lm2_v4_u32 offset);
LM2_API lm2_r4_u32 lm2_r4_scale_u32(lm2_r4_u32 r, uint32_t factor);
LM2_API lm2_r4_u32 lm2_r4_expand_u32(lm2_r4_u32 r, uint32_t amount);

// Arithmetic operators
LM2_API lm2_r4_u32 lm2_r4_add_u32(lm2_r4_u32 a, lm2_r4_u32 b);
LM2_API lm2_r4_u32 lm2_r4_add_s_u32(lm2_r4_u32 r, uint32_t s);
LM2_API lm2_r4_u32 lm2_r4_add_v_u32(lm2_r4_u32 r, lm2_v4_u32 v);
LM2_API lm2_r4_u32 lm2_r4_sub_u32(lm2_r4_u32 a, lm2_r4_u32 b);
LM2_API lm2_r4_u32 lm2_r4_sub_s_u32(lm2_r4_u32 r, uint32_t s);
LM2_API lm2_r4_u32 lm2_r4_sub_v_u32(lm2_r4_u32 r, lm2_v4_u32 v);
LM2_API lm2_r4_u32 lm2_r4_mul_u32(lm2_r4_u32 a, lm2_r4_u32 b);
LM2_API lm2_r4_u32 lm2_r4_mul_s_u32(lm2_r4_u32 r, uint32_t s);
LM2_API lm2_r4_u32 lm2_r4_mul_v_u32(lm2_r4_u32 r, lm2_v4_u32 v);
LM2_API lm2_r4_u32 lm2_r4_div_u32(lm2_r4_u32 a, lm2_r4_u32 b);
LM2_API lm2_r4_u32 lm2_r4_div_s_u32(lm2_r4_u32 r, uint32_t s);
LM2_API lm2_r4_u32 lm2_r4_div_v_u32(lm2_r4_u32 r, lm2_v4_u32 v);
LM2_API lm2_r4_u32 lm2_r4_mod_u32(lm2_r4_u32 a, lm2_r4_u32 b);
LM2_API lm2_r4_u32 lm2_r4_mod_s_u32(lm2_r4_u32 r, uint32_t s);
LM2_API lm2_r4_u32 lm2_r4_mod_v_u32(lm2_r4_u32 r, lm2_v4_u32 v);

// Scalar function forwards
LM2_API lm2_r4_u32 lm2_r4_floor_u32(lm2_r4_u32 a);
LM2_API lm2_r4_u32 lm2_r4_ceil_u32(lm2_r4_u32 a);
LM2_API lm2_r4_u32 lm2_r4_round_u32(lm2_r4_u32 a);
LM2_API lm2_r4_u32 lm2_r4_trunc_u32(lm2_r4_u32 a);
LM2_API lm2_r4_u32 lm2_r4_abs_u32(lm2_r4_u32 a);
LM2_API lm2_r4_u32 lm2_r4_floor_multiple_u32(lm2_r4_u32 a, lm2_r4_u32 b);
LM2_API lm2_r4_u32 lm2_r4_ceil_multiple_u32(lm2_r4_u32 a, lm2_r4_u32 b);
LM2_API lm2_r4_u32 lm2_r4_round_multiple_u32(lm2_r4_u32 a, lm2_r4_u32 b);
LM2_API lm2_r4_u32 lm2_r4_trunc_multiple_u32(lm2_r4_u32 a, lm2_r4_u32 b);
LM2_API lm2_r4_u32 lm2_r4_min_u32(lm2_r4_u32 a, lm2_r4_u32 b);
LM2_API lm2_r4_u32 lm2_r4_max_u32(lm2_r4_u32 a, lm2_r4_u32 b);
LM2_API lm2_r4_u32 lm2_r4_clamp_u32(lm2_r4_u32 a, lm2_r4_u32 b, lm2_r4_u32 c);
LM2_API lm2_r4_u32 lm2_r4_lerp_u32(lm2_r4_u32 a, lm2_r4_u32 b, lm2_r4_u32 c);

// Queries
LM2_API lm2_r4_u32 lm2_r4_union_u32(lm2_r4_u32 a, lm2_r4_u32 b);
LM2_API lm2_r4_u32 lm2_r4_intersection_u32(lm2_r4_u32 a, lm2_r4_u32 b);
LM2_API lm2_v4_u32 lm2_r4_size_u32(lm2_r4_u32 r);
LM2_API lm2_v4_u32 lm2_r4_extents_u32(lm2_r4_u32 r);
LM2_API lm2_v4_u32 lm2_r4_center_u32(lm2_r4_u32 r);
LM2_API int lm2_r4_contains_point_u32(lm2_r4_u32 r, lm2_v4_u32 point);
LM2_API int lm2_r4_overlaps_u32(lm2_r4_u32 a, lm2_r4_u32 b);
LM2_API uint32_t lm2_r4_hypervolume_u32(lm2_r4_u32 r);

// ---------------------------------------------------------------------------
// lm2_r4_u16 - 4D Range (16-bit unsigned integer)
// ---------------------------------------------------------------------------
typedef union lm2_r4_u16 {
  lm2_v4_u16 e[2];
  uint16_t e2[8];
  struct {
    lm2_v4_u16 min;
    lm2_v4_u16 max;
  };
  _LM2_SUBSCRIPT_OP(lm2_v4_u16, 2)
} lm2_r4_u16;

// Constructors
LM2_API lm2_r4_u16 lm2_r4_from_min_max_u16(lm2_v4_u16 min, lm2_v4_u16 max);
LM2_API lm2_r4_u16 lm2_r4_from_center_extents_u16(lm2_v4_u16 center, lm2_v4_u16 extents);
LM2_API lm2_r4_u16 lm2_r4_from_center_size_u16(lm2_v4_u16 center, lm2_v4_u16 size);
LM2_API lm2_r4_u16 lm2_r4_from_position_size_u16(lm2_v4_u16 position, lm2_v4_u16 size);
LM2_API lm2_r4_u16 lm2_r4_zero_u16(void);

// Operations
LM2_API lm2_r4_u16 lm2_r4_normalize_u16(lm2_r4_u16 r);
LM2_API lm2_r4_u16 lm2_r4_translate_u16(lm2_r4_u16 r, lm2_v4_u16 offset);
LM2_API lm2_r4_u16 lm2_r4_scale_u16(lm2_r4_u16 r, uint16_t factor);
LM2_API lm2_r4_u16 lm2_r4_expand_u16(lm2_r4_u16 r, uint16_t amount);

// Arithmetic operators
LM2_API lm2_r4_u16 lm2_r4_add_u16(lm2_r4_u16 a, lm2_r4_u16 b);
LM2_API lm2_r4_u16 lm2_r4_add_s_u16(lm2_r4_u16 r, uint16_t s);
LM2_API lm2_r4_u16 lm2_r4_add_v_u16(lm2_r4_u16 r, lm2_v4_u16 v);
LM2_API lm2_r4_u16 lm2_r4_sub_u16(lm2_r4_u16 a, lm2_r4_u16 b);
LM2_API lm2_r4_u16 lm2_r4_sub_s_u16(lm2_r4_u16 r, uint16_t s);
LM2_API lm2_r4_u16 lm2_r4_sub_v_u16(lm2_r4_u16 r, lm2_v4_u16 v);
LM2_API lm2_r4_u16 lm2_r4_mul_u16(lm2_r4_u16 a, lm2_r4_u16 b);
LM2_API lm2_r4_u16 lm2_r4_mul_s_u16(lm2_r4_u16 r, uint16_t s);
LM2_API lm2_r4_u16 lm2_r4_mul_v_u16(lm2_r4_u16 r, lm2_v4_u16 v);
LM2_API lm2_r4_u16 lm2_r4_div_u16(lm2_r4_u16 a, lm2_r4_u16 b);
LM2_API lm2_r4_u16 lm2_r4_div_s_u16(lm2_r4_u16 r, uint16_t s);
LM2_API lm2_r4_u16 lm2_r4_div_v_u16(lm2_r4_u16 r, lm2_v4_u16 v);
LM2_API lm2_r4_u16 lm2_r4_mod_u16(lm2_r4_u16 a, lm2_r4_u16 b);
LM2_API lm2_r4_u16 lm2_r4_mod_s_u16(lm2_r4_u16 r, uint16_t s);
LM2_API lm2_r4_u16 lm2_r4_mod_v_u16(lm2_r4_u16 r, lm2_v4_u16 v);

// Scalar function forwards
LM2_API lm2_r4_u16 lm2_r4_floor_u16(lm2_r4_u16 a);
LM2_API lm2_r4_u16 lm2_r4_ceil_u16(lm2_r4_u16 a);
LM2_API lm2_r4_u16 lm2_r4_round_u16(lm2_r4_u16 a);
LM2_API lm2_r4_u16 lm2_r4_trunc_u16(lm2_r4_u16 a);
LM2_API lm2_r4_u16 lm2_r4_abs_u16(lm2_r4_u16 a);
LM2_API lm2_r4_u16 lm2_r4_floor_multiple_u16(lm2_r4_u16 a, lm2_r4_u16 b);
LM2_API lm2_r4_u16 lm2_r4_ceil_multiple_u16(lm2_r4_u16 a, lm2_r4_u16 b);
LM2_API lm2_r4_u16 lm2_r4_round_multiple_u16(lm2_r4_u16 a, lm2_r4_u16 b);
LM2_API lm2_r4_u16 lm2_r4_trunc_multiple_u16(lm2_r4_u16 a, lm2_r4_u16 b);
LM2_API lm2_r4_u16 lm2_r4_min_u16(lm2_r4_u16 a, lm2_r4_u16 b);
LM2_API lm2_r4_u16 lm2_r4_max_u16(lm2_r4_u16 a, lm2_r4_u16 b);
LM2_API lm2_r4_u16 lm2_r4_clamp_u16(lm2_r4_u16 a, lm2_r4_u16 b, lm2_r4_u16 c);
LM2_API lm2_r4_u16 lm2_r4_lerp_u16(lm2_r4_u16 a, lm2_r4_u16 b, lm2_r4_u16 c);

// Queries
LM2_API lm2_r4_u16 lm2_r4_union_u16(lm2_r4_u16 a, lm2_r4_u16 b);
LM2_API lm2_r4_u16 lm2_r4_intersection_u16(lm2_r4_u16 a, lm2_r4_u16 b);
LM2_API lm2_v4_u16 lm2_r4_size_u16(lm2_r4_u16 r);
LM2_API lm2_v4_u16 lm2_r4_extents_u16(lm2_r4_u16 r);
LM2_API lm2_v4_u16 lm2_r4_center_u16(lm2_r4_u16 r);
LM2_API int lm2_r4_contains_point_u16(lm2_r4_u16 r, lm2_v4_u16 point);
LM2_API int lm2_r4_overlaps_u16(lm2_r4_u16 a, lm2_r4_u16 b);
LM2_API uint16_t lm2_r4_hypervolume_u16(lm2_r4_u16 r);

// ---------------------------------------------------------------------------
// lm2_r4_u8 - 4D Range (8-bit unsigned integer)
// ---------------------------------------------------------------------------
typedef union lm2_r4_u8 {
  lm2_v4_u8 e[2];
  uint8_t e2[8];
  struct {
    lm2_v4_u8 min;
    lm2_v4_u8 max;
  };
  _LM2_SUBSCRIPT_OP(lm2_v4_u8, 2)
} lm2_r4_u8;

// Constructors
LM2_API lm2_r4_u8 lm2_r4_from_min_max_u8(lm2_v4_u8 min, lm2_v4_u8 max);
LM2_API lm2_r4_u8 lm2_r4_from_center_extents_u8(lm2_v4_u8 center, lm2_v4_u8 extents);
LM2_API lm2_r4_u8 lm2_r4_from_center_size_u8(lm2_v4_u8 center, lm2_v4_u8 size);
LM2_API lm2_r4_u8 lm2_r4_from_position_size_u8(lm2_v4_u8 position, lm2_v4_u8 size);
LM2_API lm2_r4_u8 lm2_r4_zero_u8(void);

// Operations
LM2_API lm2_r4_u8 lm2_r4_normalize_u8(lm2_r4_u8 r);
LM2_API lm2_r4_u8 lm2_r4_translate_u8(lm2_r4_u8 r, lm2_v4_u8 offset);
LM2_API lm2_r4_u8 lm2_r4_scale_u8(lm2_r4_u8 r, uint8_t factor);
LM2_API lm2_r4_u8 lm2_r4_expand_u8(lm2_r4_u8 r, uint8_t amount);

// Arithmetic operators
LM2_API lm2_r4_u8 lm2_r4_add_u8(lm2_r4_u8 a, lm2_r4_u8 b);
LM2_API lm2_r4_u8 lm2_r4_add_s_u8(lm2_r4_u8 r, uint8_t s);
LM2_API lm2_r4_u8 lm2_r4_add_v_u8(lm2_r4_u8 r, lm2_v4_u8 v);
LM2_API lm2_r4_u8 lm2_r4_sub_u8(lm2_r4_u8 a, lm2_r4_u8 b);
LM2_API lm2_r4_u8 lm2_r4_sub_s_u8(lm2_r4_u8 r, uint8_t s);
LM2_API lm2_r4_u8 lm2_r4_sub_v_u8(lm2_r4_u8 r, lm2_v4_u8 v);
LM2_API lm2_r4_u8 lm2_r4_mul_u8(lm2_r4_u8 a, lm2_r4_u8 b);
LM2_API lm2_r4_u8 lm2_r4_mul_s_u8(lm2_r4_u8 r, uint8_t s);
LM2_API lm2_r4_u8 lm2_r4_mul_v_u8(lm2_r4_u8 r, lm2_v4_u8 v);
LM2_API lm2_r4_u8 lm2_r4_div_u8(lm2_r4_u8 a, lm2_r4_u8 b);
LM2_API lm2_r4_u8 lm2_r4_div_s_u8(lm2_r4_u8 r, uint8_t s);
LM2_API lm2_r4_u8 lm2_r4_div_v_u8(lm2_r4_u8 r, lm2_v4_u8 v);
LM2_API lm2_r4_u8 lm2_r4_mod_u8(lm2_r4_u8 a, lm2_r4_u8 b);
LM2_API lm2_r4_u8 lm2_r4_mod_s_u8(lm2_r4_u8 r, uint8_t s);
LM2_API lm2_r4_u8 lm2_r4_mod_v_u8(lm2_r4_u8 r, lm2_v4_u8 v);

// Scalar function forwards
LM2_API lm2_r4_u8 lm2_r4_floor_u8(lm2_r4_u8 a);
LM2_API lm2_r4_u8 lm2_r4_ceil_u8(lm2_r4_u8 a);
LM2_API lm2_r4_u8 lm2_r4_round_u8(lm2_r4_u8 a);
LM2_API lm2_r4_u8 lm2_r4_trunc_u8(lm2_r4_u8 a);
LM2_API lm2_r4_u8 lm2_r4_abs_u8(lm2_r4_u8 a);
LM2_API lm2_r4_u8 lm2_r4_floor_multiple_u8(lm2_r4_u8 a, lm2_r4_u8 b);
LM2_API lm2_r4_u8 lm2_r4_ceil_multiple_u8(lm2_r4_u8 a, lm2_r4_u8 b);
LM2_API lm2_r4_u8 lm2_r4_round_multiple_u8(lm2_r4_u8 a, lm2_r4_u8 b);
LM2_API lm2_r4_u8 lm2_r4_trunc_multiple_u8(lm2_r4_u8 a, lm2_r4_u8 b);
LM2_API lm2_r4_u8 lm2_r4_min_u8(lm2_r4_u8 a, lm2_r4_u8 b);
LM2_API lm2_r4_u8 lm2_r4_max_u8(lm2_r4_u8 a, lm2_r4_u8 b);
LM2_API lm2_r4_u8 lm2_r4_clamp_u8(lm2_r4_u8 a, lm2_r4_u8 b, lm2_r4_u8 c);
LM2_API lm2_r4_u8 lm2_r4_lerp_u8(lm2_r4_u8 a, lm2_r4_u8 b, lm2_r4_u8 c);

// Queries
LM2_API lm2_r4_u8 lm2_r4_union_u8(lm2_r4_u8 a, lm2_r4_u8 b);
LM2_API lm2_r4_u8 lm2_r4_intersection_u8(lm2_r4_u8 a, lm2_r4_u8 b);
LM2_API lm2_v4_u8 lm2_r4_size_u8(lm2_r4_u8 r);
LM2_API lm2_v4_u8 lm2_r4_extents_u8(lm2_r4_u8 r);
LM2_API lm2_v4_u8 lm2_r4_center_u8(lm2_r4_u8 r);
LM2_API int lm2_r4_contains_point_u8(lm2_r4_u8 r, lm2_v4_u8 point);
LM2_API int lm2_r4_overlaps_u8(lm2_r4_u8 a, lm2_r4_u8 b);
LM2_API uint8_t lm2_r4_hypervolume_u8(lm2_r4_u8 r);

// Default range4 type (float-based)
typedef lm2_r4_f32 lm2_r4;

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// C++ operator overloads and constructors (must be outside extern "C")
#ifndef LM2_NO_CPP_OPERATORS
#  include "lm2_range_operators.h"
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4_f64, f64, lm2_v4_f64)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4_f32, f32, lm2_v4_f32)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4_i64, i64, lm2_v4_i64)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4_i32, i32, lm2_v4_i32)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4_i16, i16, lm2_v4_i16)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4_i8, i8, lm2_v4_i8)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4_u64, u64, lm2_v4_u64)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4_u32, u32, lm2_v4_u32)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4_u16, u16, lm2_v4_u16)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4_u8, u8, lm2_v4_u8)
#endif
