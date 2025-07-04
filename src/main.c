#include <stdio.h>
#include <raylib.h>

#include "fb.h"
#include "gui.h"
#include "img/bmp.h"
#include "img/ppm.h"

#include "palette.h"
#include "fpsgraph.h"
#include "math/julia.h"
#include "math/complex.h"
#include "math/parse-input.h"

void _(){}
int main(void){
  /* Before we start rendering, let's initialize:
   * palette, zoom, center zoom */
  setZoomXY((Complex){0.072,-0.039});  // Zoom into the origin.
  int points = 0;

  SetTraceLogCallback(_);
  InitWindow(1200, 768, TextFormat("JDS git-%s", VERSION));
  SetTargetFPS(120);

  Vector2 fbLoc = (Vector2){500, 200};


  /* GUI components */
  Slider s = { // Escape value
    .min = 0.0f, .max = 250.0f, .pos = {.x = 50, .y = 500}, .div_value = 15, .actual = 0,
    .Body = { .w = s.max, .h = 20, .xPos = s.pos.x, .yPos = s.pos.y-10 } };

  Input c = { // Complex number
    .counter = 0, .input_area = {.x = 50, .y = 375}, .end_area = {.x = 300,.y = c.input_area.y+35},
    .max = INP_MAX };

  Button draw_fb = { .xy = {.x = 120, .y = 550},.dim = {.x = 75, .y = 25},
    .neutral_color = GRAY, .clicked_color = DARKGRAY, .text = "DRAW" };
  
  Button render_ppm = { .xy = {.x = 85, .y = 580},.dim = {.x = 150, .y = 25},
    .neutral_color = GRAY, .clicked_color = DARKGRAY, .text = "RENDER PPM" };

  Button render_bmp = { .xy = {.x = render_ppm.xy.x, .y = 610},.dim = {.x = 150, .y = 25},
    .neutral_color = GRAY, .clicked_color = DARKGRAY, .text = "RENDER BMP" };

  Button clear_ = { .xy = { .x = 325, .y = 380 }, .dim = {.x=85, .y=25},
    .neutral_color = GRAY, .clicked_color = DARKGRAY, .text = "RESET" };

  // Zoom buttons
  Button zoomInB = { .xy = { .x = (fbLoc.x+WIDTH)-100, .y = (fbLoc.y+HEIGHT)+15 },
  .dim = {.x = 35, .y = 30}, .neutral_color = BLACK, .clicked_color = DARKGRAY, .text = "IN" };
  
   Button zoomOutB = { .xy = { .x = (fbLoc.x+WIDTH)-60, .y = (fbLoc.y+HEIGHT)+15 },
  .dim = {.x = 55, .y = 30}, .neutral_color = BLACK, .clicked_color = DARKGRAY, .text = "OUT" };
  
  Button resetZoom = { .xy = { .x = (fbLoc.x+(WIDTH/2)), .y = zoomInB.xy.y }, .dim = { .x = 85, 30 },
    .neutral_color = BLACK, .clicked_color = DARKGRAY, .text = "RESET" };


  init_fb(); 
  Vector2 mouseInFb = {0,0};
  Complex xc = zoomXY;
  
  Complex cc = {0,0};
  float R = 0.0f;

  while(!WindowShouldClose()){
    Vector2 mouse = GetMousePosition();
    
    if(IsMouseOverFb(mouse, fbLoc)){
      mouseInFb = getMousePosInFB(mouse, fbLoc);
      if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        // Convert the current pixel on the screen to a complex number and zoom
        xc = FBPixelToComplex((Point){mouseInFb.x, mouseInFb.y});
        setZoomXY(xc);

        // Set viewport centering on that point.
        zoomIn(1, R, cc);
      }
    }

    if(DidClickButton(resetZoom, mouse)){
      setZoomXY((Complex){0.072, -0.039});
      xc = zoomXY;
      zoom = 2.0f;
      GenerateJuliaSet(cc, R);
    }

    float mouseWheel = GetMouseWheelMove();
    if(mouseWheel != 0.0f && IsMouseOverFb(mouse, fbLoc)){
      if(mouseWheel == 1.0f) zoomIn(ZOOMIN_FACTOR, R, cc);
      else {
        if(zoom <= 2.5) zoomIn(ZOOMOUT_FACTOR, R, cc);
      }
    }

    // Zoom in / out
    if(DidHoldButton(zoomInB, mouse))  zoomIn(ZOOMIN_FACTOR,  R, cc);
    if(zoom <= 2.5 && DidHoldButton(zoomOutB, mouse)) zoomIn(ZOOMOUT_FACTOR, R, cc);

    if(DidClickButton(draw_fb, mouse)){
      cc = str_to_complex(c.input_data);
      R = determine_R(cc, s.actual);
      // TODO: check if should use hardcoded palette, or user defined palette provided in some sort of INI file.
      points = GenerateJuliaSet(cc, R);
    }

    if(DidClickButton(render_ppm, mouse)) {
      write_file_to_buf("render.ppm");
      printf("[DEBUG] outputted image file!\n");
    }

    if(DidClickButton(render_bmp, mouse)){
      generate_image_file("render.bmp");
      printf("[DEBUG] rendered image file!\n");
    }

    if(DidClickButton(clear_, mouse)){
      memset(c.input_data, 0, c.max); c.counter = 0;
      for(int i = 0; i < 2; i++) checkboxes[i].isSelected = false;
    }

    BeginDrawing();
      ClearBackground(WHITE);
      DrawSlider(s);

      // update and draw
      UpdateSlider(&s, mouse);
      UpdateInputBox(&c); DrawInput(c);
      
      for(int i = 0; i < CHECKBOX_COUNT; i++) {
        drawCheckbox(checkboxes[i]);
        updateCheckbox(&checkboxes[i], mouse);
      }

      render_button(draw_fb, mouse); render_button(render_ppm, mouse); render_button(zoomOutB, mouse);
      render_button(render_bmp, mouse); render_button(clear_, mouse); render_button(zoomInB, mouse);
      render_button(resetZoom, mouse);

      // Clamp actual to a int.
      s.actual = (int)s.actual;

      // Text that tells you what we're doing
      DrawText("Rendering Options", 45, 195, 20, BLACK);
      DrawText("c, for f(z) = z^2 + c", c.input_area.x+15, c.input_area.y-40, 20, BLACK);
      DrawText(TextFormat("Accuracy multiplier: %.0f", s.actual), s.pos.x+(s.pos.x/2), s.pos.y-40, 20, BLACK);

      DrawText(TextFormat("Mouse at %03d, %03d", (int)mouseInFb.x, (int)mouseInFb.y), fbLoc.x+5, fbLoc.y-25, 20, BLACK);
      DrawText(TextFormat("Zooming in at %.3f%s%.3fi", xc.re, (xc.im > 0) ? "+" : "", xc.im), fbLoc.x+WIDTH-250,
          fbLoc.y-25, 20, BLACK);
      DrawText(TextFormat("Zoom: %.6f", zoom), fbLoc.x+10, zoomInB.xy.y, 20, BLACK);
      DrawText(TextFormat("Running JDS %s", VERSION), 10, 750, 10, BLACK);
      
      // Framebuffer area
      DrawRectangleLines(fbLoc.x-1, fbLoc.y-1, WIDTH+2, HEIGHT+2, BLACK);


      // Render julia set
      if(JuliaSet[0].location.x == 0) {
        for(int i = 0; i < points; i++){
          Result r = JuliaSet[i]; Point p = r.location;
          float iteration = r.iterations;
          if(r.iterations > MAX_ITERATIONS){
            float log_zn = log(p.x * p.x) / 2;
            float nu     = log(log_zn / log(2)) / log(2);
            iteration    = iteration + 1 - nu;
          }

          int color1 = palette[(int)floor(iteration)];
          int color2 = palette[(int)floor(iteration) + 1];

          int new_color = (int)linear_interpolate(color1, color2, 
                    fmod(iteration, 1.f));
          putpixel(p.x, p.y, new_color);
        }
        render_fb(fbLoc);
      }

      update_FPSGraph();
      RenderFPSGraph((Vector2){200, 10});
      DrawFPS(10,10);
    EndDrawing();
  }
  return 0;
}
