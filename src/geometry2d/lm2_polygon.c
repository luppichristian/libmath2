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

#include <lm2/geometry2d/lm2_polygon.h>
#include <lm2/geometry2d/lm2_edge2.h>
#include <lm2/geometry2d/lm2_triangle2.h>
#include <lm2/lm2_constants.h>
#include <lm2/ranges/lm2_range2.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/scalar/lm2_trigonometry.h>
#include <lm2/vectors/lm2_vector2.h>
#include <lm2/vectors/lm2_vector_specifics.h>
#include <stdlib.h>

// =============================================================================
// Construction Helpers
// =============================================================================

LM2_API lm2_polygon_f64 lm2_polygon_make_f64(lm2_v2_f64* vertices, size_t vertex_count) {
  LM2_ASSERT(vertices != NULL);
  LM2_ASSERT(vertex_count >= 3);
  lm2_polygon_f64 polygon;
  polygon.vertices = vertices;
  polygon.vertex_count = vertex_count;
  return polygon;
}

LM2_API lm2_polygon_f32 lm2_polygon_make_f32(lm2_v2_f32* vertices, size_t vertex_count) {
  LM2_ASSERT(vertices != NULL);
  LM2_ASSERT(vertex_count >= 3);
  lm2_polygon_f32 polygon;
  polygon.vertices = vertices;
  polygon.vertex_count = vertex_count;
  return polygon;
}

LM2_API void lm2_polygon_make_regular_f64(lm2_v2_f64* out_vertices, size_t num_sides, lm2_v2_f64 center, double radius) {
  LM2_ASSERT(out_vertices != NULL);
  LM2_ASSERT(num_sides >= 3);
  LM2_ASSERT(radius >= 0.0);

  double angle_step = lm2_div_f64(lm2_mul_f64(2.0, LM2_PI_F64), (double)num_sides);

  for (size_t i = 0; i < num_sides; i++) {
    double angle = lm2_mul_f64((double)i, angle_step);
    out_vertices[i].x = lm2_add_f64(center.x, lm2_mul_f64(lm2_cos_f64(angle), radius));
    out_vertices[i].y = lm2_add_f64(center.y, lm2_mul_f64(lm2_sin_f64(angle), radius));
  }
}

LM2_API void lm2_polygon_make_regular_f32(lm2_v2_f32* out_vertices, size_t num_sides, lm2_v2_f32 center, float radius) {
  LM2_ASSERT(out_vertices != NULL);
  LM2_ASSERT(num_sides >= 3);
  LM2_ASSERT(radius >= 0.0f);

  float angle_step = lm2_div_f32(lm2_mul_f32(2.0f, LM2_PI_F32), (float)num_sides);

  for (size_t i = 0; i < num_sides; i++) {
    float angle = lm2_mul_f32((float)i, angle_step);
    out_vertices[i].x = lm2_add_f32(center.x, lm2_mul_f32(lm2_cos_f32(angle), radius));
    out_vertices[i].y = lm2_add_f32(center.y, lm2_mul_f32(lm2_sin_f32(angle), radius));
  }
}

LM2_API void lm2_polygon_make_rect_f64(lm2_v2_f64* out_vertices, lm2_v2_f64 min, lm2_v2_f64 max) {
  LM2_ASSERT(out_vertices != NULL);
  out_vertices[0].x = min.x;
  out_vertices[0].y = min.y;
  out_vertices[1].x = max.x;
  out_vertices[1].y = min.y;
  out_vertices[2].x = max.x;
  out_vertices[2].y = max.y;
  out_vertices[3].x = min.x;
  out_vertices[3].y = max.y;
}

LM2_API void lm2_polygon_make_rect_f32(lm2_v2_f32* out_vertices, lm2_v2_f32 min, lm2_v2_f32 max) {
  LM2_ASSERT(out_vertices != NULL);
  out_vertices[0].x = min.x;
  out_vertices[0].y = min.y;
  out_vertices[1].x = max.x;
  out_vertices[1].y = min.y;
  out_vertices[2].x = max.x;
  out_vertices[2].y = max.y;
  out_vertices[3].x = min.x;
  out_vertices[3].y = max.y;
}

LM2_API void lm2_polygon_make_triangle_f64(lm2_v2_f64* out_vertices, lm2_v2_f64 position, lm2_v2_f64 tip, double base_width) {
  LM2_ASSERT(out_vertices != NULL);
  LM2_ASSERT(base_width >= 0.0);

  // Calculate direction vector from position to tip
  lm2_v2_f64 dir = lm2_v2_sub_f64(tip, position);
  double len = lm2_v2_length_f64(dir);

  if (len > 0.0) {
    dir = lm2_v2_mul_s_f64(dir, lm2_div_f64(1.0, len));
  } else {
    dir.x = 0.0;
    dir.y = 1.0;
  }

  // Perpendicular vector for base
  lm2_v2_f64 perp = {lm2_mul_f64(dir.y, -1.0), dir.x};
  double half_width = lm2_mul_f64(base_width, 0.5);

  // Calculate base vertices
  out_vertices[0] = tip;
  out_vertices[1] = lm2_v2_add_f64(position, lm2_v2_mul_s_f64(perp, half_width));
  out_vertices[2] = lm2_v2_sub_f64(position, lm2_v2_mul_s_f64(perp, half_width));
}

