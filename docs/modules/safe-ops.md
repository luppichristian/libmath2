---
layout: default
title: Safe Ops
---

# Safe Arithmetic Operations

## Overview

Overflow-checked arithmetic operations for all numeric types. Operations assert on overflow, underflow, and division by zero using `LM2_ASSERT`. Can be disabled with `LM2_UNSAFE` for release builds.

## Why Use This?

Integer overflow and division by zero are common sources of bugs. Safe ops catch these at development time while allowing you to disable checks for performance in production.

## Functions

All operations are available for all 10 numeric types.

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

`LM2_UNSAFE` must be defined **when compiling the library** to disable the
checks in its compiled safe arithmetic functions. Defining it only in a
consumer before including the headers does not change an already-built library.
For example, configure a separate CMake build with:

```sh
cmake -S . -B build-unsafe -DLM2_BUILD_TESTS=OFF -DCMAKE_C_FLAGS=-DLM2_UNSAFE
```

With checks disabled, callers must avoid operations with undefined behavior,
including signed overflow and integer division or modulo by zero. Unsigned
arithmetic follows the usual C wrapping rules.

To customize assertions in compiled library functions, provide the definition
while compiling the library itself; a definition in a consumer translation unit
only affects code compiled in that unit:

```c
#define LM2_ASSERT(expr) my_custom_assert(expr)
#include <lm2.h>
```
