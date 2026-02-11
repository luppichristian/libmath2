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
#include "lm2/geometry3d/lm2_capsule3.h"

// Test fixture for Capsule3 tests
class Capsule3Test : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
  static constexpr double PI = 3.14159265358979323846;
};

// =============================================================================
// Construction Tests (f64)
// =============================================================================

TEST_F(Capsule3Test, Make_F64) {
  lm2_v3_f64 start = lm2_v3_make_f64(0.0, 0.0, 0.0);
  lm2_v3_f64 end = lm2_v3_make_f64(10.0, 0.0, 0.0);
  lm2_capsule3_f64 capsule = lm2_capsule3_make_f64(start, end, 2.0);

  EXPECT_DOUBLE_EQ(capsule.start.x, 0.0);
  EXPECT_DOUBLE_EQ(capsule.start.y, 0.0);
  EXPECT_DOUBLE_EQ(capsule.start.z, 0.0);
  EXPECT_DOUBLE_EQ(capsule.end.x, 10.0);
  EXPECT_DOUBLE_EQ(capsule.end.y, 0.0);
  EXPECT_DOUBLE_EQ(capsule.end.z, 0.0);
  EXPECT_DOUBLE_EQ(capsule.radius, 2.0);
}

TEST_F(Capsule3Test, MakeCoords_F64) {
  lm2_capsule3_f64 capsule = lm2_capsule3_make_coords_f64(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 1.5);

  EXPECT_DOUBLE_EQ(capsule.start.x, 1.0);
  EXPECT_DOUBLE_EQ(capsule.start.y, 2.0);
  EXPECT_DOUBLE_EQ(capsule.start.z, 3.0);
  EXPECT_DOUBLE_EQ(capsule.end.x, 4.0);
  EXPECT_DOUBLE_EQ(capsule.end.y, 5.0);
  EXPECT_DOUBLE_EQ(capsule.end.z, 6.0);
  EXPECT_DOUBLE_EQ(capsule.radius, 1.5);
}

TEST_F(Capsule3Test, FromCenter_F64) {
  lm2_v3_f64 center = lm2_v3_make_f64(5.0, 5.0, 5.0);
  lm2_v3_f64 direction = lm2_v3_make_f64(1.0, 0.0, 0.0);
  lm2_capsule3_f64 capsule = lm2_capsule3_from_center_f64(center, direction, 3.0, 2.0);

  EXPECT_NEAR(capsule.start.x, 2.0, EPSILON_F64);
  EXPECT_NEAR(capsule.start.y, 5.0, EPSILON_F64);
  EXPECT_NEAR(capsule.start.z, 5.0, EPSILON_F64);
  EXPECT_NEAR(capsule.end.x, 8.0, EPSILON_F64);
  EXPECT_NEAR(capsule.end.y, 5.0, EPSILON_F64);
  EXPECT_NEAR(capsule.end.z, 5.0, EPSILON_F64);
  EXPECT_DOUBLE_EQ(capsule.radius, 2.0);
}

// =============================================================================
// Construction Tests (f32)
// =============================================================================

TEST_F(Capsule3Test, Make_F32) {
  lm2_v3_f32 start = lm2_v3_make_f32(0.0f, 0.0f, 0.0f);
  lm2_v3_f32 end = lm2_v3_make_f32(10.0f, 0.0f, 0.0f);
  lm2_capsule3_f32 capsule = lm2_capsule3_make_f32(start, end, 2.0f);

  EXPECT_FLOAT_EQ(capsule.start.x, 0.0f);
  EXPECT_FLOAT_EQ(capsule.end.x, 10.0f);
  EXPECT_FLOAT_EQ(capsule.radius, 2.0f);
}

TEST_F(Capsule3Test, MakeCoords_F32) {
  lm2_capsule3_f32 capsule = lm2_capsule3_make_coords_f32(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 1.5f);

  EXPECT_FLOAT_EQ(capsule.start.x, 1.0f);
  EXPECT_FLOAT_EQ(capsule.end.z, 6.0f);
  EXPECT_FLOAT_EQ(capsule.radius, 1.5f);
}

TEST_F(Capsule3Test, FromCenter_F32) {
  lm2_v3_f32 center = lm2_v3_make_f32(5.0f, 5.0f, 5.0f);
  lm2_v3_f32 direction = lm2_v3_make_f32(1.0f, 0.0f, 0.0f);
  lm2_capsule3_f32 capsule = lm2_capsule3_from_center_f32(center, direction, 3.0f, 2.0f);

  EXPECT_NEAR(capsule.start.x, 2.0f, EPSILON_F32);
  EXPECT_NEAR(capsule.end.x, 8.0f, EPSILON_F32);
  EXPECT_FLOAT_EQ(capsule.radius, 2.0f);
}

