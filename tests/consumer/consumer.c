#ifdef LM2_ENABLE_UNPREFIXED_NAMES
#  include <stdlib.h>
#  ifndef min
#    define min(a, b) (-123)
#  endif
#  ifndef max
#    define max(a, b) (-123)
#  endif
#endif

#include <lm2.h>

#ifdef LM2_NO_GENERICS
#  ifdef lm2_add
#    error "LM2_NO_GENERICS must disable the C generic macros"
#  endif
#endif

#ifdef LM2_ENABLE_UNPREFIXED_NAMES
#  ifndef v2_f32
#    error "LM2_ENABLE_UNPREFIXED_NAMES must enable the aliases"
#  endif
#else
#  ifdef v2_f32
#    error "Unprefixed aliases must be opt-in"
#  endif
#endif

int main(void) {
  lm2_v2_f32 a = lm2_v2_make_f32(1.0f, 2.0f);
  lm2_v2_f32 b = lm2_v2_make_f32(3.0f, 4.0f);
#ifndef LM2_NO_GENERICS
  lm2_v2_f32 sum = lm2_v2_add(a, b);
  if (lm2_add(2.0f, 3.0f) != 5.0f || lm2_add((int32_t)7, (int32_t)2) != 9) return 1;
#  define CHECK_EASING(name)                                      \
    if (lm2_ease_##name(0.25f) != lm2_ease_##name##_f32(0.25f) || \
        lm2_ease_##name(0.75) != lm2_ease_##name##_f64(0.75)) return 3;
  CHECK_EASING(linear)
  CHECK_EASING(sin_in)
  CHECK_EASING(sin_out)
  CHECK_EASING(sin_in_out)
  CHECK_EASING(quad_in)
  CHECK_EASING(quad_out)
  CHECK_EASING(quad_in_out)
  CHECK_EASING(cubic_in)
  CHECK_EASING(cubic_out)
  CHECK_EASING(cubic_in_out)
  CHECK_EASING(quart_in)
  CHECK_EASING(quart_out)
  CHECK_EASING(quart_in_out)
  CHECK_EASING(quint_in)
  CHECK_EASING(quint_out)
  CHECK_EASING(quint_in_out)
  CHECK_EASING(exp_in)
  CHECK_EASING(exp_out)
  CHECK_EASING(exp_in_out)
  CHECK_EASING(circ_in)
  CHECK_EASING(circ_out)
  CHECK_EASING(circ_in_out)
  CHECK_EASING(back_in)
  CHECK_EASING(back_out)
  CHECK_EASING(back_in_out)
  CHECK_EASING(elastic_in)
  CHECK_EASING(elastic_out)
  CHECK_EASING(elastic_in_out)
  CHECK_EASING(bounce_in)
  CHECK_EASING(bounce_out)
  CHECK_EASING(bounce_in_out)
#  undef CHECK_EASING
  if (ease_linear(0.25f) != 0.25f) return 6;
#else
  lm2_v2_f32 sum = lm2_v2_add_f32(a, b);
#endif
#ifdef LM2_ENABLE_UNPREFIXED_NAMES
  v2_f32 alias_sum = v2_add_f32(a, b);
  if (alias_sum.x != 4.0f || alias_sum.y != 6.0f) return 2;
#  ifndef LM2_NO_GENERICS
  if (ease_linear(0.25f) != 0.25f || ease_linear(0.75) != 0.75) return 4;
  if (min(2.0f, 3.0f) != 2.0f || max(2.0f, 3.0f) != 3.0f) return 5;
#  endif
#endif
  return sum.x != 4.0f || sum.y != 6.0f;
}
