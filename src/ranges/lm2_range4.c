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

#include <lm2/ranges/lm2_range4.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/vectors/lm2_vector4.h>

// =============================================================================
// Constructors
// =============================================================================

#define _LM2_IMPL_R4_CONSTRUCTORS(type_name, vec_type, scalar_type, scalar_suffix)                  \
  LM2_API type_name lm2_r4_from_min_max_##scalar_suffix(vec_type min, vec_type max) {               \
    type_name result;                                                                               \
    result.min = min;                                                                               \
    result.max = max;                                                                               \
    return result;                                                                                  \
  }                                                                                                 \
  LM2_API type_name lm2_r4_from_center_extents_##scalar_suffix(vec_type center, vec_type extents) { \
    type_name result;                                                                               \
    result.min = lm2_v4_sub_##scalar_suffix(center, extents);                                       \
    result.max = lm2_v4_add_##scalar_suffix(center, extents);                                       \
    return result;                                                                                  \
  }                                                                                                 \
  LM2_API type_name lm2_r4_from_center_size_##scalar_suffix(vec_type center, vec_type size) {       \
    vec_type half_size = lm2_v4_mul_s_##scalar_suffix(size, (scalar_type)0.5);                      \
    type_name result;                                                                               \
    result.min = lm2_v4_sub_##scalar_suffix(center, half_size);                                     \
    result.max = lm2_v4_add_##scalar_suffix(center, half_size);                                     \
    return result;                                                                                  \
  }                                                                                                 \
  LM2_API type_name lm2_r4_from_position_size_##scalar_suffix(vec_type position, vec_type size) {   \
    type_name result;                                                                               \
    result.min = position;                                                                          \
    result.max = lm2_v4_add_##scalar_suffix(position, size);                                        \
    return result;                                                                                  \
  }                                                                                                 \
  LM2_API type_name lm2_r4_zero_##scalar_suffix(void) {                                             \
    type_name result;                                                                               \
    result.min = lm2_v4_zero_##scalar_suffix();                                                     \
    result.max = lm2_v4_zero_##scalar_suffix();                                                     \
    return result;                                                                                  \
  }

// =============================================================================
// Arithmetic operations
// =============================================================================

#define _LM2_IMPL_R4_RANGE_OP(type_name, scalar_suffix, op_name)                   \
  LM2_API type_name lm2_r4_##op_name##_##scalar_suffix(type_name a, type_name b) { \
    type_name result;                                                              \
    result.min = lm2_v4_##op_name##_##scalar_suffix(a.min, b.min);                 \
    result.max = lm2_v4_##op_name##_##scalar_suffix(a.max, b.max);                 \
    return result;                                                                 \
  }

#define _LM2_IMPL_R4_SCALAR_OP(type_name, vec_type, scalar_type, scalar_suffix, op_name) \
  LM2_API type_name lm2_r4_##op_name##_s_##scalar_suffix(type_name a, scalar_type s) {   \
    type_name result;                                                                    \
    result.min = lm2_v4_##op_name##_s_##scalar_suffix(a.min, s);                         \
    result.max = lm2_v4_##op_name##_s_##scalar_suffix(a.max, s);                         \
    return result;                                                                       \
  }

#define _LM2_IMPL_R4_VECTOR_OP(type_name, vec_type, scalar_suffix, op_name)         \
  LM2_API type_name lm2_r4_##op_name##_v_##scalar_suffix(type_name a, vec_type v) { \
    type_name result;                                                               \
    result.min = lm2_v4_##op_name##_##scalar_suffix(a.min, v);                      \
    result.max = lm2_v4_##op_name##_##scalar_suffix(a.max, v);                      \
    return result;                                                                  \
  }

