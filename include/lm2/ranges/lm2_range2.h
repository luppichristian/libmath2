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

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// 2D Range (AABB) Type Definitions
// =============================================================================
// A range2 represents a 2D axis-aligned bounding box (AABB) or rectangle
// with minimum and maximum points.

// ---------------------------------------------------------------------------
// lm2_r2_f64 - 2D Range (double precision)
// ---------------------------------------------------------------------------

typedef union lm2_r2_f64 {
  lm2_v2_f64 e[2];
  double e2[4];
  struct {
    lm2_v2_f64 min;
    lm2_v2_f64 max;
  };
  _LM2_SUBSCRIPT_OP(lm2_v2_f64, 2)
} lm2_r2_f64;

LM2_API lm2_r2_f64 lm2_r2_from_min_max_f64(lm2_v2_f64 min, lm2_v2_f64 max);
LM2_API lm2_r2_f64 lm2_r2_from_center_extents_f64(lm2_v2_f64 center, lm2_v2_f64 extents);
LM2_API lm2_r2_f64 lm2_r2_from_center_size_f64(lm2_v2_f64 center, lm2_v2_f64 size);
LM2_API lm2_r2_f64 lm2_r2_from_position_size_f64(lm2_v2_f64 position, lm2_v2_f64 size);
LM2_API lm2_r2_f64 lm2_r2_zero_f64(void);
LM2_API lm2_r2_f64 lm2_r2_add_f64(lm2_r2_f64 a, lm2_r2_f64 b);
LM2_API lm2_r2_f64 lm2_r2_add_s_f64(lm2_r2_f64 r, double s);
LM2_API lm2_r2_f64 lm2_r2_add_v_f64(lm2_r2_f64 r, lm2_v2_f64 v);
LM2_API lm2_r2_f64 lm2_r2_sub_f64(lm2_r2_f64 a, lm2_r2_f64 b);
LM2_API lm2_r2_f64 lm2_r2_sub_s_f64(lm2_r2_f64 r, double s);
LM2_API lm2_r2_f64 lm2_r2_sub_v_f64(lm2_r2_f64 r, lm2_v2_f64 v);
LM2_API lm2_r2_f64 lm2_r2_mul_f64(lm2_r2_f64 a, lm2_r2_f64 b);
LM2_API lm2_r2_f64 lm2_r2_mul_s_f64(lm2_r2_f64 r, double s);
LM2_API lm2_r2_f64 lm2_r2_mul_v_f64(lm2_r2_f64 r, lm2_v2_f64 v);
LM2_API lm2_r2_f64 lm2_r2_div_f64(lm2_r2_f64 a, lm2_r2_f64 b);
LM2_API lm2_r2_f64 lm2_r2_div_s_f64(lm2_r2_f64 r, double s);
LM2_API lm2_r2_f64 lm2_r2_div_v_f64(lm2_r2_f64 r, lm2_v2_f64 v);
LM2_API lm2_r2_f64 lm2_r2_mod_f64(lm2_r2_f64 a, lm2_r2_f64 b);
LM2_API lm2_r2_f64 lm2_r2_mod_s_f64(lm2_r2_f64 r, double s);
LM2_API lm2_r2_f64 lm2_r2_mod_v_f64(lm2_r2_f64 r, lm2_v2_f64 v);
LM2_API lm2_r2_f64 lm2_r2_floor_f64(lm2_r2_f64 a);
LM2_API lm2_r2_f64 lm2_r2_ceil_f64(lm2_r2_f64 a);
LM2_API lm2_r2_f64 lm2_r2_round_f64(lm2_r2_f64 a);
LM2_API lm2_r2_f64 lm2_r2_trunc_f64(lm2_r2_f64 a);
LM2_API lm2_r2_f64 lm2_r2_abs_f64(lm2_r2_f64 a);
LM2_API lm2_r2_f64 lm2_r2_sign_f64(lm2_r2_f64 a);
LM2_API lm2_r2_f64 lm2_r2_sign0_f64(lm2_r2_f64 a);
LM2_API lm2_r2_f64 lm2_r2_floor_multiple_f64(lm2_r2_f64 a, lm2_r2_f64 b);
LM2_API lm2_r2_f64 lm2_r2_ceil_multiple_f64(lm2_r2_f64 a, lm2_r2_f64 b);
LM2_API lm2_r2_f64 lm2_r2_round_multiple_f64(lm2_r2_f64 a, lm2_r2_f64 b);
LM2_API lm2_r2_f64 lm2_r2_trunc_multiple_f64(lm2_r2_f64 a, lm2_r2_f64 b);
LM2_API lm2_r2_f64 lm2_r2_min_f64(lm2_r2_f64 a, lm2_r2_f64 b);
LM2_API lm2_r2_f64 lm2_r2_min_abs_f64(lm2_r2_f64 a, lm2_r2_f64 b);
LM2_API lm2_r2_f64 lm2_r2_max_f64(lm2_r2_f64 a, lm2_r2_f64 b);
LM2_API lm2_r2_f64 lm2_r2_max_abs_f64(lm2_r2_f64 a, lm2_r2_f64 b);
LM2_API lm2_r2_f64 lm2_r2_clamp_f64(lm2_r2_f64 a, lm2_r2_f64 b, lm2_r2_f64 c);
LM2_API lm2_r2_f64 lm2_r2_saturate_f64(lm2_r2_f64 value);
LM2_API lm2_r2_f64 lm2_r2_lerp_f64(lm2_r2_f64 a, lm2_r2_f64 b, lm2_r2_f64 c);
LM2_API lm2_r2_f64 lm2_r2_smoothstep_f64(lm2_r2_f64 edge0, lm2_r2_f64 x, lm2_r2_f64 edge1);
LM2_API lm2_r2_f64 lm2_r2_alpha_f64(lm2_r2_f64 a, lm2_r2_f64 value, lm2_r2_f64 b);
LM2_API lm2_r2_f64 lm2_r2_fract_f64(lm2_r2_f64 a);
LM2_API lm2_r2_f64 lm2_r2_pow_f64(lm2_r2_f64 base, lm2_r2_f64 exponent);
LM2_API lm2_r2_f64 lm2_r2_sqrt_f64(lm2_r2_f64 a);
LM2_API lm2_r2_f64 lm2_r2_union_f64(lm2_r2_f64 a, lm2_r2_f64 b);
LM2_API lm2_r2_f64 lm2_r2_intersection_f64(lm2_r2_f64 a, lm2_r2_f64 b);
LM2_API lm2_v2_f64 lm2_r2_size_f64(lm2_r2_f64 r);
LM2_API lm2_v2_f64 lm2_r2_extents_f64(lm2_r2_f64 r);
LM2_API lm2_v2_f64 lm2_r2_center_f64(lm2_r2_f64 r);
LM2_API int lm2_r2_contains_point_f64(lm2_r2_f64 r, lm2_v2_f64 point);
LM2_API int lm2_r2_overlaps_f64(lm2_r2_f64 a, lm2_r2_f64 b);
LM2_API double lm2_r2_area_f64(lm2_r2_f64 r);

