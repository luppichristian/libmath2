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
#include "lm2/misc/lm2_bezier_curves.h"

// Test fixture for Bezier curves tests
class BezierCurvesTest : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Linear Bezier Tests - 2D
// =============================================================================

TEST_F(BezierCurvesTest, LinearBezier2_F64_AtT0) {
  lm2_v2_f64 p0 = {0.0, 0.0};
  lm2_v2_f64 p1 = {10.0, 10.0};
  lm2_v2_f64 result = lm2_bezier_linear2_f64(p0, p1, 0.0);
  
  EXPECT_NEAR(result.x, p0.x, EPSILON_F64);
  EXPECT_NEAR(result.y, p0.y, EPSILON_F64);
}

TEST_F(BezierCurvesTest, LinearBezier2_F64_AtT1) {
  lm2_v2_f64 p0 = {0.0, 0.0};
  lm2_v2_f64 p1 = {10.0, 10.0};
  lm2_v2_f64 result = lm2_bezier_linear2_f64(p0, p1, 1.0);
  
  EXPECT_NEAR(result.x, p1.x, EPSILON_F64);
  EXPECT_NEAR(result.y, p1.y, EPSILON_F64);
}

TEST_F(BezierCurvesTest, LinearBezier2_F64_AtT05) {
  lm2_v2_f64 p0 = {0.0, 0.0};
  lm2_v2_f64 p1 = {10.0, 10.0};
  lm2_v2_f64 result = lm2_bezier_linear2_f64(p0, p1, 0.5);
  
  EXPECT_NEAR(result.x, 5.0, EPSILON_F64);
  EXPECT_NEAR(result.y, 5.0, EPSILON_F64);
}

TEST_F(BezierCurvesTest, LinearBezier2_F32) {
  lm2_v2_f32 p0 = {0.0f, 0.0f};
  lm2_v2_f32 p1 = {10.0f, 5.0f};
  lm2_v2_f32 result = lm2_bezier_linear2_f32(p0, p1, 0.25f);
  
  EXPECT_NEAR(result.x, 2.5f, EPSILON_F32);
  EXPECT_NEAR(result.y, 1.25f, EPSILON_F32);
}

// =============================================================================
// Linear Bezier Tests - 3D
// =============================================================================

TEST_F(BezierCurvesTest, LinearBezier3_F64) {
  lm2_v3_f64 p0 = {0.0, 0.0, 0.0};
  lm2_v3_f64 p1 = {10.0, 10.0, 10.0};
  lm2_v3_f64 result = lm2_bezier_linear3_f64(p0, p1, 0.5);
  
  EXPECT_NEAR(result.x, 5.0, EPSILON_F64);
  EXPECT_NEAR(result.y, 5.0, EPSILON_F64);
  EXPECT_NEAR(result.z, 5.0, EPSILON_F64);
}

TEST_F(BezierCurvesTest, LinearBezier3_F32) {
  lm2_v3_f32 p0 = {1.0f, 2.0f, 3.0f};
  lm2_v3_f32 p1 = {5.0f, 6.0f, 7.0f};
  lm2_v3_f32 result = lm2_bezier_linear3_f32(p0, p1, 0.5f);
  
  EXPECT_NEAR(result.x, 3.0f, EPSILON_F32);
  EXPECT_NEAR(result.y, 4.0f, EPSILON_F32);
  EXPECT_NEAR(result.z, 5.0f, EPSILON_F32);
}

// =============================================================================
// Linear Bezier Tests - 4D
// =============================================================================

TEST_F(BezierCurvesTest, LinearBezier4_F64) {
  lm2_v4_f64 p0 = {0.0, 0.0, 0.0, 0.0};
  lm2_v4_f64 p1 = {10.0, 10.0, 10.0, 10.0};
  lm2_v4_f64 result = lm2_bezier_linear4_f64(p0, p1, 0.3);
  
  EXPECT_NEAR(result.x, 3.0, EPSILON_F64);
  EXPECT_NEAR(result.y, 3.0, EPSILON_F64);
  EXPECT_NEAR(result.z, 3.0, EPSILON_F64);
  EXPECT_NEAR(result.w, 3.0, EPSILON_F64);
}

