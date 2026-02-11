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

#include <lm2/geometry3d/lm2_aabb3.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/vectors/lm2_vector_specifics.h>

// =============================================================================
// Construction Helpers
// =============================================================================

LM2_API lm2_aabb3_f64 lm2_aabb3_unit_f64(void) {
  lm2_aabb3_f64 aabb3;
  aabb3.min.x = 0.0;
  aabb3.min.y = 0.0;
  aabb3.min.z = 0.0;
  aabb3.max.x = 1.0;
  aabb3.max.y = 1.0;
  aabb3.max.z = 1.0;
  return aabb3;
}

LM2_API lm2_aabb3_f32 lm2_aabb3_unit_f32(void) {
  lm2_aabb3_f32 aabb3;
  aabb3.min.x = 0.0f;
  aabb3.min.y = 0.0f;
  aabb3.min.z = 0.0f;
  aabb3.max.x = 1.0f;
  aabb3.max.y = 1.0f;
  aabb3.max.z = 1.0f;
  return aabb3;
}

// =============================================================================
// Construction Wrappers
// =============================================================================

LM2_API lm2_aabb3_f64 lm2_aabb3_from_min_max_f64(lm2_v3_f64 min, lm2_v3_f64 max) {
  return lm2_r3_from_min_max_f64(min, max);
}

LM2_API lm2_aabb3_f32 lm2_aabb3_from_min_max_f32(lm2_v3_f32 min, lm2_v3_f32 max) {
  return lm2_r3_from_min_max_f32(min, max);
}

LM2_API lm2_aabb3_f64 lm2_aabb3_from_center_size_f64(lm2_v3_f64 center, lm2_v3_f64 size) {
  return lm2_r3_from_center_size_f64(center, size);
}

LM2_API lm2_aabb3_f32 lm2_aabb3_from_center_size_f32(lm2_v3_f32 center, lm2_v3_f32 size) {
  return lm2_r3_from_center_size_f32(center, size);
}

LM2_API lm2_aabb3_f64 lm2_aabb3_from_center_extents_f64(lm2_v3_f64 center, lm2_v3_f64 extents) {
  return lm2_r3_from_center_extents_f64(center, extents);
}

LM2_API lm2_aabb3_f32 lm2_aabb3_from_center_extents_f32(lm2_v3_f32 center, lm2_v3_f32 extents) {
  return lm2_r3_from_center_extents_f32(center, extents);
}

LM2_API lm2_aabb3_f64 lm2_aabb3_from_position_size_f64(lm2_v3_f64 pos, lm2_v3_f64 size) {
  return lm2_r3_from_position_size_f64(pos, size);
}

LM2_API lm2_aabb3_f32 lm2_aabb3_from_position_size_f32(lm2_v3_f32 pos, lm2_v3_f32 size) {
  return lm2_r3_from_position_size_f32(pos, size);
}

// =============================================================================
// AABB3 Properties
// =============================================================================

LM2_API double lm2_aabb3_surface_area_f64(lm2_aabb3_f64 aabb3) {
  // Surface Area = 2(wh + wd + hd) where w=width, h=height, d=depth
  double width = lm2_sub_f64(aabb3.max.x, aabb3.min.x);
  double height = lm2_sub_f64(aabb3.max.y, aabb3.min.y);
  double depth = lm2_sub_f64(aabb3.max.z, aabb3.min.z);

  double wh = lm2_mul_f64(width, height);
  double wd = lm2_mul_f64(width, depth);
  double hd = lm2_mul_f64(height, depth);

  double sum = lm2_add_f64(lm2_add_f64(wh, wd), hd);
  return lm2_mul_f64(2.0, sum);
}

LM2_API float lm2_aabb3_surface_area_f32(lm2_aabb3_f32 aabb3) {
  // Surface Area = 2(wh + wd + hd) where w=width, h=height, d=depth
  float width = lm2_sub_f32(aabb3.max.x, aabb3.min.x);
  float height = lm2_sub_f32(aabb3.max.y, aabb3.min.y);
  float depth = lm2_sub_f32(aabb3.max.z, aabb3.min.z);

  float wh = lm2_mul_f32(width, height);
  float wd = lm2_mul_f32(width, depth);
  float hd = lm2_mul_f32(height, depth);

  float sum = lm2_add_f32(lm2_add_f32(wh, wd), hd);
  return lm2_mul_f32(2.0f, sum);
}

