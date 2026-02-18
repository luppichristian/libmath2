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

#include <lm2/camera/lm2_camera3.h>
#include <lm2/matrices/lm2_matrix4x4.h>
#include <lm2/misc/lm2_quaternion.h>
#include <lm2/scalar/lm2_trigonometry.h>
#include <lm2/vectors/lm2_vector_specifics.h>

// =============================================================================
// Camera 3D Functions - f64
// =============================================================================

LM2_API lm2_camera3_f64 lm2_camera3_perspective_f64(lm2_v3_f64 position, lm2_v3_f64 target, lm2_v3_f64 up, double fov_y, double aspect, double near_plane, double far_plane) {
  lm2_camera3_f64 cam;
  cam.position = position;
  cam.target = target;
  cam.up = up;
  cam.fov_y = fov_y;
  cam.aspect = aspect;
  cam.near_plane = near_plane;
  cam.far_plane = far_plane;
  cam.ortho_size = 1.0;
  cam.projection = LM2_CAMERA3_PERSPECTIVE;
  return cam;
}

LM2_API lm2_camera3_f64 lm2_camera3_orthographic_f64(lm2_v3_f64 position, lm2_v3_f64 target, lm2_v3_f64 up, double ortho_size, double aspect, double near_plane, double far_plane) {
  lm2_camera3_f64 cam;
  cam.position = position;
  cam.target = target;
  cam.up = up;
  cam.fov_y = 1.0471975511965976;  // pi/3 as default (unused for ortho)
  cam.aspect = aspect;
  cam.near_plane = near_plane;
  cam.far_plane = far_plane;
  cam.ortho_size = ortho_size;
  cam.projection = LM2_CAMERA3_ORTHOGRAPHIC;
  return cam;
}

LM2_API lm2_m4x4_f64 lm2_camera3_get_view_f64(lm2_camera3_f64 camera) {
  return lm2_m4x4_look_at_f64(camera.position, camera.target, camera.up);
}

LM2_API lm2_m4x4_f64 lm2_camera3_get_projection_f64(lm2_camera3_f64 camera) {
  if (camera.projection == LM2_CAMERA3_PERSPECTIVE) {
    return lm2_m4x4_perspective_f64(camera.fov_y, camera.aspect, camera.near_plane, camera.far_plane);
  }
  double h = camera.ortho_size;
  double w = h * camera.aspect;
  return lm2_m4x4_ortho_f64(-w, w, -h, h, camera.near_plane, camera.far_plane);
}

LM2_API lm2_m4x4_f64 lm2_camera3_get_view_projection_f64(lm2_camera3_f64 camera) {
  lm2_m4x4_f64 v = lm2_camera3_get_view_f64(camera);
  lm2_m4x4_f64 p = lm2_camera3_get_projection_f64(camera);
  return lm2_m4x4_multiply_f64(p, v);
}

LM2_API lm2_m4x4_f64 lm2_camera3_get_inv_view_f64(lm2_camera3_f64 camera) {
  return lm2_m4x4_inverse_f64(lm2_camera3_get_view_f64(camera));
}

LM2_API lm2_v3_f64 lm2_camera3_get_forward_f64(lm2_camera3_f64 camera) {
  lm2_v3_f64 dir;
  dir.x = camera.target.x - camera.position.x;
  dir.y = camera.target.y - camera.position.y;
  dir.z = camera.target.z - camera.position.z;
  return lm2_v3_normalize_f64(dir);
}

LM2_API lm2_v3_f64 lm2_camera3_get_right_f64(lm2_camera3_f64 camera) {
  lm2_v3_f64 fwd = lm2_camera3_get_forward_f64(camera);
  lm2_v3_f64 right = lm2_v3_cross_f64(fwd, camera.up);
  return lm2_v3_normalize_f64(right);
}

LM2_API lm2_v3_f64 lm2_camera3_get_up_f64(lm2_camera3_f64 camera) {
  lm2_v3_f64 fwd = lm2_camera3_get_forward_f64(camera);
  lm2_v3_f64 right = lm2_camera3_get_right_f64(camera);
  return lm2_v3_cross_f64(right, fwd);
}

