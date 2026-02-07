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

#include "lm2_base.h"
#include "lm2_vector4.h"

// C++ array subscript operator for range unions
#if defined(__cplusplus) && !defined(LM2_NO_CPP_OPERATORS)
#  define _LM2_RANGE_SUBSCRIPT_OP(vec_type)          \
    inline vec_type& operator[](int i) {             \
      return e[i];                                   \
    }                                                \
    inline const vec_type& operator[](int i) const { \
      return e[i];                                   \
    }
#else
#  define _LM2_RANGE_SUBSCRIPT_OP(vec_type)
#endif

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// Range4 Constructor Declaration Macros
// =============================================================================

// Create range from min and max points
#define _LM2_DECLARE_RANGE4_FROM_MIN_MAX(type_name, vec_type) \
  LM2_API type_name type_name##_from_min_max(vec_type min, vec_type max);

// Create range from center point and extents (half-size)
#define _LM2_DECLARE_RANGE4_FROM_CENTER_EXTENTS(type_name, vec_type) \
  LM2_API type_name type_name##_from_center_extents(vec_type center, vec_type extents);

// Create range from center point and full size
#define _LM2_DECLARE_RANGE4_FROM_CENTER_SIZE(type_name, vec_type) \
  LM2_API type_name type_name##_from_center_size(vec_type center, vec_type size);

// Create range from position (min) and size
#define _LM2_DECLARE_RANGE4_FROM_POSITION_SIZE(type_name, vec_type) \
  LM2_API type_name type_name##_from_position_size(vec_type position, vec_type size);

// Create zero range (min and max at origin)
#define _LM2_DECLARE_RANGE4_ZERO(type_name) \
  LM2_API type_name type_name##_zero(void);

// =============================================================================
// Range4 Operation Declaration Macros
// =============================================================================

// Normalize range (ensure min <= max)
#define _LM2_DECLARE_RANGE4_NORMALIZE(type_name) \
  LM2_API type_name type_name##_normalize(type_name r);

// Translate range by offset
#define _LM2_DECLARE_RANGE4_TRANSLATE(type_name, vec_type) \
  LM2_API type_name type_name##_translate(type_name r, vec_type offset);

// Scale range around center
#define _LM2_DECLARE_RANGE4_SCALE(type_name, scalar_type) \
  LM2_API type_name type_name##_scale(type_name r, scalar_type factor);

// Expand range by amount (adds to extents)
#define _LM2_DECLARE_RANGE4_EXPAND(type_name, scalar_type) \
  LM2_API type_name type_name##_expand(type_name r, scalar_type amount);

// Union of two ranges (bounding box containing both)
#define _LM2_DECLARE_RANGE4_UNION(type_name) \
  LM2_API type_name type_name##_union(type_name a, type_name b);

// Intersection of two ranges (overlapping region)
#define _LM2_DECLARE_RANGE4_INTERSECTION(type_name) \
  LM2_API type_name type_name##_intersection(type_name a, type_name b);

// =============================================================================
// Range4 Query Declaration Macros
// =============================================================================

// Get size of range (max - min)
#define _LM2_DECLARE_RANGE4_SIZE(type_name, vec_type) \
  LM2_API vec_type type_name##_size(type_name r);

// Get extents (half-size)
#define _LM2_DECLARE_RANGE4_EXTENTS(type_name, vec_type) \
  LM2_API vec_type type_name##_extents(type_name r);

// Get center point
#define _LM2_DECLARE_RANGE4_CENTER(type_name, vec_type) \
  LM2_API vec_type type_name##_center(type_name r);

// Check if point is inside range
#define _LM2_DECLARE_RANGE4_CONTAINS_POINT(type_name, vec_type) \
  LM2_API int type_name##_contains_point(type_name r, vec_type point);

// Check if two ranges overlap
#define _LM2_DECLARE_RANGE4_OVERLAPS(type_name) \
  LM2_API int type_name##_overlaps(type_name a, type_name b);

// Get hypervolume of range (4D volume)
#define _LM2_DECLARE_RANGE4_HYPERVOLUME(type_name, scalar_type) \
  LM2_API scalar_type type_name##_hypervolume(type_name r);

// =============================================================================
// Range4 Scalar Function Declaration Macros
// =============================================================================
// These macros forward scalar functions to ranges by applying them
// component-wise to both min and max vectors.

