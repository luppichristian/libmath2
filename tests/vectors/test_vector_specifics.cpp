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
#include "lm2/vectors/lm2_vector_specifics.h"

// Test fixture for vector specifics tests
class VectorSpecificsTest : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
  static constexpr double PI = 3.14159265358979323846;
};

// =============================================================================
// Dot Product Tests (2D)
// =============================================================================

TEST_F(VectorSpecificsTest, Dot2_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(3.0, 4.0);
  lm2_v2_f64 b = lm2_v2_make_f64(2.0, 1.0);
  double result = lm2_v2_dot_f64(a, b);
  EXPECT_DOUBLE_EQ(result, 10.0);  // 3*2 + 4*1 = 10
}

TEST_F(VectorSpecificsTest, Dot2_F32) {
  lm2_v2_f32 a = lm2_v2_make_f32(3.0f, 4.0f);
  lm2_v2_f32 b = lm2_v2_make_f32(2.0f, 1.0f);
  float result = lm2_v2_dot_f32(a, b);
  EXPECT_FLOAT_EQ(result, 10.0f);
}

TEST_F(VectorSpecificsTest, Dot2_I32) {
  lm2_v2_i32 a = lm2_v2_make_i32(3, 4);
  lm2_v2_i32 b = lm2_v2_make_i32(2, 1);
  int32_t result = lm2_v2_dot_i32(a, b);
  EXPECT_EQ(result, 10);
}

TEST_F(VectorSpecificsTest, Dot2_Orthogonal_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(1.0, 0.0);
  lm2_v2_f64 b = lm2_v2_make_f64(0.0, 1.0);
  double result = lm2_v2_dot_f64(a, b);
  EXPECT_DOUBLE_EQ(result, 0.0);  // Orthogonal vectors
}

// =============================================================================
// Dot Product Tests (3D)
// =============================================================================

TEST_F(VectorSpecificsTest, Dot3_F64) {
  lm2_v3_f64 a = lm2_v3_make_f64(1.0, 2.0, 3.0);
  lm2_v3_f64 b = lm2_v3_make_f64(4.0, 5.0, 6.0);
  double result = lm2_v3_dot_f64(a, b);
  EXPECT_DOUBLE_EQ(result, 32.0);  // 1*4 + 2*5 + 3*6 = 32
}

TEST_F(VectorSpecificsTest, Dot3_F32) {
  lm2_v3_f32 a = lm2_v3_make_f32(1.0f, 2.0f, 3.0f);
  lm2_v3_f32 b = lm2_v3_make_f32(4.0f, 5.0f, 6.0f);
  float result = lm2_v3_dot_f32(a, b);
  EXPECT_FLOAT_EQ(result, 32.0f);
}

TEST_F(VectorSpecificsTest, Dot3_I32) {
  lm2_v3_i32 a = lm2_v3_make_i32(1, 2, 3);
  lm2_v3_i32 b = lm2_v3_make_i32(4, 5, 6);
  int32_t result = lm2_v3_dot_i32(a, b);
  EXPECT_EQ(result, 32);
}

TEST_F(VectorSpecificsTest, Dot3_Orthogonal_F64) {
  lm2_v3_f64 a = lm2_v3_make_f64(1.0, 0.0, 0.0);
  lm2_v3_f64 b = lm2_v3_make_f64(0.0, 1.0, 0.0);
  double result = lm2_v3_dot_f64(a, b);
  EXPECT_DOUBLE_EQ(result, 0.0);
}

// =============================================================================
// Dot Product Tests (4D)
// =============================================================================

TEST_F(VectorSpecificsTest, Dot4_F64) {
  lm2_v4_f64 a = lm2_v4_make_f64(1.0, 2.0, 3.0, 4.0);
  lm2_v4_f64 b = lm2_v4_make_f64(5.0, 6.0, 7.0, 8.0);
  double result = lm2_v4_dot_f64(a, b);
  EXPECT_DOUBLE_EQ(result, 70.0);  // 1*5 + 2*6 + 3*7 + 4*8 = 70
}