LM2_API lm2_camera3_f64 lm2_camera3_move_f64(lm2_camera3_f64 camera, lm2_v3_f64 delta) {
  camera.position.x += delta.x;
  camera.position.y += delta.y;
  camera.position.z += delta.z;
  camera.target.x += delta.x;
  camera.target.y += delta.y;
  camera.target.z += delta.z;
  return camera;
}

LM2_API lm2_camera3_f64 lm2_camera3_look_at_f64(lm2_camera3_f64 camera, lm2_v3_f64 target) {
  camera.target = target;
  return camera;
}

LM2_API lm2_camera3_f64 lm2_camera3_orbit_f64(lm2_camera3_f64 camera, double yaw, double pitch) {
  // Orbit camera around the target point
  lm2_v3_f64 offset;
  offset.x = camera.position.x - camera.target.x;
  offset.y = camera.position.y - camera.target.y;
  offset.z = camera.position.z - camera.target.z;

  double radius = lm2_v3_length_f64(offset);
  double theta = lm2_atan2_f64(offset.x, offset.z) + yaw;
  // Use atan2 to compute polar angle from y-axis robustly
  double xz_len = lm2_sqrt_f64(offset.x * offset.x + offset.z * offset.z);
  double phi = lm2_atan2_f64(xz_len, offset.y) + pitch;

  // Clamp phi to avoid gimbal lock at poles
  if (phi < 0.01) phi = 0.01;
  if (phi > 3.13159265358979323846) phi = 3.13159265358979323846;

  lm2_v3_f64 new_offset;
  new_offset.x = radius * lm2_sin_f64(phi) * lm2_sin_f64(theta);
  new_offset.y = radius * lm2_cos_f64(phi);
  new_offset.z = radius * lm2_sin_f64(phi) * lm2_cos_f64(theta);

  camera.position.x = camera.target.x + new_offset.x;
  camera.position.y = camera.target.y + new_offset.y;
  camera.position.z = camera.target.z + new_offset.z;
  return camera;
}

LM2_API lm2_camera3_f64 lm2_camera3_set_aspect_f64(lm2_camera3_f64 camera, double aspect) {
  camera.aspect = aspect;
  return camera;
}

LM2_API lm2_camera3_f64 lm2_camera3_set_fov_y_f64(lm2_camera3_f64 camera, double fov_y) {
  camera.fov_y = fov_y;
  return camera;
}

LM2_API lm2_v3_f64 lm2_camera3_world_to_ndc_f64(lm2_camera3_f64 camera, lm2_v3_f64 world_pos) {
  lm2_m4x4_f64 vp = lm2_camera3_get_view_projection_f64(camera);
  lm2_v4_f64 clip = lm2_m4x4_transform_f64(vp, (lm2_v4_f64) {world_pos.x, world_pos.y, world_pos.z, 1.0});
  lm2_v3_f64 ndc;
  ndc.x = clip.x / clip.w;
  ndc.y = clip.y / clip.w;
  ndc.z = clip.z / clip.w;
  return ndc;
}

LM2_API lm2_v3_f64 lm2_camera3_ndc_to_world_f64(lm2_camera3_f64 camera, lm2_v3_f64 ndc_pos) {
  lm2_m4x4_f64 inv_vp = lm2_m4x4_inverse_f64(lm2_camera3_get_view_projection_f64(camera));
  lm2_v4_f64 clip = lm2_m4x4_transform_f64(inv_vp, (lm2_v4_f64) {ndc_pos.x, ndc_pos.y, ndc_pos.z, 1.0});
  lm2_v3_f64 world;
  world.x = clip.x / clip.w;
  world.y = clip.y / clip.w;
  world.z = clip.z / clip.w;
  return world;
}

// =============================================================================
// Camera 3D Functions - f32
// =============================================================================

LM2_API lm2_camera3_f32 lm2_camera3_perspective_f32(lm2_v3_f32 position, lm2_v3_f32 target, lm2_v3_f32 up, float fov_y, float aspect, float near_plane, float far_plane) {
  lm2_camera3_f32 cam;
  cam.position = position;
  cam.target = target;
  cam.up = up;
  cam.fov_y = fov_y;
  cam.aspect = aspect;
  cam.near_plane = near_plane;
  cam.far_plane = far_plane;
  cam.ortho_size = 1.0f;
  cam.projection = LM2_CAMERA3_PERSPECTIVE;
  return cam;
}

