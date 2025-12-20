#include "bruhfirstsearch.h"
#include "../data_structures/queue.h"
#include <stdio.h>
#include <stdlib.h>
struct BFSResult {
  int x;
  int y;
  int distance;
};

struct Diameter {
  int puzzle_start_x, puzzle_start_y;
  int puzzle_end_x, puzzle_end_y;
  int minimum_steps;
};
const int NORTH = 1;
const int EAST = 2;
const int SOUTH = 4;
const int WEST = 8;
const int DX[] = {0, 1, 0, -1};
const int DY[] = {-1, 0, 1, 0};
const int WALL_FLAGS[] = {NORTH, EAST, SOUTH, WEST};
// helper function to free distance matrix
void bfs_free_matrix(int **matrix, int height) {
  if (matrix == NULL)
    return;
  for (int i = 0; i < height; i++) {
    free(matrix[i]);
  }
  free(matrix);
}
int **bfs_init_distance_matrix(int width, int height) {
  int **distance_matrix = NULL; // allocate HEIGHT columns
  distance_matrix = malloc(height * sizeof(int *));
  if (distance_matrix == NULL) {
    return NULL;
  }
  for (int i = 0; i < height; i++) {
    distance_matrix[i] = malloc(width * sizeof(int));
    if (distance_matrix[i] == NULL) {
      return NULL;
    }
    for (int j = 0; j < width; j++) {
      distance_matrix[i][j] = -1;
    }
  }
  return distance_matrix;
};

BFSResult bfs_get_end_node(Maze *maze, int start_x, int start_y) {

  // Create distance matrix to track distance from start node;
  int **distance_matrix = bfs_init_distance_matrix(maze->width, maze->height);
  Queue *processer = queue_init();
  distance_matrix[start_y][start_x] = 0;
  queue_push(processer, start_x,
             start_y); // We will always start from 0, 0 for each maze

  BFSResult end_node = {-1, -1, -1};

  if (!distance_matrix) {
    return end_node;
  }

  while (processer->count != 0) {
    QueueNode *node = queue_pop(processer);
    for (int i = 0; i < 4; i++) {
      int new_x = node->x_coord + DX[i];
      int new_y = node->y_coord + DY[i];
      int dir = WALL_FLAGS[i];
      int cum_dist = distance_matrix[node->y_coord][node->x_coord];
      if (cum_dist > end_node.distance) {
        end_node.distance = cum_dist;
        end_node.x = node->x_coord;
        end_node.y = node->y_coord;
      }
      // bounds check
      if (new_x < 0 || new_y < 0 || new_x >= maze->width ||
          new_y >= maze->height) {
        continue;
      }
      // Valid move check
      if ((maze->maze[node->y_coord][node->x_coord] & dir) == 0)
        continue;
      if (distance_matrix[new_y][new_x] == -1) {
        distance_matrix[new_y][new_x] = cum_dist + 1;
        queue_push(processer, new_x, new_y);
      }
    }
    free(node);
  }
  queue_free(processer);
  bfs_free_matrix(distance_matrix, maze->height);
  return end_node;
};

Diameter bfs_traverse_maze(Maze *maze) {
  Diameter solution = {-1, -1, -1, -1, -1};
  // First pass to determine the farthest node from initial node
  BFSResult start_point = bfs_get_end_node(maze, 0, 0);
  // Second pass to determine the farthest node from the farthest node
  // Guaranteed to find the longest path
  BFSResult end_point = bfs_get_end_node(maze, start_point.x, start_point.y);
  solution.puzzle_start_x = start_point.x;
  solution.puzzle_start_y = start_point.y;
  solution.puzzle_end_x = end_point.x;
  solution.puzzle_end_y = end_point.y;
  solution.minimum_steps = end_point.distance;
  return solution;
};
int bfs_test() {
  // 1. Setup Parameters
  int width = 20;
  int height = 20;

  printf("--- Generating %dx%d Maze using Prim's Algorithm ---\n", width,
         height);

  // 2. Generate the Maze
  // Using the signature from your header: Maze *maze_generate(int width, int
  // height);
  Maze *my_maze = maze_generate(width, height);

  if (my_maze == NULL) {
    fprintf(
        stderr,
        "Error: Failed to generate maze (Memory Allocation or Logic Error).\n");
    return EXIT_FAILURE;
  }

  // 3. Print the Maze Structure
  // Using the function from your header
  printf("\n[Generated Maze Map]\n");
  print_maze(my_maze);

  // 4. Run the Solver (Double BFS)
  printf("\n--- Solving (Finding Longest Path) ---\n");
  Diameter result = bfs_traverse_maze(my_maze);

  // 5. Report Numerical Results
  // These coordinates are exactly what you need to pass to your game
  // engine/renderer
  for (int i = 0; i < my_maze->height; i++) {
    for (int j = 0; j < my_maze->width; j++) {
      for (int h = 4; h >= 0; h--) {
        int k = my_maze->maze[i][j] >> h; // Shift the bit to position 0
        if (k & 1)                        // Check if the bit is 1 or 0
          printf("1");
        else
          printf("0");
      }
      printf(" ");
    }
    printf("\n");
  }
  printf("\n");
  printf("Calculated Longest Path (Diameter):\n");
  printf("  Start Node: (%d, %d)\n", result.puzzle_start_x,
         result.puzzle_start_y);
  printf("  End Node:   (%d, %d)\n", result.puzzle_end_x, result.puzzle_end_y);
  printf("  Distance:   %d steps\n", result.minimum_steps);

  // Note: Since 'maze_free' is not in your header, verify how you want to clean
  // up. Ideally, you should add a maze_free(Maze *m) function to primnproper.h
  // later.

  return EXIT_SUCCESS;
}
