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

#include <lm2/vectors/lm2_vector_specifics.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <lm2/scalar/lm2_trigonometry.h>

// =============================================================================
// Dot Product - 2D
// =============================================================================

LM2_API double lm2_dot_v2f64(lm2_v2f64 a, lm2_v2f64 b) {
  return lm2_add_f64(lm2_mul_f64(a.x, b.x), lm2_mul_f64(a.y, b.y));
}

LM2_API float lm2_dot_v2f32(lm2_v2f32 a, lm2_v2f32 b) {
  return lm2_add_f32(lm2_mul_f32(a.x, b.x), lm2_mul_f32(a.y, b.y));
}

LM2_API int64_t lm2_dot_v2i64(lm2_v2i64 a, lm2_v2i64 b) {
  return lm2_add_i64(lm2_mul_i64(a.x, b.x), lm2_mul_i64(a.y, b.y));
}

LM2_API int32_t lm2_dot_v2i32(lm2_v2i32 a, lm2_v2i32 b) {
  return lm2_add_i32(lm2_mul_i32(a.x, b.x), lm2_mul_i32(a.y, b.y));
}

LM2_API int16_t lm2_dot_v2i16(lm2_v2i16 a, lm2_v2i16 b) {
  return lm2_add_i16(lm2_mul_i16(a.x, b.x), lm2_mul_i16(a.y, b.y));
}

LM2_API int8_t lm2_dot_v2i8(lm2_v2i8 a, lm2_v2i8 b) {
  return lm2_add_i8(lm2_mul_i8(a.x, b.x), lm2_mul_i8(a.y, b.y));
}

// =============================================================================
// Dot Product - 3D
// =============================================================================

LM2_API double lm2_dot_v3f64(lm2_v3f64 a, lm2_v3f64 b) {
  return lm2_add_f64(
      lm2_add_f64(lm2_mul_f64(a.x, b.x), lm2_mul_f64(a.y, b.y)),
      lm2_mul_f64(a.z, b.z));
}

LM2_API float lm2_dot_v3f32(lm2_v3f32 a, lm2_v3f32 b) {
  return lm2_add_f32(
      lm2_add_f32(lm2_mul_f32(a.x, b.x), lm2_mul_f32(a.y, b.y)),
      lm2_mul_f32(a.z, b.z));
}

LM2_API int64_t lm2_dot_v3i64(lm2_v3i64 a, lm2_v3i64 b) {
  return lm2_add_i64(
      lm2_add_i64(lm2_mul_i64(a.x, b.x), lm2_mul_i64(a.y, b.y)),
      lm2_mul_i64(a.z, b.z));
}

LM2_API int32_t lm2_dot_v3i32(lm2_v3i32 a, lm2_v3i32 b) {
  return lm2_add_i32(
      lm2_add_i32(lm2_mul_i32(a.x, b.x), lm2_mul_i32(a.y, b.y)),
      lm2_mul_i32(a.z, b.z));
}

LM2_API int16_t lm2_dot_v3i16(lm2_v3i16 a, lm2_v3i16 b) {
  return lm2_add_i16(
      lm2_add_i16(lm2_mul_i16(a.x, b.x), lm2_mul_i16(a.y, b.y)),
      lm2_mul_i16(a.z, b.z));
}

LM2_API int8_t lm2_dot_v3i8(lm2_v3i8 a, lm2_v3i8 b) {
  return lm2_add_i8(
      lm2_add_i8(lm2_mul_i8(a.x, b.x), lm2_mul_i8(a.y, b.y)),
      lm2_mul_i8(a.z, b.z));
}

// =============================================================================
// Dot Product - 4D
// =============================================================================

LM2_API double lm2_dot_v4f64(lm2_v4f64 a, lm2_v4f64 b) {
  return lm2_add_f64(
      lm2_add_f64(lm2_mul_f64(a.x, b.x), lm2_mul_f64(a.y, b.y)),
      lm2_add_f64(lm2_mul_f64(a.z, b.z), lm2_mul_f64(a.w, b.w)));
}

LM2_API float lm2_dot_v4f32(lm2_v4f32 a, lm2_v4f32 b) {
  return lm2_add_f32(
      lm2_add_f32(lm2_mul_f32(a.x, b.x), lm2_mul_f32(a.y, b.y)),
      lm2_add_f32(lm2_mul_f32(a.z, b.z), lm2_mul_f32(a.w, b.w)));
}

LM2_API int64_t lm2_dot_v4i64(lm2_v4i64 a, lm2_v4i64 b) {
  return lm2_add_i64(
      lm2_add_i64(lm2_mul_i64(a.x, b.x), lm2_mul_i64(a.y, b.y)),
      lm2_add_i64(lm2_mul_i64(a.z, b.z), lm2_mul_i64(a.w, b.w)));
}

