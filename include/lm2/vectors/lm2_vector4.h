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

#include "lm2/vectors/lm2_vector_defines.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// lm2_v4_f64
// =============================================================================

// lm2_v4_f64 - 64-bit floating-point 4D vector
typedef union lm2_v4_f64 {
  double e[4];
  struct {
    double x, y, z, w;
  };
  struct {
    double s, t, r, q;
  };
  _LM2_SUBSCRIPT_OP(double, 4)
} lm2_v4_f64;

LM2_API lm2_v4_f64 lm2_v4_add_f64(lm2_v4_f64 a, lm2_v4_f64 b);
LM2_API lm2_v4_f64 lm2_v4_sub_f64(lm2_v4_f64 a, lm2_v4_f64 b);
LM2_API lm2_v4_f64 lm2_v4_mul_f64(lm2_v4_f64 a, lm2_v4_f64 b);
LM2_API lm2_v4_f64 lm2_v4_div_f64(lm2_v4_f64 a, lm2_v4_f64 b);
LM2_API lm2_v4_f64 lm2_v4_add_s_f64(lm2_v4_f64 a, double b);
LM2_API lm2_v4_f64 lm2_v4_sub_s_f64(lm2_v4_f64 a, double b);
LM2_API lm2_v4_f64 lm2_v4_mul_s_f64(lm2_v4_f64 a, double b);
LM2_API lm2_v4_f64 lm2_v4_div_s_f64(lm2_v4_f64 a, double b);
LM2_API lm2_v4_f64 lm2_v4_neg_f64(lm2_v4_f64 a);
LM2_API lm2_v4_f64 lm2_v4_floor_f64(lm2_v4_f64 a);
LM2_API lm2_v4_f64 lm2_v4_ceil_f64(lm2_v4_f64 a);
LM2_API lm2_v4_f64 lm2_v4_round_f64(lm2_v4_f64 a);
LM2_API lm2_v4_f64 lm2_v4_trunc_f64(lm2_v4_f64 a);
LM2_API lm2_v4_f64 lm2_v4_abs_f64(lm2_v4_f64 a);
LM2_API lm2_v4_f64 lm2_v4_sign_f64(lm2_v4_f64 a);
LM2_API lm2_v4_f64 lm2_v4_sign0_f64(lm2_v4_f64 a);
LM2_API lm2_v4_f64 lm2_v4_saturate_f64(lm2_v4_f64 a);
LM2_API lm2_v4_f64 lm2_v4_fract_f64(lm2_v4_f64 a);
LM2_API lm2_v4_f64 lm2_v4_sqrt_f64(lm2_v4_f64 a);
LM2_API lm2_v4_f64 lm2_v4_floor_multiple_f64(lm2_v4_f64 a, lm2_v4_f64 b);
LM2_API lm2_v4_f64 lm2_v4_ceil_multiple_f64(lm2_v4_f64 a, lm2_v4_f64 b);
LM2_API lm2_v4_f64 lm2_v4_round_multiple_f64(lm2_v4_f64 a, lm2_v4_f64 b);
LM2_API lm2_v4_f64 lm2_v4_trunc_multiple_f64(lm2_v4_f64 a, lm2_v4_f64 b);
LM2_API lm2_v4_f64 lm2_v4_min_f64(lm2_v4_f64 a, lm2_v4_f64 b);
LM2_API lm2_v4_f64 lm2_v4_min_abs_f64(lm2_v4_f64 a, lm2_v4_f64 b);
LM2_API lm2_v4_f64 lm2_v4_max_f64(lm2_v4_f64 a, lm2_v4_f64 b);
LM2_API lm2_v4_f64 lm2_v4_max_abs_f64(lm2_v4_f64 a, lm2_v4_f64 b);
LM2_API lm2_v4_f64 lm2_v4_mod_f64(lm2_v4_f64 a, lm2_v4_f64 b);
LM2_API lm2_v4_f64 lm2_v4_pow_f64(lm2_v4_f64 a, lm2_v4_f64 b);
LM2_API lm2_v4_f64 lm2_v4_clamp_f64(lm2_v4_f64 a, lm2_v4_f64 b, lm2_v4_f64 c);
LM2_API lm2_v4_f64 lm2_v4_lerp_f64(lm2_v4_f64 a, lm2_v4_f64 b, lm2_v4_f64 c);
LM2_API lm2_v4_f64 lm2_v4_smoothstep_f64(lm2_v4_f64 a, lm2_v4_f64 b, lm2_v4_f64 c);
LM2_API lm2_v4_f64 lm2_v4_alpha_f64(lm2_v4_f64 a, lm2_v4_f64 b, lm2_v4_f64 c);
LM2_API lm2_v4_f64 lm2_v4_make_f64(double x, double y, double z, double w);
LM2_API lm2_v4_f64 lm2_v4_splat_f64(double v);
LM2_API lm2_v4_f64 lm2_v4_zero_f64(void);

