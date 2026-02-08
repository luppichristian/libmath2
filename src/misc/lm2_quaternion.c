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
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/scalar/lm2_trigonometry.h>
#include <lm2/vectors/lm2_vector_specifics.h>

// =============================================================================
// Implementation Macros
// =============================================================================

#define _LM2_IMPL_QUAT_BASIC(quat_type, scalar_type, scalar_suffix)                                \
  LM2_API quat_type quat_type##_identity(void) {                                                   \
    quat_type result;                                                                              \
    result.x = (scalar_type)0;                                                                     \
    result.y = (scalar_type)0;                                                                     \
    result.z = (scalar_type)0;                                                                     \
    result.w = (scalar_type)1;                                                                     \
    return result;                                                                                 \
  }                                                                                                \
  LM2_API quat_type quat_type##_zero(void) {                                                       \
    quat_type result;                                                                              \
    result.x = (scalar_type)0;                                                                     \
    result.y = (scalar_type)0;                                                                     \
    result.z = (scalar_type)0;                                                                     \
    result.w = (scalar_type)0;                                                                     \
    return result;                                                                                 \
  }                                                                                                \
  LM2_API quat_type quat_type##_make(scalar_type x, scalar_type y, scalar_type z, scalar_type w) { \
    quat_type result;                                                                              \
    result.x = x;                                                                                  \
    result.y = y;                                                                                  \
    result.z = z;                                                                                  \
    result.w = w;                                                                                  \
    return result;                                                                                 \
  }

#define _LM2_IMPL_QUAT_FROM(quat_type, scalar_type, scalar_suffix, vec3_type)                                                                                       \
  LM2_API quat_type quat_type##_from_axis_angle(vec3_type axis, scalar_type angle) {                                                                                \
    vec3_type normalized = lm2_normalize_##vec3_type(axis);                                                                                                         \
    scalar_type half_angle = lm2_mul_##scalar_suffix(angle, (scalar_type)0.5);                                                                                      \
    scalar_type s = lm2_sin_##scalar_suffix(half_angle);                                                                                                            \
    scalar_type c = lm2_cos_##scalar_suffix(half_angle);                                                                                                            \
    quat_type result;                                                                                                                                               \
    result.x = lm2_mul_##scalar_suffix(normalized.x, s);                                                                                                            \
    result.y = lm2_mul_##scalar_suffix(normalized.y, s);                                                                                                            \
    result.z = lm2_mul_##scalar_suffix(normalized.z, s);                                                                                                            \
    result.w = c;                                                                                                                                                   \
    return result;                                                                                                                                                  \
  }                                                                                                                                                                 \
  LM2_API quat_type quat_type##_from_euler(scalar_type pitch, scalar_type yaw, scalar_type roll) {                                                                  \
    scalar_type half_pitch = lm2_mul_##scalar_suffix(pitch, (scalar_type)0.5);                                                                                      \
    scalar_type half_yaw = lm2_mul_##scalar_suffix(yaw, (scalar_type)0.5);                                                                                          \
    scalar_type half_roll = lm2_mul_##scalar_suffix(roll, (scalar_type)0.5);                                                                                        \
    scalar_type cp = lm2_cos_##scalar_suffix(half_pitch);                                                                                                           \
    scalar_type sp = lm2_sin_##scalar_suffix(half_pitch);                                                                                                           \
    scalar_type cy = lm2_cos_##scalar_suffix(half_yaw);                                                                                                             \
    scalar_type sy = lm2_sin_##scalar_suffix(half_yaw);                                                                                                             \
    scalar_type cr = lm2_cos_##scalar_suffix(half_roll);                                                                                                            \
    scalar_type sr = lm2_sin_##scalar_suffix(half_roll);                                                                                                            \
    quat_type result;                                                                                                                                               \
    result.w = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(lm2_mul_##scalar_suffix(cr, cp), cy), lm2_mul_##scalar_suffix(lm2_mul_##scalar_suffix(sr, sp), sy)); \
    result.x = lm2_add_##scalar_suffix(lm2_mul_##scalar_suffix(lm2_mul_##scalar_suffix(sr, cp), cy), lm2_mul_##scalar_suffix(lm2_mul_##scalar_suffix(cr, sp), sy)); \
    result.y = lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(lm2_mul_##scalar_suffix(cr, sp), cy), lm2_mul_##scalar_suffix(lm2_mul_##scalar_suffix(sr, cp), sy)); \
    result.z = lm2_add_##scalar_suffix(lm2_mul_##scalar_suffix(lm2_mul_##scalar_suffix(cr, cp), sy), lm2_mul_##scalar_suffix(lm2_mul_##scalar_suffix(sr, sp), cy)); \
    return result;                                                                                                                                                  \
  }                                                                                                                                                                 \
  LM2_API quat_type quat_type##_from_euler_vec(vec3_type euler) {                                                                                                   \
    return quat_type##_from_euler(euler.x, euler.y, euler.z);                                                                                                       \
  }