LM2_API int32_t lm2_dot_v4i32(lm2_v4i32 a, lm2_v4i32 b) {
  return lm2_add_i32(
      lm2_add_i32(lm2_mul_i32(a.x, b.x), lm2_mul_i32(a.y, b.y)),
      lm2_add_i32(lm2_mul_i32(a.z, b.z), lm2_mul_i32(a.w, b.w)));
}

LM2_API int16_t lm2_dot_v4i16(lm2_v4i16 a, lm2_v4i16 b) {
  return lm2_add_i16(
      lm2_add_i16(lm2_mul_i16(a.x, b.x), lm2_mul_i16(a.y, b.y)),
      lm2_add_i16(lm2_mul_i16(a.z, b.z), lm2_mul_i16(a.w, b.w)));
}

LM2_API int8_t lm2_dot_v4i8(lm2_v4i8 a, lm2_v4i8 b) {
  return lm2_add_i8(
      lm2_add_i8(lm2_mul_i8(a.x, b.x), lm2_mul_i8(a.y, b.y)),
      lm2_add_i8(lm2_mul_i8(a.z, b.z), lm2_mul_i8(a.w, b.w)));
}

// =============================================================================
// Cross Product - 3D only
// =============================================================================

LM2_API lm2_v3f64 lm2_cross_v3f64(lm2_v3f64 a, lm2_v3f64 b) {
  lm2_v3f64 result;
  result.x = lm2_sub_f64(lm2_mul_f64(a.y, b.z), lm2_mul_f64(a.z, b.y));
  result.y = lm2_sub_f64(lm2_mul_f64(a.z, b.x), lm2_mul_f64(a.x, b.z));
  result.z = lm2_sub_f64(lm2_mul_f64(a.x, b.y), lm2_mul_f64(a.y, b.x));
  return result;
}

LM2_API lm2_v3f32 lm2_cross_v3f32(lm2_v3f32 a, lm2_v3f32 b) {
  lm2_v3f32 result;
  result.x = lm2_sub_f32(lm2_mul_f32(a.y, b.z), lm2_mul_f32(a.z, b.y));
  result.y = lm2_sub_f32(lm2_mul_f32(a.z, b.x), lm2_mul_f32(a.x, b.z));
  result.z = lm2_sub_f32(lm2_mul_f32(a.x, b.y), lm2_mul_f32(a.y, b.x));
  return result;
}

LM2_API lm2_v3i64 lm2_cross_v3i64(lm2_v3i64 a, lm2_v3i64 b) {
  lm2_v3i64 result;
  result.x = lm2_sub_i64(lm2_mul_i64(a.y, b.z), lm2_mul_i64(a.z, b.y));
  result.y = lm2_sub_i64(lm2_mul_i64(a.z, b.x), lm2_mul_i64(a.x, b.z));
  result.z = lm2_sub_i64(lm2_mul_i64(a.x, b.y), lm2_mul_i64(a.y, b.x));
  return result;
}

LM2_API lm2_v3i32 lm2_cross_v3i32(lm2_v3i32 a, lm2_v3i32 b) {
  lm2_v3i32 result;
  result.x = lm2_sub_i32(lm2_mul_i32(a.y, b.z), lm2_mul_i32(a.z, b.y));
  result.y = lm2_sub_i32(lm2_mul_i32(a.z, b.x), lm2_mul_i32(a.x, b.z));
  result.z = lm2_sub_i32(lm2_mul_i32(a.x, b.y), lm2_mul_i32(a.y, b.x));
  return result;
}

LM2_API lm2_v3i16 lm2_cross_v3i16(lm2_v3i16 a, lm2_v3i16 b) {
  lm2_v3i16 result;
  result.x = lm2_sub_i16(lm2_mul_i16(a.y, b.z), lm2_mul_i16(a.z, b.y));
  result.y = lm2_sub_i16(lm2_mul_i16(a.z, b.x), lm2_mul_i16(a.x, b.z));
  result.z = lm2_sub_i16(lm2_mul_i16(a.x, b.y), lm2_mul_i16(a.y, b.x));
  return result;
}

LM2_API lm2_v3i8 lm2_cross_v3i8(lm2_v3i8 a, lm2_v3i8 b) {
  lm2_v3i8 result;
  result.x = lm2_sub_i8(lm2_mul_i8(a.y, b.z), lm2_mul_i8(a.z, b.y));
  result.y = lm2_sub_i8(lm2_mul_i8(a.z, b.x), lm2_mul_i8(a.x, b.z));
  result.z = lm2_sub_i8(lm2_mul_i8(a.x, b.y), lm2_mul_i8(a.y, b.x));
  return result;
}

// =============================================================================
// 2D Cross Product (returns scalar)
// =============================================================================

LM2_API double lm2_cross_v2f64(lm2_v2f64 a, lm2_v2f64 b) {
  return lm2_sub_f64(lm2_mul_f64(a.x, b.y), lm2_mul_f64(a.y, b.x));
}

