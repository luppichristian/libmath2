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

#include <lm2/geometry/lm2_rectangle.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/vectors/lm2_vector_specifics.h>

// =============================================================================
// Rectangle Corner Implementation Macros
// =============================================================================

#define _LM2_IMPL_RECT2_GET_CORNER(type_name, vec_type, scalar_type, suffix)    \
  LM2_API vec_type type_name##_get_corner(type_name rect, lm2_corner2 corner) { \
    switch (corner) {                                                           \
      case LM2_CORNER2_TOP_RIGHT: return rect.max;                              \
      case LM2_CORNER2_TOP_LEFT:  {                                             \
        vec_type v;                                                             \
        v.x = rect.min.x;                                                       \
        v.y = rect.max.y;                                                       \
        return v;                                                               \
      }                                                                         \
      case LM2_CORNER2_BOTTOM_RIGHT: {                                          \
        vec_type v;                                                             \
        v.x = rect.max.x;                                                       \
        v.y = rect.min.y;                                                       \
        return v;                                                               \
      }                                                                         \
      case LM2_CORNER2_BOTTOM_LEFT: return rect.min;                            \
      default:                      return rect.min;                                                 \
    }                                                                           \
  }

#define _LM2_IMPL_RECT2_GET_BOTTOM_LEFT(type_name, vec_type, scalar_type, suffix) \
  LM2_API vec_type type_name##_get_bottom_left(type_name rect) {                  \
    return rect.min;                                                              \
  }

#define _LM2_IMPL_RECT2_GET_TOP_RIGHT(type_name, vec_type, scalar_type, suffix) \
  LM2_API vec_type type_name##_get_top_right(type_name rect) {                  \
    return rect.max;                                                            \
  }

#define _LM2_IMPL_RECT2_GET_BOTTOM_RIGHT(type_name, vec_type, scalar_type, suffix) \
  LM2_API vec_type type_name##_get_bottom_right(type_name rect) {                  \
    vec_type result;                                                               \
    result.x = rect.max.x;                                                         \
    result.y = rect.min.y;                                                         \
    return result;                                                                 \
  }

#define _LM2_IMPL_RECT2_GET_TOP_LEFT(type_name, vec_type, scalar_type, suffix) \
  LM2_API vec_type type_name##_get_top_left(type_name rect) {                  \
    vec_type result;                                                           \
    result.x = rect.min.x;                                                     \
    result.y = rect.max.y;                                                     \
    return result;                                                             \
  }

// =============================================================================
// Rectangle Transform Implementation Macros
// =============================================================================

#define _LM2_IMPL_RECT2_SCALE_FROM_CENTER(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_scale_from_center(type_name rect, vec_type scale) { \
    vec_type center = type_name##_center(rect);                                     \
    vec_type extents = type_name##_extents(rect);                                   \
    vec_type new_extents;                                                           \
    new_extents.x = lm2_mul_##suffix(extents.x, scale.x);                           \
    new_extents.y = lm2_mul_##suffix(extents.y, scale.y);                           \
    return type_name##_from_center_extents(center, new_extents);                    \
  }

#define _LM2_IMPL_RECT2_SCALE_FROM_MIN(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_scale_from_min(type_name rect, vec_type scale) { \
    vec_type size = type_name##_size(rect);                                      \
    vec_type new_size;                                                           \
    new_size.x = lm2_mul_##suffix(size.x, scale.x);                              \
    new_size.y = lm2_mul_##suffix(size.y, scale.y);                              \
    return type_name##_from_position_size(rect.min, new_size);                   \
  }

#define _LM2_IMPL_RECT2_SCALE_FROM_MAX(type_name, vec_type, scalar_type, suffix) \
  LM2_API type_name type_name##_scale_from_max(type_name rect, vec_type scale) { \
    vec_type size = type_name##_size(rect);                                      \
    vec_type new_size;                                                           \
    new_size.x = lm2_mul_##suffix(size.x, scale.x);                              \
    new_size.y = lm2_mul_##suffix(size.y, scale.y);                              \
    vec_type new_min;                                                            \
    new_min.x = lm2_sub_##suffix(rect.max.x, new_size.x);                        \
    new_min.y = lm2_sub_##suffix(rect.max.y, new_size.y);                        \
    return type_name##_from_position_size(new_min, new_size);                    \
  }

