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
#include "lm2/matrices/lm2_matrix4x4.h"

// Test fixture for matrix4x4 tests
class Matrix4x4Test : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Creation and Initialization Tests (f64)
// =============================================================================

TEST_F(Matrix4x4Test, Identity_F64) {
  lm2_m4x4_f64 m = lm2_m4x4_identity_f64();
  EXPECT_DOUBLE_EQ(m.m00, 1.0);
  EXPECT_DOUBLE_EQ(m.m11, 1.0);
  EXPECT_DOUBLE_EQ(m.m22, 1.0);
  EXPECT_DOUBLE_EQ(m.m33, 1.0);
  EXPECT_DOUBLE_EQ(m.m01, 0.0);
  EXPECT_DOUBLE_EQ(m.m02, 0.0);
  EXPECT_DOUBLE_EQ(m.m10, 0.0);
  EXPECT_DOUBLE_EQ(m.m12, 0.0);
}

TEST_F(Matrix4x4Test, Zero_F64) {
  lm2_m4x4_f64 m = lm2_m4x4_zero_f64();
  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(m.e[i], 0.0);
  }
}

TEST_F(Matrix4x4Test, Make_F64) {
  lm2_m4x4_f64 m = lm2_m4x4_make_f64(
      1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0);
  EXPECT_DOUBLE_EQ(m.m00, 1.0);
  EXPECT_DOUBLE_EQ(m.m01, 2.0);
  EXPECT_DOUBLE_EQ(m.m02, 3.0);
  EXPECT_DOUBLE_EQ(m.m03, 4.0);
  EXPECT_DOUBLE_EQ(m.m10, 5.0);
  EXPECT_DOUBLE_EQ(m.m11, 6.0);
  EXPECT_DOUBLE_EQ(m.m12, 7.0);
  EXPECT_DOUBLE_EQ(m.m13, 8.0);
  EXPECT_DOUBLE_EQ(m.m20, 9.0);
  EXPECT_DOUBLE_EQ(m.m21, 10.0);
  EXPECT_DOUBLE_EQ(m.m22, 11.0);
  EXPECT_DOUBLE_EQ(m.m23, 12.0);
  EXPECT_DOUBLE_EQ(m.m30, 13.0);
  EXPECT_DOUBLE_EQ(m.m31, 14.0);
  EXPECT_DOUBLE_EQ(m.m32, 15.0);
  EXPECT_DOUBLE_EQ(m.m33, 16.0);
}

// =============================================================================
// Transformation Creation Tests (f64)
// =============================================================================

TEST_F(Matrix4x4Test, Scale_F64) {
  lm2_v3_f64 scale = {2.0, 3.0, 4.0};
  lm2_m4x4_f64 m = lm2_m4x4_scale_f64(scale);

  EXPECT_DOUBLE_EQ(m.m00, 2.0);
  EXPECT_DOUBLE_EQ(m.m11, 3.0);
  EXPECT_DOUBLE_EQ(m.m22, 4.0);
  EXPECT_DOUBLE_EQ(m.m33, 1.0);
  EXPECT_DOUBLE_EQ(m.m01, 0.0);
  EXPECT_DOUBLE_EQ(m.m10, 0.0);
}

TEST_F(Matrix4x4Test, ScaleUniform_F64) {
  lm2_m4x4_f64 m = lm2_m4x4_scale_uniform_f64(2.5);

  EXPECT_DOUBLE_EQ(m.m00, 2.5);
  EXPECT_DOUBLE_EQ(m.m11, 2.5);
  EXPECT_DOUBLE_EQ(m.m22, 2.5);
  EXPECT_DOUBLE_EQ(m.m33, 1.0);
}

TEST_F(Matrix4x4Test, Translate_F64) {
  lm2_v3_f64 translation = {10.0, 20.0, 30.0};
  lm2_m4x4_f64 m = lm2_m4x4_translate_f64(translation);

  EXPECT_DOUBLE_EQ(m.m00, 1.0);
  EXPECT_DOUBLE_EQ(m.m11, 1.0);
  EXPECT_DOUBLE_EQ(m.m22, 1.0);
  EXPECT_DOUBLE_EQ(m.m33, 1.0);
  EXPECT_DOUBLE_EQ(m.m03, 10.0);
  EXPECT_DOUBLE_EQ(m.m13, 20.0);
  EXPECT_DOUBLE_EQ(m.m23, 30.0);
}

