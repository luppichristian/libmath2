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

#include <lm2/lm2_bezier_curves.h>
#include <lm2/lm2_safe_ops.h>
#include <lm2/lm2_scalar.h>
#include <lm2/lm2_vector_specifics.h>

// =============================================================================
// Linear Bezier - 2D (f64)
// =============================================================================

LM2_API lm2_v2f64 lm2_bezier_linear_v2f64(lm2_v2f64 p0, lm2_v2f64 p1, double t) {
  double one_minus_t = lm2_sub_f64(1.0, t);
  lm2_v2f64 term0 = lm2_mul_lm2_v2f64_double(p0, one_minus_t);
  lm2_v2f64 term1 = lm2_mul_lm2_v2f64_double(p1, t);
  return lm2_add_lm2_v2f64(term0, term1);
}

// =============================================================================
// Linear Bezier - 2D (f32)
// =============================================================================

LM2_API lm2_v2f32 lm2_bezier_linear_v2f32(lm2_v2f32 p0, lm2_v2f32 p1, float t) {
  float one_minus_t = lm2_sub_f32(1.0f, t);
  lm2_v2f32 term0 = lm2_mul_lm2_v2f32_float(p0, one_minus_t);
  lm2_v2f32 term1 = lm2_mul_lm2_v2f32_float(p1, t);
  return lm2_add_lm2_v2f32(term0, term1);
}

// =============================================================================
// Linear Bezier - 3D (f64)
// =============================================================================

LM2_API lm2_v3f64 lm2_bezier_linear_v3f64(lm2_v3f64 p0, lm2_v3f64 p1, double t) {
  double one_minus_t = lm2_sub_f64(1.0, t);
  lm2_v3f64 term0 = lm2_mul_lm2_v3f64_double(p0, one_minus_t);
  lm2_v3f64 term1 = lm2_mul_lm2_v3f64_double(p1, t);
  return lm2_add_lm2_v3f64(term0, term1);
}

// =============================================================================
// Linear Bezier - 3D (f32)
// =============================================================================

LM2_API lm2_v3f32 lm2_bezier_linear_v3f32(lm2_v3f32 p0, lm2_v3f32 p1, float t) {
  float one_minus_t = lm2_sub_f32(1.0f, t);
  lm2_v3f32 term0 = lm2_mul_lm2_v3f32_float(p0, one_minus_t);
  lm2_v3f32 term1 = lm2_mul_lm2_v3f32_float(p1, t);
  return lm2_add_lm2_v3f32(term0, term1);
}

// =============================================================================
// Linear Bezier - 4D (f64)
// =============================================================================

LM2_API lm2_v4f64 lm2_bezier_linear_v4f64(lm2_v4f64 p0, lm2_v4f64 p1, double t) {
  double one_minus_t = lm2_sub_f64(1.0, t);
  lm2_v4f64 term0 = lm2_mul_lm2_v4f64_double(p0, one_minus_t);
  lm2_v4f64 term1 = lm2_mul_lm2_v4f64_double(p1, t);
  return lm2_add_lm2_v4f64(term0, term1);
}

// =============================================================================
// Linear Bezier - 4D (f32)
// =============================================================================

LM2_API lm2_v4f32 lm2_bezier_linear_v4f32(lm2_v4f32 p0, lm2_v4f32 p1, float t) {
  float one_minus_t = lm2_sub_f32(1.0f, t);
  lm2_v4f32 term0 = lm2_mul_lm2_v4f32_float(p0, one_minus_t);
  lm2_v4f32 term1 = lm2_mul_lm2_v4f32_float(p1, t);
  return lm2_add_lm2_v4f32(term0, term1);
}

// =============================================================================
// Quadratic Bezier - 2D (f64)
// =============================================================================

LM2_API lm2_v2f64 lm2_bezier_quadratic_v2f64(lm2_v2f64 p0, lm2_v2f64 p1, lm2_v2f64 p2, double t) {
  double one_minus_t = lm2_sub_f64(1.0, t);
  double one_minus_t_sq = lm2_mul_f64(one_minus_t, one_minus_t);
  double t_sq = lm2_mul_f64(t, t);
  double two_one_minus_t_t = lm2_mul_f64(2.0, lm2_mul_f64(one_minus_t, t));

  lm2_v2f64 term0 = lm2_mul_lm2_v2f64_double(p0, one_minus_t_sq);
  lm2_v2f64 term1 = lm2_mul_lm2_v2f64_double(p1, two_one_minus_t_t);
  lm2_v2f64 term2 = lm2_mul_lm2_v2f64_double(p2, t_sq);

  return lm2_add_lm2_v2f64(lm2_add_lm2_v2f64(term0, term1), term2);
}

// =============================================================================
// Quadratic Bezier - 2D (f32)
// =============================================================================

LM2_API lm2_v2f32 lm2_bezier_quadratic_v2f32(lm2_v2f32 p0, lm2_v2f32 p1, lm2_v2f32 p2, float t) {
  float one_minus_t = lm2_sub_f32(1.0f, t);
  float one_minus_t_sq = lm2_mul_f32(one_minus_t, one_minus_t);
  float t_sq = lm2_mul_f32(t, t);
  float two_one_minus_t_t = lm2_mul_f32(2.0f, lm2_mul_f32(one_minus_t, t));

  lm2_v2f32 term0 = lm2_mul_lm2_v2f32_float(p0, one_minus_t_sq);
  lm2_v2f32 term1 = lm2_mul_lm2_v2f32_float(p1, two_one_minus_t_t);
  lm2_v2f32 term2 = lm2_mul_lm2_v2f32_float(p2, t_sq);

  return lm2_add_lm2_v2f32(lm2_add_lm2_v2f32(term0, term1), term2);
}

// =============================================================================
// Quadratic Bezier - 3D (f64)
// =============================================================================

LM2_API lm2_v3f64 lm2_bezier_quadratic_v3f64(lm2_v3f64 p0, lm2_v3f64 p1, lm2_v3f64 p2, double t) {
  double one_minus_t = lm2_sub_f64(1.0, t);
  double one_minus_t_sq = lm2_mul_f64(one_minus_t, one_minus_t);
  double t_sq = lm2_mul_f64(t, t);
  double two_one_minus_t_t = lm2_mul_f64(2.0, lm2_mul_f64(one_minus_t, t));

  lm2_v3f64 term0 = lm2_mul_lm2_v3f64_double(p0, one_minus_t_sq);
  lm2_v3f64 term1 = lm2_mul_lm2_v3f64_double(p1, two_one_minus_t_t);
  lm2_v3f64 term2 = lm2_mul_lm2_v3f64_double(p2, t_sq);

  return lm2_add_lm2_v3f64(lm2_add_lm2_v3f64(term0, term1), term2);
}

