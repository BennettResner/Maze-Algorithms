#include "utilities.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

// --- ERROR HANDLING ---

void die(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    exit(1);
}

// --- MEMORY ---

void *safe_malloc(size_t n) {
    void *p = malloc(n);
    if (!p) die("malloc(%zu) failed", n);
    return p;
}

void *safe_calloc(size_t n, size_t size) {
    void *p = calloc(n, size);
    if (!p) die("calloc(%zu, %zu) failed", n, size);
    return p;
}

// --- ARGS ---

/* Return true if str is a valid positive integer. */
static bool is_positive_int(const char *str) {
    if (!str || *str == '\0') return false;
    for (const char *p = str; *p; p++) {
        if (!isdigit((unsigned char)*p)) return false;
    }
    return true;
}

Args parse_args(int argc, char *argv[]) {
    Args args = {
        .width      = 100,
        .height     = 100,
        .gen        = GEN_RECURSIVE_DFS,
        .solve      = SOLVE_BFS,
        .animation  = false,
        .tick_rate  = 0,
    };

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-size") == 0) {
            if (i + 1 >= argc || !is_positive_int(argv[i + 1]))
                die("-size requires a positive integer argument");
            args.width  = atoi(argv[++i]);
            /* Look-ahead: if the next token is also a number, treat as height. */
            if (i + 1 < argc && is_positive_int(argv[i + 1]))
                args.height = atoi(argv[++i]);
            else
                args.height = args.width;

        } else if (strcmp(argv[i], "-gen") == 0) {
            if (i + 1 >= argc) die("-gen requires an algorithm name");
            i++;
            if (strcmp(argv[i], "recursive_dfs") == 0)
                args.gen = GEN_RECURSIVE_DFS;
            else
                die("unknown generator '%s' (available: recursive_dfs)", argv[i]);

        } else if (strcmp(argv[i], "-solve") == 0) {
            if (i + 1 >= argc) die("-solve requires an algorithm name");
            i++;
            if (strcmp(argv[i], "bfs") == 0)
                args.solve = SOLVE_BFS;
            else if (strcmp(argv[i], "dfs") == 0)
                args.solve = SOLVE_DFS;
            else if (strcmp(argv[i], "astar") == 0)
                args.solve = SOLVE_ASTAR;
            else
                die("unknown solver '%s' (available: bfs, dfs, astar)", argv[i]);

        } else if (strcmp(argv[i], "-animation") == 0) {
            if (i + 1 >= argc || !is_positive_int(argv[i + 1]))
                die("-animation requires a positive integer tick rate (ms)");
            args.tick_rate = atoi(argv[++i]);
            if (args.tick_rate <= 0)
                die("-animation tick rate must be greater than 0");
            args.animation = true;

        } else {
            die("unknown argument '%s'", argv[i]);
        }
    }

    return args;
}
