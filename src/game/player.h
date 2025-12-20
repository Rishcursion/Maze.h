#ifndef PLAYER_H
#define PLAYER_H
typedef struct {
  double x_coord; // Position of the player along the X-axis;
  double y_coord; // Position of the player along the Y-axis
  double angle;   // Angle of the player's camera;
  double fov;     // Field of view for 3D
} PlayerState;
#endif // !PLAYER_H
