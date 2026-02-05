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

#include "libmath2/libmath2_safe_ops.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// Floor
LM2_API double lm2_floor_f64(double a);
LM2_API float lm2_floor_f32(float a);
LM2_API double lm2_floor_multiple_f64(double a, double multiple);
LM2_API float lm2_floor_multiple_f32(float a, float multiple);

// Ceil
LM2_API double lm2_ceil_f64(double a);
LM2_API float lm2_ceil_f32(float a);
LM2_API double lm2_ceil_multiple_f64(double a, double multiple);
LM2_API float lm2_ceil_multiple_f32(float a, float multiple);

// Round
LM2_API double lm2_round_f64(double a);
LM2_API float lm2_round_f32(float a);
LM2_API double lm2_round_multiple_f64(double a, double multiple);
LM2_API float lm2_round_multiple_f32(float a, float multiple);

// Truncate
LM2_API double lm2_trunc_f64(double a);
LM2_API float lm2_trunc_f32(float a);
LM2_API double lm2_trunc_multiple_f64(double a, double multiple);
LM2_API float lm2_trunc_multiple_f32(float a, float multiple);

// Abs
LM2_API double lm2_abs_f64(double a);
LM2_API float lm2_abs_f32(float a);

// Sign (returns 1 or -1)
LM2_API double lm2_sign_f64(double a);
LM2_API float lm2_sign_f32(float a);

// Sign0 (returns 1, -1, or 0)
LM2_API double lm2_sign0_f64(double a);
LM2_API float lm2_sign0_f32(float a);

// Min
LM2_API double lm2_min_f64(double a, double b);
LM2_API float lm2_min_f32(float a, float b);
LM2_API double lm2_min_abs_f64(double a, double b);
LM2_API float lm2_min_abs_f32(float a, float b);

// Max
LM2_API double lm2_max_f64(double a, double b);
LM2_API float lm2_max_f32(float a, float b);
LM2_API double lm2_max_abs_f64(double a, double b);
LM2_API float lm2_max_abs_f32(float a, float b);

// Clamp
LM2_API double lm2_clamp_f64(double min, double value, double max);
LM2_API float lm2_clamp_f32(float min, float value, float max);

// Saturate to [0, 1]
LM2_API double lm2_saturate_f64(double value);
LM2_API float lm2_saturate_f32(float value);

// Lerp
LM2_API double lm2_lerp_f64(double a, double t, double b);
LM2_API float lm2_lerp_f32(float a, float t, float b);

// Smoothstep
LM2_API double lm2_smoothstep_f64(double edge0, double x, double edge1);
LM2_API float lm2_smoothstep_f32(float edge0, float x, float edge1);

// Alpha
LM2_API double lm2_alpha_f64(double a, double value, double b);
LM2_API float lm2_alpha_f32(float a, float value, float b);

// Fract
LM2_API double lm2_fract_f64(double a);
LM2_API float lm2_fract_f32(float a);

// Modulo
LM2_API double lm2_mod_f64(double a, double b);
LM2_API float lm2_mod_f32(float a, float b);

// Normalize (divide by sign)
LM2_API double lm2_norm_f64(double a);
LM2_API float lm2_norm_f32(float a);

// Generics
#ifndef LM2_NO_GENERICS
#  define lm2_floor(...)          _LM2_GENERIC(lm2_floor, __VA_ARGS__)
#  define lm2_floor_multiple(...) _LM2_GENERIC(lm2_floor_multiple, __VA_ARGS__)
#  define lm2_ceil(...)           _LM2_GENERIC(lm2_ceil, __VA_ARGS__)
#  define lm2_ceil_multiple(...)  _LM2_GENERIC(lm2_ceil_multiple, __VA_ARGS__)
#  define lm2_round(...)          _LM2_GENERIC(lm2_round, __VA_ARGS__)
#  define lm2_round_multiple(...) _LM2_GENERIC(lm2_round_multiple, __VA_ARGS__)
#  define lm2_trunc(...)          _LM2_GENERIC(lm2_trunc, __VA_ARGS__)
#  define lm2_trunc_multiple(...) _LM2_GENERIC(lm2_trunc_multiple, __VA_ARGS__)
#  define lm2_abs(...)            _LM2_GENERIC(lm2_abs, __VA_ARGS__)
#  define lm2_sign(...)           _LM2_GENERIC(lm2_sign, __VA_ARGS__)
#  define lm2_sign0(...)          _LM2_GENERIC(lm2_sign0, __VA_ARGS__)
#  define lm2_min(...)            _LM2_GENERIC(lm2_min, __VA_ARGS__)
#  define lm2_min_abs(...)        _LM2_GENERIC(lm2_min_abs, __VA_ARGS__)
#  define lm2_max(...)            _LM2_GENERIC(lm2_max, __VA_ARGS__)
#  define lm2_max_abs(...)        _LM2_GENERIC(lm2_max_abs, __VA_ARGS__)
#  define lm2_clamp(...)          _LM2_GENERIC(lm2_clamp, __VA_ARGS__)
#  define lm2_saturate(...)       _LM2_GENERIC(lm2_saturate, __VA_ARGS__)
#  define lm2_lerp(...)           _LM2_GENERIC(lm2_lerp, __VA_ARGS__)
#  define lm2_smoothstep(...)     _LM2_GENERIC(lm2_smoothstep, __VA_ARGS__)
#  define lm2_alpha(...)          _LM2_GENERIC(lm2_alpha, __VA_ARGS__)
#  define lm2_fract(...)          _LM2_GENERIC(lm2_fract, __VA_ARGS__)
#  define lm2_mod(...)            _LM2_GENERIC(lm2_mod, __VA_ARGS__)
#  define lm2_norm(...)           _LM2_GENERIC(lm2_norm, __VA_ARGS__)
#endif

// #############################################################################
LM2_HEADER_END;
// #############################################################################