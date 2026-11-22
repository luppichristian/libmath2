#pragma once

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

#include <lm2/geometry2d/lm2_aabb2.h>
#include <lm2/geometry2d/lm2_edge2.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/vectors/lm2_vector_specifics.h>

// =============================================================================
// AABB2 Corner Implementation Macros
// =============================================================================

#define _LM2_IMPL_RECT2_GET_CORNER(type_name, vec_type, scalar_type, suffix)        \
  LM2_API vec_type lm2_r2_get_corner_##suffix(type_name rect, lm2_corner2 corner) { \
    switch (corner) {                                                               \
      case LM2_CORNER2_TOP_RIGHT: return rect.max;                                  \
      case LM2_CORNER2_TOP_LEFT:  {                                                 \
        vec_type v;                                                                 \
        v.x = rect.min.x;                                                           \
        v.y = rect.max.y;                                                           \
        return v;                                                                   \
      }                                                                             \
      case LM2_CORNER2_BOTTOM_RIGHT: {                                              \
        vec_type v;                                                                 \
        v.x = rect.max.x;                                                           \
        v.y = rect.min.y;                                                           \
        return v;                                                                   \
      }                                                                             \
      case LM2_CORNER2_BOTTOM_LEFT: return rect.min;                                \
      default:                      return rect.min;                                \
    }                                                                               \
  }

#define _LM2_IMPL_RECT2_GET_BOTTOM_LEFT(type_name, vec_type, scalar_type, suffix) \
  LM2_API vec_type lm2_r2_get_bottom_left_##suffix(type_name rect) {              \
    return rect.min;                                                              \
  }

#define _LM2_IMPL_RECT2_GET_TOP_RIGHT(type_name, vec_type, scalar_type, suffix) \
  LM2_API vec_type lm2_r2_get_top_right_##suffix(type_name rect) {              \
    return rect.max;                                                            \
  }

#define _LM2_IMPL_RECT2_GET_BOTTOM_RIGHT(type_name, vec_type, scalar_type, suffix) \
  LM2_API vec_type lm2_r2_get_bottom_right_##suffix(type_name rect) {              \
    vec_type result;                                                               \
    result.x = rect.max.x;                                                         \
    result.y = rect.min.y;                                                         \
    return result;                                                                 \
  }

#define _LM2_IMPL_RECT2_GET_TOP_LEFT(type_name, vec_type, scalar_type, suffix) \
  LM2_API vec_type lm2_r2_get_top_left_##suffix(type_name rect) {              \
    vec_type result;                                                           \
    result.x = rect.min.x;                                                     \
    result.y = rect.max.y;                                                     \
    return result;                                                             \
  }

// =============================================================================
// AABB2 Transform Implementation Macros
// =============================================================================

#define _LM2_IMPL_RECT2_SCALE_FROM_CENTER(type_name, vec_type, scalar_type, suffix)     \
  LM2_API type_name lm2_r2_scale_from_center_##suffix(type_name rect, vec_type scale) { \
    vec_type center = lm2_r2_center_##suffix(rect);                                     \
    vec_type extents = lm2_r2_extents_##suffix(rect);                                   \
    vec_type new_extents;                                                               \
    new_extents.x = lm2_mul_##suffix(extents.x, scale.x);                               \
    new_extents.y = lm2_mul_##suffix(extents.y, scale.y);                               \
    return lm2_r2_from_center_extents_##suffix(center, new_extents);                    \
  }

#define _LM2_IMPL_RECT2_SCALE_FROM_MIN(type_name, vec_type, scalar_type, suffix)     \
  LM2_API type_name lm2_r2_scale_from_min_##suffix(type_name rect, vec_type scale) { \
    vec_type size = lm2_r2_size_##suffix(rect);                                      \
    vec_type new_size;                                                               \
    new_size.x = lm2_mul_##suffix(size.x, scale.x);                                  \
    new_size.y = lm2_mul_##suffix(size.y, scale.y);                                  \
    return lm2_r2_from_position_size_##suffix(rect.min, new_size);                   \
  }

