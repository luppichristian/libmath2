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

#include <gtest/gtest.h>
#include "lm2/ranges/lm2_range_conversions.h"

// Test fixture for range conversions tests
class RangeConversionsTest : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-6f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Range2 Conversions - Floating Point
// =============================================================================

TEST_F(RangeConversionsTest, Range2_F64ToF32) {
  lm2_r2_f64 r_f64 = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(1.5, 2.5), lm2_v2_make_f64(5.5, 6.5));
  lm2_r2_f32 r_f32 = lm2_r2_f64_to_f32(r_f64);

  EXPECT_FLOAT_EQ(r_f32.min.x, 1.5f);
  EXPECT_FLOAT_EQ(r_f32.min.y, 2.5f);
  EXPECT_FLOAT_EQ(r_f32.max.x, 5.5f);
  EXPECT_FLOAT_EQ(r_f32.max.y, 6.5f);
}

TEST_F(RangeConversionsTest, Range2_F32ToF64) {
  lm2_r2_f32 r_f32 = lm2_r2_from_min_max_f32(
      lm2_v2_make_f32(1.5f, 2.5f), lm2_v2_make_f32(5.5f, 6.5f));
  lm2_r2_f64 r_f64 = lm2_r2_f32_to_f64(r_f32);

  EXPECT_NEAR(r_f64.min.x, 1.5, EPSILON_F32);
  EXPECT_NEAR(r_f64.min.y, 2.5, EPSILON_F32);
  EXPECT_NEAR(r_f64.max.x, 5.5, EPSILON_F32);
  EXPECT_NEAR(r_f64.max.y, 6.5, EPSILON_F32);
}

// =============================================================================
// Range2 Conversions - Float to Integer
// =============================================================================

TEST_F(RangeConversionsTest, Range2_F64ToI32) {
  lm2_r2_f64 r_f64 = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(1.9, 2.1), lm2_v2_make_f64(5.7, 6.3));
  lm2_r2_i32 r_i32 = lm2_r2_f64_to_i32(r_f64);

  EXPECT_EQ(r_i32.min.x, 1);
  EXPECT_EQ(r_i32.min.y, 2);
  EXPECT_EQ(r_i32.max.x, 5);
  EXPECT_EQ(r_i32.max.y, 6);
}

TEST_F(RangeConversionsTest, Range2_F32ToI32) {
  lm2_r2_f32 r_f32 = lm2_r2_from_min_max_f32(
      lm2_v2_make_f32(1.9f, 2.1f), lm2_v2_make_f32(5.7f, 6.3f));
  lm2_r2_i32 r_i32 = lm2_r2_f32_to_i32(r_f32);

  EXPECT_EQ(r_i32.min.x, 1);
  EXPECT_EQ(r_i32.min.y, 2);
  EXPECT_EQ(r_i32.max.x, 5);
  EXPECT_EQ(r_i32.max.y, 6);
}

TEST_F(RangeConversionsTest, Range2_F64ToU32) {
  lm2_r2_f64 r_f64 = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(1.9, 2.1), lm2_v2_make_f64(5.7, 6.3));
  lm2_r2_u32 r_u32 = lm2_r2_f64_to_u32(r_f64);

  EXPECT_EQ(r_u32.min.x, 1u);
  EXPECT_EQ(r_u32.min.y, 2u);
  EXPECT_EQ(r_u32.max.x, 5u);
  EXPECT_EQ(r_u32.max.y, 6u);
}

// =============================================================================
// Range2 Conversions - Integer to Float
// =============================================================================

TEST_F(RangeConversionsTest, Range2_I32ToF64) {
  lm2_r2_i32 r_i32 = lm2_r2_from_min_max_i32(
      lm2_v2_make_i32(1, 2), lm2_v2_make_i32(5, 6));
  lm2_r2_f64 r_f64 = lm2_r2_i32_to_f64(r_i32);

  EXPECT_DOUBLE_EQ(r_f64.min.x, 1.0);
  EXPECT_DOUBLE_EQ(r_f64.min.y, 2.0);
  EXPECT_DOUBLE_EQ(r_f64.max.x, 5.0);
  EXPECT_DOUBLE_EQ(r_f64.max.y, 6.0);
}

