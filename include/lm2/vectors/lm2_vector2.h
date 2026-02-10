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
// 2D Vector Type Definitions
// =============================================================================

// lm2_v2_f64 - 64-bit floating-point 2D vector
typedef union lm2_v2_f64 {
  double e[2];
  struct {
    double x, y;
  };
  struct {
    double s, t;
  };
  _LM2_VECTOR_SUBSCRIPT_OP(double, 2)
} lm2_v2_f64;

// lm2_v2_f32 - 32-bit floating-point 2D vector
typedef union lm2_v2_f32 {
  float e[2];
  struct {
    float x, y;
  };
  struct {
    float s, t;
  };
  _LM2_VECTOR_SUBSCRIPT_OP(float, 2)
} lm2_v2_f32;

// lm2_v2_i64 - 64-bit signed integer 2D vector
typedef union lm2_v2_i64 {
  int64_t e[2];
  struct {
    int64_t x, y;
  };
  struct {
    int64_t s, t;
  };
  _LM2_VECTOR_SUBSCRIPT_OP(int64_t, 2)
} lm2_v2_i64;

// lm2_v2_i32 - 32-bit signed integer 2D vector
typedef union lm2_v2_i32 {
  int32_t e[2];
  struct {
    int32_t x, y;
  };
  struct {
    int32_t s, t;
  };
  _LM2_VECTOR_SUBSCRIPT_OP(int32_t, 2)
} lm2_v2_i32;

// lm2_v2_i16 - 16-bit signed integer 2D vector
typedef union lm2_v2_i16 {
  int16_t e[2];
  struct {
    int16_t x, y;
  };
  struct {
    int16_t s, t;
  };
  _LM2_VECTOR_SUBSCRIPT_OP(int16_t, 2)
} lm2_v2_i16;

// lm2_v2_i8 - 8-bit signed integer 2D vector
typedef union lm2_v2_i8 {
  int8_t e[2];
  struct {
    int8_t x, y;
  };
  struct {
    int8_t s, t;
  };
  _LM2_VECTOR_SUBSCRIPT_OP(int8_t, 2)
} lm2_v2_i8;

// lm2_v2_u64 - 64-bit unsigned integer 2D vector
typedef union lm2_v2_u64 {
  uint64_t e[2];
  struct {
    uint64_t x, y;
  };
  struct {
    uint64_t s, t;
  };
  _LM2_VECTOR_SUBSCRIPT_OP(uint64_t, 2)
} lm2_v2_u64;

// lm2_v2_u32 - 32-bit unsigned integer 2D vector
typedef union lm2_v2_u32 {
  uint32_t e[2];
  struct {
    uint32_t x, y;
  };
  struct {
    uint32_t s, t;
  };
  _LM2_VECTOR_SUBSCRIPT_OP(uint32_t, 2)
} lm2_v2_u32;

// lm2_v2_u16 - 16-bit unsigned integer 2D vector
typedef union lm2_v2_u16 {
  uint16_t e[2];
  struct {
    uint16_t x, y;
  };
  struct {
    uint16_t s, t;
  };
  _LM2_VECTOR_SUBSCRIPT_OP(uint16_t, 2)
} lm2_v2_u16;

// lm2_v2_u8 - 8-bit unsigned integer 2D vector
typedef union lm2_v2_u8 {
  uint8_t e[2];
  struct {
    uint8_t x, y;
  };
  struct {
    uint8_t s, t;
  };
  _LM2_VECTOR_SUBSCRIPT_OP(uint8_t, 2)
} lm2_v2_u8;

// =============================================================================
// lm2_v2_f64 Operations
// =============================================================================
LM2_API lm2_v2_f64 lm2_v2_add_f64(lm2_v2_f64 a, lm2_v2_f64 b);
LM2_API lm2_v2_f64 lm2_v2_sub_f64(lm2_v2_f64 a, lm2_v2_f64 b);
LM2_API lm2_v2_f64 lm2_v2_mul_f64(lm2_v2_f64 a, lm2_v2_f64 b);
LM2_API lm2_v2_f64 lm2_v2_div_f64(lm2_v2_f64 a, lm2_v2_f64 b);
LM2_API lm2_v2_f64 lm2_v2_add_s_f64(lm2_v2_f64 a, double b);
LM2_API lm2_v2_f64 lm2_v2_sub_s_f64(lm2_v2_f64 a, double b);
LM2_API lm2_v2_f64 lm2_v2_mul_s_f64(lm2_v2_f64 a, double b);
LM2_API lm2_v2_f64 lm2_v2_div_s_f64(lm2_v2_f64 a, double b);
LM2_API lm2_v2_f64 lm2_v2_neg_f64(lm2_v2_f64 a);
LM2_API lm2_v2_f64 lm2_v2_floor_f64(lm2_v2_f64 a);
LM2_API lm2_v2_f64 lm2_v2_ceil_f64(lm2_v2_f64 a);
LM2_API lm2_v2_f64 lm2_v2_round_f64(lm2_v2_f64 a);
LM2_API lm2_v2_f64 lm2_v2_trunc_f64(lm2_v2_f64 a);
LM2_API lm2_v2_f64 lm2_v2_abs_f64(lm2_v2_f64 a);
LM2_API lm2_v2_f64 lm2_v2_sign_f64(lm2_v2_f64 a);
LM2_API lm2_v2_f64 lm2_v2_sign0_f64(lm2_v2_f64 a);
LM2_API lm2_v2_f64 lm2_v2_saturate_f64(lm2_v2_f64 a);
LM2_API lm2_v2_f64 lm2_v2_fract_f64(lm2_v2_f64 a);
LM2_API lm2_v2_f64 lm2_v2_sqrt_f64(lm2_v2_f64 a);
LM2_API lm2_v2_f64 lm2_v2_floor_multiple_f64(lm2_v2_f64 a, lm2_v2_f64 b);
LM2_API lm2_v2_f64 lm2_v2_ceil_multiple_f64(lm2_v2_f64 a, lm2_v2_f64 b);
LM2_API lm2_v2_f64 lm2_v2_round_multiple_f64(lm2_v2_f64 a, lm2_v2_f64 b);
LM2_API lm2_v2_f64 lm2_v2_trunc_multiple_f64(lm2_v2_f64 a, lm2_v2_f64 b);
LM2_API lm2_v2_f64 lm2_v2_min_f64(lm2_v2_f64 a, lm2_v2_f64 b);
LM2_API lm2_v2_f64 lm2_v2_min_abs_f64(lm2_v2_f64 a, lm2_v2_f64 b);
LM2_API lm2_v2_f64 lm2_v2_max_f64(lm2_v2_f64 a, lm2_v2_f64 b);
LM2_API lm2_v2_f64 lm2_v2_max_abs_f64(lm2_v2_f64 a, lm2_v2_f64 b);
LM2_API lm2_v2_f64 lm2_v2_mod_f64(lm2_v2_f64 a, lm2_v2_f64 b);
LM2_API lm2_v2_f64 lm2_v2_pow_f64(lm2_v2_f64 a, lm2_v2_f64 b);
LM2_API lm2_v2_f64 lm2_v2_clamp_f64(lm2_v2_f64 a, lm2_v2_f64 b, lm2_v2_f64 c);
LM2_API lm2_v2_f64 lm2_v2_lerp_f64(lm2_v2_f64 a, lm2_v2_f64 b, lm2_v2_f64 c);
LM2_API lm2_v2_f64 lm2_v2_smoothstep_f64(lm2_v2_f64 a, lm2_v2_f64 b, lm2_v2_f64 c);
LM2_API lm2_v2_f64 lm2_v2_alpha_f64(lm2_v2_f64 a, lm2_v2_f64 b, lm2_v2_f64 c);
LM2_API lm2_v2_f64 lm2_v2_make_f64(double x, double y);
LM2_API lm2_v2_f64 lm2_v2_splat_f64(double v);
LM2_API lm2_v2_f64 lm2_v2_zero_f64(void);

