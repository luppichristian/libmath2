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

#include <lm2/geometry3d/lm2_sphere.h>
#include <lm2/lm2_constants.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/vectors/lm2_vector_specifics.h>

// =============================================================================
// Construction Helpers
// =============================================================================

LM2_API lm2_sphere_f64 lm2_sphere_make_f64(lm2_v3_f64 center, double radius) {
  LM2_ASSERT(radius >= 0.0);
  lm2_sphere_f64 sphere;
  sphere.center = center;
  sphere.radius = radius;
  return sphere;
}

LM2_API lm2_sphere_f32 lm2_sphere_make_f32(lm2_v3_f32 center, float radius) {
  LM2_ASSERT(radius >= 0.0f);
  lm2_sphere_f32 sphere;
  sphere.center = center;
  sphere.radius = radius;
  return sphere;
}

LM2_API lm2_sphere_f64 lm2_sphere_make_coords_f64(double x, double y, double z, double radius) {
  LM2_ASSERT(radius >= 0.0);
  lm2_sphere_f64 sphere;
  sphere.center.x = x;
  sphere.center.y = y;
  sphere.center.z = z;
  sphere.radius = radius;
  return sphere;
}

LM2_API lm2_sphere_f32 lm2_sphere_make_coords_f32(float x, float y, float z, float radius) {
  LM2_ASSERT(radius >= 0.0f);
  lm2_sphere_f32 sphere;
  sphere.center.x = x;
  sphere.center.y = y;
  sphere.center.z = z;
  sphere.radius = radius;
  return sphere;
}

LM2_API lm2_sphere_f64 lm2_sphere_unit_f64(void) {
  lm2_sphere_f64 sphere;
  sphere.center.x = 0.0;
  sphere.center.y = 0.0;
  sphere.center.z = 0.0;
  sphere.radius = 1.0;
  return sphere;
}

LM2_API lm2_sphere_f32 lm2_sphere_unit_f32(void) {
  lm2_sphere_f32 sphere;
  sphere.center.x = 0.0f;
  sphere.center.y = 0.0f;
  sphere.center.z = 0.0f;
  sphere.radius = 1.0f;
  return sphere;
}

// =============================================================================
// Sphere Properties
// =============================================================================

LM2_API double lm2_sphere_volume_f64(lm2_sphere_f64 sphere) {
  // Volume = (4/3) * π * r³
  double r_cubed = lm2_mul_f64(lm2_mul_f64(sphere.radius, sphere.radius), sphere.radius);
  double four_thirds = lm2_div_f64(4.0, 3.0);
  return lm2_mul_f64(lm2_mul_f64(four_thirds, LM2_PI_F64), r_cubed);
}

LM2_API float lm2_sphere_volume_f32(lm2_sphere_f32 sphere) {
  // Volume = (4/3) * π * r³
  float r_cubed = lm2_mul_f32(lm2_mul_f32(sphere.radius, sphere.radius), sphere.radius);
  float four_thirds = lm2_div_f32(4.0f, 3.0f);
  return lm2_mul_f32(lm2_mul_f32(four_thirds, LM2_PI_F32), r_cubed);
}

LM2_API double lm2_sphere_surface_area_f64(lm2_sphere_f64 sphere) {
  // Surface Area = 4 * π * r²
  double r_squared = lm2_mul_f64(sphere.radius, sphere.radius);
  return lm2_mul_f64(lm2_mul_f64(4.0, LM2_PI_F64), r_squared);
}

LM2_API float lm2_sphere_surface_area_f32(lm2_sphere_f32 sphere) {
  // Surface Area = 4 * π * r²
  float r_squared = lm2_mul_f32(sphere.radius, sphere.radius);
  return lm2_mul_f32(lm2_mul_f32(4.0f, LM2_PI_F32), r_squared);
}

LM2_API double lm2_sphere_diameter_f64(lm2_sphere_f64 sphere) {
  return lm2_mul_f64(sphere.radius, 2.0);
}

LM2_API float lm2_sphere_diameter_f32(lm2_sphere_f32 sphere) {
  return lm2_mul_f32(sphere.radius, 2.0f);
}

// =============================================================================
// Sphere Tests
// =============================================================================

LM2_API bool lm2_sphere_contains_point_f64(lm2_sphere_f64 sphere, lm2_v3_f64 point) {
  double dist_sq = lm2_v3_distance_sq_f64(sphere.center, point);
  double radius_sq = lm2_mul_f64(sphere.radius, sphere.radius);
  return dist_sq <= radius_sq;
}

LM2_API bool lm2_sphere_contains_point_f32(lm2_sphere_f32 sphere, lm2_v3_f32 point) {
  float dist_sq = lm2_v3_distance_sq_f32(sphere.center, point);
  float radius_sq = lm2_mul_f32(sphere.radius, sphere.radius);
  return dist_sq <= radius_sq;
}

LM2_API bool lm2_spheres_overlap_f64(lm2_sphere_f64 a, lm2_sphere_f64 b) {
  double dist_sq = lm2_v3_distance_sq_f64(a.center, b.center);
  double radius_sum = lm2_add_f64(a.radius, b.radius);
  double radius_sum_sq = lm2_mul_f64(radius_sum, radius_sum);
  return dist_sq <= radius_sum_sq;
}

LM2_API bool lm2_spheres_overlap_f32(lm2_sphere_f32 a, lm2_sphere_f32 b) {
  float dist_sq = lm2_v3_distance_sq_f32(a.center, b.center);
  float radius_sum = lm2_add_f32(a.radius, b.radius);
  float radius_sum_sq = lm2_mul_f32(radius_sum, radius_sum);
  return dist_sq <= radius_sum_sq;
}

LM2_API bool lm2_sphere_contains_sphere_f64(lm2_sphere_f64 a, lm2_sphere_f64 b) {
  double dist = lm2_v3_distance_f64(a.center, b.center);
  double radius_diff = lm2_sub_f64(a.radius, b.radius);
  return dist <= radius_diff && radius_diff >= 0.0;
}

LM2_API bool lm2_sphere_contains_sphere_f32(lm2_sphere_f32 a, lm2_sphere_f32 b) {
  float dist = lm2_v3_distance_f32(a.center, b.center);
  float radius_diff = lm2_sub_f32(a.radius, b.radius);
  return dist <= radius_diff && radius_diff >= 0.0f;
}

// =============================================================================
// Sphere Transformations
// =============================================================================

LM2_API lm2_sphere_f64 lm2_sphere_translate_f64(lm2_sphere_f64 sphere, lm2_v3_f64 offset) {
  lm2_sphere_f64 result;
  result.center = lm2_v3_add_f64(sphere.center, offset);
  result.radius = sphere.radius;
  return result;
}

LM2_API lm2_sphere_f32 lm2_sphere_translate_f32(lm2_sphere_f32 sphere, lm2_v3_f32 offset) {
  lm2_sphere_f32 result;
  result.center = lm2_v3_add_f32(sphere.center, offset);
  result.radius = sphere.radius;
  return result;
}

LM2_API lm2_sphere_f64 lm2_sphere_scale_f64(lm2_sphere_f64 sphere, double scale) {
  lm2_sphere_f64 result;
  result.center = sphere.center;
  result.radius = lm2_mul_f64(sphere.radius, scale);
  return result;
}

LM2_API lm2_sphere_f32 lm2_sphere_scale_f32(lm2_sphere_f32 sphere, float scale) {
  lm2_sphere_f32 result;
  result.center = sphere.center;
  result.radius = lm2_mul_f32(sphere.radius, scale);
  return result;
}
