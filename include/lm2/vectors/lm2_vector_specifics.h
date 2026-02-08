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
LM2_API double lm2_dot_v2f64(lm2_v2f64 a, lm2_v2f64 b);
LM2_API float lm2_dot_v2f32(lm2_v2f32 a, lm2_v2f32 b);
LM2_API int64_t lm2_dot_v2i64(lm2_v2i64 a, lm2_v2i64 b);
LM2_API int32_t lm2_dot_v2i32(lm2_v2i32 a, lm2_v2i32 b);
LM2_API int16_t lm2_dot_v2i16(lm2_v2i16 a, lm2_v2i16 b);
LM2_API int8_t lm2_dot_v2i8(lm2_v2i8 a, lm2_v2i8 b);

// 3D dot product
LM2_API double lm2_dot_v3f64(lm2_v3f64 a, lm2_v3f64 b);
LM2_API float lm2_dot_v3f32(lm2_v3f32 a, lm2_v3f32 b);
LM2_API int64_t lm2_dot_v3i64(lm2_v3i64 a, lm2_v3i64 b);
LM2_API int32_t lm2_dot_v3i32(lm2_v3i32 a, lm2_v3i32 b);
LM2_API int16_t lm2_dot_v3i16(lm2_v3i16 a, lm2_v3i16 b);
LM2_API int8_t lm2_dot_v3i8(lm2_v3i8 a, lm2_v3i8 b);

// 4D dot product
LM2_API double lm2_dot_v4f64(lm2_v4f64 a, lm2_v4f64 b);
LM2_API float lm2_dot_v4f32(lm2_v4f32 a, lm2_v4f32 b);
LM2_API int64_t lm2_dot_v4i64(lm2_v4i64 a, lm2_v4i64 b);
LM2_API int32_t lm2_dot_v4i32(lm2_v4i32 a, lm2_v4i32 b);
LM2_API int16_t lm2_dot_v4i16(lm2_v4i16 a, lm2_v4i16 b);
LM2_API int8_t lm2_dot_v4i8(lm2_v4i8 a, lm2_v4i8 b);

// =============================================================================
// Cross Product (3D only)
// =============================================================================

LM2_API lm2_v3f64 lm2_cross_v3f64(lm2_v3f64 a, lm2_v3f64 b);
LM2_API lm2_v3f32 lm2_cross_v3f32(lm2_v3f32 a, lm2_v3f32 b);
LM2_API lm2_v3i64 lm2_cross_v3i64(lm2_v3i64 a, lm2_v3i64 b);
LM2_API lm2_v3i32 lm2_cross_v3i32(lm2_v3i32 a, lm2_v3i32 b);
LM2_API lm2_v3i16 lm2_cross_v3i16(lm2_v3i16 a, lm2_v3i16 b);
LM2_API lm2_v3i8 lm2_cross_v3i8(lm2_v3i8 a, lm2_v3i8 b);

// =============================================================================
// 2D Cross Product (returns scalar: a.x * b.y - a.y * b.x)
// =============================================================================

LM2_API double lm2_cross_v2f64(lm2_v2f64 a, lm2_v2f64 b);
LM2_API float lm2_cross_v2f32(lm2_v2f32 a, lm2_v2f32 b);
LM2_API int64_t lm2_cross_v2i64(lm2_v2i64 a, lm2_v2i64 b);
LM2_API int32_t lm2_cross_v2i32(lm2_v2i32 a, lm2_v2i32 b);
LM2_API int16_t lm2_cross_v2i16(lm2_v2i16 a, lm2_v2i16 b);
LM2_API int8_t lm2_cross_v2i8(lm2_v2i8 a, lm2_v2i8 b);

// =============================================================================
// 2D Cross Product for Turn Detection (3-point version)
// Returns scalar for determining turn direction:
// > 0: Left turn (counterclockwise)
// < 0: Right turn (clockwise)
// = 0: Collinear (points on same line)
// =============================================================================

LM2_API double lm2_cross3_v2f64(lm2_v2f64 a, lm2_v2f64 b, lm2_v2f64 c);
LM2_API float lm2_cross3_v2f32(lm2_v2f32 a, lm2_v2f32 b, lm2_v2f32 c);
LM2_API int64_t lm2_cross3_v2i64(lm2_v2i64 a, lm2_v2i64 b, lm2_v2i64 c);
LM2_API int32_t lm2_cross3_v2i32(lm2_v2i32 a, lm2_v2i32 b, lm2_v2i32 c);
LM2_API int16_t lm2_cross3_v2i16(lm2_v2i16 a, lm2_v2i16 b, lm2_v2i16 c);
LM2_API int8_t lm2_cross3_v2i8(lm2_v2i8 a, lm2_v2i8 b, lm2_v2i8 c);

