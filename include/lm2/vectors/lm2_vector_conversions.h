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

#include "lm2/vectors/lm2_vector2.h"
#include "lm2/vectors/lm2_vector3.h"
#include "lm2/vectors/lm2_vector4.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// Vector2 Conversions
// =============================================================================

// From f64
LM2_API lm2_v2_f32 lm2_v2_f64_to_f32(lm2_v2_f64 v);
LM2_API lm2_v2_i64 lm2_v2_f64_to_i64(lm2_v2_f64 v);
LM2_API lm2_v2_i32 lm2_v2_f64_to_i32(lm2_v2_f64 v);
LM2_API lm2_v2_i16 lm2_v2_f64_to_i16(lm2_v2_f64 v);
LM2_API lm2_v2_i8 lm2_v2_f64_to_i8(lm2_v2_f64 v);
LM2_API lm2_v2_u64 lm2_v2_f64_to_u64(lm2_v2_f64 v);
LM2_API lm2_v2_u32 lm2_v2_f64_to_u32(lm2_v2_f64 v);
LM2_API lm2_v2_u16 lm2_v2_f64_to_u16(lm2_v2_f64 v);
LM2_API lm2_v2_u8 lm2_v2_f64_to_u8(lm2_v2_f64 v);

// From f32
LM2_API lm2_v2_f64 lm2_v2_f32_to_f64(lm2_v2_f32 v);
LM2_API lm2_v2_i64 lm2_v2_f32_to_i64(lm2_v2_f32 v);
LM2_API lm2_v2_i32 lm2_v2_f32_to_i32(lm2_v2_f32 v);
LM2_API lm2_v2_i16 lm2_v2_f32_to_i16(lm2_v2_f32 v);
LM2_API lm2_v2_i8 lm2_v2_f32_to_i8(lm2_v2_f32 v);
LM2_API lm2_v2_u64 lm2_v2_f32_to_u64(lm2_v2_f32 v);
LM2_API lm2_v2_u32 lm2_v2_f32_to_u32(lm2_v2_f32 v);
LM2_API lm2_v2_u16 lm2_v2_f32_to_u16(lm2_v2_f32 v);
LM2_API lm2_v2_u8 lm2_v2_f32_to_u8(lm2_v2_f32 v);

// From i64
LM2_API lm2_v2_f64 lm2_v2_i64_to_f64(lm2_v2_i64 v);
LM2_API lm2_v2_f32 lm2_v2_i64_to_f32(lm2_v2_i64 v);
LM2_API lm2_v2_i32 lm2_v2_i64_to_i32(lm2_v2_i64 v);
LM2_API lm2_v2_i16 lm2_v2_i64_to_i16(lm2_v2_i64 v);
LM2_API lm2_v2_i8 lm2_v2_i64_to_i8(lm2_v2_i64 v);
LM2_API lm2_v2_u64 lm2_v2_i64_to_u64(lm2_v2_i64 v);
LM2_API lm2_v2_u32 lm2_v2_i64_to_u32(lm2_v2_i64 v);
LM2_API lm2_v2_u16 lm2_v2_i64_to_u16(lm2_v2_i64 v);
LM2_API lm2_v2_u8 lm2_v2_i64_to_u8(lm2_v2_i64 v);

// From i32
LM2_API lm2_v2_f64 lm2_v2_i32_to_f64(lm2_v2_i32 v);
LM2_API lm2_v2_f32 lm2_v2_i32_to_f32(lm2_v2_i32 v);
LM2_API lm2_v2_i64 lm2_v2_i32_to_i64(lm2_v2_i32 v);
LM2_API lm2_v2_i16 lm2_v2_i32_to_i16(lm2_v2_i32 v);
LM2_API lm2_v2_i8 lm2_v2_i32_to_i8(lm2_v2_i32 v);
LM2_API lm2_v2_u64 lm2_v2_i32_to_u64(lm2_v2_i32 v);
LM2_API lm2_v2_u32 lm2_v2_i32_to_u32(lm2_v2_i32 v);
LM2_API lm2_v2_u16 lm2_v2_i32_to_u16(lm2_v2_i32 v);
LM2_API lm2_v2_u8 lm2_v2_i32_to_u8(lm2_v2_i32 v);

