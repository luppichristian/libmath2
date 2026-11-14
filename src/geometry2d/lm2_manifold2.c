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

#include "lm2_c2_utils.h"
#include "lm2/geometry2d/lm2_manifold2.h"
#include "lm2/geometry2d/lm2_plane2.h"
#include "lm2/geometry2d/lm2_shape2.h"
#include "lm2/scalar/lm2_safe_ops.h"
#include "lm2/scalar/lm2_scalar.h"
#include "lm2/vectors/lm2_vector_specifics.h"

#include <float.h>
#include <limits.h>
#include <math.h>
#include <string.h>

// Polygon manifold calculations use coordinates relative to the reference face
// so that translating a shape does not discard its sub-float contact depth.
static double _lm2_polygon_manifold_faces_f64(const lm2_v2_f64* a, size_t a_count, const lm2_v2_f64* b, size_t b_count, size_t* face) {
  double best = -INFINITY;
  for (size_t i = 0; i < a_count; ++i) {
    lm2_v2_f64 start = a[i], end = a[(i + 1) % a_count];
    double dx = end.x - start.x, dy = end.y - start.y;
    double length = hypot(dx, dy);
    if (length == 0.0) continue;
    double nx = dy / length, ny = -dx / length;
    double separation = INFINITY;
    for (size_t j = 0; j < b_count; ++j) {
      double distance = (b[j].x - start.x) * nx + (b[j].y - start.y) * ny;
      separation = fmin(separation, distance);
    }
    if (separation > best) {
      best = separation;
      *face = i;
    }
  }
  return best;
}

static bool _lm2_polygon_clip_side_f64(lm2_v2_f64 segment[2], double tx, double ty, double limit, bool upper) {
  double along0 = segment[0].x * tx + segment[0].y * ty;
  double along1 = segment[1].x * tx + segment[1].y * ty;
  double d0 = upper ? along0 - limit : -along0;
  double d1 = upper ? along1 - limit : -along1;
  lm2_v2_f64 result[2];
  int count = 0;
  if (d0 < 0.0) result[count++] = segment[0];
  if (d1 < 0.0) result[count++] = segment[1];
  if (d0 == 0.0 && d1 == 0.0) {
    result[count++] = segment[0];
    result[count++] = segment[1];
  } else if ((d0 <= 0.0 && d1 >= 0.0) || (d1 <= 0.0 && d0 >= 0.0)) {
    double scale = fmax(fabs(d0), fabs(d1));
    double t = (d0 / scale) / (d0 / scale - d1 / scale);
    result[count++] = (lm2_v2_f64) {segment[0].x + t * (segment[1].x - segment[0].x),
                                    segment[0].y + t * (segment[1].y - segment[0].y)};
  }
  if (count < 2) return false;
  segment[0] = result[0];
  segment[1] = result[1];
  return true;
}

static void _lm2_polygon_manifold_f64(const lm2_v2_f64* a, size_t a_count, const lm2_v2_f64* b, size_t b_count, lm2_manifold_f64* out) {
  *out = (lm2_manifold_f64) {0};
  size_t face_a = 0, face_b = 0;
  double sep_a = _lm2_polygon_manifold_faces_f64(a, a_count, b, b_count, &face_a);
  if (sep_a >= 0.0 || !isfinite(sep_a)) return;
  double sep_b = _lm2_polygon_manifold_faces_f64(b, b_count, a, a_count, &face_b);
  if (sep_b >= 0.0 || !isfinite(sep_b)) return;
  // Reference the face with the least penetration. An absolute bias makes
  // the choice depend on scale and can select a face whose incident edge
  // does not overlap it at all for small polygons.
  bool flip = sep_b >= sep_a;
  const lm2_v2_f64* ref = flip ? b : a;
  const lm2_v2_f64* inc = flip ? a : b;
  size_t ref_count = flip ? b_count : a_count;
  size_t inc_count = flip ? a_count : b_count;
  size_t face = flip ? face_b : face_a;
  lm2_v2_f64 origin = ref[face], end = ref[(face + 1) % ref_count];
  double dx = end.x - origin.x, dy = end.y - origin.y;
  double length = hypot(dx, dy);
  if (length == 0.0 || !isfinite(length)) return;
  double tx = dx / length, ty = dy / length, nx = ty, ny = -tx;
  double best_dot = INFINITY;
  size_t incident = 0;
  for (size_t i = 0; i < inc_count; ++i) {
    lm2_v2_f64 p = inc[i], q = inc[(i + 1) % inc_count];
    double ex = q.x - p.x, ey = q.y - p.y, edge_length = hypot(ex, ey);
    if (edge_length == 0.0) continue;
    double dot = nx * (ey / edge_length) - ny * (ex / edge_length);
    if (dot < best_dot) {
      best_dot = dot;
      incident = i;
    }
  }
  if (!isfinite(best_dot)) return;
  lm2_v2_f64 p = inc[incident], q = inc[(incident + 1) % inc_count];
  lm2_v2_f64 segment[2] = {
      {p.x - origin.x, p.y - origin.y},
      {q.x - origin.x, q.y - origin.y}
  };
  if (!_lm2_polygon_clip_side_f64(segment, tx, ty, length, false) ||
      !_lm2_polygon_clip_side_f64(segment, tx, ty, length, true)) return;
  for (int i = 0; i < 2; ++i) {
    double x = segment[i].x, y = segment[i].y;
    double depth = -(x * nx + y * ny);
    if (depth >= 0.0) {
      int index = out->count++;
      out->depths[index] = depth;
      out->contact_points[index] = (lm2_v2_f64) {origin.x + x, origin.y + y};
    }
  }
  if (out->count) out->normal = (lm2_v2_f64) {flip ? -nx : nx, flip ? -ny : ny};
}

static double _lm2_cross_points_f64(lm2_v2_f64 a, lm2_v2_f64 b, lm2_v2_f64 p) {
  double dx = b.x - a.x, dy = b.y - a.y;
  double px = p.x - a.x, py = p.y - a.y;
  double edge_scale = fmax(fabs(dx), fabs(dy));
  double point_scale = fmax(fabs(px), fabs(py));
  if (edge_scale == 0.0 || point_scale == 0.0) return 0.0;
  return (dx / edge_scale) * (py / point_scale) - (dy / edge_scale) * (px / point_scale);
}

static double _lm2_point_segment_distance_f64(lm2_v2_f64 p, lm2_v2_f64 a, lm2_v2_f64 b) {
  double dx = b.x - a.x, dy = b.y - a.y;
  double length = hypot(dx, dy);
  if (length == 0.0) return hypot(p.x - a.x, p.y - a.y);
  double ux = dx / length, uy = dy / length;
  double px = p.x - a.x, py = p.y - a.y;
  double along = px * ux + py * uy;
  if (along < 0.0) along = 0.0;
  if (along > length) along = length;
  return hypot(px - along * ux, py - along * uy);
}

static bool _lm2_point_on_segment_f64(lm2_v2_f64 p, lm2_v2_f64 a, lm2_v2_f64 b) {
  return p.x >= fmin(a.x, b.x) && p.x <= fmax(a.x, b.x) &&
         p.y >= fmin(a.y, b.y) && p.y <= fmax(a.y, b.y);
}

static double _lm2_segment_distance_f64(lm2_v2_f64 a, lm2_v2_f64 b, lm2_v2_f64 c, lm2_v2_f64 d) {
  double ab_c = _lm2_cross_points_f64(a, b, c), ab_d = _lm2_cross_points_f64(a, b, d);
  double cd_a = _lm2_cross_points_f64(c, d, a), cd_b = _lm2_cross_points_f64(c, d, b);
  if (((ab_c > 0.0 && ab_d < 0.0) || (ab_c < 0.0 && ab_d > 0.0)) &&
      ((cd_a > 0.0 && cd_b < 0.0) || (cd_a < 0.0 && cd_b > 0.0))) return 0.0;
  if ((ab_c == 0.0 && _lm2_point_on_segment_f64(c, a, b)) ||
      (ab_d == 0.0 && _lm2_point_on_segment_f64(d, a, b)) ||
      (cd_a == 0.0 && _lm2_point_on_segment_f64(a, c, d)) ||
      (cd_b == 0.0 && _lm2_point_on_segment_f64(b, c, d))) return 0.0;
  return fmin(fmin(_lm2_point_segment_distance_f64(a, c, d), _lm2_point_segment_distance_f64(b, c, d)),
              fmin(_lm2_point_segment_distance_f64(c, a, b), _lm2_point_segment_distance_f64(d, a, b)));
}

static bool _lm2_point_in_convex_f64(lm2_v2_f64 p, const lm2_v2_f64* vertices, size_t count) {
  bool positive = false, negative = false;
  bool has_area = false;
  for (size_t i = 0; i < count; ++i) {
    double cross = _lm2_cross_points_f64(vertices[i], vertices[(i + 1) % count], p);
    positive |= cross > 0.0;
    negative |= cross < 0.0;
    if (positive && negative) return false;
    if (_lm2_cross_points_f64(vertices[0], vertices[i], vertices[(i + 1) % count]) != 0.0) has_area = true;
  }
  if (has_area) return true;
  for (size_t i = 0; i < count; ++i) {
    if (_lm2_cross_points_f64(vertices[i], vertices[(i + 1) % count], p) == 0.0 &&
        _lm2_point_on_segment_f64(p, vertices[i], vertices[(i + 1) % count])) return true;
  }
  return false;
}

static bool _lm2_convex_overlap_f64(const lm2_v2_f64* a, size_t a_count, const lm2_v2_f64* b, size_t b_count) {
  bool a_has_area = false, b_has_area = false;
  for (size_t i = 1; i + 1 < a_count; ++i)
    if (_lm2_cross_points_f64(a[0], a[i], a[i + 1]) != 0.0) a_has_area = true;
  for (size_t i = 1; i + 1 < b_count; ++i)
    if (_lm2_cross_points_f64(b[0], b[i], b[i + 1]) != 0.0) b_has_area = true;
  if (!a_has_area || !b_has_area) {
    if (_lm2_point_in_convex_f64(a[0], b, b_count) || _lm2_point_in_convex_f64(b[0], a, a_count)) return true;
    for (size_t i = 0; i < a_count; ++i)
      for (size_t j = 0; j < b_count; ++j)
        if (_lm2_segment_distance_f64(a[i], a[(i + 1) % a_count], b[j], b[(j + 1) % b_count]) == 0.0)
          return true;
    return false;
  }
  double coordinate_scale = 0.0;
  for (size_t i = 0; i < a_count; ++i)
    coordinate_scale = fmax(coordinate_scale, fmax(fabs(a[i].x - a[0].x), fabs(a[i].y - a[0].y)));
  for (size_t i = 0; i < b_count; ++i)
    coordinate_scale = fmax(coordinate_scale, fmax(fabs(b[i].x - a[0].x), fabs(b[i].y - a[0].y)));
  if (coordinate_scale == 0.0) return true;
  for (int shape = 0; shape < 2; ++shape) {
    const lm2_v2_f64* vertices = shape == 0 ? a : b;
    size_t count = shape == 0 ? a_count : b_count;
    for (size_t i = 0; i < count; ++i) {
      lm2_v2_f64 start = vertices[i], end = vertices[(i + 1) % count];
      double nx = -(end.y - start.y), ny = end.x - start.x;
      double axis_scale = fmax(fabs(nx), fabs(ny));
      if (axis_scale == 0.0) continue;
      nx /= axis_scale;
      ny /= axis_scale;
      double a_min = 0.0, a_max = 0.0;
      double b_min = ((b[0].x - a[0].x) / coordinate_scale) * nx +
                     ((b[0].y - a[0].y) / coordinate_scale) * ny,
             b_max = b_min;
      for (size_t j = 1; j < a_count; ++j) {
        double projection = ((a[j].x - a[0].x) / coordinate_scale) * nx +
                            ((a[j].y - a[0].y) / coordinate_scale) * ny;
        a_min = fmin(a_min, projection);
        a_max = fmax(a_max, projection);
      }
      for (size_t j = 1; j < b_count; ++j) {
        double projection = ((b[j].x - a[0].x) / coordinate_scale) * nx +
                            ((b[j].y - a[0].y) / coordinate_scale) * ny;
        b_min = fmin(b_min, projection);
        b_max = fmax(b_max, projection);
      }
      if (a_max < b_min || b_max < a_min) return false;
    }
  }
  return true;
}

