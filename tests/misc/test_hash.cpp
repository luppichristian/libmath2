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
#include <cstring>
#include <set>
#include "lm2/misc/lm2_hash.h"

// Test fixture for hash tests
class HashTest : public ::testing::Test {
 protected:
  // Helper to check if hash is non-zero (good distribution indicator)
  template<typename T>
  bool is_non_zero(T hash) {
    return hash != 0;
  }
};

// =============================================================================
// Low-Level Bit-Mixing Tests
// =============================================================================

TEST_F(HashTest, MixU64_Deterministic) {
  uint64_t value = 12345678901234ULL;
  uint64_t hash1 = lm2_hash_mix_u64(value);
  uint64_t hash2 = lm2_hash_mix_u64(value);
  
  // Same input should produce same output
  EXPECT_EQ(hash1, hash2);
}

TEST_F(HashTest, MixU64_Different) {
  uint64_t hash1 = lm2_hash_mix_u64(12345ULL);
  uint64_t hash2 = lm2_hash_mix_u64(12346ULL);
  
  // Different inputs should (very likely) produce different outputs
  EXPECT_NE(hash1, hash2);
}

TEST_F(HashTest, MixU64_Zero) {
  uint64_t hash = lm2_hash_mix_u64(0);
  // Even zero should produce a non-zero hash
  EXPECT_NE(hash, 0ULL);
}

TEST_F(HashTest, MixU32_Deterministic) {
  uint32_t value = 123456789U;
  uint32_t hash1 = lm2_hash_mix_u32(value);
  uint32_t hash2 = lm2_hash_mix_u32(value);
  
  EXPECT_EQ(hash1, hash2);
}

TEST_F(HashTest, MixU32_Different) {
  uint32_t hash1 = lm2_hash_mix_u32(12345U);
  uint32_t hash2 = lm2_hash_mix_u32(12346U);
  
  EXPECT_NE(hash1, hash2);
}

TEST_F(HashTest, MixU32_Zero) {
  uint32_t hash = lm2_hash_mix_u32(0);
  EXPECT_NE(hash, 0U);
}

// =============================================================================
// Floating Point Hash Tests
// =============================================================================

TEST_F(HashTest, HashF64_Deterministic) {
  double value = 3.14159265358979;
  uint64_t hash1 = lm2_hash_f64(value);
  uint64_t hash2 = lm2_hash_f64(value);
  
  EXPECT_EQ(hash1, hash2);
}

TEST_F(HashTest, HashF64_Different) {
  uint64_t hash1 = lm2_hash_f64(3.14159);
  uint64_t hash2 = lm2_hash_f64(3.14160);
  
  EXPECT_NE(hash1, hash2);
}

TEST_F(HashTest, HashF64_SpecialValues) {
  uint64_t hash_zero = lm2_hash_f64(0.0);
  uint64_t hash_one = lm2_hash_f64(1.0);
  uint64_t hash_neg_one = lm2_hash_f64(-1.0);
  
  // All should be different
  EXPECT_NE(hash_zero, hash_one);
  EXPECT_NE(hash_one, hash_neg_one);
  EXPECT_NE(hash_zero, hash_neg_one);
}

TEST_F(HashTest, HashF32_Deterministic) {
  float value = 3.14159f;
  uint32_t hash1 = lm2_hash_f32(value);
  uint32_t hash2 = lm2_hash_f32(value);
  
  EXPECT_EQ(hash1, hash2);
}

TEST_F(HashTest, HashF32_Different) {
  uint32_t hash1 = lm2_hash_f32(3.14f);
  uint32_t hash2 = lm2_hash_f32(3.15f);
  
  EXPECT_NE(hash1, hash2);
}

// =============================================================================
// Integer Hash Tests - 64-bit
// =============================================================================

TEST_F(HashTest, HashI64_Deterministic) {
  int64_t value = -123456789012345LL;
  uint64_t hash1 = lm2_hash_i64(value);
  uint64_t hash2 = lm2_hash_i64(value);
  
  EXPECT_EQ(hash1, hash2);
}

TEST_F(HashTest, HashI64_Different) {
  uint64_t hash1 = lm2_hash_i64(100LL);
  uint64_t hash2 = lm2_hash_i64(101LL);
  
  EXPECT_NE(hash1, hash2);
}

