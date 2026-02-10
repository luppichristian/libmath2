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
#include "lm2/vectors/lm2_vector_conversions.h"

// Test fixture for vector conversion tests
class VectorConversionsTest : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-6f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Vector2 Conversion Tests
// =============================================================================

// Float to Float conversions (v2)
TEST_F(VectorConversionsTest, V2_F64_to_F32) {
  lm2_v2_f64 v = lm2_v2_make_f64(3.5, 4.5);
  lm2_v2_f32 result = lm2_v2_f64_to_f32(v);
  EXPECT_FLOAT_EQ(result.x, 3.5f);
  EXPECT_FLOAT_EQ(result.y, 4.5f);
}

TEST_F(VectorConversionsTest, V2_F32_to_F64) {
  lm2_v2_f32 v = lm2_v2_make_f32(3.5f, 4.5f);
  lm2_v2_f64 result = lm2_v2_f32_to_f64(v);
  EXPECT_DOUBLE_EQ(result.x, 3.5);
  EXPECT_DOUBLE_EQ(result.y, 4.5);
}

// Float to Integer conversions (v2)
TEST_F(VectorConversionsTest, V2_F64_to_I32) {
  lm2_v2_f64 v = lm2_v2_make_f64(3.7, 4.2);
  lm2_v2_i32 result = lm2_v2_f64_to_i32(v);
  EXPECT_EQ(result.x, 3);
  EXPECT_EQ(result.y, 4);
}

TEST_F(VectorConversionsTest, V2_F32_to_I32) {
  lm2_v2_f32 v = lm2_v2_make_f32(3.7f, 4.2f);
  lm2_v2_i32 result = lm2_v2_f32_to_i32(v);
  EXPECT_EQ(result.x, 3);
  EXPECT_EQ(result.y, 4);
}

TEST_F(VectorConversionsTest, V2_F64_to_I64) {
  lm2_v2_f64 v = lm2_v2_make_f64(100.7, 200.2);
  lm2_v2_i64 result = lm2_v2_f64_to_i64(v);
  EXPECT_EQ(result.x, 100);
  EXPECT_EQ(result.y, 200);
}

TEST_F(VectorConversionsTest, V2_F32_to_I64) {
  lm2_v2_f32 v = lm2_v2_make_f32(100.7f, 200.2f);
  lm2_v2_i64 result = lm2_v2_f32_to_i64(v);
  EXPECT_EQ(result.x, 100);
  EXPECT_EQ(result.y, 200);
}

// Integer to Float conversions (v2)
TEST_F(VectorConversionsTest, V2_I32_to_F64) {
  lm2_v2_i32 v = lm2_v2_make_i32(3, 4);
  lm2_v2_f64 result = lm2_v2_i32_to_f64(v);
  EXPECT_DOUBLE_EQ(result.x, 3.0);
  EXPECT_DOUBLE_EQ(result.y, 4.0);
}

TEST_F(VectorConversionsTest, V2_I32_to_F32) {
  lm2_v2_i32 v = lm2_v2_make_i32(3, 4);
  lm2_v2_f32 result = lm2_v2_i32_to_f32(v);
  EXPECT_FLOAT_EQ(result.x, 3.0f);
  EXPECT_FLOAT_EQ(result.y, 4.0f);
}

TEST_F(VectorConversionsTest, V2_I64_to_F64) {
  lm2_v2_i64 v = lm2_v2_make_i64(100, 200);
  lm2_v2_f64 result = lm2_v2_i64_to_f64(v);
  EXPECT_DOUBLE_EQ(result.x, 100.0);
  EXPECT_DOUBLE_EQ(result.y, 200.0);
}

TEST_F(VectorConversionsTest, V2_I64_to_F32) {
  lm2_v2_i64 v = lm2_v2_make_i64(100, 200);
  lm2_v2_f32 result = lm2_v2_i64_to_f32(v);
  EXPECT_FLOAT_EQ(result.x, 100.0f);
  EXPECT_FLOAT_EQ(result.y, 200.0f);
}

// Integer to Integer conversions (v2)
TEST_F(VectorConversionsTest, V2_I32_to_I64) {
  lm2_v2_i32 v = lm2_v2_make_i32(3, 4);
  lm2_v2_i64 result = lm2_v2_i32_to_i64(v);
  EXPECT_EQ(result.x, 3);
  EXPECT_EQ(result.y, 4);
}

