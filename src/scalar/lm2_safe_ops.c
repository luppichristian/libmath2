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

#include <lm2/scalar/lm2_safe_ops.h>

LM2_API double lm2_add_f64(double a, double b) {
  double result = a + b;

  // Assert no overflow (finite inputs must produce finite output)
  LM2_ASSERT_UNSAFE(isfinite(a) && isfinite(b));
  LM2_ASSERT_UNSAFE(isfinite(result));

  // Assert no underflow to subnormal (optional, depending on policy)
  LM2_ASSERT_UNSAFE(result == 0.0 || fabs(result) >= DBL_MIN);
  return result;
}

LM2_API float lm2_add_f32(float a, float b) {
  float result = a + b;

  // Assert no overflow (finite inputs must produce finite output)
  LM2_ASSERT_UNSAFE(isfinite(a) && isfinite(b));
  LM2_ASSERT_UNSAFE(isfinite(result));

  // Assert no underflow to subnormal (optional, depending on policy)
  LM2_ASSERT_UNSAFE(result == 0.0f || fabsf(result) >= FLT_MIN);
  return result;
}

LM2_API int64_t lm2_add_i64(int64_t a, int64_t b) {
  int64_t result = a + b;
  // Check for overflow: if both operands have same sign, result must have same sign
  LM2_ASSERT_UNSAFE(!((a > 0 && b > 0 && result < 0) || (a < 0 && b < 0 && result > 0)));
  return result;
}

LM2_API int32_t lm2_add_i32(int32_t a, int32_t b) {
  int32_t result = a + b;
  LM2_ASSERT_UNSAFE(!((a > 0 && b > 0 && result < 0) || (a < 0 && b < 0 && result > 0)));
  return result;
}

LM2_API int16_t lm2_add_i16(int16_t a, int16_t b) {
  int16_t result = a + b;
  LM2_ASSERT_UNSAFE(!((a > 0 && b > 0 && result < 0) || (a < 0 && b < 0 && result > 0)));
  return result;
}

LM2_API int8_t lm2_add_i8(int8_t a, int8_t b) {
  int8_t result = a + b;
  LM2_ASSERT_UNSAFE(!((a > 0 && b > 0 && result < 0) || (a < 0 && b < 0 && result > 0)));
  return result;
}

LM2_API uint64_t lm2_add_u64(uint64_t a, uint64_t b) {
  uint64_t result = a + b;
  // Check for overflow: result must be >= both operands
  LM2_ASSERT_UNSAFE(result >= a && result >= b);
  return result;
}

LM2_API uint32_t lm2_add_u32(uint32_t a, uint32_t b) {
  uint32_t result = a + b;
  LM2_ASSERT_UNSAFE(result >= a && result >= b);
  return result;
}

LM2_API uint16_t lm2_add_u16(uint16_t a, uint16_t b) {
  uint16_t result = a + b;
  LM2_ASSERT_UNSAFE(result >= a && result >= b);
  return result;
}

LM2_API uint8_t lm2_add_u8(uint8_t a, uint8_t b) {
  uint8_t result = a + b;
  LM2_ASSERT_UNSAFE(result >= a && result >= b);
  return result;
}

// =============================================================================
// Subtraction operations
// =============================================================================

LM2_API double lm2_sub_f64(double a, double b) {
  double result = a - b;
  LM2_ASSERT_UNSAFE(isfinite(a) && isfinite(b));
  LM2_ASSERT_UNSAFE(isfinite(result));
  LM2_ASSERT_UNSAFE(result == 0.0 || fabs(result) >= DBL_MIN);
  return result;
}

LM2_API float lm2_sub_f32(float a, float b) {
  float result = a - b;
  LM2_ASSERT_UNSAFE(isfinite(a) && isfinite(b));
  LM2_ASSERT_UNSAFE(isfinite(result));
  LM2_ASSERT_UNSAFE(result == 0.0f || fabsf(result) >= FLT_MIN);
  return result;
}

