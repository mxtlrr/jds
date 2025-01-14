#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "complex.h"

extern uint16_t palette[16];
typedef struct Result {
  bool stays_in; // Does it stay bounded?
  int iterations; // If stays_in = false, then this is the amount
                  // of iterations before it runs off.
  Complex c;      // The point itself
} Result;

typedef struct Point {
  int x;
  int y;
} Point;


Result does_point_escape(Complex z, Complex seed, int R);

extern Result JuliaSet[300000];
extern Point remappedPoints[300000];


#define STEP 0.1

// From (-10, -10) to (10, 10)
int GenerateJuliaSet(Complex seed, int R, float step);

// Map points in julia set to available points on the framebuffer
// Example:
// Origin is (320, 240) for 640x480 fb
// -0.4 + 0.9i ==[ x10 ]==> (-4,9) ==[ map through origin ]==> (316, 249)
void remap_points();