TEST_F(VectorSpecificsTest, Dot4_F32) {
  lm2_v4_f32 a = lm2_v4_make_f32(1.0f, 2.0f, 3.0f, 4.0f);
  lm2_v4_f32 b = lm2_v4_make_f32(5.0f, 6.0f, 7.0f, 8.0f);
  float result = lm2_v4_dot_f32(a, b);
  EXPECT_FLOAT_EQ(result, 70.0f);
}

TEST_F(VectorSpecificsTest, Dot4_I32) {
  lm2_v4_i32 a = lm2_v4_make_i32(1, 2, 3, 4);
  lm2_v4_i32 b = lm2_v4_make_i32(5, 6, 7, 8);
  int32_t result = lm2_v4_dot_i32(a, b);
  EXPECT_EQ(result, 70);
}

// =============================================================================
// Cross Product Tests (3D)
// =============================================================================

TEST_F(VectorSpecificsTest, Cross3_F64) {
  lm2_v3_f64 a = lm2_v3_make_f64(1.0, 0.0, 0.0);
  lm2_v3_f64 b = lm2_v3_make_f64(0.0, 1.0, 0.0);
  lm2_v3_f64 result = lm2_v3_cross_f64(a, b);
  EXPECT_DOUBLE_EQ(result.x, 0.0);
  EXPECT_DOUBLE_EQ(result.y, 0.0);
  EXPECT_DOUBLE_EQ(result.z, 1.0);
}

TEST_F(VectorSpecificsTest, Cross3_F32) {
  lm2_v3_f32 a = lm2_v3_make_f32(1.0f, 0.0f, 0.0f);
  lm2_v3_f32 b = lm2_v3_make_f32(0.0f, 1.0f, 0.0f);
  lm2_v3_f32 result = lm2_v3_cross_f32(a, b);
  EXPECT_FLOAT_EQ(result.x, 0.0f);
  EXPECT_FLOAT_EQ(result.y, 0.0f);
  EXPECT_FLOAT_EQ(result.z, 1.0f);
}

TEST_F(VectorSpecificsTest, Cross3_I32) {
  lm2_v3_i32 a = lm2_v3_make_i32(1, 0, 0);
  lm2_v3_i32 b = lm2_v3_make_i32(0, 1, 0);
  lm2_v3_i32 result = lm2_v3_cross_i32(a, b);
  EXPECT_EQ(result.x, 0);
  EXPECT_EQ(result.y, 0);
  EXPECT_EQ(result.z, 1);
}

TEST_F(VectorSpecificsTest, Cross3_General_F64) {
  lm2_v3_f64 a = lm2_v3_make_f64(2.0, 3.0, 4.0);
  lm2_v3_f64 b = lm2_v3_make_f64(5.0, 6.0, 7.0);
  lm2_v3_f64 result = lm2_v3_cross_f64(a, b);
  EXPECT_DOUBLE_EQ(result.x, -3.0);  // 3*7 - 4*6 = -3
  EXPECT_DOUBLE_EQ(result.y, 6.0);   // 4*5 - 2*7 = 6
  EXPECT_DOUBLE_EQ(result.z, -3.0);  // 2*6 - 3*5 = -3
}

// =============================================================================
// Cross Product Tests (2D - returns scalar)
// =============================================================================

TEST_F(VectorSpecificsTest, Cross2_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(3.0, 4.0);
  lm2_v2_f64 b = lm2_v2_make_f64(5.0, 6.0);
  double result = lm2_v2_cross_f64(a, b);
  EXPECT_DOUBLE_EQ(result, -2.0);  // 3*6 - 4*5 = -2
}

TEST_F(VectorSpecificsTest, Cross2_F32) {
  lm2_v2_f32 a = lm2_v2_make_f32(3.0f, 4.0f);
  lm2_v2_f32 b = lm2_v2_make_f32(5.0f, 6.0f);
  float result = lm2_v2_cross_f32(a, b);
  EXPECT_FLOAT_EQ(result, -2.0f);
}