LM2_API double lm2_aabb3_diagonal_f64(lm2_aabb3_f64 aabb3) {
  // Diagonal = sqrt((max.x - min.x)² + (max.y - min.y)² + (max.z - min.z)²)
  lm2_v3_f64 size = lm2_v3_sub_f64(aabb3.max, aabb3.min);
  return lm2_v3_length_f64(size);
}

LM2_API float lm2_aabb3_diagonal_f32(lm2_aabb3_f32 aabb3) {
  // Diagonal = sqrt((max.x - min.x)² + (max.y - min.y)² + (max.z - min.z)²)
  lm2_v3_f32 size = lm2_v3_sub_f32(aabb3.max, aabb3.min);
  return lm2_v3_length_f32(size);
}

LM2_API double lm2_aabb3_width_f64(lm2_aabb3_f64 aabb3) {
  return lm2_sub_f64(aabb3.max.x, aabb3.min.x);
}

LM2_API float lm2_aabb3_width_f32(lm2_aabb3_f32 aabb3) {
  return lm2_sub_f32(aabb3.max.x, aabb3.min.x);
}

LM2_API double lm2_aabb3_height_f64(lm2_aabb3_f64 aabb3) {
  return lm2_sub_f64(aabb3.max.y, aabb3.min.y);
}

LM2_API float lm2_aabb3_height_f32(lm2_aabb3_f32 aabb3) {
  return lm2_sub_f32(aabb3.max.y, aabb3.min.y);
}

LM2_API double lm2_aabb3_depth_f64(lm2_aabb3_f64 aabb3) {
  return lm2_sub_f64(aabb3.max.z, aabb3.min.z);
}

LM2_API float lm2_aabb3_depth_f32(lm2_aabb3_f32 aabb3) {
  return lm2_sub_f32(aabb3.max.z, aabb3.min.z);
}

// =============================================================================
// AABB3 Corner Operations
// =============================================================================

LM2_API lm2_v3_f64 lm2_aabb3_get_corner_f64(lm2_aabb3_f64 aabb3, lm2_corner3 corner) {
  lm2_v3_f64 result;

  switch (corner) {
    case LM2_CORNER3_MIN_MIN_MIN:
      result.x = aabb3.min.x;
      result.y = aabb3.min.y;
      result.z = aabb3.min.z;
      break;
    case LM2_CORNER3_MIN_MIN_MAX:
      result.x = aabb3.min.x;
      result.y = aabb3.min.y;
      result.z = aabb3.max.z;
      break;
    case LM2_CORNER3_MIN_MAX_MIN:
      result.x = aabb3.min.x;
      result.y = aabb3.max.y;
      result.z = aabb3.min.z;
      break;
    case LM2_CORNER3_MIN_MAX_MAX:
      result.x = aabb3.min.x;
      result.y = aabb3.max.y;
      result.z = aabb3.max.z;
      break;
    case LM2_CORNER3_MAX_MIN_MIN:
      result.x = aabb3.max.x;
      result.y = aabb3.min.y;
      result.z = aabb3.min.z;
      break;
    case LM2_CORNER3_MAX_MIN_MAX:
      result.x = aabb3.max.x;
      result.y = aabb3.min.y;
      result.z = aabb3.max.z;
      break;
    case LM2_CORNER3_MAX_MAX_MIN:
      result.x = aabb3.max.x;
      result.y = aabb3.max.y;
      result.z = aabb3.min.z;
      break;
    case LM2_CORNER3_MAX_MAX_MAX:
      result.x = aabb3.max.x;
      result.y = aabb3.max.y;
      result.z = aabb3.max.z;
      break;
    default:
      LM2_ASSERT(false && "Invalid corner enum");
      result.x = 0.0;
      result.y = 0.0;
      result.z = 0.0;
      break;
  }

  return result;
}

