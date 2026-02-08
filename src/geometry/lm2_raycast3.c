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

#include "lm2/geometry/lm2_raycast3.h"
#include "lm2/scalar/lm2_safe_ops.h"
#include "lm2/scalar/lm2_scalar.h"
#include "lm2/vectors/lm2_vector_specifics.h"

// =============================================================================
// 3D Ray Construction - f64
// =============================================================================

LM2_API lm2_ray3_f64 lm2_ray3_make_f64(lm2_v3f64 origin, lm2_v3f64 direction, double t_max) {
  lm2_ray3_f64 result;
  result.origin = origin;
  result.direction = direction;
  result.t_max = t_max;
  return result;
}

LM2_API lm2_ray3_f64 lm2_ray3_from_points_f64(lm2_v3f64 start, lm2_v3f64 end) {
  lm2_ray3_f64 result;
  result.origin = start;
  lm2_v3f64 diff = lm2_sub_lm2_v3f64(end, start);
  double length = lm2_length_v3f64(diff);
  result.direction = lm2_normalize_v3f64(diff);
  result.t_max = length;
  return result;
}

LM2_API lm2_v3f64 lm2_ray3_point_at_f64(lm2_ray3_f64 ray, double t) {
  lm2_v3f64 scaled_dir = lm2_mul_lm2_v3f64_double(ray.direction, t);
  return lm2_add_lm2_v3f64(ray.origin, scaled_dir);
}

// =============================================================================
// 3D Ray Construction - f32
// =============================================================================

LM2_API lm2_ray3_f32 lm2_ray3_make_f32(lm2_v3f32 origin, lm2_v3f32 direction, float t_max) {
  lm2_ray3_f32 result;
  result.origin = origin;
  result.direction = direction;
  result.t_max = t_max;
  return result;
}

LM2_API lm2_ray3_f32 lm2_ray3_from_points_f32(lm2_v3f32 start, lm2_v3f32 end) {
  lm2_ray3_f32 result;
  result.origin = start;
  lm2_v3f32 diff = lm2_sub_lm2_v3f32(end, start);
  float length = lm2_length_v3f32(diff);
  result.direction = lm2_normalize_v3f32(diff);
  result.t_max = length;
  return result;
}

LM2_API lm2_v3f32 lm2_ray3_point_at_f32(lm2_ray3_f32 ray, float t) {
  lm2_v3f32 scaled_dir = lm2_mul_lm2_v3f32_float(ray.direction, t);
  return lm2_add_lm2_v3f32(ray.origin, scaled_dir);
}

// =============================================================================
// 3D Ray vs Primitive Tests - f64
// =============================================================================

LM2_API lm2_rayhit3_f64 lm2_raycast_sphere_f64(lm2_ray3_f64 ray, lm2_v3f64 center, double radius) {
  lm2_rayhit3_f64 result;

  // Ray-sphere intersection using quadratic formula
  lm2_v3f64 oc = lm2_sub_lm2_v3f64(ray.origin, center);
  double a = lm2_dot_v3f64(ray.direction, ray.direction);
  double b = lm2_mul_f64(2.0, lm2_dot_v3f64(oc, ray.direction));
  double c = lm2_sub_f64(lm2_dot_v3f64(oc, oc), lm2_mul_f64(radius, radius));
  double discriminant = lm2_sub_f64(lm2_mul_f64(b, b), lm2_mul_f64(lm2_mul_f64(4.0, a), c));

  if (discriminant < 0.0) {
    result.hit = false;
    result.t = 0.0;
    result.normal = (lm2_v3f64) {0.0, 0.0, 0.0};
    result.point = (lm2_v3f64) {0.0, 0.0, 0.0};
  } else {
    double sqrt_disc = lm2_sqrt_f64(discriminant);
    double t = lm2_div_f64(lm2_sub_f64(lm2_mul_f64(-1.0, b), sqrt_disc), lm2_mul_f64(2.0, a));

    if (t < 0.0 || t > ray.t_max) {
      result.hit = false;
      result.t = 0.0;
      result.normal = (lm2_v3f64) {0.0, 0.0, 0.0};
      result.point = (lm2_v3f64) {0.0, 0.0, 0.0};
    } else {
      result.hit = true;
      result.t = t;
      result.point = lm2_ray3_point_at_f64(ray, t);
      result.normal = lm2_normalize_v3f64(lm2_sub_lm2_v3f64(result.point, center));
    }
  }

  return result;
}