// =============================================================================
// Length / Magnitude
// =============================================================================

// 2D length
LM2_API double lm2_length_v2f64(lm2_v2f64 v);
LM2_API float lm2_length_v2f32(lm2_v2f32 v);

// 3D length
LM2_API double lm2_length_v3f64(lm2_v3f64 v);
LM2_API float lm2_length_v3f32(lm2_v3f32 v);

// 4D length
LM2_API double lm2_length_v4f64(lm2_v4f64 v);
LM2_API float lm2_length_v4f32(lm2_v4f32 v);

// =============================================================================
// Length Squared (faster than length, no sqrt)
// =============================================================================

// 2D length squared
LM2_API double lm2_length_sq_v2f64(lm2_v2f64 v);
LM2_API float lm2_length_sq_v2f32(lm2_v2f32 v);

// 3D length squared
LM2_API double lm2_length_sq_v3f64(lm2_v3f64 v);
LM2_API float lm2_length_sq_v3f32(lm2_v3f32 v);

// 4D length squared
LM2_API double lm2_length_sq_v4f64(lm2_v4f64 v);
LM2_API float lm2_length_sq_v4f32(lm2_v4f32 v);

// =============================================================================
// Distance
// =============================================================================

// 2D distance
LM2_API double lm2_distance_v2f64(lm2_v2f64 a, lm2_v2f64 b);
LM2_API float lm2_distance_v2f32(lm2_v2f32 a, lm2_v2f32 b);

// 3D distance
LM2_API double lm2_distance_v3f64(lm2_v3f64 a, lm2_v3f64 b);
LM2_API float lm2_distance_v3f32(lm2_v3f32 a, lm2_v3f32 b);

// 4D distance
LM2_API double lm2_distance_v4f64(lm2_v4f64 a, lm2_v4f64 b);
LM2_API float lm2_distance_v4f32(lm2_v4f32 a, lm2_v4f32 b);

// =============================================================================
// Distance Squared (faster than distance, no sqrt)
// =============================================================================

// 2D distance squared
LM2_API double lm2_distance_sq_v2f64(lm2_v2f64 a, lm2_v2f64 b);
LM2_API float lm2_distance_sq_v2f32(lm2_v2f32 a, lm2_v2f32 b);

// 3D distance squared
LM2_API double lm2_distance_sq_v3f64(lm2_v3f64 a, lm2_v3f64 b);
LM2_API float lm2_distance_sq_v3f32(lm2_v3f32 a, lm2_v3f32 b);

// 4D distance squared
LM2_API double lm2_distance_sq_v4f64(lm2_v4f64 a, lm2_v4f64 b);
LM2_API float lm2_distance_sq_v4f32(lm2_v4f32 a, lm2_v4f32 b);

// =============================================================================
// Normalize (returns unit vector in same direction)
// =============================================================================

// 2D normalize
LM2_API lm2_v2f64 lm2_normalize_v2f64(lm2_v2f64 v);
LM2_API lm2_v2f32 lm2_normalize_v2f32(lm2_v2f32 v);

// 3D normalize
LM2_API lm2_v3f64 lm2_normalize_v3f64(lm2_v3f64 v);
LM2_API lm2_v3f32 lm2_normalize_v3f32(lm2_v3f32 v);

// 4D normalize
LM2_API lm2_v4f64 lm2_normalize_v4f64(lm2_v4f64 v);
LM2_API lm2_v4f32 lm2_normalize_v4f32(lm2_v4f32 v);

// =============================================================================
// Angle Between Vectors (in radians)
// =============================================================================

// 2D angle
LM2_API double lm2_angle_v2f64(lm2_v2f64 a, lm2_v2f64 b);
LM2_API float lm2_angle_v2f32(lm2_v2f32 a, lm2_v2f32 b);

// 3D angle
LM2_API double lm2_angle_v3f64(lm2_v3f64 a, lm2_v3f64 b);
LM2_API float lm2_angle_v3f32(lm2_v3f32 a, lm2_v3f32 b);

// =============================================================================
// 2D Rotation
// =============================================================================

// Rotate 2D vector by angle (in radians)
LM2_API lm2_v2f64 lm2_rotate_v2f64(lm2_v2f64 v, double angle);
LM2_API lm2_v2f32 lm2_rotate_v2f32(lm2_v2f32 v, float angle);

// Rotate 2D vector around a point by angle (in radians)
LM2_API lm2_v2f64 lm2_rotate_around_v2f64(lm2_v2f64 v, lm2_v2f64 point, double angle);
LM2_API lm2_v2f32 lm2_rotate_around_v2f32(lm2_v2f32 v, lm2_v2f32 point, float angle);