LM2_API void lm2_polygon_make_triangle_f32(lm2_v2_f32* out_vertices, lm2_v2_f32 position, lm2_v2_f32 tip, float base_width) {
  LM2_ASSERT(out_vertices != NULL);
  LM2_ASSERT(base_width >= 0.0f);

  // Calculate direction vector from position to tip
  lm2_v2_f32 dir = lm2_v2_sub_f32(tip, position);
  float len = lm2_v2_length_f32(dir);

  if (len > 0.0f) {
    dir = lm2_v2_mul_s_f32(dir, lm2_div_f32(1.0f, len));
  } else {
    dir.x = 0.0f;
    dir.y = 1.0f;
  }

  // Perpendicular vector for base
  lm2_v2_f32 perp = {lm2_mul_f32(dir.y, -1.0f), dir.x};
  float half_width = lm2_mul_f32(base_width, 0.5f);

  // Calculate base vertices
  out_vertices[0] = tip;
  out_vertices[1] = lm2_v2_add_f32(position, lm2_v2_mul_s_f32(perp, half_width));
  out_vertices[2] = lm2_v2_sub_f32(position, lm2_v2_mul_s_f32(perp, half_width));
}

LM2_API void lm2_polygon_from_triangle_f64(lm2_v2_f64* out_vertices, const lm2_triangle2_f64 triangle) {
  LM2_ASSERT(out_vertices != NULL);
  out_vertices[0] = triangle[0];
  out_vertices[1] = triangle[1];
  out_vertices[2] = triangle[2];
}

LM2_API void lm2_polygon_from_triangle_f32(lm2_v2_f32* out_vertices, const lm2_triangle2_f32 triangle) {
  LM2_ASSERT(out_vertices != NULL);
  out_vertices[0] = triangle[0];
  out_vertices[1] = triangle[1];
  out_vertices[2] = triangle[2];
}

// =============================================================================
// Polygon Properties
// =============================================================================

LM2_API bool lm2_polygon_validate_f64(lm2_polygon_f64 polygon) {
  return polygon.vertices != NULL && polygon.vertex_count >= 3;
}

LM2_API bool lm2_polygon_validate_f32(lm2_polygon_f32 polygon) {
  return polygon.vertices != NULL && polygon.vertex_count >= 3;
}

LM2_API double lm2_polygon_signed_area_f64(lm2_polygon_f64 polygon) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);

  // Shoelace formula (returns signed area)
  double area = 0.0;
  for (size_t i = 0; i < polygon.vertex_count; i++) {
    size_t j = (i + 1) % polygon.vertex_count;
    double cross = lm2_sub_f64(
        lm2_mul_f64(polygon.vertices[i].x, polygon.vertices[j].y),
        lm2_mul_f64(polygon.vertices[j].x, polygon.vertices[i].y));
    area = lm2_add_f64(area, cross);
  }
  return lm2_mul_f64(area, 0.5);
}

LM2_API float lm2_polygon_signed_area_f32(lm2_polygon_f32 polygon) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);

  // Shoelace formula (returns signed area)
  float area = 0.0f;
  for (size_t i = 0; i < polygon.vertex_count; i++) {
    size_t j = (i + 1) % polygon.vertex_count;
    float cross = lm2_sub_f32(
        lm2_mul_f32(polygon.vertices[i].x, polygon.vertices[j].y),
        lm2_mul_f32(polygon.vertices[j].x, polygon.vertices[i].y));
    area = lm2_add_f32(area, cross);
  }
  return lm2_mul_f32(area, 0.5f);
}

LM2_API double lm2_polygon_area_f64(lm2_polygon_f64 polygon) {
  return lm2_abs_f64(lm2_polygon_signed_area_f64(polygon));
}

LM2_API float lm2_polygon_area_f32(lm2_polygon_f32 polygon) {
  return lm2_abs_f32(lm2_polygon_signed_area_f32(polygon));
}

LM2_API lm2_winding_order lm2_polygon_winding_order_f64(lm2_polygon_f64 polygon) {
  double area = lm2_polygon_signed_area_f64(polygon);
  if (area > 0.0) {
    return LM2_WINDING_COUNTERCLOCKWISE;
  } else if (area < 0.0) {
    return LM2_WINDING_CLOCKWISE;
  }
  return LM2_WINDING_NONE;
}

LM2_API lm2_winding_order lm2_polygon_winding_order_f32(lm2_polygon_f32 polygon) {
  float area = lm2_polygon_signed_area_f32(polygon);
  if (area > 0.0f) {
    return LM2_WINDING_COUNTERCLOCKWISE;
  } else if (area < 0.0f) {
    return LM2_WINDING_CLOCKWISE;
  }
  return LM2_WINDING_NONE;
}