// ---------------------------------------------------------------------------
// lm2_r2_f32 - 2D Range (single precision)
// ---------------------------------------------------------------------------

typedef union lm2_r2_f32 {
  lm2_v2_f32 e[2];
  float e2[4];
  struct {
    lm2_v2_f32 min;
    lm2_v2_f32 max;
  };
  _LM2_SUBSCRIPT_OP(lm2_v2_f32, 2)
} lm2_r2_f32;

LM2_API lm2_r2_f32 lm2_r2_from_min_max_f32(lm2_v2_f32 min, lm2_v2_f32 max);
LM2_API lm2_r2_f32 lm2_r2_from_center_extents_f32(lm2_v2_f32 center, lm2_v2_f32 extents);
LM2_API lm2_r2_f32 lm2_r2_from_center_size_f32(lm2_v2_f32 center, lm2_v2_f32 size);
LM2_API lm2_r2_f32 lm2_r2_from_position_size_f32(lm2_v2_f32 position, lm2_v2_f32 size);
LM2_API lm2_r2_f32 lm2_r2_zero_f32(void);
LM2_API lm2_r2_f32 lm2_r2_add_f32(lm2_r2_f32 a, lm2_r2_f32 b);
LM2_API lm2_r2_f32 lm2_r2_add_s_f32(lm2_r2_f32 r, float s);
LM2_API lm2_r2_f32 lm2_r2_add_v_f32(lm2_r2_f32 r, lm2_v2_f32 v);
LM2_API lm2_r2_f32 lm2_r2_sub_f32(lm2_r2_f32 a, lm2_r2_f32 b);
LM2_API lm2_r2_f32 lm2_r2_sub_s_f32(lm2_r2_f32 r, float s);
LM2_API lm2_r2_f32 lm2_r2_sub_v_f32(lm2_r2_f32 r, lm2_v2_f32 v);
LM2_API lm2_r2_f32 lm2_r2_mul_f32(lm2_r2_f32 a, lm2_r2_f32 b);
LM2_API lm2_r2_f32 lm2_r2_mul_s_f32(lm2_r2_f32 r, float s);
LM2_API lm2_r2_f32 lm2_r2_mul_v_f32(lm2_r2_f32 r, lm2_v2_f32 v);
LM2_API lm2_r2_f32 lm2_r2_div_f32(lm2_r2_f32 a, lm2_r2_f32 b);
LM2_API lm2_r2_f32 lm2_r2_div_s_f32(lm2_r2_f32 r, float s);
LM2_API lm2_r2_f32 lm2_r2_div_v_f32(lm2_r2_f32 r, lm2_v2_f32 v);
LM2_API lm2_r2_f32 lm2_r2_mod_f32(lm2_r2_f32 a, lm2_r2_f32 b);
LM2_API lm2_r2_f32 lm2_r2_mod_s_f32(lm2_r2_f32 r, float s);
LM2_API lm2_r2_f32 lm2_r2_mod_v_f32(lm2_r2_f32 r, lm2_v2_f32 v);
LM2_API lm2_r2_f32 lm2_r2_floor_f32(lm2_r2_f32 a);
LM2_API lm2_r2_f32 lm2_r2_ceil_f32(lm2_r2_f32 a);
LM2_API lm2_r2_f32 lm2_r2_round_f32(lm2_r2_f32 a);
LM2_API lm2_r2_f32 lm2_r2_trunc_f32(lm2_r2_f32 a);
LM2_API lm2_r2_f32 lm2_r2_abs_f32(lm2_r2_f32 a);
LM2_API lm2_r2_f32 lm2_r2_sign_f32(lm2_r2_f32 a);
LM2_API lm2_r2_f32 lm2_r2_sign0_f32(lm2_r2_f32 a);
LM2_API lm2_r2_f32 lm2_r2_floor_multiple_f32(lm2_r2_f32 a, lm2_r2_f32 b);
LM2_API lm2_r2_f32 lm2_r2_ceil_multiple_f32(lm2_r2_f32 a, lm2_r2_f32 b);
LM2_API lm2_r2_f32 lm2_r2_round_multiple_f32(lm2_r2_f32 a, lm2_r2_f32 b);
LM2_API lm2_r2_f32 lm2_r2_trunc_multiple_f32(lm2_r2_f32 a, lm2_r2_f32 b);
LM2_API lm2_r2_f32 lm2_r2_min_f32(lm2_r2_f32 a, lm2_r2_f32 b);
LM2_API lm2_r2_f32 lm2_r2_min_abs_f32(lm2_r2_f32 a, lm2_r2_f32 b);
LM2_API lm2_r2_f32 lm2_r2_max_f32(lm2_r2_f32 a, lm2_r2_f32 b);
LM2_API lm2_r2_f32 lm2_r2_max_abs_f32(lm2_r2_f32 a, lm2_r2_f32 b);
LM2_API lm2_r2_f32 lm2_r2_clamp_f32(lm2_r2_f32 a, lm2_r2_f32 b, lm2_r2_f32 c);
LM2_API lm2_r2_f32 lm2_r2_saturate_f32(lm2_r2_f32 value);
LM2_API lm2_r2_f32 lm2_r2_lerp_f32(lm2_r2_f32 a, lm2_r2_f32 b, lm2_r2_f32 c);
LM2_API lm2_r2_f32 lm2_r2_smoothstep_f32(lm2_r2_f32 edge0, lm2_r2_f32 x, lm2_r2_f32 edge1);
LM2_API lm2_r2_f32 lm2_r2_alpha_f32(lm2_r2_f32 a, lm2_r2_f32 value, lm2_r2_f32 b);
LM2_API lm2_r2_f32 lm2_r2_fract_f32(lm2_r2_f32 a);
LM2_API lm2_r2_f32 lm2_r2_pow_f32(lm2_r2_f32 base, lm2_r2_f32 exponent);
LM2_API lm2_r2_f32 lm2_r2_sqrt_f32(lm2_r2_f32 a);
LM2_API lm2_r2_f32 lm2_r2_union_f32(lm2_r2_f32 a, lm2_r2_f32 b);
LM2_API lm2_r2_f32 lm2_r2_intersection_f32(lm2_r2_f32 a, lm2_r2_f32 b);
LM2_API lm2_v2_f32 lm2_r2_size_f32(lm2_r2_f32 r);
LM2_API lm2_v2_f32 lm2_r2_extents_f32(lm2_r2_f32 r);
LM2_API lm2_v2_f32 lm2_r2_center_f32(lm2_r2_f32 r);
LM2_API int lm2_r2_contains_point_f32(lm2_r2_f32 r, lm2_v2_f32 point);
LM2_API int lm2_r2_overlaps_f32(lm2_r2_f32 a, lm2_r2_f32 b);
LM2_API float lm2_r2_area_f32(lm2_r2_f32 r);

