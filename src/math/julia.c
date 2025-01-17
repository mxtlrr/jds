#include "math/julia.h"

uint16_t palette[16] = { 0xf00f };

double scale_coord(int p, int sd, double min, double max) {
  return min + ((double)p / (sd - 1)) * (max - min);
}

// use 1.57 for R
int pixel(Point a, Complex c, int R){
  double zx = scale_coord(a.x, WIDTH, -R, R);
  double zy = scale_coord(a.y, HEIGHT, -R, R);

  int i = 0;
  while(zx*zx + zy*zy < pow(R,2) && i<MAX_ITERATIONS){
    double xtemp = zx*zx - zy*zy;
    zy = 2*zx*zy+c.im;
    zx = xtemp + c.re;

    i++;
  }

  if(i == MAX_ITERATIONS) return 0;
  else return i;
}


Result JuliaSet[JULIA_SET_SIZE];
int GenerateJuliaSet(Complex seed, int R){
  int counter = 0;
  for(int y = -HEIGHT; y < HEIGHT; y++){
    for(int x = -WIDTH; x < WIDTH; x++){
      int pc = pixel((Point){x,y}, seed, R);
      JuliaSet[counter] = (Result){
        .location = (Point){x,y},
        .iterations = pc
      };
      counter++;
    }
  }

  return counter;
}