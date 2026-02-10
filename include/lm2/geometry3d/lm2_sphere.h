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
// Sphere Types
// =============================================================================

// Sphere structure to represent a 3D sphere
typedef struct lm2_sphere_f64 {
  lm2_v3_f64 center;
  double radius;
} lm2_sphere_f64;

typedef struct lm2_sphere_f32 {
  lm2_v3_f32 center;
  float radius;
} lm2_sphere_f32;

// Default sphere type
typedef lm2_sphere_f32 lm2_sphere;

// =============================================================================
// Construction Helpers
// =============================================================================

// Create a sphere from center point and radius
LM2_API lm2_sphere_f64 lm2_sphere_make_f64(lm2_v3_f64 center, double radius);
LM2_API lm2_sphere_f32 lm2_sphere_make_f32(lm2_v3_f32 center, float radius);

// Create a sphere from coordinates and radius
LM2_API lm2_sphere_f64 lm2_sphere_make_coords_f64(double x, double y, double z, double radius);
LM2_API lm2_sphere_f32 lm2_sphere_make_coords_f32(float x, float y, float z, float radius);

// Create a unit sphere at origin
LM2_API lm2_sphere_f64 lm2_sphere_unit_f64(void);
LM2_API lm2_sphere_f32 lm2_sphere_unit_f32(void);

// =============================================================================
// Sphere Properties
// =============================================================================

// Get the volume of a sphere
LM2_API double lm2_sphere_volume_f64(lm2_sphere_f64 sphere);
LM2_API float lm2_sphere_volume_f32(lm2_sphere_f32 sphere);

// Get the surface area of a sphere
LM2_API double lm2_sphere_surface_area_f64(lm2_sphere_f64 sphere);
LM2_API float lm2_sphere_surface_area_f32(lm2_sphere_f32 sphere);

// Get the diameter of a sphere
LM2_API double lm2_sphere_diameter_f64(lm2_sphere_f64 sphere);
LM2_API float lm2_sphere_diameter_f32(lm2_sphere_f32 sphere);

// =============================================================================
// Sphere Tests
// =============================================================================

// Check if a point is inside a sphere
LM2_API bool lm2_sphere_contains_point_f64(lm2_sphere_f64 sphere, lm2_v3_f64 point);
LM2_API bool lm2_sphere_contains_point_f32(lm2_sphere_f32 sphere, lm2_v3_f32 point);

// Check if two spheres overlap
LM2_API bool lm2_spheres_overlap_f64(lm2_sphere_f64 a, lm2_sphere_f64 b);
LM2_API bool lm2_spheres_overlap_f32(lm2_sphere_f32 a, lm2_sphere_f32 b);

// Check if sphere a is completely inside sphere b
LM2_API bool lm2_sphere_contains_sphere_f64(lm2_sphere_f64 a, lm2_sphere_f64 b);
LM2_API bool lm2_sphere_contains_sphere_f32(lm2_sphere_f32 a, lm2_sphere_f32 b);

// =============================================================================
// Sphere Transformations
// =============================================================================

// Translate a sphere by an offset
LM2_API lm2_sphere_f64 lm2_sphere_translate_f64(lm2_sphere_f64 sphere, lm2_v3_f64 offset);
LM2_API lm2_sphere_f32 lm2_sphere_translate_f32(lm2_sphere_f32 sphere, lm2_v3_f32 offset);

// Scale a sphere's radius
LM2_API lm2_sphere_f64 lm2_sphere_scale_f64(lm2_sphere_f64 sphere, double scale);
LM2_API lm2_sphere_f32 lm2_sphere_scale_f32(lm2_sphere_f32 sphere, float scale);

// #############################################################################
LM2_HEADER_END;
// #############################################################################