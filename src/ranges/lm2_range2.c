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

#include <lm2/ranges/lm2_range2.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>

// =============================================================================
// Range2 Implementation Helpers
// =============================================================================
// These macros implement all range2 operations for a specific type using the
// libmath2 safe operations and scalar functions.

// Implement constructors
#define _LM2_IMPL_RANGE2_FROM_MIN_MAX(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name lm2_r2_from_min_max_##suffix(vec_type min, vec_type max) {  \
    type_name result;                                                           \
    result.min = min;                                                           \
    result.max = max;                                                           \
    return result;                                                              \
  }

#define _LM2_IMPL_RANGE2_FROM_CENTER_EXTENTS(type_name, vec_type, scalar_type, suffix)       \
  LM2_API type_name lm2_r2_from_center_extents_##suffix(vec_type center, vec_type extents) { \
    type_name result;                                                                        \
    result.min.x = lm2_sub_##suffix(center.x, extents.x);                                    \
    result.min.y = lm2_sub_##suffix(center.y, extents.y);                                    \
    result.max.x = lm2_add_##suffix(center.x, extents.x);                                    \
    result.max.y = lm2_add_##suffix(center.y, extents.y);                                    \
    return result;                                                                           \
  }

#define _LM2_IMPL_RANGE2_FROM_CENTER_SIZE(type_name, vec_type, scalar_type, suffix)    \
  LM2_API type_name lm2_r2_from_center_size_##suffix(vec_type center, vec_type size) { \
    scalar_type half_x = lm2_div_##suffix(size.x, (scalar_type)2);                     \
    scalar_type half_y = lm2_div_##suffix(size.y, (scalar_type)2);                     \
    type_name result;                                                                  \
    result.min.x = lm2_sub_##suffix(center.x, half_x);                                 \
    result.min.y = lm2_sub_##suffix(center.y, half_y);                                 \
    result.max.x = lm2_add_##suffix(center.x, half_x);                                 \
    result.max.y = lm2_add_##suffix(center.y, half_y);                                 \
    return result;                                                                     \
  }

#define _LM2_IMPL_RANGE2_FROM_POSITION_SIZE(type_name, vec_type, scalar_type, suffix)      \
  LM2_API type_name lm2_r2_from_position_size_##suffix(vec_type position, vec_type size) { \
    type_name result;                                                                      \
    result.min = position;                                                                 \
    result.max.x = lm2_add_##suffix(position.x, size.x);                                   \
    result.max.y = lm2_add_##suffix(position.y, size.y);                                   \
    return result;                                                                         \
  }

#define _LM2_IMPL_RANGE2_ZERO(type_name, vec_type, suffix) \
  LM2_API type_name lm2_r2_zero_##suffix(void) {           \
    type_name result;                                      \
    result.min = lm2_v2_zero_##suffix();                   \
    result.max = lm2_v2_zero_##suffix();                   \
    return result;                                         \
  }

// Implement operations
#define _LM2_IMPL_RANGE2_NORMALIZE(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name lm2_r2_normalize_##suffix(type_name r) {                 \
    type_name result;                                                        \
    result.min.x = lm2_min_##suffix(r.min.x, r.max.x);                       \
    result.min.y = lm2_min_##suffix(r.min.y, r.max.y);                       \
    result.max.x = lm2_max_##suffix(r.min.x, r.max.x);                       \
    result.max.y = lm2_max_##suffix(r.min.y, r.max.y);                       \
    return result;                                                           \
  }

#define _LM2_IMPL_RANGE2_TRANSLATE(type_name, vec_type, scalar_type, suffix)  \
  LM2_API type_name lm2_r2_translate_##suffix(type_name r, vec_type offset) { \
    type_name result;                                                         \
    result.min.x = lm2_add_##suffix(r.min.x, offset.x);                       \
    result.min.y = lm2_add_##suffix(r.min.y, offset.y);                       \
    result.max.x = lm2_add_##suffix(r.max.x, offset.x);                       \
    result.max.y = lm2_add_##suffix(r.max.y, offset.y);                       \
    return result;                                                            \
  }

