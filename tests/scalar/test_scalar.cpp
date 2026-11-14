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
#include <cmath>
#include <limits>
#include "lm2/scalar/lm2_scalar.h"

// Test fixture for scalar tests
class ScalarTest : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-6f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Floor Tests
// =============================================================================

TEST_F(ScalarTest, Floor_F64) {
  EXPECT_DOUBLE_EQ(lm2_floor_f64(3.7), 3.0);
  EXPECT_DOUBLE_EQ(lm2_floor_f64(-3.7), -4.0);
  EXPECT_DOUBLE_EQ(lm2_floor_f64(0.0), 0.0);
  EXPECT_DOUBLE_EQ(lm2_floor_f64(-0.0), -0.0);
  EXPECT_DOUBLE_EQ(lm2_floor_f64(5.0), 5.0);
}

TEST_F(ScalarTest, Floor_F32) {
  EXPECT_FLOAT_EQ(lm2_floor_f32(3.7f), 3.0f);
  EXPECT_FLOAT_EQ(lm2_floor_f32(-3.7f), -4.0f);
  EXPECT_FLOAT_EQ(lm2_floor_f32(0.0f), 0.0f);
  EXPECT_FLOAT_EQ(lm2_floor_f32(5.0f), 5.0f);
}

TEST_F(ScalarTest, FloorMultiple_F64) {
  EXPECT_DOUBLE_EQ(lm2_floor_multiple_f64(17.5, 5.0), 15.0);
  EXPECT_DOUBLE_EQ(lm2_floor_multiple_f64(22.0, 5.0), 20.0);
  EXPECT_DOUBLE_EQ(lm2_floor_multiple_f64(-7.5, 5.0), -10.0);
}

TEST_F(ScalarTest, FloorMultiple_F32) {
  EXPECT_FLOAT_EQ(lm2_floor_multiple_f32(17.5f, 5.0f), 15.0f);
  EXPECT_FLOAT_EQ(lm2_floor_multiple_f32(22.0f, 5.0f), 20.0f);
  EXPECT_FLOAT_EQ(lm2_floor_multiple_f32(-7.5f, 5.0f), -10.0f);
}

// =============================================================================
// Ceil Tests
// =============================================================================

TEST_F(ScalarTest, Ceil_F64) {
  EXPECT_DOUBLE_EQ(lm2_ceil_f64(3.2), 4.0);
  EXPECT_DOUBLE_EQ(lm2_ceil_f64(-3.2), -3.0);
  EXPECT_DOUBLE_EQ(lm2_ceil_f64(0.0), 0.0);
  EXPECT_DOUBLE_EQ(lm2_ceil_f64(5.0), 5.0);
}

TEST_F(ScalarTest, Ceil_F32) {
  EXPECT_FLOAT_EQ(lm2_ceil_f32(3.2f), 4.0f);
  EXPECT_FLOAT_EQ(lm2_ceil_f32(-3.2f), -3.0f);
  EXPECT_FLOAT_EQ(lm2_ceil_f32(0.0f), 0.0f);
  EXPECT_FLOAT_EQ(lm2_ceil_f32(5.0f), 5.0f);
}

TEST_F(ScalarTest, CeilMultiple_F64) {
  EXPECT_DOUBLE_EQ(lm2_ceil_multiple_f64(17.5, 5.0), 20.0);
  EXPECT_DOUBLE_EQ(lm2_ceil_multiple_f64(22.0, 5.0), 25.0);
  EXPECT_DOUBLE_EQ(lm2_ceil_multiple_f64(-7.5, 5.0), -5.0);
}

TEST_F(ScalarTest, CeilMultiple_F32) {
  EXPECT_FLOAT_EQ(lm2_ceil_multiple_f32(17.5f, 5.0f), 20.0f);
  EXPECT_FLOAT_EQ(lm2_ceil_multiple_f32(22.0f, 5.0f), 25.0f);
  EXPECT_FLOAT_EQ(lm2_ceil_multiple_f32(-7.5f, 5.0f), -5.0f);
}

