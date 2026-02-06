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

#include <libmath2/libmath2_vector3.h>
#include <libmath2/libmath2_safe_ops.h>
#include <libmath2/libmath2_scalar.h>

// =============================================================================
// Implementation Macros
// =============================================================================

#define _LM2_IMPL_V3_VEC_OP(type_name, scalar_suffix, op_name)        \
  LM2_API type_name op_name##_##type_name(type_name a, type_name b) { \
    type_name result;                                                 \
    result.x = op_name##_##scalar_suffix(a.x, b.x);                   \
    result.y = op_name##_##scalar_suffix(a.y, b.y);                   \
    result.z = op_name##_##scalar_suffix(a.z, b.z);                   \
    return result;                                                    \
  }

#define _LM2_IMPL_V3_SCALAR_OP(type_name, scalar_type, scalar_suffix, op_name) \
  LM2_API type_name op_name##_##type_name##_##scalar_type(type_name a,         \
                                                          scalar_type b) {     \
    type_name result;                                                          \
    result.x = op_name##_##scalar_suffix(a.x, b);                              \
    result.y = op_name##_##scalar_suffix(a.y, b);                              \
    result.z = op_name##_##scalar_suffix(a.z, b);                              \
    return result;                                                             \
  }

#define _LM2_IMPL_V3_NEG(type_name, scalar_type)       \
  LM2_API type_name lm2_neg_##type_name(type_name a) { \
    type_name result;                                  \
    result.x = (scalar_type)(-a.x);                    \
    result.y = (scalar_type)(-a.y);                    \
    result.z = (scalar_type)(-a.z);                    \
    return result;                                     \
  }

#define _LM2_IMPL_V3_ALL_OPS(type_name, scalar_type, scalar_suffix)      \
  _LM2_IMPL_V3_VEC_OP(type_name, scalar_suffix, lm2_add)                 \
  _LM2_IMPL_V3_VEC_OP(type_name, scalar_suffix, lm2_sub)                 \
  _LM2_IMPL_V3_VEC_OP(type_name, scalar_suffix, lm2_mul)                 \
  _LM2_IMPL_V3_VEC_OP(type_name, scalar_suffix, lm2_div)                 \
  _LM2_IMPL_V3_SCALAR_OP(type_name, scalar_type, scalar_suffix, lm2_add) \
  _LM2_IMPL_V3_SCALAR_OP(type_name, scalar_type, scalar_suffix, lm2_sub) \
  _LM2_IMPL_V3_SCALAR_OP(type_name, scalar_type, scalar_suffix, lm2_mul) \
  _LM2_IMPL_V3_SCALAR_OP(type_name, scalar_type, scalar_suffix, lm2_div) \
  _LM2_IMPL_V3_NEG(type_name, scalar_type)

#define _LM2_IMPL_V3_SCALAR_FUNC_1(type_name, scalar_suffix, func_name) \
  LM2_API type_name func_name##_##type_name(type_name a) {              \
    type_name result;                                                   \
    result.x = func_name##_##scalar_suffix(a.x);                        \
    result.y = func_name##_##scalar_suffix(a.y);                        \
    result.z = func_name##_##scalar_suffix(a.z);                        \
    return result;                                                      \
  }

#define _LM2_IMPL_V3_SCALAR_FUNC_2(type_name, scalar_suffix, func_name) \
  LM2_API type_name func_name##_##type_name(type_name a, type_name b) { \
    type_name result;                                                   \
    result.x = func_name##_##scalar_suffix(a.x, b.x);                   \
    result.y = func_name##_##scalar_suffix(a.y, b.y);                   \
    result.z = func_name##_##scalar_suffix(a.z, b.z);                   \
    return result;                                                      \
  }

#define _LM2_IMPL_V3_SCALAR_FUNC_3(type_name, scalar_suffix, func_name)              \
  LM2_API type_name func_name##_##type_name(type_name a, type_name b, type_name c) { \
    type_name result;                                                                \
    result.x = func_name##_##scalar_suffix(a.x, b.x, c.x);                           \
    result.y = func_name##_##scalar_suffix(a.y, b.y, c.y);                           \
    result.z = func_name##_##scalar_suffix(a.z, b.z, c.z);                           \
    return result;                                                                   \
  }

// =============================================================================
// Vector3 Implementations
// =============================================================================

_LM2_IMPL_V3_ALL_OPS(lm2_v3f64, double, f64)
_LM2_IMPL_V3_ALL_OPS(lm2_v3f32, float, f32)
_LM2_IMPL_V3_ALL_OPS(lm2_v3i64, int64_t, i64)
_LM2_IMPL_V3_ALL_OPS(lm2_v3i32, int32_t, i32)
_LM2_IMPL_V3_ALL_OPS(lm2_v3i16, int16_t, i16)
_LM2_IMPL_V3_ALL_OPS(lm2_v3i8, int8_t, i8)
_LM2_IMPL_V3_ALL_OPS(lm2_v3u64, uint64_t, u64)
_LM2_IMPL_V3_ALL_OPS(lm2_v3u32, uint32_t, u32)
_LM2_IMPL_V3_ALL_OPS(lm2_v3u16, uint16_t, u16)
_LM2_IMPL_V3_ALL_OPS(lm2_v3u8, uint8_t, u8)