LM2_API float lm2_cross_v2f32(lm2_v2f32 a, lm2_v2f32 b) {
  return lm2_sub_f32(lm2_mul_f32(a.x, b.y), lm2_mul_f32(a.y, b.x));
}

LM2_API int64_t lm2_cross_v2i64(lm2_v2i64 a, lm2_v2i64 b) {
  return lm2_sub_i64(lm2_mul_i64(a.x, b.y), lm2_mul_i64(a.y, b.x));
}

LM2_API int32_t lm2_cross_v2i32(lm2_v2i32 a, lm2_v2i32 b) {
  return lm2_sub_i32(lm2_mul_i32(a.x, b.y), lm2_mul_i32(a.y, b.x));
}

LM2_API int16_t lm2_cross_v2i16(lm2_v2i16 a, lm2_v2i16 b) {
  return lm2_sub_i16(lm2_mul_i16(a.x, b.y), lm2_mul_i16(a.y, b.x));
}

LM2_API int8_t lm2_cross_v2i8(lm2_v2i8 a, lm2_v2i8 b) {
  return lm2_sub_i8(lm2_mul_i8(a.x, b.y), lm2_mul_i8(a.y, b.x));
}

// =============================================================================
// 2D Cross Product for Turn Detection (3-point version)
// =============================================================================

LM2_API double lm2_cross3_v2f64(lm2_v2f64 a, lm2_v2f64 b, lm2_v2f64 c) {
  // Compute vectors (b - a) and (c - a), then their cross product
  double abx = lm2_sub_f64(b.x, a.x);
  double aby = lm2_sub_f64(b.y, a.y);
  double acx = lm2_sub_f64(c.x, a.x);
  double acy = lm2_sub_f64(c.y, a.y);
  return lm2_sub_f64(lm2_mul_f64(abx, acy), lm2_mul_f64(aby, acx));
}

LM2_API float lm2_cross3_v2f32(lm2_v2f32 a, lm2_v2f32 b, lm2_v2f32 c) {
  // Compute vectors (b - a) and (c - a), then their cross product
  float abx = lm2_sub_f32(b.x, a.x);
  float aby = lm2_sub_f32(b.y, a.y);
  float acx = lm2_sub_f32(c.x, a.x);
  float acy = lm2_sub_f32(c.y, a.y);
  return lm2_sub_f32(lm2_mul_f32(abx, acy), lm2_mul_f32(aby, acx));
}

LM2_API int64_t lm2_cross3_v2i64(lm2_v2i64 a, lm2_v2i64 b, lm2_v2i64 c) {
  // Compute vectors (b - a) and (c - a), then their cross product
  int64_t abx = lm2_sub_i64(b.x, a.x);
  int64_t aby = lm2_sub_i64(b.y, a.y);
  int64_t acx = lm2_sub_i64(c.x, a.x);
  int64_t acy = lm2_sub_i64(c.y, a.y);
  return lm2_sub_i64(lm2_mul_i64(abx, acy), lm2_mul_i64(aby, acx));
}

LM2_API int32_t lm2_cross3_v2i32(lm2_v2i32 a, lm2_v2i32 b, lm2_v2i32 c) {
  // Compute vectors (b - a) and (c - a), then their cross product
  int32_t abx = lm2_sub_i32(b.x, a.x);
  int32_t aby = lm2_sub_i32(b.y, a.y);
  int32_t acx = lm2_sub_i32(c.x, a.x);
  int32_t acy = lm2_sub_i32(c.y, a.y);
  return lm2_sub_i32(lm2_mul_i32(abx, acy), lm2_mul_i32(aby, acx));
}

LM2_API int16_t lm2_cross3_v2i16(lm2_v2i16 a, lm2_v2i16 b, lm2_v2i16 c) {
  // Compute vectors (b - a) and (c - a), then their cross product
  int16_t abx = lm2_sub_i16(b.x, a.x);
  int16_t aby = lm2_sub_i16(b.y, a.y);
  int16_t acx = lm2_sub_i16(c.x, a.x);
  int16_t acy = lm2_sub_i16(c.y, a.y);
  return lm2_sub_i16(lm2_mul_i16(abx, acy), lm2_mul_i16(aby, acx));
}

LM2_API int8_t lm2_cross3_v2i8(lm2_v2i8 a, lm2_v2i8 b, lm2_v2i8 c) {
  // Compute vectors (b - a) and (c - a), then their cross product
  int8_t abx = lm2_sub_i8(b.x, a.x);
  int8_t aby = lm2_sub_i8(b.y, a.y);
  int8_t acx = lm2_sub_i8(c.x, a.x);
  int8_t acy = lm2_sub_i8(c.y, a.y);
  return lm2_sub_i8(lm2_mul_i8(abx, acy), lm2_mul_i8(aby, acx));
}

// =============================================================================
// Length / Magnitude
// =============================================================================

