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
#include <algorithm>
#include <cmath>
#include <limits>
#include "lm2/misc/lm2_noise.h"

// Test fixture for noise tests
class NoiseTest : public ::testing::Test {
 protected:
  static constexpr float EPSILON_F32 = 1e-5f;
  static constexpr double EPSILON_F64 = 1e-10;
};

// =============================================================================
// Perlin Noise 2D Tests - F64
// =============================================================================

TEST_F(NoiseTest, Perlin2_F64_Deterministic) {
  double x = 3.7, y = 2.5;

  double result1 = lm2_perlin2_f64(x, y);
  double result2 = lm2_perlin2_f64(x, y);

  // Same input should produce same output
  EXPECT_DOUBLE_EQ(result1, result2);
}

TEST_F(NoiseTest, Perlin2_F64_Range) {
  // Test multiple points to verify range [-1, 1]
  for (double x = -10.0; x <= 10.0; x += 1.0) {
    for (double y = -10.0; y <= 10.0; y += 1.0) {
      double result = lm2_perlin2_f64(x, y);
      EXPECT_GE(result, -1.0) << "At (" << x << ", " << y << ")";
      EXPECT_LE(result, 1.0) << "At (" << x << ", " << y << ")";
    }
  }
}

TEST_F(NoiseTest, Perlin2_F64_Continuity) {
  // Nearby points should have similar values (continuity)
  double x = 5.5, y = 3.3;
  double epsilon = 0.01;

  double center = lm2_perlin2_f64(x, y);
  double right = lm2_perlin2_f64(x + epsilon, y);
  double up = lm2_perlin2_f64(x, y + epsilon);

  // Values should be close (continuous)
  EXPECT_LT(std::abs(center - right), 0.1);
  EXPECT_LT(std::abs(center - up), 0.1);
}

TEST_F(NoiseTest, Perlin2_F64_NotConstant) {
  // Perlin noise should vary across space (use non-integer coordinates)
  double v1 = lm2_perlin2_f64(0.5, 0.5);
  double v2 = lm2_perlin2_f64(10.5, 0.5);
  double v3 = lm2_perlin2_f64(0.5, 10.5);
  double v4 = lm2_perlin2_f64(10.5, 10.5);

  // At least some values should be different
  bool has_variation = (v1 != v2) || (v1 != v3) || (v1 != v4);
  EXPECT_TRUE(has_variation);
}

TEST_F(NoiseTest, Perlin2_F64_DifferentPositions) {
  double result1 = lm2_perlin2_f64(1.5, 2.5);
  double result2 = lm2_perlin2_f64(3.5, 4.5);

  // Different positions should (very likely) produce different values
  EXPECT_NE(result1, result2);
}

// =============================================================================
// Perlin Noise 2D Tests - F32
// =============================================================================

TEST_F(NoiseTest, Perlin2_F32_Deterministic) {
  float x = 3.7f, y = 2.5f;

  float result1 = lm2_perlin2_f32(x, y);
  float result2 = lm2_perlin2_f32(x, y);

  EXPECT_FLOAT_EQ(result1, result2);
}

TEST_F(NoiseTest, Perlin2_F32_Range) {
  for (float x = -10.0f; x <= 10.0f; x += 1.0f) {
    for (float y = -10.0f; y <= 10.0f; y += 1.0f) {
      float result = lm2_perlin2_f32(x, y);
      EXPECT_GE(result, -1.0f) << "At (" << x << ", " << y << ")";
      EXPECT_LE(result, 1.0f) << "At (" << x << ", " << y << ")";
    }
  }
}

TEST_F(NoiseTest, Perlin2_F32_Continuity) {
  float x = 5.5f, y = 3.3f;
  float epsilon = 0.01f;

  float center = lm2_perlin2_f32(x, y);
  float right = lm2_perlin2_f32(x + epsilon, y);
  float up = lm2_perlin2_f32(x, y + epsilon);

  EXPECT_LT(std::abs(center - right), 0.1f);
  EXPECT_LT(std::abs(center - up), 0.1f);
}

