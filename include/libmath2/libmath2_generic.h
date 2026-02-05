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

// These macros reduce the boilerplate needed to define a type-generic function
// that dispatches across the 10 standard numeric types (f64, f32, i64, i32, i16, i8, u64, u32, u16, u8).

#ifndef LM2_NO_GENERICS
#  ifdef __cplusplus
#    include <type_traits>

// Generic dispatcher function - switches on template type
template <typename T, typename... Args>
inline auto _lm2_generic(auto&& f64, auto&& f32, auto&& i64, auto&& i32, auto&& i16, auto&& i8, auto&& u64, auto&& u32, auto&& u16, auto&& u8, T first, Args&&... rest) -> decltype(auto) {
  using _LM2_T = std::remove_cvref_t<T>;
  if constexpr (std::is_same_v<_LM2_T, double>) return f64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, float>)
    return f32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, int64_t>)
    return i64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, int32_t>)
    return i32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, int16_t>)
    return i16(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, int8_t>)
    return i8(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, uint64_t>)
    return u64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, uint32_t>)
    return u32(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, uint16_t>)
    return u16(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, uint8_t>)
    return u8(first, rest...);
  else
    static_assert(sizeof(_LM2_T) == 0, "Unsupported type");
}

// C++17 expression-level dispatch using generic dispatcher function
// Usage: #define lm2_sum(...) _LM2_GENERIC(lm2_sum, __VA_ARGS__)
#    define _LM2_GENERIC(name, ...) \
      _lm2_generic(name##_f64, name##_f32, name##_i64, name##_i32, name##_i16, name##_i8, name##_u64, name##_u32, name##_u16, name##_u8, __VA_ARGS__)

#  else

// C11 _Generic expression-level dispatch.
// Usage: #define lm2_sum(...) _LM2_GENERIC(lm2_sum, __VA_ARGS__)
#    define _LM2_GENERIC(name, ...) \
      _Generic((__VA_ARGS__),       \
          double: name##_f64,       \
          float: name##_f32,        \
          int64_t: name##_i64,      \
          int32_t: name##_i32,      \
          int16_t: name##_i16,      \
          int8_t: name##_i8,        \
          uint64_t: name##_u64,     \
          uint32_t: name##_u32,     \
          uint16_t: name##_u16,     \
          uint8_t: name##_u8)(__VA_ARGS__)

#  endif

#else

// Expands to nothing
#  define _LM2_GENERIC(name, ...)

#endif