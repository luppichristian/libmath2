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

// =============================================================================
// Generic Range Dispatch Macros
// =============================================================================
// These macros provide type-generic dispatch for range operations.

#ifndef LM2_NO_GENERICS
#  ifdef __cplusplus
#    include <type_traits>

// Forward declarations for range types
union lm2_range2f64;
union lm2_range2f32;
union lm2_range2i64;
union lm2_range2i32;
union lm2_range2i16;
union lm2_range2i8;
union lm2_range2u64;
union lm2_range2u32;
union lm2_range2u16;
union lm2_range2u8;
union lm2_range3f64;
union lm2_range3f32;
union lm2_range3i64;
union lm2_range3i32;
union lm2_range3i16;
union lm2_range3i8;
union lm2_range3u64;
union lm2_range3u32;
union lm2_range3u16;
union lm2_range3u8;
union lm2_range4f64;
union lm2_range4f32;
union lm2_range4i64;
union lm2_range4i32;
union lm2_range4i16;
union lm2_range4i8;
union lm2_range4u64;
union lm2_range4u32;
union lm2_range4u16;
union lm2_range4u8;

// Generic dispatcher for range2 operations
template <typename T, typename... Args>
inline auto _lm2_generic_range2(
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
  if constexpr (std::is_same_v<_LM2_T, lm2_range2f64>) return f64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range2f32>)
    return f32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range2i64>)
    return i64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range2i32>)
    return i32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range2i16>)
    return i16(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range2i8>)
    return i8(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range2u64>)
    return u64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range2u32>)
    return u32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range2u16>)
    return u16(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range2u8>)
    return u8(first, rest...);
  else
    static_assert(sizeof(_LM2_T) == 0, "Unsupported range2 type");
}

// Generic dispatcher for range3 operations
template <typename T, typename... Args>
inline auto _lm2_generic_range3(
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
  if constexpr (std::is_same_v<_LM2_T, lm2_range3f64>) return f64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range3f32>)
    return f32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range3i64>)
    return i64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range3i32>)
    return i32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range3i16>)
    return i16(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range3i8>)
    return i8(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range3u64>)
    return u64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range3u32>)
    return u32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range3u16>)
    return u16(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range3u8>)
    return u8(first, rest...);
  else
    static_assert(sizeof(_LM2_T) == 0, "Unsupported range3 type");
}

// Generic dispatcher for range4 operations
template <typename T, typename... Args>
inline auto _lm2_generic_range4(
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
  if constexpr (std::is_same_v<_LM2_T, lm2_range4f64>) return f64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range4f32>)
    return f32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range4i64>)
    return i64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range4i32>)
    return i32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range4i16>)
    return i16(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range4i8>)
    return i8(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range4u64>)
    return u64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range4u32>)
    return u32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range4u16>)
    return u16(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, lm2_range4u8>)
    return u8(first, rest...);
  else
    static_assert(sizeof(_LM2_T) == 0, "Unsupported range4 type");
}

