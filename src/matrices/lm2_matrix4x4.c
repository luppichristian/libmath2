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
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/scalar/lm2_trigonometry.h>
#include <lm2/vectors/lm2_vector_specifics.h>

// =============================================================================
// Implementation Macros
// =============================================================================

#define _LM2_IMPL_M4X4_BASIC(mat_type, scalar_type, scalar_suffix)                                                                                                                                                                                                                                                   \
  LM2_API mat_type mat_type##_identity(void) {                                                                                                                                                                                                                                                                       \
    mat_type result;                                                                                                                                                                                                                                                                                                 \
    result.m00 = (scalar_type)1;                                                                                                                                                                                                                                                                                     \
    result.m01 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m02 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m03 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m10 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m11 = (scalar_type)1;                                                                                                                                                                                                                                                                                     \
    result.m12 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m13 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m20 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m21 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m22 = (scalar_type)1;                                                                                                                                                                                                                                                                                     \
    result.m23 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m30 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m31 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m32 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m33 = (scalar_type)1;                                                                                                                                                                                                                                                                                     \
    return result;                                                                                                                                                                                                                                                                                                   \
  }                                                                                                                                                                                                                                                                                                                  \
  LM2_API mat_type mat_type##_zero(void) {                                                                                                                                                                                                                                                                           \
    mat_type result;                                                                                                                                                                                                                                                                                                 \
    result.m00 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m01 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m02 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m03 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m10 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m11 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m12 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m13 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m20 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m21 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m22 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m23 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m30 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m31 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m32 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    result.m33 = (scalar_type)0;                                                                                                                                                                                                                                                                                     \
    return result;                                                                                                                                                                                                                                                                                                   \
  }                                                                                                                                                                                                                                                                                                                  \
  LM2_API mat_type mat_type##_make(scalar_type m00, scalar_type m01, scalar_type m02, scalar_type m03, scalar_type m10, scalar_type m11, scalar_type m12, scalar_type m13, scalar_type m20, scalar_type m21, scalar_type m22, scalar_type m23, scalar_type m30, scalar_type m31, scalar_type m32, scalar_type m33) { \
    mat_type result;                                                                                                                                                                                                                                                                                                 \
    result.m00 = m00;                                                                                                                                                                                                                                                                                                \
    result.m01 = m01;                                                                                                                                                                                                                                                                                                \
    result.m02 = m02;                                                                                                                                                                                                                                                                                                \
    result.m03 = m03;                                                                                                                                                                                                                                                                                                \
    result.m10 = m10;                                                                                                                                                                                                                                                                                                \
    result.m11 = m11;                                                                                                                                                                                                                                                                                                \
    result.m12 = m12;                                                                                                                                                                                                                                                                                                \
    result.m13 = m13;                                                                                                                                                                                                                                                                                                \
    result.m20 = m20;                                                                                                                                                                                                                                                                                                \
    result.m21 = m21;                                                                                                                                                                                                                                                                                                \
    result.m22 = m22;                                                                                                                                                                                                                                                                                                \
    result.m23 = m23;                                                                                                                                                                                                                                                                                                \
    result.m30 = m30;                                                                                                                                                                                                                                                                                                \
    result.m31 = m31;                                                                                                                                                                                                                                                                                                \
    result.m32 = m32;                                                                                                                                                                                                                                                                                                \
    result.m33 = m33;                                                                                                                                                                                                                                                                                                \
    return result;                                                                                                                                                                                                                                                                                                   \
  }

