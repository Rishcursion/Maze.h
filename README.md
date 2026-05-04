# Maze.h

> **A from-scratch maze generator in C. Because the only way to actually understand recursive backtracking is to debug it at 2am with `printf`.**

A small C project that grew out of wanting to write something non-trivial in raw C — no STL crutches, no garbage collector, just structs and `malloc`. The premise: implement the classic maze-generation algorithms (Recursive Backtracker, Prim's, Eller's) from a paper-and-pencil description, with a real data-structure layer underneath (dynamic array, queue, logging) instead of pretending arrays are infinite.

## What works right now

```
src/core/maze.c                 Maze grid construction / destruction
src/core/generators/
  ├── recursivebt.c             Recursive backtracker (DFS-based) — done
  ├── primnproper.c             Prim's algorithm — in progress
  └── ellers.c                  Eller's algorithm — stubbed
include/ds/dynamic_array.h      Hand-rolled vector
include/ds/queue.h              Hand-rolled queue
include/utils/logger.h          Levelled logging (debug/info/warn) so I can `make` and tail
```

The recursive backtracker is the only generator that's currently end-to-end. Prim's and Eller's are scaffolded but not finished — the function signatures are there, the logic isn't.

There's no rendering yet. Maze state lives in a 2D `char**` grid with bitmasked wall flags. Output is whatever you wire up; the eventual plan is an SDL window so I can visualize generation step-by-step (which is the only way to actually *see* the difference between Prim's and DFS).

## Why "Maze.h"?

The name's a lie — the public API spans a dozen headers under `include/`, not one. I named the repo before I understood what scope this would grow into. Renaming GitHub repos breaks links, so it stays.

## Build

```bash
make
./build/game
```

The Makefile auto-discovers sources under `src/` and emits `compile_commands.json` for clangd. There's a `make clean` if things get weird.

## Why I'm building this

Two reasons:
1. To have a "real" C project that isn't a 100-line LeetCode submission. Memory ownership across nested structs forces you to think about lifetimes in a way that Python and JS just don't.
2. Mazes are a great forcing function — they need a graph-ish data structure, an algorithm, and a renderer, which is enough surface area to learn how to actually *organize* a C codebase (headers, build system, debug tooling) without the project ballooning into something I'll abandon.

It will probably be abandoned anyway. But further along than the last attempt.