// =============================================================================
// lm2_v2_f32 Operations
// =============================================================================
LM2_API lm2_v2_f32 lm2_v2_add_f32(lm2_v2_f32 a, lm2_v2_f32 b);
LM2_API lm2_v2_f32 lm2_v2_sub_f32(lm2_v2_f32 a, lm2_v2_f32 b);
LM2_API lm2_v2_f32 lm2_v2_mul_f32(lm2_v2_f32 a, lm2_v2_f32 b);
LM2_API lm2_v2_f32 lm2_v2_div_f32(lm2_v2_f32 a, lm2_v2_f32 b);
LM2_API lm2_v2_f32 lm2_v2_add_s_f32(lm2_v2_f32 a, float b);
LM2_API lm2_v2_f32 lm2_v2_sub_s_f32(lm2_v2_f32 a, float b);
LM2_API lm2_v2_f32 lm2_v2_mul_s_f32(lm2_v2_f32 a, float b);
LM2_API lm2_v2_f32 lm2_v2_div_s_f32(lm2_v2_f32 a, float b);
LM2_API lm2_v2_f32 lm2_v2_neg_f32(lm2_v2_f32 a);
LM2_API lm2_v2_f32 lm2_v2_floor_f32(lm2_v2_f32 a);
LM2_API lm2_v2_f32 lm2_v2_ceil_f32(lm2_v2_f32 a);
LM2_API lm2_v2_f32 lm2_v2_round_f32(lm2_v2_f32 a);
LM2_API lm2_v2_f32 lm2_v2_trunc_f32(lm2_v2_f32 a);
LM2_API lm2_v2_f32 lm2_v2_abs_f32(lm2_v2_f32 a);
LM2_API lm2_v2_f32 lm2_v2_sign_f32(lm2_v2_f32 a);
LM2_API lm2_v2_f32 lm2_v2_sign0_f32(lm2_v2_f32 a);
LM2_API lm2_v2_f32 lm2_v2_saturate_f32(lm2_v2_f32 a);
LM2_API lm2_v2_f32 lm2_v2_fract_f32(lm2_v2_f32 a);
LM2_API lm2_v2_f32 lm2_v2_sqrt_f32(lm2_v2_f32 a);
LM2_API lm2_v2_f32 lm2_v2_floor_multiple_f32(lm2_v2_f32 a, lm2_v2_f32 b);
LM2_API lm2_v2_f32 lm2_v2_ceil_multiple_f32(lm2_v2_f32 a, lm2_v2_f32 b);
LM2_API lm2_v2_f32 lm2_v2_round_multiple_f32(lm2_v2_f32 a, lm2_v2_f32 b);
LM2_API lm2_v2_f32 lm2_v2_trunc_multiple_f32(lm2_v2_f32 a, lm2_v2_f32 b);
LM2_API lm2_v2_f32 lm2_v2_min_f32(lm2_v2_f32 a, lm2_v2_f32 b);
LM2_API lm2_v2_f32 lm2_v2_min_abs_f32(lm2_v2_f32 a, lm2_v2_f32 b);
LM2_API lm2_v2_f32 lm2_v2_max_f32(lm2_v2_f32 a, lm2_v2_f32 b);
LM2_API lm2_v2_f32 lm2_v2_max_abs_f32(lm2_v2_f32 a, lm2_v2_f32 b);
LM2_API lm2_v2_f32 lm2_v2_mod_f32(lm2_v2_f32 a, lm2_v2_f32 b);
LM2_API lm2_v2_f32 lm2_v2_pow_f32(lm2_v2_f32 a, lm2_v2_f32 b);
LM2_API lm2_v2_f32 lm2_v2_clamp_f32(lm2_v2_f32 a, lm2_v2_f32 b, lm2_v2_f32 c);
LM2_API lm2_v2_f32 lm2_v2_lerp_f32(lm2_v2_f32 a, lm2_v2_f32 b, lm2_v2_f32 c);
LM2_API lm2_v2_f32 lm2_v2_smoothstep_f32(lm2_v2_f32 a, lm2_v2_f32 b, lm2_v2_f32 c);
LM2_API lm2_v2_f32 lm2_v2_alpha_f32(lm2_v2_f32 a, lm2_v2_f32 b, lm2_v2_f32 c);
LM2_API lm2_v2_f32 lm2_v2_make_f32(float x, float y);
LM2_API lm2_v2_f32 lm2_v2_splat_f32(float v);
LM2_API lm2_v2_f32 lm2_v2_zero_f32(void);