// Unary scalar function (e.g., floor, ceil, abs, sqrt)
#define _LM2_DECLARE_RANGE4_SCALAR_FUNC_1(type_name, func_name) \
  LM2_API type_name func_name##_##type_name(type_name a);

// Binary scalar function (e.g., min, max, pow, mod)
#define _LM2_DECLARE_RANGE4_SCALAR_FUNC_2(type_name, func_name) \
  LM2_API type_name func_name##_##type_name(type_name a, type_name b);

// Ternary scalar function (e.g., clamp, lerp, smoothstep)
#define _LM2_DECLARE_RANGE4_SCALAR_FUNC_3(type_name, func_name) \
  LM2_API type_name func_name##_##type_name(type_name a, type_name b, type_name c);

// =============================================================================
// 4D Range (AABB) Type Definitions
// =============================================================================
// A range4 represents a 4D axis-aligned bounding box (hyperrectangle)
// with minimum and maximum points.

#define _LM2_DEFINE_RANGE4(type_name, vec_type, scalar_type)       \
  typedef union type_name {                                        \
    vec_type e[2];                                                 \
    struct {                                                       \
      vec_type min;                                                \
      vec_type max;                                                \
    };                                                             \
    _LM2_RANGE_SUBSCRIPT_OP(vec_type)                              \
  } type_name;                                                     \
  _LM2_DECLARE_RANGE4_FROM_MIN_MAX(type_name, vec_type)            \
  _LM2_DECLARE_RANGE4_FROM_CENTER_EXTENTS(type_name, vec_type)     \
  _LM2_DECLARE_RANGE4_FROM_CENTER_SIZE(type_name, vec_type)        \
  _LM2_DECLARE_RANGE4_FROM_POSITION_SIZE(type_name, vec_type)      \
  _LM2_DECLARE_RANGE4_ZERO(type_name)                              \
  _LM2_DECLARE_RANGE4_NORMALIZE(type_name)                         \
  _LM2_DECLARE_RANGE4_TRANSLATE(type_name, vec_type)               \
  _LM2_DECLARE_RANGE4_SCALE(type_name, scalar_type)                \
  _LM2_DECLARE_RANGE4_EXPAND(type_name, scalar_type)               \
  _LM2_DECLARE_RANGE4_UNION(type_name)                             \
  _LM2_DECLARE_RANGE4_INTERSECTION(type_name)                      \
  _LM2_DECLARE_RANGE4_SIZE(type_name, vec_type)                    \
  _LM2_DECLARE_RANGE4_EXTENTS(type_name, vec_type)                 \
  _LM2_DECLARE_RANGE4_CENTER(type_name, vec_type)                  \
  _LM2_DECLARE_RANGE4_CONTAINS_POINT(type_name, vec_type)          \
  _LM2_DECLARE_RANGE4_OVERLAPS(type_name)                          \
  _LM2_DECLARE_RANGE4_HYPERVOLUME(type_name, scalar_type)          \
  _LM2_DECLARE_RANGE4_SCALAR_FUNC_1(type_name, lm2_floor)          \
  _LM2_DECLARE_RANGE4_SCALAR_FUNC_1(type_name, lm2_ceil)           \
  _LM2_DECLARE_RANGE4_SCALAR_FUNC_1(type_name, lm2_round)          \
  _LM2_DECLARE_RANGE4_SCALAR_FUNC_1(type_name, lm2_trunc)          \
  _LM2_DECLARE_RANGE4_SCALAR_FUNC_1(type_name, lm2_abs)            \
  _LM2_DECLARE_RANGE4_SCALAR_FUNC_2(type_name, lm2_floor_multiple) \
  _LM2_DECLARE_RANGE4_SCALAR_FUNC_2(type_name, lm2_ceil_multiple)  \
  _LM2_DECLARE_RANGE4_SCALAR_FUNC_2(type_name, lm2_round_multiple) \
  _LM2_DECLARE_RANGE4_SCALAR_FUNC_2(type_name, lm2_trunc_multiple) \
  _LM2_DECLARE_RANGE4_SCALAR_FUNC_2(type_name, lm2_min)            \
  _LM2_DECLARE_RANGE4_SCALAR_FUNC_2(type_name, lm2_max)            \
  _LM2_DECLARE_RANGE4_SCALAR_FUNC_3(type_name, lm2_clamp)          \
  _LM2_DECLARE_RANGE4_SCALAR_FUNC_3(type_name, lm2_lerp)

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