TEST_F(VectorConversionsTest, V2_I64_to_I32) {
  lm2_v2_i64 v = lm2_v2_make_i64(100, 200);
  lm2_v2_i32 result = lm2_v2_i64_to_i32(v);
  EXPECT_EQ(result.x, 100);
  EXPECT_EQ(result.y, 200);
}

TEST_F(VectorConversionsTest, V2_I32_to_I16) {
  lm2_v2_i32 v = lm2_v2_make_i32(100, 200);
  lm2_v2_i16 result = lm2_v2_i32_to_i16(v);
  EXPECT_EQ(result.x, 100);
  EXPECT_EQ(result.y, 200);
}

TEST_F(VectorConversionsTest, V2_I16_to_I32) {
  lm2_v2_i16 v = lm2_v2_make_i16(100, 200);
  lm2_v2_i32 result = lm2_v2_i16_to_i32(v);
  EXPECT_EQ(result.x, 100);
  EXPECT_EQ(result.y, 200);
}

// Float to Unsigned Integer conversions (v2)
TEST_F(VectorConversionsTest, V2_F64_to_U32) {
  lm2_v2_f64 v = lm2_v2_make_f64(3.7, 4.2);
  lm2_v2_u32 result = lm2_v2_f64_to_u32(v);
  EXPECT_EQ(result.x, 3u);
  EXPECT_EQ(result.y, 4u);
}

TEST_F(VectorConversionsTest, V2_F32_to_U32) {
  lm2_v2_f32 v = lm2_v2_make_f32(3.7f, 4.2f);
  lm2_v2_u32 result = lm2_v2_f32_to_u32(v);
  EXPECT_EQ(result.x, 3u);
  EXPECT_EQ(result.y, 4u);
}

// Unsigned Integer to Float conversions (v2)
TEST_F(VectorConversionsTest, V2_U32_to_F64) {
  lm2_v2_u32 v = lm2_v2_make_u32(3, 4);
  lm2_v2_f64 result = lm2_v2_u32_to_f64(v);
  EXPECT_DOUBLE_EQ(result.x, 3.0);
  EXPECT_DOUBLE_EQ(result.y, 4.0);
}

TEST_F(VectorConversionsTest, V2_U32_to_F32) {
  lm2_v2_u32 v = lm2_v2_make_u32(3, 4);
  lm2_v2_f32 result = lm2_v2_u32_to_f32(v);
  EXPECT_FLOAT_EQ(result.x, 3.0f);
  EXPECT_FLOAT_EQ(result.y, 4.0f);
}

// Signed to Unsigned Integer conversions (v2)
TEST_F(VectorConversionsTest, V2_I32_to_U32) {
  lm2_v2_i32 v = lm2_v2_make_i32(3, 4);
  lm2_v2_u32 result = lm2_v2_i32_to_u32(v);
  EXPECT_EQ(result.x, 3u);
  EXPECT_EQ(result.y, 4u);
}

TEST_F(VectorConversionsTest, V2_U32_to_I32) {
  lm2_v2_u32 v = lm2_v2_make_u32(3, 4);
  lm2_v2_i32 result = lm2_v2_u32_to_i32(v);
  EXPECT_EQ(result.x, 3);
  EXPECT_EQ(result.y, 4);
}

// =============================================================================
// Vector3 Conversion Tests
// =============================================================================

// Float to Float conversions (v3)
TEST_F(VectorConversionsTest, V3_F64_to_F32) {
  lm2_v3_f64 v = lm2_v3_make_f64(3.5, 4.5, 5.5);
  lm2_v3_f32 result = lm2_v3_f64_to_f32(v);
  EXPECT_FLOAT_EQ(result.x, 3.5f);
  EXPECT_FLOAT_EQ(result.y, 4.5f);
  EXPECT_FLOAT_EQ(result.z, 5.5f);
}

TEST_F(VectorConversionsTest, V3_F32_to_F64) {
  lm2_v3_f32 v = lm2_v3_make_f32(3.5f, 4.5f, 5.5f);
  lm2_v3_f64 result = lm2_v3_f32_to_f64(v);
  EXPECT_DOUBLE_EQ(result.x, 3.5);
  EXPECT_DOUBLE_EQ(result.y, 4.5);
  EXPECT_DOUBLE_EQ(result.z, 5.5);
}

