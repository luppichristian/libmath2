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

#include "lm2/geometry3d/lm2_raycast3.h"
#include "lm2/geometry3d/lm2_shape3.h"
#include "lm2/geometry3d/lm2_edge3.h"
#include "lm2/geometry3d/lm2_plane3.h"
#include "lm2/geometry3d/lm2_sphere.h"
#include "lm2/geometry3d/lm2_capsule3.h"
#include "lm2/geometry3d/lm2_cuboid.h"
#include "lm2/geometry3d/lm2_triangle3.h"
#include "lm2/scalar/lm2_safe_ops.h"
#include "lm2/scalar/lm2_scalar.h"
#include "lm2/vectors/lm2_vector_specifics.h"

// =============================================================================
// 3D Ray Construction - f64
// =============================================================================

LM2_API lm2_ray3_f64 lm2_ray3_make_f64(lm2_v3_f64 origin, lm2_v3_f64 direction, double t_max) {
  lm2_ray3_f64 result;
  result.origin = origin;
  result.direction = direction;
  result.t_max = t_max;
  return result;
}

LM2_API lm2_ray3_f64 lm2_ray3_from_points_f64(lm2_v3_f64 start, lm2_v3_f64 end) {
  lm2_ray3_f64 result;
  result.origin = start;
  lm2_v3_f64 diff = lm2_v3_sub_f64(end, start);
  double length = lm2_v3_length_f64(diff);
  result.direction = lm2_v3_normalize_f64(diff);
  result.t_max = length;
  return result;
}

LM2_API lm2_v3_f64 lm2_ray3_point_at_f64(lm2_ray3_f64 ray, double t) {
  lm2_v3_f64 scaled_dir = lm2_v3_mul_s_f64(ray.direction, t);
  return lm2_v3_add_f64(ray.origin, scaled_dir);
}

// =============================================================================
// 3D Ray Construction - f32
// =============================================================================

LM2_API lm2_ray3_f32 lm2_ray3_make_f32(lm2_v3_f32 origin, lm2_v3_f32 direction, float t_max) {
  lm2_ray3_f32 result;
  result.origin = origin;
  result.direction = direction;
  result.t_max = t_max;
  return result;
}

LM2_API lm2_ray3_f32 lm2_ray3_from_points_f32(lm2_v3_f32 start, lm2_v3_f32 end) {
  lm2_ray3_f32 result;
  result.origin = start;
  lm2_v3_f32 diff = lm2_v3_sub_f32(end, start);
  float length = lm2_v3_length_f32(diff);
  result.direction = lm2_v3_normalize_f32(diff);
  result.t_max = length;
  return result;
}

LM2_API lm2_v3_f32 lm2_ray3_point_at_f32(lm2_ray3_f32 ray, float t) {
  lm2_v3_f32 scaled_dir = lm2_v3_mul_s_f32(ray.direction, t);
  return lm2_v3_add_f32(ray.origin, scaled_dir);
}

// =============================================================================
// 3D Ray vs Primitive Tests - f64
// =============================================================================

LM2_API lm2_rayhit3_f64 lm2_raycast_sphere_f64(lm2_ray3_f64 ray, lm2_v3_f64 center, double radius) {
  lm2_rayhit3_f64 result;

  // Ray-sphere intersection using quadratic formula
  lm2_v3_f64 oc = lm2_v3_sub_f64(ray.origin, center);
  double a = lm2_v3_dot_f64(ray.direction, ray.direction);
  double b = lm2_mul_f64(2.0, lm2_v3_dot_f64(oc, ray.direction));
  double c = lm2_sub_f64(lm2_v3_dot_f64(oc, oc), lm2_mul_f64(radius, radius));
  double discriminant = lm2_sub_f64(lm2_mul_f64(b, b), lm2_mul_f64(lm2_mul_f64(4.0, a), c));

  if (discriminant < 0.0) {
    result.hit = false;
    result.t = 0.0;
    result.normal = (lm2_v3_f64) {0.0, 0.0, 0.0};
    result.point = (lm2_v3_f64) {0.0, 0.0, 0.0};
  } else {
    double sqrt_disc = lm2_sqrt_f64(discriminant);
    double t = lm2_div_f64(lm2_sub_f64(lm2_mul_f64(-1.0, b), sqrt_disc), lm2_mul_f64(2.0, a));

    if (t < 0.0 || t > ray.t_max) {
      result.hit = false;
      result.t = 0.0;
      result.normal = (lm2_v3_f64) {0.0, 0.0, 0.0};
      result.point = (lm2_v3_f64) {0.0, 0.0, 0.0};
    } else {
      result.hit = true;
      result.t = t;
      result.point = lm2_ray3_point_at_f64(ray, t);
      result.normal = lm2_v3_normalize_f64(lm2_v3_sub_f64(result.point, center));
    }
  }

  return result;
}

