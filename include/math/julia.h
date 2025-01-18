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

#define STEP 0.1
int GenerateJuliaSet(Complex seed, int R);

// This function determines a possible R. The higher the R, the more accurate
// the julia set is. It's pretty much a quadratic
float determine_R(Complex c, int accuracy);

// remaps the points to actually not shrink when accuracy increases.
void remap_points(int point_count, float R);
