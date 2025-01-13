/* JDS renders pixels via a linear framebuffer, so that rendering to 
 * external images is easier. */
#pragma once

#include <stdint.h>
#include <raylib.h>

#define WIDTH  640
#define HEIGHT 480


// 640x480
extern uint32_t buffer[307200];

Color color_to_raylib(uint32_t c);
void putpixel(int x, int y, uint32_t color);

// start is the starting place of the framebuffer
void render_fb(Vector2 start);