LM2_API double lm2_polygon_perimeter_f64(lm2_polygon_f64 polygon) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);

  double perimeter = 0.0;
  for (size_t i = 0; i < polygon.vertex_count; i++) {
    size_t j = (i + 1) % polygon.vertex_count;
    double dist = lm2_v2_distance_f64(polygon.vertices[i], polygon.vertices[j]);
    perimeter = lm2_add_f64(perimeter, dist);
  }
  return perimeter;
}

LM2_API float lm2_polygon_perimeter_f32(lm2_polygon_f32 polygon) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);

  float perimeter = 0.0f;
  for (size_t i = 0; i < polygon.vertex_count; i++) {
    size_t j = (i + 1) % polygon.vertex_count;
    float dist = lm2_v2_distance_f32(polygon.vertices[i], polygon.vertices[j]);
    perimeter = lm2_add_f32(perimeter, dist);
  }
  return perimeter;
}

LM2_API lm2_v2_f64 lm2_polygon_centroid_f64(lm2_polygon_f64 polygon) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);

  lm2_v2_f64 centroid = {0.0, 0.0};
  double signed_area = 0.0;

  for (size_t i = 0; i < polygon.vertex_count; i++) {
    size_t j = (i + 1) % polygon.vertex_count;
    double cross = lm2_sub_f64(
        lm2_mul_f64(polygon.vertices[i].x, polygon.vertices[j].y),
        lm2_mul_f64(polygon.vertices[j].x, polygon.vertices[i].y));
    signed_area = lm2_add_f64(signed_area, cross);
    centroid.x = lm2_add_f64(centroid.x, lm2_mul_f64(lm2_add_f64(polygon.vertices[i].x, polygon.vertices[j].x), cross));
    centroid.y = lm2_add_f64(centroid.y, lm2_mul_f64(lm2_add_f64(polygon.vertices[i].y, polygon.vertices[j].y), cross));
  }

  signed_area = lm2_mul_f64(signed_area, 0.5);
  double factor = lm2_div_f64(1.0, lm2_mul_f64(6.0, signed_area));
  centroid.x = lm2_mul_f64(centroid.x, factor);
  centroid.y = lm2_mul_f64(centroid.y, factor);

  return centroid;
}

LM2_API lm2_v2_f32 lm2_polygon_centroid_f32(lm2_polygon_f32 polygon) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);

  lm2_v2_f32 centroid = {0.0f, 0.0f};
  float signed_area = 0.0f;

  for (size_t i = 0; i < polygon.vertex_count; i++) {
    size_t j = (i + 1) % polygon.vertex_count;
    float cross = lm2_sub_f32(
        lm2_mul_f32(polygon.vertices[i].x, polygon.vertices[j].y),
        lm2_mul_f32(polygon.vertices[j].x, polygon.vertices[i].y));
    signed_area = lm2_add_f32(signed_area, cross);
    centroid.x = lm2_add_f32(centroid.x, lm2_mul_f32(lm2_add_f32(polygon.vertices[i].x, polygon.vertices[j].x), cross));
    centroid.y = lm2_add_f32(centroid.y, lm2_mul_f32(lm2_add_f32(polygon.vertices[i].y, polygon.vertices[j].y), cross));
  }

  signed_area = lm2_mul_f32(signed_area, 0.5f);
  float factor = lm2_div_f32(1.0f, lm2_mul_f32(6.0f, signed_area));
  centroid.x = lm2_mul_f32(centroid.x, factor);
  centroid.y = lm2_mul_f32(centroid.y, factor);

  return centroid;
}

LM2_API bool lm2_polygon_is_ccw_f64(lm2_polygon_f64 polygon) {
  double area = lm2_polygon_area_f64(polygon);
  return area > 0.0;
}

LM2_API bool lm2_polygon_is_ccw_f32(lm2_polygon_f32 polygon) {
  float area = lm2_polygon_signed_area_f32(polygon);
  return area > 0.0f;
}

LM2_API lm2_v2_f64 lm2_polygon_center_f64(lm2_polygon_f64 polygon) {
  return lm2_polygon_centroid_f64(polygon);
}

LM2_API lm2_v2_f32 lm2_polygon_center_f32(lm2_polygon_f32 polygon) {
  return lm2_polygon_centroid_f32(polygon);
}

LM2_API lm2_r2_f64 lm2_polygon_bounds_f64(lm2_polygon_f64 polygon) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);

  lm2_r2_f64 bounds;
  bounds.min = polygon.vertices[0];
  bounds.max = polygon.vertices[0];

  for (size_t i = 1; i < polygon.vertex_count; i++) {
    bounds.min.x = lm2_min_f64(bounds.min.x, polygon.vertices[i].x);
    bounds.min.y = lm2_min_f64(bounds.min.y, polygon.vertices[i].y);
    bounds.max.x = lm2_max_f64(bounds.max.x, polygon.vertices[i].x);
    bounds.max.y = lm2_max_f64(bounds.max.y, polygon.vertices[i].y);
  }

  return bounds;
}

