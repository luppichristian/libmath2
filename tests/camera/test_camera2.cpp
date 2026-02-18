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
#include "lm2/camera/lm2_camera2.h"
#include "lm2/lm2_constants.h"

class Camera2Test : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-9;
};

// =============================================================================
// Construction - f64
// =============================================================================

TEST_F(Camera2Test, Make_F64) {
  lm2_v2_f64 pos = {10.0, 20.0};
  lm2_r2_f64 vp = lm2_r2_from_min_max_f64({0.0, 0.0}, {800.0, 600.0});
  lm2_camera2_f64 c = lm2_camera2_make_f64(pos, 0.5, 2.0, vp);

  EXPECT_DOUBLE_EQ(c.position.x, 10.0);
  EXPECT_DOUBLE_EQ(c.position.y, 20.0);
  EXPECT_DOUBLE_EQ(c.rotation, 0.5);
  EXPECT_DOUBLE_EQ(c.zoom, 2.0);
  EXPECT_DOUBLE_EQ(c.viewport.min.x, 0.0);
  EXPECT_DOUBLE_EQ(c.viewport.max.x, 800.0);
}

TEST_F(Camera2Test, Default_F64) {
  lm2_r2_f64 vp = lm2_r2_from_min_max_f64({0.0, 0.0}, {1280.0, 720.0});
  lm2_camera2_f64 c = lm2_camera2_default_f64(vp);

  EXPECT_DOUBLE_EQ(c.position.x, 640.0);
  EXPECT_DOUBLE_EQ(c.position.y, 360.0);
  EXPECT_DOUBLE_EQ(c.rotation, 0.0);
  EXPECT_DOUBLE_EQ(c.zoom, 1.0);
}

// =============================================================================
// Viewport helpers - f64
// =============================================================================

TEST_F(Camera2Test, ViewportSize_F64) {
  lm2_r2_f64 vp = lm2_r2_from_min_max_f64({0.0, 0.0}, {800.0, 600.0});
  lm2_camera2_f64 c = lm2_camera2_default_f64(vp);
  lm2_v2_f64 size = lm2_camera2_get_viewport_size_f64(c);

  EXPECT_DOUBLE_EQ(size.x, 800.0);
  EXPECT_DOUBLE_EQ(size.y, 600.0);
}

TEST_F(Camera2Test, ViewportCenter_F64) {
  lm2_r2_f64 vp = lm2_r2_from_min_max_f64({0.0, 0.0}, {800.0, 600.0});
  lm2_camera2_f64 c = lm2_camera2_default_f64(vp);
  lm2_v2_f64 ctr = lm2_camera2_get_viewport_center_f64(c);

  EXPECT_DOUBLE_EQ(ctr.x, 400.0);
  EXPECT_DOUBLE_EQ(ctr.y, 300.0);
}

TEST_F(Camera2Test, WorldBounds_NoZoom_F64) {
  lm2_r2_f64 vp = lm2_r2_from_min_max_f64({0.0, 0.0}, {800.0, 600.0});
  lm2_camera2_f64 c = lm2_camera2_default_f64(vp);  // pos = (400, 300), zoom = 1
  lm2_r2_f64 bounds = lm2_camera2_get_world_bounds_f64(c);

  EXPECT_NEAR(bounds.min.x, 0.0, EPSILON_F64);
  EXPECT_NEAR(bounds.min.y, 0.0, EPSILON_F64);
  EXPECT_NEAR(bounds.max.x, 800.0, EPSILON_F64);
  EXPECT_NEAR(bounds.max.y, 600.0, EPSILON_F64);
}

TEST_F(Camera2Test, WorldBounds_Zoom2_F64) {
  lm2_r2_f64 vp = lm2_r2_from_min_max_f64({0.0, 0.0}, {800.0, 600.0});
  lm2_camera2_f64 c = lm2_camera2_default_f64(vp);
  c = lm2_camera2_set_zoom_f64(c, 2.0);
  lm2_r2_f64 bounds = lm2_camera2_get_world_bounds_f64(c);

  // Half size at zoom 2: 200 x 150 around center (400, 300)
  EXPECT_NEAR(bounds.min.x, 200.0, EPSILON_F64);
  EXPECT_NEAR(bounds.min.y, 150.0, EPSILON_F64);
  EXPECT_NEAR(bounds.max.x, 600.0, EPSILON_F64);
  EXPECT_NEAR(bounds.max.y, 450.0, EPSILON_F64);
}

