#include <lm2/geometry3d/lm2_edge3.h>

#ifdef LM2_GEOMETRY3D_LM2_RAYCAST3_H_INCLUDED
#  error "The edge3 module must not load raycast3"
#endif

int main(void) {
  lm2_edge3_f32 edge = lm2_edge3_make_coords_f32(0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 2.0f);
  return lm2_edge3_length_sq_f32(edge) != 9.0f;
}
