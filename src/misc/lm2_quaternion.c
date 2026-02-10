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

#include <lm2/misc/lm2_quaternion.h>
#include <lm2/lm2_constants.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/scalar/lm2_trigonometry.h>
#include <lm2/vectors/lm2_vector_specifics.h>

// =============================================================================
// Quaternion Functions - f64
// =============================================================================

// Basic constructors
LM2_API lm2_quat_f64 lm2_quat_identity_f64(void) {
  lm2_quat_f64 q = {0.0, 0.0, 0.0, 1.0};
  return q;
}

LM2_API lm2_quat_f64 lm2_quat_zero_f64(void) {
  lm2_quat_f64 q = {0.0, 0.0, 0.0, 0.0};
  return q;
}

LM2_API lm2_quat_f64 lm2_quat_make_f64(double x, double y, double z, double w) {
  lm2_quat_f64 q = {x, y, z, w};
  return q;
}

// Conversions from other representations
LM2_API lm2_quat_f64 lm2_quat_from_axis_angle_f64(lm2_v3_f64 axis, double angle) {
  // Normalize the axis
  double len_sq = lm2_add_f64(lm2_add_f64(lm2_mul_f64(axis.x, axis.x), lm2_mul_f64(axis.y, axis.y)), lm2_mul_f64(axis.z, axis.z));
  double len = lm2_sqrt_f64(len_sq);
  LM2_ASSERT_UNSAFE(len > 0.0);

  double inv_len = lm2_div_f64(1.0, len);
  double nx = lm2_mul_f64(axis.x, inv_len);
  double ny = lm2_mul_f64(axis.y, inv_len);
  double nz = lm2_mul_f64(axis.z, inv_len);

  double half_angle = lm2_mul_f64(angle, 0.5);
  double s = lm2_sin_f64(half_angle);
  double c = lm2_cos_f64(half_angle);

  lm2_quat_f64 q;
  q.x = lm2_mul_f64(nx, s);
  q.y = lm2_mul_f64(ny, s);
  q.z = lm2_mul_f64(nz, s);
  q.w = c;
  return q;
}

LM2_API lm2_quat_f64 lm2_quat_from_euler_f64(double pitch, double yaw, double roll) {
  // Convert Euler angles (pitch, yaw, roll) to quaternion
  // Rotation order: YXZ (yaw, pitch, roll)
  double half_pitch = lm2_mul_f64(pitch, 0.5);
  double half_yaw = lm2_mul_f64(yaw, 0.5);
  double half_roll = lm2_mul_f64(roll, 0.5);

  double cp = lm2_cos_f64(half_pitch);
  double sp = lm2_sin_f64(half_pitch);
  double cy = lm2_cos_f64(half_yaw);
  double sy = lm2_sin_f64(half_yaw);
  double cr = lm2_cos_f64(half_roll);
  double sr = lm2_sin_f64(half_roll);

  lm2_quat_f64 q;
  q.w = lm2_sub_f64(lm2_add_f64(lm2_mul_f64(cr, lm2_mul_f64(cp, cy)), lm2_mul_f64(sr, lm2_mul_f64(sp, sy))), 0.0);
  q.x = lm2_sub_f64(lm2_mul_f64(sr, lm2_mul_f64(cp, cy)), lm2_mul_f64(cr, lm2_mul_f64(sp, sy)));
  q.y = lm2_add_f64(lm2_mul_f64(cr, lm2_mul_f64(sp, cy)), lm2_mul_f64(sr, lm2_mul_f64(cp, sy)));
  q.z = lm2_sub_f64(lm2_mul_f64(cr, lm2_mul_f64(cp, sy)), lm2_mul_f64(sr, lm2_mul_f64(sp, cy)));
  return q;
}

LM2_API lm2_quat_f64 lm2_quat_from_euler_vec_f64(lm2_v3_f64 euler) {
  return lm2_quat_from_euler_f64(euler.x, euler.y, euler.z);
}

