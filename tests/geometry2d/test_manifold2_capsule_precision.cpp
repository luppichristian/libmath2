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
#include "lm2/geometry2d/lm2_manifold2.h"

TEST(CapsuleManifoldPrecisionTest, LargeCoordinatesPreserveSmallOverlapAndContact) {
  constexpr double x = 16777216.0;
  const lm2_capsule2_f64 a = {
      {    x, 0},
      {x + 1, 0},
      0.5
  };
  const lm2_capsule2_f64 b = {
      {x + 1.75, 0},
      {x + 2.75, 0},
      0.5
  };
  lm2_manifold_f64 hit = {};
  lm2_manifold_capsule_to_capsule_f64(a, b, &hit);
  ASSERT_EQ(hit.count, 1);
  EXPECT_DOUBLE_EQ(hit.depths[0], 0.25);
  EXPECT_DOUBLE_EQ(hit.normal.x, 1.0);
  EXPECT_DOUBLE_EQ(hit.normal.y, 0.0);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].x, x + 1.25);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].y, 0.0);
}

TEST(CapsuleManifoldPrecisionTest, TangencyAndCrossingFollowBackendConventions) {
  const lm2_capsule2_f64 a = {
      {0, 0},
      {2, 0},
      0.5
  };
  lm2_capsule2_f64 b = {
      {3, 0},
      {4, 0},
      0.5
  };
  lm2_manifold_f64 hit = {};
  lm2_manifold_capsule_to_capsule_f64(a, b, &hit);
  EXPECT_EQ(hit.count, 0);
  b = {
      {1, -1},
      {1,  1},
      0.25
  };
  lm2_manifold_capsule_to_capsule_f64(a, b, &hit);
  ASSERT_EQ(hit.count, 1);
  EXPECT_DOUBLE_EQ(hit.depths[0], 0.75);
  EXPECT_DOUBLE_EQ(hit.normal.x, 0.0);
  EXPECT_DOUBLE_EQ(hit.normal.y, 1.0);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].x, 1.0);
  EXPECT_DOUBLE_EQ(hit.contact_points[0].y, -0.25);
}

TEST(CapsuleManifoldPrecisionTest, DegenerateSegmentsRemainFinite) {
  const lm2_capsule2_f64 a = {
      {0, 0},
      {0, 0},
      1
  };
  const lm2_capsule2_f64 b = {
      {0, 0},
      {0, 0},
      0.5
  };
  lm2_manifold_f64 hit = {};
  lm2_manifold_capsule_to_capsule_f64(a, b, &hit);
  ASSERT_EQ(hit.count, 1);
  EXPECT_DOUBLE_EQ(hit.depths[0], 1.5);
  EXPECT_TRUE(std::isfinite(hit.normal.x));
  EXPECT_TRUE(std::isfinite(hit.normal.y));
  EXPECT_NEAR(std::hypot(hit.normal.x, hit.normal.y), 1.0, 1e-14);
}

TEST(CapsuleManifoldPrecisionTest, ParallelAndEndpointContactsReverseDirection) {
  const lm2_capsule2_f64 a = {
      {0, 0},
      {2, 0},
      0.5
  };
  const lm2_capsule2_f64 b = {
      {1, 0.75},
      {3, 0.75},
      0.5
  };
  lm2_manifold_f64 forward = {}, reverse = {};
  lm2_manifold_capsule_to_capsule_f64(a, b, &forward);
  lm2_manifold_capsule_to_capsule_f64(b, a, &reverse);
  ASSERT_EQ(forward.count, 1);
  ASSERT_EQ(reverse.count, 1);
  EXPECT_DOUBLE_EQ(forward.depths[0], 0.25);
  EXPECT_DOUBLE_EQ(reverse.depths[0], 0.25);
  EXPECT_DOUBLE_EQ(forward.normal.x, 0.0);
  EXPECT_DOUBLE_EQ(forward.normal.y, 1.0);
  EXPECT_DOUBLE_EQ(reverse.normal.x, 0.0);
  EXPECT_DOUBLE_EQ(reverse.normal.y, -1.0);
  EXPECT_DOUBLE_EQ(forward.contact_points[0].y, 0.25);
  EXPECT_DOUBLE_EQ(reverse.contact_points[0].y, 0.5);
}

TEST(CapsuleManifoldPrecisionTest, TinyAxesAndGapsPreserveContact) {
  const lm2_capsule2_f64 a = {
      {     0, 0},
      {2e-200, 0},
      0.5e-200
  };
  const lm2_capsule2_f64 b = {
      {3e-200, 0},
      {4e-200, 0},
      0.75e-200
  };
  lm2_manifold_f64 hit = {};
  lm2_manifold_capsule_to_capsule_f64(a, b, &hit);
  ASSERT_EQ(hit.count, 1);
  EXPECT_NEAR(hit.depths[0] / 1e-200, 0.25, 1e-14);
  EXPECT_DOUBLE_EQ(hit.normal.x, 1.0);
  EXPECT_DOUBLE_EQ(hit.normal.y, 0.0);
}

TEST(CapsuleManifoldPrecisionTest, SeparatedAxesUseClosestEndpointAndSurfaceOfB) {
  const lm2_capsule2_f64 a = {
      {0, 0},
      {2, 0},
      1
  };
  const lm2_capsule2_f64 b = {
      {3, 1},
      {3, 2},
      0.5
  };
  lm2_manifold_f64 hit = {};
  lm2_manifold_capsule_to_capsule_f64(a, b, &hit);
  ASSERT_EQ(hit.count, 1);
  const double component = 1.0 / std::sqrt(2.0);
  EXPECT_NEAR(hit.depths[0], 1.5 - std::sqrt(2.0), 1e-14);
  EXPECT_NEAR(hit.normal.x, component, 1e-14);
  EXPECT_NEAR(hit.normal.y, component, 1e-14);
  EXPECT_NEAR(hit.contact_points[0].x, 3.0 - 0.5 * component, 1e-14);
  EXPECT_NEAR(hit.contact_points[0].y, 1.0 - 0.5 * component, 1e-14);
}
