# Maze Algorithm

Goal: Create a 1 million x 1 million maze. Is it possible? Let's find out! In this project we're going to use the c language to demonstrate optimizations that can be made in maze generation and solving algorithms. Each file will have an associated plain-text file to explain it's initial idea, function, and implementation. We will also test each implementation against a series of benchmarks to see how they compare to each other. 

## Changelog

---

### 2026-02-20 — Core Infrastructure

- Implemented naive maze data structure (`src/maze.h/c`)
- Implemented utilities: error handling, memory helpers, CLI argument parsing (`src/utilities.h/c`)
- Started main bootstrap (`src/main.c`)
- Added rendering stubs (`src/render/`)
- Added unit test suite (`tests/`) — 27 tests passing
- Updated build system (`Makefile`) with test and clean targets

### 2026-02-18 — Initial Skeleton

- Established project directory structure: `src/`, `explained/`, `Makefile`
- Added stub source files: `src/main.c`, `src/maze.h/c`, `src/generators/RecursiveDFS.h/c`, `src/searchers/BFS.h/c`
- Added explanation placeholders mirroring the source layout under `explained/`
- No algorithms implemented yet; project does not compile to a runnable binary
