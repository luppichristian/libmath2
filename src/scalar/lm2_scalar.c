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

#include <lm2/scalar/lm2_scalar.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <math.h>

// =============================================================================
// Floor Functions
// =============================================================================

LM2_API double lm2_floor_f64(double a) {
  LM2_ASSERT(isfinite(a));
  return floor(a);
}

LM2_API float lm2_floor_f32(float a) {
  LM2_ASSERT(isfinite(a));
  return floorf(a);
}

LM2_API double lm2_floor_multiple_f64(double a, double multiple) {
  LM2_ASSERT(isfinite(a));
  LM2_ASSERT(isfinite(multiple) && multiple != 0.0);
  return lm2_mul_f64(floor(lm2_div_f64(a, multiple)), multiple);
}

LM2_API float lm2_floor_multiple_f32(float a, float multiple) {
  LM2_ASSERT(isfinite(a));
  LM2_ASSERT(isfinite(multiple) && multiple != 0.0f);
  return lm2_mul_f32(floorf(lm2_div_f32(a, multiple)), multiple);
}

// =============================================================================
// Ceil Functions
// =============================================================================

LM2_API double lm2_ceil_f64(double a) {
  LM2_ASSERT(isfinite(a));
  return ceil(a);
}

LM2_API float lm2_ceil_f32(float a) {
  LM2_ASSERT(isfinite(a));
  return ceilf(a);
}

LM2_API double lm2_ceil_multiple_f64(double a, double multiple) {
  LM2_ASSERT(isfinite(a));
  LM2_ASSERT(isfinite(multiple) && multiple != 0.0);
  return lm2_mul_f64(ceil(lm2_div_f64(a, multiple)), multiple);
}

LM2_API float lm2_ceil_multiple_f32(float a, float multiple) {
  LM2_ASSERT(isfinite(a));
  LM2_ASSERT(isfinite(multiple) && multiple != 0.0f);
  return lm2_mul_f32(ceilf(lm2_div_f32(a, multiple)), multiple);
}

// =============================================================================
// Round Functions
// =============================================================================

LM2_API double lm2_round_f64(double a) {
  LM2_ASSERT(isfinite(a));
  return round(a);
}

LM2_API float lm2_round_f32(float a) {
  LM2_ASSERT(isfinite(a));
  return roundf(a);
}

LM2_API double lm2_round_multiple_f64(double a, double multiple) {
  LM2_ASSERT(isfinite(a));
  LM2_ASSERT(isfinite(multiple) && multiple != 0.0);
  return lm2_mul_f64(round(lm2_div_f64(a, multiple)), multiple);
}

LM2_API float lm2_round_multiple_f32(float a, float multiple) {
  LM2_ASSERT(isfinite(a));
  LM2_ASSERT(isfinite(multiple) && multiple != 0.0f);
  return lm2_mul_f32(roundf(lm2_div_f32(a, multiple)), multiple);
}

// =============================================================================
// Truncate Functions
// =============================================================================

LM2_API double lm2_trunc_f64(double a) {
  LM2_ASSERT(isfinite(a));
  return trunc(a);
}

LM2_API float lm2_trunc_f32(float a) {
  LM2_ASSERT(isfinite(a));
  return truncf(a);
}

LM2_API double lm2_trunc_multiple_f64(double a, double multiple) {
  LM2_ASSERT(isfinite(a));
  LM2_ASSERT(isfinite(multiple) && multiple != 0.0);
  return lm2_mul_f64(trunc(lm2_div_f64(a, multiple)), multiple);
}

LM2_API float lm2_trunc_multiple_f32(float a, float multiple) {
  LM2_ASSERT(isfinite(a));
  LM2_ASSERT(isfinite(multiple) && multiple != 0.0f);
  return lm2_mul_f32(truncf(lm2_div_f32(a, multiple)), multiple);
}

// =============================================================================
// Abs Functions
// =============================================================================

LM2_API double lm2_abs_f64(double a) {
  LM2_ASSERT(isfinite(a));
  return fabs(a);
}

LM2_API float lm2_abs_f32(float a) {
  LM2_ASSERT(isfinite(a));
  return fabsf(a);
}

// =============================================================================
// Sign Functions (returns 1 or -1)
// =============================================================================

