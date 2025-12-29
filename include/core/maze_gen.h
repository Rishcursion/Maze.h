#ifndef MAZE_GEN_H
#define MAZE_GEN_H

typedef struct Maze Maze; // Defined in include/maze.h
typedef enum {
  GEN_OK = 0,
  GEN_ERR_LOGIC = -1,
  GEN_ERR_NULL = -2,
} GEN_STATUS;

int gen_recursive_back_tracker(Maze *maze);
int gen_prims(Maze *maze);
int gen_ellers(Maze *maze);

#endif // !MAZE_GEN_H
