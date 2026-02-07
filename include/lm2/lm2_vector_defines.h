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

#include "lm2_scalar.h"
#include "lm2_vector_operators.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// Declare vector-vector operation functions
#define _LM2_DECLARE_VECTOR_OP(type_name, name) \
  LM2_API type_name name(type_name a, type_name b);

// Declare vector-scalar operation functions
#define _LM2_DECLARE_VECTOR_OP_SCALAR(type_name, scalar_type, name) \
  LM2_API type_name name(type_name a, scalar_type b);

// Declare unary vector operation functions
#define _LM2_DECLARE_VECTOR_UNARY_OP(type_name, name) \
  LM2_API type_name name(type_name a);

// =============================================================================
// Vector Constructor Macros
// =============================================================================
// These macros declare helper functions for creating vectors from scalar values.

// Constructor for V2 (takes x, y components)
#define _LM2_DECLARE_V2_MAKE(type_name, scalar_type) \
  LM2_API type_name type_name##_make(scalar_type x, scalar_type y);

// Constructor for V3 (takes x, y, z components)
#define _LM2_DECLARE_V3_MAKE(type_name, scalar_type) \
  LM2_API type_name type_name##_make(scalar_type x, scalar_type y, scalar_type z);

// Constructor for V4 (takes x, y, z, w components)
#define _LM2_DECLARE_V4_MAKE(type_name, scalar_type) \
  LM2_API type_name type_name##_make(scalar_type x, scalar_type y, scalar_type z, scalar_type w);

// Splat constructor (all components set to same value)
#define _LM2_DECLARE_V2_SPLAT(type_name, scalar_type) \
  LM2_API type_name type_name##_splat(scalar_type v);

#define _LM2_DECLARE_V3_SPLAT(type_name, scalar_type) \
  LM2_API type_name type_name##_splat(scalar_type v);

#define _LM2_DECLARE_V4_SPLAT(type_name, scalar_type) \
  LM2_API type_name type_name##_splat(scalar_type v);

// Zero constructor (all components set to 0)
#define _LM2_DECLARE_V2_ZERO(type_name) \
  LM2_API type_name type_name##_zero(void);

#define _LM2_DECLARE_V3_ZERO(type_name) \
  LM2_API type_name type_name##_zero(void);

#define _LM2_DECLARE_V4_ZERO(type_name) \
  LM2_API type_name type_name##_zero(void);

// =============================================================================
// Scalar Function Porting Macros
// =============================================================================
// These macros "port" scalar functions to work with vectors by applying them
// component-wise to each vector element.

// Unary scalar function (e.g., floor, ceil, abs, sqrt)
#define _LM2_DECLARE_SCALAR_FUNC_1(type_name, func_name) \
  LM2_API type_name func_name(type_name a);

// Binary scalar function (e.g., min, max, pow, mod)
#define _LM2_DECLARE_SCALAR_FUNC_2(type_name, func_name) \
  LM2_API type_name func_name(type_name a, type_name b);

// Ternary scalar function (e.g., clamp, lerp, smoothstep)
#define _LM2_DECLARE_SCALAR_FUNC_3(type_name, func_name) \
  LM2_API type_name func_name(type_name a, type_name b, type_name c);

// C++ operator[] for vector unions
#if defined(__cplusplus) && !defined(LM2_NO_CPP_OPERATORS)
#  define _LM2_VECTOR_SUBSCRIPT_OP(scalar_type, size)   \
    inline scalar_type& operator[](int i) {             \
      return e[i];                                      \
    }                                                   \
    inline const scalar_type& operator[](int i) const { \
      return e[i];                                      \
    }
#else
#  define _LM2_VECTOR_SUBSCRIPT_OP(scalar_type, size)
#endif

// #############################################################################
LM2_HEADER_END;
// #############################################################################

// =============================================================================
// Generic Vector Dispatch Macros
// =============================================================================
// These macros provide type-generic dispatch for vector operations,
// similar to lm2_generic.h but for vector types.

#ifndef LM2_NO_GENERICS
#  ifdef __cplusplus
#    include <type_traits>

