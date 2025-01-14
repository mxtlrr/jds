#include "math/complex.h"

float Re(Complex c){ return c.re; }
float Im(Complex c){ return c.im; }

Complex ComplexAdd(Complex a, Complex b){
  // a = x+yi, b = u+vi
  return (Complex){.re = (a.re + b.re), .im = (a.im + b.im)};
}

Complex ComplexSub(Complex a, Complex b){
  return (Complex){.re = (a.re - b.re), .im = (a.im - b.im)};
}

Complex ComplexMul(Complex a, Complex b){
  // (a+bi) * (c+di) = ac-bd + (ad+bc)i
  return (Complex){.re = ((a.re*b.re)-(a.im*b.im)),
                    .im = ((a.re*b.im)+(a.im*b.re))};
}