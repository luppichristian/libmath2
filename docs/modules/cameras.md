# Cameras

## Overview

2D and 3D camera types that encapsulate position, orientation, and projection parameters. Functions are provided for constructing cameras, computing view and projection matrices, transforming points between spaces, and manipulating the camera through movement, rotation, zoom, and orbit.

## Why Use This?

Camera types save you from manually managing view and projection matrices. They provide high-level helpers like `world_to_screen`, `screen_to_world`, and `world_to_ndc` so you can focus on gameplay and rendering logic rather than matrix math.

---

## Camera 2D

**Header:** `lm2/camera/lm2_camera2.h`

A 2D orthographic camera defined by a world-space position, rotation in radians, uniform zoom, and a screen viewport rectangle. All manipulation functions return a modified camera; assign the result to retain the change.

### Coordinate conventions

`viewport.min` and `viewport.max` are absolute screen pixel coordinates, normally the top-left and bottom-right corners. The view matrix maps the camera's world-space `position` to the viewport center. It translates by `-position`, rotates by `-rotation`, scales by `zoom`, then translates to that center. Screen coordinates are not relative to `viewport.min`.

There is no Y-axis flip: at zero rotation, increasing world X or Y increases screen X or Y. Rotation is measured in the numeric XY plane, so its apparent direction depends on whether the display's Y axis points up or down. World units are chosen by the caller; at zoom 1 one world unit maps to one screen pixel.

Use positive, nonzero zoom and zoom factors for ordinary zooming. Constructors and setters do not clamp or validate them. The inverse view, screen-to-world conversion, and world bounds require a nonzero zoom. Anchored zoom requires both the original and resulting zoom to be nonzero. A singular inverse can assert.

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
| `lm2_camera2_default_f32(viewport)` | Position at viewport center, no rotation, zoom 1; the view transform is identity |

#### View Matrix

| Function | Description |
|----------|-------------|
| `lm2_camera2_get_view_f32(camera)` | 3x2 view matrix (world → absolute screen pixels) |
| `lm2_camera2_get_inv_view_f32(camera)` | 3x2 inverse view matrix (absolute screen pixels → world) |

#### Space Transforms

| Function | Description |
|----------|-------------|
| `lm2_camera2_world_to_screen_f32(camera, world_pos)` | World-space point → screen pixels |
| `lm2_camera2_screen_to_world_f32(camera, screen_pos)` | Screen pixels → world-space point |

#### Camera Manipulation

| Function | Description |
|----------|-------------|
| `lm2_camera2_move_f32(camera, delta)` | Translate camera by world-space delta |
| `lm2_camera2_zoom_at_f32(camera, zoom_factor, screen_anchor)` | Multiply zoom and adjust position to keep the world point under the absolute screen anchor fixed |
| `lm2_camera2_set_zoom_f32(camera, zoom)` | Set zoom to an absolute value |
| `lm2_camera2_rotate_f32(camera, delta_radians)` | Rotate by an angle delta |

#### Viewport Helpers

| Function | Description |
|----------|-------------|
| `lm2_camera2_get_viewport_size_f32(camera)` | Viewport size in pixels |
| `lm2_camera2_get_viewport_center_f32(camera)` | Viewport center in pixels |
| `lm2_camera2_get_world_bounds_f32(camera)` | World-space AABB enclosing the four transformed viewport corners; conservative for a rotated camera |

### Example