// =============================================================================
// Round Tests
// =============================================================================

TEST_F(ScalarTest, Round_F64) {
  EXPECT_DOUBLE_EQ(lm2_round_f64(3.4), 3.0);
  EXPECT_DOUBLE_EQ(lm2_round_f64(3.5), 4.0);
  EXPECT_DOUBLE_EQ(lm2_round_f64(-3.4), -3.0);
  EXPECT_DOUBLE_EQ(lm2_round_f64(-3.5), -4.0);
  EXPECT_DOUBLE_EQ(lm2_round_f64(0.0), 0.0);
}

TEST_F(ScalarTest, Round_F32) {
  EXPECT_FLOAT_EQ(lm2_round_f32(3.4f), 3.0f);
  EXPECT_FLOAT_EQ(lm2_round_f32(3.5f), 4.0f);
  EXPECT_FLOAT_EQ(lm2_round_f32(-3.4f), -3.0f);
  EXPECT_FLOAT_EQ(lm2_round_f32(-3.5f), -4.0f);
}

TEST_F(ScalarTest, RoundMultiple_F64) {
  EXPECT_DOUBLE_EQ(lm2_round_multiple_f64(17.4, 5.0), 15.0);
  EXPECT_DOUBLE_EQ(lm2_round_multiple_f64(17.5, 5.0), 20.0);
  EXPECT_DOUBLE_EQ(lm2_round_multiple_f64(22.6, 5.0), 25.0);
}

TEST_F(ScalarTest, RoundMultiple_F32) {
  EXPECT_FLOAT_EQ(lm2_round_multiple_f32(17.4f, 5.0f), 15.0f);
  EXPECT_FLOAT_EQ(lm2_round_multiple_f32(17.5f, 5.0f), 20.0f);
  EXPECT_FLOAT_EQ(lm2_round_multiple_f32(22.6f, 5.0f), 25.0f);
}

// =============================================================================
// Truncate Tests
// =============================================================================

TEST_F(ScalarTest, Trunc_F64) {
  EXPECT_DOUBLE_EQ(lm2_trunc_f64(3.7), 3.0);
  EXPECT_DOUBLE_EQ(lm2_trunc_f64(-3.7), -3.0);
  EXPECT_DOUBLE_EQ(lm2_trunc_f64(0.0), 0.0);
  EXPECT_DOUBLE_EQ(lm2_trunc_f64(5.0), 5.0);
}

TEST_F(ScalarTest, Trunc_F32) {
  EXPECT_FLOAT_EQ(lm2_trunc_f32(3.7f), 3.0f);
  EXPECT_FLOAT_EQ(lm2_trunc_f32(-3.7f), -3.0f);
  EXPECT_FLOAT_EQ(lm2_trunc_f32(0.0f), 0.0f);
}

TEST_F(ScalarTest, TruncMultiple_F64) {
  EXPECT_DOUBLE_EQ(lm2_trunc_multiple_f64(17.9, 5.0), 15.0);
  EXPECT_DOUBLE_EQ(lm2_trunc_multiple_f64(-17.9, 5.0), -15.0);
}

TEST_F(ScalarTest, TruncMultiple_F32) {
  EXPECT_FLOAT_EQ(lm2_trunc_multiple_f32(17.9f, 5.0f), 15.0f);
  EXPECT_FLOAT_EQ(lm2_trunc_multiple_f32(-17.9f, 5.0f), -15.0f);
}

// =============================================================================
// Abs Tests
// =============================================================================

TEST_F(ScalarTest, Abs_F64) {
  EXPECT_DOUBLE_EQ(lm2_abs_f64(5.0), 5.0);
  EXPECT_DOUBLE_EQ(lm2_abs_f64(-5.0), 5.0);
  EXPECT_DOUBLE_EQ(lm2_abs_f64(0.0), 0.0);
  EXPECT_DOUBLE_EQ(lm2_abs_f64(-0.0), 0.0);
}

