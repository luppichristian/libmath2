#include <lm2/geometry2d/lm2_circle.h>

#if defined(LM2_CAMERA_LM2_CAMERA3_H_INCLUDED) || defined(LM2_GEOMETRY2D_LM2_RAYCAST2_H_INCLUDED) || defined(LM2_PRIVATE_C2_MAX_POLYGON_VERTS)
#  error "The circle module must not load camera or collision modules"
#endif

int main(void) {
  lm2_circle_f32 circle = lm2_circle_make_coords_f32(1.0f, 2.0f, 3.0f);
  return circle.center.x != 1.0f || circle.center.y != 2.0f || circle.radius != 3.0f;
}
