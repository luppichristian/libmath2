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

**Note:** Keep this list up to date when adding or modifying modules.

## Code Safety and Consistency Standards

### 1. Use Safe Operations Instead of Standard C Operators

All arithmetic operations in libmath2 implementation files should use safe operations from `libmath2_safe_ops.h` instead of standard C operators. This provides overflow/underflow detection and division-by-zero protection.

**Include the header:**
```c
#include <libmath2/libmath2_safe_ops.h>
```

**Replace operators as follows:**

| Standard C | Safe Operation (double) | Safe Operation (float) |
|------------|-------------------------|------------------------|
| `a + b`    | `lm2_add_f64(a, b)`    | `lm2_add_f32(a, b)`   |
| `a - b`    | `lm2_sub_f64(a, b)`    | `lm2_sub_f32(a, b)`   |
| `a * b`    | `lm2_mul_f64(a, b)`    | `lm2_mul_f32(a, b)`   |
| `a / b`    | `lm2_div_f64(a, b)`    | `lm2_div_f32(a, b)`   |

**Example:**
```c
// ❌ Standard C operators
double result = a + b * c;

// ✅ Safe operations
double result = lm2_add_f64(a, lm2_mul_f64(b, c));
```

**Note:** Safe operations are available for integer types as well (`_i64`, `_i32`, `_i16`, `_i8`, `_u64`, `_u32`, `_u16`, `_u8`).

### 2. Use libmath2_scalar Functions

Replace standard C math functions with libmath2_scalar equivalents to maintain consistency and leverage library features.

**Include the header:**
```c
#include <libmath2/libmath2_scalar.h>
```

**Common replacements:**

| Standard C      | libmath2_scalar (double) | libmath2_scalar (float) |
|-----------------|--------------------------|-------------------------|
| `fmod(a, b)`    | `lm2_mod_f64(a, b)`     | `lm2_mod_f32(a, b)`    |
| `pow(b, e)`     | `lm2_pow_f64(b, e)`     | `lm2_pow_f32(b, e)`    |
| `sqrt(a)`       | `lm2_sqrt_f64(a)`       | `lm2_sqrt_f32(a)`      |
| `floor(a)`      | `lm2_floor_f64(a)`      | `lm2_floor_f32(a)`     |
| `ceil(a)`       | `lm2_ceil_f64(a)`       | `lm2_ceil_f32(a)`      |
| `round(a)`      | `lm2_round_f64(a)`      | `lm2_round_f32(a)`     |
| `trunc(a)`      | `lm2_trunc_f64(a)`      | `lm2_trunc_f32(a)`     |
| `fabs(a)`       | `lm2_abs_f64(a)`        | `lm2_abs_f32(a)`       |

**Example:**
```c
// ❌ Standard C functions
double result = sqrt(pow(a, 2.0) + pow(b, 2.0));

// ✅ libmath2_scalar functions
double result = lm2_sqrt_f64(lm2_add_f64(lm2_pow_f64(a, 2.0), lm2_pow_f64(b, 2.0)));
```

### 3. Use libmath2_trigonometry Functions

Replace standard C trigonometry functions with libmath2_trigonometry equivalents.

**Include the header:**
```c
#include <libmath2/libmath2_trigonometry.h>
```

**Common replacements:**

| Standard C    | libmath2_trigonometry (double) | libmath2_trigonometry (float) |
|---------------|--------------------------------|------------------------------|
| `sin(a)`      | `lm2_sin_f64(a)`              | `lm2_sin_f32(a)`            |
| `cos(a)`      | `lm2_cos_f64(a)`              | `lm2_cos_f32(a)`            |
| `tan(a)`      | `lm2_tan_f64(a)`              | `lm2_tan_f32(a)`            |
| `asin(a)`     | `lm2_asin_f64(a)`             | `lm2_asin_f32(a)`           |
| `acos(a)`     | `lm2_acos_f64(a)`             | `lm2_acos_f32(a)`           |
| `atan(a)`     | `lm2_atan_f64(a)`             | `lm2_atan_f32(a)`           |
| `atan2(y, x)` | `lm2_atan2_f64(y, x)`         | `lm2_atan2_f32(y, x)`       |

