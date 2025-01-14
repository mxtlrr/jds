#include <stdio.h>
#include <raylib.h>

#include "fb.h"
#include "gui.h"

#include "math/complex.h"
#include "math/parse-input.h"
#include "math/julia.h"

void _(){}
int main(void){
  int points = 0;

  SetTraceLogCallback(_);
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

  Slider step = {
    .min = 0.0f, .max = 250.0f, .pos = {.x = 50, .y = 200 },
    .div_value = 2500.0f,
    .Body = {
      .w = 250.0f, .h = 20, .xPos = step.pos.x, .yPos = step.pos.y-10
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
    if(IsKeyPressed(KEY_R)){
      Complex cc = str_to_complex(c.input_data);
      printf("[DEBUG] complex number is %.3f+%.3fi\n", cc.re, cc.im);
      points = GenerateJuliaSet(cc, (int)s.actual, step.actual);
      remap_points(points); // remap points
    }

    BeginDrawing();
      ClearBackground(WHITE);
      DrawSlider(s); DrawSlider(step);
      Vector2 mouse = GetMousePosition();
      UpdateSlider(&s, mouse);
      UpdateSlider(&step, mouse);

      // Clamp actual to a int.
      s.actual = (int)s.actual;

      UpdateInputBox(&c); DrawInput(c);
      UpdateInputBox(&color); DrawInput(color);

      // Text that tells you what we're doing
      DrawText(TextFormat("Step value: %.3f", step.actual), step.pos.x+(step.pos.x)/2, step.pos.y-40, 20, BLACK);
      DrawText("Color for points in the set", color.input_area.x-10, color.input_area.y-40, 20, BLACK);
      DrawText("c, for f(z) = z^2 + c", c.input_area.x+15, c.input_area.y-40, 20, BLACK);
      DrawText(TextFormat("R=%.0f", s.actual), s.pos.x+(s.pos.x/2), s.pos.y-40, 20, BLACK);

      // Framebuffer area
      DrawRectangleLines(fbLoc.x-1, fbLoc.y-1, WIDTH+2, HEIGHT+2, BLACK);


      for(int i = 0; i < points; i++){
        Point r = remappedPoints[i];
        putpixel(r.x, r.y, palette[JuliaSet[i].iterations]);
      }
      render_fb(fbLoc);

      // Data
      int fps = GetFPS();
      DrawText(TextFormat("FPS: %3d", fps), 10, 10, 20, DARKGREEN);
      DrawText("[DEBUG] Press R to render Julia set!", 10, 40, 20, BLACK);
      DrawText("[DEBUG] Press E to clear framebuffer", 10, 60, 20, BLACK);
      
    EndDrawing();
  }

  CloseWindow();
  return 0;
}