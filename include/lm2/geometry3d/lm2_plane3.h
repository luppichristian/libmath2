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
#include "lm2/vectors/lm2_vector3.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// Plane Types
// =============================================================================

// Plane structure to represent a 3D plane using normal-distance form
// The plane equation is: dot(normal, point) = distance
// Where normal is a unit vector
typedef struct lm2_plane3_f64 {
  lm2_v3f64 normal;  // Unit normal vector
  double distance;   // Distance from origin along normal
} lm2_plane3_f64;

typedef struct lm2_plane3_f32 {
  lm2_v3f32 normal;  // Unit normal vector
  float distance;    // Distance from origin along normal
} lm2_plane3_f32;

// Default plane type
typedef lm2_plane3_f32 lm2_plane3;

// =============================================================================
// Construction Helpers
// =============================================================================

// Create a plane from a normal vector and distance from origin
// The normal will be normalized automatically
LM2_API lm2_plane3_f64 lm2_plane3_make_f64(lm2_v3f64 normal, double distance);
LM2_API lm2_plane3_f32 lm2_plane3_make_f32(lm2_v3f32 normal, float distance);

// Create a plane from a point on the plane and a normal vector
// The normal will be normalized automatically
LM2_API lm2_plane3_f64 lm2_plane3_from_point_normal_f64(lm2_v3f64 point, lm2_v3f64 normal);
LM2_API lm2_plane3_f32 lm2_plane3_from_point_normal_f32(lm2_v3f32 point, lm2_v3f32 normal);

// Create a plane from three points (counter-clockwise winding defines normal)
LM2_API lm2_plane3_f64 lm2_plane3_from_points_f64(lm2_v3f64 p0, lm2_v3f64 p1, lm2_v3f64 p2);
LM2_API lm2_plane3_f32 lm2_plane3_from_points_f32(lm2_v3f32 p0, lm2_v3f32 p1, lm2_v3f32 p2);

// Create standard planes (XY, XZ, YZ at origin)
LM2_API lm2_plane3_f64 lm2_plane3_xy_f64(void);
LM2_API lm2_plane3_f32 lm2_plane3_xy_f32(void);

LM2_API lm2_plane3_f64 lm2_plane3_xz_f64(void);
LM2_API lm2_plane3_f32 lm2_plane3_xz_f32(void);

LM2_API lm2_plane3_f64 lm2_plane3_yz_f64(void);
LM2_API lm2_plane3_f32 lm2_plane3_yz_f32(void);

// =============================================================================
// Plane Operations
// =============================================================================

// Get the signed distance from a point to the plane
// Positive means on the side of the normal, negative means opposite side
LM2_API double lm2_plane3_distance_to_point_f64(lm2_plane3_f64 plane, lm2_v3f64 point);
LM2_API float lm2_plane3_distance_to_point_f32(lm2_plane3_f32 plane, lm2_v3f32 point);

// Project a point onto the plane
LM2_API lm2_v3f64 lm2_plane3_project_point_f64(lm2_plane3_f64 plane, lm2_v3f64 point);
LM2_API lm2_v3f32 lm2_plane3_project_point_f32(lm2_plane3_f32 plane, lm2_v3f32 point);

// Get the closest point on the plane to a given point
LM2_API lm2_v3f64 lm2_plane3_closest_point_f64(lm2_plane3_f64 plane, lm2_v3f64 point);
LM2_API lm2_v3f32 lm2_plane3_closest_point_f32(lm2_plane3_f32 plane, lm2_v3f32 point);

// =============================================================================
// Plane Tests
// =============================================================================

// Check if a point is on the plane (within epsilon tolerance)
LM2_API bool lm2_plane3_contains_point_f64(lm2_plane3_f64 plane, lm2_v3f64 point, double epsilon);
LM2_API bool lm2_plane3_contains_point_f32(lm2_plane3_f32 plane, lm2_v3f32 point, float epsilon);

// Check which side of the plane a point is on
// Returns: > 0 if on normal side, < 0 if opposite, 0 if on plane
LM2_API double lm2_plane3_side_f64(lm2_plane3_f64 plane, lm2_v3f64 point);
LM2_API float lm2_plane3_side_f32(lm2_plane3_f32 plane, lm2_v3f32 point);

// =============================================================================
// Plane Transformations
// =============================================================================

// Flip the plane (reverse normal and negate distance)
LM2_API lm2_plane3_f64 lm2_plane3_flip_f64(lm2_plane3_f64 plane);
LM2_API lm2_plane3_f32 lm2_plane3_flip_f32(lm2_plane3_f32 plane);

// Translate the plane by an offset
LM2_API lm2_plane3_f64 lm2_plane3_translate_f64(lm2_plane3_f64 plane, lm2_v3f64 offset);
LM2_API lm2_plane3_f32 lm2_plane3_translate_f32(lm2_plane3_f32 plane, lm2_v3f32 offset);

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// C++ operator overloads (must be outside extern "C")
#ifndef LM2_NO_CPP_OPERATORS
#  include "lm2_geometry_operators.h"
_LM2_DEFINE_PLANE3_OPERATORS(lm2_plane3_f64, f64, lm2_v3f64, double)
_LM2_DEFINE_PLANE3_OPERATORS(lm2_plane3_f32, f32, lm2_v3f32, float)
#endif
