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
// 3D Vector Type Definitions
// =============================================================================

// lm2_v3f64 - 64-bit floating-point 3D vector
typedef union lm2_v3f64 {
  double e[3];
  struct {
    double x, y, z;
  };
  struct {
    double s, t, r;
  };
  _LM2_VECTOR_SUBSCRIPT_OP(double, 3)
} lm2_v3f64;

// lm2_v3f32 - 32-bit floating-point 3D vector
typedef union lm2_v3f32 {
  float e[3];
  struct {
    float x, y, z;
  };
  struct {
    float s, t, r;
  };
  _LM2_VECTOR_SUBSCRIPT_OP(float, 3)
} lm2_v3f32;

// lm2_v3i64 - 64-bit signed integer 3D vector
typedef union lm2_v3i64 {
  int64_t e[3];
  struct {
    int64_t x, y, z;
  };
  struct {
    int64_t s, t, r;
  };
  _LM2_VECTOR_SUBSCRIPT_OP(int64_t, 3)
} lm2_v3i64;

// lm2_v3i32 - 32-bit signed integer 3D vector
typedef union lm2_v3i32 {
  int32_t e[3];
  struct {
    int32_t x, y, z;
  };
  struct {
    int32_t s, t, r;
  };
  _LM2_VECTOR_SUBSCRIPT_OP(int32_t, 3)
} lm2_v3i32;

// lm2_v3i16 - 16-bit signed integer 3D vector
typedef union lm2_v3i16 {
  int16_t e[3];
  struct {
    int16_t x, y, z;
  };
  struct {
    int16_t s, t, r;
  };
  _LM2_VECTOR_SUBSCRIPT_OP(int16_t, 3)
} lm2_v3i16;

// lm2_v3i8 - 8-bit signed integer 3D vector
typedef union lm2_v3i8 {
  int8_t e[3];
  struct {
    int8_t x, y, z;
  };
  struct {
    int8_t s, t, r;
  };
  _LM2_VECTOR_SUBSCRIPT_OP(int8_t, 3)
} lm2_v3i8;

// lm2_v3u64 - 64-bit unsigned integer 3D vector
typedef union lm2_v3u64 {
  uint64_t e[3];
  struct {
    uint64_t x, y, z;
  };
  struct {
    uint64_t s, t, r;
  };
  _LM2_VECTOR_SUBSCRIPT_OP(uint64_t, 3)
} lm2_v3u64;

// lm2_v3u32 - 32-bit unsigned integer 3D vector
typedef union lm2_v3u32 {
  uint32_t e[3];
  struct {
    uint32_t x, y, z;
  };
  struct {
    uint32_t s, t, r;
  };
  _LM2_VECTOR_SUBSCRIPT_OP(uint32_t, 3)
} lm2_v3u32;

// lm2_v3u16 - 16-bit unsigned integer 3D vector
typedef union lm2_v3u16 {
  uint16_t e[3];
  struct {
    uint16_t x, y, z;
  };
  struct {
    uint16_t s, t, r;
  };
  _LM2_VECTOR_SUBSCRIPT_OP(uint16_t, 3)
} lm2_v3u16;

// lm2_v3u8 - 8-bit unsigned integer 3D vector
typedef union lm2_v3u8 {
  uint8_t e[3];
  struct {
    uint8_t x, y, z;
  };
  struct {
    uint8_t s, t, r;
  };
  _LM2_VECTOR_SUBSCRIPT_OP(uint8_t, 3)
} lm2_v3u8;

// =============================================================================
// lm2_v3f64 Operations
// =============================================================================
LM2_API lm2_v3f64 lm2_add_lm2_v3f64(lm2_v3f64 a, lm2_v3f64 b);
LM2_API lm2_v3f64 lm2_sub_lm2_v3f64(lm2_v3f64 a, lm2_v3f64 b);
LM2_API lm2_v3f64 lm2_mul_lm2_v3f64(lm2_v3f64 a, lm2_v3f64 b);
LM2_API lm2_v3f64 lm2_div_lm2_v3f64(lm2_v3f64 a, lm2_v3f64 b);
LM2_API lm2_v3f64 lm2_add_lm2_v3f64_double(lm2_v3f64 a, double b);
LM2_API lm2_v3f64 lm2_sub_lm2_v3f64_double(lm2_v3f64 a, double b);
LM2_API lm2_v3f64 lm2_mul_lm2_v3f64_double(lm2_v3f64 a, double b);
LM2_API lm2_v3f64 lm2_div_lm2_v3f64_double(lm2_v3f64 a, double b);
LM2_API lm2_v3f64 lm2_neg_lm2_v3f64(lm2_v3f64 a);
LM2_API lm2_v3f64 lm2_floor_lm2_v3f64(lm2_v3f64 a);
LM2_API lm2_v3f64 lm2_ceil_lm2_v3f64(lm2_v3f64 a);
LM2_API lm2_v3f64 lm2_round_lm2_v3f64(lm2_v3f64 a);
LM2_API lm2_v3f64 lm2_trunc_lm2_v3f64(lm2_v3f64 a);
LM2_API lm2_v3f64 lm2_abs_lm2_v3f64(lm2_v3f64 a);
LM2_API lm2_v3f64 lm2_sign_lm2_v3f64(lm2_v3f64 a);
LM2_API lm2_v3f64 lm2_sign0_lm2_v3f64(lm2_v3f64 a);
LM2_API lm2_v3f64 lm2_saturate_lm2_v3f64(lm2_v3f64 a);
LM2_API lm2_v3f64 lm2_fract_lm2_v3f64(lm2_v3f64 a);
LM2_API lm2_v3f64 lm2_norm_lm2_v3f64(lm2_v3f64 a);
LM2_API lm2_v3f64 lm2_sqrt_lm2_v3f64(lm2_v3f64 a);
LM2_API lm2_v3f64 lm2_floor_multiple_lm2_v3f64(lm2_v3f64 a, lm2_v3f64 b);
LM2_API lm2_v3f64 lm2_ceil_multiple_lm2_v3f64(lm2_v3f64 a, lm2_v3f64 b);
LM2_API lm2_v3f64 lm2_round_multiple_lm2_v3f64(lm2_v3f64 a, lm2_v3f64 b);
LM2_API lm2_v3f64 lm2_trunc_multiple_lm2_v3f64(lm2_v3f64 a, lm2_v3f64 b);
LM2_API lm2_v3f64 lm2_min_lm2_v3f64(lm2_v3f64 a, lm2_v3f64 b);
LM2_API lm2_v3f64 lm2_min_abs_lm2_v3f64(lm2_v3f64 a, lm2_v3f64 b);
LM2_API lm2_v3f64 lm2_max_lm2_v3f64(lm2_v3f64 a, lm2_v3f64 b);
LM2_API lm2_v3f64 lm2_max_abs_lm2_v3f64(lm2_v3f64 a, lm2_v3f64 b);
LM2_API lm2_v3f64 lm2_mod_lm2_v3f64(lm2_v3f64 a, lm2_v3f64 b);
LM2_API lm2_v3f64 lm2_pow_lm2_v3f64(lm2_v3f64 a, lm2_v3f64 b);
LM2_API lm2_v3f64 lm2_clamp_lm2_v3f64(lm2_v3f64 a, lm2_v3f64 b, lm2_v3f64 c);
LM2_API lm2_v3f64 lm2_lerp_lm2_v3f64(lm2_v3f64 a, lm2_v3f64 b, lm2_v3f64 c);
LM2_API lm2_v3f64 lm2_smoothstep_lm2_v3f64(lm2_v3f64 a, lm2_v3f64 b, lm2_v3f64 c);
LM2_API lm2_v3f64 lm2_alpha_lm2_v3f64(lm2_v3f64 a, lm2_v3f64 b, lm2_v3f64 c);
LM2_API lm2_v3f64 lm2_v3f64_make(double x, double y, double z);
LM2_API lm2_v3f64 lm2_v3f64_splat(double v);
LM2_API lm2_v3f64 lm2_v3f64_zero(void);

