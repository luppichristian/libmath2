# libmath2

[![Language](https://img.shields.io/badge/language-C%20%2F%20C%2B%2B-00599C)](https://github.com/luppichristian/libmath2)
[![Docs](https://img.shields.io/badge/docs-Markdown-blue)](docs/index.md)
[![CI](https://img.shields.io/github/actions/workflow/status/luppichristian/libmath2/ci.yml?branch=main&label=ci)](https://github.com/luppichristian/libmath2/actions/workflows/ci.yml)
[![License](https://img.shields.io/badge/license-MIT-green)](LICENSE.md)

A header-only C/C++ mathematics library for 2D/3D vector operations, matrix transformations, quaternion rotations, collision detection, and more.

Designed for graphics programming, game development, and physics simulations, libmath2 provides a complete set of mathematical primitives with support for multiple numeric types (f64, f32, i64, i32, i16, i8, u64, u32, u16, u8) and first-class C/C++ interoperability.

## Features

- **Vectors** — 2D, 3D, and 4D vectors with arithmetic and comparisons across 10 numeric types, plus floating-point interpolation and rounding
- **Matrices** — 3x2, 3x3, and 4x4 matrix types for 2D/3D transformations and projections
- **Quaternions** — Rotation representation with SLERP/NLERP interpolation, Euler/axis-angle conversions
- **Cameras** — 2D camera (pan, zoom, rotate, world↔screen) and 3D camera (perspective/orthographic, look-at, orbit, NDC conversions)
- **Ranges** — 2D, 3D, and 4D axis-aligned bounding boxes with containment, overlap, union, and intersection tests
- **2D Geometry** — Circles, AABBs, capsules, edges, planes, polygons, triangles, raycasting, and collision manifolds
- **3D Geometry** — Spheres, AABBs, capsules, edges, planes, triangles, and raycasting
- **Scalar Math** — Floor, ceil, round, clamp, lerp, smoothstep, and safe arithmetic with overflow detection
- **Trigonometry** — Trig functions with angle wrapping, shortest-path interpolation in radians and degrees
- **Bezier Curves** — Linear, quadratic, and cubic evaluation with derivatives, splitting, and arc length
- **Easing Functions** — 31 easing curves (sin, quad, cubic, quart, quint, exp, circ, back, elastic, bounce)
- **Noise** — Perlin and Voronoi noise in 2D and 3D
- **Hashing** — Non-cryptographic hash functions for all numeric types plus FNV-1a for arbitrary buffers
- **Constants** — Typed `f32`/`f64` constants for π, 2π, half-π, rad↔deg conversion factors, √2, e, and the Euler–Mascheroni constant
- **C/C++ Extensions** — C11 `_Generic` macros, C++ function overloads, and operator overloads (+, -, *, /, [], etc.)

## Usage

Add the repository's `include/` directory to your include path, then include
libmath2:

```c
#include <lm2.h>

int main(void) {
    lm2_v3_f32 v = lm2_v3_make_f32(1.0f, 2.0f, 3.0f);
    return lm2_v3_length_f32(v) > 0.0f ? 0 : 1;
}
```

To use only specific modules, include their headers instead. Each module also
includes the dependencies it needs:

```c
#include <lm2/vectors/lm2_vector2.h>

int main(void) {
    lm2_v2_f32 position = lm2_v2_make_f32(1.0f, 2.0f);
    return position.x == 1.0f ? 0 : 1;
}
```

`<lm2.h>` includes every module and enables the language extensions by default.
Individual module headers provide their suffixed C API; see
[Extensions](docs/modules/extensions.md) for generic functions and operators.

The library requires a C11 compiler or a C++20 compiler for its C++ extensions.
Some platforms also require linking the system math library (for example, `-lm`).
The 2D collision backend, [cute_c2](https://github.com/RandyGaul/cute_headers),
is included in `include/`.

To build and run the tests, see [Getting Started](docs/getting-started.md).

### Compile-Time Defines

| Define | Description |
|--------|-------------|
| `LM2_UNSAFE` | Disable overflow/underflow assertions in safe ops for performance |
| `LM2_NO_CPP_OPERATORS` | Disable C++ operator overloads for all types |
| `LM2_NO_GENERICS` | Disable C11 `_Generic` macros and C++ function overloads |
| `LM2_ENABLE_UNPREFIXED_NAMES` | Enable unprefixed aliases (e.g. `v2_f32` for `lm2_v2_f32`) |
| `LM2_NO_IMPLEMENTATION` | Don't include implementations of defined functions |

## Documentation

See the [documentation](docs/index.md) for API reference and usage examples.

## License

MIT License - see [LICENSE.md](LICENSE.md)
