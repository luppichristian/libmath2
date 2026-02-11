---
layout: default
title: Trigonometry
---

# Trigonometry

## Overview

Trigonometric functions, angle conversions, angle wrapping, and angular interpolation. All angle parameters are in radians unless noted.

## Why Use This?

Game and graphics code constantly works with angles for rotation, field of view, arc calculations, and smooth angular interpolation.

## Functions

### Basic Trig

| Function | Description |
|----------|-------------|
| `lm2_cos_f32(angle_rad)` | Cosine |
| `lm2_sin_f32(angle_rad)` | Sine |
| `lm2_tan_f32(angle_rad)` | Tangent |
| `lm2_acos_f32(value)` | Inverse cosine |
| `lm2_asin_f32(value)` | Inverse sine |
| `lm2_atan_f32(value)` | Inverse tangent |
| `lm2_atan2_f32(y, x)` | Two-argument inverse tangent |

### Conversions

| Function | Description |
|----------|-------------|
| `lm2_deg_to_rad_f32(degrees)` | Degrees to radians |
| `lm2_rad_to_deg_f32(radians)` | Radians to degrees |

### Angle Operations (Radians)

| Function | Description |
|----------|-------------|
| `lm2_wrap_rad_f32(angle)` | Wrap angle to [-PI, PI] |
| `lm2_shortest_rad_f32(from, to)` | Shortest angular distance in [-PI, PI] |
| `lm2_lerp_rad_f32(a, t, b)` | Interpolate angles using shortest path |

### Angle Operations (Degrees)

| Function | Description |
|----------|-------------|
| `lm2_wrap_deg_f32(angle)` | Wrap angle to [-180, 180] |
| `lm2_shortest_deg_f32(from, to)` | Shortest angular distance in [-180, 180] |
| `lm2_lerp_deg_f32(a, t, b)` | Interpolate angles using shortest path |

All functions are available in `_f64` and `_f32` variants.

## Constants

| Constant | Value | Description |
|----------|-------|-------------|
| `LM2_PI_F32` | 3.14159... | PI |
| `LM2_2PI_F32` | 6.28318... | 2 * PI |
| `LM2_HPI_F32` | 1.57079... | PI / 2 |
| `LM2_RAD_TO_DEG_F32` | 57.2957... | Radians-to-degrees multiplier |
| `LM2_DEG_TO_RAD_F32` | 0.01745... | Degrees-to-radians multiplier |
| `LM2_EULER_F32` | 0.57721... | Euler-Mascheroni constant |
| `LM2_SQRT2_F32` | 1.41421... | Square root of 2 |
| `LM2_E_F32` | 2.71828... | Euler's number |

All constants also available with `_F64` suffix.

## Example

```c
float angle_deg = 270.0f;
float angle_rad = lm2_deg_to_rad_f32(angle_deg);
float wrapped = lm2_wrap_deg_f32(angle_deg); // -90

// Smoothly interpolate between two angles
float from = lm2_deg_to_rad_f32(350.0f);
float to   = lm2_deg_to_rad_f32(10.0f);
float mid  = lm2_lerp_rad_f32(from, 0.5f, to);  // goes through 0, not 180
```
