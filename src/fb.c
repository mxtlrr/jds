#include "fb.h"

uint32_t buffer[307200] = {0};
Texture2D rendered_texture;

void putpixel(int x, int y, uint32_t color) {
  // Individual color bits
  uint8_t r = (color >> 16) & 0xFF;
  uint8_t g = (color >> 8) & 0xFF;
  uint8_t b = (color) & 0xFF;

  uint32_t formedcolor = (b << 16) | (g << 8) | r;  // Generate R8G8B8
  buffer[y * 640 + x] = (0xff << 24) | formedcolor; // Append A to the front.
  // It's ABGR because x86 is little endian.
}

void init_fb(){
  rendered_texture = LoadTextureFromImage((Image){
    .data = buffer, .width = WIDTH, .height = HEIGHT,
    .mipmaps = 1, .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
  });
}

void render_fb(Vector2 start) {
  UpdateTexture(rendered_texture, buffer);
  DrawTexture(rendered_texture, start.x, start.y, WHITE);
}

bool IsMouseOverFb(Vector2 m, Vector2 sPos){
  // ill use this to generate actual complex numbers to
  // zoom in.
  if(sPos.x <= m.x && sPos.x+WIDTH >= m.x &&
      sPos.y <= m.y && sPos.y+HEIGHT >= m.y) return true;
  return false;
}

Vector2 getMousePosInFB(Vector2 m, Vector2 sPos){
  return (Vector2){
    .x = m.x - sPos.x,
    .y = m.y - sPos.y
  };
}