TEST_F(RangeConversionsTest, Range2_I32ToF32) {
  lm2_r2_i32 r_i32 = lm2_r2_from_min_max_i32(
      lm2_v2_make_i32(1, 2), lm2_v2_make_i32(5, 6));
  lm2_r2_f32 r_f32 = lm2_r2_i32_to_f32(r_i32);

  EXPECT_FLOAT_EQ(r_f32.min.x, 1.0f);
  EXPECT_FLOAT_EQ(r_f32.min.y, 2.0f);
  EXPECT_FLOAT_EQ(r_f32.max.x, 5.0f);
  EXPECT_FLOAT_EQ(r_f32.max.y, 6.0f);
}

TEST_F(RangeConversionsTest, Range2_U32ToF64) {
  lm2_r2_u32 r_u32 = lm2_r2_from_min_max_u32(
      lm2_v2_make_u32(1, 2), lm2_v2_make_u32(5, 6));
  lm2_r2_f64 r_f64 = lm2_r2_u32_to_f64(r_u32);

  EXPECT_DOUBLE_EQ(r_f64.min.x, 1.0);
  EXPECT_DOUBLE_EQ(r_f64.min.y, 2.0);
  EXPECT_DOUBLE_EQ(r_f64.max.x, 5.0);
  EXPECT_DOUBLE_EQ(r_f64.max.y, 6.0);
}

// =============================================================================
// Range2 Conversions - Integer Width Changes
// =============================================================================

TEST_F(RangeConversionsTest, Range2_I64ToI32) {
  lm2_r2_i64 r_i64 = lm2_r2_from_min_max_i64(
      lm2_v2_make_i64(1, 2), lm2_v2_make_i64(5, 6));
  lm2_r2_i32 r_i32 = lm2_r2_i64_to_i32(r_i64);

  EXPECT_EQ(r_i32.min.x, 1);
  EXPECT_EQ(r_i32.min.y, 2);
  EXPECT_EQ(r_i32.max.x, 5);
  EXPECT_EQ(r_i32.max.y, 6);
}

TEST_F(RangeConversionsTest, Range2_I32ToI64) {
  lm2_r2_i32 r_i32 = lm2_r2_from_min_max_i32(
      lm2_v2_make_i32(1, 2), lm2_v2_make_i32(5, 6));
  lm2_r2_i64 r_i64 = lm2_r2_i32_to_i64(r_i32);

  EXPECT_EQ(r_i64.min.x, 1);
  EXPECT_EQ(r_i64.min.y, 2);
  EXPECT_EQ(r_i64.max.x, 5);
  EXPECT_EQ(r_i64.max.y, 6);
}

TEST_F(RangeConversionsTest, Range2_I32ToI16) {
  lm2_r2_i32 r_i32 = lm2_r2_from_min_max_i32(
      lm2_v2_make_i32(100, 200), lm2_v2_make_i32(500, 600));
  lm2_r2_i16 r_i16 = lm2_r2_i32_to_i16(r_i32);

  EXPECT_EQ(r_i16.min.x, 100);
  EXPECT_EQ(r_i16.min.y, 200);
  EXPECT_EQ(r_i16.max.x, 500);
  EXPECT_EQ(r_i16.max.y, 600);
}

TEST_F(RangeConversionsTest, Range2_I16ToI32) {
  lm2_r2_i16 r_i16 = lm2_r2_from_min_max_i16(
      lm2_v2_make_i16(100, 200), lm2_v2_make_i16(500, 600));
  lm2_r2_i32 r_i32 = lm2_r2_i16_to_i32(r_i16);

  EXPECT_EQ(r_i32.min.x, 100);
  EXPECT_EQ(r_i32.min.y, 200);
  EXPECT_EQ(r_i32.max.x, 500);
  EXPECT_EQ(r_i32.max.y, 600);
}

