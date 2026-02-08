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

#include <lm2/ranges/lm2_range3.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>

// =============================================================================
// Range3 Implementation Helpers
// =============================================================================

// Implement constructors
#define _LM2_IMPL_RANGE3_FROM_MIN_MAX(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_from_min_max(vec_type min, vec_type max) {      \
    type_name result;                                                           \
    result.min = min;                                                           \
    result.max = max;                                                           \
    return result;                                                              \
  }

#define _LM2_IMPL_RANGE3_FROM_CENTER_EXTENTS(type_name, vec_type, scalar_type, suffix)   \
  LM2_API type_name type_name##_from_center_extents(vec_type center, vec_type extents) { \
    type_name result;                                                                    \
    result.min.x = lm2_sub_##suffix(center.x, extents.x);                                \
    result.min.y = lm2_sub_##suffix(center.y, extents.y);                                \
    result.min.z = lm2_sub_##suffix(center.z, extents.z);                                \
    result.max.x = lm2_add_##suffix(center.x, extents.x);                                \
    result.max.y = lm2_add_##suffix(center.y, extents.y);                                \
    result.max.z = lm2_add_##suffix(center.z, extents.z);                                \
    return result;                                                                       \
  }

#define _LM2_IMPL_RANGE3_FROM_CENTER_SIZE(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_from_center_size(vec_type center, vec_type size) {  \
    scalar_type half_x = lm2_div_##suffix(size.x, (scalar_type)2);                  \
    scalar_type half_y = lm2_div_##suffix(size.y, (scalar_type)2);                  \
    scalar_type half_z = lm2_div_##suffix(size.z, (scalar_type)2);                  \
    type_name result;                                                               \
    result.min.x = lm2_sub_##suffix(center.x, half_x);                              \
    result.min.y = lm2_sub_##suffix(center.y, half_y);                              \
    result.min.z = lm2_sub_##suffix(center.z, half_z);                              \
    result.max.x = lm2_add_##suffix(center.x, half_x);                              \
    result.max.y = lm2_add_##suffix(center.y, half_y);                              \
    result.max.z = lm2_add_##suffix(center.z, half_z);                              \
    return result;                                                                  \
  }

#define _LM2_IMPL_RANGE3_FROM_POSITION_SIZE(type_name, vec_type, scalar_type, suffix)  \
  LM2_API type_name type_name##_from_position_size(vec_type position, vec_type size) { \
    type_name result;                                                                  \
    result.min = position;                                                             \
    result.max.x = lm2_add_##suffix(position.x, size.x);                               \
    result.max.y = lm2_add_##suffix(position.y, size.y);                               \
    result.max.z = lm2_add_##suffix(position.z, size.z);                               \
    return result;                                                                     \
  }

#define _LM2_IMPL_RANGE3_ZERO(type_name, vec_type) \
  LM2_API type_name type_name##_zero(void) {       \
    type_name result;                              \
    result.min = vec_type##_zero();                \
    result.max = vec_type##_zero();                \
    return result;                                 \
  }

// Implement operations
#define _LM2_IMPL_RANGE3_NORMALIZE(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_normalize(type_name r) {                     \
    type_name result;                                                        \
    result.min.x = lm2_min_##suffix(r.min.x, r.max.x);                       \
    result.min.y = lm2_min_##suffix(r.min.y, r.max.y);                       \
    result.min.z = lm2_min_##suffix(r.min.z, r.max.z);                       \
    result.max.x = lm2_max_##suffix(r.min.x, r.max.x);                       \
    result.max.y = lm2_max_##suffix(r.min.y, r.max.y);                       \
    result.max.z = lm2_max_##suffix(r.min.z, r.max.z);                       \
    return result;                                                           \
  }

#define _LM2_IMPL_RANGE3_TRANSLATE(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_translate(type_name r, vec_type offset) {    \
    type_name result;                                                        \
    result.min.x = lm2_add_##suffix(r.min.x, offset.x);                      \
    result.min.y = lm2_add_##suffix(r.min.y, offset.y);                      \
    result.min.z = lm2_add_##suffix(r.min.z, offset.z);                      \
    result.max.x = lm2_add_##suffix(r.max.x, offset.x);                      \
    result.max.y = lm2_add_##suffix(r.max.y, offset.y);                      \
    result.max.z = lm2_add_##suffix(r.max.z, offset.z);                      \
    return result;                                                           \
  }

