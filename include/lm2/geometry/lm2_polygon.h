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
#include "lm2/geometry/lm2_triangle.h"
#include "lm2/lm2_base.h"
#include "lm2/ranges/lm2_range2.h"
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

// Create a triangle polygon (caller provides output array of size 3)
LM2_API void lm2_polygon_make_triangle_f64(lm2_v2f64* out_vertices, lm2_v2f64 position, lm2_v2f64 tip, double base_width);
LM2_API void lm2_polygon_make_triangle_f32(lm2_v2f32* out_vertices, lm2_v2f32 position, lm2_v2f32 tip, float base_width);

// Create a polygon from a triangle (caller provides output array of size 3)
LM2_API void lm2_polygon_from_triangle_f64(lm2_v2f64* out_vertices, const lm2_triangle_f64 triangle);
LM2_API void lm2_polygon_from_triangle_f32(lm2_v2f32* out_vertices, const lm2_triangle_f32 triangle);

// =============================================================================
// Polygon Properties
// =============================================================================

// Validate a polygon (checks for null pointer and minimum vertex count)
LM2_API bool lm2_polygon_validate_f64(lm2_polygon_f64 polygon);
LM2_API bool lm2_polygon_validate_f32(lm2_polygon_f32 polygon);

// Calculate the signed area of a polygon (positive for CCW, negative for CW)
LM2_API double lm2_polygon_signed_area_f64(lm2_polygon_f64 polygon);
LM2_API float lm2_polygon_signed_area_f32(lm2_polygon_f32 polygon);

// Calculate the area of a polygon (absolute value, always positive)
LM2_API double lm2_polygon_area_f64(lm2_polygon_f64 polygon);
LM2_API float lm2_polygon_area_f32(lm2_polygon_f32 polygon);

// Get the winding order of a polygon
LM2_API lm2_winding_order lm2_polygon_winding_order_f64(lm2_polygon_f64 polygon);
LM2_API lm2_winding_order lm2_polygon_winding_order_f32(lm2_polygon_f32 polygon);

// Calculate the perimeter of a polygon
LM2_API double lm2_polygon_perimeter_f64(lm2_polygon_f64 polygon);
LM2_API float lm2_polygon_perimeter_f32(lm2_polygon_f32 polygon);

// Calculate the centroid (geometric center) of a polygon
LM2_API lm2_v2f64 lm2_polygon_centroid_f64(lm2_polygon_f64 polygon);
LM2_API lm2_v2f32 lm2_polygon_centroid_f32(lm2_polygon_f32 polygon);

// Check if polygon vertices are ordered counter-clockwise
LM2_API bool lm2_polygon_is_ccw_f64(lm2_polygon_f64 polygon);
LM2_API bool lm2_polygon_is_ccw_f32(lm2_polygon_f32 polygon);

// Calculate the geometric center (alias for centroid)
LM2_API lm2_v2f64 lm2_polygon_center_f64(lm2_polygon_f64 polygon);
LM2_API lm2_v2f32 lm2_polygon_center_f32(lm2_polygon_f32 polygon);

// Calculate the axis-aligned bounding box of a polygon
LM2_API lm2_r2f64 lm2_polygon_bounds_f64(lm2_polygon_f64 polygon);
LM2_API lm2_r2f32 lm2_polygon_bounds_f32(lm2_polygon_f32 polygon);

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

// Check if a polygon is a triangle (has exactly 3 vertices)
LM2_API bool lm2_polygon_is_triangle_f64(lm2_polygon_f64 polygon);
LM2_API bool lm2_polygon_is_triangle_f32(lm2_polygon_f32 polygon);

// Check if a polygon is a quad (has exactly 4 vertices)
LM2_API bool lm2_polygon_is_quad_f64(lm2_polygon_f64 polygon);
LM2_API bool lm2_polygon_is_quad_f32(lm2_polygon_f32 polygon);

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

// Insert a vertex at a specific index (caller manages vertex array, must have space)
LM2_API void lm2_polygon_insert_vertex_f64(lm2_v2f64* vertices, size_t* vertex_count, size_t index, lm2_v2f64 vertex);
LM2_API void lm2_polygon_insert_vertex_f32(lm2_v2f32* vertices, size_t* vertex_count, size_t index, lm2_v2f32 vertex);

// Remove a vertex at a specific index (shifts remaining vertices)
LM2_API void lm2_polygon_remove_vertex_f64(lm2_v2f64* vertices, size_t* vertex_count, size_t index);
LM2_API void lm2_polygon_remove_vertex_f32(lm2_v2f32* vertices, size_t* vertex_count, size_t index);

// Move polygon so its centroid is at the specified position
LM2_API void lm2_polygon_place_at_center_f64(lm2_polygon_f64 polygon, lm2_v2f64 position);
LM2_API void lm2_polygon_place_at_center_f32(lm2_polygon_f32 polygon, lm2_v2f32 position);

// =============================================================================
// Polygon Triangulation
// =============================================================================

// Calculate the maximum number of triangles for a polygon (vertex_count - 2)
LM2_API size_t lm2_polygon_max_triangle_count(size_t vertex_count);

// Triangulate a polygon using ear clipping algorithm
// out_indices: caller-provided array to store triangle indices (size = max_triangle_count * 3)
// Returns: actual number of triangles generated
LM2_API size_t lm2_polygon_triangulate_ear_clipping_f64(lm2_polygon_f64 polygon, size_t* out_indices);
LM2_API size_t lm2_polygon_triangulate_ear_clipping_f32(lm2_polygon_f32 polygon, size_t* out_indices);

// =============================================================================
// Polygon Splitting
// =============================================================================

// Split polygon into subpolygons with max vertices each
// out_polygons: caller-provided array of polygon structures (size = estimated split count)
// out_vertices_buffer: caller-provided vertex buffer for all subpolygons
// max_vertices: maximum vertices per subpolygon
// Returns: actual number of subpolygons generated
LM2_API size_t lm2_polygon_split_by_max_vertices_f64(lm2_polygon_f64 polygon, lm2_polygon_f64* out_polygons, lm2_v2f64* out_vertices_buffer, size_t max_vertices);
LM2_API size_t lm2_polygon_split_by_max_vertices_f32(lm2_polygon_f32 polygon, lm2_polygon_f32* out_polygons, lm2_v2f32* out_vertices_buffer, size_t max_vertices);

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// C++ operator overloads (must be outside extern "C")
#ifndef LM2_NO_CPP_OPERATORS
#  include "lm2_geometry_operators.h"
_LM2_DEFINE_POLYGON_OPERATORS(lm2_polygon_f64, lm2_v2f64, double)
_LM2_DEFINE_POLYGON_OPERATORS(lm2_polygon_f32, lm2_v2f32, float)
#endif
