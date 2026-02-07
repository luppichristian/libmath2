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

#include "lm2_base.h"
#include "lm2_generic.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// Non-cryptographic hash functions for basic types and data buffers
// These are designed to be simple and fast, suitable for hash tables,
// checksums, and other non-security-critical applications.

// =============================================================================
// Low-Level Bit-Mixing Functions
// =============================================================================

// 64-bit integer mixing function using multiplication and XOR-shift operations
// This is the core mixing function used by lm2_hash_u64, lm2_hash_i64, and lm2_hash_f64
LM2_API uint64_t lm2_hash_mix_64(uint64_t x);

// 32-bit integer mixing function using multiplication and XOR-shift operations
// This is the core mixing function used by lm2_hash_u32, lm2_hash_i32, and lm2_hash_f32
LM2_API uint32_t lm2_hash_mix_32(uint32_t x);

// =============================================================================
// Hash Functions for Numeric Types
// =============================================================================

// Hash function for double-precision floating point
// Uses a simple bit-mixing algorithm for floating point values
LM2_API uint64_t lm2_hash_f64(double value);

// Hash function for single-precision floating point
// Uses a simple bit-mixing algorithm for floating point values
LM2_API uint32_t lm2_hash_f32(float value);

// Hash function for 64-bit signed integer
// Uses a simple bit-mixing algorithm
LM2_API uint64_t lm2_hash_i64(int64_t value);

// Hash function for 32-bit signed integer
// Uses a simple bit-mixing algorithm
LM2_API uint32_t lm2_hash_i32(int32_t value);

// Hash function for 16-bit signed integer
// Casts to 32-bit and uses the 32-bit hash function
LM2_API uint32_t lm2_hash_i16(int16_t value);

// Hash function for 8-bit signed integer
// Casts to 32-bit and uses the 32-bit hash function
LM2_API uint32_t lm2_hash_i8(int8_t value);

// Hash function for 64-bit unsigned integer
// Uses a simple bit-mixing algorithm
LM2_API uint64_t lm2_hash_u64(uint64_t value);

// Hash function for 32-bit unsigned integer
// Uses a simple bit-mixing algorithm
LM2_API uint32_t lm2_hash_u32(uint32_t value);

// Hash function for 16-bit unsigned integer
// Casts to 32-bit and uses the 32-bit hash function
LM2_API uint32_t lm2_hash_u16(uint16_t value);

// Hash function for 8-bit unsigned integer
// Casts to 32-bit and uses the 32-bit hash function
LM2_API uint32_t lm2_hash_u8(uint8_t value);

// =============================================================================
// Generic Data Buffer Hashing
// =============================================================================

// FNV-1a hash algorithm for arbitrary data buffers (32-bit version)
// This is a simple, fast, non-cryptographic hash function
// data: pointer to the data buffer
// size: size of the data buffer in bytes
// Returns: 32-bit hash value
LM2_API uint32_t lm2_hash_fnv1a_32(const void* data, size_t size);

// FNV-1a hash algorithm for arbitrary data buffers (64-bit version)
// This is a simple, fast, non-cryptographic hash function
// data: pointer to the data buffer
// size: size of the data buffer in bytes
// Returns: 64-bit hash value
LM2_API uint64_t lm2_hash_fnv1a_64(const void* data, size_t size);

// =============================================================================
// Hash Combining
// =============================================================================

// Combine two 32-bit hash values into one
// This is useful for hashing composite objects
// seed: the initial hash value (or previous combined hash)
// hash: the new hash value to combine
// Returns: combined hash value
LM2_API uint32_t lm2_hash_combine_32(uint32_t seed, uint32_t hash);

// Combine two 64-bit hash values into one
// This is useful for hashing composite objects
// seed: the initial hash value (or previous combined hash)
// hash: the new hash value to combine
// Returns: combined hash value
LM2_API uint64_t lm2_hash_combine_64(uint64_t seed, uint64_t hash);

// =============================================================================
// Generics
// =============================================================================

// Internal generic dispatcher for uint32/uint64 hash functions
// This is used for functions that only support these two types
#ifndef LM2_NO_GENERICS
#  ifdef __cplusplus

// C++17 template-based dispatcher for uint32/uint64 types
template <typename T, typename... Args>
inline auto _lm2_hash_generic_32_64(auto&& u64, auto&& u32, T first, Args&&... rest) -> decltype(auto) {
  using _LM2_T = std::remove_cvref_t<T>;
  if constexpr (std::is_same_v<_LM2_T, uint64_t>) return u64(first, rest...);
  else if constexpr (std::is_same_v<_LM2_T, uint32_t>)
    return u32(first, rest...);
  else
    static_assert(sizeof(_LM2_T) == 0, "Only uint32_t and uint64_t are supported");
}

#    define _LM2_GENERIC_32_64(name, ...) \
      _lm2_hash_generic_32_64(name##_64, name##_32, __VA_ARGS__)

#  else

// C11 _Generic-based dispatcher for uint32/uint64 types
#    define _LM2_GENERIC_32_64(name, ...) \
      _Generic((__VA_ARGS__),             \
          uint64_t: name##_64,            \
          uint32_t: name##_32)(__VA_ARGS__)

#  endif

// Public generic functions
#  define lm2_hash(...)                _LM2_GENERIC(lm2_hash, __VA_ARGS__)
#  define lm2_hash_mix(x)              _LM2_GENERIC_32_64(lm2_hash_mix, x)
#  define lm2_hash_combine(seed, hash) _LM2_GENERIC_32_64(lm2_hash_combine, seed, hash)

#endif

// #############################################################################
LM2_HEADER_END;
// #############################################################################
