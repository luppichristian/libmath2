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

#include "libmath2_vector_defines.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// Define a vector type with 2 components and associated operations
#define _LM2_DEFINE_V2(type_name, scalar_type)                                               \
  typedef union type_name {                                                                  \
    scalar_type e[2];                                                                        \
    struct {                                                                                 \
      scalar_type x, y;                                                                      \
    };                                                                                       \
    struct {                                                                                 \
      scalar_type s, t;                                                                      \
    };                                                                                       \
  } type_name;                                                                               \
  _LM2_DECLARE_VECTOR_OP(type_name, lm2_add_##type_name)                                     \
  _LM2_DECLARE_VECTOR_OP(type_name, lm2_sub_##type_name)                                     \
  _LM2_DECLARE_VECTOR_OP(type_name, lm2_mul_##type_name)                                     \
  _LM2_DECLARE_VECTOR_OP(type_name, lm2_div_##type_name)                                     \
  _LM2_DECLARE_VECTOR_OP_SCALAR(type_name, scalar_type, lm2_add_##type_name##_##scalar_type) \
  _LM2_DECLARE_VECTOR_OP_SCALAR(type_name, scalar_type, lm2_sub_##type_name##_##scalar_type) \
  _LM2_DECLARE_VECTOR_OP_SCALAR(type_name, scalar_type, lm2_mul_##type_name##_##scalar_type) \
  _LM2_DECLARE_VECTOR_OP_SCALAR(type_name, scalar_type, lm2_div_##type_name##_##scalar_type)

// 2D vector types
_LM2_DEFINE_V2(lm2_v2f64, double)
_LM2_DEFINE_V2(lm2_v2f32, float)
_LM2_DEFINE_V2(lm2_v2i64, int64_t)
_LM2_DEFINE_V2(lm2_v2i32, int32_t)
_LM2_DEFINE_V2(lm2_v2i16, int16_t)
_LM2_DEFINE_V2(lm2_v2i8, int8_t)
_LM2_DEFINE_V2(lm2_v2u64, uint64_t)
_LM2_DEFINE_V2(lm2_v2u32, uint32_t)
_LM2_DEFINE_V2(lm2_v2u16, uint16_t)
_LM2_DEFINE_V2(lm2_v2u8, uint8_t)

// Default vector type
typedef lm2_v2f32 lm2_v2;

// #############################################################################
LM2_HEADER_END;
// #############################################################################

#ifndef LM2_NO_GENERICS
// Generic V2 vector-vector operations (type-dispatched)
#  define lm2_add_v2(...) _LM2_GENERIC_V2(lm2_add, __VA_ARGS__)
#  define lm2_sub_v2(...) _LM2_GENERIC_V2(lm2_sub, __VA_ARGS__)
#  define lm2_mul_v2(...) _LM2_GENERIC_V2(lm2_mul, __VA_ARGS__)
#  define lm2_div_v2(...) _LM2_GENERIC_V2(lm2_div, __VA_ARGS__)

// Generic V2 vector-scalar operations (type-dispatched)
#  define lm2_add_v2_s(...) _LM2_GENERIC_V2_SCALAR(lm2_add, __VA_ARGS__)
#  define lm2_sub_v2_s(...) _LM2_GENERIC_V2_SCALAR(lm2_sub, __VA_ARGS__)
#  define lm2_mul_v2_s(...) _LM2_GENERIC_V2_SCALAR(lm2_mul, __VA_ARGS__)
#  define lm2_div_v2_s(...) _LM2_GENERIC_V2_SCALAR(lm2_div, __VA_ARGS__)
#endif