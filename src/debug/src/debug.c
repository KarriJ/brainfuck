// for the record this specifically can be a cause of some major headache 
// I have not made a good job with this
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdint.h>
#include <string.h>
#include "../../interpret/headers/interpreter_config.h"
#include "../headers/debug_display.h"
#include "../headers/debug_commands.h"


bool DEBUGENABLED = false;

int debug_enabled()
{
    if (DEBUGENABLED)
    {
        return 1;
    }

    return 0;
}

int debug_enable()
{
    DEBUGENABLED = true;

    if (debug_enabled() == 1)
    {
        return 0;
    }

    printf("Couldn't enable debug mode\n");
    return 1;
}

int debug_disable()
{
    DEBUGENABLED = false;

    if (debug_enabled() == 0)
    {
        return 0;
    }

    printf("Couldn't disable debug mode\n");
    return 1;
}

int run_command(char* command, int n, uint8_t* array, size_t* ptr)
{
    // matches command and runs appropriate function
    // returns
    // 1 if errors
    // 0 if no errors or command not recognized
    // -1 for command was not run
    int exit_code = 0;
    if (strcmp(command, BYTE_CMD) == 0)
    {
        exit_code = byte_modify(array, (*ptr), n);
    }
    
    else if (strcmp(command, PTR_CMD) == 0)
    {
        exit_code = ptr_modify(ptr, n);
    }

    else if (strcmp(command, OFFSET_CMD) == 0)
    {
        exit_code = offset_modify(n);
    }

    else 
    {   
        ERROR_MESSAGE = INVALID_CMD_MSG;
    }

    return exit_code;
}

int get_command(uint8_t* array, size_t* ptr)
{
    // gets command and calls approriate function
    // returns 
    // -1 if empty command (move forward)
    // 0 if command ran without errors or was not recognized
    // 1 if errors
    
    char line[2048];
    char command[100];
    int n;

    printf("Debugger command : ");
    fgets(line, sizeof(line), stdin);

    if (line[0] == '\n')
    {
        return -1;
    }

    int argc = sscanf(line, "%99s %d", command, &n);
    if (argc == 1)
    {
        ERROR_MESSAGE = "Missing n\n";
    }

    int exit_code = run_command(command, n, array, ptr);
    if (exit_code == 1)
    {
        printf("Error running command\n");
        return 1;
    }

    return 0;
}

int debug(uint8_t* array, char* bf, size_t* ptr, size_t* idx)
{
    if (MAX_DIGITS == -1)
    {
        set_max_digits();
    }

    display(bf, array, (*ptr), (*idx));
    
    while (get_command(array, ptr) != -1)
    {
        display(bf, array, (*ptr), (*idx));
    }

    return 0;
}
