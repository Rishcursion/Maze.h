#include "menu.h"
#include <stdio.h>

// --- CONSTANTS ---
// Change these here to adjust the limits for the entire menu
#define MIN_MAZE_SIZE 5
#define MAX_MAZE_SIZE 100

void clear_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

CONFIG get_user_config() {
  // Initialize with safe defaults
  CONFIG game_config = {MASTER_BFS, ALGO_PRIMS, MODE_2D, 20, 20};

  int choice = 0;
  int running = 1;

  printf("=====================================================\n");
  printf("    THE MAZE MASTER  (WRITTEN IN C AND BLOOD)\n");
  printf("                  and a lot of tears\n");
  printf("=====================================================\n\n");

  while (running) {
    // Print Menu INSIDE the loop so user sees it again after picking
    printf("\n--- CURRENT CONFIGURATION ---\n");
    printf("Mode: %s | Algo: %s | Solver: %s | Size: %dx%d\n",
           (game_config.view == MODE_3D) ? "3D (DOOM)" : "2D (PACMAN)",
           (game_config.maze_algorithm == ALGO_PRIMS) ? "Prims" : "Backtracker",
           (game_config.master == MASTER_BFS)
               ? "BFS (Longest)"
               : (game_config.master == MASTER_DFS ? "DFS (Deepest)"
                                                   : "A* (Shortest)"),
           game_config.width, game_config.height);

    printf("\n[1] Set Rendering Style (2D or 3D)\n");
    printf("[2] Choose Maze Generation Algorithm\n");
    printf("[3] Choose Maze Problem Setter Algorithm\n");
    printf("[4] Set Height And Width\n");
    printf("[5] START GAME\n");
    printf(">> ");

    if (scanf("%d", &choice) != 1) {
      printf("Invalid input. Don't break the code, please.\n");
      clear_buffer();
      continue;
    }

    switch (choice) {
    case 1: { // Rendering
      int secondary_choice;
      printf("\n--- VISUALS ---\n");
      printf(
          "[3] 3D Rendered Maze (DOOM-style, might cause motion sickness)\n");
      printf("[2] 2D Rendered Maze (PACMAN-style, classic and safe)\n");
      printf(">> ");
      scanf("%d", &secondary_choice);

      if (secondary_choice == 3) {
        game_config.view = MODE_3D;
        printf(">> Mode set to 3D. Good luck.\n");
      } else if (secondary_choice == 2) {
        game_config.view = MODE_2D;
        printf(">> Mode set to 2D.\n");
      } else {
        printf(">> Incorrect Option. Keeping previous setting.\n");
      }
      break;
    }

    case 2: { // Algorithm
      char algorithm_choice;
      printf("\n--- GENERATION STRATEGY ---\n");
      printf("[A] Prim's Algorithm (Short Branches, Looks Like Shattered "
             "Glass)\n");
      printf("[B] Recursive Backtracker (Long Winding Rivers, You WILL Get "
             "Lost)\n");
      printf(">> ");

      scanf(" %c", &algorithm_choice);

      if (algorithm_choice == 'A' || algorithm_choice == 'a') {
        game_config.maze_algorithm = ALGO_PRIMS;
        printf(">> Algo set to Prim's.\n");
      } else if (algorithm_choice == 'B' || algorithm_choice == 'b') {
        game_config.maze_algorithm = ALGO_RECURSIVE_BACKTRACKER;
        printf(">> Algo set to Backtracker.\n");
      } else {
        printf(">> Incorrect Option.\n");
      }
      break;
    }

    case 3: { // Solver
      int solver_choice;
      printf("\n--- THE PROBLEM SOLVER ---\n");
      printf("[1] Breadth First Search (The Perfectionist. Finds The Absolute "
             "Longest Path)\n");
      printf("[2] Depth First Search (The Gambler. Just Finds A Deep Path, Not "
             "Always The Best)\n");
      printf("[3] A* (The Speedrunner. Finds The Shortest Path To The Exit "
             "Instantly)\n");
      printf(">> ");
      scanf("%d", &solver_choice);

      if (solver_choice == 1) {
        game_config.master = MASTER_BFS;
        printf(">> Solver set to BFS.\n");
      } else if (solver_choice == 2) {
        game_config.master = MASTER_DFS;
        printf(">> Solver set to DFS.\n");
      } else if (solver_choice == 3) {
        game_config.master = MASTER_A_STAR;
        printf(">> Solver set to A*.\n");
      } else {
        printf(">> Incorrect Option.\n");
      }
      break;
    }

    case 4: { // Dimensions
      int w, h;
      printf("\n--- HOW MUCH PAIN DO YOU WANT? ---\n");
      printf("Current Size: %dx%d\n", game_config.width, game_config.height);

      // Using constants here ensures the prompt matches the logic
      printf("Enter Width (Min %d, Max %d): ", MIN_MAZE_SIZE, MAX_MAZE_SIZE);
      if (scanf("%d", &w) == 1 && w >= MIN_MAZE_SIZE && w <= MAX_MAZE_SIZE) {
        game_config.width = w;
      } else {
        printf("Invalid Width. Stick to the limits.\n");
        clear_buffer();
      }

      printf("Enter Height (Min %d, Max %d): ", MIN_MAZE_SIZE, MAX_MAZE_SIZE);
      if (scanf("%d", &h) == 1 && h >= MIN_MAZE_SIZE && h <= MAX_MAZE_SIZE) {
        game_config.height = h;
      } else {
        printf("Invalid Height. Stick to the limits.\n");
        clear_buffer();
      }
      printf(">> Grid updated to %dx%d.\n", game_config.width,
             game_config.height);
      break;
    }

    case 5: // Start Game
      printf("\nInitializing memory... Praying to the compiler...\n");
      printf("Starting Game.\n");
      running = 0; // Break the while loop
      break;

    default:
      printf("That's not an option. Try again.\n");
      break;
    }
  }

  return game_config;
}