TEST_F(ScalarTest, Abs_F32) {
  EXPECT_FLOAT_EQ(lm2_abs_f32(5.0f), 5.0f);
  EXPECT_FLOAT_EQ(lm2_abs_f32(-5.0f), 5.0f);
  EXPECT_FLOAT_EQ(lm2_abs_f32(0.0f), 0.0f);
}

// =============================================================================
// Sign Tests
// =============================================================================

TEST_F(ScalarTest, Sign_F64) {
  EXPECT_DOUBLE_EQ(lm2_sign_f64(5.0), 1.0);
  EXPECT_DOUBLE_EQ(lm2_sign_f64(-5.0), -1.0);
  EXPECT_DOUBLE_EQ(lm2_sign_f64(0.0), 1.0);  // Returns 1 for zero
}

TEST_F(ScalarTest, Sign_F32) {
  EXPECT_FLOAT_EQ(lm2_sign_f32(5.0f), 1.0f);
  EXPECT_FLOAT_EQ(lm2_sign_f32(-5.0f), -1.0f);
  EXPECT_FLOAT_EQ(lm2_sign_f32(0.0f), 1.0f);
}

TEST_F(ScalarTest, Sign0_F64) {
  EXPECT_DOUBLE_EQ(lm2_sign0_f64(5.0), 1.0);
  EXPECT_DOUBLE_EQ(lm2_sign0_f64(-5.0), -1.0);
  EXPECT_DOUBLE_EQ(lm2_sign0_f64(0.0), 0.0);  // Returns 0 for zero
}

TEST_F(ScalarTest, Sign0_F32) {
  EXPECT_FLOAT_EQ(lm2_sign0_f32(5.0f), 1.0f);
  EXPECT_FLOAT_EQ(lm2_sign0_f32(-5.0f), -1.0f);
  EXPECT_FLOAT_EQ(lm2_sign0_f32(0.0f), 0.0f);
}

// =============================================================================
// Min/Max Tests
// =============================================================================

TEST_F(ScalarTest, Min_F64) {
  EXPECT_DOUBLE_EQ(lm2_min_f64(3.0, 5.0), 3.0);
  EXPECT_DOUBLE_EQ(lm2_min_f64(5.0, 3.0), 3.0);
  EXPECT_DOUBLE_EQ(lm2_min_f64(-5.0, -3.0), -5.0);
}

TEST_F(ScalarTest, Min_F32) {
  EXPECT_FLOAT_EQ(lm2_min_f32(3.0f, 5.0f), 3.0f);
  EXPECT_FLOAT_EQ(lm2_min_f32(5.0f, 3.0f), 3.0f);
}

TEST_F(ScalarTest, MinAbs_F64) {
  EXPECT_DOUBLE_EQ(lm2_min_abs_f64(-3.0, 5.0), -3.0);
  EXPECT_DOUBLE_EQ(lm2_min_abs_f64(-5.0, 3.0), 3.0);
}

TEST_F(ScalarTest, MinAbs_F32) {
  EXPECT_FLOAT_EQ(lm2_min_abs_f32(-3.0f, 5.0f), -3.0f);
  EXPECT_FLOAT_EQ(lm2_min_abs_f32(-5.0f, 3.0f), 3.0f);
}

TEST_F(ScalarTest, Max_F64) {
  EXPECT_DOUBLE_EQ(lm2_max_f64(3.0, 5.0), 5.0);
  EXPECT_DOUBLE_EQ(lm2_max_f64(5.0, 3.0), 5.0);
  EXPECT_DOUBLE_EQ(lm2_max_f64(-5.0, -3.0), -3.0);
}

TEST_F(ScalarTest, Max_F32) {
  EXPECT_FLOAT_EQ(lm2_max_f32(3.0f, 5.0f), 5.0f);
  EXPECT_FLOAT_EQ(lm2_max_f32(5.0f, 3.0f), 5.0f);
}

TEST_F(ScalarTest, MaxAbs_F64) {
  EXPECT_DOUBLE_EQ(lm2_max_abs_f64(-3.0, 5.0), 5.0);
  EXPECT_DOUBLE_EQ(lm2_max_abs_f64(-5.0, 3.0), -5.0);
}

