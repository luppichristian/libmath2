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

#include <libmath2/libmath2_easings.h>
#include <libmath2/libmath2_constants.h>
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
  return 1.0 - cos(t * LM2_HPI_F64);
}

LM2_API double ease_sin_out_f64(double t) {
  return sin(t * LM2_HPI_F64);
}

LM2_API double ease_sin_in_out_f64(double t) {
  return -(cos(LM2_PI_F64 * t) - 1.0) / 2.0;
}

LM2_API float ease_sin_in_f32(float t) {
  return 1.0f - cosf(t * LM2_HPI_F32);
}

LM2_API float ease_sin_out_f32(float t) {
  return sinf(t * LM2_HPI_F32);
}

LM2_API float ease_sin_in_out_f32(float t) {
  return -(cosf(LM2_PI_F32 * t) - 1.0f) / 2.0f;
}

// =============================================================================
// Quad
// =============================================================================

LM2_API double ease_quad_in_f64(double t) {
  return t * t;
}

LM2_API double ease_quad_out_f64(double t) {
  return 1.0 - (1.0 - t) * (1.0 - t);
}

LM2_API double ease_quad_in_out_f64(double t) {
  return t < 0.5 ? 2.0 * t * t : 1.0 - pow(-2.0 * t + 2.0, 2.0) / 2.0;
}

LM2_API float ease_quad_in_f32(float t) {
  return t * t;
}

LM2_API float ease_quad_out_f32(float t) {
  return 1.0f - (1.0f - t) * (1.0f - t);
}

LM2_API float ease_quad_in_out_f32(float t) {
  return t < 0.5f ? 2.0f * t * t : 1.0f - powf(-2.0f * t + 2.0f, 2.0f) / 2.0f;
}

// =============================================================================
// Cubic
// =============================================================================

LM2_API double ease_cubic_in_f64(double t) {
  return t * t * t;
}

LM2_API double ease_cubic_out_f64(double t) {
  double u = 1.0 - t;
  return 1.0 - u * u * u;
}

LM2_API double ease_cubic_in_out_f64(double t) {
  return t < 0.5 ? 4.0 * t * t * t : 1.0 - pow(-2.0 * t + 2.0, 3.0) / 2.0;
}

LM2_API float ease_cubic_in_f32(float t) {
  return t * t * t;
}

LM2_API float ease_cubic_out_f32(float t) {
  float u = 1.0f - t;
  return 1.0f - u * u * u;
}

LM2_API float ease_cubic_in_out_f32(float t) {
  return t < 0.5f ? 4.0f * t * t * t : 1.0f - powf(-2.0f * t + 2.0f, 3.0f) / 2.0f;
}

// =============================================================================
// Quart
// =============================================================================

LM2_API double ease_quart_in_f64(double t) {
  return t * t * t * t;
}

LM2_API double ease_quart_out_f64(double t) {
  double u = 1.0 - t;
  return 1.0 - u * u * u * u;
}

LM2_API double ease_quart_in_out_f64(double t) {
  return t < 0.5 ? 8.0 * t * t * t * t : 1.0 - pow(-2.0 * t + 2.0, 4.0) / 2.0;
}

LM2_API float ease_quart_in_f32(float t) {
  return t * t * t * t;
}

LM2_API float ease_quart_out_f32(float t) {
  float u = 1.0f - t;
  return 1.0f - u * u * u * u;
}

LM2_API float ease_quart_in_out_f32(float t) {
  return t < 0.5f ? 8.0f * t * t * t * t : 1.0f - powf(-2.0f * t + 2.0f, 4.0f) / 2.0f;
}

// =============================================================================
// Quint
// =============================================================================

LM2_API double ease_quint_in_f64(double t) {
  return t * t * t * t * t;
}

LM2_API double ease_quint_out_f64(double t) {
  double u = 1.0 - t;
  return 1.0 - u * u * u * u * u;
}

LM2_API double ease_quint_in_out_f64(double t) {
  return t < 0.5 ? 16.0 * t * t * t * t * t : 1.0 - pow(-2.0 * t + 2.0, 5.0) / 2.0;
}

LM2_API float ease_quint_in_f32(float t) {
  return t * t * t * t * t;
}

LM2_API float ease_quint_out_f32(float t) {
  float u = 1.0f - t;
  return 1.0f - u * u * u * u * u;
}

LM2_API float ease_quint_in_out_f32(float t) {
  return t < 0.5f ? 16.0f * t * t * t * t * t : 1.0f - powf(-2.0f * t + 2.0f, 5.0f) / 2.0f;
}

// =============================================================================
// Exp
// =============================================================================

