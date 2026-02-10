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

#include "lm2_c2_utils.h"
#include "lm2/geometry2d/lm2_manifold2.h"
#include "lm2/geometry2d/lm2_plane2.h"
#include "lm2/geometry2d/lm2_shape2.h"
#include "lm2/scalar/lm2_safe_ops.h"
#include "lm2/scalar/lm2_scalar.h"
#include "lm2/vectors/lm2_vector_specifics.h"

#include <string.h>

// =============================================================================
// Boolean Collision Detection - f64
// =============================================================================

LM2_API bool lm2_collide_circle_to_circle_f64(lm2_circle_f64 a, lm2_circle_f64 b) {
  return c2CircletoCircle(lm2_circle_f64_to_c2(a), lm2_circle_f64_to_c2(b)) != 0;
}

LM2_API bool lm2_collide_circle_to_aabb_f64(lm2_circle_f64 circle, lm2_r2_f64 aabb) {
  return c2CircletoAABB(lm2_circle_f64_to_c2(circle), lm2_r2_f64_to_c2(aabb)) != 0;
}

LM2_API bool lm2_collide_circle_to_capsule_f64(lm2_circle_f64 circle, lm2_capsule2_f64 capsule) {
  return c2CircletoCapsule(lm2_circle_f64_to_c2(circle), lm2_capsule2_f64_to_c2(capsule)) != 0;
}

LM2_API bool lm2_collide_circle_to_polygon_f64(lm2_circle_f64 circle, lm2_polygon_f64 polygon) {
  c2Poly poly = lm2_polygon_f64_to_c2(polygon);
  return c2CircletoPoly(lm2_circle_f64_to_c2(circle), &poly, NULL) != 0;
}

LM2_API bool lm2_collide_aabb_to_aabb_f64(lm2_r2_f64 a, lm2_r2_f64 b) {
  return c2AABBtoAABB(lm2_r2_f64_to_c2(a), lm2_r2_f64_to_c2(b)) != 0;
}

LM2_API bool lm2_collide_aabb_to_capsule_f64(lm2_r2_f64 aabb, lm2_capsule2_f64 capsule) {
  return c2AABBtoCapsule(lm2_r2_f64_to_c2(aabb), lm2_capsule2_f64_to_c2(capsule)) != 0;
}

