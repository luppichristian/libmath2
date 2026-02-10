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
// Dot Product
// =============================================================================

// 2D dot product
LM2_API double lm2_v2_dot_f64(lm2_v2_f64 a, lm2_v2_f64 b);
LM2_API float lm2_v2_dot_f32(lm2_v2_f32 a, lm2_v2_f32 b);
LM2_API int64_t lm2_v2_dot_i64(lm2_v2_i64 a, lm2_v2_i64 b);
LM2_API int32_t lm2_v2_dot_i32(lm2_v2_i32 a, lm2_v2_i32 b);
LM2_API int16_t lm2_v2_dot_i16(lm2_v2_i16 a, lm2_v2_i16 b);
LM2_API int8_t lm2_v2_dot_i8(lm2_v2_i8 a, lm2_v2_i8 b);

// 3D dot product
LM2_API double lm2_v3_dot_f64(lm2_v3_f64 a, lm2_v3_f64 b);
LM2_API float lm2_v3_dot_f32(lm2_v3_f32 a, lm2_v3_f32 b);
LM2_API int64_t lm2_v3_dot_i64(lm2_v3_i64 a, lm2_v3_i64 b);
LM2_API int32_t lm2_v3_dot_i32(lm2_v3_i32 a, lm2_v3_i32 b);
LM2_API int16_t lm2_v3_dot_i16(lm2_v3_i16 a, lm2_v3_i16 b);
LM2_API int8_t lm2_v3_dot_i8(lm2_v3_i8 a, lm2_v3_i8 b);

// 4D dot product
LM2_API double lm2_v4_dot_f64(lm2_v4_f64 a, lm2_v4_f64 b);
LM2_API float lm2_v4_dot_f32(lm2_v4_f32 a, lm2_v4_f32 b);
LM2_API int64_t lm2_v4_dot_i64(lm2_v4_i64 a, lm2_v4_i64 b);
LM2_API int32_t lm2_v4_dot_i32(lm2_v4_i32 a, lm2_v4_i32 b);
LM2_API int16_t lm2_v4_dot_i16(lm2_v4_i16 a, lm2_v4_i16 b);
LM2_API int8_t lm2_v4_dot_i8(lm2_v4_i8 a, lm2_v4_i8 b);

// =============================================================================
// Cross Product (3D only)
// =============================================================================

LM2_API lm2_v3_f64 lm2_v3_cross_f64(lm2_v3_f64 a, lm2_v3_f64 b);
LM2_API lm2_v3_f32 lm2_v3_cross_f32(lm2_v3_f32 a, lm2_v3_f32 b);
LM2_API lm2_v3_i64 lm2_v3_cross_i64(lm2_v3_i64 a, lm2_v3_i64 b);
LM2_API lm2_v3_i32 lm2_v3_cross_i32(lm2_v3_i32 a, lm2_v3_i32 b);
LM2_API lm2_v3_i16 lm2_v3_cross_i16(lm2_v3_i16 a, lm2_v3_i16 b);
LM2_API lm2_v3_i8 lm2_v3_cross_i8(lm2_v3_i8 a, lm2_v3_i8 b);

// =============================================================================
// 2D Cross Product (returns scalar: a.x * b.y - a.y * b.x)
// =============================================================================

LM2_API double lm2_v2_cross_f64(lm2_v2_f64 a, lm2_v2_f64 b);
LM2_API float lm2_v2_cross_f32(lm2_v2_f32 a, lm2_v2_f32 b);
LM2_API int64_t lm2_v2_cross_i64(lm2_v2_i64 a, lm2_v2_i64 b);
LM2_API int32_t lm2_v2_cross_i32(lm2_v2_i32 a, lm2_v2_i32 b);
LM2_API int16_t lm2_v2_cross_i16(lm2_v2_i16 a, lm2_v2_i16 b);
LM2_API int8_t lm2_v2_cross_i8(lm2_v2_i8 a, lm2_v2_i8 b);

// =============================================================================
// 2D Cross Product for Turn Detection (3-point version)
// Returns scalar for determining turn direction:
// > 0: Left turn (counterclockwise)
// < 0: Right turn (clockwise)
// = 0: Collinear (points on same line)
// =============================================================================

