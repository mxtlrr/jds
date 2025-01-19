#include "palette.h"

uint16_t gen_color(color_t c){
  // Note that the last field will always be 0xF since we ignore it.
  // If we set it to 0, then it's the same as transparency.
  return (c.r << 12) | (c.g << 8) | (c.b << 4) | 0x0f;
}

color_t rgba2color(uint16_t c){
  uint16_t rgb = (c>>4); // Each digit is 4 bits. (4*4 = 16 bits).
                         // Ignore last digit (alpha) by shifting right

  return (color_t){
    .r = (rgb >> 8),
    .g = ((rgb >> 4) & 0x0f),
    .b = rgb & 0x0f
  };
}


void generate_palette(uint16_t initial_value, int p, uint16_t* dest){
  double value = 4096 * pow(2,-4*p); // cursed.
 // dest[0] = initial_value;
  for(int i=0; i<16; i++) dest[i] = initial_value + (value*i);
}
