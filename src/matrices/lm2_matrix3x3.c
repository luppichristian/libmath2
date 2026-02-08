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
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/scalar/lm2_trigonometry.h>

// =============================================================================
// Implementation Macros
// =============================================================================

#define _LM2_IMPL_M3X3_BASIC(mat_type, scalar_type, scalar_suffix)                                                                                                                            \
  LM2_API mat_type mat_type##_identity(void) {                                                                                                                                                \
    mat_type result;                                                                                                                                                                          \
    result.m00 = (scalar_type)1;                                                                                                                                                              \
    result.m01 = (scalar_type)0;                                                                                                                                                              \
    result.m02 = (scalar_type)0;                                                                                                                                                              \
    result.m10 = (scalar_type)0;                                                                                                                                                              \
    result.m11 = (scalar_type)1;                                                                                                                                                              \
    result.m12 = (scalar_type)0;                                                                                                                                                              \
    result.m20 = (scalar_type)0;                                                                                                                                                              \
    result.m21 = (scalar_type)0;                                                                                                                                                              \
    result.m22 = (scalar_type)1;                                                                                                                                                              \
    return result;                                                                                                                                                                            \
  }                                                                                                                                                                                           \
  LM2_API mat_type mat_type##_zero(void) {                                                                                                                                                    \
    mat_type result;                                                                                                                                                                          \
    result.m00 = (scalar_type)0;                                                                                                                                                              \
    result.m01 = (scalar_type)0;                                                                                                                                                              \
    result.m02 = (scalar_type)0;                                                                                                                                                              \
    result.m10 = (scalar_type)0;                                                                                                                                                              \
    result.m11 = (scalar_type)0;                                                                                                                                                              \
    result.m12 = (scalar_type)0;                                                                                                                                                              \
    result.m20 = (scalar_type)0;                                                                                                                                                              \
    result.m21 = (scalar_type)0;                                                                                                                                                              \
    result.m22 = (scalar_type)0;                                                                                                                                                              \
    return result;                                                                                                                                                                            \
  }                                                                                                                                                                                           \
  LM2_API mat_type mat_type##_make(scalar_type m00, scalar_type m01, scalar_type m02, scalar_type m10, scalar_type m11, scalar_type m12, scalar_type m20, scalar_type m21, scalar_type m22) { \
    mat_type result;                                                                                                                                                                          \
    result.m00 = m00;                                                                                                                                                                         \
    result.m01 = m01;                                                                                                                                                                         \
    result.m02 = m02;                                                                                                                                                                         \
    result.m10 = m10;                                                                                                                                                                         \
    result.m11 = m11;                                                                                                                                                                         \
    result.m12 = m12;                                                                                                                                                                         \
    result.m20 = m20;                                                                                                                                                                         \
    result.m21 = m21;                                                                                                                                                                         \
    result.m22 = m22;                                                                                                                                                                         \
    return result;                                                                                                                                                                            \
  }