// =============================================================================
// lm2_v3f32 Operations
// =============================================================================
LM2_API lm2_v3f32 lm2_add_lm2_v3f32(lm2_v3f32 a, lm2_v3f32 b);
LM2_API lm2_v3f32 lm2_sub_lm2_v3f32(lm2_v3f32 a, lm2_v3f32 b);
LM2_API lm2_v3f32 lm2_mul_lm2_v3f32(lm2_v3f32 a, lm2_v3f32 b);
LM2_API lm2_v3f32 lm2_div_lm2_v3f32(lm2_v3f32 a, lm2_v3f32 b);
LM2_API lm2_v3f32 lm2_add_lm2_v3f32_float(lm2_v3f32 a, float b);
LM2_API lm2_v3f32 lm2_sub_lm2_v3f32_float(lm2_v3f32 a, float b);
LM2_API lm2_v3f32 lm2_mul_lm2_v3f32_float(lm2_v3f32 a, float b);
LM2_API lm2_v3f32 lm2_div_lm2_v3f32_float(lm2_v3f32 a, float b);
LM2_API lm2_v3f32 lm2_neg_lm2_v3f32(lm2_v3f32 a);
LM2_API lm2_v3f32 lm2_floor_lm2_v3f32(lm2_v3f32 a);
LM2_API lm2_v3f32 lm2_ceil_lm2_v3f32(lm2_v3f32 a);
LM2_API lm2_v3f32 lm2_round_lm2_v3f32(lm2_v3f32 a);
LM2_API lm2_v3f32 lm2_trunc_lm2_v3f32(lm2_v3f32 a);
LM2_API lm2_v3f32 lm2_abs_lm2_v3f32(lm2_v3f32 a);
LM2_API lm2_v3f32 lm2_sign_lm2_v3f32(lm2_v3f32 a);
LM2_API lm2_v3f32 lm2_sign0_lm2_v3f32(lm2_v3f32 a);
LM2_API lm2_v3f32 lm2_saturate_lm2_v3f32(lm2_v3f32 a);
LM2_API lm2_v3f32 lm2_fract_lm2_v3f32(lm2_v3f32 a);
LM2_API lm2_v3f32 lm2_norm_lm2_v3f32(lm2_v3f32 a);
LM2_API lm2_v3f32 lm2_sqrt_lm2_v3f32(lm2_v3f32 a);
LM2_API lm2_v3f32 lm2_floor_multiple_lm2_v3f32(lm2_v3f32 a, lm2_v3f32 b);
LM2_API lm2_v3f32 lm2_ceil_multiple_lm2_v3f32(lm2_v3f32 a, lm2_v3f32 b);
LM2_API lm2_v3f32 lm2_round_multiple_lm2_v3f32(lm2_v3f32 a, lm2_v3f32 b);
LM2_API lm2_v3f32 lm2_trunc_multiple_lm2_v3f32(lm2_v3f32 a, lm2_v3f32 b);
LM2_API lm2_v3f32 lm2_min_lm2_v3f32(lm2_v3f32 a, lm2_v3f32 b);
LM2_API lm2_v3f32 lm2_min_abs_lm2_v3f32(lm2_v3f32 a, lm2_v3f32 b);
LM2_API lm2_v3f32 lm2_max_lm2_v3f32(lm2_v3f32 a, lm2_v3f32 b);
LM2_API lm2_v3f32 lm2_max_abs_lm2_v3f32(lm2_v3f32 a, lm2_v3f32 b);
LM2_API lm2_v3f32 lm2_mod_lm2_v3f32(lm2_v3f32 a, lm2_v3f32 b);
LM2_API lm2_v3f32 lm2_pow_lm2_v3f32(lm2_v3f32 a, lm2_v3f32 b);
LM2_API lm2_v3f32 lm2_clamp_lm2_v3f32(lm2_v3f32 a, lm2_v3f32 b, lm2_v3f32 c);
LM2_API lm2_v3f32 lm2_lerp_lm2_v3f32(lm2_v3f32 a, lm2_v3f32 b, lm2_v3f32 c);
LM2_API lm2_v3f32 lm2_smoothstep_lm2_v3f32(lm2_v3f32 a, lm2_v3f32 b, lm2_v3f32 c);
LM2_API lm2_v3f32 lm2_alpha_lm2_v3f32(lm2_v3f32 a, lm2_v3f32 b, lm2_v3f32 c);
LM2_API lm2_v3f32 lm2_v3f32_make(float x, float y, float z);
LM2_API lm2_v3f32 lm2_v3f32_splat(float v);
LM2_API lm2_v3f32 lm2_v3f32_zero(void);

