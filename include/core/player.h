#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
  double x, y;
  double angle;
  double fov;
} PlayerState;

typedef enum {
  PLAYER_OK = 0,
  PLAYER_ERR_MEM = -1,
  PLAYER_ERR_LOGIC = -2,
  PLAYER_ERR_NULL = -3
} PLAYER_ERRORS;
PlayerState *player_init(double x, double y, double angle, double fov);
int player_update(PlayerState *state, double x, double y, double angle);
void player_free(PlayerState *state);

#endif // !PLAYER_H