LM2_API lm2_r2_f32 lm2_polygon_bounds_f32(lm2_polygon_f32 polygon) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);

  lm2_r2_f32 bounds;
  bounds.min = polygon.vertices[0];
  bounds.max = polygon.vertices[0];

  for (size_t i = 1; i < polygon.vertex_count; i++) {
    bounds.min.x = lm2_min_f32(bounds.min.x, polygon.vertices[i].x);
    bounds.min.y = lm2_min_f32(bounds.min.y, polygon.vertices[i].y);
    bounds.max.x = lm2_max_f32(bounds.max.x, polygon.vertices[i].x);
    bounds.max.y = lm2_max_f32(bounds.max.y, polygon.vertices[i].y);
  }

  return bounds;
}

// =============================================================================
// Polygon Tests
// =============================================================================

LM2_API bool lm2_polygon_contains_point_f64(lm2_polygon_f64 polygon, lm2_v2_f64 point) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);

  // Ray casting algorithm
  bool inside = false;
  for (size_t i = 0, j = polygon.vertex_count - 1; i < polygon.vertex_count; j = i++) {
    lm2_v2_f64 vi = polygon.vertices[i];
    lm2_v2_f64 vj = polygon.vertices[j];

    if (((vi.y > point.y) != (vj.y > point.y)) &&
        (point.x < lm2_add_f64(lm2_mul_f64(lm2_div_f64(lm2_sub_f64(vj.x, vi.x), lm2_sub_f64(vj.y, vi.y)),
                                           lm2_sub_f64(point.y, vi.y)),
                               vi.x))) {
      inside = !inside;
    }
  }
  return inside;
}

LM2_API bool lm2_polygon_contains_point_f32(lm2_polygon_f32 polygon, lm2_v2_f32 point) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);

  // Ray casting algorithm
  bool inside = false;
  for (size_t i = 0, j = polygon.vertex_count - 1; i < polygon.vertex_count; j = i++) {
    lm2_v2_f32 vi = polygon.vertices[i];
    lm2_v2_f32 vj = polygon.vertices[j];

    if (((vi.y > point.y) != (vj.y > point.y)) &&
        (point.x < lm2_add_f32(lm2_mul_f32(lm2_div_f32(lm2_sub_f32(vj.x, vi.x), lm2_sub_f32(vj.y, vi.y)),
                                           lm2_sub_f32(point.y, vi.y)),
                               vi.x))) {
      inside = !inside;
    }
  }
  return inside;
}

// Helper function to compute cross product of vectors (p1->p2) and (p1->p3)
static double cross_product_f64(lm2_v2_f64 p1, lm2_v2_f64 p2, lm2_v2_f64 p3) {
  double dx1 = lm2_sub_f64(p2.x, p1.x);
  double dy1 = lm2_sub_f64(p2.y, p1.y);
  double dx2 = lm2_sub_f64(p3.x, p1.x);
  double dy2 = lm2_sub_f64(p3.y, p1.y);
  return lm2_sub_f64(lm2_mul_f64(dx1, dy2), lm2_mul_f64(dy1, dx2));
}

static float cross_product_f32(lm2_v2_f32 p1, lm2_v2_f32 p2, lm2_v2_f32 p3) {
  float dx1 = lm2_sub_f32(p2.x, p1.x);
  float dy1 = lm2_sub_f32(p2.y, p1.y);
  float dx2 = lm2_sub_f32(p3.x, p1.x);
  float dy2 = lm2_sub_f32(p3.y, p1.y);
  return lm2_sub_f32(lm2_mul_f32(dx1, dy2), lm2_mul_f32(dy1, dx2));
}

LM2_API bool lm2_polygon_is_convex_f64(lm2_polygon_f64 polygon) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);

  if (polygon.vertex_count < 3) return false;

  bool has_positive = false;
  bool has_negative = false;

  for (size_t i = 0; i < polygon.vertex_count; i++) {
    size_t j = (i + 1) % polygon.vertex_count;
    size_t k = (i + 2) % polygon.vertex_count;
    double cross = cross_product_f64(polygon.vertices[i], polygon.vertices[j], polygon.vertices[k]);

    if (cross > 0.0) has_positive = true;
    if (cross < 0.0) has_negative = true;

    if (has_positive && has_negative) return false;
  }

  return true;
}

LM2_API bool lm2_polygon_is_convex_f32(lm2_polygon_f32 polygon) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);

  if (polygon.vertex_count < 3) return false;

  bool has_positive = false;
  bool has_negative = false;

  for (size_t i = 0; i < polygon.vertex_count; i++) {
    size_t j = (i + 1) % polygon.vertex_count;
    size_t k = (i + 2) % polygon.vertex_count;
    float cross = cross_product_f32(polygon.vertices[i], polygon.vertices[j], polygon.vertices[k]);

    if (cross > 0.0f) has_positive = true;
    if (cross < 0.0f) has_negative = true;

    if (has_positive && has_negative) return false;
  }

  return true;
}

