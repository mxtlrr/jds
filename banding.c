/* Generates a smooth "fade" effect between two colors. 
 * Used for palette generation for jds */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  uint8_t r, g, b, a;
} Color;

bool are_colors_the_same(Color a, Color b){
  return (a.r == b.r) && (a.g == b.g) && (a.b == b.b);
}

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

  Color c = (Color){color1 >> 16, (color1 & 0xFFFF) >> 8, color1 & 0xFF, 255};
  Color c2 = (Color){color2 >> 16, (color2 & 0xFFFF) >> 8, color2 & 0xFF, 255 };
  for(uint32_t frame = 0; ; frame++){
    for(uint16_t i = 0; i <= 640; i++){
      if(i % (640/4) == 0 && frame % 30 == 0){
        if(c.r      < c2.r) c.r++;
        else if(c.r > c2.r) c.r--;

        if(c.g      < c2.g) c.g++;
        else if(c.g > c2.g) c.g--;

        if(c.b      < c2.b) c.b++;
        else if(c.b > c2.b) c.b--;

        uint32_t conv = conv_to_32(c);
        if(are_colors_the_same(c,c2)) return 0;
        printf("%#06x,\n", conv);
      }
    }
  }
  return 0;
}