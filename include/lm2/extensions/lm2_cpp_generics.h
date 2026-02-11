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
#if defined(__cplusplus) && !defined(LM2_NO_GENERICS)
#  include <cstdint>
#  include <type_traits>

// Helper macros for type dispatch
#  define LM2_DISPATCH_FULL(name, ...)                                       \
    if constexpr (std::is_same_v<T, double>) return name##_f64(__VA_ARGS__); \
    else if constexpr (std::is_same_v<T, float>)                             \
      return name##_f32(__VA_ARGS__);                                        \
    else if constexpr (std::is_same_v<T, int64_t>)                           \
      return name##_i64(__VA_ARGS__);                                        \
    else if constexpr (std::is_same_v<T, int32_t>)                           \
      return name##_i32(__VA_ARGS__);                                        \
    else if constexpr (std::is_same_v<T, int16_t>)                           \
      return name##_i16(__VA_ARGS__);                                        \
    else if constexpr (std::is_same_v<T, int8_t>)                            \
      return name##_i8(__VA_ARGS__);                                         \
    else if constexpr (std::is_same_v<T, uint64_t>)                          \
      return name##_u64(__VA_ARGS__);                                        \
    else if constexpr (std::is_same_v<T, uint32_t>)                          \
      return name##_u32(__VA_ARGS__);                                        \
    else if constexpr (std::is_same_v<T, uint16_t>)                          \
      return name##_u16(__VA_ARGS__);                                        \
    else if constexpr (std::is_same_v<T, uint8_t>)                           \
      return name##_u8(__VA_ARGS__);                                         \
    else                                                                     \
      static_assert(sizeof(T) == 0, "Unsupported type");

#  define LM2_DISPATCH_FLOAT(name, ...)                                      \
    if constexpr (std::is_same_v<T, double>) return name##_f64(__VA_ARGS__); \
    else if constexpr (std::is_same_v<T, float>)                             \
      return name##_f32(__VA_ARGS__);                                        \
    else                                                                     \
      static_assert(sizeof(T) == 0, "Unsupported type (float/double only)");

#  define LM2_DISPATCH_SIGNED(name, ...)                                     \
    if constexpr (std::is_same_v<T, double>) return name##_f64(__VA_ARGS__); \
    else if constexpr (std::is_same_v<T, float>)                             \
      return name##_f32(__VA_ARGS__);                                        \
    else if constexpr (std::is_same_v<T, int64_t>)                           \
      return name##_i64(__VA_ARGS__);                                        \
    else if constexpr (std::is_same_v<T, int32_t>)                           \
      return name##_i32(__VA_ARGS__);                                        \
    else if constexpr (std::is_same_v<T, int16_t>)                           \
      return name##_i16(__VA_ARGS__);                                        \
    else if constexpr (std::is_same_v<T, int8_t>)                            \
      return name##_i8(__VA_ARGS__);                                         \
    else                                                                     \
      static_assert(sizeof(T) == 0, "Unsupported type (signed only)");

#  define LM2_DISPATCH_UINT(name, ...)                                         \
    if constexpr (std::is_same_v<T, uint64_t>) return name##_u64(__VA_ARGS__); \
    else if constexpr (std::is_same_v<T, uint32_t>)                            \
      return name##_u32(__VA_ARGS__);                                          \
    else                                                                       \
      static_assert(sizeof(T) == 0, "Unsupported type (unsigned only)");

// ==================================================================
// SCALAR OPERATIONS
// ==================================================================

