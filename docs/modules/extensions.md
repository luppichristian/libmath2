# C/C++ Extensions

## Overview

Optional language extensions that provide a more ergonomic API: C11 `_Generic` macros for type-inferred function dispatch, C++ function overloads, and C++ operator overloads.

## Why Use This?

These extensions let you write cleaner code by removing the need for explicit type suffixes. In C++ you can use natural operators like `+`, `-`, `*`, `/` on vectors and matrices.

## C11 Generic Macros

**Header:** `lm2/extensions/lm2_c11_generics.h`

When compiling as C11 or later, type-generic macros are available so you can write:

```c
lm2_v3_f32 a = lm2_v3_make_f32(1, 2, 3);
lm2_v3_f32 b = lm2_v3_make_f32(4, 5, 6);

lm2_v3_f32 sum = lm2_v3_add(a, b);  // Dispatches to lm2_v3_add_f32
```

Each macro selects a function at compile time using its controlling expression. Other scalar arguments are converted to the selected function’s parameter types; for example, `lm2_add(1.0f, 2.0)` selects the f32 function. Supported argument types and parameter order depend on the macro.

**Disable:** Define `LM2_NO_GENERICS` before including headers.

## C++ Function Overloads

**Header:** `lm2/extensions/lm2_cpp_generics.h`

When compiling as C++, function overloads are provided:

```cpp
lm2_v3_f32 a = lm2_v3_make_f32(1, 2, 3);
lm2_v3_f64 b = lm2_v3_make_f64(1, 2, 3);

lm2_v3_f32 r1 = lm2_v3_add(a, a);  // Calls lm2_v3_add_f32
lm2_v3_f64 r2 = lm2_v3_add(b, b);  // Calls lm2_v3_add_f64
```

**Disable:** Define `LM2_NO_GENERICS` before including headers.

## C++ Operator Overloads

**Header:** `lm2/extensions/lm2_cpp_operators.h`

When compiling as C++, operator overloads are available for vectors, ranges, and matrices:

```cpp
lm2_v3_f32 a = lm2_v3_make_f32(1, 2, 3);
lm2_v3_f32 b = lm2_v3_make_f32(4, 5, 6);

lm2_v3_f32 sum  = a + b;    // lm2_v3_add_f32
lm2_v3_f32 diff = a - b;    // lm2_v3_sub_f32
lm2_v3_f32 prod = a * b;    // lm2_v3_mul_f32
lm2_v3_f32 quot = a / b;    // lm2_v3_div_f32

float x = a[0];             // subscript operator
```

For matrices, `m3x2 * v2` and `m4x4 * v3` transform points, including
translation and, for 4x4, a possible homogeneous divide. Use
`transform_vector` for directions. `m3x3 * v3` and `m4x4 * v4` return full
homogeneous products. For ranges, `|` and `&` are union and intersection;
adding a vector translates, while multiplying by a scalar or vector scales the
bounds about the origin. Quaternion `q * v3` rotates a vector and expects a
unit quaternion.

**Disable:** Define `LM2_NO_CPP_OPERATORS` before including headers.

## Generic-wrapper limitations

Some C11 macros refer to undeclared functions and fail when expanded:

- `lm2_r2_make`, `lm2_r3_make`, `lm2_r4_make`, and `lm2_r2_get_center`.
- `lm2_m3x2_from_translation`, `_from_rotation`, and `_from_scale`.
- `lm2_m3x3_from_rotation_x`, `_from_rotation_y`, and `_from_rotation_z`.
- `lm2_m4x4_from_translation`, `_from_rotation_x`, `_from_rotation_y`, `_from_rotation_z`, `_from_quaternion`, and `_orthographic`.

Six other C11 macros pass too few arguments to their declared targets:
`lm2_triangle2_make`, `lm2_triangle3_make`, `lm2_ray2_make`, `lm2_ray3_make`,
`lm2_raycast_sphere`, and `lm2_raycast_triangle`. Use their suffixed functions
with the signatures in the headers. Four C triangle macros also fail because
array arguments decay to pointers before `_Generic` selection:
`lm2_triangle2_area`, `lm2_triangle2_contains_point`, `lm2_triangle3_area`,
and `lm2_triangle3_normal`. Call their suffixed versions directly.

