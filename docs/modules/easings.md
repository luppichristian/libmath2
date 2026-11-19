# Easing Functions

## Overview

31 easing functions for animation and tweening. Each maps normalized progress `t`, normally in `[0, 1]`, to an eased interpolation factor.

## Why Use This?

Easing functions add natural-feeling motion to animations, UI transitions, camera movements, and procedural effects.

## Easing Families

Except for linear, each family has `_in`, `_out`, and `_in_out` variants, conventionally describing an accelerating start, decelerating end, or both. Back, elastic, and bounce curves can overshoot or oscillate, so their speed is not monotonic.

| Family | Functions |
|--------|-----------|
| Linear | `lm2_ease_linear_f32(t)` |
| Sine | `lm2_ease_sin_in_f32`, `lm2_ease_sin_out_f32`, `lm2_ease_sin_in_out_f32` |
| Quadratic | `lm2_ease_quad_in_f32`, `lm2_ease_quad_out_f32`, `lm2_ease_quad_in_out_f32` |
| Cubic | `lm2_ease_cubic_in_f32`, `lm2_ease_cubic_out_f32`, `lm2_ease_cubic_in_out_f32` |
| Quartic | `lm2_ease_quart_in_f32`, `lm2_ease_quart_out_f32`, `lm2_ease_quart_in_out_f32` |
| Quintic | `lm2_ease_quint_in_f32`, `lm2_ease_quint_out_f32`, `lm2_ease_quint_in_out_f32` |
| Exponential | `lm2_ease_exp_in_f32`, `lm2_ease_exp_out_f32`, `lm2_ease_exp_in_out_f32` |
| Circular | `lm2_ease_circ_in_f32`, `lm2_ease_circ_out_f32`, `lm2_ease_circ_in_out_f32` |
| Back | `lm2_ease_back_in_f32`, `lm2_ease_back_out_f32`, `lm2_ease_back_in_out_f32` |
| Elastic | `lm2_ease_elastic_in_f32`, `lm2_ease_elastic_out_f32`, `lm2_ease_elastic_in_out_f32` |
| Bounce | `lm2_ease_bounce_in_f32`, `lm2_ease_bounce_out_f32`, `lm2_ease_bounce_in_out_f32` |

All functions are also available in `_f64` variants. Neither input nor output is clamped. Back and elastic can overshoot `[0, 1]` even with `t` in that range. Inputs outside `[0, 1]` use the formulas directly; circular curves can encounter a negative square root, and safe arithmetic assertions may apply. Clamp input or output explicitly if the application requires it.

## Generic Easing

Use the `easing` enum with the generic function to select easing at runtime. `EASING_MAX` and unknown values return `t` unchanged:

```c
float result = lm2_ease_f32(EASING_BOUNCE_OUT, t);
```

### Enum Values

The `easing` enum includes the following values (in declaration order):

```c
EASING_LINEAR,
EASING_SIN_IN, EASING_SIN_OUT, EASING_SIN_IN_OUT,
EASING_CUB_IN, EASING_CUB_OUT, EASING_CUB_IN_OUT,
EASING_QUINT_IN, EASING_QUINT_OUT, EASING_QUINT_IN_OUT,
EASING_CIRC_IN, EASING_CIRC_OUT, EASING_CIRC_IN_OUT,
EASING_ELASTIC_IN, EASING_ELASTIC_OUT, EASING_ELASTIC_IN_OUT,
EASING_QUAD_IN, EASING_QUAD_OUT, EASING_QUAD_IN_OUT,
EASING_QUART_IN, EASING_QUART_OUT, EASING_QUART_IN_OUT,
EASING_EXP_IN, EASING_EXP_OUT, EASING_EXP_IN_OUT,
EASING_BACK_IN, EASING_BACK_OUT, EASING_BACK_IN_OUT,
EASING_BOUNCE_IN, EASING_BOUNCE_OUT, EASING_BOUNCE_IN_OUT,
EASING_MAX
```

### Helper

`lm2_easing_to_string(easing)` returns the named enum constant as a string literal, including `EASING_MAX`; an unknown value returns `"EASING_UNKNOWN"`.

## Example

```c
// Animate a UI element sliding in
float t = elapsed / duration;  // 0 to 1
float eased_t = lm2_ease_cubic_out_f32(t);
float x = lm2_lerp_f32(start_x, eased_t, end_x);

// Or use the generic version for configurable easing
easing curve = EASING_ELASTIC_OUT;
float eased = lm2_ease_f32(curve, t);
```
