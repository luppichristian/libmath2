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

#include <lm2/ranges/lm2_range_conversions.h>
#include <lm2/lm2_base.h>
#include <lm2/vectors/lm2_vector_conversions.h>

// =============================================================================
// Range2 Conversions - from f64
// =============================================================================

LM2_API lm2_r2_f32 lm2_r2_f64_to_f32(lm2_r2_f64 r) {
  lm2_r2_f32 result = {
      {lm2_v2_f64_to_f32(r.min), lm2_v2_f64_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i64 lm2_r2_f64_to_i64(lm2_r2_f64 r) {
  lm2_r2_i64 result = {
      {lm2_v2_f64_to_i64(r.min), lm2_v2_f64_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i32 lm2_r2_f64_to_i32(lm2_r2_f64 r) {
  lm2_r2_i32 result = {
      {lm2_v2_f64_to_i32(r.min), lm2_v2_f64_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i16 lm2_r2_f64_to_i16(lm2_r2_f64 r) {
  lm2_r2_i16 result = {
      {lm2_v2_f64_to_i16(r.min), lm2_v2_f64_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i8 lm2_r2_f64_to_i8(lm2_r2_f64 r) {
  lm2_r2_i8 result = {
      {lm2_v2_f64_to_i8(r.min), lm2_v2_f64_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u64 lm2_r2_f64_to_u64(lm2_r2_f64 r) {
  lm2_r2_u64 result = {
      {lm2_v2_f64_to_u64(r.min), lm2_v2_f64_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u32 lm2_r2_f64_to_u32(lm2_r2_f64 r) {
  lm2_r2_u32 result = {
      {lm2_v2_f64_to_u32(r.min), lm2_v2_f64_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u16 lm2_r2_f64_to_u16(lm2_r2_f64 r) {
  lm2_r2_u16 result = {
      {lm2_v2_f64_to_u16(r.min), lm2_v2_f64_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u8 lm2_r2_f64_to_u8(lm2_r2_f64 r) {
  lm2_r2_u8 result = {
      {lm2_v2_f64_to_u8(r.min), lm2_v2_f64_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range2 Conversions - from f32
// =============================================================================

LM2_API lm2_r2_f64 lm2_r2_f32_to_f64(lm2_r2_f32 r) {
  lm2_r2_f64 result = {
      {lm2_v2_f32_to_f64(r.min), lm2_v2_f32_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i64 lm2_r2_f32_to_i64(lm2_r2_f32 r) {
  lm2_r2_i64 result = {
      {lm2_v2_f32_to_i64(r.min), lm2_v2_f32_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i32 lm2_r2_f32_to_i32(lm2_r2_f32 r) {
  lm2_r2_i32 result = {
      {lm2_v2_f32_to_i32(r.min), lm2_v2_f32_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i16 lm2_r2_f32_to_i16(lm2_r2_f32 r) {
  lm2_r2_i16 result = {
      {lm2_v2_f32_to_i16(r.min), lm2_v2_f32_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i8 lm2_r2_f32_to_i8(lm2_r2_f32 r) {
  lm2_r2_i8 result = {
      {lm2_v2_f32_to_i8(r.min), lm2_v2_f32_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u64 lm2_r2_f32_to_u64(lm2_r2_f32 r) {
  lm2_r2_u64 result = {
      {lm2_v2_f32_to_u64(r.min), lm2_v2_f32_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u32 lm2_r2_f32_to_u32(lm2_r2_f32 r) {
  lm2_r2_u32 result = {
      {lm2_v2_f32_to_u32(r.min), lm2_v2_f32_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u16 lm2_r2_f32_to_u16(lm2_r2_f32 r) {
  lm2_r2_u16 result = {
      {lm2_v2_f32_to_u16(r.min), lm2_v2_f32_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u8 lm2_r2_f32_to_u8(lm2_r2_f32 r) {
  lm2_r2_u8 result = {
      {lm2_v2_f32_to_u8(r.min), lm2_v2_f32_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range2 Conversions - from i64
// =============================================================================

LM2_API lm2_r2_f64 lm2_r2_i64_to_f64(lm2_r2_i64 r) {
  lm2_r2_f64 result = {
      {lm2_v2_i64_to_f64(r.min), lm2_v2_i64_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_f32 lm2_r2_i64_to_f32(lm2_r2_i64 r) {
  lm2_r2_f32 result = {
      {lm2_v2_i64_to_f32(r.min), lm2_v2_i64_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i32 lm2_r2_i64_to_i32(lm2_r2_i64 r) {
  lm2_r2_i32 result = {
      {lm2_v2_i64_to_i32(r.min), lm2_v2_i64_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i16 lm2_r2_i64_to_i16(lm2_r2_i64 r) {
  lm2_r2_i16 result = {
      {lm2_v2_i64_to_i16(r.min), lm2_v2_i64_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i8 lm2_r2_i64_to_i8(lm2_r2_i64 r) {
  lm2_r2_i8 result = {
      {lm2_v2_i64_to_i8(r.min), lm2_v2_i64_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u64 lm2_r2_i64_to_u64(lm2_r2_i64 r) {
  lm2_r2_u64 result = {
      {lm2_v2_i64_to_u64(r.min), lm2_v2_i64_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u32 lm2_r2_i64_to_u32(lm2_r2_i64 r) {
  lm2_r2_u32 result = {
      {lm2_v2_i64_to_u32(r.min), lm2_v2_i64_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u16 lm2_r2_i64_to_u16(lm2_r2_i64 r) {
  lm2_r2_u16 result = {
      {lm2_v2_i64_to_u16(r.min), lm2_v2_i64_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u8 lm2_r2_i64_to_u8(lm2_r2_i64 r) {
  lm2_r2_u8 result = {
      {lm2_v2_i64_to_u8(r.min), lm2_v2_i64_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range2 Conversions - from i32
// =============================================================================

LM2_API lm2_r2_f64 lm2_r2_i32_to_f64(lm2_r2_i32 r) {
  lm2_r2_f64 result = {
      {lm2_v2_i32_to_f64(r.min), lm2_v2_i32_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_f32 lm2_r2_i32_to_f32(lm2_r2_i32 r) {
  lm2_r2_f32 result = {
      {lm2_v2_i32_to_f32(r.min), lm2_v2_i32_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i64 lm2_r2_i32_to_i64(lm2_r2_i32 r) {
  lm2_r2_i64 result = {
      {lm2_v2_i32_to_i64(r.min), lm2_v2_i32_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i16 lm2_r2_i32_to_i16(lm2_r2_i32 r) {
  lm2_r2_i16 result = {
      {lm2_v2_i32_to_i16(r.min), lm2_v2_i32_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i8 lm2_r2_i32_to_i8(lm2_r2_i32 r) {
  lm2_r2_i8 result = {
      {lm2_v2_i32_to_i8(r.min), lm2_v2_i32_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u64 lm2_r2_i32_to_u64(lm2_r2_i32 r) {
  lm2_r2_u64 result = {
      {lm2_v2_i32_to_u64(r.min), lm2_v2_i32_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u32 lm2_r2_i32_to_u32(lm2_r2_i32 r) {
  lm2_r2_u32 result = {
      {lm2_v2_i32_to_u32(r.min), lm2_v2_i32_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u16 lm2_r2_i32_to_u16(lm2_r2_i32 r) {
  lm2_r2_u16 result = {
      {lm2_v2_i32_to_u16(r.min), lm2_v2_i32_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u8 lm2_r2_i32_to_u8(lm2_r2_i32 r) {
  lm2_r2_u8 result = {
      {lm2_v2_i32_to_u8(r.min), lm2_v2_i32_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range2 Conversions - from i16
// =============================================================================

LM2_API lm2_r2_f64 lm2_r2_i16_to_f64(lm2_r2_i16 r) {
  lm2_r2_f64 result = {
      {lm2_v2_i16_to_f64(r.min), lm2_v2_i16_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_f32 lm2_r2_i16_to_f32(lm2_r2_i16 r) {
  lm2_r2_f32 result = {
      {lm2_v2_i16_to_f32(r.min), lm2_v2_i16_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i64 lm2_r2_i16_to_i64(lm2_r2_i16 r) {
  lm2_r2_i64 result = {
      {lm2_v2_i16_to_i64(r.min), lm2_v2_i16_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i32 lm2_r2_i16_to_i32(lm2_r2_i16 r) {
  lm2_r2_i32 result = {
      {lm2_v2_i16_to_i32(r.min), lm2_v2_i16_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i8 lm2_r2_i16_to_i8(lm2_r2_i16 r) {
  lm2_r2_i8 result = {
      {lm2_v2_i16_to_i8(r.min), lm2_v2_i16_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u64 lm2_r2_i16_to_u64(lm2_r2_i16 r) {
  lm2_r2_u64 result = {
      {lm2_v2_i16_to_u64(r.min), lm2_v2_i16_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u32 lm2_r2_i16_to_u32(lm2_r2_i16 r) {
  lm2_r2_u32 result = {
      {lm2_v2_i16_to_u32(r.min), lm2_v2_i16_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u16 lm2_r2_i16_to_u16(lm2_r2_i16 r) {
  lm2_r2_u16 result = {
      {lm2_v2_i16_to_u16(r.min), lm2_v2_i16_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u8 lm2_r2_i16_to_u8(lm2_r2_i16 r) {
  lm2_r2_u8 result = {
      {lm2_v2_i16_to_u8(r.min), lm2_v2_i16_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range2 Conversions - from i8
// =============================================================================

LM2_API lm2_r2_f64 lm2_r2_i8_to_f64(lm2_r2_i8 r) {
  lm2_r2_f64 result = {
      {lm2_v2_i8_to_f64(r.min), lm2_v2_i8_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_f32 lm2_r2_i8_to_f32(lm2_r2_i8 r) {
  lm2_r2_f32 result = {
      {lm2_v2_i8_to_f32(r.min), lm2_v2_i8_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i64 lm2_r2_i8_to_i64(lm2_r2_i8 r) {
  lm2_r2_i64 result = {
      {lm2_v2_i8_to_i64(r.min), lm2_v2_i8_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i32 lm2_r2_i8_to_i32(lm2_r2_i8 r) {
  lm2_r2_i32 result = {
      {lm2_v2_i8_to_i32(r.min), lm2_v2_i8_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i16 lm2_r2_i8_to_i16(lm2_r2_i8 r) {
  lm2_r2_i16 result = {
      {lm2_v2_i8_to_i16(r.min), lm2_v2_i8_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u64 lm2_r2_i8_to_u64(lm2_r2_i8 r) {
  lm2_r2_u64 result = {
      {lm2_v2_i8_to_u64(r.min), lm2_v2_i8_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u32 lm2_r2_i8_to_u32(lm2_r2_i8 r) {
  lm2_r2_u32 result = {
      {lm2_v2_i8_to_u32(r.min), lm2_v2_i8_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u16 lm2_r2_i8_to_u16(lm2_r2_i8 r) {
  lm2_r2_u16 result = {
      {lm2_v2_i8_to_u16(r.min), lm2_v2_i8_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u8 lm2_r2_i8_to_u8(lm2_r2_i8 r) {
  lm2_r2_u8 result = {
      {lm2_v2_i8_to_u8(r.min), lm2_v2_i8_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range2 Conversions - from u64
// =============================================================================

LM2_API lm2_r2_f64 lm2_r2_u64_to_f64(lm2_r2_u64 r) {
  lm2_r2_f64 result = {
      {lm2_v2_u64_to_f64(r.min), lm2_v2_u64_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_f32 lm2_r2_u64_to_f32(lm2_r2_u64 r) {
  lm2_r2_f32 result = {
      {lm2_v2_u64_to_f32(r.min), lm2_v2_u64_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i64 lm2_r2_u64_to_i64(lm2_r2_u64 r) {
  lm2_r2_i64 result = {
      {lm2_v2_u64_to_i64(r.min), lm2_v2_u64_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i32 lm2_r2_u64_to_i32(lm2_r2_u64 r) {
  lm2_r2_i32 result = {
      {lm2_v2_u64_to_i32(r.min), lm2_v2_u64_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i16 lm2_r2_u64_to_i16(lm2_r2_u64 r) {
  lm2_r2_i16 result = {
      {lm2_v2_u64_to_i16(r.min), lm2_v2_u64_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i8 lm2_r2_u64_to_i8(lm2_r2_u64 r) {
  lm2_r2_i8 result = {
      {lm2_v2_u64_to_i8(r.min), lm2_v2_u64_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u32 lm2_r2_u64_to_u32(lm2_r2_u64 r) {
  lm2_r2_u32 result = {
      {lm2_v2_u64_to_u32(r.min), lm2_v2_u64_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u16 lm2_r2_u64_to_u16(lm2_r2_u64 r) {
  lm2_r2_u16 result = {
      {lm2_v2_u64_to_u16(r.min), lm2_v2_u64_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u8 lm2_r2_u64_to_u8(lm2_r2_u64 r) {
  lm2_r2_u8 result = {
      {lm2_v2_u64_to_u8(r.min), lm2_v2_u64_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range2 Conversions - from u32
// =============================================================================

LM2_API lm2_r2_f64 lm2_r2_u32_to_f64(lm2_r2_u32 r) {
  lm2_r2_f64 result = {
      {lm2_v2_u32_to_f64(r.min), lm2_v2_u32_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_f32 lm2_r2_u32_to_f32(lm2_r2_u32 r) {
  lm2_r2_f32 result = {
      {lm2_v2_u32_to_f32(r.min), lm2_v2_u32_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i64 lm2_r2_u32_to_i64(lm2_r2_u32 r) {
  lm2_r2_i64 result = {
      {lm2_v2_u32_to_i64(r.min), lm2_v2_u32_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i32 lm2_r2_u32_to_i32(lm2_r2_u32 r) {
  lm2_r2_i32 result = {
      {lm2_v2_u32_to_i32(r.min), lm2_v2_u32_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i16 lm2_r2_u32_to_i16(lm2_r2_u32 r) {
  lm2_r2_i16 result = {
      {lm2_v2_u32_to_i16(r.min), lm2_v2_u32_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i8 lm2_r2_u32_to_i8(lm2_r2_u32 r) {
  lm2_r2_i8 result = {
      {lm2_v2_u32_to_i8(r.min), lm2_v2_u32_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u64 lm2_r2_u32_to_u64(lm2_r2_u32 r) {
  lm2_r2_u64 result = {
      {lm2_v2_u32_to_u64(r.min), lm2_v2_u32_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u16 lm2_r2_u32_to_u16(lm2_r2_u32 r) {
  lm2_r2_u16 result = {
      {lm2_v2_u32_to_u16(r.min), lm2_v2_u32_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u8 lm2_r2_u32_to_u8(lm2_r2_u32 r) {
  lm2_r2_u8 result = {
      {lm2_v2_u32_to_u8(r.min), lm2_v2_u32_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range2 Conversions - from u16
// =============================================================================

LM2_API lm2_r2_f64 lm2_r2_u16_to_f64(lm2_r2_u16 r) {
  lm2_r2_f64 result = {
      {lm2_v2_u16_to_f64(r.min), lm2_v2_u16_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_f32 lm2_r2_u16_to_f32(lm2_r2_u16 r) {
  lm2_r2_f32 result = {
      {lm2_v2_u16_to_f32(r.min), lm2_v2_u16_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i64 lm2_r2_u16_to_i64(lm2_r2_u16 r) {
  lm2_r2_i64 result = {
      {lm2_v2_u16_to_i64(r.min), lm2_v2_u16_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i32 lm2_r2_u16_to_i32(lm2_r2_u16 r) {
  lm2_r2_i32 result = {
      {lm2_v2_u16_to_i32(r.min), lm2_v2_u16_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i16 lm2_r2_u16_to_i16(lm2_r2_u16 r) {
  lm2_r2_i16 result = {
      {lm2_v2_u16_to_i16(r.min), lm2_v2_u16_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i8 lm2_r2_u16_to_i8(lm2_r2_u16 r) {
  lm2_r2_i8 result = {
      {lm2_v2_u16_to_i8(r.min), lm2_v2_u16_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u64 lm2_r2_u16_to_u64(lm2_r2_u16 r) {
  lm2_r2_u64 result = {
      {lm2_v2_u16_to_u64(r.min), lm2_v2_u16_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u32 lm2_r2_u16_to_u32(lm2_r2_u16 r) {
  lm2_r2_u32 result = {
      {lm2_v2_u16_to_u32(r.min), lm2_v2_u16_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u8 lm2_r2_u16_to_u8(lm2_r2_u16 r) {
  lm2_r2_u8 result = {
      {lm2_v2_u16_to_u8(r.min), lm2_v2_u16_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range2 Conversions - from u8
// =============================================================================

LM2_API lm2_r2_f64 lm2_r2_u8_to_f64(lm2_r2_u8 r) {
  lm2_r2_f64 result = {
      {lm2_v2_u8_to_f64(r.min), lm2_v2_u8_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_f32 lm2_r2_u8_to_f32(lm2_r2_u8 r) {
  lm2_r2_f32 result = {
      {lm2_v2_u8_to_f32(r.min), lm2_v2_u8_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i64 lm2_r2_u8_to_i64(lm2_r2_u8 r) {
  lm2_r2_i64 result = {
      {lm2_v2_u8_to_i64(r.min), lm2_v2_u8_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i32 lm2_r2_u8_to_i32(lm2_r2_u8 r) {
  lm2_r2_i32 result = {
      {lm2_v2_u8_to_i32(r.min), lm2_v2_u8_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i16 lm2_r2_u8_to_i16(lm2_r2_u8 r) {
  lm2_r2_i16 result = {
      {lm2_v2_u8_to_i16(r.min), lm2_v2_u8_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i8 lm2_r2_u8_to_i8(lm2_r2_u8 r) {
  lm2_r2_i8 result = {
      {lm2_v2_u8_to_i8(r.min), lm2_v2_u8_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u64 lm2_r2_u8_to_u64(lm2_r2_u8 r) {
  lm2_r2_u64 result = {
      {lm2_v2_u8_to_u64(r.min), lm2_v2_u8_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u32 lm2_r2_u8_to_u32(lm2_r2_u8 r) {
  lm2_r2_u32 result = {
      {lm2_v2_u8_to_u32(r.min), lm2_v2_u8_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u16 lm2_r2_u8_to_u16(lm2_r2_u8 r) {
  lm2_r2_u16 result = {
      {lm2_v2_u8_to_u16(r.min), lm2_v2_u8_to_u16(r.max)}
  };
  return result;
}

// =============================================================================
// Range3 Conversions - from f64
// =============================================================================

LM2_API lm2_r3_f32 lm2_r3_f64_to_f32(lm2_r3_f64 r) {
  lm2_r3_f32 result = {
      {lm2_v3_f64_to_f32(r.min), lm2_v3_f64_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i64 lm2_r3_f64_to_i64(lm2_r3_f64 r) {
  lm2_r3_i64 result = {
      {lm2_v3_f64_to_i64(r.min), lm2_v3_f64_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i32 lm2_r3_f64_to_i32(lm2_r3_f64 r) {
  lm2_r3_i32 result = {
      {lm2_v3_f64_to_i32(r.min), lm2_v3_f64_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i16 lm2_r3_f64_to_i16(lm2_r3_f64 r) {
  lm2_r3_i16 result = {
      {lm2_v3_f64_to_i16(r.min), lm2_v3_f64_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i8 lm2_r3_f64_to_i8(lm2_r3_f64 r) {
  lm2_r3_i8 result = {
      {lm2_v3_f64_to_i8(r.min), lm2_v3_f64_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u64 lm2_r3_f64_to_u64(lm2_r3_f64 r) {
  lm2_r3_u64 result = {
      {lm2_v3_f64_to_u64(r.min), lm2_v3_f64_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u32 lm2_r3_f64_to_u32(lm2_r3_f64 r) {
  lm2_r3_u32 result = {
      {lm2_v3_f64_to_u32(r.min), lm2_v3_f64_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u16 lm2_r3_f64_to_u16(lm2_r3_f64 r) {
  lm2_r3_u16 result = {
      {lm2_v3_f64_to_u16(r.min), lm2_v3_f64_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u8 lm2_r3_f64_to_u8(lm2_r3_f64 r) {
  lm2_r3_u8 result = {
      {lm2_v3_f64_to_u8(r.min), lm2_v3_f64_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range3 Conversions - from f32
// =============================================================================

LM2_API lm2_r3_f64 lm2_r3_f32_to_f64(lm2_r3_f32 r) {
  lm2_r3_f64 result = {
      {lm2_v3_f32_to_f64(r.min), lm2_v3_f32_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i64 lm2_r3_f32_to_i64(lm2_r3_f32 r) {
  lm2_r3_i64 result = {
      {lm2_v3_f32_to_i64(r.min), lm2_v3_f32_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i32 lm2_r3_f32_to_i32(lm2_r3_f32 r) {
  lm2_r3_i32 result = {
      {lm2_v3_f32_to_i32(r.min), lm2_v3_f32_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i16 lm2_r3_f32_to_i16(lm2_r3_f32 r) {
  lm2_r3_i16 result = {
      {lm2_v3_f32_to_i16(r.min), lm2_v3_f32_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i8 lm2_r3_f32_to_i8(lm2_r3_f32 r) {
  lm2_r3_i8 result = {
      {lm2_v3_f32_to_i8(r.min), lm2_v3_f32_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u64 lm2_r3_f32_to_u64(lm2_r3_f32 r) {
  lm2_r3_u64 result = {
      {lm2_v3_f32_to_u64(r.min), lm2_v3_f32_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u32 lm2_r3_f32_to_u32(lm2_r3_f32 r) {
  lm2_r3_u32 result = {
      {lm2_v3_f32_to_u32(r.min), lm2_v3_f32_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u16 lm2_r3_f32_to_u16(lm2_r3_f32 r) {
  lm2_r3_u16 result = {
      {lm2_v3_f32_to_u16(r.min), lm2_v3_f32_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u8 lm2_r3_f32_to_u8(lm2_r3_f32 r) {
  lm2_r3_u8 result = {
      {lm2_v3_f32_to_u8(r.min), lm2_v3_f32_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range3 Conversions - from i64
// =============================================================================

LM2_API lm2_r3_f64 lm2_r3_i64_to_f64(lm2_r3_i64 r) {
  lm2_r3_f64 result = {
      {lm2_v3_i64_to_f64(r.min), lm2_v3_i64_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_f32 lm2_r3_i64_to_f32(lm2_r3_i64 r) {
  lm2_r3_f32 result = {
      {lm2_v3_i64_to_f32(r.min), lm2_v3_i64_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i32 lm2_r3_i64_to_i32(lm2_r3_i64 r) {
  lm2_r3_i32 result = {
      {lm2_v3_i64_to_i32(r.min), lm2_v3_i64_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i16 lm2_r3_i64_to_i16(lm2_r3_i64 r) {
  lm2_r3_i16 result = {
      {lm2_v3_i64_to_i16(r.min), lm2_v3_i64_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i8 lm2_r3_i64_to_i8(lm2_r3_i64 r) {
  lm2_r3_i8 result = {
      {lm2_v3_i64_to_i8(r.min), lm2_v3_i64_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u64 lm2_r3_i64_to_u64(lm2_r3_i64 r) {
  lm2_r3_u64 result = {
      {lm2_v3_i64_to_u64(r.min), lm2_v3_i64_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u32 lm2_r3_i64_to_u32(lm2_r3_i64 r) {
  lm2_r3_u32 result = {
      {lm2_v3_i64_to_u32(r.min), lm2_v3_i64_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u16 lm2_r3_i64_to_u16(lm2_r3_i64 r) {
  lm2_r3_u16 result = {
      {lm2_v3_i64_to_u16(r.min), lm2_v3_i64_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u8 lm2_r3_i64_to_u8(lm2_r3_i64 r) {
  lm2_r3_u8 result = {
      {lm2_v3_i64_to_u8(r.min), lm2_v3_i64_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range3 Conversions - from i32
// =============================================================================

LM2_API lm2_r3_f64 lm2_r3_i32_to_f64(lm2_r3_i32 r) {
  lm2_r3_f64 result = {
      {lm2_v3_i32_to_f64(r.min), lm2_v3_i32_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_f32 lm2_r3_i32_to_f32(lm2_r3_i32 r) {
  lm2_r3_f32 result = {
      {lm2_v3_i32_to_f32(r.min), lm2_v3_i32_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i64 lm2_r3_i32_to_i64(lm2_r3_i32 r) {
  lm2_r3_i64 result = {
      {lm2_v3_i32_to_i64(r.min), lm2_v3_i32_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i16 lm2_r3_i32_to_i16(lm2_r3_i32 r) {
  lm2_r3_i16 result = {
      {lm2_v3_i32_to_i16(r.min), lm2_v3_i32_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i8 lm2_r3_i32_to_i8(lm2_r3_i32 r) {
  lm2_r3_i8 result = {
      {lm2_v3_i32_to_i8(r.min), lm2_v3_i32_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u64 lm2_r3_i32_to_u64(lm2_r3_i32 r) {
  lm2_r3_u64 result = {
      {lm2_v3_i32_to_u64(r.min), lm2_v3_i32_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u32 lm2_r3_i32_to_u32(lm2_r3_i32 r) {
  lm2_r3_u32 result = {
      {lm2_v3_i32_to_u32(r.min), lm2_v3_i32_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u16 lm2_r3_i32_to_u16(lm2_r3_i32 r) {
  lm2_r3_u16 result = {
      {lm2_v3_i32_to_u16(r.min), lm2_v3_i32_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u8 lm2_r3_i32_to_u8(lm2_r3_i32 r) {
  lm2_r3_u8 result = {
      {lm2_v3_i32_to_u8(r.min), lm2_v3_i32_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range3 Conversions - from i16
// =============================================================================

LM2_API lm2_r3_f64 lm2_r3_i16_to_f64(lm2_r3_i16 r) {
  lm2_r3_f64 result = {
      {lm2_v3_i16_to_f64(r.min), lm2_v3_i16_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_f32 lm2_r3_i16_to_f32(lm2_r3_i16 r) {
  lm2_r3_f32 result = {
      {lm2_v3_i16_to_f32(r.min), lm2_v3_i16_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i64 lm2_r3_i16_to_i64(lm2_r3_i16 r) {
  lm2_r3_i64 result = {
      {lm2_v3_i16_to_i64(r.min), lm2_v3_i16_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i32 lm2_r3_i16_to_i32(lm2_r3_i16 r) {
  lm2_r3_i32 result = {
      {lm2_v3_i16_to_i32(r.min), lm2_v3_i16_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i8 lm2_r3_i16_to_i8(lm2_r3_i16 r) {
  lm2_r3_i8 result = {
      {lm2_v3_i16_to_i8(r.min), lm2_v3_i16_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u64 lm2_r3_i16_to_u64(lm2_r3_i16 r) {
  lm2_r3_u64 result = {
      {lm2_v3_i16_to_u64(r.min), lm2_v3_i16_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u32 lm2_r3_i16_to_u32(lm2_r3_i16 r) {
  lm2_r3_u32 result = {
      {lm2_v3_i16_to_u32(r.min), lm2_v3_i16_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u16 lm2_r3_i16_to_u16(lm2_r3_i16 r) {
  lm2_r3_u16 result = {
      {lm2_v3_i16_to_u16(r.min), lm2_v3_i16_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u8 lm2_r3_i16_to_u8(lm2_r3_i16 r) {
  lm2_r3_u8 result = {
      {lm2_v3_i16_to_u8(r.min), lm2_v3_i16_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range3 Conversions - from i8
// =============================================================================

LM2_API lm2_r3_f64 lm2_r3_i8_to_f64(lm2_r3_i8 r) {
  lm2_r3_f64 result = {
      {lm2_v3_i8_to_f64(r.min), lm2_v3_i8_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_f32 lm2_r3_i8_to_f32(lm2_r3_i8 r) {
  lm2_r3_f32 result = {
      {lm2_v3_i8_to_f32(r.min), lm2_v3_i8_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i64 lm2_r3_i8_to_i64(lm2_r3_i8 r) {
  lm2_r3_i64 result = {
      {lm2_v3_i8_to_i64(r.min), lm2_v3_i8_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i32 lm2_r3_i8_to_i32(lm2_r3_i8 r) {
  lm2_r3_i32 result = {
      {lm2_v3_i8_to_i32(r.min), lm2_v3_i8_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i16 lm2_r3_i8_to_i16(lm2_r3_i8 r) {
  lm2_r3_i16 result = {
      {lm2_v3_i8_to_i16(r.min), lm2_v3_i8_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u64 lm2_r3_i8_to_u64(lm2_r3_i8 r) {
  lm2_r3_u64 result = {
      {lm2_v3_i8_to_u64(r.min), lm2_v3_i8_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u32 lm2_r3_i8_to_u32(lm2_r3_i8 r) {
  lm2_r3_u32 result = {
      {lm2_v3_i8_to_u32(r.min), lm2_v3_i8_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u16 lm2_r3_i8_to_u16(lm2_r3_i8 r) {
  lm2_r3_u16 result = {
      {lm2_v3_i8_to_u16(r.min), lm2_v3_i8_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u8 lm2_r3_i8_to_u8(lm2_r3_i8 r) {
  lm2_r3_u8 result = {
      {lm2_v3_i8_to_u8(r.min), lm2_v3_i8_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range3 Conversions - from u64
// =============================================================================

LM2_API lm2_r3_f64 lm2_r3_u64_to_f64(lm2_r3_u64 r) {
  lm2_r3_f64 result = {
      {lm2_v3_u64_to_f64(r.min), lm2_v3_u64_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_f32 lm2_r3_u64_to_f32(lm2_r3_u64 r) {
  lm2_r3_f32 result = {
      {lm2_v3_u64_to_f32(r.min), lm2_v3_u64_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i64 lm2_r3_u64_to_i64(lm2_r3_u64 r) {
  lm2_r3_i64 result = {
      {lm2_v3_u64_to_i64(r.min), lm2_v3_u64_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i32 lm2_r3_u64_to_i32(lm2_r3_u64 r) {
  lm2_r3_i32 result = {
      {lm2_v3_u64_to_i32(r.min), lm2_v3_u64_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i16 lm2_r3_u64_to_i16(lm2_r3_u64 r) {
  lm2_r3_i16 result = {
      {lm2_v3_u64_to_i16(r.min), lm2_v3_u64_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i8 lm2_r3_u64_to_i8(lm2_r3_u64 r) {
  lm2_r3_i8 result = {
      {lm2_v3_u64_to_i8(r.min), lm2_v3_u64_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u32 lm2_r3_u64_to_u32(lm2_r3_u64 r) {
  lm2_r3_u32 result = {
      {lm2_v3_u64_to_u32(r.min), lm2_v3_u64_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u16 lm2_r3_u64_to_u16(lm2_r3_u64 r) {
  lm2_r3_u16 result = {
      {lm2_v3_u64_to_u16(r.min), lm2_v3_u64_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u8 lm2_r3_u64_to_u8(lm2_r3_u64 r) {
  lm2_r3_u8 result = {
      {lm2_v3_u64_to_u8(r.min), lm2_v3_u64_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range3 Conversions - from u32
// =============================================================================

LM2_API lm2_r3_f64 lm2_r3_u32_to_f64(lm2_r3_u32 r) {
  lm2_r3_f64 result = {
      {lm2_v3_u32_to_f64(r.min), lm2_v3_u32_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_f32 lm2_r3_u32_to_f32(lm2_r3_u32 r) {
  lm2_r3_f32 result = {
      {lm2_v3_u32_to_f32(r.min), lm2_v3_u32_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i64 lm2_r3_u32_to_i64(lm2_r3_u32 r) {
  lm2_r3_i64 result = {
      {lm2_v3_u32_to_i64(r.min), lm2_v3_u32_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i32 lm2_r3_u32_to_i32(lm2_r3_u32 r) {
  lm2_r3_i32 result = {
      {lm2_v3_u32_to_i32(r.min), lm2_v3_u32_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i16 lm2_r3_u32_to_i16(lm2_r3_u32 r) {
  lm2_r3_i16 result = {
      {lm2_v3_u32_to_i16(r.min), lm2_v3_u32_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i8 lm2_r3_u32_to_i8(lm2_r3_u32 r) {
  lm2_r3_i8 result = {
      {lm2_v3_u32_to_i8(r.min), lm2_v3_u32_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u64 lm2_r3_u32_to_u64(lm2_r3_u32 r) {
  lm2_r3_u64 result = {
      {lm2_v3_u32_to_u64(r.min), lm2_v3_u32_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u16 lm2_r3_u32_to_u16(lm2_r3_u32 r) {
  lm2_r3_u16 result = {
      {lm2_v3_u32_to_u16(r.min), lm2_v3_u32_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u8 lm2_r3_u32_to_u8(lm2_r3_u32 r) {
  lm2_r3_u8 result = {
      {lm2_v3_u32_to_u8(r.min), lm2_v3_u32_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range3 Conversions - from u16
// =============================================================================

LM2_API lm2_r3_f64 lm2_r3_u16_to_f64(lm2_r3_u16 r) {
  lm2_r3_f64 result = {
      {lm2_v3_u16_to_f64(r.min), lm2_v3_u16_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_f32 lm2_r3_u16_to_f32(lm2_r3_u16 r) {
  lm2_r3_f32 result = {
      {lm2_v3_u16_to_f32(r.min), lm2_v3_u16_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i64 lm2_r3_u16_to_i64(lm2_r3_u16 r) {
  lm2_r3_i64 result = {
      {lm2_v3_u16_to_i64(r.min), lm2_v3_u16_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i32 lm2_r3_u16_to_i32(lm2_r3_u16 r) {
  lm2_r3_i32 result = {
      {lm2_v3_u16_to_i32(r.min), lm2_v3_u16_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i16 lm2_r3_u16_to_i16(lm2_r3_u16 r) {
  lm2_r3_i16 result = {
      {lm2_v3_u16_to_i16(r.min), lm2_v3_u16_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i8 lm2_r3_u16_to_i8(lm2_r3_u16 r) {
  lm2_r3_i8 result = {
      {lm2_v3_u16_to_i8(r.min), lm2_v3_u16_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u64 lm2_r3_u16_to_u64(lm2_r3_u16 r) {
  lm2_r3_u64 result = {
      {lm2_v3_u16_to_u64(r.min), lm2_v3_u16_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u32 lm2_r3_u16_to_u32(lm2_r3_u16 r) {
  lm2_r3_u32 result = {
      {lm2_v3_u16_to_u32(r.min), lm2_v3_u16_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u8 lm2_r3_u16_to_u8(lm2_r3_u16 r) {
  lm2_r3_u8 result = {
      {lm2_v3_u16_to_u8(r.min), lm2_v3_u16_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range3 Conversions - from u8
// =============================================================================

LM2_API lm2_r3_f64 lm2_r3_u8_to_f64(lm2_r3_u8 r) {
  lm2_r3_f64 result = {
      {lm2_v3_u8_to_f64(r.min), lm2_v3_u8_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_f32 lm2_r3_u8_to_f32(lm2_r3_u8 r) {
  lm2_r3_f32 result = {
      {lm2_v3_u8_to_f32(r.min), lm2_v3_u8_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i64 lm2_r3_u8_to_i64(lm2_r3_u8 r) {
  lm2_r3_i64 result = {
      {lm2_v3_u8_to_i64(r.min), lm2_v3_u8_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i32 lm2_r3_u8_to_i32(lm2_r3_u8 r) {
  lm2_r3_i32 result = {
      {lm2_v3_u8_to_i32(r.min), lm2_v3_u8_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i16 lm2_r3_u8_to_i16(lm2_r3_u8 r) {
  lm2_r3_i16 result = {
      {lm2_v3_u8_to_i16(r.min), lm2_v3_u8_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i8 lm2_r3_u8_to_i8(lm2_r3_u8 r) {
  lm2_r3_i8 result = {
      {lm2_v3_u8_to_i8(r.min), lm2_v3_u8_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u64 lm2_r3_u8_to_u64(lm2_r3_u8 r) {
  lm2_r3_u64 result = {
      {lm2_v3_u8_to_u64(r.min), lm2_v3_u8_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u32 lm2_r3_u8_to_u32(lm2_r3_u8 r) {
  lm2_r3_u32 result = {
      {lm2_v3_u8_to_u32(r.min), lm2_v3_u8_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u16 lm2_r3_u8_to_u16(lm2_r3_u8 r) {
  lm2_r3_u16 result = {
      {lm2_v3_u8_to_u16(r.min), lm2_v3_u8_to_u16(r.max)}
  };
  return result;
}

// =============================================================================
// Range4 Conversions - from f64
// =============================================================================

LM2_API lm2_r4_f32 lm2_r4_f64_to_f32(lm2_r4_f64 r) {
  lm2_r4_f32 result = {
      {lm2_v4_f64_to_f32(r.min), lm2_v4_f64_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i64 lm2_r4_f64_to_i64(lm2_r4_f64 r) {
  lm2_r4_i64 result = {
      {lm2_v4_f64_to_i64(r.min), lm2_v4_f64_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i32 lm2_r4_f64_to_i32(lm2_r4_f64 r) {
  lm2_r4_i32 result = {
      {lm2_v4_f64_to_i32(r.min), lm2_v4_f64_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i16 lm2_r4_f64_to_i16(lm2_r4_f64 r) {
  lm2_r4_i16 result = {
      {lm2_v4_f64_to_i16(r.min), lm2_v4_f64_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i8 lm2_r4_f64_to_i8(lm2_r4_f64 r) {
  lm2_r4_i8 result = {
      {lm2_v4_f64_to_i8(r.min), lm2_v4_f64_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u64 lm2_r4_f64_to_u64(lm2_r4_f64 r) {
  lm2_r4_u64 result = {
      {lm2_v4_f64_to_u64(r.min), lm2_v4_f64_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u32 lm2_r4_f64_to_u32(lm2_r4_f64 r) {
  lm2_r4_u32 result = {
      {lm2_v4_f64_to_u32(r.min), lm2_v4_f64_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u16 lm2_r4_f64_to_u16(lm2_r4_f64 r) {
  lm2_r4_u16 result = {
      {lm2_v4_f64_to_u16(r.min), lm2_v4_f64_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u8 lm2_r4_f64_to_u8(lm2_r4_f64 r) {
  lm2_r4_u8 result = {
      {lm2_v4_f64_to_u8(r.min), lm2_v4_f64_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range4 Conversions - from f32
// =============================================================================

LM2_API lm2_r4_f64 lm2_r4_f32_to_f64(lm2_r4_f32 r) {
  lm2_r4_f64 result = {
      {lm2_v4_f32_to_f64(r.min), lm2_v4_f32_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i64 lm2_r4_f32_to_i64(lm2_r4_f32 r) {
  lm2_r4_i64 result = {
      {lm2_v4_f32_to_i64(r.min), lm2_v4_f32_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i32 lm2_r4_f32_to_i32(lm2_r4_f32 r) {
  lm2_r4_i32 result = {
      {lm2_v4_f32_to_i32(r.min), lm2_v4_f32_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i16 lm2_r4_f32_to_i16(lm2_r4_f32 r) {
  lm2_r4_i16 result = {
      {lm2_v4_f32_to_i16(r.min), lm2_v4_f32_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i8 lm2_r4_f32_to_i8(lm2_r4_f32 r) {
  lm2_r4_i8 result = {
      {lm2_v4_f32_to_i8(r.min), lm2_v4_f32_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u64 lm2_r4_f32_to_u64(lm2_r4_f32 r) {
  lm2_r4_u64 result = {
      {lm2_v4_f32_to_u64(r.min), lm2_v4_f32_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u32 lm2_r4_f32_to_u32(lm2_r4_f32 r) {
  lm2_r4_u32 result = {
      {lm2_v4_f32_to_u32(r.min), lm2_v4_f32_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u16 lm2_r4_f32_to_u16(lm2_r4_f32 r) {
  lm2_r4_u16 result = {
      {lm2_v4_f32_to_u16(r.min), lm2_v4_f32_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u8 lm2_r4_f32_to_u8(lm2_r4_f32 r) {
  lm2_r4_u8 result = {
      {lm2_v4_f32_to_u8(r.min), lm2_v4_f32_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range4 Conversions - from i64
// =============================================================================

LM2_API lm2_r4_f64 lm2_r4_i64_to_f64(lm2_r4_i64 r) {
  lm2_r4_f64 result = {
      {lm2_v4_i64_to_f64(r.min), lm2_v4_i64_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_f32 lm2_r4_i64_to_f32(lm2_r4_i64 r) {
  lm2_r4_f32 result = {
      {lm2_v4_i64_to_f32(r.min), lm2_v4_i64_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i32 lm2_r4_i64_to_i32(lm2_r4_i64 r) {
  lm2_r4_i32 result = {
      {lm2_v4_i64_to_i32(r.min), lm2_v4_i64_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i16 lm2_r4_i64_to_i16(lm2_r4_i64 r) {
  lm2_r4_i16 result = {
      {lm2_v4_i64_to_i16(r.min), lm2_v4_i64_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i8 lm2_r4_i64_to_i8(lm2_r4_i64 r) {
  lm2_r4_i8 result = {
      {lm2_v4_i64_to_i8(r.min), lm2_v4_i64_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u64 lm2_r4_i64_to_u64(lm2_r4_i64 r) {
  lm2_r4_u64 result = {
      {lm2_v4_i64_to_u64(r.min), lm2_v4_i64_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u32 lm2_r4_i64_to_u32(lm2_r4_i64 r) {
  lm2_r4_u32 result = {
      {lm2_v4_i64_to_u32(r.min), lm2_v4_i64_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u16 lm2_r4_i64_to_u16(lm2_r4_i64 r) {
  lm2_r4_u16 result = {
      {lm2_v4_i64_to_u16(r.min), lm2_v4_i64_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u8 lm2_r4_i64_to_u8(lm2_r4_i64 r) {
  lm2_r4_u8 result = {
      {lm2_v4_i64_to_u8(r.min), lm2_v4_i64_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range4 Conversions - from i32
// =============================================================================

LM2_API lm2_r4_f64 lm2_r4_i32_to_f64(lm2_r4_i32 r) {
  lm2_r4_f64 result = {
      {lm2_v4_i32_to_f64(r.min), lm2_v4_i32_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_f32 lm2_r4_i32_to_f32(lm2_r4_i32 r) {
  lm2_r4_f32 result = {
      {lm2_v4_i32_to_f32(r.min), lm2_v4_i32_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i64 lm2_r4_i32_to_i64(lm2_r4_i32 r) {
  lm2_r4_i64 result = {
      {lm2_v4_i32_to_i64(r.min), lm2_v4_i32_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i16 lm2_r4_i32_to_i16(lm2_r4_i32 r) {
  lm2_r4_i16 result = {
      {lm2_v4_i32_to_i16(r.min), lm2_v4_i32_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i8 lm2_r4_i32_to_i8(lm2_r4_i32 r) {
  lm2_r4_i8 result = {
      {lm2_v4_i32_to_i8(r.min), lm2_v4_i32_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u64 lm2_r4_i32_to_u64(lm2_r4_i32 r) {
  lm2_r4_u64 result = {
      {lm2_v4_i32_to_u64(r.min), lm2_v4_i32_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u32 lm2_r4_i32_to_u32(lm2_r4_i32 r) {
  lm2_r4_u32 result = {
      {lm2_v4_i32_to_u32(r.min), lm2_v4_i32_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u16 lm2_r4_i32_to_u16(lm2_r4_i32 r) {
  lm2_r4_u16 result = {
      {lm2_v4_i32_to_u16(r.min), lm2_v4_i32_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u8 lm2_r4_i32_to_u8(lm2_r4_i32 r) {
  lm2_r4_u8 result = {
      {lm2_v4_i32_to_u8(r.min), lm2_v4_i32_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range4 Conversions - from i16
// =============================================================================

LM2_API lm2_r4_f64 lm2_r4_i16_to_f64(lm2_r4_i16 r) {
  lm2_r4_f64 result = {
      {lm2_v4_i16_to_f64(r.min), lm2_v4_i16_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_f32 lm2_r4_i16_to_f32(lm2_r4_i16 r) {
  lm2_r4_f32 result = {
      {lm2_v4_i16_to_f32(r.min), lm2_v4_i16_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i64 lm2_r4_i16_to_i64(lm2_r4_i16 r) {
  lm2_r4_i64 result = {
      {lm2_v4_i16_to_i64(r.min), lm2_v4_i16_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i32 lm2_r4_i16_to_i32(lm2_r4_i16 r) {
  lm2_r4_i32 result = {
      {lm2_v4_i16_to_i32(r.min), lm2_v4_i16_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i8 lm2_r4_i16_to_i8(lm2_r4_i16 r) {
  lm2_r4_i8 result = {
      {lm2_v4_i16_to_i8(r.min), lm2_v4_i16_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u64 lm2_r4_i16_to_u64(lm2_r4_i16 r) {
  lm2_r4_u64 result = {
      {lm2_v4_i16_to_u64(r.min), lm2_v4_i16_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u32 lm2_r4_i16_to_u32(lm2_r4_i16 r) {
  lm2_r4_u32 result = {
      {lm2_v4_i16_to_u32(r.min), lm2_v4_i16_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u16 lm2_r4_i16_to_u16(lm2_r4_i16 r) {
  lm2_r4_u16 result = {
      {lm2_v4_i16_to_u16(r.min), lm2_v4_i16_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u8 lm2_r4_i16_to_u8(lm2_r4_i16 r) {
  lm2_r4_u8 result = {
      {lm2_v4_i16_to_u8(r.min), lm2_v4_i16_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range4 Conversions - from i8
// =============================================================================

LM2_API lm2_r4_f64 lm2_r4_i8_to_f64(lm2_r4_i8 r) {
  lm2_r4_f64 result = {
      {lm2_v4_i8_to_f64(r.min), lm2_v4_i8_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_f32 lm2_r4_i8_to_f32(lm2_r4_i8 r) {
  lm2_r4_f32 result = {
      {lm2_v4_i8_to_f32(r.min), lm2_v4_i8_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i64 lm2_r4_i8_to_i64(lm2_r4_i8 r) {
  lm2_r4_i64 result = {
      {lm2_v4_i8_to_i64(r.min), lm2_v4_i8_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i32 lm2_r4_i8_to_i32(lm2_r4_i8 r) {
  lm2_r4_i32 result = {
      {lm2_v4_i8_to_i32(r.min), lm2_v4_i8_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i16 lm2_r4_i8_to_i16(lm2_r4_i8 r) {
  lm2_r4_i16 result = {
      {lm2_v4_i8_to_i16(r.min), lm2_v4_i8_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u64 lm2_r4_i8_to_u64(lm2_r4_i8 r) {
  lm2_r4_u64 result = {
      {lm2_v4_i8_to_u64(r.min), lm2_v4_i8_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u32 lm2_r4_i8_to_u32(lm2_r4_i8 r) {
  lm2_r4_u32 result = {
      {lm2_v4_i8_to_u32(r.min), lm2_v4_i8_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u16 lm2_r4_i8_to_u16(lm2_r4_i8 r) {
  lm2_r4_u16 result = {
      {lm2_v4_i8_to_u16(r.min), lm2_v4_i8_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u8 lm2_r4_i8_to_u8(lm2_r4_i8 r) {
  lm2_r4_u8 result = {
      {lm2_v4_i8_to_u8(r.min), lm2_v4_i8_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range4 Conversions - from u64
// =============================================================================

LM2_API lm2_r4_f64 lm2_r4_u64_to_f64(lm2_r4_u64 r) {
  lm2_r4_f64 result = {
      {lm2_v4_u64_to_f64(r.min), lm2_v4_u64_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_f32 lm2_r4_u64_to_f32(lm2_r4_u64 r) {
  lm2_r4_f32 result = {
      {lm2_v4_u64_to_f32(r.min), lm2_v4_u64_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i64 lm2_r4_u64_to_i64(lm2_r4_u64 r) {
  lm2_r4_i64 result = {
      {lm2_v4_u64_to_i64(r.min), lm2_v4_u64_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i32 lm2_r4_u64_to_i32(lm2_r4_u64 r) {
  lm2_r4_i32 result = {
      {lm2_v4_u64_to_i32(r.min), lm2_v4_u64_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i16 lm2_r4_u64_to_i16(lm2_r4_u64 r) {
  lm2_r4_i16 result = {
      {lm2_v4_u64_to_i16(r.min), lm2_v4_u64_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i8 lm2_r4_u64_to_i8(lm2_r4_u64 r) {
  lm2_r4_i8 result = {
      {lm2_v4_u64_to_i8(r.min), lm2_v4_u64_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u32 lm2_r4_u64_to_u32(lm2_r4_u64 r) {
  lm2_r4_u32 result = {
      {lm2_v4_u64_to_u32(r.min), lm2_v4_u64_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u16 lm2_r4_u64_to_u16(lm2_r4_u64 r) {
  lm2_r4_u16 result = {
      {lm2_v4_u64_to_u16(r.min), lm2_v4_u64_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u8 lm2_r4_u64_to_u8(lm2_r4_u64 r) {
  lm2_r4_u8 result = {
      {lm2_v4_u64_to_u8(r.min), lm2_v4_u64_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range4 Conversions - from u32
// =============================================================================

LM2_API lm2_r4_f64 lm2_r4_u32_to_f64(lm2_r4_u32 r) {
  lm2_r4_f64 result = {
      {lm2_v4_u32_to_f64(r.min), lm2_v4_u32_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_f32 lm2_r4_u32_to_f32(lm2_r4_u32 r) {
  lm2_r4_f32 result = {
      {lm2_v4_u32_to_f32(r.min), lm2_v4_u32_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i64 lm2_r4_u32_to_i64(lm2_r4_u32 r) {
  lm2_r4_i64 result = {
      {lm2_v4_u32_to_i64(r.min), lm2_v4_u32_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i32 lm2_r4_u32_to_i32(lm2_r4_u32 r) {
  lm2_r4_i32 result = {
      {lm2_v4_u32_to_i32(r.min), lm2_v4_u32_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i16 lm2_r4_u32_to_i16(lm2_r4_u32 r) {
  lm2_r4_i16 result = {
      {lm2_v4_u32_to_i16(r.min), lm2_v4_u32_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i8 lm2_r4_u32_to_i8(lm2_r4_u32 r) {
  lm2_r4_i8 result = {
      {lm2_v4_u32_to_i8(r.min), lm2_v4_u32_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u64 lm2_r4_u32_to_u64(lm2_r4_u32 r) {
  lm2_r4_u64 result = {
      {lm2_v4_u32_to_u64(r.min), lm2_v4_u32_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u16 lm2_r4_u32_to_u16(lm2_r4_u32 r) {
  lm2_r4_u16 result = {
      {lm2_v4_u32_to_u16(r.min), lm2_v4_u32_to_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u8 lm2_r4_u32_to_u8(lm2_r4_u32 r) {
  lm2_r4_u8 result = {
      {lm2_v4_u32_to_u8(r.min), lm2_v4_u32_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range4 Conversions - from u16
// =============================================================================

LM2_API lm2_r4_f64 lm2_r4_u16_to_f64(lm2_r4_u16 r) {
  lm2_r4_f64 result = {
      {lm2_v4_u16_to_f64(r.min), lm2_v4_u16_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_f32 lm2_r4_u16_to_f32(lm2_r4_u16 r) {
  lm2_r4_f32 result = {
      {lm2_v4_u16_to_f32(r.min), lm2_v4_u16_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i64 lm2_r4_u16_to_i64(lm2_r4_u16 r) {
  lm2_r4_i64 result = {
      {lm2_v4_u16_to_i64(r.min), lm2_v4_u16_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i32 lm2_r4_u16_to_i32(lm2_r4_u16 r) {
  lm2_r4_i32 result = {
      {lm2_v4_u16_to_i32(r.min), lm2_v4_u16_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i16 lm2_r4_u16_to_i16(lm2_r4_u16 r) {
  lm2_r4_i16 result = {
      {lm2_v4_u16_to_i16(r.min), lm2_v4_u16_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i8 lm2_r4_u16_to_i8(lm2_r4_u16 r) {
  lm2_r4_i8 result = {
      {lm2_v4_u16_to_i8(r.min), lm2_v4_u16_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u64 lm2_r4_u16_to_u64(lm2_r4_u16 r) {
  lm2_r4_u64 result = {
      {lm2_v4_u16_to_u64(r.min), lm2_v4_u16_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u32 lm2_r4_u16_to_u32(lm2_r4_u16 r) {
  lm2_r4_u32 result = {
      {lm2_v4_u16_to_u32(r.min), lm2_v4_u16_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u8 lm2_r4_u16_to_u8(lm2_r4_u16 r) {
  lm2_r4_u8 result = {
      {lm2_v4_u16_to_u8(r.min), lm2_v4_u16_to_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range4 Conversions - from u8
// =============================================================================

LM2_API lm2_r4_f64 lm2_r4_u8_to_f64(lm2_r4_u8 r) {
  lm2_r4_f64 result = {
      {lm2_v4_u8_to_f64(r.min), lm2_v4_u8_to_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_f32 lm2_r4_u8_to_f32(lm2_r4_u8 r) {
  lm2_r4_f32 result = {
      {lm2_v4_u8_to_f32(r.min), lm2_v4_u8_to_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i64 lm2_r4_u8_to_i64(lm2_r4_u8 r) {
  lm2_r4_i64 result = {
      {lm2_v4_u8_to_i64(r.min), lm2_v4_u8_to_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i32 lm2_r4_u8_to_i32(lm2_r4_u8 r) {
  lm2_r4_i32 result = {
      {lm2_v4_u8_to_i32(r.min), lm2_v4_u8_to_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i16 lm2_r4_u8_to_i16(lm2_r4_u8 r) {
  lm2_r4_i16 result = {
      {lm2_v4_u8_to_i16(r.min), lm2_v4_u8_to_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r4_i8 lm2_r4_u8_to_i8(lm2_r4_u8 r) {
  lm2_r4_i8 result = {
      {lm2_v4_u8_to_i8(r.min), lm2_v4_u8_to_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u64 lm2_r4_u8_to_u64(lm2_r4_u8 r) {
  lm2_r4_u64 result = {
      {lm2_v4_u8_to_u64(r.min), lm2_v4_u8_to_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u32 lm2_r4_u8_to_u32(lm2_r4_u8 r) {
  lm2_r4_u32 result = {
      {lm2_v4_u8_to_u32(r.min), lm2_v4_u8_to_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r4_u16 lm2_r4_u8_to_u16(lm2_r4_u8 r) {
  lm2_r4_u16 result = {
      {lm2_v4_u8_to_u16(r.min), lm2_v4_u8_to_u16(r.max)}
  };
  return result;
}

// =============================================================================
// Range Upcast Functions (r2 -> r3)
// =============================================================================

LM2_API lm2_r3_f64 lm2_r2_upcast_f64(lm2_r2_f64 r, double z_min, double z_max) {
  lm2_r3_f64 result = {
      {lm2_v2_upcast_f64(r.min, z_min), lm2_v2_upcast_f64(r.max, z_max)}
  };
  return result;
}

LM2_API lm2_r3_f32 lm2_r2_upcast_f32(lm2_r2_f32 r, float z_min, float z_max) {
  lm2_r3_f32 result = {
      {lm2_v2_upcast_f32(r.min, z_min), lm2_v2_upcast_f32(r.max, z_max)}
  };
  return result;
}

LM2_API lm2_r3_i64 lm2_r2_upcast_i64(lm2_r2_i64 r, int64_t z_min, int64_t z_max) {
  lm2_r3_i64 result = {
      {lm2_v2_upcast_i64(r.min, z_min), lm2_v2_upcast_i64(r.max, z_max)}
  };
  return result;
}

LM2_API lm2_r3_i32 lm2_r2_upcast_i32(lm2_r2_i32 r, int32_t z_min, int32_t z_max) {
  lm2_r3_i32 result = {
      {lm2_v2_upcast_i32(r.min, z_min), lm2_v2_upcast_i32(r.max, z_max)}
  };
  return result;
}

LM2_API lm2_r3_i16 lm2_r2_upcast_i16(lm2_r2_i16 r, int16_t z_min, int16_t z_max) {
  lm2_r3_i16 result = {
      {lm2_v2_upcast_i16(r.min, z_min), lm2_v2_upcast_i16(r.max, z_max)}
  };
  return result;
}

LM2_API lm2_r3_i8 lm2_r2_upcast_i8(lm2_r2_i8 r, int8_t z_min, int8_t z_max) {
  lm2_r3_i8 result = {
      {lm2_v2_upcast_i8(r.min, z_min), lm2_v2_upcast_i8(r.max, z_max)}
  };
  return result;
}

LM2_API lm2_r3_u64 lm2_r2_upcast_u64(lm2_r2_u64 r, uint64_t z_min, uint64_t z_max) {
  lm2_r3_u64 result = {
      {lm2_v2_upcast_u64(r.min, z_min), lm2_v2_upcast_u64(r.max, z_max)}
  };
  return result;
}

LM2_API lm2_r3_u32 lm2_r2_upcast_u32(lm2_r2_u32 r, uint32_t z_min, uint32_t z_max) {
  lm2_r3_u32 result = {
      {lm2_v2_upcast_u32(r.min, z_min), lm2_v2_upcast_u32(r.max, z_max)}
  };
  return result;
}

LM2_API lm2_r3_u16 lm2_r2_upcast_u16(lm2_r2_u16 r, uint16_t z_min, uint16_t z_max) {
  lm2_r3_u16 result = {
      {lm2_v2_upcast_u16(r.min, z_min), lm2_v2_upcast_u16(r.max, z_max)}
  };
  return result;
}

LM2_API lm2_r3_u8 lm2_r2_upcast_u8(lm2_r2_u8 r, uint8_t z_min, uint8_t z_max) {
  lm2_r3_u8 result = {
      {lm2_v2_upcast_u8(r.min, z_min), lm2_v2_upcast_u8(r.max, z_max)}
  };
  return result;
}

// =============================================================================
// Range Upcast Functions (r3 -> r4)
// =============================================================================

LM2_API lm2_r4_f64 lm2_r3_upcast_f64(lm2_r3_f64 r, double w_min, double w_max) {
  lm2_r4_f64 result = {
      {lm2_v3_upcast_f64(r.min, w_min), lm2_v3_upcast_f64(r.max, w_max)}
  };
  return result;
}

LM2_API lm2_r4_f32 lm2_r3_upcast_f32(lm2_r3_f32 r, float w_min, float w_max) {
  lm2_r4_f32 result = {
      {lm2_v3_upcast_f32(r.min, w_min), lm2_v3_upcast_f32(r.max, w_max)}
  };
  return result;
}

LM2_API lm2_r4_i64 lm2_r3_upcast_i64(lm2_r3_i64 r, int64_t w_min, int64_t w_max) {
  lm2_r4_i64 result = {
      {lm2_v3_upcast_i64(r.min, w_min), lm2_v3_upcast_i64(r.max, w_max)}
  };
  return result;
}

LM2_API lm2_r4_i32 lm2_r3_upcast_i32(lm2_r3_i32 r, int32_t w_min, int32_t w_max) {
  lm2_r4_i32 result = {
      {lm2_v3_upcast_i32(r.min, w_min), lm2_v3_upcast_i32(r.max, w_max)}
  };
  return result;
}

LM2_API lm2_r4_i16 lm2_r3_upcast_i16(lm2_r3_i16 r, int16_t w_min, int16_t w_max) {
  lm2_r4_i16 result = {
      {lm2_v3_upcast_i16(r.min, w_min), lm2_v3_upcast_i16(r.max, w_max)}
  };
  return result;
}

LM2_API lm2_r4_i8 lm2_r3_upcast_i8(lm2_r3_i8 r, int8_t w_min, int8_t w_max) {
  lm2_r4_i8 result = {
      {lm2_v3_upcast_i8(r.min, w_min), lm2_v3_upcast_i8(r.max, w_max)}
  };
  return result;
}

LM2_API lm2_r4_u64 lm2_r3_upcast_u64(lm2_r3_u64 r, uint64_t w_min, uint64_t w_max) {
  lm2_r4_u64 result = {
      {lm2_v3_upcast_u64(r.min, w_min), lm2_v3_upcast_u64(r.max, w_max)}
  };
  return result;
}

LM2_API lm2_r4_u32 lm2_r3_upcast_u32(lm2_r3_u32 r, uint32_t w_min, uint32_t w_max) {
  lm2_r4_u32 result = {
      {lm2_v3_upcast_u32(r.min, w_min), lm2_v3_upcast_u32(r.max, w_max)}
  };
  return result;
}

LM2_API lm2_r4_u16 lm2_r3_upcast_u16(lm2_r3_u16 r, uint16_t w_min, uint16_t w_max) {
  lm2_r4_u16 result = {
      {lm2_v3_upcast_u16(r.min, w_min), lm2_v3_upcast_u16(r.max, w_max)}
  };
  return result;
}

LM2_API lm2_r4_u8 lm2_r3_upcast_u8(lm2_r3_u8 r, uint8_t w_min, uint8_t w_max) {
  lm2_r4_u8 result = {
      {lm2_v3_upcast_u8(r.min, w_min), lm2_v3_upcast_u8(r.max, w_max)}
  };
  return result;
}

// =============================================================================
// Range Downcast Functions (r3 -> r2)
// =============================================================================

LM2_API lm2_r2_f64 lm2_r3_downcast_f64(lm2_r3_f64 r) {
  lm2_r2_f64 result = {
      {lm2_v3_downcast_f64(r.min), lm2_v3_downcast_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_f32 lm2_r3_downcast_f32(lm2_r3_f32 r) {
  lm2_r2_f32 result = {
      {lm2_v3_downcast_f32(r.min), lm2_v3_downcast_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i64 lm2_r3_downcast_i64(lm2_r3_i64 r) {
  lm2_r2_i64 result = {
      {lm2_v3_downcast_i64(r.min), lm2_v3_downcast_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i32 lm2_r3_downcast_i32(lm2_r3_i32 r) {
  lm2_r2_i32 result = {
      {lm2_v3_downcast_i32(r.min), lm2_v3_downcast_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i16 lm2_r3_downcast_i16(lm2_r3_i16 r) {
  lm2_r2_i16 result = {
      {lm2_v3_downcast_i16(r.min), lm2_v3_downcast_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r2_i8 lm2_r3_downcast_i8(lm2_r3_i8 r) {
  lm2_r2_i8 result = {
      {lm2_v3_downcast_i8(r.min), lm2_v3_downcast_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u64 lm2_r3_downcast_u64(lm2_r3_u64 r) {
  lm2_r2_u64 result = {
      {lm2_v3_downcast_u64(r.min), lm2_v3_downcast_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u32 lm2_r3_downcast_u32(lm2_r3_u32 r) {
  lm2_r2_u32 result = {
      {lm2_v3_downcast_u32(r.min), lm2_v3_downcast_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u16 lm2_r3_downcast_u16(lm2_r3_u16 r) {
  lm2_r2_u16 result = {
      {lm2_v3_downcast_u16(r.min), lm2_v3_downcast_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r2_u8 lm2_r3_downcast_u8(lm2_r3_u8 r) {
  lm2_r2_u8 result = {
      {lm2_v3_downcast_u8(r.min), lm2_v3_downcast_u8(r.max)}
  };
  return result;
}

// =============================================================================
// Range Downcast Functions (r4 -> r3)
// =============================================================================

LM2_API lm2_r3_f64 lm2_r4_downcast_f64(lm2_r4_f64 r) {
  lm2_r3_f64 result = {
      {lm2_v4_downcast_f64(r.min), lm2_v4_downcast_f64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_f32 lm2_r4_downcast_f32(lm2_r4_f32 r) {
  lm2_r3_f32 result = {
      {lm2_v4_downcast_f32(r.min), lm2_v4_downcast_f32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i64 lm2_r4_downcast_i64(lm2_r4_i64 r) {
  lm2_r3_i64 result = {
      {lm2_v4_downcast_i64(r.min), lm2_v4_downcast_i64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i32 lm2_r4_downcast_i32(lm2_r4_i32 r) {
  lm2_r3_i32 result = {
      {lm2_v4_downcast_i32(r.min), lm2_v4_downcast_i32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i16 lm2_r4_downcast_i16(lm2_r4_i16 r) {
  lm2_r3_i16 result = {
      {lm2_v4_downcast_i16(r.min), lm2_v4_downcast_i16(r.max)}
  };
  return result;
}

LM2_API lm2_r3_i8 lm2_r4_downcast_i8(lm2_r4_i8 r) {
  lm2_r3_i8 result = {
      {lm2_v4_downcast_i8(r.min), lm2_v4_downcast_i8(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u64 lm2_r4_downcast_u64(lm2_r4_u64 r) {
  lm2_r3_u64 result = {
      {lm2_v4_downcast_u64(r.min), lm2_v4_downcast_u64(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u32 lm2_r4_downcast_u32(lm2_r4_u32 r) {
  lm2_r3_u32 result = {
      {lm2_v4_downcast_u32(r.min), lm2_v4_downcast_u32(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u16 lm2_r4_downcast_u16(lm2_r4_u16 r) {
  lm2_r3_u16 result = {
      {lm2_v4_downcast_u16(r.min), lm2_v4_downcast_u16(r.max)}
  };
  return result;
}

LM2_API lm2_r3_u8 lm2_r4_downcast_u8(lm2_r4_u8 r) {
  lm2_r3_u8 result = {
      {lm2_v4_downcast_u8(r.min), lm2_v4_downcast_u8(r.max)}
  };
  return result;
}