// =============================================================================
// Range2 Conversions - Signed/Unsigned
// =============================================================================

TEST_F(RangeConversionsTest, Range2_I32ToU32) {
  lm2_r2_i32 r_i32 = lm2_r2_from_min_max_i32(
      lm2_v2_make_i32(1, 2), lm2_v2_make_i32(5, 6));
  lm2_r2_u32 r_u32 = lm2_r2_i32_to_u32(r_i32);

  EXPECT_EQ(r_u32.min.x, 1u);
  EXPECT_EQ(r_u32.min.y, 2u);
  EXPECT_EQ(r_u32.max.x, 5u);
  EXPECT_EQ(r_u32.max.y, 6u);
}

TEST_F(RangeConversionsTest, Range2_U32ToI32) {
  lm2_r2_u32 r_u32 = lm2_r2_from_min_max_u32(
      lm2_v2_make_u32(1, 2), lm2_v2_make_u32(5, 6));
  lm2_r2_i32 r_i32 = lm2_r2_u32_to_i32(r_u32);

  EXPECT_EQ(r_i32.min.x, 1);
  EXPECT_EQ(r_i32.min.y, 2);
  EXPECT_EQ(r_i32.max.x, 5);
  EXPECT_EQ(r_i32.max.y, 6);
}

// =============================================================================
// Range3 Conversions - Floating Point
// =============================================================================

TEST_F(RangeConversionsTest, Range3_F64ToF32) {
  lm2_r3_f64 r_f64 = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(1.5, 2.5, 3.5), lm2_v3_make_f64(5.5, 6.5, 7.5));
  lm2_r3_f32 r_f32 = lm2_r3_f64_to_f32(r_f64);

  EXPECT_FLOAT_EQ(r_f32.min.x, 1.5f);
  EXPECT_FLOAT_EQ(r_f32.min.y, 2.5f);
  EXPECT_FLOAT_EQ(r_f32.min.z, 3.5f);
  EXPECT_FLOAT_EQ(r_f32.max.x, 5.5f);
  EXPECT_FLOAT_EQ(r_f32.max.y, 6.5f);
  EXPECT_FLOAT_EQ(r_f32.max.z, 7.5f);
}

TEST_F(RangeConversionsTest, Range3_F32ToF64) {
  lm2_r3_f32 r_f32 = lm2_r3_from_min_max_f32(
      lm2_v3_make_f32(1.5f, 2.5f, 3.5f), lm2_v3_make_f32(5.5f, 6.5f, 7.5f));
  lm2_r3_f64 r_f64 = lm2_r3_f32_to_f64(r_f32);

  EXPECT_NEAR(r_f64.min.x, 1.5, EPSILON_F32);
  EXPECT_NEAR(r_f64.min.y, 2.5, EPSILON_F32);
  EXPECT_NEAR(r_f64.min.z, 3.5, EPSILON_F32);
  EXPECT_NEAR(r_f64.max.x, 5.5, EPSILON_F32);
  EXPECT_NEAR(r_f64.max.y, 6.5, EPSILON_F32);
  EXPECT_NEAR(r_f64.max.z, 7.5, EPSILON_F32);
}

// =============================================================================
// Range3 Conversions - Float to Integer
// =============================================================================

TEST_F(RangeConversionsTest, Range3_F64ToI32) {
  lm2_r3_f64 r_f64 = lm2_r3_from_min_max_f64(
      lm2_v3_make_f64(1.9, 2.1, 3.7), lm2_v3_make_f64(5.7, 6.3, 8.2));
  lm2_r3_i32 r_i32 = lm2_r3_f64_to_i32(r_f64);

  EXPECT_EQ(r_i32.min.x, 1);
  EXPECT_EQ(r_i32.min.y, 2);
  EXPECT_EQ(r_i32.min.z, 3);
  EXPECT_EQ(r_i32.max.x, 5);
  EXPECT_EQ(r_i32.max.y, 6);
  EXPECT_EQ(r_i32.max.z, 8);
}