// Helper function to check if two line segments intersect
static bool segments_intersect_f64(lm2_v2_f64 a1, lm2_v2_f64 a2, lm2_v2_f64 b1, lm2_v2_f64 b2) {
  double d1 = cross_product_f64(b1, b2, a1);
  double d2 = cross_product_f64(b1, b2, a2);
  double d3 = cross_product_f64(a1, a2, b1);
  double d4 = cross_product_f64(a1, a2, b2);

  if (((d1 > 0.0 && d2 < 0.0) || (d1 < 0.0 && d2 > 0.0)) &&
      ((d3 > 0.0 && d4 < 0.0) || (d3 < 0.0 && d4 > 0.0))) {
    return true;
  }

  return false;
}

static bool segments_intersect_f32(lm2_v2_f32 a1, lm2_v2_f32 a2, lm2_v2_f32 b1, lm2_v2_f32 b2) {
  float d1 = lm2_cross_product_2d_f32(b1, b2, a1);
  float d2 = lm2_cross_product_2d_f32(b1, b2, a2);
  float d3 = lm2_cross_product_2d_f32(a1, a2, b1);
  float d4 = lm2_cross_product_2d_f32(a1, a2, b2);

  if (((d1 > 0.0f && d2 < 0.0f) || (d1 < 0.0f && d2 > 0.0f)) &&
      ((d3 > 0.0f && d4 < 0.0f) || (d3 < 0.0f && d4 > 0.0f))) {
    return true;
  }

  return false;
}

LM2_API bool lm2_polygon_is_simple_f64(lm2_polygon_f64 polygon) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);

  // Check if any non-adjacent edges intersect
  for (size_t i = 0; i < polygon.vertex_count; i++) {
    size_t j = (i + 1) % polygon.vertex_count;
    lm2_v2_f64 a1 = polygon.vertices[i];
    lm2_v2_f64 a2 = polygon.vertices[j];

    for (size_t k = i + 2; k < polygon.vertex_count; k++) {
      // Skip adjacent edges
      if (k == j || (i == 0 && k == polygon.vertex_count - 1)) continue;

      size_t l = (k + 1) % polygon.vertex_count;
      lm2_v2_f64 b1 = polygon.vertices[k];
      lm2_v2_f64 b2 = polygon.vertices[l];

      if (segments_intersect_f64(a1, a2, b1, b2)) {
        return false;
      }
    }
  }

  return true;
}

LM2_API bool lm2_polygon_is_simple_f32(lm2_polygon_f32 polygon) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);

  // Check if any non-adjacent edges intersect
  for (size_t i = 0; i < polygon.vertex_count; i++) {
    size_t j = (i + 1) % polygon.vertex_count;
    lm2_v2_f32 a1 = polygon.vertices[i];
    lm2_v2_f32 a2 = polygon.vertices[j];

    for (size_t k = i + 2; k < polygon.vertex_count; k++) {
      // Skip adjacent edges
      if (k == j || (i == 0 && k == polygon.vertex_count - 1)) continue;

      size_t l = (k + 1) % polygon.vertex_count;
      lm2_v2_f32 b1 = polygon.vertices[k];
      lm2_v2_f32 b2 = polygon.vertices[l];

      if (segments_intersect_f32(a1, a2, b1, b2)) {
        return false;
      }
    }
  }

  return true;
}

LM2_API bool lm2_polygon_is_triangle_f64(lm2_polygon_f64 polygon) {
  return polygon.vertex_count == 3;
}

LM2_API bool lm2_polygon_is_triangle_f32(lm2_polygon_f32 polygon) {
  return polygon.vertex_count == 3;
}

LM2_API bool lm2_polygon_is_quad_f64(lm2_polygon_f64 polygon) {
  return polygon.vertex_count == 4;
}

LM2_API bool lm2_polygon_is_quad_f32(lm2_polygon_f32 polygon) {
  return polygon.vertex_count == 4;
}

// =============================================================================
// Polygon Transformations
// =============================================================================

LM2_API void lm2_polygon_translate_f64(lm2_polygon_f64 polygon, lm2_v2_f64 offset) {
  LM2_ASSERT(polygon.vertices != NULL);
  for (size_t i = 0; i < polygon.vertex_count; i++) {
    polygon.vertices[i] = lm2_v2_add_f64(polygon.vertices[i], offset);
  }
}

LM2_API void lm2_polygon_translate_f32(lm2_polygon_f32 polygon, lm2_v2_f32 offset) {
  LM2_ASSERT(polygon.vertices != NULL);
  for (size_t i = 0; i < polygon.vertex_count; i++) {
    polygon.vertices[i] = lm2_v2_add_f32(polygon.vertices[i], offset);
  }
}

LM2_API void lm2_polygon_scale_f64(lm2_polygon_f64 polygon, lm2_v2_f64 center, double scale) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(scale >= 0.0);
  for (size_t i = 0; i < polygon.vertex_count; i++) {
    lm2_v2_f64 offset = lm2_v2_sub_f64(polygon.vertices[i], center);
    offset = lm2_v2_mul_s_f64(offset, scale);
    polygon.vertices[i] = lm2_v2_add_f64(center, offset);
  }
}

