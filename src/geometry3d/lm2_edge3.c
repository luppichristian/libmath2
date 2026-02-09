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

#include <lm2/geometry3d/lm2_edge3.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/vectors/lm2_vector_specifics.h>

// =============================================================================
// Construction Helpers
// =============================================================================

LM2_API lm2_edge3_f64 lm2_edge3_make_f64(lm2_v3f64 start, lm2_v3f64 end) {
  lm2_edge3_f64 edge;
  edge.start = start;
  edge.end = end;
  return edge;
}

LM2_API lm2_edge3_f32 lm2_edge3_make_f32(lm2_v3f32 start, lm2_v3f32 end) {
  lm2_edge3_f32 edge;
  edge.start = start;
  edge.end = end;
  return edge;
}

LM2_API lm2_edge3_f64 lm2_edge3_make_coords_f64(double x1, double y1, double z1, double x2, double y2, double z2) {
  lm2_edge3_f64 edge;
  edge.start.x = x1;
  edge.start.y = y1;
  edge.start.z = z1;
  edge.end.x = x2;
  edge.end.y = y2;
  edge.end.z = z2;
  return edge;
}

LM2_API lm2_edge3_f32 lm2_edge3_make_coords_f32(float x1, float y1, float z1, float x2, float y2, float z2) {
  lm2_edge3_f32 edge;
  edge.start.x = x1;
  edge.start.y = y1;
  edge.start.z = z1;
  edge.end.x = x2;
  edge.end.y = y2;
  edge.end.z = z2;
  return edge;
}

// =============================================================================
// Edge Properties
// =============================================================================

LM2_API double lm2_edge3_length_sq_f64(lm2_edge3_f64 edge) {
  double dx = lm2_sub_f64(edge.end.x, edge.start.x);
  double dy = lm2_sub_f64(edge.end.y, edge.start.y);
  double dz = lm2_sub_f64(edge.end.z, edge.start.z);
  return lm2_add_f64(lm2_add_f64(lm2_mul_f64(dx, dx), lm2_mul_f64(dy, dy)), lm2_mul_f64(dz, dz));
}

LM2_API float lm2_edge3_length_sq_f32(lm2_edge3_f32 edge) {
  float dx = lm2_sub_f32(edge.end.x, edge.start.x);
  float dy = lm2_sub_f32(edge.end.y, edge.start.y);
  float dz = lm2_sub_f32(edge.end.z, edge.start.z);
  return lm2_add_f32(lm2_add_f32(lm2_mul_f32(dx, dx), lm2_mul_f32(dy, dy)), lm2_mul_f32(dz, dz));
}

LM2_API double lm2_edge3_length_f64(lm2_edge3_f64 edge) {
  return lm2_sqrt_f64(lm2_edge3_length_sq_f64(edge));
}

LM2_API float lm2_edge3_length_f32(lm2_edge3_f32 edge) {
  return lm2_sqrt_f32(lm2_edge3_length_sq_f32(edge));
}

// =============================================================================
// Edge Comparison
// =============================================================================

LM2_API bool lm2_points3_equal_f64(lm2_v3f64 a, lm2_v3f64 b, double epsilon) {
  double dx = lm2_abs_f64(lm2_sub_f64(a.x, b.x));
  double dy = lm2_abs_f64(lm2_sub_f64(a.y, b.y));
  double dz = lm2_abs_f64(lm2_sub_f64(a.z, b.z));
  return (dx < epsilon) && (dy < epsilon) && (dz < epsilon);
}

LM2_API bool lm2_points3_equal_f32(lm2_v3f32 a, lm2_v3f32 b, float epsilon) {
  float dx = lm2_abs_f32(lm2_sub_f32(a.x, b.x));
  float dy = lm2_abs_f32(lm2_sub_f32(a.y, b.y));
  float dz = lm2_abs_f32(lm2_sub_f32(a.z, b.z));
  return (dx < epsilon) && (dy < epsilon) && (dz < epsilon);
}

LM2_API bool lm2_edges3_equal_f64(lm2_edge3_f64 e1, lm2_edge3_f64 e2, double epsilon) {
  return (lm2_points3_equal_f64(e1.start, e2.start, epsilon) && lm2_points3_equal_f64(e1.end, e2.end, epsilon)) ||
         (lm2_points3_equal_f64(e1.start, e2.end, epsilon) && lm2_points3_equal_f64(e1.end, e2.start, epsilon));
}

LM2_API bool lm2_edges3_equal_f32(lm2_edge3_f32 e1, lm2_edge3_f32 e2, float epsilon) {
  return (lm2_points3_equal_f32(e1.start, e2.start, epsilon) && lm2_points3_equal_f32(e1.end, e2.end, epsilon)) ||
         (lm2_points3_equal_f32(e1.start, e2.end, epsilon) && lm2_points3_equal_f32(e1.end, e2.start, epsilon));
}

