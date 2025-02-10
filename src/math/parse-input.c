#include "math/parse-input.h"

int countChars( char* s, char c ){
  return *s == '\0' ? 0 : countChars(s+1,c) + (*s == c);
}

Complex str_to_complex(char* str) {
    int decimals = countChars(str, '.');
    if (decimals == 1) {
        if (str[strlen(str) - 1] == '.') return (Complex){0, 0};
        if (countChars(str, 'i') == 0) return (Complex){strtof(str, NULL), 0};
        if (countChars(str, 'i') == 1) return (Complex){0, strtof(str, NULL)};
    }
    if (decimals == 0) return (Complex){0, 0};

    int plus_symbols = countChars(str, '+');
    int minus_symbols = countChars(str, '-');

    char a[MAX_PRECISION] = {0};
    char b[MAX_PRECISION] = {0};

    if (minus_symbols == 2) {
        // Re < 0, Im < 0.
        size_t l = 0;
        for (int i = 1; str[i] != '-'; i++) l = i;
        l++;

        strncpy(a, str, l);
        a[l] = '\0';
        strncpy(b, str + l, strlen(str) - l);
        b[strlen(str) - l] = '\0';
    } else {
        int new_thing = 0;
        if (strstr(str, "+") && minus_symbols != 2) {
            for (int i = 0; str[i] != '+'; i++) new_thing = i + 1;
        }
        if (strstr(str, "-") && plus_symbols != 2) {
            for (int i = 0; str[i] != '-'; i++) new_thing = i + 1;
        }
        strncpy(a, str, new_thing);
        a[new_thing] = '\0';

        int length_after_symbol = strlen(str) - new_thing - 1;
        strncpy(b, str + new_thing + 1, length_after_symbol);
        b[length_after_symbol] = '\0';
    }

    return (Complex){
        .re = strtof(a, NULL),
        .im = strtof(b, NULL)
    };
}

