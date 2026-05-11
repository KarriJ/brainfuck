#pragma once


#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern const char* INSTRUCTION_SET;

typedef enum 
{
    PTR_INCR = '>',
    PTR_DECR = '<',
    BYTE_INCR = '+',
    BYTE_DECR = '-',
    OUTPUT = '.',
    INPUT = ',',
    LOOP_START = '[',
    LOOP_END = ']'
} Instruction;

int is_instruction(Instruction instruction);
int validate_loops(char* array);


