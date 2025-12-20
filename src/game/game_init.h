#ifndef GAME_INIT_H
#define GAME_INIT_H
#include "../generators/backtracktothefuture.h"
#include "../generators/primnproper.h"
#include "../solvers/bruhfirstsearch.h"
#include "menu.h"
#include "player.h"
typedef struct {
  PlayerState player;
  Maze *maze_state;
  CONFIG game_config;
} GameState;

GameState game_initialize(CONFIG game_config);
#endif // !GAME_INIT_H