TEST_F(HashTest, HashI64_SignMatters) {
  uint64_t hash_pos = lm2_hash_i64(12345LL);
  uint64_t hash_neg = lm2_hash_i64(-12345LL);
  
  EXPECT_NE(hash_pos, hash_neg);
}

TEST_F(HashTest, HashU64_Deterministic) {
  uint64_t value = 9876543210987654ULL;
  uint64_t hash1 = lm2_hash_u64(value);
  uint64_t hash2 = lm2_hash_u64(value);
  
  EXPECT_EQ(hash1, hash2);
}

TEST_F(HashTest, HashU64_Different) {
  uint64_t hash1 = lm2_hash_u64(1000ULL);
  uint64_t hash2 = lm2_hash_u64(1001ULL);
  
  EXPECT_NE(hash1, hash2);
}

// =============================================================================
// Integer Hash Tests - 32-bit
// =============================================================================

TEST_F(HashTest, HashI32_Deterministic) {
  int32_t value = -987654321;
  uint32_t hash1 = lm2_hash_i32(value);
  uint32_t hash2 = lm2_hash_i32(value);
  
  EXPECT_EQ(hash1, hash2);
}

TEST_F(HashTest, HashI32_Different) {
  uint32_t hash1 = lm2_hash_i32(100);
  uint32_t hash2 = lm2_hash_i32(101);
  
  EXPECT_NE(hash1, hash2);
}

TEST_F(HashTest, HashI32_SignMatters) {
  uint32_t hash_pos = lm2_hash_i32(12345);
  uint32_t hash_neg = lm2_hash_i32(-12345);
  
  EXPECT_NE(hash_pos, hash_neg);
}

TEST_F(HashTest, HashU32_Deterministic) {
  uint32_t value = 3141592653U;
  uint32_t hash1 = lm2_hash_u32(value);
  uint32_t hash2 = lm2_hash_u32(value);
  
  EXPECT_EQ(hash1, hash2);
}

TEST_F(HashTest, HashU32_Different) {
  uint32_t hash1 = lm2_hash_u32(1000U);
  uint32_t hash2 = lm2_hash_u32(1001U);
  
  EXPECT_NE(hash1, hash2);
}

// =============================================================================
// Integer Hash Tests - 16-bit
// =============================================================================

TEST_F(HashTest, HashI16_Deterministic) {
  int16_t value = -12345;
  uint32_t hash1 = lm2_hash_i16(value);
  uint32_t hash2 = lm2_hash_i16(value);
  
  EXPECT_EQ(hash1, hash2);
}

TEST_F(HashTest, HashI16_Different) {
  uint32_t hash1 = lm2_hash_i16(100);
  uint32_t hash2 = lm2_hash_i16(101);
  
  EXPECT_NE(hash1, hash2);
}

TEST_F(HashTest, HashU16_Deterministic) {
  uint16_t value = 54321;
  uint32_t hash1 = lm2_hash_u16(value);
  uint32_t hash2 = lm2_hash_u16(value);
  
  EXPECT_EQ(hash1, hash2);
}

TEST_F(HashTest, HashU16_Different) {
  uint32_t hash1 = lm2_hash_u16(1000);
  uint32_t hash2 = lm2_hash_u16(1001);
  
  EXPECT_NE(hash1, hash2);
}

// =============================================================================
// Integer Hash Tests - 8-bit
// =============================================================================

TEST_F(HashTest, HashI8_Deterministic) {
  int8_t value = -123;
  uint32_t hash1 = lm2_hash_i8(value);
  uint32_t hash2 = lm2_hash_i8(value);
  
  EXPECT_EQ(hash1, hash2);
}

TEST_F(HashTest, HashI8_Different) {
  uint32_t hash1 = lm2_hash_i8(10);
  uint32_t hash2 = lm2_hash_i8(11);
  
  EXPECT_NE(hash1, hash2);
}

TEST_F(HashTest, HashU8_Deterministic) {
  uint8_t value = 234;
  uint32_t hash1 = lm2_hash_u8(value);
  uint32_t hash2 = lm2_hash_u8(value);
  
  EXPECT_EQ(hash1, hash2);
}

TEST_F(HashTest, HashU8_Different) {
  uint32_t hash1 = lm2_hash_u8(10);
  uint32_t hash2 = lm2_hash_u8(11);
  
  EXPECT_NE(hash1, hash2);
}