// From i16
LM2_API lm2_v2_f64 lm2_v2_i16_to_f64(lm2_v2_i16 v);
LM2_API lm2_v2_f32 lm2_v2_i16_to_f32(lm2_v2_i16 v);
LM2_API lm2_v2_i64 lm2_v2_i16_to_i64(lm2_v2_i16 v);
LM2_API lm2_v2_i32 lm2_v2_i16_to_i32(lm2_v2_i16 v);
LM2_API lm2_v2_i8 lm2_v2_i16_to_i8(lm2_v2_i16 v);
LM2_API lm2_v2_u64 lm2_v2_i16_to_u64(lm2_v2_i16 v);
LM2_API lm2_v2_u32 lm2_v2_i16_to_u32(lm2_v2_i16 v);
LM2_API lm2_v2_u16 lm2_v2_i16_to_u16(lm2_v2_i16 v);
LM2_API lm2_v2_u8 lm2_v2_i16_to_u8(lm2_v2_i16 v);

// From i8
LM2_API lm2_v2_f64 lm2_v2_i8_to_f64(lm2_v2_i8 v);
LM2_API lm2_v2_f32 lm2_v2_i8_to_f32(lm2_v2_i8 v);
LM2_API lm2_v2_i64 lm2_v2_i8_to_i64(lm2_v2_i8 v);
LM2_API lm2_v2_i32 lm2_v2_i8_to_i32(lm2_v2_i8 v);
LM2_API lm2_v2_i16 lm2_v2_i8_to_i16(lm2_v2_i8 v);
LM2_API lm2_v2_u64 lm2_v2_i8_to_u64(lm2_v2_i8 v);
LM2_API lm2_v2_u32 lm2_v2_i8_to_u32(lm2_v2_i8 v);
LM2_API lm2_v2_u16 lm2_v2_i8_to_u16(lm2_v2_i8 v);
LM2_API lm2_v2_u8 lm2_v2_i8_to_u8(lm2_v2_i8 v);

// From u64
LM2_API lm2_v2_f64 lm2_v2_u64_to_f64(lm2_v2_u64 v);
LM2_API lm2_v2_f32 lm2_v2_u64_to_f32(lm2_v2_u64 v);
LM2_API lm2_v2_i64 lm2_v2_u64_to_i64(lm2_v2_u64 v);
LM2_API lm2_v2_i32 lm2_v2_u64_to_i32(lm2_v2_u64 v);
LM2_API lm2_v2_i16 lm2_v2_u64_to_i16(lm2_v2_u64 v);
LM2_API lm2_v2_i8 lm2_v2_u64_to_i8(lm2_v2_u64 v);
LM2_API lm2_v2_u32 lm2_v2_u64_to_u32(lm2_v2_u64 v);
LM2_API lm2_v2_u16 lm2_v2_u64_to_u16(lm2_v2_u64 v);
LM2_API lm2_v2_u8 lm2_v2_u64_to_u8(lm2_v2_u64 v);

// From u32
LM2_API lm2_v2_f64 lm2_v2_u32_to_f64(lm2_v2_u32 v);
LM2_API lm2_v2_f32 lm2_v2_u32_to_f32(lm2_v2_u32 v);
LM2_API lm2_v2_i64 lm2_v2_u32_to_i64(lm2_v2_u32 v);
LM2_API lm2_v2_i32 lm2_v2_u32_to_i32(lm2_v2_u32 v);
LM2_API lm2_v2_i16 lm2_v2_u32_to_i16(lm2_v2_u32 v);
LM2_API lm2_v2_i8 lm2_v2_u32_to_i8(lm2_v2_u32 v);
LM2_API lm2_v2_u64 lm2_v2_u32_to_u64(lm2_v2_u32 v);
LM2_API lm2_v2_u16 lm2_v2_u32_to_u16(lm2_v2_u32 v);
LM2_API lm2_v2_u8 lm2_v2_u32_to_u8(lm2_v2_u32 v);

// From u16
LM2_API lm2_v2_f64 lm2_v2_u16_to_f64(lm2_v2_u16 v);
LM2_API lm2_v2_f32 lm2_v2_u16_to_f32(lm2_v2_u16 v);
LM2_API lm2_v2_i64 lm2_v2_u16_to_i64(lm2_v2_u16 v);
LM2_API lm2_v2_i32 lm2_v2_u16_to_i32(lm2_v2_u16 v);
LM2_API lm2_v2_i16 lm2_v2_u16_to_i16(lm2_v2_u16 v);
LM2_API lm2_v2_i8 lm2_v2_u16_to_i8(lm2_v2_u16 v);
LM2_API lm2_v2_u64 lm2_v2_u16_to_u64(lm2_v2_u16 v);
LM2_API lm2_v2_u32 lm2_v2_u16_to_u32(lm2_v2_u16 v);
LM2_API lm2_v2_u8 lm2_v2_u16_to_u8(lm2_v2_u16 v);

