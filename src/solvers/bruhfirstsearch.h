#ifndef BFS_H
#define BFS_H
#include "../generators/primnproper.h"

typedef struct {
  int x;
  int y;
  int distance;
} BFSResult;

typedef struct {
  int puzzle_start_x, puzzle_start_y;
  int puzzle_end_x, puzzle_end_y;
  int minimum_steps;
} Diameter;

int **bfs_init_distance_matrix(int width, int height);
BFSResult bfs_get_end_node(Maze *maze, int start_x, int start_y);
Diameter bfs_traverse_maze(Maze *maze);
#endif // !BFS_H