template <typename T>
static inline T lm2_add(T a, T b) {
  LM2_DISPATCH_FULL(lm2_add, a, b)
}
template <typename T>
static inline T lm2_sub(T a, T b) {
  LM2_DISPATCH_FULL(lm2_sub, a, b)
}
template <typename T>
static inline T lm2_mul(T a, T b) {
  LM2_DISPATCH_FULL(lm2_mul, a, b)
}
template <typename T>
static inline T lm2_div(T a, T b) {
  LM2_DISPATCH_FULL(lm2_div, a, b)
}
template <typename T>
static inline T lm2_mod(T a, T b) {
  LM2_DISPATCH_FULL(lm2_mod, a, b)
}
template <typename T>
static inline T lm2_neg(T a) {
  LM2_DISPATCH_SIGNED(lm2_neg, a)
}
template <typename T>
static inline T lm2_floor(T x) {
  LM2_DISPATCH_FLOAT(lm2_floor, x)
}
template <typename T>
static inline T lm2_floor_multiple(T x, T m) {
  LM2_DISPATCH_FLOAT(lm2_floor_multiple, x, m)
}
template <typename T>
static inline T lm2_ceil(T x) {
  LM2_DISPATCH_FLOAT(lm2_ceil, x)
}
template <typename T>
static inline T lm2_ceil_multiple(T x, T m) {
  LM2_DISPATCH_FLOAT(lm2_ceil_multiple, x, m)
}
template <typename T>
static inline T lm2_round(T x) {
  LM2_DISPATCH_FLOAT(lm2_round, x)
}
template <typename T>
static inline T lm2_round_multiple(T x, T m) {
  LM2_DISPATCH_FLOAT(lm2_round_multiple, x, m)
}
template <typename T>
static inline T lm2_trunc(T x) {
  LM2_DISPATCH_FLOAT(lm2_trunc, x)
}
template <typename T>
static inline T lm2_trunc_multiple(T x, T m) {
  LM2_DISPATCH_FLOAT(lm2_trunc_multiple, x, m)
}
template <typename T>
static inline T lm2_abs(T x) {
  LM2_DISPATCH_SIGNED(lm2_abs, x)
}
template <typename T>
static inline T lm2_sign(T x) {
  LM2_DISPATCH_SIGNED(lm2_sign, x)
}
template <typename T>
static inline T lm2_sign0(T x) {
  LM2_DISPATCH_SIGNED(lm2_sign0, x)
}
template <typename T>
static inline T lm2_sqrt(T x) {
  LM2_DISPATCH_FLOAT(lm2_sqrt, x)
}
template <typename T>
static inline T lm2_pow(T x, T y) {
  LM2_DISPATCH_FLOAT(lm2_pow, x, y)
}
template <typename T>
static inline T lm2_min(T a, T b) {
  LM2_DISPATCH_FULL(lm2_min, a, b)
}
template <typename T>
static inline T lm2_min_abs(T a, T b) {
  LM2_DISPATCH_SIGNED(lm2_min_abs, a, b)
}
template <typename T>
static inline T lm2_max(T a, T b) {
  LM2_DISPATCH_FULL(lm2_max, a, b)
}
template <typename T>
static inline T lm2_max_abs(T a, T b) {
  LM2_DISPATCH_SIGNED(lm2_max_abs, a, b)
}
template <typename T>
static inline T lm2_clamp(T x, T min, T max) {
  LM2_DISPATCH_FULL(lm2_clamp, x, min, max)
}
template <typename T>
static inline T lm2_saturate(T x) {
  LM2_DISPATCH_FLOAT(lm2_saturate, x)
}
template <typename T>
static inline T lm2_lerp(T a, T b, T t) {
  LM2_DISPATCH_FLOAT(lm2_lerp, a, b, t)
}
template <typename T>
static inline T lm2_smoothstep(T a, T b, T t) {
  LM2_DISPATCH_FLOAT(lm2_smoothstep, a, b, t)
}
template <typename T>
static inline T lm2_alpha(T a, T b, T t) {
  LM2_DISPATCH_FLOAT(lm2_alpha, a, b, t)
}
template <typename T>
static inline T lm2_fract(T x) {
  LM2_DISPATCH_FLOAT(lm2_fract, x)
}
template <typename T>
static inline T lm2_cos(T x) {
  LM2_DISPATCH_FLOAT(lm2_cos, x)
}
template <typename T>
static inline T lm2_sin(T x) {
  LM2_DISPATCH_FLOAT(lm2_sin, x)
}
template <typename T>
static inline T lm2_tan(T x) {
  LM2_DISPATCH_FLOAT(lm2_tan, x)
}
template <typename T>
static inline T lm2_acos(T x) {
  LM2_DISPATCH_FLOAT(lm2_acos, x)
}
template <typename T>
static inline T lm2_asin(T x) {
  LM2_DISPATCH_FLOAT(lm2_asin, x)
}
template <typename T>
static inline T lm2_atan(T x) {
  LM2_DISPATCH_FLOAT(lm2_atan, x)
}
template <typename T>
static inline T lm2_atan2(T y, T x) {
  LM2_DISPATCH_FLOAT(lm2_atan2, y, x)
}
template <typename T>
static inline T lm2_deg_to_rad(T deg) {
  LM2_DISPATCH_FLOAT(lm2_deg_to_rad, deg)
}
template <typename T>
static inline T lm2_rad_to_deg(T rad) {
  LM2_DISPATCH_FLOAT(lm2_rad_to_deg, rad)
}
template <typename T>
static inline T lm2_wrap_rad(T rad) {
  LM2_DISPATCH_FLOAT(lm2_wrap_rad, rad)
}
template <typename T>
static inline T lm2_shortest_rad(T a, T b) {
  LM2_DISPATCH_FLOAT(lm2_shortest_rad, a, b)
}
template <typename T>
static inline T lm2_lerp_rad(T a, T b, T t) {
  LM2_DISPATCH_FLOAT(lm2_lerp_rad, a, b, t)
}
template <typename T>
static inline T lm2_wrap_deg(T deg) {
  LM2_DISPATCH_FLOAT(lm2_wrap_deg, deg)
}
template <typename T>
static inline T lm2_shortest_deg(T a, T b) {
  LM2_DISPATCH_FLOAT(lm2_shortest_deg, a, b)
}
template <typename T>
static inline T lm2_lerp_deg(T a, T b, T t) {
  LM2_DISPATCH_FLOAT(lm2_lerp_deg, a, b, t)
}