// ---------------------------------------------------------------------------
// lm2_r2_i64 - 2D Range (64-bit signed integer)
// ---------------------------------------------------------------------------
typedef union lm2_r2_i64 {
  lm2_v2_i64 e[2];
  int64_t e2[4];
  struct {
    lm2_v2_i64 min;
    lm2_v2_i64 max;
  };
  _LM2_SUBSCRIPT_OP(lm2_v2_i64, 2)
} lm2_r2_i64;

LM2_API lm2_r2_i64 lm2_r2_from_min_max_i64(lm2_v2_i64 min, lm2_v2_i64 max);
LM2_API lm2_r2_i64 lm2_r2_from_center_extents_i64(lm2_v2_i64 center, lm2_v2_i64 extents);
LM2_API lm2_r2_i64 lm2_r2_from_center_size_i64(lm2_v2_i64 center, lm2_v2_i64 size);
LM2_API lm2_r2_i64 lm2_r2_from_position_size_i64(lm2_v2_i64 position, lm2_v2_i64 size);
LM2_API lm2_r2_i64 lm2_r2_zero_i64(void);
LM2_API lm2_r2_i64 lm2_r2_add_i64(lm2_r2_i64 a, lm2_r2_i64 b);
LM2_API lm2_r2_i64 lm2_r2_add_s_i64(lm2_r2_i64 r, int64_t s);
LM2_API lm2_r2_i64 lm2_r2_add_v_i64(lm2_r2_i64 r, lm2_v2_i64 v);
LM2_API lm2_r2_i64 lm2_r2_sub_i64(lm2_r2_i64 a, lm2_r2_i64 b);
LM2_API lm2_r2_i64 lm2_r2_sub_s_i64(lm2_r2_i64 r, int64_t s);
LM2_API lm2_r2_i64 lm2_r2_sub_v_i64(lm2_r2_i64 r, lm2_v2_i64 v);
LM2_API lm2_r2_i64 lm2_r2_mul_i64(lm2_r2_i64 a, lm2_r2_i64 b);
LM2_API lm2_r2_i64 lm2_r2_mul_s_i64(lm2_r2_i64 r, int64_t s);
LM2_API lm2_r2_i64 lm2_r2_mul_v_i64(lm2_r2_i64 r, lm2_v2_i64 v);
LM2_API lm2_r2_i64 lm2_r2_div_i64(lm2_r2_i64 a, lm2_r2_i64 b);
LM2_API lm2_r2_i64 lm2_r2_div_s_i64(lm2_r2_i64 r, int64_t s);
LM2_API lm2_r2_i64 lm2_r2_div_v_i64(lm2_r2_i64 r, lm2_v2_i64 v);
LM2_API lm2_r2_i64 lm2_r2_mod_i64(lm2_r2_i64 a, lm2_r2_i64 b);
LM2_API lm2_r2_i64 lm2_r2_mod_s_i64(lm2_r2_i64 r, int64_t s);
LM2_API lm2_r2_i64 lm2_r2_mod_v_i64(lm2_r2_i64 r, lm2_v2_i64 v);
LM2_API lm2_r2_i64 lm2_r2_abs_i64(lm2_r2_i64 a);
LM2_API lm2_r2_i64 lm2_r2_sign_i64(lm2_r2_i64 a);
LM2_API lm2_r2_i64 lm2_r2_sign0_i64(lm2_r2_i64 a);
LM2_API lm2_r2_i64 lm2_r2_min_i64(lm2_r2_i64 a, lm2_r2_i64 b);
LM2_API lm2_r2_i64 lm2_r2_min_abs_i64(lm2_r2_i64 a, lm2_r2_i64 b);
LM2_API lm2_r2_i64 lm2_r2_max_i64(lm2_r2_i64 a, lm2_r2_i64 b);
LM2_API lm2_r2_i64 lm2_r2_max_abs_i64(lm2_r2_i64 a, lm2_r2_i64 b);
LM2_API lm2_r2_i64 lm2_r2_clamp_i64(lm2_r2_i64 a, lm2_r2_i64 b, lm2_r2_i64 c);
LM2_API lm2_r2_i64 lm2_r2_union_i64(lm2_r2_i64 a, lm2_r2_i64 b);
LM2_API lm2_r2_i64 lm2_r2_intersection_i64(lm2_r2_i64 a, lm2_r2_i64 b);
LM2_API lm2_v2_i64 lm2_r2_size_i64(lm2_r2_i64 r);
LM2_API lm2_v2_i64 lm2_r2_extents_i64(lm2_r2_i64 r);
LM2_API lm2_v2_i64 lm2_r2_center_i64(lm2_r2_i64 r);
LM2_API int lm2_r2_contains_point_i64(lm2_r2_i64 r, lm2_v2_i64 point);
LM2_API int lm2_r2_overlaps_i64(lm2_r2_i64 a, lm2_r2_i64 b);
LM2_API int64_t lm2_r2_area_i64(lm2_r2_i64 r);

// ---------------------------------------------------------------------------
// lm2_r2_i32 - 2D Range (32-bit signed integer)
// ---------------------------------------------------------------------------

typedef union lm2_r2_i32 {
  lm2_v2_i32 e[2];
  int32_t e2[4];
  struct {
    lm2_v2_i32 min;
    lm2_v2_i32 max;
  };
  _LM2_SUBSCRIPT_OP(lm2_v2_i32, 2)
} lm2_r2_i32;

