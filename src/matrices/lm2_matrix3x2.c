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

#include <lm2/matrices/lm2_matrix3x2.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/scalar/lm2_trigonometry.h>

// =============================================================================
// Matrix 3x2 f64 Implementations
// =============================================================================

LM2_API lm2_matrix3x2_f64 lm2_matrix3x2_f64_identity(void) {
  lm2_matrix3x2_f64 result;
  result.m00 = 1.0;
  result.m01 = 0.0;
  result.m02 = 0.0;
  result.m10 = 0.0;
  result.m11 = 1.0;
  result.m12 = 0.0;
  return result;
}

LM2_API lm2_matrix3x2_f64 lm2_matrix3x2_f64_zero(void) {
  lm2_matrix3x2_f64 result;
  result.m00 = 0.0;
  result.m01 = 0.0;
  result.m02 = 0.0;
  result.m10 = 0.0;
  result.m11 = 0.0;
  result.m12 = 0.0;
  return result;
}

LM2_API lm2_matrix3x2_f64 lm2_matrix3x2_f64_make(double m00, double m01, double m02, double m10, double m11, double m12) {
  lm2_matrix3x2_f64 result;
  result.m00 = m00;
  result.m01 = m01;
  result.m02 = m02;
  result.m10 = m10;
  result.m11 = m11;
  result.m12 = m12;
  return result;
}

LM2_API lm2_matrix3x2_f64 lm2_matrix3x2_f64_scale(lm2_v2_f64 scale) {
  lm2_matrix3x2_f64 result;
  result.m00 = scale.x;
  result.m01 = 0.0;
  result.m02 = 0.0;
  result.m10 = 0.0;
  result.m11 = scale.y;
  result.m12 = 0.0;
  return result;
}

LM2_API lm2_matrix3x2_f64 lm2_matrix3x2_f64_scale_uniform(double scale) {
  lm2_matrix3x2_f64 result;
  result.m00 = scale;
  result.m01 = 0.0;
  result.m02 = 0.0;
  result.m10 = 0.0;
  result.m11 = scale;
  result.m12 = 0.0;
  return result;
}

LM2_API lm2_matrix3x2_f64 lm2_matrix3x2_f64_translate(lm2_v2_f64 translation) {
  lm2_matrix3x2_f64 result;
  result.m00 = 1.0;
  result.m01 = 0.0;
  result.m02 = translation.x;
  result.m10 = 0.0;
  result.m11 = 1.0;
  result.m12 = translation.y;
  return result;
}

LM2_API lm2_matrix3x2_f64 lm2_matrix3x2_f64_rotate(double angle) {
  double c = lm2_cos_f64(angle);
  double s = lm2_sin_f64(angle);
  lm2_matrix3x2_f64 result;
  result.m00 = c;
  result.m01 = lm2_neg_f64(s);
  result.m02 = 0.0;
  result.m10 = s;
  result.m11 = c;
  result.m12 = 0.0;
  return result;
}

LM2_API lm2_matrix3x2_f64 lm2_matrix3x2_f64_rotate_around_pivot(double angle, lm2_v2_f64 pivot) {
  double c = lm2_cos_f64(angle);
  double s = lm2_sin_f64(angle);
  double one_minus_c = lm2_sub_f64(1.0, c);
  lm2_matrix3x2_f64 result;
  result.m00 = c;
  result.m01 = lm2_neg_f64(s);
  result.m02 = lm2_add_f64(
      lm2_mul_f64(pivot.x, one_minus_c),
      lm2_mul_f64(pivot.y, s));
  result.m10 = s;
  result.m11 = c;
  result.m12 = lm2_add_f64(
      lm2_mul_f64(pivot.y, one_minus_c),
      lm2_mul_f64(lm2_neg_f64(pivot.x), s));
  return result;
}

LM2_API lm2_matrix3x2_f64 lm2_matrix3x2_f64_scale_translate(lm2_v2_f64 scale, lm2_v2_f64 translation) {
  lm2_matrix3x2_f64 result;
  result.m00 = scale.x;
  result.m01 = 0.0;
  result.m02 = translation.x;
  result.m10 = 0.0;
  result.m11 = scale.y;
  result.m12 = translation.y;
  return result;
}

