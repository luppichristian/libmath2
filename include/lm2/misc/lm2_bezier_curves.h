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
#include "lm2/vectors/lm2_vector3.h"
#include "lm2/vectors/lm2_vector4.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// Linear Bezier (2 control points) - 2D
// B(t) = (1-t)*P0 + t*P1
// =============================================================================

LM2_API lm2_v2f64 lm2_bezier_linear_v2f64(lm2_v2f64 p0, lm2_v2f64 p1, double t);
LM2_API lm2_v2f32 lm2_bezier_linear_v2f32(lm2_v2f32 p0, lm2_v2f32 p1, float t);

// =============================================================================
// Linear Bezier (2 control points) - 3D
// =============================================================================

LM2_API lm2_v3f64 lm2_bezier_linear_v3f64(lm2_v3f64 p0, lm2_v3f64 p1, double t);
LM2_API lm2_v3f32 lm2_bezier_linear_v3f32(lm2_v3f32 p0, lm2_v3f32 p1, float t);

// =============================================================================
// Linear Bezier (2 control points) - 4D
// =============================================================================

LM2_API lm2_v4f64 lm2_bezier_linear_v4f64(lm2_v4f64 p0, lm2_v4f64 p1, double t);
LM2_API lm2_v4f32 lm2_bezier_linear_v4f32(lm2_v4f32 p0, lm2_v4f32 p1, float t);

// =============================================================================
// Quadratic Bezier (3 control points) - 2D
// B(t) = (1-t)^2*P0 + 2*(1-t)*t*P1 + t^2*P2
// =============================================================================

LM2_API lm2_v2f64 lm2_bezier_quadratic_v2f64(lm2_v2f64 p0, lm2_v2f64 p1, lm2_v2f64 p2, double t);
LM2_API lm2_v2f32 lm2_bezier_quadratic_v2f32(lm2_v2f32 p0, lm2_v2f32 p1, lm2_v2f32 p2, float t);

// =============================================================================
// Quadratic Bezier (3 control points) - 3D
// =============================================================================

LM2_API lm2_v3f64 lm2_bezier_quadratic_v3f64(lm2_v3f64 p0, lm2_v3f64 p1, lm2_v3f64 p2, double t);
LM2_API lm2_v3f32 lm2_bezier_quadratic_v3f32(lm2_v3f32 p0, lm2_v3f32 p1, lm2_v3f32 p2, float t);

// =============================================================================
// Quadratic Bezier (3 control points) - 4D
// =============================================================================

LM2_API lm2_v4f64 lm2_bezier_quadratic_v4f64(lm2_v4f64 p0, lm2_v4f64 p1, lm2_v4f64 p2, double t);
LM2_API lm2_v4f32 lm2_bezier_quadratic_v4f32(lm2_v4f32 p0, lm2_v4f32 p1, lm2_v4f32 p2, float t);

// =============================================================================
// Cubic Bezier (4 control points) - 2D
// B(t) = (1-t)^3*P0 + 3*(1-t)^2*t*P1 + 3*(1-t)*t^2*P2 + t^3*P3
// =============================================================================

LM2_API lm2_v2f64 lm2_bezier_cubic_v2f64(lm2_v2f64 p0, lm2_v2f64 p1, lm2_v2f64 p2, lm2_v2f64 p3, double t);
LM2_API lm2_v2f32 lm2_bezier_cubic_v2f32(lm2_v2f32 p0, lm2_v2f32 p1, lm2_v2f32 p2, lm2_v2f32 p3, float t);

// =============================================================================
// Cubic Bezier (4 control points) - 3D
// =============================================================================

LM2_API lm2_v3f64 lm2_bezier_cubic_v3f64(lm2_v3f64 p0, lm2_v3f64 p1, lm2_v3f64 p2, lm2_v3f64 p3, double t);
LM2_API lm2_v3f32 lm2_bezier_cubic_v3f32(lm2_v3f32 p0, lm2_v3f32 p1, lm2_v3f32 p2, lm2_v3f32 p3, float t);

// =============================================================================
// Cubic Bezier (4 control points) - 4D
// =============================================================================

LM2_API lm2_v4f64 lm2_bezier_cubic_v4f64(lm2_v4f64 p0, lm2_v4f64 p1, lm2_v4f64 p2, lm2_v4f64 p3, double t);
LM2_API lm2_v4f32 lm2_bezier_cubic_v4f32(lm2_v4f32 p0, lm2_v4f32 p1, lm2_v4f32 p2, lm2_v4f32 p3, float t);

// =============================================================================
// Quadratic Bezier Derivative (velocity) - 2D
// B'(t) = 2*(1-t)*(P1-P0) + 2*t*(P2-P1)
// =============================================================================

LM2_API lm2_v2f64 lm2_bezier_quadratic_derivative_v2f64(lm2_v2f64 p0, lm2_v2f64 p1, lm2_v2f64 p2, double t);
LM2_API lm2_v2f32 lm2_bezier_quadratic_derivative_v2f32(lm2_v2f32 p0, lm2_v2f32 p1, lm2_v2f32 p2, float t);

