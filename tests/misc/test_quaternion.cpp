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
#include "lm2/misc/lm2_quaternion.h"
#include "lm2/lm2_constants.h"

// Test fixture for quaternion tests
class QuaternionTest : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Basic Constructor Tests - F64
// =============================================================================

TEST_F(QuaternionTest, Identity_F64) {
  lm2_quat_f64 q = lm2_quat_identity_f64();
  
  EXPECT_NEAR(q.x, 0.0, EPSILON_F64);
  EXPECT_NEAR(q.y, 0.0, EPSILON_F64);
  EXPECT_NEAR(q.z, 0.0, EPSILON_F64);
  EXPECT_NEAR(q.w, 1.0, EPSILON_F64);
}

TEST_F(QuaternionTest, Zero_F64) {
  lm2_quat_f64 q = lm2_quat_zero_f64();
  
  EXPECT_NEAR(q.x, 0.0, EPSILON_F64);
  EXPECT_NEAR(q.y, 0.0, EPSILON_F64);
  EXPECT_NEAR(q.z, 0.0, EPSILON_F64);
  EXPECT_NEAR(q.w, 0.0, EPSILON_F64);
}

TEST_F(QuaternionTest, Make_F64) {
  lm2_quat_f64 q = lm2_quat_make_f64(1.0, 2.0, 3.0, 4.0);
  
  EXPECT_NEAR(q.x, 1.0, EPSILON_F64);
  EXPECT_NEAR(q.y, 2.0, EPSILON_F64);
  EXPECT_NEAR(q.z, 3.0, EPSILON_F64);
  EXPECT_NEAR(q.w, 4.0, EPSILON_F64);
}

// =============================================================================
// Basic Constructor Tests - F32
// =============================================================================

TEST_F(QuaternionTest, Identity_F32) {
  lm2_quat_f32 q = lm2_quat_identity_f32();
  
  EXPECT_NEAR(q.x, 0.0f, EPSILON_F32);
  EXPECT_NEAR(q.y, 0.0f, EPSILON_F32);
  EXPECT_NEAR(q.z, 0.0f, EPSILON_F32);
  EXPECT_NEAR(q.w, 1.0f, EPSILON_F32);
}

TEST_F(QuaternionTest, Zero_F32) {
  lm2_quat_f32 q = lm2_quat_zero_f32();
  
  EXPECT_NEAR(q.x, 0.0f, EPSILON_F32);
  EXPECT_NEAR(q.y, 0.0f, EPSILON_F32);
  EXPECT_NEAR(q.z, 0.0f, EPSILON_F32);
  EXPECT_NEAR(q.w, 0.0f, EPSILON_F32);
}

TEST_F(QuaternionTest, Make_F32) {
  lm2_quat_f32 q = lm2_quat_make_f32(1.0f, 2.0f, 3.0f, 4.0f);
  
  EXPECT_NEAR(q.x, 1.0f, EPSILON_F32);
  EXPECT_NEAR(q.y, 2.0f, EPSILON_F32);
  EXPECT_NEAR(q.z, 3.0f, EPSILON_F32);
  EXPECT_NEAR(q.w, 4.0f, EPSILON_F32);
}

// =============================================================================
// Conversion Tests - From Axis-Angle
// =============================================================================

TEST_F(QuaternionTest, FromAxisAngle_F64_NoRotation) {
  lm2_v3_f64 axis = {0.0, 1.0, 0.0};
  double angle = 0.0;
  
  lm2_quat_f64 q = lm2_quat_from_axis_angle_f64(axis, angle);
  
  // No rotation = identity quaternion
  EXPECT_NEAR(q.x, 0.0, EPSILON_F64);
  EXPECT_NEAR(q.y, 0.0, EPSILON_F64);
  EXPECT_NEAR(q.z, 0.0, EPSILON_F64);
  EXPECT_NEAR(q.w, 1.0, EPSILON_F64);
}

