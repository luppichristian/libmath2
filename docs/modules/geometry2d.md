# 2D Geometry

## Overview

2D geometric primitives including circles, axis-aligned bounding boxes, capsules, edges, planes, polygons, and triangles. Also includes raycasting and collision manifold types for 2D collision detection.

## Coordinates and conventions

All points, vectors, and shapes in a query must use the same caller-chosen 2D
coordinate system. No shape carries a transform. Results such as contact and
hit points are in that same space. Angles are in radians; positive rotation is
counterclockwise in Cartesian coordinates (+X right, +Y up). The winding
names refer to this Cartesian orientation; a display with +Y down appears
visually reversed.

Radii are nonnegative. Circle and capsule constructors assert this condition,
as do their radius-scaling functions. Polygon, triangle and segment predicates
use floating-point arithmetic rather than exact geometric predicates, so
nearly collinear or extreme inputs can be sensitive to rounding or overflow.

## Shapes

### Circle

A circle defined by center point and radius.

**Types:** `lm2_circle_f64`, `lm2_circle_f32`

**Structure:**
```c
typedef struct lm2_circle_f32 {
    lm2_v2_f32 center;
    float radius;
} lm2_circle_f32;
```

**Functions:**

| Function | Description |
|----------|-------------|
| `lm2_circle_make_f32(center, radius)` | Create from center and radius |
| `lm2_circle_make_coords_f32(x, y, radius)` | Create from coordinates |
| `lm2_circle_unit_f32()` | Unit circle at origin |
| `lm2_circle_area_f32(c)` | Area |
| `lm2_circle_circumference_f32(c)` | Circumference |
| `lm2_circle_diameter_f32(c)` | Diameter |
| `lm2_circle_contains_point_f32(c, point)` | Includes the boundary |
| `lm2_circles_overlap_f32(a, b)` | Includes external tangency |
| `lm2_circle_contains_circle_f32(a, b)` | True when `a` contains `b`, including internal tangency |
| `lm2_circle_translate_f32(c, offset)` | Translate circle |
| `lm2_circle_scale_f32(c, scale)` | Scale radius about the unchanged center; scale must be nonnegative |

### AABB2

A 2D axis-aligned box is represented by a range with componentwise `min <= max`. Axes are those of the input coordinate system: left/right mean min/max X
and bottom/top mean min/max Y. Point containment, rectangle containment, and
rectangle overlap include their boundaries.

`get_dim` is `max - min`; `get_closest_point` clamps each coordinate to the
box. The floating-point distance to a point is Euclidean and zero for an
inside point; `closest_distance_from_edges` is also zero for overlapping boxes.
The header declares integer versions of both distance functions, but they do
not have definitions; use the floating-point versions. Other AABB operations
support the integer variants listed in `lm2_aabb2.h`.

`scale_from_center`, `scale_from_min`, and `scale_from_max` scale the box
componentwise about the named anchor. Shrink and inflate move each side by the
amount, changing each dimension by twice that amount; they do not prevent
inverted bounds. A cut returns the selected strip and updates the passed box
to the remainder. Amount is not clamped to box size; an invalid cut enum
returns a zero range. Alignment preserves the subrectangle size and positions
it at the start, center, or end of each axis. Integer results are subject to
integer division and representability limits, including intermediate values.

### Capsule2

A capsule consists of all points within its radius of the segment from `start`
to `end`. Point containment and capsule overlap include touching. The
`from_center` constructor normalizes its direction and places endpoints
at `center ± direction * half_length`; a zero direction gives coincident
endpoints at the center. The half-length describes the segment, not the rounded
ends. `total_length` adds two radii to segment length.
`scale_radius` leaves the endpoints unchanged. See `lm2_capsule2.h`.

### Edge2

An edge is the closed line segment from `start` to `end`. Segment intersection
includes endpoints and collinear overlap. Floating-point intersection expects
finite coordinates and can be affected by rounding; the integer segment
intersection functions use exact integer orientation. Distance functions
measure to the finite segments. Point and edge equality compare each coordinate
with a strict `< epsilon`, so epsilon zero does not match even identical points. `lm2_edge2_from_plane` uses the supplied center as-is; it
must lie on the plane for the resulting edge to lie on that line. See
`lm2_edge2.h`.

### Plane2

A 2D plane is an infinite line `dot(normal, point) = distance`, with a unit
normal. Signed point distance is `dot(normal, point) - distance`, positive on
the normal side. `lm2_plane2_make(normal, distance)` divides **both** arguments
by the normal length, preserving the input equation. `from_point_normal`
instead calculates the distance from the point after normalizing. Normals must
be nonzero, and the two points passed to `from_points` must be distinct; its
normal is the counterclockwise perpendicular to `p1 - p0`.

