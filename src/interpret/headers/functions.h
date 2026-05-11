#pragma once 


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../../../headers/bf_config.h"


#define CELL_COUNT 30000

int bounds_check(size_t ptr);
int increment_byte(uint8_t* array, size_t ptr);
int decrement_byte(uint8_t* array, size_t ptr);
int increment_ptr(size_t* ptr);
int decrement_ptr(size_t* ptr);
int input(uint8_t* array, size_t ptr);
int output(uint8_t* array, size_t ptr);
int jump_fwd(uint8_t* arr, size_t ptr, char* bf, size_t* idx);
int jump_bwd(uint8_t* arr, size_t ptr, char* bf, size_t* idx);
int run_instruction(Instruction instruction, uint8_t* array, char* bf, size_t* ptr, size_t* idx);