#define _LM2_IMPL_RANGE3_SCALE(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_scale(type_name r, scalar_type factor) { \
    vec_type center = type_name##_center(r);                             \
    vec_type extents = type_name##_extents(r);                           \
    type_name result;                                                    \
    scalar_type new_ext_x = lm2_mul_##suffix(extents.x, factor);         \
    scalar_type new_ext_y = lm2_mul_##suffix(extents.y, factor);         \
    scalar_type new_ext_z = lm2_mul_##suffix(extents.z, factor);         \
    result.min.x = lm2_sub_##suffix(center.x, new_ext_x);                \
    result.min.y = lm2_sub_##suffix(center.y, new_ext_y);                \
    result.min.z = lm2_sub_##suffix(center.z, new_ext_z);                \
    result.max.x = lm2_add_##suffix(center.x, new_ext_x);                \
    result.max.y = lm2_add_##suffix(center.y, new_ext_y);                \
    result.max.z = lm2_add_##suffix(center.z, new_ext_z);                \
    return result;                                                       \
  }

#define _LM2_IMPL_RANGE3_EXPAND(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_expand(type_name r, scalar_type amount) { \
    type_name result;                                                     \
    result.min.x = lm2_sub_##suffix(r.min.x, amount);                     \
    result.min.y = lm2_sub_##suffix(r.min.y, amount);                     \
    result.min.z = lm2_sub_##suffix(r.min.z, amount);                     \
    result.max.x = lm2_add_##suffix(r.max.x, amount);                     \
    result.max.y = lm2_add_##suffix(r.max.y, amount);                     \
    result.max.z = lm2_add_##suffix(r.max.z, amount);                     \
    return result;                                                        \
  }

#define _LM2_IMPL_RANGE3_UNION(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_union(type_name a, type_name b) {        \
    type_name result;                                                    \
    result.min.x = lm2_min_##suffix(a.min.x, b.min.x);                   \
    result.min.y = lm2_min_##suffix(a.min.y, b.min.y);                   \
    result.min.z = lm2_min_##suffix(a.min.z, b.min.z);                   \
    result.max.x = lm2_max_##suffix(a.max.x, b.max.x);                   \
    result.max.y = lm2_max_##suffix(a.max.y, b.max.y);                   \
    result.max.z = lm2_max_##suffix(a.max.z, b.max.z);                   \
    return result;                                                       \
  }

#define _LM2_IMPL_RANGE3_INTERSECTION(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_intersection(type_name a, type_name b) {        \
    type_name result;                                                           \
    result.min.x = lm2_max_##suffix(a.min.x, b.min.x);                          \
    result.min.y = lm2_max_##suffix(a.min.y, b.min.y);                          \
    result.min.z = lm2_max_##suffix(a.min.z, b.min.z);                          \
    result.max.x = lm2_min_##suffix(a.max.x, b.max.x);                          \
    result.max.y = lm2_min_##suffix(a.max.y, b.max.y);                          \
    result.max.z = lm2_min_##suffix(a.max.z, b.max.z);                          \
    return result;                                                              \
  }

// Implement queries
#define _LM2_IMPL_RANGE3_SIZE(type_name, vec_type, scalar_type, suffix) \
  LM2_API vec_type type_name##_size(type_name r) {                      \
    vec_type result;                                                    \
    result.x = lm2_sub_##suffix(r.max.x, r.min.x);                      \
    result.y = lm2_sub_##suffix(r.max.y, r.min.y);                      \
    result.z = lm2_sub_##suffix(r.max.z, r.min.z);                      \
    return result;                                                      \
  }

#define _LM2_IMPL_RANGE3_EXTENTS(type_name, vec_type, scalar_type, suffix) \
  LM2_API vec_type type_name##_extents(type_name r) {                      \
    vec_type size = type_name##_size(r);                                   \
    vec_type result;                                                       \
    result.x = lm2_div_##suffix(size.x, (scalar_type)2);                   \
    result.y = lm2_div_##suffix(size.y, (scalar_type)2);                   \
    result.z = lm2_div_##suffix(size.z, (scalar_type)2);                   \
    return result;                                                         \
  }

