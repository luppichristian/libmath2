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
#include "lm2/geometry2d/lm2_edge2.h"
#include "lm2/geometry2d/lm2_raycast2.h"
#include "lm2/geometry2d/lm2_shape2.h"
#include "lm2/geometry3d/lm2_raycast3.h"
#include "lm2/scalar/lm2_safe_ops.h"
#include "lm2/scalar/lm2_scalar.h"
#include "lm2/vectors/lm2_vector_specifics.h"

// =============================================================================
// 2D Ray Construction - f64
// =============================================================================

LM2_API lm2_ray2_f64 lm2_ray2_make_f64(lm2_v2_f64 origin, lm2_v2_f64 direction, double t_max) {
  lm2_ray2_f64 result;
  result.origin = origin;
  result.direction = direction;
  result.t_max = t_max;
  return result;
}

LM2_API lm2_ray2_f64 lm2_ray2_from_points_f64(lm2_v2_f64 start, lm2_v2_f64 end) {
  lm2_ray2_f64 result;
  result.origin = start;
  lm2_v2_f64 diff = lm2_v2_sub_f64(end, start);
  double length = lm2_v2_length_f64(diff);
  result.direction = lm2_v2_norm_f64(diff);
  result.t_max = length;
  return result;
}

LM2_API lm2_v2_f64 lm2_ray2_point_at_f64(lm2_ray2_f64 ray, double t) {
  lm2_v2_f64 scaled_dir = lm2_v2_mul_s_f64(ray.direction, t);
  return lm2_v2_add_f64(ray.origin, scaled_dir);
}

// =============================================================================
// 2D Ray Construction - f32
// =============================================================================

LM2_API lm2_ray2_f32 lm2_ray2_make_f32(lm2_v2_f32 origin, lm2_v2_f32 direction, float t_max) {
  lm2_ray2_f32 result;
  result.origin = origin;
  result.direction = direction;
  result.t_max = t_max;
  return result;
}

LM2_API lm2_ray2_f32 lm2_ray2_from_points_f32(lm2_v2_f32 start, lm2_v2_f32 end) {
  lm2_ray2_f32 result;
  result.origin = start;
  lm2_v2_f32 diff = lm2_v2_sub_f32(end, start);
  float length = lm2_v2_length_f32(diff);
  result.direction = lm2_v2_norm_f32(diff);
  result.t_max = length;
  return result;
}

LM2_API lm2_v2_f32 lm2_ray2_point_at_f32(lm2_ray2_f32 ray, float t) {
  lm2_v2_f32 scaled_dir = lm2_v2_mul_s_f32(ray.direction, t);
  return lm2_v2_add_f32(ray.origin, scaled_dir);
}

// =============================================================================
// 2D Ray vs Primitive Tests - f64
// =============================================================================

// At a surface origin, return the outward face normal. Keep the caller's
// fallback for an origin strictly inside the box, where no face is selected.
static lm2_v2_f64 _lm2_aabb_origin_normal_f64(lm2_v2_f64 origin, lm2_r2_f64 aabb, lm2_v2_f64 fallback) {
  if (origin.x == aabb.min.x) return (lm2_v2_f64) {-1.0, 0.0};
  if (origin.x == aabb.max.x) return (lm2_v2_f64) {1.0, 0.0};
  if (origin.y == aabb.min.y) return (lm2_v2_f64) {0.0, -1.0};
  if (origin.y == aabb.max.y) return (lm2_v2_f64) {0.0, 1.0};
  return fallback;
}

static lm2_v2_f32 _lm2_aabb_origin_normal_f32(lm2_v2_f32 origin, lm2_r2_f32 aabb, lm2_v2_f32 fallback) {
  if (origin.x == aabb.min.x) return (lm2_v2_f32) {-1.0f, 0.0f};
  if (origin.x == aabb.max.x) return (lm2_v2_f32) {1.0f, 0.0f};
  if (origin.y == aabb.min.y) return (lm2_v2_f32) {0.0f, -1.0f};
  if (origin.y == aabb.max.y) return (lm2_v2_f32) {0.0f, 1.0f};
  return fallback;
}

