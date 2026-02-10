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

#include <lm2/geometry3d/lm2_capsule3.h>
#include <lm2/geometry3d/lm2_edge3.h>
#include <lm2/lm2_constants.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/vectors/lm2_vector3.h>
#include <lm2/vectors/lm2_vector_specifics.h>

// =============================================================================
// Construction Helpers
// =============================================================================

LM2_API lm2_capsule3_f64 lm2_capsule3_make_f64(lm2_v3_f64 start, lm2_v3_f64 end, double radius) {
  LM2_ASSERT(radius >= 0.0);
  lm2_capsule3_f64 capsule;
  capsule.start = start;
  capsule.end = end;
  capsule.radius = radius;
  return capsule;
}

LM2_API lm2_capsule3_f32 lm2_capsule3_make_f32(lm2_v3_f32 start, lm2_v3_f32 end, float radius) {
  LM2_ASSERT(radius >= 0.0f);
  lm2_capsule3_f32 capsule;
  capsule.start = start;
  capsule.end = end;
  capsule.radius = radius;
  return capsule;
}

LM2_API lm2_capsule3_f64 lm2_capsule3_make_coords_f64(double x1, double y1, double z1, double x2, double y2, double z2, double radius) {
  LM2_ASSERT(radius >= 0.0);
  lm2_capsule3_f64 capsule;
  capsule.start.x = x1;
  capsule.start.y = y1;
  capsule.start.z = z1;
  capsule.end.x = x2;
  capsule.end.y = y2;
  capsule.end.z = z2;
  capsule.radius = radius;
  return capsule;
}

LM2_API lm2_capsule3_f32 lm2_capsule3_make_coords_f32(float x1, float y1, float z1, float x2, float y2, float z2, float radius) {
  LM2_ASSERT(radius >= 0.0f);
  lm2_capsule3_f32 capsule;
  capsule.start.x = x1;
  capsule.start.y = y1;
  capsule.start.z = z1;
  capsule.end.x = x2;
  capsule.end.y = y2;
  capsule.end.z = z2;
  capsule.radius = radius;
  return capsule;
}

LM2_API lm2_capsule3_f64 lm2_capsule3_from_center_f64(lm2_v3_f64 center, lm2_v3_f64 direction, double half_length, double radius) {
  LM2_ASSERT(radius >= 0.0);
  LM2_ASSERT(half_length >= 0.0);
  lm2_v3_f64 normalized = lm2_v3_normalize_f64(direction);
  lm2_v3_f64 offset = lm2_v3_mul_s_f64(normalized, half_length);
  lm2_capsule3_f64 capsule;
  capsule.start = lm2_v3_sub_f64(center, offset);
  capsule.end = lm2_v3_add_f64(center, offset);
  capsule.radius = radius;
  return capsule;
}

LM2_API lm2_capsule3_f32 lm2_capsule3_from_center_f32(lm2_v3_f32 center, lm2_v3_f32 direction, float half_length, float radius) {
  LM2_ASSERT(radius >= 0.0f);
  LM2_ASSERT(half_length >= 0.0f);
  lm2_v3_f32 normalized = lm2_v3_normalize_f32(direction);
  lm2_v3_f32 offset = lm2_v3_mul_s_f32(normalized, half_length);
  lm2_capsule3_f32 capsule;
  capsule.start = lm2_v3_sub_f32(center, offset);
  capsule.end = lm2_v3_add_f32(center, offset);
  capsule.radius = radius;
  return capsule;
}

// =============================================================================
// Capsule Properties
// =============================================================================

LM2_API double lm2_capsule3_length_f64(lm2_capsule3_f64 capsule) {
  return lm2_v3_distance_f64(capsule.start, capsule.end);
}

LM2_API float lm2_capsule3_length_f32(lm2_capsule3_f32 capsule) {
  return lm2_v3_distance_f32(capsule.start, capsule.end);
}

LM2_API double lm2_capsule3_total_length_f64(lm2_capsule3_f64 capsule) {
  double seg_length = lm2_v3_distance_f64(capsule.start, capsule.end);
  double diameter = lm2_mul_f64(2.0, capsule.radius);
  return lm2_add_f64(seg_length, diameter);
}

LM2_API float lm2_capsule3_total_length_f32(lm2_capsule3_f32 capsule) {
  float seg_length = lm2_v3_distance_f32(capsule.start, capsule.end);
  float diameter = lm2_mul_f32(2.0f, capsule.radius);
  return lm2_add_f32(seg_length, diameter);
}