#define _LM2_IMPL_RECT2_SCALE_FROM_MAX(type_name, vec_type, scalar_type, suffix)     \
  LM2_API type_name lm2_r2_scale_from_max_##suffix(type_name rect, vec_type scale) { \
    vec_type size = lm2_r2_size_##suffix(rect);                                      \
    vec_type new_size;                                                               \
    new_size.x = lm2_mul_##suffix(size.x, scale.x);                                  \
    new_size.y = lm2_mul_##suffix(size.y, scale.y);                                  \
    vec_type new_min;                                                                \
    new_min.x = lm2_sub_##suffix(rect.max.x, new_size.x);                            \
    new_min.y = lm2_sub_##suffix(rect.max.y, new_size.y);                            \
    return lm2_r2_from_position_size_##suffix(new_min, new_size);                    \
  }

#define _LM2_IMPL_RECT2_SHRINK_VEC(type_name, vec_type, scalar_type, suffix)      \
  LM2_API type_name lm2_r2_shrink_vec_##suffix(type_name rect, vec_type amount) { \
    type_name result;                                                             \
    result.min.x = lm2_add_##suffix(rect.min.x, amount.x);                        \
    result.min.y = lm2_add_##suffix(rect.min.y, amount.y);                        \
    result.max.x = lm2_sub_##suffix(rect.max.x, amount.x);                        \
    result.max.y = lm2_sub_##suffix(rect.max.y, amount.y);                        \
    return result;                                                                \
  }

#define _LM2_IMPL_RECT2_SHRINK_SCALAR(type_name, vec_type, scalar_type, suffix)         \
  LM2_API type_name lm2_r2_shrink_scalar_##suffix(type_name rect, scalar_type amount) { \
    type_name result;                                                                   \
    result.min.x = lm2_add_##suffix(rect.min.x, amount);                                \
    result.min.y = lm2_add_##suffix(rect.min.y, amount);                                \
    result.max.x = lm2_sub_##suffix(rect.max.x, amount);                                \
    result.max.y = lm2_sub_##suffix(rect.max.y, amount);                                \
    return result;                                                                      \
  }

#define _LM2_IMPL_RECT2_INFLATE_VEC(type_name, vec_type, scalar_type, suffix)      \
  LM2_API type_name lm2_r2_inflate_vec_##suffix(type_name rect, vec_type amount) { \
    type_name result;                                                              \
    result.min.x = lm2_sub_##suffix(rect.min.x, amount.x);                         \
    result.min.y = lm2_sub_##suffix(rect.min.y, amount.y);                         \
    result.max.x = lm2_add_##suffix(rect.max.x, amount.x);                         \
    result.max.y = lm2_add_##suffix(rect.max.y, amount.y);                         \
    return result;                                                                 \
  }

#define _LM2_IMPL_RECT2_INFLATE_SCALAR(type_name, vec_type, scalar_type, suffix)         \
  LM2_API type_name lm2_r2_inflate_scalar_##suffix(type_name rect, scalar_type amount) { \
    type_name result;                                                                    \
    result.min.x = lm2_sub_##suffix(rect.min.x, amount);                                 \
    result.min.y = lm2_sub_##suffix(rect.min.y, amount);                                 \
    result.max.x = lm2_add_##suffix(rect.max.x, amount);                                 \
    result.max.y = lm2_add_##suffix(rect.max.y, amount);                                 \
    return result;                                                                       \
  }

// =============================================================================
// AABB2 Query Implementation Macros
// =============================================================================

#define _LM2_IMPL_RECT2_GET_DIM(type_name, vec_type, scalar_type, suffix) \
  LM2_API vec_type lm2_r2_get_dim_##suffix(type_name rect) {              \
    return lm2_r2_size_##suffix(rect);                                    \
  }

#define _LM2_IMPL_RECT2_OVERLAP_RECT(type_name, vec_type, scalar_type, suffix) \
  LM2_API int lm2_r2_overlap_rect_##suffix(type_name a, type_name b) {         \
    return lm2_r2_overlaps_##suffix(a, b);                                     \
  }