LM2_API lm2_rayhit3_f64 lm2_raycast_aabb3_f64(lm2_ray3_f64 ray, lm2_r3_f64 aabb) {
  lm2_rayhit3_f64 result;

  // Ray-AABB intersection using slab method
  double t_min = 0.0;
  double t_max = ray.t_max;

  for (int i = 0; i < 3; ++i) {
    double inv_d = lm2_div_f64(1.0, ray.direction.e[i]);
    double t0 = lm2_mul_f64(lm2_sub_f64(aabb.min.e[i], ray.origin.e[i]), inv_d);
    double t1 = lm2_mul_f64(lm2_sub_f64(aabb.max.e[i], ray.origin.e[i]), inv_d);

    if (inv_d < 0.0) {
      double temp = t0;
      t0 = t1;
      t1 = temp;
    }

    t_min = t0 > t_min ? t0 : t_min;
    t_max = t1 < t_max ? t1 : t_max;

    if (t_max <= t_min) {
      result.hit = false;
      result.t = 0.0;
      result.normal = (lm2_v3_f64) {0.0, 0.0, 0.0};
      result.point = (lm2_v3_f64) {0.0, 0.0, 0.0};
      return result;
    }
  }

  result.hit = true;
  result.t = t_min;
  result.point = lm2_ray3_point_at_f64(ray, t_min);

  // Compute normal
  lm2_v3_f64 center = lm2_v3_mul_s_f64(lm2_v3_add_f64(aabb.min, aabb.max), 0.5);
  lm2_v3_f64 local = lm2_v3_sub_f64(result.point, center);
  lm2_v3_f64 abs_local = lm2_v3_abs_f64(local);

  if (abs_local.x > abs_local.y && abs_local.x > abs_local.z) {
    result.normal = (lm2_v3_f64) {local.x > 0.0 ? 1.0 : -1.0, 0.0, 0.0};
  } else if (abs_local.y > abs_local.z) {
    result.normal = (lm2_v3_f64) {0.0, local.y > 0.0 ? 1.0 : -1.0, 0.0};
  } else {
    result.normal = (lm2_v3_f64) {0.0, 0.0, local.z > 0.0 ? 1.0 : -1.0};
  }

  return result;
}

LM2_API lm2_rayhit3_f64 lm2_raycast_triangle_f64(lm2_ray3_f64 ray, lm2_v3_f64 v0, lm2_v3_f64 v1, lm2_v3_f64 v2) {
  lm2_rayhit3_f64 result;

  // Möller-Trumbore intersection algorithm
  const double epsilon = LM2_RAYCAST3_EPSILON_F64;

  lm2_v3_f64 edge1 = lm2_v3_sub_f64(v1, v0);
  lm2_v3_f64 edge2 = lm2_v3_sub_f64(v2, v0);
  lm2_v3_f64 h = lm2_v3_cross_f64(ray.direction, edge2);
  double a = lm2_v3_dot_f64(edge1, h);

  if (lm2_abs_f64(a) < epsilon) {
    result.hit = false;
    result.t = 0.0;
    result.normal = (lm2_v3_f64) {0.0, 0.0, 0.0};
    result.point = (lm2_v3_f64) {0.0, 0.0, 0.0};
    return result;
  }

  double f = lm2_div_f64(1.0, a);
  lm2_v3_f64 s = lm2_v3_sub_f64(ray.origin, v0);
  double u = lm2_mul_f64(f, lm2_v3_dot_f64(s, h));

  if (u < 0.0 || u > 1.0) {
    result.hit = false;
    result.t = 0.0;
    result.normal = (lm2_v3_f64) {0.0, 0.0, 0.0};
    result.point = (lm2_v3_f64) {0.0, 0.0, 0.0};
    return result;
  }

  lm2_v3_f64 q = lm2_v3_cross_f64(s, edge1);
  double v = lm2_mul_f64(f, lm2_v3_dot_f64(ray.direction, q));

  if (v < 0.0 || lm2_add_f64(u, v) > 1.0) {
    result.hit = false;
    result.t = 0.0;
    result.normal = (lm2_v3_f64) {0.0, 0.0, 0.0};
    result.point = (lm2_v3_f64) {0.0, 0.0, 0.0};
    return result;
  }

  double t = lm2_mul_f64(f, lm2_v3_dot_f64(edge2, q));

  if (t > epsilon && t <= ray.t_max) {
    result.hit = true;
    result.t = t;
    result.point = lm2_ray3_point_at_f64(ray, t);
    result.normal = lm2_v3_normalize_f64(lm2_v3_cross_f64(edge1, edge2));
  } else {
    result.hit = false;
    result.t = 0.0;
    result.normal = (lm2_v3_f64) {0.0, 0.0, 0.0};
    result.point = (lm2_v3_f64) {0.0, 0.0, 0.0};
  }

  return result;
}

LM2_API lm2_rayhit3_f64 lm2_raycast_plane_f64(lm2_ray3_f64 ray, lm2_v3_f64 plane_point, lm2_v3_f64 plane_normal) {
  lm2_rayhit3_f64 result;

  const double epsilon = LM2_RAYCAST3_EPSILON_F64;

  double denom = lm2_v3_dot_f64(plane_normal, ray.direction);

  if (lm2_abs_f64(denom) > epsilon) {
    lm2_v3_f64 p0l0 = lm2_v3_sub_f64(plane_point, ray.origin);
    double t = lm2_div_f64(lm2_v3_dot_f64(p0l0, plane_normal), denom);

    if (t >= 0.0 && t <= ray.t_max) {
      result.hit = true;
      result.t = t;
      result.point = lm2_ray3_point_at_f64(ray, t);
      result.normal = plane_normal;
      return result;
    }
  }

  result.hit = false;
  result.t = 0.0;
  result.normal = (lm2_v3_f64) {0.0, 0.0, 0.0};
  result.point = (lm2_v3_f64) {0.0, 0.0, 0.0};
  return result;
}

