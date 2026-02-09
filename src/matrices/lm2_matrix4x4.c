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

#include <lm2/matrices/lm2_matrix4x4.h>
#include <lm2/misc/lm2_quaternion.h>
#include <lm2/lm2_constants.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/scalar/lm2_trigonometry.h>
#include <lm2/vectors/lm2_vector_specifics.h>

// =============================================================================
// Matrix 4x4 Functions - f64
// =============================================================================

// Basic constructors
LM2_API lm2_m4x4f64 lm2_m4x4f64_identity(void) {
  lm2_m4x4f64 m = {
      1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0};
  return m;
}

LM2_API lm2_m4x4f64 lm2_m4x4f64_zero(void) {
  lm2_m4x4f64 m = {
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  return m;
}

LM2_API lm2_m4x4f64 lm2_m4x4f64_make(double m00, double m01, double m02, double m03, double m10, double m11, double m12, double m13, double m20, double m21, double m22, double m23, double m30, double m31, double m32, double m33) {
  lm2_m4x4f64 m = {
      m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33};
  return m;
}

// Transformations
LM2_API lm2_m4x4f64 lm2_m4x4f64_scale(lm2_v3f64 scale) {
  lm2_m4x4f64 m = {
      scale.x, 0.0, 0.0, 0.0, 0.0, scale.y, 0.0, 0.0, 0.0, 0.0, scale.z, 0.0, 0.0, 0.0, 0.0, 1.0};
  return m;
}

LM2_API lm2_m4x4f64 lm2_m4x4f64_scale_uniform(double scale) {
  lm2_m4x4f64 m = {
      scale, 0.0, 0.0, 0.0, 0.0, scale, 0.0, 0.0, 0.0, 0.0, scale, 0.0, 0.0, 0.0, 0.0, 1.0};
  return m;
}

LM2_API lm2_m4x4f64 lm2_m4x4f64_translate(lm2_v3f64 translation) {
  lm2_m4x4f64 m = {
      1.0, 0.0, 0.0, translation.x, 0.0, 1.0, 0.0, translation.y, 0.0, 0.0, 1.0, translation.z, 0.0, 0.0, 0.0, 1.0};
  return m;
}

LM2_API lm2_m4x4f64 lm2_m4x4f64_rotate_x(double angle) {
  double c = lm2_cos_f64(angle);
  double s = lm2_sin_f64(angle);

  lm2_m4x4f64 m = {
      1.0, 0.0, 0.0, 0.0, 0.0, c, lm2_sub_f64(0.0, s), 0.0, 0.0, s, c, 0.0, 0.0, 0.0, 0.0, 1.0};
  return m;
}

LM2_API lm2_m4x4f64 lm2_m4x4f64_rotate_y(double angle) {
  double c = lm2_cos_f64(angle);
  double s = lm2_sin_f64(angle);

  lm2_m4x4f64 m = {
      c, 0.0, s, 0.0, 0.0, 1.0, 0.0, 0.0, lm2_sub_f64(0.0, s), 0.0, c, 0.0, 0.0, 0.0, 0.0, 1.0};
  return m;
}

LM2_API lm2_m4x4f64 lm2_m4x4f64_rotate_z(double angle) {
  double c = lm2_cos_f64(angle);
  double s = lm2_sin_f64(angle);

  lm2_m4x4f64 m = {
      c, lm2_sub_f64(0.0, s), 0.0, 0.0, s, c, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0};
  return m;
}

LM2_API lm2_m4x4f64 lm2_m4x4f64_rotate_axis(lm2_v3f64 axis, double angle) {
  // Normalize axis
  double len_sq = lm2_add_f64(lm2_add_f64(lm2_mul_f64(axis.x, axis.x), lm2_mul_f64(axis.y, axis.y)), lm2_mul_f64(axis.z, axis.z));
  double len = lm2_sqrt_f64(len_sq);
  LM2_ASSERT_UNSAFE(len > 0.0);

  double inv_len = lm2_div_f64(1.0, len);
  double x = lm2_mul_f64(axis.x, inv_len);
  double y = lm2_mul_f64(axis.y, inv_len);
  double z = lm2_mul_f64(axis.z, inv_len);

  double c = lm2_cos_f64(angle);
  double s = lm2_sin_f64(angle);
  double t = lm2_sub_f64(1.0, c);

  lm2_m4x4f64 m;
  m.m00 = lm2_add_f64(lm2_mul_f64(t, lm2_mul_f64(x, x)), c);
  m.m01 = lm2_sub_f64(lm2_mul_f64(t, lm2_mul_f64(x, y)), lm2_mul_f64(z, s));
  m.m02 = lm2_add_f64(lm2_mul_f64(t, lm2_mul_f64(x, z)), lm2_mul_f64(y, s));
  m.m03 = 0.0;

  m.m10 = lm2_add_f64(lm2_mul_f64(t, lm2_mul_f64(x, y)), lm2_mul_f64(z, s));
  m.m11 = lm2_add_f64(lm2_mul_f64(t, lm2_mul_f64(y, y)), c);
  m.m12 = lm2_sub_f64(lm2_mul_f64(t, lm2_mul_f64(y, z)), lm2_mul_f64(x, s));
  m.m13 = 0.0;

  m.m20 = lm2_sub_f64(lm2_mul_f64(t, lm2_mul_f64(x, z)), lm2_mul_f64(y, s));
  m.m21 = lm2_add_f64(lm2_mul_f64(t, lm2_mul_f64(y, z)), lm2_mul_f64(x, s));
  m.m22 = lm2_add_f64(lm2_mul_f64(t, lm2_mul_f64(z, z)), c);
  m.m23 = 0.0;

  m.m30 = 0.0;
  m.m31 = 0.0;
  m.m32 = 0.0;
  m.m33 = 1.0;

  return m;
}

LM2_API lm2_m4x4f64 lm2_m4x4f64_scale_translate(lm2_v3f64 scale, lm2_v3f64 translation) {
  lm2_m4x4f64 m = {
      scale.x, 0.0, 0.0, translation.x, 0.0, scale.y, 0.0, translation.y, 0.0, 0.0, scale.z, translation.z, 0.0, 0.0, 0.0, 1.0};
  return m;
}

LM2_API lm2_m4x4f64 lm2_m4x4f64_world_transform(lm2_v3f64 translation, lm2_v3f64 scale, lm2_v3f64 rotation_euler) {
  // T * R * S
  lm2_m4x4f64 s = lm2_m4x4f64_scale(scale);
  lm2_m4x4f64 rx = lm2_m4x4f64_rotate_x(rotation_euler.x);
  lm2_m4x4f64 ry = lm2_m4x4f64_rotate_y(rotation_euler.y);
  lm2_m4x4f64 rz = lm2_m4x4f64_rotate_z(rotation_euler.z);
  lm2_m4x4f64 t = lm2_m4x4f64_translate(translation);

  lm2_m4x4f64 temp1 = lm2_m4x4f64_multiply(rz, s);
  lm2_m4x4f64 temp2 = lm2_m4x4f64_multiply(ry, temp1);
  lm2_m4x4f64 temp3 = lm2_m4x4f64_multiply(rx, temp2);
  return lm2_m4x4f64_multiply(t, temp3);
}

// Operations
LM2_API lm2_m4x4f64 lm2_m4x4f64_multiply(lm2_m4x4f64 a, lm2_m4x4f64 b) {
  lm2_m4x4f64 result;

  // Row 0
  result.m00 = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m00, b.m00), lm2_mul_f64(a.m01, b.m10)), lm2_mul_f64(a.m02, b.m20)), lm2_mul_f64(a.m03, b.m30));
  result.m01 = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m00, b.m01), lm2_mul_f64(a.m01, b.m11)), lm2_mul_f64(a.m02, b.m21)), lm2_mul_f64(a.m03, b.m31));
  result.m02 = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m00, b.m02), lm2_mul_f64(a.m01, b.m12)), lm2_mul_f64(a.m02, b.m22)), lm2_mul_f64(a.m03, b.m32));
  result.m03 = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m00, b.m03), lm2_mul_f64(a.m01, b.m13)), lm2_mul_f64(a.m02, b.m23)), lm2_mul_f64(a.m03, b.m33));

  // Row 1
  result.m10 = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m10, b.m00), lm2_mul_f64(a.m11, b.m10)), lm2_mul_f64(a.m12, b.m20)), lm2_mul_f64(a.m13, b.m30));
  result.m11 = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m10, b.m01), lm2_mul_f64(a.m11, b.m11)), lm2_mul_f64(a.m12, b.m21)), lm2_mul_f64(a.m13, b.m31));
  result.m12 = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m10, b.m02), lm2_mul_f64(a.m11, b.m12)), lm2_mul_f64(a.m12, b.m22)), lm2_mul_f64(a.m13, b.m32));
  result.m13 = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m10, b.m03), lm2_mul_f64(a.m11, b.m13)), lm2_mul_f64(a.m12, b.m23)), lm2_mul_f64(a.m13, b.m33));

  // Row 2
  result.m20 = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m20, b.m00), lm2_mul_f64(a.m21, b.m10)), lm2_mul_f64(a.m22, b.m20)), lm2_mul_f64(a.m23, b.m30));
  result.m21 = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m20, b.m01), lm2_mul_f64(a.m21, b.m11)), lm2_mul_f64(a.m22, b.m21)), lm2_mul_f64(a.m23, b.m31));
  result.m22 = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m20, b.m02), lm2_mul_f64(a.m21, b.m12)), lm2_mul_f64(a.m22, b.m22)), lm2_mul_f64(a.m23, b.m32));
  result.m23 = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m20, b.m03), lm2_mul_f64(a.m21, b.m13)), lm2_mul_f64(a.m22, b.m23)), lm2_mul_f64(a.m23, b.m33));

  // Row 3
  result.m30 = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m30, b.m00), lm2_mul_f64(a.m31, b.m10)), lm2_mul_f64(a.m32, b.m20)), lm2_mul_f64(a.m33, b.m30));
  result.m31 = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m30, b.m01), lm2_mul_f64(a.m31, b.m11)), lm2_mul_f64(a.m32, b.m21)), lm2_mul_f64(a.m33, b.m31));
  result.m32 = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m30, b.m02), lm2_mul_f64(a.m31, b.m12)), lm2_mul_f64(a.m32, b.m22)), lm2_mul_f64(a.m33, b.m32));
  result.m33 = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m30, b.m03), lm2_mul_f64(a.m31, b.m13)), lm2_mul_f64(a.m32, b.m23)), lm2_mul_f64(a.m33, b.m33));

  return result;
}

