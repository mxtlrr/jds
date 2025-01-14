#include <stdio.h>
#include <raylib.h>

#include "fb.h"
#include "gui.h"

int main(void){
  InitWindow(1200, 768, TextFormat("JDS git-%s", VERSION));
  SetTargetFPS(60);

  Vector2 fbLoc = (Vector2){500, 200};


  /* GUI components */
  Slider s = { // Escape value
    .min = 0.0f, .max = 250.0f, .pos = {.x = 50, .y = 500},
    .div_value = 15,
    .Body = {
      .w = s.max, .h = 20, .xPos = s.pos.x, .yPos = s.pos.y-10
    }
  };

  Input c = {
    .counter = 0, .input_area = {.x = 50, .y = 375},
    .end_area = {.x = 300,.y = c.input_area.y+35},
    .max = INP_MAX
  };

  Input color = {
    .counter = 0, .input_area = {.x = 50, .y = 275},
    .end_area = {.x = 300, .y = color.input_area.y+35},
    .max = 4 // 16 bit color
  };

  
  init_fb();
  while(!WindowShouldClose()){
    BeginDrawing();
      ClearBackground(WHITE);
      DrawSlider(s);
      Vector2 mouse = GetMousePosition();
      UpdateSlider(&s, mouse);

      // Clamp actual to a int.
      s.actual = (int)s.actual;

      UpdateInputBox(&c); DrawInput(c);
      UpdateInputBox(&color); DrawInput(color);

      // Text that tells you what we're doing
      DrawText("Color for points in the set", color.input_area.x-10, color.input_area.y-40, 20, BLACK);
      DrawText("c, for f(z) = z^2 + c", c.input_area.x+15, c.input_area.y-40, 20, BLACK);
      DrawText(TextFormat("R=%.0f", s.actual), s.pos.x+(s.pos.x/2), s.pos.y-40, 20, BLACK);

      // Framebuffer area
      DrawRectangleLines(fbLoc.x-1, fbLoc.y-1, WIDTH+2, HEIGHT+2, BLACK);
      render_fb(fbLoc);


      // Data
      int fps = GetFPS();
      DrawText(TextFormat("FPS: %3d", fps), 10, 10, 20, DARKGREEN);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}