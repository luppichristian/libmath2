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

#include <lm2/vectors/lm2_vector_conversions.h>
#include <lm2/lm2_base.h>

// =============================================================================
// Vector2 Conversions - from f64
// =============================================================================

LM2_API lm2_v2_f32 lm2_v2_f64_to_f32(lm2_v2_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= -FLT_MAX && v.x <= FLT_MAX);
  LM2_ASSERT_UNSAFE(v.y >= -FLT_MAX && v.y <= FLT_MAX);
  lm2_v2_f32 result = {
      {(float)v.x, (float)v.y}
  };
  return result;
}

LM2_API lm2_v2_i64 lm2_v2_f64_to_i64(lm2_v2_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= (double)INT64_MIN && v.x <= (double)INT64_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (double)INT64_MIN && v.y <= (double)INT64_MAX);
  lm2_v2_i64 result = {
      {(int64_t)v.x, (int64_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i32 lm2_v2_f64_to_i32(lm2_v2_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= (double)INT32_MIN && v.x <= (double)INT32_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (double)INT32_MIN && v.y <= (double)INT32_MAX);
  lm2_v2_i32 result = {
      {(int32_t)v.x, (int32_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i16 lm2_v2_f64_to_i16(lm2_v2_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= (double)INT16_MIN && v.x <= (double)INT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (double)INT16_MIN && v.y <= (double)INT16_MAX);
  lm2_v2_i16 result = {
      {(int16_t)v.x, (int16_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i8 lm2_v2_f64_to_i8(lm2_v2_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= (double)INT8_MIN && v.x <= (double)INT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (double)INT8_MIN && v.y <= (double)INT8_MAX);
  lm2_v2_i8 result = {
      {(int8_t)v.x, (int8_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u64 lm2_v2_f64_to_u64(lm2_v2_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0 && v.x <= (double)UINT64_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0 && v.y <= (double)UINT64_MAX);
  lm2_v2_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u32 lm2_v2_f64_to_u32(lm2_v2_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0 && v.x <= (double)UINT32_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0 && v.y <= (double)UINT32_MAX);
  lm2_v2_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u16 lm2_v2_f64_to_u16(lm2_v2_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0 && v.x <= (double)UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0 && v.y <= (double)UINT16_MAX);
  lm2_v2_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u8 lm2_v2_f64_to_u8(lm2_v2_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0 && v.x <= (double)UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0 && v.y <= (double)UINT8_MAX);
  lm2_v2_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y}
  };
  return result;
}

// =============================================================================
// Vector2 Conversions - from f32
// =============================================================================

LM2_API lm2_v2_f64 lm2_v2_f32_to_f64(lm2_v2_f32 v) {
  lm2_v2_f64 result = {
      {(double)v.x, (double)v.y}
  };
  return result;
}

LM2_API lm2_v2_i64 lm2_v2_f32_to_i64(lm2_v2_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= (float)INT64_MIN && v.x <= (float)INT64_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (float)INT64_MIN && v.y <= (float)INT64_MAX);
  lm2_v2_i64 result = {
      {(int64_t)v.x, (int64_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i32 lm2_v2_f32_to_i32(lm2_v2_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= (float)INT32_MIN && v.x <= (float)INT32_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (float)INT32_MIN && v.y <= (float)INT32_MAX);
  lm2_v2_i32 result = {
      {(int32_t)v.x, (int32_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i16 lm2_v2_f32_to_i16(lm2_v2_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= (float)INT16_MIN && v.x <= (float)INT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (float)INT16_MIN && v.y <= (float)INT16_MAX);
  lm2_v2_i16 result = {
      {(int16_t)v.x, (int16_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i8 lm2_v2_f32_to_i8(lm2_v2_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= (float)INT8_MIN && v.x <= (float)INT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (float)INT8_MIN && v.y <= (float)INT8_MAX);
  lm2_v2_i8 result = {
      {(int8_t)v.x, (int8_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u64 lm2_v2_f32_to_u64(lm2_v2_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0f && v.x <= (float)UINT64_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0f && v.y <= (float)UINT64_MAX);
  lm2_v2_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u32 lm2_v2_f32_to_u32(lm2_v2_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0f && v.x <= (float)UINT32_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0f && v.y <= (float)UINT32_MAX);
  lm2_v2_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u16 lm2_v2_f32_to_u16(lm2_v2_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0f && v.x <= (float)UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0f && v.y <= (float)UINT16_MAX);
  lm2_v2_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u8 lm2_v2_f32_to_u8(lm2_v2_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0f && v.x <= (float)UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0f && v.y <= (float)UINT8_MAX);
  lm2_v2_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y}
  };
  return result;
}

// =============================================================================
// Vector2 Conversions - from i64
// =============================================================================

LM2_API lm2_v2_f64 lm2_v2_i64_to_f64(lm2_v2_i64 v) {
  lm2_v2_f64 result = {
      {(double)v.x, (double)v.y}
  };
  return result;
}

LM2_API lm2_v2_f32 lm2_v2_i64_to_f32(lm2_v2_i64 v) {
  lm2_v2_f32 result = {
      {(float)v.x, (float)v.y}
  };
  return result;
}

LM2_API lm2_v2_i32 lm2_v2_i64_to_i32(lm2_v2_i64 v) {
  LM2_ASSERT_UNSAFE(v.x >= INT32_MIN && v.x <= INT32_MAX);
  LM2_ASSERT_UNSAFE(v.y >= INT32_MIN && v.y <= INT32_MAX);
  lm2_v2_i32 result = {
      {(int32_t)v.x, (int32_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i16 lm2_v2_i64_to_i16(lm2_v2_i64 v) {
  LM2_ASSERT_UNSAFE(v.x >= INT16_MIN && v.x <= INT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= INT16_MIN && v.y <= INT16_MAX);
  lm2_v2_i16 result = {
      {(int16_t)v.x, (int16_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i8 lm2_v2_i64_to_i8(lm2_v2_i64 v) {
  LM2_ASSERT_UNSAFE(v.x >= INT8_MIN && v.x <= INT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= INT8_MIN && v.y <= INT8_MAX);
  lm2_v2_i8 result = {
      {(int8_t)v.x, (int8_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u64 lm2_v2_i64_to_u64(lm2_v2_i64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0);
  lm2_v2_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u32 lm2_v2_i64_to_u32(lm2_v2_i64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.x <= UINT32_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0 && v.y <= UINT32_MAX);
  lm2_v2_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u16 lm2_v2_i64_to_u16(lm2_v2_i64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.x <= UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0 && v.y <= UINT16_MAX);
  lm2_v2_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u8 lm2_v2_i64_to_u8(lm2_v2_i64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.x <= UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0 && v.y <= UINT8_MAX);
  lm2_v2_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y}
  };
  return result;
}

// =============================================================================
// Vector2 Conversions - from i32
// =============================================================================

LM2_API lm2_v2_f64 lm2_v2_i32_to_f64(lm2_v2_i32 v) {
  lm2_v2_f64 result = {
      {(double)v.x, (double)v.y}
  };
  return result;
}

LM2_API lm2_v2_f32 lm2_v2_i32_to_f32(lm2_v2_i32 v) {
  lm2_v2_f32 result = {
      {(float)v.x, (float)v.y}
  };
  return result;
}

LM2_API lm2_v2_i64 lm2_v2_i32_to_i64(lm2_v2_i32 v) {
  lm2_v2_i64 result = {
      {(int64_t)v.x, (int64_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i16 lm2_v2_i32_to_i16(lm2_v2_i32 v) {
  LM2_ASSERT_UNSAFE(v.x >= INT16_MIN && v.x <= INT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= INT16_MIN && v.y <= INT16_MAX);
  lm2_v2_i16 result = {
      {(int16_t)v.x, (int16_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i8 lm2_v2_i32_to_i8(lm2_v2_i32 v) {
  LM2_ASSERT_UNSAFE(v.x >= INT8_MIN && v.x <= INT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= INT8_MIN && v.y <= INT8_MAX);
  lm2_v2_i8 result = {
      {(int8_t)v.x, (int8_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u64 lm2_v2_i32_to_u64(lm2_v2_i32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0);
  lm2_v2_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u32 lm2_v2_i32_to_u32(lm2_v2_i32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0);
  lm2_v2_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u16 lm2_v2_i32_to_u16(lm2_v2_i32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.x <= UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0 && v.y <= UINT16_MAX);
  lm2_v2_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u8 lm2_v2_i32_to_u8(lm2_v2_i32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.x <= UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0 && v.y <= UINT8_MAX);
  lm2_v2_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y}
  };
  return result;
}

// =============================================================================
// Vector2 Conversions - from i16
// =============================================================================

LM2_API lm2_v2_f64 lm2_v2_i16_to_f64(lm2_v2_i16 v) {
  lm2_v2_f64 result = {
      {(double)v.x, (double)v.y}
  };
  return result;
}

LM2_API lm2_v2_f32 lm2_v2_i16_to_f32(lm2_v2_i16 v) {
  lm2_v2_f32 result = {
      {(float)v.x, (float)v.y}
  };
  return result;
}

LM2_API lm2_v2_i64 lm2_v2_i16_to_i64(lm2_v2_i16 v) {
  lm2_v2_i64 result = {
      {(int64_t)v.x, (int64_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i32 lm2_v2_i16_to_i32(lm2_v2_i16 v) {
  lm2_v2_i32 result = {
      {(int32_t)v.x, (int32_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i8 lm2_v2_i16_to_i8(lm2_v2_i16 v) {
  LM2_ASSERT_UNSAFE(v.x >= INT8_MIN && v.x <= INT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= INT8_MIN && v.y <= INT8_MAX);
  lm2_v2_i8 result = {
      {(int8_t)v.x, (int8_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u64 lm2_v2_i16_to_u64(lm2_v2_i16 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0);
  lm2_v2_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u32 lm2_v2_i16_to_u32(lm2_v2_i16 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0);
  lm2_v2_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u16 lm2_v2_i16_to_u16(lm2_v2_i16 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0);
  lm2_v2_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u8 lm2_v2_i16_to_u8(lm2_v2_i16 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.x <= UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0 && v.y <= UINT8_MAX);
  lm2_v2_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y}
  };
  return result;
}

// =============================================================================
// Vector2 Conversions - from i8
// =============================================================================

LM2_API lm2_v2_f64 lm2_v2_i8_to_f64(lm2_v2_i8 v) {
  lm2_v2_f64 result = {
      {(double)v.x, (double)v.y}
  };
  return result;
}

LM2_API lm2_v2_f32 lm2_v2_i8_to_f32(lm2_v2_i8 v) {
  lm2_v2_f32 result = {
      {(float)v.x, (float)v.y}
  };
  return result;
}

LM2_API lm2_v2_i64 lm2_v2_i8_to_i64(lm2_v2_i8 v) {
  lm2_v2_i64 result = {
      {(int64_t)v.x, (int64_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i32 lm2_v2_i8_to_i32(lm2_v2_i8 v) {
  lm2_v2_i32 result = {
      {(int32_t)v.x, (int32_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i16 lm2_v2_i8_to_i16(lm2_v2_i8 v) {
  lm2_v2_i16 result = {
      {(int16_t)v.x, (int16_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u64 lm2_v2_i8_to_u64(lm2_v2_i8 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0);
  lm2_v2_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u32 lm2_v2_i8_to_u32(lm2_v2_i8 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0);
  lm2_v2_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u16 lm2_v2_i8_to_u16(lm2_v2_i8 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0);
  lm2_v2_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u8 lm2_v2_i8_to_u8(lm2_v2_i8 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0);
  lm2_v2_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y}
  };
  return result;
}

// =============================================================================
// Vector2 Conversions - from u64
// =============================================================================

LM2_API lm2_v2_f64 lm2_v2_u64_to_f64(lm2_v2_u64 v) {
  lm2_v2_f64 result = {
      {(double)v.x, (double)v.y}
  };
  return result;
}

LM2_API lm2_v2_f32 lm2_v2_u64_to_f32(lm2_v2_u64 v) {
  lm2_v2_f32 result = {
      {(float)v.x, (float)v.y}
  };
  return result;
}

LM2_API lm2_v2_i64 lm2_v2_u64_to_i64(lm2_v2_u64 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT64_MAX && v.y <= INT64_MAX);
  lm2_v2_i64 result = {
      {(int64_t)v.x, (int64_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i32 lm2_v2_u64_to_i32(lm2_v2_u64 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT32_MAX && v.y <= INT32_MAX);
  lm2_v2_i32 result = {
      {(int32_t)v.x, (int32_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i16 lm2_v2_u64_to_i16(lm2_v2_u64 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT16_MAX && v.y <= INT16_MAX);
  lm2_v2_i16 result = {
      {(int16_t)v.x, (int16_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i8 lm2_v2_u64_to_i8(lm2_v2_u64 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT8_MAX && v.y <= INT8_MAX);
  lm2_v2_i8 result = {
      {(int8_t)v.x, (int8_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u32 lm2_v2_u64_to_u32(lm2_v2_u64 v) {
  LM2_ASSERT_UNSAFE(v.x <= UINT32_MAX && v.y <= UINT32_MAX);
  lm2_v2_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u16 lm2_v2_u64_to_u16(lm2_v2_u64 v) {
  LM2_ASSERT_UNSAFE(v.x <= UINT16_MAX && v.y <= UINT16_MAX);
  lm2_v2_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u8 lm2_v2_u64_to_u8(lm2_v2_u64 v) {
  LM2_ASSERT_UNSAFE(v.x <= UINT8_MAX && v.y <= UINT8_MAX);
  lm2_v2_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y}
  };
  return result;
}

// =============================================================================
// Vector2 Conversions - from u32
// =============================================================================

LM2_API lm2_v2_f64 lm2_v2_u32_to_f64(lm2_v2_u32 v) {
  lm2_v2_f64 result = {
      {(double)v.x, (double)v.y}
  };
  return result;
}

LM2_API lm2_v2_f32 lm2_v2_u32_to_f32(lm2_v2_u32 v) {
  lm2_v2_f32 result = {
      {(float)v.x, (float)v.y}
  };
  return result;
}

LM2_API lm2_v2_i64 lm2_v2_u32_to_i64(lm2_v2_u32 v) {
  lm2_v2_i64 result = {
      {(int64_t)v.x, (int64_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i32 lm2_v2_u32_to_i32(lm2_v2_u32 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT32_MAX && v.y <= INT32_MAX);
  lm2_v2_i32 result = {
      {(int32_t)v.x, (int32_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i16 lm2_v2_u32_to_i16(lm2_v2_u32 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT16_MAX && v.y <= INT16_MAX);
  lm2_v2_i16 result = {
      {(int16_t)v.x, (int16_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i8 lm2_v2_u32_to_i8(lm2_v2_u32 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT8_MAX && v.y <= INT8_MAX);
  lm2_v2_i8 result = {
      {(int8_t)v.x, (int8_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u64 lm2_v2_u32_to_u64(lm2_v2_u32 v) {
  lm2_v2_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u16 lm2_v2_u32_to_u16(lm2_v2_u32 v) {
  LM2_ASSERT_UNSAFE(v.x <= UINT16_MAX && v.y <= UINT16_MAX);
  lm2_v2_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u8 lm2_v2_u32_to_u8(lm2_v2_u32 v) {
  LM2_ASSERT_UNSAFE(v.x <= UINT8_MAX && v.y <= UINT8_MAX);
  lm2_v2_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y}
  };
  return result;
}

// =============================================================================
// Vector2 Conversions - from u16
// =============================================================================

LM2_API lm2_v2_f64 lm2_v2_u16_to_f64(lm2_v2_u16 v) {
  lm2_v2_f64 result = {
      {(double)v.x, (double)v.y}
  };
  return result;
}

LM2_API lm2_v2_f32 lm2_v2_u16_to_f32(lm2_v2_u16 v) {
  lm2_v2_f32 result = {
      {(float)v.x, (float)v.y}
  };
  return result;
}

LM2_API lm2_v2_i64 lm2_v2_u16_to_i64(lm2_v2_u16 v) {
  lm2_v2_i64 result = {
      {(int64_t)v.x, (int64_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i32 lm2_v2_u16_to_i32(lm2_v2_u16 v) {
  lm2_v2_i32 result = {
      {(int32_t)v.x, (int32_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i16 lm2_v2_u16_to_i16(lm2_v2_u16 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT16_MAX && v.y <= INT16_MAX);
  lm2_v2_i16 result = {
      {(int16_t)v.x, (int16_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i8 lm2_v2_u16_to_i8(lm2_v2_u16 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT8_MAX && v.y <= INT8_MAX);
  lm2_v2_i8 result = {
      {(int8_t)v.x, (int8_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u64 lm2_v2_u16_to_u64(lm2_v2_u16 v) {
  lm2_v2_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u32 lm2_v2_u16_to_u32(lm2_v2_u16 v) {
  lm2_v2_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u8 lm2_v2_u16_to_u8(lm2_v2_u16 v) {
  LM2_ASSERT_UNSAFE(v.x <= UINT8_MAX && v.y <= UINT8_MAX);
  lm2_v2_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y}
  };
  return result;
}

// =============================================================================
// Vector2 Conversions - from u8
// =============================================================================

LM2_API lm2_v2_f64 lm2_v2_u8_to_f64(lm2_v2_u8 v) {
  lm2_v2_f64 result = {
      {(double)v.x, (double)v.y}
  };
  return result;
}

LM2_API lm2_v2_f32 lm2_v2_u8_to_f32(lm2_v2_u8 v) {
  lm2_v2_f32 result = {
      {(float)v.x, (float)v.y}
  };
  return result;
}

LM2_API lm2_v2_i64 lm2_v2_u8_to_i64(lm2_v2_u8 v) {
  lm2_v2_i64 result = {
      {(int64_t)v.x, (int64_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i32 lm2_v2_u8_to_i32(lm2_v2_u8 v) {
  lm2_v2_i32 result = {
      {(int32_t)v.x, (int32_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i16 lm2_v2_u8_to_i16(lm2_v2_u8 v) {
  lm2_v2_i16 result = {
      {(int16_t)v.x, (int16_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_i8 lm2_v2_u8_to_i8(lm2_v2_u8 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT8_MAX && v.y <= INT8_MAX);
  lm2_v2_i8 result = {
      {(int8_t)v.x, (int8_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u64 lm2_v2_u8_to_u64(lm2_v2_u8 v) {
  lm2_v2_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u32 lm2_v2_u8_to_u32(lm2_v2_u8 v) {
  lm2_v2_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y}
  };
  return result;
}

LM2_API lm2_v2_u16 lm2_v2_u8_to_u16(lm2_v2_u8 v) {
  lm2_v2_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y}
  };
  return result;
}

// =============================================================================
// Vector3 Conversions - from f64
// =============================================================================

LM2_API lm2_v3_f32 lm2_v3_f64_to_f32(lm2_v3_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= -FLT_MAX && v.x <= FLT_MAX);
  LM2_ASSERT_UNSAFE(v.y >= -FLT_MAX && v.y <= FLT_MAX);
  LM2_ASSERT_UNSAFE(v.z >= -FLT_MAX && v.z <= FLT_MAX);
  lm2_v3_f32 result = {
      {(float)v.x, (float)v.y, (float)v.z}
  };
  return result;
}

LM2_API lm2_v3_i64 lm2_v3_f64_to_i64(lm2_v3_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= (double)INT64_MIN && v.x <= (double)INT64_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (double)INT64_MIN && v.y <= (double)INT64_MAX);
  LM2_ASSERT_UNSAFE(v.z >= (double)INT64_MIN && v.z <= (double)INT64_MAX);
  lm2_v3_i64 result = {
      {(int64_t)v.x, (int64_t)v.y, (int64_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i32 lm2_v3_f64_to_i32(lm2_v3_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= (double)INT32_MIN && v.x <= (double)INT32_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (double)INT32_MIN && v.y <= (double)INT32_MAX);
  LM2_ASSERT_UNSAFE(v.z >= (double)INT32_MIN && v.z <= (double)INT32_MAX);
  lm2_v3_i32 result = {
      {(int32_t)v.x, (int32_t)v.y, (int32_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i16 lm2_v3_f64_to_i16(lm2_v3_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= (double)INT16_MIN && v.x <= (double)INT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (double)INT16_MIN && v.y <= (double)INT16_MAX);
  LM2_ASSERT_UNSAFE(v.z >= (double)INT16_MIN && v.z <= (double)INT16_MAX);
  lm2_v3_i16 result = {
      {(int16_t)v.x, (int16_t)v.y, (int16_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i8 lm2_v3_f64_to_i8(lm2_v3_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= (double)INT8_MIN && v.x <= (double)INT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (double)INT8_MIN && v.y <= (double)INT8_MAX);
  LM2_ASSERT_UNSAFE(v.z >= (double)INT8_MIN && v.z <= (double)INT8_MAX);
  lm2_v3_i8 result = {
      {(int8_t)v.x, (int8_t)v.y, (int8_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u64 lm2_v3_f64_to_u64(lm2_v3_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0 && v.x <= (double)UINT64_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0 && v.y <= (double)UINT64_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0.0 && v.z <= (double)UINT64_MAX);
  lm2_v3_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y, (uint64_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u32 lm2_v3_f64_to_u32(lm2_v3_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0 && v.x <= (double)UINT32_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0 && v.y <= (double)UINT32_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0.0 && v.z <= (double)UINT32_MAX);
  lm2_v3_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y, (uint32_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u16 lm2_v3_f64_to_u16(lm2_v3_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0 && v.x <= (double)UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0 && v.y <= (double)UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0.0 && v.z <= (double)UINT16_MAX);
  lm2_v3_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y, (uint16_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u8 lm2_v3_f64_to_u8(lm2_v3_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0 && v.x <= (double)UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0 && v.y <= (double)UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0.0 && v.z <= (double)UINT8_MAX);
  lm2_v3_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y, (uint8_t)v.z}
  };
  return result;
}

// =============================================================================
// Vector3 Conversions - from f32
// =============================================================================

LM2_API lm2_v3_f64 lm2_v3_f32_to_f64(lm2_v3_f32 v) {
  lm2_v3_f64 result = {
      {(double)v.x, (double)v.y, (double)v.z}
  };
  return result;
}

LM2_API lm2_v3_i64 lm2_v3_f32_to_i64(lm2_v3_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= (float)INT64_MIN && v.x <= (float)INT64_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (float)INT64_MIN && v.y <= (float)INT64_MAX);
  LM2_ASSERT_UNSAFE(v.z >= (float)INT64_MIN && v.z <= (float)INT64_MAX);
  lm2_v3_i64 result = {
      {(int64_t)v.x, (int64_t)v.y, (int64_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i32 lm2_v3_f32_to_i32(lm2_v3_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= (float)INT32_MIN && v.x <= (float)INT32_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (float)INT32_MIN && v.y <= (float)INT32_MAX);
  LM2_ASSERT_UNSAFE(v.z >= (float)INT32_MIN && v.z <= (float)INT32_MAX);
  lm2_v3_i32 result = {
      {(int32_t)v.x, (int32_t)v.y, (int32_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i16 lm2_v3_f32_to_i16(lm2_v3_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= (float)INT16_MIN && v.x <= (float)INT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (float)INT16_MIN && v.y <= (float)INT16_MAX);
  LM2_ASSERT_UNSAFE(v.z >= (float)INT16_MIN && v.z <= (float)INT16_MAX);
  lm2_v3_i16 result = {
      {(int16_t)v.x, (int16_t)v.y, (int16_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i8 lm2_v3_f32_to_i8(lm2_v3_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= (float)INT8_MIN && v.x <= (float)INT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (float)INT8_MIN && v.y <= (float)INT8_MAX);
  LM2_ASSERT_UNSAFE(v.z >= (float)INT8_MIN && v.z <= (float)INT8_MAX);
  lm2_v3_i8 result = {
      {(int8_t)v.x, (int8_t)v.y, (int8_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u64 lm2_v3_f32_to_u64(lm2_v3_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0f && v.x <= (float)UINT64_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0f && v.y <= (float)UINT64_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0.0f && v.z <= (float)UINT64_MAX);
  lm2_v3_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y, (uint64_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u32 lm2_v3_f32_to_u32(lm2_v3_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0f && v.x <= (float)UINT32_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0f && v.y <= (float)UINT32_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0.0f && v.z <= (float)UINT32_MAX);
  lm2_v3_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y, (uint32_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u16 lm2_v3_f32_to_u16(lm2_v3_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0f && v.x <= (float)UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0f && v.y <= (float)UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0.0f && v.z <= (float)UINT16_MAX);
  lm2_v3_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y, (uint16_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u8 lm2_v3_f32_to_u8(lm2_v3_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0f && v.x <= (float)UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0f && v.y <= (float)UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0.0f && v.z <= (float)UINT8_MAX);
  lm2_v3_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y, (uint8_t)v.z}
  };
  return result;
}

// =============================================================================
// Vector3 Conversions - from i64
// =============================================================================

LM2_API lm2_v3_f64 lm2_v3_i64_to_f64(lm2_v3_i64 v) {
  lm2_v3_f64 result = {
      {(double)v.x, (double)v.y, (double)v.z}
  };
  return result;
}

LM2_API lm2_v3_f32 lm2_v3_i64_to_f32(lm2_v3_i64 v) {
  lm2_v3_f32 result = {
      {(float)v.x, (float)v.y, (float)v.z}
  };
  return result;
}

LM2_API lm2_v3_i32 lm2_v3_i64_to_i32(lm2_v3_i64 v) {
  LM2_ASSERT_UNSAFE(v.x >= INT32_MIN && v.x <= INT32_MAX);
  LM2_ASSERT_UNSAFE(v.y >= INT32_MIN && v.y <= INT32_MAX);
  LM2_ASSERT_UNSAFE(v.z >= INT32_MIN && v.z <= INT32_MAX);
  lm2_v3_i32 result = {
      {(int32_t)v.x, (int32_t)v.y, (int32_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i16 lm2_v3_i64_to_i16(lm2_v3_i64 v) {
  LM2_ASSERT_UNSAFE(v.x >= INT16_MIN && v.x <= INT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= INT16_MIN && v.y <= INT16_MAX);
  LM2_ASSERT_UNSAFE(v.z >= INT16_MIN && v.z <= INT16_MAX);
  lm2_v3_i16 result = {
      {(int16_t)v.x, (int16_t)v.y, (int16_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i8 lm2_v3_i64_to_i8(lm2_v3_i64 v) {
  LM2_ASSERT_UNSAFE(v.x >= INT8_MIN && v.x <= INT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= INT8_MIN && v.y <= INT8_MAX);
  LM2_ASSERT_UNSAFE(v.z >= INT8_MIN && v.z <= INT8_MAX);
  lm2_v3_i8 result = {
      {(int8_t)v.x, (int8_t)v.y, (int8_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u64 lm2_v3_i64_to_u64(lm2_v3_i64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0 && v.z >= 0);
  lm2_v3_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y, (uint64_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u32 lm2_v3_i64_to_u32(lm2_v3_i64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.x <= UINT32_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0 && v.y <= UINT32_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0 && v.z <= UINT32_MAX);
  lm2_v3_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y, (uint32_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u16 lm2_v3_i64_to_u16(lm2_v3_i64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.x <= UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0 && v.y <= UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0 && v.z <= UINT16_MAX);
  lm2_v3_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y, (uint16_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u8 lm2_v3_i64_to_u8(lm2_v3_i64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.x <= UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0 && v.y <= UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0 && v.z <= UINT8_MAX);
  lm2_v3_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y, (uint8_t)v.z}
  };
  return result;
}

// =============================================================================
// Vector3 Conversions - from i32
// =============================================================================

LM2_API lm2_v3_f64 lm2_v3_i32_to_f64(lm2_v3_i32 v) {
  lm2_v3_f64 result = {
      {(double)v.x, (double)v.y, (double)v.z}
  };
  return result;
}

LM2_API lm2_v3_f32 lm2_v3_i32_to_f32(lm2_v3_i32 v) {
  lm2_v3_f32 result = {
      {(float)v.x, (float)v.y, (float)v.z}
  };
  return result;
}

LM2_API lm2_v3_i64 lm2_v3_i32_to_i64(lm2_v3_i32 v) {
  lm2_v3_i64 result = {
      {(int64_t)v.x, (int64_t)v.y, (int64_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i16 lm2_v3_i32_to_i16(lm2_v3_i32 v) {
  LM2_ASSERT_UNSAFE(v.x >= INT16_MIN && v.x <= INT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= INT16_MIN && v.y <= INT16_MAX);
  LM2_ASSERT_UNSAFE(v.z >= INT16_MIN && v.z <= INT16_MAX);
  lm2_v3_i16 result = {
      {(int16_t)v.x, (int16_t)v.y, (int16_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i8 lm2_v3_i32_to_i8(lm2_v3_i32 v) {
  LM2_ASSERT_UNSAFE(v.x >= INT8_MIN && v.x <= INT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= INT8_MIN && v.y <= INT8_MAX);
  LM2_ASSERT_UNSAFE(v.z >= INT8_MIN && v.z <= INT8_MAX);
  lm2_v3_i8 result = {
      {(int8_t)v.x, (int8_t)v.y, (int8_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u64 lm2_v3_i32_to_u64(lm2_v3_i32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0 && v.z >= 0);
  lm2_v3_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y, (uint64_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u32 lm2_v3_i32_to_u32(lm2_v3_i32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0 && v.z >= 0);
  lm2_v3_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y, (uint32_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u16 lm2_v3_i32_to_u16(lm2_v3_i32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.x <= UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0 && v.y <= UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0 && v.z <= UINT16_MAX);
  lm2_v3_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y, (uint16_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u8 lm2_v3_i32_to_u8(lm2_v3_i32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.x <= UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0 && v.y <= UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0 && v.z <= UINT8_MAX);
  lm2_v3_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y, (uint8_t)v.z}
  };
  return result;
}

// =============================================================================
// Vector3 Conversions - from i16
// =============================================================================

LM2_API lm2_v3_f64 lm2_v3_i16_to_f64(lm2_v3_i16 v) {
  lm2_v3_f64 result = {
      {(double)v.x, (double)v.y, (double)v.z}
  };
  return result;
}

LM2_API lm2_v3_f32 lm2_v3_i16_to_f32(lm2_v3_i16 v) {
  lm2_v3_f32 result = {
      {(float)v.x, (float)v.y, (float)v.z}
  };
  return result;
}

LM2_API lm2_v3_i64 lm2_v3_i16_to_i64(lm2_v3_i16 v) {
  lm2_v3_i64 result = {
      {(int64_t)v.x, (int64_t)v.y, (int64_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i32 lm2_v3_i16_to_i32(lm2_v3_i16 v) {
  lm2_v3_i32 result = {
      {(int32_t)v.x, (int32_t)v.y, (int32_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i8 lm2_v3_i16_to_i8(lm2_v3_i16 v) {
  LM2_ASSERT_UNSAFE(v.x >= INT8_MIN && v.x <= INT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= INT8_MIN && v.y <= INT8_MAX);
  LM2_ASSERT_UNSAFE(v.z >= INT8_MIN && v.z <= INT8_MAX);
  lm2_v3_i8 result = {
      {(int8_t)v.x, (int8_t)v.y, (int8_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u64 lm2_v3_i16_to_u64(lm2_v3_i16 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0 && v.z >= 0);
  lm2_v3_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y, (uint64_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u32 lm2_v3_i16_to_u32(lm2_v3_i16 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0 && v.z >= 0);
  lm2_v3_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y, (uint32_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u16 lm2_v3_i16_to_u16(lm2_v3_i16 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0 && v.z >= 0);
  lm2_v3_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y, (uint16_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u8 lm2_v3_i16_to_u8(lm2_v3_i16 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.x <= UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0 && v.y <= UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0 && v.z <= UINT8_MAX);
  lm2_v3_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y, (uint8_t)v.z}
  };
  return result;
}

// =============================================================================
// Vector3 Conversions - from i8
// =============================================================================

LM2_API lm2_v3_f64 lm2_v3_i8_to_f64(lm2_v3_i8 v) {
  lm2_v3_f64 result = {
      {(double)v.x, (double)v.y, (double)v.z}
  };
  return result;
}

LM2_API lm2_v3_f32 lm2_v3_i8_to_f32(lm2_v3_i8 v) {
  lm2_v3_f32 result = {
      {(float)v.x, (float)v.y, (float)v.z}
  };
  return result;
}

LM2_API lm2_v3_i64 lm2_v3_i8_to_i64(lm2_v3_i8 v) {
  lm2_v3_i64 result = {
      {(int64_t)v.x, (int64_t)v.y, (int64_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i32 lm2_v3_i8_to_i32(lm2_v3_i8 v) {
  lm2_v3_i32 result = {
      {(int32_t)v.x, (int32_t)v.y, (int32_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i16 lm2_v3_i8_to_i16(lm2_v3_i8 v) {
  lm2_v3_i16 result = {
      {(int16_t)v.x, (int16_t)v.y, (int16_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u64 lm2_v3_i8_to_u64(lm2_v3_i8 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0 && v.z >= 0);
  lm2_v3_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y, (uint64_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u32 lm2_v3_i8_to_u32(lm2_v3_i8 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0 && v.z >= 0);
  lm2_v3_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y, (uint32_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u16 lm2_v3_i8_to_u16(lm2_v3_i8 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0 && v.z >= 0);
  lm2_v3_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y, (uint16_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u8 lm2_v3_i8_to_u8(lm2_v3_i8 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0 && v.z >= 0);
  lm2_v3_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y, (uint8_t)v.z}
  };
  return result;
}

// =============================================================================
// Vector3 Conversions - from u64
// =============================================================================

LM2_API lm2_v3_f64 lm2_v3_u64_to_f64(lm2_v3_u64 v) {
  lm2_v3_f64 result = {
      {(double)v.x, (double)v.y, (double)v.z}
  };
  return result;
}

LM2_API lm2_v3_f32 lm2_v3_u64_to_f32(lm2_v3_u64 v) {
  lm2_v3_f32 result = {
      {(float)v.x, (float)v.y, (float)v.z}
  };
  return result;
}

LM2_API lm2_v3_i64 lm2_v3_u64_to_i64(lm2_v3_u64 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT64_MAX && v.y <= INT64_MAX && v.z <= INT64_MAX);
  lm2_v3_i64 result = {
      {(int64_t)v.x, (int64_t)v.y, (int64_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i32 lm2_v3_u64_to_i32(lm2_v3_u64 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT32_MAX && v.y <= INT32_MAX && v.z <= INT32_MAX);
  lm2_v3_i32 result = {
      {(int32_t)v.x, (int32_t)v.y, (int32_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i16 lm2_v3_u64_to_i16(lm2_v3_u64 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT16_MAX && v.y <= INT16_MAX && v.z <= INT16_MAX);
  lm2_v3_i16 result = {
      {(int16_t)v.x, (int16_t)v.y, (int16_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i8 lm2_v3_u64_to_i8(lm2_v3_u64 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT8_MAX && v.y <= INT8_MAX && v.z <= INT8_MAX);
  lm2_v3_i8 result = {
      {(int8_t)v.x, (int8_t)v.y, (int8_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u32 lm2_v3_u64_to_u32(lm2_v3_u64 v) {
  LM2_ASSERT_UNSAFE(v.x <= UINT32_MAX && v.y <= UINT32_MAX && v.z <= UINT32_MAX);
  lm2_v3_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y, (uint32_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u16 lm2_v3_u64_to_u16(lm2_v3_u64 v) {
  LM2_ASSERT_UNSAFE(v.x <= UINT16_MAX && v.y <= UINT16_MAX && v.z <= UINT16_MAX);
  lm2_v3_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y, (uint16_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u8 lm2_v3_u64_to_u8(lm2_v3_u64 v) {
  LM2_ASSERT_UNSAFE(v.x <= UINT8_MAX && v.y <= UINT8_MAX && v.z <= UINT8_MAX);
  lm2_v3_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y, (uint8_t)v.z}
  };
  return result;
}

// =============================================================================
// Vector3 Conversions - from u32
// =============================================================================

LM2_API lm2_v3_f64 lm2_v3_u32_to_f64(lm2_v3_u32 v) {
  lm2_v3_f64 result = {
      {(double)v.x, (double)v.y, (double)v.z}
  };
  return result;
}

LM2_API lm2_v3_f32 lm2_v3_u32_to_f32(lm2_v3_u32 v) {
  lm2_v3_f32 result = {
      {(float)v.x, (float)v.y, (float)v.z}
  };
  return result;
}

LM2_API lm2_v3_i64 lm2_v3_u32_to_i64(lm2_v3_u32 v) {
  lm2_v3_i64 result = {
      {(int64_t)v.x, (int64_t)v.y, (int64_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i32 lm2_v3_u32_to_i32(lm2_v3_u32 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT32_MAX && v.y <= INT32_MAX && v.z <= INT32_MAX);
  lm2_v3_i32 result = {
      {(int32_t)v.x, (int32_t)v.y, (int32_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i16 lm2_v3_u32_to_i16(lm2_v3_u32 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT16_MAX && v.y <= INT16_MAX && v.z <= INT16_MAX);
  lm2_v3_i16 result = {
      {(int16_t)v.x, (int16_t)v.y, (int16_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i8 lm2_v3_u32_to_i8(lm2_v3_u32 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT8_MAX && v.y <= INT8_MAX && v.z <= INT8_MAX);
  lm2_v3_i8 result = {
      {(int8_t)v.x, (int8_t)v.y, (int8_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u64 lm2_v3_u32_to_u64(lm2_v3_u32 v) {
  lm2_v3_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y, (uint64_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u16 lm2_v3_u32_to_u16(lm2_v3_u32 v) {
  LM2_ASSERT_UNSAFE(v.x <= UINT16_MAX && v.y <= UINT16_MAX && v.z <= UINT16_MAX);
  lm2_v3_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y, (uint16_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u8 lm2_v3_u32_to_u8(lm2_v3_u32 v) {
  LM2_ASSERT_UNSAFE(v.x <= UINT8_MAX && v.y <= UINT8_MAX && v.z <= UINT8_MAX);
  lm2_v3_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y, (uint8_t)v.z}
  };
  return result;
}

// =============================================================================
// Vector3 Conversions - from u16
// =============================================================================

LM2_API lm2_v3_f64 lm2_v3_u16_to_f64(lm2_v3_u16 v) {
  lm2_v3_f64 result = {
      {(double)v.x, (double)v.y, (double)v.z}
  };
  return result;
}

LM2_API lm2_v3_f32 lm2_v3_u16_to_f32(lm2_v3_u16 v) {
  lm2_v3_f32 result = {
      {(float)v.x, (float)v.y, (float)v.z}
  };
  return result;
}

LM2_API lm2_v3_i64 lm2_v3_u16_to_i64(lm2_v3_u16 v) {
  lm2_v3_i64 result = {
      {(int64_t)v.x, (int64_t)v.y, (int64_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i32 lm2_v3_u16_to_i32(lm2_v3_u16 v) {
  lm2_v3_i32 result = {
      {(int32_t)v.x, (int32_t)v.y, (int32_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i16 lm2_v3_u16_to_i16(lm2_v3_u16 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT16_MAX && v.y <= INT16_MAX && v.z <= INT16_MAX);
  lm2_v3_i16 result = {
      {(int16_t)v.x, (int16_t)v.y, (int16_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i8 lm2_v3_u16_to_i8(lm2_v3_u16 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT8_MAX && v.y <= INT8_MAX && v.z <= INT8_MAX);
  lm2_v3_i8 result = {
      {(int8_t)v.x, (int8_t)v.y, (int8_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u64 lm2_v3_u16_to_u64(lm2_v3_u16 v) {
  lm2_v3_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y, (uint64_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u32 lm2_v3_u16_to_u32(lm2_v3_u16 v) {
  lm2_v3_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y, (uint32_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u8 lm2_v3_u16_to_u8(lm2_v3_u16 v) {
  LM2_ASSERT_UNSAFE(v.x <= UINT8_MAX && v.y <= UINT8_MAX && v.z <= UINT8_MAX);
  lm2_v3_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y, (uint8_t)v.z}
  };
  return result;
}

// =============================================================================
// Vector3 Conversions - from u8
// =============================================================================

LM2_API lm2_v3_f64 lm2_v3_u8_to_f64(lm2_v3_u8 v) {
  lm2_v3_f64 result = {
      {(double)v.x, (double)v.y, (double)v.z}
  };
  return result;
}

LM2_API lm2_v3_f32 lm2_v3_u8_to_f32(lm2_v3_u8 v) {
  lm2_v3_f32 result = {
      {(float)v.x, (float)v.y, (float)v.z}
  };
  return result;
}

LM2_API lm2_v3_i64 lm2_v3_u8_to_i64(lm2_v3_u8 v) {
  lm2_v3_i64 result = {
      {(int64_t)v.x, (int64_t)v.y, (int64_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i32 lm2_v3_u8_to_i32(lm2_v3_u8 v) {
  lm2_v3_i32 result = {
      {(int32_t)v.x, (int32_t)v.y, (int32_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i16 lm2_v3_u8_to_i16(lm2_v3_u8 v) {
  lm2_v3_i16 result = {
      {(int16_t)v.x, (int16_t)v.y, (int16_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_i8 lm2_v3_u8_to_i8(lm2_v3_u8 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT8_MAX && v.y <= INT8_MAX && v.z <= INT8_MAX);
  lm2_v3_i8 result = {
      {(int8_t)v.x, (int8_t)v.y, (int8_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u64 lm2_v3_u8_to_u64(lm2_v3_u8 v) {
  lm2_v3_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y, (uint64_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u32 lm2_v3_u8_to_u32(lm2_v3_u8 v) {
  lm2_v3_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y, (uint32_t)v.z}
  };
  return result;
}

LM2_API lm2_v3_u16 lm2_v3_u8_to_u16(lm2_v3_u8 v) {
  lm2_v3_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y, (uint16_t)v.z}
  };
  return result;
}

// =============================================================================
// Vector4 Conversions - from f64
// =============================================================================

LM2_API lm2_v4_f32 lm2_v4_f64_to_f32(lm2_v4_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= -FLT_MAX && v.x <= FLT_MAX);
  LM2_ASSERT_UNSAFE(v.y >= -FLT_MAX && v.y <= FLT_MAX);
  LM2_ASSERT_UNSAFE(v.z >= -FLT_MAX && v.z <= FLT_MAX);
  LM2_ASSERT_UNSAFE(v.w >= -FLT_MAX && v.w <= FLT_MAX);
  lm2_v4_f32 result = {
      {(float)v.x, (float)v.y, (float)v.z, (float)v.w}
  };
  return result;
}

LM2_API lm2_v4_i64 lm2_v4_f64_to_i64(lm2_v4_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= (double)INT64_MIN && v.x <= (double)INT64_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (double)INT64_MIN && v.y <= (double)INT64_MAX);
  LM2_ASSERT_UNSAFE(v.z >= (double)INT64_MIN && v.z <= (double)INT64_MAX);
  LM2_ASSERT_UNSAFE(v.w >= (double)INT64_MIN && v.w <= (double)INT64_MAX);
  lm2_v4_i64 result = {
      {(int64_t)v.x, (int64_t)v.y, (int64_t)v.z, (int64_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i32 lm2_v4_f64_to_i32(lm2_v4_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= (double)INT32_MIN && v.x <= (double)INT32_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (double)INT32_MIN && v.y <= (double)INT32_MAX);
  LM2_ASSERT_UNSAFE(v.z >= (double)INT32_MIN && v.z <= (double)INT32_MAX);
  LM2_ASSERT_UNSAFE(v.w >= (double)INT32_MIN && v.w <= (double)INT32_MAX);
  lm2_v4_i32 result = {
      {(int32_t)v.x, (int32_t)v.y, (int32_t)v.z, (int32_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i16 lm2_v4_f64_to_i16(lm2_v4_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= (double)INT16_MIN && v.x <= (double)INT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (double)INT16_MIN && v.y <= (double)INT16_MAX);
  LM2_ASSERT_UNSAFE(v.z >= (double)INT16_MIN && v.z <= (double)INT16_MAX);
  LM2_ASSERT_UNSAFE(v.w >= (double)INT16_MIN && v.w <= (double)INT16_MAX);
  lm2_v4_i16 result = {
      {(int16_t)v.x, (int16_t)v.y, (int16_t)v.z, (int16_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i8 lm2_v4_f64_to_i8(lm2_v4_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= (double)INT8_MIN && v.x <= (double)INT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (double)INT8_MIN && v.y <= (double)INT8_MAX);
  LM2_ASSERT_UNSAFE(v.z >= (double)INT8_MIN && v.z <= (double)INT8_MAX);
  LM2_ASSERT_UNSAFE(v.w >= (double)INT8_MIN && v.w <= (double)INT8_MAX);
  lm2_v4_i8 result = {
      {(int8_t)v.x, (int8_t)v.y, (int8_t)v.z, (int8_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u64 lm2_v4_f64_to_u64(lm2_v4_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0 && v.x <= (double)UINT64_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0 && v.y <= (double)UINT64_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0.0 && v.z <= (double)UINT64_MAX);
  LM2_ASSERT_UNSAFE(v.w >= 0.0 && v.w <= (double)UINT64_MAX);
  lm2_v4_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y, (uint64_t)v.z, (uint64_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u32 lm2_v4_f64_to_u32(lm2_v4_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0 && v.x <= (double)UINT32_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0 && v.y <= (double)UINT32_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0.0 && v.z <= (double)UINT32_MAX);
  LM2_ASSERT_UNSAFE(v.w >= 0.0 && v.w <= (double)UINT32_MAX);
  lm2_v4_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y, (uint32_t)v.z, (uint32_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u16 lm2_v4_f64_to_u16(lm2_v4_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0 && v.x <= (double)UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0 && v.y <= (double)UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0.0 && v.z <= (double)UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.w >= 0.0 && v.w <= (double)UINT16_MAX);
  lm2_v4_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y, (uint16_t)v.z, (uint16_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u8 lm2_v4_f64_to_u8(lm2_v4_f64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0 && v.x <= (double)UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0 && v.y <= (double)UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0.0 && v.z <= (double)UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.w >= 0.0 && v.w <= (double)UINT8_MAX);
  lm2_v4_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y, (uint8_t)v.z, (uint8_t)v.w}
  };
  return result;
}

// =============================================================================
// Vector4 Conversions - from f32
// =============================================================================

LM2_API lm2_v4_f64 lm2_v4_f32_to_f64(lm2_v4_f32 v) {
  lm2_v4_f64 result = {
      {(double)v.x, (double)v.y, (double)v.z, (double)v.w}
  };
  return result;
}

LM2_API lm2_v4_i64 lm2_v4_f32_to_i64(lm2_v4_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= (float)INT64_MIN && v.x <= (float)INT64_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (float)INT64_MIN && v.y <= (float)INT64_MAX);
  LM2_ASSERT_UNSAFE(v.z >= (float)INT64_MIN && v.z <= (float)INT64_MAX);
  LM2_ASSERT_UNSAFE(v.w >= (float)INT64_MIN && v.w <= (float)INT64_MAX);
  lm2_v4_i64 result = {
      {(int64_t)v.x, (int64_t)v.y, (int64_t)v.z, (int64_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i32 lm2_v4_f32_to_i32(lm2_v4_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= (float)INT32_MIN && v.x <= (float)INT32_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (float)INT32_MIN && v.y <= (float)INT32_MAX);
  LM2_ASSERT_UNSAFE(v.z >= (float)INT32_MIN && v.z <= (float)INT32_MAX);
  LM2_ASSERT_UNSAFE(v.w >= (float)INT32_MIN && v.w <= (float)INT32_MAX);
  lm2_v4_i32 result = {
      {(int32_t)v.x, (int32_t)v.y, (int32_t)v.z, (int32_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i16 lm2_v4_f32_to_i16(lm2_v4_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= (float)INT16_MIN && v.x <= (float)INT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (float)INT16_MIN && v.y <= (float)INT16_MAX);
  LM2_ASSERT_UNSAFE(v.z >= (float)INT16_MIN && v.z <= (float)INT16_MAX);
  LM2_ASSERT_UNSAFE(v.w >= (float)INT16_MIN && v.w <= (float)INT16_MAX);
  lm2_v4_i16 result = {
      {(int16_t)v.x, (int16_t)v.y, (int16_t)v.z, (int16_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i8 lm2_v4_f32_to_i8(lm2_v4_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= (float)INT8_MIN && v.x <= (float)INT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= (float)INT8_MIN && v.y <= (float)INT8_MAX);
  LM2_ASSERT_UNSAFE(v.z >= (float)INT8_MIN && v.z <= (float)INT8_MAX);
  LM2_ASSERT_UNSAFE(v.w >= (float)INT8_MIN && v.w <= (float)INT8_MAX);
  lm2_v4_i8 result = {
      {(int8_t)v.x, (int8_t)v.y, (int8_t)v.z, (int8_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u64 lm2_v4_f32_to_u64(lm2_v4_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0f && v.x <= (float)UINT64_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0f && v.y <= (float)UINT64_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0.0f && v.z <= (float)UINT64_MAX);
  LM2_ASSERT_UNSAFE(v.w >= 0.0f && v.w <= (float)UINT64_MAX);
  lm2_v4_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y, (uint64_t)v.z, (uint64_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u32 lm2_v4_f32_to_u32(lm2_v4_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0f && v.x <= (float)UINT32_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0f && v.y <= (float)UINT32_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0.0f && v.z <= (float)UINT32_MAX);
  LM2_ASSERT_UNSAFE(v.w >= 0.0f && v.w <= (float)UINT32_MAX);
  lm2_v4_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y, (uint32_t)v.z, (uint32_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u16 lm2_v4_f32_to_u16(lm2_v4_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0f && v.x <= (float)UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0f && v.y <= (float)UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0.0f && v.z <= (float)UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.w >= 0.0f && v.w <= (float)UINT16_MAX);
  lm2_v4_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y, (uint16_t)v.z, (uint16_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u8 lm2_v4_f32_to_u8(lm2_v4_f32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0.0f && v.x <= (float)UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0.0f && v.y <= (float)UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0.0f && v.z <= (float)UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.w >= 0.0f && v.w <= (float)UINT8_MAX);
  lm2_v4_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y, (uint8_t)v.z, (uint8_t)v.w}
  };
  return result;
}

// =============================================================================
// Vector4 Conversions - from i64
// =============================================================================

LM2_API lm2_v4_f64 lm2_v4_i64_to_f64(lm2_v4_i64 v) {
  lm2_v4_f64 result = {
      {(double)v.x, (double)v.y, (double)v.z, (double)v.w}
  };
  return result;
}

LM2_API lm2_v4_f32 lm2_v4_i64_to_f32(lm2_v4_i64 v) {
  lm2_v4_f32 result = {
      {(float)v.x, (float)v.y, (float)v.z, (float)v.w}
  };
  return result;
}

LM2_API lm2_v4_i32 lm2_v4_i64_to_i32(lm2_v4_i64 v) {
  LM2_ASSERT_UNSAFE(v.x >= INT32_MIN && v.x <= INT32_MAX);
  LM2_ASSERT_UNSAFE(v.y >= INT32_MIN && v.y <= INT32_MAX);
  LM2_ASSERT_UNSAFE(v.z >= INT32_MIN && v.z <= INT32_MAX);
  LM2_ASSERT_UNSAFE(v.w >= INT32_MIN && v.w <= INT32_MAX);
  lm2_v4_i32 result = {
      {(int32_t)v.x, (int32_t)v.y, (int32_t)v.z, (int32_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i16 lm2_v4_i64_to_i16(lm2_v4_i64 v) {
  LM2_ASSERT_UNSAFE(v.x >= INT16_MIN && v.x <= INT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= INT16_MIN && v.y <= INT16_MAX);
  LM2_ASSERT_UNSAFE(v.z >= INT16_MIN && v.z <= INT16_MAX);
  LM2_ASSERT_UNSAFE(v.w >= INT16_MIN && v.w <= INT16_MAX);
  lm2_v4_i16 result = {
      {(int16_t)v.x, (int16_t)v.y, (int16_t)v.z, (int16_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i8 lm2_v4_i64_to_i8(lm2_v4_i64 v) {
  LM2_ASSERT_UNSAFE(v.x >= INT8_MIN && v.x <= INT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= INT8_MIN && v.y <= INT8_MAX);
  LM2_ASSERT_UNSAFE(v.z >= INT8_MIN && v.z <= INT8_MAX);
  LM2_ASSERT_UNSAFE(v.w >= INT8_MIN && v.w <= INT8_MAX);
  lm2_v4_i8 result = {
      {(int8_t)v.x, (int8_t)v.y, (int8_t)v.z, (int8_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u64 lm2_v4_i64_to_u64(lm2_v4_i64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0 && v.z >= 0 && v.w >= 0);
  lm2_v4_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y, (uint64_t)v.z, (uint64_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u32 lm2_v4_i64_to_u32(lm2_v4_i64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.x <= UINT32_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0 && v.y <= UINT32_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0 && v.z <= UINT32_MAX);
  LM2_ASSERT_UNSAFE(v.w >= 0 && v.w <= UINT32_MAX);
  lm2_v4_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y, (uint32_t)v.z, (uint32_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u16 lm2_v4_i64_to_u16(lm2_v4_i64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.x <= UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0 && v.y <= UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0 && v.z <= UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.w >= 0 && v.w <= UINT16_MAX);
  lm2_v4_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y, (uint16_t)v.z, (uint16_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u8 lm2_v4_i64_to_u8(lm2_v4_i64 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.x <= UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0 && v.y <= UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0 && v.z <= UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.w >= 0 && v.w <= UINT8_MAX);
  lm2_v4_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y, (uint8_t)v.z, (uint8_t)v.w}
  };
  return result;
}

// =============================================================================
// Vector4 Conversions - from i32
// =============================================================================

LM2_API lm2_v4_f64 lm2_v4_i32_to_f64(lm2_v4_i32 v) {
  lm2_v4_f64 result = {
      {(double)v.x, (double)v.y, (double)v.z, (double)v.w}
  };
  return result;
}

LM2_API lm2_v4_f32 lm2_v4_i32_to_f32(lm2_v4_i32 v) {
  lm2_v4_f32 result = {
      {(float)v.x, (float)v.y, (float)v.z, (float)v.w}
  };
  return result;
}

LM2_API lm2_v4_i64 lm2_v4_i32_to_i64(lm2_v4_i32 v) {
  lm2_v4_i64 result = {
      {(int64_t)v.x, (int64_t)v.y, (int64_t)v.z, (int64_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i16 lm2_v4_i32_to_i16(lm2_v4_i32 v) {
  LM2_ASSERT_UNSAFE(v.x >= INT16_MIN && v.x <= INT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= INT16_MIN && v.y <= INT16_MAX);
  LM2_ASSERT_UNSAFE(v.z >= INT16_MIN && v.z <= INT16_MAX);
  LM2_ASSERT_UNSAFE(v.w >= INT16_MIN && v.w <= INT16_MAX);
  lm2_v4_i16 result = {
      {(int16_t)v.x, (int16_t)v.y, (int16_t)v.z, (int16_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i8 lm2_v4_i32_to_i8(lm2_v4_i32 v) {
  LM2_ASSERT_UNSAFE(v.x >= INT8_MIN && v.x <= INT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= INT8_MIN && v.y <= INT8_MAX);
  LM2_ASSERT_UNSAFE(v.z >= INT8_MIN && v.z <= INT8_MAX);
  LM2_ASSERT_UNSAFE(v.w >= INT8_MIN && v.w <= INT8_MAX);
  lm2_v4_i8 result = {
      {(int8_t)v.x, (int8_t)v.y, (int8_t)v.z, (int8_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u64 lm2_v4_i32_to_u64(lm2_v4_i32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0 && v.z >= 0 && v.w >= 0);
  lm2_v4_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y, (uint64_t)v.z, (uint64_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u32 lm2_v4_i32_to_u32(lm2_v4_i32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0 && v.z >= 0 && v.w >= 0);
  lm2_v4_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y, (uint32_t)v.z, (uint32_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u16 lm2_v4_i32_to_u16(lm2_v4_i32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.x <= UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0 && v.y <= UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0 && v.z <= UINT16_MAX);
  LM2_ASSERT_UNSAFE(v.w >= 0 && v.w <= UINT16_MAX);
  lm2_v4_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y, (uint16_t)v.z, (uint16_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u8 lm2_v4_i32_to_u8(lm2_v4_i32 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.x <= UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0 && v.y <= UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0 && v.z <= UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.w >= 0 && v.w <= UINT8_MAX);
  lm2_v4_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y, (uint8_t)v.z, (uint8_t)v.w}
  };
  return result;
}

// =============================================================================
// Vector4 Conversions - from i16
// =============================================================================

LM2_API lm2_v4_f64 lm2_v4_i16_to_f64(lm2_v4_i16 v) {
  lm2_v4_f64 result = {
      {(double)v.x, (double)v.y, (double)v.z, (double)v.w}
  };
  return result;
}

LM2_API lm2_v4_f32 lm2_v4_i16_to_f32(lm2_v4_i16 v) {
  lm2_v4_f32 result = {
      {(float)v.x, (float)v.y, (float)v.z, (float)v.w}
  };
  return result;
}

LM2_API lm2_v4_i64 lm2_v4_i16_to_i64(lm2_v4_i16 v) {
  lm2_v4_i64 result = {
      {(int64_t)v.x, (int64_t)v.y, (int64_t)v.z, (int64_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i32 lm2_v4_i16_to_i32(lm2_v4_i16 v) {
  lm2_v4_i32 result = {
      {(int32_t)v.x, (int32_t)v.y, (int32_t)v.z, (int32_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i8 lm2_v4_i16_to_i8(lm2_v4_i16 v) {
  LM2_ASSERT_UNSAFE(v.x >= INT8_MIN && v.x <= INT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= INT8_MIN && v.y <= INT8_MAX);
  LM2_ASSERT_UNSAFE(v.z >= INT8_MIN && v.z <= INT8_MAX);
  LM2_ASSERT_UNSAFE(v.w >= INT8_MIN && v.w <= INT8_MAX);
  lm2_v4_i8 result = {
      {(int8_t)v.x, (int8_t)v.y, (int8_t)v.z, (int8_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u64 lm2_v4_i16_to_u64(lm2_v4_i16 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0 && v.z >= 0 && v.w >= 0);
  lm2_v4_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y, (uint64_t)v.z, (uint64_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u32 lm2_v4_i16_to_u32(lm2_v4_i16 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0 && v.z >= 0 && v.w >= 0);
  lm2_v4_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y, (uint32_t)v.z, (uint32_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u16 lm2_v4_i16_to_u16(lm2_v4_i16 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0 && v.z >= 0 && v.w >= 0);
  lm2_v4_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y, (uint16_t)v.z, (uint16_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u8 lm2_v4_i16_to_u8(lm2_v4_i16 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.x <= UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.y >= 0 && v.y <= UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.z >= 0 && v.z <= UINT8_MAX);
  LM2_ASSERT_UNSAFE(v.w >= 0 && v.w <= UINT8_MAX);
  lm2_v4_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y, (uint8_t)v.z, (uint8_t)v.w}
  };
  return result;
}

// =============================================================================
// Vector4 Conversions - from i8
// =============================================================================

LM2_API lm2_v4_f64 lm2_v4_i8_to_f64(lm2_v4_i8 v) {
  lm2_v4_f64 result = {
      {(double)v.x, (double)v.y, (double)v.z, (double)v.w}
  };
  return result;
}

LM2_API lm2_v4_f32 lm2_v4_i8_to_f32(lm2_v4_i8 v) {
  lm2_v4_f32 result = {
      {(float)v.x, (float)v.y, (float)v.z, (float)v.w}
  };
  return result;
}

LM2_API lm2_v4_i64 lm2_v4_i8_to_i64(lm2_v4_i8 v) {
  lm2_v4_i64 result = {
      {(int64_t)v.x, (int64_t)v.y, (int64_t)v.z, (int64_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i32 lm2_v4_i8_to_i32(lm2_v4_i8 v) {
  lm2_v4_i32 result = {
      {(int32_t)v.x, (int32_t)v.y, (int32_t)v.z, (int32_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i16 lm2_v4_i8_to_i16(lm2_v4_i8 v) {
  lm2_v4_i16 result = {
      {(int16_t)v.x, (int16_t)v.y, (int16_t)v.z, (int16_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u64 lm2_v4_i8_to_u64(lm2_v4_i8 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0 && v.z >= 0 && v.w >= 0);
  lm2_v4_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y, (uint64_t)v.z, (uint64_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u32 lm2_v4_i8_to_u32(lm2_v4_i8 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0 && v.z >= 0 && v.w >= 0);
  lm2_v4_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y, (uint32_t)v.z, (uint32_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u16 lm2_v4_i8_to_u16(lm2_v4_i8 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0 && v.z >= 0 && v.w >= 0);
  lm2_v4_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y, (uint16_t)v.z, (uint16_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u8 lm2_v4_i8_to_u8(lm2_v4_i8 v) {
  LM2_ASSERT_UNSAFE(v.x >= 0 && v.y >= 0 && v.z >= 0 && v.w >= 0);
  lm2_v4_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y, (uint8_t)v.z, (uint8_t)v.w}
  };
  return result;
}

// =============================================================================
// Vector4 Conversions - from u64
// =============================================================================

LM2_API lm2_v4_f64 lm2_v4_u64_to_f64(lm2_v4_u64 v) {
  lm2_v4_f64 result = {
      {(double)v.x, (double)v.y, (double)v.z, (double)v.w}
  };
  return result;
}

LM2_API lm2_v4_f32 lm2_v4_u64_to_f32(lm2_v4_u64 v) {
  lm2_v4_f32 result = {
      {(float)v.x, (float)v.y, (float)v.z, (float)v.w}
  };
  return result;
}

LM2_API lm2_v4_i64 lm2_v4_u64_to_i64(lm2_v4_u64 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT64_MAX && v.y <= INT64_MAX && v.z <= INT64_MAX && v.w <= INT64_MAX);
  lm2_v4_i64 result = {
      {(int64_t)v.x, (int64_t)v.y, (int64_t)v.z, (int64_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i32 lm2_v4_u64_to_i32(lm2_v4_u64 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT32_MAX && v.y <= INT32_MAX && v.z <= INT32_MAX && v.w <= INT32_MAX);
  lm2_v4_i32 result = {
      {(int32_t)v.x, (int32_t)v.y, (int32_t)v.z, (int32_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i16 lm2_v4_u64_to_i16(lm2_v4_u64 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT16_MAX && v.y <= INT16_MAX && v.z <= INT16_MAX && v.w <= INT16_MAX);
  lm2_v4_i16 result = {
      {(int16_t)v.x, (int16_t)v.y, (int16_t)v.z, (int16_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i8 lm2_v4_u64_to_i8(lm2_v4_u64 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT8_MAX && v.y <= INT8_MAX && v.z <= INT8_MAX && v.w <= INT8_MAX);
  lm2_v4_i8 result = {
      {(int8_t)v.x, (int8_t)v.y, (int8_t)v.z, (int8_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u32 lm2_v4_u64_to_u32(lm2_v4_u64 v) {
  LM2_ASSERT_UNSAFE(v.x <= UINT32_MAX && v.y <= UINT32_MAX && v.z <= UINT32_MAX && v.w <= UINT32_MAX);
  lm2_v4_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y, (uint32_t)v.z, (uint32_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u16 lm2_v4_u64_to_u16(lm2_v4_u64 v) {
  LM2_ASSERT_UNSAFE(v.x <= UINT16_MAX && v.y <= UINT16_MAX && v.z <= UINT16_MAX && v.w <= UINT16_MAX);
  lm2_v4_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y, (uint16_t)v.z, (uint16_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u8 lm2_v4_u64_to_u8(lm2_v4_u64 v) {
  LM2_ASSERT_UNSAFE(v.x <= UINT8_MAX && v.y <= UINT8_MAX && v.z <= UINT8_MAX && v.w <= UINT8_MAX);
  lm2_v4_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y, (uint8_t)v.z, (uint8_t)v.w}
  };
  return result;
}

// =============================================================================
// Vector4 Conversions - from u32
// =============================================================================

LM2_API lm2_v4_f64 lm2_v4_u32_to_f64(lm2_v4_u32 v) {
  lm2_v4_f64 result = {
      {(double)v.x, (double)v.y, (double)v.z, (double)v.w}
  };
  return result;
}

LM2_API lm2_v4_f32 lm2_v4_u32_to_f32(lm2_v4_u32 v) {
  lm2_v4_f32 result = {
      {(float)v.x, (float)v.y, (float)v.z, (float)v.w}
  };
  return result;
}

LM2_API lm2_v4_i64 lm2_v4_u32_to_i64(lm2_v4_u32 v) {
  lm2_v4_i64 result = {
      {(int64_t)v.x, (int64_t)v.y, (int64_t)v.z, (int64_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i32 lm2_v4_u32_to_i32(lm2_v4_u32 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT32_MAX && v.y <= INT32_MAX && v.z <= INT32_MAX && v.w <= INT32_MAX);
  lm2_v4_i32 result = {
      {(int32_t)v.x, (int32_t)v.y, (int32_t)v.z, (int32_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i16 lm2_v4_u32_to_i16(lm2_v4_u32 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT16_MAX && v.y <= INT16_MAX && v.z <= INT16_MAX && v.w <= INT16_MAX);
  lm2_v4_i16 result = {
      {(int16_t)v.x, (int16_t)v.y, (int16_t)v.z, (int16_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i8 lm2_v4_u32_to_i8(lm2_v4_u32 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT8_MAX && v.y <= INT8_MAX && v.z <= INT8_MAX && v.w <= INT8_MAX);
  lm2_v4_i8 result = {
      {(int8_t)v.x, (int8_t)v.y, (int8_t)v.z, (int8_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u64 lm2_v4_u32_to_u64(lm2_v4_u32 v) {
  lm2_v4_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y, (uint64_t)v.z, (uint64_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u16 lm2_v4_u32_to_u16(lm2_v4_u32 v) {
  LM2_ASSERT_UNSAFE(v.x <= UINT16_MAX && v.y <= UINT16_MAX && v.z <= UINT16_MAX && v.w <= UINT16_MAX);
  lm2_v4_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y, (uint16_t)v.z, (uint16_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u8 lm2_v4_u32_to_u8(lm2_v4_u32 v) {
  LM2_ASSERT_UNSAFE(v.x <= UINT8_MAX && v.y <= UINT8_MAX && v.z <= UINT8_MAX && v.w <= UINT8_MAX);
  lm2_v4_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y, (uint8_t)v.z, (uint8_t)v.w}
  };
  return result;
}

// =============================================================================
// Vector4 Conversions - from u16
// =============================================================================

LM2_API lm2_v4_f64 lm2_v4_u16_to_f64(lm2_v4_u16 v) {
  lm2_v4_f64 result = {
      {(double)v.x, (double)v.y, (double)v.z, (double)v.w}
  };
  return result;
}

LM2_API lm2_v4_f32 lm2_v4_u16_to_f32(lm2_v4_u16 v) {
  lm2_v4_f32 result = {
      {(float)v.x, (float)v.y, (float)v.z, (float)v.w}
  };
  return result;
}

LM2_API lm2_v4_i64 lm2_v4_u16_to_i64(lm2_v4_u16 v) {
  lm2_v4_i64 result = {
      {(int64_t)v.x, (int64_t)v.y, (int64_t)v.z, (int64_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i32 lm2_v4_u16_to_i32(lm2_v4_u16 v) {
  lm2_v4_i32 result = {
      {(int32_t)v.x, (int32_t)v.y, (int32_t)v.z, (int32_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i16 lm2_v4_u16_to_i16(lm2_v4_u16 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT16_MAX && v.y <= INT16_MAX && v.z <= INT16_MAX && v.w <= INT16_MAX);
  lm2_v4_i16 result = {
      {(int16_t)v.x, (int16_t)v.y, (int16_t)v.z, (int16_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i8 lm2_v4_u16_to_i8(lm2_v4_u16 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT8_MAX && v.y <= INT8_MAX && v.z <= INT8_MAX && v.w <= INT8_MAX);
  lm2_v4_i8 result = {
      {(int8_t)v.x, (int8_t)v.y, (int8_t)v.z, (int8_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u64 lm2_v4_u16_to_u64(lm2_v4_u16 v) {
  lm2_v4_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y, (uint64_t)v.z, (uint64_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u32 lm2_v4_u16_to_u32(lm2_v4_u16 v) {
  lm2_v4_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y, (uint32_t)v.z, (uint32_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u8 lm2_v4_u16_to_u8(lm2_v4_u16 v) {
  LM2_ASSERT_UNSAFE(v.x <= UINT8_MAX && v.y <= UINT8_MAX && v.z <= UINT8_MAX && v.w <= UINT8_MAX);
  lm2_v4_u8 result = {
      {(uint8_t)v.x, (uint8_t)v.y, (uint8_t)v.z, (uint8_t)v.w}
  };
  return result;
}

// =============================================================================
// Vector4 Conversions - from u8
// =============================================================================

LM2_API lm2_v4_f64 lm2_v4_u8_to_f64(lm2_v4_u8 v) {
  lm2_v4_f64 result = {
      {(double)v.x, (double)v.y, (double)v.z, (double)v.w}
  };
  return result;
}

LM2_API lm2_v4_f32 lm2_v4_u8_to_f32(lm2_v4_u8 v) {
  lm2_v4_f32 result = {
      {(float)v.x, (float)v.y, (float)v.z, (float)v.w}
  };
  return result;
}

LM2_API lm2_v4_i64 lm2_v4_u8_to_i64(lm2_v4_u8 v) {
  lm2_v4_i64 result = {
      {(int64_t)v.x, (int64_t)v.y, (int64_t)v.z, (int64_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i32 lm2_v4_u8_to_i32(lm2_v4_u8 v) {
  lm2_v4_i32 result = {
      {(int32_t)v.x, (int32_t)v.y, (int32_t)v.z, (int32_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i16 lm2_v4_u8_to_i16(lm2_v4_u8 v) {
  lm2_v4_i16 result = {
      {(int16_t)v.x, (int16_t)v.y, (int16_t)v.z, (int16_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_i8 lm2_v4_u8_to_i8(lm2_v4_u8 v) {
  LM2_ASSERT_UNSAFE(v.x <= INT8_MAX && v.y <= INT8_MAX && v.z <= INT8_MAX && v.w <= INT8_MAX);
  lm2_v4_i8 result = {
      {(int8_t)v.x, (int8_t)v.y, (int8_t)v.z, (int8_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u64 lm2_v4_u8_to_u64(lm2_v4_u8 v) {
  lm2_v4_u64 result = {
      {(uint64_t)v.x, (uint64_t)v.y, (uint64_t)v.z, (uint64_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u32 lm2_v4_u8_to_u32(lm2_v4_u8 v) {
  lm2_v4_u32 result = {
      {(uint32_t)v.x, (uint32_t)v.y, (uint32_t)v.z, (uint32_t)v.w}
  };
  return result;
}

LM2_API lm2_v4_u16 lm2_v4_u8_to_u16(lm2_v4_u8 v) {
  lm2_v4_u16 result = {
      {(uint16_t)v.x, (uint16_t)v.y, (uint16_t)v.z, (uint16_t)v.w}
  };
  return result;
}

// =============================================================================
// Vector Upcast Functions (v2 -> v3)
// =============================================================================

LM2_API lm2_v3_f64 lm2_v2_upcast_f64(lm2_v2_f64 v, double z) {
  lm2_v3_f64 result = {
      {v.x, v.y, z}
  };
  return result;
}

LM2_API lm2_v3_f32 lm2_v2_upcast_f32(lm2_v2_f32 v, float z) {
  lm2_v3_f32 result = {
      {v.x, v.y, z}
  };
  return result;
}

LM2_API lm2_v3_i64 lm2_v2_upcast_i64(lm2_v2_i64 v, int64_t z) {
  lm2_v3_i64 result = {
      {v.x, v.y, z}
  };
  return result;
}

LM2_API lm2_v3_i32 lm2_v2_upcast_i32(lm2_v2_i32 v, int32_t z) {
  lm2_v3_i32 result = {
      {v.x, v.y, z}
  };
  return result;
}

LM2_API lm2_v3_i16 lm2_v2_upcast_i16(lm2_v2_i16 v, int16_t z) {
  lm2_v3_i16 result = {
      {v.x, v.y, z}
  };
  return result;
}

LM2_API lm2_v3_i8 lm2_v2_upcast_i8(lm2_v2_i8 v, int8_t z) {
  lm2_v3_i8 result = {
      {v.x, v.y, z}
  };
  return result;
}

LM2_API lm2_v3_u64 lm2_v2_upcast_u64(lm2_v2_u64 v, uint64_t z) {
  lm2_v3_u64 result = {
      {v.x, v.y, z}
  };
  return result;
}

LM2_API lm2_v3_u32 lm2_v2_upcast_u32(lm2_v2_u32 v, uint32_t z) {
  lm2_v3_u32 result = {
      {v.x, v.y, z}
  };
  return result;
}

LM2_API lm2_v3_u16 lm2_v2_upcast_u16(lm2_v2_u16 v, uint16_t z) {
  lm2_v3_u16 result = {
      {v.x, v.y, z}
  };
  return result;
}

LM2_API lm2_v3_u8 lm2_v2_upcast_u8(lm2_v2_u8 v, uint8_t z) {
  lm2_v3_u8 result = {
      {v.x, v.y, z}
  };
  return result;
}

// =============================================================================
// Vector Upcast Functions (v3 -> v4)
// =============================================================================

LM2_API lm2_v4_f64 lm2_v3_upcast_f64(lm2_v3_f64 v, double w) {
  lm2_v4_f64 result = {
      {v.x, v.y, v.z, w}
  };
  return result;
}

LM2_API lm2_v4_f32 lm2_v3_upcast_f32(lm2_v3_f32 v, float w) {
  lm2_v4_f32 result = {
      {v.x, v.y, v.z, w}
  };
  return result;
}

LM2_API lm2_v4_i64 lm2_v3_upcast_i64(lm2_v3_i64 v, int64_t w) {
  lm2_v4_i64 result = {
      {v.x, v.y, v.z, w}
  };
  return result;
}

LM2_API lm2_v4_i32 lm2_v3_upcast_i32(lm2_v3_i32 v, int32_t w) {
  lm2_v4_i32 result = {
      {v.x, v.y, v.z, w}
  };
  return result;
}

LM2_API lm2_v4_i16 lm2_v3_upcast_i16(lm2_v3_i16 v, int16_t w) {
  lm2_v4_i16 result = {
      {v.x, v.y, v.z, w}
  };
  return result;
}

LM2_API lm2_v4_i8 lm2_v3_upcast_i8(lm2_v3_i8 v, int8_t w) {
  lm2_v4_i8 result = {
      {v.x, v.y, v.z, w}
  };
  return result;
}

LM2_API lm2_v4_u64 lm2_v3_upcast_u64(lm2_v3_u64 v, uint64_t w) {
  lm2_v4_u64 result = {
      {v.x, v.y, v.z, w}
  };
  return result;
}

LM2_API lm2_v4_u32 lm2_v3_upcast_u32(lm2_v3_u32 v, uint32_t w) {
  lm2_v4_u32 result = {
      {v.x, v.y, v.z, w}
  };
  return result;
}

LM2_API lm2_v4_u16 lm2_v3_upcast_u16(lm2_v3_u16 v, uint16_t w) {
  lm2_v4_u16 result = {
      {v.x, v.y, v.z, w}
  };
  return result;
}

LM2_API lm2_v4_u8 lm2_v3_upcast_u8(lm2_v3_u8 v, uint8_t w) {
  lm2_v4_u8 result = {
      {v.x, v.y, v.z, w}
  };
  return result;
}

// =============================================================================
// Vector Downcast Functions (v3 -> v2)
// =============================================================================

LM2_API lm2_v2_f64 lm2_v3_downcast_f64(lm2_v3_f64 v) {
  lm2_v2_f64 result = {
      {v.x, v.y}
  };
  return result;
}

LM2_API lm2_v2_f32 lm2_v3_downcast_f32(lm2_v3_f32 v) {
  lm2_v2_f32 result = {
      {v.x, v.y}
  };
  return result;
}

LM2_API lm2_v2_i64 lm2_v3_downcast_i64(lm2_v3_i64 v) {
  lm2_v2_i64 result = {
      {v.x, v.y}
  };
  return result;
}

LM2_API lm2_v2_i32 lm2_v3_downcast_i32(lm2_v3_i32 v) {
  lm2_v2_i32 result = {
      {v.x, v.y}
  };
  return result;
}

LM2_API lm2_v2_i16 lm2_v3_downcast_i16(lm2_v3_i16 v) {
  lm2_v2_i16 result = {
      {v.x, v.y}
  };
  return result;
}

LM2_API lm2_v2_i8 lm2_v3_downcast_i8(lm2_v3_i8 v) {
  lm2_v2_i8 result = {
      {v.x, v.y}
  };
  return result;
}

LM2_API lm2_v2_u64 lm2_v3_downcast_u64(lm2_v3_u64 v) {
  lm2_v2_u64 result = {
      {v.x, v.y}
  };
  return result;
}

LM2_API lm2_v2_u32 lm2_v3_downcast_u32(lm2_v3_u32 v) {
  lm2_v2_u32 result = {
      {v.x, v.y}
  };
  return result;
}

LM2_API lm2_v2_u16 lm2_v3_downcast_u16(lm2_v3_u16 v) {
  lm2_v2_u16 result = {
      {v.x, v.y}
  };
  return result;
}

LM2_API lm2_v2_u8 lm2_v3_downcast_u8(lm2_v3_u8 v) {
  lm2_v2_u8 result = {
      {v.x, v.y}
  };
  return result;
}

// =============================================================================
// Vector Downcast Functions (v4 -> v3)
// =============================================================================

LM2_API lm2_v3_f64 lm2_v4_downcast_f64(lm2_v4_f64 v) {
  lm2_v3_f64 result = {
      {v.x, v.y, v.z}
  };
  return result;
}

LM2_API lm2_v3_f32 lm2_v4_downcast_f32(lm2_v4_f32 v) {
  lm2_v3_f32 result = {
      {v.x, v.y, v.z}
  };
  return result;
}

LM2_API lm2_v3_i64 lm2_v4_downcast_i64(lm2_v4_i64 v) {
  lm2_v3_i64 result = {
      {v.x, v.y, v.z}
  };
  return result;
}

LM2_API lm2_v3_i32 lm2_v4_downcast_i32(lm2_v4_i32 v) {
  lm2_v3_i32 result = {
      {v.x, v.y, v.z}
  };
  return result;
}

LM2_API lm2_v3_i16 lm2_v4_downcast_i16(lm2_v4_i16 v) {
  lm2_v3_i16 result = {
      {v.x, v.y, v.z}
  };
  return result;
}

LM2_API lm2_v3_i8 lm2_v4_downcast_i8(lm2_v4_i8 v) {
  lm2_v3_i8 result = {
      {v.x, v.y, v.z}
  };
  return result;
}

LM2_API lm2_v3_u64 lm2_v4_downcast_u64(lm2_v4_u64 v) {
  lm2_v3_u64 result = {
      {v.x, v.y, v.z}
  };
  return result;
}

LM2_API lm2_v3_u32 lm2_v4_downcast_u32(lm2_v4_u32 v) {
  lm2_v3_u32 result = {
      {v.x, v.y, v.z}
  };
  return result;
}

LM2_API lm2_v3_u16 lm2_v4_downcast_u16(lm2_v4_u16 v) {
  lm2_v3_u16 result = {
      {v.x, v.y, v.z}
  };
  return result;
}

LM2_API lm2_v3_u8 lm2_v4_downcast_u8(lm2_v4_u8 v) {
  lm2_v3_u8 result = {
      {v.x, v.y, v.z}
  };
  return result;
}