// ==================================================================
// Note: Vector/Matrix/Quaternion operations require explicit
// template instantiation by the user due to C++17 limitations.
//
// Example usage:
//   lm2_v2_add<float>(v1, v2)
//   lm2_m4x4_identity<double>()
//   lm2_quat_slerp<float>(q1, q2, t)
// ==================================================================

// VECTOR2
template <typename T, typename V>
static inline V lm2_v2_add(V a, V b) {
  LM2_DISPATCH_FULL(lm2_v2_add, a, b)
}
template <typename T, typename V>
static inline V lm2_v2_sub(V a, V b) {
  LM2_DISPATCH_FULL(lm2_v2_sub, a, b)
}
template <typename T, typename V>
static inline V lm2_v2_mul(V a, V b) {
  LM2_DISPATCH_FULL(lm2_v2_mul, a, b)
}
template <typename T, typename V>
static inline V lm2_v2_div(V a, V b) {
  LM2_DISPATCH_FULL(lm2_v2_div, a, b)
}
template <typename T, typename V>
static inline V lm2_v2_add_s(V v, T s) {
  LM2_DISPATCH_FULL(lm2_v2_add_s, v, s)
}
template <typename T, typename V>
static inline V lm2_v2_mul_s(V v, T s) {
  LM2_DISPATCH_FULL(lm2_v2_mul_s, v, s)
}
template <typename T, typename V>
static inline V lm2_v2_neg(V v) {
  LM2_DISPATCH_SIGNED(lm2_v2_neg, v)
}
template <typename T, typename V>
static inline V lm2_v2_min(V a, V b) {
  LM2_DISPATCH_FULL(lm2_v2_min, a, b)
}
template <typename T, typename V>
static inline V lm2_v2_max(V a, V b) {
  LM2_DISPATCH_FULL(lm2_v2_max, a, b)
}
template <typename T, typename V>
static inline V lm2_v2_clamp(V v, V min, V max) {
  LM2_DISPATCH_FULL(lm2_v2_clamp, v, min, max)
}
template <typename T, typename V>
static inline V lm2_v2_lerp(V a, V b, T t) {
  LM2_DISPATCH_FLOAT(lm2_v2_lerp, a, b, t)
}
template <typename T>
static inline decltype(auto) lm2_v2_make(T x, T y) {
  LM2_DISPATCH_FULL(lm2_v2_make, x, y)
}
template <typename T>
static inline decltype(auto) lm2_v2_splat(T s) {
  LM2_DISPATCH_FULL(lm2_v2_splat, s)
}
template <typename T>
static inline decltype(auto) lm2_v2_zero() {
  LM2_DISPATCH_FULL(lm2_v2_zero)
}
template <typename T, typename V>
static inline T lm2_v2_dot(V a, V b) {
  LM2_DISPATCH_SIGNED(lm2_v2_dot, a, b)
}
template <typename T, typename V>
static inline T lm2_v2_cross(V a, V b) {
  LM2_DISPATCH_SIGNED(lm2_v2_cross, a, b)
}
template <typename T, typename V>
static inline T lm2_v2_length(V v) {
  LM2_DISPATCH_FLOAT(lm2_v2_length, v)
}
template <typename T, typename V>
static inline T lm2_v2_length_sq(V v) {
  LM2_DISPATCH_FLOAT(lm2_v2_length_sq, v)
}
template <typename T, typename V>
static inline T lm2_v2_distance(V a, V b) {
  LM2_DISPATCH_FLOAT(lm2_v2_distance, a, b)
}
template <typename T, typename V>
static inline V lm2_v2_normalize(V v) {
  LM2_DISPATCH_FLOAT(lm2_v2_normalize, v)
}
template <typename T, typename V>
static inline T lm2_v2_angle(V a, V b) {
  LM2_DISPATCH_FLOAT(lm2_v2_angle, a, b)
}
template <typename T, typename V>
static inline V lm2_v2_rotate(V v, T angle) {
  LM2_DISPATCH_FLOAT(lm2_v2_rotate, v, angle)
}
template <typename T, typename V>
static inline V lm2_v2_perp_ccw(V v) {
  LM2_DISPATCH_SIGNED(lm2_v2_perp_ccw, v)
}
template <typename T, typename V>
static inline V lm2_v2_perp_cw(V v) {
  LM2_DISPATCH_SIGNED(lm2_v2_perp_cw, v)
}