LM2_API lm2_matrix3x2_f64 lm2_matrix3x2_f64_world_transform(lm2_v2_f64 translation, lm2_v2_f64 scale, double rotation) {
  double c = lm2_cos_f64(rotation);
  double s = lm2_sin_f64(rotation);
  lm2_matrix3x2_f64 result;
  result.m00 = lm2_mul_f64(c, scale.x);
  result.m01 = lm2_mul_f64(lm2_neg_f64(s), scale.y);
  result.m02 = translation.x;
  result.m10 = lm2_mul_f64(s, scale.x);
  result.m11 = lm2_mul_f64(c, scale.y);
  result.m12 = translation.y;
  return result;
}

LM2_API lm2_matrix3x2_f64 lm2_matrix3x2_f64_multiply(lm2_matrix3x2_f64 a, lm2_matrix3x2_f64 b) {
  lm2_matrix3x2_f64 result;
  result.m00 = lm2_add_f64(
      lm2_mul_f64(a.m00, b.m00),
      lm2_mul_f64(a.m01, b.m10));
  result.m01 = lm2_add_f64(
      lm2_mul_f64(a.m00, b.m01),
      lm2_mul_f64(a.m01, b.m11));
  result.m02 = lm2_add_f64(
      lm2_add_f64(
          lm2_mul_f64(a.m00, b.m02),
          lm2_mul_f64(a.m01, b.m12)),
      a.m02);
  result.m10 = lm2_add_f64(
      lm2_mul_f64(a.m10, b.m00),
      lm2_mul_f64(a.m11, b.m10));
  result.m11 = lm2_add_f64(
      lm2_mul_f64(a.m10, b.m01),
      lm2_mul_f64(a.m11, b.m11));
  result.m12 = lm2_add_f64(
      lm2_add_f64(
          lm2_mul_f64(a.m10, b.m02),
          lm2_mul_f64(a.m11, b.m12)),
      a.m12);
  return result;
}

LM2_API double lm2_matrix3x2_f64_determinant(lm2_matrix3x2_f64 m) {
  return lm2_sub_f64(
      lm2_mul_f64(m.m00, m.m11),
      lm2_mul_f64(m.m01, m.m10));
}

LM2_API lm2_matrix3x2_f64 lm2_matrix3x2_f64_inverse(lm2_matrix3x2_f64 m) {
  double det = lm2_matrix3x2_f64_determinant(m);
  LM2_ASSERT_UNSAFE(lm2_abs_f64(det) > 0.000001);
  double inv_det = lm2_div_f64(1.0, det);
  lm2_matrix3x2_f64 result;
  result.m00 = lm2_mul_f64(m.m11, inv_det);
  result.m01 = lm2_mul_f64(lm2_neg_f64(m.m01), inv_det);
  result.m10 = lm2_mul_f64(lm2_neg_f64(m.m10), inv_det);
  result.m11 = lm2_mul_f64(m.m00, inv_det);
  result.m02 = lm2_mul_f64(
      inv_det,
      lm2_sub_f64(
          lm2_mul_f64(m.m01, m.m12),
          lm2_mul_f64(m.m11, m.m02)));
  result.m12 = lm2_mul_f64(
      inv_det,
      lm2_sub_f64(
          lm2_mul_f64(m.m10, m.m02),
          lm2_mul_f64(m.m00, m.m12)));
  return result;
}

LM2_API lm2_v2_f64 lm2_matrix3x2_f64_transform_point(lm2_matrix3x2_f64 m, lm2_v2_f64 v) {
  lm2_v2_f64 result;
  result.x = lm2_add_f64(
      lm2_add_f64(
          lm2_mul_f64(m.m00, v.x),
          lm2_mul_f64(m.m01, v.y)),
      m.m02);
  result.y = lm2_add_f64(
      lm2_add_f64(
          lm2_mul_f64(m.m10, v.x),
          lm2_mul_f64(m.m11, v.y)),
      m.m12);
  return result;
}

LM2_API lm2_v2_f64 lm2_matrix3x2_f64_transform_vector(lm2_matrix3x2_f64 m, lm2_v2_f64 v) {
  lm2_v2_f64 result;
  result.x = lm2_add_f64(
      lm2_mul_f64(m.m00, v.x),
      lm2_mul_f64(m.m01, v.y));
  result.y = lm2_add_f64(
      lm2_mul_f64(m.m10, v.x),
      lm2_mul_f64(m.m11, v.y));
  return result;
}

LM2_API void lm2_matrix3x2_f64_transform_points(lm2_matrix3x2_f64 m, lm2_v2_f64* points, uint32_t count) {
  LM2_ASSERT(points != NULL);
  for (uint32_t i = 0; i < count; i = lm2_add_u32(i, 1)) {
    points[i] = lm2_matrix3x2_f64_transform_point(m, points[i]);
  }
}

