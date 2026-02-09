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
typedef union lm2_quatf64 lm2_quatf64;
typedef union lm2_quatf32 lm2_quatf32;

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

typedef union lm2_m4x4f64 {
  double m[16];  // Row-major: [m00, m01, m02, m03, m10, ...]
  struct {
    double m00, m01, m02, m03;  // First row
    double m10, m11, m12, m13;  // Second row
    double m20, m21, m22, m23;  // Third row
    double m30, m31, m32, m33;  // Fourth row
  };
#if defined(__cplusplus) && !defined(LM2_NO_CPP_OPERATORS)
  inline double& operator[](int i) { return m[i]; }
  inline const double& operator[](int i) const { return m[i]; }
#endif
} lm2_m4x4f64;

typedef union lm2_m4x4f32 {
  float m[16];  // Row-major: [m00, m01, m02, m03, m10, ...]
  struct {
    float m00, m01, m02, m03;  // First row
    float m10, m11, m12, m13;  // Second row
    float m20, m21, m22, m23;  // Third row
    float m30, m31, m32, m33;  // Fourth row
  };
#if defined(__cplusplus) && !defined(LM2_NO_CPP_OPERATORS)
  inline float& operator[](int i) { return m[i]; }
  inline const float& operator[](int i) const { return m[i]; }
#endif
} lm2_m4x4f32;

// Default type alias
typedef lm2_m4x4f32 lm2_m4x4;

// =============================================================================
// Matrix 4x4 Function Declarations - f64
// =============================================================================

// Basic constructors
LM2_API lm2_m4x4f64 lm2_m4x4f64_identity(void);
LM2_API lm2_m4x4f64 lm2_m4x4f64_zero(void);
LM2_API lm2_m4x4f64 lm2_m4x4f64_make(double m00, double m01, double m02, double m03, double m10, double m11, double m12, double m13, double m20, double m21, double m22, double m23, double m30, double m31, double m32, double m33);

// Transformations
LM2_API lm2_m4x4f64 lm2_m4x4f64_scale(lm2_v3f64 scale);
LM2_API lm2_m4x4f64 lm2_m4x4f64_scale_uniform(double scale);
LM2_API lm2_m4x4f64 lm2_m4x4f64_translate(lm2_v3f64 translation);
LM2_API lm2_m4x4f64 lm2_m4x4f64_rotate_x(double angle);
LM2_API lm2_m4x4f64 lm2_m4x4f64_rotate_y(double angle);
LM2_API lm2_m4x4f64 lm2_m4x4f64_rotate_z(double angle);
LM2_API lm2_m4x4f64 lm2_m4x4f64_rotate_axis(lm2_v3f64 axis, double angle);
LM2_API lm2_m4x4f64 lm2_m4x4f64_scale_translate(lm2_v3f64 scale, lm2_v3f64 translation);
LM2_API lm2_m4x4f64 lm2_m4x4f64_world_transform(lm2_v3f64 translation, lm2_v3f64 scale, lm2_v3f64 rotation_euler);

// Operations
LM2_API lm2_m4x4f64 lm2_m4x4f64_multiply(lm2_m4x4f64 a, lm2_m4x4f64 b);
LM2_API lm2_m4x4f64 lm2_m4x4f64_transpose(lm2_m4x4f64 m);
LM2_API lm2_m4x4f64 lm2_m4x4f64_inverse(lm2_m4x4f64 m);
LM2_API double lm2_m4x4f64_determinant(lm2_m4x4f64 m);
LM2_API double lm2_m4x4f64_trace(lm2_m4x4f64 m);
LM2_API lm2_v3f64 lm2_m4x4f64_transform_point(lm2_m4x4f64 m, lm2_v3f64 v);
LM2_API lm2_v3f64 lm2_m4x4f64_transform_vector(lm2_m4x4f64 m, lm2_v3f64 v);
LM2_API lm2_v4f64 lm2_m4x4f64_transform(lm2_m4x4f64 m, lm2_v4f64 v);
LM2_API void lm2_m4x4f64_transform_points(lm2_m4x4f64 m, lm2_v3f64* points, uint32_t count);
LM2_API void lm2_m4x4f64_transform_points_src_dst(lm2_m4x4f64 m, const lm2_v3f64* src, lm2_v3f64* dst, uint32_t count);

// Getters
LM2_API lm2_v3f64 lm2_m4x4f64_get_scale(lm2_m4x4f64 m);
LM2_API lm2_v3f64 lm2_m4x4f64_get_translation(lm2_m4x4f64 m);

// Projection
LM2_API lm2_m4x4f64 lm2_m4x4f64_ortho(double left, double right, double bottom, double top, double near_plane, double far_plane);
LM2_API lm2_m4x4f64 lm2_m4x4f64_perspective(double fov_y, double aspect, double near_plane, double far_plane);
LM2_API lm2_m4x4f64 lm2_m4x4f64_look_at(lm2_v3f64 eye, lm2_v3f64 target, lm2_v3f64 up);

