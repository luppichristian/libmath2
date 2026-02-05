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

#include <libmath2/libmath2_vector2.h>
#include <libmath2/libmath2_safe_ops.h>

// =============================================================================
// Implementation Macros
// =============================================================================

#define _LM2_IMPL_V2_VEC_OP(type_name, scalar_suffix, op_name)                 \
  LM2_API type_name op_name##_##type_name(type_name a, type_name b) {          \
    type_name result;                                                          \
    result.x = op_name##_##scalar_suffix(a.x, b.x);                            \
    result.y = op_name##_##scalar_suffix(a.y, b.y);                            \
    return result;                                                             \
  }

#define _LM2_IMPL_V2_SCALAR_OP(type_name, scalar_type, scalar_suffix, op_name)    \
  LM2_API type_name op_name##_##type_name##_##scalar_type(type_name a,           \
                                                          scalar_type b) {       \
    type_name result;                                                            \
    result.x = op_name##_##scalar_suffix(a.x, b);                                \
    result.y = op_name##_##scalar_suffix(a.y, b);                                \
    return result;                                                               \
  }

#define _LM2_IMPL_V2_NEG(type_name, scalar_type)                                 \
  LM2_API type_name lm2_neg_##type_name(type_name a) {                           \
    type_name result;                                                            \
    result.x = (scalar_type)(-a.x);                                              \
    result.y = (scalar_type)(-a.y);                                              \
    return result;                                                               \
  }

#define _LM2_IMPL_V2_ALL_OPS(type_name, scalar_type, scalar_suffix)            \
  _LM2_IMPL_V2_VEC_OP(type_name, scalar_suffix, lm2_add)                       \
  _LM2_IMPL_V2_VEC_OP(type_name, scalar_suffix, lm2_sub)                       \
  _LM2_IMPL_V2_VEC_OP(type_name, scalar_suffix, lm2_mul)                       \
  _LM2_IMPL_V2_VEC_OP(type_name, scalar_suffix, lm2_div)                       \
  _LM2_IMPL_V2_SCALAR_OP(type_name, scalar_type, scalar_suffix, lm2_add)       \
  _LM2_IMPL_V2_SCALAR_OP(type_name, scalar_type, scalar_suffix, lm2_sub)       \
  _LM2_IMPL_V2_SCALAR_OP(type_name, scalar_type, scalar_suffix, lm2_mul)       \
  _LM2_IMPL_V2_SCALAR_OP(type_name, scalar_type, scalar_suffix, lm2_div)       \
  _LM2_IMPL_V2_NEG(type_name, scalar_type)

// =============================================================================
// Vector2 Implementations
// =============================================================================

_LM2_IMPL_V2_ALL_OPS(lm2_v2f64, double, f64)
_LM2_IMPL_V2_ALL_OPS(lm2_v2f32, float, f32)
_LM2_IMPL_V2_ALL_OPS(lm2_v2i64, int64_t, i64)
_LM2_IMPL_V2_ALL_OPS(lm2_v2i32, int32_t, i32)
_LM2_IMPL_V2_ALL_OPS(lm2_v2i16, int16_t, i16)
_LM2_IMPL_V2_ALL_OPS(lm2_v2i8, int8_t, i8)
_LM2_IMPL_V2_ALL_OPS(lm2_v2u64, uint64_t, u64)
_LM2_IMPL_V2_ALL_OPS(lm2_v2u32, uint32_t, u32)
_LM2_IMPL_V2_ALL_OPS(lm2_v2u16, uint16_t, u16)
_LM2_IMPL_V2_ALL_OPS(lm2_v2u8, uint8_t, u8)
