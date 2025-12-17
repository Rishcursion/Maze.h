#ifndef primnproper

// Used to verify whether coords are valid and adds that to potential candidate
// nodes
int add_visitor(int x_coord, int y_coord, int **maze, int *visit_queue);
// Used to add nodes 4-adjacent to current coordinates to visit
int mark_visitor(int x_coord, int y_coord, int **maze, int *visit_queue);
// Retrieves neighbours adjacent to current coordinates in the maze
int get_neighbours(int x_coord, int y_coord, int **maze);
// Returns direction to turn to by comparing new and old coordinates
int get_direction(int x_coord, int y_coord, int new_x, int new_y);

#endif // !pnp