#define _LM2_IMPL_QUAT_TO(quat_type, scalar_type, scalar_suffix, vec3_type)                                                                                                                                  \
  LM2_API void quat_type##_to_axis_angle(quat_type q, vec3_type* axis, scalar_type* angle) {                                                                                                                 \
    LM2_ASSERT(axis != NULL);                                                                                                                                                                                \
    LM2_ASSERT(angle != NULL);                                                                                                                                                                               \
    scalar_type s = lm2_sqrt_##scalar_suffix(lm2_sub_##scalar_suffix((scalar_type)1, lm2_mul_##scalar_suffix(q.w, q.w)));                                                                                    \
    if (s < (scalar_type)0.001) {                                                                                                                                                                            \
      axis->x = q.x;                                                                                                                                                                                         \
      axis->y = q.y;                                                                                                                                                                                         \
      axis->z = q.z;                                                                                                                                                                                         \
    } else {                                                                                                                                                                                                 \
      scalar_type inv_s = lm2_div_##scalar_suffix((scalar_type)1, s);                                                                                                                                        \
      axis->x = lm2_mul_##scalar_suffix(q.x, inv_s);                                                                                                                                                         \
      axis->y = lm2_mul_##scalar_suffix(q.y, inv_s);                                                                                                                                                         \
      axis->z = lm2_mul_##scalar_suffix(q.z, inv_s);                                                                                                                                                         \
    }                                                                                                                                                                                                        \
    *angle = lm2_mul_##scalar_suffix(lm2_acos_##scalar_suffix(q.w), (scalar_type)2);                                                                                                                         \
  }                                                                                                                                                                                                          \
  LM2_API vec3_type quat_type##_to_euler(quat_type q) {                                                                                                                                                      \
    vec3_type result;                                                                                                                                                                                        \
    scalar_type sinr_cosp = lm2_mul_##scalar_suffix((scalar_type)2, lm2_add_##scalar_suffix(lm2_mul_##scalar_suffix(q.w, q.x), lm2_mul_##scalar_suffix(q.y, q.z)));                                          \
    scalar_type cosr_cosp = lm2_sub_##scalar_suffix((scalar_type)1, lm2_mul_##scalar_suffix((scalar_type)2, lm2_add_##scalar_suffix(lm2_mul_##scalar_suffix(q.x, q.x), lm2_mul_##scalar_suffix(q.y, q.y)))); \
    result.x = lm2_atan2_##scalar_suffix(sinr_cosp, cosr_cosp);                                                                                                                                              \
    scalar_type sinp = lm2_mul_##scalar_suffix((scalar_type)2, lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(q.w, q.y), lm2_mul_##scalar_suffix(q.z, q.x)));                                               \
    if (lm2_abs_##scalar_suffix(sinp) >= (scalar_type)1) {                                                                                                                                                   \
      if (sinp >= (scalar_type)0) {                                                                                                                                                                          \
        result.y = (scalar_type)1.57079632679489661923;                                                                                                                                                      \
      } else {                                                                                                                                                                                               \
        result.y = (scalar_type) - 1.57079632679489661923;                                                                                                                                                   \
      }                                                                                                                                                                                                      \
    } else {                                                                                                                                                                                                 \
      result.y = lm2_asin_##scalar_suffix(sinp);                                                                                                                                                             \
    }                                                                                                                                                                                                        \
    scalar_type siny_cosp = lm2_mul_##scalar_suffix((scalar_type)2, lm2_add_##scalar_suffix(lm2_mul_##scalar_suffix(q.w, q.z), lm2_mul_##scalar_suffix(q.x, q.y)));                                          \
    scalar_type cosy_cosp = lm2_sub_##scalar_suffix((scalar_type)1, lm2_mul_##scalar_suffix((scalar_type)2, lm2_add_##scalar_suffix(lm2_mul_##scalar_suffix(q.y, q.y), lm2_mul_##scalar_suffix(q.z, q.z)))); \
    result.z = lm2_atan2_##scalar_suffix(siny_cosp, cosy_cosp);                                                                                                                                              \
    return result;                                                                                                                                                                                           \
  }

