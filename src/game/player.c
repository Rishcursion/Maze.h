#include "player.h"
#include <stdio.h>
#include <stdlib.h>

struct HistoryState {
  PlayerState *current_state;
  struct HistoryState *next_state;
  struct HistoryState *prev_state;
};
struct HistoryReplay {
  struct HistoryState *head;
  struct HistoryState *tail;
  struct HistoryState *current;
  int history_count;
};

enum PLAYER_ERROR { ERR_MEM, ERR_INVALID_ARGS, ERR_UNKNOWN };

PlayerState *player_init(double x, double y, double angle, double fov) {
  PlayerState *new_state;
  new_state = (PlayerState *)malloc(sizeof(PlayerState));
  if (!new_state) {
    return NULL;
  }
  new_state->angle = angle;
  new_state->fov = fov;
  new_state->x_coord = x;
  new_state->y_coord = y;
  return new_state;
}

HistoryReplay *history_init(void) {
  HistoryReplay *history = malloc(sizeof(HistoryReplay));
  if (!history) {
    return NULL;
  }
  struct HistoryState *dummy_node = calloc(1, sizeof(struct HistoryState));
  if (!dummy_node) {
    free(history);
    return NULL;
  }
  // Explicit initialization to avoid pointer black magic
  dummy_node->prev_state = NULL;
  dummy_node->next_state = NULL;
  dummy_node->current_state = NULL;
  history->head = dummy_node;
  history->tail = dummy_node;
  history->history_count = 0;
  return history;
}
void history_clear_future(HistoryReplay *history);

int history_push(HistoryReplay *history, PlayerState *past_state) {
  // If making a new move after an undo clear history;
  if (history->current != history->tail) {
    history_clear_future(history);
  }
  /*We'll be using a dummy node model, so we don't have to handle head being
   * NULL*/

  struct HistoryState *temp = malloc(sizeof(struct HistoryState));
  if (!temp) {
    return ERR_MEM;
  }
  temp->current_state = (PlayerState *)malloc(sizeof(PlayerState));
  if (!temp->current_state) {
    free(temp);
    return ERR_MEM;
  }
  temp->current_state->angle = past_state->angle;
  temp->current_state->fov = past_state->fov;
  temp->current_state->x_coord = past_state->x_coord;
  temp->current_state->y_coord = past_state->y_coord;
  temp->next_state = NULL;
  // Copying of past state is done, now need to add this to history
  // Link new node with end of history
  temp->prev_state = history->tail;
  // Link end of history with new node
  history->tail->next_state = temp;
  // make new node the end of history
  history->tail = temp;
  history->current = temp;
  history->history_count++;
  return 0;
}

int player_update(double x, double y, double angle,
                  PlayerState *current_player_state, HistoryReplay *history) {
  /*Ok so this function will be slighlyyyyy complex, what's gonna happen is:
    i) The current state is pushed to the tail of tracked history
    ii) The player state is then updated with the new values
  well, it looks pretty simple in words but let's see how it goes in
  implementation
  */
  PlayerState *temp = current_player_state; // Copy current state to temp
  int result = history_push(history, current_player_state);
  switch (result) {
  case ERR_MEM:
    printf("Memory Error In History Update!\n");
    // Propogate error
    return ERR_MEM;
  default:
    break;
  }
  // Note: we assume that the update function recieves values that have already
  // been interpolated from the direction the player is facing using fov and
  // angle etc....
  current_player_state->x_coord = x;
  current_player_state->y_coord = y;
  current_player_state->angle = angle;

  return EXIT_SUCCESS;
}

int player_undo(HistoryReplay *history, PlayerState *current_player_state) {}

void player_free(PlayerState *current_player_state) {
  free(current_player_state);
  current_player_state = NULL;
}
