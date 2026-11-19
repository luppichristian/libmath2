# 3D Geometry

The 3D geometry modules provide spheres, axis-aligned boxes, capsules, line
segments, planes and triangles, plus ray and mesh conversion helpers. Both
`f32` and `f64` variants are available. Coordinates supplied to a query must
share a coordinate space and scale: these functions do not transform objects
between model, world, view or screen space. Normals and returned points use
the same axes as the inputs.

## Spheres and capsules

`lm2_sphere_f32` and `lm2_sphere_f64` store a center and radius. Construction
asserts a nonnegative radius. Point containment and sphere overlap include the
boundary, so tangency counts. `lm2_sphere_contains_sphere(a, b)` tests whether
**a contains b**. Translation moves the center; scaling changes only the radius,
not the center. A negative scale creates a negative radius, so use a
nonnegative factor for a valid sphere.

A capsule is the set of points within its radius of the finite segment from
`start` to `end`. Its length is the segment length; total length includes both
rounded ends (`length + 2 * radius`). `lm2_capsule3_from_center` normalizes the
direction and places endpoints at `center +/- direction * half_length`; a zero
direction makes the endpoints coincide. Constructors require nonnegative radius
and half-length. Containment and overlap include tangency. The second capsule
passed to `lm2_capsules3_overlap(a, b)` must have distinct endpoints: the
segment-distance helper divides by its squared axis length. Translation moves
both endpoints; `scale_radius` changes only the radius and requires a
nonnegative scale.

## Axis-aligned boxes

`lm2_aabb3_*` is an alias for `lm2_r3_*`, with `min` and `max` coordinates.
Use ordered bounds on each axis. The `center_size` constructor accepts full
size, while `center_extents` accepts half-size; `position_size` uses the minimum
corner and full size. The unit box spans `(0, 0, 0)` to `(1, 1, 1)`.

Corner enumeration selects min or max independently for x, y and z; the
`get_corners` array follows enum order. Face names are fixed to the input axes:
front +Z, back -Z, left -X, right +X, top +Y, and bottom -Y. They do not
follow a camera. Face normals point outward along these axes.

`lm2_aabb3_scale` multiplies both corners componentwise about the coordinate
origin, not the box center. Negative components can reverse min and max; the
function does not reorder them. `expand` subtracts its amount from min and
adds it to max; negative amounts shrink the box. Range operations and their
other conventions are described in [Ranges](ranges.md).

## Planes and edges

`lm2_plane3_*` represents `dot(normal, point) = distance`. Its normal is a unit
vector and distance is signed along that normal from the coordinate origin.
`make` normalizes the supplied normal but stores the given distance unchanged;
`from_point_normal` computes distance from the point after normalizing. A zero
normal, or three collinear points, does not define a geometric plane. Three-point
construction and triangle normals use `cross(p1 - p0, p2 - p0)`. The standard
XY, XZ, and YZ planes have +Z, +Y and +X normals respectively.

Signed distance and side are `dot(normal, point) - distance`: positive is on
the normal side. Projection and closest-point operations assume a unit normal.
Containment checks absolute signed distance `<= epsilon`, with nonnegative
epsilon. Flip negates normal and distance; translation adds `dot(normal,
offset)` to distance.

An edge is a finite segment from `start` to `end`. `from_ray` uses the ray
origin and `origin + direction * t_max` as endpoints. `from_plane` projects
and normalizes the direction but does **not** project the center: supply a center already on
the plane. A direction parallel to the plane normal gives a zero-length edge.
Point equality compares each coordinate difference strictly `< epsilon`, so
zero epsilon does not even match identical finite points. Edge equality accepts
either endpoint order. The point-to-edge squared distance clamps to the segment
and treats coincident endpoints as a point. The edge-to-edge squared distance
helper requires a nonzero second segment: its parallel branch divides by that
segment's squared length. Segment intersection uses scale-dependent absolute
epsilon checks; its collinear branch returns false for a near-degenerate first
segment.

## Triangles and mesh conversion