LM2_API lm2_m4x4f64 lm2_m4x4f64_transpose(lm2_m4x4f64 m) {
  lm2_m4x4f64 result = {
      m.m00, m.m10, m.m20, m.m30, m.m01, m.m11, m.m21, m.m31, m.m02, m.m12, m.m22, m.m32, m.m03, m.m13, m.m23, m.m33};
  return result;
}

LM2_API double lm2_m4x4f64_determinant(lm2_m4x4f64 m) {
  // Calculate determinant using cofactor expansion along first row
  double a00_det = lm2_sub_f64(lm2_sub_f64(lm2_mul_f64(m.m11, lm2_sub_f64(lm2_mul_f64(m.m22, m.m33), lm2_mul_f64(m.m23, m.m32))), lm2_mul_f64(m.m12, lm2_sub_f64(lm2_mul_f64(m.m21, m.m33), lm2_mul_f64(m.m23, m.m31)))), lm2_mul_f64(m.m13, lm2_sub_f64(lm2_mul_f64(m.m21, m.m32), lm2_mul_f64(m.m22, m.m31))));

  double a01_det = lm2_sub_f64(lm2_sub_f64(lm2_mul_f64(m.m10, lm2_sub_f64(lm2_mul_f64(m.m22, m.m33), lm2_mul_f64(m.m23, m.m32))), lm2_mul_f64(m.m12, lm2_sub_f64(lm2_mul_f64(m.m20, m.m33), lm2_mul_f64(m.m23, m.m30)))), lm2_mul_f64(m.m13, lm2_sub_f64(lm2_mul_f64(m.m20, m.m32), lm2_mul_f64(m.m22, m.m30))));

  double a02_det = lm2_sub_f64(lm2_sub_f64(lm2_mul_f64(m.m10, lm2_sub_f64(lm2_mul_f64(m.m21, m.m33), lm2_mul_f64(m.m23, m.m31))), lm2_mul_f64(m.m11, lm2_sub_f64(lm2_mul_f64(m.m20, m.m33), lm2_mul_f64(m.m23, m.m30)))), lm2_mul_f64(m.m13, lm2_sub_f64(lm2_mul_f64(m.m20, m.m31), lm2_mul_f64(m.m21, m.m30))));

  double a03_det = lm2_sub_f64(lm2_sub_f64(lm2_mul_f64(m.m10, lm2_sub_f64(lm2_mul_f64(m.m21, m.m32), lm2_mul_f64(m.m22, m.m31))), lm2_mul_f64(m.m11, lm2_sub_f64(lm2_mul_f64(m.m20, m.m32), lm2_mul_f64(m.m22, m.m30)))), lm2_mul_f64(m.m12, lm2_sub_f64(lm2_mul_f64(m.m20, m.m31), lm2_mul_f64(m.m21, m.m30))));

  return lm2_sub_f64(lm2_add_f64(lm2_mul_f64(m.m00, a00_det), lm2_mul_f64(m.m02, a02_det)), lm2_add_f64(lm2_mul_f64(m.m01, a01_det), lm2_mul_f64(m.m03, a03_det)));
}

LM2_API lm2_m4x4f64 lm2_m4x4f64_inverse(lm2_m4x4f64 m) {
  double det = lm2_m4x4f64_determinant(m);
  LM2_ASSERT_UNSAFE(lm2_abs_f64(det) > 1e-10);

  double inv_det = lm2_div_f64(1.0, det);

  lm2_m4x4f64 result;

  // Calculate adjugate matrix (cofactor matrix transposed) and multiply by inv_det
  result.m00 = lm2_mul_f64(lm2_add_f64(lm2_sub_f64(lm2_mul_f64(m.m11, lm2_sub_f64(lm2_mul_f64(m.m22, m.m33), lm2_mul_f64(m.m23, m.m32))), lm2_mul_f64(m.m12, lm2_sub_f64(lm2_mul_f64(m.m21, m.m33), lm2_mul_f64(m.m23, m.m31)))), lm2_mul_f64(m.m13, lm2_sub_f64(lm2_mul_f64(m.m21, m.m32), lm2_mul_f64(m.m22, m.m31)))), inv_det);
  result.m01 = lm2_mul_f64(lm2_sub_f64(lm2_add_f64(lm2_mul_f64(m.m01, lm2_sub_f64(lm2_mul_f64(m.m23, m.m32), lm2_mul_f64(m.m22, m.m33))), lm2_mul_f64(m.m02, lm2_sub_f64(lm2_mul_f64(m.m21, m.m33), lm2_mul_f64(m.m23, m.m31)))), lm2_mul_f64(m.m03, lm2_sub_f64(lm2_mul_f64(m.m21, m.m32), lm2_mul_f64(m.m22, m.m31)))), inv_det);
  result.m02 = lm2_mul_f64(lm2_add_f64(lm2_sub_f64(lm2_mul_f64(m.m01, lm2_sub_f64(lm2_mul_f64(m.m12, m.m33), lm2_mul_f64(m.m13, m.m32))), lm2_mul_f64(m.m02, lm2_sub_f64(lm2_mul_f64(m.m11, m.m33), lm2_mul_f64(m.m13, m.m31)))), lm2_mul_f64(m.m03, lm2_sub_f64(lm2_mul_f64(m.m11, m.m32), lm2_mul_f64(m.m12, m.m31)))), inv_det);
  result.m03 = lm2_mul_f64(lm2_sub_f64(lm2_add_f64(lm2_mul_f64(m.m01, lm2_sub_f64(lm2_mul_f64(m.m13, m.m22), lm2_mul_f64(m.m12, m.m23))), lm2_mul_f64(m.m02, lm2_sub_f64(lm2_mul_f64(m.m11, m.m23), lm2_mul_f64(m.m13, m.m21)))), lm2_mul_f64(m.m03, lm2_sub_f64(lm2_mul_f64(m.m11, m.m22), lm2_mul_f64(m.m12, m.m21)))), inv_det);

  result.m10 = lm2_mul_f64(lm2_sub_f64(lm2_add_f64(lm2_mul_f64(m.m10, lm2_sub_f64(lm2_mul_f64(m.m23, m.m32), lm2_mul_f64(m.m22, m.m33))), lm2_mul_f64(m.m12, lm2_sub_f64(lm2_mul_f64(m.m20, m.m33), lm2_mul_f64(m.m23, m.m30)))), lm2_mul_f64(m.m13, lm2_sub_f64(lm2_mul_f64(m.m20, m.m32), lm2_mul_f64(m.m22, m.m30)))), inv_det);
  result.m11 = lm2_mul_f64(lm2_add_f64(lm2_sub_f64(lm2_mul_f64(m.m00, lm2_sub_f64(lm2_mul_f64(m.m22, m.m33), lm2_mul_f64(m.m23, m.m32))), lm2_mul_f64(m.m02, lm2_sub_f64(lm2_mul_f64(m.m20, m.m33), lm2_mul_f64(m.m23, m.m30)))), lm2_mul_f64(m.m03, lm2_sub_f64(lm2_mul_f64(m.m20, m.m32), lm2_mul_f64(m.m22, m.m30)))), inv_det);
  result.m12 = lm2_mul_f64(lm2_sub_f64(lm2_add_f64(lm2_mul_f64(m.m00, lm2_sub_f64(lm2_mul_f64(m.m13, m.m32), lm2_mul_f64(m.m12, m.m33))), lm2_mul_f64(m.m02, lm2_sub_f64(lm2_mul_f64(m.m10, m.m33), lm2_mul_f64(m.m13, m.m30)))), lm2_mul_f64(m.m03, lm2_sub_f64(lm2_mul_f64(m.m10, m.m32), lm2_mul_f64(m.m12, m.m30)))), inv_det);
  result.m13 = lm2_mul_f64(lm2_add_f64(lm2_sub_f64(lm2_mul_f64(m.m00, lm2_sub_f64(lm2_mul_f64(m.m12, m.m23), lm2_mul_f64(m.m13, m.m22))), lm2_mul_f64(m.m02, lm2_sub_f64(lm2_mul_f64(m.m10, m.m23), lm2_mul_f64(m.m13, m.m20)))), lm2_mul_f64(m.m03, lm2_sub_f64(lm2_mul_f64(m.m10, m.m22), lm2_mul_f64(m.m12, m.m20)))), inv_det);

  result.m20 = lm2_mul_f64(lm2_add_f64(lm2_sub_f64(lm2_mul_f64(m.m10, lm2_sub_f64(lm2_mul_f64(m.m21, m.m33), lm2_mul_f64(m.m23, m.m31))), lm2_mul_f64(m.m11, lm2_sub_f64(lm2_mul_f64(m.m20, m.m33), lm2_mul_f64(m.m23, m.m30)))), lm2_mul_f64(m.m13, lm2_sub_f64(lm2_mul_f64(m.m20, m.m31), lm2_mul_f64(m.m21, m.m30)))), inv_det);
  result.m21 = lm2_mul_f64(lm2_sub_f64(lm2_add_f64(lm2_mul_f64(m.m00, lm2_sub_f64(lm2_mul_f64(m.m23, m.m31), lm2_mul_f64(m.m21, m.m33))), lm2_mul_f64(m.m01, lm2_sub_f64(lm2_mul_f64(m.m20, m.m33), lm2_mul_f64(m.m23, m.m30)))), lm2_mul_f64(m.m03, lm2_sub_f64(lm2_mul_f64(m.m20, m.m31), lm2_mul_f64(m.m21, m.m30)))), inv_det);
  result.m22 = lm2_mul_f64(lm2_add_f64(lm2_sub_f64(lm2_mul_f64(m.m00, lm2_sub_f64(lm2_mul_f64(m.m11, m.m33), lm2_mul_f64(m.m13, m.m31))), lm2_mul_f64(m.m01, lm2_sub_f64(lm2_mul_f64(m.m10, m.m33), lm2_mul_f64(m.m13, m.m30)))), lm2_mul_f64(m.m03, lm2_sub_f64(lm2_mul_f64(m.m10, m.m31), lm2_mul_f64(m.m11, m.m30)))), inv_det);
  result.m23 = lm2_mul_f64(lm2_sub_f64(lm2_add_f64(lm2_mul_f64(m.m00, lm2_sub_f64(lm2_mul_f64(m.m13, m.m21), lm2_mul_f64(m.m11, m.m23))), lm2_mul_f64(m.m01, lm2_sub_f64(lm2_mul_f64(m.m10, m.m23), lm2_mul_f64(m.m13, m.m20)))), lm2_mul_f64(m.m03, lm2_sub_f64(lm2_mul_f64(m.m10, m.m21), lm2_mul_f64(m.m11, m.m20)))), inv_det);

  result.m30 = lm2_mul_f64(lm2_sub_f64(lm2_add_f64(lm2_mul_f64(m.m10, lm2_sub_f64(lm2_mul_f64(m.m22, m.m31), lm2_mul_f64(m.m21, m.m32))), lm2_mul_f64(m.m11, lm2_sub_f64(lm2_mul_f64(m.m20, m.m32), lm2_mul_f64(m.m22, m.m30)))), lm2_mul_f64(m.m12, lm2_sub_f64(lm2_mul_f64(m.m20, m.m31), lm2_mul_f64(m.m21, m.m30)))), inv_det);
  result.m31 = lm2_mul_f64(lm2_add_f64(lm2_sub_f64(lm2_mul_f64(m.m00, lm2_sub_f64(lm2_mul_f64(m.m21, m.m32), lm2_mul_f64(m.m22, m.m31))), lm2_mul_f64(m.m01, lm2_sub_f64(lm2_mul_f64(m.m20, m.m32), lm2_mul_f64(m.m22, m.m30)))), lm2_mul_f64(m.m02, lm2_sub_f64(lm2_mul_f64(m.m20, m.m31), lm2_mul_f64(m.m21, m.m30)))), inv_det);
  result.m32 = lm2_mul_f64(lm2_sub_f64(lm2_add_f64(lm2_mul_f64(m.m00, lm2_sub_f64(lm2_mul_f64(m.m12, m.m31), lm2_mul_f64(m.m11, m.m32))), lm2_mul_f64(m.m01, lm2_sub_f64(lm2_mul_f64(m.m10, m.m32), lm2_mul_f64(m.m12, m.m30)))), lm2_mul_f64(m.m02, lm2_sub_f64(lm2_mul_f64(m.m10, m.m31), lm2_mul_f64(m.m11, m.m30)))), inv_det);
  result.m33 = lm2_mul_f64(lm2_add_f64(lm2_sub_f64(lm2_mul_f64(m.m00, lm2_sub_f64(lm2_mul_f64(m.m11, m.m22), lm2_mul_f64(m.m12, m.m21))), lm2_mul_f64(m.m01, lm2_sub_f64(lm2_mul_f64(m.m10, m.m22), lm2_mul_f64(m.m12, m.m20)))), lm2_mul_f64(m.m02, lm2_sub_f64(lm2_mul_f64(m.m10, m.m21), lm2_mul_f64(m.m11, m.m20)))), inv_det);

  return result;
}

