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

#include <stddef.h>
#include "lm2/lm2_base.h"
#include "lm2/vectors/lm2_vector2.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// Polygon Types
// =============================================================================

// Polygon structure - caller manages the vertices array memory
typedef struct lm2_polygon_f64 {
  lm2_v2f64* vertices;  // Pointer to array of vertices (caller-managed)
  size_t vertex_count;  // Number of vertices
} lm2_polygon_f64;

typedef struct lm2_polygon_f32 {
  lm2_v2f32* vertices;  // Pointer to array of vertices (caller-managed)
  size_t vertex_count;  // Number of vertices
} lm2_polygon_f32;

// Default polygon type
typedef lm2_polygon_f32 lm2_polygon;

// =============================================================================
// Construction Helpers
// =============================================================================

// Create a polygon from an array of vertices (caller manages memory)
LM2_API lm2_polygon_f64 lm2_polygon_make_f64(lm2_v2f64* vertices, size_t vertex_count);
LM2_API lm2_polygon_f32 lm2_polygon_make_f32(lm2_v2f32* vertices, size_t vertex_count);

// Create a regular polygon (caller provides output array with required size)
LM2_API void lm2_polygon_make_regular_f64(lm2_v2f64* out_vertices, size_t num_sides, lm2_v2f64 center, double radius);
LM2_API void lm2_polygon_make_regular_f32(lm2_v2f32* out_vertices, size_t num_sides, lm2_v2f32 center, float radius);

// Create a rectangle polygon (caller provides output array of size 4)
LM2_API void lm2_polygon_make_rect_f64(lm2_v2f64* out_vertices, lm2_v2f64 min, lm2_v2f64 max);
LM2_API void lm2_polygon_make_rect_f32(lm2_v2f32* out_vertices, lm2_v2f32 min, lm2_v2f32 max);

// =============================================================================
// Polygon Properties
// =============================================================================

// Calculate the area of a polygon (signed, positive for CCW, negative for CW)
LM2_API double lm2_polygon_area_f64(lm2_polygon_f64 polygon);
LM2_API float lm2_polygon_area_f32(lm2_polygon_f32 polygon);

// Calculate the perimeter of a polygon
LM2_API double lm2_polygon_perimeter_f64(lm2_polygon_f64 polygon);
LM2_API float lm2_polygon_perimeter_f32(lm2_polygon_f32 polygon);

// Calculate the centroid (geometric center) of a polygon
LM2_API lm2_v2f64 lm2_polygon_centroid_f64(lm2_polygon_f64 polygon);
LM2_API lm2_v2f32 lm2_polygon_centroid_f32(lm2_polygon_f32 polygon);

// Check if polygon vertices are ordered counter-clockwise
LM2_API bool lm2_polygon_is_ccw_f64(lm2_polygon_f64 polygon);
LM2_API bool lm2_polygon_is_ccw_f32(lm2_polygon_f32 polygon);

// =============================================================================
// Polygon Tests
// =============================================================================

// Check if a point is inside a polygon (using ray casting algorithm)
LM2_API bool lm2_polygon_contains_point_f64(lm2_polygon_f64 polygon, lm2_v2f64 point);
LM2_API bool lm2_polygon_contains_point_f32(lm2_polygon_f32 polygon, lm2_v2f32 point);

// Check if a polygon is convex
LM2_API bool lm2_polygon_is_convex_f64(lm2_polygon_f64 polygon);
LM2_API bool lm2_polygon_is_convex_f32(lm2_polygon_f32 polygon);

// Check if a polygon is simple (no self-intersections)
LM2_API bool lm2_polygon_is_simple_f64(lm2_polygon_f64 polygon);
LM2_API bool lm2_polygon_is_simple_f32(lm2_polygon_f32 polygon);

// =============================================================================
// Polygon Transformations
// =============================================================================

// Translate a polygon by an offset (modifies vertices in-place)
LM2_API void lm2_polygon_translate_f64(lm2_polygon_f64 polygon, lm2_v2f64 offset);
LM2_API void lm2_polygon_translate_f32(lm2_polygon_f32 polygon, lm2_v2f32 offset);

// Scale a polygon around a center point (modifies vertices in-place)
LM2_API void lm2_polygon_scale_f64(lm2_polygon_f64 polygon, lm2_v2f64 center, double scale);
LM2_API void lm2_polygon_scale_f32(lm2_polygon_f32 polygon, lm2_v2f32 center, float scale);

// Rotate a polygon around a center point (modifies vertices in-place)
LM2_API void lm2_polygon_rotate_f64(lm2_polygon_f64 polygon, lm2_v2f64 center, double angle_radians);
LM2_API void lm2_polygon_rotate_f32(lm2_polygon_f32 polygon, lm2_v2f32 center, float angle_radians);