LM2_API double lm2_v2_cross3_f64(lm2_v2_f64 a, lm2_v2_f64 b, lm2_v2_f64 c);
LM2_API float lm2_v2_cross3_f32(lm2_v2_f32 a, lm2_v2_f32 b, lm2_v2_f32 c);
LM2_API int64_t lm2_v2_cross3_i64(lm2_v2_i64 a, lm2_v2_i64 b, lm2_v2_i64 c);
LM2_API int32_t lm2_v2_cross3_i32(lm2_v2_i32 a, lm2_v2_i32 b, lm2_v2_i32 c);
LM2_API int16_t lm2_v2_cross3_i16(lm2_v2_i16 a, lm2_v2_i16 b, lm2_v2_i16 c);
LM2_API int8_t lm2_v2_cross3_i8(lm2_v2_i8 a, lm2_v2_i8 b, lm2_v2_i8 c);

// =============================================================================
// Length / Magnitude
// =============================================================================

// 2D length
LM2_API double lm2_v2_length_f64(lm2_v2_f64 v);
LM2_API float lm2_v2_length_f32(lm2_v2_f32 v);

// 3D length
LM2_API double lm2_v3_length_f64(lm2_v3_f64 v);
LM2_API float lm2_v3_length_f32(lm2_v3_f32 v);

// 4D length
LM2_API double lm2_v4_length_f64(lm2_v4_f64 v);
LM2_API float lm2_v4_length_f32(lm2_v4_f32 v);

// =============================================================================
// Length Squared (faster than length, no sqrt)
// =============================================================================

// 2D length squared
LM2_API double lm2_v2_length_sq_f64(lm2_v2_f64 v);
LM2_API float lm2_v2_length_sq_f32(lm2_v2_f32 v);

// 3D length squared
LM2_API double lm2_v3_length_sq_f64(lm2_v3_f64 v);
LM2_API float lm2_v3_length_sq_f32(lm2_v3_f32 v);

// 4D length squared
LM2_API double lm2_v4_length_sq_f64(lm2_v4_f64 v);
LM2_API float lm2_v4_length_sq_f32(lm2_v4_f32 v);

// =============================================================================
// Distance
// =============================================================================

// 2D distance
LM2_API double lm2_v2_distance_f64(lm2_v2_f64 a, lm2_v2_f64 b);
LM2_API float lm2_v2_distance_f32(lm2_v2_f32 a, lm2_v2_f32 b);

// 3D distance
LM2_API double lm2_v3_distance_f64(lm2_v3_f64 a, lm2_v3_f64 b);
LM2_API float lm2_v3_distance_f32(lm2_v3_f32 a, lm2_v3_f32 b);

// 4D distance
LM2_API double lm2_v4_distance_f64(lm2_v4_f64 a, lm2_v4_f64 b);
LM2_API float lm2_v4_distance_f32(lm2_v4_f32 a, lm2_v4_f32 b);

// =============================================================================
// Distance Squared (faster than distance, no sqrt)
// =============================================================================

// 2D distance squared
LM2_API double lm2_v2_distance_sq_f64(lm2_v2_f64 a, lm2_v2_f64 b);
LM2_API float lm2_v2_distance_sq_f32(lm2_v2_f32 a, lm2_v2_f32 b);

// 3D distance squared
LM2_API double lm2_v3_distance_sq_f64(lm2_v3_f64 a, lm2_v3_f64 b);
LM2_API float lm2_v3_distance_sq_f32(lm2_v3_f32 a, lm2_v3_f32 b);

// 4D distance squared
LM2_API double lm2_v4_distance_sq_f64(lm2_v4_f64 a, lm2_v4_f64 b);
LM2_API float lm2_v4_distance_sq_f32(lm2_v4_f32 a, lm2_v4_f32 b);

// =============================================================================
// Normalize (returns unit vector in same direction)
// =============================================================================

// 2D normalize
LM2_API lm2_v2_f64 lm2_v2_normalize_f64(lm2_v2_f64 v);
LM2_API lm2_v2_f32 lm2_v2_normalize_f32(lm2_v2_f32 v);

// 3D normalize
LM2_API lm2_v3_f64 lm2_v3_normalize_f64(lm2_v3_f64 v);
LM2_API lm2_v3_f32 lm2_v3_normalize_f32(lm2_v3_f32 v);

