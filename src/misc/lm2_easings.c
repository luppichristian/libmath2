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

#include <lm2/misc/lm2_easings.h>
#include <lm2/lm2_constants.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/scalar/lm2_trigonometry.h>
#include <math.h>

// =============================================================================
// Linear
// =============================================================================

LM2_API double ease_linear_f64(double t) {
  return t;
}

LM2_API float ease_linear_f32(float t) {
  return t;
}

// =============================================================================
// Sin
// =============================================================================

LM2_API double ease_sin_in_f64(double t) {
  return lm2_sub_f64(1.0, lm2_cos_f64(lm2_mul_f64(t, LM2_HPI_F64)));
}

LM2_API double ease_sin_out_f64(double t) {
  return lm2_sin_f64(lm2_mul_f64(t, LM2_HPI_F64));
}

LM2_API double ease_sin_in_out_f64(double t) {
  return lm2_div_f64(-lm2_sub_f64(lm2_cos_f64(lm2_mul_f64(LM2_PI_F64, t)), 1.0), 2.0);
}

LM2_API float ease_sin_in_f32(float t) {
  return lm2_sub_f32(1.0f, lm2_cos_f32(lm2_mul_f32(t, LM2_HPI_F32)));
}

LM2_API float ease_sin_out_f32(float t) {
  return lm2_sin_f32(lm2_mul_f32(t, LM2_HPI_F32));
}

LM2_API float ease_sin_in_out_f32(float t) {
  return lm2_div_f32(-lm2_sub_f32(lm2_cos_f32(lm2_mul_f32(LM2_PI_F32, t)), 1.0f), 2.0f);
}

// =============================================================================
// Quad
// =============================================================================

LM2_API double ease_quad_in_f64(double t) {
  return lm2_mul_f64(t, t);
}

LM2_API double ease_quad_out_f64(double t) {
  return lm2_sub_f64(1.0, lm2_mul_f64(lm2_sub_f64(1.0, t), lm2_sub_f64(1.0, t)));
}

LM2_API double ease_quad_in_out_f64(double t) {
  return t < 0.5 ? lm2_mul_f64(lm2_mul_f64(2.0, t), t) : lm2_sub_f64(1.0, lm2_div_f64(lm2_pow_f64(lm2_add_f64(lm2_mul_f64(-2.0, t), 2.0), 2.0), 2.0));
}

LM2_API float ease_quad_in_f32(float t) {
  return lm2_mul_f32(t, t);
}

LM2_API float ease_quad_out_f32(float t) {
  return lm2_sub_f32(1.0f, lm2_mul_f32(lm2_sub_f32(1.0f, t), lm2_sub_f32(1.0f, t)));
}

LM2_API float ease_quad_in_out_f32(float t) {
  return t < 0.5f ? lm2_mul_f32(lm2_mul_f32(2.0f, t), t) : lm2_sub_f32(1.0f, lm2_div_f32(lm2_pow_f32(lm2_add_f32(lm2_mul_f32(-2.0f, t), 2.0f), 2.0f), 2.0f));
}

// =============================================================================
// Cubic
// =============================================================================

LM2_API double ease_cubic_in_f64(double t) {
  return lm2_mul_f64(lm2_mul_f64(t, t), t);
}

LM2_API double ease_cubic_out_f64(double t) {
  double u = lm2_sub_f64(1.0, t);
  return lm2_sub_f64(1.0, lm2_mul_f64(lm2_mul_f64(u, u), u));
}

LM2_API double ease_cubic_in_out_f64(double t) {
  return t < 0.5 ? lm2_mul_f64(lm2_mul_f64(lm2_mul_f64(4.0, t), t), t) : lm2_sub_f64(1.0, lm2_div_f64(lm2_pow_f64(lm2_add_f64(lm2_mul_f64(-2.0, t), 2.0), 3.0), 2.0));
}

