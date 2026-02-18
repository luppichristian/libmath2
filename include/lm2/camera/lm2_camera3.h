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

#include "lm2/lm2_base.h"
#include "lm2/matrices/lm2_matrix4x4.h"
#include "lm2/misc/lm2_quaternion.h"
#include "lm2/vectors/lm2_vector3.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// Camera 3D
// =============================================================================
// Represents a 3D camera with a position, orientation (forward/up vectors),
// and projection parameters (perspective or orthographic).
//
// Conventions:
//   - Right-handed coordinate system
//   - Forward is the direction the camera is looking at
//   - Up is the world-up hint used to compute the right axis (via cross product)
//   - fov_y : vertical field of view in radians (for perspective projection)
//   - aspect : width / height of the viewport
//   - near_plane / far_plane : clipping distances (must be > 0)
//   - ortho_size : half-height of the orthographic frustum

// =============================================================================
// Camera3 Projection Mode
// =============================================================================

typedef enum lm2_camera3_projection {
  LM2_CAMERA3_PERSPECTIVE,
  LM2_CAMERA3_ORTHOGRAPHIC,
} lm2_camera3_projection;

// =============================================================================
// Camera3 Types - f64
// =============================================================================

typedef struct lm2_camera3_f64 {
  lm2_v3_f64 position;                // World-space eye position
  lm2_v3_f64 target;                  // World-space look-at target
  lm2_v3_f64 up;                      // World up hint (usually (0,1,0))
  double fov_y;                       // Vertical FOV in radians (perspective)
  double aspect;                      // Width / height ratio
  double near_plane;                  // Near clipping distance
  double far_plane;                   // Far clipping distance
  double ortho_size;                  // Half-height for orthographic projection
  lm2_camera3_projection projection;  // Projection mode
} lm2_camera3_f64;

// =============================================================================
// Camera3 Functions - f64
// =============================================================================

// Construction
LM2_API lm2_camera3_f64 lm2_camera3_perspective_f64(lm2_v3_f64 position, lm2_v3_f64 target, lm2_v3_f64 up, double fov_y, double aspect, double near_plane, double far_plane);
LM2_API lm2_camera3_f64 lm2_camera3_orthographic_f64(lm2_v3_f64 position, lm2_v3_f64 target, lm2_v3_f64 up, double ortho_size, double aspect, double near_plane, double far_plane);

// View / projection matrices
LM2_API lm2_m4x4_f64 lm2_camera3_get_view_f64(lm2_camera3_f64 camera);
LM2_API lm2_m4x4_f64 lm2_camera3_get_projection_f64(lm2_camera3_f64 camera);
LM2_API lm2_m4x4_f64 lm2_camera3_get_view_projection_f64(lm2_camera3_f64 camera);
LM2_API lm2_m4x4_f64 lm2_camera3_get_inv_view_f64(lm2_camera3_f64 camera);

// Derived direction vectors
LM2_API lm2_v3_f64 lm2_camera3_get_forward_f64(lm2_camera3_f64 camera);
LM2_API lm2_v3_f64 lm2_camera3_get_right_f64(lm2_camera3_f64 camera);
LM2_API lm2_v3_f64 lm2_camera3_get_up_f64(lm2_camera3_f64 camera);

// Camera manipulation
LM2_API lm2_camera3_f64 lm2_camera3_move_f64(lm2_camera3_f64 camera, lm2_v3_f64 delta);
LM2_API lm2_camera3_f64 lm2_camera3_look_at_f64(lm2_camera3_f64 camera, lm2_v3_f64 target);
LM2_API lm2_camera3_f64 lm2_camera3_orbit_f64(lm2_camera3_f64 camera, double yaw, double pitch);
LM2_API lm2_camera3_f64 lm2_camera3_set_aspect_f64(lm2_camera3_f64 camera, double aspect);
LM2_API lm2_camera3_f64 lm2_camera3_set_fov_y_f64(lm2_camera3_f64 camera, double fov_y);

// Quaternion orientation
LM2_API lm2_camera3_f64 lm2_camera3_from_quat_f64(lm2_v3_f64 position, lm2_quat_f64 orientation, double fov_y, double aspect, double near_plane, double far_plane);
LM2_API lm2_quat_f64 lm2_camera3_get_orientation_f64(lm2_camera3_f64 camera);
LM2_API lm2_camera3_f64 lm2_camera3_set_orientation_f64(lm2_camera3_f64 camera, lm2_quat_f64 orientation);
LM2_API lm2_camera3_f64 lm2_camera3_rotate_local_f64(lm2_camera3_f64 camera, lm2_quat_f64 rotation);