#define _LM2_IMPL_RANGE2_SCALE(type_name, vec_type, scalar_type, suffix)     \
  LM2_API type_name lm2_r2_scale_##suffix(type_name r, scalar_type factor) { \
    vec_type center = lm2_r2_center_##suffix(r);                             \
    vec_type extents = lm2_r2_extents_##suffix(r);                           \
    type_name result;                                                        \
    scalar_type new_ext_x = lm2_mul_##suffix(extents.x, factor);             \
    scalar_type new_ext_y = lm2_mul_##suffix(extents.y, factor);             \
    result.min.x = lm2_sub_##suffix(center.x, new_ext_x);                    \
    result.min.y = lm2_sub_##suffix(center.y, new_ext_y);                    \
    result.max.x = lm2_add_##suffix(center.x, new_ext_x);                    \
    result.max.y = lm2_add_##suffix(center.y, new_ext_y);                    \
    return result;                                                           \
  }

#define _LM2_IMPL_RANGE2_EXPAND(type_name, vec_type, scalar_type, suffix)     \
  LM2_API type_name lm2_r2_expand_##suffix(type_name r, scalar_type amount) { \
    type_name result;                                                         \
    result.min.x = lm2_sub_##suffix(r.min.x, amount);                         \
    result.min.y = lm2_sub_##suffix(r.min.y, amount);                         \
    result.max.x = lm2_add_##suffix(r.max.x, amount);                         \
    result.max.y = lm2_add_##suffix(r.max.y, amount);                         \
    return result;                                                            \
  }

#define _LM2_IMPL_RANGE2_UNION(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name lm2_r2_union_##suffix(type_name a, type_name b) {    \
    type_name result;                                                    \
    result.min.x = lm2_min_##suffix(a.min.x, b.min.x);                   \
    result.min.y = lm2_min_##suffix(a.min.y, b.min.y);                   \
    result.max.x = lm2_max_##suffix(a.max.x, b.max.x);                   \
    result.max.y = lm2_max_##suffix(a.max.y, b.max.y);                   \
    return result;                                                       \
  }

#define _LM2_IMPL_RANGE2_INTERSECTION(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name lm2_r2_intersection_##suffix(type_name a, type_name b) {    \
    type_name result;                                                           \
    result.min.x = lm2_max_##suffix(a.min.x, b.min.x);                          \
    result.min.y = lm2_max_##suffix(a.min.y, b.min.y);                          \
    result.max.x = lm2_min_##suffix(a.max.x, b.max.x);                          \
    result.max.y = lm2_min_##suffix(a.max.y, b.max.y);                          \
    return result;                                                              \
  }

// Implement queries
#define _LM2_IMPL_RANGE2_SIZE(type_name, vec_type, scalar_type, suffix) \
  LM2_API vec_type lm2_r2_size_##suffix(type_name r) {                  \
    vec_type result;                                                    \
    result.x = lm2_sub_##suffix(r.max.x, r.min.x);                      \
    result.y = lm2_sub_##suffix(r.max.y, r.min.y);                      \
    return result;                                                      \
  }

#define _LM2_IMPL_RANGE2_EXTENTS(type_name, vec_type, scalar_type, suffix) \
  LM2_API vec_type lm2_r2_extents_##suffix(type_name r) {                  \
    vec_type size = lm2_r2_size_##suffix(r);                               \
    vec_type result;                                                       \
    result.x = lm2_div_##suffix(size.x, (scalar_type)2);                   \
    result.y = lm2_div_##suffix(size.y, (scalar_type)2);                   \
    return result;                                                         \
  }

