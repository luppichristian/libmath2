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

#include <lm2/matrices/lm2_matrix3x3.h>
#include <lm2/lm2_constants.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/scalar/lm2_trigonometry.h>

// =============================================================================
// Matrix 3x3 Functions - f64
// =============================================================================

// Basic constructors
LM2_API lm2_m3x3_f64 lm2_m3x3_identity_f64(void) {
  lm2_m3x3_f64 m = {
      1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
  return m;
}

LM2_API lm2_m3x3_f64 lm2_m3x3_zero_f64(void) {
  lm2_m3x3_f64 m = {
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  return m;
}

LM2_API lm2_m3x3_f64 lm2_m3x3_make_f64(double m00, double m01, double m02, double m10, double m11, double m12, double m20, double m21, double m22) {
  lm2_m3x3_f64 m = {
      m00, m01, m02, m10, m11, m12, m20, m21, m22};
  return m;
}

// Transformations
LM2_API lm2_m3x3_f64 lm2_m3x3_scale_f64(lm2_v2_f64 scale) {
  lm2_m3x3_f64 m = {
      scale.x, 0.0, 0.0, 0.0, scale.y, 0.0, 0.0, 0.0, 1.0};
  return m;
}

LM2_API lm2_m3x3_f64 lm2_m3x3_scale_uniform_f64(double scale) {
  lm2_m3x3_f64 m = {
      scale, 0.0, 0.0, 0.0, scale, 0.0, 0.0, 0.0, 1.0};
  return m;
}

LM2_API lm2_m3x3_f64 lm2_m3x3_translate_f64(lm2_v2_f64 translation) {
  lm2_m3x3_f64 m = {
      1.0, 0.0, translation.x, 0.0, 1.0, translation.y, 0.0, 0.0, 1.0};
  return m;
}

LM2_API lm2_m3x3_f64 lm2_m3x3_rotate_f64(double angle) {
  double c = lm2_cos_f64(angle);
  double s = lm2_sin_f64(angle);

  lm2_m3x3_f64 m = {
      c, lm2_sub_f64(0.0, s), 0.0, s, c, 0.0, 0.0, 0.0, 1.0};
  return m;
}

LM2_API lm2_m3x3_f64 lm2_m3x3_rotate_around_pivot_f64(double angle, lm2_v2_f64 pivot) {
  // T(pivot) * R(angle) * T(-pivot)
  lm2_m3x3_f64 translate_to_origin = lm2_m3x3_translate_f64((lm2_v2_f64) {lm2_sub_f64(0.0, pivot.x), lm2_sub_f64(0.0, pivot.y)});
  lm2_m3x3_f64 rotate = lm2_m3x3_rotate_f64(angle);
  lm2_m3x3_f64 translate_back = lm2_m3x3_translate_f64(pivot);

  lm2_m3x3_f64 temp = lm2_m3x3_multiply_f64(rotate, translate_to_origin);
  return lm2_m3x3_multiply_f64(translate_back, temp);
}

LM2_API lm2_m3x3_f64 lm2_m3x3_scale_translate_f64(lm2_v2_f64 scale, lm2_v2_f64 translation) {
  lm2_m3x3_f64 m = {
      scale.x, 0.0, translation.x, 0.0, scale.y, translation.y, 0.0, 0.0, 1.0};
  return m;
}

// Operations
LM2_API lm2_m3x3_f64 lm2_m3x3_multiply_f64(lm2_m3x3_f64 a, lm2_m3x3_f64 b) {
  lm2_m3x3_f64 result;

  // Row 0
  result.m00 = lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m00, b.m00), lm2_mul_f64(a.m01, b.m10)), lm2_mul_f64(a.m02, b.m20));
  result.m01 = lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m00, b.m01), lm2_mul_f64(a.m01, b.m11)), lm2_mul_f64(a.m02, b.m21));
  result.m02 = lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m00, b.m02), lm2_mul_f64(a.m01, b.m12)), lm2_mul_f64(a.m02, b.m22));

  // Row 1
  result.m10 = lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m10, b.m00), lm2_mul_f64(a.m11, b.m10)), lm2_mul_f64(a.m12, b.m20));
  result.m11 = lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m10, b.m01), lm2_mul_f64(a.m11, b.m11)), lm2_mul_f64(a.m12, b.m21));
  result.m12 = lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m10, b.m02), lm2_mul_f64(a.m11, b.m12)), lm2_mul_f64(a.m12, b.m22));

  // Row 2
  result.m20 = lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m20, b.m00), lm2_mul_f64(a.m21, b.m10)), lm2_mul_f64(a.m22, b.m20));
  result.m21 = lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m20, b.m01), lm2_mul_f64(a.m21, b.m11)), lm2_mul_f64(a.m22, b.m21));
  result.m22 = lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.m20, b.m02), lm2_mul_f64(a.m21, b.m12)), lm2_mul_f64(a.m22, b.m22));

  return result;
}