// =============================================================================
// lm2_v2_i64 Operations
// =============================================================================
LM2_API lm2_v2_i64 lm2_v2_add_i64(lm2_v2_i64 a, lm2_v2_i64 b);
LM2_API lm2_v2_i64 lm2_v2_sub_i64(lm2_v2_i64 a, lm2_v2_i64 b);
LM2_API lm2_v2_i64 lm2_v2_mul_i64(lm2_v2_i64 a, lm2_v2_i64 b);
LM2_API lm2_v2_i64 lm2_v2_div_i64(lm2_v2_i64 a, lm2_v2_i64 b);
LM2_API lm2_v2_i64 lm2_v2_add_s_i64(lm2_v2_i64 a, int64_t b);
LM2_API lm2_v2_i64 lm2_v2_sub_s_i64(lm2_v2_i64 a, int64_t b);
LM2_API lm2_v2_i64 lm2_v2_mul_s_i64(lm2_v2_i64 a, int64_t b);
LM2_API lm2_v2_i64 lm2_v2_div_s_i64(lm2_v2_i64 a, int64_t b);
LM2_API lm2_v2_i64 lm2_v2_neg_i64(lm2_v2_i64 a);
LM2_API lm2_v2_i64 lm2_v2_floor_i64(lm2_v2_i64 a);
LM2_API lm2_v2_i64 lm2_v2_ceil_i64(lm2_v2_i64 a);
LM2_API lm2_v2_i64 lm2_v2_round_i64(lm2_v2_i64 a);
LM2_API lm2_v2_i64 lm2_v2_trunc_i64(lm2_v2_i64 a);
LM2_API lm2_v2_i64 lm2_v2_abs_i64(lm2_v2_i64 a);
LM2_API lm2_v2_i64 lm2_v2_sign_i64(lm2_v2_i64 a);
LM2_API lm2_v2_i64 lm2_v2_sign0_i64(lm2_v2_i64 a);
LM2_API lm2_v2_i64 lm2_v2_saturate_i64(lm2_v2_i64 a);
LM2_API lm2_v2_i64 lm2_v2_fract_i64(lm2_v2_i64 a);
LM2_API lm2_v2_i64 lm2_v2_sqrt_i64(lm2_v2_i64 a);
LM2_API lm2_v2_i64 lm2_v2_floor_multiple_i64(lm2_v2_i64 a, lm2_v2_i64 b);
LM2_API lm2_v2_i64 lm2_v2_ceil_multiple_i64(lm2_v2_i64 a, lm2_v2_i64 b);
LM2_API lm2_v2_i64 lm2_v2_round_multiple_i64(lm2_v2_i64 a, lm2_v2_i64 b);
LM2_API lm2_v2_i64 lm2_v2_trunc_multiple_i64(lm2_v2_i64 a, lm2_v2_i64 b);
LM2_API lm2_v2_i64 lm2_v2_min_i64(lm2_v2_i64 a, lm2_v2_i64 b);
LM2_API lm2_v2_i64 lm2_v2_min_abs_i64(lm2_v2_i64 a, lm2_v2_i64 b);
LM2_API lm2_v2_i64 lm2_v2_max_i64(lm2_v2_i64 a, lm2_v2_i64 b);
LM2_API lm2_v2_i64 lm2_v2_max_abs_i64(lm2_v2_i64 a, lm2_v2_i64 b);
LM2_API lm2_v2_i64 lm2_v2_mod_i64(lm2_v2_i64 a, lm2_v2_i64 b);
LM2_API lm2_v2_i64 lm2_v2_pow_i64(lm2_v2_i64 a, lm2_v2_i64 b);
LM2_API lm2_v2_i64 lm2_v2_clamp_i64(lm2_v2_i64 a, lm2_v2_i64 b, lm2_v2_i64 c);
LM2_API lm2_v2_i64 lm2_v2_lerp_i64(lm2_v2_i64 a, lm2_v2_i64 b, lm2_v2_i64 c);
LM2_API lm2_v2_i64 lm2_v2_smoothstep_i64(lm2_v2_i64 a, lm2_v2_i64 b, lm2_v2_i64 c);
LM2_API lm2_v2_i64 lm2_v2_alpha_i64(lm2_v2_i64 a, lm2_v2_i64 b, lm2_v2_i64 c);
LM2_API lm2_v2_i64 lm2_v2_make_i64(int64_t x, int64_t y);
LM2_API lm2_v2_i64 lm2_v2_splat_i64(int64_t v);
LM2_API lm2_v2_i64 lm2_v2_zero_i64(void);