TEST_F(ScalarTest, MaxAbs_F32) {
  EXPECT_FLOAT_EQ(lm2_max_abs_f32(-3.0f, 5.0f), 5.0f);
  EXPECT_FLOAT_EQ(lm2_max_abs_f32(-5.0f, 3.0f), -5.0f);
}

// =============================================================================
// Clamp Tests
// =============================================================================

TEST_F(ScalarTest, Clamp_F64) {
  EXPECT_DOUBLE_EQ(lm2_clamp_f64(0.0, 5.0, 10.0), 5.0);
  EXPECT_DOUBLE_EQ(lm2_clamp_f64(0.0, -5.0, 10.0), 0.0);
  EXPECT_DOUBLE_EQ(lm2_clamp_f64(0.0, 15.0, 10.0), 10.0);
}

TEST_F(ScalarTest, Clamp_F32) {
  EXPECT_FLOAT_EQ(lm2_clamp_f32(0.0f, 5.0f, 10.0f), 5.0f);
  EXPECT_FLOAT_EQ(lm2_clamp_f32(0.0f, -5.0f, 10.0f), 0.0f);
  EXPECT_FLOAT_EQ(lm2_clamp_f32(0.0f, 15.0f, 10.0f), 10.0f);
}

// =============================================================================
// Saturate Tests
// =============================================================================

TEST_F(ScalarTest, Saturate_F64) {
  EXPECT_DOUBLE_EQ(lm2_saturate_f64(0.5), 0.5);
  EXPECT_DOUBLE_EQ(lm2_saturate_f64(-0.5), 0.0);
  EXPECT_DOUBLE_EQ(lm2_saturate_f64(1.5), 1.0);
  EXPECT_DOUBLE_EQ(lm2_saturate_f64(0.0), 0.0);
  EXPECT_DOUBLE_EQ(lm2_saturate_f64(1.0), 1.0);
}

TEST_F(ScalarTest, Saturate_F32) {
  EXPECT_FLOAT_EQ(lm2_saturate_f32(0.5f), 0.5f);
  EXPECT_FLOAT_EQ(lm2_saturate_f32(-0.5f), 0.0f);
  EXPECT_FLOAT_EQ(lm2_saturate_f32(1.5f), 1.0f);
}

// =============================================================================
// Lerp Tests
// =============================================================================

TEST_F(ScalarTest, Lerp_F64) {
  EXPECT_DOUBLE_EQ(lm2_lerp_f64(0.0, 0.0, 10.0), 0.0);
  EXPECT_DOUBLE_EQ(lm2_lerp_f64(0.0, 0.5, 10.0), 5.0);
  EXPECT_DOUBLE_EQ(lm2_lerp_f64(0.0, 1.0, 10.0), 10.0);
  EXPECT_DOUBLE_EQ(lm2_lerp_f64(5.0, 0.5, 15.0), 10.0);
}

TEST_F(ScalarTest, Lerp_F32) {
  EXPECT_FLOAT_EQ(lm2_lerp_f32(0.0f, 0.0f, 10.0f), 0.0f);
  EXPECT_FLOAT_EQ(lm2_lerp_f32(0.0f, 0.5f, 10.0f), 5.0f);
  EXPECT_FLOAT_EQ(lm2_lerp_f32(0.0f, 1.0f, 10.0f), 10.0f);
}

// =============================================================================
// Smoothstep Tests
// =============================================================================

TEST_F(ScalarTest, Smoothstep_F64) {
  EXPECT_DOUBLE_EQ(lm2_smoothstep_f64(0.0, 0.0, 1.0), 0.0);
  EXPECT_DOUBLE_EQ(lm2_smoothstep_f64(0.0, 1.0, 1.0), 1.0);
  EXPECT_NEAR(lm2_smoothstep_f64(0.0, 0.5, 1.0), 0.5, EPSILON_F64);
  EXPECT_DOUBLE_EQ(lm2_smoothstep_f64(0.0, -0.5, 1.0), 0.0);  // Below edge0
  EXPECT_DOUBLE_EQ(lm2_smoothstep_f64(0.0, 1.5, 1.0), 1.0);   // Above edge1
}

