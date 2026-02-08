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
// - LM2_NO_CPP_OPERATORS: Disable C++ operator overloads

#include "lm2/geometry2d/lm2_capsule2.h"
#include "lm2/geometry2d/lm2_circle.h"
#include "lm2/geometry2d/lm2_edge2.h"
#include "lm2/geometry2d/lm2_plane2.h"
#include "lm2/geometry2d/lm2_polygon.h"
#include "lm2/geometry2d/lm2_raycast2.h"
#include "lm2/geometry2d/lm2_rectangle.h"
#include "lm2/geometry2d/lm2_shape.h"
#include "lm2/geometry2d/lm2_triangle.h"
#include "lm2/geometry2d/lm2_triangle_geometry.h"
#include "lm2/geometry3d/lm2_capsule3.h"
#include "lm2/geometry3d/lm2_cuboid.h"
#include "lm2/geometry3d/lm2_edge3.h"
#include "lm2/geometry3d/lm2_plane3.h"
#include "lm2/geometry3d/lm2_raycast3.h"
#include "lm2/geometry3d/lm2_sphere.h"
#include "lm2/lm2_base.h"
#include "lm2/lm2_constants.h"
#include "lm2/misc/lm2_bezier_curves.h"
#include "lm2/misc/lm2_easings.h"
#include "lm2/misc/lm2_hash.h"
#include "lm2/misc/lm2_noise.h"
#include "lm2/ranges/lm2_range2.h"
#include "lm2/ranges/lm2_range3.h"
#include "lm2/ranges/lm2_range4.h"
#include "lm2/scalar/lm2_safe_ops.h"
#include "lm2/scalar/lm2_scalar.h"
#include "lm2/scalar/lm2_trigonometry.h"
#include "lm2/vectors/lm2_vector2.h"
#include "lm2/vectors/lm2_vector3.h"
#include "lm2/vectors/lm2_vector4.h"
#include "lm2/vectors/lm2_vector_specifics.h"