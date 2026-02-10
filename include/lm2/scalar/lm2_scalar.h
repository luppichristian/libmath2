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

#include "lm2/scalar/lm2_safe_ops.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// Floor
LM2_API double lm2_floor_f64(double a);
LM2_API float lm2_floor_f32(float a);
LM2_API double lm2_floor_multiple_f64(double a, double multiple);
LM2_API float lm2_floor_multiple_f32(float a, float multiple);

// Ceil
LM2_API double lm2_ceil_f64(double a);
LM2_API float lm2_ceil_f32(float a);
LM2_API double lm2_ceil_multiple_f64(double a, double multiple);
LM2_API float lm2_ceil_multiple_f32(float a, float multiple);

// Round
LM2_API double lm2_round_f64(double a);
LM2_API float lm2_round_f32(float a);
LM2_API double lm2_round_multiple_f64(double a, double multiple);
LM2_API float lm2_round_multiple_f32(float a, float multiple);

// Truncate
LM2_API double lm2_trunc_f64(double a);
LM2_API float lm2_trunc_f32(float a);
LM2_API double lm2_trunc_multiple_f64(double a, double multiple);
LM2_API float lm2_trunc_multiple_f32(float a, float multiple);

// Abs
LM2_API double lm2_abs_f64(double a);
LM2_API float lm2_abs_f32(float a);
LM2_API int64_t lm2_abs_i64(int64_t a);
LM2_API int32_t lm2_abs_i32(int32_t a);
LM2_API int16_t lm2_abs_i16(int16_t a);
LM2_API int8_t lm2_abs_i8(int8_t a);

// Sign (returns 1 or -1)
LM2_API double lm2_sign_f64(double a);
LM2_API float lm2_sign_f32(float a);
LM2_API int64_t lm2_sign_i64(int64_t a);
LM2_API int32_t lm2_sign_i32(int32_t a);
LM2_API int16_t lm2_sign_i16(int16_t a);
LM2_API int8_t lm2_sign_i8(int8_t a);

// Sign0 (returns 1, -1, or 0)
LM2_API double lm2_sign0_f64(double a);
LM2_API float lm2_sign0_f32(float a);
LM2_API int64_t lm2_sign0_i64(int64_t a);
LM2_API int32_t lm2_sign0_i32(int32_t a);
LM2_API int16_t lm2_sign0_i16(int16_t a);
LM2_API int8_t lm2_sign0_i8(int8_t a);

// Min
LM2_API double lm2_min_f64(double a, double b);
LM2_API float lm2_min_f32(float a, float b);
LM2_API int64_t lm2_min_i64(int64_t a, int64_t b);
LM2_API int32_t lm2_min_i32(int32_t a, int32_t b);
LM2_API int16_t lm2_min_i16(int16_t a, int16_t b);
LM2_API int8_t lm2_min_i8(int8_t a, int8_t b);
LM2_API uint64_t lm2_min_u64(uint64_t a, uint64_t b);
LM2_API uint32_t lm2_min_u32(uint32_t a, uint32_t b);
LM2_API uint16_t lm2_min_u16(uint16_t a, uint16_t b);
LM2_API uint8_t lm2_min_u8(uint8_t a, uint8_t b);

// Min Abs
LM2_API double lm2_min_abs_f64(double a, double b);
LM2_API float lm2_min_abs_f32(float a, float b);
LM2_API int64_t lm2_min_abs_i64(int64_t a, int64_t b);
LM2_API int32_t lm2_min_abs_i32(int32_t a, int32_t b);
LM2_API int16_t lm2_min_abs_i16(int16_t a, int16_t b);
LM2_API int8_t lm2_min_abs_i8(int8_t a, int8_t b);

// Max
LM2_API double lm2_max_f64(double a, double b);
LM2_API float lm2_max_f32(float a, float b);
LM2_API int64_t lm2_max_i64(int64_t a, int64_t b);
LM2_API int32_t lm2_max_i32(int32_t a, int32_t b);
LM2_API int16_t lm2_max_i16(int16_t a, int16_t b);
LM2_API int8_t lm2_max_i8(int8_t a, int8_t b);
LM2_API uint64_t lm2_max_u64(uint64_t a, uint64_t b);
LM2_API uint32_t lm2_max_u32(uint32_t a, uint32_t b);
LM2_API uint16_t lm2_max_u16(uint16_t a, uint16_t b);
LM2_API uint8_t lm2_max_u8(uint8_t a, uint8_t b);

// Max absolute
LM2_API double lm2_max_abs_f64(double a, double b);
LM2_API float lm2_max_abs_f32(float a, float b);
LM2_API int64_t lm2_max_abs_i64(int64_t a, int64_t b);
LM2_API int32_t lm2_max_abs_i32(int32_t a, int32_t b);
LM2_API int16_t lm2_max_abs_i16(int16_t a, int16_t b);
LM2_API int8_t lm2_max_abs_i8(int8_t a, int8_t b);

// Clamp
LM2_API double lm2_clamp_f64(double min, double value, double max);
LM2_API float lm2_clamp_f32(float min, float value, float max);
LM2_API int64_t lm2_clamp_i64(int64_t min, int64_t value, int64_t max);
LM2_API int32_t lm2_clamp_i32(int32_t min, int32_t value, int32_t max);
LM2_API int16_t lm2_clamp_i16(int16_t min, int16_t value, int16_t max);
LM2_API int8_t lm2_clamp_i8(int8_t min, int8_t value, int8_t max);
LM2_API uint64_t lm2_clamp_u64(uint64_t min, uint64_t value, uint64_t max);
LM2_API uint32_t lm2_clamp_u32(uint32_t min, uint32_t value, uint32_t max);
LM2_API uint16_t lm2_clamp_u16(uint16_t min, uint16_t value, uint16_t max);
LM2_API uint8_t lm2_clamp_u8(uint8_t min, uint8_t value, uint8_t max);

// Saturate to [0, 1]
LM2_API double lm2_saturate_f64(double value);
LM2_API float lm2_saturate_f32(float value);

// Lerp
LM2_API double lm2_lerp_f64(double a, double t, double b);
LM2_API float lm2_lerp_f32(float a, float t, float b);

// Smoothstep
LM2_API double lm2_smoothstep_f64(double edge0, double x, double edge1);
LM2_API float lm2_smoothstep_f32(float edge0, float x, float edge1);

// Alpha
LM2_API double lm2_alpha_f64(double a, double value, double b);
LM2_API float lm2_alpha_f32(float a, float value, float b);

// Fract
LM2_API double lm2_fract_f64(double a);
LM2_API float lm2_fract_f32(float a);

// Power
LM2_API double lm2_pow_f64(double base, double exponent);
LM2_API float lm2_pow_f32(float base, float exponent);

// Square root
LM2_API double lm2_sqrt_f64(double a);
LM2_API float lm2_sqrt_f32(float a);

// #############################################################################
LM2_HEADER_END;
// #############################################################################