---
layout: default
title: Bezier Curves
---

# Bezier Curves

## Overview

Linear, quadratic, and cubic Bezier curve evaluation in 2D, 3D, and 4D. Includes first and second derivatives (velocity/acceleration), curve splitting via De Casteljau's algorithm, and arc length approximation.

## Why Use This?

Bezier curves are used for smooth paths, animation curves, font rendering, vector graphics, camera tracks, and UI transitions.

## Functions

All functions available in `_f64` and `_f32` variants. Suffix `2`, `3`, `4` indicates dimensionality.

### Curve Evaluation

#### Linear Bezier (2 control points)

`B(t) = (1-t)*P0 + t*P1`

| Function | Description |
|----------|-------------|
| `lm2_bezier_linear2_f32(p0, p1, t)` | 2D linear Bezier |
| `lm2_bezier_linear3_f32(p0, p1, t)` | 3D linear Bezier |
| `lm2_bezier_linear4_f32(p0, p1, t)` | 4D linear Bezier |

#### Quadratic Bezier (3 control points)

`B(t) = (1-t)^2*P0 + 2*(1-t)*t*P1 + t^2*P2`

| Function | Description |
|----------|-------------|
| `lm2_bezier_quadratic2_f32(p0, p1, p2, t)` | 2D quadratic |
| `lm2_bezier_quadratic3_f32(p0, p1, p2, t)` | 3D quadratic |
| `lm2_bezier_quadratic4_f32(p0, p1, p2, t)` | 4D quadratic |

#### Cubic Bezier (4 control points)

`B(t) = (1-t)^3*P0 + 3*(1-t)^2*t*P1 + 3*(1-t)*t^2*P2 + t^3*P3`

| Function | Description |
|----------|-------------|
| `lm2_bezier_cubic2_f32(p0, p1, p2, p3, t)` | 2D cubic |
| `lm2_bezier_cubic3_f32(p0, p1, p2, p3, t)` | 3D cubic |
| `lm2_bezier_cubic4_f32(p0, p1, p2, p3, t)` | 4D cubic |

### Derivatives

#### First Derivative (Velocity)

| Function | Description |
|----------|-------------|
| `lm2_bezier_quadratic_derivative2_f32(p0, p1, p2, t)` | 2D quadratic velocity |
| `lm2_bezier_quadratic_derivative3_f32(p0, p1, p2, t)` | 3D quadratic velocity |
| `lm2_bezier_cubic_derivative2_f32(p0, p1, p2, p3, t)` | 2D cubic velocity |
| `lm2_bezier_cubic_derivative3_f32(p0, p1, p2, p3, t)` | 3D cubic velocity |

#### Second Derivative (Acceleration)

| Function | Description |
|----------|-------------|
| `lm2_bezier_cubic_second_derivative2_f32(p0, p1, p2, p3, t)` | 2D cubic acceleration |
| `lm2_bezier_cubic_second_derivative3_f32(p0, p1, p2, p3, t)` | 3D cubic acceleration |

### Splitting

Split a cubic Bezier at parameter `t` into two cubic curves using De Casteljau's algorithm.

**Signature:**
```c
void lm2_bezier_cubic_split2_f32(
    lm2_v2_f32 p0, lm2_v2_f32 p1, lm2_v2_f32 p2, lm2_v2_f32 p3,
    float t,
    lm2_v2_f32* left_p0, lm2_v2_f32* left_p1, lm2_v2_f32* left_p2, lm2_v2_f32* left_p3,
    lm2_v2_f32* right_p0, lm2_v2_f32* right_p1, lm2_v2_f32* right_p2, lm2_v2_f32* right_p3
);
```

Also available in 3D (`_split3_`) and 4D (`_split4_`).

### Arc Length

Approximate arc length of a cubic Bezier curve using segment subdivision.

**Signature:** `float lm2_bezier_cubic_length2_f32(lm2_v2_f32 p0, lm2_v2_f32 p1, lm2_v2_f32 p2, lm2_v2_f32 p3, int segments)`

**Parameters:**
- `segments` — Number of segments for approximation (higher = more accurate)

## Example

```c
lm2_v2_f32 p0 = lm2_v2_make_f32(0, 0);
lm2_v2_f32 p1 = lm2_v2_make_f32(0, 10);
lm2_v2_f32 p2 = lm2_v2_make_f32(10, 10);
lm2_v2_f32 p3 = lm2_v2_make_f32(10, 0);

// Evaluate curve at midpoint
lm2_v2_f32 mid = lm2_bezier_cubic2_f32(p0, p1, p2, p3, 0.5f);

// Get velocity at midpoint
lm2_v2_f32 vel = lm2_bezier_cubic_derivative2_f32(p0, p1, p2, p3, 0.5f);

// Approximate arc length
float length = lm2_bezier_cubic_length2_f32(p0, p1, p2, p3, 100);
```