LM2_API lm2_m3x3_f64 lm2_m3x3_transpose_f64(lm2_m3x3_f64 m) {
  lm2_m3x3_f64 result = {
      m.m00, m.m10, m.m20, m.m01, m.m11, m.m21, m.m02, m.m12, m.m22};
  return result;
}

LM2_API double lm2_m3x3_determinant_f64(lm2_m3x3_f64 m) {
  // det = m00(m11*m22 - m12*m21) - m01(m10*m22 - m12*m20) + m02(m10*m21 - m11*m20)
  double term1 = lm2_mul_f64(m.m00, lm2_sub_f64(lm2_mul_f64(m.m11, m.m22), lm2_mul_f64(m.m12, m.m21)));
  double term2 = lm2_mul_f64(m.m01, lm2_sub_f64(lm2_mul_f64(m.m10, m.m22), lm2_mul_f64(m.m12, m.m20)));
  double term3 = lm2_mul_f64(m.m02, lm2_sub_f64(lm2_mul_f64(m.m10, m.m21), lm2_mul_f64(m.m11, m.m20)));

  return lm2_add_f64(lm2_sub_f64(term1, term2), term3);
}

LM2_API lm2_m3x3_f64 lm2_m3x3_inverse_f64(lm2_m3x3_f64 m) {
  double det = lm2_m3x3_determinant_f64(m);
  LM2_ASSERT_UNSAFE(lm2_abs_f64(det) > 1e-10);

  double inv_det = lm2_div_f64(1.0, det);

  lm2_m3x3_f64 result;

  // Calculate cofactor matrix and transpose (adjugate)
  result.m00 = lm2_mul_f64(lm2_sub_f64(lm2_mul_f64(m.m11, m.m22), lm2_mul_f64(m.m12, m.m21)), inv_det);
  result.m01 = lm2_mul_f64(lm2_sub_f64(lm2_mul_f64(m.m02, m.m21), lm2_mul_f64(m.m01, m.m22)), inv_det);
  result.m02 = lm2_mul_f64(lm2_sub_f64(lm2_mul_f64(m.m01, m.m12), lm2_mul_f64(m.m02, m.m11)), inv_det);

  result.m10 = lm2_mul_f64(lm2_sub_f64(lm2_mul_f64(m.m12, m.m20), lm2_mul_f64(m.m10, m.m22)), inv_det);
  result.m11 = lm2_mul_f64(lm2_sub_f64(lm2_mul_f64(m.m00, m.m22), lm2_mul_f64(m.m02, m.m20)), inv_det);
  result.m12 = lm2_mul_f64(lm2_sub_f64(lm2_mul_f64(m.m02, m.m10), lm2_mul_f64(m.m00, m.m12)), inv_det);

  result.m20 = lm2_mul_f64(lm2_sub_f64(lm2_mul_f64(m.m10, m.m21), lm2_mul_f64(m.m11, m.m20)), inv_det);
  result.m21 = lm2_mul_f64(lm2_sub_f64(lm2_mul_f64(m.m01, m.m20), lm2_mul_f64(m.m00, m.m21)), inv_det);
  result.m22 = lm2_mul_f64(lm2_sub_f64(lm2_mul_f64(m.m00, m.m11), lm2_mul_f64(m.m01, m.m10)), inv_det);

  return result;
}

LM2_API double lm2_m3x3_trace_f64(lm2_m3x3_f64 m) {
  return lm2_add_f64(lm2_add_f64(m.m00, m.m11), m.m22);
}