LM2_API lm2_v3_f32 lm2_aabb3_get_corner_f32(lm2_aabb3_f32 aabb3, lm2_corner3 corner) {
  lm2_v3_f32 result;

  switch (corner) {
    case LM2_CORNER3_MIN_MIN_MIN:
      result.x = aabb3.min.x;
      result.y = aabb3.min.y;
      result.z = aabb3.min.z;
      break;
    case LM2_CORNER3_MIN_MIN_MAX:
      result.x = aabb3.min.x;
      result.y = aabb3.min.y;
      result.z = aabb3.max.z;
      break;
    case LM2_CORNER3_MIN_MAX_MIN:
      result.x = aabb3.min.x;
      result.y = aabb3.max.y;
      result.z = aabb3.min.z;
      break;
    case LM2_CORNER3_MIN_MAX_MAX:
      result.x = aabb3.min.x;
      result.y = aabb3.max.y;
      result.z = aabb3.max.z;
      break;
    case LM2_CORNER3_MAX_MIN_MIN:
      result.x = aabb3.max.x;
      result.y = aabb3.min.y;
      result.z = aabb3.min.z;
      break;
    case LM2_CORNER3_MAX_MIN_MAX:
      result.x = aabb3.max.x;
      result.y = aabb3.min.y;
      result.z = aabb3.max.z;
      break;
    case LM2_CORNER3_MAX_MAX_MIN:
      result.x = aabb3.max.x;
      result.y = aabb3.max.y;
      result.z = aabb3.min.z;
      break;
    case LM2_CORNER3_MAX_MAX_MAX:
      result.x = aabb3.max.x;
      result.y = aabb3.max.y;
      result.z = aabb3.max.z;
      break;
    default:
      LM2_ASSERT(false && "Invalid corner enum");
      result.x = 0.0f;
      result.y = 0.0f;
      result.z = 0.0f;
      break;
  }

  return result;
}

LM2_API void lm2_aabb3_get_corners_f64(lm2_aabb3_f64 aabb3, lm2_v3_f64 corners[8]) {
  LM2_ASSERT(corners != NULL);

  for (int i = 0; i < 8; i++) {
    corners[i] = lm2_aabb3_get_corner_f64(aabb3, (lm2_corner3)i);
  }
}

LM2_API void lm2_aabb3_get_corners_f32(lm2_aabb3_f32 aabb3, lm2_v3_f32 corners[8]) {
  LM2_ASSERT(corners != NULL);

  for (int i = 0; i < 8; i++) {
    corners[i] = lm2_aabb3_get_corner_f32(aabb3, (lm2_corner3)i);
  }
}

// =============================================================================
// AABB3 Face Operations
// =============================================================================

LM2_API lm2_v3_f64 lm2_aabb3_face_center_f64(lm2_aabb3_f64 aabb3, lm2_aabb3_face face) {
  lm2_v3_f64 result;
  lm2_v3_f64 center = lm2_r3_center_f64(aabb3);

  switch (face) {
    case LM2_AABB3_FACE_FRONT:  // +Z
      result.x = center.x;
      result.y = center.y;
      result.z = aabb3.max.z;
      break;
    case LM2_AABB3_FACE_BACK:  // -Z
      result.x = center.x;
      result.y = center.y;
      result.z = aabb3.min.z;
      break;
    case LM2_AABB3_FACE_LEFT:  // -X
      result.x = aabb3.min.x;
      result.y = center.y;
      result.z = center.z;
      break;
    case LM2_AABB3_FACE_RIGHT:  // +X
      result.x = aabb3.max.x;
      result.y = center.y;
      result.z = center.z;
      break;
    case LM2_AABB3_FACE_TOP:  // +Y
      result.x = center.x;
      result.y = aabb3.max.y;
      result.z = center.z;
      break;
    case LM2_AABB3_FACE_BOTTOM:  // -Y
      result.x = center.x;
      result.y = aabb3.min.y;
      result.z = center.z;
      break;
    default:
      LM2_ASSERT(false && "Invalid face enum");
      result = center;
      break;
  }

  return result;
}