// VECTOR3
template <typename T, typename V>
static inline V lm2_v3_add(V a, V b) {
  LM2_DISPATCH_FULL(lm2_v3_add, a, b)
}
template <typename T, typename V>
static inline V lm2_v3_sub(V a, V b) {
  LM2_DISPATCH_FULL(lm2_v3_sub, a, b)
}
template <typename T, typename V>
static inline V lm2_v3_mul(V a, V b) {
  LM2_DISPATCH_FULL(lm2_v3_mul, a, b)
}
template <typename T, typename V>
static inline V lm2_v3_div(V a, V b) {
  LM2_DISPATCH_FULL(lm2_v3_div, a, b)
}
template <typename T, typename V>
static inline V lm2_v3_add_s(V v, T s) {
  LM2_DISPATCH_FULL(lm2_v3_add_s, v, s)
}
template <typename T, typename V>
static inline V lm2_v3_mul_s(V v, T s) {
  LM2_DISPATCH_FULL(lm2_v3_mul_s, v, s)
}
template <typename T, typename V>
static inline V lm2_v3_neg(V v) {
  LM2_DISPATCH_SIGNED(lm2_v3_neg, v)
}
template <typename T, typename V>
static inline V lm2_v3_min(V a, V b) {
  LM2_DISPATCH_FULL(lm2_v3_min, a, b)
}
template <typename T, typename V>
static inline V lm2_v3_max(V a, V b) {
  LM2_DISPATCH_FULL(lm2_v3_max, a, b)
}
template <typename T, typename V>
static inline V lm2_v3_clamp(V v, V min, V max) {
  LM2_DISPATCH_FULL(lm2_v3_clamp, v, min, max)
}
template <typename T, typename V>
static inline V lm2_v3_lerp(V a, V b, T t) {
  LM2_DISPATCH_FLOAT(lm2_v3_lerp, a, b, t)
}
template <typename T>
static inline decltype(auto) lm2_v3_make(T x, T y, T z) {
  LM2_DISPATCH_FULL(lm2_v3_make, x, y, z)
}
template <typename T>
static inline decltype(auto) lm2_v3_splat(T s) {
  LM2_DISPATCH_FULL(lm2_v3_splat, s)
}
template <typename T>
static inline decltype(auto) lm2_v3_zero() {
  LM2_DISPATCH_FULL(lm2_v3_zero)
}
template <typename T, typename V>
static inline T lm2_v3_dot(V a, V b) {
  LM2_DISPATCH_SIGNED(lm2_v3_dot, a, b)
}
template <typename T, typename V>
static inline V lm2_v3_cross(V a, V b) {
  LM2_DISPATCH_SIGNED(lm2_v3_cross, a, b)
}
template <typename T, typename V>
static inline T lm2_v3_length(V v) {
  LM2_DISPATCH_FLOAT(lm2_v3_length, v)
}
template <typename T, typename V>
static inline T lm2_v3_length_sq(V v) {
  LM2_DISPATCH_FLOAT(lm2_v3_length_sq, v)
}
template <typename T, typename V>
static inline T lm2_v3_distance(V a, V b) {
  LM2_DISPATCH_FLOAT(lm2_v3_distance, a, b)
}
template <typename T, typename V>
static inline V lm2_v3_normalize(V v) {
  LM2_DISPATCH_FLOAT(lm2_v3_normalize, v)
}
template <typename T, typename V>
static inline T lm2_v3_angle(V a, V b) {
  LM2_DISPATCH_FLOAT(lm2_v3_angle, a, b)
}

