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
//   lm2_r2_f32 r = {{0, 0}, {10, 10}};
//   lm2_v2_f32 offset = {5, 5};
//   lm2_r2_f32 translated = r + offset;  // translate range
//   lm2_r2_f32 scaled = r * 2.0f;        // scale around center
//   lm2_v2_f32 min = r[0];                   // array access to min/max

// =============================================================================
// Range2 Operators
// =============================================================================

#  define _LM2_DEFINE_RANGE2_OPERATORS(type_name, suffix, vec_type) \
    inline type_name operator+(type_name r, vec_type offset) {      \
      return lm2_r2_translate_##suffix(r, offset);                  \
    }                                                               \
    inline type_name operator-(type_name r, vec_type offset) {      \
      return lm2_r2_sub_v_##suffix(r, offset);                      \
    }                                                               \
    inline type_name operator*(type_name r, type_name b) {          \
      return lm2_r2_mul_##suffix(r, b);                             \
    }                                                               \
    inline type_name operator/(type_name r, type_name b) {          \
      return lm2_r2_div_##suffix(r, b);                             \
    }                                                               \
    inline type_name operator|(type_name a, type_name b) {          \
      return lm2_r2_union_##suffix(a, b);                           \
    }                                                               \
    inline type_name operator&(type_name a, type_name b) {          \
      return lm2_r2_intersection_##suffix(a, b);                    \
    }

// =============================================================================
// Range3 Operators
// =============================================================================

#  define _LM2_DEFINE_RANGE3_OPERATORS(type_name, suffix, vec_type) \
    inline type_name operator+(type_name r, vec_type offset) {      \
      return lm2_r3_translate_##suffix(r, offset);                  \
    }                                                               \
    inline type_name operator-(type_name r, vec_type offset) {      \
      return lm2_r3_sub_v_##suffix(r, offset);                      \
    }                                                               \
    inline type_name operator*(type_name r, type_name b) {          \
      return lm2_r3_mul_##suffix(r, b);                             \
    }                                                               \
    inline type_name operator/(type_name r, type_name b) {          \
      return lm2_r3_div_##suffix(r, b);                             \
    }                                                               \
    inline type_name operator|(type_name a, type_name b) {          \
      return lm2_r3_union_##suffix(a, b);                           \
    }                                                               \
    inline type_name operator&(type_name a, type_name b) {          \
      return lm2_r3_intersection_##suffix(a, b);                    \
    }

// =============================================================================
// Range4 Operators
// =============================================================================

#  define _LM2_DEFINE_RANGE4_OPERATORS(type_name, suffix, vec_type) \
    inline type_name operator+(type_name r, vec_type offset) {      \
      return lm2_r4_translate_##suffix(r, offset);                  \
    }                                                               \
    inline type_name operator-(type_name r, vec_type offset) {      \
      return lm2_r4_sub_v_##suffix(r, offset);                      \
    }                                                               \
    inline type_name operator*(type_name r, type_name b) {          \
      return lm2_r4_mul_##suffix(r, b);                             \
    }                                                               \
    inline type_name operator/(type_name r, type_name b) {          \
      return lm2_r4_div_##suffix(r, b);                             \
    }                                                               \
    inline type_name operator|(type_name a, type_name b) {          \
      return lm2_r4_union_##suffix(a, b);                           \
    }                                                               \
    inline type_name operator&(type_name a, type_name b) {          \
      return lm2_r4_intersection_##suffix(a, b);                    \
    }

#else

#  define _LM2_DEFINE_RANGE2_OPERATORS(type_name, suffix, vec_type)
#  define _LM2_DEFINE_RANGE3_OPERATORS(type_name, suffix, vec_type)
#  define _LM2_DEFINE_RANGE4_OPERATORS(type_name, suffix, vec_type)
#  define _LM2_DEFINE_RANGE2_CONSTRUCTORS(type_name, suffix, vec_type)
#  define _LM2_DEFINE_RANGE3_CONSTRUCTORS(type_name, suffix, vec_type)
#  define _LM2_DEFINE_RANGE4_CONSTRUCTORS(type_name, suffix, vec_type)

#endif
