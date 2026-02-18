---
layout: default
title: Cameras
---

# Cameras

## Overview

2D and 3D camera types that encapsulate position, orientation, and projection parameters. Functions are provided for constructing cameras, computing view and projection matrices, transforming points between spaces, and manipulating the camera through movement, rotation, zoom, and orbit.

## Why Use This?

Camera types save you from manually managing view and projection matrices. They provide high-level helpers like `world_to_screen`, `screen_to_world`, and `world_to_ndc` so you can focus on gameplay and rendering logic rather than matrix math.

---

## Camera 2D

**Header:** `lm2/camera/lm2_camera2.h`

A 2D orthographic camera defined by a world-space position, a counter-clockwise rotation, a uniform zoom factor, and a screen viewport rectangle.

### Types

| Type | Scalar | Description |
|------|--------|-------------|
| `lm2_camera2_f64` | `double` | 2D camera (double precision) |
| `lm2_camera2_f32` | `float` | 2D camera (float precision) |

### Structure

```c
typedef struct lm2_camera2_f32 {
    lm2_v2_f32 position;  // World-space center of the camera
    float      rotation;  // Counter-clockwise rotation in radians
    float      zoom;      // Uniform zoom factor (1.0 = no zoom)
    lm2_r2_f32 viewport;  // Screen viewport rectangle in pixels
} lm2_camera2_f32;
```

### Functions

All functions shown with `_f32` suffix. Also available with `_f64`.

#### Construction

| Function | Description |
|----------|-------------|
| `lm2_camera2_make_f32(position, rotation, zoom, viewport)` | Construct from all fields |
| `lm2_camera2_default_f32(viewport)` | Default camera: origin, no rotation, zoom 1 |

#### View Matrix

| Function | Description |
|----------|-------------|
| `lm2_camera2_get_view_f32(camera)` | 3x2 view matrix (world → camera space) |
| `lm2_camera2_get_inv_view_f32(camera)` | 3x2 inverse view matrix (camera → world space) |

#### Space Transforms

| Function | Description |
|----------|-------------|
| `lm2_camera2_world_to_screen_f32(camera, world_pos)` | World-space point → screen pixels |
| `lm2_camera2_screen_to_world_f32(camera, screen_pos)` | Screen pixels → world-space point |

#### Camera Manipulation

| Function | Description |
|----------|-------------|
| `lm2_camera2_move_f32(camera, delta)` | Translate camera by world-space delta |
| `lm2_camera2_zoom_at_f32(camera, zoom_factor, screen_anchor)` | Zoom in/out keeping a screen point fixed |
| `lm2_camera2_set_zoom_f32(camera, zoom)` | Set zoom to an absolute value |
| `lm2_camera2_rotate_f32(camera, delta_radians)` | Rotate by an angle delta |

#### Viewport Helpers

| Function | Description |
|----------|-------------|
| `lm2_camera2_get_viewport_size_f32(camera)` | Viewport size in pixels |
| `lm2_camera2_get_viewport_center_f32(camera)` | Viewport center in pixels |
| `lm2_camera2_get_world_bounds_f32(camera)` | Visible world-space AABB |

### Example

```c
#include <lm2/camera/lm2_camera2.h>

lm2_r2_f32 viewport = lm2_r2_from_min_max_f32(
    lm2_v2_zero_f32(),
    lm2_v2_make_f32(1280.0f, 720.0f)
);

lm2_camera2_f32 cam = lm2_camera2_default_f32(viewport);

// Pan the camera to center on a point
cam = lm2_camera2_move_f32(cam, lm2_v2_make_f32(100.0f, 50.0f));

// Zoom in towards the mouse cursor
cam = lm2_camera2_zoom_at_f32(cam, 1.1f, lm2_v2_make_f32(640.0f, 360.0f));

// Convert a mouse click to world coordinates
lm2_v2_f32 world_pos = lm2_camera2_screen_to_world_f32(cam, lm2_v2_make_f32(100.0f, 200.0f));

// Get the view matrix for rendering
lm2_m3x2_f32 view = lm2_camera2_get_view_f32(cam);
```

---

## Camera 3D

**Header:** `lm2/camera/lm2_camera3.h`

A 3D camera supporting both perspective and orthographic projection, defined by a world-space position, a look-at target, an up hint, and projection parameters. Uses a right-handed coordinate system.

### Types

| Type | Scalar | Description |
|------|--------|-------------|
| `lm2_camera3_f64` | `double` | 3D camera (double precision) |
| `lm2_camera3_f32` | `float` | 3D camera (float precision) |

### Projection Enum

