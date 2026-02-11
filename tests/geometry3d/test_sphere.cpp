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

#include <gtest/gtest.h>
#include <cmath>
#include "lm2/geometry3d/lm2_sphere.h"

// Test fixture for Sphere tests
class SphereTest : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
  static constexpr double PI = 3.14159265358979323846;
};

// =============================================================================
// Construction Tests (f64)
// =============================================================================

TEST_F(SphereTest, Make_F64) {
  lm2_v3_f64 center = lm2_v3_make_f64(1.0, 2.0, 3.0);
  lm2_sphere_f64 sphere = lm2_sphere_make_f64(center, 5.0);

  EXPECT_DOUBLE_EQ(sphere.center.x, 1.0);
  EXPECT_DOUBLE_EQ(sphere.center.y, 2.0);
  EXPECT_DOUBLE_EQ(sphere.center.z, 3.0);
  EXPECT_DOUBLE_EQ(sphere.radius, 5.0);
}

TEST_F(SphereTest, MakeCoords_F64) {
  lm2_sphere_f64 sphere = lm2_sphere_make_coords_f64(2.0, 3.0, 4.0, 7.0);

  EXPECT_DOUBLE_EQ(sphere.center.x, 2.0);
  EXPECT_DOUBLE_EQ(sphere.center.y, 3.0);
  EXPECT_DOUBLE_EQ(sphere.center.z, 4.0);
  EXPECT_DOUBLE_EQ(sphere.radius, 7.0);
}

TEST_F(SphereTest, Unit_F64) {
  lm2_sphere_f64 sphere = lm2_sphere_unit_f64();

  EXPECT_DOUBLE_EQ(sphere.center.x, 0.0);
  EXPECT_DOUBLE_EQ(sphere.center.y, 0.0);
  EXPECT_DOUBLE_EQ(sphere.center.z, 0.0);
  EXPECT_DOUBLE_EQ(sphere.radius, 1.0);
}

// =============================================================================
// Construction Tests (f32)
// =============================================================================

TEST_F(SphereTest, Make_F32) {
  lm2_v3_f32 center = lm2_v3_make_f32(1.0f, 2.0f, 3.0f);
  lm2_sphere_f32 sphere = lm2_sphere_make_f32(center, 5.0f);

  EXPECT_FLOAT_EQ(sphere.center.x, 1.0f);
  EXPECT_FLOAT_EQ(sphere.center.y, 2.0f);
  EXPECT_FLOAT_EQ(sphere.center.z, 3.0f);
  EXPECT_FLOAT_EQ(sphere.radius, 5.0f);
}

TEST_F(SphereTest, MakeCoords_F32) {
  lm2_sphere_f32 sphere = lm2_sphere_make_coords_f32(2.0f, 3.0f, 4.0f, 7.0f);

  EXPECT_FLOAT_EQ(sphere.center.x, 2.0f);
  EXPECT_FLOAT_EQ(sphere.center.y, 3.0f);
  EXPECT_FLOAT_EQ(sphere.center.z, 4.0f);
  EXPECT_FLOAT_EQ(sphere.radius, 7.0f);
}

TEST_F(SphereTest, Unit_F32) {
  lm2_sphere_f32 sphere = lm2_sphere_unit_f32();

  EXPECT_FLOAT_EQ(sphere.center.x, 0.0f);
  EXPECT_FLOAT_EQ(sphere.center.y, 0.0f);
  EXPECT_FLOAT_EQ(sphere.center.z, 0.0f);
  EXPECT_FLOAT_EQ(sphere.radius, 1.0f);
}

// =============================================================================
// Properties Tests (f64)
// =============================================================================

TEST_F(SphereTest, Volume_F64) {
  lm2_sphere_f64 sphere = lm2_sphere_make_coords_f64(0.0, 0.0, 0.0, 3.0);
  double volume = lm2_sphere_volume_f64(sphere);

  // Volume = (4/3) * π * r^3 = (4/3) * π * 27 = 36π ≈ 113.097
  double expected = (4.0 / 3.0) * PI * 27.0;
  EXPECT_NEAR(volume, expected, EPSILON_F64);
}

