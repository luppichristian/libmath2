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

#include <lm2/vectors/lm2_vector2.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>

// =============================================================================
// Basic operations
// =============================================================================

#define _LM2_IMPL_V2_VEC_OP(type_name, scalar_suffix, op_name)                     \
  LM2_API type_name lm2_v2_##op_name##_##scalar_suffix(type_name a, type_name b) { \
    type_name result;                                                              \
    result.x = lm2_##op_name##_##scalar_suffix(a.x, b.x);                          \
    result.y = lm2_##op_name##_##scalar_suffix(a.y, b.y);                          \
    return result;                                                                 \
  }

#define _LM2_IMPL_V2_SCALAR_OP(type_name, scalar_type, scalar_suffix, op_name) \
  LM2_API type_name lm2_v2_##op_name##_s_##scalar_suffix(type_name a,          \
                                                         scalar_type b) {      \
    type_name result;                                                          \
    result.x = lm2_##op_name##_##scalar_suffix(a.x, b);                        \
    result.y = lm2_##op_name##_##scalar_suffix(a.y, b);                        \
    return result;                                                             \
  }

#define _LM2_IMPL_V2_ALL_OPS(type_name, scalar_type, scalar_suffix)  \
  _LM2_IMPL_V2_VEC_OP(type_name, scalar_suffix, add)                 \
  _LM2_IMPL_V2_VEC_OP(type_name, scalar_suffix, sub)                 \
  _LM2_IMPL_V2_VEC_OP(type_name, scalar_suffix, mul)                 \
  _LM2_IMPL_V2_VEC_OP(type_name, scalar_suffix, div)                 \
  _LM2_IMPL_V2_SCALAR_OP(type_name, scalar_type, scalar_suffix, add) \
  _LM2_IMPL_V2_SCALAR_OP(type_name, scalar_type, scalar_suffix, sub) \
  _LM2_IMPL_V2_SCALAR_OP(type_name, scalar_type, scalar_suffix, mul) \
  _LM2_IMPL_V2_SCALAR_OP(type_name, scalar_type, scalar_suffix, div)

_LM2_IMPL_V2_ALL_OPS(lm2_v2_f64, double, f64)
_LM2_IMPL_V2_ALL_OPS(lm2_v2_f32, float, f32)
_LM2_IMPL_V2_ALL_OPS(lm2_v2_i64, int64_t, i64)
_LM2_IMPL_V2_ALL_OPS(lm2_v2_i32, int32_t, i32)
_LM2_IMPL_V2_ALL_OPS(lm2_v2_i16, int16_t, i16)
_LM2_IMPL_V2_ALL_OPS(lm2_v2_i8, int8_t, i8)
_LM2_IMPL_V2_ALL_OPS(lm2_v2_u64, uint64_t, u64)
_LM2_IMPL_V2_ALL_OPS(lm2_v2_u32, uint32_t, u32)
_LM2_IMPL_V2_ALL_OPS(lm2_v2_u16, uint16_t, u16)
_LM2_IMPL_V2_ALL_OPS(lm2_v2_u8, uint8_t, u8)

// =============================================================================
// Negation operations
// =============================================================================

#define _LM2_IMPL_V2_NEG(type_name, scalar_type, scalar_suffix) \
  LM2_API type_name lm2_v2_neg_##scalar_suffix(type_name a) {   \
    type_name result;                                           \
    result.x = (scalar_type)(-a.x);                             \
    result.y = (scalar_type)(-a.y);                             \
    return result;                                              \
  }

_LM2_IMPL_V2_NEG(lm2_v2_f64, double, f64)
_LM2_IMPL_V2_NEG(lm2_v2_f32, float, f32)
_LM2_IMPL_V2_NEG(lm2_v2_i64, int64_t, i64)
_LM2_IMPL_V2_NEG(lm2_v2_i32, int32_t, i32)
_LM2_IMPL_V2_NEG(lm2_v2_i16, int16_t, i16)
_LM2_IMPL_V2_NEG(lm2_v2_i8, int8_t, i8)

// =============================================================================
// Scalar functions (only for float/double)
// =============================================================================

#define _LM2_IMPL_V2_SCALAR_FUNC_1(type_name, scalar_suffix, func_name) \
  LM2_API type_name lm2_v2_##func_name##_##scalar_suffix(type_name a) { \
    type_name result;                                                   \
    result.x = lm2_##func_name##_##scalar_suffix(a.x);                  \
    result.y = lm2_##func_name##_##scalar_suffix(a.y);                  \
    return result;                                                      \
  }

#define _LM2_IMPL_V2_SCALAR_FUNC_2(type_name, scalar_suffix, func_name)              \
  LM2_API type_name lm2_v2_##func_name##_##scalar_suffix(type_name a, type_name b) { \
    type_name result;                                                                \
    result.x = lm2_##func_name##_##scalar_suffix(a.x, b.x);                          \
    result.y = lm2_##func_name##_##scalar_suffix(a.y, b.y);                          \
    return result;                                                                   \
  }