#define _LM2_IMPL_RANGE2_CENTER(type_name, vec_type, scalar_type, suffix) \
  LM2_API vec_type lm2_r2_center_##suffix(type_name r) {                  \
    vec_type result;                                                      \
    scalar_type sum_x = lm2_add_##suffix(r.min.x, r.max.x);               \
    scalar_type sum_y = lm2_add_##suffix(r.min.y, r.max.y);               \
    result.x = lm2_div_##suffix(sum_x, (scalar_type)2);                   \
    result.y = lm2_div_##suffix(sum_y, (scalar_type)2);                   \
    return result;                                                        \
  }

#define _LM2_IMPL_RANGE2_CONTAINS_POINT(type_name, vec_type, scalar_type, suffix) \
  LM2_API int lm2_r2_contains_point_##suffix(type_name r, vec_type point) {       \
    return (point.x >= r.min.x && point.x <= r.max.x &&                           \
            point.y >= r.min.y && point.y <= r.max.y);                            \
  }

#define _LM2_IMPL_RANGE2_OVERLAPS(type_name, vec_type, scalar_type, suffix) \
  LM2_API int lm2_r2_overlaps_##suffix(type_name a, type_name b) {          \
    return (a.min.x <= b.max.x && a.max.x >= b.min.x &&                     \
            a.min.y <= b.max.y && a.max.y >= b.min.y);                      \
  }

#define _LM2_IMPL_RANGE2_AREA(type_name, vec_type, scalar_type, suffix) \
  LM2_API scalar_type lm2_r2_area_##suffix(type_name r) {               \
    vec_type size = lm2_r2_size_##suffix(r);                            \
    return lm2_mul_##suffix(size.x, size.y);                            \
  }

// =============================================================================
// Range2 Arithmetic Operation Implementation Macros
// =============================================================================
// Component-wise arithmetic operations on ranges.

// Range + Range (component-wise)
#define _LM2_IMPL_RANGE2_ADD_RANGE(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name lm2_r2_add_##suffix(type_name a, type_name b) {          \
    type_name result;                                                        \
    result.min.x = lm2_add_##suffix(a.min.x, b.min.x);                       \
    result.min.y = lm2_add_##suffix(a.min.y, b.min.y);                       \
    result.max.x = lm2_add_##suffix(a.max.x, b.max.x);                       \
    result.max.y = lm2_add_##suffix(a.max.y, b.max.y);                       \
    return result;                                                           \
  }

// Range + Scalar (applies to all components)
#define _LM2_IMPL_RANGE2_ADD_SCALAR(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name lm2_r2_add_s_##suffix(type_name r, scalar_type s) {       \
    type_name result;                                                         \
    result.min.x = lm2_add_##suffix(r.min.x, s);                              \
    result.min.y = lm2_add_##suffix(r.min.y, s);                              \
    result.max.x = lm2_add_##suffix(r.max.x, s);                              \
    result.max.y = lm2_add_##suffix(r.max.y, s);                              \
    return result;                                                            \
  }

// Range + Vector (applies to both min and max)
#define _LM2_IMPL_RANGE2_ADD_VECTOR(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name lm2_r2_add_v_##suffix(type_name r, vec_type v) {          \
    type_name result;                                                         \
    result.min.x = lm2_add_##suffix(r.min.x, v.x);                            \
    result.min.y = lm2_add_##suffix(r.min.y, v.y);                            \
    result.max.x = lm2_add_##suffix(r.max.x, v.x);                            \
    result.max.y = lm2_add_##suffix(r.max.y, v.y);                            \
    return result;                                                            \
  }

// Range - Range
#define _LM2_IMPL_RANGE2_SUB_RANGE(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name lm2_r2_sub_##suffix(type_name a, type_name b) {          \
    type_name result;                                                        \
    result.min.x = lm2_sub_##suffix(a.min.x, b.min.x);                       \
    result.min.y = lm2_sub_##suffix(a.min.y, b.min.y);                       \
    result.max.x = lm2_sub_##suffix(a.max.x, b.max.x);                       \
    result.max.y = lm2_sub_##suffix(a.max.y, b.max.y);                       \
    return result;                                                           \
  }

