#pragma once 

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdint.h>
#include <string.h>
#include "../../interpret/headers/interpreter_config.h"
#include "../headers/debug_display.h"
#include "../headers/debug_commands.h"


extern bool DEBUGENABLED;


int debug_enabled();
int debug_enable();
int debug_disable();
int run_command(char* command, int n, uint8_t* array, size_t* ptr);
int get_command(uint8_t* array, size_t* ptr);
int debug(uint8_t* array, char* bf, size_t* ptr, size_t* idx);
