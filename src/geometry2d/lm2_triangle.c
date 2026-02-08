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

#include <lm2/geometry2d/lm2_triangle.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/geometry2d/lm2_edge.h>
#include <lm2/vectors/lm2_vector_specifics.h>

// =============================================================================
// Construction Helpers
// =============================================================================

LM2_API void lm2_triangle_make_f64(lm2_triangle_f64 tri, lm2_v2f64 a, lm2_v2f64 b, lm2_v2f64 c) {
  tri[0] = a;
  tri[1] = b;
  tri[2] = c;
}

LM2_API void lm2_triangle_make_f32(lm2_triangle_f32 tri, lm2_v2f32 a, lm2_v2f32 b, lm2_v2f32 c) {
  tri[0] = a;
  tri[1] = b;
  tri[2] = c;
}

LM2_API void lm2_triangle_make_coords_f64(lm2_triangle_f64 tri, double ax, double ay, double bx, double by, double cx, double cy) {
  tri[0].x = ax;
  tri[0].y = ay;
  tri[1].x = bx;
  tri[1].y = by;
  tri[2].x = cx;
  tri[2].y = cy;
}

LM2_API void lm2_triangle_make_coords_f32(lm2_triangle_f32 tri, float ax, float ay, float bx, float by, float cx, float cy) {
  tri[0].x = ax;
  tri[0].y = ay;
  tri[1].x = bx;
  tri[1].y = by;
  tri[2].x = cx;
  tri[2].y = cy;
}

// =============================================================================
// Triangle Properties
// =============================================================================

LM2_API double lm2_triangle_signed_area_f64(const lm2_triangle_f64 tri) {
  // Signed area = 0.5 * ((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y))
  double dx1 = lm2_sub_f64(tri[1].x, tri[0].x);
  double dy1 = lm2_sub_f64(tri[2].y, tri[0].y);
  double dx2 = lm2_sub_f64(tri[2].x, tri[0].x);
  double dy2 = lm2_sub_f64(tri[1].y, tri[0].y);

  double cross = lm2_sub_f64(lm2_mul_f64(dx1, dy1), lm2_mul_f64(dx2, dy2));
  return lm2_mul_f64(0.5, cross);
}

LM2_API float lm2_triangle_signed_area_f32(const lm2_triangle_f32 tri) {
  float dx1 = lm2_sub_f32(tri[1].x, tri[0].x);
  float dy1 = lm2_sub_f32(tri[2].y, tri[0].y);
  float dx2 = lm2_sub_f32(tri[2].x, tri[0].x);
  float dy2 = lm2_sub_f32(tri[1].y, tri[0].y);

  float cross = lm2_sub_f32(lm2_mul_f32(dx1, dy1), lm2_mul_f32(dx2, dy2));
  return lm2_mul_f32(0.5f, cross);
}

LM2_API double lm2_triangle_area_f64(const lm2_triangle_f64 tri) {
  return lm2_abs_f64(lm2_triangle_signed_area_f64(tri));
}

LM2_API float lm2_triangle_area_f32(const lm2_triangle_f32 tri) {
  return lm2_abs_f32(lm2_triangle_signed_area_f32(tri));
}

// =============================================================================
// Perimeter
// =============================================================================

LM2_API double lm2_triangle_perimeter_f64(const lm2_triangle_f64 tri) {
  double ab = lm2_distance_v2f64(tri[0], tri[1]);
  double bc = lm2_distance_v2f64(tri[1], tri[2]);
  double ca = lm2_distance_v2f64(tri[2], tri[0]);
  return lm2_add_f64(lm2_add_f64(ab, bc), ca);
}

LM2_API float lm2_triangle_perimeter_f32(const lm2_triangle_f32 tri) {
  float ab = lm2_distance_v2f32(tri[0], tri[1]);
  float bc = lm2_distance_v2f32(tri[1], tri[2]);
  float ca = lm2_distance_v2f32(tri[2], tri[0]);
  return lm2_add_f32(lm2_add_f32(ab, bc), ca);
}