// =============================================================================
// lm2_v4_f32
// =============================================================================

// lm2_v4_f32 - 32-bit floating-point 4D vector
typedef union lm2_v4_f32 {
  float e[4];
  struct {
    float x, y, z, w;
  };
  struct {
    float s, t, r, q;
  };
  _LM2_SUBSCRIPT_OP(float, 4)
} lm2_v4_f32;

LM2_API lm2_v4_f32 lm2_v4_add_f32(lm2_v4_f32 a, lm2_v4_f32 b);
LM2_API lm2_v4_f32 lm2_v4_sub_f32(lm2_v4_f32 a, lm2_v4_f32 b);
LM2_API lm2_v4_f32 lm2_v4_mul_f32(lm2_v4_f32 a, lm2_v4_f32 b);
LM2_API lm2_v4_f32 lm2_v4_div_f32(lm2_v4_f32 a, lm2_v4_f32 b);
LM2_API lm2_v4_f32 lm2_v4_add_s_f32(lm2_v4_f32 a, float b);
LM2_API lm2_v4_f32 lm2_v4_sub_s_f32(lm2_v4_f32 a, float b);
LM2_API lm2_v4_f32 lm2_v4_mul_s_f32(lm2_v4_f32 a, float b);
LM2_API lm2_v4_f32 lm2_v4_div_s_f32(lm2_v4_f32 a, float b);
LM2_API lm2_v4_f32 lm2_v4_neg_f32(lm2_v4_f32 a);
LM2_API lm2_v4_f32 lm2_v4_floor_f32(lm2_v4_f32 a);
LM2_API lm2_v4_f32 lm2_v4_ceil_f32(lm2_v4_f32 a);
LM2_API lm2_v4_f32 lm2_v4_round_f32(lm2_v4_f32 a);
LM2_API lm2_v4_f32 lm2_v4_trunc_f32(lm2_v4_f32 a);
LM2_API lm2_v4_f32 lm2_v4_abs_f32(lm2_v4_f32 a);
LM2_API lm2_v4_f32 lm2_v4_sign_f32(lm2_v4_f32 a);
LM2_API lm2_v4_f32 lm2_v4_sign0_f32(lm2_v4_f32 a);
LM2_API lm2_v4_f32 lm2_v4_saturate_f32(lm2_v4_f32 a);
LM2_API lm2_v4_f32 lm2_v4_fract_f32(lm2_v4_f32 a);
LM2_API lm2_v4_f32 lm2_v4_sqrt_f32(lm2_v4_f32 a);
LM2_API lm2_v4_f32 lm2_v4_floor_multiple_f32(lm2_v4_f32 a, lm2_v4_f32 b);
LM2_API lm2_v4_f32 lm2_v4_ceil_multiple_f32(lm2_v4_f32 a, lm2_v4_f32 b);
LM2_API lm2_v4_f32 lm2_v4_round_multiple_f32(lm2_v4_f32 a, lm2_v4_f32 b);
LM2_API lm2_v4_f32 lm2_v4_trunc_multiple_f32(lm2_v4_f32 a, lm2_v4_f32 b);
LM2_API lm2_v4_f32 lm2_v4_min_f32(lm2_v4_f32 a, lm2_v4_f32 b);
LM2_API lm2_v4_f32 lm2_v4_min_abs_f32(lm2_v4_f32 a, lm2_v4_f32 b);
LM2_API lm2_v4_f32 lm2_v4_max_f32(lm2_v4_f32 a, lm2_v4_f32 b);
LM2_API lm2_v4_f32 lm2_v4_max_abs_f32(lm2_v4_f32 a, lm2_v4_f32 b);
LM2_API lm2_v4_f32 lm2_v4_mod_f32(lm2_v4_f32 a, lm2_v4_f32 b);
LM2_API lm2_v4_f32 lm2_v4_pow_f32(lm2_v4_f32 a, lm2_v4_f32 b);
LM2_API lm2_v4_f32 lm2_v4_clamp_f32(lm2_v4_f32 a, lm2_v4_f32 b, lm2_v4_f32 c);
LM2_API lm2_v4_f32 lm2_v4_lerp_f32(lm2_v4_f32 a, lm2_v4_f32 b, lm2_v4_f32 c);
LM2_API lm2_v4_f32 lm2_v4_smoothstep_f32(lm2_v4_f32 a, lm2_v4_f32 b, lm2_v4_f32 c);
LM2_API lm2_v4_f32 lm2_v4_alpha_f32(lm2_v4_f32 a, lm2_v4_f32 b, lm2_v4_f32 c);
LM2_API lm2_v4_f32 lm2_v4_make_f32(float x, float y, float z, float w);
LM2_API lm2_v4_f32 lm2_v4_splat_f32(float v);
LM2_API lm2_v4_f32 lm2_v4_zero_f32(void);