// Conversions to other representations
LM2_API void lm2_quat_to_axis_angle_f64(lm2_quat_f64 q, lm2_v3_f64* axis, double* angle) {
  LM2_ASSERT(axis != NULL && angle != NULL);

  double len_sq = lm2_add_f64(lm2_add_f64(lm2_mul_f64(q.x, q.x), lm2_mul_f64(q.y, q.y)), lm2_mul_f64(q.z, q.z));

  if (len_sq < 1e-10) {
    // No rotation
    axis->x = 1.0;
    axis->y = 0.0;
    axis->z = 0.0;
    *angle = 0.0;
    return;
  }

  double len = lm2_sqrt_f64(len_sq);
  double inv_len = lm2_div_f64(1.0, len);

  axis->x = lm2_mul_f64(q.x, inv_len);
  axis->y = lm2_mul_f64(q.y, inv_len);
  axis->z = lm2_mul_f64(q.z, inv_len);
  *angle = lm2_mul_f64(2.0, lm2_atan2_f64(len, q.w));
}

LM2_API lm2_v3_f64 lm2_quat_to_euler_f64(lm2_quat_f64 q) {
  lm2_v3_f64 euler;

  // Roll (x-axis rotation)
  double sinr_cosp = lm2_mul_f64(2.0, lm2_add_f64(lm2_mul_f64(q.w, q.x), lm2_mul_f64(q.y, q.z)));
  double cosr_cosp = lm2_sub_f64(1.0, lm2_mul_f64(2.0, lm2_add_f64(lm2_mul_f64(q.x, q.x), lm2_mul_f64(q.y, q.y))));
  euler.z = lm2_atan2_f64(sinr_cosp, cosr_cosp);

  // Pitch (y-axis rotation)
  double sinp = lm2_mul_f64(2.0, lm2_sub_f64(lm2_mul_f64(q.w, q.y), lm2_mul_f64(q.z, q.x)));
  if (lm2_abs_f64(sinp) >= 1.0) {
    euler.x = lm2_mul_f64(lm2_sign_f64(sinp), LM2_HPI_F64);  // Use 90 degrees if out of range
  } else {
    euler.x = lm2_asin_f64(sinp);
  }

  // Yaw (z-axis rotation)
  double siny_cosp = lm2_mul_f64(2.0, lm2_add_f64(lm2_mul_f64(q.w, q.z), lm2_mul_f64(q.x, q.y)));
  double cosy_cosp = lm2_sub_f64(1.0, lm2_mul_f64(2.0, lm2_add_f64(lm2_mul_f64(q.y, q.y), lm2_mul_f64(q.z, q.z))));
  euler.y = lm2_atan2_f64(siny_cosp, cosy_cosp);

  return euler;
}

// Operations
LM2_API lm2_quat_f64 lm2_quat_conjugate_f64(lm2_quat_f64 q) {
  lm2_quat_f64 result;
  result.x = lm2_sub_f64(0.0, q.x);
  result.y = lm2_sub_f64(0.0, q.y);
  result.z = lm2_sub_f64(0.0, q.z);
  result.w = q.w;
  return result;
}

LM2_API lm2_quat_f64 lm2_quat_inverse_f64(lm2_quat_f64 q) {
  double len_sq = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(q.x, q.x), lm2_mul_f64(q.y, q.y)), lm2_mul_f64(q.z, q.z)), lm2_mul_f64(q.w, q.w));
  LM2_ASSERT_UNSAFE(len_sq > 0.0);

  double inv_len_sq = lm2_div_f64(1.0, len_sq);

  lm2_quat_f64 result;
  result.x = lm2_mul_f64(lm2_sub_f64(0.0, q.x), inv_len_sq);
  result.y = lm2_mul_f64(lm2_sub_f64(0.0, q.y), inv_len_sq);
  result.z = lm2_mul_f64(lm2_sub_f64(0.0, q.z), inv_len_sq);
  result.w = lm2_mul_f64(q.w, inv_len_sq);
  return result;
}

LM2_API lm2_quat_f64 lm2_quat_normalize_f64(lm2_quat_f64 q) {
  double len_sq = lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(q.x, q.x), lm2_mul_f64(q.y, q.y)), lm2_mul_f64(q.z, q.z)), lm2_mul_f64(q.w, q.w));
  LM2_ASSERT_UNSAFE(len_sq > 0.0);

  double inv_len = lm2_div_f64(1.0, lm2_sqrt_f64(len_sq));

  lm2_quat_f64 result;
  result.x = lm2_mul_f64(q.x, inv_len);
  result.y = lm2_mul_f64(q.y, inv_len);
  result.z = lm2_mul_f64(q.z, inv_len);
  result.w = lm2_mul_f64(q.w, inv_len);
  return result;
}