static bool _lm2_circle_convex_f64(lm2_circle_f64 circle, const lm2_v2_f64* vertices, size_t count) {
  if (_lm2_point_in_convex_f64(circle.center, vertices, count)) return true;
  for (size_t i = 0; i < count; ++i) {
    if (_lm2_point_segment_distance_f64(circle.center, vertices[i], vertices[(i + 1) % count]) <= circle.radius)
      return true;
  }
  return false;
}

static bool _lm2_capsule_convex_f64(lm2_capsule2_f64 capsule, const lm2_v2_f64* vertices, size_t count) {
  if (_lm2_point_in_convex_f64(capsule.start, vertices, count) ||
      _lm2_point_in_convex_f64(capsule.end, vertices, count)) return true;
  for (size_t i = 0; i < count; ++i) {
    if (_lm2_segment_distance_f64(capsule.start, capsule.end, vertices[i], vertices[(i + 1) % count]) <= capsule.radius)
      return true;
  }
  return false;
}

static void _lm2_box_vertices_f64(lm2_r2_f64 box, lm2_v2_f64 vertices[4]) {
  vertices[0] = box.min;
  vertices[1] = (lm2_v2_f64) {box.max.x, box.min.y};
  vertices[2] = box.max;
  vertices[3] = (lm2_v2_f64) {box.min.x, box.max.y};
}

static bool _lm2_box_capsule_f64(lm2_r2_f64 box, lm2_capsule2_f64 capsule) {
  lm2_v2_f64 vertices[4];
  _lm2_box_vertices_f64(box, vertices);
  if ((capsule.start.x >= box.min.x && capsule.start.x <= box.max.x &&
       capsule.start.y >= box.min.y && capsule.start.y <= box.max.y) ||
      (capsule.end.x >= box.min.x && capsule.end.x <= box.max.x &&
       capsule.end.y >= box.min.y && capsule.end.y <= box.max.y)) return true;
  for (size_t i = 0; i < 4; ++i) {
    if (_lm2_segment_distance_f64(capsule.start, capsule.end, vertices[i], vertices[(i + 1) % 4]) <= capsule.radius)
      return true;
  }
  return false;
}

static bool _lm2_box_convex_f64(lm2_r2_f64 box, const lm2_v2_f64* vertices, size_t count) {
  lm2_v2_f64 box_vertices[4];
  _lm2_box_vertices_f64(box, box_vertices);
  return _lm2_convex_overlap_f64(box_vertices, 4, vertices, count);
}

// =============================================================================
// Boolean Collision Detection - f64
// =============================================================================

LM2_API bool lm2_collide_circle_to_circle_f64(lm2_circle_f64 a, lm2_circle_f64 b) {
  double dx = b.center.x - a.center.x;
  double dy = b.center.y - a.center.y;
  return hypot(dx, dy) <= a.radius + b.radius;
}

LM2_API bool lm2_collide_circle_to_aabb_f64(lm2_circle_f64 circle, lm2_r2_f64 aabb) {
  double x = circle.center.x < aabb.min.x ? aabb.min.x : circle.center.x > aabb.max.x ? aabb.max.x
                                                                                      : circle.center.x;
  double y = circle.center.y < aabb.min.y ? aabb.min.y : circle.center.y > aabb.max.y ? aabb.max.y
                                                                                      : circle.center.y;
  double dx = circle.center.x - x;
  double dy = circle.center.y - y;
  return hypot(dx, dy) < circle.radius;
}

LM2_API bool lm2_collide_circle_to_capsule_f64(lm2_circle_f64 circle, lm2_capsule2_f64 capsule) {
  const double dx = capsule.end.x - capsule.start.x;
  const double dy = capsule.end.y - capsule.start.y;
  const double length = hypot(dx, dy);
  const double ux = length > 0.0 ? dx / length : 0.0;
  const double uy = length > 0.0 ? dy / length : 0.0;
  const double ox = circle.center.x - capsule.start.x;
  const double oy = circle.center.y - capsule.start.y;
  double along = ox * ux + oy * uy;
  if (along < 0.0) along = 0.0;
  if (along > length) along = length;
  // Keep the existing strict tangency convention for this predicate.
  return hypot(ox - along * ux, oy - along * uy) < circle.radius + capsule.radius;
}

LM2_API bool lm2_collide_circle_to_polygon_f64(lm2_circle_f64 circle, lm2_polygon_f64 polygon) {
  LM2_ASSERT(polygon.vertices != NULL && polygon.vertex_count >= 3 && polygon.vertex_count <= C2_MAX_POLYGON_VERTS);
  return _lm2_circle_convex_f64(circle, polygon.vertices, polygon.vertex_count);
}

LM2_API bool lm2_collide_aabb_to_aabb_f64(lm2_r2_f64 a, lm2_r2_f64 b) {
  return !(b.max.x < a.min.x || a.max.x < b.min.x ||
           b.max.y < a.min.y || a.max.y < b.min.y);
}

LM2_API bool lm2_collide_aabb_to_capsule_f64(lm2_r2_f64 aabb, lm2_capsule2_f64 capsule) {
  return _lm2_box_capsule_f64(aabb, capsule);
}

LM2_API bool lm2_collide_aabb_to_polygon_f64(lm2_r2_f64 aabb, lm2_polygon_f64 polygon) {
  LM2_ASSERT(polygon.vertices != NULL && polygon.vertex_count >= 3 && polygon.vertex_count <= C2_MAX_POLYGON_VERTS);
  return _lm2_box_convex_f64(aabb, polygon.vertices, polygon.vertex_count);
}

LM2_API bool lm2_collide_capsule_to_capsule_f64(lm2_capsule2_f64 a, lm2_capsule2_f64 b) {
  return _lm2_segment_distance_f64(a.start, a.end, b.start, b.end) <= a.radius + b.radius;
}

LM2_API bool lm2_collide_capsule_to_polygon_f64(lm2_capsule2_f64 capsule, lm2_polygon_f64 polygon) {
  LM2_ASSERT(polygon.vertices != NULL && polygon.vertex_count >= 3 && polygon.vertex_count <= C2_MAX_POLYGON_VERTS);
  return _lm2_capsule_convex_f64(capsule, polygon.vertices, polygon.vertex_count);
}

LM2_API bool lm2_collide_polygon_to_polygon_f64(lm2_polygon_f64 a, lm2_polygon_f64 b) {
  LM2_ASSERT(a.vertices != NULL && a.vertex_count >= 3 && a.vertex_count <= C2_MAX_POLYGON_VERTS);
  LM2_ASSERT(b.vertices != NULL && b.vertex_count >= 3 && b.vertex_count <= C2_MAX_POLYGON_VERTS);
  return _lm2_convex_overlap_f64(a.vertices, a.vertex_count, b.vertices, b.vertex_count);
}

// =============================================================================
// Boolean Collision Detection - f32
// =============================================================================

LM2_API bool lm2_collide_circle_to_circle_f32(lm2_circle_f32 a, lm2_circle_f32 b) {
  float dx = b.center.x - a.center.x;
  float dy = b.center.y - a.center.y;
  return hypotf(dx, dy) <= a.radius + b.radius;
}

LM2_API bool lm2_collide_circle_to_aabb_f32(lm2_circle_f32 circle, lm2_r2_f32 aabb) {
  float x = fmaxf(aabb.min.x, fminf(circle.center.x, aabb.max.x));
  float y = fmaxf(aabb.min.y, fminf(circle.center.y, aabb.max.y));
  return hypotf(circle.center.x - x, circle.center.y - y) < circle.radius;
}

LM2_API bool lm2_collide_circle_to_capsule_f32(lm2_circle_f32 circle, lm2_capsule2_f32 capsule) {
  return c2CircletoCapsule(lm2_circle_f32_to_c2(circle), lm2_capsule2_f32_to_c2(capsule)) != 0;
}

LM2_API bool lm2_collide_circle_to_polygon_f32(lm2_circle_f32 circle, lm2_polygon_f32 polygon) {
  c2Poly poly = lm2_polygon_f32_to_c2(polygon);
  return c2CircletoPoly(lm2_circle_f32_to_c2(circle), &poly, NULL) != 0;
}

LM2_API bool lm2_collide_aabb_to_aabb_f32(lm2_r2_f32 a, lm2_r2_f32 b) {
  return c2AABBtoAABB(lm2_r2_f32_to_c2(a), lm2_r2_f32_to_c2(b)) != 0;
}

LM2_API bool lm2_collide_aabb_to_capsule_f32(lm2_r2_f32 aabb, lm2_capsule2_f32 capsule) {
  return c2AABBtoCapsule(lm2_r2_f32_to_c2(aabb), lm2_capsule2_f32_to_c2(capsule)) != 0;
}

LM2_API bool lm2_collide_aabb_to_polygon_f32(lm2_r2_f32 aabb, lm2_polygon_f32 polygon) {
  c2Poly poly = lm2_polygon_f32_to_c2(polygon);
  return c2AABBtoPoly(lm2_r2_f32_to_c2(aabb), &poly, NULL) != 0;
}

LM2_API bool lm2_collide_capsule_to_capsule_f32(lm2_capsule2_f32 a, lm2_capsule2_f32 b) {
  return c2CapsuletoCapsule(lm2_capsule2_f32_to_c2(a), lm2_capsule2_f32_to_c2(b)) != 0;
}

LM2_API bool lm2_collide_capsule_to_polygon_f32(lm2_capsule2_f32 capsule, lm2_polygon_f32 polygon) {
  c2Poly poly = lm2_polygon_f32_to_c2(polygon);
  return c2CapsuletoPoly(lm2_capsule2_f32_to_c2(capsule), &poly, NULL) != 0;
}

LM2_API bool lm2_collide_polygon_to_polygon_f32(lm2_polygon_f32 a, lm2_polygon_f32 b) {
  c2Poly poly_a = lm2_polygon_f32_to_c2(a);
  c2Poly poly_b = lm2_polygon_f32_to_c2(b);
  return c2PolytoPoly(&poly_a, NULL, &poly_b, NULL) != 0;
}

// =============================================================================
// Manifold Generation - f64
// =============================================================================

LM2_API void lm2_manifold_circle_to_circle_f64(lm2_circle_f64 a, lm2_circle_f64 b, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  *out_manifold = (lm2_manifold_f64) {0};
  double dx = b.center.x - a.center.x;
  double dy = b.center.y - a.center.y;
  double distance = hypot(dx, dy);
  double radius_sum = a.radius + b.radius;
  if (distance >= radius_sum) return;

  lm2_v2_f64 normal = distance != 0.0
                          ? (lm2_v2_f64) {dx / distance, dy / distance}
                          : (lm2_v2_f64) {0.0, 1.0};
  out_manifold->count = 1;
  out_manifold->depths[0] = radius_sum - distance;
  out_manifold->normal = normal;
  out_manifold->contact_points[0].x = b.center.x - normal.x * b.radius;
  out_manifold->contact_points[0].y = b.center.y - normal.y * b.radius;
}