#define _LM2_IMPL_R4_BASIC_OPS(type_name, vec_type, scalar_type, scalar_suffix) \
  _LM2_IMPL_R4_RANGE_OP(type_name, scalar_suffix, add)                          \
  _LM2_IMPL_R4_RANGE_OP(type_name, scalar_suffix, sub)                          \
  _LM2_IMPL_R4_RANGE_OP(type_name, scalar_suffix, mul)                          \
  _LM2_IMPL_R4_RANGE_OP(type_name, scalar_suffix, div)                          \
  _LM2_IMPL_R4_SCALAR_OP(type_name, vec_type, scalar_type, scalar_suffix, add)  \
  _LM2_IMPL_R4_SCALAR_OP(type_name, vec_type, scalar_type, scalar_suffix, sub)  \
  _LM2_IMPL_R4_SCALAR_OP(type_name, vec_type, scalar_type, scalar_suffix, mul)  \
  _LM2_IMPL_R4_SCALAR_OP(type_name, vec_type, scalar_type, scalar_suffix, div)  \
  _LM2_IMPL_R4_VECTOR_OP(type_name, vec_type, scalar_suffix, add)               \
  _LM2_IMPL_R4_VECTOR_OP(type_name, vec_type, scalar_suffix, sub)               \
  _LM2_IMPL_R4_VECTOR_OP(type_name, vec_type, scalar_suffix, mul)               \
  _LM2_IMPL_R4_VECTOR_OP(type_name, vec_type, scalar_suffix, div)

#define _LM2_IMPL_R4_MOD_SCALAR(type_name, vec_type, scalar_type, scalar_suffix) \
  LM2_API type_name lm2_r4_mod_s_##scalar_suffix(type_name a, scalar_type s) {   \
    type_name result;                                                            \
    result.min.x = lm2_mod_##scalar_suffix(a.min.x, s);                          \
    result.min.y = lm2_mod_##scalar_suffix(a.min.y, s);                          \
    result.min.z = lm2_mod_##scalar_suffix(a.min.z, s);                          \
    result.min.w = lm2_mod_##scalar_suffix(a.min.w, s);                          \
    result.max.x = lm2_mod_##scalar_suffix(a.max.x, s);                          \
    result.max.y = lm2_mod_##scalar_suffix(a.max.y, s);                          \
    result.max.z = lm2_mod_##scalar_suffix(a.max.z, s);                          \
    result.max.w = lm2_mod_##scalar_suffix(a.max.w, s);                          \
    return result;                                                               \
  }

#define _LM2_IMPL_R4_ALL_OPS(type_name, vec_type, scalar_type, scalar_suffix) \
  _LM2_IMPL_R4_BASIC_OPS(type_name, vec_type, scalar_type, scalar_suffix)     \
  _LM2_IMPL_R4_RANGE_OP(type_name, scalar_suffix, mod)                        \
  _LM2_IMPL_R4_MOD_SCALAR(type_name, vec_type, scalar_type, scalar_suffix)    \
  _LM2_IMPL_R4_VECTOR_OP(type_name, vec_type, scalar_suffix, mod)

// =============================================================================
// Scalar function forwards
// =============================================================================

#define _LM2_IMPL_R4_SCALAR_FUNC_1(type_name, scalar_suffix, func_name) \
  LM2_API type_name lm2_r4_##func_name##_##scalar_suffix(type_name a) { \
    type_name result;                                                   \
    result.min = lm2_v4_##func_name##_##scalar_suffix(a.min);           \
    result.max = lm2_v4_##func_name##_##scalar_suffix(a.max);           \
    return result;                                                      \
  }

#define _LM2_IMPL_R4_SCALAR_FUNC_2(type_name, scalar_suffix, func_name)              \
  LM2_API type_name lm2_r4_##func_name##_##scalar_suffix(type_name a, type_name b) { \
    type_name result;                                                                \
    result.min = lm2_v4_##func_name##_##scalar_suffix(a.min, b.min);                 \
    result.max = lm2_v4_##func_name##_##scalar_suffix(a.max, b.max);                 \
    return result;                                                                   \
  }

#define _LM2_IMPL_R4_SCALAR_FUNC_3(type_name, scalar_suffix, func_name)                           \
  LM2_API type_name lm2_r4_##func_name##_##scalar_suffix(type_name a, type_name b, type_name c) { \
    type_name result;                                                                             \
    result.min = lm2_v4_##func_name##_##scalar_suffix(a.min, b.min, c.min);                       \
    result.max = lm2_v4_##func_name##_##scalar_suffix(a.max, b.max, c.max);                       \
    return result;                                                                                \
  }