// Reverse the winding order of a polygon (modifies vertices in-place)
LM2_API void lm2_polygon_reverse_winding_f64(lm2_polygon_f64 polygon);
LM2_API void lm2_polygon_reverse_winding_f32(lm2_polygon_f32 polygon);

// =============================================================================
// Generic Macros
// =============================================================================

#ifndef LM2_NO_GENERICS
#  ifdef __cplusplus
#    define _LM2_POLYGON_GENERIC(name, ...) \
      _Generic((__VA_ARGS__),               \
          lm2_polygon_f64: name##_f64,      \
          lm2_polygon_f32: name##_f32,      \
          lm2_v2f64*: name##_f64,           \
          lm2_v2f32*: name##_f32)(__VA_ARGS__)
#  else
#    define _LM2_POLYGON_GENERIC(name, ...) \
      _Generic((__VA_ARGS__),               \
          lm2_polygon_f64: name##_f64,      \
          lm2_polygon_f32: name##_f32,      \
          lm2_v2f64*: name##_f64,           \
          lm2_v2f32*: name##_f32)(__VA_ARGS__)
#  endif

// Construction helpers
#  define lm2_polygon_make(vertices, count) \
    _Generic((vertices),                    \
        lm2_v2f64*: lm2_polygon_make_f64,   \
        lm2_v2f32*: lm2_polygon_make_f32)(vertices, count)

#  define lm2_polygon_make_regular(out, num_sides, center, radius) \
    _Generic((out),                                                \
        lm2_v2f64*: lm2_polygon_make_regular_f64,                  \
        lm2_v2f32*: lm2_polygon_make_regular_f32)(out, num_sides, center, radius)

#  define lm2_polygon_make_rect(out, min, max) \
    _Generic((out),                            \
        lm2_v2f64*: lm2_polygon_make_rect_f64, \
        lm2_v2f32*: lm2_polygon_make_rect_f32)(out, min, max)

// Polygon properties
#  define lm2_polygon_area(polygon)       \
    _Generic((polygon).vertices,          \
        lm2_v2f64*: lm2_polygon_area_f64, \
        lm2_v2f32*: lm2_polygon_area_f32)(polygon)

#  define lm2_polygon_perimeter(polygon)       \
    _Generic((polygon).vertices,               \
        lm2_v2f64*: lm2_polygon_perimeter_f64, \
        lm2_v2f32*: lm2_polygon_perimeter_f32)(polygon)

#  define lm2_polygon_centroid(polygon)       \
    _Generic((polygon).vertices,              \
        lm2_v2f64*: lm2_polygon_centroid_f64, \
        lm2_v2f32*: lm2_polygon_centroid_f32)(polygon)

#  define lm2_polygon_is_ccw(polygon)       \
    _Generic((polygon).vertices,            \
        lm2_v2f64*: lm2_polygon_is_ccw_f64, \
        lm2_v2f32*: lm2_polygon_is_ccw_f32)(polygon)

// Polygon tests
#  define lm2_polygon_contains_point(polygon, point) \
    _Generic((polygon).vertices,                     \
        lm2_v2f64*: lm2_polygon_contains_point_f64,  \
        lm2_v2f32*: lm2_polygon_contains_point_f32)(polygon, point)

#  define lm2_polygon_is_convex(polygon)       \
    _Generic((polygon).vertices,               \
        lm2_v2f64*: lm2_polygon_is_convex_f64, \
        lm2_v2f32*: lm2_polygon_is_convex_f32)(polygon)

#  define lm2_polygon_is_simple(polygon)       \
    _Generic((polygon).vertices,               \
        lm2_v2f64*: lm2_polygon_is_simple_f64, \
        lm2_v2f32*: lm2_polygon_is_simple_f32)(polygon)

// Polygon transformations
#  define lm2_polygon_translate(polygon, offset) \
    _Generic((polygon).vertices,                 \
        lm2_v2f64*: lm2_polygon_translate_f64,   \
        lm2_v2f32*: lm2_polygon_translate_f32)(polygon, offset)

#  define lm2_polygon_scale(polygon, center, scale) \
    _Generic((polygon).vertices,                    \
        lm2_v2f64*: lm2_polygon_scale_f64,          \
        lm2_v2f32*: lm2_polygon_scale_f32)(polygon, center, scale)

#  define lm2_polygon_rotate(polygon, center, angle) \
    _Generic((polygon).vertices,                     \
        lm2_v2f64*: lm2_polygon_rotate_f64,          \
        lm2_v2f32*: lm2_polygon_rotate_f32)(polygon, center, angle)

#  define lm2_polygon_reverse_winding(polygon)       \
    _Generic((polygon).vertices,                     \
        lm2_v2f64*: lm2_polygon_reverse_winding_f64, \
        lm2_v2f32*: lm2_polygon_reverse_winding_f32)(polygon)

#endif

// #############################################################################
LM2_HEADER_END;
// #############################################################################