// =============================================================================
// Quadratic Bezier - 3D (f32)
// =============================================================================

LM2_API lm2_v3f32 lm2_bezier_quadratic_v3f32(lm2_v3f32 p0, lm2_v3f32 p1, lm2_v3f32 p2, float t) {
  float one_minus_t = lm2_sub_f32(1.0f, t);
  float one_minus_t_sq = lm2_mul_f32(one_minus_t, one_minus_t);
  float t_sq = lm2_mul_f32(t, t);
  float two_one_minus_t_t = lm2_mul_f32(2.0f, lm2_mul_f32(one_minus_t, t));

  lm2_v3f32 term0 = lm2_mul_lm2_v3f32_float(p0, one_minus_t_sq);
  lm2_v3f32 term1 = lm2_mul_lm2_v3f32_float(p1, two_one_minus_t_t);
  lm2_v3f32 term2 = lm2_mul_lm2_v3f32_float(p2, t_sq);

  return lm2_add_lm2_v3f32(lm2_add_lm2_v3f32(term0, term1), term2);
}

// =============================================================================
// Quadratic Bezier - 4D (f64)
// =============================================================================

LM2_API lm2_v4f64 lm2_bezier_quadratic_v4f64(lm2_v4f64 p0, lm2_v4f64 p1, lm2_v4f64 p2, double t) {
  double one_minus_t = lm2_sub_f64(1.0, t);
  double one_minus_t_sq = lm2_mul_f64(one_minus_t, one_minus_t);
  double t_sq = lm2_mul_f64(t, t);
  double two_one_minus_t_t = lm2_mul_f64(2.0, lm2_mul_f64(one_minus_t, t));

  lm2_v4f64 term0 = lm2_mul_lm2_v4f64_double(p0, one_minus_t_sq);
  lm2_v4f64 term1 = lm2_mul_lm2_v4f64_double(p1, two_one_minus_t_t);
  lm2_v4f64 term2 = lm2_mul_lm2_v4f64_double(p2, t_sq);

  return lm2_add_lm2_v4f64(lm2_add_lm2_v4f64(term0, term1), term2);
}

// =============================================================================
// Quadratic Bezier - 4D (f32)
// =============================================================================

LM2_API lm2_v4f32 lm2_bezier_quadratic_v4f32(lm2_v4f32 p0, lm2_v4f32 p1, lm2_v4f32 p2, float t) {
  float one_minus_t = lm2_sub_f32(1.0f, t);
  float one_minus_t_sq = lm2_mul_f32(one_minus_t, one_minus_t);
  float t_sq = lm2_mul_f32(t, t);
  float two_one_minus_t_t = lm2_mul_f32(2.0f, lm2_mul_f32(one_minus_t, t));

  lm2_v4f32 term0 = lm2_mul_lm2_v4f32_float(p0, one_minus_t_sq);
  lm2_v4f32 term1 = lm2_mul_lm2_v4f32_float(p1, two_one_minus_t_t);
  lm2_v4f32 term2 = lm2_mul_lm2_v4f32_float(p2, t_sq);

  return lm2_add_lm2_v4f32(lm2_add_lm2_v4f32(term0, term1), term2);
}

// =============================================================================
// Cubic Bezier - 2D (f64)
// =============================================================================

LM2_API lm2_v2f64 lm2_bezier_cubic_v2f64(lm2_v2f64 p0, lm2_v2f64 p1, lm2_v2f64 p2, lm2_v2f64 p3, double t) {
  double one_minus_t = lm2_sub_f64(1.0, t);
  double one_minus_t_sq = lm2_mul_f64(one_minus_t, one_minus_t);
  double one_minus_t_cu = lm2_mul_f64(one_minus_t_sq, one_minus_t);
  double t_sq = lm2_mul_f64(t, t);
  double t_cu = lm2_mul_f64(t_sq, t);

  double coef0 = one_minus_t_cu;
  double coef1 = lm2_mul_f64(3.0, lm2_mul_f64(one_minus_t_sq, t));
  double coef2 = lm2_mul_f64(3.0, lm2_mul_f64(one_minus_t, t_sq));
  double coef3 = t_cu;

  lm2_v2f64 term0 = lm2_mul_lm2_v2f64_double(p0, coef0);
  lm2_v2f64 term1 = lm2_mul_lm2_v2f64_double(p1, coef1);
  lm2_v2f64 term2 = lm2_mul_lm2_v2f64_double(p2, coef2);
  lm2_v2f64 term3 = lm2_mul_lm2_v2f64_double(p3, coef3);

  return lm2_add_lm2_v2f64(lm2_add_lm2_v2f64(term0, term1), lm2_add_lm2_v2f64(term2, term3));
}

// =============================================================================
// Cubic Bezier - 2D (f32)
// =============================================================================

LM2_API lm2_v2f32 lm2_bezier_cubic_v2f32(lm2_v2f32 p0, lm2_v2f32 p1, lm2_v2f32 p2, lm2_v2f32 p3, float t) {
  float one_minus_t = lm2_sub_f32(1.0f, t);
  float one_minus_t_sq = lm2_mul_f32(one_minus_t, one_minus_t);
  float one_minus_t_cu = lm2_mul_f32(one_minus_t_sq, one_minus_t);
  float t_sq = lm2_mul_f32(t, t);
  float t_cu = lm2_mul_f32(t_sq, t);

  float coef0 = one_minus_t_cu;
  float coef1 = lm2_mul_f32(3.0f, lm2_mul_f32(one_minus_t_sq, t));
  float coef2 = lm2_mul_f32(3.0f, lm2_mul_f32(one_minus_t, t_sq));
  float coef3 = t_cu;

  lm2_v2f32 term0 = lm2_mul_lm2_v2f32_float(p0, coef0);
  lm2_v2f32 term1 = lm2_mul_lm2_v2f32_float(p1, coef1);
  lm2_v2f32 term2 = lm2_mul_lm2_v2f32_float(p2, coef2);
  lm2_v2f32 term3 = lm2_mul_lm2_v2f32_float(p3, coef3);

  return lm2_add_lm2_v2f32(lm2_add_lm2_v2f32(term0, term1), lm2_add_lm2_v2f32(term2, term3));
}

// =============================================================================
// Cubic Bezier - 3D (f64)
// =============================================================================