LM2_API double lm2_capsule3_volume_f64(lm2_capsule3_f64 capsule) {
  // Volume = (4/3) * π * r³ + π * r² * h (sphere + cylinder)
  double seg_length = lm2_v3_distance_f64(capsule.start, capsule.end);
  double r_squared = lm2_mul_f64(capsule.radius, capsule.radius);
  double r_cubed = lm2_mul_f64(r_squared, capsule.radius);

  // Sphere volume: (4/3) * π * r³
  double sphere_volume = lm2_mul_f64(lm2_mul_f64(lm2_div_f64(4.0, 3.0), LM2_PI_F64), r_cubed);

  // Cylinder volume: π * r² * h
  double cylinder_volume = lm2_mul_f64(lm2_mul_f64(LM2_PI_F64, r_squared), seg_length);

  return lm2_add_f64(sphere_volume, cylinder_volume);
}

LM2_API float lm2_capsule3_volume_f32(lm2_capsule3_f32 capsule) {
  // Volume = (4/3) * π * r³ + π * r² * h (sphere + cylinder)
  float seg_length = lm2_v3_distance_f32(capsule.start, capsule.end);
  float r_squared = lm2_mul_f32(capsule.radius, capsule.radius);
  float r_cubed = lm2_mul_f32(r_squared, capsule.radius);

  // Sphere volume: (4/3) * π * r³
  float sphere_volume = lm2_mul_f32(lm2_mul_f32(lm2_div_f32(4.0f, 3.0f), LM2_PI_F32), r_cubed);

  // Cylinder volume: π * r² * h
  float cylinder_volume = lm2_mul_f32(lm2_mul_f32(LM2_PI_F32, r_squared), seg_length);

  return lm2_add_f32(sphere_volume, cylinder_volume);
}

LM2_API double lm2_capsule3_surface_area_f64(lm2_capsule3_f64 capsule) {
  // Surface area = 4 * π * r² + 2 * π * r * h (sphere + cylinder lateral)
  double seg_length = lm2_v3_distance_f64(capsule.start, capsule.end);
  double r_squared = lm2_mul_f64(capsule.radius, capsule.radius);

  // Sphere surface area: 4 * π * r²
  double sphere_area = lm2_mul_f64(lm2_mul_f64(4.0, LM2_PI_F64), r_squared);

  // Cylinder lateral surface area: 2 * π * r * h
  double cylinder_area = lm2_mul_f64(lm2_mul_f64(lm2_mul_f64(2.0, LM2_PI_F64), capsule.radius), seg_length);

  return lm2_add_f64(sphere_area, cylinder_area);
}

LM2_API float lm2_capsule3_surface_area_f32(lm2_capsule3_f32 capsule) {
  // Surface area = 4 * π * r² + 2 * π * r * h (sphere + cylinder lateral)
  float seg_length = lm2_v3_distance_f32(capsule.start, capsule.end);
  float r_squared = lm2_mul_f32(capsule.radius, capsule.radius);

  // Sphere surface area: 4 * π * r²
  float sphere_area = lm2_mul_f32(lm2_mul_f32(4.0f, LM2_PI_F32), r_squared);

  // Cylinder lateral surface area: 2 * π * r * h
  float cylinder_area = lm2_mul_f32(lm2_mul_f32(lm2_mul_f32(2.0f, LM2_PI_F32), capsule.radius), seg_length);

  return lm2_add_f32(sphere_area, cylinder_area);
}

LM2_API lm2_v3_f64 lm2_capsule3_center_f64(lm2_capsule3_f64 capsule) {
  lm2_v3_f64 sum = lm2_v3_add_f64(capsule.start, capsule.end);
  return lm2_v3_mul_s_f64(sum, 0.5);
}

LM2_API lm2_v3_f32 lm2_capsule3_center_f32(lm2_capsule3_f32 capsule) {
  lm2_v3_f32 sum = lm2_v3_add_f32(capsule.start, capsule.end);
  return lm2_v3_mul_s_f32(sum, 0.5f);
}

// =============================================================================
// Capsule-Point Collision
// =============================================================================

LM2_API bool lm2_capsule3_contains_point_f64(lm2_capsule3_f64 capsule, lm2_v3_f64 point) {
  lm2_edge3_f64 edge = {capsule.start, capsule.end};
  double dist_sq = lm2_point_to_edge3_distance_sq_f64(point, edge);
  double radius_sq = lm2_mul_f64(capsule.radius, capsule.radius);
  return dist_sq <= radius_sq;
}