```c
typedef enum lm2_camera3_projection {
    LM2_CAMERA3_PERSPECTIVE,
    LM2_CAMERA3_ORTHOGRAPHIC,
} lm2_camera3_projection;
```

### Structure

```c
typedef struct lm2_camera3_f32 {
    lm2_v3_f32              position;    // World-space eye position
    lm2_v3_f32              target;      // World-space look-at target
    lm2_v3_f32              up;          // World up hint (usually (0,1,0))
    float                   fov_y;       // Vertical FOV in radians (perspective)
    float                   aspect;      // Width / height ratio
    float                   near_plane;  // Near clipping distance
    float                   far_plane;   // Far clipping distance
    float                   ortho_size;  // Half-height (orthographic)
    lm2_camera3_projection  projection;  // Projection mode
} lm2_camera3_f32;
```

### Functions

All functions shown with `_f32` suffix. Also available with `_f64`.

#### Construction

| Function | Description |
|----------|-------------|
| `lm2_camera3_perspective_f32(position, target, up, fov_y, aspect, near_plane, far_plane)` | Create perspective camera |
| `lm2_camera3_orthographic_f32(position, target, up, ortho_size, aspect, near_plane, far_plane)` | Create orthographic camera |
| `lm2_camera3_from_quat_f32(position, orientation, fov_y, aspect, near_plane, far_plane)` | Create perspective camera from quaternion orientation |

#### View / Projection Matrices

| Function | Description |
|----------|-------------|
| `lm2_camera3_get_view_f32(camera)` | 4x4 view matrix (world → camera space) |
| `lm2_camera3_get_projection_f32(camera)` | 4x4 projection matrix (perspective or ortho) |
| `lm2_camera3_get_view_projection_f32(camera)` | Combined view-projection matrix |
| `lm2_camera3_get_inv_view_f32(camera)` | Inverse view matrix (camera → world space) |

#### Derived Direction Vectors

| Function | Description |
|----------|-------------|
| `lm2_camera3_get_forward_f32(camera)` | Normalized forward direction vector |
| `lm2_camera3_get_right_f32(camera)` | Normalized right direction vector |
| `lm2_camera3_get_up_f32(camera)` | Normalized up direction vector |

#### Camera Manipulation

| Function | Description |
|----------|-------------|
| `lm2_camera3_move_f32(camera, delta)` | Translate position and target by world-space delta |
| `lm2_camera3_look_at_f32(camera, target)` | Change the look-at target |
| `lm2_camera3_orbit_f32(camera, yaw, pitch)` | Orbit around the target by yaw and pitch angles |
| `lm2_camera3_set_aspect_f32(camera, aspect)` | Update the aspect ratio |
| `lm2_camera3_set_fov_y_f32(camera, fov_y)` | Update the vertical field of view |

#### Quaternion Orientation

| Function | Description |
|----------|-------------|
| `lm2_camera3_get_orientation_f32(camera)` | Extract camera orientation as quaternion |
| `lm2_camera3_set_orientation_f32(camera, orientation)` | Set orientation from quaternion (updates target) |
| `lm2_camera3_rotate_local_f32(camera, rotation)` | Apply a local-space quaternion rotation |

#### Space Transforms

| Function | Description |
|----------|-------------|
| `lm2_camera3_world_to_ndc_f32(camera, world_pos)` | World-space point → NDC (-1 to 1) |
| `lm2_camera3_ndc_to_world_f32(camera, ndc_pos)` | NDC point → world-space |

### Example

```c
#include <lm2/camera/lm2_camera3.h>

// Create a perspective camera looking at the origin
lm2_camera3_f32 cam = lm2_camera3_perspective_f32(
    lm2_v3_make_f32(0.0f, 3.0f, 8.0f),   // position
    lm2_v3_zero_f32(),                     // target (origin)
    lm2_v3_make_f32(0.0f, 1.0f, 0.0f),   // up
    LM2_HPI_F32 / 2.0f,                   // fov_y (~45 degrees)
    16.0f / 9.0f,                          // aspect
    0.1f,                                  // near_plane
    1000.0f                                // far_plane
);

// Get matrices for rendering
lm2_m4x4_f32 view = lm2_camera3_get_view_f32(cam);
lm2_m4x4_f32 proj = lm2_camera3_get_projection_f32(cam);
lm2_m4x4_f32 vp   = lm2_camera3_get_view_projection_f32(cam);

// Orbit the camera around the target
cam = lm2_camera3_orbit_f32(cam, 0.01f, 0.0f);  // rotate 0.01 rad around Y

// Convert a world point to NDC for visibility testing
lm2_v3_f32 ndc = lm2_camera3_world_to_ndc_f32(cam, lm2_v3_make_f32(1.0f, 0.0f, 0.0f));
```
