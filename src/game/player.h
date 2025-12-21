#ifndef PLAYER_H
#define PLAYER_H
typedef struct {
  double x_coord; // Position of the player along the X-axis;
  double y_coord; // Position of the player along the Y-axis
  double angle;   // Angle of the player's camera;
  double fov;     // Field of view for 3D
} PlayerState;

typedef struct History HistoryState;

typedef struct HistoryReplay HistoryReplay;

// Player state modification
int player_update(double x, double y, double angle,
                  PlayerState *current_player_state, HistoryReplay *history);
int player_undo(HistoryReplay *history, PlayerState *current_player_state);
int player_redo(HistoryReplay *history, PlayerState *current_player_state);
PlayerState *player_init(double x, double y, double angle, double fov);

// Cleanup functions
void player_free(PlayerState *current_player_state);
void history_free(HistoryReplay *history);

// History Functions
HistoryReplay *history_init(void);

#endif // !PLAYER_H
