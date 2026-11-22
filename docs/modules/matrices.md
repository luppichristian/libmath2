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
| `lm2_m3x3_f64` | `double` | 3x3 matrix (2D homogeneous / 3D rotation) |
| `lm2_m3x3_f32` | `float` | 3x3 matrix |
| `lm2_m4x4_f64` | `double` | 4x4 3D transformation matrix |
| `lm2_m4x4_f32` | `float` | 4x4 3D transformation matrix |

## Conventions and transforms

Matrices use row-major storage but multiply column vectors on the right. `mul(a, b)` computes `a * b`, so `b` acts first. The coordinate spaces are determined by the matrices supplied: for example, `projection * view * model` maps model-space points to homogeneous clip coordinates; dividing by clip W produces normalized device coordinates.

Angles are radians. The 2D rotation builders turn +X toward +Y for a positive angle (counterclockwise when X points right and Y points up). The 3D rotation builders follow the right-hand rule. `rotate_axis` normalizes its axis and requires a nonzero axis. The 2D `world_transform` is `T * R * S`; the 4x4 version is `T * Rx * Ry * Rz * S`, applying scale, Z, Y, X, then translation.

Point transforms append a homogeneous 1; direction transforms append 0 and ignore translation. The 3x3 and 4x4 point functions divide by the computed homogeneous `w` when `|w - 1|` exceeds `1e-10` for f64 or `1e-6` for f32. In that case, `|w|` must exceed the same threshold. The full `transform` functions return all homogeneous components without dividing. Array transforms require non-null pointers even when count is zero. Exact in-place operation is supported; partially overlapping source and destination ranges can overwrite unread elements.

Scale getters return the lengths of the linear-part columns, so they do not recover negative scale signs and are not a general decomposition of shear. The 2D rotation getter computes `atan2(m10, m00)`; translation getters read the last affine column.

## Inversion requirements and numerical limits

The inverse functions require a finite, invertible matrix and arithmetic within
the [safe operations](safe-ops.md) range. For 3x2 affine matrices, the 2x2
linear part must be invertible. When `LM2_UNSAFE` is not defined,
a computed zero determinant (including signed zero) or invalid arithmetic
causes an assertion. `LM2_UNSAFE` disables these checks when defined while
including libmath2; the caller remains responsible for valid inputs.

The inverses use determinant/cofactor arithmetic. A nonzero computed
determinant does not guarantee that a matrix is well-conditioned or that its
inverse is accurate. Rounding, overflow, and underflow can affect results or
cause assertions, especially for ill-conditioned matrices and extreme scales.
Choose input scales and precision appropriate for the application, and check
inverse residuals where accuracy matters.

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
| `lm2_m3x2_mul_f32(a, b)` | Matrix multiplication (applies b first, then a) |
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
| `lm2_m3x2_ortho_f32(left, right, bottom, top)` | Maps left/right and bottom/top to -1/+1; each absolute extent must exceed `1e-6` in both precisions |

---

## Matrix 3x3 Layout

Row-major, 9 elements:

```
[m00 m01 m02]
[m10 m11 m12]
[m20 m21 m22]
```

Access via named fields (`m.m00`, ...) or flat array (`m.e[0]` through `m.e[8]`).

All nine elements are stored. The 2D affine builders use bottom row `[0 0 1]`; other bottom rows can represent projective transforms. The matrix also supports general 3D linear transforms.

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
| `lm2_m3x3_mul_f32(a, b)` | Matrix multiplication |
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
| `lm2_m4x4_mul_f32(a, b)` | Matrix multiplication |
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

Build a right-handed world-to-view matrix: the eye maps to the origin and the direction from eye to target maps to negative Z. The rows contain right, corrected up, and negative forward. The length of `target - eye` and the length of the cross product of normalized forward with `up` must each exceed `1e-10` for f64 or `1e-6` for f32.

**Signature:** `lm2_m4x4_f32 lm2_m4x4_look_at_f32(lm2_v3_f32 eye, lm2_v3_f32 target, lm2_v3_f32 up)`

#### `lm2_m4x4_perspective_f32`

Build a right-handed perspective projection from view space looking down negative Z. After homogeneous division, `z = -near_plane` maps to NDC -1 and `z = -far_plane` maps to +1; `w_clip = -z_view`. For a conventional frustum use positive aspect, `0 < fov_y < π`, and `0 < near_plane < far_plane`. The absolute values of aspect, tangent of half FOV, and far-minus-near must exceed `1e-10` for f64 or `1e-6` for f32.

**Signature:** `lm2_m4x4_f32 lm2_m4x4_perspective_f32(float fov_y, float aspect, float near_plane, float far_plane)`

**Parameters:**
- `fov_y` — Vertical field of view in radians
- `aspect` — Width / height ratio
- `near_plane` — Near clipping distance
- `far_plane` — Far clipping distance

#### `lm2_m4x4_ortho_f32`

Build a right-handed orthographic projection from view space to NDC. Left/right and bottom/top map to -1/+1; view-space `z = -near_plane` and `z = -far_plane` map to -1 and +1. The absolute separation of each pair of bounds must exceed `1e-10` for f64 or `1e-6` for f32.

**Signature:** `lm2_m4x4_f32 lm2_m4x4_ortho_f32(float left, float right, float bottom, float top, float near_plane, float far_plane)`

### Quaternion Conversions

| Function | Description |
|----------|-------------|
| `lm2_m4x4_from_quat_f32(q)` | Normalize a nonzero quaternion and convert it to a 4x4 rotation matrix |
| `lm2_m4x4_to_quat_f32(m)` | Extract a quaternion from the orthonormal upper-left 3x3 rotation |

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

lm2_m4x4_f32 mvp = lm2_m4x4_mul_f32(
    lm2_m4x4_mul_f32(proj, view), model
);
```