LM2_API lm2_r2_i32 lm2_r2_from_min_max_i32(lm2_v2_i32 min, lm2_v2_i32 max);
LM2_API lm2_r2_i32 lm2_r2_from_center_extents_i32(lm2_v2_i32 center, lm2_v2_i32 extents);
LM2_API lm2_r2_i32 lm2_r2_from_center_size_i32(lm2_v2_i32 center, lm2_v2_i32 size);
LM2_API lm2_r2_i32 lm2_r2_from_position_size_i32(lm2_v2_i32 position, lm2_v2_i32 size);
LM2_API lm2_r2_i32 lm2_r2_zero_i32(void);
LM2_API lm2_r2_i32 lm2_r2_add_i32(lm2_r2_i32 a, lm2_r2_i32 b);
LM2_API lm2_r2_i32 lm2_r2_add_s_i32(lm2_r2_i32 r, int32_t s);
LM2_API lm2_r2_i32 lm2_r2_add_v_i32(lm2_r2_i32 r, lm2_v2_i32 v);
LM2_API lm2_r2_i32 lm2_r2_sub_i32(lm2_r2_i32 a, lm2_r2_i32 b);
LM2_API lm2_r2_i32 lm2_r2_sub_s_i32(lm2_r2_i32 r, int32_t s);
LM2_API lm2_r2_i32 lm2_r2_sub_v_i32(lm2_r2_i32 r, lm2_v2_i32 v);
LM2_API lm2_r2_i32 lm2_r2_mul_i32(lm2_r2_i32 a, lm2_r2_i32 b);
LM2_API lm2_r2_i32 lm2_r2_mul_s_i32(lm2_r2_i32 r, int32_t s);
LM2_API lm2_r2_i32 lm2_r2_mul_v_i32(lm2_r2_i32 r, lm2_v2_i32 v);
LM2_API lm2_r2_i32 lm2_r2_div_i32(lm2_r2_i32 a, lm2_r2_i32 b);
LM2_API lm2_r2_i32 lm2_r2_div_s_i32(lm2_r2_i32 r, int32_t s);
LM2_API lm2_r2_i32 lm2_r2_div_v_i32(lm2_r2_i32 r, lm2_v2_i32 v);
LM2_API lm2_r2_i32 lm2_r2_mod_i32(lm2_r2_i32 a, lm2_r2_i32 b);
LM2_API lm2_r2_i32 lm2_r2_mod_s_i32(lm2_r2_i32 r, int32_t s);
LM2_API lm2_r2_i32 lm2_r2_mod_v_i32(lm2_r2_i32 r, lm2_v2_i32 v);
LM2_API lm2_r2_i32 lm2_r2_abs_i32(lm2_r2_i32 a);
LM2_API lm2_r2_i32 lm2_r2_sign_i32(lm2_r2_i32 a);
LM2_API lm2_r2_i32 lm2_r2_sign0_i32(lm2_r2_i32 a);
LM2_API lm2_r2_i32 lm2_r2_min_i32(lm2_r2_i32 a, lm2_r2_i32 b);
LM2_API lm2_r2_i32 lm2_r2_min_abs_i32(lm2_r2_i32 a, lm2_r2_i32 b);
LM2_API lm2_r2_i32 lm2_r2_max_i32(lm2_r2_i32 a, lm2_r2_i32 b);
LM2_API lm2_r2_i32 lm2_r2_max_abs_i32(lm2_r2_i32 a, lm2_r2_i32 b);
LM2_API lm2_r2_i32 lm2_r2_clamp_i32(lm2_r2_i32 a, lm2_r2_i32 b, lm2_r2_i32 c);
LM2_API lm2_r2_i32 lm2_r2_union_i32(lm2_r2_i32 a, lm2_r2_i32 b);
LM2_API lm2_r2_i32 lm2_r2_intersection_i32(lm2_r2_i32 a, lm2_r2_i32 b);
LM2_API lm2_v2_i32 lm2_r2_size_i32(lm2_r2_i32 r);
LM2_API lm2_v2_i32 lm2_r2_extents_i32(lm2_r2_i32 r);
LM2_API lm2_v2_i32 lm2_r2_center_i32(lm2_r2_i32 r);
LM2_API int lm2_r2_contains_point_i32(lm2_r2_i32 r, lm2_v2_i32 point);
LM2_API int lm2_r2_overlaps_i32(lm2_r2_i32 a, lm2_r2_i32 b);
LM2_API int32_t lm2_r2_area_i32(lm2_r2_i32 r);

// ---------------------------------------------------------------------------
// lm2_r2_i16 - 2D Range (16-bit signed integer)
// ---------------------------------------------------------------------------

typedef union lm2_r2_i16 {
  lm2_v2_i16 e[2];
  int16_t e2[4];
  struct {
    lm2_v2_i16 min;
    lm2_v2_i16 max;
  };
  _LM2_SUBSCRIPT_OP(lm2_v2_i16, 2)
} lm2_r2_i16;

