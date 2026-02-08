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

#include "lm2/scalar/lm2_scalar.h"

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

// Declare vector-vector operation functions
#define _LM2_DECLARE_VECTOR_OP(type_name, name) \
  LM2_API type_name name(type_name a, type_name b);

// Declare vector-scalar operation functions
#define _LM2_DECLARE_VECTOR_OP_SCALAR(type_name, scalar_type, name) \
  LM2_API type_name name(type_name a, scalar_type b);

// Declare unary vector operation functions
#define _LM2_DECLARE_VECTOR_UNARY_OP(type_name, name) \
  LM2_API type_name name(type_name a);

// =============================================================================
// Vector Constructor Macros
// =============================================================================
// These macros declare helper functions for creating vectors from scalar values.

// Constructor for V2 (takes x, y components)
#define _LM2_DECLARE_V2_MAKE(type_name, scalar_type) \
  LM2_API type_name type_name##_make(scalar_type x, scalar_type y);

// Constructor for V3 (takes x, y, z components)
#define _LM2_DECLARE_V3_MAKE(type_name, scalar_type) \
  LM2_API type_name type_name##_make(scalar_type x, scalar_type y, scalar_type z);

// Constructor for V4 (takes x, y, z, w components)
#define _LM2_DECLARE_V4_MAKE(type_name, scalar_type) \
  LM2_API type_name type_name##_make(scalar_type x, scalar_type y, scalar_type z, scalar_type w);

// Splat constructor (all components set to same value)
#define _LM2_DECLARE_V2_SPLAT(type_name, scalar_type) \
  LM2_API type_name type_name##_splat(scalar_type v);

#define _LM2_DECLARE_V3_SPLAT(type_name, scalar_type) \
  LM2_API type_name type_name##_splat(scalar_type v);

#define _LM2_DECLARE_V4_SPLAT(type_name, scalar_type) \
  LM2_API type_name type_name##_splat(scalar_type v);

// Zero constructor (all components set to 0)
#define _LM2_DECLARE_V2_ZERO(type_name) \
  LM2_API type_name type_name##_zero(void);

#define _LM2_DECLARE_V3_ZERO(type_name) \
  LM2_API type_name type_name##_zero(void);

#define _LM2_DECLARE_V4_ZERO(type_name) \
  LM2_API type_name type_name##_zero(void);

// =============================================================================
// Scalar Function Porting Macros
// =============================================================================
// These macros "port" scalar functions to work with vectors by applying them
// component-wise to each vector element.

// Unary scalar function (e.g., floor, ceil, abs, sqrt)
#define _LM2_DECLARE_SCALAR_FUNC_1(type_name, func_name) \
  LM2_API type_name func_name(type_name a);

// Binary scalar function (e.g., min, max, pow, mod)
#define _LM2_DECLARE_SCALAR_FUNC_2(type_name, func_name) \
  LM2_API type_name func_name(type_name a, type_name b);

// Ternary scalar function (e.g., clamp, lerp, smoothstep)
#define _LM2_DECLARE_SCALAR_FUNC_3(type_name, func_name) \
  LM2_API type_name func_name(type_name a, type_name b, type_name c);

// C++ operator[] for vector unions
#if defined(__cplusplus) && !defined(LM2_NO_CPP_OPERATORS)
#  define _LM2_VECTOR_SUBSCRIPT_OP(scalar_type, size)   \
    inline scalar_type& operator[](int i) {             \
      return e[i];                                      \
    }                                                   \
    inline const scalar_type& operator[](int i) const { \
      return e[i];                                      \
    }
#else
#  define _LM2_VECTOR_SUBSCRIPT_OP(scalar_type, size)
#endif

// =============================================================================
// C++ Constructors for Vector Types
// =============================================================================
// These macros inject actual C++ constructors into vector unions.

#if defined(__cplusplus) && !defined(LM2_NO_CPP_OPERATORS)
// V2 constructors (make, splat, default zero)
#  define _LM2_V2_CPP_CONSTRUCTORS(type_name, scalar_type) \
    type_name(): x(0), y(0) {                              \
    }                                                      \
    type_name(scalar_type x, scalar_type y): x(x), y(y) {  \
    }                                                      \
    explicit type_name(scalar_type v): x(v), y(v) {        \
    }

// V3 constructors (make, splat, default zero)
#  define _LM2_V3_CPP_CONSTRUCTORS(type_name, scalar_type) \
    type_name(): x(0), y(0), z(0) {                        \
    }                                                      \
    type_name(scalar_type x, scalar_type y, scalar_type z) \
        : x(x), y(y), z(z) {                               \
    }                                                      \
    explicit type_name(scalar_type v): x(v), y(v), z(v) {  \
    }

// V4 constructors (make, splat, default zero)
#  define _LM2_V4_CPP_CONSTRUCTORS(type_name, scalar_type)                \
    type_name(): x(0), y(0), z(0), w(0) {                                 \
    }                                                                     \
    type_name(scalar_type x, scalar_type y, scalar_type z, scalar_type w) \
        : x(x), y(y), z(z), w(w) {                                        \
    }                                                                     \
    explicit type_name(scalar_type v): x(v), y(v), z(v), w(v) {           \
    }
#else
#  define _LM2_V2_CPP_CONSTRUCTORS(type_name, scalar_type)
#  define _LM2_V3_CPP_CONSTRUCTORS(type_name, scalar_type)
#  define _LM2_V4_CPP_CONSTRUCTORS(type_name, scalar_type)
#endif

// #############################################################################
LM2_HEADER_END;
// #############################################################################