// From u8
LM2_API lm2_v2_f64 lm2_v2_u8_to_f64(lm2_v2_u8 v);
LM2_API lm2_v2_f32 lm2_v2_u8_to_f32(lm2_v2_u8 v);
LM2_API lm2_v2_i64 lm2_v2_u8_to_i64(lm2_v2_u8 v);
LM2_API lm2_v2_i32 lm2_v2_u8_to_i32(lm2_v2_u8 v);
LM2_API lm2_v2_i16 lm2_v2_u8_to_i16(lm2_v2_u8 v);
LM2_API lm2_v2_i8 lm2_v2_u8_to_i8(lm2_v2_u8 v);
LM2_API lm2_v2_u64 lm2_v2_u8_to_u64(lm2_v2_u8 v);
LM2_API lm2_v2_u32 lm2_v2_u8_to_u32(lm2_v2_u8 v);
LM2_API lm2_v2_u16 lm2_v2_u8_to_u16(lm2_v2_u8 v);

// =============================================================================
// Vector3 Conversions
// =============================================================================

// From f64
LM2_API lm2_v3_f32 lm2_v3_f64_to_f32(lm2_v3_f64 v);
LM2_API lm2_v3_i64 lm2_v3_f64_to_i64(lm2_v3_f64 v);
LM2_API lm2_v3_i32 lm2_v3_f64_to_i32(lm2_v3_f64 v);
LM2_API lm2_v3_i16 lm2_v3_f64_to_i16(lm2_v3_f64 v);
LM2_API lm2_v3_i8 lm2_v3_f64_to_i8(lm2_v3_f64 v);
LM2_API lm2_v3_u64 lm2_v3_f64_to_u64(lm2_v3_f64 v);
LM2_API lm2_v3_u32 lm2_v3_f64_to_u32(lm2_v3_f64 v);
LM2_API lm2_v3_u16 lm2_v3_f64_to_u16(lm2_v3_f64 v);
LM2_API lm2_v3_u8 lm2_v3_f64_to_u8(lm2_v3_f64 v);

// From f32
LM2_API lm2_v3_f64 lm2_v3_f32_to_f64(lm2_v3_f32 v);
LM2_API lm2_v3_i64 lm2_v3_f32_to_i64(lm2_v3_f32 v);
LM2_API lm2_v3_i32 lm2_v3_f32_to_i32(lm2_v3_f32 v);
LM2_API lm2_v3_i16 lm2_v3_f32_to_i16(lm2_v3_f32 v);
LM2_API lm2_v3_i8 lm2_v3_f32_to_i8(lm2_v3_f32 v);
LM2_API lm2_v3_u64 lm2_v3_f32_to_u64(lm2_v3_f32 v);
LM2_API lm2_v3_u32 lm2_v3_f32_to_u32(lm2_v3_f32 v);
LM2_API lm2_v3_u16 lm2_v3_f32_to_u16(lm2_v3_f32 v);
LM2_API lm2_v3_u8 lm2_v3_f32_to_u8(lm2_v3_f32 v);

// From i64
LM2_API lm2_v3_f64 lm2_v3_i64_to_f64(lm2_v3_i64 v);
LM2_API lm2_v3_f32 lm2_v3_i64_to_f32(lm2_v3_i64 v);
LM2_API lm2_v3_i32 lm2_v3_i64_to_i32(lm2_v3_i64 v);
LM2_API lm2_v3_i16 lm2_v3_i64_to_i16(lm2_v3_i64 v);
LM2_API lm2_v3_i8 lm2_v3_i64_to_i8(lm2_v3_i64 v);
LM2_API lm2_v3_u64 lm2_v3_i64_to_u64(lm2_v3_i64 v);
LM2_API lm2_v3_u32 lm2_v3_i64_to_u32(lm2_v3_i64 v);
LM2_API lm2_v3_u16 lm2_v3_i64_to_u16(lm2_v3_i64 v);
LM2_API lm2_v3_u8 lm2_v3_i64_to_u8(lm2_v3_i64 v);