#define _LM2_IMPL_RECT2_OVERLAP_POINT(type_name, vec_type, scalar_type, suffix) \
  LM2_API int lm2_r2_overlap_point_##suffix(type_name rect, vec_type point) {   \
    return lm2_r2_contains_point_##suffix(rect, point);                         \
  }

#define _LM2_IMPL_RECT2_CONTAINS(type_name, vec_type, scalar_type, suffix)             \
  LM2_API int lm2_r2_contains_##suffix(type_name rect, type_name subrect) {            \
    int min_contained = (subrect.min.x >= rect.min.x && subrect.min.x <= rect.max.x && \
                         subrect.min.y >= rect.min.y && subrect.min.y <= rect.max.y);  \
    int max_contained = (subrect.max.x >= rect.min.x && subrect.max.x <= rect.max.x && \
                         subrect.max.y >= rect.min.y && subrect.max.y <= rect.max.y);  \
    return min_contained && max_contained;                                             \
  }

#define _LM2_IMPL_RECT2_DISTANCE(type_name, vec_type, scalar_type, suffix)       \
  LM2_API scalar_type lm2_r2_distance_##suffix(type_name rect, vec_type point) { \
    vec_type closest = lm2_r2_get_closest_point_##suffix(rect, point);           \
    return lm2_v2_distance_##suffix(point, closest);                             \
  }

#define _LM2_IMPL_RECT2_GET_CLOSEST_POINT(type_name, vec_type, scalar_type, suffix)    \
  LM2_API vec_type lm2_r2_get_closest_point_##suffix(type_name rect, vec_type point) { \
    vec_type result;                                                                   \
    result.x = lm2_clamp_##suffix(rect.min.x, point.x, rect.max.x);                    \
    result.y = lm2_clamp_##suffix(rect.min.y, point.y, rect.max.y);                    \
    return result;                                                                     \
  }

#define _LM2_IMPL_RECT2_CLOSEST_DISTANCE_FROM_EDGES(type_name, vec_type, scalar_type, suffix)       \
  LM2_API scalar_type lm2_r2_closest_distance_from_edges_##suffix(type_name a, type_name b) {       \
    if (lm2_r2_overlaps_##suffix(a, b)) {                                                           \
      return (scalar_type)0;                                                                        \
    }                                                                                               \
    scalar_type dx = (scalar_type)0;                                                                \
    scalar_type dy = (scalar_type)0;                                                                \
    if (b.max.x < a.min.x) {                                                                        \
      dx = lm2_sub_##suffix(a.min.x, b.max.x);                                                      \
    } else if (b.min.x > a.max.x) {                                                                 \
      dx = lm2_sub_##suffix(b.min.x, a.max.x);                                                      \
    }                                                                                               \
    if (b.max.y < a.min.y) {                                                                        \
      dy = lm2_sub_##suffix(a.min.y, b.max.y);                                                      \
    } else if (b.min.y > a.max.y) {                                                                 \
      dy = lm2_sub_##suffix(b.min.y, a.max.y);                                                      \
    }                                                                                               \
    return lm2_sqrt_##suffix(lm2_add_##suffix(lm2_mul_##suffix(dx, dx), lm2_mul_##suffix(dy, dy))); \
  }

// Exact orientation for 64-bit integer coordinates. A coordinate difference
// can require 64 magnitude bits and a cross-product term 128 bits, even when
// the source coordinates are signed. Represent each product as two limbs so
// this also works on compilers without a native 128-bit integer type.
typedef struct _lm2_u128_pair {
  uint64_t high, low;
} _lm2_u128_pair;
typedef struct _lm2_integer_point {
  uint64_t x, y;
} _lm2_integer_point;

