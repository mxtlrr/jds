#include <stdio.h>
#include <raylib.h>

#include "fb.h"
#include "gui.h"

int main(void){
  InitWindow(1200, 768, TextFormat("JDS git-%s", VERSION));
  SetTargetFPS(60);

  Vector2 fbLoc = (Vector2){500, 200};
  Slider s = {
    .min = 0.0f, .max = 250.0f, .pos = {.x = 50, .y = 500},
    .div_value = 15,
    .Body = {
      .w = s.max, .h = 20, .xPos = s.pos.x, .yPos = s.pos.y-10
    }
  };

  while(!WindowShouldClose()){
    BeginDrawing();
      ClearBackground(WHITE);
      DrawSlider(s);
      Vector2 mouse = GetMousePosition();
      UpdateSlider(&s, mouse);

      DrawText(TextFormat("R=%.3f", s.actual), s.pos.x+(s.pos.x/2), s.pos.y-40, 20, BLACK);
      // Framebuffer area
      DrawRectangleLines(fbLoc.x, fbLoc.y, WIDTH, HEIGHT, BLACK);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}