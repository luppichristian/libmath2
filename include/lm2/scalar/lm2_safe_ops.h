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

#include "lm2/lm2_base.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// Safe Addition for Numeric Types
// =============================================================================
// Returns the sum of a and b, or handles overflow/underflow appropriately
// LM2_ASSERTS will be triggered on overflow/underflow conditions

LM2_API double lm2_add_f64(double a, double b);
LM2_API float lm2_add_f32(float a, float b);
LM2_API int64_t lm2_add_i64(int64_t a, int64_t b);
LM2_API int32_t lm2_add_i32(int32_t a, int32_t b);
LM2_API int16_t lm2_add_i16(int16_t a, int16_t b);
LM2_API int8_t lm2_add_i8(int8_t a, int8_t b);
LM2_API uint64_t lm2_add_u64(uint64_t a, uint64_t b);
LM2_API uint32_t lm2_add_u32(uint32_t a, uint32_t b);
LM2_API uint16_t lm2_add_u16(uint16_t a, uint16_t b);
LM2_API uint8_t lm2_add_u8(uint8_t a, uint8_t b);

// =============================================================================
// Safe Subtraction for Numeric Types
// =============================================================================
// Returns the difference of a and b, or handles overflow/underflow appropriately
// LM2_ASSERTS will be triggered on overflow/underflow conditions

LM2_API double lm2_sub_f64(double a, double b);
LM2_API float lm2_sub_f32(float a, float b);
LM2_API int64_t lm2_sub_i64(int64_t a, int64_t b);
LM2_API int32_t lm2_sub_i32(int32_t a, int32_t b);
LM2_API int16_t lm2_sub_i16(int16_t a, int16_t b);
LM2_API int8_t lm2_sub_i8(int8_t a, int8_t b);
LM2_API uint64_t lm2_sub_u64(uint64_t a, uint64_t b);
LM2_API uint32_t lm2_sub_u32(uint32_t a, uint32_t b);
LM2_API uint16_t lm2_sub_u16(uint16_t a, uint16_t b);
LM2_API uint8_t lm2_sub_u8(uint8_t a, uint8_t b);

// =============================================================================
// Safe Multiplication for Numeric Types
// =============================================================================
// Returns the product of a and b, or handles overflow/underflow appropriately
// LM2_ASSERTS will be triggered on overflow/underflow conditions

LM2_API double lm2_mul_f64(double a, double b);
LM2_API float lm2_mul_f32(float a, float b);
LM2_API int64_t lm2_mul_i64(int64_t a, int64_t b);
LM2_API int32_t lm2_mul_i32(int32_t a, int32_t b);
LM2_API int16_t lm2_mul_i16(int16_t a, int16_t b);
LM2_API int8_t lm2_mul_i8(int8_t a, int8_t b);
LM2_API uint64_t lm2_mul_u64(uint64_t a, uint64_t b);
LM2_API uint32_t lm2_mul_u32(uint32_t a, uint32_t b);
LM2_API uint16_t lm2_mul_u16(uint16_t a, uint16_t b);
LM2_API uint8_t lm2_mul_u8(uint8_t a, uint8_t b);

// =============================================================================
// Safe Division for Numeric Types
// =============================================================================
// Returns the quotient of a and b, or handles division by zero appropriately
// LM2_ASSERTS will be triggered on division by zero conditions

LM2_API double lm2_div_f64(double a, double b);
LM2_API float lm2_div_f32(float a, float b);
LM2_API int64_t lm2_div_i64(int64_t a, int64_t b);
LM2_API int32_t lm2_div_i32(int32_t a, int32_t b);
LM2_API int16_t lm2_div_i16(int16_t a, int16_t b);
LM2_API int8_t lm2_div_i8(int8_t a, int8_t b);
LM2_API uint64_t lm2_div_u64(uint64_t a, uint64_t b);
LM2_API uint32_t lm2_div_u32(uint32_t a, uint32_t b);
LM2_API uint16_t lm2_div_u16(uint16_t a, uint16_t b);
LM2_API uint8_t lm2_div_u8(uint8_t a, uint8_t b);

// =============================================================================
// Safe Modulo for Integer Types
// =============================================================================

LM2_API double lm2_mod_f64(double a, double b);
LM2_API float lm2_mod_f32(float a, float b);
LM2_API int64_t lm2_mod_i64(int64_t a, int64_t b);
LM2_API int32_t lm2_mod_i32(int32_t a, int32_t b);
LM2_API int16_t lm2_mod_i16(int16_t a, int16_t b);
LM2_API int8_t lm2_mod_i8(int8_t a, int8_t b);
LM2_API uint64_t lm2_mod_u64(uint64_t a, uint64_t b);
LM2_API uint32_t lm2_mod_u32(uint32_t a, uint32_t b);
LM2_API uint16_t lm2_mod_u16(uint16_t a, uint16_t b);
LM2_API uint8_t lm2_mod_u8(uint8_t a, uint8_t b);

// =============================================================================
// Safe Negation for Numeric Types
// =============================================================================

LM2_API double lm2_neg_f64(double a);
LM2_API float lm2_neg_f32(float a);
LM2_API int64_t lm2_neg_i64(int64_t a);
LM2_API int32_t lm2_neg_i32(int32_t a);
LM2_API int16_t lm2_neg_i16(int16_t a);
LM2_API int8_t lm2_neg_i8(int8_t a);

// #############################################################################
LM2_HEADER_END;
// #############################################################################