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

#include <lm2/geometry3d/lm2_plane3.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/vectors/lm2_vector_specifics.h>

// =============================================================================
// Construction Helpers
// =============================================================================

LM2_API lm2_plane3_f64 lm2_plane3_make_f64(lm2_v3f64 normal, double distance) {
  lm2_plane3_f64 plane;
  plane.normal = lm2_normalize_v3f64(normal);
  plane.distance = distance;
  return plane;
}

LM2_API lm2_plane3_f32 lm2_plane3_make_f32(lm2_v3f32 normal, float distance) {
  lm2_plane3_f32 plane;
  plane.normal = lm2_normalize_v3f32(normal);
  plane.distance = distance;
  return plane;
}

LM2_API lm2_plane3_f64 lm2_plane3_from_point_normal_f64(lm2_v3f64 point, lm2_v3f64 normal) {
  lm2_plane3_f64 plane;
  plane.normal = lm2_normalize_v3f64(normal);
  plane.distance = lm2_dot_v3f64(plane.normal, point);
  return plane;
}

LM2_API lm2_plane3_f32 lm2_plane3_from_point_normal_f32(lm2_v3f32 point, lm2_v3f32 normal) {
  lm2_plane3_f32 plane;
  plane.normal = lm2_normalize_v3f32(normal);
  plane.distance = lm2_dot_v3f32(plane.normal, point);
  return plane;
}

LM2_API lm2_plane3_f64 lm2_plane3_from_points_f64(lm2_v3f64 p0, lm2_v3f64 p1, lm2_v3f64 p2) {
  // Calculate two edge vectors
  lm2_v3f64 edge1 = lm2_sub_lm2_v3f64(p1, p0);
  lm2_v3f64 edge2 = lm2_sub_lm2_v3f64(p2, p0);

  // Calculate normal via cross product
  lm2_v3f64 normal = lm2_cross_v3f64(edge1, edge2);

  return lm2_plane3_from_point_normal_f64(p0, normal);
}

LM2_API lm2_plane3_f32 lm2_plane3_from_points_f32(lm2_v3f32 p0, lm2_v3f32 p1, lm2_v3f32 p2) {
  // Calculate two edge vectors
  lm2_v3f32 edge1 = lm2_sub_lm2_v3f32(p1, p0);
  lm2_v3f32 edge2 = lm2_sub_lm2_v3f32(p2, p0);
  lm2_v3f32 normal = lm2_cross_v3f32(edge1, edge2);

  return lm2_plane3_from_point_normal_f32(p0, normal);
}

LM2_API lm2_plane3_f64 lm2_plane3_xy_f64(void) {
  lm2_plane3_f64 plane;
  plane.normal.x = 0.0;
  plane.normal.y = 0.0;
  plane.normal.z = 1.0;
  plane.distance = 0.0;
  return plane;
}

LM2_API lm2_plane3_f32 lm2_plane3_xy_f32(void) {
  lm2_plane3_f32 plane;
  plane.normal.x = 0.0f;
  plane.normal.y = 0.0f;
  plane.normal.z = 1.0f;
  plane.distance = 0.0f;
  return plane;
}

LM2_API lm2_plane3_f64 lm2_plane3_xz_f64(void) {
  lm2_plane3_f64 plane;
  plane.normal.x = 0.0;
  plane.normal.y = 1.0;
  plane.normal.z = 0.0;
  plane.distance = 0.0;
  return plane;
}

LM2_API lm2_plane3_f32 lm2_plane3_xz_f32(void) {
  lm2_plane3_f32 plane;
  plane.normal.x = 0.0f;
  plane.normal.y = 1.0f;
  plane.normal.z = 0.0f;
  plane.distance = 0.0f;
  return plane;
}

LM2_API lm2_plane3_f64 lm2_plane3_yz_f64(void) {
  lm2_plane3_f64 plane;
  plane.normal.x = 1.0;
  plane.normal.y = 0.0;
  plane.normal.z = 0.0;
  plane.distance = 0.0;
  return plane;
}

LM2_API lm2_plane3_f32 lm2_plane3_yz_f32(void) {
  lm2_plane3_f32 plane;
  plane.normal.x = 1.0f;
  plane.normal.y = 0.0f;
  plane.normal.z = 0.0f;
  plane.distance = 0.0f;
  return plane;
}

// =============================================================================
// Plane Operations
// =============================================================================

