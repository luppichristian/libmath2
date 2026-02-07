# Agent Guidelines for libmath2

This document provides guidelines for AI agents and developers working on the libmath2 codebase.

## Library Modules Overview

Quick reference of all libmath2 modules:

| Module | Description |
|--------|-------------|
| **lm2_base.h** | Base types, macros, and core definitions |
| **lm2_constants.h** | Mathematical constants (PI, E, etc.) |
| **lm2_generic.h** | Type-generic macro utilities (`_LM2_GENERIC`) |
| **lm2_safe_ops.h** | Safe arithmetic operations with overflow/underflow detection |
| **lm2_scalar.h** | Scalar math functions (sqrt, pow, floor, ceil, abs, etc.) |
| **lm2_trigonometry.h** | Trigonometric functions (sin, cos, tan, asin, acos, atan, atan2) |
| **lm2_easings.h** | Easing functions for animations and interpolations |
| **lm2_noise.h** | Noise generation functions (Perlin, simplex, etc.) |
| **lm2_hash.h** | Hash functions for various data types |
| **lm2_bezier_curves.h** | Bézier curve calculations |
| **lm2_vector2.h** | 2D vector operations |
| **lm2_vector3.h** | 3D vector operations |
| **lm2_vector4.h** | 4D vector operations |
| **lm2_vector_defines.h** | Vector type definitions and structure declarations |
| **lm2_vector_operators.h** | Generic vector operator macros |
| **lm2_vector_specifics.h** | Vector-specific utility functions |
| **lm2_edge.h** | Edge calculations and operations |
| **lm2_triangle.h** | Triangle calculations and operations |
| **lm2_triangle_geometry.h** | Triangle list conversions (vertex arrays, indexed meshes) |

**Note:** Keep this list up to date when adding or modifying modules.

## Code Safety and Consistency Standards

### Use Library Functions (Not Standard C)

Replace standard C operators and functions with libmath2 equivalents for safety, consistency, and overflow/underflow detection.

**Include required headers:**
```c
#include <libmath2/libmath2_safe_ops.h>      // For arithmetic operations
#include <libmath2/libmath2_scalar.h>        // For scalar math functions
#include <libmath2/libmath2_trigonometry.h>  // For trig functions
```

**Function replacements:**

| Standard C | libmath2 (double) | libmath2 (float) |
|------------|-------------------|------------------|
| `a + b` | `lm2_add_f64(a, b)` | `lm2_add_f32(a, b)` |
| `a - b` | `lm2_sub_f64(a, b)` | `lm2_sub_f32(a, b)` |
| `a * b` | `lm2_mul_f64(a, b)` | `lm2_mul_f32(a, b)` |
| `a / b` | `lm2_div_f64(a, b)` | `lm2_div_f32(a, b)` |
| `fmod(a, b)` | `lm2_mod_f64(a, b)` | `lm2_mod_f32(a, b)` |
| `pow(b, e)` | `lm2_pow_f64(b, e)` | `lm2_pow_f32(b, e)` |
| `sqrt(a)` | `lm2_sqrt_f64(a)` | `lm2_sqrt_f32(a)` |
| `floor(a)` | `lm2_floor_f64(a)` | `lm2_floor_f32(a)` |
| `ceil(a)` | `lm2_ceil_f64(a)` | `lm2_ceil_f32(a)` |
| `round(a)` | `lm2_round_f64(a)` | `lm2_round_f32(a)` |
| `trunc(a)` | `lm2_trunc_f64(a)` | `lm2_trunc_f32(a)` |
| `fabs(a)` | `lm2_abs_f64(a)` | `lm2_abs_f32(a)` |
| `sin(a)` | `lm2_sin_f64(a)` | `lm2_sin_f32(a)` |
| `cos(a)` | `lm2_cos_f64(a)` | `lm2_cos_f32(a)` |
| `tan(a)` | `lm2_tan_f64(a)` | `lm2_tan_f32(a)` |
| `asin(a)` | `lm2_asin_f64(a)` | `lm2_asin_f32(a)` |
| `acos(a)` | `lm2_acos_f64(a)` | `lm2_acos_f32(a)` |
| `atan(a)` | `lm2_atan_f64(a)` | `lm2_atan_f32(a)` |
| `atan2(y, x)` | `lm2_atan2_f64(y, x)` | `lm2_atan2_f32(y, x)` |

