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

3D ranges (`lm2_r3_*`) and 4D ranges (`lm2_r4_*`) follow the same pattern.
All coordinates use the caller’s chosen space. `min` and `max` should be
ordered per axis; constructors and arithmetic do not automatically sort them.

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
| `lm2_r2_from_position_size_f32(position, size)` | From minimum corner and size |
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

The 3D and 4D counterparts expose `volume` and `hypervolume`, respectively.
Properties are available for all 10 numeric suffixes. Center is computed as
`(min + max) / 2` and extents as `(max - min) / 2`; intermediate arithmetic
must be representable. Integer division truncates toward zero. In
`from_center_size`, integer size components are halved first, so a nonnegative
odd size produces a range one unit smaller along that axis. For example, center
5 and size 3 produce [4, 6]. The area, volume and hypervolume functions use
native multiplication for the size components, without safe-operation overflow
checks. The caller must ensure the product is representable.

### Tests

| Function | Returns | Description |
|----------|---------|-------------|
| `lm2_r2_contains_point_f32(r, point)` | `int` | True if point is inside range |
| `lm2_r2_overlaps_f32(a, b)` | `int` | True if two ranges overlap |

Both tests include boundaries and are available for all numeric suffixes.
Touching faces, edges, or corners therefore count as overlap.

### Set Operations

| Function | Description |
|----------|-------------|
| `lm2_r2_union_f32(a, b)` | Smallest range containing both |
| `lm2_r2_intersection_f32(a, b)` | Componentwise `max(a.min,b.min)` to `min(a.max,b.max)` |
| `lm2_r2_scale_from_center_s_f32(r, scale)` | Scale extents uniformly from center by scalar (all ranges use `_s` suffix) |

Intersection does not return an empty flag or reorder bounds. For disjoint
ranges, at least one resulting min exceeds max; call `overlaps` first if an
ordered intersection is required. Arithmetic operates on corresponding min and
max components, not on sets of points. In particular, multiplying by a negative
value can reverse bounds. `scale_from_center_s` and `_v` scale extents about the
computed center and can likewise reverse bounds with negative factors; integer
center and extents rounding can change the range even at scale 1.

In 3D and 4D, `norm` swaps min and max independently on inverted axes.
`expand(r, amount)` subtracts amount from each min coordinate and adds it to
each max coordinate; a negative amount shrinks the range and can invert it.

### Component-wise functions

Rounding, comparisons, sign, interpolation and other scalar functions are
applied separately to the min and max vectors. They inherit the vector scalar
preconditions and do not preserve ordered bounds in general. `clamp(value,
min, max)` takes the value first. `smoothstep(edge0, edge1, x)` and `alpha(a,
b, value)` take endpoints before the value. Lerp has a dimension-specific
argument order: `lm2_r2_lerp(a, b, t)` but `lm2_r3_lerp(a, t, b)` and
`lm2_r4_lerp(a, t, b)`. Each computes `a + t * (b - a)` componentwise without
clamping `t`. See [Vectors](vectors.md) for scalar function behavior and
preconditions.

`lm2_range_conversions.h` converts the two bounds independently with the vector
conversion rules. Float-to-integer conversion truncates toward zero; conversions
are not geometric floor/ceil expansion and can lose coverage. Dimensional
upcasts append caller-supplied min/max coordinates; downcasts drop the last
axis. Neither applies a coordinate transform.

### Declared overloads without definitions

The current library does not define the unsigned `mod`, `mod_s`, or `mod_v`
overloads for any range dimension, even though they are declared. The `r2`
unsigned `abs_u64` and `abs_u32` declarations also lack definitions. For `r3`
and `r4`, unsigned `abs` and integer `floor`, `ceil`, `round`, `trunc`, their
`_multiple` variants, and `lerp` are declared but not defined. Calling these
symbols causes a link failure. Use supported overloads or apply the equivalent
operation to the bounds explicitly.

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
