#include <lm2/lm2_bootstrap.h>

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

#ifndef LM2_GEOMETRY3D_LM2_RAYCAST3_H_INCLUDED
#define LM2_GEOMETRY3D_LM2_RAYCAST3_H_INCLUDED

#include "lm2/lm2_base.h"
#include "lm2/ranges/lm2_range3.h"
#include "lm2/vectors/lm2_vector3.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// Ray Types (3D)
// =============================================================================

// A ray is origin + t * direction, with query interval 0 <= t <= t_max.
// Ray and primitive coordinates must be in the same caller-selected space.
// t is a distance only for a unit direction; make does not normalize it.
typedef struct lm2_ray3_f64 {
  lm2_v3_f64 origin;     // Ray origin position
  lm2_v3_f64 direction;  // Ray direction (should be normalized)
  double t_max;          // Maximum ray parameter
} lm2_ray3_f64;

typedef struct lm2_ray3_f32 {
  lm2_v3_f32 origin;     // Ray origin position
  lm2_v3_f32 direction;  // Ray direction (should be normalized)
  float t_max;           // Maximum ray parameter
} lm2_ray3_f32;

// =============================================================================
// Ray Hit Result Types (3D)
// =============================================================================

// 3D Ray hit result
typedef struct lm2_rayhit3_f64 {
  bool hit;           // Whether the ray hit something
  double t;           // Ray parameter at hit
  lm2_v3_f64 point;   // Hit point in input coordinate space
  lm2_v3_f64 normal;  // Hit normal; may be zero for degenerate cases
} lm2_rayhit3_f64;

typedef struct lm2_rayhit3_f32 {
  bool hit;           // Whether the ray hit something
  float t;            // Ray parameter at hit
  lm2_v3_f32 point;   // Hit point in input coordinate space
  lm2_v3_f32 normal;  // Hit normal; may be zero for degenerate cases
} lm2_rayhit3_f32;

// =============================================================================
// 3D Ray Construction
// =============================================================================

// Store origin, direction, and maximum parameter unchanged.
LM2_API lm2_ray3_f64 lm2_ray3_make_f64(lm2_v3_f64 origin, lm2_v3_f64 direction, double t_max);
LM2_API lm2_ray3_f32 lm2_ray3_make_f32(lm2_v3_f32 origin, lm2_v3_f32 direction, float t_max);

// Create a ray from start to end: direction is normalized and t_max is the
// segment length. Coincident points produce zero direction and t_max.
LM2_API lm2_ray3_f64 lm2_ray3_from_points_f64(lm2_v3_f64 start, lm2_v3_f64 end);
LM2_API lm2_ray3_f32 lm2_ray3_from_points_f32(lm2_v3_f32 start, lm2_v3_f32 end);

// Return origin + t * direction without clamping t to the ray interval.
LM2_API lm2_v3_f64 lm2_ray3_point_at_f64(lm2_ray3_f64 ray, double t);
LM2_API lm2_v3_f32 lm2_ray3_point_at_f32(lm2_ray3_f32 ray, float t);

// =============================================================================
// 3D Ray vs Primitive Tests
// =============================================================================

// The queries below return a zero-initialized result on a miss. For sphere and
// capsule, an origin inside the shape reports the forward exit surface.
// Ray vs Sphere. Radius is treated as its absolute value. Surface hit points
// are computed relative to the sphere center; when t rounds at large
// distances, point can differ from
// lm2_ray3_point_at(ray, t). A stationary ray inside returns its origin and a
// zero normal.
LM2_API lm2_rayhit3_f64 lm2_raycast_sphere_f64(lm2_ray3_f64 ray, lm2_v3_f64 center, double radius);
LM2_API lm2_rayhit3_f32 lm2_raycast_sphere_f32(lm2_ray3_f32 ray, lm2_v3_f32 center, float radius);

// Ray vs AABB (range3). For an origin inside or on the box, returns t=0
// and the origin. A surface-origin normal is the first matching outward face
// in x, y, z order; an interior normal is a fallback axis based on the largest
// absolute displacement from the box center (ties favor z, then y).
LM2_API lm2_rayhit3_f64 lm2_raycast_aabb3_f64(lm2_ray3_f64 ray, lm2_r3_f64 aabb);
LM2_API lm2_rayhit3_f32 lm2_raycast_aabb3_f32(lm2_ray3_f32 ray, lm2_r3_f32 aabb);

// Ray vs Triangle (3D). Both sides are tested; the normal follows vertex
// winding, not the ray direction. The absolute determinant threshold uses
// LM2_RAYCAST3_EPSILON_F32/F64 and depends on triangle and direction scale. Edge and
// vertex hits are included.
LM2_API lm2_rayhit3_f64 lm2_raycast_triangle_f64(lm2_ray3_f64 ray, lm2_v3_f64 v0, lm2_v3_f64 v1, lm2_v3_f64 v2);
LM2_API lm2_rayhit3_f32 lm2_raycast_triangle_f32(lm2_ray3_f32 ray, lm2_v3_f32 v0, lm2_v3_f32 v1, lm2_v3_f32 v2);

// Ray vs Plane (3D). The supplied normal is normalized and returned without
// facing it toward the ray. A zero normal or abs(dot(normal, direction)) <=
// LM2_RAYCAST3_EPSILON_F32/F64 misses. An origin on the plane otherwise hits at t=0.
LM2_API lm2_rayhit3_f64 lm2_raycast_plane_f64(lm2_ray3_f64 ray, lm2_v3_f64 plane_point, lm2_v3_f64 plane_normal);
LM2_API lm2_rayhit3_f32 lm2_raycast_plane_f32(lm2_ray3_f32 ray, lm2_v3_f32 plane_point, lm2_v3_f32 plane_normal);

// Ray vs Capsule (3D). Supply a nonnegative radius. Coincident endpoints use
// the sphere query. A stationary
// ray inside returns its origin and a zero normal. At extreme distances,
// rounded t may not reproduce the returned surface point via point_at.
LM2_API lm2_rayhit3_f64 lm2_raycast_capsule_f64(lm2_ray3_f64 ray, lm2_v3_f64 start, lm2_v3_f64 end, double radius);
LM2_API lm2_rayhit3_f32 lm2_raycast_capsule_f32(lm2_ray3_f32 ray, lm2_v3_f32 start, lm2_v3_f32 end, float radius);

// Closest approach of the finite ray interval and finite segment. Hit if their
// distance is <= nonnegative tolerance; point is on the ray, and normal points
// from the segment to that point. At zero separation it is the normalized
// cross(direction, edge), or zero when that cross product is zero.
LM2_API lm2_rayhit3_f64 lm2_raycast_edge_f64(lm2_ray3_f64 ray, lm2_v3_f64 edge_start, lm2_v3_f64 edge_end, double tolerance);
LM2_API lm2_rayhit3_f32 lm2_raycast_edge_f32(lm2_ray3_f32 ray, lm2_v3_f32 edge_start, lm2_v3_f32 edge_end, float tolerance);

// =============================================================================
// Generic Shape Raycasting
// =============================================================================

#include "lm2_shape3.h"

// Dispatch by shape type; shape.data must be non-NULL and match the tag. Edge
// tests use LM2_RAYCAST3_EPSILON_F32/F64 as tolerance. Unknown tags return a miss.
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


#endif // LM2_GEOMETRY3D_LM2_RAYCAST3_H_INCLUDED


#ifndef LM2_PRIVATE_DECLARATION_PHASE
#  include "lm2_raycast3_impl.h"
#endif
