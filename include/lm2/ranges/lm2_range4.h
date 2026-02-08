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

#define _LM2_DEFINE_RANGE4(type_name, vec_type, scalar_type)      \
  typedef union type_name {                                       \
    vec_type e[2];                                                \
    struct {                                                      \
      vec_type min;                                               \
      vec_type max;                                               \
    };                                                            \
    _LM2_RANGE_SUBSCRIPT_OP(vec_type)                             \
  } type_name;                                                    \
  _LM2_DECLARE_RANGE_FROM_MIN_MAX(type_name, vec_type)            \
  _LM2_DECLARE_RANGE_FROM_CENTER_EXTENTS(type_name, vec_type)     \
  _LM2_DECLARE_RANGE_FROM_CENTER_SIZE(type_name, vec_type)        \
  _LM2_DECLARE_RANGE_FROM_POSITION_SIZE(type_name, vec_type)      \
  _LM2_DECLARE_RANGE_ZERO(type_name)                              \
  _LM2_DECLARE_RANGE_NORMALIZE(type_name)                         \
  _LM2_DECLARE_RANGE_TRANSLATE(type_name, vec_type)               \
  _LM2_DECLARE_RANGE_SCALE(type_name, scalar_type)                \
  _LM2_DECLARE_RANGE_EXPAND(type_name, scalar_type)               \
  _LM2_DECLARE_RANGE_ARITHMETIC(type_name, vec_type, scalar_type) \
  _LM2_DECLARE_RANGE_UNION(type_name)                             \
  _LM2_DECLARE_RANGE_INTERSECTION(type_name)                      \
  _LM2_DECLARE_RANGE_SIZE(type_name, vec_type)                    \
  _LM2_DECLARE_RANGE_EXTENTS(type_name, vec_type)                 \
  _LM2_DECLARE_RANGE_CENTER(type_name, vec_type)                  \
  _LM2_DECLARE_RANGE_CONTAINS_POINT(type_name, vec_type)          \
  _LM2_DECLARE_RANGE_OVERLAPS(type_name)                          \
  _LM2_DECLARE_RANGE4_HYPERVOLUME(type_name, scalar_type)         \
  _LM2_DECLARE_RANGE_SCALAR_FUNC_1(type_name, lm2_floor)          \
  _LM2_DECLARE_RANGE_SCALAR_FUNC_1(type_name, lm2_ceil)           \
  _LM2_DECLARE_RANGE_SCALAR_FUNC_1(type_name, lm2_round)          \
  _LM2_DECLARE_RANGE_SCALAR_FUNC_1(type_name, lm2_trunc)          \
  _LM2_DECLARE_RANGE_SCALAR_FUNC_1(type_name, lm2_abs)            \
  _LM2_DECLARE_RANGE_SCALAR_FUNC_2(type_name, lm2_floor_multiple) \
  _LM2_DECLARE_RANGE_SCALAR_FUNC_2(type_name, lm2_ceil_multiple)  \
  _LM2_DECLARE_RANGE_SCALAR_FUNC_2(type_name, lm2_round_multiple) \
  _LM2_DECLARE_RANGE_SCALAR_FUNC_2(type_name, lm2_trunc_multiple) \
  _LM2_DECLARE_RANGE_SCALAR_FUNC_2(type_name, lm2_min)            \
  _LM2_DECLARE_RANGE_SCALAR_FUNC_2(type_name, lm2_max)            \
  _LM2_DECLARE_RANGE_SCALAR_FUNC_3(type_name, lm2_clamp)          \
  _LM2_DECLARE_RANGE_SCALAR_FUNC_3(type_name, lm2_lerp)

// 4D Range types for all 10 numeric types
_LM2_DEFINE_RANGE4(lm2_range4f64, lm2_v4f64, double)
_LM2_DEFINE_RANGE4(lm2_range4f32, lm2_v4f32, float)
_LM2_DEFINE_RANGE4(lm2_range4i64, lm2_v4i64, int64_t)
_LM2_DEFINE_RANGE4(lm2_range4i32, lm2_v4i32, int32_t)
_LM2_DEFINE_RANGE4(lm2_range4i16, lm2_v4i16, int16_t)
_LM2_DEFINE_RANGE4(lm2_range4i8, lm2_v4i8, int8_t)
_LM2_DEFINE_RANGE4(lm2_range4u64, lm2_v4u64, uint64_t)
_LM2_DEFINE_RANGE4(lm2_range4u32, lm2_v4u32, uint32_t)
_LM2_DEFINE_RANGE4(lm2_range4u16, lm2_v4u16, uint16_t)
_LM2_DEFINE_RANGE4(lm2_range4u8, lm2_v4u8, uint8_t)