// =============================================================================
// 2D Perpendicular Vectors
// =============================================================================

// Perpendicular vector (90 degrees counter-clockwise)
LM2_API lm2_v2f64 lm2_perp_ccw_v2f64(lm2_v2f64 v);
LM2_API lm2_v2f32 lm2_perp_ccw_v2f32(lm2_v2f32 v);
LM2_API lm2_v2i64 lm2_perp_ccw_v2i64(lm2_v2i64 v);
LM2_API lm2_v2i32 lm2_perp_ccw_v2i32(lm2_v2i32 v);
LM2_API lm2_v2i16 lm2_perp_ccw_v2i16(lm2_v2i16 v);
LM2_API lm2_v2i8 lm2_perp_ccw_v2i8(lm2_v2i8 v);

// Perpendicular vector (90 degrees clockwise)
LM2_API lm2_v2f64 lm2_perp_cw_v2f64(lm2_v2f64 v);
LM2_API lm2_v2f32 lm2_perp_cw_v2f32(lm2_v2f32 v);
LM2_API lm2_v2i64 lm2_perp_cw_v2i64(lm2_v2i64 v);
LM2_API lm2_v2i32 lm2_perp_cw_v2i32(lm2_v2i32 v);
LM2_API lm2_v2i16 lm2_perp_cw_v2i16(lm2_v2i16 v);
LM2_API lm2_v2i8 lm2_perp_cw_v2i8(lm2_v2i8 v);

// =============================================================================
// Reflection
// =============================================================================

// Reflect vector across a normal
LM2_API lm2_v2f64 lm2_reflect_v2f64(lm2_v2f64 v, lm2_v2f64 normal);
LM2_API lm2_v2f32 lm2_reflect_v2f32(lm2_v2f32 v, lm2_v2f32 normal);
LM2_API lm2_v3f64 lm2_reflect_v3f64(lm2_v3f64 v, lm2_v3f64 normal);
LM2_API lm2_v3f32 lm2_reflect_v3f32(lm2_v3f32 v, lm2_v3f32 normal);

// =============================================================================
// Projection
// =============================================================================

// Project vector a onto vector b
LM2_API lm2_v2f64 lm2_project_v2f64(lm2_v2f64 a, lm2_v2f64 b);
LM2_API lm2_v2f32 lm2_project_v2f32(lm2_v2f32 a, lm2_v2f32 b);
LM2_API lm2_v3f64 lm2_project_v3f64(lm2_v3f64 a, lm2_v3f64 b);
LM2_API lm2_v3f32 lm2_project_v3f32(lm2_v3f32 a, lm2_v3f32 b);

// =============================================================================
// Generic Macros
// =============================================================================

#ifndef LM2_NO_GENERICS
#  include "lm2_vector_generics.h"
#  define lm2_dot(...)           _LM2_GENERIC_VALL(lm2_dot, __VA_ARGS__)
#  define lm2_cross(...)         _LM2_GENERIC_V3(lm2_cross, __VA_ARGS__)
#  define lm2_cross2d(...)       _LM2_GENERIC_V2(lm2_cross2d, __VA_ARGS__)
#  define lm2_cross_tri(...)     _LM2_GENERIC_V2(lm2_cross_tri, __VA_ARGS__)
#  define lm2_length(...)        _LM2_GENERIC_VF(lm2_length, __VA_ARGS__)
#  define lm2_length_sq(...)     _LM2_GENERIC_VF(lm2_length_sq, __VA_ARGS__)
#  define lm2_distance(...)      _LM2_GENERIC_VF(lm2_distance, __VA_ARGS__)
#  define lm2_distance_sq(...)   _LM2_GENERIC_VF(lm2_distance_sq, __VA_ARGS__)
#  define lm2_normalize(...)     _LM2_GENERIC_VF(lm2_normalize, __VA_ARGS__)
#  define lm2_angle(...)         _LM2_GENERIC_V23F(lm2_angle, __VA_ARGS__)
#  define lm2_rotate(...)        _LM2_GENERIC_V2(lm2_rotate, __VA_ARGS__)
#  define lm2_rotate_around(...) _LM2_GENERIC_V2(lm2_rotate_around, __VA_ARGS__)
#  define lm2_perp_ccw(...)      _LM2_GENERIC_V2(lm2_perp_ccw, __VA_ARGS__)
#  define lm2_perp_cw(...)       _LM2_GENERIC_V2(lm2_perp_cw, __VA_ARGS__)
#  define lm2_reflect(...)       _LM2_GENERIC_V23F(lm2_reflect, __VA_ARGS__)
#  define lm2_project(...)       _LM2_GENERIC_V23F(lm2_project, __VA_ARGS__)
#endif

// #############################################################################
LM2_HEADER_END;
// #############################################################################