#define _LM2_IMPL_V2_SCALAR_FUNC_3(type_name, scalar_suffix, func_name)                           \
  LM2_API type_name lm2_v2_##func_name##_##scalar_suffix(type_name a, type_name b, type_name c) { \
    type_name result;                                                                             \
    result.x = lm2_##func_name##_##scalar_suffix(a.x, b.x, c.x);                                  \
    result.y = lm2_##func_name##_##scalar_suffix(a.y, b.y, c.y);                                  \
    return result;                                                                                \
  }

#define _LM2_IMPL_V2_CLAMP(type_name, scalar_suffix)                                              \
  LM2_API type_name lm2_v2_clamp_##scalar_suffix(type_name value, type_name min, type_name max) { \
    type_name result;                                                                             \
    result.x = lm2_clamp_##scalar_suffix(min.x, value.x, max.x);                                  \
    result.y = lm2_clamp_##scalar_suffix(min.y, value.y, max.y);                                  \
    return result;                                                                                \
  }

#define _LM2_IMPL_V2_SMOOTHSTEP(type_name, scalar_suffix)                                              \
  LM2_API type_name lm2_v2_smoothstep_##scalar_suffix(type_name edge0, type_name edge1, type_name x) { \
    type_name result;                                                                                  \
    result.x = lm2_smoothstep_##scalar_suffix(edge0.x, x.x, edge1.x);                                  \
    result.y = lm2_smoothstep_##scalar_suffix(edge0.y, x.y, edge1.y);                                  \
    return result;                                                                                     \
  }

#define _LM2_IMPL_V2_ALPHA(type_name, scalar_suffix)                                          \
  LM2_API type_name lm2_v2_alpha_##scalar_suffix(type_name a, type_name b, type_name value) { \
    type_name result;                                                                         \
    result.x = lm2_alpha_##scalar_suffix(a.x, value.x, b.x);                                  \
    result.y = lm2_alpha_##scalar_suffix(a.y, value.y, b.y);                                  \
    return result;                                                                            \
  }

#define _LM2_IMPL_V2_ALL_SCALAR_FUNCS(type_name, scalar_suffix)        \
  _LM2_IMPL_V2_SCALAR_FUNC_1(type_name, scalar_suffix, floor)          \
  _LM2_IMPL_V2_SCALAR_FUNC_1(type_name, scalar_suffix, ceil)           \
  _LM2_IMPL_V2_SCALAR_FUNC_1(type_name, scalar_suffix, round)          \
  _LM2_IMPL_V2_SCALAR_FUNC_1(type_name, scalar_suffix, trunc)          \
  _LM2_IMPL_V2_SCALAR_FUNC_1(type_name, scalar_suffix, abs)            \
  _LM2_IMPL_V2_SCALAR_FUNC_1(type_name, scalar_suffix, sign)           \
  _LM2_IMPL_V2_SCALAR_FUNC_1(type_name, scalar_suffix, sign0)          \
  _LM2_IMPL_V2_SCALAR_FUNC_1(type_name, scalar_suffix, saturate)       \
  _LM2_IMPL_V2_SCALAR_FUNC_1(type_name, scalar_suffix, fract)          \
  _LM2_IMPL_V2_SCALAR_FUNC_1(type_name, scalar_suffix, sqrt)           \
  _LM2_IMPL_V2_SCALAR_FUNC_2(type_name, scalar_suffix, floor_multiple) \
  _LM2_IMPL_V2_SCALAR_FUNC_2(type_name, scalar_suffix, ceil_multiple)  \
  _LM2_IMPL_V2_SCALAR_FUNC_2(type_name, scalar_suffix, round_multiple) \
  _LM2_IMPL_V2_SCALAR_FUNC_2(type_name, scalar_suffix, trunc_multiple) \
  _LM2_IMPL_V2_SCALAR_FUNC_2(type_name, scalar_suffix, min)            \
  _LM2_IMPL_V2_SCALAR_FUNC_2(type_name, scalar_suffix, min_abs)        \
  _LM2_IMPL_V2_SCALAR_FUNC_2(type_name, scalar_suffix, max)            \
  _LM2_IMPL_V2_SCALAR_FUNC_2(type_name, scalar_suffix, max_abs)        \
  _LM2_IMPL_V2_SCALAR_FUNC_2(type_name, scalar_suffix, mod)            \
  _LM2_IMPL_V2_SCALAR_FUNC_2(type_name, scalar_suffix, pow)            \
  _LM2_IMPL_V2_CLAMP(type_name, scalar_suffix)                         \
  _LM2_IMPL_V2_SCALAR_FUNC_3(type_name, scalar_suffix, lerp)           \
  _LM2_IMPL_V2_SMOOTHSTEP(type_name, scalar_suffix)                    \
  _LM2_IMPL_V2_ALPHA(type_name, scalar_suffix)