#define _LM2_IMPL_M4X4_TRANSFORM(mat_type, scalar_type, scalar_suffix, vec3_type)                                  \
  LM2_API mat_type mat_type##_scale(vec3_type scale) {                                                             \
    mat_type result = mat_type##_identity();                                                                       \
    result.m00 = scale.x;                                                                                          \
    result.m11 = scale.y;                                                                                          \
    result.m22 = scale.z;                                                                                          \
    return result;                                                                                                 \
  }                                                                                                                \
  LM2_API mat_type mat_type##_scale_uniform(scalar_type scale) {                                                   \
    mat_type result = mat_type##_identity();                                                                       \
    result.m00 = scale;                                                                                            \
    result.m11 = scale;                                                                                            \
    result.m22 = scale;                                                                                            \
    return result;                                                                                                 \
  }                                                                                                                \
  LM2_API mat_type mat_type##_translate(vec3_type translation) {                                                   \
    mat_type result = mat_type##_identity();                                                                       \
    result.m03 = translation.x;                                                                                    \
    result.m13 = translation.y;                                                                                    \
    result.m23 = translation.z;                                                                                    \
    return result;                                                                                                 \
  }                                                                                                                \
  LM2_API mat_type mat_type##_rotate_x(scalar_type angle) {                                                        \
    scalar_type c = lm2_cos_##scalar_suffix(angle);                                                                \
    scalar_type s = lm2_sin_##scalar_suffix(angle);                                                                \
    mat_type result = mat_type##_identity();                                                                       \
    result.m11 = c;                                                                                                \
    result.m12 = lm2_neg_##scalar_suffix(s);                                                                       \
    result.m21 = s;                                                                                                \
    result.m22 = c;                                                                                                \
    return result;                                                                                                 \
  }                                                                                                                \
  LM2_API mat_type mat_type##_rotate_y(scalar_type angle) {                                                        \
    scalar_type c = lm2_cos_##scalar_suffix(angle);                                                                \
    scalar_type s = lm2_sin_##scalar_suffix(angle);                                                                \
    mat_type result = mat_type##_identity();                                                                       \
    result.m00 = c;                                                                                                \
    result.m02 = s;                                                                                                \
    result.m20 = lm2_neg_##scalar_suffix(s);                                                                       \
    result.m22 = c;                                                                                                \
    return result;                                                                                                 \
  }                                                                                                                \
  LM2_API mat_type mat_type##_rotate_z(scalar_type angle) {                                                        \
    scalar_type c = lm2_cos_##scalar_suffix(angle);                                                                \
    scalar_type s = lm2_sin_##scalar_suffix(angle);                                                                \
    mat_type result = mat_type##_identity();                                                                       \
    result.m00 = c;                                                                                                \
    result.m01 = lm2_neg_##scalar_suffix(s);                                                                       \
    result.m10 = s;                                                                                                \
    result.m11 = c;                                                                                                \
    return result;                                                                                                 \
  }                                                                                                                \
  LM2_API mat_type mat_type##_rotate_axis(vec3_type axis, scalar_type angle) {                                     \
    vec3_type n = lm2_normalize_##vec3_type(axis);                                                                 \
    scalar_type c = lm2_cos_##scalar_suffix(angle);                                                                \
    scalar_type s = lm2_sin_##scalar_suffix(angle);                                                                \
    scalar_type one_minus_c = lm2_sub_##scalar_suffix((scalar_type)1, c);                                          \
    mat_type result;                                                                                               \
    result.m00 = lm2_add_##scalar_suffix(c,                                                                        \
                                         lm2_mul_##scalar_suffix(lm2_mul_##scalar_suffix(n.x, n.x), one_minus_c)); \
    result.m01 = lm2_sub_##scalar_suffix(                                                                          \
        lm2_mul_##scalar_suffix(lm2_mul_##scalar_suffix(n.x, n.y), one_minus_c),                                   \
        lm2_mul_##scalar_suffix(n.z, s));                                                                          \
    result.m02 = lm2_add_##scalar_suffix(                                                                          \
        lm2_mul_##scalar_suffix(lm2_mul_##scalar_suffix(n.x, n.z), one_minus_c),                                   \
        lm2_mul_##scalar_suffix(n.y, s));                                                                          \
    result.m03 = (scalar_type)0;                                                                                   \
    result.m10 = lm2_add_##scalar_suffix(                                                                          \
        lm2_mul_##scalar_suffix(lm2_mul_##scalar_suffix(n.y, n.x), one_minus_c),                                   \
        lm2_mul_##scalar_suffix(n.z, s));                                                                          \
    result.m11 = lm2_add_##scalar_suffix(c,                                                                        \
                                         lm2_mul_##scalar_suffix(lm2_mul_##scalar_suffix(n.y, n.y), one_minus_c)); \
    result.m12 = lm2_sub_##scalar_suffix(                                                                          \
        lm2_mul_##scalar_suffix(lm2_mul_##scalar_suffix(n.y, n.z), one_minus_c),                                   \
        lm2_mul_##scalar_suffix(n.x, s));                                                                          \
    result.m13 = (scalar_type)0;                                                                                   \
    result.m20 = lm2_sub_##scalar_suffix(                                                                          \
        lm2_mul_##scalar_suffix(lm2_mul_##scalar_suffix(n.z, n.x), one_minus_c),                                   \
        lm2_mul_##scalar_suffix(n.y, s));                                                                          \
    result.m21 = lm2_add_##scalar_suffix(                                                                          \
        lm2_mul_##scalar_suffix(lm2_mul_##scalar_suffix(n.z, n.y), one_minus_c),                                   \
        lm2_mul_##scalar_suffix(n.x, s));                                                                          \
    result.m22 = lm2_add_##scalar_suffix(c,                                                                        \
                                         lm2_mul_##scalar_suffix(lm2_mul_##scalar_suffix(n.z, n.z), one_minus_c)); \
    result.m23 = (scalar_type)0;                                                                                   \
    result.m30 = (scalar_type)0;                                                                                   \
    result.m31 = (scalar_type)0;                                                                                   \
    result.m32 = (scalar_type)0;                                                                                   \
    result.m33 = (scalar_type)1;                                                                                   \
    return result;                                                                                                 \
  }                                                                                                                \
  LM2_API mat_type mat_type##_scale_translate(vec3_type scale, vec3_type translation) {                            \
    mat_type result = mat_type##_identity();                                                                       \
    result.m00 = scale.x;                                                                                          \
    result.m11 = scale.y;                                                                                          \
    result.m22 = scale.z;                                                                                          \
    result.m03 = translation.x;                                                                                    \
    result.m13 = translation.y;                                                                                    \
    result.m23 = translation.z;                                                                                    \
    return result;                                                                                                 \
  }                                                                                                                \
  LM2_API mat_type mat_type##_world_transform(vec3_type translation, vec3_type scale, vec3_type rotation_euler) {  \
    mat_type rx = mat_type##_rotate_x(rotation_euler.x);                                                           \
    mat_type ry = mat_type##_rotate_y(rotation_euler.y);                                                           \
    mat_type rz = mat_type##_rotate_z(rotation_euler.z);                                                           \
    mat_type rotation = mat_type##_multiply(mat_type##_multiply(rz, ry), rx);                                      \
    mat_type scale_mat = mat_type##_scale(scale);                                                                  \
    mat_type translate_mat = mat_type##_translate(translation);                                                    \
    return mat_type##_multiply(mat_type##_multiply(scale_mat, rotation), translate_mat);                           \
  }