LM2_API lm2_rayhit2_f64 lm2_raycast_circle_f64(lm2_ray2_f64 ray, lm2_circle_f64 circle) {
  lm2_rayhit2_f64 result = {0};
  if (ray.t_max < 0.0) return result;
  double dx = ray.origin.x - circle.center.x;
  double dy = ray.origin.y - circle.center.y;
  double radius = fabs(circle.radius);

  // Match the existing convention for an origin inside or on the circle.
  if (hypot(dx, dy) <= radius) {
    result.hit = true;
    result.point = ray.origin;
    return result;
  }

  double dir_len = hypot(ray.direction.x, ray.direction.y);
  if (dir_len == 0.0) return result;
  double ux = ray.direction.x / dir_len;
  double uy = ray.direction.y / dir_len;
  double signed_perpendicular = dx * uy - dy * ux;
  double perpendicular = fabs(signed_perpendicular);
  if (perpendicular > radius) return result;
  // Compute the half-chord without squaring the radius: squaring valid small
  // or large values can underflow or overflow even when the hit is finite.
  double ratio = radius > 0.0 ? perpendicular / radius : 0.0;
  double half_chord = radius * sqrt((1.0 - ratio) * (1.0 + ratio));
  double t = (-(dx * ux + dy * uy) - half_chord) / dir_len;
  if (t < 0.0 || t > ray.t_max) return result;

  result.hit = true;
  result.t = t;
  // Derive the entry point from the local chord. Reconstructing it with the
  // rounded t can cancel a small radius when the ray begins very far away.
  lm2_v2_f64 relative_hit = {
      signed_perpendicular * uy - half_chord * ux,
      -signed_perpendicular * ux - half_chord * uy};
  result.point = (lm2_v2_f64) {circle.center.x + relative_hit.x,
                               circle.center.y + relative_hit.y};
  double normal_len = hypot(relative_hit.x, relative_hit.y);
  if (normal_len > 0.0) {
    result.normal = (lm2_v2_f64) {relative_hit.x / normal_len, relative_hit.y / normal_len};
  }
  return result;
}

LM2_API lm2_rayhit2_f64 lm2_raycast_aabb_f64(lm2_ray2_f64 ray, lm2_r2_f64 aabb) {
  lm2_rayhit2_f64 result = {0};
  if (ray.t_max < 0.0) return result;
  double t_enter = 0.0;
  double t_exit = ray.t_max;
  // The former backend selected the negative X normal for inside-origin hits.
  lm2_v2_f64 normal = {-1.0, 0.0};

  for (int axis = 0; axis < 2; ++axis) {
    double origin = ray.origin.e[axis];
    double direction = ray.direction.e[axis];
    LM2_ASSERT(isfinite(origin) && isfinite(direction));
    LM2_ASSERT(isfinite(aabb.min.e[axis]) && isfinite(aabb.max.e[axis]));
    if (direction == 0.0) {
      if (origin < aabb.min.e[axis] || origin > aabb.max.e[axis]) return result;
      continue;
    }
    // A tiny nonzero component can produce an infinite slab bound even when
    // the actual hit is finite. It can also produce a subnormal hit point.
    double near_t = (aabb.min.e[axis] - origin) / direction;
    double far_t = (aabb.max.e[axis] - origin) / direction;
    double near_normal = -1.0;
    if (near_t > far_t) {
      double tmp = near_t;
      near_t = far_t;
      far_t = tmp;
      near_normal = 1.0;
    }
    if (near_t > t_enter) {
      t_enter = near_t;
      normal = (lm2_v2_f64) {0.0, 0.0};
      normal.e[axis] = near_normal;
    }
    if (far_t < t_exit) t_exit = far_t;
    if (t_enter > t_exit) return result;
  }

  result.hit = true;
  result.t = t_enter;
  result.point.x = ray.origin.x + ray.direction.x * t_enter;
  result.point.y = ray.origin.y + ray.direction.y * t_enter;
  result.normal = normal;
  if (t_enter == 0.0) result.normal = _lm2_aabb_origin_normal_f64(ray.origin, aabb, result.normal);
  return result;
}

