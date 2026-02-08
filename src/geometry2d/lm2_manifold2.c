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

#define CUTE_C2_IMPLEMENTATION
#include <cute_c2.h>

#include "lm2/geometry2d/lm2_manifold2.h"
#include "lm2/scalar/lm2_safe_ops.h"
#include "lm2/scalar/lm2_scalar.h"

#include <string.h>

// =============================================================================
// Helper Functions: Convert libmath2 types to cute_c2 types
// =============================================================================

static c2v lm2_v2f32_to_c2v(lm2_v2f32 v) {
  c2v result;
  result.x = v.x;
  result.y = v.y;
  return result;
}

static c2v lm2_v2f64_to_c2v(lm2_v2f64 v) {
  c2v result;
  result.x = (float)v.x;
  result.y = (float)v.y;
  return result;
}

static lm2_v2f32 c2v_to_lm2_v2f32(c2v v) {
  lm2_v2f32 result;
  result.x = v.x;
  result.y = v.y;
  return result;
}

static lm2_v2f64 c2v_to_lm2_v2f64(c2v v) {
  lm2_v2f64 result;
  result.x = (double)v.x;
  result.y = (double)v.y;
  return result;
}

static c2Circle lm2_circle_f32_to_c2(lm2_circle_f32 circle) {
  c2Circle result;
  result.p = lm2_v2f32_to_c2v(circle.center);
  result.r = circle.radius;
  return result;
}

static c2Circle lm2_circle_f64_to_c2(lm2_circle_f64 circle) {
  c2Circle result;
  result.p = lm2_v2f64_to_c2v(circle.center);
  result.r = (float)circle.radius;
  return result;
}

static c2Capsule lm2_capsule2_f32_to_c2(lm2_capsule2_f32 capsule) {
  c2Capsule result;
  result.a = lm2_v2f32_to_c2v(capsule.start);
  result.b = lm2_v2f32_to_c2v(capsule.end);
  result.r = capsule.radius;
  return result;
}

static c2Capsule lm2_capsule2_f64_to_c2(lm2_capsule2_f64 capsule) {
  c2Capsule result;
  result.a = lm2_v2f64_to_c2v(capsule.start);
  result.b = lm2_v2f64_to_c2v(capsule.end);
  result.r = (float)capsule.radius;
  return result;
}

static c2AABB lm2_r2f32_to_c2(lm2_r2f32 aabb) {
  c2AABB result;
  result.min = lm2_v2f32_to_c2v(aabb.min);
  result.max = lm2_v2f32_to_c2v(aabb.max);
  return result;
}

static c2AABB lm2_r2f64_to_c2(lm2_r2f64 aabb) {
  c2AABB result;
  result.min = lm2_v2f64_to_c2v(aabb.min);
  result.max = lm2_v2f64_to_c2v(aabb.max);
  return result;
}

static c2Poly lm2_polygon_f32_to_c2(lm2_polygon_f32 polygon) {
  c2Poly result;
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count <= C2_MAX_POLYGON_VERTS);

  result.count = (int)polygon.vertex_count;
  for (size_t i = 0; i < polygon.vertex_count && i < C2_MAX_POLYGON_VERTS; ++i) {
    result.verts[i] = lm2_v2f32_to_c2v(polygon.vertices[i]);
  }

  // Compute normals
  c2Norms(result.verts, result.norms, result.count);

  return result;
}

static c2Poly lm2_polygon_f64_to_c2(lm2_polygon_f64 polygon) {
  c2Poly result;
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count <= C2_MAX_POLYGON_VERTS);

  result.count = (int)polygon.vertex_count;
  for (size_t i = 0; i < polygon.vertex_count && i < C2_MAX_POLYGON_VERTS; ++i) {
    result.verts[i] = lm2_v2f64_to_c2v(polygon.vertices[i]);
  }

  // Compute normals
  c2Norms(result.verts, result.norms, result.count);

  return result;
}

static void c2_manifold_to_lm2_f32(c2Manifold m, lm2_manifold_f32* out) {
  LM2_ASSERT(out != NULL);

  out->count = m.count;
  out->normal = c2v_to_lm2_v2f32(m.n);

  for (int i = 0; i < m.count; ++i) {
    out->depths[i] = m.depths[i];
    out->contact_points[i] = c2v_to_lm2_v2f32(m.contact_points[i]);
  }
}

