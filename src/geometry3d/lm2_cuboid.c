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

#include <lm2/geometry3d/lm2_cuboid.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/vectors/lm2_vector_specifics.h>

// =============================================================================
// Construction Helpers
// =============================================================================

LM2_API lm2_cuboid_f64 lm2_cuboid_unit_f64(void) {
  lm2_cuboid_f64 cuboid;
  cuboid.min.x = 0.0;
  cuboid.min.y = 0.0;
  cuboid.min.z = 0.0;
  cuboid.max.x = 1.0;
  cuboid.max.y = 1.0;
  cuboid.max.z = 1.0;
  return cuboid;
}

LM2_API lm2_cuboid_f32 lm2_cuboid_unit_f32(void) {
  lm2_cuboid_f32 cuboid;
  cuboid.min.x = 0.0f;
  cuboid.min.y = 0.0f;
  cuboid.min.z = 0.0f;
  cuboid.max.x = 1.0f;
  cuboid.max.y = 1.0f;
  cuboid.max.z = 1.0f;
  return cuboid;
}

// =============================================================================
// Cuboid Properties
// =============================================================================

LM2_API double lm2_cuboid_surface_area_f64(lm2_cuboid_f64 cuboid) {
  // Surface Area = 2(wh + wd + hd) where w=width, h=height, d=depth
  double width = lm2_sub_f64(cuboid.max.x, cuboid.min.x);
  double height = lm2_sub_f64(cuboid.max.y, cuboid.min.y);
  double depth = lm2_sub_f64(cuboid.max.z, cuboid.min.z);

  double wh = lm2_mul_f64(width, height);
  double wd = lm2_mul_f64(width, depth);
  double hd = lm2_mul_f64(height, depth);

  double sum = lm2_add_f64(lm2_add_f64(wh, wd), hd);
  return lm2_mul_f64(2.0, sum);
}

LM2_API float lm2_cuboid_surface_area_f32(lm2_cuboid_f32 cuboid) {
  // Surface Area = 2(wh + wd + hd) where w=width, h=height, d=depth
  float width = lm2_sub_f32(cuboid.max.x, cuboid.min.x);
  float height = lm2_sub_f32(cuboid.max.y, cuboid.min.y);
  float depth = lm2_sub_f32(cuboid.max.z, cuboid.min.z);

  float wh = lm2_mul_f32(width, height);
  float wd = lm2_mul_f32(width, depth);
  float hd = lm2_mul_f32(height, depth);

  float sum = lm2_add_f32(lm2_add_f32(wh, wd), hd);
  return lm2_mul_f32(2.0f, sum);
}

LM2_API double lm2_cuboid_diagonal_f64(lm2_cuboid_f64 cuboid) {
  // Diagonal = sqrt((max.x - min.x)² + (max.y - min.y)² + (max.z - min.z)²)
  lm2_v3f64 size = lm2_sub_lm2_v3f64(cuboid.max, cuboid.min);
  return lm2_length_v3f64(size);
}

LM2_API float lm2_cuboid_diagonal_f32(lm2_cuboid_f32 cuboid) {
  // Diagonal = sqrt((max.x - min.x)² + (max.y - min.y)² + (max.z - min.z)²)
  lm2_v3f32 size = lm2_sub_lm2_v3f32(cuboid.max, cuboid.min);
  return lm2_length_v3f32(size);
}

LM2_API double lm2_cuboid_width_f64(lm2_cuboid_f64 cuboid) {
  return lm2_sub_f64(cuboid.max.x, cuboid.min.x);
}

LM2_API float lm2_cuboid_width_f32(lm2_cuboid_f32 cuboid) {
  return lm2_sub_f32(cuboid.max.x, cuboid.min.x);
}

LM2_API double lm2_cuboid_height_f64(lm2_cuboid_f64 cuboid) {
  return lm2_sub_f64(cuboid.max.y, cuboid.min.y);
}

LM2_API float lm2_cuboid_height_f32(lm2_cuboid_f32 cuboid) {
  return lm2_sub_f32(cuboid.max.y, cuboid.min.y);
}

LM2_API double lm2_cuboid_depth_f64(lm2_cuboid_f64 cuboid) {
  return lm2_sub_f64(cuboid.max.z, cuboid.min.z);
}

LM2_API float lm2_cuboid_depth_f32(lm2_cuboid_f32 cuboid) {
  return lm2_sub_f32(cuboid.max.z, cuboid.min.z);
}

// =============================================================================
// Cuboid Corner Operations
// =============================================================================

