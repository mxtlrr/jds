// TODO: implement smooth coloring.
#pragma once


#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "math/julia.h"

#define MODIFY_AMOUNT_RB 0x1f
#define PALETTE_SIZE       15

enum PALETTE_MODIFIERS {
  CHANGE_R = 0,
  CHANGE_G,
  CHANGE_B
};

extern uint32_t palette[PALETTE_SIZE];