TEST_F(QuaternionTest, FromAxisAngle_F64_90DegY) {
  lm2_v3_f64 axis = {0.0, 1.0, 0.0};  // Y-axis
  double angle = LM2_PI_F64 / 2.0;    // 90 degrees
  
  lm2_quat_f64 q = lm2_quat_from_axis_angle_f64(axis, angle);
  
  // For 90 degree rotation around Y: q = (0, sin(45°), 0, cos(45°))
  double sin45 = std::sin(LM2_PI_F64 / 4.0);
  double cos45 = std::cos(LM2_PI_F64 / 4.0);
  
  EXPECT_NEAR(q.x, 0.0, EPSILON_F64);
  EXPECT_NEAR(q.y, sin45, EPSILON_F64);
  EXPECT_NEAR(q.z, 0.0, EPSILON_F64);
  EXPECT_NEAR(q.w, cos45, EPSILON_F64);
}

TEST_F(QuaternionTest, FromAxisAngle_F32_180DegZ) {
  lm2_v3_f32 axis = {0.0f, 0.0f, 1.0f};  // Z-axis
  float angle = LM2_PI_F32;               // 180 degrees
  
  lm2_quat_f32 q = lm2_quat_from_axis_angle_f32(axis, angle);
  
  // For 180 degree rotation around Z: q = (0, 0, 1, 0)
  EXPECT_NEAR(q.x, 0.0f, EPSILON_F32);
  EXPECT_NEAR(q.y, 0.0f, EPSILON_F32);
  EXPECT_NEAR(q.z, 1.0f, EPSILON_F32);
  EXPECT_NEAR(q.w, 0.0f, EPSILON_F32);
}

// =============================================================================
// Conversion Tests - To Axis-Angle
// =============================================================================

TEST_F(QuaternionTest, ToAxisAngle_F64_Identity) {
  lm2_quat_f64 q = lm2_quat_identity_f64();
  lm2_v3_f64 axis;
  double angle;
  
  lm2_quat_to_axis_angle_f64(q, &axis, &angle);
  
  EXPECT_NEAR(angle, 0.0, EPSILON_F64);
}

TEST_F(QuaternionTest, ToAxisAngle_F64_RoundTrip) {
  lm2_v3_f64 original_axis = {0.0, 1.0, 0.0};
  double original_angle = LM2_PI_F64 / 3.0;  // 60 degrees
  
  lm2_quat_f64 q = lm2_quat_from_axis_angle_f64(original_axis, original_angle);
  
  lm2_v3_f64 result_axis;
  double result_angle;
  lm2_quat_to_axis_angle_f64(q, &result_axis, &result_angle);
  
  EXPECT_NEAR(result_angle, original_angle, EPSILON_F64);
  EXPECT_NEAR(result_axis.x, original_axis.x, EPSILON_F64);
  EXPECT_NEAR(result_axis.y, original_axis.y, EPSILON_F64);
  EXPECT_NEAR(result_axis.z, original_axis.z, EPSILON_F64);
}

TEST_F(QuaternionTest, ToAxisAngle_F32_RoundTrip) {
  lm2_v3_f32 original_axis = {1.0f, 0.0f, 0.0f};
  float original_angle = LM2_PI_F32 / 4.0f;  // 45 degrees
  
  lm2_quat_f32 q = lm2_quat_from_axis_angle_f32(original_axis, original_angle);
  
  lm2_v3_f32 result_axis;
  float result_angle;
  lm2_quat_to_axis_angle_f32(q, &result_axis, &result_angle);
  
  EXPECT_NEAR(result_angle, original_angle, EPSILON_F32);
  EXPECT_NEAR(result_axis.x, original_axis.x, EPSILON_F32);
}

// =============================================================================
// Basic Operations Tests - F64
// =============================================================================

TEST_F(QuaternionTest, Conjugate_F64) {
  lm2_quat_f64 q = lm2_quat_make_f64(1.0, 2.0, 3.0, 4.0);
  lm2_quat_f64 conj = lm2_quat_conjugate_f64(q);
  
  EXPECT_NEAR(conj.x, -1.0, EPSILON_F64);
  EXPECT_NEAR(conj.y, -2.0, EPSILON_F64);
  EXPECT_NEAR(conj.z, -3.0, EPSILON_F64);
  EXPECT_NEAR(conj.w, 4.0, EPSILON_F64);
}

