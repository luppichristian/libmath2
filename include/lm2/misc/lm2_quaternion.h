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

typedef union lm2_quat_f64 {
  double e[4];  // [x, y, z, w]
  struct {
    double x, y, z, w;  // w is scalar, xyz is vector part
  };

  _LM2_SUBSCRIPT_OP(double, 4)
} lm2_quat_f64;

typedef union lm2_quat_f32 {
  float e[4];  // [x, y, z, w]
  struct {
    float x, y, z, w;  // w is scalar, xyz is vector part
  };

  _LM2_SUBSCRIPT_OP(float, 4)
} lm2_quat_f32;

// Default type alias
typedef lm2_quat_f32 lm2_quat;

// =============================================================================
// Quaternion Function Declarations - f64
// =============================================================================

// Basic constructors
LM2_API lm2_quat_f64 lm2_quat_identity_f64(void);
LM2_API lm2_quat_f64 lm2_quat_zero_f64(void);
LM2_API lm2_quat_f64 lm2_quat_make_f64(double x, double y, double z, double w);

// Conversions from other representations
LM2_API lm2_quat_f64 lm2_quat_from_axis_angle_f64(lm2_v3_f64 axis, double angle);
LM2_API lm2_quat_f64 lm2_quat_from_euler_f64(double pitch, double yaw, double roll);
LM2_API lm2_quat_f64 lm2_quat_from_euler_vec_f64(lm2_v3_f64 euler);

// Conversions to other representations
LM2_API void lm2_quat_to_axis_angle_f64(lm2_quat_f64 q, lm2_v3_f64* axis, double* angle);
LM2_API lm2_v3_f64 lm2_quat_to_euler_f64(lm2_quat_f64 q);

// Operations
LM2_API lm2_quat_f64 lm2_quat_conjugate_f64(lm2_quat_f64 q);
LM2_API lm2_quat_f64 lm2_quat_inverse_f64(lm2_quat_f64 q);
LM2_API lm2_quat_f64 lm2_quat_normalize_f64(lm2_quat_f64 q);
LM2_API lm2_quat_f64 lm2_quat_multiply_f64(lm2_quat_f64 a, lm2_quat_f64 b);
LM2_API lm2_quat_f64 lm2_quat_add_f64(lm2_quat_f64 a, lm2_quat_f64 b);
LM2_API lm2_quat_f64 lm2_quat_sub_f64(lm2_quat_f64 a, lm2_quat_f64 b);
LM2_API lm2_quat_f64 lm2_quat_scale_f64(lm2_quat_f64 q, double s);
LM2_API double lm2_quat_dot_f64(lm2_quat_f64 a, lm2_quat_f64 b);
LM2_API double lm2_quat_length_squared_f64(lm2_quat_f64 q);
LM2_API double lm2_quat_length_f64(lm2_quat_f64 q);
LM2_API lm2_v3_f64 lm2_quat_rotate_vector_f64(lm2_quat_f64 q, lm2_v3_f64 v);
LM2_API lm2_quat_f64 lm2_quat_slerp_f64(lm2_quat_f64 a, lm2_quat_f64 b, double t);
LM2_API lm2_quat_f64 lm2_quat_nlerp_f64(lm2_quat_f64 a, lm2_quat_f64 b, double t);
LM2_API bool lm2_quat_equals_f64(lm2_quat_f64 a, lm2_quat_f64 b, double epsilon);

// =============================================================================
// Quaternion Function Declarations - f32
// =============================================================================

// Basic constructors
LM2_API lm2_quat_f32 lm2_quat_identity_f32(void);
LM2_API lm2_quat_f32 lm2_quat_zero_f32(void);
LM2_API lm2_quat_f32 lm2_quat_make_f32(float x, float y, float z, float w);

// Conversions from other representations
LM2_API lm2_quat_f32 lm2_quat_from_axis_angle_f32(lm2_v3_f32 axis, float angle);
LM2_API lm2_quat_f32 lm2_quat_from_euler_f32(float pitch, float yaw, float roll);
LM2_API lm2_quat_f32 lm2_quat_from_euler_vec_f32(lm2_v3_f32 euler);

// Conversions to other representations
LM2_API void lm2_quat_to_axis_angle_f32(lm2_quat_f32 q, lm2_v3_f32* axis, float* angle);
LM2_API lm2_v3_f32 lm2_quat_to_euler_f32(lm2_quat_f32 q);

// Operations
LM2_API lm2_quat_f32 lm2_quat_conjugate_f32(lm2_quat_f32 q);
LM2_API lm2_quat_f32 lm2_quat_inverse_f32(lm2_quat_f32 q);
LM2_API lm2_quat_f32 lm2_quat_normalize_f32(lm2_quat_f32 q);
LM2_API lm2_quat_f32 lm2_quat_multiply_f32(lm2_quat_f32 a, lm2_quat_f32 b);
LM2_API lm2_quat_f32 lm2_quat_add_f32(lm2_quat_f32 a, lm2_quat_f32 b);
LM2_API lm2_quat_f32 lm2_quat_sub_f32(lm2_quat_f32 a, lm2_quat_f32 b);
LM2_API lm2_quat_f32 lm2_quat_scale_f32(lm2_quat_f32 q, float s);
LM2_API float lm2_quat_dot_f32(lm2_quat_f32 a, lm2_quat_f32 b);
LM2_API float lm2_quat_length_squared_f32(lm2_quat_f32 q);
LM2_API float lm2_quat_length_f32(lm2_quat_f32 q);
LM2_API lm2_v3_f32 lm2_quat_rotate_vector_f32(lm2_quat_f32 q, lm2_v3_f32 v);
LM2_API lm2_quat_f32 lm2_quat_slerp_f32(lm2_quat_f32 a, lm2_quat_f32 b, float t);
LM2_API lm2_quat_f32 lm2_quat_nlerp_f32(lm2_quat_f32 a, lm2_quat_f32 b, float t);
LM2_API bool lm2_quat_equals_f32(lm2_quat_f32 a, lm2_quat_f32 b, float epsilon);

// #############################################################################
LM2_HEADER_END;
// #############################################################################
