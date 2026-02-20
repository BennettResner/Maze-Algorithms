#include "maze.h"


// --- INITIATE ---

void initiate_maze(Maze *maze, Cell *cell_buffer, int width, int height) {
    maze->cells  = cell_buffer;
    maze->width  = width;
    maze->height = height;

    int total_cells = width * height;
    for (int cell_index = 0; cell_index < total_cells; cell_index++) {
        maze->cells[cell_index].north = true;
        maze->cells[cell_index].south = true;
        maze->cells[cell_index].east  = true;
        maze->cells[cell_index].west  = true;
    }
}

// --- DESTROY WALL ---

void destroy_wall(Maze *maze, int col, int row, Direction dir) {
    Cell *current_cell = &maze->cells[row * maze->width + col];

    switch (dir) {
        case NORTH:
            current_cell->north = false;
            maze->cells[(row - 1) * maze->width + col].south = false;
            break;
        case SOUTH:
            current_cell->south = false;
            maze->cells[(row + 1) * maze->width + col].north = false;
            break;
        case EAST:
            current_cell->east = false;
            maze->cells[row * maze->width + (col + 1)].west = false;
            break;
        case WEST:
            current_cell->west = false;
            maze->cells[row * maze->width + (col - 1)].east = false;
            break;
    }
}
