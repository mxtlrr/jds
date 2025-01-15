#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "fb.h"

#define MAX_COLOR 0xF // 16bit rgb

// Writes
void write_file_to_buf(char* filename);