TEST_F(VectorSpecificsTest, Cross2_I32) {
  lm2_v2_i32 a = lm2_v2_make_i32(3, 4);
  lm2_v2_i32 b = lm2_v2_make_i32(5, 6);
  int32_t result = lm2_v2_cross_i32(a, b);
  EXPECT_EQ(result, -2);
}

// =============================================================================
// Cross3 (Three-point cross for turn detection)
// =============================================================================

TEST_F(VectorSpecificsTest, Cross3_LeftTurn_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(0.0, 0.0);
  lm2_v2_f64 b = lm2_v2_make_f64(1.0, 0.0);
  lm2_v2_f64 c = lm2_v2_make_f64(1.0, 1.0);
  double result = lm2_v2_cross3_f64(a, b, c);
  EXPECT_GT(result, 0.0);  // Left turn (counter-clockwise)
}

TEST_F(VectorSpecificsTest, Cross3_RightTurn_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(0.0, 0.0);
  lm2_v2_f64 b = lm2_v2_make_f64(1.0, 0.0);
  lm2_v2_f64 c = lm2_v2_make_f64(1.0, -1.0);
  double result = lm2_v2_cross3_f64(a, b, c);
  EXPECT_LT(result, 0.0);  // Right turn (clockwise)
}

TEST_F(VectorSpecificsTest, Cross3_Collinear_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(0.0, 0.0);
  lm2_v2_f64 b = lm2_v2_make_f64(1.0, 0.0);
  lm2_v2_f64 c = lm2_v2_make_f64(2.0, 0.0);
  double result = lm2_v2_cross3_f64(a, b, c);
  EXPECT_DOUBLE_EQ(result, 0.0);  // Collinear
}

// =============================================================================
// Length Tests
// =============================================================================

TEST_F(VectorSpecificsTest, Length2_F64) {
  lm2_v2_f64 v = lm2_v2_make_f64(3.0, 4.0);
  double result = lm2_v2_length_f64(v);
  EXPECT_DOUBLE_EQ(result, 5.0);  // 3-4-5 triangle
}

TEST_F(VectorSpecificsTest, Length2_F32) {
  lm2_v2_f32 v = lm2_v2_make_f32(3.0f, 4.0f);
  float result = lm2_v2_length_f32(v);
  EXPECT_FLOAT_EQ(result, 5.0f);
}

TEST_F(VectorSpecificsTest, Length3_F64) {
  lm2_v3_f64 v = lm2_v3_make_f64(2.0, 3.0, 6.0);
  double result = lm2_v3_length_f64(v);
  EXPECT_DOUBLE_EQ(result, 7.0);  // sqrt(4+9+36) = 7
}

TEST_F(VectorSpecificsTest, Length3_F32) {
  lm2_v3_f32 v = lm2_v3_make_f32(2.0f, 3.0f, 6.0f);
  float result = lm2_v3_length_f32(v);
  EXPECT_FLOAT_EQ(result, 7.0f);
}

TEST_F(VectorSpecificsTest, Length4_F64) {
  lm2_v4_f64 v = lm2_v4_make_f64(2.0, 3.0, 6.0, 0.0);
  double result = lm2_v4_length_f64(v);
  EXPECT_DOUBLE_EQ(result, 7.0);
}

TEST_F(VectorSpecificsTest, Length4_F32) {
  lm2_v4_f32 v = lm2_v4_make_f32(2.0f, 3.0f, 6.0f, 0.0f);
  float result = lm2_v4_length_f32(v);
  EXPECT_FLOAT_EQ(result, 7.0f);
}

// =============================================================================
// Length Squared Tests
// =============================================================================

TEST_F(VectorSpecificsTest, LengthSq2_F64) {
  lm2_v2_f64 v = lm2_v2_make_f64(3.0, 4.0);
  double result = lm2_v2_length_sq_f64(v);
  EXPECT_DOUBLE_EQ(result, 25.0);  // 9 + 16 = 25
}