Translation adds `dot(normal, offset)` to the distance. Rotation rotates the
normal about the coordinate origin and leaves the signed distance unchanged.
Projection and closest-point operations require the unit-normal representation.
See `lm2_plane2.h`.

### Polygon

A polygon stores a borrowed pointer and vertex count; it does not copy or own
its array. Keep the array alive while using the polygon. Transformations modify
the shared array in place, and insertion requires caller-provided capacity.
The signed area is positive for counterclockwise order and negative for
clockwise order. The centroid is area-weighted and requires nonzero area.
The point-in-polygon ray-crossing test does not consistently classify points
on the boundary; use a separate edge test if boundary classification matters.

`make_regular` writes counterclockwise vertices starting at the positive X
radius; it requires at least three sides and a nonnegative radius. `make_rect`
writes the four min/max corners in counterclockwise order for ordered bounds.
`make_triangle` writes the tip, then two base endpoints centered at `position`
and perpendicular to `tip - position`; the base width must be nonnegative. If
tip equals position, it uses +Y as the direction. `validate` checks only a
non-null vertex pointer and at least three vertices; it does not prove the
polygon is simple, convex, or nondegenerate. `is_convex` compares consecutive
turn signs and ignores collinear turns, so it can accept a wholly collinear or
self-intersecting input. `is_simple` checks only nonadjacent edge
intersections; it does not establish distinct vertices or nondegeneracy, and
three coincident vertices can pass. Insertion accepts an index through the current count
and needs one extra array slot; removal requires more than three vertices.
Both shift later vertices and update the caller's count.

General polygon operations include simple concave polygons, but collision and
raycast routines have stricter requirements described below. Triangulation
accepts a simple nondegenerate polygon of either winding and writes up to
`vertex_count - 2` triangles as indices into the original array. Allocate
`3 * (vertex_count - 2)` indices, without overlapping the vertices. A smaller
result means triangulation was incomplete or allocation failed. Splitting
requires `max_vertices >= 3`, space for `n - 2` output polygon structures and
`3 * (n - 2)` output vertices for `n` input vertices; output arrays must not
overlap input or each other. A zero result signals failure; successful output
polygons point into the supplied vertex buffer. If the input already fits, it
is copied unchanged even when concave; splitting does not guarantee convex
output suitable for collision or raycast queries. See `lm2_polygon.h`.

### Triangle2

A triangle is an array of three vertices. Signed area and winding use the
Cartesian convention above. Winding returns `LM2_WINDING_NONE` when the
absolute signed area is below the type's machine epsilon. Point containment
includes the edges for a nondegenerate triangle of either winding. Triangle
overlap tests vertex containment and closed edge intersections, so touching
counts. Use nondegenerate triangles for both: a triangle with coincident
vertices treats any point as inside, and a collinear triangle treats points on
its supporting line as inside; overlap can therefore report distant degenerate
triangles as overlapping.

The classification helpers use absolute, strict comparisons against the given
`epsilon`: degeneracy compares area, right-triangle tests compare squared
lengths, and isosceles/equilateral tests compare lengths. Therefore one
numerical tolerance applies to quantities with different units. With epsilon
zero, even a zero-area triangle is not considered degenerate and equal side
lengths do not satisfy the strict equality checks. `classify` chooses the first
match in this order: degenerate, right, equilateral, isosceles, scalene. The
individual right test does not reject degeneracy on its own. `shared_edge`
compares endpoints componentwise with a strict epsilon in either direction;
if found it returns the first matching edge from the first triangle. The edge
value is unspecified when `exists` is false. See `lm2_triangle2.h`.

`lm2_triangle2_geometry.h` converts triangle lists to flat vertex arrays or
indexed meshes and back. The indexed conversion deduplicates against previously
emitted vertices when the absolute difference in **each component** is at
most `epsilon`; it chooses the first matching vertex. Use its size query with
the same input and nonnegative epsilon; allocate at least the larger of its `vertex_count`
and `triangle_count` vertices, and its
`index_count` indices. Counts and indices must fit `uint32_t`; pointers must
be non-null even for empty input. Keep input, vertex, and index buffers
disjoint. A new vertex is written before its capacity
assertion, so an undersized buffer is unsafe. Index and vertex counts for
triangle lists must be multiples of three, and indices must refer to existing
vertices. If the size query cannot
allocate its temporary deduplication buffer, it returns the conservative upper
bound of three vertices per triangle.

### Shape2