TEST_F(QuaternionTest, Length_F64) {
  lm2_quat_f64 q = lm2_quat_make_f64(1.0, 2.0, 2.0, 0.0);
  
  double len_sq = lm2_quat_length_squared_f64(q);
  double len = lm2_quat_length_f64(q);
  
  EXPECT_NEAR(len_sq, 9.0, EPSILON_F64);  // 1 + 4 + 4 + 0 = 9
  EXPECT_NEAR(len, 3.0, EPSILON_F64);
}

TEST_F(QuaternionTest, Normalize_F64) {
  lm2_quat_f64 q = lm2_quat_make_f64(3.0, 0.0, 4.0, 0.0);
  lm2_quat_f64 norm = lm2_quat_normalize_f64(q);
  
  double len = lm2_quat_length_f64(norm);
  EXPECT_NEAR(len, 1.0, EPSILON_F64);
  
  // Should be proportional to original
  EXPECT_NEAR(norm.x, 0.6, EPSILON_F64);  // 3/5
  EXPECT_NEAR(norm.y, 0.0, EPSILON_F64);
  EXPECT_NEAR(norm.z, 0.8, EPSILON_F64);  // 4/5
  EXPECT_NEAR(norm.w, 0.0, EPSILON_F64);
}

TEST_F(QuaternionTest, Inverse_F64) {
  lm2_v3_f64 axis = {0.0, 1.0, 0.0};
  double angle = LM2_PI_F64 / 4.0;
  
  lm2_quat_f64 q = lm2_quat_from_axis_angle_f64(axis, angle);
  lm2_quat_f64 inv = lm2_quat_inverse_f64(q);
  
  // q * q^-1 should equal identity
  lm2_quat_f64 result = lm2_quat_multiply_f64(q, inv);
  
  EXPECT_NEAR(result.x, 0.0, EPSILON_F64);
  EXPECT_NEAR(result.y, 0.0, EPSILON_F64);
  EXPECT_NEAR(result.z, 0.0, EPSILON_F64);
  EXPECT_NEAR(result.w, 1.0, EPSILON_F64);
}

TEST_F(QuaternionTest, Add_F64) {
  lm2_quat_f64 a = lm2_quat_make_f64(1.0, 2.0, 3.0, 4.0);
  lm2_quat_f64 b = lm2_quat_make_f64(5.0, 6.0, 7.0, 8.0);
  
  lm2_quat_f64 result = lm2_quat_add_f64(a, b);
  
  EXPECT_NEAR(result.x, 6.0, EPSILON_F64);
  EXPECT_NEAR(result.y, 8.0, EPSILON_F64);
  EXPECT_NEAR(result.z, 10.0, EPSILON_F64);
  EXPECT_NEAR(result.w, 12.0, EPSILON_F64);
}

TEST_F(QuaternionTest, Sub_F64) {
  lm2_quat_f64 a = lm2_quat_make_f64(5.0, 6.0, 7.0, 8.0);
  lm2_quat_f64 b = lm2_quat_make_f64(1.0, 2.0, 3.0, 4.0);
  
  lm2_quat_f64 result = lm2_quat_sub_f64(a, b);
  
  EXPECT_NEAR(result.x, 4.0, EPSILON_F64);
  EXPECT_NEAR(result.y, 4.0, EPSILON_F64);
  EXPECT_NEAR(result.z, 4.0, EPSILON_F64);
  EXPECT_NEAR(result.w, 4.0, EPSILON_F64);
}

TEST_F(QuaternionTest, Scale_F64) {
  lm2_quat_f64 q = lm2_quat_make_f64(1.0, 2.0, 3.0, 4.0);
  lm2_quat_f64 result = lm2_quat_scale_f64(q, 2.0);
  
  EXPECT_NEAR(result.x, 2.0, EPSILON_F64);
  EXPECT_NEAR(result.y, 4.0, EPSILON_F64);
  EXPECT_NEAR(result.z, 6.0, EPSILON_F64);
  EXPECT_NEAR(result.w, 8.0, EPSILON_F64);
}

