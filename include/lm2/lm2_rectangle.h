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
#include "lm2_range2.h"
#include "lm2_vector2.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// Rectangle Corner Enumerations
// =============================================================================

typedef enum lm2_corner2 {
  LM2_CORNER2_TOP_RIGHT,
  LM2_CORNER2_TOP_LEFT,
  LM2_CORNER2_BOTTOM_RIGHT,
  LM2_CORNER2_BOTTOM_LEFT,
} lm2_corner2;

typedef enum lm2_rect_cut {
  LM2_RECT_CUT_LEFT,
  LM2_RECT_CUT_RIGHT,
  LM2_RECT_CUT_TOP,
  LM2_RECT_CUT_BOTTOM,
} lm2_rect_cut;

typedef enum lm2_align {
  LM2_ALIGN_START,
  LM2_ALIGN_CENTER,
  LM2_ALIGN_END,
} lm2_align;

// =============================================================================
// Rectangle Corner Declaration Macros
// =============================================================================

// Get corner by enum
#define _LM2_DECLARE_RECT2_GET_CORNER(type_name, vec_type) \
  LM2_API vec_type type_name##_get_corner(type_name rect, lm2_corner2 corner);

// Get specific corners
#define _LM2_DECLARE_RECT2_GET_BOTTOM_LEFT(type_name, vec_type) \
  LM2_API vec_type type_name##_get_bottom_left(type_name rect);

#define _LM2_DECLARE_RECT2_GET_TOP_RIGHT(type_name, vec_type) \
  LM2_API vec_type type_name##_get_top_right(type_name rect);

#define _LM2_DECLARE_RECT2_GET_BOTTOM_RIGHT(type_name, vec_type) \
  LM2_API vec_type type_name##_get_bottom_right(type_name rect);

#define _LM2_DECLARE_RECT2_GET_TOP_LEFT(type_name, vec_type) \
  LM2_API vec_type type_name##_get_top_left(type_name rect);

// =============================================================================
// Rectangle Transform Declaration Macros
// =============================================================================

// Scale from center point
#define _LM2_DECLARE_RECT2_SCALE_FROM_CENTER(type_name, vec_type) \
  LM2_API type_name type_name##_scale_from_center(type_name rect, vec_type scale);

// Scale from min point
#define _LM2_DECLARE_RECT2_SCALE_FROM_MIN(type_name, vec_type) \
  LM2_API type_name type_name##_scale_from_min(type_name rect, vec_type scale);

// Scale from max point
#define _LM2_DECLARE_RECT2_SCALE_FROM_MAX(type_name, vec_type) \
  LM2_API type_name type_name##_scale_from_max(type_name rect, vec_type scale);

// Shrink by vector amount
#define _LM2_DECLARE_RECT2_SHRINK_VEC(type_name, vec_type) \
  LM2_API type_name type_name##_shrink_vec(type_name rect, vec_type amount);

// Shrink by scalar amount
#define _LM2_DECLARE_RECT2_SHRINK_SCALAR(type_name, scalar_type) \
  LM2_API type_name type_name##_shrink_scalar(type_name rect, scalar_type amount);

// Inflate by vector amount
#define _LM2_DECLARE_RECT2_INFLATE_VEC(type_name, vec_type) \
  LM2_API type_name type_name##_inflate_vec(type_name rect, vec_type amount);

// Inflate by scalar amount
#define _LM2_DECLARE_RECT2_INFLATE_SCALAR(type_name, scalar_type) \
  LM2_API type_name type_name##_inflate_scalar(type_name rect, scalar_type amount);

// =============================================================================
// Rectangle Query Declaration Macros
// =============================================================================

// Get dimension (size) of rectangle
#define _LM2_DECLARE_RECT2_GET_DIM(type_name, vec_type) \
  LM2_API vec_type type_name##_get_dim(type_name rect);

// Check if rectangles overlap
#define _LM2_DECLARE_RECT2_OVERLAP_RECT(type_name) \
  LM2_API int type_name##_overlap_rect(type_name a, type_name b);