// =============================================================================
// lm2_v3i64 Operations
// =============================================================================
LM2_API lm2_v3i64 lm2_add_lm2_v3i64(lm2_v3i64 a, lm2_v3i64 b);
LM2_API lm2_v3i64 lm2_sub_lm2_v3i64(lm2_v3i64 a, lm2_v3i64 b);
LM2_API lm2_v3i64 lm2_mul_lm2_v3i64(lm2_v3i64 a, lm2_v3i64 b);
LM2_API lm2_v3i64 lm2_div_lm2_v3i64(lm2_v3i64 a, lm2_v3i64 b);
LM2_API lm2_v3i64 lm2_add_lm2_v3i64_int64_t(lm2_v3i64 a, int64_t b);
LM2_API lm2_v3i64 lm2_sub_lm2_v3i64_int64_t(lm2_v3i64 a, int64_t b);
LM2_API lm2_v3i64 lm2_mul_lm2_v3i64_int64_t(lm2_v3i64 a, int64_t b);
LM2_API lm2_v3i64 lm2_div_lm2_v3i64_int64_t(lm2_v3i64 a, int64_t b);
LM2_API lm2_v3i64 lm2_neg_lm2_v3i64(lm2_v3i64 a);
LM2_API lm2_v3i64 lm2_floor_lm2_v3i64(lm2_v3i64 a);
LM2_API lm2_v3i64 lm2_ceil_lm2_v3i64(lm2_v3i64 a);
LM2_API lm2_v3i64 lm2_round_lm2_v3i64(lm2_v3i64 a);
LM2_API lm2_v3i64 lm2_trunc_lm2_v3i64(lm2_v3i64 a);
LM2_API lm2_v3i64 lm2_abs_lm2_v3i64(lm2_v3i64 a);
LM2_API lm2_v3i64 lm2_sign_lm2_v3i64(lm2_v3i64 a);
LM2_API lm2_v3i64 lm2_sign0_lm2_v3i64(lm2_v3i64 a);
LM2_API lm2_v3i64 lm2_saturate_lm2_v3i64(lm2_v3i64 a);
LM2_API lm2_v3i64 lm2_fract_lm2_v3i64(lm2_v3i64 a);
LM2_API lm2_v3i64 lm2_norm_lm2_v3i64(lm2_v3i64 a);
LM2_API lm2_v3i64 lm2_sqrt_lm2_v3i64(lm2_v3i64 a);
LM2_API lm2_v3i64 lm2_floor_multiple_lm2_v3i64(lm2_v3i64 a, lm2_v3i64 b);
LM2_API lm2_v3i64 lm2_ceil_multiple_lm2_v3i64(lm2_v3i64 a, lm2_v3i64 b);
LM2_API lm2_v3i64 lm2_round_multiple_lm2_v3i64(lm2_v3i64 a, lm2_v3i64 b);
LM2_API lm2_v3i64 lm2_trunc_multiple_lm2_v3i64(lm2_v3i64 a, lm2_v3i64 b);
LM2_API lm2_v3i64 lm2_min_lm2_v3i64(lm2_v3i64 a, lm2_v3i64 b);
LM2_API lm2_v3i64 lm2_min_abs_lm2_v3i64(lm2_v3i64 a, lm2_v3i64 b);
LM2_API lm2_v3i64 lm2_max_lm2_v3i64(lm2_v3i64 a, lm2_v3i64 b);
LM2_API lm2_v3i64 lm2_max_abs_lm2_v3i64(lm2_v3i64 a, lm2_v3i64 b);
LM2_API lm2_v3i64 lm2_mod_lm2_v3i64(lm2_v3i64 a, lm2_v3i64 b);
LM2_API lm2_v3i64 lm2_pow_lm2_v3i64(lm2_v3i64 a, lm2_v3i64 b);
LM2_API lm2_v3i64 lm2_clamp_lm2_v3i64(lm2_v3i64 a, lm2_v3i64 b, lm2_v3i64 c);
LM2_API lm2_v3i64 lm2_lerp_lm2_v3i64(lm2_v3i64 a, lm2_v3i64 b, lm2_v3i64 c);
LM2_API lm2_v3i64 lm2_smoothstep_lm2_v3i64(lm2_v3i64 a, lm2_v3i64 b, lm2_v3i64 c);
LM2_API lm2_v3i64 lm2_alpha_lm2_v3i64(lm2_v3i64 a, lm2_v3i64 b, lm2_v3i64 c);
LM2_API lm2_v3i64 lm2_v3i64_make(int64_t x, int64_t y, int64_t z);
LM2_API lm2_v3i64 lm2_v3i64_splat(int64_t v);
LM2_API lm2_v3i64 lm2_v3i64_zero(void);