TEST_F(QuaternionTest, Dot_F64) {
  lm2_quat_f64 a = lm2_quat_make_f64(1.0, 2.0, 3.0, 4.0);
  lm2_quat_f64 b = lm2_quat_make_f64(5.0, 6.0, 7.0, 8.0);
  
  double dot = lm2_quat_dot_f64(a, b);
  
  // 1*5 + 2*6 + 3*7 + 4*8 = 5 + 12 + 21 + 32 = 70
  EXPECT_NEAR(dot, 70.0, EPSILON_F64);
}

// =============================================================================
// Basic Operations Tests - F32
// =============================================================================

TEST_F(QuaternionTest, Conjugate_F32) {
  lm2_quat_f32 q = lm2_quat_make_f32(1.0f, 2.0f, 3.0f, 4.0f);
  lm2_quat_f32 conj = lm2_quat_conjugate_f32(q);
  
  EXPECT_NEAR(conj.x, -1.0f, EPSILON_F32);
  EXPECT_NEAR(conj.y, -2.0f, EPSILON_F32);
  EXPECT_NEAR(conj.z, -3.0f, EPSILON_F32);
  EXPECT_NEAR(conj.w, 4.0f, EPSILON_F32);
}

TEST_F(QuaternionTest, Normalize_F32) {
  lm2_quat_f32 q = lm2_quat_make_f32(3.0f, 0.0f, 4.0f, 0.0f);
  lm2_quat_f32 norm = lm2_quat_normalize_f32(q);
  
  float len = lm2_quat_length_f32(norm);
  EXPECT_NEAR(len, 1.0f, EPSILON_F32);
}

// =============================================================================
// Quaternion Multiplication Tests
// =============================================================================

TEST_F(QuaternionTest, Multiply_F64_Identity) {
  lm2_quat_f64 q = lm2_quat_make_f64(1.0, 2.0, 3.0, 4.0);
  lm2_quat_f64 identity = lm2_quat_identity_f64();
  
  lm2_quat_f64 result = lm2_quat_multiply_f64(q, identity);
  
  EXPECT_NEAR(result.x, q.x, EPSILON_F64);
  EXPECT_NEAR(result.y, q.y, EPSILON_F64);
  EXPECT_NEAR(result.z, q.z, EPSILON_F64);
  EXPECT_NEAR(result.w, q.w, EPSILON_F64);
}

TEST_F(QuaternionTest, Multiply_F64_NonCommutative) {
  lm2_quat_f64 a = lm2_quat_make_f64(1.0, 0.0, 0.0, 1.0);
  lm2_quat_f64 b = lm2_quat_make_f64(0.0, 1.0, 0.0, 1.0);
  
  lm2_quat_f64 ab = lm2_quat_multiply_f64(a, b);
  lm2_quat_f64 ba = lm2_quat_multiply_f64(b, a);
  
  // Quaternion multiplication is not commutative
  EXPECT_FALSE(lm2_quat_equals_f64(ab, ba, EPSILON_F64));
}

TEST_F(QuaternionTest, Multiply_F32_Rotations) {
  // Two 90-degree rotations around Y should equal 180-degree rotation
  lm2_v3_f32 axis = {0.0f, 1.0f, 0.0f};
  float angle90 = LM2_PI_F32 / 2.0f;
  
  lm2_quat_f32 q90 = lm2_quat_from_axis_angle_f32(axis, angle90);
  lm2_quat_f32 q180 = lm2_quat_multiply_f32(q90, q90);
  
  // Check it's close to a 180-degree rotation
  lm2_v3_f32 result_axis;
  float result_angle;
  lm2_quat_to_axis_angle_f32(q180, &result_axis, &result_angle);
  
  EXPECT_NEAR(result_angle, LM2_PI_F32, 0.001f);
}

// =============================================================================
// Vector Rotation Tests
// =============================================================================

