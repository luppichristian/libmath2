---
layout: default
title: Noise
---

# Noise

## Overview

Procedural noise generation with Perlin and Voronoi noise in 2D and 3D.

## Why Use This?

Noise functions are essential for procedural terrain, texture generation, particle effects, cloud rendering, and organic-looking randomness.

## Functions

### Perlin Noise

Classic gradient noise that produces smooth, continuous values.

| Function | Description |
|----------|-------------|
| `lm2_perlin2_f32(x, y)` | 2D Perlin noise |
| `lm2_perlin3_f32(x, y, z)` | 3D Perlin noise |

**Returns:** Value in [-1, 1].

### Voronoi Noise

Cell-based noise returning the Euclidean distance to the nearest feature point.

| Function | Description |
|----------|-------------|
| `lm2_voronoi2_f32(x, y)` | 2D Voronoi noise |
| `lm2_voronoi3_f32(x, y, z)` | 3D Voronoi noise |

**Returns:** Euclidean distance to nearest feature point.

All functions also available in `_f64` variants.

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
