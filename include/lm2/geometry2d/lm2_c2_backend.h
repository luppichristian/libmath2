#pragma once

// Embed a private, translation-unit-local copy of the unmodified cute_c2 backend.
#define LM2_PRIVATE_C2_MAX_POLYGON_VERTS 8
#include <float.h>
#include <math.h>
#include <string.h>

#pragma push_macro("CUTE_C2_H")
#undef CUTE_C2_H
#pragma push_macro("CUTE_C2_IMPLEMENTATION_ONCE")
#undef CUTE_C2_IMPLEMENTATION_ONCE
#pragma push_macro("CUTE_C2_IMPLEMENTATION")
#undef CUTE_C2_IMPLEMENTATION
#pragma push_macro("CUTE_C2_API")
#undef CUTE_C2_API
#pragma push_macro("C2_INLINE")
#undef C2_INLINE
#pragma push_macro("C2_MAX_POLYGON_VERTS")
#undef C2_MAX_POLYGON_VERTS
#pragma push_macro("C2_GJK_ITERS")
#undef C2_GJK_ITERS
#pragma push_macro("C2_BARY")
#undef C2_BARY
#pragma push_macro("C2_BARY2")
#undef C2_BARY2
#pragma push_macro("C2_BARY3")
#undef C2_BARY3
#pragma push_macro("c2Abs")
#undef c2Abs
#pragma push_macro("c2Clamp")
#undef c2Clamp
#pragma push_macro("c2Cos")
#undef c2Cos
#pragma push_macro("c2Impact")
#undef c2Impact
#pragma push_macro("c2Max")
#undef c2Max
#pragma push_macro("c2Min")
#undef c2Min
#pragma push_macro("c2Sign")
#undef c2Sign
#pragma push_macro("c2Sin")
#undef c2Sin
#pragma push_macro("c2Sqrt")
#undef c2Sqrt
#define C2_TYPE                                 lm2_private_C2_TYPE
#define C2_TYPE_AABB                            lm2_private_C2_TYPE_AABB
#define C2_TYPE_CAPSULE                         lm2_private_C2_TYPE_CAPSULE
#define C2_TYPE_CIRCLE                          lm2_private_C2_TYPE_CIRCLE
#define C2_TYPE_NONE                            lm2_private_C2_TYPE_NONE
#define C2_TYPE_POLY                            lm2_private_C2_TYPE_POLY
#define c22                                     lm2_private_c22
#define c23                                     lm2_private_c23
#define c2AABB                                  lm2_private_c2AABB
#define c2AABBtoAABB                            lm2_private_c2AABBtoAABB
#define c2AABBtoAABBManifold                    lm2_private_c2AABBtoAABBManifold
#define c2AABBtoCapsule                         lm2_private_c2AABBtoCapsule
#define c2AABBtoCapsuleManifold                 lm2_private_c2AABBtoCapsuleManifold
#define c2AABBtoPoint                           lm2_private_c2AABBtoPoint
#define c2AABBtoPoly                            lm2_private_c2AABBtoPoly
#define c2AABBtoPolyManifold                    lm2_private_c2AABBtoPolyManifold
#define c2Absv                                  lm2_private_c2Absv
#define c2Add                                   lm2_private_c2Add
#define c2AntinormalFace                        lm2_private_c2AntinormalFace
#define c2BBVerts                               lm2_private_c2BBVerts
#define c2CCW90                                 lm2_private_c2CCW90
#define c2Capsule                               lm2_private_c2Capsule
#define c2CapsuleSupport                        lm2_private_c2CapsuleSupport
#define c2CapsuletoCapsule                      lm2_private_c2CapsuletoCapsule
#define c2CapsuletoCapsuleManifold              lm2_private_c2CapsuletoCapsuleManifold
#define c2CapsuletoPoly                         lm2_private_c2CapsuletoPoly
#define c2CapsuletoPolyManifold                 lm2_private_c2CapsuletoPolyManifold
#define c2CastRay                               lm2_private_c2CastRay
#define c2CheckFaces                            lm2_private_c2CheckFaces
#define c2Circle                                lm2_private_c2Circle
#define c2CircleToPoint                         lm2_private_c2CircleToPoint
#define c2CircletoAABB                          lm2_private_c2CircletoAABB
#define c2CircletoAABBManifold                  lm2_private_c2CircletoAABBManifold
#define c2CircletoCapsule                       lm2_private_c2CircletoCapsule
#define c2CircletoCapsuleManifold               lm2_private_c2CircletoCapsuleManifold
#define c2CircletoCircle                        lm2_private_c2CircletoCircle
#define c2CircletoCircleManifold                lm2_private_c2CircletoCircleManifold
#define c2CircletoPoly                          lm2_private_c2CircletoPoly
#define c2CircletoPolyManifold                  lm2_private_c2CircletoPolyManifold
#define c2Clampv                                lm2_private_c2Clampv
#define c2Clip                                  lm2_private_c2Clip
#define c2Collide                               lm2_private_c2Collide
#define c2Collided                              lm2_private_c2Collided
#define c2D                                     lm2_private_c2D
#define c2Det2                                  lm2_private_c2Det2
#define c2Dist                                  lm2_private_c2Dist
#define c2Div                                   lm2_private_c2Div
#define c2Dot                                   lm2_private_c2Dot
#define c2Dual                                  lm2_private_c2Dual
#define c2GJK                                   lm2_private_c2GJK
#define c2GJKCache                              lm2_private_c2GJKCache
#define c2GJKSimplexMetric                      lm2_private_c2GJKSimplexMetric
#define c2Hmax                                  lm2_private_c2Hmax
#define c2Hmin                                  lm2_private_c2Hmin
#define c2Hull                                  lm2_private_c2Hull
#define c2Incident                              lm2_private_c2Incident
#define c2Inflate                               lm2_private_c2Inflate
#define c2InflatePoly                           lm2_private_c2InflatePoly
#define c2Intersect                             lm2_private_c2Intersect
#define c2KeepDeep                              lm2_private_c2KeepDeep
#define c2L                                     lm2_private_c2L
#define c2Len                                   lm2_private_c2Len
#define c2Lerp                                  lm2_private_c2Lerp
#define c2MakePoly                              lm2_private_c2MakePoly
#define c2MakeProxy                             lm2_private_c2MakeProxy
#define c2Manifold                              lm2_private_c2Manifold
#define c2Maxv                                  lm2_private_c2Maxv
#define c2Minv                                  lm2_private_c2Minv
#define c2Mulmm                                 lm2_private_c2Mulmm
#define c2MulmmT                                lm2_private_c2MulmmT
#define c2Mulmv                                 lm2_private_c2Mulmv
#define c2MulmvT                                lm2_private_c2MulmvT
#define c2Mulrr                                 lm2_private_c2Mulrr
#define c2MulrrT                                lm2_private_c2MulrrT
#define c2Mulrv                                 lm2_private_c2Mulrv
#define c2MulrvT                                lm2_private_c2MulrvT
#define c2Mulvs                                 lm2_private_c2Mulvs
#define c2Mulvv                                 lm2_private_c2Mulvv
#define c2Mulxh                                 lm2_private_c2Mulxh
#define c2MulxhT                                lm2_private_c2MulxhT
#define c2Mulxv                                 lm2_private_c2Mulxv
#define c2MulxvT                                lm2_private_c2MulxvT
#define c2Mulxx                                 lm2_private_c2Mulxx
#define c2MulxxT                                lm2_private_c2MulxxT
#define c2Neg                                   lm2_private_c2Neg
#define c2Norm                                  lm2_private_c2Norm
#define c2Norms                                 lm2_private_c2Norms
#define c2Origin                                lm2_private_c2Origin
#define c2Parallel                              lm2_private_c2Parallel
#define c2PlaneAt                               lm2_private_c2PlaneAt
#define c2Poly                                  lm2_private_c2Poly
#define c2PolytoPoly                            lm2_private_c2PolytoPoly
#define c2PolytoPolyManifold                    lm2_private_c2PolytoPolyManifold
#define c2Project                               lm2_private_c2Project
#define c2Proxy                                 lm2_private_c2Proxy
#define c2Ray                                   lm2_private_c2Ray
#define c2RayToPlane_OneDimensional             lm2_private_c2RayToPlane_OneDimensional
#define c2Raycast                               lm2_private_c2Raycast
#define c2Rayto                                 lm2_private_c2Rayto
#define c2RaytoAABB                             lm2_private_c2RaytoAABB
#define c2RaytoCapsule                          lm2_private_c2RaytoCapsule
#define c2RaytoCircle                           lm2_private_c2RaytoCircle
#define c2RaytoPoly                             lm2_private_c2RaytoPoly
#define c2Rot                                   lm2_private_c2Rot
#define c2RotIdentity                           lm2_private_c2RotIdentity
#define c2RotX                                  lm2_private_c2RotX
#define c2RotY                                  lm2_private_c2RotY
#define c2SafeNorm                              lm2_private_c2SafeNorm
#define c2SidePlanes                            lm2_private_c2SidePlanes
#define c2SidePlanesFromPoly                    lm2_private_c2SidePlanesFromPoly
#define c2SignedDistPointToPlane_OneDimensional lm2_private_c2SignedDistPointToPlane_OneDimensional
#define c2Simplex                               lm2_private_c2Simplex
#define c2SinCos                                lm2_private_c2SinCos
#define c2Skew                                  lm2_private_c2Skew
#define c2Sub                                   lm2_private_c2Sub
#define c2Support                               lm2_private_c2Support
#define c2TOI                                   lm2_private_c2TOI
#define c2TOIResult                             lm2_private_c2TOIResult
#define c2Transform                             lm2_private_c2Transform
#define c2V                                     lm2_private_c2V
#define c2Witness                               lm2_private_c2Witness
#define c2h                                     lm2_private_c2h
#define c2m                                     lm2_private_c2m
#define c2r                                     lm2_private_c2r
#define c2sv                                    lm2_private_c2sv
#define c2v                                     lm2_private_c2v
#define c2x                                     lm2_private_c2x
#define c2xIdentity                             lm2_private_c2xIdentity

