#pragma once

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

#include <lm2/geometry2d/lm2_edge2.h>
#include <lm2/geometry3d/lm2_raycast3.h>
#include <lm2/geometry2d/lm2_plane2.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/vectors/lm2_vector_specifics.h>
#include <math.h>

// =============================================================================
// Construction Helpers
// =============================================================================

LM2_API lm2_edge2_f64 lm2_edge2_make_f64(lm2_v2_f64 start, lm2_v2_f64 end) {
  lm2_edge2_f64 edge;
  edge.start = start;
  edge.end = end;
  return edge;
}

LM2_API lm2_edge2_f32 lm2_edge2_make_f32(lm2_v2_f32 start, lm2_v2_f32 end) {
  lm2_edge2_f32 edge;
  edge.start = start;
  edge.end = end;
  return edge;
}

LM2_API lm2_edge2_f64 lm2_edge2_make_coords_f64(double x1, double y1, double x2, double y2) {
  lm2_edge2_f64 edge;
  edge.start.x = x1;
  edge.start.y = y1;
  edge.end.x = x2;
  edge.end.y = y2;
  return edge;
}

LM2_API lm2_edge2_f32 lm2_edge2_make_coords_f32(float x1, float y1, float x2, float y2) {
  lm2_edge2_f32 edge;
  edge.start.x = x1;
  edge.start.y = y1;
  edge.end.x = x2;
  edge.end.y = y2;
  return edge;
}

// =============================================================================
// Conversion from Other Geometry Types
// =============================================================================

LM2_API lm2_edge2_f64 lm2_edge2_from_ray_f64(lm2_ray2_f64 ray) {
  lm2_edge2_f64 edge;
  edge.start = ray.origin;
  edge.end.x = lm2_add_f64(ray.origin.x, lm2_mul_f64(ray.direction.x, ray.t_max));
  edge.end.y = lm2_add_f64(ray.origin.y, lm2_mul_f64(ray.direction.y, ray.t_max));
  return edge;
}

LM2_API lm2_edge2_f32 lm2_edge2_from_ray_f32(lm2_ray2_f32 ray) {
  lm2_edge2_f32 edge;
  edge.start = ray.origin;
  edge.end.x = lm2_add_f32(ray.origin.x, lm2_mul_f32(ray.direction.x, ray.t_max));
  edge.end.y = lm2_add_f32(ray.origin.y, lm2_mul_f32(ray.direction.y, ray.t_max));
  return edge;
}

LM2_API lm2_edge2_f64 lm2_edge2_from_plane_f64(lm2_plane2_f64 plane, lm2_v2_f64 center, double length) {
  // Get a direction perpendicular to the plane's normal (rotate 90 degrees)
  lm2_v2_f64 dir;
  dir.x = lm2_neg_f64(plane.normal.y);
  dir.y = plane.normal.x;

  // Calculate half length
  double half_length = lm2_mul_f64(length, 0.5);

  // Create edge centered at the given point
  lm2_edge2_f64 edge;
  edge.start.x = lm2_sub_f64(center.x, lm2_mul_f64(dir.x, half_length));
  edge.start.y = lm2_sub_f64(center.y, lm2_mul_f64(dir.y, half_length));
  edge.end.x = lm2_add_f64(center.x, lm2_mul_f64(dir.x, half_length));
  edge.end.y = lm2_add_f64(center.y, lm2_mul_f64(dir.y, half_length));

  return edge;
}

LM2_API lm2_edge2_f32 lm2_edge2_from_plane_f32(lm2_plane2_f32 plane, lm2_v2_f32 center, float length) {
  // Get a direction perpendicular to the plane's normal (rotate 90 degrees)
  lm2_v2_f32 dir;
  dir.x = lm2_neg_f32(plane.normal.y);
  dir.y = plane.normal.x;

  // Calculate half length
  float half_length = lm2_mul_f32(length, 0.5f);

  // Create edge centered at the given point
  lm2_edge2_f32 edge;
  edge.start.x = lm2_sub_f32(center.x, lm2_mul_f32(dir.x, half_length));
  edge.start.y = lm2_sub_f32(center.y, lm2_mul_f32(dir.y, half_length));
  edge.end.x = lm2_add_f32(center.x, lm2_mul_f32(dir.x, half_length));
  edge.end.y = lm2_add_f32(center.y, lm2_mul_f32(dir.y, half_length));

  return edge;
}

// =============================================================================
// Edge Properties
// =============================================================================

