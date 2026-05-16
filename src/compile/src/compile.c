#include <stdio.h>
#include <stdlib.h>
#include "../../../headers/file_read.h"
#include "../headers/transpile.h"
#include "../headers/file_output.h"

int compile(char* source_path, char* destination)
{
    char* source_code = read_file(source_path);
    
    if (validate_loops(source_code) == 1)
    {
        printf("Error with loops\n");
        free(source_code);
        return 1;
    }

    char* program = transpile(source_code);


    if (program == NULL)
    {
        printf("Error transpiling\n");
        free(source_code);
        return 1;
    }

    free(source_code);

    if (output_program(program, destination) == 1)
    {
        printf("Error compiling or writing transpiled code\n");
        free(program);
        return 1;
    }
    
    free(program);
    return 0;
}