---
layout: default
title: Vector Specifics
---

# Vector Specifics

## Overview

Higher-level vector operations including dot product, cross product, length, distance, normalization, angle computation, rotation, reflection, and projection. These operate on floating-point vector types.

## Why Use This?

These are the essential geometric operations needed for lighting calculations, physics, camera systems, collision detection, and spatial queries.

## Functions

### Dot Product

Returns the scalar dot product of two vectors.

| Function | Description |
|----------|-------------|
| `lm2_v2_dot_f32(a, b)` | 2D dot product (float) |
| `lm2_v3_dot_f32(a, b)` | 3D dot product (float) |
| `lm2_v4_dot_f32(a, b)` | 4D dot product (float) |

Also available for `_f64` and integer types (`_i64`, `_i32`, `_i16`, `_i8`).

### Cross Product

#### 3D Cross Product

Returns the cross product vector, perpendicular to both inputs.

**Signature:** `lm2_v3_f32 lm2_v3_cross_f32(lm2_v3_f32 a, lm2_v3_f32 b)`

Also available for `_f64` and integer types (`_i64`, `_i32`, `_i16`, `_i8`).

#### 2D Cross Product

Returns the scalar z-component of the cross product (a.x * b.y - a.y * b.x).

**Signature:** `float lm2_v2_cross_f32(lm2_v2_f32 a, lm2_v2_f32 b)`

Also available for `_f64` and integer types (`_i64`, `_i32`, `_i16`, `_i8`).

#### 2D Cross Product (3-point)

Returns the cross product of vectors (b-a) and (c-a). Useful for turn detection:
- `> 0`: Left turn (counterclockwise)
- `< 0`: Right turn (clockwise)
- `= 0`: Collinear

**Signature:** `float lm2_v2_cross3_f32(lm2_v2_f32 a, lm2_v2_f32 b, lm2_v2_f32 c)`

Also available for `_f64` and integer types (`_i64`, `_i32`, `_i16`, `_i8`).

### Length / Magnitude

| Function | Description |
|----------|-------------|
| `lm2_v2_length_f32(v)` | 2D vector length |
| `lm2_v3_length_f32(v)` | 3D vector length |
| `lm2_v4_length_f32(v)` | 4D vector length |
| `lm2_v2_length_sq_f32(v)` | 2D squared length (no sqrt, faster) |
| `lm2_v3_length_sq_f32(v)` | 3D squared length |
| `lm2_v4_length_sq_f32(v)` | 4D squared length |

### Distance

| Function | Description |
|----------|-------------|
| `lm2_v2_distance_f32(a, b)` | 2D distance between points |
| `lm2_v3_distance_f32(a, b)` | 3D distance between points |
| `lm2_v4_distance_f32(a, b)` | 4D distance between points |
| `lm2_v2_distance_sq_f32(a, b)` | 2D squared distance (no sqrt, faster) |
| `lm2_v3_distance_sq_f32(a, b)` | 3D squared distance |
| `lm2_v4_distance_sq_f32(a, b)` | 4D squared distance |

### Normalize

Returns a unit vector in the same direction.

| Function | Description |
|----------|-------------|
| `lm2_v2_normalize_f32(v)` | Normalize 2D vector |
| `lm2_v3_normalize_f32(v)` | Normalize 3D vector |
| `lm2_v4_normalize_f32(v)` | Normalize 4D vector |

### Angle

Returns the angle between two vectors in radians.

| Function | Description |
|----------|-------------|
| `lm2_v2_angle_f32(a, b)` | Angle between 2D vectors |
| `lm2_v3_angle_f32(a, b)` | Angle between 3D vectors |

### 2D Rotation

#### `lm2_v2_rotate_f32`

Rotate a 2D vector by an angle (radians).

**Signature:** `lm2_v2_f32 lm2_v2_rotate_f32(lm2_v2_f32 v, float angle)`

#### `lm2_v2_rotate_around_f32`

Rotate a 2D vector around a pivot point by an angle (radians).

**Signature:** `lm2_v2_f32 lm2_v2_rotate_around_f32(lm2_v2_f32 v, lm2_v2_f32 point, float angle)`

### Perpendicular Vectors (2D)

| Function | Description |
|----------|-------------|
| `lm2_v2_perp_ccw_f32(v)` | 90-degree counter-clockwise rotation |
| `lm2_v2_perp_cw_f32(v)` | 90-degree clockwise rotation |

Available for all signed types.

### Reflection

Reflect a vector across a normal.

| Function | Description |
|----------|-------------|
| `lm2_v2_reflect_f32(v, normal)` | 2D reflection |
| `lm2_v3_reflect_f32(v, normal)` | 3D reflection |

### Projection

Project vector `a` onto vector `b`.

| Function | Description |
|----------|-------------|
| `lm2_v2_project_f32(a, b)` | 2D projection |
| `lm2_v3_project_f32(a, b)` | 3D projection |

## Conversions

See also the vector conversion functions in `lm2_vector_conversions.h`:

- **Type conversions**: `lm2_v2_f32_to_i32(v)`, `lm2_v3_f64_to_f32(v)`, etc.
- **Upcast**: `lm2_v2_upcast_f32(v, z)` — v2 to v3 by adding z component
- **Downcast**: `lm2_v3_downcast_f32(v)` — v3 to v2 by dropping z component

## Example

```c
lm2_v3_f32 forward = lm2_v3_make_f32(0, 0, -1);
lm2_v3_f32 normal  = lm2_v3_make_f32(0, 1, 0);

// Reflect off a surface
lm2_v3_f32 bounce = lm2_v3_reflect_f32(forward, normal);

// Project onto a plane normal
lm2_v3_f32 projected = lm2_v3_project_f32(forward, normal);

// Angle between vectors
float angle = lm2_v3_angle_f32(forward, normal); // ~1.5708 (PI/2)
```