TEST_F(NoiseTest, Perlin2_F32_NotConstant) {
  // Use non-integer coordinates to avoid lattice points where noise is zero
  float v1 = lm2_perlin2_f32(0.5f, 0.5f);
  float v2 = lm2_perlin2_f32(10.5f, 0.5f);
  float v3 = lm2_perlin2_f32(0.5f, 10.5f);

  bool has_variation = (v1 != v2) || (v1 != v3);
  EXPECT_TRUE(has_variation);
}

// =============================================================================
// Perlin Noise 3D Tests - F64
// =============================================================================

TEST_F(NoiseTest, Perlin3_F64_Deterministic) {
  double x = 3.7, y = 2.5, z = 1.2;

  double result1 = lm2_perlin3_f64(x, y, z);
  double result2 = lm2_perlin3_f64(x, y, z);

  EXPECT_DOUBLE_EQ(result1, result2);
}

TEST_F(NoiseTest, Perlin3_F64_Range) {
  for (double x = -5.0; x <= 5.0; x += 2.0) {
    for (double y = -5.0; y <= 5.0; y += 2.0) {
      for (double z = -5.0; z <= 5.0; z += 2.0) {
        double result = lm2_perlin3_f64(x, y, z);
        EXPECT_GE(result, -1.0) << "At (" << x << ", " << y << ", " << z << ")";
        EXPECT_LE(result, 1.0) << "At (" << x << ", " << y << ", " << z << ")";
      }
    }
  }
}

TEST_F(NoiseTest, Perlin3_F64_Continuity) {
  double x = 5.5, y = 3.3, z = 2.2;
  double epsilon = 0.01;

  double center = lm2_perlin3_f64(x, y, z);
  double right = lm2_perlin3_f64(x + epsilon, y, z);
  double up = lm2_perlin3_f64(x, y + epsilon, z);
  double forward = lm2_perlin3_f64(x, y, z + epsilon);

  EXPECT_LT(std::abs(center - right), 0.1);
  EXPECT_LT(std::abs(center - up), 0.1);
  EXPECT_LT(std::abs(center - forward), 0.1);
}

TEST_F(NoiseTest, Perlin3_F64_NotConstant) {
  // Use non-integer coordinates to avoid lattice points where noise is zero
  double v1 = lm2_perlin3_f64(0.5, 0.5, 0.5);
  double v2 = lm2_perlin3_f64(10.5, 0.5, 0.5);
  double v3 = lm2_perlin3_f64(0.5, 10.5, 0.5);
  double v4 = lm2_perlin3_f64(0.5, 0.5, 10.5);

  bool has_variation = (v1 != v2) || (v1 != v3) || (v1 != v4);
  EXPECT_TRUE(has_variation);
}

TEST_F(NoiseTest, Perlin3_F64_DifferentPositions) {
  double result1 = lm2_perlin3_f64(1.5, 2.5, 3.5);
  double result2 = lm2_perlin3_f64(4.5, 5.5, 6.5);

  EXPECT_NE(result1, result2);
}

// =============================================================================
// Perlin Noise 3D Tests - F32
// =============================================================================

TEST_F(NoiseTest, Perlin3_F32_Deterministic) {
  float x = 3.7f, y = 2.5f, z = 1.2f;

  float result1 = lm2_perlin3_f32(x, y, z);
  float result2 = lm2_perlin3_f32(x, y, z);

  EXPECT_FLOAT_EQ(result1, result2);
}

TEST_F(NoiseTest, Perlin3_F32_Range) {
  for (float x = -5.0f; x <= 5.0f; x += 2.0f) {
    for (float y = -5.0f; y <= 5.0f; y += 2.0f) {
      for (float z = -5.0f; z <= 5.0f; z += 2.0f) {
        float result = lm2_perlin3_f32(x, y, z);
        EXPECT_GE(result, -1.0f);
        EXPECT_LE(result, 1.0f);
      }
    }
  }
}

