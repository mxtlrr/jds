#include <stdlib.h>
#include "palette.h"

uint32_t palette[] = {
  0x000000, 0x19071a, 0x09012f,
  0x040449, 0x000764, 0x0c2c8a,
  0x1852b1, 0x86b5e5, 0xd3ecf8,
  0xf1e9bf, 0xf8c95f, 0xffaa00,
  0xcc8000, 0x995700, 0x6a3403
};

float linear_interpolate(float v1, float v2, float t){
  return (1 - t) * v1 + t * v2;
}