LM2_API lm2_camera3_f32 lm2_camera3_orthographic_f32(lm2_v3_f32 position, lm2_v3_f32 target, lm2_v3_f32 up, float ortho_size, float aspect, float near_plane, float far_plane) {
  lm2_camera3_f32 cam;
  cam.position = position;
  cam.target = target;
  cam.up = up;
  cam.fov_y = 1.0471975f;
  cam.aspect = aspect;
  cam.near_plane = near_plane;
  cam.far_plane = far_plane;
  cam.ortho_size = ortho_size;
  cam.projection = LM2_CAMERA3_ORTHOGRAPHIC;
  return cam;
}

LM2_API lm2_m4x4_f32 lm2_camera3_get_view_f32(lm2_camera3_f32 camera) {
  return lm2_m4x4_look_at_f32(camera.position, camera.target, camera.up);
}

LM2_API lm2_m4x4_f32 lm2_camera3_get_projection_f32(lm2_camera3_f32 camera) {
  if (camera.projection == LM2_CAMERA3_PERSPECTIVE) {
    return lm2_m4x4_perspective_f32(camera.fov_y, camera.aspect, camera.near_plane, camera.far_plane);
  }
  float h = camera.ortho_size;
  float w = h * camera.aspect;
  return lm2_m4x4_ortho_f32(-w, w, -h, h, camera.near_plane, camera.far_plane);
}

LM2_API lm2_m4x4_f32 lm2_camera3_get_view_projection_f32(lm2_camera3_f32 camera) {
  lm2_m4x4_f32 v = lm2_camera3_get_view_f32(camera);
  lm2_m4x4_f32 p = lm2_camera3_get_projection_f32(camera);
  return lm2_m4x4_multiply_f32(p, v);
}

LM2_API lm2_m4x4_f32 lm2_camera3_get_inv_view_f32(lm2_camera3_f32 camera) {
  return lm2_m4x4_inverse_f32(lm2_camera3_get_view_f32(camera));
}

LM2_API lm2_v3_f32 lm2_camera3_get_forward_f32(lm2_camera3_f32 camera) {
  lm2_v3_f32 dir;
  dir.x = camera.target.x - camera.position.x;
  dir.y = camera.target.y - camera.position.y;
  dir.z = camera.target.z - camera.position.z;
  return lm2_v3_normalize_f32(dir);
}

LM2_API lm2_v3_f32 lm2_camera3_get_right_f32(lm2_camera3_f32 camera) {
  lm2_v3_f32 fwd = lm2_camera3_get_forward_f32(camera);
  lm2_v3_f32 right = lm2_v3_cross_f32(fwd, camera.up);
  return lm2_v3_normalize_f32(right);
}

LM2_API lm2_v3_f32 lm2_camera3_get_up_f32(lm2_camera3_f32 camera) {
  lm2_v3_f32 fwd = lm2_camera3_get_forward_f32(camera);
  lm2_v3_f32 right = lm2_camera3_get_right_f32(camera);
  return lm2_v3_cross_f32(right, fwd);
}

LM2_API lm2_camera3_f32 lm2_camera3_move_f32(lm2_camera3_f32 camera, lm2_v3_f32 delta) {
  camera.position.x += delta.x;
  camera.position.y += delta.y;
  camera.position.z += delta.z;
  camera.target.x += delta.x;
  camera.target.y += delta.y;
  camera.target.z += delta.z;
  return camera;
}

LM2_API lm2_camera3_f32 lm2_camera3_look_at_f32(lm2_camera3_f32 camera, lm2_v3_f32 target) {
  camera.target = target;
  return camera;
}

