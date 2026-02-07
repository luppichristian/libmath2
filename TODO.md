
# libmath2 TODO

## Step-by-step plan (Claude Code)

3. [ ] New module `lm2_shape` (cute_c2 wrapper): integrate cute_c2 (prefer vendored single-header or FetchContent), wrap shapes + collision/query APIs with libmath2 naming/types/macros, keep type-safety and generics where applicable, ensure no allocations and consistent safe-ops usage

4. [ ] New module `lm2_raycast`: ray types (2D/3D) + hit/result structs, ray vs primitive tests (segment/edge, circle/sphere, AABB/range2-3, triangle), closest-hit helpers, consistent epsilon handling, no allocations (integrate with cute_c2)

5. [ ] New module `lm2_polygon`: creation helpers, operations (insert/remove/transform), area + winding order, shape classification (triangle/quad + fundamental shapes), triangulation (triangle list), decide internal (ear clipping) vs external dependency

6. [ ] Polygon creation: create polygon with N edges, create triangle polygon (position + tip), create polygon from rect, create polygon from triangle

7. [ ] Polygon getters: validate polygon, signed area, area, winding order, convex check, triangle check, quad check, center, bounds, Box2D conversion (if applicable), point containment

8. [ ] Polygon manipulation: insert vertex, remove vertex, translate, scale, place at center

9. [ ] Polygon triangulation: ear clipping triangulation, define max triangle count (vertex_count - 2)

10. [ ] Polygon subpolygons: split polygon by max vertices, generate convex subpolygons