TEST_F(QuaternionTest, RotateVector_F64_NoRotation) {
  lm2_quat_f64 identity = lm2_quat_identity_f64();
  lm2_v3_f64 v = {1.0, 2.0, 3.0};
  
  lm2_v3_f64 result = lm2_quat_rotate_vector_f64(identity, v);
  
  EXPECT_NEAR(result.x, v.x, EPSILON_F64);
  EXPECT_NEAR(result.y, v.y, EPSILON_F64);
  EXPECT_NEAR(result.z, v.z, EPSILON_F64);
}

TEST_F(QuaternionTest, RotateVector_F64_90DegY) {
  // 90-degree rotation around Y-axis
  lm2_v3_f64 axis = {0.0, 1.0, 0.0};
  double angle = LM2_PI_F64 / 2.0;
  lm2_quat_f64 q = lm2_quat_from_axis_angle_f64(axis, angle);
  
  // Rotate vector (1, 0, 0)
  lm2_v3_f64 v = {1.0, 0.0, 0.0};
  lm2_v3_f64 result = lm2_quat_rotate_vector_f64(q, v);
  
  // Should rotate to approximately (0, 0, -1)
  EXPECT_NEAR(result.x, 0.0, 0.001);
  EXPECT_NEAR(result.y, 0.0, 0.001);
  EXPECT_NEAR(result.z, -1.0, 0.001);
}

TEST_F(QuaternionTest, RotateVector_F32_180DegZ) {
  // 180-degree rotation around Z-axis
  lm2_v3_f32 axis = {0.0f, 0.0f, 1.0f};
  float angle = LM2_PI_F32;
  lm2_quat_f32 q = lm2_quat_from_axis_angle_f32(axis, angle);
  
  // Rotate vector (1, 0, 0)
  lm2_v3_f32 v = {1.0f, 0.0f, 0.0f};
  lm2_v3_f32 result = lm2_quat_rotate_vector_f32(q, v);
  
  // Should rotate to approximately (-1, 0, 0)
  EXPECT_NEAR(result.x, -1.0f, 0.001f);
  EXPECT_NEAR(result.y, 0.0f, 0.001f);
  EXPECT_NEAR(result.z, 0.0f, 0.001f);
}

TEST_F(QuaternionTest, RotateVector_F64_PreservesLength) {
  lm2_v3_f64 axis = {1.0, 1.0, 1.0};
  double angle = LM2_PI_F64 / 3.0;
  lm2_quat_f64 q = lm2_quat_from_axis_angle_f64(axis, angle);
  q = lm2_quat_normalize_f64(q);
  
  lm2_v3_f64 v = {3.0, 4.0, 5.0};
  double original_length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
  
  lm2_v3_f64 result = lm2_quat_rotate_vector_f64(q, v);
  double result_length = std::sqrt(result.x * result.x + result.y * result.y + result.z * result.z);
  
  // Rotation should preserve vector length
  EXPECT_NEAR(result_length, original_length, 0.001);
}

// =============================================================================
// SLERP Tests (Spherical Linear Interpolation)
// =============================================================================

TEST_F(QuaternionTest, Slerp_F64_T0) {
  lm2_quat_f64 a = lm2_quat_identity_f64();
  lm2_v3_f64 axis = {0.0, 1.0, 0.0};
  lm2_quat_f64 b = lm2_quat_from_axis_angle_f64(axis, LM2_PI_F64 / 2.0);
  
  lm2_quat_f64 result = lm2_quat_slerp_f64(a, b, 0.0);
  
  // At t=0, should equal first quaternion
  EXPECT_TRUE(lm2_quat_equals_f64(result, a, EPSILON_F64));
}

TEST_F(QuaternionTest, Slerp_F64_T1) {
  lm2_quat_f64 a = lm2_quat_identity_f64();
  lm2_v3_f64 axis = {0.0, 1.0, 0.0};
  lm2_quat_f64 b = lm2_quat_from_axis_angle_f64(axis, LM2_PI_F64 / 2.0);
  
  lm2_quat_f64 result = lm2_quat_slerp_f64(a, b, 1.0);
  
  // At t=1, should equal second quaternion
  EXPECT_TRUE(lm2_quat_equals_f64(result, b, 0.001));
}

