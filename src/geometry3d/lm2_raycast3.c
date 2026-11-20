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
#include "lm2/geometry3d/lm2_aabb3.h"
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
  result.direction = lm2_v3_norm_f64(diff);
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
  result.direction = lm2_v3_norm_f32(diff);
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

// Local vector arithmetic permits valid subnormal components in ray queries.
#define LM2_RAY3_VECTOR_HELPERS(suffix, type, hyp)                                             \
  static lm2_v3_##suffix _lm2_ray_sub_##suffix(lm2_v3_##suffix a, lm2_v3_##suffix b) {         \
    lm2_v3_##suffix r = {a.x - b.x, a.y - b.y, a.z - b.z};                                     \
    return r;                                                                                  \
  }                                                                                            \
  static lm2_v3_##suffix _lm2_ray_add_##suffix(lm2_v3_##suffix a, lm2_v3_##suffix b) {         \
    lm2_v3_##suffix r = {a.x + b.x, a.y + b.y, a.z + b.z};                                     \
    return r;                                                                                  \
  }                                                                                            \
  static lm2_v3_##suffix _lm2_ray_mul_##suffix(lm2_v3_##suffix a, type b) {                    \
    lm2_v3_##suffix r = {a.x * b, a.y * b, a.z * b};                                           \
    return r;                                                                                  \
  }                                                                                            \
  static type _lm2_ray_dot_##suffix(lm2_v3_##suffix a, lm2_v3_##suffix b) {                    \
    return a.x * b.x + a.y * b.y + a.z * b.z;                                                  \
  }                                                                                            \
  static lm2_v3_##suffix _lm2_ray_cross_##suffix(lm2_v3_##suffix a, lm2_v3_##suffix b) {       \
    lm2_v3_##suffix r = {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x}; \
    return r;                                                                                  \
  }                                                                                            \
  static lm2_v3_##suffix _lm2_ray_norm_##suffix(lm2_v3_##suffix v) {                           \
    type len = hyp(hyp(v.x, v.y), v.z);                                                        \
    if (len == 0) {                                                                            \
      lm2_v3_##suffix r = {0};                                                                 \
      return r;                                                                                \
    }                                                                                          \
    lm2_v3_##suffix r = {v.x / len, v.y / len, v.z / len};                                     \
    return r;                                                                                  \
  }
LM2_RAY3_VECTOR_HELPERS(f64, double, hypot)
LM2_RAY3_VECTOR_HELPERS(f32, float, hypotf)
#undef LM2_RAY3_VECTOR_HELPERS

LM2_API lm2_rayhit3_f64 lm2_raycast_sphere_f64(lm2_ray3_f64 ray, lm2_v3_f64 center, double radius) {
  lm2_rayhit3_f64 result = {0};
  if (ray.t_max < 0.0) return result;
  lm2_v3_f64 oc = _lm2_ray_sub_f64(ray.origin, center);
  double dir_len = hypot(hypot(ray.direction.x, ray.direction.y), ray.direction.z);
  radius = fabs(radius);
  if (dir_len == 0.0) {
    if (hypot(hypot(oc.x, oc.y), oc.z) <= radius) {
      result.hit = true;
      result.point = ray.origin;
    }
    return result;
  }
  lm2_v3_f64 unit = {ray.direction.x / dir_len, ray.direction.y / dir_len, ray.direction.z / dir_len};
  lm2_v3_f64 cross = _lm2_ray_cross_f64(oc, unit);
  double perpendicular = hypot(hypot(cross.x, cross.y), cross.z);
  if (perpendicular > radius) return result;
  // A scaled half-chord avoids both radius-squared overflow and underflow.
  double ratio = radius > 0.0 ? perpendicular / radius : 0.0;
  double half_chord = radius * sqrt((1.0 - ratio) * (1.0 + ratio));
  double along = -_lm2_ray_dot_f64(oc, unit);
  double t = (along - half_chord) / dir_len;
  double radial_along = -half_chord;
  if (t < 0.0) {
    t = (along + half_chord) / dir_len;
    radial_along = half_chord;
  }
  if (t < 0.0 || t > ray.t_max) return result;
  result.hit = true;
  result.t = t;
  // The parameter can round to the sphere center for distant origins. Form
  // the radial vector from the closest offset and the selected half-chord.
  lm2_v3_f64 closest = _lm2_ray_cross_f64(unit, cross);
  lm2_v3_f64 radial = _lm2_ray_add_f64(closest, _lm2_ray_mul_f64(unit, radial_along));
  result.point = _lm2_ray_add_f64(center, radial);
  result.normal = _lm2_ray_norm_f64(radial);
  return result;
}