TEST_F(SphereTest, SurfaceArea_F64) {
  lm2_sphere_f64 sphere = lm2_sphere_make_coords_f64(0.0, 0.0, 0.0, 3.0);
  double area = lm2_sphere_surface_area_f64(sphere);

  // Surface Area = 4 * π * r^2 = 4 * π * 9 = 36π ≈ 113.097
  double expected = 4.0 * PI * 9.0;
  EXPECT_NEAR(area, expected, EPSILON_F64);
}

TEST_F(SphereTest, Diameter_F64) {
  lm2_sphere_f64 sphere = lm2_sphere_make_coords_f64(0.0, 0.0, 0.0, 5.0);
  double diameter = lm2_sphere_diameter_f64(sphere);

  EXPECT_DOUBLE_EQ(diameter, 10.0);
}

TEST_F(SphereTest, UnitSphereProperties_F64) {
  lm2_sphere_f64 sphere = lm2_sphere_unit_f64();

  // Unit sphere (r=1): volume = (4/3)π, area = 4π
  double volume = lm2_sphere_volume_f64(sphere);
  double area = lm2_sphere_surface_area_f64(sphere);

  EXPECT_NEAR(volume, (4.0 / 3.0) * PI, EPSILON_F64);
  EXPECT_NEAR(area, 4.0 * PI, EPSILON_F64);
}

// =============================================================================
// Properties Tests (f32)
// =============================================================================

TEST_F(SphereTest, Volume_F32) {
  lm2_sphere_f32 sphere = lm2_sphere_make_coords_f32(0.0f, 0.0f, 0.0f, 3.0f);
  float volume = lm2_sphere_volume_f32(sphere);

  float expected = (4.0f / 3.0f) * static_cast<float>(PI) * 27.0f;
  EXPECT_NEAR(volume, expected, EPSILON_F32);
}

TEST_F(SphereTest, SurfaceArea_F32) {
  lm2_sphere_f32 sphere = lm2_sphere_make_coords_f32(0.0f, 0.0f, 0.0f, 3.0f);
  float area = lm2_sphere_surface_area_f32(sphere);

  float expected = 4.0f * static_cast<float>(PI) * 9.0f;
  EXPECT_NEAR(area, expected, EPSILON_F32);
}

TEST_F(SphereTest, Diameter_F32) {
  lm2_sphere_f32 sphere = lm2_sphere_make_coords_f32(0.0f, 0.0f, 0.0f, 5.0f);
  float diameter = lm2_sphere_diameter_f32(sphere);

  EXPECT_FLOAT_EQ(diameter, 10.0f);
}

// =============================================================================
// Containment Tests (f64)
// =============================================================================

TEST_F(SphereTest, ContainsPoint_F64) {
  lm2_sphere_f64 sphere = lm2_sphere_make_coords_f64(0.0, 0.0, 0.0, 10.0);

  // Point inside
  lm2_v3_f64 inside = lm2_v3_make_f64(5.0, 0.0, 0.0);
  EXPECT_TRUE(lm2_sphere_contains_point_f64(sphere, inside));

  // Point outside
  lm2_v3_f64 outside = lm2_v3_make_f64(15.0, 0.0, 0.0);
  EXPECT_FALSE(lm2_sphere_contains_point_f64(sphere, outside));

  // Point on surface (within floating point tolerance)
  lm2_v3_f64 onSurface = lm2_v3_make_f64(10.0, 0.0, 0.0);
  EXPECT_TRUE(lm2_sphere_contains_point_f64(sphere, onSurface));

  // Point at center
  lm2_v3_f64 center = lm2_v3_make_f64(0.0, 0.0, 0.0);
  EXPECT_TRUE(lm2_sphere_contains_point_f64(sphere, center));
}

