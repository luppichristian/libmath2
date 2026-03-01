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

#include "lm2/camera/lm2_camera2.h"
#include "lm2/camera/lm2_camera3.h"
#include "lm2/geometry2d/lm2_aabb2.h"
#include "lm2/geometry2d/lm2_capsule2.h"
#include "lm2/geometry2d/lm2_circle.h"
#include "lm2/geometry2d/lm2_edge2.h"
#include "lm2/geometry2d/lm2_manifold2.h"
#include "lm2/geometry2d/lm2_plane2.h"
#include "lm2/geometry2d/lm2_polygon.h"
#include "lm2/geometry2d/lm2_raycast2.h"
#include "lm2/geometry2d/lm2_shape2.h"
#include "lm2/geometry2d/lm2_triangle2.h"
#include "lm2/geometry2d/lm2_triangle2_geometry.h"
#include "lm2/geometry3d/lm2_aabb3.h"
#include "lm2/geometry3d/lm2_capsule3.h"
#include "lm2/geometry3d/lm2_edge3.h"
#include "lm2/geometry3d/lm2_plane3.h"
#include "lm2/geometry3d/lm2_raycast3.h"
#include "lm2/geometry3d/lm2_shape3.h"
#include "lm2/geometry3d/lm2_sphere.h"
#include "lm2/geometry3d/lm2_triangle3.h"
#include "lm2/geometry3d/lm2_triangle3_geometry.h"
#include "lm2/lm2_base.h"
#include "lm2/lm2_constants.h"
#include "lm2/matrices/lm2_matrix3x2.h"
#include "lm2/matrices/lm2_matrix3x3.h"
#include "lm2/matrices/lm2_matrix4x4.h"
#include "lm2/misc/lm2_bezier_curves.h"
#include "lm2/misc/lm2_easings.h"
#include "lm2/misc/lm2_hash.h"
#include "lm2/misc/lm2_noise.h"
#include "lm2/misc/lm2_quaternion.h"
#include "lm2/ranges/lm2_range2.h"
#include "lm2/ranges/lm2_range3.h"
#include "lm2/ranges/lm2_range4.h"
#include "lm2/ranges/lm2_range_conversions.h"
#include "lm2/scalar/lm2_safe_ops.h"
#include "lm2/scalar/lm2_scalar.h"
#include "lm2/scalar/lm2_trigonometry.h"
#include "lm2/vectors/lm2_vector2.h"
#include "lm2/vectors/lm2_vector3.h"
#include "lm2/vectors/lm2_vector4.h"
#include "lm2/vectors/lm2_vector_conversions.h"
#include "lm2/vectors/lm2_vector_specifics.h"

#if defined(__cplusplus) && !defined(LM2_NO_CPP_OPERATORS)

// =============================================================================
// Vector Operators
// =============================================================================

// Unary negation - signed types only
// VT = C++ type (e.g. lm2_v2_f64), VEC = API base (e.g. v2), T = type suffix (e.g. f64)
#  define LM2_VEC_NEG_OP(VT, VEC, T)   \
    static inline VT operator-(VT v) { \
      return lm2_##VEC##_neg_##T(v);   \
    }

// Vector-vector binary operators
#  define LM2_VEC_BIN_VV(VT, VEC, T)         \
    static inline VT operator+(VT a, VT b) { \
      return lm2_##VEC##_add_##T(a, b);      \
    }                                        \
    static inline VT operator-(VT a, VT b) { \
      return lm2_##VEC##_sub_##T(a, b);      \
    }                                        \
    static inline VT operator*(VT a, VT b) { \
      return lm2_##VEC##_mul_##T(a, b);      \
    }                                        \
    static inline VT operator/(VT a, VT b) { \
      return lm2_##VEC##_div_##T(a, b);      \
    }

// Vector-scalar binary operators
#  define LM2_VEC_BIN_VS(VT, VEC, T, ST)     \
    static inline VT operator+(VT v, ST s) { \
      return lm2_##VEC##_add_s_##T(v, s);    \
    }                                        \
    static inline VT operator-(VT v, ST s) { \
      return lm2_##VEC##_sub_s_##T(v, s);    \
    }                                        \
    static inline VT operator*(VT v, ST s) { \
      return lm2_##VEC##_mul_s_##T(v, s);    \
    }                                        \
    static inline VT operator/(VT v, ST s) { \
      return lm2_##VEC##_div_s_##T(v, s);    \
    }

// Scalar-vector binary operators
#  define LM2_VEC_BIN_SV(VT, VEC, T, ST)                       \
    static inline VT operator+(ST s, VT v) {                   \
      return lm2_##VEC##_add_s_##T(v, s);                      \
    }                                                          \
    static inline VT operator*(ST s, VT v) {                   \
      return lm2_##VEC##_mul_s_##T(v, s);                      \
    }                                                          \
    static inline VT operator-(ST s, VT v) {                   \
      return lm2_##VEC##_sub_##T(lm2_##VEC##_splat_##T(s), v); \
    }                                                          \
    static inline VT operator/(ST s, VT v) {                   \
      return lm2_##VEC##_div_##T(lm2_##VEC##_splat_##T(s), v); \
    }

// Compound assignment operators
#  define LM2_VEC_COMPOUND(VT, VEC, T, ST)      \
    static inline VT& operator+=(VT& a, VT b) { \
      a = lm2_##VEC##_add_##T(a, b);            \
      return a;                                 \
    }                                           \
    static inline VT& operator-=(VT& a, VT b) { \
      a = lm2_##VEC##_sub_##T(a, b);            \
      return a;                                 \
    }                                           \
    static inline VT& operator*=(VT& a, VT b) { \
      a = lm2_##VEC##_mul_##T(a, b);            \
      return a;                                 \
    }                                           \
    static inline VT& operator/=(VT& a, VT b) { \
      a = lm2_##VEC##_div_##T(a, b);            \
      return a;                                 \
    }                                           \
    static inline VT& operator+=(VT& v, ST s) { \
      v = lm2_##VEC##_add_s_##T(v, s);          \
      return v;                                 \
    }                                           \
    static inline VT& operator-=(VT& v, ST s) { \
      v = lm2_##VEC##_sub_s_##T(v, s);          \
      return v;                                 \
    }                                           \
    static inline VT& operator*=(VT& v, ST s) { \
      v = lm2_##VEC##_mul_s_##T(v, s);          \
      return v;                                 \
    }                                           \
    static inline VT& operator/=(VT& v, ST s) { \
      v = lm2_##VEC##_div_s_##T(v, s);          \
      return v;                                 \
    }

