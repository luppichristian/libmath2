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

#include "lm2/geometry3d/lm2_triangle3.h"
#include "lm2/vectors/lm2_vector3.h"
#include "lm2/scalar/lm2_safe_ops.h"
#include "lm2/scalar/lm2_scalar.h"
#include "lm2/geometry3d/lm2_edge3.h"
#include "lm2/vectors/lm2_vector_specifics.h"

// =============================================================================
// Construction Helpers
// =============================================================================

LM2_API void lm2_triangle3_make_f64(lm2_triangle3_f64 tri, lm2_v3_f64 a, lm2_v3_f64 b, lm2_v3_f64 c) {
  tri[0] = a;
  tri[1] = b;
  tri[2] = c;
}

LM2_API void lm2_triangle3_make_f32(lm2_triangle3_f32 tri, lm2_v3_f32 a, lm2_v3_f32 b, lm2_v3_f32 c) {
  tri[0] = a;
  tri[1] = b;
  tri[2] = c;
}

LM2_API void lm2_triangle3_make_coords_f64(lm2_triangle3_f64 tri, double ax, double ay, double az, double bx, double by, double bz, double cx, double cy, double cz) {
  tri[0].x = ax;
  tri[0].y = ay;
  tri[0].z = az;
  tri[1].x = bx;
  tri[1].y = by;
  tri[1].z = bz;
  tri[2].x = cx;
  tri[2].y = cy;
  tri[2].z = cz;
}

LM2_API void lm2_triangle3_make_coords_f32(lm2_triangle3_f32 tri, float ax, float ay, float az, float bx, float by, float bz, float cx, float cy, float cz) {
  tri[0].x = ax;
  tri[0].y = ay;
  tri[0].z = az;
  tri[1].x = bx;
  tri[1].y = by;
  tri[1].z = bz;
  tri[2].x = cx;
  tri[2].y = cy;
  tri[2].z = cz;
}

// =============================================================================
// Triangle Properties
// =============================================================================

LM2_API double lm2_triangle3_area_f64(const lm2_triangle3_f64 tri) {
  // Area = 0.5 * |cross(AB, AC)|
  lm2_v3_f64 ab = lm2_v3_sub_f64(tri[1], tri[0]);
  lm2_v3_f64 ac = lm2_v3_sub_f64(tri[2], tri[0]);
  lm2_v3_f64 cross = lm2_v3_cross_f64(ab, ac);
  double length = lm2_v3_length_f64(cross);
  return lm2_mul_f64(0.5, length);
}

LM2_API float lm2_triangle3_area_f32(const lm2_triangle3_f32 tri) {
  lm2_v3_f32 ab = lm2_v3_sub_f32(tri[1], tri[0]);
  lm2_v3_f32 ac = lm2_v3_sub_f32(tri[2], tri[0]);
  lm2_v3_f32 cross = lm2_v3_cross_f32(ab, ac);
  float length = lm2_v3_length_f32(cross);
  return lm2_mul_f32(0.5f, length);
}

LM2_API double lm2_triangle3_perimeter_f64(const lm2_triangle3_f64 tri) {
  double ab = lm2_v3_distance_f64(tri[0], tri[1]);
  double bc = lm2_v3_distance_f64(tri[1], tri[2]);
  double ca = lm2_v3_distance_f64(tri[2], tri[0]);
  return lm2_add_f64(lm2_add_f64(ab, bc), ca);
}

LM2_API float lm2_triangle3_perimeter_f32(const lm2_triangle3_f32 tri) {
  float ab = lm2_v3_distance_f32(tri[0], tri[1]);
  float bc = lm2_v3_distance_f32(tri[1], tri[2]);
  float ca = lm2_v3_distance_f32(tri[2], tri[0]);
  return lm2_add_f32(lm2_add_f32(ab, bc), ca);
}

LM2_API lm2_v3_f64 lm2_triangle3_normal_f64(const lm2_triangle3_f64 tri) {
  lm2_v3_f64 ab = lm2_v3_sub_f64(tri[1], tri[0]);
  lm2_v3_f64 ac = lm2_v3_sub_f64(tri[2], tri[0]);
  lm2_v3_f64 cross = lm2_v3_cross_f64(ab, ac);
  return lm2_v3_normalize_f64(cross);
}

