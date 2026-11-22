# Getting Started

## Installation

Copy the `include/` directory into your project or add it to your compiler's
include path. The bundled `cute_c2.h` supplies the 2D collision backend.

## Running the tests

The test suite uses CMake 3.19 or newer and GoogleTest. Configure, build, and
run it from the repository root:

```sh
cmake -S tests -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

CMake fetches GoogleTest if it is not installed. Set `LM2_GTEST_FETCH=OFF` to
require a locally installed copy.

## Basic Usage

Include libmath2 in each translation unit that calls its functions. The
functions have `static inline` linkage, so no separately compiled libmath2
library is needed.

```c
#include <lm2.h>
```

You can also include individual modules:

```c
#include <lm2/vectors/lm2_vector3.h>
#include <lm2/matrices/lm2_matrix4x4.h>
#include <lm2/misc/lm2_quaternion.h>
```

A C11 compiler is required for C; C++ extensions require C++20. Some platforms
also require linking the system math library, for example with `-lm`.

The following snippets assume `<lm2.h>` is included.

### Working with Vectors

```c
// Create vectors
lm2_v3_f32 a = lm2_v3_make_f32(1.0f, 2.0f, 3.0f);
lm2_v3_f32 b = lm2_v3_splat_f32(5.0f);  // {5, 5, 5}

// Arithmetic
lm2_v3_f32 sum  = lm2_v3_add_f32(a, b);
lm2_v3_f32 diff = lm2_v3_sub_f32(a, b);
lm2_v3_f32 scaled = lm2_v3_mul_s_f32(a, 2.0f);

// Dot and cross products
float dot = lm2_v3_dot_f32(a, b);
lm2_v3_f32 cross = lm2_v3_cross_f32(a, b);

// Length and normalization
float len = lm2_v3_length_f32(a);
lm2_v3_f32 unit = lm2_v3_norm_f32(a);

// Access components
float x = a.x;
float y = a.y;
float z = a.z;
// Or by index
float first = a.e[0];
```

### Working with Matrices

```c
// Identity and transformation matrices
lm2_m4x4_f32 identity = lm2_m4x4_identity_f32();
lm2_m4x4_f32 trans = lm2_m4x4_translate_f32(lm2_v3_make_f32(10, 0, 0));
lm2_m4x4_f32 rot = lm2_m4x4_rotate_y_f32(LM2_HPI_F32);
lm2_m4x4_f32 scl = lm2_m4x4_scale_f32(lm2_v3_splat_f32(2.0f));

// Combine transforms
lm2_m4x4_f32 model = lm2_m4x4_mul_f32(trans, rot);

// Transform a point
lm2_v3_f32 world_pos = lm2_m4x4_transform_point_f32(model, lm2_v3_zero_f32());

// Camera and projection
lm2_m4x4_f32 view = lm2_m4x4_look_at_f32(
    lm2_v3_make_f32(0, 5, 10),  // eye
    lm2_v3_zero_f32(),           // target
    lm2_v3_make_f32(0, 1, 0)    // up
);
lm2_m4x4_f32 proj = lm2_m4x4_perspective_f32(
    lm2_deg_to_rad_f32(60.0f),  // FOV
    16.0f / 9.0f,                // aspect ratio
    0.1f, 1000.0f                // near, far
);
```

### Working with Quaternions

```c
// Create quaternions
lm2_quat_f32 q = lm2_quat_from_axis_angle_f32(
    lm2_v3_make_f32(0, 1, 0),  // Y axis
    LM2_HPI_F32                 // 90 degrees
);

// Rotate a vector
lm2_v3_f32 rotated = lm2_quat_rotate_vector_f32(q, lm2_v3_make_f32(1, 0, 0));

// Interpolate rotations
lm2_quat_f32 q2 = lm2_quat_from_euler_f32(LM2_PI_F32, 0, 0);
lm2_quat_f32 mid = lm2_quat_slerp_f32(q, q2, 0.5f);
```

## Numeric Type Suffixes

All vector, matrix, range, and scalar functions are suffixed with the numeric type:

| Suffix | C Type | Description |
|--------|--------|-------------|
| `_f64` | `double` | 64-bit floating point |
| `_f32` | `float` | 32-bit floating point |
| `_i64` | `int64_t` | 64-bit signed integer |
| `_i32` | `int32_t` | 32-bit signed integer |
| `_i16` | `int16_t` | 16-bit signed integer |
| `_i8` | `int8_t` | 8-bit signed integer |
| `_u64` | `uint64_t` | 64-bit unsigned integer |
| `_u32` | `uint32_t` | 32-bit unsigned integer |
| `_u16` | `uint16_t` | 16-bit unsigned integer |
| `_u8` | `uint8_t` | 8-bit unsigned integer |

## Compile-Time Configuration

| Define | Description |
|--------|-------------|
| `LM2_UNSAFE` | Disable overflow/underflow assertions in safe arithmetic for performance |
| `LM2_NO_CPP_OPERATORS` | Disable C++ operator overloads (`+`, `-`, `*`, `/`, `[]`) |
| `LM2_NO_GENERICS` | Disable C11 `_Generic` macros and C++ function overloads |
| `LM2_ASSERT(expr)` | Override assertions; by default uses `assert` in debug builds and aborts on failure with `NDEBUG` |

Define `LM2_UNSAFE` or customize `LM2_ASSERT` before including libmath2 in
each translation unit where the configuration should apply. See [Safe Arithmetic](modules/safe-ops.md)
for configuration and numerical behavior.

## C++ Features

The public vector types use anonymous-struct extensions to expose component
aliases. Clang, GCC, and MSVC accept these in their default modes, but strict
ISO C++20 builds with `-pedantic-errors` do not support the current vector API.

When compiled as C++, libmath2 automatically provides:

- **Operator overloads** for vectors, ranges, and matrices (`+`, `-`, `*`, `/`, `[]`)
- **Function overloads** that let you omit the type suffix (e.g., `lm2_v3_add(a, b)` instead of `lm2_v3_add_f32(a, b)`)

Disable with `LM2_NO_CPP_OPERATORS` or `LM2_NO_GENERICS`.
