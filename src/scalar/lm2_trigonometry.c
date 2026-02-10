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

#include <lm2/scalar/lm2_trigonometry.h>
#include <lm2/lm2_constants.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <math.h>

// =============================================================================
// Cosine Functions
// =============================================================================

LM2_API double lm2_cos_f64(double angle_rad) {
  LM2_ASSERT(isfinite(angle_rad));
  return cos(angle_rad);
}

LM2_API float lm2_cos_f32(float angle_rad) {
  LM2_ASSERT(isfinite(angle_rad));
  return cosf(angle_rad);
}

// =============================================================================
// Sine Functions
// =============================================================================

LM2_API double lm2_sin_f64(double angle_rad) {
  LM2_ASSERT(isfinite(angle_rad));
  return sin(angle_rad);
}

LM2_API float lm2_sin_f32(float angle_rad) {
  LM2_ASSERT(isfinite(angle_rad));
  return sinf(angle_rad);
}

// =============================================================================
// Tangent Functions
// =============================================================================

LM2_API double lm2_tan_f64(double angle_rad) {
  LM2_ASSERT(isfinite(angle_rad));
  return tan(angle_rad);
}

LM2_API float lm2_tan_f32(float angle_rad) {
  LM2_ASSERT(isfinite(angle_rad));
  return tanf(angle_rad);
}

// =============================================================================
// Arc Cosine Functions
// =============================================================================

LM2_API double lm2_acos_f64(double value) {
  LM2_ASSERT(isfinite(value) && value >= -1.0 && value <= 1.0);
  return acos(value);
}

LM2_API float lm2_acos_f32(float value) {
  LM2_ASSERT(isfinite(value) && value >= -1.0f && value <= 1.0f);
  return acosf(value);
}

// =============================================================================
// Arc Sine Functions
// =============================================================================

LM2_API double lm2_asin_f64(double value) {
  LM2_ASSERT(isfinite(value) && value >= -1.0 && value <= 1.0);
  return asin(value);
}

LM2_API float lm2_asin_f32(float value) {
  LM2_ASSERT(isfinite(value) && value >= -1.0f && value <= 1.0f);
  return asinf(value);
}

// =============================================================================
// Arc Tangent Functions
// =============================================================================

LM2_API double lm2_atan_f64(double value) {
  LM2_ASSERT(isfinite(value));
  return atan(value);
}

LM2_API float lm2_atan_f32(float value) {
  LM2_ASSERT(isfinite(value));
  return atanf(value);
}

// =============================================================================
// Arc Tangent 2 Functions
// =============================================================================

LM2_API double lm2_atan2_f64(double y, double x) {
  LM2_ASSERT(isfinite(y));
  LM2_ASSERT(isfinite(x));
  return atan2(y, x);
}

LM2_API float lm2_atan2_f32(float y, float x) {
  LM2_ASSERT(isfinite(y));
  LM2_ASSERT(isfinite(x));
  return atan2f(y, x);
}

// =============================================================================
// Degrees to Radians Conversion
// =============================================================================

LM2_API double lm2_deg_to_rad_f64(double degrees) {
  LM2_ASSERT(isfinite(degrees));
  return lm2_mul_f64(degrees, LM2_DEG_TO_RAD_F64);
}

LM2_API float lm2_deg_to_rad_f32(float degrees) {
  LM2_ASSERT(isfinite(degrees));
  return lm2_mul_f32(degrees, LM2_DEG_TO_RAD_F32);
}

// =============================================================================
// Radians to Degrees Conversion
// =============================================================================

LM2_API double lm2_rad_to_deg_f64(double radians) {
  LM2_ASSERT(isfinite(radians));
  return lm2_mul_f64(radians, LM2_RAD_TO_DEG_F64);
}

LM2_API float lm2_rad_to_deg_f32(float radians) {
  LM2_ASSERT(isfinite(radians));
  return lm2_mul_f32(radians, LM2_RAD_TO_DEG_F32);
}

// =============================================================================
// Wrap Angle to [-PI, PI] (Radians)
// =============================================================================

LM2_API double lm2_wrap_rad_f64(double angle_rad) {
  LM2_ASSERT(isfinite(angle_rad));
  double wrapped = lm2_mod_f64(lm2_add_f64(angle_rad, LM2_PI_F64), LM2_2PI_F64);
  if (wrapped < 0.0) {
    wrapped = lm2_add_f64(wrapped, LM2_2PI_F64);
  }
  return lm2_sub_f64(wrapped, LM2_PI_F64);
}

