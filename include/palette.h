#pragma once
#include <stdio.h>
#include <math.h>
#include <stdint.h>

// starts from 0xabF (or 0xaFb, or 0xFba), and goes down
// until said F = 0. a & b are held constant
#define PALETTE_SIZE 16

// Technically it's 12-bit color since we use the
// R4G4B4A4 model, but ignore the last four bits
// (the alpha)
typedef struct color {
  uint8_t r : 4;
  uint8_t g : 4;
  uint8_t b : 4;
} color_t;

// Generates a valid 16-bit RGBA from 12-bit RGB.
uint16_t gen_color(color_t c);
color_t rbga2color(uint16_t c);

enum PALETTE_MODIFIERS {
  CHANGE_R = 0,
  CHANGE_G,
  CHANGE_B
};

// Generates a palette from an initial value and the value to change. 
void generate_palette(uint16_t initial_value, int p, uint16_t* dest);


