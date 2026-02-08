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

#pragma once

#include "lm2/scalar/lm2_scalar.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// Cos
LM2_API double lm2_cos_f64(double angle_rad);
LM2_API float lm2_cos_f32(float angle_rad);

// Sin
LM2_API double lm2_sin_f64(double angle_rad);
LM2_API float lm2_sin_f32(float angle_rad);

// Tan
LM2_API double lm2_tan_f64(double angle_rad);
LM2_API float lm2_tan_f32(float angle_rad);

// Acos
LM2_API double lm2_acos_f64(double value);
LM2_API float lm2_acos_f32(float value);

// Asin
LM2_API double lm2_asin_f64(double value);
LM2_API float lm2_asin_f32(float value);

// Atan
LM2_API double lm2_atan_f64(double value);
LM2_API float lm2_atan_f32(float value);

// Atan2
LM2_API double lm2_atan2_f64(double y, double x);
LM2_API float lm2_atan2_f32(float y, float x);

// Helpers for radians/degrees conversion
LM2_API double lm2_deg_to_rad_f64(double degrees);
LM2_API float lm2_deg_to_rad_f32(float degrees);
LM2_API double lm2_rad_to_deg_f64(double radians);
LM2_API float lm2_rad_to_deg_f32(float radians);

// Angles (in radians)
LM2_API double lm2_wrap_rad_f64(double angle_rad);
LM2_API float lm2_wrap_rad_f32(float angle_rad);
LM2_API double lm2_shortest_rad_f64(double from_angle_rad, double to_angle_rad);
LM2_API float lm2_shortest_rad_f32(float from_angle_rad, float to_angle_rad);
LM2_API double lm2_lerp_rad_f64(double a_rad, double t, double b_rad);
LM2_API float lm2_lerp_rad_f32(float a_rad, float t, float b_rad);

// Angles (in degrees)
LM2_API double lm2_wrap_deg_f64(double angle_deg);
LM2_API float lm2_wrap_deg_f32(float angle_deg);
LM2_API double lm2_shortest_deg_f64(double from_angle_deg, double to_angle_deg);
LM2_API float lm2_shortest_deg_f32(float from_angle_deg, float to_angle_deg);
LM2_API double lm2_lerp_deg_f64(double a_deg, double t, double b_deg);
LM2_API float lm2_lerp_deg_f32(float a_deg, float t, float b_deg);

// #############################################################################
LM2_HEADER_END;
// #############################################################################