// =============================================================================
// lm2_v2_i32 Operations
// =============================================================================
LM2_API lm2_v2_i32 lm2_v2_add_i32(lm2_v2_i32 a, lm2_v2_i32 b);
LM2_API lm2_v2_i32 lm2_v2_sub_i32(lm2_v2_i32 a, lm2_v2_i32 b);
LM2_API lm2_v2_i32 lm2_v2_mul_i32(lm2_v2_i32 a, lm2_v2_i32 b);
LM2_API lm2_v2_i32 lm2_v2_div_i32(lm2_v2_i32 a, lm2_v2_i32 b);
LM2_API lm2_v2_i32 lm2_v2_add_s_i32(lm2_v2_i32 a, int32_t b);
LM2_API lm2_v2_i32 lm2_v2_sub_s_i32(lm2_v2_i32 a, int32_t b);
LM2_API lm2_v2_i32 lm2_v2_mul_s_i32(lm2_v2_i32 a, int32_t b);
LM2_API lm2_v2_i32 lm2_v2_div_s_i32(lm2_v2_i32 a, int32_t b);
LM2_API lm2_v2_i32 lm2_v2_neg_i32(lm2_v2_i32 a);
LM2_API lm2_v2_i32 lm2_v2_floor_i32(lm2_v2_i32 a);
LM2_API lm2_v2_i32 lm2_v2_ceil_i32(lm2_v2_i32 a);
LM2_API lm2_v2_i32 lm2_v2_round_i32(lm2_v2_i32 a);
LM2_API lm2_v2_i32 lm2_v2_trunc_i32(lm2_v2_i32 a);
LM2_API lm2_v2_i32 lm2_v2_abs_i32(lm2_v2_i32 a);
LM2_API lm2_v2_i32 lm2_v2_sign_i32(lm2_v2_i32 a);
LM2_API lm2_v2_i32 lm2_v2_sign0_i32(lm2_v2_i32 a);
LM2_API lm2_v2_i32 lm2_v2_saturate_i32(lm2_v2_i32 a);
LM2_API lm2_v2_i32 lm2_v2_fract_i32(lm2_v2_i32 a);
LM2_API lm2_v2_i32 lm2_v2_sqrt_i32(lm2_v2_i32 a);
LM2_API lm2_v2_i32 lm2_v2_floor_multiple_i32(lm2_v2_i32 a, lm2_v2_i32 b);
LM2_API lm2_v2_i32 lm2_v2_ceil_multiple_i32(lm2_v2_i32 a, lm2_v2_i32 b);
LM2_API lm2_v2_i32 lm2_v2_round_multiple_i32(lm2_v2_i32 a, lm2_v2_i32 b);
LM2_API lm2_v2_i32 lm2_v2_trunc_multiple_i32(lm2_v2_i32 a, lm2_v2_i32 b);
LM2_API lm2_v2_i32 lm2_v2_min_i32(lm2_v2_i32 a, lm2_v2_i32 b);
LM2_API lm2_v2_i32 lm2_v2_min_abs_i32(lm2_v2_i32 a, lm2_v2_i32 b);
LM2_API lm2_v2_i32 lm2_v2_max_i32(lm2_v2_i32 a, lm2_v2_i32 b);
LM2_API lm2_v2_i32 lm2_v2_max_abs_i32(lm2_v2_i32 a, lm2_v2_i32 b);
LM2_API lm2_v2_i32 lm2_v2_mod_i32(lm2_v2_i32 a, lm2_v2_i32 b);
LM2_API lm2_v2_i32 lm2_v2_pow_i32(lm2_v2_i32 a, lm2_v2_i32 b);
LM2_API lm2_v2_i32 lm2_v2_clamp_i32(lm2_v2_i32 a, lm2_v2_i32 b, lm2_v2_i32 c);
LM2_API lm2_v2_i32 lm2_v2_lerp_i32(lm2_v2_i32 a, lm2_v2_i32 b, lm2_v2_i32 c);
LM2_API lm2_v2_i32 lm2_v2_smoothstep_i32(lm2_v2_i32 a, lm2_v2_i32 b, lm2_v2_i32 c);
LM2_API lm2_v2_i32 lm2_v2_alpha_i32(lm2_v2_i32 a, lm2_v2_i32 b, lm2_v2_i32 c);
LM2_API lm2_v2_i32 lm2_v2_make_i32(int32_t x, int32_t y);
LM2_API lm2_v2_i32 lm2_v2_splat_i32(int32_t v);
LM2_API lm2_v2_i32 lm2_v2_zero_i32(void);

// =============================================================================
// lm2_v2_i16 Operations
// =============================================================================
LM2_API lm2_v2_i16 lm2_v2_add_i16(lm2_v2_i16 a, lm2_v2_i16 b);
LM2_API lm2_v2_i16 lm2_v2_sub_i16(lm2_v2_i16 a, lm2_v2_i16 b);
LM2_API lm2_v2_i16 lm2_v2_mul_i16(lm2_v2_i16 a, lm2_v2_i16 b);
LM2_API lm2_v2_i16 lm2_v2_div_i16(lm2_v2_i16 a, lm2_v2_i16 b);
LM2_API lm2_v2_i16 lm2_v2_add_s_i16(lm2_v2_i16 a, int16_t b);
LM2_API lm2_v2_i16 lm2_v2_sub_s_i16(lm2_v2_i16 a, int16_t b);
LM2_API lm2_v2_i16 lm2_v2_mul_s_i16(lm2_v2_i16 a, int16_t b);
LM2_API lm2_v2_i16 lm2_v2_div_s_i16(lm2_v2_i16 a, int16_t b);
LM2_API lm2_v2_i16 lm2_v2_neg_i16(lm2_v2_i16 a);
LM2_API lm2_v2_i16 lm2_v2_floor_i16(lm2_v2_i16 a);
LM2_API lm2_v2_i16 lm2_v2_ceil_i16(lm2_v2_i16 a);
LM2_API lm2_v2_i16 lm2_v2_round_i16(lm2_v2_i16 a);
LM2_API lm2_v2_i16 lm2_v2_trunc_i16(lm2_v2_i16 a);
LM2_API lm2_v2_i16 lm2_v2_abs_i16(lm2_v2_i16 a);
LM2_API lm2_v2_i16 lm2_v2_sign_i16(lm2_v2_i16 a);
LM2_API lm2_v2_i16 lm2_v2_sign0_i16(lm2_v2_i16 a);
LM2_API lm2_v2_i16 lm2_v2_saturate_i16(lm2_v2_i16 a);
LM2_API lm2_v2_i16 lm2_v2_fract_i16(lm2_v2_i16 a);
LM2_API lm2_v2_i16 lm2_v2_sqrt_i16(lm2_v2_i16 a);
LM2_API lm2_v2_i16 lm2_v2_floor_multiple_i16(lm2_v2_i16 a, lm2_v2_i16 b);
LM2_API lm2_v2_i16 lm2_v2_ceil_multiple_i16(lm2_v2_i16 a, lm2_v2_i16 b);
LM2_API lm2_v2_i16 lm2_v2_round_multiple_i16(lm2_v2_i16 a, lm2_v2_i16 b);
LM2_API lm2_v2_i16 lm2_v2_trunc_multiple_i16(lm2_v2_i16 a, lm2_v2_i16 b);
LM2_API lm2_v2_i16 lm2_v2_min_i16(lm2_v2_i16 a, lm2_v2_i16 b);
LM2_API lm2_v2_i16 lm2_v2_min_abs_i16(lm2_v2_i16 a, lm2_v2_i16 b);
LM2_API lm2_v2_i16 lm2_v2_max_i16(lm2_v2_i16 a, lm2_v2_i16 b);
LM2_API lm2_v2_i16 lm2_v2_max_abs_i16(lm2_v2_i16 a, lm2_v2_i16 b);
LM2_API lm2_v2_i16 lm2_v2_mod_i16(lm2_v2_i16 a, lm2_v2_i16 b);
LM2_API lm2_v2_i16 lm2_v2_pow_i16(lm2_v2_i16 a, lm2_v2_i16 b);
LM2_API lm2_v2_i16 lm2_v2_clamp_i16(lm2_v2_i16 a, lm2_v2_i16 b, lm2_v2_i16 c);
LM2_API lm2_v2_i16 lm2_v2_lerp_i16(lm2_v2_i16 a, lm2_v2_i16 b, lm2_v2_i16 c);
LM2_API lm2_v2_i16 lm2_v2_smoothstep_i16(lm2_v2_i16 a, lm2_v2_i16 b, lm2_v2_i16 c);
LM2_API lm2_v2_i16 lm2_v2_alpha_i16(lm2_v2_i16 a, lm2_v2_i16 b, lm2_v2_i16 c);
LM2_API lm2_v2_i16 lm2_v2_make_i16(int16_t x, int16_t y);
LM2_API lm2_v2_i16 lm2_v2_splat_i16(int16_t v);
LM2_API lm2_v2_i16 lm2_v2_zero_i16(void);

