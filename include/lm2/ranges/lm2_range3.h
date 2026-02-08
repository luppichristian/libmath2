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
#include "lm2/vectors/lm2_vector3.h"
#include "lm2_range_defines.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// 3D Range (AABB) Type Definitions
// =============================================================================
// A range3 represents a 3D axis-aligned bounding box (AABB) or cube/box
// with minimum and maximum points.
#define _LM2_DEFINE_RANGE3(type_name, vec_type, scalar_type)      \
  typedef union type_name {                                       \
    vec_type e[2];                                                \
    struct {                                                      \
      vec_type min;                                               \
      vec_type max;                                               \
    };                                                            \
    _LM2_RANGE3_CPP_CONSTRUCTORS(type_name, vec_type)             \
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
  _LM2_DECLARE_RANGE3_VOLUME(type_name, scalar_type)              \
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

// 3D Range types for all 10 numeric types
_LM2_DEFINE_RANGE3(lm2_r3f64, lm2_v3f64, double)
_LM2_DEFINE_RANGE3(lm2_r3f32, lm2_v3f32, float)
_LM2_DEFINE_RANGE3(lm2_r3i64, lm2_v3i64, int64_t)
_LM2_DEFINE_RANGE3(lm2_r3i32, lm2_v3i32, int32_t)
_LM2_DEFINE_RANGE3(lm2_r3i16, lm2_v3i16, int16_t)
_LM2_DEFINE_RANGE3(lm2_r3i8, lm2_v3i8, int8_t)
_LM2_DEFINE_RANGE3(lm2_r3u64, lm2_v3u64, uint64_t)
_LM2_DEFINE_RANGE3(lm2_r3u32, lm2_v3u32, uint32_t)
_LM2_DEFINE_RANGE3(lm2_r3u16, lm2_v3u16, uint16_t)
_LM2_DEFINE_RANGE3(lm2_r3u8, lm2_v3u8, uint8_t)

// Default range3 type (float-based)
typedef lm2_r3f32 lm2_r3;

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// Generics
#ifndef LM2_NO_GENERICS
#  include "lm2_range_generics.h"
#  define lm2_floor_r3(...)          _LM2_GENERIC_RANGE3(lm2_floor, __VA_ARGS__)
#  define lm2_ceil_r3(...)           _LM2_GENERIC_RANGE3(lm2_ceil, __VA_ARGS__)
#  define lm2_round_r3(...)          _LM2_GENERIC_RANGE3(lm2_round, __VA_ARGS__)
#  define lm2_trunc_r3(...)          _LM2_GENERIC_RANGE3(lm2_trunc, __VA_ARGS__)
#  define lm2_abs_r3(...)            _LM2_GENERIC_RANGE3(lm2_abs, __VA_ARGS__)
#  define lm2_floor_multiple_r3(...) _LM2_GENERIC_RANGE3(lm2_floor_multiple, __VA_ARGS__)
#  define lm2_ceil_multiple_r3(...)  _LM2_GENERIC_RANGE3(lm2_ceil_multiple, __VA_ARGS__)
#  define lm2_round_multiple_r3(...) _LM2_GENERIC_RANGE3(lm2_round_multiple, __VA_ARGS__)
#  define lm2_trunc_multiple_r3(...) _LM2_GENERIC_RANGE3(lm2_trunc_multiple, __VA_ARGS__)
#  define lm2_min_r3(...)            _LM2_GENERIC_RANGE3(lm2_min, __VA_ARGS__)
#  define lm2_max_r3(...)            _LM2_GENERIC_RANGE3(lm2_max, __VA_ARGS__)
#  define lm2_clamp_r3(...)          _LM2_GENERIC_RANGE3(lm2_clamp, __VA_ARGS__)
#  define lm2_lerp_r3(...)           _LM2_GENERIC_RANGE3(lm2_lerp, __VA_ARGS__)
#  define lm2_normalize_r3(...)      _LM2_GENERIC_RANGE3(normalize, __VA_ARGS__)
#  define lm2_translate_r3(...)      _LM2_GENERIC_RANGE3(translate, __VA_ARGS__)
#  define lm2_scale_r3(...)          _LM2_GENERIC_RANGE3(scale, __VA_ARGS__)
#  define lm2_expand_r3(...)         _LM2_GENERIC_RANGE3(expand, __VA_ARGS__)
#  define lm2_contains_point_r3(...) _LM2_GENERIC_RANGE3(contains_point, __VA_ARGS__)
#  define lm2_overlaps_r3(...)       _LM2_GENERIC_RANGE3(overlaps, __VA_ARGS__)
#  define lm2_size_r3(...)           _LM2_GENERIC_RANGE3(size, __VA_ARGS__)
#  define lm2_extents_r3(...)        _LM2_GENERIC_RANGE3(extents, __VA_ARGS__)
#  define lm2_center_r3(...)         _LM2_GENERIC_RANGE3(center, __VA_ARGS__)
#  define lm2_volume_r3(...)         _LM2_GENERIC_RANGE3(volume, __VA_ARGS__)
// Arithmetic operations (support range+range, range+vector, range+scalar)
#  define lm2_add_r3(r, x)                _LM2_RANGE3_ARITH(add, r, x)
#  define lm2_sub_r3(r, x)                _LM2_RANGE3_ARITH(sub, r, x)
#  define lm2_mul_r3(r, x)                _LM2_RANGE3_ARITH(mul, r, x)
#  define lm2_div_r3(r, x)                _LM2_RANGE3_ARITH(div, r, x)
#  define lm2_mod_r3(r, x)                _LM2_RANGE3_ARITH(mod, r, x)
#  define lm2_r3_from_min_max(...)        _LM2_GENERIC_RANGE3(from_min_max, __VA_ARGS__)
#  define lm2_r3_from_center_extents(...) _LM2_GENERIC_RANGE3(from_center_extents, __VA_ARGS__)
#  define lm2_r3_from_center_size(...)    _LM2_GENERIC_RANGE3(from_center_size, __VA_ARGS__)
#  define lm2_r3_from_position_size(...)  _LM2_GENERIC_RANGE3(from_position_size, __VA_ARGS__)
#endif

// C++ operator overloads and constructors (must be outside extern "C")
#ifndef LM2_NO_CPP_OPERATORS
#  include "lm2_range_operators.h"
_LM2_DEFINE_RANGE3_OPERATORS(lm2_r3f64, lm2_v3f64)
_LM2_DEFINE_RANGE3_OPERATORS(lm2_r3f32, lm2_v3f32)
_LM2_DEFINE_RANGE3_OPERATORS(lm2_r3i64, lm2_v3i64)
_LM2_DEFINE_RANGE3_OPERATORS(lm2_r3i32, lm2_v3i32)
_LM2_DEFINE_RANGE3_OPERATORS(lm2_r3i16, lm2_v3i16)
_LM2_DEFINE_RANGE3_OPERATORS(lm2_r3i8, lm2_v3i8)
_LM2_DEFINE_RANGE3_OPERATORS(lm2_r3u64, lm2_v3u64)
_LM2_DEFINE_RANGE3_OPERATORS(lm2_r3u32, lm2_v3u32)
_LM2_DEFINE_RANGE3_OPERATORS(lm2_r3u16, lm2_v3u16)
_LM2_DEFINE_RANGE3_OPERATORS(lm2_r3u8, lm2_v3u8)
#endif