// From i32
LM2_API lm2_v3_f64 lm2_v3_i32_to_f64(lm2_v3_i32 v);
LM2_API lm2_v3_f32 lm2_v3_i32_to_f32(lm2_v3_i32 v);
LM2_API lm2_v3_i64 lm2_v3_i32_to_i64(lm2_v3_i32 v);
LM2_API lm2_v3_i16 lm2_v3_i32_to_i16(lm2_v3_i32 v);
LM2_API lm2_v3_i8 lm2_v3_i32_to_i8(lm2_v3_i32 v);
LM2_API lm2_v3_u64 lm2_v3_i32_to_u64(lm2_v3_i32 v);
LM2_API lm2_v3_u32 lm2_v3_i32_to_u32(lm2_v3_i32 v);
LM2_API lm2_v3_u16 lm2_v3_i32_to_u16(lm2_v3_i32 v);
LM2_API lm2_v3_u8 lm2_v3_i32_to_u8(lm2_v3_i32 v);

// From i16
LM2_API lm2_v3_f64 lm2_v3_i16_to_f64(lm2_v3_i16 v);
LM2_API lm2_v3_f32 lm2_v3_i16_to_f32(lm2_v3_i16 v);
LM2_API lm2_v3_i64 lm2_v3_i16_to_i64(lm2_v3_i16 v);
LM2_API lm2_v3_i32 lm2_v3_i16_to_i32(lm2_v3_i16 v);
LM2_API lm2_v3_i8 lm2_v3_i16_to_i8(lm2_v3_i16 v);
LM2_API lm2_v3_u64 lm2_v3_i16_to_u64(lm2_v3_i16 v);
LM2_API lm2_v3_u32 lm2_v3_i16_to_u32(lm2_v3_i16 v);
LM2_API lm2_v3_u16 lm2_v3_i16_to_u16(lm2_v3_i16 v);
LM2_API lm2_v3_u8 lm2_v3_i16_to_u8(lm2_v3_i16 v);

// From i8
LM2_API lm2_v3_f64 lm2_v3_i8_to_f64(lm2_v3_i8 v);
LM2_API lm2_v3_f32 lm2_v3_i8_to_f32(lm2_v3_i8 v);
LM2_API lm2_v3_i64 lm2_v3_i8_to_i64(lm2_v3_i8 v);
LM2_API lm2_v3_i32 lm2_v3_i8_to_i32(lm2_v3_i8 v);
LM2_API lm2_v3_i16 lm2_v3_i8_to_i16(lm2_v3_i8 v);
LM2_API lm2_v3_u64 lm2_v3_i8_to_u64(lm2_v3_i8 v);
LM2_API lm2_v3_u32 lm2_v3_i8_to_u32(lm2_v3_i8 v);
LM2_API lm2_v3_u16 lm2_v3_i8_to_u16(lm2_v3_i8 v);
LM2_API lm2_v3_u8 lm2_v3_i8_to_u8(lm2_v3_i8 v);

// From u64
LM2_API lm2_v3_f64 lm2_v3_u64_to_f64(lm2_v3_u64 v);
LM2_API lm2_v3_f32 lm2_v3_u64_to_f32(lm2_v3_u64 v);
LM2_API lm2_v3_i64 lm2_v3_u64_to_i64(lm2_v3_u64 v);
LM2_API lm2_v3_i32 lm2_v3_u64_to_i32(lm2_v3_u64 v);
LM2_API lm2_v3_i16 lm2_v3_u64_to_i16(lm2_v3_u64 v);
LM2_API lm2_v3_i8 lm2_v3_u64_to_i8(lm2_v3_u64 v);
LM2_API lm2_v3_u32 lm2_v3_u64_to_u32(lm2_v3_u64 v);
LM2_API lm2_v3_u16 lm2_v3_u64_to_u16(lm2_v3_u64 v);
LM2_API lm2_v3_u8 lm2_v3_u64_to_u8(lm2_v3_u64 v);

