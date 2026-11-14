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

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <vector>

#include <gtest/gtest.h>

#include "lm2/geometry2d/lm2_polygon.h"

namespace {

  uint32_t next_random(uint32_t& state) {
    state = state * 1664525u + 1013904223u;
    return state;
  }

  template <typename Vector>
  double twice_triangle_area(const Vector& a, const Vector& b, const Vector& c) {
    const double abx = static_cast<double>(b.x) - static_cast<double>(a.x);
    const double aby = static_cast<double>(b.y) - static_cast<double>(a.y);
    const double acx = static_cast<double>(c.x) - static_cast<double>(a.x);
    const double acy = static_cast<double>(c.y) - static_cast<double>(a.y);
    return abx * acy - aby * acx;
  }

  template <typename Vector, typename Polygon, size_t (*triangulate)(Polygon, size_t*)>
  void check_simple_polygons() {
    using Scalar = decltype(Vector {}.x);
    constexpr double tau = 6.283185307179586476925286766559;
    uint32_t state = 0x315f9a27u;

    for (size_t count = 3; count <= 15; ++count) {
      for (int sample = 0; sample < 20; ++sample) {
        SCOPED_TRACE(::testing::Message() << "vertices=" << count << ", sample=" << sample);
        std::vector<Vector> vertices(count);
        const double offset_x = sample % 3 == 0 ? 10000.0 : 0.0;
        const double offset_y = sample % 3 == 0 ? -10000.0 : 0.0;

        // Vertices are in strictly increasing angular order around a common
        // interior point, with positive radii and every angular gap below pi.
        // The resulting polygon is simple, while varied radii produce concavity.
        for (size_t i = 0; i < count; ++i) {
          const double jitter = (static_cast<double>(next_random(state) % 1001u) / 1000.0 - 0.5) * 0.15;
          const double radius = 0.5 + static_cast<double>(next_random(state) % 9501u) / 1000.0;
          const double angle = tau * (static_cast<double>(i) + jitter) / static_cast<double>(count);
          vertices[i].x = static_cast<Scalar>(offset_x + radius * std::cos(angle));
          vertices[i].y = static_cast<Scalar>(offset_y + radius * std::sin(angle));
        }
        if (sample % 2 != 0) std::reverse(vertices.begin(), vertices.end());

        // Independently calculate polygon area using a fan of signed cross
        // products; unlike the tested routine, this does not triangulate it.
        double polygon_twice_area = 0.0;
        for (size_t i = 1; i + 1 < count; ++i) {
          polygon_twice_area += twice_triangle_area(vertices[0], vertices[i], vertices[i + 1]);
        }

        Polygon polygon = {vertices.data(), count};
        std::vector<size_t> indices(3 * (count - 2), count);
        const size_t triangle_count = triangulate(polygon, indices.data());
        ASSERT_EQ(triangle_count, count - 2);
        double triangles_twice_area = 0.0;
        for (size_t i = 0; i < triangle_count; ++i) {
          const size_t a = indices[3 * i];
          const size_t b = indices[3 * i + 1];
          const size_t c = indices[3 * i + 2];
          ASSERT_LT(a, count);
          ASSERT_LT(b, count);
          ASSERT_LT(c, count);
          const double area = twice_triangle_area(vertices[a], vertices[b], vertices[c]);
          EXPECT_GT(area * polygon_twice_area, 0.0);
          triangles_twice_area += std::abs(area);
        }
        EXPECT_NEAR(triangles_twice_area, std::abs(polygon_twice_area), 1e-10 * std::max(1.0, std::abs(polygon_twice_area)));
      }
    }
  }

}  // namespace

TEST(PolygonTriangulationProperties, ConservesAreaForSimpleF64Polygons) {
  check_simple_polygons<lm2_v2_f64, lm2_polygon_f64, lm2_polygon_triangulate_ear_clipping_f64>();
}

TEST(PolygonTriangulationProperties, ConservesAreaForSimpleF32Polygons) {
  check_simple_polygons<lm2_v2_f32, lm2_polygon_f32, lm2_polygon_triangulate_ear_clipping_f32>();
}