LM2_API void lm2_polygon_scale_f32(lm2_polygon_f32 polygon, lm2_v2_f32 center, float scale) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(scale >= 0.0f);
  for (size_t i = 0; i < polygon.vertex_count; i++) {
    lm2_v2_f32 offset = lm2_v2_sub_f32(polygon.vertices[i], center);
    offset = lm2_v2_mul_s_f32(offset, scale);
    polygon.vertices[i] = lm2_v2_add_f32(center, offset);
  }
}

LM2_API void lm2_polygon_rotate_f64(lm2_polygon_f64 polygon, lm2_v2_f64 center, double angle_radians) {
  LM2_ASSERT(polygon.vertices != NULL);
  double cos_a = lm2_cos_f64(angle_radians);
  double sin_a = lm2_sin_f64(angle_radians);

  for (size_t i = 0; i < polygon.vertex_count; i++) {
    lm2_v2_f64 offset = lm2_v2_sub_f64(polygon.vertices[i], center);
    double new_x = lm2_sub_f64(lm2_mul_f64(offset.x, cos_a), lm2_mul_f64(offset.y, sin_a));
    double new_y = lm2_add_f64(lm2_mul_f64(offset.x, sin_a), lm2_mul_f64(offset.y, cos_a));
    polygon.vertices[i].x = lm2_add_f64(center.x, new_x);
    polygon.vertices[i].y = lm2_add_f64(center.y, new_y);
  }
}

LM2_API void lm2_polygon_rotate_f32(lm2_polygon_f32 polygon, lm2_v2_f32 center, float angle_radians) {
  LM2_ASSERT(polygon.vertices != NULL);
  float cos_a = lm2_cos_f32(angle_radians);
  float sin_a = lm2_sin_f32(angle_radians);

  for (size_t i = 0; i < polygon.vertex_count; i++) {
    lm2_v2_f32 offset = lm2_v2_sub_f32(polygon.vertices[i], center);
    float new_x = lm2_sub_f32(lm2_mul_f32(offset.x, cos_a), lm2_mul_f32(offset.y, sin_a));
    float new_y = lm2_add_f32(lm2_mul_f32(offset.x, sin_a), lm2_mul_f32(offset.y, cos_a));
    polygon.vertices[i].x = lm2_add_f32(center.x, new_x);
    polygon.vertices[i].y = lm2_add_f32(center.y, new_y);
  }
}

LM2_API void lm2_polygon_reverse_winding_f64(lm2_polygon_f64 polygon) {
  LM2_ASSERT(polygon.vertices != NULL);
  size_t left = 0;
  size_t right = polygon.vertex_count - 1;

  while (left < right) {
    // Swap vertices
    lm2_v2_f64 temp = polygon.vertices[left];
    polygon.vertices[left] = polygon.vertices[right];
    polygon.vertices[right] = temp;
    left++;
    right--;
  }
}

LM2_API void lm2_polygon_reverse_winding_f32(lm2_polygon_f32 polygon) {
  LM2_ASSERT(polygon.vertices != NULL);
  size_t left = 0;
  size_t right = polygon.vertex_count - 1;

  while (left < right) {
    // Swap vertices
    lm2_v2_f32 temp = polygon.vertices[left];
    polygon.vertices[left] = polygon.vertices[right];
    polygon.vertices[right] = temp;
    left++;
    right--;
  }
}

LM2_API void lm2_polygon_insert_vertex_f64(lm2_v2_f64* vertices, size_t* vertex_count, size_t index, lm2_v2_f64 vertex) {
  LM2_ASSERT(vertices != NULL);
  LM2_ASSERT(vertex_count != NULL);
  LM2_ASSERT(*vertex_count >= 3);
  LM2_ASSERT(index <= *vertex_count);

  // Shift vertices to make room
  for (size_t i = *vertex_count; i > index; i--) {
    vertices[i] = vertices[i - 1];
  }

  vertices[index] = vertex;
  (*vertex_count)++;
}

LM2_API void lm2_polygon_insert_vertex_f32(lm2_v2_f32* vertices, size_t* vertex_count, size_t index, lm2_v2_f32 vertex) {
  LM2_ASSERT(vertices != NULL);
  LM2_ASSERT(vertex_count != NULL);
  LM2_ASSERT(*vertex_count >= 3);
  LM2_ASSERT(index <= *vertex_count);

  // Shift vertices to make room
  for (size_t i = *vertex_count; i > index; i--) {
    vertices[i] = vertices[i - 1];
  }

  vertices[index] = vertex;
  (*vertex_count)++;
}

LM2_API void lm2_polygon_remove_vertex_f64(lm2_v2_f64* vertices, size_t* vertex_count, size_t index) {
  LM2_ASSERT(vertices != NULL);
  LM2_ASSERT(vertex_count != NULL);
  LM2_ASSERT(*vertex_count > 3);  // Must have at least 3 vertices after removal
  LM2_ASSERT(index < *vertex_count);

  // Shift vertices to fill the gap
  for (size_t i = index; i < *vertex_count - 1; i++) {
    vertices[i] = vertices[i + 1];
  }

  (*vertex_count)--;
}