// =============================================================================
// Properties Tests (f64)
// =============================================================================

TEST_F(Capsule3Test, Length_F64) {
  lm2_v3_f64 start = lm2_v3_make_f64(0.0, 0.0, 0.0);
  lm2_v3_f64 end = lm2_v3_make_f64(0.0, 0.0, 10.0);
  lm2_capsule3_f64 capsule = lm2_capsule3_make_f64(start, end, 2.0);

  double length = lm2_capsule3_length_f64(capsule);
  EXPECT_DOUBLE_EQ(length, 10.0);
}

TEST_F(Capsule3Test, TotalLength_F64) {
  lm2_v3_f64 start = lm2_v3_make_f64(0.0, 0.0, 0.0);
  lm2_v3_f64 end = lm2_v3_make_f64(0.0, 0.0, 10.0);
  lm2_capsule3_f64 capsule = lm2_capsule3_make_f64(start, end, 2.0);

  // Total length = line length + 2*radius = 10 + 4 = 14
  double totalLength = lm2_capsule3_total_length_f64(capsule);
  EXPECT_DOUBLE_EQ(totalLength, 14.0);
}

TEST_F(Capsule3Test, Volume_F64) {
  // Capsule with line length 10 and radius 2
  lm2_v3_f64 start = lm2_v3_make_f64(0.0, 0.0, 0.0);
  lm2_v3_f64 end = lm2_v3_make_f64(0.0, 0.0, 10.0);
  lm2_capsule3_f64 capsule = lm2_capsule3_make_f64(start, end, 2.0);

  // Volume = cylinder + 2 hemisphere caps
  // = π*r²*h + (4/3)*π*r³
  // = π*4*10 + (4/3)*π*8
  // = 40π + (32/3)π = (152/3)π
  double volume = lm2_capsule3_volume_f64(capsule);
  double expected = PI * 4.0 * 10.0 + (4.0 / 3.0) * PI * 8.0;
  EXPECT_NEAR(volume, expected, EPSILON_F64);
}

TEST_F(Capsule3Test, SurfaceArea_F64) {
  lm2_v3_f64 start = lm2_v3_make_f64(0.0, 0.0, 0.0);
  lm2_v3_f64 end = lm2_v3_make_f64(0.0, 0.0, 10.0);
  lm2_capsule3_f64 capsule = lm2_capsule3_make_f64(start, end, 2.0);

  // Surface area = cylinder lateral + sphere
  // = 2πrh + 4πr²
  // = 2π*2*10 + 4π*4
  // = 40π + 16π = 56π
  double area = lm2_capsule3_surface_area_f64(capsule);
  double expected = 2.0 * PI * 2.0 * 10.0 + 4.0 * PI * 4.0;
  EXPECT_NEAR(area, expected, EPSILON_F64);
}

TEST_F(Capsule3Test, Center_F64) {
  lm2_v3_f64 start = lm2_v3_make_f64(0.0, 0.0, 0.0);
  lm2_v3_f64 end = lm2_v3_make_f64(10.0, 0.0, 0.0);
  lm2_capsule3_f64 capsule = lm2_capsule3_make_f64(start, end, 2.0);

  lm2_v3_f64 center = lm2_capsule3_center_f64(capsule);
  EXPECT_DOUBLE_EQ(center.x, 5.0);
  EXPECT_DOUBLE_EQ(center.y, 0.0);
  EXPECT_DOUBLE_EQ(center.z, 0.0);
}

// =============================================================================
// Properties Tests (f32)
// =============================================================================

TEST_F(Capsule3Test, Length_F32) {
  lm2_v3_f32 start = lm2_v3_make_f32(0.0f, 0.0f, 0.0f);
  lm2_v3_f32 end = lm2_v3_make_f32(0.0f, 0.0f, 10.0f);
  lm2_capsule3_f32 capsule = lm2_capsule3_make_f32(start, end, 2.0f);

  float length = lm2_capsule3_length_f32(capsule);
  EXPECT_FLOAT_EQ(length, 10.0f);
}

TEST_F(Capsule3Test, TotalLength_F32) {
  lm2_v3_f32 start = lm2_v3_make_f32(0.0f, 0.0f, 0.0f);
  lm2_v3_f32 end = lm2_v3_make_f32(0.0f, 0.0f, 10.0f);
  lm2_capsule3_f32 capsule = lm2_capsule3_make_f32(start, end, 2.0f);

  float totalLength = lm2_capsule3_total_length_f32(capsule);
  EXPECT_FLOAT_EQ(totalLength, 14.0f);
}