// Forward declarations for vector types (needed for template)
union lm2_v2f64;
union lm2_v2f32;
union lm2_v2i64;
union lm2_v2i32;
union lm2_v2i16;
union lm2_v2i8;
union lm2_v2u64;
union lm2_v2u32;
union lm2_v2u16;
union lm2_v2u8;
union lm2_v3f64;
union lm2_v3f32;
union lm2_v3i64;
union lm2_v3i32;
union lm2_v3i16;
union lm2_v3i8;
union lm2_v3u64;
union lm2_v3u32;
union lm2_v3u16;
union lm2_v3u8;
union lm2_v4f64;
union lm2_v4f32;
union lm2_v4i64;
union lm2_v4i32;
union lm2_v4i16;
union lm2_v4i8;
union lm2_v4u64;
union lm2_v4u32;
union lm2_v4u16;
union lm2_v4u8;

// Generic dispatcher for V2 vector-vector operations
template <typename T, typename... Args>
inline auto _lm2_generic_v2(
    auto&& f64,
    auto&& f32,
    auto&& i64,
    auto&& i32,
    auto&& i16,
    auto&& i8,
    auto&& u64,
    auto&& u32,
    auto&& u16,
    auto&& u8,
    T first,
    Args&&... rest) -> decltype(auto) {
  using _LM2_T = std::remove_cvref_t<T>;
  if constexpr (std::is_same_v<_LM2_T, lm2_v2f64>) return f64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v2f32>)
    return f32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v2i64>)
    return i64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v2i32>)
    return i32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v2i16>)
    return i16(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v2i8>)
    return i8(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v2u64>)
    return u64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v2u32>)
    return u32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v2u16>)
    return u16(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v2u8>)
    return u8(first, rest...);
  else
    static_assert(sizeof(_LM2_T) == 0, "Unsupported V2 type");
}

// Generic dispatcher for V3 vector-vector operations
template <typename T, typename... Args>
inline auto _lm2_generic_v3(
    auto&& f64,
    auto&& f32,
    auto&& i64,
    auto&& i32,
    auto&& i16,
    auto&& i8,
    auto&& u64,
    auto&& u32,
    auto&& u16,
    auto&& u8,
    T first,
    Args&&... rest) -> decltype(auto) {
  using _LM2_T = std::remove_cvref_t<T>;
  if constexpr (std::is_same_v<_LM2_T, lm2_v3f64>) return f64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v3f32>)
    return f32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v3i64>)
    return i64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v3i32>)
    return i32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v3i16>)
    return i16(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v3i8>)
    return i8(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v3u64>)
    return u64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v3u32>)
    return u32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v3u16>)
    return u16(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v3u8>)
    return u8(first, rest...);
  else
    static_assert(sizeof(_LM2_T) == 0, "Unsupported V3 type");
}

// Generic dispatcher for V4 vector-vector operations
template <typename T, typename... Args>
inline auto _lm2_generic_v4(
    auto&& f64,
    auto&& f32,
    auto&& i64,
    auto&& i32,
    auto&& i16,
    auto&& i8,
    auto&& u64,
    auto&& u32,
    auto&& u16,
    auto&& u8,
    T first,
    Args&&... rest) -> decltype(auto) {
  using _LM2_T = std::remove_cvref_t<T>;
  if constexpr (std::is_same_v<_LM2_T, lm2_v4f64>) return f64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v4f32>)
    return f32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v4i64>)
    return i64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v4i32>)
    return i32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v4i16>)
    return i16(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v4i8>)
    return i8(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v4u64>)
    return u64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v4u32>)
    return u32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v4u16>)
    return u16(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v4u8>)
    return u8(first, rest...);
  else
    static_assert(sizeof(_LM2_T) == 0, "Unsupported V4 type");
}