LM2_API double lm2_m4x4f64_trace(lm2_m4x4f64 m) {
  return lm2_add_f64(lm2_add_f64(lm2_add_f64(m.m00, m.m11), m.m22), m.m33);
}

LM2_API lm2_v3f64 lm2_m4x4f64_transform_point(lm2_m4x4f64 m, lm2_v3f64 v) {
  // Transform as homogeneous point (x, y, z, 1)
  double x = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(m.m00, v.x), lm2_mul_f64(m.m01, v.y)), lm2_mul_f64(m.m02, v.z)), m.m03);
  double y = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(m.m10, v.x), lm2_mul_f64(m.m11, v.y)), lm2_mul_f64(m.m12, v.z)), m.m13);
  double z = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(m.m20, v.x), lm2_mul_f64(m.m21, v.y)), lm2_mul_f64(m.m22, v.z)), m.m23);
  double w = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(m.m30, v.x), lm2_mul_f64(m.m31, v.y)), lm2_mul_f64(m.m32, v.z)), m.m33);

  // Perspective divide if needed
  if (lm2_abs_f64(lm2_sub_f64(w, 1.0)) > 1e-10) {
    LM2_ASSERT_UNSAFE(lm2_abs_f64(w) > 1e-10);
    x = lm2_div_f64(x, w);
    y = lm2_div_f64(y, w);
    z = lm2_div_f64(z, w);
  }

  lm2_v3f64 result = {x, y, z};
  return result;
}

LM2_API lm2_v3f64 lm2_m4x4f64_transform_vector(lm2_m4x4f64 m, lm2_v3f64 v) {
  // Transform as vector (x, y, z, 0) - no translation
  double x = lm2_add_f64(lm2_add_f64(lm2_mul_f64(m.m00, v.x), lm2_mul_f64(m.m01, v.y)), lm2_mul_f64(m.m02, v.z));
  double y = lm2_add_f64(lm2_add_f64(lm2_mul_f64(m.m10, v.x), lm2_mul_f64(m.m11, v.y)), lm2_mul_f64(m.m12, v.z));
  double z = lm2_add_f64(lm2_add_f64(lm2_mul_f64(m.m20, v.x), lm2_mul_f64(m.m21, v.y)), lm2_mul_f64(m.m22, v.z));

  lm2_v3f64 result = {x, y, z};
  return result;
}

LM2_API lm2_v4f64 lm2_m4x4f64_transform(lm2_m4x4f64 m, lm2_v4f64 v) {
  // Transform full 4D vector
  double x = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(m.m00, v.x), lm2_mul_f64(m.m01, v.y)), lm2_mul_f64(m.m02, v.z)), lm2_mul_f64(m.m03, v.w));
  double y = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(m.m10, v.x), lm2_mul_f64(m.m11, v.y)), lm2_mul_f64(m.m12, v.z)), lm2_mul_f64(m.m13, v.w));
  double z = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(m.m20, v.x), lm2_mul_f64(m.m21, v.y)), lm2_mul_f64(m.m22, v.z)), lm2_mul_f64(m.m23, v.w));
  double w = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(m.m30, v.x), lm2_mul_f64(m.m31, v.y)), lm2_mul_f64(m.m32, v.z)), lm2_mul_f64(m.m33, v.w));

  lm2_v4f64 result = {x, y, z, w};
  return result;
}

LM2_API void lm2_m4x4f64_transform_points(lm2_m4x4f64 m, lm2_v3f64* points, uint32_t count) {
  LM2_ASSERT(points != NULL);

  for (uint32_t i = 0; i < count; i++) {
    points[i] = lm2_m4x4f64_transform_point(m, points[i]);
  }
}

LM2_API void lm2_m4x4f64_transform_points_src_dst(lm2_m4x4f64 m, const lm2_v3f64* src, lm2_v3f64* dst, uint32_t count) {
  LM2_ASSERT(src != NULL && dst != NULL);

  for (uint32_t i = 0; i < count; i++) {
    dst[i] = lm2_m4x4f64_transform_point(m, src[i]);
  }
}

// Getters
LM2_API lm2_v3f64 lm2_m4x4f64_get_scale(lm2_m4x4f64 m) {
  // Extract scale from matrix
  double sx = lm2_sqrt_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(m.m00, m.m00), lm2_mul_f64(m.m10, m.m10)), lm2_mul_f64(m.m20, m.m20)));
  double sy = lm2_sqrt_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(m.m01, m.m01), lm2_mul_f64(m.m11, m.m11)), lm2_mul_f64(m.m21, m.m21)));
  double sz = lm2_sqrt_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(m.m02, m.m02), lm2_mul_f64(m.m12, m.m12)), lm2_mul_f64(m.m22, m.m22)));

  lm2_v3f64 result = {sx, sy, sz};
  return result;
}

LM2_API lm2_v3f64 lm2_m4x4f64_get_translation(lm2_m4x4f64 m) {
  lm2_v3f64 result = {m.m03, m.m13, m.m23};
  return result;
}

