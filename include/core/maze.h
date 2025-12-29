#ifndef MAZE_H
#define MAZE_H

// Bit flags that show the state of the maze
#define VISITED 0x10
#define UNVISITED 0x20
// Maze state struct, used to represent the maze state and attributes
typedef struct {
  int **state;
  int height;
  int width;
} Maze;

// Enum for LSB positions of wall flags
typedef enum { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 } DIRECTIONS;
// Enum for maze related errors
typedef enum {
  MAZE_OK = 0,
  MAZE_ERR_MEMORY = -1,
  MAZE_ERR_LOGIC = -2,
  MAZE_ERR_NULL = -3
} MAZE_ERRORS;
// Function Prototypes

Maze *maze_construct(
    int width,
    int height); // Used to initialize the MAZE struct with default values
void maze_destruct(Maze *maze); // Used to safely free the MAZE struct

#endif // !MAZE_H