// =============================================================================
// Macro to generate all scalar function implementations for a vector type
// =============================================================================

#define _LM2_IMPL_V3_ALL_SCALAR_FUNCS(type_name, scalar_suffix)            \
  _LM2_IMPL_V3_SCALAR_FUNC_1(type_name, scalar_suffix, lm2_floor)          \
  _LM2_IMPL_V3_SCALAR_FUNC_1(type_name, scalar_suffix, lm2_ceil)           \
  _LM2_IMPL_V3_SCALAR_FUNC_1(type_name, scalar_suffix, lm2_round)          \
  _LM2_IMPL_V3_SCALAR_FUNC_1(type_name, scalar_suffix, lm2_trunc)          \
  _LM2_IMPL_V3_SCALAR_FUNC_1(type_name, scalar_suffix, lm2_abs)            \
  _LM2_IMPL_V3_SCALAR_FUNC_1(type_name, scalar_suffix, lm2_sign)           \
  _LM2_IMPL_V3_SCALAR_FUNC_1(type_name, scalar_suffix, lm2_sign0)          \
  _LM2_IMPL_V3_SCALAR_FUNC_1(type_name, scalar_suffix, lm2_saturate)       \
  _LM2_IMPL_V3_SCALAR_FUNC_1(type_name, scalar_suffix, lm2_fract)          \
  _LM2_IMPL_V3_SCALAR_FUNC_1(type_name, scalar_suffix, lm2_norm)           \
  _LM2_IMPL_V3_SCALAR_FUNC_1(type_name, scalar_suffix, lm2_sqrt)           \
  _LM2_IMPL_V3_SCALAR_FUNC_2(type_name, scalar_suffix, lm2_floor_multiple) \
  _LM2_IMPL_V3_SCALAR_FUNC_2(type_name, scalar_suffix, lm2_ceil_multiple)  \
  _LM2_IMPL_V3_SCALAR_FUNC_2(type_name, scalar_suffix, lm2_round_multiple) \
  _LM2_IMPL_V3_SCALAR_FUNC_2(type_name, scalar_suffix, lm2_trunc_multiple) \
  _LM2_IMPL_V3_SCALAR_FUNC_2(type_name, scalar_suffix, lm2_min)            \
  _LM2_IMPL_V3_SCALAR_FUNC_2(type_name, scalar_suffix, lm2_min_abs)        \
  _LM2_IMPL_V3_SCALAR_FUNC_2(type_name, scalar_suffix, lm2_max)            \
  _LM2_IMPL_V3_SCALAR_FUNC_2(type_name, scalar_suffix, lm2_max_abs)        \
  _LM2_IMPL_V3_SCALAR_FUNC_2(type_name, scalar_suffix, lm2_mod)            \
  _LM2_IMPL_V3_SCALAR_FUNC_2(type_name, scalar_suffix, lm2_pow)            \
  _LM2_IMPL_V3_SCALAR_FUNC_3(type_name, scalar_suffix, lm2_clamp)          \
  _LM2_IMPL_V3_SCALAR_FUNC_3(type_name, scalar_suffix, lm2_lerp)           \
  _LM2_IMPL_V3_SCALAR_FUNC_3(type_name, scalar_suffix, lm2_smoothstep)     \
  _LM2_IMPL_V3_SCALAR_FUNC_3(type_name, scalar_suffix, lm2_alpha)

// =============================================================================
// Scalar Function Implementations
// =============================================================================

_LM2_IMPL_V3_ALL_SCALAR_FUNCS(lm2_v3f64, f64)
_LM2_IMPL_V3_ALL_SCALAR_FUNCS(lm2_v3f32, f32)
_LM2_IMPL_V3_ALL_SCALAR_FUNCS(lm2_v3i64, i64)
_LM2_IMPL_V3_ALL_SCALAR_FUNCS(lm2_v3i32, i32)
_LM2_IMPL_V3_ALL_SCALAR_FUNCS(lm2_v3i16, i16)
_LM2_IMPL_V3_ALL_SCALAR_FUNCS(lm2_v3i8, i8)
_LM2_IMPL_V3_ALL_SCALAR_FUNCS(lm2_v3u64, u64)
_LM2_IMPL_V3_ALL_SCALAR_FUNCS(lm2_v3u32, u32)
_LM2_IMPL_V3_ALL_SCALAR_FUNCS(lm2_v3u16, u16)
_LM2_IMPL_V3_ALL_SCALAR_FUNCS(lm2_v3u8, u8)