#define _LM2_IMPL_M3X3_TRANSFORM(mat_type, scalar_type, scalar_suffix, vec2_type)       \
  LM2_API mat_type mat_type##_scale(vec2_type scale) {                                  \
    mat_type result;                                                                    \
    result.m00 = scale.x;                                                               \
    result.m01 = (scalar_type)0;                                                        \
    result.m02 = (scalar_type)0;                                                        \
    result.m10 = (scalar_type)0;                                                        \
    result.m11 = scale.y;                                                               \
    result.m12 = (scalar_type)0;                                                        \
    result.m20 = (scalar_type)0;                                                        \
    result.m21 = (scalar_type)0;                                                        \
    result.m22 = (scalar_type)1;                                                        \
    return result;                                                                      \
  }                                                                                     \
  LM2_API mat_type mat_type##_scale_uniform(scalar_type scale) {                        \
    mat_type result;                                                                    \
    result.m00 = scale;                                                                 \
    result.m01 = (scalar_type)0;                                                        \
    result.m02 = (scalar_type)0;                                                        \
    result.m10 = (scalar_type)0;                                                        \
    result.m11 = scale;                                                                 \
    result.m12 = (scalar_type)0;                                                        \
    result.m20 = (scalar_type)0;                                                        \
    result.m21 = (scalar_type)0;                                                        \
    result.m22 = (scalar_type)1;                                                        \
    return result;                                                                      \
  }                                                                                     \
  LM2_API mat_type mat_type##_translate(vec2_type translation) {                        \
    mat_type result;                                                                    \
    result.m00 = (scalar_type)1;                                                        \
    result.m01 = (scalar_type)0;                                                        \
    result.m02 = translation.x;                                                         \
    result.m10 = (scalar_type)0;                                                        \
    result.m11 = (scalar_type)1;                                                        \
    result.m12 = translation.y;                                                         \
    result.m20 = (scalar_type)0;                                                        \
    result.m21 = (scalar_type)0;                                                        \
    result.m22 = (scalar_type)1;                                                        \
    return result;                                                                      \
  }                                                                                     \
  LM2_API mat_type mat_type##_rotate(scalar_type angle) {                               \
    scalar_type c = lm2_cos_##scalar_suffix(angle);                                     \
    scalar_type s = lm2_sin_##scalar_suffix(angle);                                     \
    mat_type result;                                                                    \
    result.m00 = c;                                                                     \
    result.m01 = lm2_neg_##scalar_suffix(s);                                            \
    result.m02 = (scalar_type)0;                                                        \
    result.m10 = s;                                                                     \
    result.m11 = c;                                                                     \
    result.m12 = (scalar_type)0;                                                        \
    result.m20 = (scalar_type)0;                                                        \
    result.m21 = (scalar_type)0;                                                        \
    result.m22 = (scalar_type)1;                                                        \
    return result;                                                                      \
  }                                                                                     \
  LM2_API mat_type mat_type##_rotate_around_pivot(scalar_type angle, vec2_type pivot) { \
    scalar_type c = lm2_cos_##scalar_suffix(angle);                                     \
    scalar_type s = lm2_sin_##scalar_suffix(angle);                                     \
    scalar_type one_minus_c = lm2_sub_##scalar_suffix((scalar_type)1, c);               \
    mat_type result;                                                                    \
    result.m00 = c;                                                                     \
    result.m01 = lm2_neg_##scalar_suffix(s);                                            \
    result.m02 = lm2_add_##scalar_suffix(                                               \
        lm2_mul_##scalar_suffix(pivot.x, one_minus_c),                                  \
        lm2_mul_##scalar_suffix(pivot.y, s));                                           \
    result.m10 = s;                                                                     \
    result.m11 = c;                                                                     \
    result.m12 = lm2_add_##scalar_suffix(                                               \
        lm2_mul_##scalar_suffix(pivot.y, one_minus_c),                                  \
        lm2_mul_##scalar_suffix(lm2_neg_##scalar_suffix(pivot.x), s));                  \
    result.m20 = (scalar_type)0;                                                        \
    result.m21 = (scalar_type)0;                                                        \
    result.m22 = (scalar_type)1;                                                        \
    return result;                                                                      \
  }                                                                                     \
  LM2_API mat_type mat_type##_scale_translate(vec2_type scale, vec2_type translation) { \
    mat_type result;                                                                    \
    result.m00 = scale.x;                                                               \
    result.m01 = (scalar_type)0;                                                        \
    result.m02 = translation.x;                                                         \
    result.m10 = (scalar_type)0;                                                        \
    result.m11 = scale.y;                                                               \
    result.m12 = translation.y;                                                         \
    result.m20 = (scalar_type)0;                                                        \
    result.m21 = (scalar_type)0;                                                        \
    result.m22 = (scalar_type)1;                                                        \
    return result;                                                                      \
  }