TEST_F(Matrix4x4Test, RotateX90Degrees_F64) {
  lm2_m4x4_f64 m = lm2_m4x4_rotate_x_f64(LM2_PI_F64 / 2.0);

  EXPECT_DOUBLE_EQ(m.m00, 1.0);
  EXPECT_NEAR(m.m11, 0.0, EPSILON_F64);
  EXPECT_NEAR(m.m12, -1.0, EPSILON_F64);
  EXPECT_NEAR(m.m21, 1.0, EPSILON_F64);
  EXPECT_NEAR(m.m22, 0.0, EPSILON_F64);
  EXPECT_DOUBLE_EQ(m.m33, 1.0);
}

TEST_F(Matrix4x4Test, RotateY90Degrees_F64) {
  lm2_m4x4_f64 m = lm2_m4x4_rotate_y_f64(LM2_PI_F64 / 2.0);

  EXPECT_NEAR(m.m00, 0.0, EPSILON_F64);
  EXPECT_NEAR(m.m02, 1.0, EPSILON_F64);
  EXPECT_DOUBLE_EQ(m.m11, 1.0);
  EXPECT_NEAR(m.m20, -1.0, EPSILON_F64);
  EXPECT_NEAR(m.m22, 0.0, EPSILON_F64);
  EXPECT_DOUBLE_EQ(m.m33, 1.0);
}

TEST_F(Matrix4x4Test, RotateZ90Degrees_F64) {
  lm2_m4x4_f64 m = lm2_m4x4_rotate_z_f64(LM2_PI_F64 / 2.0);

  EXPECT_NEAR(m.m00, 0.0, EPSILON_F64);
  EXPECT_NEAR(m.m01, -1.0, EPSILON_F64);
  EXPECT_NEAR(m.m10, 1.0, EPSILON_F64);
  EXPECT_NEAR(m.m11, 0.0, EPSILON_F64);
  EXPECT_DOUBLE_EQ(m.m22, 1.0);
  EXPECT_DOUBLE_EQ(m.m33, 1.0);
}

TEST_F(Matrix4x4Test, RotateAxis_F64) {
  lm2_v3_f64 axis = {0.0, 0.0, 1.0};
  lm2_m4x4_f64 m = lm2_m4x4_rotate_axis_f64(axis, LM2_PI_F64 / 2.0);

  // Rotation around Z-axis
  EXPECT_NEAR(m.m00, 0.0, EPSILON_F64);
  EXPECT_NEAR(m.m01, -1.0, EPSILON_F64);
  EXPECT_NEAR(m.m10, 1.0, EPSILON_F64);
  EXPECT_NEAR(m.m11, 0.0, EPSILON_F64);
}

TEST_F(Matrix4x4Test, ScaleTranslate_F64) {
  lm2_v3_f64 scale = {2.0, 3.0, 4.0};
  lm2_v3_f64 translation = {10.0, 20.0, 30.0};
  lm2_m4x4_f64 m = lm2_m4x4_scale_translate_f64(scale, translation);

  EXPECT_DOUBLE_EQ(m.m00, 2.0);
  EXPECT_DOUBLE_EQ(m.m11, 3.0);
  EXPECT_DOUBLE_EQ(m.m22, 4.0);
  EXPECT_DOUBLE_EQ(m.m03, 10.0);
  EXPECT_DOUBLE_EQ(m.m13, 20.0);
  EXPECT_DOUBLE_EQ(m.m23, 30.0);
}

TEST_F(Matrix4x4Test, WorldTransform_F64) {
  lm2_v3_f64 translation = {10.0, 20.0, 30.0};
  lm2_v3_f64 scale = {2.0, 2.0, 2.0};
  lm2_v3_f64 rotation = {0.0, 0.0, LM2_PI_F64 / 4.0};

  lm2_m4x4_f64 m = lm2_m4x4_world_transform_f64(translation, scale, rotation);

  // Test that origin transforms correctly
  lm2_v3_f64 p = {0.0, 0.0, 0.0};
  lm2_v3_f64 result = lm2_m4x4_transform_point_f64(m, p);

  EXPECT_NEAR(result.x, 10.0, EPSILON_F64);
  EXPECT_NEAR(result.y, 20.0, EPSILON_F64);
  EXPECT_NEAR(result.z, 30.0, EPSILON_F64);
}

