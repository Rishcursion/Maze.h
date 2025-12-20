#include "primnproper.h"
#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- LOCAL CONSTANTS ---
// We use these arrays to iterate i = 0..3
const int WALL_FLAGS[] = {NORTH, EAST, SOUTH, WEST};
const int OPPOSITE_FLAGS[] = {SOUTH, WEST, NORTH, EAST};

int add_visitor(Node *node, Maze *maze, Frontier *visit_queue) {
  // 1. Bounds Check
  if (node->x_coord < 0 || node->x_coord >= maze->width || node->y_coord < 0 ||
      node->y_coord >= maze->height) {
    return EXIT_FAILURE;
  }

  // 2. Unvisited Check (Cell value is 0)
  if (maze->maze[node->y_coord][node->x_coord] == 0) {
    // Mark as Candidate (UNVISITED)
    maze->maze[node->y_coord][node->x_coord] |= UNVISITED;
    array_push(visit_queue, node->x_coord, node->y_coord);
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
};

int mark_visitor(Node *node, Maze *maze, Frontier *visit_queue) {
  // 1. Mark current cell as part of Maze (VISITED)
  maze->maze[node->y_coord][node->x_coord] |= VISITED;
  // 2. Remove the Candidate flag (UNVISITED)
  maze->maze[node->y_coord][node->x_coord] &= ~UNVISITED;

  // 3. Add valid neighbors to the frontier
  for (int i = 0; i < 4; i++) {
    Node new_node;
    new_node.x_coord = node->x_coord + DX[i];
    new_node.y_coord = node->y_coord + DY[i];

    // add_visitor handles bounds and 'is 0' checks internally
    add_visitor(&new_node, maze, visit_queue);
  }
  return EXIT_SUCCESS;
};

// Helper to find which visited neighbor we should connect to
Frontier *get_neighbours(Node *node, Maze *maze) {
  Frontier *neighbours = array_init(4);

  for (int i = 0; i < 4; i++) {
    int nx = node->x_coord + DX[i];
    int ny = node->y_coord + DY[i];

    // Check Bounds
    if (nx >= 0 && nx < maze->width && ny >= 0 && ny < maze->height) {
      // Check if this neighbor is already IN the maze (VISITED)
      if (maze->maze[ny][nx] & VISITED) {
        array_push(neighbours, nx, ny);
      }
    }
  }
  return neighbours;
};

// Helper to calculate the wall flag between two adjacent nodes
int get_direction_flag(Node *from, Node *to) {
  // Check all 4 directions to see which one matches the offset
  for (int i = 0; i < 4; i++) {
    if ((from->x_coord + DX[i] == to->x_coord) &&
        (from->y_coord + DY[i] == to->y_coord)) {
      return WALL_FLAGS[i];
    }
  }
  return 0;
}

// Helper to get the opposite flag (for the target cell)
int get_opposite_flag(int flag) {
  for (int i = 0; i < 4; i++) {
    if (WALL_FLAGS[i] == flag)
      return OPPOSITE_FLAGS[i];
  }
  return 0;
}

void prim_maze_generate(Maze *my_maze) {
  // 1. Initialize
  srand(time(NULL));
  Frontier *visit_queue = array_init(10);

  // Add arbitrary start node (0,0)
  Node start_node = {0, 0};
  add_visitor(&start_node, my_maze, visit_queue);

  while (visit_queue->num_elements > 0) {
    // A. Pick random node from frontier (The "Growth Candidate")
    Node current = array_delete_random(visit_queue);

    // B. Find neighbours that are ALREADY part of the maze
    Frontier *neighbours = get_neighbours(&current, my_maze);

    if (neighbours->num_elements > 0) {
      // C. Connect to ONE random existing maze cell
      Node target = array_delete_random(neighbours);

      // Calculate Direction Flags
      int dir =
          get_direction_flag(&target, &current); // Flag for Target -> Current
      int opp = get_opposite_flag(dir);          // Flag for Current -> Target

      // Carve the path (Open walls)
      my_maze->maze[target.y_coord][target.x_coord] |= dir;
      my_maze->maze[current.y_coord][current.x_coord] |= opp;
    }

    // D. Mark current as VISITED and add its empty neighbors to frontier
    mark_visitor(&current, my_maze, visit_queue);

    // E. Cleanup
    array_clean(neighbours);
  }

  printf("\nCleaning up generation memory...\n");
  array_clean(visit_queue);
}
