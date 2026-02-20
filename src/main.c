#include "maze.h"
#include "utilities.h"
#include "generators/RecursiveDFS.h"
#include "searchers/BFS.h"
#include "render/render.h"

// --- MAIN ---

int main(int argc, char *argv[]) {
    Args args = parse_args(argc, argv);

    Cell cell_buffer[args.width * args.height];
    Maze maze;
    initiate_maze(&maze, cell_buffer, args.width, args.height);

    switch (args.gen) {
        case GEN_RECURSIVE_DFS:
            /* TODO: recursive_dfs_generate(&maze); */
            break;
    }

    return 0;
}
