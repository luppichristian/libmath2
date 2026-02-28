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
#include "lm2/ranges/lm2_range3.h"
#include "lm2/vectors/lm2_vector3.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// Ray Types (3D)
// =============================================================================

// 3D Ray structure
typedef struct lm2_ray3_f64 {
  lm2_v3_f64 origin;     // Ray origin position
  lm2_v3_f64 direction;  // Ray direction (should be normalized)
  double t_max;          // Maximum distance along ray
} lm2_ray3_f64;

typedef struct lm2_ray3_f32 {
  lm2_v3_f32 origin;     // Ray origin position
  lm2_v3_f32 direction;  // Ray direction (should be normalized)
  float t_max;           // Maximum distance along ray
} lm2_ray3_f32;

// =============================================================================
// Ray Hit Result Types (3D)
// =============================================================================

// 3D Ray hit result
typedef struct lm2_rayhit3_f64 {
  bool hit;           // Whether the ray hit something
  double t;           // Distance along ray where hit occurred
  lm2_v3_f64 point;   // Hit point in world space
  lm2_v3_f64 normal;  // Surface normal at hit point (unit length)
} lm2_rayhit3_f64;

typedef struct lm2_rayhit3_f32 {
  bool hit;           // Whether the ray hit something
  float t;            // Distance along ray where hit occurred
  lm2_v3_f32 point;   // Hit point in world space
  lm2_v3_f32 normal;  // Surface normal at hit point (unit length)
} lm2_rayhit3_f32;

// =============================================================================
// 3D Ray Construction
// =============================================================================

// Create a 3D ray from origin, direction, and max distance
LM2_API lm2_ray3_f64 lm2_ray3_make_f64(lm2_v3_f64 origin, lm2_v3_f64 direction, double t_max);
LM2_API lm2_ray3_f32 lm2_ray3_make_f32(lm2_v3_f32 origin, lm2_v3_f32 direction, float t_max);

// Create a 3D ray from two points
LM2_API lm2_ray3_f64 lm2_ray3_from_points_f64(lm2_v3_f64 start, lm2_v3_f64 end);
LM2_API lm2_ray3_f32 lm2_ray3_from_points_f32(lm2_v3_f32 start, lm2_v3_f32 end);

// Get point along ray at distance t
LM2_API lm2_v3_f64 lm2_ray3_point_at_f64(lm2_ray3_f64 ray, double t);
LM2_API lm2_v3_f32 lm2_ray3_point_at_f32(lm2_ray3_f32 ray, float t);

// =============================================================================
// 3D Ray vs Primitive Tests
// =============================================================================

// Ray vs Sphere (3D circle)
LM2_API lm2_rayhit3_f64 lm2_raycast_sphere_f64(lm2_ray3_f64 ray, lm2_v3_f64 center, double radius);
LM2_API lm2_rayhit3_f32 lm2_raycast_sphere_f32(lm2_ray3_f32 ray, lm2_v3_f32 center, float radius);

// Ray vs AABB (range3)
LM2_API lm2_rayhit3_f64 lm2_raycast_aabb3_f64(lm2_ray3_f64 ray, lm2_r3_f64 aabb);
LM2_API lm2_rayhit3_f32 lm2_raycast_aabb3_f32(lm2_ray3_f32 ray, lm2_r3_f32 aabb);

// Ray vs Triangle (3D)
LM2_API lm2_rayhit3_f64 lm2_raycast_triangle_f64(lm2_ray3_f64 ray, lm2_v3_f64 v0, lm2_v3_f64 v1, lm2_v3_f64 v2);
LM2_API lm2_rayhit3_f32 lm2_raycast_triangle_f32(lm2_ray3_f32 ray, lm2_v3_f32 v0, lm2_v3_f32 v1, lm2_v3_f32 v2);

// Ray vs Plane (3D)
LM2_API lm2_rayhit3_f64 lm2_raycast_plane_f64(lm2_ray3_f64 ray, lm2_v3_f64 plane_point, lm2_v3_f64 plane_normal);
LM2_API lm2_rayhit3_f32 lm2_raycast_plane_f32(lm2_ray3_f32 ray, lm2_v3_f32 plane_point, lm2_v3_f32 plane_normal);

// Ray vs Capsule (3D)
LM2_API lm2_rayhit3_f64 lm2_raycast_capsule_f64(lm2_ray3_f64 ray, lm2_v3_f64 start, lm2_v3_f64 end, double radius);
LM2_API lm2_rayhit3_f32 lm2_raycast_capsule_f32(lm2_ray3_f32 ray, lm2_v3_f32 start, lm2_v3_f32 end, float radius);

// Ray vs Edge/Line Segment (3D) - returns closest approach
LM2_API lm2_rayhit3_f64 lm2_raycast_edge_f64(lm2_ray3_f64 ray, lm2_v3_f64 edge_start, lm2_v3_f64 edge_end, double tolerance);
LM2_API lm2_rayhit3_f32 lm2_raycast_edge_f32(lm2_ray3_f32 ray, lm2_v3_f32 edge_start, lm2_v3_f32 edge_end, float tolerance);

// =============================================================================
// Generic Shape Raycasting
// =============================================================================

#include "lm2_shape3.h"

// Generic ray vs shape (dispatches based on shape type)
LM2_API lm2_rayhit3_f64 lm2_raycast_shape3_f64(lm2_ray3_f64 ray, lm2_shape3_f64 shape);
LM2_API lm2_rayhit3_f32 lm2_raycast_shape3_f32(lm2_ray3_f32 ray, lm2_shape3_f32 shape);

// =============================================================================
// Epsilon/Tolerance Constants
// =============================================================================

// Default epsilon for 3D raycast operations
#define LM2_RAYCAST3_EPSILON_F64 1e-9
#define LM2_RAYCAST3_EPSILON_F32 1e-6f

// #############################################################################
LM2_HEADER_END;
// #############################################################################