// Float to Integer conversions (v3)
TEST_F(VectorConversionsTest, V3_F64_to_I32) {
  lm2_v3_f64 v = lm2_v3_make_f64(3.7, 4.2, 5.9);
  lm2_v3_i32 result = lm2_v3_f64_to_i32(v);
  EXPECT_EQ(result.x, 3);
  EXPECT_EQ(result.y, 4);
  EXPECT_EQ(result.z, 5);
}

TEST_F(VectorConversionsTest, V3_F32_to_I32) {
  lm2_v3_f32 v = lm2_v3_make_f32(3.7f, 4.2f, 5.9f);
  lm2_v3_i32 result = lm2_v3_f32_to_i32(v);
  EXPECT_EQ(result.x, 3);
  EXPECT_EQ(result.y, 4);
  EXPECT_EQ(result.z, 5);
}

TEST_F(VectorConversionsTest, V3_F64_to_I64) {
  lm2_v3_f64 v = lm2_v3_make_f64(100.7, 200.2, 300.9);
  lm2_v3_i64 result = lm2_v3_f64_to_i64(v);
  EXPECT_EQ(result.x, 100);
  EXPECT_EQ(result.y, 200);
  EXPECT_EQ(result.z, 300);
}

TEST_F(VectorConversionsTest, V3_F32_to_I64) {
  lm2_v3_f32 v = lm2_v3_make_f32(100.7f, 200.2f, 300.9f);
  lm2_v3_i64 result = lm2_v3_f32_to_i64(v);
  EXPECT_EQ(result.x, 100);
  EXPECT_EQ(result.y, 200);
  EXPECT_EQ(result.z, 300);
}

// Integer to Float conversions (v3)
TEST_F(VectorConversionsTest, V3_I32_to_F64) {
  lm2_v3_i32 v = lm2_v3_make_i32(3, 4, 5);
  lm2_v3_f64 result = lm2_v3_i32_to_f64(v);
  EXPECT_DOUBLE_EQ(result.x, 3.0);
  EXPECT_DOUBLE_EQ(result.y, 4.0);
  EXPECT_DOUBLE_EQ(result.z, 5.0);
}

TEST_F(VectorConversionsTest, V3_I32_to_F32) {
  lm2_v3_i32 v = lm2_v3_make_i32(3, 4, 5);
  lm2_v3_f32 result = lm2_v3_i32_to_f32(v);
  EXPECT_FLOAT_EQ(result.x, 3.0f);
  EXPECT_FLOAT_EQ(result.y, 4.0f);
  EXPECT_FLOAT_EQ(result.z, 5.0f);
}

TEST_F(VectorConversionsTest, V3_I64_to_F64) {
  lm2_v3_i64 v = lm2_v3_make_i64(100, 200, 300);
  lm2_v3_f64 result = lm2_v3_i64_to_f64(v);
  EXPECT_DOUBLE_EQ(result.x, 100.0);
  EXPECT_DOUBLE_EQ(result.y, 200.0);
  EXPECT_DOUBLE_EQ(result.z, 300.0);
}

TEST_F(VectorConversionsTest, V3_I64_to_F32) {
  lm2_v3_i64 v = lm2_v3_make_i64(100, 200, 300);
  lm2_v3_f32 result = lm2_v3_i64_to_f32(v);
  EXPECT_FLOAT_EQ(result.x, 100.0f);
  EXPECT_FLOAT_EQ(result.y, 200.0f);
  EXPECT_FLOAT_EQ(result.z, 300.0f);
}

// Integer to Integer conversions (v3)
TEST_F(VectorConversionsTest, V3_I32_to_I64) {
  lm2_v3_i32 v = lm2_v3_make_i32(3, 4, 5);
  lm2_v3_i64 result = lm2_v3_i32_to_i64(v);
  EXPECT_EQ(result.x, 3);
  EXPECT_EQ(result.y, 4);
  EXPECT_EQ(result.z, 5);
}

TEST_F(VectorConversionsTest, V3_I64_to_I32) {
  lm2_v3_i64 v = lm2_v3_make_i64(100, 200, 300);
  lm2_v3_i32 result = lm2_v3_i64_to_i32(v);
  EXPECT_EQ(result.x, 100);
  EXPECT_EQ(result.y, 200);
  EXPECT_EQ(result.z, 300);
}

TEST_F(VectorConversionsTest, V3_I32_to_I16) {
  lm2_v3_i32 v = lm2_v3_make_i32(100, 200, 300);
  lm2_v3_i16 result = lm2_v3_i32_to_i16(v);
  EXPECT_EQ(result.x, 100);
  EXPECT_EQ(result.y, 200);
  EXPECT_EQ(result.z, 300);
}