LM2_API double lm2_edge2_length_sq_f64(lm2_edge2_f64 edge) {
  double dx = lm2_sub_f64(edge.end.x, edge.start.x);
  double dy = lm2_sub_f64(edge.end.y, edge.start.y);
  return lm2_add_f64(lm2_mul_f64(dx, dx), lm2_mul_f64(dy, dy));
}

LM2_API float lm2_edge2_length_sq_f32(lm2_edge2_f32 edge) {
  float dx = lm2_sub_f32(edge.end.x, edge.start.x);
  float dy = lm2_sub_f32(edge.end.y, edge.start.y);
  return lm2_add_f32(lm2_mul_f32(dx, dx), lm2_mul_f32(dy, dy));
}

LM2_API double lm2_edge2_length_f64(lm2_edge2_f64 edge) {
  return lm2_sqrt_f64(lm2_edge2_length_sq_f64(edge));
}

LM2_API float lm2_edge2_length_f32(lm2_edge2_f32 edge) {
  return lm2_sqrt_f32(lm2_edge2_length_sq_f32(edge));
}

// =============================================================================
// Edge Comparison
// =============================================================================

LM2_API bool lm2_points2_equal_f64(lm2_v2_f64 a, lm2_v2_f64 b, double epsilon) {
  double dx = lm2_abs_f64(lm2_sub_f64(a.x, b.x));
  double dy = lm2_abs_f64(lm2_sub_f64(a.y, b.y));
  return (dx < epsilon) && (dy < epsilon);
}

LM2_API bool lm2_points2_equal_f32(lm2_v2_f32 a, lm2_v2_f32 b, float epsilon) {
  float dx = lm2_abs_f32(lm2_sub_f32(a.x, b.x));
  float dy = lm2_abs_f32(lm2_sub_f32(a.y, b.y));
  return (dx < epsilon) && (dy < epsilon);
}

LM2_API bool lm2_edges2_equal_f64(lm2_edge2_f64 e1, lm2_edge2_f64 e2, double epsilon) {
  return (lm2_points2_equal_f64(e1.start, e2.start, epsilon) && lm2_points2_equal_f64(e1.end, e2.end, epsilon)) ||
         (lm2_points2_equal_f64(e1.start, e2.end, epsilon) && lm2_points2_equal_f64(e1.end, e2.start, epsilon));
}

LM2_API bool lm2_edges2_equal_f32(lm2_edge2_f32 e1, lm2_edge2_f32 e2, float epsilon) {
  return (lm2_points2_equal_f32(e1.start, e2.start, epsilon) && lm2_points2_equal_f32(e1.end, e2.end, epsilon)) ||
         (lm2_points2_equal_f32(e1.start, e2.end, epsilon) && lm2_points2_equal_f32(e1.end, e2.start, epsilon));
}

// =============================================================================
// Edge Intersection
// =============================================================================

static bool lm2_edge2_on_segment_f64(lm2_v2_f64 a, lm2_v2_f64 b, lm2_v2_f64 point) {
  return point.x >= lm2_min_f64(a.x, b.x) && point.x <= lm2_max_f64(a.x, b.x) &&
         point.y >= lm2_min_f64(a.y, b.y) && point.y <= lm2_max_f64(a.y, b.y);
}

static bool lm2_edge2_on_segment_f32(lm2_v2_f32 a, lm2_v2_f32 b, lm2_v2_f32 point) {
  return point.x >= lm2_min_f32(a.x, b.x) && point.x <= lm2_max_f32(a.x, b.x) &&
         point.y >= lm2_min_f32(a.y, b.y) && point.y <= lm2_max_f32(a.y, b.y);
}

// Only the sign is required. Scale each vector independently before the
// products so ordinary finite coordinates do not overflow or underflow.
static long double lm2_edge2_orientation_f64(lm2_v2_f64 a, lm2_v2_f64 b, lm2_v2_f64 p) {
  long double dx = (long double)b.x - a.x, dy = (long double)b.y - a.y;
  long double px = (long double)p.x - a.x, py = (long double)p.y - a.y;
  if (!isfinite(dx) || !isfinite(dy) || !isfinite(px) || !isfinite(py)) {
    dx = (long double)b.x * 0.5L - (long double)a.x * 0.5L;
    dy = (long double)b.y * 0.5L - (long double)a.y * 0.5L;
    px = (long double)p.x * 0.5L - (long double)a.x * 0.5L;
    py = (long double)p.y * 0.5L - (long double)a.y * 0.5L;
  }
  long double ds = fmaxl(fabsl(dx), fabsl(dy));
  long double ps = fmaxl(fabsl(px), fabsl(py));
  if (ds == 0.0L || ps == 0.0L) return 0.0L;
  int de, pe;
  (void)frexpl(ds, &de);
  (void)frexpl(ps, &pe);
  return scalbnl(dx, -de) * scalbnl(py, -pe) - scalbnl(dy, -de) * scalbnl(px, -pe);
}

