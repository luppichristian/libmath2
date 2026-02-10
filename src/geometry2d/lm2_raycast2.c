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
  result.direction = lm2_v2_normalize_f64(diff);
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
  result.direction = lm2_v2_normalize_f32(diff);
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

LM2_API lm2_rayhit2_f64 lm2_raycast_circle_f64(lm2_ray2_f64 ray, lm2_circle_f64 circle) {
  lm2_rayhit2_f64 result;
  c2Raycast hit;
  c2Ray c2_ray = lm2_ray2_f64_to_c2(ray);
  c2Circle c2_circle = lm2_circle_f64_to_c2(circle);

  int did_hit = c2RaytoCircle(c2_ray, c2_circle, &hit);
  result.hit = did_hit != 0;

  if (result.hit) {
    result.t = (double)hit.t;
    result.normal = c2v_to_lm22_f64(hit.n);
    result.point = lm2_ray2_point_at_f64(ray, result.t);
  } else {
    result.t = 0.0;
    result.normal = (lm2_v2_f64) {0.0, 0.0};
    result.point = (lm2_v2_f64) {0.0, 0.0};
  }

  return result;
}

LM2_API lm2_rayhit2_f64 lm2_raycast_aabb_f64(lm2_ray2_f64 ray, lm2_r2_f64 aabb) {
  lm2_rayhit2_f64 result;
  c2Raycast hit;
  c2Ray c2_ray = lm2_ray2_f64_to_c2(ray);
  c2AABB c2_aabb = lm2_r2_f64_to_c2(aabb);

  int did_hit = c2RaytoAABB(c2_ray, c2_aabb, &hit);
  result.hit = did_hit != 0;

  if (result.hit) {
    result.t = (double)hit.t;
    result.normal = c2v_to_lm22_f64(hit.n);
    result.point = lm2_ray2_point_at_f64(ray, result.t);
  } else {
    result.t = 0.0;
    result.normal = (lm2_v2_f64) {0.0, 0.0};
    result.point = (lm2_v2_f64) {0.0, 0.0};
  }

  return result;
}

LM2_API lm2_rayhit2_f64 lm2_raycast_capsule2_f64(lm2_ray2_f64 ray, lm2_capsule2_f64 capsule) {
  lm2_rayhit2_f64 result;
  c2Raycast hit;
  c2Ray c2_ray = lm2_ray2_f64_to_c2(ray);
  c2Capsule c2_capsule = lm2_capsule2_f64_to_c2(capsule);

  int did_hit = c2RaytoCapsule(c2_ray, c2_capsule, &hit);
  result.hit = did_hit != 0;

  if (result.hit) {
    result.t = (double)hit.t;
    result.normal = c2v_to_lm22_f64(hit.n);
    result.point = lm2_ray2_point_at_f64(ray, result.t);
  } else {
    result.t = 0.0;
    result.normal = (lm2_v2_f64) {0.0, 0.0};
    result.point = (lm2_v2_f64) {0.0, 0.0};
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
    result.normal = c2v_to_lm22_f64(hit.n);
    result.point = lm2_ray2_point_at_f64(ray, result.t);
  } else {
    result.t = 0.0;
    result.normal = (lm2_v2_f64) {0.0, 0.0};
    result.point = (lm2_v2_f64) {0.0, 0.0};
  }

  return result;
}

LM2_API lm2_rayhit2_f64 lm2_raycast_segment_f64(lm2_ray2_f64 ray, lm2_v2_f64 segment_start, lm2_v2_f64 segment_end) {
  // Convert segment to capsule with zero radius
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
  lm2_rayhit2_f32 result;
  c2Raycast hit;
  c2Ray c2_ray = lm2_ray2_f32_to_c2(ray);
  c2Circle c2_circle = lm2_circle_f32_to_c2(circle);

  int did_hit = c2RaytoCircle(c2_ray, c2_circle, &hit);
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

LM2_API lm2_rayhit2_f32 lm2_raycast_aabb_f32(lm2_ray2_f32 ray, lm2_r2_f32 aabb) {
  lm2_rayhit2_f32 result;
  c2Raycast hit;
  c2Ray c2_ray = lm2_ray2_f32_to_c2(ray);
  c2AABB c2_aabb = lm2_r2_f32_to_c2(aabb);

  int did_hit = c2RaytoAABB(c2_ray, c2_aabb, &hit);
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

LM2_API lm2_rayhit2_f32 lm2_raycast_capsule2_f32(lm2_ray2_f32 ray, lm2_capsule2_f32 capsule) {
  lm2_rayhit2_f32 result;
  c2Raycast hit;
  c2Ray c2_ray = lm2_ray2_f32_to_c2(ray);
  c2Capsule c2_capsule = lm2_capsule2_f32_to_c2(capsule);

  int did_hit = c2RaytoCapsule(c2_ray, c2_capsule, &hit);
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
  // Convert segment to capsule with zero radius
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
  lm2_rayhit2_f64 result;
  result.hit = false;
  result.t = 0.0;
  result.point = (lm2_v2_f64) {0.0, 0.0};
  result.normal = (lm2_v2_f64) {0.0, 0.0};

  // Convert triangle to polygon
  c2Poly poly = lm2_triangle2_f64_to_c2(tri);

  // Convert ray to c2Ray
  c2Ray c2ray = lm2_ray2_f64_to_c2(ray);

  // Perform raycast
  c2Raycast out;
  int hit = c2RaytoPoly(c2ray, &poly, NULL, &out);

  if (hit) {
    result.hit = true;
    result.t = (double)out.t;
    result.point = lm2_v2_add_f64(ray.origin, lm2_v2_mul_s_f64(ray.direction, result.t));
    result.normal = c2v_to_lm22_f64(out.n);
  }

  return result;
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
  double denom = lm2_dot_f64(ray.direction, plane.normal);

  // Check if ray is parallel to plane (denom close to zero)
  if (lm2_abs_f64(denom) < LM2_RAYCAST2_EPSILON_F64) {
    return result;  // No intersection (parallel or nearly parallel)
  }

  // Compute signed distance from ray origin to plane
  double origin_dist = lm2_sub_f64(lm2_dot_f64(ray.origin, plane.normal), plane.distance);

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
  float denom = lm2_dot_f32(ray.direction, plane.normal);

  // Check if ray is parallel to plane (denom close to zero)
  if (lm2_abs_f32(denom) < LM2_RAYCAST2_EPSILON_F32) {
    return result;  // No intersection (parallel or nearly parallel)
  }

  // Compute signed distance from ray origin to plane
  float origin_dist = lm2_sub_f32(lm2_dot_f32(ray.origin, plane.normal), plane.distance);

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

    case LM2_SHAPE2_RECTANGLE: {
      lm2_rectangle2_f64* rect = (lm2_rectangle2_f64*)shape.data;
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

    case LM2_SHAPE2_RECTANGLE: {
      lm2_rectangle2_f32* rect = (lm2_rectangle2_f32*)shape.data;
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
