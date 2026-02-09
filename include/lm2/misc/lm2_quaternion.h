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
// Quaternion Function Declarations - f64
// =============================================================================

// Basic constructors
LM2_API lm2_quatf64 lm2_quatf64_identity(void);
LM2_API lm2_quatf64 lm2_quatf64_zero(void);
LM2_API lm2_quatf64 lm2_quatf64_make(double x, double y, double z, double w);

// Conversions from other representations
LM2_API lm2_quatf64 lm2_quatf64_from_axis_angle(lm2_v3f64 axis, double angle);
LM2_API lm2_quatf64 lm2_quatf64_from_euler(double pitch, double yaw, double roll);
LM2_API lm2_quatf64 lm2_quatf64_from_euler_vec(lm2_v3f64 euler);

// Conversions to other representations
LM2_API void lm2_quatf64_to_axis_angle(lm2_quatf64 q, lm2_v3f64* axis, double* angle);
LM2_API lm2_v3f64 lm2_quatf64_to_euler(lm2_quatf64 q);

// Operations
LM2_API lm2_quatf64 lm2_quatf64_conjugate(lm2_quatf64 q);
LM2_API lm2_quatf64 lm2_quatf64_inverse(lm2_quatf64 q);
LM2_API lm2_quatf64 lm2_quatf64_normalize(lm2_quatf64 q);
LM2_API lm2_quatf64 lm2_quatf64_multiply(lm2_quatf64 a, lm2_quatf64 b);
LM2_API lm2_quatf64 lm2_quatf64_add(lm2_quatf64 a, lm2_quatf64 b);
LM2_API lm2_quatf64 lm2_quatf64_sub(lm2_quatf64 a, lm2_quatf64 b);
LM2_API lm2_quatf64 lm2_quatf64_scale(lm2_quatf64 q, double s);
LM2_API double lm2_quatf64_dot(lm2_quatf64 a, lm2_quatf64 b);
LM2_API double lm2_quatf64_length_squared(lm2_quatf64 q);
LM2_API double lm2_quatf64_length(lm2_quatf64 q);
LM2_API lm2_v3f64 lm2_quatf64_rotate_vector(lm2_quatf64 q, lm2_v3f64 v);
LM2_API lm2_quatf64 lm2_quatf64_slerp(lm2_quatf64 a, lm2_quatf64 b, double t);
LM2_API lm2_quatf64 lm2_quatf64_nlerp(lm2_quatf64 a, lm2_quatf64 b, double t);
LM2_API bool lm2_quatf64_equals(lm2_quatf64 a, lm2_quatf64 b, double epsilon);

// =============================================================================
// Quaternion Function Declarations - f32
// =============================================================================

// Basic constructors
LM2_API lm2_quatf32 lm2_quatf32_identity(void);
LM2_API lm2_quatf32 lm2_quatf32_zero(void);
LM2_API lm2_quatf32 lm2_quatf32_make(float x, float y, float z, float w);

// Conversions from other representations
LM2_API lm2_quatf32 lm2_quatf32_from_axis_angle(lm2_v3f32 axis, float angle);
LM2_API lm2_quatf32 lm2_quatf32_from_euler(float pitch, float yaw, float roll);
LM2_API lm2_quatf32 lm2_quatf32_from_euler_vec(lm2_v3f32 euler);

// Conversions to other representations
LM2_API void lm2_quatf32_to_axis_angle(lm2_quatf32 q, lm2_v3f32* axis, float* angle);
LM2_API lm2_v3f32 lm2_quatf32_to_euler(lm2_quatf32 q);

// Operations
LM2_API lm2_quatf32 lm2_quatf32_conjugate(lm2_quatf32 q);
LM2_API lm2_quatf32 lm2_quatf32_inverse(lm2_quatf32 q);
LM2_API lm2_quatf32 lm2_quatf32_normalize(lm2_quatf32 q);
LM2_API lm2_quatf32 lm2_quatf32_multiply(lm2_quatf32 a, lm2_quatf32 b);
LM2_API lm2_quatf32 lm2_quatf32_add(lm2_quatf32 a, lm2_quatf32 b);
LM2_API lm2_quatf32 lm2_quatf32_sub(lm2_quatf32 a, lm2_quatf32 b);
LM2_API lm2_quatf32 lm2_quatf32_scale(lm2_quatf32 q, float s);
LM2_API float lm2_quatf32_dot(lm2_quatf32 a, lm2_quatf32 b);
LM2_API float lm2_quatf32_length_squared(lm2_quatf32 q);
LM2_API float lm2_quatf32_length(lm2_quatf32 q);
LM2_API lm2_v3f32 lm2_quatf32_rotate_vector(lm2_quatf32 q, lm2_v3f32 v);
LM2_API lm2_quatf32 lm2_quatf32_slerp(lm2_quatf32 a, lm2_quatf32 b, float t);
LM2_API lm2_quatf32 lm2_quatf32_nlerp(lm2_quatf32 a, lm2_quatf32 b, float t);
LM2_API bool lm2_quatf32_equals(lm2_quatf32 a, lm2_quatf32 b, float epsilon);

// #############################################################################
LM2_HEADER_END;
// #############################################################################
