#pragma once 

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

extern bool DEBUG_ENABLED;

int debug_enabled();
int debug_enable();
int debug_disable();
int debug(uint8_t* array, char* bf, size_t* ptr, size_t* idx, int cell_count);