// Projection
LM2_API lm2_m4x4f64 lm2_m4x4f64_ortho(double left, double right, double bottom, double top, double near_plane, double far_plane) {
  double rl = lm2_sub_f64(right, left);
  double tb = lm2_sub_f64(top, bottom);
  double fn = lm2_sub_f64(far_plane, near_plane);

  LM2_ASSERT_UNSAFE(lm2_abs_f64(rl) > 1e-10);
  LM2_ASSERT_UNSAFE(lm2_abs_f64(tb) > 1e-10);
  LM2_ASSERT_UNSAFE(lm2_abs_f64(fn) > 1e-10);

  lm2_m4x4f64 m;
  m.m00 = lm2_div_f64(2.0, rl);
  m.m01 = 0.0;
  m.m02 = 0.0;
  m.m03 = lm2_sub_f64(0.0, lm2_div_f64(lm2_add_f64(right, left), rl));

  m.m10 = 0.0;
  m.m11 = lm2_div_f64(2.0, tb);
  m.m12 = 0.0;
  m.m13 = lm2_sub_f64(0.0, lm2_div_f64(lm2_add_f64(top, bottom), tb));

  m.m20 = 0.0;
  m.m21 = 0.0;
  m.m22 = lm2_sub_f64(0.0, lm2_div_f64(2.0, fn));
  m.m23 = lm2_sub_f64(0.0, lm2_div_f64(lm2_add_f64(far_plane, near_plane), fn));

  m.m30 = 0.0;
  m.m31 = 0.0;
  m.m32 = 0.0;
  m.m33 = 1.0;

  return m;
}

LM2_API lm2_m4x4f64 lm2_m4x4f64_perspective(double fov_y, double aspect, double near_plane, double far_plane) {
  double tan_half_fov = lm2_tan_f64(lm2_mul_f64(fov_y, 0.5));
  double fn = lm2_sub_f64(far_plane, near_plane);

  LM2_ASSERT_UNSAFE(lm2_abs_f64(aspect) > 1e-10);
  LM2_ASSERT_UNSAFE(lm2_abs_f64(tan_half_fov) > 1e-10);
  LM2_ASSERT_UNSAFE(lm2_abs_f64(fn) > 1e-10);

  lm2_m4x4f64 m;
  m.m00 = lm2_div_f64(1.0, lm2_mul_f64(aspect, tan_half_fov));
  m.m01 = 0.0;
  m.m02 = 0.0;
  m.m03 = 0.0;

  m.m10 = 0.0;
  m.m11 = lm2_div_f64(1.0, tan_half_fov);
  m.m12 = 0.0;
  m.m13 = 0.0;

  m.m20 = 0.0;
  m.m21 = 0.0;
  m.m22 = lm2_sub_f64(0.0, lm2_div_f64(lm2_add_f64(far_plane, near_plane), fn));
  m.m23 = lm2_sub_f64(0.0, lm2_div_f64(lm2_mul_f64(2.0, lm2_mul_f64(far_plane, near_plane)), fn));

  m.m30 = 0.0;
  m.m31 = 0.0;
  m.m32 = -1.0;
  m.m33 = 0.0;

  return m;
}

LM2_API lm2_m4x4f64 lm2_m4x4f64_look_at(lm2_v3f64 eye, lm2_v3f64 target, lm2_v3f64 up) {
  // Calculate forward (z) axis
  lm2_v3f64 f = {lm2_sub_f64(target.x, eye.x), lm2_sub_f64(target.y, eye.y), lm2_sub_f64(target.z, eye.z)};
  double f_len_sq = lm2_dot_v3f64(f, f);
  double f_len = lm2_sqrt_f64(f_len_sq);
  LM2_ASSERT_UNSAFE(f_len > 1e-10);
  double f_inv_len = lm2_div_f64(1.0, f_len);
  f.x = lm2_mul_f64(f.x, f_inv_len);
  f.y = lm2_mul_f64(f.y, f_inv_len);
  f.z = lm2_mul_f64(f.z, f_inv_len);

  // Calculate right (x) axis
  lm2_v3f64 s = lm2_cross_v3f64(f, up);
  double s_len_sq = lm2_dot_v3f64(s, s);
  double s_len = lm2_sqrt_f64(s_len_sq);
  LM2_ASSERT_UNSAFE(s_len > 1e-10);
  double s_inv_len = lm2_div_f64(1.0, s_len);
  s.x = lm2_mul_f64(s.x, s_inv_len);
  s.y = lm2_mul_f64(s.y, s_inv_len);
  s.z = lm2_mul_f64(s.z, s_inv_len);

  // Calculate up (y) axis
  lm2_v3f64 u = lm2_cross_v3f64(s, f);

  lm2_m4x4f64 m;
  m.m00 = s.x;
  m.m01 = s.y;
  m.m02 = s.z;
  m.m03 = lm2_sub_f64(0.0, lm2_dot_v3f64(s, eye));

  m.m10 = u.x;
  m.m11 = u.y;
  m.m12 = u.z;
  m.m13 = lm2_sub_f64(0.0, lm2_dot_v3f64(u, eye));

  m.m20 = lm2_sub_f64(0.0, f.x);
  m.m21 = lm2_sub_f64(0.0, f.y);
  m.m22 = lm2_sub_f64(0.0, f.z);
  m.m23 = lm2_dot_v3f64(f, eye);

  m.m30 = 0.0;
  m.m31 = 0.0;
  m.m32 = 0.0;
  m.m33 = 1.0;

  return m;
}

// Quaternion conversions - f64
LM2_API lm2_m4x4f64 lm2_m4x4f64_from_quaternion(lm2_quatf64 q) {
  // Normalize quaternion
  q = lm2_quatf64_normalize(q);

  double xx = lm2_mul_f64(q.x, q.x);
  double yy = lm2_mul_f64(q.y, q.y);
  double zz = lm2_mul_f64(q.z, q.z);
  double xy = lm2_mul_f64(q.x, q.y);
  double xz = lm2_mul_f64(q.x, q.z);
  double yz = lm2_mul_f64(q.y, q.z);
  double wx = lm2_mul_f64(q.w, q.x);
  double wy = lm2_mul_f64(q.w, q.y);
  double wz = lm2_mul_f64(q.w, q.z);

  lm2_m4x4f64 m;
  m.m00 = lm2_sub_f64(1.0, lm2_mul_f64(2.0, lm2_add_f64(yy, zz)));
  m.m01 = lm2_mul_f64(2.0, lm2_sub_f64(xy, wz));
  m.m02 = lm2_mul_f64(2.0, lm2_add_f64(xz, wy));
  m.m03 = 0.0;

  m.m10 = lm2_mul_f64(2.0, lm2_add_f64(xy, wz));
  m.m11 = lm2_sub_f64(1.0, lm2_mul_f64(2.0, lm2_add_f64(xx, zz)));
  m.m12 = lm2_mul_f64(2.0, lm2_sub_f64(yz, wx));
  m.m13 = 0.0;

  m.m20 = lm2_mul_f64(2.0, lm2_sub_f64(xz, wy));
  m.m21 = lm2_mul_f64(2.0, lm2_add_f64(yz, wx));
  m.m22 = lm2_sub_f64(1.0, lm2_mul_f64(2.0, lm2_add_f64(xx, yy)));
  m.m23 = 0.0;

  m.m30 = 0.0;
  m.m31 = 0.0;
  m.m32 = 0.0;
  m.m33 = 1.0;

  return m;
}

LM2_API lm2_quatf64 lm2_m4x4f64_to_quaternion(lm2_m4x4f64 m) {
  lm2_quatf64 q;

  double trace = lm2_add_f64(lm2_add_f64(m.m00, m.m11), m.m22);

  if (trace > 0.0) {
    double s = lm2_mul_f64(0.5, lm2_div_f64(1.0, lm2_sqrt_f64(lm2_add_f64(trace, 1.0))));
    q.w = lm2_mul_f64(0.25, lm2_div_f64(1.0, s));
    q.x = lm2_mul_f64(lm2_sub_f64(m.m21, m.m12), s);
    q.y = lm2_mul_f64(lm2_sub_f64(m.m02, m.m20), s);
    q.z = lm2_mul_f64(lm2_sub_f64(m.m10, m.m01), s);
  } else if ((m.m00 > m.m11) && (m.m00 > m.m22)) {
    double s = lm2_mul_f64(2.0, lm2_sqrt_f64(lm2_add_f64(lm2_sub_f64(lm2_sub_f64(1.0, m.m00), m.m11), m.m22)));
    LM2_ASSERT_UNSAFE(lm2_abs_f64(s) > 1e-10);
    q.w = lm2_div_f64(lm2_sub_f64(m.m21, m.m12), s);
    q.x = lm2_mul_f64(0.25, s);
    q.y = lm2_div_f64(lm2_add_f64(m.m01, m.m10), s);
    q.z = lm2_div_f64(lm2_add_f64(m.m02, m.m20), s);
  } else if (m.m11 > m.m22) {
    double s = lm2_mul_f64(2.0, lm2_sqrt_f64(lm2_add_f64(lm2_sub_f64(lm2_sub_f64(1.0, m.m00), m.m11), m.m22)));
    LM2_ASSERT_UNSAFE(lm2_abs_f64(s) > 1e-10);
    q.w = lm2_div_f64(lm2_sub_f64(m.m02, m.m20), s);
    q.x = lm2_div_f64(lm2_add_f64(m.m01, m.m10), s);
    q.y = lm2_mul_f64(0.25, s);
    q.z = lm2_div_f64(lm2_add_f64(m.m12, m.m21), s);
  } else {
    double s = lm2_mul_f64(2.0, lm2_sqrt_f64(lm2_add_f64(lm2_sub_f64(lm2_sub_f64(1.0, m.m00), m.m11), m.m22)));
    LM2_ASSERT_UNSAFE(lm2_abs_f64(s) > 1e-10);
    q.w = lm2_div_f64(lm2_sub_f64(m.m10, m.m01), s);
    q.x = lm2_div_f64(lm2_add_f64(m.m02, m.m20), s);
    q.y = lm2_div_f64(lm2_add_f64(m.m12, m.m21), s);
    q.z = lm2_mul_f64(0.25, s);
  }

  return q;
}
// =============================================================================
// Matrix 4x4 Functions - f32
// =============================================================================