TEST_F(VectorSpecificsTest, LengthSq2_F32) {
  lm2_v2_f32 v = lm2_v2_make_f32(3.0f, 4.0f);
  float result = lm2_v2_length_sq_f32(v);
  EXPECT_FLOAT_EQ(result, 25.0f);
}

TEST_F(VectorSpecificsTest, LengthSq3_F64) {
  lm2_v3_f64 v = lm2_v3_make_f64(2.0, 3.0, 6.0);
  double result = lm2_v3_length_sq_f64(v);
  EXPECT_DOUBLE_EQ(result, 49.0);  // 4 + 9 + 36 = 49
}

TEST_F(VectorSpecificsTest, LengthSq3_F32) {
  lm2_v3_f32 v = lm2_v3_make_f32(2.0f, 3.0f, 6.0f);
  float result = lm2_v3_length_sq_f32(v);
  EXPECT_FLOAT_EQ(result, 49.0f);
}

TEST_F(VectorSpecificsTest, LengthSq4_F64) {
  lm2_v4_f64 v = lm2_v4_make_f64(2.0, 3.0, 6.0, 0.0);
  double result = lm2_v4_length_sq_f64(v);
  EXPECT_DOUBLE_EQ(result, 49.0);
}

TEST_F(VectorSpecificsTest, LengthSq4_F32) {
  lm2_v4_f32 v = lm2_v4_make_f32(2.0f, 3.0f, 6.0f, 0.0f);
  float result = lm2_v4_length_sq_f32(v);
  EXPECT_FLOAT_EQ(result, 49.0f);
}

// =============================================================================
// Distance Tests
// =============================================================================

TEST_F(VectorSpecificsTest, Distance2_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(1.0, 2.0);
  lm2_v2_f64 b = lm2_v2_make_f64(4.0, 6.0);
  double result = lm2_v2_distance_f64(a, b);
  EXPECT_DOUBLE_EQ(result, 5.0);  // sqrt(9 + 16) = 5
}

TEST_F(VectorSpecificsTest, Distance2_F32) {
  lm2_v2_f32 a = lm2_v2_make_f32(1.0f, 2.0f);
  lm2_v2_f32 b = lm2_v2_make_f32(4.0f, 6.0f);
  float result = lm2_v2_distance_f32(a, b);
  EXPECT_FLOAT_EQ(result, 5.0f);
}

TEST_F(VectorSpecificsTest, Distance3_F64) {
  lm2_v3_f64 a = lm2_v3_make_f64(1.0, 2.0, 3.0);
  lm2_v3_f64 b = lm2_v3_make_f64(4.0, 6.0, 3.0);
  double result = lm2_v3_distance_f64(a, b);
  EXPECT_DOUBLE_EQ(result, 5.0);  // sqrt(9 + 16 + 0) = 5
}

TEST_F(VectorSpecificsTest, Distance3_F32) {
  lm2_v3_f32 a = lm2_v3_make_f32(1.0f, 2.0f, 3.0f);
  lm2_v3_f32 b = lm2_v3_make_f32(4.0f, 6.0f, 3.0f);
  float result = lm2_v3_distance_f32(a, b);
  EXPECT_FLOAT_EQ(result, 5.0f);
}

TEST_F(VectorSpecificsTest, Distance4_F64) {
  lm2_v4_f64 a = lm2_v4_make_f64(1.0, 2.0, 3.0, 0.0);
  lm2_v4_f64 b = lm2_v4_make_f64(4.0, 6.0, 3.0, 0.0);
  double result = lm2_v4_distance_f64(a, b);
  EXPECT_DOUBLE_EQ(result, 5.0);
}

TEST_F(VectorSpecificsTest, Distance4_F32) {
  lm2_v4_f32 a = lm2_v4_make_f32(1.0f, 2.0f, 3.0f, 0.0f);
  lm2_v4_f32 b = lm2_v4_make_f32(4.0f, 6.0f, 3.0f, 0.0f);
  float result = lm2_v4_distance_f32(a, b);
  EXPECT_FLOAT_EQ(result, 5.0f);
}

