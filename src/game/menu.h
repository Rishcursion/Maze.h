#ifndef MENU_H
#define MENU_H

typedef enum { ALGO_PRIMS, ALGO_RECURSIVE_BACKTRACKER } AlgoType;
typedef enum { MASTER_DFS, MASTER_BFS, MASTER_A_STAR } PuzzleMaster;
typedef enum { MODE_2D, MODE_3D } RENDER;
typedef struct {
  PuzzleMaster master;
  AlgoType maze_algorithm;
  RENDER view;
  int width;
  int height;
} CONFIG;

CONFIG get_user_config(void);
#endif // !MENU_H