Use explicit suffixed functions instead. Range construction can use
`lm2_r2_from_min_max_f32`, `lm2_r3_from_min_max_f32`, or
`lm2_r4_from_min_max_f32`, for example; `lm2_r2_center_f32` gets the center.
The corresponding 3x2 builders are `translate`, `rotate`, and `scale_uniform`;
4x4 builders are `translate`, `rotate_x/y/z`, `from_quat`, and `ortho`, with
`_f32` or `_f64` suffixes. For 2D homogeneous rotation use
`lm2_m3x3_rotate_f32`; there are no 3x3 X/Y rotation builders. Some declared
suffixed range functions also lack definitions, as listed in
[Ranges](ranges.md).

C++ templates have separate limitations, and argument deduction varies across
modules. For example, `lm2_quat_inverse(q)` cannot deduce its scalar type, and
`lm2_camera3_get_view(cam)` cannot deduce its scalar and matrix return types.
The suffixed functions avoid these deduction issues. `lm2_m4x4_mul(a, b)`
cannot infer its scalar template argument, although
`lm2_m4x4_mul<float>(a, b)` can. The two-argument generic
`lm2_m4x4_rotate_x<float>(m, angle)` calls a one-argument function and fails to
instantiate. Prefer suffixed matrix functions when a wrapper cannot be used.
Additional C++ matrix templates reference undeclared targets: 3x2
`from_rotation` and `from_scale`; 3x3 `from_rotation_x/y/z`, `from_scale`,
and `rotate_x/y/z`; and 4x4 `from_rotation_x/y/z`, `from_scale`, and
`orthographic`. The 3x2 `rotate` and `scale`, 3x3 `scale`, and 4x4
`rotate_x/y/z` and `scale` templates pass a matrix to typed builders that take
only an angle or scale. Use suffixed builders and `mul` to compose a matrix in
the order described in [Matrices](matrices.md). The C++ `lm2_hash_fnv1a(x)`
wrapper also passes one argument to a function that requires a buffer and size;
use `lm2_hash_fnv1a_u32(data, size)` or `_u64` directly.

C++ scalar templates also require compatible argument types for deduction; the
mixed-type C example above does not deduce a single `T` in C++.

## Subscript Operator

All vector, matrix, and range types support `operator[]` in C++ for element access:

```cpp
lm2_v3_f32 v = lm2_v3_make_f32(1, 2, 3);
float y = v[1];   // 2.0f
v[0] = 10.0f;     // modify x component

lm2_m4x4_f32 m = lm2_m4x4_identity_f32();
float diag = m[0]; // m00
```

Bounds are checked with `LM2_ASSERT`. Defining `LM2_NO_CPP_OPERATORS` also
removes these subscript operators.

## Unprefixed aliases

Define `LM2_ENABLE_UNPREFIXED_NAMES` before including `<lm2.h>` to enable
preprocessor aliases such as `v2_f32` for `lm2_v2_f32` and `v2_add_f32` for
`lm2_v2_add_f32`. There is no default-precision `v2` type. Unsuffixed generic
function aliases are omitted when `LM2_NO_GENERICS` is defined. The aliases
include common names such as `floor`, `div`, and `abs`, and replace existing
`min` and `max` macros, so enabling them can affect other headers and code.
Some aliases refer to stale or unavailable targets, including `r2_make_f32`,
`r2_get_center_f32`, and `m4x4_from_quaternion_f32`; use the prefixed suffixed
functions when an alias is unavailable.

## Automatic Inclusion

When including `<lm2.h>`, extensions are automatically included based on the compiler:

- **C++:** Both `lm2_cpp_generics.h` and `lm2_cpp_operators.h` are included
- **C11+:** `lm2_c11_generics.h` is included
- **Pre-C11 C:** No extensions

To opt out, define `LM2_NO_GENERICS` and/or `LM2_NO_CPP_OPERATORS` before including any headers.
Individual module headers expose their suffixed APIs without automatically
including the global generics and non-member operator overloads. Include
`<lm2.h>` or the relevant extension header when those features are needed.