LM2_API lm2_v3_f32 lm2_aabb3_face_center_f32(lm2_aabb3_f32 aabb3, lm2_aabb3_face face) {
  lm2_v3_f32 result;
  lm2_v3_f32 center = lm2_r3_center_f32(aabb3);

  switch (face) {
    case LM2_AABB3_FACE_FRONT:  // +Z
      result.x = center.x;
      result.y = center.y;
      result.z = aabb3.max.z;
      break;
    case LM2_AABB3_FACE_BACK:  // -Z
      result.x = center.x;
      result.y = center.y;
      result.z = aabb3.min.z;
      break;
    case LM2_AABB3_FACE_LEFT:  // -X
      result.x = aabb3.min.x;
      result.y = center.y;
      result.z = center.z;
      break;
    case LM2_AABB3_FACE_RIGHT:  // +X
      result.x = aabb3.max.x;
      result.y = center.y;
      result.z = center.z;
      break;
    case LM2_AABB3_FACE_TOP:  // +Y
      result.x = center.x;
      result.y = aabb3.max.y;
      result.z = center.z;
      break;
    case LM2_AABB3_FACE_BOTTOM:  // -Y
      result.x = center.x;
      result.y = aabb3.min.y;
      result.z = center.z;
      break;
    default:
      LM2_ASSERT(false && "Invalid face enum");
      result = center;
      break;
  }

  return result;
}

LM2_API lm2_v3_f64 lm2_aabb3_face_normal_f64(lm2_aabb3_face face) {
  lm2_v3_f64 normal;

  switch (face) {
    case LM2_AABB3_FACE_FRONT:  // +Z
      normal.x = 0.0;
      normal.y = 0.0;
      normal.z = 1.0;
      break;
    case LM2_AABB3_FACE_BACK:  // -Z
      normal.x = 0.0;
      normal.y = 0.0;
      normal.z = -1.0;
      break;
    case LM2_AABB3_FACE_LEFT:  // -X
      normal.x = -1.0;
      normal.y = 0.0;
      normal.z = 0.0;
      break;
    case LM2_AABB3_FACE_RIGHT:  // +X
      normal.x = 1.0;
      normal.y = 0.0;
      normal.z = 0.0;
      break;
    case LM2_AABB3_FACE_TOP:  // +Y
      normal.x = 0.0;
      normal.y = 1.0;
      normal.z = 0.0;
      break;
    case LM2_AABB3_FACE_BOTTOM:  // -Y
      normal.x = 0.0;
      normal.y = -1.0;
      normal.z = 0.0;
      break;
    default:
      LM2_ASSERT(false && "Invalid face enum");
      normal.x = 0.0;
      normal.y = 0.0;
      normal.z = 0.0;
      break;
  }

  return normal;
}

LM2_API lm2_v3_f32 lm2_aabb3_face_normal_f32(lm2_aabb3_face face) {
  lm2_v3_f32 normal;

  switch (face) {
    case LM2_AABB3_FACE_FRONT:  // +Z
      normal.x = 0.0f;
      normal.y = 0.0f;
      normal.z = 1.0f;
      break;
    case LM2_AABB3_FACE_BACK:  // -Z
      normal.x = 0.0f;
      normal.y = 0.0f;
      normal.z = -1.0f;
      break;
    case LM2_AABB3_FACE_LEFT:  // -X
      normal.x = -1.0f;
      normal.y = 0.0f;
      normal.z = 0.0f;
      break;
    case LM2_AABB3_FACE_RIGHT:  // +X
      normal.x = 1.0f;
      normal.y = 0.0f;
      normal.z = 0.0f;
      break;
    case LM2_AABB3_FACE_TOP:  // +Y
      normal.x = 0.0f;
      normal.y = 1.0f;
      normal.z = 0.0f;
      break;
    case LM2_AABB3_FACE_BOTTOM:  // -Y
      normal.x = 0.0f;
      normal.y = -1.0f;
      normal.z = 0.0f;
      break;
    default:
      LM2_ASSERT(false && "Invalid face enum");
      normal.x = 0.0f;
      normal.y = 0.0f;
      normal.z = 0.0f;
      break;
  }

  return normal;
}

// =============================================================================
// AABB3 Tests
// =============================================================================

