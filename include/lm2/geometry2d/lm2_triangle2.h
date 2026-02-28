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
#include "lm2_edge2.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// Triangle Types
// =============================================================================

// 2D Triangle defined as an array of 3 vertices
typedef lm2_v2_f64 lm2_triangle2_f64[3];
typedef lm2_v2_f32 lm2_triangle2_f32[3];

// =============================================================================
// Triangle Type Enums
// =============================================================================

typedef enum lm2_triangle2_type {
  LM2_TRIANGLE2_SCALENE,      // All sides have different lengths
  LM2_TRIANGLE2_ISOSCELES,    // Two sides have equal length
  LM2_TRIANGLE2_EQUILATERAL,  // All sides have equal length
  LM2_TRIANGLE2_RIGHT,        // Has a 90-degree angle
  LM2_TRIANGLE2_DEGENERATE    // Collinear points (area = 0)
} lm2_triangle2_type;

typedef enum lm2_winding_order {
  LM2_WINDING_NONE,             // Degenerate triangle
  LM2_WINDING_CLOCKWISE,        // CW winding
  LM2_WINDING_COUNTERCLOCKWISE  // CCW winding
} lm2_winding_order;

// =============================================================================
// Construction Helpers
// =============================================================================

// Create a triangle from three 2D points
LM2_API void lm2_triangle2_make_f64(lm2_triangle2_f64 tri, lm2_v2_f64 a, lm2_v2_f64 b, lm2_v2_f64 c);
LM2_API void lm2_triangle2_make_f32(lm2_triangle2_f32 tri, lm2_v2_f32 a, lm2_v2_f32 b, lm2_v2_f32 c);

// Create a triangle from coordinate values
LM2_API void lm2_triangle2_make_coords_f64(lm2_triangle2_f64 tri, double ax, double ay, double bx, double by, double cx, double cy);
LM2_API void lm2_triangle2_make_coords_f32(lm2_triangle2_f32 tri, float ax, float ay, float bx, float by, float cx, float cy);

// =============================================================================
// Triangle Properties
// =============================================================================

// Calculate the signed area of a triangle (positive for CCW, negative for CW)
LM2_API double lm2_triangle2_signed_area_f64(const lm2_triangle2_f64 tri);
LM2_API float lm2_triangle2_signed_area_f32(const lm2_triangle2_f32 tri);

// Calculate the area of a triangle (always positive)
LM2_API double lm2_triangle2_area_f64(const lm2_triangle2_f64 tri);
LM2_API float lm2_triangle2_area_f32(const lm2_triangle2_f32 tri);

// Calculate the perimeter of a triangle
LM2_API double lm2_triangle2_perimeter_f64(const lm2_triangle2_f64 tri);
LM2_API float lm2_triangle2_perimeter_f32(const lm2_triangle2_f32 tri);

// Get winding order
LM2_API lm2_winding_order lm2_triangle2_winding_f64(const lm2_triangle2_f64 tri);
LM2_API lm2_winding_order lm2_triangle2_winding_f32(const lm2_triangle2_f32 tri);

// =============================================================================
// Triangle Classification
// =============================================================================

// Check if triangle is degenerate (collinear points)
LM2_API bool lm2_triangle2_is_degenerate_f64(const lm2_triangle2_f64 tri, double epsilon);
LM2_API bool lm2_triangle2_is_degenerate_f32(const lm2_triangle2_f32 tri, float epsilon);

// Check if triangle is a right triangle
LM2_API bool lm2_triangle2_is_right_f64(const lm2_triangle2_f64 tri, double epsilon);
LM2_API bool lm2_triangle2_is_right_f32(const lm2_triangle2_f32 tri, float epsilon);

// Check if triangle is isosceles (two equal sides)
LM2_API bool lm2_triangle2_is_isosceles_f64(const lm2_triangle2_f64 tri, double epsilon);
LM2_API bool lm2_triangle2_is_isosceles_f32(const lm2_triangle2_f32 tri, float epsilon);

// Check if triangle is equilateral (all equal sides)
LM2_API bool lm2_triangle2_is_equilateral_f64(const lm2_triangle2_f64 tri, double epsilon);
LM2_API bool lm2_triangle2_is_equilateral_f32(const lm2_triangle2_f32 tri, float epsilon);

// Check if triangle is scalene (all different sides)
LM2_API bool lm2_triangle2_is_scalene_f64(const lm2_triangle2_f64 tri, double epsilon);
LM2_API bool lm2_triangle2_is_scalene_f32(const lm2_triangle2_f32 tri, float epsilon);

// Get the primary type of the triangle
LM2_API lm2_triangle2_type lm2_triangle2_classify_f64(const lm2_triangle2_f64 tri, double epsilon);
LM2_API lm2_triangle2_type lm2_triangle2_classify_f32(const lm2_triangle2_f32 tri, float epsilon);

// =============================================================================
// Triangle-Point Intersection
// =============================================================================

// Check if a point is inside a triangle
LM2_API bool lm2_triangle2_contains_point_f64(const lm2_triangle2_f64 tri, lm2_v2_f64 point);
LM2_API bool lm2_triangle2_contains_point_f32(const lm2_triangle2_f32 tri, lm2_v2_f32 point);

// =============================================================================
// Triangle-Triangle Intersection
// =============================================================================

// Check if two triangles overlap
LM2_API bool lm2_triangle2_overlaps_f64(const lm2_triangle2_f64 t1, const lm2_triangle2_f64 t2);
LM2_API bool lm2_triangle2_overlaps_f32(const lm2_triangle2_f32 t1, const lm2_triangle2_f32 t2);

// =============================================================================
// Triangle-Edge Operations
// =============================================================================

// Check if two triangles share an edge and return it
LM2_API lm2_edge2_result_f64 lm2_triangle2_shared_edge_f64(const lm2_triangle2_f64 t1, const lm2_triangle2_f64 t2, double epsilon);
LM2_API lm2_edge2_result_f32 lm2_triangle2_shared_edge_f32(const lm2_triangle2_f32 t1, const lm2_triangle2_f32 t2, float epsilon);

// #############################################################################
LM2_HEADER_END;
// #############################################################################