LM2_API float lm2_wrap_rad_f32(float angle_rad) {
  LM2_ASSERT(isfinite(angle_rad));
  float wrapped = lm2_mod_f32(lm2_add_f32(angle_rad, LM2_PI_F32), LM2_2PI_F32);
  if (wrapped < 0.0f) {
    wrapped = lm2_add_f32(wrapped, LM2_2PI_F32);
  }
  return lm2_sub_f32(wrapped, LM2_PI_F32);
}

// =============================================================================
// Shortest Angular Distance (Radians)
// =============================================================================

LM2_API double lm2_shortest_rad_f64(double from_angle_rad, double to_angle_rad) {
  LM2_ASSERT(isfinite(from_angle_rad));
  LM2_ASSERT(isfinite(to_angle_rad));
  double diff = lm2_sub_f64(to_angle_rad, from_angle_rad);
  return lm2_wrap_rad_f64(diff);
}

LM2_API float lm2_shortest_rad_f32(float from_angle_rad, float to_angle_rad) {
  LM2_ASSERT(isfinite(from_angle_rad));
  LM2_ASSERT(isfinite(to_angle_rad));
  float diff = lm2_sub_f32(to_angle_rad, from_angle_rad);
  return lm2_wrap_rad_f32(diff);
}

// =============================================================================
// Lerp for Angles (Radians)
// =============================================================================

LM2_API double lm2_lerp_rad_f64(double a_rad, double t, double b_rad) {
  LM2_ASSERT(isfinite(a_rad));
  LM2_ASSERT(isfinite(t));
  LM2_ASSERT(isfinite(b_rad));
  double shortest = lm2_shortest_rad_f64(a_rad, b_rad);
  return lm2_add_f64(a_rad, lm2_mul_f64(t, shortest));
}

LM2_API float lm2_lerp_rad_f32(float a_rad, float t, float b_rad) {
  LM2_ASSERT(isfinite(a_rad));
  LM2_ASSERT(isfinite(t));
  LM2_ASSERT(isfinite(b_rad));
  float shortest = lm2_shortest_rad_f32(a_rad, b_rad);
  return lm2_add_f32(a_rad, lm2_mul_f32(t, shortest));
}

// =============================================================================
// Wrap Angle to [-180, 180] (Degrees)
// =============================================================================

LM2_API double lm2_wrap_deg_f64(double angle_deg) {
  LM2_ASSERT(isfinite(angle_deg));
  double wrapped = lm2_mod_f64(lm2_add_f64(angle_deg, 180.0), 360.0);
  if (wrapped < 0.0) {
    wrapped = lm2_add_f64(wrapped, 360.0);
  }
  return lm2_sub_f64(wrapped, 180.0);
}

LM2_API float lm2_wrap_deg_f32(float angle_deg) {
  LM2_ASSERT(isfinite(angle_deg));
  float wrapped = lm2_mod_f32(lm2_add_f32(angle_deg, 180.0f), 360.0f);
  if (wrapped < 0.0f) {
    wrapped = lm2_add_f32(wrapped, 360.0f);
  }
  return lm2_sub_f32(wrapped, 180.0f);
}

// =============================================================================
// Shortest Angular Distance (Degrees)
// =============================================================================

LM2_API double lm2_shortest_deg_f64(double from_angle_deg, double to_angle_deg) {
  LM2_ASSERT(isfinite(from_angle_deg));
  LM2_ASSERT(isfinite(to_angle_deg));
  double diff = lm2_sub_f64(to_angle_deg, from_angle_deg);
  return lm2_wrap_deg_f64(diff);
}

LM2_API float lm2_shortest_deg_f32(float from_angle_deg, float to_angle_deg) {
  LM2_ASSERT(isfinite(from_angle_deg));
  LM2_ASSERT(isfinite(to_angle_deg));
  float diff = lm2_sub_f32(to_angle_deg, from_angle_deg);
  return lm2_wrap_deg_f32(diff);
}

// =============================================================================
// Lerp for Angles (Degrees)
// =============================================================================

LM2_API double lm2_lerp_deg_f64(double a_deg, double t, double b_deg) {
  LM2_ASSERT(isfinite(a_deg));
  LM2_ASSERT(isfinite(t));
  LM2_ASSERT(isfinite(b_deg));
  double shortest = lm2_shortest_deg_f64(a_deg, b_deg);
  return lm2_add_f64(a_deg, lm2_mul_f64(t, shortest));
}

LM2_API float lm2_lerp_deg_f32(float a_deg, float t, float b_deg) {
  LM2_ASSERT(isfinite(a_deg));
  LM2_ASSERT(isfinite(t));
  LM2_ASSERT(isfinite(b_deg));
  float shortest = lm2_shortest_deg_f32(a_deg, b_deg);
  return lm2_add_f32(a_deg, lm2_mul_f32(t, shortest));
}