TEST_F(VectorConversionsTest, V3_I16_to_I32) {
  lm2_v3_i16 v = lm2_v3_make_i16(100, 200, 300);
  lm2_v3_i32 result = lm2_v3_i16_to_i32(v);
  EXPECT_EQ(result.x, 100);
  EXPECT_EQ(result.y, 200);
  EXPECT_EQ(result.z, 300);
}

// Float to Unsigned Integer conversions (v3)
TEST_F(VectorConversionsTest, V3_F64_to_U32) {
  lm2_v3_f64 v = lm2_v3_make_f64(3.7, 4.2, 5.9);
  lm2_v3_u32 result = lm2_v3_f64_to_u32(v);
  EXPECT_EQ(result.x, 3u);
  EXPECT_EQ(result.y, 4u);
  EXPECT_EQ(result.z, 5u);
}

TEST_F(VectorConversionsTest, V3_F32_to_U32) {
  lm2_v3_f32 v = lm2_v3_make_f32(3.7f, 4.2f, 5.9f);
  lm2_v3_u32 result = lm2_v3_f32_to_u32(v);
  EXPECT_EQ(result.x, 3u);
  EXPECT_EQ(result.y, 4u);
  EXPECT_EQ(result.z, 5u);
}

// Unsigned Integer to Float conversions (v3)
TEST_F(VectorConversionsTest, V3_U32_to_F64) {
  lm2_v3_u32 v = lm2_v3_make_u32(3, 4, 5);
  lm2_v3_f64 result = lm2_v3_u32_to_f64(v);
  EXPECT_DOUBLE_EQ(result.x, 3.0);
  EXPECT_DOUBLE_EQ(result.y, 4.0);
  EXPECT_DOUBLE_EQ(result.z, 5.0);
}

TEST_F(VectorConversionsTest, V3_U32_to_F32) {
  lm2_v3_u32 v = lm2_v3_make_u32(3, 4, 5);
  lm2_v3_f32 result = lm2_v3_u32_to_f32(v);
  EXPECT_FLOAT_EQ(result.x, 3.0f);
  EXPECT_FLOAT_EQ(result.y, 4.0f);
  EXPECT_FLOAT_EQ(result.z, 5.0f);
}

// Signed to Unsigned Integer conversions (v3)
TEST_F(VectorConversionsTest, V3_I32_to_U32) {
  lm2_v3_i32 v = lm2_v3_make_i32(3, 4, 5);
  lm2_v3_u32 result = lm2_v3_i32_to_u32(v);
  EXPECT_EQ(result.x, 3u);
  EXPECT_EQ(result.y, 4u);
  EXPECT_EQ(result.z, 5u);
}

TEST_F(VectorConversionsTest, V3_U32_to_I32) {
  lm2_v3_u32 v = lm2_v3_make_u32(3, 4, 5);
  lm2_v3_i32 result = lm2_v3_u32_to_i32(v);
  EXPECT_EQ(result.x, 3);
  EXPECT_EQ(result.y, 4);
  EXPECT_EQ(result.z, 5);
}

// =============================================================================
// Vector4 Conversion Tests
// =============================================================================

// Float to Float conversions (v4)
TEST_F(VectorConversionsTest, V4_F64_to_F32) {
  lm2_v4_f64 v = lm2_v4_make_f64(3.5, 4.5, 5.5, 6.5);
  lm2_v4_f32 result = lm2_v4_f64_to_f32(v);
  EXPECT_FLOAT_EQ(result.x, 3.5f);
  EXPECT_FLOAT_EQ(result.y, 4.5f);
  EXPECT_FLOAT_EQ(result.z, 5.5f);
  EXPECT_FLOAT_EQ(result.w, 6.5f);
}

TEST_F(VectorConversionsTest, V4_F32_to_F64) {
  lm2_v4_f32 v = lm2_v4_make_f32(3.5f, 4.5f, 5.5f, 6.5f);
  lm2_v4_f64 result = lm2_v4_f32_to_f64(v);
  EXPECT_DOUBLE_EQ(result.x, 3.5);
  EXPECT_DOUBLE_EQ(result.y, 4.5);
  EXPECT_DOUBLE_EQ(result.z, 5.5);
  EXPECT_DOUBLE_EQ(result.w, 6.5);
}