**Example:**
```c
// ❌ Standard C functions
double result = sin(angle) * cos(angle);

// ✅ libmath2_trigonometry functions
double result = lm2_mul_f64(lm2_sin_f64(angle), lm2_cos_f64(angle));
```

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

## Files Following These Standards

The following files have been updated to follow these standards:

- `src/libmath2_scalar.c`
- `src/libmath2_trigonometry.c`
- `src/libmath2_easings.c`
- `src/libmath2_noise.c`

## Benefits

1. **Safety**: Overflow, underflow, and division-by-zero detection
2. **Consistency**: Uniform API across the entire library
3. **Maintainability**: Easier to add optimizations or logging to all operations
4. **Portability**: Centralized handling of platform-specific behavior
5. **Debugging**: LM2_ASSERTS can be triggered on error conditions

## Exception: Low-Level Implementations

The implementations of the safe operations themselves (in `libmath2_safe_ops.c`) and certain low-level wrappers (like `lm2_sin_f64` calling `sin()`) are exempt from these rules, as they form the foundation of the abstraction layer.

## Creating Generic Functions

libmath2 provides a consistent pattern for creating type-generic functions that work across all 10 standard numeric types (`f64`, `f32`, `i64`, `i32`, `i16`, `i8`, `u64`, `u32`, `u16`, `u8`).

### The Generic Function Pattern

**Step 1: Define Internal Generic Macro Utility**

First, define an internal generic macro utility using the `_LM2_GENERIC` helper from `lm2_generic.h`. The internal utility should have an underscore prefix:

```c
#include <lm2/lm2_generic.h>

// Internal generic macro utility (with underscore prefix)
#define _lm2_my_function(x, y) _LM2_GENERIC(lm2_my_function, x, y)
```

**Step 2: Define Public Generic Function**

Then define the public generic function macro using the internal utility:

```c
#ifndef LM2_NO_GENERICS
  #define lm2_my_function(x, y) _lm2_my_function(x, y)
#endif
```

**Step 3: Implement Type-Specific Variants**

Implement all type-specific variants that the generic macro will dispatch to:

```c
// In header file
double lm2_my_function_f64(double x, double y);
float lm2_my_function_f32(float x, float y);
int64_t lm2_my_function_i64(int64_t x, int64_t y);
// ... (continue for all 10 types)

// In source file
double lm2_my_function_f64(double x, double y) {
    return lm2_add_f64(x, y);  // Use safe operations!
}
// ... (implement remaining variants)
```

### Complete Example

Here's a complete example from `lm2_safe_ops.h`:

```c
// 1. Define internal generic macro utility
#define _lm2_add(a, b) _LM2_GENERIC(lm2_add, a, b)

// 2. Define public generic function
#ifndef LM2_NO_GENERICS
  #define lm2_add(a, b) _lm2_add(a, b)
#endif

// 3. Type-specific implementations exist
// lm2_add_f64, lm2_add_f32, lm2_add_i64, etc.
```

### Key Rules

1. **Always define the internal utility first** (with underscore prefix)
2. **Then define the public generic function** using the internal utility
3. **Implement all 10 type-specific variants** (`_f64`, `_f32`, `_i64`, `_i32`, `_i16`, `_i8`, `_u64`, `_u32`, `_u16`, `_u8`)
4. **Respect `LM2_NO_GENERICS`** - wrap public generic macros in `#ifndef LM2_NO_GENERICS`
5. **The first argument determines the dispatch** - `_LM2_GENERIC` uses the first variadic argument to determine which type-specific function to call

### How It Works

- **C11**: Uses `_Generic` keyword for compile-time type selection
- **C++17**: Uses template specialization with `std::is_same_v` for type selection
- Both approaches provide zero runtime overhead - the correct function is selected at compile time

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