LM2_API lm2_v2_f64 lm2_m3x3_transform_point_f64(lm2_m3x3_f64 m, lm2_v2_f64 v) {
  // Transform as homogeneous point (x, y, 1)
  double x = lm2_add_f64(lm2_add_f64(lm2_mul_f64(m.m00, v.x), lm2_mul_f64(m.m01, v.y)), m.m02);
  double y = lm2_add_f64(lm2_add_f64(lm2_mul_f64(m.m10, v.x), lm2_mul_f64(m.m11, v.y)), m.m12);
  double w = lm2_add_f64(lm2_add_f64(lm2_mul_f64(m.m20, v.x), lm2_mul_f64(m.m21, v.y)), m.m22);

  // Perspective divide if needed
  if (lm2_abs_f64(lm2_sub_f64(w, 1.0)) > 1e-10) {
    LM2_ASSERT_UNSAFE(lm2_abs_f64(w) > 1e-10);
    x = lm2_div_f64(x, w);
    y = lm2_div_f64(y, w);
  }

  lm2_v2_f64 result = {x, y};
  return result;
}

LM2_API lm2_v2_f64 lm2_m3x3_transform_vector_f64(lm2_m3x3_f64 m, lm2_v2_f64 v) {
  // Transform as vector (x, y, 0) - no translation
  double x = lm2_add_f64(lm2_mul_f64(m.m00, v.x), lm2_mul_f64(m.m01, v.y));
  double y = lm2_add_f64(lm2_mul_f64(m.m10, v.x), lm2_mul_f64(m.m11, v.y));

  lm2_v2_f64 result = {x, y};
  return result;
}

LM2_API lm2_v3_f64 lm2_m3x3_transform_f64(lm2_m3x3_f64 m, lm2_v3_f64 v) {
  // Transform full 3D vector
  double x = lm2_add_f64(lm2_add_f64(lm2_mul_f64(m.m00, v.x), lm2_mul_f64(m.m01, v.y)), lm2_mul_f64(m.m02, v.z));
  double y = lm2_add_f64(lm2_add_f64(lm2_mul_f64(m.m10, v.x), lm2_mul_f64(m.m11, v.y)), lm2_mul_f64(m.m12, v.z));
  double z = lm2_add_f64(lm2_add_f64(lm2_mul_f64(m.m20, v.x), lm2_mul_f64(m.m21, v.y)), lm2_mul_f64(m.m22, v.z));

  lm2_v3_f64 result = {x, y, z};
  return result;
}

LM2_API void lm2_m3x3_transform_points_f64(lm2_m3x3_f64 m, lm2_v2_f64* points, uint32_t count) {
  LM2_ASSERT(points != NULL);

  for (uint32_t i = 0; i < count; i++) {
    points[i] = lm2_m3x3_transform_point_f64(m, points[i]);
  }
}

LM2_API void lm2_m3x3_transform_points_src_dst_f64(lm2_m3x3_f64 m, const lm2_v2_f64* src, lm2_v2_f64* dst, uint32_t count) {
  LM2_ASSERT(src != NULL && dst != NULL);

  for (uint32_t i = 0; i < count; i++) {
    dst[i] = lm2_m3x3_transform_point_f64(m, src[i]);
  }
}

// Getters
LM2_API double lm2_m3x3_get_rotation_f64(lm2_m3x3_f64 m) {
  // Extract rotation angle from the rotation part
  return lm2_atan2_f64(m.m10, m.m00);
}

LM2_API lm2_v2_f64 lm2_m3x3_get_scale_f64(lm2_m3x3_f64 m) {
  // Extract scale from matrix
  double sx = lm2_sqrt_f64(lm2_add_f64(lm2_mul_f64(m.m00, m.m00), lm2_mul_f64(m.m10, m.m10)));
  double sy = lm2_sqrt_f64(lm2_add_f64(lm2_mul_f64(m.m01, m.m01), lm2_mul_f64(m.m11, m.m11)));

  lm2_v2_f64 result = {sx, sy};
  return result;
}