LM2_API double lm2_length_v2f64(lm2_v2f64 v) {
  return lm2_sqrt_f64(lm2_add_f64(lm2_mul_f64(v.x, v.x), lm2_mul_f64(v.y, v.y)));
}

LM2_API float lm2_length_v2f32(lm2_v2f32 v) {
  return lm2_sqrt_f32(lm2_add_f32(lm2_mul_f32(v.x, v.x), lm2_mul_f32(v.y, v.y)));
}

LM2_API double lm2_length_v3f64(lm2_v3f64 v) {
  return lm2_sqrt_f64(
      lm2_add_f64(
          lm2_add_f64(lm2_mul_f64(v.x, v.x), lm2_mul_f64(v.y, v.y)),
          lm2_mul_f64(v.z, v.z)));
}

LM2_API float lm2_length_v3f32(lm2_v3f32 v) {
  return lm2_sqrt_f32(
      lm2_add_f32(
          lm2_add_f32(lm2_mul_f32(v.x, v.x), lm2_mul_f32(v.y, v.y)),
          lm2_mul_f32(v.z, v.z)));
}

LM2_API double lm2_length_v4f64(lm2_v4f64 v) {
  return lm2_sqrt_f64(
      lm2_add_f64(
          lm2_add_f64(lm2_mul_f64(v.x, v.x), lm2_mul_f64(v.y, v.y)),
          lm2_add_f64(lm2_mul_f64(v.z, v.z), lm2_mul_f64(v.w, v.w))));
}

LM2_API float lm2_length_v4f32(lm2_v4f32 v) {
  return lm2_sqrt_f32(
      lm2_add_f32(
          lm2_add_f32(lm2_mul_f32(v.x, v.x), lm2_mul_f32(v.y, v.y)),
          lm2_add_f32(lm2_mul_f32(v.z, v.z), lm2_mul_f32(v.w, v.w))));
}

// =============================================================================
// Length Squared
// =============================================================================

LM2_API double lm2_length_sq_v2f64(lm2_v2f64 v) {
  return lm2_add_f64(lm2_mul_f64(v.x, v.x), lm2_mul_f64(v.y, v.y));
}

LM2_API float lm2_length_sq_v2f32(lm2_v2f32 v) {
  return lm2_add_f32(lm2_mul_f32(v.x, v.x), lm2_mul_f32(v.y, v.y));
}

LM2_API double lm2_length_sq_v3f64(lm2_v3f64 v) {
  return lm2_add_f64(
      lm2_add_f64(lm2_mul_f64(v.x, v.x), lm2_mul_f64(v.y, v.y)),
      lm2_mul_f64(v.z, v.z));
}

LM2_API float lm2_length_sq_v3f32(lm2_v3f32 v) {
  return lm2_add_f32(
      lm2_add_f32(lm2_mul_f32(v.x, v.x), lm2_mul_f32(v.y, v.y)),
      lm2_mul_f32(v.z, v.z));
}

LM2_API double lm2_length_sq_v4f64(lm2_v4f64 v) {
  return lm2_add_f64(
      lm2_add_f64(lm2_mul_f64(v.x, v.x), lm2_mul_f64(v.y, v.y)),
      lm2_add_f64(lm2_mul_f64(v.z, v.z), lm2_mul_f64(v.w, v.w)));
}

LM2_API float lm2_length_sq_v4f32(lm2_v4f32 v) {
  return lm2_add_f32(
      lm2_add_f32(lm2_mul_f32(v.x, v.x), lm2_mul_f32(v.y, v.y)),
      lm2_add_f32(lm2_mul_f32(v.z, v.z), lm2_mul_f32(v.w, v.w)));
}

// =============================================================================
// Distance
// =============================================================================

LM2_API double lm2_distance_v2f64(lm2_v2f64 a, lm2_v2f64 b) {
  double dx = lm2_sub_f64(b.x, a.x);
  double dy = lm2_sub_f64(b.y, a.y);
  return lm2_sqrt_f64(lm2_add_f64(lm2_mul_f64(dx, dx), lm2_mul_f64(dy, dy)));
}

LM2_API float lm2_distance_v2f32(lm2_v2f32 a, lm2_v2f32 b) {
  float dx = lm2_sub_f32(b.x, a.x);
  float dy = lm2_sub_f32(b.y, a.y);
  return lm2_sqrt_f32(lm2_add_f32(lm2_mul_f32(dx, dx), lm2_mul_f32(dy, dy)));
}

LM2_API double lm2_distance_v3f64(lm2_v3f64 a, lm2_v3f64 b) {
  double dx = lm2_sub_f64(b.x, a.x);
  double dy = lm2_sub_f64(b.y, a.y);
  double dz = lm2_sub_f64(b.z, a.z);
  return lm2_sqrt_f64(
      lm2_add_f64(
          lm2_add_f64(lm2_mul_f64(dx, dx), lm2_mul_f64(dy, dy)),
          lm2_mul_f64(dz, dz)));
}