TEST_F(ScalarTest, Smoothstep_F32) {
  EXPECT_FLOAT_EQ(lm2_smoothstep_f32(0.0f, 0.0f, 1.0f), 0.0f);
  EXPECT_FLOAT_EQ(lm2_smoothstep_f32(0.0f, 1.0f, 1.0f), 1.0f);
  EXPECT_NEAR(lm2_smoothstep_f32(0.0f, 0.5f, 1.0f), 0.5f, EPSILON_F32);
}

// =============================================================================
// Alpha Tests
// =============================================================================

TEST_F(ScalarTest, Alpha_F64) {
  EXPECT_DOUBLE_EQ(lm2_alpha_f64(0.0, 0.0, 10.0), 0.0);
  EXPECT_DOUBLE_EQ(lm2_alpha_f64(0.0, 5.0, 10.0), 0.5);
  EXPECT_DOUBLE_EQ(lm2_alpha_f64(0.0, 10.0, 10.0), 1.0);
}

TEST_F(ScalarTest, Alpha_F32) {
  EXPECT_FLOAT_EQ(lm2_alpha_f32(0.0f, 0.0f, 10.0f), 0.0f);
  EXPECT_FLOAT_EQ(lm2_alpha_f32(0.0f, 5.0f, 10.0f), 0.5f);
  EXPECT_FLOAT_EQ(lm2_alpha_f32(0.0f, 10.0f, 10.0f), 1.0f);
}

// =============================================================================
// Fract Tests
// =============================================================================

TEST_F(ScalarTest, Fract_F64) {
  EXPECT_NEAR(lm2_fract_f64(3.7), 0.7, EPSILON_F64);
  EXPECT_NEAR(lm2_fract_f64(-3.7), 0.3, EPSILON_F64);
  EXPECT_DOUBLE_EQ(lm2_fract_f64(5.0), 0.0);
}

TEST_F(ScalarTest, Fract_F32) {
  EXPECT_NEAR(lm2_fract_f32(3.7f), 0.7f, EPSILON_F32);
  EXPECT_NEAR(lm2_fract_f32(-3.7f), 0.3f, EPSILON_F32);
  EXPECT_FLOAT_EQ(lm2_fract_f32(5.0f), 0.0f);
}

// =============================================================================
// Mod Tests
// =============================================================================

TEST_F(ScalarTest, Mod_F64) {
  EXPECT_NEAR(lm2_mod_f64(7.5, 3.0), 1.5, EPSILON_F64);
  EXPECT_NEAR(lm2_mod_f64(-7.5, 3.0), -1.5, EPSILON_F64);  // fmod keeps sign of dividend
  EXPECT_NEAR(lm2_mod_f64(7.5, -3.0), 1.5, EPSILON_F64);
}

TEST_F(ScalarTest, Mod_F32) {
  EXPECT_NEAR(lm2_mod_f32(7.5f, 3.0f), 1.5f, EPSILON_F32);
  EXPECT_NEAR(lm2_mod_f32(-7.5f, 3.0f), -1.5f, EPSILON_F32);  // fmod keeps sign of dividend
}

// =============================================================================
// Power Tests
// =============================================================================

TEST_F(ScalarTest, Pow_F64) {
  EXPECT_DOUBLE_EQ(lm2_pow_f64(2.0, 3.0), 8.0);
  EXPECT_DOUBLE_EQ(lm2_pow_f64(5.0, 2.0), 25.0);
  EXPECT_DOUBLE_EQ(lm2_pow_f64(2.0, 0.0), 1.0);
  EXPECT_NEAR(lm2_pow_f64(9.0, 0.5), 3.0, EPSILON_F64);
}

TEST_F(ScalarTest, Pow_F32) {
  EXPECT_FLOAT_EQ(lm2_pow_f32(2.0f, 3.0f), 8.0f);
  EXPECT_FLOAT_EQ(lm2_pow_f32(5.0f, 2.0f), 25.0f);
  EXPECT_FLOAT_EQ(lm2_pow_f32(2.0f, 0.0f), 1.0f);
}