static _lm2_u128_pair _lm2_multiply_u64_wide(uint64_t a, uint64_t b) {
  uint64_t al = (uint32_t)a, ah = a >> 32;
  uint64_t bl = (uint32_t)b, bh = b >> 32;
  uint64_t p00 = lm2_mul_u64(al, bl), p01 = lm2_mul_u64(al, bh);
  uint64_t p10 = lm2_mul_u64(ah, bl), p11 = lm2_mul_u64(ah, bh);
  uint64_t middle = lm2_add_u64(lm2_add_u64(p00 >> 32, (uint32_t)p01), (uint32_t)p10);
  return LM2_PRIVATE_LITERAL(_lm2_u128_pair) {lm2_add_u64(lm2_add_u64(lm2_add_u64(p11, p01 >> 32), p10 >> 32), middle >> 32),
                                              (middle << 32) | (uint32_t)p00};
}

static int _lm2_integer_difference(uint64_t a, uint64_t b, uint64_t* magnitude) {
  if (a > b) {
    *magnitude = lm2_sub_u64(a, b);
    return 1;
  }
  if (a < b) {
    *magnitude = lm2_sub_u64(b, a);
    return -1;
  }
  *magnitude = 0;
  return 0;
}

static int _lm2_integer_orientation(_lm2_integer_point a, _lm2_integer_point b, _lm2_integer_point c) {
  uint64_t bx, by, cx, cy;
  int sx = _lm2_integer_difference(b.x, a.x, &bx);
  int sy = _lm2_integer_difference(b.y, a.y, &by);
  int tx = _lm2_integer_difference(c.x, a.x, &cx);
  int ty = _lm2_integer_difference(c.y, a.y, &cy);
  int p_sign = lm2_mul_i32(sx, ty), q_sign = lm2_mul_i32(sy, tx);
  if (p_sign != q_sign) return p_sign > q_sign ? 1 : -1;
  if (p_sign == 0) return 0;
  _lm2_u128_pair p = _lm2_multiply_u64_wide(bx, cy);
  _lm2_u128_pair q = _lm2_multiply_u64_wide(by, cx);
  int cmp = p.high != q.high ? (p.high > q.high ? 1 : -1) : p.low != q.low ? (p.low > q.low ? 1 : -1)
                                                                           : 0;
  return lm2_mul_i32(p_sign, cmp);
}

static bool _lm2_integer_point_on_segment(_lm2_integer_point p, _lm2_integer_point a, _lm2_integer_point b) {
  return p.x >= (a.x < b.x ? a.x : b.x) && p.x <= (a.x > b.x ? a.x : b.x) &&
         p.y >= (a.y < b.y ? a.y : b.y) && p.y <= (a.y > b.y ? a.y : b.y);
}

static int _lm2_integer_segments_intersect(_lm2_integer_point a, _lm2_integer_point b, _lm2_integer_point c, _lm2_integer_point d) {
  int ab_c = _lm2_integer_orientation(a, b, c), ab_d = _lm2_integer_orientation(a, b, d);
  int cd_a = _lm2_integer_orientation(c, d, a), cd_b = _lm2_integer_orientation(c, d, b);
  if (lm2_mul_i32(ab_c, ab_d) < 0 && lm2_mul_i32(cd_a, cd_b) < 0) return 1;
  return (ab_c == 0 && _lm2_integer_point_on_segment(c, a, b)) ||
         (ab_d == 0 && _lm2_integer_point_on_segment(d, a, b)) ||
         (cd_a == 0 && _lm2_integer_point_on_segment(a, c, d)) ||
         (cd_b == 0 && _lm2_integer_point_on_segment(b, c, d));
}

// XOR maps signed coordinates monotonically onto the unsigned domain. Casts
// from signed values to uint64_t are defined modulo 2^64, including INT64_MIN.
#define _LM2_IMPL_INTEGER_SEGMENTS(vec_type, suffix, mask)                                          \
  LM2_API int lm2_segments_intersect_##suffix(vec_type a0, vec_type a1, vec_type b0, vec_type b1) { \
    _lm2_integer_point a = {(uint64_t)a0.x ^ (mask), (uint64_t)a0.y ^ (mask)};                      \
    _lm2_integer_point b = {(uint64_t)a1.x ^ (mask), (uint64_t)a1.y ^ (mask)};                      \
    _lm2_integer_point c = {(uint64_t)b0.x ^ (mask), (uint64_t)b0.y ^ (mask)};                      \
    _lm2_integer_point d = {(uint64_t)b1.x ^ (mask), (uint64_t)b1.y ^ (mask)};                      \
    return _lm2_integer_segments_intersect(a, b, c, d);                                             \
  }

