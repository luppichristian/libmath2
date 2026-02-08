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
// Edge Types
// =============================================================================

// Edge structure to represent a 2D line segment
typedef struct lm2_edge_f64 {
  lm2_v2f64 start, end;
} lm2_edge_f64;

typedef struct lm2_edge_f32 {
  lm2_v2f32 start, end;
} lm2_edge_f32;

// Default edge type
typedef lm2_edge_f32 lm2_edge;

// Edge result with existence flag
typedef struct lm2_edge_result_f64 {
  lm2_edge_f64 edge;
  bool exists;
} lm2_edge_result_f64;

typedef struct lm2_edge_result_f32 {
  lm2_edge_f32 edge;
  bool exists;
} lm2_edge_result_f32;

typedef lm2_edge_result_f32 lm2_edge_result;

// =============================================================================
// Construction Helpers
// =============================================================================

// Create an edge from two points
LM2_API lm2_edge_f64 lm2_edge_make_f64(lm2_v2f64 start, lm2_v2f64 end);
LM2_API lm2_edge_f32 lm2_edge_make_f32(lm2_v2f32 start, lm2_v2f32 end);

// Create an edge from coordinates
LM2_API lm2_edge_f64 lm2_edge_make_coords_f64(double x1, double y1, double x2, double y2);
LM2_API lm2_edge_f32 lm2_edge_make_coords_f32(float x1, float y1, float x2, float y2);

// =============================================================================
// Edge Properties
// =============================================================================

// Get the length of an edge
LM2_API double lm2_edge_length_f64(lm2_edge_f64 edge);
LM2_API float lm2_edge_length_f32(lm2_edge_f32 edge);

// Get the squared length of an edge (faster, avoids sqrt)
LM2_API double lm2_edge_length_sq_f64(lm2_edge_f64 edge);
LM2_API float lm2_edge_length_sq_f32(lm2_edge_f32 edge);

// =============================================================================
// Edge Comparison
// =============================================================================

// Check if two points are equal within epsilon
LM2_API bool lm2_points_equal_f64(lm2_v2f64 a, lm2_v2f64 b, double epsilon);
LM2_API bool lm2_points_equal_f32(lm2_v2f32 a, lm2_v2f32 b, float epsilon);

// Check if two edges are the same (regardless of direction)
LM2_API bool lm2_edges_equal_f64(lm2_edge_f64 e1, lm2_edge_f64 e2, double epsilon);
LM2_API bool lm2_edges_equal_f32(lm2_edge_f32 e1, lm2_edge_f32 e2, float epsilon);

// =============================================================================
// Edge Intersection
// =============================================================================

// Check if two line segments intersect
LM2_API bool lm2_edges_intersect_f64(lm2_edge_f64 e1, lm2_edge_f64 e2);
LM2_API bool lm2_edges_intersect_f32(lm2_edge_f32 e1, lm2_edge_f32 e2);

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// C++ operator overloads (must be outside extern "C")
#ifndef LM2_NO_CPP_OPERATORS
#  include "lm2_geometry_operators.h"
_LM2_DEFINE_EDGE_OPERATORS(lm2_edge_f64, lm2_v2f64, double)
_LM2_DEFINE_EDGE_OPERATORS(lm2_edge_f32, lm2_v2f32, float)
#endif