#define _LM2_IMPL_RECT2_SHRINK_VEC(type_name, vec_type, scalar_type, suffix)  \
  LM2_API type_name type_name##_shrink_vec(type_name rect, vec_type amount) { \
    type_name result;                                                         \
    result.min.x = lm2_add_##suffix(rect.min.x, amount.x);                    \
    result.min.y = lm2_add_##suffix(rect.min.y, amount.y);                    \
    result.max.x = lm2_sub_##suffix(rect.max.x, amount.x);                    \
    result.max.y = lm2_sub_##suffix(rect.max.y, amount.y);                    \
    return result;                                                            \
  }

#define _LM2_IMPL_RECT2_SHRINK_SCALAR(type_name, vec_type, scalar_type, suffix)     \
  LM2_API type_name type_name##_shrink_scalar(type_name rect, scalar_type amount) { \
    type_name result;                                                               \
    result.min.x = lm2_add_##suffix(rect.min.x, amount);                            \
    result.min.y = lm2_add_##suffix(rect.min.y, amount);                            \
    result.max.x = lm2_sub_##suffix(rect.max.x, amount);                            \
    result.max.y = lm2_sub_##suffix(rect.max.y, amount);                            \
    return result;                                                                  \
  }

#define _LM2_IMPL_RECT2_INFLATE_VEC(type_name, vec_type, scalar_type, suffix)  \
  LM2_API type_name type_name##_inflate_vec(type_name rect, vec_type amount) { \
    type_name result;                                                          \
    result.min.x = lm2_sub_##suffix(rect.min.x, amount.x);                     \
    result.min.y = lm2_sub_##suffix(rect.min.y, amount.y);                     \
    result.max.x = lm2_add_##suffix(rect.max.x, amount.x);                     \
    result.max.y = lm2_add_##suffix(rect.max.y, amount.y);                     \
    return result;                                                             \
  }

#define _LM2_IMPL_RECT2_INFLATE_SCALAR(type_name, vec_type, scalar_type, suffix)     \
  LM2_API type_name type_name##_inflate_scalar(type_name rect, scalar_type amount) { \
    type_name result;                                                                \
    result.min.x = lm2_sub_##suffix(rect.min.x, amount);                             \
    result.min.y = lm2_sub_##suffix(rect.min.y, amount);                             \
    result.max.x = lm2_add_##suffix(rect.max.x, amount);                             \
    result.max.y = lm2_add_##suffix(rect.max.y, amount);                             \
    return result;                                                                   \
  }

// =============================================================================
// Rectangle Query Implementation Macros
// =============================================================================

#define _LM2_IMPL_RECT2_GET_DIM(type_name, vec_type, scalar_type, suffix) \
  LM2_API vec_type type_name##_get_dim(type_name rect) {                  \
    return type_name##_size(rect);                                        \
  }

#define _LM2_IMPL_RECT2_OVERLAP_RECT(type_name, vec_type, scalar_type, suffix) \
  LM2_API int type_name##_overlap_rect(type_name a, type_name b) {             \
    return type_name##_overlaps(a, b);                                         \
  }

#define _LM2_IMPL_RECT2_OVERLAP_POINT(type_name, vec_type, scalar_type, suffix) \
  LM2_API int type_name##_overlap_point(type_name rect, vec_type point) {       \
    return type_name##_contains_point(rect, point);                             \
  }

#define _LM2_IMPL_RECT2_CONTAINS(type_name, vec_type, scalar_type, suffix)             \
  LM2_API int type_name##_contains(type_name rect, type_name subrect) {                \
    int min_contained = (subrect.min.x >= rect.min.x && subrect.min.x <= rect.max.x && \
                         subrect.min.y >= rect.min.y && subrect.min.y <= rect.max.y);  \
    int max_contained = (subrect.max.x >= rect.min.x && subrect.max.x <= rect.max.x && \
                         subrect.max.y >= rect.min.y && subrect.max.y <= rect.max.y);  \
    return min_contained && max_contained;                                             \
  }