// =============================================================================
// Distance Squared Tests
// =============================================================================

TEST_F(VectorSpecificsTest, DistanceSq2_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(1.0, 2.0);
  lm2_v2_f64 b = lm2_v2_make_f64(4.0, 6.0);
  double result = lm2_v2_distance_sq_f64(a, b);
  EXPECT_DOUBLE_EQ(result, 25.0);  // 9 + 16 = 25
}

TEST_F(VectorSpecificsTest, DistanceSq2_F32) {
  lm2_v2_f32 a = lm2_v2_make_f32(1.0f, 2.0f);
  lm2_v2_f32 b = lm2_v2_make_f32(4.0f, 6.0f);
  float result = lm2_v2_distance_sq_f32(a, b);
  EXPECT_FLOAT_EQ(result, 25.0f);
}

TEST_F(VectorSpecificsTest, DistanceSq3_F64) {
  lm2_v3_f64 a = lm2_v3_make_f64(1.0, 2.0, 3.0);
  lm2_v3_f64 b = lm2_v3_make_f64(4.0, 6.0, 3.0);
  double result = lm2_v3_distance_sq_f64(a, b);
  EXPECT_DOUBLE_EQ(result, 25.0);  // 9 + 16 + 0 = 25
}

TEST_F(VectorSpecificsTest, DistanceSq3_F32) {
  lm2_v3_f32 a = lm2_v3_make_f32(1.0f, 2.0f, 3.0f);
  lm2_v3_f32 b = lm2_v3_make_f32(4.0f, 6.0f, 3.0f);
  float result = lm2_v3_distance_sq_f32(a, b);
  EXPECT_FLOAT_EQ(result, 25.0f);
}

TEST_F(VectorSpecificsTest, DistanceSq4_F64) {
  lm2_v4_f64 a = lm2_v4_make_f64(1.0, 2.0, 3.0, 0.0);
  lm2_v4_f64 b = lm2_v4_make_f64(4.0, 6.0, 3.0, 0.0);
  double result = lm2_v4_distance_sq_f64(a, b);
  EXPECT_DOUBLE_EQ(result, 25.0);
}

TEST_F(VectorSpecificsTest, DistanceSq4_F32) {
  lm2_v4_f32 a = lm2_v4_make_f32(1.0f, 2.0f, 3.0f, 0.0f);
  lm2_v4_f32 b = lm2_v4_make_f32(4.0f, 6.0f, 3.0f, 0.0f);
  float result = lm2_v4_distance_sq_f32(a, b);
  EXPECT_FLOAT_EQ(result, 25.0f);
}

// =============================================================================
// Normalize Tests
// =============================================================================

TEST_F(VectorSpecificsTest, Normalize2_F64) {
  lm2_v2_f64 v = lm2_v2_make_f64(3.0, 4.0);
  lm2_v2_f64 result = lm2_v2_normalize_f64(v);
  EXPECT_DOUBLE_EQ(result.x, 0.6);  // 3/5
  EXPECT_DOUBLE_EQ(result.y, 0.8);  // 4/5
}

TEST_F(VectorSpecificsTest, Normalize2_F32) {
  lm2_v2_f32 v = lm2_v2_make_f32(3.0f, 4.0f);
  lm2_v2_f32 result = lm2_v2_normalize_f32(v);
  EXPECT_FLOAT_EQ(result.x, 0.6f);
  EXPECT_FLOAT_EQ(result.y, 0.8f);
}

TEST_F(VectorSpecificsTest, Normalize3_F64) {
  lm2_v3_f64 v = lm2_v3_make_f64(2.0, 3.0, 6.0);
  lm2_v3_f64 result = lm2_v3_normalize_f64(v);
  EXPECT_DOUBLE_EQ(result.x, 2.0 / 7.0);
  EXPECT_DOUBLE_EQ(result.y, 3.0 / 7.0);
  EXPECT_DOUBLE_EQ(result.z, 6.0 / 7.0);
}