LM2_API lm2_quat_f64 lm2_quat_multiply_f64(lm2_quat_f64 a, lm2_quat_f64 b) {
  lm2_quat_f64 result;
  result.w = lm2_sub_f64(lm2_sub_f64(lm2_mul_f64(a.w, b.w), lm2_mul_f64(a.x, b.x)), lm2_add_f64(lm2_mul_f64(a.y, b.y), lm2_mul_f64(a.z, b.z)));
  result.x = lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.w, b.x), lm2_mul_f64(a.x, b.w)), lm2_sub_f64(lm2_mul_f64(a.y, b.z), lm2_mul_f64(a.z, b.y)));
  result.y = lm2_add_f64(lm2_sub_f64(lm2_mul_f64(a.w, b.y), lm2_mul_f64(a.x, b.z)), lm2_add_f64(lm2_mul_f64(a.y, b.w), lm2_mul_f64(a.z, b.x)));
  result.z = lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.w, b.z), lm2_mul_f64(a.x, b.y)), lm2_sub_f64(lm2_mul_f64(a.z, b.w), lm2_mul_f64(a.y, b.x)));
  return result;
}

LM2_API lm2_quat_f64 lm2_quat_add_f64(lm2_quat_f64 a, lm2_quat_f64 b) {
  lm2_quat_f64 result;
  result.x = lm2_add_f64(a.x, b.x);
  result.y = lm2_add_f64(a.y, b.y);
  result.z = lm2_add_f64(a.z, b.z);
  result.w = lm2_add_f64(a.w, b.w);
  return result;
}

LM2_API lm2_quat_f64 lm2_quat_sub_f64(lm2_quat_f64 a, lm2_quat_f64 b) {
  lm2_quat_f64 result;
  result.x = lm2_sub_f64(a.x, b.x);
  result.y = lm2_sub_f64(a.y, b.y);
  result.z = lm2_sub_f64(a.z, b.z);
  result.w = lm2_sub_f64(a.w, b.w);
  return result;
}

LM2_API lm2_quat_f64 lm2_quat_scale_f64(lm2_quat_f64 q, double s) {
  lm2_quat_f64 result;
  result.x = lm2_mul_f64(q.x, s);
  result.y = lm2_mul_f64(q.y, s);
  result.z = lm2_mul_f64(q.z, s);
  result.w = lm2_mul_f64(q.w, s);
  return result;
}

LM2_API double lm2_quat_dot_f64(lm2_quat_f64 a, lm2_quat_f64 b) {
  return lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(a.x, b.x), lm2_mul_f64(a.y, b.y)), lm2_mul_f64(a.z, b.z)), lm2_mul_f64(a.w, b.w));
}

LM2_API double lm2_quat_length_squared_f64(lm2_quat_f64 q) {
  return lm2_add_f64(lm2_add_f64(lm2_add_f64(lm2_mul_f64(q.x, q.x), lm2_mul_f64(q.y, q.y)), lm2_mul_f64(q.z, q.z)), lm2_mul_f64(q.w, q.w));
}

LM2_API double lm2_quat_length_f64(lm2_quat_f64 q) {
  return lm2_sqrt_f64(lm2_quat_length_squared(q));
}

LM2_API lm2_v3_f64 lm2_quat_rotate_vector_f64(lm2_quat_f64 q, lm2_v3_f64 v) {
  // Use the formula: v' = q * v * q^-1
  // Optimized version: v' = v + 2 * cross(q.xyz, cross(q.xyz, v) + q.w * v)
  lm2_v3_f64 qv = {q.x, q.y, q.z};

  // cross(q.xyz, v)
  lm2_v3_f64 cross1 = lm2_v3_cross_f64(qv, v);

  // q.w * v
  lm2_v3_f64 wv = {lm2_mul_f64(q.w, v.x), lm2_mul_f64(q.w, v.y), lm2_mul_f64(q.w, v.z)};

  // cross(q.xyz, v) + q.w * v
  lm2_v3_f64 sum = {lm2_add_f64(cross1.x, wv.x), lm2_add_f64(cross1.y, wv.y), lm2_add_f64(cross1.z, wv.z)};

  // cross(q.xyz, sum)
  lm2_v3_f64 cross2 = lm2_v3_cross_f64(qv, sum);

  // 2 * cross2
  lm2_v3_f64 scaled = {lm2_mul_f64(2.0, cross2.x), lm2_mul_f64(2.0, cross2.y), lm2_mul_f64(2.0, cross2.z)};

  // v + scaled
  lm2_v3_f64 result = {lm2_add_f64(v.x, scaled.x), lm2_add_f64(v.y, scaled.y), lm2_add_f64(v.z, scaled.z)};
  return result;
}