LM2_API lm2_rayhit3_f64 lm2_raycast_aabb3_f64(lm2_ray3_f64 ray, lm2_r3_f64 aabb) {
  lm2_rayhit3_f64 result = {0};
  if (ray.t_max < 0.0) return result;

  // Ray-AABB intersection using slab method
  double t_min = 0.0;
  double t_max = ray.t_max;
  lm2_v3_f64 entry_normal = {0.0, 0.0, 0.0};

  for (int i = 0; i < 3; ++i) {
    // A small nonzero component can still cross a slab along a long ray.
    if (ray.direction.e[i] == 0.0) {
      // Ray is parallel to slab - check if origin is within slab bounds
      if (ray.origin.e[i] < aabb.min.e[i] || ray.origin.e[i] > aabb.max.e[i]) {
        result.hit = false;
        result.t = 0.0;
        result.normal = (lm2_v3_f64) {0.0, 0.0, 0.0};
        result.point = (lm2_v3_f64) {0.0, 0.0, 0.0};
        return result;
      }
      continue;
    }

    // Division may overflow to infinity for a subnormal component; that is a
    // valid slab bound and must not reject an otherwise finite intersection.
    double t0 = (aabb.min.e[i] - ray.origin.e[i]) / ray.direction.e[i];
    double t1 = (aabb.max.e[i] - ray.origin.e[i]) / ray.direction.e[i];

    if (ray.direction.e[i] < 0.0) {
      double temp = t0;
      t0 = t1;
      t1 = temp;
    }

    if (t0 > t_min) {
      t_min = t0;
      entry_normal = (lm2_v3_f64) {0.0, 0.0, 0.0};
      entry_normal.e[i] = ray.direction.e[i] < 0.0 ? 1.0 : -1.0;
    }
    t_max = t1 < t_max ? t1 : t_max;

    if (t_max < t_min) {
      result.hit = false;
      result.t = 0.0;
      result.normal = (lm2_v3_f64) {0.0, 0.0, 0.0};
      result.point = (lm2_v3_f64) {0.0, 0.0, 0.0};
      return result;
    }
  }

  result.hit = true;
  result.t = t_min;
  for (int i = 0; i < 3; ++i) result.point.e[i] = ray.origin.e[i] + ray.direction.e[i] * t_min;

  if (t_min > 0.0) {
    result.normal = entry_normal;
    return result;
  }

  // Surface-origin hits use the outward face normal. For an origin strictly
  // inside, retain the previous fallback direction.
  for (int i = 0; i < 3; ++i) {
    if (ray.origin.e[i] == aabb.min.e[i] || ray.origin.e[i] == aabb.max.e[i]) {
      result.normal = (lm2_v3_f64) {0.0, 0.0, 0.0};
      result.normal.e[i] = ray.origin.e[i] == aabb.min.e[i] ? -1.0 : 1.0;
      return result;
    }
  }

  // Interior fallback.
  lm2_v3_f64 local;
  lm2_v3_f64 abs_local;
  for (int i = 0; i < 3; ++i) {
    local.e[i] = result.point.e[i] - (aabb.min.e[i] * 0.5 + aabb.max.e[i] * 0.5);
    abs_local.e[i] = fabs(local.e[i]);
  }

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

  if (t >= 0.0 && t <= ray.t_max) {
    result.hit = true;
    result.t = t;
    result.point = lm2_ray3_point_at_f64(ray, t);
    result.normal = lm2_v3_norm_f64(lm2_v3_cross_f64(edge1, edge2));
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
  // Scaling first keeps the length representable for finite normals even
  // when all components are near DBL_MAX or in the subnormal range.
  const double scale = fmax(fmax(fabs(plane_normal.x), fabs(plane_normal.y)), fabs(plane_normal.z));
  if (scale > 0.0 && isfinite(scale)) {
    plane_normal.x /= scale;
    plane_normal.y /= scale;
    plane_normal.z /= scale;
  }
  plane_normal = _lm2_ray_norm_f64(plane_normal);

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
  lm2_rayhit3_f32 result = {0};
  if (ray.t_max < 0.0f) return result;
  lm2_v3_f32 oc = _lm2_ray_sub_f32(ray.origin, center);
  float dir_len = hypotf(hypotf(ray.direction.x, ray.direction.y), ray.direction.z);
  radius = fabsf(radius);
  if (dir_len == 0.0f) {
    if (hypotf(hypotf(oc.x, oc.y), oc.z) <= radius) {
      result.hit = true;
      result.point = ray.origin;
    }
    return result;
  }
  lm2_v3_f32 unit = {ray.direction.x / dir_len, ray.direction.y / dir_len, ray.direction.z / dir_len};
  lm2_v3_f32 cross = _lm2_ray_cross_f32(oc, unit);
  float perpendicular = hypotf(hypotf(cross.x, cross.y), cross.z);
  if (perpendicular > radius) return result;
  float ratio = radius > 0.0f ? perpendicular / radius : 0.0f;
  float half_chord = radius * sqrtf((1.0f - ratio) * (1.0f + ratio));
  float along = -_lm2_ray_dot_f32(oc, unit);
  float t = (along - half_chord) / dir_len;
  float radial_along = -half_chord;
  if (t < 0.0f) {
    t = (along + half_chord) / dir_len;
    radial_along = half_chord;
  }
  if (t < 0.0f || t > ray.t_max) return result;
  result.hit = true;
  result.t = t;
  lm2_v3_f32 closest = _lm2_ray_cross_f32(unit, cross);
  lm2_v3_f32 radial = _lm2_ray_add_f32(closest, _lm2_ray_mul_f32(unit, radial_along));
  result.point = _lm2_ray_add_f32(center, radial);
  result.normal = _lm2_ray_norm_f32(radial);
  return result;
}

LM2_API lm2_rayhit3_f32 lm2_raycast_aabb3_f32(lm2_ray3_f32 ray, lm2_r3_f32 aabb) {
  lm2_rayhit3_f32 result = {0};
  if (ray.t_max < 0.0f) return result;

  // Ray-AABB intersection using slab method
  float t_min = 0.0f;
  float t_max = ray.t_max;
  lm2_v3_f32 entry_normal = {0.0f, 0.0f, 0.0f};

  for (int i = 0; i < 3; ++i) {
    // A small nonzero component can still cross a slab along a long ray.
    if (ray.direction.e[i] == 0.0f) {
      // Ray is parallel to slab - check if origin is within slab bounds
      if (ray.origin.e[i] < aabb.min.e[i] || ray.origin.e[i] > aabb.max.e[i]) {
        result.hit = false;
        result.t = 0.0f;
        result.normal = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
        result.point = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
        return result;
      }
      continue;
    }

    float t0 = (aabb.min.e[i] - ray.origin.e[i]) / ray.direction.e[i];
    float t1 = (aabb.max.e[i] - ray.origin.e[i]) / ray.direction.e[i];

    if (ray.direction.e[i] < 0.0f) {
      float temp = t0;
      t0 = t1;
      t1 = temp;
    }

    if (t0 > t_min) {
      t_min = t0;
      entry_normal = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
      entry_normal.e[i] = ray.direction.e[i] < 0.0f ? 1.0f : -1.0f;
    }
    t_max = t1 < t_max ? t1 : t_max;

    if (t_max < t_min) {
      result.hit = false;
      result.t = 0.0f;
      result.normal = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
      result.point = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
      return result;
    }
  }

  result.hit = true;
  result.t = t_min;
  for (int i = 0; i < 3; ++i) result.point.e[i] = ray.origin.e[i] + ray.direction.e[i] * t_min;

  if (t_min > 0.0f) {
    result.normal = entry_normal;
    return result;
  }

  for (int i = 0; i < 3; ++i) {
    if (ray.origin.e[i] == aabb.min.e[i] || ray.origin.e[i] == aabb.max.e[i]) {
      result.normal = (lm2_v3_f32) {0.0f, 0.0f, 0.0f};
      result.normal.e[i] = ray.origin.e[i] == aabb.min.e[i] ? -1.0f : 1.0f;
      return result;
    }
  }

  // Compute normal
  lm2_v3_f32 local;
  lm2_v3_f32 abs_local;
  for (int i = 0; i < 3; ++i) {
    local.e[i] = result.point.e[i] - (aabb.min.e[i] * 0.5f + aabb.max.e[i] * 0.5f);
    abs_local.e[i] = fabsf(local.e[i]);
  }

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

  if (t >= 0.0f && t <= ray.t_max) {
    result.hit = true;
    result.t = t;
    result.point = lm2_ray3_point_at_f32(ray, t);
    result.normal = lm2_v3_norm_f32(lm2_v3_cross_f32(edge1, edge2));
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
  const float scale = fmaxf(fmaxf(fabsf(plane_normal.x), fabsf(plane_normal.y)), fabsf(plane_normal.z));
  if (scale > 0.0f && isfinite(scale)) {
    plane_normal.x /= scale;
    plane_normal.y /= scale;
    plane_normal.z /= scale;
  }
  plane_normal = _lm2_ray_norm_f32(plane_normal);

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

// For extreme differences between ray distance and capsule size, scaling all
// coordinates together would collapse the capsule. Work with unit axes and
// compute the side normal directly, even when entry and exit t round equally.
#define LM2_RAY3_CAPSULE_FAR(suffix, type, hyp, absfn, rootfn, fmafn)                                                            \
  static type _lm2_ray_diff_products_##suffix(type a, type b, type c, type d) {                                                  \
    type cd = c * d;                                                                                                             \
    return fmafn(a, b, -cd) - fmafn(c, d, -cd);                                                                                  \
  }                                                                                                                              \
  static lm2_rayhit3_##suffix _lm2_ray_capsule_far_##suffix(                                                                     \
      lm2_ray3_##suffix ray, lm2_v3_##suffix start, lm2_v3_##suffix end, type radius) {                                          \
    lm2_rayhit3_##suffix result = {0};                                                                                           \
    lm2_v3_##suffix axis = _lm2_ray_sub_##suffix(end, start);                                                                    \
    lm2_v3_##suffix offset = _lm2_ray_sub_##suffix(ray.origin, start);                                                           \
    type axis_len = hyp(hyp(axis.x, axis.y), axis.z);                                                                            \
    type dir_len = hyp(hyp(ray.direction.x, ray.direction.y), ray.direction.z);                                                  \
    if (axis_len == 0) return lm2_raycast_sphere_##suffix(ray, start, radius);                                                   \
    lm2_v3_##suffix axis_unit = {axis.x / axis_len, axis.y / axis_len, axis.z / axis_len};                                       \
    type axis_offset = _lm2_ray_dot_##suffix(offset, axis_unit);                                                                 \
    if (dir_len == 0) {                                                                                                          \
      type along = axis_offset < 0 ? 0 : axis_offset > axis_len ? axis_len                                                       \
                                                                : axis_offset;                                                   \
      lm2_v3_##suffix relative = _lm2_ray_sub_##suffix(offset, _lm2_ray_mul_##suffix(axis_unit, along));                         \
      if (hyp(hyp(relative.x, relative.y), relative.z) <= radius) {                                                              \
        result.hit = true;                                                                                                       \
        result.point = ray.origin;                                                                                               \
      }                                                                                                                          \
      return result;                                                                                                             \
    }                                                                                                                            \
    lm2_v3_##suffix dir = {ray.direction.x / dir_len, ray.direction.y / dir_len, ray.direction.z / dir_len};                     \
    type base = -_lm2_ray_dot_##suffix(offset, dir);                                                                             \
    type best_local = INFINITY;                                                                                                  \
    /* Compensate both products: an asymmetric contracted multiply-subtract can                                                  \
       turn an exactly parallel, distant origin into a huge spurious offset. */                                                  \
    lm2_v3_##suffix origin_cross = {                                                                                             \
        _lm2_ray_diff_products_##suffix(ray.origin.y, dir.z, ray.origin.z, dir.y),                                               \
        _lm2_ray_diff_products_##suffix(ray.origin.z, dir.x, ray.origin.x, dir.z),                                               \
        _lm2_ray_diff_products_##suffix(ray.origin.x, dir.y, ray.origin.y, dir.x)};                                              \
    lm2_v3_##suffix projected_origin = _lm2_ray_cross_##suffix(dir, origin_cross);                                               \
    lm2_v3_##suffix projected_start = _lm2_ray_cross_##suffix(dir, _lm2_ray_cross_##suffix(start, dir));                         \
    lm2_v3_##suffix offset_projected = _lm2_ray_sub_##suffix(projected_origin, projected_start);                                 \
    lm2_v3_##suffix cross = _lm2_ray_cross_##suffix(axis_unit, dir);                                                             \
    type cross_len = hyp(hyp(cross.x, cross.y), cross.z);                                                                        \
    if (cross_len > 0) {                                                                                                         \
      lm2_v3_##suffix n = {cross.x / cross_len, cross.y / cross_len, cross.z / cross_len};                                       \
      lm2_v3_##suffix axis_projected_unit = _lm2_ray_cross_##suffix(dir, n);                                                     \
      type signed_dist = _lm2_ray_dot_##suffix(offset_projected, n);                                                             \
      type dist = absfn(signed_dist);                                                                                            \
      if (dist <= radius) {                                                                                                      \
        lm2_v3_##suffix tangent = _lm2_ray_cross_##suffix(n, axis_unit);                                                         \
        type ratio = radius > 0 ? dist / radius : 0;                                                                             \
        type half = radius * rootfn((1 - ratio) * (1 + ratio));                                                                  \
        type center = -_lm2_ray_dot_##suffix(offset_projected, tangent) / cross_len;                                             \
        type span = half / cross_len;                                                                                            \
        for (int i = 0; i < 2; ++i) {                                                                                            \
          type sign = i == 0 ? -1 : 1;                                                                                           \
          type local_distance = center + sign * span;                                                                            \
          type t = (base + local_distance) / dir_len;                                                                            \
          lm2_v3_##suffix radial = _lm2_ray_add_##suffix(                                                                        \
              _lm2_ray_mul_##suffix(n, signed_dist), _lm2_ray_mul_##suffix(tangent, sign * half));                               \
          type axial = _lm2_ray_dot_##suffix(_lm2_ray_sub_##suffix(offset_projected, radial),                                    \
                                             axis_projected_unit) /                                                              \
                       cross_len;                                                                                                \
          if (t >= 0 && t <= ray.t_max && local_distance < best_local && axial >= 0 && axial <= axis_len) {                      \
            result.normal = _lm2_ray_norm_##suffix(radial);                                                                      \
            result.point = _lm2_ray_add_##suffix(start, _lm2_ray_add_##suffix(_lm2_ray_mul_##suffix(axis_unit, axial), radial)); \
            best_local = local_distance;                                                                                         \
            result.t = t;                                                                                                        \
            result.hit = true;                                                                                                   \
          }                                                                                                                      \
        }                                                                                                                        \
      }                                                                                                                          \
    }                                                                                                                            \
    for (int cap = 0; cap < 2; ++cap) {                                                                                          \
      lm2_v3_##suffix oc = cap == 0 ? offset_projected : _lm2_ray_sub_##suffix(offset_projected, axis);                          \
      lm2_v3_##suffix cross_oc = _lm2_ray_cross_##suffix(oc, dir);                                                               \
      type dist = hyp(hyp(cross_oc.x, cross_oc.y), cross_oc.z);                                                                  \
      if (dist > radius) continue;                                                                                               \
      type ratio = radius > 0 ? dist / radius : 0;                                                                               \
      type half = radius * rootfn((1 - ratio) * (1 + ratio));                                                                    \
      type center_distance = -_lm2_ray_dot_##suffix(oc, dir);                                                                    \
      lm2_v3_##suffix perpendicular = _lm2_ray_cross_##suffix(dir, cross_oc);                                                    \
      for (int i = 0; i < 2; ++i) {                                                                                              \
        type sign = i == 0 ? -1 : 1;                                                                                             \
        type local_distance = center_distance + sign * half;                                                                     \
        type t = (base + local_distance) / dir_len;                                                                              \
        lm2_v3_##suffix radial = _lm2_ray_add_##suffix(perpendicular, _lm2_ray_mul_##suffix(dir, sign * half));                  \
        type axial = _lm2_ray_dot_##suffix(radial, axis_unit);                                                                   \
        if (t >= 0 && t <= ray.t_max && local_distance < best_local &&                                                           \
            (cap == 0 ? axial <= 0 : axial >= 0)) {                                                                              \
          result.normal = _lm2_ray_norm_##suffix(radial);                                                                        \
          result.point = _lm2_ray_add_##suffix(cap == 0 ? start : end, radial);                                                  \
          best_local = local_distance;                                                                                           \
          result.t = t;                                                                                                          \
          result.hit = true;                                                                                                     \
        }                                                                                                                        \
      }                                                                                                                          \
    }                                                                                                                            \
    return result;                                                                                                               \
  }
