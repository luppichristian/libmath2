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

#include <gtest/gtest.h>
#include <cmath>
#include "lm2/camera/lm2_camera3.h"
#include "lm2/lm2_constants.h"
#include "lm2/matrices/lm2_matrix4x4.h"
#include "lm2/misc/lm2_quaternion.h"

class Camera3Test : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-4f;
  static constexpr double EPSILON_F64 = 1e-8;

  // Standard perspective camera looking down -Z
  lm2_camera3_f64 make_default_f64() {
    lm2_v3_f64 pos = {0.0, 0.0, 5.0};
    lm2_v3_f64 target = {0.0, 0.0, 0.0};
    lm2_v3_f64 up = {0.0, 1.0, 0.0};
    return lm2_camera3_perspective_f64(pos, target, up, LM2_PI_F64 / 3.0, 16.0 / 9.0, 0.1, 1000.0);
  }

  lm2_camera3_f32 make_default_f32() {
    lm2_v3_f32 pos = {0.0f, 0.0f, 5.0f};
    lm2_v3_f32 target = {0.0f, 0.0f, 0.0f};
    lm2_v3_f32 up = {0.0f, 1.0f, 0.0f};
    return lm2_camera3_perspective_f32(pos, target, up, LM2_PI_F32 / 3.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
  }
};

// =============================================================================
// Construction - f64
// =============================================================================

TEST_F(Camera3Test, Perspective_F64) {
  lm2_camera3_f64 cam = make_default_f64();

  EXPECT_DOUBLE_EQ(cam.position.z, 5.0);
  EXPECT_DOUBLE_EQ(cam.target.x, 0.0);
  EXPECT_DOUBLE_EQ(cam.near_plane, 0.1);
  EXPECT_DOUBLE_EQ(cam.far_plane, 1000.0);
  EXPECT_EQ(cam.projection, LM2_CAMERA3_PERSPECTIVE);
}

TEST_F(Camera3Test, Orthographic_F64) {
  lm2_v3_f64 pos = {0.0, 0.0, 10.0};
  lm2_v3_f64 target = {0.0, 0.0, 0.0};
  lm2_v3_f64 up = {0.0, 1.0, 0.0};
  lm2_camera3_f64 cam = lm2_camera3_orthographic_f64(pos, target, up, 5.0, 1.0, 0.1, 100.0);

  EXPECT_DOUBLE_EQ(cam.ortho_size, 5.0);
  EXPECT_EQ(cam.projection, LM2_CAMERA3_ORTHOGRAPHIC);
}

// =============================================================================
// View matrix - f64
// =============================================================================

TEST_F(Camera3Test, ViewMatrix_NotIdentity_F64) {
  lm2_camera3_f64 cam = make_default_f64();
  lm2_m4x4_f64 view = lm2_camera3_get_view_f64(cam);

  // Camera is offset from origin, so view matrix is not identity
  // The translation column (m03, m13, m23) should be non-trivial
  EXPECT_FALSE(view.m03 == 0.0 && view.m13 == 0.0 && view.m23 == 0.0);
}

TEST_F(Camera3Test, InvView_IsViewInverse_F64) {
  lm2_camera3_f64 cam = make_default_f64();
  lm2_m4x4_f64 view = lm2_camera3_get_view_f64(cam);
  lm2_m4x4_f64 inv = lm2_camera3_get_inv_view_f64(cam);
  lm2_m4x4_f64 product = lm2_m4x4_multiply_f64(view, inv);

  EXPECT_NEAR(product.m00, 1.0, EPSILON_F64);
  EXPECT_NEAR(product.m11, 1.0, EPSILON_F64);
  EXPECT_NEAR(product.m22, 1.0, EPSILON_F64);
  EXPECT_NEAR(product.m33, 1.0, EPSILON_F64);
  EXPECT_NEAR(product.m01, 0.0, EPSILON_F64);
  EXPECT_NEAR(product.m10, 0.0, EPSILON_F64);
  EXPECT_NEAR(product.m02, 0.0, EPSILON_F64);
  EXPECT_NEAR(product.m20, 0.0, EPSILON_F64);
}

// =============================================================================
// Direction vectors - f64
// =============================================================================

TEST_F(Camera3Test, Forward_F64) {
  lm2_camera3_f64 cam = make_default_f64();
  lm2_v3_f64 fwd = lm2_camera3_get_forward_f64(cam);

  // Camera at (0,0,5) looking at (0,0,0) → forward is (0,0,-1)
  EXPECT_NEAR(fwd.x, 0.0, EPSILON_F64);
  EXPECT_NEAR(fwd.y, 0.0, EPSILON_F64);
  EXPECT_NEAR(fwd.z, -1.0, EPSILON_F64);
}