TEST_F(BezierCurvesTest, LinearBezier4_F32) {
  lm2_v4_f32 p0 = {2.0f, 4.0f, 6.0f, 8.0f};
  lm2_v4_f32 p1 = {12.0f, 14.0f, 16.0f, 18.0f};
  lm2_v4_f32 result = lm2_bezier_linear4_f32(p0, p1, 0.5f);
  
  EXPECT_NEAR(result.x, 7.0f, EPSILON_F32);
  EXPECT_NEAR(result.y, 9.0f, EPSILON_F32);
  EXPECT_NEAR(result.z, 11.0f, EPSILON_F32);
  EXPECT_NEAR(result.w, 13.0f, EPSILON_F32);
}

// =============================================================================
// Quadratic Bezier Tests - 2D
// =============================================================================

TEST_F(BezierCurvesTest, QuadraticBezier2_F64_AtT0) {
  lm2_v2_f64 p0 = {0.0, 0.0};
  lm2_v2_f64 p1 = {5.0, 10.0};
  lm2_v2_f64 p2 = {10.0, 0.0};
  lm2_v2_f64 result = lm2_bezier_quadratic2_f64(p0, p1, p2, 0.0);
  
  EXPECT_NEAR(result.x, p0.x, EPSILON_F64);
  EXPECT_NEAR(result.y, p0.y, EPSILON_F64);
}

TEST_F(BezierCurvesTest, QuadraticBezier2_F64_AtT1) {
  lm2_v2_f64 p0 = {0.0, 0.0};
  lm2_v2_f64 p1 = {5.0, 10.0};
  lm2_v2_f64 p2 = {10.0, 0.0};
  lm2_v2_f64 result = lm2_bezier_quadratic2_f64(p0, p1, p2, 1.0);
  
  EXPECT_NEAR(result.x, p2.x, EPSILON_F64);
  EXPECT_NEAR(result.y, p2.y, EPSILON_F64);
}

TEST_F(BezierCurvesTest, QuadraticBezier2_F64_AtT05) {
  lm2_v2_f64 p0 = {0.0, 0.0};
  lm2_v2_f64 p1 = {5.0, 10.0};
  lm2_v2_f64 p2 = {10.0, 0.0};
  lm2_v2_f64 result = lm2_bezier_quadratic2_f64(p0, p1, p2, 0.5);
  
  EXPECT_NEAR(result.x, 5.0, EPSILON_F64);
  EXPECT_NEAR(result.y, 5.0, EPSILON_F64);
}

TEST_F(BezierCurvesTest, QuadraticBezier2_F32) {
  lm2_v2_f32 p0 = {0.0f, 0.0f};
  lm2_v2_f32 p1 = {2.0f, 4.0f};
  lm2_v2_f32 p2 = {4.0f, 0.0f};
  lm2_v2_f32 result = lm2_bezier_quadratic2_f32(p0, p1, p2, 0.5f);
  
  EXPECT_NEAR(result.x, 2.0f, EPSILON_F32);
  EXPECT_NEAR(result.y, 2.0f, EPSILON_F32);
}

// =============================================================================
// Quadratic Bezier Tests - 3D
// =============================================================================

TEST_F(BezierCurvesTest, QuadraticBezier3_F64) {
  lm2_v3_f64 p0 = {0.0, 0.0, 0.0};
  lm2_v3_f64 p1 = {5.0, 10.0, 5.0};
  lm2_v3_f64 p2 = {10.0, 0.0, 10.0};
  lm2_v3_f64 result = lm2_bezier_quadratic3_f64(p0, p1, p2, 0.5);
  
  EXPECT_NEAR(result.x, 5.0, EPSILON_F64);
  EXPECT_NEAR(result.y, 5.0, EPSILON_F64);
  EXPECT_NEAR(result.z, 5.0, EPSILON_F64);
}

TEST_F(BezierCurvesTest, QuadraticBezier3_F32) {
  lm2_v3_f32 p0 = {0.0f, 0.0f, 0.0f};
  lm2_v3_f32 p1 = {2.0f, 4.0f, 2.0f};
  lm2_v3_f32 p2 = {4.0f, 0.0f, 4.0f};
  lm2_v3_f32 result = lm2_bezier_quadratic3_f32(p0, p1, p2, 0.5f);
  
  EXPECT_NEAR(result.x, 2.0f, EPSILON_F32);
  EXPECT_NEAR(result.y, 2.0f, EPSILON_F32);
  EXPECT_NEAR(result.z, 2.0f, EPSILON_F32);
}

// =============================================================================
// Quadratic Bezier Tests - 4D
// =============================================================================

