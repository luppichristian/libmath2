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
#include "lm2/matrices/lm2_matrix3x2.h"

// Test fixture for matrix3x2 tests
class Matrix3x2Test : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Creation and Initialization Tests (f64)
// =============================================================================

TEST_F(Matrix3x2Test, Identity_F64) {
  lm2_m3x2_f64 m = lm2_m3x2_identity_f64();
  EXPECT_DOUBLE_EQ(m.m00, 1.0);
  EXPECT_DOUBLE_EQ(m.m01, 0.0);
  EXPECT_DOUBLE_EQ(m.m02, 0.0);
  EXPECT_DOUBLE_EQ(m.m10, 0.0);
  EXPECT_DOUBLE_EQ(m.m11, 1.0);
  EXPECT_DOUBLE_EQ(m.m12, 0.0);
}

TEST_F(Matrix3x2Test, Zero_F64) {
  lm2_m3x2_f64 m = lm2_m3x2_zero_f64();
  for (int i = 0; i < 6; i++) {
    EXPECT_DOUBLE_EQ(m.e[i], 0.0);
  }
}

TEST_F(Matrix3x2Test, Make_F64) {
  lm2_m3x2_f64 m = lm2_m3x2_make_f64(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
  EXPECT_DOUBLE_EQ(m.m00, 1.0);
  EXPECT_DOUBLE_EQ(m.m01, 2.0);
  EXPECT_DOUBLE_EQ(m.m02, 3.0);
  EXPECT_DOUBLE_EQ(m.m10, 4.0);
  EXPECT_DOUBLE_EQ(m.m11, 5.0);
  EXPECT_DOUBLE_EQ(m.m12, 6.0);
}

TEST_F(Matrix3x2Test, AlternativeFieldNames_F64) {
  lm2_m3x2_f64 m = lm2_m3x2_make_f64(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
  EXPECT_DOUBLE_EQ(m.a, 1.0);
  EXPECT_DOUBLE_EQ(m.c, 2.0);
  EXPECT_DOUBLE_EQ(m.tx, 3.0);
  EXPECT_DOUBLE_EQ(m.b, 4.0);
  EXPECT_DOUBLE_EQ(m.d, 5.0);
  EXPECT_DOUBLE_EQ(m.ty, 6.0);
}

// =============================================================================
// Transformation Creation Tests (f64)
// =============================================================================

TEST_F(Matrix3x2Test, Scale_F64) {
  lm2_v2_f64 scale = {2.0, 3.0};
  lm2_m3x2_f64 m = lm2_m3x2_scale_f64(scale);

  EXPECT_DOUBLE_EQ(m.m00, 2.0);
  EXPECT_DOUBLE_EQ(m.m11, 3.0);
  EXPECT_DOUBLE_EQ(m.m01, 0.0);
  EXPECT_DOUBLE_EQ(m.m10, 0.0);
  EXPECT_DOUBLE_EQ(m.m02, 0.0);
  EXPECT_DOUBLE_EQ(m.m12, 0.0);
}

TEST_F(Matrix3x2Test, ScaleUniform_F64) {
  lm2_m3x2_f64 m = lm2_m3x2_scale_uniform_f64(2.5);

  EXPECT_DOUBLE_EQ(m.m00, 2.5);
  EXPECT_DOUBLE_EQ(m.m11, 2.5);
  EXPECT_DOUBLE_EQ(m.m01, 0.0);
  EXPECT_DOUBLE_EQ(m.m10, 0.0);
  EXPECT_DOUBLE_EQ(m.m02, 0.0);
  EXPECT_DOUBLE_EQ(m.m12, 0.0);
}

TEST_F(Matrix3x2Test, Translate_F64) {
  lm2_v2_f64 translation = {10.0, 20.0};
  lm2_m3x2_f64 m = lm2_m3x2_translate_f64(translation);

  EXPECT_DOUBLE_EQ(m.m00, 1.0);
  EXPECT_DOUBLE_EQ(m.m11, 1.0);
  EXPECT_DOUBLE_EQ(m.m02, 10.0);
  EXPECT_DOUBLE_EQ(m.m12, 20.0);
  EXPECT_DOUBLE_EQ(m.m01, 0.0);
  EXPECT_DOUBLE_EQ(m.m10, 0.0);
}

TEST_F(Matrix3x2Test, Rotate90Degrees_F64) {
  lm2_m3x2_f64 m = lm2_m3x2_rotate_f64(LM2_PI_F64 / 2.0);

  EXPECT_NEAR(m.m00, 0.0, EPSILON_F64);
  EXPECT_NEAR(m.m01, -1.0, EPSILON_F64);
  EXPECT_NEAR(m.m10, 1.0, EPSILON_F64);
  EXPECT_NEAR(m.m11, 0.0, EPSILON_F64);
  EXPECT_NEAR(m.m02, 0.0, EPSILON_F64);
  EXPECT_NEAR(m.m12, 0.0, EPSILON_F64);
}

TEST_F(Matrix3x2Test, RotateAroundPivot_F64) {
  lm2_v2_f64 pivot = {5.0, 5.0};
  lm2_m3x2_f64 m = lm2_m3x2_rotate_around_pivot_f64(LM2_PI_F64, pivot);

  // After 180 degree rotation around (5, 5), point (5, 5) should stay at (5, 5)
  lm2_v2_f64 p = {5.0, 5.0};
  lm2_v2_f64 result = lm2_m3x2_transform_point_f64(m, p);

  EXPECT_NEAR(result.x, 5.0, EPSILON_F64);
  EXPECT_NEAR(result.y, 5.0, EPSILON_F64);
}

TEST_F(Matrix3x2Test, ScaleTranslate_F64) {
  lm2_v2_f64 scale = {2.0, 3.0};
  lm2_v2_f64 translation = {10.0, 20.0};
  lm2_m3x2_f64 m = lm2_m3x2_scale_translate_f64(scale, translation);

  EXPECT_DOUBLE_EQ(m.m00, 2.0);
  EXPECT_DOUBLE_EQ(m.m11, 3.0);
  EXPECT_DOUBLE_EQ(m.m02, 10.0);
  EXPECT_DOUBLE_EQ(m.m12, 20.0);
}

TEST_F(Matrix3x2Test, WorldTransform_F64) {
  lm2_v2_f64 translation = {10.0, 20.0};
  lm2_v2_f64 scale = {2.0, 2.0};
  double rotation = LM2_PI_F64 / 4.0;

  lm2_m3x2_f64 m = lm2_m3x2_world_transform_f64(translation, scale, rotation);

  // Test that it produces a valid transform
  lm2_v2_f64 p = {0.0, 0.0};
  lm2_v2_f64 result = lm2_m3x2_transform_point_f64(m, p);

  EXPECT_NEAR(result.x, 10.0, EPSILON_F64);
  EXPECT_NEAR(result.y, 20.0, EPSILON_F64);
}

// =============================================================================
// Matrix Operations Tests (f64)
// =============================================================================

TEST_F(Matrix3x2Test, Multiply_F64) {
  lm2_m3x2_f64 a = lm2_m3x2_translate_f64({10.0, 20.0});
  lm2_m3x2_f64 b = lm2_m3x2_scale_f64({2.0, 3.0});
  lm2_m3x2_f64 result = lm2_m3x2_multiply_f64(a, b);

  // Translation * Scale = scale then translate
  lm2_v2_f64 p = {1.0, 1.0};
  lm2_v2_f64 transformed = lm2_m3x2_transform_point_f64(result, p);

  EXPECT_NEAR(transformed.x, 12.0, EPSILON_F64);
  EXPECT_NEAR(transformed.y, 23.0, EPSILON_F64);
}

TEST_F(Matrix3x2Test, Determinant_F64) {
  lm2_m3x2_f64 m = lm2_m3x2_make_f64(2.0, 0.0, 5.0, 0.0, 3.0, 7.0);
  double det = lm2_m3x2_determinant_f64(m);

  EXPECT_DOUBLE_EQ(det, 6.0);  // det = 2*3 - 0*0 = 6
}

TEST_F(Matrix3x2Test, Inverse_F64) {
  lm2_m3x2_f64 m = lm2_m3x2_scale_translate_f64({2.0, 3.0}, {10.0, 20.0});
  lm2_m3x2_f64 inv = lm2_m3x2_inverse_f64(m);
  lm2_m3x2_f64 identity = lm2_m3x2_multiply_f64(m, inv);

  EXPECT_NEAR(identity.m00, 1.0, EPSILON_F64);
  EXPECT_NEAR(identity.m11, 1.0, EPSILON_F64);
  EXPECT_NEAR(identity.m01, 0.0, EPSILON_F64);
  EXPECT_NEAR(identity.m10, 0.0, EPSILON_F64);
  EXPECT_NEAR(identity.m02, 0.0, EPSILON_F64);
  EXPECT_NEAR(identity.m12, 0.0, EPSILON_F64);
}

// =============================================================================
// Transformation Tests (f64)
// =============================================================================

TEST_F(Matrix3x2Test, TransformPoint_F64) {
  lm2_m3x2_f64 m = lm2_m3x2_translate_f64({10.0, 20.0});
  lm2_v2_f64 p = {5.0, 8.0};
  lm2_v2_f64 result = lm2_m3x2_transform_point_f64(m, p);

  EXPECT_DOUBLE_EQ(result.x, 15.0);
  EXPECT_DOUBLE_EQ(result.y, 28.0);
}

TEST_F(Matrix3x2Test, TransformVector_F64) {
  lm2_m3x2_f64 m = lm2_m3x2_translate_f64({10.0, 20.0});
  lm2_v2_f64 v = {5.0, 8.0};
  lm2_v2_f64 result = lm2_m3x2_transform_vector_f64(m, v);

  // Translation should not affect vectors
  EXPECT_DOUBLE_EQ(result.x, 5.0);
  EXPECT_DOUBLE_EQ(result.y, 8.0);
}

TEST_F(Matrix3x2Test, TransformPoints_F64) {
  lm2_m3x2_f64 m = lm2_m3x2_scale_f64({2.0, 2.0});
  lm2_v2_f64 points[3] = {
      {1.0, 1.0},
      {2.0, 2.0},
      {3.0, 3.0}
  };

  lm2_m3x2_transform_points_f64(m, points, 3);

  EXPECT_DOUBLE_EQ(points[0].x, 2.0);
  EXPECT_DOUBLE_EQ(points[0].y, 2.0);
  EXPECT_DOUBLE_EQ(points[1].x, 4.0);
  EXPECT_DOUBLE_EQ(points[1].y, 4.0);
  EXPECT_DOUBLE_EQ(points[2].x, 6.0);
  EXPECT_DOUBLE_EQ(points[2].y, 6.0);
}

TEST_F(Matrix3x2Test, TransformPointsSrcDst_F64) {
  lm2_m3x2_f64 m = lm2_m3x2_scale_f64({2.0, 2.0});
  const lm2_v2_f64 src[2] = {
      {1.0, 1.0},
      {2.0, 2.0}
  };
  lm2_v2_f64 dst[2];

  lm2_m3x2_transform_points_src_dst_f64(m, src, dst, 2);

  EXPECT_DOUBLE_EQ(dst[0].x, 2.0);
  EXPECT_DOUBLE_EQ(dst[0].y, 2.0);
  EXPECT_DOUBLE_EQ(dst[1].x, 4.0);
  EXPECT_DOUBLE_EQ(dst[1].y, 4.0);
}

// =============================================================================
// Extraction Tests (f64)
// =============================================================================

TEST_F(Matrix3x2Test, GetRotation_F64) {
  double angle = LM2_PI_F64 / 3.0;
  lm2_m3x2_f64 m = lm2_m3x2_rotate_f64(angle);
  double extracted = lm2_m3x2_get_rotation_f64(m);

  EXPECT_NEAR(extracted, angle, EPSILON_F64);
}

TEST_F(Matrix3x2Test, GetScale_F64) {
  lm2_v2_f64 scale = {2.0, 3.0};
  lm2_m3x2_f64 m = lm2_m3x2_scale_f64(scale);
  lm2_v2_f64 extracted = lm2_m3x2_get_scale_f64(m);

  EXPECT_DOUBLE_EQ(extracted.x, 2.0);
  EXPECT_DOUBLE_EQ(extracted.y, 3.0);
}

TEST_F(Matrix3x2Test, GetTranslation_F64) {
  lm2_v2_f64 translation = {10.0, 20.0};
  lm2_m3x2_f64 m = lm2_m3x2_translate_f64(translation);
  lm2_v2_f64 extracted = lm2_m3x2_get_translation_f64(m);

  EXPECT_DOUBLE_EQ(extracted.x, 10.0);
  EXPECT_DOUBLE_EQ(extracted.y, 20.0);
}

// =============================================================================
// Projection Tests (f64)
// =============================================================================

TEST_F(Matrix3x2Test, Ortho_F64) {
  lm2_m3x2_f64 m = lm2_m3x2_ortho_f64(0.0, 800.0, 0.0, 600.0);

  // Test corner transformations
  lm2_v2_f64 bottomLeft = lm2_m3x2_transform_point_f64(m, {0.0, 0.0});
  lm2_v2_f64 topRight = lm2_m3x2_transform_point_f64(m, {800.0, 600.0});

  EXPECT_NEAR(bottomLeft.x, -1.0, EPSILON_F64);
  EXPECT_NEAR(bottomLeft.y, -1.0, EPSILON_F64);
  EXPECT_NEAR(topRight.x, 1.0, EPSILON_F64);
  EXPECT_NEAR(topRight.y, 1.0, EPSILON_F64);
}

// =============================================================================
// Creation and Initialization Tests (f32)
// =============================================================================

TEST_F(Matrix3x2Test, Identity_F32) {
  lm2_m3x2_f32 m = lm2_m3x2_identity_f32();
  EXPECT_FLOAT_EQ(m.m00, 1.0f);
  EXPECT_FLOAT_EQ(m.m01, 0.0f);
  EXPECT_FLOAT_EQ(m.m02, 0.0f);
  EXPECT_FLOAT_EQ(m.m10, 0.0f);
  EXPECT_FLOAT_EQ(m.m11, 1.0f);
  EXPECT_FLOAT_EQ(m.m12, 0.0f);
}

TEST_F(Matrix3x2Test, Zero_F32) {
  lm2_m3x2_f32 m = lm2_m3x2_zero_f32();
  for (int i = 0; i < 6; i++) {
    EXPECT_FLOAT_EQ(m.e[i], 0.0f);
  }
}

TEST_F(Matrix3x2Test, Make_F32) {
  lm2_m3x2_f32 m = lm2_m3x2_make_f32(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);
  EXPECT_FLOAT_EQ(m.m00, 1.0f);
  EXPECT_FLOAT_EQ(m.m01, 2.0f);
  EXPECT_FLOAT_EQ(m.m02, 3.0f);
  EXPECT_FLOAT_EQ(m.m10, 4.0f);
  EXPECT_FLOAT_EQ(m.m11, 5.0f);
  EXPECT_FLOAT_EQ(m.m12, 6.0f);
}

// =============================================================================
// Transformation Creation Tests (f32)
// =============================================================================

TEST_F(Matrix3x2Test, Scale_F32) {
  lm2_v2_f32 scale = {2.0f, 3.0f};
  lm2_m3x2_f32 m = lm2_m3x2_scale_f32(scale);

  EXPECT_FLOAT_EQ(m.m00, 2.0f);
  EXPECT_FLOAT_EQ(m.m11, 3.0f);
  EXPECT_FLOAT_EQ(m.m01, 0.0f);
  EXPECT_FLOAT_EQ(m.m10, 0.0f);
  EXPECT_FLOAT_EQ(m.m02, 0.0f);
  EXPECT_FLOAT_EQ(m.m12, 0.0f);
}

TEST_F(Matrix3x2Test, Translate_F32) {
  lm2_v2_f32 translation = {10.0f, 20.0f};
  lm2_m3x2_f32 m = lm2_m3x2_translate_f32(translation);

  EXPECT_FLOAT_EQ(m.m00, 1.0f);
  EXPECT_FLOAT_EQ(m.m11, 1.0f);
  EXPECT_FLOAT_EQ(m.m02, 10.0f);
  EXPECT_FLOAT_EQ(m.m12, 20.0f);
  EXPECT_FLOAT_EQ(m.m01, 0.0f);
  EXPECT_FLOAT_EQ(m.m10, 0.0f);
}

TEST_F(Matrix3x2Test, Rotate90Degrees_F32) {
  lm2_m3x2_f32 m = lm2_m3x2_rotate_f32(LM2_PI_F32 / 2.0f);

  EXPECT_NEAR(m.m00, 0.0f, EPSILON_F32);
  EXPECT_NEAR(m.m01, -1.0f, EPSILON_F32);
  EXPECT_NEAR(m.m10, 1.0f, EPSILON_F32);
  EXPECT_NEAR(m.m11, 0.0f, EPSILON_F32);
  EXPECT_NEAR(m.m02, 0.0f, EPSILON_F32);
  EXPECT_NEAR(m.m12, 0.0f, EPSILON_F32);
}

// =============================================================================
// Matrix Operations Tests (f32)
// =============================================================================

TEST_F(Matrix3x2Test, Multiply_F32) {
  lm2_m3x2_f32 a = lm2_m3x2_translate_f32({10.0f, 20.0f});
  lm2_m3x2_f32 b = lm2_m3x2_scale_f32({2.0f, 3.0f});
  lm2_m3x2_f32 result = lm2_m3x2_multiply_f32(a, b);

  lm2_v2_f32 p = {1.0f, 1.0f};
  lm2_v2_f32 transformed = lm2_m3x2_transform_point_f32(result, p);

  EXPECT_NEAR(transformed.x, 12.0f, EPSILON_F32);
  EXPECT_NEAR(transformed.y, 23.0f, EPSILON_F32);
}

TEST_F(Matrix3x2Test, Determinant_F32) {
  lm2_m3x2_f32 m = lm2_m3x2_make_f32(2.0f, 0.0f, 5.0f, 0.0f, 3.0f, 7.0f);
  float det = lm2_m3x2_determinant_f32(m);

  EXPECT_FLOAT_EQ(det, 6.0f);
}

TEST_F(Matrix3x2Test, Inverse_F32) {
  lm2_m3x2_f32 m = lm2_m3x2_scale_translate_f32({2.0f, 3.0f}, {10.0f, 20.0f});
  lm2_m3x2_f32 inv = lm2_m3x2_inverse_f32(m);
  lm2_m3x2_f32 identity = lm2_m3x2_multiply_f32(m, inv);

  EXPECT_NEAR(identity.m00, 1.0f, EPSILON_F32);
  EXPECT_NEAR(identity.m11, 1.0f, EPSILON_F32);
  EXPECT_NEAR(identity.m01, 0.0f, EPSILON_F32);
  EXPECT_NEAR(identity.m10, 0.0f, EPSILON_F32);
  EXPECT_NEAR(identity.m02, 0.0f, EPSILON_F32);
  EXPECT_NEAR(identity.m12, 0.0f, EPSILON_F32);
}

// =============================================================================
// Transformation Tests (f32)
// =============================================================================

TEST_F(Matrix3x2Test, TransformPoint_F32) {
  lm2_m3x2_f32 m = lm2_m3x2_translate_f32({10.0f, 20.0f});
  lm2_v2_f32 p = {5.0f, 8.0f};
  lm2_v2_f32 result = lm2_m3x2_transform_point_f32(m, p);

  EXPECT_FLOAT_EQ(result.x, 15.0f);
  EXPECT_FLOAT_EQ(result.y, 28.0f);
}

TEST_F(Matrix3x2Test, TransformVector_F32) {
  lm2_m3x2_f32 m = lm2_m3x2_translate_f32({10.0f, 20.0f});
  lm2_v2_f32 v = {5.0f, 8.0f};
  lm2_v2_f32 result = lm2_m3x2_transform_vector_f32(m, v);

  EXPECT_FLOAT_EQ(result.x, 5.0f);
  EXPECT_FLOAT_EQ(result.y, 8.0f);
}

TEST_F(Matrix3x2Test, GetRotation_F32) {
  float angle = LM2_PI_F32 / 3.0f;
  lm2_m3x2_f32 m = lm2_m3x2_rotate_f32(angle);
  float extracted = lm2_m3x2_get_rotation_f32(m);

  EXPECT_NEAR(extracted, angle, EPSILON_F32);
}

TEST_F(Matrix3x2Test, GetScale_F32) {
  lm2_v2_f32 scale = {2.0f, 3.0f};
  lm2_m3x2_f32 m = lm2_m3x2_scale_f32(scale);
  lm2_v2_f32 extracted = lm2_m3x2_get_scale_f32(m);

  EXPECT_FLOAT_EQ(extracted.x, 2.0f);
  EXPECT_FLOAT_EQ(extracted.y, 3.0f);
}

TEST_F(Matrix3x2Test, GetTranslation_F32) {
  lm2_v2_f32 translation = {10.0f, 20.0f};
  lm2_m3x2_f32 m = lm2_m3x2_translate_f32(translation);
  lm2_v2_f32 extracted = lm2_m3x2_get_translation_f32(m);

  EXPECT_FLOAT_EQ(extracted.x, 10.0f);
  EXPECT_FLOAT_EQ(extracted.y, 20.0f);
}