// VECTOR4
template <typename T, typename V>
static inline V lm2_v4_add(V a, V b) {
  LM2_DISPATCH_FULL(lm2_v4_add, a, b)
}
template <typename T, typename V>
static inline V lm2_v4_sub(V a, V b) {
  LM2_DISPATCH_FULL(lm2_v4_sub, a, b)
}
template <typename T, typename V>
static inline V lm2_v4_mul(V a, V b) {
  LM2_DISPATCH_FULL(lm2_v4_mul, a, b)
}
template <typename T, typename V>
static inline V lm2_v4_div(V a, V b) {
  LM2_DISPATCH_FULL(lm2_v4_div, a, b)
}
template <typename T, typename V>
static inline V lm2_v4_add_s(V v, T s) {
  LM2_DISPATCH_FULL(lm2_v4_add_s, v, s)
}
template <typename T, typename V>
static inline V lm2_v4_mul_s(V v, T s) {
  LM2_DISPATCH_FULL(lm2_v4_mul_s, v, s)
}
template <typename T, typename V>
static inline V lm2_v4_neg(V v) {
  LM2_DISPATCH_SIGNED(lm2_v4_neg, v)
}
template <typename T, typename V>
static inline V lm2_v4_min(V a, V b) {
  LM2_DISPATCH_FULL(lm2_v4_min, a, b)
}
template <typename T, typename V>
static inline V lm2_v4_max(V a, V b) {
  LM2_DISPATCH_FULL(lm2_v4_max, a, b)
}
template <typename T, typename V>
static inline V lm2_v4_clamp(V v, V min, V max) {
  LM2_DISPATCH_FULL(lm2_v4_clamp, v, min, max)
}
template <typename T, typename V>
static inline V lm2_v4_lerp(V a, V b, T t) {
  LM2_DISPATCH_FLOAT(lm2_v4_lerp, a, b, t)
}
template <typename T>
static inline decltype(auto) lm2_v4_make(T x, T y, T z, T w) {
  LM2_DISPATCH_FULL(lm2_v4_make, x, y, z, w)
}
template <typename T>
static inline decltype(auto) lm2_v4_splat(T s) {
  LM2_DISPATCH_FULL(lm2_v4_splat, s)
}
template <typename T>
static inline decltype(auto) lm2_v4_zero() {
  LM2_DISPATCH_FULL(lm2_v4_zero)
}
template <typename T, typename V>
static inline T lm2_v4_dot(V a, V b) {
  LM2_DISPATCH_SIGNED(lm2_v4_dot, a, b)
}
template <typename T, typename V>
static inline T lm2_v4_length(V v) {
  LM2_DISPATCH_FLOAT(lm2_v4_length, v)
}
template <typename T, typename V>
static inline T lm2_v4_length_sq(V v) {
  LM2_DISPATCH_FLOAT(lm2_v4_length_sq, v)
}
template <typename T, typename V>
static inline T lm2_v4_distance(V a, V b) {
  LM2_DISPATCH_FLOAT(lm2_v4_distance, a, b)
}
template <typename T, typename V>
static inline V lm2_v4_normalize(V v) {
  LM2_DISPATCH_FLOAT(lm2_v4_normalize, v)
}

// MATRIX3X2
template <typename T>
static inline decltype(auto) lm2_m3x2_identity() {
  LM2_DISPATCH_FLOAT(lm2_m3x2_identity)
}
template <typename T>
static inline decltype(auto) lm2_m3x2_zero() {
  LM2_DISPATCH_FLOAT(lm2_m3x2_zero)
}
template <typename T, typename M>
static inline M lm2_m3x2_from_rotation(T angle) {
  LM2_DISPATCH_FLOAT(lm2_m3x2_from_rotation, angle)
}
template <typename T, typename M>
static inline M lm2_m3x2_from_scale(T s) {
  LM2_DISPATCH_FLOAT(lm2_m3x2_from_scale, s)
}
template <typename T, typename M>
static inline M lm2_m3x2_mul(M a, M b) {
  LM2_DISPATCH_FLOAT(lm2_m3x2_mul, a, b)
}
template <typename T, typename M>
static inline M lm2_m3x2_rotate(M m, T angle) {
  LM2_DISPATCH_FLOAT(lm2_m3x2_rotate, m, angle)
}
template <typename T, typename M>
static inline M lm2_m3x2_scale(M m, T s) {
  LM2_DISPATCH_FLOAT(lm2_m3x2_scale, m, s)
}
template <typename T, typename M>
static inline M lm2_m3x2_inverse(M m) {
  LM2_DISPATCH_FLOAT(lm2_m3x2_inverse, m)
}
template <typename T, typename M>
static inline T lm2_m3x2_determinant(M m) {
  LM2_DISPATCH_FLOAT(lm2_m3x2_determinant, m)
}