LM2_API double lm2_sign_f64(double a) {
  LM2_ASSERT(isfinite(a));
  return (a >= 0.0) ? 1.0 : -1.0;
}

LM2_API float lm2_sign_f32(float a) {
  LM2_ASSERT(isfinite(a));
  return (a >= 0.0f) ? 1.0f : -1.0f;
}

// =============================================================================
// Sign0 Functions (returns 1, -1, or 0)
// =============================================================================

LM2_API double lm2_sign0_f64(double a) {
  LM2_ASSERT(isfinite(a));
  if (a > 0.0) return 1.0;
  if (a < 0.0) return -1.0;
  return 0.0;
}

LM2_API float lm2_sign0_f32(float a) {
  LM2_ASSERT(isfinite(a));
  if (a > 0.0f) return 1.0f;
  if (a < 0.0f) return -1.0f;
  return 0.0f;
}

// =============================================================================
// Min Functions
// =============================================================================

LM2_API double lm2_min_f64(double a, double b) {
  LM2_ASSERT(isfinite(a));
  LM2_ASSERT(isfinite(b));
  return (a < b) ? a : b;
}

LM2_API float lm2_min_f32(float a, float b) {
  LM2_ASSERT(isfinite(a));
  LM2_ASSERT(isfinite(b));
  return (a < b) ? a : b;
}

LM2_API double lm2_min_abs_f64(double a, double b) {
  LM2_ASSERT(isfinite(a));
  LM2_ASSERT(isfinite(b));
  return (fabs(a) < fabs(b)) ? a : b;
}

LM2_API float lm2_min_abs_f32(float a, float b) {
  LM2_ASSERT(isfinite(a));
  LM2_ASSERT(isfinite(b));
  return (fabsf(a) < fabsf(b)) ? a : b;
}

// =============================================================================
// Max Functions
// =============================================================================

LM2_API double lm2_max_f64(double a, double b) {
  LM2_ASSERT(isfinite(a));
  LM2_ASSERT(isfinite(b));
  return (a > b) ? a : b;
}

LM2_API float lm2_max_f32(float a, float b) {
  LM2_ASSERT(isfinite(a));
  LM2_ASSERT(isfinite(b));
  return (a > b) ? a : b;
}

LM2_API double lm2_max_abs_f64(double a, double b) {
  LM2_ASSERT(isfinite(a));
  LM2_ASSERT(isfinite(b));
  return (fabs(a) > fabs(b)) ? a : b;
}

LM2_API float lm2_max_abs_f32(float a, float b) {
  LM2_ASSERT(isfinite(a));
  LM2_ASSERT(isfinite(b));
  return (fabsf(a) > fabsf(b)) ? a : b;
}

// =============================================================================
// Clamp Functions
// =============================================================================

LM2_API double lm2_clamp_f64(double min, double value, double max) {
  LM2_ASSERT(isfinite(min));
  LM2_ASSERT(isfinite(value));
  LM2_ASSERT(isfinite(max));
  LM2_ASSERT(min <= max);
  if (value < min) return min;
  if (value > max) return max;
  return value;
}

LM2_API float lm2_clamp_f32(float min, float value, float max) {
  LM2_ASSERT(isfinite(min));
  LM2_ASSERT(isfinite(value));
  LM2_ASSERT(isfinite(max));
  LM2_ASSERT(min <= max);
  if (value < min) return min;
  if (value > max) return max;
  return value;
}

// =============================================================================
// Saturate Functions (clamp to [0, 1])
// =============================================================================

LM2_API double lm2_saturate_f64(double value) {
  return lm2_clamp_f64(0.0, value, 1.0);
}

LM2_API float lm2_saturate_f32(float value) {
  return lm2_clamp_f32(0.0f, value, 1.0f);
}

// =============================================================================
// Lerp Functions (linear interpolation)
// =============================================================================

LM2_API double lm2_lerp_f64(double a, double t, double b) {
  LM2_ASSERT(isfinite(a));
  LM2_ASSERT(isfinite(t));
  LM2_ASSERT(isfinite(b));
  return lm2_add_f64(a, lm2_mul_f64(t, lm2_sub_f64(b, a)));
}

