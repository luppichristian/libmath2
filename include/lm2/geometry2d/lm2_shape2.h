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

#include "lm2/geometry2d/lm2_capsule2.h"
#include "lm2/geometry2d/lm2_circle.h"
#include "lm2/geometry2d/lm2_edge2.h"
#include "lm2/geometry2d/lm2_polygon.h"
#include "lm2/geometry2d/lm2_aabb2.h"
#include "lm2/geometry2d/lm2_triangle2.h"
#include "lm2/lm2_base.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// Shape Type Enumeration
// =============================================================================

typedef enum lm2_shape2_type {
  LM2_SHAPE2_CIRCLE,
  LM2_SHAPE2_CAPSULE,
  LM2_SHAPE2_AABB2,
  LM2_SHAPE2_TRIANGLE,
  LM2_SHAPE2_POLYGON,
  LM2_SHAPE2_EDGE,
} lm2_shape2_type;

// =============================================================================
// Shape Structure
// =============================================================================

typedef struct lm2_shape2_f32 {
  lm2_shape2_type type;
  void* data;
} lm2_shape2_f32;

typedef struct lm2_shape2_f64 {
  lm2_shape2_type type;
  void* data;
} lm2_shape2_f64;

// Default shape type
typedef lm2_shape2_f32 lm2_shape2;

// =============================================================================
// Construction Helpers
// =============================================================================

// Create shape from circle
LM2_API lm2_shape2_f64 lm2_shape2_from_circle_f64(lm2_circle_f64* circle);
LM2_API lm2_shape2_f32 lm2_shape2_from_circle_f32(lm2_circle_f32* circle);

// Create shape from capsule
LM2_API lm2_shape2_f64 lm2_shape2_from_capsule_f64(lm2_capsule2_f64* capsule);
LM2_API lm2_shape2_f32 lm2_shape2_from_capsule_f32(lm2_capsule2_f32* capsule);

// Create shape from aabb2
LM2_API lm2_shape2_f64 lm2_shape2_from_aabb2_f64(lm2_aabb2_f64* aabb2);
LM2_API lm2_shape2_f32 lm2_shape2_from_aabb2_f32(lm2_aabb2_f32* aabb2);

// Create shape from triangle
LM2_API lm2_shape2_f64 lm2_shape2_from_triangle_f64(lm2_triangle2_f64* triangle);
LM2_API lm2_shape2_f32 lm2_shape2_from_triangle_f32(lm2_triangle2_f32* triangle);

// Create shape from polygon
LM2_API lm2_shape2_f64 lm2_shape2_from_polygon_f64(lm2_polygon_f64* polygon);
LM2_API lm2_shape2_f32 lm2_shape2_from_polygon_f32(lm2_polygon_f32* polygon);

// Create shape from edge
LM2_API lm2_shape2_f64 lm2_shape2_from_edge_f64(lm2_edge2_f64* edge);
LM2_API lm2_shape2_f32 lm2_shape2_from_edge_f32(lm2_edge2_f32* edge);

// =============================================================================
// Extraction Helpers
// =============================================================================

// Extract circle from shape (returns NULL if not a circle)
LM2_API lm2_circle_f64* lm2_shape2_as_circle_f64(lm2_shape2_f64* shape);
LM2_API lm2_circle_f32* lm2_shape2_as_circle_f32(lm2_shape2_f32* shape);

// Extract capsule from shape (returns NULL if not a capsule)
LM2_API lm2_capsule2_f64* lm2_shape2_as_capsule_f64(lm2_shape2_f64* shape);
LM2_API lm2_capsule2_f32* lm2_shape2_as_capsule_f32(lm2_shape2_f32* shape);

// Extract aabb2 from shape (returns NULL if not an aabb2)
LM2_API lm2_aabb2_f64* lm2_shape2_as_aabb2_f64(lm2_shape2_f64* shape);
LM2_API lm2_aabb2_f32* lm2_shape2_as_aabb2_f32(lm2_shape2_f32* shape);

// Extract triangle from shape (returns NULL if not a triangle)
LM2_API lm2_triangle2_f64* lm2_shape2_as_triangle_f64(lm2_shape2_f64* shape);
LM2_API lm2_triangle2_f32* lm2_shape2_as_triangle_f32(lm2_shape2_f32* shape);

// Extract polygon from shape (returns NULL if not a polygon)
LM2_API lm2_polygon_f64* lm2_shape2_as_polygon_f64(lm2_shape2_f64* shape);
LM2_API lm2_polygon_f32* lm2_shape2_as_polygon_f32(lm2_shape2_f32* shape);

// Extract edge from shape (returns NULL if not an edge)
LM2_API lm2_edge2_f64* lm2_shape2_as_edge_f64(lm2_shape2_f64* shape);
LM2_API lm2_edge2_f32* lm2_shape2_as_edge_f32(lm2_shape2_f32* shape);

// =============================================================================
// Type Query Helpers
// =============================================================================

// Check if shape is of specific type
LM2_API bool lm2_shape2_is_type_f64(const lm2_shape2_f64* shape, lm2_shape2_type type);
LM2_API bool lm2_shape2_is_type_f32(const lm2_shape2_f32* shape, lm2_shape2_type type);

// Get shape type
LM2_API lm2_shape2_type lm2_shape2_get_type_f64(const lm2_shape2_f64* shape);
LM2_API lm2_shape2_type lm2_shape2_get_type_f32(const lm2_shape2_f32* shape);

// #############################################################################
LM2_HEADER_END;
// #############################################################################
