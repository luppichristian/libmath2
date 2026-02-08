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

#include <lm2/geometry2d/lm2_triangle_geometry.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>
#include <string.h>  // For memcpy

// =============================================================================
// Triangle List to Vertex Array Conversion
// =============================================================================

LM2_API size_t lm2_triangle_list_to_vertex_array_size_f64(size_t triangle_count) {
  return lm2_mul_u64(triangle_count, 3);
}

LM2_API size_t lm2_triangle_list_to_vertex_array_size_f32(size_t triangle_count) {
  return lm2_mul_u64(triangle_count, 3);
}

LM2_API void lm2_triangle_list_to_vertex_array_f64(
    const lm2_triangle_f64* triangles,
    size_t triangle_count,
    lm2_v2f64* vertices,
    size_t vertex_buffer_size) {
  LM2_ASSERT(triangles != NULL);
  LM2_ASSERT(vertices != NULL);

  size_t required_size = lm2_triangle_list_to_vertex_array_size_f64(triangle_count);
  LM2_ASSERT(vertex_buffer_size >= required_size);

  size_t vertex_index = 0;
  for (size_t i = 0; i < triangle_count; i = lm2_add_u64(i, 1)) {
    vertices[vertex_index] = triangles[i][0];
    vertex_index = lm2_add_u64(vertex_index, 1);

    vertices[vertex_index] = triangles[i][1];
    vertex_index = lm2_add_u64(vertex_index, 1);

    vertices[vertex_index] = triangles[i][2];
    vertex_index = lm2_add_u64(vertex_index, 1);
  }
}

LM2_API void lm2_triangle_list_to_vertex_array_f32(
    const lm2_triangle_f32* triangles,
    size_t triangle_count,
    lm2_v2f32* vertices,
    size_t vertex_buffer_size) {
  LM2_ASSERT(triangles != NULL);
  LM2_ASSERT(vertices != NULL);

  size_t required_size = lm2_triangle_list_to_vertex_array_size_f32(triangle_count);
  LM2_ASSERT(vertex_buffer_size >= required_size);

  size_t vertex_index = 0;
  for (size_t i = 0; i < triangle_count; i = lm2_add_u64(i, 1)) {
    vertices[vertex_index] = triangles[i][0];
    vertex_index = lm2_add_u64(vertex_index, 1);

    vertices[vertex_index] = triangles[i][1];
    vertex_index = lm2_add_u64(vertex_index, 1);

    vertices[vertex_index] = triangles[i][2];
    vertex_index = lm2_add_u64(vertex_index, 1);
  }
}

// =============================================================================
// Vertex Array to Triangle List Conversion (Inverse)
// =============================================================================

LM2_API size_t lm2_vertex_array_to_triangle_list_size_f64(size_t vertex_count) {
  LM2_ASSERT(lm2_mod_u64(vertex_count, 3) == 0);
  return lm2_div_u64(vertex_count, 3);
}

LM2_API size_t lm2_vertex_array_to_triangle_list_size_f32(size_t vertex_count) {
  LM2_ASSERT(lm2_mod_u64(vertex_count, 3) == 0);
  return lm2_div_u64(vertex_count, 3);
}

LM2_API void lm2_vertex_array_to_triangle_list_f64(
    const lm2_v2f64* vertices,
    size_t vertex_count,
    lm2_triangle_f64* triangles,
    size_t triangle_buffer_size) {
  LM2_ASSERT(vertices != NULL);
  LM2_ASSERT(triangles != NULL);
  LM2_ASSERT(lm2_mod_u64(vertex_count, 3) == 0);

  size_t required_size = lm2_vertex_array_to_triangle_list_size_f64(vertex_count);
  LM2_ASSERT(triangle_buffer_size >= required_size);

  size_t triangle_index = 0;
  for (size_t i = 0; i < vertex_count; i = lm2_add_u64(i, 3)) {
    triangles[triangle_index][0] = vertices[i];
    triangles[triangle_index][1] = vertices[lm2_add_u64(i, 1)];
    triangles[triangle_index][2] = vertices[lm2_add_u64(i, 2)];
    triangle_index = lm2_add_u64(triangle_index, 1);
  }
}

LM2_API void lm2_vertex_array_to_triangle_list_f32(
    const lm2_v2f32* vertices,
    size_t vertex_count,
    lm2_triangle_f32* triangles,
    size_t triangle_buffer_size) {
  LM2_ASSERT(vertices != NULL);
  LM2_ASSERT(triangles != NULL);
  LM2_ASSERT(lm2_mod_u64(vertex_count, 3) == 0);

  size_t required_size = lm2_vertex_array_to_triangle_list_size_f32(vertex_count);
  LM2_ASSERT(triangle_buffer_size >= required_size);

  size_t triangle_index = 0;
  for (size_t i = 0; i < vertex_count; i = lm2_add_u64(i, 3)) {
    triangles[triangle_index][0] = vertices[i];
    triangles[triangle_index][1] = vertices[lm2_add_u64(i, 1)];
    triangles[triangle_index][2] = vertices[lm2_add_u64(i, 2)];
    triangle_index = lm2_add_u64(triangle_index, 1);
  }
}