// =============================================================================
// lm2_v3i32 Operations
// =============================================================================
LM2_API lm2_v3i32 lm2_add_lm2_v3i32(lm2_v3i32 a, lm2_v3i32 b);
LM2_API lm2_v3i32 lm2_sub_lm2_v3i32(lm2_v3i32 a, lm2_v3i32 b);
LM2_API lm2_v3i32 lm2_mul_lm2_v3i32(lm2_v3i32 a, lm2_v3i32 b);
LM2_API lm2_v3i32 lm2_div_lm2_v3i32(lm2_v3i32 a, lm2_v3i32 b);
LM2_API lm2_v3i32 lm2_add_lm2_v3i32_int32_t(lm2_v3i32 a, int32_t b);
LM2_API lm2_v3i32 lm2_sub_lm2_v3i32_int32_t(lm2_v3i32 a, int32_t b);
LM2_API lm2_v3i32 lm2_mul_lm2_v3i32_int32_t(lm2_v3i32 a, int32_t b);
LM2_API lm2_v3i32 lm2_div_lm2_v3i32_int32_t(lm2_v3i32 a, int32_t b);
LM2_API lm2_v3i32 lm2_neg_lm2_v3i32(lm2_v3i32 a);
LM2_API lm2_v3i32 lm2_floor_lm2_v3i32(lm2_v3i32 a);
LM2_API lm2_v3i32 lm2_ceil_lm2_v3i32(lm2_v3i32 a);
LM2_API lm2_v3i32 lm2_round_lm2_v3i32(lm2_v3i32 a);
LM2_API lm2_v3i32 lm2_trunc_lm2_v3i32(lm2_v3i32 a);
LM2_API lm2_v3i32 lm2_abs_lm2_v3i32(lm2_v3i32 a);
LM2_API lm2_v3i32 lm2_sign_lm2_v3i32(lm2_v3i32 a);
LM2_API lm2_v3i32 lm2_sign0_lm2_v3i32(lm2_v3i32 a);
LM2_API lm2_v3i32 lm2_saturate_lm2_v3i32(lm2_v3i32 a);
LM2_API lm2_v3i32 lm2_fract_lm2_v3i32(lm2_v3i32 a);
LM2_API lm2_v3i32 lm2_norm_lm2_v3i32(lm2_v3i32 a);
LM2_API lm2_v3i32 lm2_sqrt_lm2_v3i32(lm2_v3i32 a);
LM2_API lm2_v3i32 lm2_floor_multiple_lm2_v3i32(lm2_v3i32 a, lm2_v3i32 b);
LM2_API lm2_v3i32 lm2_ceil_multiple_lm2_v3i32(lm2_v3i32 a, lm2_v3i32 b);
LM2_API lm2_v3i32 lm2_round_multiple_lm2_v3i32(lm2_v3i32 a, lm2_v3i32 b);
LM2_API lm2_v3i32 lm2_trunc_multiple_lm2_v3i32(lm2_v3i32 a, lm2_v3i32 b);
LM2_API lm2_v3i32 lm2_min_lm2_v3i32(lm2_v3i32 a, lm2_v3i32 b);
LM2_API lm2_v3i32 lm2_min_abs_lm2_v3i32(lm2_v3i32 a, lm2_v3i32 b);
LM2_API lm2_v3i32 lm2_max_lm2_v3i32(lm2_v3i32 a, lm2_v3i32 b);
LM2_API lm2_v3i32 lm2_max_abs_lm2_v3i32(lm2_v3i32 a, lm2_v3i32 b);
LM2_API lm2_v3i32 lm2_mod_lm2_v3i32(lm2_v3i32 a, lm2_v3i32 b);
LM2_API lm2_v3i32 lm2_pow_lm2_v3i32(lm2_v3i32 a, lm2_v3i32 b);
LM2_API lm2_v3i32 lm2_clamp_lm2_v3i32(lm2_v3i32 a, lm2_v3i32 b, lm2_v3i32 c);
LM2_API lm2_v3i32 lm2_lerp_lm2_v3i32(lm2_v3i32 a, lm2_v3i32 b, lm2_v3i32 c);
LM2_API lm2_v3i32 lm2_smoothstep_lm2_v3i32(lm2_v3i32 a, lm2_v3i32 b, lm2_v3i32 c);
LM2_API lm2_v3i32 lm2_alpha_lm2_v3i32(lm2_v3i32 a, lm2_v3i32 b, lm2_v3i32 c);
LM2_API lm2_v3i32 lm2_v3i32_make(int32_t x, int32_t y, int32_t z);
LM2_API lm2_v3i32 lm2_v3i32_splat(int32_t v);
LM2_API lm2_v3i32 lm2_v3i32_zero(void);

// =============================================================================
// lm2_v3i16 Operations
// =============================================================================
LM2_API lm2_v3i16 lm2_add_lm2_v3i16(lm2_v3i16 a, lm2_v3i16 b);
LM2_API lm2_v3i16 lm2_sub_lm2_v3i16(lm2_v3i16 a, lm2_v3i16 b);
LM2_API lm2_v3i16 lm2_mul_lm2_v3i16(lm2_v3i16 a, lm2_v3i16 b);
LM2_API lm2_v3i16 lm2_div_lm2_v3i16(lm2_v3i16 a, lm2_v3i16 b);
LM2_API lm2_v3i16 lm2_add_lm2_v3i16_int16_t(lm2_v3i16 a, int16_t b);
LM2_API lm2_v3i16 lm2_sub_lm2_v3i16_int16_t(lm2_v3i16 a, int16_t b);
LM2_API lm2_v3i16 lm2_mul_lm2_v3i16_int16_t(lm2_v3i16 a, int16_t b);
LM2_API lm2_v3i16 lm2_div_lm2_v3i16_int16_t(lm2_v3i16 a, int16_t b);
LM2_API lm2_v3i16 lm2_neg_lm2_v3i16(lm2_v3i16 a);
LM2_API lm2_v3i16 lm2_floor_lm2_v3i16(lm2_v3i16 a);
LM2_API lm2_v3i16 lm2_ceil_lm2_v3i16(lm2_v3i16 a);
LM2_API lm2_v3i16 lm2_round_lm2_v3i16(lm2_v3i16 a);
LM2_API lm2_v3i16 lm2_trunc_lm2_v3i16(lm2_v3i16 a);
LM2_API lm2_v3i16 lm2_abs_lm2_v3i16(lm2_v3i16 a);
LM2_API lm2_v3i16 lm2_sign_lm2_v3i16(lm2_v3i16 a);
LM2_API lm2_v3i16 lm2_sign0_lm2_v3i16(lm2_v3i16 a);
LM2_API lm2_v3i16 lm2_saturate_lm2_v3i16(lm2_v3i16 a);
LM2_API lm2_v3i16 lm2_fract_lm2_v3i16(lm2_v3i16 a);
LM2_API lm2_v3i16 lm2_norm_lm2_v3i16(lm2_v3i16 a);
LM2_API lm2_v3i16 lm2_sqrt_lm2_v3i16(lm2_v3i16 a);
LM2_API lm2_v3i16 lm2_floor_multiple_lm2_v3i16(lm2_v3i16 a, lm2_v3i16 b);
LM2_API lm2_v3i16 lm2_ceil_multiple_lm2_v3i16(lm2_v3i16 a, lm2_v3i16 b);
LM2_API lm2_v3i16 lm2_round_multiple_lm2_v3i16(lm2_v3i16 a, lm2_v3i16 b);
LM2_API lm2_v3i16 lm2_trunc_multiple_lm2_v3i16(lm2_v3i16 a, lm2_v3i16 b);
LM2_API lm2_v3i16 lm2_min_lm2_v3i16(lm2_v3i16 a, lm2_v3i16 b);
LM2_API lm2_v3i16 lm2_min_abs_lm2_v3i16(lm2_v3i16 a, lm2_v3i16 b);
LM2_API lm2_v3i16 lm2_max_lm2_v3i16(lm2_v3i16 a, lm2_v3i16 b);
LM2_API lm2_v3i16 lm2_max_abs_lm2_v3i16(lm2_v3i16 a, lm2_v3i16 b);
LM2_API lm2_v3i16 lm2_mod_lm2_v3i16(lm2_v3i16 a, lm2_v3i16 b);
LM2_API lm2_v3i16 lm2_pow_lm2_v3i16(lm2_v3i16 a, lm2_v3i16 b);
LM2_API lm2_v3i16 lm2_clamp_lm2_v3i16(lm2_v3i16 a, lm2_v3i16 b, lm2_v3i16 c);
LM2_API lm2_v3i16 lm2_lerp_lm2_v3i16(lm2_v3i16 a, lm2_v3i16 b, lm2_v3i16 c);
LM2_API lm2_v3i16 lm2_smoothstep_lm2_v3i16(lm2_v3i16 a, lm2_v3i16 b, lm2_v3i16 c);
LM2_API lm2_v3i16 lm2_alpha_lm2_v3i16(lm2_v3i16 a, lm2_v3i16 b, lm2_v3i16 c);
LM2_API lm2_v3i16 lm2_v3i16_make(int16_t x, int16_t y, int16_t z);
LM2_API lm2_v3i16 lm2_v3i16_splat(int16_t v);
LM2_API lm2_v3i16 lm2_v3i16_zero(void);