LM2_API float ease_cubic_in_f32(float t) {
  return lm2_mul_f32(lm2_mul_f32(t, t), t);
}

LM2_API float ease_cubic_out_f32(float t) {
  float u = lm2_sub_f32(1.0f, t);
  return lm2_sub_f32(1.0f, lm2_mul_f32(lm2_mul_f32(u, u), u));
}

LM2_API float ease_cubic_in_out_f32(float t) {
  return t < 0.5f ? lm2_mul_f32(lm2_mul_f32(lm2_mul_f32(4.0f, t), t), t) : lm2_sub_f32(1.0f, lm2_div_f32(lm2_pow_f32(lm2_add_f32(lm2_mul_f32(-2.0f, t), 2.0f), 3.0f), 2.0f));
}

// =============================================================================
// Quart
// =============================================================================

LM2_API double ease_quart_in_f64(double t) {
  return lm2_mul_f64(lm2_mul_f64(lm2_mul_f64(t, t), t), t);
}

LM2_API double ease_quart_out_f64(double t) {
  double u = lm2_sub_f64(1.0, t);
  return lm2_sub_f64(1.0, lm2_mul_f64(lm2_mul_f64(lm2_mul_f64(u, u), u), u));
}

LM2_API double ease_quart_in_out_f64(double t) {
  return t < 0.5 ? lm2_mul_f64(lm2_mul_f64(lm2_mul_f64(lm2_mul_f64(8.0, t), t), t), t) : lm2_sub_f64(1.0, lm2_div_f64(lm2_pow_f64(lm2_add_f64(lm2_mul_f64(-2.0, t), 2.0), 4.0), 2.0));
}

LM2_API float ease_quart_in_f32(float t) {
  return lm2_mul_f32(lm2_mul_f32(lm2_mul_f32(t, t), t), t);
}

LM2_API float ease_quart_out_f32(float t) {
  float u = lm2_sub_f32(1.0f, t);
  return lm2_sub_f32(1.0f, lm2_mul_f32(lm2_mul_f32(lm2_mul_f32(u, u), u), u));
}

LM2_API float ease_quart_in_out_f32(float t) {
  return t < 0.5f ? lm2_mul_f32(lm2_mul_f32(lm2_mul_f32(lm2_mul_f32(8.0f, t), t), t), t) : lm2_sub_f32(1.0f, lm2_div_f32(lm2_pow_f32(lm2_add_f32(lm2_mul_f32(-2.0f, t), 2.0f), 4.0f), 2.0f));
}

// =============================================================================
// Quint
// =============================================================================

LM2_API double ease_quint_in_f64(double t) {
  return lm2_mul_f64(lm2_mul_f64(lm2_mul_f64(lm2_mul_f64(t, t), t), t), t);
}

LM2_API double ease_quint_out_f64(double t) {
  double u = lm2_sub_f64(1.0, t);
  return lm2_sub_f64(1.0, lm2_mul_f64(lm2_mul_f64(lm2_mul_f64(lm2_mul_f64(u, u), u), u), u));
}

LM2_API double ease_quint_in_out_f64(double t) {
  return t < 0.5 ? lm2_mul_f64(lm2_mul_f64(lm2_mul_f64(lm2_mul_f64(lm2_mul_f64(16.0, t), t), t), t), t) : lm2_sub_f64(1.0, lm2_div_f64(lm2_pow_f64(lm2_add_f64(lm2_mul_f64(-2.0, t), 2.0), 5.0), 2.0));
}

LM2_API float ease_quint_in_f32(float t) {
  return lm2_mul_f32(lm2_mul_f32(lm2_mul_f32(lm2_mul_f32(t, t), t), t), t);
}

LM2_API float ease_quint_out_f32(float t) {
  float u = lm2_sub_f32(1.0f, t);
  return lm2_sub_f32(1.0f, lm2_mul_f32(lm2_mul_f32(lm2_mul_f32(lm2_mul_f32(u, u), u), u), u));
}