// Check if point is in rectangle
#define _LM2_DECLARE_RECT2_OVERLAP_POINT(type_name, vec_type) \
  LM2_API int type_name##_overlap_point(type_name rect, vec_type point);

// Check if rectangle contains another rectangle
#define _LM2_DECLARE_RECT2_CONTAINS(type_name) \
  LM2_API int type_name##_contains(type_name rect, type_name subrect);

// Distance from rectangle to point
#define _LM2_DECLARE_RECT2_DISTANCE(type_name, vec_type, scalar_type) \
  LM2_API scalar_type type_name##_distance(type_name rect, vec_type point);

// Get closest point on/in rectangle to a point
#define _LM2_DECLARE_RECT2_GET_CLOSEST_POINT(type_name, vec_type) \
  LM2_API vec_type type_name##_get_closest_point(type_name rect, vec_type point);

// Closest distance between edges of two rectangles
#define _LM2_DECLARE_RECT2_CLOSEST_DISTANCE_FROM_EDGES(type_name, scalar_type) \
  LM2_API scalar_type type_name##_closest_distance_from_edges(type_name a, type_name b);

// Check if two line segments intersect
#define _LM2_DECLARE_RECT2_SEGMENTS_INTERSECT(vec_type) \
  LM2_API int lm2_segments_intersect_##vec_type(vec_type a0, vec_type a1, vec_type b0, vec_type b1);

// =============================================================================
// Rectangle Cut Declaration Macros
// =============================================================================

// Cut by direction and amount (modifies rect, returns cut piece)
#define _LM2_DECLARE_RECT2_CUT(type_name, scalar_type) \
  LM2_API type_name type_name##_cut(type_name* rect, lm2_rect_cut cut_type, scalar_type amount);

// Cut from left (modifies rect, returns cut piece)
#define _LM2_DECLARE_RECT2_CUT_LEFT(type_name, scalar_type) \
  LM2_API type_name type_name##_cut_left(type_name* rect, scalar_type amount);

// Cut from right (modifies rect, returns cut piece)
#define _LM2_DECLARE_RECT2_CUT_RIGHT(type_name, scalar_type) \
  LM2_API type_name type_name##_cut_right(type_name* rect, scalar_type amount);

// Cut from bottom (modifies rect, returns cut piece)
#define _LM2_DECLARE_RECT2_CUT_BOTTOM(type_name, scalar_type) \
  LM2_API type_name type_name##_cut_bottom(type_name* rect, scalar_type amount);

// Cut from top (modifies rect, returns cut piece)
#define _LM2_DECLARE_RECT2_CUT_TOP(type_name, scalar_type) \
  LM2_API type_name type_name##_cut_top(type_name* rect, scalar_type amount);

// =============================================================================
// Rectangle Alignment Declaration Macros
// =============================================================================

// Align subrectangle within rectangle
#define _LM2_DECLARE_RECT2_ALIGN_SUBRECT(type_name) \
  LM2_API type_name type_name##_align_subrect(type_name rect, type_name subrect, lm2_align align_x, lm2_align align_y);

// =============================================================================
// Rectangle Type Macro - Declares all rectangle operations for a type
// =============================================================================

