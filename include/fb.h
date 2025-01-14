/* JDS renders pixels via a linear framebuffer, so that rendering to 
 * external images is easier. */
#pragma once

#include <stdint.h>
#include <raylib.h>
#include <stdlib.h>

#define WIDTH  640
#define HEIGHT 480


// 640x480
extern uint16_t buffer[307200];
extern Texture2D rendered_texture;

void putpixel(int x, int y, uint16_t color);

// start is the starting place of the framebuffer
void render_fb(Vector2 start);

void init_fb();