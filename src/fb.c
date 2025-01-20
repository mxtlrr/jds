#include "fb.h"

uint16_t buffer[307200] = {0};
Texture2D rendered_texture;

void putpixel(int x, int y, uint16_t color) {
  buffer[y * 640 + x] = color;
}

void init_fb(){
  rendered_texture = LoadTextureFromImage((Image){
    .data = buffer, .width = WIDTH, .height = 480,
    .mipmaps = 1, .format = PIXELFORMAT_UNCOMPRESSED_R4G4B4A4
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
