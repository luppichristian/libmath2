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

#include "libmath2_vector_defines.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// Define a vector type with 4 components and associated operations
#define _LM2_DEFINE_V4(type_name, scalar_type)                                               \
  typedef union type_name {                                                                  \
    scalar_type e[4];                                                                        \
    struct {                                                                                 \
      scalar_type x, y, z, w;                                                                \
    };                                                                                       \
    struct {                                                                                 \
      scalar_type s, t, r, q;                                                                \
    };                                                                                       \
    _LM2_VECTOR_SUBSCRIPT_OP(scalar_type, 4)                                                 \
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

// 4D vector types
_LM2_DEFINE_V4(lm2_v4f64, double)
_LM2_DEFINE_V4(lm2_v4f32, float)
_LM2_DEFINE_V4(lm2_v4i64, int64_t)
_LM2_DEFINE_V4(lm2_v4i32, int32_t)
_LM2_DEFINE_V4(lm2_v4i16, int16_t)
_LM2_DEFINE_V4(lm2_v4i8, int8_t)
_LM2_DEFINE_V4(lm2_v4u64, uint64_t)
_LM2_DEFINE_V4(lm2_v4u32, uint32_t)
_LM2_DEFINE_V4(lm2_v4u16, uint16_t)
_LM2_DEFINE_V4(lm2_v4u8, uint8_t)

// Default vector type
typedef lm2_v4f32 lm2_v4;

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// C++ operator overloads (must be outside extern "C")
#ifndef LM2_NO_CPP_OPERATORS
_LM2_DEFINE_V4_OPERATORS(lm2_v4f64, double)
_LM2_DEFINE_V4_OPERATORS(lm2_v4f32, float)
_LM2_DEFINE_V4_OPERATORS(lm2_v4i64, int64_t)
_LM2_DEFINE_V4_OPERATORS(lm2_v4i32, int32_t)
_LM2_DEFINE_V4_OPERATORS(lm2_v4i16, int16_t)
_LM2_DEFINE_V4_OPERATORS(lm2_v4i8, int8_t)
_LM2_DEFINE_V4_OPERATORS(lm2_v4u64, uint64_t)
_LM2_DEFINE_V4_OPERATORS(lm2_v4u32, uint32_t)
_LM2_DEFINE_V4_OPERATORS(lm2_v4u16, uint16_t)
_LM2_DEFINE_V4_OPERATORS(lm2_v4u8, uint8_t)
#endif

#ifndef LM2_NO_GENERICS
// Generic V4 vector-vector operations (type-dispatched)
#  define lm2_add_v4(...) _LM2_GENERIC_V4(lm2_add, __VA_ARGS__)
#  define lm2_sub_v4(...) _LM2_GENERIC_V4(lm2_sub, __VA_ARGS__)
#  define lm2_mul_v4(...) _LM2_GENERIC_V4(lm2_mul, __VA_ARGS__)
#  define lm2_div_v4(...) _LM2_GENERIC_V4(lm2_div, __VA_ARGS__)

// Generic V4 vector-scalar operations (type-dispatched)
#  define lm2_add_v4_s(...) _LM2_GENERIC_V4_SCALAR(lm2_add, __VA_ARGS__)
#  define lm2_sub_v4_s(...) _LM2_GENERIC_V4_SCALAR(lm2_sub, __VA_ARGS__)
#  define lm2_mul_v4_s(...) _LM2_GENERIC_V4_SCALAR(lm2_mul, __VA_ARGS__)
#  define lm2_div_v4_s(...) _LM2_GENERIC_V4_SCALAR(lm2_div, __VA_ARGS__)

// Generic V4 unary operations (type-dispatched)
#  define lm2_neg_v4(...) _LM2_GENERIC_V4_UNARY(lm2_neg, __VA_ARGS__)

// Generic V4 scalar functions (type-dispatched)
// Unary scalar functions
#  define lm2_floor_v4(...)    _LM2_GENERIC_V4_UNARY(lm2_floor, __VA_ARGS__)
#  define lm2_ceil_v4(...)     _LM2_GENERIC_V4_UNARY(lm2_ceil, __VA_ARGS__)
#  define lm2_round_v4(...)    _LM2_GENERIC_V4_UNARY(lm2_round, __VA_ARGS__)
#  define lm2_trunc_v4(...)    _LM2_GENERIC_V4_UNARY(lm2_trunc, __VA_ARGS__)
#  define lm2_abs_v4(...)      _LM2_GENERIC_V4_UNARY(lm2_abs, __VA_ARGS__)
#  define lm2_sign_v4(...)     _LM2_GENERIC_V4_UNARY(lm2_sign, __VA_ARGS__)
#  define lm2_sign0_v4(...)    _LM2_GENERIC_V4_UNARY(lm2_sign0, __VA_ARGS__)
#  define lm2_saturate_v4(...) _LM2_GENERIC_V4_UNARY(lm2_saturate, __VA_ARGS__)
#  define lm2_fract_v4(...)    _LM2_GENERIC_V4_UNARY(lm2_fract, __VA_ARGS__)
#  define lm2_norm_v4(...)     _LM2_GENERIC_V4_UNARY(lm2_norm, __VA_ARGS__)
#  define lm2_sqrt_v4(...)     _LM2_GENERIC_V4_UNARY(lm2_sqrt, __VA_ARGS__)

// Binary scalar functions
#  define lm2_floor_multiple_v4(...) _LM2_GENERIC_V4(lm2_floor_multiple, __VA_ARGS__)
#  define lm2_ceil_multiple_v4(...)  _LM2_GENERIC_V4(lm2_ceil_multiple, __VA_ARGS__)
#  define lm2_round_multiple_v4(...) _LM2_GENERIC_V4(lm2_round_multiple, __VA_ARGS__)
#  define lm2_trunc_multiple_v4(...) _LM2_GENERIC_V4(lm2_trunc_multiple, __VA_ARGS__)
#  define lm2_min_v4(...)            _LM2_GENERIC_V4(lm2_min, __VA_ARGS__)
#  define lm2_min_abs_v4(...)        _LM2_GENERIC_V4(lm2_min_abs, __VA_ARGS__)
#  define lm2_max_v4(...)            _LM2_GENERIC_V4(lm2_max, __VA_ARGS__)
#  define lm2_max_abs_v4(...)        _LM2_GENERIC_V4(lm2_max_abs, __VA_ARGS__)
#  define lm2_mod_v4(...)            _LM2_GENERIC_V4(lm2_mod, __VA_ARGS__)
#  define lm2_pow_v4(...)            _LM2_GENERIC_V4(lm2_pow, __VA_ARGS__)

// Ternary scalar functions
#  define lm2_clamp_v4(...)      _LM2_GENERIC_V4(lm2_clamp, __VA_ARGS__)
#  define lm2_lerp_v4(...)       _LM2_GENERIC_V4(lm2_lerp, __VA_ARGS__)
#  define lm2_smoothstep_v4(...) _LM2_GENERIC_V4(lm2_smoothstep, __VA_ARGS__)
#  define lm2_alpha_v4(...)      _LM2_GENERIC_V4(lm2_alpha, __VA_ARGS__)

#endif