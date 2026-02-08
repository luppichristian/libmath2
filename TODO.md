
# libmath2 TODO

## Step-by-step plan (Claude Code)

3. [ ] New module `lm2_shape` (cute_c2 wrapper): integrate cute_c2 (prefer vendored single-header or FetchContent), wrap shapes + collision/query APIs with libmath2 naming/types/macros, keep type-safety and generics where applicable, ensure no allocations and consistent safe-ops usage

4. [ ] New module `lm2_raycast`: ray types (2D/3D) + hit/result structs, ray vs primitive tests (segment/edge, circle/sphere, AABB/range2-3, triangle), closest-hit helpers, consistent epsilon handling, no allocations (integrate with cute_c2)
