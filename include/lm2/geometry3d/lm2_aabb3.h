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
#include "lm2/ranges/lm2_range3.h"
#include "lm2/vectors/lm2_vector3.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// AABB3 Type Aliases
// =============================================================================
// AABB3 is an axis-aligned 3D box, represented by lm2_range3 (AABB)

typedef lm2_r3_f64 lm2_aabb3_f64;
typedef lm2_r3_f32 lm2_aabb3_f32;
typedef lm2_r3_i64 lm2_aabb3_i64;
typedef lm2_r3_i32 lm2_aabb3_i32;
typedef lm2_r3_i16 lm2_aabb3_i16;
typedef lm2_r3_i8 lm2_aabb3_i8;
typedef lm2_r3_u64 lm2_aabb3_u64;
typedef lm2_r3_u32 lm2_aabb3_u32;
typedef lm2_r3_u16 lm2_aabb3_u16;
typedef lm2_r3_u8 lm2_aabb3_u8;

// Default aabb3 type
typedef lm2_r3_f32 lm2_aabb3;

// =============================================================================
// AABB3 Corner Enumeration
// =============================================================================

typedef enum lm2_corner3 {
  LM2_CORNER3_MIN_MIN_MIN = 0,  // (min.x, min.y, min.z)
  LM2_CORNER3_MIN_MIN_MAX = 1,  // (min.x, min.y, max.z)
  LM2_CORNER3_MIN_MAX_MIN = 2,  // (min.x, max.y, min.z)
  LM2_CORNER3_MIN_MAX_MAX = 3,  // (min.x, max.y, max.z)
  LM2_CORNER3_MAX_MIN_MIN = 4,  // (max.x, min.y, min.z)
  LM2_CORNER3_MAX_MIN_MAX = 5,  // (max.x, min.y, max.z)
  LM2_CORNER3_MAX_MAX_MIN = 6,  // (max.x, max.y, min.z)
  LM2_CORNER3_MAX_MAX_MAX = 7,  // (max.x, max.y, max.z)
} lm2_corner3;

typedef enum lm2_aabb3_face {
  LM2_AABB3_FACE_FRONT,   // +Z
  LM2_AABB3_FACE_BACK,    // -Z
  LM2_AABB3_FACE_LEFT,    // -X
  LM2_AABB3_FACE_RIGHT,   // +X
  LM2_AABB3_FACE_TOP,     // +Y
  LM2_AABB3_FACE_BOTTOM,  // -Y
} lm2_aabb3_face;

// =============================================================================
// Construction Helpers (using range3 functions)
// =============================================================================
// Note: Most construction is already provided by lm2_range3
// These are convenient wrappers for aabb3-specific clarity

LM2_API lm2_aabb3_f64 lm2_aabb3_from_min_max_f64(lm2_v3_f64 min, lm2_v3_f64 max);
LM2_API lm2_aabb3_f32 lm2_aabb3_from_min_max_f32(lm2_v3_f32 min, lm2_v3_f32 max);

LM2_API lm2_aabb3_f64 lm2_aabb3_from_center_size_f64(lm2_v3_f64 center, lm2_v3_f64 size);
LM2_API lm2_aabb3_f32 lm2_aabb3_from_center_size_f32(lm2_v3_f32 center, lm2_v3_f32 size);

LM2_API lm2_aabb3_f64 lm2_aabb3_from_center_extents_f64(lm2_v3_f64 center, lm2_v3_f64 extents);
LM2_API lm2_aabb3_f32 lm2_aabb3_from_center_extents_f32(lm2_v3_f32 center, lm2_v3_f32 extents);

LM2_API lm2_aabb3_f64 lm2_aabb3_from_position_size_f64(lm2_v3_f64 pos, lm2_v3_f64 size);
LM2_API lm2_aabb3_f32 lm2_aabb3_from_position_size_f32(lm2_v3_f32 pos, lm2_v3_f32 size);

// Create a unit aabb3 (0,0,0) to (1,1,1)
LM2_API lm2_aabb3_f64 lm2_aabb3_unit_f64(void);
LM2_API lm2_aabb3_f32 lm2_aabb3_unit_f32(void);

// =============================================================================
// AABB3 Properties (additional to range3)
// =============================================================================

