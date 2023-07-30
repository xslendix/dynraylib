#include "dynconf.h"

#include <raylib.h>

Vector2 position = {0, WINDOW_HEIGHT / 2};
#define SPEED 10
#define BALL_RAD 30
int speed_x = SPEED;
int speed_y = SPEED;

void rl_init(void) { SetTargetFPS(30); }

void rl_update(void) {
  if (position.x + BALL_RAD > WINDOW_WIDTH)
    speed_x = -SPEED;
  else if (position.x - BALL_RAD < 0)
    speed_x = SPEED;
  position.x += speed_x;
  if (position.y + BALL_RAD > WINDOW_HEIGHT)
    speed_y = -SPEED;
  else if (position.y - BALL_RAD < 0)
    speed_y = SPEED;
  position.y += speed_y;

  BeginDrawing();
  ClearBackground((Color){.r = 0, .g = 0, .b = 0x22, .a = 0xff});
  DrawCircleV(position, BALL_RAD, WHITE);
  DrawFPS(10, 10);
  EndDrawing();
}
