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

#pragma once

#include "lm2/lm2_base.h"
#include "lm2/vectors/lm2_vector2.h"
#include "lm2_triangle2.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// =============================================================================
// Triangle List to Vertex Array Conversion
// =============================================================================

// Query the size needed for a vertex array from a triangle list
// Each triangle contributes 3 vertices to the array
// Returns: number of vertices (triangle_count * 3)
LM2_API size_t lm2_triangle2_list_to_vertex_array_size_f64(size_t triangle_count);
LM2_API size_t lm2_triangle2_list_to_vertex_array_size_f32(size_t triangle_count);

// Generate vertex array from triangle list
// triangles: array of triangles (each triangle is 3 vertices)
// triangle_count: number of triangles
// vertices: output buffer for vertices (must be at least triangle_count * 3)
// vertex_buffer_size: size of the vertices buffer in number of vertices
LM2_API void lm2_triangle2_list_to_vertex_array_f64(
    const lm2_triangle2_f64* triangles,
    size_t triangle_count,
    lm2_v2_f64* vertices,
    size_t vertex_buffer_size);

LM2_API void lm2_triangle2_list_to_vertex_array_f32(
    const lm2_triangle2_f32* triangles,
    size_t triangle_count,
    lm2_v2_f32* vertices,
    size_t vertex_buffer_size);

// =============================================================================
// Vertex Array to Triangle List Conversion (Inverse)
// =============================================================================

// Query the number of triangles from a vertex array
// vertex_count must be divisible by 3
// Returns: number of triangles (vertex_count / 3)
LM2_API size_t lm2_vertex_array_to_triangle_list_size_f64(size_t vertex_count);
LM2_API size_t lm2_vertex_array_to_triangle_list_size_f32(size_t vertex_count);

// Generate triangle list from vertex array
// vertices: array of vertices
// vertex_count: number of vertices (must be divisible by 3)
// triangles: output buffer for triangles (must be at least vertex_count / 3)
// triangle_buffer_size: size of the triangles buffer in number of triangles
LM2_API void lm2_vertex_array_to_triangle_list_f64(
    const lm2_v2_f64* vertices,
    size_t vertex_count,
    lm2_triangle2_f64* triangles,
    size_t triangle_buffer_size);

LM2_API void lm2_vertex_array_to_triangle_list_f32(
    const lm2_v2_f32* vertices,
    size_t vertex_count,
    lm2_triangle2_f32* triangles,
    size_t triangle_buffer_size);

// =============================================================================
// Indexed Mesh Information
// =============================================================================

// Structure to hold indexed mesh size information
typedef struct lm2_indexed_mesh_size {
  size_t vertex_count;  // Number of unique vertices
  size_t index_count;   // Number of indices (triangle_count * 3)
} lm2_indexed_mesh_size;

// =============================================================================
// Triangle List to Indexed Mesh Conversion
// =============================================================================

// Query the sizes needed for indexed mesh buffers from a triangle list
// This function deduplicates vertices and returns the size information
// triangles: array of triangles
// triangle_count: number of triangles
// epsilon: tolerance for vertex comparison (use 0.0 for exact comparison)
// Returns: structure with vertex_count and index_count
LM2_API lm2_indexed_mesh_size lm2_triangle2_list_to_indexed_mesh_size_f64(
    const lm2_triangle2_f64* triangles,
    size_t triangle_count,
    double epsilon);

LM2_API lm2_indexed_mesh_size lm2_triangle2_list_to_indexed_mesh_size_f32(
    const lm2_triangle2_f32* triangles,
    size_t triangle_count,
    float epsilon);

// Generate indexed mesh (vertices + indices) from triangle list
// This function deduplicates vertices within the specified epsilon tolerance
// triangles: array of triangles
// triangle_count: number of triangles
// epsilon: tolerance for vertex comparison (use 0.0 for exact comparison)
// vertices: output buffer for unique vertices
// vertex_buffer_size: size of vertices buffer in number of vertices
// indices: output buffer for indices
// index_buffer_size: size of indices buffer in number of indices
LM2_API void lm2_triangle2_list_to_indexed_mesh_f64(
    const lm2_triangle2_f64* triangles,
    size_t triangle_count,
    double epsilon,
    lm2_v2_f64* vertices,
    size_t vertex_buffer_size,
    uint32_t* indices,
    size_t index_buffer_size);

LM2_API void lm2_triangle2_list_to_indexed_mesh_f32(
    const lm2_triangle2_f32* triangles,
    size_t triangle_count,
    float epsilon,
    lm2_v2_f32* vertices,
    size_t vertex_buffer_size,
    uint32_t* indices,
    size_t index_buffer_size);

// =============================================================================
// Indexed Mesh to Triangle List Conversion (Inverse)
// =============================================================================

// Query the number of triangles from an indexed mesh
// index_count must be divisible by 3
// Returns: number of triangles (index_count / 3)
LM2_API size_t lm2_indexed_mesh_to_triangle_list_size_f64(size_t index_count);
LM2_API size_t lm2_indexed_mesh_to_triangle_list_size_f32(size_t index_count);

// Generate triangle list from indexed mesh
// vertices: array of unique vertices
// vertex_count: number of vertices
// indices: array of indices (must be divisible by 3)
// index_count: number of indices
// triangles: output buffer for triangles (must be at least index_count / 3)
// triangle_buffer_size: size of triangles buffer in number of triangles
LM2_API void lm2_indexed_mesh_to_triangle_list_f64(
    const lm2_v2_f64* vertices,
    size_t vertex_count,
    const uint32_t* indices,
    size_t index_count,
    lm2_triangle2_f64* triangles,
    size_t triangle_buffer_size);

LM2_API void lm2_indexed_mesh_to_triangle_list_f32(
    const lm2_v2_f32* vertices,
    size_t vertex_count,
    const uint32_t* indices,
    size_t index_count,
    lm2_triangle2_f32* triangles,
    size_t triangle_buffer_size);

// #############################################################################
LM2_HEADER_END;
