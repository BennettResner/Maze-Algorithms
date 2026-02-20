#include <criterion/criterion.h>
#include "../src/utilities.h"

// --- SUITE: defaults ---

Test(args, defaults) {
    char *argv[] = {"maze", NULL};
    Args a = parse_args(1, argv);
    cr_assert_eq(a.width,     100);
    cr_assert_eq(a.height,    100);
    cr_assert_eq(a.gen,       GEN_RECURSIVE_DFS);
    cr_assert_eq(a.solve,     SOLVE_BFS);
    cr_assert_eq(a.animation, false);
    cr_assert_eq(a.tick_rate, 0);
}

// --- SUITE: -size ---

Test(args, size_square) {
    char *argv[] = {"maze", "-size", "42", NULL};
    Args a = parse_args(3, argv);
    cr_assert_eq(a.width,  42);
    cr_assert_eq(a.height, 42);
}

Test(args, size_rect) {
    char *argv[] = {"maze", "-size", "30", "50", NULL};
    Args a = parse_args(4, argv);
    cr_assert_eq(a.width,  30);
    cr_assert_eq(a.height, 50);
}

Test(args, size_rect_lookahead_stops_at_flag) {
    /* Next token after width is a flag, not a number — height should equal width. */
    char *argv[] = {"maze", "-size", "30", "-gen", "recursive_dfs", NULL};
    Args a = parse_args(5, argv);
    cr_assert_eq(a.width,  30);
    cr_assert_eq(a.height, 30);
    cr_assert_eq(a.gen,    GEN_RECURSIVE_DFS);
}

Test(args, size_missing_value, .exit_code = 1) {
    char *argv[] = {"maze", "-size", NULL};
    parse_args(2, argv);
}

Test(args, size_non_integer, .exit_code = 1) {
    char *argv[] = {"maze", "-size", "abc", NULL};
    parse_args(3, argv);
}

// --- SUITE: -gen ---

Test(args, gen_recursive_dfs) {
    char *argv[] = {"maze", "-gen", "recursive_dfs", NULL};
    Args a = parse_args(3, argv);
    cr_assert_eq(a.gen, GEN_RECURSIVE_DFS);
}

Test(args, gen_unknown, .exit_code = 1) {
    char *argv[] = {"maze", "-gen", "bad_algo", NULL};
    parse_args(3, argv);
}

Test(args, gen_missing_value, .exit_code = 1) {
    char *argv[] = {"maze", "-gen", NULL};
    parse_args(2, argv);
}

// --- SUITE: -solve ---

Test(args, solve_bfs) {
    char *argv[] = {"maze", "-solve", "bfs", NULL};
    Args a = parse_args(3, argv);
    cr_assert_eq(a.solve, SOLVE_BFS);
}

Test(args, solve_dfs) {
    char *argv[] = {"maze", "-solve", "dfs", NULL};
    Args a = parse_args(3, argv);
    cr_assert_eq(a.solve, SOLVE_DFS);
}

Test(args, solve_astar) {
    char *argv[] = {"maze", "-solve", "astar", NULL};
    Args a = parse_args(3, argv);
    cr_assert_eq(a.solve, SOLVE_ASTAR);
}

Test(args, solve_unknown, .exit_code = 1) {
    char *argv[] = {"maze", "-solve", "dijkstra", NULL};
    parse_args(3, argv);
}

Test(args, solve_missing_value, .exit_code = 1) {
    char *argv[] = {"maze", "-solve", NULL};
    parse_args(2, argv);
}

// --- SUITE: -animation ---

Test(args, animation) {
    char *argv[] = {"maze", "-animation", "100", NULL};
    Args a = parse_args(3, argv);
    cr_assert_eq(a.animation, true);
    cr_assert_eq(a.tick_rate, 100);
}

Test(args, animation_missing_value, .exit_code = 1) {
    char *argv[] = {"maze", "-animation", NULL};
    parse_args(2, argv);
}

Test(args, animation_non_integer, .exit_code = 1) {
    char *argv[] = {"maze", "-animation", "fast", NULL};
    parse_args(3, argv);
}

// --- SUITE: combined flags ---

Test(args, combined_all_flags) {
    char *argv[] = {
        "maze", "-size", "10", "20",
        "-gen", "recursive_dfs",
        "-solve", "astar",
        "-animation", "50",
        NULL
    };
    Args a = parse_args(10, argv);
    cr_assert_eq(a.width,     10);
    cr_assert_eq(a.height,    20);
    cr_assert_eq(a.gen,       GEN_RECURSIVE_DFS);
    cr_assert_eq(a.solve,     SOLVE_ASTAR);
    cr_assert_eq(a.animation, true);
    cr_assert_eq(a.tick_rate, 50);
}

// --- SUITE: unknown flag ---

Test(args, unknown_flag, .exit_code = 1) {
    char *argv[] = {"maze", "-verbose", NULL};
    parse_args(2, argv);
}
