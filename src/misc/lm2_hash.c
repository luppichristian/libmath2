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

#include <lm2/misc/lm2_hash.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <string.h>

// FNV-1a hash constants
#define FNV1A_32_OFFSET 0x811c9dc5u
#define FNV1A_32_PRIME  0x01000193u
#define FNV1A_64_OFFSET 0xcbf29ce484222325ull
#define FNV1A_64_PRIME  0x00000100000001b3ull

// =============================================================================
// Low-Level Bit-Mixing Functions
// =============================================================================

LM2_API uint64_t lm2_hash_mix_u64(uint64_t x) {
  x ^= x >> 33;
  x *= 0xff51afd7ed558ccdull;
  x ^= x >> 33;
  x *= 0xc4ceb9fe1a85ec53ull;
  x ^= x >> 33;
  return x;
}

LM2_API uint32_t lm2_hash_mix_u32(uint32_t x) {
  x ^= x >> 16;
  x *= 0x85ebca6bu;
  x ^= x >> 13;
  x *= 0xc2b2ae35u;
  x ^= x >> 16;
  return x;
}

// =============================================================================
// 64-bit Hash Functions
// =============================================================================

LM2_API uint64_t lm2_hash_u64(uint64_t value) {
  return lm2_hash_mix_u64(value);
}

LM2_API uint64_t lm2_hash_i64(int64_t value) {
  // Reinterpret as unsigned
  uint64_t u_value;
  memcpy(&u_value, &value, sizeof(uint64_t));
  return lm2_hash_mix_u64(u_value);
}

LM2_API uint64_t lm2_hash_f64(double value) {
  // Special handling for -0.0 and 0.0 (treat as same)
  if (value == 0.0) {
    value = 0.0;
  }

  // Reinterpret bits as uint64_t
  uint64_t bits;
  memcpy(&bits, &value, sizeof(uint64_t));
  return lm2_hash_mix_u64(bits);
}

// =============================================================================
// 32-bit Hash Functions
// =============================================================================

LM2_API uint32_t lm2_hash_u32(uint32_t value) {
  return lm2_hash_mix_u32(value);
}

LM2_API uint32_t lm2_hash_u16(uint16_t value) {
  return lm2_hash_mix_u32((uint32_t)value);
}

LM2_API uint32_t lm2_hash_u8(uint8_t value) {
  return lm2_hash_mix_u32((uint32_t)value);
}

LM2_API uint32_t lm2_hash_i32(int32_t value) {
  // Reinterpret as unsigned
  uint32_t u_value;
  memcpy(&u_value, &value, sizeof(uint32_t));
  return lm2_hash_mix_u32(u_value);
}

LM2_API uint32_t lm2_hash_i16(int16_t value) {
  // Cast to int32_t first to preserve sign, then hash
  return lm2_hash_i32((int32_t)value);
}

LM2_API uint32_t lm2_hash_i8(int8_t value) {
  // Cast to int32_t first to preserve sign, then hash
  return lm2_hash_i32((int32_t)value);
}

LM2_API uint32_t lm2_hash_f32(float value) {
  // Special handling for -0.0f and 0.0f (treat as same)
  if (value == 0.0f) {
    value = 0.0f;
  }

  // Reinterpret bits as uint32_t
  uint32_t bits;
  memcpy(&bits, &value, sizeof(uint32_t));
  return lm2_hash_mix_u32(bits);
}

// =============================================================================
// FNV-1a Hash for Data Buffers
// =============================================================================

LM2_API uint32_t lm2_hash_fnv1a_u32(const void* data, size_t size) {
  if (data == NULL || size == 0) {
    return FNV1A_32_OFFSET;
  }

  uint32_t hash = FNV1A_32_OFFSET;
  const uint8_t* bytes = (const uint8_t*)data;

  for (size_t i = 0; i < size; i++) {
    hash ^= bytes[i];
    hash *= FNV1A_32_PRIME;
  }

  return hash;
}

LM2_API uint64_t lm2_hash_fnv1a_u64(const void* data, size_t size) {
  if (data == NULL || size == 0) {
    return FNV1A_64_OFFSET;
  }

  uint64_t hash = FNV1A_64_OFFSET;
  const uint8_t* bytes = (const uint8_t*)data;

  for (size_t i = 0; i < size; i++) {
    hash ^= bytes[i];
    hash *= FNV1A_64_PRIME;
  }

  return hash;
}

// =============================================================================
// Hash Combining
// =============================================================================

LM2_API uint32_t lm2_hash_combine_u32(uint32_t seed, uint32_t hash) {
  // Based on boost::hash_combine
  // Golden ratio approximation for 32-bit: 0x9e3779b9
  seed ^= hash + 0x9e3779b9u + (seed << 6) + (seed >> 2);
  return seed;
}

LM2_API uint64_t lm2_hash_combine_u64(uint64_t seed, uint64_t hash) {
  // Based on boost::hash_combine
  // Golden ratio approximation for 64-bit: 0x9e3779b97f4a7c15
  seed ^= hash + 0x9e3779b97f4a7c15ull + (seed << 12) + (seed >> 4);
  return seed;
}
