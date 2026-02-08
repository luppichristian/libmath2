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
// C++ Operator Overloads for Range Types
// =============================================================================
// These operators provide natural syntax for range operations in C++:
//   lm2_r2f32 r = {{0, 0}, {10, 10}};
//   lm2_v2f32 offset = {5, 5};
//   lm2_r2f32 translated = r + offset;  // translate range
//   lm2_r2f32 scaled = r * 2.0f;        // scale around center
//   lm2_v2f32 min = r[0];                   // array access to min/max

// =============================================================================
// Range2 Operators
// =============================================================================

#  define _LM2_DEFINE_RANGE2_OPERATORS(type_name, vec_type)    \
    inline type_name operator+(type_name r, vec_type offset) { \
      return type_name##_translate(r, offset);                 \
    }                                                          \
    inline type_name operator-(type_name r, vec_type offset) { \
      return type_name##_sub_vec(r, offset);                   \
    }                                                          \
    inline type_name operator*(type_name r, type_name b) {     \
      return type_name##_mul(r, b);                            \
    }                                                          \
    inline type_name operator/(type_name r, type_name b) {     \
      return type_name##_div(r, b);                            \
    }                                                          \
    inline type_name operator|(type_name a, type_name b) {     \
      return type_name##_union(a, b);                          \
    }                                                          \
    inline type_name operator&(type_name a, type_name b) {     \
      return type_name##_intersection(a, b);                   \
    }

// =============================================================================
// Range3 Operators
// =============================================================================

#  define _LM2_DEFINE_RANGE3_OPERATORS(type_name, vec_type)    \
    inline type_name operator+(type_name r, vec_type offset) { \
      return type_name##_translate(r, offset);                 \
    }                                                          \
    inline type_name operator-(type_name r, vec_type offset) { \
      return type_name##_sub_vec(r, offset);                   \
    }                                                          \
    inline type_name operator*(type_name r, type_name b) {     \
      return type_name##_mul(r, b);                            \
    }                                                          \
    inline type_name operator/(type_name r, type_name b) {     \
      return type_name##_div(r, b);                            \
    }                                                          \
    inline type_name operator|(type_name a, type_name b) {     \
      return type_name##_union(a, b);                          \
    }                                                          \
    inline type_name operator&(type_name a, type_name b) {     \
      return type_name##_intersection(a, b);                   \
    }

// =============================================================================
// Range4 Operators
// =============================================================================

#  define _LM2_DEFINE_RANGE4_OPERATORS(type_name, vec_type)    \
    inline type_name operator+(type_name r, vec_type offset) { \
      return type_name##_translate(r, offset);                 \
    }                                                          \
    inline type_name operator-(type_name r, vec_type offset) { \
      return type_name##_sub_vec(r, offset);                   \
    }                                                          \
    inline type_name operator*(type_name r, type_name b) {     \
      return type_name##_mul(r, b);                            \
    }                                                          \
    inline type_name operator/(type_name r, type_name b) {     \
      return type_name##_div(r, b);                            \
    }                                                          \
    inline type_name operator|(type_name a, type_name b) {     \
      return type_name##_union(a, b);                          \
    }                                                          \
    inline type_name operator&(type_name a, type_name b) {     \
      return type_name##_intersection(a, b);                   \
    }

#else

#  define _LM2_DEFINE_RANGE2_OPERATORS(type_name, vec_type)
#  define _LM2_DEFINE_RANGE3_OPERATORS(type_name, vec_type)
#  define _LM2_DEFINE_RANGE4_OPERATORS(type_name, vec_type)
#  define _LM2_DEFINE_RANGE2_CONSTRUCTORS(type_name, vec_type)
#  define _LM2_DEFINE_RANGE3_CONSTRUCTORS(type_name, vec_type)
#  define _LM2_DEFINE_RANGE4_CONSTRUCTORS(type_name, vec_type)

#endif