// C++ expression-level dispatch macros
#    define _LM2_GENERIC_V2(name, ...) \
      _lm2_generic_v2(name##_lm2_v2f64, name##_lm2_v2f32, name##_lm2_v2i64, name##_lm2_v2i32, name##_lm2_v2i16, name##_lm2_v2i8, name##_lm2_v2u64, name##_lm2_v2u32, name##_lm2_v2u16, name##_lm2_v2u8, __VA_ARGS__)

#    define _LM2_GENERIC_V3(name, ...) \
      _lm2_generic_v3(name##_lm2_v3f64, name##_lm2_v3f32, name##_lm2_v3i64, name##_lm2_v3i32, name##_lm2_v3i16, name##_lm2_v3i8, name##_lm2_v3u64, name##_lm2_v3u32, name##_lm2_v3u16, name##_lm2_v3u8, __VA_ARGS__)

#    define _LM2_GENERIC_V4(name, ...) \
      _lm2_generic_v4(name##_lm2_v4f64, name##_lm2_v4f32, name##_lm2_v4i64, name##_lm2_v4i32, name##_lm2_v4i16, name##_lm2_v4i8, name##_lm2_v4u64, name##_lm2_v4u32, name##_lm2_v4u16, name##_lm2_v4u8, __VA_ARGS__)

// C++ scalar dispatch (vector + scalar operations)
#    define _LM2_GENERIC_V2_SCALAR(name, ...) \
      _lm2_generic_v2(name##_lm2_v2f64_double, name##_lm2_v2f32_float, name##_lm2_v2i64_int64_t, name##_lm2_v2i32_int32_t, name##_lm2_v2i16_int16_t, name##_lm2_v2i8_int8_t, name##_lm2_v2u64_uint64_t, name##_lm2_v2u32_uint32_t, name##_lm2_v2u16_uint16_t, name##_lm2_v2u8_uint8_t, __VA_ARGS__)

#    define _LM2_GENERIC_V3_SCALAR(name, ...) \
      _lm2_generic_v3(name##_lm2_v3f64_double, name##_lm2_v3f32_float, name##_lm2_v3i64_int64_t, name##_lm2_v3i32_int32_t, name##_lm2_v3i16_int16_t, name##_lm2_v3i8_int8_t, name##_lm2_v3u64_uint64_t, name##_lm2_v3u32_uint32_t, name##_lm2_v3u16_uint16_t, name##_lm2_v3u8_uint8_t, __VA_ARGS__)

#    define _LM2_GENERIC_V4_SCALAR(name, ...) \
      _lm2_generic_v4(name##_lm2_v4f64_double, name##_lm2_v4f32_float, name##_lm2_v4i64_int64_t, name##_lm2_v4i32_int32_t, name##_lm2_v4i16_int16_t, name##_lm2_v4i8_int8_t, name##_lm2_v4u64_uint64_t, name##_lm2_v4u32_uint32_t, name##_lm2_v4u16_uint16_t, name##_lm2_v4u8_uint8_t, __VA_ARGS__)

// C++ unary dispatch (single argument)
#    define _LM2_GENERIC_V2_UNARY(name, ...) _LM2_GENERIC_V2(name, __VA_ARGS__)
#    define _LM2_GENERIC_V3_UNARY(name, ...) _LM2_GENERIC_V3(name, __VA_ARGS__)
#    define _LM2_GENERIC_V4_UNARY(name, ...) _LM2_GENERIC_V4(name, __VA_ARGS__)

#  else

// C11 _Generic dispatch for V2 vector-vector operations
#    define _LM2_GENERIC_V2(name, first, ...) \
      _Generic((first),                       \
          lm2_v2f64: name##_lm2_v2f64,        \
          lm2_v2f32: name##_lm2_v2f32,        \
          lm2_v2i64: name##_lm2_v2i64,        \
          lm2_v2i32: name##_lm2_v2i32,        \
          lm2_v2i16: name##_lm2_v2i16,        \
          lm2_v2i8: name##_lm2_v2i8,          \
          lm2_v2u64: name##_lm2_v2u64,        \
          lm2_v2u32: name##_lm2_v2u32,        \
          lm2_v2u16: name##_lm2_v2u16,        \
          lm2_v2u8: name##_lm2_v2u8)(first, __VA_ARGS__)

// C11 _Generic dispatch for V3 vector-vector operations
#    define _LM2_GENERIC_V3(name, first, ...) \
      _Generic((first),                       \
          lm2_v3f64: name##_lm2_v3f64,        \
          lm2_v3f32: name##_lm2_v3f32,        \
          lm2_v3i64: name##_lm2_v3i64,        \
          lm2_v3i32: name##_lm2_v3i32,        \
          lm2_v3i16: name##_lm2_v3i16,        \
          lm2_v3i8: name##_lm2_v3i8,          \
          lm2_v3u64: name##_lm2_v3u64,        \
          lm2_v3u32: name##_lm2_v3u32,        \
          lm2_v3u16: name##_lm2_v3u16,        \
          lm2_v3u8: name##_lm2_v3u8)(first, __VA_ARGS__)

// C11 _Generic dispatch for V4 vector-vector operations
#    define _LM2_GENERIC_V4(name, first, ...) \
      _Generic((first),                       \
          lm2_v4f64: name##_lm2_v4f64,        \
          lm2_v4f32: name##_lm2_v4f32,        \
          lm2_v4i64: name##_lm2_v4i64,        \
          lm2_v4i32: name##_lm2_v4i32,        \
          lm2_v4i16: name##_lm2_v4i16,        \
          lm2_v4i8: name##_lm2_v4i8,          \
          lm2_v4u64: name##_lm2_v4u64,        \
          lm2_v4u32: name##_lm2_v4u32,        \
          lm2_v4u16: name##_lm2_v4u16,        \
          lm2_v4u8: name##_lm2_v4u8)(first, __VA_ARGS__)

// C11 _Generic dispatch for V2 vector-scalar operations
#    define _LM2_GENERIC_V2_SCALAR(name, first, ...) \
      _Generic((first),                              \
          lm2_v2f64: name##_lm2_v2f64_double,        \
          lm2_v2f32: name##_lm2_v2f32_float,         \
          lm2_v2i64: name##_lm2_v2i64_int64_t,       \
          lm2_v2i32: name##_lm2_v2i32_int32_t,       \
          lm2_v2i16: name##_lm2_v2i16_int16_t,       \
          lm2_v2i8: name##_lm2_v2i8_int8_t,          \
          lm2_v2u64: name##_lm2_v2u64_uint64_t,      \
          lm2_v2u32: name##_lm2_v2u32_uint32_t,      \
          lm2_v2u16: name##_lm2_v2u16_uint16_t,      \
          lm2_v2u8: name##_lm2_v2u8_uint8_t)(first, __VA_ARGS__)

// C11 _Generic dispatch for V3 vector-scalar operations
#    define _LM2_GENERIC_V3_SCALAR(name, first, ...) \
      _Generic((first),                              \
          lm2_v3f64: name##_lm2_v3f64_double,        \
          lm2_v3f32: name##_lm2_v3f32_float,         \
          lm2_v3i64: name##_lm2_v3i64_int64_t,       \
          lm2_v3i32: name##_lm2_v3i32_int32_t,       \
          lm2_v3i16: name##_lm2_v3i16_int16_t,       \
          lm2_v3i8: name##_lm2_v3i8_int8_t,          \
          lm2_v3u64: name##_lm2_v3u64_uint64_t,      \
          lm2_v3u32: name##_lm2_v3u32_uint32_t,      \
          lm2_v3u16: name##_lm2_v3u16_uint16_t,      \
          lm2_v3u8: name##_lm2_v3u8_uint8_t)(first, __VA_ARGS__)

// C11 _Generic dispatch for V4 vector-scalar operations
#    define _LM2_GENERIC_V4_SCALAR(name, first, ...) \
      _Generic((first),                              \
          lm2_v4f64: name##_lm2_v4f64_double,        \
          lm2_v4f32: name##_lm2_v4f32_float,         \
          lm2_v4i64: name##_lm2_v4i64_int64_t,       \
          lm2_v4i32: name##_lm2_v4i32_int32_t,       \
          lm2_v4i16: name##_lm2_v4i16_int16_t,       \
          lm2_v4i8: name##_lm2_v4i8_int8_t,          \
          lm2_v4u64: name##_lm2_v4u64_uint64_t,      \
          lm2_v4u32: name##_lm2_v4u32_uint32_t,      \
          lm2_v4u16: name##_lm2_v4u16_uint16_t,      \
          lm2_v4u8: name##_lm2_v4u8_uint8_t)(first, __VA_ARGS__)

// C11 _Generic dispatch for unary vector operations
#    define _LM2_GENERIC_V2_UNARY(name, first) \
      _Generic((first),                        \
          lm2_v2f64: name##_lm2_v2f64,         \
          lm2_v2f32: name##_lm2_v2f32,         \
          lm2_v2i64: name##_lm2_v2i64,         \
          lm2_v2i32: name##_lm2_v2i32,         \
          lm2_v2i16: name##_lm2_v2i16,         \
          lm2_v2i8: name##_lm2_v2i8,           \
          lm2_v2u64: name##_lm2_v2u64,         \
          lm2_v2u32: name##_lm2_v2u32,         \
          lm2_v2u16: name##_lm2_v2u16,         \
          lm2_v2u8: name##_lm2_v2u8)(first)

#    define _LM2_GENERIC_V3_UNARY(name, first) \
      _Generic((first),                        \
          lm2_v3f64: name##_lm2_v3f64,         \
          lm2_v3f32: name##_lm2_v3f32,         \
          lm2_v3i64: name##_lm2_v3i64,         \
          lm2_v3i32: name##_lm2_v3i32,         \
          lm2_v3i16: name##_lm2_v3i16,         \
          lm2_v3i8: name##_lm2_v3i8,           \
          lm2_v3u64: name##_lm2_v3u64,         \
          lm2_v3u32: name##_lm2_v3u32,         \
          lm2_v3u16: name##_lm2_v3u16,         \
          lm2_v3u8: name##_lm2_v3u8)(first)

#    define _LM2_GENERIC_V4_UNARY(name, first) \
      _Generic((first),                        \
          lm2_v4f64: name##_lm2_v4f64,         \
          lm2_v4f32: name##_lm2_v4f32,         \
          lm2_v4i64: name##_lm2_v4i64,         \
          lm2_v4i32: name##_lm2_v4i32,         \
          lm2_v4i16: name##_lm2_v4i16,         \
          lm2_v4i8: name##_lm2_v4i8,           \
          lm2_v4u64: name##_lm2_v4u64,         \
          lm2_v4u32: name##_lm2_v4u32,         \
          lm2_v4u16: name##_lm2_v4u16,         \
          lm2_v4u8: name##_lm2_v4u8)(first)

#  endif

#else

// Expands to nothing when generics are disabled
#  define _LM2_GENERIC_V2(name, ...)
#  define _LM2_GENERIC_V3(name, ...)
#  define _LM2_GENERIC_V4(name, ...)
#  define _LM2_GENERIC_V2_SCALAR(name, ...)
#  define _LM2_GENERIC_V3_SCALAR(name, ...)
#  define _LM2_GENERIC_V4_SCALAR(name, ...)
#  define _LM2_GENERIC_V2_UNARY(name, ...)
#  define _LM2_GENERIC_V3_UNARY(name, ...)
#  define _LM2_GENERIC_V4_UNARY(name, ...)

#endif

// =============================================================================
// Multi-Dimensional Vector Generics (for functions that work across dimensions)
// =============================================================================

#ifndef LM2_NO_GENERICS
#  ifdef __cplusplus

// Generic dispatcher that combines V2, V3, and V4 float types
template <typename T, typename... Args>
inline auto _lm2_generic_vf(
    auto&& v2f64,
    auto&& v2f32,
    auto&& v3f64,
    auto&& v3f32,
    auto&& v4f64,
    auto&& v4f32,
    T first,
    Args&&... rest) -> decltype(auto) {
  using _LM2_T = std::remove_cvref_t<T>;
  if constexpr (std::is_same_v<_LM2_T, lm2_v2f64>) return v2f64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v2f32>)
    return v2f32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v3f64>)
    return v3f64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v3f32>)
    return v3f32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v4f64>)
    return v4f64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v4f32>)
    return v4f32(first, rest...);
  else
    static_assert(sizeof(_LM2_T) == 0, "Unsupported vector float type");
}

// Generic dispatcher for V2/V3/V4 all types (including integers)
template <typename T, typename... Args>
inline auto _lm2_generic_vall(
    auto&& v2f64,
    auto&& v2f32,
    auto&& v2i64,
    auto&& v2i32,
    auto&& v2i16,
    auto&& v2i8,
    auto&& v3f64,
    auto&& v3f32,
    auto&& v3i64,
    auto&& v3i32,
    auto&& v3i16,
    auto&& v3i8,
    auto&& v4f64,
    auto&& v4f32,
    auto&& v4i64,
    auto&& v4i32,
    auto&& v4i16,
    auto&& v4i8,
    T first,
    Args&&... rest) -> decltype(auto) {
  using _LM2_T = std::remove_cvref_t<T>;
  if constexpr (std::is_same_v<_LM2_T, lm2_v2f64>) return v2f64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v2f32>)
    return v2f32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v2i64>)
    return v2i64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v2i32>)
    return v2i32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v2i16>)
    return v2i16(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v2i8>)
    return v2i8(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v3f64>)
    return v3f64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v3f32>)
    return v3f32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v3i64>)
    return v3i64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v3i32>)
    return v3i32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v3i16>)
    return v3i16(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v3i8>)
    return v3i8(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v4f64>)
    return v4f64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v4f32>)
    return v4f32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v4i64>)
    return v4i64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v4i32>)
    return v4i32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v4i16>)
    return v4i16(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v4i8>)
    return v4i8(first, rest...);
  else
    static_assert(sizeof(_LM2_T) == 0, "Unsupported vector type");
}