// Range - Scalar
#define _LM2_IMPL_RANGE2_SUB_SCALAR(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name lm2_r2_sub_s_##suffix(type_name r, scalar_type s) {       \
    type_name result;                                                         \
    result.min.x = lm2_sub_##suffix(r.min.x, s);                              \
    result.min.y = lm2_sub_##suffix(r.min.y, s);                              \
    result.max.x = lm2_sub_##suffix(r.max.x, s);                              \
    result.max.y = lm2_sub_##suffix(r.max.y, s);                              \
    return result;                                                            \
  }

// Range - Vector
#define _LM2_IMPL_RANGE2_SUB_VECTOR(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name lm2_r2_sub_v_##suffix(type_name r, vec_type v) {          \
    type_name result;                                                         \
    result.min.x = lm2_sub_##suffix(r.min.x, v.x);                            \
    result.min.y = lm2_sub_##suffix(r.min.y, v.y);                            \
    result.max.x = lm2_sub_##suffix(r.max.x, v.x);                            \
    result.max.y = lm2_sub_##suffix(r.max.y, v.y);                            \
    return result;                                                            \
  }

// Range * Range
#define _LM2_IMPL_RANGE2_MUL_RANGE(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name lm2_r2_mul_##suffix(type_name a, type_name b) {          \
    type_name result;                                                        \
    result.min.x = lm2_mul_##suffix(a.min.x, b.min.x);                       \
    result.min.y = lm2_mul_##suffix(a.min.y, b.min.y);                       \
    result.max.x = lm2_mul_##suffix(a.max.x, b.max.x);                       \
    result.max.y = lm2_mul_##suffix(a.max.y, b.max.y);                       \
    return result;                                                           \
  }

// Range * Scalar
#define _LM2_IMPL_RANGE2_MUL_SCALAR(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name lm2_r2_mul_s_##suffix(type_name r, scalar_type s) {       \
    type_name result;                                                         \
    result.min.x = lm2_mul_##suffix(r.min.x, s);                              \
    result.min.y = lm2_mul_##suffix(r.min.y, s);                              \
    result.max.x = lm2_mul_##suffix(r.max.x, s);                              \
    result.max.y = lm2_mul_##suffix(r.max.y, s);                              \
    return result;                                                            \
  }

// Range * Vector
#define _LM2_IMPL_RANGE2_MUL_VECTOR(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name lm2_r2_mul_v_##suffix(type_name r, vec_type v) {          \
    type_name result;                                                         \
    result.min.x = lm2_mul_##suffix(r.min.x, v.x);                            \
    result.min.y = lm2_mul_##suffix(r.min.y, v.y);                            \
    result.max.x = lm2_mul_##suffix(r.max.x, v.x);                            \
    result.max.y = lm2_mul_##suffix(r.max.y, v.y);                            \
    return result;                                                            \
  }

// Range / Range
#define _LM2_IMPL_RANGE2_DIV_RANGE(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name lm2_r2_div_##suffix(type_name a, type_name b) {          \
    type_name result;                                                        \
    result.min.x = lm2_div_##suffix(a.min.x, b.min.x);                       \
    result.min.y = lm2_div_##suffix(a.min.y, b.min.y);                       \
    result.max.x = lm2_div_##suffix(a.max.x, b.max.x);                       \
    result.max.y = lm2_div_##suffix(a.max.y, b.max.y);                       \
    return result;                                                           \
  }

// Range / Scalar
#define _LM2_IMPL_RANGE2_DIV_SCALAR(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name lm2_r2_div_s_##suffix(type_name r, scalar_type s) {       \
    type_name result;                                                         \
    result.min.x = lm2_div_##suffix(r.min.x, s);                              \
    result.min.y = lm2_div_##suffix(r.min.y, s);                              \
    result.max.x = lm2_div_##suffix(r.max.x, s);                              \
    result.max.y = lm2_div_##suffix(r.max.y, s);                              \
    return result;                                                            \
  }

