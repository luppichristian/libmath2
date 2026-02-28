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

#include "lm2/lm2_base.h"
#include "lm2/vectors/lm2_vector2.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// Ray Types (2D)
// =============================================================================

// 2D Ray structure
// IMPORTANT: direction should be normalized, t specifies the distance along direction
typedef struct lm2_ray2_f64 {
  lm2_v2_f64 origin;     // Ray origin position
  lm2_v2_f64 direction;  // Ray direction (should be normalized)
  double t_max;          // Maximum distance along ray
} lm2_ray2_f64;

typedef struct lm2_ray2_f32 {
  lm2_v2_f32 origin;     // Ray origin position
  lm2_v2_f32 direction;  // Ray direction (should be normalized)
  float t_max;           // Maximum distance along ray
} lm2_ray2_f32;

// Default 2D ray type
typedef lm2_ray2_f32 lm2_ray2;

// #############################################################################
LM2_HEADER_END;
// #############################################################################
