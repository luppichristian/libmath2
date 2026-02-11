---
layout: default
title: Geometry 3D
---

# 3D Geometry

## Overview

3D geometric primitives including spheres, axis-aligned bounding boxes, capsules, edges, planes, and triangles, with raycasting support.

## Why Use This?

These primitives are used for 3D physics, collision detection, spatial partitioning, picking, and level geometry.

## Shapes

### Sphere

A sphere defined by center point and radius. See `lm2_sphere.h`.

**Types:** `lm2_sphere_f64`, `lm2_sphere_f32`

### AABB3

3D axis-aligned bounding box. See `lm2_aabb3.h`.

### Capsule3

A 3D capsule defined by two endpoints and a radius. See `lm2_capsule3.h`.

### Edge3

A 3D line segment defined by two endpoints. See `lm2_edge3.h`.

### Plane3

A 3D plane defined by normal and distance. See `lm2_plane3.h`.

### Triangle3

A 3D triangle with construction and property functions. See `lm2_triangle3.h`.

Additional triangle geometry functions in `lm2_triangle3_geometry.h`.

### Shape3

A generic 3D shape container. See `lm2_shape3.h`.

## Raycasting

`lm2_raycast3.h` provides ray-shape intersection queries for 3D shapes.

## Example

```c
#include <lm2/geometry3d/lm2_sphere.h>

lm2_sphere_f32 s = { .center = lm2_v3_zero_f32(), .radius = 10.0f };
```
