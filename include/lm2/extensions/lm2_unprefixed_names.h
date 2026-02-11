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

#define PI2_F32        LM2_2PI_F32
#define PI2_F64        LM2_2PI_F64
#define DEG_TO_RAD_F32 LM2_DEG_TO_RAD_F32
#define DEG_TO_RAD_F64 LM2_DEG_TO_RAD_F64
#define E_F32          LM2_E_F32
#define E_F64          LM2_E_F64
#define EULER_F32      LM2_EULER_F32
#define EULER_F64      LM2_EULER_F64
#define HPI_F32        LM2_HPI_F32
#define HPI_F64        LM2_HPI_F64
#define PI_F32         LM2_PI_F32
#define PI_F64         LM2_PI_F64
#define RAD_TO_DEG_F32 LM2_RAD_TO_DEG_F32
#define RAD_TO_DEG_F64 LM2_RAD_TO_DEG_F64
#define SQRT2_F32      LM2_SQRT2_F32
#define SQRT2_F64      LM2_SQRT2_F64

#define floor_f64                               lm2_floor_f64
#define floor_f32                               lm2_floor_f32
#define floor_multiple_f64                      lm2_floor_multiple_f64
#define floor_multiple_f32                      lm2_floor_multiple_f32
#define ceil_f64                                lm2_ceil_f64
#define ceil_f32                                lm2_ceil_f32
#define ceil_multiple_f64                       lm2_ceil_multiple_f64
#define ceil_multiple_f32                       lm2_ceil_multiple_f32
#define round_f64                               lm2_round_f64
#define round_f32                               lm2_round_f32
#define round_multiple_f64                      lm2_round_multiple_f64
#define round_multiple_f32                      lm2_round_multiple_f32
#define trunc_f64                               lm2_trunc_f64
#define trunc_f32                               lm2_trunc_f32
#define trunc_multiple_f64                      lm2_trunc_multiple_f64
#define trunc_multiple_f32                      lm2_trunc_multiple_f32
#define abs_f64                                 lm2_abs_f64
#define abs_f32                                 lm2_abs_f32
#define abs_i64                                 lm2_abs_i64
#define abs_i32                                 lm2_abs_i32
#define abs_i16                                 lm2_abs_i16
#define abs_i8                                  lm2_abs_i8
#define sign_f64                                lm2_sign_f64
#define sign_f32                                lm2_sign_f32
#define sign_i64                                lm2_sign_i64
#define sign_i32                                lm2_sign_i32
#define sign_i16                                lm2_sign_i16
#define sign_i8                                 lm2_sign_i8
#define sign0_f64                               lm2_sign0_f64
#define sign0_f32                               lm2_sign0_f32
#define sign0_i64                               lm2_sign0_i64
#define sign0_i32                               lm2_sign0_i32
#define sign0_i16                               lm2_sign0_i16
#define sign0_i8                                lm2_sign0_i8
#define min_f64                                 lm2_min_f64
#define min_f32                                 lm2_min_f32
#define min_i64                                 lm2_min_i64
#define min_i32                                 lm2_min_i32
#define min_i16                                 lm2_min_i16
#define min_i8                                  lm2_min_i8
#define min_u64                                 lm2_min_u64
#define min_u32                                 lm2_min_u32
#define min_u16                                 lm2_min_u16
#define min_u8                                  lm2_min_u8
#define min_abs_f64                             lm2_min_abs_f64
#define min_abs_f32                             lm2_min_abs_f32
#define min_abs_i64                             lm2_min_abs_i64
#define min_abs_i32                             lm2_min_abs_i32
#define min_abs_i16                             lm2_min_abs_i16
#define min_abs_i8                              lm2_min_abs_i8
#define max_f64                                 lm2_max_f64
#define max_f32                                 lm2_max_f32
#define max_i64                                 lm2_max_i64
#define max_i32                                 lm2_max_i32
#define max_i16                                 lm2_max_i16
#define max_i8                                  lm2_max_i8
#define max_u64                                 lm2_max_u64
#define max_u32                                 lm2_max_u32
#define max_u16                                 lm2_max_u16
#define max_u8                                  lm2_max_u8
#define max_abs_f64                             lm2_max_abs_f64
#define max_abs_f32                             lm2_max_abs_f32
#define max_abs_i64                             lm2_max_abs_i64
#define max_abs_i32                             lm2_max_abs_i32
#define max_abs_i16                             lm2_max_abs_i16
#define max_abs_i8                              lm2_max_abs_i8
#define clamp_f64                               lm2_clamp_f64
#define clamp_f32                               lm2_clamp_f32
#define clamp_i64                               lm2_clamp_i64
#define clamp_i32                               lm2_clamp_i32
#define clamp_i16                               lm2_clamp_i16
#define clamp_i8                                lm2_clamp_i8
#define clamp_u64                               lm2_clamp_u64
#define clamp_u32                               lm2_clamp_u32
#define clamp_u16                               lm2_clamp_u16
#define clamp_u8                                lm2_clamp_u8
#define saturate_f64                            lm2_saturate_f64
#define saturate_f32                            lm2_saturate_f32
#define lerp_f64                                lm2_lerp_f64
#define lerp_f32                                lm2_lerp_f32
#define smoothstep_f64                          lm2_smoothstep_f64
#define smoothstep_f32                          lm2_smoothstep_f32
#define alpha_f64                               lm2_alpha_f64
#define alpha_f32                               lm2_alpha_f32
#define fract_f64                               lm2_fract_f64
#define fract_f32                               lm2_fract_f32
#define pow_f64                                 lm2_pow_f64
#define pow_f32                                 lm2_pow_f32
#define sqrt_f64                                lm2_sqrt_f64
#define sqrt_f32                                lm2_sqrt_f32
#define cos_f64                                 lm2_cos_f64
#define cos_f32                                 lm2_cos_f32
#define sin_f64                                 lm2_sin_f64
#define sin_f32                                 lm2_sin_f32
#define tan_f64                                 lm2_tan_f64
#define tan_f32                                 lm2_tan_f32
#define acos_f64                                lm2_acos_f64
#define acos_f32                                lm2_acos_f32
#define asin_f64                                lm2_asin_f64
#define asin_f32                                lm2_asin_f32
#define atan_f64                                lm2_atan_f64
#define atan_f32                                lm2_atan_f32
#define atan2_f64                               lm2_atan2_f64
#define atan2_f32                               lm2_atan2_f32
#define deg_to_rad_f64                          lm2_deg_to_rad_f64
#define deg_to_rad_f32                          lm2_deg_to_rad_f32
#define rad_to_deg_f64                          lm2_rad_to_deg_f64
#define rad_to_deg_f32                          lm2_rad_to_deg_f32
#define wrap_rad_f64                            lm2_wrap_rad_f64
#define wrap_rad_f32                            lm2_wrap_rad_f32
#define shortest_rad_f64                        lm2_shortest_rad_f64
#define shortest_rad_f32                        lm2_shortest_rad_f32
#define lerp_rad_f64                            lm2_lerp_rad_f64
#define lerp_rad_f32                            lm2_lerp_rad_f32
#define wrap_deg_f64                            lm2_wrap_deg_f64
#define wrap_deg_f32                            lm2_wrap_deg_f32
#define shortest_deg_f64                        lm2_shortest_deg_f64
#define shortest_deg_f32                        lm2_shortest_deg_f32
#define lerp_deg_f64                            lm2_lerp_deg_f64
#define lerp_deg_f32                            lm2_lerp_deg_f32
#define bezier_linear2_f64                      lm2_bezier_linear2_f64
#define bezier_linear2_f32                      lm2_bezier_linear2_f32
#define bezier_linear3_f64                      lm2_bezier_linear3_f64
#define bezier_linear3_f32                      lm2_bezier_linear3_f32
#define bezier_linear4_f64                      lm2_bezier_linear4_f64
#define bezier_linear4_f32                      lm2_bezier_linear4_f32
#define bezier_quadratic2_f64                   lm2_bezier_quadratic2_f64
#define bezier_quadratic2_f32                   lm2_bezier_quadratic2_f32
#define bezier_quadratic3_f64                   lm2_bezier_quadratic3_f64
#define bezier_quadratic3_f32                   lm2_bezier_quadratic3_f32
#define bezier_quadratic4_f64                   lm2_bezier_quadratic4_f64
#define bezier_quadratic4_f32                   lm2_bezier_quadratic4_f32
#define bezier_cubic2_f64                       lm2_bezier_cubic2_f64
#define bezier_cubic2_f32                       lm2_bezier_cubic2_f32
#define bezier_cubic3_f64                       lm2_bezier_cubic3_f64
#define bezier_cubic3_f32                       lm2_bezier_cubic3_f32
#define bezier_cubic4_f64                       lm2_bezier_cubic4_f64
#define bezier_cubic4_f32                       lm2_bezier_cubic4_f32
#define bezier_quadratic_derivative2_f64        lm2_bezier_quadratic_derivative2_f64
#define bezier_quadratic_derivative2_f32        lm2_bezier_quadratic_derivative2_f32
#define bezier_quadratic_derivative3_f64        lm2_bezier_quadratic_derivative3_f64
#define bezier_quadratic_derivative3_f32        lm2_bezier_quadratic_derivative3_f32
#define bezier_quadratic_derivative4_f64        lm2_bezier_quadratic_derivative4_f64
#define bezier_quadratic_derivative4_f32        lm2_bezier_quadratic_derivative4_f32
#define bezier_cubic_derivative2_f64            lm2_bezier_cubic_derivative2_f64
#define bezier_cubic_derivative2_f32            lm2_bezier_cubic_derivative2_f32
#define bezier_cubic_derivative3_f64            lm2_bezier_cubic_derivative3_f64
#define bezier_cubic_derivative3_f32            lm2_bezier_cubic_derivative3_f32
#define bezier_cubic_derivative4_f64            lm2_bezier_cubic_derivative4_f64
#define bezier_cubic_derivative4_f32            lm2_bezier_cubic_derivative4_f32
#define bezier_cubic_second_derivative2_f64     lm2_bezier_cubic_second_derivative2_f64
#define bezier_cubic_second_derivative2_f32     lm2_bezier_cubic_second_derivative2_f32
#define bezier_cubic_second_derivative3_f64     lm2_bezier_cubic_second_derivative3_f64
#define bezier_cubic_second_derivative3_f32     lm2_bezier_cubic_second_derivative3_f32
#define bezier_cubic_second_derivative4_f64     lm2_bezier_cubic_second_derivative4_f64
#define bezier_cubic_second_derivative4_f32     lm2_bezier_cubic_second_derivative4_f32
#define bezier_cubic_split2_f64                 lm2_bezier_cubic_split2_f64
#define bezier_cubic_split2_f32                 lm2_bezier_cubic_split2_f32
#define bezier_cubic_split3_f64                 lm2_bezier_cubic_split3_f64
#define bezier_cubic_split3_f32                 lm2_bezier_cubic_split3_f32
#define bezier_cubic_split4_f64                 lm2_bezier_cubic_split4_f64
#define bezier_cubic_split4_f32                 lm2_bezier_cubic_split4_f32
#define bezier_cubic_length2_f64                lm2_bezier_cubic_length2_f64
#define bezier_cubic_length2_f32                lm2_bezier_cubic_length2_f32
#define bezier_cubic_length3_f64                lm2_bezier_cubic_length3_f64
#define bezier_cubic_length3_f32                lm2_bezier_cubic_length3_f32
#define bezier_cubic_length4_f64                lm2_bezier_cubic_length4_f64
#define bezier_cubic_length4_f32                lm2_bezier_cubic_length4_f32
#define ease_linear_f64                         lm2_ease_linear_f64
#define ease_linear_f32                         lm2_ease_linear_f32
#define ease_sin_in_f64                         lm2_ease_sin_in_f64
#define ease_sin_out_f64                        lm2_ease_sin_out_f64
#define ease_sin_in_out_f64                     lm2_ease_sin_in_out_f64
#define ease_sin_in_f32                         lm2_ease_sin_in_f32
#define ease_sin_out_f32                        lm2_ease_sin_out_f32
#define ease_sin_in_out_f32                     lm2_ease_sin_in_out_f32
#define ease_quad_in_f64                        lm2_ease_quad_in_f64
#define ease_quad_out_f64                       lm2_ease_quad_out_f64
#define ease_quad_in_out_f64                    lm2_ease_quad_in_out_f64
#define ease_quad_in_f32                        lm2_ease_quad_in_f32
#define ease_quad_out_f32                       lm2_ease_quad_out_f32
#define ease_quad_in_out_f32                    lm2_ease_quad_in_out_f32
#define ease_cubic_in_f64                       lm2_ease_cubic_in_f64
#define ease_cubic_out_f64                      lm2_ease_cubic_out_f64
#define ease_cubic_in_out_f64                   lm2_ease_cubic_in_out_f64
#define ease_cubic_in_f32                       lm2_ease_cubic_in_f32
#define ease_cubic_out_f32                      lm2_ease_cubic_out_f32
#define ease_cubic_in_out_f32                   lm2_ease_cubic_in_out_f32
#define ease_quart_in_f64                       lm2_ease_quart_in_f64
#define ease_quart_out_f64                      lm2_ease_quart_out_f64
#define ease_quart_in_out_f64                   lm2_ease_quart_in_out_f64
#define ease_quart_in_f32                       lm2_ease_quart_in_f32
#define ease_quart_out_f32                      lm2_ease_quart_out_f32
#define ease_quart_in_out_f32                   lm2_ease_quart_in_out_f32
#define ease_quint_in_f64                       lm2_ease_quint_in_f64
#define ease_quint_out_f64                      lm2_ease_quint_out_f64
#define ease_quint_in_out_f64                   lm2_ease_quint_in_out_f64
#define ease_quint_in_f32                       lm2_ease_quint_in_f32
#define ease_quint_out_f32                      lm2_ease_quint_out_f32
#define ease_quint_in_out_f32                   lm2_ease_quint_in_out_f32
#define ease_exp_in_f64                         lm2_ease_exp_in_f64
#define ease_exp_out_f64                        lm2_ease_exp_out_f64
#define ease_exp_in_out_f64                     lm2_ease_exp_in_out_f64
#define ease_exp_in_f32                         lm2_ease_exp_in_f32
#define ease_exp_out_f32                        lm2_ease_exp_out_f32
#define ease_exp_in_out_f32                     lm2_ease_exp_in_out_f32
#define ease_circ_in_f64                        lm2_ease_circ_in_f64
#define ease_circ_out_f64                       lm2_ease_circ_out_f64
#define ease_circ_in_out_f64                    lm2_ease_circ_in_out_f64
#define ease_circ_in_f32                        lm2_ease_circ_in_f32
#define ease_circ_out_f32                       lm2_ease_circ_out_f32
#define ease_circ_in_out_f32                    lm2_ease_circ_in_out_f32
#define ease_back_in_f64                        lm2_ease_back_in_f64
#define ease_back_out_f64                       lm2_ease_back_out_f64
#define ease_back_in_out_f64                    lm2_ease_back_in_out_f64
#define ease_back_in_f32                        lm2_ease_back_in_f32
#define ease_back_out_f32                       lm2_ease_back_out_f32
#define ease_back_in_out_f32                    lm2_ease_back_in_out_f32
#define ease_elastic_in_f64                     lm2_ease_elastic_in_f64
#define ease_elastic_out_f64                    lm2_ease_elastic_out_f64
#define ease_elastic_in_out_f64                 lm2_ease_elastic_in_out_f64
#define ease_elastic_in_f32                     lm2_ease_elastic_in_f32
#define ease_elastic_out_f32                    lm2_ease_elastic_out_f32
#define ease_elastic_in_out_f32                 lm2_ease_elastic_in_out_f32
#define ease_bounce_in_f64                      lm2_ease_bounce_in_f64
#define ease_bounce_out_f64                     lm2_ease_bounce_out_f64
#define ease_bounce_in_out_f64                  lm2_ease_bounce_in_out_f64
#define ease_bounce_in_f32                      lm2_ease_bounce_in_f32
#define ease_bounce_out_f32                     lm2_ease_bounce_out_f32
#define ease_bounce_in_out_f32                  lm2_ease_bounce_in_out_f32
#define easing_to_string                        lm2_easing_to_string
#define ease_f64                                lm2_ease_f64
#define ease_f32                                lm2_ease_f32
#define hash_mix_u64                            lm2_hash_mix_u64
#define hash_mix_u32                            lm2_hash_mix_u32
#define hash_f64                                lm2_hash_f64
#define hash_f32                                lm2_hash_f32
#define hash_i64                                lm2_hash_i64
#define hash_i32                                lm2_hash_i32
#define hash_i16                                lm2_hash_i16
#define hash_i8                                 lm2_hash_i8
#define hash_u64                                lm2_hash_u64
#define hash_u32                                lm2_hash_u32
#define hash_u16                                lm2_hash_u16
#define hash_u8                                 lm2_hash_u8
#define hash_fnv1a_u32                          lm2_hash_fnv1a_u32
#define hash_fnv1a_u64                          lm2_hash_fnv1a_u64
#define hash_combine_u32                        lm2_hash_combine_u32
#define hash_combine_u64                        lm2_hash_combine_u64
#define perlin2_f64                             lm2_perlin2_f64
#define perlin2_f32                             lm2_perlin2_f32
#define perlin3_f64                             lm2_perlin3_f64
#define perlin3_f32                             lm2_perlin3_f32
#define voronoi2_f64                            lm2_voronoi2_f64
#define voronoi2_f32                            lm2_voronoi2_f32
#define voronoi3_f64                            lm2_voronoi3_f64
#define voronoi3_f32                            lm2_voronoi3_f32
#define quat_f64                                lm2_quat_f64
#define quat_f32                                lm2_quat_f32
#define quat                                    lm2_quat
#define quat_identity_f64                       lm2_quat_identity_f64
#define quat_zero_f64                           lm2_quat_zero_f64
#define quat_make_f64                           lm2_quat_make_f64
#define quat_from_axis_angle_f64                lm2_quat_from_axis_angle_f64
#define quat_from_euler_f64                     lm2_quat_from_euler_f64
#define quat_from_euler_vec_f64                 lm2_quat_from_euler_vec_f64
#define quat_to_axis_angle_f64                  lm2_quat_to_axis_angle_f64
#define quat_to_euler_f64                       lm2_quat_to_euler_f64
#define quat_conjugate_f64                      lm2_quat_conjugate_f64
#define quat_inverse_f64                        lm2_quat_inverse_f64
#define quat_normalize_f64                      lm2_quat_normalize_f64
#define quat_multiply_f64                       lm2_quat_multiply_f64
#define quat_add_f64                            lm2_quat_add_f64
#define quat_sub_f64                            lm2_quat_sub_f64
#define quat_scale_f64                          lm2_quat_scale_f64
#define quat_dot_f64                            lm2_quat_dot_f64
#define quat_length_squared_f64                 lm2_quat_length_squared_f64
#define quat_length_f64                         lm2_quat_length_f64
#define quat_rotate_vector_f64                  lm2_quat_rotate_vector_f64
#define quat_slerp_f64                          lm2_quat_slerp_f64
#define quat_nlerp_f64                          lm2_quat_nlerp_f64
#define quat_equals_f64                         lm2_quat_equals_f64
#define quat_identity_f32                       lm2_quat_identity_f32
#define quat_zero_f32                           lm2_quat_zero_f32
#define quat_make_f32                           lm2_quat_make_f32
#define quat_from_axis_angle_f32                lm2_quat_from_axis_angle_f32
#define quat_from_euler_f32                     lm2_quat_from_euler_f32
#define quat_from_euler_vec_f32                 lm2_quat_from_euler_vec_f32
#define quat_to_axis_angle_f32                  lm2_quat_to_axis_angle_f32
#define quat_to_euler_f32                       lm2_quat_to_euler_f32
#define quat_conjugate_f32                      lm2_quat_conjugate_f32
#define quat_inverse_f32                        lm2_quat_inverse_f32
#define quat_normalize_f32                      lm2_quat_normalize_f32
#define quat_multiply_f32                       lm2_quat_multiply_f32
#define quat_add_f32                            lm2_quat_add_f32
#define quat_sub_f32                            lm2_quat_sub_f32
#define quat_scale_f32                          lm2_quat_scale_f32
#define quat_dot_f32                            lm2_quat_dot_f32
#define quat_length_squared_f32                 lm2_quat_length_squared_f32
#define quat_length_f32                         lm2_quat_length_f32
#define quat_rotate_vector_f32                  lm2_quat_rotate_vector_f32
#define quat_slerp_f32                          lm2_quat_slerp_f32
#define quat_nlerp_f32                          lm2_quat_nlerp_f32
#define quat_equals_f32                         lm2_quat_equals_f32
#define v2_f64                                  lm2_v2_f64
#define v2_f32                                  lm2_v2_f32
#define v2_i64                                  lm2_v2_i64
#define v2_i32                                  lm2_v2_i32
#define v2_i16                                  lm2_v2_i16
#define v2_i8                                   lm2_v2_i8
#define v2_u64                                  lm2_v2_u64
#define v2_u32                                  lm2_v2_u32
#define v2_u16                                  lm2_v2_u16
#define v2_u8                                   lm2_v2_u8
#define v2                                      lm2_v2
#define v3_f64                                  lm2_v3_f64
#define v3_f32                                  lm2_v3_f32
#define v3_i64                                  lm2_v3_i64
#define v3_i32                                  lm2_v3_i32
#define v3_i16                                  lm2_v3_i16
#define v3_i8                                   lm2_v3_i8
#define v3_u64                                  lm2_v3_u64
#define v3_u32                                  lm2_v3_u32
#define v3_u16                                  lm2_v3_u16
#define v3_u8                                   lm2_v3_u8
#define v3                                      lm2_v3
#define v4_f64                                  lm2_v4_f64
#define v4_f32                                  lm2_v4_f32
#define v4_i64                                  lm2_v4_i64
#define v4_i32                                  lm2_v4_i32
#define v4_i16                                  lm2_v4_i16
#define v4_i8                                   lm2_v4_i8
#define v4_u64                                  lm2_v4_u64
#define v4_u32                                  lm2_v4_u32
#define v4_u16                                  lm2_v4_u16
#define v4_u8                                   lm2_v4_u8
#define v4                                      lm2_v4
#define v2_add_f64                              lm2_v2_add_f64
#define v2_sub_f64                              lm2_v2_sub_f64
#define v2_mul_f64                              lm2_v2_mul_f64
#define v2_div_f64                              lm2_v2_div_f64
#define v2_add_s_f64                            lm2_v2_add_s_f64
#define v2_sub_s_f64                            lm2_v2_sub_s_f64
#define v2_mul_s_f64                            lm2_v2_mul_s_f64
#define v2_div_s_f64                            lm2_v2_div_s_f64
#define v2_neg_f64                              lm2_v2_neg_f64
#define v2_floor_f64                            lm2_v2_floor_f64
#define v2_ceil_f64                             lm2_v2_ceil_f64
#define v2_round_f64                            lm2_v2_round_f64
#define v2_trunc_f64                            lm2_v2_trunc_f64
#define v2_abs_f64                              lm2_v2_abs_f64
#define v2_sign_f64                             lm2_v2_sign_f64
#define v2_sign0_f64                            lm2_v2_sign0_f64
#define v2_saturate_f64                         lm2_v2_saturate_f64
#define v2_fract_f64                            lm2_v2_fract_f64
#define v2_sqrt_f64                             lm2_v2_sqrt_f64
#define v2_floor_multiple_f64                   lm2_v2_floor_multiple_f64
#define v2_ceil_multiple_f64                    lm2_v2_ceil_multiple_f64
#define v2_round_multiple_f64                   lm2_v2_round_multiple_f64
#define v2_trunc_multiple_f64                   lm2_v2_trunc_multiple_f64
#define v2_min_f64                              lm2_v2_min_f64
#define v2_min_abs_f64                          lm2_v2_min_abs_f64
#define v2_max_f64                              lm2_v2_max_f64
#define v2_max_abs_f64                          lm2_v2_max_abs_f64
#define v2_mod_f64                              lm2_v2_mod_f64
#define v2_pow_f64                              lm2_v2_pow_f64
#define v2_clamp_f64                            lm2_v2_clamp_f64
#define v2_lerp_f64                             lm2_v2_lerp_f64
#define v2_smoothstep_f64                       lm2_v2_smoothstep_f64
#define v2_alpha_f64                            lm2_v2_alpha_f64
#define v2_make_f64                             lm2_v2_make_f64
#define v2_splat_f64                            lm2_v2_splat_f64
#define v2_zero_f64                             lm2_v2_zero_f64
#define v2_dot_f64                              lm2_v2_dot_f64
#define v2_cross_f64                            lm2_v2_cross_f64
#define v2_cross3_f64                           lm2_v2_cross3_f64
#define v2_length_f64                           lm2_v2_length_f64
#define v2_length_sq_f64                        lm2_v2_length_sq_f64
#define v2_distance_f64                         lm2_v2_distance_f64
#define v2_distance_sq_f64                      lm2_v2_distance_sq_f64
#define v2_normalize_f64                        lm2_v2_normalize_f64
#define v2_angle_f64                            lm2_v2_angle_f64
#define v2_rotate_f64                           lm2_v2_rotate_f64
#define v2_rotate_around_f64                    lm2_v2_rotate_around_f64
#define v2_perp_ccw_f64                         lm2_v2_perp_ccw_f64
#define v2_perp_cw_f64                          lm2_v2_perp_cw_f64
#define v2_reflect_f64                          lm2_v2_reflect_f64
#define v2_project_f64                          lm2_v2_project_f64
#define v2_add_f32                              lm2_v2_add_f32
#define v2_sub_f32                              lm2_v2_sub_f32
#define v2_mul_f32                              lm2_v2_mul_f32
#define v2_div_f32                              lm2_v2_div_f32
#define v2_add_s_f32                            lm2_v2_add_s_f32
#define v2_sub_s_f32                            lm2_v2_sub_s_f32
#define v2_mul_s_f32                            lm2_v2_mul_s_f32
#define v2_div_s_f32                            lm2_v2_div_s_f32
#define v2_neg_f32                              lm2_v2_neg_f32
#define v2_floor_f32                            lm2_v2_floor_f32
#define v2_ceil_f32                             lm2_v2_ceil_f32
#define v2_round_f32                            lm2_v2_round_f32
#define v2_trunc_f32                            lm2_v2_trunc_f32
#define v2_abs_f32                              lm2_v2_abs_f32
#define v2_sign_f32                             lm2_v2_sign_f32
#define v2_sign0_f32                            lm2_v2_sign0_f32
#define v2_saturate_f32                         lm2_v2_saturate_f32
#define v2_fract_f32                            lm2_v2_fract_f32
#define v2_sqrt_f32                             lm2_v2_sqrt_f32
#define v2_floor_multiple_f32                   lm2_v2_floor_multiple_f32
#define v2_ceil_multiple_f32                    lm2_v2_ceil_multiple_f32
#define v2_round_multiple_f32                   lm2_v2_round_multiple_f32
#define v2_trunc_multiple_f32                   lm2_v2_trunc_multiple_f32
#define v2_min_f32                              lm2_v2_min_f32
#define v2_min_abs_f32                          lm2_v2_min_abs_f32
#define v2_max_f32                              lm2_v2_max_f32
#define v2_max_abs_f32                          lm2_v2_max_abs_f32
#define v2_mod_f32                              lm2_v2_mod_f32
#define v2_pow_f32                              lm2_v2_pow_f32
#define v2_clamp_f32                            lm2_v2_clamp_f32
#define v2_lerp_f32                             lm2_v2_lerp_f32
#define v2_smoothstep_f32                       lm2_v2_smoothstep_f32
#define v2_alpha_f32                            lm2_v2_alpha_f32
#define v2_make_f32                             lm2_v2_make_f32
#define v2_splat_f32                            lm2_v2_splat_f32
#define v2_zero_f32                             lm2_v2_zero_f32
#define v2_dot_f32                              lm2_v2_dot_f32
#define v2_cross_f32                            lm2_v2_cross_f32
#define v2_cross3_f32                           lm2_v2_cross3_f32
#define v2_length_f32                           lm2_v2_length_f32
#define v2_length_sq_f32                        lm2_v2_length_sq_f32
#define v2_distance_f32                         lm2_v2_distance_f32
#define v2_distance_sq_f32                      lm2_v2_distance_sq_f32
#define v2_normalize_f32                        lm2_v2_normalize_f32
#define v2_angle_f32                            lm2_v2_angle_f32
#define v2_rotate_f32                           lm2_v2_rotate_f32
#define v2_rotate_around_f32                    lm2_v2_rotate_around_f32
#define v2_perp_ccw_f32                         lm2_v2_perp_ccw_f32
#define v2_perp_cw_f32                          lm2_v2_perp_cw_f32
#define v2_reflect_f32                          lm2_v2_reflect_f32
#define v2_project_f32                          lm2_v2_project_f32
#define v3_add_f64                              lm2_v3_add_f64
#define v3_sub_f64                              lm2_v3_sub_f64
#define v3_mul_f64                              lm2_v3_mul_f64
#define v3_div_f64                              lm2_v3_div_f64
#define v3_add_s_f64                            lm2_v3_add_s_f64
#define v3_sub_s_f64                            lm2_v3_sub_s_f64
#define v3_mul_s_f64                            lm2_v3_mul_s_f64
#define v3_div_s_f64                            lm2_v3_div_s_f64
#define v3_neg_f64                              lm2_v3_neg_f64
#define v3_floor_f64                            lm2_v3_floor_f64
#define v3_ceil_f64                             lm2_v3_ceil_f64
#define v3_round_f64                            lm2_v3_round_f64
#define v3_trunc_f64                            lm2_v3_trunc_f64
#define v3_abs_f64                              lm2_v3_abs_f64
#define v3_sign_f64                             lm2_v3_sign_f64
#define v3_sign0_f64                            lm2_v3_sign0_f64
#define v3_saturate_f64                         lm2_v3_saturate_f64
#define v3_fract_f64                            lm2_v3_fract_f64
#define v3_sqrt_f64                             lm2_v3_sqrt_f64
#define v3_min_f64                              lm2_v3_min_f64
#define v3_max_f64                              lm2_v3_max_f64
#define v3_clamp_f64                            lm2_v3_clamp_f64
#define v3_lerp_f64                             lm2_v3_lerp_f64
#define v3_make_f64                             lm2_v3_make_f64
#define v3_splat_f64                            lm2_v3_splat_f64
#define v3_zero_f64                             lm2_v3_zero_f64
#define v3_dot_f64                              lm2_v3_dot_f64
#define v3_cross_f64                            lm2_v3_cross_f64
#define v3_length_f64                           lm2_v3_length_f64
#define v3_length_sq_f64                        lm2_v3_length_sq_f64
#define v3_distance_f64                         lm2_v3_distance_f64
#define v3_distance_sq_f64                      lm2_v3_distance_sq_f64
#define v3_normalize_f64                        lm2_v3_normalize_f64
#define v3_angle_f64                            lm2_v3_angle_f64
#define v3_reflect_f64                          lm2_v3_reflect_f64
#define v3_project_f64                          lm2_v3_project_f64
#define v3_add_f32                              lm2_v3_add_f32
#define v3_sub_f32                              lm2_v3_sub_f32
#define v3_mul_f32                              lm2_v3_mul_f32
#define v3_div_f32                              lm2_v3_div_f32
#define v3_add_s_f32                            lm2_v3_add_s_f32
#define v3_sub_s_f32                            lm2_v3_sub_s_f32
#define v3_mul_s_f32                            lm2_v3_mul_s_f32
#define v3_div_s_f32                            lm2_v3_div_s_f32
#define v3_neg_f32                              lm2_v3_neg_f32
#define v3_floor_f32                            lm2_v3_floor_f32
#define v3_ceil_f32                             lm2_v3_ceil_f32
#define v3_round_f32                            lm2_v3_round_f32
#define v3_trunc_f32                            lm2_v3_trunc_f32
#define v3_abs_f32                              lm2_v3_abs_f32
#define v3_sign_f32                             lm2_v3_sign_f32
#define v3_sign0_f32                            lm2_v3_sign0_f32
#define v3_saturate_f32                         lm2_v3_saturate_f32
#define v3_fract_f32                            lm2_v3_fract_f32
#define v3_sqrt_f32                             lm2_v3_sqrt_f32
#define v3_min_f32                              lm2_v3_min_f32
#define v3_max_f32                              lm2_v3_max_f32
#define v3_clamp_f32                            lm2_v3_clamp_f32
#define v3_lerp_f32                             lm2_v3_lerp_f32
#define v3_make_f32                             lm2_v3_make_f32
#define v3_splat_f32                            lm2_v3_splat_f32
#define v3_zero_f32                             lm2_v3_zero_f32
#define v3_dot_f32                              lm2_v3_dot_f32
#define v3_cross_f32                            lm2_v3_cross_f32
#define v3_length_f32                           lm2_v3_length_f32
#define v3_length_sq_f32                        lm2_v3_length_sq_f32
#define v3_distance_f32                         lm2_v3_distance_f32
#define v3_distance_sq_f32                      lm2_v3_distance_sq_f32
#define v3_normalize_f32                        lm2_v3_normalize_f32
#define v3_angle_f32                            lm2_v3_angle_f32
#define v3_reflect_f32                          lm2_v3_reflect_f32
#define v3_project_f32                          lm2_v3_project_f32
#define v4_add_f64                              lm2_v4_add_f64
#define v4_sub_f64                              lm2_v4_sub_f64
#define v4_mul_f64                              lm2_v4_mul_f64
#define v4_div_f64                              lm2_v4_div_f64
#define v4_add_s_f64                            lm2_v4_add_s_f64
#define v4_sub_s_f64                            lm2_v4_sub_s_f64
#define v4_mul_s_f64                            lm2_v4_mul_s_f64
#define v4_div_s_f64                            lm2_v4_div_s_f64
#define v4_neg_f64                              lm2_v4_neg_f64
#define v4_floor_f64                            lm2_v4_floor_f64
#define v4_ceil_f64                             lm2_v4_ceil_f64
#define v4_round_f64                            lm2_v4_round_f64
#define v4_trunc_f64                            lm2_v4_trunc_f64
#define v4_abs_f64                              lm2_v4_abs_f64
#define v4_sign_f64                             lm2_v4_sign_f64
#define v4_sign0_f64                            lm2_v4_sign0_f64
#define v4_saturate_f64                         lm2_v4_saturate_f64
#define v4_fract_f64                            lm2_v4_fract_f64
#define v4_sqrt_f64                             lm2_v4_sqrt_f64
#define v4_min_f64                              lm2_v4_min_f64
#define v4_max_f64                              lm2_v4_max_f64
#define v4_clamp_f64                            lm2_v4_clamp_f64
#define v4_lerp_f64                             lm2_v4_lerp_f64
#define v4_make_f64                             lm2_v4_make_f64
#define v4_splat_f64                            lm2_v4_splat_f64
#define v4_zero_f64                             lm2_v4_zero_f64
#define v4_dot_f64                              lm2_v4_dot_f64
#define v4_length_f64                           lm2_v4_length_f64
#define v4_length_sq_f64                        lm2_v4_length_sq_f64
#define v4_distance_f64                         lm2_v4_distance_f64
#define v4_distance_sq_f64                      lm2_v4_distance_sq_f64
#define v4_normalize_f64                        lm2_v4_normalize_f64
#define v4_add_f32                              lm2_v4_add_f32
#define v4_sub_f32                              lm2_v4_sub_f32
#define v4_mul_f32                              lm2_v4_mul_f32
#define v4_div_f32                              lm2_v4_div_f32
#define v4_add_s_f32                            lm2_v4_add_s_f32
#define v4_sub_s_f32                            lm2_v4_sub_s_f32
#define v4_mul_s_f32                            lm2_v4_mul_s_f32
#define v4_div_s_f32                            lm2_v4_div_s_f32
#define v4_neg_f32                              lm2_v4_neg_f32
#define v4_floor_f32                            lm2_v4_floor_f32
#define v4_ceil_f32                             lm2_v4_ceil_f32
#define v4_round_f32                            lm2_v4_round_f32
#define v4_trunc_f32                            lm2_v4_trunc_f32
#define v4_abs_f32                              lm2_v4_abs_f32
#define v4_sign_f32                             lm2_v4_sign_f32
#define v4_sign0_f32                            lm2_v4_sign0_f32
#define v4_saturate_f32                         lm2_v4_saturate_f32
#define v4_fract_f32                            lm2_v4_fract_f32
#define v4_sqrt_f32                             lm2_v4_sqrt_f32
#define v4_min_f32                              lm2_v4_min_f32
#define v4_max_f32                              lm2_v4_max_f32
#define v4_clamp_f32                            lm2_v4_clamp_f32
#define v4_lerp_f32                             lm2_v4_lerp_f32
#define v4_make_f32                             lm2_v4_make_f32
#define v4_splat_f32                            lm2_v4_splat_f32
#define v4_zero_f32                             lm2_v4_zero_f32
#define v4_dot_f32                              lm2_v4_dot_f32
#define v4_length_f32                           lm2_v4_length_f32
#define v4_length_sq_f32                        lm2_v4_length_sq_f32
#define v4_distance_f32                         lm2_v4_distance_f32
#define v4_distance_sq_f32                      lm2_v4_distance_sq_f32
#define v4_normalize_f32                        lm2_v4_normalize_f32
#define r2_f64                                  lm2_r2_f64
#define r2_f32                                  lm2_r2_f32
#define r2_i64                                  lm2_r2_i64
#define r2_i32                                  lm2_r2_i32
#define r2_i16                                  lm2_r2_i16
#define r2_i8                                   lm2_r2_i8
#define r2_u64                                  lm2_r2_u64
#define r2_u32                                  lm2_r2_u32
#define r2_u16                                  lm2_r2_u16
#define r2_u8                                   lm2_r2_u8
#define r2                                      lm2_r2
#define r3_f64                                  lm2_r3_f64
#define r3_f32                                  lm2_r3_f32
#define r3_i64                                  lm2_r3_i64
#define r3_i32                                  lm2_r3_i32
#define r3_i16                                  lm2_r3_i16
#define r3_i8                                   lm2_r3_i8
#define r3_u64                                  lm2_r3_u64
#define r3_u32                                  lm2_r3_u32
#define r3_u16                                  lm2_r3_u16
#define r3_u8                                   lm2_r3_u8
#define r3                                      lm2_r3
#define r4_f64                                  lm2_r4_f64
#define r4_f32                                  lm2_r4_f32
#define r4_i64                                  lm2_r4_i64
#define r4_i32                                  lm2_r4_i32
#define r4_i16                                  lm2_r4_i16
#define r4_i8                                   lm2_r4_i8
#define r4_u64                                  lm2_r4_u64
#define r4_u32                                  lm2_r4_u32
#define r4_u16                                  lm2_r4_u16
#define r4_u8                                   lm2_r4_u8
#define r4                                      lm2_r4
#define r2_make_f64                             lm2_r2_make_f64
#define r2_make_from_min_max_f64                lm2_r2_make_from_min_max_f64
#define r2_make_from_pos_size_f64               lm2_r2_make_from_pos_size_f64
#define r2_make_from_center_size_f64            lm2_r2_make_from_center_size_f64
#define r2_get_min_f64                          lm2_r2_get_min_f64
#define r2_get_max_f64                          lm2_r2_get_max_f64
#define r2_get_size_f64                         lm2_r2_get_size_f64
#define r2_get_center_f64                       lm2_r2_get_center_f64
#define r2_normalize_f64                        lm2_r2_normalize_f64
#define r2_translate_f64                        lm2_r2_translate_f64
#define r2_expand_f64                           lm2_r2_expand_f64
#define r2_scale_f64                            lm2_r2_scale_f64
#define r2_union_f64                            lm2_r2_union_f64
#define r2_intersection_f64                     lm2_r2_intersection_f64
#define r2_contains_point_f64                   lm2_r2_contains_point_f64
#define r2_overlaps_f64                         lm2_r2_overlaps_f64
#define r2_area_f64                             lm2_r2_area_f64
#define r2_lerp_f64                             lm2_r2_lerp_f64
#define r2_make_f32                             lm2_r2_make_f32
#define r2_make_from_min_max_f32                lm2_r2_make_from_min_max_f32
#define r2_make_from_pos_size_f32               lm2_r2_make_from_pos_size_f32
#define r2_make_from_center_size_f32            lm2_r2_make_from_center_size_f32
#define r2_get_min_f32                          lm2_r2_get_min_f32
#define r2_get_max_f32                          lm2_r2_get_max_f32
#define r2_get_size_f32                         lm2_r2_get_size_f32
#define r2_get_center_f32                       lm2_r2_get_center_f32
#define r2_normalize_f32                        lm2_r2_normalize_f32
#define r2_translate_f32                        lm2_r2_translate_f32
#define r2_expand_f32                           lm2_r2_expand_f32
#define r2_scale_f32                            lm2_r2_scale_f32
#define r2_union_f32                            lm2_r2_union_f32
#define r2_intersection_f32                     lm2_r2_intersection_f32
#define r2_contains_point_f32                   lm2_r2_contains_point_f32
#define r2_overlaps_f32                         lm2_r2_overlaps_f32
#define r2_area_f32                             lm2_r2_area_f32
#define r2_lerp_f32                             lm2_r2_lerp_f32
#define r3_make_f64                             lm2_r3_make_f64
#define r3_make_from_min_max_f64                lm2_r3_make_from_min_max_f64
#define r3_get_min_f64                          lm2_r3_get_min_f64
#define r3_get_max_f64                          lm2_r3_get_max_f64
#define r3_get_size_f64                         lm2_r3_get_size_f64
#define r3_get_center_f64                       lm2_r3_get_center_f64
#define r3_normalize_f64                        lm2_r3_normalize_f64
#define r3_translate_f64                        lm2_r3_translate_f64
#define r3_expand_f64                           lm2_r3_expand_f64
#define r3_scale_f64                            lm2_r3_scale_f64
#define r3_union_f64                            lm2_r3_union_f64
#define r3_intersection_f64                     lm2_r3_intersection_f64
#define r3_contains_point_f64                   lm2_r3_contains_point_f64
#define r3_overlaps_f64                         lm2_r3_overlaps_f64
#define r3_volume_f64                           lm2_r3_volume_f64
#define r3_make_f32                             lm2_r3_make_f32
#define r3_make_from_min_max_f32                lm2_r3_make_from_min_max_f32
#define r3_get_min_f32                          lm2_r3_get_min_f32
#define r3_get_max_f32                          lm2_r3_get_max_f32
#define r3_get_size_f32                         lm2_r3_get_size_f32
#define r3_get_center_f32                       lm2_r3_get_center_f32
#define r3_normalize_f32                        lm2_r3_normalize_f32
#define r3_translate_f32                        lm2_r3_translate_f32
#define r3_expand_f32                           lm2_r3_expand_f32
#define r3_scale_f32                            lm2_r3_scale_f32
#define r3_union_f32                            lm2_r3_union_f32
#define r3_intersection_f32                     lm2_r3_intersection_f32
#define r3_contains_point_f32                   lm2_r3_contains_point_f32
#define r3_overlaps_f32                         lm2_r3_overlaps_f32
#define r3_volume_f32                           lm2_r3_volume_f32
#define m3x2_f64                                lm2_m3x2_f64
#define m3x2_f32                                lm2_m3x2_f32
#define m3x2                                    lm2_m3x2
#define m3x3_f64                                lm2_m3x3_f64
#define m3x3_f32                                lm2_m3x3_f32
#define m3x3                                    lm2_m3x3
#define m4x4_f64                                lm2_m4x4_f64
#define m4x4_f32                                lm2_m4x4_f32
#define m4x4                                    lm2_m4x4
#define m3x2_identity_f64                       lm2_m3x2_identity_f64
#define m3x2_zero_f64                           lm2_m3x2_zero_f64
#define m3x2_from_translation_f64               lm2_m3x2_from_translation_f64
#define m3x2_from_rotation_f64                  lm2_m3x2_from_rotation_f64
#define m3x2_from_scale_f64                     lm2_m3x2_from_scale_f64
#define m3x2_from_trs_f64                       lm2_m3x2_from_trs_f64
#define m3x2_mul_f64                            lm2_m3x2_mul_f64
#define m3x2_transform_point_f64                lm2_m3x2_transform_point_f64
#define m3x2_transform_vector_f64               lm2_m3x2_transform_vector_f64
#define m3x2_translate_f64                      lm2_m3x2_translate_f64
#define m3x2_rotate_f64                         lm2_m3x2_rotate_f64
#define m3x2_scale_f64                          lm2_m3x2_scale_f64
#define m3x2_inverse_f64                        lm2_m3x2_inverse_f64
#define m3x2_determinant_f64                    lm2_m3x2_determinant_f64
#define m3x2_identity_f32                       lm2_m3x2_identity_f32
#define m3x2_zero_f32                           lm2_m3x2_zero_f32
#define m3x2_from_translation_f32               lm2_m3x2_from_translation_f32
#define m3x2_from_rotation_f32                  lm2_m3x2_from_rotation_f32
#define m3x2_from_scale_f32                     lm2_m3x2_from_scale_f32
#define m3x2_from_trs_f32                       lm2_m3x2_from_trs_f32
#define m3x2_mul_f32                            lm2_m3x2_mul_f32
#define m3x2_transform_point_f32                lm2_m3x2_transform_point_f32
#define m3x2_transform_vector_f32               lm2_m3x2_transform_vector_f32
#define m3x2_translate_f32                      lm2_m3x2_translate_f32
#define m3x2_rotate_f32                         lm2_m3x2_rotate_f32
#define m3x2_scale_f32                          lm2_m3x2_scale_f32
#define m3x2_inverse_f32                        lm2_m3x2_inverse_f32
#define m3x2_determinant_f32                    lm2_m3x2_determinant_f32
#define m3x3_identity_f64                       lm2_m3x3_identity_f64
#define m3x3_zero_f64                           lm2_m3x3_zero_f64
#define m3x3_from_rotation_x_f64                lm2_m3x3_from_rotation_x_f64
#define m3x3_from_rotation_y_f64                lm2_m3x3_from_rotation_y_f64
#define m3x3_from_rotation_z_f64                lm2_m3x3_from_rotation_z_f64
#define m3x3_mul_f64                            lm2_m3x3_mul_f64
#define m3x3_transform_f64                      lm2_m3x3_transform_f64
#define m3x3_transpose_f64                      lm2_m3x3_transpose_f64
#define m3x3_inverse_f64                        lm2_m3x3_inverse_f64
#define m3x3_determinant_f64                    lm2_m3x3_determinant_f64
#define m3x3_identity_f32                       lm2_m3x3_identity_f32
#define m3x3_zero_f32                           lm2_m3x3_zero_f32
#define m3x3_from_rotation_x_f32                lm2_m3x3_from_rotation_x_f32
#define m3x3_from_rotation_y_f32                lm2_m3x3_from_rotation_y_f32
#define m3x3_from_rotation_z_f32                lm2_m3x3_from_rotation_z_f32
#define m3x3_mul_f32                            lm2_m3x3_mul_f32
#define m3x3_transform_f32                      lm2_m3x3_transform_f32
#define m3x3_transpose_f32                      lm2_m3x3_transpose_f32
#define m3x3_inverse_f32                        lm2_m3x3_inverse_f32
#define m3x3_determinant_f32                    lm2_m3x3_determinant_f32
#define m4x4_identity_f64                       lm2_m4x4_identity_f64
#define m4x4_zero_f64                           lm2_m4x4_zero_f64
#define m4x4_from_translation_f64               lm2_m4x4_from_translation_f64
#define m4x4_from_rotation_x_f64                lm2_m4x4_from_rotation_x_f64
#define m4x4_from_rotation_y_f64                lm2_m4x4_from_rotation_y_f64
#define m4x4_from_rotation_z_f64                lm2_m4x4_from_rotation_z_f64
#define m4x4_from_quaternion_f64                lm2_m4x4_from_quaternion_f64
#define m4x4_from_scale_f64                     lm2_m4x4_from_scale_f64
#define m4x4_from_trs_f64                       lm2_m4x4_from_trs_f64
#define m4x4_mul_f64                            lm2_m4x4_mul_f64
#define m4x4_transform_point_f64                lm2_m4x4_transform_point_f64
#define m4x4_transform_vector_f64               lm2_m4x4_transform_vector_f64
#define m4x4_translate_f64                      lm2_m4x4_translate_f64
#define m4x4_rotate_x_f64                       lm2_m4x4_rotate_x_f64
#define m4x4_rotate_y_f64                       lm2_m4x4_rotate_y_f64
#define m4x4_rotate_z_f64                       lm2_m4x4_rotate_z_f64
#define m4x4_scale_f64                          lm2_m4x4_scale_f64
#define m4x4_transpose_f64                      lm2_m4x4_transpose_f64
#define m4x4_inverse_f64                        lm2_m4x4_inverse_f64
#define m4x4_determinant_f64                    lm2_m4x4_determinant_f64
#define m4x4_look_at_f64                        lm2_m4x4_look_at_f64
#define m4x4_perspective_f64                    lm2_m4x4_perspective_f64
#define m4x4_orthographic_f64                   lm2_m4x4_orthographic_f64
#define m4x4_identity_f32                       lm2_m4x4_identity_f32
#define m4x4_zero_f32                           lm2_m4x4_zero_f32
#define m4x4_from_translation_f32               lm2_m4x4_from_translation_f32
#define m4x4_from_rotation_x_f32                lm2_m4x4_from_rotation_x_f32
#define m4x4_from_rotation_y_f32                lm2_m4x4_from_rotation_y_f32
#define m4x4_from_rotation_z_f32                lm2_m4x4_from_rotation_z_f32
#define m4x4_from_quaternion_f32                lm2_m4x4_from_quaternion_f32
#define m4x4_from_scale_f32                     lm2_m4x4_from_scale_f32
#define m4x4_from_trs_f32                       lm2_m4x4_from_trs_f32
#define m4x4_mul_f32                            lm2_m4x4_mul_f32
#define m4x4_transform_point_f32                lm2_m4x4_transform_point_f32
#define m4x4_transform_vector_f32               lm2_m4x4_transform_vector_f32
#define m4x4_translate_f32                      lm2_m4x4_translate_f32
#define m4x4_rotate_x_f32                       lm2_m4x4_rotate_x_f32
#define m4x4_rotate_y_f32                       lm2_m4x4_rotate_y_f32
#define m4x4_rotate_z_f32                       lm2_m4x4_rotate_z_f32
#define m4x4_scale_f32                          lm2_m4x4_scale_f32
#define m4x4_transpose_f32                      lm2_m4x4_transpose_f32
#define m4x4_inverse_f32                        lm2_m4x4_inverse_f32
#define m4x4_determinant_f32                    lm2_m4x4_determinant_f32
#define m4x4_look_at_f32                        lm2_m4x4_look_at_f32
#define m4x4_perspective_f32                    lm2_m4x4_perspective_f32
#define m4x4_orthographic_f32                   lm2_m4x4_orthographic_f32
#define circle_f64                              lm2_circle_f64
#define circle_f32                              lm2_circle_f32
#define circle                                  lm2_circle
#define circle_make_f64                         lm2_circle_make_f64
#define circle_unit_f64                         lm2_circle_unit_f64
#define circle_area_f64                         lm2_circle_area_f64
#define circle_circumference_f64                lm2_circle_circumference_f64
#define circle_contains_point_f64               lm2_circle_contains_point_f64
#define circles_overlap_f64                     lm2_circles_overlap_f64
#define circle_translate_f64                    lm2_circle_translate_f64
#define circle_scale_f64                        lm2_circle_scale_f64
#define circle_make_f32                         lm2_circle_make_f32
#define circle_unit_f32                         lm2_circle_unit_f32
#define circle_area_f32                         lm2_circle_area_f32
#define circle_circumference_f32                lm2_circle_circumference_f32
#define circle_contains_point_f32               lm2_circle_contains_point_f32
#define circles_overlap_f32                     lm2_circles_overlap_f32
#define circle_translate_f32                    lm2_circle_translate_f32
#define circle_scale_f32                        lm2_circle_scale_f32
#define aabb2                                   lm2_aabb2
#define aabb2_f32                               lm2_aabb2_f32
#define aabb2_f64                               lm2_aabb2_f64
#define aabb2_i16                               lm2_aabb2_i16
#define aabb2_i32                               lm2_aabb2_i32
#define aabb2_i64                               lm2_aabb2_i64
#define aabb2_i8                                lm2_aabb2_i8
#define aabb2_u16                               lm2_aabb2_u16
#define aabb2_u32                               lm2_aabb2_u32
#define aabb2_u64                               lm2_aabb2_u64
#define aabb2_u8                                lm2_aabb2_u8
#define capsule2                                lm2_capsule2
#define capsule2_f32                            lm2_capsule2_f32
#define capsule2_f64                            lm2_capsule2_f64
#define capsule2_area_f32                       lm2_capsule2_area_f32
#define capsule2_area_f64                       lm2_capsule2_area_f64
#define capsule2_center_f32                     lm2_capsule2_center_f32
#define capsule2_center_f64                     lm2_capsule2_center_f64
#define capsule2_contains_point_f32             lm2_capsule2_contains_point_f32
#define capsule2_contains_point_f64             lm2_capsule2_contains_point_f64
#define capsule2_from_center_f32                lm2_capsule2_from_center_f32
#define capsule2_from_center_f64                lm2_capsule2_from_center_f64
#define capsule2_length_f32                     lm2_capsule2_length_f32
#define capsule2_length_f64                     lm2_capsule2_length_f64
#define capsule2_make_coords_f32                lm2_capsule2_make_coords_f32
#define capsule2_make_coords_f64                lm2_capsule2_make_coords_f64
#define capsule2_make_f32                       lm2_capsule2_make_f32
#define capsule2_make_f64                       lm2_capsule2_make_f64
#define capsule2_perimeter_f32                  lm2_capsule2_perimeter_f32
#define capsule2_perimeter_f64                  lm2_capsule2_perimeter_f64
#define capsule2_scale_radius_f32               lm2_capsule2_scale_radius_f32
#define capsule2_scale_radius_f64               lm2_capsule2_scale_radius_f64
#define capsule2_total_length_f32               lm2_capsule2_total_length_f32
#define capsule2_total_length_f64               lm2_capsule2_total_length_f64
#define capsule2_translate_f32                  lm2_capsule2_translate_f32
#define capsule2_translate_f64                  lm2_capsule2_translate_f64
#define capsule2s_overlap_f32                   lm2_capsule2s_overlap_f32
#define capsule2s_overlap_f64                   lm2_capsule2s_overlap_f64
#define corner2                                 lm2_corner2
#define edge2                                   lm2_edge2
#define edge2_f32                               lm2_edge2_f32
#define edge2_f64                               lm2_edge2_f64
#define edge2_from_plane_f32                    lm2_edge2_from_plane_f32
#define edge2_from_plane_f64                    lm2_edge2_from_plane_f64
#define edge2_from_ray_f32                      lm2_edge2_from_ray_f32
#define edge2_from_ray_f64                      lm2_edge2_from_ray_f64
#define edge2_length_f32                        lm2_edge2_length_f32
#define edge2_length_f64                        lm2_edge2_length_f64
#define edge2_length_sq_f32                     lm2_edge2_length_sq_f32
#define edge2_length_sq_f64                     lm2_edge2_length_sq_f64
#define edge2_make_coords_f32                   lm2_edge2_make_coords_f32
#define edge2_make_coords_f64                   lm2_edge2_make_coords_f64
#define edge2_make_f32                          lm2_edge2_make_f32
#define edge2_make_f64                          lm2_edge2_make_f64
#define edge2_result                            lm2_edge2_result
#define edge2_result_f32                        lm2_edge2_result_f32
#define edge2_result_f64                        lm2_edge2_result_f64
#define edge2_to_edge2_distance_sq_f32          lm2_edge2_to_edge2_distance_sq_f32
#define edge2_to_edge2_distance_sq_f64          lm2_edge2_to_edge2_distance_sq_f64
#define edges2_equal_f32                        lm2_edges2_equal_f32
#define edges2_equal_f64                        lm2_edges2_equal_f64
#define edges2_intersect_f32                    lm2_edges2_intersect_f32
#define edges2_intersect_f64                    lm2_edges2_intersect_f64
#define point_to_edge2_distance_sq_f32          lm2_point_to_edge2_distance_sq_f32
#define point_to_edge2_distance_sq_f64          lm2_point_to_edge2_distance_sq_f64
#define points2_equal_f32                       lm2_points2_equal_f32
#define points2_equal_f64                       lm2_points2_equal_f64
#define align                                   lm2_align
#define manifold                                lm2_manifold
#define manifold_f32                            lm2_manifold_f32
#define manifold_f64                            lm2_manifold_f64
#define manifold_aabb_to_aabb_f32               lm2_manifold_aabb_to_aabb_f32
#define manifold_aabb_to_aabb_f64               lm2_manifold_aabb_to_aabb_f64
#define manifold_aabb_to_capsule_f32            lm2_manifold_aabb_to_capsule_f32
#define manifold_aabb_to_capsule_f64            lm2_manifold_aabb_to_capsule_f64
#define manifold_aabb_to_plane_f32              lm2_manifold_aabb_to_plane_f32
#define manifold_aabb_to_plane_f64              lm2_manifold_aabb_to_plane_f64
#define manifold_aabb_to_polygon_f32            lm2_manifold_aabb_to_polygon_f32
#define manifold_aabb_to_polygon_f64            lm2_manifold_aabb_to_polygon_f64
#define manifold_capsule_to_capsule_f32         lm2_manifold_capsule_to_capsule_f32
#define manifold_capsule_to_capsule_f64         lm2_manifold_capsule_to_capsule_f64
#define manifold_capsule_to_plane_f32           lm2_manifold_capsule_to_plane_f32
#define manifold_capsule_to_plane_f64           lm2_manifold_capsule_to_plane_f64
#define manifold_capsule_to_polygon_f32         lm2_manifold_capsule_to_polygon_f32
#define manifold_capsule_to_polygon_f64         lm2_manifold_capsule_to_polygon_f64
#define manifold_circle_to_aabb_f32             lm2_manifold_circle_to_aabb_f32
#define manifold_circle_to_aabb_f64             lm2_manifold_circle_to_aabb_f64
#define manifold_circle_to_capsule_f32          lm2_manifold_circle_to_capsule_f32
#define manifold_circle_to_capsule_f64          lm2_manifold_circle_to_capsule_f64
#define manifold_circle_to_circle_f32           lm2_manifold_circle_to_circle_f32
#define manifold_circle_to_circle_f64           lm2_manifold_circle_to_circle_f64
#define manifold_circle_to_plane_f32            lm2_manifold_circle_to_plane_f32
#define manifold_circle_to_plane_f64            lm2_manifold_circle_to_plane_f64
#define manifold_circle_to_polygon_f32          lm2_manifold_circle_to_polygon_f32
#define manifold_circle_to_polygon_f64          lm2_manifold_circle_to_polygon_f64
#define manifold_polygon_to_plane_f32           lm2_manifold_polygon_to_plane_f32
#define manifold_polygon_to_plane_f64           lm2_manifold_polygon_to_plane_f64
#define manifold_polygon_to_polygon_f32         lm2_manifold_polygon_to_polygon_f32
#define manifold_polygon_to_polygon_f64         lm2_manifold_polygon_to_polygon_f64
#define manifold_shape_to_shape_f32             lm2_manifold_shape_to_shape_f32
#define manifold_shape_to_shape_f64             lm2_manifold_shape_to_shape_f64
#define manifold_triangle_to_aabb_f32           lm2_manifold_triangle_to_aabb_f32
#define manifold_triangle_to_aabb_f64           lm2_manifold_triangle_to_aabb_f64
#define manifold_triangle_to_capsule_f32        lm2_manifold_triangle_to_capsule_f32
#define manifold_triangle_to_capsule_f64        lm2_manifold_triangle_to_capsule_f64
#define manifold_triangle_to_circle_f32         lm2_manifold_triangle_to_circle_f32
#define manifold_triangle_to_circle_f64         lm2_manifold_triangle_to_circle_f64
#define manifold_triangle_to_plane_f32          lm2_manifold_triangle_to_plane_f32
#define manifold_triangle_to_plane_f64          lm2_manifold_triangle_to_plane_f64
#define manifold_triangle_to_polygon_f32        lm2_manifold_triangle_to_polygon_f32
#define manifold_triangle_to_polygon_f64        lm2_manifold_triangle_to_polygon_f64
#define manifold_triangle_to_triangle_f32       lm2_manifold_triangle_to_triangle_f32
#define manifold_triangle_to_triangle_f64       lm2_manifold_triangle_to_triangle_f64
#define collide_aabb_to_aabb_f32                lm2_collide_aabb_to_aabb_f32
#define collide_aabb_to_aabb_f64                lm2_collide_aabb_to_aabb_f64
#define collide_aabb_to_capsule_f32             lm2_collide_aabb_to_capsule_f32
#define collide_aabb_to_capsule_f64             lm2_collide_aabb_to_capsule_f64
#define collide_aabb_to_polygon_f32             lm2_collide_aabb_to_polygon_f32
#define collide_aabb_to_polygon_f64             lm2_collide_aabb_to_polygon_f64
#define collide_capsule_to_capsule_f32          lm2_collide_capsule_to_capsule_f32
#define collide_capsule_to_capsule_f64          lm2_collide_capsule_to_capsule_f64
#define collide_capsule_to_polygon_f32          lm2_collide_capsule_to_polygon_f32
#define collide_capsule_to_polygon_f64          lm2_collide_capsule_to_polygon_f64
#define collide_circle_to_aabb_f32              lm2_collide_circle_to_aabb_f32
#define collide_circle_to_aabb_f64              lm2_collide_circle_to_aabb_f64
#define collide_circle_to_capsule_f32           lm2_collide_circle_to_capsule_f32
#define collide_circle_to_capsule_f64           lm2_collide_circle_to_capsule_f64
#define collide_circle_to_circle_f32            lm2_collide_circle_to_circle_f32
#define collide_circle_to_circle_f64            lm2_collide_circle_to_circle_f64
#define collide_circle_to_polygon_f32           lm2_collide_circle_to_polygon_f32
#define collide_circle_to_polygon_f64           lm2_collide_circle_to_polygon_f64
#define collide_polygon_to_polygon_f32          lm2_collide_polygon_to_polygon_f32
#define collide_polygon_to_polygon_f64          lm2_collide_polygon_to_polygon_f64
#define collide_triangle_to_aabb_f32            lm2_collide_triangle_to_aabb_f32
#define collide_triangle_to_aabb_f64            lm2_collide_triangle_to_aabb_f64
#define collide_triangle_to_capsule_f32         lm2_collide_triangle_to_capsule_f32
#define collide_triangle_to_capsule_f64         lm2_collide_triangle_to_capsule_f64
#define collide_triangle_to_circle_f32          lm2_collide_triangle_to_circle_f32
#define collide_triangle_to_circle_f64          lm2_collide_triangle_to_circle_f64
#define collide_triangle_to_polygon_f32         lm2_collide_triangle_to_polygon_f32
#define collide_triangle_to_polygon_f64         lm2_collide_triangle_to_polygon_f64
#define collide_triangle_to_triangle_f32        lm2_collide_triangle_to_triangle_f32
#define collide_triangle_to_triangle_f64        lm2_collide_triangle_to_triangle_f64
#define plane2                                  lm2_plane2
#define plane2_f32                              lm2_plane2_f32
#define plane2_f64                              lm2_plane2_f64
#define plane2_closest_point_f32                lm2_plane2_closest_point_f32
#define plane2_closest_point_f64                lm2_plane2_closest_point_f64
#define plane2_contains_point_f32               lm2_plane2_contains_point_f32
#define plane2_contains_point_f64               lm2_plane2_contains_point_f64
#define plane2_distance_to_point_f32            lm2_plane2_distance_to_point_f32
#define plane2_distance_to_point_f64            lm2_plane2_distance_to_point_f64
#define plane2_flip_f32                         lm2_plane2_flip_f32
#define plane2_flip_f64                         lm2_plane2_flip_f64
#define plane2_from_point_normal_f32            lm2_plane2_from_point_normal_f32
#define plane2_from_point_normal_f64            lm2_plane2_from_point_normal_f64
#define plane2_from_points_f32                  lm2_plane2_from_points_f32
#define plane2_from_points_f64                  lm2_plane2_from_points_f64
#define plane2_make_f32                         lm2_plane2_make_f32
#define plane2_make_f64                         lm2_plane2_make_f64
#define plane2_project_point_f32                lm2_plane2_project_point_f32
#define plane2_project_point_f64                lm2_plane2_project_point_f64
#define plane2_rotate_f32                       lm2_plane2_rotate_f32
#define plane2_rotate_f64                       lm2_plane2_rotate_f64
#define plane2_side_f32                         lm2_plane2_side_f32
#define plane2_side_f64                         lm2_plane2_side_f64
#define plane2_translate_f32                    lm2_plane2_translate_f32
#define plane2_translate_f64                    lm2_plane2_translate_f64
#define plane2_x_axis_f32                       lm2_plane2_x_axis_f32
#define plane2_x_axis_f64                       lm2_plane2_x_axis_f64
#define plane2_y_axis_f32                       lm2_plane2_y_axis_f32
#define plane2_y_axis_f64                       lm2_plane2_y_axis_f64
#define polygon                                 lm2_polygon
#define polygon_f32                             lm2_polygon_f32
#define polygon_f64                             lm2_polygon_f64
#define polygon_area_f32                        lm2_polygon_area_f32
#define polygon_area_f64                        lm2_polygon_area_f64
#define polygon_bounds_f32                      lm2_polygon_bounds_f32
#define polygon_bounds_f64                      lm2_polygon_bounds_f64
#define polygon_center_f32                      lm2_polygon_center_f32
#define polygon_center_f64                      lm2_polygon_center_f64
#define polygon_centroid_f32                    lm2_polygon_centroid_f32
#define polygon_centroid_f64                    lm2_polygon_centroid_f64
#define polygon_contains_point_f32              lm2_polygon_contains_point_f32
#define polygon_contains_point_f64              lm2_polygon_contains_point_f64
#define polygon_from_triangle_f32               lm2_polygon_from_triangle_f32
#define polygon_from_triangle_f64               lm2_polygon_from_triangle_f64
#define polygon_insert_vertex_f32               lm2_polygon_insert_vertex_f32
#define polygon_insert_vertex_f64               lm2_polygon_insert_vertex_f64
#define polygon_is_ccw_f32                      lm2_polygon_is_ccw_f32
#define polygon_is_ccw_f64                      lm2_polygon_is_ccw_f64
#define polygon_is_convex_f32                   lm2_polygon_is_convex_f32
#define polygon_is_convex_f64                   lm2_polygon_is_convex_f64
#define polygon_is_quad_f32                     lm2_polygon_is_quad_f32
#define polygon_is_quad_f64                     lm2_polygon_is_quad_f64
#define polygon_is_simple_f32                   lm2_polygon_is_simple_f32
#define polygon_is_simple_f64                   lm2_polygon_is_simple_f64
#define polygon_is_triangle_f32                 lm2_polygon_is_triangle_f32
#define polygon_is_triangle_f64                 lm2_polygon_is_triangle_f64
#define polygon_make_f32                        lm2_polygon_make_f32
#define polygon_make_f64                        lm2_polygon_make_f64
#define polygon_make_rect_f32                   lm2_polygon_make_rect_f32
#define polygon_make_rect_f64                   lm2_polygon_make_rect_f64
#define polygon_make_regular_f32                lm2_polygon_make_regular_f32
#define polygon_make_regular_f64                lm2_polygon_make_regular_f64
#define polygon_make_triangle_f32               lm2_polygon_make_triangle_f32
#define polygon_make_triangle_f64               lm2_polygon_make_triangle_f64
#define polygon_max_triangle_count              lm2_polygon_max_triangle_count
#define polygon_perimeter_f32                   lm2_polygon_perimeter_f32
#define polygon_perimeter_f64                   lm2_polygon_perimeter_f64
#define polygon_place_at_center_f32             lm2_polygon_place_at_center_f32
#define polygon_place_at_center_f64             lm2_polygon_place_at_center_f64
#define polygon_remove_vertex_f32               lm2_polygon_remove_vertex_f32
#define polygon_remove_vertex_f64               lm2_polygon_remove_vertex_f64
#define polygon_reverse_winding_f32             lm2_polygon_reverse_winding_f32
#define polygon_reverse_winding_f64             lm2_polygon_reverse_winding_f64
#define polygon_rotate_f32                      lm2_polygon_rotate_f32
#define polygon_rotate_f64                      lm2_polygon_rotate_f64
#define polygon_scale_f32                       lm2_polygon_scale_f32
#define polygon_scale_f64                       lm2_polygon_scale_f64
#define polygon_signed_area_f32                 lm2_polygon_signed_area_f32
#define polygon_signed_area_f64                 lm2_polygon_signed_area_f64
#define polygon_split_by_max_vertices_f32       lm2_polygon_split_by_max_vertices_f32
#define polygon_split_by_max_vertices_f64       lm2_polygon_split_by_max_vertices_f64
#define polygon_translate_f32                   lm2_polygon_translate_f32
#define polygon_translate_f64                   lm2_polygon_translate_f64
#define polygon_triangulate_ear_clipping_f32    lm2_polygon_triangulate_ear_clipping_f32
#define polygon_triangulate_ear_clipping_f64    lm2_polygon_triangulate_ear_clipping_f64
#define polygon_validate_f32                    lm2_polygon_validate_f32
#define polygon_validate_f64                    lm2_polygon_validate_f64
#define polygon_winding_order_f32               lm2_polygon_winding_order_f32
#define polygon_winding_order_f64               lm2_polygon_winding_order_f64
#define make_convex_polygon_f32                 lm2_make_convex_polygon_f32
#define make_convex_polygon_f64                 lm2_make_convex_polygon_f64
#define compute_normals_f32                     lm2_compute_normals_f32
#define compute_normals_f64                     lm2_compute_normals_f64
#define convex_hull_f32                         lm2_convex_hull_f32
#define convex_hull_f64                         lm2_convex_hull_f64
#define winding_order                           lm2_winding_order
#define ray2                                    lm2_ray2
#define ray2_f32                                lm2_ray2_f32
#define ray2_f64                                lm2_ray2_f64
#define ray2_from_points_f32                    lm2_ray2_from_points_f32
#define ray2_from_points_f64                    lm2_ray2_from_points_f64
#define ray2_make_f32                           lm2_ray2_make_f32
#define ray2_make_f64                           lm2_ray2_make_f64
#define ray2_point_at_f32                       lm2_ray2_point_at_f32
#define ray2_point_at_f64                       lm2_ray2_point_at_f64
#define rayhit2                                 lm2_rayhit2
#define rayhit2_f32                             lm2_rayhit2_f32
#define rayhit2_f64                             lm2_rayhit2_f64
#define raycast_aabb_f32                        lm2_raycast_aabb_f32
#define raycast_aabb_f64                        lm2_raycast_aabb_f64
#define raycast_capsule2_f32                    lm2_raycast_capsule2_f32
#define raycast_capsule2_f64                    lm2_raycast_capsule2_f64
#define raycast_circle_f32                      lm2_raycast_circle_f32
#define raycast_circle_f64                      lm2_raycast_circle_f64
#define raycast_plane2_f32                      lm2_raycast_plane2_f32
#define raycast_plane2_f64                      lm2_raycast_plane2_f64
#define raycast_polygon_f32                     lm2_raycast_polygon_f32
#define raycast_polygon_f64                     lm2_raycast_polygon_f64
#define raycast_segment_f32                     lm2_raycast_segment_f32
#define raycast_segment_f64                     lm2_raycast_segment_f64
#define raycast_shape2_f32                      lm2_raycast_shape2_f32
#define raycast_shape2_f64                      lm2_raycast_shape2_f64
#define raycast_triangle2_f32                   lm2_raycast_triangle2_f32
#define raycast_triangle2_f64                   lm2_raycast_triangle2_f64
#define shape2                                  lm2_shape2
#define shape2_f32                              lm2_shape2_f32
#define shape2_f64                              lm2_shape2_f64
#define shape2_as_aabb2_f32                     lm2_shape2_as_aabb2_f32
#define shape2_as_aabb2_f64                     lm2_shape2_as_aabb2_f64
#define shape2_as_capsule_f32                   lm2_shape2_as_capsule_f32
#define shape2_as_capsule_f64                   lm2_shape2_as_capsule_f64
#define shape2_as_circle_f32                    lm2_shape2_as_circle_f32
#define shape2_as_circle_f64                    lm2_shape2_as_circle_f64
#define shape2_as_edge_f32                      lm2_shape2_as_edge_f32
#define shape2_as_edge_f64                      lm2_shape2_as_edge_f64
#define shape2_as_polygon_f32                   lm2_shape2_as_polygon_f32
#define shape2_as_polygon_f64                   lm2_shape2_as_polygon_f64
#define shape2_as_triangle_f32                  lm2_shape2_as_triangle_f32
#define shape2_as_triangle_f64                  lm2_shape2_as_triangle_f64
#define shape2_from_aabb2_f32                   lm2_shape2_from_aabb2_f32
#define shape2_from_aabb2_f64                   lm2_shape2_from_aabb2_f64
#define shape2_from_capsule_f32                 lm2_shape2_from_capsule_f32
#define shape2_from_capsule_f64                 lm2_shape2_from_capsule_f64
#define shape2_from_circle_f32                  lm2_shape2_from_circle_f32
#define shape2_from_circle_f64                  lm2_shape2_from_circle_f64
#define shape2_from_edge_f32                    lm2_shape2_from_edge_f32
#define shape2_from_edge_f64                    lm2_shape2_from_edge_f64
#define shape2_from_polygon_f32                 lm2_shape2_from_polygon_f32
#define shape2_from_polygon_f64                 lm2_shape2_from_polygon_f64
#define shape2_from_triangle_f32                lm2_shape2_from_triangle_f32
#define shape2_from_triangle_f64                lm2_shape2_from_triangle_f64
#define shape2_get_type_f32                     lm2_shape2_get_type_f32
#define shape2_get_type_f64                     lm2_shape2_get_type_f64
#define shape2_is_type_f32                      lm2_shape2_is_type_f32
#define shape2_is_type_f64                      lm2_shape2_is_type_f64
#define shape2_type                             lm2_shape2_type
#define triangle2                               lm2_triangle2
#define triangle2_f32                           lm2_triangle2_f32
#define triangle2_f64                           lm2_triangle2_f64
#define triangle2_area_f32                      lm2_triangle2_area_f32
#define triangle2_area_f64                      lm2_triangle2_area_f64
#define triangle2_classify_f32                  lm2_triangle2_classify_f32
#define triangle2_classify_f64                  lm2_triangle2_classify_f64
#define triangle2_contains_point_f32            lm2_triangle2_contains_point_f32
#define triangle2_contains_point_f64            lm2_triangle2_contains_point_f64
#define triangle2_is_degenerate_f32             lm2_triangle2_is_degenerate_f32
#define triangle2_is_degenerate_f64             lm2_triangle2_is_degenerate_f64
#define triangle2_is_equilateral_f32            lm2_triangle2_is_equilateral_f32
#define triangle2_is_equilateral_f64            lm2_triangle2_is_equilateral_f64
#define triangle2_is_isosceles_f32              lm2_triangle2_is_isosceles_f32
#define triangle2_is_isosceles_f64              lm2_triangle2_is_isosceles_f64
#define triangle2_is_right_f32                  lm2_triangle2_is_right_f32
#define triangle2_is_right_f64                  lm2_triangle2_is_right_f64
#define triangle2_is_scalene_f32                lm2_triangle2_is_scalene_f32
#define triangle2_is_scalene_f64                lm2_triangle2_is_scalene_f64
#define triangle2_list_to_indexed_mesh_f32      lm2_triangle2_list_to_indexed_mesh_f32
#define triangle2_list_to_indexed_mesh_f64      lm2_triangle2_list_to_indexed_mesh_f64
#define triangle2_list_to_indexed_mesh_size_f32 lm2_triangle2_list_to_indexed_mesh_size_f32
#define triangle2_list_to_indexed_mesh_size_f64 lm2_triangle2_list_to_indexed_mesh_size_f64
#define triangle2_list_to_vertex_array_f32      lm2_triangle2_list_to_vertex_array_f32
#define triangle2_list_to_vertex_array_f64      lm2_triangle2_list_to_vertex_array_f64
#define triangle2_list_to_vertex_array_size_f32 lm2_triangle2_list_to_vertex_array_size_f32
#define triangle2_list_to_vertex_array_size_f64 lm2_triangle2_list_to_vertex_array_size_f64
#define triangle2_make_coords_f32               lm2_triangle2_make_coords_f32
#define triangle2_make_coords_f64               lm2_triangle2_make_coords_f64
#define triangle2_make_f32                      lm2_triangle2_make_f32
#define triangle2_make_f64                      lm2_triangle2_make_f64
#define triangle2_overlaps_f32                  lm2_triangle2_overlaps_f32
#define triangle2_overlaps_f64                  lm2_triangle2_overlaps_f64
#define triangle2_perimeter_f32                 lm2_triangle2_perimeter_f32
#define triangle2_perimeter_f64                 lm2_triangle2_perimeter_f64
#define triangle2_shared_edge_f32               lm2_triangle2_shared_edge_f32
#define triangle2_shared_edge_f64               lm2_triangle2_shared_edge_f64
#define triangle2_signed_area_f32               lm2_triangle2_signed_area_f32
#define triangle2_signed_area_f64               lm2_triangle2_signed_area_f64
#define triangle2_type                          lm2_triangle2_type
#define triangle2_winding_f32                   lm2_triangle2_winding_f32
#define triangle2_winding_f64                   lm2_triangle2_winding_f64
#define indexed_mesh_size                       lm2_indexed_mesh_size
#define indexed_mesh_to_triangle_list_f32       lm2_indexed_mesh_to_triangle_list_f32
#define indexed_mesh_to_triangle_list_f64       lm2_indexed_mesh_to_triangle_list_f64
#define indexed_mesh_to_triangle_list_size_f32  lm2_indexed_mesh_to_triangle_list_size_f32
#define indexed_mesh_to_triangle_list_size_f64  lm2_indexed_mesh_to_triangle_list_size_f64
#define vertex_array_to_triangle_list_f32       lm2_vertex_array_to_triangle_list_f32
#define vertex_array_to_triangle_list_f64       lm2_vertex_array_to_triangle_list_f64
#define vertex_array_to_triangle_list_size_f32  lm2_vertex_array_to_triangle_list_size_f32
#define vertex_array_to_triangle_list_size_f64  lm2_vertex_array_to_triangle_list_size_f64
#define aabb3                                   lm2_aabb3
#define aabb3_f32                               lm2_aabb3_f32
#define aabb3_f64                               lm2_aabb3_f64
#define aabb3_i16                               lm2_aabb3_i16
#define aabb3_i32                               lm2_aabb3_i32
#define aabb3_i64                               lm2_aabb3_i64
#define aabb3_i8                                lm2_aabb3_i8
#define aabb3_u16                               lm2_aabb3_u16
#define aabb3_u32                               lm2_aabb3_u32
#define aabb3_u64                               lm2_aabb3_u64
#define aabb3_u8                                lm2_aabb3_u8
#define aabb3_contains_point_f32                lm2_aabb3_contains_point_f32
#define aabb3_contains_point_f64                lm2_aabb3_contains_point_f64
#define aabb3_depth_f32                         lm2_aabb3_depth_f32
#define aabb3_depth_f64                         lm2_aabb3_depth_f64
#define aabb3_diagonal_f32                      lm2_aabb3_diagonal_f32
#define aabb3_diagonal_f64                      lm2_aabb3_diagonal_f64
#define aabb3_expand_f32                        lm2_aabb3_expand_f32
#define aabb3_expand_f64                        lm2_aabb3_expand_f64
#define aabb3_face                              lm2_aabb3_face
#define aabb3_face_center_f32                   lm2_aabb3_face_center_f32
#define aabb3_face_center_f64                   lm2_aabb3_face_center_f64
#define aabb3_face_normal_f32                   lm2_aabb3_face_normal_f32
#define aabb3_face_normal_f64                   lm2_aabb3_face_normal_f64
#define aabb3_from_center_extents_f32           lm2_aabb3_from_center_extents_f32
#define aabb3_from_center_extents_f64           lm2_aabb3_from_center_extents_f64
#define aabb3_from_center_size_f32              lm2_aabb3_from_center_size_f32
#define aabb3_from_center_size_f64              lm2_aabb3_from_center_size_f64
#define aabb3_from_min_max_f32                  lm2_aabb3_from_min_max_f32
#define aabb3_from_min_max_f64                  lm2_aabb3_from_min_max_f64
#define aabb3_from_position_size_f32            lm2_aabb3_from_position_size_f32
#define aabb3_from_position_size_f64            lm2_aabb3_from_position_size_f64
#define aabb3_get_corner_f32                    lm2_aabb3_get_corner_f32
#define aabb3_get_corner_f64                    lm2_aabb3_get_corner_f64
#define aabb3_get_corners_f32                   lm2_aabb3_get_corners_f32
#define aabb3_get_corners_f64                   lm2_aabb3_get_corners_f64
#define aabb3_height_f32                        lm2_aabb3_height_f32
#define aabb3_height_f64                        lm2_aabb3_height_f64
#define aabb3_overlaps_f32                      lm2_aabb3_overlaps_f32
#define aabb3_overlaps_f64                      lm2_aabb3_overlaps_f64
#define aabb3_scale_f32                         lm2_aabb3_scale_f32
#define aabb3_scale_f64                         lm2_aabb3_scale_f64
#define aabb3_surface_area_f32                  lm2_aabb3_surface_area_f32
#define aabb3_surface_area_f64                  lm2_aabb3_surface_area_f64
#define aabb3_translate_f32                     lm2_aabb3_translate_f32
#define aabb3_translate_f64                     lm2_aabb3_translate_f64
#define aabb3_unit_f32                          lm2_aabb3_unit_f32
#define aabb3_unit_f64                          lm2_aabb3_unit_f64
#define aabb3_width_f32                         lm2_aabb3_width_f32
#define aabb3_width_f64                         lm2_aabb3_width_f64
#define capsule3                                lm2_capsule3
#define capsule3_f32                            lm2_capsule3_f32
#define capsule3_f64                            lm2_capsule3_f64
#define capsule3_center_f32                     lm2_capsule3_center_f32
#define capsule3_center_f64                     lm2_capsule3_center_f64
#define capsule3_contains_point_f32             lm2_capsule3_contains_point_f32
#define capsule3_contains_point_f64             lm2_capsule3_contains_point_f64
#define capsule3_from_center_f32                lm2_capsule3_from_center_f32
#define capsule3_from_center_f64                lm2_capsule3_from_center_f64
#define capsule3_length_f32                     lm2_capsule3_length_f32
#define capsule3_length_f64                     lm2_capsule3_length_f64
#define capsule3_make_coords_f32                lm2_capsule3_make_coords_f32
#define capsule3_make_coords_f64                lm2_capsule3_make_coords_f64
#define capsule3_make_f32                       lm2_capsule3_make_f32
#define capsule3_make_f64                       lm2_capsule3_make_f64
#define capsule3_scale_radius_f32               lm2_capsule3_scale_radius_f32
#define capsule3_scale_radius_f64               lm2_capsule3_scale_radius_f64
#define capsule3_surface_area_f32               lm2_capsule3_surface_area_f32
#define capsule3_surface_area_f64               lm2_capsule3_surface_area_f64
#define capsule3_total_length_f32               lm2_capsule3_total_length_f32
#define capsule3_total_length_f64               lm2_capsule3_total_length_f64
#define capsule3_translate_f32                  lm2_capsule3_translate_f32
#define capsule3_translate_f64                  lm2_capsule3_translate_f64
#define capsule3_volume_f32                     lm2_capsule3_volume_f32
#define capsule3_volume_f64                     lm2_capsule3_volume_f64
#define capsules3_overlap_f32                   lm2_capsules3_overlap_f32
#define capsules3_overlap_f64                   lm2_capsules3_overlap_f64
#define corner3                                 lm2_corner3
#define edge3                                   lm2_edge3
#define edge3_f32                               lm2_edge3_f32
#define edge3_f64                               lm2_edge3_f64
#define edge3_from_plane_f32                    lm2_edge3_from_plane_f32
#define edge3_from_plane_f64                    lm2_edge3_from_plane_f64
#define edge3_from_ray_f32                      lm2_edge3_from_ray_f32
#define edge3_from_ray_f64                      lm2_edge3_from_ray_f64
#define edge3_length_f32                        lm2_edge3_length_f32
#define edge3_length_f64                        lm2_edge3_length_f64
#define edge3_length_sq_f32                     lm2_edge3_length_sq_f32
#define edge3_length_sq_f64                     lm2_edge3_length_sq_f64
#define edge3_make_coords_f32                   lm2_edge3_make_coords_f32
#define edge3_make_coords_f64                   lm2_edge3_make_coords_f64
#define edge3_make_f32                          lm2_edge3_make_f32
#define edge3_make_f64                          lm2_edge3_make_f64
#define edge3_result                            lm2_edge3_result
#define edge3_result_f32                        lm2_edge3_result_f32
#define edge3_result_f64                        lm2_edge3_result_f64
#define edge3_to_edge3_distance_sq_f32          lm2_edge3_to_edge3_distance_sq_f32
#define edge3_to_edge3_distance_sq_f64          lm2_edge3_to_edge3_distance_sq_f64
#define edges3_equal_f32                        lm2_edges3_equal_f32
#define edges3_equal_f64                        lm2_edges3_equal_f64
#define edges3_intersect_f32                    lm2_edges3_intersect_f32
#define edges3_intersect_f64                    lm2_edges3_intersect_f64
#define point_to_edge3_distance_sq_f32          lm2_point_to_edge3_distance_sq_f32
#define point_to_edge3_distance_sq_f64          lm2_point_to_edge3_distance_sq_f64
#define points3_equal_f32                       lm2_points3_equal_f32
#define points3_equal_f64                       lm2_points3_equal_f64
#define plane3                                  lm2_plane3
#define plane3_f32                              lm2_plane3_f32
#define plane3_f64                              lm2_plane3_f64
#define plane3_closest_point_f32                lm2_plane3_closest_point_f32
#define plane3_closest_point_f64                lm2_plane3_closest_point_f64
#define plane3_contains_point_f32               lm2_plane3_contains_point_f32
#define plane3_contains_point_f64               lm2_plane3_contains_point_f64
#define plane3_distance_to_point_f32            lm2_plane3_distance_to_point_f32
#define plane3_distance_to_point_f64            lm2_plane3_distance_to_point_f64
#define plane3_flip_f32                         lm2_plane3_flip_f32
#define plane3_flip_f64                         lm2_plane3_flip_f64
#define plane3_from_point_normal_f32            lm2_plane3_from_point_normal_f32
#define plane3_from_point_normal_f64            lm2_plane3_from_point_normal_f64
#define plane3_from_points_f32                  lm2_plane3_from_points_f32
#define plane3_from_points_f64                  lm2_plane3_from_points_f64
#define plane3_make_f32                         lm2_plane3_make_f32
#define plane3_make_f64                         lm2_plane3_make_f64
#define plane3_project_point_f32                lm2_plane3_project_point_f32
#define plane3_project_point_f64                lm2_plane3_project_point_f64
#define plane3_side_f32                         lm2_plane3_side_f32
#define plane3_side_f64                         lm2_plane3_side_f64
#define plane3_translate_f32                    lm2_plane3_translate_f32
#define plane3_translate_f64                    lm2_plane3_translate_f64
#define plane3_xy_f32                           lm2_plane3_xy_f32
#define plane3_xy_f64                           lm2_plane3_xy_f64
#define plane3_xz_f32                           lm2_plane3_xz_f32
#define plane3_xz_f64                           lm2_plane3_xz_f64
#define plane3_yz_f32                           lm2_plane3_yz_f32
#define plane3_yz_f64                           lm2_plane3_yz_f64
#define ray3                                    lm2_ray3
#define ray3_f32                                lm2_ray3_f32
#define ray3_f64                                lm2_ray3_f64
#define ray3_from_points_f32                    lm2_ray3_from_points_f32
#define ray3_from_points_f64                    lm2_ray3_from_points_f64
#define ray3_make_f32                           lm2_ray3_make_f32
#define ray3_make_f64                           lm2_ray3_make_f64
#define ray3_point_at_f32                       lm2_ray3_point_at_f32
#define ray3_point_at_f64                       lm2_ray3_point_at_f64
#define rayhit3                                 lm2_rayhit3
#define rayhit3_f32                             lm2_rayhit3_f32
#define rayhit3_f64                             lm2_rayhit3_f64
#define raycast_aabb3_f32                       lm2_raycast_aabb3_f32
#define raycast_aabb3_f64                       lm2_raycast_aabb3_f64
#define raycast_capsule_f32                     lm2_raycast_capsule_f32
#define raycast_capsule_f64                     lm2_raycast_capsule_f64
#define raycast_edge_f32                        lm2_raycast_edge_f32
#define raycast_edge_f64                        lm2_raycast_edge_f64
#define raycast_plane_f32                       lm2_raycast_plane_f32
#define raycast_plane_f64                       lm2_raycast_plane_f64
#define raycast_shape3_f32                      lm2_raycast_shape3_f32
#define raycast_shape3_f64                      lm2_raycast_shape3_f64
#define raycast_sphere_f32                      lm2_raycast_sphere_f32
#define raycast_sphere_f64                      lm2_raycast_sphere_f64
#define raycast_triangle_f32                    lm2_raycast_triangle_f32
#define raycast_triangle_f64                    lm2_raycast_triangle_f64
#define shape3                                  lm2_shape3
#define shape3_f32                              lm2_shape3_f32
#define shape3_f64                              lm2_shape3_f64
#define shape3_as_aabb3_f32                     lm2_shape3_as_aabb3_f32
#define shape3_as_aabb3_f64                     lm2_shape3_as_aabb3_f64
#define shape3_as_capsule_f32                   lm2_shape3_as_capsule_f32
#define shape3_as_capsule_f64                   lm2_shape3_as_capsule_f64
#define shape3_as_edge_f32                      lm2_shape3_as_edge_f32
#define shape3_as_edge_f64                      lm2_shape3_as_edge_f64
#define shape3_as_sphere_f32                    lm2_shape3_as_sphere_f32
#define shape3_as_sphere_f64                    lm2_shape3_as_sphere_f64
#define shape3_as_triangle_f32                  lm2_shape3_as_triangle_f32
#define shape3_as_triangle_f64                  lm2_shape3_as_triangle_f64
#define shape3_from_aabb3_f32                   lm2_shape3_from_aabb3_f32
#define shape3_from_aabb3_f64                   lm2_shape3_from_aabb3_f64
#define shape3_from_capsule_f32                 lm2_shape3_from_capsule_f32
#define shape3_from_capsule_f64                 lm2_shape3_from_capsule_f64
#define shape3_from_edge_f32                    lm2_shape3_from_edge_f32
#define shape3_from_edge_f64                    lm2_shape3_from_edge_f64
#define shape3_from_sphere_f32                  lm2_shape3_from_sphere_f32
#define shape3_from_sphere_f64                  lm2_shape3_from_sphere_f64
#define shape3_from_triangle_f32                lm2_shape3_from_triangle_f32
#define shape3_from_triangle_f64                lm2_shape3_from_triangle_f64
#define shape3_get_type_f32                     lm2_shape3_get_type_f32
#define shape3_get_type_f64                     lm2_shape3_get_type_f64
#define shape3_is_type_f32                      lm2_shape3_is_type_f32
#define shape3_is_type_f64                      lm2_shape3_is_type_f64
#define shape3_type                             lm2_shape3_type
#define sphere                                  lm2_sphere
#define sphere_f32                              lm2_sphere_f32
#define sphere_f64                              lm2_sphere_f64
#define sphere_contains_point_f32               lm2_sphere_contains_point_f32
#define sphere_contains_point_f64               lm2_sphere_contains_point_f64
#define sphere_contains_sphere_f32              lm2_sphere_contains_sphere_f32
#define sphere_contains_sphere_f64              lm2_sphere_contains_sphere_f64
#define sphere_diameter_f32                     lm2_sphere_diameter_f32
#define sphere_diameter_f64                     lm2_sphere_diameter_f64
#define sphere_make_coords_f32                  lm2_sphere_make_coords_f32
#define sphere_make_coords_f64                  lm2_sphere_make_coords_f64
#define sphere_make_f32                         lm2_sphere_make_f32
#define sphere_make_f64                         lm2_sphere_make_f64
#define sphere_scale_f32                        lm2_sphere_scale_f32
#define sphere_scale_f64                        lm2_sphere_scale_f64
#define sphere_surface_area_f32                 lm2_sphere_surface_area_f32
#define sphere_surface_area_f64                 lm2_sphere_surface_area_f64
#define sphere_translate_f32                    lm2_sphere_translate_f32
#define sphere_translate_f64                    lm2_sphere_translate_f64
#define sphere_unit_f32                         lm2_sphere_unit_f32
#define sphere_unit_f64                         lm2_sphere_unit_f64
#define sphere_volume_f32                       lm2_sphere_volume_f32
#define sphere_volume_f64                       lm2_sphere_volume_f64
#define spheres_overlap_f32                     lm2_spheres_overlap_f32
#define spheres_overlap_f64                     lm2_spheres_overlap_f64
#define triangle3                               lm2_triangle3
#define triangle3_f32                           lm2_triangle3_f32
#define triangle3_f64                           lm2_triangle3_f64
#define triangle3_area_f32                      lm2_triangle3_area_f32
#define triangle3_area_f64                      lm2_triangle3_area_f64
#define triangle3_centroid_f32                  lm2_triangle3_centroid_f32
#define triangle3_centroid_f64                  lm2_triangle3_centroid_f64
#define triangle3_classify_f32                  lm2_triangle3_classify_f32
#define triangle3_classify_f64                  lm2_triangle3_classify_f64
#define triangle3_contains_point_f32            lm2_triangle3_contains_point_f32
#define triangle3_contains_point_f64            lm2_triangle3_contains_point_f64
#define triangle3_is_degenerate_f32             lm2_triangle3_is_degenerate_f32
#define triangle3_is_degenerate_f64             lm2_triangle3_is_degenerate_f64
#define triangle3_is_equilateral_f32            lm2_triangle3_is_equilateral_f32
#define triangle3_is_equilateral_f64            lm2_triangle3_is_equilateral_f64
#define triangle3_is_isosceles_f32              lm2_triangle3_is_isosceles_f32
#define triangle3_is_isosceles_f64              lm2_triangle3_is_isosceles_f64
#define triangle3_is_right_f32                  lm2_triangle3_is_right_f32
#define triangle3_is_right_f64                  lm2_triangle3_is_right_f64
#define triangle3_is_scalene_f32                lm2_triangle3_is_scalene_f32
#define triangle3_is_scalene_f64                lm2_triangle3_is_scalene_f64
#define triangle3_list_to_indexed_mesh_f32      lm2_triangle3_list_to_indexed_mesh_f32
#define triangle3_list_to_indexed_mesh_f64      lm2_triangle3_list_to_indexed_mesh_f64
#define triangle3_list_to_indexed_mesh_size_f32 lm2_triangle3_list_to_indexed_mesh_size_f32
#define triangle3_list_to_indexed_mesh_size_f64 lm2_triangle3_list_to_indexed_mesh_size_f64
#define triangle3_list_to_vertex_array_f32      lm2_triangle3_list_to_vertex_array_f32
#define triangle3_list_to_vertex_array_f64      lm2_triangle3_list_to_vertex_array_f64
#define triangle3_list_to_vertex_array_size_f32 lm2_triangle3_list_to_vertex_array_size_f32
#define triangle3_list_to_vertex_array_size_f64 lm2_triangle3_list_to_vertex_array_size_f64
#define triangle3_make_coords_f32               lm2_triangle3_make_coords_f32
#define triangle3_make_coords_f64               lm2_triangle3_make_coords_f64
#define triangle3_make_f32                      lm2_triangle3_make_f32
#define triangle3_make_f64                      lm2_triangle3_make_f64
#define triangle3_normal_f32                    lm2_triangle3_normal_f32
#define triangle3_normal_f64                    lm2_triangle3_normal_f64
#define triangle3_overlaps_f32                  lm2_triangle3_overlaps_f32
#define triangle3_overlaps_f64                  lm2_triangle3_overlaps_f64
#define triangle3_perimeter_f32                 lm2_triangle3_perimeter_f32
#define triangle3_perimeter_f64                 lm2_triangle3_perimeter_f64
#define triangle3_shared_edge_f32               lm2_triangle3_shared_edge_f32
#define triangle3_shared_edge_f64               lm2_triangle3_shared_edge_f64
#define triangle3_type                          lm2_triangle3_type
#define indexed_mesh3_size                      lm2_indexed_mesh3_size
#define indexed_mesh_to_triangle3_list_f32      lm2_indexed_mesh_to_triangle3_list_f32
#define indexed_mesh_to_triangle3_list_f64      lm2_indexed_mesh_to_triangle3_list_f64
#define indexed_mesh_to_triangle3_list_size_f32 lm2_indexed_mesh_to_triangle3_list_size_f32
#define indexed_mesh_to_triangle3_list_size_f64 lm2_indexed_mesh_to_triangle3_list_size_f64
#define vertex_array_to_triangle3_list_f32      lm2_vertex_array_to_triangle3_list_f32
#define vertex_array_to_triangle3_list_f64      lm2_vertex_array_to_triangle3_list_f64
#define vertex_array_to_triangle3_list_size_f32 lm2_vertex_array_to_triangle3_list_size_f32
#define vertex_array_to_triangle3_list_size_f64 lm2_vertex_array_to_triangle3_list_size_f64