// =============================================================================
// lm2_v3i8 Operations
// =============================================================================
LM2_API lm2_v3i8 lm2_add_lm2_v3i8(lm2_v3i8 a, lm2_v3i8 b);
LM2_API lm2_v3i8 lm2_sub_lm2_v3i8(lm2_v3i8 a, lm2_v3i8 b);
LM2_API lm2_v3i8 lm2_mul_lm2_v3i8(lm2_v3i8 a, lm2_v3i8 b);
LM2_API lm2_v3i8 lm2_div_lm2_v3i8(lm2_v3i8 a, lm2_v3i8 b);
LM2_API lm2_v3i8 lm2_add_lm2_v3i8_int8_t(lm2_v3i8 a, int8_t b);
LM2_API lm2_v3i8 lm2_sub_lm2_v3i8_int8_t(lm2_v3i8 a, int8_t b);
LM2_API lm2_v3i8 lm2_mul_lm2_v3i8_int8_t(lm2_v3i8 a, int8_t b);
LM2_API lm2_v3i8 lm2_div_lm2_v3i8_int8_t(lm2_v3i8 a, int8_t b);
LM2_API lm2_v3i8 lm2_neg_lm2_v3i8(lm2_v3i8 a);
LM2_API lm2_v3i8 lm2_floor_lm2_v3i8(lm2_v3i8 a);
LM2_API lm2_v3i8 lm2_ceil_lm2_v3i8(lm2_v3i8 a);
LM2_API lm2_v3i8 lm2_round_lm2_v3i8(lm2_v3i8 a);
LM2_API lm2_v3i8 lm2_trunc_lm2_v3i8(lm2_v3i8 a);
LM2_API lm2_v3i8 lm2_abs_lm2_v3i8(lm2_v3i8 a);
LM2_API lm2_v3i8 lm2_sign_lm2_v3i8(lm2_v3i8 a);
LM2_API lm2_v3i8 lm2_sign0_lm2_v3i8(lm2_v3i8 a);
LM2_API lm2_v3i8 lm2_saturate_lm2_v3i8(lm2_v3i8 a);
LM2_API lm2_v3i8 lm2_fract_lm2_v3i8(lm2_v3i8 a);
LM2_API lm2_v3i8 lm2_norm_lm2_v3i8(lm2_v3i8 a);
LM2_API lm2_v3i8 lm2_sqrt_lm2_v3i8(lm2_v3i8 a);
LM2_API lm2_v3i8 lm2_floor_multiple_lm2_v3i8(lm2_v3i8 a, lm2_v3i8 b);
LM2_API lm2_v3i8 lm2_ceil_multiple_lm2_v3i8(lm2_v3i8 a, lm2_v3i8 b);
LM2_API lm2_v3i8 lm2_round_multiple_lm2_v3i8(lm2_v3i8 a, lm2_v3i8 b);
LM2_API lm2_v3i8 lm2_trunc_multiple_lm2_v3i8(lm2_v3i8 a, lm2_v3i8 b);
LM2_API lm2_v3i8 lm2_min_lm2_v3i8(lm2_v3i8 a, lm2_v3i8 b);
LM2_API lm2_v3i8 lm2_min_abs_lm2_v3i8(lm2_v3i8 a, lm2_v3i8 b);
LM2_API lm2_v3i8 lm2_max_lm2_v3i8(lm2_v3i8 a, lm2_v3i8 b);
LM2_API lm2_v3i8 lm2_max_abs_lm2_v3i8(lm2_v3i8 a, lm2_v3i8 b);
LM2_API lm2_v3i8 lm2_mod_lm2_v3i8(lm2_v3i8 a, lm2_v3i8 b);
LM2_API lm2_v3i8 lm2_pow_lm2_v3i8(lm2_v3i8 a, lm2_v3i8 b);
LM2_API lm2_v3i8 lm2_clamp_lm2_v3i8(lm2_v3i8 a, lm2_v3i8 b, lm2_v3i8 c);
LM2_API lm2_v3i8 lm2_lerp_lm2_v3i8(lm2_v3i8 a, lm2_v3i8 b, lm2_v3i8 c);
LM2_API lm2_v3i8 lm2_smoothstep_lm2_v3i8(lm2_v3i8 a, lm2_v3i8 b, lm2_v3i8 c);
LM2_API lm2_v3i8 lm2_alpha_lm2_v3i8(lm2_v3i8 a, lm2_v3i8 b, lm2_v3i8 c);
LM2_API lm2_v3i8 lm2_v3i8_make(int8_t x, int8_t y, int8_t z);
LM2_API lm2_v3i8 lm2_v3i8_splat(int8_t v);
LM2_API lm2_v3i8 lm2_v3i8_zero(void);