// =============================================================================
// Quadratic Bezier Derivative (velocity) - 3D
// =============================================================================

LM2_API lm2_v3f64 lm2_bezier_quadratic_derivative_v3f64(lm2_v3f64 p0, lm2_v3f64 p1, lm2_v3f64 p2, double t);
LM2_API lm2_v3f32 lm2_bezier_quadratic_derivative_v3f32(lm2_v3f32 p0, lm2_v3f32 p1, lm2_v3f32 p2, float t);

// =============================================================================
// Quadratic Bezier Derivative (velocity) - 4D
// =============================================================================

LM2_API lm2_v4f64 lm2_bezier_quadratic_derivative_v4f64(lm2_v4f64 p0, lm2_v4f64 p1, lm2_v4f64 p2, double t);
LM2_API lm2_v4f32 lm2_bezier_quadratic_derivative_v4f32(lm2_v4f32 p0, lm2_v4f32 p1, lm2_v4f32 p2, float t);

// =============================================================================
// Cubic Bezier Derivative (velocity) - 2D
// B'(t) = 3*(1-t)^2*(P1-P0) + 6*(1-t)*t*(P2-P1) + 3*t^2*(P3-P2)
// =============================================================================

LM2_API lm2_v2f64 lm2_bezier_cubic_derivative_v2f64(lm2_v2f64 p0, lm2_v2f64 p1, lm2_v2f64 p2, lm2_v2f64 p3, double t);
LM2_API lm2_v2f32 lm2_bezier_cubic_derivative_v2f32(lm2_v2f32 p0, lm2_v2f32 p1, lm2_v2f32 p2, lm2_v2f32 p3, float t);

// =============================================================================
// Cubic Bezier Derivative (velocity) - 3D
// =============================================================================

LM2_API lm2_v3f64 lm2_bezier_cubic_derivative_v3f64(lm2_v3f64 p0, lm2_v3f64 p1, lm2_v3f64 p2, lm2_v3f64 p3, double t);
LM2_API lm2_v3f32 lm2_bezier_cubic_derivative_v3f32(lm2_v3f32 p0, lm2_v3f32 p1, lm2_v3f32 p2, lm2_v3f32 p3, float t);

// =============================================================================
// Cubic Bezier Derivative (velocity) - 4D
// =============================================================================

LM2_API lm2_v4f64 lm2_bezier_cubic_derivative_v4f64(lm2_v4f64 p0, lm2_v4f64 p1, lm2_v4f64 p2, lm2_v4f64 p3, double t);
LM2_API lm2_v4f32 lm2_bezier_cubic_derivative_v4f32(lm2_v4f32 p0, lm2_v4f32 p1, lm2_v4f32 p2, lm2_v4f32 p3, float t);

// =============================================================================
// Cubic Bezier Second Derivative (acceleration) - 2D
// B''(t) = 6*(1-t)*(P2-2*P1+P0) + 6*t*(P3-2*P2+P1)
// =============================================================================

LM2_API lm2_v2f64 lm2_bezier_cubic_second_derivative_v2f64(lm2_v2f64 p0, lm2_v2f64 p1, lm2_v2f64 p2, lm2_v2f64 p3, double t);
LM2_API lm2_v2f32 lm2_bezier_cubic_second_derivative_v2f32(lm2_v2f32 p0, lm2_v2f32 p1, lm2_v2f32 p2, lm2_v2f32 p3, float t);

// =============================================================================
// Cubic Bezier Second Derivative (acceleration) - 3D
// =============================================================================

LM2_API lm2_v3f64 lm2_bezier_cubic_second_derivative_v3f64(lm2_v3f64 p0, lm2_v3f64 p1, lm2_v3f64 p2, lm2_v3f64 p3, double t);
LM2_API lm2_v3f32 lm2_bezier_cubic_second_derivative_v3f32(lm2_v3f32 p0, lm2_v3f32 p1, lm2_v3f32 p2, lm2_v3f32 p3, float t);

// =============================================================================
// Cubic Bezier Second Derivative (acceleration) - 4D
// =============================================================================

LM2_API lm2_v4f64 lm2_bezier_cubic_second_derivative_v4f64(lm2_v4f64 p0, lm2_v4f64 p1, lm2_v4f64 p2, lm2_v4f64 p3, double t);
LM2_API lm2_v4f32 lm2_bezier_cubic_second_derivative_v4f32(lm2_v4f32 p0, lm2_v4f32 p1, lm2_v4f32 p2, lm2_v4f32 p3, float t);

// =============================================================================
// Bezier Curve Splitting - 2D
// Splits a cubic bezier curve at parameter t into two cubic curves
// Uses De Casteljau's algorithm
// left_* will contain the curve from 0 to t
// right_* will contain the curve from t to 1
// =============================================================================