LM2_API void lm2_polygon_remove_vertex_f32(lm2_v2_f32* vertices, size_t* vertex_count, size_t index) {
  LM2_ASSERT(vertices != NULL);
  LM2_ASSERT(vertex_count != NULL);
  LM2_ASSERT(*vertex_count > 3);  // Must have at least 3 vertices after removal
  LM2_ASSERT(index < *vertex_count);

  // Shift vertices to fill the gap
  for (size_t i = index; i < *vertex_count - 1; i++) {
    vertices[i] = vertices[i + 1];
  }

  (*vertex_count)--;
}

LM2_API void lm2_polygon_place_at_center_f64(lm2_polygon_f64 polygon, lm2_v2_f64 position) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);

  lm2_v2_f64 current_center = lm2_polygon_centroid_f64(polygon);
  lm2_v2_f64 offset = lm2_v2_sub_f64(position, current_center);
  lm2_polygon_translate_f64(polygon, offset);
}

LM2_API void lm2_polygon_place_at_center_f32(lm2_polygon_f32 polygon, lm2_v2_f32 position) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);

  lm2_v2_f32 current_center = lm2_polygon_centroid_f32(polygon);
  lm2_v2_f32 offset = lm2_v2_sub_f32(position, current_center);
  lm2_polygon_translate_f32(polygon, offset);
}

// =============================================================================
// Polygon Triangulation
// =============================================================================

LM2_API size_t lm2_polygon_max_triangle_count(size_t vertex_count) {
  LM2_ASSERT(vertex_count >= 3);
  return vertex_count - 2;
}

// Helper function to check if a triangle at indices (i, j, k) is an ear
static bool is_ear_f64(const lm2_v2_f64* vertices, const size_t* indices, size_t n, size_t i, size_t j, size_t k) {
  lm2_v2_f64 a = vertices[indices[i]];
  lm2_v2_f64 b = vertices[indices[j]];
  lm2_v2_f64 c = vertices[indices[k]];
  lm2_triangle2_f64 tri = {a, b, c};

  // Check if triangle is convex
  if (lm2_cross_product_2d_f64(a, b, c) < 0.0) {
    return false;
  }

  // Check if any other vertex is inside this triangle
  for (size_t m = 0; m < n; m++) {
    if (m == i || m == j || m == k) continue;
    if (lm2_triangle2_contains_point_f64(tri, vertices[indices[m]])) {
      return false;
    }
  }

  return true;
}

static bool is_ear_f32(const lm2_v2_f32* vertices, const size_t* indices, size_t n, size_t i, size_t j, size_t k) {
  lm2_v2_f32 a = vertices[indices[i]];
  lm2_v2_f32 b = vertices[indices[j]];
  lm2_v2_f32 c = vertices[indices[k]];
  lm2_triangle2_f32 tri = {a, b, c};

  // Check if triangle is convex
  if (lm2_cross_product_2d_f32(a, b, c) < 0.0f) {
    return false;
  }

  // Check if any other vertex is inside this triangle
  for (size_t m = 0; m < n; m++) {
    if (m == i || m == j || m == k) continue;
    if (lm2_triangle2_contains_point_f32(tri, vertices[indices[m]])) {
      return false;
    }
  }

  return true;
}

LM2_API size_t lm2_polygon_triangulate_ear_clipping_f64(lm2_polygon_f64 polygon, size_t* out_indices) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);
  LM2_ASSERT(out_indices != NULL);

  size_t n = polygon.vertex_count;
  size_t triangle_count = 0;

  // Create working array of vertex indices (heap allocation for MSVC compatibility)
  size_t* indices = (size_t*)malloc(n * sizeof(size_t));
  if (indices == NULL) {
    return 0;
  }
  for (size_t i = 0; i < n; i++) {
    indices[i] = i;
  }

  // Triangulate
  while (n > 2) {
    bool ear_found = false;

    for (size_t i = 0; i < n; i++) {
      size_t prev = (i == 0) ? (n - 1) : (i - 1);
      size_t next = (i + 1) % n;

      if (is_ear_f64(polygon.vertices, indices, n, prev, i, next)) {
        // Output triangle
        out_indices[triangle_count * 3 + 0] = indices[prev];
        out_indices[triangle_count * 3 + 1] = indices[i];
        out_indices[triangle_count * 3 + 2] = indices[next];
        triangle_count++;

        // Remove vertex i from the list
        for (size_t j = i; j < n - 1; j++) {
          indices[j] = indices[j + 1];
        }
        n--;
        ear_found = true;
        break;
      }
    }

    // If no ear found, break to avoid infinite loop
    if (!ear_found) {
      break;
    }
  }

  return triangle_count;
}