// Complete vector operator set for signed types
#  define LM2_VEC_OPS_SIGNED(VT, VEC, T, ST) \
    LM2_VEC_NEG_OP(VT, VEC, T)               \
    LM2_VEC_BIN_VV(VT, VEC, T)               \
    LM2_VEC_BIN_VS(VT, VEC, T, ST)           \
    LM2_VEC_BIN_SV(VT, VEC, T, ST)           \
    LM2_VEC_COMPOUND(VT, VEC, T, ST)

// Complete vector operator set for unsigned types
#  define LM2_VEC_OPS_UNSIGNED(VT, VEC, T, ST) \
    LM2_VEC_BIN_VV(VT, VEC, T)                 \
    LM2_VEC_BIN_VS(VT, VEC, T, ST)             \
    LM2_VEC_BIN_SV(VT, VEC, T, ST)             \
    LM2_VEC_COMPOUND(VT, VEC, T, ST)

// Vector2 operators
LM2_VEC_OPS_SIGNED(lm2_v2_f64, v2, f64, double)
LM2_VEC_OPS_SIGNED(lm2_v2_f32, v2, f32, float)
LM2_VEC_OPS_SIGNED(lm2_v2_i64, v2, i64, int64_t)
LM2_VEC_OPS_SIGNED(lm2_v2_i32, v2, i32, int32_t)
LM2_VEC_OPS_SIGNED(lm2_v2_i16, v2, i16, int16_t)
LM2_VEC_OPS_SIGNED(lm2_v2_i8, v2, i8, int8_t)
LM2_VEC_OPS_UNSIGNED(lm2_v2_u64, v2, u64, uint64_t)
LM2_VEC_OPS_UNSIGNED(lm2_v2_u32, v2, u32, uint32_t)
LM2_VEC_OPS_UNSIGNED(lm2_v2_u16, v2, u16, uint16_t)
LM2_VEC_OPS_UNSIGNED(lm2_v2_u8, v2, u8, uint8_t)

// Vector3 operators
LM2_VEC_OPS_SIGNED(lm2_v3_f64, v3, f64, double)
LM2_VEC_OPS_SIGNED(lm2_v3_f32, v3, f32, float)
LM2_VEC_OPS_SIGNED(lm2_v3_i64, v3, i64, int64_t)
LM2_VEC_OPS_SIGNED(lm2_v3_i32, v3, i32, int32_t)
LM2_VEC_OPS_SIGNED(lm2_v3_i16, v3, i16, int16_t)
LM2_VEC_OPS_SIGNED(lm2_v3_i8, v3, i8, int8_t)
LM2_VEC_OPS_UNSIGNED(lm2_v3_u64, v3, u64, uint64_t)
LM2_VEC_OPS_UNSIGNED(lm2_v3_u32, v3, u32, uint32_t)
LM2_VEC_OPS_UNSIGNED(lm2_v3_u16, v3, u16, uint16_t)
LM2_VEC_OPS_UNSIGNED(lm2_v3_u8, v3, u8, uint8_t)

// Vector4 operators
LM2_VEC_OPS_SIGNED(lm2_v4_f64, v4, f64, double)
LM2_VEC_OPS_SIGNED(lm2_v4_f32, v4, f32, float)
LM2_VEC_OPS_SIGNED(lm2_v4_i64, v4, i64, int64_t)
LM2_VEC_OPS_SIGNED(lm2_v4_i32, v4, i32, int32_t)
LM2_VEC_OPS_SIGNED(lm2_v4_i16, v4, i16, int16_t)
LM2_VEC_OPS_SIGNED(lm2_v4_i8, v4, i8, int8_t)
LM2_VEC_OPS_UNSIGNED(lm2_v4_u64, v4, u64, uint64_t)
LM2_VEC_OPS_UNSIGNED(lm2_v4_u32, v4, u32, uint32_t)
LM2_VEC_OPS_UNSIGNED(lm2_v4_u16, v4, u16, uint16_t)
LM2_VEC_OPS_UNSIGNED(lm2_v4_u8, v4, u8, uint8_t)

// =============================================================================
// Matrix Operators
// =============================================================================

// Matrix3x2 operators
static inline lm2_m3x2_f64 operator*(const lm2_m3x2_f64& a, const lm2_m3x2_f64& b) {
  return lm2_m3x2_mul_f64(a, b);
}
static inline lm2_m3x2_f32 operator*(const lm2_m3x2_f32& a, const lm2_m3x2_f32& b) {
  return lm2_m3x2_mul_f32(a, b);
}
static inline lm2_v2_f64 operator*(const lm2_m3x2_f64& m, const lm2_v2_f64& v) {
  return lm2_m3x2_transform_point_f64(m, v);
}
static inline lm2_v2_f32 operator*(const lm2_m3x2_f32& m, const lm2_v2_f32& v) {
  return lm2_m3x2_transform_point_f32(m, v);
}
static inline lm2_m3x2_f64& operator*=(lm2_m3x2_f64& a, const lm2_m3x2_f64& b) {
  a = lm2_m3x2_mul_f64(a, b);
  return a;
}
static inline lm2_m3x2_f32& operator*=(lm2_m3x2_f32& a, const lm2_m3x2_f32& b) {
  a = lm2_m3x2_mul_f32(a, b);
  return a;
}