// =============================================================================
// lm2_v4_i64
// =============================================================================

// lm2_v4_i64 - 64-bit signed integer 4D vector
typedef union lm2_v4_i64 {
  int64_t e[4];
  struct {
    int64_t x, y, z, w;
  };
  struct {
    int64_t s, t, r, q;
  };
  _LM2_SUBSCRIPT_OP(int64_t, 4)
} lm2_v4_i64;

LM2_API lm2_v4_i64 lm2_v4_add_i64(lm2_v4_i64 a, lm2_v4_i64 b);
LM2_API lm2_v4_i64 lm2_v4_sub_i64(lm2_v4_i64 a, lm2_v4_i64 b);
LM2_API lm2_v4_i64 lm2_v4_mul_i64(lm2_v4_i64 a, lm2_v4_i64 b);
LM2_API lm2_v4_i64 lm2_v4_div_i64(lm2_v4_i64 a, lm2_v4_i64 b);
LM2_API lm2_v4_i64 lm2_v4_add_s_i64(lm2_v4_i64 a, int64_t b);
LM2_API lm2_v4_i64 lm2_v4_sub_s_i64(lm2_v4_i64 a, int64_t b);
LM2_API lm2_v4_i64 lm2_v4_mul_s_i64(lm2_v4_i64 a, int64_t b);
LM2_API lm2_v4_i64 lm2_v4_div_s_i64(lm2_v4_i64 a, int64_t b);
LM2_API lm2_v4_i64 lm2_v4_neg_i64(lm2_v4_i64 a);
LM2_API lm2_v4_i64 lm2_v4_abs_i64(lm2_v4_i64 a);
LM2_API lm2_v4_i64 lm2_v4_sign_i64(lm2_v4_i64 a);
LM2_API lm2_v4_i64 lm2_v4_sign0_i64(lm2_v4_i64 a);
LM2_API lm2_v4_i64 lm2_v4_min_i64(lm2_v4_i64 a, lm2_v4_i64 b);
LM2_API lm2_v4_i64 lm2_v4_min_abs_i64(lm2_v4_i64 a, lm2_v4_i64 b);
LM2_API lm2_v4_i64 lm2_v4_max_i64(lm2_v4_i64 a, lm2_v4_i64 b);
LM2_API lm2_v4_i64 lm2_v4_max_abs_i64(lm2_v4_i64 a, lm2_v4_i64 b);
LM2_API lm2_v4_i64 lm2_v4_mod_i64(lm2_v4_i64 a, lm2_v4_i64 b);
LM2_API lm2_v4_i64 lm2_v4_clamp_i64(lm2_v4_i64 a, lm2_v4_i64 b, lm2_v4_i64 c);
LM2_API lm2_v4_i64 lm2_v4_make_i64(int64_t x, int64_t y, int64_t z, int64_t w);
LM2_API lm2_v4_i64 lm2_v4_splat_i64(int64_t v);
LM2_API lm2_v4_i64 lm2_v4_zero_i64(void);

// =============================================================================
// lm2_v4_i32
// =============================================================================

// lm2_v4_i32 - 32-bit signed integer 4D vector
typedef union lm2_v4_i32 {
  int32_t e[4];
  struct {
    int32_t x, y, z, w;
  };
  struct {
    int32_t s, t, r, q;
  };
  _LM2_SUBSCRIPT_OP(int32_t, 4)
} lm2_v4_i32;