LM2_API lm2_r2_i16 lm2_r2_from_min_max_i16(lm2_v2_i16 min, lm2_v2_i16 max);
LM2_API lm2_r2_i16 lm2_r2_from_center_extents_i16(lm2_v2_i16 center, lm2_v2_i16 extents);
LM2_API lm2_r2_i16 lm2_r2_from_center_size_i16(lm2_v2_i16 center, lm2_v2_i16 size);
LM2_API lm2_r2_i16 lm2_r2_from_position_size_i16(lm2_v2_i16 position, lm2_v2_i16 size);
LM2_API lm2_r2_i16 lm2_r2_zero_i16(void);
LM2_API lm2_r2_i16 lm2_r2_add_i16(lm2_r2_i16 a, lm2_r2_i16 b);
LM2_API lm2_r2_i16 lm2_r2_add_s_i16(lm2_r2_i16 r, int16_t s);
LM2_API lm2_r2_i16 lm2_r2_add_v_i16(lm2_r2_i16 r, lm2_v2_i16 v);
LM2_API lm2_r2_i16 lm2_r2_sub_i16(lm2_r2_i16 a, lm2_r2_i16 b);
LM2_API lm2_r2_i16 lm2_r2_sub_s_i16(lm2_r2_i16 r, int16_t s);
LM2_API lm2_r2_i16 lm2_r2_sub_v_i16(lm2_r2_i16 r, lm2_v2_i16 v);
LM2_API lm2_r2_i16 lm2_r2_mul_i16(lm2_r2_i16 a, lm2_r2_i16 b);
LM2_API lm2_r2_i16 lm2_r2_mul_s_i16(lm2_r2_i16 r, int16_t s);
LM2_API lm2_r2_i16 lm2_r2_mul_v_i16(lm2_r2_i16 r, lm2_v2_i16 v);
LM2_API lm2_r2_i16 lm2_r2_div_i16(lm2_r2_i16 a, lm2_r2_i16 b);
LM2_API lm2_r2_i16 lm2_r2_div_s_i16(lm2_r2_i16 r, int16_t s);
LM2_API lm2_r2_i16 lm2_r2_div_v_i16(lm2_r2_i16 r, lm2_v2_i16 v);
LM2_API lm2_r2_i16 lm2_r2_mod_i16(lm2_r2_i16 a, lm2_r2_i16 b);
LM2_API lm2_r2_i16 lm2_r2_mod_s_i16(lm2_r2_i16 r, int16_t s);
LM2_API lm2_r2_i16 lm2_r2_mod_v_i16(lm2_r2_i16 r, lm2_v2_i16 v);
LM2_API lm2_r2_i16 lm2_r2_abs_i16(lm2_r2_i16 a);
LM2_API lm2_r2_i16 lm2_r2_sign_i16(lm2_r2_i16 a);
LM2_API lm2_r2_i16 lm2_r2_sign0_i16(lm2_r2_i16 a);
LM2_API lm2_r2_i16 lm2_r2_min_i16(lm2_r2_i16 a, lm2_r2_i16 b);
LM2_API lm2_r2_i16 lm2_r2_min_abs_i16(lm2_r2_i16 a, lm2_r2_i16 b);
LM2_API lm2_r2_i16 lm2_r2_max_i16(lm2_r2_i16 a, lm2_r2_i16 b);
LM2_API lm2_r2_i16 lm2_r2_max_abs_i16(lm2_r2_i16 a, lm2_r2_i16 b);
LM2_API lm2_r2_i16 lm2_r2_clamp_i16(lm2_r2_i16 a, lm2_r2_i16 b, lm2_r2_i16 c);
LM2_API lm2_r2_i16 lm2_r2_union_i16(lm2_r2_i16 a, lm2_r2_i16 b);
LM2_API lm2_r2_i16 lm2_r2_intersection_i16(lm2_r2_i16 a, lm2_r2_i16 b);
LM2_API lm2_v2_i16 lm2_r2_size_i16(lm2_r2_i16 r);
LM2_API lm2_v2_i16 lm2_r2_extents_i16(lm2_r2_i16 r);
LM2_API lm2_v2_i16 lm2_r2_center_i16(lm2_r2_i16 r);
LM2_API int lm2_r2_contains_point_i16(lm2_r2_i16 r, lm2_v2_i16 point);
LM2_API int lm2_r2_overlaps_i16(lm2_r2_i16 a, lm2_r2_i16 b);
LM2_API int16_t lm2_r2_area_i16(lm2_r2_i16 r);

// ---------------------------------------------------------------------------
// lm2_r2_i8 - 2D Range (8-bit signed integer)
// ---------------------------------------------------------------------------

typedef union lm2_r2_i8 {
  lm2_v2_i8 e[2];
  int8_t e2[4];
  struct {
    lm2_v2_i8 min;
    lm2_v2_i8 max;
  };
  _LM2_SUBSCRIPT_OP(lm2_v2_i8, 2)
} lm2_r2_i8;

LM2_API lm2_r2_i8 lm2_r2_from_min_max_i8(lm2_v2_i8 min, lm2_v2_i8 max);
LM2_API lm2_r2_i8 lm2_r2_from_center_extents_i8(lm2_v2_i8 center, lm2_v2_i8 extents);
LM2_API lm2_r2_i8 lm2_r2_from_center_size_i8(lm2_v2_i8 center, lm2_v2_i8 size);
LM2_API lm2_r2_i8 lm2_r2_from_position_size_i8(lm2_v2_i8 position, lm2_v2_i8 size);
LM2_API lm2_r2_i8 lm2_r2_zero_i8(void);
LM2_API lm2_r2_i8 lm2_r2_add_i8(lm2_r2_i8 a, lm2_r2_i8 b);
LM2_API lm2_r2_i8 lm2_r2_add_s_i8(lm2_r2_i8 r, int8_t s);
LM2_API lm2_r2_i8 lm2_r2_add_v_i8(lm2_r2_i8 r, lm2_v2_i8 v);
LM2_API lm2_r2_i8 lm2_r2_sub_i8(lm2_r2_i8 a, lm2_r2_i8 b);
LM2_API lm2_r2_i8 lm2_r2_sub_s_i8(lm2_r2_i8 r, int8_t s);
LM2_API lm2_r2_i8 lm2_r2_sub_v_i8(lm2_r2_i8 r, lm2_v2_i8 v);
LM2_API lm2_r2_i8 lm2_r2_mul_i8(lm2_r2_i8 a, lm2_r2_i8 b);
LM2_API lm2_r2_i8 lm2_r2_mul_s_i8(lm2_r2_i8 r, int8_t s);
LM2_API lm2_r2_i8 lm2_r2_mul_v_i8(lm2_r2_i8 r, lm2_v2_i8 v);
LM2_API lm2_r2_i8 lm2_r2_div_i8(lm2_r2_i8 a, lm2_r2_i8 b);
LM2_API lm2_r2_i8 lm2_r2_div_s_i8(lm2_r2_i8 r, int8_t s);
LM2_API lm2_r2_i8 lm2_r2_div_v_i8(lm2_r2_i8 r, lm2_v2_i8 v);
LM2_API lm2_r2_i8 lm2_r2_mod_i8(lm2_r2_i8 a, lm2_r2_i8 b);
LM2_API lm2_r2_i8 lm2_r2_mod_s_i8(lm2_r2_i8 r, int8_t s);
LM2_API lm2_r2_i8 lm2_r2_mod_v_i8(lm2_r2_i8 r, lm2_v2_i8 v);
LM2_API lm2_r2_i8 lm2_r2_abs_i8(lm2_r2_i8 a);
LM2_API lm2_r2_i8 lm2_r2_sign_i8(lm2_r2_i8 a);
LM2_API lm2_r2_i8 lm2_r2_sign0_i8(lm2_r2_i8 a);
LM2_API lm2_r2_i8 lm2_r2_min_i8(lm2_r2_i8 a, lm2_r2_i8 b);
LM2_API lm2_r2_i8 lm2_r2_min_abs_i8(lm2_r2_i8 a, lm2_r2_i8 b);
LM2_API lm2_r2_i8 lm2_r2_max_i8(lm2_r2_i8 a, lm2_r2_i8 b);
LM2_API lm2_r2_i8 lm2_r2_max_abs_i8(lm2_r2_i8 a, lm2_r2_i8 b);
LM2_API lm2_r2_i8 lm2_r2_clamp_i8(lm2_r2_i8 a, lm2_r2_i8 b, lm2_r2_i8 c);
LM2_API lm2_r2_i8 lm2_r2_union_i8(lm2_r2_i8 a, lm2_r2_i8 b);
LM2_API lm2_r2_i8 lm2_r2_intersection_i8(lm2_r2_i8 a, lm2_r2_i8 b);
LM2_API lm2_v2_i8 lm2_r2_size_i8(lm2_r2_i8 r);
LM2_API lm2_v2_i8 lm2_r2_extents_i8(lm2_r2_i8 r);
LM2_API lm2_v2_i8 lm2_r2_center_i8(lm2_r2_i8 r);
LM2_API int lm2_r2_contains_point_i8(lm2_r2_i8 r, lm2_v2_i8 point);
LM2_API int lm2_r2_overlaps_i8(lm2_r2_i8 a, lm2_r2_i8 b);
LM2_API int8_t lm2_r2_area_i8(lm2_r2_i8 r);