LM2_API lm2_v2_f64 lm2_m3x3_get_translation_f64(lm2_m3x3_f64 m) {
  lm2_v2_f64 result = {m.m02, m.m12};
  return result;
}
// =============================================================================
// Matrix 3x3 Functions - f32
// =============================================================================

// Basic constructors
LM2_API lm2_m3x3_f32 lm2_m3x3_identity_f32(void) {
  lm2_m3x3_f32 m = {
      1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  return m;
}

LM2_API lm2_m3x3_f32 lm2_m3x3_zero_f32(void) {
  lm2_m3x3_f32 m = {
      0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
  return m;
}

LM2_API lm2_m3x3_f32 lm2_m3x3_make_f32(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22) {
  lm2_m3x3_f32 m = {
      m00, m01, m02, m10, m11, m12, m20, m21, m22};
  return m;
}

// Transformations
LM2_API lm2_m3x3_f32 lm2_m3x3_scale_f32(lm2_v2_f32 scale) {
  lm2_m3x3_f32 m = {
      scale.x, 0.0f, 0.0f, 0.0f, scale.y, 0.0f, 0.0f, 0.0f, 1.0f};
  return m;
}

LM2_API lm2_m3x3_f32 lm2_m3x3_scale_uniform_f32(float scale) {
  lm2_m3x3_f32 m = {
      scale, 0.0f, 0.0f, 0.0f, scale, 0.0f, 0.0f, 0.0f, 1.0f};
  return m;
}

LM2_API lm2_m3x3_f32 lm2_m3x3_translate_f32(lm2_v2_f32 translation) {
  lm2_m3x3_f32 m = {
      1.0f, 0.0f, translation.x, 0.0f, 1.0f, translation.y, 0.0f, 0.0f, 1.0f};
  return m;
}

LM2_API lm2_m3x3_f32 lm2_m3x3_rotate_f32(float angle) {
  float c = lm2_cos_f32(angle);
  float s = lm2_sin_f32(angle);

  lm2_m3x3_f32 m = {
      c, lm2_sub_f32(0.0f, s), 0.0f, s, c, 0.0f, 0.0f, 0.0f, 1.0f};
  return m;
}

LM2_API lm2_m3x3_f32 lm2_m3x3_rotate_around_pivot_f32(float angle, lm2_v2_f32 pivot) {
  // T(pivot) * R(angle) * T(-pivot)
  lm2_m3x3_f32 translate_to_origin = lm2_m3x3_translate_f32((lm2_v2_f32) {lm2_sub_f32(0.0f, pivot.x), lm2_sub_f32(0.0f, pivot.y)});
  lm2_m3x3_f32 rotate = lm2_m3x3_rotate_f32(angle);
  lm2_m3x3_f32 translate_back = lm2_m3x3_translate_f32(pivot);

  lm2_m3x3_f32 temp = lm2_m3x3_multiply_f32(rotate, translate_to_origin);
  return lm2_m3x3_multiply_f32(translate_back, temp);
}

LM2_API lm2_m3x3_f32 lm2_m3x3_scale_translate_f32(lm2_v2_f32 scale, lm2_v2_f32 translation) {
  lm2_m3x3_f32 m = {
      scale.x, 0.0f, translation.x, 0.0f, scale.y, translation.y, 0.0f, 0.0f, 1.0f};
  return m;
}

// Operations
LM2_API lm2_m3x3_f32 lm2_m3x3_multiply_f32(lm2_m3x3_f32 a, lm2_m3x3_f32 b) {
  lm2_m3x3_f32 result;

  // Row 0
  result.m00 = lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m00, b.m00), lm2_mul_f32(a.m01, b.m10)), lm2_mul_f32(a.m02, b.m20));
  result.m01 = lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m00, b.m01), lm2_mul_f32(a.m01, b.m11)), lm2_mul_f32(a.m02, b.m21));
  result.m02 = lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m00, b.m02), lm2_mul_f32(a.m01, b.m12)), lm2_mul_f32(a.m02, b.m22));

  // Row 1
  result.m10 = lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m10, b.m00), lm2_mul_f32(a.m11, b.m10)), lm2_mul_f32(a.m12, b.m20));
  result.m11 = lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m10, b.m01), lm2_mul_f32(a.m11, b.m11)), lm2_mul_f32(a.m12, b.m21));
  result.m12 = lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m10, b.m02), lm2_mul_f32(a.m11, b.m12)), lm2_mul_f32(a.m12, b.m22));

  // Row 2
  result.m20 = lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m20, b.m00), lm2_mul_f32(a.m21, b.m10)), lm2_mul_f32(a.m22, b.m20));
  result.m21 = lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m20, b.m01), lm2_mul_f32(a.m21, b.m11)), lm2_mul_f32(a.m22, b.m21));
  result.m22 = lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.m20, b.m02), lm2_mul_f32(a.m21, b.m12)), lm2_mul_f32(a.m22, b.m22));

  return result;
}

