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

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// Capsule Types
// =============================================================================

// Capsule structure to represent a 2D capsule (line segment with radius)
typedef struct lm2_capsule_f64 {
  lm2_v2f64 start, end;
  double radius;
} lm2_capsule_f64;

typedef struct lm2_capsule_f32 {
  lm2_v2f32 start, end;
  float radius;
} lm2_capsule_f32;

// Default capsule type
typedef lm2_capsule_f32 lm2_capsule;

// =============================================================================
// Construction Helpers
// =============================================================================

// Create a capsule from two points and radius
LM2_API lm2_capsule_f64 lm2_capsule_make_f64(lm2_v2f64 start, lm2_v2f64 end, double radius);
LM2_API lm2_capsule_f32 lm2_capsule_make_f32(lm2_v2f32 start, lm2_v2f32 end, float radius);

// Create a capsule from coordinates and radius
LM2_API lm2_capsule_f64 lm2_capsule_make_coords_f64(double x1, double y1, double x2, double y2, double radius);
LM2_API lm2_capsule_f32 lm2_capsule_make_coords_f32(float x1, float y1, float x2, float y2, float radius);

// Create a capsule from center, direction, half-length, and radius
LM2_API lm2_capsule_f64 lm2_capsule_from_center_f64(lm2_v2f64 center, lm2_v2f64 direction, double half_length, double radius);
LM2_API lm2_capsule_f32 lm2_capsule_from_center_f32(lm2_v2f32 center, lm2_v2f32 direction, float half_length, float radius);

// =============================================================================
// Capsule Properties
// =============================================================================

// Get the length of the capsule's line segment
LM2_API double lm2_capsule_length_f64(lm2_capsule_f64 capsule);
LM2_API float lm2_capsule_length_f32(lm2_capsule_f32 capsule);

// Get the total length including rounded ends (length + 2*radius)
LM2_API double lm2_capsule_total_length_f64(lm2_capsule_f64 capsule);
LM2_API float lm2_capsule_total_length_f32(lm2_capsule_f32 capsule);

// Get the area of the capsule
LM2_API double lm2_capsule_area_f64(lm2_capsule_f64 capsule);
LM2_API float lm2_capsule_area_f32(lm2_capsule_f32 capsule);

// Get the perimeter of the capsule
LM2_API double lm2_capsule_perimeter_f64(lm2_capsule_f64 capsule);
LM2_API float lm2_capsule_perimeter_f32(lm2_capsule_f32 capsule);

// Get the center point of the capsule
LM2_API lm2_v2f64 lm2_capsule_center_f64(lm2_capsule_f64 capsule);
LM2_API lm2_v2f32 lm2_capsule_center_f32(lm2_capsule_f32 capsule);

// =============================================================================
// Capsule Tests
// =============================================================================

// Check if a point is inside a capsule
LM2_API bool lm2_capsule_contains_point_f64(lm2_capsule_f64 capsule, lm2_v2f64 point);
LM2_API bool lm2_capsule_contains_point_f32(lm2_capsule_f32 capsule, lm2_v2f32 point);

// Check if two capsules overlap
LM2_API bool lm2_capsules_overlap_f64(lm2_capsule_f64 a, lm2_capsule_f64 b);
LM2_API bool lm2_capsules_overlap_f32(lm2_capsule_f32 a, lm2_capsule_f32 b);

// =============================================================================
// Capsule Transformations
// =============================================================================

// Translate a capsule by an offset
LM2_API lm2_capsule_f64 lm2_capsule_translate_f64(lm2_capsule_f64 capsule, lm2_v2f64 offset);
LM2_API lm2_capsule_f32 lm2_capsule_translate_f32(lm2_capsule_f32 capsule, lm2_v2f32 offset);

// Scale a capsule's radius
LM2_API lm2_capsule_f64 lm2_capsule_scale_radius_f64(lm2_capsule_f64 capsule, double scale);
LM2_API lm2_capsule_f32 lm2_capsule_scale_radius_f32(lm2_capsule_f32 capsule, float scale);

// =============================================================================
// Generic Macros
// =============================================================================

#ifndef LM2_NO_GENERICS
#  ifdef __cplusplus
#    define _LM2_CAPSULE_GENERIC(name, ...) \
      _Generic((__VA_ARGS__),               \
          lm2_capsule_f64: name##_f64,      \
          lm2_capsule_f32: name##_f32,      \
          lm2_v2f64: name##_f64,            \
          lm2_v2f32: name##_f32,            \
          double: name##_f64,               \
          float: name##_f32)(__VA_ARGS__)
#  else
#    define _LM2_CAPSULE_GENERIC(name, ...) \
      _Generic((__VA_ARGS__),               \
          lm2_capsule_f64: name##_f64,      \
          lm2_capsule_f32: name##_f32,      \
          lm2_v2f64: name##_f64,            \
          lm2_v2f32: name##_f32,            \
          double: name##_f64,               \
          float: name##_f32)(__VA_ARGS__)
#  endif

// Construction helpers
#  define lm2_capsule_make(...) _LM2_CAPSULE_GENERIC(lm2_capsule_make, __VA_ARGS__)
#  define lm2_capsule_make_coords(x1, y1, x2, y2, r) \
    _Generic((x1),                                   \
        double: lm2_capsule_make_coords_f64,         \
        float: lm2_capsule_make_coords_f32)(x1, y1, x2, y2, r)
#  define lm2_capsule_from_center(center, dir, half_len, r) \
    _Generic((center).x,                                    \
        double: lm2_capsule_from_center_f64,                \
        float: lm2_capsule_from_center_f32)(center, dir, half_len, r)

// Capsule properties
#  define lm2_capsule_length(capsule)       _LM2_CAPSULE_GENERIC(lm2_capsule_length, capsule)
#  define lm2_capsule_total_length(capsule) _LM2_CAPSULE_GENERIC(lm2_capsule_total_length, capsule)
#  define lm2_capsule_area(capsule)         _LM2_CAPSULE_GENERIC(lm2_capsule_area, capsule)
#  define lm2_capsule_perimeter(capsule)    _LM2_CAPSULE_GENERIC(lm2_capsule_perimeter, capsule)
#  define lm2_capsule_center(capsule)       _LM2_CAPSULE_GENERIC(lm2_capsule_center, capsule)

// Capsule tests
#  define lm2_capsule_contains_point(capsule, point) \
    _Generic((capsule).start.x,                      \
        double: lm2_capsule_contains_point_f64,      \
        float: lm2_capsule_contains_point_f32)(capsule, point)

#  define lm2_capsules_overlap(a, b)      \
    _Generic((a).start.x,                 \
        double: lm2_capsules_overlap_f64, \
        float: lm2_capsules_overlap_f32)(a, b)

// Capsule transformations
#  define lm2_capsule_translate(capsule, offset) \
    _Generic((capsule).start.x,                  \
        double: lm2_capsule_translate_f64,       \
        float: lm2_capsule_translate_f32)(capsule, offset)

#  define lm2_capsule_scale_radius(capsule, scale) \
    _Generic((capsule).start.x,                    \
        double: lm2_capsule_scale_radius_f64,      \
        float: lm2_capsule_scale_radius_f32)(capsule, scale)

#endif

// #############################################################################
LM2_HEADER_END;
// #############################################################################
