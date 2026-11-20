# libmath2 contributor guidance

libmath2 is a C math library built with CMake. Public headers are in `include/`, implementations in `src/`, GoogleTest C++ tests in `tests/`, and user documentation in `docs/`.

## Local Graphify

Use the locally installed Graphify CLI for codebase navigation. The generated graph is in `.graphify/` and is ignored by Git. Before every Graphify command, set `GRAPHIFY_OUT=.graphify` in the process environment (in PowerShell: `$env:GRAPHIFY_OUT = '.graphify'`; in POSIX shells: `export GRAPHIFY_OUT=.graphify`). This repo-specific setting overrides the default `graphify-out/` path in the user-level Graphify skill; use the CLI rather than the skill's hard-coded build pipeline. From the repository root, run `graphify query "<question>"`, `graphify explain "<symbol>"`, or `graphify path "<from>" "<to>"`. The graph covers code and Markdown structure; it is not a semantic analysis of all prose. The C++ grammar used for headers captures more types but can misinterpret C, and some macro-heavy headers parse only partially. Verify symbols and completeness against the current headers and source. Consult source directly if a graph query is empty, incomplete, stale, or unhelpful.

Keep extraction local. Do not use Graphify Cloud or a remote semantic backend for this repository. To build or refresh the structural code and Markdown graph, set `GRAPHIFY_BACKEND=none` and run `graphify update .`. Run this after code or documentation changes. A new checkout needs the Graphify CLI installed and an initial local build before queries work. Avoid `graphify extract . --code-only`: it disables the Markdown scan for subsequent updates.

## Conventions

- Follow `.clang-format` and use `lower_snake_case` for identifiers. Types do not use a `_t` suffix.
- Public identifiers use the `lm2_` prefix; primitive specialization suffixes such as `f32`, `f64`, `i32`, and `u32` go at the end.
- Place related functionality in existing modules where appropriate. Modules generally have a public header under `include/lm2/<category>/`, an implementation under `src/<category>/`, and tests under `tests/<category>/`.

## Changing the public API

- Keep declarations, definitions, call sites, and unit tests consistent. Write tests for new functionality and update tests for changed behavior.
- Add new public module headers to `include/lm2.h`.
- Update the applicable C++ template and operator overloads, C11 generic dispatch, and unprefixed aliases in `include/lm2/extensions/lm2_cpp_generics.h`, `lm2_cpp_operators.h`, `lm2_c11_generics.h`, and `lm2_unprefixed_names.h` when the public API changes.