TEST_F(SphereTest, SpheresOverlap_F64) {
  lm2_sphere_f64 a = lm2_sphere_make_coords_f64(0.0, 0.0, 0.0, 5.0);

  // Overlapping sphere
  lm2_sphere_f64 b = lm2_sphere_make_coords_f64(8.0, 0.0, 0.0, 5.0);
  EXPECT_TRUE(lm2_spheres_overlap_f64(a, b));

  // Non-overlapping sphere
  lm2_sphere_f64 c = lm2_sphere_make_coords_f64(20.0, 0.0, 0.0, 5.0);
  EXPECT_FALSE(lm2_spheres_overlap_f64(a, c));

  // Touching spheres (edge case)
  lm2_sphere_f64 d = lm2_sphere_make_coords_f64(10.0, 0.0, 0.0, 5.0);
  EXPECT_TRUE(lm2_spheres_overlap_f64(a, d));
}

TEST_F(SphereTest, SphereContainsSphere_F64) {
  lm2_sphere_f64 big = lm2_sphere_make_coords_f64(0.0, 0.0, 0.0, 10.0);

  // Completely inside
  lm2_sphere_f64 small = lm2_sphere_make_coords_f64(0.0, 0.0, 0.0, 5.0);
  EXPECT_TRUE(lm2_sphere_contains_sphere_f64(big, small));

  // Partially overlapping (not contained)
  lm2_sphere_f64 partial = lm2_sphere_make_coords_f64(8.0, 0.0, 0.0, 5.0);
  EXPECT_FALSE(lm2_sphere_contains_sphere_f64(big, partial));

  // Completely outside
  lm2_sphere_f64 outside = lm2_sphere_make_coords_f64(20.0, 0.0, 0.0, 5.0);
  EXPECT_FALSE(lm2_sphere_contains_sphere_f64(big, outside));
}

// =============================================================================
// Containment Tests (f32)
// =============================================================================

TEST_F(SphereTest, ContainsPoint_F32) {
  lm2_sphere_f32 sphere = lm2_sphere_make_coords_f32(0.0f, 0.0f, 0.0f, 10.0f);

  lm2_v3_f32 inside = lm2_v3_make_f32(5.0f, 0.0f, 0.0f);
  EXPECT_TRUE(lm2_sphere_contains_point_f32(sphere, inside));

  lm2_v3_f32 outside = lm2_v3_make_f32(15.0f, 0.0f, 0.0f);
  EXPECT_FALSE(lm2_sphere_contains_point_f32(sphere, outside));
}

TEST_F(SphereTest, SpheresOverlap_F32) {
  lm2_sphere_f32 a = lm2_sphere_make_coords_f32(0.0f, 0.0f, 0.0f, 5.0f);
  lm2_sphere_f32 b = lm2_sphere_make_coords_f32(8.0f, 0.0f, 0.0f, 5.0f);

  EXPECT_TRUE(lm2_spheres_overlap_f32(a, b));

  lm2_sphere_f32 c = lm2_sphere_make_coords_f32(20.0f, 0.0f, 0.0f, 5.0f);
  EXPECT_FALSE(lm2_spheres_overlap_f32(a, c));
}

TEST_F(SphereTest, SphereContainsSphere_F32) {
  lm2_sphere_f32 big = lm2_sphere_make_coords_f32(0.0f, 0.0f, 0.0f, 10.0f);
  lm2_sphere_f32 small = lm2_sphere_make_coords_f32(0.0f, 0.0f, 0.0f, 5.0f);

  EXPECT_TRUE(lm2_sphere_contains_sphere_f32(big, small));

  lm2_sphere_f32 partial = lm2_sphere_make_coords_f32(8.0f, 0.0f, 0.0f, 5.0f);
  EXPECT_FALSE(lm2_sphere_contains_sphere_f32(big, partial));
}

