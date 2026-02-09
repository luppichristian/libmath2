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
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/vectors/lm2_vector_specifics.h>

// =============================================================================
// Construction Helpers
// =============================================================================

LM2_API lm2_edge2_f64 lm2_edge2_make_f64(lm2_v2f64 start, lm2_v2f64 end) {
  lm2_edge2_f64 edge;
  edge.start = start;
  edge.end = end;
  return edge;
}

LM2_API lm2_edge2_f32 lm2_edge2_make_f32(lm2_v2f32 start, lm2_v2f32 end) {
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

LM2_API bool lm2_points2_equal_f64(lm2_v2f64 a, lm2_v2f64 b, double epsilon) {
  double dx = lm2_abs_f64(lm2_sub_f64(a.x, b.x));
  double dy = lm2_abs_f64(lm2_sub_f64(a.y, b.y));
  return (dx < epsilon) && (dy < epsilon);
}

LM2_API bool lm2_points2_equal_f32(lm2_v2f32 a, lm2_v2f32 b, float epsilon) {
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
// 2D Cross Product (Geometric Utilities)
// =============================================================================

LM2_API double lm2_cross_product_2d_f64(lm2_v2f64 p1, lm2_v2f64 p2, lm2_v2f64 p3) {
  double dx1 = lm2_sub_f64(p2.x, p1.x);
  double dy1 = lm2_sub_f64(p2.y, p1.y);
  double dx2 = lm2_sub_f64(p3.x, p1.x);
  double dy2 = lm2_sub_f64(p3.y, p1.y);
  return lm2_sub_f64(lm2_mul_f64(dx1, dy2), lm2_mul_f64(dy1, dx2));
}

LM2_API float lm2_cross_product_2d_f32(lm2_v2f32 p1, lm2_v2f32 p2, lm2_v2f32 p3) {
  float dx1 = lm2_sub_f32(p2.x, p1.x);
  float dy1 = lm2_sub_f32(p2.y, p1.y);
  float dx2 = lm2_sub_f32(p3.x, p1.x);
  float dy2 = lm2_sub_f32(p3.y, p1.y);
  return lm2_sub_f32(lm2_mul_f32(dx1, dy2), lm2_mul_f32(dy1, dx2));
}

// =============================================================================
// Edge Intersection
// =============================================================================

LM2_API bool lm2_edges2_intersect_f64(lm2_edge2_f64 e1, lm2_edge2_f64 e2) {
  // Use cross products to check intersection
  double d1 = lm2_cross3_v2f64(e2.end, e1.start, e2.start);
  double d2 = lm2_cross3_v2f64(e2.end, e1.end, e2.start);
  double d3 = lm2_cross3_v2f64(e1.end, e2.start, e1.start);
  double d4 = lm2_cross3_v2f64(e1.end, e2.end, e1.start);

  if (((d1 > 0.0 && d2 < 0.0) || (d1 < 0.0 && d2 > 0.0)) &&
      ((d3 > 0.0 && d4 < 0.0) || (d3 < 0.0 && d4 > 0.0))) {
    return true;
  }

  // Check for collinear overlaps
  if (lm2_abs_f64(d1) < DBL_EPSILON || lm2_abs_f64(d2) < DBL_EPSILON ||
      lm2_abs_f64(d3) < DBL_EPSILON || lm2_abs_f64(d4) < DBL_EPSILON) {
    return true;
  }

  return false;
}

LM2_API bool lm2_edges2_intersect_f32(lm2_edge2_f32 e1, lm2_edge2_f32 e2) {
  float d1 = lm2_cross3_v2f32(e2.end, e1.start, e2.start);
  float d2 = lm2_cross3_v2f32(e2.end, e1.end, e2.start);
  float d3 = lm2_cross3_v2f32(e1.end, e2.start, e1.start);
  float d4 = lm2_cross3_v2f32(e1.end, e2.end, e1.start);

  if (((d1 > 0.0f && d2 < 0.0f) || (d1 < 0.0f && d2 > 0.0f)) &&
      ((d3 > 0.0f && d4 < 0.0f) || (d3 < 0.0f && d4 > 0.0f))) {
    return true;
  }

  if (lm2_abs_f32(d1) < FLT_EPSILON || lm2_abs_f32(d2) < FLT_EPSILON ||
      lm2_abs_f32(d3) < FLT_EPSILON || lm2_abs_f32(d4) < FLT_EPSILON) {
    return true;
  }

  return false;
}

// =============================================================================
// Edge Distance
// =============================================================================

LM2_API double lm2_point_to_edge2_distance_sq_f64(lm2_v2f64 point, lm2_edge2_f64 edge) {
  lm2_v2f64 ab = lm2_sub_lm2_v2f64(edge.end, edge.start);
  lm2_v2f64 ap = lm2_sub_lm2_v2f64(point, edge.start);

  double ab_len_sq = lm2_length_sq_v2f64(ab);

  // If segment is degenerate (start == end), return distance squared to start point
  if (ab_len_sq == 0.0) {
    return lm2_length_sq_v2f64(ap);
  }

  // Project p onto line ab, clamped to [0, 1]
  double t = lm2_div_f64(lm2_dot_v2f64(ap, ab), ab_len_sq);
  t = lm2_clamp_f64(t, 0.0, 1.0);

  // Find closest point on segment
  lm2_v2f64 closest = lm2_add_lm2_v2f64(edge.start, lm2_mul_lm2_v2f64_double(ab, t));
  lm2_v2f64 pc = lm2_sub_lm2_v2f64(point, closest);

  return lm2_length_sq_v2f64(pc);
}

LM2_API float lm2_point_to_edge2_distance_sq_f32(lm2_v2f32 point, lm2_edge2_f32 edge) {
  lm2_v2f32 ab = lm2_sub_lm2_v2f32(edge.end, edge.start);
  lm2_v2f32 ap = lm2_sub_lm2_v2f32(point, edge.start);

  float ab_len_sq = lm2_length_sq_v2f32(ab);

  // If segment is degenerate (start == end), return distance squared to start point
  if (ab_len_sq == 0.0f) {
    return lm2_length_sq_v2f32(ap);
  }

  // Project p onto line ab, clamped to [0, 1]
  float t = lm2_div_f32(lm2_dot_v2f32(ap, ab), ab_len_sq);
  t = lm2_clamp_f32(t, 0.0f, 1.0f);

  // Find closest point on segment
  lm2_v2f32 closest = lm2_add_lm2_v2f32(edge.start, lm2_mul_lm2_v2f32_float(ab, t));
  lm2_v2f32 pc = lm2_sub_lm2_v2f32(point, closest);

  return lm2_length_sq_v2f32(pc);
}

LM2_API double lm2_edge2_to_edge2_distance_sq_f64(lm2_edge2_f64 e1, lm2_edge2_f64 e2) {
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
  // Use the minimum of four point-to-segment distances
  float d1 = lm2_point_to_edge2_distance_sq_f32(e1.start, e2);
  float d2 = lm2_point_to_edge2_distance_sq_f32(e1.end, e2);
  float d3 = lm2_point_to_edge2_distance_sq_f32(e2.start, e1);
  float d4 = lm2_point_to_edge2_distance_sq_f32(e2.end, e1);

  float min1 = lm2_min_f32(d1, d2);
  float min2 = lm2_min_f32(d3, d4);
  return lm2_min_f32(min1, min2);
}