LM2_API lm2_rayhit2_f64 lm2_raycast_capsule2_f64(lm2_ray2_f64 ray, lm2_capsule2_f64 capsule) {
  lm2_rayhit2_f64 result = {0};
  if (ray.t_max < 0.0) return result;
  const double dx = capsule.end.x - capsule.start.x;
  const double dy = capsule.end.y - capsule.start.y;
  const double length = hypot(dx, dy);
  const double ux = length > 0.0 ? dx / length : 0.0;
  const double uy = length > 0.0 ? dy / length : 0.0;
  const double ox = ray.origin.x - capsule.start.x;
  const double oy = ray.origin.y - capsule.start.y;
  double along = ox * ux + oy * uy;
  if (along < 0.0) along = 0.0;
  if (along > length) along = length;
  if (hypot(ox - along * ux, oy - along * uy) <= capsule.radius) {
    // Preserve the 2D backend's origin-inside convention.
    result.hit = true;
    result.point = ray.origin;
    result.normal = (lm2_v2_f64) {ux, uy};
    return result;
  }

  // The 3D implementation handles a capsule in any plane, including z=0.
  lm2_ray3_f64 ray3 = {
      {   ray.origin.x,    ray.origin.y, 0.0},
      {ray.direction.x, ray.direction.y, 0.0},
      ray.t_max
  };
  lm2_v3_f64 start = {capsule.start.x, capsule.start.y, 0.0};
  lm2_v3_f64 end = {capsule.end.x, capsule.end.y, 0.0};
  lm2_rayhit3_f64 hit = lm2_raycast_capsule_f64(ray3, start, end, capsule.radius);
  if (hit.hit) {
    result.hit = true;
    result.t = hit.t;
    result.point = (lm2_v2_f64) {hit.point.x, hit.point.y};
    result.normal = (lm2_v2_f64) {hit.normal.x, hit.normal.y};
    if (capsule.radius == 0.0 && length > 0.0 && result.normal.x == 0.0 && result.normal.y == 0.0) {
      // A zero-radius capsule is a segment: use the face opposing the ray.
      const double dot = uy * ray.direction.x - ux * ray.direction.y;
      if (dot != 0.0) {
        const double sign = dot > 0.0 ? -1.0 : 1.0;
        result.normal = (lm2_v2_f64) {sign * uy, -sign * ux};
      }
    }
  }
  return result;
}

// Clip against the outward half-planes of a counterclockwise convex polygon.
// Like the original backend, a ray starting inside has no entering face.
static lm2_rayhit2_f64 _lm2_raycast_convex_f64(lm2_ray2_f64 ray, const lm2_v2_f64* vertices, size_t count) {
  lm2_rayhit2_f64 result = {0};
  double lo = 0.0;
  double hi = ray.t_max;
  size_t entry = count;
  if (hi < 0.0) return result;

  for (size_t i = 0; i < count; ++i) {
    const lm2_v2_f64 a = vertices[i];
    const lm2_v2_f64 b = vertices[(i + 1) % count];
    const double ex = b.y - a.y;
    const double ey = a.x - b.x;
    const double edge_length = hypot(ex, ey);
    if (edge_length == 0.0) continue;
    const double nx = ex / edge_length;
    const double ny = ey / edge_length;
    const double numerator = nx * (a.x - ray.origin.x) + ny * (a.y - ray.origin.y);
    const double denominator = nx * ray.direction.x + ny * ray.direction.y;
    if (denominator == 0.0) {
      if (numerator < 0.0) return result;
    } else {
      const double t = numerator / denominator;
      if (denominator < 0.0 && t > lo) {
        lo = t;
        entry = i;
      } else if (denominator > 0.0 && t < hi) {
        hi = t;
      }
    }
    if (hi < lo) return result;
  }

  if (entry == count) return result;
  const lm2_v2_f64 a = vertices[entry];
  const lm2_v2_f64 b = vertices[(entry + 1) % count];
  const double nx = b.y - a.y;
  const double ny = a.x - b.x;
  const double length = hypot(nx, ny);
  LM2_ASSERT(length > 0.0);
  result.hit = true;
  result.t = lo;
  result.point.x = ray.origin.x + ray.direction.x * lo;
  result.point.y = ray.origin.y + ray.direction.y * lo;
  result.normal.x = nx / length;
  result.normal.y = ny / length;
  return result;
}