#define _LM2_IMPL_M4X4_MULTIPLY(mat_type, scalar_type, scalar_suffix)                   \
  LM2_API mat_type mat_type##_multiply(mat_type a, mat_type b) {                        \
    mat_type result;                                                                    \
    for (int row = 0; row < 4; row = lm2_add_i32(row, 1)) {                             \
      for (int col = 0; col < 4; col = lm2_add_i32(col, 1)) {                           \
        scalar_type sum = (scalar_type)0;                                               \
        for (int k = 0; k < 4; k = lm2_add_i32(k, 1)) {                                 \
          sum = lm2_add_##scalar_suffix(sum,                                            \
                                        lm2_mul_##scalar_suffix(                        \
                                            a.m[lm2_add_i32(lm2_mul_i32(row, 4), k)],   \
                                            b.m[lm2_add_i32(lm2_mul_i32(k, 4), col)])); \
        }                                                                               \
        result.m[lm2_add_i32(lm2_mul_i32(row, 4), col)] = sum;                          \
      }                                                                                 \
    }                                                                                   \
    return result;                                                                      \
  }

#define _LM2_IMPL_M4X4_OPS(mat_type, scalar_type, scalar_suffix, vec3_type, vec4_type)                                 \
  LM2_API mat_type mat_type##_transpose(mat_type m) {                                                                  \
    mat_type result;                                                                                                   \
    result.m00 = m.m00;                                                                                                \
    result.m01 = m.m10;                                                                                                \
    result.m02 = m.m20;                                                                                                \
    result.m03 = m.m30;                                                                                                \
    result.m10 = m.m01;                                                                                                \
    result.m11 = m.m11;                                                                                                \
    result.m12 = m.m21;                                                                                                \
    result.m13 = m.m31;                                                                                                \
    result.m20 = m.m02;                                                                                                \
    result.m21 = m.m12;                                                                                                \
    result.m22 = m.m22;                                                                                                \
    result.m23 = m.m32;                                                                                                \
    result.m30 = m.m03;                                                                                                \
    result.m31 = m.m13;                                                                                                \
    result.m32 = m.m23;                                                                                                \
    result.m33 = m.m33;                                                                                                \
    return result;                                                                                                     \
  }                                                                                                                    \
  LM2_API scalar_type mat_type##_determinant(mat_type m) {                                                             \
    scalar_type a00 = m.m00, a01 = m.m01, a02 = m.m02, a03 = m.m03;                                                    \
    scalar_type a10 = m.m10, a11 = m.m11, a12 = m.m12, a13 = m.m13;                                                    \
    scalar_type a20 = m.m20, a21 = m.m21, a22 = m.m22, a23 = m.m23;                                                    \
    scalar_type a30 = m.m30, a31 = m.m31, a32 = m.m32, a33 = m.m33;                                                    \
    scalar_type b00 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a00, a11),                                       \
                                              lm2_mul_##scalar_suffix(a01, a10));                                      \
    scalar_type b01 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a00, a12),                                       \
                                              lm2_mul_##scalar_suffix(a02, a10));                                      \
    scalar_type b02 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a00, a13),                                       \
                                              lm2_mul_##scalar_suffix(a03, a10));                                      \
    scalar_type b03 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a01, a12),                                       \
                                              lm2_mul_##scalar_suffix(a02, a11));                                      \
    scalar_type b04 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a01, a13),                                       \
                                              lm2_mul_##scalar_suffix(a03, a11));                                      \
    scalar_type b05 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a02, a13),                                       \
                                              lm2_mul_##scalar_suffix(a03, a12));                                      \
    scalar_type b06 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a20, a31),                                       \
                                              lm2_mul_##scalar_suffix(a21, a30));                                      \
    scalar_type b07 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a20, a32),                                       \
                                              lm2_mul_##scalar_suffix(a22, a30));                                      \
    scalar_type b08 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a20, a33),                                       \
                                              lm2_mul_##scalar_suffix(a23, a30));                                      \
    scalar_type b09 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a21, a32),                                       \
                                              lm2_mul_##scalar_suffix(a22, a31));                                      \
    scalar_type b10 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a21, a33),                                       \
                                              lm2_mul_##scalar_suffix(a23, a31));                                      \
    scalar_type b11 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a22, a33),                                       \
                                              lm2_mul_##scalar_suffix(a23, a32));                                      \
    return lm2_add_##scalar_suffix(                                                                                    \
        lm2_sub_##scalar_suffix(                                                                                       \
            lm2_add_##scalar_suffix(                                                                                   \
                lm2_mul_##scalar_suffix(b00, b11),                                                                     \
                lm2_mul_##scalar_suffix(b01, b10)),                                                                    \
            lm2_mul_##scalar_suffix(b02, b09)),                                                                        \
        lm2_sub_##scalar_suffix(                                                                                       \
            lm2_mul_##scalar_suffix(b03, b08),                                                                         \
            lm2_add_##scalar_suffix(                                                                                   \
                lm2_mul_##scalar_suffix(b04, b07),                                                                     \
                lm2_mul_##scalar_suffix(b05, b06))));                                                                  \
  }                                                                                                                    \
  LM2_API scalar_type mat_type##_trace(mat_type m) {                                                                   \
    return lm2_add_##scalar_suffix(                                                                                    \
        lm2_add_##scalar_suffix(                                                                                       \
            lm2_add_##scalar_suffix(m.m00, m.m11),                                                                     \
            m.m22),                                                                                                    \
        m.m33);                                                                                                        \
  }                                                                                                                    \
  LM2_API mat_type mat_type##_inverse(mat_type m) {                                                                    \
    scalar_type a00 = m.m00, a01 = m.m01, a02 = m.m02, a03 = m.m03;                                                    \
    scalar_type a10 = m.m10, a11 = m.m11, a12 = m.m12, a13 = m.m13;                                                    \
    scalar_type a20 = m.m20, a21 = m.m21, a22 = m.m22, a23 = m.m23;                                                    \
    scalar_type a30 = m.m30, a31 = m.m31, a32 = m.m32, a33 = m.m33;                                                    \
    scalar_type b00 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a00, a11),                                       \
                                              lm2_mul_##scalar_suffix(a01, a10));                                      \
    scalar_type b01 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a00, a12),                                       \
                                              lm2_mul_##scalar_suffix(a02, a10));                                      \
    scalar_type b02 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a00, a13),                                       \
                                              lm2_mul_##scalar_suffix(a03, a10));                                      \
    scalar_type b03 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a01, a12),                                       \
                                              lm2_mul_##scalar_suffix(a02, a11));                                      \
    scalar_type b04 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a01, a13),                                       \
                                              lm2_mul_##scalar_suffix(a03, a11));                                      \
    scalar_type b05 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a02, a13),                                       \
                                              lm2_mul_##scalar_suffix(a03, a12));                                      \
    scalar_type b06 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a20, a31),                                       \
                                              lm2_mul_##scalar_suffix(a21, a30));                                      \
    scalar_type b07 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a20, a32),                                       \
                                              lm2_mul_##scalar_suffix(a22, a30));                                      \
    scalar_type b08 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a20, a33),                                       \
                                              lm2_mul_##scalar_suffix(a23, a30));                                      \
    scalar_type b09 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a21, a32),                                       \
                                              lm2_mul_##scalar_suffix(a22, a31));                                      \
    scalar_type b10 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a21, a33),                                       \
                                              lm2_mul_##scalar_suffix(a23, a31));                                      \
    scalar_type b11 = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a22, a33),                                       \
                                              lm2_mul_##scalar_suffix(a23, a32));                                      \
    scalar_type det = lm2_add_##scalar_suffix(                                                                         \
        lm2_sub_##scalar_suffix(                                                                                       \
            lm2_add_##scalar_suffix(                                                                                   \
                lm2_mul_##scalar_suffix(b00, b11),                                                                     \
                lm2_mul_##scalar_suffix(b01, b10)),                                                                    \
            lm2_mul_##scalar_suffix(b02, b09)),                                                                        \
        lm2_sub_##scalar_suffix(                                                                                       \
            lm2_mul_##scalar_suffix(b03, b08),                                                                         \
            lm2_add_##scalar_suffix(                                                                                   \
                lm2_mul_##scalar_suffix(b04, b07),                                                                     \
                lm2_mul_##scalar_suffix(b05, b06))));                                                                  \
    LM2_ASSERT_UNSAFE(lm2_abs_##scalar_suffix(det) > (scalar_type)0.000001);                                           \
    scalar_type inv_det = lm2_div_##scalar_suffix((scalar_type)1, det);                                                \
    mat_type result;                                                                                                   \
    result.m00 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_add_##scalar_suffix(                                                      \
                                             lm2_sub_##scalar_suffix(                                                  \
                                                 lm2_mul_##scalar_suffix(a11, b11),                                    \
                                                 lm2_mul_##scalar_suffix(a12, b10)),                                   \
                                             lm2_mul_##scalar_suffix(a13, b09)));                                      \
    result.m01 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_sub_##scalar_suffix(                                                      \
                                             lm2_add_##scalar_suffix(                                                  \
                                                 lm2_mul_##scalar_suffix(a02, b10),                                    \
                                                 lm2_mul_##scalar_suffix(a03, b09)),                                   \
                                             lm2_mul_##scalar_suffix(a01, b11)));                                      \
    result.m02 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_add_##scalar_suffix(                                                      \
                                             lm2_sub_##scalar_suffix(                                                  \
                                                 lm2_mul_##scalar_suffix(a31, b05),                                    \
                                                 lm2_mul_##scalar_suffix(a32, b04)),                                   \
                                             lm2_mul_##scalar_suffix(a33, b03)));                                      \
    result.m03 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_sub_##scalar_suffix(                                                      \
                                             lm2_add_##scalar_suffix(                                                  \
                                                 lm2_mul_##scalar_suffix(a22, b04),                                    \
                                                 lm2_mul_##scalar_suffix(a23, b03)),                                   \
                                             lm2_mul_##scalar_suffix(a21, b05)));                                      \
    result.m10 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_sub_##scalar_suffix(                                                      \
                                             lm2_add_##scalar_suffix(                                                  \
                                                 lm2_mul_##scalar_suffix(a12, b08),                                    \
                                                 lm2_mul_##scalar_suffix(a13, b07)),                                   \
                                             lm2_mul_##scalar_suffix(a10, b11)));                                      \
    result.m11 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_add_##scalar_suffix(                                                      \
                                             lm2_sub_##scalar_suffix(                                                  \
                                                 lm2_mul_##scalar_suffix(a00, b11),                                    \
                                                 lm2_mul_##scalar_suffix(a02, b08)),                                   \
                                             lm2_mul_##scalar_suffix(a03, b07)));                                      \
    result.m12 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_sub_##scalar_suffix(                                                      \
                                             lm2_add_##scalar_suffix(                                                  \
                                                 lm2_mul_##scalar_suffix(a32, b02),                                    \
                                                 lm2_mul_##scalar_suffix(a33, b01)),                                   \
                                             lm2_mul_##scalar_suffix(a30, b05)));                                      \
    result.m13 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_add_##scalar_suffix(                                                      \
                                             lm2_sub_##scalar_suffix(                                                  \
                                                 lm2_mul_##scalar_suffix(a20, b05),                                    \
                                                 lm2_mul_##scalar_suffix(a22, b02)),                                   \
                                             lm2_mul_##scalar_suffix(a23, b01)));                                      \
    result.m20 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_add_##scalar_suffix(                                                      \
                                             lm2_sub_##scalar_suffix(                                                  \
                                                 lm2_mul_##scalar_suffix(a10, b10),                                    \
                                                 lm2_mul_##scalar_suffix(a11, b08)),                                   \
                                             lm2_mul_##scalar_suffix(a13, b06)));                                      \
    result.m21 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_sub_##scalar_suffix(                                                      \
                                             lm2_add_##scalar_suffix(                                                  \
                                                 lm2_mul_##scalar_suffix(a01, b08),                                    \
                                                 lm2_mul_##scalar_suffix(a03, b06)),                                   \
                                             lm2_mul_##scalar_suffix(a00, b10)));                                      \
    result.m22 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_add_##scalar_suffix(                                                      \
                                             lm2_sub_##scalar_suffix(                                                  \
                                                 lm2_mul_##scalar_suffix(a30, b04),                                    \
                                                 lm2_mul_##scalar_suffix(a31, b02)),                                   \
                                             lm2_mul_##scalar_suffix(a33, b00)));                                      \
    result.m23 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_sub_##scalar_suffix(                                                      \
                                             lm2_add_##scalar_suffix(                                                  \
                                                 lm2_mul_##scalar_suffix(a21, b02),                                    \
                                                 lm2_mul_##scalar_suffix(a23, b00)),                                   \
                                             lm2_mul_##scalar_suffix(a20, b04)));                                      \
    result.m30 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_sub_##scalar_suffix(                                                      \
                                             lm2_add_##scalar_suffix(                                                  \
                                                 lm2_mul_##scalar_suffix(a11, b07),                                    \
                                                 lm2_mul_##scalar_suffix(a12, b06)),                                   \
                                             lm2_mul_##scalar_suffix(a10, b09)));                                      \
    result.m31 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_add_##scalar_suffix(                                                      \
                                             lm2_sub_##scalar_suffix(                                                  \
                                                 lm2_mul_##scalar_suffix(a00, b09),                                    \
                                                 lm2_mul_##scalar_suffix(a01, b07)),                                   \
                                             lm2_mul_##scalar_suffix(a02, b06)));                                      \
    result.m32 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_sub_##scalar_suffix(                                                      \
                                             lm2_add_##scalar_suffix(                                                  \
                                                 lm2_mul_##scalar_suffix(a31, b01),                                    \
                                                 lm2_mul_##scalar_suffix(a32, b00)),                                   \
                                             lm2_mul_##scalar_suffix(a30, b03)));                                      \
    result.m33 = lm2_mul_##scalar_suffix(inv_det,                                                                      \
                                         lm2_add_##scalar_suffix(                                                      \
                                             lm2_sub_##scalar_suffix(                                                  \
                                                 lm2_mul_##scalar_suffix(a20, b03),                                    \
                                                 lm2_mul_##scalar_suffix(a21, b01)),                                   \
                                             lm2_mul_##scalar_suffix(a22, b00)));                                      \
    return result;                                                                                                     \
  }                                                                                                                    \
  LM2_API vec3_type mat_type##_transform_point(mat_type m, vec3_type v) {                                              \
    scalar_type w = lm2_add_##scalar_suffix(                                                                           \
        lm2_add_##scalar_suffix(                                                                                       \
            lm2_add_##scalar_suffix(                                                                                   \
                lm2_mul_##scalar_suffix(m.m30, v.x),                                                                   \
                lm2_mul_##scalar_suffix(m.m31, v.y)),                                                                  \
            lm2_mul_##scalar_suffix(m.m32, v.z)),                                                                      \
        m.m33);                                                                                                        \
    LM2_ASSERT_UNSAFE(lm2_abs_##scalar_suffix(w) > (scalar_type)0.000001);                                             \
    scalar_type inv_w = lm2_div_##scalar_suffix((scalar_type)1, w);                                                    \
    vec3_type result;                                                                                                  \
    result.x = lm2_mul_##scalar_suffix(inv_w,                                                                          \
                                       lm2_add_##scalar_suffix(                                                        \
                                           lm2_add_##scalar_suffix(                                                    \
                                               lm2_add_##scalar_suffix(                                                \
                                                   lm2_mul_##scalar_suffix(m.m00, v.x),                                \
                                                   lm2_mul_##scalar_suffix(m.m01, v.y)),                               \
                                               lm2_mul_##scalar_suffix(m.m02, v.z)),                                   \
                                           m.m03));                                                                    \
    result.y = lm2_mul_##scalar_suffix(inv_w,                                                                          \
                                       lm2_add_##scalar_suffix(                                                        \
                                           lm2_add_##scalar_suffix(                                                    \
                                               lm2_add_##scalar_suffix(                                                \
                                                   lm2_mul_##scalar_suffix(m.m10, v.x),                                \
                                                   lm2_mul_##scalar_suffix(m.m11, v.y)),                               \
                                               lm2_mul_##scalar_suffix(m.m12, v.z)),                                   \
                                           m.m13));                                                                    \
    result.z = lm2_mul_##scalar_suffix(inv_w,                                                                          \
                                       lm2_add_##scalar_suffix(                                                        \
                                           lm2_add_##scalar_suffix(                                                    \
                                               lm2_add_##scalar_suffix(                                                \
                                                   lm2_mul_##scalar_suffix(m.m20, v.x),                                \
                                                   lm2_mul_##scalar_suffix(m.m21, v.y)),                               \
                                               lm2_mul_##scalar_suffix(m.m22, v.z)),                                   \
                                           m.m23));                                                                    \
    return result;                                                                                                     \
  }                                                                                                                    \
  LM2_API vec3_type mat_type##_transform_vector(mat_type m, vec3_type v) {                                             \
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
  LM2_API vec4_type mat_type##_transform(mat_type m, vec4_type v) {                                                    \
    vec4_type result;                                                                                                  \
    result.x = lm2_add_##scalar_suffix(                                                                                \
        lm2_add_##scalar_suffix(                                                                                       \
            lm2_add_##scalar_suffix(                                                                                   \
                lm2_mul_##scalar_suffix(m.m00, v.x),                                                                   \
                lm2_mul_##scalar_suffix(m.m01, v.y)),                                                                  \
            lm2_mul_##scalar_suffix(m.m02, v.z)),                                                                      \
        lm2_mul_##scalar_suffix(m.m03, v.w));                                                                          \
    result.y = lm2_add_##scalar_suffix(                                                                                \
        lm2_add_##scalar_suffix(                                                                                       \
            lm2_add_##scalar_suffix(                                                                                   \
                lm2_mul_##scalar_suffix(m.m10, v.x),                                                                   \
                lm2_mul_##scalar_suffix(m.m11, v.y)),                                                                  \
            lm2_mul_##scalar_suffix(m.m12, v.z)),                                                                      \
        lm2_mul_##scalar_suffix(m.m13, v.w));                                                                          \
    result.z = lm2_add_##scalar_suffix(                                                                                \
        lm2_add_##scalar_suffix(                                                                                       \
            lm2_add_##scalar_suffix(                                                                                   \
                lm2_mul_##scalar_suffix(m.m20, v.x),                                                                   \
                lm2_mul_##scalar_suffix(m.m21, v.y)),                                                                  \
            lm2_mul_##scalar_suffix(m.m22, v.z)),                                                                      \
        lm2_mul_##scalar_suffix(m.m23, v.w));                                                                          \
    result.w = lm2_add_##scalar_suffix(                                                                                \
        lm2_add_##scalar_suffix(                                                                                       \
            lm2_add_##scalar_suffix(                                                                                   \
                lm2_mul_##scalar_suffix(m.m30, v.x),                                                                   \
                lm2_mul_##scalar_suffix(m.m31, v.y)),                                                                  \
            lm2_mul_##scalar_suffix(m.m32, v.z)),                                                                      \
        lm2_mul_##scalar_suffix(m.m33, v.w));                                                                          \
    return result;                                                                                                     \
  }                                                                                                                    \
  LM2_API void mat_type##_transform_points(mat_type m, vec3_type* points, uint32_t count) {                            \
    LM2_ASSERT(points != NULL);                                                                                        \
    for (uint32_t i = 0; i < count; i = lm2_add_u32(i, 1)) {                                                           \
      points[i] = mat_type##_transform_point(m, points[i]);                                                            \
    }                                                                                                                  \
  }                                                                                                                    \
  LM2_API void mat_type##_transform_points_src_dst(mat_type m, const vec3_type* src, vec3_type* dst, uint32_t count) { \
    LM2_ASSERT(src != NULL);                                                                                           \
    LM2_ASSERT(dst != NULL);                                                                                           \
    for (uint32_t i = 0; i < count; i = lm2_add_u32(i, 1)) {                                                           \
      dst[i] = mat_type##_transform_point(m, src[i]);                                                                  \
    }                                                                                                                  \
  }