TEST_F(NoiseTest, Perlin3_F32_Continuity) {
  float x = 5.5f, y = 3.3f, z = 2.2f;
  float epsilon = 0.01f;

  float center = lm2_perlin3_f32(x, y, z);
  float right = lm2_perlin3_f32(x + epsilon, y, z);

  EXPECT_LT(std::abs(center - right), 0.1f);
}

// =============================================================================
// Voronoi Noise 2D Tests - F64
// =============================================================================

TEST_F(NoiseTest, Voronoi2_F64_Deterministic) {
  double x = 3.7, y = 2.5;

  double result1 = lm2_voronoi2_f64(x, y);
  double result2 = lm2_voronoi2_f64(x, y);

  EXPECT_DOUBLE_EQ(result1, result2);
}

TEST_F(NoiseTest, Voronoi2_F64_NonNegative) {
  // Voronoi returns distance, which should be non-negative
  for (double x = -10.0; x <= 10.0; x += 1.0) {
    for (double y = -10.0; y <= 10.0; y += 1.0) {
      double result = lm2_voronoi2_f64(x, y);
      EXPECT_GE(result, 0.0) << "At (" << x << ", " << y << ")";
    }
  }
}

TEST_F(NoiseTest, Voronoi2_F64_UpperBound) {
  // Voronoi distance should be reasonable (not infinite)
  for (double x = -10.0; x <= 10.0; x += 1.0) {
    for (double y = -10.0; y <= 10.0; y += 1.0) {
      double result = lm2_voronoi2_f64(x, y);
      EXPECT_LT(result, 10.0) << "At (" << x << ", " << y << ")";
    }
  }
}

TEST_F(NoiseTest, Voronoi2_F64_NotConstant) {
  double v1 = lm2_voronoi2_f64(0.0, 0.0);
  double v2 = lm2_voronoi2_f64(10.0, 0.0);
  double v3 = lm2_voronoi2_f64(0.0, 10.0);

  bool has_variation = (v1 != v2) || (v1 != v3);
  EXPECT_TRUE(has_variation);
}

TEST_F(NoiseTest, Voronoi2_F64_DifferentPositions) {
  double result1 = lm2_voronoi2_f64(1.5, 2.5);
  double result2 = lm2_voronoi2_f64(3.5, 4.5);

  // Different positions should (very likely) produce different values
  EXPECT_NE(result1, result2);
}

// =============================================================================
// Voronoi Noise 2D Tests - F32
// =============================================================================

TEST_F(NoiseTest, Voronoi2_F32_Deterministic) {
  float x = 3.7f, y = 2.5f;

  float result1 = lm2_voronoi2_f32(x, y);
  float result2 = lm2_voronoi2_f32(x, y);

  EXPECT_FLOAT_EQ(result1, result2);
}

TEST_F(NoiseTest, Voronoi2_F32_NonNegative) {
  for (float x = -10.0f; x <= 10.0f; x += 1.0f) {
    for (float y = -10.0f; y <= 10.0f; y += 1.0f) {
      float result = lm2_voronoi2_f32(x, y);
      EXPECT_GE(result, 0.0f) << "At (" << x << ", " << y << ")";
    }
  }
}

TEST_F(NoiseTest, Voronoi2_F32_UpperBound) {
  for (float x = -10.0f; x <= 10.0f; x += 1.0f) {
    for (float y = -10.0f; y <= 10.0f; y += 1.0f) {
      float result = lm2_voronoi2_f32(x, y);
      EXPECT_LT(result, 10.0f) << "At (" << x << ", " << y << ")";
    }
  }
}

TEST_F(NoiseTest, Voronoi2_F32_NotConstant) {
  float v1 = lm2_voronoi2_f32(0.0f, 0.0f);
  float v2 = lm2_voronoi2_f32(10.0f, 0.0f);

  EXPECT_NE(v1, v2);
}