LM2_API lm2_v4_i32 lm2_v4_add_i32(lm2_v4_i32 a, lm2_v4_i32 b);
LM2_API lm2_v4_i32 lm2_v4_sub_i32(lm2_v4_i32 a, lm2_v4_i32 b);
LM2_API lm2_v4_i32 lm2_v4_mul_i32(lm2_v4_i32 a, lm2_v4_i32 b);
LM2_API lm2_v4_i32 lm2_v4_div_i32(lm2_v4_i32 a, lm2_v4_i32 b);
LM2_API lm2_v4_i32 lm2_v4_add_s_i32(lm2_v4_i32 a, int32_t b);
LM2_API lm2_v4_i32 lm2_v4_sub_s_i32(lm2_v4_i32 a, int32_t b);
LM2_API lm2_v4_i32 lm2_v4_mul_s_i32(lm2_v4_i32 a, int32_t b);
LM2_API lm2_v4_i32 lm2_v4_div_s_i32(lm2_v4_i32 a, int32_t b);
LM2_API lm2_v4_i32 lm2_v4_neg_i32(lm2_v4_i32 a);
LM2_API lm2_v4_i32 lm2_v4_abs_i32(lm2_v4_i32 a);
LM2_API lm2_v4_i32 lm2_v4_sign_i32(lm2_v4_i32 a);
LM2_API lm2_v4_i32 lm2_v4_sign0_i32(lm2_v4_i32 a);
LM2_API lm2_v4_i32 lm2_v4_min_i32(lm2_v4_i32 a, lm2_v4_i32 b);
LM2_API lm2_v4_i32 lm2_v4_min_abs_i32(lm2_v4_i32 a, lm2_v4_i32 b);
LM2_API lm2_v4_i32 lm2_v4_max_i32(lm2_v4_i32 a, lm2_v4_i32 b);
LM2_API lm2_v4_i32 lm2_v4_max_abs_i32(lm2_v4_i32 a, lm2_v4_i32 b);
LM2_API lm2_v4_i32 lm2_v4_mod_i32(lm2_v4_i32 a, lm2_v4_i32 b);
LM2_API lm2_v4_i32 lm2_v4_clamp_i32(lm2_v4_i32 a, lm2_v4_i32 b, lm2_v4_i32 c);
LM2_API lm2_v4_i32 lm2_v4_make_i32(int32_t x, int32_t y, int32_t z, int32_t w);
LM2_API lm2_v4_i32 lm2_v4_splat_i32(int32_t v);
LM2_API lm2_v4_i32 lm2_v4_zero_i32(void);

// =============================================================================
// lm2_v4_i16
// =============================================================================

// lm2_v4_i16 - 16-bit signed integer 4D vector
typedef union lm2_v4_i16 {
  int16_t e[4];
  struct {
    int16_t x, y, z, w;
  };
  struct {
    int16_t s, t, r, q;
  };
  _LM2_SUBSCRIPT_OP(int16_t, 4)
} lm2_v4_i16;

LM2_API lm2_v4_i16 lm2_v4_add_i16(lm2_v4_i16 a, lm2_v4_i16 b);
LM2_API lm2_v4_i16 lm2_v4_sub_i16(lm2_v4_i16 a, lm2_v4_i16 b);
LM2_API lm2_v4_i16 lm2_v4_mul_i16(lm2_v4_i16 a, lm2_v4_i16 b);
LM2_API lm2_v4_i16 lm2_v4_div_i16(lm2_v4_i16 a, lm2_v4_i16 b);
LM2_API lm2_v4_i16 lm2_v4_add_s_i16(lm2_v4_i16 a, int16_t b);
LM2_API lm2_v4_i16 lm2_v4_sub_s_i16(lm2_v4_i16 a, int16_t b);
LM2_API lm2_v4_i16 lm2_v4_mul_s_i16(lm2_v4_i16 a, int16_t b);
LM2_API lm2_v4_i16 lm2_v4_div_s_i16(lm2_v4_i16 a, int16_t b);
LM2_API lm2_v4_i16 lm2_v4_neg_i16(lm2_v4_i16 a);
LM2_API lm2_v4_i16 lm2_v4_abs_i16(lm2_v4_i16 a);
LM2_API lm2_v4_i16 lm2_v4_sign_i16(lm2_v4_i16 a);
LM2_API lm2_v4_i16 lm2_v4_sign0_i16(lm2_v4_i16 a);
LM2_API lm2_v4_i16 lm2_v4_min_i16(lm2_v4_i16 a, lm2_v4_i16 b);
LM2_API lm2_v4_i16 lm2_v4_min_abs_i16(lm2_v4_i16 a, lm2_v4_i16 b);
LM2_API lm2_v4_i16 lm2_v4_max_i16(lm2_v4_i16 a, lm2_v4_i16 b);
LM2_API lm2_v4_i16 lm2_v4_max_abs_i16(lm2_v4_i16 a, lm2_v4_i16 b);
LM2_API lm2_v4_i16 lm2_v4_mod_i16(lm2_v4_i16 a, lm2_v4_i16 b);
LM2_API lm2_v4_i16 lm2_v4_clamp_i16(lm2_v4_i16 a, lm2_v4_i16 b, lm2_v4_i16 c);
LM2_API lm2_v4_i16 lm2_v4_make_i16(int16_t x, int16_t y, int16_t z, int16_t w);
LM2_API lm2_v4_i16 lm2_v4_splat_i16(int16_t v);
LM2_API lm2_v4_i16 lm2_v4_zero_i16(void);