TEST_F(BezierCurvesTest, QuadraticBezier4_F64) {
  lm2_v4_f64 p0 = {0.0, 0.0, 0.0, 0.0};
  lm2_v4_f64 p1 = {5.0, 10.0, 5.0, 10.0};
  lm2_v4_f64 p2 = {10.0, 0.0, 10.0, 0.0};
  lm2_v4_f64 result = lm2_bezier_quadratic4_f64(p0, p1, p2, 0.5);
  
  EXPECT_NEAR(result.x, 5.0, EPSILON_F64);
  EXPECT_NEAR(result.y, 5.0, EPSILON_F64);
  EXPECT_NEAR(result.z, 5.0, EPSILON_F64);
  EXPECT_NEAR(result.w, 5.0, EPSILON_F64);
}

TEST_F(BezierCurvesTest, QuadraticBezier4_F32) {
  lm2_v4_f32 p0 = {0.0f, 0.0f, 0.0f, 0.0f};
  lm2_v4_f32 p1 = {2.0f, 4.0f, 2.0f, 4.0f};
  lm2_v4_f32 p2 = {4.0f, 0.0f, 4.0f, 0.0f};
  lm2_v4_f32 result = lm2_bezier_quadratic4_f32(p0, p1, p2, 0.5f);
  
  EXPECT_NEAR(result.x, 2.0f, EPSILON_F32);
  EXPECT_NEAR(result.y, 2.0f, EPSILON_F32);
  EXPECT_NEAR(result.z, 2.0f, EPSILON_F32);
  EXPECT_NEAR(result.w, 2.0f, EPSILON_F32);
}

// =============================================================================
// Cubic Bezier Tests - 2D
// =============================================================================

TEST_F(BezierCurvesTest, CubicBezier2_F64_AtT0) {
  lm2_v2_f64 p0 = {0.0, 0.0};
  lm2_v2_f64 p1 = {1.0, 3.0};
  lm2_v2_f64 p2 = {2.0, 3.0};
  lm2_v2_f64 p3 = {3.0, 0.0};
  lm2_v2_f64 result = lm2_bezier_cubic2_f64(p0, p1, p2, p3, 0.0);
  
  EXPECT_NEAR(result.x, p0.x, EPSILON_F64);
  EXPECT_NEAR(result.y, p0.y, EPSILON_F64);
}

TEST_F(BezierCurvesTest, CubicBezier2_F64_AtT1) {
  lm2_v2_f64 p0 = {0.0, 0.0};
  lm2_v2_f64 p1 = {1.0, 3.0};
  lm2_v2_f64 p2 = {2.0, 3.0};
  lm2_v2_f64 p3 = {3.0, 0.0};
  lm2_v2_f64 result = lm2_bezier_cubic2_f64(p0, p1, p2, p3, 1.0);
  
  EXPECT_NEAR(result.x, p3.x, EPSILON_F64);
  EXPECT_NEAR(result.y, p3.y, EPSILON_F64);
}

TEST_F(BezierCurvesTest, CubicBezier2_F64_AtT05) {
  lm2_v2_f64 p0 = {0.0, 0.0};
  lm2_v2_f64 p1 = {0.0, 4.0};
  lm2_v2_f64 p2 = {4.0, 4.0};
  lm2_v2_f64 p3 = {4.0, 0.0};
  lm2_v2_f64 result = lm2_bezier_cubic2_f64(p0, p1, p2, p3, 0.5);
  
  EXPECT_NEAR(result.x, 2.0, EPSILON_F64);
  EXPECT_NEAR(result.y, 3.0, EPSILON_F64);
}

TEST_F(BezierCurvesTest, CubicBezier2_F32) {
  lm2_v2_f32 p0 = {0.0f, 0.0f};
  lm2_v2_f32 p1 = {0.0f, 2.0f};
  lm2_v2_f32 p2 = {2.0f, 2.0f};
  lm2_v2_f32 p3 = {2.0f, 0.0f};
  lm2_v2_f32 result = lm2_bezier_cubic2_f32(p0, p1, p2, p3, 0.5f);
  
  EXPECT_NEAR(result.x, 1.0f, EPSILON_F32);
  EXPECT_NEAR(result.y, 1.5f, EPSILON_F32);
}

// =============================================================================
// Cubic Bezier Tests - 3D
// =============================================================================

