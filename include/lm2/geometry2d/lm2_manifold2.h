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
// Collision Manifold Types
// =============================================================================

// Collision manifold structure to describe how shapes collide
typedef struct lm2_manifold_f64 {
  int count;                     // Number of contact points (0, 1, or 2)
  double depths[2];              // Penetration depths
  lm2_v2_f64 contact_points[2];  // Contact points
  lm2_v2_f64 normal;             // Collision normal (from A to B)
} lm2_manifold_f64;

typedef struct lm2_manifold_f32 {
  int count;                     // Number of contact points (0, 1, or 2)
  float depths[2];               // Penetration depths
  lm2_v2_f32 contact_points[2];  // Contact points
  lm2_v2_f32 normal;             // Collision normal (from A to B)
} lm2_manifold_f32;

// =============================================================================
// Boolean Collision Detection (Fast, YES/NO only)
// =============================================================================

// Circle to Circle
LM2_API bool lm2_collide_circle_to_circle_f64(lm2_circle_f64 a, lm2_circle_f64 b);
LM2_API bool lm2_collide_circle_to_circle_f32(lm2_circle_f32 a, lm2_circle_f32 b);

// Circle to AABB
LM2_API bool lm2_collide_circle_to_aabb_f64(lm2_circle_f64 circle, lm2_r2_f64 aabb);
LM2_API bool lm2_collide_circle_to_aabb_f32(lm2_circle_f32 circle, lm2_r2_f32 aabb);

// Circle to Capsule
LM2_API bool lm2_collide_circle_to_capsule_f64(lm2_circle_f64 circle, lm2_capsule2_f64 capsule);
LM2_API bool lm2_collide_circle_to_capsule_f32(lm2_circle_f32 circle, lm2_capsule2_f32 capsule);

// Circle to Polygon
LM2_API bool lm2_collide_circle_to_polygon_f64(lm2_circle_f64 circle, lm2_polygon_f64 polygon);
LM2_API bool lm2_collide_circle_to_polygon_f32(lm2_circle_f32 circle, lm2_polygon_f32 polygon);

// AABB to AABB
LM2_API bool lm2_collide_aabb_to_aabb_f64(lm2_r2_f64 a, lm2_r2_f64 b);
LM2_API bool lm2_collide_aabb_to_aabb_f32(lm2_r2_f32 a, lm2_r2_f32 b);

// AABB to Capsule
LM2_API bool lm2_collide_aabb_to_capsule_f64(lm2_r2_f64 aabb, lm2_capsule2_f64 capsule);
LM2_API bool lm2_collide_aabb_to_capsule_f32(lm2_r2_f32 aabb, lm2_capsule2_f32 capsule);

// AABB to Polygon
LM2_API bool lm2_collide_aabb_to_polygon_f64(lm2_r2_f64 aabb, lm2_polygon_f64 polygon);
LM2_API bool lm2_collide_aabb_to_polygon_f32(lm2_r2_f32 aabb, lm2_polygon_f32 polygon);

// Capsule to Capsule
LM2_API bool lm2_collide_capsule_to_capsule_f64(lm2_capsule2_f64 a, lm2_capsule2_f64 b);
LM2_API bool lm2_collide_capsule_to_capsule_f32(lm2_capsule2_f32 a, lm2_capsule2_f32 capsule);

// Capsule to Polygon
LM2_API bool lm2_collide_capsule_to_polygon_f64(lm2_capsule2_f64 capsule, lm2_polygon_f64 polygon);
LM2_API bool lm2_collide_capsule_to_polygon_f32(lm2_capsule2_f32 capsule, lm2_polygon_f32 polygon);

// Polygon to Polygon
LM2_API bool lm2_collide_polygon_to_polygon_f64(lm2_polygon_f64 a, lm2_polygon_f64 b);
LM2_API bool lm2_collide_polygon_to_polygon_f32(lm2_polygon_f32 a, lm2_polygon_f32 b);

