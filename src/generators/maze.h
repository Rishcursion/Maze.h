#ifndef MAZE_H
#define MAZE_H
#include <stddef.h>

typedef struct {
  int **maze;
  size_t width;
  size_t height;
} Maze;

typedef enum { NORTH, EAST, SOUTH, WEST } DIRECTIONS;
extern const int DY[];
extern const int DX[];
extern const int OPPOSITE[];
extern const int VISITED;
extern const int UNVISITED;

void print_maze(Maze *maze);
void print_ascii_maze(Maze *maze);
Maze *maze_init(int width, int height);
void maze_free(Maze *maze);
#endif // !MAZE_H