TEST_F(BezierCurvesTest, CubicBezier3_F64) {
  lm2_v3_f64 p0 = {0.0, 0.0, 0.0};
  lm2_v3_f64 p1 = {1.0, 3.0, 1.0};
  lm2_v3_f64 p2 = {2.0, 3.0, 2.0};
  lm2_v3_f64 p3 = {3.0, 0.0, 3.0};
  lm2_v3_f64 result = lm2_bezier_cubic3_f64(p0, p1, p2, p3, 0.5);
  
  EXPECT_NEAR(result.x, 1.5, EPSILON_F64);
  EXPECT_NEAR(result.y, 2.25, EPSILON_F64);
  EXPECT_NEAR(result.z, 1.5, EPSILON_F64);
}

TEST_F(BezierCurvesTest, CubicBezier3_F32) {
  lm2_v3_f32 p0 = {0.0f, 0.0f, 0.0f};
  lm2_v3_f32 p1 = {1.0f, 2.0f, 1.0f};
  lm2_v3_f32 p2 = {2.0f, 2.0f, 2.0f};
  lm2_v3_f32 p3 = {3.0f, 0.0f, 3.0f};
  lm2_v3_f32 result = lm2_bezier_cubic3_f32(p0, p1, p2, p3, 0.5f);
  
  EXPECT_NEAR(result.x, 1.5f, EPSILON_F32);
  EXPECT_NEAR(result.y, 1.5f, EPSILON_F32);
  EXPECT_NEAR(result.z, 1.5f, EPSILON_F32);
}

// =============================================================================
// Cubic Bezier Tests - 4D
// =============================================================================

TEST_F(BezierCurvesTest, CubicBezier4_F64) {
  lm2_v4_f64 p0 = {0.0, 0.0, 0.0, 0.0};
  lm2_v4_f64 p1 = {1.0, 3.0, 1.0, 3.0};
  lm2_v4_f64 p2 = {2.0, 3.0, 2.0, 3.0};
  lm2_v4_f64 p3 = {3.0, 0.0, 3.0, 0.0};
  lm2_v4_f64 result = lm2_bezier_cubic4_f64(p0, p1, p2, p3, 0.5);
  
  EXPECT_NEAR(result.x, 1.5, EPSILON_F64);
  EXPECT_NEAR(result.y, 2.25, EPSILON_F64);
  EXPECT_NEAR(result.z, 1.5, EPSILON_F64);
  EXPECT_NEAR(result.w, 2.25, EPSILON_F64);
}

TEST_F(BezierCurvesTest, CubicBezier4_F32) {
  lm2_v4_f32 p0 = {0.0f, 0.0f, 0.0f, 0.0f};
  lm2_v4_f32 p1 = {1.0f, 2.0f, 1.0f, 2.0f};
  lm2_v4_f32 p2 = {2.0f, 2.0f, 2.0f, 2.0f};
  lm2_v4_f32 p3 = {3.0f, 0.0f, 3.0f, 0.0f};
  lm2_v4_f32 result = lm2_bezier_cubic4_f32(p0, p1, p2, p3, 0.5f);
  
  EXPECT_NEAR(result.x, 1.5f, EPSILON_F32);
  EXPECT_NEAR(result.y, 1.5f, EPSILON_F32);
  EXPECT_NEAR(result.z, 1.5f, EPSILON_F32);
  EXPECT_NEAR(result.w, 1.5f, EPSILON_F32);
}

// =============================================================================
// Quadratic Bezier Derivative Tests
// =============================================================================

TEST_F(BezierCurvesTest, QuadraticDerivative2_F64) {
  lm2_v2_f64 p0 = {0.0, 0.0};
  lm2_v2_f64 p1 = {5.0, 10.0};
  lm2_v2_f64 p2 = {10.0, 0.0};
  
  // At t=0, derivative should point in direction of p1-p0
  lm2_v2_f64 result_t0 = lm2_bezier_quadratic_derivative2_f64(p0, p1, p2, 0.0);
  EXPECT_NEAR(result_t0.x, 10.0, EPSILON_F64);
  EXPECT_NEAR(result_t0.y, 20.0, EPSILON_F64);
  
  // At t=1, derivative should point in direction of p2-p1
  lm2_v2_f64 result_t1 = lm2_bezier_quadratic_derivative2_f64(p0, p1, p2, 1.0);
  EXPECT_NEAR(result_t1.x, 10.0, EPSILON_F64);
  EXPECT_NEAR(result_t1.y, -20.0, EPSILON_F64);
}