// =============================================================================
// Voronoi Noise 3D Tests - F64
// =============================================================================

TEST_F(NoiseTest, Voronoi3_F64_Deterministic) {
  double x = 3.7, y = 2.5, z = 1.2;

  double result1 = lm2_voronoi3_f64(x, y, z);
  double result2 = lm2_voronoi3_f64(x, y, z);

  EXPECT_DOUBLE_EQ(result1, result2);
}

TEST_F(NoiseTest, Voronoi3_F64_NonNegative) {
  for (double x = -5.0; x <= 5.0; x += 2.0) {
    for (double y = -5.0; y <= 5.0; y += 2.0) {
      for (double z = -5.0; z <= 5.0; z += 2.0) {
        double result = lm2_voronoi3_f64(x, y, z);
        EXPECT_GE(result, 0.0);
      }
    }
  }
}

TEST_F(NoiseTest, Voronoi3_F64_UpperBound) {
  for (double x = -5.0; x <= 5.0; x += 2.0) {
    for (double y = -5.0; y <= 5.0; y += 2.0) {
      for (double z = -5.0; z <= 5.0; z += 2.0) {
        double result = lm2_voronoi3_f64(x, y, z);
        EXPECT_LT(result, 10.0);
      }
    }
  }
}

TEST_F(NoiseTest, Voronoi3_F64_NotConstant) {
  double v1 = lm2_voronoi3_f64(0.0, 0.0, 0.0);
  double v2 = lm2_voronoi3_f64(10.0, 0.0, 0.0);
  double v3 = lm2_voronoi3_f64(0.0, 10.0, 0.0);

  bool has_variation = (v1 != v2) || (v1 != v3);
  EXPECT_TRUE(has_variation);
}

TEST_F(NoiseTest, Voronoi3_F64_DifferentPositions) {
  double result1 = lm2_voronoi3_f64(1.5, 2.5, 3.5);
  double result2 = lm2_voronoi3_f64(4.5, 5.5, 6.5);

  EXPECT_NE(result1, result2);
}

// =============================================================================
// Voronoi Noise 3D Tests - F32
// =============================================================================

TEST_F(NoiseTest, Voronoi3_F32_Deterministic) {
  float x = 3.7f, y = 2.5f, z = 1.2f;

  float result1 = lm2_voronoi3_f32(x, y, z);
  float result2 = lm2_voronoi3_f32(x, y, z);

  EXPECT_FLOAT_EQ(result1, result2);
}

TEST_F(NoiseTest, Voronoi3_F32_NonNegative) {
  for (float x = -5.0f; x <= 5.0f; x += 2.0f) {
    for (float y = -5.0f; y <= 5.0f; y += 2.0f) {
      for (float z = -5.0f; z <= 5.0f; z += 2.0f) {
        float result = lm2_voronoi3_f32(x, y, z);
        EXPECT_GE(result, 0.0f);
      }
    }
  }
}

TEST_F(NoiseTest, Voronoi3_F32_UpperBound) {
  for (float x = -5.0f; x <= 5.0f; x += 2.0f) {
    for (float y = -5.0f; y <= 5.0f; y += 2.0f) {
      for (float z = -5.0f; z <= 5.0f; z += 2.0f) {
        float result = lm2_voronoi3_f32(x, y, z);
        EXPECT_LT(result, 10.0f);
      }
    }
  }
}

TEST_F(NoiseTest, Voronoi3_F32_NotConstant) {
  float v1 = lm2_voronoi3_f32(0.0f, 0.0f, 0.0f);
  float v2 = lm2_voronoi3_f32(10.0f, 0.0f, 0.0f);

  EXPECT_NE(v1, v2);
}

// =============================================================================
// Comparison Tests
// =============================================================================