LM2_API lm2_v3f64 lm2_bezier_cubic_v3f64(lm2_v3f64 p0, lm2_v3f64 p1, lm2_v3f64 p2, lm2_v3f64 p3, double t) {
  double one_minus_t = lm2_sub_f64(1.0, t);
  double one_minus_t_sq = lm2_mul_f64(one_minus_t, one_minus_t);
  double one_minus_t_cu = lm2_mul_f64(one_minus_t_sq, one_minus_t);
  double t_sq = lm2_mul_f64(t, t);
  double t_cu = lm2_mul_f64(t_sq, t);

  double coef0 = one_minus_t_cu;
  double coef1 = lm2_mul_f64(3.0, lm2_mul_f64(one_minus_t_sq, t));
  double coef2 = lm2_mul_f64(3.0, lm2_mul_f64(one_minus_t, t_sq));
  double coef3 = t_cu;

  lm2_v3f64 term0 = lm2_mul_lm2_v3f64_double(p0, coef0);
  lm2_v3f64 term1 = lm2_mul_lm2_v3f64_double(p1, coef1);
  lm2_v3f64 term2 = lm2_mul_lm2_v3f64_double(p2, coef2);
  lm2_v3f64 term3 = lm2_mul_lm2_v3f64_double(p3, coef3);

  return lm2_add_lm2_v3f64(lm2_add_lm2_v3f64(term0, term1), lm2_add_lm2_v3f64(term2, term3));
}

// =============================================================================
// Cubic Bezier - 3D (f32)
// =============================================================================

LM2_API lm2_v3f32 lm2_bezier_cubic_v3f32(lm2_v3f32 p0, lm2_v3f32 p1, lm2_v3f32 p2, lm2_v3f32 p3, float t) {
  float one_minus_t = lm2_sub_f32(1.0f, t);
  float one_minus_t_sq = lm2_mul_f32(one_minus_t, one_minus_t);
  float one_minus_t_cu = lm2_mul_f32(one_minus_t_sq, one_minus_t);
  float t_sq = lm2_mul_f32(t, t);
  float t_cu = lm2_mul_f32(t_sq, t);

  float coef0 = one_minus_t_cu;
  float coef1 = lm2_mul_f32(3.0f, lm2_mul_f32(one_minus_t_sq, t));
  float coef2 = lm2_mul_f32(3.0f, lm2_mul_f32(one_minus_t, t_sq));
  float coef3 = t_cu;

  lm2_v3f32 term0 = lm2_mul_lm2_v3f32_float(p0, coef0);
  lm2_v3f32 term1 = lm2_mul_lm2_v3f32_float(p1, coef1);
  lm2_v3f32 term2 = lm2_mul_lm2_v3f32_float(p2, coef2);
  lm2_v3f32 term3 = lm2_mul_lm2_v3f32_float(p3, coef3);

  return lm2_add_lm2_v3f32(lm2_add_lm2_v3f32(term0, term1), lm2_add_lm2_v3f32(term2, term3));
}

// =============================================================================
// Cubic Bezier - 4D (f64)
// =============================================================================

LM2_API lm2_v4f64 lm2_bezier_cubic_v4f64(lm2_v4f64 p0, lm2_v4f64 p1, lm2_v4f64 p2, lm2_v4f64 p3, double t) {
  double one_minus_t = lm2_sub_f64(1.0, t);
  double one_minus_t_sq = lm2_mul_f64(one_minus_t, one_minus_t);
  double one_minus_t_cu = lm2_mul_f64(one_minus_t_sq, one_minus_t);
  double t_sq = lm2_mul_f64(t, t);
  double t_cu = lm2_mul_f64(t_sq, t);

  double coef0 = one_minus_t_cu;
  double coef1 = lm2_mul_f64(3.0, lm2_mul_f64(one_minus_t_sq, t));
  double coef2 = lm2_mul_f64(3.0, lm2_mul_f64(one_minus_t, t_sq));
  double coef3 = t_cu;

  lm2_v4f64 term0 = lm2_mul_lm2_v4f64_double(p0, coef0);
  lm2_v4f64 term1 = lm2_mul_lm2_v4f64_double(p1, coef1);
  lm2_v4f64 term2 = lm2_mul_lm2_v4f64_double(p2, coef2);
  lm2_v4f64 term3 = lm2_mul_lm2_v4f64_double(p3, coef3);

  return lm2_add_lm2_v4f64(lm2_add_lm2_v4f64(term0, term1), lm2_add_lm2_v4f64(term2, term3));
}

// =============================================================================
// Cubic Bezier - 4D (f32)
// =============================================================================

LM2_API lm2_v4f32 lm2_bezier_cubic_v4f32(lm2_v4f32 p0, lm2_v4f32 p1, lm2_v4f32 p2, lm2_v4f32 p3, float t) {
  float one_minus_t = lm2_sub_f32(1.0f, t);
  float one_minus_t_sq = lm2_mul_f32(one_minus_t, one_minus_t);
  float one_minus_t_cu = lm2_mul_f32(one_minus_t_sq, one_minus_t);
  float t_sq = lm2_mul_f32(t, t);
  float t_cu = lm2_mul_f32(t_sq, t);

  float coef0 = one_minus_t_cu;
  float coef1 = lm2_mul_f32(3.0f, lm2_mul_f32(one_minus_t_sq, t));
  float coef2 = lm2_mul_f32(3.0f, lm2_mul_f32(one_minus_t, t_sq));
  float coef3 = t_cu;

  lm2_v4f32 term0 = lm2_mul_lm2_v4f32_float(p0, coef0);
  lm2_v4f32 term1 = lm2_mul_lm2_v4f32_float(p1, coef1);
  lm2_v4f32 term2 = lm2_mul_lm2_v4f32_float(p2, coef2);
  lm2_v4f32 term3 = lm2_mul_lm2_v4f32_float(p3, coef3);

  return lm2_add_lm2_v4f32(lm2_add_lm2_v4f32(term0, term1), lm2_add_lm2_v4f32(term2, term3));
}

// =============================================================================
// Quadratic Bezier Derivative - 2D (f64)
// =============================================================================

LM2_API lm2_v2f64 lm2_bezier_quadratic_derivative_v2f64(lm2_v2f64 p0, lm2_v2f64 p1, lm2_v2f64 p2, double t) {
  double one_minus_t = lm2_sub_f64(1.0, t);
  double two_one_minus_t = lm2_mul_f64(2.0, one_minus_t);
  double two_t = lm2_mul_f64(2.0, t);

  lm2_v2f64 diff01 = lm2_sub_lm2_v2f64(p1, p0);
  lm2_v2f64 diff12 = lm2_sub_lm2_v2f64(p2, p1);

  lm2_v2f64 term0 = lm2_mul_lm2_v2f64_double(diff01, two_one_minus_t);
  lm2_v2f64 term1 = lm2_mul_lm2_v2f64_double(diff12, two_t);

  return lm2_add_lm2_v2f64(term0, term1);
}