// =============================================================================
// World/Screen transforms - f64
// =============================================================================

TEST_F(Camera2Test, WorldToScreen_Identity_F64) {
  // Camera centered at viewport center, no rotation, zoom 1
  // world_to_screen(position) should return viewport center
  lm2_r2_f64 vp = lm2_r2_from_min_max_f64({0.0, 0.0}, {800.0, 600.0});
  lm2_camera2_f64 c = lm2_camera2_default_f64(vp);
  lm2_v2_f64 screen = lm2_camera2_world_to_screen_f64(c, c.position);

  EXPECT_NEAR(screen.x, 400.0, EPSILON_F64);
  EXPECT_NEAR(screen.y, 300.0, EPSILON_F64);
}

TEST_F(Camera2Test, ScreenToWorld_RoundTrip_F64) {
  lm2_r2_f64 vp = lm2_r2_from_min_max_f64({0.0, 0.0}, {800.0, 600.0});
  lm2_camera2_f64 c = lm2_camera2_default_f64(vp);
  c.position.x = 50.0;
  c.position.y = -30.0;

  lm2_v2_f64 world_in = {123.0, -456.0};
  lm2_v2_f64 screen = lm2_camera2_world_to_screen_f64(c, world_in);
  lm2_v2_f64 world_out = lm2_camera2_screen_to_world_f64(c, screen);

  EXPECT_NEAR(world_out.x, world_in.x, EPSILON_F64);
  EXPECT_NEAR(world_out.y, world_in.y, EPSILON_F64);
}

TEST_F(Camera2Test, ScreenToWorld_RoundTrip_WithRotation_F64) {
  lm2_r2_f64 vp = lm2_r2_from_min_max_f64({0.0, 0.0}, {800.0, 600.0});
  lm2_camera2_f64 c = lm2_camera2_default_f64(vp);
  c.rotation = 0.785398;  // ~45 degrees
  c.zoom = 1.5;

  lm2_v2_f64 world_in = {300.0, 100.0};
  lm2_v2_f64 screen = lm2_camera2_world_to_screen_f64(c, world_in);
  lm2_v2_f64 world_out = lm2_camera2_screen_to_world_f64(c, screen);

  EXPECT_NEAR(world_out.x, world_in.x, 1e-6);
  EXPECT_NEAR(world_out.y, world_in.y, 1e-6);
}

// =============================================================================
// Camera manipulation - f64
// =============================================================================

TEST_F(Camera2Test, Move_F64) {
  lm2_r2_f64 vp = lm2_r2_from_min_max_f64({0.0, 0.0}, {800.0, 600.0});
  lm2_camera2_f64 c = lm2_camera2_default_f64(vp);
  lm2_v2_f64 delta = {10.0, -5.0};
  c = lm2_camera2_move_f64(c, delta);

  EXPECT_DOUBLE_EQ(c.position.x, 410.0);
  EXPECT_DOUBLE_EQ(c.position.y, 295.0);
}

TEST_F(Camera2Test, Rotate_F64) {
  lm2_r2_f64 vp = lm2_r2_from_min_max_f64({0.0, 0.0}, {800.0, 600.0});
  lm2_camera2_f64 c = lm2_camera2_default_f64(vp);
  c = lm2_camera2_rotate_f64(c, 1.0);

  EXPECT_DOUBLE_EQ(c.rotation, 1.0);
}

TEST_F(Camera2Test, SetZoom_F64) {
  lm2_r2_f64 vp = lm2_r2_from_min_max_f64({0.0, 0.0}, {800.0, 600.0});
  lm2_camera2_f64 c = lm2_camera2_default_f64(vp);
  c = lm2_camera2_set_zoom_f64(c, 3.5);

  EXPECT_DOUBLE_EQ(c.zoom, 3.5);
}

TEST_F(Camera2Test, ZoomAt_PreservesAnchorPoint_F64) {
  // Zooming at the viewport center should not move the world point under cursor
  lm2_r2_f64 vp = lm2_r2_from_min_max_f64({0.0, 0.0}, {800.0, 600.0});
  lm2_camera2_f64 c = lm2_camera2_default_f64(vp);
  lm2_v2_f64 anchor = {400.0, 300.0};  // viewport center

  lm2_v2_f64 world_before = lm2_camera2_screen_to_world_f64(c, anchor);
  c = lm2_camera2_zoom_at_f64(c, 2.0, anchor);
  lm2_v2_f64 world_after = lm2_camera2_screen_to_world_f64(c, anchor);

  EXPECT_NEAR(world_before.x, world_after.x, EPSILON_F64);
  EXPECT_NEAR(world_before.y, world_after.y, EPSILON_F64);
}

