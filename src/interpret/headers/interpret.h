#pragma once


#include <stdio.h>
#include <stdint.h>
#include "../../../headers/file_read.h"
#include "../../../headers/bf_config.h"
#include "../headers/functions.h"
#include "../../debug/headers/debug.h"

int run_program(Instruction* bf);
int interpret(char* source_path);