// Basic constructors
LM2_API lm2_m4x4f32 lm2_m4x4f32_identity(void) {
  lm2_m4x4f32 m = {
      1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  return m;
}

LM2_API lm2_m4x4f32 lm2_m4x4f32_zero(void) {
  lm2_m4x4f32 m = {
      0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
  return m;
}

LM2_API lm2_m4x4f32 lm2_m4x4f32_make(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33) {
  lm2_m4x4f32 m = {
      m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33};
  return m;
}

// Transformations
LM2_API lm2_m4x4f32 lm2_m4x4f32_scale(lm2_v3f32 scale) {
  lm2_m4x4f32 m = {
      scale.x, 0.0f, 0.0f, 0.0f, 0.0f, scale.y, 0.0f, 0.0f, 0.0f, 0.0f, scale.z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  return m;
}

LM2_API lm2_m4x4f32 lm2_m4x4f32_scale_uniform(float scale) {
  lm2_m4x4f32 m = {
      scale, 0.0f, 0.0f, 0.0f, 0.0f, scale, 0.0f, 0.0f, 0.0f, 0.0f, scale, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  return m;
}

LM2_API lm2_m4x4f32 lm2_m4x4f32_translate(lm2_v3f32 translation) {
  lm2_m4x4f32 m = {
      1.0f, 0.0f, 0.0f, translation.x, 0.0f, 1.0f, 0.0f, translation.y, 0.0f, 0.0f, 1.0f, translation.z, 0.0f, 0.0f, 0.0f, 1.0f};
  return m;
}

LM2_API lm2_m4x4f32 lm2_m4x4f32_rotate_x(float angle) {
  float c = lm2_cos_f32(angle);
  float s = lm2_sin_f32(angle);

  lm2_m4x4f32 m = {
      1.0f, 0.0f, 0.0f, 0.0f, 0.0f, c, lm2_sub_f32(0.0f, s), 0.0f, 0.0f, s, c, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  return m;
}

LM2_API lm2_m4x4f32 lm2_m4x4f32_rotate_y(float angle) {
  float c = lm2_cos_f32(angle);
  float s = lm2_sin_f32(angle);

  lm2_m4x4f32 m = {
      c, 0.0f, s, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, lm2_sub_f32(0.0f, s), 0.0f, c, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  return m;
}

LM2_API lm2_m4x4f32 lm2_m4x4f32_rotate_z(float angle) {
  float c = lm2_cos_f32(angle);
  float s = lm2_sin_f32(angle);

  lm2_m4x4f32 m = {
      c, lm2_sub_f32(0.0f, s), 0.0f, 0.0f, s, c, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  return m;
}

LM2_API lm2_m4x4f32 lm2_m4x4f32_rotate_axis(lm2_v3f32 axis, float angle) {
  // Normalize axis
  float len_sq = lm2_add_f32(lm2_add_f32(lm2_mul_f32(axis.x, axis.x), lm2_mul_f32(axis.y, axis.y)), lm2_mul_f32(axis.z, axis.z));
  float len = lm2_sqrt_f32(len_sq);
  LM2_ASSERT_UNSAFE(len > 0.0f);

  float inv_len = lm2_div_f32(1.0f, len);
  float x = lm2_mul_f32(axis.x, inv_len);
  float y = lm2_mul_f32(axis.y, inv_len);
  float z = lm2_mul_f32(axis.z, inv_len);

  float c = lm2_cos_f32(angle);
  float s = lm2_sin_f32(angle);
  float t = lm2_sub_f32(1.0f, c);

  lm2_m4x4f32 m;
  m.m00 = lm2_add_f32(lm2_mul_f32(t, lm2_mul_f32(x, x)), c);
  m.m01 = lm2_sub_f32(lm2_mul_f32(t, lm2_mul_f32(x, y)), lm2_mul_f32(z, s));
  m.m02 = lm2_add_f32(lm2_mul_f32(t, lm2_mul_f32(x, z)), lm2_mul_f32(y, s));
  m.m03 = 0.0f;

  m.m10 = lm2_add_f32(lm2_mul_f32(t, lm2_mul_f32(x, y)), lm2_mul_f32(z, s));
  m.m11 = lm2_add_f32(lm2_mul_f32(t, lm2_mul_f32(y, y)), c);
  m.m12 = lm2_sub_f32(lm2_mul_f32(t, lm2_mul_f32(y, z)), lm2_mul_f32(x, s));
  m.m13 = 0.0f;

  m.m20 = lm2_sub_f32(lm2_mul_f32(t, lm2_mul_f32(x, z)), lm2_mul_f32(y, s));
  m.m21 = lm2_add_f32(lm2_mul_f32(t, lm2_mul_f32(y, z)), lm2_mul_f32(x, s));
  m.m22 = lm2_add_f32(lm2_mul_f32(t, lm2_mul_f32(z, z)), c);
  m.m23 = 0.0f;

  m.m30 = 0.0f;
  m.m31 = 0.0f;
  m.m32 = 0.0f;
  m.m33 = 1.0f;

  return m;
}

LM2_API lm2_m4x4f32 lm2_m4x4f32_scale_translate(lm2_v3f32 scale, lm2_v3f32 translation) {
  lm2_m4x4f32 m = {
      scale.x, 0.0f, 0.0f, translation.x, 0.0f, scale.y, 0.0f, translation.y, 0.0f, 0.0f, scale.z, translation.z, 0.0f, 0.0f, 0.0f, 1.0f};
  return m;
}

LM2_API lm2_m4x4f32 lm2_m4x4f32_world_transform(lm2_v3f32 translation, lm2_v3f32 scale, lm2_v3f32 rotation_euler) {
  // T * R * S
  lm2_m4x4f32 s = lm2_m4x4f32_scale(scale);
  lm2_m4x4f32 rx = lm2_m4x4f32_rotate_x(rotation_euler.x);
  lm2_m4x4f32 ry = lm2_m4x4f32_rotate_y(rotation_euler.y);
  lm2_m4x4f32 rz = lm2_m4x4f32_rotate_z(rotation_euler.z);
  lm2_m4x4f32 t = lm2_m4x4f32_translate(translation);

  lm2_m4x4f32 temp1 = lm2_m4x4f32_multiply(rz, s);
  lm2_m4x4f32 temp2 = lm2_m4x4f32_multiply(ry, temp1);
  lm2_m4x4f32 temp3 = lm2_m4x4f32_multiply(rx, temp2);
  return lm2_m4x4f32_multiply(t, temp3);
}

// Operations
LM2_API lm2_m4x4f32 lm2_m4x4f32_multiply(lm2_m4x4f32 a, lm2_m4x4f32 b) {
  lm2_m4x4f32 result;

  // Row 0
  result.m00 = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m00, b.m00), lm2_mul_f32(a.m01, b.m10)), lm2_mul_f32(a.m02, b.m20)), lm2_mul_f32(a.m03, b.m30));
  result.m01 = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m00, b.m01), lm2_mul_f32(a.m01, b.m11)), lm2_mul_f32(a.m02, b.m21)), lm2_mul_f32(a.m03, b.m31));
  result.m02 = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m00, b.m02), lm2_mul_f32(a.m01, b.m12)), lm2_mul_f32(a.m02, b.m22)), lm2_mul_f32(a.m03, b.m32));
  result.m03 = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m00, b.m03), lm2_mul_f32(a.m01, b.m13)), lm2_mul_f32(a.m02, b.m23)), lm2_mul_f32(a.m03, b.m33));

  // Row 1
  result.m10 = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m10, b.m00), lm2_mul_f32(a.m11, b.m10)), lm2_mul_f32(a.m12, b.m20)), lm2_mul_f32(a.m13, b.m30));
  result.m11 = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m10, b.m01), lm2_mul_f32(a.m11, b.m11)), lm2_mul_f32(a.m12, b.m21)), lm2_mul_f32(a.m13, b.m31));
  result.m12 = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m10, b.m02), lm2_mul_f32(a.m11, b.m12)), lm2_mul_f32(a.m12, b.m22)), lm2_mul_f32(a.m13, b.m32));
  result.m13 = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m10, b.m03), lm2_mul_f32(a.m11, b.m13)), lm2_mul_f32(a.m12, b.m23)), lm2_mul_f32(a.m13, b.m33));

  // Row 2
  result.m20 = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m20, b.m00), lm2_mul_f32(a.m21, b.m10)), lm2_mul_f32(a.m22, b.m20)), lm2_mul_f32(a.m23, b.m30));
  result.m21 = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m20, b.m01), lm2_mul_f32(a.m21, b.m11)), lm2_mul_f32(a.m22, b.m21)), lm2_mul_f32(a.m23, b.m31));
  result.m22 = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m20, b.m02), lm2_mul_f32(a.m21, b.m12)), lm2_mul_f32(a.m22, b.m22)), lm2_mul_f32(a.m23, b.m32));
  result.m23 = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m20, b.m03), lm2_mul_f32(a.m21, b.m13)), lm2_mul_f32(a.m22, b.m23)), lm2_mul_f32(a.m23, b.m33));

  // Row 3
  result.m30 = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m30, b.m00), lm2_mul_f32(a.m31, b.m10)), lm2_mul_f32(a.m32, b.m20)), lm2_mul_f32(a.m33, b.m30));
  result.m31 = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m30, b.m01), lm2_mul_f32(a.m31, b.m11)), lm2_mul_f32(a.m32, b.m21)), lm2_mul_f32(a.m33, b.m31));
  result.m32 = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m30, b.m02), lm2_mul_f32(a.m31, b.m12)), lm2_mul_f32(a.m32, b.m22)), lm2_mul_f32(a.m33, b.m32));
  result.m33 = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m30, b.m03), lm2_mul_f32(a.m31, b.m13)), lm2_mul_f32(a.m32, b.m23)), lm2_mul_f32(a.m33, b.m33));

  return result;
}