static void c2_manifold_to_lm2_f64(c2Manifold m, lm2_manifold_f64* out) {
  LM2_ASSERT(out != NULL);

  out->count = m.count;
  out->normal = c2v_to_lm2_v2f64(m.n);

  for (int i = 0; i < m.count; ++i) {
    out->depths[i] = (double)m.depths[i];
    out->contact_points[i] = c2v_to_lm2_v2f64(m.contact_points[i]);
  }
}

// =============================================================================
// Boolean Collision Detection - f64
// =============================================================================

LM2_API bool lm2_collide_circle_to_circle_f64(lm2_circle_f64 a, lm2_circle_f64 b) {
  return c2CircletoCircle(lm2_circle_f64_to_c2(a), lm2_circle_f64_to_c2(b)) != 0;
}

LM2_API bool lm2_collide_circle_to_aabb_f64(lm2_circle_f64 circle, lm2_r2f64 aabb) {
  return c2CircletoAABB(lm2_circle_f64_to_c2(circle), lm2_r2f64_to_c2(aabb)) != 0;
}

LM2_API bool lm2_collide_circle_to_capsule_f64(lm2_circle_f64 circle, lm2_capsule2_f64 capsule) {
  return c2CircletoCapsule(lm2_circle_f64_to_c2(circle), lm2_capsule2_f64_to_c2(capsule)) != 0;
}

LM2_API bool lm2_collide_circle_to_polygon_f64(lm2_circle_f64 circle, lm2_polygon_f64 polygon) {
  c2Poly poly = lm2_polygon_f64_to_c2(polygon);
  return c2CircletoPoly(lm2_circle_f64_to_c2(circle), &poly, NULL) != 0;
}

LM2_API bool lm2_collide_aabb_to_aabb_f64(lm2_r2f64 a, lm2_r2f64 b) {
  return c2AABBtoAABB(lm2_r2f64_to_c2(a), lm2_r2f64_to_c2(b)) != 0;
}

LM2_API bool lm2_collide_aabb_to_capsule_f64(lm2_r2f64 aabb, lm2_capsule2_f64 capsule) {
  return c2AABBtoCapsule(lm2_r2f64_to_c2(aabb), lm2_capsule2_f64_to_c2(capsule)) != 0;
}

LM2_API bool lm2_collide_aabb_to_polygon_f64(lm2_r2f64 aabb, lm2_polygon_f64 polygon) {
  c2Poly poly = lm2_polygon_f64_to_c2(polygon);
  return c2AABBtoPoly(lm2_r2f64_to_c2(aabb), &poly, NULL) != 0;
}

LM2_API bool lm2_collide_capsule_to_capsule_f64(lm2_capsule2_f64 a, lm2_capsule2_f64 b) {
  return c2CapsuletoCapsule(lm2_capsule2_f64_to_c2(a), lm2_capsule2_f64_to_c2(b)) != 0;
}

LM2_API bool lm2_collide_capsule_to_polygon_f64(lm2_capsule2_f64 capsule, lm2_polygon_f64 polygon) {
  c2Poly poly = lm2_polygon_f64_to_c2(polygon);
  return c2CapsuletoPoly(lm2_capsule2_f64_to_c2(capsule), &poly, NULL) != 0;
}

LM2_API bool lm2_collide_polygon_to_polygon_f64(lm2_polygon_f64 a, lm2_polygon_f64 b) {
  c2Poly poly_a = lm2_polygon_f64_to_c2(a);
  c2Poly poly_b = lm2_polygon_f64_to_c2(b);
  return c2PolytoPoly(&poly_a, NULL, &poly_b, NULL) != 0;
}

// =============================================================================
// Boolean Collision Detection - f32
// =============================================================================

LM2_API bool lm2_collide_circle_to_circle_f32(lm2_circle_f32 a, lm2_circle_f32 b) {
  return c2CircletoCircle(lm2_circle_f32_to_c2(a), lm2_circle_f32_to_c2(b)) != 0;
}