TEST_F(NoiseTest, Perlin2_vs_Perlin3_SameXY) {
  // 2D and 3D versions should give different results even with same x,y
  double result_2d = lm2_perlin2_f64(5.5, 3.3);
  double result_3d = lm2_perlin3_f64(5.5, 3.3, 0.0);

  // They're different noise functions, so should differ
  EXPECT_NE(result_2d, result_3d);
}

TEST_F(NoiseTest, Perlin_vs_Voronoi) {
  // Perlin and Voronoi are very different noise types
  double perlin = lm2_perlin2_f64(5.5, 3.3);
  double voronoi = lm2_voronoi2_f64(5.5, 3.3);

  // Perlin is in [-1, 1], Voronoi is in [0, inf)
  // They should generally differ in character
  EXPECT_GE(voronoi, 0.0);
}

TEST_F(NoiseTest, PerlinFractionalGridStaysWithinDocumentedRange) {
  for (int ix = -12; ix <= 12; ++ix) {
    for (int iy = -12; iy <= 12; ++iy) {
      const double x = ix * 0.25 + 0.125;
      const double y = iy * 0.25 + 0.125;
      const double v2 = lm2_perlin2_f64(x, y);
      const float v2f = lm2_perlin2_f32((float)x, (float)y);
      EXPECT_GE(v2, -1.0);
      EXPECT_LE(v2, 1.0);
      EXPECT_GE(v2f, -1.0f);
      EXPECT_LE(v2f, 1.0f);
      EXPECT_NEAR(v2f, v2, 2e-6);
      for (int iz = -4; iz <= 4; ++iz) {
        const double z = iz * 0.5 + 0.125;
        const double v3 = lm2_perlin3_f64(x, y, z);
        const float v3f = lm2_perlin3_f32((float)x, (float)y, (float)z);
        EXPECT_GE(v3, -1.0);
        EXPECT_LE(v3, 1.0);
        EXPECT_GE(v3f, -1.0f);
        EXPECT_LE(v3f, 1.0f);
        EXPECT_NEAR(v3f, v3, 2e-6);
      }
    }
  }
}

TEST_F(NoiseTest, PerlinIsContinuousAcrossPositiveAndNegativeLatticeBoundaries) {
  constexpr double delta = 1e-5;
  for (int boundary = -3; boundary <= 3; ++boundary) {
    const double x = boundary;
    EXPECT_NEAR(lm2_perlin2_f64(x - delta, 0.375), lm2_perlin2_f64(x + delta, 0.375), 5e-5);
    EXPECT_NEAR(lm2_perlin2_f64(0.375, x - delta), lm2_perlin2_f64(0.375, x + delta), 5e-5);
    EXPECT_NEAR(lm2_perlin3_f64(x - delta, 0.375, -0.625), lm2_perlin3_f64(x + delta, 0.375, -0.625), 5e-5);
    EXPECT_NEAR(lm2_perlin3_f64(0.375, x - delta, -0.625), lm2_perlin3_f64(0.375, x + delta, -0.625), 5e-5);
    EXPECT_NEAR(lm2_perlin3_f64(0.375, -0.625, x - delta), lm2_perlin3_f64(0.375, -0.625, x + delta), 5e-5);
    EXPECT_NEAR(lm2_perlin2_f32((float)(x - delta), 0.375f), lm2_perlin2_f32((float)(x + delta), 0.375f), 5e-5f);
    EXPECT_NEAR(lm2_perlin3_f32((float)(x - delta), 0.375f, -0.625f), lm2_perlin3_f32((float)(x + delta), 0.375f, -0.625f), 5e-5f);
  }
}

