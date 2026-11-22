#include <lm2/geometry2d/lm2_manifold2.h>

int header_only_c_peer(void) {
  lm2_circle_f32 a = lm2_circle_make_coords_f32(0.0f, 0.0f, 1.0f);
  lm2_circle_f32 b = lm2_circle_make_coords_f32(1.0f, 0.0f, 1.0f);
  lm2_manifold_f32 manifold;
  lm2_manifold_circle_to_circle_f32(a, b, &manifold);
  return lm2_collide_circle_to_circle_f32(a, b) && manifold.count > 0;
}
