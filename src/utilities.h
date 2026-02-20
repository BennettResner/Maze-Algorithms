#pragma once

#include <stddef.h>
#include <stdbool.h>

// --- MACROS ---

#define MIN(a, b) ({ __typeof__(a) _a = (a); __typeof__(b) _b = (b); _a < _b ? _a : _b; })
#define MAX(a, b) ({ __typeof__(a) _a = (a); __typeof__(b) _b = (b); _a > _b ? _a : _b; })

// --- ERROR HANDLING ---

/* Print a formatted error message to stderr and exit with code 1. */
void die(const char *fmt, ...);

// --- MEMORY ---

/* Allocate n bytes; calls die() if allocation fails. */
void *safe_malloc(size_t n);

/* Allocate n elements of size bytes each, zero-initialised; calls die() on failure. */
void *safe_calloc(size_t n, size_t size);

// --- ARGS ---

typedef enum {
    GEN_RECURSIVE_DFS,
} GeneratorAlg;

typedef enum {
    SOLVE_BFS,
    SOLVE_DFS,
    SOLVE_ASTAR,
} SolverAlg;

typedef struct {
    int          width;      /* maze width  (default 100) */
    int          height;     /* maze height (default 100) */
    GeneratorAlg gen;        /* generation algorithm (default GEN_RECURSIVE_DFS) */
    SolverAlg    solve;      /* solver algorithm     (default SOLVE_BFS) */
    bool         animation;  /* whether animation is enabled (default false) */
    int          tick_rate;  /* ms per animation step; 0 when animation is false */
} Args;

/* Parse argc/argv into an Args struct using the project CLI spec.
   Calls die() on unknown flags or invalid values. */
Args parse_args(int argc, char *argv[]);