// =============================================================================
// Quadratic Bezier Derivative - 2D (f32)
// =============================================================================

LM2_API lm2_v2f32 lm2_bezier_quadratic_derivative_v2f32(lm2_v2f32 p0, lm2_v2f32 p1, lm2_v2f32 p2, float t) {
  float one_minus_t = lm2_sub_f32(1.0f, t);
  float two_one_minus_t = lm2_mul_f32(2.0f, one_minus_t);
  float two_t = lm2_mul_f32(2.0f, t);

  lm2_v2f32 diff01 = lm2_sub_lm2_v2f32(p1, p0);
  lm2_v2f32 diff12 = lm2_sub_lm2_v2f32(p2, p1);

  lm2_v2f32 term0 = lm2_mul_lm2_v2f32_float(diff01, two_one_minus_t);
  lm2_v2f32 term1 = lm2_mul_lm2_v2f32_float(diff12, two_t);

  return lm2_add_lm2_v2f32(term0, term1);
}

// =============================================================================
// Quadratic Bezier Derivative - 3D (f64)
// =============================================================================

LM2_API lm2_v3f64 lm2_bezier_quadratic_derivative_v3f64(lm2_v3f64 p0, lm2_v3f64 p1, lm2_v3f64 p2, double t) {
  double one_minus_t = lm2_sub_f64(1.0, t);
  double two_one_minus_t = lm2_mul_f64(2.0, one_minus_t);
  double two_t = lm2_mul_f64(2.0, t);

  lm2_v3f64 diff01 = lm2_sub_lm2_v3f64(p1, p0);
  lm2_v3f64 diff12 = lm2_sub_lm2_v3f64(p2, p1);

  lm2_v3f64 term0 = lm2_mul_lm2_v3f64_double(diff01, two_one_minus_t);
  lm2_v3f64 term1 = lm2_mul_lm2_v3f64_double(diff12, two_t);

  return lm2_add_lm2_v3f64(term0, term1);
}

// =============================================================================
// Quadratic Bezier Derivative - 3D (f32)
// =============================================================================

LM2_API lm2_v3f32 lm2_bezier_quadratic_derivative_v3f32(lm2_v3f32 p0, lm2_v3f32 p1, lm2_v3f32 p2, float t) {
  float one_minus_t = lm2_sub_f32(1.0f, t);
  float two_one_minus_t = lm2_mul_f32(2.0f, one_minus_t);
  float two_t = lm2_mul_f32(2.0f, t);

  lm2_v3f32 diff01 = lm2_sub_lm2_v3f32(p1, p0);
  lm2_v3f32 diff12 = lm2_sub_lm2_v3f32(p2, p1);

  lm2_v3f32 term0 = lm2_mul_lm2_v3f32_float(diff01, two_one_minus_t);
  lm2_v3f32 term1 = lm2_mul_lm2_v3f32_float(diff12, two_t);

  return lm2_add_lm2_v3f32(term0, term1);
}

// =============================================================================
// Quadratic Bezier Derivative - 4D (f64)
// =============================================================================

LM2_API lm2_v4f64 lm2_bezier_quadratic_derivative_v4f64(lm2_v4f64 p0, lm2_v4f64 p1, lm2_v4f64 p2, double t) {
  double one_minus_t = lm2_sub_f64(1.0, t);
  double two_one_minus_t = lm2_mul_f64(2.0, one_minus_t);
  double two_t = lm2_mul_f64(2.0, t);

  lm2_v4f64 diff01 = lm2_sub_lm2_v4f64(p1, p0);
  lm2_v4f64 diff12 = lm2_sub_lm2_v4f64(p2, p1);

  lm2_v4f64 term0 = lm2_mul_lm2_v4f64_double(diff01, two_one_minus_t);
  lm2_v4f64 term1 = lm2_mul_lm2_v4f64_double(diff12, two_t);

  return lm2_add_lm2_v4f64(term0, term1);
}

// =============================================================================
// Quadratic Bezier Derivative - 4D (f32)
// =============================================================================

LM2_API lm2_v4f32 lm2_bezier_quadratic_derivative_v4f32(lm2_v4f32 p0, lm2_v4f32 p1, lm2_v4f32 p2, float t) {
  float one_minus_t = lm2_sub_f32(1.0f, t);
  float two_one_minus_t = lm2_mul_f32(2.0f, one_minus_t);
  float two_t = lm2_mul_f32(2.0f, t);

  lm2_v4f32 diff01 = lm2_sub_lm2_v4f32(p1, p0);
  lm2_v4f32 diff12 = lm2_sub_lm2_v4f32(p2, p1);

  lm2_v4f32 term0 = lm2_mul_lm2_v4f32_float(diff01, two_one_minus_t);
  lm2_v4f32 term1 = lm2_mul_lm2_v4f32_float(diff12, two_t);

  return lm2_add_lm2_v4f32(term0, term1);
}

// =============================================================================
// Cubic Bezier Derivative - 2D (f64)
// =============================================================================

LM2_API lm2_v2f64 lm2_bezier_cubic_derivative_v2f64(lm2_v2f64 p0, lm2_v2f64 p1, lm2_v2f64 p2, lm2_v2f64 p3, double t) {
  double one_minus_t = lm2_sub_f64(1.0, t);
  double one_minus_t_sq = lm2_mul_f64(one_minus_t, one_minus_t);
  double t_sq = lm2_mul_f64(t, t);

  double coef0 = lm2_mul_f64(3.0, one_minus_t_sq);
  double coef1 = lm2_mul_f64(6.0, lm2_mul_f64(one_minus_t, t));
  double coef2 = lm2_mul_f64(3.0, t_sq);

  lm2_v2f64 diff01 = lm2_sub_lm2_v2f64(p1, p0);
  lm2_v2f64 diff12 = lm2_sub_lm2_v2f64(p2, p1);
  lm2_v2f64 diff23 = lm2_sub_lm2_v2f64(p3, p2);

  lm2_v2f64 term0 = lm2_mul_lm2_v2f64_double(diff01, coef0);
  lm2_v2f64 term1 = lm2_mul_lm2_v2f64_double(diff12, coef1);
  lm2_v2f64 term2 = lm2_mul_lm2_v2f64_double(diff23, coef2);

  return lm2_add_lm2_v2f64(lm2_add_lm2_v2f64(term0, term1), term2);
}

// =============================================================================
// Cubic Bezier Derivative - 2D (f32)
// =============================================================================