LM2_API lm2_quat_f64 lm2_quat_slerp_f64(lm2_quat_f64 a, lm2_quat_f64 b, double t) {
  // Spherical linear interpolation
  double dot = lm2_quat_dot(a, b);

  // If the dot product is negative, negate one quaternion to take the shorter path
  if (dot < 0.0) {
    b.x = lm2_sub_f64(0.0, b.x);
    b.y = lm2_sub_f64(0.0, b.y);
    b.z = lm2_sub_f64(0.0, b.z);
    b.w = lm2_sub_f64(0.0, b.w);
    dot = lm2_sub_f64(0.0, dot);
  }

  // If quaternions are very close, use linear interpolation to avoid division by zero
  if (dot > 0.9995) {
    return lm2_quat_nlerp_f64(a, b, t);
  }

  // Clamp dot to avoid numerical errors with acos
  dot = lm2_clamp_f64(0.0, dot, 1.0);

  double theta = lm2_acos_f64(dot);
  double sin_theta = lm2_sin_f64(theta);
  double inv_sin_theta = lm2_div_f64(1.0, sin_theta);

  double w1 = lm2_mul_f64(lm2_sin_f64(lm2_mul_f64(lm2_sub_f64(1.0, t), theta)), inv_sin_theta);
  double w2 = lm2_mul_f64(lm2_sin_f64(lm2_mul_f64(t, theta)), inv_sin_theta);

  lm2_quat_f64 result;
  result.x = lm2_add_f64(lm2_mul_f64(a.x, w1), lm2_mul_f64(b.x, w2));
  result.y = lm2_add_f64(lm2_mul_f64(a.y, w1), lm2_mul_f64(b.y, w2));
  result.z = lm2_add_f64(lm2_mul_f64(a.z, w1), lm2_mul_f64(b.z, w2));
  result.w = lm2_add_f64(lm2_mul_f64(a.w, w1), lm2_mul_f64(b.w, w2));
  return result;
}

LM2_API lm2_quat_f64 lm2_quat_nlerp_f64(lm2_quat_f64 a, lm2_quat_f64 b, double t) {
  // Normalized linear interpolation
  double dot = lm2_quat_dot(a, b);

  // If the dot product is negative, negate one quaternion to take the shorter path
  if (dot < 0.0) {
    b.x = lm2_sub_f64(0.0, b.x);
    b.y = lm2_sub_f64(0.0, b.y);
    b.z = lm2_sub_f64(0.0, b.z);
    b.w = lm2_sub_f64(0.0, b.w);
  }

  double one_minus_t = lm2_sub_f64(1.0, t);

  lm2_quat_f64 result;
  result.x = lm2_add_f64(lm2_mul_f64(a.x, one_minus_t), lm2_mul_f64(b.x, t));
  result.y = lm2_add_f64(lm2_mul_f64(a.y, one_minus_t), lm2_mul_f64(b.y, t));
  result.z = lm2_add_f64(lm2_mul_f64(a.z, one_minus_t), lm2_mul_f64(b.z, t));
  result.w = lm2_add_f64(lm2_mul_f64(a.w, one_minus_t), lm2_mul_f64(b.w, t));

  return lm2_quat_normalize_f64(result);
}

LM2_API bool lm2_quat_equals_f64(lm2_quat_f64 a, lm2_quat_f64 b, double epsilon) {
  double dx = lm2_abs_f64(lm2_sub_f64(a.x, b.x));
  double dy = lm2_abs_f64(lm2_sub_f64(a.y, b.y));
  double dz = lm2_abs_f64(lm2_sub_f64(a.z, b.z));
  double dw = lm2_abs_f64(lm2_sub_f64(a.w, b.w));
  return (dx <= epsilon) && (dy <= epsilon) && (dz <= epsilon) && (dw <= epsilon);
}

