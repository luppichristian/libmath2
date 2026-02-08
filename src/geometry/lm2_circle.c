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

#include <lm2/geometry/lm2_circle.h>
#include <lm2/lm2_constants.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/vectors/lm2_vector_specifics.h>

// =============================================================================
// Construction Helpers
// =============================================================================

LM2_API lm2_circle_f64 lm2_circle_make_f64(lm2_v2f64 center, double radius) {
  LM2_ASSERT(radius >= 0.0);
  lm2_circle_f64 circle;
  circle.center = center;
  circle.radius = radius;
  return circle;
}

LM2_API lm2_circle_f32 lm2_circle_make_f32(lm2_v2f32 center, float radius) {
  LM2_ASSERT(radius >= 0.0f);
  lm2_circle_f32 circle;
  circle.center = center;
  circle.radius = radius;
  return circle;
}

LM2_API lm2_circle_f64 lm2_circle_make_coords_f64(double x, double y, double radius) {
  LM2_ASSERT(radius >= 0.0);
  lm2_circle_f64 circle;
  circle.center.x = x;
  circle.center.y = y;
  circle.radius = radius;
  return circle;
}

LM2_API lm2_circle_f32 lm2_circle_make_coords_f32(float x, float y, float radius) {
  LM2_ASSERT(radius >= 0.0f);
  lm2_circle_f32 circle;
  circle.center.x = x;
  circle.center.y = y;
  circle.radius = radius;
  return circle;
}

LM2_API lm2_circle_f64 lm2_circle_unit_f64(void) {
  lm2_circle_f64 circle;
  circle.center.x = 0.0;
  circle.center.y = 0.0;
  circle.radius = 1.0;
  return circle;
}

LM2_API lm2_circle_f32 lm2_circle_unit_f32(void) {
  lm2_circle_f32 circle;
  circle.center.x = 0.0f;
  circle.center.y = 0.0f;
  circle.radius = 1.0f;
  return circle;
}

// =============================================================================
// Circle Properties
// =============================================================================

LM2_API double lm2_circle_area_f64(lm2_circle_f64 circle) {
  // Area = π * r²
  double r_squared = lm2_mul_f64(circle.radius, circle.radius);
  return lm2_mul_f64(LM2_PI_F64, r_squared);
}

LM2_API float lm2_circle_area_f32(lm2_circle_f32 circle) {
  // Area = π * r²
  float r_squared = lm2_mul_f32(circle.radius, circle.radius);
  return lm2_mul_f32(LM2_PI_F32, r_squared);
}

LM2_API double lm2_circle_circumference_f64(lm2_circle_f64 circle) {
  // Circumference = 2 * π * r
  double two_pi = lm2_mul_f64(2.0, LM2_PI_F64);
  return lm2_mul_f64(two_pi, circle.radius);
}

LM2_API float lm2_circle_circumference_f32(lm2_circle_f32 circle) {
  // Circumference = 2 * π * r
  float two_pi = lm2_mul_f32(2.0f, LM2_PI_F32);
  return lm2_mul_f32(two_pi, circle.radius);
}

LM2_API double lm2_circle_diameter_f64(lm2_circle_f64 circle) {
  // Diameter = 2 * r
  return lm2_mul_f64(2.0, circle.radius);
}

LM2_API float lm2_circle_diameter_f32(lm2_circle_f32 circle) {
  // Diameter = 2 * r
  return lm2_mul_f32(2.0f, circle.radius);
}

// =============================================================================
// Circle Tests
// =============================================================================

LM2_API bool lm2_circle_contains_point_f64(lm2_circle_f64 circle, lm2_v2f64 point) {
  double dist_sq = lm2_v2_distance_sq_f64(circle.center, point);
  double radius_sq = lm2_mul_f64(circle.radius, circle.radius);
  return dist_sq <= radius_sq;
}

LM2_API bool lm2_circle_contains_point_f32(lm2_circle_f32 circle, lm2_v2f32 point) {
  float dist_sq = lm2_v2_distance_sq_f32(circle.center, point);
  float radius_sq = lm2_mul_f32(circle.radius, circle.radius);
  return dist_sq <= radius_sq;
}

LM2_API bool lm2_circles_overlap_f64(lm2_circle_f64 a, lm2_circle_f64 b) {
  double dist_sq = lm2_v2_distance_sq_f64(a.center, b.center);
  double sum_radii = lm2_add_f64(a.radius, b.radius);
  double sum_radii_sq = lm2_mul_f64(sum_radii, sum_radii);
  return dist_sq <= sum_radii_sq;
}

LM2_API bool lm2_circles_overlap_f32(lm2_circle_f32 a, lm2_circle_f32 b) {
  float dist_sq = lm2_v2_distance_sq_f32(a.center, b.center);
  float sum_radii = lm2_add_f32(a.radius, b.radius);
  float sum_radii_sq = lm2_mul_f32(sum_radii, sum_radii);
  return dist_sq <= sum_radii_sq;
}

LM2_API bool lm2_circle_contains_circle_f64(lm2_circle_f64 a, lm2_circle_f64 b) {
  // Circle 'a' contains circle 'b' if distance between centers + radius of b <= radius of a
  double dist = lm2_v2_distance_f64(a.center, b.center);
  double dist_plus_b_radius = lm2_add_f64(dist, b.radius);
  return dist_plus_b_radius <= a.radius;
}

LM2_API bool lm2_circle_contains_circle_f32(lm2_circle_f32 a, lm2_circle_f32 b) {
  // Circle 'a' contains circle 'b' if distance between centers + radius of b <= radius of a
  float dist = lm2_v2_distance_f32(a.center, b.center);
  float dist_plus_b_radius = lm2_add_f32(dist, b.radius);
  return dist_plus_b_radius <= a.radius;
}

// =============================================================================
// Circle Transformations
// =============================================================================

LM2_API lm2_circle_f64 lm2_circle_translate_f64(lm2_circle_f64 circle, lm2_v2f64 offset) {
  lm2_circle_f64 result;
  result.center = lm2_add_lm2_v2f64(circle.center, offset);
  result.radius = circle.radius;
  return result;
}

LM2_API lm2_circle_f32 lm2_circle_translate_f32(lm2_circle_f32 circle, lm2_v2f32 offset) {
  lm2_circle_f32 result;
  result.center = lm2_add_lm2_v2f32(circle.center, offset);
  result.radius = circle.radius;
  return result;
}

LM2_API lm2_circle_f64 lm2_circle_scale_f64(lm2_circle_f64 circle, double scale) {
  LM2_ASSERT(scale >= 0.0);
  lm2_circle_f64 result;
  result.center = circle.center;
  result.radius = lm2_mul_f64(circle.radius, scale);
  return result;
}

LM2_API lm2_circle_f32 lm2_circle_scale_f32(lm2_circle_f32 circle, float scale) {
  LM2_ASSERT(scale >= 0.0f);
  lm2_circle_f32 result;
  result.center = circle.center;
  result.radius = lm2_mul_f32(circle.radius, scale);
  return result;
}
