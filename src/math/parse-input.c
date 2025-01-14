#include "math/parse-input.h"

Complex str_to_complex(char* str){
  char a[MAX_PRECISION+3] = {0};
  char b[MAX_PRECISION+3] = {0};

  int new_thing = 0;
  for(int i = 0; str[i] != '+'; i++) new_thing = i+1;
  strncpy(a, str, new_thing);

  int length_after_plus = (strlen(str)-new_thing-1);
  strncpy(b, str+new_thing+1, length_after_plus-1);

  Complex c = {
    .re = strtof(a, NULL),
    .im = strtof(b, NULL)
  };
  return c;
}