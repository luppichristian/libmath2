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

#include "../../lm2.h"

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
// Vector operations deduce the vector type from the first argument.
// Zero-value helpers still use an explicit scalar template argument.
// ==================================================================

// VECTOR OPERATIONS
template <typename A>
static inline auto lm2_v2_abs(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_abs_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_abs_f32(a);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_abs_i64(a);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_abs_i32(a);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_abs_i16(a);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_abs_i8(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_add(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_add_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_add_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_add_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_add_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_add_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_add_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u64>)
    return lm2_v2_add_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u32>)
    return lm2_v2_add_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u16>)
    return lm2_v2_add_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u8>)
    return lm2_v2_add_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_add_s(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_add_s_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_add_s_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_add_s_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_add_s_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_add_s_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_add_s_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u64>)
    return lm2_v2_add_s_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u32>)
    return lm2_v2_add_s_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u16>)
    return lm2_v2_add_s_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u8>)
    return lm2_v2_add_s_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B, typename C>
static inline auto lm2_v2_alpha(A a, B b, C c) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_alpha_f64(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_alpha_f32(a, b, c);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_angle(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_angle_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_angle_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_ceil(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_ceil_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_ceil_f32(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_ceil_multiple(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_ceil_multiple_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_ceil_multiple_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B, typename C>
static inline auto lm2_v2_clamp(A a, B b, C c) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_clamp_f64(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_clamp_f32(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_clamp_i64(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_clamp_i32(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_clamp_i16(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_clamp_i8(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v2_u64>)
    return lm2_v2_clamp_u64(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v2_u32>)
    return lm2_v2_clamp_u32(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v2_u16>)
    return lm2_v2_clamp_u16(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v2_u8>)
    return lm2_v2_clamp_u8(a, b, c);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_cross(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_cross_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_cross_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_cross_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_cross_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_cross_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_cross_i8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B, typename C>
static inline auto lm2_v2_cross3(A a, B b, C c) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_cross3_f64(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_cross3_f32(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_cross3_i64(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_cross3_i32(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_cross3_i16(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_cross3_i8(a, b, c);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_distance(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_distance_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_distance_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_distance_sq(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_distance_sq_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_distance_sq_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_div(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_div_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_div_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_div_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_div_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_div_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_div_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u64>)
    return lm2_v2_div_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u32>)
    return lm2_v2_div_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u16>)
    return lm2_v2_div_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u8>)
    return lm2_v2_div_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_div_s(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_div_s_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_div_s_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_div_s_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_div_s_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_div_s_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_div_s_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u64>)
    return lm2_v2_div_s_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u32>)
    return lm2_v2_div_s_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u16>)
    return lm2_v2_div_s_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u8>)
    return lm2_v2_div_s_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_dot(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_dot_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_dot_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_dot_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_dot_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_dot_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_dot_i8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_floor(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_floor_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_floor_f32(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_floor_multiple(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_floor_multiple_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_floor_multiple_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_fract(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_fract_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_fract_f32(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_length(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_length_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_length_f32(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_length_sq(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_length_sq_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_length_sq_f32(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B, typename C>
static inline auto lm2_v2_lerp(A a, B b, C c) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_lerp_f64(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_lerp_f32(a, b, c);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename T>
static inline auto lm2_v2_make(T x, T y) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<T, double>)
    return lm2_v2_make_f64(x, y);
  else if constexpr (std::is_same_v<T, float>)
    return lm2_v2_make_f32(x, y);
  else if constexpr (std::is_same_v<T, int64_t>)
    return lm2_v2_make_i64(x, y);
  else if constexpr (std::is_same_v<T, int32_t>)
    return lm2_v2_make_i32(x, y);
  else if constexpr (std::is_same_v<T, int16_t>)
    return lm2_v2_make_i16(x, y);
  else if constexpr (std::is_same_v<T, int8_t>)
    return lm2_v2_make_i8(x, y);
  else if constexpr (std::is_same_v<T, uint64_t>)
    return lm2_v2_make_u64(x, y);
  else if constexpr (std::is_same_v<T, uint32_t>)
    return lm2_v2_make_u32(x, y);
  else if constexpr (std::is_same_v<T, uint16_t>)
    return lm2_v2_make_u16(x, y);
  else if constexpr (std::is_same_v<T, uint8_t>)
    return lm2_v2_make_u8(x, y);
  else
    static_assert(sizeof(T) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_max(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_max_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_max_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_max_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_max_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_max_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_max_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u64>)
    return lm2_v2_max_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u32>)
    return lm2_v2_max_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u16>)
    return lm2_v2_max_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u8>)
    return lm2_v2_max_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_max_abs(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_max_abs_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_max_abs_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_max_abs_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_max_abs_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_max_abs_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_max_abs_i8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_min(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_min_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_min_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_min_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_min_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_min_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_min_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u64>)
    return lm2_v2_min_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u32>)
    return lm2_v2_min_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u16>)
    return lm2_v2_min_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u8>)
    return lm2_v2_min_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_min_abs(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_min_abs_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_min_abs_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_min_abs_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_min_abs_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_min_abs_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_min_abs_i8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_mod(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_mod_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_mod_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_mod_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_mod_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_mod_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_mod_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u64>)
    return lm2_v2_mod_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u32>)
    return lm2_v2_mod_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u16>)
    return lm2_v2_mod_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u8>)
    return lm2_v2_mod_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_mul(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_mul_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_mul_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_mul_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_mul_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_mul_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_mul_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u64>)
    return lm2_v2_mul_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u32>)
    return lm2_v2_mul_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u16>)
    return lm2_v2_mul_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u8>)
    return lm2_v2_mul_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_mul_s(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_mul_s_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_mul_s_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_mul_s_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_mul_s_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_mul_s_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_mul_s_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u64>)
    return lm2_v2_mul_s_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u32>)
    return lm2_v2_mul_s_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u16>)
    return lm2_v2_mul_s_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u8>)
    return lm2_v2_mul_s_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_neg(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_neg_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_neg_f32(a);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_neg_i64(a);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_neg_i32(a);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_neg_i16(a);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_neg_i8(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_norm(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_norm_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_norm_f32(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_perp_ccw(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_perp_ccw_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_perp_ccw_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_perp_ccw_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_perp_ccw_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_perp_ccw_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_perp_ccw_i8(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_perp_cw(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_perp_cw_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_perp_cw_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_perp_cw_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_perp_cw_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_perp_cw_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_perp_cw_i8(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_pow(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_pow_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_pow_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_project(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_project_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_project_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_reflect(A v, B normal) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_reflect_f64(v, normal);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_reflect_f32(v, normal);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_rotate(A v, B angle) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_rotate_f64(v, angle);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_rotate_f32(v, angle);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B, typename C>
static inline auto lm2_v2_rotate_around(A v, B point, C angle) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_rotate_around_f64(v, point, angle);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_rotate_around_f32(v, point, angle);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_round(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_round_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_round_f32(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_round_multiple(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_round_multiple_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_round_multiple_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_saturate(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_saturate_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_saturate_f32(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_sign(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_sign_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_sign_f32(a);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_sign_i64(a);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_sign_i32(a);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_sign_i16(a);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_sign_i8(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_sign0(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_sign0_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_sign0_f32(a);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_sign0_i64(a);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_sign0_i32(a);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_sign0_i16(a);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_sign0_i8(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B, typename C>
static inline auto lm2_v2_smoothstep(A a, B b, C c) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_smoothstep_f64(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_smoothstep_f32(a, b, c);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename T>
static inline auto lm2_v2_splat(T v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<T, double>)
    return lm2_v2_splat_f64(v);
  else if constexpr (std::is_same_v<T, float>)
    return lm2_v2_splat_f32(v);
  else if constexpr (std::is_same_v<T, int64_t>)
    return lm2_v2_splat_i64(v);
  else if constexpr (std::is_same_v<T, int32_t>)
    return lm2_v2_splat_i32(v);
  else if constexpr (std::is_same_v<T, int16_t>)
    return lm2_v2_splat_i16(v);
  else if constexpr (std::is_same_v<T, int8_t>)
    return lm2_v2_splat_i8(v);
  else if constexpr (std::is_same_v<T, uint64_t>)
    return lm2_v2_splat_u64(v);
  else if constexpr (std::is_same_v<T, uint32_t>)
    return lm2_v2_splat_u32(v);
  else if constexpr (std::is_same_v<T, uint16_t>)
    return lm2_v2_splat_u16(v);
  else if constexpr (std::is_same_v<T, uint8_t>)
    return lm2_v2_splat_u8(v);
  else
    static_assert(sizeof(T) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_sqrt(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_sqrt_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_sqrt_f32(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_sub(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_sub_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_sub_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_sub_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_sub_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_sub_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_sub_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u64>)
    return lm2_v2_sub_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u32>)
    return lm2_v2_sub_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u16>)
    return lm2_v2_sub_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u8>)
    return lm2_v2_sub_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_sub_s(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_sub_s_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_sub_s_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_sub_s_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_sub_s_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_sub_s_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_sub_s_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u64>)
    return lm2_v2_sub_s_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u32>)
    return lm2_v2_sub_s_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u16>)
    return lm2_v2_sub_s_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_u8>)
    return lm2_v2_sub_s_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_to_f32(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_f64_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_i64_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_i32_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_i16_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_i8_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u64>)
    return lm2_v2_u64_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u32>)
    return lm2_v2_u32_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u16>)
    return lm2_v2_u16_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u8>)
    return lm2_v2_u8_to_f32(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_to_f64(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_f32_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_i64_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_i32_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_i16_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_i8_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u64>)
    return lm2_v2_u64_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u32>)
    return lm2_v2_u32_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u16>)
    return lm2_v2_u16_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u8>)
    return lm2_v2_u8_to_f64(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_to_i16(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_f64_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_f32_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_i64_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_i32_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_i8_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u64>)
    return lm2_v2_u64_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u32>)
    return lm2_v2_u32_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u16>)
    return lm2_v2_u16_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u8>)
    return lm2_v2_u8_to_i16(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_to_i32(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_f64_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_f32_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_i64_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_i16_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_i8_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u64>)
    return lm2_v2_u64_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u32>)
    return lm2_v2_u32_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u16>)
    return lm2_v2_u16_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u8>)
    return lm2_v2_u8_to_i32(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_to_i64(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_f64_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_f32_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_i32_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_i16_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_i8_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u64>)
    return lm2_v2_u64_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u32>)
    return lm2_v2_u32_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u16>)
    return lm2_v2_u16_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u8>)
    return lm2_v2_u8_to_i64(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_to_i8(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_f64_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_f32_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_i64_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_i32_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_i16_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u64>)
    return lm2_v2_u64_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u32>)
    return lm2_v2_u32_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u16>)
    return lm2_v2_u16_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u8>)
    return lm2_v2_u8_to_i8(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_to_u16(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_f64_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_f32_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_i64_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_i32_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_i16_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_i8_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u64>)
    return lm2_v2_u64_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u32>)
    return lm2_v2_u32_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u8>)
    return lm2_v2_u8_to_u16(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_to_u32(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_f64_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_f32_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_i64_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_i32_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_i16_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_i8_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u64>)
    return lm2_v2_u64_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u16>)
    return lm2_v2_u16_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u8>)
    return lm2_v2_u8_to_u32(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_to_u64(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_f64_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_f32_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_i64_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_i32_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_i16_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_i8_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u32>)
    return lm2_v2_u32_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u16>)
    return lm2_v2_u16_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u8>)
    return lm2_v2_u8_to_u64(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_to_u8(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_f64_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_f32_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_i64_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_i32_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_i16_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_i8_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u64>)
    return lm2_v2_u64_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u32>)
    return lm2_v2_u32_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v2_u16>)
    return lm2_v2_u16_to_u8(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v2_trunc(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_trunc_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_trunc_f32(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_trunc_multiple(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_trunc_multiple_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_trunc_multiple_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v2_upcast(A v, B z) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v2_f64>)
    return lm2_v2_upcast_f64(v, z);
  else if constexpr (std::is_same_v<A, lm2_v2_f32>)
    return lm2_v2_upcast_f32(v, z);
  else if constexpr (std::is_same_v<A, lm2_v2_i64>)
    return lm2_v2_upcast_i64(v, z);
  else if constexpr (std::is_same_v<A, lm2_v2_i32>)
    return lm2_v2_upcast_i32(v, z);
  else if constexpr (std::is_same_v<A, lm2_v2_i16>)
    return lm2_v2_upcast_i16(v, z);
  else if constexpr (std::is_same_v<A, lm2_v2_i8>)
    return lm2_v2_upcast_i8(v, z);
  else if constexpr (std::is_same_v<A, lm2_v2_u64>)
    return lm2_v2_upcast_u64(v, z);
  else if constexpr (std::is_same_v<A, lm2_v2_u32>)
    return lm2_v2_upcast_u32(v, z);
  else if constexpr (std::is_same_v<A, lm2_v2_u16>)
    return lm2_v2_upcast_u16(v, z);
  else if constexpr (std::is_same_v<A, lm2_v2_u8>)
    return lm2_v2_upcast_u8(v, z);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename T>
static inline auto lm2_v2_zero() {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<T, double>)
    return lm2_v2_zero_f64();
  else if constexpr (std::is_same_v<T, float>)
    return lm2_v2_zero_f32();
  else if constexpr (std::is_same_v<T, int64_t>)
    return lm2_v2_zero_i64();
  else if constexpr (std::is_same_v<T, int32_t>)
    return lm2_v2_zero_i32();
  else if constexpr (std::is_same_v<T, int16_t>)
    return lm2_v2_zero_i16();
  else if constexpr (std::is_same_v<T, int8_t>)
    return lm2_v2_zero_i8();
  else if constexpr (std::is_same_v<T, uint64_t>)
    return lm2_v2_zero_u64();
  else if constexpr (std::is_same_v<T, uint32_t>)
    return lm2_v2_zero_u32();
  else if constexpr (std::is_same_v<T, uint16_t>)
    return lm2_v2_zero_u16();
  else if constexpr (std::is_same_v<T, uint8_t>)
    return lm2_v2_zero_u8();
  else
    static_assert(sizeof(T) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_abs(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_abs_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_abs_f32(a);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_abs_i64(a);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_abs_i32(a);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_abs_i16(a);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_abs_i8(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_add(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_add_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_add_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_add_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_add_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_add_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_add_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_add_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u32>)
    return lm2_v3_add_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u16>)
    return lm2_v3_add_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u8>)
    return lm2_v3_add_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_add_s(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_add_s_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_add_s_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_add_s_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_add_s_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_add_s_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_add_s_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_add_s_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u32>)
    return lm2_v3_add_s_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u16>)
    return lm2_v3_add_s_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u8>)
    return lm2_v3_add_s_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B, typename C>
static inline auto lm2_v3_alpha(A a, B b, C c) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_alpha_f64(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_alpha_f32(a, b, c);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_angle(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_angle_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_angle_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_ceil(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_ceil_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_ceil_f32(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_ceil_multiple(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_ceil_multiple_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_ceil_multiple_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B, typename C>
static inline auto lm2_v3_clamp(A a, B b, C c) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_clamp_f64(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_clamp_f32(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_clamp_i64(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_clamp_i32(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_clamp_i16(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_clamp_i8(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_clamp_u64(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v3_u32>)
    return lm2_v3_clamp_u32(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v3_u16>)
    return lm2_v3_clamp_u16(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v3_u8>)
    return lm2_v3_clamp_u8(a, b, c);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_cross(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_cross_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_cross_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_cross_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_cross_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_cross_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_cross_i8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_distance(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_distance_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_distance_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_distance_sq(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_distance_sq_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_distance_sq_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_div(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_div_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_div_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_div_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_div_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_div_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_div_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_div_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u32>)
    return lm2_v3_div_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u16>)
    return lm2_v3_div_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u8>)
    return lm2_v3_div_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_div_s(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_div_s_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_div_s_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_div_s_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_div_s_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_div_s_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_div_s_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_div_s_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u32>)
    return lm2_v3_div_s_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u16>)
    return lm2_v3_div_s_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u8>)
    return lm2_v3_div_s_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_dot(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_dot_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_dot_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_dot_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_dot_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_dot_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_dot_i8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_downcast(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_downcast_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_downcast_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_downcast_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_downcast_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_downcast_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_downcast_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_downcast_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u32>)
    return lm2_v3_downcast_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u16>)
    return lm2_v3_downcast_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u8>)
    return lm2_v3_downcast_u8(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_floor(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_floor_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_floor_f32(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_floor_multiple(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_floor_multiple_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_floor_multiple_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_fract(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_fract_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_fract_f32(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_length(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_length_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_length_f32(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_length_sq(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_length_sq_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_length_sq_f32(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B, typename C>
static inline auto lm2_v3_lerp(A a, B b, C c) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_lerp_f64(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_lerp_f32(a, b, c);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename T>
static inline auto lm2_v3_make(T x, T y, T z) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<T, double>)
    return lm2_v3_make_f64(x, y, z);
  else if constexpr (std::is_same_v<T, float>)
    return lm2_v3_make_f32(x, y, z);
  else if constexpr (std::is_same_v<T, int64_t>)
    return lm2_v3_make_i64(x, y, z);
  else if constexpr (std::is_same_v<T, int32_t>)
    return lm2_v3_make_i32(x, y, z);
  else if constexpr (std::is_same_v<T, int16_t>)
    return lm2_v3_make_i16(x, y, z);
  else if constexpr (std::is_same_v<T, int8_t>)
    return lm2_v3_make_i8(x, y, z);
  else if constexpr (std::is_same_v<T, uint64_t>)
    return lm2_v3_make_u64(x, y, z);
  else if constexpr (std::is_same_v<T, uint32_t>)
    return lm2_v3_make_u32(x, y, z);
  else if constexpr (std::is_same_v<T, uint16_t>)
    return lm2_v3_make_u16(x, y, z);
  else if constexpr (std::is_same_v<T, uint8_t>)
    return lm2_v3_make_u8(x, y, z);
  else
    static_assert(sizeof(T) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_max(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_max_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_max_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_max_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_max_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_max_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_max_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_max_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u32>)
    return lm2_v3_max_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u16>)
    return lm2_v3_max_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u8>)
    return lm2_v3_max_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_max_abs(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_max_abs_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_max_abs_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_max_abs_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_max_abs_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_max_abs_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_max_abs_i8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_min(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_min_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_min_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_min_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_min_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_min_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_min_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_min_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u32>)
    return lm2_v3_min_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u16>)
    return lm2_v3_min_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u8>)
    return lm2_v3_min_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_min_abs(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_min_abs_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_min_abs_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_min_abs_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_min_abs_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_min_abs_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_min_abs_i8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_mod(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_mod_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_mod_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_mod_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_mod_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_mod_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_mod_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_mod_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u32>)
    return lm2_v3_mod_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u16>)
    return lm2_v3_mod_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u8>)
    return lm2_v3_mod_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_mul(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_mul_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_mul_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_mul_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_mul_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_mul_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_mul_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_mul_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u32>)
    return lm2_v3_mul_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u16>)
    return lm2_v3_mul_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u8>)
    return lm2_v3_mul_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_mul_s(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_mul_s_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_mul_s_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_mul_s_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_mul_s_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_mul_s_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_mul_s_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_mul_s_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u32>)
    return lm2_v3_mul_s_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u16>)
    return lm2_v3_mul_s_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u8>)
    return lm2_v3_mul_s_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_neg(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_neg_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_neg_f32(a);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_neg_i64(a);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_neg_i32(a);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_neg_i16(a);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_neg_i8(a);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_neg_u64(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_norm(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_norm_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_norm_f32(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_pow(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_pow_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_pow_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_project(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_project_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_project_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_reflect(A v, B normal) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_reflect_f64(v, normal);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_reflect_f32(v, normal);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_round(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_round_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_round_f32(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_round_multiple(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_round_multiple_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_round_multiple_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_saturate(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_saturate_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_saturate_f32(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_sign(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_sign_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_sign_f32(a);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_sign_i64(a);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_sign_i32(a);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_sign_i16(a);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_sign_i8(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_sign0(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_sign0_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_sign0_f32(a);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_sign0_i64(a);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_sign0_i32(a);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_sign0_i16(a);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_sign0_i8(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B, typename C>
static inline auto lm2_v3_smoothstep(A a, B b, C c) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_smoothstep_f64(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_smoothstep_f32(a, b, c);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename T>
static inline auto lm2_v3_splat(T v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<T, double>)
    return lm2_v3_splat_f64(v);
  else if constexpr (std::is_same_v<T, float>)
    return lm2_v3_splat_f32(v);
  else if constexpr (std::is_same_v<T, int64_t>)
    return lm2_v3_splat_i64(v);
  else if constexpr (std::is_same_v<T, int32_t>)
    return lm2_v3_splat_i32(v);
  else if constexpr (std::is_same_v<T, int16_t>)
    return lm2_v3_splat_i16(v);
  else if constexpr (std::is_same_v<T, int8_t>)
    return lm2_v3_splat_i8(v);
  else if constexpr (std::is_same_v<T, uint64_t>)
    return lm2_v3_splat_u64(v);
  else if constexpr (std::is_same_v<T, uint32_t>)
    return lm2_v3_splat_u32(v);
  else if constexpr (std::is_same_v<T, uint16_t>)
    return lm2_v3_splat_u16(v);
  else if constexpr (std::is_same_v<T, uint8_t>)
    return lm2_v3_splat_u8(v);
  else
    static_assert(sizeof(T) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_sqrt(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_sqrt_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_sqrt_f32(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_sub(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_sub_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_sub_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_sub_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_sub_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_sub_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_sub_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_sub_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u32>)
    return lm2_v3_sub_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u16>)
    return lm2_v3_sub_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u8>)
    return lm2_v3_sub_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_sub_s(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_sub_s_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_sub_s_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_sub_s_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_sub_s_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_sub_s_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_sub_s_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_sub_s_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u32>)
    return lm2_v3_sub_s_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u16>)
    return lm2_v3_sub_s_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_u8>)
    return lm2_v3_sub_s_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_to_f32(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_f64_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_i64_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_i32_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_i16_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_i8_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_u64_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u32>)
    return lm2_v3_u32_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u16>)
    return lm2_v3_u16_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u8>)
    return lm2_v3_u8_to_f32(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_to_f64(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_f32_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_i64_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_i32_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_i16_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_i8_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_u64_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u32>)
    return lm2_v3_u32_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u16>)
    return lm2_v3_u16_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u8>)
    return lm2_v3_u8_to_f64(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_to_i16(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_f64_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_f32_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_i64_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_i32_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_i8_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_u64_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u32>)
    return lm2_v3_u32_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u16>)
    return lm2_v3_u16_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u8>)
    return lm2_v3_u8_to_i16(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_to_i32(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_f64_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_f32_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_i64_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_i16_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_i8_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_u64_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u32>)
    return lm2_v3_u32_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u16>)
    return lm2_v3_u16_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u8>)
    return lm2_v3_u8_to_i32(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_to_i64(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_f64_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_f32_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_i32_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_i16_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_i8_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_u64_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u32>)
    return lm2_v3_u32_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u16>)
    return lm2_v3_u16_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u8>)
    return lm2_v3_u8_to_i64(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_to_i8(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_f64_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_f32_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_i64_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_i32_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_i16_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_u64_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u32>)
    return lm2_v3_u32_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u16>)
    return lm2_v3_u16_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u8>)
    return lm2_v3_u8_to_i8(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_to_u16(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_f64_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_f32_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_i64_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_i32_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_i16_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_i8_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_u64_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u32>)
    return lm2_v3_u32_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u8>)
    return lm2_v3_u8_to_u16(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_to_u32(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_f64_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_f32_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_i64_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_i32_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_i16_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_i8_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_u64_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u16>)
    return lm2_v3_u16_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u8>)
    return lm2_v3_u8_to_u32(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_to_u64(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_f64_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_f32_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_i64_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_i32_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_i16_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_i8_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u32>)
    return lm2_v3_u32_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u16>)
    return lm2_v3_u16_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u8>)
    return lm2_v3_u8_to_u64(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_to_u8(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_f64_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_f32_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_i64_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_i32_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_i16_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_i8_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_u64_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u32>)
    return lm2_v3_u32_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v3_u16>)
    return lm2_v3_u16_to_u8(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v3_trunc(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_trunc_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_trunc_f32(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_trunc_multiple(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_trunc_multiple_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_trunc_multiple_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v3_upcast(A v, B w) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v3_f64>)
    return lm2_v3_upcast_f64(v, w);
  else if constexpr (std::is_same_v<A, lm2_v3_f32>)
    return lm2_v3_upcast_f32(v, w);
  else if constexpr (std::is_same_v<A, lm2_v3_i64>)
    return lm2_v3_upcast_i64(v, w);
  else if constexpr (std::is_same_v<A, lm2_v3_i32>)
    return lm2_v3_upcast_i32(v, w);
  else if constexpr (std::is_same_v<A, lm2_v3_i16>)
    return lm2_v3_upcast_i16(v, w);
  else if constexpr (std::is_same_v<A, lm2_v3_i8>)
    return lm2_v3_upcast_i8(v, w);
  else if constexpr (std::is_same_v<A, lm2_v3_u64>)
    return lm2_v3_upcast_u64(v, w);
  else if constexpr (std::is_same_v<A, lm2_v3_u32>)
    return lm2_v3_upcast_u32(v, w);
  else if constexpr (std::is_same_v<A, lm2_v3_u16>)
    return lm2_v3_upcast_u16(v, w);
  else if constexpr (std::is_same_v<A, lm2_v3_u8>)
    return lm2_v3_upcast_u8(v, w);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename T>
static inline auto lm2_v3_zero() {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<T, double>)
    return lm2_v3_zero_f64();
  else if constexpr (std::is_same_v<T, float>)
    return lm2_v3_zero_f32();
  else if constexpr (std::is_same_v<T, int64_t>)
    return lm2_v3_zero_i64();
  else if constexpr (std::is_same_v<T, int32_t>)
    return lm2_v3_zero_i32();
  else if constexpr (std::is_same_v<T, int16_t>)
    return lm2_v3_zero_i16();
  else if constexpr (std::is_same_v<T, int8_t>)
    return lm2_v3_zero_i8();
  else if constexpr (std::is_same_v<T, uint64_t>)
    return lm2_v3_zero_u64();
  else if constexpr (std::is_same_v<T, uint32_t>)
    return lm2_v3_zero_u32();
  else if constexpr (std::is_same_v<T, uint16_t>)
    return lm2_v3_zero_u16();
  else if constexpr (std::is_same_v<T, uint8_t>)
    return lm2_v3_zero_u8();
  else
    static_assert(sizeof(T) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_abs(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_abs_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_abs_f32(a);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_abs_i64(a);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_abs_i32(a);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_abs_i16(a);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_abs_i8(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v4_add(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_add_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_add_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_add_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_add_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_add_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_add_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u64>)
    return lm2_v4_add_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u32>)
    return lm2_v4_add_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u16>)
    return lm2_v4_add_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u8>)
    return lm2_v4_add_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v4_add_s(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_add_s_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_add_s_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_add_s_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_add_s_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_add_s_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_add_s_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u64>)
    return lm2_v4_add_s_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u32>)
    return lm2_v4_add_s_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u16>)
    return lm2_v4_add_s_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u8>)
    return lm2_v4_add_s_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B, typename C>
static inline auto lm2_v4_alpha(A a, B b, C c) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_alpha_f64(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_alpha_f32(a, b, c);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_ceil(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_ceil_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_ceil_f32(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v4_ceil_multiple(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_ceil_multiple_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_ceil_multiple_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B, typename C>
static inline auto lm2_v4_clamp(A a, B b, C c) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_clamp_f64(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_clamp_f32(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_clamp_i64(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_clamp_i32(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_clamp_i16(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_clamp_i8(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v4_u64>)
    return lm2_v4_clamp_u64(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v4_u32>)
    return lm2_v4_clamp_u32(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v4_u16>)
    return lm2_v4_clamp_u16(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v4_u8>)
    return lm2_v4_clamp_u8(a, b, c);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v4_distance(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_distance_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_distance_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v4_distance_sq(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_distance_sq_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_distance_sq_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v4_div(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_div_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_div_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_div_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_div_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_div_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_div_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u64>)
    return lm2_v4_div_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u32>)
    return lm2_v4_div_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u16>)
    return lm2_v4_div_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u8>)
    return lm2_v4_div_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v4_div_s(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_div_s_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_div_s_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_div_s_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_div_s_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_div_s_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_div_s_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u64>)
    return lm2_v4_div_s_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u32>)
    return lm2_v4_div_s_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u16>)
    return lm2_v4_div_s_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u8>)
    return lm2_v4_div_s_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v4_dot(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_dot_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_dot_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_dot_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_dot_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_dot_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_dot_i8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_downcast(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_downcast_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_downcast_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_downcast_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_downcast_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_downcast_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_downcast_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u64>)
    return lm2_v4_downcast_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u32>)
    return lm2_v4_downcast_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u16>)
    return lm2_v4_downcast_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u8>)
    return lm2_v4_downcast_u8(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_floor(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_floor_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_floor_f32(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v4_floor_multiple(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_floor_multiple_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_floor_multiple_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_fract(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_fract_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_fract_f32(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_length(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_length_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_length_f32(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_length_sq(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_length_sq_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_length_sq_f32(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B, typename C>
static inline auto lm2_v4_lerp(A a, B b, C c) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_lerp_f64(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_lerp_f32(a, b, c);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename T>
static inline auto lm2_v4_make(T x, T y, T z, T w) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<T, double>)
    return lm2_v4_make_f64(x, y, z, w);
  else if constexpr (std::is_same_v<T, float>)
    return lm2_v4_make_f32(x, y, z, w);
  else if constexpr (std::is_same_v<T, int64_t>)
    return lm2_v4_make_i64(x, y, z, w);
  else if constexpr (std::is_same_v<T, int32_t>)
    return lm2_v4_make_i32(x, y, z, w);
  else if constexpr (std::is_same_v<T, int16_t>)
    return lm2_v4_make_i16(x, y, z, w);
  else if constexpr (std::is_same_v<T, int8_t>)
    return lm2_v4_make_i8(x, y, z, w);
  else if constexpr (std::is_same_v<T, uint64_t>)
    return lm2_v4_make_u64(x, y, z, w);
  else if constexpr (std::is_same_v<T, uint32_t>)
    return lm2_v4_make_u32(x, y, z, w);
  else if constexpr (std::is_same_v<T, uint16_t>)
    return lm2_v4_make_u16(x, y, z, w);
  else if constexpr (std::is_same_v<T, uint8_t>)
    return lm2_v4_make_u8(x, y, z, w);
  else
    static_assert(sizeof(T) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v4_max(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_max_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_max_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_max_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_max_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_max_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_max_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u64>)
    return lm2_v4_max_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u32>)
    return lm2_v4_max_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u16>)
    return lm2_v4_max_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u8>)
    return lm2_v4_max_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v4_max_abs(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_max_abs_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_max_abs_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_max_abs_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_max_abs_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_max_abs_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_max_abs_i8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v4_min(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_min_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_min_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_min_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_min_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_min_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_min_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u64>)
    return lm2_v4_min_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u32>)
    return lm2_v4_min_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u16>)
    return lm2_v4_min_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u8>)
    return lm2_v4_min_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v4_min_abs(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_min_abs_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_min_abs_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_min_abs_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_min_abs_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_min_abs_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_min_abs_i8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v4_mod(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_mod_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_mod_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_mod_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_mod_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_mod_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_mod_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u64>)
    return lm2_v4_mod_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u32>)
    return lm2_v4_mod_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u16>)
    return lm2_v4_mod_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u8>)
    return lm2_v4_mod_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v4_mul(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_mul_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_mul_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_mul_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_mul_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_mul_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_mul_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u64>)
    return lm2_v4_mul_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u32>)
    return lm2_v4_mul_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u16>)
    return lm2_v4_mul_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u8>)
    return lm2_v4_mul_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v4_mul_s(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_mul_s_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_mul_s_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_mul_s_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_mul_s_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_mul_s_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_mul_s_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u64>)
    return lm2_v4_mul_s_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u32>)
    return lm2_v4_mul_s_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u16>)
    return lm2_v4_mul_s_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u8>)
    return lm2_v4_mul_s_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_neg(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_neg_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_neg_f32(a);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_neg_i64(a);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_neg_i32(a);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_neg_i16(a);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_neg_i8(a);
  else if constexpr (std::is_same_v<A, lm2_v4_u32>)
    return lm2_v4_neg_u32(a);
  else if constexpr (std::is_same_v<A, lm2_v4_u8>)
    return lm2_v4_neg_u8(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_norm(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_norm_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_norm_f32(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v4_pow(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_pow_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_pow_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_round(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_round_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_round_f32(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v4_round_multiple(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_round_multiple_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_round_multiple_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_saturate(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_saturate_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_saturate_f32(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_sign(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_sign_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_sign_f32(a);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_sign_i64(a);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_sign_i32(a);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_sign_i16(a);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_sign_i8(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_sign0(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_sign0_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_sign0_f32(a);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_sign0_i64(a);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_sign0_i32(a);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_sign0_i16(a);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_sign0_i8(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B, typename C>
static inline auto lm2_v4_smoothstep(A a, B b, C c) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_smoothstep_f64(a, b, c);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_smoothstep_f32(a, b, c);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename T>
static inline auto lm2_v4_splat(T v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<T, double>)
    return lm2_v4_splat_f64(v);
  else if constexpr (std::is_same_v<T, float>)
    return lm2_v4_splat_f32(v);
  else if constexpr (std::is_same_v<T, int64_t>)
    return lm2_v4_splat_i64(v);
  else if constexpr (std::is_same_v<T, int32_t>)
    return lm2_v4_splat_i32(v);
  else if constexpr (std::is_same_v<T, int16_t>)
    return lm2_v4_splat_i16(v);
  else if constexpr (std::is_same_v<T, int8_t>)
    return lm2_v4_splat_i8(v);
  else if constexpr (std::is_same_v<T, uint64_t>)
    return lm2_v4_splat_u64(v);
  else if constexpr (std::is_same_v<T, uint32_t>)
    return lm2_v4_splat_u32(v);
  else if constexpr (std::is_same_v<T, uint16_t>)
    return lm2_v4_splat_u16(v);
  else if constexpr (std::is_same_v<T, uint8_t>)
    return lm2_v4_splat_u8(v);
  else
    static_assert(sizeof(T) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_sqrt(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_sqrt_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_sqrt_f32(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v4_sub(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_sub_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_sub_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_sub_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_sub_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_sub_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_sub_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u64>)
    return lm2_v4_sub_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u32>)
    return lm2_v4_sub_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u16>)
    return lm2_v4_sub_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u8>)
    return lm2_v4_sub_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v4_sub_s(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_sub_s_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_sub_s_f32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_sub_s_i64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_sub_s_i32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_sub_s_i16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_sub_s_i8(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u64>)
    return lm2_v4_sub_s_u64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u32>)
    return lm2_v4_sub_s_u32(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u16>)
    return lm2_v4_sub_s_u16(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_u8>)
    return lm2_v4_sub_s_u8(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_to_f32(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_f64_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_i64_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_i32_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_i16_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_i8_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u64>)
    return lm2_v4_u64_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u32>)
    return lm2_v4_u32_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u16>)
    return lm2_v4_u16_to_f32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u8>)
    return lm2_v4_u8_to_f32(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_to_f64(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_f32_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_i64_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_i32_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_i16_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_i8_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u64>)
    return lm2_v4_u64_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u32>)
    return lm2_v4_u32_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u16>)
    return lm2_v4_u16_to_f64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u8>)
    return lm2_v4_u8_to_f64(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_to_i16(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_f64_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_f32_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_i64_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_i32_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_i8_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u64>)
    return lm2_v4_u64_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u32>)
    return lm2_v4_u32_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u16>)
    return lm2_v4_u16_to_i16(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u8>)
    return lm2_v4_u8_to_i16(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_to_i32(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_f64_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_f32_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_i64_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_i16_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_i8_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u64>)
    return lm2_v4_u64_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u32>)
    return lm2_v4_u32_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u16>)
    return lm2_v4_u16_to_i32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u8>)
    return lm2_v4_u8_to_i32(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_to_i64(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_f64_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_f32_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_i32_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_i16_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_i8_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u64>)
    return lm2_v4_u64_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u32>)
    return lm2_v4_u32_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u16>)
    return lm2_v4_u16_to_i64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u8>)
    return lm2_v4_u8_to_i64(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_to_i8(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_f64_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_f32_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_i64_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_i32_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_i16_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u64>)
    return lm2_v4_u64_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u32>)
    return lm2_v4_u32_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u16>)
    return lm2_v4_u16_to_i8(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u8>)
    return lm2_v4_u8_to_i8(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_to_u16(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_f64_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_f32_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_i64_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_i32_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_i16_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_i8_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u64>)
    return lm2_v4_u64_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u32>)
    return lm2_v4_u32_to_u16(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u8>)
    return lm2_v4_u8_to_u16(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_to_u32(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_f64_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_f32_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_i64_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_i32_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_i16_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_i8_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u64>)
    return lm2_v4_u64_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u16>)
    return lm2_v4_u16_to_u32(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u8>)
    return lm2_v4_u8_to_u32(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_to_u64(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_f64_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_f32_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_i64_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_i32_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_i16_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_i8_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u32>)
    return lm2_v4_u32_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u16>)
    return lm2_v4_u16_to_u64(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u8>)
    return lm2_v4_u8_to_u64(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_to_u8(A v) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_f64_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_f32_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i64>)
    return lm2_v4_i64_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i32>)
    return lm2_v4_i32_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i16>)
    return lm2_v4_i16_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v4_i8>)
    return lm2_v4_i8_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u64>)
    return lm2_v4_u64_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u32>)
    return lm2_v4_u32_to_u8(v);
  else if constexpr (std::is_same_v<A, lm2_v4_u16>)
    return lm2_v4_u16_to_u8(v);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A>
static inline auto lm2_v4_trunc(A a) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_trunc_f64(a);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_trunc_f32(a);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename A, typename B>
static inline auto lm2_v4_trunc_multiple(A a, B b) {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<A, lm2_v4_f64>)
    return lm2_v4_trunc_multiple_f64(a, b);
  else if constexpr (std::is_same_v<A, lm2_v4_f32>)
    return lm2_v4_trunc_multiple_f32(a, b);
  else
    static_assert(sizeof(A) == 0, "Unsupported type");
}
template <typename T>
static inline auto lm2_v4_zero() {
  if constexpr (false) {
  } else if constexpr (std::is_same_v<T, double>)
    return lm2_v4_zero_f64();
  else if constexpr (std::is_same_v<T, float>)
    return lm2_v4_zero_f32();
  else if constexpr (std::is_same_v<T, int64_t>)
    return lm2_v4_zero_i64();
  else if constexpr (std::is_same_v<T, int32_t>)
    return lm2_v4_zero_i32();
  else if constexpr (std::is_same_v<T, int16_t>)
    return lm2_v4_zero_i16();
  else if constexpr (std::is_same_v<T, int8_t>)
    return lm2_v4_zero_i8();
  else if constexpr (std::is_same_v<T, uint64_t>)
    return lm2_v4_zero_u64();
  else if constexpr (std::is_same_v<T, uint32_t>)
    return lm2_v4_zero_u32();
  else if constexpr (std::is_same_v<T, uint16_t>)
    return lm2_v4_zero_u16();
  else if constexpr (std::is_same_v<T, uint8_t>)
    return lm2_v4_zero_u8();
  else
    static_assert(sizeof(T) == 0, "Unsupported type");
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
static inline Q lm2_quat_norm(Q q) {
  LM2_DISPATCH_FLOAT(lm2_quat_norm, q)
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
static inline T lm2_ease_linear(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_linear, t)
}
template <typename T>
static inline T lm2_ease_sin_in(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_sin_in, t)
}
template <typename T>
static inline T lm2_ease_sin_out(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_sin_out, t)
}
template <typename T>
static inline T lm2_ease_sin_in_out(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_sin_in_out, t)
}
template <typename T>
static inline T lm2_ease_quad_in(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_quad_in, t)
}
template <typename T>
static inline T lm2_ease_quad_out(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_quad_out, t)
}
template <typename T>
static inline T lm2_ease_quad_in_out(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_quad_in_out, t)
}
template <typename T>
static inline T lm2_ease_cubic_in(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_cubic_in, t)
}
template <typename T>
static inline T lm2_ease_cubic_out(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_cubic_out, t)
}
template <typename T>
static inline T lm2_ease_cubic_in_out(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_cubic_in_out, t)
}
template <typename T>
static inline T lm2_ease_quart_in(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_quart_in, t)
}
template <typename T>
static inline T lm2_ease_quart_out(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_quart_out, t)
}
template <typename T>
static inline T lm2_ease_quart_in_out(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_quart_in_out, t)
}
template <typename T>
static inline T lm2_ease_quint_in(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_quint_in, t)
}
template <typename T>
static inline T lm2_ease_quint_out(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_quint_out, t)
}
template <typename T>
static inline T lm2_ease_quint_in_out(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_quint_in_out, t)
}
template <typename T>
static inline T lm2_ease_exp_in(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_exp_in, t)
}
template <typename T>
static inline T lm2_ease_exp_out(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_exp_out, t)
}
template <typename T>
static inline T lm2_ease_exp_in_out(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_exp_in_out, t)
}
template <typename T>
static inline T lm2_ease_circ_in(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_circ_in, t)
}
template <typename T>
static inline T lm2_ease_circ_out(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_circ_out, t)
}
template <typename T>
static inline T lm2_ease_circ_in_out(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_circ_in_out, t)
}
template <typename T>
static inline T lm2_ease_back_in(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_back_in, t)
}
template <typename T>
static inline T lm2_ease_back_out(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_back_out, t)
}
template <typename T>
static inline T lm2_ease_back_in_out(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_back_in_out, t)
}
template <typename T>
static inline T lm2_ease_elastic_in(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_elastic_in, t)
}
template <typename T>
static inline T lm2_ease_elastic_out(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_elastic_out, t)
}
template <typename T>
static inline T lm2_ease_elastic_in_out(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_elastic_in_out, t)
}
template <typename T>
static inline T lm2_ease_bounce_in(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_bounce_in, t)
}
template <typename T>
static inline T lm2_ease_bounce_out(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_bounce_out, t)
}
template <typename T>
static inline T lm2_ease_bounce_in_out(T t) {
  LM2_DISPATCH_FLOAT(lm2_ease_bounce_in_out, t)
}

// CAMERA2
template <typename T, typename C2, typename V2, typename R2>
static inline C2 lm2_camera2_make(V2 position, T rotation, T zoom, R2 viewport) {
  LM2_DISPATCH_FLOAT(lm2_camera2_make, position, rotation, zoom, viewport)
}
template <typename T, typename C2, typename R2>
static inline C2 lm2_camera2_default(R2 viewport) {
  LM2_DISPATCH_FLOAT(lm2_camera2_default, viewport)
}
template <typename T, typename C2, typename M>
static inline M lm2_camera2_get_view(C2 camera) {
  LM2_DISPATCH_FLOAT(lm2_camera2_get_view, camera)
}
template <typename T, typename C2, typename M>
static inline M lm2_camera2_get_inv_view(C2 camera) {
  LM2_DISPATCH_FLOAT(lm2_camera2_get_inv_view, camera)
}
template <typename T, typename C2, typename V2>
static inline V2 lm2_camera2_world_to_screen(C2 camera, V2 world_pos) {
  LM2_DISPATCH_FLOAT(lm2_camera2_world_to_screen, camera, world_pos)
}
template <typename T, typename C2, typename V2>
static inline V2 lm2_camera2_screen_to_world(C2 camera, V2 screen_pos) {
  LM2_DISPATCH_FLOAT(lm2_camera2_screen_to_world, camera, screen_pos)
}
template <typename T, typename C2, typename V2>
static inline C2 lm2_camera2_move(C2 camera, V2 delta) {
  LM2_DISPATCH_FLOAT(lm2_camera2_move, camera, delta)
}
template <typename T, typename C2, typename V2>
static inline C2 lm2_camera2_zoom_at(C2 camera, T zoom_factor, V2 screen_anchor) {
  LM2_DISPATCH_FLOAT(lm2_camera2_zoom_at, camera, zoom_factor, screen_anchor)
}
template <typename T, typename C2>
static inline C2 lm2_camera2_set_zoom(C2 camera, T zoom) {
  LM2_DISPATCH_FLOAT(lm2_camera2_set_zoom, camera, zoom)
}
template <typename T, typename C2>
static inline C2 lm2_camera2_rotate(C2 camera, T delta_radians) {
  LM2_DISPATCH_FLOAT(lm2_camera2_rotate, camera, delta_radians)
}
template <typename T, typename C2, typename V2>
static inline V2 lm2_camera2_get_viewport_size(C2 camera) {
  LM2_DISPATCH_FLOAT(lm2_camera2_get_viewport_size, camera)
}
template <typename T, typename C2, typename V2>
static inline V2 lm2_camera2_get_viewport_center(C2 camera) {
  LM2_DISPATCH_FLOAT(lm2_camera2_get_viewport_center, camera)
}
template <typename T, typename C2, typename R2>
static inline R2 lm2_camera2_get_world_bounds(C2 camera) {
  LM2_DISPATCH_FLOAT(lm2_camera2_get_world_bounds, camera)
}

// CAMERA3
template <typename T, typename C3, typename V3>
static inline C3 lm2_camera3_perspective(V3 position, V3 target, V3 up, T fov_y, T aspect, T near_plane, T far_plane) {
  LM2_DISPATCH_FLOAT(lm2_camera3_perspective, position, target, up, fov_y, aspect, near_plane, far_plane)
}
template <typename T, typename C3, typename V3>
static inline C3 lm2_camera3_orthographic(V3 position, V3 target, V3 up, T ortho_size, T aspect, T near_plane, T far_plane) {
  LM2_DISPATCH_FLOAT(lm2_camera3_orthographic, position, target, up, ortho_size, aspect, near_plane, far_plane)
}
template <typename T, typename C3, typename M4>
static inline M4 lm2_camera3_get_view(C3 camera) {
  LM2_DISPATCH_FLOAT(lm2_camera3_get_view, camera)
}
template <typename T, typename C3, typename M4>
static inline M4 lm2_camera3_get_projection(C3 camera) {
  LM2_DISPATCH_FLOAT(lm2_camera3_get_projection, camera)
}
template <typename T, typename C3, typename M4>
static inline M4 lm2_camera3_get_view_projection(C3 camera) {
  LM2_DISPATCH_FLOAT(lm2_camera3_get_view_projection, camera)
}
template <typename T, typename C3, typename M4>
static inline M4 lm2_camera3_get_inv_view(C3 camera) {
  LM2_DISPATCH_FLOAT(lm2_camera3_get_inv_view, camera)
}
template <typename T, typename C3, typename V3>
static inline V3 lm2_camera3_get_forward(C3 camera) {
  LM2_DISPATCH_FLOAT(lm2_camera3_get_forward, camera)
}
template <typename T, typename C3, typename V3>
static inline V3 lm2_camera3_get_right(C3 camera) {
  LM2_DISPATCH_FLOAT(lm2_camera3_get_right, camera)
}
template <typename T, typename C3, typename V3>
static inline V3 lm2_camera3_get_up(C3 camera) {
  LM2_DISPATCH_FLOAT(lm2_camera3_get_up, camera)
}
template <typename T, typename C3, typename V3>
static inline C3 lm2_camera3_move(C3 camera, V3 delta) {
  LM2_DISPATCH_FLOAT(lm2_camera3_move, camera, delta)
}
template <typename T, typename C3, typename V3>
static inline C3 lm2_camera3_look_at(C3 camera, V3 target) {
  LM2_DISPATCH_FLOAT(lm2_camera3_look_at, camera, target)
}
template <typename T, typename C3>
static inline C3 lm2_camera3_orbit(C3 camera, T yaw, T pitch) {
  LM2_DISPATCH_FLOAT(lm2_camera3_orbit, camera, yaw, pitch)
}
template <typename T, typename C3>
static inline C3 lm2_camera3_set_aspect(C3 camera, T aspect) {
  LM2_DISPATCH_FLOAT(lm2_camera3_set_aspect, camera, aspect)
}
template <typename T, typename C3>
static inline C3 lm2_camera3_set_fov_y(C3 camera, T fov_y) {
  LM2_DISPATCH_FLOAT(lm2_camera3_set_fov_y, camera, fov_y)
}
template <typename T, typename C3, typename V3, typename Q>
static inline C3 lm2_camera3_from_quat(V3 position, Q orientation, T fov_y, T aspect, T near_plane, T far_plane) {
  LM2_DISPATCH_FLOAT(lm2_camera3_from_quat, position, orientation, fov_y, aspect, near_plane, far_plane)
}
template <typename T, typename C3, typename Q>
static inline Q lm2_camera3_get_orientation(C3 camera) {
  LM2_DISPATCH_FLOAT(lm2_camera3_get_orientation, camera)
}
template <typename T, typename C3, typename Q>
static inline C3 lm2_camera3_set_orientation(C3 camera, Q orientation) {
  LM2_DISPATCH_FLOAT(lm2_camera3_set_orientation, camera, orientation)
}
template <typename T, typename C3, typename Q>
static inline C3 lm2_camera3_rotate_local(C3 camera, Q rotation) {
  LM2_DISPATCH_FLOAT(lm2_camera3_rotate_local, camera, rotation)
}
template <typename T, typename C3, typename V3>
static inline V3 lm2_camera3_world_to_ndc(C3 camera, V3 world_pos) {
  LM2_DISPATCH_FLOAT(lm2_camera3_world_to_ndc, camera, world_pos)
}
template <typename T, typename C3, typename V3>
static inline V3 lm2_camera3_ndc_to_world(C3 camera, V3 ndc_pos) {
  LM2_DISPATCH_FLOAT(lm2_camera3_ndc_to_world, camera, ndc_pos)
}

#  undef LM2_DISPATCH_FULL
#  undef LM2_DISPATCH_FLOAT
#  undef LM2_DISPATCH_SIGNED
#  undef LM2_DISPATCH_UINT

#endif