LM2_API double ease_exp_in_f64(double t) {
  return t == 0.0 ? 0.0 : pow(2.0, 10.0 * t - 10.0);
}

LM2_API double ease_exp_out_f64(double t) {
  return t == 1.0 ? 1.0 : 1.0 - pow(2.0, -10.0 * t);
}

LM2_API double ease_exp_in_out_f64(double t) {
  if (t == 0.0) return 0.0;
  if (t == 1.0) return 1.0;
  return t < 0.5 ? pow(2.0, 20.0 * t - 10.0) / 2.0 : (2.0 - pow(2.0, -20.0 * t + 10.0)) / 2.0;
}

LM2_API float ease_exp_in_f32(float t) {
  return t == 0.0f ? 0.0f : powf(2.0f, 10.0f * t - 10.0f);
}

LM2_API float ease_exp_out_f32(float t) {
  return t == 1.0f ? 1.0f : 1.0f - powf(2.0f, -10.0f * t);
}

LM2_API float ease_exp_in_out_f32(float t) {
  if (t == 0.0f) return 0.0f;
  if (t == 1.0f) return 1.0f;
  return t < 0.5f ? powf(2.0f, 20.0f * t - 10.0f) / 2.0f : (2.0f - powf(2.0f, -20.0f * t + 10.0f)) / 2.0f;
}

// =============================================================================
// Circ
// =============================================================================

LM2_API double ease_circ_in_f64(double t) {
  return 1.0 - sqrt(1.0 - t * t);
}

LM2_API double ease_circ_out_f64(double t) {
  return sqrt(1.0 - (t - 1.0) * (t - 1.0));
}

LM2_API double ease_circ_in_out_f64(double t) {
  return t < 0.5
             ? (1.0 - sqrt(1.0 - pow(2.0 * t, 2.0))) / 2.0
             : (sqrt(1.0 - pow(-2.0 * t + 2.0, 2.0)) + 1.0) / 2.0;
}

LM2_API float ease_circ_in_f32(float t) {
  return 1.0f - sqrtf(1.0f - t * t);
}

LM2_API float ease_circ_out_f32(float t) {
  return sqrtf(1.0f - (t - 1.0f) * (t - 1.0f));
}

LM2_API float ease_circ_in_out_f32(float t) {
  return t < 0.5f
             ? (1.0f - sqrtf(1.0f - powf(2.0f * t, 2.0f))) / 2.0f
             : (sqrtf(1.0f - powf(-2.0f * t + 2.0f, 2.0f)) + 1.0f) / 2.0f;
}

// =============================================================================
// Back
// =============================================================================

LM2_API double ease_back_in_f64(double t) {
  const double c1 = 1.70158;
  const double c3 = c1 + 1.0;
  return c3 * t * t * t - c1 * t * t;
}

LM2_API double ease_back_out_f64(double t) {
  const double c1 = 1.70158;
  const double c3 = c1 + 1.0;
  double u = t - 1.0;
  return 1.0 + c3 * u * u * u + c1 * u * u;
}

LM2_API double ease_back_in_out_f64(double t) {
  const double c1 = 1.70158;
  const double c2 = c1 * 1.525;

  return t < 0.5
             ? (pow(2.0 * t, 2.0) * ((c2 + 1.0) * 2.0 * t - c2)) / 2.0
             : (pow(2.0 * t - 2.0, 2.0) * ((c2 + 1.0) * (t * 2.0 - 2.0) + c2) + 2.0) / 2.0;
}

LM2_API float ease_back_in_f32(float t) {
  const float c1 = 1.70158f;
  const float c3 = c1 + 1.0f;
  return c3 * t * t * t - c1 * t * t;
}

LM2_API float ease_back_out_f32(float t) {
  const float c1 = 1.70158f;
  const float c3 = c1 + 1.0f;
  float u = t - 1.0f;
  return 1.0f + c3 * u * u * u + c1 * u * u;
}

LM2_API float ease_back_in_out_f32(float t) {
  const float c1 = 1.70158f;
  const float c2 = c1 * 1.525f;

  return t < 0.5f
             ? (powf(2.0f * t, 2.0f) * ((c2 + 1.0f) * 2.0f * t - c2)) / 2.0f
             : (powf(2.0f * t - 2.0f, 2.0f) * ((c2 + 1.0f) * (t * 2.0f - 2.0f) + c2) + 2.0f) / 2.0f;
}

// =============================================================================
// Elastic
// =============================================================================

LM2_API double ease_elastic_in_f64(double t) {
  const double c4 = (2.0 * LM2_PI_F64) / 3.0;

  if (t == 0.0) return 0.0;
  if (t == 1.0) return 1.0;
  return -pow(2.0, 10.0 * t - 10.0) * sin((t * 10.0 - 10.75) * c4);
}

