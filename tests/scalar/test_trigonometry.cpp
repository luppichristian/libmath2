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
#include "lm2/lm2_constants.h"
#include "lm2/scalar/lm2_trigonometry.h"

// Test fixture for trigonometry tests
class TrigonometryTest : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-6f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Cos Tests
// =============================================================================

TEST_F(TrigonometryTest, Cos_F64) {
  EXPECT_NEAR(lm2_cos_f64(0.0), 1.0, EPSILON_F64);
  EXPECT_NEAR(lm2_cos_f64(LM2_PI_F64 / 2.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_cos_f64(LM2_PI_F64), -1.0, EPSILON_F64);
  EXPECT_NEAR(lm2_cos_f64(LM2_PI_F64 * 2.0), 1.0, EPSILON_F64);
  EXPECT_NEAR(lm2_cos_f64(LM2_PI_F64 / 4.0), 0.70710678118, EPSILON_F64);
}

TEST_F(TrigonometryTest, Cos_F32) {
  EXPECT_NEAR(lm2_cos_f32(0.0f), 1.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_cos_f32(LM2_PI_F32 / 2.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_cos_f32(LM2_PI_F32), -1.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_cos_f32(LM2_PI_F32 * 2.0f), 1.0f, EPSILON_F32);
}

// =============================================================================
// Sin Tests
// =============================================================================

TEST_F(TrigonometryTest, Sin_F64) {
  EXPECT_NEAR(lm2_sin_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_sin_f64(LM2_PI_F64 / 2.0), 1.0, EPSILON_F64);
  EXPECT_NEAR(lm2_sin_f64(LM2_PI_F64), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_sin_f64(LM2_PI_F64 * 3.0 / 2.0), -1.0, EPSILON_F64);
  EXPECT_NEAR(lm2_sin_f64(LM2_PI_F64 / 4.0), 0.70710678118, EPSILON_F64);
}

TEST_F(TrigonometryTest, Sin_F32) {
  EXPECT_NEAR(lm2_sin_f32(0.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_sin_f32(LM2_PI_F32 / 2.0f), 1.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_sin_f32(LM2_PI_F32), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_sin_f32(LM2_PI_F32 * 3.0f / 2.0f), -1.0f, EPSILON_F32);
}

// =============================================================================
// Tan Tests
// =============================================================================

TEST_F(TrigonometryTest, Tan_F64) {
  EXPECT_NEAR(lm2_tan_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_tan_f64(LM2_PI_F64 / 4.0), 1.0, EPSILON_F64);
  EXPECT_NEAR(lm2_tan_f64(-LM2_PI_F64 / 4.0), -1.0, EPSILON_F64);
  EXPECT_NEAR(lm2_tan_f64(LM2_PI_F64), 0.0, EPSILON_F64);
}

TEST_F(TrigonometryTest, Tan_F32) {
  EXPECT_NEAR(lm2_tan_f32(0.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_tan_f32(LM2_PI_F32 / 4.0f), 1.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_tan_f32(-LM2_PI_F32 / 4.0f), -1.0f, EPSILON_F32);
}

// =============================================================================
// Acos Tests
// =============================================================================

TEST_F(TrigonometryTest, Acos_F64) {
  EXPECT_NEAR(lm2_acos_f64(1.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_acos_f64(0.0), LM2_PI_F64 / 2.0, EPSILON_F64);
  EXPECT_NEAR(lm2_acos_f64(-1.0), LM2_PI_F64, EPSILON_F64);
  EXPECT_NEAR(lm2_acos_f64(0.5), LM2_PI_F64 / 3.0, EPSILON_F64);
}

TEST_F(TrigonometryTest, Acos_F32) {
  EXPECT_NEAR(lm2_acos_f32(1.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_acos_f32(0.0f), LM2_PI_F32 / 2.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_acos_f32(-1.0f), LM2_PI_F32, EPSILON_F32);
}

// =============================================================================
// Asin Tests
// =============================================================================

TEST_F(TrigonometryTest, Asin_F64) {
  EXPECT_NEAR(lm2_asin_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_asin_f64(1.0), LM2_PI_F64 / 2.0, EPSILON_F64);
  EXPECT_NEAR(lm2_asin_f64(-1.0), -LM2_PI_F64 / 2.0, EPSILON_F64);
  EXPECT_NEAR(lm2_asin_f64(0.5), LM2_PI_F64 / 6.0, EPSILON_F64);
}

TEST_F(TrigonometryTest, Asin_F32) {
  EXPECT_NEAR(lm2_asin_f32(0.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_asin_f32(1.0f), LM2_PI_F32 / 2.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_asin_f32(-1.0f), -LM2_PI_F32 / 2.0f, EPSILON_F32);
}

// =============================================================================
// Atan Tests
// =============================================================================

TEST_F(TrigonometryTest, Atan_F64) {
  EXPECT_NEAR(lm2_atan_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_atan_f64(1.0), LM2_PI_F64 / 4.0, EPSILON_F64);
  EXPECT_NEAR(lm2_atan_f64(-1.0), -LM2_PI_F64 / 4.0, EPSILON_F64);
}

TEST_F(TrigonometryTest, Atan_F32) {
  EXPECT_NEAR(lm2_atan_f32(0.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_atan_f32(1.0f), LM2_PI_F32 / 4.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_atan_f32(-1.0f), -LM2_PI_F32 / 4.0f, EPSILON_F32);
}

// =============================================================================
// Atan2 Tests
// =============================================================================

TEST_F(TrigonometryTest, Atan2_F64) {
  EXPECT_NEAR(lm2_atan2_f64(0.0, 1.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_atan2_f64(1.0, 0.0), LM2_PI_F64 / 2.0, EPSILON_F64);
  EXPECT_NEAR(lm2_atan2_f64(0.0, -1.0), LM2_PI_F64, EPSILON_F64);
  EXPECT_NEAR(lm2_atan2_f64(-1.0, 0.0), -LM2_PI_F64 / 2.0, EPSILON_F64);
  EXPECT_NEAR(lm2_atan2_f64(1.0, 1.0), LM2_PI_F64 / 4.0, EPSILON_F64);
}

TEST_F(TrigonometryTest, Atan2_F32) {
  EXPECT_NEAR(lm2_atan2_f32(0.0f, 1.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_atan2_f32(1.0f, 0.0f), LM2_PI_F32 / 2.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_atan2_f32(0.0f, -1.0f), LM2_PI_F32, EPSILON_F32);
  EXPECT_NEAR(lm2_atan2_f32(1.0f, 1.0f), LM2_PI_F32 / 4.0f, EPSILON_F32);
}

// =============================================================================
// Degree/Radian Conversion Tests
// =============================================================================

TEST_F(TrigonometryTest, DegToRad_F64) {
  EXPECT_NEAR(lm2_deg_to_rad_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_deg_to_rad_f64(90.0), LM2_PI_F64 / 2.0, EPSILON_F64);
  EXPECT_NEAR(lm2_deg_to_rad_f64(180.0), LM2_PI_F64, EPSILON_F64);
  EXPECT_NEAR(lm2_deg_to_rad_f64(360.0), LM2_PI_F64 * 2.0, EPSILON_F64);
  EXPECT_NEAR(lm2_deg_to_rad_f64(-90.0), -LM2_PI_F64 / 2.0, EPSILON_F64);
}

TEST_F(TrigonometryTest, DegToRad_F32) {
  EXPECT_NEAR(lm2_deg_to_rad_f32(0.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_deg_to_rad_f32(90.0f), LM2_PI_F32 / 2.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_deg_to_rad_f32(180.0f), LM2_PI_F32, EPSILON_F32);
  EXPECT_NEAR(lm2_deg_to_rad_f32(360.0f), LM2_PI_F32 * 2.0f, EPSILON_F32);
}

TEST_F(TrigonometryTest, RadToDeg_F64) {
  EXPECT_NEAR(lm2_rad_to_deg_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_rad_to_deg_f64(LM2_PI_F64 / 2.0), 90.0, EPSILON_F64);
  EXPECT_NEAR(lm2_rad_to_deg_f64(LM2_PI_F64), 180.0, EPSILON_F64);
  EXPECT_NEAR(lm2_rad_to_deg_f64(LM2_PI_F64 * 2.0), 360.0, EPSILON_F64);
  EXPECT_NEAR(lm2_rad_to_deg_f64(-LM2_PI_F64 / 2.0), -90.0, EPSILON_F64);
}

TEST_F(TrigonometryTest, RadToDeg_F32) {
  EXPECT_NEAR(lm2_rad_to_deg_f32(0.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_rad_to_deg_f32(LM2_PI_F32 / 2.0f), 90.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_rad_to_deg_f32(LM2_PI_F32), 180.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_rad_to_deg_f32(LM2_PI_F32 * 2.0f), 360.0f, EPSILON_F32);
}

// =============================================================================
// Angle Wrapping Tests (Radians)
// =============================================================================

TEST_F(TrigonometryTest, WrapRad_F64) {
  EXPECT_NEAR(lm2_wrap_rad_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_wrap_rad_f64(LM2_PI_F64), -LM2_PI_F64, EPSILON_F64);  // Wraps to [-π, π]
  EXPECT_NEAR(lm2_wrap_rad_f64(LM2_PI_F64 * 2.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_wrap_rad_f64(LM2_PI_F64 * 3.0), -LM2_PI_F64, EPSILON_F64);
  EXPECT_NEAR(lm2_wrap_rad_f64(-LM2_PI_F64), -LM2_PI_F64, EPSILON_F64);
  EXPECT_NEAR(lm2_wrap_rad_f64(LM2_PI_F64 / 2.0), LM2_PI_F64 / 2.0, EPSILON_F64);
}

TEST_F(TrigonometryTest, WrapRad_F32) {
  EXPECT_NEAR(lm2_wrap_rad_f32(0.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_wrap_rad_f32(LM2_PI_F32), -LM2_PI_F32, EPSILON_F32);  // Wraps to [-π, π]
  EXPECT_NEAR(lm2_wrap_rad_f32(LM2_PI_F32 * 2.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_wrap_rad_f32(LM2_PI_F32 * 3.0f), -LM2_PI_F32, EPSILON_F32);
}

// =============================================================================
// Shortest Angle Tests (Radians)
// =============================================================================

TEST_F(TrigonometryTest, ShortestRad_F64) {
  EXPECT_NEAR(lm2_shortest_rad_f64(0.0, LM2_PI_F64), -LM2_PI_F64, EPSILON_F64);  // π wraps to -π
  EXPECT_NEAR(lm2_shortest_rad_f64(0.0, LM2_PI_F64 * 2.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_shortest_rad_f64(0.0, LM2_PI_F64 / 2.0), LM2_PI_F64 / 2.0, EPSILON_F64);

  // Test wrapping: going from 0 to 3*PI/2 is shorter going backwards (-PI/2)
  double result = lm2_shortest_rad_f64(0.0, LM2_PI_F64 * 3.0 / 2.0);
  EXPECT_NEAR(result, -LM2_PI_F64 / 2.0, EPSILON_F64);
}

TEST_F(TrigonometryTest, ShortestRad_F32) {
  EXPECT_NEAR(lm2_shortest_rad_f32(0.0f, LM2_PI_F32), -LM2_PI_F32, EPSILON_F32);  // π wraps to -π
  EXPECT_NEAR(lm2_shortest_rad_f32(0.0f, LM2_PI_F32 * 2.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_shortest_rad_f32(0.0f, LM2_PI_F32 / 2.0f), LM2_PI_F32 / 2.0f, EPSILON_F32);
}

// =============================================================================
// Lerp Angle Tests (Radians)
// =============================================================================

TEST_F(TrigonometryTest, LerpRad_F64) {
  EXPECT_NEAR(lm2_lerp_rad_f64(0.0, 0.0, LM2_PI_F64), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_lerp_rad_f64(0.0, 1.0, LM2_PI_F64), -LM2_PI_F64, EPSILON_F64);        // Uses shortest path
  EXPECT_NEAR(lm2_lerp_rad_f64(0.0, 0.5, LM2_PI_F64), -LM2_PI_F64 / 2.0, EPSILON_F64);  // Halfway on shortest path
}

TEST_F(TrigonometryTest, LerpRad_F32) {
  EXPECT_NEAR(lm2_lerp_rad_f32(0.0f, 0.0f, LM2_PI_F32), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_lerp_rad_f32(0.0f, 1.0f, LM2_PI_F32), -LM2_PI_F32, EPSILON_F32);         // Uses shortest path
  EXPECT_NEAR(lm2_lerp_rad_f32(0.0f, 0.5f, LM2_PI_F32), -LM2_PI_F32 / 2.0f, EPSILON_F32);  // Halfway on shortest path
}

// =============================================================================
// Angle Wrapping Tests (Degrees)
// =============================================================================

TEST_F(TrigonometryTest, WrapDeg_F64) {
  EXPECT_NEAR(lm2_wrap_deg_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_wrap_deg_f64(180.0), -180.0, EPSILON_F64);  // Wraps to [-180, 180]
  EXPECT_NEAR(lm2_wrap_deg_f64(360.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_wrap_deg_f64(540.0), -180.0, EPSILON_F64);
  EXPECT_NEAR(lm2_wrap_deg_f64(-180.0), -180.0, EPSILON_F64);
  EXPECT_NEAR(lm2_wrap_deg_f64(90.0), 90.0, EPSILON_F64);
}

TEST_F(TrigonometryTest, WrapDeg_F32) {
  EXPECT_NEAR(lm2_wrap_deg_f32(0.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_wrap_deg_f32(180.0f), -180.0f, EPSILON_F32);  // Wraps to [-180, 180]
  EXPECT_NEAR(lm2_wrap_deg_f32(360.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_wrap_deg_f32(540.0f), -180.0f, EPSILON_F32);
}

// =============================================================================
// Shortest Angle Tests (Degrees)
// =============================================================================

TEST_F(TrigonometryTest, ShortestDeg_F64) {
  EXPECT_NEAR(lm2_shortest_deg_f64(0.0, 180.0), -180.0, EPSILON_F64);  // 180 wraps to -180
  EXPECT_NEAR(lm2_shortest_deg_f64(0.0, 360.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_shortest_deg_f64(0.0, 90.0), 90.0, EPSILON_F64);

  // Test wrapping: going from 0 to 270 is shorter going backwards (-90)
  double result = lm2_shortest_deg_f64(0.0, 270.0);
  EXPECT_NEAR(result, -90.0, EPSILON_F64);
}

TEST_F(TrigonometryTest, ShortestDeg_F32) {
  EXPECT_NEAR(lm2_shortest_deg_f32(0.0f, 180.0f), -180.0f, EPSILON_F32);  // 180 wraps to -180
  EXPECT_NEAR(lm2_shortest_deg_f32(0.0f, 360.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_shortest_deg_f32(0.0f, 90.0f), 90.0f, EPSILON_F32);
}

// =============================================================================
// Lerp Angle Tests (Degrees)
// =============================================================================

TEST_F(TrigonometryTest, LerpDeg_F64) {
  EXPECT_NEAR(lm2_lerp_deg_f64(0.0, 0.0, 180.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_lerp_deg_f64(0.0, 1.0, 180.0), -180.0, EPSILON_F64);  // Uses shortest path
  EXPECT_NEAR(lm2_lerp_deg_f64(0.0, 0.5, 180.0), -90.0, EPSILON_F64);   // Halfway on shortest path
}

TEST_F(TrigonometryTest, LerpDeg_F32) {
  EXPECT_NEAR(lm2_lerp_deg_f32(0.0f, 0.0f, 180.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_lerp_deg_f32(0.0f, 1.0f, 180.0f), -180.0f, EPSILON_F32);  // Uses shortest path
  EXPECT_NEAR(lm2_lerp_deg_f32(0.0f, 0.5f, 180.0f), -90.0f, EPSILON_F32);   // Halfway on shortest path
}
