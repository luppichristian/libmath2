---
layout: default
title: Vectors
---

# Vectors

## Overview

2D, 3D, and 4D vector types supporting 10 numeric types each, with a comprehensive set of component-wise arithmetic, rounding, comparison, and interpolation operations.

## Why Use This?

Vectors are the fundamental building block for positions, directions, velocities, colors, and texture coordinates in graphics and game applications.

## Types

Each dimensionality has types for all supported numeric precisions:

### 2D Vectors

| Type | Scalar | Description |
|------|--------|-------------|
| `lm2_v2_f64` | `double` | 64-bit float 2D vector |
| `lm2_v2_f32` | `float` | 32-bit float 2D vector |
| `lm2_v2_i64` | `int64_t` | 64-bit signed int 2D vector |
| `lm2_v2_i32` | `int32_t` | 32-bit signed int 2D vector |
| `lm2_v2_i16` | `int16_t` | 16-bit signed int 2D vector |
| `lm2_v2_i8` | `int8_t` | 8-bit signed int 2D vector |
| `lm2_v2_u64` | `uint64_t` | 64-bit unsigned int 2D vector |
| `lm2_v2_u32` | `uint32_t` | 32-bit unsigned int 2D vector |
| `lm2_v2_u16` | `uint16_t` | 16-bit unsigned int 2D vector |
| `lm2_v2_u8` | `uint8_t` | 8-bit unsigned int 2D vector |
| `lm2_v2` | `float` | Default alias for `lm2_v2_f32` |

### 3D Vectors (`lm2_v3_*`)

Same type variants as 2D with an additional `z` component. Default: `lm2_v3` = `lm2_v3_f32`.

### 4D Vectors (`lm2_v4_*`)

Same type variants with `x`, `y`, `z`, `w` components. Default: `lm2_v4` = `lm2_v4_f32`.

## Component Access

Vectors are defined as unions, allowing multiple access patterns:

```c
lm2_v3_f32 v = lm2_v3_make_f32(1.0f, 2.0f, 3.0f);

// Named fields (spatial)
float x = v.x;
float y = v.y;
float z = v.z;

// Named fields (texture coordinates)
float s = v.s;
float t = v.t;
float r = v.r;  // 3D only

// Array access
float first = v.e[0];

// C++ subscript operator
float second = v[1];  // C++ only
```

## Functions

All functions are shown with `_f32` suffix. Replace with any supported type suffix.

### Construction

#### `lm2_v2_make_f32`

Create a vector from components.

**Signature:** `lm2_v2_f32 lm2_v2_make_f32(float x, float y)`

#### `lm2_v2_splat_f32`

Create a vector with all components set to the same value.

**Signature:** `lm2_v2_f32 lm2_v2_splat_f32(float v)`

#### `lm2_v2_zero_f32`

Create a zero vector.

**Signature:** `lm2_v2_f32 lm2_v2_zero_f32(void)`

### Arithmetic

| Function | Description |
|----------|-------------|
| `lm2_v2_add_f32(a, b)` | Component-wise addition |
| `lm2_v2_sub_f32(a, b)` | Component-wise subtraction |
| `lm2_v2_mul_f32(a, b)` | Component-wise multiplication |
| `lm2_v2_div_f32(a, b)` | Component-wise division |
| `lm2_v2_mod_f32(a, b)` | Component-wise modulo |
| `lm2_v2_neg_f32(a)` | Negate all components |

### Scalar Arithmetic

| Function | Description |
|----------|-------------|
| `lm2_v2_add_s_f32(a, s)` | Add scalar to all components |
| `lm2_v2_sub_s_f32(a, s)` | Subtract scalar from all components |
| `lm2_v2_mul_s_f32(a, s)` | Multiply all components by scalar |
| `lm2_v2_div_s_f32(a, s)` | Divide all components by scalar |

### Rounding (float types only)

| Function | Description |
|----------|-------------|
| `lm2_v2_floor_f32(a)` | Floor each component |
| `lm2_v2_ceil_f32(a)` | Ceil each component |
| `lm2_v2_round_f32(a)` | Round each component |
| `lm2_v2_trunc_f32(a)` | Truncate each component |
| `lm2_v2_floor_multiple_f32(a, b)` | Floor to nearest multiple |
| `lm2_v2_ceil_multiple_f32(a, b)` | Ceil to nearest multiple |
| `lm2_v2_round_multiple_f32(a, b)` | Round to nearest multiple |
| `lm2_v2_trunc_multiple_f32(a, b)` | Truncate to nearest multiple |

### Comparisons

| Function | Description |
|----------|-------------|
| `lm2_v2_min_f32(a, b)` | Component-wise minimum |
| `lm2_v2_max_f32(a, b)` | Component-wise maximum |
| `lm2_v2_min_abs_f32(a, b)` | Component-wise minimum by absolute value |
| `lm2_v2_max_abs_f32(a, b)` | Component-wise maximum by absolute value |
| `lm2_v2_clamp_f32(min, val, max)` | Clamp each component to range |

### Sign and Absolute Value

| Function | Description |
|----------|-------------|
| `lm2_v2_abs_f32(a)` | Absolute value of each component |
| `lm2_v2_sign_f32(a)` | Sign of each component (1 or -1) |
| `lm2_v2_sign0_f32(a)` | Sign of each component (1, -1, or 0) |

### Interpolation (float types only)

| Function | Description |
|----------|-------------|
| `lm2_v2_saturate_f32(a)` | Clamp each component to [0, 1] |
| `lm2_v2_lerp_f32(a, t, b)` | Linear interpolation |
| `lm2_v2_smoothstep_f32(edge0, x, edge1)` | Smooth Hermite interpolation |
| `lm2_v2_alpha_f32(a, val, b)` | Inverse lerp (compute t from value) |

### Math (float types only)

| Function | Description |
|----------|-------------|
| `lm2_v2_fract_f32(a)` | Fractional part of each component |
| `lm2_v2_pow_f32(a, b)` | Component-wise power |
| `lm2_v2_sqrt_f32(a)` | Component-wise square root |

## Example

```c
#include <lm2/vectors/lm2_vector3.h>
#include <lm2/vectors/lm2_vector_specifics.h>

lm2_v3_f32 a = lm2_v3_make_f32(3.0f, 0.0f, 4.0f);
lm2_v3_f32 b = lm2_v3_make_f32(0.0f, 1.0f, 0.0f);

lm2_v3_f32 sum = lm2_v3_add_f32(a, b);       // {3, 1, 4}
lm2_v3_f32 half = lm2_v3_mul_s_f32(a, 0.5f); // {1.5, 0, 2}
float dot = lm2_v3_dot_f32(a, b);             // 0
lm2_v3_f32 unit = lm2_v3_normalize_f32(a);    // {0.6, 0, 0.8}
```
