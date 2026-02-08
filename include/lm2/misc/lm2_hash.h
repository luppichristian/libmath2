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
LM2_API uint64_t lm2_hash_mix_u64(uint64_t x);

// 32-bit integer mixing function using multiplication and XOR-shift operations
// This is the core mixing function used by lm2_hash_u32, lm2_hash_i32, and lm2_hash_f32
LM2_API uint32_t lm2_hash_mix_u32(uint32_t x);

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
LM2_API uint32_t lm2_hash_fnv1a_u32(const void* data, size_t size);

// FNV-1a hash algorithm for arbitrary data buffers (64-bit version)
// This is a simple, fast, non-cryptographic hash function
// data: pointer to the data buffer
// size: size of the data buffer in bytes
// Returns: 64-bit hash value
LM2_API uint64_t lm2_hash_fnv1a_u64(const void* data, size_t size);

// =============================================================================
// Hash Combining
// =============================================================================

// Combine two 32-bit hash values into one
// This is useful for hashing composite objects
// seed: the initial hash value (or previous combined hash)
// hash: the new hash value to combine
// Returns: combined hash value
LM2_API uint32_t lm2_hash_combine_u32(uint32_t seed, uint32_t hash);

// Combine two 64-bit hash values into one
// This is useful for hashing composite objects
// seed: the initial hash value (or previous combined hash)
// hash: the new hash value to combine
// Returns: combined hash value
LM2_API uint64_t lm2_hash_combine_u64(uint64_t seed, uint64_t hash);

// #############################################################################
LM2_HEADER_END;
// #############################################################################
