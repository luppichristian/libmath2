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

// =============================================================================
// C++ Array Subscript Operator for Range Unions
// =============================================================================

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
// Generic Range Constructor Declaration Macros
// =============================================================================
// These macros work for all range dimensions (2D, 3D, 4D)

// Create range from min and max points
#define _LM2_DECLARE_RANGE_FROM_MIN_MAX(type_name, vec_type) \
  LM2_API type_name type_name##_from_min_max(vec_type min, vec_type max);

// Create range from center point and extents (half-size)
#define _LM2_DECLARE_RANGE_FROM_CENTER_EXTENTS(type_name, vec_type) \
  LM2_API type_name type_name##_from_center_extents(vec_type center, vec_type extents);

// Create range from center point and full size
#define _LM2_DECLARE_RANGE_FROM_CENTER_SIZE(type_name, vec_type) \
  LM2_API type_name type_name##_from_center_size(vec_type center, vec_type size);

// Create range from position (min) and size
#define _LM2_DECLARE_RANGE_FROM_POSITION_SIZE(type_name, vec_type) \
  LM2_API type_name type_name##_from_position_size(vec_type position, vec_type size);

// Create zero range (min and max at origin)
#define _LM2_DECLARE_RANGE_ZERO(type_name) \
  LM2_API type_name type_name##_zero(void);

// =============================================================================
// Generic Range Operation Declaration Macros
// =============================================================================

// Normalize range (ensure min <= max)
#define _LM2_DECLARE_RANGE_NORMALIZE(type_name) \
  LM2_API type_name type_name##_normalize(type_name r);

// Translate range by offset
#define _LM2_DECLARE_RANGE_TRANSLATE(type_name, vec_type) \
  LM2_API type_name type_name##_translate(type_name r, vec_type offset);

// Scale range around center
#define _LM2_DECLARE_RANGE_SCALE(type_name, scalar_type) \
  LM2_API type_name type_name##_scale(type_name r, scalar_type factor);

// Expand range by amount (adds to extents)
#define _LM2_DECLARE_RANGE_EXPAND(type_name, scalar_type) \
  LM2_API type_name type_name##_expand(type_name r, scalar_type amount);

// Union of two ranges (bounding box containing both)
#define _LM2_DECLARE_RANGE_UNION(type_name) \
  LM2_API type_name type_name##_union(type_name a, type_name b);

// Intersection of two ranges (overlapping region)
#define _LM2_DECLARE_RANGE_INTERSECTION(type_name) \
  LM2_API type_name type_name##_intersection(type_name a, type_name b);

// =============================================================================
// Range Arithmetic Operation Declaration Macros
// =============================================================================
// Component-wise arithmetic operations on ranges.
// Each operation is available in three variants:
//   - range ⊕ range: operates component-wise on both min and max
//   - range ⊕ scalar: applies scalar to all components of min and max
//   - range ⊕ vector: applies vector to both min and max

// Add operations
#define _LM2_DECLARE_RANGE_ADD_RANGE(type_name) \
  LM2_API type_name type_name##_add(type_name a, type_name b);

#define _LM2_DECLARE_RANGE_ADD_SCALAR(type_name, scalar_type) \
  LM2_API type_name type_name##_add_scalar(type_name r, scalar_type s);

#define _LM2_DECLARE_RANGE_ADD_VECTOR(type_name, vec_type) \
  LM2_API type_name type_name##_add_vec(type_name r, vec_type v);

// Subtract operations
#define _LM2_DECLARE_RANGE_SUB_RANGE(type_name) \
  LM2_API type_name type_name##_sub(type_name a, type_name b);

#define _LM2_DECLARE_RANGE_SUB_SCALAR(type_name, scalar_type) \
  LM2_API type_name type_name##_sub_scalar(type_name r, scalar_type s);

#define _LM2_DECLARE_RANGE_SUB_VECTOR(type_name, vec_type) \
  LM2_API type_name type_name##_sub_vec(type_name r, vec_type v);

// Multiply operations
#define _LM2_DECLARE_RANGE_MUL_RANGE(type_name) \
  LM2_API type_name type_name##_mul(type_name a, type_name b);

#define _LM2_DECLARE_RANGE_MUL_SCALAR(type_name, scalar_type) \
  LM2_API type_name type_name##_mul_scalar(type_name r, scalar_type s);

#define _LM2_DECLARE_RANGE_MUL_VECTOR(type_name, vec_type) \
  LM2_API type_name type_name##_mul_vec(type_name r, vec_type v);

// Divide operations
#define _LM2_DECLARE_RANGE_DIV_RANGE(type_name) \
  LM2_API type_name type_name##_div(type_name a, type_name b);

#define _LM2_DECLARE_RANGE_DIV_SCALAR(type_name, scalar_type) \
  LM2_API type_name type_name##_div_scalar(type_name r, scalar_type s);

#define _LM2_DECLARE_RANGE_DIV_VECTOR(type_name, vec_type) \
  LM2_API type_name type_name##_div_vec(type_name r, vec_type v);

// Modulo operations
#define _LM2_DECLARE_RANGE_MOD_RANGE(type_name) \
  LM2_API type_name type_name##_mod(type_name a, type_name b);

#define _LM2_DECLARE_RANGE_MOD_SCALAR(type_name, scalar_type) \
  LM2_API type_name type_name##_mod_scalar(type_name r, scalar_type s);

#define _LM2_DECLARE_RANGE_MOD_VECTOR(type_name, vec_type) \
  LM2_API type_name type_name##_mod_vec(type_name r, vec_type v);