// =============================================================================
// Manifold Generation (Slower, provides collision details)
// =============================================================================

// Circle to Circle Manifold
LM2_API void lm2_manifold_circle_to_circle_f64(lm2_circle_f64 a, lm2_circle_f64 b, lm2_manifold_f64* out_manifold);
LM2_API void lm2_manifold_circle_to_circle_f32(lm2_circle_f32 a, lm2_circle_f32 b, lm2_manifold_f32* out_manifold);

// Circle to AABB Manifold
LM2_API void lm2_manifold_circle_to_aabb_f64(lm2_circle_f64 circle, lm2_r2_f64 aabb, lm2_manifold_f64* out_manifold);
LM2_API void lm2_manifold_circle_to_aabb_f32(lm2_circle_f32 circle, lm2_r2_f32 aabb, lm2_manifold_f32* out_manifold);

// Circle to Capsule Manifold
LM2_API void lm2_manifold_circle_to_capsule_f64(lm2_circle_f64 circle, lm2_capsule2_f64 capsule, lm2_manifold_f64* out_manifold);
LM2_API void lm2_manifold_circle_to_capsule_f32(lm2_circle_f32 circle, lm2_capsule2_f32 capsule, lm2_manifold_f32* out_manifold);

// Circle to Polygon Manifold
LM2_API void lm2_manifold_circle_to_polygon_f64(lm2_circle_f64 circle, lm2_polygon_f64 polygon, lm2_manifold_f64* out_manifold);
LM2_API void lm2_manifold_circle_to_polygon_f32(lm2_circle_f32 circle, lm2_polygon_f32 polygon, lm2_manifold_f32* out_manifold);

// AABB to AABB Manifold
LM2_API void lm2_manifold_aabb_to_aabb_f64(lm2_r2_f64 a, lm2_r2_f64 b, lm2_manifold_f64* out_manifold);
LM2_API void lm2_manifold_aabb_to_aabb_f32(lm2_r2_f32 a, lm2_r2_f32 b, lm2_manifold_f32* out_manifold);

// AABB to Capsule Manifold
LM2_API void lm2_manifold_aabb_to_capsule_f64(lm2_r2_f64 aabb, lm2_capsule2_f64 capsule, lm2_manifold_f64* out_manifold);
LM2_API void lm2_manifold_aabb_to_capsule_f32(lm2_r2_f32 aabb, lm2_capsule2_f32 capsule, lm2_manifold_f32* out_manifold);

// AABB to Polygon Manifold
LM2_API void lm2_manifold_aabb_to_polygon_f64(lm2_r2_f64 aabb, lm2_polygon_f64 polygon, lm2_manifold_f64* out_manifold);
LM2_API void lm2_manifold_aabb_to_polygon_f32(lm2_r2_f32 aabb, lm2_polygon_f32 polygon, lm2_manifold_f32* out_manifold);

// Capsule to Capsule Manifold
LM2_API void lm2_manifold_capsule_to_capsule_f64(lm2_capsule2_f64 a, lm2_capsule2_f64 b, lm2_manifold_f64* out_manifold);
LM2_API void lm2_manifold_capsule_to_capsule_f32(lm2_capsule2_f32 a, lm2_capsule2_f32 b, lm2_manifold_f32* out_manifold);

// Capsule to Polygon Manifold
LM2_API void lm2_manifold_capsule_to_polygon_f64(lm2_capsule2_f64 capsule, lm2_polygon_f64 polygon, lm2_manifold_f64* out_manifold);
LM2_API void lm2_manifold_capsule_to_polygon_f32(lm2_capsule2_f32 capsule, lm2_polygon_f32 polygon, lm2_manifold_f32* out_manifold);

// Polygon to Polygon Manifold
LM2_API void lm2_manifold_polygon_to_polygon_f64(lm2_polygon_f64 a, lm2_polygon_f64 b, lm2_manifold_f64* out_manifold);
LM2_API void lm2_manifold_polygon_to_polygon_f32(lm2_polygon_f32 a, lm2_polygon_f32 b, lm2_manifold_f32* out_manifold);