TEST_F(HashTest, HashU8_AllValues) {
  // Test that all 256 byte values produce unique hashes
  std::set<uint32_t> hashes;
  for (int i = 0; i < 256; ++i) {
    uint32_t hash = lm2_hash_u8(static_cast<uint8_t>(i));
    hashes.insert(hash);
  }
  
  // All 256 values should produce unique hashes
  EXPECT_EQ(hashes.size(), 256u);
}

// =============================================================================
// FNV-1a Buffer Hash Tests - 32-bit
// =============================================================================

TEST_F(HashTest, FNV1a32_EmptyBuffer) {
  uint32_t hash = lm2_hash_fnv1a_u32(nullptr, 0);
  // Should return FNV-1a offset basis for 32-bit
  EXPECT_NE(hash, 0U);
}

TEST_F(HashTest, FNV1a32_Deterministic) {
  const char* data = "Hello, World!";
  size_t size = strlen(data);
  
  uint32_t hash1 = lm2_hash_fnv1a_u32(data, size);
  uint32_t hash2 = lm2_hash_fnv1a_u32(data, size);
  
  EXPECT_EQ(hash1, hash2);
}

TEST_F(HashTest, FNV1a32_Different) {
  const char* data1 = "Hello, World!";
  const char* data2 = "Hello, World?";
  
  uint32_t hash1 = lm2_hash_fnv1a_u32(data1, strlen(data1));
  uint32_t hash2 = lm2_hash_fnv1a_u32(data2, strlen(data2));
  
  EXPECT_NE(hash1, hash2);
}

TEST_F(HashTest, FNV1a32_SizeMatters) {
  const char* data = "Hello, World!";
  
  uint32_t hash1 = lm2_hash_fnv1a_u32(data, 5);  // "Hello"
  uint32_t hash2 = lm2_hash_fnv1a_u32(data, strlen(data));
  
  EXPECT_NE(hash1, hash2);
}

TEST_F(HashTest, FNV1a32_OrderMatters) {
  const char* data1 = "abc";
  const char* data2 = "cba";
  
  uint32_t hash1 = lm2_hash_fnv1a_u32(data1, strlen(data1));
  uint32_t hash2 = lm2_hash_fnv1a_u32(data2, strlen(data2));
  
  EXPECT_NE(hash1, hash2);
}

TEST_F(HashTest, FNV1a32_BinaryData) {
  uint8_t data[] = {0x00, 0x01, 0x02, 0xFF, 0xFE, 0xFD};
  
  uint32_t hash = lm2_hash_fnv1a_u32(data, sizeof(data));
  EXPECT_NE(hash, 0U);
}

// =============================================================================
// FNV-1a Buffer Hash Tests - 64-bit
// =============================================================================

TEST_F(HashTest, FNV1a64_EmptyBuffer) {
  uint64_t hash = lm2_hash_fnv1a_u64(nullptr, 0);
  // Should return FNV-1a offset basis for 64-bit
  EXPECT_NE(hash, 0ULL);
}

TEST_F(HashTest, FNV1a64_Deterministic) {
  const char* data = "Hello, World!";
  size_t size = strlen(data);
  
  uint64_t hash1 = lm2_hash_fnv1a_u64(data, size);
  uint64_t hash2 = lm2_hash_fnv1a_u64(data, size);
  
  EXPECT_EQ(hash1, hash2);
}

TEST_F(HashTest, FNV1a64_Different) {
  const char* data1 = "Hello, World!";
  const char* data2 = "Hello, World?";
  
  uint64_t hash1 = lm2_hash_fnv1a_u64(data1, strlen(data1));
  uint64_t hash2 = lm2_hash_fnv1a_u64(data2, strlen(data2));
  
  EXPECT_NE(hash1, hash2);
}

TEST_F(HashTest, FNV1a64_LongString) {
  std::string long_str(10000, 'a');
  
  uint64_t hash = lm2_hash_fnv1a_u64(long_str.c_str(), long_str.size());
  EXPECT_NE(hash, 0ULL);
}

TEST_F(HashTest, FNV1a64_vs_32) {
  const char* data = "Test Data";
  size_t size = strlen(data);
  
  uint32_t hash32 = lm2_hash_fnv1a_u32(data, size);
  uint64_t hash64 = lm2_hash_fnv1a_u64(data, size);
  
  // 64-bit and 32-bit versions should produce different hash spaces
  EXPECT_NE(static_cast<uint64_t>(hash32), hash64);
}