// =============================================================================
// lm2_v3u64 Operations
// =============================================================================
LM2_API lm2_v3u64 lm2_add_lm2_v3u64(lm2_v3u64 a, lm2_v3u64 b);
LM2_API lm2_v3u64 lm2_sub_lm2_v3u64(lm2_v3u64 a, lm2_v3u64 b);
LM2_API lm2_v3u64 lm2_mul_lm2_v3u64(lm2_v3u64 a, lm2_v3u64 b);
LM2_API lm2_v3u64 lm2_div_lm2_v3u64(lm2_v3u64 a, lm2_v3u64 b);
LM2_API lm2_v3u64 lm2_add_lm2_v3u64_uint64_t(lm2_v3u64 a, uint64_t b);
LM2_API lm2_v3u64 lm2_sub_lm2_v3u64_uint64_t(lm2_v3u64 a, uint64_t b);
LM2_API lm2_v3u64 lm2_mul_lm2_v3u64_uint64_t(lm2_v3u64 a, uint64_t b);
LM2_API lm2_v3u64 lm2_div_lm2_v3u64_uint64_t(lm2_v3u64 a, uint64_t b);
LM2_API lm2_v3u64 lm2_neg_lm2_v3u64(lm2_v3u64 a);
LM2_API lm2_v3u64 lm2_floor_lm2_v3u64(lm2_v3u64 a);
LM2_API lm2_v3u64 lm2_ceil_lm2_v3u64(lm2_v3u64 a);
LM2_API lm2_v3u64 lm2_round_lm2_v3u64(lm2_v3u64 a);
LM2_API lm2_v3u64 lm2_trunc_lm2_v3u64(lm2_v3u64 a);
LM2_API lm2_v3u64 lm2_abs_lm2_v3u64(lm2_v3u64 a);
LM2_API lm2_v3u64 lm2_sign_lm2_v3u64(lm2_v3u64 a);
LM2_API lm2_v3u64 lm2_sign0_lm2_v3u64(lm2_v3u64 a);
LM2_API lm2_v3u64 lm2_saturate_lm2_v3u64(lm2_v3u64 a);
LM2_API lm2_v3u64 lm2_fract_lm2_v3u64(lm2_v3u64 a);
LM2_API lm2_v3u64 lm2_norm_lm2_v3u64(lm2_v3u64 a);
LM2_API lm2_v3u64 lm2_sqrt_lm2_v3u64(lm2_v3u64 a);
LM2_API lm2_v3u64 lm2_floor_multiple_lm2_v3u64(lm2_v3u64 a, lm2_v3u64 b);
LM2_API lm2_v3u64 lm2_ceil_multiple_lm2_v3u64(lm2_v3u64 a, lm2_v3u64 b);
LM2_API lm2_v3u64 lm2_round_multiple_lm2_v3u64(lm2_v3u64 a, lm2_v3u64 b);
LM2_API lm2_v3u64 lm2_trunc_multiple_lm2_v3u64(lm2_v3u64 a, lm2_v3u64 b);
LM2_API lm2_v3u64 lm2_min_lm2_v3u64(lm2_v3u64 a, lm2_v3u64 b);
LM2_API lm2_v3u64 lm2_min_abs_lm2_v3u64(lm2_v3u64 a, lm2_v3u64 b);
LM2_API lm2_v3u64 lm2_max_lm2_v3u64(lm2_v3u64 a, lm2_v3u64 b);
LM2_API lm2_v3u64 lm2_max_abs_lm2_v3u64(lm2_v3u64 a, lm2_v3u64 b);
LM2_API lm2_v3u64 lm2_mod_lm2_v3u64(lm2_v3u64 a, lm2_v3u64 b);
LM2_API lm2_v3u64 lm2_pow_lm2_v3u64(lm2_v3u64 a, lm2_v3u64 b);
LM2_API lm2_v3u64 lm2_clamp_lm2_v3u64(lm2_v3u64 a, lm2_v3u64 b, lm2_v3u64 c);
LM2_API lm2_v3u64 lm2_lerp_lm2_v3u64(lm2_v3u64 a, lm2_v3u64 b, lm2_v3u64 c);
LM2_API lm2_v3u64 lm2_smoothstep_lm2_v3u64(lm2_v3u64 a, lm2_v3u64 b, lm2_v3u64 c);
LM2_API lm2_v3u64 lm2_alpha_lm2_v3u64(lm2_v3u64 a, lm2_v3u64 b, lm2_v3u64 c);
LM2_API lm2_v3u64 lm2_v3u64_make(uint64_t x, uint64_t y, uint64_t z);
LM2_API lm2_v3u64 lm2_v3u64_splat(uint64_t v);
LM2_API lm2_v3u64 lm2_v3u64_zero(void);

// =============================================================================
// lm2_v3u32 Operations
// =============================================================================
LM2_API lm2_v3u32 lm2_add_lm2_v3u32(lm2_v3u32 a, lm2_v3u32 b);
LM2_API lm2_v3u32 lm2_sub_lm2_v3u32(lm2_v3u32 a, lm2_v3u32 b);
LM2_API lm2_v3u32 lm2_mul_lm2_v3u32(lm2_v3u32 a, lm2_v3u32 b);
LM2_API lm2_v3u32 lm2_div_lm2_v3u32(lm2_v3u32 a, lm2_v3u32 b);
LM2_API lm2_v3u32 lm2_add_lm2_v3u32_uint32_t(lm2_v3u32 a, uint32_t b);
LM2_API lm2_v3u32 lm2_sub_lm2_v3u32_uint32_t(lm2_v3u32 a, uint32_t b);
LM2_API lm2_v3u32 lm2_mul_lm2_v3u32_uint32_t(lm2_v3u32 a, uint32_t b);
LM2_API lm2_v3u32 lm2_div_lm2_v3u32_uint32_t(lm2_v3u32 a, uint32_t b);
LM2_API lm2_v3u32 lm2_neg_lm2_v3u32(lm2_v3u32 a);
LM2_API lm2_v3u32 lm2_floor_lm2_v3u32(lm2_v3u32 a);
LM2_API lm2_v3u32 lm2_ceil_lm2_v3u32(lm2_v3u32 a);
LM2_API lm2_v3u32 lm2_round_lm2_v3u32(lm2_v3u32 a);
LM2_API lm2_v3u32 lm2_trunc_lm2_v3u32(lm2_v3u32 a);
LM2_API lm2_v3u32 lm2_abs_lm2_v3u32(lm2_v3u32 a);
LM2_API lm2_v3u32 lm2_sign_lm2_v3u32(lm2_v3u32 a);
LM2_API lm2_v3u32 lm2_sign0_lm2_v3u32(lm2_v3u32 a);
LM2_API lm2_v3u32 lm2_saturate_lm2_v3u32(lm2_v3u32 a);
LM2_API lm2_v3u32 lm2_fract_lm2_v3u32(lm2_v3u32 a);
LM2_API lm2_v3u32 lm2_norm_lm2_v3u32(lm2_v3u32 a);
LM2_API lm2_v3u32 lm2_sqrt_lm2_v3u32(lm2_v3u32 a);
LM2_API lm2_v3u32 lm2_floor_multiple_lm2_v3u32(lm2_v3u32 a, lm2_v3u32 b);
LM2_API lm2_v3u32 lm2_ceil_multiple_lm2_v3u32(lm2_v3u32 a, lm2_v3u32 b);
LM2_API lm2_v3u32 lm2_round_multiple_lm2_v3u32(lm2_v3u32 a, lm2_v3u32 b);
LM2_API lm2_v3u32 lm2_trunc_multiple_lm2_v3u32(lm2_v3u32 a, lm2_v3u32 b);
LM2_API lm2_v3u32 lm2_min_lm2_v3u32(lm2_v3u32 a, lm2_v3u32 b);
LM2_API lm2_v3u32 lm2_min_abs_lm2_v3u32(lm2_v3u32 a, lm2_v3u32 b);
LM2_API lm2_v3u32 lm2_max_lm2_v3u32(lm2_v3u32 a, lm2_v3u32 b);
LM2_API lm2_v3u32 lm2_max_abs_lm2_v3u32(lm2_v3u32 a, lm2_v3u32 b);
LM2_API lm2_v3u32 lm2_mod_lm2_v3u32(lm2_v3u32 a, lm2_v3u32 b);
LM2_API lm2_v3u32 lm2_pow_lm2_v3u32(lm2_v3u32 a, lm2_v3u32 b);
LM2_API lm2_v3u32 lm2_clamp_lm2_v3u32(lm2_v3u32 a, lm2_v3u32 b, lm2_v3u32 c);
LM2_API lm2_v3u32 lm2_lerp_lm2_v3u32(lm2_v3u32 a, lm2_v3u32 b, lm2_v3u32 c);
LM2_API lm2_v3u32 lm2_smoothstep_lm2_v3u32(lm2_v3u32 a, lm2_v3u32 b, lm2_v3u32 c);
LM2_API lm2_v3u32 lm2_alpha_lm2_v3u32(lm2_v3u32 a, lm2_v3u32 b, lm2_v3u32 c);
LM2_API lm2_v3u32 lm2_v3u32_make(uint32_t x, uint32_t y, uint32_t z);
LM2_API lm2_v3u32 lm2_v3u32_splat(uint32_t v);
LM2_API lm2_v3u32 lm2_v3u32_zero(void);