// =============================================================================
// lm2_v2_i8 Operations
// =============================================================================
LM2_API lm2_v2_i8 lm2_v2_add_i8(lm2_v2_i8 a, lm2_v2_i8 b);
LM2_API lm2_v2_i8 lm2_v2_sub_i8(lm2_v2_i8 a, lm2_v2_i8 b);
LM2_API lm2_v2_i8 lm2_v2_mul_i8(lm2_v2_i8 a, lm2_v2_i8 b);
LM2_API lm2_v2_i8 lm2_v2_div_i8(lm2_v2_i8 a, lm2_v2_i8 b);
LM2_API lm2_v2_i8 lm2_v2_add_s_i8(lm2_v2_i8 a, int8_t b);
LM2_API lm2_v2_i8 lm2_v2_sub_s_i8(lm2_v2_i8 a, int8_t b);
LM2_API lm2_v2_i8 lm2_v2_mul_s_i8(lm2_v2_i8 a, int8_t b);
LM2_API lm2_v2_i8 lm2_v2_div_s_i8(lm2_v2_i8 a, int8_t b);
LM2_API lm2_v2_i8 lm2_v2_neg_i8(lm2_v2_i8 a);
LM2_API lm2_v2_i8 lm2_v2_floor_i8(lm2_v2_i8 a);
LM2_API lm2_v2_i8 lm2_v2_ceil_i8(lm2_v2_i8 a);
LM2_API lm2_v2_i8 lm2_v2_round_i8(lm2_v2_i8 a);
LM2_API lm2_v2_i8 lm2_v2_trunc_i8(lm2_v2_i8 a);
LM2_API lm2_v2_i8 lm2_v2_abs_i8(lm2_v2_i8 a);
LM2_API lm2_v2_i8 lm2_v2_sign_i8(lm2_v2_i8 a);
LM2_API lm2_v2_i8 lm2_v2_sign0_i8(lm2_v2_i8 a);
LM2_API lm2_v2_i8 lm2_v2_saturate_i8(lm2_v2_i8 a);
LM2_API lm2_v2_i8 lm2_v2_fract_i8(lm2_v2_i8 a);
LM2_API lm2_v2_i8 lm2_v2_sqrt_i8(lm2_v2_i8 a);
LM2_API lm2_v2_i8 lm2_v2_floor_multiple_i8(lm2_v2_i8 a, lm2_v2_i8 b);
LM2_API lm2_v2_i8 lm2_v2_ceil_multiple_i8(lm2_v2_i8 a, lm2_v2_i8 b);
LM2_API lm2_v2_i8 lm2_v2_round_multiple_i8(lm2_v2_i8 a, lm2_v2_i8 b);
LM2_API lm2_v2_i8 lm2_v2_trunc_multiple_i8(lm2_v2_i8 a, lm2_v2_i8 b);
LM2_API lm2_v2_i8 lm2_v2_min_i8(lm2_v2_i8 a, lm2_v2_i8 b);
LM2_API lm2_v2_i8 lm2_v2_min_abs_i8(lm2_v2_i8 a, lm2_v2_i8 b);
LM2_API lm2_v2_i8 lm2_v2_max_i8(lm2_v2_i8 a, lm2_v2_i8 b);
LM2_API lm2_v2_i8 lm2_v2_max_abs_i8(lm2_v2_i8 a, lm2_v2_i8 b);
LM2_API lm2_v2_i8 lm2_v2_mod_i8(lm2_v2_i8 a, lm2_v2_i8 b);
LM2_API lm2_v2_i8 lm2_v2_pow_i8(lm2_v2_i8 a, lm2_v2_i8 b);
LM2_API lm2_v2_i8 lm2_v2_clamp_i8(lm2_v2_i8 a, lm2_v2_i8 b, lm2_v2_i8 c);
LM2_API lm2_v2_i8 lm2_v2_lerp_i8(lm2_v2_i8 a, lm2_v2_i8 b, lm2_v2_i8 c);
LM2_API lm2_v2_i8 lm2_v2_smoothstep_i8(lm2_v2_i8 a, lm2_v2_i8 b, lm2_v2_i8 c);
LM2_API lm2_v2_i8 lm2_v2_alpha_i8(lm2_v2_i8 a, lm2_v2_i8 b, lm2_v2_i8 c);
LM2_API lm2_v2_i8 lm2_v2_make_i8(int8_t x, int8_t y);
LM2_API lm2_v2_i8 lm2_v2_splat_i8(int8_t v);
LM2_API lm2_v2_i8 lm2_v2_zero_i8(void);