// =============================================================================
// AABB2 Cut Implementation Macros
// =============================================================================

#define _LM2_IMPL_RECT2_CUT(type_name, vec_type, scalar_type, suffix)                                 \
  LM2_API type_name lm2_r2_cut_##suffix(type_name* rect, lm2_rect_cut cut_type, scalar_type amount) { \
    LM2_ASSERT(rect != NULL);                                                                         \
    switch (cut_type) {                                                                               \
      case LM2_RECT_CUT_LEFT:   return lm2_r2_cut_left_##suffix(rect, amount);                        \
      case LM2_RECT_CUT_RIGHT:  return lm2_r2_cut_right_##suffix(rect, amount);                       \
      case LM2_RECT_CUT_TOP:    return lm2_r2_cut_top_##suffix(rect, amount);                         \
      case LM2_RECT_CUT_BOTTOM: return lm2_r2_cut_bottom_##suffix(rect, amount);                      \
      default:                  {                                                                     \
        type_name zero = lm2_r2_zero_##suffix();                                                      \
        return zero;                                                                                  \
      }                                                                                               \
    }                                                                                                 \
  }

#define _LM2_IMPL_RECT2_CUT_LEFT(type_name, vec_type, scalar_type, suffix)          \
  LM2_API type_name lm2_r2_cut_left_##suffix(type_name* rect, scalar_type amount) { \
    LM2_ASSERT(rect != NULL);                                                       \
    type_name result;                                                               \
    result.min = rect->min;                                                         \
    result.max.x = lm2_add_##suffix(rect->min.x, amount);                           \
    result.max.y = rect->max.y;                                                     \
    rect->min.x = lm2_add_##suffix(rect->min.x, amount);                            \
    return result;                                                                  \
  }

#define _LM2_IMPL_RECT2_CUT_RIGHT(type_name, vec_type, scalar_type, suffix)          \
  LM2_API type_name lm2_r2_cut_right_##suffix(type_name* rect, scalar_type amount) { \
    LM2_ASSERT(rect != NULL);                                                        \
    type_name result;                                                                \
    result.min.x = lm2_sub_##suffix(rect->max.x, amount);                            \
    result.min.y = rect->min.y;                                                      \
    result.max = rect->max;                                                          \
    rect->max.x = lm2_sub_##suffix(rect->max.x, amount);                             \
    return result;                                                                   \
  }

#define _LM2_IMPL_RECT2_CUT_BOTTOM(type_name, vec_type, scalar_type, suffix)          \
  LM2_API type_name lm2_r2_cut_bottom_##suffix(type_name* rect, scalar_type amount) { \
    LM2_ASSERT(rect != NULL);                                                         \
    type_name result;                                                                 \
    result.min = rect->min;                                                           \
    result.max.x = rect->max.x;                                                       \
    result.max.y = lm2_add_##suffix(rect->min.y, amount);                             \
    rect->min.y = lm2_add_##suffix(rect->min.y, amount);                              \
    return result;                                                                    \
  }

#define _LM2_IMPL_RECT2_CUT_TOP(type_name, vec_type, scalar_type, suffix)          \
  LM2_API type_name lm2_r2_cut_top_##suffix(type_name* rect, scalar_type amount) { \
    LM2_ASSERT(rect != NULL);                                                      \
    type_name result;                                                              \
    result.min.x = rect->min.x;                                                    \
    result.min.y = lm2_sub_##suffix(rect->max.y, amount);                          \
    result.max = rect->max;                                                        \
    rect->max.y = lm2_sub_##suffix(rect->max.y, amount);                           \
    return result;                                                                 \
  }

// =============================================================================
// AABB2 Alignment Implementation Macros
// =============================================================================

