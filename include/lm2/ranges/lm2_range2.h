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
#include "lm2_range_defines.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// 2D Range (AABB) Type Definitions
// =============================================================================
// A range2 represents a 2D axis-aligned bounding box (AABB) or rectangle
// with minimum and maximum points.
#define _LM2_DEFINE_RANGE2(type_name, vec_type, scalar_type)      \
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
  _LM2_DECLARE_RANGE_SCALAR_FUNC_3(type_name, lm2_lerp)           \
  _LM2_DECLARE_RANGE_UNION(type_name)                             \
  _LM2_DECLARE_RANGE_INTERSECTION(type_name)                      \
  _LM2_DECLARE_RANGE_SIZE(type_name, vec_type)                    \
  _LM2_DECLARE_RANGE_EXTENTS(type_name, vec_type)                 \
  _LM2_DECLARE_RANGE_CENTER(type_name, vec_type)                  \
  _LM2_DECLARE_RANGE_CONTAINS_POINT(type_name, vec_type)          \
  _LM2_DECLARE_RANGE_OVERLAPS(type_name)                          \
  _LM2_DECLARE_RANGE2_AREA(type_name, scalar_type)

// 2D Range types for all 10 numeric types
_LM2_DEFINE_RANGE2(lm2_r2f64, lm2_v2f64, double)
_LM2_DEFINE_RANGE2(lm2_r2f32, lm2_v2f32, float)
_LM2_DEFINE_RANGE2(lm2_r2i64, lm2_v2i64, int64_t)
_LM2_DEFINE_RANGE2(lm2_r2i32, lm2_v2i32, int32_t)
_LM2_DEFINE_RANGE2(lm2_r2i16, lm2_v2i16, int16_t)
_LM2_DEFINE_RANGE2(lm2_r2i8, lm2_v2i8, int8_t)
_LM2_DEFINE_RANGE2(lm2_r2u64, lm2_v2u64, uint64_t)
_LM2_DEFINE_RANGE2(lm2_r2u32, lm2_v2u32, uint32_t)
_LM2_DEFINE_RANGE2(lm2_r2u16, lm2_v2u16, uint16_t)
_LM2_DEFINE_RANGE2(lm2_r2u8, lm2_v2u8, uint8_t)

// Default range2 type (float-based)
typedef lm2_r2f32 lm2_r2;

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// Generics
#ifndef LM2_NO_GENERICS
#  include "lm2_range_generics.h"
#  define lm2_floor_r2(...)          _LM2_GENERIC_RANGE2(lm2_floor, __VA_ARGS__)
#  define lm2_ceil_r2(...)           _LM2_GENERIC_RANGE2(lm2_ceil, __VA_ARGS__)
#  define lm2_round_r2(...)          _LM2_GENERIC_RANGE2(lm2_round, __VA_ARGS__)
#  define lm2_trunc_r2(...)          _LM2_GENERIC_RANGE2(lm2_trunc, __VA_ARGS__)
#  define lm2_abs_r2(...)            _LM2_GENERIC_RANGE2(lm2_abs, __VA_ARGS__)
#  define lm2_floor_multiple_r2(...) _LM2_GENERIC_RANGE2(lm2_floor_multiple, __VA_ARGS__)
#  define lm2_ceil_multiple_r2(...)  _LM2_GENERIC_RANGE2(lm2_ceil_multiple, __VA_ARGS__)
#  define lm2_round_multiple_r2(...) _LM2_GENERIC_RANGE2(lm2_round_multiple, __VA_ARGS__)
#  define lm2_trunc_multiple_r2(...) _LM2_GENERIC_RANGE2(lm2_trunc_multiple, __VA_ARGS__)
#  define lm2_min_r2(...)            _LM2_GENERIC_RANGE2(lm2_min, __VA_ARGS__)
#  define lm2_max_r2(...)            _LM2_GENERIC_RANGE2(lm2_max, __VA_ARGS__)
#  define lm2_clamp_r2(...)          _LM2_GENERIC_RANGE2(lm2_clamp, __VA_ARGS__)
#  define lm2_lerp_r2(...)           _LM2_GENERIC_RANGE2(lm2_lerp, __VA_ARGS__)
#  define lm2_normalize_r2(...)      _LM2_GENERIC_RANGE2(normalize, __VA_ARGS__)
#  define lm2_translate_r2(...)      _LM2_GENERIC_RANGE2(translate, __VA_ARGS__)
#  define lm2_scale_r2(...)          _LM2_GENERIC_RANGE2(scale, __VA_ARGS__)
#  define lm2_expand_r2(...)         _LM2_GENERIC_RANGE2(expand, __VA_ARGS__)
#  define lm2_union_r2(...)          _LM2_GENERIC_RANGE2(union, __VA_ARGS__)
#  define lm2_intersection_r2(...)   _LM2_GENERIC_RANGE2(intersection, __VA_ARGS__)
#  define lm2_size_r2(...)           _LM2_GENERIC_RANGE2(size, __VA_ARGS__)
#  define lm2_extents_r2(...)        _LM2_GENERIC_RANGE2(extents, __VA_ARGS__)
#  define lm2_center_r2(...)         _LM2_GENERIC_RANGE2(center, __VA_ARGS__)
#  define lm2_contains_point_r2(...) _LM2_GENERIC_RANGE2(contains_point, __VA_ARGS__)
#  define lm2_overlaps_r2(...)       _LM2_GENERIC_RANGE2(overlaps, __VA_ARGS__)
#  define lm2_area_r2(...)           _LM2_GENERIC_RANGE2(area, __VA_ARGS__)
#  define lm2_add_r2(r, x)           _LM2_RANGE2_ARITH(add, r, x)
#  define lm2_sub_r2(r, x)           _LM2_RANGE2_ARITH(sub, r, x)
#  define lm2_mul_r2(r, x)           _LM2_RANGE2_ARITH(mul, r, x)
#  define lm2_div_r2(r, x)           _LM2_RANGE2_ARITH(div, r, x)
#  define lm2_mod_r2(r, x)           _LM2_RANGE2_ARITH(mod, r, x)
#endif