// =============================================================================
// Edge Intersection
// =============================================================================

LM2_API bool lm2_edges3_intersect_f64(lm2_edge3_f64 e1, lm2_edge3_f64 e2, double epsilon) {
  // Compute direction vectors
  lm2_v3f64 d1 = lm2_sub_lm2_v3f64(e1.end, e1.start);
  lm2_v3f64 d2 = lm2_sub_lm2_v3f64(e2.end, e2.start);
  lm2_v3f64 r = lm2_sub_lm2_v3f64(e2.start, e1.start);

  // Cross product of direction vectors
  lm2_v3f64 cross_d1_d2 = lm2_cross_v3f64(d1, d2);
  double cross_mag_sq = lm2_dot_v3f64(cross_d1_d2, cross_d1_d2);

  // Check if lines are parallel
  if (cross_mag_sq < lm2_mul_f64(epsilon, epsilon)) {
    // Lines are parallel, check if they're on the same line
    lm2_v3f64 cross_r_d1 = lm2_cross_v3f64(r, d1);
    double cross_r_d1_mag_sq = lm2_dot_v3f64(cross_r_d1, cross_r_d1);
    if (cross_r_d1_mag_sq < lm2_mul_f64(epsilon, epsilon)) {
      // Collinear segments - check for overlap
      double d1_dot = lm2_dot_v3f64(d1, d1);
      if (d1_dot < lm2_mul_f64(epsilon, epsilon)) {
        return false;  // First segment is degenerate
      }
      double t0 = lm2_div_f64(lm2_dot_v3f64(r, d1), d1_dot);
      double t1 = lm2_div_f64(lm2_dot_v3f64(lm2_add_lm2_v3f64(r, d2), d1), d1_dot);
      double t_min = lm2_min_f64(t0, t1);
      double t_max = lm2_max_f64(t0, t1);
      return (t_min <= 1.0) && (t_max >= 0.0);
    }
    return false;  // Parallel but not collinear
  }

  // Compute parameters for closest points
  double r_cross_d2_dot_cross = lm2_dot_v3f64(lm2_cross_v3f64(r, d2), cross_d1_d2);
  double t1 = lm2_div_f64(r_cross_d2_dot_cross, cross_mag_sq);

  double r_cross_d1_dot_cross = lm2_dot_v3f64(lm2_cross_v3f64(r, d1), cross_d1_d2);
  double t2 = lm2_div_f64(r_cross_d1_dot_cross, cross_mag_sq);

  // Check if parameters are within [0,1]
  if (t1 < 0.0 || t1 > 1.0 || t2 < 0.0 || t2 > 1.0) {
    return false;
  }

  // Compute closest points
  lm2_v3f64 p1 = lm2_add_lm2_v3f64(e1.start, lm2_mul_lm2_v3f64_double(d1, t1));
  lm2_v3f64 p2 = lm2_add_lm2_v3f64(e2.start, lm2_mul_lm2_v3f64_double(d2, t2));

  // Check distance between closest points
  return lm2_distance_v3f64(p1, p2) < epsilon;
}

LM2_API bool lm2_edges3_intersect_f32(lm2_edge3_f32 e1, lm2_edge3_f32 e2, float epsilon) {
  // Compute direction vectors
  lm2_v3f32 d1 = lm2_sub_lm2_v3f32(e1.end, e1.start);
  lm2_v3f32 d2 = lm2_sub_lm2_v3f32(e2.end, e2.start);
  lm2_v3f32 r = lm2_sub_lm2_v3f32(e2.start, e1.start);

  // Cross product of direction vectors
  lm2_v3f32 cross_d1_d2 = lm2_cross_v3f32(d1, d2);
  float cross_mag_sq = lm2_dot_v3f32(cross_d1_d2, cross_d1_d2);

  // Check if lines are parallel
  if (cross_mag_sq < lm2_mul_f32(epsilon, epsilon)) {
    // Lines are parallel, check if they're on the same line
    lm2_v3f32 cross_r_d1 = lm2_cross_v3f32(r, d1);
    float cross_r_d1_mag_sq = lm2_dot_v3f32(cross_r_d1, cross_r_d1);
    if (cross_r_d1_mag_sq < lm2_mul_f32(epsilon, epsilon)) {
      // Collinear segments - check for overlap
      float d1_dot = lm2_dot_v3f32(d1, d1);
      if (d1_dot < lm2_mul_f32(epsilon, epsilon)) {
        return false;  // First segment is degenerate
      }
      float t0 = lm2_div_f32(lm2_dot_v3f32(r, d1), d1_dot);
      float t1 = lm2_div_f32(lm2_dot_v3f32(lm2_add_lm2_v3f32(r, d2), d1), d1_dot);
      float t_min = lm2_min_f32(t0, t1);
      float t_max = lm2_max_f32(t0, t1);
      return (t_min <= 1.0f) && (t_max >= 0.0f);
    }
    return false;  // Parallel but not collinear
  }

  // Compute parameters for closest points
  float r_cross_d2_dot_cross = lm2_dot_v3f32(lm2_cross_v3f32(r, d2), cross_d1_d2);
  float t1 = lm2_div_f32(r_cross_d2_dot_cross, cross_mag_sq);

  float r_cross_d1_dot_cross = lm2_dot_v3f32(lm2_cross_v3f32(r, d1), cross_d1_d2);
  float t2 = lm2_div_f32(r_cross_d1_dot_cross, cross_mag_sq);

  // Check if parameters are within [0,1]
  if (t1 < 0.0f || t1 > 1.0f || t2 < 0.0f || t2 > 1.0f) {
    return false;
  }

  // Compute closest points
  lm2_v3f32 p1 = lm2_add_lm2_v3f32(e1.start, lm2_mul_lm2_v3f32_float(d1, t1));
  lm2_v3f32 p2 = lm2_add_lm2_v3f32(e2.start, lm2_mul_lm2_v3f32_float(d2, t2));

  // Check distance between closest points
  return lm2_distance_v3f32(p1, p2) < epsilon;
}