LM2_API lm2_m4x4f32 lm2_m4x4f32_transpose(lm2_m4x4f32 m) {
  lm2_m4x4f32 result = {
      m.m00, m.m10, m.m20, m.m30, m.m01, m.m11, m.m21, m.m31, m.m02, m.m12, m.m22, m.m32, m.m03, m.m13, m.m23, m.m33};
  return result;
}

LM2_API float lm2_m4x4f32_determinant(lm2_m4x4f32 m) {
  // Calculate determinant using cofactor expansion along first row
  float a00_det = lm2_sub_f32(lm2_sub_f32(lm2_mul_f32(m.m11, lm2_sub_f32(lm2_mul_f32(m.m22, m.m33), lm2_mul_f32(m.m23, m.m32))), lm2_mul_f32(m.m12, lm2_sub_f32(lm2_mul_f32(m.m21, m.m33), lm2_mul_f32(m.m23, m.m31)))), lm2_mul_f32(m.m13, lm2_sub_f32(lm2_mul_f32(m.m21, m.m32), lm2_mul_f32(m.m22, m.m31))));

  float a01_det = lm2_sub_f32(lm2_sub_f32(lm2_mul_f32(m.m10, lm2_sub_f32(lm2_mul_f32(m.m22, m.m33), lm2_mul_f32(m.m23, m.m32))), lm2_mul_f32(m.m12, lm2_sub_f32(lm2_mul_f32(m.m20, m.m33), lm2_mul_f32(m.m23, m.m30)))), lm2_mul_f32(m.m13, lm2_sub_f32(lm2_mul_f32(m.m20, m.m32), lm2_mul_f32(m.m22, m.m30))));

  float a02_det = lm2_sub_f32(lm2_sub_f32(lm2_mul_f32(m.m10, lm2_sub_f32(lm2_mul_f32(m.m21, m.m33), lm2_mul_f32(m.m23, m.m31))), lm2_mul_f32(m.m11, lm2_sub_f32(lm2_mul_f32(m.m20, m.m33), lm2_mul_f32(m.m23, m.m30)))), lm2_mul_f32(m.m13, lm2_sub_f32(lm2_mul_f32(m.m20, m.m31), lm2_mul_f32(m.m21, m.m30))));

  float a03_det = lm2_sub_f32(lm2_sub_f32(lm2_mul_f32(m.m10, lm2_sub_f32(lm2_mul_f32(m.m21, m.m32), lm2_mul_f32(m.m22, m.m31))), lm2_mul_f32(m.m11, lm2_sub_f32(lm2_mul_f32(m.m20, m.m32), lm2_mul_f32(m.m22, m.m30)))), lm2_mul_f32(m.m12, lm2_sub_f32(lm2_mul_f32(m.m20, m.m31), lm2_mul_f32(m.m21, m.m30))));

  return lm2_sub_f32(lm2_add_f32(lm2_mul_f32(m.m00, a00_det), lm2_mul_f32(m.m02, a02_det)), lm2_add_f32(lm2_mul_f32(m.m01, a01_det), lm2_mul_f32(m.m03, a03_det)));
}

LM2_API lm2_m4x4f32 lm2_m4x4f32_inverse(lm2_m4x4f32 m) {
  float det = lm2_m4x4f32_determinant(m);
  LM2_ASSERT_UNSAFE(lm2_abs_f32(det) > 1e-6f);

  float inv_det = lm2_div_f32(1.0f, det);

  lm2_m4x4f32 result;

  // Calculate adjugate matrix (cofactor matrix transposed) and multiply by inv_det
  result.m00 = lm2_mul_f32(lm2_add_f32(lm2_sub_f32(lm2_mul_f32(m.m11, lm2_sub_f32(lm2_mul_f32(m.m22, m.m33), lm2_mul_f32(m.m23, m.m32))), lm2_mul_f32(m.m12, lm2_sub_f32(lm2_mul_f32(m.m21, m.m33), lm2_mul_f32(m.m23, m.m31)))), lm2_mul_f32(m.m13, lm2_sub_f32(lm2_mul_f32(m.m21, m.m32), lm2_mul_f32(m.m22, m.m31)))), inv_det);
  result.m01 = lm2_mul_f32(lm2_sub_f32(lm2_add_f32(lm2_mul_f32(m.m01, lm2_sub_f32(lm2_mul_f32(m.m23, m.m32), lm2_mul_f32(m.m22, m.m33))), lm2_mul_f32(m.m02, lm2_sub_f32(lm2_mul_f32(m.m21, m.m33), lm2_mul_f32(m.m23, m.m31)))), lm2_mul_f32(m.m03, lm2_sub_f32(lm2_mul_f32(m.m21, m.m32), lm2_mul_f32(m.m22, m.m31)))), inv_det);
  result.m02 = lm2_mul_f32(lm2_add_f32(lm2_sub_f32(lm2_mul_f32(m.m01, lm2_sub_f32(lm2_mul_f32(m.m12, m.m33), lm2_mul_f32(m.m13, m.m32))), lm2_mul_f32(m.m02, lm2_sub_f32(lm2_mul_f32(m.m11, m.m33), lm2_mul_f32(m.m13, m.m31)))), lm2_mul_f32(m.m03, lm2_sub_f32(lm2_mul_f32(m.m11, m.m32), lm2_mul_f32(m.m12, m.m31)))), inv_det);
  result.m03 = lm2_mul_f32(lm2_sub_f32(lm2_add_f32(lm2_mul_f32(m.m01, lm2_sub_f32(lm2_mul_f32(m.m13, m.m22), lm2_mul_f32(m.m12, m.m23))), lm2_mul_f32(m.m02, lm2_sub_f32(lm2_mul_f32(m.m11, m.m23), lm2_mul_f32(m.m13, m.m21)))), lm2_mul_f32(m.m03, lm2_sub_f32(lm2_mul_f32(m.m11, m.m22), lm2_mul_f32(m.m12, m.m21)))), inv_det);

  result.m10 = lm2_mul_f32(lm2_sub_f32(lm2_add_f32(lm2_mul_f32(m.m10, lm2_sub_f32(lm2_mul_f32(m.m23, m.m32), lm2_mul_f32(m.m22, m.m33))), lm2_mul_f32(m.m12, lm2_sub_f32(lm2_mul_f32(m.m20, m.m33), lm2_mul_f32(m.m23, m.m30)))), lm2_mul_f32(m.m13, lm2_sub_f32(lm2_mul_f32(m.m20, m.m32), lm2_mul_f32(m.m22, m.m30)))), inv_det);
  result.m11 = lm2_mul_f32(lm2_add_f32(lm2_sub_f32(lm2_mul_f32(m.m00, lm2_sub_f32(lm2_mul_f32(m.m22, m.m33), lm2_mul_f32(m.m23, m.m32))), lm2_mul_f32(m.m02, lm2_sub_f32(lm2_mul_f32(m.m20, m.m33), lm2_mul_f32(m.m23, m.m30)))), lm2_mul_f32(m.m03, lm2_sub_f32(lm2_mul_f32(m.m20, m.m32), lm2_mul_f32(m.m22, m.m30)))), inv_det);
  result.m12 = lm2_mul_f32(lm2_sub_f32(lm2_add_f32(lm2_mul_f32(m.m00, lm2_sub_f32(lm2_mul_f32(m.m13, m.m32), lm2_mul_f32(m.m12, m.m33))), lm2_mul_f32(m.m02, lm2_sub_f32(lm2_mul_f32(m.m10, m.m33), lm2_mul_f32(m.m13, m.m30)))), lm2_mul_f32(m.m03, lm2_sub_f32(lm2_mul_f32(m.m10, m.m32), lm2_mul_f32(m.m12, m.m30)))), inv_det);
  result.m13 = lm2_mul_f32(lm2_add_f32(lm2_sub_f32(lm2_mul_f32(m.m00, lm2_sub_f32(lm2_mul_f32(m.m12, m.m23), lm2_mul_f32(m.m13, m.m22))), lm2_mul_f32(m.m02, lm2_sub_f32(lm2_mul_f32(m.m10, m.m23), lm2_mul_f32(m.m13, m.m20)))), lm2_mul_f32(m.m03, lm2_sub_f32(lm2_mul_f32(m.m10, m.m22), lm2_mul_f32(m.m12, m.m20)))), inv_det);

  result.m20 = lm2_mul_f32(lm2_add_f32(lm2_sub_f32(lm2_mul_f32(m.m10, lm2_sub_f32(lm2_mul_f32(m.m21, m.m33), lm2_mul_f32(m.m23, m.m31))), lm2_mul_f32(m.m11, lm2_sub_f32(lm2_mul_f32(m.m20, m.m33), lm2_mul_f32(m.m23, m.m30)))), lm2_mul_f32(m.m13, lm2_sub_f32(lm2_mul_f32(m.m20, m.m31), lm2_mul_f32(m.m21, m.m30)))), inv_det);
  result.m21 = lm2_mul_f32(lm2_sub_f32(lm2_add_f32(lm2_mul_f32(m.m00, lm2_sub_f32(lm2_mul_f32(m.m23, m.m31), lm2_mul_f32(m.m21, m.m33))), lm2_mul_f32(m.m01, lm2_sub_f32(lm2_mul_f32(m.m20, m.m33), lm2_mul_f32(m.m23, m.m30)))), lm2_mul_f32(m.m03, lm2_sub_f32(lm2_mul_f32(m.m20, m.m31), lm2_mul_f32(m.m21, m.m30)))), inv_det);
  result.m22 = lm2_mul_f32(lm2_add_f32(lm2_sub_f32(lm2_mul_f32(m.m00, lm2_sub_f32(lm2_mul_f32(m.m11, m.m33), lm2_mul_f32(m.m13, m.m31))), lm2_mul_f32(m.m01, lm2_sub_f32(lm2_mul_f32(m.m10, m.m33), lm2_mul_f32(m.m13, m.m30)))), lm2_mul_f32(m.m03, lm2_sub_f32(lm2_mul_f32(m.m10, m.m31), lm2_mul_f32(m.m11, m.m30)))), inv_det);
  result.m23 = lm2_mul_f32(lm2_sub_f32(lm2_add_f32(lm2_mul_f32(m.m00, lm2_sub_f32(lm2_mul_f32(m.m13, m.m21), lm2_mul_f32(m.m11, m.m23))), lm2_mul_f32(m.m01, lm2_sub_f32(lm2_mul_f32(m.m10, m.m23), lm2_mul_f32(m.m13, m.m20)))), lm2_mul_f32(m.m03, lm2_sub_f32(lm2_mul_f32(m.m10, m.m21), lm2_mul_f32(m.m11, m.m20)))), inv_det);

  result.m30 = lm2_mul_f32(lm2_sub_f32(lm2_add_f32(lm2_mul_f32(m.m10, lm2_sub_f32(lm2_mul_f32(m.m22, m.m31), lm2_mul_f32(m.m21, m.m32))), lm2_mul_f32(m.m11, lm2_sub_f32(lm2_mul_f32(m.m20, m.m32), lm2_mul_f32(m.m22, m.m30)))), lm2_mul_f32(m.m12, lm2_sub_f32(lm2_mul_f32(m.m20, m.m31), lm2_mul_f32(m.m21, m.m30)))), inv_det);
  result.m31 = lm2_mul_f32(lm2_add_f32(lm2_sub_f32(lm2_mul_f32(m.m00, lm2_sub_f32(lm2_mul_f32(m.m21, m.m32), lm2_mul_f32(m.m22, m.m31))), lm2_mul_f32(m.m01, lm2_sub_f32(lm2_mul_f32(m.m20, m.m32), lm2_mul_f32(m.m22, m.m30)))), lm2_mul_f32(m.m02, lm2_sub_f32(lm2_mul_f32(m.m20, m.m31), lm2_mul_f32(m.m21, m.m30)))), inv_det);
  result.m32 = lm2_mul_f32(lm2_sub_f32(lm2_add_f32(lm2_mul_f32(m.m00, lm2_sub_f32(lm2_mul_f32(m.m12, m.m31), lm2_mul_f32(m.m11, m.m32))), lm2_mul_f32(m.m01, lm2_sub_f32(lm2_mul_f32(m.m10, m.m32), lm2_mul_f32(m.m12, m.m30)))), lm2_mul_f32(m.m02, lm2_sub_f32(lm2_mul_f32(m.m10, m.m31), lm2_mul_f32(m.m11, m.m30)))), inv_det);
  result.m33 = lm2_mul_f32(lm2_add_f32(lm2_sub_f32(lm2_mul_f32(m.m00, lm2_sub_f32(lm2_mul_f32(m.m11, m.m22), lm2_mul_f32(m.m12, m.m21))), lm2_mul_f32(m.m01, lm2_sub_f32(lm2_mul_f32(m.m10, m.m22), lm2_mul_f32(m.m12, m.m20)))), lm2_mul_f32(m.m02, lm2_sub_f32(lm2_mul_f32(m.m10, m.m21), lm2_mul_f32(m.m11, m.m20)))), inv_det);

  return result;
}