// =============================================================================
// 3D Ray vs Primitive Tests - f32
// =============================================================================

LM2_API lm2_rayhit3_f32 lm2_raycast_sphere_f32(lm2_ray3_f32 ray, lm2_v3_f32 center, float radius) {
  lm2_rayhit3_f32 result;

  // Ray-sphere intersection using quadratic formula
  lm2_v3_f32 oc = lm2_v3_sub_f32(ray.origin, center);
  float a = lm2_v3_dot_f32(ray.direction, ray.direction);
  float b = lm2_mul_f32(2.0f, lm2_v3_dot_f32(oc, ray.direction));
  float c = lm2_sub_f32(lm2_v3_dot_f32(oc, oc), lm2_mul_f32(radius, radius));
  float discriminant = lm2_sub_f32(lm2_mul_f32(b, b), lm2_mul_f32(lm2_mul_f32(4.0f, a), c));

  if (discriminant < 0.0f) {
    result.hit = false;
    result.t = 0.0f;
    result.normal = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
    result.point = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
  } else {
    float sqrt_disc = lm2_sqrt_f32(discriminant);
    float t = lm2_div_f32(lm2_sub_f32(lm2_mul_f32(-1.0f, b), sqrt_disc), lm2_mul_f32(2.0f, a));

    if (t < 0.0f || t > ray.t_max) {
      result.hit = false;
      result.t = 0.0f;
      result.normal = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
      result.point = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
    } else {
      result.hit = true;
      result.t = t;
      result.point = lm2_ray3_point_at_f32(ray, t);
      result.normal = lm2_v3_normalize_f32(lm2_v3_sub_f32(result.point, center));
    }
  }

  return result;
}

LM2_API lm2_rayhit3_f32 lm2_raycast_aabb3_f32(lm2_ray3_f32 ray, lm2_r3_f32 aabb) {
  lm2_rayhit3_f32 result;

  // Ray-AABB intersection using slab method
  float t_min = 0.0f;
  float t_max = ray.t_max;

  for (int i = 0; i < 3; ++i) {
    float inv_d = lm2_div_f32(1.0f, ray.direction.e[i]);
    float t0 = lm2_mul_f32(lm2_sub_f32(aabb.min.e[i], ray.origin.e[i]), inv_d);
    float t1 = lm2_mul_f32(lm2_sub_f32(aabb.max.e[i], ray.origin.e[i]), inv_d);

    if (inv_d < 0.0f) {
      float temp = t0;
      t0 = t1;
      t1 = temp;
    }

    t_min = t0 > t_min ? t0 : t_min;
    t_max = t1 < t_max ? t1 : t_max;

    if (t_max <= t_min) {
      result.hit = false;
      result.t = 0.0f;
      result.normal = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
      result.point = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
      return result;
    }
  }

  result.hit = true;
  result.t = t_min;
  result.point = lm2_ray3_point_at_f32(ray, t_min);

  // Compute normal
  lm2_v3_f32 center = lm2_v3_mul_s_f32(lm2_v3_add_f32(aabb.min, aabb.max), 0.5f);
  lm2_v3_f32 local = lm2_v3_sub_f32(result.point, center);
  lm2_v3_f32 abs_local = lm2_v3_abs_f32(local);

  if (abs_local.x > abs_local.y && abs_local.x > abs_local.z) {
    result.normal = (lm2_v3_f32) {local.x > 0.0f ? 1.0f : -1.0f, 0.0f, 0.0f};
  } else if (abs_local.y > abs_local.z) {
    result.normal = (lm2_v3_f32) {0.0f, local.y > 0.0f ? 1.0f : -1.0f, 0.0f};
  } else {
    result.normal = (lm2_v3_f32) {0.0f, 0.0f, local.z > 0.0f ? 1.0f : -1.0f};
  }

  return result;
}

