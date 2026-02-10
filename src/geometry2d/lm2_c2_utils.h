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

// Internal header for converting between libmath2 and cute_c2 types
// Used by manifold2.c and raycast2.c to avoid duplication

#include "lm2/geometry2d/lm2_capsule2.h"
#include "lm2/geometry2d/lm2_circle.h"
#include "lm2/geometry2d/lm2_manifold2.h"
#include "lm2/geometry2d/lm2_polygon.h"
#include "lm2/geometry2d/lm2_raycast2.h"
#include "lm2/geometry2d/lm2_triangle2.h"
#include "lm2/lm2_base.h"
#include "lm2/ranges/lm2_range2.h"
#include "lm2/vectors/lm2_vector2.h"

#include <cute_c2.h>

// =============================================================================
// Vector Conversions
// =============================================================================

c2v lm22_f32_to_c2v(lm2_v2_f32 v);
c2v lm22_f64_to_c2v(lm2_v2_f64 v);
lm2_v2_f32 c2v_to_lm22_f32(c2v v);
lm2_v2_f64 c2v_to_lm22_f64(c2v v);

// =============================================================================
// Shape Conversions
// =============================================================================

c2Ray lm2_ray2_f32_to_c2(lm2_ray2_f32 ray);
c2Ray lm2_ray2_f64_to_c2(lm2_ray2_f64 ray);

c2Circle lm2_circle_f32_to_c2(lm2_circle_f32 circle);
c2Circle lm2_circle_f64_to_c2(lm2_circle_f64 circle);

c2AABB lm2_r2_f32_to_c2(lm2_r2_f32 aabb);
c2AABB lm2_r2_f64_to_c2(lm2_r2_f64 aabb);

c2Capsule lm2_capsule2_f32_to_c2(lm2_capsule2_f32 capsule);
c2Capsule lm2_capsule2_f64_to_c2(lm2_capsule2_f64 capsule);

c2Poly lm2_polygon_f32_to_c2(lm2_polygon_f32 polygon);
c2Poly lm2_polygon_f64_to_c2(lm2_polygon_f64 polygon);

c2Poly lm2_triangle2_f32_to_c2(const lm2_triangle2_f32 tri);
c2Poly lm2_triangle2_f64_to_c2(const lm2_triangle2_f64 tri);

// =============================================================================
// Manifold Conversions
// =============================================================================

void c2_manifold_to_lm2_f32(c2Manifold m, lm2_manifold_f32* out);
void c2_manifold_to_lm2_f64(c2Manifold m, lm2_manifold_f64* out);
