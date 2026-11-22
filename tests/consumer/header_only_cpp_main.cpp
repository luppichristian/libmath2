#include <lm2/vectors/lm2_vector2.h>
#include <lm2.h>

bool header_only_cpp_peer();

int main() {
  lm2_v2_f32 a = lm2_v2_make_f32(1.0f, 2.0f);
  lm2_v2_f32 b = lm2_v2_make_f32(3.0f, 4.0f);
  lm2_v2_f32 generic_sum = lm2_v2_add(a, b);
  lm2_v2_f32 operator_sum = a + b;
  if (generic_sum.x != 4.0f || operator_sum.y != 6.0f) return 1;
  lm2_circle_f32 circle = lm2_circle_make_coords_f32(0.0f, 0.0f, 1.0f);
  lm2_r2_f32 box = lm2_r2_from_min_max_f32(lm2_v2_make_f32(-0.5f, -0.5f), lm2_v2_make_f32(0.5f, 0.5f));
  return !(lm2_collide_circle_to_aabb_f32(circle, box) && header_only_cpp_peer());
}