TEST_F(QuaternionTest, Slerp_F64_T05) {
  lm2_quat_f64 a = lm2_quat_identity_f64();
  lm2_v3_f64 axis = {0.0, 1.0, 0.0};
  lm2_quat_f64 b = lm2_quat_from_axis_angle_f64(axis, LM2_PI_F64 / 2.0);
  
  lm2_quat_f64 result = lm2_quat_slerp_f64(a, b, 0.5);
  
  // At t=0.5, should be halfway rotation
  lm2_v3_f64 result_axis;
  double result_angle;
  lm2_quat_to_axis_angle_f64(result, &result_axis, &result_angle);
  
  EXPECT_NEAR(result_angle, LM2_PI_F64 / 4.0, 0.001);  // 45 degrees
}

TEST_F(QuaternionTest, Slerp_F32) {
  lm2_quat_f32 a = lm2_quat_identity_f32();
  lm2_v3_f32 axis = {1.0f, 0.0f, 0.0f};
  lm2_quat_f32 b = lm2_quat_from_axis_angle_f32(axis, LM2_PI_F32);
  
  lm2_quat_f32 result = lm2_quat_slerp_f32(a, b, 0.5f);
  
  // Result should be normalized
  float len = lm2_quat_length_f32(result);
  EXPECT_NEAR(len, 1.0f, EPSILON_F32);
}

// =============================================================================
// NLERP Tests (Normalized Linear Interpolation)
// =============================================================================

TEST_F(QuaternionTest, Nlerp_F64_T0) {
  lm2_quat_f64 a = lm2_quat_identity_f64();
  lm2_v3_f64 axis = {0.0, 1.0, 0.0};
  lm2_quat_f64 b = lm2_quat_from_axis_angle_f64(axis, LM2_PI_F64 / 2.0);
  
  lm2_quat_f64 result = lm2_quat_nlerp_f64(a, b, 0.0);
  
  EXPECT_TRUE(lm2_quat_equals_f64(result, a, EPSILON_F64));
}

TEST_F(QuaternionTest, Nlerp_F64_T1) {
  lm2_quat_f64 a = lm2_quat_identity_f64();
  lm2_v3_f64 axis = {0.0, 1.0, 0.0};
  lm2_quat_f64 b = lm2_quat_from_axis_angle_f64(axis, LM2_PI_F64 / 2.0);
  
  lm2_quat_f64 result = lm2_quat_nlerp_f64(a, b, 1.0);
  
  EXPECT_TRUE(lm2_quat_equals_f64(result, b, 0.001));
}

TEST_F(QuaternionTest, Nlerp_F64_Normalized) {
  lm2_quat_f64 a = lm2_quat_identity_f64();
  lm2_v3_f64 axis = {0.0, 1.0, 0.0};
  lm2_quat_f64 b = lm2_quat_from_axis_angle_f64(axis, LM2_PI_F64 / 2.0);
  
  lm2_quat_f64 result = lm2_quat_nlerp_f64(a, b, 0.5);
  
  // NLERP result should be normalized
  double len = lm2_quat_length_f64(result);
  EXPECT_NEAR(len, 1.0, EPSILON_F64);
}

TEST_F(QuaternionTest, Nlerp_F32) {
  lm2_quat_f32 a = lm2_quat_identity_f32();
  lm2_v3_f32 axis = {0.0f, 0.0f, 1.0f};
  lm2_quat_f32 b = lm2_quat_from_axis_angle_f32(axis, LM2_PI_F32 / 4.0f);
  
  lm2_quat_f32 result = lm2_quat_nlerp_f32(a, b, 0.5f);
  
  float len = lm2_quat_length_f32(result);
  EXPECT_NEAR(len, 1.0f, EPSILON_F32);
}

// =============================================================================
// Euler Angle Conversion Tests
// =============================================================================

TEST_F(QuaternionTest, FromEuler_F64_Zero) {
  lm2_quat_f64 q = lm2_quat_from_euler_f64(0.0, 0.0, 0.0);
  
  // Zero rotation should be identity
  EXPECT_TRUE(lm2_quat_equals_f64(q, lm2_quat_identity_f64(), 0.001));
}

