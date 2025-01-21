/* A graph on the top of the window that shows current FPS. */
#pragma once

#include <stdio.h>
#include <stdint.h>
#include <raylib.h>

// Pixels in width of the graph
#define GR_WIDTH 300

#define COLOR_GOOD (Color){004, 255, 000, 255} // Anything above 70 FPS
#define COLOR_OK   (Color){247, 169, 000, 255} // Anything above 30 FPS and under 70 FPS
#define COLOR_BAD  (Color){247, 000, 000, 255} // Anything under 30 FPS

extern uint8_t Graph_fps[GR_WIDTH]; // FPS graph
extern int counter;                 // ...

Color getColorFromFps(uint8_t fps);

void update_FPSGraph();
void RenderFPSGraph(Vector2);