// =============================================================================
// lm2_v3u16 Operations
// =============================================================================
LM2_API lm2_v3u16 lm2_add_lm2_v3u16(lm2_v3u16 a, lm2_v3u16 b);
LM2_API lm2_v3u16 lm2_sub_lm2_v3u16(lm2_v3u16 a, lm2_v3u16 b);
LM2_API lm2_v3u16 lm2_mul_lm2_v3u16(lm2_v3u16 a, lm2_v3u16 b);
LM2_API lm2_v3u16 lm2_div_lm2_v3u16(lm2_v3u16 a, lm2_v3u16 b);
LM2_API lm2_v3u16 lm2_add_lm2_v3u16_uint16_t(lm2_v3u16 a, uint16_t b);
LM2_API lm2_v3u16 lm2_sub_lm2_v3u16_uint16_t(lm2_v3u16 a, uint16_t b);
LM2_API lm2_v3u16 lm2_mul_lm2_v3u16_uint16_t(lm2_v3u16 a, uint16_t b);
LM2_API lm2_v3u16 lm2_div_lm2_v3u16_uint16_t(lm2_v3u16 a, uint16_t b);
LM2_API lm2_v3u16 lm2_neg_lm2_v3u16(lm2_v3u16 a);
LM2_API lm2_v3u16 lm2_floor_lm2_v3u16(lm2_v3u16 a);
LM2_API lm2_v3u16 lm2_ceil_lm2_v3u16(lm2_v3u16 a);
LM2_API lm2_v3u16 lm2_round_lm2_v3u16(lm2_v3u16 a);
LM2_API lm2_v3u16 lm2_trunc_lm2_v3u16(lm2_v3u16 a);
LM2_API lm2_v3u16 lm2_abs_lm2_v3u16(lm2_v3u16 a);
LM2_API lm2_v3u16 lm2_sign_lm2_v3u16(lm2_v3u16 a);
LM2_API lm2_v3u16 lm2_sign0_lm2_v3u16(lm2_v3u16 a);
LM2_API lm2_v3u16 lm2_saturate_lm2_v3u16(lm2_v3u16 a);
LM2_API lm2_v3u16 lm2_fract_lm2_v3u16(lm2_v3u16 a);
LM2_API lm2_v3u16 lm2_norm_lm2_v3u16(lm2_v3u16 a);
LM2_API lm2_v3u16 lm2_sqrt_lm2_v3u16(lm2_v3u16 a);
LM2_API lm2_v3u16 lm2_floor_multiple_lm2_v3u16(lm2_v3u16 a, lm2_v3u16 b);
LM2_API lm2_v3u16 lm2_ceil_multiple_lm2_v3u16(lm2_v3u16 a, lm2_v3u16 b);
LM2_API lm2_v3u16 lm2_round_multiple_lm2_v3u16(lm2_v3u16 a, lm2_v3u16 b);
LM2_API lm2_v3u16 lm2_trunc_multiple_lm2_v3u16(lm2_v3u16 a, lm2_v3u16 b);
LM2_API lm2_v3u16 lm2_min_lm2_v3u16(lm2_v3u16 a, lm2_v3u16 b);
LM2_API lm2_v3u16 lm2_min_abs_lm2_v3u16(lm2_v3u16 a, lm2_v3u16 b);
LM2_API lm2_v3u16 lm2_max_lm2_v3u16(lm2_v3u16 a, lm2_v3u16 b);
LM2_API lm2_v3u16 lm2_max_abs_lm2_v3u16(lm2_v3u16 a, lm2_v3u16 b);
LM2_API lm2_v3u16 lm2_mod_lm2_v3u16(lm2_v3u16 a, lm2_v3u16 b);
LM2_API lm2_v3u16 lm2_pow_lm2_v3u16(lm2_v3u16 a, lm2_v3u16 b);
LM2_API lm2_v3u16 lm2_clamp_lm2_v3u16(lm2_v3u16 a, lm2_v3u16 b, lm2_v3u16 c);
LM2_API lm2_v3u16 lm2_lerp_lm2_v3u16(lm2_v3u16 a, lm2_v3u16 b, lm2_v3u16 c);
LM2_API lm2_v3u16 lm2_smoothstep_lm2_v3u16(lm2_v3u16 a, lm2_v3u16 b, lm2_v3u16 c);
LM2_API lm2_v3u16 lm2_alpha_lm2_v3u16(lm2_v3u16 a, lm2_v3u16 b, lm2_v3u16 c);
LM2_API lm2_v3u16 lm2_v3u16_make(uint16_t x, uint16_t y, uint16_t z);
LM2_API lm2_v3u16 lm2_v3u16_splat(uint16_t v);
LM2_API lm2_v3u16 lm2_v3u16_zero(void);

