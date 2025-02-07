#include <stdlib.h>
#include "palette.h"

void generate_palette(int p, uint32_t* dest){
  // if(p == CHANGE_R) return;
  double value = 65536 * pow(2,-4*p); // cursed.
  for(int i=0; i<256; i++) dest[i] = ((int)(value*i)); 
}