// =============================================================================
// lm2_v2_u64 Operations
// =============================================================================
LM2_API lm2_v2_u64 lm2_v2_add_u64(lm2_v2_u64 a, lm2_v2_u64 b);
LM2_API lm2_v2_u64 lm2_v2_sub_u64(lm2_v2_u64 a, lm2_v2_u64 b);
LM2_API lm2_v2_u64 lm2_v2_mul_u64(lm2_v2_u64 a, lm2_v2_u64 b);
LM2_API lm2_v2_u64 lm2_v2_div_u64(lm2_v2_u64 a, lm2_v2_u64 b);
LM2_API lm2_v2_u64 lm2_v2_add_s_u64(lm2_v2_u64 a, uint64_t b);
LM2_API lm2_v2_u64 lm2_v2_sub_s_u64(lm2_v2_u64 a, uint64_t b);
LM2_API lm2_v2_u64 lm2_v2_mul_s_u64(lm2_v2_u64 a, uint64_t b);
LM2_API lm2_v2_u64 lm2_v2_div_s_u64(lm2_v2_u64 a, uint64_t b);
LM2_API lm2_v2_u64 lm2_v2_neg_u64(lm2_v2_u64 a);
LM2_API lm2_v2_u64 lm2_v2_floor_u64(lm2_v2_u64 a);
LM2_API lm2_v2_u64 lm2_v2_ceil_u64(lm2_v2_u64 a);
LM2_API lm2_v2_u64 lm2_v2_round_u64(lm2_v2_u64 a);
LM2_API lm2_v2_u64 lm2_v2_trunc_u64(lm2_v2_u64 a);
LM2_API lm2_v2_u64 lm2_v2_abs_u64(lm2_v2_u64 a);
LM2_API lm2_v2_u64 lm2_v2_sign_u64(lm2_v2_u64 a);
LM2_API lm2_v2_u64 lm2_v2_sign0_u64(lm2_v2_u64 a);
LM2_API lm2_v2_u64 lm2_v2_saturate_u64(lm2_v2_u64 a);
LM2_API lm2_v2_u64 lm2_v2_fract_u64(lm2_v2_u64 a);
LM2_API lm2_v2_u64 lm2_v2_sqrt_u64(lm2_v2_u64 a);
LM2_API lm2_v2_u64 lm2_v2_floor_multiple_u64(lm2_v2_u64 a, lm2_v2_u64 b);
LM2_API lm2_v2_u64 lm2_v2_ceil_multiple_u64(lm2_v2_u64 a, lm2_v2_u64 b);
LM2_API lm2_v2_u64 lm2_v2_round_multiple_u64(lm2_v2_u64 a, lm2_v2_u64 b);
LM2_API lm2_v2_u64 lm2_v2_trunc_multiple_u64(lm2_v2_u64 a, lm2_v2_u64 b);
LM2_API lm2_v2_u64 lm2_v2_min_u64(lm2_v2_u64 a, lm2_v2_u64 b);
LM2_API lm2_v2_u64 lm2_v2_min_abs_u64(lm2_v2_u64 a, lm2_v2_u64 b);
LM2_API lm2_v2_u64 lm2_v2_max_u64(lm2_v2_u64 a, lm2_v2_u64 b);
LM2_API lm2_v2_u64 lm2_v2_max_abs_u64(lm2_v2_u64 a, lm2_v2_u64 b);
LM2_API lm2_v2_u64 lm2_v2_mod_u64(lm2_v2_u64 a, lm2_v2_u64 b);
LM2_API lm2_v2_u64 lm2_v2_pow_u64(lm2_v2_u64 a, lm2_v2_u64 b);
LM2_API lm2_v2_u64 lm2_v2_clamp_u64(lm2_v2_u64 a, lm2_v2_u64 b, lm2_v2_u64 c);
LM2_API lm2_v2_u64 lm2_v2_lerp_u64(lm2_v2_u64 a, lm2_v2_u64 b, lm2_v2_u64 c);
LM2_API lm2_v2_u64 lm2_v2_smoothstep_u64(lm2_v2_u64 a, lm2_v2_u64 b, lm2_v2_u64 c);
LM2_API lm2_v2_u64 lm2_v2_alpha_u64(lm2_v2_u64 a, lm2_v2_u64 b, lm2_v2_u64 c);
LM2_API lm2_v2_u64 lm2_v2_make_u64(uint64_t x, uint64_t y);
LM2_API lm2_v2_u64 lm2_v2_splat_u64(uint64_t v);
LM2_API lm2_v2_u64 lm2_v2_zero_u64(void);

// =============================================================================
// lm2_v2_u32 Operations
// =============================================================================
LM2_API lm2_v2_u32 lm2_v2_add_u32(lm2_v2_u32 a, lm2_v2_u32 b);
LM2_API lm2_v2_u32 lm2_v2_sub_u32(lm2_v2_u32 a, lm2_v2_u32 b);
LM2_API lm2_v2_u32 lm2_v2_mul_u32(lm2_v2_u32 a, lm2_v2_u32 b);
LM2_API lm2_v2_u32 lm2_v2_div_u32(lm2_v2_u32 a, lm2_v2_u32 b);
LM2_API lm2_v2_u32 lm2_v2_add_s_u32(lm2_v2_u32 a, uint32_t b);
LM2_API lm2_v2_u32 lm2_v2_sub_s_u32(lm2_v2_u32 a, uint32_t b);
LM2_API lm2_v2_u32 lm2_v2_mul_s_u32(lm2_v2_u32 a, uint32_t b);
LM2_API lm2_v2_u32 lm2_v2_div_s_u32(lm2_v2_u32 a, uint32_t b);
LM2_API lm2_v2_u32 lm2_v2_neg_u32(lm2_v2_u32 a);
LM2_API lm2_v2_u32 lm2_v2_floor_u32(lm2_v2_u32 a);
LM2_API lm2_v2_u32 lm2_v2_ceil_u32(lm2_v2_u32 a);
LM2_API lm2_v2_u32 lm2_v2_round_u32(lm2_v2_u32 a);
LM2_API lm2_v2_u32 lm2_v2_trunc_u32(lm2_v2_u32 a);
LM2_API lm2_v2_u32 lm2_v2_abs_u32(lm2_v2_u32 a);
LM2_API lm2_v2_u32 lm2_v2_sign_u32(lm2_v2_u32 a);
LM2_API lm2_v2_u32 lm2_v2_sign0_u32(lm2_v2_u32 a);
LM2_API lm2_v2_u32 lm2_v2_saturate_u32(lm2_v2_u32 a);
LM2_API lm2_v2_u32 lm2_v2_fract_u32(lm2_v2_u32 a);
LM2_API lm2_v2_u32 lm2_v2_sqrt_u32(lm2_v2_u32 a);
LM2_API lm2_v2_u32 lm2_v2_floor_multiple_u32(lm2_v2_u32 a, lm2_v2_u32 b);
LM2_API lm2_v2_u32 lm2_v2_ceil_multiple_u32(lm2_v2_u32 a, lm2_v2_u32 b);
LM2_API lm2_v2_u32 lm2_v2_round_multiple_u32(lm2_v2_u32 a, lm2_v2_u32 b);
LM2_API lm2_v2_u32 lm2_v2_trunc_multiple_u32(lm2_v2_u32 a, lm2_v2_u32 b);
LM2_API lm2_v2_u32 lm2_v2_min_u32(lm2_v2_u32 a, lm2_v2_u32 b);
LM2_API lm2_v2_u32 lm2_v2_min_abs_u32(lm2_v2_u32 a, lm2_v2_u32 b);
LM2_API lm2_v2_u32 lm2_v2_max_u32(lm2_v2_u32 a, lm2_v2_u32 b);
LM2_API lm2_v2_u32 lm2_v2_max_abs_u32(lm2_v2_u32 a, lm2_v2_u32 b);
LM2_API lm2_v2_u32 lm2_v2_mod_u32(lm2_v2_u32 a, lm2_v2_u32 b);
LM2_API lm2_v2_u32 lm2_v2_pow_u32(lm2_v2_u32 a, lm2_v2_u32 b);
LM2_API lm2_v2_u32 lm2_v2_clamp_u32(lm2_v2_u32 a, lm2_v2_u32 b, lm2_v2_u32 c);
LM2_API lm2_v2_u32 lm2_v2_lerp_u32(lm2_v2_u32 a, lm2_v2_u32 b, lm2_v2_u32 c);
LM2_API lm2_v2_u32 lm2_v2_smoothstep_u32(lm2_v2_u32 a, lm2_v2_u32 b, lm2_v2_u32 c);
LM2_API lm2_v2_u32 lm2_v2_alpha_u32(lm2_v2_u32 a, lm2_v2_u32 b, lm2_v2_u32 c);
LM2_API lm2_v2_u32 lm2_v2_make_u32(uint32_t x, uint32_t y);
LM2_API lm2_v2_u32 lm2_v2_splat_u32(uint32_t v);
LM2_API lm2_v2_u32 lm2_v2_zero_u32(void);

