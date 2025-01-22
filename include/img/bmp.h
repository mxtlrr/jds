#pragma once


#include <stdio.h>
#include <stdint.h>

#include "fb.h"

uint32_t rgb_to_bgr(uint32_t rgb);
void write_header(const char* file, uint32_t* data);
void generate_image_file(char* filename);