LM2_API lm2_rayhit3_f64 lm2_raycast_aabb3_f64(lm2_ray3_f64 ray, lm2_r3f64 aabb) {
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
      result.normal = (lm2_v3f64) {0.0, 0.0, 0.0};
      result.point = (lm2_v3f64) {0.0, 0.0, 0.0};
      return result;
    }
  }

  result.hit = true;
  result.t = t_min;
  result.point = lm2_ray3_point_at_f64(ray, t_min);

  // Compute normal
  lm2_v3f64 center = lm2_mul_lm2_v3f64_double(lm2_add_lm2_v3f64(aabb.min, aabb.max), 0.5);
  lm2_v3f64 local = lm2_sub_lm2_v3f64(result.point, center);
  lm2_v3f64 abs_local = lm2_abs_lm2_v3f64(local);

  if (abs_local.x > abs_local.y && abs_local.x > abs_local.z) {
    result.normal = (lm2_v3f64) {local.x > 0.0 ? 1.0 : -1.0, 0.0, 0.0};
  } else if (abs_local.y > abs_local.z) {
    result.normal = (lm2_v3f64) {0.0, local.y > 0.0 ? 1.0 : -1.0, 0.0};
  } else {
    result.normal = (lm2_v3f64) {0.0, 0.0, local.z > 0.0 ? 1.0 : -1.0};
  }

  return result;
}

LM2_API lm2_rayhit3_f64 lm2_raycast_triangle_f64(lm2_ray3_f64 ray, lm2_v3f64 v0, lm2_v3f64 v1, lm2_v3f64 v2) {
  lm2_rayhit3_f64 result;

  // Möller-Trumbore intersection algorithm
  const double epsilon = LM2_RAYCAST3_EPSILON_F64;

  lm2_v3f64 edge1 = lm2_sub_lm2_v3f64(v1, v0);
  lm2_v3f64 edge2 = lm2_sub_lm2_v3f64(v2, v0);
  lm2_v3f64 h = lm2_cross_v3f64(ray.direction, edge2);
  double a = lm2_dot_v3f64(edge1, h);

  if (lm2_abs_f64(a) < epsilon) {
    result.hit = false;
    result.t = 0.0;
    result.normal = (lm2_v3f64) {0.0, 0.0, 0.0};
    result.point = (lm2_v3f64) {0.0, 0.0, 0.0};
    return result;
  }

  double f = lm2_div_f64(1.0, a);
  lm2_v3f64 s = lm2_sub_lm2_v3f64(ray.origin, v0);
  double u = lm2_mul_f64(f, lm2_dot_v3f64(s, h));

  if (u < 0.0 || u > 1.0) {
    result.hit = false;
    result.t = 0.0;
    result.normal = (lm2_v3f64) {0.0, 0.0, 0.0};
    result.point = (lm2_v3f64) {0.0, 0.0, 0.0};
    return result;
  }

  lm2_v3f64 q = lm2_cross_v3f64(s, edge1);
  double v = lm2_mul_f64(f, lm2_dot_v3f64(ray.direction, q));

  if (v < 0.0 || lm2_add_f64(u, v) > 1.0) {
    result.hit = false;
    result.t = 0.0;
    result.normal = (lm2_v3f64) {0.0, 0.0, 0.0};
    result.point = (lm2_v3f64) {0.0, 0.0, 0.0};
    return result;
  }

  double t = lm2_mul_f64(f, lm2_dot_v3f64(edge2, q));

  if (t > epsilon && t <= ray.t_max) {
    result.hit = true;
    result.t = t;
    result.point = lm2_ray3_point_at_f64(ray, t);
    result.normal = lm2_normalize_v3f64(lm2_cross_v3f64(edge1, edge2));
  } else {
    result.hit = false;
    result.t = 0.0;
    result.normal = (lm2_v3f64) {0.0, 0.0, 0.0};
    result.point = (lm2_v3f64) {0.0, 0.0, 0.0};
  }

  return result;
}