_LM2_IMPL_V2_ALL_SCALAR_FUNCS(lm2_v2_f64, f64)
_LM2_IMPL_V2_ALL_SCALAR_FUNCS(lm2_v2_f32, f32)

// =============================================================================
// Integer scalar functions
// =============================================================================

#define _LM2_IMPL_V2_SIGNED_INT_FUNCS(type_name, scalar_suffix) \
  _LM2_IMPL_V2_SCALAR_FUNC_1(type_name, scalar_suffix, abs)     \
  _LM2_IMPL_V2_SCALAR_FUNC_1(type_name, scalar_suffix, sign)    \
  _LM2_IMPL_V2_SCALAR_FUNC_1(type_name, scalar_suffix, sign0)   \
  _LM2_IMPL_V2_SCALAR_FUNC_2(type_name, scalar_suffix, min)     \
  _LM2_IMPL_V2_SCALAR_FUNC_2(type_name, scalar_suffix, min_abs) \
  _LM2_IMPL_V2_SCALAR_FUNC_2(type_name, scalar_suffix, max)     \
  _LM2_IMPL_V2_SCALAR_FUNC_2(type_name, scalar_suffix, max_abs) \
  _LM2_IMPL_V2_SCALAR_FUNC_2(type_name, scalar_suffix, mod)     \
  _LM2_IMPL_V2_CLAMP(type_name, scalar_suffix)

#define _LM2_IMPL_V2_UNSIGNED_INT_FUNCS(type_name, scalar_suffix) \
  _LM2_IMPL_V2_SCALAR_FUNC_2(type_name, scalar_suffix, min)       \
  _LM2_IMPL_V2_SCALAR_FUNC_2(type_name, scalar_suffix, max)       \
  _LM2_IMPL_V2_CLAMP(type_name, scalar_suffix)

_LM2_IMPL_V2_SIGNED_INT_FUNCS(lm2_v2_i64, i64)
_LM2_IMPL_V2_SIGNED_INT_FUNCS(lm2_v2_i32, i32)
_LM2_IMPL_V2_SIGNED_INT_FUNCS(lm2_v2_i16, i16)
_LM2_IMPL_V2_SIGNED_INT_FUNCS(lm2_v2_i8, i8)

_LM2_IMPL_V2_UNSIGNED_INT_FUNCS(lm2_v2_u64, u64)
_LM2_IMPL_V2_UNSIGNED_INT_FUNCS(lm2_v2_u32, u32)
_LM2_IMPL_V2_UNSIGNED_INT_FUNCS(lm2_v2_u16, u16)
_LM2_IMPL_V2_UNSIGNED_INT_FUNCS(lm2_v2_u8, u8)

// =============================================================================
// V2 Constructors
// =============================================================================

#define _LM2_IMPL_V2_ALL_CONSTRUCTORS(type_name, scalar_type, scalar_suffix)    \
  LM2_API type_name lm2_v2_make_##scalar_suffix(scalar_type x, scalar_type y) { \
    type_name result = {                                                        \
        {x, y} \
    };                                                                \
    return result;                                                              \
  }                                                                             \
  LM2_API type_name lm2_v2_splat_##scalar_suffix(scalar_type v) {               \
    type_name result = {                                                        \
        {v, v} \
    };                                                                \
    return result;                                                              \
  }                                                                             \
  LM2_API type_name lm2_v2_zero_##scalar_suffix(void) {                         \
    type_name result = {                                                        \
        {(scalar_type)0, (scalar_type)0} \
    };                                      \
    return result;                                                              \
  }

_LM2_IMPL_V2_ALL_CONSTRUCTORS(lm2_v2_f64, double, f64)
_LM2_IMPL_V2_ALL_CONSTRUCTORS(lm2_v2_f32, float, f32)
_LM2_IMPL_V2_ALL_CONSTRUCTORS(lm2_v2_i64, int64_t, i64)
_LM2_IMPL_V2_ALL_CONSTRUCTORS(lm2_v2_i32, int32_t, i32)
_LM2_IMPL_V2_ALL_CONSTRUCTORS(lm2_v2_i16, int16_t, i16)
_LM2_IMPL_V2_ALL_CONSTRUCTORS(lm2_v2_i8, int8_t, i8)
_LM2_IMPL_V2_ALL_CONSTRUCTORS(lm2_v2_u64, uint64_t, u64)
_LM2_IMPL_V2_ALL_CONSTRUCTORS(lm2_v2_u32, uint32_t, u32)
_LM2_IMPL_V2_ALL_CONSTRUCTORS(lm2_v2_u16, uint16_t, u16)
_LM2_IMPL_V2_ALL_CONSTRUCTORS(lm2_v2_u8, uint8_t, u8)
