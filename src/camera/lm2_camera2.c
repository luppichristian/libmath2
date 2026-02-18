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

#include <lm2/camera/lm2_camera2.h>
#include <lm2/matrices/lm2_matrix3x2.h>
#include <lm2/scalar/lm2_trigonometry.h>
#include <lm2/vectors/lm2_vector2.h>
#include <lm2/vectors/lm2_vector_specifics.h>

// =============================================================================
// Camera 2D Functions - f64
// =============================================================================

LM2_API lm2_camera2_f64 lm2_camera2_make_f64(lm2_v2_f64 position, double rotation, double zoom, lm2_r2_f64 viewport) {
  lm2_camera2_f64 cam;
  cam.position = position;
  cam.rotation = rotation;
  cam.zoom = zoom;
  cam.viewport = viewport;
  return cam;
}

LM2_API lm2_camera2_f64 lm2_camera2_default_f64(lm2_r2_f64 viewport) {
  lm2_v2_f64 min = viewport.min;
  lm2_v2_f64 max = viewport.max;
  lm2_v2_f64 center;
  center.x = (min.x + max.x) * 0.5;
  center.y = (min.y + max.y) * 0.5;
  return lm2_camera2_make_f64(center, 0.0, 1.0, viewport);
}

// The view matrix transforms world-space points into screen-space.
//
// Steps:
//   1. Translate world by -position  (move world so camera is at origin)
//   2. Rotate by -rotation           (undo camera rotation)
//   3. Scale by zoom                 (apply zoom)
//   4. Translate to viewport center  (place origin at center of viewport)
LM2_API lm2_m3x2_f64 lm2_camera2_get_view_f64(lm2_camera2_f64 camera) {
  lm2_v2_f64 min = camera.viewport.min;
  lm2_v2_f64 max = camera.viewport.max;
  lm2_v2_f64 center;
  center.x = (min.x + max.x) * 0.5;
  center.y = (min.y + max.y) * 0.5;

  lm2_v2_f64 neg_pos;
  neg_pos.x = -camera.position.x;
  neg_pos.y = -camera.position.y;

  lm2_m3x2_f64 t = lm2_m3x2_translate_f64(neg_pos);
  lm2_m3x2_f64 r = lm2_m3x2_rotate_f64(-camera.rotation);

  lm2_v2_f64 zoom_vec;
  zoom_vec.x = camera.zoom;
  zoom_vec.y = camera.zoom;
  lm2_m3x2_f64 s = lm2_m3x2_scale_f64(zoom_vec);
  lm2_m3x2_f64 tc = lm2_m3x2_translate_f64(center);

  // Compose: tc * s * r * t
  lm2_m3x2_f64 tmp = lm2_m3x2_multiply_f64(r, t);
  tmp = lm2_m3x2_multiply_f64(s, tmp);
  tmp = lm2_m3x2_multiply_f64(tc, tmp);
  return tmp;
}

LM2_API lm2_m3x2_f64 lm2_camera2_get_inv_view_f64(lm2_camera2_f64 camera) {
  return lm2_m3x2_inverse_f64(lm2_camera2_get_view_f64(camera));
}

LM2_API lm2_v2_f64 lm2_camera2_world_to_screen_f64(lm2_camera2_f64 camera, lm2_v2_f64 world_pos) {
  return lm2_m3x2_transform_point_f64(lm2_camera2_get_view_f64(camera), world_pos);
}

LM2_API lm2_v2_f64 lm2_camera2_screen_to_world_f64(lm2_camera2_f64 camera, lm2_v2_f64 screen_pos) {
  return lm2_m3x2_transform_point_f64(lm2_camera2_get_inv_view_f64(camera), screen_pos);
}

LM2_API lm2_camera2_f64 lm2_camera2_move_f64(lm2_camera2_f64 camera, lm2_v2_f64 delta) {
  camera.position.x += delta.x;
  camera.position.y += delta.y;
  return camera;
}