LM2_API lm2_v2f32 lm2_bezier_cubic_derivative_v2f32(lm2_v2f32 p0, lm2_v2f32 p1, lm2_v2f32 p2, lm2_v2f32 p3, float t) {
  float one_minus_t = lm2_sub_f32(1.0f, t);
  float one_minus_t_sq = lm2_mul_f32(one_minus_t, one_minus_t);
  float t_sq = lm2_mul_f32(t, t);

  float coef0 = lm2_mul_f32(3.0f, one_minus_t_sq);
  float coef1 = lm2_mul_f32(6.0f, lm2_mul_f32(one_minus_t, t));
  float coef2 = lm2_mul_f32(3.0f, t_sq);

  lm2_v2f32 diff01 = lm2_sub_lm2_v2f32(p1, p0);
  lm2_v2f32 diff12 = lm2_sub_lm2_v2f32(p2, p1);
  lm2_v2f32 diff23 = lm2_sub_lm2_v2f32(p3, p2);

  lm2_v2f32 term0 = lm2_mul_lm2_v2f32_float(diff01, coef0);
  lm2_v2f32 term1 = lm2_mul_lm2_v2f32_float(diff12, coef1);
  lm2_v2f32 term2 = lm2_mul_lm2_v2f32_float(diff23, coef2);

  return lm2_add_lm2_v2f32(lm2_add_lm2_v2f32(term0, term1), term2);
}

// =============================================================================
// Cubic Bezier Derivative - 3D (f64)
// =============================================================================

LM2_API lm2_v3f64 lm2_bezier_cubic_derivative_v3f64(lm2_v3f64 p0, lm2_v3f64 p1, lm2_v3f64 p2, lm2_v3f64 p3, double t) {
  double one_minus_t = lm2_sub_f64(1.0, t);
  double one_minus_t_sq = lm2_mul_f64(one_minus_t, one_minus_t);
  double t_sq = lm2_mul_f64(t, t);

  double coef0 = lm2_mul_f64(3.0, one_minus_t_sq);
  double coef1 = lm2_mul_f64(6.0, lm2_mul_f64(one_minus_t, t));
  double coef2 = lm2_mul_f64(3.0, t_sq);

  lm2_v3f64 diff01 = lm2_sub_lm2_v3f64(p1, p0);
  lm2_v3f64 diff12 = lm2_sub_lm2_v3f64(p2, p1);
  lm2_v3f64 diff23 = lm2_sub_lm2_v3f64(p3, p2);

  lm2_v3f64 term0 = lm2_mul_lm2_v3f64_double(diff01, coef0);
  lm2_v3f64 term1 = lm2_mul_lm2_v3f64_double(diff12, coef1);
  lm2_v3f64 term2 = lm2_mul_lm2_v3f64_double(diff23, coef2);

  return lm2_add_lm2_v3f64(lm2_add_lm2_v3f64(term0, term1), term2);
}

// =============================================================================
// Cubic Bezier Derivative - 3D (f32)
// =============================================================================

LM2_API lm2_v3f32 lm2_bezier_cubic_derivative_v3f32(lm2_v3f32 p0, lm2_v3f32 p1, lm2_v3f32 p2, lm2_v3f32 p3, float t) {
  float one_minus_t = lm2_sub_f32(1.0f, t);
  float one_minus_t_sq = lm2_mul_f32(one_minus_t, one_minus_t);
  float t_sq = lm2_mul_f32(t, t);

  float coef0 = lm2_mul_f32(3.0f, one_minus_t_sq);
  float coef1 = lm2_mul_f32(6.0f, lm2_mul_f32(one_minus_t, t));
  float coef2 = lm2_mul_f32(3.0f, t_sq);

  lm2_v3f32 diff01 = lm2_sub_lm2_v3f32(p1, p0);
  lm2_v3f32 diff12 = lm2_sub_lm2_v3f32(p2, p1);
  lm2_v3f32 diff23 = lm2_sub_lm2_v3f32(p3, p2);

  lm2_v3f32 term0 = lm2_mul_lm2_v3f32_float(diff01, coef0);
  lm2_v3f32 term1 = lm2_mul_lm2_v3f32_float(diff12, coef1);
  lm2_v3f32 term2 = lm2_mul_lm2_v3f32_float(diff23, coef2);

  return lm2_add_lm2_v3f32(lm2_add_lm2_v3f32(term0, term1), term2);
}

// =============================================================================
// Cubic Bezier Derivative - 4D (f64)
// =============================================================================

LM2_API lm2_v4f64 lm2_bezier_cubic_derivative_v4f64(lm2_v4f64 p0, lm2_v4f64 p1, lm2_v4f64 p2, lm2_v4f64 p3, double t) {
  double one_minus_t = lm2_sub_f64(1.0, t);
  double one_minus_t_sq = lm2_mul_f64(one_minus_t, one_minus_t);
  double t_sq = lm2_mul_f64(t, t);

  double coef0 = lm2_mul_f64(3.0, one_minus_t_sq);
  double coef1 = lm2_mul_f64(6.0, lm2_mul_f64(one_minus_t, t));
  double coef2 = lm2_mul_f64(3.0, t_sq);

  lm2_v4f64 diff01 = lm2_sub_lm2_v4f64(p1, p0);
  lm2_v4f64 diff12 = lm2_sub_lm2_v4f64(p2, p1);
  lm2_v4f64 diff23 = lm2_sub_lm2_v4f64(p3, p2);

  lm2_v4f64 term0 = lm2_mul_lm2_v4f64_double(diff01, coef0);
  lm2_v4f64 term1 = lm2_mul_lm2_v4f64_double(diff12, coef1);
  lm2_v4f64 term2 = lm2_mul_lm2_v4f64_double(diff23, coef2);

  return lm2_add_lm2_v4f64(lm2_add_lm2_v4f64(term0, term1), term2);
}

// =============================================================================
// Cubic Bezier Derivative - 4D (f32)
// =============================================================================