LM2_API lm2_v3_f32 lm2_triangle3_normal_f32(const lm2_triangle3_f32 tri) {
  lm2_v3_f32 ab = lm2_v3_sub_f32(tri[1], tri[0]);
  lm2_v3_f32 ac = lm2_v3_sub_f32(tri[2], tri[0]);
  lm2_v3_f32 cross = lm2_v3_cross_f32(ab, ac);
  return lm2_v3_normalize_f32(cross);
}

LM2_API lm2_v3_f64 lm2_triangle3_centroid_f64(const lm2_triangle3_f64 tri) {
  lm2_v3_f64 sum = lm2_v3_add_f64(lm2_v3_add_f64(tri[0], tri[1]), tri[2]);
  return lm2_v3_mul_s_f64(sum, lm2_div_f64(1.0, 3.0));
}

LM2_API lm2_v3_f32 lm2_triangle3_centroid_f32(const lm2_triangle3_f32 tri) {
  lm2_v3_f32 sum = lm2_v3_add_f32(lm2_v3_add_f32(tri[0], tri[1]), tri[2]);
  return lm2_v3_mul_s_f32(sum, lm2_div_f32(1.0f, 3.0f));
}

// =============================================================================
// Triangle Classification
// =============================================================================

LM2_API bool lm2_triangle3_is_degenerate_f64(const lm2_triangle3_f64 tri, double epsilon) {
  double area = lm2_triangle3_area_f64(tri);
  return area < epsilon;
}

LM2_API bool lm2_triangle3_is_degenerate_f32(const lm2_triangle3_f32 tri, float epsilon) {
  float area = lm2_triangle3_area_f32(tri);
  return area < epsilon;
}

LM2_API bool lm2_triangle3_is_right_f64(const lm2_triangle3_f64 tri, double epsilon) {
  // Calculate squared side lengths
  lm2_v3_f64 ab = lm2_v3_sub_f64(tri[1], tri[0]);
  double ab_sq = lm2_v3_dot_f64(ab, ab);

  lm2_v3_f64 bc = lm2_v3_sub_f64(tri[2], tri[1]);
  double bc_sq = lm2_v3_dot_f64(bc, bc);

  lm2_v3_f64 ca = lm2_v3_sub_f64(tri[0], tri[2]);
  double ca_sq = lm2_v3_dot_f64(ca, ca);

  // Check if any combination satisfies Pythagorean theorem: a² + b² = c²
  double sum1 = lm2_add_f64(ab_sq, bc_sq);
  double sum2 = lm2_add_f64(bc_sq, ca_sq);
  double sum3 = lm2_add_f64(ca_sq, ab_sq);

  return (lm2_abs_f64(lm2_sub_f64(sum1, ca_sq)) < epsilon) ||
         (lm2_abs_f64(lm2_sub_f64(sum2, ab_sq)) < epsilon) ||
         (lm2_abs_f64(lm2_sub_f64(sum3, bc_sq)) < epsilon);
}

LM2_API bool lm2_triangle3_is_right_f32(const lm2_triangle3_f32 tri, float epsilon) {
  lm2_v3_f32 ab = lm2_v3_sub_f32(tri[1], tri[0]);
  float ab_sq = lm2_v3_dot_f32(ab, ab);

  lm2_v3_f32 bc = lm2_v3_sub_f32(tri[2], tri[1]);
  float bc_sq = lm2_v3_dot_f32(bc, bc);

  lm2_v3_f32 ca = lm2_v3_sub_f32(tri[0], tri[2]);
  float ca_sq = lm2_v3_dot_f32(ca, ca);

  float sum1 = lm2_add_f32(ab_sq, bc_sq);
  float sum2 = lm2_add_f32(bc_sq, ca_sq);
  float sum3 = lm2_add_f32(ca_sq, ab_sq);

  return (lm2_abs_f32(lm2_sub_f32(sum1, ca_sq)) < epsilon) ||
         (lm2_abs_f32(lm2_sub_f32(sum2, ab_sq)) < epsilon) ||
         (lm2_abs_f32(lm2_sub_f32(sum3, bc_sq)) < epsilon);
}