TEST_F(Capsule3Test, Volume_F32) {
  lm2_v3_f32 start = lm2_v3_make_f32(0.0f, 0.0f, 0.0f);
  lm2_v3_f32 end = lm2_v3_make_f32(0.0f, 0.0f, 10.0f);
  lm2_capsule3_f32 capsule = lm2_capsule3_make_f32(start, end, 2.0f);

  float volume = lm2_capsule3_volume_f32(capsule);
  float expected = static_cast<float>(PI) * 4.0f * 10.0f + (4.0f / 3.0f) * static_cast<float>(PI) * 8.0f;
  EXPECT_NEAR(volume, expected, EPSILON_F32);
}

TEST_F(Capsule3Test, SurfaceArea_F32) {
  lm2_v3_f32 start = lm2_v3_make_f32(0.0f, 0.0f, 0.0f);
  lm2_v3_f32 end = lm2_v3_make_f32(0.0f, 0.0f, 10.0f);
  lm2_capsule3_f32 capsule = lm2_capsule3_make_f32(start, end, 2.0f);

  float area = lm2_capsule3_surface_area_f32(capsule);
  float expected = 2.0f * static_cast<float>(PI) * 2.0f * 10.0f + 4.0f * static_cast<float>(PI) * 4.0f;
  EXPECT_NEAR(area, expected, EPSILON_F32);
}

TEST_F(Capsule3Test, Center_F32) {
  lm2_v3_f32 start = lm2_v3_make_f32(0.0f, 0.0f, 0.0f);
  lm2_v3_f32 end = lm2_v3_make_f32(10.0f, 0.0f, 0.0f);
  lm2_capsule3_f32 capsule = lm2_capsule3_make_f32(start, end, 2.0f);

  lm2_v3_f32 center = lm2_capsule3_center_f32(capsule);
  EXPECT_FLOAT_EQ(center.x, 5.0f);
}

// =============================================================================
// Containment Tests (f64)
// =============================================================================

TEST_F(Capsule3Test, ContainsPoint_F64) {
  lm2_v3_f64 start = lm2_v3_make_f64(0.0, 0.0, 0.0);
  lm2_v3_f64 end = lm2_v3_make_f64(10.0, 0.0, 0.0);
  lm2_capsule3_f64 capsule = lm2_capsule3_make_f64(start, end, 2.0);

  // Point inside (on the line segment)
  lm2_v3_f64 inside = lm2_v3_make_f64(5.0, 0.0, 0.0);
  EXPECT_TRUE(lm2_capsule3_contains_point_f64(capsule, inside));

  // Point inside (within radius)
  lm2_v3_f64 withinRadius = lm2_v3_make_f64(5.0, 1.5, 0.0);
  EXPECT_TRUE(lm2_capsule3_contains_point_f64(capsule, withinRadius));

  // Point outside
  lm2_v3_f64 outside = lm2_v3_make_f64(5.0, 5.0, 0.0);
  EXPECT_FALSE(lm2_capsule3_contains_point_f64(capsule, outside));

  // Point near the end cap
  lm2_v3_f64 nearCap = lm2_v3_make_f64(11.5, 0.0, 0.0);
  EXPECT_TRUE(lm2_capsule3_contains_point_f64(capsule, nearCap));
}

TEST_F(Capsule3Test, CapsulesOverlap_F64) {
  lm2_capsule3_f64 a = lm2_capsule3_make_f64(
      lm2_v3_make_f64(0.0, 0.0, 0.0),
      lm2_v3_make_f64(10.0, 0.0, 0.0),
      2.0);

  // Overlapping capsule
  lm2_capsule3_f64 b = lm2_capsule3_make_f64(
      lm2_v3_make_f64(8.0, 0.0, 0.0),
      lm2_v3_make_f64(18.0, 0.0, 0.0),
      2.0);
  EXPECT_TRUE(lm2_capsules3_overlap_f64(a, b));

  // Non-overlapping capsule
  lm2_capsule3_f64 c = lm2_capsule3_make_f64(
      lm2_v3_make_f64(20.0, 0.0, 0.0),
      lm2_v3_make_f64(30.0, 0.0, 0.0),
      2.0);
  EXPECT_FALSE(lm2_capsules3_overlap_f64(a, c));
}

// =============================================================================
// Containment Tests (f32)
// =============================================================================

TEST_F(Capsule3Test, ContainsPoint_F32) {
  lm2_v3_f32 start = lm2_v3_make_f32(0.0f, 0.0f, 0.0f);
  lm2_v3_f32 end = lm2_v3_make_f32(10.0f, 0.0f, 0.0f);
  lm2_capsule3_f32 capsule = lm2_capsule3_make_f32(start, end, 2.0f);

  lm2_v3_f32 inside = lm2_v3_make_f32(5.0f, 0.0f, 0.0f);
  EXPECT_TRUE(lm2_capsule3_contains_point_f32(capsule, inside));

  lm2_v3_f32 outside = lm2_v3_make_f32(5.0f, 5.0f, 0.0f);
  EXPECT_FALSE(lm2_capsule3_contains_point_f32(capsule, outside));
}

