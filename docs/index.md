# libmath2

A comprehensive C/C++ mathematics library for 2D/3D vector operations, matrix transformations, quaternion rotations, collision detection, and more.

## Overview

libmath2 provides a complete set of mathematical primitives for graphics, game development, and physics simulations. Vectors and ranges support floating-point and signed and unsigned integer types; matrices, cameras, and many geometric operations use f32 and f64. The API uses consistent naming conventions and supports C and C++.

See [Getting Started](getting-started.md) for installation and usage instructions.

## Quick Start

```bash
cmake -B build
cmake --build build
```

```c
#include <lm2.h>

int main(void) {
    lm2_v3_f32 pos = lm2_v3_make_f32(1.0f, 2.0f, 3.0f);
    lm2_v3_f32 dir = lm2_v3_norm_f32(pos);
    float len = lm2_v3_length_f32(pos);
    (void)dir;
    (void)len;
    return 0;
}
```

## Modules

| Module | Description |
|--------|-------------|
| [Vectors](modules/vectors.md) | 2D, 3D, and 4D vector types with full arithmetic and utility operations |
| [Vector Specifics](modules/vector-specifics.md) | Dot/cross products, length, distance, normalize, angle, rotation, reflection, projection |
| [Matrices](modules/matrices.md) | 3x2, 3x3, and 4x4 transformation matrices |
| [Scalar](modules/scalar.md) | Scalar math: rounding, clamping, interpolation, power, sqrt |
| [Trigonometry](modules/trigonometry.md) | Trig functions with angle wrapping and interpolation |
| [Safe Ops](modules/safe-ops.md) | Overflow-checked arithmetic for all numeric types |
| [Ranges](modules/ranges.md) | 2D, 3D, and 4D axis-aligned bounding boxes |
| [Geometry 2D](modules/geometry2d.md) | 2D shapes: circles, AABBs, capsules, edges, planes, polygons, triangles |
| [Geometry 3D](modules/geometry3d.md) | 3D shapes: spheres, AABBs, capsules, edges, planes, triangles |
| [Cameras](modules/cameras.md) | 2D orthographic and 3D perspective/orthographic camera types with view matrix and space transform helpers |
| [Quaternions](modules/quaternions.md) | Rotation quaternions with SLERP, Euler, and axis-angle conversions |
| [Bezier Curves](modules/bezier-curves.md) | Linear, quadratic, and cubic Bezier evaluation, derivatives, splitting |
| [Easings](modules/easings.md) | 31 easing functions for animation and tweening |
| [Noise](modules/noise.md) | Perlin and Voronoi noise generation |
| [Hash](modules/hash.md) | Non-cryptographic hash functions and FNV-1a |
| [Extensions](modules/extensions.md) | C11 generics, C++ overloads, and operator overloads |

## Naming Convention

Most type-specialized functions follow the pattern:

```
lm2_<module>_<operation>_<type>
```

For example:
- `lm2_v3_add_f32` — Add two 3D float vectors
- `lm2_m4x4_inverse_f64` — Invert a 4x4 double matrix
- `lm2_quat_slerp_f32` — Spherical interpolation between float quaternions