// Matrix3x3 operators
static inline lm2_m3x3_f64 operator*(const lm2_m3x3_f64& a, const lm2_m3x3_f64& b) {
  return lm2_m3x3_mul_f64(a, b);
}
static inline lm2_m3x3_f32 operator*(const lm2_m3x3_f32& a, const lm2_m3x3_f32& b) {
  return lm2_m3x3_mul_f32(a, b);
}
static inline lm2_v3_f64 operator*(const lm2_m3x3_f64& m, const lm2_v3_f64& v) {
  return lm2_m3x3_transform_f64(m, v);
}
static inline lm2_v3_f32 operator*(const lm2_m3x3_f32& m, const lm2_v3_f32& v) {
  return lm2_m3x3_transform_f32(m, v);
}
static inline lm2_m3x3_f64& operator*=(lm2_m3x3_f64& a, const lm2_m3x3_f64& b) {
  a = lm2_m3x3_mul_f64(a, b);
  return a;
}
static inline lm2_m3x3_f32& operator*=(lm2_m3x3_f32& a, const lm2_m3x3_f32& b) {
  a = lm2_m3x3_mul_f32(a, b);
  return a;
}

// Matrix4x4 operators
static inline lm2_m4x4_f64 operator*(const lm2_m4x4_f64& a, const lm2_m4x4_f64& b) {
  return lm2_m4x4_mul_f64(a, b);
}
static inline lm2_m4x4_f32 operator*(const lm2_m4x4_f32& a, const lm2_m4x4_f32& b) {
  return lm2_m4x4_mul_f32(a, b);
}
static inline lm2_v3_f64 operator*(const lm2_m4x4_f64& m, const lm2_v3_f64& v) {
  return lm2_m4x4_transform_point_f64(m, v);
}
static inline lm2_v3_f32 operator*(const lm2_m4x4_f32& m, const lm2_v3_f32& v) {
  return lm2_m4x4_transform_point_f32(m, v);
}
static inline lm2_v4_f64 operator*(const lm2_m4x4_f64& m, const lm2_v4_f64& v) {
  return lm2_m4x4_transform_f64(m, v);
}
static inline lm2_v4_f32 operator*(const lm2_m4x4_f32& m, const lm2_v4_f32& v) {
  return lm2_m4x4_transform_f32(m, v);
}
static inline lm2_m4x4_f64& operator*=(lm2_m4x4_f64& a, const lm2_m4x4_f64& b) {
  a = lm2_m4x4_mul_f64(a, b);
  return a;
}
static inline lm2_m4x4_f32& operator*=(lm2_m4x4_f32& a, const lm2_m4x4_f32& b) {
  a = lm2_m4x4_mul_f32(a, b);
  return a;
}

// =============================================================================
// Range (AABB) Operators
// =============================================================================

// Range translation operators
// VT = C++ vector type, VEC = API base (v2/v3/v4), T = type suffix
#  define LM2_RANGE_TRANSLATE(RT, VT, REC, VEC, T)         \
    static inline RT operator+(const RT& r, const VT& v) { \
      return lm2_##REC##_add_v_##T(r, v);                  \
    }                                                      \
    static inline RT operator-(const RT& r, const VT& v) { \
      return lm2_##REC##_sub_v_##T(r, v);                  \
    }                                                      \
    static inline RT& operator+=(RT& r, const VT& v) {     \
      r = lm2_##REC##_add_v_##T(r, v);                     \
      return r;                                            \
    }                                                      \
    static inline RT& operator-=(RT& r, const VT& v) {     \
      r = lm2_##REC##_sub_v_##T(r, v);                     \
      return r;                                            \
    }

// Range scalar scaling operators
#  define LM2_RANGE_SCALE_SCALAR(RT, REC, T, ST)    \
    static inline RT operator*(const RT& r, ST s) { \
      return lm2_##REC##_mul_s_##T(r, s);           \
    }                                               \
    static inline RT operator*(ST s, const RT& r) { \
      return lm2_##REC##_mul_s_##T(r, s);           \
    }                                               \
    static inline RT operator/(const RT& r, ST s) { \
      return lm2_##REC##_div_s_##T(r, s);           \
    }                                               \
    static inline RT& operator*=(RT& r, ST s) {     \
      r = lm2_##REC##_mul_s_##T(r, s);              \
      return r;                                     \
    }                                               \
    static inline RT& operator/=(RT& r, ST s) {     \
      r = lm2_##REC##_div_s_##T(r, s);              \
      return r;                                     \
    }

// Range vector scaling operators
#  define LM2_RANGE_SCALE_VECTOR(RT, VT, REC, VEC, T)      \
    static inline RT operator*(const RT& r, const VT& v) { \
      return lm2_##REC##_mul_v_##T(r, v);                  \
    }                                                      \
    static inline RT operator*(const VT& v, const RT& r) { \
      return lm2_##REC##_mul_v_##T(r, v);                  \
    }                                                      \
    static inline RT operator/(const RT& r, const VT& v) { \
      return lm2_##REC##_div_v_##T(r, v);                  \
    }                                                      \
    static inline RT& operator*=(RT& r, const VT& v) {     \
      r = lm2_##REC##_mul_v_##T(r, v);                     \
      return r;                                            \
    }                                                      \
    static inline RT& operator/=(RT& r, const VT& v) {     \
      r = lm2_##REC##_div_v_##T(r, v);                     \
      return r;                                            \
    }

// Range set operators
#  define LM2_RANGE_SET_OPS(RT, REC, T)                    \
    static inline RT operator|(const RT& a, const RT& b) { \
      return lm2_##REC##_union_##T(a, b);                  \
    }                                                      \
    static inline RT operator&(const RT& a, const RT& b) { \
      return lm2_##REC##_intersection_##T(a, b);           \
    }                                                      \
    static inline RT& operator|=(RT& a, const RT& b) {     \
      a = lm2_##REC##_union_##T(a, b);                     \
      return a;                                            \
    }                                                      \
    static inline RT& operator&=(RT& a, const RT& b) {     \
      a = lm2_##REC##_intersection_##T(a, b);              \
      return a;                                            \
    }

// Range equality operators
#  define LM2_RANGE_EQUALITY(RT, REC, VT, T)                  \
    static inline bool operator==(const RT& a, const RT& b) { \
      return a.min.x == b.min.x &&                            \
             a.min.y == b.min.y &&                            \
             a.max.x == b.max.x &&                            \
             a.max.y == b.max.y;                              \
    }                                                         \
    static inline bool operator!=(const RT& a, const RT& b) { \
      return !(a == b);                                       \
    }