// =============================================================================
// View matrix - f64
// =============================================================================

TEST_F(Camera2Test, GetView_NotZero_F64) {
  lm2_r2_f64 vp = lm2_r2_from_min_max_f64({0.0, 0.0}, {800.0, 600.0});
  lm2_camera2_f64 c = lm2_camera2_default_f64(vp);
  lm2_m3x2_f64 view = lm2_camera2_get_view_f64(c);

  // Identity-like: scale should be 1 on diagonal, translation at viewport center
  EXPECT_NEAR(view.m00, 1.0, EPSILON_F64);
  EXPECT_NEAR(view.m11, 1.0, EPSILON_F64);
}

TEST_F(Camera2Test, InvView_IsViewInverse_F64) {
  lm2_r2_f64 vp = lm2_r2_from_min_max_f64({0.0, 0.0}, {800.0, 600.0});
  lm2_camera2_f64 c = lm2_camera2_default_f64(vp);
  c.zoom = 1.5;
  c.rotation = 0.3;
  lm2_m3x2_f64 view = lm2_camera2_get_view_f64(c);
  lm2_m3x2_f64 inv = lm2_camera2_get_inv_view_f64(c);
  lm2_m3x2_f64 prod = lm2_m3x2_multiply_f64(view, inv);

  // Product should be identity
  EXPECT_NEAR(prod.m00, 1.0, 1e-6);
  EXPECT_NEAR(prod.m11, 1.0, 1e-6);
  EXPECT_NEAR(prod.m01, 0.0, 1e-6);
  EXPECT_NEAR(prod.m10, 0.0, 1e-6);
  EXPECT_NEAR(prod.m02, 0.0, 1e-6);
  EXPECT_NEAR(prod.m12, 0.0, 1e-6);
}

// =============================================================================
// Construction - f32
// =============================================================================

TEST_F(Camera2Test, Make_F32) {
  lm2_v2_f32 pos = {10.0f, 20.0f};
  lm2_r2_f32 vp = lm2_r2_from_min_max_f32({0.0f, 0.0f}, {800.0f, 600.0f});
  lm2_camera2_f32 c = lm2_camera2_make_f32(pos, 0.5f, 2.0f, vp);

  EXPECT_FLOAT_EQ(c.position.x, 10.0f);
  EXPECT_FLOAT_EQ(c.rotation, 0.5f);
  EXPECT_FLOAT_EQ(c.zoom, 2.0f);
}

TEST_F(Camera2Test, ScreenToWorld_RoundTrip_F32) {
  lm2_r2_f32 vp = lm2_r2_from_min_max_f32({0.0f, 0.0f}, {800.0f, 600.0f});
  lm2_camera2_f32 c = lm2_camera2_default_f32(vp);
  c.position.x = 50.0f;
  c.position.y = -30.0f;

  lm2_v2_f32 world_in = {123.0f, -456.0f};
  lm2_v2_f32 screen = lm2_camera2_world_to_screen_f32(c, world_in);
  lm2_v2_f32 world_out = lm2_camera2_screen_to_world_f32(c, screen);

  EXPECT_NEAR(world_out.x, world_in.x, EPSILON_F32);
  EXPECT_NEAR(world_out.y, world_in.y, EPSILON_F32);
}

TEST_F(Camera2Test, ZoomAt_PreservesAnchorPoint_F32) {
  lm2_r2_f32 vp = lm2_r2_from_min_max_f32({0.0f, 0.0f}, {800.0f, 600.0f});
  lm2_camera2_f32 c = lm2_camera2_default_f32(vp);
  lm2_v2_f32 anchor = {400.0f, 300.0f};

  lm2_v2_f32 world_before = lm2_camera2_screen_to_world_f32(c, anchor);
  c = lm2_camera2_zoom_at_f32(c, 2.0f, anchor);
  lm2_v2_f32 world_after = lm2_camera2_screen_to_world_f32(c, anchor);

  EXPECT_NEAR(world_before.x, world_after.x, EPSILON_F32);
  EXPECT_NEAR(world_before.y, world_after.y, EPSILON_F32);
}
