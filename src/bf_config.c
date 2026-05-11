#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const char* INSTRUCTION_SET = "<>+-.,[]";

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

int is_instruction(Instruction instruction)
{
    // returns 1 if found char ch is found in global char* INSTRUCTION_SET
    // otherwise 0
     
    for (size_t idx = 0; INSTRUCTION_SET[idx] != '\0'; idx++)
    {
        if (INSTRUCTION_SET[idx] == instruction)
        {
            return 1;
        }
    }

    return 0;
}

int validate_loops(char* array)
{  
    // Validates loops in array by iterating over it and tracking depth
    // 0 if no errors
    // 1 if errors
    size_t program_length = strlen(array);
    int depth = 0;

    for (int idx = 0; idx < program_length; idx++)
    {
        Instruction instruction = array[idx];

        if (is_instruction(instruction) == 0)
        {
            printf("Invalid instruction caught\n");
            return 1;
        }

        if (depth < 0)
        {
            printf("Brackets mismatch\n");
            return 1;
        }

        if (instruction == LOOP_START)
        {
            depth++;
        }

        if (instruction == LOOP_END)
        {
            depth--;
        }

    }

    if (depth != 0)
    {
        printf("Brackets mismatch\n");
        return 1;
    }

    return 0;
}


