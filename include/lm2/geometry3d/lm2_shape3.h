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

#include "lm2/geometry3d/lm2_capsule3.h"
#include "lm2/geometry3d/lm2_cuboid.h"
#include "lm2/geometry3d/lm2_edge3.h"
#include "lm2/geometry3d/lm2_sphere.h"
#include "lm2/geometry3d/lm2_triangle3.h"
#include "lm2/lm2_base.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// Shape Type Enumeration
// =============================================================================

typedef enum lm2_shape3_type {
  LM2_SHAPE3_SPHERE,
  LM2_SHAPE3_CAPSULE,
  LM2_SHAPE3_CUBOID,
  LM2_SHAPE3_TRIANGLE,
  LM2_SHAPE3_EDGE,
} lm2_shape3_type;

// =============================================================================
// Shape Structure
// =============================================================================

typedef struct lm2_shape3_f32 {
  lm2_shape3_type type;
  void* data;
} lm2_shape3_f32;

typedef struct lm2_shape3_f64 {
  lm2_shape3_type type;
  void* data;
} lm2_shape3_f64;

// Default shape type
typedef lm2_shape3_f32 lm2_shape3;

// =============================================================================
// Construction Helpers
// =============================================================================

// Create shape from sphere
LM2_API lm2_shape3_f64 lm2_shape3_from_sphere_f64(lm2_sphere_f64* sphere);
LM2_API lm2_shape3_f32 lm2_shape3_from_sphere_f32(lm2_sphere_f32* sphere);

// Create shape from capsule
LM2_API lm2_shape3_f64 lm2_shape3_from_capsule_f64(lm2_capsule3_f64* capsule);
LM2_API lm2_shape3_f32 lm2_shape3_from_capsule_f32(lm2_capsule3_f32* capsule);

// Create shape from cuboid
LM2_API lm2_shape3_f64 lm2_shape3_from_cuboid_f64(lm2_cuboid_f64* cuboid);
LM2_API lm2_shape3_f32 lm2_shape3_from_cuboid_f32(lm2_cuboid_f32* cuboid);

// Create shape from triangle
LM2_API lm2_shape3_f64 lm2_shape3_from_triangle_f64(lm2_triangle3_f64* triangle);
LM2_API lm2_shape3_f32 lm2_shape3_from_triangle_f32(lm2_triangle3_f32* triangle);

// Create shape from edge
LM2_API lm2_shape3_f64 lm2_shape3_from_edge_f64(lm2_edge3_f64* edge);
LM2_API lm2_shape3_f32 lm2_shape3_from_edge_f32(lm2_edge3_f32* edge);

// =============================================================================
// Extraction Helpers
// =============================================================================

// Extract sphere from shape (returns NULL if not a sphere)
LM2_API lm2_sphere_f64* lm2_shape3_as_sphere_f64(lm2_shape3_f64* shape);
LM2_API lm2_sphere_f32* lm2_shape3_as_sphere_f32(lm2_shape3_f32* shape);

// Extract capsule from shape (returns NULL if not a capsule)
LM2_API lm2_capsule3_f64* lm2_shape3_as_capsule_f64(lm2_shape3_f64* shape);
LM2_API lm2_capsule3_f32* lm2_shape3_as_capsule_f32(lm2_shape3_f32* shape);

// Extract cuboid from shape (returns NULL if not a cuboid)
LM2_API lm2_cuboid_f64* lm2_shape3_as_cuboid_f64(lm2_shape3_f64* shape);
LM2_API lm2_cuboid_f32* lm2_shape3_as_cuboid_f32(lm2_shape3_f32* shape);

// Extract triangle from shape (returns NULL if not a triangle)
LM2_API lm2_triangle3_f64* lm2_shape3_as_triangle_f64(lm2_shape3_f64* shape);
LM2_API lm2_triangle3_f32* lm2_shape3_as_triangle_f32(lm2_shape3_f32* shape);

// Extract edge from shape (returns NULL if not an edge)
LM2_API lm2_edge3_f64* lm2_shape3_as_edge_f64(lm2_shape3_f64* shape);
LM2_API lm2_edge3_f32* lm2_shape3_as_edge_f32(lm2_shape3_f32* shape);

// =============================================================================
// Type Query Helpers
// =============================================================================

// Check if shape is of specific type
LM2_API bool lm2_shape3_is_type_f64(const lm2_shape3_f64* shape, lm2_shape3_type type);
LM2_API bool lm2_shape3_is_type_f32(const lm2_shape3_f32* shape, lm2_shape3_type type);

// Get shape type
LM2_API lm2_shape3_type lm2_shape3_get_type_f64(const lm2_shape3_f64* shape);
LM2_API lm2_shape3_type lm2_shape3_get_type_f32(const lm2_shape3_f32* shape);

// #############################################################################
LM2_HEADER_END;
// #############################################################################