LM2_API lm2_m3x3_f32 lm2_m3x3_transpose_f32(lm2_m3x3_f32 m) {
  lm2_m3x3_f32 result = {
      m.m00, m.m10, m.m20, m.m01, m.m11, m.m21, m.m02, m.m12, m.m22};
  return result;
}

LM2_API float lm2_m3x3_determinant_f32(lm2_m3x3_f32 m) {
  // det = m00(m11*m22 - m12*m21) - m01(m10*m22 - m12*m20) + m02(m10*m21 - m11*m20)
  float term1 = lm2_mul_f32(m.m00, lm2_sub_f32(lm2_mul_f32(m.m11, m.m22), lm2_mul_f32(m.m12, m.m21)));
  float term2 = lm2_mul_f32(m.m01, lm2_sub_f32(lm2_mul_f32(m.m10, m.m22), lm2_mul_f32(m.m12, m.m20)));
  float term3 = lm2_mul_f32(m.m02, lm2_sub_f32(lm2_mul_f32(m.m10, m.m21), lm2_mul_f32(m.m11, m.m20)));

  return lm2_add_f32(lm2_sub_f32(term1, term2), term3);
}

LM2_API lm2_m3x3_f32 lm2_m3x3_inverse_f32(lm2_m3x3_f32 m) {
  float det = lm2_m3x3_determinant_f32(m);
  LM2_ASSERT_UNSAFE(lm2_abs_f32(det) > 1e-6f);

  float inv_det = lm2_div_f32(1.0f, det);

  lm2_m3x3_f32 result;

  // Calculate cofactor matrix and transpose (adjugate)
  result.m00 = lm2_mul_f32(lm2_sub_f32(lm2_mul_f32(m.m11, m.m22), lm2_mul_f32(m.m12, m.m21)), inv_det);
  result.m01 = lm2_mul_f32(lm2_sub_f32(lm2_mul_f32(m.m02, m.m21), lm2_mul_f32(m.m01, m.m22)), inv_det);
  result.m02 = lm2_mul_f32(lm2_sub_f32(lm2_mul_f32(m.m01, m.m12), lm2_mul_f32(m.m02, m.m11)), inv_det);

  result.m10 = lm2_mul_f32(lm2_sub_f32(lm2_mul_f32(m.m12, m.m20), lm2_mul_f32(m.m10, m.m22)), inv_det);
  result.m11 = lm2_mul_f32(lm2_sub_f32(lm2_mul_f32(m.m00, m.m22), lm2_mul_f32(m.m02, m.m20)), inv_det);
  result.m12 = lm2_mul_f32(lm2_sub_f32(lm2_mul_f32(m.m02, m.m10), lm2_mul_f32(m.m00, m.m12)), inv_det);

  result.m20 = lm2_mul_f32(lm2_sub_f32(lm2_mul_f32(m.m10, m.m21), lm2_mul_f32(m.m11, m.m20)), inv_det);
  result.m21 = lm2_mul_f32(lm2_sub_f32(lm2_mul_f32(m.m01, m.m20), lm2_mul_f32(m.m00, m.m21)), inv_det);
  result.m22 = lm2_mul_f32(lm2_sub_f32(lm2_mul_f32(m.m00, m.m11), lm2_mul_f32(m.m01, m.m10)), inv_det);

  return result;
}

LM2_API float lm2_m3x3_trace_f32(lm2_m3x3_f32 m) {
  return lm2_add_f32(lm2_add_f32(m.m00, m.m11), m.m22);
}

