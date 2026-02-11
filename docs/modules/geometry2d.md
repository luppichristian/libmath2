---
layout: default
title: Geometry 2D
---

# 2D Geometry

## Overview

2D geometric primitives including circles, axis-aligned bounding boxes, capsules, edges, planes, polygons, and triangles. Also includes raycasting and collision manifold types for 2D collision detection.

## Why Use This?

These primitives are the building blocks for 2D physics engines, collision detection, spatial queries, and computational geometry.

## Shapes

### Circle

A circle defined by center point and radius.

**Types:** `lm2_circle_f64`, `lm2_circle_f32`, `lm2_circle` (default = f32)

**Structure:**
```c
typedef struct lm2_circle_f32 {
    lm2_v2_f32 center;
    float radius;
} lm2_circle_f32;
```

**Functions:**

| Function | Description |
|----------|-------------|
| `lm2_circle_make_f32(center, radius)` | Create from center and radius |
| `lm2_circle_make_coords_f32(x, y, radius)` | Create from coordinates |
| `lm2_circle_unit_f32()` | Unit circle at origin |
| `lm2_circle_area_f32(c)` | Area |
| `lm2_circle_circumference_f32(c)` | Circumference |
| `lm2_circle_diameter_f32(c)` | Diameter |
| `lm2_circle_contains_point_f32(c, point)` | Point-in-circle test |
| `lm2_circles_overlap_f32(a, b)` | Circle-circle overlap |
| `lm2_circle_contains_circle_f32(a, b)` | Circle containment |
| `lm2_circle_translate_f32(c, offset)` | Translate circle |
| `lm2_circle_scale_f32(c, scale)` | Scale radius |

### AABB2

2D axis-aligned bounding box. See `lm2_aabb2.h`.

### Capsule2

A 2D capsule (rounded rectangle) defined by two endpoints and a radius. See `lm2_capsule2.h`.

### Edge2

A 2D line segment defined by two endpoints. See `lm2_edge2.h`.

### Plane2

A 2D plane (line) defined by normal and distance. See `lm2_plane2.h`.

### Polygon

A 2D convex polygon. See `lm2_polygon.h`.

### Triangle2

A 2D triangle with construction and property functions. See `lm2_triangle2.h`.

Additional triangle geometry functions (area, barycentric coordinates, circumcenter, incircle, etc.) in `lm2_triangle2_geometry.h`.

### Shape2

A generic 2D shape container that can represent any of the above primitives. See `lm2_shape2.h`.

## Raycasting

`lm2_raycast2.h` provides ray-shape intersection queries for 2D shapes.

## Collision Manifolds

`lm2_manifold2.h` provides contact information for 2D collision pairs, including contact points, normals, and penetration depths.

## Example

```c
lm2_circle_f32 c = lm2_circle_make_coords_f32(0, 0, 5.0f);
lm2_v2_f32 point = lm2_v2_make_f32(3.0f, 4.0f);

bool inside = lm2_circle_contains_point_f32(c, point);  // true (dist=5, radius=5)
float area = lm2_circle_area_f32(c);                     // ~78.54
```