LM2_API lm2_rayhit3_f32 lm2_raycast_triangle_f32(lm2_ray3_f32 ray, lm2_v3_f32 v0, lm2_v3_f32 v1, lm2_v3_f32 v2) {
  lm2_rayhit3_f32 result;

  // Möller-Trumbore intersection algorithm
  const float epsilon = LM2_RAYCAST3_EPSILON_F32;

  lm2_v3_f32 edge1 = lm2_v3_sub_f32(v1, v0);
  lm2_v3_f32 edge2 = lm2_v3_sub_f32(v2, v0);
  lm2_v3_f32 h = lm2_v3_cross_f32(ray.direction, edge2);
  float a = lm2_v3_dot_f32(edge1, h);

  if (lm2_abs_f32(a) < epsilon) {
    result.hit = false;
    result.t = 0.0f;
    result.normal = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
    result.point = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
    return result;
  }

  float f = lm2_div_f32(1.0f, a);
  lm2_v3_f32 s = lm2_v3_sub_f32(ray.origin, v0);
  float u = lm2_mul_f32(f, lm2_v3_dot_f32(s, h));

  if (u < 0.0f || u > 1.0f) {
    result.hit = false;
    result.t = 0.0f;
    result.normal = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
    result.point = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
    return result;
  }

  lm2_v3_f32 q = lm2_v3_cross_f32(s, edge1);
  float v = lm2_mul_f32(f, lm2_v3_dot_f32(ray.direction, q));

  if (v < 0.0f || lm2_add_f32(u, v) > 1.0f) {
    result.hit = false;
    result.t = 0.0f;
    result.normal = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
    result.point = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
    return result;
  }

  float t = lm2_mul_f32(f, lm2_v3_dot_f32(edge2, q));

  if (t > epsilon && t <= ray.t_max) {
    result.hit = true;
    result.t = t;
    result.point = lm2_ray3_point_at_f32(ray, t);
    result.normal = lm2_v3_normalize_f32(lm2_v3_cross_f32(edge1, edge2));
  } else {
    result.hit = false;
    result.t = 0.0f;
    result.normal = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
    result.point = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
  }

  return result;
}

LM2_API lm2_rayhit3_f32 lm2_raycast_plane_f32(lm2_ray3_f32 ray, lm2_v3_f32 plane_point, lm2_v3_f32 plane_normal) {
  lm2_rayhit3_f32 result;

  const float epsilon = LM2_RAYCAST3_EPSILON_F32;

  float denom = lm2_v3_dot_f32(plane_normal, ray.direction);

  if (lm2_abs_f32(denom) > epsilon) {
    lm2_v3_f32 p0l0 = lm2_v3_sub_f32(plane_point, ray.origin);
    float t = lm2_div_f32(lm2_v3_dot_f32(p0l0, plane_normal), denom);

    if (t >= 0.0f && t <= ray.t_max) {
      result.hit = true;
      result.t = t;
      result.point = lm2_ray3_point_at_f32(ray, t);
      result.normal = plane_normal;
      return result;
    }
  }

  result.hit = false;
  result.t = 0.0f;
  result.normal = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
  result.point = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
  return result;
}

// =============================================================================
// Ray vs Capsule Tests
// =============================================================================

