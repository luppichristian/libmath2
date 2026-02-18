/*
MIT License

Copyright (c) 2026 Christian Luppi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once
#if !defined(LM2_NO_GENERICS) && !defined(__cplusplus) && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L

// Scalar operations
#  define lm2_add(x, y) \
    _Generic((x), float: lm2_add_f32, double: lm2_add_f64, int8_t: lm2_add_i8, int16_t: lm2_add_i16, int32_t: lm2_add_i32, int64_t: lm2_add_i64, uint8_t: lm2_add_u8, uint16_t: lm2_add_u16, uint32_t: lm2_add_u32, uint64_t: lm2_add_u64)(x, y)
#  define lm2_sub(x, y) \
    _Generic((x), float: lm2_sub_f32, double: lm2_sub_f64, int8_t: lm2_sub_i8, int16_t: lm2_sub_i16, int32_t: lm2_sub_i32, int64_t: lm2_sub_i64, uint8_t: lm2_sub_u8, uint16_t: lm2_sub_u16, uint32_t: lm2_sub_u32, uint64_t: lm2_sub_u64)(x, y)
#  define lm2_mul(x, y) \
    _Generic((x), float: lm2_mul_f32, double: lm2_mul_f64, int8_t: lm2_mul_i8, int16_t: lm2_mul_i16, int32_t: lm2_mul_i32, int64_t: lm2_mul_i64, uint8_t: lm2_mul_u8, uint16_t: lm2_mul_u16, uint32_t: lm2_mul_u32, uint64_t: lm2_mul_u64)(x, y)
#  define lm2_div(x, y) \
    _Generic((x), float: lm2_div_f32, double: lm2_div_f64, int8_t: lm2_div_i8, int16_t: lm2_div_i16, int32_t: lm2_div_i32, int64_t: lm2_div_i64, uint8_t: lm2_div_u8, uint16_t: lm2_div_u16, uint32_t: lm2_div_u32, uint64_t: lm2_div_u64)(x, y)
#  define lm2_mod(x, y) \
    _Generic((x), float: lm2_mod_f32, double: lm2_mod_f64, int8_t: lm2_mod_i8, int16_t: lm2_mod_i16, int32_t: lm2_mod_i32, int64_t: lm2_mod_i64, uint8_t: lm2_mod_u8, uint16_t: lm2_mod_u16, uint32_t: lm2_mod_u32, uint64_t: lm2_mod_u64)(x, y)
#  define lm2_neg(x) \
    _Generic((x), float: lm2_neg_f32, double: lm2_neg_f64, int8_t: lm2_neg_i8, int16_t: lm2_neg_i16, int32_t: lm2_neg_i32, int64_t: lm2_neg_i64)(x)
#  define lm2_floor(x) \
    _Generic((x), float: lm2_floor_f32, double: lm2_floor_f64)(x)
#  define lm2_floor_multiple(x, y) \
    _Generic((x), float: lm2_floor_multiple_f32, double: lm2_floor_multiple_f64)(x, y)
#  define lm2_ceil(x) \
    _Generic((x), float: lm2_ceil_f32, double: lm2_ceil_f64)(x)
#  define lm2_ceil_multiple(x, y) \
    _Generic((x), float: lm2_ceil_multiple_f32, double: lm2_ceil_multiple_f64)(x, y)
#  define lm2_round(x) \
    _Generic((x), float: lm2_round_f32, double: lm2_round_f64)(x)
#  define lm2_round_multiple(x, y) \
    _Generic((x), float: lm2_round_multiple_f32, double: lm2_round_multiple_f64)(x, y)
#  define lm2_trunc(x) \
    _Generic((x), float: lm2_trunc_f32, double: lm2_trunc_f64)(x)
#  define lm2_trunc_multiple(x, y) \
    _Generic((x), float: lm2_trunc_multiple_f32, double: lm2_trunc_multiple_f64)(x, y)
#  define lm2_abs(x) \
    _Generic((x), float: lm2_abs_f32, double: lm2_abs_f64, int8_t: lm2_abs_i8, int16_t: lm2_abs_i16, int32_t: lm2_abs_i32, int64_t: lm2_abs_i64)(x)
#  define lm2_sign(x) \
    _Generic((x), float: lm2_sign_f32, double: lm2_sign_f64, int8_t: lm2_sign_i8, int16_t: lm2_sign_i16, int32_t: lm2_sign_i32, int64_t: lm2_sign_i64)(x)
#  define lm2_sign0(x) \
    _Generic((x), float: lm2_sign0_f32, double: lm2_sign0_f64, int8_t: lm2_sign0_i8, int16_t: lm2_sign0_i16, int32_t: lm2_sign0_i32, int64_t: lm2_sign0_i64)(x)
#  define lm2_min(x, y) \
    _Generic((x), float: lm2_min_f32, double: lm2_min_f64, int8_t: lm2_min_i8, int16_t: lm2_min_i16, int32_t: lm2_min_i32, int64_t: lm2_min_i64, uint8_t: lm2_min_u8, uint16_t: lm2_min_u16, uint32_t: lm2_min_u32, uint64_t: lm2_min_u64)(x, y)
#  define lm2_min_abs(x, y) \
    _Generic((x), float: lm2_min_abs_f32, double: lm2_min_abs_f64, int8_t: lm2_min_abs_i8, int16_t: lm2_min_abs_i16, int32_t: lm2_min_abs_i32, int64_t: lm2_min_abs_i64)(x, y)
#  define lm2_max(x, y) \
    _Generic((x), float: lm2_max_f32, double: lm2_max_f64, int8_t: lm2_max_i8, int16_t: lm2_max_i16, int32_t: lm2_max_i32, int64_t: lm2_max_i64, uint8_t: lm2_max_u8, uint16_t: lm2_max_u16, uint32_t: lm2_max_u32, uint64_t: lm2_max_u64)(x, y)
#  define lm2_max_abs(x, y) \
    _Generic((x), float: lm2_max_abs_f32, double: lm2_max_abs_f64, int8_t: lm2_max_abs_i8, int16_t: lm2_max_abs_i16, int32_t: lm2_max_abs_i32, int64_t: lm2_max_abs_i64)(x, y)
#  define lm2_clamp(x, y, z) \
    _Generic((x), float: lm2_clamp_f32, double: lm2_clamp_f64, int8_t: lm2_clamp_i8, int16_t: lm2_clamp_i16, int32_t: lm2_clamp_i32, int64_t: lm2_clamp_i64, uint8_t: lm2_clamp_u8, uint16_t: lm2_clamp_u16, uint32_t: lm2_clamp_u32, uint64_t: lm2_clamp_u64)(x, y, z)
#  define lm2_saturate(x) \
    _Generic((x), float: lm2_saturate_f32, double: lm2_saturate_f64)(x)
#  define lm2_lerp(x, y, t) \
    _Generic((x), float: lm2_lerp_f32, double: lm2_lerp_f64)(x, y, t)
#  define lm2_smoothstep(x, y, t) \
    _Generic((x), float: lm2_smoothstep_f32, double: lm2_smoothstep_f64)(x, y, t)
#  define lm2_alpha(x, y, a) \
    _Generic((x), float: lm2_alpha_f32, double: lm2_alpha_f64)(x, y, a)
#  define lm2_fract(x) \
    _Generic((x), float: lm2_fract_f32, double: lm2_fract_f64)(x)
#  define lm2_pow(x, y) \
    _Generic((x), float: lm2_pow_f32, double: lm2_pow_f64)(x, y)
#  define lm2_sqrt(x) \
    _Generic((x), float: lm2_sqrt_f32, double: lm2_sqrt_f64)(x)
#  define lm2_cos(x) \
    _Generic((x), float: lm2_cos_f32, double: lm2_cos_f64)(x)
#  define lm2_sin(x) \
    _Generic((x), float: lm2_sin_f32, double: lm2_sin_f64)(x)
#  define lm2_tan(x) \
    _Generic((x), float: lm2_tan_f32, double: lm2_tan_f64)(x)
#  define lm2_acos(x) \
    _Generic((x), float: lm2_acos_f32, double: lm2_acos_f64)(x)
#  define lm2_asin(x) \
    _Generic((x), float: lm2_asin_f32, double: lm2_asin_f64)(x)
#  define lm2_atan(x) \
    _Generic((x), float: lm2_atan_f32, double: lm2_atan_f64)(x)
#  define lm2_atan2(y, x) \
    _Generic((y), float: lm2_atan2_f32, double: lm2_atan2_f64)(y, x)
#  define lm2_deg_to_rad(x) \
    _Generic((x), float: lm2_deg_to_rad_f32, double: lm2_deg_to_rad_f64)(x)
#  define lm2_rad_to_deg(x) \
    _Generic((x), float: lm2_rad_to_deg_f32, double: lm2_rad_to_deg_f64)(x)
#  define lm2_wrap_rad(x) \
    _Generic((x), float: lm2_wrap_rad_f32, double: lm2_wrap_rad_f64)(x)
#  define lm2_shortest_rad(x, y) \
    _Generic((x), float: lm2_shortest_rad_f32, double: lm2_shortest_rad_f64)(x, y)
#  define lm2_lerp_rad(x, y, t) \
    _Generic((x), float: lm2_lerp_rad_f32, double: lm2_lerp_rad_f64)(x, y, t)
#  define lm2_wrap_deg(x) \
    _Generic((x), float: lm2_wrap_deg_f32, double: lm2_wrap_deg_f64)(x)
#  define lm2_shortest_deg(x, y) \
    _Generic((x), float: lm2_shortest_deg_f32, double: lm2_shortest_deg_f64)(x, y)
#  define lm2_lerp_deg(x, y, t) \
    _Generic((x), float: lm2_lerp_deg_f32, double: lm2_lerp_deg_f64)(x, y, t)
#  define lm2_hash(x) \
    _Generic((x), float: lm2_hash_f32, double: lm2_hash_f64, int8_t: lm2_hash_i8, int16_t: lm2_hash_i16, int32_t: lm2_hash_i32, int64_t: lm2_hash_i64, uint8_t: lm2_hash_u8, uint16_t: lm2_hash_u16, uint32_t: lm2_hash_u32, uint64_t: lm2_hash_u64)(x)
#  define lm2_perlin2(x, y) \
    _Generic((x), float: lm2_perlin2_f32, double: lm2_perlin2_f64)(x, y)
#  define lm2_perlin3(x, y, z) \
    _Generic((x), float: lm2_perlin3_f32, double: lm2_perlin3_f64)(x, y, z)
#  define lm2_voronoi2(x, y) \
    _Generic((x), float: lm2_voronoi2_f32, double: lm2_voronoi2_f64)(x, y)
#  define lm2_voronoi3(x, y, z) \
    _Generic((x), float: lm2_voronoi3_f32, double: lm2_voronoi3_f64)(x, y, z)
#  define lm2_bezier_linear2(p0, p1, t) \
    _Generic((t), float: lm2_bezier_linear2_f32, double: lm2_bezier_linear2_f64)(p0, p1, t)
#  define lm2_bezier_linear3(p0, p1, t) \
    _Generic((t), float: lm2_bezier_linear3_f32, double: lm2_bezier_linear3_f64)(p0, p1, t)
#  define lm2_bezier_linear4(p0, p1, t) \
    _Generic((t), float: lm2_bezier_linear4_f32, double: lm2_bezier_linear4_f64)(p0, p1, t)
#  define lm2_bezier_quadratic2(p0, p1, p2, t) \
    _Generic((t), float: lm2_bezier_quadratic2_f32, double: lm2_bezier_quadratic2_f64)(p0, p1, p2, t)
#  define lm2_bezier_quadratic3(p0, p1, p2, t) \
    _Generic((t), float: lm2_bezier_quadratic3_f32, double: lm2_bezier_quadratic3_f64)(p0, p1, p2, t)
#  define lm2_bezier_quadratic4(p0, p1, p2, t) \
    _Generic((t), float: lm2_bezier_quadratic4_f32, double: lm2_bezier_quadratic4_f64)(p0, p1, p2, t)
#  define lm2_bezier_cubic2(p0, p1, p2, p3, t) \
    _Generic((t), float: lm2_bezier_cubic2_f32, double: lm2_bezier_cubic2_f64)(p0, p1, p2, p3, t)
#  define lm2_bezier_cubic3(p0, p1, p2, p3, t) \
    _Generic((t), float: lm2_bezier_cubic3_f32, double: lm2_bezier_cubic3_f64)(p0, p1, p2, p3, t)
#  define lm2_bezier_cubic4(p0, p1, p2, p3, t) \
    _Generic((t), float: lm2_bezier_cubic4_f32, double: lm2_bezier_cubic4_f64)(p0, p1, p2, p3, t)
#  define lm2_bezier_quadratic_derivative2(p0, p1, p2, t) \
    _Generic((t), float: lm2_bezier_quadratic_derivative2_f32, double: lm2_bezier_quadratic_derivative2_f64)(p0, p1, p2, t)
#  define lm2_bezier_quadratic_derivative3(p0, p1, p2, t) \
    _Generic((t), float: lm2_bezier_quadratic_derivative3_f32, double: lm2_bezier_quadratic_derivative3_f64)(p0, p1, p2, t)
#  define lm2_bezier_quadratic_derivative4(p0, p1, p2, t) \
    _Generic((t), float: lm2_bezier_quadratic_derivative4_f32, double: lm2_bezier_quadratic_derivative4_f64)(p0, p1, p2, t)
#  define lm2_bezier_cubic_derivative2(p0, p1, p2, p3, t) \
    _Generic((t), float: lm2_bezier_cubic_derivative2_f32, double: lm2_bezier_cubic_derivative2_f64)(p0, p1, p2, p3, t)
#  define lm2_bezier_cubic_derivative3(p0, p1, p2, p3, t) \
    _Generic((t), float: lm2_bezier_cubic_derivative3_f32, double: lm2_bezier_cubic_derivative3_f64)(p0, p1, p2, p3, t)
#  define lm2_bezier_cubic_derivative4(p0, p1, p2, p3, t) \
    _Generic((t), float: lm2_bezier_cubic_derivative4_f32, double: lm2_bezier_cubic_derivative4_f64)(p0, p1, p2, p3, t)
#  define lm2_bezier_cubic_second_derivative2(p0, p1, p2, p3, t) \
    _Generic((t), float: lm2_bezier_cubic_second_derivative2_f32, double: lm2_bezier_cubic_second_derivative2_f64)(p0, p1, p2, p3, t)
#  define lm2_bezier_cubic_second_derivative3(p0, p1, p2, p3, t) \
    _Generic((t), float: lm2_bezier_cubic_second_derivative3_f32, double: lm2_bezier_cubic_second_derivative3_f64)(p0, p1, p2, p3, t)
#  define lm2_bezier_cubic_second_derivative4(p0, p1, p2, p3, t) \
    _Generic((t), float: lm2_bezier_cubic_second_derivative4_f32, double: lm2_bezier_cubic_second_derivative4_f64)(p0, p1, p2, p3, t)
#  define lm2_bezier_cubic_split2(p0, p1, p2, p3, t, l0, l1, l2, l3, r0, r1, r2, r3) \
    _Generic((t), float: lm2_bezier_cubic_split2_f32, double: lm2_bezier_cubic_split2_f64)(p0, p1, p2, p3, t, l0, l1, l2, l3, r0, r1, r2, r3)
#  define lm2_bezier_cubic_split3(p0, p1, p2, p3, t, l0, l1, l2, l3, r0, r1, r2, r3) \
    _Generic((t), float: lm2_bezier_cubic_split3_f32, double: lm2_bezier_cubic_split3_f64)(p0, p1, p2, p3, t, l0, l1, l2, l3, r0, r1, r2, r3)
#  define lm2_bezier_cubic_split4(p0, p1, p2, p3, t, l0, l1, l2, l3, r0, r1, r2, r3) \
    _Generic((t), float: lm2_bezier_cubic_split4_f32, double: lm2_bezier_cubic_split4_f64)(p0, p1, p2, p3, t, l0, l1, l2, l3, r0, r1, r2, r3)
#  define lm2_bezier_cubic_length2(p0, p1, p2, p3, steps) \
    _Generic((p0), lm2_v2_f32: lm2_bezier_cubic_length2_f32, lm2_v2_f64: lm2_bezier_cubic_length2_f64)(p0, p1, p2, p3, steps)
#  define lm2_bezier_cubic_length3(p0, p1, p2, p3, steps) \
    _Generic((p0), lm2_v3_f32: lm2_bezier_cubic_length3_f32, lm2_v3_f64: lm2_bezier_cubic_length3_f64)(p0, p1, p2, p3, steps)
#  define lm2_bezier_cubic_length4(p0, p1, p2, p3, steps) \
    _Generic((p0), lm2_v4_f32: lm2_bezier_cubic_length4_f32, lm2_v4_f64: lm2_bezier_cubic_length4_f64)(p0, p1, p2, p3, steps)
#  define ease_linear(t) \
    _Generic((t), float: ease_linear_f32, double: lm2_ease_linear_f64)(t)
#  define ease_sin_in(t) \
    _Generic((t), float: ease_sin_in_f32, double: lm2_ease_sin_in_f64)(t)
#  define ease_sin_out(t) \
    _Generic((t), float: ease_sin_out_f32, double: lm2_ease_sin_out_f64)(t)
#  define ease_sin_in_out(t) \
    _Generic((t), float: ease_sin_in_out_f32, double: lm2_ease_sin_in_out_f64)(t)
#  define ease_quad_in(t) \
    _Generic((t), float: ease_quad_in_f32, double: lm2_ease_quad_in_f64)(t)
#  define ease_quad_out(t) \
    _Generic((t), float: ease_quad_out_f32, double: lm2_ease_quad_out_f64)(t)
#  define ease_quad_in_out(t) \
    _Generic((t), float: ease_quad_in_out_f32, double: lm2_ease_quad_in_out_f64)(t)
#  define ease_cubic_in(t) \
    _Generic((t), float: ease_cubic_in_f32, double: lm2_ease_cubic_in_f64)(t)
#  define ease_cubic_out(t) \
    _Generic((t), float: ease_cubic_out_f32, double: lm2_ease_cubic_out_f64)(t)
#  define ease_cubic_in_out(t) \
    _Generic((t), float: ease_cubic_in_out_f32, double: lm2_ease_cubic_in_out_f64)(t)
#  define ease_quart_in(t) \
    _Generic((t), float: ease_quart_in_f32, double: lm2_ease_quart_in_f64)(t)
#  define ease_quart_out(t) \
    _Generic((t), float: ease_quart_out_f32, double: lm2_ease_quart_out_f64)(t)
#  define ease_quart_in_out(t) \
    _Generic((t), float: ease_quart_in_out_f32, double: lm2_ease_quart_in_out_f64)(t)
#  define ease_quint_in(t) \
    _Generic((t), float: ease_quint_in_f32, double: lm2_ease_quint_in_f64)(t)
#  define ease_quint_out(t) \
    _Generic((t), float: ease_quint_out_f32, double: lm2_ease_quint_out_f64)(t)
#  define ease_quint_in_out(t) \
    _Generic((t), float: ease_quint_in_out_f32, double: lm2_ease_quint_in_out_f64)(t)
#  define ease_exp_in(t) \
    _Generic((t), float: ease_exp_in_f32, double: lm2_ease_exp_in_f64)(t)
#  define ease_exp_out(t) \
    _Generic((t), float: ease_exp_out_f32, double: lm2_ease_exp_out_f64)(t)
#  define ease_exp_in_out(t) \
    _Generic((t), float: ease_exp_in_out_f32, double: lm2_ease_exp_in_out_f64)(t)
#  define ease_circ_in(t) \
    _Generic((t), float: ease_circ_in_f32, double: lm2_ease_circ_in_f64)(t)
#  define ease_circ_out(t) \
    _Generic((t), float: ease_circ_out_f32, double: lm2_ease_circ_out_f64)(t)
#  define ease_circ_in_out(t) \
    _Generic((t), float: ease_circ_in_out_f32, double: lm2_ease_circ_in_out_f64)(t)
#  define ease_back_in(t) \
    _Generic((t), float: ease_back_in_f32, double: lm2_ease_back_in_f64)(t)
#  define ease_back_out(t) \
    _Generic((t), float: ease_back_out_f32, double: lm2_ease_back_out_f64)(t)
#  define ease_back_in_out(t) \
    _Generic((t), float: ease_back_in_out_f32, double: lm2_ease_back_in_out_f64)(t)
#  define ease_elastic_in(t) \
    _Generic((t), float: ease_elastic_in_f32, double: lm2_ease_elastic_in_f64)(t)
#  define ease_elastic_out(t) \
    _Generic((t), float: ease_elastic_out_f32, double: lm2_ease_elastic_out_f64)(t)
#  define ease_elastic_in_out(t) \
    _Generic((t), float: ease_elastic_in_out_f32, double: lm2_ease_elastic_in_out_f64)(t)
#  define ease_bounce_in(t) \
    _Generic((t), float: ease_bounce_in_f32, double: lm2_ease_bounce_in_f64)(t)
#  define ease_bounce_out(t) \
    _Generic((t), float: ease_bounce_out_f32, double: lm2_ease_bounce_out_f64)(t)
#  define ease_bounce_in_out(t) \
    _Generic((t), float: ease_bounce_in_out_f32, double: lm2_ease_bounce_in_out_f64)(t)
#  define lm2_ease(e, t) \
    _Generic((t), float: lm2_ease_f32, double: lm2_ease_f64)(e, t)

// Vector2 operations
#  define lm2_v2_add(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_add_f64, lm2_v2_f32: lm2_v2_add_f32, lm2_v2_i64: lm2_v2_add_i64, lm2_v2_i32: lm2_v2_add_i32, lm2_v2_i16: lm2_v2_add_i16, lm2_v2_i8: lm2_v2_add_i8, lm2_v2_u64: lm2_v2_add_u64, lm2_v2_u32: lm2_v2_add_u32, lm2_v2_u16: lm2_v2_add_u16, lm2_v2_u8: lm2_v2_add_u8)(a, b)
#  define lm2_v2_sub(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_sub_f64, lm2_v2_f32: lm2_v2_sub_f32, lm2_v2_i64: lm2_v2_sub_i64, lm2_v2_i32: lm2_v2_sub_i32, lm2_v2_i16: lm2_v2_sub_i16, lm2_v2_i8: lm2_v2_sub_i8, lm2_v2_u64: lm2_v2_sub_u64, lm2_v2_u32: lm2_v2_sub_u32, lm2_v2_u16: lm2_v2_sub_u16, lm2_v2_u8: lm2_v2_sub_u8)(a, b)
#  define lm2_v2_mul(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_mul_f64, lm2_v2_f32: lm2_v2_mul_f32, lm2_v2_i64: lm2_v2_mul_i64, lm2_v2_i32: lm2_v2_mul_i32, lm2_v2_i16: lm2_v2_mul_i16, lm2_v2_i8: lm2_v2_mul_i8, lm2_v2_u64: lm2_v2_mul_u64, lm2_v2_u32: lm2_v2_mul_u32, lm2_v2_u16: lm2_v2_mul_u16, lm2_v2_u8: lm2_v2_mul_u8)(a, b)
#  define lm2_v2_div(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_div_f64, lm2_v2_f32: lm2_v2_div_f32, lm2_v2_i64: lm2_v2_div_i64, lm2_v2_i32: lm2_v2_div_i32, lm2_v2_i16: lm2_v2_div_i16, lm2_v2_i8: lm2_v2_div_i8, lm2_v2_u64: lm2_v2_div_u64, lm2_v2_u32: lm2_v2_div_u32, lm2_v2_u16: lm2_v2_div_u16, lm2_v2_u8: lm2_v2_div_u8)(a, b)
#  define lm2_v2_add_s(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_add_s_f64, lm2_v2_f32: lm2_v2_add_s_f32, lm2_v2_i64: lm2_v2_add_s_i64, lm2_v2_i32: lm2_v2_add_s_i32, lm2_v2_i16: lm2_v2_add_s_i16, lm2_v2_i8: lm2_v2_add_s_i8, lm2_v2_u64: lm2_v2_add_s_u64, lm2_v2_u32: lm2_v2_add_s_u32, lm2_v2_u16: lm2_v2_add_s_u16, lm2_v2_u8: lm2_v2_add_s_u8)(a, b)
#  define lm2_v2_sub_s(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_sub_s_f64, lm2_v2_f32: lm2_v2_sub_s_f32, lm2_v2_i64: lm2_v2_sub_s_i64, lm2_v2_i32: lm2_v2_sub_s_i32, lm2_v2_i16: lm2_v2_sub_s_i16, lm2_v2_i8: lm2_v2_sub_s_i8, lm2_v2_u64: lm2_v2_sub_s_u64, lm2_v2_u32: lm2_v2_sub_s_u32, lm2_v2_u16: lm2_v2_sub_s_u16, lm2_v2_u8: lm2_v2_sub_s_u8)(a, b)
#  define lm2_v2_mul_s(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_mul_s_f64, lm2_v2_f32: lm2_v2_mul_s_f32, lm2_v2_i64: lm2_v2_mul_s_i64, lm2_v2_i32: lm2_v2_mul_s_i32, lm2_v2_i16: lm2_v2_mul_s_i16, lm2_v2_i8: lm2_v2_mul_s_i8, lm2_v2_u64: lm2_v2_mul_s_u64, lm2_v2_u32: lm2_v2_mul_s_u32, lm2_v2_u16: lm2_v2_mul_s_u16, lm2_v2_u8: lm2_v2_mul_s_u8)(a, b)
#  define lm2_v2_div_s(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_div_s_f64, lm2_v2_f32: lm2_v2_div_s_f32, lm2_v2_i64: lm2_v2_div_s_i64, lm2_v2_i32: lm2_v2_div_s_i32, lm2_v2_i16: lm2_v2_div_s_i16, lm2_v2_i8: lm2_v2_div_s_i8, lm2_v2_u64: lm2_v2_div_s_u64, lm2_v2_u32: lm2_v2_div_s_u32, lm2_v2_u16: lm2_v2_div_s_u16, lm2_v2_u8: lm2_v2_div_s_u8)(a, b)
#  define lm2_v2_neg(a) \
    _Generic((a), lm2_v2_f64: lm2_v2_neg_f64, lm2_v2_f32: lm2_v2_neg_f32, lm2_v2_i64: lm2_v2_neg_i64, lm2_v2_i32: lm2_v2_neg_i32, lm2_v2_i16: lm2_v2_neg_i16, lm2_v2_i8: lm2_v2_neg_i8, lm2_v2_u64: lm2_v2_neg_u64)(a)
#  define lm2_v2_floor(a) \
    _Generic((a), lm2_v2_f64: lm2_v2_floor_f64, lm2_v2_f32: lm2_v2_floor_f32)(a)
#  define lm2_v2_ceil(a) \
    _Generic((a), lm2_v2_f64: lm2_v2_ceil_f64, lm2_v2_f32: lm2_v2_ceil_f32)(a)
#  define lm2_v2_round(a) \
    _Generic((a), lm2_v2_f64: lm2_v2_round_f64, lm2_v2_f32: lm2_v2_round_f32)(a)
#  define lm2_v2_trunc(a) \
    _Generic((a), lm2_v2_f64: lm2_v2_trunc_f64, lm2_v2_f32: lm2_v2_trunc_f32)(a)
#  define lm2_v2_abs(a) \
    _Generic((a), lm2_v2_f64: lm2_v2_abs_f64, lm2_v2_f32: lm2_v2_abs_f32, lm2_v2_i64: lm2_v2_abs_i64, lm2_v2_i32: lm2_v2_abs_i32, lm2_v2_i16: lm2_v2_abs_i16, lm2_v2_i8: lm2_v2_abs_i8)(a)
#  define lm2_v2_sign(a) \
    _Generic((a), lm2_v2_f64: lm2_v2_sign_f64, lm2_v2_f32: lm2_v2_sign_f32, lm2_v2_i64: lm2_v2_sign_i64, lm2_v2_i32: lm2_v2_sign_i32, lm2_v2_i16: lm2_v2_sign_i16, lm2_v2_i8: lm2_v2_sign_i8)(a)
#  define lm2_v2_sign0(a) \
    _Generic((a), lm2_v2_f64: lm2_v2_sign0_f64, lm2_v2_f32: lm2_v2_sign0_f32, lm2_v2_i64: lm2_v2_sign0_i64, lm2_v2_i32: lm2_v2_sign0_i32, lm2_v2_i16: lm2_v2_sign0_i16, lm2_v2_i8: lm2_v2_sign0_i8)(a)
#  define lm2_v2_saturate(a) \
    _Generic((a), lm2_v2_f64: lm2_v2_saturate_f64, lm2_v2_f32: lm2_v2_saturate_f32)(a)
#  define lm2_v2_fract(a) \
    _Generic((a), lm2_v2_f64: lm2_v2_fract_f64, lm2_v2_f32: lm2_v2_fract_f32)(a)
#  define lm2_v2_sqrt(a) \
    _Generic((a), lm2_v2_f64: lm2_v2_sqrt_f64, lm2_v2_f32: lm2_v2_sqrt_f32)(a)
#  define lm2_v2_floor_multiple(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_floor_multiple_f64, lm2_v2_f32: lm2_v2_floor_multiple_f32)(a, b)
#  define lm2_v2_ceil_multiple(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_ceil_multiple_f64, lm2_v2_f32: lm2_v2_ceil_multiple_f32)(a, b)
#  define lm2_v2_round_multiple(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_round_multiple_f64, lm2_v2_f32: lm2_v2_round_multiple_f32)(a, b)
#  define lm2_v2_trunc_multiple(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_trunc_multiple_f64, lm2_v2_f32: lm2_v2_trunc_multiple_f32)(a, b)
#  define lm2_v2_min(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_min_f64, lm2_v2_f32: lm2_v2_min_f32, lm2_v2_i64: lm2_v2_min_i64, lm2_v2_i32: lm2_v2_min_i32, lm2_v2_i16: lm2_v2_min_i16, lm2_v2_i8: lm2_v2_min_i8, lm2_v2_u64: lm2_v2_min_u64, lm2_v2_u32: lm2_v2_min_u32, lm2_v2_u16: lm2_v2_min_u16, lm2_v2_u8: lm2_v2_min_u8)(a, b)
#  define lm2_v2_min_abs(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_min_abs_f64, lm2_v2_f32: lm2_v2_min_abs_f32, lm2_v2_i64: lm2_v2_min_abs_i64, lm2_v2_i32: lm2_v2_min_abs_i32, lm2_v2_i16: lm2_v2_min_abs_i16, lm2_v2_i8: lm2_v2_min_abs_i8)(a, b)
#  define lm2_v2_max(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_max_f64, lm2_v2_f32: lm2_v2_max_f32, lm2_v2_i64: lm2_v2_max_i64, lm2_v2_i32: lm2_v2_max_i32, lm2_v2_i16: lm2_v2_max_i16, lm2_v2_i8: lm2_v2_max_i8, lm2_v2_u64: lm2_v2_max_u64, lm2_v2_u32: lm2_v2_max_u32, lm2_v2_u16: lm2_v2_max_u16, lm2_v2_u8: lm2_v2_max_u8)(a, b)
#  define lm2_v2_max_abs(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_max_abs_f64, lm2_v2_f32: lm2_v2_max_abs_f32, lm2_v2_i64: lm2_v2_max_abs_i64, lm2_v2_i32: lm2_v2_max_abs_i32, lm2_v2_i16: lm2_v2_max_abs_i16, lm2_v2_i8: lm2_v2_max_abs_i8)(a, b)
#  define lm2_v2_mod(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_mod_f64, lm2_v2_f32: lm2_v2_mod_f32, lm2_v2_i64: lm2_v2_mod_i64, lm2_v2_i32: lm2_v2_mod_i32, lm2_v2_i16: lm2_v2_mod_i16, lm2_v2_i8: lm2_v2_mod_i8, lm2_v2_u64: lm2_v2_mod_u64, lm2_v2_u32: lm2_v2_mod_u32, lm2_v2_u16: lm2_v2_mod_u16, lm2_v2_u8: lm2_v2_mod_u8)(a, b)
#  define lm2_v2_pow(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_pow_f64, lm2_v2_f32: lm2_v2_pow_f32)(a, b)
#  define lm2_v2_clamp(a, b, c) \
    _Generic((a), lm2_v2_f64: lm2_v2_clamp_f64, lm2_v2_f32: lm2_v2_clamp_f32, lm2_v2_i64: lm2_v2_clamp_i64, lm2_v2_i32: lm2_v2_clamp_i32, lm2_v2_i16: lm2_v2_clamp_i16, lm2_v2_i8: lm2_v2_clamp_i8, lm2_v2_u64: lm2_v2_clamp_u64, lm2_v2_u32: lm2_v2_clamp_u32, lm2_v2_u16: lm2_v2_clamp_u16, lm2_v2_u8: lm2_v2_clamp_u8)(a, b, c)
#  define lm2_v2_lerp(a, b, t) \
    _Generic((a), lm2_v2_f64: lm2_v2_lerp_f64, lm2_v2_f32: lm2_v2_lerp_f32)(a, b, t)
#  define lm2_v2_smoothstep(a, b, t) \
    _Generic((a), lm2_v2_f64: lm2_v2_smoothstep_f64, lm2_v2_f32: lm2_v2_smoothstep_f32)(a, b, t)
#  define lm2_v2_alpha(a, b, t) \
    _Generic((a), lm2_v2_f64: lm2_v2_alpha_f64, lm2_v2_f32: lm2_v2_alpha_f32)(a, b, t)
#  define lm2_v2_dot(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_dot_f64, lm2_v2_f32: lm2_v2_dot_f32, lm2_v2_i64: lm2_v2_dot_i64, lm2_v2_i32: lm2_v2_dot_i32, lm2_v2_i16: lm2_v2_dot_i16, lm2_v2_i8: lm2_v2_dot_i8)(a, b)
#  define lm2_v2_cross(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_cross_f64, lm2_v2_f32: lm2_v2_cross_f32, lm2_v2_i64: lm2_v2_cross_i64, lm2_v2_i32: lm2_v2_cross_i32, lm2_v2_i16: lm2_v2_cross_i16, lm2_v2_i8: lm2_v2_cross_i8)(a, b)
#  define lm2_v2_cross3(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_cross3_f64, lm2_v2_f32: lm2_v2_cross3_f32, lm2_v2_i64: lm2_v2_cross3_i64, lm2_v2_i32: lm2_v2_cross3_i32, lm2_v2_i16: lm2_v2_cross3_i16, lm2_v2_i8: lm2_v2_cross3_i8)(a, b)
#  define lm2_v2_length(a) \
    _Generic((a), lm2_v2_f64: lm2_v2_length_f64, lm2_v2_f32: lm2_v2_length_f32)(a)
#  define lm2_v2_length_sq(a) \
    _Generic((a), lm2_v2_f64: lm2_v2_length_sq_f64, lm2_v2_f32: lm2_v2_length_sq_f32)(a)
#  define lm2_v2_distance(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_distance_f64, lm2_v2_f32: lm2_v2_distance_f32)(a, b)
#  define lm2_v2_distance_sq(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_distance_sq_f64, lm2_v2_f32: lm2_v2_distance_sq_f32)(a, b)
#  define lm2_v2_normalize(a) \
    _Generic((a), lm2_v2_f64: lm2_v2_normalize_f64, lm2_v2_f32: lm2_v2_normalize_f32)(a)
#  define lm2_v2_angle(a, b) \
    _Generic((a), lm2_v2_f64: lm2_v2_angle_f64, lm2_v2_f32: lm2_v2_angle_f32)(a, b)
#  define lm2_v2_rotate(v, a) \
    _Generic((v), lm2_v2_f64: lm2_v2_rotate_f64, lm2_v2_f32: lm2_v2_rotate_f32)(v, a)
#  define lm2_v2_rotate_around(v, c, a) \
    _Generic((v), lm2_v2_f64: lm2_v2_rotate_around_f64, lm2_v2_f32: lm2_v2_rotate_around_f32)(v, c, a)
#  define lm2_v2_perp_ccw(a) \
    _Generic((a), lm2_v2_f64: lm2_v2_perp_ccw_f64, lm2_v2_f32: lm2_v2_perp_ccw_f32, lm2_v2_i64: lm2_v2_perp_ccw_i64, lm2_v2_i32: lm2_v2_perp_ccw_i32, lm2_v2_i16: lm2_v2_perp_ccw_i16, lm2_v2_i8: lm2_v2_perp_ccw_i8)(a)
#  define lm2_v2_perp_cw(a) \
    _Generic((a), lm2_v2_f64: lm2_v2_perp_cw_f64, lm2_v2_f32: lm2_v2_perp_cw_f32, lm2_v2_i64: lm2_v2_perp_cw_i64, lm2_v2_i32: lm2_v2_perp_cw_i32, lm2_v2_i16: lm2_v2_perp_cw_i16, lm2_v2_i8: lm2_v2_perp_cw_i8)(a)
#  define lm2_v2_reflect(v, n) \
    _Generic((v), lm2_v2_f64: lm2_v2_reflect_f64, lm2_v2_f32: lm2_v2_reflect_f32)(v, n)
#  define lm2_v2_project(v, onto) \
    _Generic((v), lm2_v2_f64: lm2_v2_project_f64, lm2_v2_f32: lm2_v2_project_f32)(v, onto)
#  define lm2_v2_upcast(v) \
    _Generic((v), lm2_v2_f64: lm2_v2_upcast_f64, lm2_v2_f32: lm2_v2_upcast_f32, lm2_v2_i64: lm2_v2_upcast_i64, lm2_v2_i32: lm2_v2_upcast_i32, lm2_v2_i16: lm2_v2_upcast_i16, lm2_v2_i8: lm2_v2_upcast_i8, lm2_v2_u64: lm2_v2_upcast_u64, lm2_v2_u32: lm2_v2_upcast_u32, lm2_v2_u16: lm2_v2_upcast_u16, lm2_v2_u8: lm2_v2_upcast_u8)(v)

// Vector3 operations
#  define lm2_v3_add(a, b) \
    _Generic((a), lm2_v3_f64: lm2_v3_add_f64, lm2_v3_f32: lm2_v3_add_f32, lm2_v3_i64: lm2_v3_add_i64, lm2_v3_i32: lm2_v3_add_i32, lm2_v3_i16: lm2_v3_add_i16, lm2_v3_i8: lm2_v3_add_i8, lm2_v3_u64: lm2_v3_add_u64, lm2_v3_u32: lm2_v3_add_u32, lm2_v3_u16: lm2_v3_add_u16, lm2_v3_u8: lm2_v3_add_u8)(a, b)
#  define lm2_v3_sub(a, b) \
    _Generic((a), lm2_v3_f64: lm2_v3_sub_f64, lm2_v3_f32: lm2_v3_sub_f32, lm2_v3_i64: lm2_v3_sub_i64, lm2_v3_i32: lm2_v3_sub_i32, lm2_v3_i16: lm2_v3_sub_i16, lm2_v3_i8: lm2_v3_sub_i8, lm2_v3_u64: lm2_v3_sub_u64, lm2_v3_u32: lm2_v3_sub_u32, lm2_v3_u16: lm2_v3_sub_u16, lm2_v3_u8: lm2_v3_sub_u8)(a, b)
#  define lm2_v3_mul(a, b) \
    _Generic((a), lm2_v3_f64: lm2_v3_mul_f64, lm2_v3_f32: lm2_v3_mul_f32, lm2_v3_i64: lm2_v3_mul_i64, lm2_v3_i32: lm2_v3_mul_i32, lm2_v3_i16: lm2_v3_mul_i16, lm2_v3_i8: lm2_v3_mul_i8, lm2_v3_u64: lm2_v3_mul_u64, lm2_v3_u32: lm2_v3_mul_u32, lm2_v3_u16: lm2_v3_mul_u16, lm2_v3_u8: lm2_v3_mul_u8)(a, b)
#  define lm2_v3_div(a, b) \
    _Generic((a), lm2_v3_f64: lm2_v3_div_f64, lm2_v3_f32: lm2_v3_div_f32, lm2_v3_i64: lm2_v3_div_i64, lm2_v3_i32: lm2_v3_div_i32, lm2_v3_i16: lm2_v3_div_i16, lm2_v3_i8: lm2_v3_div_i8, lm2_v3_u64: lm2_v3_div_u64, lm2_v3_u32: lm2_v3_div_u32, lm2_v3_u16: lm2_v3_div_u16, lm2_v3_u8: lm2_v3_div_u8)(a, b)
#  define lm2_v3_add_s(a, b) \
    _Generic((a), lm2_v3_f64: lm2_v3_add_s_f64, lm2_v3_f32: lm2_v3_add_s_f32, lm2_v3_i64: lm2_v3_add_s_i64, lm2_v3_i32: lm2_v3_add_s_i32, lm2_v3_i16: lm2_v3_add_s_i16, lm2_v3_i8: lm2_v3_add_s_i8, lm2_v3_u64: lm2_v3_add_s_u64, lm2_v3_u32: lm2_v3_add_s_u32, lm2_v3_u16: lm2_v3_add_s_u16, lm2_v3_u8: lm2_v3_add_s_u8)(a, b)
#  define lm2_v3_sub_s(a, b) \
    _Generic((a), lm2_v3_f64: lm2_v3_sub_s_f64, lm2_v3_f32: lm2_v3_sub_s_f32, lm2_v3_i64: lm2_v3_sub_s_i64, lm2_v3_i32: lm2_v3_sub_s_i32, lm2_v3_i16: lm2_v3_sub_s_i16, lm2_v3_i8: lm2_v3_sub_s_i8, lm2_v3_u64: lm2_v3_sub_s_u64, lm2_v3_u32: lm2_v3_sub_s_u32, lm2_v3_u16: lm2_v3_sub_s_u16, lm2_v3_u8: lm2_v3_sub_s_u8)(a, b)
#  define lm2_v3_mul_s(a, b) \
    _Generic((a), lm2_v3_f64: lm2_v3_mul_s_f64, lm2_v3_f32: lm2_v3_mul_s_f32, lm2_v3_i64: lm2_v3_mul_s_i64, lm2_v3_i32: lm2_v3_mul_s_i32, lm2_v3_i16: lm2_v3_mul_s_i16, lm2_v3_i8: lm2_v3_mul_s_i8, lm2_v3_u64: lm2_v3_mul_s_u64, lm2_v3_u32: lm2_v3_mul_s_u32, lm2_v3_u16: lm2_v3_mul_s_u16, lm2_v3_u8: lm2_v3_mul_s_u8)(a, b)
#  define lm2_v3_div_s(a, b) \
    _Generic((a), lm2_v3_f64: lm2_v3_div_s_f64, lm2_v3_f32: lm2_v3_div_s_f32, lm2_v3_i64: lm2_v3_div_s_i64, lm2_v3_i32: lm2_v3_div_s_i32, lm2_v3_i16: lm2_v3_div_s_i16, lm2_v3_i8: lm2_v3_div_s_i8, lm2_v3_u64: lm2_v3_div_s_u64, lm2_v3_u32: lm2_v3_div_s_u32, lm2_v3_u16: lm2_v3_div_s_u16, lm2_v3_u8: lm2_v3_div_s_u8)(a, b)
#  define lm2_v3_neg(a) \
    _Generic((a), lm2_v3_f64: lm2_v3_neg_f64, lm2_v3_f32: lm2_v3_neg_f32, lm2_v3_i64: lm2_v3_neg_i64, lm2_v3_i32: lm2_v3_neg_i32, lm2_v3_i16: lm2_v3_neg_i16, lm2_v3_i8: lm2_v3_neg_i8, lm2_v3_u64: lm2_v3_neg_u64)(a)
#  define lm2_v3_floor(a) \
    _Generic((a), lm2_v3_f64: lm2_v3_floor_f64, lm2_v3_f32: lm2_v3_floor_f32)(a)
#  define lm2_v3_ceil(a) \
    _Generic((a), lm2_v3_f64: lm2_v3_ceil_f64, lm2_v3_f32: lm2_v3_ceil_f32)(a)
#  define lm2_v3_round(a) \
    _Generic((a), lm2_v3_f64: lm2_v3_round_f64, lm2_v3_f32: lm2_v3_round_f32)(a)
#  define lm2_v3_trunc(a) \
    _Generic((a), lm2_v3_f64: lm2_v3_trunc_f64, lm2_v3_f32: lm2_v3_trunc_f32)(a)
#  define lm2_v3_abs(a) \
    _Generic((a), lm2_v3_f64: lm2_v3_abs_f64, lm2_v3_f32: lm2_v3_abs_f32, lm2_v3_i64: lm2_v3_abs_i64, lm2_v3_i32: lm2_v3_abs_i32, lm2_v3_i16: lm2_v3_abs_i16, lm2_v3_i8: lm2_v3_abs_i8)(a)
#  define lm2_v3_sign(a) \
    _Generic((a), lm2_v3_f64: lm2_v3_sign_f64, lm2_v3_f32: lm2_v3_sign_f32, lm2_v3_i64: lm2_v3_sign_i64, lm2_v3_i32: lm2_v3_sign_i32, lm2_v3_i16: lm2_v3_sign_i16, lm2_v3_i8: lm2_v3_sign_i8)(a)
#  define lm2_v3_sign0(a) \
    _Generic((a), lm2_v3_f64: lm2_v3_sign0_f64, lm2_v3_f32: lm2_v3_sign0_f32, lm2_v3_i64: lm2_v3_sign0_i64, lm2_v3_i32: lm2_v3_sign0_i32, lm2_v3_i16: lm2_v3_sign0_i16, lm2_v3_i8: lm2_v3_sign0_i8)(a)
#  define lm2_v3_saturate(a) \
    _Generic((a), lm2_v3_f64: lm2_v3_saturate_f64, lm2_v3_f32: lm2_v3_saturate_f32)(a)
#  define lm2_v3_fract(a) \
    _Generic((a), lm2_v3_f64: lm2_v3_fract_f64, lm2_v3_f32: lm2_v3_fract_f32)(a)
#  define lm2_v3_sqrt(a) \
    _Generic((a), lm2_v3_f64: lm2_v3_sqrt_f64, lm2_v3_f32: lm2_v3_sqrt_f32)(a)
#  define lm2_v3_floor_multiple(a, b) \
    _Generic((a), lm2_v3_f64: lm2_v3_floor_multiple_f64, lm2_v3_f32: lm2_v3_floor_multiple_f32)(a, b)
#  define lm2_v3_ceil_multiple(a, b) \
    _Generic((a), lm2_v3_f64: lm2_v3_ceil_multiple_f64, lm2_v3_f32: lm2_v3_ceil_multiple_f32)(a, b)
#  define lm2_v3_round_multiple(a, b) \
    _Generic((a), lm2_v3_f64: lm2_v3_round_multiple_f64, lm2_v3_f32: lm2_v3_round_multiple_f32)(a, b)
#  define lm2_v3_trunc_multiple(a, b) \
    _Generic((a), lm2_v3_f64: lm2_v3_trunc_multiple_f64, lm2_v3_f32: lm2_v3_trunc_multiple_f32)(a, b)
#  define lm2_v3_min(a, b) \
    _Generic((a), lm2_v3_f64: lm2_v3_min_f64, lm2_v3_f32: lm2_v3_min_f32, lm2_v3_i64: lm2_v3_min_i64, lm2_v3_i32: lm2_v3_min_i32, lm2_v3_i16: lm2_v3_min_i16, lm2_v3_i8: lm2_v3_min_i8, lm2_v3_u64: lm2_v3_min_u64, lm2_v3_u32: lm2_v3_min_u32, lm2_v3_u16: lm2_v3_min_u16, lm2_v3_u8: lm2_v3_min_u8)(a, b)
#  define lm2_v3_min_abs(a, b) \
    _Generic((a), lm2_v3_f64: lm2_v3_min_abs_f64, lm2_v3_f32: lm2_v3_min_abs_f32, lm2_v3_i64: lm2_v3_min_abs_i64, lm2_v3_i32: lm2_v3_min_abs_i32, lm2_v3_i16: lm2_v3_min_abs_i16, lm2_v3_i8: lm2_v3_min_abs_i8)(a, b)
#  define lm2_v3_max(a, b) \
    _Generic((a), lm2_v3_f64: lm2_v3_max_f64, lm2_v3_f32: lm2_v3_max_f32, lm2_v3_i64: lm2_v3_max_i64, lm2_v3_i32: lm2_v3_max_i32, lm2_v3_i16: lm2_v3_max_i16, lm2_v3_i8: lm2_v3_max_i8, lm2_v3_u64: lm2_v3_max_u64, lm2_v3_u32: lm2_v3_max_u32, lm2_v3_u16: lm2_v3_max_u16, lm2_v3_u8: lm2_v3_max_u8)(a, b)
#  define lm2_v3_max_abs(a, b) \
    _Generic((a), lm2_v3_f64: lm2_v3_max_abs_f64, lm2_v3_f32: lm2_v3_max_abs_f32, lm2_v3_i64: lm2_v3_max_abs_i64, lm2_v3_i32: lm2_v3_max_abs_i32, lm2_v3_i16: lm2_v3_max_abs_i16, lm2_v3_i8: lm2_v3_max_abs_i8)(a, b)
#  define lm2_v3_mod(a, b) \
    _Generic((a), lm2_v3_f64: lm2_v3_mod_f64, lm2_v3_f32: lm2_v3_mod_f32, lm2_v3_i64: lm2_v3_mod_i64, lm2_v3_i32: lm2_v3_mod_i32, lm2_v3_i16: lm2_v3_mod_i16, lm2_v3_i8: lm2_v3_mod_i8, lm2_v3_u64: lm2_v3_mod_u64, lm2_v3_u32: lm2_v3_mod_u32, lm2_v3_u16: lm2_v3_mod_u16, lm2_v3_u8: lm2_v3_mod_u8)(a, b)
#  define lm2_v3_pow(a, b) \
    _Generic((a), lm2_v3_f64: lm2_v3_pow_f64, lm2_v3_f32: lm2_v3_pow_f32)(a, b)
#  define lm2_v3_clamp(a, b, c) \
    _Generic((a), lm2_v3_f64: lm2_v3_clamp_f64, lm2_v3_f32: lm2_v3_clamp_f32, lm2_v3_i64: lm2_v3_clamp_i64, lm2_v3_i32: lm2_v3_clamp_i32, lm2_v3_i16: lm2_v3_clamp_i16, lm2_v3_i8: lm2_v3_clamp_i8, lm2_v3_u64: lm2_v3_clamp_u64, lm2_v3_u32: lm2_v3_clamp_u32, lm2_v3_u16: lm2_v3_clamp_u16, lm2_v3_u8: lm2_v3_clamp_u8)(a, b, c)
#  define lm2_v3_lerp(a, b, t) \
    _Generic((a), lm2_v3_f64: lm2_v3_lerp_f64, lm2_v3_f32: lm2_v3_lerp_f32)(a, b, t)
#  define lm2_v3_smoothstep(a, b, t) \
    _Generic((a), lm2_v3_f64: lm2_v3_smoothstep_f64, lm2_v3_f32: lm2_v3_smoothstep_f32)(a, b, t)
#  define lm2_v3_alpha(a, b, t) \
    _Generic((a), lm2_v3_f64: lm2_v3_alpha_f64, lm2_v3_f32: lm2_v3_alpha_f32)(a, b, t)
#  define lm2_v3_dot(a, b) \
    _Generic((a), lm2_v3_f64: lm2_v3_dot_f64, lm2_v3_f32: lm2_v3_dot_f32, lm2_v3_i64: lm2_v3_dot_i64, lm2_v3_i32: lm2_v3_dot_i32, lm2_v3_i16: lm2_v3_dot_i16, lm2_v3_i8: lm2_v3_dot_i8)(a, b)
#  define lm2_v3_cross(a, b) \
    _Generic((a), lm2_v3_f64: lm2_v3_cross_f64, lm2_v3_f32: lm2_v3_cross_f32, lm2_v3_i64: lm2_v3_cross_i64, lm2_v3_i32: lm2_v3_cross_i32, lm2_v3_i16: lm2_v3_cross_i16, lm2_v3_i8: lm2_v3_cross_i8)(a, b)
#  define lm2_v3_length(a) \
    _Generic((a), lm2_v3_f64: lm2_v3_length_f64, lm2_v3_f32: lm2_v3_length_f32)(a)
#  define lm2_v3_length_sq(a) \
    _Generic((a), lm2_v3_f64: lm2_v3_length_sq_f64, lm2_v3_f32: lm2_v3_length_sq_f32)(a)
#  define lm2_v3_distance(a, b) \
    _Generic((a), lm2_v3_f64: lm2_v3_distance_f64, lm2_v3_f32: lm2_v3_distance_f32)(a, b)
#  define lm2_v3_distance_sq(a, b) \
    _Generic((a), lm2_v3_f64: lm2_v3_distance_sq_f64, lm2_v3_f32: lm2_v3_distance_sq_f32)(a, b)
#  define lm2_v3_normalize(a) \
    _Generic((a), lm2_v3_f64: lm2_v3_normalize_f64, lm2_v3_f32: lm2_v3_normalize_f32)(a)
#  define lm2_v3_angle(a, b) \
    _Generic((a), lm2_v3_f64: lm2_v3_angle_f64, lm2_v3_f32: lm2_v3_angle_f32)(a, b)
#  define lm2_v3_reflect(v, n) \
    _Generic((v), lm2_v3_f64: lm2_v3_reflect_f64, lm2_v3_f32: lm2_v3_reflect_f32)(v, n)
#  define lm2_v3_project(v, onto) \
    _Generic((v), lm2_v3_f64: lm2_v3_project_f64, lm2_v3_f32: lm2_v3_project_f32)(v, onto)
#  define lm2_v3_upcast(v) \
    _Generic((v), lm2_v3_f64: lm2_v3_upcast_f64, lm2_v3_f32: lm2_v3_upcast_f32, lm2_v3_i64: lm2_v3_upcast_i64, lm2_v3_i32: lm2_v3_upcast_i32, lm2_v3_i16: lm2_v3_upcast_i16, lm2_v3_i8: lm2_v3_upcast_i8, lm2_v3_u64: lm2_v3_upcast_u64, lm2_v3_u32: lm2_v3_upcast_u32, lm2_v3_u16: lm2_v3_upcast_u16, lm2_v3_u8: lm2_v3_upcast_u8)(v)
#  define lm2_v3_downcast(v) \
    _Generic((v), lm2_v3_f64: lm2_v3_downcast_f64, lm2_v3_f32: lm2_v3_downcast_f32, lm2_v3_i64: lm2_v3_downcast_i64, lm2_v3_i32: lm2_v3_downcast_i32, lm2_v3_i16: lm2_v3_downcast_i16, lm2_v3_i8: lm2_v3_downcast_i8, lm2_v3_u64: lm2_v3_downcast_u64, lm2_v3_u32: lm2_v3_downcast_u32, lm2_v3_u16: lm2_v3_downcast_u16, lm2_v3_u8: lm2_v3_downcast_u8)(v)

// Vector4 operations
#  define lm2_v4_add(a, b) \
    _Generic((a), lm2_v4_f64: lm2_v4_add_f64, lm2_v4_f32: lm2_v4_add_f32, lm2_v4_i64: lm2_v4_add_i64, lm2_v4_i32: lm2_v4_add_i32, lm2_v4_i16: lm2_v4_add_i16, lm2_v4_i8: lm2_v4_add_i8, lm2_v4_u64: lm2_v4_add_u64, lm2_v4_u32: lm2_v4_add_u32, lm2_v4_u16: lm2_v4_add_u16, lm2_v4_u8: lm2_v4_add_u8)(a, b)
#  define lm2_v4_sub(a, b) \
    _Generic((a), lm2_v4_f64: lm2_v4_sub_f64, lm2_v4_f32: lm2_v4_sub_f32, lm2_v4_i64: lm2_v4_sub_i64, lm2_v4_i32: lm2_v4_sub_i32, lm2_v4_i16: lm2_v4_sub_i16, lm2_v4_i8: lm2_v4_sub_i8, lm2_v4_u64: lm2_v4_sub_u64, lm2_v4_u32: lm2_v4_sub_u32, lm2_v4_u16: lm2_v4_sub_u16, lm2_v4_u8: lm2_v4_sub_u8)(a, b)
#  define lm2_v4_mul(a, b) \
    _Generic((a), lm2_v4_f64: lm2_v4_mul_f64, lm2_v4_f32: lm2_v4_mul_f32, lm2_v4_i64: lm2_v4_mul_i64, lm2_v4_i32: lm2_v4_mul_i32, lm2_v4_i16: lm2_v4_mul_i16, lm2_v4_i8: lm2_v4_mul_i8, lm2_v4_u64: lm2_v4_mul_u64, lm2_v4_u32: lm2_v4_mul_u32, lm2_v4_u16: lm2_v4_mul_u16, lm2_v4_u8: lm2_v4_mul_u8)(a, b)
#  define lm2_v4_div(a, b) \
    _Generic((a), lm2_v4_f64: lm2_v4_div_f64, lm2_v4_f32: lm2_v4_div_f32, lm2_v4_i64: lm2_v4_div_i64, lm2_v4_i32: lm2_v4_div_i32, lm2_v4_i16: lm2_v4_div_i16, lm2_v4_i8: lm2_v4_div_i8, lm2_v4_u64: lm2_v4_div_u64, lm2_v4_u32: lm2_v4_div_u32, lm2_v4_u16: lm2_v4_div_u16, lm2_v4_u8: lm2_v4_div_u8)(a, b)
#  define lm2_v4_add_s(a, b) \
    _Generic((a), lm2_v4_f64: lm2_v4_add_s_f64, lm2_v4_f32: lm2_v4_add_s_f32, lm2_v4_i64: lm2_v4_add_s_i64, lm2_v4_i32: lm2_v4_add_s_i32, lm2_v4_i16: lm2_v4_add_s_i16, lm2_v4_i8: lm2_v4_add_s_i8, lm2_v4_u64: lm2_v4_add_s_u64, lm2_v4_u32: lm2_v4_add_s_u32, lm2_v4_u16: lm2_v4_add_s_u16, lm2_v4_u8: lm2_v4_add_s_u8)(a, b)
#  define lm2_v4_sub_s(a, b) \
    _Generic((a), lm2_v4_f64: lm2_v4_sub_s_f64, lm2_v4_f32: lm2_v4_sub_s_f32, lm2_v4_i64: lm2_v4_sub_s_i64, lm2_v4_i32: lm2_v4_sub_s_i32, lm2_v4_i16: lm2_v4_sub_s_i16, lm2_v4_i8: lm2_v4_sub_s_i8, lm2_v4_u64: lm2_v4_sub_s_u64, lm2_v4_u32: lm2_v4_sub_s_u32, lm2_v4_u16: lm2_v4_sub_s_u16, lm2_v4_u8: lm2_v4_sub_s_u8)(a, b)
#  define lm2_v4_mul_s(a, b) \
    _Generic((a), lm2_v4_f64: lm2_v4_mul_s_f64, lm2_v4_f32: lm2_v4_mul_s_f32, lm2_v4_i64: lm2_v4_mul_s_i64, lm2_v4_i32: lm2_v4_mul_s_i32, lm2_v4_i16: lm2_v4_mul_s_i16, lm2_v4_i8: lm2_v4_mul_s_i8, lm2_v4_u64: lm2_v4_mul_s_u64, lm2_v4_u32: lm2_v4_mul_s_u32, lm2_v4_u16: lm2_v4_mul_s_u16, lm2_v4_u8: lm2_v4_mul_s_u8)(a, b)
#  define lm2_v4_div_s(a, b) \
    _Generic((a), lm2_v4_f64: lm2_v4_div_s_f64, lm2_v4_f32: lm2_v4_div_s_f32, lm2_v4_i64: lm2_v4_div_s_i64, lm2_v4_i32: lm2_v4_div_s_i32, lm2_v4_i16: lm2_v4_div_s_i16, lm2_v4_i8: lm2_v4_div_s_i8, lm2_v4_u64: lm2_v4_div_s_u64, lm2_v4_u32: lm2_v4_div_s_u32, lm2_v4_u16: lm2_v4_div_s_u16, lm2_v4_u8: lm2_v4_div_s_u8)(a, b)
#  define lm2_v4_neg(a) \
    _Generic((a), lm2_v4_f64: lm2_v4_neg_f64, lm2_v4_f32: lm2_v4_neg_f32, lm2_v4_i64: lm2_v4_neg_i64, lm2_v4_i32: lm2_v4_neg_i32, lm2_v4_i16: lm2_v4_neg_i16, lm2_v4_i8: lm2_v4_neg_i8, lm2_v4_u8: lm2_v4_neg_u8, lm2_v4_u32: lm2_v4_neg_u32)(a)
#  define lm2_v4_floor(a) \
    _Generic((a), lm2_v4_f64: lm2_v4_floor_f64, lm2_v4_f32: lm2_v4_floor_f32)(a)
#  define lm2_v4_ceil(a) \
    _Generic((a), lm2_v4_f64: lm2_v4_ceil_f64, lm2_v4_f32: lm2_v4_ceil_f32)(a)
#  define lm2_v4_round(a) \
    _Generic((a), lm2_v4_f64: lm2_v4_round_f64, lm2_v4_f32: lm2_v4_round_f32)(a)
#  define lm2_v4_trunc(a) \
    _Generic((a), lm2_v4_f64: lm2_v4_trunc_f64, lm2_v4_f32: lm2_v4_trunc_f32)(a)
#  define lm2_v4_abs(a) \
    _Generic((a), lm2_v4_f64: lm2_v4_abs_f64, lm2_v4_f32: lm2_v4_abs_f32, lm2_v4_i64: lm2_v4_abs_i64, lm2_v4_i32: lm2_v4_abs_i32, lm2_v4_i16: lm2_v4_abs_i16, lm2_v4_i8: lm2_v4_abs_i8)(a)
#  define lm2_v4_sign(a) \
    _Generic((a), lm2_v4_f64: lm2_v4_sign_f64, lm2_v4_f32: lm2_v4_sign_f32, lm2_v4_i64: lm2_v4_sign_i64, lm2_v4_i32: lm2_v4_sign_i32, lm2_v4_i16: lm2_v4_sign_i16, lm2_v4_i8: lm2_v4_sign_i8)(a)
#  define lm2_v4_sign0(a) \
    _Generic((a), lm2_v4_f64: lm2_v4_sign0_f64, lm2_v4_f32: lm2_v4_sign0_f32, lm2_v4_i64: lm2_v4_sign0_i64, lm2_v4_i32: lm2_v4_sign0_i32, lm2_v4_i16: lm2_v4_sign0_i16, lm2_v4_i8: lm2_v4_sign0_i8)(a)
#  define lm2_v4_saturate(a) \
    _Generic((a), lm2_v4_f64: lm2_v4_saturate_f64, lm2_v4_f32: lm2_v4_saturate_f32)(a)
#  define lm2_v4_fract(a) \
    _Generic((a), lm2_v4_f64: lm2_v4_fract_f64, lm2_v4_f32: lm2_v4_fract_f32)(a)
#  define lm2_v4_sqrt(a) \
    _Generic((a), lm2_v4_f64: lm2_v4_sqrt_f64, lm2_v4_f32: lm2_v4_sqrt_f32)(a)
#  define lm2_v4_floor_multiple(a, b) \
    _Generic((a), lm2_v4_f64: lm2_v4_floor_multiple_f64, lm2_v4_f32: lm2_v4_floor_multiple_f32)(a, b)
#  define lm2_v4_ceil_multiple(a, b) \
    _Generic((a), lm2_v4_f64: lm2_v4_ceil_multiple_f64, lm2_v4_f32: lm2_v4_ceil_multiple_f32)(a, b)
#  define lm2_v4_round_multiple(a, b) \
    _Generic((a), lm2_v4_f64: lm2_v4_round_multiple_f64, lm2_v4_f32: lm2_v4_round_multiple_f32)(a, b)
#  define lm2_v4_trunc_multiple(a, b) \
    _Generic((a), lm2_v4_f64: lm2_v4_trunc_multiple_f64, lm2_v4_f32: lm2_v4_trunc_multiple_f32)(a, b)
#  define lm2_v4_min(a, b) \
    _Generic((a), lm2_v4_f64: lm2_v4_min_f64, lm2_v4_f32: lm2_v4_min_f32, lm2_v4_i64: lm2_v4_min_i64, lm2_v4_i32: lm2_v4_min_i32, lm2_v4_i16: lm2_v4_min_i16, lm2_v4_i8: lm2_v4_min_i8, lm2_v4_u64: lm2_v4_min_u64, lm2_v4_u32: lm2_v4_min_u32, lm2_v4_u16: lm2_v4_min_u16, lm2_v4_u8: lm2_v4_min_u8)(a, b)
#  define lm2_v4_min_abs(a, b) \
    _Generic((a), lm2_v4_f64: lm2_v4_min_abs_f64, lm2_v4_f32: lm2_v4_min_abs_f32, lm2_v4_i64: lm2_v4_min_abs_i64, lm2_v4_i32: lm2_v4_min_abs_i32, lm2_v4_i16: lm2_v4_min_abs_i16, lm2_v4_i8: lm2_v4_min_abs_i8)(a, b)
#  define lm2_v4_max(a, b) \
    _Generic((a), lm2_v4_f64: lm2_v4_max_f64, lm2_v4_f32: lm2_v4_max_f32, lm2_v4_i64: lm2_v4_max_i64, lm2_v4_i32: lm2_v4_max_i32, lm2_v4_i16: lm2_v4_max_i16, lm2_v4_i8: lm2_v4_max_i8, lm2_v4_u64: lm2_v4_max_u64, lm2_v4_u32: lm2_v4_max_u32, lm2_v4_u16: lm2_v4_max_u16, lm2_v4_u8: lm2_v4_max_u8)(a, b)
#  define lm2_v4_max_abs(a, b) \
    _Generic((a), lm2_v4_f64: lm2_v4_max_abs_f64, lm2_v4_f32: lm2_v4_max_abs_f32, lm2_v4_i64: lm2_v4_max_abs_i64, lm2_v4_i32: lm2_v4_max_abs_i32, lm2_v4_i16: lm2_v4_max_abs_i16, lm2_v4_i8: lm2_v4_max_abs_i8)(a, b)
#  define lm2_v4_mod(a, b) \
    _Generic((a), lm2_v4_f64: lm2_v4_mod_f64, lm2_v4_f32: lm2_v4_mod_f32, lm2_v4_i64: lm2_v4_mod_i64, lm2_v4_i32: lm2_v4_mod_i32, lm2_v4_i16: lm2_v4_mod_i16, lm2_v4_i8: lm2_v4_mod_i8, lm2_v4_u64: lm2_v4_mod_u64, lm2_v4_u32: lm2_v4_mod_u32, lm2_v4_u16: lm2_v4_mod_u16, lm2_v4_u8: lm2_v4_mod_u8)(a, b)
#  define lm2_v4_pow(a, b) \
    _Generic((a), lm2_v4_f64: lm2_v4_pow_f64, lm2_v4_f32: lm2_v4_pow_f32)(a, b)
#  define lm2_v4_clamp(a, b, c) \
    _Generic((a), lm2_v4_f64: lm2_v4_clamp_f64, lm2_v4_f32: lm2_v4_clamp_f32, lm2_v4_i64: lm2_v4_clamp_i64, lm2_v4_i32: lm2_v4_clamp_i32, lm2_v4_i16: lm2_v4_clamp_i16, lm2_v4_i8: lm2_v4_clamp_i8, lm2_v4_u64: lm2_v4_clamp_u64, lm2_v4_u32: lm2_v4_clamp_u32, lm2_v4_u16: lm2_v4_clamp_u16, lm2_v4_u8: lm2_v4_clamp_u8)(a, b, c)
#  define lm2_v4_lerp(a, b, t) \
    _Generic((a), lm2_v4_f64: lm2_v4_lerp_f64, lm2_v4_f32: lm2_v4_lerp_f32)(a, b, t)
#  define lm2_v4_smoothstep(a, b, t) \
    _Generic((a), lm2_v4_f64: lm2_v4_smoothstep_f64, lm2_v4_f32: lm2_v4_smoothstep_f32)(a, b, t)
#  define lm2_v4_alpha(a, b, t) \
    _Generic((a), lm2_v4_f64: lm2_v4_alpha_f64, lm2_v4_f32: lm2_v4_alpha_f32)(a, b, t)
#  define lm2_v4_dot(a, b) \
    _Generic((a), lm2_v4_f64: lm2_v4_dot_f64, lm2_v4_f32: lm2_v4_dot_f32, lm2_v4_i64: lm2_v4_dot_i64, lm2_v4_i32: lm2_v4_dot_i32, lm2_v4_i16: lm2_v4_dot_i16, lm2_v4_i8: lm2_v4_dot_i8)(a, b)
#  define lm2_v4_length(a) \
    _Generic((a), lm2_v4_f64: lm2_v4_length_f64, lm2_v4_f32: lm2_v4_length_f32)(a)
#  define lm2_v4_length_sq(a) \
    _Generic((a), lm2_v4_f64: lm2_v4_length_sq_f64, lm2_v4_f32: lm2_v4_length_sq_f32)(a)
#  define lm2_v4_distance(a, b) \
    _Generic((a), lm2_v4_f64: lm2_v4_distance_f64, lm2_v4_f32: lm2_v4_distance_f32)(a, b)
#  define lm2_v4_distance_sq(a, b) \
    _Generic((a), lm2_v4_f64: lm2_v4_distance_sq_f64, lm2_v4_f32: lm2_v4_distance_sq_f32)(a, b)
#  define lm2_v4_normalize(a) \
    _Generic((a), lm2_v4_f64: lm2_v4_normalize_f64, lm2_v4_f32: lm2_v4_normalize_f32)(a)
#  define lm2_v4_downcast(v) \
    _Generic((v), lm2_v4_f64: lm2_v4_downcast_f64, lm2_v4_f32: lm2_v4_downcast_f32, lm2_v4_i64: lm2_v4_downcast_i64, lm2_v4_i32: lm2_v4_downcast_i32, lm2_v4_i16: lm2_v4_downcast_i16, lm2_v4_i8: lm2_v4_downcast_i8, lm2_v4_u64: lm2_v4_downcast_u64, lm2_v4_u32: lm2_v4_downcast_u32, lm2_v4_u16: lm2_v4_downcast_u16, lm2_v4_u8: lm2_v4_downcast_u8)(v)

// Matrix operations
#  define lm2_m3x2_identity() \
    _Generic((float) {0}, float: lm2_m3x2_identity_f32, double: lm2_m3x2_identity_f64)()
#  define lm2_m3x2_zero() \
    _Generic((float) {0}, float: lm2_m3x2_zero_f32, double: lm2_m3x2_zero_f64)()
#  define lm2_m3x2_mul(a, b) \
    _Generic((a), lm2_m3x2_f64: lm2_m3x2_mul_f64, lm2_m3x2_f32: lm2_m3x2_mul_f32)(a, b)
#  define lm2_m3x3_identity() \
    _Generic((float) {0}, float: lm2_m3x3_identity_f32, double: lm2_m3x3_identity_f64)()
#  define lm2_m3x3_zero() \
    _Generic((float) {0}, float: lm2_m3x3_zero_f32, double: lm2_m3x3_zero_f64)()
#  define lm2_m3x3_mul(a, b) \
    _Generic((a), lm2_m3x3_f64: lm2_m3x3_mul_f64, lm2_m3x3_f32: lm2_m3x3_mul_f32)(a, b)
#  define lm2_m4x4_identity() \
    _Generic((float) {0}, float: lm2_m4x4_identity_f32, double: lm2_m4x4_identity_f64)()
#  define lm2_m4x4_zero() \
    _Generic((float) {0}, float: lm2_m4x4_zero_f32, double: lm2_m4x4_zero_f64)()
#  define lm2_m4x4_mul(a, b) \
    _Generic((a), lm2_m4x4_f64: lm2_m4x4_mul_f64, lm2_m4x4_f32: lm2_m4x4_mul_f32)(a, b)

// Quaternion operations
#  define lm2_quat_identity() \
    _Generic((float) {0}, float: lm2_quat_identity_f32, double: lm2_quat_identity_f64)()
#  define lm2_quat_multiply(a, b) \
    _Generic((a), lm2_quat_f64: lm2_quat_multiply_f64, lm2_quat_f32: lm2_quat_multiply_f32)(a, b)
#  define lm2_quat_normalize(q) \
    _Generic((q), lm2_quat_f64: lm2_quat_normalize_f64, lm2_quat_f32: lm2_quat_normalize_f32)(q)

// Range2/3/4 operations - comprehensive set
#  define lm2_r2_make(a, b, c, d) \
    _Generic((a), double: lm2_r2_make_f64, float: lm2_r2_make_f32, int64_t: lm2_r2_make_i64, int32_t: lm2_r2_make_i32, int16_t: lm2_r2_make_i16, int8_t: lm2_r2_make_i8, uint64_t: lm2_r2_make_u64, uint32_t: lm2_r2_make_u32, uint16_t: lm2_r2_make_u16, uint8_t: lm2_r2_make_u8)(a, b, c, d)
#  define lm2_r2_translate(r, v) \
    _Generic((r), lm2_r2_f64: lm2_r2_translate_f64, lm2_r2_f32: lm2_r2_translate_f32, lm2_r2_i64: lm2_r2_translate_i64, lm2_r2_i32: lm2_r2_translate_i32, lm2_r2_i16: lm2_r2_translate_i16, lm2_r2_i8: lm2_r2_translate_i8, lm2_r2_u64: lm2_r2_translate_u64, lm2_r2_u32: lm2_r2_translate_u32, lm2_r2_u16: lm2_r2_translate_u16, lm2_r2_u8: lm2_r2_translate_u8)(r, v)
#  define lm2_r2_contains_point(r, p) \
    _Generic((r), lm2_r2_f64: lm2_r2_contains_point_f64, lm2_r2_f32: lm2_r2_contains_point_f32, lm2_r2_i64: lm2_r2_contains_point_i64, lm2_r2_i32: lm2_r2_contains_point_i32, lm2_r2_i16: lm2_r2_contains_point_i16, lm2_r2_i8: lm2_r2_contains_point_i8, lm2_r2_u64: lm2_r2_contains_point_u64, lm2_r2_u32: lm2_r2_contains_point_u32, lm2_r2_u16: lm2_r2_contains_point_u16, lm2_r2_u8: lm2_r2_contains_point_u8)(r, p)
#  define lm2_r2_overlaps(a, b) \
    _Generic((a), lm2_r2_f64: lm2_r2_overlaps_f64, lm2_r2_f32: lm2_r2_overlaps_f32, lm2_r2_i64: lm2_r2_overlaps_i64, lm2_r2_i32: lm2_r2_overlaps_i32, lm2_r2_i16: lm2_r2_overlaps_i16, lm2_r2_i8: lm2_r2_overlaps_i8, lm2_r2_u64: lm2_r2_overlaps_u64, lm2_r2_u32: lm2_r2_overlaps_u32, lm2_r2_u16: lm2_r2_overlaps_u16, lm2_r2_u8: lm2_r2_overlaps_u8)(a, b)
#  define lm2_r2_area(r) \
    _Generic((r), lm2_r2_f64: lm2_r2_area_f64, lm2_r2_f32: lm2_r2_area_f32, lm2_r2_i64: lm2_r2_area_i64, lm2_r2_i32: lm2_r2_area_i32, lm2_r2_i16: lm2_r2_area_i16, lm2_r2_i8: lm2_r2_area_i8, lm2_r2_u64: lm2_r2_area_u64, lm2_r2_u32: lm2_r2_area_u32, lm2_r2_u16: lm2_r2_area_u16, lm2_r2_u8: lm2_r2_area_u8)(r)
#  define lm2_r2_get_center(r) \
    _Generic((r), lm2_r2_f64: lm2_r2_get_center_f64, lm2_r2_f32: lm2_r2_get_center_f32, lm2_r2_i64: lm2_r2_get_center_i64, lm2_r2_i32: lm2_r2_get_center_i32, lm2_r2_i16: lm2_r2_get_center_i16, lm2_r2_i8: lm2_r2_get_center_i8, lm2_r2_u64: lm2_r2_get_center_u64, lm2_r2_u32: lm2_r2_get_center_u32, lm2_r2_u16: lm2_r2_get_center_u16, lm2_r2_u8: lm2_r2_get_center_u8)(r)
#  define lm2_r2_union(a, b) \
    _Generic((a), lm2_r2_f64: lm2_r2_union_f64, lm2_r2_f32: lm2_r2_union_f32, lm2_r2_i64: lm2_r2_union_i64, lm2_r2_i32: lm2_r2_union_i32, lm2_r2_i16: lm2_r2_union_i16, lm2_r2_i8: lm2_r2_union_i8, lm2_r2_u64: lm2_r2_union_u64, lm2_r2_u32: lm2_r2_union_u32, lm2_r2_u16: lm2_r2_union_u16, lm2_r2_u8: lm2_r2_union_u8)(a, b)
#  define lm2_r2_intersection(a, b) \
    _Generic((a), lm2_r2_f64: lm2_r2_intersection_f64, lm2_r2_f32: lm2_r2_intersection_f32, lm2_r2_i64: lm2_r2_intersection_i64, lm2_r2_i32: lm2_r2_intersection_i32, lm2_r2_i16: lm2_r2_intersection_i16, lm2_r2_i8: lm2_r2_intersection_i8, lm2_r2_u64: lm2_r2_intersection_u64, lm2_r2_u32: lm2_r2_intersection_u32, lm2_r2_u16: lm2_r2_intersection_u16, lm2_r2_u8: lm2_r2_intersection_u8)(a, b)
#  define lm2_r3_make(a, b, c, d, e, f) \
    _Generic((a), double: lm2_r3_make_f64, float: lm2_r3_make_f32, int64_t: lm2_r3_make_i64, int32_t: lm2_r3_make_i32, int16_t: lm2_r3_make_i16, int8_t: lm2_r3_make_i8, uint64_t: lm2_r3_make_u64, uint32_t: lm2_r3_make_u32, uint16_t: lm2_r3_make_u16, uint8_t: lm2_r3_make_u8)(a, b, c, d, e, f)
#  define lm2_r3_contains_point(r, p) \
    _Generic((r), lm2_r3_f64: lm2_r3_contains_point_f64, lm2_r3_f32: lm2_r3_contains_point_f32, lm2_r3_i64: lm2_r3_contains_point_i64, lm2_r3_i32: lm2_r3_contains_point_i32, lm2_r3_i16: lm2_r3_contains_point_i16, lm2_r3_i8: lm2_r3_contains_point_i8, lm2_r3_u64: lm2_r3_contains_point_u64, lm2_r3_u32: lm2_r3_contains_point_u32, lm2_r3_u16: lm2_r3_contains_point_u16, lm2_r3_u8: lm2_r3_contains_point_u8)(r, p)
#  define lm2_r3_volume(r) \
    _Generic((r), lm2_r3_f64: lm2_r3_volume_f64, lm2_r3_f32: lm2_r3_volume_f32, lm2_r3_i64: lm2_r3_volume_i64, lm2_r3_i32: lm2_r3_volume_i32, lm2_r3_i16: lm2_r3_volume_i16, lm2_r3_i8: lm2_r3_volume_i8, lm2_r3_u64: lm2_r3_volume_u64, lm2_r3_u32: lm2_r3_volume_u32, lm2_r3_u16: lm2_r3_volume_u16, lm2_r3_u8: lm2_r3_volume_u8)(r)
#  define lm2_r3_overlaps(a, b) \
    _Generic((a), lm2_r3_f64: lm2_r3_overlaps_f64, lm2_r3_f32: lm2_r3_overlaps_f32, lm2_r3_i64: lm2_r3_overlaps_i64, lm2_r3_i32: lm2_r3_overlaps_i32, lm2_r3_i16: lm2_r3_overlaps_i16, lm2_r3_i8: lm2_r3_overlaps_i8, lm2_r3_u64: lm2_r3_overlaps_u64, lm2_r3_u32: lm2_r3_overlaps_u32, lm2_r3_u16: lm2_r3_overlaps_u16, lm2_r3_u8: lm2_r3_overlaps_u8)(a, b)
#  define lm2_r4_make(x1, x2, y1, y2, z1, z2, w1, w2) \
    _Generic((x1), double: lm2_r4_make_f64, float: lm2_r4_make_f32, int64_t: lm2_r4_make_i64, int32_t: lm2_r4_make_i32, int16_t: lm2_r4_make_i16, int8_t: lm2_r4_make_i8, uint64_t: lm2_r4_make_u64, uint32_t: lm2_r4_make_u32, uint16_t: lm2_r4_make_u16, uint8_t: lm2_r4_make_u8)(x1, x2, y1, y2, z1, z2, w1, w2)
#  define lm2_r4_contains_point(r, p) \
    _Generic((r), lm2_r4_f64: lm2_r4_contains_point_f64, lm2_r4_f32: lm2_r4_contains_point_f32, lm2_r4_i64: lm2_r4_contains_point_i64, lm2_r4_i32: lm2_r4_contains_point_i32, lm2_r4_i16: lm2_r4_contains_point_i16, lm2_r4_i8: lm2_r4_contains_point_i8, lm2_r4_u64: lm2_r4_contains_point_u64, lm2_r4_u32: lm2_r4_contains_point_u32, lm2_r4_u16: lm2_r4_contains_point_u16, lm2_r4_u8: lm2_r4_contains_point_u8)(r, p)
#  define lm2_r4_hypervolume(r) \
    _Generic((r), lm2_r4_f64: lm2_r4_hypervolume_f64, lm2_r4_f32: lm2_r4_hypervolume_f32, lm2_r4_i64: lm2_r4_hypervolume_i64, lm2_r4_i32: lm2_r4_hypervolume_i32, lm2_r4_i16: lm2_r4_hypervolume_i16, lm2_r4_i8: lm2_r4_hypervolume_i8, lm2_r4_u64: lm2_r4_hypervolume_u64, lm2_r4_u32: lm2_r4_hypervolume_u32, lm2_r4_u16: lm2_r4_hypervolume_u16, lm2_r4_u8: lm2_r4_hypervolume_u8)(r)

// Matrix3x2/3x3/4x4 operations - comprehensive set
#  define lm2_m3x2_from_translation(v) \
    _Generic((v), lm2_v2_f64: lm2_m3x2_from_translation_f64, lm2_v2_f32: lm2_m3x2_from_translation_f32)(v)
#  define lm2_m3x2_from_rotation(a) \
    _Generic((a), double: lm2_m3x2_from_rotation_f64, float: lm2_m3x2_from_rotation_f32)(a)
#  define lm2_m3x2_from_scale(s) \
    _Generic((s), double: lm2_m3x2_from_scale_f64, float: lm2_m3x2_from_scale_f32)(s)
#  define lm2_m3x2_transform_point(m, p) \
    _Generic((m), lm2_m3x2_f64: lm2_m3x2_transform_point_f64, lm2_m3x2_f32: lm2_m3x2_transform_point_f32)(m, p)
#  define lm2_m3x2_transform_vector(m, v) \
    _Generic((m), lm2_m3x2_f64: lm2_m3x2_transform_vector_f64, lm2_m3x2_f32: lm2_m3x2_transform_vector_f32)(m, v)
#  define lm2_m3x2_inverse(m) \
    _Generic((m), lm2_m3x2_f64: lm2_m3x2_inverse_f64, lm2_m3x2_f32: lm2_m3x2_inverse_f32)(m)
#  define lm2_m3x2_determinant(m) \
    _Generic((m), lm2_m3x2_f64: lm2_m3x2_determinant_f64, lm2_m3x2_f32: lm2_m3x2_determinant_f32)(m)
#  define lm2_m3x3_from_rotation_x(a) \
    _Generic((a), double: lm2_m3x3_from_rotation_x_f64, float: lm2_m3x3_from_rotation_x_f32)(a)
#  define lm2_m3x3_from_rotation_y(a) \
    _Generic((a), double: lm2_m3x3_from_rotation_y_f64, float: lm2_m3x3_from_rotation_y_f32)(a)
#  define lm2_m3x3_from_rotation_z(a) \
    _Generic((a), double: lm2_m3x3_from_rotation_z_f64, float: lm2_m3x3_from_rotation_z_f32)(a)
#  define lm2_m3x3_transform(m, v) \
    _Generic((m), lm2_m3x3_f64: lm2_m3x3_transform_f64, lm2_m3x3_f32: lm2_m3x3_transform_f32)(m, v)
#  define lm2_m3x3_transpose(m) \
    _Generic((m), lm2_m3x3_f64: lm2_m3x3_transpose_f64, lm2_m3x3_f32: lm2_m3x3_transpose_f32)(m)
#  define lm2_m3x3_inverse(m) \
    _Generic((m), lm2_m3x3_f64: lm2_m3x3_inverse_f64, lm2_m3x3_f32: lm2_m3x3_inverse_f32)(m)
#  define lm2_m3x3_determinant(m) \
    _Generic((m), lm2_m3x3_f64: lm2_m3x3_determinant_f64, lm2_m3x3_f32: lm2_m3x3_determinant_f32)(m)
#  define lm2_m4x4_from_translation(v) \
    _Generic((v), lm2_v3_f64: lm2_m4x4_from_translation_f64, lm2_v3_f32: lm2_m4x4_from_translation_f32)(v)
#  define lm2_m4x4_from_rotation_x(a) \
    _Generic((a), double: lm2_m4x4_from_rotation_x_f64, float: lm2_m4x4_from_rotation_x_f32)(a)
#  define lm2_m4x4_from_rotation_y(a) \
    _Generic((a), double: lm2_m4x4_from_rotation_y_f64, float: lm2_m4x4_from_rotation_y_f32)(a)
#  define lm2_m4x4_from_rotation_z(a) \
    _Generic((a), double: lm2_m4x4_from_rotation_z_f64, float: lm2_m4x4_from_rotation_z_f32)(a)
#  define lm2_m4x4_from_quaternion(q) \
    _Generic((q), lm2_quat_f64: lm2_m4x4_from_quaternion_f64, lm2_quat_f32: lm2_m4x4_from_quaternion_f32)(q)
#  define lm2_m4x4_transform_point(m, p) \
    _Generic((m), lm2_m4x4_f64: lm2_m4x4_transform_point_f64, lm2_m4x4_f32: lm2_m4x4_transform_point_f32)(m, p)
#  define lm2_m4x4_transform_vector(m, v) \
    _Generic((m), lm2_m4x4_f64: lm2_m4x4_transform_vector_f64, lm2_m4x4_f32: lm2_m4x4_transform_vector_f32)(m, v)
#  define lm2_m4x4_transpose(m) \
    _Generic((m), lm2_m4x4_f64: lm2_m4x4_transpose_f64, lm2_m4x4_f32: lm2_m4x4_transpose_f32)(m)
#  define lm2_m4x4_inverse(m) \
    _Generic((m), lm2_m4x4_f64: lm2_m4x4_inverse_f64, lm2_m4x4_f32: lm2_m4x4_inverse_f32)(m)
#  define lm2_m4x4_determinant(m) \
    _Generic((m), lm2_m4x4_f64: lm2_m4x4_determinant_f64, lm2_m4x4_f32: lm2_m4x4_determinant_f32)(m)
#  define lm2_m4x4_look_at(eye, target, up) \
    _Generic((eye), lm2_v3_f64: lm2_m4x4_look_at_f64, lm2_v3_f32: lm2_m4x4_look_at_f32)(eye, target, up)
#  define lm2_m4x4_perspective(fov, aspect, near, far) \
    _Generic((fov), double: lm2_m4x4_perspective_f64, float: lm2_m4x4_perspective_f32)(fov, aspect, near, far)
#  define lm2_m4x4_orthographic(l, r, b, t, n, f) \
    _Generic((l), double: lm2_m4x4_orthographic_f64, float: lm2_m4x4_orthographic_f32)(l, r, b, t, n, f)

// Quaternion operations - comprehensive set
#  define lm2_quat_zero() \
    _Generic((float) {0}, float: lm2_quat_zero_f32, double: lm2_quat_zero_f64)()
#  define lm2_quat_make(x, y, z, w) \
    _Generic((x), double: lm2_quat_make_f64, float: lm2_quat_make_f32)(x, y, z, w)
#  define lm2_quat_from_axis_angle(axis, angle) \
    _Generic((axis), lm2_v3_f64: lm2_quat_from_axis_angle_f64, lm2_v3_f32: lm2_quat_from_axis_angle_f32)(axis, angle)
#  define lm2_quat_from_euler(x, y, z) \
    _Generic((x), double: lm2_quat_from_euler_f64, float: lm2_quat_from_euler_f32)(x, y, z)
#  define lm2_quat_conjugate(q) \
    _Generic((q), lm2_quat_f64: lm2_quat_conjugate_f64, lm2_quat_f32: lm2_quat_conjugate_f32)(q)
#  define lm2_quat_inverse(q) \
    _Generic((q), lm2_quat_f64: lm2_quat_inverse_f64, lm2_quat_f32: lm2_quat_inverse_f32)(q)
#  define lm2_quat_add(a, b) \
    _Generic((a), lm2_quat_f64: lm2_quat_add_f64, lm2_quat_f32: lm2_quat_add_f32)(a, b)
#  define lm2_quat_sub(a, b) \
    _Generic((a), lm2_quat_f64: lm2_quat_sub_f64, lm2_quat_f32: lm2_quat_sub_f32)(a, b)
#  define lm2_quat_scale(q, s) \
    _Generic((q), lm2_quat_f64: lm2_quat_scale_f64, lm2_quat_f32: lm2_quat_scale_f32)(q, s)
#  define lm2_quat_dot(a, b) \
    _Generic((a), lm2_quat_f64: lm2_quat_dot_f64, lm2_quat_f32: lm2_quat_dot_f32)(a, b)
#  define lm2_quat_length(q) \
    _Generic((q), lm2_quat_f64: lm2_quat_length_f64, lm2_quat_f32: lm2_quat_length_f32)(q)
#  define lm2_quat_rotate_vector(q, v) \
    _Generic((q), lm2_quat_f64: lm2_quat_rotate_vector_f64, lm2_quat_f32: lm2_quat_rotate_vector_f32)(q, v)
#  define lm2_quat_slerp(a, b, t) \
    _Generic((a), lm2_quat_f64: lm2_quat_slerp_f64, lm2_quat_f32: lm2_quat_slerp_f32)(a, b, t)
#  define lm2_quat_nlerp(a, b, t) \
    _Generic((a), lm2_quat_f64: lm2_quat_nlerp_f64, lm2_quat_f32: lm2_quat_nlerp_f32)(a, b, t)

// Geometry2D/3D operations - key functions
#  define lm2_aabb3_from_min_max(min, max) \
    _Generic((min), lm2_v3_f64: lm2_aabb3_from_min_max_f64, lm2_v3_f32: lm2_aabb3_from_min_max_f32)(min, max)
#  define lm2_aabb3_contains_point(aabb, p) \
    _Generic((aabb), lm2_aabb3_f64: lm2_aabb3_contains_point_f64, lm2_aabb3_f32: lm2_aabb3_contains_point_f32)(aabb, p)
#  define lm2_aabb3_overlaps(a, b) \
    _Generic((a), lm2_aabb3_f64: lm2_aabb3_overlaps_f64, lm2_aabb3_f32: lm2_aabb3_overlaps_f32)(a, b)
#  define lm2_capsule2_make(a, b, r) \
    _Generic((a), lm2_v2_f64: lm2_capsule2_make_f64, lm2_v2_f32: lm2_capsule2_make_f32)(a, b, r)
#  define lm2_capsule2_contains_point(c, p) \
    _Generic((c), lm2_capsule2_f64: lm2_capsule2_contains_point_f64, lm2_capsule2_f32: lm2_capsule2_contains_point_f32)(c, p)
#  define lm2_capsule3_make(a, b, r) \
    _Generic((a), lm2_v3_f64: lm2_capsule3_make_f64, lm2_v3_f32: lm2_capsule3_make_f32)(a, b, r)
#  define lm2_capsule3_contains_point(c, p) \
    _Generic((c), lm2_capsule3_f64: lm2_capsule3_contains_point_f64, lm2_capsule3_f32: lm2_capsule3_contains_point_f32)(c, p)
#  define lm2_circle_make(c, r) \
    _Generic((c), lm2_v2_f64: lm2_circle_make_f64, lm2_v2_f32: lm2_circle_make_f32)(c, r)
#  define lm2_circle_area(c) \
    _Generic((c), lm2_circle_f64: lm2_circle_area_f64, lm2_circle_f32: lm2_circle_area_f32)(c)
#  define lm2_circle_circumference(c) \
    _Generic((c), lm2_circle_f64: lm2_circle_circumference_f64, lm2_circle_f32: lm2_circle_circumference_f32)(c)
#  define lm2_circle_contains_point(c, p) \
    _Generic((c), lm2_circle_f64: lm2_circle_contains_point_f64, lm2_circle_f32: lm2_circle_contains_point_f32)(c, p)
#  define lm2_sphere_make(c, r) \
    _Generic((c), lm2_v3_f64: lm2_sphere_make_f64, lm2_v3_f32: lm2_sphere_make_f32)(c, r)
#  define lm2_sphere_volume(s) \
    _Generic((s), lm2_sphere_f64: lm2_sphere_volume_f64, lm2_sphere_f32: lm2_sphere_volume_f32)(s)
#  define lm2_sphere_surface_area(s) \
    _Generic((s), lm2_sphere_f64: lm2_sphere_surface_area_f64, lm2_sphere_f32: lm2_sphere_surface_area_f32)(s)
#  define lm2_sphere_contains_point(s, p) \
    _Generic((s), lm2_sphere_f64: lm2_sphere_contains_point_f64, lm2_sphere_f32: lm2_sphere_contains_point_f32)(s, p)
#  define lm2_triangle2_make(a, b, c) \
    _Generic((a), lm2_v2_f64: lm2_triangle2_make_f64, lm2_v2_f32: lm2_triangle2_make_f32)(a, b, c)
#  define lm2_triangle2_area(t) \
    _Generic((t), lm2_triangle2_f64: lm2_triangle2_area_f64, lm2_triangle2_f32: lm2_triangle2_area_f32)(t)
#  define lm2_triangle2_contains_point(t, p) \
    _Generic((t), lm2_triangle2_f64: lm2_triangle2_contains_point_f64, lm2_triangle2_f32: lm2_triangle2_contains_point_f32)(t, p)
#  define lm2_triangle3_make(a, b, c) \
    _Generic((a), lm2_v3_f64: lm2_triangle3_make_f64, lm2_v3_f32: lm2_triangle3_make_f32)(a, b, c)
#  define lm2_triangle3_area(t) \
    _Generic((t), lm2_triangle3_f64: lm2_triangle3_area_f64, lm2_triangle3_f32: lm2_triangle3_area_f32)(t)
#  define lm2_triangle3_normal(t) \
    _Generic((t), lm2_triangle3_f64: lm2_triangle3_normal_f64, lm2_triangle3_f32: lm2_triangle3_normal_f32)(t)
#  define lm2_plane2_make(n, d) \
    _Generic((n), lm2_v2_f64: lm2_plane2_make_f64, lm2_v2_f32: lm2_plane2_make_f32)(n, d)
#  define lm2_plane2_distance_to_point(p, pt) \
    _Generic((p), lm2_plane2_f64: lm2_plane2_distance_to_point_f64, lm2_plane2_f32: lm2_plane2_distance_to_point_f32)(p, pt)
#  define lm2_plane3_make(n, d) \
    _Generic((n), lm2_v3_f64: lm2_plane3_make_f64, lm2_v3_f32: lm2_plane3_make_f32)(n, d)
#  define lm2_plane3_distance_to_point(p, pt) \
    _Generic((p), lm2_plane3_f64: lm2_plane3_distance_to_point_f64, lm2_plane3_f32: lm2_plane3_distance_to_point_f32)(p, pt)
#  define lm2_ray2_make(o, d) \
    _Generic((o), lm2_v2_f64: lm2_ray2_make_f64, lm2_v2_f32: lm2_ray2_make_f32)(o, d)
#  define lm2_ray3_make(o, d) \
    _Generic((o), lm2_v3_f64: lm2_ray3_make_f64, lm2_v3_f32: lm2_ray3_make_f32)(o, d)
#  define lm2_raycast_circle(r, c) \
    _Generic((r), lm2_ray2_f64: lm2_raycast_circle_f64, lm2_ray2_f32: lm2_raycast_circle_f32)(r, c)
#  define lm2_raycast_sphere(r, s) \
    _Generic((r), lm2_ray3_f64: lm2_raycast_sphere_f64, lm2_ray3_f32: lm2_raycast_sphere_f32)(r, s)
#  define lm2_raycast_triangle(r, t) \
    _Generic((r), lm2_ray3_f64: lm2_raycast_triangle_f64, lm2_ray3_f32: lm2_raycast_triangle_f32)(r, t)
#  define lm2_collide_circle_to_circle(a, b) \
    _Generic((a), lm2_circle_f64: lm2_collide_circle_to_circle_f64, lm2_circle_f32: lm2_collide_circle_to_circle_f32)(a, b)
#  define lm2_camera2_make(pos, rot, zoom, vp) \
    _Generic((pos), lm2_v2_f64: lm2_camera2_make_f64, lm2_v2_f32: lm2_camera2_make_f32)(pos, rot, zoom, vp)
#  define lm2_camera2_default(vp) \
    _Generic((vp), lm2_r2_f64: lm2_camera2_default_f64, lm2_r2_f32: lm2_camera2_default_f32)(vp)
#  define lm2_camera2_get_view(c) \
    _Generic((c), lm2_camera2_f64: lm2_camera2_get_view_f64, lm2_camera2_f32: lm2_camera2_get_view_f32)(c)
#  define lm2_camera2_get_inv_view(c) \
    _Generic((c), lm2_camera2_f64: lm2_camera2_get_inv_view_f64, lm2_camera2_f32: lm2_camera2_get_inv_view_f32)(c)
#  define lm2_camera2_world_to_screen(c, p) \
    _Generic((c), lm2_camera2_f64: lm2_camera2_world_to_screen_f64, lm2_camera2_f32: lm2_camera2_world_to_screen_f32)(c, p)
#  define lm2_camera2_screen_to_world(c, p) \
    _Generic((c), lm2_camera2_f64: lm2_camera2_screen_to_world_f64, lm2_camera2_f32: lm2_camera2_screen_to_world_f32)(c, p)
#  define lm2_camera2_move(c, d) \
    _Generic((c), lm2_camera2_f64: lm2_camera2_move_f64, lm2_camera2_f32: lm2_camera2_move_f32)(c, d)
#  define lm2_camera2_zoom_at(c, f, a) \
    _Generic((c), lm2_camera2_f64: lm2_camera2_zoom_at_f64, lm2_camera2_f32: lm2_camera2_zoom_at_f32)(c, f, a)
#  define lm2_camera2_set_zoom(c, z) \
    _Generic((c), lm2_camera2_f64: lm2_camera2_set_zoom_f64, lm2_camera2_f32: lm2_camera2_set_zoom_f32)(c, z)
#  define lm2_camera2_rotate(c, r) \
    _Generic((c), lm2_camera2_f64: lm2_camera2_rotate_f64, lm2_camera2_f32: lm2_camera2_rotate_f32)(c, r)
#  define lm2_camera2_get_viewport_size(c) \
    _Generic((c), lm2_camera2_f64: lm2_camera2_get_viewport_size_f64, lm2_camera2_f32: lm2_camera2_get_viewport_size_f32)(c)
#  define lm2_camera2_get_viewport_center(c) \
    _Generic((c), lm2_camera2_f64: lm2_camera2_get_viewport_center_f64, lm2_camera2_f32: lm2_camera2_get_viewport_center_f32)(c)
#  define lm2_camera2_get_world_bounds(c) \
    _Generic((c), lm2_camera2_f64: lm2_camera2_get_world_bounds_f64, lm2_camera2_f32: lm2_camera2_get_world_bounds_f32)(c)
#  define lm2_camera3_get_view(c) \
    _Generic((c), lm2_camera3_f64: lm2_camera3_get_view_f64, lm2_camera3_f32: lm2_camera3_get_view_f32)(c)
#  define lm2_camera3_get_projection(c) \
    _Generic((c), lm2_camera3_f64: lm2_camera3_get_projection_f64, lm2_camera3_f32: lm2_camera3_get_projection_f32)(c)
#  define lm2_camera3_get_view_projection(c) \
    _Generic((c), lm2_camera3_f64: lm2_camera3_get_view_projection_f64, lm2_camera3_f32: lm2_camera3_get_view_projection_f32)(c)
#  define lm2_camera3_get_inv_view(c) \
    _Generic((c), lm2_camera3_f64: lm2_camera3_get_inv_view_f64, lm2_camera3_f32: lm2_camera3_get_inv_view_f32)(c)
#  define lm2_camera3_get_forward(c) \
    _Generic((c), lm2_camera3_f64: lm2_camera3_get_forward_f64, lm2_camera3_f32: lm2_camera3_get_forward_f32)(c)
#  define lm2_camera3_get_right(c) \
    _Generic((c), lm2_camera3_f64: lm2_camera3_get_right_f64, lm2_camera3_f32: lm2_camera3_get_right_f32)(c)
#  define lm2_camera3_get_up(c) \
    _Generic((c), lm2_camera3_f64: lm2_camera3_get_up_f64, lm2_camera3_f32: lm2_camera3_get_up_f32)(c)
#  define lm2_camera3_move(c, d) \
    _Generic((c), lm2_camera3_f64: lm2_camera3_move_f64, lm2_camera3_f32: lm2_camera3_move_f32)(c, d)
#  define lm2_camera3_look_at(c, t) \
    _Generic((c), lm2_camera3_f64: lm2_camera3_look_at_f64, lm2_camera3_f32: lm2_camera3_look_at_f32)(c, t)
#  define lm2_camera3_orbit(c, y, p) \
    _Generic((c), lm2_camera3_f64: lm2_camera3_orbit_f64, lm2_camera3_f32: lm2_camera3_orbit_f32)(c, y, p)
#  define lm2_camera3_set_aspect(c, a) \
    _Generic((c), lm2_camera3_f64: lm2_camera3_set_aspect_f64, lm2_camera3_f32: lm2_camera3_set_aspect_f32)(c, a)
#  define lm2_camera3_set_fov_y(c, f) \
    _Generic((c), lm2_camera3_f64: lm2_camera3_set_fov_y_f64, lm2_camera3_f32: lm2_camera3_set_fov_y_f32)(c, f)
#  define lm2_camera3_get_orientation(c) \
    _Generic((c), lm2_camera3_f64: lm2_camera3_get_orientation_f64, lm2_camera3_f32: lm2_camera3_get_orientation_f32)(c)
#  define lm2_camera3_set_orientation(c, q) \
    _Generic((c), lm2_camera3_f64: lm2_camera3_set_orientation_f64, lm2_camera3_f32: lm2_camera3_set_orientation_f32)(c, q)
#  define lm2_camera3_rotate_local(c, q) \
    _Generic((c), lm2_camera3_f64: lm2_camera3_rotate_local_f64, lm2_camera3_f32: lm2_camera3_rotate_local_f32)(c, q)
#  define lm2_camera3_world_to_ndc(c, p) \
    _Generic((c), lm2_camera3_f64: lm2_camera3_world_to_ndc_f64, lm2_camera3_f32: lm2_camera3_world_to_ndc_f32)(c, p)
#  define lm2_camera3_ndc_to_world(c, p) \
    _Generic((c), lm2_camera3_f64: lm2_camera3_ndc_to_world_f64, lm2_camera3_f32: lm2_camera3_ndc_to_world_f32)(c, p)

#endif