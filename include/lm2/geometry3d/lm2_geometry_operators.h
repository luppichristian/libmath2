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
// C++ Operator Overloads for 3D Geometry Types
// =============================================================================
// These operators provide natural syntax for geometry operations in C++:
//   lm2_sphere_f32 s = {{5, 5, 5}, 10};
//   lm2_v3_f32 offset = {2, 3, 1};
//   lm2_sphere_f32 moved = s + offset;     // translate sphere
//   lm2_sphere_f32 scaled = s * 2.0f;      // scale radius

// =============================================================================
// Capsule Operators
// =============================================================================

#  define _LM2_DEFINE_CAPSULE3_OPERATORS(type_name, suffix, vec_base, scalar_type)           \
    extern "C++" inline type_name operator+(type_name capsule, vec_base##_##suffix offset) { \
      return lm2_capsule3_translate_##suffix(capsule, offset);                               \
    }                                                                                        \
    extern "C++" inline type_name operator-(type_name capsule, vec_base##_##suffix offset) { \
      return lm2_capsule3_translate_##suffix(capsule, vec_base##_neg_##suffix(offset));      \
    }                                                                                        \
    extern "C++" inline type_name operator*(type_name capsule, scalar_type scale) {          \
      return lm2_capsule3_scale_radius_##suffix(capsule, scale);                             \
    }

// =============================================================================
// Sphere Operators
// =============================================================================

#  define _LM2_DEFINE_SPHERE_OPERATORS(type_name, suffix, vec_base, scalar_type)            \
    extern "C++" inline type_name operator+(type_name sphere, vec_base##_##suffix offset) { \
      return lm2_sphere_translate_##suffix(sphere, offset);                                 \
    }                                                                                       \
    extern "C++" inline type_name operator-(type_name sphere, vec_base##_##suffix offset) { \
      return lm2_sphere_translate_##suffix(sphere, vec_base##_neg_##suffix(offset));        \
    }                                                                                       \
    extern "C++" inline type_name operator*(type_name sphere, scalar_type scale) {          \
      return lm2_sphere_scale_##suffix(sphere, scale);                                      \
    }

// =============================================================================
// Edge Operators
// =============================================================================

#  define _LM2_DEFINE_EDGE3_OPERATORS(type_name, suffix, vec_base, scalar_type)           \
    extern "C++" inline type_name operator+(type_name edge, vec_base##_##suffix offset) { \
      return type_name {                                                                  \
          vec_base##_add_##suffix(edge.start, offset),                                    \
          vec_base##_add_##suffix(edge.end, offset)};                                     \
    }                                                                                     \
    extern "C++" inline type_name operator-(type_name edge, vec_base##_##suffix offset) { \
      return type_name {                                                                  \
          vec_base##_sub_##suffix(edge.start, offset),                                    \
          vec_base##_sub_##suffix(edge.end, offset)};                                     \
    }

// =============================================================================
// Triangle Operators
// =============================================================================
// Note: Triangles are defined as arrays, so we provide helper functions
// wrapped as operators for consistency

#  define _LM2_DEFINE_TRIANGLE3_OPERATORS(triangle_type, suffix, vec_base, scalar_type)                  \
    inline void lm2_triangle3_translate_##triangle_type(triangle_type tri, vec_base##_##suffix offset) { \
      tri[0] = vec_base##_add_##suffix(tri[0], offset);                                                  \
      tri[1] = vec_base##_add_##suffix(tri[1], offset);                                                  \
      tri[2] = vec_base##_add_##suffix(tri[2], offset);                                                  \
    }

// =============================================================================
// Plane Operators
// =============================================================================

#  define _LM2_DEFINE_PLANE3_OPERATORS(type_name, suffix, vec_base, scalar_type)           \
    extern "C++" inline type_name operator+(type_name plane, vec_base##_##suffix offset) { \
      return lm2_plane3_translate_##suffix(plane, offset);                                 \
    }                                                                                      \
    extern "C++" inline type_name operator-(type_name plane, vec_base##_##suffix offset) { \
      return lm2_plane3_translate_##suffix(plane, vec_base##_neg_##suffix(offset));        \
    }

// =============================================================================
// Ray Operators
// =============================================================================

#  define _LM2_DEFINE_RAY3_OPERATORS(type_name, suffix, vec_base, scalar_type)           \
    extern "C++" inline type_name operator+(type_name ray, vec_base##_##suffix offset) { \
      return type_name {vec_base##_add_##suffix(ray.origin, offset),                     \
                        ray.direction,                                                   \
                        ray.t_max};                                                      \
    }                                                                                    \
    extern "C++" inline type_name operator-(type_name ray, vec_base##_##suffix offset) { \
      return type_name {vec_base##_sub_##suffix(ray.origin, offset),                     \
                        ray.direction,                                                   \
                        ray.t_max};                                                      \
    }

#else

#  define _LM2_DEFINE_CAPSULE3_OPERATORS(type_name, suffix, vec_base, scalar_type)
#  define _LM2_DEFINE_SPHERE_OPERATORS(type_name, suffix, vec_base, scalar_type)
#  define _LM2_DEFINE_EDGE3_OPERATORS(type_name, suffix, vec_base, scalar_type)
#  define _LM2_DEFINE_TRIANGLE3_OPERATORS(triangle_type, suffix, vec_base, scalar_type)
#  define _LM2_DEFINE_PLANE3_OPERATORS(type_name, suffix, vec_base, scalar_type)
#  define _LM2_DEFINE_RAY3_OPERATORS(type_name, suffix, vec_base, scalar_type)

#endif