// =============================================================================
// Matrix 4x4 Function Declarations - f32
// =============================================================================

// Basic constructors
LM2_API lm2_m4x4f32 lm2_m4x4f32_identity(void);
LM2_API lm2_m4x4f32 lm2_m4x4f32_zero(void);
LM2_API lm2_m4x4f32 lm2_m4x4f32_make(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);

// Transformations
LM2_API lm2_m4x4f32 lm2_m4x4f32_scale(lm2_v3f32 scale);
LM2_API lm2_m4x4f32 lm2_m4x4f32_scale_uniform(float scale);
LM2_API lm2_m4x4f32 lm2_m4x4f32_translate(lm2_v3f32 translation);
LM2_API lm2_m4x4f32 lm2_m4x4f32_rotate_x(float angle);
LM2_API lm2_m4x4f32 lm2_m4x4f32_rotate_y(float angle);
LM2_API lm2_m4x4f32 lm2_m4x4f32_rotate_z(float angle);
LM2_API lm2_m4x4f32 lm2_m4x4f32_rotate_axis(lm2_v3f32 axis, float angle);
LM2_API lm2_m4x4f32 lm2_m4x4f32_scale_translate(lm2_v3f32 scale, lm2_v3f32 translation);
LM2_API lm2_m4x4f32 lm2_m4x4f32_world_transform(lm2_v3f32 translation, lm2_v3f32 scale, lm2_v3f32 rotation_euler);

// Operations
LM2_API lm2_m4x4f32 lm2_m4x4f32_multiply(lm2_m4x4f32 a, lm2_m4x4f32 b);
LM2_API lm2_m4x4f32 lm2_m4x4f32_transpose(lm2_m4x4f32 m);
LM2_API lm2_m4x4f32 lm2_m4x4f32_inverse(lm2_m4x4f32 m);
LM2_API float lm2_m4x4f32_determinant(lm2_m4x4f32 m);
LM2_API float lm2_m4x4f32_trace(lm2_m4x4f32 m);
LM2_API lm2_v3f32 lm2_m4x4f32_transform_point(lm2_m4x4f32 m, lm2_v3f32 v);
LM2_API lm2_v3f32 lm2_m4x4f32_transform_vector(lm2_m4x4f32 m, lm2_v3f32 v);
LM2_API lm2_v4f32 lm2_m4x4f32_transform(lm2_m4x4f32 m, lm2_v4f32 v);
LM2_API void lm2_m4x4f32_transform_points(lm2_m4x4f32 m, lm2_v3f32* points, uint32_t count);
LM2_API void lm2_m4x4f32_transform_points_src_dst(lm2_m4x4f32 m, const lm2_v3f32* src, lm2_v3f32* dst, uint32_t count);

// Getters
LM2_API lm2_v3f32 lm2_m4x4f32_get_scale(lm2_m4x4f32 m);
LM2_API lm2_v3f32 lm2_m4x4f32_get_translation(lm2_m4x4f32 m);

// Projection
LM2_API lm2_m4x4f32 lm2_m4x4f32_ortho(float left, float right, float bottom, float top, float near_plane, float far_plane);
LM2_API lm2_m4x4f32 lm2_m4x4f32_perspective(float fov_y, float aspect, float near_plane, float far_plane);
LM2_API lm2_m4x4f32 lm2_m4x4f32_look_at(lm2_v3f32 eye, lm2_v3f32 target, lm2_v3f32 up);

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// =============================================================================
// Quaternion Conversion Functions (Outside extern "C" for C++ compatibility)
// =============================================================================
// These functions return/accept quaternion types which have C++ operators,
// so they cannot use C linkage in C++ mode.

// Quaternion conversions - f64
LM2_API lm2_m4x4f64 lm2_m4x4f64_from_quaternion(lm2_quatf64 q);
LM2_API lm2_quatf64 lm2_m4x4f64_to_quaternion(lm2_m4x4f64 m);

// Quaternion conversions - f32
LM2_API lm2_m4x4f32 lm2_m4x4f32_from_quaternion(lm2_quatf32 q);
LM2_API lm2_quatf32 lm2_m4x4f32_to_quaternion(lm2_m4x4f32 m);

// C++ operator overloads (must be outside extern "C")
#if defined(__cplusplus) && !defined(LM2_NO_CPP_OPERATORS)
#  include "lm2_matrix_operators.h"
_LM2_DEFINE_M4X4_OPERATORS(lm2_m4x4f64, lm2_v3f64, lm2_v4f64)
_LM2_DEFINE_M4X4_OPERATORS(lm2_m4x4f32, lm2_v3f32, lm2_v4f32)
#endif