// MATRIX3X3
template <typename T>
static inline decltype(auto) lm2_m3x3_identity() {
  LM2_DISPATCH_FLOAT(lm2_m3x3_identity)
}
template <typename T>
static inline decltype(auto) lm2_m3x3_zero() {
  LM2_DISPATCH_FLOAT(lm2_m3x3_zero)
}
template <typename T, typename M>
static inline M lm2_m3x3_from_rotation_x(T angle) {
  LM2_DISPATCH_FLOAT(lm2_m3x3_from_rotation_x, angle)
}
template <typename T, typename M>
static inline M lm2_m3x3_from_rotation_y(T angle) {
  LM2_DISPATCH_FLOAT(lm2_m3x3_from_rotation_y, angle)
}
template <typename T, typename M>
static inline M lm2_m3x3_from_rotation_z(T angle) {
  LM2_DISPATCH_FLOAT(lm2_m3x3_from_rotation_z, angle)
}
template <typename T, typename M>
static inline M lm2_m3x3_from_scale(T s) {
  LM2_DISPATCH_FLOAT(lm2_m3x3_from_scale, s)
}
template <typename T, typename M>
static inline M lm2_m3x3_mul(M a, M b) {
  LM2_DISPATCH_FLOAT(lm2_m3x3_mul, a, b)
}
template <typename T, typename M>
static inline M lm2_m3x3_rotate_x(M m, T angle) {
  LM2_DISPATCH_FLOAT(lm2_m3x3_rotate_x, m, angle)
}
template <typename T, typename M>
static inline M lm2_m3x3_rotate_y(M m, T angle) {
  LM2_DISPATCH_FLOAT(lm2_m3x3_rotate_y, m, angle)
}
template <typename T, typename M>
static inline M lm2_m3x3_rotate_z(M m, T angle) {
  LM2_DISPATCH_FLOAT(lm2_m3x3_rotate_z, m, angle)
}
template <typename T, typename M>
static inline M lm2_m3x3_scale(M m, T s) {
  LM2_DISPATCH_FLOAT(lm2_m3x3_scale, m, s)
}
template <typename T, typename M>
static inline M lm2_m3x3_transpose(M m) {
  LM2_DISPATCH_FLOAT(lm2_m3x3_transpose, m)
}
template <typename T, typename M>
static inline M lm2_m3x3_inverse(M m) {
  LM2_DISPATCH_FLOAT(lm2_m3x3_inverse, m)
}
template <typename T, typename M>
static inline T lm2_m3x3_determinant(M m) {
  LM2_DISPATCH_FLOAT(lm2_m3x3_determinant, m)
}

// MATRIX4X4
template <typename T>
static inline decltype(auto) lm2_m4x4_identity() {
  LM2_DISPATCH_FLOAT(lm2_m4x4_identity)
}
template <typename T>
static inline decltype(auto) lm2_m4x4_zero() {
  LM2_DISPATCH_FLOAT(lm2_m4x4_zero)
}
template <typename T, typename M>
static inline M lm2_m4x4_from_rotation_x(T angle) {
  LM2_DISPATCH_FLOAT(lm2_m4x4_from_rotation_x, angle)
}
template <typename T, typename M>
static inline M lm2_m4x4_from_rotation_y(T angle) {
  LM2_DISPATCH_FLOAT(lm2_m4x4_from_rotation_y, angle)
}
template <typename T, typename M>
static inline M lm2_m4x4_from_rotation_z(T angle) {
  LM2_DISPATCH_FLOAT(lm2_m4x4_from_rotation_z, angle)
}
template <typename T, typename M>
static inline M lm2_m4x4_from_scale(T s) {
  LM2_DISPATCH_FLOAT(lm2_m4x4_from_scale, s)
}
template <typename T, typename M>
static inline M lm2_m4x4_mul(M a, M b) {
  LM2_DISPATCH_FLOAT(lm2_m4x4_mul, a, b)
}
template <typename T, typename M>
static inline M lm2_m4x4_rotate_x(M m, T angle) {
  LM2_DISPATCH_FLOAT(lm2_m4x4_rotate_x, m, angle)
}
template <typename T, typename M>
static inline M lm2_m4x4_rotate_y(M m, T angle) {
  LM2_DISPATCH_FLOAT(lm2_m4x4_rotate_y, m, angle)
}
template <typename T, typename M>
static inline M lm2_m4x4_rotate_z(M m, T angle) {
  LM2_DISPATCH_FLOAT(lm2_m4x4_rotate_z, m, angle)
}
template <typename T, typename M>
static inline M lm2_m4x4_scale(M m, T s) {
  LM2_DISPATCH_FLOAT(lm2_m4x4_scale, m, s)
}
template <typename T, typename M>
static inline M lm2_m4x4_transpose(M m) {
  LM2_DISPATCH_FLOAT(lm2_m4x4_transpose, m)
}
template <typename T, typename M>
static inline M lm2_m4x4_inverse(M m) {
  LM2_DISPATCH_FLOAT(lm2_m4x4_inverse, m)
}
template <typename T, typename M>
static inline T lm2_m4x4_determinant(M m) {
  LM2_DISPATCH_FLOAT(lm2_m4x4_determinant, m)
}
template <typename T, typename M>
static inline M lm2_m4x4_perspective(T fovy, T aspect, T near, T far) {
  LM2_DISPATCH_FLOAT(lm2_m4x4_perspective, fovy, aspect, near, far)
}
template <typename T, typename M>
static inline M lm2_m4x4_orthographic(T left, T right, T bottom, T top, T near, T far) {
  LM2_DISPATCH_FLOAT(lm2_m4x4_orthographic, left, right, bottom, top, near, far)
}