LM2_API void lm2_manifold_circle_to_aabb_f64(lm2_circle_f64 circle, lm2_r2_f64 aabb, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  *out_manifold = (lm2_manifold_f64) {0};
  double closest_x = fmax(aabb.min.x, fmin(circle.center.x, aabb.max.x));
  double closest_y = fmax(aabb.min.y, fmin(circle.center.y, aabb.max.y));
  double dx = closest_x - circle.center.x;
  double dy = closest_y - circle.center.y;
  double distance = hypot(dx, dy);
  if (distance >= circle.radius) return;

  out_manifold->count = 1;
  if (distance > 0.0) {
    out_manifold->normal = (lm2_v2_f64) {dx / distance, dy / distance};
    out_manifold->depths[0] = circle.radius - distance;
    out_manifold->contact_points[0] = (lm2_v2_f64) {closest_x, closest_y};
  } else {
    double left = circle.center.x - aabb.min.x;
    double right = aabb.max.x - circle.center.x;
    double bottom = circle.center.y - aabb.min.y;
    double top = aabb.max.y - circle.center.y;
    double x_overlap = fmin(left, right);
    double y_overlap = fmin(bottom, top);
    double depth;
    if (x_overlap < y_overlap) {
      depth = x_overlap;
      out_manifold->normal = (lm2_v2_f64) {left < right ? 1.0 : -1.0, 0.0};
    } else {
      depth = y_overlap;
      out_manifold->normal = (lm2_v2_f64) {0.0, bottom < top ? 1.0 : -1.0};
    }
    out_manifold->depths[0] = circle.radius + depth;
    out_manifold->contact_points[0].x = circle.center.x - out_manifold->normal.x * depth;
    out_manifold->contact_points[0].y = circle.center.y - out_manifold->normal.y * depth;
  }
}

LM2_API void lm2_manifold_circle_to_capsule_f64(lm2_circle_f64 circle, lm2_capsule2_f64 capsule, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  *out_manifold = (lm2_manifold_f64) {0};
  const double axis_x = capsule.end.x - capsule.start.x;
  const double axis_y = capsule.end.y - capsule.start.y;
  const double length = hypot(axis_x, axis_y);
  const double ux = length > 0.0 ? axis_x / length : 0.0;
  const double uy = length > 0.0 ? axis_y / length : 0.0;
  const double ox = circle.center.x - capsule.start.x;
  const double oy = circle.center.y - capsule.start.y;
  double along = ox * ux + oy * uy;
  along = fmax(0.0, fmin(along, length));
  const double dx = along * ux - ox;
  const double dy = along * uy - oy;
  const double distance = hypot(dx, dy);
  const double radius_sum = circle.radius + capsule.radius;
  if (distance >= radius_sum) return;

  const lm2_v2_f64 normal = distance > 0.0
                                ? (lm2_v2_f64) {dx / distance, dy / distance}
                                : (length > 0.0 ? (lm2_v2_f64) {-uy, ux} : (lm2_v2_f64) {0.0, 1.0});
  out_manifold->count = 1;
  out_manifold->normal = normal;
  out_manifold->depths[0] = radius_sum - distance;
  out_manifold->contact_points[0] = (lm2_v2_f64) {
      capsule.start.x + along * ux - normal.x * capsule.radius,
      capsule.start.y + along * uy - normal.y * capsule.radius};
}

LM2_API void lm2_manifold_circle_to_polygon_f64(lm2_circle_f64 circle, lm2_polygon_f64 polygon, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  LM2_ASSERT(polygon.vertices != NULL && polygon.vertex_count >= 3 && polygon.vertex_count <= C2_MAX_POLYGON_VERTS);
  *out_manifold = (lm2_manifold_f64) {0};
  bool inside = true;
  double max_separation = -INFINITY;
  double closest_distance = INFINITY;
  lm2_v2_f64 face_normal = {0.0, 0.0};
  lm2_v2_f64 closest = {0.0, 0.0};
  for (size_t i = 0; i < polygon.vertex_count; ++i) {
    const lm2_v2_f64 a = polygon.vertices[i];
    const lm2_v2_f64 b = polygon.vertices[(i + 1) % polygon.vertex_count];
    const double ex = b.x - a.x;
    const double ey = b.y - a.y;
    const double length = hypot(ex, ey);
    LM2_ASSERT(length > 0.0);
    const double ux = ex / length;
    const double uy = ey / length;
    const double ax = a.x - circle.center.x;
    const double ay = a.y - circle.center.y;
    const double separation = ax * -uy + ay * ux;
    if (separation > 0.0) inside = false;
    if (separation > max_separation) {
      max_separation = separation;
      face_normal = (lm2_v2_f64) {uy, -ux};
    }
    double along = -(ax * ux + ay * uy);
    along = fmax(0.0, fmin(along, length));
    const double dx = ax + along * ux;
    const double dy = ay + along * uy;
    const double distance = hypot(dx, dy);
    if (distance < closest_distance) {
      closest_distance = distance;
      closest = (lm2_v2_f64) {dx, dy};
    }
  }
  if (inside) {
    out_manifold->count = 1;
    out_manifold->normal = (lm2_v2_f64) {-face_normal.x, -face_normal.y};
    out_manifold->depths[0] = circle.radius - max_separation;
    out_manifold->contact_points[0] = (lm2_v2_f64) {circle.center.x - face_normal.x * max_separation,
                                                    circle.center.y - face_normal.y * max_separation};
  } else if (closest_distance < circle.radius) {
    out_manifold->count = 1;
    out_manifold->normal = (lm2_v2_f64) {closest.x / closest_distance, closest.y / closest_distance};
    out_manifold->depths[0] = circle.radius - closest_distance;
    out_manifold->contact_points[0] = (lm2_v2_f64) {circle.center.x + closest.x, circle.center.y + closest.y};
  }
}

// Both endpoints are ordered. Same-sign subtraction cannot overflow, and
// avoids losing a subnormal endpoint by halving each operand separately.
static double _lm2_interval_midpoint_f64(double lower, double upper) {
  return lower < 0.0 && upper > 0.0 ? lower * 0.5 + upper * 0.5 : lower + (upper - lower) * 0.5;
}

static float _lm2_interval_midpoint_f32(float lower, float upper) {
  return lower < 0.0f && upper > 0.0f ? lower * 0.5f + upper * 0.5f : lower + (upper - lower) * 0.5f;
}

LM2_API void lm2_manifold_aabb_to_aabb_f64(lm2_r2_f64 a, lm2_r2_f64 b, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  *out_manifold = (lm2_manifold_f64) {0};
  double dx = fmin(a.max.x - b.min.x, b.max.x - a.min.x);
  double dy = fmin(a.max.y - b.min.y, b.max.y - a.min.y);
  if (dx < 0.0 || dy < 0.0) return;

  double ax = a.min.x * 0.5 + a.max.x * 0.5;
  double ay = a.min.y * 0.5 + a.max.y * 0.5;
  double bx = b.min.x * 0.5 + b.max.x * 0.5;
  double by = b.min.y * 0.5 + b.max.y * 0.5;
  out_manifold->count = 1;
  if (dx < dy) {
    out_manifold->normal = (lm2_v2_f64) {bx < ax ? -1.0 : 1.0, 0.0};
    out_manifold->depths[0] = dx;
    double tangent = _lm2_interval_midpoint_f64(fmax(a.min.y, b.min.y), fmin(a.max.y, b.max.y));
    out_manifold->contact_points[0] = (lm2_v2_f64) {bx < ax ? a.min.x : a.max.x, tangent};
  } else {
    out_manifold->normal = (lm2_v2_f64) {0.0, by < ay ? -1.0 : 1.0};
    out_manifold->depths[0] = dy;
    double tangent = _lm2_interval_midpoint_f64(fmax(a.min.x, b.min.x), fmin(a.max.x, b.max.x));
    out_manifold->contact_points[0] = (lm2_v2_f64) {tangent, by < ay ? a.min.y : a.max.y};
  }
}

LM2_API void lm2_manifold_aabb_to_capsule_f64(lm2_r2_f64 aabb, lm2_capsule2_f64 capsule, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  lm2_v2_f64 vertices[4];
  _lm2_box_vertices_f64(aabb, vertices);
  lm2_polygon_f64 polygon = {vertices, 4};
  lm2_manifold_capsule_to_polygon_f64(capsule, polygon, out_manifold);
  if (out_manifold->count) {
    out_manifold->normal.x = -out_manifold->normal.x;
    out_manifold->normal.y = -out_manifold->normal.y;
  }
}

LM2_API void lm2_manifold_aabb_to_polygon_f64(lm2_r2_f64 aabb, lm2_polygon_f64 polygon, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  LM2_ASSERT(polygon.vertices != NULL && polygon.vertex_count >= 3 && polygon.vertex_count <= C2_MAX_POLYGON_VERTS);
  lm2_v2_f64 box[4];
  _lm2_box_vertices_f64(aabb, box);
  _lm2_polygon_manifold_f64(box, 4, polygon.vertices, polygon.vertex_count, out_manifold);
}

static lm2_v2_f64 _lm2_capsule_project_f64(lm2_v2_f64 p, lm2_v2_f64 start, lm2_v2_f64 end) {
  const double dx = end.x - start.x, dy = end.y - start.y;
  const double length = hypot(dx, dy);
  if (length == 0.0) return start;
  const double ux = dx / length, uy = dy / length;
  const double along = fmax(0.0, fmin(length, (p.x - start.x) * ux + (p.y - start.y) * uy));
  return (lm2_v2_f64) {start.x + along * ux, start.y + along * uy};
}

static void _lm2_capsule_candidate_f64(lm2_v2_f64 p, lm2_v2_f64 q, double* best, lm2_v2_f64* best_p, lm2_v2_f64* best_q) {
  const double distance = hypot(q.x - p.x, q.y - p.y);
  if (distance < *best) {
    *best = distance;
    *best_p = p;
    *best_q = q;
  }
}

LM2_API void lm2_manifold_capsule_to_capsule_f64(lm2_capsule2_f64 a, lm2_capsule2_f64 b, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  *out_manifold = (lm2_manifold_f64) {0};
  // Work relative to A's first endpoint to retain small separations after a
  // large translation. Four endpoint projections cover nonintersecting axes.
  const lm2_v2_f64 a0 = {0.0, 0.0};
  const lm2_v2_f64 a1 = {a.end.x - a.start.x, a.end.y - a.start.y};
  const lm2_v2_f64 b0 = {b.start.x - a.start.x, b.start.y - a.start.y};
  const lm2_v2_f64 b1 = {b.end.x - a.start.x, b.end.y - a.start.y};
  const double alen = hypot(a1.x, a1.y), blen = hypot(b1.x - b0.x, b1.y - b0.y);
  lm2_v2_f64 pa = a0, pb = b0;
  double distance = INFINITY;
  _lm2_capsule_candidate_f64(a0, _lm2_capsule_project_f64(a0, b0, b1), &distance, &pa, &pb);
  _lm2_capsule_candidate_f64(a1, _lm2_capsule_project_f64(a1, b0, b1), &distance, &pa, &pb);
  _lm2_capsule_candidate_f64(_lm2_capsule_project_f64(b0, a0, a1), b0, &distance, &pa, &pb);
  _lm2_capsule_candidate_f64(_lm2_capsule_project_f64(b1, a0, a1), b1, &distance, &pa, &pb);

  // For crossing axes the minimum is an interior intersection.
  if (alen > 0.0 && blen > 0.0) {
    const double ax = a1.x / alen, ay = a1.y / alen;
    const double bx = (b1.x - b0.x) / blen, by = (b1.y - b0.y) / blen;
    const double det = ax * by - ay * bx;
    if (det != 0.0) {
      const double t = (b0.x * by - b0.y * bx) / det;
      const double u = (b0.x * ay - b0.y * ax) / det;
      if (t >= 0.0 && t <= alen && u >= 0.0 && u <= blen) {
        pa = (lm2_v2_f64) {t * ax, t * ay};
        pb = pa;
        distance = 0.0;
      }
    }
  }
  const double radius = a.radius + b.radius;
  if (distance >= radius) return;
  const lm2_v2_f64 normal = distance > 0.0
                                ? (lm2_v2_f64) {(pb.x - pa.x) / distance, (pb.y - pa.y) / distance}
                                : (alen > 0.0 ? (lm2_v2_f64) {-a1.y / alen, a1.x / alen} : (lm2_v2_f64) {0.0, 1.0});
  out_manifold->count = 1;
  out_manifold->normal = normal;
  out_manifold->depths[0] = radius - distance;
  out_manifold->contact_points[0] = (lm2_v2_f64) {a.start.x + pb.x - normal.x * b.radius,
                                                  a.start.y + pb.y - normal.y * b.radius};
}