#ifndef LM2_NO_GENERICS
#  define add                             lm2_add
#  define sub                             lm2_sub
#  define mul                             lm2_mul
#  define div                             lm2_div
#  define mod                             lm2_mod
#  define neg                             lm2_neg
#  define floor                           lm2_floor
#  define floor_multiple                  lm2_floor_multiple
#  define ceil                            lm2_ceil
#  define ceil_multiple                   lm2_ceil_multiple
#  define round                           lm2_round
#  define round_multiple                  lm2_round_multiple
#  define trunc                           lm2_trunc
#  define trunc_multiple                  lm2_trunc_multiple
#  define abs                             lm2_abs
#  define sign                            lm2_sign
#  define sign0                           lm2_sign0
#  define min                             lm2_min
#  define min_abs                         lm2_min_abs
#  define max                             lm2_max
#  define max_abs                         lm2_max_abs
#  define clamp                           lm2_clamp
#  define saturate                        lm2_saturate
#  define lerp                            lm2_lerp
#  define smoothstep                      lm2_smoothstep
#  define alpha                           lm2_alpha
#  define fract                           lm2_fract
#  define pow                             lm2_pow
#  define sqrt                            lm2_sqrt
#  define cos                             lm2_cos
#  define sin                             lm2_sin
#  define tan                             lm2_tan
#  define acos                            lm2_acos
#  define asin                            lm2_asin
#  define atan                            lm2_atan
#  define atan2                           lm2_atan2
#  define deg_to_rad                      lm2_deg_to_rad
#  define rad_to_deg                      lm2_rad_to_deg
#  define wrap_rad                        lm2_wrap_rad
#  define shortest_rad                    lm2_shortest_rad
#  define lerp_rad                        lm2_lerp_rad
#  define wrap_deg                        lm2_wrap_deg
#  define shortest_deg                    lm2_shortest_deg
#  define lerp_deg                        lm2_lerp_deg
#  define hash                            lm2_hash
#  define perlin2                         lm2_perlin2
#  define perlin3                         lm2_perlin3
#  define voronoi2                        lm2_voronoi2
#  define voronoi3                        lm2_voronoi3
#  define bezier_linear2                  lm2_bezier_linear2
#  define bezier_linear3                  lm2_bezier_linear3
#  define bezier_linear4                  lm2_bezier_linear4
#  define bezier_quadratic2               lm2_bezier_quadratic2
#  define bezier_quadratic3               lm2_bezier_quadratic3
#  define bezier_quadratic4               lm2_bezier_quadratic4
#  define bezier_cubic2                   lm2_bezier_cubic2
#  define bezier_cubic3                   lm2_bezier_cubic3
#  define bezier_cubic4                   lm2_bezier_cubic4
#  define bezier_quadratic_derivative2    lm2_bezier_quadratic_derivative2
#  define bezier_quadratic_derivative3    lm2_bezier_quadratic_derivative3
#  define bezier_quadratic_derivative4    lm2_bezier_quadratic_derivative4
#  define bezier_cubic_derivative2        lm2_bezier_cubic_derivative2
#  define bezier_cubic_derivative3        lm2_bezier_cubic_derivative3
#  define bezier_cubic_derivative4        lm2_bezier_cubic_derivative4
#  define bezier_cubic_second_derivative2 lm2_bezier_cubic_second_derivative2
#  define bezier_cubic_second_derivative3 lm2_bezier_cubic_second_derivative3
#  define bezier_cubic_second_derivative4 lm2_bezier_cubic_second_derivative4
#  define bezier_cubic_split2             lm2_bezier_cubic_split2
#  define bezier_cubic_split3             lm2_bezier_cubic_split3
#  define bezier_cubic_split4             lm2_bezier_cubic_split4
#  define bezier_cubic_length2            lm2_bezier_cubic_length2
#  define bezier_cubic_length3            lm2_bezier_cubic_length3
#  define bezier_cubic_length4            lm2_bezier_cubic_length4
#  define ease_linear                     lm2_ease_linear
#  define ease_sin_in                     lm2_ease_sin_in
#  define ease_sin_out                    lm2_ease_sin_out
#  define ease_sin_in_out                 lm2_ease_sin_in_out
#  define ease_quad_in                    lm2_ease_quad_in
#  define ease_quad_out                   lm2_ease_quad_out
#  define ease_quad_in_out                lm2_ease_quad_in_out
#  define ease_cubic_in                   lm2_ease_cubic_in
#  define ease_cubic_out                  lm2_ease_cubic_out
#  define ease_cubic_in_out               lm2_ease_cubic_in_out
#  define ease_quart_in                   lm2_ease_quart_in
#  define ease_quart_out                  lm2_ease_quart_out
#  define ease_quart_in_out               lm2_ease_quart_in_out
#  define ease_quint_in                   lm2_ease_quint_in
#  define ease_quint_out                  lm2_ease_quint_out
#  define ease_quint_in_out               lm2_ease_quint_in_out
#  define ease_exp_in                     lm2_ease_exp_in
#  define ease_exp_out                    lm2_ease_exp_out
#  define ease_exp_in_out                 lm2_ease_exp_in_out
#  define ease_circ_in                    lm2_ease_circ_in
#  define ease_circ_out                   lm2_ease_circ_out
#  define ease_circ_in_out                lm2_ease_circ_in_out
#  define ease_back_in                    lm2_ease_back_in
#  define ease_back_out                   lm2_ease_back_out
#  define ease_back_in_out                lm2_ease_back_in_out
#  define ease_elastic_in                 lm2_ease_elastic_in
#  define ease_elastic_out                lm2_ease_elastic_out
#  define ease_elastic_in_out             lm2_ease_elastic_in_out
#  define ease_bounce_in                  lm2_ease_bounce_in
#  define ease_bounce_out                 lm2_ease_bounce_out
#  define ease_bounce_in_out              lm2_ease_bounce_in_out
#  define ease                            lm2_ease
#  define v2_add                          lm2_v2_add
#  define v2_sub                          lm2_v2_sub
#  define v2_mul                          lm2_v2_mul
#  define v2_div                          lm2_v2_div
#  define v2_add_s                        lm2_v2_add_s
#  define v2_sub_s                        lm2_v2_sub_s
#  define v2_mul_s                        lm2_v2_mul_s
#  define v2_div_s                        lm2_v2_div_s
#  define v2_neg                          lm2_v2_neg
#  define v2_floor                        lm2_v2_floor
#  define v2_ceil                         lm2_v2_ceil
#  define v2_round                        lm2_v2_round
#  define v2_trunc                        lm2_v2_trunc
#  define v2_abs                          lm2_v2_abs
#  define v2_sign                         lm2_v2_sign
#  define v2_sign0                        lm2_v2_sign0
#  define v2_saturate                     lm2_v2_saturate
#  define v2_fract                        lm2_v2_fract
#  define v2_sqrt                         lm2_v2_sqrt
#  define v2_floor_multiple               lm2_v2_floor_multiple
#  define v2_ceil_multiple                lm2_v2_ceil_multiple
#  define v2_round_multiple               lm2_v2_round_multiple
#  define v2_trunc_multiple               lm2_v2_trunc_multiple
#  define v2_min                          lm2_v2_min
#  define v2_min_abs                      lm2_v2_min_abs
#  define v2_max                          lm2_v2_max
#  define v2_max_abs                      lm2_v2_max_abs
#  define v2_mod                          lm2_v2_mod
#  define v2_pow                          lm2_v2_pow
#  define v2_clamp                        lm2_v2_clamp
#  define v2_lerp                         lm2_v2_lerp
#  define v2_smoothstep                   lm2_v2_smoothstep
#  define v2_alpha                        lm2_v2_alpha
#  define v2_dot                          lm2_v2_dot
#  define v2_cross                        lm2_v2_cross
#  define v2_cross3                       lm2_v2_cross3
#  define v2_length                       lm2_v2_length
#  define v2_length_sq                    lm2_v2_length_sq
#  define v2_distance                     lm2_v2_distance
#  define v2_distance_sq                  lm2_v2_distance_sq
#  define v2_normalize                    lm2_v2_normalize
#  define v2_angle                        lm2_v2_angle
#  define v2_rotate                       lm2_v2_rotate
#  define v2_rotate_around                lm2_v2_rotate_around
#  define v2_perp_ccw                     lm2_v2_perp_ccw
#  define v2_perp_cw                      lm2_v2_perp_cw
#  define v2_reflect                      lm2_v2_reflect
#  define v2_project                      lm2_v2_project
#  define v2_upcast                       lm2_v2_upcast
#  define v3_add                          lm2_v3_add
#  define v3_sub                          lm2_v3_sub
#  define v3_mul                          lm2_v3_mul
#  define v3_div                          lm2_v3_div
#  define v3_add_s                        lm2_v3_add_s
#  define v3_sub_s                        lm2_v3_sub_s
#  define v3_mul_s                        lm2_v3_mul_s
#  define v3_div_s                        lm2_v3_div_s
#  define v3_neg                          lm2_v3_neg
#  define v3_floor                        lm2_v3_floor
#  define v3_ceil                         lm2_v3_ceil
#  define v3_round                        lm2_v3_round
#  define v3_trunc                        lm2_v3_trunc
#  define v3_abs                          lm2_v3_abs
#  define v3_sign                         lm2_v3_sign
#  define v3_sign0                        lm2_v3_sign0
#  define v3_saturate                     lm2_v3_saturate
#  define v3_fract                        lm2_v3_fract
#  define v3_sqrt                         lm2_v3_sqrt
#  define v3_floor_multiple               lm2_v3_floor_multiple
#  define v3_ceil_multiple                lm2_v3_ceil_multiple
#  define v3_round_multiple               lm2_v3_round_multiple
#  define v3_trunc_multiple               lm2_v3_trunc_multiple
#  define v3_min                          lm2_v3_min
#  define v3_min_abs                      lm2_v3_min_abs
#  define v3_max                          lm2_v3_max
#  define v3_max_abs                      lm2_v3_max_abs
#  define v3_mod                          lm2_v3_mod
#  define v3_pow                          lm2_v3_pow
#  define v3_clamp                        lm2_v3_clamp
#  define v3_lerp                         lm2_v3_lerp
#  define v3_smoothstep                   lm2_v3_smoothstep
#  define v3_alpha                        lm2_v3_alpha
#  define v3_dot                          lm2_v3_dot
#  define v3_cross                        lm2_v3_cross
#  define v3_length                       lm2_v3_length
#  define v3_length_sq                    lm2_v3_length_sq
#  define v3_distance                     lm2_v3_distance
#  define v3_distance_sq                  lm2_v3_distance_sq
#  define v3_normalize                    lm2_v3_normalize
#  define v3_angle                        lm2_v3_angle
#  define v3_reflect                      lm2_v3_reflect
#  define v3_project                      lm2_v3_project
#  define v3_upcast                       lm2_v3_upcast
#  define v3_downcast                     lm2_v3_downcast
#  define v4_add                          lm2_v4_add
#  define v4_sub                          lm2_v4_sub
#  define v4_mul                          lm2_v4_mul
#  define v4_div                          lm2_v4_div
#  define v4_add_s                        lm2_v4_add_s
#  define v4_sub_s                        lm2_v4_sub_s
#  define v4_mul_s                        lm2_v4_mul_s
#  define v4_div_s                        lm2_v4_div_s
#  define v4_neg                          lm2_v4_neg
#  define v4_floor                        lm2_v4_floor
#  define v4_ceil                         lm2_v4_ceil
#  define v4_round                        lm2_v4_round
#  define v4_trunc                        lm2_v4_trunc
#  define v4_abs                          lm2_v4_abs
#  define v4_sign                         lm2_v4_sign
#  define v4_sign0                        lm2_v4_sign0
#  define v4_saturate                     lm2_v4_saturate
#  define v4_fract                        lm2_v4_fract
#  define v4_sqrt                         lm2_v4_sqrt
#  define v4_floor_multiple               lm2_v4_floor_multiple
#  define v4_ceil_multiple                lm2_v4_ceil_multiple
#  define v4_round_multiple               lm2_v4_round_multiple
#  define v4_trunc_multiple               lm2_v4_trunc_multiple
#  define v4_min                          lm2_v4_min
#  define v4_min_abs                      lm2_v4_min_abs
#  define v4_max                          lm2_v4_max
#  define v4_max_abs                      lm2_v4_max_abs
#  define v4_mod                          lm2_v4_mod
#  define v4_pow                          lm2_v4_pow
#  define v4_clamp                        lm2_v4_clamp
#  define v4_lerp                         lm2_v4_lerp
#  define v4_smoothstep                   lm2_v4_smoothstep
#  define v4_alpha                        lm2_v4_alpha
#  define v4_dot                          lm2_v4_dot
#  define v4_length                       lm2_v4_length
#  define v4_length_sq                    lm2_v4_length_sq
#  define v4_distance                     lm2_v4_distance
#  define v4_distance_sq                  lm2_v4_distance_sq
#  define v4_normalize                    lm2_v4_normalize
#  define v4_downcast                     lm2_v4_downcast
#  define m3x2_identity                   lm2_m3x2_identity
#  define m3x2_zero                       lm2_m3x2_zero
#  define m3x2_mul                        lm2_m3x2_mul
#  define m3x3_identity                   lm2_m3x3_identity
#  define m3x3_zero                       lm2_m3x3_zero
#  define m3x3_mul                        lm2_m3x3_mul
#  define m4x4_identity                   lm2_m4x4_identity
#  define m4x4_zero                       lm2_m4x4_zero
#  define m4x4_mul                        lm2_m4x4_mul
#  define quat_identity                   lm2_quat_identity
#  define quat_multiply                   lm2_quat_multiply
#  define quat_normalize                  lm2_quat_normalize
#  define r2_make                         lm2_r2_make
#  define r2_translate                    lm2_r2_translate
#  define r2_contains_point               lm2_r2_contains_point
#  define r2_overlaps                     lm2_r2_overlaps
#  define r2_area                         lm2_r2_area
#  define r2_get_center                   lm2_r2_get_center
#  define r2_union                        lm2_r2_union
#  define r2_intersection                 lm2_r2_intersection
#  define r3_make                         lm2_r3_make
#  define r3_contains_point               lm2_r3_contains_point
#  define r3_volume                       lm2_r3_volume
#  define r3_overlaps                     lm2_r3_overlaps
#  define r4_make                         lm2_r4_make
#  define r4_contains_point               lm2_r4_contains_point
#  define r4_hypervolume                  lm2_r4_hypervolume
#  define m3x2_from_translation           lm2_m3x2_from_translation
#  define m3x2_from_rotation              lm2_m3x2_from_rotation
#  define m3x2_from_scale                 lm2_m3x2_from_scale
#  define m3x2_transform_point            lm2_m3x2_transform_point
#  define m3x2_transform_vector           lm2_m3x2_transform_vector
#  define m3x2_inverse                    lm2_m3x2_inverse
#  define m3x2_determinant                lm2_m3x2_determinant
#  define m3x3_from_rotation_x            lm2_m3x3_from_rotation_x
#  define m3x3_from_rotation_y            lm2_m3x3_from_rotation_y
#  define m3x3_from_rotation_z            lm2_m3x3_from_rotation_z
#  define m3x3_transform                  lm2_m3x3_transform
#  define m3x3_transpose                  lm2_m3x3_transpose
#  define m3x3_inverse                    lm2_m3x3_inverse
#  define m3x3_determinant                lm2_m3x3_determinant
#  define m4x4_from_translation           lm2_m4x4_from_translation
#  define m4x4_from_rotation_x            lm2_m4x4_from_rotation_x
#  define m4x4_from_rotation_y            lm2_m4x4_from_rotation_y
#  define m4x4_from_rotation_z            lm2_m4x4_from_rotation_z
#  define m4x4_from_quaternion            lm2_m4x4_from_quaternion
#  define m4x4_transform_point            lm2_m4x4_transform_point
#  define m4x4_transform_vector           lm2_m4x4_transform_vector
#  define m4x4_transpose                  lm2_m4x4_transpose
#  define m4x4_inverse                    lm2_m4x4_inverse
#  define m4x4_determinant                lm2_m4x4_determinant
#  define m4x4_look_at                    lm2_m4x4_look_at
#  define m4x4_perspective                lm2_m4x4_perspective
#  define m4x4_orthographic               lm2_m4x4_orthographic
#  define quat_zero                       lm2_quat_zero
#  define quat_make                       lm2_quat_make
#  define quat_from_axis_angle            lm2_quat_from_axis_angle
#  define quat_from_euler                 lm2_quat_from_euler
#  define quat_conjugate                  lm2_quat_conjugate
#  define quat_inverse                    lm2_quat_inverse
#  define quat_add                        lm2_quat_add
#  define quat_sub                        lm2_quat_sub
#  define quat_scale                      lm2_quat_scale
#  define quat_dot                        lm2_quat_dot
#  define quat_length                     lm2_quat_length
#  define quat_rotate_vector              lm2_quat_rotate_vector
#  define quat_slerp                      lm2_quat_slerp
#  define quat_nlerp                      lm2_quat_nlerp
#  define aabb3_from_min_max              lm2_aabb3_from_min_max
#  define aabb3_contains_point            lm2_aabb3_contains_point
#  define aabb3_overlaps                  lm2_aabb3_overlaps
#  define capsule2_make                   lm2_capsule2_make
#  define capsule2_contains_point         lm2_capsule2_contains_point
#  define capsule3_make                   lm2_capsule3_make
#  define capsule3_contains_point         lm2_capsule3_contains_point
#  define circle_make                     lm2_circle_make
#  define circle_area                     lm2_circle_area
#  define circle_circumference            lm2_circle_circumference
#  define circle_contains_point           lm2_circle_contains_point
#  define sphere_make                     lm2_sphere_make
#  define sphere_volume                   lm2_sphere_volume
#  define sphere_surface_area             lm2_sphere_surface_area
#  define sphere_contains_point           lm2_sphere_contains_point
#  define triangle2_make                  lm2_triangle2_make
#  define triangle2_area                  lm2_triangle2_area
#  define triangle2_contains_point        lm2_triangle2_contains_point
#  define triangle3_make                  lm2_triangle3_make
#  define triangle3_area                  lm2_triangle3_area
#  define triangle3_normal                lm2_triangle3_normal
#  define plane2_make                     lm2_plane2_make
#  define plane2_distance_to_point        lm2_plane2_distance_to_point
#  define plane3_make                     lm2_plane3_make
#  define plane3_distance_to_point        lm2_plane3_distance_to_point
#  define ray2_make                       lm2_ray2_make
#  define ray3_make                       lm2_ray3_make
#  define raycast_circle                  lm2_raycast_circle
#  define raycast_sphere                  lm2_raycast_sphere
#  define raycast_triangle                lm2_raycast_triangle
#  define collide_circle_to_circle        lm2_collide_circle_to_circle
#endif