LM2_API lm2_winding_order lm2_triangle_winding_f64(const lm2_triangle_f64 tri) {
  double signed_area = lm2_triangle_signed_area_f64(tri);
  if (lm2_abs_f64(signed_area) < DBL_EPSILON) {
    return LM2_WINDING_NONE;
  }
  return signed_area > 0.0 ? LM2_WINDING_COUNTERCLOCKWISE : LM2_WINDING_CLOCKWISE;
}

LM2_API lm2_winding_order lm2_triangle_winding_f32(const lm2_triangle_f32 tri) {
  float signed_area = lm2_triangle_signed_area_f32(tri);
  if (lm2_abs_f32(signed_area) < FLT_EPSILON) {
    return LM2_WINDING_NONE;
  }
  return signed_area > 0.0f ? LM2_WINDING_COUNTERCLOCKWISE : LM2_WINDING_CLOCKWISE;
}

// =============================================================================
// Triangle Classification
// =============================================================================

LM2_API bool lm2_triangle_is_degenerate_f64(const lm2_triangle_f64 tri, double epsilon) {
  double area = lm2_triangle_area_f64(tri);
  return area < epsilon;
}

LM2_API bool lm2_triangle_is_degenerate_f32(const lm2_triangle_f32 tri, float epsilon) {
  float area = lm2_triangle_area_f32(tri);
  return area < epsilon;
}

LM2_API bool lm2_triangle_is_right_f64(const lm2_triangle_f64 tri, double epsilon) {
  // Calculate squared side lengths
  double dx_ab = lm2_sub_f64(tri[1].x, tri[0].x);
  double dy_ab = lm2_sub_f64(tri[1].y, tri[0].y);
  double ab_sq = lm2_add_f64(lm2_mul_f64(dx_ab, dx_ab), lm2_mul_f64(dy_ab, dy_ab));

  double dx_bc = lm2_sub_f64(tri[2].x, tri[1].x);
  double dy_bc = lm2_sub_f64(tri[2].y, tri[1].y);
  double bc_sq = lm2_add_f64(lm2_mul_f64(dx_bc, dx_bc), lm2_mul_f64(dy_bc, dy_bc));

  double dx_ca = lm2_sub_f64(tri[0].x, tri[2].x);
  double dy_ca = lm2_sub_f64(tri[0].y, tri[2].y);
  double ca_sq = lm2_add_f64(lm2_mul_f64(dx_ca, dx_ca), lm2_mul_f64(dy_ca, dy_ca));

  // Check if any combination satisfies Pythagorean theorem: a² + b² = c²
  double sum1 = lm2_add_f64(ab_sq, bc_sq);
  double sum2 = lm2_add_f64(bc_sq, ca_sq);
  double sum3 = lm2_add_f64(ca_sq, ab_sq);

  return (lm2_abs_f64(lm2_sub_f64(sum1, ca_sq)) < epsilon) ||
         (lm2_abs_f64(lm2_sub_f64(sum2, ab_sq)) < epsilon) ||
         (lm2_abs_f64(lm2_sub_f64(sum3, bc_sq)) < epsilon);
}

LM2_API bool lm2_triangle_is_right_f32(const lm2_triangle_f32 tri, float epsilon) {
  float dx_ab = lm2_sub_f32(tri[1].x, tri[0].x);
  float dy_ab = lm2_sub_f32(tri[1].y, tri[0].y);
  float ab_sq = lm2_add_f32(lm2_mul_f32(dx_ab, dx_ab), lm2_mul_f32(dy_ab, dy_ab));

  float dx_bc = lm2_sub_f32(tri[2].x, tri[1].x);
  float dy_bc = lm2_sub_f32(tri[2].y, tri[1].y);
  float bc_sq = lm2_add_f32(lm2_mul_f32(dx_bc, dx_bc), lm2_mul_f32(dy_bc, dy_bc));

  float dx_ca = lm2_sub_f32(tri[0].x, tri[2].x);
  float dy_ca = lm2_sub_f32(tri[0].y, tri[2].y);
  float ca_sq = lm2_add_f32(lm2_mul_f32(dx_ca, dx_ca), lm2_mul_f32(dy_ca, dy_ca));

  float sum1 = lm2_add_f32(ab_sq, bc_sq);
  float sum2 = lm2_add_f32(bc_sq, ca_sq);
  float sum3 = lm2_add_f32(ca_sq, ab_sq);

  return (lm2_abs_f32(lm2_sub_f32(sum1, ca_sq)) < epsilon) ||
         (lm2_abs_f32(lm2_sub_f32(sum2, ab_sq)) < epsilon) ||
         (lm2_abs_f32(lm2_sub_f32(sum3, bc_sq)) < epsilon);
}