static double _lm2_cap_poly_dot_f64(lm2_v2_f64 a, lm2_v2_f64 b) {
  return a.x * b.x + a.y * b.y;
}

static lm2_v2_f64 _lm2_cap_poly_sub_f64(lm2_v2_f64 a, lm2_v2_f64 b) {
  return (lm2_v2_f64) {a.x - b.x, a.y - b.y};
}

// Clip a segment against dot(normal, point - origin) <= 0, preserving the
// backend's endpoint ordering for the resulting contacts.
static int _lm2_cap_poly_clip_f64(lm2_v2_f64 seg[2], lm2_v2_f64 origin, lm2_v2_f64 normal) {
  lm2_v2_f64 out[2];
  int count = 0;
  double d0 = _lm2_cap_poly_dot_f64(_lm2_cap_poly_sub_f64(seg[0], origin), normal);
  double d1 = _lm2_cap_poly_dot_f64(_lm2_cap_poly_sub_f64(seg[1], origin), normal);
  if (d0 < 0.0) out[count++] = seg[0];
  if (d1 < 0.0) out[count++] = seg[1];
  if (d0 == 0.0 && d1 == 0.0) {
    out[count++] = seg[0];
    out[count++] = seg[1];
  } else if ((d0 <= 0.0 && d1 >= 0.0) || (d1 <= 0.0 && d0 >= 0.0)) {
    double t = d0 / (d0 - d1);
    out[count++] = (lm2_v2_f64) {seg[0].x + t * (seg[1].x - seg[0].x),
                                 seg[0].y + t * (seg[1].y - seg[0].y)};
  }
  if (count == 2) {
    seg[0] = out[0];
    seg[1] = out[1];
  }
  return count;
}

LM2_API void lm2_manifold_capsule_to_polygon_f64(lm2_capsule2_f64 capsule, lm2_polygon_f64 polygon, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  LM2_ASSERT(polygon.vertices != NULL && polygon.vertex_count >= 3 && polygon.vertex_count <= C2_MAX_POLYGON_VERTS);
  *out_manifold = (lm2_manifold_f64) {0};
  lm2_v2_f64 axis = _lm2_cap_poly_sub_f64(capsule.end, capsule.start);
  double length = hypot(axis.x, axis.y);
  if (length == 0.0) {
    lm2_circle_f64 circle = {capsule.start, capsule.radius};
    lm2_manifold_circle_to_polygon_f64(circle, polygon, out_manifold);
    return;
  }
  lm2_v2_f64 vertices[C2_MAX_POLYGON_VERTS];
  for (size_t i = 0; i < polygon.vertex_count; ++i)
    vertices[i] = _lm2_cap_poly_sub_f64(polygon.vertices[i], capsule.start);
  lm2_v2_f64 zero = {0.0, 0.0}, point_a = zero, point_b = zero;
  double distance = INFINITY;
  for (size_t i = 0; i < polygon.vertex_count; ++i) {
    lm2_v2_f64 a = vertices[i], b = vertices[(i + 1) % polygon.vertex_count];
    _lm2_capsule_candidate_f64(zero, _lm2_capsule_project_f64(zero, a, b), &distance, &point_a, &point_b);
    _lm2_capsule_candidate_f64(axis, _lm2_capsule_project_f64(axis, a, b), &distance, &point_a, &point_b);
    _lm2_capsule_candidate_f64(_lm2_capsule_project_f64(a, zero, axis), a, &distance, &point_a, &point_b);
    _lm2_capsule_candidate_f64(_lm2_capsule_project_f64(b, zero, axis), b, &distance, &point_a, &point_b);
  }
  lm2_capsule2_f64 segment = {zero, axis, 0.0};
  if (!_lm2_capsule_convex_f64(segment, vertices, polygon.vertex_count)) {
    if (distance >= capsule.radius || distance == 0.0) return;
    lm2_v2_f64 n = {(point_b.x - point_a.x) / distance, (point_b.y - point_a.y) / distance};
    out_manifold->count = 1;
    out_manifold->normal = n;
    out_manifold->depths[0] = capsule.radius - distance;
    out_manifold->contact_points[0] = (lm2_v2_f64) {capsule.start.x + point_a.x + n.x * capsule.radius,
                                                    capsule.start.y + point_a.y + n.y * capsule.radius};
    return;
  }

  // Select the least-penetrating polygon face or capsule side as the reference.
  double best = -INFINITY;
  size_t face = 0;
  int code = 0;
  for (size_t i = 0; i < polygon.vertex_count; ++i) {
    lm2_v2_f64 a = vertices[i], b = vertices[(i + 1) % polygon.vertex_count];
    lm2_v2_f64 e = _lm2_cap_poly_sub_f64(b, a);
    double len = hypot(e.x, e.y);
    LM2_ASSERT(len > 0.0);
    lm2_v2_f64 n = {e.y / len, -e.x / len};
    double sep = fmin(_lm2_cap_poly_dot_f64(_lm2_cap_poly_sub_f64(zero, a), n),
                      _lm2_cap_poly_dot_f64(_lm2_cap_poly_sub_f64(axis, a), n));
    if (sep > best) {
      best = sep;
      face = i;
    }
  }
  lm2_v2_f64 ab = {-axis.x / length, -axis.y / length};
  lm2_v2_f64 side[2] = {
      { ab.y, -ab.x},
      {-ab.y,  ab.x}
  };
  for (int j = 0; j < 2; ++j) {
    double sep = INFINITY;
    for (size_t i = 0; i < polygon.vertex_count; ++i)
      sep = fmin(sep, _lm2_cap_poly_dot_f64(vertices[i], side[j]));
    if (sep > best) {
      best = sep;
      code = j + 1;
    }
  }
  lm2_v2_f64 seg[2], ref_a, ref_b;
  if (code == 0) {
    seg[0] = zero;
    seg[1] = axis;
    ref_a = vertices[face];
    ref_b = vertices[(face + 1) % polygon.vertex_count];
  } else {
    lm2_v2_f64 n = side[code - 1];
    double min_dot = INFINITY;
    size_t incident = 0;
    for (size_t i = 0; i < polygon.vertex_count; ++i) {
      lm2_v2_f64 e = _lm2_cap_poly_sub_f64(vertices[(i + 1) % polygon.vertex_count], vertices[i]);
      double len = hypot(e.x, e.y);
      lm2_v2_f64 en = {e.y / len, -e.x / len};
      double dot = _lm2_cap_poly_dot_f64(n, en);
      if (dot < min_dot) {
        min_dot = dot;
        incident = i;
      }
    }
    seg[0] = vertices[incident];
    seg[1] = vertices[(incident + 1) % polygon.vertex_count];
    ref_a = code == 1 ? axis : zero;
    ref_b = code == 1 ? zero : axis;
  }
  lm2_v2_f64 ref = _lm2_cap_poly_sub_f64(ref_b, ref_a);
  double ref_len = hypot(ref.x, ref.y);
  lm2_v2_f64 tangent = {ref.x / ref_len, ref.y / ref_len};
  lm2_v2_f64 neg_tangent = {-tangent.x, -tangent.y};
  if (_lm2_cap_poly_clip_f64(seg, ref_a, neg_tangent) < 2 ||
      _lm2_cap_poly_clip_f64(seg, ref_b, tangent) < 2) return;
  lm2_v2_f64 normal = {tangent.y, -tangent.x};
  for (int i = 0; i < 2; ++i) {
    double depth = -_lm2_cap_poly_dot_f64(_lm2_cap_poly_sub_f64(seg[i], ref_a), normal);
    // A clipped point exactly on the reference line can round slightly to
    // either side, especially when the dot product is contracted into an FMA.
    double scale = fmax(fmax(fabs(seg[i].x), fabs(seg[i].y)), fmax(fabs(ref_a.x), fabs(ref_a.y)));
    double tolerance = 16.0 * DBL_EPSILON * scale;
    if (depth >= -tolerance) {
      int k = out_manifold->count++;
      out_manifold->depths[k] = fmax(depth, 0.0) + capsule.radius;
      out_manifold->contact_points[k] = (lm2_v2_f64) {capsule.start.x + seg[i].x, capsule.start.y + seg[i].y};
    }
  }
  if (out_manifold->count) out_manifold->normal = code == 0 ? (lm2_v2_f64) {-normal.x, -normal.y} : normal;
}

LM2_API void lm2_manifold_polygon_to_polygon_f64(lm2_polygon_f64 a, lm2_polygon_f64 b, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  LM2_ASSERT(a.vertices != NULL && a.vertex_count >= 3 && a.vertex_count <= C2_MAX_POLYGON_VERTS);
  LM2_ASSERT(b.vertices != NULL && b.vertex_count >= 3 && b.vertex_count <= C2_MAX_POLYGON_VERTS);
  _lm2_polygon_manifold_f64(a.vertices, a.vertex_count, b.vertices, b.vertex_count, out_manifold);
}

// =============================================================================
// Manifold Generation - f32
// =============================================================================

LM2_API void lm2_manifold_circle_to_circle_f32(lm2_circle_f32 a, lm2_circle_f32 b, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  *out_manifold = (lm2_manifold_f32) {0};
  float dx = b.center.x - a.center.x;
  float dy = b.center.y - a.center.y;
  float distance = hypotf(dx, dy);
  float radius_sum = a.radius + b.radius;
  if (distance >= radius_sum) return;

  lm2_v2_f32 normal = distance != 0.0f
                          ? (lm2_v2_f32) {dx / distance, dy / distance}
                          : (lm2_v2_f32) {0.0f, 1.0f};
  out_manifold->count = 1;
  out_manifold->depths[0] = radius_sum - distance;
  out_manifold->normal = normal;
  out_manifold->contact_points[0].x = b.center.x - normal.x * b.radius;
  out_manifold->contact_points[0].y = b.center.y - normal.y * b.radius;
}

LM2_API void lm2_manifold_circle_to_aabb_f32(lm2_circle_f32 circle, lm2_r2_f32 aabb, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  *out_manifold = (lm2_manifold_f32) {0};
  float closest_x = fmaxf(aabb.min.x, fminf(circle.center.x, aabb.max.x));
  float closest_y = fmaxf(aabb.min.y, fminf(circle.center.y, aabb.max.y));
  float dx = closest_x - circle.center.x;
  float dy = closest_y - circle.center.y;
  float distance = hypotf(dx, dy);
  if (distance >= circle.radius) return;

  out_manifold->count = 1;
  if (distance > 0.0f) {
    out_manifold->normal = (lm2_v2_f32) {dx / distance, dy / distance};
    out_manifold->depths[0] = circle.radius - distance;
    out_manifold->contact_points[0] = (lm2_v2_f32) {closest_x, closest_y};
  } else {
    float left = circle.center.x - aabb.min.x;
    float right = aabb.max.x - circle.center.x;
    float bottom = circle.center.y - aabb.min.y;
    float top = aabb.max.y - circle.center.y;
    float x_overlap = fminf(left, right);
    float y_overlap = fminf(bottom, top);
    float depth;
    if (x_overlap < y_overlap) {
      depth = x_overlap;
      out_manifold->normal = (lm2_v2_f32) {left < right ? 1.0f : -1.0f, 0.0f};
    } else {
      depth = y_overlap;
      out_manifold->normal = (lm2_v2_f32) {0.0f, bottom < top ? 1.0f : -1.0f};
    }
    out_manifold->depths[0] = circle.radius + depth;
    out_manifold->contact_points[0].x = circle.center.x - out_manifold->normal.x * depth;
    out_manifold->contact_points[0].y = circle.center.y - out_manifold->normal.y * depth;
  }
}