// Float to Integer conversions (v4)
TEST_F(VectorConversionsTest, V4_F64_to_I32) {
  lm2_v4_f64 v = lm2_v4_make_f64(3.7, 4.2, 5.9, 6.1);
  lm2_v4_i32 result = lm2_v4_f64_to_i32(v);
  EXPECT_EQ(result.x, 3);
  EXPECT_EQ(result.y, 4);
  EXPECT_EQ(result.z, 5);
  EXPECT_EQ(result.w, 6);
}

TEST_F(VectorConversionsTest, V4_F32_to_I32) {
  lm2_v4_f32 v = lm2_v4_make_f32(3.7f, 4.2f, 5.9f, 6.1f);
  lm2_v4_i32 result = lm2_v4_f32_to_i32(v);
  EXPECT_EQ(result.x, 3);
  EXPECT_EQ(result.y, 4);
  EXPECT_EQ(result.z, 5);
  EXPECT_EQ(result.w, 6);
}

TEST_F(VectorConversionsTest, V4_F64_to_I64) {
  lm2_v4_f64 v = lm2_v4_make_f64(100.7, 200.2, 300.9, 400.1);
  lm2_v4_i64 result = lm2_v4_f64_to_i64(v);
  EXPECT_EQ(result.x, 100);
  EXPECT_EQ(result.y, 200);
  EXPECT_EQ(result.z, 300);
  EXPECT_EQ(result.w, 400);
}

TEST_F(VectorConversionsTest, V4_F32_to_I64) {
  lm2_v4_f32 v = lm2_v4_make_f32(100.7f, 200.2f, 300.9f, 400.1f);
  lm2_v4_i64 result = lm2_v4_f32_to_i64(v);
  EXPECT_EQ(result.x, 100);
  EXPECT_EQ(result.y, 200);
  EXPECT_EQ(result.z, 300);
  EXPECT_EQ(result.w, 400);
}

// Integer to Float conversions (v4)
TEST_F(VectorConversionsTest, V4_I32_to_F64) {
  lm2_v4_i32 v = lm2_v4_make_i32(3, 4, 5, 6);
  lm2_v4_f64 result = lm2_v4_i32_to_f64(v);
  EXPECT_DOUBLE_EQ(result.x, 3.0);
  EXPECT_DOUBLE_EQ(result.y, 4.0);
  EXPECT_DOUBLE_EQ(result.z, 5.0);
  EXPECT_DOUBLE_EQ(result.w, 6.0);
}

TEST_F(VectorConversionsTest, V4_I32_to_F32) {
  lm2_v4_i32 v = lm2_v4_make_i32(3, 4, 5, 6);
  lm2_v4_f32 result = lm2_v4_i32_to_f32(v);
  EXPECT_FLOAT_EQ(result.x, 3.0f);
  EXPECT_FLOAT_EQ(result.y, 4.0f);
  EXPECT_FLOAT_EQ(result.z, 5.0f);
  EXPECT_FLOAT_EQ(result.w, 6.0f);
}

TEST_F(VectorConversionsTest, V4_I64_to_F64) {
  lm2_v4_i64 v = lm2_v4_make_i64(100, 200, 300, 400);
  lm2_v4_f64 result = lm2_v4_i64_to_f64(v);
  EXPECT_DOUBLE_EQ(result.x, 100.0);
  EXPECT_DOUBLE_EQ(result.y, 200.0);
  EXPECT_DOUBLE_EQ(result.z, 300.0);
  EXPECT_DOUBLE_EQ(result.w, 400.0);
}

TEST_F(VectorConversionsTest, V4_I64_to_F32) {
  lm2_v4_i64 v = lm2_v4_make_i64(100, 200, 300, 400);
  lm2_v4_f32 result = lm2_v4_i64_to_f32(v);
  EXPECT_FLOAT_EQ(result.x, 100.0f);
  EXPECT_FLOAT_EQ(result.y, 200.0f);
  EXPECT_FLOAT_EQ(result.z, 300.0f);
  EXPECT_FLOAT_EQ(result.w, 400.0f);
}

// Integer to Integer conversions (v4)
TEST_F(VectorConversionsTest, V4_I32_to_I64) {
  lm2_v4_i32 v = lm2_v4_make_i32(3, 4, 5, 6);
  lm2_v4_i64 result = lm2_v4_i32_to_i64(v);
  EXPECT_EQ(result.x, 3);
  EXPECT_EQ(result.y, 4);
  EXPECT_EQ(result.z, 5);
  EXPECT_EQ(result.w, 6);
}