// 4D normalize
LM2_API lm2_v4_f64 lm2_v4_normalize_f64(lm2_v4_f64 v);
LM2_API lm2_v4_f32 lm2_v4_normalize_f32(lm2_v4_f32 v);

// =============================================================================
// Angle Between Vectors (in radians)
// =============================================================================

// 2D angle
LM2_API double lm2_v2_angle_f64(lm2_v2_f64 a, lm2_v2_f64 b);
LM2_API float lm2_v2_angle_f32(lm2_v2_f32 a, lm2_v2_f32 b);

// 3D angle
LM2_API double lm2_v3_angle_f64(lm2_v3_f64 a, lm2_v3_f64 b);
LM2_API float lm2_v3_angle_f32(lm2_v3_f32 a, lm2_v3_f32 b);

// =============================================================================
// 2D Rotation
// =============================================================================

// Rotate 2D vector by angle (in radians)
LM2_API lm2_v2_f64 lm2_v2_rotate_f64(lm2_v2_f64 v, double angle);
LM2_API lm2_v2_f32 lm2_v2_rotate_f32(lm2_v2_f32 v, float angle);

// Rotate 2D vector around a point by angle (in radians)
LM2_API lm2_v2_f64 lm2_v2_rotate_around_f64(lm2_v2_f64 v, lm2_v2_f64 point, double angle);
LM2_API lm2_v2_f32 lm2_v2_rotate_around_f32(lm2_v2_f32 v, lm2_v2_f32 point, float angle);

// =============================================================================
// 2D Perpendicular Vectors
// =============================================================================

// Perpendicular vector (90 degrees counter-clockwise)
LM2_API lm2_v2_f64 lm2_v2_perp_ccw_f64(lm2_v2_f64 v);
LM2_API lm2_v2_f32 lm2_v2_perp_ccw_f32(lm2_v2_f32 v);
LM2_API lm2_v2_i64 lm2_v2_perp_ccw_i64(lm2_v2_i64 v);
LM2_API lm2_v2_i32 lm2_v2_perp_ccw_i32(lm2_v2_i32 v);
LM2_API lm2_v2_i16 lm2_v2_perp_ccw_i16(lm2_v2_i16 v);
LM2_API lm2_v2_i8 lm2_v2_perp_ccw_i8(lm2_v2_i8 v);

// Perpendicular vector (90 degrees clockwise)
LM2_API lm2_v2_f64 lm2_v2_perp_cw_f64(lm2_v2_f64 v);
LM2_API lm2_v2_f32 lm2_v2_perp_cw_f32(lm2_v2_f32 v);
LM2_API lm2_v2_i64 lm2_v2_perp_cw_i64(lm2_v2_i64 v);
LM2_API lm2_v2_i32 lm2_v2_perp_cw_i32(lm2_v2_i32 v);
LM2_API lm2_v2_i16 lm2_v2_perp_cw_i16(lm2_v2_i16 v);
LM2_API lm2_v2_i8 lm2_v2_perp_cw_i8(lm2_v2_i8 v);

// =============================================================================
// Reflection
// =============================================================================

// Reflect vector across a normal
LM2_API lm2_v2_f64 lm2_v2_reflect_f64(lm2_v2_f64 v, lm2_v2_f64 normal);
LM2_API lm2_v2_f32 lm2_v2_reflect_f32(lm2_v2_f32 v, lm2_v2_f32 normal);
LM2_API lm2_v3_f64 lm2_v3_reflect_f64(lm2_v3_f64 v, lm2_v3_f64 normal);
LM2_API lm2_v3_f32 lm2_v3_reflect_f32(lm2_v3_f32 v, lm2_v3_f32 normal);

// =============================================================================
// Projection
// =============================================================================

// Project vector a onto vector b
LM2_API lm2_v2_f64 lm2_v2_project_f64(lm2_v2_f64 a, lm2_v2_f64 b);
LM2_API lm2_v2_f32 lm2_v2_project_f32(lm2_v2_f32 a, lm2_v2_f32 b);
LM2_API lm2_v3_f64 lm2_v3_project_f64(lm2_v3_f64 a, lm2_v3_f64 b);
LM2_API lm2_v3_f32 lm2_v3_project_f32(lm2_v3_f32 a, lm2_v3_f32 b);

// #############################################################################
LM2_HEADER_END;
// #############################################################################