// QUATERNION
template <typename T>
static inline decltype(auto) lm2_quat_identity() {
  LM2_DISPATCH_FLOAT(lm2_quat_identity)
}
template <typename T>
static inline decltype(auto) lm2_quat_zero() {
  LM2_DISPATCH_FLOAT(lm2_quat_zero)
}
template <typename T, typename Q>
static inline Q lm2_quat_make(T x, T y, T z, T w) {
  LM2_DISPATCH_FLOAT(lm2_quat_make, x, y, z, w)
}
template <typename T, typename Q>
static inline Q lm2_quat_from_euler(T x, T y, T z) {
  LM2_DISPATCH_FLOAT(lm2_quat_from_euler, x, y, z)
}
template <typename T, typename Q>
static inline Q lm2_quat_conjugate(Q q) {
  LM2_DISPATCH_FLOAT(lm2_quat_conjugate, q)
}
template <typename T, typename Q>
static inline Q lm2_quat_inverse(Q q) {
  LM2_DISPATCH_FLOAT(lm2_quat_inverse, q)
}
template <typename T, typename Q>
static inline Q lm2_quat_normalize(Q q) {
  LM2_DISPATCH_FLOAT(lm2_quat_normalize, q)
}
template <typename T, typename Q>
static inline Q lm2_quat_multiply(Q a, Q b) {
  LM2_DISPATCH_FLOAT(lm2_quat_multiply, a, b)
}
template <typename T, typename Q>
static inline T lm2_quat_dot(Q a, Q b) {
  LM2_DISPATCH_FLOAT(lm2_quat_dot, a, b)
}
template <typename T, typename Q>
static inline T lm2_quat_length(Q q) {
  LM2_DISPATCH_FLOAT(lm2_quat_length, q)
}
template <typename T, typename Q>
static inline Q lm2_quat_slerp(Q a, Q b, T t) {
  LM2_DISPATCH_FLOAT(lm2_quat_slerp, a, b, t)
}

// NOISE
template <typename T>
static inline T lm2_perlin2(T x, T y) {
  LM2_DISPATCH_FLOAT(lm2_perlin2, x, y)
}
template <typename T>
static inline T lm2_perlin3(T x, T y, T z) {
  LM2_DISPATCH_FLOAT(lm2_perlin3, x, y, z)
}
template <typename T>
static inline T lm2_voronoi2(T x, T y) {
  LM2_DISPATCH_FLOAT(lm2_voronoi2, x, y)
}
template <typename T>
static inline T lm2_voronoi3(T x, T y, T z) {
  LM2_DISPATCH_FLOAT(lm2_voronoi3, x, y, z)
}

// HASH
template <typename T>
static inline T lm2_hash_mix(T x) {
  LM2_DISPATCH_UINT(lm2_hash_mix, x)
}
template <typename T>
static inline T lm2_hash_fnv1a(T x) {
  LM2_DISPATCH_UINT(lm2_hash_fnv1a, x)
}
template <typename T>
static inline T lm2_hash_combine(T a, T b) {
  LM2_DISPATCH_UINT(lm2_hash_combine, a, b)
}