#define _LM2_IMPL_RECT2_ALIGN_SUBRECT(type_name, vec_type, scalar_type, suffix)                                              \
  LM2_API type_name lm2_r2_align_subrect_##suffix(type_name rect, type_name subrect, lm2_align align_x, lm2_align align_y) { \
    vec_type rect_size = lm2_r2_size_##suffix(rect);                                                                         \
    vec_type sub_size = lm2_r2_size_##suffix(subrect);                                                                       \
    type_name result = subrect;                                                                                              \
    scalar_type two = (scalar_type)2;                                                                                        \
    switch (align_x) {                                                                                                       \
      case LM2_ALIGN_START:                                                                                                  \
        result.min.x = rect.min.x;                                                                                           \
        result.max.x = lm2_add_##suffix(rect.min.x, sub_size.x);                                                             \
        break;                                                                                                               \
      case LM2_ALIGN_CENTER: {                                                                                               \
        scalar_type offset = lm2_div_##suffix(lm2_sub_##suffix(rect_size.x, sub_size.x), two);                               \
        result.min.x = lm2_add_##suffix(rect.min.x, offset);                                                                 \
        result.max.x = lm2_add_##suffix(result.min.x, sub_size.x);                                                           \
        break;                                                                                                               \
      }                                                                                                                      \
      case LM2_ALIGN_END:                                                                                                    \
        result.max.x = rect.max.x;                                                                                           \
        result.min.x = lm2_sub_##suffix(rect.max.x, sub_size.x);                                                             \
        break;                                                                                                               \
    }                                                                                                                        \
    switch (align_y) {                                                                                                       \
      case LM2_ALIGN_START:                                                                                                  \
        result.min.y = rect.min.y;                                                                                           \
        result.max.y = lm2_add_##suffix(rect.min.y, sub_size.y);                                                             \
        break;                                                                                                               \
      case LM2_ALIGN_CENTER: {                                                                                               \
        scalar_type offset = lm2_div_##suffix(lm2_sub_##suffix(rect_size.y, sub_size.y), two);                               \
        result.min.y = lm2_add_##suffix(rect.min.y, offset);                                                                 \
        result.max.y = lm2_add_##suffix(result.min.y, sub_size.y);                                                           \
        break;                                                                                                               \
      }                                                                                                                      \
      case LM2_ALIGN_END:                                                                                                    \
        result.max.y = rect.max.y;                                                                                           \
        result.min.y = lm2_sub_##suffix(rect.max.y, sub_size.y);                                                             \
        break;                                                                                                               \
    }                                                                                                                        \
    return result;                                                                                                           \
  }

// =============================================================================
// Complete AABB2 Implementation for One Type
// =============================================================================