LM2_API lm2_rayhit2_f64 lm2_raycast_polygon_f64(lm2_ray2_f64 ray, lm2_polygon_f64 polygon) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3 && polygon.vertex_count <= C2_MAX_POLYGON_VERTS);
  return _lm2_raycast_convex_f64(ray, polygon.vertices, polygon.vertex_count);
}

LM2_API lm2_rayhit2_f64 lm2_raycast_segment_f64(lm2_ray2_f64 ray, lm2_v2_f64 segment_start, lm2_v2_f64 segment_end) {
  // Backward-compat wrapper - canonical API is lm2_raycast_edge2_f64 in lm2_edge2.h
  lm2_capsule2_f64 capsule;
  capsule.start = segment_start;
  capsule.end = segment_end;
  capsule.radius = 0.0;

  return lm2_raycast_capsule2_f64(ray, capsule);
}

// =============================================================================
// 2D Ray vs Primitive Tests - f32
// =============================================================================

LM2_API lm2_rayhit2_f32 lm2_raycast_circle_f32(lm2_ray2_f32 ray, lm2_circle_f32 circle) {
  lm2_rayhit2_f32 result = {0};
  if (ray.t_max < 0.0f) return result;
  float dx = ray.origin.x - circle.center.x;
  float dy = ray.origin.y - circle.center.y;
  float radius = fabsf(circle.radius);
  if (hypotf(dx, dy) <= radius) {
    result.hit = true;
    result.point = ray.origin;
    return result;
  }
  float dir_len = hypotf(ray.direction.x, ray.direction.y);
  if (dir_len == 0.0f) return result;
  float ux = ray.direction.x / dir_len;
  float uy = ray.direction.y / dir_len;
  float signed_perpendicular = dx * uy - dy * ux;
  float perpendicular = fabsf(signed_perpendicular);
  if (perpendicular > radius) return result;
  float ratio = radius > 0.0f ? perpendicular / radius : 0.0f;
  float half_chord = radius * sqrtf((1.0f - ratio) * (1.0f + ratio));
  float t = (-(dx * ux + dy * uy) - half_chord) / dir_len;
  if (t < 0.0f || t > ray.t_max) return result;
  result.hit = true;
  result.t = t;
  lm2_v2_f32 relative_hit = {
      signed_perpendicular * uy - half_chord * ux,
      -signed_perpendicular * ux - half_chord * uy};
  result.point = (lm2_v2_f32) {circle.center.x + relative_hit.x,
                               circle.center.y + relative_hit.y};
  float normal_len = hypotf(relative_hit.x, relative_hit.y);
  if (normal_len > 0.0f) {
    result.normal = (lm2_v2_f32) {relative_hit.x / normal_len, relative_hit.y / normal_len};
  }
  return result;
}

LM2_API lm2_rayhit2_f32 lm2_raycast_aabb_f32(lm2_ray2_f32 ray, lm2_r2_f32 aabb) {
  lm2_rayhit2_f32 result = {0};
  if (ray.t_max < 0.0f) return result;
  c2Raycast hit;
  c2Ray c2_ray = lm2_ray2_f32_to_c2(ray);
  c2AABB c2_aabb = lm2_r2_f32_to_c2(aabb);

  int did_hit = c2RaytoAABB(c2_ray, c2_aabb, &hit);
  result.hit = did_hit != 0;

  if (result.hit) {
    result.t = hit.t;
    result.normal = c2v_to_lm22_f32(hit.n);
    result.point = lm2_ray2_point_at_f32(ray, result.t);
    if (result.t == 0.0f) result.normal = _lm2_aabb_origin_normal_f32(ray.origin, aabb, result.normal);
  } else {
    result.t = 0.0f;
    result.normal = (lm2_v2_f32) {0.0f, 0.0f};
    result.point = (lm2_v2_f32) {0.0f, 0.0f};
  }

  return result;
}

