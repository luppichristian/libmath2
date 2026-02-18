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
//   [ 0   0   1 ]   [0  0  1 ] (implicit third row, never stored)
//
// STORAGE: Row-major, 6 elements. mRC = row R, column C. e[R*3+C].
//   Alternative field names: a=m00, c=m01, tx=m02, b=m10, d=m11, ty=m12.
//
// MULTIPLICATION: M * v (column vector on the right), implicit w=1 for points.
//   result.x = m00*v.x + m01*v.y + m02   (point, row 0 dot [v 1])
//   result.y = m10*v.x + m11*v.y + m12
//   For vectors (w=0): translation (m02, m12) is ignored.
//
// TRANSLATION: stored in column 2 (m02=tx, m12=ty).
//   lm2_m3x2_translate produces: [1 0 tx / 0 1 ty]
//
// 2D ROTATION: CCW by angle θ:
//   [cos θ  -sin θ  0]
//   [sin θ   cos θ  0]
//
// COMPOSITION: lm2_m3x2_multiply(A, B) applies B first, then A (A*B).
//   To build TRS: multiply(translate, multiply(rotate, scale)).
//
// Can represent: translation, rotation, scaling, shearing, and combinations.
// Efficient for 2D transformations (only stores 6 values vs 9 for full 3x3).

// =============================================================================
// Matrix 3x2 Function Declarations - f64
// =============================================================================

typedef union lm2_m3x2_f64 {
  double e[6];  // [m00, m01, m02, m10, m11, m12]
  struct {
    double m00, m01, m02;  // First row: [a, c, tx]
    double m10, m11, m12;  // Second row: [b, d, ty]
  };
  struct {
    double a, c, tx;  // Alternative names
    double b, d, ty;
  };
  _LM2_SUBSCRIPT_OP(double, 6)
} lm2_m3x2_f64;

LM2_API lm2_m3x2_f64 lm2_m3x2_identity_f64(void);
LM2_API lm2_m3x2_f64 lm2_m3x2_zero_f64(void);
LM2_API lm2_m3x2_f64 lm2_m3x2_make_f64(double m00, double m01, double m02, double m10, double m11, double m12);
LM2_API lm2_m3x2_f64 lm2_m3x2_scale_f64(lm2_v2_f64 scale);
LM2_API lm2_m3x2_f64 lm2_m3x2_scale_uniform_f64(double scale);
LM2_API lm2_m3x2_f64 lm2_m3x2_translate_f64(lm2_v2_f64 translation);
LM2_API lm2_m3x2_f64 lm2_m3x2_rotate_f64(double angle);
LM2_API lm2_m3x2_f64 lm2_m3x2_rotate_around_pivot_f64(double angle, lm2_v2_f64 pivot);
LM2_API lm2_m3x2_f64 lm2_m3x2_scale_translate_f64(lm2_v2_f64 scale, lm2_v2_f64 translation);
LM2_API lm2_m3x2_f64 lm2_m3x2_world_transform_f64(lm2_v2_f64 translation, lm2_v2_f64 scale, double rotation);
LM2_API lm2_m3x2_f64 lm2_m3x2_multiply_f64(lm2_m3x2_f64 a, lm2_m3x2_f64 b);
LM2_API lm2_m3x2_f64 lm2_m3x2_inverse_f64(lm2_m3x2_f64 m);
LM2_API double lm2_m3x2_determinant_f64(lm2_m3x2_f64 m);
LM2_API lm2_v2_f64 lm2_m3x2_transform_point_f64(lm2_m3x2_f64 m, lm2_v2_f64 v);
LM2_API lm2_v2_f64 lm2_m3x2_transform_vector_f64(lm2_m3x2_f64 m, lm2_v2_f64 v);
LM2_API void lm2_m3x2_transform_points_f64(lm2_m3x2_f64 m, lm2_v2_f64* points, uint32_t count);
LM2_API void lm2_m3x2_transform_points_src_dst_f64(lm2_m3x2_f64 m, const lm2_v2_f64* src, lm2_v2_f64* dst, uint32_t count);
LM2_API double lm2_m3x2_get_rotation_f64(lm2_m3x2_f64 m);
LM2_API lm2_v2_f64 lm2_m3x2_get_scale_f64(lm2_m3x2_f64 m);
LM2_API lm2_v2_f64 lm2_m3x2_get_translation_f64(lm2_m3x2_f64 m);
LM2_API lm2_m3x2_f64 lm2_m3x2_ortho_f64(double left, double right, double bottom, double top);