// =============================================================================
// Matrix Operations Tests (f64)
// =============================================================================

TEST_F(Matrix4x4Test, Multiply_F64) {
  lm2_m4x4_f64 a = lm2_m4x4_translate_f64({10.0, 20.0, 30.0});
  lm2_m4x4_f64 b = lm2_m4x4_scale_f64({2.0, 3.0, 4.0});
  lm2_m4x4_f64 result = lm2_m4x4_multiply_f64(a, b);

  lm2_v3_f64 p = {1.0, 1.0, 1.0};
  lm2_v3_f64 transformed = lm2_m4x4_transform_point_f64(result, p);

  EXPECT_NEAR(transformed.x, 12.0, EPSILON_F64);
  EXPECT_NEAR(transformed.y, 23.0, EPSILON_F64);
  EXPECT_NEAR(transformed.z, 34.0, EPSILON_F64);
}

TEST_F(Matrix4x4Test, Transpose_F64) {
  lm2_m4x4_f64 m = lm2_m4x4_make_f64(
      1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0);
  lm2_m4x4_f64 mt = lm2_m4x4_transpose_f64(m);

  EXPECT_DOUBLE_EQ(mt.m00, 1.0);
  EXPECT_DOUBLE_EQ(mt.m01, 5.0);
  EXPECT_DOUBLE_EQ(mt.m02, 9.0);
  EXPECT_DOUBLE_EQ(mt.m03, 13.0);
  EXPECT_DOUBLE_EQ(mt.m10, 2.0);
  EXPECT_DOUBLE_EQ(mt.m11, 6.0);
  EXPECT_DOUBLE_EQ(mt.m12, 10.0);
  EXPECT_DOUBLE_EQ(mt.m13, 14.0);
}

TEST_F(Matrix4x4Test, Determinant_F64) {
  lm2_m4x4_f64 m = lm2_m4x4_identity_f64();
  double det = lm2_m4x4_determinant_f64(m);

  EXPECT_DOUBLE_EQ(det, 1.0);
}

TEST_F(Matrix4x4Test, Trace_F64) {
  lm2_m4x4_f64 m = lm2_m4x4_make_f64(
      1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0);
  double trace = lm2_m4x4_trace_f64(m);

  EXPECT_DOUBLE_EQ(trace, 34.0);  // 1 + 6 + 11 + 16 = 34
}

TEST_F(Matrix4x4Test, Inverse_F64) {
  lm2_m4x4_f64 m = lm2_m4x4_scale_translate_f64({2.0, 3.0, 4.0}, {10.0, 20.0, 30.0});
  lm2_m4x4_f64 inv = lm2_m4x4_inverse_f64(m);
  lm2_m4x4_f64 identity = lm2_m4x4_multiply_f64(m, inv);

  EXPECT_NEAR(identity.m00, 1.0, EPSILON_F64);
  EXPECT_NEAR(identity.m11, 1.0, EPSILON_F64);
  EXPECT_NEAR(identity.m22, 1.0, EPSILON_F64);
  EXPECT_NEAR(identity.m33, 1.0, EPSILON_F64);
  EXPECT_NEAR(identity.m01, 0.0, EPSILON_F64);
  EXPECT_NEAR(identity.m02, 0.0, EPSILON_F64);
  EXPECT_NEAR(identity.m10, 0.0, EPSILON_F64);
  EXPECT_NEAR(identity.m12, 0.0, EPSILON_F64);
}

// =============================================================================
// Transformation Tests (f64)
// =============================================================================

TEST_F(Matrix4x4Test, TransformPoint_F64) {
  lm2_m4x4_f64 m = lm2_m4x4_translate_f64({10.0, 20.0, 30.0});
  lm2_v3_f64 p = {5.0, 8.0, 12.0};
  lm2_v3_f64 result = lm2_m4x4_transform_point_f64(m, p);

  EXPECT_DOUBLE_EQ(result.x, 15.0);
  EXPECT_DOUBLE_EQ(result.y, 28.0);
  EXPECT_DOUBLE_EQ(result.z, 42.0);
}