LM2_API lm2_rayhit3_f64 lm2_raycast_plane_f64(lm2_ray3_f64 ray, lm2_v3f64 plane_point, lm2_v3f64 plane_normal) {
  lm2_rayhit3_f64 result;

  const double epsilon = LM2_RAYCAST3_EPSILON_F64;

  double denom = lm2_dot_v3f64(plane_normal, ray.direction);

  if (lm2_abs_f64(denom) > epsilon) {
    lm2_v3f64 p0l0 = lm2_sub_lm2_v3f64(plane_point, ray.origin);
    double t = lm2_div_f64(lm2_dot_v3f64(p0l0, plane_normal), denom);

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
  result.normal = (lm2_v3f64) {0.0, 0.0, 0.0};
  result.point = (lm2_v3f64) {0.0, 0.0, 0.0};
  return result;
}

// =============================================================================
// 3D Ray vs Primitive Tests - f32
// =============================================================================

LM2_API lm2_rayhit3_f32 lm2_raycast_sphere_f32(lm2_ray3_f32 ray, lm2_v3f32 center, float radius) {
  lm2_rayhit3_f32 result;

  // Ray-sphere intersection using quadratic formula
  lm2_v3f32 oc = lm2_sub_lm2_v3f32(ray.origin, center);
  float a = lm2_dot_v3f32(ray.direction, ray.direction);
  float b = lm2_mul_f32(2.0f, lm2_dot_v3f32(oc, ray.direction));
  float c = lm2_sub_f32(lm2_dot_v3f32(oc, oc), lm2_mul_f32(radius, radius));
  float discriminant = lm2_sub_f32(lm2_mul_f32(b, b), lm2_mul_f32(lm2_mul_f32(4.0f, a), c));

  if (discriminant < 0.0f) {
    result.hit = false;
    result.t = 0.0f;
    result.normal = (lm2_v3f32) {0.0f, 0.0f, 0.0f};
    result.point = (lm2_v3f32) {0.0f, 0.0f, 0.0f};
  } else {
    float sqrt_disc = lm2_sqrt_f32(discriminant);
    float t = lm2_div_f32(lm2_sub_f32(lm2_mul_f32(-1.0f, b), sqrt_disc), lm2_mul_f32(2.0f, a));

    if (t < 0.0f || t > ray.t_max) {
      result.hit = false;
      result.t = 0.0f;
      result.normal = (lm2_v3f32) {0.0f, 0.0f, 0.0f};
      result.point = (lm2_v3f32) {0.0f, 0.0f, 0.0f};
    } else {
      result.hit = true;
      result.t = t;
      result.point = lm2_ray3_point_at_f32(ray, t);
      result.normal = lm2_normalize_v3f32(lm2_sub_lm2_v3f32(result.point, center));
    }
  }

  return result;
}

LM2_API lm2_rayhit3_f32 lm2_raycast_aabb3_f32(lm2_ray3_f32 ray, lm2_r3f32 aabb) {
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
      result.normal = (lm2_v3f32) {0.0f, 0.0f, 0.0f};
      result.point = (lm2_v3f32) {0.0f, 0.0f, 0.0f};
      return result;
    }
  }

  result.hit = true;
  result.t = t_min;
  result.point = lm2_ray3_point_at_f32(ray, t_min);

  // Compute normal
  lm2_v3f32 center = lm2_mul_lm2_v3f32_float(lm2_add_lm2_v3f32(aabb.min, aabb.max), 0.5f);
  lm2_v3f32 local = lm2_sub_lm2_v3f32(result.point, center);
  lm2_v3f32 abs_local = lm2_abs_lm2_v3f32(local);

  if (abs_local.x > abs_local.y && abs_local.x > abs_local.z) {
    result.normal = (lm2_v3f32) {local.x > 0.0f ? 1.0f : -1.0f, 0.0f, 0.0f};
  } else if (abs_local.y > abs_local.z) {
    result.normal = (lm2_v3f32) {0.0f, local.y > 0.0f ? 1.0f : -1.0f, 0.0f};
  } else {
    result.normal = (lm2_v3f32) {0.0f, 0.0f, local.z > 0.0f ? 1.0f : -1.0f};
  }

  return result;
}