// =============================================================================
// Hash Combining Tests - 32-bit
// =============================================================================

TEST_F(HashTest, Combine32_Deterministic) {
  uint32_t seed = 12345U;
  uint32_t hash = 67890U;
  
  uint32_t result1 = lm2_hash_combine_u32(seed, hash);
  uint32_t result2 = lm2_hash_combine_u32(seed, hash);
  
  EXPECT_EQ(result1, result2);
}

TEST_F(HashTest, Combine32_OrderMatters) {
  uint32_t a = 12345U;
  uint32_t b = 67890U;
  
  uint32_t combo1 = lm2_hash_combine_u32(a, b);
  uint32_t combo2 = lm2_hash_combine_u32(b, a);
  
  // Order should matter for hash combining
  EXPECT_NE(combo1, combo2);
}

TEST_F(HashTest, Combine32_Multiple) {
  uint32_t seed = 0;
  
  // Combine multiple hashes
  seed = lm2_hash_combine_u32(seed, lm2_hash_u32(123U));
  seed = lm2_hash_combine_u32(seed, lm2_hash_u32(456U));
  seed = lm2_hash_combine_u32(seed, lm2_hash_u32(789U));
  
  EXPECT_NE(seed, 0U);
}

TEST_F(HashTest, Combine32_CompositeObject) {
  // Example: hashing a composite object with multiple fields
  struct Point {
    int32_t x, y;
  } p1 = {10, 20}, p2 = {10, 21};
  
  uint32_t hash1 = lm2_hash_combine_u32(lm2_hash_i32(p1.x), lm2_hash_i32(p1.y));
  uint32_t hash2 = lm2_hash_combine_u32(lm2_hash_i32(p2.x), lm2_hash_i32(p2.y));
  
  EXPECT_NE(hash1, hash2);
}

// =============================================================================
// Hash Combining Tests - 64-bit
// =============================================================================

TEST_F(HashTest, Combine64_Deterministic) {
  uint64_t seed = 12345678901234ULL;
  uint64_t hash = 98765432109876ULL;
  
  uint64_t result1 = lm2_hash_combine_u64(seed, hash);
  uint64_t result2 = lm2_hash_combine_u64(seed, hash);
  
  EXPECT_EQ(result1, result2);
}

TEST_F(HashTest, Combine64_OrderMatters) {
  uint64_t a = 12345678901234ULL;
  uint64_t b = 98765432109876ULL;
  
  uint64_t combo1 = lm2_hash_combine_u64(a, b);
  uint64_t combo2 = lm2_hash_combine_u64(b, a);
  
  EXPECT_NE(combo1, combo2);
}

TEST_F(HashTest, Combine64_Multiple) {
  uint64_t seed = 0;
  
  seed = lm2_hash_combine_u64(seed, lm2_hash_u64(123ULL));
  seed = lm2_hash_combine_u64(seed, lm2_hash_u64(456ULL));
  seed = lm2_hash_combine_u64(seed, lm2_hash_u64(789ULL));
  
  EXPECT_NE(seed, 0ULL);
}

// =============================================================================
// Distribution Tests
// =============================================================================

TEST_F(HashTest, Distribution_U32_Sequential) {
  std::set<uint32_t> hashes;
  
  // Hash sequential values
  for (uint32_t i = 0; i < 1000; ++i) {
    hashes.insert(lm2_hash_u32(i));
  }
  
  // All should be unique (no collisions expected)
  EXPECT_EQ(hashes.size(), 1000u);
}

TEST_F(HashTest, Distribution_U64_Sequential) {
  std::set<uint64_t> hashes;
  
  for (uint64_t i = 0; i < 1000; ++i) {
    hashes.insert(lm2_hash_u64(i));
  }
  
  EXPECT_EQ(hashes.size(), 1000u);
}

TEST_F(HashTest, Distribution_F64_Small) {
  std::set<uint64_t> hashes;
  
  // Hash small floating point increments
  for (int i = 0; i < 1000; ++i) {
    hashes.insert(lm2_hash_f64(i * 0.1));
  }
  
  // Should have good distribution
  EXPECT_GT(hashes.size(), 950u);  // Allow for some potential collisions
}
