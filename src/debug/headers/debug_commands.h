#pragma once 

#include <stdio.h>
#include <stdint.h>
#include "../../interpret/headers/interpreter_config.h"

#define BYTE_CMD "byte"
#define PTR_CMD "ptr"
#define OFFSET_CMD "offset"
#define INVALID_CMD_MSG "Command not recognized\n"
#define INVALID_PTR_MSG "Pointer value invalid\n"


extern int OFFSET;
extern char* ERROR_MESSAGE;

int byte_modify(uint8_t* arr, size_t ptr, int n);
int ptr_modify(size_t* ptr, int n);
int offset_modify(int n);