// =============================================================================
// Triangle Collision Detection (Fast, YES/NO only)
// =============================================================================

// Triangle to Triangle
LM2_API bool lm2_collide_triangle_to_triangle_f64(const lm2_triangle2_f64 a, const lm2_triangle2_f64 b);
LM2_API bool lm2_collide_triangle_to_triangle_f32(const lm2_triangle2_f32 a, const lm2_triangle2_f32 b);

// Triangle to Circle
LM2_API bool lm2_collide_triangle_to_circle_f64(const lm2_triangle2_f64 tri, lm2_circle_f64 circle);
LM2_API bool lm2_collide_triangle_to_circle_f32(const lm2_triangle2_f32 tri, lm2_circle_f32 circle);

// Triangle to AABB
LM2_API bool lm2_collide_triangle_to_aabb_f64(const lm2_triangle2_f64 tri, lm2_r2_f64 aabb);
LM2_API bool lm2_collide_triangle_to_aabb_f32(const lm2_triangle2_f32 tri, lm2_r2_f32 aabb);

// Triangle to Capsule
LM2_API bool lm2_collide_triangle_to_capsule_f64(const lm2_triangle2_f64 tri, lm2_capsule2_f64 capsule);
LM2_API bool lm2_collide_triangle_to_capsule_f32(const lm2_triangle2_f32 tri, lm2_capsule2_f32 capsule);

// Triangle to Polygon
LM2_API bool lm2_collide_triangle_to_polygon_f64(const lm2_triangle2_f64 tri, lm2_polygon_f64 polygon);
LM2_API bool lm2_collide_triangle_to_polygon_f32(const lm2_triangle2_f32 tri, lm2_polygon_f32 polygon);

// =============================================================================
// Triangle Manifold Generation (Slower, provides collision details)
// =============================================================================

// Triangle to Triangle Manifold
LM2_API void lm2_manifold_triangle_to_triangle_f64(const lm2_triangle2_f64 a, const lm2_triangle2_f64 b, lm2_manifold_f64* out_manifold);
LM2_API void lm2_manifold_triangle_to_triangle_f32(const lm2_triangle2_f32 a, const lm2_triangle2_f32 b, lm2_manifold_f32* out_manifold);

// Triangle to Circle Manifold
LM2_API void lm2_manifold_triangle_to_circle_f64(const lm2_triangle2_f64 tri, lm2_circle_f64 circle, lm2_manifold_f64* out_manifold);
LM2_API void lm2_manifold_triangle_to_circle_f32(const lm2_triangle2_f32 tri, lm2_circle_f32 circle, lm2_manifold_f32* out_manifold);

// Triangle to AABB Manifold
LM2_API void lm2_manifold_triangle_to_aabb_f64(const lm2_triangle2_f64 tri, lm2_r2_f64 aabb, lm2_manifold_f64* out_manifold);
LM2_API void lm2_manifold_triangle_to_aabb_f32(const lm2_triangle2_f32 tri, lm2_r2_f32 aabb, lm2_manifold_f32* out_manifold);

// Triangle to Capsule Manifold
LM2_API void lm2_manifold_triangle_to_capsule_f64(const lm2_triangle2_f64 tri, lm2_capsule2_f64 capsule, lm2_manifold_f64* out_manifold);
LM2_API void lm2_manifold_triangle_to_capsule_f32(const lm2_triangle2_f32 tri, lm2_capsule2_f32 capsule, lm2_manifold_f32* out_manifold);

// Triangle to Polygon Manifold
LM2_API void lm2_manifold_triangle_to_polygon_f64(const lm2_triangle2_f64 tri, lm2_polygon_f64 polygon, lm2_manifold_f64* out_manifold);
LM2_API void lm2_manifold_triangle_to_polygon_f32(const lm2_triangle2_f32 tri, lm2_polygon_f32 polygon, lm2_manifold_f32* out_manifold);