TEST_F(RangeConversionsTest, Range3_F32ToI32) {
  lm2_r3_f32 r_f32 = lm2_r3_from_min_max_f32(
      lm2_v3_make_f32(1.9f, 2.1f, 3.7f), lm2_v3_make_f32(5.7f, 6.3f, 8.2f));
  lm2_r3_i32 r_i32 = lm2_r3_f32_to_i32(r_f32);

  EXPECT_EQ(r_i32.min.x, 1);
  EXPECT_EQ(r_i32.min.y, 2);
  EXPECT_EQ(r_i32.min.z, 3);
  EXPECT_EQ(r_i32.max.x, 5);
  EXPECT_EQ(r_i32.max.y, 6);
  EXPECT_EQ(r_i32.max.z, 8);
}

// =============================================================================
// Range3 Conversions - Integer to Float
// =============================================================================

TEST_F(RangeConversionsTest, Range3_I32ToF64) {
  lm2_r3_i32 r_i32 = lm2_r3_from_min_max_i32(
      lm2_v3_make_i32(1, 2, 3), lm2_v3_make_i32(5, 6, 7));
  lm2_r3_f64 r_f64 = lm2_r3_i32_to_f64(r_i32);

  EXPECT_DOUBLE_EQ(r_f64.min.x, 1.0);
  EXPECT_DOUBLE_EQ(r_f64.min.y, 2.0);
  EXPECT_DOUBLE_EQ(r_f64.min.z, 3.0);
  EXPECT_DOUBLE_EQ(r_f64.max.x, 5.0);
  EXPECT_DOUBLE_EQ(r_f64.max.y, 6.0);
  EXPECT_DOUBLE_EQ(r_f64.max.z, 7.0);
}

TEST_F(RangeConversionsTest, Range3_I32ToF32) {
  lm2_r3_i32 r_i32 = lm2_r3_from_min_max_i32(
      lm2_v3_make_i32(1, 2, 3), lm2_v3_make_i32(5, 6, 7));
  lm2_r3_f32 r_f32 = lm2_r3_i32_to_f32(r_i32);

  EXPECT_FLOAT_EQ(r_f32.min.x, 1.0f);
  EXPECT_FLOAT_EQ(r_f32.min.y, 2.0f);
  EXPECT_FLOAT_EQ(r_f32.min.z, 3.0f);
  EXPECT_FLOAT_EQ(r_f32.max.x, 5.0f);
  EXPECT_FLOAT_EQ(r_f32.max.y, 6.0f);
  EXPECT_FLOAT_EQ(r_f32.max.z, 7.0f);
}

// =============================================================================
// Range3 Conversions - Integer Width Changes
// =============================================================================

TEST_F(RangeConversionsTest, Range3_I64ToI32) {
  lm2_r3_i64 r_i64 = lm2_r3_from_min_max_i64(
      lm2_v3_make_i64(1, 2, 3), lm2_v3_make_i64(5, 6, 7));
  lm2_r3_i32 r_i32 = lm2_r3_i64_to_i32(r_i64);

  EXPECT_EQ(r_i32.min.x, 1);
  EXPECT_EQ(r_i32.min.y, 2);
  EXPECT_EQ(r_i32.min.z, 3);
  EXPECT_EQ(r_i32.max.x, 5);
  EXPECT_EQ(r_i32.max.y, 6);
  EXPECT_EQ(r_i32.max.z, 7);
}

