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

#include "lm2/geometry3d/lm2_shape3.h"

// =============================================================================
// Construction Helpers - f64
// =============================================================================

LM2_API lm2_shape3_f64 lm2_shape3_from_sphere_f64(lm2_sphere_f64* sphere) {
  LM2_ASSERT(sphere != NULL);
  lm2_shape3_f64 shape;
  shape.type = LM2_SHAPE3_SPHERE;
  shape.data = sphere;
  return shape;
}

LM2_API lm2_shape3_f64 lm2_shape3_from_capsule_f64(lm2_capsule3_f64* capsule) {
  LM2_ASSERT(capsule != NULL);
  lm2_shape3_f64 shape;
  shape.type = LM2_SHAPE3_CAPSULE;
  shape.data = capsule;
  return shape;
}

LM2_API lm2_shape3_f64 lm2_shape3_from_aabb3_f64(lm2_aabb3_f64* aabb3) {
  LM2_ASSERT(aabb3 != NULL);
  lm2_shape3_f64 shape;
  shape.type = LM2_SHAPE3_AABB3;
  shape.data = aabb3;
  return shape;
}

LM2_API lm2_shape3_f64 lm2_shape3_from_triangle_f64(lm2_triangle3_f64* triangle) {
  LM2_ASSERT(triangle != NULL);
  lm2_shape3_f64 shape;
  shape.type = LM2_SHAPE3_TRIANGLE;
  shape.data = triangle;
  return shape;
}

LM2_API lm2_shape3_f64 lm2_shape3_from_edge_f64(lm2_edge3_f64* edge) {
  LM2_ASSERT(edge != NULL);
  lm2_shape3_f64 shape;
  shape.type = LM2_SHAPE3_EDGE;
  shape.data = edge;
  return shape;
}

// =============================================================================
// Construction Helpers - f32
// =============================================================================

LM2_API lm2_shape3_f32 lm2_shape3_from_sphere_f32(lm2_sphere_f32* sphere) {
  LM2_ASSERT(sphere != NULL);
  lm2_shape3_f32 shape;
  shape.type = LM2_SHAPE3_SPHERE;
  shape.data = sphere;
  return shape;
}

LM2_API lm2_shape3_f32 lm2_shape3_from_capsule_f32(lm2_capsule3_f32* capsule) {
  LM2_ASSERT(capsule != NULL);
  lm2_shape3_f32 shape;
  shape.type = LM2_SHAPE3_CAPSULE;
  shape.data = capsule;
  return shape;
}

LM2_API lm2_shape3_f32 lm2_shape3_from_aabb3_f32(lm2_aabb3_f32* aabb3) {
  LM2_ASSERT(aabb3 != NULL);
  lm2_shape3_f32 shape;
  shape.type = LM2_SHAPE3_AABB3;
  shape.data = aabb3;
  return shape;
}

LM2_API lm2_shape3_f32 lm2_shape3_from_triangle_f32(lm2_triangle3_f32* triangle) {
  LM2_ASSERT(triangle != NULL);
  lm2_shape3_f32 shape;
  shape.type = LM2_SHAPE3_TRIANGLE;
  shape.data = triangle;
  return shape;
}

LM2_API lm2_shape3_f32 lm2_shape3_from_edge_f32(lm2_edge3_f32* edge) {
  LM2_ASSERT(edge != NULL);
  lm2_shape3_f32 shape;
  shape.type = LM2_SHAPE3_EDGE;
  shape.data = edge;
  return shape;
}

// =============================================================================
// Extraction Helpers - f64
// =============================================================================

LM2_API lm2_sphere_f64* lm2_shape3_as_sphere_f64(lm2_shape3_f64* shape) {
  LM2_ASSERT(shape != NULL);
  if (shape->type != LM2_SHAPE3_SPHERE) {
    return NULL;
  }
  return (lm2_sphere_f64*)shape->data;
}