TEST_F(Matrix4x4Test, TransformVector_F64) {
  lm2_m4x4_f64 m = lm2_m4x4_translate_f64({10.0, 20.0, 30.0});
  lm2_v3_f64 v = {5.0, 8.0, 12.0};
  lm2_v3_f64 result = lm2_m4x4_transform_vector_f64(m, v);

  // Translation should not affect vectors
  EXPECT_DOUBLE_EQ(result.x, 5.0);
  EXPECT_DOUBLE_EQ(result.y, 8.0);
  EXPECT_DOUBLE_EQ(result.z, 12.0);
}

TEST_F(Matrix4x4Test, Transform_F64) {
  lm2_m4x4_f64 m = lm2_m4x4_scale_f64({2.0, 3.0, 4.0});
  lm2_v4_f64 v = {1.0, 2.0, 3.0, 1.0};
  lm2_v4_f64 result = lm2_m4x4_transform_f64(m, v);

  EXPECT_DOUBLE_EQ(result.x, 2.0);
  EXPECT_DOUBLE_EQ(result.y, 6.0);
  EXPECT_DOUBLE_EQ(result.z, 12.0);
  EXPECT_DOUBLE_EQ(result.w, 1.0);
}

TEST_F(Matrix4x4Test, TransformPoints_F64) {
  lm2_m4x4_f64 m = lm2_m4x4_scale_f64({2.0, 2.0, 2.0});
  lm2_v3_f64 points[3] = {
      {1.0, 1.0, 1.0},
      {2.0, 2.0, 2.0},
      {3.0, 3.0, 3.0}
  };

  lm2_m4x4_transform_points_f64(m, points, 3);

  EXPECT_DOUBLE_EQ(points[0].x, 2.0);
  EXPECT_DOUBLE_EQ(points[0].y, 2.0);
  EXPECT_DOUBLE_EQ(points[0].z, 2.0);
  EXPECT_DOUBLE_EQ(points[1].x, 4.0);
  EXPECT_DOUBLE_EQ(points[1].y, 4.0);
  EXPECT_DOUBLE_EQ(points[1].z, 4.0);
}

TEST_F(Matrix4x4Test, TransformPointsSrcDst_F64) {
  lm2_m4x4_f64 m = lm2_m4x4_scale_f64({2.0, 2.0, 2.0});
  const lm2_v3_f64 src[2] = {
      {1.0, 1.0, 1.0},
      {2.0, 2.0, 2.0}
  };
  lm2_v3_f64 dst[2];

  lm2_m4x4_transform_points_src_dst_f64(m, src, dst, 2);

  EXPECT_DOUBLE_EQ(dst[0].x, 2.0);
  EXPECT_DOUBLE_EQ(dst[0].y, 2.0);
  EXPECT_DOUBLE_EQ(dst[0].z, 2.0);
  EXPECT_DOUBLE_EQ(dst[1].x, 4.0);
  EXPECT_DOUBLE_EQ(dst[1].y, 4.0);
  EXPECT_DOUBLE_EQ(dst[1].z, 4.0);
}

// =============================================================================
// Extraction Tests (f64)
// =============================================================================

TEST_F(Matrix4x4Test, GetScale_F64) {
  lm2_v3_f64 scale = {2.0, 3.0, 4.0};
  lm2_m4x4_f64 m = lm2_m4x4_scale_f64(scale);
  lm2_v3_f64 extracted = lm2_m4x4_get_scale_f64(m);

  EXPECT_DOUBLE_EQ(extracted.x, 2.0);
  EXPECT_DOUBLE_EQ(extracted.y, 3.0);
  EXPECT_DOUBLE_EQ(extracted.z, 4.0);
}

TEST_F(Matrix4x4Test, GetTranslation_F64) {
  lm2_v3_f64 translation = {10.0, 20.0, 30.0};
  lm2_m4x4_f64 m = lm2_m4x4_translate_f64(translation);
  lm2_v3_f64 extracted = lm2_m4x4_get_translation_f64(m);

  EXPECT_DOUBLE_EQ(extracted.x, 10.0);
  EXPECT_DOUBLE_EQ(extracted.y, 20.0);
  EXPECT_DOUBLE_EQ(extracted.z, 30.0);
}