// =============================================================================
// Plane Manifold Generation (Slower, provides collision details)
// =============================================================================

// Circle to Plane Manifold
LM2_API void lm2_manifold_circle_to_plane_f64(lm2_circle_f64 circle, lm2_plane2_f64 plane, lm2_manifold_f64* out_manifold);
LM2_API void lm2_manifold_circle_to_plane_f32(lm2_circle_f32 circle, lm2_plane2_f32 plane, lm2_manifold_f32* out_manifold);

// Capsule to Plane Manifold
LM2_API void lm2_manifold_capsule_to_plane_f64(lm2_capsule2_f64 capsule, lm2_plane2_f64 plane, lm2_manifold_f64* out_manifold);
LM2_API void lm2_manifold_capsule_to_plane_f32(lm2_capsule2_f32 capsule, lm2_plane2_f32 plane, lm2_manifold_f32* out_manifold);

// AABB to Plane Manifold
LM2_API void lm2_manifold_aabb_to_plane_f64(lm2_r2_f64 aabb, lm2_plane2_f64 plane, lm2_manifold_f64* out_manifold);
LM2_API void lm2_manifold_aabb_to_plane_f32(lm2_r2_f32 aabb, lm2_plane2_f32 plane, lm2_manifold_f32* out_manifold);

// Triangle to Plane Manifold
LM2_API void lm2_manifold_triangle_to_plane_f64(const lm2_triangle2_f64 tri, lm2_plane2_f64 plane, lm2_manifold_f64* out_manifold);
LM2_API void lm2_manifold_triangle_to_plane_f32(const lm2_triangle2_f32 tri, lm2_plane2_f32 plane, lm2_manifold_f32* out_manifold);

// Polygon to Plane Manifold
LM2_API void lm2_manifold_polygon_to_plane_f64(lm2_polygon_f64 polygon, lm2_plane2_f64 plane, lm2_manifold_f64* out_manifold);
LM2_API void lm2_manifold_polygon_to_plane_f32(lm2_polygon_f32 polygon, lm2_plane2_f32 plane, lm2_manifold_f32* out_manifold);

// =============================================================================
// Generic Shape Manifold Generation
// =============================================================================

#include "lm2_shape2.h"

// Generic shape-to-shape manifold (dispatches based on shape types)
LM2_API void lm2_manifold_shape_to_shape_f64(lm2_shape2_f64 shape_a, lm2_shape2_f64 shape_b, lm2_manifold_f64* out_manifold);
LM2_API void lm2_manifold_shape_to_shape_f32(lm2_shape2_f32 shape_a, lm2_shape2_f32 shape_b, lm2_manifold_f32* out_manifold);

// =============================================================================
// Convex Hull Generation
// =============================================================================

// Compute convex hull of a set of points
// Returns the number of vertices in the hull (fills out_vertices with hull points)
LM2_API int lm2_convex_hull_f64(lm2_v2_f64* points, int point_count, lm2_v2_f64* out_vertices, int max_vertices);
LM2_API int lm2_convex_hull_f32(lm2_v2_f32* points, int point_count, lm2_v2_f32* out_vertices, int max_vertices);

// Compute polygon normals
LM2_API void lm2_compute_normals_f64(lm2_v2_f64* vertices, lm2_v2_f64* out_normals, int vertex_count);
LM2_API void lm2_compute_normals_f32(lm2_v2_f32* vertices, lm2_v2_f32* out_normals, int vertex_count);

// Make a convex polygon (runs convex hull + computes normals)
// Modifies the polygon's vertices in place if needed
LM2_API void lm2_make_convex_polygon_f64(lm2_polygon_f64* polygon, lm2_v2_f64* out_normals);
LM2_API void lm2_make_convex_polygon_f32(lm2_polygon_f32* polygon, lm2_v2_f32* out_normals);

// #############################################################################
LM2_HEADER_END;
// #############################################################################