LM2_API bool lm2_edges2_intersect_f64(lm2_edge2_f64 e1, lm2_edge2_f64 e2) {
  long double d1 = lm2_edge2_orientation_f64(e1.start, e1.end, e2.start);
  long double d2 = lm2_edge2_orientation_f64(e1.start, e1.end, e2.end);
  long double d3 = lm2_edge2_orientation_f64(e2.start, e2.end, e1.start);
  long double d4 = lm2_edge2_orientation_f64(e2.start, e2.end, e1.end);

  if (((d1 > 0.0 && d2 < 0.0) || (d1 < 0.0 && d2 > 0.0)) &&
      ((d3 > 0.0 && d4 < 0.0) || (d3 < 0.0 && d4 > 0.0))) return true;
  if (d1 == 0.0 && lm2_edge2_on_segment_f64(e1.start, e1.end, e2.start)) return true;
  if (d2 == 0.0 && lm2_edge2_on_segment_f64(e1.start, e1.end, e2.end)) return true;
  if (d3 == 0.0 && lm2_edge2_on_segment_f64(e2.start, e2.end, e1.start)) return true;
  if (d4 == 0.0 && lm2_edge2_on_segment_f64(e2.start, e2.end, e1.end)) return true;
  return false;
}

LM2_API bool lm2_edges2_intersect_f32(lm2_edge2_f32 e1, lm2_edge2_f32 e2) {
  lm2_v2_f64 a = {e1.start.x, e1.start.y}, b = {e1.end.x, e1.end.y};
  lm2_v2_f64 c = {e2.start.x, e2.start.y}, d = {e2.end.x, e2.end.y};
  long double d1 = lm2_edge2_orientation_f64(a, b, c);
  long double d2 = lm2_edge2_orientation_f64(a, b, d);
  long double d3 = lm2_edge2_orientation_f64(c, d, a);
  long double d4 = lm2_edge2_orientation_f64(c, d, b);

  if (((d1 > 0.0f && d2 < 0.0f) || (d1 < 0.0f && d2 > 0.0f)) &&
      ((d3 > 0.0f && d4 < 0.0f) || (d3 < 0.0f && d4 > 0.0f))) return true;
  if (d1 == 0.0f && lm2_edge2_on_segment_f32(e1.start, e1.end, e2.start)) return true;
  if (d2 == 0.0f && lm2_edge2_on_segment_f32(e1.start, e1.end, e2.end)) return true;
  if (d3 == 0.0f && lm2_edge2_on_segment_f32(e2.start, e2.end, e1.start)) return true;
  if (d4 == 0.0f && lm2_edge2_on_segment_f32(e2.start, e2.end, e1.end)) return true;
  return false;
}

// =============================================================================
// Edge Distance
// =============================================================================

LM2_API double lm2_point_to_edge2_distance_sq_f64(lm2_v2_f64 point, lm2_edge2_f64 edge) {
  lm2_v2_f64 ab = lm2_v2_sub_f64(edge.end, edge.start);
  lm2_v2_f64 ap = lm2_v2_sub_f64(point, edge.start);

  double ab_len_sq = lm2_v2_length_sq_f64(ab);

  // If segment is degenerate (start == end), return distance squared to start point
  if (ab_len_sq == 0.0) {
    return lm2_v2_length_sq_f64(ap);
  }

  // Project p onto line ab, clamped to [0, 1]
  double t = lm2_div_f64(lm2_v2_dot_f64(ap, ab), ab_len_sq);
  t = lm2_clamp_f64(0.0, t, 1.0);

  // Find closest point on segment
  lm2_v2_f64 closest = lm2_v2_add_f64(edge.start, lm2_v2_mul_s_f64(ab, t));
  lm2_v2_f64 pc = lm2_v2_sub_f64(point, closest);

  return lm2_v2_length_sq_f64(pc);
}