#define _LM2_IMPL_QUAT_OPS(quat_type, scalar_type, scalar_suffix, vec3_type)                                                                                                                                                          \
  LM2_API quat_type quat_type##_conjugate(quat_type q) {                                                                                                                                                                              \
    quat_type result;                                                                                                                                                                                                                 \
    result.x = lm2_neg_##scalar_suffix(q.x);                                                                                                                                                                                          \
    result.y = lm2_neg_##scalar_suffix(q.y);                                                                                                                                                                                          \
    result.z = lm2_neg_##scalar_suffix(q.z);                                                                                                                                                                                          \
    result.w = q.w;                                                                                                                                                                                                                   \
    return result;                                                                                                                                                                                                                    \
  }                                                                                                                                                                                                                                   \
  LM2_API quat_type quat_type##_inverse(quat_type q) {                                                                                                                                                                                \
    scalar_type len_sq = quat_type##_length_squared(q);                                                                                                                                                                               \
    LM2_ASSERT_UNSAFE(len_sq > (scalar_type)0);                                                                                                                                                                                       \
    scalar_type inv_len_sq = lm2_div_##scalar_suffix((scalar_type)1, len_sq);                                                                                                                                                         \
    quat_type conj = quat_type##_conjugate(q);                                                                                                                                                                                        \
    return quat_type##_scale(conj, inv_len_sq);                                                                                                                                                                                       \
  }                                                                                                                                                                                                                                   \
  LM2_API quat_type quat_type##_normalize(quat_type q) {                                                                                                                                                                              \
    scalar_type len = quat_type##_length(q);                                                                                                                                                                                          \
    LM2_ASSERT_UNSAFE(len > (scalar_type)0);                                                                                                                                                                                          \
    scalar_type inv_len = lm2_div_##scalar_suffix((scalar_type)1, len);                                                                                                                                                               \
    return quat_type##_scale(q, inv_len);                                                                                                                                                                                             \
  }                                                                                                                                                                                                                                   \
  LM2_API quat_type quat_type##_multiply(quat_type a, quat_type b) {                                                                                                                                                                  \
    quat_type result;                                                                                                                                                                                                                 \
    result.w = lm2_sub_##scalar_suffix(lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a.w, b.w), lm2_mul_##scalar_suffix(a.x, b.x)), lm2_add_##scalar_suffix(lm2_mul_##scalar_suffix(a.y, b.y), lm2_mul_##scalar_suffix(a.z, b.z))); \
    result.x = lm2_add_##scalar_suffix(lm2_add_##scalar_suffix(lm2_mul_##scalar_suffix(a.w, b.x), lm2_mul_##scalar_suffix(a.x, b.w)), lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a.y, b.z), lm2_mul_##scalar_suffix(a.z, b.y))); \
    result.y = lm2_add_##scalar_suffix(lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a.w, b.y), lm2_mul_##scalar_suffix(a.x, b.z)), lm2_add_##scalar_suffix(lm2_mul_##scalar_suffix(a.y, b.w), lm2_mul_##scalar_suffix(a.z, b.x))); \
    result.z = lm2_add_##scalar_suffix(lm2_add_##scalar_suffix(lm2_mul_##scalar_suffix(a.w, b.z), lm2_mul_##scalar_suffix(a.x, b.y)), lm2_sub_##scalar_suffix(lm2_mul_##scalar_suffix(a.z, b.w), lm2_mul_##scalar_suffix(a.y, b.x))); \
    return result;                                                                                                                                                                                                                    \
  }                                                                                                                                                                                                                                   \
  LM2_API quat_type quat_type##_add(quat_type a, quat_type b) {                                                                                                                                                                       \
    quat_type result;                                                                                                                                                                                                                 \
    result.x = lm2_add_##scalar_suffix(a.x, b.x);                                                                                                                                                                                     \
    result.y = lm2_add_##scalar_suffix(a.y, b.y);                                                                                                                                                                                     \
    result.z = lm2_add_##scalar_suffix(a.z, b.z);                                                                                                                                                                                     \
    result.w = lm2_add_##scalar_suffix(a.w, b.w);                                                                                                                                                                                     \
    return result;                                                                                                                                                                                                                    \
  }                                                                                                                                                                                                                                   \
  LM2_API quat_type quat_type##_sub(quat_type a, quat_type b) {                                                                                                                                                                       \
    quat_type result;                                                                                                                                                                                                                 \
    result.x = lm2_sub_##scalar_suffix(a.x, b.x);                                                                                                                                                                                     \
    result.y = lm2_sub_##scalar_suffix(a.y, b.y);                                                                                                                                                                                     \
    result.z = lm2_sub_##scalar_suffix(a.z, b.z);                                                                                                                                                                                     \
    result.w = lm2_sub_##scalar_suffix(a.w, b.w);                                                                                                                                                                                     \
    return result;                                                                                                                                                                                                                    \
  }                                                                                                                                                                                                                                   \
  LM2_API quat_type quat_type##_scale(quat_type q, scalar_type s) {                                                                                                                                                                   \
    quat_type result;                                                                                                                                                                                                                 \
    result.x = lm2_mul_##scalar_suffix(q.x, s);                                                                                                                                                                                       \
    result.y = lm2_mul_##scalar_suffix(q.y, s);                                                                                                                                                                                       \
    result.z = lm2_mul_##scalar_suffix(q.z, s);                                                                                                                                                                                       \
    result.w = lm2_mul_##scalar_suffix(q.w, s);                                                                                                                                                                                       \
    return result;                                                                                                                                                                                                                    \
  }                                                                                                                                                                                                                                   \
  LM2_API scalar_type quat_type##_dot(quat_type a, quat_type b) {                                                                                                                                                                     \
    return lm2_add_##scalar_suffix(lm2_add_##scalar_suffix(lm2_mul_##scalar_suffix(a.x, b.x), lm2_mul_##scalar_suffix(a.y, b.y)), lm2_add_##scalar_suffix(lm2_mul_##scalar_suffix(a.z, b.z), lm2_mul_##scalar_suffix(a.w, b.w)));     \
  }                                                                                                                                                                                                                                   \
  LM2_API scalar_type quat_type##_length_squared(quat_type q) {                                                                                                                                                                       \
    return lm2_add_##scalar_suffix(lm2_add_##scalar_suffix(lm2_mul_##scalar_suffix(q.x, q.x), lm2_mul_##scalar_suffix(q.y, q.y)), lm2_add_##scalar_suffix(lm2_mul_##scalar_suffix(q.z, q.z), lm2_mul_##scalar_suffix(q.w, q.w)));     \
  }                                                                                                                                                                                                                                   \
  LM2_API scalar_type quat_type##_length(quat_type q) {                                                                                                                                                                               \
    return lm2_sqrt_##scalar_suffix(quat_type##_length_squared(q));                                                                                                                                                                   \
  }                                                                                                                                                                                                                                   \
  LM2_API vec3_type quat_type##_rotate_vector(quat_type q, vec3_type v) {                                                                                                                                                             \
    vec3_type qvec = {q.x, q.y, q.z};                                                                                                                                                                                                 \
    vec3_type cross1 = lm2_cross_##vec3_type(qvec, v);                                                                                                                                                                                \
    vec3_type cross2 = lm2_cross_##vec3_type(qvec, cross1);                                                                                                                                                                           \
    cross1 = lm2_mul_##vec3_type##_##scalar_suffix(cross1, lm2_mul_##scalar_suffix(q.w, (scalar_type)2));                                                                                                                             \
    cross2 = lm2_mul_##vec3_type##_##scalar_suffix(cross2, (scalar_type)2);                                                                                                                                                           \
    return lm2_add_##vec3_type(lm2_add_##vec3_type(v, cross1), cross2);                                                                                                                                                               \
  }                                                                                                                                                                                                                                   \
  LM2_API quat_type quat_type##_slerp(quat_type a, quat_type b, scalar_type t) {                                                                                                                                                      \
    scalar_type dot = quat_type##_dot(a, b);                                                                                                                                                                                          \
    if (dot < (scalar_type)0) {                                                                                                                                                                                                       \
      b = quat_type##_scale(b, (scalar_type) - 1);                                                                                                                                                                                    \
      dot = lm2_neg_##scalar_suffix(dot);                                                                                                                                                                                             \
    }                                                                                                                                                                                                                                 \
    if (dot > (scalar_type)0.9995) {                                                                                                                                                                                                  \
      return quat_type##_nlerp(a, b, t);                                                                                                                                                                                              \
    }                                                                                                                                                                                                                                 \
    scalar_type theta = lm2_acos_##scalar_suffix(dot);                                                                                                                                                                                \
    scalar_type theta_t = lm2_mul_##scalar_suffix(theta, t);                                                                                                                                                                          \
    scalar_type sin_theta = lm2_sin_##scalar_suffix(theta);                                                                                                                                                                           \
    scalar_type sin_theta_t = lm2_sin_##scalar_suffix(theta_t);                                                                                                                                                                       \
    scalar_type s0 = lm2_div_##scalar_suffix(lm2_cos_##scalar_suffix(theta_t), sin_theta);                                                                                                                                            \
    s0 = lm2_sub_##scalar_suffix(s0, lm2_div_##scalar_suffix(lm2_mul_##scalar_suffix(dot, sin_theta_t), sin_theta));                                                                                                                  \
    scalar_type s1 = lm2_div_##scalar_suffix(sin_theta_t, sin_theta);                                                                                                                                                                 \
    quat_type q0 = quat_type##_scale(a, s0);                                                                                                                                                                                          \
    quat_type q1 = quat_type##_scale(b, s1);                                                                                                                                                                                          \
    return quat_type##_add(q0, q1);                                                                                                                                                                                                   \
  }                                                                                                                                                                                                                                   \
  LM2_API quat_type quat_type##_nlerp(quat_type a, quat_type b, scalar_type t) {                                                                                                                                                      \
    scalar_type one_minus_t = lm2_sub_##scalar_suffix((scalar_type)1, t);                                                                                                                                                             \
    quat_type result = quat_type##_add(quat_type##_scale(a, one_minus_t), quat_type##_scale(b, t));                                                                                                                                   \
    return quat_type##_normalize(result);                                                                                                                                                                                             \
  }                                                                                                                                                                                                                                   \
  LM2_API bool quat_type##_equals(quat_type a, quat_type b, scalar_type epsilon) {                                                                                                                                                    \
    scalar_type dx = lm2_abs_##scalar_suffix(lm2_sub_##scalar_suffix(a.x, b.x));                                                                                                                                                      \
    scalar_type dy = lm2_abs_##scalar_suffix(lm2_sub_##scalar_suffix(a.y, b.y));                                                                                                                                                      \
    scalar_type dz = lm2_abs_##scalar_suffix(lm2_sub_##scalar_suffix(a.z, b.z));                                                                                                                                                      \
    scalar_type dw = lm2_abs_##scalar_suffix(lm2_sub_##scalar_suffix(a.w, b.w));                                                                                                                                                      \
    return (dx <= epsilon) && (dy <= epsilon) && (dz <= epsilon) && (dw <= epsilon);                                                                                                                                                  \
  }

// =============================================================================
// Quaternion Implementations
// =============================================================================

_LM2_IMPL_QUAT_BASIC(lm2_quatf64, double, f64)
_LM2_IMPL_QUAT_BASIC(lm2_quatf32, float, f32)

_LM2_IMPL_QUAT_FROM(lm2_quatf64, double, f64, lm2_v3f64)
_LM2_IMPL_QUAT_FROM(lm2_quatf32, float, f32, lm2_v3f32)

_LM2_IMPL_QUAT_TO(lm2_quatf64, double, f64, lm2_v3f64)
_LM2_IMPL_QUAT_TO(lm2_quatf32, float, f32, lm2_v3f32)

_LM2_IMPL_QUAT_OPS(lm2_quatf64, double, f64, lm2_v3f64)
_LM2_IMPL_QUAT_OPS(lm2_quatf32, float, f32, lm2_v3f32)