#define _LM2_IMPL_RANGE3_CENTER(type_name, vec_type, scalar_type, suffix) \
  LM2_API vec_type type_name##_center(type_name r) {                      \
    vec_type result;                                                      \
    scalar_type sum_x = lm2_add_##suffix(r.min.x, r.max.x);               \
    scalar_type sum_y = lm2_add_##suffix(r.min.y, r.max.y);               \
    scalar_type sum_z = lm2_add_##suffix(r.min.z, r.max.z);               \
    result.x = lm2_div_##suffix(sum_x, (scalar_type)2);                   \
    result.y = lm2_div_##suffix(sum_y, (scalar_type)2);                   \
    result.z = lm2_div_##suffix(sum_z, (scalar_type)2);                   \
    return result;                                                        \
  }

#define _LM2_IMPL_RANGE3_CONTAINS_POINT(type_name, vec_type, scalar_type, suffix) \
  LM2_API int type_name##_contains_point(type_name r, vec_type point) {           \
    return (point.x >= r.min.x && point.x <= r.max.x &&                           \
            point.y >= r.min.y && point.y <= r.max.y &&                           \
            point.z >= r.min.z && point.z <= r.max.z);                            \
  }

#define _LM2_IMPL_RANGE3_OVERLAPS(type_name, vec_type, scalar_type, suffix) \
  LM2_API int type_name##_overlaps(type_name a, type_name b) {              \
    return (a.min.x <= b.max.x && a.max.x >= b.min.x &&                     \
            a.min.y <= b.max.y && a.max.y >= b.min.y &&                     \
            a.min.z <= b.max.z && a.max.z >= b.min.z);                      \
  }

#define _LM2_IMPL_RANGE3_VOLUME(type_name, vec_type, scalar_type, suffix) \
  LM2_API scalar_type type_name##_volume(type_name r) {                   \
    vec_type size = type_name##_size(r);                                  \
    scalar_type area = lm2_mul_##suffix(size.x, size.y);                  \
    return lm2_mul_##suffix(area, size.z);                                \
  }

// =============================================================================
// Range3 Arithmetic Operation Implementation Macros
// =============================================================================
// Component-wise arithmetic operations on ranges.

// Range + Range (component-wise)
#define _LM2_IMPL_RANGE3_ADD_RANGE(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_add(type_name a, type_name b) {              \
    type_name result;                                                        \
    result.min.x = lm2_add_##suffix(a.min.x, b.min.x);                       \
    result.min.y = lm2_add_##suffix(a.min.y, b.min.y);                       \
    result.min.z = lm2_add_##suffix(a.min.z, b.min.z);                       \
    result.max.x = lm2_add_##suffix(a.max.x, b.max.x);                       \
    result.max.y = lm2_add_##suffix(a.max.y, b.max.y);                       \
    result.max.z = lm2_add_##suffix(a.max.z, b.max.z);                       \
    return result;                                                           \
  }

// Range + Scalar (applies to all components)
#define _LM2_IMPL_RANGE3_ADD_SCALAR(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_add_scalar(type_name r, scalar_type s) {      \
    type_name result;                                                         \
    result.min.x = lm2_add_##suffix(r.min.x, s);                              \
    result.min.y = lm2_add_##suffix(r.min.y, s);                              \
    result.min.z = lm2_add_##suffix(r.min.z, s);                              \
    result.max.x = lm2_add_##suffix(r.max.x, s);                              \
    result.max.y = lm2_add_##suffix(r.max.y, s);                              \
    result.max.z = lm2_add_##suffix(r.max.z, s);                              \
    return result;                                                            \
  }

// Range + Vector (applies to both min and max)
#define _LM2_IMPL_RANGE3_ADD_VECTOR(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_add_vec(type_name r, vec_type v) {            \
    type_name result;                                                         \
    result.min.x = lm2_add_##suffix(r.min.x, v.x);                            \
    result.min.y = lm2_add_##suffix(r.min.y, v.y);                            \
    result.min.z = lm2_add_##suffix(r.min.z, v.z);                            \
    result.max.x = lm2_add_##suffix(r.max.x, v.x);                            \
    result.max.y = lm2_add_##suffix(r.max.y, v.y);                            \
    result.max.z = lm2_add_##suffix(r.max.z, v.z);                            \
    return result;                                                            \
  }