// C++ expression-level dispatch macros
#    define _LM2_GENERIC_RANGE2(name, ...) \
      _lm2_generic_range2(lm2_range2f64_##name, lm2_range2f32_##name, lm2_range2i64_##name, lm2_range2i32_##name, lm2_range2i16_##name, lm2_range2i8_##name, lm2_range2u64_##name, lm2_range2u32_##name, lm2_range2u16_##name, lm2_range2u8_##name, __VA_ARGS__)

#    define _LM2_GENERIC_RANGE3(name, ...) \
      _lm2_generic_range3(lm2_range3f64_##name, lm2_range3f32_##name, lm2_range3i64_##name, lm2_range3i32_##name, lm2_range3i16_##name, lm2_range3i8_##name, lm2_range3u64_##name, lm2_range3u32_##name, lm2_range3u16_##name, lm2_range3u8_##name, __VA_ARGS__)

#    define _LM2_GENERIC_RANGE4(name, ...) \
      _lm2_generic_range4(lm2_range4f64_##name, lm2_range4f32_##name, lm2_range4i64_##name, lm2_range4i32_##name, lm2_range4i16_##name, lm2_range4i8_##name, lm2_range4u64_##name, lm2_range4u32_##name, lm2_range4u16_##name, lm2_range4u8_##name, __VA_ARGS__)

#  else

// C11 _Generic dispatch for range2 operations
#    define _LM2_GENERIC_RANGE2(name, first, ...) \
      _Generic((first),                           \
          lm2_range2f64: lm2_range2f64_##name,    \
          lm2_range2f32: lm2_range2f32_##name,    \
          lm2_range2i64: lm2_range2i64_##name,    \
          lm2_range2i32: lm2_range2i32_##name,    \
          lm2_range2i16: lm2_range2i16_##name,    \
          lm2_range2i8: lm2_range2i8_##name,      \
          lm2_range2u64: lm2_range2u64_##name,    \
          lm2_range2u32: lm2_range2u32_##name,    \
          lm2_range2u16: lm2_range2u16_##name,    \
          lm2_range2u8: lm2_range2u8_##name)(first, __VA_ARGS__)

// C11 _Generic dispatch for range3 operations
#    define _LM2_GENERIC_RANGE3(name, first, ...) \
      _Generic((first),                           \
          lm2_range3f64: lm2_range3f64_##name,    \
          lm2_range3f32: lm2_range3f32_##name,    \
          lm2_range3i64: lm2_range3i64_##name,    \
          lm2_range3i32: lm2_range3i32_##name,    \
          lm2_range3i16: lm2_range3i16_##name,    \
          lm2_range3i8: lm2_range3i8_##name,      \
          lm2_range3u64: lm2_range3u64_##name,    \
          lm2_range3u32: lm2_range3u32_##name,    \
          lm2_range3u16: lm2_range3u16_##name,    \
          lm2_range3u8: lm2_range3u8_##name)(first, __VA_ARGS__)

// C11 _Generic dispatch for range4 operations
#    define _LM2_GENERIC_RANGE4(name, first, ...) \
      _Generic((first),                           \
          lm2_range4f64: lm2_range4f64_##name,    \
          lm2_range4f32: lm2_range4f32_##name,    \
          lm2_range4i64: lm2_range4i64_##name,    \
          lm2_range4i32: lm2_range4i32_##name,    \
          lm2_range4i16: lm2_range4i16_##name,    \
          lm2_range4i8: lm2_range4i8_##name,      \
          lm2_range4u64: lm2_range4u64_##name,    \
          lm2_range4u32: lm2_range4u32_##name,    \
          lm2_range4u16: lm2_range4u16_##name,    \
          lm2_range4u8: lm2_range4u8_##name)(first, __VA_ARGS__)

#  endif

// =============================================================================
// Multi-Type Arithmetic Dispatch for Ranges
// =============================================================================
// These macros dispatch arithmetic operations based on BOTH the range type
// and the second operand type (range, vector, or scalar)

#  ifdef __cplusplus

// C++ overload-based dispatch for range arithmetic
// Dispatches based on second argument type: range -> _func, vector -> _func_vec, scalar -> _func_scalar

#    define _LM2_RANGE_ARITHMETIC_DISPATCH(range_prefix, func, r, x) \
      _Generic((x),                                                  \
          lm2_range2f64: range_prefix##_##func,                      \
          lm2_range2f32: range_prefix##_##func,                      \
          lm2_range2i64: range_prefix##_##func,                      \
          lm2_range2i32: range_prefix##_##func,                      \
          lm2_range2i16: range_prefix##_##func,                      \
          lm2_range2i8: range_prefix##_##func,                       \
          lm2_range2u64: range_prefix##_##func,                      \
          lm2_range2u32: range_prefix##_##func,                      \
          lm2_range2u16: range_prefix##_##func,                      \
          lm2_range2u8: range_prefix##_##func,                       \
          lm2_range3f64: range_prefix##_##func,                      \
          lm2_range3f32: range_prefix##_##func,                      \
          lm2_range3i64: range_prefix##_##func,                      \
          lm2_range3i32: range_prefix##_##func,                      \
          lm2_range3i16: range_prefix##_##func,                      \
          lm2_range3i8: range_prefix##_##func,                       \
          lm2_range3u64: range_prefix##_##func,                      \
          lm2_range3u32: range_prefix##_##func,                      \
          lm2_range3u16: range_prefix##_##func,                      \
          lm2_range3u8: range_prefix##_##func,                       \
          lm2_range4f64: range_prefix##_##func,                      \
          lm2_range4f32: range_prefix##_##func,                      \
          lm2_range4i64: range_prefix##_##func,                      \
          lm2_range4i32: range_prefix##_##func,                      \
          lm2_range4i16: range_prefix##_##func,                      \
          lm2_range4i8: range_prefix##_##func,                       \
          lm2_range4u64: range_prefix##_##func,                      \
          lm2_range4u32: range_prefix##_##func,                      \
          lm2_range4u16: range_prefix##_##func,                      \
          lm2_range4u8: range_prefix##_##func,                       \
          lm2_v2f64: range_prefix##_##func##_vec,                    \
          lm2_v2f32: range_prefix##_##func##_vec,                    \
          lm2_v2i64: range_prefix##_##func##_vec,                    \
          lm2_v2i32: range_prefix##_##func##_vec,                    \
          lm2_v2i16: range_prefix##_##func##_vec,                    \
          lm2_v2i8: range_prefix##_##func##_vec,                     \
          lm2_v2u64: range_prefix##_##func##_vec,                    \
          lm2_v2u32: range_prefix##_##func##_vec,                    \
          lm2_v2u16: range_prefix##_##func##_vec,                    \
          lm2_v2u8: range_prefix##_##func##_vec,                     \
          lm2_v3f64: range_prefix##_##func##_vec,                    \
          lm2_v3f32: range_prefix##_##func##_vec,                    \
          lm2_v3i64: range_prefix##_##func##_vec,                    \
          lm2_v3i32: range_prefix##_##func##_vec,                    \
          lm2_v3i16: range_prefix##_##func##_vec,                    \
          lm2_v3i8: range_prefix##_##func##_vec,                     \
          lm2_v3u64: range_prefix##_##func##_vec,                    \
          lm2_v3u32: range_prefix##_##func##_vec,                    \
          lm2_v3u16: range_prefix##_##func##_vec,                    \
          lm2_v3u8: range_prefix##_##func##_vec,                     \
          lm2_v4f64: range_prefix##_##func##_vec,                    \
          lm2_v4f32: range_prefix##_##func##_vec,                    \
          lm2_v4i64: range_prefix##_##func##_vec,                    \
          lm2_v4i32: range_prefix##_##func##_vec,                    \
          lm2_v4i16: range_prefix##_##func##_vec,                    \
          lm2_v4i8: range_prefix##_##func##_vec,                     \
          lm2_v4u64: range_prefix##_##func##_vec,                    \
          lm2_v4u32: range_prefix##_##func##_vec,                    \
          lm2_v4u16: range_prefix##_##func##_vec,                    \
          lm2_v4u8: range_prefix##_##func##_vec,                     \
          double: range_prefix##_##func##_scalar,                    \
          float: range_prefix##_##func##_scalar,                     \
          int64_t: range_prefix##_##func##_scalar,                   \
          int32_t: range_prefix##_##func##_scalar,                   \
          int16_t: range_prefix##_##func##_scalar,                   \
          int8_t: range_prefix##_##func##_scalar,                    \
          uint64_t: range_prefix##_##func##_scalar,                  \
          uint32_t: range_prefix##_##func##_scalar,                  \
          uint16_t: range_prefix##_##func##_scalar,                  \
          uint8_t: range_prefix##_##func##_scalar)(r, x)

// Range2 arithmetic dispatch
#    define _LM2_RANGE2_ARITH(func, r, x)                                           \
      _Generic((r),                                                                 \
          lm2_range2f64: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range2f64, func, r, x), \
          lm2_range2f32: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range2f32, func, r, x), \
          lm2_range2i64: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range2i64, func, r, x), \
          lm2_range2i32: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range2i32, func, r, x), \
          lm2_range2i16: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range2i16, func, r, x), \
          lm2_range2i8: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range2i8, func, r, x),   \
          lm2_range2u64: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range2u64, func, r, x), \
          lm2_range2u32: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range2u32, func, r, x), \
          lm2_range2u16: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range2u16, func, r, x), \
          lm2_range2u8: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range2u8, func, r, x))

