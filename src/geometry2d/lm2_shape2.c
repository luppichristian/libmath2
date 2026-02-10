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

#include "lm2/geometry2d/lm2_shape2.h"

// =============================================================================
// Construction Helpers - f64
// =============================================================================

LM2_API lm2_shape2_f64 lm2_shape2_from_circle_f64(lm2_circle_f64* circle) {
  LM2_ASSERT(circle != NULL);
  lm2_shape2_f64 shape;
  shape.type = LM2_SHAPE2_CIRCLE;
  shape.data = circle;
  return shape;
}

LM2_API lm2_shape2_f64 lm2_shape2_from_capsule_f64(lm2_capsule2_f64* capsule) {
  LM2_ASSERT(capsule != NULL);
  lm2_shape2_f64 shape;
  shape.type = LM2_SHAPE2_CAPSULE;
  shape.data = capsule;
  return shape;
}

LM2_API lm2_shape2_f64 lm2_shape2_from_aabb2_f64(lm2_aabb2_f64* aabb2) {
  LM2_ASSERT(aabb2 != NULL);
  lm2_shape2_f64 shape;
  shape.type = LM2_SHAPE2_AABB2;
  shape.data = aabb2;
  return shape;
}

LM2_API lm2_shape2_f64 lm2_shape2_from_triangle_f64(lm2_triangle2_f64* triangle) {
  LM2_ASSERT(triangle != NULL);
  lm2_shape2_f64 shape;
  shape.type = LM2_SHAPE2_TRIANGLE;
  shape.data = triangle;
  return shape;
}

LM2_API lm2_shape2_f64 lm2_shape2_from_polygon_f64(lm2_polygon_f64* polygon) {
  LM2_ASSERT(polygon != NULL);
  lm2_shape2_f64 shape;
  shape.type = LM2_SHAPE2_POLYGON;
  shape.data = polygon;
  return shape;
}

LM2_API lm2_shape2_f64 lm2_shape2_from_edge_f64(lm2_edge2_f64* edge) {
  LM2_ASSERT(edge != NULL);
  lm2_shape2_f64 shape;
  shape.type = LM2_SHAPE2_EDGE;
  shape.data = edge;
  return shape;
}

// =============================================================================
// Construction Helpers - f32
// =============================================================================

LM2_API lm2_shape2_f32 lm2_shape2_from_circle_f32(lm2_circle_f32* circle) {
  LM2_ASSERT(circle != NULL);
  lm2_shape2_f32 shape;
  shape.type = LM2_SHAPE2_CIRCLE;
  shape.data = circle;
  return shape;
}

LM2_API lm2_shape2_f32 lm2_shape2_from_capsule_f32(lm2_capsule2_f32* capsule) {
  LM2_ASSERT(capsule != NULL);
  lm2_shape2_f32 shape;
  shape.type = LM2_SHAPE2_CAPSULE;
  shape.data = capsule;
  return shape;
}

LM2_API lm2_shape2_f32 lm2_shape2_from_aabb2_f32(lm2_aabb2_f32* aabb2) {
  LM2_ASSERT(aabb2 != NULL);
  lm2_shape2_f32 shape;
  shape.type = LM2_SHAPE2_AABB2;
  shape.data = aabb2;
  return shape;
}

LM2_API lm2_shape2_f32 lm2_shape2_from_triangle_f32(lm2_triangle2_f32* triangle) {
  LM2_ASSERT(triangle != NULL);
  lm2_shape2_f32 shape;
  shape.type = LM2_SHAPE2_TRIANGLE;
  shape.data = triangle;
  return shape;
}

LM2_API lm2_shape2_f32 lm2_shape2_from_polygon_f32(lm2_polygon_f32* polygon) {
  LM2_ASSERT(polygon != NULL);
  lm2_shape2_f32 shape;
  shape.type = LM2_SHAPE2_POLYGON;
  shape.data = polygon;
  return shape;
}

LM2_API lm2_shape2_f32 lm2_shape2_from_edge_f32(lm2_edge2_f32* edge) {
  LM2_ASSERT(edge != NULL);
  lm2_shape2_f32 shape;
  shape.type = LM2_SHAPE2_EDGE;
  shape.data = edge;
  return shape;
}

// =============================================================================
// Extraction Helpers - f64
// =============================================================================

LM2_API lm2_circle_f64* lm2_shape2_as_circle_f64(lm2_shape2_f64* shape) {
  LM2_ASSERT(shape != NULL);
  if (shape->type != LM2_SHAPE2_CIRCLE) {
    return NULL;
  }
  return (lm2_circle_f64*)shape->data;
}

