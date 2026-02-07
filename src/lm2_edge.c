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

#include <lm2/lm2_edge.h>
#include <lm2/lm2_safe_ops.h>
#include <lm2/lm2_scalar.h>

// =============================================================================
// Construction Helpers
// =============================================================================

LM2_API lm2_edge_f64 lm2_edge_make_f64(lm2_v2f64 start, lm2_v2f64 end) {
  lm2_edge_f64 edge;
  edge.start = start;
  edge.end = end;
  return edge;
}

LM2_API lm2_edge_f32 lm2_edge_make_f32(lm2_v2f32 start, lm2_v2f32 end) {
  lm2_edge_f32 edge;
  edge.start = start;
  edge.end = end;
  return edge;
}

LM2_API lm2_edge_f64 lm2_edge_make_coords_f64(double x1, double y1, double x2, double y2) {
  lm2_edge_f64 edge;
  edge.start.x = x1;
  edge.start.y = y1;
  edge.end.x = x2;
  edge.end.y = y2;
  return edge;
}

LM2_API lm2_edge_f32 lm2_edge_make_coords_f32(float x1, float y1, float x2, float y2) {
  lm2_edge_f32 edge;
  edge.start.x = x1;
  edge.start.y = y1;
  edge.end.x = x2;
  edge.end.y = y2;
  return edge;
}

// =============================================================================
// Edge Properties
// =============================================================================

LM2_API double lm2_edge_length_sq_f64(lm2_edge_f64 edge) {
  double dx = lm2_sub_f64(edge.end.x, edge.start.x);
  double dy = lm2_sub_f64(edge.end.y, edge.start.y);
  return lm2_add_f64(lm2_mul_f64(dx, dx), lm2_mul_f64(dy, dy));
}

LM2_API float lm2_edge_length_sq_f32(lm2_edge_f32 edge) {
  float dx = lm2_sub_f32(edge.end.x, edge.start.x);
  float dy = lm2_sub_f32(edge.end.y, edge.start.y);
  return lm2_add_f32(lm2_mul_f32(dx, dx), lm2_mul_f32(dy, dy));
}

LM2_API double lm2_edge_length_f64(lm2_edge_f64 edge) {
  return lm2_sqrt_f64(lm2_edge_length_sq_f64(edge));
}

LM2_API float lm2_edge_length_f32(lm2_edge_f32 edge) {
  return lm2_sqrt_f32(lm2_edge_length_sq_f32(edge));
}

// =============================================================================
// Edge Comparison
// =============================================================================

LM2_API bool lm2_points_equal_f64(lm2_v2f64 a, lm2_v2f64 b, double epsilon) {
  double dx = lm2_abs_f64(lm2_sub_f64(a.x, b.x));
  double dy = lm2_abs_f64(lm2_sub_f64(a.y, b.y));
  return (dx < epsilon) && (dy < epsilon);
}

LM2_API bool lm2_points_equal_f32(lm2_v2f32 a, lm2_v2f32 b, float epsilon) {
  float dx = lm2_abs_f32(lm2_sub_f32(a.x, b.x));
  float dy = lm2_abs_f32(lm2_sub_f32(a.y, b.y));
  return (dx < epsilon) && (dy < epsilon);
}

LM2_API bool lm2_edges_equal_f64(lm2_edge_f64 e1, lm2_edge_f64 e2, double epsilon) {
  return (lm2_points_equal_f64(e1.start, e2.start, epsilon) && lm2_points_equal_f64(e1.end, e2.end, epsilon)) ||
         (lm2_points_equal_f64(e1.start, e2.end, epsilon) && lm2_points_equal_f64(e1.end, e2.start, epsilon));
}

LM2_API bool lm2_edges_equal_f32(lm2_edge_f32 e1, lm2_edge_f32 e2, float epsilon) {
  return (lm2_points_equal_f32(e1.start, e2.start, epsilon) && lm2_points_equal_f32(e1.end, e2.end, epsilon)) ||
         (lm2_points_equal_f32(e1.start, e2.end, epsilon) && lm2_points_equal_f32(e1.end, e2.start, epsilon));
}

// =============================================================================
// Edge Intersection
// =============================================================================

// Helper to compute cross product sign for point relative to line
static double _lm2_point_line_sign_f64(lm2_v2f64 p, lm2_v2f64 a, lm2_v2f64 b) {
  double dx1 = lm2_sub_f64(p.x, b.x);
  double dy1 = lm2_sub_f64(a.y, b.y);
  double dx2 = lm2_sub_f64(a.x, b.x);
  double dy2 = lm2_sub_f64(p.y, b.y);

  return lm2_sub_f64(lm2_mul_f64(dx1, dy1), lm2_mul_f64(dx2, dy2));
}

static float _lm2_point_line_sign_f32(lm2_v2f32 p, lm2_v2f32 a, lm2_v2f32 b) {
  float dx1 = lm2_sub_f32(p.x, b.x);
  float dy1 = lm2_sub_f32(a.y, b.y);
  float dx2 = lm2_sub_f32(a.x, b.x);
  float dy2 = lm2_sub_f32(p.y, b.y);

  return lm2_sub_f32(lm2_mul_f32(dx1, dy1), lm2_mul_f32(dx2, dy2));
}

LM2_API bool lm2_edges_intersect_f64(lm2_edge_f64 e1, lm2_edge_f64 e2) {
  // Use cross products to check intersection
  double d1 = _lm2_point_line_sign_f64(e1.start, e2.start, e2.end);
  double d2 = _lm2_point_line_sign_f64(e1.end, e2.start, e2.end);
  double d3 = _lm2_point_line_sign_f64(e2.start, e1.start, e1.end);
  double d4 = _lm2_point_line_sign_f64(e2.end, e1.start, e1.end);

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

LM2_API bool lm2_edges_intersect_f32(lm2_edge_f32 e1, lm2_edge_f32 e2) {
  float d1 = _lm2_point_line_sign_f32(e1.start, e2.start, e2.end);
  float d2 = _lm2_point_line_sign_f32(e1.end, e2.start, e2.end);
  float d3 = _lm2_point_line_sign_f32(e2.start, e1.start, e1.end);
  float d4 = _lm2_point_line_sign_f32(e2.end, e1.start, e1.end);

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