TEST_F(VectorSpecificsTest, Normalize3_F32) {
  lm2_v3_f32 v = lm2_v3_make_f32(2.0f, 3.0f, 6.0f);
  lm2_v3_f32 result = lm2_v3_normalize_f32(v);
  EXPECT_FLOAT_EQ(result.x, 2.0f / 7.0f);
  EXPECT_FLOAT_EQ(result.y, 3.0f / 7.0f);
  EXPECT_FLOAT_EQ(result.z, 6.0f / 7.0f);
}

TEST_F(VectorSpecificsTest, Normalize4_F64) {
  lm2_v4_f64 v = lm2_v4_make_f64(2.0, 0.0, 0.0, 0.0);
  lm2_v4_f64 result = lm2_v4_normalize_f64(v);
  EXPECT_DOUBLE_EQ(result.x, 1.0);
  EXPECT_DOUBLE_EQ(result.y, 0.0);
  EXPECT_DOUBLE_EQ(result.z, 0.0);
  EXPECT_DOUBLE_EQ(result.w, 0.0);
}

TEST_F(VectorSpecificsTest, Normalize4_F32) {
  lm2_v4_f32 v = lm2_v4_make_f32(2.0f, 0.0f, 0.0f, 0.0f);
  lm2_v4_f32 result = lm2_v4_normalize_f32(v);
  EXPECT_FLOAT_EQ(result.x, 1.0f);
  EXPECT_FLOAT_EQ(result.y, 0.0f);
  EXPECT_FLOAT_EQ(result.z, 0.0f);
  EXPECT_FLOAT_EQ(result.w, 0.0f);
}

// =============================================================================
// Angle Tests
// =============================================================================

TEST_F(VectorSpecificsTest, Angle2_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(1.0, 0.0);
  lm2_v2_f64 b = lm2_v2_make_f64(0.0, 1.0);
  double result = lm2_v2_angle_f64(a, b);
  EXPECT_NEAR(result, PI / 2.0, EPSILON_F64);  // 90 degrees
}

TEST_F(VectorSpecificsTest, Angle2_F32) {
  lm2_v2_f32 a = lm2_v2_make_f32(1.0f, 0.0f);
  lm2_v2_f32 b = lm2_v2_make_f32(0.0f, 1.0f);
  float result = lm2_v2_angle_f32(a, b);
  EXPECT_NEAR(result, PI / 2.0f, EPSILON_F32);
}

TEST_F(VectorSpecificsTest, Angle3_F64) {
  lm2_v3_f64 a = lm2_v3_make_f64(1.0, 0.0, 0.0);
  lm2_v3_f64 b = lm2_v3_make_f64(0.0, 1.0, 0.0);
  double result = lm2_v3_angle_f64(a, b);
  EXPECT_NEAR(result, PI / 2.0, EPSILON_F64);
}

TEST_F(VectorSpecificsTest, Angle3_F32) {
  lm2_v3_f32 a = lm2_v3_make_f32(1.0f, 0.0f, 0.0f);
  lm2_v3_f32 b = lm2_v3_make_f32(0.0f, 1.0f, 0.0f);
  float result = lm2_v3_angle_f32(a, b);
  EXPECT_NEAR(result, PI / 2.0f, EPSILON_F32);
}

// =============================================================================
// 2D Rotation Tests
// =============================================================================

TEST_F(VectorSpecificsTest, Rotate2_F64) {
  lm2_v2_f64 v = lm2_v2_make_f64(1.0, 0.0);
  lm2_v2_f64 result = lm2_v2_rotate_f64(v, PI / 2.0);  // Rotate 90 degrees
  EXPECT_NEAR(result.x, 0.0, EPSILON_F64);
  EXPECT_NEAR(result.y, 1.0, EPSILON_F64);
}