LM2_API lm2_camera2_f64 lm2_camera2_zoom_at_f64(lm2_camera2_f64 camera, double zoom_factor, lm2_v2_f64 screen_anchor) {
  // Convert screen anchor to world space before zoom change
  lm2_v2_f64 world_before = lm2_camera2_screen_to_world_f64(camera, screen_anchor);

  camera.zoom *= zoom_factor;

  // After zoom, re-derive world position so that world_before still maps to screen_anchor
  lm2_v2_f64 world_after = lm2_camera2_screen_to_world_f64(camera, screen_anchor);

  camera.position.x += world_before.x - world_after.x;
  camera.position.y += world_before.y - world_after.y;
  return camera;
}

LM2_API lm2_camera2_f64 lm2_camera2_set_zoom_f64(lm2_camera2_f64 camera, double zoom) {
  camera.zoom = zoom;
  return camera;
}

LM2_API lm2_camera2_f64 lm2_camera2_rotate_f64(lm2_camera2_f64 camera, double delta_radians) {
  camera.rotation += delta_radians;
  return camera;
}

LM2_API lm2_v2_f64 lm2_camera2_get_viewport_size_f64(lm2_camera2_f64 camera) {
  lm2_v2_f64 size;
  size.x = camera.viewport.max.x - camera.viewport.min.x;
  size.y = camera.viewport.max.y - camera.viewport.min.y;
  return size;
}

LM2_API lm2_v2_f64 lm2_camera2_get_viewport_center_f64(lm2_camera2_f64 camera) {
  lm2_v2_f64 center;
  center.x = (camera.viewport.min.x + camera.viewport.max.x) * 0.5;
  center.y = (camera.viewport.min.y + camera.viewport.max.y) * 0.5;
  return center;
}

LM2_API lm2_r2_f64 lm2_camera2_get_world_bounds_f64(lm2_camera2_f64 camera) {
  lm2_v2_f64 size = lm2_camera2_get_viewport_size_f64(camera);
  double half_w = (size.x * 0.5) / camera.zoom;
  double half_h = (size.y * 0.5) / camera.zoom;

  lm2_r2_f64 bounds;
  bounds.min.x = camera.position.x - half_w;
  bounds.min.y = camera.position.y - half_h;
  bounds.max.x = camera.position.x + half_w;
  bounds.max.y = camera.position.y + half_h;
  return bounds;
}

// =============================================================================
// Camera 2D Functions - f32
// =============================================================================

LM2_API lm2_camera2_f32 lm2_camera2_make_f32(lm2_v2_f32 position, float rotation, float zoom, lm2_r2_f32 viewport) {
  lm2_camera2_f32 cam;
  cam.position = position;
  cam.rotation = rotation;
  cam.zoom = zoom;
  cam.viewport = viewport;
  return cam;
}

LM2_API lm2_camera2_f32 lm2_camera2_default_f32(lm2_r2_f32 viewport) {
  lm2_v2_f32 min = viewport.min;
  lm2_v2_f32 max = viewport.max;
  lm2_v2_f32 center;
  center.x = (min.x + max.x) * 0.5f;
  center.y = (min.y + max.y) * 0.5f;
  return lm2_camera2_make_f32(center, 0.0f, 1.0f, viewport);
}

LM2_API lm2_m3x2_f32 lm2_camera2_get_view_f32(lm2_camera2_f32 camera) {
  lm2_v2_f32 min = camera.viewport.min;
  lm2_v2_f32 max = camera.viewport.max;
  lm2_v2_f32 center;
  center.x = (min.x + max.x) * 0.5f;
  center.y = (min.y + max.y) * 0.5f;

  lm2_v2_f32 neg_pos;
  neg_pos.x = -camera.position.x;
  neg_pos.y = -camera.position.y;

  lm2_m3x2_f32 t = lm2_m3x2_translate_f32(neg_pos);
  lm2_m3x2_f32 r = lm2_m3x2_rotate_f32(-camera.rotation);

  lm2_v2_f32 zoom_vec;
  zoom_vec.x = camera.zoom;
  zoom_vec.y = camera.zoom;
  lm2_m3x2_f32 s = lm2_m3x2_scale_f32(zoom_vec);
  lm2_m3x2_f32 tc = lm2_m3x2_translate_f32(center);

  lm2_m3x2_f32 tmp = lm2_m3x2_multiply_f32(r, t);
  tmp = lm2_m3x2_multiply_f32(s, tmp);
  tmp = lm2_m3x2_multiply_f32(tc, tmp);
  return tmp;
}