LM2_API lm2_v4f32 lm2_bezier_cubic_derivative_v4f32(lm2_v4f32 p0, lm2_v4f32 p1, lm2_v4f32 p2, lm2_v4f32 p3, float t) {
  float one_minus_t = lm2_sub_f32(1.0f, t);
  float one_minus_t_sq = lm2_mul_f32(one_minus_t, one_minus_t);
  float t_sq = lm2_mul_f32(t, t);

  float coef0 = lm2_mul_f32(3.0f, one_minus_t_sq);
  float coef1 = lm2_mul_f32(6.0f, lm2_mul_f32(one_minus_t, t));
  float coef2 = lm2_mul_f32(3.0f, t_sq);

  lm2_v4f32 diff01 = lm2_sub_lm2_v4f32(p1, p0);
  lm2_v4f32 diff12 = lm2_sub_lm2_v4f32(p2, p1);
  lm2_v4f32 diff23 = lm2_sub_lm2_v4f32(p3, p2);

  lm2_v4f32 term0 = lm2_mul_lm2_v4f32_float(diff01, coef0);
  lm2_v4f32 term1 = lm2_mul_lm2_v4f32_float(diff12, coef1);
  lm2_v4f32 term2 = lm2_mul_lm2_v4f32_float(diff23, coef2);

  return lm2_add_lm2_v4f32(lm2_add_lm2_v4f32(term0, term1), term2);
}

// =============================================================================
// Cubic Bezier Second Derivative - 2D (f64)
// =============================================================================

LM2_API lm2_v2f64 lm2_bezier_cubic_second_derivative_v2f64(lm2_v2f64 p0, lm2_v2f64 p1, lm2_v2f64 p2, lm2_v2f64 p3, double t) {
  double one_minus_t = lm2_sub_f64(1.0, t);
  double six_one_minus_t = lm2_mul_f64(6.0, one_minus_t);
  double six_t = lm2_mul_f64(6.0, t);

  // P2 - 2*P1 + P0
  lm2_v2f64 two_p1 = lm2_mul_lm2_v2f64_double(p1, 2.0);
  lm2_v2f64 diff0 = lm2_sub_lm2_v2f64(lm2_add_lm2_v2f64(p2, p0), two_p1);

  // P3 - 2*P2 + P1
  lm2_v2f64 two_p2 = lm2_mul_lm2_v2f64_double(p2, 2.0);
  lm2_v2f64 diff1 = lm2_sub_lm2_v2f64(lm2_add_lm2_v2f64(p3, p1), two_p2);

  lm2_v2f64 term0 = lm2_mul_lm2_v2f64_double(diff0, six_one_minus_t);
  lm2_v2f64 term1 = lm2_mul_lm2_v2f64_double(diff1, six_t);

  return lm2_add_lm2_v2f64(term0, term1);
}

// =============================================================================
// Cubic Bezier Second Derivative - 2D (f32)
// =============================================================================

LM2_API lm2_v2f32 lm2_bezier_cubic_second_derivative_v2f32(lm2_v2f32 p0, lm2_v2f32 p1, lm2_v2f32 p2, lm2_v2f32 p3, float t) {
  float one_minus_t = lm2_sub_f32(1.0f, t);
  float six_one_minus_t = lm2_mul_f32(6.0f, one_minus_t);
  float six_t = lm2_mul_f32(6.0f, t);

  // P2 - 2*P1 + P0
  lm2_v2f32 two_p1 = lm2_mul_lm2_v2f32_float(p1, 2.0f);
  lm2_v2f32 diff0 = lm2_sub_lm2_v2f32(lm2_add_lm2_v2f32(p2, p0), two_p1);

  // P3 - 2*P2 + P1
  lm2_v2f32 two_p2 = lm2_mul_lm2_v2f32_float(p2, 2.0f);
  lm2_v2f32 diff1 = lm2_sub_lm2_v2f32(lm2_add_lm2_v2f32(p3, p1), two_p2);

  lm2_v2f32 term0 = lm2_mul_lm2_v2f32_float(diff0, six_one_minus_t);
  lm2_v2f32 term1 = lm2_mul_lm2_v2f32_float(diff1, six_t);

  return lm2_add_lm2_v2f32(term0, term1);
}

// =============================================================================
// Cubic Bezier Second Derivative - 3D (f64)
// =============================================================================

LM2_API lm2_v3f64 lm2_bezier_cubic_second_derivative_v3f64(lm2_v3f64 p0, lm2_v3f64 p1, lm2_v3f64 p2, lm2_v3f64 p3, double t) {
  double one_minus_t = lm2_sub_f64(1.0, t);
  double six_one_minus_t = lm2_mul_f64(6.0, one_minus_t);
  double six_t = lm2_mul_f64(6.0, t);

  // P2 - 2*P1 + P0
  lm2_v3f64 two_p1 = lm2_mul_lm2_v3f64_double(p1, 2.0);
  lm2_v3f64 diff0 = lm2_sub_lm2_v3f64(lm2_add_lm2_v3f64(p2, p0), two_p1);

  // P3 - 2*P2 + P1
  lm2_v3f64 two_p2 = lm2_mul_lm2_v3f64_double(p2, 2.0);
  lm2_v3f64 diff1 = lm2_sub_lm2_v3f64(lm2_add_lm2_v3f64(p3, p1), two_p2);

  lm2_v3f64 term0 = lm2_mul_lm2_v3f64_double(diff0, six_one_minus_t);
  lm2_v3f64 term1 = lm2_mul_lm2_v3f64_double(diff1, six_t);

  return lm2_add_lm2_v3f64(term0, term1);
}

// =============================================================================
// Cubic Bezier Second Derivative - 3D (f32)
// =============================================================================

LM2_API lm2_v3f32 lm2_bezier_cubic_second_derivative_v3f32(lm2_v3f32 p0, lm2_v3f32 p1, lm2_v3f32 p2, lm2_v3f32 p3, float t) {
  float one_minus_t = lm2_sub_f32(1.0f, t);
  float six_one_minus_t = lm2_mul_f32(6.0f, one_minus_t);
  float six_t = lm2_mul_f32(6.0f, t);

  // P2 - 2*P1 + P0
  lm2_v3f32 two_p1 = lm2_mul_lm2_v3f32_float(p1, 2.0f);
  lm2_v3f32 diff0 = lm2_sub_lm2_v3f32(lm2_add_lm2_v3f32(p2, p0), two_p1);

  // P3 - 2*P2 + P1
  lm2_v3f32 two_p2 = lm2_mul_lm2_v3f32_float(p2, 2.0f);
  lm2_v3f32 diff1 = lm2_sub_lm2_v3f32(lm2_add_lm2_v3f32(p3, p1), two_p2);

  lm2_v3f32 term0 = lm2_mul_lm2_v3f32_float(diff0, six_one_minus_t);
  lm2_v3f32 term1 = lm2_mul_lm2_v3f32_float(diff1, six_t);

  return lm2_add_lm2_v3f32(term0, term1);
}

// =============================================================================
// Cubic Bezier Second Derivative - 4D (f64)
// =============================================================================

