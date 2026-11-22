#include <lm2/vectors/lm2_vector2.h>

#if defined(LM2_GEOMETRY2D_LM2_AABB2_H_INCLUDED) || defined(LM2_CAMERA_LM2_CAMERA3_H_INCLUDED) || defined(LM2_PRIVATE_C2_MAX_POLYGON_VERTS)
#  error "The vector2 module must not load camera or collision modules"
#endif

int main(void) {
  lm2_v2_f32 a = lm2_v2_make_f32(1.0f, 2.0f);
  lm2_v2_f32 b = lm2_v2_make_f32(3.0f, 4.0f);
  lm2_v2_f32 sum = lm2_v2_add_f32(a, b);
  return sum.x != 4.0f || sum.y != 6.0f;
}