LM2_API void lm2_manifold_circle_to_capsule_f32(lm2_circle_f32 circle, lm2_capsule2_f32 capsule, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m = {0};
  c2CircletoCapsuleManifold(lm2_circle_f32_to_c2(circle), lm2_capsule2_f32_to_c2(capsule), &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_circle_to_polygon_f32(lm2_circle_f32 circle, lm2_polygon_f32 polygon, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m = {0};
  c2Poly poly = lm2_polygon_f32_to_c2(polygon);
  c2CircletoPolyManifold(lm2_circle_f32_to_c2(circle), &poly, NULL, &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_aabb_to_aabb_f32(lm2_r2_f32 a, lm2_r2_f32 b, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m = {0};
  c2AABBtoAABBManifold(lm2_r2_f32_to_c2(a), lm2_r2_f32_to_c2(b), &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
  if (out_manifold->count > 0) {
    if (out_manifold->normal.x != 0.0f) {
      out_manifold->contact_points[0].y = _lm2_interval_midpoint_f32(fmaxf(a.min.y, b.min.y), fminf(a.max.y, b.max.y));
    } else {
      out_manifold->contact_points[0].x = _lm2_interval_midpoint_f32(fmaxf(a.min.x, b.min.x), fminf(a.max.x, b.max.x));
    }
  }
}

LM2_API void lm2_manifold_aabb_to_capsule_f32(lm2_r2_f32 aabb, lm2_capsule2_f32 capsule, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m = {0};
  c2AABBtoCapsuleManifold(lm2_r2_f32_to_c2(aabb), lm2_capsule2_f32_to_c2(capsule), &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_aabb_to_polygon_f32(lm2_r2_f32 aabb, lm2_polygon_f32 polygon, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m = {0};
  c2Poly poly = lm2_polygon_f32_to_c2(polygon);
  c2AABBtoPolyManifold(lm2_r2_f32_to_c2(aabb), &poly, NULL, &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_capsule_to_capsule_f32(lm2_capsule2_f32 a, lm2_capsule2_f32 b, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m = {0};
  c2CapsuletoCapsuleManifold(lm2_capsule2_f32_to_c2(a), lm2_capsule2_f32_to_c2(b), &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_capsule_to_polygon_f32(lm2_capsule2_f32 capsule, lm2_polygon_f32 polygon, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m = {0};
  c2Poly poly = lm2_polygon_f32_to_c2(polygon);
  c2CapsuletoPolyManifold(lm2_capsule2_f32_to_c2(capsule), &poly, NULL, &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_polygon_to_polygon_f32(lm2_polygon_f32 a, lm2_polygon_f32 b, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m = {0};
  c2Poly poly_a = lm2_polygon_f32_to_c2(a);
  c2Poly poly_b = lm2_polygon_f32_to_c2(b);
  c2PolytoPolyManifold(&poly_a, NULL, &poly_b, NULL, &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

// =============================================================================
// Convex Hull Generation
// =============================================================================

static int _lm2_hull_compare_f64(const void* lhs, const void* rhs) {
  const lm2_v2_f64* a = lhs;
  const lm2_v2_f64* b = rhs;
  if (a->x < b->x) return -1;
  if (a->x > b->x) return 1;
  if (a->y < b->y) return -1;
  if (a->y > b->y) return 1;
  return 0;
}

static long double _lm2_hull_turn_f64(lm2_v2_f64 a, lm2_v2_f64 b, lm2_v2_f64 c) {
  long double abx = (long double)b.x - a.x;
  long double aby = (long double)b.y - a.y;
  long double acx = (long double)c.x - a.x;
  long double acy = (long double)c.y - a.y;
  // Some platforms give long double the same range as double. Avoid overflow
  // in differences between finite coordinates of opposite signs there.
  if (!isfinite(abx) || !isfinite(aby) || !isfinite(acx) || !isfinite(acy)) {
    abx = (long double)b.x * 0.5L - (long double)a.x * 0.5L;
    aby = (long double)b.y * 0.5L - (long double)a.y * 0.5L;
    acx = (long double)c.x * 0.5L - (long double)a.x * 0.5L;
    acy = (long double)c.y * 0.5L - (long double)a.y * 0.5L;
  }
  // The turn depends only on the sign, so scale each vector by a power of
  // two to keep products in range without rounding the dominant component.
  const long double ab_scale = fmaxl(fabsl(abx), fabsl(aby));
  const long double ac_scale = fmaxl(fabsl(acx), fabsl(acy));
  if (ab_scale == 0.0L || ac_scale == 0.0L) return 0.0L;
  int ab_exponent, ac_exponent;
  (void)frexpl(ab_scale, &ab_exponent);
  (void)frexpl(ac_scale, &ac_exponent);
  return scalbnl(abx, -ab_exponent) * scalbnl(acy, -ac_exponent) -
         scalbnl(aby, -ab_exponent) * scalbnl(acx, -ac_exponent);
}

LM2_API int lm2_convex_hull_f64(lm2_v2_f64* points, int point_count, lm2_v2_f64* out_vertices, int max_vertices) {
  LM2_ASSERT(points != NULL);
  LM2_ASSERT(out_vertices != NULL);
  LM2_ASSERT(point_count >= 0);
  LM2_ASSERT(max_vertices >= 0);

  if (point_count <= 2 || max_vertices <= 0) return 0;
  const size_t count = (size_t)point_count;
  LM2_ASSERT(count <= SIZE_MAX / (2 * sizeof(lm2_v2_f64)));
  if (count > SIZE_MAX / (2 * sizeof(lm2_v2_f64))) return 0;

  lm2_v2_f64* sorted = malloc(count * sizeof(*sorted));
  lm2_v2_f64* hull = malloc(2 * count * sizeof(*hull));
  if (sorted == NULL || hull == NULL) {
    free(sorted);
    free(hull);
    LM2_ASSERT(false);
    return 0;
  }
  for (size_t i = 0; i < count; ++i) {
    LM2_ASSERT(isfinite(points[i].x) && isfinite(points[i].y));
    if (!isfinite(points[i].x) || !isfinite(points[i].y)) {
      free(sorted);
      free(hull);
      return 0;
    }
    sorted[i] = points[i];
  }
  qsort(sorted, count, sizeof(*sorted), _lm2_hull_compare_f64);
  size_t unique = 0;
  for (size_t i = 0; i < count; ++i) {
    if (unique == 0 || sorted[i].x != sorted[unique - 1].x || sorted[i].y != sorted[unique - 1].y) {
      sorted[unique++] = sorted[i];
    }
  }

  size_t n = 0;
  for (size_t i = 0; i < unique; ++i) {
    while (n >= 2 && _lm2_hull_turn_f64(hull[n - 2], hull[n - 1], sorted[i]) <= 0.0L) --n;
    hull[n++] = sorted[i];
  }
  if (unique > 1) {
    const size_t upper_start = n + 1;
    for (size_t i = unique - 1; i-- > 0;) {
      while (n >= upper_start && _lm2_hull_turn_f64(hull[n - 2], hull[n - 1], sorted[i]) <= 0.0L) --n;
      hull[n++] = sorted[i];
    }
    --n;  // The first point is repeated at the end.
  }

  // Preserve the backend's conventional first vertex (rightmost, then lowest).
  size_t first = 0;
  for (size_t i = 1; i < n; ++i) {
    if (hull[i].x > hull[first].x || (hull[i].x == hull[first].x && hull[i].y < hull[first].y)) first = i;
  }
  const size_t result_count = n < (size_t)max_vertices ? n : (size_t)max_vertices;
  for (size_t i = 0; i < result_count; ++i) out_vertices[i] = hull[(first + i) % n];
  free(hull);
  free(sorted);
  return (int)result_count;
}

LM2_API int lm2_convex_hull_f32(lm2_v2_f32* points, int point_count, lm2_v2_f32* out_vertices, int max_vertices) {
  LM2_ASSERT(points != NULL);
  LM2_ASSERT(out_vertices != NULL);
  LM2_ASSERT(point_count >= 0);
  LM2_ASSERT(max_vertices >= 0);

  if (point_count == 0) {
    return 0;
  }

  // Convert to c2v
  c2v* temp = (c2v*)malloc(sizeof(c2v) * (size_t)point_count);
  LM2_ASSERT(temp != NULL);

  for (int i = 0; i < point_count; ++i) {
    temp[i] = lm22_f32_to_c2v(points[i]);
  }

  // Compute hull
  int hull_count = c2Hull(temp, point_count);

  // Convert back (up to max_vertices)
  int result_count = hull_count < max_vertices ? hull_count : max_vertices;
  for (int i = 0; i < result_count; ++i) {
    out_vertices[i] = c2v_to_lm22_f32(temp[i]);
  }

  free(temp);
  return result_count;
}

LM2_API void lm2_compute_normals_f64(lm2_v2_f64* vertices, lm2_v2_f64* out_normals, int vertex_count) {
  LM2_ASSERT(vertices != NULL);
  LM2_ASSERT(out_normals != NULL);
  LM2_ASSERT(vertex_count >= 0);

  if (vertex_count == 0) {
    return;
  }

  LM2_ASSERT((size_t)vertex_count <= SIZE_MAX / sizeof(*out_normals));
  lm2_v2_f64* temp_norms = malloc(sizeof(*temp_norms) * (size_t)vertex_count);
  LM2_ASSERT(temp_norms != NULL);

  // A temporary output also permits the input and output arrays to overlap.
  for (int i = 0; i < vertex_count; ++i) {
    const int next = i + 1 < vertex_count ? i + 1 : 0;
    const double dx = vertices[next].x - vertices[i].x;
    const double dy = vertices[next].y - vertices[i].y;
    const double length = hypot(dx, dy);
    temp_norms[i].x = length > 0.0 ? dy / length : 0.0;
    temp_norms[i].y = length > 0.0 ? -dx / length : 0.0;
  }
  memcpy(out_normals, temp_norms, sizeof(*temp_norms) * (size_t)vertex_count);
  free(temp_norms);
}

LM2_API void lm2_compute_normals_f32(lm2_v2_f32* vertices, lm2_v2_f32* out_normals, int vertex_count) {
  LM2_ASSERT(vertices != NULL);
  LM2_ASSERT(out_normals != NULL);
  LM2_ASSERT(vertex_count >= 0);

  if (vertex_count == 0) {
    return;
  }

  // Convert to c2v
  c2v* temp_verts = (c2v*)malloc(sizeof(c2v) * (size_t)vertex_count);
  c2v* temp_norms = (c2v*)malloc(sizeof(c2v) * (size_t)vertex_count);
  LM2_ASSERT(temp_verts != NULL && temp_norms != NULL);

  for (int i = 0; i < vertex_count; ++i) {
    temp_verts[i] = lm22_f32_to_c2v(vertices[i]);
  }

  // Compute normals
  c2Norms(temp_verts, temp_norms, vertex_count);

  // Convert back
  for (int i = 0; i < vertex_count; ++i) {
    out_normals[i] = c2v_to_lm22_f32(temp_norms[i]);
  }

  free(temp_verts);
  free(temp_norms);
}

LM2_API void lm2_make_convex_polygon_f64(lm2_polygon_f64* polygon, lm2_v2_f64* out_normals) {
  LM2_ASSERT(polygon != NULL);
  LM2_ASSERT(polygon->vertices != NULL);
  LM2_ASSERT(out_normals != NULL);

  LM2_ASSERT(polygon->vertex_count <= INT_MAX);
  if (polygon->vertex_count > INT_MAX) return;
  const int count = (int)polygon->vertex_count;
  const int hull_count = lm2_convex_hull_f64(polygon->vertices, count, polygon->vertices, count);
  polygon->vertex_count = (size_t)hull_count;
  if (hull_count > 0) lm2_compute_normals_f64(polygon->vertices, out_normals, hull_count);
}

LM2_API void lm2_make_convex_polygon_f32(lm2_polygon_f32* polygon, lm2_v2_f32* out_normals) {
  LM2_ASSERT(polygon != NULL);
  LM2_ASSERT(polygon->vertices != NULL);
  LM2_ASSERT(out_normals != NULL);

  // Convert to c2v
  c2v* temp_verts = (c2v*)malloc(sizeof(c2v) * polygon->vertex_count);
  c2v* temp_norms = (c2v*)malloc(sizeof(c2v) * polygon->vertex_count);
  LM2_ASSERT(temp_verts != NULL && temp_norms != NULL);

  for (size_t i = 0; i < polygon->vertex_count; ++i) {
    temp_verts[i] = lm22_f32_to_c2v(polygon->vertices[i]);
  }

  // Compute hull
  int hull_count = c2Hull(temp_verts, (int)polygon->vertex_count);

  // Compute normals
  c2Norms(temp_verts, temp_norms, hull_count);

  // Convert back
  for (int i = 0; i < hull_count; ++i) {
    polygon->vertices[i] = c2v_to_lm22_f32(temp_verts[i]);
    out_normals[i] = c2v_to_lm22_f32(temp_norms[i]);
  }

  polygon->vertex_count = (size_t)hull_count;

  free(temp_verts);
  free(temp_norms);
}

// =============================================================================
// Triangle Collision Detection - f64
// =============================================================================

LM2_API bool lm2_collide_triangle_to_triangle_f64(const lm2_triangle2_f64 a, const lm2_triangle2_f64 b) {
  return _lm2_convex_overlap_f64(a, 3, b, 3);
}

LM2_API bool lm2_collide_triangle_to_circle_f64(const lm2_triangle2_f64 tri, lm2_circle_f64 circle) {
  return _lm2_circle_convex_f64(circle, tri, 3);
}

LM2_API bool lm2_collide_triangle_to_aabb_f64(const lm2_triangle2_f64 tri, lm2_r2_f64 aabb) {
  return _lm2_box_convex_f64(aabb, tri, 3);
}

LM2_API bool lm2_collide_triangle_to_capsule_f64(const lm2_triangle2_f64 tri, lm2_capsule2_f64 capsule) {
  return _lm2_capsule_convex_f64(capsule, tri, 3);
}

LM2_API bool lm2_collide_triangle_to_polygon_f64(const lm2_triangle2_f64 tri, lm2_polygon_f64 polygon) {
  LM2_ASSERT(polygon.vertices != NULL && polygon.vertex_count >= 3 && polygon.vertex_count <= C2_MAX_POLYGON_VERTS);
  return _lm2_convex_overlap_f64(tri, 3, polygon.vertices, polygon.vertex_count);
}

// =============================================================================
// Triangle Collision Detection - f32
// =============================================================================

LM2_API bool lm2_collide_triangle_to_triangle_f32(const lm2_triangle2_f32 a, const lm2_triangle2_f32 b) {
  c2Poly poly_a = lm2_triangle2_f32_to_c2(a);
  c2Poly poly_b = lm2_triangle2_f32_to_c2(b);
  return c2PolytoPoly(&poly_a, NULL, &poly_b, NULL) != 0;
}

LM2_API bool lm2_collide_triangle_to_circle_f32(const lm2_triangle2_f32 tri, lm2_circle_f32 circle) {
  c2Poly poly = lm2_triangle2_f32_to_c2(tri);
  return c2CircletoPoly(lm2_circle_f32_to_c2(circle), &poly, NULL) != 0;
}

LM2_API bool lm2_collide_triangle_to_aabb_f32(const lm2_triangle2_f32 tri, lm2_r2_f32 aabb) {
  c2Poly poly = lm2_triangle2_f32_to_c2(tri);
  return c2AABBtoPoly(lm2_r2_f32_to_c2(aabb), &poly, NULL) != 0;
}

LM2_API bool lm2_collide_triangle_to_capsule_f32(const lm2_triangle2_f32 tri, lm2_capsule2_f32 capsule) {
  c2Poly poly = lm2_triangle2_f32_to_c2(tri);
  return c2CapsuletoPoly(lm2_capsule2_f32_to_c2(capsule), &poly, NULL) != 0;
}

LM2_API bool lm2_collide_triangle_to_polygon_f32(const lm2_triangle2_f32 tri, lm2_polygon_f32 polygon) {
  c2Poly poly_tri = lm2_triangle2_f32_to_c2(tri);
  c2Poly poly = lm2_polygon_f32_to_c2(polygon);
  return c2PolytoPoly(&poly_tri, NULL, &poly, NULL) != 0;
}

// =============================================================================
// Triangle Manifold Generation - f64
// =============================================================================

LM2_API void lm2_manifold_triangle_to_triangle_f64(const lm2_triangle2_f64 a, const lm2_triangle2_f64 b, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  _lm2_polygon_manifold_f64(a, 3, b, 3, out_manifold);
}

LM2_API void lm2_manifold_triangle_to_circle_f64(const lm2_triangle2_f64 tri, lm2_circle_f64 circle, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  lm2_v2_f64 vertices[3] = {tri[0], tri[1], tri[2]};
  lm2_polygon_f64 polygon = {vertices, 3};
  lm2_manifold_circle_to_polygon_f64(circle, polygon, out_manifold);
  if (out_manifold->count > 0) {
    out_manifold->normal.x = -out_manifold->normal.x;
    out_manifold->normal.y = -out_manifold->normal.y;
  }
}

LM2_API void lm2_manifold_triangle_to_aabb_f64(const lm2_triangle2_f64 tri, lm2_r2_f64 aabb, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  lm2_v2_f64 box[4];
  _lm2_box_vertices_f64(aabb, box);
  _lm2_polygon_manifold_f64(box, 4, tri, 3, out_manifold);
  if (out_manifold->count > 0) {
    out_manifold->normal.x = -out_manifold->normal.x;
    out_manifold->normal.y = -out_manifold->normal.y;
  }
}

LM2_API void lm2_manifold_triangle_to_capsule_f64(const lm2_triangle2_f64 tri, lm2_capsule2_f64 capsule, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  lm2_v2_f64 vertices[3] = {tri[0], tri[1], tri[2]};
  lm2_polygon_f64 polygon = {vertices, 3};
  lm2_manifold_capsule_to_polygon_f64(capsule, polygon, out_manifold);
  if (out_manifold->count > 0) {
    out_manifold->normal.x = -out_manifold->normal.x;
    out_manifold->normal.y = -out_manifold->normal.y;
  }
}

LM2_API void lm2_manifold_triangle_to_polygon_f64(const lm2_triangle2_f64 tri, lm2_polygon_f64 polygon, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  LM2_ASSERT(polygon.vertices != NULL && polygon.vertex_count >= 3 && polygon.vertex_count <= C2_MAX_POLYGON_VERTS);
  _lm2_polygon_manifold_f64(tri, 3, polygon.vertices, polygon.vertex_count, out_manifold);
}

// =============================================================================
// Triangle Manifold Generation - f32
// =============================================================================

LM2_API void lm2_manifold_triangle_to_triangle_f32(const lm2_triangle2_f32 a, const lm2_triangle2_f32 b, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m = {0};
  c2Poly poly_a = lm2_triangle2_f32_to_c2(a);
  c2Poly poly_b = lm2_triangle2_f32_to_c2(b);
  c2PolytoPolyManifold(&poly_a, NULL, &poly_b, NULL, &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_triangle_to_circle_f32(const lm2_triangle2_f32 tri, lm2_circle_f32 circle, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m = {0};
  c2Poly poly = lm2_triangle2_f32_to_c2(tri);
  c2CircletoPolyManifold(lm2_circle_f32_to_c2(circle), &poly, NULL, &m);
  if (m.count > 0) {
    m.n.x = -m.n.x;
    m.n.y = -m.n.y;
  }
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_triangle_to_aabb_f32(const lm2_triangle2_f32 tri, lm2_r2_f32 aabb, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m = {0};
  c2Poly poly = lm2_triangle2_f32_to_c2(tri);
  c2AABBtoPolyManifold(lm2_r2_f32_to_c2(aabb), &poly, NULL, &m);
  if (m.count > 0) {
    m.n.x = -m.n.x;
    m.n.y = -m.n.y;
  }
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_triangle_to_capsule_f32(const lm2_triangle2_f32 tri, lm2_capsule2_f32 capsule, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m = {0};
  c2Poly poly = lm2_triangle2_f32_to_c2(tri);
  c2CapsuletoPolyManifold(lm2_capsule2_f32_to_c2(capsule), &poly, NULL, &m);
  if (m.count > 0) {
    m.n.x = -m.n.x;
    m.n.y = -m.n.y;
  }
  c2_manifold_to_lm2_f32(m, out_manifold);
}

LM2_API void lm2_manifold_triangle_to_polygon_f32(const lm2_triangle2_f32 tri, lm2_polygon_f32 polygon, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  c2Manifold m = {0};
  c2Poly poly_tri = lm2_triangle2_f32_to_c2(tri);
  c2Poly poly = lm2_polygon_f32_to_c2(polygon);
  c2PolytoPolyManifold(&poly_tri, NULL, &poly, NULL, &m);
  c2_manifold_to_lm2_f32(m, out_manifold);
}

// =============================================================================
// Plane Manifold Generation - f64
// =============================================================================

LM2_API void lm2_manifold_circle_to_plane_f64(lm2_circle_f64 circle, lm2_plane2_f64 plane, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  *out_manifold = (lm2_manifold_f64) {0};

  // Calculate signed distance from circle center to plane
  double dist_to_center = lm2_sub_f64(lm2_v2_dot_f64(circle.center, plane.normal), plane.distance);
  double penetration = lm2_sub_f64(circle.radius, lm2_abs_f64(dist_to_center));

  if (lm2_sub_f64(penetration, 0.0) <= 0.0) {
    // No collision
    out_manifold->count = 0;
    return;
  }

  // One contact point: circle center projected onto plane
  out_manifold->count = 1;
  out_manifold->depths[0] = penetration;
  out_manifold->normal = plane.normal;

  // Contact point is on the plane surface, in the direction of the circle center
  lm2_v2_f64 scaled_normal = lm2_v2_mul_s_f64(plane.normal, dist_to_center);
  out_manifold->contact_points[0] = lm2_v2_sub_f64(circle.center, scaled_normal);
}

LM2_API void lm2_manifold_capsule_to_plane_f64(lm2_capsule2_f64 capsule, lm2_plane2_f64 plane, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  *out_manifold = (lm2_manifold_f64) {0};

  // Check both endpoints of the capsule
  double dist_start = lm2_sub_f64(lm2_v2_dot_f64(capsule.start, plane.normal), plane.distance);
  double dist_end = lm2_sub_f64(lm2_v2_dot_f64(capsule.end, plane.normal), plane.distance);

  double pen_start = lm2_sub_f64(capsule.radius, lm2_abs_f64(dist_start));
  double pen_end = lm2_sub_f64(capsule.radius, lm2_abs_f64(dist_end));

  out_manifold->count = 0;

  if (lm2_sub_f64(pen_start, 0.0) > 0.0) {
    out_manifold->depths[out_manifold->count] = pen_start;
    lm2_v2_f64 scaled_normal = lm2_v2_mul_s_f64(plane.normal, dist_start);
    out_manifold->contact_points[out_manifold->count] = lm2_v2_sub_f64(capsule.start, scaled_normal);
    out_manifold->count = lm2_add_i32(out_manifold->count, 1);
    out_manifold->normal = plane.normal;
  }

  if (lm2_sub_f64(pen_end, 0.0) > 0.0 && out_manifold->count < 2) {
    out_manifold->depths[out_manifold->count] = pen_end;
    lm2_v2_f64 scaled_normal = lm2_v2_mul_s_f64(plane.normal, dist_end);
    out_manifold->contact_points[out_manifold->count] = lm2_v2_sub_f64(capsule.end, scaled_normal);
    out_manifold->count = lm2_add_i32(out_manifold->count, 1);
    out_manifold->normal = plane.normal;
  }
}

LM2_API void lm2_manifold_aabb_to_plane_f64(lm2_r2_f64 aabb, lm2_plane2_f64 plane, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  *out_manifold = (lm2_manifold_f64) {0};

  // Get AABB corners
  lm2_v2_f64 corners[4];
  corners[0] = aabb.min;
  corners[1] = (lm2_v2_f64) {aabb.max.x, aabb.min.y};
  corners[2] = aabb.max;
  corners[3] = (lm2_v2_f64) {aabb.min.x, aabb.max.y};

  out_manifold->count = 0;

  // Check each corner
  for (int i = 0; i < 4 && out_manifold->count < 2; i = lm2_add_i32(i, 1)) {
    double dist = lm2_sub_f64(lm2_v2_dot_f64(corners[i], plane.normal), plane.distance);
    double penetration = lm2_mul_f64(-1.0, dist);  // Negative distance means penetration

    if (lm2_sub_f64(penetration, 0.0) > 0.0) {
      out_manifold->depths[out_manifold->count] = penetration;
      out_manifold->contact_points[out_manifold->count] = corners[i];
      out_manifold->count = lm2_add_i32(out_manifold->count, 1);
      out_manifold->normal = plane.normal;
    }
  }
}

LM2_API void lm2_manifold_triangle_to_plane_f64(const lm2_triangle2_f64 tri, lm2_plane2_f64 plane, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  *out_manifold = (lm2_manifold_f64) {0};

  lm2_v2_f64 verts[3] = {tri[0], tri[1], tri[2]};

  out_manifold->count = 0;

  // Check each vertex
  for (int i = 0; i < 3 && out_manifold->count < 2; i = lm2_add_i32(i, 1)) {
    double dist = lm2_sub_f64(lm2_v2_dot_f64(verts[i], plane.normal), plane.distance);
    double penetration = lm2_mul_f64(-1.0, dist);

    if (lm2_sub_f64(penetration, 0.0) > 0.0) {
      out_manifold->depths[out_manifold->count] = penetration;
      out_manifold->contact_points[out_manifold->count] = verts[i];
      out_manifold->count = lm2_add_i32(out_manifold->count, 1);
      out_manifold->normal = plane.normal;
    }
  }
}

LM2_API void lm2_manifold_polygon_to_plane_f64(lm2_polygon_f64 polygon, lm2_plane2_f64 plane, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  *out_manifold = (lm2_manifold_f64) {0};
  LM2_ASSERT(polygon.vertices != NULL);

  out_manifold->count = 0;

  // Check each vertex
  for (size_t i = 0; i < polygon.vertex_count && out_manifold->count < 2; i++) {
    double dist = lm2_sub_f64(lm2_v2_dot_f64(polygon.vertices[i], plane.normal), plane.distance);
    double penetration = lm2_mul_f64(-1.0, dist);

    if (lm2_sub_f64(penetration, 0.0) > 0.0) {
      out_manifold->depths[out_manifold->count] = penetration;
      out_manifold->contact_points[out_manifold->count] = polygon.vertices[i];
      out_manifold->count = lm2_add_i32(out_manifold->count, 1);
      out_manifold->normal = plane.normal;
    }
  }
}

// =============================================================================
// Plane Manifold Generation - f32
// =============================================================================

LM2_API void lm2_manifold_circle_to_plane_f32(lm2_circle_f32 circle, lm2_plane2_f32 plane, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  *out_manifold = (lm2_manifold_f32) {0};

  float dist_to_center = lm2_sub_f32(lm2_v2_dot_f32(circle.center, plane.normal), plane.distance);
  float penetration = lm2_sub_f32(circle.radius, lm2_abs_f32(dist_to_center));

  if (lm2_sub_f32(penetration, 0.0f) <= 0.0f) {
    out_manifold->count = 0;
    return;
  }

  out_manifold->count = 1;
  out_manifold->depths[0] = penetration;
  out_manifold->normal = plane.normal;

  lm2_v2_f32 scaled_normal = lm2_v2_mul_s_f32(plane.normal, dist_to_center);
  out_manifold->contact_points[0] = lm2_v2_sub_f32(circle.center, scaled_normal);
}

LM2_API void lm2_manifold_capsule_to_plane_f32(lm2_capsule2_f32 capsule, lm2_plane2_f32 plane, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  *out_manifold = (lm2_manifold_f32) {0};

  float dist_start = lm2_sub_f32(lm2_v2_dot_f32(capsule.start, plane.normal), plane.distance);
  float dist_end = lm2_sub_f32(lm2_v2_dot_f32(capsule.end, plane.normal), plane.distance);

  float pen_start = lm2_sub_f32(capsule.radius, lm2_abs_f32(dist_start));
  float pen_end = lm2_sub_f32(capsule.radius, lm2_abs_f32(dist_end));

  out_manifold->count = 0;

  if (lm2_sub_f32(pen_start, 0.0f) > 0.0f) {
    out_manifold->depths[out_manifold->count] = pen_start;
    lm2_v2_f32 scaled_normal = lm2_v2_mul_s_f32(plane.normal, dist_start);
    out_manifold->contact_points[out_manifold->count] = lm2_v2_sub_f32(capsule.start, scaled_normal);
    out_manifold->count = lm2_add_i32(out_manifold->count, 1);
    out_manifold->normal = plane.normal;
  }

  if (lm2_sub_f32(pen_end, 0.0f) > 0.0f && out_manifold->count < 2) {
    out_manifold->depths[out_manifold->count] = pen_end;
    lm2_v2_f32 scaled_normal = lm2_v2_mul_s_f32(plane.normal, dist_end);
    out_manifold->contact_points[out_manifold->count] = lm2_v2_sub_f32(capsule.end, scaled_normal);
    out_manifold->count = lm2_add_i32(out_manifold->count, 1);
    out_manifold->normal = plane.normal;
  }
}

LM2_API void lm2_manifold_aabb_to_plane_f32(lm2_r2_f32 aabb, lm2_plane2_f32 plane, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  *out_manifold = (lm2_manifold_f32) {0};

  lm2_v2_f32 corners[4];
  corners[0] = aabb.min;
  corners[1] = (lm2_v2_f32) {aabb.max.x, aabb.min.y};
  corners[2] = aabb.max;
  corners[3] = (lm2_v2_f32) {aabb.min.x, aabb.max.y};

  out_manifold->count = 0;

  for (int i = 0; i < 4 && out_manifold->count < 2; i = lm2_add_i32(i, 1)) {
    float dist = lm2_sub_f32(lm2_v2_dot_f32(corners[i], plane.normal), plane.distance);
    float penetration = lm2_mul_f32(-1.0f, dist);

    if (lm2_sub_f32(penetration, 0.0f) > 0.0f) {
      out_manifold->depths[out_manifold->count] = penetration;
      out_manifold->contact_points[out_manifold->count] = corners[i];
      out_manifold->count = lm2_add_i32(out_manifold->count, 1);
      out_manifold->normal = plane.normal;
    }
  }
}

LM2_API void lm2_manifold_triangle_to_plane_f32(const lm2_triangle2_f32 tri, lm2_plane2_f32 plane, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  *out_manifold = (lm2_manifold_f32) {0};

  lm2_v2_f32 verts[3] = {tri[0], tri[1], tri[2]};

  out_manifold->count = 0;

  for (int i = 0; i < 3 && out_manifold->count < 2; i = lm2_add_i32(i, 1)) {
    float dist = lm2_sub_f32(lm2_v2_dot_f32(verts[i], plane.normal), plane.distance);
    float penetration = lm2_mul_f32(-1.0f, dist);

    if (lm2_sub_f32(penetration, 0.0f) > 0.0f) {
      out_manifold->depths[out_manifold->count] = penetration;
      out_manifold->contact_points[out_manifold->count] = verts[i];
      out_manifold->count = lm2_add_i32(out_manifold->count, 1);
      out_manifold->normal = plane.normal;
    }
  }
}

LM2_API void lm2_manifold_polygon_to_plane_f32(lm2_polygon_f32 polygon, lm2_plane2_f32 plane, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  *out_manifold = (lm2_manifold_f32) {0};
  LM2_ASSERT(polygon.vertices != NULL);

  out_manifold->count = 0;

  for (size_t i = 0; i < polygon.vertex_count && out_manifold->count < 2; i++) {
    float dist = lm2_sub_f32(lm2_v2_dot_f32(polygon.vertices[i], plane.normal), plane.distance);
    float penetration = lm2_mul_f32(-1.0f, dist);

    if (lm2_sub_f32(penetration, 0.0f) > 0.0f) {
      out_manifold->depths[out_manifold->count] = penetration;
      out_manifold->contact_points[out_manifold->count] = polygon.vertices[i];
      out_manifold->count = lm2_add_i32(out_manifold->count, 1);
      out_manifold->normal = plane.normal;
    }
  }
}

// =============================================================================
// Generic Shape Manifold Generation - f64
// =============================================================================

LM2_API void lm2_manifold_shape_to_shape_f64(lm2_shape2_f64 shape_a, lm2_shape2_f64 shape_b, lm2_manifold_f64* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  *out_manifold = (lm2_manifold_f64) {0};
  LM2_ASSERT(shape_a.data != NULL);
  LM2_ASSERT(shape_b.data != NULL);

  // Initialize manifold to no collision
  out_manifold->count = 0;

  // Dispatch based on shape types
  switch (shape_a.type) {
    case LM2_SHAPE2_CIRCLE: {
      lm2_circle_f64* circle = (lm2_circle_f64*)shape_a.data;
      switch (shape_b.type) {
        case LM2_SHAPE2_CIRCLE:
          lm2_manifold_circle_to_circle_f64(*circle, *(lm2_circle_f64*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_CAPSULE:
          lm2_manifold_circle_to_capsule_f64(*circle, *(lm2_capsule2_f64*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_AABB2: {
          lm2_aabb2_f64* rect = (lm2_aabb2_f64*)shape_b.data;
          lm2_manifold_circle_to_aabb_f64(*circle, *rect, out_manifold);
          break;
        }
        case LM2_SHAPE2_TRIANGLE:
          lm2_manifold_triangle_to_circle_f64(*(lm2_triangle2_f64*)shape_b.data, *circle, out_manifold);
          // Flip normal since we swapped order
          out_manifold->normal = lm2_v2_mul_s_f64(out_manifold->normal, -1.0);
          break;
        case LM2_SHAPE2_POLYGON:
          lm2_manifold_circle_to_polygon_f64(*circle, *(lm2_polygon_f64*)shape_b.data, out_manifold);
          break;
        default:
          break;
      }
      break;
    }

    case LM2_SHAPE2_CAPSULE: {
      lm2_capsule2_f64* capsule = (lm2_capsule2_f64*)shape_a.data;
      switch (shape_b.type) {
        case LM2_SHAPE2_CIRCLE:
          lm2_manifold_circle_to_capsule_f64(*(lm2_circle_f64*)shape_b.data, *capsule, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f64(out_manifold->normal, -1.0);
          break;
        case LM2_SHAPE2_CAPSULE:
          lm2_manifold_capsule_to_capsule_f64(*capsule, *(lm2_capsule2_f64*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_AABB2: {
          lm2_aabb2_f64* rect = (lm2_aabb2_f64*)shape_b.data;
          lm2_manifold_aabb_to_capsule_f64(*rect, *capsule, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f64(out_manifold->normal, -1.0);
          break;
        }
        case LM2_SHAPE2_TRIANGLE:
          lm2_manifold_triangle_to_capsule_f64(*(lm2_triangle2_f64*)shape_b.data, *capsule, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f64(out_manifold->normal, -1.0);
          break;
        case LM2_SHAPE2_POLYGON:
          lm2_manifold_capsule_to_polygon_f64(*capsule, *(lm2_polygon_f64*)shape_b.data, out_manifold);
          break;
        default:
          break;
      }
      break;
    }

    case LM2_SHAPE2_AABB2: {
      lm2_aabb2_f64* rect = (lm2_aabb2_f64*)shape_a.data;
      switch (shape_b.type) {
        case LM2_SHAPE2_CIRCLE:
          lm2_manifold_circle_to_aabb_f64(*(lm2_circle_f64*)shape_b.data, *rect, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f64(out_manifold->normal, -1.0);
          break;
        case LM2_SHAPE2_CAPSULE:
          lm2_manifold_aabb_to_capsule_f64(*rect, *(lm2_capsule2_f64*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_AABB2: {
          lm2_aabb2_f64* rect_b = (lm2_aabb2_f64*)shape_b.data;
          lm2_manifold_aabb_to_aabb_f64(*rect, *rect_b, out_manifold);
          break;
        }
        case LM2_SHAPE2_TRIANGLE:
          lm2_manifold_triangle_to_aabb_f64(*(lm2_triangle2_f64*)shape_b.data, *rect, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f64(out_manifold->normal, -1.0);
          break;
        case LM2_SHAPE2_POLYGON:
          lm2_manifold_aabb_to_polygon_f64(*rect, *(lm2_polygon_f64*)shape_b.data, out_manifold);
          break;
        default:
          break;
      }
      break;
    }

    case LM2_SHAPE2_TRIANGLE: {
      lm2_triangle2_f64* tri = (lm2_triangle2_f64*)shape_a.data;
      switch (shape_b.type) {
        case LM2_SHAPE2_CIRCLE:
          lm2_manifold_triangle_to_circle_f64(*tri, *(lm2_circle_f64*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_CAPSULE:
          lm2_manifold_triangle_to_capsule_f64(*tri, *(lm2_capsule2_f64*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_AABB2: {
          lm2_aabb2_f64* rect = (lm2_aabb2_f64*)shape_b.data;
          lm2_manifold_triangle_to_aabb_f64(*tri, *rect, out_manifold);
          break;
        }
        case LM2_SHAPE2_TRIANGLE:
          lm2_manifold_triangle_to_triangle_f64(*tri, *(lm2_triangle2_f64*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_POLYGON:
          lm2_manifold_triangle_to_polygon_f64(*tri, *(lm2_polygon_f64*)shape_b.data, out_manifold);
          break;
        default:
          break;
      }
      break;
    }

    case LM2_SHAPE2_POLYGON: {
      lm2_polygon_f64* poly = (lm2_polygon_f64*)shape_a.data;
      switch (shape_b.type) {
        case LM2_SHAPE2_CIRCLE:
          lm2_manifold_circle_to_polygon_f64(*(lm2_circle_f64*)shape_b.data, *poly, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f64(out_manifold->normal, -1.0);
          break;
        case LM2_SHAPE2_CAPSULE:
          lm2_manifold_capsule_to_polygon_f64(*(lm2_capsule2_f64*)shape_b.data, *poly, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f64(out_manifold->normal, -1.0);
          break;
        case LM2_SHAPE2_AABB2: {
          lm2_aabb2_f64* rect = (lm2_aabb2_f64*)shape_b.data;
          lm2_manifold_aabb_to_polygon_f64(*rect, *poly, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f64(out_manifold->normal, -1.0);
          break;
        }
        case LM2_SHAPE2_TRIANGLE:
          lm2_manifold_triangle_to_polygon_f64(*(lm2_triangle2_f64*)shape_b.data, *poly, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f64(out_manifold->normal, -1.0);
          break;
        case LM2_SHAPE2_POLYGON:
          lm2_manifold_polygon_to_polygon_f64(*poly, *(lm2_polygon_f64*)shape_b.data, out_manifold);
          break;
        default:
          break;
      }
      break;
    }

    default:
      break;
  }
}

// =============================================================================
// Generic Shape Manifold Generation - f32
// =============================================================================

LM2_API void lm2_manifold_shape_to_shape_f32(lm2_shape2_f32 shape_a, lm2_shape2_f32 shape_b, lm2_manifold_f32* out_manifold) {
  LM2_ASSERT(out_manifold != NULL);
  *out_manifold = (lm2_manifold_f32) {0};
  LM2_ASSERT(shape_a.data != NULL);
  LM2_ASSERT(shape_b.data != NULL);

  out_manifold->count = 0;

  switch (shape_a.type) {
    case LM2_SHAPE2_CIRCLE: {
      lm2_circle_f32* circle = (lm2_circle_f32*)shape_a.data;
      switch (shape_b.type) {
        case LM2_SHAPE2_CIRCLE:
          lm2_manifold_circle_to_circle_f32(*circle, *(lm2_circle_f32*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_CAPSULE:
          lm2_manifold_circle_to_capsule_f32(*circle, *(lm2_capsule2_f32*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_AABB2: {
          lm2_aabb2_f32* rect = (lm2_aabb2_f32*)shape_b.data;
          lm2_manifold_circle_to_aabb_f32(*circle, *rect, out_manifold);
          break;
        }
        case LM2_SHAPE2_TRIANGLE:
          lm2_manifold_triangle_to_circle_f32(*(lm2_triangle2_f32*)shape_b.data, *circle, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f32(out_manifold->normal, -1.0f);
          break;
        case LM2_SHAPE2_POLYGON:
          lm2_manifold_circle_to_polygon_f32(*circle, *(lm2_polygon_f32*)shape_b.data, out_manifold);
          break;
        default:
          break;
      }
      break;
    }

    case LM2_SHAPE2_CAPSULE: {
      lm2_capsule2_f32* capsule = (lm2_capsule2_f32*)shape_a.data;
      switch (shape_b.type) {
        case LM2_SHAPE2_CIRCLE:
          lm2_manifold_circle_to_capsule_f32(*(lm2_circle_f32*)shape_b.data, *capsule, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f32(out_manifold->normal, -1.0f);
          break;
        case LM2_SHAPE2_CAPSULE:
          lm2_manifold_capsule_to_capsule_f32(*capsule, *(lm2_capsule2_f32*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_AABB2: {
          lm2_aabb2_f32* rect = (lm2_aabb2_f32*)shape_b.data;
          lm2_manifold_aabb_to_capsule_f32(*rect, *capsule, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f32(out_manifold->normal, -1.0f);
          break;
        }
        case LM2_SHAPE2_TRIANGLE:
          lm2_manifold_triangle_to_capsule_f32(*(lm2_triangle2_f32*)shape_b.data, *capsule, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f32(out_manifold->normal, -1.0f);
          break;
        case LM2_SHAPE2_POLYGON:
          lm2_manifold_capsule_to_polygon_f32(*capsule, *(lm2_polygon_f32*)shape_b.data, out_manifold);
          break;
        default:
          break;
      }
      break;
    }

    case LM2_SHAPE2_AABB2: {
      lm2_aabb2_f32* rect = (lm2_aabb2_f32*)shape_a.data;
      switch (shape_b.type) {
        case LM2_SHAPE2_CIRCLE:
          lm2_manifold_circle_to_aabb_f32(*(lm2_circle_f32*)shape_b.data, *rect, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f32(out_manifold->normal, -1.0f);
          break;
        case LM2_SHAPE2_CAPSULE:
          lm2_manifold_aabb_to_capsule_f32(*rect, *(lm2_capsule2_f32*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_AABB2: {
          lm2_aabb2_f32* rect_b = (lm2_aabb2_f32*)shape_b.data;
          lm2_manifold_aabb_to_aabb_f32(*rect, *rect_b, out_manifold);
          break;
        }
        case LM2_SHAPE2_TRIANGLE:
          lm2_manifold_triangle_to_aabb_f32(*(lm2_triangle2_f32*)shape_b.data, *rect, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f32(out_manifold->normal, -1.0f);
          break;
        case LM2_SHAPE2_POLYGON:
          lm2_manifold_aabb_to_polygon_f32(*rect, *(lm2_polygon_f32*)shape_b.data, out_manifold);
          break;
        default:
          break;
      }
      break;
    }

    case LM2_SHAPE2_TRIANGLE: {
      lm2_triangle2_f32* tri = (lm2_triangle2_f32*)shape_a.data;
      switch (shape_b.type) {
        case LM2_SHAPE2_CIRCLE:
          lm2_manifold_triangle_to_circle_f32(*tri, *(lm2_circle_f32*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_CAPSULE:
          lm2_manifold_triangle_to_capsule_f32(*tri, *(lm2_capsule2_f32*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_AABB2: {
          lm2_aabb2_f32* rect = (lm2_aabb2_f32*)shape_b.data;
          lm2_manifold_triangle_to_aabb_f32(*tri, *rect, out_manifold);
          break;
        }
        case LM2_SHAPE2_TRIANGLE:
          lm2_manifold_triangle_to_triangle_f32(*tri, *(lm2_triangle2_f32*)shape_b.data, out_manifold);
          break;
        case LM2_SHAPE2_POLYGON:
          lm2_manifold_triangle_to_polygon_f32(*tri, *(lm2_polygon_f32*)shape_b.data, out_manifold);
          break;
        default:
          break;
      }
      break;
    }

    case LM2_SHAPE2_POLYGON: {
      lm2_polygon_f32* poly = (lm2_polygon_f32*)shape_a.data;
      switch (shape_b.type) {
        case LM2_SHAPE2_CIRCLE:
          lm2_manifold_circle_to_polygon_f32(*(lm2_circle_f32*)shape_b.data, *poly, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f32(out_manifold->normal, -1.0f);
          break;
        case LM2_SHAPE2_CAPSULE:
          lm2_manifold_capsule_to_polygon_f32(*(lm2_capsule2_f32*)shape_b.data, *poly, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f32(out_manifold->normal, -1.0f);
          break;
        case LM2_SHAPE2_AABB2: {
          lm2_aabb2_f32* rect = (lm2_aabb2_f32*)shape_b.data;
          lm2_manifold_aabb_to_polygon_f32(*rect, *poly, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f32(out_manifold->normal, -1.0f);
          break;
        }
        case LM2_SHAPE2_TRIANGLE:
          lm2_manifold_triangle_to_polygon_f32(*(lm2_triangle2_f32*)shape_b.data, *poly, out_manifold);
          out_manifold->normal = lm2_v2_mul_s_f32(out_manifold->normal, -1.0f);
          break;
        case LM2_SHAPE2_POLYGON:
          lm2_manifold_polygon_to_polygon_f32(*poly, *(lm2_polygon_f32*)shape_b.data, out_manifold);
          break;
        default:
          break;
      }
      break;
    }

    default:
      break;
  }
}