// The vendored implementation intentionally leaves some enum values to the
// default branch. Keep its diagnostics local to the embedded copy.
#if defined(__clang__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wswitch"
#elif defined(__GNUC__)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wswitch"
#endif

#ifndef __cplusplus
#  if defined(_MSC_VER)
#    define CUTE_C2_API   static inline
#    define __forceinline static __forceinline
#  else
// The inline macro adds static to cute_c2's inline helpers and API declarations.
#    define CUTE_C2_API inline
#    define inline      static inline
#  endif
#else
#  define CUTE_C2_API static inline
#endif
#include <cute_c2.h>
#ifndef __cplusplus
#  if defined(_MSC_VER)
#    undef __forceinline
#  else
#    undef inline
#  endif
#endif

static c2Poly c2Dual(c2Poly poly, float skin_factor);
static c2Poly c2InflatePoly(c2Poly poly, float skin_factor);
static int c2AABBtoPoint(c2AABB box, c2v point);
static int c2CircleToPoint(c2Circle circle, c2v point);

#define CUTE_C2_IMPLEMENTATION
#include <cute_c2.h>

#if defined(__clang__)
#  pragma clang diagnostic pop
#elif defined(__GNUC__)
#  pragma GCC diagnostic pop
#endif
#undef C2_TYPE
#undef C2_TYPE_AABB
#undef C2_TYPE_CAPSULE
#undef C2_TYPE_CIRCLE
#undef C2_TYPE_NONE
#undef C2_TYPE_POLY
#undef c22
#undef c23
#undef c2AABB
#undef c2AABBtoAABB
#undef c2AABBtoAABBManifold
#undef c2AABBtoCapsule
#undef c2AABBtoCapsuleManifold
#undef c2AABBtoPoint
#undef c2AABBtoPoly
#undef c2AABBtoPolyManifold
#undef c2Absv
#undef c2Add
#undef c2AntinormalFace
#undef c2BBVerts
#undef c2CCW90
#undef c2Capsule
#undef c2CapsuleSupport
#undef c2CapsuletoCapsule
#undef c2CapsuletoCapsuleManifold
#undef c2CapsuletoPoly
#undef c2CapsuletoPolyManifold
#undef c2CastRay
#undef c2CheckFaces
#undef c2Circle
#undef c2CircleToPoint
#undef c2CircletoAABB
#undef c2CircletoAABBManifold
#undef c2CircletoCapsule
#undef c2CircletoCapsuleManifold
#undef c2CircletoCircle
#undef c2CircletoCircleManifold
#undef c2CircletoPoly
#undef c2CircletoPolyManifold
#undef c2Clampv
#undef c2Clip
#undef c2Collide
#undef c2Collided
#undef c2D
#undef c2Det2
#undef c2Dist
#undef c2Div
#undef c2Dot
#undef c2Dual
#undef c2GJK
#undef c2GJKCache
#undef c2GJKSimplexMetric
#undef c2Hmax
#undef c2Hmin
#undef c2Hull
#undef c2Incident
#undef c2Inflate
#undef c2InflatePoly
#undef c2Intersect
#undef c2KeepDeep
#undef c2L
#undef c2Len
#undef c2Lerp
#undef c2MakePoly
#undef c2MakeProxy
#undef c2Manifold
#undef c2Maxv
#undef c2Minv
#undef c2Mulmm
#undef c2MulmmT
#undef c2Mulmv
#undef c2MulmvT
#undef c2Mulrr
#undef c2MulrrT
#undef c2Mulrv
#undef c2MulrvT
#undef c2Mulvs
#undef c2Mulvv
#undef c2Mulxh
#undef c2MulxhT
#undef c2Mulxv
#undef c2MulxvT
#undef c2Mulxx
#undef c2MulxxT
#undef c2Neg
#undef c2Norm
#undef c2Norms
#undef c2Origin
#undef c2Parallel
#undef c2PlaneAt
#undef c2Poly
#undef c2PolytoPoly
#undef c2PolytoPolyManifold
#undef c2Project
#undef c2Proxy
#undef c2Ray
#undef c2RayToPlane_OneDimensional
#undef c2Raycast
#undef c2Rayto
#undef c2RaytoAABB
#undef c2RaytoCapsule
#undef c2RaytoCircle
#undef c2RaytoPoly
#undef c2Rot
#undef c2RotIdentity
#undef c2RotX
#undef c2RotY
#undef c2SafeNorm
#undef c2SidePlanes
#undef c2SidePlanesFromPoly
#undef c2SignedDistPointToPlane_OneDimensional
#undef c2Simplex
#undef c2SinCos
#undef c2Skew
#undef c2Sub
#undef c2Support
#undef c2TOI
#undef c2TOIResult
#undef c2Transform
#undef c2V
#undef c2Witness
#undef c2h
#undef c2m
#undef c2r
#undef c2sv
#undef c2v
#undef c2x
#undef c2xIdentity
#undef c2Sqrt
#pragma pop_macro("c2Sqrt")
#undef c2Sin
#pragma pop_macro("c2Sin")
#undef c2Sign
#pragma pop_macro("c2Sign")
#undef c2Min
#pragma pop_macro("c2Min")
#undef c2Max
#pragma pop_macro("c2Max")
#undef c2Impact
#pragma pop_macro("c2Impact")
#undef c2Cos
#pragma pop_macro("c2Cos")
#undef c2Clamp
#pragma pop_macro("c2Clamp")
#undef c2Abs
#pragma pop_macro("c2Abs")
#undef C2_BARY3
#pragma pop_macro("C2_BARY3")
#undef C2_BARY2
#pragma pop_macro("C2_BARY2")
#undef C2_BARY
#pragma pop_macro("C2_BARY")
#undef C2_GJK_ITERS
#pragma pop_macro("C2_GJK_ITERS")
#undef C2_MAX_POLYGON_VERTS
#pragma pop_macro("C2_MAX_POLYGON_VERTS")
#undef C2_INLINE
#pragma pop_macro("C2_INLINE")
#undef CUTE_C2_API
#pragma pop_macro("CUTE_C2_API")
#undef CUTE_C2_IMPLEMENTATION
#pragma pop_macro("CUTE_C2_IMPLEMENTATION")
#undef CUTE_C2_IMPLEMENTATION_ONCE
#pragma pop_macro("CUTE_C2_IMPLEMENTATION_ONCE")
#undef CUTE_C2_H
#pragma pop_macro("CUTE_C2_H")