#define _LM2_IMPL_M3X3_OPS(mat_type, scalar_type, scalar_suffix, vec2_type, vec3_type)                                 \
  LM2_API mat_type mat_type##_multiply(mat_type a, mat_type b) {                                                       \
    mat_type result;                                                                                                   \
    result.m00 = lm2_add_##scalar_suffix(                                                                              \
        lm2_add_##scalar_suffix(                                                                                       \
            lm2_mul_##scalar_suffix(a.m00, b.m00),                                                                     \
            lm2_mul_##scalar_suffix(a.m01, b.m10)),                                                                    \
        lm2_mul_##scalar_suffix(a.m02, b.m20));                                                                        \
    result.m01 = lm2_add_##scalar_suffix(                                                                              \
        lm2_add_##scalar_suffix(                                                                                       \
            lm2_mul_##scalar_suffix(a.m00, b.m01),                                                                     \
            lm2_mul_##scalar_suffix(a.m01, b.m11)),                                                                    \
        lm2_mul_##scalar_suffix(a.m02, b.m21));                                                                        \
    result.m02 = lm2_add_##scalar_suffix(                                                                              \
        lm2_add_##scalar_suffix(                                                                                       \
            lm2_mul_##scalar_suffix(a.m00, b.m02),                                                                     \
            lm2_mul_##scalar_suffix(a.m01, b.m12)),                                                                    \
        lm2_mul_##scalar_suffix(a.m02, b.m22));                                                                        \
    result.m10 = lm2_add_##scalar_suffix(                                                                              \
        lm2_add_##scalar_suffix(                                                                                       \
            lm2_mul_##scalar_suffix(a.m10, b.m00),                                                                     \
            lm2_mul_##scalar_suffix(a.m11, b.m10)),                                                                    \
        lm2_mul_##scalar_suffix(a.m12, b.m20));                                                                        \
    result.m11 = lm2_add_##scalar_suffix(                                                                              \
        lm2_add_##scalar_suffix(                                                                                       \
            lm2_mul_##scalar_suffix(a.m10, b.m01),                                                                     \
            lm2_mul_##scalar_suffix(a.m11, b.m11)),                                                                    \
        lm2_mul_##scalar_suffix(a.m12, b.m21));                                                                        \
    result.m12 = lm2_add_##scalar_suffix(                                                                              \
        lm2_add_##scalar_suffix(                                                                                       \
            lm2_mul_##scalar_suffix(a.m10, b.m02),                                                                     \
            lm2_mul_##scalar_suffix(a.m11, b.m12)),                                                                    \
        lm2_mul_##scalar_suffix(a.m12, b.m22));                                                                        \
    result.m20 = lm2_add_##scalar_suffix(                                                                              \
        lm2_add_##scalar_suffix(                                                                                       \
            lm2_mul_##scalar_suffix(a.m20, b.m00),                                                                     \
            lm2_mul_##scalar_suffix(a.m21, b.m10)),                                                                    \
        lm2_mul_##scalar_suffix(a.m22, b.m20));                                                                        \
    result.m21 = lm2_add_##scalar_suffix(                                                                              \
        lm2_add_##scalar_suffix(                                                                                       \
            lm2_mul_##scalar_suffix(a.m20, b.m01),                                                                     \
            lm2_mul_##scalar_suffix(a.m21, b.m11)),                                                                    \
        lm2_mul_##scalar_suffix(a.m22, b.m21));                                                                        \
    result.m22 = lm2_add_##scalar_suffix(                                                                              \
        lm2_add_##scalar_suffix(                                                                                       \
            lm2_mul_##scalar_suffix(a.m20, b.m02),                                                                     \
            lm2_mul_##scalar_suffix(a.m21, b.m12)),                                                                    \
        lm2_mul_##scalar_suffix(a.m22, b.m22));                                                                        \
    return result;                                                                                                     \
  }                                                                                                                    \
  LM2_API mat_type mat_type##_transpose(mat_type m) {                                                                  \
    mat_type result;                                                                                                   \
    result.m00 = m.m00;                                                                                                \
    result.m01 = m.m10;                                                                                                \
    result.m02 = m.m20;                                                                                                \
    result.m10 = m.m01;                                                                                                \
    result.m11 = m.m11;                                                                                                \
    result.m12 = m.m21;                                                                                                \
    result.m20 = m.m02;                                                                                                \
    result.m21 = m.m12;                                                                                                \
    result.m22 = m.m22;                                                                                                \
    return result;                                                                                                     \
  }                                                                                                                    \
  LM2_API scalar_type mat_type##_determinant(mat_type m) {                                                             \
    scalar_type term1 = lm2_mul_##scalar_suffix(m.m00,                                                                 \
                                                lm2_sub_##scalar_suffix(                                               \
                                                    lm2_mul_##scalar_suffix(m.m11, m.m22),                             \
                                                    lm2_mul_##scalar_suffix(m.m12, m.m21)));                           \
    scalar_type term2 = lm2_mul_##scalar_suffix(m.m01,                                                                 \
                                                lm2_sub_##scalar_suffix(                                               \
                                                    lm2_mul_##scalar_suffix(m.m10, m.m22),                             \
                                                    lm2_mul_##scalar_suffix(m.m12, m.m20)));                           \
    scalar_type term3 = lm2_mul_##scalar_suffix(m.m02,                                                                 \
                                                lm2_sub_##scalar_suffix(                                               \
                                                    lm2_mul_##scalar_suffix(m.m10, m.m21),                             \
                                                    lm2_mul_##scalar_suffix(m.m11, m.m20)));                           \
    return lm2_sub_##scalar_suffix(lm2_add_##scalar_suffix(term1, term3), term2);                                      \
  }                                                                                                                    \
  LM2_API scalar_type mat_type##_trace(mat_type m) {                                                                   \
    return lm2_add_##scalar_suffix(                                                                                    \
        lm2_add_##scalar_suffix(m.m00, m.m11),                                                                         \
        m.m22);                                                                                                        \
  }                                                                                                                    \
  LM2_API mat_type mat_type##_inverse(mat_type m) {                                                                    \
    scalar_type det = mat_type##_determinant(m);                                                                       \
    LM2_ASSERT_UNSAFE(lm2_abs_##scalar_suffix(det) > (scalar_type)0.000001);                                           \
    scalar_type inv_det = lm2_div_##scalar_suffix((scalar_type)1, det);                                                \
    mat_type result;                                                                                                   \
    result.m00 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_sub_##scalar_suffix(                                                      \
                                             lm2_mul_##scalar_suffix(m.m11, m.m22),                                    \
                                             lm2_mul_##scalar_suffix(m.m12, m.m21)));                                  \
    result.m01 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_sub_##scalar_suffix(                                                      \
                                             lm2_mul_##scalar_suffix(m.m02, m.m21),                                    \
                                             lm2_mul_##scalar_suffix(m.m01, m.m22)));                                  \
    result.m02 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_sub_##scalar_suffix(                                                      \
                                             lm2_mul_##scalar_suffix(m.m01, m.m12),                                    \
                                             lm2_mul_##scalar_suffix(m.m02, m.m11)));                                  \
    result.m10 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_sub_##scalar_suffix(                                                      \
                                             lm2_mul_##scalar_suffix(m.m12, m.m20),                                    \
                                             lm2_mul_##scalar_suffix(m.m10, m.m22)));                                  \
    result.m11 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_sub_##scalar_suffix(                                                      \
                                             lm2_mul_##scalar_suffix(m.m00, m.m22),                                    \
                                             lm2_mul_##scalar_suffix(m.m02, m.m20)));                                  \
    result.m12 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_sub_##scalar_suffix(                                                      \
                                             lm2_mul_##scalar_suffix(m.m02, m.m10),                                    \
                                             lm2_mul_##scalar_suffix(m.m00, m.m12)));                                  \
    result.m20 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_sub_##scalar_suffix(                                                      \
                                             lm2_mul_##scalar_suffix(m.m10, m.m21),                                    \
                                             lm2_mul_##scalar_suffix(m.m11, m.m20)));                                  \
    result.m21 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_sub_##scalar_suffix(                                                      \
                                             lm2_mul_##scalar_suffix(m.m01, m.m20),                                    \
                                             lm2_mul_##scalar_suffix(m.m00, m.m21)));                                  \
    result.m22 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_sub_##scalar_suffix(                                                      \
                                             lm2_mul_##scalar_suffix(m.m00, m.m11),                                    \
                                             lm2_mul_##scalar_suffix(m.m01, m.m10)));                                  \
    return result;                                                                                                     \
  }                                                                                                                    \
  LM2_API vec2_type mat_type##_transform_point(mat_type m, vec2_type v) {                                              \
    scalar_type w = lm2_add_##scalar_suffix(                                                                           \
        lm2_add_##scalar_suffix(                                                                                       \
            lm2_mul_##scalar_suffix(m.m20, v.x),                                                                       \
            lm2_mul_##scalar_suffix(m.m21, v.y)),                                                                      \
        m.m22);                                                                                                        \
    LM2_ASSERT_UNSAFE(lm2_abs_##scalar_suffix(w) > (scalar_type)0.000001);                                             \
    scalar_type inv_w = lm2_div_##scalar_suffix((scalar_type)1, w);                                                    \
    vec2_type result;                                                                                                  \
    result.x = lm2_mul_##scalar_suffix(inv_w,                                                                          \
                                       lm2_add_##scalar_suffix(                                                        \
                                           lm2_add_##scalar_suffix(                                                    \
                                               lm2_mul_##scalar_suffix(m.m00, v.x),                                    \
                                               lm2_mul_##scalar_suffix(m.m01, v.y)),                                   \
                                           m.m02));                                                                    \
    result.y = lm2_mul_##scalar_suffix(inv_w,                                                                          \
                                       lm2_add_##scalar_suffix(                                                        \
                                           lm2_add_##scalar_suffix(                                                    \
                                               lm2_mul_##scalar_suffix(m.m10, v.x),                                    \
                                               lm2_mul_##scalar_suffix(m.m11, v.y)),                                   \
                                           m.m12));                                                                    \
    return result;                                                                                                     \
  }                                                                                                                    \
  LM2_API vec2_type mat_type##_transform_vector(mat_type m, vec2_type v) {                                             \
    vec2_type result;                                                                                                  \
    result.x = lm2_add_##scalar_suffix(                                                                                \
        lm2_mul_##scalar_suffix(m.m00, v.x),                                                                           \
        lm2_mul_##scalar_suffix(m.m01, v.y));                                                                          \
    result.y = lm2_add_##scalar_suffix(                                                                                \
        lm2_mul_##scalar_suffix(m.m10, v.x),                                                                           \
        lm2_mul_##scalar_suffix(m.m11, v.y));                                                                          \
    return result;                                                                                                     \
  }                                                                                                                    \
  LM2_API vec3_type mat_type##_transform(mat_type m, vec3_type v) {                                                    \
    vec3_type result;                                                                                                  \
    result.x = lm2_add_##scalar_suffix(                                                                                \
        lm2_add_##scalar_suffix(                                                                                       \
            lm2_mul_##scalar_suffix(m.m00, v.x),                                                                       \
            lm2_mul_##scalar_suffix(m.m01, v.y)),                                                                      \
        lm2_mul_##scalar_suffix(m.m02, v.z));                                                                          \
    result.y = lm2_add_##scalar_suffix(                                                                                \
        lm2_add_##scalar_suffix(                                                                                       \
            lm2_mul_##scalar_suffix(m.m10, v.x),                                                                       \
            lm2_mul_##scalar_suffix(m.m11, v.y)),                                                                      \
        lm2_mul_##scalar_suffix(m.m12, v.z));                                                                          \
    result.z = lm2_add_##scalar_suffix(                                                                                \
        lm2_add_##scalar_suffix(                                                                                       \
            lm2_mul_##scalar_suffix(m.m20, v.x),                                                                       \
            lm2_mul_##scalar_suffix(m.m21, v.y)),                                                                      \
        lm2_mul_##scalar_suffix(m.m22, v.z));                                                                          \
    return result;                                                                                                     \
  }                                                                                                                    \
  LM2_API void mat_type##_transform_points(mat_type m, vec2_type* points, uint32_t count) {                            \
    LM2_ASSERT(points != NULL);                                                                                        \
    for (uint32_t i = 0; i < count; i = lm2_add_u32(i, 1)) {                                                           \
      points[i] = mat_type##_transform_point(m, points[i]);                                                            \
    }                                                                                                                  \
  }                                                                                                                    \
  LM2_API void mat_type##_transform_points_src_dst(mat_type m, const vec2_type* src, vec2_type* dst, uint32_t count) { \
    LM2_ASSERT(src != NULL);                                                                                           \
    LM2_ASSERT(dst != NULL);                                                                                           \
    for (uint32_t i = 0; i < count; i = lm2_add_u32(i, 1)) {                                                           \
      dst[i] = mat_type##_transform_point(m, src[i]);                                                                  \
    }                                                                                                                  \
  }