// Get the surface area of an aabb3
LM2_API double lm2_aabb3_surface_area_f64(lm2_aabb3_f64 aabb3);
LM2_API float lm2_aabb3_surface_area_f32(lm2_aabb3_f32 aabb3);

// Get the length of the diagonal
LM2_API double lm2_aabb3_diagonal_f64(lm2_aabb3_f64 aabb3);
LM2_API float lm2_aabb3_diagonal_f32(lm2_aabb3_f32 aabb3);

// Get width (x extent), height (y extent), depth (z extent)
LM2_API double lm2_aabb3_width_f64(lm2_aabb3_f64 aabb3);
LM2_API float lm2_aabb3_width_f32(lm2_aabb3_f32 aabb3);

LM2_API double lm2_aabb3_height_f64(lm2_aabb3_f64 aabb3);
LM2_API float lm2_aabb3_height_f32(lm2_aabb3_f32 aabb3);

LM2_API double lm2_aabb3_depth_f64(lm2_aabb3_f64 aabb3);
LM2_API float lm2_aabb3_depth_f32(lm2_aabb3_f32 aabb3);

// =============================================================================
// AABB3 Corner Operations
// =============================================================================

// Get a specific corner by enum
LM2_API lm2_v3_f64 lm2_aabb3_get_corner_f64(lm2_aabb3_f64 aabb3, lm2_corner3 corner);
LM2_API lm2_v3_f32 lm2_aabb3_get_corner_f32(lm2_aabb3_f32 aabb3, lm2_corner3 corner);

// Get all 8 corners of the aabb3
LM2_API void lm2_aabb3_get_corners_f64(lm2_aabb3_f64 aabb3, lm2_v3_f64 corners[8]);
LM2_API void lm2_aabb3_get_corners_f32(lm2_aabb3_f32 aabb3, lm2_v3_f32 corners[8]);

// =============================================================================
// AABB3 Face Operations
// =============================================================================

// Get the center point of a face
LM2_API lm2_v3_f64 lm2_aabb3_face_center_f64(lm2_aabb3_f64 aabb3, lm2_aabb3_face face);
LM2_API lm2_v3_f32 lm2_aabb3_face_center_f32(lm2_aabb3_f32 aabb3, lm2_aabb3_face face);

// Get the normal of a face
LM2_API lm2_v3_f64 lm2_aabb3_face_normal_f64(lm2_aabb3_face face);
LM2_API lm2_v3_f32 lm2_aabb3_face_normal_f32(lm2_aabb3_face face);

// =============================================================================
// AABB3 Tests (using range3 functions)
// =============================================================================

LM2_API int lm2_aabb3_contains_point_f64(lm2_aabb3_f64 aabb3, lm2_v3_f64 point);
LM2_API int lm2_aabb3_contains_point_f32(lm2_aabb3_f32 aabb3, lm2_v3_f32 point);

LM2_API int lm2_aabb3_overlaps_f64(lm2_aabb3_f64 a, lm2_aabb3_f64 b);
LM2_API int lm2_aabb3_overlaps_f32(lm2_aabb3_f32 a, lm2_aabb3_f32 b);

// =============================================================================
// AABB3 Transformations (using range3 functions)
// =============================================================================

LM2_API lm2_aabb3_f64 lm2_aabb3_translate_f64(lm2_aabb3_f64 aabb3, lm2_v3_f64 offset);
LM2_API lm2_aabb3_f32 lm2_aabb3_translate_f32(lm2_aabb3_f32 aabb3, lm2_v3_f32 offset);

LM2_API lm2_aabb3_f64 lm2_aabb3_scale_f64(lm2_aabb3_f64 aabb3, lm2_v3_f64 scale);
LM2_API lm2_aabb3_f32 lm2_aabb3_scale_f32(lm2_aabb3_f32 aabb3, lm2_v3_f32 scale);

LM2_API lm2_aabb3_f64 lm2_aabb3_expand_f64(lm2_aabb3_f64 aabb3, lm2_v3_f64 amount);
LM2_API lm2_aabb3_f32 lm2_aabb3_expand_f32(lm2_aabb3_f32 aabb3, lm2_v3_f32 amount);

// #############################################################################
LM2_HEADER_END;
// #############################################################################
// Note: C++ operators are defined in lm2_range3.h since aabb3s are range3 types