LM2_API lm2_rayhit2_f32 lm2_raycast_capsule2_f32(lm2_ray2_f32 ray, lm2_capsule2_f32 capsule) {
  lm2_rayhit2_f32 result = {0};
  if (ray.t_max < 0.0f) return result;
  float dx = capsule.end.x - capsule.start.x;
  float dy = capsule.end.y - capsule.start.y;
  float length = hypotf(dx, dy);
  float ux = length > 0.0f ? dx / length : 0.0f;
  float uy = length > 0.0f ? dy / length : 0.0f;
  float ox = ray.origin.x - capsule.start.x;
  float oy = ray.origin.y - capsule.start.y;
  float along = ox * ux + oy * uy;
  if (along < 0.0f) along = 0.0f;
  if (along > length) along = length;
  if (hypotf(ox - along * ux, oy - along * uy) <= capsule.radius) {
    result.hit = true;
    result.point = ray.origin;
    result.normal = (lm2_v2_f32) {ux, uy};
    return result;
  }
  lm2_ray3_f32 ray3 = {
      {   ray.origin.x,    ray.origin.y, 0.0f},
      {ray.direction.x, ray.direction.y, 0.0f},
      ray.t_max
  };
  lm2_v3_f32 start = {capsule.start.x, capsule.start.y, 0.0f};
  lm2_v3_f32 end = {capsule.end.x, capsule.end.y, 0.0f};
  lm2_rayhit3_f32 hit = lm2_raycast_capsule_f32(ray3, start, end, capsule.radius);
  if (hit.hit) {
    result.hit = true;
    result.t = hit.t;
    result.point = (lm2_v2_f32) {hit.point.x, hit.point.y};
    result.normal = (lm2_v2_f32) {hit.normal.x, hit.normal.y};
    if (capsule.radius == 0.0f && length > 0.0f && result.normal.x == 0.0f && result.normal.y == 0.0f) {
      float dot = uy * ray.direction.x - ux * ray.direction.y;
      if (dot != 0.0f) {
        float sign = dot > 0.0f ? -1.0f : 1.0f;
        result.normal = (lm2_v2_f32) {sign * uy, -sign * ux};
      }
    }
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
    result.normal = c2v_to_lm22_f32(hit.n);
    result.point = lm2_ray2_point_at_f32(ray, result.t);
  } else {
    result.t = 0.0f;
    result.normal = (lm2_v2_f32) {0.0f, 0.0f};
    result.point = (lm2_v2_f32) {0.0f, 0.0f};
  }

  return result;
}

LM2_API lm2_rayhit2_f32 lm2_raycast_segment_f32(lm2_ray2_f32 ray, lm2_v2_f32 segment_start, lm2_v2_f32 segment_end) {
  // Backward-compat wrapper - canonical API is lm2_raycast_edge2_f32 in lm2_edge2.h
  lm2_capsule2_f32 capsule;
  capsule.start = segment_start;
  capsule.end = segment_end;
  capsule.radius = 0.0f;

  return lm2_raycast_capsule2_f32(ray, capsule);
}

// =============================================================================
// Ray vs Triangle - f64
// =============================================================================

LM2_API lm2_rayhit2_f64 lm2_raycast_triangle2_f64(lm2_ray2_f64 ray, const lm2_triangle2_f64 tri) {
  return _lm2_raycast_convex_f64(ray, tri, 3);
}

// =============================================================================
// Ray vs Triangle - f32
// =============================================================================