```c
#include <lm2/camera/lm2_camera2.h>

lm2_r2_f32 viewport = lm2_r2_from_min_max_f32(
    lm2_v2_zero_f32(),
    lm2_v2_make_f32(1280.0f, 720.0f)
);

lm2_camera2_f32 cam = lm2_camera2_default_f32(viewport);

// Move the camera by a world-space offset
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

A 3D camera supporting perspective and orthographic projection, defined by a world-space position, look-at target, up hint, and projection parameters. All manipulation functions return a modified camera; assign the result to retain the change.

### Coordinate and projection conventions

The camera is right-handed. Its view space has +X right, +Y up, and -Z forward. `position` and `target` are world-space points, and `up` is a world-space hint. The derived directions are `forward = normalize(target - position)`, `right = normalize(cross(forward, up))`, and `up = cross(right, forward)`. The stored up hint need not be perpendicular to forward, but it must not be parallel; position and target must differ. The view matrix requires both `length(target - position)` and `length(cross(forward, up))` to exceed `1e-10` for f64 or `1e-6` for f32; smaller values can assert. The direction getters normalize zero to zero, so they can return zero for a degenerate camera even when view construction asserts.

For perspective, `fov_y` is the vertical field of view in radians and `aspect` is viewport width divided by height. For orthographic projection, `ortho_size` is the half-height and `ortho_size * aspect` is the half-width of a frustum centered on the view axis. Near and far are distances in front of the eye. Use `0 < near_plane < far_plane`, positive aspect and orthographic size, and `0 < fov_y < pi` for perspective. Constructors and setters store the supplied values without clamping or validation; invalid inputs can cause assertions or singular matrices. Projection enum values other than `LM2_CAMERA3_PERSPECTIVE` select the orthographic path.

The combined matrix is `projection * view`. After the homogeneous divide, the visible NDC volume is `[-1, 1]` on all three axes: the near and far planes map to Z = -1 and +1, respectively. These are OpenGL-style depth coordinates. `world_to_ndc` and `ndc_to_world` divide by homogeneous W without checking it, so the caller must ensure it is nonzero; the inverse conversion also requires an invertible view-projection matrix. They do not perform clipping or visibility testing.

### Orbit and quaternion conventions

Orbit uses the world +Y axis as its polar axis, regardless of the camera's `up` hint. It preserves target and position-to-target distance; positive yaw moves a +Z offset toward +X, while positive pitch moves it toward -Y. The polar angle is clamped to `[0.01, pi - 0.01]` radians, so a near-pole camera can move even with zero pitch. A zero-radius orbit remains degenerate.

Quaternion constructors and setters take a unit camera-to-world orientation relative to the default forward `(0, 0, -1)` and up `(0, 1, 0)`. They rotate those axes, set `target = position + forward`, and replace `up`, so the target distance becomes one. `get_orientation` instead extracts the world-to-camera rotation from the view matrix. Conjugate its result to recover the orientation accepted by `set_orientation`. `rotate_local` composes the camera-to-world orientation with a local rotation on the right and normalizes it; it also resets target distance to one.

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
| `lm2_camera3_get_projection_f32(camera)` | 4x4 view → homogeneous clip-space projection matrix |
| `lm2_camera3_get_view_projection_f32(camera)` | `projection * view` (world → homogeneous clip space) |
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
| `lm2_camera3_orbit_f32(camera, yaw, pitch)` | Orbit around target in radians using world +Y as polar axis |
| `lm2_camera3_set_aspect_f32(camera, aspect)` | Update the aspect ratio |
| `lm2_camera3_set_fov_y_f32(camera, fov_y)` | Update the vertical field of view |

#### Quaternion Orientation

| Function | Description |
|----------|-------------|
| `lm2_camera3_get_orientation_f32(camera)` | Extract world-to-camera rotation from the view matrix |
| `lm2_camera3_set_orientation_f32(camera, orientation)` | Set camera-to-world orientation; updates target and up |
| `lm2_camera3_rotate_local_f32(camera, rotation)` | Apply a local-space quaternion rotation |

#### Space Transforms

| Function | Description |
|----------|-------------|
| `lm2_camera3_world_to_ndc_f32(camera, world_pos)` | World-space point → NDC after homogeneous divide (no visibility test) |
| `lm2_camera3_ndc_to_world_f32(camera, ndc_pos)` | NDC point → world-space |

### Example

```c
#include <lm2/camera/lm2_camera3.h>
#include <lm2/lm2_constants.h>

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

// Convert a world point to NDC (test clip W and bounds separately for visibility)
lm2_v3_f32 ndc = lm2_camera3_world_to_ndc_f32(cam, lm2_v3_make_f32(1.0f, 0.0f, 0.0f));
```