// Range - Range
#define _LM2_IMPL_RANGE3_SUB_RANGE(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_sub(type_name a, type_name b) {              \
    type_name result;                                                        \
    result.min.x = lm2_sub_##suffix(a.min.x, b.min.x);                       \
    result.min.y = lm2_sub_##suffix(a.min.y, b.min.y);                       \
    result.min.z = lm2_sub_##suffix(a.min.z, b.min.z);                       \
    result.max.x = lm2_sub_##suffix(a.max.x, b.max.x);                       \
    result.max.y = lm2_sub_##suffix(a.max.y, b.max.y);                       \
    result.max.z = lm2_sub_##suffix(a.max.z, b.max.z);                       \
    return result;                                                           \
  }

// Range - Scalar
#define _LM2_IMPL_RANGE3_SUB_SCALAR(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_sub_scalar(type_name r, scalar_type s) {      \
    type_name result;                                                         \
    result.min.x = lm2_sub_##suffix(r.min.x, s);                              \
    result.min.y = lm2_sub_##suffix(r.min.y, s);                              \
    result.min.z = lm2_sub_##suffix(r.min.z, s);                              \
    result.max.x = lm2_sub_##suffix(r.max.x, s);                              \
    result.max.y = lm2_sub_##suffix(r.max.y, s);                              \
    result.max.z = lm2_sub_##suffix(r.max.z, s);                              \
    return result;                                                            \
  }

// Range - Vector
#define _LM2_IMPL_RANGE3_SUB_VECTOR(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_sub_vec(type_name r, vec_type v) {            \
    type_name result;                                                         \
    result.min.x = lm2_sub_##suffix(r.min.x, v.x);                            \
    result.min.y = lm2_sub_##suffix(r.min.y, v.y);                            \
    result.min.z = lm2_sub_##suffix(r.min.z, v.z);                            \
    result.max.x = lm2_sub_##suffix(r.max.x, v.x);                            \
    result.max.y = lm2_sub_##suffix(r.max.y, v.y);                            \
    result.max.z = lm2_sub_##suffix(r.max.z, v.z);                            \
    return result;                                                            \
  }

// Range * Range
#define _LM2_IMPL_RANGE3_MUL_RANGE(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_mul(type_name a, type_name b) {              \
    type_name result;                                                        \
    result.min.x = lm2_mul_##suffix(a.min.x, b.min.x);                       \
    result.min.y = lm2_mul_##suffix(a.min.y, b.min.y);                       \
    result.min.z = lm2_mul_##suffix(a.min.z, b.min.z);                       \
    result.max.x = lm2_mul_##suffix(a.max.x, b.max.x);                       \
    result.max.y = lm2_mul_##suffix(a.max.y, b.max.y);                       \
    result.max.z = lm2_mul_##suffix(a.max.z, b.max.z);                       \
    return result;                                                           \
  }

// Range * Scalar
#define _LM2_IMPL_RANGE3_MUL_SCALAR(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_mul_scalar(type_name r, scalar_type s) {      \
    type_name result;                                                         \
    result.min.x = lm2_mul_##suffix(r.min.x, s);                              \
    result.min.y = lm2_mul_##suffix(r.min.y, s);                              \
    result.min.z = lm2_mul_##suffix(r.min.z, s);                              \
    result.max.x = lm2_mul_##suffix(r.max.x, s);                              \
    result.max.y = lm2_mul_##suffix(r.max.y, s);                              \
    result.max.z = lm2_mul_##suffix(r.max.z, s);                              \
    return result;                                                            \
  }

// Range * Vector
#define _LM2_IMPL_RANGE3_MUL_VECTOR(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_mul_vec(type_name r, vec_type v) {            \
    type_name result;                                                         \
    result.min.x = lm2_mul_##suffix(r.min.x, v.x);                            \
    result.min.y = lm2_mul_##suffix(r.min.y, v.y);                            \
    result.min.z = lm2_mul_##suffix(r.min.z, v.z);                            \
    result.max.x = lm2_mul_##suffix(r.max.x, v.x);                            \
    result.max.y = lm2_mul_##suffix(r.max.y, v.y);                            \
    result.max.z = lm2_mul_##suffix(r.max.z, v.z);                            \
    return result;                                                            \
  }

