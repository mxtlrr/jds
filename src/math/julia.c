#include "math/julia.h"


Result does_point_escape(Complex z, Complex seed, int R){
  Complex z_n = z; // no im?
  for(int i = 0; i < 10; i++){
    z_n = ComplexMul(z_n, z_n); // z_n^2.
    z_n = ComplexAdd(z_n, seed);
    if(AbsComplex(z_n) > R){
      return (Result){ .iterations = i, .stays_in = false };
    }
  }
  return (Result){.iterations = 0, .stays_in = true, .c = z };
}



Result JuliaSet[9000];
int GenerateJuliaSet(Complex seed, int R){
  int counter = 0;
  float x=0;float y=0;
  for(y = -10; y < 10; y+=0.1){
    for(x = -10; x < 10; x+=0.1){
      Complex point = {.re = x, .im = y}; // Cursed!
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

Point remappedPoints[9000];
void remap_points(int n_points){
  for(int i = 0; i < n_points; i++){
    Point p = (Point){ .x = (JuliaSet[i].c.re*10), .y = (JuliaSet[i].c.im*10) };
    remappedPoints[i] = (Point){320+(p.x), 240+(p.y)};
  }
}