#define _LM2_DECLARE_RECT2_ALL(type_name, vec_type, scalar_type)         \
  _LM2_DECLARE_RECT2_GET_CORNER(type_name, vec_type)                     \
  _LM2_DECLARE_RECT2_GET_BOTTOM_LEFT(type_name, vec_type)                \
  _LM2_DECLARE_RECT2_GET_TOP_RIGHT(type_name, vec_type)                  \
  _LM2_DECLARE_RECT2_GET_BOTTOM_RIGHT(type_name, vec_type)               \
  _LM2_DECLARE_RECT2_GET_TOP_LEFT(type_name, vec_type)                   \
  _LM2_DECLARE_RECT2_SCALE_FROM_CENTER(type_name, vec_type)              \
  _LM2_DECLARE_RECT2_SCALE_FROM_MIN(type_name, vec_type)                 \
  _LM2_DECLARE_RECT2_SCALE_FROM_MAX(type_name, vec_type)                 \
  _LM2_DECLARE_RECT2_SHRINK_VEC(type_name, vec_type)                     \
  _LM2_DECLARE_RECT2_SHRINK_SCALAR(type_name, scalar_type)               \
  _LM2_DECLARE_RECT2_INFLATE_VEC(type_name, vec_type)                    \
  _LM2_DECLARE_RECT2_INFLATE_SCALAR(type_name, scalar_type)              \
  _LM2_DECLARE_RECT2_GET_DIM(type_name, vec_type)                        \
  _LM2_DECLARE_RECT2_OVERLAP_RECT(type_name)                             \
  _LM2_DECLARE_RECT2_OVERLAP_POINT(type_name, vec_type)                  \
  _LM2_DECLARE_RECT2_CONTAINS(type_name)                                 \
  _LM2_DECLARE_RECT2_DISTANCE(type_name, vec_type, scalar_type)          \
  _LM2_DECLARE_RECT2_GET_CLOSEST_POINT(type_name, vec_type)              \
  _LM2_DECLARE_RECT2_CLOSEST_DISTANCE_FROM_EDGES(type_name, scalar_type) \
  _LM2_DECLARE_RECT2_CUT(type_name, scalar_type)                         \
  _LM2_DECLARE_RECT2_CUT_LEFT(type_name, scalar_type)                    \
  _LM2_DECLARE_RECT2_CUT_RIGHT(type_name, scalar_type)                   \
  _LM2_DECLARE_RECT2_CUT_BOTTOM(type_name, scalar_type)                  \
  _LM2_DECLARE_RECT2_CUT_TOP(type_name, scalar_type)                     \
  _LM2_DECLARE_RECT2_ALIGN_SUBRECT(type_name)

// =============================================================================
// Rectangle Operations for All 10 Types
// =============================================================================

_LM2_DECLARE_RECT2_ALL(lm2_range2f64, lm2_v2f64, double)
_LM2_DECLARE_RECT2_ALL(lm2_range2f32, lm2_v2f32, float)
_LM2_DECLARE_RECT2_ALL(lm2_range2i64, lm2_v2i64, int64_t)
_LM2_DECLARE_RECT2_ALL(lm2_range2i32, lm2_v2i32, int32_t)
_LM2_DECLARE_RECT2_ALL(lm2_range2i16, lm2_v2i16, int16_t)
_LM2_DECLARE_RECT2_ALL(lm2_range2i8, lm2_v2i8, int8_t)
_LM2_DECLARE_RECT2_ALL(lm2_range2u64, lm2_v2u64, uint64_t)
_LM2_DECLARE_RECT2_ALL(lm2_range2u32, lm2_v2u32, uint32_t)
_LM2_DECLARE_RECT2_ALL(lm2_range2u16, lm2_v2u16, uint16_t)
_LM2_DECLARE_RECT2_ALL(lm2_range2u8, lm2_v2u8, uint8_t)

// Segments intersect functions for all vector types
_LM2_DECLARE_RECT2_SEGMENTS_INTERSECT(lm2_v2f64)
_LM2_DECLARE_RECT2_SEGMENTS_INTERSECT(lm2_v2f32)
_LM2_DECLARE_RECT2_SEGMENTS_INTERSECT(lm2_v2i64)
_LM2_DECLARE_RECT2_SEGMENTS_INTERSECT(lm2_v2i32)
_LM2_DECLARE_RECT2_SEGMENTS_INTERSECT(lm2_v2i16)
_LM2_DECLARE_RECT2_SEGMENTS_INTERSECT(lm2_v2i8)
_LM2_DECLARE_RECT2_SEGMENTS_INTERSECT(lm2_v2u64)
_LM2_DECLARE_RECT2_SEGMENTS_INTERSECT(lm2_v2u32)
_LM2_DECLARE_RECT2_SEGMENTS_INTERSECT(lm2_v2u16)
_LM2_DECLARE_RECT2_SEGMENTS_INTERSECT(lm2_v2u8)

