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

#include <lm2/geometry2d/lm2_capsule2.h>
#include <lm2/geometry2d/lm2_edge2.h>
#include <lm2/lm2_constants.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/vectors/lm2_vector2.h>
#include <lm2/vectors/lm2_vector_specifics.h>

// =============================================================================
// Construction Helpers
// =============================================================================

LM2_API lm2_capsule2_f64 lm2_capsule2_make_f64(lm2_v2f64 start, lm2_v2f64 end, double radius) {
  LM2_ASSERT(radius >= 0.0);
  lm2_capsule2_f64 capsule;
  capsule.start = start;
  capsule.end = end;
  capsule.radius = radius;
  return capsule;
}

LM2_API lm2_capsule2_f32 lm2_capsule2_make_f32(lm2_v2f32 start, lm2_v2f32 end, float radius) {
  LM2_ASSERT(radius >= 0.0f);
  lm2_capsule2_f32 capsule;
  capsule.start = start;
  capsule.end = end;
  capsule.radius = radius;
  return capsule;
}

LM2_API lm2_capsule2_f64 lm2_capsule2_make_coords_f64(double x1, double y1, double x2, double y2, double radius) {
  LM2_ASSERT(radius >= 0.0);
  lm2_capsule2_f64 capsule;
  capsule.start.x = x1;
  capsule.start.y = y1;
  capsule.end.x = x2;
  capsule.end.y = y2;
  capsule.radius = radius;
  return capsule;
}

LM2_API lm2_capsule2_f32 lm2_capsule2_make_coords_f32(float x1, float y1, float x2, float y2, float radius) {
  LM2_ASSERT(radius >= 0.0f);
  lm2_capsule2_f32 capsule;
  capsule.start.x = x1;
  capsule.start.y = y1;
  capsule.end.x = x2;
  capsule.end.y = y2;
  capsule.radius = radius;
  return capsule;
}

LM2_API lm2_capsule2_f64 lm2_capsule2_from_center_f64(lm2_v2f64 center, lm2_v2f64 direction, double half_length, double radius) {
  LM2_ASSERT(radius >= 0.0);
  LM2_ASSERT(half_length >= 0.0);
  lm2_v2f64 normalized = lm2_normalize_v2f64(direction);
  lm2_v2f64 offset = lm2_mul_lm2_v2f64_double(normalized, half_length);
  lm2_capsule2_f64 capsule;
  capsule.start = lm2_sub_lm2_v2f64(center, offset);
  capsule.end = lm2_add_lm2_v2f64(center, offset);
  capsule.radius = radius;
  return capsule;
}

LM2_API lm2_capsule2_f32 lm2_capsule2_from_center_f32(lm2_v2f32 center, lm2_v2f32 direction, float half_length, float radius) {
  LM2_ASSERT(radius >= 0.0f);
  LM2_ASSERT(half_length >= 0.0f);
  lm2_v2f32 normalized = lm2_normalize_v2f32(direction);
  lm2_v2f32 offset = lm2_mul_lm2_v2f32_float(normalized, half_length);
  lm2_capsule2_f32 capsule;
  capsule.start = lm2_sub_lm2_v2f32(center, offset);
  capsule.end = lm2_add_lm2_v2f32(center, offset);
  capsule.radius = radius;
  return capsule;
}

// =============================================================================
// Capsule Properties
// =============================================================================

LM2_API double lm2_capsule2_length_f64(lm2_capsule2_f64 capsule) {
  return lm2_distance_v2f64(capsule.start, capsule.end);
}

LM2_API float lm2_capsule2_length_f32(lm2_capsule2_f32 capsule) {
  return lm2_distance_v2f32(capsule.start, capsule.end);
}

LM2_API double lm2_capsule2_total_length_f64(lm2_capsule2_f64 capsule) {
  double seg_length = lm2_distance_v2f64(capsule.start, capsule.end);
  double diameter = lm2_mul_f64(2.0, capsule.radius);
  return lm2_add_f64(seg_length, diameter);
}

LM2_API float lm2_capsule2_total_length_f32(lm2_capsule2_f32 capsule) {
  float seg_length = lm2_distance_v2f32(capsule.start, capsule.end);
  float diameter = lm2_mul_f32(2.0f, capsule.radius);
  return lm2_add_f32(seg_length, diameter);
}

LM2_API double lm2_capsule2_area_f64(lm2_capsule2_f64 capsule) {
  // Area = π * r² + 2 * r * length (circle + rectangle)
  double seg_length = lm2_distance_v2f64(capsule.start, capsule.end);
  double r_squared = lm2_mul_f64(capsule.radius, capsule.radius);
  double circle_area = lm2_mul_f64(LM2_PI_F64, r_squared);
  double rect_area = lm2_mul_f64(lm2_mul_f64(2.0, capsule.radius), seg_length);
  return lm2_add_f64(circle_area, rect_area);
}

LM2_API float lm2_capsule2_area_f32(lm2_capsule2_f32 capsule) {
  // Area = π * r² + 2 * r * length (circle + rectangle)
  float seg_length = lm2_distance_v2f32(capsule.start, capsule.end);
  float r_squared = lm2_mul_f32(capsule.radius, capsule.radius);
  float circle_area = lm2_mul_f32(LM2_PI_F32, r_squared);
  float rect_area = lm2_mul_f32(lm2_mul_f32(2.0f, capsule.radius), seg_length);
  return lm2_add_f32(circle_area, rect_area);
}

