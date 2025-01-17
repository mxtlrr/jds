#include <stdio.h>
#include <raylib.h>

#include "fb.h"
#include "gui.h"
#include "img/ppm.h"

#include "math/julia.h"
#include "math/complex.h"
#include "math/parse-input.h"

uint16_t interpolate_palette(uint16_t* palette, int palette_size, double iterations) {
  int index = (int)iterations % palette_size;
  int next_index = (index + 1) % palette_size;
  double t = iterations - (int)iterations;  // Fractional part

  // Interpolate between the two colors
  uint16_t color1 = palette[index];
  uint16_t color2 = palette[next_index];

  uint8_t r1 = (color1 >> 8) & 0xF, g1 = (color1 >> 4) & 0xF, b1 = color1 & 0xF;
  uint8_t r2 = (color2 >> 8) & 0xF, g2 = (color2 >> 4) & 0xF, b2 = color2 & 0xF;

  uint8_t r = (1 - t) * r1 + t * r2;
  uint8_t g = (1 - t) * g1 + t * g2;
  uint8_t b = (1 - t) * b1 + t * b2;

  return (r << 8) | (g << 4) | b;
}

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
      points = GenerateJuliaSet(cc, 1.57); // TODO: unhardcore R
      printf("%d points!\n", points);
      // remap_points(points); // remap points
    }

    if(IsKeyDown(KEY_B)) {
      write_file_to_buf("render.ppm");
      printf("[DEBUG] outputted image file!\n");
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
        Result r = JuliaSet[i]; Point p = r.location;
        putpixel(p.x, p.y, palette[JuliaSet[i].iterations]);
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