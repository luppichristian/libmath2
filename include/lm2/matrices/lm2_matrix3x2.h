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
// Matrix 3x2 Function Declarations - f64
// =============================================================================

// Basic constructors
LM2_API lm2_m3x2f64 lm2_m3x2f64_identity(void);
LM2_API lm2_m3x2f64 lm2_m3x2f64_zero(void);
LM2_API lm2_m3x2f64 lm2_m3x2f64_make(double m00, double m01, double m02, double m10, double m11, double m12);

// Transformations
LM2_API lm2_m3x2f64 lm2_m3x2f64_scale(lm2_v2f64 scale);
LM2_API lm2_m3x2f64 lm2_m3x2f64_scale_uniform(double scale);
LM2_API lm2_m3x2f64 lm2_m3x2f64_translate(lm2_v2f64 translation);
LM2_API lm2_m3x2f64 lm2_m3x2f64_rotate(double angle);
LM2_API lm2_m3x2f64 lm2_m3x2f64_rotate_around_pivot(double angle, lm2_v2f64 pivot);
LM2_API lm2_m3x2f64 lm2_m3x2f64_scale_translate(lm2_v2f64 scale, lm2_v2f64 translation);
LM2_API lm2_m3x2f64 lm2_m3x2f64_world_transform(lm2_v2f64 translation, lm2_v2f64 scale, double rotation);

// Operations
LM2_API lm2_m3x2f64 lm2_m3x2f64_multiply(lm2_m3x2f64 a, lm2_m3x2f64 b);
LM2_API lm2_m3x2f64 lm2_m3x2f64_inverse(lm2_m3x2f64 m);
LM2_API double lm2_m3x2f64_determinant(lm2_m3x2f64 m);
LM2_API lm2_v2f64 lm2_m3x2f64_transform_point(lm2_m3x2f64 m, lm2_v2f64 v);
LM2_API lm2_v2f64 lm2_m3x2f64_transform_vector(lm2_m3x2f64 m, lm2_v2f64 v);
LM2_API void lm2_m3x2f64_transform_points(lm2_m3x2f64 m, lm2_v2f64* points, uint32_t count);
LM2_API void lm2_m3x2f64_transform_points_src_dst(lm2_m3x2f64 m, const lm2_v2f64* src, lm2_v2f64* dst, uint32_t count);

// Getters
LM2_API double lm2_m3x2f64_get_rotation(lm2_m3x2f64 m);
LM2_API lm2_v2f64 lm2_m3x2f64_get_scale(lm2_m3x2f64 m);
LM2_API lm2_v2f64 lm2_m3x2f64_get_translation(lm2_m3x2f64 m);

// Projection
LM2_API lm2_m3x2f64 lm2_m3x2f64_ortho(double left, double right, double bottom, double top);

// =============================================================================
// Matrix 3x2 Function Declarations - f32
// =============================================================================

// Basic constructors
LM2_API lm2_m3x2f32 lm2_m3x2f32_identity(void);
LM2_API lm2_m3x2f32 lm2_m3x2f32_zero(void);
LM2_API lm2_m3x2f32 lm2_m3x2f32_make(float m00, float m01, float m02, float m10, float m11, float m12);

// Transformations
LM2_API lm2_m3x2f32 lm2_m3x2f32_scale(lm2_v2f32 scale);
LM2_API lm2_m3x2f32 lm2_m3x2f32_scale_uniform(float scale);
LM2_API lm2_m3x2f32 lm2_m3x2f32_translate(lm2_v2f32 translation);
LM2_API lm2_m3x2f32 lm2_m3x2f32_rotate(float angle);
LM2_API lm2_m3x2f32 lm2_m3x2f32_rotate_around_pivot(float angle, lm2_v2f32 pivot);
LM2_API lm2_m3x2f32 lm2_m3x2f32_scale_translate(lm2_v2f32 scale, lm2_v2f32 translation);
LM2_API lm2_m3x2f32 lm2_m3x2f32_world_transform(lm2_v2f32 translation, lm2_v2f32 scale, float rotation);

// Operations
LM2_API lm2_m3x2f32 lm2_m3x2f32_multiply(lm2_m3x2f32 a, lm2_m3x2f32 b);
LM2_API lm2_m3x2f32 lm2_m3x2f32_inverse(lm2_m3x2f32 m);
LM2_API float lm2_m3x2f32_determinant(lm2_m3x2f32 m);
LM2_API lm2_v2f32 lm2_m3x2f32_transform_point(lm2_m3x2f32 m, lm2_v2f32 v);
LM2_API lm2_v2f32 lm2_m3x2f32_transform_vector(lm2_m3x2f32 m, lm2_v2f32 v);
LM2_API void lm2_m3x2f32_transform_points(lm2_m3x2f32 m, lm2_v2f32* points, uint32_t count);
LM2_API void lm2_m3x2f32_transform_points_src_dst(lm2_m3x2f32 m, const lm2_v2f32* src, lm2_v2f32* dst, uint32_t count);

// Getters
LM2_API float lm2_m3x2f32_get_rotation(lm2_m3x2f32 m);
LM2_API lm2_v2f32 lm2_m3x2f32_get_scale(lm2_m3x2f32 m);
LM2_API lm2_v2f32 lm2_m3x2f32_get_translation(lm2_m3x2f32 m);

// Projection
LM2_API lm2_m3x2f32 lm2_m3x2f32_ortho(float left, float right, float bottom, float top);

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// C++ operator overloads (must be outside extern "C")
#if defined(__cplusplus) && !defined(LM2_NO_CPP_OPERATORS)
#  include "lm2_matrix_operators.h"
_LM2_DEFINE_M3X2_OPERATORS(lm2_m3x2f64, lm2_v2f64)
_LM2_DEFINE_M3X2_OPERATORS(lm2_m3x2f32, lm2_v2f32)
#endif
