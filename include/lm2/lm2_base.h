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

// #############################################################################
// LM2 utilities
// #############################################################################

#ifdef __cplusplus
#  define LM2_HEADER_BEGIN extern "C" {
#  define LM2_HEADER_END   }
#else
#  define LM2_HEADER_BEGIN
#  define LM2_HEADER_END
#endif

// #############################################################################
LM2_HEADER_BEGIN;
// #############################################################################

#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// #############################################################################
// LM2_API macro for shared library symbol visibility
// #############################################################################

#if defined(LM2_SHARED)
#  if defined(_WIN32) || defined(_WIN64)
#    if defined(LM2_EXPORTS)
#      define LM2_API __declspec(dllexport)
#    else
#      define LM2_API __declspec(dllimport)
#    endif
#  elif __GNUC__ >= 4
#    define LM2_API __attribute__((visibility("default")))
#  else
#    define LM2_API
#  endif
#else
#  define LM2_API
#endif

// #############################################################################
// LM2_ASSERT macro for internal assertions
// #############################################################################

#if !defined(LM2_ASSERT)
#  include <assert.h>
#  define LM2_ASSERT(expr) assert(expr)
#endif

#ifdef LM2_UNSAFE
#  define LM2_ASSERT_UNSAFE(x)
#else
#  define LM2_ASSERT_UNSAFE(x) LM2_ASSERT(x)
#endif

// #############################################################################
// Assert floating point sizes
// #############################################################################

#ifdef __cplusplus
static_assert(sizeof(float) == 4, "Expected float to be 4 bytes");
static_assert(sizeof(double) == 8, "Expected double to be 8 bytes");
#else
_Static_assert(sizeof(float) == 4, "Expected float to be 4 bytes");
_Static_assert(sizeof(double) == 8, "Expected double to be 8 bytes");
#endif

// #############################################################################
LM2_HEADER_END;
// #############################################################################