// =============================================================================
// Sqrt Tests
// =============================================================================

TEST_F(ScalarTest, Sqrt_F64) {
  EXPECT_DOUBLE_EQ(lm2_sqrt_f64(4.0), 2.0);
  EXPECT_DOUBLE_EQ(lm2_sqrt_f64(9.0), 3.0);
  EXPECT_DOUBLE_EQ(lm2_sqrt_f64(0.0), 0.0);
  EXPECT_NEAR(lm2_sqrt_f64(2.0), 1.41421356237, EPSILON_F64);
}

TEST_F(ScalarTest, Sqrt_F32) {
  EXPECT_FLOAT_EQ(lm2_sqrt_f32(4.0f), 2.0f);
  EXPECT_FLOAT_EQ(lm2_sqrt_f32(9.0f), 3.0f);
  EXPECT_FLOAT_EQ(lm2_sqrt_f32(0.0f), 0.0f);
  EXPECT_NEAR(lm2_sqrt_f32(2.0f), 1.41421356f, EPSILON_F32);
}

// Test integer overloads at both limits and across every clamp branch.
#define DEFINE_INTEGER_COMPARISON_TEST(suffix, value_type)          \
  TEST_F(ScalarTest, IntegerComparisons_##suffix) {                 \
    const value_type low = std::numeric_limits<value_type>::min();  \
    const value_type high = std::numeric_limits<value_type>::max(); \
    EXPECT_EQ(lm2_min_##suffix(low, high), low);                    \
    EXPECT_EQ(lm2_min_##suffix(high, low), low);                    \
    EXPECT_EQ(lm2_max_##suffix(low, high), high);                   \
    EXPECT_EQ(lm2_max_##suffix(high, low), high);                   \
    EXPECT_EQ(lm2_min_##suffix(high, high), high);                  \
    EXPECT_EQ(lm2_max_##suffix(low, low), low);                     \
    EXPECT_EQ(lm2_clamp_##suffix(2, 1, 6), 2);                      \
    EXPECT_EQ(lm2_clamp_##suffix(2, 2, 6), 2);                      \
    EXPECT_EQ(lm2_clamp_##suffix(2, 4, 6), 4);                      \
    EXPECT_EQ(lm2_clamp_##suffix(2, 6, 6), 6);                      \
    EXPECT_EQ(lm2_clamp_##suffix(2, 7, 6), 6);                      \
    EXPECT_EQ(lm2_clamp_##suffix(4, 0, 4), 4);                      \
    EXPECT_DEATH((void)lm2_clamp_##suffix(6, 4, 2), "");            \
  }

DEFINE_INTEGER_COMPARISON_TEST(i64, int64_t);
DEFINE_INTEGER_COMPARISON_TEST(i32, int32_t);
DEFINE_INTEGER_COMPARISON_TEST(i16, int16_t);
DEFINE_INTEGER_COMPARISON_TEST(i8, int8_t);
DEFINE_INTEGER_COMPARISON_TEST(u64, uint64_t);
DEFINE_INTEGER_COMPARISON_TEST(u32, uint32_t);
DEFINE_INTEGER_COMPARISON_TEST(u16, uint16_t);
DEFINE_INTEGER_COMPARISON_TEST(u8, uint8_t);

#undef DEFINE_INTEGER_COMPARISON_TEST

#define DEFINE_SIGNED_MAGNITUDE_TEST(suffix, value_type)            \
  TEST_F(ScalarTest, SignedMagnitudeAndSign_##suffix) {             \
    const value_type low = std::numeric_limits<value_type>::min();  \
    const value_type high = std::numeric_limits<value_type>::max(); \
    EXPECT_EQ(lm2_abs_##suffix(-7), 7);                             \
    EXPECT_EQ(lm2_abs_##suffix(0), 0);                              \
    EXPECT_EQ(lm2_abs_##suffix(high), high);                        \
    EXPECT_EQ(lm2_sign_##suffix(low), -1);                          \
    EXPECT_EQ(lm2_sign_##suffix(0), 1);                             \
    EXPECT_EQ(lm2_sign_##suffix(high), 1);                          \
    EXPECT_EQ(lm2_sign0_##suffix(low), -1);                         \
    EXPECT_EQ(lm2_sign0_##suffix(0), 0);                            \
    EXPECT_EQ(lm2_sign0_##suffix(high), 1);                         \
    EXPECT_EQ(lm2_min_abs_##suffix(-3, 7), -3);                     \
    EXPECT_EQ(lm2_min_abs_##suffix(7, -3), -3);                     \
    EXPECT_EQ(lm2_max_abs_##suffix(-3, 7), 7);                      \
    EXPECT_EQ(lm2_max_abs_##suffix(7, -3), 7);                      \
    EXPECT_EQ(lm2_min_abs_##suffix(low, high), high);               \
    EXPECT_EQ(lm2_min_abs_##suffix(high, low), high);               \
    EXPECT_EQ(lm2_max_abs_##suffix(low, high), low);                \
    EXPECT_EQ(lm2_max_abs_##suffix(high, low), low);                \
    EXPECT_DEATH((void)lm2_abs_##suffix(low), "");                  \
  }

DEFINE_SIGNED_MAGNITUDE_TEST(i64, int64_t);
DEFINE_SIGNED_MAGNITUDE_TEST(i32, int32_t);
DEFINE_SIGNED_MAGNITUDE_TEST(i16, int16_t);
DEFINE_SIGNED_MAGNITUDE_TEST(i8, int8_t);

#undef DEFINE_SIGNED_MAGNITUDE_TEST

template <typename Function>
static void expect_scalar_assertion(Function function) {
  EXPECT_DEATH((void)function(), "");
}

#define DEFINE_FLOAT_BOUNDARY_TEST(suffix, value_type)                         \
  TEST_F(ScalarTest, FloatingPointBoundaries_##suffix) {                       \
    const value_type inf = std::numeric_limits<value_type>::infinity();        \
    const value_type nan = std::numeric_limits<value_type>::quiet_NaN();       \
    EXPECT_EQ(lm2_sign_##suffix(-0.0), 1);                                     \
    EXPECT_EQ(lm2_sign0_##suffix(-0.0), 0);                                    \
    EXPECT_EQ(lm2_fract_##suffix(-1.25), 0.75);                                \
    EXPECT_EQ(lm2_lerp_##suffix(2, -1, 6), -2);                                \
    EXPECT_EQ(lm2_alpha_##suffix(6, 4, 2), 0.5);                               \
    EXPECT_EQ(lm2_smoothstep_##suffix(2, 3, 6), 0.15625);                      \
    EXPECT_EQ(lm2_round_multiple_##suffix(-5, 2), -6);                         \
    expect_scalar_assertion([&] { return lm2_floor_##suffix(inf); });          \
    expect_scalar_assertion([&] { return lm2_ceil_##suffix(nan); });           \
    expect_scalar_assertion([] { return lm2_floor_multiple_##suffix(1, 0); }); \
    expect_scalar_assertion([] { return lm2_ceil_multiple_##suffix(1, 0); });  \
    expect_scalar_assertion([] { return lm2_round_multiple_##suffix(1, 0); }); \
    expect_scalar_assertion([] { return lm2_trunc_multiple_##suffix(1, 0); }); \
    expect_scalar_assertion([] { return lm2_smoothstep_##suffix(1, 1, 1); });  \
    expect_scalar_assertion([] { return lm2_alpha_##suffix(1, 0, 1); });       \
    expect_scalar_assertion([] { return lm2_pow_##suffix(-1, 0.5); });         \
    expect_scalar_assertion([] { return lm2_sqrt_##suffix(-1); });             \
  }

DEFINE_FLOAT_BOUNDARY_TEST(f64, double);
DEFINE_FLOAT_BOUNDARY_TEST(f32, float);

#undef DEFINE_FLOAT_BOUNDARY_TEST
