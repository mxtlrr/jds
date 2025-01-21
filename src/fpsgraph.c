#include "fpsgraph.h"


uint8_t Graph_fps[GR_WIDTH] = {0};
int counter = 0;

void update_FPSGraph(){
  int fps = GetFPS();
  if(counter == GR_WIDTH) counter = 0;
  Graph_fps[counter] = fps;
  counter++;
}

Color getColorFromFps(uint8_t fps){
  if(fps>70) return COLOR_GOOD;
  if(fps<70 && fps>30) return COLOR_OK;
  return COLOR_BAD;
}

void RenderFPSGraph(Vector2 startLoc){
  int xP = startLoc.x; int yP = startLoc.y;
  for(int i = 0; i < 300; i++){
    uint8_t fps_at  = Graph_fps[i];
    uint8_t fps_at2 = fps_at;
    if(i+1 > 300);
    else fps_at2 = Graph_fps[i+1];

    uint8_t avg = (fps_at+fps_at2)/2;
//    Color c  = getColorFromFps(fps_at);
    Color c2 = getColorFromFps(avg);

    // Draw a line frmo fps_at to fps_at2
    DrawLine(xP+i, 120-fps_at, xP+i+1, 120-fps_at2, c2);
  }

  DrawText("120", startLoc.x-35, startLoc.y-5, 20, BLACK);
  DrawText("0",   startLoc.x-15, startLoc.y+110, 20, BLACK);

  DrawRectangleLines(xP, yP, GR_WIDTH, 120, BLACK);
}