LM2_API bool lm2_triangle_is_isosceles_f64(const lm2_triangle_f64 tri, double epsilon) {
  double ab = _lm2_distance_f64(tri[0], tri[1]);
  double bc = _lm2_distance_f64(tri[1], tri[2]);
  double ca = _lm2_distance_f64(tri[2], tri[0]);

  bool ab_eq_bc = lm2_abs_f64(lm2_sub_f64(ab, bc)) < epsilon;
  bool bc_eq_ca = lm2_abs_f64(lm2_sub_f64(bc, ca)) < epsilon;
  bool ca_eq_ab = lm2_abs_f64(lm2_sub_f64(ca, ab)) < epsilon;

  return ab_eq_bc || bc_eq_ca || ca_eq_ab;
}

LM2_API bool lm2_triangle_is_isosceles_f32(const lm2_triangle_f32 tri, float epsilon) {
  float ab = _lm2_distance_f32(tri[0], tri[1]);
  float bc = _lm2_distance_f32(tri[1], tri[2]);
  float ca = _lm2_distance_f32(tri[2], tri[0]);

  bool ab_eq_bc = lm2_abs_f32(lm2_sub_f32(ab, bc)) < epsilon;
  bool bc_eq_ca = lm2_abs_f32(lm2_sub_f32(bc, ca)) < epsilon;
  bool ca_eq_ab = lm2_abs_f32(lm2_sub_f32(ca, ab)) < epsilon;

  return ab_eq_bc || bc_eq_ca || ca_eq_ab;
}

LM2_API bool lm2_triangle_is_equilateral_f64(const lm2_triangle_f64 tri, double epsilon) {
  double ab = _lm2_distance_f64(tri[0], tri[1]);
  double bc = _lm2_distance_f64(tri[1], tri[2]);
  double ca = _lm2_distance_f64(tri[2], tri[0]);

  bool ab_eq_bc = lm2_abs_f64(lm2_sub_f64(ab, bc)) < epsilon;
  bool bc_eq_ca = lm2_abs_f64(lm2_sub_f64(bc, ca)) < epsilon;

  return ab_eq_bc && bc_eq_ca;
}

LM2_API bool lm2_triangle_is_equilateral_f32(const lm2_triangle_f32 tri, float epsilon) {
  float ab = _lm2_distance_f32(tri[0], tri[1]);
  float bc = _lm2_distance_f32(tri[1], tri[2]);
  float ca = _lm2_distance_f32(tri[2], tri[0]);

  bool ab_eq_bc = lm2_abs_f32(lm2_sub_f32(ab, bc)) < epsilon;
  bool bc_eq_ca = lm2_abs_f32(lm2_sub_f32(bc, ca)) < epsilon;

  return ab_eq_bc && bc_eq_ca;
}

LM2_API bool lm2_triangle_is_scalene_f64(const lm2_triangle_f64 tri, double epsilon) {
  double ab = _lm2_distance_f64(tri[0], tri[1]);
  double bc = _lm2_distance_f64(tri[1], tri[2]);
  double ca = _lm2_distance_f64(tri[2], tri[0]);

  bool ab_ne_bc = lm2_abs_f64(lm2_sub_f64(ab, bc)) >= epsilon;
  bool bc_ne_ca = lm2_abs_f64(lm2_sub_f64(bc, ca)) >= epsilon;
  bool ca_ne_ab = lm2_abs_f64(lm2_sub_f64(ca, ab)) >= epsilon;

  return ab_ne_bc && bc_ne_ca && ca_ne_ab;
}

