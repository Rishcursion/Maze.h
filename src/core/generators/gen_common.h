#ifndef GEN_COMMON_H
#define GEN_COMMON_H

#include "core/maze.h"

// Direction Deltas
extern const int DX[4];
extern const int DY[4];
extern const int OPPOSITE[4];
// Helper function to shuffle array
void helper_shuffle(int *array, int n);
int helper_unvisited_neighbours(Maze *maze, int curr_x, int curr_y,
                                int *neighbour_x, int *neighbour_y);

int helper_valid_neighbours(Maze *maze, int curr_x, int curr_y,
                            int *neighbour_x, int *neighbour_y);
#endif // !GEN_COMMON_H
