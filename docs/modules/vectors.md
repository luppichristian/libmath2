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

### 3D Vectors (`lm2_v3_*`)

Same type variants as 2D with an additional `z` component.

### 4D Vectors (`lm2_v4_*`)

Same type variants with `x`, `y`, `z`, `w` components.

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
```

In C++, the same type also supports checked subscripting:

```cpp
lm2_v3_f32 v = lm2_v3_make_f32(1.0f, 2.0f, 3.0f);
float second = v[1];
```

## Functions

The examples use `_f32`. Basic arithmetic, construction, `min`, `max`, and
`clamp` also have integer variants; negation, `abs`, sign, `min_abs`, and
`max_abs` have signed integer variants. Rounding, interpolation, `fract`,
`pow`, and `sqrt` are floating-point operations. Coordinates have the meaning
the caller assigns them: component-wise operations do not transform between
world, view, model, or any other coordinate spaces. Geometric operations such
as dot products and normalization are covered in [Vector Specifics](vector-specifics.md).

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
| `lm2_v2_clamp_f32(value, min, max)` | Clamp each component between its corresponding bounds |

### Sign and Absolute Value

| Function | Description |
|----------|-------------|
| `lm2_v2_abs_f32(a)` | Absolute value of each component |
| `lm2_v2_sign_f32(a)` | Sign of each component (1 for zero or positive, -1 for negative) |
| `lm2_v2_sign0_f32(a)` | Sign of each component (1, -1, or 0) |

### Interpolation (float types only)

| Function | Description |
|----------|-------------|
| `lm2_v2_saturate_f32(a)` | Clamp each component to [0, 1] |
| `lm2_v2_lerp_f32(a, t, b)` | `a + t * (b - a)` per component, without clamping `t` |
| `lm2_v2_smoothstep_f32(edge0, edge1, x)` | Clamp `(x-edge0)/(edge1-edge0)` to [0, 1], then apply `t*t*(3-2*t)` per component |
| `lm2_v2_alpha_f32(a, b, value)` | `(value-a)/(b-a)` per component; no clamping |

### Math (float types only)

| Function | Description |
|----------|-------------|
| `lm2_v2_fract_f32(a)` | `a - floor(a)` per component (e.g. `fract(-1.25) = 0.75`) |
| `lm2_v2_pow_f32(a, b)` | Component-wise power |
| `lm2_v2_sqrt_f32(a)` | Component-wise square root |

The headers declare `lm2_v3_neg_u64`, `lm2_v4_neg_u32`, and
`lm2_v4_neg_u8`, but the library does not define these unsigned negation
functions; calling them causes a link failure.

## Preconditions and numeric conversions

Arithmetic applies the corresponding [safe scalar operation](safe-ops.md) per
component. Divisors and rounding multiples must be nonzero. Signed integer
division truncates toward zero; modulo is the C remainder (floating-point uses
`fmod`), so its sign follows the dividend. In checked builds, safe arithmetic
asserts on invalid operations and several overflow or underflow conditions;
`LM2_UNSAFE` disables those checks, not the underlying C restrictions. Vector
negation uses native unary minus rather than the safe-negation helper; avoid
negating a signed type’s minimum value.
Floating scalar helpers also have their own assertions, including finite inputs,
ordered clamp limits, distinct interpolation endpoints for `smoothstep` and
`alpha`, and nonnegative square-root inputs. `round` rounds halfway values
away from zero.

`lm2_vector_conversions.h` converts each component independently between scalar
types. Floating-to-integer conversion truncates toward zero; narrowing checks use
`LM2_ASSERT_UNSAFE` where implemented and compare the original value before
truncation. For example, f64-to-i32 rejects `2147483647.5` even though truncating
it would fit. The caller must keep conversions in range even when checks are
disabled. Floating narrowing and integer-to-float
conversion can lose precision. Dimensional upcasts append the supplied `z` or
`w`; downcasts discard the last coordinate. They do not apply a spatial or
homogeneous-coordinate transform.

## Example

```c
#include <lm2/vectors/lm2_vector3.h>
#include <lm2/vectors/lm2_vector_specifics.h>

lm2_v3_f32 a = lm2_v3_make_f32(3.0f, 0.0f, 4.0f);
lm2_v3_f32 b = lm2_v3_make_f32(0.0f, 1.0f, 0.0f);

lm2_v3_f32 sum = lm2_v3_add_f32(a, b);       // {3, 1, 4}
lm2_v3_f32 half = lm2_v3_mul_s_f32(a, 0.5f); // {1.5, 0, 2}
float dot = lm2_v3_dot_f32(a, b);             // 0
lm2_v3_f32 unit = lm2_v3_norm_f32(a);    // {0.6, 0, 0.8}
```
