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
#include <memory>
#include <vector>
#include "lm2/geometry3d/lm2_triangle3_geometry.h"

// Test fixture for Triangle3Geometry tests
class Triangle3GeometryTest : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Triangle List to Vertex Array - Size Tests
// =============================================================================

TEST_F(Triangle3GeometryTest, TriangleListToVertexArraySize_F64) {
  size_t size = lm2_triangle3_list_to_vertex_array_size_f64(5);
  EXPECT_EQ(size, 15);  // 5 triangles * 3 vertices = 15
}

TEST_F(Triangle3GeometryTest, TriangleListToVertexArraySize_F32) {
  size_t size = lm2_triangle3_list_to_vertex_array_size_f32(3);
  EXPECT_EQ(size, 9);  // 3 triangles * 3 vertices = 9
}

// =============================================================================
// Triangle List to Vertex Array - Conversion Tests (f64)
// =============================================================================

TEST_F(Triangle3GeometryTest, TriangleListToVertexArray_F64) {
  // Create 2 triangles
  lm2_triangle3_f64 triangles[2];
  lm2_triangle3_make_coords_f64(triangles[0], 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  lm2_triangle3_make_coords_f64(triangles[1], 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0);

  size_t vertex_count = lm2_triangle3_list_to_vertex_array_size_f64(2);
  std::vector<lm2_v3_f64> vertices(vertex_count);

  lm2_triangle3_list_to_vertex_array_f64(triangles, 2, vertices.data(), vertex_count);

  // Verify first triangle
  EXPECT_DOUBLE_EQ(vertices[0].x, 0.0);
  EXPECT_DOUBLE_EQ(vertices[0].y, 0.0);
  EXPECT_DOUBLE_EQ(vertices[1].x, 1.0);
  EXPECT_DOUBLE_EQ(vertices[2].y, 1.0);

  // Verify second triangle
  EXPECT_DOUBLE_EQ(vertices[3].x, 1.0);
  EXPECT_DOUBLE_EQ(vertices[4].x, 1.0);
  EXPECT_DOUBLE_EQ(vertices[5].y, 1.0);
}

// =============================================================================
// Triangle List to Vertex Array - Conversion Tests (f32)
// =============================================================================

TEST_F(Triangle3GeometryTest, TriangleListToVertexArray_F32) {
  lm2_triangle3_f32 triangles[2];
  lm2_triangle3_make_coords_f32(triangles[0], 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
  lm2_triangle3_make_coords_f32(triangles[1], 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

  size_t vertex_count = lm2_triangle3_list_to_vertex_array_size_f32(2);
  std::vector<lm2_v3_f32> vertices(vertex_count);

  lm2_triangle3_list_to_vertex_array_f32(triangles, 2, vertices.data(), vertex_count);

  EXPECT_FLOAT_EQ(vertices[0].x, 0.0f);
  EXPECT_FLOAT_EQ(vertices[1].x, 1.0f);
}

// =============================================================================
// Vertex Array to Triangle List - Size Tests
// =============================================================================

TEST_F(Triangle3GeometryTest, VertexArrayToTriangleListSize_F64) {
  size_t size = lm2_vertex_array_to_triangle3_list_size_f64(15);
  EXPECT_EQ(size, 5);  // 15 vertices / 3 = 5 triangles
}

TEST_F(Triangle3GeometryTest, VertexArrayToTriangleListSize_F32) {
  size_t size = lm2_vertex_array_to_triangle3_list_size_f32(9);
  EXPECT_EQ(size, 3);  // 9 vertices / 3 = 3 triangles
}

// =============================================================================
// Vertex Array to Triangle List - Conversion Tests (f64)
// =============================================================================

TEST_F(Triangle3GeometryTest, VertexArrayToTriangleList_F64) {
  // Create vertex array (2 triangles = 6 vertices)
  lm2_v3_f64 vertices[6] = {
      {0.0, 0.0, 0.0},
      {1.0, 0.0, 0.0},
      {0.0, 1.0, 0.0}, // Triangle 1
      {1.0, 0.0, 0.0},
      {1.0, 1.0, 0.0},
      {0.0, 1.0, 0.0}  // Triangle 2
  };

  size_t triangle_count = lm2_vertex_array_to_triangle3_list_size_f64(6);
  auto triangles = std::make_unique<lm2_triangle3_f64[]>(triangle_count);

  lm2_vertex_array_to_triangle3_list_f64(vertices, 6, triangles.get(), triangle_count);

  EXPECT_EQ(triangle_count, 2);
  EXPECT_DOUBLE_EQ(triangles[0][0].x, 0.0);
  EXPECT_DOUBLE_EQ(triangles[0][1].x, 1.0);
  EXPECT_DOUBLE_EQ(triangles[1][0].x, 1.0);
}

// =============================================================================
// Vertex Array to Triangle List - Conversion Tests (f32)
// =============================================================================

TEST_F(Triangle3GeometryTest, VertexArrayToTriangleList_F32) {
  lm2_v3_f32 vertices[6] = {
      {0.0f, 0.0f, 0.0f},
      {1.0f, 0.0f, 0.0f},
      {0.0f, 1.0f, 0.0f},
      {1.0f, 0.0f, 0.0f},
      {1.0f, 1.0f, 0.0f},
      {0.0f, 1.0f, 0.0f}
  };

  size_t triangle_count = lm2_vertex_array_to_triangle3_list_size_f32(6);
  auto triangles = std::make_unique<lm2_triangle3_f32[]>(triangle_count);

  lm2_vertex_array_to_triangle3_list_f32(vertices, 6, triangles.get(), triangle_count);

  EXPECT_EQ(triangle_count, 2);
  EXPECT_FLOAT_EQ(triangles[0][0].x, 0.0f);
}

// =============================================================================
// Indexed Mesh Size Tests (f64)
// =============================================================================

TEST_F(Triangle3GeometryTest, TriangleListToIndexedMeshSize_F64) {
  // Create 2 triangles sharing vertices
  lm2_triangle3_f64 triangles[2];
  lm2_triangle3_make_coords_f64(triangles[0], 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  lm2_triangle3_make_coords_f64(triangles[1], 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0);

  lm2_indexed_mesh3_size size = lm2_triangle3_list_to_indexed_mesh_size_f64(triangles, 2, EPSILON_F64);

  // These two triangles share 2 vertices, so we should have 4 unique vertices
  EXPECT_EQ(size.vertex_count, 4);
  EXPECT_EQ(size.index_count, 6);  // 2 triangles * 3 indices
}

// =============================================================================
// Indexed Mesh Size Tests (f32)
// =============================================================================

TEST_F(Triangle3GeometryTest, TriangleListToIndexedMeshSize_F32) {
  lm2_triangle3_f32 triangles[2];
  lm2_triangle3_make_coords_f32(triangles[0], 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
  lm2_triangle3_make_coords_f32(triangles[1], 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

  lm2_indexed_mesh3_size size = lm2_triangle3_list_to_indexed_mesh_size_f32(triangles, 2, EPSILON_F32);

  EXPECT_EQ(size.vertex_count, 4);
  EXPECT_EQ(size.index_count, 6);
}

// =============================================================================
// Triangle List to Indexed Mesh - Conversion Tests (f64)
// =============================================================================

TEST_F(Triangle3GeometryTest, TriangleListToIndexedMesh_F64) {
  // Create 2 triangles sharing vertices
  lm2_triangle3_f64 triangles[2];
  lm2_triangle3_make_coords_f64(triangles[0], 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  lm2_triangle3_make_coords_f64(triangles[1], 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0);

  lm2_indexed_mesh3_size size = lm2_triangle3_list_to_indexed_mesh_size_f64(triangles, 2, EPSILON_F64);

  std::vector<lm2_v3_f64> vertices(size.vertex_count);
  std::vector<uint32_t> indices(size.index_count);

  lm2_triangle3_list_to_indexed_mesh_f64(
      triangles, 2, EPSILON_F64, vertices.data(), size.vertex_count, indices.data(), size.index_count);

  // Verify we have the expected number of unique vertices
  EXPECT_EQ(vertices.size(), 4);
  EXPECT_EQ(indices.size(), 6);

  // All indices should be valid (< vertex_count)
  for (size_t i = 0; i < indices.size(); ++i) {
    EXPECT_LT(indices[i], size.vertex_count);
  }
}

// =============================================================================
// Triangle List to Indexed Mesh - Conversion Tests (f32)
// =============================================================================

TEST_F(Triangle3GeometryTest, TriangleListToIndexedMesh_F32) {
  lm2_triangle3_f32 triangles[2];
  lm2_triangle3_make_coords_f32(triangles[0], 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
  lm2_triangle3_make_coords_f32(triangles[1], 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

  lm2_indexed_mesh3_size size = lm2_triangle3_list_to_indexed_mesh_size_f32(triangles, 2, EPSILON_F32);

  std::vector<lm2_v3_f32> vertices(size.vertex_count);
  std::vector<uint32_t> indices(size.index_count);

  lm2_triangle3_list_to_indexed_mesh_f32(
      triangles, 2, EPSILON_F32, vertices.data(), size.vertex_count, indices.data(), size.index_count);

  EXPECT_EQ(vertices.size(), 4);
  EXPECT_EQ(indices.size(), 6);
}

// =============================================================================
// Indexed Mesh to Triangle List - Size Tests
// =============================================================================

TEST_F(Triangle3GeometryTest, IndexedMeshToTriangleListSize_F64) {
  size_t size = lm2_indexed_mesh_to_triangle3_list_size_f64(12);
  EXPECT_EQ(size, 4);  // 12 indices / 3 = 4 triangles
}

TEST_F(Triangle3GeometryTest, IndexedMeshToTriangleListSize_F32) {
  size_t size = lm2_indexed_mesh_to_triangle3_list_size_f32(6);
  EXPECT_EQ(size, 2);  // 6 indices / 3 = 2 triangles
}

// =============================================================================
// Indexed Mesh to Triangle List - Conversion Tests (f64)
// =============================================================================

TEST_F(Triangle3GeometryTest, IndexedMeshToTriangleList_F64) {
  // Create indexed mesh (4 vertices, 2 triangles)
  lm2_v3_f64 vertices[4] = {
      {0.0, 0.0, 0.0},
      {1.0, 0.0, 0.0},
      {0.0, 1.0, 0.0},
      {1.0, 1.0, 0.0}
  };

  uint32_t indices[6] = {0, 1, 2, 1, 3, 2};

  size_t triangle_count = lm2_indexed_mesh_to_triangle3_list_size_f64(6);
  auto triangles = std::make_unique<lm2_triangle3_f64[]>(triangle_count);

  lm2_indexed_mesh_to_triangle3_list_f64(
      vertices, 4, indices, 6, triangles.get(), triangle_count);

  EXPECT_EQ(triangle_count, 2);

  // Verify first triangle
  EXPECT_DOUBLE_EQ(triangles[0][0].x, 0.0);
  EXPECT_DOUBLE_EQ(triangles[0][1].x, 1.0);
  EXPECT_DOUBLE_EQ(triangles[0][2].y, 1.0);
}

// =============================================================================
// Indexed Mesh to Triangle List - Conversion Tests (f32)
// =============================================================================

TEST_F(Triangle3GeometryTest, IndexedMeshToTriangleList_F32) {
  lm2_v3_f32 vertices[4] = {
      {0.0f, 0.0f, 0.0f},
      {1.0f, 0.0f, 0.0f},
      {0.0f, 1.0f, 0.0f},
      {1.0f, 1.0f, 0.0f}
  };

  uint32_t indices[6] = {0, 1, 2, 1, 3, 2};

  size_t triangle_count = lm2_indexed_mesh_to_triangle3_list_size_f32(6);
  auto triangles = std::make_unique<lm2_triangle3_f32[]>(triangle_count);

  lm2_indexed_mesh_to_triangle3_list_f32(
      vertices, 4, indices, 6, triangles.get(), triangle_count);

  EXPECT_EQ(triangle_count, 2);
  EXPECT_FLOAT_EQ(triangles[0][0].x, 0.0f);
}

// =============================================================================
// Round-trip Tests
// =============================================================================

TEST_F(Triangle3GeometryTest, RoundTrip_VertexArray_F64) {
  // Create original triangles
  lm2_triangle3_f64 original[2];
  lm2_triangle3_make_coords_f64(original[0], 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  lm2_triangle3_make_coords_f64(original[1], 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0);

  // Convert to vertex array
  size_t vertex_count = lm2_triangle3_list_to_vertex_array_size_f64(2);
  std::vector<lm2_v3_f64> vertices(vertex_count);
  lm2_triangle3_list_to_vertex_array_f64(original, 2, vertices.data(), vertex_count);

  // Convert back to triangles
  size_t triangle_count = lm2_vertex_array_to_triangle3_list_size_f64(vertex_count);
  auto result = std::make_unique<lm2_triangle3_f64[]>(triangle_count);
  lm2_vertex_array_to_triangle3_list_f64(vertices.data(), vertex_count, result.get(), triangle_count);

  // Verify round-trip
  EXPECT_EQ(triangle_count, 2);
  for (size_t i = 0; i < 3; ++i) {
    EXPECT_NEAR(result[0][i].x, original[0][i].x, EPSILON_F64);
    EXPECT_NEAR(result[0][i].y, original[0][i].y, EPSILON_F64);
    EXPECT_NEAR(result[0][i].z, original[0][i].z, EPSILON_F64);
  }
}

TEST_F(Triangle3GeometryTest, RoundTrip_IndexedMesh_F64) {
  // Create original triangles
  lm2_triangle3_f64 original[2];
  lm2_triangle3_make_coords_f64(original[0], 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  lm2_triangle3_make_coords_f64(original[1], 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0);

  // Convert to indexed mesh
  lm2_indexed_mesh3_size size = lm2_triangle3_list_to_indexed_mesh_size_f64(original, 2, EPSILON_F64);
  std::vector<lm2_v3_f64> vertices(size.vertex_count);
  std::vector<uint32_t> indices(size.index_count);
  lm2_triangle3_list_to_indexed_mesh_f64(
      original, 2, EPSILON_F64, vertices.data(), size.vertex_count, indices.data(), size.index_count);

  // Convert back to triangles
  size_t triangle_count = lm2_indexed_mesh_to_triangle3_list_size_f64(size.index_count);
  auto result = std::make_unique<lm2_triangle3_f64[]>(triangle_count);
  lm2_indexed_mesh_to_triangle3_list_f64(
      vertices.data(), size.vertex_count, indices.data(), size.index_count, result.get(), triangle_count);

  // Verify round-trip (triangles should be identical)
  EXPECT_EQ(triangle_count, 2);
}

// =============================================================================
// Edge Cases
// =============================================================================

TEST_F(Triangle3GeometryTest, SingleTriangle_F64) {
  lm2_triangle3_f64 tri;
  lm2_triangle3_make_coords_f64(tri, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  lm2_indexed_mesh3_size size = lm2_triangle3_list_to_indexed_mesh_size_f64(&tri, 1, EPSILON_F64);

  EXPECT_EQ(size.vertex_count, 3);  // Single triangle has 3 unique vertices
  EXPECT_EQ(size.index_count, 3);
}

TEST_F(Triangle3GeometryTest, NoSharedVertices_F64) {
  // Create triangles with no shared vertices
  lm2_triangle3_f64 triangles[2];
  lm2_triangle3_make_coords_f64(triangles[0], 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  lm2_triangle3_make_coords_f64(triangles[1], 5.0, 5.0, 5.0, 6.0, 5.0, 5.0, 5.0, 6.0, 5.0);

  lm2_indexed_mesh3_size size = lm2_triangle3_list_to_indexed_mesh_size_f64(triangles, 2, EPSILON_F64);

  EXPECT_EQ(size.vertex_count, 6);  // No sharing = 6 unique vertices
  EXPECT_EQ(size.index_count, 6);
}