LM2_API lm2_rayhit3_f64 lm2_raycast_capsule_f64(lm2_ray3_f64 ray, lm2_v3_f64 start, lm2_v3_f64 end, double radius) {
  lm2_rayhit3_f64 result;

  // Ray-capsule intersection:
  // 1. Find closest point on capsule line segment to ray
  // 2. Treat that as a moving sphere and find intersection

  lm2_v3_f64 seg_dir = lm2_v3_sub_f64(end, start);
  lm2_v3_f64 ray_to_start = lm2_v3_sub_f64(start, ray.origin);

  double seg_len_sq = lm2_v3_dot_f64(seg_dir, seg_dir);
  double ray_dot_seg = lm2_v3_dot_f64(ray.direction, seg_dir);
  double ray_to_start_dot_seg = lm2_v3_dot_f64(ray_to_start, seg_dir);
  double ray_dot_ray = lm2_v3_dot_f64(ray.direction, ray.direction);
  double ray_to_start_dot_ray = lm2_v3_dot_f64(ray_to_start, ray.direction);

  // Parameters for closest points on infinite lines
  double denom = lm2_sub_f64(lm2_mul_f64(seg_len_sq, ray_dot_ray), lm2_mul_f64(ray_dot_seg, ray_dot_seg));

  const double epsilon = LM2_RAYCAST3_EPSILON_F64;

  double best_t = ray.t_max;
  bool found_hit = false;
  lm2_v3_f64 best_point, best_normal;

  // Check if ray and segment are parallel
  if (lm2_abs_f64(denom) < epsilon) {
    // Parallel case - check spheres at endpoints
    // Check start sphere
    lm2_rayhit3_f64 start_hit = lm2_raycast_sphere_f64(ray, start, radius);
    if (start_hit.hit && start_hit.t < best_t) {
      best_t = start_hit.t;
      best_point = start_hit.point;
      best_normal = start_hit.normal;
      found_hit = true;
    }

    // Check end sphere
    lm2_rayhit3_f64 end_hit = lm2_raycast_sphere_f64(ray, end, radius);
    if (end_hit.hit && end_hit.t < best_t) {
      best_t = end_hit.t;
      best_point = end_hit.point;
      best_normal = end_hit.normal;
      found_hit = true;
    }
  } else {
    // Non-parallel case - sweep sphere along segment
    // For each t along ray, find closest point on segment and check distance
    // This requires solving for when distance equals radius

    // We'll check multiple samples and the endpoint spheres
    // For a robust solution, we check endpoint spheres and solve the quadratic

    // Check start sphere
    lm2_rayhit3_f64 start_hit = lm2_raycast_sphere_f64(ray, start, radius);
    if (start_hit.hit && start_hit.t < best_t) {
      best_t = start_hit.t;
      best_point = start_hit.point;
      best_normal = start_hit.normal;
      found_hit = true;
    }

    // Check end sphere
    lm2_rayhit3_f64 end_hit = lm2_raycast_sphere_f64(ray, end, radius);
    if (end_hit.hit && end_hit.t < best_t) {
      best_t = end_hit.t;
      best_point = end_hit.point;
      best_normal = end_hit.normal;
      found_hit = true;
    }

    // Check cylinder portion (infinite cylinder, then clamp to segment)
    // Distance from ray point to line segment as function of t
    // Minimize: ||ray_origin + t*ray_dir - (start + s*seg_dir)||^2 where 0 <= s <= 1

    // For cylinder, solve quadratic for when distance = radius
    lm2_v3_f64 m = lm2_v3_sub_f64(ray.origin, start);
    lm2_v3_f64 n = ray.direction;
    lm2_v3_f64 d = seg_dir;

    double md = lm2_v3_dot_f64(m, d);
    double nd = lm2_v3_dot_f64(n, d);
    double dd = lm2_v3_dot_f64(d, d);
    double nn = lm2_v3_dot_f64(n, n);
    double mn = lm2_v3_dot_f64(m, n);
    double mm = lm2_v3_dot_f64(m, m);

    // Only check if segment has length
    if (dd > epsilon) {
      double inv_dd = lm2_div_f64(1.0, dd);

      // Quadratic coefficients for distance squared = radius squared
      double a = lm2_sub_f64(nn, lm2_mul_f64(lm2_mul_f64(nd, nd), inv_dd));
      double b = lm2_sub_f64(mn, lm2_mul_f64(lm2_mul_f64(nd, md), inv_dd));
      double c = lm2_sub_f64(mm, lm2_mul_f64(lm2_mul_f64(md, md), inv_dd));
      c = lm2_sub_f64(c, lm2_mul_f64(radius, radius));

      // Solve quadratic a*t^2 + 2*b*t + c = 0
      double discriminant = lm2_sub_f64(lm2_mul_f64(b, b), lm2_mul_f64(a, c));

      if (discriminant >= 0.0 && lm2_abs_f64(a) > epsilon) {
        double sqrt_disc = lm2_sqrt_f64(discriminant);
        double t1 = lm2_div_f64(lm2_sub_f64(lm2_mul_f64(-1.0, b), sqrt_disc), a);
        double t2 = lm2_div_f64(lm2_add_f64(lm2_mul_f64(-1.0, b), sqrt_disc), a);

        // Check both solutions
        for (int i = 0; i < 2; i++) {
          double t = (i == 0) ? t1 : t2;

          if (t >= 0.0 && t <= ray.t_max && t < best_t) {
            // Check if corresponding point on segment is within bounds
            double s = lm2_mul_f64(lm2_add_f64(md, lm2_mul_f64(nd, t)), inv_dd);

            if (s >= 0.0 && s <= 1.0) {
              // Valid hit on cylinder portion
              lm2_v3_f64 point = lm2_ray3_point_at_f64(ray, t);
              lm2_v3_f64 seg_point = lm2_v3_add_f64(start, lm2_v3_mul_s_f64(seg_dir, s));
              lm2_v3_f64 normal = lm2_v3_normalize_f64(lm2_v3_sub_f64(point, seg_point));

              best_t = t;
              best_point = point;
              best_normal = normal;
              found_hit = true;
            }
          }
        }
      }
    }
  }

  if (found_hit) {
    result.hit = true;
    result.t = best_t;
    result.point = best_point;
    result.normal = best_normal;
  } else {
    result.hit = false;
    result.t = 0.0;
    result.normal = (lm2_v3_f64) {0.0, 0.0, 0.0};
    result.point = (lm2_v3_f64) {0.0, 0.0, 0.0};
  }

  return result;
}