#define _LM2_IMPL_R4_CLAMP(type_name, scalar_suffix)                                      \
  LM2_API type_name lm2_r4_clamp_##scalar_suffix(type_name a, type_name b, type_name c) { \
    type_name result;                                                                     \
    result.min = lm2_v4_clamp_##scalar_suffix(a.min, b.min, c.min);                       \
    result.max = lm2_v4_clamp_##scalar_suffix(a.max, b.max, c.max);                       \
    return result;                                                                        \
  }

#define _LM2_IMPL_R4_SMOOTHSTEP(type_name, scalar_suffix)                                              \
  LM2_API type_name lm2_r4_smoothstep_##scalar_suffix(type_name edge0, type_name x, type_name edge1) { \
    type_name result;                                                                                  \
    result.min = lm2_v4_smoothstep_##scalar_suffix(edge0.min, x.min, edge1.min);                       \
    result.max = lm2_v4_smoothstep_##scalar_suffix(edge0.max, x.max, edge1.max);                       \
    return result;                                                                                     \
  }

#define _LM2_IMPL_R4_ALPHA(type_name, scalar_suffix)                                          \
  LM2_API type_name lm2_r4_alpha_##scalar_suffix(type_name a, type_name value, type_name b) { \
    type_name result;                                                                         \
    result.min = lm2_v4_alpha_##scalar_suffix(a.min, value.min, b.min);                       \
    result.max = lm2_v4_alpha_##scalar_suffix(a.max, value.max, b.max);                       \
    return result;                                                                            \
  }

#define _LM2_IMPL_R4_ALL_SCALAR_FUNCS(type_name, scalar_suffix)        \
  _LM2_IMPL_R4_SCALAR_FUNC_1(type_name, scalar_suffix, floor)          \
  _LM2_IMPL_R4_SCALAR_FUNC_1(type_name, scalar_suffix, ceil)           \
  _LM2_IMPL_R4_SCALAR_FUNC_1(type_name, scalar_suffix, round)          \
  _LM2_IMPL_R4_SCALAR_FUNC_1(type_name, scalar_suffix, trunc)          \
  _LM2_IMPL_R4_SCALAR_FUNC_1(type_name, scalar_suffix, abs)            \
  _LM2_IMPL_R4_SCALAR_FUNC_1(type_name, scalar_suffix, sign)           \
  _LM2_IMPL_R4_SCALAR_FUNC_1(type_name, scalar_suffix, sign0)          \
  _LM2_IMPL_R4_SCALAR_FUNC_1(type_name, scalar_suffix, saturate)       \
  _LM2_IMPL_R4_SCALAR_FUNC_1(type_name, scalar_suffix, fract)          \
  _LM2_IMPL_R4_SCALAR_FUNC_1(type_name, scalar_suffix, sqrt)           \
  _LM2_IMPL_R4_SCALAR_FUNC_2(type_name, scalar_suffix, floor_multiple) \
  _LM2_IMPL_R4_SCALAR_FUNC_2(type_name, scalar_suffix, ceil_multiple)  \
  _LM2_IMPL_R4_SCALAR_FUNC_2(type_name, scalar_suffix, round_multiple) \
  _LM2_IMPL_R4_SCALAR_FUNC_2(type_name, scalar_suffix, trunc_multiple) \
  _LM2_IMPL_R4_SCALAR_FUNC_2(type_name, scalar_suffix, min)            \
  _LM2_IMPL_R4_SCALAR_FUNC_2(type_name, scalar_suffix, min_abs)        \
  _LM2_IMPL_R4_SCALAR_FUNC_2(type_name, scalar_suffix, max)            \
  _LM2_IMPL_R4_SCALAR_FUNC_2(type_name, scalar_suffix, max_abs)        \
  _LM2_IMPL_R4_SCALAR_FUNC_2(type_name, scalar_suffix, pow)            \
  _LM2_IMPL_R4_CLAMP(type_name, scalar_suffix)                         \
  _LM2_IMPL_R4_SCALAR_FUNC_3(type_name, scalar_suffix, lerp)           \
  _LM2_IMPL_R4_SMOOTHSTEP(type_name, scalar_suffix)                    \
  _LM2_IMPL_R4_ALPHA(type_name, scalar_suffix)

// =============================================================================
// Range-specific functions
// =============================================================================

