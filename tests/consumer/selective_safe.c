#include <lm2/scalar/lm2_safe_ops.h>

#if defined(LM2_VECTORS_LM2_VECTOR2_H_INCLUDED) || defined(LM2_GEOMETRY2D_LM2_AABB2_H_INCLUDED) || defined(LM2_PRIVATE_C2_MAX_POLYGON_VERTS)
#  error "The safe operations module must not load vector or collision modules"
#endif

int main(void) {
  return lm2_add_i32(2, 3) != 5;
}
