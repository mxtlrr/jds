#include "fb.h"

uint32_t buffer[307200];

Color color_to_raylib(uint32_t c){
  return (Color){.r = (c>>16) & 0xff,
    .g = (c>>8) & 0xff, .b = c & 0xff, .a = 255};
}
void putpixel(int x, int y, uint32_t color){
  buffer[x*y] = color;
}

void render_fb(Vector2 start){

}