LM2_API lm2_rayhit3_f32 lm2_raycast_capsule_f32(lm2_ray3_f32 ray, lm2_v3_f32 start, lm2_v3_f32 end, float radius) {
  lm2_rayhit3_f32 result;

  lm2_v3_f32 seg_dir = lm2_v3_sub_f32(end, start);
  lm2_v3_f32 ray_to_start = lm2_v3_sub_f32(start, ray.origin);

  float seg_len_sq = lm2_v3_dot_f32(seg_dir, seg_dir);
  float ray_dot_seg = lm2_v3_dot_f32(ray.direction, seg_dir);
  float ray_to_start_dot_seg = lm2_v3_dot_f32(ray_to_start, seg_dir);
  float ray_dot_ray = lm2_v3_dot_f32(ray.direction, ray.direction);
  float ray_to_start_dot_ray = lm2_v3_dot_f32(ray_to_start, ray.direction);

  float denom = lm2_sub_f32(lm2_mul_f32(seg_len_sq, ray_dot_ray), lm2_mul_f32(ray_dot_seg, ray_dot_seg));

  const float epsilon = LM2_RAYCAST3_EPSILON_F32;

  float best_t = ray.t_max;
  bool found_hit = false;
  lm2_v3_f32 best_point, best_normal;

  if (lm2_abs_f32(denom) < epsilon) {
    lm2_rayhit3_f32 start_hit = lm2_raycast_sphere_f32(ray, start, radius);
    if (start_hit.hit && start_hit.t < best_t) {
      best_t = start_hit.t;
      best_point = start_hit.point;
      best_normal = start_hit.normal;
      found_hit = true;
    }

    lm2_rayhit3_f32 end_hit = lm2_raycast_sphere_f32(ray, end, radius);
    if (end_hit.hit && end_hit.t < best_t) {
      best_t = end_hit.t;
      best_point = end_hit.point;
      best_normal = end_hit.normal;
      found_hit = true;
    }
  } else {
    lm2_rayhit3_f32 start_hit = lm2_raycast_sphere_f32(ray, start, radius);
    if (start_hit.hit && start_hit.t < best_t) {
      best_t = start_hit.t;
      best_point = start_hit.point;
      best_normal = start_hit.normal;
      found_hit = true;
    }

    lm2_rayhit3_f32 end_hit = lm2_raycast_sphere_f32(ray, end, radius);
    if (end_hit.hit && end_hit.t < best_t) {
      best_t = end_hit.t;
      best_point = end_hit.point;
      best_normal = end_hit.normal;
      found_hit = true;
    }

    lm2_v3_f32 m = lm2_v3_sub_f32(ray.origin, start);
    lm2_v3_f32 n = ray.direction;
    lm2_v3_f32 d = seg_dir;

    float md = lm2_v3_dot_f32(m, d);
    float nd = lm2_v3_dot_f32(n, d);
    float dd = lm2_v3_dot_f32(d, d);
    float nn = lm2_v3_dot_f32(n, n);
    float mn = lm2_v3_dot_f32(m, n);
    float mm = lm2_v3_dot_f32(m, m);

    if (dd > epsilon) {
      float inv_dd = lm2_div_f32(1.0f, dd);

      float a = lm2_sub_f32(nn, lm2_mul_f32(lm2_mul_f32(nd, nd), inv_dd));
      float b = lm2_sub_f32(mn, lm2_mul_f32(lm2_mul_f32(nd, md), inv_dd));
      float c = lm2_sub_f32(mm, lm2_mul_f32(lm2_mul_f32(md, md), inv_dd));
      c = lm2_sub_f32(c, lm2_mul_f32(radius, radius));

      float discriminant = lm2_sub_f32(lm2_mul_f32(b, b), lm2_mul_f32(a, c));

      if (discriminant >= 0.0f && lm2_abs_f32(a) > epsilon) {
        float sqrt_disc = lm2_sqrt_f32(discriminant);
        float t1 = lm2_div_f32(lm2_sub_f32(lm2_mul_f32(-1.0f, b), sqrt_disc), a);
        float t2 = lm2_div_f32(lm2_add_f32(lm2_mul_f32(-1.0f, b), sqrt_disc), a);

        for (int i = 0; i < 2; i++) {
          float t = (i == 0) ? t1 : t2;

          if (t >= 0.0f && t <= ray.t_max && t < best_t) {
            float s = lm2_mul_f32(lm2_add_f32(md, lm2_mul_f32(nd, t)), inv_dd);

            if (s >= 0.0f && s <= 1.0f) {
              lm2_v3_f32 point = lm2_ray3_point_at_f32(ray, t);
              lm2_v3_f32 seg_point = lm2_v3_add_f32(start, lm2_v3_mul_s_f32(seg_dir, s));
              lm2_v3_f32 normal = lm2_v3_normalize_f32(lm2_v3_sub_f32(point, seg_point));

              best_t = t;
              best_point = point;
              best_normal = normal;
              found_hit = true;
            }
          }
        }
      }
    }
  }

  if (found_hit) {
    result.hit = true;
    result.t = best_t;
    result.point = best_point;
    result.normal = best_normal;
  } else {
    result.hit = false;
    result.t = 0.0f;
    result.normal = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
    result.point = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
  }

  return result;
}

// =============================================================================
// Ray vs Edge/Line Segment Tests
// =============================================================================