// =============================================================================
// Helper Functions for Vertex Deduplication
// =============================================================================

static bool _lm2_vertices_equal_f64(lm2_v2f64 a, lm2_v2f64 b, double epsilon) {
  double dx = lm2_abs_f64(lm2_sub_f64(a.x, b.x));
  double dy = lm2_abs_f64(lm2_sub_f64(a.y, b.y));
  return dx <= epsilon && dy <= epsilon;
}

static bool _lm2_vertices_equal_f32(lm2_v2f32 a, lm2_v2f32 b, float epsilon) {
  float dx = lm2_abs_f32(lm2_sub_f32(a.x, b.x));
  float dy = lm2_abs_f32(lm2_sub_f32(a.y, b.y));
  return dx <= epsilon && dy <= epsilon;
}

static uint32_t _lm2_find_or_add_vertex_f64(
    lm2_v2f64 vertex,
    lm2_v2f64* vertices,
    uint32_t* vertex_count,
    double epsilon) {
  // Search for existing vertex
  for (uint32_t i = 0; i < *vertex_count; i = lm2_add_u32(i, 1)) {
    if (_lm2_vertices_equal_f64(vertices[i], vertex, epsilon)) {
      return i;
    }
  }

  // Add new vertex
  uint32_t index = *vertex_count;
  vertices[index] = vertex;
  *vertex_count = lm2_add_u32(*vertex_count, 1);
  return index;
}

static uint32_t _lm2_find_or_add_vertex_f32(
    lm2_v2f32 vertex,
    lm2_v2f32* vertices,
    uint32_t* vertex_count,
    float epsilon) {
  // Search for existing vertex
  for (uint32_t i = 0; i < *vertex_count; i = lm2_add_u32(i, 1)) {
    if (_lm2_vertices_equal_f32(vertices[i], vertex, epsilon)) {
      return i;
    }
  }

  // Add new vertex
  uint32_t index = *vertex_count;
  vertices[index] = vertex;
  *vertex_count = lm2_add_u32(*vertex_count, 1);
  return index;
}

// =============================================================================
// Triangle List to Indexed Mesh Conversion
// =============================================================================

LM2_API lm2_indexed_mesh_size lm2_triangle_list_to_indexed_mesh_size_f64(
    const lm2_triangle_f64* triangles,
    size_t triangle_count,
    double epsilon) {
  LM2_ASSERT(triangles != NULL);

  lm2_indexed_mesh_size result = {0, 0};

  // We need temporary storage to track unique vertices during size calculation
  // Worst case: all vertices are unique (triangle_count * 3)
  size_t max_vertices = lm2_mul_u64(triangle_count, 3);

  // For size query, we need to actually perform the deduplication
  // This requires temporary storage which violates our no-allocation policy
  // So we'll do a simplified estimation: return worst-case size
  // Users can call this with a temp buffer pattern if needed

  result.vertex_count = max_vertices;  // Worst case
  result.index_count = lm2_mul_u64(triangle_count, 3);

  return result;
}

LM2_API lm2_indexed_mesh_size lm2_triangle_list_to_indexed_mesh_size_f32(
    const lm2_triangle_f32* triangles,
    size_t triangle_count,
    float epsilon) {
  LM2_ASSERT(triangles != NULL);

  lm2_indexed_mesh_size result = {0, 0};

  // Worst case: all vertices are unique
  size_t max_vertices = lm2_mul_u64(triangle_count, 3);

  result.vertex_count = max_vertices;  // Worst case
  result.index_count = lm2_mul_u64(triangle_count, 3);

  return result;
}

LM2_API void lm2_triangle_list_to_indexed_mesh_f64(
    const lm2_triangle_f64* triangles,
    size_t triangle_count,
    double epsilon,
    lm2_v2f64* vertices,
    size_t vertex_buffer_size,
    uint32_t* indices,
    size_t index_buffer_size) {
  LM2_ASSERT(triangles != NULL);
  LM2_ASSERT(vertices != NULL);
  LM2_ASSERT(indices != NULL);

  size_t required_index_count = lm2_mul_u64(triangle_count, 3);
  LM2_ASSERT(index_buffer_size >= required_index_count);
  LM2_ASSERT(vertex_buffer_size >= triangle_count);  // At least this many

  uint32_t vertex_count = 0;
  uint32_t index_count = 0;

  for (size_t i = 0; i < triangle_count; i = lm2_add_u64(i, 1)) {
    // Process each vertex of the triangle
    for (int j = 0; j < 3; j++) {
      uint32_t index = _lm2_find_or_add_vertex_f64(
          triangles[i][j],
          vertices,
          &vertex_count,
          epsilon);

      LM2_ASSERT(vertex_count <= vertex_buffer_size);
      indices[index_count] = index;
      index_count = lm2_add_u32(index_count, 1);
    }
  }
}

