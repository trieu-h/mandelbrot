#include <stdio.h>
#include "include/raylib.h"
#include "include/raymath.h"

#define WIDTH 800
#define HEIGHT 600
#define ONE_UNIT 200
#define Y_AXIS ONE_UNIT*3
#define X_AXIS HEIGHT/2
#define TICK_OFFSET 5

int mandelbrot(float x_p, float y_p) {
  int i = 0;
  float prev_x = 0;
  float prev_y = 0;

  while (i < 1000) {
    float cur_x = prev_x * prev_x - prev_y * prev_y + x_p;
    float cur_y = 2*prev_x*prev_y + y_p;
    float abs_val_squared = (cur_x * cur_x) + (cur_y * cur_y);

    if (abs_val_squared > 2*2) { // Mandelbrot set is bounded inside an absolute value of 2
      return i;
    }

    i++;
    prev_x = cur_x;
    prev_y = cur_y;
  }

  return -1;
}

void main() {
  InitWindow(WIDTH, HEIGHT, "Mandelbrot");

  bool quit = false;
  while (!quit)
  {
    if (IsKeyDown(KEY_Q)) {
      quit = true;
    }
    BeginDrawing();
    ClearBackground(BLACK);

    // Draw x and y axis
    DrawLine(0, X_AXIS, WIDTH, X_AXIS, WHITE);
    DrawLine(Y_AXIS, 0, Y_AXIS, HEIGHT, WHITE);

    // Iterate through each pixels to determine if it's in the Mandelbrot set or not
    for (int x = 0; x <= WIDTH; x++) {
      for (int y = 0; y <= HEIGHT; y++) {
        float x_coord = Vector2Distance((Vector2) {x, y}, (Vector2) {Y_AXIS, y}) / ONE_UNIT;
        if (x < Y_AXIS) x_coord = -x_coord;
        float y_coord = Vector2Distance((Vector2) {x, y}, (Vector2) {x, X_AXIS}) / ONE_UNIT;
        if (y > X_AXIS) y_coord = -y_coord;

        Color palette[5] = {RED, MAROON, GOLD, ORANGE, YELLOW};
        int m = mandelbrot(x_coord, y_coord);
        if (m == -1) {
          DrawPixel(x, y, BLACK);
        } else {
          DrawPixel(x, y, palette[m%5]);
        }
      };
    }

    EndDrawing();
  }

  CloseWindow();
}