LM2_API float ease_quint_in_out_f32(float t) {
  return t < 0.5f ? lm2_mul_f32(lm2_mul_f32(lm2_mul_f32(lm2_mul_f32(lm2_mul_f32(16.0f, t), t), t), t), t) : lm2_sub_f32(1.0f, lm2_div_f32(lm2_pow_f32(lm2_add_f32(lm2_mul_f32(-2.0f, t), 2.0f), 5.0f), 2.0f));
}

// =============================================================================
// Exp
// =============================================================================

LM2_API double ease_exp_in_f64(double t) {
  return t == 0.0 ? 0.0 : lm2_pow_f64(2.0, lm2_sub_f64(lm2_mul_f64(10.0, t), 10.0));
}

LM2_API double ease_exp_out_f64(double t) {
  return t == 1.0 ? 1.0 : lm2_sub_f64(1.0, lm2_pow_f64(2.0, lm2_mul_f64(-10.0, t)));
}

LM2_API double ease_exp_in_out_f64(double t) {
  if (t == 0.0) return 0.0;
  if (t == 1.0) return 1.0;
  return t < 0.5 ? lm2_div_f64(lm2_pow_f64(2.0, lm2_sub_f64(lm2_mul_f64(20.0, t), 10.0)), 2.0) : lm2_div_f64(lm2_sub_f64(2.0, lm2_pow_f64(2.0, lm2_add_f64(lm2_mul_f64(-20.0, t), 10.0))), 2.0);
}

LM2_API float ease_exp_in_f32(float t) {
  return t == 0.0f ? 0.0f : lm2_pow_f32(2.0f, lm2_sub_f32(lm2_mul_f32(10.0f, t), 10.0f));
}

LM2_API float ease_exp_out_f32(float t) {
  return t == 1.0f ? 1.0f : lm2_sub_f32(1.0f, lm2_pow_f32(2.0f, lm2_mul_f32(-10.0f, t)));
}

LM2_API float ease_exp_in_out_f32(float t) {
  if (t == 0.0f) return 0.0f;
  if (t == 1.0f) return 1.0f;
  return t < 0.5f ? lm2_div_f32(lm2_pow_f32(2.0f, lm2_sub_f32(lm2_mul_f32(20.0f, t), 10.0f)), 2.0f) : lm2_div_f32(lm2_sub_f32(2.0f, lm2_pow_f32(2.0f, lm2_add_f32(lm2_mul_f32(-20.0f, t), 10.0f))), 2.0f);
}

// =============================================================================
// Circ
// =============================================================================

LM2_API double ease_circ_in_f64(double t) {
  return lm2_sub_f64(1.0, lm2_sqrt_f64(lm2_sub_f64(1.0, lm2_mul_f64(t, t))));
}

LM2_API double ease_circ_out_f64(double t) {
  return lm2_sqrt_f64(lm2_sub_f64(1.0, lm2_mul_f64(lm2_sub_f64(t, 1.0), lm2_sub_f64(t, 1.0))));
}

LM2_API double ease_circ_in_out_f64(double t) {
  return t < 0.5
             ? lm2_div_f64(lm2_sub_f64(1.0, lm2_sqrt_f64(lm2_sub_f64(1.0, lm2_pow_f64(lm2_mul_f64(2.0, t), 2.0)))), 2.0)
             : lm2_div_f64(lm2_add_f64(lm2_sqrt_f64(lm2_sub_f64(1.0, lm2_pow_f64(lm2_add_f64(lm2_mul_f64(-2.0, t), 2.0), 2.0))), 1.0), 2.0);
}

LM2_API float ease_circ_in_f32(float t) {
  return lm2_sub_f32(1.0f, lm2_sqrt_f32(lm2_sub_f32(1.0f, lm2_mul_f32(t, t))));
}

LM2_API float ease_circ_out_f32(float t) {
  return lm2_sqrt_f32(lm2_sub_f32(1.0f, lm2_mul_f32(lm2_sub_f32(t, 1.0f), lm2_sub_f32(t, 1.0f))));
}

