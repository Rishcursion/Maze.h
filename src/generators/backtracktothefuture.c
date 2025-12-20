#include "backtracktothefuture.h"
#include "maze.h"
#include <stdlib.h>

// Helper to shuffle direction indices (0-3) for randomness
int shuffle_arr(int size, int *array) {
  for (int i = 0; i < size - 1; i++) {
    int r = i + (rand() % (size - i));
    int temp = array[i];
    array[i] = array[r];
    array[r] = temp;
  }
  return EXIT_SUCCESS;
}

// Helper to get the opposite direction index (0->2, 1->3, etc.)
// N(0)<->S(2), E(1)<->W(3)
int get_opposite_idx(int dir_idx) { return (dir_idx + 2) % 4; }

// The Recursive Backtracker Algorithm
// Signature updated to use Maze* struct
int delorean(Maze *maze, int cx, int cy) {
  // 1. Define Directions Indices (0:North, 1:East, 2:South, 3:West)
  int directions[] = {NORTH, EAST, SOUTH, WEST};
  shuffle_arr(4, directions);

  int nx, ny;

  // 2. Iterate through randomized directions
  for (int i = 0; i < 4; i++) {
    int dir_idx = directions[i];

    // Calculate new coordinates using the shared arrays from maze.h
    nx = cx + DX[dir_idx];
    ny = cy + DY[dir_idx];

    // 3. Bounds Check
    if (nx >= 0 && nx < maze->width && ny >= 0 && ny < maze->height) {

      // 4. Unvisited Check
      // (If cell is 0, it has no walls carved yet, so it is unvisited)
      if (maze->maze[ny][nx] == 0) {

        // 5. Carve Walls (Set Bitmasks)
        // We use bitshifting to create the flags:
        // 1<<0(1)=N, 1<<1(2)=E, 1<<2(4)=S, 1<<3(8)=W
        maze->maze[cy][cx] |= (1 << dir_idx);
        maze->maze[ny][nx] |= (1 << get_opposite_idx(dir_idx));

        // 6. Recursive Call (The "Backtrack" happens when this returns)
        delorean(maze, nx, ny);
      }
    }
  }
  return EXIT_SUCCESS;
}