LM2_API int64_t lm2_sub_i64(int64_t a, int64_t b) {
  int64_t result = a - b;
  // Check for overflow: subtracting negative can overflow, subtracting positive can underflow
  LM2_ASSERT_UNSAFE(!((b < 0 && a > INT64_MAX + b) || (b > 0 && a < INT64_MIN + b)));
  return result;
}

LM2_API int32_t lm2_sub_i32(int32_t a, int32_t b) {
  int32_t result = a - b;
  LM2_ASSERT_UNSAFE(!((b < 0 && a > INT32_MAX + b) || (b > 0 && a < INT32_MIN + b)));
  return result;
}

LM2_API int16_t lm2_sub_i16(int16_t a, int16_t b) {
  int16_t result = a - b;
  LM2_ASSERT_UNSAFE(!((b < 0 && a > INT16_MAX + b) || (b > 0 && a < INT16_MIN + b)));
  return result;
}

LM2_API int8_t lm2_sub_i8(int8_t a, int8_t b) {
  int8_t result = a - b;
  LM2_ASSERT_UNSAFE(!((b < 0 && a > INT8_MAX + b) || (b > 0 && a < INT8_MIN + b)));
  return result;
}

LM2_API uint64_t lm2_sub_u64(uint64_t a, uint64_t b) {
  // Check for underflow: a must be >= b
  LM2_ASSERT_UNSAFE(a >= b);
  return a - b;
}

LM2_API uint32_t lm2_sub_u32(uint32_t a, uint32_t b) {
  LM2_ASSERT_UNSAFE(a >= b);
  return a - b;
}

LM2_API uint16_t lm2_sub_u16(uint16_t a, uint16_t b) {
  LM2_ASSERT_UNSAFE(a >= b);
  return a - b;
}

LM2_API uint8_t lm2_sub_u8(uint8_t a, uint8_t b) {
  LM2_ASSERT_UNSAFE(a >= b);
  return a - b;
}

// =============================================================================
// Multiplication operations
// =============================================================================

LM2_API double lm2_mul_f64(double a, double b) {
  double result = a * b;
  LM2_ASSERT_UNSAFE(isfinite(a) && isfinite(b));
  LM2_ASSERT_UNSAFE(isfinite(result));
  LM2_ASSERT_UNSAFE(result == 0.0 || fabs(result) >= DBL_MIN);
  return result;
}

LM2_API float lm2_mul_f32(float a, float b) {
  float result = a * b;
  LM2_ASSERT_UNSAFE(isfinite(a) && isfinite(b));
  LM2_ASSERT_UNSAFE(isfinite(result));
  LM2_ASSERT_UNSAFE(result == 0.0f || fabsf(result) >= FLT_MIN);
  return result;
}

LM2_API int64_t lm2_mul_i64(int64_t a, int64_t b) {
  // Special cases
  if (a == 0 || b == 0) return 0;

  int64_t result = a * b;
  // Check for overflow by dividing back
  LM2_ASSERT_UNSAFE(result / b == a);
  // Special case: INT64_MIN * -1 overflows
  LM2_ASSERT_UNSAFE(!(a == INT64_MIN && b == -1));
  return result;
}

LM2_API int32_t lm2_mul_i32(int32_t a, int32_t b) {
  if (a == 0 || b == 0) return 0;

  int32_t result = a * b;
  LM2_ASSERT_UNSAFE(result / b == a);
  LM2_ASSERT_UNSAFE(!(a == INT32_MIN && b == -1));
  return result;
}

LM2_API int16_t lm2_mul_i16(int16_t a, int16_t b) {
  if (a == 0 || b == 0) return 0;

  int16_t result = a * b;
  LM2_ASSERT_UNSAFE(result / b == a);
  LM2_ASSERT_UNSAFE(!(a == INT16_MIN && b == -1));
  return result;
}