LM2_API float ease_circ_in_out_f32(float t) {
  return t < 0.5f
             ? lm2_div_f32(lm2_sub_f32(1.0f, lm2_sqrt_f32(lm2_sub_f32(1.0f, lm2_pow_f32(lm2_mul_f32(2.0f, t), 2.0f)))), 2.0f)
             : lm2_div_f32(lm2_add_f32(lm2_sqrt_f32(lm2_sub_f32(1.0f, lm2_pow_f32(lm2_add_f32(lm2_mul_f32(-2.0f, t), 2.0f), 2.0f))), 1.0f), 2.0f);
}

// =============================================================================
// Back
// =============================================================================

LM2_API double ease_back_in_f64(double t) {
  const double c1 = 1.70158;
  const double c3 = lm2_add_f64(c1, 1.0);
  return lm2_sub_f64(lm2_mul_f64(lm2_mul_f64(lm2_mul_f64(c3, t), t), t), lm2_mul_f64(lm2_mul_f64(c1, t), t));
}

LM2_API double ease_back_out_f64(double t) {
  const double c1 = 1.70158;
  const double c3 = lm2_add_f64(c1, 1.0);
  double u = lm2_sub_f64(t, 1.0);
  return lm2_add_f64(lm2_add_f64(1.0, lm2_mul_f64(lm2_mul_f64(lm2_mul_f64(c3, u), u), u)), lm2_mul_f64(lm2_mul_f64(c1, u), u));
}

LM2_API double ease_back_in_out_f64(double t) {
  const double c1 = 1.70158;
  const double c2 = lm2_mul_f64(c1, 1.525);

  return t < 0.5
             ? lm2_div_f64(lm2_mul_f64(lm2_pow_f64(lm2_mul_f64(2.0, t), 2.0), lm2_sub_f64(lm2_mul_f64(lm2_add_f64(c2, 1.0), lm2_mul_f64(2.0, t)), c2)), 2.0)
             : lm2_div_f64(lm2_add_f64(lm2_mul_f64(lm2_pow_f64(lm2_sub_f64(lm2_mul_f64(2.0, t), 2.0), 2.0), lm2_add_f64(lm2_mul_f64(lm2_add_f64(c2, 1.0), lm2_sub_f64(lm2_mul_f64(t, 2.0), 2.0)), c2)), 2.0), 2.0);
}

LM2_API float ease_back_in_f32(float t) {
  const float c1 = 1.70158f;
  const float c3 = lm2_add_f32(c1, 1.0f);
  return lm2_sub_f32(lm2_mul_f32(lm2_mul_f32(lm2_mul_f32(c3, t), t), t), lm2_mul_f32(lm2_mul_f32(c1, t), t));
}

LM2_API float ease_back_out_f32(float t) {
  const float c1 = 1.70158f;
  const float c3 = lm2_add_f32(c1, 1.0f);
  float u = lm2_sub_f32(t, 1.0f);
  return lm2_add_f32(lm2_add_f32(1.0f, lm2_mul_f32(lm2_mul_f32(lm2_mul_f32(c3, u), u), u)), lm2_mul_f32(lm2_mul_f32(c1, u), u));
}

LM2_API float ease_back_in_out_f32(float t) {
  const float c1 = 1.70158f;
  const float c2 = lm2_mul_f32(c1, 1.525f);

  return t < 0.5f
             ? lm2_div_f32(lm2_mul_f32(lm2_pow_f32(lm2_mul_f32(2.0f, t), 2.0f), lm2_sub_f32(lm2_mul_f32(lm2_add_f32(c2, 1.0f), lm2_mul_f32(2.0f, t)), c2)), 2.0f)
             : lm2_div_f32(lm2_add_f32(lm2_mul_f32(lm2_pow_f32(lm2_sub_f32(lm2_mul_f32(2.0f, t), 2.0f), 2.0f), lm2_add_f32(lm2_mul_f32(lm2_add_f32(c2, 1.0f), lm2_sub_f32(lm2_mul_f32(t, 2.0f), 2.0f)), c2)), 2.0f), 2.0f);
}

