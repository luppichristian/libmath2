// Minimal test to reproduce "too few arguments" error
#include "lm2/extensions/lm2_cpp_operators.h"

int main() {
  lm2_v2_f64 a = {1.0, 2.0};
  lm2_v2_f64 b = a + a;  // Uses operator+
  lm2_v2_f64 c = -a;     // Uses operator-
  return 0;
}