A tagged, non-owning pointer to a circle, capsule, AABB, triangle, polygon, or
edge. The pointed-to object and any polygon vertex array must remain alive
through each query. The tag and precision must match the object. Planes are not
among the generic shape variants. See `lm2_shape2.h`.

## Raycasting

`lm2_ray2_make` stores the supplied direction unchanged; provide a unit vector
so `t` and `t_max` are distances. `lm2_ray2_from_points` normalizes the
vector from start to end and sets `t_max` to its length; coincident points
produce zero direction and `t_max = 0`.
`lm2_ray2_point_at` evaluates `origin + direction * t` without clamping.
Raycasts restrict hits to the ray interval from zero through `t_max`.

A hit reports `hit`, `t`, `point`, and a surface `normal` in the input space.
On a miss, do not use the point or normal. When the ray begins inside a shape,
the normal may be zero or arbitrary; a circle raycast also returns zero normal
when the origin is on its boundary. At extreme distances, a rounded `t` may
not reproduce the returned circle or capsule surface point when substituted
into the ray equation. A plane raycast misses when the absolute dot product of
direction and normal is below `LM2_RAYCAST2_EPSILON_F32` or `_F64`; the
threshold depends on their scale. Its hit normal faces against the ray direction. The segment wrappers are retained for compatibility;
`lm2_raycast_edge2` accepts an edge directly.

Polygon raycasts require 3–8 convex, nondegenerate, counterclockwise vertices;
triangle raycasts require nondegenerate counterclockwise triangles. These
conditions are not fully checked at runtime. Polygon and triangle raycasts in
both precisions report a miss when the origin is inside or when the only
entering face is at `t = 0` (for example, starting on a face and pointing
inward). Circle, capsule and AABB raycasts can report an origin hit at `t = 0`.
See `lm2_raycast2.h` and `lm2_rayhit2.h`.

## Collision Manifolds

`lm2_collide_*` functions return a boolean; `lm2_manifold_*` functions write
up to two contacts, their depths, and a normal. For shape pairs, the normal
convention is from the first argument toward the second, with fallback
directions for ambiguous coincident or contained cases. Contact points use the
input coordinate space. Empty manifolds and unused contact slots are zeroed.
The output pointer must be non-null. Collision predicates and manifolds use
the precision named by the suffix. Polygons in shape-pair operations must be
convex and nondegenerate, with 3–8 counterclockwise vertices; triangles must
be nondegenerate and counterclockwise. These requirements are not fully
checked at runtime.

Tangency handling differs between pairs and between boolean and manifold
queries. Circle-circle boolean collision includes external tangency, but its
manifold returns no contacts at exact tangency. Circle-AABB and circle-capsule
boolean tests require strict overlap; AABB-AABB boolean tests include touching,
and the f64 AABB-AABB manifold reports a zero-depth contact at touching.
Do not infer a manifold contact solely from the boolean result. Some f32
collision pairs use a GJK backend with a near-zero `FLT_EPSILON` cutoff and can
disagree with f64 or direct shape tests at very small separations. For example,
two zero-radius, point-like capsules separated by `5e-8` can collide according
to the f32 boolean pair test while the direct capsule-overlap test says no.

Plane manifolds return the supplied plane normal rather than orienting it from
the first shape to the plane. Circle and capsule routines compare the
absolute distances of the center or endpoints to the infinite line and require
strictly positive penetration; exact tangency produces no contact. The capsule
routine only checks its endpoints. AABB, triangle and polygon routines
return up to the first two vertices on the plane's negative side, even when the
whole shape lies on that side and only touches the line. These routines have
different semantics from a general solid-shape intersection test.

Generic shape manifolds support circle, capsule, AABB, triangle, and polygon
pairs. A pair involving an edge is unsupported and returns an empty manifold;
shape data pointers must be non-null. The `f64` convex hull routine considers
all finite input points and can return more than eight vertices; the `f32`
version uses only the first eight and returns zero for two or fewer inputs.
Both truncate to output capacity and permit input/output overlap. Normal
computation returns the normalized right-hand edge perpendicular `(dy, -dx)`,
outward for counterclockwise vertices, and supports overlapping arrays. For a
zero-length edge, f64 returns zero while f32 may return NaNs. See
`lm2_manifold2.h` for the available pairs and helpers.

## Example

```c
lm2_circle_f32 c = lm2_circle_make_coords_f32(0, 0, 5.0f);
lm2_v2_f32 point = lm2_v2_make_f32(3.0f, 4.0f);

bool inside = lm2_circle_contains_point_f32(c, point);  // true (dist=5, radius=5)
float area = lm2_circle_area_f32(c);                     // ~78.54
```
