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

#include "lm2/geometry2d/lm2_ray2.h"
#include "lm2/geometry2d/lm2_rayhit2.h"
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
// 2D Ray Construction
// =============================================================================

// Create a 2D ray from origin, direction, and max distance
LM2_API lm2_ray2_f64 lm2_ray2_make_f64(lm2_v2_f64 origin, lm2_v2_f64 direction, double t_max);
LM2_API lm2_ray2_f32 lm2_ray2_make_f32(lm2_v2_f32 origin, lm2_v2_f32 direction, float t_max);

// Create a 2D ray from two points
LM2_API lm2_ray2_f64 lm2_ray2_from_points_f64(lm2_v2_f64 start, lm2_v2_f64 end);
LM2_API lm2_ray2_f32 lm2_ray2_from_points_f32(lm2_v2_f32 start, lm2_v2_f32 end);

// Get point along ray at distance t
LM2_API lm2_v2_f64 lm2_ray2_point_at_f64(lm2_ray2_f64 ray, double t);
LM2_API lm2_v2_f32 lm2_ray2_point_at_f32(lm2_ray2_f32 ray, float t);

// =============================================================================
// 2D Ray vs Primitive Tests
// =============================================================================

// Ray vs Circle
LM2_API lm2_rayhit2_f64 lm2_raycast_circle_f64(lm2_ray2_f64 ray, lm2_circle_f64 circle);
LM2_API lm2_rayhit2_f32 lm2_raycast_circle_f32(lm2_ray2_f32 ray, lm2_circle_f32 circle);

// Ray vs AABB (range2)
LM2_API lm2_rayhit2_f64 lm2_raycast_aabb_f64(lm2_ray2_f64 ray, lm2_r2_f64 aabb);
LM2_API lm2_rayhit2_f32 lm2_raycast_aabb_f32(lm2_ray2_f32 ray, lm2_r2_f32 aabb);

// Ray vs Capsule
LM2_API lm2_rayhit2_f64 lm2_raycast_capsule2_f64(lm2_ray2_f64 ray, lm2_capsule2_f64 capsule);
LM2_API lm2_rayhit2_f32 lm2_raycast_capsule2_f32(lm2_ray2_f32 ray, lm2_capsule2_f32 capsule);

// Ray vs Polygon
LM2_API lm2_rayhit2_f64 lm2_raycast_polygon_f64(lm2_ray2_f64 ray, lm2_polygon_f64 polygon);
LM2_API lm2_rayhit2_f32 lm2_raycast_polygon_f32(lm2_ray2_f32 ray, lm2_polygon_f32 polygon);

// Ray vs Line Segment (edge)
// NOTE: Prefer lm2_raycast_edge2_f64/f32 (from lm2_edge2.h) which accepts an
// lm2_edge2 struct and is the canonical edge2 API.  These wrappers are kept
// for backward compatibility.
LM2_API lm2_rayhit2_f64 lm2_raycast_segment_f64(lm2_ray2_f64 ray, lm2_v2_f64 segment_start, lm2_v2_f64 segment_end);
LM2_API lm2_rayhit2_f32 lm2_raycast_segment_f32(lm2_ray2_f32 ray, lm2_v2_f32 segment_start, lm2_v2_f32 segment_end);

// Ray vs Triangle
LM2_API lm2_rayhit2_f64 lm2_raycast_triangle2_f64(lm2_ray2_f64 ray, const lm2_triangle2_f64 tri);
LM2_API lm2_rayhit2_f32 lm2_raycast_triangle2_f32(lm2_ray2_f32 ray, const lm2_triangle2_f32 tri);

// Ray vs Plane (infinite line in 2D)
LM2_API lm2_rayhit2_f64 lm2_raycast_plane2_f64(lm2_ray2_f64 ray, lm2_plane2_f64 plane);
LM2_API lm2_rayhit2_f32 lm2_raycast_plane2_f32(lm2_ray2_f32 ray, lm2_plane2_f32 plane);

// =============================================================================
// Generic Shape Raycasting
// =============================================================================

#include "lm2_shape2.h"

// Generic ray vs shape (dispatches based on shape type)
LM2_API lm2_rayhit2_f64 lm2_raycast_shape2_f64(lm2_ray2_f64 ray, lm2_shape2_f64 shape);
LM2_API lm2_rayhit2_f32 lm2_raycast_shape2_f32(lm2_ray2_f32 ray, lm2_shape2_f32 shape);

// =============================================================================
// Epsilon/Tolerance Constants
// =============================================================================

// Default epsilon for 2D raycast operations
#define LM2_RAYCAST2_EPSILON_F64 1e-9
#define LM2_RAYCAST2_EPSILON_F32 1e-6f

// #############################################################################
LM2_HEADER_END;
// #############################################################################