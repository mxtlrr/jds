#include "img/ppm.h"

void write_file_to_buf(char* filename) {
  FILE* fp = fopen(filename, "wb");
  fprintf(fp, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
  
  for (int i = 0; i < WIDTH * HEIGHT; i++) {
    uint32_t color = buffer[i];
    // Buffer data is AGBR, i.e.
    // 0xff037bfc.
    uint8_t a = (color >> 24);
    uint8_t b = ((color>>16) & 0xff);
    uint8_t g = ((color>> 8) & 0xff);
    uint8_t r = color & 0xff;

    // gross
    (a==0) ? (fprintf(fp,"%c%c%c",255,255,255)) : (fprintf(fp,"%c%c%c",r,g,b));
  }

  fclose(fp);
}