TEST_F(BezierCurvesTest, QuadraticDerivative2_F32) {
  lm2_v2_f32 p0 = {0.0f, 0.0f};
  lm2_v2_f32 p1 = {2.0f, 4.0f};
  lm2_v2_f32 p2 = {4.0f, 0.0f};
  
  lm2_v2_f32 result = lm2_bezier_quadratic_derivative2_f32(p0, p1, p2, 0.5f);
  EXPECT_NEAR(result.x, 4.0f, EPSILON_F32);
  EXPECT_NEAR(result.y, 0.0f, EPSILON_F32);
}

TEST_F(BezierCurvesTest, QuadraticDerivative3_F64) {
  lm2_v3_f64 p0 = {0.0, 0.0, 0.0};
  lm2_v3_f64 p1 = {5.0, 10.0, 5.0};
  lm2_v3_f64 p2 = {10.0, 0.0, 10.0};
  
  lm2_v3_f64 result = lm2_bezier_quadratic_derivative3_f64(p0, p1, p2, 0.5);
  EXPECT_NEAR(result.x, 10.0, EPSILON_F64);
  EXPECT_NEAR(result.y, 0.0, EPSILON_F64);
  EXPECT_NEAR(result.z, 10.0, EPSILON_F64);
}

TEST_F(BezierCurvesTest, QuadraticDerivative4_F32) {
  lm2_v4_f32 p0 = {0.0f, 0.0f, 0.0f, 0.0f};
  lm2_v4_f32 p1 = {2.0f, 4.0f, 2.0f, 4.0f};
  lm2_v4_f32 p2 = {4.0f, 0.0f, 4.0f, 0.0f};
  
  lm2_v4_f32 result = lm2_bezier_quadratic_derivative4_f32(p0, p1, p2, 0.5f);
  EXPECT_NEAR(result.x, 4.0f, EPSILON_F32);
  EXPECT_NEAR(result.y, 0.0f, EPSILON_F32);
  EXPECT_NEAR(result.z, 4.0f, EPSILON_F32);
  EXPECT_NEAR(result.w, 0.0f, EPSILON_F32);
}

// =============================================================================
// Cubic Bezier Derivative Tests
// =============================================================================

TEST_F(BezierCurvesTest, CubicDerivative2_F64) {
  lm2_v2_f64 p0 = {0.0, 0.0};
  lm2_v2_f64 p1 = {1.0, 3.0};
  lm2_v2_f64 p2 = {2.0, 3.0};
  lm2_v2_f64 p3 = {3.0, 0.0};
  
  // At t=0, derivative should be proportional to p1-p0
  lm2_v2_f64 result_t0 = lm2_bezier_cubic_derivative2_f64(p0, p1, p2, p3, 0.0);
  EXPECT_NEAR(result_t0.x, 3.0, EPSILON_F64);
  EXPECT_NEAR(result_t0.y, 9.0, EPSILON_F64);
}

TEST_F(BezierCurvesTest, CubicDerivative3_F32) {
  lm2_v3_f32 p0 = {0.0f, 0.0f, 0.0f};
  lm2_v3_f32 p1 = {1.0f, 2.0f, 1.0f};
  lm2_v3_f32 p2 = {2.0f, 2.0f, 2.0f};
  lm2_v3_f32 p3 = {3.0f, 0.0f, 3.0f};
  
  lm2_v3_f32 result = lm2_bezier_cubic_derivative3_f32(p0, p1, p2, p3, 0.5f);
  // Verify derivative is non-zero
  EXPECT_GT(std::abs(result.x) + std::abs(result.y) + std::abs(result.z), 0.0f);
}

// =============================================================================
// Cubic Bezier Second Derivative Tests
// =============================================================================

TEST_F(BezierCurvesTest, CubicSecondDerivative2_F64) {
  lm2_v2_f64 p0 = {0.0, 0.0};
  lm2_v2_f64 p1 = {1.0, 3.0};
  lm2_v2_f64 p2 = {2.0, 3.0};
  lm2_v2_f64 p3 = {3.0, 0.0};
  
  lm2_v2_f64 result = lm2_bezier_cubic_second_derivative2_f64(p0, p1, p2, p3, 0.5);
  // Second derivative represents curvature
  EXPECT_GT(std::abs(result.x) + std::abs(result.y), 0.0);
}

