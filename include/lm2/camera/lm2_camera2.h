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
#include "lm2/matrices/lm2_matrix3x2.h"
#include "lm2/ranges/lm2_range2.h"
#include "lm2/vectors/lm2_vector2.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// Camera 2D
// =============================================================================
// Represents a 2D orthographic camera with position, rotation and zoom.
//
// The view matrix transforms world-space coordinates into camera/view-space.
// The inverse view matrix transforms camera-space back to world-space.
//
// Screen-space coordinates are in pixels relative to the viewport origin
// (top-left). World-space coordinates are in whatever units the user defines.
//
// Convention:
//   - position : world-space position of the camera center
//   - rotation : counter-clockwise angle in radians
//   - zoom     : uniform scale factor (zoom > 1 zooms in, 0 < zoom < 1 zooms out)
//   - viewport : screen rectangle in pixels (min = top-left, max = bottom-right)

// =============================================================================
// Camera2 Types - f64
// =============================================================================

typedef struct lm2_camera2_f64 {
  lm2_v2_f64 position;  // World-space center of the camera
  double rotation;      // Counter-clockwise rotation in radians
  double zoom;          // Uniform zoom factor (default 1.0)
  lm2_r2_f64 viewport;  // Screen viewport rectangle in pixels
} lm2_camera2_f64;

// =============================================================================
// Camera2 Functions - f64
// =============================================================================

// Construction
LM2_API lm2_camera2_f64 lm2_camera2_make_f64(lm2_v2_f64 position, double rotation, double zoom, lm2_r2_f64 viewport);
LM2_API lm2_camera2_f64 lm2_camera2_default_f64(lm2_r2_f64 viewport);

// View matrix
LM2_API lm2_m3x2_f64 lm2_camera2_get_view_f64(lm2_camera2_f64 camera);
LM2_API lm2_m3x2_f64 lm2_camera2_get_inv_view_f64(lm2_camera2_f64 camera);

// Space transforms
LM2_API lm2_v2_f64 lm2_camera2_world_to_screen_f64(lm2_camera2_f64 camera, lm2_v2_f64 world_pos);
LM2_API lm2_v2_f64 lm2_camera2_screen_to_world_f64(lm2_camera2_f64 camera, lm2_v2_f64 screen_pos);

// Camera manipulation
LM2_API lm2_camera2_f64 lm2_camera2_move_f64(lm2_camera2_f64 camera, lm2_v2_f64 delta);
LM2_API lm2_camera2_f64 lm2_camera2_zoom_at_f64(lm2_camera2_f64 camera, double zoom_factor, lm2_v2_f64 screen_anchor);
LM2_API lm2_camera2_f64 lm2_camera2_set_zoom_f64(lm2_camera2_f64 camera, double zoom);
LM2_API lm2_camera2_f64 lm2_camera2_rotate_f64(lm2_camera2_f64 camera, double delta_radians);

// Viewport helpers
LM2_API lm2_v2_f64 lm2_camera2_get_viewport_size_f64(lm2_camera2_f64 camera);
LM2_API lm2_v2_f64 lm2_camera2_get_viewport_center_f64(lm2_camera2_f64 camera);
LM2_API lm2_r2_f64 lm2_camera2_get_world_bounds_f64(lm2_camera2_f64 camera);

// =============================================================================
// Camera2 Types - f32
// =============================================================================

typedef struct lm2_camera2_f32 {
  lm2_v2_f32 position;  // World-space center of the camera
  float rotation;       // Counter-clockwise rotation in radians
  float zoom;           // Uniform zoom factor (default 1.0)
  lm2_r2_f32 viewport;  // Screen viewport rectangle in pixels
} lm2_camera2_f32;

// =============================================================================
// Camera2 Functions - f32
// =============================================================================

// Construction
LM2_API lm2_camera2_f32 lm2_camera2_make_f32(lm2_v2_f32 position, float rotation, float zoom, lm2_r2_f32 viewport);
LM2_API lm2_camera2_f32 lm2_camera2_default_f32(lm2_r2_f32 viewport);

// View matrix
LM2_API lm2_m3x2_f32 lm2_camera2_get_view_f32(lm2_camera2_f32 camera);
LM2_API lm2_m3x2_f32 lm2_camera2_get_inv_view_f32(lm2_camera2_f32 camera);

// Space transforms
LM2_API lm2_v2_f32 lm2_camera2_world_to_screen_f32(lm2_camera2_f32 camera, lm2_v2_f32 world_pos);
LM2_API lm2_v2_f32 lm2_camera2_screen_to_world_f32(lm2_camera2_f32 camera, lm2_v2_f32 screen_pos);

// Camera manipulation
LM2_API lm2_camera2_f32 lm2_camera2_move_f32(lm2_camera2_f32 camera, lm2_v2_f32 delta);
LM2_API lm2_camera2_f32 lm2_camera2_zoom_at_f32(lm2_camera2_f32 camera, float zoom_factor, lm2_v2_f32 screen_anchor);
LM2_API lm2_camera2_f32 lm2_camera2_set_zoom_f32(lm2_camera2_f32 camera, float zoom);
LM2_API lm2_camera2_f32 lm2_camera2_rotate_f32(lm2_camera2_f32 camera, float delta_radians);

// Viewport helpers
LM2_API lm2_v2_f32 lm2_camera2_get_viewport_size_f32(lm2_camera2_f32 camera);
LM2_API lm2_v2_f32 lm2_camera2_get_viewport_center_f32(lm2_camera2_f32 camera);
LM2_API lm2_r2_f32 lm2_camera2_get_world_bounds_f32(lm2_camera2_f32 camera);

// #############################################################################
LM2_HEADER_END;
// #############################################################################