LM2_API float lm2_m4x4f32_trace(lm2_m4x4f32 m) {
  return lm2_add_f32(lm2_add_f32(lm2_add_f32(m.m00, m.m11), m.m22), m.m33);
}

LM2_API lm2_v3f32 lm2_m4x4f32_transform_point(lm2_m4x4f32 m, lm2_v3f32 v) {
  // Transform as homogeneous point (x, y, z, 1)
  float x = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(m.m00, v.x), lm2_mul_f32(m.m01, v.y)), lm2_mul_f32(m.m02, v.z)), m.m03);
  float y = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(m.m10, v.x), lm2_mul_f32(m.m11, v.y)), lm2_mul_f32(m.m12, v.z)), m.m13);
  float z = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(m.m20, v.x), lm2_mul_f32(m.m21, v.y)), lm2_mul_f32(m.m22, v.z)), m.m23);
  float w = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(m.m30, v.x), lm2_mul_f32(m.m31, v.y)), lm2_mul_f32(m.m32, v.z)), m.m33);

  // Perspective divide if needed
  if (lm2_abs_f32(lm2_sub_f32(w, 1.0f)) > 1e-6f) {
    LM2_ASSERT_UNSAFE(lm2_abs_f32(w) > 1e-6f);
    x = lm2_div_f32(x, w);
    y = lm2_div_f32(y, w);
    z = lm2_div_f32(z, w);
  }

  lm2_v3f32 result = {x, y, z};
  return result;
}

LM2_API lm2_v3f32 lm2_m4x4f32_transform_vector(lm2_m4x4f32 m, lm2_v3f32 v) {
  // Transform as vector (x, y, z, 0) - no translation
  float x = lm2_add_f32(lm2_add_f32(lm2_mul_f32(m.m00, v.x), lm2_mul_f32(m.m01, v.y)), lm2_mul_f32(m.m02, v.z));
  float y = lm2_add_f32(lm2_add_f32(lm2_mul_f32(m.m10, v.x), lm2_mul_f32(m.m11, v.y)), lm2_mul_f32(m.m12, v.z));
  float z = lm2_add_f32(lm2_add_f32(lm2_mul_f32(m.m20, v.x), lm2_mul_f32(m.m21, v.y)), lm2_mul_f32(m.m22, v.z));

  lm2_v3f32 result = {x, y, z};
  return result;
}

LM2_API lm2_v4f32 lm2_m4x4f32_transform(lm2_m4x4f32 m, lm2_v4f32 v) {
  // Transform full 4D vector
  float x = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(m.m00, v.x), lm2_mul_f32(m.m01, v.y)), lm2_mul_f32(m.m02, v.z)), lm2_mul_f32(m.m03, v.w));
  float y = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(m.m10, v.x), lm2_mul_f32(m.m11, v.y)), lm2_mul_f32(m.m12, v.z)), lm2_mul_f32(m.m13, v.w));
  float z = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(m.m20, v.x), lm2_mul_f32(m.m21, v.y)), lm2_mul_f32(m.m22, v.z)), lm2_mul_f32(m.m23, v.w));
  float w = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(m.m30, v.x), lm2_mul_f32(m.m31, v.y)), lm2_mul_f32(m.m32, v.z)), lm2_mul_f32(m.m33, v.w));

  lm2_v4f32 result = {x, y, z, w};
  return result;
}

LM2_API void lm2_m4x4f32_transform_points(lm2_m4x4f32 m, lm2_v3f32* points, uint32_t count) {
  LM2_ASSERT(points != NULL);

  for (uint32_t i = 0; i < count; i++) {
    points[i] = lm2_m4x4f32_transform_point(m, points[i]);
  }
}

LM2_API void lm2_m4x4f32_transform_points_src_dst(lm2_m4x4f32 m, const lm2_v3f32* src, lm2_v3f32* dst, uint32_t count) {
  LM2_ASSERT(src != NULL && dst != NULL);

  for (uint32_t i = 0; i < count; i++) {
    dst[i] = lm2_m4x4f32_transform_point(m, src[i]);
  }
}

// Getters
LM2_API lm2_v3f32 lm2_m4x4f32_get_scale(lm2_m4x4f32 m) {
  // Extract scale from matrix
  float sx = lm2_sqrt_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(m.m00, m.m00), lm2_mul_f32(m.m10, m.m10)), lm2_mul_f32(m.m20, m.m20)));
  float sy = lm2_sqrt_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(m.m01, m.m01), lm2_mul_f32(m.m11, m.m11)), lm2_mul_f32(m.m21, m.m21)));
  float sz = lm2_sqrt_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(m.m02, m.m02), lm2_mul_f32(m.m12, m.m12)), lm2_mul_f32(m.m22, m.m22)));

  lm2_v3f32 result = {sx, sy, sz};
  return result;
}

LM2_API lm2_v3f32 lm2_m4x4f32_get_translation(lm2_m4x4f32 m) {
  lm2_v3f32 result = {m.m03, m.m13, m.m23};
  return result;
}

