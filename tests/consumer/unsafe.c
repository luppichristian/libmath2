#include <lm2.h>

#include <math.h>
#include <stdint.h>

int main(void) {
  // Unsigned wrap is defined by C; the checked build asserts on this input.
  if (lm2_add_u32(UINT32_MAX, 1) != 0) return 1;
  if (lm2_mul_u16(UINT16_MAX, UINT16_MAX) != 1) return 2;
  if (!isnan(lm2_mod_f64(1.0, 0.0))) return 3;

  // Signed-to-unsigned conversion is defined modulo 2^32; the checked
  // vector implementation rejects negative inputs before the conversion.
  lm2_v2_u32 wrapped = lm2_v2_i32_to_u32(lm2_v2_make_i32(-1, 2));
  if (wrapped.x != UINT32_MAX || wrapped.y != 2) return 4;

  lm2_v2_i32 vector = lm2_v2_f64_to_i32(lm2_v2_make_f64(-2.5, 3.5));
  if (vector.x != -2 || vector.y != 3) return 5;
  lm2_r2_f64 input = lm2_r2_from_scalars_f64(1.9, 2.1, 5.7, 6.3);
  lm2_r2_i32 range = lm2_r2_f64_to_i32(input);
  if (range.min.x != 1 || range.min.y != 2 || range.max.x != 5 || range.max.y != 6) return 6;

  lm2_m3x2_f64 matrix = lm2_m3x2_make_f64(2, 0, 4, 0, 4, 8);
  lm2_m3x2_f64 identity = lm2_m3x2_mul_f64(matrix, lm2_m3x2_inverse_f64(matrix));
  if (identity.m00 != 1 || identity.m01 != 0 || identity.m02 != 0 ||
      identity.m10 != 0 || identity.m11 != 1 || identity.m12 != 0) return 7;
  return 0;
}
