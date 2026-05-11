#include <stdio.h>
#include <stdbool.h>
#include "./compile/headers/compile.h"
#include "./interpret/headers/interpret.h"
#include "./debug/headers/debug.h"

typedef enum 
{
    COMPILE = 'c',
    INTERPRET = 'i',
    DEBUG = 'd'
} Mode;


Mode selected_mode = -1;
char* source_path = NULL;
char* destination_path = NULL;

int validate_args()
{
    // Returns 1 if errors are found
    // 0 if args are good

    bool errors = false;
    if (selected_mode == -1)
    {
        printf("Mode not selected\n");
        errors = true;
    }
    
    if (source_path == NULL)
    {
        printf("Unable to work without source\n");
        errors = true;
    }
    
    if (selected_mode == INTERPRET || selected_mode == DEBUG)
    {
        if (destination_path != NULL)
        {
            printf("Destination not required to interpret or debug\n");
            errors = true;
        }
    }

    if (selected_mode == COMPILE && destination_path == NULL)
    {
        printf("Unable to compile without destination\n");
        errors = 1;
    }

    return 0;
}

int set_flag(char* flag)
{
    if (selected_mode != -1)
    {
        printf("Conflicting flags\n");
        return 1;
    }

    selected_mode = flag[1];

    switch (selected_mode) 
    {
        case COMPILE:
        case INTERPRET:
        case DEBUG:
            return 0;
        default:
            printf("Invalid mode selected\n");
            return 1;
    }

    return 1;
}

int set_path(char* path, bool last_was_flag)
{
    if (last_was_flag == true)
    {
        if (source_path != NULL)
        {
            printf("Conflicting source paths\n");
            return 1;
        }

        source_path = path;
        return 0;
    }

    if (destination_path != NULL)
    {
        printf("Conflicting destination paths\n");
        return 1;
    }

    destination_path = path;
    return 0;
}

int set_args(int argc, char** argv)
{   
    bool last_was_flag = false;
    for (int idx = 1; idx < argc; idx++)
    {
        char* arg = argv[idx];

        if (arg[0] == '-')
        {
            if (set_flag(arg) == 1)
            {
                printf("Error setting flags\n");
                return 1;
            }

            last_was_flag = true;
            continue;
        }
        
        if (set_path(arg, last_was_flag) == 1)
        {   
            printf("Error setting paths\n");
            return 1;
        }

        last_was_flag = false;
    }

    if (validate_args() == 1)
    {
        return 1;
    }

    return 0;
}

void help_panel()
{
    printf("----Brainfuck tools----\n");
    printf("Modes\n");
    printf("\t[-i]nterpret - <mode> <source_file>\n");
    printf("\t[-d]debug - <mode> <source_file>\n");
    printf("\t[-c]compile - <mode> <source_file> + <destination>\n\n");
}

void print_args()
{
    printf("----Args----\n");
    printf("Source path: %s\n", source_path);
    printf("Destination path: %s\n", destination_path);
    printf("Selected_mode: %d\n\n", selected_mode);
}

int main(int argc, char** argv)
{

    if (argc == 1)
    {
        help_panel();
        return 1;
    }

    if (set_args(argc, argv) == 1)
    {
        printf("Args couldn't be parsed\nRun with no args for help\n");
        print_args();
        return 1;
    }

    if (selected_mode == COMPILE)
    {
        if (compile(source_path, destination_path) == 1)
        {
            return 1;
        }

        return 0;
    }

    else if (selected_mode == INTERPRET || selected_mode == DEBUG)
    {   
        if (selected_mode == DEBUG)
        {
            if (debug_enable() == 1)
            {
                return 1;
            }
        }

        if (interpret(source_path) == 1)
        {
            return 1;
        }

        return 0;
    }
    
    printf("Error(s) occured and were not caught\n");
    return 1;
}

