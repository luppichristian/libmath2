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

// cute_c2 has externally linked implementation symbols. Namespace every one,
// including its undeclared helpers, so a static consumer can embed another
// copy and an ELF consumer cannot interpose on libmath2's collision backend.
// The list tracks the pinned cute_c2 implementation in CMakeLists.txt.
#define c2AABBtoAABB               lm2_private_c2AABBtoAABB
#define c2AABBtoAABBManifold       lm2_private_c2AABBtoAABBManifold
#define c2AABBtoCapsule            lm2_private_c2AABBtoCapsule
#define c2AABBtoCapsuleManifold    lm2_private_c2AABBtoCapsuleManifold
#define c2AABBtoPoint              lm2_private_c2AABBtoPoint
#define c2AABBtoPoly               lm2_private_c2AABBtoPoly
#define c2AABBtoPolyManifold       lm2_private_c2AABBtoPolyManifold
#define c2CapsuletoCapsule         lm2_private_c2CapsuletoCapsule
#define c2CapsuletoCapsuleManifold lm2_private_c2CapsuletoCapsuleManifold
#define c2CapsuletoPoly            lm2_private_c2CapsuletoPoly
#define c2CapsuletoPolyManifold    lm2_private_c2CapsuletoPolyManifold
#define c2CastRay                  lm2_private_c2CastRay
#define c2CircleToPoint            lm2_private_c2CircleToPoint
#define c2CircletoAABB             lm2_private_c2CircletoAABB
#define c2CircletoAABBManifold     lm2_private_c2CircletoAABBManifold
#define c2CircletoCapsule          lm2_private_c2CircletoCapsule
#define c2CircletoCapsuleManifold  lm2_private_c2CircletoCapsuleManifold
#define c2CircletoCircle           lm2_private_c2CircletoCircle
#define c2CircletoCircleManifold   lm2_private_c2CircletoCircleManifold
#define c2CircletoPoly             lm2_private_c2CircletoPoly
#define c2CircletoPolyManifold     lm2_private_c2CircletoPolyManifold
#define c2Collide                  lm2_private_c2Collide
#define c2Collided                 lm2_private_c2Collided
#define c2Dual                     lm2_private_c2Dual
#define c2GJK                      lm2_private_c2GJK
#define c2Hull                     lm2_private_c2Hull
#define c2Inflate                  lm2_private_c2Inflate
#define c2InflatePoly              lm2_private_c2InflatePoly
#define c2MakePoly                 lm2_private_c2MakePoly
#define c2Norms                    lm2_private_c2Norms
#define c2PolytoPoly               lm2_private_c2PolytoPoly
#define c2PolytoPolyManifold       lm2_private_c2PolytoPolyManifold
#define c2RaytoAABB                lm2_private_c2RaytoAABB
#define c2RaytoCapsule             lm2_private_c2RaytoCapsule
#define c2RaytoCircle              lm2_private_c2RaytoCircle
#define c2RaytoPoly                lm2_private_c2RaytoPoly
#define c2TOI                      lm2_private_c2TOI

#include <cute_c2.h>

// Conversion helpers are internal to the library as well.
#define c2_manifold_to_lm2_f32  lm2_private_c2_manifold_to_lm2_f32
#define c2_manifold_to_lm2_f64  lm2_private_c2_manifold_to_lm2_f64
#define c2v_to_lm22_f32         lm2_private_c2v_to_lm22_f32
#define c2v_to_lm22_f64         lm2_private_c2v_to_lm22_f64
#define lm22_f32_to_c2v         lm2_private_lm22_f32_to_c2v
#define lm22_f64_to_c2v         lm2_private_lm22_f64_to_c2v
#define lm2_ray2_f32_to_c2      lm2_private_ray2_f32_to_c2
#define lm2_ray2_f64_to_c2      lm2_private_ray2_f64_to_c2
#define lm2_circle_f32_to_c2    lm2_private_circle_f32_to_c2
#define lm2_circle_f64_to_c2    lm2_private_circle_f64_to_c2
#define lm2_r2_f32_to_c2        lm2_private_r2_f32_to_c2
#define lm2_r2_f64_to_c2        lm2_private_r2_f64_to_c2
#define lm2_capsule2_f32_to_c2  lm2_private_capsule2_f32_to_c2
#define lm2_capsule2_f64_to_c2  lm2_private_capsule2_f64_to_c2
#define lm2_polygon_f32_to_c2   lm2_private_polygon_f32_to_c2
#define lm2_polygon_f64_to_c2   lm2_private_polygon_f64_to_c2
#define lm2_triangle2_f32_to_c2 lm2_private_triangle2_f32_to_c2
#define lm2_triangle2_f64_to_c2 lm2_private_triangle2_f64_to_c2

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
