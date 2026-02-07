# Agent Guidelines for libmath2

Guidelines for AI agents working on libmath2. This library is type-safe, cross-platform, and supports 10 numeric types (f64, f32, i64, i32, i16, i8, u64, u32, u16, u8).

## Table of Contents

1. [Architecture & Modules](#architecture--modules)
2. [Core Principles](#core-principles)
3. [Code Safety Standards](#code-safety-standards)
4. [Type-Generic Programming](#type-generic-programming)
5. [Adding New Functions](#adding-new-functions)
6. [Implementation Checklist](#implementation-checklist)

---

## Architecture & Modules

**Key Features:**
- Type-generic design with zero runtime overhead
- All arithmetic has overflow/underflow detection
- Caller-managed memory (no internal allocations)
- C11+ and C++17+ compatible

**Modules:**

| Module | Purpose |
|--------|---------|
| **lm2_base.h** | Core definitions: `LM2_API`, `LM2_ASSERT`, `LM2_ASSERT_UNSAFE` |
| **lm2_generic.h** | Type-generic dispatcher: `_LM2_GENERIC` |
| **lm2_safe_ops.h** | Arithmetic: `lm2_add`, `lm2_sub`, `lm2_mul`, `lm2_div` |
| **lm2_scalar.h** | Math functions: `lm2_sqrt`, `lm2_pow`, `lm2_floor`, `lm2_ceil`, `lm2_abs`, `lm2_min`, `lm2_max`, `lm2_clamp`, `lm2_lerp` |
| **lm2_trigonometry.h** | Trig functions: `lm2_sin`, `lm2_cos`, `lm2_tan`, `lm2_asin`, `lm2_acos`, `lm2_atan`, `lm2_atan2` |
| **lm2_vector2/3/4.h** | Vector operations (2D/3D/4D) |
| **lm2_vector_specifics.h** | Vector utilities: length, normalize, distance |
| **lm2_easings.h** | Easing/interpolation functions |
| **lm2_noise.h** | Noise generation |
| **lm2_hash.h** | Hash functions |
| **lm2_triangle.h** | Triangle functions |
| **lm2_edge.h** | Edge functions |
| **lm2_bezier_curves.h** | Bézier curves |

---

## Core Principles

1. **Consistency**: Every math operation uses libmath2 functions (no standard C operators)
2. **Explicit Types**: All functions have type suffixes (`_f64`, `_f32`, `_i32`, etc.)
3. **Safety by Default**: `LM2_ASSERT_UNSAFE` checks in debug builds catch overflow/underflow/div-by-zero
4. **No Allocations**: Library never calls `malloc`/`free` - caller manages all memory

---

## Code Safety Standards

**CRITICAL RULE**: Always use libmath2 functions, never standard C operators. This ensures safety and error detection.

**Required headers in every `.c` file:**
```c
#include <lm2/lm2_safe_ops.h>       // For +, -, *, /
#include <lm2/lm2_scalar.h>         // For sqrt, pow, floor, ceil, etc.
#include <lm2/lm2_trigonometry.h>   // For sin, cos, tan, etc.
```

**Function replacements** (all support _f64/_f32/_i64/_i32/_i16/_i8/_u64/_u32/_u16/_u8):

| Standard C | libmath2 | Standard C | libmath2 |
|------------|----------|------------|----------|
| `a + b` | `lm2_add_*(a,b)` | `sqrt(a)` | `lm2_sqrt_*(a)` |
| `a - b` | `lm2_sub_*(a,b)` | `pow(b,e)` | `lm2_pow_*(b,e)` |
| `a * b` | `lm2_mul_*(a,b)` | `floor(a)` | `lm2_floor_*(a)` |
| `a / b` | `lm2_div_*(a,b)` | `ceil(a)` | `lm2_ceil_*(a)` |
| `fmod(a,b)` | `lm2_mod_*(a,b)` | `round(a)` | `lm2_round_*(a)` |
| `fabs(a)` | `lm2_abs_*(a)` | `trunc(a)` | `lm2_trunc_*(a)` |
| `fmin(a,b)` | `lm2_min_*(a,b)` | `sin/cos/tan(a)` | `lm2_sin/cos/tan_*(a)` |
| `fmax(a,b)` | `lm2_max_*(a,b)` | `asin/acos/atan(a)` | `lm2_asin/acos/atan_*(a)` |

*Replace `*` with type suffix (`f64`, `f32`, `i64`, `i32`, `i16`, `i8`, `u64`, `u32`, `u16`, `u8`)*

**Example - Before & After:**
```c
// ❌ WRONG
double dist(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1, dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

// ✅ CORRECT
double dist(double x1, double y1, double x2, double y2) {
    double dx = lm2_sub_f64(x2, x1), dy = lm2_sub_f64(y2, y1);
    return lm2_sqrt_f64(lm2_add_f64(lm2_mul_f64(dx, dx), lm2_mul_f64(dy, dy)));
}
```

**Assertions:**
- `LM2_ASSERT(expr)` - Always active (null checks, bounds, preconditions)
- `LM2_ASSERT_UNSAFE(expr)` - Debug only (overflow/underflow/div-by-zero)

**Exceptions (only these files can use standard C operators):**
- `lm2_safe_ops.c` - Low-level safe operation implementations
- Direct wrappers like `lm2_sin_f64(a) { return sin(a); }`

---

## Type-Generic Programming

**10 Supported Types:** f64 (double), f32 (float), i64, i32, i16, i8, u64, u32, u16, u8

**How it works:** `_LM2_GENERIC` macro dispatches at compile-time (C11 `_Generic` or C++17 templates) with zero runtime cost.

**CRITICAL PATTERN: Define Helper Macros Once, Use for All Functions**

**1. Define Helper Macro** (once, at top of header):
```c
#define _LM2_DEFINE_BINARY_OP(name)                    \
  LM2_API double name##_f64(double a, double b);       \
  LM2_API float name##_f32(float a, float b);          \
  LM2_API int64_t name##_i64(int64_t a, int64_t b);    \
  LM2_API int32_t name##_i32(int32_t a, int32_t b);    \
  LM2_API int16_t name##_i16(int16_t a, int16_t b);    \
  LM2_API int8_t name##_i8(int8_t a, int8_t b);        \
  LM2_API uint64_t name##_u64(uint64_t a, uint64_t b); \
  LM2_API uint32_t name##_u32(uint32_t a, uint32_t b); \
  LM2_API uint16_t name##_u16(uint16_t a, uint16_t b); \
  LM2_API uint8_t name##_u8(uint8_t a, uint8_t b);
```

**2. Use Helper for Declarations**:
```c
_LM2_DEFINE_BINARY_OP(lm2_min);
_LM2_DEFINE_BINARY_OP(lm2_max);
_LM2_DEFINE_BINARY_OP(lm2_mod);
```

**3. Add Generic Macros** (before `LM2_HEADER_END`):
```c
#ifndef LM2_NO_GENERICS
  #define lm2_min(...) _LM2_GENERIC(lm2_min, __VA_ARGS__)
  #define lm2_max(...) _LM2_GENERIC(lm2_max, __VA_ARGS__)
#endif
```

**4. Implement All 10 Variants** (in `.c` file):
```c
LM2_API double lm2_min_f64(double a, double b) { return (a < b) ? a : b; }
LM2_API float lm2_min_f32(float a, float b) { return (a < b) ? a : b; }
// ... all 10 types
```

**Real Example from `lm2_safe_ops.h`:**
```c
_LM2_DEFINE_SAFE_OP(lm2_add);
_LM2_DEFINE_SAFE_OP(lm2_sub);
_LM2_DEFINE_SAFE_OP(lm2_mul);
_LM2_DEFINE_SAFE_OP(lm2_div);
```

**Key Rules:**
- First argument determines type dispatch
- Always use `LM2_API` prefix
- Implement all 10 variants
- Use correct type literals (`3.14f` for float, `3.14` for double, `10ULL` for uint64_t)

---

## Adding New Functions

**Decision Tree - Module Selection:**
1. Arithmetic (+, -, *, /) → `lm2_safe_ops.h/c`
2. Scalar operations (sqrt, pow, floor, min, max) → `lm2_scalar.h/c`
3. Trigonometry (sin, cos, atan2) → `lm2_trigonometry.h/c`
4. Vectors (2D/3D/4D) → `lm2_vector2/3/4.h/c`
5. Easing/noise/hash/triangles/edges/bezier → respective module
6. New category → Create `lm2_<category>.h/c`

**Adding to Existing Module:**
1. Check for existing helper macro (e.g., `_LM2_DEFINE_BINARY_OP`)
2. If exists: use it. If not: create one first
3. Add declarations using helper macro
4. Add generic macro before `LM2_HEADER_END`
5. Implement all 10 variants in `.c` file

**Creating New Module:**
```c
// include/lm2/lm2_new_category.h
#pragma once
#include "lm2_base.h"
#include "lm2_safe_ops.h"
#include "lm2_generic.h"

LM2_HEADER_BEGIN;

// Define helper macro
#define _LM2_DEFINE_NEW_OP(name)  /* ... all 10 types ... */

// Use helper
_LM2_DEFINE_NEW_OP(lm2_func1);
_LM2_DEFINE_NEW_OP(lm2_func2);

// Generics
#ifndef LM2_NO_GENERICS
  #define lm2_func1(...) _LM2_GENERIC(lm2_func1, __VA_ARGS__)
#endif

LM2_HEADER_END;
```

Then add to `lm2.h`, `CMakeLists.txt`, and implement in `src/lm2_new_category.c`.

**Integrating Third-Party Dependencies:**
When adding external dependencies (libraries, frameworks), follow the Google Test integration pattern in CMakeLists.txt:
- Use `FetchContent_Declare` to specify the dependency source
- Use `FetchContent_MakeAvailable` to download and configure the dependency
- Link against the dependency targets using `target_link_libraries`
- Keep dependencies isolated and don't expose them in public headers if possible

---

## Implementation Checklist

**Before Starting:**
- [ ] Identified correct module
- [ ] Reviewed similar existing functions
- [ ] Determined all 10 type variants needed

**Header File (.h):**
- [ ] Used or created helper macro for declarations
- [ ] All 10 type variants declared (_f64, _f32, _i64, _i32, _i16, _i8, _u64, _u32, _u16, _u8)
- [ ] Added generic macro in `#ifndef LM2_NO_GENERICS` block before `LM2_HEADER_END`

**Implementation File (.c):**
- [ ] Included required headers (`lm2_safe_ops.h`, `lm2_scalar.h`, etc.)
- [ ] All functions have `LM2_API` prefix
- [ ] Implemented all 10 type variants
- [ ] Used libmath2 functions internally (NO standard C operators except in `lm2_safe_ops.c` or direct wrappers)
- [ ] Type suffixes match (f64 calls f64, f32 calls f32, etc.)
- [ ] No memory allocation (`malloc`/`calloc`/`realloc`/`free`)
- [ ] Used `LM2_ASSERT` for preconditions, `LM2_ASSERT_UNSAFE` for arithmetic safety

**Verification:**
- [ ] Code compiles without warnings
- [ ] Follows existing patterns
- [ ] Updated AGENTS.md if new patterns introduced

---

## Quick Reference: Common Patterns

### Pattern: Helper Macro Usage

**Step 1: Define helper macro once**
```c
#define _LM2_DEFINE_BINARY_OP(name)                    \
  LM2_API double name##_f64(double a, double b);       \
  LM2_API float name##_f32(float a, float b);          \
  LM2_API int64_t name##_i64(int64_t a, int64_t b);    \
  LM2_API int32_t name##_i32(int32_t a, int32_t b);    \
  LM2_API int16_t name##_i16(int16_t a, int16_t b);    \
  LM2_API int8_t name##_i8(int8_t a, int8_t b);        \
  LM2_API uint64_t name##_u64(uint64_t a, uint64_t b); \
  LM2_API uint32_t name##_u32(uint32_t a, uint32_t b); \
  LM2_API uint16_t name##_u16(uint16_t a, uint16_t b); \
  LM2_API uint8_t name##_u8(uint8_t a, uint8_t b);

_LM2_DEFINE_BINARY_OP(lm2_min);
_LM2_DEFINE_BINARY_OP(lm2_max);

#ifndef LM2_NO_GENERICS
  #define lm2_min(...) _LM2_GENERIC(lm2_min, __VA_ARGS__)
  #define lm2_max(...) _LM2_GENERIC(lm2_max, __VA_ARGS__)
#endif
```

**Step 2: Implement (manually or with implementation macros)**
```c
LM2_API double lm2_min_f64(double a, double b) { return (a < b) ? a : b; }
LM2_API float lm2_min_f32(float a, float b) { return (a < b) ? a : b; }
// ... all 10 types
```

**For vectors, use macro-based implementation:**
```c
_LM2_IMPL_V2_ALL_OPS(lm2_v2f64, double, f64)  // Generates all vector ops
```

---

## Summary

**Key Principles:**
1. **Always use libmath2 functions** - Never standard C operators
2. **Use helper macros** - Define once, use for all functions
3. **Implement all 10 types** - f64, f32, i64, i32, i16, i8, u64, u32, u16, u8
4. **Never allocate memory** - Caller manages memory
5. **Type suffixes must match** - f64 → f64, f32 → f32, etc.

**Helper Macro Pattern:**
1. Define helper (e.g., `_LM2_DEFINE_BINARY_OP`)
2. Use for all functions with that signature
3. Add generic dispatcher per function
4. Implement all 10 variants

**When in doubt:** Follow `lm2_safe_ops.h/c`, `lm2_vector2.h/c`, or `lm2_scalar.h/c` patterns.

**Don't create examples or tests unless specifically requested by the user.**


