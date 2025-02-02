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

#define VV_VERSION "v0.1-rc1"

void _(){}

int main(void){
  /* Before we start rendering, let's initialize:
   * palette, zoom, center zoom */
  generate_palette(0x000f, CHANGE_R, palette); // Set palette
  setZoomXY((Complex){0.072,-0.039});          // Zoom into the origin.
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

  Input color = { .counter = 0, .input_area = {.x = 50, .y = 275},
    .end_area = {.x = 300, .y = color.input_area.y+35}, .max = 1 };

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
    
    // Update complex number and R (escape radius)
    if(c.input_data[0] != 0 && (strcmp(c.input_data, "") != 0)){
      cc = str_to_complex(c.input_data);
      R = determine_R(cc, s.actual);
      //printf("Complex: %.3f, %.3fi | R=%.8f\n", cc.re, cc.im, R);
    }

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


    // Easier than using buttons
    float mouseWheel = GetMouseWheelMove();
    if(mouseWheel != 0.0f && IsMouseOverFb(mouse, fbLoc)){
      (mouseWheel == 1.0f) ? zoomIn(ZOOMIN_FACTOR, R, cc) 
            : zoomIn(ZOOMOUT_FACTOR, R, cc);
    }
    // Zoom in / out
    if(DidHoldButton(zoomInB, mouse))  zoomIn(ZOOMIN_FACTOR,  R, cc);
    if(DidHoldButton(zoomOutB, mouse)) zoomIn(ZOOMOUT_FACTOR, R, cc);
    

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
        generate_palette(0xf, nv, palette);
      } else generate_palette(0xf, 2, palette); // Let's do blue:)
      // Generate the julia set
      points = GenerateJuliaSet(cc, R);
    }

    if(DidClickButton(render_ppm, mouse)) {
      write_file_to_buf("render.ppm");
      printf("[DEBUG] outputted image file!\n");
    }

    if(DidClickButton(render_bmp, mouse)){
      generate_image_file("render.bpm");
      printf("[DEBUG] rendered image file!\n");
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
      render_button(draw_fb, mouse); render_button(render_ppm, mouse); render_button(zoomOutB, mouse);
      render_button(render_bmp, mouse); render_button(clear_, mouse); render_button(zoomInB, mouse);
      render_button(resetZoom, mouse);

      // Clamp actual to a int.
      s.actual = (int)s.actual;


      // Text that tells you what we're doing
      DrawText("Which pixel data to change?", color.input_area.x-10, color.input_area.y-40, 20, BLACK);
      DrawText("c, for f(z) = z^2 + c", c.input_area.x+15, c.input_area.y-40, 20, BLACK);
      DrawText(TextFormat("Accuracy multiplier: %.0f", s.actual), s.pos.x+(s.pos.x/2), s.pos.y-40, 20, BLACK);

      DrawText(TextFormat("Mouse at %03d, %03d", (int)mouseInFb.x, (int)mouseInFb.y), fbLoc.x+5, fbLoc.y-25, 20, BLACK);
      DrawText(TextFormat("Zooming in at %.3f%s%.3fi", xc.re, (xc.im > 0) ? "+" : "", xc.im), fbLoc.x+WIDTH-250,
          fbLoc.y-25, 20, BLACK);
      DrawText(TextFormat("Zoom: %.6f", zoom), fbLoc.x+10, zoomInB.xy.y, 20, BLACK);
      DrawText(TextFormat("Runnig JDS %s", VV_VERSION), 10, 750, 10, BLACK);
      // Framebuffer area
      DrawRectangleLines(fbLoc.x-1, fbLoc.y-1, WIDTH+2, HEIGHT+2, BLACK);


      if(JuliaSet[0].location.x != 0) asm("nop"); // Do nothing if 
      else {
        for(int i = 0; i < points; i++){
          Result r = JuliaSet[i]; Point p = r.location;
          if(p.x > WIDTH || p.y > HEIGHT){
            printf("[DEBUG] Pixel at (%.3f,%.3f) is out of bounds!\n", p.x,p.y);
          }
          else putpixel(p.x, p.y, palette[JuliaSet[i].iterations]);
        }
      render_fb(fbLoc);
      }

      update_FPSGraph();
      RenderFPSGraph((Vector2){200, 10});

      // Data
      int fps = GetFPS();
      DrawText(TextFormat("FPS: %3d", fps), 10, 10, 20, DARKGREEN);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