// =============================================================================
// Elastic
// =============================================================================

LM2_API double ease_elastic_in_f64(double t) {
  const double c4 = lm2_div_f64(lm2_mul_f64(2.0, LM2_PI_F64), 3.0);

  if (t == 0.0) return 0.0;
  if (t == 1.0) return 1.0;
  return -lm2_mul_f64(lm2_pow_f64(2.0, lm2_sub_f64(lm2_mul_f64(10.0, t), 10.0)), lm2_sin_f64(lm2_mul_f64(lm2_sub_f64(lm2_mul_f64(t, 10.0), 10.75), c4)));
}

LM2_API double ease_elastic_out_f64(double t) {
  const double c4 = lm2_div_f64(lm2_mul_f64(2.0, LM2_PI_F64), 3.0);

  if (t == 0.0) return 0.0;
  if (t == 1.0) return 1.0;
  return lm2_add_f64(lm2_mul_f64(lm2_pow_f64(2.0, lm2_mul_f64(-10.0, t)), lm2_sin_f64(lm2_mul_f64(lm2_sub_f64(lm2_mul_f64(t, 10.0), 0.75), c4))), 1.0);
}

LM2_API double ease_elastic_in_out_f64(double t) {
  const double c5 = lm2_div_f64(lm2_mul_f64(2.0, LM2_PI_F64), 4.5);

  if (t == 0.0) return 0.0;
  if (t == 1.0) return 1.0;

  return t < 0.5
             ? lm2_div_f64(-lm2_mul_f64(lm2_pow_f64(2.0, lm2_sub_f64(lm2_mul_f64(20.0, t), 10.0)), lm2_sin_f64(lm2_mul_f64(lm2_sub_f64(lm2_mul_f64(20.0, t), 11.125), c5))), 2.0)
             : lm2_add_f64(lm2_div_f64(lm2_mul_f64(lm2_pow_f64(2.0, lm2_add_f64(lm2_mul_f64(-20.0, t), 10.0)), lm2_sin_f64(lm2_mul_f64(lm2_sub_f64(lm2_mul_f64(20.0, t), 11.125), c5))), 2.0), 1.0);
}

LM2_API float ease_elastic_in_f32(float t) {
  const float c4 = lm2_div_f32(lm2_mul_f32(2.0f, LM2_PI_F32), 3.0f);

  if (t == 0.0f) return 0.0f;
  if (t == 1.0f) return 1.0f;
  return -lm2_mul_f32(lm2_pow_f32(2.0f, lm2_sub_f32(lm2_mul_f32(10.0f, t), 10.0f)), lm2_sin_f32(lm2_mul_f32(lm2_sub_f32(lm2_mul_f32(t, 10.0f), 10.75f), c4)));
}

LM2_API float ease_elastic_out_f32(float t) {
  const float c4 = lm2_div_f32(lm2_mul_f32(2.0f, LM2_PI_F32), 3.0f);

  if (t == 0.0f) return 0.0f;
  if (t == 1.0f) return 1.0f;
  return lm2_add_f32(lm2_mul_f32(lm2_pow_f32(2.0f, lm2_mul_f32(-10.0f, t)), lm2_sin_f32(lm2_mul_f32(lm2_sub_f32(lm2_mul_f32(t, 10.0f), 0.75f), c4))), 1.0f);
}