LM2_API float lm2_point_to_edge2_distance_sq_f32(lm2_v2_f32 point, lm2_edge2_f32 edge) {
  lm2_v2_f32 ab = lm2_v2_sub_f32(edge.end, edge.start);
  lm2_v2_f32 ap = lm2_v2_sub_f32(point, edge.start);

  float ab_len_sq = lm2_v2_length_sq_f32(ab);

  // If segment is degenerate (start == end), return distance squared to start point
  if (ab_len_sq == 0.0f) {
    return lm2_v2_length_sq_f32(ap);
  }

  // Project p onto line ab, clamped to [0, 1]
  float t = lm2_div_f32(lm2_v2_dot_f32(ap, ab), ab_len_sq);
  t = lm2_clamp_f32(0.0f, t, 1.0f);

  // Find closest point on segment
  lm2_v2_f32 closest = lm2_v2_add_f32(edge.start, lm2_v2_mul_s_f32(ab, t));
  lm2_v2_f32 pc = lm2_v2_sub_f32(point, closest);

  return lm2_v2_length_sq_f32(pc);
}

LM2_API double lm2_edge2_to_edge2_distance_sq_f64(lm2_edge2_f64 e1, lm2_edge2_f64 e2) {
  if (lm2_edges2_intersect_f64(e1, e2)) return 0.0;

  // Use the minimum of four point-to-segment distances
  double d1 = lm2_point_to_edge2_distance_sq_f64(e1.start, e2);
  double d2 = lm2_point_to_edge2_distance_sq_f64(e1.end, e2);
  double d3 = lm2_point_to_edge2_distance_sq_f64(e2.start, e1);
  double d4 = lm2_point_to_edge2_distance_sq_f64(e2.end, e1);

  double min1 = lm2_min_f64(d1, d2);
  double min2 = lm2_min_f64(d3, d4);
  return lm2_min_f64(min1, min2);
}

LM2_API float lm2_edge2_to_edge2_distance_sq_f32(lm2_edge2_f32 e1, lm2_edge2_f32 e2) {
  if (lm2_edges2_intersect_f32(e1, e2)) return 0.0f;

  // Use the minimum of four point-to-segment distances
  float d1 = lm2_point_to_edge2_distance_sq_f32(e1.start, e2);
  float d2 = lm2_point_to_edge2_distance_sq_f32(e1.end, e2);
  float d3 = lm2_point_to_edge2_distance_sq_f32(e2.start, e1);
  float d4 = lm2_point_to_edge2_distance_sq_f32(e2.end, e1);

  float min1 = lm2_min_f32(d1, d2);
  float min2 = lm2_min_f32(d3, d4);
  return lm2_min_f32(min1, min2);
}

// =============================================================================
// Raw-Coordinate Segment Intersection
// =============================================================================

LM2_API int lm2_edge2_segments_intersect_f64(lm2_v2_f64 a0, lm2_v2_f64 a1, lm2_v2_f64 b0, lm2_v2_f64 b1) {
  lm2_edge2_f64 e1 = lm2_edge2_make_f64(a0, a1);
  lm2_edge2_f64 e2 = lm2_edge2_make_f64(b0, b1);
  return (int)lm2_edges2_intersect_f64(e1, e2);
}

LM2_API int lm2_edge2_segments_intersect_f32(lm2_v2_f32 a0, lm2_v2_f32 a1, lm2_v2_f32 b0, lm2_v2_f32 b1) {
  lm2_edge2_f32 e1 = lm2_edge2_make_f32(a0, a1);
  lm2_edge2_f32 e2 = lm2_edge2_make_f32(b0, b1);
  return (int)lm2_edges2_intersect_f32(e1, e2);
}

