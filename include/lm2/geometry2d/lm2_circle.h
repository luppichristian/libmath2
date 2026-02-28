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
// Circle Types
// =============================================================================

// Circle structure to represent a 2D circle
typedef struct lm2_circle_f64 {
  lm2_v2_f64 center;
  double radius;
} lm2_circle_f64;

typedef struct lm2_circle_f32 {
  lm2_v2_f32 center;
  float radius;
} lm2_circle_f32;

// =============================================================================
// Construction Helpers
// =============================================================================

// Create a circle from center point and radius
LM2_API lm2_circle_f64 lm2_circle_make_f64(lm2_v2_f64 center, double radius);
LM2_API lm2_circle_f32 lm2_circle_make_f32(lm2_v2_f32 center, float radius);

// Create a circle from coordinates and radius
LM2_API lm2_circle_f64 lm2_circle_make_coords_f64(double x, double y, double radius);
LM2_API lm2_circle_f32 lm2_circle_make_coords_f32(float x, float y, float radius);

// Create a unit circle at origin
LM2_API lm2_circle_f64 lm2_circle_unit_f64(void);
LM2_API lm2_circle_f32 lm2_circle_unit_f32(void);

// =============================================================================
// Circle Properties
// =============================================================================

// Get the area of a circle
LM2_API double lm2_circle_area_f64(lm2_circle_f64 circle);
LM2_API float lm2_circle_area_f32(lm2_circle_f32 circle);

// Get the circumference of a circle
LM2_API double lm2_circle_circumference_f64(lm2_circle_f64 circle);
LM2_API float lm2_circle_circumference_f32(lm2_circle_f32 circle);

// Get the diameter of a circle
LM2_API double lm2_circle_diameter_f64(lm2_circle_f64 circle);
LM2_API float lm2_circle_diameter_f32(lm2_circle_f32 circle);

// =============================================================================
// Circle Tests
// =============================================================================

// Check if a point is inside a circle
LM2_API bool lm2_circle_contains_point_f64(lm2_circle_f64 circle, lm2_v2_f64 point);
LM2_API bool lm2_circle_contains_point_f32(lm2_circle_f32 circle, lm2_v2_f32 point);

// Check if two circles overlap
LM2_API bool lm2_circles_overlap_f64(lm2_circle_f64 a, lm2_circle_f64 b);
LM2_API bool lm2_circles_overlap_f32(lm2_circle_f32 a, lm2_circle_f32 b);

// Check if circle a is completely inside circle b
LM2_API bool lm2_circle_contains_circle_f64(lm2_circle_f64 a, lm2_circle_f64 b);
LM2_API bool lm2_circle_contains_circle_f32(lm2_circle_f32 a, lm2_circle_f32 b);

// =============================================================================
// Circle Transformations
// =============================================================================

// Translate a circle by an offset
LM2_API lm2_circle_f64 lm2_circle_translate_f64(lm2_circle_f64 circle, lm2_v2_f64 offset);
LM2_API lm2_circle_f32 lm2_circle_translate_f32(lm2_circle_f32 circle, lm2_v2_f32 offset);

// Scale a circle's radius
LM2_API lm2_circle_f64 lm2_circle_scale_f64(lm2_circle_f64 circle, double scale);
LM2_API lm2_circle_f32 lm2_circle_scale_f32(lm2_circle_f32 circle, float scale);

// #############################################################################
LM2_HEADER_END;
// #############################################################################