TEST_F(Camera3Test, Right_F64) {
  lm2_camera3_f64 cam = make_default_f64();
  lm2_v3_f64 right = lm2_camera3_get_right_f64(cam);

  // Camera looking down -Z with world up (0,1,0) → right is (1,0,0)
  EXPECT_NEAR(right.x, 1.0, EPSILON_F64);
  EXPECT_NEAR(right.y, 0.0, EPSILON_F64);
  EXPECT_NEAR(right.z, 0.0, EPSILON_F64);
}

TEST_F(Camera3Test, Up_F64) {
  lm2_camera3_f64 cam = make_default_f64();
  lm2_v3_f64 up = lm2_camera3_get_up_f64(cam);

  // Camera looking down -Z with right (1,0,0) → computed up is (0,1,0)
  EXPECT_NEAR(up.x, 0.0, EPSILON_F64);
  EXPECT_NEAR(up.y, 1.0, EPSILON_F64);
  EXPECT_NEAR(up.z, 0.0, EPSILON_F64);
}

// =============================================================================
// Camera manipulation - f64
// =============================================================================

TEST_F(Camera3Test, Move_KeepsRelativeOffset_F64) {
  lm2_camera3_f64 cam = make_default_f64();
  lm2_v3_f64 delta = {1.0, 2.0, -3.0};
  lm2_camera3_f64 moved = lm2_camera3_move_f64(cam, delta);

  EXPECT_DOUBLE_EQ(moved.position.x, cam.position.x + delta.x);
  EXPECT_DOUBLE_EQ(moved.position.y, cam.position.y + delta.y);
  EXPECT_DOUBLE_EQ(moved.position.z, cam.position.z + delta.z);
  EXPECT_DOUBLE_EQ(moved.target.x, cam.target.x + delta.x);
  EXPECT_DOUBLE_EQ(moved.target.y, cam.target.y + delta.y);
  EXPECT_DOUBLE_EQ(moved.target.z, cam.target.z + delta.z);
}

TEST_F(Camera3Test, LookAt_F64) {
  lm2_camera3_f64 cam = make_default_f64();
  lm2_v3_f64 new_target = {1.0, 2.0, 3.0};
  lm2_camera3_f64 updated = lm2_camera3_look_at_f64(cam, new_target);

  EXPECT_DOUBLE_EQ(updated.target.x, new_target.x);
  EXPECT_DOUBLE_EQ(updated.target.y, new_target.y);
  EXPECT_DOUBLE_EQ(updated.target.z, new_target.z);
}

TEST_F(Camera3Test, SetAspect_F64) {
  lm2_camera3_f64 cam = make_default_f64();
  cam = lm2_camera3_set_aspect_f64(cam, 4.0 / 3.0);
  EXPECT_DOUBLE_EQ(cam.aspect, 4.0 / 3.0);
}

TEST_F(Camera3Test, SetFovY_F64) {
  lm2_camera3_f64 cam = make_default_f64();
  cam = lm2_camera3_set_fov_y_f64(cam, 1.2);
  EXPECT_DOUBLE_EQ(cam.fov_y, 1.2);
}

// =============================================================================
// Projection matrices - f64
// =============================================================================

TEST_F(Camera3Test, PerspectiveProjection_M33_Is_Negative1_F64) {
  // In a standard perspective matrix (row-major) m32 = -1 (perspective divide row)
  lm2_camera3_f64 cam = make_default_f64();
  lm2_m4x4_f64 proj = lm2_camera3_get_projection_f64(cam);

  EXPECT_NEAR(proj.m32, -1.0, EPSILON_F64);
  EXPECT_NEAR(proj.m33, 0.0, EPSILON_F64);
}

TEST_F(Camera3Test, OrthoProjection_M33_Is_1_F64) {
  lm2_v3_f64 pos = {0.0, 0.0, 10.0};
  lm2_v3_f64 target = {0.0, 0.0, 0.0};
  lm2_v3_f64 up = {0.0, 1.0, 0.0};
  lm2_camera3_f64 cam = lm2_camera3_orthographic_f64(pos, target, up, 5.0, 1.0, 0.1, 100.0);
  lm2_m4x4_f64 proj = lm2_camera3_get_projection_f64(cam);

  // In an orthographic matrix m33 = 1 (no perspective divide)
  EXPECT_NEAR(proj.m33, 1.0, EPSILON_F64);
}