LM2_API float lm2_distance_v3f32(lm2_v3f32 a, lm2_v3f32 b) {
  float dx = lm2_sub_f32(b.x, a.x);
  float dy = lm2_sub_f32(b.y, a.y);
  float dz = lm2_sub_f32(b.z, a.z);
  return lm2_sqrt_f32(
      lm2_add_f32(
          lm2_add_f32(lm2_mul_f32(dx, dx), lm2_mul_f32(dy, dy)),
          lm2_mul_f32(dz, dz)));
}

LM2_API double lm2_distance_v4f64(lm2_v4f64 a, lm2_v4f64 b) {
  double dx = lm2_sub_f64(b.x, a.x);
  double dy = lm2_sub_f64(b.y, a.y);
  double dz = lm2_sub_f64(b.z, a.z);
  double dw = lm2_sub_f64(b.w, a.w);
  return lm2_sqrt_f64(
      lm2_add_f64(
          lm2_add_f64(lm2_mul_f64(dx, dx), lm2_mul_f64(dy, dy)),
          lm2_add_f64(lm2_mul_f64(dz, dz), lm2_mul_f64(dw, dw))));
}

LM2_API float lm2_distance_v4f32(lm2_v4f32 a, lm2_v4f32 b) {
  float dx = lm2_sub_f32(b.x, a.x);
  float dy = lm2_sub_f32(b.y, a.y);
  float dz = lm2_sub_f32(b.z, a.z);
  float dw = lm2_sub_f32(b.w, a.w);
  return lm2_sqrt_f32(
      lm2_add_f32(
          lm2_add_f32(lm2_mul_f32(dx, dx), lm2_mul_f32(dy, dy)),
          lm2_add_f32(lm2_mul_f32(dz, dz), lm2_mul_f32(dw, dw))));
}

// =============================================================================
// Distance Squared
// =============================================================================

LM2_API double lm2_distance_sq_v2f64(lm2_v2f64 a, lm2_v2f64 b) {
  double dx = lm2_sub_f64(b.x, a.x);
  double dy = lm2_sub_f64(b.y, a.y);
  return lm2_add_f64(lm2_mul_f64(dx, dx), lm2_mul_f64(dy, dy));
}

LM2_API float lm2_distance_sq_v2f32(lm2_v2f32 a, lm2_v2f32 b) {
  float dx = lm2_sub_f32(b.x, a.x);
  float dy = lm2_sub_f32(b.y, a.y);
  return lm2_add_f32(lm2_mul_f32(dx, dx), lm2_mul_f32(dy, dy));
}

LM2_API double lm2_distance_sq_v3f64(lm2_v3f64 a, lm2_v3f64 b) {
  double dx = lm2_sub_f64(b.x, a.x);
  double dy = lm2_sub_f64(b.y, a.y);
  double dz = lm2_sub_f64(b.z, a.z);
  return lm2_add_f64(
      lm2_add_f64(lm2_mul_f64(dx, dx), lm2_mul_f64(dy, dy)),
      lm2_mul_f64(dz, dz));
}

LM2_API float lm2_distance_sq_v3f32(lm2_v3f32 a, lm2_v3f32 b) {
  float dx = lm2_sub_f32(b.x, a.x);
  float dy = lm2_sub_f32(b.y, a.y);
  float dz = lm2_sub_f32(b.z, a.z);
  return lm2_add_f32(
      lm2_add_f32(lm2_mul_f32(dx, dx), lm2_mul_f32(dy, dy)),
      lm2_mul_f32(dz, dz));
}

LM2_API double lm2_distance_sq_v4f64(lm2_v4f64 a, lm2_v4f64 b) {
  double dx = lm2_sub_f64(b.x, a.x);
  double dy = lm2_sub_f64(b.y, a.y);
  double dz = lm2_sub_f64(b.z, a.z);
  double dw = lm2_sub_f64(b.w, a.w);
  return lm2_add_f64(
      lm2_add_f64(lm2_mul_f64(dx, dx), lm2_mul_f64(dy, dy)),
      lm2_add_f64(lm2_mul_f64(dz, dz), lm2_mul_f64(dw, dw)));
}

LM2_API float lm2_distance_sq_v4f32(lm2_v4f32 a, lm2_v4f32 b) {
  float dx = lm2_sub_f32(b.x, a.x);
  float dy = lm2_sub_f32(b.y, a.y);
  float dz = lm2_sub_f32(b.z, a.z);
  float dw = lm2_sub_f32(b.w, a.w);
  return lm2_add_f32(
      lm2_add_f32(lm2_mul_f32(dx, dx), lm2_mul_f32(dy, dy)),
      lm2_add_f32(lm2_mul_f32(dz, dz), lm2_mul_f32(dw, dw)));
}