LM2_API float ease_elastic_in_out_f32(float t) {
  const float c5 = lm2_div_f32(lm2_mul_f32(2.0f, LM2_PI_F32), 4.5f);

  if (t == 0.0f) return 0.0f;
  if (t == 1.0f) return 1.0f;

  return t < 0.5f
             ? lm2_div_f32(-lm2_mul_f32(lm2_pow_f32(2.0f, lm2_sub_f32(lm2_mul_f32(20.0f, t), 10.0f)), lm2_sin_f32(lm2_mul_f32(lm2_sub_f32(lm2_mul_f32(20.0f, t), 11.125f), c5))), 2.0f)
             : lm2_add_f32(lm2_div_f32(lm2_mul_f32(lm2_pow_f32(2.0f, lm2_add_f32(lm2_mul_f32(-20.0f, t), 10.0f)), lm2_sin_f32(lm2_mul_f32(lm2_sub_f32(lm2_mul_f32(20.0f, t), 11.125f), c5))), 2.0f), 1.0f);
}

// =============================================================================
// Bounce
// =============================================================================

LM2_API double ease_bounce_out_f64(double t) {
  const double n1 = 7.5625;
  const double d1 = 2.75;

  if (t < lm2_div_f64(1.0, d1)) {
    return lm2_mul_f64(lm2_mul_f64(n1, t), t);
  } else if (t < lm2_div_f64(2.0, d1)) {
    t = lm2_sub_f64(t, lm2_div_f64(1.5, d1));
    return lm2_add_f64(lm2_mul_f64(lm2_mul_f64(n1, t), t), 0.75);
  } else if (t < lm2_div_f64(2.5, d1)) {
    t = lm2_sub_f64(t, lm2_div_f64(2.25, d1));
    return lm2_add_f64(lm2_mul_f64(lm2_mul_f64(n1, t), t), 0.9375);
  } else {
    t = lm2_sub_f64(t, lm2_div_f64(2.625, d1));
    return lm2_add_f64(lm2_mul_f64(lm2_mul_f64(n1, t), t), 0.984375);
  }
}

LM2_API double ease_bounce_in_f64(double t) {
  return lm2_sub_f64(1.0, ease_bounce_out_f64(lm2_sub_f64(1.0, t)));
}

LM2_API double ease_bounce_in_out_f64(double t) {
  return t < 0.5
             ? lm2_div_f64(lm2_sub_f64(1.0, ease_bounce_out_f64(lm2_sub_f64(1.0, lm2_mul_f64(2.0, t)))), 2.0)
             : lm2_div_f64(lm2_add_f64(1.0, ease_bounce_out_f64(lm2_sub_f64(lm2_mul_f64(2.0, t), 1.0))), 2.0);
}

LM2_API float ease_bounce_out_f32(float t) {
  const float n1 = 7.5625f;
  const float d1 = 2.75f;

  if (t < lm2_div_f32(1.0f, d1)) {
    return lm2_mul_f32(lm2_mul_f32(n1, t), t);
  } else if (t < lm2_div_f32(2.0f, d1)) {
    t = lm2_sub_f32(t, lm2_div_f32(1.5f, d1));
    return lm2_add_f32(lm2_mul_f32(lm2_mul_f32(n1, t), t), 0.75f);
  } else if (t < lm2_div_f32(2.5f, d1)) {
    t = lm2_sub_f32(t, lm2_div_f32(2.25f, d1));
    return lm2_add_f32(lm2_mul_f32(lm2_mul_f32(n1, t), t), 0.9375f);
  } else {
    t = lm2_sub_f32(t, lm2_div_f32(2.625f, d1));
    return lm2_add_f32(lm2_mul_f32(lm2_mul_f32(n1, t), t), 0.984375f);
  }
}

LM2_API float ease_bounce_in_f32(float t) {
  return lm2_sub_f32(1.0f, ease_bounce_out_f32(lm2_sub_f32(1.0f, t)));
}

LM2_API float ease_bounce_in_out_f32(float t) {
  return t < 0.5f
             ? lm2_div_f32(lm2_sub_f32(1.0f, ease_bounce_out_f32(lm2_sub_f32(1.0f, lm2_mul_f32(2.0f, t)))), 2.0f)
             : lm2_div_f32(lm2_add_f32(1.0f, ease_bounce_out_f32(lm2_sub_f32(lm2_mul_f32(2.0f, t), 1.0f))), 2.0f);
}

