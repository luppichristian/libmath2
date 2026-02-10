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

#include "lm2/geometry3d/lm2_edge3.h"
#include "lm2/lm2_base.h"
#include "lm2/vectors/lm2_vector3.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// Triangle Types
// =============================================================================

// 3D Triangle defined as an array of 3 vertices
typedef lm2_v3_f64 lm2_triangle3_f64[3];
typedef lm2_v3_f32 lm2_triangle3_f32[3];

// Default triangle type
typedef lm2_triangle3_f32 lm2_triangle3;

// =============================================================================
// Triangle Type Enums
// =============================================================================

typedef enum lm2_triangle3_type {
  LM2_TRIANGLE3_SCALENE,      // All sides have different lengths
  LM2_TRIANGLE3_ISOSCELES,    // Two sides have equal length
  LM2_TRIANGLE3_EQUILATERAL,  // All sides have equal length
  LM2_TRIANGLE3_RIGHT,        // Has a 90-degree angle
  LM2_TRIANGLE3_DEGENERATE    // Collinear points (area = 0)
} lm2_triangle3_type;

// =============================================================================
// Construction Helpers
// =============================================================================

// Create a triangle from three 3D points
LM2_API void lm2_triangle3_make_f64(lm2_triangle3_f64 tri, lm2_v3_f64 a, lm2_v3_f64 b, lm2_v3_f64 c);
LM2_API void lm2_triangle3_make_f32(lm2_triangle3_f32 tri, lm2_v3_f32 a, lm2_v3_f32 b, lm2_v3_f32 c);

// Create a triangle from coordinate values
LM2_API void lm2_triangle3_make_coords_f64(lm2_triangle3_f64 tri, double ax, double ay, double az, double bx, double by, double bz, double cx, double cy, double cz);
LM2_API void lm2_triangle3_make_coords_f32(lm2_triangle3_f32 tri, float ax, float ay, float az, float bx, float by, float bz, float cx, float cy, float cz);

// =============================================================================
// Triangle Properties
// =============================================================================

// Calculate the area of a triangle (using cross product magnitude)
LM2_API double lm2_triangle3_area_f64(const lm2_triangle3_f64 tri);
LM2_API float lm2_triangle3_area_f32(const lm2_triangle3_f32 tri);

// Calculate the perimeter of a triangle
LM2_API double lm2_triangle3_perimeter_f64(const lm2_triangle3_f64 tri);
LM2_API float lm2_triangle3_perimeter_f32(const lm2_triangle3_f32 tri);

// Get the normal vector of the triangle (normalized)
LM2_API lm2_v3_f64 lm2_triangle3_normal_f64(const lm2_triangle3_f64 tri);
LM2_API lm2_v3_f32 lm2_triangle3_normal_f32(const lm2_triangle3_f32 tri);

// Get the center (centroid) of the triangle
LM2_API lm2_v3_f64 lm2_triangle3_centroid_f64(const lm2_triangle3_f64 tri);
LM2_API lm2_v3_f32 lm2_triangle3_centroid_f32(const lm2_triangle3_f32 tri);

// =============================================================================
// Triangle Classification
// =============================================================================

// Check if triangle is degenerate (collinear points)
LM2_API bool lm2_triangle3_is_degenerate_f64(const lm2_triangle3_f64 tri, double epsilon);
LM2_API bool lm2_triangle3_is_degenerate_f32(const lm2_triangle3_f32 tri, float epsilon);

// Check if triangle is a right triangle
LM2_API bool lm2_triangle3_is_right_f64(const lm2_triangle3_f64 tri, double epsilon);
LM2_API bool lm2_triangle3_is_right_f32(const lm2_triangle3_f32 tri, float epsilon);

// Check if triangle is isosceles (two equal sides)
LM2_API bool lm2_triangle3_is_isosceles_f64(const lm2_triangle3_f64 tri, double epsilon);
LM2_API bool lm2_triangle3_is_isosceles_f32(const lm2_triangle3_f32 tri, float epsilon);

// Check if triangle is equilateral (all equal sides)
LM2_API bool lm2_triangle3_is_equilateral_f64(const lm2_triangle3_f64 tri, double epsilon);
LM2_API bool lm2_triangle3_is_equilateral_f32(const lm2_triangle3_f32 tri, float epsilon);

// Check if triangle is scalene (all different sides)
LM2_API bool lm2_triangle3_is_scalene_f64(const lm2_triangle3_f64 tri, double epsilon);
LM2_API bool lm2_triangle3_is_scalene_f32(const lm2_triangle3_f32 tri, float epsilon);

// Get the primary type of the triangle
LM2_API lm2_triangle3_type lm2_triangle3_classify_f64(const lm2_triangle3_f64 tri, double epsilon);
LM2_API lm2_triangle3_type lm2_triangle3_classify_f32(const lm2_triangle3_f32 tri, float epsilon);

// =============================================================================
// Triangle-Point Intersection
// =============================================================================

// Check if a point is inside a triangle (point must be coplanar with triangle)
LM2_API bool lm2_triangle3_contains_point_f64(const lm2_triangle3_f64 tri, lm2_v3_f64 point, double epsilon);
LM2_API bool lm2_triangle3_contains_point_f32(const lm2_triangle3_f32 tri, lm2_v3_f32 point, float epsilon);

// =============================================================================
// Triangle-Triangle Intersection
// =============================================================================

// Check if two triangles overlap
LM2_API bool lm2_triangle3_overlaps_f64(const lm2_triangle3_f64 t1, const lm2_triangle3_f64 t2, double epsilon);
LM2_API bool lm2_triangle3_overlaps_f32(const lm2_triangle3_f32 t1, const lm2_triangle3_f32 t2, float epsilon);

// =============================================================================
// Triangle-Edge Operations
// =============================================================================

// Check if two triangles share an edge and return it
LM2_API lm2_edge3_result_f64 lm2_triangle3_shared_edge_f64(const lm2_triangle3_f64 t1, const lm2_triangle3_f64 t2, double epsilon);
LM2_API lm2_edge3_result_f32 lm2_triangle3_shared_edge_f32(const lm2_triangle3_f32 t1, const lm2_triangle3_f32 t2, float epsilon);

// #############################################################################
LM2_HEADER_END;
// #############################################################################