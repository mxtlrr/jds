#include "math/julia.h"

uint16_t palette[] = {
  0x000f, 0x001f, 0x002f, 0x003f,
  0x004f, 0x005f, 0x006f, 0x007f,
  0x008f, 0x009f, 0x00ff, 0x00bf,
  0x00cf, 0x00df, 0x00ef, 0x00ff
};

double scale_coord(int p, int sd, double min, double max) {
  return min + ((double)p / (sd - 1)) * (max - min);
}

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
  for(int y = 0; y < HEIGHT; y++){
    for(int x = 0; x < WIDTH; x++){
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

float determine_R(Complex c, int accuracy){
  // x^2 - x - (sqrt(Re(c)^2 + Im(c)^2))
  float CoeffC = -sqrt((Re(c)*Re(c)) + (Im(c)*Im(c)));

  // Solve the quadratic, and choose the one that's not negative
  Point solutions = {
    .x = (1 + sqrt(1 - (4*1*CoeffC)))/2,
    .y = (1 - sqrt(1 - (4*1*CoeffC)))/2
  };

  float correct = solutions.x;
  if(correct < 0) correct = solutions.y;

  // The correct value is technically a good R, we can just 
  // mulitply it by accuracy and return that.
  return correct*accuracy;
}