TEST_F(VectorSpecificsTest, Rotate2_F32) {
  lm2_v2_f32 v = lm2_v2_make_f32(1.0f, 0.0f);
  lm2_v2_f32 result = lm2_v2_rotate_f32(v, PI / 2.0f);
  EXPECT_NEAR(result.x, 0.0f, EPSILON_F32);
  EXPECT_NEAR(result.y, 1.0f, EPSILON_F32);
}

TEST_F(VectorSpecificsTest, RotateAround2_F64) {
  lm2_v2_f64 v = lm2_v2_make_f64(2.0, 0.0);
  lm2_v2_f64 point = lm2_v2_make_f64(1.0, 0.0);
  lm2_v2_f64 result = lm2_v2_rotate_around_f64(v, point, PI / 2.0);
  EXPECT_NEAR(result.x, 1.0, EPSILON_F64);
  EXPECT_NEAR(result.y, 1.0, EPSILON_F64);
}

TEST_F(VectorSpecificsTest, RotateAround2_F32) {
  lm2_v2_f32 v = lm2_v2_make_f32(2.0f, 0.0f);
  lm2_v2_f32 point = lm2_v2_make_f32(1.0f, 0.0f);
  lm2_v2_f32 result = lm2_v2_rotate_around_f32(v, point, PI / 2.0f);
  EXPECT_NEAR(result.x, 1.0f, EPSILON_F32);
  EXPECT_NEAR(result.y, 1.0f, EPSILON_F32);
}

// =============================================================================
// Perpendicular Vector Tests
// =============================================================================

TEST_F(VectorSpecificsTest, PerpCCW2_F64) {
  lm2_v2_f64 v = lm2_v2_make_f64(1.0, 0.0);
  lm2_v2_f64 result = lm2_v2_perp_ccw_f64(v);
  EXPECT_DOUBLE_EQ(result.x, 0.0);
  EXPECT_DOUBLE_EQ(result.y, 1.0);
}

TEST_F(VectorSpecificsTest, PerpCCW2_F32) {
  lm2_v2_f32 v = lm2_v2_make_f32(1.0f, 0.0f);
  lm2_v2_f32 result = lm2_v2_perp_ccw_f32(v);
  EXPECT_FLOAT_EQ(result.x, 0.0f);
  EXPECT_FLOAT_EQ(result.y, 1.0f);
}

TEST_F(VectorSpecificsTest, PerpCW2_F64) {
  lm2_v2_f64 v = lm2_v2_make_f64(1.0, 0.0);
  lm2_v2_f64 result = lm2_v2_perp_cw_f64(v);
  EXPECT_DOUBLE_EQ(result.x, 0.0);
  EXPECT_DOUBLE_EQ(result.y, -1.0);
}

TEST_F(VectorSpecificsTest, PerpCW2_F32) {
  lm2_v2_f32 v = lm2_v2_make_f32(1.0f, 0.0f);
  lm2_v2_f32 result = lm2_v2_perp_cw_f32(v);
  EXPECT_FLOAT_EQ(result.x, 0.0f);
  EXPECT_FLOAT_EQ(result.y, -1.0f);
}

TEST_F(VectorSpecificsTest, PerpCCW2_I32) {
  lm2_v2_i32 v = lm2_v2_make_i32(1, 0);
  lm2_v2_i32 result = lm2_v2_perp_ccw_i32(v);
  EXPECT_EQ(result.x, 0);
  EXPECT_EQ(result.y, 1);
}

TEST_F(VectorSpecificsTest, PerpCW2_I32) {
  lm2_v2_i32 v = lm2_v2_make_i32(1, 0);
  lm2_v2_i32 result = lm2_v2_perp_cw_i32(v);
  EXPECT_EQ(result.x, 0);
  EXPECT_EQ(result.y, -1);
}

// =============================================================================
// Reflection Tests
// =============================================================================

TEST_F(VectorSpecificsTest, Reflect2_F64) {
  lm2_v2_f64 v = lm2_v2_make_f64(1.0, -1.0);
  lm2_v2_f64 normal = lm2_v2_make_f64(0.0, 1.0);
  lm2_v2_f64 result = lm2_v2_reflect_f64(v, normal);
  EXPECT_DOUBLE_EQ(result.x, 1.0);
  EXPECT_DOUBLE_EQ(result.y, 1.0);
}