TEST_F(VectorConversionsTest, V4_I64_to_I32) {
  lm2_v4_i64 v = lm2_v4_make_i64(100, 200, 300, 400);
  lm2_v4_i32 result = lm2_v4_i64_to_i32(v);
  EXPECT_EQ(result.x, 100);
  EXPECT_EQ(result.y, 200);
  EXPECT_EQ(result.z, 300);
  EXPECT_EQ(result.w, 400);
}

TEST_F(VectorConversionsTest, V4_I32_to_I16) {
  lm2_v4_i32 v = lm2_v4_make_i32(100, 200, 300, 400);
  lm2_v4_i16 result = lm2_v4_i32_to_i16(v);
  EXPECT_EQ(result.x, 100);
  EXPECT_EQ(result.y, 200);
  EXPECT_EQ(result.z, 300);
  EXPECT_EQ(result.w, 400);
}

TEST_F(VectorConversionsTest, V4_I16_to_I32) {
  lm2_v4_i16 v = lm2_v4_make_i16(100, 200, 300, 400);
  lm2_v4_i32 result = lm2_v4_i16_to_i32(v);
  EXPECT_EQ(result.x, 100);
  EXPECT_EQ(result.y, 200);
  EXPECT_EQ(result.z, 300);
  EXPECT_EQ(result.w, 400);
}

// Float to Unsigned Integer conversions (v4)
TEST_F(VectorConversionsTest, V4_F64_to_U32) {
  lm2_v4_f64 v = lm2_v4_make_f64(3.7, 4.2, 5.9, 6.1);
  lm2_v4_u32 result = lm2_v4_f64_to_u32(v);
  EXPECT_EQ(result.x, 3u);
  EXPECT_EQ(result.y, 4u);
  EXPECT_EQ(result.z, 5u);
  EXPECT_EQ(result.w, 6u);
}

TEST_F(VectorConversionsTest, V4_F32_to_U32) {
  lm2_v4_f32 v = lm2_v4_make_f32(3.7f, 4.2f, 5.9f, 6.1f);
  lm2_v4_u32 result = lm2_v4_f32_to_u32(v);
  EXPECT_EQ(result.x, 3u);
  EXPECT_EQ(result.y, 4u);
  EXPECT_EQ(result.z, 5u);
  EXPECT_EQ(result.w, 6u);
}

// Unsigned Integer to Float conversions (v4)
TEST_F(VectorConversionsTest, V4_U32_to_F64) {
  lm2_v4_u32 v = lm2_v4_make_u32(3, 4, 5, 6);
  lm2_v4_f64 result = lm2_v4_u32_to_f64(v);
  EXPECT_DOUBLE_EQ(result.x, 3.0);
  EXPECT_DOUBLE_EQ(result.y, 4.0);
  EXPECT_DOUBLE_EQ(result.z, 5.0);
  EXPECT_DOUBLE_EQ(result.w, 6.0);
}

TEST_F(VectorConversionsTest, V4_U32_to_F32) {
  lm2_v4_u32 v = lm2_v4_make_u32(3, 4, 5, 6);
  lm2_v4_f32 result = lm2_v4_u32_to_f32(v);
  EXPECT_FLOAT_EQ(result.x, 3.0f);
  EXPECT_FLOAT_EQ(result.y, 4.0f);
  EXPECT_FLOAT_EQ(result.z, 5.0f);
  EXPECT_FLOAT_EQ(result.w, 6.0f);
}

// Signed to Unsigned Integer conversions (v4)
TEST_F(VectorConversionsTest, V4_I32_to_U32) {
  lm2_v4_i32 v = lm2_v4_make_i32(3, 4, 5, 6);
  lm2_v4_u32 result = lm2_v4_i32_to_u32(v);
  EXPECT_EQ(result.x, 3u);
  EXPECT_EQ(result.y, 4u);
  EXPECT_EQ(result.z, 5u);
  EXPECT_EQ(result.w, 6u);
}

TEST_F(VectorConversionsTest, V4_U32_to_I32) {
  lm2_v4_u32 v = lm2_v4_make_u32(3, 4, 5, 6);
  lm2_v4_i32 result = lm2_v4_u32_to_i32(v);
  EXPECT_EQ(result.x, 3);
  EXPECT_EQ(result.y, 4);
  EXPECT_EQ(result.z, 5);
  EXPECT_EQ(result.w, 6);
}