LM2_API lm2_v4f64 lm2_bezier_cubic_second_derivative_v4f64(lm2_v4f64 p0, lm2_v4f64 p1, lm2_v4f64 p2, lm2_v4f64 p3, double t) {
  double one_minus_t = lm2_sub_f64(1.0, t);
  double six_one_minus_t = lm2_mul_f64(6.0, one_minus_t);
  double six_t = lm2_mul_f64(6.0, t);

  // P2 - 2*P1 + P0
  lm2_v4f64 two_p1 = lm2_mul_lm2_v4f64_double(p1, 2.0);
  lm2_v4f64 diff0 = lm2_sub_lm2_v4f64(lm2_add_lm2_v4f64(p2, p0), two_p1);

  // P3 - 2*P2 + P1
  lm2_v4f64 two_p2 = lm2_mul_lm2_v4f64_double(p2, 2.0);
  lm2_v4f64 diff1 = lm2_sub_lm2_v4f64(lm2_add_lm2_v4f64(p3, p1), two_p2);

  lm2_v4f64 term0 = lm2_mul_lm2_v4f64_double(diff0, six_one_minus_t);
  lm2_v4f64 term1 = lm2_mul_lm2_v4f64_double(diff1, six_t);

  return lm2_add_lm2_v4f64(term0, term1);
}

// =============================================================================
// Cubic Bezier Second Derivative - 4D (f32)
// =============================================================================

LM2_API lm2_v4f32 lm2_bezier_cubic_second_derivative_v4f32(lm2_v4f32 p0, lm2_v4f32 p1, lm2_v4f32 p2, lm2_v4f32 p3, float t) {
  float one_minus_t = lm2_sub_f32(1.0f, t);
  float six_one_minus_t = lm2_mul_f32(6.0f, one_minus_t);
  float six_t = lm2_mul_f32(6.0f, t);

  // P2 - 2*P1 + P0
  lm2_v4f32 two_p1 = lm2_mul_lm2_v4f32_float(p1, 2.0f);
  lm2_v4f32 diff0 = lm2_sub_lm2_v4f32(lm2_add_lm2_v4f32(p2, p0), two_p1);

  // P3 - 2*P2 + P1
  lm2_v4f32 two_p2 = lm2_mul_lm2_v4f32_float(p2, 2.0f);
  lm2_v4f32 diff1 = lm2_sub_lm2_v4f32(lm2_add_lm2_v4f32(p3, p1), two_p2);

  lm2_v4f32 term0 = lm2_mul_lm2_v4f32_float(diff0, six_one_minus_t);
  lm2_v4f32 term1 = lm2_mul_lm2_v4f32_float(diff1, six_t);

  return lm2_add_lm2_v4f32(term0, term1);
}

// =============================================================================
// Cubic Bezier Split - 2D (f64)
// Uses De Casteljau's algorithm
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
    lm2_v2f64* right_p3) {
  // First level
  lm2_v2f64 p01 = lm2_bezier_linear_v2f64(p0, p1, t);
  lm2_v2f64 p12 = lm2_bezier_linear_v2f64(p1, p2, t);
  lm2_v2f64 p23 = lm2_bezier_linear_v2f64(p2, p3, t);

  // Second level
  lm2_v2f64 p012 = lm2_bezier_linear_v2f64(p01, p12, t);
  lm2_v2f64 p123 = lm2_bezier_linear_v2f64(p12, p23, t);

  // Third level (point on curve)
  lm2_v2f64 p0123 = lm2_bezier_linear_v2f64(p012, p123, t);

  // Left curve
  *left_p0 = p0;
  *left_p1 = p01;
  *left_p2 = p012;
  *left_p3 = p0123;

  // Right curve
  *right_p0 = p0123;
  *right_p1 = p123;
  *right_p2 = p23;
  *right_p3 = p3;
}

// =============================================================================
// Cubic Bezier Split - 2D (f32)
// =============================================================================

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
    lm2_v2f32* right_p3) {
  // First level
  lm2_v2f32 p01 = lm2_bezier_linear_v2f32(p0, p1, t);
  lm2_v2f32 p12 = lm2_bezier_linear_v2f32(p1, p2, t);
  lm2_v2f32 p23 = lm2_bezier_linear_v2f32(p2, p3, t);

  // Second level
  lm2_v2f32 p012 = lm2_bezier_linear_v2f32(p01, p12, t);
  lm2_v2f32 p123 = lm2_bezier_linear_v2f32(p12, p23, t);

  // Third level (point on curve)
  lm2_v2f32 p0123 = lm2_bezier_linear_v2f32(p012, p123, t);

  // Left curve
  *left_p0 = p0;
  *left_p1 = p01;
  *left_p2 = p012;
  *left_p3 = p0123;

  // Right curve
  *right_p0 = p0123;
  *right_p1 = p123;
  *right_p2 = p23;
  *right_p3 = p3;
}

// =============================================================================
// Cubic Bezier Split - 3D (f64)
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
    lm2_v3f64* right_p3) {
  // First level
  lm2_v3f64 p01 = lm2_bezier_linear_v3f64(p0, p1, t);
  lm2_v3f64 p12 = lm2_bezier_linear_v3f64(p1, p2, t);
  lm2_v3f64 p23 = lm2_bezier_linear_v3f64(p2, p3, t);

  // Second level
  lm2_v3f64 p012 = lm2_bezier_linear_v3f64(p01, p12, t);
  lm2_v3f64 p123 = lm2_bezier_linear_v3f64(p12, p23, t);

  // Third level (point on curve)
  lm2_v3f64 p0123 = lm2_bezier_linear_v3f64(p012, p123, t);

  // Left curve
  *left_p0 = p0;
  *left_p1 = p01;
  *left_p2 = p012;
  *left_p3 = p0123;

  // Right curve
  *right_p0 = p0123;
  *right_p1 = p123;
  *right_p2 = p23;
  *right_p3 = p3;
}

// =============================================================================
// Cubic Bezier Split - 3D (f32)
// =============================================================================

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
    lm2_v3f32* right_p3) {
  // First level
  lm2_v3f32 p01 = lm2_bezier_linear_v3f32(p0, p1, t);
  lm2_v3f32 p12 = lm2_bezier_linear_v3f32(p1, p2, t);
  lm2_v3f32 p23 = lm2_bezier_linear_v3f32(p2, p3, t);

  // Second level
  lm2_v3f32 p012 = lm2_bezier_linear_v3f32(p01, p12, t);
  lm2_v3f32 p123 = lm2_bezier_linear_v3f32(p12, p23, t);

  // Third level (point on curve)
  lm2_v3f32 p0123 = lm2_bezier_linear_v3f32(p012, p123, t);

  // Left curve
  *left_p0 = p0;
  *left_p1 = p01;
  *left_p2 = p012;
  *left_p3 = p0123;

  // Right curve
  *right_p0 = p0123;
  *right_p1 = p123;
  *right_p2 = p23;
  *right_p3 = p3;
}