LM2_API lm2_v2_f32 lm2_m3x3_transform_point_f32(lm2_m3x3_f32 m, lm2_v2_f32 v) {
  // Transform as homogeneous point (x, y, 1)
  float x = lm2_add_f32(lm2_add_f32(lm2_mul_f32(m.m00, v.x), lm2_mul_f32(m.m01, v.y)), m.m02);
  float y = lm2_add_f32(lm2_add_f32(lm2_mul_f32(m.m10, v.x), lm2_mul_f32(m.m11, v.y)), m.m12);
  float w = lm2_add_f32(lm2_add_f32(lm2_mul_f32(m.m20, v.x), lm2_mul_f32(m.m21, v.y)), m.m22);

  // Perspective divide if needed
  if (lm2_abs_f32(lm2_sub_f32(w, 1.0f)) > 1e-6f) {
    LM2_ASSERT_UNSAFE(lm2_abs_f32(w) > 1e-6f);
    x = lm2_div_f32(x, w);
    y = lm2_div_f32(y, w);
  }

  lm2_v2_f32 result = {x, y};
  return result;
}

LM2_API lm2_v2_f32 lm2_m3x3_transform_vector_f32(lm2_m3x3_f32 m, lm2_v2_f32 v) {
  // Transform as vector (x, y, 0) - no translation
  float x = lm2_add_f32(lm2_mul_f32(m.m00, v.x), lm2_mul_f32(m.m01, v.y));
  float y = lm2_add_f32(lm2_mul_f32(m.m10, v.x), lm2_mul_f32(m.m11, v.y));

  lm2_v2_f32 result = {x, y};
  return result;
}

LM2_API lm2_v3_f32 lm2_m3x3_transform_f32(lm2_m3x3_f32 m, lm2_v3_f32 v) {
  // Transform full 3D vector
  float x = lm2_add_f32(lm2_add_f32(lm2_mul_f32(m.m00, v.x), lm2_mul_f32(m.m01, v.y)), lm2_mul_f32(m.m02, v.z));
  float y = lm2_add_f32(lm2_add_f32(lm2_mul_f32(m.m10, v.x), lm2_mul_f32(m.m11, v.y)), lm2_mul_f32(m.m12, v.z));
  float z = lm2_add_f32(lm2_add_f32(lm2_mul_f32(m.m20, v.x), lm2_mul_f32(m.m21, v.y)), lm2_mul_f32(m.m22, v.z));

  lm2_v3_f32 result = {x, y, z};
  return result;
}

LM2_API void lm2_m3x3_transform_points_f32(lm2_m3x3_f32 m, lm2_v2_f32* points, uint32_t count) {
  LM2_ASSERT(points != NULL);

  for (uint32_t i = 0; i < count; i++) {
    points[i] = lm2_m3x3_transform_point_f32(m, points[i]);
  }
}

LM2_API void lm2_m3x3_transform_points_src_dst_f32(lm2_m3x3_f32 m, const lm2_v2_f32* src, lm2_v2_f32* dst, uint32_t count) {
  LM2_ASSERT(src != NULL && dst != NULL);

  for (uint32_t i = 0; i < count; i++) {
    dst[i] = lm2_m3x3_transform_point_f32(m, src[i]);
  }
}

// Getters
LM2_API float lm2_m3x3_get_rotation_f32(lm2_m3x3_f32 m) {
  // Extract rotation angle from the rotation part
  return lm2_atan2_f32(m.m10, m.m00);
}

LM2_API lm2_v2_f32 lm2_m3x3_get_scale_f32(lm2_m3x3_f32 m) {
  // Extract scale from matrix
  float sx = lm2_sqrt_f32(lm2_add_f32(lm2_mul_f32(m.m00, m.m00), lm2_mul_f32(m.m10, m.m10)));
  float sy = lm2_sqrt_f32(lm2_add_f32(lm2_mul_f32(m.m01, m.m01), lm2_mul_f32(m.m11, m.m11)));

  lm2_v2_f32 result = {sx, sy};
  return result;
}

LM2_API lm2_v2_f32 lm2_m3x3_get_translation_f32(lm2_m3x3_f32 m) {
  lm2_v2_f32 result = {m.m02, m.m12};
  return result;
}