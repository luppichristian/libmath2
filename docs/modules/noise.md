# Noise

## Overview

Deterministic procedural noise in 2D and 3D. Coordinates are positions in a unit grid selected by the caller; scale them before calling to control spatial frequency. The functions have no seed parameter.

## Why Use This?

Noise functions are essential for procedural terrain, texture generation, particle effects, cloud rendering, and organic-looking randomness.

## Functions

### Perlin Noise

Gradient noise with a fixed permutation table. Values vary smoothly between grid points and are zero at integer lattice points.

| Function | Description |
|----------|-------------|
| `lm2_perlin2_f32(x, y)` | 2D Perlin noise |
| `lm2_perlin3_f32(x, y, z)` | 3D Perlin noise |

**Returns:** Value in [-1, 1].

### Voronoi Noise

Cell-based noise with one deterministic hash-derived feature point per unit cell. The result is the nonnegative Euclidean distance to the nearest feature point, measured in grid units; it is not a cell ID.

| Function | Description |
|----------|-------------|
| `lm2_voronoi2_f32(x, y)` | 2D Voronoi noise |
| `lm2_voronoi3_f32(x, y, z)` | 3D Voronoi noise |

**Returns:** Euclidean distance to nearest feature point.

All functions also available in `_f64` variants.

Coordinates must be finite. Perlin repeats every 256 cells; Voronoi's cell
hash repeats every 2^32 cells. Floating-point rounding limits which fractional
coordinates remain representable far from the origin. Voronoi computes feature distances in local cell coordinates and searches through the second ring of cells. Generated values can differ from earlier versions because of rounding or because a closer feature was previously missed.

## Example

```c
// Generate a terrain heightmap
for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
        float h = lm2_perlin2_f32(x * 0.01f, y * 0.01f);
        heightmap[y * width + x] = h;
    }
}
```
