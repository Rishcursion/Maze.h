#ifndef primnproper
#define primnproper
#include "../data_structures/dynamic_array.h"
#include "maze.h"
// Used to verify whether coords are valid and adds that to potential candidate
// nodes
int add_visitor(Node *node, Maze *maze, Frontier *visit_queue);
// Used to add nodes 4-adjacent to current coordinates to visit
int mark_visitor(Node *node, Maze *maze, Frontier *visit_queue);
// Retrieves neighbours adjacent to current coordinates in the maze
Frontier *get_neighbours(Node *node, Maze *maze);
// Returns direction to turn to by comparing new and old coordinates
int get_direction(Node *old_node, Node *new_node);
// Returns the final generated maze
Maze *maze_generate(int width, int height);
// prints the ASCII block version of the maze;
void print_maze(Maze *maze);
#endif // !pnp