// =============================================================================
// Matrix 3x2 Function Declarations - f32
// =============================================================================

typedef union lm2_m3x2_f32 {
  float e[6];  // [m00, m01, m02, m10, m11, m12]
  struct {
    float m00, m01, m02;  // First row: [a, c, tx]
    float m10, m11, m12;  // Second row: [b, d, ty]
  };
  struct {
    float a, c, tx;  // Alternative names
    float b, d, ty;
  };
  _LM2_SUBSCRIPT_OP(float, 6)
} lm2_m3x2_f32;

LM2_API lm2_m3x2_f32 lm2_m3x2_identity_f32(void);
LM2_API lm2_m3x2_f32 lm2_m3x2_zero_f32(void);
LM2_API lm2_m3x2_f32 lm2_m3x2_make_f32(float m00, float m01, float m02, float m10, float m11, float m12);
LM2_API lm2_m3x2_f32 lm2_m3x2_scale_f32(lm2_v2_f32 scale);
LM2_API lm2_m3x2_f32 lm2_m3x2_scale_uniform_f32(float scale);
LM2_API lm2_m3x2_f32 lm2_m3x2_translate_f32(lm2_v2_f32 translation);
LM2_API lm2_m3x2_f32 lm2_m3x2_rotate_f32(float angle);
LM2_API lm2_m3x2_f32 lm2_m3x2_rotate_around_pivot_f32(float angle, lm2_v2_f32 pivot);
LM2_API lm2_m3x2_f32 lm2_m3x2_scale_translate_f32(lm2_v2_f32 scale, lm2_v2_f32 translation);
LM2_API lm2_m3x2_f32 lm2_m3x2_world_transform_f32(lm2_v2_f32 translation, lm2_v2_f32 scale, float rotation);
LM2_API lm2_m3x2_f32 lm2_m3x2_multiply_f32(lm2_m3x2_f32 a, lm2_m3x2_f32 b);
LM2_API lm2_m3x2_f32 lm2_m3x2_inverse_f32(lm2_m3x2_f32 m);
LM2_API float lm2_m3x2_determinant_f32(lm2_m3x2_f32 m);
LM2_API lm2_v2_f32 lm2_m3x2_transform_point_f32(lm2_m3x2_f32 m, lm2_v2_f32 v);
LM2_API lm2_v2_f32 lm2_m3x2_transform_vector_f32(lm2_m3x2_f32 m, lm2_v2_f32 v);
LM2_API void lm2_m3x2_transform_points_f32(lm2_m3x2_f32 m, lm2_v2_f32* points, uint32_t count);
LM2_API void lm2_m3x2_transform_points_src_dst_f32(lm2_m3x2_f32 m, const lm2_v2_f32* src, lm2_v2_f32* dst, uint32_t count);
LM2_API float lm2_m3x2_get_rotation_f32(lm2_m3x2_f32 m);
LM2_API lm2_v2_f32 lm2_m3x2_get_scale_f32(lm2_m3x2_f32 m);
LM2_API lm2_v2_f32 lm2_m3x2_get_translation_f32(lm2_m3x2_f32 m);
LM2_API lm2_m3x2_f32 lm2_m3x2_ortho_f32(float left, float right, float bottom, float top);

// Default type alias
typedef lm2_m3x2_f32 lm2_m3x2;

// #############################################################################
LM2_HEADER_END;
// #############################################################################
