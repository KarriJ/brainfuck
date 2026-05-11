#include <stdio.h>
#include <stdint.h>
#include "../../../headers/file_read.h"
#include "../headers/functions.h"
#include "../../debug/headers/debug.h"


int run_program(char* bf)
{
    uint8_t array[CELL_COUNT] = {(uint8_t)0};
    size_t program_length = strlen((char*)bf);
    size_t ptr = 0;
    size_t idx = 0;

    while(idx < program_length && bf[idx] != '\0')
    {   
        if (debug_enabled() == 1)
        {
            if (debug(array, bf, &ptr, &idx, CELL_COUNT) == 1)
            {
                printf("Error in debug\n");
                return 1;
            }
        } 

        char instruction = bf[idx]; 
        if (run_instruction(instruction, array, bf, &ptr, &idx) == 1)
        {
            printf("Error handling instruction\n");
            return 1;
        }
    }

    return 0;
}

int interpret(char* source_path)
{   
    char* source_code = read_file(source_path);

    if (validate_source_code((char*)source_code) == 1)
    {   
        printf("Error loading source code\n");
        free(source_code);
        return 1;
    }

    if (run_program(source_code) == 1)
    {
        printf("Errors occured while interpreting program\n");
        free(source_code);
        return 1;
    }

    free(source_code);
    return 0;
}