LM2_API lm2_camera3_f32 lm2_camera3_orbit_f32(lm2_camera3_f32 camera, float yaw, float pitch) {
  lm2_v3_f32 offset;
  offset.x = camera.position.x - camera.target.x;
  offset.y = camera.position.y - camera.target.y;
  offset.z = camera.position.z - camera.target.z;

  float radius = lm2_v3_length_f32(offset);
  float theta = lm2_atan2_f32(offset.x, offset.z) + yaw;
  float xz_len = lm2_sqrt_f32(offset.x * offset.x + offset.z * offset.z);
  float phi = lm2_atan2_f32(xz_len, offset.y) + pitch;

  if (phi < 0.01f) phi = 0.01f;
  if (phi > 3.13159265f) phi = 3.13159265f;

  lm2_v3_f32 new_offset;
  new_offset.x = radius * lm2_sin_f32(phi) * lm2_sin_f32(theta);
  new_offset.y = radius * lm2_cos_f32(phi);
  new_offset.z = radius * lm2_sin_f32(phi) * lm2_cos_f32(theta);

  camera.position.x = camera.target.x + new_offset.x;
  camera.position.y = camera.target.y + new_offset.y;
  camera.position.z = camera.target.z + new_offset.z;
  return camera;
}

LM2_API lm2_camera3_f32 lm2_camera3_set_aspect_f32(lm2_camera3_f32 camera, float aspect) {
  camera.aspect = aspect;
  return camera;
}

LM2_API lm2_camera3_f32 lm2_camera3_set_fov_y_f32(lm2_camera3_f32 camera, float fov_y) {
  camera.fov_y = fov_y;
  return camera;
}

LM2_API lm2_v3_f32 lm2_camera3_world_to_ndc_f32(lm2_camera3_f32 camera, lm2_v3_f32 world_pos) {
  lm2_m4x4_f32 vp = lm2_camera3_get_view_projection_f32(camera);
  lm2_v4_f32 clip = lm2_m4x4_transform_f32(vp, (lm2_v4_f32) {world_pos.x, world_pos.y, world_pos.z, 1.0f});
  lm2_v3_f32 ndc;
  ndc.x = clip.x / clip.w;
  ndc.y = clip.y / clip.w;
  ndc.z = clip.z / clip.w;
  return ndc;
}

LM2_API lm2_v3_f32 lm2_camera3_ndc_to_world_f32(lm2_camera3_f32 camera, lm2_v3_f32 ndc_pos) {
  lm2_m4x4_f32 inv_vp = lm2_m4x4_inverse_f32(lm2_camera3_get_view_projection_f32(camera));
  lm2_v4_f32 clip = lm2_m4x4_transform_f32(inv_vp, (lm2_v4_f32) {ndc_pos.x, ndc_pos.y, ndc_pos.z, 1.0f});
  lm2_v3_f32 world;
  world.x = clip.x / clip.w;
  world.y = clip.y / clip.w;
  world.z = clip.z / clip.w;
  return world;
}

// =============================================================================
// Camera 3D Quaternion Functions - f64
// =============================================================================

// Build a camera from a position and an orientation quaternion.
// The quaternion defines the camera's rotation relative to the default
// orientation (looking down -Z with up = +Y).
// The target is reconstructed by rotating the default forward (0,0,-1) by
// the quaternion and adding it to the position.
LM2_API lm2_camera3_f64 lm2_camera3_from_quat_f64(lm2_v3_f64 position, lm2_quat_f64 orientation, double fov_y, double aspect, double near_plane, double far_plane) {
  lm2_v3_f64 default_forward = {0.0, 0.0, -1.0};
  lm2_v3_f64 default_up = {0.0, 1.0, 0.0};
  lm2_v3_f64 fwd = lm2_quat_rotate_vector_f64(orientation, default_forward);
  lm2_v3_f64 up = lm2_quat_rotate_vector_f64(orientation, default_up);
  lm2_v3_f64 target;
  target.x = position.x + fwd.x;
  target.y = position.y + fwd.y;
  target.z = position.z + fwd.z;
  lm2_camera3_f64 cam;
  cam.position = position;
  cam.target = target;
  cam.up = up;
  cam.fov_y = fov_y;
  cam.aspect = aspect;
  cam.near_plane = near_plane;
  cam.far_plane = far_plane;
  cam.ortho_size = 1.0;
  cam.projection = LM2_CAMERA3_PERSPECTIVE;
  return cam;
}

// Extract the current orientation as a quaternion from the view matrix.
LM2_API lm2_quat_f64 lm2_camera3_get_orientation_f64(lm2_camera3_f64 camera) {
  lm2_m4x4_f64 view = lm2_camera3_get_view_f64(camera);
  return lm2_m4x4_to_quat_f64(view);
}