// =============================================================================
// Transformation Tests (f64)
// =============================================================================

TEST_F(SphereTest, Translate_F64) {
  lm2_sphere_f64 sphere = lm2_sphere_make_coords_f64(5.0, 5.0, 5.0, 3.0);
  lm2_v3_f64 offset = lm2_v3_make_f64(10.0, 20.0, 30.0);

  lm2_sphere_f64 translated = lm2_sphere_translate_f64(sphere, offset);

  EXPECT_DOUBLE_EQ(translated.center.x, 15.0);
  EXPECT_DOUBLE_EQ(translated.center.y, 25.0);
  EXPECT_DOUBLE_EQ(translated.center.z, 35.0);
  EXPECT_DOUBLE_EQ(translated.radius, 3.0);
}

TEST_F(SphereTest, Scale_F64) {
  lm2_sphere_f64 sphere = lm2_sphere_make_coords_f64(0.0, 0.0, 0.0, 5.0);

  lm2_sphere_f64 scaled = lm2_sphere_scale_f64(sphere, 3.0);

  EXPECT_DOUBLE_EQ(scaled.center.x, 0.0);
  EXPECT_DOUBLE_EQ(scaled.center.y, 0.0);
  EXPECT_DOUBLE_EQ(scaled.center.z, 0.0);
  EXPECT_DOUBLE_EQ(scaled.radius, 15.0);
}

// =============================================================================
// Transformation Tests (f32)
// =============================================================================

TEST_F(SphereTest, Translate_F32) {
  lm2_sphere_f32 sphere = lm2_sphere_make_coords_f32(5.0f, 5.0f, 5.0f, 3.0f);
  lm2_v3_f32 offset = lm2_v3_make_f32(10.0f, 20.0f, 30.0f);

  lm2_sphere_f32 translated = lm2_sphere_translate_f32(sphere, offset);

  EXPECT_FLOAT_EQ(translated.center.x, 15.0f);
  EXPECT_FLOAT_EQ(translated.center.y, 25.0f);
  EXPECT_FLOAT_EQ(translated.center.z, 35.0f);
  EXPECT_FLOAT_EQ(translated.radius, 3.0f);
}

TEST_F(SphereTest, Scale_F32) {
  lm2_sphere_f32 sphere = lm2_sphere_make_coords_f32(0.0f, 0.0f, 0.0f, 5.0f);

  lm2_sphere_f32 scaled = lm2_sphere_scale_f32(sphere, 3.0f);

  EXPECT_FLOAT_EQ(scaled.radius, 15.0f);
}

// =============================================================================
// Edge Cases
// =============================================================================

TEST_F(SphereTest, ZeroRadius_F64) {
  lm2_sphere_f64 sphere = lm2_sphere_make_coords_f64(5.0, 5.0, 5.0, 0.0);

  EXPECT_DOUBLE_EQ(lm2_sphere_volume_f64(sphere), 0.0);
  EXPECT_DOUBLE_EQ(lm2_sphere_surface_area_f64(sphere), 0.0);

  // Only the center point should be "inside"
  lm2_v3_f64 center = lm2_v3_make_f64(5.0, 5.0, 5.0);
  EXPECT_TRUE(lm2_sphere_contains_point_f64(sphere, center));

  lm2_v3_f64 nearby = lm2_v3_make_f64(5.1, 5.0, 5.0);
  EXPECT_FALSE(lm2_sphere_contains_point_f64(sphere, nearby));
}

TEST_F(SphereTest, NegativeScaling_F64) {
  lm2_sphere_f64 sphere = lm2_sphere_make_coords_f64(0.0, 0.0, 0.0, 5.0);

  // Negative scaling should result in a negative radius
  // (behavior depends on implementation - this documents expected behavior)
  lm2_sphere_f64 scaled = lm2_sphere_scale_f64(sphere, -2.0);
  EXPECT_DOUBLE_EQ(scaled.radius, -10.0);
}
