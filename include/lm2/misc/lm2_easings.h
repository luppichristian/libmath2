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

#include "lm2/scalar/lm2_safe_ops.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// Linear
LM2_API double ease_linear_f64(double t);
LM2_API float ease_linear_f32(float t);

// Sin
LM2_API double ease_sin_in_f64(double t);
LM2_API double ease_sin_out_f64(double t);
LM2_API double ease_sin_in_out_f64(double t);
LM2_API float ease_sin_in_f32(float t);
LM2_API float ease_sin_out_f32(float t);
LM2_API float ease_sin_in_out_f32(float t);

// Quad
LM2_API double ease_quad_in_f64(double t);
LM2_API double ease_quad_out_f64(double t);
LM2_API double ease_quad_in_out_f64(double t);
LM2_API float ease_quad_in_f32(float t);
LM2_API float ease_quad_out_f32(float t);
LM2_API float ease_quad_in_out_f32(float t);

// Cubic
LM2_API double ease_cubic_in_f64(double t);
LM2_API double ease_cubic_out_f64(double t);
LM2_API double ease_cubic_in_out_f64(double t);
LM2_API float ease_cubic_in_f32(float t);
LM2_API float ease_cubic_out_f32(float t);
LM2_API float ease_cubic_in_out_f32(float t);

// Quart
LM2_API double ease_quart_in_f64(double t);
LM2_API double ease_quart_out_f64(double t);
LM2_API double ease_quart_in_out_f64(double t);
LM2_API float ease_quart_in_f32(float t);
LM2_API float ease_quart_out_f32(float t);
LM2_API float ease_quart_in_out_f32(float t);

// Quint
LM2_API double ease_quint_in_f64(double t);
LM2_API double ease_quint_out_f64(double t);
LM2_API double ease_quint_in_out_f64(double t);
LM2_API float ease_quint_in_f32(float t);
LM2_API float ease_quint_out_f32(float t);
LM2_API float ease_quint_in_out_f32(float t);

// Exp
LM2_API double ease_exp_in_f64(double t);
LM2_API double ease_exp_out_f64(double t);
LM2_API double ease_exp_in_out_f64(double t);
LM2_API float ease_exp_in_f32(float t);
LM2_API float ease_exp_out_f32(float t);
LM2_API float ease_exp_in_out_f32(float t);

// Circ
LM2_API double ease_circ_in_f64(double t);
LM2_API double ease_circ_out_f64(double t);
LM2_API double ease_circ_in_out_f64(double t);
LM2_API float ease_circ_in_f32(float t);
LM2_API float ease_circ_out_f32(float t);
LM2_API float ease_circ_in_out_f32(float t);

// Back
LM2_API double ease_back_in_f64(double t);
LM2_API double ease_back_out_f64(double t);
LM2_API double ease_back_in_out_f64(double t);
LM2_API float ease_back_in_f32(float t);
LM2_API float ease_back_out_f32(float t);
LM2_API float ease_back_in_out_f32(float t);

// Elastic
LM2_API double ease_elastic_in_f64(double t);
LM2_API double ease_elastic_out_f64(double t);
LM2_API double ease_elastic_in_out_f64(double t);
LM2_API float ease_elastic_in_f32(float t);
LM2_API float ease_elastic_out_f32(float t);
LM2_API float ease_elastic_in_out_f32(float t);

// Bounce
LM2_API double ease_bounce_in_f64(double t);
LM2_API double ease_bounce_out_f64(double t);
LM2_API double ease_bounce_in_out_f64(double t);
LM2_API float ease_bounce_in_f32(float t);
LM2_API float ease_bounce_out_f32(float t);
LM2_API float ease_bounce_in_out_f32(float t);

// Easing types (enum)
typedef enum easing {
  EASING_LINEAR,
  EASING_SIN_IN,
  EASING_SIN_OUT,
  EASING_SIN_IN_OUT,
  EASING_CUB_IN,
  EASING_CUB_OUT,
  EASING_CUB_IN_OUT,
  EASING_QUINT_IN,
  EASING_QUINT_OUT,
  EASING_QUINT_IN_OUT,
  EASING_CIRC_IN,
  EASING_CIRC_OUT,
  EASING_CIRC_IN_OUT,
  EASING_ELASTIC_IN,
  EASING_ELASTIC_OUT,
  EASING_ELASTIC_IN_OUT,
  EASING_QUAD_IN,
  EASING_QUAD_OUT,
  EASING_QUAD_IN_OUT,
  EASING_QUART_IN,
  EASING_QUART_OUT,
  EASING_QUART_IN_OUT,
  EASING_EXP_IN,
  EASING_EXP_OUT,
  EASING_EXP_IN_OUT,
  EASING_BACK_IN,
  EASING_BACK_OUT,
  EASING_BACK_IN_OUT,
  EASING_BOUNCE_IN,
  EASING_BOUNCE_OUT,
  EASING_BOUNCE_IN_OUT,
  EASING_MAX,
} easing;