// =============================================================================
// Helper: enum to string
// =============================================================================

LM2_API const char* lm2_easing_to_string(easing easing) {
  switch (easing) {
    case EASING_LINEAR:         return "linear";
    case EASING_SIN_IN:         return "sin_in";
    case EASING_SIN_OUT:        return "sin_out";
    case EASING_SIN_IN_OUT:     return "sin_in_out";
    case EASING_CUB_IN:         return "cubic_in";
    case EASING_CUB_OUT:        return "cubic_out";
    case EASING_CUB_IN_OUT:     return "cubic_in_out";
    case EASING_QUINT_IN:       return "quint_in";
    case EASING_QUINT_OUT:      return "quint_out";
    case EASING_QUINT_IN_OUT:   return "quint_in_out";
    case EASING_CIRC_IN:        return "circ_in";
    case EASING_CIRC_OUT:       return "circ_out";
    case EASING_CIRC_IN_OUT:    return "circ_in_out";
    case EASING_ELASTIC_IN:     return "elastic_in";
    case EASING_ELASTIC_OUT:    return "elastic_out";
    case EASING_ELASTIC_IN_OUT: return "elastic_in_out";
    case EASING_QUAD_IN:        return "quad_in";
    case EASING_QUAD_OUT:       return "quad_out";
    case EASING_QUAD_IN_OUT:    return "quad_in_out";
    case EASING_QUART_IN:       return "quart_in";
    case EASING_QUART_OUT:      return "quart_out";
    case EASING_QUART_IN_OUT:   return "quart_in_out";
    case EASING_EXP_IN:         return "exp_in";
    case EASING_EXP_OUT:        return "exp_out";
    case EASING_EXP_IN_OUT:     return "exp_in_out";
    case EASING_BACK_IN:        return "back_in";
    case EASING_BACK_OUT:       return "back_out";
    case EASING_BACK_IN_OUT:    return "back_in_out";
    case EASING_BOUNCE_IN:      return "bounce_in";
    case EASING_BOUNCE_OUT:     return "bounce_out";
    case EASING_BOUNCE_IN_OUT:  return "bounce_in_out";
    case EASING_MAX:            return "unknown";
    default:                    return "unknown";
  }
}

// =============================================================================
// Generalized easing functions
// =============================================================================

LM2_API double lm2_ease_f64(easing easing, double t) {
  switch (easing) {
    case EASING_LINEAR:         return ease_linear_f64(t);
    case EASING_SIN_IN:         return ease_sin_in_f64(t);
    case EASING_SIN_OUT:        return ease_sin_out_f64(t);
    case EASING_SIN_IN_OUT:     return ease_sin_in_out_f64(t);
    case EASING_CUB_IN:         return ease_cubic_in_f64(t);
    case EASING_CUB_OUT:        return ease_cubic_out_f64(t);
    case EASING_CUB_IN_OUT:     return ease_cubic_in_out_f64(t);
    case EASING_QUINT_IN:       return ease_quint_in_f64(t);
    case EASING_QUINT_OUT:      return ease_quint_out_f64(t);
    case EASING_QUINT_IN_OUT:   return ease_quint_in_out_f64(t);
    case EASING_CIRC_IN:        return ease_circ_in_f64(t);
    case EASING_CIRC_OUT:       return ease_circ_out_f64(t);
    case EASING_CIRC_IN_OUT:    return ease_circ_in_out_f64(t);
    case EASING_ELASTIC_IN:     return ease_elastic_in_f64(t);
    case EASING_ELASTIC_OUT:    return ease_elastic_out_f64(t);
    case EASING_ELASTIC_IN_OUT: return ease_elastic_in_out_f64(t);
    case EASING_QUAD_IN:        return ease_quad_in_f64(t);
    case EASING_QUAD_OUT:       return ease_quad_out_f64(t);
    case EASING_QUAD_IN_OUT:    return ease_quad_in_out_f64(t);
    case EASING_QUART_IN:       return ease_quart_in_f64(t);
    case EASING_QUART_OUT:      return ease_quart_out_f64(t);
    case EASING_QUART_IN_OUT:   return ease_quart_in_out_f64(t);
    case EASING_EXP_IN:         return ease_exp_in_f64(t);
    case EASING_EXP_OUT:        return ease_exp_out_f64(t);
    case EASING_EXP_IN_OUT:     return ease_exp_in_out_f64(t);
    case EASING_BACK_IN:        return ease_back_in_f64(t);
    case EASING_BACK_OUT:       return ease_back_out_f64(t);
    case EASING_BACK_IN_OUT:    return ease_back_in_out_f64(t);
    case EASING_BOUNCE_IN:      return ease_bounce_in_f64(t);
    case EASING_BOUNCE_OUT:     return ease_bounce_out_f64(t);
    case EASING_BOUNCE_IN_OUT:  return ease_bounce_in_out_f64(t);
    case EASING_MAX:
    default:                    return t;
  }
}

