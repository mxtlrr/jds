// TODO: implement smooth coloring.
#pragma once


#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "math/julia.h"

enum PALETTE_MODIFIERS {
  CHANGE_R = 0,
  CHANGE_G,
  CHANGE_B
};

extern uint32_t palette[];


// Technically known as lerp. Adapted from Wikipedia.
// v1, v2: Values to interpolate
// t: between [0,1]
float linear_interpolate(float v1, float v2, float t);