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
// Ray Hit Result Types (2D)
// =============================================================================

// 2D Ray hit result
typedef struct lm2_rayhit2_f64 {
  bool hit;           // Whether the ray hit something
  double t;           // Distance along ray where hit occurred
  lm2_v2_f64 point;   // Hit point in world space
  lm2_v2_f64 normal;  // Surface normal at hit point (unit length)
} lm2_rayhit2_f64;

typedef struct lm2_rayhit2_f32 {
  bool hit;           // Whether the ray hit something
  float t;            // Distance along ray where hit occurred
  lm2_v2_f32 point;   // Hit point in world space
  lm2_v2_f32 normal;  // Surface normal at hit point (unit length)
} lm2_rayhit2_f32;

// #############################################################################
LM2_HEADER_END;
// #############################################################################
