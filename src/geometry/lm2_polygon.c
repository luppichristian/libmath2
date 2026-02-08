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

#include <lm2/geometry/lm2_polygon.h>
#include <lm2/lm2_constants.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/scalar/lm2_trigonometry.h>
#include <lm2/vectors/lm2_vector_specifics.h>

// =============================================================================
// Construction Helpers
// =============================================================================

LM2_API lm2_polygon_f64 lm2_polygon_make_f64(lm2_v2f64* vertices, size_t vertex_count) {
  LM2_ASSERT(vertices != NULL);
  LM2_ASSERT(vertex_count >= 3);
  lm2_polygon_f64 polygon;
  polygon.vertices = vertices;
  polygon.vertex_count = vertex_count;
  return polygon;
}

LM2_API lm2_polygon_f32 lm2_polygon_make_f32(lm2_v2f32* vertices, size_t vertex_count) {
  LM2_ASSERT(vertices != NULL);
  LM2_ASSERT(vertex_count >= 3);
  lm2_polygon_f32 polygon;
  polygon.vertices = vertices;
  polygon.vertex_count = vertex_count;
  return polygon;
}

LM2_API void lm2_polygon_make_regular_f64(lm2_v2f64* out_vertices, size_t num_sides, lm2_v2f64 center, double radius) {
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

LM2_API void lm2_polygon_make_regular_f32(lm2_v2f32* out_vertices, size_t num_sides, lm2_v2f32 center, float radius) {
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

LM2_API void lm2_polygon_make_rect_f64(lm2_v2f64* out_vertices, lm2_v2f64 min, lm2_v2f64 max) {
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

LM2_API void lm2_polygon_make_rect_f32(lm2_v2f32* out_vertices, lm2_v2f32 min, lm2_v2f32 max) {
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

// =============================================================================
// Polygon Properties
// =============================================================================

LM2_API double lm2_polygon_area_f64(lm2_polygon_f64 polygon) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);

  // Shoelace formula
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

LM2_API float lm2_polygon_area_f32(lm2_polygon_f32 polygon) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);

  // Shoelace formula
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

LM2_API lm2_v2f64 lm2_polygon_centroid_f64(lm2_polygon_f64 polygon) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);

  lm2_v2f64 centroid = {0.0, 0.0};
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

LM2_API lm2_v2f32 lm2_polygon_centroid_f32(lm2_polygon_f32 polygon) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);

  lm2_v2f32 centroid = {0.0f, 0.0f};
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
  float area = lm2_polygon_area_f32(polygon);
  return area > 0.0f;
}

// =============================================================================
// Polygon Tests
// =============================================================================

LM2_API bool lm2_polygon_contains_point_f64(lm2_polygon_f64 polygon, lm2_v2f64 point) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);

  // Ray casting algorithm
  bool inside = false;
  for (size_t i = 0, j = polygon.vertex_count - 1; i < polygon.vertex_count; j = i++) {
    lm2_v2f64 vi = polygon.vertices[i];
    lm2_v2f64 vj = polygon.vertices[j];

    if (((vi.y > point.y) != (vj.y > point.y)) &&
        (point.x < lm2_add_f64(lm2_mul_f64(lm2_div_f64(lm2_sub_f64(vj.x, vi.x), lm2_sub_f64(vj.y, vi.y)),
                                           lm2_sub_f64(point.y, vi.y)),
                               vi.x))) {
      inside = !inside;
    }
  }
  return inside;
}