// Range3 equality operators
#  define LM2_RANGE3_EQUALITY(RT, REC, VT, T)                 \
    static inline bool operator==(const RT& a, const RT& b) { \
      return a.min.x == b.min.x &&                            \
             a.min.y == b.min.y &&                            \
             a.min.z == b.min.z &&                            \
             a.max.x == b.max.x &&                            \
             a.max.y == b.max.y &&                            \
             a.max.z == b.max.z;                              \
    }                                                         \
    static inline bool operator!=(const RT& a, const RT& b) { \
      return !(a == b);                                       \
    }

// Range4 equality operators
#  define LM2_RANGE4_EQUALITY(RT, REC, VT, T)                 \
    static inline bool operator==(const RT& a, const RT& b) { \
      return a.min.x == b.min.x &&                            \
             a.min.y == b.min.y &&                            \
             a.min.z == b.min.z &&                            \
             a.min.w == b.min.w &&                            \
             a.max.x == b.max.x &&                            \
             a.max.y == b.max.y &&                            \
             a.max.z == b.max.z &&                            \
             a.max.w == b.max.w;                              \
    }                                                         \
    static inline bool operator!=(const RT& a, const RT& b) { \
      return !(a == b);                                       \
    }

// Complete range operator set for signed types
#  define LM2_RANGE_OPS_SIGNED(RT, VT, REC, VEC, T, ST) \
    LM2_RANGE_TRANSLATE(RT, VT, REC, VEC, T)            \
    LM2_RANGE_SCALE_SCALAR(RT, REC, T, ST)              \
    LM2_RANGE_SCALE_VECTOR(RT, VT, REC, VEC, T)         \
    LM2_RANGE_SET_OPS(RT, REC, T)                       \
    LM2_RANGE_EQUALITY(RT, REC, VT, T)

// Complete range operator set for unsigned types (no negation in translate)
#  define LM2_RANGE_OPS_UNSIGNED(RT, VT, REC, VEC, T, ST)  \
    static inline RT operator+(const RT& r, const VT& v) { \
      return lm2_##REC##_add_v_##T(r, v);                  \
    }                                                      \
    static inline RT& operator+=(RT& r, const VT& v) {     \
      r = lm2_##REC##_add_v_##T(r, v);                     \
      return r;                                            \
    }                                                      \
    LM2_RANGE_SCALE_SCALAR(RT, REC, T, ST)                 \
    LM2_RANGE_SCALE_VECTOR(RT, VT, REC, VEC, T)            \
    LM2_RANGE_SET_OPS(RT, REC, T)                          \
    LM2_RANGE_EQUALITY(RT, REC, VT, T)

// Range2 operators
LM2_RANGE_OPS_SIGNED(lm2_r2_f64, lm2_v2_f64, r2, v2, f64, double)
LM2_RANGE_OPS_SIGNED(lm2_r2_f32, lm2_v2_f32, r2, v2, f32, float)
LM2_RANGE_OPS_SIGNED(lm2_r2_i64, lm2_v2_i64, r2, v2, i64, int64_t)
LM2_RANGE_OPS_SIGNED(lm2_r2_i32, lm2_v2_i32, r2, v2, i32, int32_t)
LM2_RANGE_OPS_SIGNED(lm2_r2_i16, lm2_v2_i16, r2, v2, i16, int16_t)
LM2_RANGE_OPS_SIGNED(lm2_r2_i8, lm2_v2_i8, r2, v2, i8, int8_t)
LM2_RANGE_OPS_UNSIGNED(lm2_r2_u64, lm2_v2_u64, r2, v2, u64, uint64_t)
LM2_RANGE_OPS_UNSIGNED(lm2_r2_u32, lm2_v2_u32, r2, v2, u32, uint32_t)
LM2_RANGE_OPS_UNSIGNED(lm2_r2_u16, lm2_v2_u16, r2, v2, u16, uint16_t)
LM2_RANGE_OPS_UNSIGNED(lm2_r2_u8, lm2_v2_u8, r2, v2, u8, uint8_t)

// Complete range3 operator set for signed types
#  define LM2_RANGE3_OPS_SIGNED(RT, VT, REC, VEC, T, ST) \
    LM2_RANGE_TRANSLATE(RT, VT, REC, VEC, T)             \
    LM2_RANGE_SCALE_SCALAR(RT, REC, T, ST)               \
    LM2_RANGE_SCALE_VECTOR(RT, VT, REC, VEC, T)          \
    LM2_RANGE_SET_OPS(RT, REC, T)                        \
    LM2_RANGE3_EQUALITY(RT, REC, VT, T)

// Complete range3 operator set for unsigned types
#  define LM2_RANGE3_OPS_UNSIGNED(RT, VT, REC, VEC, T, ST) \
    static inline RT operator+(const RT& r, const VT& v) { \
      return lm2_##REC##_add_v_##T(r, v);                  \
    }                                                      \
    static inline RT& operator+=(RT& r, const VT& v) {     \
      r = lm2_##REC##_add_v_##T(r, v);                     \
      return r;                                            \
    }                                                      \
    LM2_RANGE_SCALE_SCALAR(RT, REC, T, ST)                 \
    LM2_RANGE_SCALE_VECTOR(RT, VT, REC, VEC, T)            \
    LM2_RANGE_SET_OPS(RT, REC, T)                          \
    LM2_RANGE3_EQUALITY(RT, REC, VT, T)

// Range3 operators
LM2_RANGE3_OPS_SIGNED(lm2_r3_f64, lm2_v3_f64, r3, v3, f64, double)
LM2_RANGE3_OPS_SIGNED(lm2_r3_f32, lm2_v3_f32, r3, v3, f32, float)
LM2_RANGE3_OPS_SIGNED(lm2_r3_i64, lm2_v3_i64, r3, v3, i64, int64_t)
LM2_RANGE3_OPS_SIGNED(lm2_r3_i32, lm2_v3_i32, r3, v3, i32, int32_t)
LM2_RANGE3_OPS_SIGNED(lm2_r3_i16, lm2_v3_i16, r3, v3, i16, int16_t)
LM2_RANGE3_OPS_SIGNED(lm2_r3_i8, lm2_v3_i8, r3, v3, i8, int8_t)
LM2_RANGE3_OPS_UNSIGNED(lm2_r3_u64, lm2_v3_u64, r3, v3, u64, uint64_t)
LM2_RANGE3_OPS_UNSIGNED(lm2_r3_u32, lm2_v3_u32, r3, v3, u32, uint32_t)
LM2_RANGE3_OPS_UNSIGNED(lm2_r3_u16, lm2_v3_u16, r3, v3, u16, uint16_t)
LM2_RANGE3_OPS_UNSIGNED(lm2_r3_u8, lm2_v3_u8, r3, v3, u8, uint8_t)

