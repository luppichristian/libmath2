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
_LM2_DEFINE_RANGE4(lm2_r4f64, lm2_v4f64, double)
_LM2_DEFINE_RANGE4(lm2_r4f32, lm2_v4f32, float)
_LM2_DEFINE_RANGE4(lm2_r4i64, lm2_v4i64, int64_t)
_LM2_DEFINE_RANGE4(lm2_r4i32, lm2_v4i32, int32_t)
_LM2_DEFINE_RANGE4(lm2_r4i16, lm2_v4i16, int16_t)
_LM2_DEFINE_RANGE4(lm2_r4i8, lm2_v4i8, int8_t)
_LM2_DEFINE_RANGE4(lm2_r4u64, lm2_v4u64, uint64_t)
_LM2_DEFINE_RANGE4(lm2_r4u32, lm2_v4u32, uint32_t)
_LM2_DEFINE_RANGE4(lm2_r4u16, lm2_v4u16, uint16_t)
_LM2_DEFINE_RANGE4(lm2_r4u8, lm2_v4u8, uint8_t)

// Default range4 type (float-based)
typedef lm2_r4f32 lm2_r4;

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// C++ operator overloads and constructors (must be outside extern "C")
#ifndef LM2_NO_CPP_OPERATORS
#  include "lm2_range_operators.h"
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4f64, lm2_v4f64)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4f32, lm2_v4f32)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4i64, lm2_v4i64)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4i32, lm2_v4i32)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4i16, lm2_v4i16)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4i8, lm2_v4i8)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4u64, lm2_v4u64)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4u32, lm2_v4u32)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4u16, lm2_v4u16)
_LM2_DEFINE_RANGE4_OPERATORS(lm2_r4u8, lm2_v4u8)
#endif