LM2_API void lm2_bezier_cubic_split_v2f64(
    lm2_v2f64 p0,
    lm2_v2f64 p1,
    lm2_v2f64 p2,
    lm2_v2f64 p3,
    double t,
    lm2_v2f64* left_p0,
    lm2_v2f64* left_p1,
    lm2_v2f64* left_p2,
    lm2_v2f64* left_p3,
    lm2_v2f64* right_p0,
    lm2_v2f64* right_p1,
    lm2_v2f64* right_p2,
    lm2_v2f64* right_p3);

LM2_API void lm2_bezier_cubic_split_v2f32(
    lm2_v2f32 p0,
    lm2_v2f32 p1,
    lm2_v2f32 p2,
    lm2_v2f32 p3,
    float t,
    lm2_v2f32* left_p0,
    lm2_v2f32* left_p1,
    lm2_v2f32* left_p2,
    lm2_v2f32* left_p3,
    lm2_v2f32* right_p0,
    lm2_v2f32* right_p1,
    lm2_v2f32* right_p2,
    lm2_v2f32* right_p3);

// =============================================================================
// Bezier Curve Splitting - 3D
// =============================================================================

LM2_API void lm2_bezier_cubic_split_v3f64(
    lm2_v3f64 p0,
    lm2_v3f64 p1,
    lm2_v3f64 p2,
    lm2_v3f64 p3,
    double t,
    lm2_v3f64* left_p0,
    lm2_v3f64* left_p1,
    lm2_v3f64* left_p2,
    lm2_v3f64* left_p3,
    lm2_v3f64* right_p0,
    lm2_v3f64* right_p1,
    lm2_v3f64* right_p2,
    lm2_v3f64* right_p3);

LM2_API void lm2_bezier_cubic_split_v3f32(
    lm2_v3f32 p0,
    lm2_v3f32 p1,
    lm2_v3f32 p2,
    lm2_v3f32 p3,
    float t,
    lm2_v3f32* left_p0,
    lm2_v3f32* left_p1,
    lm2_v3f32* left_p2,
    lm2_v3f32* left_p3,
    lm2_v3f32* right_p0,
    lm2_v3f32* right_p1,
    lm2_v3f32* right_p2,
    lm2_v3f32* right_p3);

// =============================================================================
// Bezier Curve Splitting - 4D
// =============================================================================

LM2_API void lm2_bezier_cubic_split_v4f64(
    lm2_v4f64 p0,
    lm2_v4f64 p1,
    lm2_v4f64 p2,
    lm2_v4f64 p3,
    double t,
    lm2_v4f64* left_p0,
    lm2_v4f64* left_p1,
    lm2_v4f64* left_p2,
    lm2_v4f64* left_p3,
    lm2_v4f64* right_p0,
    lm2_v4f64* right_p1,
    lm2_v4f64* right_p2,
    lm2_v4f64* right_p3);

LM2_API void lm2_bezier_cubic_split_v4f32(
    lm2_v4f32 p0,
    lm2_v4f32 p1,
    lm2_v4f32 p2,
    lm2_v4f32 p3,
    float t,
    lm2_v4f32* left_p0,
    lm2_v4f32* left_p1,
    lm2_v4f32* left_p2,
    lm2_v4f32* left_p3,
    lm2_v4f32* right_p0,
    lm2_v4f32* right_p1,
    lm2_v4f32* right_p2,
    lm2_v4f32* right_p3);

// =============================================================================
// Bezier Curve Arc Length Approximation - 2D
// Approximates the arc length of a cubic bezier using adaptive subdivision
// segments: number of segments to use for approximation (higher = more accurate)
// =============================================================================

LM2_API double lm2_bezier_cubic_length_v2f64(lm2_v2f64 p0, lm2_v2f64 p1, lm2_v2f64 p2, lm2_v2f64 p3, int segments);
LM2_API float lm2_bezier_cubic_length_v2f32(lm2_v2f32 p0, lm2_v2f32 p1, lm2_v2f32 p2, lm2_v2f32 p3, int segments);

// =============================================================================
// Bezier Curve Arc Length Approximation - 3D
// =============================================================================

LM2_API double lm2_bezier_cubic_length_v3f64(lm2_v3f64 p0, lm2_v3f64 p1, lm2_v3f64 p2, lm2_v3f64 p3, int segments);
LM2_API float lm2_bezier_cubic_length_v3f32(lm2_v3f32 p0, lm2_v3f32 p1, lm2_v3f32 p2, lm2_v3f32 p3, int segments);

// =============================================================================
// Bezier Curve Arc Length Approximation - 4D
// =============================================================================

LM2_API double lm2_bezier_cubic_length_v4f64(lm2_v4f64 p0, lm2_v4f64 p1, lm2_v4f64 p2, lm2_v4f64 p3, int segments);
LM2_API float lm2_bezier_cubic_length_v4f32(lm2_v4f32 p0, lm2_v4f32 p1, lm2_v4f32 p2, lm2_v4f32 p3, int segments);

// #############################################################################
LM2_HEADER_END;
// #############################################################################