// Replace the camera orientation with the given quaternion, keeping position.
LM2_API lm2_camera3_f64 lm2_camera3_set_orientation_f64(lm2_camera3_f64 camera, lm2_quat_f64 orientation) {
  lm2_v3_f64 default_forward = {0.0, 0.0, -1.0};
  lm2_v3_f64 default_up = {0.0, 1.0, 0.0};
  lm2_v3_f64 fwd = lm2_quat_rotate_vector_f64(orientation, default_forward);
  lm2_v3_f64 up = lm2_quat_rotate_vector_f64(orientation, default_up);
  camera.target.x = camera.position.x + fwd.x;
  camera.target.y = camera.position.y + fwd.y;
  camera.target.z = camera.position.z + fwd.z;
  camera.up = up;
  return camera;
}

// Apply an additional rotation (in camera-local space) to the orientation.
LM2_API lm2_camera3_f64 lm2_camera3_rotate_local_f64(lm2_camera3_f64 camera, lm2_quat_f64 rotation) {
  // get_orientation extracts from the view matrix (inverse of camera rotation),
  // so conjugate to recover the actual camera orientation before composing.
  lm2_quat_f64 current = lm2_quat_conjugate_f64(lm2_camera3_get_orientation_f64(camera));
  lm2_quat_f64 next = lm2_quat_normalize_f64(lm2_quat_multiply_f64(current, rotation));
  return lm2_camera3_set_orientation_f64(camera, next);
}

// =============================================================================
// Camera 3D Quaternion Functions - f32
// =============================================================================

LM2_API lm2_camera3_f32 lm2_camera3_from_quat_f32(lm2_v3_f32 position, lm2_quat_f32 orientation, float fov_y, float aspect, float near_plane, float far_plane) {
  lm2_v3_f32 default_forward = {0.0f, 0.0f, -1.0f};
  lm2_v3_f32 default_up = {0.0f, 1.0f, 0.0f};
  lm2_v3_f32 fwd = lm2_quat_rotate_vector_f32(orientation, default_forward);
  lm2_v3_f32 up = lm2_quat_rotate_vector_f32(orientation, default_up);
  lm2_v3_f32 target;
  target.x = position.x + fwd.x;
  target.y = position.y + fwd.y;
  target.z = position.z + fwd.z;
  lm2_camera3_f32 cam;
  cam.position = position;
  cam.target = target;
  cam.up = up;
  cam.fov_y = fov_y;
  cam.aspect = aspect;
  cam.near_plane = near_plane;
  cam.far_plane = far_plane;
  cam.ortho_size = 1.0f;
  cam.projection = LM2_CAMERA3_PERSPECTIVE;
  return cam;
}

LM2_API lm2_quat_f32 lm2_camera3_get_orientation_f32(lm2_camera3_f32 camera) {
  lm2_m4x4_f32 view = lm2_camera3_get_view_f32(camera);
  return lm2_m4x4_to_quat_f32(view);
}

LM2_API lm2_camera3_f32 lm2_camera3_set_orientation_f32(lm2_camera3_f32 camera, lm2_quat_f32 orientation) {
  lm2_v3_f32 default_forward = {0.0f, 0.0f, -1.0f};
  lm2_v3_f32 default_up = {0.0f, 1.0f, 0.0f};
  lm2_v3_f32 fwd = lm2_quat_rotate_vector_f32(orientation, default_forward);
  lm2_v3_f32 up = lm2_quat_rotate_vector_f32(orientation, default_up);
  camera.target.x = camera.position.x + fwd.x;
  camera.target.y = camera.position.y + fwd.y;
  camera.target.z = camera.position.z + fwd.z;
  camera.up = up;
  return camera;
}

LM2_API lm2_camera3_f32 lm2_camera3_rotate_local_f32(lm2_camera3_f32 camera, lm2_quat_f32 rotation) {
  // get_orientation extracts from the view matrix (inverse of camera rotation),
  // so conjugate to recover the actual camera orientation before composing.
  lm2_quat_f32 current = lm2_quat_conjugate_f32(lm2_camera3_get_orientation_f32(camera));
  lm2_quat_f32 next = lm2_quat_normalize_f32(lm2_quat_multiply_f32(current, rotation));
  return lm2_camera3_set_orientation_f32(camera, next);
}
