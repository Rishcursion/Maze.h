#include "gen_common.h"
#include "core/maze.h"
#include "utils/logger.h"
#include <stdlib.h>
/*
Specifies the deltas for the cardinal direction and the movement to be made
[NORTH, EAST, SOUTH, WEST]
Also corresponds with flags when bit shifted
*/

const int DX[4] = {0, 1, 0, -1};
const int DY[4] = {-1, 0, 1, 0};
const int OPPOSITE[4] = {2, 3, 0, 1};

void helper_shuffle(int *array, int n) {

  log_debug("Shuffling array with %d elements and initial order ->", n);
  for (int i = 0; i < n; i++) {
    log_trace("%d ", array[i]);
  }

  if (n > 1) {
    int i;
    for (i = 0; i < n - 1; i++) {
      size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
  log_debug("Shuffled Array -> ");
  for (int i = 0; i < n; i++) {
    log_trace("%d ", array[i]);
  }
}

// Used for identifying neighbours that have been visited i.e. in the frontier
int helper_valid_neighbours(Maze *maze, int curr_x, int curr_y,
                            int *neighbour_x, int *neighbour_y) {
  log_debug("Identifying valid neighbours at coordinates X: %d Y: %d", curr_x,
            curr_y);
  int n_idx = 0;
  for (int i = 0; i < 4; i++) {
    int new_x = curr_x + DX[i];
    int new_y = curr_y + DY[i];
    log_trace("Checking neighbour with delta coordinates-> X: %d + %d Y:%d %d",
              curr_x, DX[i], curr_y, DY[i]);
    // Check if current node is valid i.e. within maze bounds
    if (new_x >= 0 && new_x < maze->width && new_y >= 0 &&
        new_y < maze->height) {
      // Check if current node has been visited
      if (maze->state[new_y][new_x] & VISITED) {
        neighbour_x[n_idx] = new_x;
        neighbour_y[n_idx] = new_y;
        n_idx += 1;
      }
    }
  }
  log_debug("Found %d valid neighbours", n_idx);
  return n_idx;
}
// Used for getting all neighbouring nodes that have not been visited yet
int helper_unvisited_neighbours(Maze *maze, int curr_x, int curr_y,
                                int *neighbour_x, int *neighbour_y) {
  log_debug("Identifying valid neighbours at coordinates X: %d Y: %d", curr_x,
            curr_y);
  int n_idx = 0;
  for (int i = 0; i < 4; i++) {
    int new_x = curr_x + DX[i];
    int new_y = curr_y + DY[i];
    log_trace("Checking neighbour with delta coordinates-> X: %d + %d Y:%d %d",
              curr_x, DX[i], curr_y, DY[i]);
    if (new_x >= 0 && new_x < maze->width && new_y >= 0 &&
        new_y < maze->height) {
      // Check if current node has not been visited
      if (!(maze->state[new_y][new_x] & VISITED)) {

        neighbour_x[n_idx] = new_x;
        neighbour_y[n_idx] = new_y;
        n_idx += 1;
      }
    }
  }
  return n_idx;
}