// =============================================================================
// NDC round-trip - f64
// =============================================================================

TEST_F(Camera3Test, NdcRoundTrip_F64) {
  lm2_camera3_f64 cam = make_default_f64();
  lm2_v3_f64 world_in = {0.5, -0.3, 1.0};
  lm2_v3_f64 ndc = lm2_camera3_world_to_ndc_f64(cam, world_in);
  lm2_v3_f64 world_out = lm2_camera3_ndc_to_world_f64(cam, ndc);

  EXPECT_NEAR(world_out.x, world_in.x, 1e-6);
  EXPECT_NEAR(world_out.y, world_in.y, 1e-6);
  EXPECT_NEAR(world_out.z, world_in.z, 1e-6);
}

// =============================================================================
// Construction - f32
// =============================================================================

TEST_F(Camera3Test, Perspective_F32) {
  lm2_camera3_f32 cam = make_default_f32();

  EXPECT_FLOAT_EQ(cam.position.z, 5.0f);
  EXPECT_FLOAT_EQ(cam.near_plane, 0.1f);
  EXPECT_EQ(cam.projection, LM2_CAMERA3_PERSPECTIVE);
}

TEST_F(Camera3Test, Forward_F32) {
  lm2_camera3_f32 cam = make_default_f32();
  lm2_v3_f32 fwd = lm2_camera3_get_forward_f32(cam);

  EXPECT_NEAR(fwd.x, 0.0f, EPSILON_F32);
  EXPECT_NEAR(fwd.y, 0.0f, EPSILON_F32);
  EXPECT_NEAR(fwd.z, -1.0f, EPSILON_F32);
}

TEST_F(Camera3Test, InvView_IsViewInverse_F32) {
  lm2_camera3_f32 cam = make_default_f32();
  lm2_m4x4_f32 view = lm2_camera3_get_view_f32(cam);
  lm2_m4x4_f32 inv = lm2_camera3_get_inv_view_f32(cam);
  lm2_m4x4_f32 product = lm2_m4x4_multiply_f32(view, inv);

  EXPECT_NEAR(product.m00, 1.0f, EPSILON_F32);
  EXPECT_NEAR(product.m11, 1.0f, EPSILON_F32);
  EXPECT_NEAR(product.m22, 1.0f, EPSILON_F32);
  EXPECT_NEAR(product.m33, 1.0f, EPSILON_F32);
  EXPECT_NEAR(product.m01, 0.0f, EPSILON_F32);
  EXPECT_NEAR(product.m10, 0.0f, EPSILON_F32);
}

TEST_F(Camera3Test, NdcRoundTrip_F32) {
  lm2_camera3_f32 cam = make_default_f32();
  lm2_v3_f32 world_in = {0.5f, -0.3f, 1.0f};
  lm2_v3_f32 ndc = lm2_camera3_world_to_ndc_f32(cam, world_in);
  lm2_v3_f32 world_out = lm2_camera3_ndc_to_world_f32(cam, ndc);

  EXPECT_NEAR(world_out.x, world_in.x, EPSILON_F32);
  EXPECT_NEAR(world_out.y, world_in.y, EPSILON_F32);
  EXPECT_NEAR(world_out.z, world_in.z, EPSILON_F32);
}

// =============================================================================
// Quaternion orientation - f64
// =============================================================================

TEST_F(Camera3Test, FromQuat_Identity_SameasDefault_F64) {
  // Identity quaternion looking down -Z should produce the same view as
  // a look_at from (0,0,5) to (0,0,0).
  lm2_v3_f64 pos = {0.0, 0.0, 5.0};
  lm2_quat_f64 identity = lm2_quat_identity_f64();
  lm2_camera3_f64 qcam = lm2_camera3_from_quat_f64(pos, identity, LM2_PI_F64 / 3.0, 16.0 / 9.0, 0.1, 1000.0);
  lm2_camera3_f64 lcam = make_default_f64();

  lm2_m4x4_f64 qview = lm2_camera3_get_view_f64(qcam);
  lm2_m4x4_f64 lview = lm2_camera3_get_view_f64(lcam);

  for (int i = 0; i < 16; i++) {
    EXPECT_NEAR(qview.e[i], lview.e[i], 1e-6);
  }
}

