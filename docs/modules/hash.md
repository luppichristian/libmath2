---
layout: default
title: Hash
---

# Hash Functions

## Overview

Non-cryptographic hash functions for all numeric types, generic data buffer hashing via FNV-1a, and hash combining for composite objects.

## Why Use This?

Fast hashing is needed for hash tables, deduplication, checksums, and spatial hashing. These are not suitable for cryptographic purposes.

## Functions

### Bit-Mixing Functions

Low-level functions that mix bits of an integer for better hash distribution.

| Function | Description |
|----------|-------------|
| `lm2_hash_mix_u64(x)` | 64-bit mixing |
| `lm2_hash_mix_u32(x)` | 32-bit mixing |

### Numeric Type Hashing

| Function | Input | Output |
|----------|-------|--------|
| `lm2_hash_f64(value)` | `double` | `uint64_t` |
| `lm2_hash_f32(value)` | `float` | `uint32_t` |
| `lm2_hash_i64(value)` | `int64_t` | `uint64_t` |
| `lm2_hash_i32(value)` | `int32_t` | `uint32_t` |
| `lm2_hash_i16(value)` | `int16_t` | `uint32_t` |
| `lm2_hash_i8(value)` | `int8_t` | `uint32_t` |
| `lm2_hash_u64(value)` | `uint64_t` | `uint64_t` |
| `lm2_hash_u32(value)` | `uint32_t` | `uint32_t` |
| `lm2_hash_u16(value)` | `uint16_t` | `uint32_t` |
| `lm2_hash_u8(value)` | `uint8_t` | `uint32_t` |

### Buffer Hashing (FNV-1a)

| Function | Description |
|----------|-------------|
| `lm2_hash_fnv1a_u32(data, size)` | FNV-1a hash of arbitrary data (32-bit) |
| `lm2_hash_fnv1a_u64(data, size)` | FNV-1a hash of arbitrary data (64-bit) |

### Hash Combining

Combine two hash values into one. Useful for hashing composite objects (e.g., hash a struct by combining hashes of its fields).

| Function | Description |
|----------|-------------|
| `lm2_hash_combine_u32(seed, hash)` | Combine two 32-bit hashes |
| `lm2_hash_combine_u64(seed, hash)` | Combine two 64-bit hashes |

## Example

```c
// Hash a 2D grid cell
int32_t cell_x = 42, cell_y = 17;
uint32_t h = lm2_hash_combine_u32(lm2_hash_i32(cell_x), lm2_hash_i32(cell_y));

// Hash arbitrary data
const char* str = "hello";
uint32_t str_hash = lm2_hash_fnv1a_u32(str, 5);
```