LM2_API lm2_capsule3_f64* lm2_shape3_as_capsule_f64(lm2_shape3_f64* shape) {
  LM2_ASSERT(shape != NULL);
  if (shape->type != LM2_SHAPE3_CAPSULE) {
    return NULL;
  }
  return (lm2_capsule3_f64*)shape->data;
}

LM2_API lm2_aabb3_f64* lm2_shape3_as_aabb3_f64(lm2_shape3_f64* shape) {
  LM2_ASSERT(shape != NULL);
  if (shape->type != LM2_SHAPE3_AABB3) {
    return NULL;
  }
  return (lm2_aabb3_f64*)shape->data;
}

LM2_API lm2_triangle3_f64* lm2_shape3_as_triangle_f64(lm2_shape3_f64* shape) {
  LM2_ASSERT(shape != NULL);
  if (shape->type != LM2_SHAPE3_TRIANGLE) {
    return NULL;
  }
  return (lm2_triangle3_f64*)shape->data;
}

LM2_API lm2_edge3_f64* lm2_shape3_as_edge_f64(lm2_shape3_f64* shape) {
  LM2_ASSERT(shape != NULL);
  if (shape->type != LM2_SHAPE3_EDGE) {
    return NULL;
  }
  return (lm2_edge3_f64*)shape->data;
}

// =============================================================================
// Extraction Helpers - f32
// =============================================================================

LM2_API lm2_sphere_f32* lm2_shape3_as_sphere_f32(lm2_shape3_f32* shape) {
  LM2_ASSERT(shape != NULL);
  if (shape->type != LM2_SHAPE3_SPHERE) {
    return NULL;
  }
  return (lm2_sphere_f32*)shape->data;
}

LM2_API lm2_capsule3_f32* lm2_shape3_as_capsule_f32(lm2_shape3_f32* shape) {
  LM2_ASSERT(shape != NULL);
  if (shape->type != LM2_SHAPE3_CAPSULE) {
    return NULL;
  }
  return (lm2_capsule3_f32*)shape->data;
}

LM2_API lm2_aabb3_f32* lm2_shape3_as_aabb3_f32(lm2_shape3_f32* shape) {
  LM2_ASSERT(shape != NULL);
  if (shape->type != LM2_SHAPE3_AABB3) {
    return NULL;
  }
  return (lm2_aabb3_f32*)shape->data;
}

LM2_API lm2_triangle3_f32* lm2_shape3_as_triangle_f32(lm2_shape3_f32* shape) {
  LM2_ASSERT(shape != NULL);
  if (shape->type != LM2_SHAPE3_TRIANGLE) {
    return NULL;
  }
  return (lm2_triangle3_f32*)shape->data;
}

LM2_API lm2_edge3_f32* lm2_shape3_as_edge_f32(lm2_shape3_f32* shape) {
  LM2_ASSERT(shape != NULL);
  if (shape->type != LM2_SHAPE3_EDGE) {
    return NULL;
  }
  return (lm2_edge3_f32*)shape->data;
}

// =============================================================================
// Type Query Helpers - f64
// =============================================================================

LM2_API bool lm2_shape3_is_type_f64(const lm2_shape3_f64* shape, lm2_shape3_type type) {
  LM2_ASSERT(shape != NULL);
  return shape->type == type;
}

LM2_API lm2_shape3_type lm2_shape3_get_type_f64(const lm2_shape3_f64* shape) {
  LM2_ASSERT(shape != NULL);
  return shape->type;
}

// =============================================================================
// Type Query Helpers - f32
// =============================================================================

LM2_API bool lm2_shape3_is_type_f32(const lm2_shape3_f32* shape, lm2_shape3_type type) {
  LM2_ASSERT(shape != NULL);
  return shape->type == type;
}

LM2_API lm2_shape3_type lm2_shape3_get_type_f32(const lm2_shape3_f32* shape) {
  LM2_ASSERT(shape != NULL);
  return shape->type;
}