// Macro for floating-point types (includes distance functions)
#define _LM2_IMPL_RECT2_ALL_FLOAT(type_name, vec_type, scalar_type, suffix)             \
  _LM2_IMPL_RECT2_GET_CORNER(type_name, vec_type, scalar_type, suffix)                  \
  _LM2_IMPL_RECT2_GET_BOTTOM_LEFT(type_name, vec_type, scalar_type, suffix)             \
  _LM2_IMPL_RECT2_GET_TOP_RIGHT(type_name, vec_type, scalar_type, suffix)               \
  _LM2_IMPL_RECT2_GET_BOTTOM_RIGHT(type_name, vec_type, scalar_type, suffix)            \
  _LM2_IMPL_RECT2_GET_TOP_LEFT(type_name, vec_type, scalar_type, suffix)                \
  _LM2_IMPL_RECT2_SCALE_FROM_CENTER(type_name, vec_type, scalar_type, suffix)           \
  _LM2_IMPL_RECT2_SCALE_FROM_MIN(type_name, vec_type, scalar_type, suffix)              \
  _LM2_IMPL_RECT2_SCALE_FROM_MAX(type_name, vec_type, scalar_type, suffix)              \
  _LM2_IMPL_RECT2_SHRINK_VEC(type_name, vec_type, scalar_type, suffix)                  \
  _LM2_IMPL_RECT2_SHRINK_SCALAR(type_name, vec_type, scalar_type, suffix)               \
  _LM2_IMPL_RECT2_INFLATE_VEC(type_name, vec_type, scalar_type, suffix)                 \
  _LM2_IMPL_RECT2_INFLATE_SCALAR(type_name, vec_type, scalar_type, suffix)              \
  _LM2_IMPL_RECT2_GET_DIM(type_name, vec_type, scalar_type, suffix)                     \
  _LM2_IMPL_RECT2_OVERLAP_RECT(type_name, vec_type, scalar_type, suffix)                \
  _LM2_IMPL_RECT2_OVERLAP_POINT(type_name, vec_type, scalar_type, suffix)               \
  _LM2_IMPL_RECT2_CONTAINS(type_name, vec_type, scalar_type, suffix)                    \
  _LM2_IMPL_RECT2_DISTANCE(type_name, vec_type, scalar_type, suffix)                    \
  _LM2_IMPL_RECT2_GET_CLOSEST_POINT(type_name, vec_type, scalar_type, suffix)           \
  _LM2_IMPL_RECT2_CLOSEST_DISTANCE_FROM_EDGES(type_name, vec_type, scalar_type, suffix) \
  _LM2_IMPL_RECT2_CUT(type_name, vec_type, scalar_type, suffix)                         \
  _LM2_IMPL_RECT2_CUT_LEFT(type_name, vec_type, scalar_type, suffix)                    \
  _LM2_IMPL_RECT2_CUT_RIGHT(type_name, vec_type, scalar_type, suffix)                   \
  _LM2_IMPL_RECT2_CUT_BOTTOM(type_name, vec_type, scalar_type, suffix)                  \
  _LM2_IMPL_RECT2_CUT_TOP(type_name, vec_type, scalar_type, suffix)                     \
  _LM2_IMPL_RECT2_ALIGN_SUBRECT(type_name, vec_type, scalar_type, suffix)

// Macro for integer types (excludes distance functions that require sqrt)
#define _LM2_IMPL_RECT2_ALL_INT(type_name, vec_type, scalar_type, suffix)     \
  _LM2_IMPL_RECT2_GET_CORNER(type_name, vec_type, scalar_type, suffix)        \
  _LM2_IMPL_RECT2_GET_BOTTOM_LEFT(type_name, vec_type, scalar_type, suffix)   \
  _LM2_IMPL_RECT2_GET_TOP_RIGHT(type_name, vec_type, scalar_type, suffix)     \
  _LM2_IMPL_RECT2_GET_BOTTOM_RIGHT(type_name, vec_type, scalar_type, suffix)  \
  _LM2_IMPL_RECT2_GET_TOP_LEFT(type_name, vec_type, scalar_type, suffix)      \
  _LM2_IMPL_RECT2_SCALE_FROM_CENTER(type_name, vec_type, scalar_type, suffix) \
  _LM2_IMPL_RECT2_SCALE_FROM_MIN(type_name, vec_type, scalar_type, suffix)    \
  _LM2_IMPL_RECT2_SCALE_FROM_MAX(type_name, vec_type, scalar_type, suffix)    \
  _LM2_IMPL_RECT2_SHRINK_VEC(type_name, vec_type, scalar_type, suffix)        \
  _LM2_IMPL_RECT2_SHRINK_SCALAR(type_name, vec_type, scalar_type, suffix)     \
  _LM2_IMPL_RECT2_INFLATE_VEC(type_name, vec_type, scalar_type, suffix)       \
  _LM2_IMPL_RECT2_INFLATE_SCALAR(type_name, vec_type, scalar_type, suffix)    \
  _LM2_IMPL_RECT2_GET_DIM(type_name, vec_type, scalar_type, suffix)           \
  _LM2_IMPL_RECT2_OVERLAP_RECT(type_name, vec_type, scalar_type, suffix)      \
  _LM2_IMPL_RECT2_OVERLAP_POINT(type_name, vec_type, scalar_type, suffix)     \
  _LM2_IMPL_RECT2_CONTAINS(type_name, vec_type, scalar_type, suffix)          \
  _LM2_IMPL_RECT2_GET_CLOSEST_POINT(type_name, vec_type, scalar_type, suffix) \
  _LM2_IMPL_RECT2_CUT(type_name, vec_type, scalar_type, suffix)               \
  _LM2_IMPL_RECT2_CUT_LEFT(type_name, vec_type, scalar_type, suffix)          \
  _LM2_IMPL_RECT2_CUT_RIGHT(type_name, vec_type, scalar_type, suffix)         \
  _LM2_IMPL_RECT2_CUT_BOTTOM(type_name, vec_type, scalar_type, suffix)        \
  _LM2_IMPL_RECT2_CUT_TOP(type_name, vec_type, scalar_type, suffix)           \
  _LM2_IMPL_RECT2_ALIGN_SUBRECT(type_name, vec_type, scalar_type, suffix)