// EASINGS
template <typename T>
static inline T ease_linear(T t) {
  LM2_DISPATCH_FLOAT(ease_linear, t)
}
template <typename T>
static inline T ease_sin_in(T t) {
  LM2_DISPATCH_FLOAT(ease_sin_in, t)
}
template <typename T>
static inline T ease_sin_out(T t) {
  LM2_DISPATCH_FLOAT(ease_sin_out, t)
}
template <typename T>
static inline T ease_sin_in_out(T t) {
  LM2_DISPATCH_FLOAT(ease_sin_in_out, t)
}
template <typename T>
static inline T ease_quad_in(T t) {
  LM2_DISPATCH_FLOAT(ease_quad_in, t)
}
template <typename T>
static inline T ease_quad_out(T t) {
  LM2_DISPATCH_FLOAT(ease_quad_out, t)
}
template <typename T>
static inline T ease_quad_in_out(T t) {
  LM2_DISPATCH_FLOAT(ease_quad_in_out, t)
}
template <typename T>
static inline T ease_cubic_in(T t) {
  LM2_DISPATCH_FLOAT(ease_cubic_in, t)
}
template <typename T>
static inline T ease_cubic_out(T t) {
  LM2_DISPATCH_FLOAT(ease_cubic_out, t)
}
template <typename T>
static inline T ease_cubic_in_out(T t) {
  LM2_DISPATCH_FLOAT(ease_cubic_in_out, t)
}
template <typename T>
static inline T ease_quart_in(T t) {
  LM2_DISPATCH_FLOAT(ease_quart_in, t)
}
template <typename T>
static inline T ease_quart_out(T t) {
  LM2_DISPATCH_FLOAT(ease_quart_out, t)
}
template <typename T>
static inline T ease_quart_in_out(T t) {
  LM2_DISPATCH_FLOAT(ease_quart_in_out, t)
}
template <typename T>
static inline T ease_quint_in(T t) {
  LM2_DISPATCH_FLOAT(ease_quint_in, t)
}
template <typename T>
static inline T ease_quint_out(T t) {
  LM2_DISPATCH_FLOAT(ease_quint_out, t)
}
template <typename T>
static inline T ease_quint_in_out(T t) {
  LM2_DISPATCH_FLOAT(ease_quint_in_out, t)
}
template <typename T>
static inline T ease_exp_in(T t) {
  LM2_DISPATCH_FLOAT(ease_exp_in, t)
}
template <typename T>
static inline T ease_exp_out(T t) {
  LM2_DISPATCH_FLOAT(ease_exp_out, t)
}
template <typename T>
static inline T ease_exp_in_out(T t) {
  LM2_DISPATCH_FLOAT(ease_exp_in_out, t)
}
template <typename T>
static inline T ease_circ_in(T t) {
  LM2_DISPATCH_FLOAT(ease_circ_in, t)
}
template <typename T>
static inline T ease_circ_out(T t) {
  LM2_DISPATCH_FLOAT(ease_circ_out, t)
}
template <typename T>
static inline T ease_circ_in_out(T t) {
  LM2_DISPATCH_FLOAT(ease_circ_in_out, t)
}
template <typename T>
static inline T ease_back_in(T t) {
  LM2_DISPATCH_FLOAT(ease_back_in, t)
}
template <typename T>
static inline T ease_back_out(T t) {
  LM2_DISPATCH_FLOAT(ease_back_out, t)
}
template <typename T>
static inline T ease_back_in_out(T t) {
  LM2_DISPATCH_FLOAT(ease_back_in_out, t)
}
template <typename T>
static inline T ease_elastic_in(T t) {
  LM2_DISPATCH_FLOAT(ease_elastic_in, t)
}
template <typename T>
static inline T ease_elastic_out(T t) {
  LM2_DISPATCH_FLOAT(ease_elastic_out, t)
}
template <typename T>
static inline T ease_elastic_in_out(T t) {
  LM2_DISPATCH_FLOAT(ease_elastic_in_out, t)
}
template <typename T>
static inline T ease_bounce_in(T t) {
  LM2_DISPATCH_FLOAT(ease_bounce_in, t)
}
template <typename T>
static inline T ease_bounce_out(T t) {
  LM2_DISPATCH_FLOAT(ease_bounce_out, t)
}
template <typename T>
static inline T ease_bounce_in_out(T t) {
  LM2_DISPATCH_FLOAT(ease_bounce_in_out, t)
}

#  undef LM2_DISPATCH_FULL
#  undef LM2_DISPATCH_FLOAT
#  undef LM2_DISPATCH_SIGNED
#  undef LM2_DISPATCH_UINT

#endif
