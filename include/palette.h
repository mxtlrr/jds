#pragma once
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#define PALETTE_SIZE 256

enum PALETTE_MODIFIERS {
  CHANGE_R = 0,
  CHANGE_G,
  CHANGE_B
};

// Generates a palette from an initial value and the value to change. 
void generate_palette(int p, uint32_t* dest);


