---
layout: default
title: Matrices
---

# Matrices

## Overview

3x2, 3x3, and 4x4 matrix types for 2D and 3D transformations. Matrices are stored in row-major order and support construction, multiplication, inversion, and transformation of points and vectors.

## Why Use This?

Matrices are essential for combining translation, rotation, and scaling transformations, building camera view matrices, and creating projection matrices for rendering.

## Types

| Type | Scalar | Description |
|------|--------|-------------|
| `lm2_m3x2_f64` | `double` | 3x2 affine 2D transformation matrix |
| `lm2_m3x2_f32` | `float` | 3x2 affine 2D transformation matrix |
| `lm2_m3x2` | `float` | Default alias for `lm2_m3x2_f32` |
| `lm2_m3x3_f64` | `double` | 3x3 matrix (2D homogeneous / 3D rotation) |
| `lm2_m3x3_f32` | `float` | 3x3 matrix |
| `lm2_m3x3` | `float` | Default alias for `lm2_m3x3_f32` |
| `lm2_m4x4_f64` | `double` | 4x4 3D transformation matrix |
| `lm2_m4x4_f32` | `float` | 4x4 3D transformation matrix |
| `lm2_m4x4` | `float` | Default alias for `lm2_m4x4_f32` |

## Matrix 3x2 Layout

Row-major, 6 elements representing a 2D affine transform:

```
[m00 m01 m02]   [a  c  tx]
[m10 m11 m12] = [b  d  ty]
[  0   0   1]   (implicit third row, never stored)
```

Access via named fields (`m.m00`, `m.tx`, `m.a`, ...) or flat array (`m.e[0]` through `m.e[5]`).

## Functions (3x2)

All functions shown with `_f32` suffix. Also available with `_f64`.

### Construction

| Function | Description |
|----------|-------------|
| `lm2_m3x2_identity_f32()` | Identity matrix |
| `lm2_m3x2_zero_f32()` | Zero matrix |
| `lm2_m3x2_make_f32(m00..m12)` | Construct from 6 values |

### Transformation Builders

| Function | Description |
|----------|-------------|
| `lm2_m3x2_scale_f32(scale)` | Scale by v2 |
| `lm2_m3x2_scale_uniform_f32(s)` | Uniform scale |
| `lm2_m3x2_translate_f32(translation)` | Translation matrix |
| `lm2_m3x2_rotate_f32(angle)` | Rotation by angle (radians) |
| `lm2_m3x2_rotate_around_pivot_f32(angle, pivot)` | Rotation around a pivot point |
| `lm2_m3x2_scale_translate_f32(scale, translation)` | Combined scale + translate |
| `lm2_m3x2_world_transform_f32(translation, scale, rotation)` | Full TRS 2D world transform |

### Operations

| Function | Description |
|----------|-------------|
| `lm2_m3x2_multiply_f32(a, b)` | Matrix multiplication (applies b first, then a) |
| `lm2_m3x2_inverse_f32(m)` | Inverse |
| `lm2_m3x2_determinant_f32(m)` | Determinant |

### Transforming Points and Vectors

| Function | Description |
|----------|-------------|
| `lm2_m3x2_transform_point_f32(m, v)` | Transform 2D point (applies translation) |
| `lm2_m3x2_transform_vector_f32(m, v)` | Transform 2D direction (ignores translation) |
| `lm2_m3x2_transform_points_f32(m, points, count)` | Transform array of points in-place |
| `lm2_m3x2_transform_points_src_dst_f32(m, src, dst, count)` | Transform array of points (separate output) |

### Extraction

| Function | Description |
|----------|-------------|
| `lm2_m3x2_get_rotation_f32(m)` | Extract rotation angle from matrix |
| `lm2_m3x2_get_scale_f32(m)` | Extract scale from matrix |
| `lm2_m3x2_get_translation_f32(m)` | Extract translation from matrix |

### Projection