LM2_API void lm2_triangle_list_to_indexed_mesh_f32(
    const lm2_triangle_f32* triangles,
    size_t triangle_count,
    float epsilon,
    lm2_v2f32* vertices,
    size_t vertex_buffer_size,
    uint32_t* indices,
    size_t index_buffer_size) {
  LM2_ASSERT(triangles != NULL);
  LM2_ASSERT(vertices != NULL);
  LM2_ASSERT(indices != NULL);

  size_t required_index_count = lm2_mul_u64(triangle_count, 3);
  LM2_ASSERT(index_buffer_size >= required_index_count);
  LM2_ASSERT(vertex_buffer_size >= triangle_count);  // At least this many

  uint32_t vertex_count = 0;
  uint32_t index_count = 0;

  for (size_t i = 0; i < triangle_count; i = lm2_add_u64(i, 1)) {
    // Process each vertex of the triangle
    for (int j = 0; j < 3; j++) {
      uint32_t index = _lm2_find_or_add_vertex_f32(
          triangles[i][j],
          vertices,
          &vertex_count,
          epsilon);

      LM2_ASSERT(vertex_count <= vertex_buffer_size);
      indices[index_count] = index;
      index_count = lm2_add_u32(index_count, 1);
    }
  }
}

// =============================================================================
// Indexed Mesh to Triangle List Conversion (Inverse)
// =============================================================================

LM2_API size_t lm2_indexed_mesh_to_triangle_list_size_f64(size_t index_count) {
  LM2_ASSERT(lm2_mod_u64(index_count, 3) == 0);
  return lm2_div_u64(index_count, 3);
}

LM2_API size_t lm2_indexed_mesh_to_triangle_list_size_f32(size_t index_count) {
  LM2_ASSERT(lm2_mod_u64(index_count, 3) == 0);
  return lm2_div_u64(index_count, 3);
}

LM2_API void lm2_indexed_mesh_to_triangle_list_f64(
    const lm2_v2f64* vertices,
    size_t vertex_count,
    const uint32_t* indices,
    size_t index_count,
    lm2_triangle_f64* triangles,
    size_t triangle_buffer_size) {
  LM2_ASSERT(vertices != NULL);
  LM2_ASSERT(indices != NULL);
  LM2_ASSERT(triangles != NULL);
  LM2_ASSERT(lm2_mod_u64(index_count, 3) == 0);

  size_t required_size = lm2_indexed_mesh_to_triangle_list_size_f64(index_count);
  LM2_ASSERT(triangle_buffer_size >= required_size);

  size_t triangle_index = 0;
  for (size_t i = 0; i < index_count; i = lm2_add_u64(i, 3)) {
    uint32_t idx0 = indices[i];
    uint32_t idx1 = indices[lm2_add_u64(i, 1)];
    uint32_t idx2 = indices[lm2_add_u64(i, 2)];

    LM2_ASSERT(idx0 < vertex_count);
    LM2_ASSERT(idx1 < vertex_count);
    LM2_ASSERT(idx2 < vertex_count);

    triangles[triangle_index][0] = vertices[idx0];
    triangles[triangle_index][1] = vertices[idx1];
    triangles[triangle_index][2] = vertices[idx2];

    triangle_index = lm2_add_u64(triangle_index, 1);
  }
}

LM2_API void lm2_indexed_mesh_to_triangle_list_f32(
    const lm2_v2f32* vertices,
    size_t vertex_count,
    const uint32_t* indices,
    size_t index_count,
    lm2_triangle_f32* triangles,
    size_t triangle_buffer_size) {
  LM2_ASSERT(vertices != NULL);
  LM2_ASSERT(indices != NULL);
  LM2_ASSERT(triangles != NULL);
  LM2_ASSERT(lm2_mod_u64(index_count, 3) == 0);

  size_t required_size = lm2_indexed_mesh_to_triangle_list_size_f32(index_count);
  LM2_ASSERT(triangle_buffer_size >= required_size);

  size_t triangle_index = 0;
  for (size_t i = 0; i < index_count; i = lm2_add_u64(i, 3)) {
    uint32_t idx0 = indices[i];
    uint32_t idx1 = indices[lm2_add_u64(i, 1)];
    uint32_t idx2 = indices[lm2_add_u64(i, 2)];

    LM2_ASSERT(idx0 < vertex_count);
    LM2_ASSERT(idx1 < vertex_count);
    LM2_ASSERT(idx2 < vertex_count);

    triangles[triangle_index][0] = vertices[idx0];
    triangles[triangle_index][1] = vertices[idx1];
    triangles[triangle_index][2] = vertices[idx2];

    triangle_index = lm2_add_u64(triangle_index, 1);
  }
}
