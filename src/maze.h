#pragma once

#include <stdbool.h>

/*
 * Coordinate system:
 *   col: 0 = left edge, increases rightward (x-axis)
 *   row: 0 = top edge,  increases downward  (y-axis)
 *
 *   NORTH = row - 1    SOUTH = row + 1
 *   WEST  = col - 1    EAST  = col + 1
 *
 * Cell indexing: cells[row * width + col]
 */

// --- DIRECTION ---

typedef enum { NORTH, SOUTH, EAST, WEST } Direction;

// --- CELL ---

typedef struct {
    bool north;
    bool south;
    bool east;
    bool west;
} Cell;

// --- MAZE ---

typedef struct {
    Cell *cells;
    int   width;
    int   height;
} Maze;

// --- MAZE FUNCTIONS ---

/* Initialise a width x height maze using a caller-owned cell buffer.
   The buffer must hold at least width * height Cell elements.
   Sets all walls to present. Does not allocate any memory. */
void initiate_maze(Maze *maze, Cell *cell_buffer, int width, int height);

/* Remove the wall between the cell at (col, row) and its neighbor in direction dir.
   Also removes the reciprocal wall on the neighbor to keep the maze consistent. */
void destroy_wall(Maze *maze, int col, int row, Direction dir);