| Function | Description |
|----------|-------------|
| `lm2_m3x2_ortho_f32(left, right, bottom, top)` | 2D orthographic projection |

---

## Matrix 3x3 Layout

Row-major, 9 elements:

```
[m00 m01 m02]
[m10 m11 m12]
[m20 m21 m22]
```

Access via named fields (`m.m00`, ...) or flat array (`m.e[0]` through `m.e[8]`).

Used for 2D homogeneous transformations (with implicit bottom row `[0 0 1]`) or 3D rotation matrices.

## Functions (3x3)

All functions shown with `_f32` suffix. Also available with `_f64`.

### Construction

| Function | Description |
|----------|-------------|
| `lm2_m3x3_identity_f32()` | Identity matrix |
| `lm2_m3x3_zero_f32()` | Zero matrix |
| `lm2_m3x3_make_f32(m00..m22)` | Construct from 9 values |

### Transformation Builders

| Function | Description |
|----------|-------------|
| `lm2_m3x3_scale_f32(scale)` | Scale by v2 |
| `lm2_m3x3_scale_uniform_f32(s)` | Uniform scale |
| `lm2_m3x3_translate_f32(translation)` | Translation matrix (2D homogeneous) |
| `lm2_m3x3_rotate_f32(angle)` | Rotation by angle (radians) |
| `lm2_m3x3_rotate_around_pivot_f32(angle, pivot)` | Rotation around a pivot point |
| `lm2_m3x3_scale_translate_f32(scale, translation)` | Combined scale + translate |

### Operations

| Function | Description |
|----------|-------------|
| `lm2_m3x3_multiply_f32(a, b)` | Matrix multiplication |
| `lm2_m3x3_transpose_f32(m)` | Transpose |
| `lm2_m3x3_inverse_f32(m)` | Inverse |
| `lm2_m3x3_determinant_f32(m)` | Determinant |
| `lm2_m3x3_trace_f32(m)` | Trace (sum of diagonal) |

### Transforming Points and Vectors

| Function | Description |
|----------|-------------|
| `lm2_m3x3_transform_point_f32(m, v)` | Transform 2D point (applies translation) |
| `lm2_m3x3_transform_vector_f32(m, v)` | Transform 2D direction (ignores translation) |
| `lm2_m3x3_transform_f32(m, v)` | Transform full 3D vector |
| `lm2_m3x3_transform_points_f32(m, points, count)` | Transform array of 2D points in-place |
| `lm2_m3x3_transform_points_src_dst_f32(m, src, dst, count)` | Transform array of 2D points (separate output) |

### Extraction

| Function | Description |
|----------|-------------|
| `lm2_m3x3_get_rotation_f32(m)` | Extract rotation angle from matrix |
| `lm2_m3x3_get_scale_f32(m)` | Extract scale from matrix |
| `lm2_m3x3_get_translation_f32(m)` | Extract translation from matrix |

---

```
[m00 m01 m02 m03]
[m10 m11 m12 m13]
[m20 m21 m22 m23]
[m30 m31 m32 m33]
```

Access via named fields (`m.m00`, `m.m01`, ...) or flat array (`m.e[0]` through `m.e[15]`).

## Functions (4x4)

### Construction

| Function | Description |
|----------|-------------|
| `lm2_m4x4_identity_f32()` | Identity matrix |
| `lm2_m4x4_zero_f32()` | Zero matrix |
| `lm2_m4x4_make_f32(m00..m33)` | Construct from 16 values |

### Transformation Builders