// =============================================================================
// Quaternion Functions - f32
// =============================================================================

// Basic constructors
LM2_API lm2_quat_f32 lm2_quat_identity_f32(void) {
  lm2_quat_f32 q = {0.0f, 0.0f, 0.0f, 1.0f};
  return q;
}

LM2_API lm2_quat_f32 lm2_quat_zero_f32(void) {
  lm2_quat_f32 q = {0.0f, 0.0f, 0.0f, 0.0f};
  return q;
}

LM2_API lm2_quat_f32 lm2_quat_make_f32(float x, float y, float z, float w) {
  lm2_quat_f32 q = {x, y, z, w};
  return q;
}

// Conversions from other representations
LM2_API lm2_quat_f32 lm2_quat_from_axis_angle_f32(lm2_v3_f32 axis, float angle) {
  // Normalize the axis
  float len_sq = lm2_add_f32(lm2_add_f32(lm2_mul_f32(axis.x, axis.x), lm2_mul_f32(axis.y, axis.y)), lm2_mul_f32(axis.z, axis.z));
  float len = lm2_sqrt_f32(len_sq);
  LM2_ASSERT_UNSAFE(len > 0.0f);

  float inv_len = lm2_div_f32(1.0f, len);
  float nx = lm2_mul_f32(axis.x, inv_len);
  float ny = lm2_mul_f32(axis.y, inv_len);
  float nz = lm2_mul_f32(axis.z, inv_len);

  float half_angle = lm2_mul_f32(angle, 0.5f);
  float s = lm2_sin_f32(half_angle);
  float c = lm2_cos_f32(half_angle);

  lm2_quat_f32 q;
  q.x = lm2_mul_f32(nx, s);
  q.y = lm2_mul_f32(ny, s);
  q.z = lm2_mul_f32(nz, s);
  q.w = c;
  return q;
}

LM2_API lm2_quat_f32 lm2_quat_from_euler_f32(float pitch, float yaw, float roll) {
  // Convert Euler angles (pitch, yaw, roll) to quaternion
  // Rotation order: YXZ (yaw, pitch, roll)
  float half_pitch = lm2_mul_f32(pitch, 0.5f);
  float half_yaw = lm2_mul_f32(yaw, 0.5f);
  float half_roll = lm2_mul_f32(roll, 0.5f);

  float cp = lm2_cos_f32(half_pitch);
  float sp = lm2_sin_f32(half_pitch);
  float cy = lm2_cos_f32(half_yaw);
  float sy = lm2_sin_f32(half_yaw);
  float cr = lm2_cos_f32(half_roll);
  float sr = lm2_sin_f32(half_roll);

  lm2_quat_f32 q;
  q.w = lm2_sub_f32(lm2_add_f32(lm2_mul_f32(cr, lm2_mul_f32(cp, cy)), lm2_mul_f32(sr, lm2_mul_f32(sp, sy))), 0.0f);
  q.x = lm2_sub_f32(lm2_mul_f32(sr, lm2_mul_f32(cp, cy)), lm2_mul_f32(cr, lm2_mul_f32(sp, sy)));
  q.y = lm2_add_f32(lm2_mul_f32(cr, lm2_mul_f32(sp, cy)), lm2_mul_f32(sr, lm2_mul_f32(cp, sy)));
  q.z = lm2_sub_f32(lm2_mul_f32(cr, lm2_mul_f32(cp, sy)), lm2_mul_f32(sr, lm2_mul_f32(sp, cy)));
  return q;
}

LM2_API lm2_quat_f32 lm2_quat_from_euler_vec_f32(lm2_v3_f32 euler) {
  return lm2_quat_from_euler_f32(euler.x, euler.y, euler.z);
}

// Conversions to other representations
LM2_API void lm2_quat_to_axis_angle_f32(lm2_quat_f32 q, lm2_v3_f32* axis, float* angle) {
  LM2_ASSERT(axis != NULL && angle != NULL);

  float len_sq = lm2_add_f32(lm2_add_f32(lm2_mul_f32(q.x, q.x), lm2_mul_f32(q.y, q.y)), lm2_mul_f32(q.z, q.z));

  if (len_sq < 1e-10f) {
    // No rotation
    axis->x = 1.0f;
    axis->y = 0.0f;
    axis->z = 0.0f;
    *angle = 0.0f;
    return;
  }

  float len = lm2_sqrt_f32(len_sq);
  float inv_len = lm2_div_f32(1.0f, len);

  axis->x = lm2_mul_f32(q.x, inv_len);
  axis->y = lm2_mul_f32(q.y, inv_len);
  axis->z = lm2_mul_f32(q.z, inv_len);
  *angle = lm2_mul_f32(2.0f, lm2_atan2_f32(len, q.w));
}

