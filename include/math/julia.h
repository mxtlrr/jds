#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "fb.h"
#include "complex.h"

#define JULIA_SET_SIZE 10000000
#define MAX_ITERATIONS 16

extern uint16_t palette[16];

typedef struct Point {
  float x;
  float y;
} Point;

double scale_coord(int p, int sd, double min, double max);
// Result does_point_escape(Complex z, Complex seed, int R);

int pixel(Point a, Complex c, int R);


typedef struct Result {
  Point location;
  int iterations;
} Result;

extern Result JuliaSet[JULIA_SET_SIZE];
// extern Point remappedPoints[JULIA_SET_SIZE];


#define STEP 0.1
int GenerateJuliaSet(Complex seed, int R);

// Map points in julia set to available points on the framebuffer
// Example:
// Origin is (320, 240) for 640x480 fb
// -0.4 + 0.9i ==[ x10 ]==> (-4,9) ==[ map through origin ]==> (316, 249)
void remap_points();