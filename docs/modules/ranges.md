---
layout: default
title: Ranges
---

# Ranges (Axis-Aligned Bounding Boxes)

## Overview

2D, 3D, and 4D range types representing axis-aligned bounding boxes (AABBs) defined by min/max points. Supports all 10 numeric types with arithmetic, containment tests, overlap detection, union, and intersection.

## Why Use This?

AABBs are the most common spatial structure for broad-phase collision detection, frustum culling, spatial partitioning, and UI layout calculations.

## Types

### 2D Ranges

| Type | Scalar | Description |
|------|--------|-------------|
| `lm2_r2_f64` | `double` | 2D range (double) |
| `lm2_r2_f32` | `float` | 2D range (float) |
| `lm2_r2_i64` | `int64_t` | 2D range (int64) |
| `lm2_r2_i32` | `int32_t` | 2D range (int32) |
| `lm2_r2_i16` | `int16_t` | 2D range (int16) |
| `lm2_r2_i8` | `int8_t` | 2D range (int8) |
| `lm2_r2_u64` | `uint64_t` | 2D range (uint64) |
| `lm2_r2_u32` | `uint32_t` | 2D range (uint32) |
| `lm2_r2_u16` | `uint16_t` | 2D range (uint16) |
| `lm2_r2_u8` | `uint8_t` | 2D range (uint8) |
| `lm2_r2` | `float` | Default alias for `lm2_r2_f32` |

3D ranges (`lm2_r3_*`) and 4D ranges (`lm2_r4_*`) follow the same pattern.

## Structure

```c
typedef union lm2_r2_f32 {
    lm2_v2_f32 e[2];
    float e2[4];
    struct { lm2_v2_f32 min; lm2_v2_f32 max; };
} lm2_r2_f32;
```

## Functions

### Construction

| Function | Description |
|----------|-------------|
| `lm2_r2_from_min_max_f32(min, max)` | From min/max points |
| `lm2_r2_from_center_extents_f32(center, extents)` | From center and half-extents |
| `lm2_r2_from_center_size_f32(center, size)` | From center and full size |
| `lm2_r2_from_position_size_f32(position, size)` | From top-left position and size |
| `lm2_r2_from_scalars_f32(min_x, min_y, max_x, max_y)` | From individual scalars |
| `lm2_r2_zero_f32()` | Zero range |

### Arithmetic

| Function | Description |
|----------|-------------|
| `lm2_r2_add_f32(a, b)` | Add two ranges |
| `lm2_r2_add_s_f32(r, s)` | Add scalar to both min and max |
| `lm2_r2_add_v_f32(r, v)` | Translate range by vector |
| `lm2_r2_sub_f32(a, b)` | Subtract ranges |
| `lm2_r2_sub_s_f32(r, s)` | Subtract scalar |
| `lm2_r2_sub_v_f32(r, v)` | Reverse-translate |
| `lm2_r2_mul_f32(a, b)` | Multiply ranges |
| `lm2_r2_mul_s_f32(r, s)` | Scale range by scalar |
| `lm2_r2_mul_v_f32(r, v)` | Scale range by vector |
| `lm2_r2_div_f32(a, b)` / `_s` / `_v` | Division variants |
| `lm2_r2_mod_f32(a, b)` / `_s` / `_v` | Modulo variants |

### Properties

| Function | Description |
|----------|-------------|
| `lm2_r2_size_f32(r)` | Full size (max - min) |
| `lm2_r2_extents_f32(r)` | Half-extents (size / 2) |
| `lm2_r2_center_f32(r)` | Center point |
| `lm2_r2_area_f32(r)` | Area (size.x * size.y) |

All property functions available for all 10 numeric type suffixes.

### Tests

| Function | Returns | Description |
|----------|---------|-------------|
| `lm2_r2_contains_point_f32(r, point)` | `int` | True if point is inside range |
| `lm2_r2_overlaps_f32(a, b)` | `int` | True if two ranges overlap |

Both test functions are available for all 10 numeric type suffixes.

### Set Operations

| Function | Description |
|----------|-------------|
| `lm2_r2_union_f32(a, b)` | Smallest range containing both |
| `lm2_r2_intersection_f32(a, b)` | Overlap region of both ranges |

### Rounding, Comparison, Interpolation

Ranges support the same rounding (`floor`, `ceil`, `round`, `trunc`), comparison (`min`, `max`, `clamp`), sign (`abs`, `sign`, `sign0`), and interpolation (`saturate`, `lerp`, `smoothstep`, `alpha`, `fract`, `pow`, `sqrt`) operations as vectors, applied component-wise.

## Example

```c
lm2_r2_f32 a = lm2_r2_from_center_size_f32(
    lm2_v2_make_f32(5, 5),
    lm2_v2_make_f32(10, 10)
);
lm2_r2_f32 b = lm2_r2_from_min_max_f32(
    lm2_v2_make_f32(8, 8),
    lm2_v2_make_f32(15, 15)
);

int overlap = lm2_r2_overlaps_f32(a, b);           // 1 (true)
lm2_r2_f32 merged = lm2_r2_union_f32(a, b);        // {0,0} to {15,15}
lm2_v2_f32 center = lm2_r2_center_f32(merged);     // {7.5, 7.5}
```