// ---------------------------------------------------------------------------
// lm2_r2_u64 - 2D Range (64-bit unsigned integer)
// ---------------------------------------------------------------------------

typedef union lm2_r2_u64 {
  lm2_v2_u64 e[2];
  uint64_t e2[4];
  struct {
    lm2_v2_u64 min;
    lm2_v2_u64 max;
  };
  _LM2_SUBSCRIPT_OP(lm2_v2_u64, 2)
} lm2_r2_u64;

LM2_API lm2_r2_u64 lm2_r2_from_min_max_u64(lm2_v2_u64 min, lm2_v2_u64 max);
LM2_API lm2_r2_u64 lm2_r2_from_center_extents_u64(lm2_v2_u64 center, lm2_v2_u64 extents);
LM2_API lm2_r2_u64 lm2_r2_from_center_size_u64(lm2_v2_u64 center, lm2_v2_u64 size);
LM2_API lm2_r2_u64 lm2_r2_from_position_size_u64(lm2_v2_u64 position, lm2_v2_u64 size);
LM2_API lm2_r2_u64 lm2_r2_zero_u64(void);
LM2_API lm2_r2_u64 lm2_r2_add_u64(lm2_r2_u64 a, lm2_r2_u64 b);
LM2_API lm2_r2_u64 lm2_r2_add_s_u64(lm2_r2_u64 r, uint64_t s);
LM2_API lm2_r2_u64 lm2_r2_add_v_u64(lm2_r2_u64 r, lm2_v2_u64 v);
LM2_API lm2_r2_u64 lm2_r2_sub_u64(lm2_r2_u64 a, lm2_r2_u64 b);
LM2_API lm2_r2_u64 lm2_r2_sub_s_u64(lm2_r2_u64 r, uint64_t s);
LM2_API lm2_r2_u64 lm2_r2_sub_v_u64(lm2_r2_u64 r, lm2_v2_u64 v);
LM2_API lm2_r2_u64 lm2_r2_mul_u64(lm2_r2_u64 a, lm2_r2_u64 b);
LM2_API lm2_r2_u64 lm2_r2_mul_s_u64(lm2_r2_u64 r, uint64_t s);
LM2_API lm2_r2_u64 lm2_r2_mul_v_u64(lm2_r2_u64 r, lm2_v2_u64 v);
LM2_API lm2_r2_u64 lm2_r2_div_u64(lm2_r2_u64 a, lm2_r2_u64 b);
LM2_API lm2_r2_u64 lm2_r2_div_s_u64(lm2_r2_u64 r, uint64_t s);
LM2_API lm2_r2_u64 lm2_r2_div_v_u64(lm2_r2_u64 r, lm2_v2_u64 v);
LM2_API lm2_r2_u64 lm2_r2_mod_u64(lm2_r2_u64 a, lm2_r2_u64 b);
LM2_API lm2_r2_u64 lm2_r2_mod_s_u64(lm2_r2_u64 r, uint64_t s);
LM2_API lm2_r2_u64 lm2_r2_mod_v_u64(lm2_r2_u64 r, lm2_v2_u64 v);
LM2_API lm2_r2_u64 lm2_r2_abs_u64(lm2_r2_u64 a);
LM2_API lm2_r2_u64 lm2_r2_min_u64(lm2_r2_u64 a, lm2_r2_u64 b);
LM2_API lm2_r2_u64 lm2_r2_max_u64(lm2_r2_u64 a, lm2_r2_u64 b);
LM2_API lm2_r2_u64 lm2_r2_clamp_u64(lm2_r2_u64 a, lm2_r2_u64 b, lm2_r2_u64 c);
LM2_API lm2_r2_u64 lm2_r2_union_u64(lm2_r2_u64 a, lm2_r2_u64 b);
LM2_API lm2_r2_u64 lm2_r2_intersection_u64(lm2_r2_u64 a, lm2_r2_u64 b);
LM2_API lm2_v2_u64 lm2_r2_size_u64(lm2_r2_u64 r);
LM2_API lm2_v2_u64 lm2_r2_extents_u64(lm2_r2_u64 r);
LM2_API lm2_v2_u64 lm2_r2_center_u64(lm2_r2_u64 r);
LM2_API int lm2_r2_contains_point_u64(lm2_r2_u64 r, lm2_v2_u64 point);
LM2_API int lm2_r2_overlaps_u64(lm2_r2_u64 a, lm2_r2_u64 b);
LM2_API uint64_t lm2_r2_area_u64(lm2_r2_u64 r);

// ---------------------------------------------------------------------------
// lm2_r2_u32 - 2D Range (32-bit unsigned integer)
// ---------------------------------------------------------------------------

typedef union lm2_r2_u32 {
  lm2_v2_u32 e[2];
  uint32_t e2[4];
  struct {
    lm2_v2_u32 min;
    lm2_v2_u32 max;
  };
  _LM2_SUBSCRIPT_OP(lm2_v2_u32, 2)
} lm2_r2_u32;

