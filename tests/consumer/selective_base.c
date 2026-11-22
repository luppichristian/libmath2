#include <lm2/lm2_base.h>

#if defined(LM2_SCALAR_LM2_SAFE_OPS_H_INCLUDED) || defined(LM2_VECTORS_LM2_VECTOR2_H_INCLUDED) || defined(LM2_PRIVATE_C2_MAX_POLYGON_VERTS)
#  error "The base header must not load math or collision modules"
#endif

int main(void) {
  return 0;
}