// C++ operator overloads and constructors (must be outside extern "C")
#ifndef LM2_NO_CPP_OPERATORS
#  include "lm2_range_operators.h"
_LM2_DEFINE_RANGE2_OPERATORS(lm2_r2f64, lm2_v2f64)
_LM2_DEFINE_RANGE2_OPERATORS(lm2_r2f32, lm2_v2f32)
_LM2_DEFINE_RANGE2_OPERATORS(lm2_r2i64, lm2_v2i64)
_LM2_DEFINE_RANGE2_OPERATORS(lm2_r2i32, lm2_v2i32)
_LM2_DEFINE_RANGE2_OPERATORS(lm2_r2i16, lm2_v2i16)
_LM2_DEFINE_RANGE2_OPERATORS(lm2_r2i8, lm2_v2i8)
_LM2_DEFINE_RANGE2_OPERATORS(lm2_r2u64, lm2_v2u64)
_LM2_DEFINE_RANGE2_OPERATORS(lm2_r2u32, lm2_v2u32)
_LM2_DEFINE_RANGE2_OPERATORS(lm2_r2u16, lm2_v2u16)
_LM2_DEFINE_RANGE2_OPERATORS(lm2_r2u8, lm2_v2u8)
_LM2_DEFINE_RANGE2_CONSTRUCTORS(lm2_r2f64, lm2_v2f64)
_LM2_DEFINE_RANGE2_CONSTRUCTORS(lm2_r2f32, lm2_v2f32)
_LM2_DEFINE_RANGE2_CONSTRUCTORS(lm2_r2i64, lm2_v2i64)
_LM2_DEFINE_RANGE2_CONSTRUCTORS(lm2_r2i32, lm2_v2i32)
_LM2_DEFINE_RANGE2_CONSTRUCTORS(lm2_r2i16, lm2_v2i16)
_LM2_DEFINE_RANGE2_CONSTRUCTORS(lm2_r2i8, lm2_v2i8)
_LM2_DEFINE_RANGE2_CONSTRUCTORS(lm2_r2u64, lm2_v2u64)
_LM2_DEFINE_RANGE2_CONSTRUCTORS(lm2_r2u32, lm2_v2u32)
_LM2_DEFINE_RANGE2_CONSTRUCTORS(lm2_r2u16, lm2_v2u16)
_LM2_DEFINE_RANGE2_CONSTRUCTORS(lm2_r2u8, lm2_v2u8)
#endif