LM2_API lm2_rayhit3_f32 lm2_raycast_triangle_f32(lm2_ray3_f32 ray, lm2_v3f32 v0, lm2_v3f32 v1, lm2_v3f32 v2) {
  lm2_rayhit3_f32 result;

  // Möller-Trumbore intersection algorithm
  const float epsilon = LM2_RAYCAST3_EPSILON_F32;

  lm2_v3f32 edge1 = lm2_sub_lm2_v3f32(v1, v0);
  lm2_v3f32 edge2 = lm2_sub_lm2_v3f32(v2, v0);
  lm2_v3f32 h = lm2_cross_v3f32(ray.direction, edge2);
  float a = lm2_dot_v3f32(edge1, h);

  if (lm2_abs_f32(a) < epsilon) {
    result.hit = false;
    result.t = 0.0f;
    result.normal = (lm2_v3f32) {0.0f, 0.0f, 0.0f};
    result.point = (lm2_v3f32) {0.0f, 0.0f, 0.0f};
    return result;
  }

  float f = lm2_div_f32(1.0f, a);
  lm2_v3f32 s = lm2_sub_lm2_v3f32(ray.origin, v0);
  float u = lm2_mul_f32(f, lm2_dot_v3f32(s, h));

  if (u < 0.0f || u > 1.0f) {
    result.hit = false;
    result.t = 0.0f;
    result.normal = (lm2_v3f32) {0.0f, 0.0f, 0.0f};
    result.point = (lm2_v3f32) {0.0f, 0.0f, 0.0f};
    return result;
  }

  lm2_v3f32 q = lm2_cross_v3f32(s, edge1);
  float v = lm2_mul_f32(f, lm2_dot_v3f32(ray.direction, q));

  if (v < 0.0f || lm2_add_f32(u, v) > 1.0f) {
    result.hit = false;
    result.t = 0.0f;
    result.normal = (lm2_v3f32) {0.0f, 0.0f, 0.0f};
    result.point = (lm2_v3f32) {0.0f, 0.0f, 0.0f};
    return result;
  }

  float t = lm2_mul_f32(f, lm2_dot_v3f32(edge2, q));

  if (t > epsilon && t <= ray.t_max) {
    result.hit = true;
    result.t = t;
    result.point = lm2_ray3_point_at_f32(ray, t);
    result.normal = lm2_normalize_v3f32(lm2_cross_v3f32(edge1, edge2));
  } else {
    result.hit = false;
    result.t = 0.0f;
    result.normal = (lm2_v3f32) {0.0f, 0.0f, 0.0f};
    result.point = (lm2_v3f32) {0.0f, 0.0f, 0.0f};
  }

  return result;
}

LM2_API lm2_rayhit3_f32 lm2_raycast_plane_f32(lm2_ray3_f32 ray, lm2_v3f32 plane_point, lm2_v3f32 plane_normal) {
  lm2_rayhit3_f32 result;

  const float epsilon = LM2_RAYCAST3_EPSILON_F32;

  float denom = lm2_dot_v3f32(plane_normal, ray.direction);

  if (lm2_abs_f32(denom) > epsilon) {
    lm2_v3f32 p0l0 = lm2_sub_lm2_v3f32(plane_point, ray.origin);
    float t = lm2_div_f32(lm2_dot_v3f32(p0l0, plane_normal), denom);

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
  result.normal = (lm2_v3f32) {0.0f, 0.0f, 0.0f};
  result.point = (lm2_v3f32) {0.0f, 0.0f, 0.0f};
  return result;
}
