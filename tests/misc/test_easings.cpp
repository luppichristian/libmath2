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
#include "lm2/misc/lm2_easings.h"

// Test fixture for easing tests
class EasingsTest : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Linear Easing Tests
// =============================================================================

TEST_F(EasingsTest, Linear_F64) {
  EXPECT_NEAR(lm2_ease_linear_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_linear_f64(0.5), 0.5, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_linear_f64(1.0), 1.0, EPSILON_F64);
}

TEST_F(EasingsTest, Linear_F32) {
  EXPECT_NEAR(lm2_ease_linear_f32(0.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_linear_f32(0.5f), 0.5f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_linear_f32(1.0f), 1.0f, EPSILON_F32);
}

// =============================================================================
// Sin Easing Tests
// =============================================================================

TEST_F(EasingsTest, SinIn_F64) {
  EXPECT_NEAR(lm2_ease_sin_in_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_sin_in_f64(1.0), 1.0, EPSILON_F64);
  // Sin in should start slow and end fast
  EXPECT_LT(lm2_ease_sin_in_f64(0.5), 0.5);
}

TEST_F(EasingsTest, SinOut_F64) {
  EXPECT_NEAR(lm2_ease_sin_out_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_sin_out_f64(1.0), 1.0, EPSILON_F64);
  // Sin out should start fast and end slow
  EXPECT_GT(lm2_ease_sin_out_f64(0.5), 0.5);
}

TEST_F(EasingsTest, SinInOut_F64) {
  EXPECT_NEAR(lm2_ease_sin_in_out_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_sin_in_out_f64(0.5), 0.5, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_sin_in_out_f64(1.0), 1.0, EPSILON_F64);
}

TEST_F(EasingsTest, Sin_F32) {
  EXPECT_NEAR(lm2_ease_sin_in_f32(0.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_sin_in_f32(1.0f), 1.0f, EPSILON_F32);

  EXPECT_NEAR(lm2_ease_sin_out_f32(0.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_sin_out_f32(1.0f), 1.0f, EPSILON_F32);

  EXPECT_NEAR(lm2_ease_sin_in_out_f32(0.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_sin_in_out_f32(1.0f), 1.0f, EPSILON_F32);
}

// =============================================================================
// Quad Easing Tests
// =============================================================================

TEST_F(EasingsTest, QuadIn_F64) {
  EXPECT_NEAR(lm2_ease_quad_in_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_quad_in_f64(1.0), 1.0, EPSILON_F64);
  // Quad in: t^2
  EXPECT_NEAR(lm2_ease_quad_in_f64(0.5), 0.25, EPSILON_F64);
}

TEST_F(EasingsTest, QuadOut_F64) {
  EXPECT_NEAR(lm2_ease_quad_out_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_quad_out_f64(1.0), 1.0, EPSILON_F64);
  // Quad out should be faster than linear
  EXPECT_GT(lm2_ease_quad_out_f64(0.5), 0.5);
}

TEST_F(EasingsTest, QuadInOut_F64) {
  EXPECT_NEAR(lm2_ease_quad_in_out_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_quad_in_out_f64(0.5), 0.5, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_quad_in_out_f64(1.0), 1.0, EPSILON_F64);
}

TEST_F(EasingsTest, Quad_F32) {
  EXPECT_NEAR(lm2_ease_quad_in_f32(0.5f), 0.25f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_quad_out_f32(0.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_quad_in_out_f32(1.0f), 1.0f, EPSILON_F32);
}

// =============================================================================
// Cubic Easing Tests
// =============================================================================

TEST_F(EasingsTest, CubicIn_F64) {
  EXPECT_NEAR(lm2_ease_cubic_in_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_cubic_in_f64(1.0), 1.0, EPSILON_F64);
  // Cubic in: t^3
  EXPECT_NEAR(lm2_ease_cubic_in_f64(0.5), 0.125, EPSILON_F64);
}

TEST_F(EasingsTest, CubicOut_F64) {
  EXPECT_NEAR(lm2_ease_cubic_out_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_cubic_out_f64(1.0), 1.0, EPSILON_F64);
}

TEST_F(EasingsTest, CubicInOut_F64) {
  EXPECT_NEAR(lm2_ease_cubic_in_out_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_cubic_in_out_f64(0.5), 0.5, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_cubic_in_out_f64(1.0), 1.0, EPSILON_F64);
}

TEST_F(EasingsTest, Cubic_F32) {
  EXPECT_NEAR(lm2_ease_cubic_in_f32(0.5f), 0.125f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_cubic_out_f32(0.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_cubic_in_out_f32(1.0f), 1.0f, EPSILON_F32);
}

// =============================================================================
// Quart Easing Tests
// =============================================================================

TEST_F(EasingsTest, QuartIn_F64) {
  EXPECT_NEAR(lm2_ease_quart_in_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_quart_in_f64(1.0), 1.0, EPSILON_F64);
  // Quart in: t^4
  EXPECT_NEAR(lm2_ease_quart_in_f64(0.5), 0.0625, EPSILON_F64);
}

TEST_F(EasingsTest, QuartOut_F64) {
  EXPECT_NEAR(lm2_ease_quart_out_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_quart_out_f64(1.0), 1.0, EPSILON_F64);
}

TEST_F(EasingsTest, QuartInOut_F64) {
  EXPECT_NEAR(lm2_ease_quart_in_out_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_quart_in_out_f64(0.5), 0.5, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_quart_in_out_f64(1.0), 1.0, EPSILON_F64);
}

TEST_F(EasingsTest, Quart_F32) {
  EXPECT_NEAR(lm2_ease_quart_in_f32(0.5f), 0.0625f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_quart_out_f32(0.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_quart_in_out_f32(1.0f), 1.0f, EPSILON_F32);
}

// =============================================================================
// Quint Easing Tests
// =============================================================================

TEST_F(EasingsTest, QuintIn_F64) {
  EXPECT_NEAR(lm2_ease_quint_in_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_quint_in_f64(1.0), 1.0, EPSILON_F64);
  // Quint in: t^5
  EXPECT_NEAR(lm2_ease_quint_in_f64(0.5), 0.03125, EPSILON_F64);
}

TEST_F(EasingsTest, QuintOut_F64) {
  EXPECT_NEAR(lm2_ease_quint_out_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_quint_out_f64(1.0), 1.0, EPSILON_F64);
}

TEST_F(EasingsTest, QuintInOut_F64) {
  EXPECT_NEAR(lm2_ease_quint_in_out_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_quint_in_out_f64(0.5), 0.5, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_quint_in_out_f64(1.0), 1.0, EPSILON_F64);
}

TEST_F(EasingsTest, Quint_F32) {
  EXPECT_NEAR(lm2_ease_quint_in_f32(0.5f), 0.03125f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_quint_out_f32(0.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_quint_in_out_f32(1.0f), 1.0f, EPSILON_F32);
}

// =============================================================================
// Exp Easing Tests
// =============================================================================

TEST_F(EasingsTest, ExpIn_F64) {
  EXPECT_NEAR(lm2_ease_exp_in_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_exp_in_f64(1.0), 1.0, EPSILON_F64);
  // Exp in should start very slow
  EXPECT_LT(lm2_ease_exp_in_f64(0.5), 0.1);
}

TEST_F(EasingsTest, ExpOut_F64) {
  EXPECT_NEAR(lm2_ease_exp_out_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_exp_out_f64(1.0), 1.0, EPSILON_F64);
  // Exp out should start very fast
  EXPECT_GT(lm2_ease_exp_out_f64(0.5), 0.9);
}

TEST_F(EasingsTest, ExpInOut_F64) {
  EXPECT_NEAR(lm2_ease_exp_in_out_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_exp_in_out_f64(0.5), 0.5, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_exp_in_out_f64(1.0), 1.0, EPSILON_F64);
}

TEST_F(EasingsTest, Exp_F32) {
  EXPECT_NEAR(lm2_ease_exp_in_f32(0.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_exp_out_f32(1.0f), 1.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_exp_in_out_f32(0.5f), 0.5f, EPSILON_F32);
}

// =============================================================================
// Circ Easing Tests
// =============================================================================

TEST_F(EasingsTest, CircIn_F64) {
  EXPECT_NEAR(lm2_ease_circ_in_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_circ_in_f64(1.0), 1.0, EPSILON_F64);
  // Circ in should start slow
  EXPECT_LT(lm2_ease_circ_in_f64(0.5), 0.5);
}

TEST_F(EasingsTest, CircOut_F64) {
  EXPECT_NEAR(lm2_ease_circ_out_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_circ_out_f64(1.0), 1.0, EPSILON_F64);
  // Circ out should start fast
  EXPECT_GT(lm2_ease_circ_out_f64(0.5), 0.5);
}

TEST_F(EasingsTest, CircInOut_F64) {
  EXPECT_NEAR(lm2_ease_circ_in_out_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_circ_in_out_f64(0.5), 0.5, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_circ_in_out_f64(1.0), 1.0, EPSILON_F64);
}

TEST_F(EasingsTest, Circ_F32) {
  EXPECT_NEAR(lm2_ease_circ_in_f32(0.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_circ_out_f32(1.0f), 1.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_circ_in_out_f32(0.5f), 0.5f, EPSILON_F32);
}

// =============================================================================
// Back Easing Tests
// =============================================================================

TEST_F(EasingsTest, BackIn_F64) {
  EXPECT_NEAR(lm2_ease_back_in_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_back_in_f64(1.0), 1.0, EPSILON_F64);
  // Back in should go negative before moving forward
  EXPECT_LT(lm2_ease_back_in_f64(0.3), 0.0);
}

TEST_F(EasingsTest, BackOut_F64) {
  EXPECT_NEAR(lm2_ease_back_out_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_back_out_f64(1.0), 1.0, EPSILON_F64);
  // Back out should overshoot before settling
  EXPECT_GT(lm2_ease_back_out_f64(0.7), 1.0);
}

TEST_F(EasingsTest, BackInOut_F64) {
  EXPECT_NEAR(lm2_ease_back_in_out_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_back_in_out_f64(0.5), 0.5, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_back_in_out_f64(1.0), 1.0, EPSILON_F64);
}

TEST_F(EasingsTest, Back_F32) {
  EXPECT_NEAR(lm2_ease_back_in_f32(0.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_back_out_f32(1.0f), 1.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_back_in_out_f32(0.5f), 0.5f, EPSILON_F32);
}

// =============================================================================
// Elastic Easing Tests
// =============================================================================

TEST_F(EasingsTest, ElasticIn_F64) {
  EXPECT_NEAR(lm2_ease_elastic_in_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_elastic_in_f64(1.0), 1.0, EPSILON_F64);
  // Elastic should oscillate
}

TEST_F(EasingsTest, ElasticOut_F64) {
  EXPECT_NEAR(lm2_ease_elastic_out_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_elastic_out_f64(1.0), 1.0, EPSILON_F64);
}

TEST_F(EasingsTest, ElasticInOut_F64) {
  EXPECT_NEAR(lm2_ease_elastic_in_out_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_elastic_in_out_f64(0.5), 0.5, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_elastic_in_out_f64(1.0), 1.0, EPSILON_F64);
}

TEST_F(EasingsTest, Elastic_F32) {
  EXPECT_NEAR(lm2_ease_elastic_in_f32(0.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_elastic_out_f32(1.0f), 1.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_elastic_in_out_f32(0.5f), 0.5f, EPSILON_F32);
}

// =============================================================================
// Bounce Easing Tests
// =============================================================================

TEST_F(EasingsTest, BounceIn_F64) {
  EXPECT_NEAR(lm2_ease_bounce_in_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_bounce_in_f64(1.0), 1.0, EPSILON_F64);
}

TEST_F(EasingsTest, BounceOut_F64) {
  EXPECT_NEAR(lm2_ease_bounce_out_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_bounce_out_f64(1.0), 1.0, EPSILON_F64);
}

TEST_F(EasingsTest, BounceInOut_F64) {
  EXPECT_NEAR(lm2_ease_bounce_in_out_f64(0.0), 0.0, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_bounce_in_out_f64(0.5), 0.5, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_bounce_in_out_f64(1.0), 1.0, EPSILON_F64);
}

TEST_F(EasingsTest, Bounce_F32) {
  EXPECT_NEAR(lm2_ease_bounce_in_f32(0.0f), 0.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_bounce_out_f32(1.0f), 1.0f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_bounce_in_out_f32(0.5f), 0.5f, EPSILON_F32);
}

// =============================================================================
// Generalized Easing Function Tests
// =============================================================================

TEST_F(EasingsTest, GeneralizedEasing_F64) {
  // Test a few easing types through the generalized function
  EXPECT_NEAR(lm2_ease_f64(EASING_LINEAR, 0.5), 0.5, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_f64(EASING_QUAD_IN, 0.5), 0.25, EPSILON_F64);
  EXPECT_NEAR(lm2_ease_f64(EASING_CUB_IN, 0.5), 0.125, EPSILON_F64);

  // All easings should map 0 to 0 and 1 to 1
  for (int i = EASING_LINEAR; i < EASING_MAX; ++i) {
    easing e = static_cast<easing>(i);
    EXPECT_NEAR(lm2_ease_f64(e, 0.0), 0.0, EPSILON_F64) << "Easing type: " << i;
    EXPECT_NEAR(lm2_ease_f64(e, 1.0), 1.0, EPSILON_F64) << "Easing type: " << i;

    // For in-out types, midpoint should be 0.5
    if (i == EASING_SIN_IN_OUT || i == EASING_CUB_IN_OUT || i == EASING_QUINT_IN_OUT ||
        i == EASING_CIRC_IN_OUT || i == EASING_ELASTIC_IN_OUT || i == EASING_QUAD_IN_OUT ||
        i == EASING_QUART_IN_OUT || i == EASING_EXP_IN_OUT || i == EASING_BACK_IN_OUT ||
        i == EASING_BOUNCE_IN_OUT) {
      EXPECT_NEAR(lm2_ease_f64(e, 0.5), 0.5, EPSILON_F64) << "Easing type: " << i;
    }
  }
}

TEST_F(EasingsTest, GeneralizedEasing_F32) {
  EXPECT_NEAR(lm2_ease_f32(EASING_LINEAR, 0.5f), 0.5f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_f32(EASING_QUAD_IN, 0.5f), 0.25f, EPSILON_F32);
  EXPECT_NEAR(lm2_ease_f32(EASING_CUB_IN, 0.5f), 0.125f, EPSILON_F32);
}

// =============================================================================
// Easing to String Tests
// =============================================================================

TEST_F(EasingsTest, EasingToString) {
  EXPECT_STREQ(lm2_easing_to_string(EASING_LINEAR), "EASING_LINEAR");
  EXPECT_STREQ(lm2_easing_to_string(EASING_SIN_IN), "EASING_SIN_IN");
  EXPECT_STREQ(lm2_easing_to_string(EASING_QUAD_IN), "EASING_QUAD_IN");
  EXPECT_STREQ(lm2_easing_to_string(EASING_CUB_IN), "EASING_CUB_IN");
  EXPECT_STREQ(lm2_easing_to_string(EASING_QUINT_IN), "EASING_QUINT_IN");
  EXPECT_STREQ(lm2_easing_to_string(EASING_CIRC_IN), "EASING_CIRC_IN");
  EXPECT_STREQ(lm2_easing_to_string(EASING_ELASTIC_IN), "EASING_ELASTIC_IN");
  EXPECT_STREQ(lm2_easing_to_string(EASING_BACK_IN), "EASING_BACK_IN");
  EXPECT_STREQ(lm2_easing_to_string(EASING_BOUNCE_IN), "EASING_BOUNCE_IN");
}

// =============================================================================
// Monotonicity Tests
// =============================================================================

TEST_F(EasingsTest, MonotonicityIn) {
  // In easings should be monotonically increasing
  double prev_sin = 0.0;
  double prev_quad = 0.0;
  double prev_cubic = 0.0;
  for (double t = 0.0; t <= 1.0; t += 0.01) {
    double curr_sin = lm2_ease_sin_in_f64(t);
    double curr_quad = lm2_ease_quad_in_f64(t);
    double curr_cubic = lm2_ease_cubic_in_f64(t);

    EXPECT_GE(curr_sin, prev_sin - EPSILON_F64);
    EXPECT_GE(curr_quad, prev_quad - EPSILON_F64);
    EXPECT_GE(curr_cubic, prev_cubic - EPSILON_F64);

    prev_sin = curr_sin;
    prev_quad = curr_quad;
    prev_cubic = curr_cubic;
  }
}

TEST_F(EasingsTest, MonotonicityOut) {
  // Out easings should be monotonically increasing
  double prev_sin = 0.0;
  double prev_quad = 0.0;
  double prev_cubic = 0.0;
  for (double t = 0.0; t <= 1.0; t += 0.01) {
    double curr_sin = lm2_ease_sin_out_f64(t);
    double curr_quad = lm2_ease_quad_out_f64(t);
    double curr_cubic = lm2_ease_cubic_out_f64(t);

    EXPECT_GE(curr_sin, prev_sin - EPSILON_F64);
    EXPECT_GE(curr_quad, prev_quad - EPSILON_F64);
    EXPECT_GE(curr_cubic, prev_cubic - EPSILON_F64);

    prev_sin = curr_sin;
    prev_quad = curr_quad;
    prev_cubic = curr_cubic;
  }
}