// Generic dispatcher for V2/V3 float types
template <typename T, typename... Args>
inline auto _lm2_generic_v23f(
    auto&& v2f64,
    auto&& v2f32,
    auto&& v3f64,
    auto&& v3f32,
    T first,
    Args&&... rest) -> decltype(auto) {
  using _LM2_T = std::remove_cvref_t<T>;
  if constexpr (std::is_same_v<_LM2_T, lm2_v2f64>) return v2f64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v2f32>)
    return v2f32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v3f64>)
    return v3f64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_v3f32>)
    return v3f32(first, rest...);
  else
    static_assert(sizeof(_LM2_T) == 0, "Unsupported V2/V3 float type");
}

// C++ macros
#    define _LM2_GENERIC_VF(name, ...) \
      _lm2_generic_vf(name##_v2f64, name##_v2f32, name##_v3f64, name##_v3f32, name##_v4f64, name##_v4f32, __VA_ARGS__)

#    define _LM2_GENERIC_VALL(name, ...) \
      _lm2_generic_vall(name##_v2f64, name##_v2f32, name##_v2i64, name##_v2i32, name##_v2i16, name##_v2i8, name##_v3f64, name##_v3f32, name##_v3i64, name##_v3i32, name##_v3i16, name##_v3i8, name##_v4f64, name##_v4f32, name##_v4i64, name##_v4i32, name##_v4i16, name##_v4i8, __VA_ARGS__)

#    define _LM2_GENERIC_V23F(name, ...) \
      _lm2_generic_v23f(name##_v2f64, name##_v2f32, name##_v3f64, name##_v3f32, __VA_ARGS__)

#  else

// C11 _Generic for V2/V3/V4 float types
#    define _LM2_GENERIC_VF(name, first, ...) \
      _Generic((first),                       \
          lm2_v2f64: name##_v2f64,            \
          lm2_v2f32: name##_v2f32,            \
          lm2_v3f64: name##_v3f64,            \
          lm2_v3f32: name##_v3f32,            \
          lm2_v4f64: name##_v4f64,            \
          lm2_v4f32: name##_v4f32)(first, __VA_ARGS__)

// C11 _Generic for V2/V3/V4 all types
#    define _LM2_GENERIC_VALL(name, first, ...) \
      _Generic((first),                         \
          lm2_v2f64: name##_v2f64,              \
          lm2_v2f32: name##_v2f32,              \
          lm2_v2i64: name##_v2i64,              \
          lm2_v2i32: name##_v2i32,              \
          lm2_v2i16: name##_v2i16,              \
          lm2_v2i8: name##_v2i8,                \
          lm2_v3f64: name##_v3f64,              \
          lm2_v3f32: name##_v3f32,              \
          lm2_v3i64: name##_v3i64,              \
          lm2_v3i32: name##_v3i32,              \
          lm2_v3i16: name##_v3i16,              \
          lm2_v3i8: name##_v3i8,                \
          lm2_v4f64: name##_v4f64,              \
          lm2_v4f32: name##_v4f32,              \
          lm2_v4i64: name##_v4i64,              \
          lm2_v4i32: name##_v4i32,              \
          lm2_v4i16: name##_v4i16,              \
          lm2_v4i8: name##_v4i8)(first, __VA_ARGS__)

// C11 _Generic for V2/V3 float types
#    define _LM2_GENERIC_V23F(name, first, ...) \
      _Generic((first),                         \
          lm2_v2f64: name##_v2f64,              \
          lm2_v2f32: name##_v2f32,              \
          lm2_v3f64: name##_v3f64,              \
          lm2_v3f32: name##_v3f32)(first, __VA_ARGS__)

#  endif

#else

// Expands to nothing when generics are disabled
#  define _LM2_GENERIC_VF(name, ...)
#  define _LM2_GENERIC_VALL(name, ...)
#  define _LM2_GENERIC_V23F(name, ...)

#endif