LM2_API lm2_m3x2_f32 lm2_camera2_get_inv_view_f32(lm2_camera2_f32 camera) {
  return lm2_m3x2_inverse_f32(lm2_camera2_get_view_f32(camera));
}

LM2_API lm2_v2_f32 lm2_camera2_world_to_screen_f32(lm2_camera2_f32 camera, lm2_v2_f32 world_pos) {
  return lm2_m3x2_transform_point_f32(lm2_camera2_get_view_f32(camera), world_pos);
}

LM2_API lm2_v2_f32 lm2_camera2_screen_to_world_f32(lm2_camera2_f32 camera, lm2_v2_f32 screen_pos) {
  return lm2_m3x2_transform_point_f32(lm2_camera2_get_inv_view_f32(camera), screen_pos);
}

LM2_API lm2_camera2_f32 lm2_camera2_move_f32(lm2_camera2_f32 camera, lm2_v2_f32 delta) {
  camera.position.x += delta.x;
  camera.position.y += delta.y;
  return camera;
}

LM2_API lm2_camera2_f32 lm2_camera2_zoom_at_f32(lm2_camera2_f32 camera, float zoom_factor, lm2_v2_f32 screen_anchor) {
  lm2_v2_f32 world_before = lm2_camera2_screen_to_world_f32(camera, screen_anchor);
  camera.zoom *= zoom_factor;
  lm2_v2_f32 world_after = lm2_camera2_screen_to_world_f32(camera, screen_anchor);
  camera.position.x += world_before.x - world_after.x;
  camera.position.y += world_before.y - world_after.y;
  return camera;
}

LM2_API lm2_camera2_f32 lm2_camera2_set_zoom_f32(lm2_camera2_f32 camera, float zoom) {
  camera.zoom = zoom;
  return camera;
}

LM2_API lm2_camera2_f32 lm2_camera2_rotate_f32(lm2_camera2_f32 camera, float delta_radians) {
  camera.rotation += delta_radians;
  return camera;
}

LM2_API lm2_v2_f32 lm2_camera2_get_viewport_size_f32(lm2_camera2_f32 camera) {
  lm2_v2_f32 size;
  size.x = camera.viewport.max.x - camera.viewport.min.x;
  size.y = camera.viewport.max.y - camera.viewport.min.y;
  return size;
}

LM2_API lm2_v2_f32 lm2_camera2_get_viewport_center_f32(lm2_camera2_f32 camera) {
  lm2_v2_f32 center;
  center.x = (camera.viewport.min.x + camera.viewport.max.x) * 0.5f;
  center.y = (camera.viewport.min.y + camera.viewport.max.y) * 0.5f;
  return center;
}

LM2_API lm2_r2_f32 lm2_camera2_get_world_bounds_f32(lm2_camera2_f32 camera) {
  lm2_v2_f32 size = lm2_camera2_get_viewport_size_f32(camera);
  float half_w = (size.x * 0.5f) / camera.zoom;
  float half_h = (size.y * 0.5f) / camera.zoom;

  lm2_r2_f32 bounds;
  bounds.min.x = camera.position.x - half_w;
  bounds.min.y = camera.position.y - half_h;
  bounds.max.x = camera.position.x + half_w;
  bounds.max.y = camera.position.y + half_h;
  return bounds;
}
