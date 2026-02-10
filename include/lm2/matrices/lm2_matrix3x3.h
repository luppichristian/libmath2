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

typedef union lm2_matrix3x3_f64 {
  double e[9];  // [m00, m01, m02, m10, m11, m12, m20, m21, m22]
  struct {
    double m00, m01, m02;  // First row
    double m10, m11, m12;  // Second row
    double m20, m21, m22;  // Third row
  };
  _LM2_SUBSCRIPT_OP(double, 9)
} lm2_matrix3x3_f64;

typedef union lm2_matrix3x3_f32 {
  float e[9];  // [m00, m01, m02, m10, m11, m12, m20, m21, m22]
  struct {
    float m00, m01, m02;  // First row
    float m10, m11, m12;  // Second row
    float m20, m21, m22;  // Third row
  };
  _LM2_SUBSCRIPT_OP(float, 9)
} lm2_matrix3x3_f32;

// Default type alias
typedef lm2_matrix3x3_f32 lm2_matrix3x3;

// =============================================================================
// Matrix 3x3 Function Declarations - f64
// =============================================================================

// Basic constructors
LM2_API lm2_matrix3x3_f64 lm2_m3x3_identity_f64(void);
LM2_API lm2_matrix3x3_f64 lm2_m3x3_zero_f64(void);
LM2_API lm2_matrix3x3_f64 lm2_m3x3_make_f64(double m00, double m01, double m02, double m10, double m11, double m12, double m20, double m21, double m22);

// Transformations
LM2_API lm2_matrix3x3_f64 lm2_m3x3_scale_f64(lm2_v2_f64 scale);
LM2_API lm2_matrix3x3_f64 lm2_m3x3_scale_uniform_f64(double scale);
LM2_API lm2_matrix3x3_f64 lm2_m3x3_translate_f64(lm2_v2_f64 translation);
LM2_API lm2_matrix3x3_f64 lm2_m3x3_rotate_f64(double angle);
LM2_API lm2_matrix3x3_f64 lm2_m3x3_rotate_around_pivot_f64(double angle, lm2_v2_f64 pivot);
LM2_API lm2_matrix3x3_f64 lm2_m3x3_scale_translate_f64(lm2_v2_f64 scale, lm2_v2_f64 translation);

// Operations
LM2_API lm2_matrix3x3_f64 lm2_m3x3_multiply_f64(lm2_matrix3x3_f64 a, lm2_matrix3x3_f64 b);
LM2_API lm2_matrix3x3_f64 lm2_m3x3_transpose_f64(lm2_matrix3x3_f64 m);
LM2_API lm2_matrix3x3_f64 lm2_m3x3_inverse_f64(lm2_matrix3x3_f64 m);
LM2_API double lm2_m3x3_determinant_f64(lm2_matrix3x3_f64 m);
LM2_API double lm2_m3x3_trace_f64(lm2_matrix3x3_f64 m);
LM2_API lm2_v2_f64 lm2_m3x3_transform_point_f64(lm2_matrix3x3_f64 m, lm2_v2_f64 v);
LM2_API lm2_v2_f64 lm2_m3x3_transform_vector_f64(lm2_matrix3x3_f64 m, lm2_v2_f64 v);
LM2_API lm2_v3_f64 lm2_m3x3_transform_f64(lm2_matrix3x3_f64 m, lm2_v3_f64 v);
LM2_API void lm2_m3x3_transform_points_f64(lm2_matrix3x3_f64 m, lm2_v2_f64* points, uint32_t count);
LM2_API void lm2_m3x3_transform_points_src_dst_f64(lm2_matrix3x3_f64 m, const lm2_v2_f64* src, lm2_v2_f64* dst, uint32_t count);

// Getters
LM2_API double lm2_m3x3_get_rotation_f64(lm2_matrix3x3_f64 m);
LM2_API lm2_v2_f64 lm2_m3x3_get_scale_f64(lm2_matrix3x3_f64 m);
LM2_API lm2_v2_f64 lm2_m3x3_get_translation_f64(lm2_matrix3x3_f64 m);

// =============================================================================
// Matrix 3x3 Function Declarations - f32
// =============================================================================

// Basic constructors
LM2_API lm2_matrix3x3_f32 lm2_m3x3_identity_f32(void);
LM2_API lm2_matrix3x3_f32 lm2_m3x3_zero_f32(void);
LM2_API lm2_matrix3x3_f32 lm2_m3x3_make_f32(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22);

// Transformations
LM2_API lm2_matrix3x3_f32 lm2_m3x3_scale_f32(lm2_v2_f32 scale);
LM2_API lm2_matrix3x3_f32 lm2_m3x3_scale_uniform_f32(float scale);
LM2_API lm2_matrix3x3_f32 lm2_m3x3_translate_f32(lm2_v2_f32 translation);
LM2_API lm2_matrix3x3_f32 lm2_m3x3_rotate_f32(float angle);
LM2_API lm2_matrix3x3_f32 lm2_m3x3_rotate_around_pivot_f32(float angle, lm2_v2_f32 pivot);
LM2_API lm2_matrix3x3_f32 lm2_m3x3_scale_translate_f32(lm2_v2_f32 scale, lm2_v2_f32 translation);

// Operations
LM2_API lm2_matrix3x3_f32 lm2_m3x3_multiply_f32(lm2_matrix3x3_f32 a, lm2_matrix3x3_f32 b);
LM2_API lm2_matrix3x3_f32 lm2_m3x3_transpose_f32(lm2_matrix3x3_f32 m);
LM2_API lm2_matrix3x3_f32 lm2_m3x3_inverse_f32(lm2_matrix3x3_f32 m);
LM2_API float lm2_m3x3_determinant_f32(lm2_matrix3x3_f32 m);
LM2_API float lm2_m3x3_trace_f32(lm2_matrix3x3_f32 m);
LM2_API lm2_v2_f32 lm2_m3x3_transform_point_f32(lm2_matrix3x3_f32 m, lm2_v2_f32 v);
LM2_API lm2_v2_f32 lm2_m3x3_transform_vector_f32(lm2_matrix3x3_f32 m, lm2_v2_f32 v);
LM2_API lm2_v3_f32 lm2_m3x3_transform_f32(lm2_matrix3x3_f32 m, lm2_v3_f32 v);
LM2_API void lm2_m3x3_transform_points_f32(lm2_matrix3x3_f32 m, lm2_v2_f32* points, uint32_t count);
LM2_API void lm2_m3x3_transform_points_src_dst_f32(lm2_matrix3x3_f32 m, const lm2_v2_f32* src, lm2_v2_f32* dst, uint32_t count);

// Getters
LM2_API float lm2_m3x3_get_rotation_f32(lm2_matrix3x3_f32 m);
LM2_API lm2_v2_f32 lm2_m3x3_get_scale_f32(lm2_matrix3x3_f32 m);
LM2_API lm2_v2_f32 lm2_m3x3_get_translation_f32(lm2_matrix3x3_f32 m);

// #############################################################################
LM2_HEADER_END;
// #############################################################################