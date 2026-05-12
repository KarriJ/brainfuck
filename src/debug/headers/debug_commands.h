#pragma once 

#include <stdio.h>
#include <stdint.h>
#include "../../interpret/headers/interpreter_config.h"
#include "../headers/debug_exit_codes.h"

#define BYTE_CMD "byte"
#define PTR_CMD "ptr"
#define OFFSET_CMD "offset"
#define INVALID_CMD_MSG "Command not recognized\n"
#define INVALID_PTR_MSG "Pointer value invalid\n"


extern int OFFSET;
extern char* ERROR_MESSAGE;

Debugger_exit byte_modify(uint8_t* arr, size_t ptr, int n);
Debugger_exit ptr_modify(size_t* ptr, int n);
Debugger_exit offset_modify(int n);
