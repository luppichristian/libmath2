# libmath2

A comprehensive C/C++ mathematics library for 2D/3D vector operations, matrix transformations, quaternion rotations, collision detection, and more.

Designed for graphics programming, game development, and physics simulations, libmath2 provides a complete set of mathematical primitives with support for multiple numeric types (f64, f32, i64, i32, i16, i8, u64, u32, u16, u8) and first-class C/C++ interoperability.

## Features

> **Note for contributors**: this list must be kept up to date when modules are added or removed.

- **Vectors** — 2D, 3D, and 4D vector types with arithmetic, interpolation, rounding, and comparison operations across 10 numeric types
- **Matrices** — 3x2, 3x3, and 4x4 matrix types for 2D/3D transformations and projections
- **Quaternions** — Rotation representation with SLERP/NLERP interpolation, Euler/axis-angle conversions
- **Cameras** — 2D camera (pan, zoom, rotate, world↔screen) and 3D camera (perspective/orthographic, look-at, orbit, NDC conversions)
- **Ranges** — 2D, 3D, and 4D axis-aligned bounding boxes with containment, overlap, union, and intersection tests
- **2D Geometry** — Circles, AABBs, capsules, edges, planes, polygons, triangles, raycasting, and collision manifolds
- **3D Geometry** — Spheres, AABBs, capsules, edges, planes, triangles, and raycasting
- **Scalar Math** — Floor, ceil, round, clamp, lerp, smoothstep, and safe arithmetic with overflow detection
- **Trigonometry** — Trig functions with angle wrapping, shortest-path interpolation in radians and degrees
- **Bezier Curves** — Linear, quadratic, and cubic evaluation with derivatives, splitting, and arc length
- **Easing Functions** — 30 easing curves (sin, quad, cubic, quart, quint, exp, circ, back, elastic, bounce)
- **Noise** — Perlin and Voronoi noise in 2D and 3D
- **Hashing** — Non-cryptographic hash functions for all numeric types plus FNV-1a for arbitrary buffers
- **C/C++ Extensions** — C11 `_Generic` macros, C++ function overloads, and operator overloads (+, -, *, /, [], etc.)

## Requirements

- CMake 3.19+
- C11 compiler
- C++20 compiler (for tests and C++ extensions)

### Dependencies

Fetched automatically via CMake FetchContent:

- [cute_c2](https://github.com/RandyGaul/cute_headers) — 2D collision detection
- [GoogleTest 1.14.0](https://github.com/google/googletest) — Unit testing (build-time only)

### Build Options

| Option | Default | Description |
|--------|---------|-------------|
| `LM2_BUILD_SHARED` | `OFF` | Build as shared library |
| `LM2_BUILD_TESTS` | `ON` | Build test suite |
| `LM2_GTEST_FETCH` | `ON` | Auto-fetch GoogleTest if not found |

### Compile-Time Defines

| Define | Description |
|--------|-------------|
| `LM2_UNSAFE` | Disable overflow/underflow assertions in safe ops for performance |
| `LM2_NO_CPP_OPERATORS` | Disable C++ operator overloads for all types |
| `LM2_NO_GENERICS` | Disable C11 `_Generic` macros and C++ function overloads |
| `LM2_ENABLE_UNPREFIXED_NAMES` | Enable unprefixed names (e.g. v2 instead of lm2_v2) |

## Documentation

See the [docs](https://luppichristian.github.io/libmath2/) directory for comprehensive API documentation and usage patterns.

## License

MIT License - see [LICENSE.md](LICENSE.md)