// Default range4 type (float-based)
typedef lm2_range4f32 lm2_range4;

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// Generics
#ifndef LM2_NO_GENERICS
#  include "lm2_range_generics.h"
#  define lm2_floor_range4(...)          _LM2_GENERIC_RANGE4(lm2_floor, __VA_ARGS__)
#  define lm2_ceil_range4(...)           _LM2_GENERIC_RANGE4(lm2_ceil, __VA_ARGS__)
#  define lm2_round_range4(...)          _LM2_GENERIC_RANGE4(lm2_round, __VA_ARGS__)
#  define lm2_trunc_range4(...)          _LM2_GENERIC_RANGE4(lm2_trunc, __VA_ARGS__)
#  define lm2_abs_range4(...)            _LM2_GENERIC_RANGE4(lm2_abs, __VA_ARGS__)
#  define lm2_floor_multiple_range4(...) _LM2_GENERIC_RANGE4(lm2_floor_multiple, __VA_ARGS__)
#  define lm2_ceil_multiple_range4(...)  _LM2_GENERIC_RANGE4(lm2_ceil_multiple, __VA_ARGS__)
#  define lm2_round_multiple_range4(...) _LM2_GENERIC_RANGE4(lm2_round_multiple, __VA_ARGS__)
#  define lm2_trunc_multiple_range4(...) _LM2_GENERIC_RANGE4(lm2_trunc_multiple, __VA_ARGS__)
#  define lm2_min_range4(...)            _LM2_GENERIC_RANGE4(lm2_min, __VA_ARGS__)
#  define lm2_max_range4(...)            _LM2_GENERIC_RANGE4(lm2_max, __VA_ARGS__)
#  define lm2_clamp_range4(...)          _LM2_GENERIC_RANGE4(lm2_clamp, __VA_ARGS__)
#  define lm2_lerp_range4(...)           _LM2_GENERIC_RANGE4(lm2_lerp, __VA_ARGS__)
#  define lm2_range4_normalize(...)      _LM2_GENERIC_RANGE4(normalize, __VA_ARGS__)
#  define lm2_range4_translate(...)      _LM2_GENERIC_RANGE4(translate, __VA_ARGS__)
#  define lm2_range4_scale(...)          _LM2_GENERIC_RANGE4(scale, __VA_ARGS__)
#  define lm2_range4_expand(...)         _LM2_GENERIC_RANGE4(expand, __VA_ARGS__)
#  define lm2_range4_contains_point(...) _LM2_GENERIC_RANGE4(contains_point, __VA_ARGS__)
#  define lm2_range4_overlaps(...)       _LM2_GENERIC_RANGE4(overlaps, __VA_ARGS__)
#  define lm2_range4_size(...)           _LM2_GENERIC_RANGE4(size, __VA_ARGS__)
#  define lm2_range4_extents(...)        _LM2_GENERIC_RANGE4(extents, __VA_ARGS__)
#  define lm2_range4_center(...)         _LM2_GENERIC_RANGE4(center, __VA_ARGS__)
#  define lm2_range4_hypervolume(...)    _LM2_GENERIC_RANGE4(hypervolume, __VA_ARGS__)
// Arithmetic operations (support range+range, range+vector, range+scalar)
#  define lm2_add_range4(r, x) _LM2_RANGE4_ARITH(add, r, x)
#  define lm2_sub_range4(r, x) _LM2_RANGE4_ARITH(sub, r, x)
#  define lm2_mul_range4(r, x) _LM2_RANGE4_ARITH(mul, r, x)
#  define lm2_div_range4(r, x) _LM2_RANGE4_ARITH(div, r, x)
#  define lm2_mod_range4(r, x) _LM2_RANGE4_ARITH(mod, r, x)
#endif

// C++ operator overloads and constructors (must be outside extern "C")
#ifndef LM2_NO_CPP_OPERATORS
#  include "lm2_range_operators.h"
_LM2_DEFINE_RANGE4_OPERATORS(lm2_range4f64, lm2_v4f64)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_range4f32, lm2_v4f32)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_range4i64, lm2_v4i64)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_range4i32, lm2_v4i32)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_range4i16, lm2_v4i16)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_range4i8, lm2_v4i8)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_range4u64, lm2_v4u64)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_range4u32, lm2_v4u32)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_range4u16, lm2_v4u16)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_range4u8, lm2_v4u8)
_LM2_DEFINE_RANGE4_CONSTRUCTORS(lm2_range4f64, lm2_v4f64)
_LM2_DEFINE_RANGE4_CONSTRUCTORS(lm2_range4f32, lm2_v4f32)
_LM2_DEFINE_RANGE4_CONSTRUCTORS(lm2_range4i64, lm2_v4i64)
_LM2_DEFINE_RANGE4_CONSTRUCTORS(lm2_range4i32, lm2_v4i32)
_LM2_DEFINE_RANGE4_CONSTRUCTORS(lm2_range4i16, lm2_v4i16)
_LM2_DEFINE_RANGE4_CONSTRUCTORS(lm2_range4i8, lm2_v4i8)
_LM2_DEFINE_RANGE4_CONSTRUCTORS(lm2_range4u64, lm2_v4u64)
_LM2_DEFINE_RANGE4_CONSTRUCTORS(lm2_range4u32, lm2_v4u32)
_LM2_DEFINE_RANGE4_CONSTRUCTORS(lm2_range4u16, lm2_v4u16)
_LM2_DEFINE_RANGE4_CONSTRUCTORS(lm2_range4u8, lm2_v4u8)
#endif