#define _LM2_IMPL_RECT2_DISTANCE(type_name, vec_type, scalar_type, suffix)   \
  LM2_API scalar_type type_name##_distance(type_name rect, vec_type point) { \
    vec_type closest = type_name##_get_closest_point(rect, point);           \
    return vec_type##_distance(point, closest);                              \
  }

#define _LM2_IMPL_RECT2_GET_CLOSEST_POINT(type_name, vec_type, scalar_type, suffix) \
  LM2_API vec_type type_name##_get_closest_point(type_name rect, vec_type point) {  \
    vec_type result;                                                                \
    result.x = lm2_clamp_##suffix(point.x, rect.min.x, rect.max.x);                 \
    result.y = lm2_clamp_##suffix(point.y, rect.min.y, rect.max.y);                 \
    return result;                                                                  \
  }

#define _LM2_IMPL_RECT2_CLOSEST_DISTANCE_FROM_EDGES(type_name, vec_type, scalar_type, suffix)       \
  LM2_API scalar_type type_name##_closest_distance_from_edges(type_name a, type_name b) {           \
    if (type_name##_overlaps(a, b)) {                                                               \
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

#define _LM2_IMPL_RECT2_SEGMENTS_INTERSECT(vec_type, scalar_type, suffix)                                                      \
  LM2_API int lm2_segments_intersect_##vec_type(vec_type a0, vec_type a1, vec_type b0, vec_type b1) {                          \
    scalar_type d1_x = lm2_sub_##suffix(a1.x, a0.x);                                                                           \
    scalar_type d1_y = lm2_sub_##suffix(a1.y, a0.y);                                                                           \
    scalar_type d2_x = lm2_sub_##suffix(b1.x, b0.x);                                                                           \
    scalar_type d2_y = lm2_sub_##suffix(b1.y, b0.y);                                                                           \
    scalar_type cross = lm2_sub_##suffix(lm2_mul_##suffix(d1_x, d2_y), lm2_mul_##suffix(d1_y, d2_x));                          \
    scalar_type epsilon = (scalar_type)0.0001;                                                                                 \
    if (lm2_abs_##suffix(cross) < epsilon) {                                                                                   \
      return 0;                                                                                                                \
    }                                                                                                                          \
    scalar_type diff_x = lm2_sub_##suffix(b0.x, a0.x);                                                                         \
    scalar_type diff_y = lm2_sub_##suffix(b0.y, a0.y);                                                                         \
    scalar_type t = lm2_div_##suffix(lm2_sub_##suffix(lm2_mul_##suffix(diff_x, d2_y), lm2_mul_##suffix(diff_y, d2_x)), cross); \
    scalar_type u = lm2_div_##suffix(lm2_sub_##suffix(lm2_mul_##suffix(diff_x, d1_y), lm2_mul_##suffix(diff_y, d1_x)), cross); \
    return (t >= (scalar_type)0 && t <= (scalar_type)1 && u >= (scalar_type)0 && u <= (scalar_type)1);                         \
  }

// =============================================================================
// Rectangle Cut Implementation Macros
// =============================================================================

#define _LM2_IMPL_RECT2_CUT(type_name, vec_type, scalar_type, suffix)                             \
  LM2_API type_name type_name##_cut(type_name* rect, lm2_rect_cut cut_type, scalar_type amount) { \
    LM2_ASSERT(rect != NULL);                                                                     \
    switch (cut_type) {                                                                           \
      case LM2_RECT_CUT_LEFT:   return type_name##_cut_left(rect, amount);                        \
      case LM2_RECT_CUT_RIGHT:  return type_name##_cut_right(rect, amount);                       \
      case LM2_RECT_CUT_TOP:    return type_name##_cut_top(rect, amount);                         \
      case LM2_RECT_CUT_BOTTOM: return type_name##_cut_bottom(rect, amount);                      \
      default:                  {                                                                 \
        type_name zero = type_name##_zero();                                                      \
        return zero;                                                                              \
      }                                                                                           \
    }                                                                                             \
  }