LM2_API bool lm2_polygon_contains_point_f32(lm2_polygon_f32 polygon, lm2_v2f32 point) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(polygon.vertex_count >= 3);

  // Ray casting algorithm
  bool inside = false;
  for (size_t i = 0, j = polygon.vertex_count - 1; i < polygon.vertex_count; j = i++) {
    lm2_v2f32 vi = polygon.vertices[i];
    lm2_v2f32 vj = polygon.vertices[j];

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
static double cross_product_f64(lm2_v2f64 p1, lm2_v2f64 p2, lm2_v2f64 p3) {
  double dx1 = lm2_sub_f64(p2.x, p1.x);
  double dy1 = lm2_sub_f64(p2.y, p1.y);
  double dx2 = lm2_sub_f64(p3.x, p1.x);
  double dy2 = lm2_sub_f64(p3.y, p1.y);
  return lm2_sub_f64(lm2_mul_f64(dx1, dy2), lm2_mul_f64(dy1, dx2));
}

static float cross_product_f32(lm2_v2f32 p1, lm2_v2f32 p2, lm2_v2f32 p3) {
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
static bool segments_intersect_f64(lm2_v2f64 a1, lm2_v2f64 a2, lm2_v2f64 b1, lm2_v2f64 b2) {
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

static bool segments_intersect_f32(lm2_v2f32 a1, lm2_v2f32 a2, lm2_v2f32 b1, lm2_v2f32 b2) {
  float d1 = cross_product_f32(b1, b2, a1);
  float d2 = cross_product_f32(b1, b2, a2);
  float d3 = cross_product_f32(a1, a2, b1);
  float d4 = cross_product_f32(a1, a2, b2);

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
    lm2_v2f64 a1 = polygon.vertices[i];
    lm2_v2f64 a2 = polygon.vertices[j];

    for (size_t k = i + 2; k < polygon.vertex_count; k++) {
      // Skip adjacent edges
      if (k == j || (i == 0 && k == polygon.vertex_count - 1)) continue;

      size_t l = (k + 1) % polygon.vertex_count;
      lm2_v2f64 b1 = polygon.vertices[k];
      lm2_v2f64 b2 = polygon.vertices[l];

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
    lm2_v2f32 a1 = polygon.vertices[i];
    lm2_v2f32 a2 = polygon.vertices[j];

    for (size_t k = i + 2; k < polygon.vertex_count; k++) {
      // Skip adjacent edges
      if (k == j || (i == 0 && k == polygon.vertex_count - 1)) continue;

      size_t l = (k + 1) % polygon.vertex_count;
      lm2_v2f32 b1 = polygon.vertices[k];
      lm2_v2f32 b2 = polygon.vertices[l];

      if (segments_intersect_f32(a1, a2, b1, b2)) {
        return false;
      }
    }
  }

  return true;
}

// =============================================================================
// Polygon Transformations
// =============================================================================

LM2_API void lm2_polygon_translate_f64(lm2_polygon_f64 polygon, lm2_v2f64 offset) {
  LM2_ASSERT(polygon.vertices != NULL);
  for (size_t i = 0; i < polygon.vertex_count; i++) {
    polygon.vertices[i] = lm2_v2_add_f64(polygon.vertices[i], offset);
  }
}

LM2_API void lm2_polygon_translate_f32(lm2_polygon_f32 polygon, lm2_v2f32 offset) {
  LM2_ASSERT(polygon.vertices != NULL);
  for (size_t i = 0; i < polygon.vertex_count; i++) {
    polygon.vertices[i] = lm2_v2_add_f32(polygon.vertices[i], offset);
  }
}

LM2_API void lm2_polygon_scale_f64(lm2_polygon_f64 polygon, lm2_v2f64 center, double scale) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(scale >= 0.0);
  for (size_t i = 0; i < polygon.vertex_count; i++) {
    lm2_v2f64 offset = lm2_v2_sub_f64(polygon.vertices[i], center);
    offset = lm2_v2_scale_f64(offset, scale);
    polygon.vertices[i] = lm2_v2_add_f64(center, offset);
  }
}

LM2_API void lm2_polygon_scale_f32(lm2_polygon_f32 polygon, lm2_v2f32 center, float scale) {
  LM2_ASSERT(polygon.vertices != NULL);
  LM2_ASSERT(scale >= 0.0f);
  for (size_t i = 0; i < polygon.vertex_count; i++) {
    lm2_v2f32 offset = lm2_v2_sub_f32(polygon.vertices[i], center);
    offset = lm2_v2_scale_f32(offset, scale);
    polygon.vertices[i] = lm2_v2_add_f32(center, offset);
  }
}

LM2_API void lm2_polygon_rotate_f64(lm2_polygon_f64 polygon, lm2_v2f64 center, double angle_radians) {
  LM2_ASSERT(polygon.vertices != NULL);
  double cos_a = lm2_cos_f64(angle_radians);
  double sin_a = lm2_sin_f64(angle_radians);

  for (size_t i = 0; i < polygon.vertex_count; i++) {
    lm2_v2f64 offset = lm2_v2_sub_f64(polygon.vertices[i], center);
    double new_x = lm2_sub_f64(lm2_mul_f64(offset.x, cos_a), lm2_mul_f64(offset.y, sin_a));
    double new_y = lm2_add_f64(lm2_mul_f64(offset.x, sin_a), lm2_mul_f64(offset.y, cos_a));
    polygon.vertices[i].x = lm2_add_f64(center.x, new_x);
    polygon.vertices[i].y = lm2_add_f64(center.y, new_y);
  }
}

LM2_API void lm2_polygon_rotate_f32(lm2_polygon_f32 polygon, lm2_v2f32 center, float angle_radians) {
  LM2_ASSERT(polygon.vertices != NULL);
  float cos_a = lm2_cos_f32(angle_radians);
  float sin_a = lm2_sin_f32(angle_radians);

  for (size_t i = 0; i < polygon.vertex_count; i++) {
    lm2_v2f32 offset = lm2_v2_sub_f32(polygon.vertices[i], center);
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
    lm2_v2f64 temp = polygon.vertices[left];
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
    lm2_v2f32 temp = polygon.vertices[left];
    polygon.vertices[left] = polygon.vertices[right];
    polygon.vertices[right] = temp;
    left++;
    right--;
  }
}