LM2_API lm2_rayhit2_f32 lm2_raycast_triangle2_f32(lm2_ray2_f32 ray, const lm2_triangle2_f32 tri) {
  lm2_rayhit2_f32 result;
  result.hit = false;
  result.t = 0.0f;
  result.point = (lm2_v2_f32) {0.0f, 0.0f};
  result.normal = (lm2_v2_f32) {0.0f, 0.0f};

  // Convert triangle to polygon
  c2Poly poly = lm2_triangle2_f32_to_c2(tri);

  // Convert ray to c2Ray
  c2Ray c2ray = lm2_ray2_f32_to_c2(ray);

  // Perform raycast
  c2Raycast out;
  int hit = c2RaytoPoly(c2ray, &poly, NULL, &out);

  if (hit) {
    result.hit = true;
    result.t = out.t;
    result.point = lm2_v2_add_f32(ray.origin, lm2_v2_mul_s_f32(ray.direction, result.t));
    result.normal = c2v_to_lm22_f32(out.n);
  }

  return result;
}

// =============================================================================
// Ray vs Plane (Infinite Line in 2D) - f64
// =============================================================================

LM2_API lm2_rayhit2_f64 lm2_raycast_plane2_f64(lm2_ray2_f64 ray, lm2_plane2_f64 plane) {
  lm2_rayhit2_f64 result;
  result.hit = false;
  result.t = 0.0;
  result.point = (lm2_v2_f64) {0.0, 0.0};
  result.normal = (lm2_v2_f64) {0.0, 0.0};

  // Compute denominator (dot product of ray direction and plane normal)
  double denom = lm2_v2_dot_f64(ray.direction, plane.normal);

  // Check if ray is parallel to plane (denom close to zero)
  if (lm2_abs_f64(denom) < LM2_RAYCAST2_EPSILON_F64) {
    return result;  // No intersection (parallel or nearly parallel)
  }

  // Compute signed distance from ray origin to plane
  double origin_dist = lm2_sub_f64(lm2_v2_dot_f64(ray.origin, plane.normal), plane.distance);

  // Compute t parameter
  double t = lm2_div_f64(lm2_mul_f64(origin_dist, -1.0), denom);

  // Check if intersection is within ray bounds (t >= 0 and t <= ray.t_max)
  if (t >= 0.0 && t <= ray.t_max) {
    result.hit = true;
    result.t = t;
    result.point = lm2_v2_add_f64(ray.origin, lm2_v2_mul_s_f64(ray.direction, t));

    // Normal points in the direction of the plane normal
    // If ray is hitting from the back side, we might want to flip it
    if (denom > 0.0) {
      result.normal = lm2_v2_mul_s_f64(plane.normal, -1.0);
    } else {
      result.normal = plane.normal;
    }
  }

  return result;
}

// =============================================================================
// Ray vs Plane (Infinite Line in 2D) - f32
// =============================================================================

LM2_API lm2_rayhit2_f32 lm2_raycast_plane2_f32(lm2_ray2_f32 ray, lm2_plane2_f32 plane) {
  lm2_rayhit2_f32 result;
  result.hit = false;
  result.t = 0.0f;
  result.point = (lm2_v2_f32) {0.0f, 0.0f};
  result.normal = (lm2_v2_f32) {0.0f, 0.0f};

  // Compute denominator (dot product of ray direction and plane normal)
  float denom = lm2_v2_dot_f32(ray.direction, plane.normal);

  // Check if ray is parallel to plane (denom close to zero)
  if (lm2_abs_f32(denom) < LM2_RAYCAST2_EPSILON_F32) {
    return result;  // No intersection (parallel or nearly parallel)
  }

  // Compute signed distance from ray origin to plane
  float origin_dist = lm2_sub_f32(lm2_v2_dot_f32(ray.origin, plane.normal), plane.distance);

  // Compute t parameter
  float t = lm2_div_f32(lm2_mul_f32(origin_dist, -1.0f), denom);

  // Check if intersection is within ray bounds (t >= 0 and t <= ray.t_max)
  if (t >= 0.0f && t <= ray.t_max) {
    result.hit = true;
    result.t = t;
    result.point = lm2_v2_add_f32(ray.origin, lm2_v2_mul_s_f32(ray.direction, t));

    // Normal points in the direction of the plane normal
    // If ray is hitting from the back side, we might want to flip it
    if (denom > 0.0f) {
      result.normal = lm2_v2_mul_s_f32(plane.normal, -1.0f);
    } else {
      result.normal = plane.normal;
    }
  }

  return result;
}

