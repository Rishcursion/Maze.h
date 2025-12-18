#include "primnproper.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct Node {
  int x_coord;
  int y_coord;
};
struct Frontier {
  Node *nodes;
  int num_elements;
  int capacity;
};
struct Maze {
  int **maze;
  int width;
  int height;
};

enum DIRECTIONS { NORTH = 1, EAST = 2, SOUTH = 4, WEST = 8 };

const int VISITED = 0x10;
const int UNVISITED = 0x20;
const int OPPOSITE[] = {4, 8, 1, 0, 2};

int add_visitor(Node *node, Maze *maze, Frontier *visit_queue) {
  if ((node->x_coord >= 0 && node->x_coord < maze->width) &&
      (node->y_coord >= 0 && node->y_coord < maze->height) &&
      (maze->maze[node->y_coord][node->x_coord] == 0)) {
    maze->maze[node->y_coord][node->x_coord] |= UNVISITED;
    array_push(visit_queue, node->x_coord, node->y_coord);
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
};
int mark_visitor(Node *node, Maze *maze, Frontier *visit_queue) {
  maze->maze[node->y_coord][node->x_coord] |= VISITED;
  for (int i = -1; i < 2; i++) {
    if (i != 0) {
      Node new_node = {node->x_coord + i, node->y_coord};
      Node new_node_2 = {node->x_coord, node->y_coord + i};
      add_visitor(&new_node, maze, visit_queue);
      add_visitor(&new_node_2, maze, visit_queue);
    }
  }
  return EXIT_SUCCESS;
};
int get_direction(Node *old_node, Node *new_node) {
  if (old_node->x_coord < new_node->x_coord) {
    return EAST;
  }
  if (old_node->x_coord > new_node->x_coord) {
    return WEST;
  }
  if (old_node->y_coord < new_node->y_coord) {
    return SOUTH;
  }
  if (old_node->y_coord > new_node->y_coord) {
    return NORTH;
  }
  return 0;
};
Frontier *get_neighbours(Node *node, Maze *maze) {
  Frontier *neighbours = array_init(4);
  if (node->x_coord > 0 &&
      maze->maze[node->y_coord][node->x_coord - 1] & VISITED) {
    array_push(neighbours, node->x_coord - 1, node->y_coord);
  }
  if (node->x_coord + 1 < maze->width &&
      maze->maze[node->y_coord][node->x_coord + 1] & VISITED) {
    array_push(neighbours, node->x_coord + 1, node->y_coord);
  }
  if (node->y_coord > 0 &&
      maze->maze[node->y_coord - 1][node->x_coord] & VISITED) {
    array_push(neighbours, node->x_coord, node->y_coord - 1);
  }
  if (node->y_coord + 1 < maze->height &&
      maze->maze[node->y_coord + 1][node->x_coord] & VISITED) {
    array_push(neighbours, node->x_coord, node->y_coord + 1);
  }
  return neighbours;
};
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
int main(void) {
  int width, height;

  // 1. Setup
  srand(time(NULL));
  printf("Enter Maze Width: ");
  if (scanf("%d", &width) != 1)
    return EXIT_FAILURE;
  printf("Enter Maze Height: ");
  if (scanf("%d", &height) != 1)
    return EXIT_FAILURE;

  // Allocate Maze Struct
  Maze *my_maze = (Maze *)malloc(sizeof(Maze));
  my_maze->width = width;
  my_maze->height = height;

  // Allocate 2D Grid (using calloc to init to 0)
  my_maze->maze = (int **)malloc(height * sizeof(int *));
  for (int i = 0; i < height; i++) {
    my_maze->maze[i] = (int *)calloc(width, sizeof(int));
  }

  // Initialize Frontier
  Frontier *visit_queue = array_init(10); // Start small, it will grow

  // 2. Prim's Algorithm Start
  // Start at random point (e.g., 0,0)
  Node start_node = {0, 0};
  add_visitor(&start_node, my_maze, visit_queue);

  while (visit_queue->num_elements > 0) {
    // A. Pick random node from frontier
    Node current = array_delete_random(visit_queue);

    // B. Connect to the maze
    // Find neighbours that are ALREADY part of the maze (VISITED)
    Frontier *neighbours = get_neighbours(&current, my_maze);

    if (neighbours->num_elements > 0) {
      // Connect to one random visited neighbour
      Node target = array_delete_random(neighbours);
      int dir =
          get_direction(&target, &current); // Direction FROM target TO current
      int opp = OPPOSITE[dir >> 1];

      // Carve the path (Set bits)
      my_maze->maze[target.y_coord][target.x_coord] |= dir;
      my_maze->maze[current.y_coord][current.x_coord] |= opp;
    }

    // C. Mark current as visited and add its unvisited neighbours to frontier
    mark_visitor(&current, my_maze, visit_queue);

    // D. Clean up the temporary neighbours list
    array_clean(neighbours);
  }

  // 3. Output
  print_maze(my_maze);

  // 4. Cleanup
  printf("\nCleaning up memory...\n");

  // Free Grid
  for (int i = 0; i < height; i++) {
    free(my_maze->maze[i]);
  }
  free(my_maze->maze);
  free(my_maze);

  // Free Frontier
  array_clean(visit_queue);

  printf("Done.\n");
  return EXIT_SUCCESS;
}