// From u32
LM2_API lm2_v3_f64 lm2_v3_u32_to_f64(lm2_v3_u32 v);
LM2_API lm2_v3_f32 lm2_v3_u32_to_f32(lm2_v3_u32 v);
LM2_API lm2_v3_i64 lm2_v3_u32_to_i64(lm2_v3_u32 v);
LM2_API lm2_v3_i32 lm2_v3_u32_to_i32(lm2_v3_u32 v);
LM2_API lm2_v3_i16 lm2_v3_u32_to_i16(lm2_v3_u32 v);
LM2_API lm2_v3_i8 lm2_v3_u32_to_i8(lm2_v3_u32 v);
LM2_API lm2_v3_u64 lm2_v3_u32_to_u64(lm2_v3_u32 v);
LM2_API lm2_v3_u16 lm2_v3_u32_to_u16(lm2_v3_u32 v);
LM2_API lm2_v3_u8 lm2_v3_u32_to_u8(lm2_v3_u32 v);

// From u16
LM2_API lm2_v3_f64 lm2_v3_u16_to_f64(lm2_v3_u16 v);
LM2_API lm2_v3_f32 lm2_v3_u16_to_f32(lm2_v3_u16 v);
LM2_API lm2_v3_i64 lm2_v3_u16_to_i64(lm2_v3_u16 v);
LM2_API lm2_v3_i32 lm2_v3_u16_to_i32(lm2_v3_u16 v);
LM2_API lm2_v3_i16 lm2_v3_u16_to_i16(lm2_v3_u16 v);
LM2_API lm2_v3_i8 lm2_v3_u16_to_i8(lm2_v3_u16 v);
LM2_API lm2_v3_u64 lm2_v3_u16_to_u64(lm2_v3_u16 v);
LM2_API lm2_v3_u32 lm2_v3_u16_to_u32(lm2_v3_u16 v);
LM2_API lm2_v3_u8 lm2_v3_u16_to_u8(lm2_v3_u16 v);

// From u8
LM2_API lm2_v3_f64 lm2_v3_u8_to_f64(lm2_v3_u8 v);
LM2_API lm2_v3_f32 lm2_v3_u8_to_f32(lm2_v3_u8 v);
LM2_API lm2_v3_i64 lm2_v3_u8_to_i64(lm2_v3_u8 v);
LM2_API lm2_v3_i32 lm2_v3_u8_to_i32(lm2_v3_u8 v);
LM2_API lm2_v3_i16 lm2_v3_u8_to_i16(lm2_v3_u8 v);
LM2_API lm2_v3_i8 lm2_v3_u8_to_i8(lm2_v3_u8 v);
LM2_API lm2_v3_u64 lm2_v3_u8_to_u64(lm2_v3_u8 v);
LM2_API lm2_v3_u32 lm2_v3_u8_to_u32(lm2_v3_u8 v);
LM2_API lm2_v3_u16 lm2_v3_u8_to_u16(lm2_v3_u8 v);

// =============================================================================
// Vector4 Conversions
// =============================================================================

// From f64
LM2_API lm2_v4_f32 lm2_v4_f64_to_f32(lm2_v4_f64 v);
LM2_API lm2_v4_i64 lm2_v4_f64_to_i64(lm2_v4_f64 v);
LM2_API lm2_v4_i32 lm2_v4_f64_to_i32(lm2_v4_f64 v);
LM2_API lm2_v4_i16 lm2_v4_f64_to_i16(lm2_v4_f64 v);
LM2_API lm2_v4_i8 lm2_v4_f64_to_i8(lm2_v4_f64 v);
LM2_API lm2_v4_u64 lm2_v4_f64_to_u64(lm2_v4_f64 v);
LM2_API lm2_v4_u32 lm2_v4_f64_to_u32(lm2_v4_f64 v);
LM2_API lm2_v4_u16 lm2_v4_f64_to_u16(lm2_v4_f64 v);
LM2_API lm2_v4_u8 lm2_v4_f64_to_u8(lm2_v4_f64 v);

// From f32
LM2_API lm2_v4_f64 lm2_v4_f32_to_f64(lm2_v4_f32 v);
LM2_API lm2_v4_i64 lm2_v4_f32_to_i64(lm2_v4_f32 v);
LM2_API lm2_v4_i32 lm2_v4_f32_to_i32(lm2_v4_f32 v);
LM2_API lm2_v4_i16 lm2_v4_f32_to_i16(lm2_v4_f32 v);
LM2_API lm2_v4_i8 lm2_v4_f32_to_i8(lm2_v4_f32 v);
LM2_API lm2_v4_u64 lm2_v4_f32_to_u64(lm2_v4_f32 v);
LM2_API lm2_v4_u32 lm2_v4_f32_to_u32(lm2_v4_f32 v);
LM2_API lm2_v4_u16 lm2_v4_f32_to_u16(lm2_v4_f32 v);
LM2_API lm2_v4_u8 lm2_v4_f32_to_u8(lm2_v4_f32 v);