LM2_API lm2_rayhit3_f64 lm2_raycast_edge_f64(lm2_ray3_f64 ray, lm2_v3_f64 edge_start, lm2_v3_f64 edge_end, double tolerance) {
  lm2_rayhit3_f64 result;

  // Ray-edge closest approach
  // Find closest points between ray and line segment
  // If distance is within tolerance, report hit

  lm2_v3_f64 edge_dir = lm2_v3_sub_f64(edge_end, edge_start);
  lm2_v3_f64 w0 = lm2_v3_sub_f64(ray.origin, edge_start);

  double a = lm2_v3_dot_f64(ray.direction, ray.direction);  // always >= 0
  double b = lm2_v3_dot_f64(ray.direction, edge_dir);
  double c = lm2_v3_dot_f64(edge_dir, edge_dir);  // always >= 0
  double d = lm2_v3_dot_f64(ray.direction, w0);
  double e = lm2_v3_dot_f64(edge_dir, w0);

  double denom = lm2_sub_f64(lm2_mul_f64(a, c), lm2_mul_f64(b, b));
  const double epsilon = LM2_RAYCAST3_EPSILON_F64;

  double t_ray, t_edge;

  if (lm2_abs_f64(denom) < epsilon) {
    // Lines are parallel
    t_ray = 0.0;
    t_edge = (c > epsilon) ? lm2_div_f64(e, c) : 0.0;
    // Clamp edge parameter
    if (t_edge < 0.0) t_edge = 0.0;
    else if (t_edge > 1.0)
      t_edge = 1.0;
  } else {
    // General case
    t_ray = lm2_div_f64(lm2_sub_f64(lm2_mul_f64(b, e), lm2_mul_f64(c, d)), denom);
    t_edge = lm2_div_f64(lm2_sub_f64(lm2_mul_f64(a, e), lm2_mul_f64(b, d)), denom);

    // Clamp ray parameter to valid range
    if (t_ray < 0.0) t_ray = 0.0;
    else if (t_ray > ray.t_max)
      t_ray = ray.t_max;

    // Clamp edge parameter to [0, 1]
    if (t_edge < 0.0) {
      t_edge = 0.0;
      // Recompute t_ray for clamped edge
      lm2_v3_f64 edge_point = edge_start;
      lm2_v3_f64 diff = lm2_v3_sub_f64(edge_point, ray.origin);
      t_ray = lm2_v3_dot_f64(diff, ray.direction);
      if (t_ray < 0.0) t_ray = 0.0;
      else if (t_ray > ray.t_max)
        t_ray = ray.t_max;
    } else if (t_edge > 1.0) {
      t_edge = 1.0;
      // Recompute t_ray for clamped edge
      lm2_v3_f64 edge_point = edge_end;
      lm2_v3_f64 diff = lm2_v3_sub_f64(edge_point, ray.origin);
      t_ray = lm2_v3_dot_f64(diff, ray.direction);
      if (t_ray < 0.0) t_ray = 0.0;
      else if (t_ray > ray.t_max)
        t_ray = ray.t_max;
    }
  }

  // Compute closest points
  lm2_v3_f64 ray_point = lm2_ray3_point_at_f64(ray, t_ray);
  lm2_v3_f64 edge_point = lm2_v3_add_f64(edge_start, lm2_v3_mul_s_f64(edge_dir, t_edge));

  // Check distance
  double dist = lm2_v3_distance_f64(ray_point, edge_point);

  if (dist <= tolerance) {
    result.hit = true;
    result.t = t_ray;
    result.point = ray_point;
    // Normal points from edge to ray
    if (dist > epsilon) {
      result.normal = lm2_v3_normalize_f64(lm2_v3_sub_f64(ray_point, edge_point));
    } else {
      // Ray intersects edge, use perpendicular to both
      lm2_v3_f64 cross = lm2_v3_cross_f64(ray.direction, edge_dir);
      double cross_len = lm2_v3_length_f64(cross);
      if (cross_len > epsilon) {
        result.normal = lm2_v3_normalize_f64(cross);
      } else {
        // Parallel, use any perpendicular
        result.normal = (lm2_v3_f64) {1.0, 0.0, 0.0};
      }
    }
  } else {
    result.hit = false;
    result.t = 0.0;
    result.normal = (lm2_v3_f64) {0.0, 0.0, 0.0};
    result.point = (lm2_v3_f64) {0.0, 0.0, 0.0};
  }

  return result;
}

LM2_API lm2_rayhit3_f32 lm2_raycast_edge_f32(lm2_ray3_f32 ray, lm2_v3_f32 edge_start, lm2_v3_f32 edge_end, float tolerance) {
  lm2_rayhit3_f32 result;

  lm2_v3_f32 edge_dir = lm2_v3_sub_f32(edge_end, edge_start);
  lm2_v3_f32 w0 = lm2_v3_sub_f32(ray.origin, edge_start);

  float a = lm2_v3_dot_f32(ray.direction, ray.direction);
  float b = lm2_v3_dot_f32(ray.direction, edge_dir);
  float c = lm2_v3_dot_f32(edge_dir, edge_dir);
  float d = lm2_v3_dot_f32(ray.direction, w0);
  float e = lm2_v3_dot_f32(edge_dir, w0);

  float denom = lm2_sub_f32(lm2_mul_f32(a, c), lm2_mul_f32(b, b));
  const float epsilon = LM2_RAYCAST3_EPSILON_F32;

  float t_ray, t_edge;

  if (lm2_abs_f32(denom) < epsilon) {
    t_ray = 0.0f;
    t_edge = (c > epsilon) ? lm2_div_f32(e, c) : 0.0f;
    if (t_edge < 0.0f) t_edge = 0.0f;
    else if (t_edge > 1.0f)
      t_edge = 1.0f;
  } else {
    t_ray = lm2_div_f32(lm2_sub_f32(lm2_mul_f32(b, e), lm2_mul_f32(c, d)), denom);
    t_edge = lm2_div_f32(lm2_sub_f32(lm2_mul_f32(a, e), lm2_mul_f32(b, d)), denom);

    if (t_ray < 0.0f) t_ray = 0.0f;
    else if (t_ray > ray.t_max)
      t_ray = ray.t_max;

    if (t_edge < 0.0f) {
      t_edge = 0.0f;
      lm2_v3_f32 edge_point = edge_start;
      lm2_v3_f32 diff = lm2_v3_sub_f32(edge_point, ray.origin);
      t_ray = lm2_v3_dot_f32(diff, ray.direction);
      if (t_ray < 0.0f) t_ray = 0.0f;
      else if (t_ray > ray.t_max)
        t_ray = ray.t_max;
    } else if (t_edge > 1.0f) {
      t_edge = 1.0f;
      lm2_v3_f32 edge_point = edge_end;
      lm2_v3_f32 diff = lm2_v3_sub_f32(edge_point, ray.origin);
      t_ray = lm2_v3_dot_f32(diff, ray.direction);
      if (t_ray < 0.0f) t_ray = 0.0f;
      else if (t_ray > ray.t_max)
        t_ray = ray.t_max;
    }
  }

  lm2_v3_f32 ray_point = lm2_ray3_point_at_f32(ray, t_ray);
  lm2_v3_f32 edge_point = lm2_v3_add_f32(edge_start, lm2_v3_mul_s_f32(edge_dir, t_edge));

  float dist = lm2_v3_distance_f32(ray_point, edge_point);

  if (dist <= tolerance) {
    result.hit = true;
    result.t = t_ray;
    result.point = ray_point;
    if (dist > epsilon) {
      result.normal = lm2_v3_normalize_f32(lm2_v3_sub_f32(ray_point, edge_point));
    } else {
      lm2_v3_f32 cross = lm2_v3_cross_f32(ray.direction, edge_dir);
      float cross_len = lm2_v3_length_f32(cross);
      if (cross_len > epsilon) {
        result.normal = lm2_v3_normalize_f32(cross);
      } else {
        result.normal = (lm2_v3_f32) {1.0f, 0.0f, 0.0f};
      }
    }
  } else {
    result.hit = false;
    result.t = 0.0f;
    result.normal = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
    result.point = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
  }

  return result;
}