TEST_F(NoiseTest, PerlinRepeatsAtLargeFiniteCoordinates) {
  // The permutation table repeats every 256 cells, including beyond int range.
  constexpr double x = 2147483712.25;
  constexpr double y = -2147483695.625;
  constexpr double z = 2147483679.5;
  EXPECT_NEAR(lm2_perlin2_f64(x, y), lm2_perlin2_f64(64.25, 208.375), 1e-12);
  EXPECT_NEAR(lm2_perlin3_f64(x, y, z), lm2_perlin3_f64(64.25, 208.375, 31.5), 1e-12);
  EXPECT_NEAR(lm2_perlin2_f32(2147483904.0f, 0.375f), lm2_perlin2_f32(0.0f, 0.375f), 1e-6f);
  EXPECT_NEAR(lm2_perlin3_f32(-2147483904.0f, 0.375f, -0.625f), lm2_perlin3_f32(0.0f, 0.375f, -0.625f), 1e-6f);
}

TEST_F(NoiseTest, VoronoiUsesWrappedCellsAtLargeCoordinates) {
  constexpr double period = 4294967296.0;
  EXPECT_NEAR(lm2_voronoi2_f64(period + 0.25, -period + 0.375), lm2_voronoi2_f64(0.25, 0.375), 1e-12);
  EXPECT_NEAR(lm2_voronoi3_f64(period + 0.25, -period + 0.375, period - 0.5), lm2_voronoi3_f64(0.25, 0.375, -0.5), 1e-12);
  EXPECT_NEAR(lm2_voronoi2_f32(4294967296.0f, 0.375f), lm2_voronoi2_f32(0.0f, 0.375f), 1e-6f);
  EXPECT_NEAR(lm2_voronoi3_f32(-4294967296.0f, 0.375f, -0.5f), lm2_voronoi3_f32(0.0f, 0.375f, -0.5f), 1e-6f);
}

TEST_F(NoiseTest, VoronoiMatchesIndependentCellSearch) {
  // Reference distances were calculated with a 5-by-5 (or 5-by-5-by-5)
  // cell search using the algorithm's hash constants and Euclidean distance.
  EXPECT_NEAR(lm2_voronoi2_f64(0.25, 0.375), 0.33190746301218804, 1e-12);
  EXPECT_NEAR(lm2_voronoi2_f64(-2.25, 3.75), 0.43670401691814004, 1e-12);
  EXPECT_NEAR(lm2_voronoi2_f64(7.125, -5.625), 0.69259318583578511, 1e-12);
  EXPECT_NEAR(lm2_voronoi3_f64(0.25, 0.375, -0.5), 0.22719968253974571, 1e-12);
  EXPECT_NEAR(lm2_voronoi3_f64(-2.25, 3.75, 1.125), 0.68871041548849632, 1e-12);
  EXPECT_NEAR(lm2_voronoi3_f64(7.125, -5.625, 2.875), 0.61112229755921432, 1e-12);
  EXPECT_NEAR(lm2_voronoi2_f32(-2.25f, 3.75f), 0.43670401691814004, 1e-6);
  EXPECT_NEAR(lm2_voronoi3_f32(7.125f, -5.625f, 2.875f), 0.61112229755921432, 1e-6);
}

TEST_F(NoiseTest, VoronoiSearchesBeyondImmediateNeighborsWhenNecessary) {
  // An independent five-by-five cell search finds the nearest feature in the
  // second cell ring here; a three-by-three search returns 1.0954591309.
  constexpr double x = 483.95473044365644;
  constexpr double y = -530.9488158673048;
  EXPECT_NEAR(lm2_voronoi2_f64(x, y), 1.0801618008275458, 1e-12);
  EXPECT_NEAR(lm2_voronoi2_f32((float)x, (float)y),
              lm2_voronoi2_f64((double)(float)x, (double)(float)y),
              2e-6);

  // The nearest 3D feature also lies in the second ring for this position.
  constexpr double x3 = 1926.0027213022113;
  constexpr double y3 = 4401.0350201278925;
  constexpr double z3 = -2461.7621628567576;
  EXPECT_NEAR(lm2_voronoi3_f64(x3, y3, z3), 1.0946613390482458, 1e-12);
  EXPECT_NEAR(lm2_voronoi3_f32((float)x3, (float)y3, (float)z3),
              lm2_voronoi3_f64((double)(float)x3, (double)(float)y3, (double)(float)z3),
              2e-6);
}