TEST_F(RangeConversionsTest, Range3_I32ToI64) {
  lm2_r3_i32 r_i32 = lm2_r3_from_min_max_i32(
      lm2_v3_make_i32(1, 2, 3), lm2_v3_make_i32(5, 6, 7));
  lm2_r3_i64 r_i64 = lm2_r3_i32_to_i64(r_i32);

  EXPECT_EQ(r_i64.min.x, 1);
  EXPECT_EQ(r_i64.min.y, 2);
  EXPECT_EQ(r_i64.min.z, 3);
  EXPECT_EQ(r_i64.max.x, 5);
  EXPECT_EQ(r_i64.max.y, 6);
  EXPECT_EQ(r_i64.max.z, 7);
}

// =============================================================================
// Range4 Conversions - Floating Point
// =============================================================================

TEST_F(RangeConversionsTest, Range4_F64ToF32) {
  lm2_r4_f64 r_f64 = lm2_r4_from_min_max_f64(
      lm2_v4_make_f64(1.5, 2.5, 3.5, 4.5), lm2_v4_make_f64(5.5, 6.5, 7.5, 8.5));
  lm2_r4_f32 r_f32 = lm2_r4_f64_to_f32(r_f64);

  EXPECT_FLOAT_EQ(r_f32.min.x, 1.5f);
  EXPECT_FLOAT_EQ(r_f32.min.y, 2.5f);
  EXPECT_FLOAT_EQ(r_f32.min.z, 3.5f);
  EXPECT_FLOAT_EQ(r_f32.min.w, 4.5f);
  EXPECT_FLOAT_EQ(r_f32.max.x, 5.5f);
  EXPECT_FLOAT_EQ(r_f32.max.y, 6.5f);
  EXPECT_FLOAT_EQ(r_f32.max.z, 7.5f);
  EXPECT_FLOAT_EQ(r_f32.max.w, 8.5f);
}

TEST_F(RangeConversionsTest, Range4_F32ToF64) {
  lm2_r4_f32 r_f32 = lm2_r4_from_min_max_f32(
      lm2_v4_make_f32(1.5f, 2.5f, 3.5f, 4.5f), lm2_v4_make_f32(5.5f, 6.5f, 7.5f, 8.5f));
  lm2_r4_f64 r_f64 = lm2_r4_f32_to_f64(r_f32);

  EXPECT_NEAR(r_f64.min.x, 1.5, EPSILON_F32);
  EXPECT_NEAR(r_f64.min.y, 2.5, EPSILON_F32);
  EXPECT_NEAR(r_f64.min.z, 3.5, EPSILON_F32);
  EXPECT_NEAR(r_f64.min.w, 4.5, EPSILON_F32);
  EXPECT_NEAR(r_f64.max.x, 5.5, EPSILON_F32);
  EXPECT_NEAR(r_f64.max.y, 6.5, EPSILON_F32);
  EXPECT_NEAR(r_f64.max.z, 7.5, EPSILON_F32);
  EXPECT_NEAR(r_f64.max.w, 8.5, EPSILON_F32);
}

// =============================================================================
// Range4 Conversions - Float to Integer
// =============================================================================

TEST_F(RangeConversionsTest, Range4_F64ToI32) {
  lm2_r4_f64 r_f64 = lm2_r4_from_min_max_f64(
      lm2_v4_make_f64(1.9, 2.1, 3.7, 4.3), lm2_v4_make_f64(5.7, 6.3, 8.2, 9.8));
  lm2_r4_i32 r_i32 = lm2_r4_f64_to_i32(r_f64);

  EXPECT_EQ(r_i32.min.x, 1);
  EXPECT_EQ(r_i32.min.y, 2);
  EXPECT_EQ(r_i32.min.z, 3);
  EXPECT_EQ(r_i32.min.w, 4);
  EXPECT_EQ(r_i32.max.x, 5);
  EXPECT_EQ(r_i32.max.y, 6);
  EXPECT_EQ(r_i32.max.z, 8);
  EXPECT_EQ(r_i32.max.w, 9);
}