// Space transforms
LM2_API lm2_v3_f64 lm2_camera3_world_to_ndc_f64(lm2_camera3_f64 camera, lm2_v3_f64 world_pos);
LM2_API lm2_v3_f64 lm2_camera3_ndc_to_world_f64(lm2_camera3_f64 camera, lm2_v3_f64 ndc_pos);

// =============================================================================
// Camera3 Types - f32
// =============================================================================

typedef struct lm2_camera3_f32 {
  lm2_v3_f32 position;                // World-space eye position
  lm2_v3_f32 target;                  // World-space look-at target
  lm2_v3_f32 up;                      // World up hint (usually (0,1,0))
  float fov_y;                        // Vertical FOV in radians (perspective)
  float aspect;                       // Width / height ratio
  float near_plane;                   // Near clipping distance
  float far_plane;                    // Far clipping distance
  float ortho_size;                   // Half-height for orthographic projection
  lm2_camera3_projection projection;  // Projection mode
} lm2_camera3_f32;

// =============================================================================
// Camera3 Functions - f32
// =============================================================================

// Construction
LM2_API lm2_camera3_f32 lm2_camera3_perspective_f32(lm2_v3_f32 position, lm2_v3_f32 target, lm2_v3_f32 up, float fov_y, float aspect, float near_plane, float far_plane);
LM2_API lm2_camera3_f32 lm2_camera3_orthographic_f32(lm2_v3_f32 position, lm2_v3_f32 target, lm2_v3_f32 up, float ortho_size, float aspect, float near_plane, float far_plane);

// View / projection matrices
LM2_API lm2_m4x4_f32 lm2_camera3_get_view_f32(lm2_camera3_f32 camera);
LM2_API lm2_m4x4_f32 lm2_camera3_get_projection_f32(lm2_camera3_f32 camera);
LM2_API lm2_m4x4_f32 lm2_camera3_get_view_projection_f32(lm2_camera3_f32 camera);
LM2_API lm2_m4x4_f32 lm2_camera3_get_inv_view_f32(lm2_camera3_f32 camera);

// Derived direction vectors
LM2_API lm2_v3_f32 lm2_camera3_get_forward_f32(lm2_camera3_f32 camera);
LM2_API lm2_v3_f32 lm2_camera3_get_right_f32(lm2_camera3_f32 camera);
LM2_API lm2_v3_f32 lm2_camera3_get_up_f32(lm2_camera3_f32 camera);

// Camera manipulation
LM2_API lm2_camera3_f32 lm2_camera3_move_f32(lm2_camera3_f32 camera, lm2_v3_f32 delta);
LM2_API lm2_camera3_f32 lm2_camera3_look_at_f32(lm2_camera3_f32 camera, lm2_v3_f32 target);
LM2_API lm2_camera3_f32 lm2_camera3_orbit_f32(lm2_camera3_f32 camera, float yaw, float pitch);
LM2_API lm2_camera3_f32 lm2_camera3_set_aspect_f32(lm2_camera3_f32 camera, float aspect);
LM2_API lm2_camera3_f32 lm2_camera3_set_fov_y_f32(lm2_camera3_f32 camera, float fov_y);

// Quaternion orientation
LM2_API lm2_camera3_f32 lm2_camera3_from_quat_f32(lm2_v3_f32 position, lm2_quat_f32 orientation, float fov_y, float aspect, float near_plane, float far_plane);
LM2_API lm2_quat_f32 lm2_camera3_get_orientation_f32(lm2_camera3_f32 camera);
LM2_API lm2_camera3_f32 lm2_camera3_set_orientation_f32(lm2_camera3_f32 camera, lm2_quat_f32 orientation);
LM2_API lm2_camera3_f32 lm2_camera3_rotate_local_f32(lm2_camera3_f32 camera, lm2_quat_f32 rotation);

// Space transforms
LM2_API lm2_v3_f32 lm2_camera3_world_to_ndc_f32(lm2_camera3_f32 camera, lm2_v3_f32 world_pos);
LM2_API lm2_v3_f32 lm2_camera3_ndc_to_world_f32(lm2_camera3_f32 camera, lm2_v3_f32 ndc_pos);

// #############################################################################
LM2_HEADER_END;
// #############################################################################