// Range / Range
#define _LM2_IMPL_RANGE3_DIV_RANGE(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_div(type_name a, type_name b) {              \
    type_name result;                                                        \
    result.min.x = lm2_div_##suffix(a.min.x, b.min.x);                       \
    result.min.y = lm2_div_##suffix(a.min.y, b.min.y);                       \
    result.min.z = lm2_div_##suffix(a.min.z, b.min.z);                       \
    result.max.x = lm2_div_##suffix(a.max.x, b.max.x);                       \
    result.max.y = lm2_div_##suffix(a.max.y, b.max.y);                       \
    result.max.z = lm2_div_##suffix(a.max.z, b.max.z);                       \
    return result;                                                           \
  }

// Range / Scalar
#define _LM2_IMPL_RANGE3_DIV_SCALAR(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_div_scalar(type_name r, scalar_type s) {      \
    type_name result;                                                         \
    result.min.x = lm2_div_##suffix(r.min.x, s);                              \
    result.min.y = lm2_div_##suffix(r.min.y, s);                              \
    result.min.z = lm2_div_##suffix(r.min.z, s);                              \
    result.max.x = lm2_div_##suffix(r.max.x, s);                              \
    result.max.y = lm2_div_##suffix(r.max.y, s);                              \
    result.max.z = lm2_div_##suffix(r.max.z, s);                              \
    return result;                                                            \
  }

// Range / Vector
#define _LM2_IMPL_RANGE3_DIV_VECTOR(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_div_vec(type_name r, vec_type v) {            \
    type_name result;                                                         \
    result.min.x = lm2_div_##suffix(r.min.x, v.x);                            \
    result.min.y = lm2_div_##suffix(r.min.y, v.y);                            \
    result.min.z = lm2_div_##suffix(r.min.z, v.z);                            \
    result.max.x = lm2_div_##suffix(r.max.x, v.x);                            \
    result.max.y = lm2_div_##suffix(r.max.y, v.y);                            \
    result.max.z = lm2_div_##suffix(r.max.z, v.z);                            \
    return result;                                                            \
  }

// Range % Range
#define _LM2_IMPL_RANGE3_MOD_RANGE(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_mod(type_name a, type_name b) {              \
    type_name result;                                                        \
    result.min.x = lm2_mod_##suffix(a.min.x, b.min.x);                       \
    result.min.y = lm2_mod_##suffix(a.min.y, b.min.y);                       \
    result.min.z = lm2_mod_##suffix(a.min.z, b.min.z);                       \
    result.max.x = lm2_mod_##suffix(a.max.x, b.max.x);                       \
    result.max.y = lm2_mod_##suffix(a.max.y, b.max.y);                       \
    result.max.z = lm2_mod_##suffix(a.max.z, b.max.z);                       \
    return result;                                                           \
  }

// Range % Scalar
#define _LM2_IMPL_RANGE3_MOD_SCALAR(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_mod_scalar(type_name r, scalar_type s) {      \
    type_name result;                                                         \
    result.min.x = lm2_mod_##suffix(r.min.x, s);                              \
    result.min.y = lm2_mod_##suffix(r.min.y, s);                              \
    result.min.z = lm2_mod_##suffix(r.min.z, s);                              \
    result.max.x = lm2_mod_##suffix(r.max.x, s);                              \
    result.max.y = lm2_mod_##suffix(r.max.y, s);                              \
    result.max.z = lm2_mod_##suffix(r.max.z, s);                              \
    return result;                                                            \
  }

// Range % Vector
#define _LM2_IMPL_RANGE3_MOD_VECTOR(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_mod_vec(type_name r, vec_type v) {            \
    type_name result;                                                         \
    result.min.x = lm2_mod_##suffix(r.min.x, v.x);                            \
    result.min.y = lm2_mod_##suffix(r.min.y, v.y);                            \
    result.min.z = lm2_mod_##suffix(r.min.z, v.z);                            \
    result.max.x = lm2_mod_##suffix(r.max.x, v.x);                            \
    result.max.y = lm2_mod_##suffix(r.max.y, v.y);                            \
    result.max.z = lm2_mod_##suffix(r.max.z, v.z);                            \
    return result;                                                            \
  }

