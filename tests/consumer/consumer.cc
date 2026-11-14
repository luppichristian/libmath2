#include <lm2.h>

#include <concepts>

template <typename T>
concept has_addition = requires(T a, T b) { a + b; };

template <typename T>
concept has_generic_addition = requires(T a, T b) { lm2_v2_add(a, b); };

// These expectations come from the test configuration, independently of the
// library flags, so accidentally disabling both features fails the test.
#ifdef LM2_TEST_EXPECT_NO_GENERICS
static_assert(!has_generic_addition<lm2_v2_f32>);
static_assert(has_addition<lm2_v2_f32>);
#endif
#ifdef LM2_TEST_EXPECT_NO_OPERATORS
static_assert(has_generic_addition<lm2_v2_f32>);
static_assert(!has_addition<lm2_v2_f32>);
#endif

#ifdef LM2_NO_GENERICS
static_assert(!has_generic_addition<lm2_v2_f32>);
#else
static_assert(has_generic_addition<lm2_v2_f32>);
#endif

#ifdef LM2_NO_CPP_OPERATORS
static_assert(!has_addition<lm2_v2_f32>);
#else
static_assert(has_addition<lm2_v2_f32>);
#endif

int main() {
  const lm2_v2_f32 a = lm2_v2_make_f32(1.0f, 2.0f);
  const lm2_v2_f32 b = lm2_v2_make_f32(3.0f, 4.0f);
#ifndef LM2_NO_GENERICS
  const auto generic_sum = lm2_v2_add(a, b);
  if (lm2_add(2.0f, 3.0f) != 5.0f || generic_sum.x != 4.0f || generic_sum.y != 6.0f) return 1;
#endif
#ifndef LM2_NO_CPP_OPERATORS
  const auto sum = a + b;
#else
  const auto sum = lm2_v2_add_f32(a, b);
#endif
#ifdef LM2_ENABLE_UNPREFIXED_NAMES
  const v2_f32 alias_sum = v2_add_f32(a, b);
  if (alias_sum.x != 4.0f || alias_sum.y != 6.0f) return 2;
#endif
  return sum.x != 4.0f || sum.y != 6.0f;
}
