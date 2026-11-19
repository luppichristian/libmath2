# Quaternions

## Overview

Quaternion types for representing 3D rotations efficiently, with SLERP/NLERP interpolation, Euler angle and axis-angle conversions, and vector rotation.

## Why Use This?

Quaternions avoid gimbal lock, interpolate smoothly, concatenate efficiently, and are more compact than rotation matrices (4 values vs 9).

## Types

| Type | Scalar | Description |
|------|--------|-------------|
| `lm2_quat_f64` | `double` | 64-bit quaternion |
| `lm2_quat_f32` | `float` | 32-bit quaternion |

**Format:** `[x, y, z, w]` where `w` is the scalar part and `(x, y, z)` is the vector part.

## Rotation conventions

Rotations are active, use radians, and follow the right-hand rule: a positive quarter-turn about +Y sends +X toward -Z. `rotate_vector` and `to_euler` expect unit quaternions; quaternion-to-matrix conversion normalizes its nonzero input. `from_axis_angle` normalizes its nonzero axis. `multiply(a, b)` is the Hamilton product and applies `b` first, then `a`. `norm` and `inverse` require a nonzero quaternion.

`from_euler(pitch, yaw, roll)` uses pitch about Y, yaw about Z, and roll about X, composing `Rz(yaw) * Ry(pitch) * Rx(roll)`. The vector form passes its X, Y, Z components as pitch, yaw, roll respectively. `to_euler` returns that same ordering, with pitch in `[-π/2, π/2]`; Euler angles are not unique at gimbal lock. This order differs from the 4x4 `world_transform` Euler order.

`to_axis_angle` requires both output pointers. If the squared vector-part length is below `1e-10` in either precision, it returns axis `(1, 0, 0)` and angle zero. `equals` compares each component within epsilon, so `q` and `-q` can represent the same rotation without comparing equal.

SLERP and NLERP expect unit inputs and negate the second quaternion when necessary to take the shorter arc. Neither clamps `t`, so values outside `[0, 1]` extrapolate. NLERP normalizes the result; SLERP switches to NLERP for nearly identical inputs.

## Functions

### Construction

| Function | Description |
|----------|-------------|
| `lm2_quat_identity_f32()` | Identity quaternion (no rotation) |
| `lm2_quat_zero_f32()` | Zero quaternion |
| `lm2_quat_make_f32(x, y, z, w)` | From components |

### Conversions

| Function | Description |
|----------|-------------|
| `lm2_quat_from_axis_angle_f32(axis, angle)` | From axis and angle (radians) |
| `lm2_quat_from_euler_f32(pitch, yaw, roll)` | From Euler angles |
| `lm2_quat_from_euler_vec_f32(euler)` | From Euler angles as v3 |
| `lm2_quat_to_axis_angle_f32(q, &axis, &angle)` | Extract axis and angle |
| `lm2_quat_to_euler_f32(q)` | Convert to Euler angles (v3) |

### Operations

| Function | Description |
|----------|-------------|
| `lm2_quat_conjugate_f32(q)` | Conjugate (negate vector part) |
| `lm2_quat_inverse_f32(q)` | Inverse rotation |
| `lm2_quat_norm_f32(q)` | Normalize to unit quaternion |
| `lm2_quat_multiply_f32(a, b)` | Combine rotations |
| `lm2_quat_add_f32(a, b)` | Component-wise addition |
| `lm2_quat_sub_f32(a, b)` | Component-wise subtraction |
| `lm2_quat_scale_f32(q, s)` | Scale by scalar |

### Analysis

| Function | Description |
|----------|-------------|
| `lm2_quat_dot_f32(a, b)` | Dot product |
| `lm2_quat_length_f32(q)` | Length (magnitude) |
| `lm2_quat_length_squared_f32(q)` | Squared length |
| `lm2_quat_equals_f32(a, b, epsilon)` | Approximate equality (returns `bool`) |

### Rotation

#### `lm2_quat_rotate_vector_f32`

Rotate a 3D vector by the quaternion.

**Signature:** `lm2_v3_f32 lm2_quat_rotate_vector_f32(lm2_quat_f32 q, lm2_v3_f32 v)`

### Interpolation

#### `lm2_quat_slerp_f32`

Spherical interpolation follows the short arc at constant angular velocity, except when nearly identical inputs trigger the NLERP fallback.

**Signature:** `lm2_quat_f32 lm2_quat_slerp_f32(lm2_quat_f32 a, lm2_quat_f32 b, float t)`

**Parameters:**
- `a` — Start rotation
- `b` — End rotation
- `t` — Interpolation factor [0, 1]

#### `lm2_quat_nlerp_f32`

Normalized linear interpolation. Faster than SLERP but non-constant velocity.

**Signature:** `lm2_quat_f32 lm2_quat_nlerp_f32(lm2_quat_f32 a, lm2_quat_f32 b, float t)`

## Example

```c
// Create rotation: 90 degrees around Y axis
lm2_quat_f32 q = lm2_quat_from_axis_angle_f32(
    lm2_v3_make_f32(0, 1, 0),
    LM2_HPI_F32
);

// Rotate a point
lm2_v3_f32 point = lm2_v3_make_f32(1, 0, 0);
lm2_v3_f32 rotated = lm2_quat_rotate_vector_f32(q, point);
// rotated ~ {0, 0, -1}

// Interpolate between two rotations
lm2_quat_f32 q2 = lm2_quat_from_euler_f32(LM2_PI_F32, 0, 0);
lm2_quat_f32 halfway = lm2_quat_slerp_f32(q, q2, 0.5f);

// Convert to matrix for rendering
lm2_m4x4_f32 mat = lm2_m4x4_from_quat_f32(q);
```