LM2_API bool lm2_triangle3_is_isosceles_f64(const lm2_triangle3_f64 tri, double epsilon) {
  double ab = lm2_v3_distance_f64(tri[0], tri[1]);
  double bc = lm2_v3_distance_f64(tri[1], tri[2]);
  double ca = lm2_v3_distance_f64(tri[2], tri[0]);

  bool ab_eq_bc = lm2_abs_f64(lm2_sub_f64(ab, bc)) < epsilon;
  bool bc_eq_ca = lm2_abs_f64(lm2_sub_f64(bc, ca)) < epsilon;
  bool ca_eq_ab = lm2_abs_f64(lm2_sub_f64(ca, ab)) < epsilon;

  return ab_eq_bc || bc_eq_ca || ca_eq_ab;
}

LM2_API bool lm2_triangle3_is_isosceles_f32(const lm2_triangle3_f32 tri, float epsilon) {
  float ab = lm2_v3_distance_f32(tri[0], tri[1]);
  float bc = lm2_v3_distance_f32(tri[1], tri[2]);
  float ca = lm2_v3_distance_f32(tri[2], tri[0]);

  bool ab_eq_bc = lm2_abs_f32(lm2_sub_f32(ab, bc)) < epsilon;
  bool bc_eq_ca = lm2_abs_f32(lm2_sub_f32(bc, ca)) < epsilon;
  bool ca_eq_ab = lm2_abs_f32(lm2_sub_f32(ca, ab)) < epsilon;

  return ab_eq_bc || bc_eq_ca || ca_eq_ab;
}

LM2_API bool lm2_triangle3_is_equilateral_f64(const lm2_triangle3_f64 tri, double epsilon) {
  double ab = lm2_v3_distance_f64(tri[0], tri[1]);
  double bc = lm2_v3_distance_f64(tri[1], tri[2]);
  double ca = lm2_v3_distance_f64(tri[2], tri[0]);

  bool ab_eq_bc = lm2_abs_f64(lm2_sub_f64(ab, bc)) < epsilon;
  bool bc_eq_ca = lm2_abs_f64(lm2_sub_f64(bc, ca)) < epsilon;

  return ab_eq_bc && bc_eq_ca;
}

LM2_API bool lm2_triangle3_is_equilateral_f32(const lm2_triangle3_f32 tri, float epsilon) {
  float ab = lm2_v3_distance_f32(tri[0], tri[1]);
  float bc = lm2_v3_distance_f32(tri[1], tri[2]);
  float ca = lm2_v3_distance_f32(tri[2], tri[0]);

  bool ab_eq_bc = lm2_abs_f32(lm2_sub_f32(ab, bc)) < epsilon;
  bool bc_eq_ca = lm2_abs_f32(lm2_sub_f32(bc, ca)) < epsilon;

  return ab_eq_bc && bc_eq_ca;
}

LM2_API bool lm2_triangle3_is_scalene_f64(const lm2_triangle3_f64 tri, double epsilon) {
  double ab = lm2_v3_distance_f64(tri[0], tri[1]);
  double bc = lm2_v3_distance_f64(tri[1], tri[2]);
  double ca = lm2_v3_distance_f64(tri[2], tri[0]);

  bool ab_ne_bc = lm2_abs_f64(lm2_sub_f64(ab, bc)) >= epsilon;
  bool bc_ne_ca = lm2_abs_f64(lm2_sub_f64(bc, ca)) >= epsilon;
  bool ca_ne_ab = lm2_abs_f64(lm2_sub_f64(ca, ab)) >= epsilon;

  return ab_ne_bc && bc_ne_ca && ca_ne_ab;
}

LM2_API bool lm2_triangle3_is_scalene_f32(const lm2_triangle3_f32 tri, float epsilon) {
  float ab = lm2_v3_distance_f32(tri[0], tri[1]);
  float bc = lm2_v3_distance_f32(tri[1], tri[2]);
  float ca = lm2_v3_distance_f32(tri[2], tri[0]);

  bool ab_ne_bc = lm2_abs_f32(lm2_sub_f32(ab, bc)) >= epsilon;
  bool bc_ne_ca = lm2_abs_f32(lm2_sub_f32(bc, ca)) >= epsilon;
  bool ca_ne_ab = lm2_abs_f32(lm2_sub_f32(ca, ab)) >= epsilon;

  return ab_ne_bc && bc_ne_ca && ca_ne_ab;
}