// Shared by edge and capsule raycasts without a dependency on capsule2.h.
static inline lm2_rayhit2_f64 lm2_private_raycast_capsule2_f64(lm2_ray2_f64 ray, lm2_v2_f64 start_point, lm2_v2_f64 end_point, double radius) {
  lm2_rayhit2_f64 result = {0};
  if (ray.t_max < 0.0) return result;
  const double dx = end_point.x - start_point.x;
  const double dy = end_point.y - start_point.y;
  const double length = hypot(dx, dy);
  const double ux = length > 0.0 ? dx / length : 0.0;
  const double uy = length > 0.0 ? dy / length : 0.0;
  const double ox = ray.origin.x - start_point.x;
  const double oy = ray.origin.y - start_point.y;
  double along = ox * ux + oy * uy;
  if (along < 0.0) along = 0.0;
  if (along > length) along = length;
  if (hypot(ox - along * ux, oy - along * uy) <= radius) {
    // Preserve the 2D backend's origin-inside convention.
    result.hit = true;
    result.point = ray.origin;
    result.normal = LM2_PRIVATE_LITERAL(lm2_v2_f64) {ux, uy};
    return result;
  }

  // The 3D implementation handles a capsule in any plane, including z=0.
  lm2_ray3_f64 ray3 = {
      {   ray.origin.x,    ray.origin.y, 0.0},
      {ray.direction.x, ray.direction.y, 0.0},
      ray.t_max
  };
  lm2_v3_f64 start = {start_point.x, start_point.y, 0.0};
  lm2_v3_f64 end = {end_point.x, end_point.y, 0.0};
  lm2_rayhit3_f64 hit = lm2_raycast_capsule_f64(ray3, start, end, radius);
  if (hit.hit) {
    result.hit = true;
    result.t = hit.t;
    result.point = LM2_PRIVATE_LITERAL(lm2_v2_f64) {hit.point.x, hit.point.y};
    result.normal = LM2_PRIVATE_LITERAL(lm2_v2_f64) {hit.normal.x, hit.normal.y};
    if (radius == 0.0 && length > 0.0 && result.normal.x == 0.0 && result.normal.y == 0.0) {
      // A zero-radius capsule is a segment: use the face opposing the ray.
      const double dot = uy * ray.direction.x - ux * ray.direction.y;
      if (dot != 0.0) {
        const double sign = dot > 0.0 ? -1.0 : 1.0;
        result.normal = LM2_PRIVATE_LITERAL(lm2_v2_f64) {sign * uy, lm2_neg_f64(sign) * ux};
      }
    }
  }
  return result;
}

static inline lm2_rayhit2_f32 lm2_private_raycast_capsule2_f32(lm2_ray2_f32 ray, lm2_v2_f32 start_point, lm2_v2_f32 end_point, float radius) {
  lm2_rayhit2_f32 result = {0};
  if (ray.t_max < 0.0f) return result;
  float dx = end_point.x - start_point.x;
  float dy = end_point.y - start_point.y;
  float length = hypotf(dx, dy);
  float ux = length > 0.0f ? dx / length : 0.0f;
  float uy = length > 0.0f ? dy / length : 0.0f;
  float ox = ray.origin.x - start_point.x;
  float oy = ray.origin.y - start_point.y;
  float along = ox * ux + oy * uy;
  if (along < 0.0f) along = 0.0f;
  if (along > length) along = length;
  if (hypotf(ox - along * ux, oy - along * uy) <= radius) {
    result.hit = true;
    result.point = ray.origin;
    result.normal = LM2_PRIVATE_LITERAL(lm2_v2_f32) {ux, uy};
    return result;
  }
  lm2_ray3_f32 ray3 = {
      {   ray.origin.x,    ray.origin.y, 0.0f},
      {ray.direction.x, ray.direction.y, 0.0f},
      ray.t_max
  };
  lm2_v3_f32 start = {start_point.x, start_point.y, 0.0f};
  lm2_v3_f32 end = {end_point.x, end_point.y, 0.0f};
  lm2_rayhit3_f32 hit = lm2_raycast_capsule_f32(ray3, start, end, radius);
  if (hit.hit) {
    result.hit = true;
    result.t = hit.t;
    result.point = LM2_PRIVATE_LITERAL(lm2_v2_f32) {hit.point.x, hit.point.y};
    result.normal = LM2_PRIVATE_LITERAL(lm2_v2_f32) {hit.normal.x, hit.normal.y};
    if (radius == 0.0f && length > 0.0f && result.normal.x == 0.0f && result.normal.y == 0.0f) {
      float dot = uy * ray.direction.x - ux * ray.direction.y;
      if (dot != 0.0f) {
        float sign = dot > 0.0f ? -1.0f : 1.0f;
        result.normal = LM2_PRIVATE_LITERAL(lm2_v2_f32) {sign * uy, lm2_neg_f32(sign) * ux};
      }
    }
  }
  return result;
}

// =============================================================================
// Raycasting Against an Edge
// =============================================================================

LM2_API lm2_rayhit2_f64 lm2_raycast_edge2_f64(lm2_ray2_f64 ray, lm2_edge2_f64 edge) {
  return lm2_private_raycast_capsule2_f64(ray, edge.start, edge.end, 0.0);
}

LM2_API lm2_rayhit2_f32 lm2_raycast_edge2_f32(lm2_ray2_f32 ray, lm2_edge2_f32 edge) {
  return lm2_private_raycast_capsule2_f32(ray, edge.start, edge.end, 0.0f);
}
