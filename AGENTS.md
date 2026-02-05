# Agent Guidelines for libmath2

This document provides guidelines for AI agents and developers working on the libmath2 codebase.

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

## Adding New Functions

When adding new mathematical functions to libmath2:

1. Define the function prototype in the appropriate header
2. Implement both `_f64` and `_f32` variants
3. Use safe operations and libmath2 functions internally
4. Add generic macro support if applicable
5. Update this document if introducing new categories of functions
