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
#include "lm2/vectors/lm2_vector3.h"
#include "lm2/vectors/lm2_vector4.h"

// Forward declare quaternion types
typedef union lm2_quat_f64 lm2_quat_f64;
typedef union lm2_quat_f32 lm2_quat_f32;

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
// Can represent: translation, rotation, scaling, projection, and combinations.
// Standard format for 3D graphics transformations.

typedef union lm2_matrix4x4_f64 {
  double e[16];  // Row-major: [m00, m01, m02, m03, m10, ...]
  struct {
    double m00, m01, m02, m03;  // First row
    double m10, m11, m12, m13;  // Second row
    double m20, m21, m22, m23;  // Third row
    double m30, m31, m32, m33;  // Fourth row
  };
  _LM2_SUBSCRIPT_OP(double, 16)
} lm2_matrix4x4_f64;

typedef union lm2_matrix4x4_f32 {
  float e[16];  // Row-major: [m00, m01, m02, m03, m10, ...]
  struct {
    float m00, m01, m02, m03;  // First row
    float m10, m11, m12, m13;  // Second row
    float m20, m21, m22, m23;  // Third row
    float m30, m31, m32, m33;  // Fourth row
  };
  _LM2_SUBSCRIPT_OP(float, 16)
} lm2_matrix4x4_f32;

// Default type alias
typedef lm2_matrix4x4_f32 lm2_matrix4x4;

// =============================================================================
// Matrix 4x4 Function Declarations - f64
// =============================================================================

// Basic constructors
LM2_API lm2_matrix4x4_f64 lm2_m4x4_identity_f64(void);
LM2_API lm2_matrix4x4_f64 lm2_m4x4_zero_f64(void);
LM2_API lm2_matrix4x4_f64 lm2_m4x4_make_f64(double m00, double m01, double m02, double m03, double m10, double m11, double m12, double m13, double m20, double m21, double m22, double m23, double m30, double m31, double m32, double m33);

// Transformations
LM2_API lm2_matrix4x4_f64 lm2_m4x4_scale_f64(lm2_v3_f64 scale);
LM2_API lm2_matrix4x4_f64 lm2_m4x4_scale_uniform_f64(double scale);
LM2_API lm2_matrix4x4_f64 lm2_m4x4_translate_f64(lm2_v3_f64 translation);
LM2_API lm2_matrix4x4_f64 lm2_m4x4_rotate_x_f64(double angle);
LM2_API lm2_matrix4x4_f64 lm2_m4x4_rotate_y_f64(double angle);
LM2_API lm2_matrix4x4_f64 lm2_m4x4_rotate_z_f64(double angle);
LM2_API lm2_matrix4x4_f64 lm2_m4x4_rotate_axis_f64(lm2_v3_f64 axis, double angle);
LM2_API lm2_matrix4x4_f64 lm2_m4x4_scale_translate_f64(lm2_v3_f64 scale, lm2_v3_f64 translation);
LM2_API lm2_matrix4x4_f64 lm2_m4x4_world_transform_f64(lm2_v3_f64 translation, lm2_v3_f64 scale, lm2_v3_f64 rotation_euler);

// Operations
LM2_API lm2_matrix4x4_f64 lm2_m4x4_multiply_f64(lm2_matrix4x4_f64 a, lm2_matrix4x4_f64 b);
LM2_API lm2_matrix4x4_f64 lm2_m4x4_transpose_f64(lm2_matrix4x4_f64 m);
LM2_API lm2_matrix4x4_f64 lm2_m4x4_inverse_f64(lm2_matrix4x4_f64 m);
LM2_API double lm2_m4x4_determinant_f64(lm2_matrix4x4_f64 m);
LM2_API double lm2_m4x4_trace_f64(lm2_matrix4x4_f64 m);
LM2_API lm2_v3_f64 lm2_m4x4_transform_point_f64(lm2_matrix4x4_f64 m, lm2_v3_f64 v);
LM2_API lm2_v3_f64 lm2_m4x4_transform_vector_f64(lm2_matrix4x4_f64 m, lm2_v3_f64 v);
LM2_API lm2_v4_f64 lm2_m4x4_transform_f64(lm2_matrix4x4_f64 m, lm2_v4_f64 v);
LM2_API void lm2_m4x4_transform_points_f64(lm2_matrix4x4_f64 m, lm2_v3_f64* points, uint32_t count);
LM2_API void lm2_m4x4_transform_points_src_dst_f64(lm2_matrix4x4_f64 m, const lm2_v3_f64* src, lm2_v3_f64* dst, uint32_t count);

// Getters
LM2_API lm2_v3_f64 lm2_m4x4_get_scale_f64(lm2_matrix4x4_f64 m);
LM2_API lm2_v3_f64 lm2_m4x4_get_translation_f64(lm2_matrix4x4_f64 m);

// Projection
LM2_API lm2_matrix4x4_f64 lm2_m4x4_ortho_f64(double left, double right, double bottom, double top, double near_plane, double far_plane);
LM2_API lm2_matrix4x4_f64 lm2_m4x4_perspective_f64(double fov_y, double aspect, double near_plane, double far_plane);
LM2_API lm2_matrix4x4_f64 lm2_m4x4_look_at_f64(lm2_v3_f64 eye, lm2_v3_f64 target, lm2_v3_f64 up);

