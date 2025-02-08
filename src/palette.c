#include <stdlib.h>
#include "palette.h"

void generate_palette(int p, uint32_t* dest){
  dest[0] = 0;
  switch(p){
    case CHANGE_B:
      for(int i = 1; i < 256; i++) dest[i] = (0x30+(i+MODIFY_AMOUNT_RB));
      break;
    case CHANGE_G:
      for(int i = 1; i < 256; i++) dest[i] = ((0x100*(i+MODIFY_AMOUNT_RB)));
      break;
    case CHANGE_R:
      for(int i = 1; i < 256; i++) dest[i] = ((65536*(i+MODIFY_AMOUNT_RB)));
      break;
  }
}