LM2_API float lm2_lerp_f32(float a, float t, float b) {
  LM2_ASSERT(isfinite(a));
  LM2_ASSERT(isfinite(t));
  LM2_ASSERT(isfinite(b));
  return lm2_add_f32(a, lm2_mul_f32(t, lm2_sub_f32(b, a)));
}

// =============================================================================
// Smoothstep Functions
// =============================================================================

LM2_API double lm2_smoothstep_f64(double edge0, double x, double edge1) {
  LM2_ASSERT(isfinite(edge0));
  LM2_ASSERT(isfinite(x));
  LM2_ASSERT(isfinite(edge1));
  LM2_ASSERT(edge0 != edge1);
  double t = lm2_clamp_f64(0.0, lm2_div_f64(lm2_sub_f64(x, edge0), lm2_sub_f64(edge1, edge0)), 1.0);
  return lm2_mul_f64(lm2_mul_f64(t, t), lm2_sub_f64(3.0, lm2_mul_f64(2.0, t)));
}

LM2_API float lm2_smoothstep_f32(float edge0, float x, float edge1) {
  LM2_ASSERT(isfinite(edge0));
  LM2_ASSERT(isfinite(x));
  LM2_ASSERT(isfinite(edge1));
  LM2_ASSERT(edge0 != edge1);
  float t = lm2_clamp_f32(0.0f, lm2_div_f32(lm2_sub_f32(x, edge0), lm2_sub_f32(edge1, edge0)), 1.0f);
  return lm2_mul_f32(lm2_mul_f32(t, t), lm2_sub_f32(3.0f, lm2_mul_f32(2.0f, t)));
}

// =============================================================================
// Alpha Functions (inverse lerp)
// =============================================================================

LM2_API double lm2_alpha_f64(double a, double value, double b) {
  LM2_ASSERT(isfinite(a));
  LM2_ASSERT(isfinite(value));
  LM2_ASSERT(isfinite(b));
  LM2_ASSERT(a != b);
  return lm2_div_f64(lm2_sub_f64(value, a), lm2_sub_f64(b, a));
}

LM2_API float lm2_alpha_f32(float a, float value, float b) {
  LM2_ASSERT(isfinite(a));
  LM2_ASSERT(isfinite(value));
  LM2_ASSERT(isfinite(b));
  LM2_ASSERT(a != b);
  return lm2_div_f32(lm2_sub_f32(value, a), lm2_sub_f32(b, a));
}

// =============================================================================
// Fract Functions (fractional part)
// =============================================================================

LM2_API double lm2_fract_f64(double a) {
  LM2_ASSERT(isfinite(a));
  return lm2_sub_f64(a, floor(a));
}

LM2_API float lm2_fract_f32(float a) {
  LM2_ASSERT(isfinite(a));
  return lm2_sub_f32(a, floorf(a));
}

// =============================================================================
// Modulo Functions
// =============================================================================

LM2_API double lm2_mod_f64(double a, double b) {
  LM2_ASSERT(isfinite(a));
  LM2_ASSERT(isfinite(b) && b != 0.0);
  return fmod(a, b);
}

LM2_API float lm2_mod_f32(float a, float b) {
  LM2_ASSERT(isfinite(a));
  LM2_ASSERT(isfinite(b) && b != 0.0f);
  return fmodf(a, b);
}

// =============================================================================
// Power Functions
// =============================================================================

LM2_API double lm2_pow_f64(double base, double exponent) {
  LM2_ASSERT(isfinite(base));
  LM2_ASSERT(isfinite(exponent));
  LM2_ASSERT(base >= 0.0 || exponent == floor(exponent));
  return pow(base, exponent);
}

LM2_API float lm2_pow_f32(float base, float exponent) {
  LM2_ASSERT(isfinite(base));
  LM2_ASSERT(isfinite(exponent));
  LM2_ASSERT(base >= 0.0f || exponent == floorf(exponent));
  return powf(base, exponent);
}

// =============================================================================
// Square Root Functions
// =============================================================================

LM2_API double lm2_sqrt_f64(double a) {
  LM2_ASSERT(isfinite(a) && a >= 0.0);
  return sqrt(a);
}

LM2_API float lm2_sqrt_f32(float a) {
  LM2_ASSERT(isfinite(a) && a >= 0.0f);
  return sqrtf(a);
}