| Function | Description |
|----------|-------------|
| `lm2_m4x4_scale_f32(scale)` | Scale by v3 (non-uniform) |
| `lm2_m4x4_scale_uniform_f32(s)` | Uniform scale |
| `lm2_m4x4_translate_f32(translation)` | Translation matrix |
| `lm2_m4x4_rotate_x_f32(angle)` | Rotation around X axis |
| `lm2_m4x4_rotate_y_f32(angle)` | Rotation around Y axis |
| `lm2_m4x4_rotate_z_f32(angle)` | Rotation around Z axis |
| `lm2_m4x4_rotate_axis_f32(axis, angle)` | Rotation around arbitrary axis |
| `lm2_m4x4_scale_translate_f32(scale, translation)` | Combined scale + translate |
| `lm2_m4x4_world_transform_f32(translation, scale, euler)` | Full TRS world transform |

### Operations

| Function | Description |
|----------|-------------|
| `lm2_m4x4_multiply_f32(a, b)` | Matrix multiplication |
| `lm2_m4x4_transpose_f32(m)` | Transpose |
| `lm2_m4x4_inverse_f32(m)` | Inverse |
| `lm2_m4x4_determinant_f32(m)` | Determinant |
| `lm2_m4x4_trace_f32(m)` | Trace (sum of diagonal) |

### Transforming Points and Vectors

| Function | Description |
|----------|-------------|
| `lm2_m4x4_transform_point_f32(m, v)` | Transform 3D point (applies translation) |
| `lm2_m4x4_transform_vector_f32(m, v)` | Transform 3D direction (ignores translation) |
| `lm2_m4x4_transform_f32(m, v)` | Transform 4D vector |
| `lm2_m4x4_transform_points_f32(m, points, count)` | Transform array of points in-place |
| `lm2_m4x4_transform_points_src_dst_f32(m, src, dst, count)` | Transform array of points (separate output) |

### Extraction

| Function | Description |
|----------|-------------|
| `lm2_m4x4_get_scale_f32(m)` | Extract scale from matrix |
| `lm2_m4x4_get_translation_f32(m)` | Extract translation from matrix |

### Camera and Projection

#### `lm2_m4x4_look_at_f32`

Build a view matrix from eye position, target, and up vector.

**Signature:** `lm2_m4x4_f32 lm2_m4x4_look_at_f32(lm2_v3_f32 eye, lm2_v3_f32 target, lm2_v3_f32 up)`

#### `lm2_m4x4_perspective_f32`

Build a perspective projection matrix.

**Signature:** `lm2_m4x4_f32 lm2_m4x4_perspective_f32(float fov_y, float aspect, float near_plane, float far_plane)`

**Parameters:**
- `fov_y` — Vertical field of view in radians
- `aspect` — Width / height ratio
- `near_plane` — Near clipping distance
- `far_plane` — Far clipping distance

#### `lm2_m4x4_ortho_f32`

Build an orthographic projection matrix.

**Signature:** `lm2_m4x4_f32 lm2_m4x4_ortho_f32(float left, float right, float bottom, float top, float near_plane, float far_plane)`

### Quaternion Conversions

| Function | Description |
|----------|-------------|
| `lm2_m4x4_from_quat_f32(q)` | Convert quaternion to 4x4 rotation matrix |
| `lm2_m4x4_to_quat_f32(m)` | Extract quaternion from rotation matrix |

## Example

```c
// Build model-view-projection matrix
lm2_m4x4_f32 model = lm2_m4x4_world_transform_f32(
    lm2_v3_make_f32(0, 0, -5),     // position
    lm2_v3_splat_f32(1.0f),         // scale
    lm2_v3_make_f32(0, 0.5f, 0)    // rotation (euler)
);

lm2_m4x4_f32 view = lm2_m4x4_look_at_f32(
    lm2_v3_make_f32(0, 3, 8),
    lm2_v3_zero_f32(),
    lm2_v3_make_f32(0, 1, 0)
);

lm2_m4x4_f32 proj = lm2_m4x4_perspective_f32(1.047f, 16.0f/9.0f, 0.1f, 100.0f);

lm2_m4x4_f32 mvp = lm2_m4x4_multiply_f32(
    lm2_m4x4_multiply_f32(proj, view), model
);
```