// =============================================================================
// Matrix 4x4 Function Declarations - f32
// =============================================================================

// Basic constructors
LM2_API lm2_matrix4x4_f32 lm2_m4x4_identity_f32(void);
LM2_API lm2_matrix4x4_f32 lm2_m4x4_zero_f32(void);
LM2_API lm2_matrix4x4_f32 lm2_m4x4_make_f32(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);

// Transformations
LM2_API lm2_matrix4x4_f32 lm2_m4x4_scale_f32(lm2_v3_f32 scale);
LM2_API lm2_matrix4x4_f32 lm2_m4x4_scale_uniform_f32(float scale);
LM2_API lm2_matrix4x4_f32 lm2_m4x4_translate_f32(lm2_v3_f32 translation);
LM2_API lm2_matrix4x4_f32 lm2_m4x4_rotate_x_f32(float angle);
LM2_API lm2_matrix4x4_f32 lm2_m4x4_rotate_y_f32(float angle);
LM2_API lm2_matrix4x4_f32 lm2_m4x4_rotate_z_f32(float angle);
LM2_API lm2_matrix4x4_f32 lm2_m4x4_rotate_axis_f32(lm2_v3_f32 axis, float angle);
LM2_API lm2_matrix4x4_f32 lm2_m4x4_scale_translate_f32(lm2_v3_f32 scale, lm2_v3_f32 translation);
LM2_API lm2_matrix4x4_f32 lm2_m4x4_world_transform_f32(lm2_v3_f32 translation, lm2_v3_f32 scale, lm2_v3_f32 rotation_euler);

// Operations
LM2_API lm2_matrix4x4_f32 lm2_m4x4_multiply_f32(lm2_matrix4x4_f32 a, lm2_matrix4x4_f32 b);
LM2_API lm2_matrix4x4_f32 lm2_m4x4_transpose_f32(lm2_matrix4x4_f32 m);
LM2_API lm2_matrix4x4_f32 lm2_m4x4_inverse_f32(lm2_matrix4x4_f32 m);
LM2_API float lm2_m4x4_determinant_f32(lm2_matrix4x4_f32 m);
LM2_API float lm2_m4x4_trace_f32(lm2_matrix4x4_f32 m);
LM2_API lm2_v3_f32 lm2_m4x4_transform_point_f32(lm2_matrix4x4_f32 m, lm2_v3_f32 v);
LM2_API lm2_v3_f32 lm2_m4x4_transform_vector_f32(lm2_matrix4x4_f32 m, lm2_v3_f32 v);
LM2_API lm2_v4_f32 lm2_m4x4_transform_f32(lm2_matrix4x4_f32 m, lm2_v4_f32 v);
LM2_API void lm2_m4x4_transform_points_f32(lm2_matrix4x4_f32 m, lm2_v3_f32* points, uint32_t count);
LM2_API void lm2_m4x4_transform_points_src_dst_f32(lm2_matrix4x4_f32 m, const lm2_v3_f32* src, lm2_v3_f32* dst, uint32_t count);

// Getters
LM2_API lm2_v3_f32 lm2_m4x4_get_scale_f32(lm2_matrix4x4_f32 m);
LM2_API lm2_v3_f32 lm2_m4x4_get_translation_f32(lm2_matrix4x4_f32 m);

// Projection
LM2_API lm2_matrix4x4_f32 lm2_m4x4_ortho_f32(float left, float right, float bottom, float top, float near_plane, float far_plane);
LM2_API lm2_matrix4x4_f32 lm2_m4x4_perspective_f32(float fov_y, float aspect, float near_plane, float far_plane);
LM2_API lm2_matrix4x4_f32 lm2_m4x4_look_at_f32(lm2_v3_f32 eye, lm2_v3_f32 target, lm2_v3_f32 up);

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// =============================================================================
// Quaternion Conversion Functions (Outside extern "C" for C++ compatibility)
// =============================================================================
// These functions return/accept quaternion types which have C++ operators,
// so they cannot use C linkage in C++ mode.

// Quaternion conversions - f64
LM2_API lm2_matrix4x4_f64 lm2_m4x4_from_quaternion_f64(lm2_quat_f64 q);
LM2_API lm2_quat_f64 lm2_m4x4_to_quaternion_f64(lm2_matrix4x4_f64 m);

// Quaternion conversions - f32
LM2_API lm2_matrix4x4_f32 lm2_m4x4_from_quaternion_f32(lm2_quat_f32 q);
LM2_API lm2_quat_f32 lm2_m4x4_to_quaternion_f32(lm2_matrix4x4_f32 m);

// C++ operator overloads (must be outside extern "C")
#if defined(__cplusplus) && !defined(LM2_NO_CPP_OPERATORS)
#  include "lm2_matrix_operators.h"
_LM2_DEFINE_MATRIX4X4_OPERATORS_SUFFIX(lm2_matrix4x4_f64, lm2_v3_f64, lm2_v4_f64, f64)
_LM2_DEFINE_MATRIX4X4_OPERATORS_SUFFIX(lm2_matrix4x4_f32, lm2_v3_f32, lm2_v4_f32, f32)
#endif