TEST_F(Camera3Test, GetOrientation_RoundTrip_F64) {
  // Extract orientation from an existing camera, then rebuild via from_quat;
  // the view matrices should match.
  lm2_camera3_f64 cam = make_default_f64();
  lm2_quat_f64 orient = lm2_camera3_get_orientation_f64(cam);
  lm2_camera3_f64 rebuilt = lm2_camera3_from_quat_f64(
      cam.position, orient, cam.fov_y, cam.aspect, cam.near_plane, cam.far_plane);

  lm2_m4x4_f64 va = lm2_camera3_get_view_f64(cam);
  lm2_m4x4_f64 vb = lm2_camera3_get_view_f64(rebuilt);
  for (int i = 0; i < 16; i++) {
    EXPECT_NEAR(va.e[i], vb.e[i], 1e-6);
  }
}

TEST_F(Camera3Test, SetOrientation_ChangesForward_F64) {
  lm2_camera3_f64 cam = make_default_f64();  // looking down -Z

  // Rotate 90 degrees around Y → camera should now look down -X
  lm2_v3_f64 y_axis = {0.0, 1.0, 0.0};
  lm2_quat_f64 rot90y = lm2_quat_from_axis_angle_f64(y_axis, LM2_PI_F64 / 2.0);
  lm2_camera3_f64 rotated = lm2_camera3_set_orientation_f64(cam, rot90y);

  lm2_v3_f64 fwd = lm2_camera3_get_forward_f64(rotated);
  EXPECT_NEAR(fwd.x, -1.0, 1e-6);
  EXPECT_NEAR(fwd.y, 0.0, 1e-6);
  EXPECT_NEAR(fwd.z, 0.0, 1e-6);
}

TEST_F(Camera3Test, RotateLocal_ComposesTwoRotations_F64) {
  lm2_camera3_f64 cam = make_default_f64();

  // Two 45-degree Y rotations should equal one 90-degree Y rotation
  lm2_v3_f64 y_axis = {0.0, 1.0, 0.0};
  lm2_quat_f64 r45 = lm2_quat_from_axis_angle_f64(y_axis, LM2_PI_F64 / 4.0);
  lm2_camera3_f64 after1 = lm2_camera3_rotate_local_f64(cam, r45);
  lm2_camera3_f64 after2 = lm2_camera3_rotate_local_f64(after1, r45);

  lm2_quat_f64 r90 = lm2_quat_from_axis_angle_f64(y_axis, LM2_PI_F64 / 2.0);
  lm2_camera3_f64 ref = lm2_camera3_set_orientation_f64(cam, r90);

  lm2_v3_f64 fwd_composed = lm2_camera3_get_forward_f64(after2);
  lm2_v3_f64 fwd_ref = lm2_camera3_get_forward_f64(ref);
  EXPECT_NEAR(fwd_composed.x, fwd_ref.x, 1e-6);
  EXPECT_NEAR(fwd_composed.y, fwd_ref.y, 1e-6);
  EXPECT_NEAR(fwd_composed.z, fwd_ref.z, 1e-6);
}

// =============================================================================
// Quaternion orientation - f32
// =============================================================================

TEST_F(Camera3Test, FromQuat_Identity_SameasDefault_F32) {
  lm2_v3_f32 pos = {0.0f, 0.0f, 5.0f};
  lm2_quat_f32 identity = lm2_quat_identity_f32();
  lm2_camera3_f32 qcam = lm2_camera3_from_quat_f32(pos, identity, LM2_PI_F32 / 3.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
  lm2_camera3_f32 lcam = make_default_f32();

  lm2_m4x4_f32 qview = lm2_camera3_get_view_f32(qcam);
  lm2_m4x4_f32 lview = lm2_camera3_get_view_f32(lcam);

  for (int i = 0; i < 16; i++) {
    EXPECT_NEAR(qview.e[i], lview.e[i], EPSILON_F32);
  }
}

TEST_F(Camera3Test, SetOrientation_ChangesForward_F32) {
  lm2_camera3_f32 cam = make_default_f32();

  lm2_v3_f32 y_axis = {0.0f, 1.0f, 0.0f};
  lm2_quat_f32 rot90y = lm2_quat_from_axis_angle_f32(y_axis, LM2_PI_F32 / 2.0f);
  lm2_camera3_f32 rotated = lm2_camera3_set_orientation_f32(cam, rot90y);

  lm2_v3_f32 fwd = lm2_camera3_get_forward_f32(rotated);
  EXPECT_NEAR(fwd.x, -1.0f, EPSILON_F32);
  EXPECT_NEAR(fwd.y, 0.0f, EPSILON_F32);
  EXPECT_NEAR(fwd.z, 0.0f, EPSILON_F32);
}