// Convenience macro to implement all arithmetic operations
#define _LM2_IMPL_RANGE3_ARITHMETIC(type_name, vec_type, scalar_type, suffix) \
  _LM2_IMPL_RANGE3_ADD_RANGE(type_name, vec_type, scalar_type, suffix)        \
  _LM2_IMPL_RANGE3_ADD_SCALAR(type_name, vec_type, scalar_type, suffix)       \
  _LM2_IMPL_RANGE3_ADD_VECTOR(type_name, vec_type, scalar_type, suffix)       \
  _LM2_IMPL_RANGE3_SUB_RANGE(type_name, vec_type, scalar_type, suffix)        \
  _LM2_IMPL_RANGE3_SUB_SCALAR(type_name, vec_type, scalar_type, suffix)       \
  _LM2_IMPL_RANGE3_SUB_VECTOR(type_name, vec_type, scalar_type, suffix)       \
  _LM2_IMPL_RANGE3_MUL_RANGE(type_name, vec_type, scalar_type, suffix)        \
  _LM2_IMPL_RANGE3_MUL_SCALAR(type_name, vec_type, scalar_type, suffix)       \
  _LM2_IMPL_RANGE3_MUL_VECTOR(type_name, vec_type, scalar_type, suffix)       \
  _LM2_IMPL_RANGE3_DIV_RANGE(type_name, vec_type, scalar_type, suffix)        \
  _LM2_IMPL_RANGE3_DIV_SCALAR(type_name, vec_type, scalar_type, suffix)       \
  _LM2_IMPL_RANGE3_DIV_VECTOR(type_name, vec_type, scalar_type, suffix)       \
  _LM2_IMPL_RANGE3_MOD_RANGE(type_name, vec_type, scalar_type, suffix)        \
  _LM2_IMPL_RANGE3_MOD_SCALAR(type_name, vec_type, scalar_type, suffix)       \
  _LM2_IMPL_RANGE3_MOD_VECTOR(type_name, vec_type, scalar_type, suffix)

// =============================================================================
// Range3 Scalar Function Implementation Macros
// =============================================================================
// These macros forward scalar functions to ranges by applying them
// component-wise to both min and max vectors.

// Unary scalar function (e.g., floor, ceil, abs)
#define _LM2_IMPL_RANGE3_SCALAR_FUNC_1(type_name, vec_type, func_name) \
  LM2_API type_name func_name##_##type_name(type_name a) {             \
    type_name result;                                                  \
    result.min = func_name##_##vec_type(a.min);                        \
    result.max = func_name##_##vec_type(a.max);                        \
    return result;                                                     \
  }

// Binary scalar function (e.g., min, max, pow, mod)
#define _LM2_IMPL_RANGE3_SCALAR_FUNC_2(type_name, vec_type, func_name)  \
  LM2_API type_name func_name##_##type_name(type_name a, type_name b) { \
    type_name result;                                                   \
    result.min = func_name##_##vec_type(a.min, b.min);                  \
    result.max = func_name##_##vec_type(a.max, b.max);                  \
    return result;                                                      \
  }

// Ternary scalar function (e.g., clamp, lerp, smoothstep)
#define _LM2_IMPL_RANGE3_SCALAR_FUNC_3(type_name, vec_type, func_name)               \
  LM2_API type_name func_name##_##type_name(type_name a, type_name b, type_name c) { \
    type_name result;                                                                \
    result.min = func_name##_##vec_type(a.min, b.min, c.min);                        \
    result.max = func_name##_##vec_type(a.max, b.max, c.max);                        \
    return result;                                                                   \
  }

