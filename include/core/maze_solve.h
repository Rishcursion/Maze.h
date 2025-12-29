#ifndef MAZE_SOLVE_H
#define MAZE_SOLVE_H
#include "../ds/dynamic_array.h"
typedef struct Maze Maze;
typedef enum {
  SOLVE_OK = 0,
  SOLVE_ERR_LOGIC = -1,
  SOLVE_ERR_NULL = -2
} SOLVE_STATUS;

int solve_bfs(Maze *maze, int start_x,
              int start_y); // Used for generating longest path

DynamicArray *solve_astar(
    Maze *maze, int start_x, int start_y, int end_x,
    int end_y); // Used for generating paths between custom start and end points

#endif // !MAZE_SOLVE_H
