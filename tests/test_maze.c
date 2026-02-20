#include <criterion/criterion.h>
#include "../src/maze.h"

// --- SUITE: initiate_maze ---

Test(maze, initiate_stores_dimensions) {
    Cell buffer[3 * 3];
    Maze maze;
    initiate_maze(&maze, buffer, 3, 3);
    cr_assert_eq(maze.width,  3);
    cr_assert_eq(maze.height, 3);
}

Test(maze, initiate_stores_buffer_pointer) {
    Cell buffer[3 * 3];
    Maze maze;
    initiate_maze(&maze, buffer, 3, 3);
    cr_assert_eq(maze.cells, buffer);
}

Test(maze, initiate_all_walls_present) {
    Cell buffer[3 * 3];
    Maze maze;
    initiate_maze(&maze, buffer, 3, 3);
    int total_cells = 3 * 3;
    for (int cell_index = 0; cell_index < total_cells; cell_index++) {
        cr_assert(maze.cells[cell_index].north, "cell %d north should be true", cell_index);
        cr_assert(maze.cells[cell_index].south, "cell %d south should be true", cell_index);
        cr_assert(maze.cells[cell_index].east,  "cell %d east should be true",  cell_index);
        cr_assert(maze.cells[cell_index].west,  "cell %d west should be true",  cell_index);
    }
}

// --- SUITE: destroy_wall ---

/* Helper: build a fresh 3x3 maze. Interior cell (1,1) has valid neighbors in all directions. */
static Maze make_3x3(Cell buffer[9]) {
    Maze maze;
    initiate_maze(&maze, buffer, 3, 3);
    return maze;
}

Test(maze, destroy_north_clears_current_and_neighbor) {
    Cell buffer[9];
    Maze maze = make_3x3(buffer);
    /* Remove north wall of (col=1, row=1) — neighbor is (col=1, row=0). */
    destroy_wall(&maze, 1, 1, NORTH);
    cr_assert(!maze.cells[1 * 3 + 1].north, "current cell north should be false");
    cr_assert(!maze.cells[0 * 3 + 1].south, "neighbor south should be false");
}

Test(maze, destroy_south_clears_current_and_neighbor) {
    Cell buffer[9];
    Maze maze = make_3x3(buffer);
    destroy_wall(&maze, 1, 1, SOUTH);
    cr_assert(!maze.cells[1 * 3 + 1].south, "current cell south should be false");
    cr_assert(!maze.cells[2 * 3 + 1].north, "neighbor north should be false");
}

Test(maze, destroy_east_clears_current_and_neighbor) {
    Cell buffer[9];
    Maze maze = make_3x3(buffer);
    destroy_wall(&maze, 1, 1, EAST);
    cr_assert(!maze.cells[1 * 3 + 1].east, "current cell east should be false");
    cr_assert(!maze.cells[1 * 3 + 2].west, "neighbor west should be false");
}

Test(maze, destroy_west_clears_current_and_neighbor) {
    Cell buffer[9];
    Maze maze = make_3x3(buffer);
    destroy_wall(&maze, 1, 1, WEST);
    cr_assert(!maze.cells[1 * 3 + 1].west, "current cell west should be false");
    cr_assert(!maze.cells[1 * 3 + 0].east, "neighbor east should be false");
}

Test(maze, destroy_north_leaves_other_walls_intact) {
    Cell buffer[9];
    Maze maze = make_3x3(buffer);
    destroy_wall(&maze, 1, 1, NORTH);
    /* Remaining walls on (1,1) should still be up. */
    cr_assert(maze.cells[1 * 3 + 1].south, "current south should remain true");
    cr_assert(maze.cells[1 * 3 + 1].east,  "current east should remain true");
    cr_assert(maze.cells[1 * 3 + 1].west,  "current west should remain true");
    /* Other walls on the neighbor (1,0) should still be up. */
    cr_assert(maze.cells[0 * 3 + 1].north, "neighbor north should remain true");
    cr_assert(maze.cells[0 * 3 + 1].east,  "neighbor east should remain true");
    cr_assert(maze.cells[0 * 3 + 1].west,  "neighbor west should remain true");
}