LM2_API bool lm2_collide_circle_to_aabb_f32(lm2_circle_f32 circle, lm2_r2f32 aabb) {
  return c2CircletoAABB(lm2_circle_f32_to_c2(circle), lm2_r2f32_to_c2(aabb)) != 0;
}

LM2_API bool lm2_collide_circle_to_capsule_f32(lm2_circle_f32 circle, lm2_capsule2_f32 capsule) {
  return c2CircletoCapsule(lm2_circle_f32_to_c2(circle), lm2_capsule2_f32_to_c2(capsule)) != 0;
}

LM2_API bool lm2_collide_circle_to_polygon_f32(lm2_circle_f32 circle, lm2_polygon_f32 polygon) {
  c2Poly poly = lm2_polygon_f32_to_c2(polygon);
  return c2CircletoPoly(lm2_circle_f32_to_c2(circle), &poly, NULL) != 0;
}

LM2_API bool lm2_collide_aabb_to_aabb_f32(lm2_r2f32 a, lm2_r2f32 b) {
  return c2AABBtoAABB(lm2_r2f32_to_c2(a), lm2_r2f32_to_c2(b)) != 0;
}

LM2_API bool lm2_collide_aabb_to_capsule_f32(lm2_r2f32 aabb, lm2_capsule2_f32 capsule) {
  return c2AABBtoCapsule(lm2_r2f32_to_c2(aabb), lm2_capsule2_f32_to_c2(capsule)) != 0;
}

LM2_API bool lm2_collide_aabb_to_polygon_f32(lm2_r2f32 aabb, lm2_polygon_f32 polygon) {
  c2Poly poly = lm2_polygon_f32_to_c2(polygon);
  return c2AABBtoPoly(lm2_r2f32_to_c2(aabb), &poly, NULL) != 0;
}

LM2_API bool lm2_collide_capsule_to_capsule_f32(lm2_capsule2_f32 a, lm2_capsule2_f32 b) {
  return c2CapsuletoCapsule(lm2_capsule2_f32_to_c2(a), lm2_capsule2_f32_to_c2(b)) != 0;
}

LM2_API bool lm2_collide_capsule_to_polygon_f32(lm2_capsule2_f32 capsule, lm2_polygon_f32 polygon) {
  c2Poly poly = lm2_polygon_f32_to_c2(polygon);
  return c2CapsuletoPoly(lm2_capsule2_f32_to_c2(capsule), &poly, NULL) != 0;
}

LM2_API bool lm2_collide_polygon_to_polygon_f32(lm2_polygon_f32 a, lm2_polygon_f32 b) {
  c2Poly poly_a = lm2_polygon_f32_to_c2(a);
  c2Poly poly_b = lm2_polygon_f32_to_c2(b);
  return c2PolytoPoly(&poly_a, NULL, &poly_b, NULL) != 0;
}

// =============================================================================
// Manifold Generation - f64
// =============================================================================

LM2_API void lm2_manifold_circle_to_circle_f64(lm2_circle_f64 a, lm2_circle_f64 b, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2CircletoCircleManifold(lm2_circle_f64_to_c2(a), lm2_circle_f64_to_c2(b), &m);
  c2_manifold_to_lm2_f64(m, out_manifold);
}

LM2_API void lm2_manifold_circle_to_aabb_f64(lm2_circle_f64 circle, lm2_r2f64 aabb, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2CircletoAABBManifold(lm2_circle_f64_to_c2(circle), lm2_r2f64_to_c2(aabb), &m);
  c2_manifold_to_lm2_f64(m, out_manifold);
}

LM2_API void lm2_manifold_circle_to_capsule_f64(lm2_circle_f64 circle, lm2_capsule2_f64 capsule, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2CircletoCapsuleManifold(lm2_circle_f64_to_c2(circle), lm2_capsule2_f64_to_c2(capsule), &m);
  c2_manifold_to_lm2_f64(m, out_manifold);
}

LM2_API void lm2_manifold_circle_to_polygon_f64(lm2_circle_f64 circle, lm2_polygon_f64 polygon, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2Poly poly = lm2_polygon_f64_to_c2(polygon);
  c2CircletoPolyManifold(lm2_circle_f64_to_c2(circle), &poly, NULL, &m);
  c2_manifold_to_lm2_f64(m, out_manifold);
}