// =============================================================================
// Normalize
// =============================================================================

LM2_API lm2_v2f64 lm2_normalize_v2f64(lm2_v2f64 v) {
  double len = lm2_length_v2f64(v);
  lm2_v2f64 result;
  if (len == 0.0) {
    result.x = 0.0;
    result.y = 0.0;
  } else {
    result.x = lm2_div_f64(v.x, len);
    result.y = lm2_div_f64(v.y, len);
  }
  return result;
}

LM2_API lm2_v2f32 lm2_normalize_v2f32(lm2_v2f32 v) {
  float len = lm2_length_v2f32(v);
  lm2_v2f32 result;
  if (len == 0.0f) {
    result.x = 0.0f;
    result.y = 0.0f;
  } else {
    result.x = lm2_div_f32(v.x, len);
    result.y = lm2_div_f32(v.y, len);
  }
  return result;
}

LM2_API lm2_v3f64 lm2_normalize_v3f64(lm2_v3f64 v) {
  double len = lm2_length_v3f64(v);
  lm2_v3f64 result;
  if (len == 0.0) {
    result.x = 0.0;
    result.y = 0.0;
    result.z = 0.0;
  } else {
    result.x = lm2_div_f64(v.x, len);
    result.y = lm2_div_f64(v.y, len);
    result.z = lm2_div_f64(v.z, len);
  }
  return result;
}

LM2_API lm2_v3f32 lm2_normalize_v3f32(lm2_v3f32 v) {
  float len = lm2_length_v3f32(v);
  lm2_v3f32 result;
  if (len == 0.0f) {
    result.x = 0.0f;
    result.y = 0.0f;
    result.z = 0.0f;
  } else {
    result.x = lm2_div_f32(v.x, len);
    result.y = lm2_div_f32(v.y, len);
    result.z = lm2_div_f32(v.z, len);
  }
  return result;
}

LM2_API lm2_v4f64 lm2_normalize_v4f64(lm2_v4f64 v) {
  double len = lm2_length_v4f64(v);
  lm2_v4f64 result;
  if (len == 0.0) {
    result.x = 0.0;
    result.y = 0.0;
    result.z = 0.0;
    result.w = 0.0;
  } else {
    result.x = lm2_div_f64(v.x, len);
    result.y = lm2_div_f64(v.y, len);
    result.z = lm2_div_f64(v.z, len);
    result.w = lm2_div_f64(v.w, len);
  }
  return result;
}

LM2_API lm2_v4f32 lm2_normalize_v4f32(lm2_v4f32 v) {
  float len = lm2_length_v4f32(v);
  lm2_v4f32 result;
  if (len == 0.0f) {
    result.x = 0.0f;
    result.y = 0.0f;
    result.z = 0.0f;
    result.w = 0.0f;
  } else {
    result.x = lm2_div_f32(v.x, len);
    result.y = lm2_div_f32(v.y, len);
    result.z = lm2_div_f32(v.z, len);
    result.w = lm2_div_f32(v.w, len);
  }
  return result;
}

// =============================================================================
// Angle Between Vectors
// =============================================================================

LM2_API double lm2_angle_v2f64(lm2_v2f64 a, lm2_v2f64 b) {
  double dot = lm2_dot_v2f64(a, b);
  double len_a = lm2_length_v2f64(a);
  double len_b = lm2_length_v2f64(b);
  double cos_angle = lm2_div_f64(dot, lm2_mul_f64(len_a, len_b));
  return lm2_acos_f64(cos_angle);
}

LM2_API float lm2_angle_v2f32(lm2_v2f32 a, lm2_v2f32 b) {
  float dot = lm2_dot_v2f32(a, b);
  float len_a = lm2_length_v2f32(a);
  float len_b = lm2_length_v2f32(b);
  float cos_angle = lm2_div_f32(dot, lm2_mul_f32(len_a, len_b));
  return lm2_acos_f32(cos_angle);
}

LM2_API double lm2_angle_v3f64(lm2_v3f64 a, lm2_v3f64 b) {
  double dot = lm2_dot_v3f64(a, b);
  double len_a = lm2_length_v3f64(a);
  double len_b = lm2_length_v3f64(b);
  double cos_angle = lm2_div_f64(dot, lm2_mul_f64(len_a, len_b));
  return lm2_acos_f64(cos_angle);
}

LM2_API float lm2_angle_v3f32(lm2_v3f32 a, lm2_v3f32 b) {
  float dot = lm2_dot_v3f32(a, b);
  float len_a = lm2_length_v3f32(a);
  float len_b = lm2_length_v3f32(b);
  float cos_angle = lm2_div_f32(dot, lm2_mul_f32(len_a, len_b));
  return lm2_acos_f32(cos_angle);
}

// =============================================================================
// 2D Rotation
// =============================================================================

