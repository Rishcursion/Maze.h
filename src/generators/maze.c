#include "maze.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/*
Instead of using a sparse matrix with 9*2 bytes, i decided to use a
padded matrix off by one, where i'll bitshift the cardinal directions
to access the respective delta operation.
If the number of directions is increased, the matrix will need to be padded
by the number of bits required to represent the maximum cardinality integer.

NORTH = 1 << 1 = 0
EAST = 2 << 1 = 1
SOUTH = 4 << 1 = 2
WEST = 8 << 1 = 4

index 3 is the padded space.
*/
const int DX[] = {0, 1, 0, -1}; // Adjusted to match N, E, S, W index
const int DY[] = {-1, 0, 1, 0};
const int OPPOSITE[] = {SOUTH, WEST, NORTH, EAST};
const int VISITED = 0x10;
const int UNVISITED = 0x20;
void print_ascii_maze(Maze *print_maze) {
  // Loop through every row of the maze
  int h = print_maze->height;
  int w = print_maze->width;
  int **maze = print_maze->maze;
  for (int y = 0; y < h; y++) {

    // --- LINE 1: CEILINGS ---
    // For the first row, we just print a solid top border
    if (y == 0) {
      for (int x = 0; x < w; x++)
        printf("+---");
      printf("+\n");
    }

    // --- LINE 2: WALLS & ROOMS ---
    // Start with the Leftmost wall
    printf("|");
    for (int x = 0; x < w; x++) {
      // The Room itself is empty space
      printf("   ");

      // The East Wall: Check if there is a path East
      // If path exists (1), draw space " ". If not (0), draw wall "|".
      if (maze[y][x] & EAST) {
        printf(" ");
      } else {
        printf("|");
      }
    }
    printf("\n");

    // --- LINE 3: FLOORS ---
    // Start with the Leftmost corner
    printf("+");
    for (int x = 0; x < w; x++) {
      // The South Wall: Check if there is a path South
      // If path exists (1), draw gap "   ". If not (0), draw wall "---".
      if (maze[y][x] & SOUTH) {
        printf("   ");
      } else {
        printf("---");
      }
      // The Corner is always a plus
      printf("+");
    }
    printf("\n");
  }
}

void print_maze(Maze *maze) {
  // Print Top Border
  for (int i = 0; i < maze->width; i++)
    printf("+---");
  printf("+\n");

  for (int y = 0; y < maze->height; y++) {
    // Print West wall of the row
    printf("|");
    for (int x = 0; x < maze->width; x++) {
      // CELL BODY: Check if connected EAST
      if (maze->maze[y][x] & EAST) {
        printf("    "); // No wall
      } else {
        printf("   |"); // Wall
      }
    }
    printf("\n");

    // CELL BOTTOM: Check if connected SOUTH
    printf("+");
    for (int x = 0; x < maze->width; x++) {
      if (maze->maze[y][x] & SOUTH) {
        printf("   +"); // No wall (path down)
      } else {
        printf("---+"); // Wall
      }
    }
    printf("\n");
  }
}

void maze_free(Maze *maze) {
  for (int i = 0; i < maze->height; i++) {
    free(maze->maze[i]);
    maze->maze[i] = NULL;
  }
  free(maze->maze);
  maze->maze = NULL;
  free(maze);
  maze = NULL;
}
Maze *maze_init(int width, int height) {
  Maze *maze = NULL;

  // 1. Allocate the Wrapper
  maze = (Maze *)malloc(sizeof(Maze));
  if (!maze) {
    return NULL;
  }
  maze->width = width;
  maze->height = height;

  // 2. Allocate the Spine (Array of Pointers)
  maze->maze = (int **)malloc(height * sizeof(int *));
  if (!maze->maze) {
    free(maze); // Safe, nothing else allocated yet
    return NULL;
  }

  // 3. Allocate the Ribs (The Rows)
  for (int i = 0; i < height; i++) {
    // FIX 1: Use sizeof(int), not sizeof(int*)
    maze->maze[i] = (int *)calloc(width, sizeof(int));

    // FIX 2: Proper Cleanup on Failure
    if (!maze->maze[i]) {
      maze_free(maze);
    }
  }

  return maze;
}