// =============================================================================
// Generic Shape Raycasting - f64
// =============================================================================

LM2_API lm2_rayhit3_f64 lm2_raycast_shape3_f64(lm2_ray3_f64 ray, lm2_shape3_f64 shape) {
  LM2_ASSERT(shape.data != NULL);

  lm2_rayhit3_f64 result;
  result.hit = false;
  result.t = 0.0;
  result.point = (lm2_v3_f64) {0.0, 0.0, 0.0};
  result.normal = (lm2_v3_f64) {0.0, 0.0, 0.0};

  switch (shape.type) {
    case LM2_SHAPE3_SPHERE: {
      lm2_sphere_f64* sphere = (lm2_sphere_f64*)shape.data;
      result = lm2_raycast_sphere_f64(ray, sphere->center, sphere->radius);
      break;
    }

    case LM2_SHAPE3_CAPSULE: {
      lm2_capsule3_f64* capsule = (lm2_capsule3_f64*)shape.data;
      result = lm2_raycast_capsule_f64(ray, capsule->start, capsule->end, capsule->radius);
      break;
    }

    case LM2_SHAPE3_CUBOID: {
      lm2_cuboid_f64* cuboid = (lm2_cuboid_f64*)shape.data;
      result = lm2_raycast_aabb3_f64(ray, *cuboid);
      break;
    }

    case LM2_SHAPE3_TRIANGLE: {
      lm2_triangle3_f64* tri = (lm2_triangle3_f64*)shape.data;
      result = lm2_raycast_triangle_f64(ray, (*tri)[0], (*tri)[1], (*tri)[2]);
      break;
    }

    case LM2_SHAPE3_EDGE: {
      lm2_edge3_f64* edge = (lm2_edge3_f64*)shape.data;
      result = lm2_raycast_edge_f64(ray, edge->start, edge->end, LM2_RAYCAST3_EPSILON_F64);
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

LM2_API lm2_rayhit3_f32 lm2_raycast_shape3_f32(lm2_ray3_f32 ray, lm2_shape3_f32 shape) {
  LM2_ASSERT(shape.data != NULL);

  lm2_rayhit3_f32 result;
  result.hit = false;
  result.t = 0.0f;
  result.point = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
  result.normal = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};

  switch (shape.type) {
    case LM2_SHAPE3_SPHERE: {
      lm2_sphere_f32* sphere = (lm2_sphere_f32*)shape.data;
      result = lm2_raycast_sphere_f32(ray, sphere->center, sphere->radius);
      break;
    }

    case LM2_SHAPE3_CAPSULE: {
      lm2_capsule3_f32* capsule = (lm2_capsule3_f32*)shape.data;
      result = lm2_raycast_capsule_f32(ray, capsule->start, capsule->end, capsule->radius);
      break;
    }

    case LM2_SHAPE3_CUBOID: {
      lm2_cuboid_f32* cuboid = (lm2_cuboid_f32*)shape.data;
      result = lm2_raycast_aabb3_f32(ray, *cuboid);
      break;
    }

    case LM2_SHAPE3_TRIANGLE: {
      lm2_triangle3_f32* tri = (lm2_triangle3_f32*)shape.data;
      result = lm2_raycast_triangle_f32(ray, (*tri)[0], (*tri)[1], (*tri)[2]);
      break;
    }

    case LM2_SHAPE3_EDGE: {
      lm2_edge3_f32* edge = (lm2_edge3_f32*)shape.data;
      result = lm2_raycast_edge_f32(ray, edge->start, edge->end, LM2_RAYCAST3_EPSILON_F32);
      break;
    }

    default:
      break;
  }

  return result;
}