LM2_RAY3_CAPSULE_FAR(f64, double, hypot, fabs, sqrt, fma)
LM2_RAY3_CAPSULE_FAR(f32, float, hypotf, fabsf, sqrtf, fmaf)
#undef LM2_RAY3_CAPSULE_FAR

LM2_API lm2_rayhit3_f64 lm2_raycast_capsule_f64(lm2_ray3_f64 ray, lm2_v3_f64 start, lm2_v3_f64 end, double radius) {
  lm2_rayhit3_f64 result = {0};
  if (ray.t_max < 0.0) return result;
  lm2_v3_f64 axis = _lm2_ray_sub_f64(end, start);
  lm2_v3_f64 offset = _lm2_ray_sub_f64(ray.origin, start);
  // The cylinder calculation below contains products of squared lengths.
  // Rescale uniformly for very small or large finite geometry, and restore
  // world-space t and point afterward. The unit direction and normal do not
  // change under this scale.
  double scale = fmax(fmax(fmax(fabs(axis.x), fabs(axis.y)), fabs(axis.z)),
                      fmax(fmax(fmax(fabs(offset.x), fabs(offset.y)), fabs(offset.z)), fabs(radius)));
  if (isfinite(scale) && scale > 0.0 && (scale < 1e-70 || scale > 1e70)) {
    double shape_scale = fmax(fmax(fmax(fabs(axis.x), fabs(axis.y)), fabs(axis.z)), fabs(radius));
    if (shape_scale / scale < 1e-70) return _lm2_ray_capsule_far_f64(ray, start, end, radius);
    lm2_ray3_f64 scaled_ray = {
        {offset.x / scale, offset.y / scale, offset.z / scale},
        ray.direction,
        ray.t_max / scale
    };
    lm2_v3_f64 zero = {0.0, 0.0, 0.0};
    lm2_v3_f64 scaled_axis = {axis.x / scale, axis.y / scale, axis.z / scale};
    result = lm2_raycast_capsule_f64(scaled_ray, zero, scaled_axis, radius / scale);
    if (result.hit) {
      result.t *= scale;
      result.point = _lm2_ray_add_f64(ray.origin, _lm2_ray_mul_f64(ray.direction, result.t));
    }
    return result;
  }
  double axis_sq = _lm2_ray_dot_f64(axis, axis);
  double dir_sq = _lm2_ray_dot_f64(ray.direction, ray.direction);
  double radius_sq = radius * radius;
  if (axis_sq == 0.0) return lm2_raycast_sphere_f64(ray, start, radius);

  double axis_offset = _lm2_ray_dot_f64(axis, offset);
  double axis_dir = _lm2_ray_dot_f64(axis, ray.direction);
  if (dir_sq == 0.0) {
    double s = axis_offset / axis_sq;
    if (s < 0.0) s = 0.0;
    if (s > 1.0) s = 1.0;
    lm2_v3_f64 relative = _lm2_ray_sub_f64(offset, _lm2_ray_mul_f64(axis, s));
    if (_lm2_ray_dot_f64(relative, relative) <= radius_sq) {
      result.hit = true;
      result.point = ray.origin;
    }
    return result;
  }

  double best_t = ray.t_max;
  lm2_v3_f64 best_normal = {0};
  // Infinite cylinder intersected with the interval of the segment axis.
  lm2_v3_f64 cross_dir = _lm2_ray_cross_f64(axis, ray.direction);
  double a = _lm2_ray_dot_f64(cross_dir, cross_dir);
  if (a > 0.0) {
    double b = _lm2_ray_dot_f64(_lm2_ray_cross_f64(axis, offset), cross_dir);
    double triple = _lm2_ray_dot_f64(offset, cross_dir);
    double radial_sq = radius_sq - (triple * triple) / a;
    if (radial_sq >= 0.0) {
      double center_t = -b / a;
      double half_span = sqrt(axis_sq * radial_sq / a);
      double roots[2] = {center_t - half_span, center_t + half_span};
      for (int i = 0; i < 2; ++i) {
        double t = roots[i];
        double axial = axis_offset + t * axis_dir;
        if (t >= 0.0 && t <= best_t && axial >= 0.0 && axial <= axis_sq) {
          lm2_v3_f64 relative = _lm2_ray_add_f64(offset, _lm2_ray_mul_f64(ray.direction, t));
          relative = _lm2_ray_sub_f64(relative, _lm2_ray_mul_f64(axis, axial / axis_sq));
          best_normal = _lm2_ray_norm_f64(relative);
          best_t = t;
          result.hit = true;
        }
      }
    }
  }

  // Restrict each end sphere to its outer hemisphere; the other half lies
  // inside the cylinder and must not be reported as a capsule surface.
  for (int cap = 0; cap < 2; ++cap) {
    lm2_v3_f64 center = cap == 0 ? start : end;
    lm2_v3_f64 oc = _lm2_ray_sub_f64(ray.origin, center);
    double half_b = _lm2_ray_dot_f64(oc, ray.direction);
    lm2_v3_f64 cross = _lm2_ray_cross_f64(oc, ray.direction);
    double cap_disc = dir_sq * radius_sq - _lm2_ray_dot_f64(cross, cross);
    if (cap_disc < 0.0) continue;
    double root = sqrt(cap_disc);
    double roots[2] = {(-half_b - root) / dir_sq, (-half_b + root) / dir_sq};
    for (int i = 0; i < 2; ++i) {
      double t = roots[i];
      double axial = axis_offset + t * axis_dir;
      if (t >= 0.0 && t <= best_t && (cap == 0 ? axial <= 0.0 : axial >= axis_sq)) {
        best_t = t;
        best_normal = _lm2_ray_norm_f64(_lm2_ray_add_f64(oc, _lm2_ray_mul_f64(ray.direction, t)));
        result.hit = true;
      }
    }
  }
  if (result.hit) {
    result.t = best_t;
    result.point = _lm2_ray_add_f64(ray.origin, _lm2_ray_mul_f64(ray.direction, best_t));
    result.normal = best_normal;
  }
  return result;
}

