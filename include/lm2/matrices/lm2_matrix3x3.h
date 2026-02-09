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
// Matrix 3x3 Function Declarations - f64
// =============================================================================

// Basic constructors
LM2_API lm2_m3x3f64 lm2_m3x3f64_identity(void);
LM2_API lm2_m3x3f64 lm2_m3x3f64_zero(void);
LM2_API lm2_m3x3f64 lm2_m3x3f64_make(double m00, double m01, double m02, double m10, double m11, double m12, double m20, double m21, double m22);

// Transformations
LM2_API lm2_m3x3f64 lm2_m3x3f64_scale(lm2_v2f64 scale);
LM2_API lm2_m3x3f64 lm2_m3x3f64_scale_uniform(double scale);
LM2_API lm2_m3x3f64 lm2_m3x3f64_translate(lm2_v2f64 translation);
LM2_API lm2_m3x3f64 lm2_m3x3f64_rotate(double angle);
LM2_API lm2_m3x3f64 lm2_m3x3f64_rotate_around_pivot(double angle, lm2_v2f64 pivot);
LM2_API lm2_m3x3f64 lm2_m3x3f64_scale_translate(lm2_v2f64 scale, lm2_v2f64 translation);

// Operations
LM2_API lm2_m3x3f64 lm2_m3x3f64_multiply(lm2_m3x3f64 a, lm2_m3x3f64 b);
LM2_API lm2_m3x3f64 lm2_m3x3f64_transpose(lm2_m3x3f64 m);
LM2_API lm2_m3x3f64 lm2_m3x3f64_inverse(lm2_m3x3f64 m);
LM2_API double lm2_m3x3f64_determinant(lm2_m3x3f64 m);
LM2_API double lm2_m3x3f64_trace(lm2_m3x3f64 m);
LM2_API lm2_v2f64 lm2_m3x3f64_transform_point(lm2_m3x3f64 m, lm2_v2f64 v);
LM2_API lm2_v2f64 lm2_m3x3f64_transform_vector(lm2_m3x3f64 m, lm2_v2f64 v);
LM2_API lm2_v3f64 lm2_m3x3f64_transform(lm2_m3x3f64 m, lm2_v3f64 v);
LM2_API void lm2_m3x3f64_transform_points(lm2_m3x3f64 m, lm2_v2f64* points, uint32_t count);
LM2_API void lm2_m3x3f64_transform_points_src_dst(lm2_m3x3f64 m, const lm2_v2f64* src, lm2_v2f64* dst, uint32_t count);

// Getters
LM2_API double lm2_m3x3f64_get_rotation(lm2_m3x3f64 m);
LM2_API lm2_v2f64 lm2_m3x3f64_get_scale(lm2_m3x3f64 m);
LM2_API lm2_v2f64 lm2_m3x3f64_get_translation(lm2_m3x3f64 m);

// =============================================================================
// Matrix 3x3 Function Declarations - f32
// =============================================================================

// Basic constructors
LM2_API lm2_m3x3f32 lm2_m3x3f32_identity(void);
LM2_API lm2_m3x3f32 lm2_m3x3f32_zero(void);
LM2_API lm2_m3x3f32 lm2_m3x3f32_make(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22);

// Transformations
LM2_API lm2_m3x3f32 lm2_m3x3f32_scale(lm2_v2f32 scale);
LM2_API lm2_m3x3f32 lm2_m3x3f32_scale_uniform(float scale);
LM2_API lm2_m3x3f32 lm2_m3x3f32_translate(lm2_v2f32 translation);
LM2_API lm2_m3x3f32 lm2_m3x3f32_rotate(float angle);
LM2_API lm2_m3x3f32 lm2_m3x3f32_rotate_around_pivot(float angle, lm2_v2f32 pivot);
LM2_API lm2_m3x3f32 lm2_m3x3f32_scale_translate(lm2_v2f32 scale, lm2_v2f32 translation);

// Operations
LM2_API lm2_m3x3f32 lm2_m3x3f32_multiply(lm2_m3x3f32 a, lm2_m3x3f32 b);
LM2_API lm2_m3x3f32 lm2_m3x3f32_transpose(lm2_m3x3f32 m);
LM2_API lm2_m3x3f32 lm2_m3x3f32_inverse(lm2_m3x3f32 m);
LM2_API float lm2_m3x3f32_determinant(lm2_m3x3f32 m);
LM2_API float lm2_m3x3f32_trace(lm2_m3x3f32 m);
LM2_API lm2_v2f32 lm2_m3x3f32_transform_point(lm2_m3x3f32 m, lm2_v2f32 v);
LM2_API lm2_v2f32 lm2_m3x3f32_transform_vector(lm2_m3x3f32 m, lm2_v2f32 v);
LM2_API lm2_v3f32 lm2_m3x3f32_transform(lm2_m3x3f32 m, lm2_v3f32 v);
LM2_API void lm2_m3x3f32_transform_points(lm2_m3x3f32 m, lm2_v2f32* points, uint32_t count);
LM2_API void lm2_m3x3f32_transform_points_src_dst(lm2_m3x3f32 m, const lm2_v2f32* src, lm2_v2f32* dst, uint32_t count);

// Getters
LM2_API float lm2_m3x3f32_get_rotation(lm2_m3x3f32 m);
LM2_API lm2_v2f32 lm2_m3x3f32_get_scale(lm2_m3x3f32 m);
LM2_API lm2_v2f32 lm2_m3x3f32_get_translation(lm2_m3x3f32 m);

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// C++ operator overloads (must be outside extern "C")
#if defined(__cplusplus) && !defined(LM2_NO_CPP_OPERATORS)
#  include "lm2_matrix_operators.h"
_LM2_DEFINE_M3X3_OPERATORS(lm2_m3x3f64, lm2_v2f64, lm2_v3f64)
_LM2_DEFINE_M3X3_OPERATORS(lm2_m3x3f32, lm2_v2f32, lm2_v3f32)
#endif