// Range / Vector
#define _LM2_IMPL_RANGE2_DIV_VECTOR(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name lm2_r2_div_v_##suffix(type_name r, vec_type v) {          \
    type_name result;                                                         \
    result.min.x = lm2_div_##suffix(r.min.x, v.x);                            \
    result.min.y = lm2_div_##suffix(r.min.y, v.y);                            \
    result.max.x = lm2_div_##suffix(r.max.x, v.x);                            \
    result.max.y = lm2_div_##suffix(r.max.y, v.y);                            \
    return result;                                                            \
  }

// Range % Range
#define _LM2_IMPL_RANGE2_MOD_RANGE(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name lm2_r2_mod_##suffix(type_name a, type_name b) {          \
    type_name result;                                                        \
    result.min.x = lm2_mod_##suffix(a.min.x, b.min.x);                       \
    result.min.y = lm2_mod_##suffix(a.min.y, b.min.y);                       \
    result.max.x = lm2_mod_##suffix(a.max.x, b.max.x);                       \
    result.max.y = lm2_mod_##suffix(a.max.y, b.max.y);                       \
    return result;                                                           \
  }

// Range % Scalar
#define _LM2_IMPL_RANGE2_MOD_SCALAR(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name lm2_r2_mod_s_##suffix(type_name r, scalar_type s) {       \
    type_name result;                                                         \
    result.min.x = lm2_mod_##suffix(r.min.x, s);                              \
    result.min.y = lm2_mod_##suffix(r.min.y, s);                              \
    result.max.x = lm2_mod_##suffix(r.max.x, s);                              \
    result.max.y = lm2_mod_##suffix(r.max.y, s);                              \
    return result;                                                            \
  }

// Range % Vector
#define _LM2_IMPL_RANGE2_MOD_VECTOR(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name lm2_r2_mod_v_##suffix(type_name r, vec_type v) {          \
    type_name result;                                                         \
    result.min.x = lm2_mod_##suffix(r.min.x, v.x);                            \
    result.min.y = lm2_mod_##suffix(r.min.y, v.y);                            \
    result.max.x = lm2_mod_##suffix(r.max.x, v.x);                            \
    result.max.y = lm2_mod_##suffix(r.max.y, v.y);                            \
    return result;                                                            \
  }

// Convenience macro to implement all arithmetic operations
#define _LM2_IMPL_RANGE2_ARITHMETIC(type_name, vec_type, scalar_type, suffix) \
  _LM2_IMPL_RANGE2_ADD_RANGE(type_name, vec_type, scalar_type, suffix)        \
  _LM2_IMPL_RANGE2_ADD_SCALAR(type_name, vec_type, scalar_type, suffix)       \
  _LM2_IMPL_RANGE2_ADD_VECTOR(type_name, vec_type, scalar_type, suffix)       \
  _LM2_IMPL_RANGE2_SUB_RANGE(type_name, vec_type, scalar_type, suffix)        \
  _LM2_IMPL_RANGE2_SUB_SCALAR(type_name, vec_type, scalar_type, suffix)       \
  _LM2_IMPL_RANGE2_SUB_VECTOR(type_name, vec_type, scalar_type, suffix)       \
  _LM2_IMPL_RANGE2_MUL_RANGE(type_name, vec_type, scalar_type, suffix)        \
  _LM2_IMPL_RANGE2_MUL_SCALAR(type_name, vec_type, scalar_type, suffix)       \
  _LM2_IMPL_RANGE2_MUL_VECTOR(type_name, vec_type, scalar_type, suffix)       \
  _LM2_IMPL_RANGE2_DIV_RANGE(type_name, vec_type, scalar_type, suffix)        \
  _LM2_IMPL_RANGE2_DIV_SCALAR(type_name, vec_type, scalar_type, suffix)       \
  _LM2_IMPL_RANGE2_DIV_VECTOR(type_name, vec_type, scalar_type, suffix)       \
  _LM2_IMPL_RANGE2_MOD_RANGE(type_name, vec_type, scalar_type, suffix)        \
  _LM2_IMPL_RANGE2_MOD_SCALAR(type_name, vec_type, scalar_type, suffix)       \
  _LM2_IMPL_RANGE2_MOD_VECTOR(type_name, vec_type, scalar_type, suffix)