LM2_API lm2_r2_u32 lm2_r2_from_min_max_u32(lm2_v2_u32 min, lm2_v2_u32 max);
LM2_API lm2_r2_u32 lm2_r2_from_center_extents_u32(lm2_v2_u32 center, lm2_v2_u32 extents);
LM2_API lm2_r2_u32 lm2_r2_from_center_size_u32(lm2_v2_u32 center, lm2_v2_u32 size);
LM2_API lm2_r2_u32 lm2_r2_from_position_size_u32(lm2_v2_u32 position, lm2_v2_u32 size);
LM2_API lm2_r2_u32 lm2_r2_zero_u32(void);
LM2_API lm2_r2_u32 lm2_r2_add_u32(lm2_r2_u32 a, lm2_r2_u32 b);
LM2_API lm2_r2_u32 lm2_r2_add_s_u32(lm2_r2_u32 r, uint32_t s);
LM2_API lm2_r2_u32 lm2_r2_add_v_u32(lm2_r2_u32 r, lm2_v2_u32 v);
LM2_API lm2_r2_u32 lm2_r2_sub_u32(lm2_r2_u32 a, lm2_r2_u32 b);
LM2_API lm2_r2_u32 lm2_r2_sub_s_u32(lm2_r2_u32 r, uint32_t s);
LM2_API lm2_r2_u32 lm2_r2_sub_v_u32(lm2_r2_u32 r, lm2_v2_u32 v);
LM2_API lm2_r2_u32 lm2_r2_mul_u32(lm2_r2_u32 a, lm2_r2_u32 b);
LM2_API lm2_r2_u32 lm2_r2_mul_s_u32(lm2_r2_u32 r, uint32_t s);
LM2_API lm2_r2_u32 lm2_r2_mul_v_u32(lm2_r2_u32 r, lm2_v2_u32 v);
LM2_API lm2_r2_u32 lm2_r2_div_u32(lm2_r2_u32 a, lm2_r2_u32 b);
LM2_API lm2_r2_u32 lm2_r2_div_s_u32(lm2_r2_u32 r, uint32_t s);
LM2_API lm2_r2_u32 lm2_r2_div_v_u32(lm2_r2_u32 r, lm2_v2_u32 v);
LM2_API lm2_r2_u32 lm2_r2_mod_u32(lm2_r2_u32 a, lm2_r2_u32 b);
LM2_API lm2_r2_u32 lm2_r2_mod_s_u32(lm2_r2_u32 r, uint32_t s);
LM2_API lm2_r2_u32 lm2_r2_mod_v_u32(lm2_r2_u32 r, lm2_v2_u32 v);
LM2_API lm2_r2_u32 lm2_r2_abs_u32(lm2_r2_u32 a);
LM2_API lm2_r2_u32 lm2_r2_min_u32(lm2_r2_u32 a, lm2_r2_u32 b);
LM2_API lm2_r2_u32 lm2_r2_max_u32(lm2_r2_u32 a, lm2_r2_u32 b);
LM2_API lm2_r2_u32 lm2_r2_clamp_u32(lm2_r2_u32 a, lm2_r2_u32 b, lm2_r2_u32 c);
LM2_API lm2_r2_u32 lm2_r2_union_u32(lm2_r2_u32 a, lm2_r2_u32 b);
LM2_API lm2_r2_u32 lm2_r2_intersection_u32(lm2_r2_u32 a, lm2_r2_u32 b);
LM2_API lm2_v2_u32 lm2_r2_size_u32(lm2_r2_u32 r);
LM2_API lm2_v2_u32 lm2_r2_extents_u32(lm2_r2_u32 r);
LM2_API lm2_v2_u32 lm2_r2_center_u32(lm2_r2_u32 r);
LM2_API int lm2_r2_contains_point_u32(lm2_r2_u32 r, lm2_v2_u32 point);
LM2_API int lm2_r2_overlaps_u32(lm2_r2_u32 a, lm2_r2_u32 b);
LM2_API uint32_t lm2_r2_area_u32(lm2_r2_u32 r);

// ---------------------------------------------------------------------------
// lm2_r2_u16 - 2D Range (16-bit unsigned integer)
// ---------------------------------------------------------------------------

typedef union lm2_r2_u16 {
  lm2_v2_u16 e[2];
  uint16_t e2[4];
  struct {
    lm2_v2_u16 min;
    lm2_v2_u16 max;
  };
  _LM2_SUBSCRIPT_OP(lm2_v2_u16, 2)
} lm2_r2_u16;

LM2_API lm2_r2_u16 lm2_r2_from_min_max_u16(lm2_v2_u16 min, lm2_v2_u16 max);
LM2_API lm2_r2_u16 lm2_r2_from_center_extents_u16(lm2_v2_u16 center, lm2_v2_u16 extents);
LM2_API lm2_r2_u16 lm2_r2_from_center_size_u16(lm2_v2_u16 center, lm2_v2_u16 size);
LM2_API lm2_r2_u16 lm2_r2_from_position_size_u16(lm2_v2_u16 position, lm2_v2_u16 size);
LM2_API lm2_r2_u16 lm2_r2_zero_u16(void);
LM2_API lm2_r2_u16 lm2_r2_add_u16(lm2_r2_u16 a, lm2_r2_u16 b);
LM2_API lm2_r2_u16 lm2_r2_add_s_u16(lm2_r2_u16 r, uint16_t s);
LM2_API lm2_r2_u16 lm2_r2_add_v_u16(lm2_r2_u16 r, lm2_v2_u16 v);
LM2_API lm2_r2_u16 lm2_r2_sub_u16(lm2_r2_u16 a, lm2_r2_u16 b);
LM2_API lm2_r2_u16 lm2_r2_sub_s_u16(lm2_r2_u16 r, uint16_t s);
LM2_API lm2_r2_u16 lm2_r2_sub_v_u16(lm2_r2_u16 r, lm2_v2_u16 v);
LM2_API lm2_r2_u16 lm2_r2_mul_u16(lm2_r2_u16 a, lm2_r2_u16 b);
LM2_API lm2_r2_u16 lm2_r2_mul_s_u16(lm2_r2_u16 r, uint16_t s);
LM2_API lm2_r2_u16 lm2_r2_mul_v_u16(lm2_r2_u16 r, lm2_v2_u16 v);
LM2_API lm2_r2_u16 lm2_r2_div_u16(lm2_r2_u16 a, lm2_r2_u16 b);
LM2_API lm2_r2_u16 lm2_r2_div_s_u16(lm2_r2_u16 r, uint16_t s);
LM2_API lm2_r2_u16 lm2_r2_div_v_u16(lm2_r2_u16 r, lm2_v2_u16 v);
LM2_API lm2_r2_u16 lm2_r2_mod_u16(lm2_r2_u16 a, lm2_r2_u16 b);
LM2_API lm2_r2_u16 lm2_r2_mod_s_u16(lm2_r2_u16 r, uint16_t s);
LM2_API lm2_r2_u16 lm2_r2_mod_v_u16(lm2_r2_u16 r, lm2_v2_u16 v);
LM2_API lm2_r2_u16 lm2_r2_min_u16(lm2_r2_u16 a, lm2_r2_u16 b);
LM2_API lm2_r2_u16 lm2_r2_max_u16(lm2_r2_u16 a, lm2_r2_u16 b);
LM2_API lm2_r2_u16 lm2_r2_clamp_u16(lm2_r2_u16 min, lm2_r2_u16 v, lm2_r2_u16 max);
LM2_API lm2_r2_u16 lm2_r2_union_u16(lm2_r2_u16 a, lm2_r2_u16 b);
LM2_API lm2_r2_u16 lm2_r2_intersection_u16(lm2_r2_u16 a, lm2_r2_u16 b);
LM2_API lm2_v2_u16 lm2_r2_size_u16(lm2_r2_u16 r);
LM2_API lm2_v2_u16 lm2_r2_extents_u16(lm2_r2_u16 r);
LM2_API lm2_v2_u16 lm2_r2_center_u16(lm2_r2_u16 r);
LM2_API int lm2_r2_contains_point_u16(lm2_r2_u16 r, lm2_v2_u16 point);
LM2_API int lm2_r2_overlaps_u16(lm2_r2_u16 a, lm2_r2_u16 b);
LM2_API uint16_t lm2_r2_area_u16(lm2_r2_u16 r);