// From i64
LM2_API lm2_v4_f64 lm2_v4_i64_to_f64(lm2_v4_i64 v);
LM2_API lm2_v4_f32 lm2_v4_i64_to_f32(lm2_v4_i64 v);
LM2_API lm2_v4_i32 lm2_v4_i64_to_i32(lm2_v4_i64 v);
LM2_API lm2_v4_i16 lm2_v4_i64_to_i16(lm2_v4_i64 v);
LM2_API lm2_v4_i8 lm2_v4_i64_to_i8(lm2_v4_i64 v);
LM2_API lm2_v4_u64 lm2_v4_i64_to_u64(lm2_v4_i64 v);
LM2_API lm2_v4_u32 lm2_v4_i64_to_u32(lm2_v4_i64 v);
LM2_API lm2_v4_u16 lm2_v4_i64_to_u16(lm2_v4_i64 v);
LM2_API lm2_v4_u8 lm2_v4_i64_to_u8(lm2_v4_i64 v);

// From i32
LM2_API lm2_v4_f64 lm2_v4_i32_to_f64(lm2_v4_i32 v);
LM2_API lm2_v4_f32 lm2_v4_i32_to_f32(lm2_v4_i32 v);
LM2_API lm2_v4_i64 lm2_v4_i32_to_i64(lm2_v4_i32 v);
LM2_API lm2_v4_i16 lm2_v4_i32_to_i16(lm2_v4_i32 v);
LM2_API lm2_v4_i8 lm2_v4_i32_to_i8(lm2_v4_i32 v);
LM2_API lm2_v4_u64 lm2_v4_i32_to_u64(lm2_v4_i32 v);
LM2_API lm2_v4_u32 lm2_v4_i32_to_u32(lm2_v4_i32 v);
LM2_API lm2_v4_u16 lm2_v4_i32_to_u16(lm2_v4_i32 v);
LM2_API lm2_v4_u8 lm2_v4_i32_to_u8(lm2_v4_i32 v);

// From i16
LM2_API lm2_v4_f64 lm2_v4_i16_to_f64(lm2_v4_i16 v);
LM2_API lm2_v4_f32 lm2_v4_i16_to_f32(lm2_v4_i16 v);
LM2_API lm2_v4_i64 lm2_v4_i16_to_i64(lm2_v4_i16 v);
LM2_API lm2_v4_i32 lm2_v4_i16_to_i32(lm2_v4_i16 v);
LM2_API lm2_v4_i8 lm2_v4_i16_to_i8(lm2_v4_i16 v);
LM2_API lm2_v4_u64 lm2_v4_i16_to_u64(lm2_v4_i16 v);
LM2_API lm2_v4_u32 lm2_v4_i16_to_u32(lm2_v4_i16 v);
LM2_API lm2_v4_u16 lm2_v4_i16_to_u16(lm2_v4_i16 v);
LM2_API lm2_v4_u8 lm2_v4_i16_to_u8(lm2_v4_i16 v);

// From i8
LM2_API lm2_v4_f64 lm2_v4_i8_to_f64(lm2_v4_i8 v);
LM2_API lm2_v4_f32 lm2_v4_i8_to_f32(lm2_v4_i8 v);
LM2_API lm2_v4_i64 lm2_v4_i8_to_i64(lm2_v4_i8 v);
LM2_API lm2_v4_i32 lm2_v4_i8_to_i32(lm2_v4_i8 v);
LM2_API lm2_v4_i16 lm2_v4_i8_to_i16(lm2_v4_i8 v);
LM2_API lm2_v4_u64 lm2_v4_i8_to_u64(lm2_v4_i8 v);
LM2_API lm2_v4_u32 lm2_v4_i8_to_u32(lm2_v4_i8 v);
LM2_API lm2_v4_u16 lm2_v4_i8_to_u16(lm2_v4_i8 v);
LM2_API lm2_v4_u8 lm2_v4_i8_to_u8(lm2_v4_i8 v);