// =============================================================================
// Projection Tests (f64)
// =============================================================================

TEST_F(Matrix4x4Test, Ortho_F64) {
  lm2_m4x4_f64 m = lm2_m4x4_ortho_f64(-1.0, 1.0, -1.0, 1.0, 0.1, 100.0);

  // Test that it creates a valid orthographic projection
  lm2_v3_f64 center = lm2_m4x4_transform_point_f64(m, {0.0, 0.0, -50.05});

  EXPECT_NEAR(center.x, 0.0, EPSILON_F64);
  EXPECT_NEAR(center.y, 0.0, EPSILON_F64);
}

TEST_F(Matrix4x4Test, Perspective_F64) {
  lm2_m4x4_f64 m = lm2_m4x4_perspective_f64(LM2_PI_F64 / 4.0, 16.0 / 9.0, 0.1, 100.0);

  // Test that diagonal elements are non-zero (basic sanity check)
  EXPECT_NE(m.m00, 0.0);
  EXPECT_NE(m.m11, 0.0);
  EXPECT_NE(m.m22, 0.0);
}

TEST_F(Matrix4x4Test, LookAt_F64) {
  lm2_v3_f64 eye = {0.0, 0.0, 5.0};
  lm2_v3_f64 target = {0.0, 0.0, 0.0};
  lm2_v3_f64 up = {0.0, 1.0, 0.0};

  lm2_m4x4_f64 m = lm2_m4x4_look_at_f64(eye, target, up);

  // Test that it creates a valid view matrix
  EXPECT_NE(m.m00, 0.0);
  EXPECT_NE(m.m11, 0.0);
  EXPECT_NE(m.m22, 0.0);
}

// =============================================================================
// Creation and Initialization Tests (f32)
// =============================================================================

TEST_F(Matrix4x4Test, Identity_F32) {
  lm2_m4x4_f32 m = lm2_m4x4_identity_f32();
  EXPECT_FLOAT_EQ(m.m00, 1.0f);
  EXPECT_FLOAT_EQ(m.m11, 1.0f);
  EXPECT_FLOAT_EQ(m.m22, 1.0f);
  EXPECT_FLOAT_EQ(m.m33, 1.0f);
  EXPECT_FLOAT_EQ(m.m01, 0.0f);
  EXPECT_FLOAT_EQ(m.m10, 0.0f);
}

TEST_F(Matrix4x4Test, Zero_F32) {
  lm2_m4x4_f32 m = lm2_m4x4_zero_f32();
  for (int i = 0; i < 16; i++) {
    EXPECT_FLOAT_EQ(m.e[i], 0.0f);
  }
}