LM2_API lm2_capsule2_f64* lm2_shape2_as_capsule_f64(lm2_shape2_f64* shape) {
  LM2_ASSERT(shape != NULL);
  if (shape->type != LM2_SHAPE2_CAPSULE) {
    return NULL;
  }
  return (lm2_capsule2_f64*)shape->data;
}

LM2_API lm2_aabb2_f64* lm2_shape2_as_aabb2_f64(lm2_shape2_f64* shape) {
  LM2_ASSERT(shape != NULL);
  if (shape->type != LM2_SHAPE2_AABB2) {
    return NULL;
  }
  return (lm2_aabb2_f64*)shape->data;
}

LM2_API lm2_triangle2_f64* lm2_shape2_as_triangle_f64(lm2_shape2_f64* shape) {
  LM2_ASSERT(shape != NULL);
  if (shape->type != LM2_SHAPE2_TRIANGLE) {
    return NULL;
  }
  return (lm2_triangle2_f64*)shape->data;
}

LM2_API lm2_polygon_f64* lm2_shape2_as_polygon_f64(lm2_shape2_f64* shape) {
  LM2_ASSERT(shape != NULL);
  if (shape->type != LM2_SHAPE2_POLYGON) {
    return NULL;
  }
  return (lm2_polygon_f64*)shape->data;
}

LM2_API lm2_edge2_f64* lm2_shape2_as_edge_f64(lm2_shape2_f64* shape) {
  LM2_ASSERT(shape != NULL);
  if (shape->type != LM2_SHAPE2_EDGE) {
    return NULL;
  }
  return (lm2_edge2_f64*)shape->data;
}

// =============================================================================
// Extraction Helpers - f32
// =============================================================================

LM2_API lm2_circle_f32* lm2_shape2_as_circle_f32(lm2_shape2_f32* shape) {
  LM2_ASSERT(shape != NULL);
  if (shape->type != LM2_SHAPE2_CIRCLE) {
    return NULL;
  }
  return (lm2_circle_f32*)shape->data;
}

LM2_API lm2_capsule2_f32* lm2_shape2_as_capsule_f32(lm2_shape2_f32* shape) {
  LM2_ASSERT(shape != NULL);
  if (shape->type != LM2_SHAPE2_CAPSULE) {
    return NULL;
  }
  return (lm2_capsule2_f32*)shape->data;
}

LM2_API lm2_aabb2_f32* lm2_shape2_as_aabb2_f32(lm2_shape2_f32* shape) {
  LM2_ASSERT(shape != NULL);
  if (shape->type != LM2_SHAPE2_AABB2) {
    return NULL;
  }
  return (lm2_aabb2_f32*)shape->data;
}

LM2_API lm2_triangle2_f32* lm2_shape2_as_triangle_f32(lm2_shape2_f32* shape) {
  LM2_ASSERT(shape != NULL);
  if (shape->type != LM2_SHAPE2_TRIANGLE) {
    return NULL;
  }
  return (lm2_triangle2_f32*)shape->data;
}

LM2_API lm2_polygon_f32* lm2_shape2_as_polygon_f32(lm2_shape2_f32* shape) {
  LM2_ASSERT(shape != NULL);
  if (shape->type != LM2_SHAPE2_POLYGON) {
    return NULL;
  }
  return (lm2_polygon_f32*)shape->data;
}

LM2_API lm2_edge2_f32* lm2_shape2_as_edge_f32(lm2_shape2_f32* shape) {
  LM2_ASSERT(shape != NULL);
  if (shape->type != LM2_SHAPE2_EDGE) {
    return NULL;
  }
  return (lm2_edge2_f32*)shape->data;
}

// =============================================================================
// Type Query Helpers - f64
// =============================================================================

LM2_API bool lm2_shape2_is_type_f64(const lm2_shape2_f64* shape, lm2_shape2_type type) {
  LM2_ASSERT(shape != NULL);
  return shape->type == type;
}

LM2_API lm2_shape2_type lm2_shape2_get_type_f64(const lm2_shape2_f64* shape) {
  LM2_ASSERT(shape != NULL);
  return shape->type;
}

// =============================================================================
// Type Query Helpers - f32
// =============================================================================

LM2_API bool lm2_shape2_is_type_f32(const lm2_shape2_f32* shape, lm2_shape2_type type) {
  LM2_ASSERT(shape != NULL);
  return shape->type == type;
}

LM2_API lm2_shape2_type lm2_shape2_get_type_f32(const lm2_shape2_f32* shape) {
  LM2_ASSERT(shape != NULL);
  return shape->type;
}