// Master macro to implement all functions for a range3 type
#define _LM2_IMPL_RANGE3_ALL(type_name, vec_type, scalar_type, suffix)           \
  _LM2_IMPL_RANGE3_FROM_MIN_MAX(type_name, vec_type, scalar_type, suffix)        \
  _LM2_IMPL_RANGE3_FROM_CENTER_EXTENTS(type_name, vec_type, scalar_type, suffix) \
  _LM2_IMPL_RANGE3_FROM_CENTER_SIZE(type_name, vec_type, scalar_type, suffix)    \
  _LM2_IMPL_RANGE3_FROM_POSITION_SIZE(type_name, vec_type, scalar_type, suffix)  \
  _LM2_IMPL_RANGE3_ZERO(type_name, vec_type)                                     \
  _LM2_IMPL_RANGE3_NORMALIZE(type_name, vec_type, scalar_type, suffix)           \
  _LM2_IMPL_RANGE3_TRANSLATE(type_name, vec_type, scalar_type, suffix)           \
  _LM2_IMPL_RANGE3_SCALE(type_name, vec_type, scalar_type, suffix)               \
  _LM2_IMPL_RANGE3_EXPAND(type_name, vec_type, scalar_type, suffix)              \
  _LM2_IMPL_RANGE3_ARITHMETIC(type_name, vec_type, scalar_type, suffix)          \
  _LM2_IMPL_RANGE3_UNION(type_name, vec_type, scalar_type, suffix)               \
  _LM2_IMPL_RANGE3_INTERSECTION(type_name, vec_type, scalar_type, suffix)        \
  _LM2_IMPL_RANGE3_SIZE(type_name, vec_type, scalar_type, suffix)                \
  _LM2_IMPL_RANGE3_EXTENTS(type_name, vec_type, scalar_type, suffix)             \
  _LM2_IMPL_RANGE3_CENTER(type_name, vec_type, scalar_type, suffix)              \
  _LM2_IMPL_RANGE3_CONTAINS_POINT(type_name, vec_type, scalar_type, suffix)      \
  _LM2_IMPL_RANGE3_OVERLAPS(type_name, vec_type, scalar_type, suffix)            \
  _LM2_IMPL_RANGE3_VOLUME(type_name, vec_type, scalar_type, suffix)              \
  _LM2_IMPL_RANGE3_SCALAR_FUNC_1(type_name, vec_type, lm2_floor)                 \
  _LM2_IMPL_RANGE3_SCALAR_FUNC_1(type_name, vec_type, lm2_ceil)                  \
  _LM2_IMPL_RANGE3_SCALAR_FUNC_1(type_name, vec_type, lm2_round)                 \
  _LM2_IMPL_RANGE3_SCALAR_FUNC_1(type_name, vec_type, lm2_trunc)                 \
  _LM2_IMPL_RANGE3_SCALAR_FUNC_1(type_name, vec_type, lm2_abs)                   \
  _LM2_IMPL_RANGE3_SCALAR_FUNC_2(type_name, vec_type, lm2_floor_multiple)        \
  _LM2_IMPL_RANGE3_SCALAR_FUNC_2(type_name, vec_type, lm2_ceil_multiple)         \
  _LM2_IMPL_RANGE3_SCALAR_FUNC_2(type_name, vec_type, lm2_round_multiple)        \
  _LM2_IMPL_RANGE3_SCALAR_FUNC_2(type_name, vec_type, lm2_trunc_multiple)        \
  _LM2_IMPL_RANGE3_SCALAR_FUNC_2(type_name, vec_type, lm2_min)                   \
  _LM2_IMPL_RANGE3_SCALAR_FUNC_2(type_name, vec_type, lm2_max)                   \
  _LM2_IMPL_RANGE3_SCALAR_FUNC_3(type_name, vec_type, lm2_clamp)                 \
  _LM2_IMPL_RANGE3_SCALAR_FUNC_3(type_name, vec_type, lm2_lerp)

// =============================================================================
// Range3 Implementations for All 10 Numeric Types
// =============================================================================

_LM2_IMPL_RANGE3_ALL(lm2_range3f64, lm2_v3f64, double, f64)
_LM2_IMPL_RANGE3_ALL(lm2_range3f32, lm2_v3f32, float, f32)
_LM2_IMPL_RANGE3_ALL(lm2_range3i64, lm2_v3i64, int64_t, i64)
_LM2_IMPL_RANGE3_ALL(lm2_range3i32, lm2_v3i32, int32_t, i32)
_LM2_IMPL_RANGE3_ALL(lm2_range3i16, lm2_v3i16, int16_t, i16)
_LM2_IMPL_RANGE3_ALL(lm2_range3i8, lm2_v3i8, int8_t, i8)
_LM2_IMPL_RANGE3_ALL(lm2_range3u64, lm2_v3u64, uint64_t, u64)
_LM2_IMPL_RANGE3_ALL(lm2_range3u32, lm2_v3u32, uint32_t, u32)
_LM2_IMPL_RANGE3_ALL(lm2_range3u16, lm2_v3u16, uint16_t, u16)
_LM2_IMPL_RANGE3_ALL(lm2_range3u8, lm2_v3u8, uint8_t, u8)
