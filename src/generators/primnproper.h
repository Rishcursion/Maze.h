#ifndef primnproper
#include "../data_structures/dynamic_array.h"

typedef struct {
  int **maze;
  size_t width;
  size_t height;
} Maze;
// Used to verify whether coords are valid and adds that to potential candidate
// nodes

int add_visitor(Node *node, Maze *maze, Frontier *visit_queue);
// Used to add nodes 4-adjacent to current coordinates to visit
int mark_visitor(Node *node, Maze *maze, Frontier *visit_queue);
// Retrieves neighbours adjacent to current coordinates in the maze
Frontier *get_neighbours(Node *node, Maze *maze);
// Returns direction to turn to by comparing new and old coordinates
int get_direction(Node *old_node, Node *new_node);

#endif // !pnp