LM2_API double lm2_capsule2_perimeter_f64(lm2_capsule2_f64 capsule) {
  // Perimeter = 2 * π * r + 2 * length
  double seg_length = lm2_distance_v2f64(capsule.start, capsule.end);
  double circle_perim = lm2_mul_f64(lm2_mul_f64(2.0, LM2_PI_F64), capsule.radius);
  double line_perim = lm2_mul_f64(2.0, seg_length);
  return lm2_add_f64(circle_perim, line_perim);
}

LM2_API float lm2_capsule2_perimeter_f32(lm2_capsule2_f32 capsule) {
  // Perimeter = 2 * π * r + 2 * length
  float seg_length = lm2_distance_v2f32(capsule.start, capsule.end);
  float circle_perim = lm2_mul_f32(lm2_mul_f32(2.0f, LM2_PI_F32), capsule.radius);
  float line_perim = lm2_mul_f32(2.0f, seg_length);
  return lm2_add_f32(circle_perim, line_perim);
}

LM2_API lm2_v2f64 lm2_capsule2_center_f64(lm2_capsule2_f64 capsule) {
  lm2_v2f64 sum = lm2_add_lm2_v2f64(capsule.start, capsule.end);
  return lm2_mul_lm2_v2f64_double(sum, 0.5);
}

LM2_API lm2_v2f32 lm2_capsule2_center_f32(lm2_capsule2_f32 capsule) {
  lm2_v2f32 sum = lm2_add_lm2_v2f32(capsule.start, capsule.end);
  return lm2_mul_lm2_v2f32_float(sum, 0.5f);
}

// =============================================================================
// Capsule-Point Collision
// =============================================================================

LM2_API bool lm2_capsule2_contains_point_f64(lm2_capsule2_f64 capsule, lm2_v2f64 point) {
  lm2_edge2_f64 edge = {capsule.start, capsule.end};
  double dist_sq = lm2_point_to_edge2_distance_sq_f64(point, edge);
  double radius_sq = lm2_mul_f64(capsule.radius, capsule.radius);
  return dist_sq <= radius_sq;
}

LM2_API bool lm2_capsule2_contains_point_f32(lm2_capsule2_f32 capsule, lm2_v2f32 point) {
  lm2_edge2_f32 edge = {capsule.start, capsule.end};
  float dist_sq = lm2_point_to_edge2_distance_sq_f32(point, edge);
  float radius_sq = lm2_mul_f32(capsule.radius, capsule.radius);
  return dist_sq <= radius_sq;
}

// =============================================================================
// Capsule-Capsule Collision
// =============================================================================

LM2_API bool lm2_capsule2s_overlap_f64(lm2_capsule2_f64 a, lm2_capsule2_f64 b) {
  lm2_edge2_f64 edge_a = {a.start, a.end};
  lm2_edge2_f64 edge_b = {b.start, b.end};
  double dist_sq = lm2_edge2_to_edge2_distance_sq_f64(edge_a, edge_b);
  double sum_radii = lm2_add_f64(a.radius, b.radius);
  double sum_radii_sq = lm2_mul_f64(sum_radii, sum_radii);
  return dist_sq <= sum_radii_sq;
}

LM2_API bool lm2_capsule2s_overlap_f32(lm2_capsule2_f32 a, lm2_capsule2_f32 b) {
  lm2_edge2_f32 edge_a = {a.start, a.end};
  lm2_edge2_f32 edge_b = {b.start, b.end};
  float dist_sq = lm2_edge2_to_edge2_distance_sq_f32(edge_a, edge_b);
  float sum_radii = lm2_add_f32(a.radius, b.radius);
  float sum_radii_sq = lm2_mul_f32(sum_radii, sum_radii);
  return dist_sq <= sum_radii_sq;
}

// =============================================================================
// Capsule Transformations
// =============================================================================

LM2_API lm2_capsule2_f64 lm2_capsule2_translate_f64(lm2_capsule2_f64 capsule, lm2_v2f64 offset) {
  lm2_capsule2_f64 result;
  result.start = lm2_add_lm2_v2f64(capsule.start, offset);
  result.end = lm2_add_lm2_v2f64(capsule.end, offset);
  result.radius = capsule.radius;
  return result;
}

LM2_API lm2_capsule2_f32 lm2_capsule2_translate_f32(lm2_capsule2_f32 capsule, lm2_v2f32 offset) {
  lm2_capsule2_f32 result;
  result.start = lm2_add_lm2_v2f32(capsule.start, offset);
  result.end = lm2_add_lm2_v2f32(capsule.end, offset);
  result.radius = capsule.radius;
  return result;
}

LM2_API lm2_capsule2_f64 lm2_capsule2_scale_radius_f64(lm2_capsule2_f64 capsule, double scale) {
  LM2_ASSERT(scale >= 0.0);
  lm2_capsule2_f64 result;
  result.start = capsule.start;
  result.end = capsule.end;
  result.radius = lm2_mul_f64(capsule.radius, scale);
  return result;
}

LM2_API lm2_capsule2_f32 lm2_capsule2_scale_radius_f32(lm2_capsule2_f32 capsule, float scale) {
  LM2_ASSERT(scale >= 0.0f);
  lm2_capsule2_f32 result;
  result.start = capsule.start;
  result.end = capsule.end;
  result.radius = lm2_mul_f32(capsule.radius, scale);
  return result;
}
