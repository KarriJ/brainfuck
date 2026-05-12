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
#include "../headers/debug_exit_codes.h"

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

Debugger_exit run_command(char* command, int n, uint8_t* array, size_t* ptr)
{
    // matches command and runs appropriate function
    // returns
    // FATAL_ERR if errors that can't be handled
    // ERR if errors can be handled
    // NO_ERR if no errors or command was not recognized
    int exit_code = NO_ERR;

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

Debugger_exit get_command(uint8_t* array, size_t* ptr)
{
    // gets command and calls approriate function
    // returns 
    // -1 if empty
    // 0 if command ran without errors or was not recognized
    // 1 if fatal errors
    
    char line[2048];
    char command[100];
    int n;

    printf("Debugger command : ");
    if (fgets(line, sizeof(line), stdin) == NULL)
    {
        printf("EOF in stdin\n");
        return FATAL_ERR;
    }

    if (line[0] == '\n' || line[0] == '\0')
    {
        return EMPTY;
    }
    
    int argc = sscanf(line, "%99s %d", command, &n);
    if (argc == 1)
    {
        ERROR_MESSAGE = "Missing n\n";
        return ERR;
    }

    Debugger_exit exit_code = run_command(command, n, array, ptr);
    if (exit_code == FATAL_ERR)
    {
        printf("Error running command\n");
        return FATAL_ERR;
    }

    return NO_ERR;
}

int debug(uint8_t* array, char* bf, size_t* ptr, size_t* idx)
{
    if (MAX_DIGITS == -1)
    {
        set_max_digits();
    }

    display(bf, array, (*ptr), (*idx));
    
    Debugger_exit code = NO_ERR;
    while (code != EMPTY)
    {   
        code = get_command(array, ptr);

        if (code == FATAL_ERR)
        {
            printf("Debugger command error\n");
            return 1;
        }

        display(bf, array, (*ptr), (*idx));
    }

    return 0;
}