LM2_API lm2_rayhit3_f32 lm2_raycast_capsule_f32(lm2_ray3_f32 ray, lm2_v3_f32 start, lm2_v3_f32 end, float radius) {
  lm2_rayhit3_f32 result = {0};
  if (ray.t_max < 0.0f) return result;
  lm2_v3_f32 axis = _lm2_ray_sub_f32(end, start);
  lm2_v3_f32 offset = _lm2_ray_sub_f32(ray.origin, start);
  float scale = fmaxf(fmaxf(fmaxf(fabsf(axis.x), fabsf(axis.y)), fabsf(axis.z)),
                      fmaxf(fmaxf(fmaxf(fabsf(offset.x), fabsf(offset.y)), fabsf(offset.z)), fabsf(radius)));
  if (isfinite(scale) && scale > 0.0f && (scale < 1e-8f || scale > 1e8f)) {
    float shape_scale = fmaxf(fmaxf(fmaxf(fabsf(axis.x), fabsf(axis.y)), fabsf(axis.z)), fabsf(radius));
    if (shape_scale / scale < 1e-8f) return _lm2_ray_capsule_far_f32(ray, start, end, radius);
    lm2_ray3_f32 scaled_ray = {
        {offset.x / scale, offset.y / scale, offset.z / scale},
        ray.direction,
        ray.t_max / scale
    };
    lm2_v3_f32 zero = {0.0f, 0.0f, 0.0f};
    lm2_v3_f32 scaled_axis = {axis.x / scale, axis.y / scale, axis.z / scale};
    result = lm2_raycast_capsule_f32(scaled_ray, zero, scaled_axis, radius / scale);
    if (result.hit) {
      result.t *= scale;
      result.point = _lm2_ray_add_f32(ray.origin, _lm2_ray_mul_f32(ray.direction, result.t));
    }
    return result;
  }
  float axis_sq = _lm2_ray_dot_f32(axis, axis);
  float dir_sq = _lm2_ray_dot_f32(ray.direction, ray.direction);
  float radius_sq = radius * radius;
  if (axis_sq == 0.0f) return lm2_raycast_sphere_f32(ray, start, radius);

  float axis_offset = _lm2_ray_dot_f32(axis, offset);
  float axis_dir = _lm2_ray_dot_f32(axis, ray.direction);
  if (dir_sq == 0.0f) {
    float s = axis_offset / axis_sq;
    if (s < 0.0f) s = 0.0f;
    if (s > 1.0f) s = 1.0f;
    lm2_v3_f32 relative = _lm2_ray_sub_f32(offset, _lm2_ray_mul_f32(axis, s));
    if (_lm2_ray_dot_f32(relative, relative) <= radius_sq) {
      result.hit = true;
      result.point = ray.origin;
    }
    return result;
  }

  float best_t = ray.t_max;
  lm2_v3_f32 best_normal = {0};
  // Infinite cylinder intersected with the interval of the segment axis.
  lm2_v3_f32 cross_dir = _lm2_ray_cross_f32(axis, ray.direction);
  float a = _lm2_ray_dot_f32(cross_dir, cross_dir);
  if (a > 0.0f) {
    float b = _lm2_ray_dot_f32(_lm2_ray_cross_f32(axis, offset), cross_dir);
    float triple = _lm2_ray_dot_f32(offset, cross_dir);
    float radial_sq = radius_sq - (triple * triple) / a;
    if (radial_sq >= 0.0f) {
      float center_t = -b / a;
      float half_span = sqrtf(axis_sq * radial_sq / a);
      float roots[2] = {center_t - half_span, center_t + half_span};
      for (int i = 0; i < 2; ++i) {
        float t = roots[i];
        float axial = axis_offset + t * axis_dir;
        if (t >= 0.0f && t <= best_t && axial >= 0.0f && axial <= axis_sq) {
          lm2_v3_f32 relative = _lm2_ray_add_f32(offset, _lm2_ray_mul_f32(ray.direction, t));
          relative = _lm2_ray_sub_f32(relative, _lm2_ray_mul_f32(axis, axial / axis_sq));
          best_normal = _lm2_ray_norm_f32(relative);
          best_t = t;
          result.hit = true;
        }
      }
    }
  }

  // Restrict each end sphere to its outer hemisphere; the other half lies
  // inside the cylinder and must not be reported as a capsule surface.
  for (int cap = 0; cap < 2; ++cap) {
    lm2_v3_f32 center = cap == 0 ? start : end;
    lm2_v3_f32 oc = _lm2_ray_sub_f32(ray.origin, center);
    float half_b = _lm2_ray_dot_f32(oc, ray.direction);
    lm2_v3_f32 cross = _lm2_ray_cross_f32(oc, ray.direction);
    float cap_disc = dir_sq * radius_sq - _lm2_ray_dot_f32(cross, cross);
    if (cap_disc < 0.0f) continue;
    float root = sqrtf(cap_disc);
    float roots[2] = {(-half_b - root) / dir_sq, (-half_b + root) / dir_sq};
    for (int i = 0; i < 2; ++i) {
      float t = roots[i];
      float axial = axis_offset + t * axis_dir;
      if (t >= 0.0f && t <= best_t && (cap == 0 ? axial <= 0.0f : axial >= axis_sq)) {
        best_t = t;
        best_normal = _lm2_ray_norm_f32(_lm2_ray_add_f32(oc, _lm2_ray_mul_f32(ray.direction, t)));
        result.hit = true;
      }
    }
  }
  if (result.hit) {
    result.t = best_t;
    result.point = _lm2_ray_add_f32(ray.origin, _lm2_ray_mul_f32(ray.direction, best_t));
    result.normal = best_normal;
  }
  return result;
}

