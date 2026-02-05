/* SPDX-License-Identifier: MIT
 * Copyright (c) 2026 libmath2 contributors
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