// =============================================================================
// Cubic Bezier Split - 4D (f64)
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
    lm2_v4f64* right_p3) {
  // First level
  lm2_v4f64 p01 = lm2_bezier_linear_v4f64(p0, p1, t);
  lm2_v4f64 p12 = lm2_bezier_linear_v4f64(p1, p2, t);
  lm2_v4f64 p23 = lm2_bezier_linear_v4f64(p2, p3, t);

  // Second level
  lm2_v4f64 p012 = lm2_bezier_linear_v4f64(p01, p12, t);
  lm2_v4f64 p123 = lm2_bezier_linear_v4f64(p12, p23, t);

  // Third level (point on curve)
  lm2_v4f64 p0123 = lm2_bezier_linear_v4f64(p012, p123, t);

  // Left curve
  *left_p0 = p0;
  *left_p1 = p01;
  *left_p2 = p012;
  *left_p3 = p0123;

  // Right curve
  *right_p0 = p0123;
  *right_p1 = p123;
  *right_p2 = p23;
  *right_p3 = p3;
}

// =============================================================================
// Cubic Bezier Split - 4D (f32)
// =============================================================================

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
    lm2_v4f32* right_p3) {
  // First level
  lm2_v4f32 p01 = lm2_bezier_linear_v4f32(p0, p1, t);
  lm2_v4f32 p12 = lm2_bezier_linear_v4f32(p1, p2, t);
  lm2_v4f32 p23 = lm2_bezier_linear_v4f32(p2, p3, t);

  // Second level
  lm2_v4f32 p012 = lm2_bezier_linear_v4f32(p01, p12, t);
  lm2_v4f32 p123 = lm2_bezier_linear_v4f32(p12, p23, t);

  // Third level (point on curve)
  lm2_v4f32 p0123 = lm2_bezier_linear_v4f32(p012, p123, t);

  // Left curve
  *left_p0 = p0;
  *left_p1 = p01;
  *left_p2 = p012;
  *left_p3 = p0123;

  // Right curve
  *right_p0 = p0123;
  *right_p1 = p123;
  *right_p2 = p23;
  *right_p3 = p3;
}

// =============================================================================
// Cubic Bezier Arc Length - 2D (f64)
// =============================================================================

LM2_API double lm2_bezier_cubic_length_v2f64(lm2_v2f64 p0, lm2_v2f64 p1, lm2_v2f64 p2, lm2_v2f64 p3, int segments) {
  double length = 0.0;
  lm2_v2f64 prev_point = p0;

  for (int i = 1; i <= segments; i++) {
    double t = lm2_div_f64((double)i, (double)segments);
    lm2_v2f64 point = lm2_bezier_cubic_v2f64(p0, p1, p2, p3, t);
    length = lm2_add_f64(length, lm2_distance_v2f64(prev_point, point));
    prev_point = point;
  }

  return length;
}

// =============================================================================
// Cubic Bezier Arc Length - 2D (f32)
// =============================================================================

LM2_API float lm2_bezier_cubic_length_v2f32(lm2_v2f32 p0, lm2_v2f32 p1, lm2_v2f32 p2, lm2_v2f32 p3, int segments) {
  float length = 0.0f;
  lm2_v2f32 prev_point = p0;

  for (int i = 1; i <= segments; i++) {
    float t = lm2_div_f32((float)i, (float)segments);
    lm2_v2f32 point = lm2_bezier_cubic_v2f32(p0, p1, p2, p3, t);
    length = lm2_add_f32(length, lm2_distance_v2f32(prev_point, point));
    prev_point = point;
  }

  return length;
}

// =============================================================================
// Cubic Bezier Arc Length - 3D (f64)
// =============================================================================

LM2_API double lm2_bezier_cubic_length_v3f64(lm2_v3f64 p0, lm2_v3f64 p1, lm2_v3f64 p2, lm2_v3f64 p3, int segments) {
  double length = 0.0;
  lm2_v3f64 prev_point = p0;

  for (int i = 1; i <= segments; i++) {
    double t = lm2_div_f64((double)i, (double)segments);
    lm2_v3f64 point = lm2_bezier_cubic_v3f64(p0, p1, p2, p3, t);
    length = lm2_add_f64(length, lm2_distance_v3f64(prev_point, point));
    prev_point = point;
  }

  return length;
}

// =============================================================================
// Cubic Bezier Arc Length - 3D (f32)
// =============================================================================

LM2_API float lm2_bezier_cubic_length_v3f32(lm2_v3f32 p0, lm2_v3f32 p1, lm2_v3f32 p2, lm2_v3f32 p3, int segments) {
  float length = 0.0f;
  lm2_v3f32 prev_point = p0;

  for (int i = 1; i <= segments; i++) {
    float t = lm2_div_f32((float)i, (float)segments);
    lm2_v3f32 point = lm2_bezier_cubic_v3f32(p0, p1, p2, p3, t);
    length = lm2_add_f32(length, lm2_distance_v3f32(prev_point, point));
    prev_point = point;
  }

  return length;
}

// =============================================================================
// Cubic Bezier Arc Length - 4D (f64)
// =============================================================================

LM2_API double lm2_bezier_cubic_length_v4f64(lm2_v4f64 p0, lm2_v4f64 p1, lm2_v4f64 p2, lm2_v4f64 p3, int segments) {
  double length = 0.0;
  lm2_v4f64 prev_point = p0;

  for (int i = 1; i <= segments; i++) {
    double t = lm2_div_f64((double)i, (double)segments);
    lm2_v4f64 point = lm2_bezier_cubic_v4f64(p0, p1, p2, p3, t);
    length = lm2_add_f64(length, lm2_distance_v4f64(prev_point, point));
    prev_point = point;
  }

  return length;
}

// =============================================================================
// Cubic Bezier Arc Length - 4D (f32)
// =============================================================================

LM2_API float lm2_bezier_cubic_length_v4f32(lm2_v4f32 p0, lm2_v4f32 p1, lm2_v4f32 p2, lm2_v4f32 p3, int segments) {
  float length = 0.0f;
  lm2_v4f32 prev_point = p0;

  for (int i = 1; i <= segments; i++) {
    float t = lm2_div_f32((float)i, (float)segments);
    lm2_v4f32 point = lm2_bezier_cubic_v4f32(p0, p1, p2, p3, t);
    length = lm2_add_f32(length, lm2_distance_v4f32(prev_point, point));
    prev_point = point;
  }

  return length;
}
