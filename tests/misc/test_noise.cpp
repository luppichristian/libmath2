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
