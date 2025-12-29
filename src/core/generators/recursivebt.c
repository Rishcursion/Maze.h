#include "core/maze.h"
#include "gen_common.h"
#include "utils/logger.h"
#include <stdlib.h>

int rbt_dig(Maze *maze, int x, int y) {

  if (!(x >= 0 && x < maze->width && y >= 0 && y < maze->height)) {
    log_error("Provided coordinates [X: %d, Y: %d] not valid in %d x %d maze",
              x, y, maze->height, maze->width);
    return EXIT_FAILURE;
  }
  log_debug("Identifying direction to dig at coordinates-> X: %d Y: %d", x, y);

  int directions[] = {NORTH, EAST, WEST, SOUTH};
  helper_shuffle(directions, 4);
  for (int i = 0; i < 3; i++) {
    int direction = directions[i];
    int new_x = x + DX[direction];
    int new_y = y + DY[direction];
    // bounds check
    if (new_x >= 0 && new_x < maze->width && new_y >= 0 &&
        new_y < maze->height) {
      maze->state[y][x] |=
          1 << direction; // Set the bit of the currently chosen direction
      maze->state[new_y][new_x] |=
          1 << OPPOSITE[direction]; // We bit shift by 1 to set the bit flag
                                    // for that direction
      rbt_dig(maze, new_x, new_y);
    }
  }
  return EXIT_SUCCESS;
}