LM2_API void lm2_manifold_aabb_to_aabb_f64(lm2_r2f64 a, lm2_r2f64 b, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2AABBtoAABBManifold(lm2_r2f64_to_c2(a), lm2_r2f64_to_c2(b), &m);
  c2_manifold_to_lm2_f64(m, out_manifold);
}

LM2_API void lm2_manifold_aabb_to_capsule_f64(lm2_r2f64 aabb, lm2_capsule2_f64 capsule, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2AABBtoCapsuleManifold(lm2_r2f64_to_c2(aabb), lm2_capsule2_f64_to_c2(capsule), &m);
  c2_manifold_to_lm2_f64(m, out_manifold);
}

LM2_API void lm2_manifold_aabb_to_polygon_f64(lm2_r2f64 aabb, lm2_polygon_f64 polygon, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2Poly poly = lm2_polygon_f64_to_c2(polygon);
  c2AABBtoPolyManifold(lm2_r2f64_to_c2(aabb), &poly, NULL, &m);
  c2_manifold_to_lm2_f64(m, out_manifold);
}

LM2_API void lm2_manifold_capsule_to_capsule_f64(lm2_capsule2_f64 a, lm2_capsule2_f64 b, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2CapsuletoCapsuleManifold(lm2_capsule2_f64_to_c2(a), lm2_capsule2_f64_to_c2(b), &m);
  c2_manifold_to_lm2_f64(m, out_manifold);
}

LM2_API void lm2_manifold_capsule_to_polygon_f64(lm2_capsule2_f64 capsule, lm2_polygon_f64 polygon, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2Poly poly = lm2_polygon_f64_to_c2(polygon);
  c2CapsuletoPolyManifold(lm2_capsule2_f64_to_c2(capsule), &poly, NULL, &m);
  c2_manifold_to_lm2_f64(m, out_manifold);
}

LM2_API void lm2_manifold_polygon_to_polygon_f64(lm2_polygon_f64 a, lm2_polygon_f64 b, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2Poly poly_a = lm2_polygon_f64_to_c2(a);
  c2Poly poly_b = lm2_polygon_f64_to_c2(b);
  c2PolytoPolyManifold(&poly_a, NULL, &poly_b, NULL, &m);
  c2_manifold_to_lm2_f64(m, out_manifold);
}

// =============================================================================
// Manifold Generation - f32
// =============================================================================