TEST_F(RangeConversionsTest, Range4_F32ToI32) {
  lm2_r4_f32 r_f32 = lm2_r4_from_min_max_f32(
      lm2_v4_make_f32(1.9f, 2.1f, 3.7f, 4.3f), lm2_v4_make_f32(5.7f, 6.3f, 8.2f, 9.8f));
  lm2_r4_i32 r_i32 = lm2_r4_f32_to_i32(r_f32);

  EXPECT_EQ(r_i32.min.x, 1);
  EXPECT_EQ(r_i32.min.y, 2);
  EXPECT_EQ(r_i32.min.z, 3);
  EXPECT_EQ(r_i32.min.w, 4);
  EXPECT_EQ(r_i32.max.x, 5);
  EXPECT_EQ(r_i32.max.y, 6);
  EXPECT_EQ(r_i32.max.z, 8);
  EXPECT_EQ(r_i32.max.w, 9);
}

// =============================================================================
// Range4 Conversions - Integer to Float
// =============================================================================

TEST_F(RangeConversionsTest, Range4_I32ToF64) {
  lm2_r4_i32 r_i32 = lm2_r4_from_min_max_i32(
      lm2_v4_make_i32(1, 2, 3, 4), lm2_v4_make_i32(5, 6, 7, 8));
  lm2_r4_f64 r_f64 = lm2_r4_i32_to_f64(r_i32);

  EXPECT_DOUBLE_EQ(r_f64.min.x, 1.0);
  EXPECT_DOUBLE_EQ(r_f64.min.y, 2.0);
  EXPECT_DOUBLE_EQ(r_f64.min.z, 3.0);
  EXPECT_DOUBLE_EQ(r_f64.min.w, 4.0);
  EXPECT_DOUBLE_EQ(r_f64.max.x, 5.0);
  EXPECT_DOUBLE_EQ(r_f64.max.y, 6.0);
  EXPECT_DOUBLE_EQ(r_f64.max.z, 7.0);
  EXPECT_DOUBLE_EQ(r_f64.max.w, 8.0);
}

TEST_F(RangeConversionsTest, Range4_I32ToF32) {
  lm2_r4_i32 r_i32 = lm2_r4_from_min_max_i32(
      lm2_v4_make_i32(1, 2, 3, 4), lm2_v4_make_i32(5, 6, 7, 8));
  lm2_r4_f32 r_f32 = lm2_r4_i32_to_f32(r_i32);

  EXPECT_FLOAT_EQ(r_f32.min.x, 1.0f);
  EXPECT_FLOAT_EQ(r_f32.min.y, 2.0f);
  EXPECT_FLOAT_EQ(r_f32.min.z, 3.0f);
  EXPECT_FLOAT_EQ(r_f32.min.w, 4.0f);
  EXPECT_FLOAT_EQ(r_f32.max.x, 5.0f);
  EXPECT_FLOAT_EQ(r_f32.max.y, 6.0f);
  EXPECT_FLOAT_EQ(r_f32.max.z, 7.0f);
  EXPECT_FLOAT_EQ(r_f32.max.w, 8.0f);
}

// =============================================================================
// Range4 Conversions - Integer Width Changes
// =============================================================================

TEST_F(RangeConversionsTest, Range4_I64ToI32) {
  lm2_r4_i64 r_i64 = lm2_r4_from_min_max_i64(
      lm2_v4_make_i64(1, 2, 3, 4), lm2_v4_make_i64(5, 6, 7, 8));
  lm2_r4_i32 r_i32 = lm2_r4_i64_to_i32(r_i64);

  EXPECT_EQ(r_i32.min.x, 1);
  EXPECT_EQ(r_i32.min.y, 2);
  EXPECT_EQ(r_i32.min.z, 3);
  EXPECT_EQ(r_i32.min.w, 4);
  EXPECT_EQ(r_i32.max.x, 5);
  EXPECT_EQ(r_i32.max.y, 6);
  EXPECT_EQ(r_i32.max.z, 7);
  EXPECT_EQ(r_i32.max.w, 8);
}

