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
#include "lm2/misc/lm2_quaternion.h"
#include "lm2/vectors/lm2_vector3.h"
#include "lm2/vectors/lm2_vector4.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// Matrix 4x4 - 3D Transformation Matrix
// =============================================================================
// Represents a 4x4 matrix (row-major) for 3D transformations:
//   [m00 m01 m02 m03]
//   [m10 m11 m12 m13]
//   [m20 m21 m22 m23]
//   [m30 m31 m32 m33]
//
// STORAGE: Row-major. mRC = row R, column C. e[R*4+C].
//   e.g. m03 is row 0, column 3 (the X translation in a TRS matrix).
//
// MULTIPLICATION: M * v (column vector on the right).
//   result.x = m00*v.x + m01*v.y + m02*v.z + m03*v.w  (row 0 dot v)
//   result.w = m30*v.x + m31*v.y + m32*v.z + m33*v.w  (row 3 dot v)
//
// TRANSLATION: stored in column 3 (m03, m13, m23).
//   lm2_m4x4_translate produces: [1 0 0 tx / 0 1 0 ty / 0 0 1 tz / 0 0 0 1]
//
// PERSPECTIVE: m32 = -1 (perspective divide: w_clip = -z_view).
//   m22/m23 hold the depth mapping terms; m33 = 0.
//
// VIEW (look_at): rows are the camera's {right, up, -forward} basis vectors.
//   This is the inverse (transpose) of the camera's world rotation.
//   Extracting orientation via lm2_m4x4_to_quat_f64 from a view matrix yields
//   the conjugate of the camera's world orientation quaternion.
//
// Can represent: translation, rotation, scaling, projection, and combinations.
// Standard format for 3D graphics transformations.

// =============================================================================
// Matrix 4x4 Function Declarations - f64
// =============================================================================

typedef union lm2_m4x4_f64 {
  double e[16];  // Row-major: [m00, m01, m02, m03, m10, ...]
  struct {
    double m00, m01, m02, m03;  // First row
    double m10, m11, m12, m13;  // Second row
    double m20, m21, m22, m23;  // Third row
    double m30, m31, m32, m33;  // Fourth row
  };
  _LM2_SUBSCRIPT_OP(double, 16)
} lm2_m4x4_f64;

LM2_API lm2_m4x4_f64 lm2_m4x4_identity_f64(void);
LM2_API lm2_m4x4_f64 lm2_m4x4_zero_f64(void);
LM2_API lm2_m4x4_f64 lm2_m4x4_make_f64(double m00, double m01, double m02, double m03, double m10, double m11, double m12, double m13, double m20, double m21, double m22, double m23, double m30, double m31, double m32, double m33);
LM2_API lm2_m4x4_f64 lm2_m4x4_scale_f64(lm2_v3_f64 scale);
LM2_API lm2_m4x4_f64 lm2_m4x4_scale_uniform_f64(double scale);
LM2_API lm2_m4x4_f64 lm2_m4x4_translate_f64(lm2_v3_f64 translation);
LM2_API lm2_m4x4_f64 lm2_m4x4_rotate_x_f64(double angle);
LM2_API lm2_m4x4_f64 lm2_m4x4_rotate_y_f64(double angle);
LM2_API lm2_m4x4_f64 lm2_m4x4_rotate_z_f64(double angle);
LM2_API lm2_m4x4_f64 lm2_m4x4_rotate_axis_f64(lm2_v3_f64 axis, double angle);
LM2_API lm2_m4x4_f64 lm2_m4x4_scale_translate_f64(lm2_v3_f64 scale, lm2_v3_f64 translation);
LM2_API lm2_m4x4_f64 lm2_m4x4_world_transform_f64(lm2_v3_f64 translation, lm2_v3_f64 scale, lm2_v3_f64 rotation_euler);
LM2_API lm2_m4x4_f64 lm2_m4x4_multiply_f64(lm2_m4x4_f64 a, lm2_m4x4_f64 b);
LM2_API lm2_m4x4_f64 lm2_m4x4_transpose_f64(lm2_m4x4_f64 m);
LM2_API lm2_m4x4_f64 lm2_m4x4_inverse_f64(lm2_m4x4_f64 m);
LM2_API double lm2_m4x4_determinant_f64(lm2_m4x4_f64 m);
LM2_API double lm2_m4x4_trace_f64(lm2_m4x4_f64 m);
LM2_API lm2_v3_f64 lm2_m4x4_transform_point_f64(lm2_m4x4_f64 m, lm2_v3_f64 v);
LM2_API lm2_v3_f64 lm2_m4x4_transform_vector_f64(lm2_m4x4_f64 m, lm2_v3_f64 v);
LM2_API lm2_v4_f64 lm2_m4x4_transform_f64(lm2_m4x4_f64 m, lm2_v4_f64 v);
LM2_API void lm2_m4x4_transform_points_f64(lm2_m4x4_f64 m, lm2_v3_f64* points, uint32_t count);
LM2_API void lm2_m4x4_transform_points_src_dst_f64(lm2_m4x4_f64 m, const lm2_v3_f64* src, lm2_v3_f64* dst, uint32_t count);
LM2_API lm2_v3_f64 lm2_m4x4_get_scale_f64(lm2_m4x4_f64 m);
LM2_API lm2_v3_f64 lm2_m4x4_get_translation_f64(lm2_m4x4_f64 m);
LM2_API lm2_m4x4_f64 lm2_m4x4_ortho_f64(double left, double right, double bottom, double top, double near_plane, double far_plane);
LM2_API lm2_m4x4_f64 lm2_m4x4_perspective_f64(double fov_y, double aspect, double near_plane, double far_plane);
LM2_API lm2_m4x4_f64 lm2_m4x4_look_at_f64(lm2_v3_f64 eye, lm2_v3_f64 target, lm2_v3_f64 up);