// From u64
LM2_API lm2_v4_f64 lm2_v4_u64_to_f64(lm2_v4_u64 v);
LM2_API lm2_v4_f32 lm2_v4_u64_to_f32(lm2_v4_u64 v);
LM2_API lm2_v4_i64 lm2_v4_u64_to_i64(lm2_v4_u64 v);
LM2_API lm2_v4_i32 lm2_v4_u64_to_i32(lm2_v4_u64 v);
LM2_API lm2_v4_i16 lm2_v4_u64_to_i16(lm2_v4_u64 v);
LM2_API lm2_v4_i8 lm2_v4_u64_to_i8(lm2_v4_u64 v);
LM2_API lm2_v4_u32 lm2_v4_u64_to_u32(lm2_v4_u64 v);
LM2_API lm2_v4_u16 lm2_v4_u64_to_u16(lm2_v4_u64 v);
LM2_API lm2_v4_u8 lm2_v4_u64_to_u8(lm2_v4_u64 v);

// From u32
LM2_API lm2_v4_f64 lm2_v4_u32_to_f64(lm2_v4_u32 v);
LM2_API lm2_v4_f32 lm2_v4_u32_to_f32(lm2_v4_u32 v);
LM2_API lm2_v4_i64 lm2_v4_u32_to_i64(lm2_v4_u32 v);
LM2_API lm2_v4_i32 lm2_v4_u32_to_i32(lm2_v4_u32 v);
LM2_API lm2_v4_i16 lm2_v4_u32_to_i16(lm2_v4_u32 v);
LM2_API lm2_v4_i8 lm2_v4_u32_to_i8(lm2_v4_u32 v);
LM2_API lm2_v4_u64 lm2_v4_u32_to_u64(lm2_v4_u32 v);
LM2_API lm2_v4_u16 lm2_v4_u32_to_u16(lm2_v4_u32 v);
LM2_API lm2_v4_u8 lm2_v4_u32_to_u8(lm2_v4_u32 v);

// From u16
LM2_API lm2_v4_f64 lm2_v4_u16_to_f64(lm2_v4_u16 v);
LM2_API lm2_v4_f32 lm2_v4_u16_to_f32(lm2_v4_u16 v);
LM2_API lm2_v4_i64 lm2_v4_u16_to_i64(lm2_v4_u16 v);
LM2_API lm2_v4_i32 lm2_v4_u16_to_i32(lm2_v4_u16 v);
LM2_API lm2_v4_i16 lm2_v4_u16_to_i16(lm2_v4_u16 v);
LM2_API lm2_v4_i8 lm2_v4_u16_to_i8(lm2_v4_u16 v);
LM2_API lm2_v4_u64 lm2_v4_u16_to_u64(lm2_v4_u16 v);
LM2_API lm2_v4_u32 lm2_v4_u16_to_u32(lm2_v4_u16 v);
LM2_API lm2_v4_u8 lm2_v4_u16_to_u8(lm2_v4_u16 v);

// From u8
LM2_API lm2_v4_f64 lm2_v4_u8_to_f64(lm2_v4_u8 v);
LM2_API lm2_v4_f32 lm2_v4_u8_to_f32(lm2_v4_u8 v);
LM2_API lm2_v4_i64 lm2_v4_u8_to_i64(lm2_v4_u8 v);
LM2_API lm2_v4_i32 lm2_v4_u8_to_i32(lm2_v4_u8 v);
LM2_API lm2_v4_i16 lm2_v4_u8_to_i16(lm2_v4_u8 v);
LM2_API lm2_v4_i8 lm2_v4_u8_to_i8(lm2_v4_u8 v);
LM2_API lm2_v4_u64 lm2_v4_u8_to_u64(lm2_v4_u8 v);
LM2_API lm2_v4_u32 lm2_v4_u8_to_u32(lm2_v4_u8 v);
LM2_API lm2_v4_u16 lm2_v4_u8_to_u16(lm2_v4_u8 v);

// =============================================================================
// Vector Upcast/Downcast Functions (Same Scalar Type)
// =============================================================================