LM2_API bool lm2_triangle_is_scalene_f32(const lm2_triangle_f32 tri, float epsilon) {
  float ab = _lm2_distance_f32(tri[0], tri[1]);
  float bc = _lm2_distance_f32(tri[1], tri[2]);
  float ca = _lm2_distance_f32(tri[2], tri[0]);

  bool ab_ne_bc = lm2_abs_f32(lm2_sub_f32(ab, bc)) >= epsilon;
  bool bc_ne_ca = lm2_abs_f32(lm2_sub_f32(bc, ca)) >= epsilon;
  bool ca_ne_ab = lm2_abs_f32(lm2_sub_f32(ca, ab)) >= epsilon;

  return ab_ne_bc && bc_ne_ca && ca_ne_ab;
}

LM2_API lm2_triangle_type lm2_triangle_classify_f64(const lm2_triangle_f64 tri, double epsilon) {
  // Check degenerate first
  if (lm2_triangle_is_degenerate_f64(tri, epsilon)) {
    return LM2_TRIANGLE_DEGENERATE;
  }

  // Check right triangle (highest priority after degenerate)
  if (lm2_triangle_is_right_f64(tri, epsilon)) {
    return LM2_TRIANGLE_RIGHT;
  }

  // Check equilateral (all sides equal)
  if (lm2_triangle_is_equilateral_f64(tri, epsilon)) {
    return LM2_TRIANGLE_EQUILATERAL;
  }

  // Check isosceles (two sides equal)
  if (lm2_triangle_is_isosceles_f64(tri, epsilon)) {
    return LM2_TRIANGLE_ISOSCELES;
  }

  // Default to scalene (all sides different)
  return LM2_TRIANGLE_SCALENE;
}

LM2_API lm2_triangle_type lm2_triangle_classify_f32(const lm2_triangle_f32 tri, float epsilon) {
  if (lm2_triangle_is_degenerate_f32(tri, epsilon)) {
    return LM2_TRIANGLE_DEGENERATE;
  }

  if (lm2_triangle_is_right_f32(tri, epsilon)) {
    return LM2_TRIANGLE_RIGHT;
  }

  if (lm2_triangle_is_equilateral_f32(tri, epsilon)) {
    return LM2_TRIANGLE_EQUILATERAL;
  }

  if (lm2_triangle_is_isosceles_f32(tri, epsilon)) {
    return LM2_TRIANGLE_ISOSCELES;
  }

  return LM2_TRIANGLE_SCALENE;
}

// =============================================================================
// Triangle-Point Intersection
// =============================================================================

LM2_API bool lm2_triangle_contains_point_f64(const lm2_triangle_f64 tri, lm2_v2f64 point) {
  // Use barycentric coordinates method
  double d1 = lm2_cross3_v2f64(tri[1], point, tri[0]);
  double d2 = lm2_cross3_v2f64(tri[2], point, tri[1]);
  double d3 = lm2_cross3_v2f64(tri[0], point, tri[2]);

  bool has_neg = (d1 < 0.0) || (d2 < 0.0) || (d3 < 0.0);
  bool has_pos = (d1 > 0.0) || (d2 > 0.0) || (d3 > 0.0);

  return !(has_neg && has_pos);
}

LM2_API bool lm2_triangle_contains_point_f32(const lm2_triangle_f32 tri, lm2_v2f32 point) {
  float d1 = lm2_cross3_v2f32(tri[1], point, tri[0]);
  float d2 = lm2_cross3_v2f32(tri[2], point, tri[1]);
  float d3 = lm2_cross3_v2f32(tri[0], point, tri[2]);

  bool has_neg = (d1 < 0.0f) || (d2 < 0.0f) || (d3 < 0.0f);
  bool has_pos = (d1 > 0.0f) || (d2 > 0.0f) || (d3 > 0.0f);

  return !(has_neg && has_pos);
}

// =============================================================================
// Triangle-Triangle Intersection
// =============================================================================

