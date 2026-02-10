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
#include "lm2_c2_utils.h"

// =============================================================================
// Vector Conversions
// =============================================================================

c2v lm22_f32_to_c2v(lm2_v2_f32 v) {
  c2v result;
  result.x = v.x;
  result.y = v.y;
  return result;
}

c2v lm22_f64_to_c2v(lm2_v2_f64 v) {
  c2v result;
  result.x = (float)v.x;
  result.y = (float)v.y;
  return result;
}

lm2_v2_f32 c2v_to_lm22_f32(c2v v) {
  lm2_v2_f32 result;
  result.x = v.x;
  result.y = v.y;
  return result;
}

lm2_v2_f64 c2v_to_lm22_f64(c2v v) {
  lm2_v2_f64 result;
  result.x = (double)v.x;
  result.y = (double)v.y;
  return result;
}

// =============================================================================
// Shape Conversions
// =============================================================================

c2Ray lm2_ray2_f32_to_c2(lm2_ray2_f32 ray) {
  c2Ray result;
  result.p = lm22_f32_to_c2v(ray.origin);
  result.d = lm22_f32_to_c2v(ray.direction);
  result.t = ray.t_max;
  return result;
}

c2Ray lm2_ray2_f64_to_c2(lm2_ray2_f64 ray) {
  c2Ray result;
  result.p = lm22_f64_to_c2v(ray.origin);
  result.d = lm22_f64_to_c2v(ray.direction);
  result.t = (float)ray.t_max;
  return result;
}

c2Circle lm2_circle_f32_to_c2(lm2_circle_f32 circle) {
  c2Circle result;
  result.p = lm22_f32_to_c2v(circle.center);
  result.r = circle.radius;
  return result;
}

c2Circle lm2_circle_f64_to_c2(lm2_circle_f64 circle) {
  c2Circle result;
  result.p = lm22_f64_to_c2v(circle.center);
  result.r = (float)circle.radius;
  return result;
}

c2AABB lm2_r2_f32_to_c2(lm2_r2_f32 aabb) {
  c2AABB result;
  result.min = lm22_f32_to_c2v(aabb.min);
  result.max = lm22_f32_to_c2v(aabb.max);
  return result;
}

c2AABB lm2_r2_f64_to_c2(lm2_r2_f64 aabb) {
  c2AABB result;
  result.min = lm22_f64_to_c2v(aabb.min);
  result.max = lm22_f64_to_c2v(aabb.max);
  return result;
}

c2Capsule lm2_capsule2_f32_to_c2(lm2_capsule2_f32 capsule) {
  c2Capsule result;
  result.a = lm22_f32_to_c2v(capsule.start);
  result.b = lm22_f32_to_c2v(capsule.end);
  result.r = capsule.radius;
  return result;
}

c2Capsule lm2_capsule2_f64_to_c2(lm2_capsule2_f64 capsule) {
  c2Capsule result;
  result.a = lm22_f64_to_c2v(capsule.start);
  result.b = lm22_f64_to_c2v(capsule.end);
  result.r = (float)capsule.radius;
  return result;
}

c2Poly lm2_polygon_f32_to_c2(lm2_polygon_f32 polygon) {
  c2Poly result;
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count <= C2_MAX_POLYGON_VERTS);

  result.count = (int)polygon.vertex_count;
  for (size_t i = 0; i < polygon.vertex_count && i < C2_MAX_POLYGON_VERTS; ++i) {
    result.verts[i] = lm22_f32_to_c2v(polygon.vertices[i]);
  }

  // Compute normals
  c2Norms(result.verts, result.norms, result.count);

  return result;
}

c2Poly lm2_polygon_f64_to_c2(lm2_polygon_f64 polygon) {
  c2Poly result;
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count <= C2_MAX_POLYGON_VERTS);

  result.count = (int)polygon.vertex_count;
  for (size_t i = 0; i < polygon.vertex_count && i < C2_MAX_POLYGON_VERTS; ++i) {
    result.verts[i] = lm22_f64_to_c2v(polygon.vertices[i]);
  }

  // Compute normals
  c2Norms(result.verts, result.norms, result.count);

  return result;
}

c2Poly lm2_triangle2_f32_to_c2(const lm2_triangle2_f32 tri) {
  c2Poly result;
  result.count = 3;
  result.verts[0] = lm22_f32_to_c2v(tri[0]);
  result.verts[1] = lm22_f32_to_c2v(tri[1]);
  result.verts[2] = lm22_f32_to_c2v(tri[2]);
  c2Norms(result.verts, result.norms, result.count);
  return result;
}

c2Poly lm2_triangle2_f64_to_c2(const lm2_triangle2_f64 tri) {
  c2Poly result;
  result.count = 3;
  result.verts[0] = lm22_f64_to_c2v(tri[0]);
  result.verts[1] = lm22_f64_to_c2v(tri[1]);
  result.verts[2] = lm22_f64_to_c2v(tri[2]);
  c2Norms(result.verts, result.norms, result.count);
  return result;
}

// =============================================================================
// Manifold Conversions
// =============================================================================

void c2_manifold_to_lm2_f32(c2Manifold m, lm2_manifold_f32* out) {
  LM2_ASSERT(out != NULL);

  out->count = m.count;
  out->normal = c2v_to_lm22_f32(m.n);

  for (int i = 0; i < m.count; ++i) {
    out->depths[i] = m.depths[i];
    out->contact_points[i] = c2v_to_lm22_f32(m.contact_points[i]);
  }
}

void c2_manifold_to_lm2_f64(c2Manifold m, lm2_manifold_f64* out) {
  LM2_ASSERT(out != NULL);

  out->count = m.count;
  out->normal = c2v_to_lm22_f64(m.n);

  for (int i = 0; i < m.count; ++i) {
    out->depths[i] = (double)m.depths[i];
    out->contact_points[i] = c2v_to_lm22_f64(m.contact_points[i]);
  }
}