LM2_API lm2_triangle3_type lm2_triangle3_classify_f64(const lm2_triangle3_f64 tri, double epsilon) {
  // Check degenerate first
  if (lm2_triangle3_is_degenerate_f64(tri, epsilon)) {
    return LM2_TRIANGLE3_DEGENERATE;
  }

  // Check right triangle (highest priority after degenerate)
  if (lm2_triangle3_is_right_f64(tri, epsilon)) {
    return LM2_TRIANGLE3_RIGHT;
  }

  // Check equilateral (all sides equal)
  if (lm2_triangle3_is_equilateral_f64(tri, epsilon)) {
    return LM2_TRIANGLE3_EQUILATERAL;
  }

  // Check isosceles (two sides equal)
  if (lm2_triangle3_is_isosceles_f64(tri, epsilon)) {
    return LM2_TRIANGLE3_ISOSCELES;
  }

  // Default to scalene (all sides different)
  return LM2_TRIANGLE3_SCALENE;
}

LM2_API lm2_triangle3_type lm2_triangle3_classify_f32(const lm2_triangle3_f32 tri, float epsilon) {
  if (lm2_triangle3_is_degenerate_f32(tri, epsilon)) {
    return LM2_TRIANGLE3_DEGENERATE;
  }

  if (lm2_triangle3_is_right_f32(tri, epsilon)) {
    return LM2_TRIANGLE3_RIGHT;
  }

  if (lm2_triangle3_is_equilateral_f32(tri, epsilon)) {
    return LM2_TRIANGLE3_EQUILATERAL;
  }

  if (lm2_triangle3_is_isosceles_f32(tri, epsilon)) {
    return LM2_TRIANGLE3_ISOSCELES;
  }

  return LM2_TRIANGLE3_SCALENE;
}

// =============================================================================
// Triangle-Point Intersection
// =============================================================================

LM2_API bool lm2_triangle3_contains_point_f64(const lm2_triangle3_f64 tri, lm2_v3_f64 point, double epsilon) {
  // First check if point is coplanar with the triangle
  lm2_v3_f64 normal = lm2_triangle3_normal_f64(tri);
  lm2_v3_f64 to_point = lm2_v3_sub_f64(point, tri[0]);
  double distance_to_plane = lm2_abs_f64(lm2_v3_dot_f64(normal, to_point));

  if (distance_to_plane > epsilon) {
    return false;  // Point is not on the triangle's plane
  }

  // Use barycentric coordinates
  lm2_v3_f64 v0 = lm2_v3_sub_f64(tri[1], tri[0]);
  lm2_v3_f64 v1 = lm2_v3_sub_f64(tri[2], tri[0]);
  lm2_v3_f64 v2 = lm2_v3_sub_f64(point, tri[0]);

  double dot00 = lm2_v3_dot_f64(v0, v0);
  double dot01 = lm2_v3_dot_f64(v0, v1);
  double dot02 = lm2_v3_dot_f64(v0, v2);
  double dot11 = lm2_v3_dot_f64(v1, v1);
  double dot12 = lm2_v3_dot_f64(v1, v2);

  double inv_denom = lm2_div_f64(1.0, lm2_sub_f64(lm2_mul_f64(dot00, dot11), lm2_mul_f64(dot01, dot01)));
  double u = lm2_mul_f64(lm2_sub_f64(lm2_mul_f64(dot11, dot02), lm2_mul_f64(dot01, dot12)), inv_denom);
  double v = lm2_mul_f64(lm2_sub_f64(lm2_mul_f64(dot00, dot12), lm2_mul_f64(dot01, dot02)), inv_denom);

  return (u >= 0.0) && (v >= 0.0) && (lm2_add_f64(u, v) <= 1.0);
}

LM2_API bool lm2_triangle3_contains_point_f32(const lm2_triangle3_f32 tri, lm2_v3_f32 point, float epsilon) {
  lm2_v3_f32 normal = lm2_triangle3_normal_f32(tri);
  lm2_v3_f32 to_point = lm2_v3_sub_f32(point, tri[0]);
  float distance_to_plane = lm2_abs_f32(lm2_v3_dot_f32(normal, to_point));

  if (distance_to_plane > epsilon) {
    return false;
  }

  lm2_v3_f32 v0 = lm2_v3_sub_f32(tri[1], tri[0]);
  lm2_v3_f32 v1 = lm2_v3_sub_f32(tri[2], tri[0]);
  lm2_v3_f32 v2 = lm2_v3_sub_f32(point, tri[0]);

  float dot00 = lm2_v3_dot_f32(v0, v0);
  float dot01 = lm2_v3_dot_f32(v0, v1);
  float dot02 = lm2_v3_dot_f32(v0, v2);
  float dot11 = lm2_v3_dot_f32(v1, v1);
  float dot12 = lm2_v3_dot_f32(v1, v2);

  float inv_denom = lm2_div_f32(1.0f, lm2_sub_f32(lm2_mul_f32(dot00, dot11), lm2_mul_f32(dot01, dot01)));
  float u = lm2_mul_f32(lm2_sub_f32(lm2_mul_f32(dot11, dot02), lm2_mul_f32(dot01, dot12)), inv_denom);
  float v = lm2_mul_f32(lm2_sub_f32(lm2_mul_f32(dot00, dot12), lm2_mul_f32(dot01, dot02)), inv_denom);

  return (u >= 0.0f) && (v >= 0.0f) && (lm2_add_f32(u, v) <= 1.0f);
}