// =============================================================================
// Matrix 4x4 Function Declarations - f32
// =============================================================================

typedef union lm2_m4x4_f32 {
  float e[16];  // Row-major: [m00, m01, m02, m03, m10, ...]
  struct {
    float m00, m01, m02, m03;  // First row
    float m10, m11, m12, m13;  // Second row
    float m20, m21, m22, m23;  // Third row
    float m30, m31, m32, m33;  // Fourth row
  };
  _LM2_SUBSCRIPT_OP(float, 16)
} lm2_m4x4_f32;

LM2_API lm2_m4x4_f32 lm2_m4x4_identity_f32(void);
LM2_API lm2_m4x4_f32 lm2_m4x4_zero_f32(void);
LM2_API lm2_m4x4_f32 lm2_m4x4_make_f32(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);
LM2_API lm2_m4x4_f32 lm2_m4x4_scale_f32(lm2_v3_f32 scale);
LM2_API lm2_m4x4_f32 lm2_m4x4_scale_uniform_f32(float scale);
LM2_API lm2_m4x4_f32 lm2_m4x4_translate_f32(lm2_v3_f32 translation);
LM2_API lm2_m4x4_f32 lm2_m4x4_rotate_x_f32(float angle);
LM2_API lm2_m4x4_f32 lm2_m4x4_rotate_y_f32(float angle);
LM2_API lm2_m4x4_f32 lm2_m4x4_rotate_z_f32(float angle);
LM2_API lm2_m4x4_f32 lm2_m4x4_rotate_axis_f32(lm2_v3_f32 axis, float angle);
LM2_API lm2_m4x4_f32 lm2_m4x4_scale_translate_f32(lm2_v3_f32 scale, lm2_v3_f32 translation);
LM2_API lm2_m4x4_f32 lm2_m4x4_world_transform_f32(lm2_v3_f32 translation, lm2_v3_f32 scale, lm2_v3_f32 rotation_euler);
LM2_API lm2_m4x4_f32 lm2_m4x4_multiply_f32(lm2_m4x4_f32 a, lm2_m4x4_f32 b);
LM2_API lm2_m4x4_f32 lm2_m4x4_transpose_f32(lm2_m4x4_f32 m);
LM2_API lm2_m4x4_f32 lm2_m4x4_inverse_f32(lm2_m4x4_f32 m);
LM2_API float lm2_m4x4_determinant_f32(lm2_m4x4_f32 m);
LM2_API float lm2_m4x4_trace_f32(lm2_m4x4_f32 m);
LM2_API lm2_v3_f32 lm2_m4x4_transform_point_f32(lm2_m4x4_f32 m, lm2_v3_f32 v);
LM2_API lm2_v3_f32 lm2_m4x4_transform_vector_f32(lm2_m4x4_f32 m, lm2_v3_f32 v);
LM2_API lm2_v4_f32 lm2_m4x4_transform_f32(lm2_m4x4_f32 m, lm2_v4_f32 v);
LM2_API void lm2_m4x4_transform_points_f32(lm2_m4x4_f32 m, lm2_v3_f32* points, uint32_t count);
LM2_API void lm2_m4x4_transform_points_src_dst_f32(lm2_m4x4_f32 m, const lm2_v3_f32* src, lm2_v3_f32* dst, uint32_t count);
LM2_API lm2_v3_f32 lm2_m4x4_get_scale_f32(lm2_m4x4_f32 m);
LM2_API lm2_v3_f32 lm2_m4x4_get_translation_f32(lm2_m4x4_f32 m);
LM2_API lm2_m4x4_f32 lm2_m4x4_ortho_f32(float left, float right, float bottom, float top, float near_plane, float far_plane);
LM2_API lm2_m4x4_f32 lm2_m4x4_perspective_f32(float fov_y, float aspect, float near_plane, float far_plane);
LM2_API lm2_m4x4_f32 lm2_m4x4_look_at_f32(lm2_v3_f32 eye, lm2_v3_f32 target, lm2_v3_f32 up);

// Quaternion conversions - f64
LM2_API lm2_m4x4_f64 lm2_m4x4_from_quat_f64(lm2_quat_f64 q);
LM2_API lm2_quat_f64 lm2_m4x4_to_quat_f64(lm2_m4x4_f64 m);

// Quaternion conversions - f32
LM2_API lm2_m4x4_f32 lm2_m4x4_from_quat_f32(lm2_quat_f32 q);
LM2_API lm2_quat_f32 lm2_m4x4_to_quat_f32(lm2_m4x4_f32 m);

// #############################################################################
LM2_HEADER_END;
// #############################################################################