// =============================================================================
// lm2_v3u8 Operations
// =============================================================================
LM2_API lm2_v3u8 lm2_add_lm2_v3u8(lm2_v3u8 a, lm2_v3u8 b);
LM2_API lm2_v3u8 lm2_sub_lm2_v3u8(lm2_v3u8 a, lm2_v3u8 b);
LM2_API lm2_v3u8 lm2_mul_lm2_v3u8(lm2_v3u8 a, lm2_v3u8 b);
LM2_API lm2_v3u8 lm2_div_lm2_v3u8(lm2_v3u8 a, lm2_v3u8 b);
LM2_API lm2_v3u8 lm2_add_lm2_v3u8_uint8_t(lm2_v3u8 a, uint8_t b);
LM2_API lm2_v3u8 lm2_sub_lm2_v3u8_uint8_t(lm2_v3u8 a, uint8_t b);
LM2_API lm2_v3u8 lm2_mul_lm2_v3u8_uint8_t(lm2_v3u8 a, uint8_t b);
LM2_API lm2_v3u8 lm2_div_lm2_v3u8_uint8_t(lm2_v3u8 a, uint8_t b);
LM2_API lm2_v3u8 lm2_neg_lm2_v3u8(lm2_v3u8 a);
LM2_API lm2_v3u8 lm2_floor_lm2_v3u8(lm2_v3u8 a);
LM2_API lm2_v3u8 lm2_ceil_lm2_v3u8(lm2_v3u8 a);
LM2_API lm2_v3u8 lm2_round_lm2_v3u8(lm2_v3u8 a);
LM2_API lm2_v3u8 lm2_trunc_lm2_v3u8(lm2_v3u8 a);
LM2_API lm2_v3u8 lm2_abs_lm2_v3u8(lm2_v3u8 a);
LM2_API lm2_v3u8 lm2_sign_lm2_v3u8(lm2_v3u8 a);
LM2_API lm2_v3u8 lm2_sign0_lm2_v3u8(lm2_v3u8 a);
LM2_API lm2_v3u8 lm2_saturate_lm2_v3u8(lm2_v3u8 a);
LM2_API lm2_v3u8 lm2_fract_lm2_v3u8(lm2_v3u8 a);
LM2_API lm2_v3u8 lm2_norm_lm2_v3u8(lm2_v3u8 a);
LM2_API lm2_v3u8 lm2_sqrt_lm2_v3u8(lm2_v3u8 a);
LM2_API lm2_v3u8 lm2_floor_multiple_lm2_v3u8(lm2_v3u8 a, lm2_v3u8 b);
LM2_API lm2_v3u8 lm2_ceil_multiple_lm2_v3u8(lm2_v3u8 a, lm2_v3u8 b);
LM2_API lm2_v3u8 lm2_round_multiple_lm2_v3u8(lm2_v3u8 a, lm2_v3u8 b);
LM2_API lm2_v3u8 lm2_trunc_multiple_lm2_v3u8(lm2_v3u8 a, lm2_v3u8 b);
LM2_API lm2_v3u8 lm2_min_lm2_v3u8(lm2_v3u8 a, lm2_v3u8 b);
LM2_API lm2_v3u8 lm2_min_abs_lm2_v3u8(lm2_v3u8 a, lm2_v3u8 b);
LM2_API lm2_v3u8 lm2_max_lm2_v3u8(lm2_v3u8 a, lm2_v3u8 b);
LM2_API lm2_v3u8 lm2_max_abs_lm2_v3u8(lm2_v3u8 a, lm2_v3u8 b);
LM2_API lm2_v3u8 lm2_mod_lm2_v3u8(lm2_v3u8 a, lm2_v3u8 b);
LM2_API lm2_v3u8 lm2_pow_lm2_v3u8(lm2_v3u8 a, lm2_v3u8 b);
LM2_API lm2_v3u8 lm2_clamp_lm2_v3u8(lm2_v3u8 a, lm2_v3u8 b, lm2_v3u8 c);
LM2_API lm2_v3u8 lm2_lerp_lm2_v3u8(lm2_v3u8 a, lm2_v3u8 b, lm2_v3u8 c);
LM2_API lm2_v3u8 lm2_smoothstep_lm2_v3u8(lm2_v3u8 a, lm2_v3u8 b, lm2_v3u8 c);
LM2_API lm2_v3u8 lm2_alpha_lm2_v3u8(lm2_v3u8 a, lm2_v3u8 b, lm2_v3u8 c);
LM2_API lm2_v3u8 lm2_v3u8_make(uint8_t x, uint8_t y, uint8_t z);
LM2_API lm2_v3u8 lm2_v3u8_splat(uint8_t v);
LM2_API lm2_v3u8 lm2_v3u8_zero(void);

// =============================================================================
// Type Alias
// =============================================================================
// Default vector type (32-bit float)
typedef lm2_v3f32 lm2_v3;

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// C++ operator overloads (must be outside extern "C")
#ifndef LM2_NO_CPP_OPERATORS
#  include "lm2_vector_operators.h"
_LM2_DEFINE_V3_OPERATORS(lm2_v3f64, double)
_LM2_DEFINE_V3_OPERATORS(lm2_v3f32, float)
_LM2_DEFINE_V3_OPERATORS(lm2_v3i64, int64_t)
_LM2_DEFINE_V3_OPERATORS(lm2_v3i32, int32_t)
_LM2_DEFINE_V3_OPERATORS(lm2_v3i16, int16_t)
_LM2_DEFINE_V3_OPERATORS(lm2_v3i8, int8_t)
_LM2_DEFINE_V3_OPERATORS(lm2_v3u64, uint64_t)
_LM2_DEFINE_V3_OPERATORS(lm2_v3u32, uint32_t)
_LM2_DEFINE_V3_OPERATORS(lm2_v3u16, uint16_t)
_LM2_DEFINE_V3_OPERATORS(lm2_v3u8, uint8_t)
#endif