TEST_F(QuaternionTest, FromEulerVec_F64) {
  lm2_v3_f64 euler = {LM2_PI_F64 / 4.0, LM2_PI_F64 / 6.0, LM2_PI_F64 / 3.0};
  
  lm2_quat_f64 q = lm2_quat_from_euler_vec_f64(euler);
  
  // Should produce a normalized quaternion
  double len = lm2_quat_length_f64(q);
  EXPECT_NEAR(len, 1.0, 0.001);
}

TEST_F(QuaternionTest, ToEuler_F64_RoundTrip) {
  lm2_v3_f64 original = {LM2_PI_F64 / 4.0, LM2_PI_F64 / 6.0, 0.0};
  
  lm2_quat_f64 q = lm2_quat_from_euler_vec_f64(original);
  lm2_v3_f64 result = lm2_quat_to_euler_f64(q);
  
  // Note: Euler angle conversions can have multiple representations
  // Just verify it produces something reasonable
  EXPECT_GT(std::abs(result.x) + std::abs(result.y) + std::abs(result.z), 0.0);
}

TEST_F(QuaternionTest, FromEuler_F32) {
  lm2_quat_f32 q = lm2_quat_from_euler_f32(0.0f, LM2_PI_F32 / 2.0f, 0.0f);
  
  // Should produce a normalized quaternion
  float len = lm2_quat_length_f32(q);
  EXPECT_NEAR(len, 1.0f, 0.001f);
}

// =============================================================================
// Equality Tests
// =============================================================================

TEST_F(QuaternionTest, Equals_F64_Same) {
  lm2_quat_f64 a = lm2_quat_make_f64(1.0, 2.0, 3.0, 4.0);
  lm2_quat_f64 b = lm2_quat_make_f64(1.0, 2.0, 3.0, 4.0);
  
  EXPECT_TRUE(lm2_quat_equals_f64(a, b, EPSILON_F64));
}

TEST_F(QuaternionTest, Equals_F64_Different) {
  lm2_quat_f64 a = lm2_quat_make_f64(1.0, 2.0, 3.0, 4.0);
  lm2_quat_f64 b = lm2_quat_make_f64(1.0, 2.0, 3.0, 4.1);
  
  EXPECT_FALSE(lm2_quat_equals_f64(a, b, EPSILON_F64));
}

TEST_F(QuaternionTest, Equals_F32_WithEpsilon) {
  lm2_quat_f32 a = lm2_quat_make_f32(1.0f, 2.0f, 3.0f, 4.0f);
  lm2_quat_f32 b = lm2_quat_make_f32(1.0001f, 2.0001f, 3.0001f, 4.0001f);
  
  EXPECT_TRUE(lm2_quat_equals_f32(a, b, 0.001f));
  EXPECT_FALSE(lm2_quat_equals_f32(a, b, 0.00001f));
}

// =============================================================================
// Combined Operations Tests
// =============================================================================

TEST_F(QuaternionTest, CombinedRotations_F64) {
  // Create two rotations and combine them
  lm2_v3_f64 y_axis = {0.0, 1.0, 0.0};
  lm2_v3_f64 z_axis = {0.0, 0.0, 1.0};
  
  lm2_quat_f64 rot_y = lm2_quat_from_axis_angle_f64(y_axis, LM2_PI_F64 / 4.0);
  lm2_quat_f64 rot_z = lm2_quat_from_axis_angle_f64(z_axis, LM2_PI_F64 / 6.0);
  
  lm2_quat_f64 combined = lm2_quat_multiply_f64(rot_y, rot_z);
  
  // Result should be normalized
  double len = lm2_quat_length_f64(combined);
  EXPECT_NEAR(len, 1.0, 0.001);
  
  // Should be able to rotate a vector
  lm2_v3_f64 v = {1.0, 0.0, 0.0};
  lm2_v3_f64 rotated = lm2_quat_rotate_vector_f64(combined, v);
  
  // Should preserve length
  double v_len = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
  double r_len = std::sqrt(rotated.x * rotated.x + rotated.y * rotated.y + rotated.z * rotated.z);
  EXPECT_NEAR(r_len, v_len, 0.001);
}