// =============================================================================
// Range2 Scalar Function Implementation Macros
// =============================================================================
// These macros forward scalar functions to ranges by applying them
// component-wise to both min and max vectors.

// Unary scalar function (e.g., floor, ceil, abs)
#define _LM2_IMPL_RANGE2_SCALAR_FUNC_1(type_name, vec_type, suffix, op_name, vec_func_name) \
  LM2_API type_name lm2_r2_##op_name##_##suffix(type_name a) {                              \
    type_name result;                                                                       \
    result.min = lm2_v2_##op_name##_##suffix(a.min);                                        \
    result.max = lm2_v2_##op_name##_##suffix(a.max);                                        \
    return result;                                                                          \
  }

// Binary scalar function (e.g., min, max, pow, mod)
#define _LM2_IMPL_RANGE2_SCALAR_FUNC_2(type_name, vec_type, suffix, op_name, vec_func_name) \
  LM2_API type_name lm2_r2_##op_name##_##suffix(type_name a, type_name b) {                 \
    type_name result;                                                                       \
    result.min = lm2_v2_##op_name##_##suffix(a.min, b.min);                                 \
    result.max = lm2_v2_##op_name##_##suffix(a.max, b.max);                                 \
    return result;                                                                          \
  }

// Ternary scalar function (e.g., clamp, lerp, smoothstep)
#define _LM2_IMPL_RANGE2_SCALAR_FUNC_3(type_name, vec_type, suffix, op_name, vec_func_name) \
  LM2_API type_name lm2_r2_##op_name##_##suffix(type_name a, type_name b, type_name c) {    \
    type_name result;                                                                       \
    result.min = lm2_v2_##op_name##_##suffix(a.min, b.min, c.min);                          \
    result.max = lm2_v2_##op_name##_##suffix(a.max, b.max, c.max);                          \
    return result;                                                                          \
  }

