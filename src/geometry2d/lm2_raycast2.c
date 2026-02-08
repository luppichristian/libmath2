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

#include <cute_c2.h>

#include "lm2/geometry2d/lm2_raycast2.h"
#include "lm2/scalar/lm2_safe_ops.h"
#include "lm2/scalar/lm2_scalar.h"
#include "lm2/vectors/lm2_vector_specifics.h"

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

static c2Ray lm2_ray2_f32_to_c2(lm2_ray2_f32 ray) {
  c2Ray result;
  result.p = lm2_v2f32_to_c2v(ray.origin);
  result.d = lm2_v2f32_to_c2v(ray.direction);
  result.t = ray.t_max;
  return result;
}

static c2Ray lm2_ray2_f64_to_c2(lm2_ray2_f64 ray) {
  c2Ray result;
  result.p = lm2_v2f64_to_c2v(ray.origin);
  result.d = lm2_v2f64_to_c2v(ray.direction);
  result.t = (float)ray.t_max;
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

// =============================================================================
// 2D Ray Construction - f64
// =============================================================================

LM2_API lm2_ray2_f64 lm2_ray2_make_f64(lm2_v2f64 origin, lm2_v2f64 direction, double t_max) {
  lm2_ray2_f64 result;
  result.origin = origin;
  result.direction = direction;
  result.t_max = t_max;
  return result;
}

LM2_API lm2_ray2_f64 lm2_ray2_from_points_f64(lm2_v2f64 start, lm2_v2f64 end) {
  lm2_ray2_f64 result;
  result.origin = start;
  lm2_v2f64 diff = lm2_sub_lm2_v2f64(end, start);
  double length = lm2_length_v2f64(diff);
  result.direction = lm2_normalize_v2f64(diff);
  result.t_max = length;
  return result;
}

LM2_API lm2_v2f64 lm2_ray2_point_at_f64(lm2_ray2_f64 ray, double t) {
  lm2_v2f64 scaled_dir = lm2_mul_lm2_v2f64_double(ray.direction, t);
  return lm2_add_lm2_v2f64(ray.origin, scaled_dir);
}

// =============================================================================
// 2D Ray Construction - f32
// =============================================================================

LM2_API lm2_ray2_f32 lm2_ray2_make_f32(lm2_v2f32 origin, lm2_v2f32 direction, float t_max) {
  lm2_ray2_f32 result;
  result.origin = origin;
  result.direction = direction;
  result.t_max = t_max;
  return result;
}

LM2_API lm2_ray2_f32 lm2_ray2_from_points_f32(lm2_v2f32 start, lm2_v2f32 end) {
  lm2_ray2_f32 result;
  result.origin = start;
  lm2_v2f32 diff = lm2_sub_lm2_v2f32(end, start);
  float length = lm2_length_v2f32(diff);
  result.direction = lm2_normalize_v2f32(diff);
  result.t_max = length;
  return result;
}

LM2_API lm2_v2f32 lm2_ray2_point_at_f32(lm2_ray2_f32 ray, float t) {
  lm2_v2f32 scaled_dir = lm2_mul_lm2_v2f32_float(ray.direction, t);
  return lm2_add_lm2_v2f32(ray.origin, scaled_dir);
}

// =============================================================================
// 2D Ray vs Primitive Tests - f64
// =============================================================================

LM2_API lm2_rayhit2_f64 lm2_raycast_circle_f64(lm2_ray2_f64 ray, lm2_circle_f64 circle) {
  lm2_rayhit2_f64 result;
  c2Raycast hit;
  c2Ray c2_ray = lm2_ray2_f64_to_c2(ray);
  c2Circle c2_circle = lm2_circle_f64_to_c2(circle);

  int did_hit = c2RaytoCircle(c2_ray, c2_circle, &hit);
  result.hit = did_hit != 0;

  if (result.hit) {
    result.t = (double)hit.t;
    result.normal = c2v_to_lm2_v2f64(hit.n);
    result.point = lm2_ray2_point_at_f64(ray, result.t);
  } else {
    result.t = 0.0;
    result.normal = (lm2_v2f64) {0.0, 0.0};
    result.point = (lm2_v2f64) {0.0, 0.0};
  }

  return result;
}

LM2_API lm2_rayhit2_f64 lm2_raycast_aabb_f64(lm2_ray2_f64 ray, lm2_r2f64 aabb) {
  lm2_rayhit2_f64 result;
  c2Raycast hit;
  c2Ray c2_ray = lm2_ray2_f64_to_c2(ray);
  c2AABB c2_aabb = lm2_r2f64_to_c2(aabb);

  int did_hit = c2RaytoAABB(c2_ray, c2_aabb, &hit);
  result.hit = did_hit != 0;

  if (result.hit) {
    result.t = (double)hit.t;
    result.normal = c2v_to_lm2_v2f64(hit.n);
    result.point = lm2_ray2_point_at_f64(ray, result.t);
  } else {
    result.t = 0.0;
    result.normal = (lm2_v2f64) {0.0, 0.0};
    result.point = (lm2_v2f64) {0.0, 0.0};
  }

  return result;
}

LM2_API lm2_rayhit2_f64 lm2_raycast_capsule_f64(lm2_ray2_f64 ray, lm2_capsule2_f64 capsule) {
  lm2_rayhit2_f64 result;
  c2Raycast hit;
  c2Ray c2_ray = lm2_ray2_f64_to_c2(ray);
  c2Capsule c2_capsule = lm2_capsule2_f64_to_c2(capsule);

  int did_hit = c2RaytoCapsule(c2_ray, c2_capsule, &hit);
  result.hit = did_hit != 0;

  if (result.hit) {
    result.t = (double)hit.t;
    result.normal = c2v_to_lm2_v2f64(hit.n);
    result.point = lm2_ray2_point_at_f64(ray, result.t);
  } else {
    result.t = 0.0;
    result.normal = (lm2_v2f64) {0.0, 0.0};
    result.point = (lm2_v2f64) {0.0, 0.0};
  }

  return result;
}

LM2_API lm2_rayhit2_f64 lm2_raycast_polygon_f64(lm2_ray2_f64 ray, lm2_polygon_f64 polygon) {
  lm2_rayhit2_f64 result;
  c2Raycast hit;
  c2Ray c2_ray = lm2_ray2_f64_to_c2(ray);
  c2Poly c2_poly = lm2_polygon_f64_to_c2(polygon);

  int did_hit = c2RaytoPoly(c2_ray, &c2_poly, NULL, &hit);
  result.hit = did_hit != 0;

  if (result.hit) {
    result.t = (double)hit.t;
    result.normal = c2v_to_lm2_v2f64(hit.n);
    result.point = lm2_ray2_point_at_f64(ray, result.t);
  } else {
    result.t = 0.0;
    result.normal = (lm2_v2f64) {0.0, 0.0};
    result.point = (lm2_v2f64) {0.0, 0.0};
  }

  return result;
}

LM2_API lm2_rayhit2_f64 lm2_raycast_segment_f64(lm2_ray2_f64 ray, lm2_v2f64 segment_start, lm2_v2f64 segment_end) {
  // Convert segment to capsule with zero radius
  lm2_capsule2_f64 capsule;
  capsule.start = segment_start;
  capsule.end = segment_end;
  capsule.radius = 0.0;

  return lm2_raycast_capsule_f64(ray, capsule);
}

// =============================================================================
// 2D Ray vs Primitive Tests - f32
// =============================================================================

LM2_API lm2_rayhit2_f32 lm2_raycast_circle_f32(lm2_ray2_f32 ray, lm2_circle_f32 circle) {
  lm2_rayhit2_f32 result;
  c2Raycast hit;
  c2Ray c2_ray = lm2_ray2_f32_to_c2(ray);
  c2Circle c2_circle = lm2_circle_f32_to_c2(circle);

  int did_hit = c2RaytoCircle(c2_ray, c2_circle, &hit);
  result.hit = did_hit != 0;

  if (result.hit) {
    result.t = hit.t;
    result.normal = c2v_to_lm2_v2f32(hit.n);
    result.point = lm2_ray2_point_at_f32(ray, result.t);
  } else {
    result.t = 0.0f;
    result.normal = (lm2_v2f32) {0.0f, 0.0f};
    result.point = (lm2_v2f32) {0.0f, 0.0f};
  }

  return result;
}

LM2_API lm2_rayhit2_f32 lm2_raycast_aabb_f32(lm2_ray2_f32 ray, lm2_r2f32 aabb) {
  lm2_rayhit2_f32 result;
  c2Raycast hit;
  c2Ray c2_ray = lm2_ray2_f32_to_c2(ray);
  c2AABB c2_aabb = lm2_r2f32_to_c2(aabb);

  int did_hit = c2RaytoAABB(c2_ray, c2_aabb, &hit);
  result.hit = did_hit != 0;

  if (result.hit) {
    result.t = hit.t;
    result.normal = c2v_to_lm2_v2f32(hit.n);
    result.point = lm2_ray2_point_at_f32(ray, result.t);
  } else {
    result.t = 0.0f;
    result.normal = (lm2_v2f32) {0.0f, 0.0f};
    result.point = (lm2_v2f32) {0.0f, 0.0f};
  }

  return result;
}

LM2_API lm2_rayhit2_f32 lm2_raycast_capsule_f32(lm2_ray2_f32 ray, lm2_capsule2_f32 capsule) {
  lm2_rayhit2_f32 result;
  c2Raycast hit;
  c2Ray c2_ray = lm2_ray2_f32_to_c2(ray);
  c2Capsule c2_capsule = lm2_capsule2_f32_to_c2(capsule);

  int did_hit = c2RaytoCapsule(c2_ray, c2_capsule, &hit);
  result.hit = did_hit != 0;

  if (result.hit) {
    result.t = hit.t;
    result.normal = c2v_to_lm2_v2f32(hit.n);
    result.point = lm2_ray2_point_at_f32(ray, result.t);
  } else {
    result.t = 0.0f;
    result.normal = (lm2_v2f32) {0.0f, 0.0f};
    result.point = (lm2_v2f32) {0.0f, 0.0f};
  }

  return result;
}

LM2_API lm2_rayhit2_f32 lm2_raycast_polygon_f32(lm2_ray2_f32 ray, lm2_polygon_f32 polygon) {
  lm2_rayhit2_f32 result;
  c2Raycast hit;
  c2Ray c2_ray = lm2_ray2_f32_to_c2(ray);
  c2Poly c2_poly = lm2_polygon_f32_to_c2(polygon);

  int did_hit = c2RaytoPoly(c2_ray, &c2_poly, NULL, &hit);
  result.hit = did_hit != 0;

  if (result.hit) {
    result.t = hit.t;
    result.normal = c2v_to_lm2_v2f32(hit.n);
    result.point = lm2_ray2_point_at_f32(ray, result.t);
  } else {
    result.t = 0.0f;
    result.normal = (lm2_v2f32) {0.0f, 0.0f};
    result.point = (lm2_v2f32) {0.0f, 0.0f};
  }

  return result;
}

LM2_API lm2_rayhit2_f32 lm2_raycast_segment_f32(lm2_ray2_f32 ray, lm2_v2f32 segment_start, lm2_v2f32 segment_end) {
  // Convert segment to capsule with zero radius
  lm2_capsule2_f32 capsule;
  capsule.start = segment_start;
  capsule.end = segment_end;
  capsule.radius = 0.0f;

  return lm2_raycast_capsule_f32(ray, capsule);
}