#define _LM2_IMPL_M4X4_GETTERS(mat_type, scalar_type, scalar_suffix, vec3_type) \
  LM2_API vec3_type mat_type##_get_scale(mat_type m) {                          \
    vec3_type result;                                                           \
    result.x = lm2_sqrt_##scalar_suffix(                                        \
        lm2_add_##scalar_suffix(                                                \
            lm2_add_##scalar_suffix(                                            \
                lm2_mul_##scalar_suffix(m.m00, m.m00),                          \
                lm2_mul_##scalar_suffix(m.m10, m.m10)),                         \
            lm2_mul_##scalar_suffix(m.m20, m.m20)));                            \
    result.y = lm2_sqrt_##scalar_suffix(                                        \
        lm2_add_##scalar_suffix(                                                \
            lm2_add_##scalar_suffix(                                            \
                lm2_mul_##scalar_suffix(m.m01, m.m01),                          \
                lm2_mul_##scalar_suffix(m.m11, m.m11)),                         \
            lm2_mul_##scalar_suffix(m.m21, m.m21)));                            \
    result.z = lm2_sqrt_##scalar_suffix(                                        \
        lm2_add_##scalar_suffix(                                                \
            lm2_add_##scalar_suffix(                                            \
                lm2_mul_##scalar_suffix(m.m02, m.m02),                          \
                lm2_mul_##scalar_suffix(m.m12, m.m12)),                         \
            lm2_mul_##scalar_suffix(m.m22, m.m22)));                            \
    return result;                                                              \
  }                                                                             \
  LM2_API vec3_type mat_type##_get_translation(mat_type m) {                    \
    vec3_type result;                                                           \
    result.x = m.m03;                                                           \
    result.y = m.m13;                                                           \
    result.z = m.m23;                                                           \
    return result;                                                              \
  }