LM2_API void lm2_matrix3x2_f64_transform_points_src_dst(lm2_matrix3x2_f64 m, const lm2_v2_f64* src, lm2_v2_f64* dst, uint32_t count) {
  LM2_ASSERT(src != NULL);
  LM2_ASSERT(dst != NULL);
  for (uint32_t i = 0; i < count; i = lm2_add_u32(i, 1)) {
    dst[i] = lm2_matrix3x2_f64_transform_point(m, src[i]);
  }
}

LM2_API double lm2_matrix3x2_f64_get_rotation(lm2_matrix3x2_f64 m) {
  return lm2_atan2_f64(m.m10, m.m00);
}

LM2_API lm2_v2_f64 lm2_matrix3x2_f64_get_scale(lm2_matrix3x2_f64 m) {
  lm2_v2_f64 result;
  result.x = lm2_sqrt_f64(
      lm2_add_f64(
          lm2_mul_f64(m.m00, m.m00),
          lm2_mul_f64(m.m10, m.m10)));
  result.y = lm2_sqrt_f64(
      lm2_add_f64(
          lm2_mul_f64(m.m01, m.m01),
          lm2_mul_f64(m.m11, m.m11)));
  return result;
}

LM2_API lm2_v2_f64 lm2_matrix3x2_f64_get_translation(lm2_matrix3x2_f64 m) {
  lm2_v2_f64 result;
  result.x = m.m02;
  result.y = m.m12;
  return result;
}

LM2_API lm2_matrix3x2_f64 lm2_matrix3x2_f64_ortho(double left, double right, double bottom, double top) {
  double width = lm2_sub_f64(right, left);
  double height = lm2_sub_f64(top, bottom);
  LM2_ASSERT_UNSAFE(lm2_abs_f64(width) > 0.000001);
  LM2_ASSERT_UNSAFE(lm2_abs_f64(height) > 0.000001);
  lm2_matrix3x2_f64 result;
  result.m00 = lm2_div_f64(2.0, width);
  result.m01 = 0.0;
  result.m02 = lm2_neg_f64(
      lm2_div_f64(lm2_add_f64(right, left), width));
  result.m10 = 0.0;
  result.m11 = lm2_div_f64(2.0, height);
  result.m12 = lm2_neg_f64(
      lm2_div_f64(lm2_add_f64(top, bottom), height));
  return result;
}

// =============================================================================
// Matrix 3x2 f32 Implementations
// =============================================================================

LM2_API lm2_matrix3x2_f32 lm2_matrix3x2_f32_identity(void) {
  lm2_matrix3x2_f32 result;
  result.m00 = 1.0f;
  result.m01 = 0.0f;
  result.m02 = 0.0f;
  result.m10 = 0.0f;
  result.m11 = 1.0f;
  result.m12 = 0.0f;
  return result;
}

LM2_API lm2_matrix3x2_f32 lm2_matrix3x2_f32_zero(void) {
  lm2_matrix3x2_f32 result;
  result.m00 = 0.0f;
  result.m01 = 0.0f;
  result.m02 = 0.0f;
  result.m10 = 0.0f;
  result.m11 = 0.0f;
  result.m12 = 0.0f;
  return result;
}

LM2_API lm2_matrix3x2_f32 lm2_matrix3x2_f32_make(float m00, float m01, float m02, float m10, float m11, float m12) {
  lm2_matrix3x2_f32 result;
  result.m00 = m00;
  result.m01 = m01;
  result.m02 = m02;
  result.m10 = m10;
  result.m11 = m11;
  result.m12 = m12;
  return result;
}

LM2_API lm2_matrix3x2_f32 lm2_matrix3x2_f32_scale(lm2_v2_f32 scale) {
  lm2_matrix3x2_f32 result;
  result.m00 = scale.x;
  result.m01 = 0.0f;
  result.m02 = 0.0f;
  result.m10 = 0.0f;
  result.m11 = scale.y;
  result.m12 = 0.0f;
  return result;
}

LM2_API lm2_matrix3x2_f32 lm2_matrix3x2_f32_scale_uniform(float scale) {
  lm2_matrix3x2_f32 result;
  result.m00 = scale;
  result.m01 = 0.0f;
  result.m02 = 0.0f;
  result.m10 = 0.0f;
  result.m11 = scale;
  result.m12 = 0.0f;
  return result;
}

LM2_API lm2_matrix3x2_f32 lm2_matrix3x2_f32_translate(lm2_v2_f32 translation) {
  lm2_matrix3x2_f32 result;
  result.m00 = 1.0f;
  result.m01 = 0.0f;
  result.m02 = translation.x;
  result.m10 = 0.0f;
  result.m11 = 1.0f;
  result.m12 = translation.y;
  return result;
}