// ---------------------------------------------------------------------------
// lm2_r2_u8 - 2D Range (8-bit unsigned integer)
// ---------------------------------------------------------------------------

typedef union lm2_r2_u8 {
  lm2_v2_u8 e[2];
  uint8_t e2[4];
  struct {
    lm2_v2_u8 min;
    lm2_v2_u8 max;
  };
  _LM2_SUBSCRIPT_OP(lm2_v2_u8, 2)
} lm2_r2_u8;

LM2_API lm2_r2_u8 lm2_r2_from_min_max_u8(lm2_v2_u8 min, lm2_v2_u8 max);
LM2_API lm2_r2_u8 lm2_r2_from_center_extents_u8(lm2_v2_u8 center, lm2_v2_u8 extents);
LM2_API lm2_r2_u8 lm2_r2_from_center_size_u8(lm2_v2_u8 center, lm2_v2_u8 size);
LM2_API lm2_r2_u8 lm2_r2_from_position_size_u8(lm2_v2_u8 position, lm2_v2_u8 size);
LM2_API lm2_r2_u8 lm2_r2_zero_u8(void);
LM2_API lm2_r2_u8 lm2_r2_add_u8(lm2_r2_u8 a, lm2_r2_u8 b);
LM2_API lm2_r2_u8 lm2_r2_add_s_u8(lm2_r2_u8 r, uint8_t s);
LM2_API lm2_r2_u8 lm2_r2_add_v_u8(lm2_r2_u8 r, lm2_v2_u8 v);
LM2_API lm2_r2_u8 lm2_r2_sub_u8(lm2_r2_u8 a, lm2_r2_u8 b);
LM2_API lm2_r2_u8 lm2_r2_sub_s_u8(lm2_r2_u8 r, uint8_t s);
LM2_API lm2_r2_u8 lm2_r2_sub_v_u8(lm2_r2_u8 r, lm2_v2_u8 v);
LM2_API lm2_r2_u8 lm2_r2_mul_u8(lm2_r2_u8 a, lm2_r2_u8 b);
LM2_API lm2_r2_u8 lm2_r2_mul_s_u8(lm2_r2_u8 r, uint8_t s);
LM2_API lm2_r2_u8 lm2_r2_mul_v_u8(lm2_r2_u8 r, lm2_v2_u8 v);
LM2_API lm2_r2_u8 lm2_r2_div_u8(lm2_r2_u8 a, lm2_r2_u8 b);
LM2_API lm2_r2_u8 lm2_r2_div_s_u8(lm2_r2_u8 r, uint8_t s);
LM2_API lm2_r2_u8 lm2_r2_div_v_u8(lm2_r2_u8 r, lm2_v2_u8 v);
LM2_API lm2_r2_u8 lm2_r2_mod_u8(lm2_r2_u8 a, lm2_r2_u8 b);
LM2_API lm2_r2_u8 lm2_r2_mod_s_u8(lm2_r2_u8 r, uint8_t s);
LM2_API lm2_r2_u8 lm2_r2_mod_v_u8(lm2_r2_u8 r, lm2_v2_u8 v);
LM2_API lm2_r2_u8 lm2_r2_min_u8(lm2_r2_u8 a, lm2_r2_u8 b);
LM2_API lm2_r2_u8 lm2_r2_max_u8(lm2_r2_u8 a, lm2_r2_u8 b);
LM2_API lm2_r2_u8 lm2_r2_clamp_u8(lm2_r2_u8 min, lm2_r2_u8 v, lm2_r2_u8 max);
LM2_API lm2_r2_u8 lm2_r2_union_u8(lm2_r2_u8 a, lm2_r2_u8 b);
LM2_API lm2_r2_u8 lm2_r2_intersection_u8(lm2_r2_u8 a, lm2_r2_u8 b);
LM2_API lm2_v2_u8 lm2_r2_size_u8(lm2_r2_u8 r);
LM2_API lm2_v2_u8 lm2_r2_extents_u8(lm2_r2_u8 r);
LM2_API lm2_v2_u8 lm2_r2_center_u8(lm2_r2_u8 r);
LM2_API int lm2_r2_contains_point_u8(lm2_r2_u8 r, lm2_v2_u8 point);
LM2_API int lm2_r2_overlaps_u8(lm2_r2_u8 a, lm2_r2_u8 b);
LM2_API uint8_t lm2_r2_area_u8(lm2_r2_u8 r);

// Default range2 type (float-based)
typedef lm2_r2_f32 lm2_r2;

// #############################################################################
LM2_HEADER_END;
// #############################################################################