#define _LM2_IMPL_M4X4_PROJECTION(mat_type, scalar_type, scalar_suffix, vec3_type)                                                                             \
  LM2_API mat_type mat_type##_ortho(scalar_type left, scalar_type right, scalar_type bottom, scalar_type top, scalar_type near_plane, scalar_type far_plane) { \
    scalar_type width = lm2_sub_##scalar_suffix(right, left);                                                                                                  \
    scalar_type height = lm2_sub_##scalar_suffix(top, bottom);                                                                                                 \
    scalar_type depth = lm2_sub_##scalar_suffix(far_plane, near_plane);                                                                                        \
    LM2_ASSERT_UNSAFE(lm2_abs_##scalar_suffix(width) > (scalar_type)0.000001);                                                                                 \
    LM2_ASSERT_UNSAFE(lm2_abs_##scalar_suffix(height) > (scalar_type)0.000001);                                                                                \
    LM2_ASSERT_UNSAFE(lm2_abs_##scalar_suffix(depth) > (scalar_type)0.000001);                                                                                 \
    mat_type result = mat_type##_zero();                                                                                                                       \
    result.m00 = lm2_div_##scalar_suffix((scalar_type)2, width);                                                                                               \
    result.m11 = lm2_div_##scalar_suffix((scalar_type)2, height);                                                                                              \
    result.m22 = lm2_div_##scalar_suffix((scalar_type) - 2, depth);                                                                                            \
    result.m03 = lm2_neg_##scalar_suffix(                                                                                                                      \
        lm2_div_##scalar_suffix(lm2_add_##scalar_suffix(right, left), width));                                                                                 \
    result.m13 = lm2_neg_##scalar_suffix(                                                                                                                      \
        lm2_div_##scalar_suffix(lm2_add_##scalar_suffix(top, bottom), height));                                                                                \
    result.m23 = lm2_neg_##scalar_suffix(                                                                                                                      \
        lm2_div_##scalar_suffix(lm2_add_##scalar_suffix(far_plane, near_plane), depth));                                                                       \
    result.m33 = (scalar_type)1;                                                                                                                               \
    return result;                                                                                                                                             \
  }                                                                                                                                                            \
  LM2_API mat_type mat_type##_perspective(scalar_type fov_y, scalar_type aspect, scalar_type near_plane, scalar_type far_plane) {                              \
    LM2_ASSERT_UNSAFE(lm2_abs_##scalar_suffix(aspect) > (scalar_type)0.000001);                                                                                \
    LM2_ASSERT_UNSAFE(lm2_abs_##scalar_suffix(                                                                                                                 \
                          lm2_sub_##scalar_suffix(far_plane, near_plane)) > (scalar_type)0.000001);                                                            \
    scalar_type half_fov = lm2_mul_##scalar_suffix(fov_y, (scalar_type)0.5);                                                                                   \
    scalar_type f = lm2_div_##scalar_suffix((scalar_type)1,                                                                                                    \
                                            lm2_tan_##scalar_suffix(half_fov));                                                                                \
    scalar_type depth = lm2_sub_##scalar_suffix(far_plane, near_plane);                                                                                        \
    mat_type result = mat_type##_zero();                                                                                                                       \
    result.m00 = lm2_div_##scalar_suffix(f, aspect);                                                                                                           \
    result.m11 = f;                                                                                                                                            \
    result.m22 = lm2_div_##scalar_suffix(                                                                                                                      \
        lm2_neg_##scalar_suffix(lm2_add_##scalar_suffix(far_plane, near_plane)),                                                                               \
        depth);                                                                                                                                                \
    result.m23 = lm2_div_##scalar_suffix(                                                                                                                      \
        lm2_neg_##scalar_suffix(lm2_mul_##scalar_suffix(                                                                                                       \
            lm2_mul_##scalar_suffix((scalar_type)2, far_plane), near_plane)),                                                                                  \
        depth);                                                                                                                                                \
    result.m32 = (scalar_type) - 1;                                                                                                                            \
    return result;                                                                                                                                             \
  }                                                                                                                                                            \
  LM2_API mat_type mat_type##_look_at(vec3_type eye, vec3_type target, vec3_type up) {                                                                         \
    vec3_type z_axis = lm2_normalize_##vec3_type(lm2_sub_##vec3_type(eye, target));                                                                            \
    vec3_type x_axis = lm2_normalize_##vec3_type(lm2_cross_##vec3_type(up, z_axis));                                                                           \
    vec3_type y_axis = lm2_cross_##vec3_type(z_axis, x_axis);                                                                                                  \
    mat_type result;                                                                                                                                           \
    result.m00 = x_axis.x;                                                                                                                                     \
    result.m01 = x_axis.y;                                                                                                                                     \
    result.m02 = x_axis.z;                                                                                                                                     \
    result.m03 = lm2_neg_##scalar_suffix(lm2_dot_##vec3_type(x_axis, eye));                                                                                    \
    result.m10 = y_axis.x;                                                                                                                                     \
    result.m11 = y_axis.y;                                                                                                                                     \
    result.m12 = y_axis.z;                                                                                                                                     \
    result.m13 = lm2_neg_##scalar_suffix(lm2_dot_##vec3_type(y_axis, eye));                                                                                    \
    result.m20 = z_axis.x;                                                                                                                                     \
    result.m21 = z_axis.y;                                                                                                                                     \
    result.m22 = z_axis.z;                                                                                                                                     \
    result.m23 = lm2_neg_##scalar_suffix(lm2_dot_##vec3_type(z_axis, eye));                                                                                    \
    result.m30 = (scalar_type)0;                                                                                                                               \
    result.m31 = (scalar_type)0;                                                                                                                               \
    result.m32 = (scalar_type)0;                                                                                                                               \
    result.m33 = (scalar_type)1;                                                                                                                               \
    return result;                                                                                                                                             \
  }