LM2_API lm2_v3_f32 lm2_quat_to_euler_f32(lm2_quat_f32 q) {
  lm2_v3_f32 euler;

  // Roll (x-axis rotation)
  float sinr_cosp = lm2_mul_f32(2.0f, lm2_add_f32(lm2_mul_f32(q.w, q.x), lm2_mul_f32(q.y, q.z)));
  float cosr_cosp = lm2_sub_f32(1.0f, lm2_mul_f32(2.0f, lm2_add_f32(lm2_mul_f32(q.x, q.x), lm2_mul_f32(q.y, q.y))));
  euler.z = lm2_atan2_f32(sinr_cosp, cosr_cosp);

  // Pitch (y-axis rotation)
  float sinp = lm2_mul_f32(2.0f, lm2_sub_f32(lm2_mul_f32(q.w, q.y), lm2_mul_f32(q.z, q.x)));
  if (lm2_abs_f32(sinp) >= 1.0f) {
    euler.x = lm2_mul_f32(lm2_sign_f32(sinp), LM2_HPI_F32);  // Use 90 degrees if out of range
  } else {
    euler.x = lm2_asin_f32(sinp);
  }

  // Yaw (z-axis rotation)
  float siny_cosp = lm2_mul_f32(2.0f, lm2_add_f32(lm2_mul_f32(q.w, q.z), lm2_mul_f32(q.x, q.y)));
  float cosy_cosp = lm2_sub_f32(1.0f, lm2_mul_f32(2.0f, lm2_add_f32(lm2_mul_f32(q.y, q.y), lm2_mul_f32(q.z, q.z))));
  euler.y = lm2_atan2_f32(siny_cosp, cosy_cosp);

  return euler;
}

// Operations
LM2_API lm2_quat_f32 lm2_quat_conjugate_f32(lm2_quat_f32 q) {
  lm2_quat_f32 result;
  result.x = lm2_sub_f32(0.0f, q.x);
  result.y = lm2_sub_f32(0.0f, q.y);
  result.z = lm2_sub_f32(0.0f, q.z);
  result.w = q.w;
  return result;
}

LM2_API lm2_quat_f32 lm2_quat_inverse_f32(lm2_quat_f32 q) {
  float len_sq = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(q.x, q.x), lm2_mul_f32(q.y, q.y)), lm2_mul_f32(q.z, q.z)), lm2_mul_f32(q.w, q.w));
  LM2_ASSERT_UNSAFE(len_sq > 0.0f);

  float inv_len_sq = lm2_div_f32(1.0f, len_sq);

  lm2_quat_f32 result;
  result.x = lm2_mul_f32(lm2_sub_f32(0.0f, q.x), inv_len_sq);
  result.y = lm2_mul_f32(lm2_sub_f32(0.0f, q.y), inv_len_sq);
  result.z = lm2_mul_f32(lm2_sub_f32(0.0f, q.z), inv_len_sq);
  result.w = lm2_mul_f32(q.w, inv_len_sq);
  return result;
}

LM2_API lm2_quat_f32 lm2_quat_normalize_f32(lm2_quat_f32 q) {
  float len_sq = lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(q.x, q.x), lm2_mul_f32(q.y, q.y)), lm2_mul_f32(q.z, q.z)), lm2_mul_f32(q.w, q.w));
  LM2_ASSERT_UNSAFE(len_sq > 0.0f);

  float inv_len = lm2_div_f32(1.0f, lm2_sqrt_f32(len_sq));

  lm2_quat_f32 result;
  result.x = lm2_mul_f32(q.x, inv_len);
  result.y = lm2_mul_f32(q.y, inv_len);
  result.z = lm2_mul_f32(q.z, inv_len);
  result.w = lm2_mul_f32(q.w, inv_len);
  return result;
}

