#include "math/julia.h"

uint16_t palette[] = {
  0x000f, 0x001f, 0x002f, 0x003f,
  0x004f, 0x005f, 0x006f, 0x007f,
  0x008f, 0x009f, 0x00ff, 0x00bf,
  0x00cf, 0x00df, 0x00ef, 0x00ff
};

Result does_point_escape(Complex z, Complex seed, int R){
  Complex z_n = z; // no im?
  for(int i = 0; i < 10; i++){
    z_n = ComplexMul(z_n, z_n); // z_n^2.
    z_n = ComplexAdd(z_n, seed);
    if(AbsComplex(z_n) > R){
      return (Result){ .iterations = R, .stays_in = false };
    }
  }
  return (Result){.iterations = AbsComplex(z_n), .stays_in = true, .c = z };
}



Result JuliaSet[300000];
int GenerateJuliaSet(Complex seed, int R, float step){
  int counter = 0;
  float x=0;float y=0;
  for(y = -10; y < 10; y+=step){
    for(x = -10; x < 10; x+=step){
      Complex point = {.re = x, .im = y};
      Result r = does_point_escape(point,seed,R);
      if(r.stays_in){
        // printf("%.3f+%.3fi is in the Julia set for seed=(%.3f+%.3fi)\n",
          // point.re, point.im, seed.re, seed.im);
        JuliaSet[counter] = r;
        counter++;
      }
    }
  }

  printf("Found %d points in Julia set!\n", counter);
  return counter;
}

Point remappedPoints[300000];
void remap_points(int n_points){
  for(int i = 0; i < n_points; i++){
    Point p = (Point){ .x = (JuliaSet[i].c.re*100), .y = (JuliaSet[i].c.im*100) };
    remappedPoints[i] = (Point){320+(p.x), 240+(p.y)};
  }
}