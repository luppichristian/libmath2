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

#include <lm2/geometry2d/lm2_plane2.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/scalar/lm2_trigonometry.h>
#include <lm2/vectors/lm2_vector_specifics.h>

// =============================================================================
// Construction Helpers
// =============================================================================

LM2_API lm2_plane2_f64 lm2_plane2_make_f64(lm2_v2_f64 normal, double distance) {
  lm2_plane2_f64 plane;
  plane.normal = lm2_v2_normalize_f64(normal);
  plane.distance = distance;
  return plane;
}

LM2_API lm2_plane2_f32 lm2_plane2_make_f32(lm2_v2_f32 normal, float distance) {
  lm2_plane2_f32 plane;
  plane.normal = lm2_v2_normalize_f32(normal);
  plane.distance = distance;
  return plane;
}

LM2_API lm2_plane2_f64 lm2_plane2_from_point_normal_f64(lm2_v2_f64 point, lm2_v2_f64 normal) {
  lm2_plane2_f64 plane;
  plane.normal = lm2_v2_normalize_f64(normal);
  plane.distance = lm2_v2_dot_f64(plane.normal, point);
  return plane;
}

LM2_API lm2_plane2_f32 lm2_plane2_from_point_normal_f32(lm2_v2_f32 point, lm2_v2_f32 normal) {
  lm2_plane2_f32 plane;
  plane.normal = lm2_v2_normalize_f32(normal);
  plane.distance = lm2_v2_dot_f32(plane.normal, point);
  return plane;
}

LM2_API lm2_plane2_f64 lm2_plane2_from_points_f64(lm2_v2_f64 p0, lm2_v2_f64 p1) {
  // Calculate edge vector
  lm2_v2_f64 edge = lm2_v2_sub_f64(p1, p0);

  // Calculate normal as perpendicular to edge (counter-clockwise 90 degree rotation)
  // If edge = (dx, dy), then normal = (-dy, dx)
  lm2_v2_f64 normal;
  normal.x = lm2_neg_f64(edge.y);
  normal.y = edge.x;

  return lm2_plane2_from_point_normal_f64(p0, normal);
}

LM2_API lm2_plane2_f32 lm2_plane2_from_points_f32(lm2_v2_f32 p0, lm2_v2_f32 p1) {
  // Calculate edge vector
  lm2_v2_f32 edge = lm2_v2_sub_f32(p1, p0);

  // Calculate normal as perpendicular to edge (counter-clockwise 90 degree rotation)
  // If edge = (dx, dy), then normal = (-dy, dx)
  lm2_v2_f32 normal;
  normal.x = lm2_neg_f32(edge.y);
  normal.y = edge.x;

  return lm2_plane2_from_point_normal_f32(p0, normal);
}

LM2_API lm2_plane2_f64 lm2_plane2_x_axis_f64(void) {
  lm2_plane2_f64 plane;
  plane.normal.x = 0.0;
  plane.normal.y = 1.0;
  plane.distance = 0.0;
  return plane;
}

LM2_API lm2_plane2_f32 lm2_plane2_x_axis_f32(void) {
  lm2_plane2_f32 plane;
  plane.normal.x = 0.0f;
  plane.normal.y = 1.0f;
  plane.distance = 0.0f;
  return plane;
}

LM2_API lm2_plane2_f64 lm2_plane2_y_axis_f64(void) {
  lm2_plane2_f64 plane;
  plane.normal.x = 1.0;
  plane.normal.y = 0.0;
  plane.distance = 0.0;
  return plane;
}

LM2_API lm2_plane2_f32 lm2_plane2_y_axis_f32(void) {
  lm2_plane2_f32 plane;
  plane.normal.x = 1.0f;
  plane.normal.y = 0.0f;
  plane.distance = 0.0f;
  return plane;
}

// =============================================================================
// Plane Operations
// =============================================================================

LM2_API double lm2_plane2_distance_to_point_f64(lm2_plane2_f64 plane, lm2_v2_f64 point) {
  // Signed distance = dot(normal, point) - distance
  double dot_product = lm2_v2_dot_f64(plane.normal, point);
  return lm2_sub_f64(dot_product, plane.distance);
}

LM2_API float lm2_plane2_distance_to_point_f32(lm2_plane2_f32 plane, lm2_v2_f32 point) {
  // Signed distance = dot(normal, point) - distance
  float dot_product = lm2_v2_dot_f32(plane.normal, point);
  return lm2_sub_f32(dot_product, plane.distance);
}

LM2_API lm2_v2_f64 lm2_plane2_project_point_f64(lm2_plane2_f64 plane, lm2_v2_f64 point) {
  // Project point = point - distance_to_plane * normal
  double dist = lm2_plane2_distance_to_point_f64(plane, point);
  lm2_v2_f64 offset = lm2_v2_mul_s_f64(plane.normal, dist);
  return lm2_v2_sub_f64(point, offset);
}

