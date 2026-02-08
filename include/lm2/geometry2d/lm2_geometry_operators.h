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

#if defined(__cplusplus) && !defined(LM2_NO_CPP_OPERATORS)

// =============================================================================
// C++ Operator Overloads for Geometry Types
// =============================================================================
// These operators provide natural syntax for geometry operations in C++:
//   lm2_circle_f32 c = {{5, 5}, 10};
//   lm2_v2f32 offset = {2, 3};
//   lm2_circle_f32 moved = c + offset;     // translate circle
//   lm2_circle_f32 scaled = c * 2.0f;      // scale radius

// =============================================================================
// Capsule Operators
// =============================================================================

#  define _LM2_DEFINE_CAPSULE_OPERATORS(type_name, suffix, vec_type, scalar_type)  \
    inline type_name operator+(type_name capsule, vec_type offset) {               \
      return lm2_capsule2_translate_##suffix(capsule, offset);                     \
    }                                                                              \
    inline type_name operator-(type_name capsule, vec_type offset) {               \
      return lm2_capsule2_translate_##suffix(capsule, lm2_neg_##vec_type(offset)); \
    }                                                                              \
    inline type_name operator*(type_name capsule, scalar_type scale) {             \
      return lm2_capsule2_scale_radius_##suffix(capsule, scale);                   \
    }

// =============================================================================
// Circle Operators
// =============================================================================

#  define _LM2_DEFINE_CIRCLE_OPERATORS(type_name, suffix, vec_type, scalar_type) \
    inline type_name operator+(type_name circle, vec_type offset) {              \
      return lm2_circle_translate_##suffix(circle, offset);                      \
    }                                                                            \
    inline type_name operator-(type_name circle, vec_type offset) {              \
      return lm2_circle_translate_##suffix(circle, lm2_neg_##vec_type(offset));  \
    }                                                                            \
    inline type_name operator*(type_name circle, scalar_type scale) {            \
      return lm2_circle_scale_##suffix(circle, scale);                           \
    }

// =============================================================================
// Edge Operators
// =============================================================================

#  define _LM2_DEFINE_EDGE_OPERATORS(type_name, vec_type, scalar_type) \
    inline type_name operator+(type_name edge, vec_type offset) {      \
      return type_name {                                               \
          lm2_add_##vec_type(edge.start, offset),                      \
          lm2_add_##vec_type(edge.end, offset)};                       \
    }                                                                  \
    inline type_name operator-(type_name edge, vec_type offset) {      \
      return type_name {                                               \
          lm2_sub_##vec_type(edge.start, offset),                      \
          lm2_sub_##vec_type(edge.end, offset)};                       \
    }

// =============================================================================
// Triangle Operators
// =============================================================================
// Note: Triangles are defined as arrays, so we provide helper functions
// wrapped as operators for consistency

#  define _LM2_DEFINE_TRIANGLE_OPERATORS(triangle_type, vec_type, scalar_type)               \
    inline void lm2_triangle_translate_##triangle_type(triangle_type tri, vec_type offset) { \
      tri[0] = lm2_add_##vec_type(tri[0], offset);                                           \
      tri[1] = lm2_add_##vec_type(tri[1], offset);                                           \
      tri[2] = lm2_add_##vec_type(tri[2], offset);                                           \
    }

// =============================================================================
// Polygon Operators
// =============================================================================
// Note: Polygons use caller-managed memory, so we provide in-place modification
// functions for translation and scaling operations

#  define _LM2_DEFINE_POLYGON_OPERATORS(type_name, vec_type, scalar_type)                       \
    inline void type_name##_translate_inplace(type_name polygon, vec_type offset) {             \
      for (size_t i = 0; i < polygon.vertex_count; ++i) {                                       \
        polygon.vertices[i] = lm2_add_##vec_type(polygon.vertices[i], offset);                  \
      }                                                                                         \
    }                                                                                           \
    inline void type_name##_scale_inplace(type_name polygon, vec_type center, vec_type scale) { \
      for (size_t i = 0; i < polygon.vertex_count; ++i) {                                       \
        vec_type relative = lm2_sub_##vec_type(polygon.vertices[i], center);                    \
        relative = lm2_mul_##vec_type(relative, scale);                                         \
        polygon.vertices[i] = lm2_add_##vec_type(center, relative);                             \
      }                                                                                         \
    }

// =============================================================================
// Plane Operators
// =============================================================================

#  define _LM2_DEFINE_PLANE2_OPERATORS(type_name, suffix, vec_type, scalar_type) \
    inline type_name operator+(type_name plane, vec_type offset) {               \
      return lm2_plane2_translate_##suffix(plane, offset);                       \
    }                                                                            \
    inline type_name operator-(type_name plane, vec_type offset) {               \
      return lm2_plane2_translate_##suffix(plane, lm2_neg_##vec_type(offset));   \
    }

// =============================================================================
// Ray Operators
// =============================================================================

#  define _LM2_DEFINE_RAY2_OPERATORS(type_name, vec_type, scalar_type) \
    inline type_name operator+(type_name ray, vec_type offset) {       \
      return type_name {lm2_add_##vec_type(ray.origin, offset),        \
                        ray.direction,                                 \
                        ray.t_max};                                    \
    }                                                                  \
    inline type_name operator-(type_name ray, vec_type offset) {       \
      return type_name {lm2_sub_##vec_type(ray.origin, offset),        \
                        ray.direction,                                 \
                        ray.t_max};                                    \
    }

#else

#  define _LM2_DEFINE_CAPSULE_OPERATORS(type_name, suffix, vec_type, scalar_type)
#  define _LM2_DEFINE_CIRCLE_OPERATORS(type_name, suffix, vec_type, scalar_type)
#  define _LM2_DEFINE_EDGE_OPERATORS(type_name, vec_type, scalar_type)
#  define _LM2_DEFINE_TRIANGLE_OPERATORS(triangle_type, vec_type, scalar_type)
#  define _LM2_DEFINE_POLYGON_OPERATORS(type_name, vec_type, scalar_type)
#  define _LM2_DEFINE_PLANE2_OPERATORS(type_name, suffix, vec_type, scalar_type)
#  define _LM2_DEFINE_RAY2_OPERATORS(type_name, vec_type, scalar_type)

#endif
