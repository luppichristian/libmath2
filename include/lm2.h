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

// Configurable defines:
// - LM2_UNSAFE: Disable safe checks in safe ops (for performance)
// - LM2_NO_GENERICS: Disable generic functions
// - LM2_NO_CPP_OPERATORS: Disable C++ operator overloads

#include "lm2/lm2_base.h"
#include "lm2/lm2_bezier_curves.h"
#include "lm2/lm2_constants.h"
#include "lm2/lm2_edge.h"
#include "lm2/lm2_noise.h"
#include "lm2/lm2_safe_ops.h"
#include "lm2/lm2_scalar.h"
#include "lm2/lm2_triangle.h"
#include "lm2/lm2_trigonometry.h"
#include "lm2/lm2_vector2.h"
#include "lm2/lm2_vector3.h"
#include "lm2/lm2_vector4.h"
#include "lm2/lm2_vector_specifics.h"