TEST_F(VectorSpecificsTest, Reflect2_F32) {
  lm2_v2_f32 v = lm2_v2_make_f32(1.0f, -1.0f);
  lm2_v2_f32 normal = lm2_v2_make_f32(0.0f, 1.0f);
  lm2_v2_f32 result = lm2_v2_reflect_f32(v, normal);
  EXPECT_FLOAT_EQ(result.x, 1.0f);
  EXPECT_FLOAT_EQ(result.y, 1.0f);
}

TEST_F(VectorSpecificsTest, Reflect3_F64) {
  lm2_v3_f64 v = lm2_v3_make_f64(1.0, -1.0, 0.0);
  lm2_v3_f64 normal = lm2_v3_make_f64(0.0, 1.0, 0.0);
  lm2_v3_f64 result = lm2_v3_reflect_f64(v, normal);
  EXPECT_DOUBLE_EQ(result.x, 1.0);
  EXPECT_DOUBLE_EQ(result.y, 1.0);
  EXPECT_DOUBLE_EQ(result.z, 0.0);
}

TEST_F(VectorSpecificsTest, Reflect3_F32) {
  lm2_v3_f32 v = lm2_v3_make_f32(1.0f, -1.0f, 0.0f);
  lm2_v3_f32 normal = lm2_v3_make_f32(0.0f, 1.0f, 0.0f);
  lm2_v3_f32 result = lm2_v3_reflect_f32(v, normal);
  EXPECT_FLOAT_EQ(result.x, 1.0f);
  EXPECT_FLOAT_EQ(result.y, 1.0f);
  EXPECT_FLOAT_EQ(result.z, 0.0f);
}

// =============================================================================
// Projection Tests
// =============================================================================

TEST_F(VectorSpecificsTest, Project2_F64) {
  lm2_v2_f64 a = lm2_v2_make_f64(3.0, 4.0);
  lm2_v2_f64 b = lm2_v2_make_f64(1.0, 0.0);
  lm2_v2_f64 result = lm2_v2_project_f64(a, b);
  EXPECT_DOUBLE_EQ(result.x, 3.0);
  EXPECT_DOUBLE_EQ(result.y, 0.0);
}

TEST_F(VectorSpecificsTest, Project2_F32) {
  lm2_v2_f32 a = lm2_v2_make_f32(3.0f, 4.0f);
  lm2_v2_f32 b = lm2_v2_make_f32(1.0f, 0.0f);
  lm2_v2_f32 result = lm2_v2_project_f32(a, b);
  EXPECT_FLOAT_EQ(result.x, 3.0f);
  EXPECT_FLOAT_EQ(result.y, 0.0f);
}

TEST_F(VectorSpecificsTest, Project3_F64) {
  lm2_v3_f64 a = lm2_v3_make_f64(3.0, 4.0, 0.0);
  lm2_v3_f64 b = lm2_v3_make_f64(1.0, 0.0, 0.0);
  lm2_v3_f64 result = lm2_v3_project_f64(a, b);
  EXPECT_DOUBLE_EQ(result.x, 3.0);
  EXPECT_DOUBLE_EQ(result.y, 0.0);
  EXPECT_DOUBLE_EQ(result.z, 0.0);
}

TEST_F(VectorSpecificsTest, Project3_F32) {
  lm2_v3_f32 a = lm2_v3_make_f32(3.0f, 4.0f, 0.0f);
  lm2_v3_f32 b = lm2_v3_make_f32(1.0f, 0.0f, 0.0f);
  lm2_v3_f32 result = lm2_v3_project_f32(a, b);
  EXPECT_FLOAT_EQ(result.x, 3.0f);
  EXPECT_FLOAT_EQ(result.y, 0.0f);
  EXPECT_FLOAT_EQ(result.z, 0.0f);
}