// =============================================================================
// lm2_v2_u16 Operations
// =============================================================================
LM2_API lm2_v2_u16 lm2_v2_add_u16(lm2_v2_u16 a, lm2_v2_u16 b);
LM2_API lm2_v2_u16 lm2_v2_sub_u16(lm2_v2_u16 a, lm2_v2_u16 b);
LM2_API lm2_v2_u16 lm2_v2_mul_u16(lm2_v2_u16 a, lm2_v2_u16 b);
LM2_API lm2_v2_u16 lm2_v2_div_u16(lm2_v2_u16 a, lm2_v2_u16 b);
LM2_API lm2_v2_u16 lm2_v2_add_s_u16(lm2_v2_u16 a, uint16_t b);
LM2_API lm2_v2_u16 lm2_v2_sub_s_u16(lm2_v2_u16 a, uint16_t b);
LM2_API lm2_v2_u16 lm2_v2_mul_s_u16(lm2_v2_u16 a, uint16_t b);
LM2_API lm2_v2_u16 lm2_v2_div_s_u16(lm2_v2_u16 a, uint16_t b);
LM2_API lm2_v2_u16 lm2_v2_neg_u16(lm2_v2_u16 a);
LM2_API lm2_v2_u16 lm2_v2_floor_u16(lm2_v2_u16 a);
LM2_API lm2_v2_u16 lm2_v2_ceil_u16(lm2_v2_u16 a);
LM2_API lm2_v2_u16 lm2_v2_round_u16(lm2_v2_u16 a);
LM2_API lm2_v2_u16 lm2_v2_trunc_u16(lm2_v2_u16 a);
LM2_API lm2_v2_u16 lm2_v2_abs_u16(lm2_v2_u16 a);
LM2_API lm2_v2_u16 lm2_v2_sign_u16(lm2_v2_u16 a);
LM2_API lm2_v2_u16 lm2_v2_sign0_u16(lm2_v2_u16 a);
LM2_API lm2_v2_u16 lm2_v2_saturate_u16(lm2_v2_u16 a);
LM2_API lm2_v2_u16 lm2_v2_fract_u16(lm2_v2_u16 a);
LM2_API lm2_v2_u16 lm2_v2_sqrt_u16(lm2_v2_u16 a);
LM2_API lm2_v2_u16 lm2_v2_floor_multiple_u16(lm2_v2_u16 a, lm2_v2_u16 b);
LM2_API lm2_v2_u16 lm2_v2_ceil_multiple_u16(lm2_v2_u16 a, lm2_v2_u16 b);
LM2_API lm2_v2_u16 lm2_v2_round_multiple_u16(lm2_v2_u16 a, lm2_v2_u16 b);
LM2_API lm2_v2_u16 lm2_v2_trunc_multiple_u16(lm2_v2_u16 a, lm2_v2_u16 b);
LM2_API lm2_v2_u16 lm2_v2_min_u16(lm2_v2_u16 a, lm2_v2_u16 b);
LM2_API lm2_v2_u16 lm2_v2_min_abs_u16(lm2_v2_u16 a, lm2_v2_u16 b);
LM2_API lm2_v2_u16 lm2_v2_max_u16(lm2_v2_u16 a, lm2_v2_u16 b);
LM2_API lm2_v2_u16 lm2_v2_max_abs_u16(lm2_v2_u16 a, lm2_v2_u16 b);
LM2_API lm2_v2_u16 lm2_v2_mod_u16(lm2_v2_u16 a, lm2_v2_u16 b);
LM2_API lm2_v2_u16 lm2_v2_pow_u16(lm2_v2_u16 a, lm2_v2_u16 b);
LM2_API lm2_v2_u16 lm2_v2_clamp_u16(lm2_v2_u16 a, lm2_v2_u16 b, lm2_v2_u16 c);
LM2_API lm2_v2_u16 lm2_v2_lerp_u16(lm2_v2_u16 a, lm2_v2_u16 b, lm2_v2_u16 c);
LM2_API lm2_v2_u16 lm2_v2_smoothstep_u16(lm2_v2_u16 a, lm2_v2_u16 b, lm2_v2_u16 c);
LM2_API lm2_v2_u16 lm2_v2_alpha_u16(lm2_v2_u16 a, lm2_v2_u16 b, lm2_v2_u16 c);
LM2_API lm2_v2_u16 lm2_v2_make_u16(uint16_t x, uint16_t y);
LM2_API lm2_v2_u16 lm2_v2_splat_u16(uint16_t v);
LM2_API lm2_v2_u16 lm2_v2_zero_u16(void);

