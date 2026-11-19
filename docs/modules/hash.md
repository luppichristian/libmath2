# Hash Functions

## Overview

Non-cryptographic hash functions for all numeric types, generic data buffer hashing via FNV-1a, and hash combining for composite objects.

## Why Use This?

These hashes can help build hash tables, checksums, and spatial hashes. Collisions are possible; compare original values when equality matters. They are not suitable for cryptographic integrity or authentication.

## Functions

### Bit-Mixing Functions

Low-level functions that mix bits of an integer for better hash distribution. Zero is replaced with a fixed nonzero input before mixing: `0x01234567` for 32 bits and `0x0123456789abcdef` for 64 bits. Zero therefore collides with the respective replacement input.

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

Narrow signed integers are sign-extended to 32 bits before hashing, and narrow unsigned integers are zero-extended. Floating-point hashes mix the object representation, except that positive and negative zero hash equally. NaN payloads are not canonicalized, so different NaN representations can produce different hashes.

### Buffer Hashing (FNV-1a)

| Function | Description |
|----------|-------------|
| `lm2_hash_fnv1a_u32(data, size)` | FNV-1a hash of arbitrary data (32-bit) |
| `lm2_hash_fnv1a_u64(data, size)` | FNV-1a hash of arbitrary data (64-bit) |

FNV-1a processes `size` bytes in memory order. A null `data` pointer or a zero size returns the FNV offset basis, including a null pointer paired with a nonzero size. Otherwise the buffer must provide at least `size` readable bytes. Hashing a raw struct includes its representation, such as padding and byte order; serialize fields explicitly when a portable representation is needed.

### Hash Combining

Combine a previous `seed` and an already computed field hash. The operation is order-dependent and useful for hashing composite objects; choose a consistent field order.

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
