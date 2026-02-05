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

#include "libmath2/libmath2_generic.h"
#include "libmath2_base.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

#define _LM2_DEFINE_SAFE_OP(name)                      \
  LM2_API double name##_f64(double a, double b);       \
  LM2_API float name##_f32(float a, float b);          \
  LM2_API int64_t name##_i64(int64_t a, int64_t b);    \
  LM2_API int32_t name##_i32(int32_t a, int32_t b);    \
  LM2_API int16_t name##_i16(int16_t a, int16_t b);    \
  LM2_API int8_t name##_i8(int8_t a, int8_t b);        \
  LM2_API uint64_t name##_u64(uint64_t a, uint64_t b); \
  LM2_API uint32_t name##_u32(uint32_t a, uint32_t b); \
  LM2_API uint16_t name##_u16(uint16_t a, uint16_t b); \
  LM2_API uint8_t name##_u8(uint8_t a, uint8_t b);

// Safe addition for numeric types
// Returns the sum of a and b, or handles overflow/underflow appropriately
// LM2_ASSERTS will be triggered on overflow/underflow conditions
_LM2_DEFINE_SAFE_OP(lm2_add);

// Safe subtraction for numeric types
// Returns the difference of a and b, or handles overflow/underflow appropriately
// LM2_ASSERTS will be triggered on overflow/underflow conditions
_LM2_DEFINE_SAFE_OP(lm2_sub);

// Safe multiplication for numeric types
// Returns the product of a and b, or handles overflow/underflow appropriately
// LM2_ASSERTS will be triggered on overflow/underflow conditions
_LM2_DEFINE_SAFE_OP(lm2_mul);

// Safe division for numeric types
// Returns the quotient of a and b, or handles division by zero appropriately
// LM2_ASSERTS will be triggered on division by zero conditions
_LM2_DEFINE_SAFE_OP(lm2_div);

// Generics
#ifndef LM2_NO_GENERICS
#  define lm2_add(...) _LM2_GENERIC(lm2_add, __VA_ARGS__)
#  define lm2_sub(...) _LM2_GENERIC(lm2_sub, __VA_ARGS__)
#  define lm2_mul(...) _LM2_GENERIC(lm2_mul, __VA_ARGS__)
#  define lm2_div(...) _LM2_GENERIC(lm2_div, __VA_ARGS__)
#endif

#undef _LM2_DEFINE_SAFE_OP

// #############################################################################
LM2_HEADER_END;
// #############################################################################