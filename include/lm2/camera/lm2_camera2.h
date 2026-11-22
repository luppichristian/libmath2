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
// Represents a 2D orthographic camera. The following contracts apply to both
// precisions. All camera-manipulation functions return a modified copy.
//
// position is the world-space point mapped to the viewport center. rotation is
// an angle in radians in the numeric XY plane; zoom is a uniform scale. The
// viewport min and max are absolute screen pixel coordinates (normally top-left
// and bottom-right), not coordinates relative to the viewport. The transform
// does not flip Y: with zero rotation, positive world X/Y maps to positive screen
// X/Y. The apparent rotation direction therefore depends on the screen Y axis.
//
// get_view maps world points directly to screen pixels: translate by -position,
// rotate by -rotation, scale by zoom, then translate to the viewport center.
// get_inv_view and screen_to_world reverse this transform. make stores its
// arguments; default sets position to the viewport center, rotation to zero,
// and zoom to one, making the resulting world-to-screen transform identity.
//
// move adds a world-space delta to position; rotate adds radians to rotation;
// set_zoom assigns an absolute zoom without changing position. zoom_at multiplies
// zoom by zoom_factor and moves the camera so the world point under the absolute
// screen_anchor remains there. Use positive, nonzero zoom and zoom_factor for
// ordinary zooming; inverse operations require nonzero zoom, including both
// the original and resulting zoom for zoom_at. Singular inverses can assert. Values are not clamped or validated.
//
// get_viewport_size returns max - min, and get_viewport_center returns their
// midpoint in screen pixels. get_world_bounds transforms all four viewport
// corners to world space and returns their axis-aligned bounding box. When the
// camera is rotated this box may exceed the visible quadrilateral.

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

#ifndef LM2_NO_IMPLEMENTATION
#  include "lm2_camera2_impl.h"
#endif