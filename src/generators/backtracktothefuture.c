#include "backtracktothefuture.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Cardinal { NORTH = 1, EAST = 2, SOUTH = 4, WEST = 8 };

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
const int DX[] = {0, 1, 0, 0, -1};
const int DY[] = {-1, 0, 1, 0, 0};
const int OPPOSITE[] = {SOUTH, WEST, NORTH, 0, EAST};

int shuffle_arr(int size, int *array) {
  for (int i = 0; i < size - 1; i++) {
    int r = i + (rand() % (size - i));
    int temp = array[i];
    array[i] = array[r];
    array[r] = temp;
  }
  return EXIT_SUCCESS;
};

int delorean(int s_x, int s_y, int width, int height, int **maze) {
  int directions[] = {NORTH, SOUTH, EAST, WEST};
  shuffle_arr(4, directions);
  int n_x, n_y;
  for (int i = 0; i < 4; i++) {
    int direction = (directions[i]);
    n_x = s_x + DX[(direction >> 1)];
    n_y = s_y + DY[(direction >> 1)];
    // Valid move check i.e. bounds check and unvisited check
    if (((n_x < width) & (n_x >= 0)) && ((n_y >= 0) & (n_y < height))) {
      // unvisited check
      if (maze[n_x][n_y] == 0) {
        maze[s_x][s_y] |= direction;
        maze[n_x][n_y] |= OPPOSITE[(direction >> 1)];
        // recursive call from new position
        delorean(n_x, n_y, width, height, maze);
      }
    }
  }
  return EXIT_SUCCESS;
}
void print_ascii_maze(int w, int h, int **maze) {
  // Loop through every row of the maze
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
      if (maze[x][y] & EAST) {
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
      if (maze[x][y] & SOUTH) {
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

// Main function to test , don't forget to comment it out;

/* int main(int argc, char *argv[]) {
//Expected Arguements
//argv[0]-> program name
//argv[1] -> maze height
//argv[2] -> maze width
  if (argc < 3) {
    printf("Not enough arguments...");
    return EXIT_FAILURE;
  }
  int width = atoi(argv[2]);
  int height = atoi(argv[1]);
  // initialize maze
  int **maze = malloc(width * sizeof(int *));
  for (int i = 0; i < width; i++) {
    maze[i] = calloc(height, sizeof(int));
  }
  // Set maze values to 0;
  delorean(0, 0, width, height, maze);
  print_ascii_maze(width, height, maze);
  for (int i = 0; i < width; i++) {
    free(maze[i]);
  }
  free(maze);
  return EXIT_SUCCESS;
} */
