#include "core/maze.h"
#include "utils/logger.h"
#include <stdlib.h>

// Used to dealloc memory one by one
void maze_destruct(Maze *maze) {
  if (!maze) {
    log_warn("Tried to destroy a NULL maze instance");
    return;
  }
  log_debug("Destroying maze instance...");
  if (maze->state) {
    for (int i = 0; i < maze->height; i++) {
      if (maze->state[i]) {
        free(maze->state[i]);
        maze->state[i] = NULL;
      }
    }
    free(maze->state);
    maze->state = NULL;
  }
  free(maze);
  maze = NULL;
  log_debug("Succesfully destroyed maze instance");
}

Maze *maze_construct(int width, int height) {
  log_debug("Initializing maze with Height: %d Width: %d", height, width);
  Maze *maze = malloc(sizeof(Maze));
  maze->height = height;
  maze->width = width;
  // Check if memory was allocated succesfully
  if (!maze) {
    free(maze);
    maze = NULL;
    log_error("Failed to allocate memory for initial maze creation");
    return NULL;
  }
  maze->state = calloc(height, sizeof(int *));
  if (!maze->state) {
    free(maze);
    maze = NULL;
    log_error("Failed to allocate memory for initial maze creation");
    return NULL;
  }
  for (int i = 0; i < height; i++) {
    maze->state[i] = (int *)calloc(width, sizeof(int));
    if (!maze->state[i]) {
      maze_destruct(maze);
      log_error("Failed to allocate memory for initial maze creation at row %d",
                i);
      return NULL;
    }
  };
  log_debug("Succesfully created maze instance");
  return maze;
}
