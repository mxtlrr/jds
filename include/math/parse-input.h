/* parses a char* into a complex type */
#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#include "complex.h"

// Each decimal will have some max precision, i.e. 0.45678 (prec=5),
// this makesit easier to convert
#define MAX_PRECISION 5

Complex str_to_complex(char* str);