TEST_F(Matrix4x4Test, Make_F32) {
  lm2_m4x4_f32 m = lm2_m4x4_make_f32(
      1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
  EXPECT_FLOAT_EQ(m.m00, 1.0f);
  EXPECT_FLOAT_EQ(m.m01, 2.0f);
  EXPECT_FLOAT_EQ(m.m10, 5.0f);
  EXPECT_FLOAT_EQ(m.m11, 6.0f);
}

// =============================================================================
// Transformation Creation Tests (f32)
// =============================================================================

TEST_F(Matrix4x4Test, Scale_F32) {
  lm2_v3_f32 scale = {2.0f, 3.0f, 4.0f};
  lm2_m4x4_f32 m = lm2_m4x4_scale_f32(scale);

  EXPECT_FLOAT_EQ(m.m00, 2.0f);
  EXPECT_FLOAT_EQ(m.m11, 3.0f);
  EXPECT_FLOAT_EQ(m.m22, 4.0f);
  EXPECT_FLOAT_EQ(m.m33, 1.0f);
}

TEST_F(Matrix4x4Test, Translate_F32) {
  lm2_v3_f32 translation = {10.0f, 20.0f, 30.0f};
  lm2_m4x4_f32 m = lm2_m4x4_translate_f32(translation);

  EXPECT_FLOAT_EQ(m.m00, 1.0f);
  EXPECT_FLOAT_EQ(m.m11, 1.0f);
  EXPECT_FLOAT_EQ(m.m22, 1.0f);
  EXPECT_FLOAT_EQ(m.m33, 1.0f);
  EXPECT_FLOAT_EQ(m.m03, 10.0f);
  EXPECT_FLOAT_EQ(m.m13, 20.0f);
  EXPECT_FLOAT_EQ(m.m23, 30.0f);
}

TEST_F(Matrix4x4Test, RotateX90Degrees_F32) {
  lm2_m4x4_f32 m = lm2_m4x4_rotate_x_f32(LM2_PI_F32 / 2.0f);

  EXPECT_FLOAT_EQ(m.m00, 1.0f);
  EXPECT_NEAR(m.m11, 0.0f, EPSILON_F32);
  EXPECT_NEAR(m.m12, -1.0f, EPSILON_F32);
  EXPECT_NEAR(m.m21, 1.0f, EPSILON_F32);
  EXPECT_NEAR(m.m22, 0.0f, EPSILON_F32);
}

TEST_F(Matrix4x4Test, RotateY90Degrees_F32) {
  lm2_m4x4_f32 m = lm2_m4x4_rotate_y_f32(LM2_PI_F32 / 2.0f);

  EXPECT_NEAR(m.m00, 0.0f, EPSILON_F32);
  EXPECT_NEAR(m.m02, 1.0f, EPSILON_F32);
  EXPECT_FLOAT_EQ(m.m11, 1.0f);
  EXPECT_NEAR(m.m20, -1.0f, EPSILON_F32);
  EXPECT_NEAR(m.m22, 0.0f, EPSILON_F32);
}

TEST_F(Matrix4x4Test, RotateZ90Degrees_F32) {
  lm2_m4x4_f32 m = lm2_m4x4_rotate_z_f32(LM2_PI_F32 / 2.0f);

  EXPECT_NEAR(m.m00, 0.0f, EPSILON_F32);
  EXPECT_NEAR(m.m01, -1.0f, EPSILON_F32);
  EXPECT_NEAR(m.m10, 1.0f, EPSILON_F32);
  EXPECT_NEAR(m.m11, 0.0f, EPSILON_F32);
}

// =============================================================================
// Matrix Operations Tests (f32)
// =============================================================================

TEST_F(Matrix4x4Test, Multiply_F32) {
  lm2_m4x4_f32 a = lm2_m4x4_translate_f32({10.0f, 20.0f, 30.0f});
  lm2_m4x4_f32 b = lm2_m4x4_scale_f32({2.0f, 3.0f, 4.0f});
  lm2_m4x4_f32 result = lm2_m4x4_multiply_f32(a, b);

  lm2_v3_f32 p = {1.0f, 1.0f, 1.0f};
  lm2_v3_f32 transformed = lm2_m4x4_transform_point_f32(result, p);

  EXPECT_NEAR(transformed.x, 12.0f, EPSILON_F32);
  EXPECT_NEAR(transformed.y, 23.0f, EPSILON_F32);
  EXPECT_NEAR(transformed.z, 34.0f, EPSILON_F32);
}

TEST_F(Matrix4x4Test, Transpose_F32) {
  lm2_m4x4_f32 m = lm2_m4x4_make_f32(
      1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
  lm2_m4x4_f32 mt = lm2_m4x4_transpose_f32(m);

  EXPECT_FLOAT_EQ(mt.m00, 1.0f);
  EXPECT_FLOAT_EQ(mt.m01, 5.0f);
  EXPECT_FLOAT_EQ(mt.m02, 9.0f);
  EXPECT_FLOAT_EQ(mt.m10, 2.0f);
}

TEST_F(Matrix4x4Test, Determinant_F32) {
  lm2_m4x4_f32 m = lm2_m4x4_identity_f32();
  float det = lm2_m4x4_determinant_f32(m);

  EXPECT_FLOAT_EQ(det, 1.0f);
}

TEST_F(Matrix4x4Test, Trace_F32) {
  lm2_m4x4_f32 m = lm2_m4x4_make_f32(
      1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
  float trace = lm2_m4x4_trace_f32(m);

  EXPECT_FLOAT_EQ(trace, 34.0f);
}

TEST_F(Matrix4x4Test, Inverse_F32) {
  lm2_m4x4_f32 m = lm2_m4x4_scale_translate_f32({2.0f, 3.0f, 4.0f}, {10.0f, 20.0f, 30.0f});
  lm2_m4x4_f32 inv = lm2_m4x4_inverse_f32(m);
  lm2_m4x4_f32 identity = lm2_m4x4_multiply_f32(m, inv);

  EXPECT_NEAR(identity.m00, 1.0f, EPSILON_F32);
  EXPECT_NEAR(identity.m11, 1.0f, EPSILON_F32);
  EXPECT_NEAR(identity.m22, 1.0f, EPSILON_F32);
  EXPECT_NEAR(identity.m33, 1.0f, EPSILON_F32);
}

// =============================================================================
// Transformation Tests (f32)
// =============================================================================

TEST_F(Matrix4x4Test, TransformPoint_F32) {
  lm2_m4x4_f32 m = lm2_m4x4_translate_f32({10.0f, 20.0f, 30.0f});
  lm2_v3_f32 p = {5.0f, 8.0f, 12.0f};
  lm2_v3_f32 result = lm2_m4x4_transform_point_f32(m, p);

  EXPECT_FLOAT_EQ(result.x, 15.0f);
  EXPECT_FLOAT_EQ(result.y, 28.0f);
  EXPECT_FLOAT_EQ(result.z, 42.0f);
}

TEST_F(Matrix4x4Test, TransformVector_F32) {
  lm2_m4x4_f32 m = lm2_m4x4_translate_f32({10.0f, 20.0f, 30.0f});
  lm2_v3_f32 v = {5.0f, 8.0f, 12.0f};
  lm2_v3_f32 result = lm2_m4x4_transform_vector_f32(m, v);

  EXPECT_FLOAT_EQ(result.x, 5.0f);
  EXPECT_FLOAT_EQ(result.y, 8.0f);
  EXPECT_FLOAT_EQ(result.z, 12.0f);
}

TEST_F(Matrix4x4Test, GetScale_F32) {
  lm2_v3_f32 scale = {2.0f, 3.0f, 4.0f};
  lm2_m4x4_f32 m = lm2_m4x4_scale_f32(scale);
  lm2_v3_f32 extracted = lm2_m4x4_get_scale_f32(m);

  EXPECT_FLOAT_EQ(extracted.x, 2.0f);
  EXPECT_FLOAT_EQ(extracted.y, 3.0f);
  EXPECT_FLOAT_EQ(extracted.z, 4.0f);
}

TEST_F(Matrix4x4Test, GetTranslation_F32) {
  lm2_v3_f32 translation = {10.0f, 20.0f, 30.0f};
  lm2_m4x4_f32 m = lm2_m4x4_translate_f32(translation);
  lm2_v3_f32 extracted = lm2_m4x4_get_translation_f32(m);

  EXPECT_FLOAT_EQ(extracted.x, 10.0f);
  EXPECT_FLOAT_EQ(extracted.y, 20.0f);
  EXPECT_FLOAT_EQ(extracted.z, 30.0f);
}

TEST_F(Matrix4x4Test, Perspective_F32) {
  lm2_m4x4_f32 m = lm2_m4x4_perspective_f32(LM2_PI_F32 / 4.0f, 16.0f / 9.0f, 0.1f, 100.0f);

  EXPECT_NE(m.m00, 0.0f);
  EXPECT_NE(m.m11, 0.0f);
  EXPECT_NE(m.m22, 0.0f);
}

TEST_F(Matrix4x4Test, LookAt_F32) {
  lm2_v3_f32 eye = {0.0f, 0.0f, 5.0f};
  lm2_v3_f32 target = {0.0f, 0.0f, 0.0f};
  lm2_v3_f32 up = {0.0f, 1.0f, 0.0f};

  lm2_m4x4_f32 m = lm2_m4x4_look_at_f32(eye, target, up);

  EXPECT_NE(m.m00, 0.0f);
  EXPECT_NE(m.m11, 0.0f);
  EXPECT_NE(m.m22, 0.0f);
}