LM2_API lm2_v2_f32 lm2_plane2_project_point_f32(lm2_plane2_f32 plane, lm2_v2_f32 point) {
  // Project point = point - distance_to_plane * normal
  float dist = lm2_plane2_distance_to_point_f32(plane, point);
  lm2_v2_f32 offset = lm2_v2_mul_s_f32(plane.normal, dist);
  return lm2_v2_sub_f32(point, offset);
}

LM2_API lm2_v2_f64 lm2_plane2_closest_point_f64(lm2_plane2_f64 plane, lm2_v2_f64 point) {
  return lm2_plane2_project_point_f64(plane, point);
}

LM2_API lm2_v2_f32 lm2_plane2_closest_point_f32(lm2_plane2_f32 plane, lm2_v2_f32 point) {
  return lm2_plane2_project_point_f32(plane, point);
}

// =============================================================================
// Plane Tests
// =============================================================================

LM2_API bool lm2_plane2_contains_point_f64(lm2_plane2_f64 plane, lm2_v2_f64 point, double epsilon) {
  LM2_ASSERT(epsilon >= 0.0);
  double dist = lm2_abs_f64(lm2_plane2_distance_to_point_f64(plane, point));
  return dist <= epsilon;
}

LM2_API bool lm2_plane2_contains_point_f32(lm2_plane2_f32 plane, lm2_v2_f32 point, float epsilon) {
  LM2_ASSERT(epsilon >= 0.0f);
  float dist = lm2_abs_f32(lm2_plane2_distance_to_point_f32(plane, point));
  return dist <= epsilon;
}

LM2_API double lm2_plane2_side_f64(lm2_plane2_f64 plane, lm2_v2_f64 point) {
  return lm2_plane2_distance_to_point_f64(plane, point);
}

LM2_API float lm2_plane2_side_f32(lm2_plane2_f32 plane, lm2_v2_f32 point) {
  return lm2_plane2_distance_to_point_f32(plane, point);
}

// =============================================================================
// Plane Transformations
// =============================================================================

LM2_API lm2_plane2_f64 lm2_plane2_flip_f64(lm2_plane2_f64 plane) {
  lm2_plane2_f64 result;
  result.normal = lm2_v2_neg_f64(plane.normal);
  result.distance = lm2_neg_f64(plane.distance);
  return result;
}

LM2_API lm2_plane2_f32 lm2_plane2_flip_f32(lm2_plane2_f32 plane) {
  lm2_plane2_f32 result;
  result.normal = lm2_v2_neg_f32(plane.normal);
  result.distance = lm2_neg_f32(plane.distance);
  return result;
}

LM2_API lm2_plane2_f64 lm2_plane2_translate_f64(lm2_plane2_f64 plane, lm2_v2_f64 offset) {
  // Translation along the normal affects distance
  double offset_dot_normal = lm2_v2_dot_f64(offset, plane.normal);
  lm2_plane2_f64 result;
  result.normal = plane.normal;
  result.distance = lm2_add_f64(plane.distance, offset_dot_normal);
  return result;
}

LM2_API lm2_plane2_f32 lm2_plane2_translate_f32(lm2_plane2_f32 plane, lm2_v2_f32 offset) {
  // Translation along the normal affects distance
  float offset_dot_normal = lm2_v2_dot_f32(offset, plane.normal);
  lm2_plane2_f32 result;
  result.normal = plane.normal;
  result.distance = lm2_add_f32(plane.distance, offset_dot_normal);
  return result;
}

LM2_API lm2_plane2_f64 lm2_plane2_rotate_f64(lm2_plane2_f64 plane, double angle) {
  // Rotate the normal vector
  double cos_angle = lm2_cos_f64(angle);
  double sin_angle = lm2_sin_f64(angle);

  lm2_plane2_f64 result;
  result.normal.x = lm2_sub_f64(
      lm2_mul_f64(plane.normal.x, cos_angle),
      lm2_mul_f64(plane.normal.y, sin_angle));
  result.normal.y = lm2_add_f64(
      lm2_mul_f64(plane.normal.x, sin_angle),
      lm2_mul_f64(plane.normal.y, cos_angle));
  result.distance = plane.distance;

  return result;
}

LM2_API lm2_plane2_f32 lm2_plane2_rotate_f32(lm2_plane2_f32 plane, float angle) {
  // Rotate the normal vector
  float cos_angle = lm2_cos_f32(angle);
  float sin_angle = lm2_sin_f32(angle);

  lm2_plane2_f32 result;
  result.normal.x = lm2_sub_f32(
      lm2_mul_f32(plane.normal.x, cos_angle),
      lm2_mul_f32(plane.normal.y, sin_angle));
  result.normal.y = lm2_add_f32(
      lm2_mul_f32(plane.normal.x, sin_angle),
      lm2_mul_f32(plane.normal.y, cos_angle));
  result.distance = plane.distance;

  return result;
}