LM2_API bool lm2_capsule3_contains_point_f32(lm2_capsule3_f32 capsule, lm2_v3_f32 point) {
  lm2_edge3_f32 edge = {capsule.start, capsule.end};
  float dist_sq = lm2_point_to_edge3_distance_sq_f32(point, edge);
  float radius_sq = lm2_mul_f32(capsule.radius, capsule.radius);
  return dist_sq <= radius_sq;
}

// Helper function to compute segment to segment distance squared
static double segment_to_segment_distance_sq_f64(lm2_v3_f64 a1, lm2_v3_f64 a2, lm2_v3_f64 b1, lm2_v3_f64 b2) {
  // Use the minimum of four point-to-segment distances
  double d1 = point_to_segment_distance_sq_f64(a1, b1, b2);
  double d2 = point_to_segment_distance_sq_f64(a2, b1, b2);
  double d3 = point_to_segment_distance_sq_f64(b1, a1, a2);
  double d4 = point_to_segment_distance_sq_f64(b2, a1, a2);

  double min1 = lm2_min_f64(d1, d2);
  double min2 = lm2_min_f64(d3, d4);
  return lm2_min_f64(min1, min2);
}

static float segment_to_segment_distance_sq_f32(lm2_v3_f32 a1, lm2_v3_f32 a2, lm2_v3_f32 b1, lm2_v3_f32 b2) {
  // Use the minimum of four point-to-segment distances
  float d1 = point_to_segment_distance_sq_f32(a1, b1, b2);
  float d2 = point_to_segment_distance_sq_f32(a2, b1, b2);
  float d3 = point_to_segment_distance_sq_f32(b1, a1, a2);
  float d4 = point_to_segment_distance_sq_f32(b2, a1, a2);

  float min1 = lm2_min_f32(d1, d2);
  float min2 = lm2_min_f32(d3, d4);
  return lm2_min_f32(min1, min2);
}

LM2_API bool lm2_capsules3_overlap_f64(lm2_capsule3_f64 a, lm2_capsule3_f64 b) {
  double dist_sq = segment_to_segment_distance_sq_f64(a.start, a.end, b.start, b.end);
  double sum_radii = lm2_add_f64(a.radius, b.radius);
  double sum_radii_sq = lm2_mul_f64(sum_radii, sum_radii);
  return dist_sq <= sum_radii_sq;
}

LM2_API bool lm2_capsules3_overlap_f32(lm2_capsule3_f32 a, lm2_capsule3_f32 b) {
  float dist_sq = segment_to_segment_distance_sq_f32(a.start, a.end, b.start, b.end);
  float sum_radii = lm2_add_f32(a.radius, b.radius);
  float sum_radii_sq = lm2_mul_f32(sum_radii, sum_radii);
  return dist_sq <= sum_radii_sq;
}

// =============================================================================
// Capsule Transformations
// =============================================================================

LM2_API lm2_capsule3_f64 lm2_capsule3_translate_f64(lm2_capsule3_f64 capsule, lm2_v3_f64 offset) {
  lm2_capsule3_f64 result;
  result.start = lm2_v3_add_f64(capsule.start, offset);
  result.end = lm2_v3_add_f64(capsule.end, offset);
  result.radius = capsule.radius;
  return result;
}

LM2_API lm2_capsule3_f32 lm2_capsule3_translate_f32(lm2_capsule3_f32 capsule, lm2_v3_f32 offset) {
  lm2_capsule3_f32 result;
  result.start = lm2_v3_add_f32(capsule.start, offset);
  result.end = lm2_v3_add_f32(capsule.end, offset);
  result.radius = capsule.radius;
  return result;
}

LM2_API lm2_capsule3_f64 lm2_capsule3_scale_radius_f64(lm2_capsule3_f64 capsule, double scale) {
  LM2_ASSERT(scale >= 0.0);
  lm2_capsule3_f64 result;
  result.start = capsule.start;
  result.end = capsule.end;
  result.radius = lm2_mul_f64(capsule.radius, scale);
  return result;
}

LM2_API lm2_capsule3_f32 lm2_capsule3_scale_radius_f32(lm2_capsule3_f32 capsule, float scale) {
  LM2_ASSERT(scale >= 0.0f);
  lm2_capsule3_f32 result;
  result.start = capsule.start;
  result.end = capsule.end;
  result.radius = lm2_mul_f32(capsule.radius, scale);
  return result;
}