#define _LM2_IMPL_R4_UNION(type_name, vec_type, scalar_suffix)               \
  LM2_API type_name lm2_r4_union_##scalar_suffix(type_name a, type_name b) { \
    type_name result;                                                        \
    result.min = lm2_v4_min_##scalar_suffix(a.min, b.min);                   \
    result.max = lm2_v4_max_##scalar_suffix(a.max, b.max);                   \
    return result;                                                           \
  }

#define _LM2_IMPL_R4_INTERSECTION(type_name, vec_type, scalar_suffix)               \
  LM2_API type_name lm2_r4_intersection_##scalar_suffix(type_name a, type_name b) { \
    type_name result;                                                               \
    result.min = lm2_v4_max_##scalar_suffix(a.min, b.min);                          \
    result.max = lm2_v4_min_##scalar_suffix(a.max, b.max);                          \
    return result;                                                                  \
  }

#define _LM2_IMPL_R4_SIZE(type_name, vec_type, scalar_suffix) \
  LM2_API vec_type lm2_r4_size_##scalar_suffix(type_name r) { \
    return lm2_v4_sub_##scalar_suffix(r.max, r.min);          \
  }

#define _LM2_IMPL_R4_EXTENTS(type_name, vec_type, scalar_type, scalar_suffix) \
  LM2_API vec_type lm2_r4_extents_##scalar_suffix(type_name r) {              \
    vec_type size = lm2_v4_sub_##scalar_suffix(r.max, r.min);                 \
    return lm2_v4_mul_s_##scalar_suffix(size, (scalar_type)0.5);              \
  }

#define _LM2_IMPL_R4_CENTER(type_name, vec_type, scalar_type, scalar_suffix) \
  LM2_API vec_type lm2_r4_center_##scalar_suffix(type_name r) {              \
    vec_type sum = lm2_v4_add_##scalar_suffix(r.min, r.max);                 \
    return lm2_v4_mul_s_##scalar_suffix(sum, (scalar_type)0.5);              \
  }

#define _LM2_IMPL_R4_CONTAINS_POINT(type_name, vec_type, scalar_type, scalar_suffix) \
  LM2_API int lm2_r4_contains_point_##scalar_suffix(type_name r, vec_type point) {   \
    return (point.x >= r.min.x && point.x <= r.max.x &&                              \
            point.y >= r.min.y && point.y <= r.max.y &&                              \
            point.z >= r.min.z && point.z <= r.max.z &&                              \
            point.w >= r.min.w && point.w <= r.max.w);                               \
  }

#define _LM2_IMPL_R4_OVERLAPS(type_name, vec_type, scalar_type, scalar_suffix) \
  LM2_API int lm2_r4_overlaps_##scalar_suffix(type_name a, type_name b) {      \
    return (a.min.x <= b.max.x && a.max.x >= b.min.x &&                        \
            a.min.y <= b.max.y && a.max.y >= b.min.y &&                        \
            a.min.z <= b.max.z && a.max.z >= b.min.z &&                        \
            a.min.w <= b.max.w && a.max.w >= b.min.w);                         \
  }

#define _LM2_IMPL_R4_HYPERVOLUME(type_name, vec_type, scalar_type, scalar_suffix) \
  LM2_API scalar_type lm2_r4_hypervolume_##scalar_suffix(type_name r) {           \
    vec_type size = lm2_v4_sub_##scalar_suffix(r.max, r.min);                     \
    return size.x * size.y * size.z * size.w;                                     \
  }

#define _LM2_IMPL_R4_NORMALIZE(type_name, vec_type, scalar_type, scalar_suffix) \
  LM2_API type_name lm2_r4_normalize_##scalar_suffix(type_name r) {             \
    type_name result = r;                                                       \
    if (result.min.x > result.max.x) {                                          \
      scalar_type temp = result.min.x;                                          \
      result.min.x = result.max.x;                                              \
      result.max.x = temp;                                                      \
    }                                                                           \
    if (result.min.y > result.max.y) {                                          \
      scalar_type temp = result.min.y;                                          \
      result.min.y = result.max.y;                                              \
      result.max.y = temp;                                                      \
    }                                                                           \
    if (result.min.z > result.max.z) {                                          \
      scalar_type temp = result.min.z;                                          \
      result.min.z = result.max.z;                                              \
      result.max.z = temp;                                                      \
    }                                                                           \
    if (result.min.w > result.max.w) {                                          \
      scalar_type temp = result.min.w;                                          \
      result.min.w = result.max.w;                                              \
      result.max.w = temp;                                                      \
    }                                                                           \
    return result;                                                              \
  }

