#include <stdio.h>
#include <raylib.h>

#include "fb.h"
#include "gui.h"
#include "img/ppm.h"

#include "palette.h"
#include "math/julia.h"
#include "math/complex.h"
#include "math/parse-input.h"

void _(){}
int main(void){
  /* Before we start rendering, let's initialize:
   * palette, zoom, center zoom */
  generate_palette(0x000f, CHANGE_R, palette); // Set palette
  setZoomXY((Complex){0,0});                   // Zoom into the origin.
  int points = 0;

  SetTraceLogCallback(_);
  InitWindow(1200, 768, TextFormat("JDS git-%s", VERSION));
//SetTargetFPS(60);

  Vector2 fbLoc = (Vector2){500, 200};


  /* GUI components */
  Slider s = { // Escape value
    .min = 0.0f, .max = 250.0f, .pos = {.x = 50, .y = 500},
    .div_value = 15,
    .Body = {
      .w = s.max, .h = 20, .xPos = s.pos.x, .yPos = s.pos.y-10
    }
  };

  Input c = { // Complex number
    .counter = 0, .input_area = {.x = 50, .y = 375},
    .end_area = {.x = 300,.y = c.input_area.y+35},
    .max = INP_MAX
  };

  Input color = {
    .counter = 0, .input_area = {.x = 50, .y = 275},
    .end_area = {.x = 300, .y = color.input_area.y+35},
    .max = 1
  };

  Button draw_fb = {
    .xy = {.x = 120, .y = 550},.dim = {.x = 75, .y = 25},
    .neutral_color = GRAY, .clicked_color = DARKGRAY, .text = "DRAW"
  };
  Button render_ppm = {
    .xy = {.x = 85, .y = 580},.dim = {.x = 145, .y = 25},
    .neutral_color = GRAY, .clicked_color = DARKGRAY, .text = "RENDER PPM"
  };
  Button render_bmp = {
    .xy = {.x = render_ppm.xy.x, .y = 610},.dim = {.x = 145, .y = 25},
    .neutral_color = GRAY, .clicked_color = DARKGRAY, .text = "RENDER BMP"
  };
  Button clear_ = {
    .xy = { .x = 325, .y = 380 }, .dim = {.x=85, .y=25},
    .neutral_color = GRAY, .clicked_color = DARKGRAY, .text = "RESET"
  };
  
  init_fb();
  while(!WindowShouldClose()){
    Vector2 mouse = GetMousePosition();

    if(IsMouseOverFb(mouse, fbLoc)){
      Vector2 loc = getMousePosInFB(mouse, fbLoc);
      printf("(%.3f, %.3f)\n", loc.x, loc.y);
    }
    if(IsKeyDown(KEY_Z)){
      printf("[DEBUG][OK] Zooming into %.3f+%.3fi\n", zoomXY.re, zoomXY.im);
      Complex cc = str_to_complex(c.input_data);
      float R = determine_R(cc, s.actual);
      zoomIn(ZOOM_FACTOR, R, cc);
      printf("[DEBUG] zoom factor: %.3f. new zoom: %.3f\n", ZOOM_FACTOR, zoom);
    }

    if(DidClickButton(draw_fb, mouse)){
      // Create the palette from the set thing
      char value = color.input_data[0];
      // TODO: check if this is uppercase or lowercase
      if(value != 0){
        // Determine what to change
        uint8_t nv = 0;
        if(value == 'r') nv = CHANGE_R;
        if(value == 'g') nv = CHANGE_G;
        if(value == 'b') nv = CHANGE_B;
       
        printf("nv=%d | val=%d\n", nv, value);
        // Now change the palette
        generate_palette(0xf, nv, palette);
      } else {
        printf("No value given!\n");
        generate_palette(0xf, 2, palette); // Let's do blue:)
      }
      // Generate the julia set
      Complex cc = str_to_complex(c.input_data);
      float R = determine_R(cc, s.actual);
      points = GenerateJuliaSet(cc, R);
    }

    if(DidClickButton(render_ppm, mouse)) {
      write_file_to_buf("render.ppm");
      printf("[DEBUG] outputted image file!\n");
    }

    if(DidClickButton(clear_, mouse)){
      memset(c.input_data, 0, c.max); c.counter = 0;
      memset(color.input_data, 0, 3); color.counter = 0;
    }

    BeginDrawing();
      ClearBackground(WHITE);
      DrawSlider(s);

      // update and draw
      UpdateSlider(&s, mouse);
      UpdateInputBox(&c); DrawInput(c);
      UpdateInputBox(&color); DrawInput(color);
      render_button(draw_fb, mouse); render_button(render_ppm, mouse);
      render_button(render_bmp, mouse); render_button(clear_, mouse);

      // Clamp actual to a int.
      s.actual = (int)s.actual;


      // Text that tells you what we're doing
      DrawText("Which pixel data to change?", color.input_area.x-10, color.input_area.y-40, 20, BLACK);
      DrawText("c, for f(z) = z^2 + c", c.input_area.x+15, c.input_area.y-40, 20, BLACK);
      DrawText(TextFormat("Accuracy multiplier: %.0f", s.actual), s.pos.x+(s.pos.x/2), s.pos.y-40, 20, BLACK);

      // Framebuffer area
      DrawRectangleLines(fbLoc.x-1, fbLoc.y-1, WIDTH+2, HEIGHT+2, BLACK);


      for(int i = 0; i < points; i++){
        Result r = JuliaSet[i]; Point p = r.location;
        if(p.x > WIDTH || p.y > HEIGHT){
          printf("[DEBUG] Pixel at (%.3f,%.3f) is out of bounds!\n", p.x,p.y);
        }
        else putpixel(p.x, p.y, palette[JuliaSet[i].iterations]);
      }
      render_fb(fbLoc);

      // Data
      int fps = GetFPS();
      DrawText(TextFormat("FPS: %3d", fps), 10, 10, 20, DARKGREEN);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