// =============================================================================
// lm2_v4_i8
// =============================================================================

// lm2_v4_i8 - 8-bit signed integer 4D vector
typedef union lm2_v4_i8 {
  int8_t e[4];
  struct {
    int8_t x, y, z, w;
  };
  struct {
    int8_t s, t, r, q;
  };
  _LM2_SUBSCRIPT_OP(int8_t, 4)
} lm2_v4_i8;

LM2_API lm2_v4_i8 lm2_v4_add_i8(lm2_v4_i8 a, lm2_v4_i8 b);
LM2_API lm2_v4_i8 lm2_v4_sub_i8(lm2_v4_i8 a, lm2_v4_i8 b);
LM2_API lm2_v4_i8 lm2_v4_mul_i8(lm2_v4_i8 a, lm2_v4_i8 b);
LM2_API lm2_v4_i8 lm2_v4_div_i8(lm2_v4_i8 a, lm2_v4_i8 b);
LM2_API lm2_v4_i8 lm2_v4_add_s_i8(lm2_v4_i8 a, int8_t b);
LM2_API lm2_v4_i8 lm2_v4_sub_s_i8(lm2_v4_i8 a, int8_t b);
LM2_API lm2_v4_i8 lm2_v4_mul_s_i8(lm2_v4_i8 a, int8_t b);
LM2_API lm2_v4_i8 lm2_v4_div_s_i8(lm2_v4_i8 a, int8_t b);
LM2_API lm2_v4_i8 lm2_v4_neg_i8(lm2_v4_i8 a);
LM2_API lm2_v4_i8 lm2_v4_abs_i8(lm2_v4_i8 a);
LM2_API lm2_v4_i8 lm2_v4_sign_i8(lm2_v4_i8 a);
LM2_API lm2_v4_i8 lm2_v4_sign0_i8(lm2_v4_i8 a);
LM2_API lm2_v4_i8 lm2_v4_min_i8(lm2_v4_i8 a, lm2_v4_i8 b);
LM2_API lm2_v4_i8 lm2_v4_min_abs_i8(lm2_v4_i8 a, lm2_v4_i8 b);
LM2_API lm2_v4_i8 lm2_v4_max_i8(lm2_v4_i8 a, lm2_v4_i8 b);
LM2_API lm2_v4_i8 lm2_v4_max_abs_i8(lm2_v4_i8 a, lm2_v4_i8 b);
LM2_API lm2_v4_i8 lm2_v4_mod_i8(lm2_v4_i8 a, lm2_v4_i8 b);
LM2_API lm2_v4_i8 lm2_v4_clamp_i8(lm2_v4_i8 a, lm2_v4_i8 b, lm2_v4_i8 c);
LM2_API lm2_v4_i8 lm2_v4_make_i8(int8_t x, int8_t y, int8_t z, int8_t w);
LM2_API lm2_v4_i8 lm2_v4_splat_i8(int8_t v);
LM2_API lm2_v4_i8 lm2_v4_zero_i8(void);

// =============================================================================
// lm2_v4_u64
// =============================================================================

// lm2_v4_u64 - 64-bit unsigned integer 4D vector
typedef union lm2_v4_u64 {
  uint64_t e[4];
  struct {
    uint64_t x, y, z, w;
  };
  struct {
    uint64_t s, t, r, q;
  };
  _LM2_SUBSCRIPT_OP(uint64_t, 4)
} lm2_v4_u64;

