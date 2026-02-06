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
// C++ Operator Overloads for Vector Types
// =============================================================================
// These operators provide natural syntax for vector operations in C++:
//   lm2_v3f32 a = {1, 2, 3};
//   lm2_v3f32 b = {4, 5, 6};
//   lm2_v3f32 c = a + b;       // vector + vector
//   lm2_v3f32 d = a * 2.0f;    // vector * scalar
//   lm2_v3f32 e = 2.0f * a;    // scalar * vector
//   float x = a[0];            // array access

// =============================================================================
// V2 Operators
// =============================================================================

#define _LM2_DEFINE_V2_OPERATORS(type_name, scalar_type)                         \
  inline type_name operator+(type_name a, type_name b) {                         \
    return lm2_add_##type_name(a, b);                                            \
  }                                                                              \
  inline type_name operator-(type_name a, type_name b) {                         \
    return lm2_sub_##type_name(a, b);                                            \
  }                                                                              \
  inline type_name operator*(type_name a, type_name b) {                         \
    return lm2_mul_##type_name(a, b);                                            \
  }                                                                              \
  inline type_name operator/(type_name a, type_name b) {                         \
    return lm2_div_##type_name(a, b);                                            \
  }                                                                              \
  inline type_name operator+(type_name a, scalar_type b) {                       \
    return lm2_add_##type_name##_##scalar_type(a, b);                            \
  }                                                                              \
  inline type_name operator-(type_name a, scalar_type b) {                       \
    return lm2_sub_##type_name##_##scalar_type(a, b);                            \
  }                                                                              \
  inline type_name operator*(type_name a, scalar_type b) {                       \
    return lm2_mul_##type_name##_##scalar_type(a, b);                            \
  }                                                                              \
  inline type_name operator/(type_name a, scalar_type b) {                       \
    return lm2_div_##type_name##_##scalar_type(a, b);                            \
  }                                                                              \
  inline type_name operator+(scalar_type a, type_name b) {                       \
    return lm2_add_##type_name##_##scalar_type(b, a);                            \
  }                                                                              \
  inline type_name operator-(scalar_type a, type_name b) {                       \
    return type_name{{(scalar_type)(a - b.e[0]), (scalar_type)(a - b.e[1])}};    \
  }                                                                              \
  inline type_name operator*(scalar_type a, type_name b) {                       \
    return lm2_mul_##type_name##_##scalar_type(b, a);                            \
  }                                                                              \
  inline type_name operator/(scalar_type a, type_name b) {                       \
    return type_name{{(scalar_type)(a / b.e[0]), (scalar_type)(a / b.e[1])}};    \
  }                                                                              \
  inline type_name operator+(type_name a) {                                      \
    return a;                                                                    \
  }                                                                              \
  inline type_name operator-(type_name a) {                                      \
    return lm2_neg_##type_name(a);                                               \
  }

// =============================================================================
// V3 Operators
// =============================================================================

