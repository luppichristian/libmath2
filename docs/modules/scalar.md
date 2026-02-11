---
layout: default
title: Scalar Math
---

# Scalar Math

## Overview

Scalar math functions for floating-point and integer types: rounding, clamping, interpolation, sign, absolute value, power, and square root.

## Why Use This?

These provide a consistent, type-safe API for common math operations across all supported numeric types, matching the same naming conventions as the vector operations.

## Functions

All functions shown with `_f32`. Replace with `_f64`, `_i64`, `_i32`, `_i16`, `_i8`, `_u64`, `_u32`, `_u16`, `_u8` as needed. Integer types do not have rounding, interpolation, fract, pow, or sqrt variants.

### Rounding (float types only)

| Function | Description |
|----------|-------------|
| `lm2_floor_f32(a)` | Floor |
| `lm2_ceil_f32(a)` | Ceil |
| `lm2_round_f32(a)` | Round to nearest |
| `lm2_trunc_f32(a)` | Truncate toward zero |
| `lm2_floor_multiple_f32(a, multiple)` | Floor to nearest multiple |
| `lm2_ceil_multiple_f32(a, multiple)` | Ceil to nearest multiple |
| `lm2_round_multiple_f32(a, multiple)` | Round to nearest multiple |
| `lm2_trunc_multiple_f32(a, multiple)` | Truncate to nearest multiple |

### Sign and Absolute Value

| Function | Types | Description |
|----------|-------|-------------|
| `lm2_abs_f32(a)` | f64, f32, i64-i8 | Absolute value |
| `lm2_sign_f32(a)` | f64, f32, i64-i8 | Returns 1 or -1 |
| `lm2_sign0_f32(a)` | f64, f32, i64-i8 | Returns 1, -1, or 0 |

### Comparison

| Function | Types | Description |
|----------|-------|-------------|
| `lm2_min_f32(a, b)` | all 10 | Minimum of two values |
| `lm2_max_f32(a, b)` | all 10 | Maximum of two values |
| `lm2_min_abs_f32(a, b)` | f64, f32, i64-i8 | Minimum by absolute value |
| `lm2_max_abs_f32(a, b)` | f64, f32, i64-i8 | Maximum by absolute value |
| `lm2_clamp_f32(min, value, max)` | all 10 | Clamp value to [min, max] |

### Interpolation (float types only)

| Function | Description |
|----------|-------------|
| `lm2_saturate_f32(value)` | Clamp to [0, 1] |
| `lm2_lerp_f32(a, t, b)` | Linear interpolation: a + t*(b-a) |
| `lm2_smoothstep_f32(edge0, x, edge1)` | Smooth Hermite interpolation |
| `lm2_alpha_f32(a, value, b)` | Inverse lerp: compute t from value |

### Math (float types only)

| Function | Description |
|----------|-------------|
| `lm2_fract_f32(a)` | Fractional part |
| `lm2_pow_f32(base, exponent)` | Power |
| `lm2_sqrt_f32(a)` | Square root |

## Example

```c
float val = 7.3f;

float clamped = lm2_clamp_f32(0.0f, val, 10.0f);     // 7.3
float rounded = lm2_round_multiple_f32(val, 2.5f);     // 7.5
float t = lm2_alpha_f32(0.0f, val, 10.0f);             // 0.73
float interp = lm2_lerp_f32(0.0f, 0.5f, 100.0f);      // 50.0
```