LM2_API int8_t lm2_mul_i8(int8_t a, int8_t b) {
  if (a == 0 || b == 0) return 0;

  int8_t result = a * b;
  LM2_ASSERT_UNSAFE(result / b == a);
  LM2_ASSERT_UNSAFE(!(a == INT8_MIN && b == -1));
  return result;
}

LM2_API uint64_t lm2_mul_u64(uint64_t a, uint64_t b) {
  if (a == 0 || b == 0) return 0;

  uint64_t result = a * b;
  // Check for overflow by dividing back
  LM2_ASSERT_UNSAFE(result / b == a);
  return result;
}

LM2_API uint32_t lm2_mul_u32(uint32_t a, uint32_t b) {
  if (a == 0 || b == 0) return 0;

  uint32_t result = a * b;
  LM2_ASSERT_UNSAFE(result / b == a);
  return result;
}

LM2_API uint16_t lm2_mul_u16(uint16_t a, uint16_t b) {
  if (a == 0 || b == 0) return 0;

  uint16_t result = a * b;
  LM2_ASSERT_UNSAFE(result / b == a);
  return result;
}

LM2_API uint8_t lm2_mul_u8(uint8_t a, uint8_t b) {
  if (a == 0 || b == 0) return 0;

  uint8_t result = a * b;
  LM2_ASSERT_UNSAFE(result / b == a);
  return result;
}

// =============================================================================
// Division operations
// =============================================================================

LM2_API double lm2_div_f64(double a, double b) {
  // Assert no division by zero
  LM2_ASSERT_UNSAFE(b != 0.0);
  LM2_ASSERT_UNSAFE(isfinite(a) && isfinite(b));

  double result = a / b;
  LM2_ASSERT_UNSAFE(isfinite(result));
  LM2_ASSERT_UNSAFE(result == 0.0 || fabs(result) >= DBL_MIN);
  return result;
}

LM2_API float lm2_div_f32(float a, float b) {
  LM2_ASSERT_UNSAFE(b != 0.0f);
  LM2_ASSERT_UNSAFE(isfinite(a) && isfinite(b));

  float result = a / b;
  LM2_ASSERT_UNSAFE(isfinite(result));
  LM2_ASSERT_UNSAFE(result == 0.0f || fabsf(result) >= FLT_MIN);
  return result;
}

LM2_API int64_t lm2_div_i64(int64_t a, int64_t b) {
  // Assert no division by zero
  LM2_ASSERT_UNSAFE(b != 0);
  // Assert no overflow (INT64_MIN / -1 overflows)
  LM2_ASSERT_UNSAFE(!(a == INT64_MIN && b == -1));
  return a / b;
}

LM2_API int32_t lm2_div_i32(int32_t a, int32_t b) {
  LM2_ASSERT_UNSAFE(b != 0);
  LM2_ASSERT_UNSAFE(!(a == INT32_MIN && b == -1));
  return a / b;
}

LM2_API int16_t lm2_div_i16(int16_t a, int16_t b) {
  LM2_ASSERT_UNSAFE(b != 0);
  LM2_ASSERT_UNSAFE(!(a == INT16_MIN && b == -1));
  return a / b;
}

LM2_API int8_t lm2_div_i8(int8_t a, int8_t b) {
  LM2_ASSERT_UNSAFE(b != 0);
  LM2_ASSERT_UNSAFE(!(a == INT8_MIN && b == -1));
  return a / b;
}

LM2_API uint64_t lm2_div_u64(uint64_t a, uint64_t b) {
  LM2_ASSERT_UNSAFE(b != 0);
  return a / b;
}

LM2_API uint32_t lm2_div_u32(uint32_t a, uint32_t b) {
  LM2_ASSERT_UNSAFE(b != 0);
  return a / b;
}

LM2_API uint16_t lm2_div_u16(uint16_t a, uint16_t b) {
  LM2_ASSERT_UNSAFE(b != 0);
  return a / b;
}

LM2_API uint8_t lm2_div_u8(uint8_t a, uint8_t b) {
  LM2_ASSERT_UNSAFE(b != 0);
  return a / b;
}
