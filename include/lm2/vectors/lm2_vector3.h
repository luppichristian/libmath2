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

// Define a vector type with 3 components and associated operations
#define _LM2_DEFINE_V3(type_name, scalar_type)                                               \
  typedef union type_name {                                                                  \
    scalar_type e[3];                                                                        \
    struct {                                                                                 \
      scalar_type x, y, z;                                                                   \
    };                                                                                       \
    struct {                                                                                 \
      scalar_type s, t, r;                                                                   \
    };                                                                                       \
    _LM2_VECTOR_SUBSCRIPT_OP(scalar_type, 3)                                                 \
  } type_name;                                                                               \
  _LM2_DECLARE_VECTOR_OP(type_name, lm2_add_##type_name)                                     \
  _LM2_DECLARE_VECTOR_OP(type_name, lm2_sub_##type_name)                                     \
  _LM2_DECLARE_VECTOR_OP(type_name, lm2_mul_##type_name)                                     \
  _LM2_DECLARE_VECTOR_OP(type_name, lm2_div_##type_name)                                     \
  _LM2_DECLARE_VECTOR_OP_SCALAR(type_name, scalar_type, lm2_add_##type_name##_##scalar_type) \
  _LM2_DECLARE_VECTOR_OP_SCALAR(type_name, scalar_type, lm2_sub_##type_name##_##scalar_type) \
  _LM2_DECLARE_VECTOR_OP_SCALAR(type_name, scalar_type, lm2_mul_##type_name##_##scalar_type) \
  _LM2_DECLARE_VECTOR_OP_SCALAR(type_name, scalar_type, lm2_div_##type_name##_##scalar_type) \
  _LM2_DECLARE_VECTOR_UNARY_OP(type_name, lm2_neg_##type_name)                               \
  _LM2_DECLARE_SCALAR_FUNC_1(type_name, lm2_floor_##type_name)                               \
  _LM2_DECLARE_SCALAR_FUNC_1(type_name, lm2_ceil_##type_name)                                \
  _LM2_DECLARE_SCALAR_FUNC_1(type_name, lm2_round_##type_name)                               \
  _LM2_DECLARE_SCALAR_FUNC_1(type_name, lm2_trunc_##type_name)                               \
  _LM2_DECLARE_SCALAR_FUNC_1(type_name, lm2_abs_##type_name)                                 \
  _LM2_DECLARE_SCALAR_FUNC_1(type_name, lm2_sign_##type_name)                                \
  _LM2_DECLARE_SCALAR_FUNC_1(type_name, lm2_sign0_##type_name)                               \
  _LM2_DECLARE_SCALAR_FUNC_1(type_name, lm2_saturate_##type_name)                            \
  _LM2_DECLARE_SCALAR_FUNC_1(type_name, lm2_fract_##type_name)                               \
  _LM2_DECLARE_SCALAR_FUNC_1(type_name, lm2_norm_##type_name)                                \
  _LM2_DECLARE_SCALAR_FUNC_1(type_name, lm2_sqrt_##type_name)                                \
  _LM2_DECLARE_SCALAR_FUNC_2(type_name, lm2_floor_multiple_##type_name)                      \
  _LM2_DECLARE_SCALAR_FUNC_2(type_name, lm2_ceil_multiple_##type_name)                       \
  _LM2_DECLARE_SCALAR_FUNC_2(type_name, lm2_round_multiple_##type_name)                      \
  _LM2_DECLARE_SCALAR_FUNC_2(type_name, lm2_trunc_multiple_##type_name)                      \
  _LM2_DECLARE_SCALAR_FUNC_2(type_name, lm2_min_##type_name)                                 \
  _LM2_DECLARE_SCALAR_FUNC_2(type_name, lm2_min_abs_##type_name)                             \
  _LM2_DECLARE_SCALAR_FUNC_2(type_name, lm2_max_##type_name)                                 \
  _LM2_DECLARE_SCALAR_FUNC_2(type_name, lm2_max_abs_##type_name)                             \
  _LM2_DECLARE_SCALAR_FUNC_2(type_name, lm2_mod_##type_name)                                 \
  _LM2_DECLARE_SCALAR_FUNC_2(type_name, lm2_pow_##type_name)                                 \
  _LM2_DECLARE_SCALAR_FUNC_3(type_name, lm2_clamp_##type_name)                               \
  _LM2_DECLARE_SCALAR_FUNC_3(type_name, lm2_lerp_##type_name)                                \
  _LM2_DECLARE_SCALAR_FUNC_3(type_name, lm2_smoothstep_##type_name)                          \
  _LM2_DECLARE_SCALAR_FUNC_3(type_name, lm2_alpha_##type_name)

// 3D vector types
_LM2_DEFINE_V3(lm2_v3f64, double)
_LM2_DEFINE_V3(lm2_v3f32, float)
_LM2_DEFINE_V3(lm2_v3i64, int64_t)
_LM2_DEFINE_V3(lm2_v3i32, int32_t)
_LM2_DEFINE_V3(lm2_v3i16, int16_t)
_LM2_DEFINE_V3(lm2_v3i8, int8_t)
_LM2_DEFINE_V3(lm2_v3u64, uint64_t)
_LM2_DEFINE_V3(lm2_v3u32, uint32_t)
_LM2_DEFINE_V3(lm2_v3u16, uint16_t)
_LM2_DEFINE_V3(lm2_v3u8, uint8_t)

// V3 constructors
_LM2_DECLARE_V3_MAKE(lm2_v3f64, double)
_LM2_DECLARE_V3_MAKE(lm2_v3f32, float)
_LM2_DECLARE_V3_MAKE(lm2_v3i64, int64_t)
_LM2_DECLARE_V3_MAKE(lm2_v3i32, int32_t)
_LM2_DECLARE_V3_MAKE(lm2_v3i16, int16_t)
_LM2_DECLARE_V3_MAKE(lm2_v3i8, int8_t)
_LM2_DECLARE_V3_MAKE(lm2_v3u64, uint64_t)
_LM2_DECLARE_V3_MAKE(lm2_v3u32, uint32_t)
_LM2_DECLARE_V3_MAKE(lm2_v3u16, uint16_t)
_LM2_DECLARE_V3_MAKE(lm2_v3u8, uint8_t)

_LM2_DECLARE_V3_SPLAT(lm2_v3f64, double)
_LM2_DECLARE_V3_SPLAT(lm2_v3f32, float)
_LM2_DECLARE_V3_SPLAT(lm2_v3i64, int64_t)
_LM2_DECLARE_V3_SPLAT(lm2_v3i32, int32_t)
_LM2_DECLARE_V3_SPLAT(lm2_v3i16, int16_t)
_LM2_DECLARE_V3_SPLAT(lm2_v3i8, int8_t)
_LM2_DECLARE_V3_SPLAT(lm2_v3u64, uint64_t)
_LM2_DECLARE_V3_SPLAT(lm2_v3u32, uint32_t)
_LM2_DECLARE_V3_SPLAT(lm2_v3u16, uint16_t)
_LM2_DECLARE_V3_SPLAT(lm2_v3u8, uint8_t)

_LM2_DECLARE_V3_ZERO(lm2_v3f64)
_LM2_DECLARE_V3_ZERO(lm2_v3f32)
_LM2_DECLARE_V3_ZERO(lm2_v3i64)
_LM2_DECLARE_V3_ZERO(lm2_v3i32)
_LM2_DECLARE_V3_ZERO(lm2_v3i16)
_LM2_DECLARE_V3_ZERO(lm2_v3i8)
_LM2_DECLARE_V3_ZERO(lm2_v3u64)
_LM2_DECLARE_V3_ZERO(lm2_v3u32)
_LM2_DECLARE_V3_ZERO(lm2_v3u16)
_LM2_DECLARE_V3_ZERO(lm2_v3u8)

// Default vector type
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