// Helper to convert enum to string
LM2_API const char* lm2_easing_to_string(easing easing);

// Generalized easing function
LM2_API double lm2_ease_f64(easing easing, double t);
LM2_API float lm2_ease_f32(easing easing, float t);

// Generic macros
#ifndef LM2_NO_GENERICS
#  define lm2_ease_linear(...)         _LM2_GENERIC(lm2_ease_linear, __VA_ARGS__)
#  define lm2_ease_sin_in(...)         _LM2_GENERIC(lm2_ease_sin_in, __VA_ARGS__)
#  define lm2_ease_sin_out(...)        _LM2_GENERIC(lm2_ease_sin_out, __VA_ARGS__)
#  define lm2_ease_sin_in_out(...)     _LM2_GENERIC(lm2_ease_sin_in_out, __VA_ARGS__)
#  define lm2_ease_cubic_in(...)       _LM2_GENERIC(lm2_ease_cubic_in, __VA_ARGS__)
#  define lm2_ease_cubic_out(...)      _LM2_GENERIC(lm2_ease_cubic_out, __VA_ARGS__)
#  define lm2_ease_cubic_in_out(...)   _LM2_GENERIC(lm2_ease_cubic_in_out, __VA_ARGS__)
#  define lm2_ease_quart_in(...)       _LM2_GENERIC(lm2_ease_quart_in, __VA_ARGS__)
#  define lm2_ease_quart_out(...)      _LM2_GENERIC(lm2_ease_quart_out, __VA_ARGS__)
#  define lm2_ease_quart_in_out(...)   _LM2_GENERIC(lm2_ease_quart_in_out, __VA_ARGS__)
#  define lm2_ease_quint_in(...)       _LM2_GENERIC(lm2_ease_quint_in, __VA_ARGS__)
#  define lm2_ease_quint_out(...)      _LM2_GENERIC(lm2_ease_quint_out, __VA_ARGS__)
#  define lm2_ease_quint_in_out(...)   _LM2_GENERIC(lm2_ease_quint_in_out, __VA_ARGS__)
#  define lm2_ease_exp_in(...)         _LM2_GENERIC(lm2_ease_exp_in, __VA_ARGS__)
#  define lm2_ease_exp_out(...)        _LM2_GENERIC(lm2_ease_exp_out, __VA_ARGS__)
#  define lm2_ease_exp_in_out(...)     _LM2_GENERIC(lm2_ease_exp_in_out, __VA_ARGS__)
#  define lm2_ease_circ_in(...)        _LM2_GENERIC(lm2_ease_circ_in, __VA_ARGS__)
#  define lm2_ease_circ_out(...)       _LM2_GENERIC(lm2_ease_circ_out, __VA_ARGS__)
#  define lm2_ease_circ_in_out(...)    _LM2_GENERIC(lm2_ease_circ_in_out, __VA_ARGS__)
#  define lm2_ease_back_in(...)        _LM2_GENERIC(lm2_ease_back_in, __VA_ARGS__)
#  define lm2_ease_back_out(...)       _LM2_GENERIC(lm2_ease_back_out, __VA_ARGS__)
#  define lm2_ease_back_in_out(...)    _LM2_GENERIC(lm2_ease_back_in_out, __VA_ARGS__)
#  define lm2_ease_elastic_in(...)     _LM2_GENERIC(lm2_ease_elastic_in, __VA_ARGS__)
#  define lm2_ease_elastic_out(...)    _LM2_GENERIC(lm2_ease_elastic_out, __VA_ARGS__)
#  define lm2_ease_elastic_in_out(...) _LM2_GENERIC(lm2_ease_elastic_in_out, __VA_ARGS__)
#  define lm2_ease_quad_in(...)        _LM2_GENERIC(lm2_ease_quad_in, __VA_ARGS__)
#  define lm2_ease_quad_out(...)       _LM2_GENERIC(lm2_ease_quad_out, __VA_ARGS__)
#  define lm2_ease_quad_in_out(...)    _LM2_GENERIC(lm2_ease_quad_in_out, __VA_ARGS__)
#  define lm2_ease_bounce_in(...)      _LM2_GENERIC(lm2_ease_bounce_in, __VA_ARGS__)
#  define lm2_ease_bounce_out(...)     _LM2_GENERIC(lm2_ease_bounce_out, __VA_ARGS__)
#  define lm2_ease_bounce_in_out(...)  _LM2_GENERIC(lm2_ease_bounce_in_out, __VA_ARGS__)
#  define lm2_ease(...)                _LM2_GENERIC(lm2_ease, __VA_ARGS__)
#endif

// #############################################################################
LM2_HEADER_END;
// #############################################################################