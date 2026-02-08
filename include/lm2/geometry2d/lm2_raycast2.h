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
#include "lm2/ranges/lm2_range2.h"
#include "lm2/vectors/lm2_vector2.h"
#include "lm2_capsule2.h"
#include "lm2_circle.h"
#include "lm2_plane2.h"
#include "lm2_polygon.h"
#include "lm2_triangle2.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// Ray Types (2D)
// =============================================================================

// 2D Ray structure
// IMPORTANT: direction should be normalized, t specifies the distance along direction
typedef struct lm2_ray2_f64 {
  lm2_v2f64 origin;     // Ray origin position
  lm2_v2f64 direction;  // Ray direction (should be normalized)
  double t_max;         // Maximum distance along ray
} lm2_ray2_f64;

typedef struct lm2_ray2_f32 {
  lm2_v2f32 origin;     // Ray origin position
  lm2_v2f32 direction;  // Ray direction (should be normalized)
  float t_max;          // Maximum distance along ray
} lm2_ray2_f32;

// Default 2D ray type
typedef lm2_ray2_f32 lm2_ray2;

// =============================================================================
// Ray Hit Result Types (2D)
// =============================================================================

// 2D Ray hit result
typedef struct lm2_rayhit2_f64 {
  bool hit;          // Whether the ray hit something
  double t;          // Distance along ray where hit occurred
  lm2_v2f64 point;   // Hit point in world space
  lm2_v2f64 normal;  // Surface normal at hit point (unit length)
} lm2_rayhit2_f64;

typedef struct lm2_rayhit2_f32 {
  bool hit;          // Whether the ray hit something
  float t;           // Distance along ray where hit occurred
  lm2_v2f32 point;   // Hit point in world space
  lm2_v2f32 normal;  // Surface normal at hit point (unit length)
} lm2_rayhit2_f32;

// Default 2D ray hit type
typedef lm2_rayhit2_f32 lm2_rayhit2;

// =============================================================================
// 2D Ray Construction
// =============================================================================

// Create a 2D ray from origin, direction, and max distance
LM2_API lm2_ray2_f64 lm2_ray2_make_f64(lm2_v2f64 origin, lm2_v2f64 direction, double t_max);
LM2_API lm2_ray2_f32 lm2_ray2_make_f32(lm2_v2f32 origin, lm2_v2f32 direction, float t_max);

// Create a 2D ray from two points
LM2_API lm2_ray2_f64 lm2_ray2_from_points_f64(lm2_v2f64 start, lm2_v2f64 end);
LM2_API lm2_ray2_f32 lm2_ray2_from_points_f32(lm2_v2f32 start, lm2_v2f32 end);

// Get point along ray at distance t
LM2_API lm2_v2f64 lm2_ray2_point_at_f64(lm2_ray2_f64 ray, double t);
LM2_API lm2_v2f32 lm2_ray2_point_at_f32(lm2_ray2_f32 ray, float t);

// =============================================================================
// 2D Ray vs Primitive Tests
// =============================================================================

// Ray vs Circle
LM2_API lm2_rayhit2_f64 lm2_raycast_circle_f64(lm2_ray2_f64 ray, lm2_circle_f64 circle);
LM2_API lm2_rayhit2_f32 lm2_raycast_circle_f32(lm2_ray2_f32 ray, lm2_circle_f32 circle);

// Ray vs AABB (range2)
LM2_API lm2_rayhit2_f64 lm2_raycast_aabb_f64(lm2_ray2_f64 ray, lm2_r2f64 aabb);
LM2_API lm2_rayhit2_f32 lm2_raycast_aabb_f32(lm2_ray2_f32 ray, lm2_r2f32 aabb);

// Ray vs Capsule
LM2_API lm2_rayhit2_f64 lm2_raycast_capsule_f64(lm2_ray2_f64 ray, lm2_capsule2_f64 capsule);
LM2_API lm2_rayhit2_f32 lm2_raycast_capsule_f32(lm2_ray2_f32 ray, lm2_capsule2_f32 capsule);

// Ray vs Polygon
LM2_API lm2_rayhit2_f64 lm2_raycast_polygon_f64(lm2_ray2_f64 ray, lm2_polygon_f64 polygon);
LM2_API lm2_rayhit2_f32 lm2_raycast_polygon_f32(lm2_ray2_f32 ray, lm2_polygon_f32 polygon);

// Ray vs Line Segment (edge)
LM2_API lm2_rayhit2_f64 lm2_raycast_segment_f64(lm2_ray2_f64 ray, lm2_v2f64 segment_start, lm2_v2f64 segment_end);
LM2_API lm2_rayhit2_f32 lm2_raycast_segment_f32(lm2_ray2_f32 ray, lm2_v2f32 segment_start, lm2_v2f32 segment_end);

// Ray vs Triangle
LM2_API lm2_rayhit2_f64 lm2_raycast_triangle_f64(lm2_ray2_f64 ray, const lm2_triangle2_f64 tri);
LM2_API lm2_rayhit2_f32 lm2_raycast_triangle_f32(lm2_ray2_f32 ray, const lm2_triangle2_f32 tri);

// Ray vs Plane (infinite line in 2D)
LM2_API lm2_rayhit2_f64 lm2_raycast_plane_f64(lm2_ray2_f64 ray, lm2_plane2_f64 plane);
LM2_API lm2_rayhit2_f32 lm2_raycast_plane_f32(lm2_ray2_f32 ray, lm2_plane2_f32 plane);

// =============================================================================
// Epsilon/Tolerance Constants
// =============================================================================

// Default epsilon for 2D raycast operations
#define LM2_RAYCAST2_EPSILON_F64 1e-9
#define LM2_RAYCAST2_EPSILON_F32 1e-6f

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// C++ operator overloads (must be outside extern "C")
#ifndef LM2_NO_CPP_OPERATORS
#  include "lm2_geometry_operators.h"
_LM2_DEFINE_RAY2_OPERATORS(lm2_ray2_f64, lm2_v2f64, double)
_LM2_DEFINE_RAY2_OPERATORS(lm2_ray2_f32, lm2_v2f32, float)
#endif