// =============================================================================
// Matrix 4x4 Implementations
// =============================================================================

_LM2_IMPL_M4X4_BASIC(lm2_m4x4f64, double, f64)
_LM2_IMPL_M4X4_BASIC(lm2_m4x4f32, float, f32)

_LM2_IMPL_M4X4_TRANSFORM(lm2_m4x4f64, double, f64, lm2_v3f64)
_LM2_IMPL_M4X4_TRANSFORM(lm2_m4x4f32, float, f32, lm2_v3f32)

_LM2_IMPL_M4X4_MULTIPLY(lm2_m4x4f64, double, f64)
_LM2_IMPL_M4X4_MULTIPLY(lm2_m4x4f32, float, f32)

_LM2_IMPL_M4X4_OPS(lm2_m4x4f64, double, f64, lm2_v3f64, lm2_v4f64)
_LM2_IMPL_M4X4_OPS(lm2_m4x4f32, float, f32, lm2_v3f32, lm2_v4f32)

_LM2_IMPL_M4X4_GETTERS(lm2_m4x4f64, double, f64, lm2_v3f64)
_LM2_IMPL_M4X4_GETTERS(lm2_m4x4f32, float, f32, lm2_v3f32)

_LM2_IMPL_M4X4_PROJECTION(lm2_m4x4f64, double, f64, lm2_v3f64)
_LM2_IMPL_M4X4_PROJECTION(lm2_m4x4f32, float, f32, lm2_v3f32)
