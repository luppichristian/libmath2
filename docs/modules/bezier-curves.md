# Bezier Curves

## Overview

Linear, quadratic, and cubic Bezier curve evaluation in 2D, 3D, and 4D. Includes first and second derivatives (velocity/acceleration), curve splitting via De Casteljau's algorithm, and arc length approximation.

## Why Use This?

Bezier curves are used for smooth paths, animation curves, font rendering, vector graphics, camera tracks, and UI transitions.

## Functions

All functions are available in `_f64` and `_f32` variants. Suffix `2`, `3`, `4` indicates dimensionality. Control points and results use the caller's coordinate space and units; no coordinate-system conversion is applied.

Calculations use [safe arithmetic](safe-ops.md), so extreme or subnormal intermediate results can assert even for finite inputs. `t` is not clamped. The interval `[0, 1]` traces the curve from its first to its last control point; values outside it evaluate the polynomial extension. Derivatives are with respect to `t`, are not normalized, and are velocity or acceleration in physical time only when the appropriate time derivatives of `t` are accounted for.

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
| `lm2_bezier_quadratic_derivative4_f32(p0, p1, p2, t)` | 4D quadratic velocity |
| `lm2_bezier_cubic_derivative2_f32(p0, p1, p2, p3, t)` | 2D cubic velocity |
| `lm2_bezier_cubic_derivative3_f32(p0, p1, p2, p3, t)` | 3D cubic velocity |
| `lm2_bezier_cubic_derivative4_f32(p0, p1, p2, p3, t)` | 4D cubic velocity |

#### Second Derivative (Acceleration)

| Function | Description |
|----------|-------------|
| `lm2_bezier_cubic_second_derivative2_f32(p0, p1, p2, p3, t)` | 2D cubic acceleration |
| `lm2_bezier_cubic_second_derivative3_f32(p0, p1, p2, p3, t)` | 3D cubic acceleration |
| `lm2_bezier_cubic_second_derivative4_f32(p0, p1, p2, p3, t)` | 4D cubic acceleration |

### Splitting

Split a cubic Bezier at parameter `t` into two cubic curves using De Casteljau's algorithm. For `t` in `[0, 1]`, the left covers the original interval `[0, t]` and the right covers `[t, 1]`; each is reparameterized to `[0, 1]` and their shared endpoint is `B(t)`. All eight output pointers must be non-null and distinct; none are optional. The parameter is not clamped.

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

Approximate the arc length of a cubic Bezier by summing Euclidean distances between uniformly spaced samples in parameter `t`. This is a polygonal approximation, not adaptive subdivision; it has no stated error bound.

| Function | Description |
|----------|-------------|
| `lm2_bezier_cubic_length2_f32(p0, p1, p2, p3, segments)` | 2D cubic arc length |
| `lm2_bezier_cubic_length3_f32(p0, p1, p2, p3, segments)` | 3D cubic arc length |
| `lm2_bezier_cubic_length4_f32(p0, p1, p2, p3, segments)` | 4D cubic arc length |

**Parameters:**
- `segments` — Number of line segments. Values `0 < segments < INT_MAX` sample from `t = 0` through `t = 1`; zero or negative values return zero. `INT_MAX` overflows the loop counter after its final iteration. Larger values generally improve the approximation.

All arc length functions also available in `_f64` variants.

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
