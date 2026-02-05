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

#include <libmath2/libmath2_scalar.h>
#include <math.h>

// =============================================================================
// Floor Functions
// =============================================================================

LM2_API double lm2_floor_f64(double a) {
  return floor(a);
}

LM2_API float lm2_floor_f32(float a) {
  return floorf(a);
}

LM2_API double lm2_floor_multiple_f64(double a, double multiple) {
  return floor(a / multiple) * multiple;
}

LM2_API float lm2_floor_multiple_f32(float a, float multiple) {
  return floorf(a / multiple) * multiple;
}

// =============================================================================
// Ceil Functions
// =============================================================================

LM2_API double lm2_ceil_f64(double a) {
  return ceil(a);
}

LM2_API float lm2_ceil_f32(float a) {
  return ceilf(a);
}

LM2_API double lm2_ceil_multiple_f64(double a, double multiple) {
  return ceil(a / multiple) * multiple;
}

LM2_API float lm2_ceil_multiple_f32(float a, float multiple) {
  return ceilf(a / multiple) * multiple;
}

// =============================================================================
// Round Functions
// =============================================================================

LM2_API double lm2_round_f64(double a) {
  return round(a);
}

LM2_API float lm2_round_f32(float a) {
  return roundf(a);
}

LM2_API double lm2_round_multiple_f64(double a, double multiple) {
  return round(a / multiple) * multiple;
}

LM2_API float lm2_round_multiple_f32(float a, float multiple) {
  return roundf(a / multiple) * multiple;
}

// =============================================================================
// Truncate Functions
// =============================================================================

LM2_API double lm2_trunc_f64(double a) {
  return trunc(a);
}

LM2_API float lm2_trunc_f32(float a) {
  return truncf(a);
}

LM2_API double lm2_trunc_multiple_f64(double a, double multiple) {
  return trunc(a / multiple) * multiple;
}

LM2_API float lm2_trunc_multiple_f32(float a, float multiple) {
  return truncf(a / multiple) * multiple;
}

// =============================================================================
// Abs Functions
// =============================================================================

LM2_API double lm2_abs_f64(double a) {
  return fabs(a);
}

LM2_API float lm2_abs_f32(float a) {
  return fabsf(a);
}

// =============================================================================
// Sign Functions (returns 1 or -1)
// =============================================================================

LM2_API double lm2_sign_f64(double a) {
  return (a >= 0.0) ? 1.0 : -1.0;
}

LM2_API float lm2_sign_f32(float a) {
  return (a >= 0.0f) ? 1.0f : -1.0f;
}

// =============================================================================
// Sign0 Functions (returns 1, -1, or 0)
// =============================================================================

LM2_API double lm2_sign0_f64(double a) {
  if (a > 0.0) return 1.0;
  if (a < 0.0) return -1.0;
  return 0.0;
}

LM2_API float lm2_sign0_f32(float a) {
  if (a > 0.0f) return 1.0f;
  if (a < 0.0f) return -1.0f;
  return 0.0f;
}

// =============================================================================
// Min Functions
// =============================================================================

LM2_API double lm2_min_f64(double a, double b) {
  return (a < b) ? a : b;
}

LM2_API float lm2_min_f32(float a, float b) {
  return (a < b) ? a : b;
}

LM2_API double lm2_min_abs_f64(double a, double b) {
  return (fabs(a) < fabs(b)) ? a : b;
}

LM2_API float lm2_min_abs_f32(float a, float b) {
  return (fabsf(a) < fabsf(b)) ? a : b;
}

// =============================================================================
// Max Functions
// =============================================================================

LM2_API double lm2_max_f64(double a, double b) {
  return (a > b) ? a : b;
}

LM2_API float lm2_max_f32(float a, float b) {
  return (a > b) ? a : b;
}

LM2_API double lm2_max_abs_f64(double a, double b) {
  return (fabs(a) > fabs(b)) ? a : b;
}

LM2_API float lm2_max_abs_f32(float a, float b) {
  return (fabsf(a) > fabsf(b)) ? a : b;
}

// =============================================================================
// Clamp Functions
// =============================================================================

LM2_API double lm2_clamp_f64(double min, double value, double max) {
  if (value < min) return min;
  if (value > max) return max;
  return value;
}

LM2_API float lm2_clamp_f32(float min, float value, float max) {
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
  return a + t * (b - a);
}

LM2_API float lm2_lerp_f32(float a, float t, float b) {
  return a + t * (b - a);
}

// =============================================================================
// Smoothstep Functions
// =============================================================================

LM2_API double lm2_smoothstep_f64(double edge0, double x, double edge1) {
  double t = lm2_clamp_f64(0.0, (x - edge0) / (edge1 - edge0), 1.0);
  return t * t * (3.0 - 2.0 * t);
}

LM2_API float lm2_smoothstep_f32(float edge0, float x, float edge1) {
  float t = lm2_clamp_f32(0.0f, (x - edge0) / (edge1 - edge0), 1.0f);
  return t * t * (3.0f - 2.0f * t);
}

// =============================================================================
// Alpha Functions (inverse lerp)
// =============================================================================

LM2_API double lm2_alpha_f64(double a, double value, double b) {
  return (value - a) / (b - a);
}

LM2_API float lm2_alpha_f32(float a, float value, float b) {
  return (value - a) / (b - a);
}

// =============================================================================
// Fract Functions (fractional part)
// =============================================================================

LM2_API double lm2_fract_f64(double a) {
  return a - floor(a);
}

LM2_API float lm2_fract_f32(float a) {
  return a - floorf(a);
}

// =============================================================================
// Modulo Functions
// =============================================================================

LM2_API double lm2_mod_f64(double a, double b) {
  return fmod(a, b);
}

LM2_API float lm2_mod_f32(float a, float b) {
  return fmodf(a, b);
}

// =============================================================================
// Normalize Functions (divide by sign)
// =============================================================================

LM2_API double lm2_norm_f64(double a) {
  return a / lm2_sign_f64(a);
}

LM2_API float lm2_norm_f32(float a) {
  return a / lm2_sign_f32(a);
}