LM2_API bool lm2_collide_aabb_to_polygon_f64(lm2_r2_f64 aabb, lm2_polygon_f64 polygon) {
  c2Poly poly = lm2_polygon_f64_to_c2(polygon);
  return c2AABBtoPoly(lm2_r2_f64_to_c2(aabb), &poly, NULL) != 0;
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

LM2_API bool lm2_collide_circle_to_aabb_f32(lm2_circle_f32 circle, lm2_r2_f32 aabb) {
  return c2CircletoAABB(lm2_circle_f32_to_c2(circle), lm2_r2_f32_to_c2(aabb)) != 0;
}

LM2_API bool lm2_collide_circle_to_capsule_f32(lm2_circle_f32 circle, lm2_capsule2_f32 capsule) {
  return c2CircletoCapsule(lm2_circle_f32_to_c2(circle), lm2_capsule2_f32_to_c2(capsule)) != 0;
}

LM2_API bool lm2_collide_circle_to_polygon_f32(lm2_circle_f32 circle, lm2_polygon_f32 polygon) {
  c2Poly poly = lm2_polygon_f32_to_c2(polygon);
  return c2CircletoPoly(lm2_circle_f32_to_c2(circle), &poly, NULL) != 0;
}

LM2_API bool lm2_collide_aabb_to_aabb_f32(lm2_r2_f32 a, lm2_r2_f32 b) {
  return c2AABBtoAABB(lm2_r2_f32_to_c2(a), lm2_r2_f32_to_c2(b)) != 0;
}

LM2_API bool lm2_collide_aabb_to_capsule_f32(lm2_r2_f32 aabb, lm2_capsule2_f32 capsule) {
  return c2AABBtoCapsule(lm2_r2_f32_to_c2(aabb), lm2_capsule2_f32_to_c2(capsule)) != 0;
}

LM2_API bool lm2_collide_aabb_to_polygon_f32(lm2_r2_f32 aabb, lm2_polygon_f32 polygon) {
  c2Poly poly = lm2_polygon_f32_to_c2(polygon);
  return c2AABBtoPoly(lm2_r2_f32_to_c2(aabb), &poly, NULL) != 0;
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

LM2_API void lm2_manifold_circle_to_aabb_f64(lm2_circle_f64 circle, lm2_r2_f64 aabb, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2CircletoAABBManifold(lm2_circle_f64_to_c2(circle), lm2_r2_f64_to_c2(aabb), &m);
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

LM2_API void lm2_manifold_aabb_to_aabb_f64(lm2_r2_f64 a, lm2_r2_f64 b, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2AABBtoAABBManifold(lm2_r2_f64_to_c2(a), lm2_r2_f64_to_c2(b), &m);
  c2_manifold_to_lm2_f64(m, out_manifold);
}

LM2_API void lm2_manifold_aabb_to_capsule_f64(lm2_r2_f64 aabb, lm2_capsule2_f64 capsule, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2AABBtoCapsuleManifold(lm2_r2_f64_to_c2(aabb), lm2_capsule2_f64_to_c2(capsule), &m);
  c2_manifold_to_lm2_f64(m, out_manifold);
}

LM2_API void lm2_manifold_aabb_to_polygon_f64(lm2_r2_f64 aabb, lm2_polygon_f64 polygon, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2Poly poly = lm2_polygon_f64_to_c2(polygon);
  c2AABBtoPolyManifold(lm2_r2_f64_to_c2(aabb), &poly, NULL, &m);
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

LM2_API void lm2_manifold_circle_to_aabb_f32(lm2_circle_f32 circle, lm2_r2_f32 aabb, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2CircletoAABBManifold(lm2_circle_f32_to_c2(circle), lm2_r2_f32_to_c2(aabb), &m);
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

LM2_API void lm2_manifold_aabb_to_aabb_f32(lm2_r2_f32 a, lm2_r2_f32 b, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2AABBtoAABBManifold(lm2_r2_f32_to_c2(a), lm2_r2_f32_to_c2(b), &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_aabb_to_capsule_f32(lm2_r2_f32 aabb, lm2_capsule2_f32 capsule, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2AABBtoCapsuleManifold(lm2_r2_f32_to_c2(aabb), lm2_capsule2_f32_to_c2(capsule), &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_aabb_to_polygon_f32(lm2_r2_f32 aabb, lm2_polygon_f32 polygon, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2Poly poly = lm2_polygon_f32_to_c2(polygon);
  c2AABBtoPolyManifold(lm2_r2_f32_to_c2(aabb), &poly, NULL, &m);
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

LM2_API int lm2_convex_hull_f64(lm2_v2_f64* points, int point_count, lm2_v2_f64* out_vertices, int max_vertices) {
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
    temp[i] = lm22_f64_to_c2v(points[i]);
  }

  // Compute hull
  int hull_count = c2Hull(temp, point_count);

  // Convert back (up to max_vertices)
  int result_count = hull_count < max_vertices ? hull_count : max_vertices;
  for (int i = 0; i < result_count; ++i) {
    out_vertices[i] = c2v_to_lm22_f64(temp[i]);
  }

  free(temp);
  return result_count;
}

LM2_API int lm2_convex_hull_f32(lm2_v2_f32* points, int point_count, lm2_v2_f32* out_vertices, int max_vertices) {
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
    temp[i] = lm22_f32_to_c2v(points[i]);
  }

  // Compute hull
  int hull_count = c2Hull(temp, point_count);

  // Convert back (up to max_vertices)
  int result_count = hull_count < max_vertices ? hull_count : max_vertices;
  for (int i = 0; i < result_count; ++i) {
    out_vertices[i] = c2v_to_lm22_f32(temp[i]);
  }

  free(temp);
  return result_count;
}

LM2_API void lm2_compute_normals_f64(lm2_v2_f64* vertices, lm2_v2_f64* out_normals, int vertex_count) {
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
    temp_verts[i] = lm22_f64_to_c2v(vertices[i]);
  }

  // Compute normals
  c2Norms(temp_verts, temp_norms, vertex_count);

  // Convert back
  for (int i = 0; i < vertex_count; ++i) {
    out_normals[i] = c2v_to_lm22_f64(temp_norms[i]);
  }

  free(temp_verts);
  free(temp_norms);
}

LM2_API void lm2_compute_normals_f32(lm2_v2_f32* vertices, lm2_v2_f32* out_normals, int vertex_count) {
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
    temp_verts[i] = lm22_f32_to_c2v(vertices[i]);
  }

  // Compute normals
  c2Norms(temp_verts, temp_norms, vertex_count);

  // Convert back
  for (int i = 0; i < vertex_count; ++i) {
    out_normals[i] = c2v_to_lm22_f32(temp_norms[i]);
  }

  free(temp_verts);
  free(temp_norms);
}

LM2_API void lm2_make_convex_polygon_f64(lm2_polygon_f64* polygon, lm2_v2_f64* out_normals) {
  LM2_ASSERT(polygon != NULL);
  LM2_ASSERT(polygon->vertices != NULL);
  LM2_ASSERT(out_normals != NULL);

  // Convert to c2v
  c2v* temp_verts = (c2v*)malloc(sizeof(c2v) * polygon->vertex_count);
  c2v* temp_norms = (c2v*)malloc(sizeof(c2v) * polygon->vertex_count);
  LM2_ASSERT(temp_verts != NULL && temp_norms != NULL);

  for (size_t i = 0; i < polygon->vertex_count; ++i) {
    temp_verts[i] = lm22_f64_to_c2v(polygon->vertices[i]);
  }

  // Compute hull
  int hull_count = c2Hull(temp_verts, (int)polygon->vertex_count);

  // Compute normals
  c2Norms(temp_verts, temp_norms, hull_count);

  // Convert back
  for (int i = 0; i < hull_count; ++i) {
    polygon->vertices[i] = c2v_to_lm22_f64(temp_verts[i]);
    out_normals[i] = c2v_to_lm22_f64(temp_norms[i]);
  }

  polygon->vertex_count = (size_t)hull_count;

  free(temp_verts);
  free(temp_norms);
}

LM2_API void lm2_make_convex_polygon_f32(lm2_polygon_f32* polygon, lm2_v2_f32* out_normals) {
  LM2_ASSERT(polygon != NULL);
  LM2_ASSERT(polygon->vertices != NULL);
  LM2_ASSERT(out_normals != NULL);

  // Convert to c2v
  c2v* temp_verts = (c2v*)malloc(sizeof(c2v) * polygon->vertex_count);
  c2v* temp_norms = (c2v*)malloc(sizeof(c2v) * polygon->vertex_count);
  LM2_ASSERT(temp_verts != NULL && temp_norms != NULL);

  for (size_t i = 0; i < polygon->vertex_count; ++i) {
    temp_verts[i] = lm22_f32_to_c2v(polygon->vertices[i]);
  }

  // Compute hull
  int hull_count = c2Hull(temp_verts, (int)polygon->vertex_count);

  // Compute normals
  c2Norms(temp_verts, temp_norms, hull_count);

  // Convert back
  for (int i = 0; i < hull_count; ++i) {
    polygon->vertices[i] = c2v_to_lm22_f32(temp_verts[i]);
    out_normals[i] = c2v_to_lm22_f32(temp_norms[i]);
  }

  polygon->vertex_count = (size_t)hull_count;

  free(temp_verts);
  free(temp_norms);
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

LM2_API bool lm2_collide_triangle_to_aabb_f64(const lm2_triangle2_f64 tri, lm2_r2_f64 aabb) {
  c2Poly poly = lm2_triangle2_f64_to_c2(tri);
  return c2AABBtoPoly(lm2_r2_f64_to_c2(aabb), &poly, NULL) != 0;
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

LM2_API bool lm2_collide_triangle_to_aabb_f32(const lm2_triangle2_f32 tri, lm2_r2_f32 aabb) {
  c2Poly poly = lm2_triangle2_f32_to_c2(tri);
  return c2AABBtoPoly(lm2_r2_f32_to_c2(aabb), &poly, NULL) != 0;
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

LM2_API void lm2_manifold_triangle_to_aabb_f64(const lm2_triangle2_f64 tri, lm2_r2_f64 aabb, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2Poly poly = lm2_triangle2_f64_to_c2(tri);
  c2AABBtoPolyManifold(lm2_r2_f64_to_c2(aabb), &poly, NULL, &m);
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

LM2_API void lm2_manifold_triangle_to_aabb_f32(const lm2_triangle2_f32 tri, lm2_r2_f32 aabb, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m;
  c2Poly poly = lm2_triangle2_f32_to_c2(tri);
  c2AABBtoPolyManifold(lm2_r2_f32_to_c2(aabb), &poly, NULL, &m);
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

// =============================================================================
// Plane Manifold Generation - f64
// =============================================================================

LM2_API void lm2_manifold_circle_to_plane_f64(lm2_circle_f64 circle, lm2_plane2_f64 plane, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);

  // Calculate signed distance from circle center to plane
  double dist_to_center = lm2_sub_f64(lm2_v2_dot_f64(circle.center, plane.normal), plane.distance);
  double penetration = lm2_sub_f64(circle.radius, lm2_abs_f64(dist_to_center));

  if (lm2_sub_f64(penetration, 0.0) <= 0.0) {
    // No collision
    out_manifold->count = 0;
    return;
  }

  // One contact point: circle center projected onto plane
  out_manifold->count = 1;
  out_manifold->depths[0] = penetration;
  out_manifold->normal = plane.normal;

  // Contact point is on the plane surface, in the direction of the circle center
  lm2_v2_f64 scaled_normal = lm2_v2_mul_s_f64(plane.normal, dist_to_center);
  out_manifold->contact_points[0] = lm2_v2_sub_f64(circle.center, scaled_normal);
}

LM2_API void lm2_manifold_capsule_to_plane_f64(lm2_capsule2_f64 capsule, lm2_plane2_f64 plane, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);

  // Check both endpoints of the capsule
  double dist_start = lm2_sub_f64(lm2_v2_dot_f64(capsule.start, plane.normal), plane.distance);
  double dist_end = lm2_sub_f64(lm2_v2_dot_f64(capsule.end, plane.normal), plane.distance);

  double pen_start = lm2_sub_f64(capsule.radius, lm2_abs_f64(dist_start));
  double pen_end = lm2_sub_f64(capsule.radius, lm2_abs_f64(dist_end));

  out_manifold->count = 0;
  out_manifold->normal = plane.normal;

  if (lm2_sub_f64(pen_start, 0.0) > 0.0) {
    out_manifold->depths[out_manifold->count] = pen_start;
    lm2_v2_f64 scaled_normal = lm2_v2_mul_s_f64(plane.normal, dist_start);
    out_manifold->contact_points[out_manifold->count] = lm2_v2_sub_f64(capsule.start, scaled_normal);
    out_manifold->count = lm2_add_i32(out_manifold->count, 1);
  }

  if (lm2_sub_f64(pen_end, 0.0) > 0.0 && out_manifold->count < 2) {
    out_manifold->depths[out_manifold->count] = pen_end;
    lm2_v2_f64 scaled_normal = lm2_v2_mul_s_f64(plane.normal, dist_end);
    out_manifold->contact_points[out_manifold->count] = lm2_v2_sub_f64(capsule.end, scaled_normal);
    out_manifold->count = lm2_add_i32(out_manifold->count, 1);
  }
}

LM2_API void lm2_manifold_aabb_to_plane_f64(lm2_r2_f64 aabb, lm2_plane2_f64 plane, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);

  // Get AABB corners
  lm2_v2_f64 corners[4];
  corners[0] = aabb.min;
  corners[1] = (lm2_v2_f64) {aabb.max.x, aabb.min.y};
  corners[2] = aabb.max;
  corners[3] = (lm2_v2_f64) {aabb.min.x, aabb.max.y};

  out_manifold->count = 0;
  out_manifold->normal = plane.normal;

  // Check each corner
  for (int i = 0; i < 4 && out_manifold->count < 2; i = lm2_add_i32(i, 1)) {
    double dist = lm2_sub_f64(lm2_v2_dot_f64(corners[i], plane.normal), plane.distance);
    double penetration = lm2_mul_f64(-1.0, dist);  // Negative distance means penetration

    if (lm2_sub_f64(penetration, 0.0) > 0.0) {
      out_manifold->depths[out_manifold->count] = penetration;
      out_manifold->contact_points[out_manifold->count] = corners[i];
      out_manifold->count = lm2_add_i32(out_manifold->count, 1);
    }
  }
}

LM2_API void lm2_manifold_triangle_to_plane_f64(const lm2_triangle2_f64 tri, lm2_plane2_f64 plane, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);

  lm2_v2_f64 verts[3] = {tri[0], tri[1], tri[2]};

  out_manifold->count = 0;
  out_manifold->normal = plane.normal;

  // Check each vertex
  for (int i = 0; i < 3 && out_manifold->count < 2; i = lm2_add_i32(i, 1)) {
    double dist = lm2_sub_f64(lm2_v2_dot_f64(verts[i], plane.normal), plane.distance);
    double penetration = lm2_mul_f64(-1.0, dist);

    if (lm2_sub_f64(penetration, 0.0) > 0.0) {
      out_manifold->depths[out_manifold->count] = penetration;
      out_manifold->contact_points[out_manifold->count] = verts[i];
      out_manifold->count = lm2_add_i32(out_manifold->count, 1);
    }
  }
}

LM2_API void lm2_manifold_polygon_to_plane_f64(lm2_polygon_f64 polygon, lm2_plane2_f64 plane, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  LM2_ASSERT(polygon.vertices != NULL);

  out_manifold->count = 0;
  out_manifold->normal = plane.normal;

  // Check each vertex
  for (size_t i = 0; i < polygon.vertex_count && out_manifold->count < 2; i++) {
    double dist = lm2_sub_f64(lm2_v2_dot_f64(polygon.vertices[i], plane.normal), plane.distance);
    double penetration = lm2_mul_f64(-1.0, dist);

    if (lm2_sub_f64(penetration, 0.0) > 0.0) {
      out_manifold->depths[out_manifold->count] = penetration;
      out_manifold->contact_points[out_manifold->count] = polygon.vertices[i];
      out_manifold->count = lm2_add_i32(out_manifold->count, 1);
    }
  }
}

// =============================================================================
// Plane Manifold Generation - f32
// =============================================================================

LM2_API void lm2_manifold_circle_to_plane_f32(lm2_circle_f32 circle, lm2_plane2_f32 plane, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);

  float dist_to_center = lm2_sub_f32(lm2_v2_dot_f32(circle.center, plane.normal), plane.distance);
  float penetration = lm2_sub_f32(circle.radius, lm2_abs_f32(dist_to_center));

  if (lm2_sub_f32(penetration, 0.0f) <= 0.0f) {
    out_manifold->count = 0;
    return;
  }

  out_manifold->count = 1;
  out_manifold->depths[0] = penetration;
  out_manifold->normal = plane.normal;

  lm2_v2_f32 scaled_normal = lm2_v2_mul_s_f32(plane.normal, dist_to_center);
  out_manifold->contact_points[0] = lm2_v2_sub_f32(circle.center, scaled_normal);
}

LM2_API void lm2_manifold_capsule_to_plane_f32(lm2_capsule2_f32 capsule, lm2_plane2_f32 plane, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);

  float dist_start = lm2_sub_f32(lm2_v2_dot_f32(capsule.start, plane.normal), plane.distance);
  float dist_end = lm2_sub_f32(lm2_v2_dot_f32(capsule.end, plane.normal), plane.distance);

  float pen_start = lm2_sub_f32(capsule.radius, lm2_abs_f32(dist_start));
  float pen_end = lm2_sub_f32(capsule.radius, lm2_abs_f32(dist_end));

  out_manifold->count = 0;
  out_manifold->normal = plane.normal;

  if (lm2_sub_f32(pen_start, 0.0f) > 0.0f) {
    out_manifold->depths[out_manifold->count] = pen_start;
    lm2_v2_f32 scaled_normal = lm2_v2_mul_s_f32(plane.normal, dist_start);
    out_manifold->contact_points[out_manifold->count] = lm2_v2_sub_f32(capsule.start, scaled_normal);
    out_manifold->count = lm2_add_i32(out_manifold->count, 1);
  }

  if (lm2_sub_f32(pen_end, 0.0f) > 0.0f && out_manifold->count < 2) {
    out_manifold->depths[out_manifold->count] = pen_end;
    lm2_v2_f32 scaled_normal = lm2_v2_mul_s_f32(plane.normal, dist_end);
    out_manifold->contact_points[out_manifold->count] = lm2_v2_sub_f32(capsule.end, scaled_normal);
    out_manifold->count = lm2_add_i32(out_manifold->count, 1);
  }
}

LM2_API void lm2_manifold_aabb_to_plane_f32(lm2_r2_f32 aabb, lm2_plane2_f32 plane, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);

  lm2_v2_f32 corners[4];
  corners[0] = aabb.min;
  corners[1] = (lm2_v2_f32) {aabb.max.x, aabb.min.y};
  corners[2] = aabb.max;
  corners[3] = (lm2_v2_f32) {aabb.min.x, aabb.max.y};

  out_manifold->count = 0;
  out_manifold->normal = plane.normal;

  for (int i = 0; i < 4 && out_manifold->count < 2; i = lm2_add_i32(i, 1)) {
    float dist = lm2_sub_f32(lm2_v2_dot_f32(corners[i], plane.normal), plane.distance);
    float penetration = lm2_mul_f32(-1.0f, dist);

    if (lm2_sub_f32(penetration, 0.0f) > 0.0f) {
      out_manifold->depths[out_manifold->count] = penetration;
      out_manifold->contact_points[out_manifold->count] = corners[i];
      out_manifold->count = lm2_add_i32(out_manifold->count, 1);
    }
  }
}

LM2_API void lm2_manifold_triangle_to_plane_f32(const lm2_triangle2_f32 tri, lm2_plane2_f32 plane, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);

  lm2_v2_f32 verts[3] = {tri[0], tri[1], tri[2]};

  out_manifold->count = 0;
  out_manifold->normal = plane.normal;

  for (int i = 0; i < 3 && out_manifold->count < 2; i = lm2_add_i32(i, 1)) {
    float dist = lm2_sub_f32(lm2_v2_dot_f32(verts[i], plane.normal), plane.distance);
    float penetration = lm2_mul_f32(-1.0f, dist);

    if (lm2_sub_f32(penetration, 0.0f) > 0.0f) {
      out_manifold->depths[out_manifold->count] = penetration;
      out_manifold->contact_points[out_manifold->count] = verts[i];
      out_manifold->count = lm2_add_i32(out_manifold->count, 1);
    }
  }
}

LM2_API void lm2_manifold_polygon_to_plane_f32(lm2_polygon_f32 polygon, lm2_plane2_f32 plane, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  LM2_ASSERT(polygon.vertices != NULL);

  out_manifold->count = 0;
  out_manifold->normal = plane.normal;

  for (size_t i = 0; i < polygon.vertex_count && out_manifold->count < 2; i++) {
    float dist = lm2_sub_f32(lm2_v2_dot_f32(polygon.vertices[i], plane.normal), plane.distance);
    float penetration = lm2_mul_f32(-1.0f, dist);

    if (lm2_sub_f32(penetration, 0.0f) > 0.0f) {
      out_manifold->depths[out_manifold->count] = penetration;
      out_manifold->contact_points[out_manifold->count] = polygon.vertices[i];
      out_manifold->count = lm2_add_i32(out_manifold->count, 1);
    }
  }
}

// =============================================================================
// Generic Shape Manifold Generation - f64
// =============================================================================

LM2_API void lm2_manifold_shape_to_shape_f64(lm2_shape2_f64 shape_a, lm2_shape2_f64 shape_b, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  LM2_ASSERT(shape_a.data != NULL);
  LM2_ASSERT(shape_b.data != NULL);

  // Initialize manifold to no collision
  out_manifold->count = 0;

  // Dispatch based on shape types
  switch (shape_a.type) {
    case LM2_SHAPE2_CIRCLE: {
      lm2_circle_f64* circle = (lm2_circle_f64*)shape_a.data;
      switch (shape_b.type) {
        case LM2_SHAPE2_CIRCLE:
          lm2_manifold_circle_to_circle_f64(*circle, *(lm2_circle_f64*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_CAPSULE:
          lm2_manifold_circle_to_capsule_f64(*circle, *(lm2_capsule2_f64*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_RECTANGLE: {
          lm2_rectangle2_f64* rect = (lm2_rectangle2_f64*)shape_b.data;
          lm2_manifold_circle_to_aabb_f64(*circle, *rect, out_manifold);
          break;
        }
        case LM2_SHAPE2_TRIANGLE:
          lm2_manifold_triangle_to_circle_f64(*(lm2_triangle2_f64*)shape_b.data, *circle, out_manifold);
          // Flip normal since we swapped order
          out_manifold->normal = lm2_v2_mul_s_f64(out_manifold->normal, -1.0);
          break;
        case LM2_SHAPE2_POLYGON:
          lm2_manifold_circle_to_polygon_f64(*circle, *(lm2_polygon_f64*)shape_b.data, out_manifold);
          break;
        default:
          break;
      }
      break;
    }

    case LM2_SHAPE2_CAPSULE: {
      lm2_capsule2_f64* capsule = (lm2_capsule2_f64*)shape_a.data;
      switch (shape_b.type) {
        case LM2_SHAPE2_CIRCLE:
          lm2_manifold_circle_to_capsule_f64(*(lm2_circle_f64*)shape_b.data, *capsule, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f64(out_manifold->normal, -1.0);
          break;
        case LM2_SHAPE2_CAPSULE:
          lm2_manifold_capsule_to_capsule_f64(*capsule, *(lm2_capsule2_f64*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_RECTANGLE: {
          lm2_rectangle2_f64* rect = (lm2_rectangle2_f64*)shape_b.data;
          lm2_manifold_aabb_to_capsule_f64(*rect, *capsule, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f64(out_manifold->normal, -1.0);
          break;
        }
        case LM2_SHAPE2_TRIANGLE:
          lm2_manifold_triangle_to_capsule_f64(*(lm2_triangle2_f64*)shape_b.data, *capsule, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f64(out_manifold->normal, -1.0);
          break;
        case LM2_SHAPE2_POLYGON:
          lm2_manifold_capsule_to_polygon_f64(*capsule, *(lm2_polygon_f64*)shape_b.data, out_manifold);
          break;
        default:
          break;
      }
      break;
    }

    case LM2_SHAPE2_RECTANGLE: {
      lm2_rectangle2_f64* rect = (lm2_rectangle2_f64*)shape_a.data;
      switch (shape_b.type) {
        case LM2_SHAPE2_CIRCLE:
          lm2_manifold_circle_to_aabb_f64(*(lm2_circle_f64*)shape_b.data, *rect, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f64(out_manifold->normal, -1.0);
          break;
        case LM2_SHAPE2_CAPSULE:
          lm2_manifold_aabb_to_capsule_f64(*rect, *(lm2_capsule2_f64*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_RECTANGLE: {
          lm2_rectangle2_f64* rect_b = (lm2_rectangle2_f64*)shape_b.data;
          lm2_manifold_aabb_to_aabb_f64(*rect, *rect_b, out_manifold);
          break;
        }
        case LM2_SHAPE2_TRIANGLE:
          lm2_manifold_triangle_to_aabb_f64(*(lm2_triangle2_f64*)shape_b.data, *rect, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f64(out_manifold->normal, -1.0);
          break;
        case LM2_SHAPE2_POLYGON:
          lm2_manifold_aabb_to_polygon_f64(*rect, *(lm2_polygon_f64*)shape_b.data, out_manifold);
          break;
        default:
          break;
      }
      break;
    }

    case LM2_SHAPE2_TRIANGLE: {
      lm2_triangle2_f64* tri = (lm2_triangle2_f64*)shape_a.data;
      switch (shape_b.type) {
        case LM2_SHAPE2_CIRCLE:
          lm2_manifold_triangle_to_circle_f64(*tri, *(lm2_circle_f64*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_CAPSULE:
          lm2_manifold_triangle_to_capsule_f64(*tri, *(lm2_capsule2_f64*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_RECTANGLE: {
          lm2_rectangle2_f64* rect = (lm2_rectangle2_f64*)shape_b.data;
          lm2_manifold_triangle_to_aabb_f64(*tri, *rect, out_manifold);
          break;
        }
        case LM2_SHAPE2_TRIANGLE:
          lm2_manifold_triangle_to_triangle_f64(*tri, *(lm2_triangle2_f64*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_POLYGON:
          lm2_manifold_triangle_to_polygon_f64(*tri, *(lm2_polygon_f64*)shape_b.data, out_manifold);
          break;
        default:
          break;
      }
      break;
    }

    case LM2_SHAPE2_POLYGON: {
      lm2_polygon_f64* poly = (lm2_polygon_f64*)shape_a.data;
      switch (shape_b.type) {
        case LM2_SHAPE2_CIRCLE:
          lm2_manifold_circle_to_polygon_f64(*(lm2_circle_f64*)shape_b.data, *poly, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f64(out_manifold->normal, -1.0);
          break;
        case LM2_SHAPE2_CAPSULE:
          lm2_manifold_capsule_to_polygon_f64(*(lm2_capsule2_f64*)shape_b.data, *poly, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f64(out_manifold->normal, -1.0);
          break;
        case LM2_SHAPE2_RECTANGLE: {
          lm2_rectangle2_f64* rect = (lm2_rectangle2_f64*)shape_b.data;
          lm2_manifold_aabb_to_polygon_f64(*rect, *poly, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f64(out_manifold->normal, -1.0);
          break;
        }
        case LM2_SHAPE2_TRIANGLE:
          lm2_manifold_triangle_to_polygon_f64(*(lm2_triangle2_f64*)shape_b.data, *poly, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f64(out_manifold->normal, -1.0);
          break;
        case LM2_SHAPE2_POLYGON:
          lm2_manifold_polygon_to_polygon_f64(*poly, *(lm2_polygon_f64*)shape_b.data, out_manifold);
          break;
        default:
          break;
      }
      break;
    }

    default:
      break;
  }
}

// =============================================================================
// Generic Shape Manifold Generation - f32
// =============================================================================

LM2_API void lm2_manifold_shape_to_shape_f32(lm2_shape2_f32 shape_a, lm2_shape2_f32 shape_b, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  LM2_ASSERT(shape_a.data != NULL);
  LM2_ASSERT(shape_b.data != NULL);

  out_manifold->count = 0;

  switch (shape_a.type) {
    case LM2_SHAPE2_CIRCLE: {
      lm2_circle_f32* circle = (lm2_circle_f32*)shape_a.data;
      switch (shape_b.type) {
        case LM2_SHAPE2_CIRCLE:
          lm2_manifold_circle_to_circle_f32(*circle, *(lm2_circle_f32*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_CAPSULE:
          lm2_manifold_circle_to_capsule_f32(*circle, *(lm2_capsule2_f32*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_RECTANGLE: {
          lm2_rectangle2_f32* rect = (lm2_rectangle2_f32*)shape_b.data;
          lm2_manifold_circle_to_aabb_f32(*circle, *rect, out_manifold);
          break;
        }
        case LM2_SHAPE2_TRIANGLE:
          lm2_manifold_triangle_to_circle_f32(*(lm2_triangle2_f32*)shape_b.data, *circle, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f32(out_manifold->normal, -1.0f);
          break;
        case LM2_SHAPE2_POLYGON:
          lm2_manifold_circle_to_polygon_f32(*circle, *(lm2_polygon_f32*)shape_b.data, out_manifold);
          break;
        default:
          break;
      }
      break;
    }

    case LM2_SHAPE2_CAPSULE: {
      lm2_capsule2_f32* capsule = (lm2_capsule2_f32*)shape_a.data;
      switch (shape_b.type) {
        case LM2_SHAPE2_CIRCLE:
          lm2_manifold_circle_to_capsule_f32(*(lm2_circle_f32*)shape_b.data, *capsule, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f32(out_manifold->normal, -1.0f);
          break;
        case LM2_SHAPE2_CAPSULE:
          lm2_manifold_capsule_to_capsule_f32(*capsule, *(lm2_capsule2_f32*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_RECTANGLE: {
          lm2_rectangle2_f32* rect = (lm2_rectangle2_f32*)shape_b.data;
          lm2_manifold_aabb_to_capsule_f32(*rect, *capsule, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f32(out_manifold->normal, -1.0f);
          break;
        }
        case LM2_SHAPE2_TRIANGLE:
          lm2_manifold_triangle_to_capsule_f32(*(lm2_triangle2_f32*)shape_b.data, *capsule, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f32(out_manifold->normal, -1.0f);
          break;
        case LM2_SHAPE2_POLYGON:
          lm2_manifold_capsule_to_polygon_f32(*capsule, *(lm2_polygon_f32*)shape_b.data, out_manifold);
          break;
        default:
          break;
      }
      break;
    }

    case LM2_SHAPE2_RECTANGLE: {
      lm2_rectangle2_f32* rect = (lm2_rectangle2_f32*)shape_a.data;
      switch (shape_b.type) {
        case LM2_SHAPE2_CIRCLE:
          lm2_manifold_circle_to_aabb_f32(*(lm2_circle_f32*)shape_b.data, *rect, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f32(out_manifold->normal, -1.0f);
          break;
        case LM2_SHAPE2_CAPSULE:
          lm2_manifold_aabb_to_capsule_f32(*rect, *(lm2_capsule2_f32*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_RECTANGLE: {
          lm2_rectangle2_f32* rect_b = (lm2_rectangle2_f32*)shape_b.data;
          lm2_manifold_aabb_to_aabb_f32(*rect, *rect_b, out_manifold);
          break;
        }
        case LM2_SHAPE2_TRIANGLE:
          lm2_manifold_triangle_to_aabb_f32(*(lm2_triangle2_f32*)shape_b.data, *rect, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f32(out_manifold->normal, -1.0f);
          break;
        case LM2_SHAPE2_POLYGON:
          lm2_manifold_aabb_to_polygon_f32(*rect, *(lm2_polygon_f32*)shape_b.data, out_manifold);
          break;
        default:
          break;
      }
      break;
    }

    case LM2_SHAPE2_TRIANGLE: {
      lm2_triangle2_f32* tri = (lm2_triangle2_f32*)shape_a.data;
      switch (shape_b.type) {
        case LM2_SHAPE2_CIRCLE:
          lm2_manifold_triangle_to_circle_f32(*tri, *(lm2_circle_f32*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_CAPSULE:
          lm2_manifold_triangle_to_capsule_f32(*tri, *(lm2_capsule2_f32*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_RECTANGLE: {
          lm2_rectangle2_f32* rect = (lm2_rectangle2_f32*)shape_b.data;
          lm2_manifold_triangle_to_aabb_f32(*tri, *rect, out_manifold);
          break;
        }
        case LM2_SHAPE2_TRIANGLE:
          lm2_manifold_triangle_to_triangle_f32(*tri, *(lm2_triangle2_f32*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_POLYGON:
          lm2_manifold_triangle_to_polygon_f32(*tri, *(lm2_polygon_f32*)shape_b.data, out_manifold);
          break;
        default:
          break;
      }
      break;
    }

    case LM2_SHAPE2_POLYGON: {
      lm2_polygon_f32* poly = (lm2_polygon_f32*)shape_a.data;
      switch (shape_b.type) {
        case LM2_SHAPE2_CIRCLE:
          lm2_manifold_circle_to_polygon_f32(*(lm2_circle_f32*)shape_b.data, *poly, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f32(out_manifold->normal, -1.0f);
          break;
        case LM2_SHAPE2_CAPSULE:
          lm2_manifold_capsule_to_polygon_f32(*(lm2_capsule2_f32*)shape_b.data, *poly, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f32(out_manifold->normal, -1.0f);
          break;
        case LM2_SHAPE2_RECTANGLE: {
          lm2_rectangle2_f32* rect = (lm2_rectangle2_f32*)shape_b.data;
          lm2_manifold_aabb_to_polygon_f32(*rect, *poly, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f32(out_manifold->normal, -1.0f);
          break;
        }
        case LM2_SHAPE2_TRIANGLE:
          lm2_manifold_triangle_to_polygon_f32(*(lm2_triangle2_f32*)shape_b.data, *poly, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f32(out_manifold->normal, -1.0f);
          break;
        case LM2_SHAPE2_POLYGON:
          lm2_manifold_polygon_to_polygon_f32(*poly, *(lm2_polygon_f32*)shape_b.data, out_manifold);
          break;
        default:
          break;
      }
      break;
    }

    default:
      break;
  }
}