// Convenience macro to declare all arithmetic operations for a range type
#define _LM2_DECLARE_RANGE_ARITHMETIC(type_name, vec_type, scalar_type) \
  _LM2_DECLARE_RANGE_ADD_RANGE(type_name)                               \
  _LM2_DECLARE_RANGE_ADD_SCALAR(type_name, scalar_type)                 \
  _LM2_DECLARE_RANGE_ADD_VECTOR(type_name, vec_type)                    \
  _LM2_DECLARE_RANGE_SUB_RANGE(type_name)                               \
  _LM2_DECLARE_RANGE_SUB_SCALAR(type_name, scalar_type)                 \
  _LM2_DECLARE_RANGE_SUB_VECTOR(type_name, vec_type)                    \
  _LM2_DECLARE_RANGE_MUL_RANGE(type_name)                               \
  _LM2_DECLARE_RANGE_MUL_SCALAR(type_name, scalar_type)                 \
  _LM2_DECLARE_RANGE_MUL_VECTOR(type_name, vec_type)                    \
  _LM2_DECLARE_RANGE_DIV_RANGE(type_name)                               \
  _LM2_DECLARE_RANGE_DIV_SCALAR(type_name, scalar_type)                 \
  _LM2_DECLARE_RANGE_DIV_VECTOR(type_name, vec_type)                    \
  _LM2_DECLARE_RANGE_MOD_RANGE(type_name)                               \
  _LM2_DECLARE_RANGE_MOD_SCALAR(type_name, scalar_type)                 \
  _LM2_DECLARE_RANGE_MOD_VECTOR(type_name, vec_type)

// =============================================================================
// Generic Range Query Declaration Macros
// =============================================================================

// Get size of range (max - min)
#define _LM2_DECLARE_RANGE_SIZE(type_name, vec_type) \
  LM2_API vec_type type_name##_size(type_name r);

// Get extents (half-size)
#define _LM2_DECLARE_RANGE_EXTENTS(type_name, vec_type) \
  LM2_API vec_type type_name##_extents(type_name r);

// Get center point
#define _LM2_DECLARE_RANGE_CENTER(type_name, vec_type) \
  LM2_API vec_type type_name##_center(type_name r);

// Check if point is inside range
#define _LM2_DECLARE_RANGE_CONTAINS_POINT(type_name, vec_type) \
  LM2_API int type_name##_contains_point(type_name r, vec_type point);

// Check if two ranges overlap
#define _LM2_DECLARE_RANGE_OVERLAPS(type_name) \
  LM2_API int type_name##_overlaps(type_name a, type_name b);

// =============================================================================
// Dimension-Specific Query Declaration Macros
// =============================================================================

// Get area of range (2D only)
#define _LM2_DECLARE_RANGE2_AREA(type_name, scalar_type) \
  LM2_API scalar_type type_name##_area(type_name r);

// Get volume of range (3D only)
#define _LM2_DECLARE_RANGE3_VOLUME(type_name, scalar_type) \
  LM2_API scalar_type type_name##_volume(type_name r);

// Get hypervolume of range (4D only)
#define _LM2_DECLARE_RANGE4_HYPERVOLUME(type_name, scalar_type) \
  LM2_API scalar_type type_name##_hypervolume(type_name r);

// =============================================================================
// Generic Range Scalar Function Declaration Macros
// =============================================================================
// These macros forward scalar functions to ranges by applying them
// component-wise to both min and max vectors.

// Unary scalar function (e.g., floor, ceil, abs, sqrt)
#define _LM2_DECLARE_RANGE_SCALAR_FUNC_1(type_name, func_name) \
  LM2_API type_name func_name##_##type_name(type_name a);

// Binary scalar function (e.g., min, max, pow, mod)
#define _LM2_DECLARE_RANGE_SCALAR_FUNC_2(type_name, func_name) \
  LM2_API type_name func_name##_##type_name(type_name a, type_name b);

// Ternary scalar function (e.g., clamp, lerp, smoothstep)
#define _LM2_DECLARE_RANGE_SCALAR_FUNC_3(type_name, func_name) \
  LM2_API type_name func_name##_##type_name(type_name a, type_name b, type_name c);

// =============================================================================
// C++ Constructors for Range Types
// =============================================================================
// These macros inject actual C++ constructors into range unions.

#if defined(__cplusplus) && !defined(LM2_NO_CPP_OPERATORS)
// Range2 constructors
#  define _LM2_RANGE2_CPP_CONSTRUCTORS(type_name, vec_type)     \
    type_name() {                                               \
      min = vec_type();                                         \
      max = vec_type();                                         \
    }                                                           \
    type_name(vec_type min, vec_type max): min(min), max(max) { \
    }

// Range3 constructors
#  define _LM2_RANGE3_CPP_CONSTRUCTORS(type_name, vec_type)     \
    type_name() {                                               \
      min = vec_type();                                         \
      max = vec_type();                                         \
    }                                                           \
    type_name(vec_type min, vec_type max): min(min), max(max) { \
    }

// Range4 constructors
#  define _LM2_RANGE4_CPP_CONSTRUCTORS(type_name, vec_type)     \
    type_name() {                                               \
      min = vec_type();                                         \
      max = vec_type();                                         \
    }                                                           \
    type_name(vec_type min, vec_type max): min(min), max(max) { \
    }
#else
#  define _LM2_RANGE2_CPP_CONSTRUCTORS(type_name, vec_type)
#  define _LM2_RANGE3_CPP_CONSTRUCTORS(type_name, vec_type)
#  define _LM2_RANGE4_CPP_CONSTRUCTORS(type_name, vec_type)
#endif

// #############################################################################
LM2_HEADER_END;
// #############################################################################
