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
#include <cstdint>
#include <limits>

#include "lm2/vectors/lm2_vector2.h"
#include "lm2/vectors/lm2_vector3.h"
#include "lm2/vectors/lm2_vector4.h"

TEST(VectorNegCheckedTest, RejectsUnrepresentableIntegerNegation) {
  const int8_t minimum = std::numeric_limits<int8_t>::min();
  EXPECT_DEATH((void)lm2_v2_neg_i8(lm2_v2_make_i8(minimum, 1)), "");
  EXPECT_DEATH((void)lm2_v3_neg_i8(lm2_v3_make_i8(1, minimum, 1)), "");
  EXPECT_DEATH((void)lm2_v4_neg_i8(lm2_v4_make_i8(1, 1, 1, minimum)), "");
}

TEST(VectorNegCheckedTest, RejectsNonfiniteFloatingInput) {
  const double infinity = std::numeric_limits<double>::infinity();
  EXPECT_DEATH((void)lm2_v2_neg_f64(lm2_v2_make_f64(infinity, 1.0)), "");
  EXPECT_DEATH((void)lm2_v3_neg_f64(lm2_v3_make_f64(1.0, infinity, 1.0)), "");
  EXPECT_DEATH((void)lm2_v4_neg_f64(lm2_v4_make_f64(1.0, 1.0, 1.0, infinity)), "");
}

TEST(VectorNegCheckedTest, UnsignedNegationWrapsPerComponent) {
  const lm2_v3_u64 a = lm2_v3_neg_u64(lm2_v3_make_u64(0, 1, UINT64_MAX));
  EXPECT_EQ(a.x, UINT64_C(0));
  EXPECT_EQ(a.y, UINT64_MAX);
  EXPECT_EQ(a.z, UINT64_C(1));
  const lm2_v4_u32 b = lm2_v4_neg_u32(lm2_v4_make_u32(0, 1, UINT32_MAX, 2));
  EXPECT_EQ(b.x, UINT32_C(0));
  EXPECT_EQ(b.y, UINT32_MAX);
  EXPECT_EQ(b.z, UINT32_C(1));
  EXPECT_EQ(b.w, UINT32_MAX - UINT32_C(1));
  const lm2_v4_u8 c = lm2_v4_neg_u8(lm2_v4_make_u8(0, 1, UINT8_MAX, 2));
  EXPECT_EQ(c.x, 0);
  EXPECT_EQ(c.y, UINT8_MAX);
  EXPECT_EQ(c.z, 1);
  EXPECT_EQ(c.w, UINT8_MAX - 1);
}