LM2_API size_t lm2_polygon_triangulate_ear_clipping_f32(lm2_polygon_f32 polygon, size_t* out_indices) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);
  LM2_ASSERT(out_indices != NULL);

  size_t n = polygon.vertex_count;
  size_t triangle_count = 0;

  // Create working array of vertex indices (heap allocation for MSVC compatibility)
  size_t* indices = (size_t*)malloc(n * sizeof(size_t));
  if (indices == NULL) {
    return 0;
  }
  for (size_t i = 0; i < n; i++) {
    indices[i] = i;
  }

  // Triangulate
  while (n > 2) {
    bool ear_found = false;

    for (size_t i = 0; i < n; i++) {
      size_t prev = (i == 0) ? (n - 1) : (i - 1);
      size_t next = (i + 1) % n;

      if (is_ear_f32(polygon.vertices, indices, n, prev, i, next)) {
        // Output triangle
        out_indices[triangle_count * 3 + 0] = indices[prev];
        out_indices[triangle_count * 3 + 1] = indices[i];
        out_indices[triangle_count * 3 + 2] = indices[next];
        triangle_count++;

        // Remove vertex i from the list
        for (size_t j = i; j < n - 1; j++) {
          indices[j] = indices[j + 1];
        }
        n--;
        ear_found = true;
        break;
      }
    }

    // If no ear found, break to avoid infinite loop
    if (!ear_found) {
      break;
    }
  }

  free(indices);
  return triangle_count;
}

// =============================================================================
// Polygon Splitting
// =============================================================================

LM2_API size_t lm2_polygon_split_by_max_vertices_f64(lm2_polygon_f64 polygon, lm2_polygon_f64* out_polygons, lm2_v2_f64* out_vertices_buffer, size_t max_vertices) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);
  LM2_ASSERT(out_polygons != NULL);
  LM2_ASSERT(out_vertices_buffer != NULL);
  LM2_ASSERT(max_vertices >= 3);

  // If polygon already fits within max_vertices, return it as-is
  if (polygon.vertex_count <= max_vertices) {
    out_polygons[0].vertices = out_vertices_buffer;
    out_polygons[0].vertex_count = polygon.vertex_count;
    for (size_t i = 0; i < polygon.vertex_count; i++) {
      out_vertices_buffer[i] = polygon.vertices[i];
    }
    return 1;
  }

  // Split polygon into chunks
  size_t num_splits = 0;
  size_t buffer_offset = 0;
  size_t current_start = 0;

  while (current_start < polygon.vertex_count) {
    size_t chunk_size = max_vertices;
    if (current_start + chunk_size > polygon.vertex_count) {
      chunk_size = polygon.vertex_count - current_start;
    }

    // Ensure we have at least 3 vertices
    if (chunk_size < 3) {
      chunk_size = 3;
    }

    out_polygons[num_splits].vertices = out_vertices_buffer + buffer_offset;
    out_polygons[num_splits].vertex_count = chunk_size;

    for (size_t i = 0; i < chunk_size; i++) {
      size_t src_index = (current_start + i) % polygon.vertex_count;
      out_vertices_buffer[buffer_offset + i] = polygon.vertices[src_index];
    }

    buffer_offset += chunk_size;
    current_start += (chunk_size - 1);  // Overlap by 1 vertex
    num_splits++;

    // Break if we've processed all vertices
    if (current_start >= polygon.vertex_count) {
      break;
    }
  }

  return num_splits;
}

LM2_API size_t lm2_polygon_split_by_max_vertices_f32(lm2_polygon_f32 polygon, lm2_polygon_f32* out_polygons, lm2_v2_f32* out_vertices_buffer, size_t max_vertices) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);
  LM2_ASSERT(out_polygons != NULL);
  LM2_ASSERT(out_vertices_buffer != NULL);
  LM2_ASSERT(max_vertices >= 3);

  // If polygon already fits within max_vertices, return it as-is
  if (polygon.vertex_count <= max_vertices) {
    out_polygons[0].vertices = out_vertices_buffer;
    out_polygons[0].vertex_count = polygon.vertex_count;
    for (size_t i = 0; i < polygon.vertex_count; i++) {
      out_vertices_buffer[i] = polygon.vertices[i];
    }
    return 1;
  }

  // Split polygon into chunks
  size_t num_splits = 0;
  size_t buffer_offset = 0;
  size_t current_start = 0;

  while (current_start < polygon.vertex_count) {
    size_t chunk_size = max_vertices;
    if (current_start + chunk_size > polygon.vertex_count) {
      chunk_size = polygon.vertex_count - current_start;
    }

    // Ensure we have at least 3 vertices
    if (chunk_size < 3) {
      chunk_size = 3;
    }

    out_polygons[num_splits].vertices = out_vertices_buffer + buffer_offset;
    out_polygons[num_splits].vertex_count = chunk_size;

    for (size_t i = 0; i < chunk_size; i++) {
      size_t src_index = (current_start + i) % polygon.vertex_count;
      out_vertices_buffer[buffer_offset + i] = polygon.vertices[src_index];
    }

    buffer_offset += chunk_size;
    current_start += (chunk_size - 1);  // Overlap by 1 vertex
    num_splits++;

    // Break if we've processed all vertices
    if (current_start >= polygon.vertex_count) {
      break;
    }
  }

  return num_splits;
}
