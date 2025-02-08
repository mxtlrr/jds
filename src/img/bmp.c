#include "img/bmp.h"

uint32_t rgb_to_bgr(uint32_t rgb){
  uint8_t r = rgb & 0xff;
  uint8_t g = (rgb>>8) & 0xff;
  uint8_t b = (rgb>>16);

  return b<<16 | g<<8 | r;
}

void write_header(const char *file, uint32_t* data) {
  FILE *fp = fopen(file, "wb");
  if (!fp) return;

  // BMP file header
  uint16_t bfType = 0x4D42;
  uint32_t bfSize = 14 + 40 + 640 * 480 * 3;
  uint32_t bfReserved = 0x00000000;
  uint32_t bfOffBits = 54;

  fwrite(&bfType, 2, 1, fp);
  fwrite(&bfSize, 4, 1, fp);
  fwrite(&bfReserved, 4, 1, fp);
  fwrite(&bfOffBits, 4, 1, fp);

    // DIB header
  uint32_t biSize = 40;
  int32_t biWidth = 640;
  int32_t biHeight = -480;
  uint16_t biPlanes = 1;
  uint16_t biBPP = 24;
  uint32_t biCompression = 0;
  uint32_t biSizeImage = 640 * 480 * 3;
  int32_t biPPM = 0;
  uint32_t biClrUsed = 0;
  uint32_t biClrImportant = 0;

  fwrite(&biSize, 4, 1, fp);
  fwrite(&biWidth, 4, 1, fp);
  fwrite(&biHeight, 4, 1, fp);
  fwrite(&biPlanes, 2, 1, fp);
  fwrite(&biBPP, 2, 1, fp);
  fwrite(&biCompression, 4, 1, fp);
  fwrite(&biSizeImage, 4, 1, fp);
  fwrite(&biPPM, 4, 1, fp);
  fwrite(&biPPM, 4, 1, fp);
  fwrite(&biClrUsed, 4, 1, fp);
  fwrite(&biClrImportant, 4, 1, fp);

  for(int y=0; y<480; y++) {
    for(int x=0; x<640; x++) {
      uint32_t color = data[y*640+x];
      uint8_t b = (color>>16);
      uint8_t g = (color>>8) & 0xFF;
      uint8_t r = color & 0xFF;

      fputc(b, fp);
      fputc(g, fp);
      fputc(r, fp);
    }
  }
  fclose(fp);
}

void generate_image_file(char* filename){
  uint32_t color[640*480];
  for(int i = 0; i < (640*480); i++){
    uint32_t color2 = buffer[i];
    
    uint8_t a = (color2 >> 24);
    uint8_t b = ((color2>>16) & 0xff);
    uint8_t g = ((color2>> 8) & 0xff);
    uint8_t r = color2 & 0xff;

    if(a==0) color[i] = 0xFFFFFF;
    else     color[i] = (b<<16)|(g<<8)|r;
  }

  write_header(filename, color);
}