`lm2_triangle3_*` is an array of three ordered vertices. Its normal is the
normalized `cross(v1 - v0, v2 - v0)` and is zero for a degenerate triangle.
`contains_point` first requires the point to lie within `epsilon` of the
triangle plane, then tests barycentric coordinates with edges included. It
requires a nondegenerate triangle; epsilon does not expand its barycentric
boundaries. Triangle overlap also requires nondegenerate inputs and may assert
for degenerate ones. Its epsilon serves both as a spatial tolerance and as a
dimensionless threshold for plane-normal angles and edge/plane parallelism. Shared-edge
queries compare endpoints in either order and return the first matching edge of
the first triangle; inspect `exists` before reading `edge`. Classification
checks degenerate, right, equilateral, isosceles, then scalene in that priority.
Epsilon is an absolute threshold but has different units: area for degeneracy, squared-length difference for the right
angle test, and length difference for side equality. Degenerate, right,
isosceles, and equilateral comparisons use strict `< epsilon`; scalene uses
`>= epsilon`. At epsilon zero, even zero area is not classified degenerate
and equal side lengths do not match the equality predicates.

`lm2_triangle3_geometry.h` converts triangle lists to flat vertex arrays and
indexed meshes and back. Flat arrays store three vertices per triangle in
order. Indexed conversion compares each coordinate difference to `epsilon`
using `<=` with nonnegative epsilon, reuses the first matching vertex, and
preserves traversal order in the index array. With `epsilon = 0`, matching is
exact for finite values. The mesh-size query returns actual deduplicated size for at most 1024 input vertices
and a worst-case size for larger lists. Allocate at least the reported vertex
count using the same input and epsilon **and** at least `triangle_count`
vertices, because the conversion asserts that minimum; allocate
`3 * triangle_count` indices. The conversion does not return the number of unique vertices. Keep input, vertex and index
buffers disjoint. A new vertex is written before its capacity assertion, so an
undersized buffer is unsafe. Counts and indices must fit in
`uint32_t`; pointers must be non-NULL even for empty input. Reverse conversions
require counts divisible by three, adequate output buffers, and indices less
than `vertex_count`.

## Raycasting

A ray is `origin + t * direction` over `0 <= t <= t_max`. `lm2_ray3_make`
stores the direction and maximum parameter unchanged; `t` measures distance
only when direction is unit length. `lm2_ray3_from_points` normalizes the
segment direction and sets `t_max` to its length; coincident points produce a
zero direction and zero maximum. `point_at` does not clamp its parameter.

A miss returns `hit = false` with the other fields zero. A hit returns the ray
parameter, a point in the input coordinate space, and a normal; the normal can
be zero for degenerate cases. Results depend on the primitive:

- Sphere and capsule casts return the first forward surface, including the exit
  when starting strictly inside. A stationary ray inside returns its origin,
  `t = 0`, and a zero normal. The sphere cast uses the absolute radius; a
  capsule requires a nonnegative radius; one with coincident endpoints uses the
  sphere cast. At very large distances, rounding of `t` can make `point_at(ray, t)` differ from the
  returned surface point.
- A box cast starting inside or on its surface returns the origin at `t = 0`.
  On a face the normal is the first matching outward face in x, y, z order;
  inside, it is a fallback axis based on the largest absolute displacement
  from the box center (ties favor z, then y).
- Triangle casts test both sides and return the winding normal, without
  orienting it toward the ray. Plane casts normalize and return the supplied
  plane normal without flipping it. The triangle cast rejects an absolute
  intersection determinant below `LM2_RAYCAST3_EPSILON_F32` or `_F64`; this
  threshold depends on triangle and direction scale. The plane cast misses if
  the absolute dot product of its normalized normal and ray direction is at
  most that epsilon, including a zero normal. Triangle edges and vertices are
  included.
- Edge casts find closest points on the finite ray interval and segment, then
  report a hit if their distance is at most the nonnegative tolerance. The
  result point is on the ray, and its normal points from the segment to that
  point. At zero separation, the normal is the normalized cross product of
  ray direction and edge direction, or zero if that cross product is zero.

`lm2_shape3_*` is a non-owning tagged pointer to a sphere, capsule, AABB,
triangle or edge. The object must outlive the wrapper and match its type and
precision. Generic raycasts require non-NULL data and use the default raycast
epsilon as the edge tolerance; an unknown tag returns a miss.

## Example

```c
#include <lm2/geometry3d/lm2_raycast3.h>

lm2_ray3_f32 ray = lm2_ray3_from_points_f32(
    lm2_v3_make_f32(0.0f, 0.0f, -5.0f),
    lm2_v3_make_f32(0.0f, 0.0f, 5.0f));
lm2_rayhit3_f32 hit = lm2_raycast_sphere_f32(
    ray, lm2_v3_make_f32(0.0f, 0.0f, 0.0f), 1.0f);
// hit.t == 4, hit.point == (0, 0, -1), hit.normal == (0, 0, -1)
```