// =============================================================================
// Generic Shape Raycasting - f64
// =============================================================================

LM2_API lm2_rayhit2_f64 lm2_raycast_shape2_f64(lm2_ray2_f64 ray, lm2_shape2_f64 shape) {
  LM2_ASSERT(shape.data != NULL);

  lm2_rayhit2_f64 result;
  result.hit = false;
  result.t = 0.0;
  result.point = (lm2_v2_f64) {0.0, 0.0};
  result.normal = (lm2_v2_f64) {0.0, 0.0};

  switch (shape.type) {
    case LM2_SHAPE2_CIRCLE: {
      lm2_circle_f64* circle = (lm2_circle_f64*)shape.data;
      result = lm2_raycast_circle_f64(ray, *circle);
      break;
    }

    case LM2_SHAPE2_CAPSULE: {
      lm2_capsule2_f64* capsule = (lm2_capsule2_f64*)shape.data;
      result = lm2_raycast_capsule2_f64(ray, *capsule);
      break;
    }

    case LM2_SHAPE2_AABB2: {
      lm2_aabb2_f64* rect = (lm2_aabb2_f64*)shape.data;
      result = lm2_raycast_aabb_f64(ray, *rect);
      break;
    }

    case LM2_SHAPE2_TRIANGLE: {
      lm2_triangle2_f64* tri = (lm2_triangle2_f64*)shape.data;
      result = lm2_raycast_triangle2_f64(ray, *tri);
      break;
    }

    case LM2_SHAPE2_POLYGON: {
      lm2_polygon_f64* poly = (lm2_polygon_f64*)shape.data;
      result = lm2_raycast_polygon_f64(ray, *poly);
      break;
    }

    case LM2_SHAPE2_EDGE: {
      lm2_edge2_f64* edge = (lm2_edge2_f64*)shape.data;
      result = lm2_raycast_segment_f64(ray, edge->start, edge->end);
      break;
    }

    default:
      break;
  }

  return result;
}

// =============================================================================
// Generic Shape Raycasting - f32
// =============================================================================

LM2_API lm2_rayhit2_f32 lm2_raycast_shape2_f32(lm2_ray2_f32 ray, lm2_shape2_f32 shape) {
  LM2_ASSERT(shape.data != NULL);

  lm2_rayhit2_f32 result;
  result.hit = false;
  result.t = 0.0f;
  result.point = (lm2_v2_f32) {0.0f, 0.0f};
  result.normal = (lm2_v2_f32) {0.0f, 0.0f};

  switch (shape.type) {
    case LM2_SHAPE2_CIRCLE: {
      lm2_circle_f32* circle = (lm2_circle_f32*)shape.data;
      result = lm2_raycast_circle_f32(ray, *circle);
      break;
    }

    case LM2_SHAPE2_CAPSULE: {
      lm2_capsule2_f32* capsule = (lm2_capsule2_f32*)shape.data;
      result = lm2_raycast_capsule2_f32(ray, *capsule);
      break;
    }

    case LM2_SHAPE2_AABB2: {
      lm2_aabb2_f32* rect = (lm2_aabb2_f32*)shape.data;
      result = lm2_raycast_aabb_f32(ray, *rect);
      break;
    }

    case LM2_SHAPE2_TRIANGLE: {
      lm2_triangle2_f32* tri = (lm2_triangle2_f32*)shape.data;
      result = lm2_raycast_triangle2_f32(ray, *tri);
      break;
    }

    case LM2_SHAPE2_POLYGON: {
      lm2_polygon_f32* poly = (lm2_polygon_f32*)shape.data;
      result = lm2_raycast_polygon_f32(ray, *poly);
      break;
    }

    case LM2_SHAPE2_EDGE: {
      lm2_edge2_f32* edge = (lm2_edge2_f32*)shape.data;
      result = lm2_raycast_segment_f32(ray, edge->start, edge->end);
      break;
    }

    default:
      break;
  }

  return result;
}