#define _LM2_DEFINE_V3_OPERATORS(type_name, scalar_type)                         \
  inline type_name operator+(type_name a, type_name b) {                         \
    return lm2_add_##type_name(a, b);                                            \
  }                                                                              \
  inline type_name operator-(type_name a, type_name b) {                         \
    return lm2_sub_##type_name(a, b);                                            \
  }                                                                              \
  inline type_name operator*(type_name a, type_name b) {                         \
    return lm2_mul_##type_name(a, b);                                            \
  }                                                                              \
  inline type_name operator/(type_name a, type_name b) {                         \
    return lm2_div_##type_name(a, b);                                            \
  }                                                                              \
  inline type_name operator+(type_name a, scalar_type b) {                       \
    return lm2_add_##type_name##_##scalar_type(a, b);                            \
  }                                                                              \
  inline type_name operator-(type_name a, scalar_type b) {                       \
    return lm2_sub_##type_name##_##scalar_type(a, b);                            \
  }                                                                              \
  inline type_name operator*(type_name a, scalar_type b) {                       \
    return lm2_mul_##type_name##_##scalar_type(a, b);                            \
  }                                                                              \
  inline type_name operator/(type_name a, scalar_type b) {                       \
    return lm2_div_##type_name##_##scalar_type(a, b);                            \
  }                                                                              \
  inline type_name operator+(scalar_type a, type_name b) {                       \
    return lm2_add_##type_name##_##scalar_type(b, a);                            \
  }                                                                              \
  inline type_name operator-(scalar_type a, type_name b) {                       \
    return type_name{{(scalar_type)(a - b.e[0]), (scalar_type)(a - b.e[1]),      \
                      (scalar_type)(a - b.e[2])}};                               \
  }                                                                              \
  inline type_name operator*(scalar_type a, type_name b) {                       \
    return lm2_mul_##type_name##_##scalar_type(b, a);                            \
  }                                                                              \
  inline type_name operator/(scalar_type a, type_name b) {                       \
    return type_name{{(scalar_type)(a / b.e[0]), (scalar_type)(a / b.e[1]),      \
                      (scalar_type)(a / b.e[2])}};                               \
  }                                                                              \
  inline type_name operator+(type_name a) {                                      \
    return a;                                                                    \
  }                                                                              \
  inline type_name operator-(type_name a) {                                      \
    return lm2_neg_##type_name(a);                                               \
  }

// =============================================================================
// V4 Operators
// =============================================================================

#define _LM2_DEFINE_V4_OPERATORS(type_name, scalar_type)                         \
  inline type_name operator+(type_name a, type_name b) {                         \
    return lm2_add_##type_name(a, b);                                            \
  }                                                                              \
  inline type_name operator-(type_name a, type_name b) {                         \
    return lm2_sub_##type_name(a, b);                                            \
  }                                                                              \
  inline type_name operator*(type_name a, type_name b) {                         \
    return lm2_mul_##type_name(a, b);                                            \
  }                                                                              \
  inline type_name operator/(type_name a, type_name b) {                         \
    return lm2_div_##type_name(a, b);                                            \
  }                                                                              \
  inline type_name operator+(type_name a, scalar_type b) {                       \
    return lm2_add_##type_name##_##scalar_type(a, b);                            \
  }                                                                              \
  inline type_name operator-(type_name a, scalar_type b) {                       \
    return lm2_sub_##type_name##_##scalar_type(a, b);                            \
  }                                                                              \
  inline type_name operator*(type_name a, scalar_type b) {                       \
    return lm2_mul_##type_name##_##scalar_type(a, b);                            \
  }                                                                              \
  inline type_name operator/(type_name a, scalar_type b) {                       \
    return lm2_div_##type_name##_##scalar_type(a, b);                            \
  }                                                                              \
  inline type_name operator+(scalar_type a, type_name b) {                       \
    return lm2_add_##type_name##_##scalar_type(b, a);                            \
  }                                                                              \
  inline type_name operator-(scalar_type a, type_name b) {                       \
    return type_name{{(scalar_type)(a - b.e[0]), (scalar_type)(a - b.e[1]),      \
                      (scalar_type)(a - b.e[2]), (scalar_type)(a - b.e[3])}};    \
  }                                                                              \
  inline type_name operator*(scalar_type a, type_name b) {                       \
    return lm2_mul_##type_name##_##scalar_type(b, a);                            \
  }                                                                              \
  inline type_name operator/(scalar_type a, type_name b) {                       \
    return type_name{{(scalar_type)(a / b.e[0]), (scalar_type)(a / b.e[1]),      \
                      (scalar_type)(a / b.e[2]), (scalar_type)(a / b.e[3])}};    \
  }                                                                              \
  inline type_name operator+(type_name a) {                                      \
    return a;                                                                    \
  }                                                                              \
  inline type_name operator-(type_name a) {                                      \
    return lm2_neg_##type_name(a);                                               \
  }

#else

#define _LM2_DEFINE_V2_OPERATORS(type_name, scalar_type)
#define _LM2_DEFINE_V3_OPERATORS(type_name, scalar_type)
#define _LM2_DEFINE_V4_OPERATORS(type_name, scalar_type)

#endif