#define _LM2_IMPL_M3X3_GETTERS(mat_type, scalar_type, scalar_suffix, vec2_type) \
  LM2_API scalar_type mat_type##_get_rotation(mat_type m) {                     \
    return lm2_atan2_##scalar_suffix(m.m10, m.m00);                             \
  }                                                                             \
  LM2_API vec2_type mat_type##_get_scale(mat_type m) {                          \
    vec2_type result;                                                           \
    result.x = lm2_sqrt_##scalar_suffix(                                        \
        lm2_add_##scalar_suffix(                                                \
            lm2_mul_##scalar_suffix(m.m00, m.m00),                              \
            lm2_mul_##scalar_suffix(m.m10, m.m10)));                            \
    result.y = lm2_sqrt_##scalar_suffix(                                        \
        lm2_add_##scalar_suffix(                                                \
            lm2_mul_##scalar_suffix(m.m01, m.m01),                              \
            lm2_mul_##scalar_suffix(m.m11, m.m11)));                            \
    return result;                                                              \
  }                                                                             \
  LM2_API vec2_type mat_type##_get_translation(mat_type m) {                    \
    vec2_type result;                                                           \
    result.x = m.m02;                                                           \
    result.y = m.m12;                                                           \
    return result;                                                              \
  }

// =============================================================================
// Matrix 3x3 Implementations
// =============================================================================

_LM2_IMPL_M3X3_BASIC(lm2_m3x3f64, double, f64)
_LM2_IMPL_M3X3_BASIC(lm2_m3x3f32, float, f32)

_LM2_IMPL_M3X3_TRANSFORM(lm2_m3x3f64, double, f64, lm2_v2f64)
_LM2_IMPL_M3X3_TRANSFORM(lm2_m3x3f32, float, f32, lm2_v2f32)

_LM2_IMPL_M3X3_OPS(lm2_m3x3f64, double, f64, lm2_v2f64, lm2_v3f64)
_LM2_IMPL_M3X3_OPS(lm2_m3x3f32, float, f32, lm2_v2f32, lm2_v3f32)

_LM2_IMPL_M3X3_GETTERS(lm2_m3x3f64, double, f64, lm2_v2f64)
_LM2_IMPL_M3X3_GETTERS(lm2_m3x3f32, float, f32, lm2_v2f32)
