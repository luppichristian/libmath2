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
#include "lm2/matrices/lm2_matrix3x3.h"

// Test fixture for matrix3x3 tests
class Matrix3x3Test : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Creation and Initialization Tests (f64)
// =============================================================================

TEST_F(Matrix3x3Test, Identity_F64) {
  lm2_m3x3_f64 m = lm2_m3x3_identity_f64();
  EXPECT_DOUBLE_EQ(m.m00, 1.0);
  EXPECT_DOUBLE_EQ(m.m11, 1.0);
  EXPECT_DOUBLE_EQ(m.m22, 1.0);
  EXPECT_DOUBLE_EQ(m.m01, 0.0);
  EXPECT_DOUBLE_EQ(m.m02, 0.0);
  EXPECT_DOUBLE_EQ(m.m10, 0.0);
  EXPECT_DOUBLE_EQ(m.m12, 0.0);
  EXPECT_DOUBLE_EQ(m.m20, 0.0);
  EXPECT_DOUBLE_EQ(m.m21, 0.0);
}

TEST_F(Matrix3x3Test, Zero_F64) {
  lm2_m3x3_f64 m = lm2_m3x3_zero_f64();
  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(m.e[i], 0.0);
  }
}

TEST_F(Matrix3x3Test, Make_F64) {
  lm2_m3x3_f64 m = lm2_m3x3_make_f64(
      1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
  EXPECT_DOUBLE_EQ(m.m00, 1.0);
  EXPECT_DOUBLE_EQ(m.m01, 2.0);
  EXPECT_DOUBLE_EQ(m.m02, 3.0);
  EXPECT_DOUBLE_EQ(m.m10, 4.0);
  EXPECT_DOUBLE_EQ(m.m11, 5.0);
  EXPECT_DOUBLE_EQ(m.m12, 6.0);
  EXPECT_DOUBLE_EQ(m.m20, 7.0);
  EXPECT_DOUBLE_EQ(m.m21, 8.0);
  EXPECT_DOUBLE_EQ(m.m22, 9.0);
}

// =============================================================================
// Transformation Creation Tests (f64)
// =============================================================================

TEST_F(Matrix3x3Test, Scale_F64) {
  lm2_v2_f64 scale = {2.0, 3.0};
  lm2_m3x3_f64 m = lm2_m3x3_scale_f64(scale);

  EXPECT_DOUBLE_EQ(m.m00, 2.0);
  EXPECT_DOUBLE_EQ(m.m11, 3.0);
  EXPECT_DOUBLE_EQ(m.m22, 1.0);
  EXPECT_DOUBLE_EQ(m.m01, 0.0);
  EXPECT_DOUBLE_EQ(m.m10, 0.0);
}

TEST_F(Matrix3x3Test, ScaleUniform_F64) {
  lm2_m3x3_f64 m = lm2_m3x3_scale_uniform_f64(2.5);

  EXPECT_DOUBLE_EQ(m.m00, 2.5);
  EXPECT_DOUBLE_EQ(m.m11, 2.5);
  EXPECT_DOUBLE_EQ(m.m22, 1.0);
}

TEST_F(Matrix3x3Test, Translate_F64) {
  lm2_v2_f64 translation = {10.0, 20.0};
  lm2_m3x3_f64 m = lm2_m3x3_translate_f64(translation);

  EXPECT_DOUBLE_EQ(m.m00, 1.0);
  EXPECT_DOUBLE_EQ(m.m11, 1.0);
  EXPECT_DOUBLE_EQ(m.m22, 1.0);
  EXPECT_DOUBLE_EQ(m.m02, 10.0);
  EXPECT_DOUBLE_EQ(m.m12, 20.0);
}

TEST_F(Matrix3x3Test, Rotate90Degrees_F64) {
  lm2_m3x3_f64 m = lm2_m3x3_rotate_f64(LM2_PI_F64 / 2.0);

  EXPECT_NEAR(m.m00, 0.0, EPSILON_F64);
  EXPECT_NEAR(m.m01, -1.0, EPSILON_F64);
  EXPECT_NEAR(m.m10, 1.0, EPSILON_F64);
  EXPECT_NEAR(m.m11, 0.0, EPSILON_F64);
  EXPECT_DOUBLE_EQ(m.m22, 1.0);
}

TEST_F(Matrix3x3Test, RotateAroundPivot_F64) {
  lm2_v2_f64 pivot = {5.0, 5.0};
  lm2_m3x3_f64 m = lm2_m3x3_rotate_around_pivot_f64(LM2_PI_F64, pivot);

  // After 180 degree rotation around (5, 5), point (5, 5) should stay at (5, 5)
  lm2_v2_f64 p = {5.0, 5.0};
  lm2_v2_f64 result = lm2_m3x3_transform_point_f64(m, p);

  EXPECT_NEAR(result.x, 5.0, EPSILON_F64);
  EXPECT_NEAR(result.y, 5.0, EPSILON_F64);
}

TEST_F(Matrix3x3Test, ScaleTranslate_F64) {
  lm2_v2_f64 scale = {2.0, 3.0};
  lm2_v2_f64 translation = {10.0, 20.0};
  lm2_m3x3_f64 m = lm2_m3x3_scale_translate_f64(scale, translation);

  EXPECT_DOUBLE_EQ(m.m00, 2.0);
  EXPECT_DOUBLE_EQ(m.m11, 3.0);
  EXPECT_DOUBLE_EQ(m.m02, 10.0);
  EXPECT_DOUBLE_EQ(m.m12, 20.0);
}

// =============================================================================
// Matrix Operations Tests (f64)
// =============================================================================

TEST_F(Matrix3x3Test, Multiply_F64) {
  lm2_m3x3_f64 a = lm2_m3x3_translate_f64({10.0, 20.0});
  lm2_m3x3_f64 b = lm2_m3x3_scale_f64({2.0, 3.0});
  lm2_m3x3_f64 result = lm2_m3x3_multiply_f64(a, b);

  lm2_v2_f64 p = {1.0, 1.0};
  lm2_v2_f64 transformed = lm2_m3x3_transform_point_f64(result, p);

  EXPECT_NEAR(transformed.x, 12.0, EPSILON_F64);
  EXPECT_NEAR(transformed.y, 23.0, EPSILON_F64);
}

TEST_F(Matrix3x3Test, Transpose_F64) {
  lm2_m3x3_f64 m = lm2_m3x3_make_f64(
      1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
  lm2_m3x3_f64 mt = lm2_m3x3_transpose_f64(m);

  EXPECT_DOUBLE_EQ(mt.m00, 1.0);
  EXPECT_DOUBLE_EQ(mt.m01, 4.0);
  EXPECT_DOUBLE_EQ(mt.m02, 7.0);
  EXPECT_DOUBLE_EQ(mt.m10, 2.0);
  EXPECT_DOUBLE_EQ(mt.m11, 5.0);
  EXPECT_DOUBLE_EQ(mt.m12, 8.0);
  EXPECT_DOUBLE_EQ(mt.m20, 3.0);
  EXPECT_DOUBLE_EQ(mt.m21, 6.0);
  EXPECT_DOUBLE_EQ(mt.m22, 9.0);
}

TEST_F(Matrix3x3Test, Determinant_F64) {
  lm2_m3x3_f64 m = lm2_m3x3_make_f64(
      1.0, 2.0, 3.0, 0.0, 1.0, 4.0, 5.0, 6.0, 0.0);
  double det = lm2_m3x3_determinant_f64(m);

  // det = 1*(1*0 - 4*6) - 2*(0*0 - 4*5) + 3*(0*6 - 1*5)
  //     = 1*(-24) - 2*(-20) + 3*(-5)
  //     = -24 + 40 - 15 = 1
  EXPECT_DOUBLE_EQ(det, 1.0);
}

TEST_F(Matrix3x3Test, Trace_F64) {
  lm2_m3x3_f64 m = lm2_m3x3_make_f64(
      1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
  double trace = lm2_m3x3_trace_f64(m);

  EXPECT_DOUBLE_EQ(trace, 15.0);  // 1 + 5 + 9 = 15
}

TEST_F(Matrix3x3Test, Inverse_F64) {
  lm2_m3x3_f64 m = lm2_m3x3_scale_translate_f64({2.0, 3.0}, {10.0, 20.0});
  lm2_m3x3_f64 inv = lm2_m3x3_inverse_f64(m);
  lm2_m3x3_f64 identity = lm2_m3x3_multiply_f64(m, inv);

  EXPECT_NEAR(identity.m00, 1.0, EPSILON_F64);
  EXPECT_NEAR(identity.m11, 1.0, EPSILON_F64);
  EXPECT_NEAR(identity.m22, 1.0, EPSILON_F64);
  EXPECT_NEAR(identity.m01, 0.0, EPSILON_F64);
  EXPECT_NEAR(identity.m02, 0.0, EPSILON_F64);
  EXPECT_NEAR(identity.m10, 0.0, EPSILON_F64);
  EXPECT_NEAR(identity.m12, 0.0, EPSILON_F64);
  EXPECT_NEAR(identity.m20, 0.0, EPSILON_F64);
  EXPECT_NEAR(identity.m21, 0.0, EPSILON_F64);
}

// =============================================================================
// Transformation Tests (f64)
// =============================================================================

TEST_F(Matrix3x3Test, TransformPoint_F64) {
  lm2_m3x3_f64 m = lm2_m3x3_translate_f64({10.0, 20.0});
  lm2_v2_f64 p = {5.0, 8.0};
  lm2_v2_f64 result = lm2_m3x3_transform_point_f64(m, p);

  EXPECT_DOUBLE_EQ(result.x, 15.0);
  EXPECT_DOUBLE_EQ(result.y, 28.0);
}

TEST_F(Matrix3x3Test, TransformVector_F64) {
  lm2_m3x3_f64 m = lm2_m3x3_translate_f64({10.0, 20.0});
  lm2_v2_f64 v = {5.0, 8.0};
  lm2_v2_f64 result = lm2_m3x3_transform_vector_f64(m, v);

  // Translation should not affect vectors
  EXPECT_DOUBLE_EQ(result.x, 5.0);
  EXPECT_DOUBLE_EQ(result.y, 8.0);
}

TEST_F(Matrix3x3Test, Transform_F64) {
  lm2_m3x3_f64 m = lm2_m3x3_scale_f64({2.0, 3.0});
  lm2_v3_f64 v = {1.0, 2.0, 3.0};
  lm2_v3_f64 result = lm2_m3x3_transform_f64(m, v);

  EXPECT_DOUBLE_EQ(result.x, 2.0);
  EXPECT_DOUBLE_EQ(result.y, 6.0);
  EXPECT_DOUBLE_EQ(result.z, 3.0);
}

TEST_F(Matrix3x3Test, TransformPoints_F64) {
  lm2_m3x3_f64 m = lm2_m3x3_scale_f64({2.0, 2.0});
  lm2_v2_f64 points[3] = {
      {1.0, 1.0},
      {2.0, 2.0},
      {3.0, 3.0}
  };

  lm2_m3x3_transform_points_f64(m, points, 3);

  EXPECT_DOUBLE_EQ(points[0].x, 2.0);
  EXPECT_DOUBLE_EQ(points[0].y, 2.0);
  EXPECT_DOUBLE_EQ(points[1].x, 4.0);
  EXPECT_DOUBLE_EQ(points[1].y, 4.0);
  EXPECT_DOUBLE_EQ(points[2].x, 6.0);
  EXPECT_DOUBLE_EQ(points[2].y, 6.0);
}

TEST_F(Matrix3x3Test, TransformPointsSrcDst_F64) {
  lm2_m3x3_f64 m = lm2_m3x3_scale_f64({2.0, 2.0});
  const lm2_v2_f64 src[2] = {
      {1.0, 1.0},
      {2.0, 2.0}
  };
  lm2_v2_f64 dst[2];

  lm2_m3x3_transform_points_src_dst_f64(m, src, dst, 2);

  EXPECT_DOUBLE_EQ(dst[0].x, 2.0);
  EXPECT_DOUBLE_EQ(dst[0].y, 2.0);
  EXPECT_DOUBLE_EQ(dst[1].x, 4.0);
  EXPECT_DOUBLE_EQ(dst[1].y, 4.0);
}

// =============================================================================
// Extraction Tests (f64)
// =============================================================================

TEST_F(Matrix3x3Test, GetRotation_F64) {
  double angle = LM2_PI_F64 / 3.0;
  lm2_m3x3_f64 m = lm2_m3x3_rotate_f64(angle);
  double extracted = lm2_m3x3_get_rotation_f64(m);

  EXPECT_NEAR(extracted, angle, EPSILON_F64);
}

TEST_F(Matrix3x3Test, GetScale_F64) {
  lm2_v2_f64 scale = {2.0, 3.0};
  lm2_m3x3_f64 m = lm2_m3x3_scale_f64(scale);
  lm2_v2_f64 extracted = lm2_m3x3_get_scale_f64(m);

  EXPECT_DOUBLE_EQ(extracted.x, 2.0);
  EXPECT_DOUBLE_EQ(extracted.y, 3.0);
}

TEST_F(Matrix3x3Test, GetTranslation_F64) {
  lm2_v2_f64 translation = {10.0, 20.0};
  lm2_m3x3_f64 m = lm2_m3x3_translate_f64(translation);
  lm2_v2_f64 extracted = lm2_m3x3_get_translation_f64(m);

  EXPECT_DOUBLE_EQ(extracted.x, 10.0);
  EXPECT_DOUBLE_EQ(extracted.y, 20.0);
}

// =============================================================================
// Creation and Initialization Tests (f32)
// =============================================================================

TEST_F(Matrix3x3Test, Identity_F32) {
  lm2_m3x3_f32 m = lm2_m3x3_identity_f32();
  EXPECT_FLOAT_EQ(m.m00, 1.0f);
  EXPECT_FLOAT_EQ(m.m11, 1.0f);
  EXPECT_FLOAT_EQ(m.m22, 1.0f);
  EXPECT_FLOAT_EQ(m.m01, 0.0f);
  EXPECT_FLOAT_EQ(m.m10, 0.0f);
}

TEST_F(Matrix3x3Test, Zero_F32) {
  lm2_m3x3_f32 m = lm2_m3x3_zero_f32();
  for (int i = 0; i < 9; i++) {
    EXPECT_FLOAT_EQ(m.e[i], 0.0f);
  }
}

TEST_F(Matrix3x3Test, Make_F32) {
  lm2_m3x3_f32 m = lm2_m3x3_make_f32(
      1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
  EXPECT_FLOAT_EQ(m.m00, 1.0f);
  EXPECT_FLOAT_EQ(m.m01, 2.0f);
  EXPECT_FLOAT_EQ(m.m02, 3.0f);
  EXPECT_FLOAT_EQ(m.m10, 4.0f);
  EXPECT_FLOAT_EQ(m.m11, 5.0f);
}

// =============================================================================
// Transformation Creation Tests (f32)
// =============================================================================

TEST_F(Matrix3x3Test, Scale_F32) {
  lm2_v2_f32 scale = {2.0f, 3.0f};
  lm2_m3x3_f32 m = lm2_m3x3_scale_f32(scale);

  EXPECT_FLOAT_EQ(m.m00, 2.0f);
  EXPECT_FLOAT_EQ(m.m11, 3.0f);
  EXPECT_FLOAT_EQ(m.m22, 1.0f);
}

TEST_F(Matrix3x3Test, Translate_F32) {
  lm2_v2_f32 translation = {10.0f, 20.0f};
  lm2_m3x3_f32 m = lm2_m3x3_translate_f32(translation);

  EXPECT_FLOAT_EQ(m.m00, 1.0f);
  EXPECT_FLOAT_EQ(m.m11, 1.0f);
  EXPECT_FLOAT_EQ(m.m22, 1.0f);
  EXPECT_FLOAT_EQ(m.m02, 10.0f);
  EXPECT_FLOAT_EQ(m.m12, 20.0f);
}

TEST_F(Matrix3x3Test, Rotate90Degrees_F32) {
  lm2_m3x3_f32 m = lm2_m3x3_rotate_f32(LM2_PI_F32 / 2.0f);

  EXPECT_NEAR(m.m00, 0.0f, EPSILON_F32);
  EXPECT_NEAR(m.m01, -1.0f, EPSILON_F32);
  EXPECT_NEAR(m.m10, 1.0f, EPSILON_F32);
  EXPECT_NEAR(m.m11, 0.0f, EPSILON_F32);
}

// =============================================================================
// Matrix Operations Tests (f32)
// =============================================================================

TEST_F(Matrix3x3Test, Multiply_F32) {
  lm2_m3x3_f32 a = lm2_m3x3_translate_f32({10.0f, 20.0f});
  lm2_m3x3_f32 b = lm2_m3x3_scale_f32({2.0f, 3.0f});
  lm2_m3x3_f32 result = lm2_m3x3_multiply_f32(a, b);

  lm2_v2_f32 p = {1.0f, 1.0f};
  lm2_v2_f32 transformed = lm2_m3x3_transform_point_f32(result, p);

  EXPECT_NEAR(transformed.x, 12.0f, EPSILON_F32);
  EXPECT_NEAR(transformed.y, 23.0f, EPSILON_F32);
}

TEST_F(Matrix3x3Test, Transpose_F32) {
  lm2_m3x3_f32 m = lm2_m3x3_make_f32(
      1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
  lm2_m3x3_f32 mt = lm2_m3x3_transpose_f32(m);

  EXPECT_FLOAT_EQ(mt.m00, 1.0f);
  EXPECT_FLOAT_EQ(mt.m01, 4.0f);
  EXPECT_FLOAT_EQ(mt.m02, 7.0f);
  EXPECT_FLOAT_EQ(mt.m10, 2.0f);
  EXPECT_FLOAT_EQ(mt.m11, 5.0f);
}

TEST_F(Matrix3x3Test, Determinant_F32) {
  lm2_m3x3_f32 m = lm2_m3x3_make_f32(
      1.0f, 2.0f, 3.0f, 0.0f, 1.0f, 4.0f, 5.0f, 6.0f, 0.0f);
  float det = lm2_m3x3_determinant_f32(m);

  EXPECT_FLOAT_EQ(det, 1.0f);
}

TEST_F(Matrix3x3Test, Trace_F32) {
  lm2_m3x3_f32 m = lm2_m3x3_make_f32(
      1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
  float trace = lm2_m3x3_trace_f32(m);

  EXPECT_FLOAT_EQ(trace, 15.0f);
}

TEST_F(Matrix3x3Test, Inverse_F32) {
  lm2_m3x3_f32 m = lm2_m3x3_scale_translate_f32({2.0f, 3.0f}, {10.0f, 20.0f});
  lm2_m3x3_f32 inv = lm2_m3x3_inverse_f32(m);
  lm2_m3x3_f32 identity = lm2_m3x3_multiply_f32(m, inv);

  EXPECT_NEAR(identity.m00, 1.0f, EPSILON_F32);
  EXPECT_NEAR(identity.m11, 1.0f, EPSILON_F32);
  EXPECT_NEAR(identity.m22, 1.0f, EPSILON_F32);
}

// =============================================================================
// Transformation Tests (f32)
// =============================================================================

TEST_F(Matrix3x3Test, TransformPoint_F32) {
  lm2_m3x3_f32 m = lm2_m3x3_translate_f32({10.0f, 20.0f});
  lm2_v2_f32 p = {5.0f, 8.0f};
  lm2_v2_f32 result = lm2_m3x3_transform_point_f32(m, p);

  EXPECT_FLOAT_EQ(result.x, 15.0f);
  EXPECT_FLOAT_EQ(result.y, 28.0f);
}

TEST_F(Matrix3x3Test, TransformVector_F32) {
  lm2_m3x3_f32 m = lm2_m3x3_translate_f32({10.0f, 20.0f});
  lm2_v2_f32 v = {5.0f, 8.0f};
  lm2_v2_f32 result = lm2_m3x3_transform_vector_f32(m, v);

  EXPECT_FLOAT_EQ(result.x, 5.0f);
  EXPECT_FLOAT_EQ(result.y, 8.0f);
}

TEST_F(Matrix3x3Test, GetRotation_F32) {
  float angle = LM2_PI_F32 / 3.0f;
  lm2_m3x3_f32 m = lm2_m3x3_rotate_f32(angle);
  float extracted = lm2_m3x3_get_rotation_f32(m);

  EXPECT_NEAR(extracted, angle, EPSILON_F32);
}

TEST_F(Matrix3x3Test, GetScale_F32) {
  lm2_v2_f32 scale = {2.0f, 3.0f};
  lm2_m3x3_f32 m = lm2_m3x3_scale_f32(scale);
  lm2_v2_f32 extracted = lm2_m3x3_get_scale_f32(m);

  EXPECT_FLOAT_EQ(extracted.x, 2.0f);
  EXPECT_FLOAT_EQ(extracted.y, 3.0f);
}

TEST_F(Matrix3x3Test, GetTranslation_F32) {
  lm2_v2_f32 translation = {10.0f, 20.0f};
  lm2_m3x3_f32 m = lm2_m3x3_translate_f32(translation);
  lm2_v2_f32 extracted = lm2_m3x3_get_translation_f32(m);

  EXPECT_FLOAT_EQ(extracted.x, 10.0f);
  EXPECT_FLOAT_EQ(extracted.y, 20.0f);
}