**Note:** All functions also available for integer types (`_i64`, `_i32`, `_i16`, `_i8`, `_u64`, `_u32`, `_u16`, `_u8`).

### Memory Allocation Policy

**Never allocate memory internally.** Caller handles all memory management. Functions requiring buffers use a query-then-write pattern:

```c
size_t size = lm2_function(input, NULL, 0);  // Query size
void* buffer = malloc(size);                  // Caller allocates
lm2_function(input, buffer, size);            // Write to buffer
```

**Rules:** No `malloc`/`calloc`/`realloc`/`free` in library code • Validate buffer sizes • Document buffer requirements

## Implementation Checklist

When implementing or modifying functions in libmath2, ensure:

- [ ] Use `LM2_API` in all function declarations (both in headers and implementations)
- [ ] Include `libmath2_safe_ops.h` for arithmetic operations
- [ ] Include `libmath2_scalar.h` for scalar math functions
- [ ] Include `libmath2_trigonometry.h` for trigonometric functions
- [ ] Replace all arithmetic operators (`+`, `-`, `*`, `/`) with safe operations
- [ ] Replace all standard C math functions with libmath2 equivalents
- [ ] Replace all standard C trig functions with libmath2 equivalents
- [ ] Use appropriate type suffixes (`_f64` for double, `_f32` for float, etc.)
- [ ] Keep `<math.h>` included only if absolutely necessary for low-level functions
- [ ] Never allocate memory internally (use query-then-write pattern for buffer operations)

**Files updated:** `src/libmath2_scalar.c`, `src/libmath2_trigonometry.c`, `src/libmath2_easings.c`, `src/libmath2_noise.c`

**Benefits:** Safety (overflow/underflow/div-by-zero detection) • Consistency • Maintainability • Portability • Debugging (LM2_ASSERTS)

**Exception:** Low-level implementations in `libmath2_safe_ops.c` and wrappers like `lm2_sin_f64` calling `sin()` are exempt.

## Creating Generic Functions

Create type-generic functions that work across all 10 numeric types (`f64`, `f32`, `i64`, `i32`, `i16`, `i8`, `u64`, `u32`, `u16`, `u8`).

**Pattern:**

```c
#include <lm2/lm2_generic.h>

// 1. Define internal generic macro utility (with underscore prefix)
#define _lm2_my_function(x, y) _LM2_GENERIC(lm2_my_function, x, y)

// 2. Define public generic function
#ifndef LM2_NO_GENERICS
  #define lm2_my_function(x, y) _lm2_my_function(x, y)
#endif

// 3. Implement all 10 type-specific variants
double lm2_my_function_f64(double x, double y) { return lm2_add_f64(x, y); }
float lm2_my_function_f32(float x, float y) { return lm2_add_f32(x, y); }
// ... (continue for all 10 types)
```

**Rules:** Define internal utility first (underscore prefix) • Use internal utility in public macro • Wrap public macro in `#ifndef LM2_NO_GENERICS` • Implement all 10 type-specific variants • First argument determines dispatch

**How it works:** C11 uses `_Generic` keyword; C++17 uses template specialization. Both provide zero runtime overhead.

## Adding New Functions

When adding new mathematical functions to libmath2:

1. Define the function prototype in the appropriate header using `LM2_API`
2. Implement all 10 type-specific variants (`_f64`, `_f32`, `_i64`, `_i32`, `_i16`, `_i8`, `_u64`, `_u32`, `_u16`, `_u8`) with `LM2_API`
3. Use safe operations and libmath2 functions internally
4. Add generic macro support following the pattern above:
   - Define internal generic macro utility (`_lm2_function_name`)
   - Define public generic function (`lm2_function_name`)
5. Update this document if introducing new categories of functions

**Note:** If a module doesn't define a specific function or helper that is strictly related to that module's domain, you can add it yourself. Ensure the new function follows the library's conventions and is placed in the appropriate module.

**Important:** Do not create examples or tests unless specifically requested.
