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
// Represents a right-handed 3D camera. Contracts below apply to both precisions;
// camera-manipulation functions return modified copies, not in-place updates.
//
// position and target are world-space points; up is a world-space up hint.
// forward = normalize(target - position), right = normalize(cross(forward, up)),
// and the computed camera up = cross(right, forward). View space has +X right,
// +Y up and -Z forward. position must differ from target and up must not be
// parallel to forward for a valid view matrix. The forward length and length
// of cross(normalize(forward), up) must each exceed 1e-10 (f64) or 1e-6
// (f32) for look_at. Direction getters normalize zero to zero, so they can
// return zero even where view construction asserts.
//
// Perspective uses vertical fov_y in radians and aspect = width / height.
// Orthographic projection is centered, with half-height ortho_size and half-width
// ortho_size * aspect. near_plane and far_plane are positive distances in front
// of the camera, with far_plane > near_plane. For a conventional perspective
// use 0 < fov_y < pi; use positive aspect and ortho_size. Constructors and setters
// store values without validating or clamping them; invalid projection values
// can produce singular matrices or assertions in the matrix functions. Any
// projection enum other than PERSPECTIVE is treated as orthographic.
//
// get_view maps world to view space, get_inv_view reverses it, get_projection
// maps view to homogeneous clip space, and get_view_projection is projection *
// view. After dividing by clip W, visible NDC spans [-1, 1] on X, Y and Z; the
// near and far planes map to Z = -1 and +1 respectively (OpenGL convention).
// world_to_ndc and ndc_to_world perform that homogeneous divide; they do not
// clip or test visibility; they divide by W without checking it. Callers must
// ensure W is nonzero. ndc_to_world also requires an invertible view-projection
// matrix.
//
// move adds a world-space delta to position and target; look_at replaces target.
// orbit keeps target and radius, using world +Y as the polar axis regardless of
// up: positive yaw moves an offset on +Z toward +X; positive pitch moves it
// toward -Y. Its polar angle is clamped to [0.01, pi - 0.01] radians, so a
// near-pole camera can move even at zero pitch. A zero-radius orbit remains
// degenerate. set_aspect
// and set_fov_y only replace their fields (fov_y affects perspective only).
//
// from_quat constructs a perspective camera; set_orientation keeps position.
// Both rotate the default camera axes (forward -Z, up +Y) by a unit quaternion,
// set target to position + rotated forward, and set up to rotated up. This resets
// target distance to one. get_orientation extracts the rotation of the view
// matrix (world to camera), i.e. the inverse of the camera-to-world orientation
// accepted by set_orientation. Conjugate it before passing it back to that
// setter. rotate_local composes camera-to-world orientation with the given local
// rotation on the right and normalizes the result; it also resets target distance.

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





#include "lm2_camera3_impl.h"