TEST_F(BezierCurvesTest, CubicSecondDerivative3_F32) {
  lm2_v3_f32 p0 = {0.0f, 0.0f, 0.0f};
  lm2_v3_f32 p1 = {1.0f, 2.0f, 1.0f};
  lm2_v3_f32 p2 = {2.0f, 2.0f, 2.0f};
  lm2_v3_f32 p3 = {3.0f, 0.0f, 3.0f};
  
  lm2_v3_f32 result = lm2_bezier_cubic_second_derivative3_f32(p0, p1, p2, p3, 0.5f);
  EXPECT_GT(std::abs(result.x) + std::abs(result.y) + std::abs(result.z), 0.0f);
}

TEST_F(BezierCurvesTest, CubicSecondDerivative4_F64) {
  lm2_v4_f64 p0 = {0.0, 0.0, 0.0, 0.0};
  lm2_v4_f64 p1 = {1.0, 3.0, 1.0, 3.0};
  lm2_v4_f64 p2 = {2.0, 3.0, 2.0, 3.0};
  lm2_v4_f64 p3 = {3.0, 0.0, 3.0, 0.0};
  
  lm2_v4_f64 result = lm2_bezier_cubic_second_derivative4_f64(p0, p1, p2, p3, 0.5);
  EXPECT_GT(std::abs(result.x) + std::abs(result.y) + std::abs(result.z) + std::abs(result.w), 0.0);
}

// =============================================================================
// Cubic Bezier Splitting Tests
// =============================================================================

TEST_F(BezierCurvesTest, CubicSplit2_F64_At05) {
  lm2_v2_f64 p0 = {0.0, 0.0};
  lm2_v2_f64 p1 = {1.0, 3.0};
  lm2_v2_f64 p2 = {2.0, 3.0};
  lm2_v2_f64 p3 = {3.0, 0.0};
  
  lm2_v2_f64 left_p0, left_p1, left_p2, left_p3;
  lm2_v2_f64 right_p0, right_p1, right_p2, right_p3;
  
  lm2_bezier_cubic_split2_f64(p0, p1, p2, p3, 0.5,
                              &left_p0, &left_p1, &left_p2, &left_p3,
                              &right_p0, &right_p1, &right_p2, &right_p3);
  
  // Left curve should start at original p0
  EXPECT_NEAR(left_p0.x, p0.x, EPSILON_F64);
  EXPECT_NEAR(left_p0.y, p0.y, EPSILON_F64);
  
  // Right curve should end at original p3
  EXPECT_NEAR(right_p3.x, p3.x, EPSILON_F64);
  EXPECT_NEAR(right_p3.y, p3.y, EPSILON_F64);
  
  // Left end should equal right start (split point)
  EXPECT_NEAR(left_p3.x, right_p0.x, EPSILON_F64);
  EXPECT_NEAR(left_p3.y, right_p0.y, EPSILON_F64);
  
  // Split point should equal curve at t=0.5
  lm2_v2_f64 mid = lm2_bezier_cubic2_f64(p0, p1, p2, p3, 0.5);
  EXPECT_NEAR(left_p3.x, mid.x, EPSILON_F64);
  EXPECT_NEAR(left_p3.y, mid.y, EPSILON_F64);
}

TEST_F(BezierCurvesTest, CubicSplit2_F32) {
  lm2_v2_f32 p0 = {0.0f, 0.0f};
  lm2_v2_f32 p1 = {1.0f, 2.0f};
  lm2_v2_f32 p2 = {2.0f, 2.0f};
  lm2_v2_f32 p3 = {3.0f, 0.0f};
  
  lm2_v2_f32 left_p0, left_p1, left_p2, left_p3;
  lm2_v2_f32 right_p0, right_p1, right_p2, right_p3;
  
  lm2_bezier_cubic_split2_f32(p0, p1, p2, p3, 0.5f,
                              &left_p0, &left_p1, &left_p2, &left_p3,
                              &right_p0, &right_p1, &right_p2, &right_p3);
  
  EXPECT_NEAR(left_p0.x, p0.x, EPSILON_F32);
  EXPECT_NEAR(right_p3.x, p3.x, EPSILON_F32);
}

