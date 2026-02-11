---
layout: default
title: Easings
---

# Easing Functions

## Overview

30 easing functions for animation and tweening, covering all standard easing curves. Each takes a normalized time `t` in [0, 1] and returns the eased value.

## Why Use This?

Easing functions add natural-feeling motion to animations, UI transitions, camera movements, and procedural effects.

## Easing Families

Each family has three variants: `_in` (accelerate), `_out` (decelerate), `_in_out` (both).

| Family | Functions |
|--------|-----------|
| Linear | `ease_linear_f32(t)` |
| Sine | `ease_sin_in_f32`, `ease_sin_out_f32`, `ease_sin_in_out_f32` |
| Quadratic | `ease_quad_in_f32`, `ease_quad_out_f32`, `ease_quad_in_out_f32` |
| Cubic | `ease_cubic_in_f32`, `ease_cubic_out_f32`, `ease_cubic_in_out_f32` |
| Quartic | `ease_quart_in_f32`, `ease_quart_out_f32`, `ease_quart_in_out_f32` |
| Quintic | `ease_quint_in_f32`, `ease_quint_out_f32`, `ease_quint_in_out_f32` |
| Exponential | `ease_exp_in_f32`, `ease_exp_out_f32`, `ease_exp_in_out_f32` |
| Circular | `ease_circ_in_f32`, `ease_circ_out_f32`, `ease_circ_in_out_f32` |
| Back | `ease_back_in_f32`, `ease_back_out_f32`, `ease_back_in_out_f32` |
| Elastic | `ease_elastic_in_f32`, `ease_elastic_out_f32`, `ease_elastic_in_out_f32` |
| Bounce | `ease_bounce_in_f32`, `ease_bounce_out_f32`, `ease_bounce_in_out_f32` |

All functions also available in `_f64` variants.

## Generic Easing

Use the `easing` enum with the generic function to select easing at runtime:

```c
float result = lm2_ease_f32(EASING_BOUNCE_OUT, t);
```

### Enum Values

```c
EASING_LINEAR, EASING_SIN_IN, EASING_SIN_OUT, EASING_SIN_IN_OUT,
EASING_QUAD_IN, EASING_QUAD_OUT, EASING_QUAD_IN_OUT,
EASING_CUB_IN, EASING_CUB_OUT, EASING_CUB_IN_OUT,
EASING_QUART_IN, EASING_QUART_OUT, EASING_QUART_IN_OUT,
EASING_QUINT_IN, EASING_QUINT_OUT, EASING_QUINT_IN_OUT,
EASING_EXP_IN, EASING_EXP_OUT, EASING_EXP_IN_OUT,
EASING_CIRC_IN, EASING_CIRC_OUT, EASING_CIRC_IN_OUT,
EASING_BACK_IN, EASING_BACK_OUT, EASING_BACK_IN_OUT,
EASING_ELASTIC_IN, EASING_ELASTIC_OUT, EASING_ELASTIC_IN_OUT,
EASING_BOUNCE_IN, EASING_BOUNCE_OUT, EASING_BOUNCE_IN_OUT
```

### Helper

`lm2_easing_to_string(easing)` — Convert enum to human-readable string.

## Example

```c
// Animate a UI element sliding in
float t = elapsed / duration;  // 0 to 1
float eased_t = ease_cubic_out_f32(t);
float x = lm2_lerp_f32(start_x, eased_t, end_x);

// Or use the generic version for configurable easing
easing curve = EASING_ELASTIC_OUT;
float eased = lm2_ease_f32(curve, t);
```