LM2_API float lm2_ease_f32(easing easing, float t) {
  switch (easing) {
    case EASING_LINEAR:         return ease_linear_f32(t);
    case EASING_SIN_IN:         return ease_sin_in_f32(t);
    case EASING_SIN_OUT:        return ease_sin_out_f32(t);
    case EASING_SIN_IN_OUT:     return ease_sin_in_out_f32(t);
    case EASING_CUB_IN:         return ease_cubic_in_f32(t);
    case EASING_CUB_OUT:        return ease_cubic_out_f32(t);
    case EASING_CUB_IN_OUT:     return ease_cubic_in_out_f32(t);
    case EASING_QUINT_IN:       return ease_quint_in_f32(t);
    case EASING_QUINT_OUT:      return ease_quint_out_f32(t);
    case EASING_QUINT_IN_OUT:   return ease_quint_in_out_f32(t);
    case EASING_CIRC_IN:        return ease_circ_in_f32(t);
    case EASING_CIRC_OUT:       return ease_circ_out_f32(t);
    case EASING_CIRC_IN_OUT:    return ease_circ_in_out_f32(t);
    case EASING_ELASTIC_IN:     return ease_elastic_in_f32(t);
    case EASING_ELASTIC_OUT:    return ease_elastic_out_f32(t);
    case EASING_ELASTIC_IN_OUT: return ease_elastic_in_out_f32(t);
    case EASING_QUAD_IN:        return ease_quad_in_f32(t);
    case EASING_QUAD_OUT:       return ease_quad_out_f32(t);
    case EASING_QUAD_IN_OUT:    return ease_quad_in_out_f32(t);
    case EASING_QUART_IN:       return ease_quart_in_f32(t);
    case EASING_QUART_OUT:      return ease_quart_out_f32(t);
    case EASING_QUART_IN_OUT:   return ease_quart_in_out_f32(t);
    case EASING_EXP_IN:         return ease_exp_in_f32(t);
    case EASING_EXP_OUT:        return ease_exp_out_f32(t);
    case EASING_EXP_IN_OUT:     return ease_exp_in_out_f32(t);
    case EASING_BACK_IN:        return ease_back_in_f32(t);
    case EASING_BACK_OUT:       return ease_back_out_f32(t);
    case EASING_BACK_IN_OUT:    return ease_back_in_out_f32(t);
    case EASING_BOUNCE_IN:      return ease_bounce_in_f32(t);
    case EASING_BOUNCE_OUT:     return ease_bounce_out_f32(t);
    case EASING_BOUNCE_IN_OUT:  return ease_bounce_in_out_f32(t);
    case EASING_MAX:
    default:                    return t;
  }
}