LM2_API lm2_quat_f32 lm2_quat_multiply_f32(lm2_quat_f32 a, lm2_quat_f32 b) {
  lm2_quat_f32 result;
  result.w = lm2_sub_f32(lm2_sub_f32(lm2_mul_f32(a.w, b.w), lm2_mul_f32(a.x, b.x)), lm2_add_f32(lm2_mul_f32(a.y, b.y), lm2_mul_f32(a.z, b.z)));
  result.x = lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.w, b.x), lm2_mul_f32(a.x, b.w)), lm2_sub_f32(lm2_mul_f32(a.y, b.z), lm2_mul_f32(a.z, b.y)));
  result.y = lm2_add_f32(lm2_sub_f32(lm2_mul_f32(a.w, b.y), lm2_mul_f32(a.x, b.z)), lm2_add_f32(lm2_mul_f32(a.y, b.w), lm2_mul_f32(a.z, b.x)));
  result.z = lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.w, b.z), lm2_mul_f32(a.x, b.y)), lm2_sub_f32(lm2_mul_f32(a.z, b.w), lm2_mul_f32(a.y, b.x)));
  return result;
}

LM2_API lm2_quat_f32 lm2_quat_add_f32(lm2_quat_f32 a, lm2_quat_f32 b) {
  lm2_quat_f32 result;
  result.x = lm2_add_f32(a.x, b.x);
  result.y = lm2_add_f32(a.y, b.y);
  result.z = lm2_add_f32(a.z, b.z);
  result.w = lm2_add_f32(a.w, b.w);
  return result;
}

LM2_API lm2_quat_f32 lm2_quat_sub_f32(lm2_quat_f32 a, lm2_quat_f32 b) {
  lm2_quat_f32 result;
  result.x = lm2_sub_f32(a.x, b.x);
  result.y = lm2_sub_f32(a.y, b.y);
  result.z = lm2_sub_f32(a.z, b.z);
  result.w = lm2_sub_f32(a.w, b.w);
  return result;
}

LM2_API lm2_quat_f32 lm2_quat_scale_f32(lm2_quat_f32 q, float s) {
  lm2_quat_f32 result;
  result.x = lm2_mul_f32(q.x, s);
  result.y = lm2_mul_f32(q.y, s);
  result.z = lm2_mul_f32(q.z, s);
  result.w = lm2_mul_f32(q.w, s);
  return result;
}

LM2_API float lm2_quat_dot_f32(lm2_quat_f32 a, lm2_quat_f32 b) {
  return lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(a.x, b.x), lm2_mul_f32(a.y, b.y)), lm2_mul_f32(a.z, b.z)), lm2_mul_f32(a.w, b.w));
}

LM2_API float lm2_quat_length_squared_f32(lm2_quat_f32 q) {
  return lm2_add_f32(lm2_add_f32(lm2_add_f32(lm2_mul_f32(q.x, q.x), lm2_mul_f32(q.y, q.y)), lm2_mul_f32(q.z, q.z)), lm2_mul_f32(q.w, q.w));
}

LM2_API float lm2_quat_length_f32(lm2_quat_f32 q) {
  return lm2_sqrt_f32(lm2_quat_length_squared(q));
}

LM2_API lm2_v3_f32 lm2_quat_rotate_vector_f32(lm2_quat_f32 q, lm2_v3_f32 v) {
  // Use the formula: v' = q * v * q^-1
  // Optimized version: v' = v + 2 * cross(q.xyz, cross(q.xyz, v) + q.w * v)
  lm2_v3_f32 qv = {q.x, q.y, q.z};

  // cross(q.xyz, v)
  lm2_v3_f32 cross1 = lm2_v3_cross_f32(qv, v);

  // q.w * v
  lm2_v3_f32 wv = {lm2_mul_f32(q.w, v.x), lm2_mul_f32(q.w, v.y), lm2_mul_f32(q.w, v.z)};

  // cross(q.xyz, v) + q.w * v
  lm2_v3_f32 sum = {lm2_add_f32(cross1.x, wv.x), lm2_add_f32(cross1.y, wv.y), lm2_add_f32(cross1.z, wv.z)};

  // cross(q.xyz, sum)
  lm2_v3_f32 cross2 = lm2_v3_cross_f32(qv, sum);

  // 2 * cross2
  lm2_v3_f32 scaled = {lm2_mul_f32(2.0f, cross2.x), lm2_mul_f32(2.0f, cross2.y), lm2_mul_f32(2.0f, cross2.z)};

  // v + scaled
  lm2_v3_f32 result = {lm2_add_f32(v.x, scaled.x), lm2_add_f32(v.y, scaled.y), lm2_add_f32(v.z, scaled.z)};
  return result;
}