LM2_API double lm2_plane3_distance_to_point_f64(lm2_plane3_f64 plane, lm2_v3f64 point) {
  // Signed distance = dot(normal, point) - distance
  double dot_product = lm2_dot_v3f64(plane.normal, point);
  return lm2_sub_f64(dot_product, plane.distance);
}

LM2_API float lm2_plane3_distance_to_point_f32(lm2_plane3_f32 plane, lm2_v3f32 point) {
  // Signed distance = dot(normal, point) - distance
  float dot_product = lm2_dot_v3f32(plane.normal, point);
  return lm2_sub_f32(dot_product, plane.distance);
}

LM2_API lm2_v3f64 lm2_plane3_project_point_f64(lm2_plane3_f64 plane, lm2_v3f64 point) {
  // Project point = point - distance_to_plane * normal
  double dist = lm2_plane3_distance_to_point_f64(plane, point);
  lm2_v3f64 offset = lm2_mul_lm2_v3f64_double(plane.normal, dist);
  return lm2_sub_lm2_v3f64(point, offset);
}

LM2_API lm2_v3f32 lm2_plane3_project_point_f32(lm2_plane3_f32 plane, lm2_v3f32 point) {
  // Project point = point - distance_to_plane * normal
  float dist = lm2_plane3_distance_to_point_f32(plane, point);
  lm2_v3f32 offset = lm2_mul_lm2_v3f32_float(plane.normal, dist);
  return lm2_sub_lm2_v3f32(point, offset);
}

LM2_API lm2_v3f64 lm2_plane3_closest_point_f64(lm2_plane3_f64 plane, lm2_v3f64 point) {
  return lm2_plane3_project_point_f64(plane, point);
}

LM2_API lm2_v3f32 lm2_plane3_closest_point_f32(lm2_plane3_f32 plane, lm2_v3f32 point) {
  return lm2_plane3_project_point_f32(plane, point);
}

// =============================================================================
// Plane Tests
// =============================================================================

LM2_API bool lm2_plane3_contains_point_f64(lm2_plane3_f64 plane, lm2_v3f64 point, double epsilon) {
  LM2_ASSERT(epsilon >= 0.0);
  double dist = lm2_abs_f64(lm2_plane3_distance_to_point_f64(plane, point));
  return dist <= epsilon;
}

LM2_API bool lm2_plane3_contains_point_f32(lm2_plane3_f32 plane, lm2_v3f32 point, float epsilon) {
  LM2_ASSERT(epsilon >= 0.0f);
  float dist = lm2_abs_f32(lm2_plane3_distance_to_point_f32(plane, point));
  return dist <= epsilon;
}

LM2_API double lm2_plane3_side_f64(lm2_plane3_f64 plane, lm2_v3f64 point) {
  return lm2_plane3_distance_to_point_f64(plane, point);
}

LM2_API float lm2_plane3_side_f32(lm2_plane3_f32 plane, lm2_v3f32 point) {
  return lm2_plane3_distance_to_point_f32(plane, point);
}

// =============================================================================
// Plane Transformations
// =============================================================================

LM2_API lm2_plane3_f64 lm2_plane3_flip_f64(lm2_plane3_f64 plane) {
  lm2_plane3_f64 result;
  result.normal = lm2_neg_lm2_v3f64(plane.normal);
  result.distance = lm2_neg_f64(plane.distance);
  return result;
}

LM2_API lm2_plane3_f32 lm2_plane3_flip_f32(lm2_plane3_f32 plane) {
  lm2_plane3_f32 result;
  result.normal = lm2_neg_lm2_v3f32(plane.normal);
  result.distance = lm2_neg_f32(plane.distance);
  return result;
}

LM2_API lm2_plane3_f64 lm2_plane3_translate_f64(lm2_plane3_f64 plane, lm2_v3f64 offset) {
  // Translation along the normal affects distance
  double offset_dot_normal = lm2_dot_v3f64(offset, plane.normal);
  lm2_plane3_f64 result;
  result.normal = plane.normal;
  result.distance = lm2_add_f64(plane.distance, offset_dot_normal);
  return result;
}

LM2_API lm2_plane3_f32 lm2_plane3_translate_f32(lm2_plane3_f32 plane, lm2_v3f32 offset) {
  // Translation along the normal affects distance
  float offset_dot_normal = lm2_dot_v3f32(offset, plane.normal);
  lm2_plane3_f32 result;
  result.normal = plane.normal;
  result.distance = lm2_add_f32(plane.distance, offset_dot_normal);
  return result;
}
