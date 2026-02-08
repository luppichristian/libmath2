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

// Define a vector type with 2 components and associated operations
#define _LM2_DEFINE_V2(type_name, scalar_type)                                               \
  typedef union type_name {                                                                  \
    scalar_type e[2];                                                                        \
    struct {                                                                                 \
      scalar_type x, y;                                                                      \
    };                                                                                       \
    struct {                                                                                 \
      scalar_type s, t;                                                                      \
    };                                                                                       \
    _LM2_V2_CPP_CONSTRUCTORS(type_name, scalar_type)                                         \
    _LM2_VECTOR_SUBSCRIPT_OP(scalar_type, 2)                                                 \
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

// 2D vector types
_LM2_DEFINE_V2(lm2_v2f64, double)
_LM2_DEFINE_V2(lm2_v2f32, float)
_LM2_DEFINE_V2(lm2_v2i64, int64_t)
_LM2_DEFINE_V2(lm2_v2i32, int32_t)
_LM2_DEFINE_V2(lm2_v2i16, int16_t)
_LM2_DEFINE_V2(lm2_v2i8, int8_t)
_LM2_DEFINE_V2(lm2_v2u64, uint64_t)
_LM2_DEFINE_V2(lm2_v2u32, uint32_t)
_LM2_DEFINE_V2(lm2_v2u16, uint16_t)
_LM2_DEFINE_V2(lm2_v2u8, uint8_t)

// V2 constructors
_LM2_DECLARE_V2_MAKE(lm2_v2f64, double)
_LM2_DECLARE_V2_MAKE(lm2_v2f32, float)
_LM2_DECLARE_V2_MAKE(lm2_v2i64, int64_t)
_LM2_DECLARE_V2_MAKE(lm2_v2i32, int32_t)
_LM2_DECLARE_V2_MAKE(lm2_v2i16, int16_t)
_LM2_DECLARE_V2_MAKE(lm2_v2i8, int8_t)
_LM2_DECLARE_V2_MAKE(lm2_v2u64, uint64_t)
_LM2_DECLARE_V2_MAKE(lm2_v2u32, uint32_t)
_LM2_DECLARE_V2_MAKE(lm2_v2u16, uint16_t)
_LM2_DECLARE_V2_MAKE(lm2_v2u8, uint8_t)

_LM2_DECLARE_V2_SPLAT(lm2_v2f64, double)
_LM2_DECLARE_V2_SPLAT(lm2_v2f32, float)
_LM2_DECLARE_V2_SPLAT(lm2_v2i64, int64_t)
_LM2_DECLARE_V2_SPLAT(lm2_v2i32, int32_t)
_LM2_DECLARE_V2_SPLAT(lm2_v2i16, int16_t)
_LM2_DECLARE_V2_SPLAT(lm2_v2i8, int8_t)
_LM2_DECLARE_V2_SPLAT(lm2_v2u64, uint64_t)
_LM2_DECLARE_V2_SPLAT(lm2_v2u32, uint32_t)
_LM2_DECLARE_V2_SPLAT(lm2_v2u16, uint16_t)
_LM2_DECLARE_V2_SPLAT(lm2_v2u8, uint8_t)

_LM2_DECLARE_V2_ZERO(lm2_v2f64)
_LM2_DECLARE_V2_ZERO(lm2_v2f32)
_LM2_DECLARE_V2_ZERO(lm2_v2i64)
_LM2_DECLARE_V2_ZERO(lm2_v2i32)
_LM2_DECLARE_V2_ZERO(lm2_v2i16)
_LM2_DECLARE_V2_ZERO(lm2_v2i8)
_LM2_DECLARE_V2_ZERO(lm2_v2u64)
_LM2_DECLARE_V2_ZERO(lm2_v2u32)
_LM2_DECLARE_V2_ZERO(lm2_v2u16)
_LM2_DECLARE_V2_ZERO(lm2_v2u8)

// Default vector type
typedef lm2_v2f32 lm2_v2;

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// Generics
#ifndef LM2_NO_GENERICS
#  include "lm2_vector_generics.h"
#  define lm2_add_v2(...)            _LM2_GENERIC_V2(lm2_add, __VA_ARGS__)
#  define lm2_sub_v2(...)            _LM2_GENERIC_V2(lm2_sub, __VA_ARGS__)
#  define lm2_mul_v2(...)            _LM2_GENERIC_V2(lm2_mul, __VA_ARGS__)
#  define lm2_div_v2(...)            _LM2_GENERIC_V2(lm2_div, __VA_ARGS__)
#  define lm2_add_v2_s(...)          _LM2_GENERIC_V2_SCALAR(lm2_add, __VA_ARGS__)
#  define lm2_sub_v2_s(...)          _LM2_GENERIC_V2_SCALAR(lm2_sub, __VA_ARGS__)
#  define lm2_mul_v2_s(...)          _LM2_GENERIC_V2_SCALAR(lm2_mul, __VA_ARGS__)
#  define lm2_div_v2_s(...)          _LM2_GENERIC_V2_SCALAR(lm2_div, __VA_ARGS__)
#  define lm2_neg_v2(...)            _LM2_GENERIC_V2_UNARY(lm2_neg, __VA_ARGS__)
#  define lm2_floor_v2(...)          _LM2_GENERIC_V2_UNARY(lm2_floor, __VA_ARGS__)
#  define lm2_ceil_v2(...)           _LM2_GENERIC_V2_UNARY(lm2_ceil, __VA_ARGS__)
#  define lm2_round_v2(...)          _LM2_GENERIC_V2_UNARY(lm2_round, __VA_ARGS__)
#  define lm2_trunc_v2(...)          _LM2_GENERIC_V2_UNARY(lm2_trunc, __VA_ARGS__)
#  define lm2_abs_v2(...)            _LM2_GENERIC_V2_UNARY(lm2_abs, __VA_ARGS__)
#  define lm2_sign_v2(...)           _LM2_GENERIC_V2_UNARY(lm2_sign, __VA_ARGS__)
#  define lm2_sign0_v2(...)          _LM2_GENERIC_V2_UNARY(lm2_sign0, __VA_ARGS__)
#  define lm2_saturate_v2(...)       _LM2_GENERIC_V2_UNARY(lm2_saturate, __VA_ARGS__)
#  define lm2_fract_v2(...)          _LM2_GENERIC_V2_UNARY(lm2_fract, __VA_ARGS__)
#  define lm2_sqrt_v2(...)           _LM2_GENERIC_V2_UNARY(lm2_sqrt, __VA_ARGS__)
#  define lm2_floor_multiple_v2(...) _LM2_GENERIC_V2(lm2_floor_multiple, __VA_ARGS__)
#  define lm2_ceil_multiple_v2(...)  _LM2_GENERIC_V2(lm2_ceil_multiple, __VA_ARGS__)
#  define lm2_round_multiple_v2(...) _LM2_GENERIC_V2(lm2_round_multiple, __VA_ARGS__)
#  define lm2_trunc_multiple_v2(...) _LM2_GENERIC_V2(lm2_trunc_multiple, __VA_ARGS__)
#  define lm2_min_v2(...)            _LM2_GENERIC_V2(lm2_min, __VA_ARGS__)
#  define lm2_min_abs_v2(...)        _LM2_GENERIC_V2(lm2_min_abs, __VA_ARGS__)
#  define lm2_max_v2(...)            _LM2_GENERIC_V2(lm2_max, __VA_ARGS__)
#  define lm2_max_abs_v2(...)        _LM2_GENERIC_V2(lm2_max_abs, __VA_ARGS__)
#  define lm2_mod_v2(...)            _LM2_GENERIC_V2(lm2_mod, __VA_ARGS__)
#  define lm2_pow_v2(...)            _LM2_GENERIC_V2(lm2_pow, __VA_ARGS__)
#  define lm2_clamp_v2(...)          _LM2_GENERIC_V2(lm2_clamp, __VA_ARGS__)
#  define lm2_lerp_v2(...)           _LM2_GENERIC_V2(lm2_lerp, __VA_ARGS__)
#  define lm2_smoothstep_v2(...)     _LM2_GENERIC_V2(lm2_smoothstep, __VA_ARGS__)
#  define lm2_alpha_v2(...)          _LM2_GENERIC_V2(lm2_alpha, __VA_ARGS__)
#  define lm2_v2_make(...)           _LM2_GENERIC_V2_MAKE(__VA_ARGS__)
#  define lm2_v2_splat(...)          _LM2_GENERIC_V2_SPLAT(__VA_ARGS__)
#endif

// C++ operator overloads (must be outside extern "C")
#ifndef LM2_NO_CPP_OPERATORS
#  include "lm2_vector_operators.h"
_LM2_DEFINE_V2_OPERATORS(lm2_v2f64, double)
_LM2_DEFINE_V2_OPERATORS(lm2_v2f32, float)
_LM2_DEFINE_V2_OPERATORS(lm2_v2i64, int64_t)
_LM2_DEFINE_V2_OPERATORS(lm2_v2i32, int32_t)
_LM2_DEFINE_V2_OPERATORS(lm2_v2i16, int16_t)
_LM2_DEFINE_V2_OPERATORS(lm2_v2i8, int8_t)
_LM2_DEFINE_V2_OPERATORS(lm2_v2u64, uint64_t)
_LM2_DEFINE_V2_OPERATORS(lm2_v2u32, uint32_t)
_LM2_DEFINE_V2_OPERATORS(lm2_v2u16, uint16_t)
_LM2_DEFINE_V2_OPERATORS(lm2_v2u8, uint8_t)
#endif