// =============================================================================
// Triangle-Triangle Intersection
// =============================================================================

LM2_API bool lm2_triangle3_overlaps_f64(const lm2_triangle3_f64 t1, const lm2_triangle3_f64 t2, double epsilon) {
  // Check if any vertex of t1 is inside t2
  if (lm2_triangle3_contains_point_f64(t2, t1[0], epsilon) ||
      lm2_triangle3_contains_point_f64(t2, t1[1], epsilon) ||
      lm2_triangle3_contains_point_f64(t2, t1[2], epsilon)) {
    return true;
  }

  // Check if any vertex of t2 is inside t1
  if (lm2_triangle3_contains_point_f64(t1, t2[0], epsilon) ||
      lm2_triangle3_contains_point_f64(t1, t2[1], epsilon) ||
      lm2_triangle3_contains_point_f64(t1, t2[2], epsilon)) {
    return true;
  }

  // For a more complete 3D triangle-triangle intersection test,
  // we would need to check edge-triangle intersections as well.
  // This simplified version checks vertex containment only.
  return false;
}

LM2_API bool lm2_triangle3_overlaps_f32(const lm2_triangle3_f32 t1, const lm2_triangle3_f32 t2, float epsilon) {
  if (lm2_triangle3_contains_point_f32(t2, t1[0], epsilon) ||
      lm2_triangle3_contains_point_f32(t2, t1[1], epsilon) ||
      lm2_triangle3_contains_point_f32(t2, t1[2], epsilon)) {
    return true;
  }

  if (lm2_triangle3_contains_point_f32(t1, t2[0], epsilon) ||
      lm2_triangle3_contains_point_f32(t1, t2[1], epsilon) ||
      lm2_triangle3_contains_point_f32(t1, t2[2], epsilon)) {
    return true;
  }

  return false;
}

// =============================================================================
// Triangle-Edge Operations
// =============================================================================

LM2_API lm2_edge3_result_f64 lm2_triangle3_shared_edge_f64(const lm2_triangle3_f64 t1, const lm2_triangle3_f64 t2, double epsilon) {
  lm2_edge3_result_f64 result;
  result.exists = false;

  // Define edges of both triangles
  lm2_edge3_f64 t1_edges[3] = {
      {t1[0], t1[1]},
      {t1[1], t1[2]},
      {t1[2], t1[0]}
  };
  lm2_edge3_f64 t2_edges[3] = {
      {t2[0], t2[1]},
      {t2[1], t2[2]},
      {t2[2], t2[0]}
  };

  // Check each edge of t1 against each edge of t2
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (lm2_edges3_equal_f64(t1_edges[i], t2_edges[j], epsilon)) {
        result.edge = t1_edges[i];
        result.exists = true;
        return result;
      }
    }
  }

  return result;
}

LM2_API lm2_edge3_result_f32 lm2_triangle3_shared_edge_f32(const lm2_triangle3_f32 t1, const lm2_triangle3_f32 t2, float epsilon) {
  lm2_edge3_result_f32 result;
  result.exists = false;

  lm2_edge3_f32 t1_edges[3] = {
      {t1[0], t1[1]},
      {t1[1], t1[2]},
      {t1[2], t1[0]}
  };
  lm2_edge3_f32 t2_edges[3] = {
      {t2[0], t2[1]},
      {t2[1], t2[2]},
      {t2[2], t2[0]}
  };

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (lm2_edges3_equal_f32(t1_edges[i], t2_edges[j], epsilon)) {
        result.edge = t1_edges[i];
        result.exists = true;
        return result;
      }
    }
  }

  return result;
}