LM2_API int lm2_aabb3_contains_point_f64(lm2_aabb3_f64 aabb3, lm2_v3_f64 point) {
  return lm2_r3_contains_point_f64(aabb3, point);
}

LM2_API int lm2_aabb3_contains_point_f32(lm2_aabb3_f32 aabb3, lm2_v3_f32 point) {
  return lm2_r3_contains_point_f32(aabb3, point);
}

LM2_API int lm2_aabb3_overlaps_f64(lm2_aabb3_f64 a, lm2_aabb3_f64 b) {
  return lm2_r3_overlaps_f64(a, b);
}

LM2_API int lm2_aabb3_overlaps_f32(lm2_aabb3_f32 a, lm2_aabb3_f32 b) {
  return lm2_r3_overlaps_f32(a, b);
}

// =============================================================================
// AABB3 Transformations
// =============================================================================

LM2_API lm2_aabb3_f64 lm2_aabb3_translate_f64(lm2_aabb3_f64 aabb3, lm2_v3_f64 offset) {
  return lm2_r3_translate_f64(aabb3, offset);
}

LM2_API lm2_aabb3_f32 lm2_aabb3_translate_f32(lm2_aabb3_f32 aabb3, lm2_v3_f32 offset) {
  return lm2_r3_translate_f32(aabb3, offset);
}

LM2_API lm2_aabb3_f64 lm2_aabb3_scale_f64(lm2_aabb3_f64 aabb3, lm2_v3_f64 scale) {
  lm2_aabb3_f64 result;
  result.min.x = lm2_mul_f64(aabb3.min.x, scale.x);
  result.min.y = lm2_mul_f64(aabb3.min.y, scale.y);
  result.min.z = lm2_mul_f64(aabb3.min.z, scale.z);
  result.max.x = lm2_mul_f64(aabb3.max.x, scale.x);
  result.max.y = lm2_mul_f64(aabb3.max.y, scale.y);
  result.max.z = lm2_mul_f64(aabb3.max.z, scale.z);
  return result;
}

LM2_API lm2_aabb3_f32 lm2_aabb3_scale_f32(lm2_aabb3_f32 aabb3, lm2_v3_f32 scale) {
  lm2_aabb3_f32 result;
  result.min.x = lm2_mul_f32(aabb3.min.x, scale.x);
  result.min.y = lm2_mul_f32(aabb3.min.y, scale.y);
  result.min.z = lm2_mul_f32(aabb3.min.z, scale.z);
  result.max.x = lm2_mul_f32(aabb3.max.x, scale.x);
  result.max.y = lm2_mul_f32(aabb3.max.y, scale.y);
  result.max.z = lm2_mul_f32(aabb3.max.z, scale.z);
  return result;
}

LM2_API lm2_aabb3_f64 lm2_aabb3_expand_f64(lm2_aabb3_f64 aabb3, lm2_v3_f64 amount) {
  lm2_aabb3_f64 result;
  result.min.x = lm2_sub_f64(aabb3.min.x, amount.x);
  result.min.y = lm2_sub_f64(aabb3.min.y, amount.y);
  result.min.z = lm2_sub_f64(aabb3.min.z, amount.z);
  result.max.x = lm2_add_f64(aabb3.max.x, amount.x);
  result.max.y = lm2_add_f64(aabb3.max.y, amount.y);
  result.max.z = lm2_add_f64(aabb3.max.z, amount.z);
  return result;
}

LM2_API lm2_aabb3_f32 lm2_aabb3_expand_f32(lm2_aabb3_f32 aabb3, lm2_v3_f32 amount) {
  lm2_aabb3_f32 result;
  result.min.x = lm2_sub_f32(aabb3.min.x, amount.x);
  result.min.y = lm2_sub_f32(aabb3.min.y, amount.y);
  result.min.z = lm2_sub_f32(aabb3.min.z, amount.z);
  result.max.x = lm2_add_f32(aabb3.max.x, amount.x);
  result.max.y = lm2_add_f32(aabb3.max.y, amount.y);
  result.max.z = lm2_add_f32(aabb3.max.z, amount.z);
  return result;
}