LM2_API lm2_v4_u64 lm2_v4_add_u64(lm2_v4_u64 a, lm2_v4_u64 b);
LM2_API lm2_v4_u64 lm2_v4_sub_u64(lm2_v4_u64 a, lm2_v4_u64 b);
LM2_API lm2_v4_u64 lm2_v4_mul_u64(lm2_v4_u64 a, lm2_v4_u64 b);
LM2_API lm2_v4_u64 lm2_v4_div_u64(lm2_v4_u64 a, lm2_v4_u64 b);
LM2_API lm2_v4_u64 lm2_v4_add_s_u64(lm2_v4_u64 a, uint64_t b);
LM2_API lm2_v4_u64 lm2_v4_sub_s_u64(lm2_v4_u64 a, uint64_t b);
LM2_API lm2_v4_u64 lm2_v4_mul_s_u64(lm2_v4_u64 a, uint64_t b);
LM2_API lm2_v4_u64 lm2_v4_div_s_u64(lm2_v4_u64 a, uint64_t b);
LM2_API lm2_v4_u64 lm2_v4_min_u64(lm2_v4_u64 a, lm2_v4_u64 b);
LM2_API lm2_v4_u64 lm2_v4_max_u64(lm2_v4_u64 a, lm2_v4_u64 b);
LM2_API lm2_v4_u64 lm2_v4_clamp_u64(lm2_v4_u64 a, lm2_v4_u64 b, lm2_v4_u64 c);
LM2_API lm2_v4_u64 lm2_v4_make_u64(uint64_t x, uint64_t y, uint64_t z, uint64_t w);
LM2_API lm2_v4_u64 lm2_v4_splat_u64(uint64_t v);
LM2_API lm2_v4_u64 lm2_v4_zero_u64(void);

// =============================================================================
// lm2_v4_u32
// =============================================================================

// lm2_v4_u32 - 32-bit unsigned integer 4D vector
typedef union lm2_v4_u32 {
  uint32_t e[4];
  struct {
    uint32_t x, y, z, w;
  };
  struct {
    uint32_t s, t, r, q;
  };
  _LM2_SUBSCRIPT_OP(uint32_t, 4)
} lm2_v4_u32;
LM2_API lm2_v4_u32 lm2_v4_add_u32(lm2_v4_u32 a, lm2_v4_u32 b);
LM2_API lm2_v4_u32 lm2_v4_sub_u32(lm2_v4_u32 a, lm2_v4_u32 b);
LM2_API lm2_v4_u32 lm2_v4_mul_u32(lm2_v4_u32 a, lm2_v4_u32 b);
LM2_API lm2_v4_u32 lm2_v4_div_u32(lm2_v4_u32 a, lm2_v4_u32 b);
LM2_API lm2_v4_u32 lm2_v4_add_s_u32(lm2_v4_u32 a, uint32_t b);
LM2_API lm2_v4_u32 lm2_v4_sub_s_u32(lm2_v4_u32 a, uint32_t b);
LM2_API lm2_v4_u32 lm2_v4_mul_s_u32(lm2_v4_u32 a, uint32_t b);
LM2_API lm2_v4_u32 lm2_v4_div_s_u32(lm2_v4_u32 a, uint32_t b);
LM2_API lm2_v4_u32 lm2_v4_neg_u32(lm2_v4_u32 a);
LM2_API lm2_v4_u32 lm2_v4_min_u32(lm2_v4_u32 a, lm2_v4_u32 b);
LM2_API lm2_v4_u32 lm2_v4_max_u32(lm2_v4_u32 a, lm2_v4_u32 b);
LM2_API lm2_v4_u32 lm2_v4_clamp_u32(lm2_v4_u32 a, lm2_v4_u32 b, lm2_v4_u32 c);
LM2_API lm2_v4_u32 lm2_v4_make_u32(uint32_t x, uint32_t y, uint32_t z, uint32_t w);
LM2_API lm2_v4_u32 lm2_v4_splat_u32(uint32_t v);
LM2_API lm2_v4_u32 lm2_v4_zero_u32(void);

// =============================================================================
// lm2_v4_u16
// =============================================================================

// lm2_v4_u16 - 16-bit unsigned integer 4D vector
typedef union lm2_v4_u16 {
  uint16_t e[4];
  struct {
    uint16_t x, y, z, w;
  };
  struct {
    uint16_t s, t, r, q;
  };
  _LM2_SUBSCRIPT_OP(uint16_t, 4)
} lm2_v4_u16;