#define _LM2_IMPL_R4_TRANSLATE(type_name, vec_type, scalar_suffix)                   \
  LM2_API type_name lm2_r4_translate_##scalar_suffix(type_name r, vec_type offset) { \
    type_name result;                                                                \
    result.min = lm2_v4_add_##scalar_suffix(r.min, offset);                          \
    result.max = lm2_v4_add_##scalar_suffix(r.max, offset);                          \
    return result;                                                                   \
  }

#define _LM2_IMPL_R4_SCALE(type_name, vec_type, scalar_type, scalar_suffix)         \
  LM2_API type_name lm2_r4_scale_##scalar_suffix(type_name r, scalar_type factor) { \
    vec_type center = lm2_r4_center_##scalar_suffix(r);                             \
    vec_type extents = lm2_r4_extents_##scalar_suffix(r);                           \
    extents = lm2_v4_mul_s_##scalar_suffix(extents, factor);                        \
    return lm2_r4_from_center_extents_##scalar_suffix(center, extents);             \
  }

#define _LM2_IMPL_R4_EXPAND(type_name, vec_type, scalar_type, scalar_suffix)         \
  LM2_API type_name lm2_r4_expand_##scalar_suffix(type_name r, scalar_type amount) { \
    vec_type expand_vec = lm2_v4_splat_##scalar_suffix(amount);                      \
    type_name result;                                                                \
    result.min = lm2_v4_sub_##scalar_suffix(r.min, expand_vec);                      \
    result.max = lm2_v4_add_##scalar_suffix(r.max, expand_vec);                      \
    return result;                                                                   \
  }

#define _LM2_IMPL_R4_ALL_RANGE_FUNCS(type_name, vec_type, scalar_type, scalar_suffix) \
  _LM2_IMPL_R4_UNION(type_name, vec_type, scalar_suffix)                              \
  _LM2_IMPL_R4_INTERSECTION(type_name, vec_type, scalar_suffix)                       \
  _LM2_IMPL_R4_SIZE(type_name, vec_type, scalar_suffix)                               \
  _LM2_IMPL_R4_EXTENTS(type_name, vec_type, scalar_type, scalar_suffix)               \
  _LM2_IMPL_R4_CENTER(type_name, vec_type, scalar_type, scalar_suffix)                \
  _LM2_IMPL_R4_CONTAINS_POINT(type_name, vec_type, scalar_type, scalar_suffix)        \
  _LM2_IMPL_R4_OVERLAPS(type_name, vec_type, scalar_type, scalar_suffix)              \
  _LM2_IMPL_R4_HYPERVOLUME(type_name, vec_type, scalar_type, scalar_suffix)           \
  _LM2_IMPL_R4_NORMALIZE(type_name, vec_type, scalar_type, scalar_suffix)             \
  _LM2_IMPL_R4_TRANSLATE(type_name, vec_type, scalar_suffix)                          \
  _LM2_IMPL_R4_SCALE(type_name, vec_type, scalar_type, scalar_suffix)                 \
  _LM2_IMPL_R4_EXPAND(type_name, vec_type, scalar_type, scalar_suffix)

// =============================================================================
// Integer-specific scalar functions
// =============================================================================

#define _LM2_IMPL_R4_SIGNED_INT_FUNCS(type_name, vec_type, scalar_type, scalar_suffix) \
  _LM2_IMPL_R4_SCALAR_FUNC_1(type_name, scalar_suffix, abs)                            \
  _LM2_IMPL_R4_SCALAR_FUNC_1(type_name, scalar_suffix, sign)                           \
  _LM2_IMPL_R4_SCALAR_FUNC_1(type_name, scalar_suffix, sign0)                          \
  _LM2_IMPL_R4_SCALAR_FUNC_2(type_name, scalar_suffix, min)                            \
  _LM2_IMPL_R4_SCALAR_FUNC_2(type_name, scalar_suffix, min_abs)                        \
  _LM2_IMPL_R4_SCALAR_FUNC_2(type_name, scalar_suffix, max)                            \
  _LM2_IMPL_R4_SCALAR_FUNC_2(type_name, scalar_suffix, max_abs)                        \
  _LM2_IMPL_R4_CLAMP(type_name, scalar_suffix)

