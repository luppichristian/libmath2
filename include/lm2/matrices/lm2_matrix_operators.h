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

#pragma once

#if defined(__cplusplus) && !defined(LM2_NO_CPP_OPERATORS)

// =============================================================================
// C++ Operator Overloads for Matrix Types
// =============================================================================
// These operators provide natural syntax for matrix operations in C++:
//   lm2_m3x2f32 a = lm2_m3x2f32_identity();
//   lm2_m3x2f32 b = lm2_m3x2f32_scale({2.0f, 2.0f});
//   lm2_m3x2f32 c = a * b;            // matrix * matrix
//   lm2_v2f32 v = {1.0f, 2.0f};
//   lm2_v2f32 u = v * a;              // vector * matrix

// =============================================================================
// Matrix 3x2 Operators
// =============================================================================

#  define _LM2_DEFINE_M3X2_OPERATORS(mat_type, vec_type)   \
    inline mat_type operator*(mat_type a, mat_type b) {    \
      return mat_type##_multiply(a, b);                    \
    }                                                      \
    inline mat_type& operator*=(mat_type& a, mat_type b) { \
      a = mat_type##_multiply(a, b);                       \
      return a;                                            \
    }                                                      \
    inline vec_type operator*(vec_type v, mat_type m) {    \
      return mat_type##_transform_point(m, v);             \
    }                                                      \
    inline vec_type& operator*=(vec_type& v, mat_type m) { \
      v = mat_type##_transform_point(m, v);                \
      return v;                                            \
    }

// =============================================================================
// Matrix 3x3 Operators
// =============================================================================

#  define _LM2_DEFINE_M3X3_OPERATORS(mat_type, vec2_type, vec3_type) \
    inline mat_type operator*(mat_type a, mat_type b) {              \
      return mat_type##_multiply(a, b);                              \
    }                                                                \
    inline mat_type& operator*=(mat_type& a, mat_type b) {           \
      a = mat_type##_multiply(a, b);                                 \
      return a;                                                      \
    }                                                                \
    inline vec2_type operator*(vec2_type v, mat_type m) {            \
      return mat_type##_transform_point(m, v);                       \
    }                                                                \
    inline vec2_type& operator*=(vec2_type& v, mat_type m) {         \
      v = mat_type##_transform_point(m, v);                          \
      return v;                                                      \
    }                                                                \
    inline vec3_type operator*(vec3_type v, mat_type m) {            \
      return mat_type##_transform(m, v);                             \
    }                                                                \
    inline vec3_type& operator*=(vec3_type& v, mat_type m) {         \
      v = mat_type##_transform(m, v);                                \
      return v;                                                      \
    }

// =============================================================================
// Matrix 4x4 Operators
// =============================================================================

#  define _LM2_DEFINE_M4X4_OPERATORS(mat_type, vec3_type, vec4_type) \
    inline mat_type operator*(mat_type a, mat_type b) {              \
      return mat_type##_multiply(a, b);                              \
    }                                                                \
    inline mat_type& operator*=(mat_type& a, mat_type b) {           \
      a = mat_type##_multiply(a, b);                                 \
      return a;                                                      \
    }                                                                \
    inline vec3_type operator*(vec3_type v, mat_type m) {            \
      return mat_type##_transform_point(m, v);                       \
    }                                                                \
    inline vec3_type& operator*=(vec3_type& v, mat_type m) {         \
      v = mat_type##_transform_point(m, v);                          \
      return v;                                                      \
    }                                                                \
    inline vec4_type operator*(vec4_type v, mat_type m) {            \
      return mat_type##_transform(m, v);                             \
    }                                                                \
    inline vec4_type& operator*=(vec4_type& v, mat_type m) {         \
      v = mat_type##_transform(m, v);                                \
      return v;                                                      \
    }

#endif  // __cplusplus && !LM2_NO_CPP_OPERATORS