TEST_F(RangeConversionsTest, Range4_I32ToI64) {
  lm2_r4_i32 r_i32 = lm2_r4_from_min_max_i32(
      lm2_v4_make_i32(1, 2, 3, 4), lm2_v4_make_i32(5, 6, 7, 8));
  lm2_r4_i64 r_i64 = lm2_r4_i32_to_i64(r_i32);

  EXPECT_EQ(r_i64.min.x, 1);
  EXPECT_EQ(r_i64.min.y, 2);
  EXPECT_EQ(r_i64.min.z, 3);
  EXPECT_EQ(r_i64.min.w, 4);
  EXPECT_EQ(r_i64.max.x, 5);
  EXPECT_EQ(r_i64.max.y, 6);
  EXPECT_EQ(r_i64.max.z, 7);
  EXPECT_EQ(r_i64.max.w, 8);
}

// =============================================================================
// Edge Cases and Precision Tests
// =============================================================================

TEST_F(RangeConversionsTest, Range2_SmallValues) {
  lm2_r2_f64 r_f64 = lm2_r2_from_min_max_f64(
      lm2_v2_make_f64(0.0001, 0.0002), lm2_v2_make_f64(0.0003, 0.0004));
  lm2_r2_f32 r_f32 = lm2_r2_f64_to_f32(r_f64);

  EXPECT_NEAR(r_f32.min.x, 0.0001f, EPSILON_F32);
  EXPECT_NEAR(r_f32.min.y, 0.0002f, EPSILON_F32);
  EXPECT_NEAR(r_f32.max.x, 0.0003f, EPSILON_F32);
  EXPECT_NEAR(r_f32.max.y, 0.0004f, EPSILON_F32);
}

TEST_F(RangeConversionsTest, Range3_LargeValues) {
  lm2_r3_i32 r_i32 = lm2_r3_from_min_max_i32(
      lm2_v3_make_i32(100000, 200000, 300000),
      lm2_v3_make_i32(500000, 600000, 700000));
  lm2_r3_f64 r_f64 = lm2_r3_i32_to_f64(r_i32);

  EXPECT_DOUBLE_EQ(r_f64.min.x, 100000.0);
  EXPECT_DOUBLE_EQ(r_f64.min.y, 200000.0);
  EXPECT_DOUBLE_EQ(r_f64.min.z, 300000.0);
  EXPECT_DOUBLE_EQ(r_f64.max.x, 500000.0);
  EXPECT_DOUBLE_EQ(r_f64.max.y, 600000.0);
  EXPECT_DOUBLE_EQ(r_f64.max.z, 700000.0);
}

TEST_F(RangeConversionsTest, Range4_NegativeValues) {
  lm2_r4_i32 r_i32 = lm2_r4_from_min_max_i32(
      lm2_v4_make_i32(-10, -20, -30, -40),
      lm2_v4_make_i32(-5, -15, -25, -35));
  lm2_r4_f32 r_f32 = lm2_r4_i32_to_f32(r_i32);

  EXPECT_FLOAT_EQ(r_f32.min.x, -10.0f);
  EXPECT_FLOAT_EQ(r_f32.min.y, -20.0f);
  EXPECT_FLOAT_EQ(r_f32.min.z, -30.0f);
  EXPECT_FLOAT_EQ(r_f32.min.w, -40.0f);
  EXPECT_FLOAT_EQ(r_f32.max.x, -5.0f);
  EXPECT_FLOAT_EQ(r_f32.max.y, -15.0f);
  EXPECT_FLOAT_EQ(r_f32.max.z, -25.0f);
  EXPECT_FLOAT_EQ(r_f32.max.w, -35.0f);
}
