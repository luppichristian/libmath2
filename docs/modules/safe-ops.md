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

Define `LM2_UNSAFE` before including headers to disable all overflow/underflow assertions for maximum performance:

```c
#define LM2_UNSAFE
#include <lm2.h>
```

Override the assertion macro:

```c
#define LM2_ASSERT(expr) my_custom_assert(expr)
#include <lm2.h>
```