TEST_F(BezierCurvesTest, CubicSplit3_F64) {
  lm2_v3_f64 p0 = {0.0, 0.0, 0.0};
  lm2_v3_f64 p1 = {1.0, 3.0, 1.0};
  lm2_v3_f64 p2 = {2.0, 3.0, 2.0};
  lm2_v3_f64 p3 = {3.0, 0.0, 3.0};
  
  lm2_v3_f64 left_p0, left_p1, left_p2, left_p3;
  lm2_v3_f64 right_p0, right_p1, right_p2, right_p3;
  
  lm2_bezier_cubic_split3_f64(p0, p1, p2, p3, 0.5,
                              &left_p0, &left_p1, &left_p2, &left_p3,
                              &right_p0, &right_p1, &right_p2, &right_p3);
  
  EXPECT_NEAR(left_p0.x, p0.x, EPSILON_F64);
  EXPECT_NEAR(right_p3.z, p3.z, EPSILON_F64);
  EXPECT_NEAR(left_p3.x, right_p0.x, EPSILON_F64);
}

TEST_F(BezierCurvesTest, CubicSplit4_F32) {
  lm2_v4_f32 p0 = {0.0f, 0.0f, 0.0f, 0.0f};
  lm2_v4_f32 p1 = {1.0f, 2.0f, 1.0f, 2.0f};
  lm2_v4_f32 p2 = {2.0f, 2.0f, 2.0f, 2.0f};
  lm2_v4_f32 p3 = {3.0f, 0.0f, 3.0f, 0.0f};
  
  lm2_v4_f32 left_p0, left_p1, left_p2, left_p3;
  lm2_v4_f32 right_p0, right_p1, right_p2, right_p3;
  
  lm2_bezier_cubic_split4_f32(p0, p1, p2, p3, 0.5f,
                              &left_p0, &left_p1, &left_p2, &left_p3,
                              &right_p0, &right_p1, &right_p2, &right_p3);
  
  EXPECT_NEAR(left_p0.w, p0.w, EPSILON_F32);
  EXPECT_NEAR(right_p3.w, p3.w, EPSILON_F32);
}

// =============================================================================
// Bezier Arc Length Tests
// =============================================================================

TEST_F(BezierCurvesTest, CubicLength2_F64_StraightLine) {
  // Straight line from (0,0) to (10,0)
  lm2_v2_f64 p0 = {0.0, 0.0};
  lm2_v2_f64 p1 = {10.0 / 3.0, 0.0};
  lm2_v2_f64 p2 = {20.0 / 3.0, 0.0};
  lm2_v2_f64 p3 = {10.0, 0.0};
  
  double length = lm2_bezier_cubic_length2_f64(p0, p1, p2, p3, 100);
  EXPECT_NEAR(length, 10.0, 0.1);
}

TEST_F(BezierCurvesTest, CubicLength2_F32) {
  lm2_v2_f32 p0 = {0.0f, 0.0f};
  lm2_v2_f32 p1 = {1.0f, 2.0f};
  lm2_v2_f32 p2 = {2.0f, 2.0f};
  lm2_v2_f32 p3 = {3.0f, 0.0f};
  
  float length = lm2_bezier_cubic_length2_f32(p0, p1, p2, p3, 50);
  // Length should be greater than straight-line distance
  EXPECT_GT(length, 3.0f);
  EXPECT_LT(length, 10.0f);  // But not unreasonably large
}

TEST_F(BezierCurvesTest, CubicLength3_F64) {
  lm2_v3_f64 p0 = {0.0, 0.0, 0.0};
  lm2_v3_f64 p1 = {1.0, 2.0, 1.0};
  lm2_v3_f64 p2 = {2.0, 2.0, 2.0};
  lm2_v3_f64 p3 = {3.0, 0.0, 3.0};
  
  double length = lm2_bezier_cubic_length3_f64(p0, p1, p2, p3, 50);
  EXPECT_GT(length, 0.0);
  EXPECT_LT(length, 15.0);
}

TEST_F(BezierCurvesTest, CubicLength4_F32) {
  lm2_v4_f32 p0 = {0.0f, 0.0f, 0.0f, 0.0f};
  lm2_v4_f32 p1 = {1.0f, 1.0f, 1.0f, 1.0f};
  lm2_v4_f32 p2 = {2.0f, 1.0f, 2.0f, 1.0f};
  lm2_v4_f32 p3 = {3.0f, 0.0f, 3.0f, 0.0f};
  
  float length = lm2_bezier_cubic_length4_f32(p0, p1, p2, p3, 50);
  EXPECT_GT(length, 0.0f);
}