TEST_F(Capsule3Test, CapsulesOverlap_F32) {
  lm2_capsule3_f32 a = lm2_capsule3_make_f32(
      lm2_v3_make_f32(0.0f, 0.0f, 0.0f),
      lm2_v3_make_f32(10.0f, 0.0f, 0.0f),
      2.0f);

  lm2_capsule3_f32 b = lm2_capsule3_make_f32(
      lm2_v3_make_f32(8.0f, 0.0f, 0.0f),
      lm2_v3_make_f32(18.0f, 0.0f, 0.0f),
      2.0f);
  EXPECT_TRUE(lm2_capsules3_overlap_f32(a, b));
}

// =============================================================================
// Transformation Tests (f64)
// =============================================================================

TEST_F(Capsule3Test, Translate_F64) {
  lm2_capsule3_f64 capsule = lm2_capsule3_make_f64(
      lm2_v3_make_f64(0.0, 0.0, 0.0),
      lm2_v3_make_f64(10.0, 0.0, 0.0),
      2.0);

  lm2_v3_f64 offset = lm2_v3_make_f64(5.0, 5.0, 5.0);
  lm2_capsule3_f64 translated = lm2_capsule3_translate_f64(capsule, offset);

  EXPECT_DOUBLE_EQ(translated.start.x, 5.0);
  EXPECT_DOUBLE_EQ(translated.start.y, 5.0);
  EXPECT_DOUBLE_EQ(translated.start.z, 5.0);
  EXPECT_DOUBLE_EQ(translated.end.x, 15.0);
  EXPECT_DOUBLE_EQ(translated.end.y, 5.0);
  EXPECT_DOUBLE_EQ(translated.end.z, 5.0);
  EXPECT_DOUBLE_EQ(translated.radius, 2.0);
}

TEST_F(Capsule3Test, ScaleRadius_F64) {
  lm2_capsule3_f64 capsule = lm2_capsule3_make_f64(
      lm2_v3_make_f64(0.0, 0.0, 0.0),
      lm2_v3_make_f64(10.0, 0.0, 0.0),
      2.0);

  lm2_capsule3_f64 scaled = lm2_capsule3_scale_radius_f64(capsule, 3.0);

  // Endpoints should remain the same
  EXPECT_DOUBLE_EQ(scaled.start.x, 0.0);
  EXPECT_DOUBLE_EQ(scaled.end.x, 10.0);

  // Radius should be scaled
  EXPECT_DOUBLE_EQ(scaled.radius, 6.0);
}

// =============================================================================
// Transformation Tests (f32)
// =============================================================================

TEST_F(Capsule3Test, Translate_F32) {
  lm2_capsule3_f32 capsule = lm2_capsule3_make_f32(
      lm2_v3_make_f32(0.0f, 0.0f, 0.0f),
      lm2_v3_make_f32(10.0f, 0.0f, 0.0f),
      2.0f);

  lm2_v3_f32 offset = lm2_v3_make_f32(5.0f, 5.0f, 5.0f);
  lm2_capsule3_f32 translated = lm2_capsule3_translate_f32(capsule, offset);

  EXPECT_FLOAT_EQ(translated.start.x, 5.0f);
  EXPECT_FLOAT_EQ(translated.end.x, 15.0f);
  EXPECT_FLOAT_EQ(translated.radius, 2.0f);
}

TEST_F(Capsule3Test, ScaleRadius_F32) {
  lm2_capsule3_f32 capsule = lm2_capsule3_make_f32(
      lm2_v3_make_f32(0.0f, 0.0f, 0.0f),
      lm2_v3_make_f32(10.0f, 0.0f, 0.0f),
      2.0f);

  lm2_capsule3_f32 scaled = lm2_capsule3_scale_radius_f32(capsule, 3.0f);

  EXPECT_FLOAT_EQ(scaled.radius, 6.0f);
}

// =============================================================================
// Edge Cases
// =============================================================================

TEST_F(Capsule3Test, ZeroLengthCapsule_F64) {
  // A capsule with zero length is essentially a sphere
  lm2_v3_f64 point = lm2_v3_make_f64(5.0, 5.0, 5.0);
  lm2_capsule3_f64 capsule = lm2_capsule3_make_f64(point, point, 2.0);

  EXPECT_DOUBLE_EQ(lm2_capsule3_length_f64(capsule), 0.0);
  EXPECT_DOUBLE_EQ(lm2_capsule3_total_length_f64(capsule), 4.0);

  // Should behave like a sphere
  lm2_v3_f64 nearPoint = lm2_v3_make_f64(6.5, 5.0, 5.0);
  EXPECT_TRUE(lm2_capsule3_contains_point_f64(capsule, nearPoint));
}