// =============================================================================
// Ray vs Edge/Line Segment Tests
// =============================================================================

LM2_API lm2_rayhit3_f64 lm2_raycast_edge_f64(lm2_ray3_f64 ray, lm2_v3_f64 edge_start, lm2_v3_f64 edge_end, double tolerance) {
  lm2_rayhit3_f64 result = {0};
  if (ray.t_max < 0.0 || tolerance < 0.0) return result;
  lm2_v3_f64 edge = lm2_v3_sub_f64(edge_end, edge_start);
  lm2_v3_f64 offset = lm2_v3_sub_f64(ray.origin, edge_start);
  double a = lm2_v3_dot_f64(ray.direction, ray.direction);
  double b = lm2_v3_dot_f64(ray.direction, edge);
  double c = lm2_v3_dot_f64(edge, edge);
  double d = lm2_v3_dot_f64(ray.direction, offset);
  double e = lm2_v3_dot_f64(edge, offset);
  double t = 0.0, u = 0.0;

  if (a == 0.0) {
    if (c != 0.0) u = lm2_div_f64(e, c);
    if (u < 0.0) u = 0.0;
    if (u > 1.0) u = 1.0;
  } else if (c == 0.0) {
    t = lm2_div_f64(lm2_neg_f64(d), a);
    if (t < 0.0) t = 0.0;
    if (t > ray.t_max) t = ray.t_max;
  } else {
    lm2_v3_f64 cross = lm2_v3_cross_f64(ray.direction, edge);
    double denom = lm2_v3_dot_f64(cross, cross);
    if (denom > 0.0) t = lm2_div_f64(lm2_v3_dot_f64(lm2_v3_cross_f64(edge, offset), cross), denom);
    if (t < 0.0) t = 0.0;
    if (t > ray.t_max) t = ray.t_max;
    u = lm2_div_f64(lm2_add_f64(e, lm2_mul_f64(b, t)), c);
    if (u < 0.0) {
      u = 0.0;
      t = lm2_div_f64(lm2_neg_f64(d), a);
      if (t < 0.0) t = 0.0;
      if (t > ray.t_max) t = ray.t_max;
    } else if (u > 1.0) {
      u = 1.0;
      t = lm2_div_f64(lm2_sub_f64(b, d), a);
      if (t < 0.0) t = 0.0;
      if (t > ray.t_max) t = ray.t_max;
    }
  }

  lm2_v3_f64 ray_point = lm2_ray3_point_at_f64(ray, t);
  lm2_v3_f64 edge_point = lm2_v3_add_f64(edge_start, lm2_v3_mul_s_f64(edge, u));
  lm2_v3_f64 separation = lm2_v3_sub_f64(ray_point, edge_point);
  double distance = lm2_v3_length_f64(separation);
  if (distance <= tolerance) {
    result.hit = true;
    result.t = t;
    result.point = ray_point;
    if (distance > 0.0) {
      result.normal = lm2_v3_norm_f64(separation);
    } else {
      // Coincident parallel or point primitives have no unique normal.
      result.normal = lm2_v3_norm_f64(lm2_v3_cross_f64(ray.direction, edge));
    }
  }
  return result;
}

