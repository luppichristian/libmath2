#include <lm2/geometry2d/lm2_raycast2.h>

bool header_only_cpp_peer() {
  lm2_circle_f32 circle = lm2_circle_make_coords_f32(0.0f, 0.0f, 1.0f);
  lm2_ray2_f32 ray = lm2_ray2_make_f32(lm2_v2_make_f32(-2.0f, 0.0f), lm2_v2_make_f32(1.0f, 0.0f), 10.0f);
  lm2_rayhit2_f32 hit = lm2_raycast_circle_f32(ray, circle);
  return hit.hit;
}