LM2_API lm2_quat_f32 lm2_quat_slerp_f32(lm2_quat_f32 a, lm2_quat_f32 b, float t) {
  // Spherical linear interpolation
  float dot = lm2_quat_dot(a, b);

  // If the dot product is negative, negate one quaternion to take the shorter path
  if (dot < 0.0f) {
    b.x = lm2_sub_f32(0.0f, b.x);
    b.y = lm2_sub_f32(0.0f, b.y);
    b.z = lm2_sub_f32(0.0f, b.z);
    b.w = lm2_sub_f32(0.0f, b.w);
    dot = lm2_sub_f32(0.0f, dot);
  }

  // If quaternions are very close, use linear interpolation to avoid division by zero
  if (dot > 0.9995f) {
    return lm2_quat_nlerp_f32(a, b, t);
  }

  // Clamp dot to avoid numerical errors with acos
  dot = lm2_clamp_f32(0.0f, dot, 1.0f);

  float theta = lm2_acos_f32(dot);
  float sin_theta = lm2_sin_f32(theta);
  float inv_sin_theta = lm2_div_f32(1.0f, sin_theta);

  float w1 = lm2_mul_f32(lm2_sin_f32(lm2_mul_f32(lm2_sub_f32(1.0f, t), theta)), inv_sin_theta);
  float w2 = lm2_mul_f32(lm2_sin_f32(lm2_mul_f32(t, theta)), inv_sin_theta);

  lm2_quat_f32 result;
  result.x = lm2_add_f32(lm2_mul_f32(a.x, w1), lm2_mul_f32(b.x, w2));
  result.y = lm2_add_f32(lm2_mul_f32(a.y, w1), lm2_mul_f32(b.y, w2));
  result.z = lm2_add_f32(lm2_mul_f32(a.z, w1), lm2_mul_f32(b.z, w2));
  result.w = lm2_add_f32(lm2_mul_f32(a.w, w1), lm2_mul_f32(b.w, w2));
  return result;
}

LM2_API lm2_quat_f32 lm2_quat_nlerp_f32(lm2_quat_f32 a, lm2_quat_f32 b, float t) {
  // Normalized linear interpolation
  float dot = lm2_quat_dot(a, b);

  // If the dot product is negative, negate one quaternion to take the shorter path
  if (dot < 0.0f) {
    b.x = lm2_sub_f32(0.0f, b.x);
    b.y = lm2_sub_f32(0.0f, b.y);
    b.z = lm2_sub_f32(0.0f, b.z);
    b.w = lm2_sub_f32(0.0f, b.w);
  }

  float one_minus_t = lm2_sub_f32(1.0f, t);

  lm2_quat_f32 result;
  result.x = lm2_add_f32(lm2_mul_f32(a.x, one_minus_t), lm2_mul_f32(b.x, t));
  result.y = lm2_add_f32(lm2_mul_f32(a.y, one_minus_t), lm2_mul_f32(b.y, t));
  result.z = lm2_add_f32(lm2_mul_f32(a.z, one_minus_t), lm2_mul_f32(b.z, t));
  result.w = lm2_add_f32(lm2_mul_f32(a.w, one_minus_t), lm2_mul_f32(b.w, t));

  return lm2_quat_normalize_f32(result);
}

LM2_API bool lm2_quat_equals_f32(lm2_quat_f32 a, lm2_quat_f32 b, float epsilon) {
  float dx = lm2_abs_f32(lm2_sub_f32(a.x, b.x));
  float dy = lm2_abs_f32(lm2_sub_f32(a.y, b.y));
  float dz = lm2_abs_f32(lm2_sub_f32(a.z, b.z));
  float dw = lm2_abs_f32(lm2_sub_f32(a.w, b.w));
  return (dx <= epsilon) && (dy <= epsilon) && (dz <= epsilon) && (dw <= epsilon);
}