LM2_API lm2_matrix3x2_f32 lm2_matrix3x2_f32_rotate(float angle) {
  float c = lm2_cos_f32(angle);
  float s = lm2_sin_f32(angle);
  lm2_matrix3x2_f32 result;
  result.m00 = c;
  result.m01 = lm2_neg_f32(s);
  result.m02 = 0.0f;
  result.m10 = s;
  result.m11 = c;
  result.m12 = 0.0f;
  return result;
}

LM2_API lm2_matrix3x2_f32 lm2_matrix3x2_f32_rotate_around_pivot(float angle, lm2_v2_f32 pivot) {
  float c = lm2_cos_f32(angle);
  float s = lm2_sin_f32(angle);
  float one_minus_c = lm2_sub_f32(1.0f, c);
  lm2_matrix3x2_f32 result;
  result.m00 = c;
  result.m01 = lm2_neg_f32(s);
  result.m02 = lm2_add_f32(
      lm2_mul_f32(pivot.x, one_minus_c),
      lm2_mul_f32(pivot.y, s));
  result.m10 = s;
  result.m11 = c;
  result.m12 = lm2_add_f32(
      lm2_mul_f32(pivot.y, one_minus_c),
      lm2_mul_f32(lm2_neg_f32(pivot.x), s));
  return result;
}

LM2_API lm2_matrix3x2_f32 lm2_matrix3x2_f32_scale_translate(lm2_v2_f32 scale, lm2_v2_f32 translation) {
  lm2_matrix3x2_f32 result;
  result.m00 = scale.x;
  result.m01 = 0.0f;
  result.m02 = translation.x;
  result.m10 = 0.0f;
  result.m11 = scale.y;
  result.m12 = translation.y;
  return result;
}

LM2_API lm2_matrix3x2_f32 lm2_matrix3x2_f32_world_transform(lm2_v2_f32 translation, lm2_v2_f32 scale, float rotation) {
  float c = lm2_cos_f32(rotation);
  float s = lm2_sin_f32(rotation);
  lm2_matrix3x2_f32 result;
  result.m00 = lm2_mul_f32(c, scale.x);
  result.m01 = lm2_mul_f32(lm2_neg_f32(s), scale.y);
  result.m02 = translation.x;
  result.m10 = lm2_mul_f32(s, scale.x);
  result.m11 = lm2_mul_f32(c, scale.y);
  result.m12 = translation.y;
  return result;
}

LM2_API lm2_matrix3x2_f32 lm2_matrix3x2_f32_multiply(lm2_matrix3x2_f32 a, lm2_matrix3x2_f32 b) {
  lm2_matrix3x2_f32 result;
  result.m00 = lm2_add_f32(
      lm2_mul_f32(a.m00, b.m00),
      lm2_mul_f32(a.m01, b.m10));
  result.m01 = lm2_add_f32(
      lm2_mul_f32(a.m00, b.m01),
      lm2_mul_f32(a.m01, b.m11));
  result.m02 = lm2_add_f32(
      lm2_add_f32(
          lm2_mul_f32(a.m00, b.m02),
          lm2_mul_f32(a.m01, b.m12)),
      a.m02);
  result.m10 = lm2_add_f32(
      lm2_mul_f32(a.m10, b.m00),
      lm2_mul_f32(a.m11, b.m10));
  result.m11 = lm2_add_f32(
      lm2_mul_f32(a.m10, b.m01),
      lm2_mul_f32(a.m11, b.m11));
  result.m12 = lm2_add_f32(
      lm2_add_f32(
          lm2_mul_f32(a.m10, b.m02),
          lm2_mul_f32(a.m11, b.m12)),
      a.m12);
  return result;
}

LM2_API float lm2_matrix3x2_f32_determinant(lm2_matrix3x2_f32 m) {
  return lm2_sub_f32(
      lm2_mul_f32(m.m00, m.m11),
      lm2_mul_f32(m.m01, m.m10));
}

