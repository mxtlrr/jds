#pragma once

typedef struct Complex {
  float re;
  float im;
} Complex;

float Re(Complex c);
float Im(Complex c);

/* Arithmetic */

// a + b
Complex ComplexAdd(Complex a, Complex b);

// a-b
Complex ComplexSub(Complex a, Complex b);

// a*b
Complex ComplexMul(Complex a, Complex b);
