/* Generates a smooth "fade" effect between two colors. 
 * Used for palette generation for jds */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#define MAX_AMOUNT 7

typedef struct {
  uint8_t r, g, b;
} Color;

uint32_t conv_to_32(Color c){
  return (c.r << 16) | (c.g << 8) | c.b;
}

// NOTE: THIS IS SUPER UNFINISHED!
// Fixes needed:
//    1. Generate `n` colors between c1 and c2
//    2. Make the jump between R/G/B channels in the intermediate
//        color not just be by one.
//    3. ??? Idk, make this garbage better.

int main(int argc, char** argv){
  if(argc == 1){
    fprintf(stderr, "usage: %s [color 1] [color 2]\n", argv[0]);
    fprintf(stderr, "\tensure both colors are in hex format, i.e.\n");
    fprintf(stderr, "\t%s 19071a 09012f\n", argv[0]);
    return 2;
  }

  uint32_t color1 = strtol(argv[1], NULL, 16);
  uint32_t color2 = strtol(argv[2], NULL, 16);

  printf("[ok]: using %06x -> %06x\n", color1, color2);
	printf("[ok]: making %02d bands\n", MAX_AMOUNT);

  Color c  = (Color){color1 >> 16, (color1 & 0xFFFF) >> 8, color1 & 0xFF};
  Color c2 = (Color){color2 >> 16, (color2 & 0xFFFF) >> 8, color2 & 0xFF};

	uint8_t dR = (abs(c2.r - c.r)) / MAX_AMOUNT; uint8_t dG = (abs(c2.g - c.g)) / MAX_AMOUNT;
	uint8_t dB = (abs(c2.b - c.b)) / MAX_AMOUNT;

	printf("dR => %d // dG => %d // dB => %d\n", dR, dG, dB);
	for(uint8_t i = 0; i < MAX_AMOUNT; i++){
		c.r += (( (c2.r - c.r) < 0 ) ? -1 : 1) * dR;
		c.g += (( (c2.g - c.g) < 0 ) ? -1 : 1) * dG;
		c.b += (( (c2.b - c.b) < 0 ) ? -1 : 1) * dB;
		printf("0x%06x,\n", conv_to_32(c));
	}
	return 0;
}