#define _LM2_IMPL_RECT2_CUT_LEFT(type_name, vec_type, scalar_type, suffix)      \
  LM2_API type_name type_name##_cut_left(type_name* rect, scalar_type amount) { \
    LM2_ASSERT(rect != NULL);                                                   \
    type_name result;                                                           \
    result.min = rect->min;                                                     \
    result.max.x = lm2_add_##suffix(rect->min.x, amount);                       \
    result.max.y = rect->max.y;                                                 \
    rect->min.x = lm2_add_##suffix(rect->min.x, amount);                        \
    return result;                                                              \
  }

#define _LM2_IMPL_RECT2_CUT_RIGHT(type_name, vec_type, scalar_type, suffix)      \
  LM2_API type_name type_name##_cut_right(type_name* rect, scalar_type amount) { \
    LM2_ASSERT(rect != NULL);                                                    \
    type_name result;                                                            \
    result.min.x = lm2_sub_##suffix(rect->max.x, amount);                        \
    result.min.y = rect->min.y;                                                  \
    result.max = rect->max;                                                      \
    rect->max.x = lm2_sub_##suffix(rect->max.x, amount);                         \
    return result;                                                               \
  }

#define _LM2_IMPL_RECT2_CUT_BOTTOM(type_name, vec_type, scalar_type, suffix)      \
  LM2_API type_name type_name##_cut_bottom(type_name* rect, scalar_type amount) { \
    LM2_ASSERT(rect != NULL);                                                     \
    type_name result;                                                             \
    result.min = rect->min;                                                       \
    result.max.x = rect->max.x;                                                   \
    result.max.y = lm2_add_##suffix(rect->min.y, amount);                         \
    rect->min.y = lm2_add_##suffix(rect->min.y, amount);                          \
    return result;                                                                \
  }

#define _LM2_IMPL_RECT2_CUT_TOP(type_name, vec_type, scalar_type, suffix)      \
  LM2_API type_name type_name##_cut_top(type_name* rect, scalar_type amount) { \
    LM2_ASSERT(rect != NULL);                                                  \
    type_name result;                                                          \
    result.min.x = rect->min.x;                                                \
    result.min.y = lm2_sub_##suffix(rect->max.y, amount);                      \
    result.max = rect->max;                                                    \
    rect->max.y = lm2_sub_##suffix(rect->max.y, amount);                       \
    return result;                                                             \
  }

// =============================================================================
// Rectangle Alignment Implementation Macros
// =============================================================================