// =============================================================================
// Convenience typedefs
// =============================================================================

// The range2 types are the rectangle types (rectangles are AABBs)
typedef lm2_range2f64 lm2_rect2f64;
typedef lm2_range2f32 lm2_rect2f32;
typedef lm2_range2i64 lm2_rect2i64;
typedef lm2_range2i32 lm2_rect2i32;
typedef lm2_range2i16 lm2_rect2i16;
typedef lm2_range2i8 lm2_rect2i8;
typedef lm2_range2u64 lm2_rect2u64;
typedef lm2_range2u32 lm2_rect2u32;
typedef lm2_range2u16 lm2_rect2u16;
typedef lm2_range2u8 lm2_rect2u8;

// Default rectangle type (float-based)
typedef lm2_range2f32 lm2_rect2;

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// =============================================================================
// Generic Rectangle Functions (Type-Dispatched)
// =============================================================================

#ifndef LM2_NO_GENERICS
// Corner functions
#  define lm2_rect2_get_corner(...)       _LM2_GENERIC_RANGE2(get_corner, __VA_ARGS__)
#  define lm2_rect2_get_bottom_left(...)  _LM2_GENERIC_RANGE2(get_bottom_left, __VA_ARGS__)
#  define lm2_rect2_get_top_right(...)    _LM2_GENERIC_RANGE2(get_top_right, __VA_ARGS__)
#  define lm2_rect2_get_bottom_right(...) _LM2_GENERIC_RANGE2(get_bottom_right, __VA_ARGS__)
#  define lm2_rect2_get_top_left(...)     _LM2_GENERIC_RANGE2(get_top_left, __VA_ARGS__)

// Transform functions (with vector parameter)
#  define lm2_rect2_scale_from_center(...) _LM2_GENERIC_RANGE2_VEC(scale_from_center, __VA_ARGS__)
#  define lm2_rect2_scale_from_min(...)    _LM2_GENERIC_RANGE2_VEC(scale_from_min, __VA_ARGS__)
#  define lm2_rect2_scale_from_max(...)    _LM2_GENERIC_RANGE2_VEC(scale_from_max, __VA_ARGS__)
#  define lm2_rect2_shrink_vec(...)        _LM2_GENERIC_RANGE2_VEC(shrink_vec, __VA_ARGS__)
#  define lm2_rect2_inflate_vec(...)       _LM2_GENERIC_RANGE2_VEC(inflate_vec, __VA_ARGS__)

// Transform functions (with scalar parameter)
#  define lm2_rect2_shrink_scalar(...)  _LM2_GENERIC_RANGE2_SCALAR(shrink_scalar, __VA_ARGS__)
#  define lm2_rect2_inflate_scalar(...) _LM2_GENERIC_RANGE2_SCALAR(inflate_scalar, __VA_ARGS__)

// Query functions
#  define lm2_rect2_get_dim(...)                     _LM2_GENERIC_RANGE2(get_dim, __VA_ARGS__)
#  define lm2_rect2_overlap_rect(...)                _LM2_GENERIC_RANGE2(overlap_rect, __VA_ARGS__)
#  define lm2_rect2_overlap_point(...)               _LM2_GENERIC_RANGE2_VEC(overlap_point, __VA_ARGS__)
#  define lm2_rect2_contains(...)                    _LM2_GENERIC_RANGE2(contains, __VA_ARGS__)
#  define lm2_rect2_distance(...)                    _LM2_GENERIC_RANGE2_VEC(distance, __VA_ARGS__)
#  define lm2_rect2_get_closest_point(...)           _LM2_GENERIC_RANGE2_VEC(get_closest_point, __VA_ARGS__)
#  define lm2_rect2_closest_distance_from_edges(...) _LM2_GENERIC_RANGE2(closest_distance_from_edges, __VA_ARGS__)

// Alignment functions
#  define lm2_rect2_align_subrect(...) _LM2_GENERIC_RANGE2(align_subrect, __VA_ARGS__)
#endif
