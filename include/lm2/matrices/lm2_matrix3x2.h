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

#include "lm2/lm2_base.h"
#include "lm2/vectors/lm2_vector2.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// Matrix 3x2 - 2D Affine Transformation Matrix
// =============================================================================
// Represents a 2D affine transformation in augmented form:
//   [m00 m01 m02]   [a  c  tx]
//   [m10 m11 m12] = [b  d  ty]
//   [ 0   0   1 ]   [0  0  1 ] (implicit)
//
// Can represent: translation, rotation, scaling, shearing, and combinations.
// Efficient for 2D transformations (only stores 6 values vs 9 for full 3x3).

typedef union lm2_m3x2f64 {
  double m[6];  // [m00, m01, m02, m10, m11, m12]
  struct {
    double m00, m01, m02;  // First row: [a, c, tx]
    double m10, m11, m12;  // Second row: [b, d, ty]
  };
  struct {
    double a, c, tx;  // Alternative names
    double b, d, ty;
  };
#if defined(__cplusplus) && !defined(LM2_NO_CPP_OPERATORS)
  inline double& operator[](int i) { return m[i]; }
  inline const double& operator[](int i) const { return m[i]; }
#endif
} lm2_m3x2f64;

typedef union lm2_m3x2f32 {
  float m[6];  // [m00, m01, m02, m10, m11, m12]
  struct {
    float m00, m01, m02;  // First row: [a, c, tx]
    float m10, m11, m12;  // Second row: [b, d, ty]
  };
  struct {
    float a, c, tx;  // Alternative names
    float b, d, ty;
  };
#if defined(__cplusplus) && !defined(LM2_NO_CPP_OPERATORS)
  inline float& operator[](int i) { return m[i]; }
  inline const float& operator[](int i) const { return m[i]; }
#endif
} lm2_m3x2f32;

// Default type alias
typedef lm2_m3x2f32 lm2_m3x2;

// =============================================================================
// Helper Macros for Declarations
// =============================================================================

#define _LM2_DECLARE_M3X2_BASIC(mat_type, scalar_type, vec_type) \
  LM2_API mat_type mat_type##_identity(void);                    \
  LM2_API mat_type mat_type##_zero(void);                        \
  LM2_API mat_type mat_type##_make(scalar_type m00, scalar_type m01, scalar_type m02, scalar_type m10, scalar_type m11, scalar_type m12);

#define _LM2_DECLARE_M3X2_TRANSFORM(mat_type, scalar_type, vec_type)                  \
  LM2_API mat_type mat_type##_scale(vec_type scale);                                  \
  LM2_API mat_type mat_type##_scale_uniform(scalar_type scale);                       \
  LM2_API mat_type mat_type##_translate(vec_type translation);                        \
  LM2_API mat_type mat_type##_rotate(scalar_type angle);                              \
  LM2_API mat_type mat_type##_rotate_around_pivot(scalar_type angle, vec_type pivot); \
  LM2_API mat_type mat_type##_scale_translate(vec_type scale, vec_type translation);  \
  LM2_API mat_type mat_type##_world_transform(vec_type translation, vec_type scale, scalar_type rotation);

#define _LM2_DECLARE_M3X2_OPS(mat_type, scalar_type, vec_type)                            \
  LM2_API mat_type mat_type##_multiply(mat_type a, mat_type b);                           \
  LM2_API mat_type mat_type##_inverse(mat_type m);                                        \
  LM2_API scalar_type mat_type##_determinant(mat_type m);                                 \
  LM2_API vec_type mat_type##_transform_point(mat_type m, vec_type v);                    \
  LM2_API vec_type mat_type##_transform_vector(mat_type m, vec_type v);                   \
  LM2_API void mat_type##_transform_points(mat_type m, vec_type* points, uint32_t count); \
  LM2_API void mat_type##_transform_points_src_dst(mat_type m, const vec_type* src, vec_type* dst, uint32_t count);

#define _LM2_DECLARE_M3X2_GETTERS(mat_type, scalar_type, vec_type) \
  LM2_API scalar_type mat_type##_get_rotation(mat_type m);         \
  LM2_API vec_type mat_type##_get_scale(mat_type m);               \
  LM2_API vec_type mat_type##_get_translation(mat_type m);

#define _LM2_DECLARE_M3X2_PROJECTION(mat_type, scalar_type) \
  LM2_API mat_type mat_type##_ortho(scalar_type left, scalar_type right, scalar_type bottom, scalar_type top);

// =============================================================================
// Matrix 3x2 Function Declarations
// =============================================================================

_LM2_DECLARE_M3X2_BASIC(lm2_m3x2f64, double, lm2_v2f64)
_LM2_DECLARE_M3X2_BASIC(lm2_m3x2f32, float, lm2_v2f32)

_LM2_DECLARE_M3X2_TRANSFORM(lm2_m3x2f64, double, lm2_v2f64)
_LM2_DECLARE_M3X2_TRANSFORM(lm2_m3x2f32, float, lm2_v2f32)

_LM2_DECLARE_M3X2_OPS(lm2_m3x2f64, double, lm2_v2f64)
_LM2_DECLARE_M3X2_OPS(lm2_m3x2f32, float, lm2_v2f32)

_LM2_DECLARE_M3X2_GETTERS(lm2_m3x2f64, double, lm2_v2f64)
_LM2_DECLARE_M3X2_GETTERS(lm2_m3x2f32, float, lm2_v2f32)

_LM2_DECLARE_M3X2_PROJECTION(lm2_m3x2f64, double)
_LM2_DECLARE_M3X2_PROJECTION(lm2_m3x2f32, float)

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// C++ operator overloads (must be outside extern "C")
#ifndef LM2_NO_CPP_OPERATORS
#  include "lm2_matrix_operators.h"
_LM2_DEFINE_M3X2_OPERATORS(lm2_m3x2f64, lm2_v2f64)
_LM2_DEFINE_M3X2_OPERATORS(lm2_m3x2f32, lm2_v2f32)
#endif