// =============================================================================
// Edge Distance
// =============================================================================

LM2_API double lm2_point_to_edge3_distance_sq_f64(lm2_v3f64 point, lm2_edge3_f64 edge) {
  lm2_v3f64 ab = lm2_sub_lm2_v3f64(edge.end, edge.start);
  lm2_v3f64 ap = lm2_sub_lm2_v3f64(point, edge.start);

  double ab_len_sq = lm2_length_sq_v3f64(ab);

  // If segment is degenerate (start == end), return distance squared to start point
  if (ab_len_sq == 0.0) {
    return lm2_length_sq_v3f64(ap);
  }

  // Project p onto line ab, clamped to [0, 1]
  double t = lm2_div_f64(lm2_dot_v3f64(ap, ab), ab_len_sq);
  t = lm2_clamp_f64(t, 0.0, 1.0);

  // Find closest point on segment
  lm2_v3f64 closest = lm2_add_lm2_v3f64(edge.start, lm2_mul_lm2_v3f64_double(ab, t));
  lm2_v3f64 pc = lm2_sub_lm2_v3f64(point, closest);

  return lm2_length_sq_v3f64(pc);
}

LM2_API float lm2_point_to_edge3_distance_sq_f32(lm2_v3f32 point, lm2_edge3_f32 edge) {
  lm2_v3f32 ab = lm2_sub_lm2_v3f32(edge.end, edge.start);
  lm2_v3f32 ap = lm2_sub_lm2_v3f32(point, edge.start);

  float ab_len_sq = lm2_length_sq_v3f32(ab);

  // If segment is degenerate (start == end), return distance squared to start point
  if (ab_len_sq == 0.0f) {
    return lm2_length_sq_v3f32(ap);
  }

  // Project p onto line ab, clamped to [0, 1]
  float t = lm2_div_f32(lm2_dot_v3f32(ap, ab), ab_len_sq);
  t = lm2_clamp_f32(t, 0.0f, 1.0f);

  // Find closest point on segment
  lm2_v3f32 closest = lm2_add_lm2_v3f32(edge.start, lm2_mul_lm2_v3f32_float(ab, t));
  lm2_v3f32 pc = lm2_sub_lm2_v3f32(point, closest);

  return lm2_length_sq_v3f32(pc);
}

LM2_API double lm2_edge3_to_edge3_distance_sq_f64(lm2_edge3_f64 e1, lm2_edge3_f64 e2) {
  // Use the minimum of four point-to-segment distances
  double d1 = lm2_point_to_edge3_distance_sq_f64(e1.start, e2);
  double d2 = lm2_point_to_edge3_distance_sq_f64(e1.end, e2);
  double d3 = lm2_point_to_edge3_distance_sq_f64(e2.start, e1);
  double d4 = lm2_point_to_edge3_distance_sq_f64(e2.end, e1);

  double min1 = lm2_min_f64(d1, d2);
  double min2 = lm2_min_f64(d3, d4);
  return lm2_min_f64(min1, min2);
}

LM2_API float lm2_edge3_to_edge3_distance_sq_f32(lm2_edge3_f32 e1, lm2_edge3_f32 e2) {
  // Use the minimum of four point-to-segment distances
  float d1 = lm2_point_to_edge3_distance_sq_f32(e1.start, e2);
  float d2 = lm2_point_to_edge3_distance_sq_f32(e1.end, e2);
  float d3 = lm2_point_to_edge3_distance_sq_f32(e2.start, e1);
  float d4 = lm2_point_to_edge3_distance_sq_f32(e2.end, e1);

  float min1 = lm2_min_f32(d1, d2);
  float min2 = lm2_min_f32(d3, d4);
  return lm2_min_f32(min1, min2);
}