// Complete range4 operator set for signed types
#  define LM2_RANGE4_OPS_SIGNED(RT, VT, REC, VEC, T, ST) \
    LM2_RANGE_TRANSLATE(RT, VT, REC, VEC, T)             \
    LM2_RANGE_SCALE_SCALAR(RT, REC, T, ST)               \
    LM2_RANGE_SCALE_VECTOR(RT, VT, REC, VEC, T)          \
    LM2_RANGE_SET_OPS(RT, REC, T)                        \
    LM2_RANGE4_EQUALITY(RT, REC, VT, T)

// Complete range4 operator set for unsigned types
#  define LM2_RANGE4_OPS_UNSIGNED(RT, VT, REC, VEC, T, ST) \
    static inline RT operator+(const RT& r, const VT& v) { \
      return lm2_##REC##_add_v_##T(r, v);                  \
    }                                                      \
    static inline RT& operator+=(RT& r, const VT& v) {     \
      r = lm2_##REC##_add_v_##T(r, v);                     \
      return r;                                            \
    }                                                      \
    LM2_RANGE_SCALE_SCALAR(RT, REC, T, ST)                 \
    LM2_RANGE_SCALE_VECTOR(RT, VT, REC, VEC, T)            \
    LM2_RANGE_SET_OPS(RT, REC, T)                          \
    LM2_RANGE4_EQUALITY(RT, REC, VT, T)

// Range4 operators
LM2_RANGE4_OPS_SIGNED(lm2_r4_f64, lm2_v4_f64, r4, v4, f64, double)
LM2_RANGE4_OPS_SIGNED(lm2_r4_f32, lm2_v4_f32, r4, v4, f32, float)
LM2_RANGE4_OPS_SIGNED(lm2_r4_i64, lm2_v4_i64, r4, v4, i64, int64_t)
LM2_RANGE4_OPS_SIGNED(lm2_r4_i32, lm2_v4_i32, r4, v4, i32, int32_t)
LM2_RANGE4_OPS_SIGNED(lm2_r4_i16, lm2_v4_i16, r4, v4, i16, int16_t)
LM2_RANGE4_OPS_SIGNED(lm2_r4_i8, lm2_v4_i8, r4, v4, i8, int8_t)
LM2_RANGE4_OPS_UNSIGNED(lm2_r4_u64, lm2_v4_u64, r4, v4, u64, uint64_t)
LM2_RANGE4_OPS_UNSIGNED(lm2_r4_u32, lm2_v4_u32, r4, v4, u32, uint32_t)
LM2_RANGE4_OPS_UNSIGNED(lm2_r4_u16, lm2_v4_u16, r4, v4, u16, uint16_t)
LM2_RANGE4_OPS_UNSIGNED(lm2_r4_u8, lm2_v4_u8, r4, v4, u8, uint8_t)

// =============================================================================
// Quaternion Operators
// =============================================================================

// Quaternion binary operators
static inline lm2_quat_f64 operator*(const lm2_quat_f64& a, const lm2_quat_f64& b) {
  return lm2_quat_multiply_f64(a, b);
}
static inline lm2_quat_f32 operator*(const lm2_quat_f32& a, const lm2_quat_f32& b) {
  return lm2_quat_multiply_f32(a, b);
}
static inline lm2_quat_f64 operator+(const lm2_quat_f64& a, const lm2_quat_f64& b) {
  return lm2_quat_add_f64(a, b);
}
static inline lm2_quat_f32 operator+(const lm2_quat_f32& a, const lm2_quat_f32& b) {
  return lm2_quat_add_f32(a, b);
}
static inline lm2_quat_f64 operator-(const lm2_quat_f64& a, const lm2_quat_f64& b) {
  return lm2_quat_sub_f64(a, b);
}
static inline lm2_quat_f32 operator-(const lm2_quat_f32& a, const lm2_quat_f32& b) {
  return lm2_quat_sub_f32(a, b);
}

// Quaternion scalar multiplication
static inline lm2_quat_f64 operator*(const lm2_quat_f64& q, double s) {
  return lm2_quat_scale_f64(q, s);
}
static inline lm2_quat_f32 operator*(const lm2_quat_f32& q, float s) {
  return lm2_quat_scale_f32(q, s);
}
static inline lm2_quat_f64 operator*(double s, const lm2_quat_f64& q) {
  return lm2_quat_scale_f64(q, s);
}
static inline lm2_quat_f32 operator*(float s, const lm2_quat_f32& q) {
  return lm2_quat_scale_f32(q, s);
}

// Quaternion vector rotation
static inline lm2_v3_f64 operator*(const lm2_quat_f64& q, const lm2_v3_f64& v) {
  return lm2_quat_rotate_vector_f64(q, v);
}
static inline lm2_v3_f32 operator*(const lm2_quat_f32& q, const lm2_v3_f32& v) {
  return lm2_quat_rotate_vector_f32(q, v);
}

// Quaternion unary operators
static inline lm2_quat_f64 operator-(const lm2_quat_f64& q) {
  return lm2_quat_scale_f64(q, -1.0);
}
static inline lm2_quat_f32 operator-(const lm2_quat_f32& q) {
  return lm2_quat_scale_f32(q, -1.0f);
}