// Range3 arithmetic dispatch
#    define _LM2_RANGE3_ARITH(func, r, x)                                           \
      _Generic((r),                                                                 \
          lm2_range3f64: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range3f64, func, r, x), \
          lm2_range3f32: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range3f32, func, r, x), \
          lm2_range3i64: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range3i64, func, r, x), \
          lm2_range3i32: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range3i32, func, r, x), \
          lm2_range3i16: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range3i16, func, r, x), \
          lm2_range3i8: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range3i8, func, r, x),   \
          lm2_range3u64: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range3u64, func, r, x), \
          lm2_range3u32: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range3u32, func, r, x), \
          lm2_range3u16: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range3u16, func, r, x), \
          lm2_range3u8: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range3u8, func, r, x))

// Range4 arithmetic dispatch
#    define _LM2_RANGE4_ARITH(func, r, x)                                           \
      _Generic((r),                                                                 \
          lm2_range4f64: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range4f64, func, r, x), \
          lm2_range4f32: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range4f32, func, r, x), \
          lm2_range4i64: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range4i64, func, r, x), \
          lm2_range4i32: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range4i32, func, r, x), \
          lm2_range4i16: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range4i16, func, r, x), \
          lm2_range4i8: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range4i8, func, r, x),   \
          lm2_range4u64: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range4u64, func, r, x), \
          lm2_range4u32: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range4u32, func, r, x), \
          lm2_range4u16: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range4u16, func, r, x), \
          lm2_range4u8: _LM2_RANGE_ARITHMETIC_DISPATCH(lm2_range4u8, func, r, x))

#  else

// C11 nested _Generic dispatch - same structure as C++
#    define _LM2_RANGE_ARITHMETIC_DISPATCH _LM2_RANGE_ARITHMETIC_DISPATCH
#    define _LM2_RANGE2_ARITH              _LM2_RANGE2_ARITH
#    define _LM2_RANGE3_ARITH              _LM2_RANGE3_ARITH
#    define _LM2_RANGE4_ARITH              _LM2_RANGE4_ARITH

#  endif

#else

// Expands to nothing when generics are disabled
#  define _LM2_GENERIC_RANGE2(name, ...)
#  define _LM2_GENERIC_RANGE3(name, ...)
#  define _LM2_GENERIC_RANGE4(name, ...)
#  define _LM2_RANGE2_ARITH(func, r, x)
#  define _LM2_RANGE3_ARITH(func, r, x)
#  define _LM2_RANGE4_ARITH(func, r, x)

#endif