// Projection
LM2_API lm2_m4x4f32 lm2_m4x4f32_ortho(float left, float right, float bottom, float top, float near_plane, float far_plane) {
  float rl = lm2_sub_f32(right, left);
  float tb = lm2_sub_f32(top, bottom);
  float fn = lm2_sub_f32(far_plane, near_plane);

  LM2_ASSERT_UNSAFE(lm2_abs_f32(rl) > 1e-6f);
  LM2_ASSERT_UNSAFE(lm2_abs_f32(tb) > 1e-6f);
  LM2_ASSERT_UNSAFE(lm2_abs_f32(fn) > 1e-6f);

  lm2_m4x4f32 m;
  m.m00 = lm2_div_f32(2.0f, rl);
  m.m01 = 0.0f;
  m.m02 = 0.0f;
  m.m03 = lm2_sub_f32(0.0f, lm2_div_f32(lm2_add_f32(right, left), rl));

  m.m10 = 0.0f;
  m.m11 = lm2_div_f32(2.0f, tb);
  m.m12 = 0.0f;
  m.m13 = lm2_sub_f32(0.0f, lm2_div_f32(lm2_add_f32(top, bottom), tb));

  m.m20 = 0.0f;
  m.m21 = 0.0f;
  m.m22 = lm2_sub_f32(0.0f, lm2_div_f32(2.0f, fn));
  m.m23 = lm2_sub_f32(0.0f, lm2_div_f32(lm2_add_f32(far_plane, near_plane), fn));

  m.m30 = 0.0f;
  m.m31 = 0.0f;
  m.m32 = 0.0f;
  m.m33 = 1.0f;

  return m;
}

LM2_API lm2_m4x4f32 lm2_m4x4f32_perspective(float fov_y, float aspect, float near_plane, float far_plane) {
  float tan_half_fov = lm2_tan_f32(lm2_mul_f32(fov_y, 0.5f));
  float fn = lm2_sub_f32(far_plane, near_plane);

  LM2_ASSERT_UNSAFE(lm2_abs_f32(aspect) > 1e-6f);
  LM2_ASSERT_UNSAFE(lm2_abs_f32(tan_half_fov) > 1e-6f);
  LM2_ASSERT_UNSAFE(lm2_abs_f32(fn) > 1e-6f);

  lm2_m4x4f32 m;
  m.m00 = lm2_div_f32(1.0f, lm2_mul_f32(aspect, tan_half_fov));
  m.m01 = 0.0f;
  m.m02 = 0.0f;
  m.m03 = 0.0f;

  m.m10 = 0.0f;
  m.m11 = lm2_div_f32(1.0f, tan_half_fov);
  m.m12 = 0.0f;
  m.m13 = 0.0f;

  m.m20 = 0.0f;
  m.m21 = 0.0f;
  m.m22 = lm2_sub_f32(0.0f, lm2_div_f32(lm2_add_f32(far_plane, near_plane), fn));
  m.m23 = lm2_sub_f32(0.0f, lm2_div_f32(lm2_mul_f32(2.0f, lm2_mul_f32(far_plane, near_plane)), fn));

  m.m30 = 0.0f;
  m.m31 = 0.0f;
  m.m32 = -1.0f;
  m.m33 = 0.0f;

  return m;
}

LM2_API lm2_m4x4f32 lm2_m4x4f32_look_at(lm2_v3f32 eye, lm2_v3f32 target, lm2_v3f32 up) {
  // Calculate forward (z) axis
  lm2_v3f32 f = {lm2_sub_f32(target.x, eye.x), lm2_sub_f32(target.y, eye.y), lm2_sub_f32(target.z, eye.z)};
  float f_len_sq = lm2_dot_v3f32(f, f);
  float f_len = lm2_sqrt_f32(f_len_sq);
  LM2_ASSERT_UNSAFE(f_len > 1e-6f);
  float f_inv_len = lm2_div_f32(1.0f, f_len);
  f.x = lm2_mul_f32(f.x, f_inv_len);
  f.y = lm2_mul_f32(f.y, f_inv_len);
  f.z = lm2_mul_f32(f.z, f_inv_len);

  // Calculate right (x) axis
  lm2_v3f32 s = lm2_cross_v3f32(f, up);
  float s_len_sq = lm2_dot_v3f32(s, s);
  float s_len = lm2_sqrt_f32(s_len_sq);
  LM2_ASSERT_UNSAFE(s_len > 1e-6f);
  float s_inv_len = lm2_div_f32(1.0f, s_len);
  s.x = lm2_mul_f32(s.x, s_inv_len);
  s.y = lm2_mul_f32(s.y, s_inv_len);
  s.z = lm2_mul_f32(s.z, s_inv_len);

  // Calculate up (y) axis
  lm2_v3f32 u = lm2_cross_v3f32(s, f);

  lm2_m4x4f32 m;
  m.m00 = s.x;
  m.m01 = s.y;
  m.m02 = s.z;
  m.m03 = lm2_sub_f32(0.0f, lm2_dot_v3f32(s, eye));

  m.m10 = u.x;
  m.m11 = u.y;
  m.m12 = u.z;
  m.m13 = lm2_sub_f32(0.0f, lm2_dot_v3f32(u, eye));

  m.m20 = lm2_sub_f32(0.0f, f.x);
  m.m21 = lm2_sub_f32(0.0f, f.y);
  m.m22 = lm2_sub_f32(0.0f, f.z);
  m.m23 = lm2_dot_v3f32(f, eye);

  m.m30 = 0.0f;
  m.m31 = 0.0f;
  m.m32 = 0.0f;
  m.m33 = 1.0f;

  return m;
}

// Quaternion conversions - f32
LM2_API lm2_m4x4f32 lm2_m4x4f32_from_quaternion(lm2_quatf32 q) {
  // Normalize quaternion
  q = lm2_quatf32_normalize(q);

  float xx = lm2_mul_f32(q.x, q.x);
  float yy = lm2_mul_f32(q.y, q.y);
  float zz = lm2_mul_f32(q.z, q.z);
  float xy = lm2_mul_f32(q.x, q.y);
  float xz = lm2_mul_f32(q.x, q.z);
  float yz = lm2_mul_f32(q.y, q.z);
  float wx = lm2_mul_f32(q.w, q.x);
  float wy = lm2_mul_f32(q.w, q.y);
  float wz = lm2_mul_f32(q.w, q.z);

  lm2_m4x4f32 m;
  m.m00 = lm2_sub_f32(1.0f, lm2_mul_f32(2.0f, lm2_add_f32(yy, zz)));
  m.m01 = lm2_mul_f32(2.0f, lm2_sub_f32(xy, wz));
  m.m02 = lm2_mul_f32(2.0f, lm2_add_f32(xz, wy));
  m.m03 = 0.0f;

  m.m10 = lm2_mul_f32(2.0f, lm2_add_f32(xy, wz));
  m.m11 = lm2_sub_f32(1.0f, lm2_mul_f32(2.0f, lm2_add_f32(xx, zz)));
  m.m12 = lm2_mul_f32(2.0f, lm2_sub_f32(yz, wx));
  m.m13 = 0.0f;

  m.m20 = lm2_mul_f32(2.0f, lm2_sub_f32(xz, wy));
  m.m21 = lm2_mul_f32(2.0f, lm2_add_f32(yz, wx));
  m.m22 = lm2_sub_f32(1.0f, lm2_mul_f32(2.0f, lm2_add_f32(xx, yy)));
  m.m23 = 0.0f;

  m.m30 = 0.0f;
  m.m31 = 0.0f;
  m.m32 = 0.0f;
  m.m33 = 1.0f;

  return m;
}

LM2_API lm2_quatf32 lm2_m4x4f32_to_quaternion(lm2_m4x4f32 m) {
  lm2_quatf32 q;

  float trace = lm2_add_f32(lm2_add_f32(m.m00, m.m11), m.m22);

  if (trace > 0.0f) {
    float s = lm2_mul_f32(0.5f, lm2_div_f32(1.0f, lm2_sqrt_f32(lm2_add_f32(trace, 1.0f))));
    q.w = lm2_mul_f32(0.25f, lm2_div_f32(1.0f, s));
    q.x = lm2_mul_f32(lm2_sub_f32(m.m21, m.m12), s);
    q.y = lm2_mul_f32(lm2_sub_f32(m.m02, m.m20), s);
    q.z = lm2_mul_f32(lm2_sub_f32(m.m10, m.m01), s);
  } else if ((m.m00 > m.m11) && (m.m00 > m.m22)) {
    float s = lm2_mul_f32(2.0f, lm2_sqrt_f32(lm2_add_f32(lm2_sub_f32(lm2_sub_f32(1.0f, m.m00), m.m11), m.m22)));
    LM2_ASSERT_UNSAFE(lm2_abs_f32(s) > 1e-6f);
    q.w = lm2_div_f32(lm2_sub_f32(m.m21, m.m12), s);
    q.x = lm2_mul_f32(0.25f, s);
    q.y = lm2_div_f32(lm2_add_f32(m.m01, m.m10), s);
    q.z = lm2_div_f32(lm2_add_f32(m.m02, m.m20), s);
  } else if (m.m11 > m.m22) {
    float s = lm2_mul_f32(2.0f, lm2_sqrt_f32(lm2_add_f32(lm2_sub_f32(lm2_sub_f32(1.0f, m.m00), m.m11), m.m22)));
    LM2_ASSERT_UNSAFE(lm2_abs_f32(s) > 1e-6f);
    q.w = lm2_div_f32(lm2_sub_f32(m.m02, m.m20), s);
    q.x = lm2_div_f32(lm2_add_f32(m.m01, m.m10), s);
    q.y = lm2_mul_f32(0.25f, s);
    q.z = lm2_div_f32(lm2_add_f32(m.m12, m.m21), s);
  } else {
    float s = lm2_mul_f32(2.0f, lm2_sqrt_f32(lm2_add_f32(lm2_sub_f32(lm2_sub_f32(1.0f, m.m00), m.m11), m.m22)));
    LM2_ASSERT_UNSAFE(lm2_abs_f32(s) > 1e-6f);
    q.w = lm2_div_f32(lm2_sub_f32(m.m10, m.m01), s);
    q.x = lm2_div_f32(lm2_add_f32(m.m02, m.m20), s);
    q.y = lm2_div_f32(lm2_add_f32(m.m12, m.m21), s);
    q.z = lm2_mul_f32(0.25f, s);
  }

  return q;
}