#define _LM2_IMPL_RECT2_ALIGN_SUBRECT(type_name, vec_type, scalar_type, suffix)                                          \
  LM2_API type_name type_name##_align_subrect(type_name rect, type_name subrect, lm2_align align_x, lm2_align align_y) { \
    vec_type rect_size = type_name##_size(rect);                                                                         \
    vec_type sub_size = type_name##_size(subrect);                                                                       \
    type_name result = subrect;                                                                                          \
    scalar_type two = (scalar_type)2;                                                                                    \
    switch (align_x) {                                                                                                   \
      case LM2_ALIGN_START:                                                                                              \
        result.min.x = rect.min.x;                                                                                       \
        result.max.x = lm2_add_##suffix(rect.min.x, sub_size.x);                                                         \
        break;                                                                                                           \
      case LM2_ALIGN_CENTER: {                                                                                           \
        scalar_type offset = lm2_div_##suffix(lm2_sub_##suffix(rect_size.x, sub_size.x), two);                           \
        result.min.x = lm2_add_##suffix(rect.min.x, offset);                                                             \
        result.max.x = lm2_add_##suffix(result.min.x, sub_size.x);                                                       \
        break;                                                                                                           \
      }                                                                                                                  \
      case LM2_ALIGN_END:                                                                                                \
        result.max.x = rect.max.x;                                                                                       \
        result.min.x = lm2_sub_##suffix(rect.max.x, sub_size.x);                                                         \
        break;                                                                                                           \
    }                                                                                                                    \
    switch (align_y) {                                                                                                   \
      case LM2_ALIGN_START:                                                                                              \
        result.min.y = rect.min.y;                                                                                       \
        result.max.y = lm2_add_##suffix(rect.min.y, sub_size.y);                                                         \
        break;                                                                                                           \
      case LM2_ALIGN_CENTER: {                                                                                           \
        scalar_type offset = lm2_div_##suffix(lm2_sub_##suffix(rect_size.y, sub_size.y), two);                           \
        result.min.y = lm2_add_##suffix(rect.min.y, offset);                                                             \
        result.max.y = lm2_add_##suffix(result.min.y, sub_size.y);                                                       \
        break;                                                                                                           \
      }                                                                                                                  \
      case LM2_ALIGN_END:                                                                                                \
        result.max.y = rect.max.y;                                                                                       \
        result.min.y = lm2_sub_##suffix(rect.max.y, sub_size.y);                                                         \
        break;                                                                                                           \
    }                                                                                                                    \
    return result;                                                                                                       \
  }

// =============================================================================
// Complete Rectangle Implementation for One Type
// =============================================================================

#define _LM2_IMPL_RECT2_ALL(type_name, vec_type, scalar_type, suffix)                   \
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

// =============================================================================
// Rectangle Implementations for All 10 Types
// =============================================================================

_LM2_IMPL_RECT2_ALL(lm2_r2f64, lm2_v2f64, double, f64)
_LM2_IMPL_RECT2_ALL(lm2_r2f32, lm2_v2f32, float, f32)
_LM2_IMPL_RECT2_ALL(lm2_r2i64, lm2_v2i64, int64_t, i64)
_LM2_IMPL_RECT2_ALL(lm2_r2i32, lm2_v2i32, int32_t, i32)
_LM2_IMPL_RECT2_ALL(lm2_r2i16, lm2_v2i16, int16_t, i16)
_LM2_IMPL_RECT2_ALL(lm2_r2i8, lm2_v2i8, int8_t, i8)
_LM2_IMPL_RECT2_ALL(lm2_r2u64, lm2_v2u64, uint64_t, u64)
_LM2_IMPL_RECT2_ALL(lm2_r2u32, lm2_v2u32, uint32_t, u32)
_LM2_IMPL_RECT2_ALL(lm2_r2u16, lm2_v2u16, uint16_t, u16)
_LM2_IMPL_RECT2_ALL(lm2_r2u8, lm2_v2u8, uint8_t, u8)

// Segments intersect implementations for all vector types
_LM2_IMPL_RECT2_SEGMENTS_INTERSECT(lm2_v2f64, double, f64)
_LM2_IMPL_RECT2_SEGMENTS_INTERSECT(lm2_v2f32, float, f32)
_LM2_IMPL_RECT2_SEGMENTS_INTERSECT(lm2_v2i64, int64_t, i64)
_LM2_IMPL_RECT2_SEGMENTS_INTERSECT(lm2_v2i32, int32_t, i32)
_LM2_IMPL_RECT2_SEGMENTS_INTERSECT(lm2_v2i16, int16_t, i16)
_LM2_IMPL_RECT2_SEGMENTS_INTERSECT(lm2_v2i8, int8_t, i8)
_LM2_IMPL_RECT2_SEGMENTS_INTERSECT(lm2_v2u64, uint64_t, u64)
_LM2_IMPL_RECT2_SEGMENTS_INTERSECT(lm2_v2u32, uint32_t, u32)
_LM2_IMPL_RECT2_SEGMENTS_INTERSECT(lm2_v2u16, uint16_t, u16)
_LM2_IMPL_RECT2_SEGMENTS_INTERSECT(lm2_v2u8, uint8_t, u8)
