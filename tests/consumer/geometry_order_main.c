#include <lm2/geometry2d/lm2_capsule2.h>
#include <lm2/geometry2d/lm2_edge2.h>
#include <lm2/geometry2d/lm2_raycast2.h>
#include <lm2/geometry3d/lm2_capsule3.h>
#include <lm2/geometry3d/lm2_edge3.h>
#include <lm2/geometry3d/lm2_raycast3.h>
#include <lm2/geometry3d/lm2_shape3.h>

int geometry_order_peer(void);

int main(void) {
  lm2_capsule2_f32 a = lm2_capsule2_make_coords_f32(-1.0f, 0.0f, 1.0f, 0.0f, 0.5f);
  lm2_capsule2_f32 b = lm2_capsule2_make_coords_f32(-1.0f, 0.5f, 1.0f, 0.5f, 0.5f);
  lm2_edge2_f32 edge_a = lm2_edge2_make_coords_f32(-1.0f, 0.0f, 1.0f, 0.0f);
  lm2_edge2_f32 edge_b = lm2_edge2_make_coords_f32(-1.0f, 2.0f, 1.0f, 2.0f);
  lm2_ray2_f32 ray = lm2_ray2_make_f32(lm2_v2_make_f32(-3.0f, 0.0f), lm2_v2_make_f32(1.0f, 0.0f), 10.0f);
  lm2_rayhit2_f32 hit = lm2_raycast_capsule2_f32(ray, a);
  return !(lm2_capsule2s_overlap_f32(a, b) && lm2_edge2_to_edge2_distance_sq_f32(edge_a, edge_b) == 4.0f &&
           hit.hit && geometry_order_peer());
}
