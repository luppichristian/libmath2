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

#ifdef __cplusplus
extern "C" {
#endif

#if defined(LIBMATH2_SHARED)
#  if defined(_WIN32) || defined(_WIN64)
#    if defined(LIBMATH2_EXPORTS)
#      define LIBMATH2_API __declspec(dllexport)
#    else
#      define LIBMATH2_API __declspec(dllimport)
#    endif
#  elif __GNUC__ >= 4
#    define LIBMATH2_API __attribute__((visibility("default")))
#  else
#    define LIBMATH2_API
#  endif
#else
#  define LIBMATH2_API
#endif

/**
 * Add two integers.
 *
 * @param a First operand.
 * @param b Second operand.
 * @return The sum of a and b.
 */
LIBMATH2_API int libmath2_add(int a, int b);

#ifdef __cplusplus
}
#endif