LM2_API lm2_v2f64 lm2_rotate_v2f64(lm2_v2f64 v, double angle) {
  double c = lm2_cos_f64(angle);
  double s = lm2_sin_f64(angle);
  lm2_v2f64 result;
  result.x = lm2_sub_f64(lm2_mul_f64(v.x, c), lm2_mul_f64(v.y, s));
  result.y = lm2_add_f64(lm2_mul_f64(v.x, s), lm2_mul_f64(v.y, c));
  return result;
}

LM2_API lm2_v2f32 lm2_rotate_v2f32(lm2_v2f32 v, float angle) {
  float c = lm2_cos_f32(angle);
  float s = lm2_sin_f32(angle);
  lm2_v2f32 result;
  result.x = lm2_sub_f32(lm2_mul_f32(v.x, c), lm2_mul_f32(v.y, s));
  result.y = lm2_add_f32(lm2_mul_f32(v.x, s), lm2_mul_f32(v.y, c));
  return result;
}

LM2_API lm2_v2f64 lm2_rotate_around_v2f64(lm2_v2f64 v, lm2_v2f64 point, double angle) {
  // Translate to origin
  lm2_v2f64 translated;
  translated.x = lm2_sub_f64(v.x, point.x);
  translated.y = lm2_sub_f64(v.y, point.y);

  // Rotate
  lm2_v2f64 rotated = lm2_rotate_v2f64(translated, angle);

  // Translate back
  lm2_v2f64 result;
  result.x = lm2_add_f64(rotated.x, point.x);
  result.y = lm2_add_f64(rotated.y, point.y);
  return result;
}

LM2_API lm2_v2f32 lm2_rotate_around_v2f32(lm2_v2f32 v, lm2_v2f32 point, float angle) {
  // Translate to origin
  lm2_v2f32 translated;
  translated.x = lm2_sub_f32(v.x, point.x);
  translated.y = lm2_sub_f32(v.y, point.y);

  // Rotate
  lm2_v2f32 rotated = lm2_rotate_v2f32(translated, angle);

  // Translate back
  lm2_v2f32 result;
  result.x = lm2_add_f32(rotated.x, point.x);
  result.y = lm2_add_f32(rotated.y, point.y);
  return result;
}

// =============================================================================
// 2D Perpendicular Vectors
// =============================================================================

LM2_API lm2_v2f64 lm2_perp_ccw_v2f64(lm2_v2f64 v) {
  lm2_v2f64 result;
  result.x = lm2_neg_f64(v.y);
  result.y = v.x;
  return result;
}

LM2_API lm2_v2f32 lm2_perp_ccw_v2f32(lm2_v2f32 v) {
  lm2_v2f32 result;
  result.x = lm2_neg_f32(v.y);
  result.y = v.x;
  return result;
}

LM2_API lm2_v2i64 lm2_perp_ccw_v2i64(lm2_v2i64 v) {
  lm2_v2i64 result;
  result.x = lm2_neg_i64(v.y);
  result.y = v.x;
  return result;
}

LM2_API lm2_v2i32 lm2_perp_ccw_v2i32(lm2_v2i32 v) {
  lm2_v2i32 result;
  result.x = lm2_neg_i32(v.y);
  result.y = v.x;
  return result;
}

LM2_API lm2_v2i16 lm2_perp_ccw_v2i16(lm2_v2i16 v) {
  lm2_v2i16 result;
  result.x = lm2_neg_i16(v.y);
  result.y = v.x;
  return result;
}

LM2_API lm2_v2i8 lm2_perp_ccw_v2i8(lm2_v2i8 v) {
  lm2_v2i8 result;
  result.x = lm2_neg_i8(v.y);
  result.y = v.x;
  return result;
}

LM2_API lm2_v2f64 lm2_perp_cw_v2f64(lm2_v2f64 v) {
  lm2_v2f64 result;
  result.x = v.y;
  result.y = lm2_neg_f64(v.x);
  return result;
}

LM2_API lm2_v2f32 lm2_perp_cw_v2f32(lm2_v2f32 v) {
  lm2_v2f32 result;
  result.x = v.y;
  result.y = lm2_neg_f32(v.x);
  return result;
}

LM2_API lm2_v2i64 lm2_perp_cw_v2i64(lm2_v2i64 v) {
  lm2_v2i64 result;
  result.x = v.y;
  result.y = lm2_neg_i64(v.x);
  return result;
}

LM2_API lm2_v2i32 lm2_perp_cw_v2i32(lm2_v2i32 v) {
  lm2_v2i32 result;
  result.x = v.y;
  result.y = lm2_neg_i32(v.x);
  return result;
}

LM2_API lm2_v2i16 lm2_perp_cw_v2i16(lm2_v2i16 v) {
  lm2_v2i16 result;
  result.x = v.y;
  result.y = lm2_neg_i16(v.x);
  return result;
}

