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
// Helper Macros for Declarations
// =============================================================================

#define _LM2_DECLARE_M4X4_BASIC(mat_type, scalar_type) \
  LM2_API mat_type mat_type##_identity(void);          \
  LM2_API mat_type mat_type##_zero(void);              \
  LM2_API mat_type mat_type##_make(scalar_type m00, scalar_type m01, scalar_type m02, scalar_type m03, scalar_type m10, scalar_type m11, scalar_type m12, scalar_type m13, scalar_type m20, scalar_type m21, scalar_type m22, scalar_type m23, scalar_type m30, scalar_type m31, scalar_type m32, scalar_type m33);

#define _LM2_DECLARE_M4X4_TRANSFORM(mat_type, scalar_type, vec3_type)                  \
  LM2_API mat_type mat_type##_scale(vec3_type scale);                                  \
  LM2_API mat_type mat_type##_scale_uniform(scalar_type scale);                        \
  LM2_API mat_type mat_type##_translate(vec3_type translation);                        \
  LM2_API mat_type mat_type##_rotate_x(scalar_type angle);                             \
  LM2_API mat_type mat_type##_rotate_y(scalar_type angle);                             \
  LM2_API mat_type mat_type##_rotate_z(scalar_type angle);                             \
  LM2_API mat_type mat_type##_rotate_axis(vec3_type axis, scalar_type angle);          \
  LM2_API mat_type mat_type##_scale_translate(vec3_type scale, vec3_type translation); \
  LM2_API mat_type mat_type##_world_transform(vec3_type translation, vec3_type scale, vec3_type rotation_euler);

#define _LM2_DECLARE_M4X4_OPS(mat_type, scalar_type, vec3_type, vec4_type)                 \
  LM2_API mat_type mat_type##_multiply(mat_type a, mat_type b);                            \
  LM2_API mat_type mat_type##_transpose(mat_type m);                                       \
  LM2_API mat_type mat_type##_inverse(mat_type m);                                         \
  LM2_API scalar_type mat_type##_determinant(mat_type m);                                  \
  LM2_API scalar_type mat_type##_trace(mat_type m);                                        \
  LM2_API vec3_type mat_type##_transform_point(mat_type m, vec3_type v);                   \
  LM2_API vec3_type mat_type##_transform_vector(mat_type m, vec3_type v);                  \
  LM2_API vec4_type mat_type##_transform(mat_type m, vec4_type v);                         \
  LM2_API void mat_type##_transform_points(mat_type m, vec3_type* points, uint32_t count); \
  LM2_API void mat_type##_transform_points_src_dst(mat_type m, const vec3_type* src, vec3_type* dst, uint32_t count);

#define _LM2_DECLARE_M4X4_GETTERS(mat_type, scalar_type, vec3_type) \
  LM2_API vec3_type mat_type##_get_scale(mat_type m);               \
  LM2_API vec3_type mat_type##_get_translation(mat_type m);

#define _LM2_DECLARE_M4X4_PROJECTION(mat_type, scalar_type, vec3_type)                                                                                        \
  LM2_API mat_type mat_type##_ortho(scalar_type left, scalar_type right, scalar_type bottom, scalar_type top, scalar_type near_plane, scalar_type far_plane); \
  LM2_API mat_type mat_type##_perspective(scalar_type fov_y, scalar_type aspect, scalar_type near_plane, scalar_type far_plane);                              \
  LM2_API mat_type mat_type##_look_at(vec3_type eye, vec3_type target, vec3_type up);

#define _LM2_DECLARE_M4X4_QUATERNION(mat_type, quat_type)   \
  LM2_API mat_type mat_type##_from_quaternion(quat_type q); \
  LM2_API quat_type mat_type##_to_quaternion(mat_type m);

// =============================================================================
// Matrix 4x4 Function Declarations
// =============================================================================

_LM2_DECLARE_M4X4_BASIC(lm2_m4x4f64, double)
_LM2_DECLARE_M4X4_BASIC(lm2_m4x4f32, float)

_LM2_DECLARE_M4X4_TRANSFORM(lm2_m4x4f64, double, lm2_v3f64)
_LM2_DECLARE_M4X4_TRANSFORM(lm2_m4x4f32, float, lm2_v3f32)

_LM2_DECLARE_M4X4_OPS(lm2_m4x4f64, double, lm2_v3f64, lm2_v4f64)
_LM2_DECLARE_M4X4_OPS(lm2_m4x4f32, float, lm2_v3f32, lm2_v4f32)

_LM2_DECLARE_M4X4_GETTERS(lm2_m4x4f64, double, lm2_v3f64)
_LM2_DECLARE_M4X4_GETTERS(lm2_m4x4f32, float, lm2_v3f32)

_LM2_DECLARE_M4X4_PROJECTION(lm2_m4x4f64, double, lm2_v3f64)
_LM2_DECLARE_M4X4_PROJECTION(lm2_m4x4f32, float, lm2_v3f32)

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// =============================================================================
// Quaternion Conversion Functions (Outside extern "C" for C++ compatibility)
// =============================================================================
// These functions return/accept quaternion types which have C++ operators,
// so they cannot use C linkage in C++ mode.

_LM2_DECLARE_M4X4_QUATERNION(lm2_m4x4f64, lm2_quatf64)
_LM2_DECLARE_M4X4_QUATERNION(lm2_m4x4f32, lm2_quatf32)

// C++ operator overloads (must be outside extern "C")
#ifndef LM2_NO_CPP_OPERATORS
#  include "lm2_matrix_operators.h"
_LM2_DEFINE_M4X4_OPERATORS(lm2_m4x4f64, lm2_v3f64, lm2_v4f64)
_LM2_DEFINE_M4X4_OPERATORS(lm2_m4x4f32, lm2_v3f32, lm2_v4f32)
#endif