LM2_API lm2_v4_u16 lm2_v4_add_u16(lm2_v4_u16 a, lm2_v4_u16 b);
LM2_API lm2_v4_u16 lm2_v4_sub_u16(lm2_v4_u16 a, lm2_v4_u16 b);
LM2_API lm2_v4_u16 lm2_v4_mul_u16(lm2_v4_u16 a, lm2_v4_u16 b);
LM2_API lm2_v4_u16 lm2_v4_div_u16(lm2_v4_u16 a, lm2_v4_u16 b);
LM2_API lm2_v4_u16 lm2_v4_add_s_u16(lm2_v4_u16 a, uint16_t b);
LM2_API lm2_v4_u16 lm2_v4_sub_s_u16(lm2_v4_u16 a, uint16_t b);
LM2_API lm2_v4_u16 lm2_v4_mul_s_u16(lm2_v4_u16 a, uint16_t b);
LM2_API lm2_v4_u16 lm2_v4_div_s_u16(lm2_v4_u16 a, uint16_t b);
LM2_API lm2_v4_u16 lm2_v4_min_u16(lm2_v4_u16 a, lm2_v4_u16 b);
LM2_API lm2_v4_u16 lm2_v4_max_u16(lm2_v4_u16 a, lm2_v4_u16 b);
LM2_API lm2_v4_u16 lm2_v4_clamp_u16(lm2_v4_u16 a, lm2_v4_u16 b, lm2_v4_u16 c);
LM2_API lm2_v4_u16 lm2_v4_make_u16(uint16_t x, uint16_t y, uint16_t z, uint16_t w);
LM2_API lm2_v4_u16 lm2_v4_splat_u16(uint16_t v);
LM2_API lm2_v4_u16 lm2_v4_zero_u16(void);

// =============================================================================
// lm2_v4_u8
// =============================================================================

// lm2_v4_u8 - 8-bit unsigned integer 4D vector
typedef union lm2_v4_u8 {
  uint8_t e[4];
  struct {
    uint8_t x, y, z, w;
  };
  struct {
    uint8_t s, t, r, q;
  };
  _LM2_SUBSCRIPT_OP(uint8_t, 4)
} lm2_v4_u8;

LM2_API lm2_v4_u8 lm2_v4_add_u8(lm2_v4_u8 a, lm2_v4_u8 b);
LM2_API lm2_v4_u8 lm2_v4_sub_u8(lm2_v4_u8 a, lm2_v4_u8 b);
LM2_API lm2_v4_u8 lm2_v4_mul_u8(lm2_v4_u8 a, lm2_v4_u8 b);
LM2_API lm2_v4_u8 lm2_v4_div_u8(lm2_v4_u8 a, lm2_v4_u8 b);
LM2_API lm2_v4_u8 lm2_v4_add_s_u8(lm2_v4_u8 a, uint8_t b);
LM2_API lm2_v4_u8 lm2_v4_sub_s_u8(lm2_v4_u8 a, uint8_t b);
LM2_API lm2_v4_u8 lm2_v4_mul_s_u8(lm2_v4_u8 a, uint8_t b);
LM2_API lm2_v4_u8 lm2_v4_div_s_u8(lm2_v4_u8 a, uint8_t b);
LM2_API lm2_v4_u8 lm2_v4_neg_u8(lm2_v4_u8 a);
LM2_API lm2_v4_u8 lm2_v4_min_u8(lm2_v4_u8 a, lm2_v4_u8 b);
LM2_API lm2_v4_u8 lm2_v4_max_u8(lm2_v4_u8 a, lm2_v4_u8 b);
LM2_API lm2_v4_u8 lm2_v4_clamp_u8(lm2_v4_u8 a, lm2_v4_u8 b, lm2_v4_u8 c);
LM2_API lm2_v4_u8 lm2_v4_make_u8(uint8_t x, uint8_t y, uint8_t z, uint8_t w);
LM2_API lm2_v4_u8 lm2_v4_splat_u8(uint8_t v);
LM2_API lm2_v4_u8 lm2_v4_zero_u8(void);

// =============================================================================
// Type Alias
// =============================================================================
// Default vector type (32-bit float)
typedef lm2_v4_f32 lm2_v4;

// #############################################################################
LM2_HEADER_END;
// #############################################################################