LM2_API void lm2_manifold_circle_to_circle_f32(lm2_circle_f32 a, lm2_circle_f32 b, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2CircletoCircleManifold(lm2_circle_f32_to_c2(a), lm2_circle_f32_to_c2(b), &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_circle_to_aabb_f32(lm2_circle_f32 circle, lm2_r2f32 aabb, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2CircletoAABBManifold(lm2_circle_f32_to_c2(circle), lm2_r2f32_to_c2(aabb), &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_circle_to_capsule_f32(lm2_circle_f32 circle, lm2_capsule2_f32 capsule, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2CircletoCapsuleManifold(lm2_circle_f32_to_c2(circle), lm2_capsule2_f32_to_c2(capsule), &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_circle_to_polygon_f32(lm2_circle_f32 circle, lm2_polygon_f32 polygon, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2Poly poly = lm2_polygon_f32_to_c2(polygon);
  c2CircletoPolyManifold(lm2_circle_f32_to_c2(circle), &poly, NULL, &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_aabb_to_aabb_f32(lm2_r2f32 a, lm2_r2f32 b, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2AABBtoAABBManifold(lm2_r2f32_to_c2(a), lm2_r2f32_to_c2(b), &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_aabb_to_capsule_f32(lm2_r2f32 aabb, lm2_capsule2_f32 capsule, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2AABBtoCapsuleManifold(lm2_r2f32_to_c2(aabb), lm2_capsule2_f32_to_c2(capsule), &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_aabb_to_polygon_f32(lm2_r2f32 aabb, lm2_polygon_f32 polygon, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2Poly poly = lm2_polygon_f32_to_c2(polygon);
  c2AABBtoPolyManifold(lm2_r2f32_to_c2(aabb), &poly, NULL, &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_capsule_to_capsule_f32(lm2_capsule2_f32 a, lm2_capsule2_f32 b, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2CapsuletoCapsuleManifold(lm2_capsule2_f32_to_c2(a), lm2_capsule2_f32_to_c2(b), &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_capsule_to_polygon_f32(lm2_capsule2_f32 capsule, lm2_polygon_f32 polygon, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2Poly poly = lm2_polygon_f32_to_c2(polygon);
  c2CapsuletoPolyManifold(lm2_capsule2_f32_to_c2(capsule), &poly, NULL, &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_polygon_to_polygon_f32(lm2_polygon_f32 a, lm2_polygon_f32 b, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2Poly poly_a = lm2_polygon_f32_to_c2(a);
  c2Poly poly_b = lm2_polygon_f32_to_c2(b);
  c2PolytoPolyManifold(&poly_a, NULL, &poly_b, NULL, &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

// =============================================================================
// Convex Hull Generation
// =============================================================================

LM2_API int lm2_convex_hull_f64(lm2_v2f64* points, int point_count, lm2_v2f64* out_vertices, int max_vertices) {
  LM2_ASSERT(points != NULL);
  LM2_ASSERT(out_vertices != NULL);
  LM2_ASSERT(point_count >= 0);
  LM2_ASSERT(max_vertices >= 0);

  if (point_count == 0) {
    return 0;
  }

  // Convert to c2v
  c2v* temp = (c2v*)malloc(sizeof(c2v) * (size_t)point_count);
  LM2_ASSERT(temp != NULL);

  for (int i = 0; i < point_count; ++i) {
    temp[i] = lm2_v2f64_to_c2v(points[i]);
  }

  // Compute hull
  int hull_count = c2Hull(temp, point_count);

  // Convert back (up to max_vertices)
  int result_count = hull_count < max_vertices ? hull_count : max_vertices;
  for (int i = 0; i < result_count; ++i) {
    out_vertices[i] = c2v_to_lm2_v2f64(temp[i]);
  }

  free(temp);
  return result_count;
}

LM2_API int lm2_convex_hull_f32(lm2_v2f32* points, int point_count, lm2_v2f32* out_vertices, int max_vertices) {
  LM2_ASSERT(points != NULL);
  LM2_ASSERT(out_vertices != NULL);
  LM2_ASSERT(point_count >= 0);
  LM2_ASSERT(max_vertices >= 0);

  if (point_count == 0) {
    return 0;
  }

  // Convert to c2v
  c2v* temp = (c2v*)malloc(sizeof(c2v) * (size_t)point_count);
  LM2_ASSERT(temp != NULL);

  for (int i = 0; i < point_count; ++i) {
    temp[i] = lm2_v2f32_to_c2v(points[i]);
  }

  // Compute hull
  int hull_count = c2Hull(temp, point_count);

  // Convert back (up to max_vertices)
  int result_count = hull_count < max_vertices ? hull_count : max_vertices;
  for (int i = 0; i < result_count; ++i) {
    out_vertices[i] = c2v_to_lm2_v2f32(temp[i]);
  }

  free(temp);
  return result_count;
}

LM2_API void lm2_compute_normals_f64(lm2_v2f64* vertices, lm2_v2f64* out_normals, int vertex_count) {
  LM2_ASSERT(vertices != NULL);
  LM2_ASSERT(out_normals != NULL);
  LM2_ASSERT(vertex_count >= 0);

  if (vertex_count == 0) {
    return;
  }

  // Convert to c2v
  c2v* temp_verts = (c2v*)malloc(sizeof(c2v) * (size_t)vertex_count);
  c2v* temp_norms = (c2v*)malloc(sizeof(c2v) * (size_t)vertex_count);
  LM2_ASSERT(temp_verts != NULL && temp_norms != NULL);

  for (int i = 0; i < vertex_count; ++i) {
    temp_verts[i] = lm2_v2f64_to_c2v(vertices[i]);
  }

  // Compute normals
  c2Norms(temp_verts, temp_norms, vertex_count);

  // Convert back
  for (int i = 0; i < vertex_count; ++i) {
    out_normals[i] = c2v_to_lm2_v2f64(temp_norms[i]);
  }

  free(temp_verts);
  free(temp_norms);
}

LM2_API void lm2_compute_normals_f32(lm2_v2f32* vertices, lm2_v2f32* out_normals, int vertex_count) {
  LM2_ASSERT(vertices != NULL);
  LM2_ASSERT(out_normals != NULL);
  LM2_ASSERT(vertex_count >= 0);

  if (vertex_count == 0) {
    return;
  }

  // Convert to c2v
  c2v* temp_verts = (c2v*)malloc(sizeof(c2v) * (size_t)vertex_count);
  c2v* temp_norms = (c2v*)malloc(sizeof(c2v) * (size_t)vertex_count);
  LM2_ASSERT(temp_verts != NULL && temp_norms != NULL);

  for (int i = 0; i < vertex_count; ++i) {
    temp_verts[i] = lm2_v2f32_to_c2v(vertices[i]);
  }

  // Compute normals
  c2Norms(temp_verts, temp_norms, vertex_count);

  // Convert back
  for (int i = 0; i < vertex_count; ++i) {
    out_normals[i] = c2v_to_lm2_v2f32(temp_norms[i]);
  }

  free(temp_verts);
  free(temp_norms);
}

LM2_API void lm2_make_convex_polygon_f64(lm2_polygon_f64* polygon, lm2_v2f64* out_normals) {
  LM2_ASSERT(polygon != NULL);
  LM2_ASSERT(polygon->vertices != NULL);
  LM2_ASSERT(out_normals != NULL);

  // Convert to c2v
  c2v* temp_verts = (c2v*)malloc(sizeof(c2v) * polygon->vertex_count);
  c2v* temp_norms = (c2v*)malloc(sizeof(c2v) * polygon->vertex_count);
  LM2_ASSERT(temp_verts != NULL && temp_norms != NULL);

  for (size_t i = 0; i < polygon->vertex_count; ++i) {
    temp_verts[i] = lm2_v2f64_to_c2v(polygon->vertices[i]);
  }

  // Compute hull
  int hull_count = c2Hull(temp_verts, (int)polygon->vertex_count);

  // Compute normals
  c2Norms(temp_verts, temp_norms, hull_count);

  // Convert back
  for (int i = 0; i < hull_count; ++i) {
    polygon->vertices[i] = c2v_to_lm2_v2f64(temp_verts[i]);
    out_normals[i] = c2v_to_lm2_v2f64(temp_norms[i]);
  }

  polygon->vertex_count = (size_t)hull_count;

  free(temp_verts);
  free(temp_norms);
}

LM2_API void lm2_make_convex_polygon_f32(lm2_polygon_f32* polygon, lm2_v2f32* out_normals) {
  LM2_ASSERT(polygon != NULL);
  LM2_ASSERT(polygon->vertices != NULL);
  LM2_ASSERT(out_normals != NULL);

  // Convert to c2v
  c2v* temp_verts = (c2v*)malloc(sizeof(c2v) * polygon->vertex_count);
  c2v* temp_norms = (c2v*)malloc(sizeof(c2v) * polygon->vertex_count);
  LM2_ASSERT(temp_verts != NULL && temp_norms != NULL);

  for (size_t i = 0; i < polygon->vertex_count; ++i) {
    temp_verts[i] = lm2_v2f32_to_c2v(polygon->vertices[i]);
  }

  // Compute hull
  int hull_count = c2Hull(temp_verts, (int)polygon->vertex_count);

  // Compute normals
  c2Norms(temp_verts, temp_norms, hull_count);

  // Convert back
  for (int i = 0; i < hull_count; ++i) {
    polygon->vertices[i] = c2v_to_lm2_v2f32(temp_verts[i]);
    out_normals[i] = c2v_to_lm2_v2f32(temp_norms[i]);
  }

  polygon->vertex_count = (size_t)hull_count;

  free(temp_verts);
  free(temp_norms);
}

// =============================================================================
// Helper Functions: Triangle to Polygon conversion
// =============================================================================

static c2Poly lm2_triangle2_f64_to_c2(const lm2_triangle2_f64 tri) {
  c2Poly result;
  result.count = 3;
  result.verts[0] = lm2_v2f64_to_c2v(tri[0]);
  result.verts[1] = lm2_v2f64_to_c2v(tri[1]);
  result.verts[2] = lm2_v2f64_to_c2v(tri[2]);
  c2Norms(result.verts, result.norms, result.count);
  return result;
}

static c2Poly lm2_triangle2_f32_to_c2(const lm2_triangle2_f32 tri) {
  c2Poly result;
  result.count = 3;
  result.verts[0] = lm2_v2f32_to_c2v(tri[0]);
  result.verts[1] = lm2_v2f32_to_c2v(tri[1]);
  result.verts[2] = lm2_v2f32_to_c2v(tri[2]);
  c2Norms(result.verts, result.norms, result.count);
  return result;
}

// =============================================================================
// Triangle Collision Detection - f64
// =============================================================================

LM2_API bool lm2_collide_triangle_to_triangle_f64(const lm2_triangle2_f64 a, const lm2_triangle2_f64 b) {
  c2Poly poly_a = lm2_triangle2_f64_to_c2(a);
  c2Poly poly_b = lm2_triangle2_f64_to_c2(b);
  return c2PolytoPoly(&poly_a, NULL, &poly_b, NULL) != 0;
}

LM2_API bool lm2_collide_triangle_to_circle_f64(const lm2_triangle2_f64 tri, lm2_circle_f64 circle) {
  c2Poly poly = lm2_triangle2_f64_to_c2(tri);
  return c2CircletoPoly(lm2_circle_f64_to_c2(circle), &poly, NULL) != 0;
}

LM2_API bool lm2_collide_triangle_to_aabb_f64(const lm2_triangle2_f64 tri, lm2_r2f64 aabb) {
  c2Poly poly = lm2_triangle2_f64_to_c2(tri);
  return c2AABBtoPoly(lm2_r2f64_to_c2(aabb), &poly, NULL) != 0;
}

LM2_API bool lm2_collide_triangle_to_capsule_f64(const lm2_triangle2_f64 tri, lm2_capsule2_f64 capsule) {
  c2Poly poly = lm2_triangle2_f64_to_c2(tri);
  return c2CapsuletoPoly(lm2_capsule2_f64_to_c2(capsule), &poly, NULL) != 0;
}

LM2_API bool lm2_collide_triangle_to_polygon_f64(const lm2_triangle2_f64 tri, lm2_polygon_f64 polygon) {
  c2Poly poly_tri = lm2_triangle2_f64_to_c2(tri);
  c2Poly poly = lm2_polygon_f64_to_c2(polygon);
  return c2PolytoPoly(&poly_tri, NULL, &poly, NULL) != 0;
}

// =============================================================================
// Triangle Collision Detection - f32
// =============================================================================

LM2_API bool lm2_collide_triangle_to_triangle_f32(const lm2_triangle2_f32 a, const lm2_triangle2_f32 b) {
  c2Poly poly_a = lm2_triangle2_f32_to_c2(a);
  c2Poly poly_b = lm2_triangle2_f32_to_c2(b);
  return c2PolytoPoly(&poly_a, NULL, &poly_b, NULL) != 0;
}

LM2_API bool lm2_collide_triangle_to_circle_f32(const lm2_triangle2_f32 tri, lm2_circle_f32 circle) {
  c2Poly poly = lm2_triangle2_f32_to_c2(tri);
  return c2CircletoPoly(lm2_circle_f32_to_c2(circle), &poly, NULL) != 0;
}

LM2_API bool lm2_collide_triangle_to_aabb_f32(const lm2_triangle2_f32 tri, lm2_r2f32 aabb) {
  c2Poly poly = lm2_triangle2_f32_to_c2(tri);
  return c2AABBtoPoly(lm2_r2f32_to_c2(aabb), &poly, NULL) != 0;
}

LM2_API bool lm2_collide_triangle_to_capsule_f32(const lm2_triangle2_f32 tri, lm2_capsule2_f32 capsule) {
  c2Poly poly = lm2_triangle2_f32_to_c2(tri);
  return c2CapsuletoPoly(lm2_capsule2_f32_to_c2(capsule), &poly, NULL) != 0;
}

LM2_API bool lm2_collide_triangle_to_polygon_f32(const lm2_triangle2_f32 tri, lm2_polygon_f32 polygon) {
  c2Poly poly_tri = lm2_triangle2_f32_to_c2(tri);
  c2Poly poly = lm2_polygon_f32_to_c2(polygon);
  return c2PolytoPoly(&poly_tri, NULL, &poly, NULL) != 0;
}

// =============================================================================
// Triangle Manifold Generation - f64
// =============================================================================

LM2_API void lm2_manifold_triangle_to_triangle_f64(const lm2_triangle2_f64 a, const lm2_triangle2_f64 b, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2Poly poly_a = lm2_triangle2_f64_to_c2(a);
  c2Poly poly_b = lm2_triangle2_f64_to_c2(b);
  c2PolytoPolyManifold(&poly_a, NULL, &poly_b, NULL, &m);
  c2_manifold_to_lm2_f64(m, out_manifold);
}

LM2_API void lm2_manifold_triangle_to_circle_f64(const lm2_triangle2_f64 tri, lm2_circle_f64 circle, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2Poly poly = lm2_triangle2_f64_to_c2(tri);
  c2CircletoPolyManifold(lm2_circle_f64_to_c2(circle), &poly, NULL, &m);
  c2_manifold_to_lm2_f64(m, out_manifold);
}

LM2_API void lm2_manifold_triangle_to_aabb_f64(const lm2_triangle2_f64 tri, lm2_r2f64 aabb, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2Poly poly = lm2_triangle2_f64_to_c2(tri);
  c2AABBtoPolyManifold(lm2_r2f64_to_c2(aabb), &poly, NULL, &m);
  c2_manifold_to_lm2_f64(m, out_manifold);
}

LM2_API void lm2_manifold_triangle_to_capsule_f64(const lm2_triangle2_f64 tri, lm2_capsule2_f64 capsule, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2Poly poly = lm2_triangle2_f64_to_c2(tri);
  c2CapsuletoPolyManifold(lm2_capsule2_f64_to_c2(capsule), &poly, NULL, &m);
  c2_manifold_to_lm2_f64(m, out_manifold);
}

LM2_API void lm2_manifold_triangle_to_polygon_f64(const lm2_triangle2_f64 tri, lm2_polygon_f64 polygon, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2Poly poly_tri = lm2_triangle2_f64_to_c2(tri);
  c2Poly poly = lm2_polygon_f64_to_c2(polygon);
  c2PolytoPolyManifold(&poly_tri, NULL, &poly, NULL, &m);
  c2_manifold_to_lm2_f64(m, out_manifold);
}

// =============================================================================
// Triangle Manifold Generation - f32
// =============================================================================

LM2_API void lm2_manifold_triangle_to_triangle_f32(const lm2_triangle2_f32 a, const lm2_triangle2_f32 b, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2Poly poly_a = lm2_triangle2_f32_to_c2(a);
  c2Poly poly_b = lm2_triangle2_f32_to_c2(b);
  c2PolytoPolyManifold(&poly_a, NULL, &poly_b, NULL, &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_triangle_to_circle_f32(const lm2_triangle2_f32 tri, lm2_circle_f32 circle, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2Poly poly = lm2_triangle2_f32_to_c2(tri);
  c2CircletoPolyManifold(lm2_circle_f32_to_c2(circle), &poly, NULL, &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_triangle_to_aabb_f32(const lm2_triangle2_f32 tri, lm2_r2f32 aabb, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2Poly poly = lm2_triangle2_f32_to_c2(tri);
  c2AABBtoPolyManifold(lm2_r2f32_to_c2(aabb), &poly, NULL, &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_triangle_to_capsule_f32(const lm2_triangle2_f32 tri, lm2_capsule2_f32 capsule, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2Poly poly = lm2_triangle2_f32_to_c2(tri);
  c2CapsuletoPolyManifold(lm2_capsule2_f32_to_c2(capsule), &poly, NULL, &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_triangle_to_polygon_f32(const lm2_triangle2_f32 tri, lm2_polygon_f32 polygon, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2Poly poly_tri = lm2_triangle2_f32_to_c2(tri);
  c2Poly poly = lm2_polygon_f32_to_c2(polygon);
  c2PolytoPolyManifold(&poly_tri, NULL, &poly, NULL, &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}
