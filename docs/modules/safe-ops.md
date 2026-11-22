# Safe Arithmetic Operations

## Overview

Overflow-checked arithmetic operations for all numeric types. Operations assert on overflow, underflow, and division by zero using `LM2_ASSERT`. Can be disabled with `LM2_UNSAFE` for release builds.

## Why Use This?

Integer overflow and division by zero are common sources of bugs. Safe ops catch these at development time while allowing you to disable checks for performance in production.

## Checked behavior

With checks enabled, integer addition, subtraction, and multiplication check the result range. Division and remainder require a nonzero divisor and reject signed minimum divided or reduced by -1; signed negation rejects the minimum. Integer division truncates toward zero and the remainder has the dividend's sign.

Floating addition, subtraction, multiplication, and division require finite operands and results, and reject nonzero subnormal results. A result rounded to zero is accepted, so these checks do not detect every underflow or loss of precision. Floating remainder uses C `fmod` with finite operands and a nonzero divisor; floating negation requires a finite input. These checks use `LM2_ASSERT_UNSAFE`; other library assertions can remain active with `LM2_UNSAFE`.

## Functions

Addition, subtraction, multiplication, division, and remainder are available for all 10 numeric types; negation is limited to floating-point and signed integer types.

### Addition

**Signature:** `float lm2_add_f32(float a, float b)`

Asserts that the result does not overflow or underflow.

### Subtraction

**Signature:** `float lm2_sub_f32(float a, float b)`

Asserts that the result does not overflow or underflow.

### Multiplication

**Signature:** `float lm2_mul_f32(float a, float b)`

Asserts that the result does not overflow or underflow.

### Division

**Signature:** `float lm2_div_f32(float a, float b)`

Asserts that `b` is not zero.

### Modulo

**Signature:** `float lm2_mod_f32(float a, float b)`

Asserts that `b` is not zero.

### Negation (signed types only)

**Signature:** `float lm2_neg_f32(float a)`

Available for `_f64`, `_f32`, `_i64`, `_i32`, `_i16`, `_i8`.

## Configuration

Define `LM2_UNSAFE` before including libmath2 in each translation unit where
you want to disable safe arithmetic checks:

```c
#define LM2_UNSAFE
#include <lm2.h>
```

With checks disabled, callers must avoid operations with undefined behavior,
including signed overflow and integer division or modulo by zero. Unsigned
arithmetic follows the usual C wrapping rules.

To customize assertions, define `LM2_ASSERT` before including libmath2:

```c
#define LM2_ASSERT(expr) my_custom_assert(expr)
#include <lm2.h>
```
