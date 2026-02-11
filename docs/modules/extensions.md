---
layout: default
title: Extensions
---

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

The correct function is selected at compile time based on the argument types via `_Generic`.

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

**Disable:** Define `LM2_NO_CPP_OPERATORS` before including headers.

## Subscript Operator

All vector, matrix, and range types support `operator[]` in C++ for element access:

```cpp
lm2_v3_f32 v = lm2_v3_make_f32(1, 2, 3);
float y = v[1];   // 2.0f
v[0] = 10.0f;     // modify x component

lm2_m4x4_f32 m = lm2_m4x4_identity_f32();
float diag = m[0]; // m00
```

Bounds are checked with `LM2_ASSERT`.

## Automatic Inclusion

When including `<lm2.h>`, extensions are automatically included based on the compiler:

- **C++:** Both `lm2_cpp_generics.h` and `lm2_cpp_operators.h` are included
- **C11+:** `lm2_c11_generics.h` is included
- **Pre-C11 C:** No extensions

To opt out, define `LM2_NO_GENERICS` and/or `LM2_NO_CPP_OPERATORS` before including any headers.