LM2_API double ease_elastic_out_f64(double t) {
  const double c4 = (2.0 * LM2_PI_F64) / 3.0;

  if (t == 0.0) return 0.0;
  if (t == 1.0) return 1.0;
  return pow(2.0, -10.0 * t) * sin((t * 10.0 - 0.75) * c4) + 1.0;
}

LM2_API double ease_elastic_in_out_f64(double t) {
  const double c5 = (2.0 * LM2_PI_F64) / 4.5;

  if (t == 0.0) return 0.0;
  if (t == 1.0) return 1.0;

  return t < 0.5
             ? -(pow(2.0, 20.0 * t - 10.0) * sin((20.0 * t - 11.125) * c5)) / 2.0
             : (pow(2.0, -20.0 * t + 10.0) * sin((20.0 * t - 11.125) * c5)) / 2.0 + 1.0;
}

LM2_API float ease_elastic_in_f32(float t) {
  const float c4 = (2.0f * LM2_PI_F32) / 3.0f;

  if (t == 0.0f) return 0.0f;
  if (t == 1.0f) return 1.0f;
  return -powf(2.0f, 10.0f * t - 10.0f) * sinf((t * 10.0f - 10.75f) * c4);
}

LM2_API float ease_elastic_out_f32(float t) {
  const float c4 = (2.0f * LM2_PI_F32) / 3.0f;

  if (t == 0.0f) return 0.0f;
  if (t == 1.0f) return 1.0f;
  return powf(2.0f, -10.0f * t) * sinf((t * 10.0f - 0.75f) * c4) + 1.0f;
}

LM2_API float ease_elastic_in_out_f32(float t) {
  const float c5 = (2.0f * LM2_PI_F32) / 4.5f;

  if (t == 0.0f) return 0.0f;
  if (t == 1.0f) return 1.0f;

  return t < 0.5f
             ? -(powf(2.0f, 20.0f * t - 10.0f) * sinf((20.0f * t - 11.125f) * c5)) / 2.0f
             : (powf(2.0f, -20.0f * t + 10.0f) * sinf((20.0f * t - 11.125f) * c5)) / 2.0f + 1.0f;
}

// =============================================================================
// Bounce
// =============================================================================

LM2_API double ease_bounce_out_f64(double t) {
  const double n1 = 7.5625;
  const double d1 = 2.75;

  if (t < 1.0 / d1) {
    return n1 * t * t;
  } else if (t < 2.0 / d1) {
    t -= 1.5 / d1;
    return n1 * t * t + 0.75;
  } else if (t < 2.5 / d1) {
    t -= 2.25 / d1;
    return n1 * t * t + 0.9375;
  } else {
    t -= 2.625 / d1;
    return n1 * t * t + 0.984375;
  }
}

LM2_API double ease_bounce_in_f64(double t) {
  return 1.0 - ease_bounce_out_f64(1.0 - t);
}

LM2_API double ease_bounce_in_out_f64(double t) {
  return t < 0.5
             ? (1.0 - ease_bounce_out_f64(1.0 - 2.0 * t)) / 2.0
             : (1.0 + ease_bounce_out_f64(2.0 * t - 1.0)) / 2.0;
}

LM2_API float ease_bounce_out_f32(float t) {
  const float n1 = 7.5625f;
  const float d1 = 2.75f;

  if (t < 1.0f / d1) {
    return n1 * t * t;
  } else if (t < 2.0f / d1) {
    t -= 1.5f / d1;
    return n1 * t * t + 0.75f;
  } else if (t < 2.5f / d1) {
    t -= 2.25f / d1;
    return n1 * t * t + 0.9375f;
  } else {
    t -= 2.625f / d1;
    return n1 * t * t + 0.984375f;
  }
}

LM2_API float ease_bounce_in_f32(float t) {
  return 1.0f - ease_bounce_out_f32(1.0f - t);
}

LM2_API float ease_bounce_in_out_f32(float t) {
  return t < 0.5f
             ? (1.0f - ease_bounce_out_f32(1.0f - 2.0f * t)) / 2.0f
             : (1.0f + ease_bounce_out_f32(2.0f * t - 1.0f)) / 2.0f;
}

// =============================================================================
// Helper: enum to string
// =============================================================================

LM2_API const char* lm2_easing_to_string(easing_t easing) {
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

LM2_API double lm2_ease_f64(easing_t easing, double t) {
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

LM2_API float lm2_ease_f32(easing_t easing, float t) {
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
