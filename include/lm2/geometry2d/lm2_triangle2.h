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

// Get winding order; absolute signed area below the type's machine epsilon
// is reported as LM2_WINDING_NONE.
LM2_API lm2_winding_order lm2_triangle2_winding_f64(const lm2_triangle2_f64 tri);
LM2_API lm2_winding_order lm2_triangle2_winding_f32(const lm2_triangle2_f32 tri);

// =============================================================================
// Triangle Classification
// =============================================================================

// Degenerate if absolute area is strictly less than epsilon. A zero epsilon
// does not classify even a zero-area triangle as degenerate.
LM2_API bool lm2_triangle2_is_degenerate_f64(const lm2_triangle2_f64 tri, double epsilon);
LM2_API bool lm2_triangle2_is_degenerate_f32(const lm2_triangle2_f32 tri, float epsilon);

// Check the Pythagorean identity with a strict absolute epsilon on squared
// side lengths. This test does not separately reject degenerate triangles.
LM2_API bool lm2_triangle2_is_right_f64(const lm2_triangle2_f64 tri, double epsilon);
LM2_API bool lm2_triangle2_is_right_f32(const lm2_triangle2_f32 tri, float epsilon);

// Compare side lengths with a strict absolute epsilon; equilateral triangles
// also satisfy this test. A zero epsilon does not match equal lengths.
LM2_API bool lm2_triangle2_is_isosceles_f64(const lm2_triangle2_f64 tri, double epsilon);
LM2_API bool lm2_triangle2_is_isosceles_f32(const lm2_triangle2_f32 tri, float epsilon);

// Compare adjacent side lengths with a strict absolute epsilon.
LM2_API bool lm2_triangle2_is_equilateral_f64(const lm2_triangle2_f64 tri, double epsilon);
LM2_API bool lm2_triangle2_is_equilateral_f32(const lm2_triangle2_f32 tri, float epsilon);

// True when each pair of side lengths differs by at least epsilon.
LM2_API bool lm2_triangle2_is_scalene_f64(const lm2_triangle2_f64 tri, double epsilon);
LM2_API bool lm2_triangle2_is_scalene_f32(const lm2_triangle2_f32 tri, float epsilon);

// Classify in priority order: degenerate, right, equilateral, isosceles,
// then scalene. The same epsilon is used by each test, despite different units.
LM2_API lm2_triangle2_type lm2_triangle2_classify_f64(const lm2_triangle2_f64 tri, double epsilon);
LM2_API lm2_triangle2_type lm2_triangle2_classify_f32(const lm2_triangle2_f32 tri, float epsilon);

// =============================================================================
// Triangle-Point Intersection
// =============================================================================

// Check point containment for either winding, including edges. Use a
// nondegenerate triangle: the sign test treats any point as inside when all
// vertices coincide, and points on the supporting line as inside when collinear.
LM2_API bool lm2_triangle2_contains_point_f64(const lm2_triangle2_f64 tri, lm2_v2_f64 point);
LM2_API bool lm2_triangle2_contains_point_f32(const lm2_triangle2_f32 tri, lm2_v2_f32 point);

// =============================================================================
// Triangle-Triangle Intersection
// =============================================================================

// Test vertex containment and closed edge intersections for either winding;
// touching counts. Use nondegenerate triangles: the containment test can make
// a degenerate triangle report overlap with a distant, disjoint triangle.
LM2_API bool lm2_triangle2_overlaps_f64(const lm2_triangle2_f64 t1, const lm2_triangle2_f64 t2);
LM2_API bool lm2_triangle2_overlaps_f32(const lm2_triangle2_f32 t1, const lm2_triangle2_f32 t2);

// =============================================================================
// Triangle-Edge Operations
// =============================================================================

// Return the first matching edge from t1, ignoring edge direction. Each
// endpoint coordinate must differ by strictly less than epsilon. When exists
// is false, the edge field is unspecified.
LM2_API lm2_edge2_result_f64 lm2_triangle2_shared_edge_f64(const lm2_triangle2_f64 t1, const lm2_triangle2_f64 t2, double epsilon);
LM2_API lm2_edge2_result_f32 lm2_triangle2_shared_edge_f32(const lm2_triangle2_f32 t1, const lm2_triangle2_f32 t2, float epsilon);

// #############################################################################
LM2_HEADER_END;
// #############################################################################

#ifndef LM2_NO_IMPLEMENTATION
#  include "lm2_triangle2_impl.h"
#endif