// =============================================================================
// AABB2 Implementations for All 10 Types
// =============================================================================

// Floating-point types (with distance functions)
_LM2_IMPL_RECT2_ALL_FLOAT(lm2_r2_f64, lm2_v2_f64, double, f64)
_LM2_IMPL_RECT2_ALL_FLOAT(lm2_r2_f32, lm2_v2_f32, float, f32)

// Integer types (without distance functions that require sqrt or lm2_v2_distance)
_LM2_IMPL_RECT2_ALL_INT(lm2_r2_i64, lm2_v2_i64, int64_t, i64)
_LM2_IMPL_RECT2_ALL_INT(lm2_r2_i32, lm2_v2_i32, int32_t, i32)
_LM2_IMPL_RECT2_ALL_INT(lm2_r2_i16, lm2_v2_i16, int16_t, i16)
_LM2_IMPL_RECT2_ALL_INT(lm2_r2_i8, lm2_v2_i8, int8_t, i8)
_LM2_IMPL_RECT2_ALL_INT(lm2_r2_u64, lm2_v2_u64, uint64_t, u64)
_LM2_IMPL_RECT2_ALL_INT(lm2_r2_u32, lm2_v2_u32, uint32_t, u32)
_LM2_IMPL_RECT2_ALL_INT(lm2_r2_u16, lm2_v2_u16, uint16_t, u16)
_LM2_IMPL_RECT2_ALL_INT(lm2_r2_u8, lm2_v2_u8, uint8_t, u8)

// Segments intersect implementations
// f64/f32: forward to canonical lm2_edge2 API
LM2_API int lm2_segments_intersect_f64(lm2_v2_f64 a0, lm2_v2_f64 a1, lm2_v2_f64 b0, lm2_v2_f64 b1) {
  return lm2_edge2_segments_intersect_f64(a0, a1, b0, b1);
}
LM2_API int lm2_segments_intersect_f32(lm2_v2_f32 a0, lm2_v2_f32 a1, lm2_v2_f32 b0, lm2_v2_f32 b1) {
  return lm2_edge2_segments_intersect_f32(a0, a1, b0, b1);
}
_LM2_IMPL_INTEGER_SEGMENTS(lm2_v2_i64, i64, UINT64_C(0x8000000000000000))
_LM2_IMPL_INTEGER_SEGMENTS(lm2_v2_i32, i32, UINT64_C(0x8000000000000000))
_LM2_IMPL_INTEGER_SEGMENTS(lm2_v2_i16, i16, UINT64_C(0x8000000000000000))
_LM2_IMPL_INTEGER_SEGMENTS(lm2_v2_i8, i8, UINT64_C(0x8000000000000000))
_LM2_IMPL_INTEGER_SEGMENTS(lm2_v2_u64, u64, UINT64_C(0))
_LM2_IMPL_INTEGER_SEGMENTS(lm2_v2_u32, u32, UINT64_C(0))
_LM2_IMPL_INTEGER_SEGMENTS(lm2_v2_u16, u16, UINT64_C(0))
_LM2_IMPL_INTEGER_SEGMENTS(lm2_v2_u8, u8, UINT64_C(0))
