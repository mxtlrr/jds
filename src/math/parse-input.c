#include "math/parse-input.h"

int countChars( char* s, char c ){
  return *s == '\0' ? 0 : countChars(s+1,c) + (*s == c);
}

// This segfaults because it doesn't know what to do when neither are
// involved.
Complex str_to_complex(char* str){
  if(countChars(str, '.') == 1){
    if(str[strlen(str)-1] == '.') return (Complex){0,0};
    if(countChars(str, 'i') == 0) return (Complex){strtof(str, NULL), 0};
    if(countChars(str, 'i') == 1) return (Complex){0, strtof(str, NULL)};
  }
  if(countChars(str, '.') == 0) return (Complex){0,0};
  

  // do something
  char a[MAX_PRECISION+3] = {0};
  char b[MAX_PRECISION+3] = {0};

  int new_thing = 0;
  if(strstr(str, "+") && countChars(str, '-') != 2) for(int i = 0; str[i] != '+'; i++) new_thing = i+1;
  if(strstr(str, "-") && countChars(str, '+') != 2) for(int i = 0; str[i] != '-'; i++) new_thing = i+1;
  strncpy(a, str, new_thing);

  int length_after_plus = (strlen(str)-new_thing-1);
  strncpy(b, str+new_thing+1, length_after_plus-1);

  Complex c = {
    .re = strtof(a, NULL),
    .im = strtof(b, NULL)
  };

  if(str[new_thing] == '-') c.im *= -1;
  return c;
}