// Upcast v2 -> v3 (adds z component)
LM2_API lm2_v3_f64 lm2_v2_upcast_f64(lm2_v2_f64 v, double z);
LM2_API lm2_v3_f32 lm2_v2_upcast_f32(lm2_v2_f32 v, float z);
LM2_API lm2_v3_i64 lm2_v2_upcast_i64(lm2_v2_i64 v, int64_t z);
LM2_API lm2_v3_i32 lm2_v2_upcast_i32(lm2_v2_i32 v, int32_t z);
LM2_API lm2_v3_i16 lm2_v2_upcast_i16(lm2_v2_i16 v, int16_t z);
LM2_API lm2_v3_i8 lm2_v2_upcast_i8(lm2_v2_i8 v, int8_t z);
LM2_API lm2_v3_u64 lm2_v2_upcast_u64(lm2_v2_u64 v, uint64_t z);
LM2_API lm2_v3_u32 lm2_v2_upcast_u32(lm2_v2_u32 v, uint32_t z);
LM2_API lm2_v3_u16 lm2_v2_upcast_u16(lm2_v2_u16 v, uint16_t z);
LM2_API lm2_v3_u8 lm2_v2_upcast_u8(lm2_v2_u8 v, uint8_t z);

// Upcast v3 -> v4 (adds w component)
LM2_API lm2_v4_f64 lm2_v3_upcast_f64(lm2_v3_f64 v, double w);
LM2_API lm2_v4_f32 lm2_v3_upcast_f32(lm2_v3_f32 v, float w);
LM2_API lm2_v4_i64 lm2_v3_upcast_i64(lm2_v3_i64 v, int64_t w);
LM2_API lm2_v4_i32 lm2_v3_upcast_i32(lm2_v3_i32 v, int32_t w);
LM2_API lm2_v4_i16 lm2_v3_upcast_i16(lm2_v3_i16 v, int16_t w);
LM2_API lm2_v4_i8 lm2_v3_upcast_i8(lm2_v3_i8 v, int8_t w);
LM2_API lm2_v4_u64 lm2_v3_upcast_u64(lm2_v3_u64 v, uint64_t w);
LM2_API lm2_v4_u32 lm2_v3_upcast_u32(lm2_v3_u32 v, uint32_t w);
LM2_API lm2_v4_u16 lm2_v3_upcast_u16(lm2_v3_u16 v, uint16_t w);
LM2_API lm2_v4_u8 lm2_v3_upcast_u8(lm2_v3_u8 v, uint8_t w);

// Downcast v3 -> v2 (drops z component)
LM2_API lm2_v2_f64 lm2_v3_downcast_f64(lm2_v3_f64 v);
LM2_API lm2_v2_f32 lm2_v3_downcast_f32(lm2_v3_f32 v);
LM2_API lm2_v2_i64 lm2_v3_downcast_i64(lm2_v3_i64 v);
LM2_API lm2_v2_i32 lm2_v3_downcast_i32(lm2_v3_i32 v);
LM2_API lm2_v2_i16 lm2_v3_downcast_i16(lm2_v3_i16 v);
LM2_API lm2_v2_i8 lm2_v3_downcast_i8(lm2_v3_i8 v);
LM2_API lm2_v2_u64 lm2_v3_downcast_u64(lm2_v3_u64 v);
LM2_API lm2_v2_u32 lm2_v3_downcast_u32(lm2_v3_u32 v);
LM2_API lm2_v2_u16 lm2_v3_downcast_u16(lm2_v3_u16 v);
LM2_API lm2_v2_u8 lm2_v3_downcast_u8(lm2_v3_u8 v);

// Downcast v4 -> v3 (drops w component)
LM2_API lm2_v3_f64 lm2_v4_downcast_f64(lm2_v4_f64 v);
LM2_API lm2_v3_f32 lm2_v4_downcast_f32(lm2_v4_f32 v);
LM2_API lm2_v3_i64 lm2_v4_downcast_i64(lm2_v4_i64 v);
LM2_API lm2_v3_i32 lm2_v4_downcast_i32(lm2_v4_i32 v);
LM2_API lm2_v3_i16 lm2_v4_downcast_i16(lm2_v4_i16 v);
LM2_API lm2_v3_i8 lm2_v4_downcast_i8(lm2_v4_i8 v);
LM2_API lm2_v3_u64 lm2_v4_downcast_u64(lm2_v4_u64 v);
LM2_API lm2_v3_u32 lm2_v4_downcast_u32(lm2_v4_u32 v);
LM2_API lm2_v3_u16 lm2_v4_downcast_u16(lm2_v4_u16 v);
LM2_API lm2_v3_u8 lm2_v4_downcast_u8(lm2_v4_u8 v);

// #############################################################################
LM2_HEADER_END;
// #############################################################################