TEST_F(NoiseTest, PerlinAcceptsFiniteInputsThatProduceSubnormalIntermediates) {
  // Cubing these normal inputs produces subnormal fade terms.
  EXPECT_NEAR(lm2_perlin2_f32(1e-13f, 0.5f), lm2_perlin2_f32(0.0f, 0.5f), 1e-6f);
  EXPECT_NEAR(lm2_perlin3_f32(0.5f, 1e-13f, 0.25f), lm2_perlin3_f32(0.5f, 0.0f, 0.25f), 1e-6f);
  EXPECT_NEAR(lm2_perlin2_f64(1e-105, 0.5), lm2_perlin2_f64(0.0, 0.5), 1e-14);
  EXPECT_NEAR(lm2_perlin3_f64(0.5, 1e-105, 0.25), lm2_perlin3_f64(0.5, 0.0, 0.25), 1e-14);
}

TEST_F(NoiseTest, NoiseAcceptsSubnormalCoordinatesInEveryDimension) {
  const float f = std::numeric_limits<float>::denorm_min();
  const double d = std::numeric_limits<double>::denorm_min();
  for (float x : {f, -f}) {
    EXPECT_NEAR(lm2_perlin2_f32(x, 0.5f), lm2_perlin2_f32(0.0f, 0.5f), 1e-6f);
    EXPECT_NEAR(lm2_perlin3_f32(0.5f, x, 0.25f), lm2_perlin3_f32(0.5f, 0.0f, 0.25f), 1e-6f);
    EXPECT_NEAR(lm2_voronoi2_f32(x, 0.5f), lm2_voronoi2_f32(0.0f, 0.5f), 1e-6f);
    EXPECT_NEAR(lm2_voronoi3_f32(0.5f, x, 0.25f), lm2_voronoi3_f32(0.5f, 0.0f, 0.25f), 1e-6f);
  }
  for (double x : {d, -d}) {
    EXPECT_NEAR(lm2_perlin2_f64(x, 0.5), lm2_perlin2_f64(0.0, 0.5), 1e-14);
    EXPECT_NEAR(lm2_perlin3_f64(0.5, x, 0.25), lm2_perlin3_f64(0.5, 0.0, 0.25), 1e-14);
    EXPECT_NEAR(lm2_voronoi2_f64(x, 0.5), lm2_voronoi2_f64(0.0, 0.5), 1e-14);
    EXPECT_NEAR(lm2_voronoi3_f64(0.5, x, 0.25), lm2_voronoi3_f64(0.5, 0.0, 0.25), 1e-14);
  }
}

TEST_F(NoiseTest, VoronoiAcceptsSubnormalSquaredFeatureDistances) {
  // The (0,0) cell's feature has x=0 and this independently calculated y.
  const float feature_y_f32 = 0.5933175683021545f;
  const double feature_y_f64 = 1274139792.0 / 2147483647.0;
  EXPECT_NEAR(lm2_voronoi2_f32(1e-20f, feature_y_f32), 1e-20f, 1e-25f);
  EXPECT_NEAR(lm2_voronoi2_f64(1e-160, feature_y_f64), 1e-160, 1e-164);
  // Squaring these still-representable distances would underflow to zero.
  EXPECT_FLOAT_EQ(lm2_voronoi2_f32(1e-30f, feature_y_f32), 1e-30f);
  EXPECT_DOUBLE_EQ(lm2_voronoi2_f64(1e-200, feature_y_f64), 1e-200);
  const float feature_z_f32 = 0.18663515150547028f;
  const double feature_z_f64 = 400795937.0 / 2147483647.0;
  EXPECT_FLOAT_EQ(lm2_voronoi3_f32(1e-30f, feature_y_f32, feature_z_f32), 1e-30f);
  EXPECT_DOUBLE_EQ(lm2_voronoi3_f64(1e-200, feature_y_f64, feature_z_f64), 1e-200);
}
