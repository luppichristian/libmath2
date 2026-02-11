
# Project Details

**Name**: libmath2

**Short Name**: lm2

**Github**: https://github.com/luppichristian/libmath2

**Languages**: C (library implementation) and C++ (google unit tests)

**Build System**: CMake

**Theme**: Math library

# Quick Query Guide for LLMs

**ALWAYS check YAML files first** when users ask about module contents:

- **"List functions in module X"** → Read `/agent/modules/<module>.yml`
- **"What modules exist?"** → Read `/agent/modules.yml`
- **"What types does module X have?"** → Read `/agent/modules/<module>.yml`

The YAML metadata is designed for fast LLM queries. Only read C headers when you need:
- Function signatures/parameters
- Implementation details
- Comments/documentation

**Example workflow:**
```
User: "list all functions for lm2_vector2"
You: Read /agent/modules/lm2_vector2.yml → Return the functions list
```

# Directory Structure

- `/include` - Public API headers (user-facing)
- `/src` - Implementation files (internal)
- `/tests` - Unit tests (GoogleTest, C++)
- `/docs` - User documentation
- `/agent` - LLM structure metadata (YML files)

# Code Style

- **Formatting**: Follow `.clang-format` strictly
- **Naming**: All identifiers use `lower_snake_case`
- **Type Suffix**: Types do NOT use `_t` suffix (unlike Linux/POSIX convention)

# Naming Conventions

## Prefix
All public identifiers use the `lm2_` prefix.

## Structure
`lm2_<type>_<action>_<primitive>`

- **type**: The data structure or domain (e.g., `vec2`, `quat`, `aabb2`)
- **action**: The operation (e.g., `add`, `normalize`, `intersect`)
- **primitive**: Type specialization suffix (if generic)

## Primitive Type Suffixes
`f32`, `f64`, `i8`, `i16`, `i32`, `i64`, `u8`, `u16`, `u32`, `u64`

Always placed **at the end** of identifiers.

## Examples
```c
// Types
typedef struct lm2_vec2_f32 {} lm2_vec2_f32;
typedef struct lm2_vec2_f64 {} lm2_vec2_f64;

// Type-related functions (type is first parameter)
lm2_list_add_f32(lm2_list_f32 list, float val);
lm2_vec2_normalize_f64(lm2_vec2_f64 v);

// Generic functions
lm2_lerp_f32(float a, float b, float t);
lm2_clamp_f64(double x, double min, double max);
```

# Module Organization

A **module** consists of:
1. Public header: `/include/lm2/<category>/<module>.h`
2. Implementation: `/src/<category>/<module>.c`
3. Unit tests: `/tests/<category>/test_<module>.cpp`
4. Metadata: `/agent/modules/<module>.yml`

All public headers are included in `/include/lm2.h`.

## Categories
- `geometry2d` - 2D shapes, collisions, raycasting
- `geometry3d` - 3D shapes, collisions, raycasting
- `matrices` - Matrix operations (3x2, 3x3, 4x4)
- `misc` - Utilities (easings, noise, quaternions, bezier, hash)
- `ranges` - Range/interval operations
- `scalar` - Scalar math (trig, safe ops)
- `vectors` - Vector operations (vec2, vec3, vec4)

**Example**: `lm2_easings` module in `misc` category:
- `/include/lm2/misc/lm2_easings.h`
- `/src/misc/lm2_easings.c`
- `/tests/misc/test_easings.cpp`

# YML Metadata Structure

**Purpose**: Fast LLM queries of library structure without parsing C headers.

## Files

### `/agent/modules.yml`
Index of all modules organized by category.

```yml
scalar:
  - lm2_safe_ops
  - lm2_scalar
  - lm2_trigonometry
misc:
  - lm2_easings
  - lm2_quaternion
```

### `/agent/modules/<module>.yml`
Complete API surface for each module (types + functions).

```yml
category: misc
types:
  - lm2_quat_f32
  - lm2_quat_f64
functions:
  - lm2_quat_identity_f32
  - lm2_quat_identity_f64
  - lm2_quat_from_axis_angle_f32
  - lm2_quat_from_axis_angle_f64
```

## Rules
- **Source**: Public headers only (`/include/**/*.h`)
- **Completeness**: Every public type and function must be listed
- **Synchronization**: Update immediately when headers change

# Editing

## General Principles

- **Don't Repeat Yourself (DRY)**: Integrate modules according to their utility. Add missing functionality to existing modules rather than creating duplicates.
- **Respect Codebase Structure**: Follow the established directory layout and naming conventions strictly.
- **Maintain Code Style**: All changes must follow `.clang-format` and project naming conventions.

## Required Tasks for Changes

### Adding New Functionality
1. Implement the function/type in the appropriate `.c` file under `/src/`
2. Add the public declaration to the corresponding header in `/include/`
3. Update `/include/lm2.h` to include the header if it's a new module
4. **Write unit tests** in the corresponding `.cpp` file under `/tests/`
5. Update the YML structure:
   - Add the module to `/agent/modules.yml` if it's new
   - Update or create `/agent/modules/<module_name>.yml` with all public types and functions

### Refactoring Function Signatures
1. Update the function declaration in the public header (`/include/`)
2. Update the function definition in the implementation (`/src/`)
3. Update all call sites across the entire codebase
4. Update corresponding unit tests (`/tests/`)
5. Update the module's YML file in `/agent/modules/`

### Adding New Modules
1. Create public header: `/include/lm2/<category>/<module_name>.h`
2. Create implementation: `/src/<category>/<module_name>.c`
3. Create unit tests: `/tests/<category>/test_<module_name>.cpp`
4. Add include to `/include/lm2.h`
5. Add module to `/agent/modules.yml` under appropriate category
6. Create `/agent/modules/<module_name>.yml` with all public types and functions

## YML Structure Synchronization

The YML files in `/agent/` **must always reflect the current state** of public headers:
- Every public type must be listed
- Every public function must be listed
- Removals from headers must be reflected in YML files
- Updates happen immediately with code changes, not as a separate step