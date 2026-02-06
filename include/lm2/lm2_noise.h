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

#include "lm2_safe_ops.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// Perlin Noise 2D (returns value in [-1, 1])
LM2_API double lm2_perlin_2d_f64(double x, double y);
LM2_API float lm2_perlin_2d_f32(float x, float y);

// Perlin Noise 3D (returns value in [-1, 1])
LM2_API double lm2_perlin_3d_f64(double x, double y, double z);
LM2_API float lm2_perlin_3d_f32(float x, float y, float z);

// Voronoi Noise 2D (returns Euclidean distance to nearest feature point)
LM2_API double lm2_voronoi_2d_f64(double x, double y);
LM2_API float lm2_voronoi_2d_f32(float x, float y);

// Voronoi Noise 3D (returns Euclidean distance to nearest feature point)
LM2_API double lm2_voronoi_3d_f64(double x, double y, double z);
LM2_API float lm2_voronoi_3d_f32(float x, float y, float z);

// Generics
#ifndef LM2_NO_GENERICS
#  define lm2_perlin_2d(...)  _LM2_GENERIC(lm2_perlin_2d, __VA_ARGS__)
#  define lm2_perlin_3d(...)  _LM2_GENERIC(lm2_perlin_3d, __VA_ARGS__)
#  define lm2_voronoi_2d(...) _LM2_GENERIC(lm2_voronoi_2d, __VA_ARGS__)
#  define lm2_voronoi_3d(...) _LM2_GENERIC(lm2_voronoi_3d, __VA_ARGS__)
#endif

// #############################################################################
LM2_HEADER_END;
// #############################################################################