LM2_API bool lm2_triangle_overlaps_f64(const lm2_triangle_f64 t1, const lm2_triangle_f64 t2) {
  // Check if any vertex of t1 is inside t2
  if (lm2_triangle_contains_point_f64(t2, t1[0]) ||
      lm2_triangle_contains_point_f64(t2, t1[1]) ||
      lm2_triangle_contains_point_f64(t2, t1[2])) {
    return true;
  }

  // Check if any vertex of t2 is inside t1
  if (lm2_triangle_contains_point_f64(t1, t2[0]) ||
      lm2_triangle_contains_point_f64(t1, t2[1]) ||
      lm2_triangle_contains_point_f64(t1, t2[2])) {
    return true;
  }

  // Check if any edges intersect
  lm2_edge_f64 t1_edges[3] = {
      {t1[0], t1[1]},
      {t1[1], t1[2]},
      {t1[2], t1[0]}
  };
  lm2_edge_f64 t2_edges[3] = {
      {t2[0], t2[1]},
      {t2[1], t2[2]},
      {t2[2], t2[0]}
  };

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (lm2_edges_intersect_f64(t1_edges[i], t2_edges[j])) {
        return true;
      }
    }
  }

  return false;
}

LM2_API bool lm2_triangle_overlaps_f32(const lm2_triangle_f32 t1, const lm2_triangle_f32 t2) {
  if (lm2_triangle_contains_point_f32(t2, t1[0]) ||
      lm2_triangle_contains_point_f32(t2, t1[1]) ||
      lm2_triangle_contains_point_f32(t2, t1[2])) {
    return true;
  }

  if (lm2_triangle_contains_point_f32(t1, t2[0]) ||
      lm2_triangle_contains_point_f32(t1, t2[1]) ||
      lm2_triangle_contains_point_f32(t1, t2[2])) {
    return true;
  }

  lm2_edge_f32 t1_edges[3] = {
      {t1[0], t1[1]},
      {t1[1], t1[2]},
      {t1[2], t1[0]}
  };
  lm2_edge_f32 t2_edges[3] = {
      {t2[0], t2[1]},
      {t2[1], t2[2]},
      {t2[2], t2[0]}
  };

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (lm2_edges_intersect_f32(t1_edges[i], t2_edges[j])) {
        return true;
      }
    }
  }

  return false;
}

// =============================================================================
// Triangle-Edge Operations
// =============================================================================

LM2_API lm2_edge_result_f64 lm2_triangle_shared_edge_f64(const lm2_triangle_f64 t1, const lm2_triangle_f64 t2, double epsilon) {
  lm2_edge_result_f64 result;
  result.exists = false;

  // Define edges of both triangles
  lm2_edge_f64 t1_edges[3] = {
      {t1[0], t1[1]},
      {t1[1], t1[2]},
      {t1[2], t1[0]}
  };
  lm2_edge_f64 t2_edges[3] = {
      {t2[0], t2[1]},
      {t2[1], t2[2]},
      {t2[2], t2[0]}
  };

  // Check each edge of t1 against each edge of t2
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (lm2_edges_equal_f64(t1_edges[i], t2_edges[j], epsilon)) {
        result.edge = t1_edges[i];
        result.exists = true;
        return result;
      }
    }
  }

  return result;
}

LM2_API lm2_edge_result_f32 lm2_triangle_shared_edge_f32(const lm2_triangle_f32 t1, const lm2_triangle_f32 t2, float epsilon) {
  lm2_edge_result_f32 result;
  result.exists = false;

  lm2_edge_f32 t1_edges[3] = {
      {t1[0], t1[1]},
      {t1[1], t1[2]},
      {t1[2], t1[0]}
  };
  lm2_edge_f32 t2_edges[3] = {
      {t2[0], t2[1]},
      {t2[1], t2[2]},
      {t2[2], t2[0]}
  };

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (lm2_edges_equal_f32(t1_edges[i], t2_edges[j], epsilon)) {
        result.edge = t1_edges[i];
        result.exists = true;
        return result;
      }
    }
  }

  return result;
}