LM2_API lm2_v3f64 lm2_cuboid_get_corner_f64(lm2_cuboid_f64 cuboid, lm2_corner3 corner) {
  lm2_v3f64 result;

  switch (corner) {
    case LM2_CORNER3_MIN_MIN_MIN:
      result.x = cuboid.min.x;
      result.y = cuboid.min.y;
      result.z = cuboid.min.z;
      break;
    case LM2_CORNER3_MIN_MIN_MAX:
      result.x = cuboid.min.x;
      result.y = cuboid.min.y;
      result.z = cuboid.max.z;
      break;
    case LM2_CORNER3_MIN_MAX_MIN:
      result.x = cuboid.min.x;
      result.y = cuboid.max.y;
      result.z = cuboid.min.z;
      break;
    case LM2_CORNER3_MIN_MAX_MAX:
      result.x = cuboid.min.x;
      result.y = cuboid.max.y;
      result.z = cuboid.max.z;
      break;
    case LM2_CORNER3_MAX_MIN_MIN:
      result.x = cuboid.max.x;
      result.y = cuboid.min.y;
      result.z = cuboid.min.z;
      break;
    case LM2_CORNER3_MAX_MIN_MAX:
      result.x = cuboid.max.x;
      result.y = cuboid.min.y;
      result.z = cuboid.max.z;
      break;
    case LM2_CORNER3_MAX_MAX_MIN:
      result.x = cuboid.max.x;
      result.y = cuboid.max.y;
      result.z = cuboid.min.z;
      break;
    case LM2_CORNER3_MAX_MAX_MAX:
      result.x = cuboid.max.x;
      result.y = cuboid.max.y;
      result.z = cuboid.max.z;
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

LM2_API lm2_v3f32 lm2_cuboid_get_corner_f32(lm2_cuboid_f32 cuboid, lm2_corner3 corner) {
  lm2_v3f32 result;

  switch (corner) {
    case LM2_CORNER3_MIN_MIN_MIN:
      result.x = cuboid.min.x;
      result.y = cuboid.min.y;
      result.z = cuboid.min.z;
      break;
    case LM2_CORNER3_MIN_MIN_MAX:
      result.x = cuboid.min.x;
      result.y = cuboid.min.y;
      result.z = cuboid.max.z;
      break;
    case LM2_CORNER3_MIN_MAX_MIN:
      result.x = cuboid.min.x;
      result.y = cuboid.max.y;
      result.z = cuboid.min.z;
      break;
    case LM2_CORNER3_MIN_MAX_MAX:
      result.x = cuboid.min.x;
      result.y = cuboid.max.y;
      result.z = cuboid.max.z;
      break;
    case LM2_CORNER3_MAX_MIN_MIN:
      result.x = cuboid.max.x;
      result.y = cuboid.min.y;
      result.z = cuboid.min.z;
      break;
    case LM2_CORNER3_MAX_MIN_MAX:
      result.x = cuboid.max.x;
      result.y = cuboid.min.y;
      result.z = cuboid.max.z;
      break;
    case LM2_CORNER3_MAX_MAX_MIN:
      result.x = cuboid.max.x;
      result.y = cuboid.max.y;
      result.z = cuboid.min.z;
      break;
    case LM2_CORNER3_MAX_MAX_MAX:
      result.x = cuboid.max.x;
      result.y = cuboid.max.y;
      result.z = cuboid.max.z;
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

LM2_API void lm2_cuboid_get_corners_f64(lm2_cuboid_f64 cuboid, lm2_v3f64 corners[8]) {
  LM2_ASSERT(corners != NULL);

  for (int i = 0; i < 8; i++) {
    corners[i] = lm2_cuboid_get_corner_f64(cuboid, (lm2_corner3)i);
  }
}

LM2_API void lm2_cuboid_get_corners_f32(lm2_cuboid_f32 cuboid, lm2_v3f32 corners[8]) {
  LM2_ASSERT(corners != NULL);

  for (int i = 0; i < 8; i++) {
    corners[i] = lm2_cuboid_get_corner_f32(cuboid, (lm2_corner3)i);
  }
}

// =============================================================================
// Cuboid Face Operations
// =============================================================================

LM2_API lm2_v3f64 lm2_cuboid_face_center_f64(lm2_cuboid_f64 cuboid, lm2_cuboid_face face) {
  lm2_v3f64 result;
  lm2_v3f64 center = lm2_r3f64_center(cuboid);

  switch (face) {
    case LM2_CUBOID_FACE_FRONT:  // +Z
      result.x = center.x;
      result.y = center.y;
      result.z = cuboid.max.z;
      break;
    case LM2_CUBOID_FACE_BACK:  // -Z
      result.x = center.x;
      result.y = center.y;
      result.z = cuboid.min.z;
      break;
    case LM2_CUBOID_FACE_LEFT:  // -X
      result.x = cuboid.min.x;
      result.y = center.y;
      result.z = center.z;
      break;
    case LM2_CUBOID_FACE_RIGHT:  // +X
      result.x = cuboid.max.x;
      result.y = center.y;
      result.z = center.z;
      break;
    case LM2_CUBOID_FACE_TOP:  // +Y
      result.x = center.x;
      result.y = cuboid.max.y;
      result.z = center.z;
      break;
    case LM2_CUBOID_FACE_BOTTOM:  // -Y
      result.x = center.x;
      result.y = cuboid.min.y;
      result.z = center.z;
      break;
    default:
      LM2_ASSERT(false && "Invalid face enum");
      result = center;
      break;
  }

  return result;
}

LM2_API lm2_v3f32 lm2_cuboid_face_center_f32(lm2_cuboid_f32 cuboid, lm2_cuboid_face face) {
  lm2_v3f32 result;
  lm2_v3f32 center = lm2_r3f32_center(cuboid);

  switch (face) {
    case LM2_CUBOID_FACE_FRONT:  // +Z
      result.x = center.x;
      result.y = center.y;
      result.z = cuboid.max.z;
      break;
    case LM2_CUBOID_FACE_BACK:  // -Z
      result.x = center.x;
      result.y = center.y;
      result.z = cuboid.min.z;
      break;
    case LM2_CUBOID_FACE_LEFT:  // -X
      result.x = cuboid.min.x;
      result.y = center.y;
      result.z = center.z;
      break;
    case LM2_CUBOID_FACE_RIGHT:  // +X
      result.x = cuboid.max.x;
      result.y = center.y;
      result.z = center.z;
      break;
    case LM2_CUBOID_FACE_TOP:  // +Y
      result.x = center.x;
      result.y = cuboid.max.y;
      result.z = center.z;
      break;
    case LM2_CUBOID_FACE_BOTTOM:  // -Y
      result.x = center.x;
      result.y = cuboid.min.y;
      result.z = center.z;
      break;
    default:
      LM2_ASSERT(false && "Invalid face enum");
      result = center;
      break;
  }

  return result;
}

LM2_API lm2_v3f64 lm2_cuboid_face_normal_f64(lm2_cuboid_face face) {
  lm2_v3f64 normal;

  switch (face) {
    case LM2_CUBOID_FACE_FRONT:  // +Z
      normal.x = 0.0;
      normal.y = 0.0;
      normal.z = 1.0;
      break;
    case LM2_CUBOID_FACE_BACK:  // -Z
      normal.x = 0.0;
      normal.y = 0.0;
      normal.z = -1.0;
      break;
    case LM2_CUBOID_FACE_LEFT:  // -X
      normal.x = -1.0;
      normal.y = 0.0;
      normal.z = 0.0;
      break;
    case LM2_CUBOID_FACE_RIGHT:  // +X
      normal.x = 1.0;
      normal.y = 0.0;
      normal.z = 0.0;
      break;
    case LM2_CUBOID_FACE_TOP:  // +Y
      normal.x = 0.0;
      normal.y = 1.0;
      normal.z = 0.0;
      break;
    case LM2_CUBOID_FACE_BOTTOM:  // -Y
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

LM2_API lm2_v3f32 lm2_cuboid_face_normal_f32(lm2_cuboid_face face) {
  lm2_v3f32 normal;

  switch (face) {
    case LM2_CUBOID_FACE_FRONT:  // +Z
      normal.x = 0.0f;
      normal.y = 0.0f;
      normal.z = 1.0f;
      break;
    case LM2_CUBOID_FACE_BACK:  // -Z
      normal.x = 0.0f;
      normal.y = 0.0f;
      normal.z = -1.0f;
      break;
    case LM2_CUBOID_FACE_LEFT:  // -X
      normal.x = -1.0f;
      normal.y = 0.0f;
      normal.z = 0.0f;
      break;
    case LM2_CUBOID_FACE_RIGHT:  // +X
      normal.x = 1.0f;
      normal.y = 0.0f;
      normal.z = 0.0f;
      break;
    case LM2_CUBOID_FACE_TOP:  // +Y
      normal.x = 0.0f;
      normal.y = 1.0f;
      normal.z = 0.0f;
      break;
    case LM2_CUBOID_FACE_BOTTOM:  // -Y
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