// =============================================================================
// lm2_v2_u8 Operations
// =============================================================================
LM2_API lm2_v2_u8 lm2_v2_add_u8(lm2_v2_u8 a, lm2_v2_u8 b);
LM2_API lm2_v2_u8 lm2_v2_sub_u8(lm2_v2_u8 a, lm2_v2_u8 b);
LM2_API lm2_v2_u8 lm2_v2_mul_u8(lm2_v2_u8 a, lm2_v2_u8 b);
LM2_API lm2_v2_u8 lm2_v2_div_u8(lm2_v2_u8 a, lm2_v2_u8 b);
LM2_API lm2_v2_u8 lm2_v2_add_s_u8(lm2_v2_u8 a, uint8_t b);
LM2_API lm2_v2_u8 lm2_v2_sub_s_u8(lm2_v2_u8 a, uint8_t b);
LM2_API lm2_v2_u8 lm2_v2_mul_s_u8(lm2_v2_u8 a, uint8_t b);
LM2_API lm2_v2_u8 lm2_v2_div_s_u8(lm2_v2_u8 a, uint8_t b);
LM2_API lm2_v2_u8 lm2_v2_neg_u8(lm2_v2_u8 a);
LM2_API lm2_v2_u8 lm2_v2_floor_u8(lm2_v2_u8 a);
LM2_API lm2_v2_u8 lm2_v2_ceil_u8(lm2_v2_u8 a);
LM2_API lm2_v2_u8 lm2_v2_round_u8(lm2_v2_u8 a);
LM2_API lm2_v2_u8 lm2_v2_trunc_u8(lm2_v2_u8 a);
LM2_API lm2_v2_u8 lm2_v2_abs_u8(lm2_v2_u8 a);
LM2_API lm2_v2_u8 lm2_v2_sign_u8(lm2_v2_u8 a);
LM2_API lm2_v2_u8 lm2_v2_sign0_u8(lm2_v2_u8 a);
LM2_API lm2_v2_u8 lm2_v2_saturate_u8(lm2_v2_u8 a);
LM2_API lm2_v2_u8 lm2_v2_fract_u8(lm2_v2_u8 a);
LM2_API lm2_v2_u8 lm2_v2_sqrt_u8(lm2_v2_u8 a);
LM2_API lm2_v2_u8 lm2_v2_floor_multiple_u8(lm2_v2_u8 a, lm2_v2_u8 b);
LM2_API lm2_v2_u8 lm2_v2_ceil_multiple_u8(lm2_v2_u8 a, lm2_v2_u8 b);
LM2_API lm2_v2_u8 lm2_v2_round_multiple_u8(lm2_v2_u8 a, lm2_v2_u8 b);
LM2_API lm2_v2_u8 lm2_v2_trunc_multiple_u8(lm2_v2_u8 a, lm2_v2_u8 b);
LM2_API lm2_v2_u8 lm2_v2_min_u8(lm2_v2_u8 a, lm2_v2_u8 b);
LM2_API lm2_v2_u8 lm2_v2_min_abs_u8(lm2_v2_u8 a, lm2_v2_u8 b);
LM2_API lm2_v2_u8 lm2_v2_max_u8(lm2_v2_u8 a, lm2_v2_u8 b);
LM2_API lm2_v2_u8 lm2_v2_max_abs_u8(lm2_v2_u8 a, lm2_v2_u8 b);
LM2_API lm2_v2_u8 lm2_v2_mod_u8(lm2_v2_u8 a, lm2_v2_u8 b);
LM2_API lm2_v2_u8 lm2_v2_pow_u8(lm2_v2_u8 a, lm2_v2_u8 b);
LM2_API lm2_v2_u8 lm2_v2_clamp_u8(lm2_v2_u8 a, lm2_v2_u8 b, lm2_v2_u8 c);
LM2_API lm2_v2_u8 lm2_v2_lerp_u8(lm2_v2_u8 a, lm2_v2_u8 b, lm2_v2_u8 c);
LM2_API lm2_v2_u8 lm2_v2_smoothstep_u8(lm2_v2_u8 a, lm2_v2_u8 b, lm2_v2_u8 c);
LM2_API lm2_v2_u8 lm2_v2_alpha_u8(lm2_v2_u8 a, lm2_v2_u8 b, lm2_v2_u8 c);
LM2_API lm2_v2_u8 lm2_v2_make_u8(uint8_t x, uint8_t y);
LM2_API lm2_v2_u8 lm2_v2_splat_u8(uint8_t v);
LM2_API lm2_v2_u8 lm2_v2_zero_u8(void);

// =============================================================================
// Type Alias
// =============================================================================
// Default vector type (32-bit float)
typedef lm2_v2_f32 lm2_v2;

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// C++ operator overloads (must be outside extern "C")
#ifndef LM2_NO_CPP_OPERATORS
#  include "lm2_vector_operators.h"
_LM2_DEFINE_V2_OPERATORS(lm2_v2_f64, double, f64)
_LM2_DEFINE_V2_OPERATORS(lm2_v2_f32, float, f32)
_LM2_DEFINE_V2_OPERATORS(lm2_v2_i64, int64_t, i64)
_LM2_DEFINE_V2_OPERATORS(lm2_v2_i32, int32_t, i32)
_LM2_DEFINE_V2_OPERATORS(lm2_v2_i16, int16_t, i16)
_LM2_DEFINE_V2_OPERATORS(lm2_v2_i8, int8_t, i8)
_LM2_DEFINE_V2_OPERATORS(lm2_v2_u64, uint64_t, u64)
_LM2_DEFINE_V2_OPERATORS(lm2_v2_u32, uint32_t, u32)
_LM2_DEFINE_V2_OPERATORS(lm2_v2_u16, uint16_t, u16)
_LM2_DEFINE_V2_OPERATORS(lm2_v2_u8, uint8_t, u8)
#endif