LM2_API lm2_v2i8 lm2_perp_cw_v2i8(lm2_v2i8 v) {
  lm2_v2i8 result;
  result.x = v.y;
  result.y = lm2_neg_i8(v.x);
  return result;
}

// =============================================================================
// Reflection
// =============================================================================

LM2_API lm2_v2f64 lm2_reflect_v2f64(lm2_v2f64 v, lm2_v2f64 normal) {
  // v - 2 * dot(v, n) * n
  double dot = lm2_dot_v2f64(v, normal);
  double factor = lm2_mul_f64(2.0, dot);
  lm2_v2f64 result;
  result.x = lm2_sub_f64(v.x, lm2_mul_f64(factor, normal.x));
  result.y = lm2_sub_f64(v.y, lm2_mul_f64(factor, normal.y));
  return result;
}

LM2_API lm2_v2f32 lm2_reflect_v2f32(lm2_v2f32 v, lm2_v2f32 normal) {
  // v - 2 * dot(v, n) * n
  float dot = lm2_dot_v2f32(v, normal);
  float factor = lm2_mul_f32(2.0f, dot);
  lm2_v2f32 result;
  result.x = lm2_sub_f32(v.x, lm2_mul_f32(factor, normal.x));
  result.y = lm2_sub_f32(v.y, lm2_mul_f32(factor, normal.y));
  return result;
}

LM2_API lm2_v3f64 lm2_reflect_v3f64(lm2_v3f64 v, lm2_v3f64 normal) {
  // v - 2 * dot(v, n) * n
  double dot = lm2_dot_v3f64(v, normal);
  double factor = lm2_mul_f64(2.0, dot);
  lm2_v3f64 result;
  result.x = lm2_sub_f64(v.x, lm2_mul_f64(factor, normal.x));
  result.y = lm2_sub_f64(v.y, lm2_mul_f64(factor, normal.y));
  result.z = lm2_sub_f64(v.z, lm2_mul_f64(factor, normal.z));
  return result;
}

LM2_API lm2_v3f32 lm2_reflect_v3f32(lm2_v3f32 v, lm2_v3f32 normal) {
  // v - 2 * dot(v, n) * n
  float dot = lm2_dot_v3f32(v, normal);
  float factor = lm2_mul_f32(2.0f, dot);
  lm2_v3f32 result;
  result.x = lm2_sub_f32(v.x, lm2_mul_f32(factor, normal.x));
  result.y = lm2_sub_f32(v.y, lm2_mul_f32(factor, normal.y));
  result.z = lm2_sub_f32(v.z, lm2_mul_f32(factor, normal.z));
  return result;
}

// =============================================================================
// Projection
// =============================================================================

LM2_API lm2_v2f64 lm2_project_v2f64(lm2_v2f64 a, lm2_v2f64 b) {
  // (dot(a, b) / dot(b, b)) * b
  double dot_ab = lm2_dot_v2f64(a, b);
  double dot_bb = lm2_dot_v2f64(b, b);
  double scalar = lm2_div_f64(dot_ab, dot_bb);
  lm2_v2f64 result;
  result.x = lm2_mul_f64(scalar, b.x);
  result.y = lm2_mul_f64(scalar, b.y);
  return result;
}

LM2_API lm2_v2f32 lm2_project_v2f32(lm2_v2f32 a, lm2_v2f32 b) {
  // (dot(a, b) / dot(b, b)) * b
  float dot_ab = lm2_dot_v2f32(a, b);
  float dot_bb = lm2_dot_v2f32(b, b);
  float scalar = lm2_div_f32(dot_ab, dot_bb);
  lm2_v2f32 result;
  result.x = lm2_mul_f32(scalar, b.x);
  result.y = lm2_mul_f32(scalar, b.y);
  return result;
}

LM2_API lm2_v3f64 lm2_project_v3f64(lm2_v3f64 a, lm2_v3f64 b) {
  // (dot(a, b) / dot(b, b)) * b
  double dot_ab = lm2_dot_v3f64(a, b);
  double dot_bb = lm2_dot_v3f64(b, b);
  double scalar = lm2_div_f64(dot_ab, dot_bb);
  lm2_v3f64 result;
  result.x = lm2_mul_f64(scalar, b.x);
  result.y = lm2_mul_f64(scalar, b.y);
  result.z = lm2_mul_f64(scalar, b.z);
  return result;
}

LM2_API lm2_v3f32 lm2_project_v3f32(lm2_v3f32 a, lm2_v3f32 b) {
  // (dot(a, b) / dot(b, b)) * b
  float dot_ab = lm2_dot_v3f32(a, b);
  float dot_bb = lm2_dot_v3f32(b, b);
  float scalar = lm2_div_f32(dot_ab, dot_bb);
  lm2_v3f32 result;
  result.x = lm2_mul_f32(scalar, b.x);
  result.y = lm2_mul_f32(scalar, b.y);
  result.z = lm2_mul_f32(scalar, b.z);
  return result;
}