LM2_API lm2_rayhit3_f32 lm2_raycast_edge_f32(lm2_ray3_f32 ray, lm2_v3_f32 edge_start, lm2_v3_f32 edge_end, float tolerance) {
  lm2_rayhit3_f32 result = {0};
  if (ray.t_max < 0.0f || tolerance < 0.0f) return result;
  lm2_v3_f32 edge = lm2_v3_sub_f32(edge_end, edge_start);
  lm2_v3_f32 offset = lm2_v3_sub_f32(ray.origin, edge_start);
  float a = lm2_v3_dot_f32(ray.direction, ray.direction);
  float b = lm2_v3_dot_f32(ray.direction, edge);
  float c = lm2_v3_dot_f32(edge, edge);
  float d = lm2_v3_dot_f32(ray.direction, offset);
  float e = lm2_v3_dot_f32(edge, offset);
  float t = 0.0f, u = 0.0f;

  if (a == 0.0f) {
    if (c != 0.0f) u = lm2_div_f32(e, c);
    if (u < 0.0f) u = 0.0f;
    if (u > 1.0f) u = 1.0f;
  } else if (c == 0.0f) {
    t = lm2_div_f32(lm2_neg_f32(d), a);
    if (t < 0.0f) t = 0.0f;
    if (t > ray.t_max) t = ray.t_max;
  } else {
    lm2_v3_f32 cross = lm2_v3_cross_f32(ray.direction, edge);
    float denom = lm2_v3_dot_f32(cross, cross);
    if (denom > 0.0f) t = lm2_div_f32(lm2_v3_dot_f32(lm2_v3_cross_f32(edge, offset), cross), denom);
    if (t < 0.0f) t = 0.0f;
    if (t > ray.t_max) t = ray.t_max;
    u = lm2_div_f32(lm2_add_f32(e, lm2_mul_f32(b, t)), c);
    if (u < 0.0f) {
      u = 0.0f;
      t = lm2_div_f32(lm2_neg_f32(d), a);
      if (t < 0.0f) t = 0.0f;
      if (t > ray.t_max) t = ray.t_max;
    } else if (u > 1.0f) {
      u = 1.0f;
      t = lm2_div_f32(lm2_sub_f32(b, d), a);
      if (t < 0.0f) t = 0.0f;
      if (t > ray.t_max) t = ray.t_max;
    }
  }

  lm2_v3_f32 ray_point = lm2_ray3_point_at_f32(ray, t);
  lm2_v3_f32 edge_point = lm2_v3_add_f32(edge_start, lm2_v3_mul_s_f32(edge, u));
  lm2_v3_f32 separation = lm2_v3_sub_f32(ray_point, edge_point);
  float distance = lm2_v3_length_f32(separation);
  if (distance <= tolerance) {
    result.hit = true;
    result.t = t;
    result.point = ray_point;
    if (distance > 0.0f) {
      result.normal = lm2_v3_norm_f32(separation);
    } else {
      // Coincident parallel or point primitives have no unique normal.
      result.normal = lm2_v3_norm_f32(lm2_v3_cross_f32(ray.direction, edge));
    }
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

    case LM2_SHAPE3_AABB3: {
      lm2_aabb3_f64* cuboid = (lm2_aabb3_f64*)shape.data;
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

    case LM2_SHAPE3_AABB3: {
      lm2_aabb3_f32* cuboid = (lm2_aabb3_f32*)shape.data;
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
