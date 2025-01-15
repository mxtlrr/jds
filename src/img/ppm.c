#include "img/ppm.h"

void write_file_to_buf(char* filename) {
  FILE* fp = fopen(filename, "wb");
  fprintf(fp, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
  
  for (int i = 0; i < WIDTH * HEIGHT; i++) {
    int r = ((buffer[i] >> 8) >> 4) * 17;
    int g = ((buffer[i] >> 8) & 0x0f) * 17;
    int b = ((buffer[i] & 0xff) >> 4) * 17;
    int a = ((buffer[i] & 0xff) & 0x0f) * 17;

    if(a == 0){ // Alpha != 0
      fputc(255, fp);
      fputc(255, fp);
      fputc(255, fp);
    } else {
      fprintf(fp, "%c%c%c",r,g,b);
      // fputc(r, fp);
      // fputc(g, fp);
      // fputc(b, fp);
    }
  }

  fclose(fp);
}