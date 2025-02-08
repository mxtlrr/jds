#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "fb.h"
#include "complex.h"

#define JULIA_SET_SIZE 10000000
#define MAX_ITERATIONS 16

extern uint32_t palette[256];

typedef struct Point {
  float x;
  float y;
} Point;

typedef struct Result {
  Point location;
  int iterations;
} Result;

extern Result JuliaSet[JULIA_SET_SIZE];

#define ZOOM_FACTOR         0.05
#define MAKE_ZOOM_FACTOR(x) (1-x)
#define ZOOMIN_FACTOR       MAKE_ZOOM_FACTOR(ZOOM_FACTOR)
#define ZOOMOUT_FACTOR      1+ZOOM_FACTOR

extern double zoom;     // Zoom amount
extern Complex zoomXY;  // Center to zoom into


// Scales coordinate to be between min and max.
double scale_coord(int p, int sd, double min, double max);

// Generates a pixel on the screen and see's if it's part of the
// Julia set. Returns the iterations it takes to escape off. Returns
// 0 if it doesn't.
// Parameters:
// p: Point on the window
// c: Complex number
// R: escape radius (usually made from determine_R)
int pixel(Point p, Complex c, int R);



#define STEP 0.1
int GenerateJuliaSet(Complex seed, int R);

// This function determines a possible R. The higher the R, the more accurate
// the julia set is. It's pretty much a quadratic
float determine_R(Complex c, int accuracy);

// Zooms in, sets everything up and the re-renders the framebuffer to the
// newly zoomed in fractal.
// Parameters:
// zoomFactor: How much to zoom in
// R:          Escape radius. Should've already been provided.
// c:          Seeded complex number
void zoomIn(double zoomFactor, float R, Complex c);

// Set the center to where we zoom into
void setZoomXY(Complex new);

// Remap positions from an actual point on the framebuffer
// to a point in the complex plain. Also used in
// generating Julia set
Complex FBPixelToComplex(Point p);