// Quaternion compound assignment operators
static inline lm2_quat_f64& operator+=(lm2_quat_f64& a, const lm2_quat_f64& b) {
  a = lm2_quat_add_f64(a, b);
  return a;
}
static inline lm2_quat_f32& operator+=(lm2_quat_f32& a, const lm2_quat_f32& b) {
  a = lm2_quat_add_f32(a, b);
  return a;
}
static inline lm2_quat_f64& operator-=(lm2_quat_f64& a, const lm2_quat_f64& b) {
  a = lm2_quat_sub_f64(a, b);
  return a;
}
static inline lm2_quat_f32& operator-=(lm2_quat_f32& a, const lm2_quat_f32& b) {
  a = lm2_quat_sub_f32(a, b);
  return a;
}
static inline lm2_quat_f64& operator*=(lm2_quat_f64& a, const lm2_quat_f64& b) {
  a = lm2_quat_multiply_f64(a, b);
  return a;
}
static inline lm2_quat_f32& operator*=(lm2_quat_f32& a, const lm2_quat_f32& b) {
  a = lm2_quat_multiply_f32(a, b);
  return a;
}
static inline lm2_quat_f64& operator*=(lm2_quat_f64& q, double s) {
  q = lm2_quat_scale_f64(q, s);
  return q;
}
static inline lm2_quat_f32& operator*=(lm2_quat_f32& q, float s) {
  q = lm2_quat_scale_f32(q, s);
  return q;
}

// Quaternion equality operators
static inline bool operator==(const lm2_quat_f64& a, const lm2_quat_f64& b) {
  return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}
static inline bool operator==(const lm2_quat_f32& a, const lm2_quat_f32& b) {
  return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}
static inline bool operator!=(const lm2_quat_f64& a, const lm2_quat_f64& b) {
  return !(a == b);
}
static inline bool operator!=(const lm2_quat_f32& a, const lm2_quat_f32& b) {
  return !(a == b);
}

// =============================================================================
// Geometry2D Shape Operators
// =============================================================================

// Circle operators (translation + scaling)
static inline lm2_circle_f64 operator+(const lm2_circle_f64& c, const lm2_v2_f64& v) {
  return lm2_circle_translate_f64(c, v);
}
static inline lm2_circle_f32 operator+(const lm2_circle_f32& c, const lm2_v2_f32& v) {
  return lm2_circle_translate_f32(c, v);
}
static inline lm2_circle_f64 operator-(const lm2_circle_f64& c, const lm2_v2_f64& v) {
  return lm2_circle_translate_f64(c, lm2_v2_neg_f64(v));
}
static inline lm2_circle_f32 operator-(const lm2_circle_f32& c, const lm2_v2_f32& v) {
  return lm2_circle_translate_f32(c, lm2_v2_neg_f32(v));
}
static inline lm2_circle_f64 operator*(const lm2_circle_f64& c, double s) {
  return lm2_circle_scale_f64(c, s);
}
static inline lm2_circle_f32 operator*(const lm2_circle_f32& c, float s) {
  return lm2_circle_scale_f32(c, s);
}
static inline lm2_circle_f64 operator*(double s, const lm2_circle_f64& c) {
  return lm2_circle_scale_f64(c, s);
}
static inline lm2_circle_f32 operator*(float s, const lm2_circle_f32& c) {
  return lm2_circle_scale_f32(c, s);
}
static inline lm2_circle_f64 operator/(const lm2_circle_f64& c, double s) {
  return lm2_circle_scale_f64(c, 1.0 / s);
}
static inline lm2_circle_f32 operator/(const lm2_circle_f32& c, float s) {
  return lm2_circle_scale_f32(c, 1.0f / s);
}
static inline lm2_circle_f64& operator+=(lm2_circle_f64& c, const lm2_v2_f64& v) {
  c = lm2_circle_translate_f64(c, v);
  return c;
}
static inline lm2_circle_f32& operator+=(lm2_circle_f32& c, const lm2_v2_f32& v) {
  c = lm2_circle_translate_f32(c, v);
  return c;
}
static inline lm2_circle_f64& operator-=(lm2_circle_f64& c, const lm2_v2_f64& v) {
  c = lm2_circle_translate_f64(c, lm2_v2_neg_f64(v));
  return c;
}
static inline lm2_circle_f32& operator-=(lm2_circle_f32& c, const lm2_v2_f32& v) {
  c = lm2_circle_translate_f32(c, lm2_v2_neg_f32(v));
  return c;
}
static inline lm2_circle_f64& operator*=(lm2_circle_f64& c, double s) {
  c = lm2_circle_scale_f64(c, s);
  return c;
}
static inline lm2_circle_f32& operator*=(lm2_circle_f32& c, float s) {
  c = lm2_circle_scale_f32(c, s);
  return c;
}
static inline lm2_circle_f64& operator/=(lm2_circle_f64& c, double s) {
  c = lm2_circle_scale_f64(c, 1.0 / s);
  return c;
}
static inline lm2_circle_f32& operator/=(lm2_circle_f32& c, float s) {
  c = lm2_circle_scale_f32(c, 1.0f / s);
  return c;
}