LM2_API lm2_matrix3x2_f32 lm2_matrix3x2_f32_inverse(lm2_matrix3x2_f32 m) {
  float det = lm2_matrix3x2_f32_determinant(m);
  LM2_ASSERT_UNSAFE(lm2_abs_f32(det) > 0.000001f);
  float inv_det = lm2_div_f32(1.0f, det);
  lm2_matrix3x2_f32 result;
  result.m00 = lm2_mul_f32(m.m11, inv_det);
  result.m01 = lm2_mul_f32(lm2_neg_f32(m.m01), inv_det);
  result.m10 = lm2_mul_f32(lm2_neg_f32(m.m10), inv_det);
  result.m11 = lm2_mul_f32(m.m00, inv_det);
  result.m02 = lm2_mul_f32(
      inv_det,
      lm2_sub_f32(
          lm2_mul_f32(m.m01, m.m12),
          lm2_mul_f32(m.m11, m.m02)));
  result.m12 = lm2_mul_f32(
      inv_det,
      lm2_sub_f32(
          lm2_mul_f32(m.m10, m.m02),
          lm2_mul_f32(m.m00, m.m12)));
  return result;
}

LM2_API lm2_v2_f32 lm2_matrix3x2_f32_transform_point(lm2_matrix3x2_f32 m, lm2_v2_f32 v) {
  lm2_v2_f32 result;
  result.x = lm2_add_f32(
      lm2_add_f32(
          lm2_mul_f32(m.m00, v.x),
          lm2_mul_f32(m.m01, v.y)),
      m.m02);
  result.y = lm2_add_f32(
      lm2_add_f32(
          lm2_mul_f32(m.m10, v.x),
          lm2_mul_f32(m.m11, v.y)),
      m.m12);
  return result;
}

LM2_API lm2_v2_f32 lm2_matrix3x2_f32_transform_vector(lm2_matrix3x2_f32 m, lm2_v2_f32 v) {
  lm2_v2_f32 result;
  result.x = lm2_add_f32(
      lm2_mul_f32(m.m00, v.x),
      lm2_mul_f32(m.m01, v.y));
  result.y = lm2_add_f32(
      lm2_mul_f32(m.m10, v.x),
      lm2_mul_f32(m.m11, v.y));
  return result;
}

LM2_API void lm2_matrix3x2_f32_transform_points(lm2_matrix3x2_f32 m, lm2_v2_f32* points, uint32_t count) {
  LM2_ASSERT(points != NULL);
  for (uint32_t i = 0; i < count; i = lm2_add_u32(i, 1)) {
    points[i] = lm2_matrix3x2_f32_transform_point(m, points[i]);
  }
}

LM2_API void lm2_matrix3x2_f32_transform_points_src_dst(lm2_matrix3x2_f32 m, const lm2_v2_f32* src, lm2_v2_f32* dst, uint32_t count) {
  LM2_ASSERT(src != NULL);
  LM2_ASSERT(dst != NULL);
  for (uint32_t i = 0; i < count; i = lm2_add_u32(i, 1)) {
    dst[i] = lm2_matrix3x2_f32_transform_point(m, src[i]);
  }
}

LM2_API float lm2_matrix3x2_f32_get_rotation(lm2_matrix3x2_f32 m) {
  return lm2_atan2_f32(m.m10, m.m00);
}

LM2_API lm2_v2_f32 lm2_matrix3x2_f32_get_scale(lm2_matrix3x2_f32 m) {
  lm2_v2_f32 result;
  result.x = lm2_sqrt_f32(
      lm2_add_f32(
          lm2_mul_f32(m.m00, m.m00),
          lm2_mul_f32(m.m10, m.m10)));
  result.y = lm2_sqrt_f32(
      lm2_add_f32(
          lm2_mul_f32(m.m01, m.m01),
          lm2_mul_f32(m.m11, m.m11)));
  return result;
}

LM2_API lm2_v2_f32 lm2_matrix3x2_f32_get_translation(lm2_matrix3x2_f32 m) {
  lm2_v2_f32 result;
  result.x = m.m02;
  result.y = m.m12;
  return result;
}

LM2_API lm2_matrix3x2_f32 lm2_matrix3x2_f32_ortho(float left, float right, float bottom, float top) {
  float width = lm2_sub_f32(right, left);
  float height = lm2_sub_f32(top, bottom);
  LM2_ASSERT_UNSAFE(lm2_abs_f32(width) > 0.000001f);
  LM2_ASSERT_UNSAFE(lm2_abs_f32(height) > 0.000001f);
  lm2_matrix3x2_f32 result;
  result.m00 = lm2_div_f32(2.0f, width);
  result.m01 = 0.0f;
  result.m02 = lm2_neg_f32(
      lm2_div_f32(lm2_add_f32(right, left), width));
  result.m10 = 0.0f;
  result.m11 = lm2_div_f32(2.0f, height);
  result.m12 = lm2_neg_f32(
      lm2_div_f32(lm2_add_f32(top, bottom), height));
  return result;
}
