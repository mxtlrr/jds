#include "math/julia.h"

uint16_t palette[16];

double scale_coord(int p, int sd, double min, double max) {
  return min + ((double)p / (sd - 1)) * (max - min);
}

int pixel(Point a, Complex c, int R){
  float zx = (a.x)/(WIDTH-1)*2*zoom-zoom+zoomXY.re;
  float zy = (a.y)/(HEIGHT-1)*2*zoom-zoom+zoomXY.im;

  int i = 0;
  while(zx*zx + zy*zy < (R*R) && i<MAX_ITERATIONS){
    double xtemp = zx*zx - zy*zy;
    zy = 2*zx*zy+c.im;
    zx = xtemp + c.re;
    i++;
  }

  return (i == MAX_ITERATIONS) ? 0 : i;
}


Result JuliaSet[JULIA_SET_SIZE];
int GenerateJuliaSet(Complex seed, int R){
  int counter = 0;
  // Dont map it because it will try and access pixels that do not exist.
  // y must be between (x, 0) and (x, HEIGHT).
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

Complex FBPixelToComplex(Point p){
  return (Complex){
    .re = (p.x)/(WIDTH-1)*2*zoom-zoom+zoomXY.re,
    .im = (p.y)/(HEIGHT-1)*2*zoom-zoom+zoomXY.im
  };
}


/** ZOOM */

double zoom = 2;
Complex zoomXY = {0,0};
void zoomIn(double zoomFactor, float R, Complex c){
  zoom *= zoomFactor;
  GenerateJuliaSet(c,R);
  // framebuffer should be updated after this.
}

void setZoomXY(Complex new){
  zoomXY = new;
}
