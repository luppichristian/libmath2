// Consumers may also compile their own copy of cute_c2. Its symbols must not
// conflict with, or replace, the private header-only collision backend in libmath2.
#define CUTE_C2_IMPLEMENTATION
#define c2CircletoAABB application_c2CircletoAABB
#include <cute_c2.h>
#undef c2CircletoAABB

#include <lm2/geometry2d/lm2_manifold2.h>

// If libmath2 accidentally calls the consumer's symbol, this stub turns
// the overlapping libmath2 query into a miss.
int c2CircletoAABB(c2Circle circle, c2AABB box) {
  (void)circle;
  (void)box;
  return 0;
}

int main(void) {
  lm2_circle_f32 circle = lm2_circle_make_coords_f32(0.0f, 0.0f, 1.0f);
  lm2_r2_f32 box = lm2_r2_from_min_max_f32(lm2_v2_make_f32(-0.5f, -0.5f), lm2_v2_make_f32(0.5f, 0.5f));
  return !lm2_collide_circle_to_aabb_f32(circle, box);
}