// Capsule2 operators (translation + radius scaling)
static inline lm2_capsule2_f64 operator+(const lm2_capsule2_f64& c, const lm2_v2_f64& v) {
  return lm2_capsule2_translate_f64(c, v);
}
static inline lm2_capsule2_f32 operator+(const lm2_capsule2_f32& c, const lm2_v2_f32& v) {
  return lm2_capsule2_translate_f32(c, v);
}
static inline lm2_capsule2_f64 operator-(const lm2_capsule2_f64& c, const lm2_v2_f64& v) {
  return lm2_capsule2_translate_f64(c, lm2_v2_neg_f64(v));
}
static inline lm2_capsule2_f32 operator-(const lm2_capsule2_f32& c, const lm2_v2_f32& v) {
  return lm2_capsule2_translate_f32(c, lm2_v2_neg_f32(v));
}
static inline lm2_capsule2_f64 operator*(const lm2_capsule2_f64& c, double s) {
  return lm2_capsule2_scale_radius_f64(c, s);
}
static inline lm2_capsule2_f32 operator*(const lm2_capsule2_f32& c, float s) {
  return lm2_capsule2_scale_radius_f32(c, s);
}
static inline lm2_capsule2_f64 operator*(double s, const lm2_capsule2_f64& c) {
  return lm2_capsule2_scale_radius_f64(c, s);
}
static inline lm2_capsule2_f32 operator*(float s, const lm2_capsule2_f32& c) {
  return lm2_capsule2_scale_radius_f32(c, s);
}
static inline lm2_capsule2_f64 operator/(const lm2_capsule2_f64& c, double s) {
  return lm2_capsule2_scale_radius_f64(c, 1.0 / s);
}
static inline lm2_capsule2_f32 operator/(const lm2_capsule2_f32& c, float s) {
  return lm2_capsule2_scale_radius_f32(c, 1.0f / s);
}
static inline lm2_capsule2_f64& operator+=(lm2_capsule2_f64& c, const lm2_v2_f64& v) {
  c = lm2_capsule2_translate_f64(c, v);
  return c;
}
static inline lm2_capsule2_f32& operator+=(lm2_capsule2_f32& c, const lm2_v2_f32& v) {
  c = lm2_capsule2_translate_f32(c, v);
  return c;
}
static inline lm2_capsule2_f64& operator-=(lm2_capsule2_f64& c, const lm2_v2_f64& v) {
  c = lm2_capsule2_translate_f64(c, lm2_v2_neg_f64(v));
  return c;
}
static inline lm2_capsule2_f32& operator-=(lm2_capsule2_f32& c, const lm2_v2_f32& v) {
  c = lm2_capsule2_translate_f32(c, lm2_v2_neg_f32(v));
  return c;
}
static inline lm2_capsule2_f64& operator*=(lm2_capsule2_f64& c, double s) {
  c = lm2_capsule2_scale_radius_f64(c, s);
  return c;
}
static inline lm2_capsule2_f32& operator*=(lm2_capsule2_f32& c, float s) {
  c = lm2_capsule2_scale_radius_f32(c, s);
  return c;
}
static inline lm2_capsule2_f64& operator/=(lm2_capsule2_f64& c, double s) {
  c = lm2_capsule2_scale_radius_f64(c, 1.0 / s);
  return c;
}
static inline lm2_capsule2_f32& operator/=(lm2_capsule2_f32& c, float s) {
  c = lm2_capsule2_scale_radius_f32(c, 1.0f / s);
  return c;
}

// Plane2 operators (translation only - rotation requires angle parameter)
static inline lm2_plane2_f64 operator+(const lm2_plane2_f64& p, const lm2_v2_f64& v) {
  return lm2_plane2_translate_f64(p, v);
}
static inline lm2_plane2_f32 operator+(const lm2_plane2_f32& p, const lm2_v2_f32& v) {
  return lm2_plane2_translate_f32(p, v);
}
static inline lm2_plane2_f64 operator-(const lm2_plane2_f64& p, const lm2_v2_f64& v) {
  return lm2_plane2_translate_f64(p, lm2_v2_neg_f64(v));
}
static inline lm2_plane2_f32 operator-(const lm2_plane2_f32& p, const lm2_v2_f32& v) {
  return lm2_plane2_translate_f32(p, lm2_v2_neg_f32(v));
}
static inline lm2_plane2_f64& operator+=(lm2_plane2_f64& p, const lm2_v2_f64& v) {
  p = lm2_plane2_translate_f64(p, v);
  return p;
}
static inline lm2_plane2_f32& operator+=(lm2_plane2_f32& p, const lm2_v2_f32& v) {
  p = lm2_plane2_translate_f32(p, v);
  return p;
}
static inline lm2_plane2_f64& operator-=(lm2_plane2_f64& p, const lm2_v2_f64& v) {
  p = lm2_plane2_translate_f64(p, lm2_v2_neg_f64(v));
  return p;
}
static inline lm2_plane2_f32& operator-=(lm2_plane2_f32& p, const lm2_v2_f32& v) {
  p = lm2_plane2_translate_f32(p, lm2_v2_neg_f32(v));
  return p;
}

// =============================================================================
// Geometry3D Shape Operators
// =============================================================================

// Sphere operators (translation + scaling)
static inline lm2_sphere_f64 operator+(const lm2_sphere_f64& s, const lm2_v3_f64& v) {
  return lm2_sphere_translate_f64(s, v);
}
static inline lm2_sphere_f32 operator+(const lm2_sphere_f32& s, const lm2_v3_f32& v) {
  return lm2_sphere_translate_f32(s, v);
}
static inline lm2_sphere_f64 operator-(const lm2_sphere_f64& s, const lm2_v3_f64& v) {
  return lm2_sphere_translate_f64(s, lm2_v3_neg_f64(v));
}
static inline lm2_sphere_f32 operator-(const lm2_sphere_f32& s, const lm2_v3_f32& v) {
  return lm2_sphere_translate_f32(s, lm2_v3_neg_f32(v));
}
static inline lm2_sphere_f64 operator*(const lm2_sphere_f64& s, double sc) {
  return lm2_sphere_scale_f64(s, sc);
}
static inline lm2_sphere_f32 operator*(const lm2_sphere_f32& s, float sc) {
  return lm2_sphere_scale_f32(s, sc);
}
static inline lm2_sphere_f64 operator*(double sc, const lm2_sphere_f64& s) {
  return lm2_sphere_scale_f64(s, sc);
}
static inline lm2_sphere_f32 operator*(float sc, const lm2_sphere_f32& s) {
  return lm2_sphere_scale_f32(s, sc);
}
static inline lm2_sphere_f64 operator/(const lm2_sphere_f64& s, double sc) {
  return lm2_sphere_scale_f64(s, 1.0 / sc);
}
static inline lm2_sphere_f32 operator/(const lm2_sphere_f32& s, float sc) {
  return lm2_sphere_scale_f32(s, 1.0f / sc);
}
static inline lm2_sphere_f64& operator+=(lm2_sphere_f64& s, const lm2_v3_f64& v) {
  s = lm2_sphere_translate_f64(s, v);
  return s;
}
static inline lm2_sphere_f32& operator+=(lm2_sphere_f32& s, const lm2_v3_f32& v) {
  s = lm2_sphere_translate_f32(s, v);
  return s;
}
static inline lm2_sphere_f64& operator-=(lm2_sphere_f64& s, const lm2_v3_f64& v) {
  s = lm2_sphere_translate_f64(s, lm2_v3_neg_f64(v));
  return s;
}
static inline lm2_sphere_f32& operator-=(lm2_sphere_f32& s, const lm2_v3_f32& v) {
  s = lm2_sphere_translate_f32(s, lm2_v3_neg_f32(v));
  return s;
}
static inline lm2_sphere_f64& operator*=(lm2_sphere_f64& s, double sc) {
  s = lm2_sphere_scale_f64(s, sc);
  return s;
}
static inline lm2_sphere_f32& operator*=(lm2_sphere_f32& s, float sc) {
  s = lm2_sphere_scale_f32(s, sc);
  return s;
}
static inline lm2_sphere_f64& operator/=(lm2_sphere_f64& s, double sc) {
  s = lm2_sphere_scale_f64(s, 1.0 / sc);
  return s;
}
static inline lm2_sphere_f32& operator/=(lm2_sphere_f32& s, float sc) {
  s = lm2_sphere_scale_f32(s, 1.0f / sc);
  return s;
}

