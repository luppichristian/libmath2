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

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// Quaternion - 3D Rotation Representation
// =============================================================================
// Quaternions represent rotations in 3D space efficiently and avoid gimbal lock.
// Format: q = w + xi + yj + zk
// Where w is the scalar part, and (x, y, z) is the vector part.
//
// Benefits over Euler angles:
// - No gimbal lock
// - Smooth interpolation (SLERP)
// - Efficient concatenation
// - Compact representation (4 values vs 9 for rotation matrix)

typedef union lm2_quatf64 {
  double e[4];  // [x, y, z, w]
  struct {
    double x, y, z, w;  // w is scalar, xyz is vector part
  };
#if defined(__cplusplus) && !defined(LM2_NO_CPP_OPERATORS)
  inline double& operator[](int i) { return e[i]; }
  inline const double& operator[](int i) const { return e[i]; }
#endif
} lm2_quatf64;

typedef union lm2_quatf32 {
  float e[4];  // [x, y, z, w]
  struct {
    float x, y, z, w;  // w is scalar, xyz is vector part
  };
#if defined(__cplusplus) && !defined(LM2_NO_CPP_OPERATORS)
  inline float& operator[](int i) { return e[i]; }
  inline const float& operator[](int i) const { return e[i]; }
#endif
} lm2_quatf32;

// Default type alias
typedef lm2_quatf32 lm2_quat;

// =============================================================================
// Helper Macros for Declarations
// =============================================================================

#define _LM2_DECLARE_QUAT_BASIC(quat_type, scalar_type) \
  LM2_API quat_type quat_type##_identity(void);         \
  LM2_API quat_type quat_type##_zero(void);             \
  LM2_API quat_type quat_type##_make(scalar_type x, scalar_type y, scalar_type z, scalar_type w);

#define _LM2_DECLARE_QUAT_FROM(quat_type, scalar_type, vec3_type)                                 \
  LM2_API quat_type quat_type##_from_axis_angle(vec3_type axis, scalar_type angle);               \
  LM2_API quat_type quat_type##_from_euler(scalar_type pitch, scalar_type yaw, scalar_type roll); \
  LM2_API quat_type quat_type##_from_euler_vec(vec3_type euler);

#define _LM2_DECLARE_QUAT_TO(quat_type, scalar_type, vec3_type)                             \
  LM2_API void quat_type##_to_axis_angle(quat_type q, vec3_type* axis, scalar_type* angle); \
  LM2_API vec3_type quat_type##_to_euler(quat_type q);

#define _LM2_DECLARE_QUAT_OPS(quat_type, scalar_type, vec3_type)                \
  LM2_API quat_type quat_type##_conjugate(quat_type q);                         \
  LM2_API quat_type quat_type##_inverse(quat_type q);                           \
  LM2_API quat_type quat_type##_normalize(quat_type q);                         \
  LM2_API quat_type quat_type##_multiply(quat_type a, quat_type b);             \
  LM2_API quat_type quat_type##_add(quat_type a, quat_type b);                  \
  LM2_API quat_type quat_type##_sub(quat_type a, quat_type b);                  \
  LM2_API quat_type quat_type##_scale(quat_type q, scalar_type s);              \
  LM2_API scalar_type quat_type##_dot(quat_type a, quat_type b);                \
  LM2_API scalar_type quat_type##_length_squared(quat_type q);                  \
  LM2_API scalar_type quat_type##_length(quat_type q);                          \
  LM2_API vec3_type quat_type##_rotate_vector(quat_type q, vec3_type v);        \
  LM2_API quat_type quat_type##_slerp(quat_type a, quat_type b, scalar_type t); \
  LM2_API quat_type quat_type##_nlerp(quat_type a, quat_type b, scalar_type t); \
  LM2_API bool quat_type##_equals(quat_type a, quat_type b, scalar_type epsilon);

// =============================================================================
// Quaternion Function Declarations
// =============================================================================

_LM2_DECLARE_QUAT_BASIC(lm2_quatf64, double)
_LM2_DECLARE_QUAT_BASIC(lm2_quatf32, float)

_LM2_DECLARE_QUAT_FROM(lm2_quatf64, double, lm2_v3f64)
_LM2_DECLARE_QUAT_FROM(lm2_quatf32, float, lm2_v3f32)

_LM2_DECLARE_QUAT_TO(lm2_quatf64, double, lm2_v3f64)
_LM2_DECLARE_QUAT_TO(lm2_quatf32, float, lm2_v3f32)

_LM2_DECLARE_QUAT_OPS(lm2_quatf64, double, lm2_v3f64)
_LM2_DECLARE_QUAT_OPS(lm2_quatf32, float, lm2_v3f32)

// #############################################################################
LM2_HEADER_END;
// #############################################################################