#define _LM2_IMPL_R4_UNSIGNED_INT_FUNCS(type_name, vec_type, scalar_type, scalar_suffix) \
  _LM2_IMPL_R4_SCALAR_FUNC_2(type_name, scalar_suffix, min)                              \
  _LM2_IMPL_R4_SCALAR_FUNC_2(type_name, scalar_suffix, max)                              \
  _LM2_IMPL_R4_CLAMP(type_name, scalar_suffix)

// =============================================================================
// Full implementation for all types
// =============================================================================

// Float types (f64, f32)
#define _LM2_IMPL_R4_FLOAT_TYPE(type_name, vec_type, scalar_type, scalar_suffix) \
  _LM2_IMPL_R4_CONSTRUCTORS(type_name, vec_type, scalar_type, scalar_suffix)     \
  _LM2_IMPL_R4_ALL_OPS(type_name, vec_type, scalar_type, scalar_suffix)          \
  _LM2_IMPL_R4_ALL_SCALAR_FUNCS(type_name, scalar_suffix)                        \
  _LM2_IMPL_R4_ALL_RANGE_FUNCS(type_name, vec_type, scalar_type, scalar_suffix)

// Signed integer types
#define _LM2_IMPL_R4_SIGNED_INT_TYPE(type_name, vec_type, scalar_type, scalar_suffix) \
  _LM2_IMPL_R4_CONSTRUCTORS(type_name, vec_type, scalar_type, scalar_suffix)          \
  _LM2_IMPL_R4_ALL_OPS(type_name, vec_type, scalar_type, scalar_suffix)               \
  _LM2_IMPL_R4_SIGNED_INT_FUNCS(type_name, vec_type, scalar_type, scalar_suffix)      \
  _LM2_IMPL_R4_ALL_RANGE_FUNCS(type_name, vec_type, scalar_type, scalar_suffix)

// Unsigned integer types
#define _LM2_IMPL_R4_UNSIGNED_INT_TYPE(type_name, vec_type, scalar_type, scalar_suffix) \
  _LM2_IMPL_R4_CONSTRUCTORS(type_name, vec_type, scalar_type, scalar_suffix)            \
  _LM2_IMPL_R4_BASIC_OPS(type_name, vec_type, scalar_type, scalar_suffix)               \
  _LM2_IMPL_R4_UNSIGNED_INT_FUNCS(type_name, vec_type, scalar_type, scalar_suffix)      \
  _LM2_IMPL_R4_ALL_RANGE_FUNCS(type_name, vec_type, scalar_type, scalar_suffix)

// Instantiate all types
_LM2_IMPL_R4_FLOAT_TYPE(lm2_r4_f64, lm2_v4_f64, double, f64);
_LM2_IMPL_R4_FLOAT_TYPE(lm2_r4_f32, lm2_v4_f32, float, f32);
_LM2_IMPL_R4_SIGNED_INT_TYPE(lm2_r4_i64, lm2_v4_i64, int64_t, i64);
_LM2_IMPL_R4_SIGNED_INT_TYPE(lm2_r4_i32, lm2_v4_i32, int32_t, i32);
_LM2_IMPL_R4_SIGNED_INT_TYPE(lm2_r4_i16, lm2_v4_i16, int16_t, i16);
_LM2_IMPL_R4_SIGNED_INT_TYPE(lm2_r4_i8, lm2_v4_i8, int8_t, i8);
_LM2_IMPL_R4_UNSIGNED_INT_TYPE(lm2_r4_u64, lm2_v4_u64, uint64_t, u64);
_LM2_IMPL_R4_UNSIGNED_INT_TYPE(lm2_r4_u32, lm2_v4_u32, uint32_t, u32);
_LM2_IMPL_R4_UNSIGNED_INT_TYPE(lm2_r4_u16, lm2_v4_u16, uint16_t, u16);
_LM2_IMPL_R4_UNSIGNED_INT_TYPE(lm2_r4_u8, lm2_v4_u8, uint8_t, u8);
