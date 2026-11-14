#include <cstdint>
#include <gtest/gtest.h>
#include <limits>
#include "lm2/geometry2d/lm2_aabb2.h"

TEST(IntegerSegmentIntersection, SignedFractionalParametersDoNotTruncateToHit) {
  EXPECT_EQ(lm2_segments_intersect_i32({0, 0}, {3, 0}, {4, -1}, {4, 2}), 0);
}

#define LM2_TEST_INTEGER_SEGMENTS(suffix)                                          \
  TEST(IntegerSegmentIntersection, Cases_##suffix) {                               \
    EXPECT_EQ(lm2_segments_intersect_##suffix({0, 0}, {6, 6}, {0, 6}, {6, 0}), 1); \
    EXPECT_EQ(lm2_segments_intersect_##suffix({6, 6}, {0, 0}, {6, 0}, {0, 6}), 1); \
    EXPECT_EQ(lm2_segments_intersect_##suffix({0, 0}, {3, 0}, {4, 0}, {6, 0}), 0); \
    EXPECT_EQ(lm2_segments_intersect_##suffix({0, 0}, {4, 0}, {2, 0}, {6, 0}), 1); \
    EXPECT_EQ(lm2_segments_intersect_##suffix({0, 0}, {4, 0}, {4, 0}, {4, 5}), 1); \
    EXPECT_EQ(lm2_segments_intersect_##suffix({2, 0}, {2, 0}, {0, 0}, {4, 0}), 1); \
    EXPECT_EQ(lm2_segments_intersect_##suffix({2, 1}, {2, 1}, {0, 0}, {4, 0}), 0); \
  }

LM2_TEST_INTEGER_SEGMENTS(i8)
LM2_TEST_INTEGER_SEGMENTS(i16)
LM2_TEST_INTEGER_SEGMENTS(i32)
LM2_TEST_INTEGER_SEGMENTS(i64)
LM2_TEST_INTEGER_SEGMENTS(u8)
LM2_TEST_INTEGER_SEGMENTS(u16)
LM2_TEST_INTEGER_SEGMENTS(u32)
LM2_TEST_INTEGER_SEGMENTS(u64)

TEST(IntegerSegmentIntersection, HandlesExtremeCoordinatesExactly) {
  constexpr auto lo = std::numeric_limits<int64_t>::min();
  constexpr auto hi = std::numeric_limits<int64_t>::max();
  constexpr auto umax = std::numeric_limits<uint64_t>::max();
  EXPECT_EQ(lm2_segments_intersect_i64({lo, lo}, {hi, hi}, {lo, hi}, {hi, lo}), 1);
  EXPECT_EQ(lm2_segments_intersect_i64({lo, lo}, {hi - 1, hi - 1}, {hi, hi}, {hi, hi}), 0);
  EXPECT_EQ(lm2_segments_intersect_u64({0, 0}, {umax, umax}, {0, umax}, {umax, 0}), 1);
  EXPECT_EQ(lm2_segments_intersect_u64({0, 0}, {umax - 1, umax - 1}, {umax, umax}, {umax, umax}), 0);
}
