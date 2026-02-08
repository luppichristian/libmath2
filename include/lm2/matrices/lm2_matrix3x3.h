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
#include "lm2/vectors/lm2_vector3.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// Matrix 3x3 - General 3x3 Matrix
// =============================================================================
// Represents a 3x3 matrix (row-major):
//   [m00 m01 m02]
//   [m10 m11 m12]
//   [m20 m21 m22]
//
// Can represent: 2D homogeneous transformations (including projective),
// 3D rotations (around axes), and general 3x3 linear transformations.

typedef union lm2_m3x3f64 {
  double m[9];  // [m00, m01, m02, m10, m11, m12, m20, m21, m22]
  struct {
    double m00, m01, m02;  // First row
    double m10, m11, m12;  // Second row
    double m20, m21, m22;  // Third row
  };
#if defined(__cplusplus) && !defined(LM2_NO_CPP_OPERATORS)
  inline double& operator[](int i) { return m[i]; }
  inline const double& operator[](int i) const { return m[i]; }
#endif
} lm2_m3x3f64;

typedef union lm2_m3x3f32 {
  float m[9];  // [m00, m01, m02, m10, m11, m12, m20, m21, m22]
  struct {
    float m00, m01, m02;  // First row
    float m10, m11, m12;  // Second row
    float m20, m21, m22;  // Third row
  };
#if defined(__cplusplus) && !defined(LM2_NO_CPP_OPERATORS)
  inline float& operator[](int i) { return m[i]; }
  inline const float& operator[](int i) const { return m[i]; }
#endif
} lm2_m3x3f32;

// Default type alias
typedef lm2_m3x3f32 lm2_m3x3;

// =============================================================================
// Helper Macros for Declarations
// =============================================================================

#define _LM2_DECLARE_M3X3_BASIC(mat_type, scalar_type) \
  LM2_API mat_type mat_type##_identity(void);          \
  LM2_API mat_type mat_type##_zero(void);              \
  LM2_API mat_type mat_type##_make(scalar_type m00, scalar_type m01, scalar_type m02, scalar_type m10, scalar_type m11, scalar_type m12, scalar_type m20, scalar_type m21, scalar_type m22);

#define _LM2_DECLARE_M3X3_TRANSFORM(mat_type, scalar_type, vec2_type)                  \
  LM2_API mat_type mat_type##_scale(vec2_type scale);                                  \
  LM2_API mat_type mat_type##_scale_uniform(scalar_type scale);                        \
  LM2_API mat_type mat_type##_translate(vec2_type translation);                        \
  LM2_API mat_type mat_type##_rotate(scalar_type angle);                               \
  LM2_API mat_type mat_type##_rotate_around_pivot(scalar_type angle, vec2_type pivot); \
  LM2_API mat_type mat_type##_scale_translate(vec2_type scale, vec2_type translation);

#define _LM2_DECLARE_M3X3_OPS(mat_type, scalar_type, vec2_type, vec3_type)                 \
  LM2_API mat_type mat_type##_multiply(mat_type a, mat_type b);                            \
  LM2_API mat_type mat_type##_transpose(mat_type m);                                       \
  LM2_API mat_type mat_type##_inverse(mat_type m);                                         \
  LM2_API scalar_type mat_type##_determinant(mat_type m);                                  \
  LM2_API scalar_type mat_type##_trace(mat_type m);                                        \
  LM2_API vec2_type mat_type##_transform_point(mat_type m, vec2_type v);                   \
  LM2_API vec2_type mat_type##_transform_vector(mat_type m, vec2_type v);                  \
  LM2_API vec3_type mat_type##_transform(mat_type m, vec3_type v);                         \
  LM2_API void mat_type##_transform_points(mat_type m, vec2_type* points, uint32_t count); \
  LM2_API void mat_type##_transform_points_src_dst(mat_type m, const vec2_type* src, vec2_type* dst, uint32_t count);

#define _LM2_DECLARE_M3X3_GETTERS(mat_type, scalar_type, vec2_type) \
  LM2_API scalar_type mat_type##_get_rotation(mat_type m);          \
  LM2_API vec2_type mat_type##_get_scale(mat_type m);               \
  LM2_API vec2_type mat_type##_get_translation(mat_type m);

// =============================================================================
// Matrix 3x3 Function Declarations
// =============================================================================

_LM2_DECLARE_M3X3_BASIC(lm2_m3x3f64, double)
_LM2_DECLARE_M3X3_BASIC(lm2_m3x3f32, float)

_LM2_DECLARE_M3X3_TRANSFORM(lm2_m3x3f64, double, lm2_v2f64)
_LM2_DECLARE_M3X3_TRANSFORM(lm2_m3x3f32, float, lm2_v2f32)

_LM2_DECLARE_M3X3_OPS(lm2_m3x3f64, double, lm2_v2f64, lm2_v3f64)
_LM2_DECLARE_M3X3_OPS(lm2_m3x3f32, float, lm2_v2f32, lm2_v3f32)

_LM2_DECLARE_M3X3_GETTERS(lm2_m3x3f64, double, lm2_v2f64)
_LM2_DECLARE_M3X3_GETTERS(lm2_m3x3f32, float, lm2_v2f32)

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// C++ operator overloads (must be outside extern "C")
#ifndef LM2_NO_CPP_OPERATORS
#  include "lm2_matrix_operators.h"
_LM2_DEFINE_M3X3_OPERATORS(lm2_m3x3f64, lm2_v2f64, lm2_v3f64)
_LM2_DEFINE_M3X3_OPERATORS(lm2_m3x3f32, lm2_v2f32, lm2_v3f32)
#endif