// Master macro to implement all functions for a range2 type
#define _LM2_IMPL_RANGE2_ALL(type_name, vec_type, scalar_type, suffix)                            \
  _LM2_IMPL_RANGE2_FROM_MIN_MAX(type_name, vec_type, scalar_type, suffix)                         \
  _LM2_IMPL_RANGE2_FROM_CENTER_EXTENTS(type_name, vec_type, scalar_type, suffix)                  \
  _LM2_IMPL_RANGE2_FROM_CENTER_SIZE(type_name, vec_type, scalar_type, suffix)                     \
  _LM2_IMPL_RANGE2_FROM_POSITION_SIZE(type_name, vec_type, scalar_type, suffix)                   \
  _LM2_IMPL_RANGE2_ZERO(type_name, vec_type, suffix)                                              \
  _LM2_IMPL_RANGE2_NORMALIZE(type_name, vec_type, scalar_type, suffix)                            \
  _LM2_IMPL_RANGE2_TRANSLATE(type_name, vec_type, scalar_type, suffix)                            \
  _LM2_IMPL_RANGE2_SCALE(type_name, vec_type, scalar_type, suffix)                                \
  _LM2_IMPL_RANGE2_EXPAND(type_name, vec_type, scalar_type, suffix)                               \
  _LM2_IMPL_RANGE2_ARITHMETIC(type_name, vec_type, scalar_type, suffix)                           \
  _LM2_IMPL_RANGE2_UNION(type_name, vec_type, scalar_type, suffix)                                \
  _LM2_IMPL_RANGE2_INTERSECTION(type_name, vec_type, scalar_type, suffix)                         \
  _LM2_IMPL_RANGE2_SIZE(type_name, vec_type, scalar_type, suffix)                                 \
  _LM2_IMPL_RANGE2_EXTENTS(type_name, vec_type, scalar_type, suffix)                              \
  _LM2_IMPL_RANGE2_CENTER(type_name, vec_type, scalar_type, suffix)                               \
  _LM2_IMPL_RANGE2_CONTAINS_POINT(type_name, vec_type, scalar_type, suffix)                       \
  _LM2_IMPL_RANGE2_OVERLAPS(type_name, vec_type, scalar_type, suffix)                             \
  _LM2_IMPL_RANGE2_AREA(type_name, vec_type, scalar_type, suffix)                                 \
  _LM2_IMPL_RANGE2_SCALAR_FUNC_1(type_name, vec_type, suffix, floor, lm2_floor)                   \
  _LM2_IMPL_RANGE2_SCALAR_FUNC_1(type_name, vec_type, suffix, ceil, lm2_ceil)                     \
  _LM2_IMPL_RANGE2_SCALAR_FUNC_1(type_name, vec_type, suffix, round, lm2_round)                   \
  _LM2_IMPL_RANGE2_SCALAR_FUNC_1(type_name, vec_type, suffix, trunc, lm2_trunc)                   \
  _LM2_IMPL_RANGE2_SCALAR_FUNC_1(type_name, vec_type, suffix, abs, lm2_abs)                       \
  _LM2_IMPL_RANGE2_SCALAR_FUNC_2(type_name, vec_type, suffix, floor_multiple, lm2_floor_multiple) \
  _LM2_IMPL_RANGE2_SCALAR_FUNC_2(type_name, vec_type, suffix, ceil_multiple, lm2_ceil_multiple)   \
  _LM2_IMPL_RANGE2_SCALAR_FUNC_2(type_name, vec_type, suffix, round_multiple, lm2_round_multiple) \
  _LM2_IMPL_RANGE2_SCALAR_FUNC_2(type_name, vec_type, suffix, trunc_multiple, lm2_trunc_multiple) \
  _LM2_IMPL_RANGE2_SCALAR_FUNC_2(type_name, vec_type, suffix, min, lm2_min)                       \
  _LM2_IMPL_RANGE2_SCALAR_FUNC_2(type_name, vec_type, suffix, max, lm2_max)                       \
  _LM2_IMPL_RANGE2_SCALAR_FUNC_3(type_name, vec_type, suffix, clamp, lm2_clamp)                   \
  _LM2_IMPL_RANGE2_SCALAR_FUNC_3(type_name, vec_type, suffix, lerp, lm2_lerp)

// =============================================================================
// Range2 Implementations for All 10 Numeric Types
// =============================================================================

_LM2_IMPL_RANGE2_ALL(lm2_r2_f64, lm2_v2_f64, double, f64)
_LM2_IMPL_RANGE2_ALL(lm2_r2_f32, lm2_v2_f32, float, f32)
_LM2_IMPL_RANGE2_ALL(lm2_r2_i64, lm2_v2_i64, int64_t, i64)
_LM2_IMPL_RANGE2_ALL(lm2_r2_i32, lm2_v2_i32, int32_t, i32)
_LM2_IMPL_RANGE2_ALL(lm2_r2_i16, lm2_v2_i16, int16_t, i16)
_LM2_IMPL_RANGE2_ALL(lm2_r2_i8, lm2_v2_i8, int8_t, i8)
_LM2_IMPL_RANGE2_ALL(lm2_r2_u64, lm2_v2_u64, uint64_t, u64)
_LM2_IMPL_RANGE2_ALL(lm2_r2_u32, lm2_v2_u32, uint32_t, u32)
_LM2_IMPL_RANGE2_ALL(lm2_r2_u16, lm2_v2_u16, uint16_t, u16)
_LM2_IMPL_RANGE2_ALL(lm2_r2_u8, lm2_v2_u8, uint8_t, u8)