// Capsule3 operators (translation + radius scaling)
static inline lm2_capsule3_f64 operator+(const lm2_capsule3_f64& c, const lm2_v3_f64& v) {
  return lm2_capsule3_translate_f64(c, v);
}
static inline lm2_capsule3_f32 operator+(const lm2_capsule3_f32& c, const lm2_v3_f32& v) {
  return lm2_capsule3_translate_f32(c, v);
}
static inline lm2_capsule3_f64 operator-(const lm2_capsule3_f64& c, const lm2_v3_f64& v) {
  return lm2_capsule3_translate_f64(c, lm2_v3_neg_f64(v));
}
static inline lm2_capsule3_f32 operator-(const lm2_capsule3_f32& c, const lm2_v3_f32& v) {
  return lm2_capsule3_translate_f32(c, lm2_v3_neg_f32(v));
}
static inline lm2_capsule3_f64 operator*(const lm2_capsule3_f64& c, double s) {
  return lm2_capsule3_scale_radius_f64(c, s);
}
static inline lm2_capsule3_f32 operator*(const lm2_capsule3_f32& c, float s) {
  return lm2_capsule3_scale_radius_f32(c, s);
}
static inline lm2_capsule3_f64 operator*(double s, const lm2_capsule3_f64& c) {
  return lm2_capsule3_scale_radius_f64(c, s);
}
static inline lm2_capsule3_f32 operator*(float s, const lm2_capsule3_f32& c) {
  return lm2_capsule3_scale_radius_f32(c, s);
}
static inline lm2_capsule3_f64 operator/(const lm2_capsule3_f64& c, double s) {
  return lm2_capsule3_scale_radius_f64(c, 1.0 / s);
}
static inline lm2_capsule3_f32 operator/(const lm2_capsule3_f32& c, float s) {
  return lm2_capsule3_scale_radius_f32(c, 1.0f / s);
}
static inline lm2_capsule3_f64& operator+=(lm2_capsule3_f64& c, const lm2_v3_f64& v) {
  c = lm2_capsule3_translate_f64(c, v);
  return c;
}
static inline lm2_capsule3_f32& operator+=(lm2_capsule3_f32& c, const lm2_v3_f32& v) {
  c = lm2_capsule3_translate_f32(c, v);
  return c;
}
static inline lm2_capsule3_f64& operator-=(lm2_capsule3_f64& c, const lm2_v3_f64& v) {
  c = lm2_capsule3_translate_f64(c, lm2_v3_neg_f64(v));
  return c;
}
static inline lm2_capsule3_f32& operator-=(lm2_capsule3_f32& c, const lm2_v3_f32& v) {
  c = lm2_capsule3_translate_f32(c, lm2_v3_neg_f32(v));
  return c;
}
static inline lm2_capsule3_f64& operator*=(lm2_capsule3_f64& c, double s) {
  c = lm2_capsule3_scale_radius_f64(c, s);
  return c;
}
static inline lm2_capsule3_f32& operator*=(lm2_capsule3_f32& c, float s) {
  c = lm2_capsule3_scale_radius_f32(c, s);
  return c;
}
static inline lm2_capsule3_f64& operator/=(lm2_capsule3_f64& c, double s) {
  c = lm2_capsule3_scale_radius_f64(c, 1.0 / s);
  return c;
}
static inline lm2_capsule3_f32& operator/=(lm2_capsule3_f32& c, float s) {
  c = lm2_capsule3_scale_radius_f32(c, 1.0f / s);
  return c;
}

// Plane3 operators (translation only)
static inline lm2_plane3_f64 operator+(const lm2_plane3_f64& p, const lm2_v3_f64& v) {
  return lm2_plane3_translate_f64(p, v);
}
static inline lm2_plane3_f32 operator+(const lm2_plane3_f32& p, const lm2_v3_f32& v) {
  return lm2_plane3_translate_f32(p, v);
}
static inline lm2_plane3_f64 operator-(const lm2_plane3_f64& p, const lm2_v3_f64& v) {
  return lm2_plane3_translate_f64(p, lm2_v3_neg_f64(v));
}
static inline lm2_plane3_f32 operator-(const lm2_plane3_f32& p, const lm2_v3_f32& v) {
  return lm2_plane3_translate_f32(p, lm2_v3_neg_f32(v));
}
static inline lm2_plane3_f64& operator+=(lm2_plane3_f64& p, const lm2_v3_f64& v) {
  p = lm2_plane3_translate_f64(p, v);
  return p;
}
static inline lm2_plane3_f32& operator+=(lm2_plane3_f32& p, const lm2_v3_f32& v) {
  p = lm2_plane3_translate_f32(p, v);
  return p;
}
static inline lm2_plane3_f64& operator-=(lm2_plane3_f64& p, const lm2_v3_f64& v) {
  p = lm2_plane3_translate_f64(p, lm2_v3_neg_f64(v));
  return p;
}
static inline lm2_plane3_f32& operator-=(lm2_plane3_f32& p, const lm2_v3_f32& v) {
  p = lm2_plane3_translate_f32(p, lm2_v3_neg_f32(v));
  return p;
}

#endif