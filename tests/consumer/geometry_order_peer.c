#include <lm2/geometry3d/lm2_shape3.h>
#include <lm2/geometry3d/lm2_raycast3.h>
#include <lm2/geometry3d/lm2_edge3.h>
#include <lm2/geometry3d/lm2_capsule3.h>
#include <lm2/geometry2d/lm2_raycast2.h>
#include <lm2/geometry2d/lm2_edge2.h>
#include <lm2/geometry2d/lm2_capsule2.h>

int geometry_order_peer(void) {
  lm2_capsule3_f32 a = lm2_capsule3_make_coords_f32(-1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f);
  lm2_capsule3_f32 b = lm2_capsule3_make_coords_f32(-1.0f, 0.5f, 0.0f, 1.0f, 0.5f, 0.0f, 0.5f);
  lm2_ray3_f32 ray = lm2_ray3_make_f32(lm2_v3_make_f32(-3.0f, 0.0f, 0.0f), lm2_v3_make_f32(1.0f, 0.0f, 0.0f), 10.0f);
  lm2_shape3_f32 shape = lm2_shape3_from_capsule_f32(&a);
  lm2_rayhit3_f32 hit = lm2_raycast_shape3_f32(ray, shape);
  return lm2_capsules3_overlap_f32(a, b) && lm2_shape3_as_capsule_f32(&shape) == &a && hit.hit;
}
