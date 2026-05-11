// for the record this specifically can be a cause of some major headache 
// I have not made a good job with this
// Memory access violations for all I know

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdint.h>
#include <string.h>

#define INSTRUCTIONS "COMMANDS:\n| <empty> = execute instruction | <offset> <n> = change ptr view offset|\n| <byte> <n> = change byte value | <ptr> <n> = move ptr |\n"
#define BYTE_CMD "byte"
#define PTR_CMD "ptr"
#define OFFSET_CMD "offset"
#define INVALID_CMD_MSG "Command not recognized\n"
#define INVALID_PTR_MSG "Pointer value invalid\n"

bool DEBUG = false;
int MAX_DIGITS = -1;
int OFFSET = 0;
char* ERROR_MESSAGE;

int debug_enabled()
{
    if (DEBUG)
    {
        return 1;
    }

    return 0;
}

int debug_enable()
{
    DEBUG = true;

    if (debug_enabled() == 1)
    {
        return 0;
    }

    printf("Couldn't enable debug mode\n");
    return 1;
}

int debug_disable()
{
    DEBUG = false;

    if (debug_enabled() == 0)
    {
        return 0;
    }

    printf("Couldn't disable debug mode\n");
    return 1;
}

void clear_screen()
{
    printf("\033[2J\033[H");
}

void display_cell_number(int cell, int cell_count)
{
    // displays the index of given cell
    if (cell < 0)
    {
        cell = cell_count + cell;
    }
    printf(" %*d  ", MAX_DIGITS,  cell);
}

void display_cell_numbers(uint8_t* array, int ptr, int cell_count)
{   
    // displays 11 cells
    // 5 on both sides of ptr
    printf("CELL : ...");
    int cell = (int)ptr + OFFSET - 5;
    
    for (int ii = 0; ii < 11; ii++, cell++)
    {
        display_cell_number(cell, cell_count);
    }
    printf("...\n");
}

void display_cell_value(uint8_t* array, int cell, int cell_count)
{
    // displays value of byte in data array
    if (cell < 0)
    {
        cell = cell_count - cell;
    }
    printf("[%*u] ", MAX_DIGITS,  array[cell]);
}

void display_cell_values(uint8_t* array, int ptr, int cell_count)
{
    // displayes 11 values from data array
    // 5 from both sides of ptr
    printf("VAL  : ...");
    int cell = (int)ptr + OFFSET - 5;
    
    for (int ii = 0; ii < 11; ii++, cell++)
    {
        display_cell_value(array, cell, cell_count);
    }
    printf("...\n");

}

void display_modifiers(size_t ptr)
{
    printf("POINTER : %d\n", (int)ptr);
    printf("OFFSET  : %d\n", OFFSET);
}

void display_instructions()
{
    // displays istructions
    printf("%s\n", INSTRUCTIONS);
}
void display_error_messages()
{
    if (ERROR_MESSAGE != NULL)
    {
        printf("%s\n", ERROR_MESSAGE);
        ERROR_MESSAGE = NULL;
    }
}

void display_instruction_stream(char* bf, size_t idx)
{   
    static int program_length = -1;
    if (program_length == -1)
    {
        program_length = strlen(bf);
    }

    printf("Instruction stream : ");

    for (int ii = idx; ii < idx + 10; ii++)
    {
        if (ii >= program_length)
        {
            break;
        }

        printf("%c ", bf[ii]);
    }

    printf("..\n");
}

void display(char* bf, uint8_t* array, size_t ptr, size_t idx, int cell_count)
{
    clear_screen();
    printf("\n\n");
    display_cell_numbers(array, ptr, cell_count);
    display_cell_values(array, ptr, cell_count);
    printf("\n\n");
    display_modifiers(ptr);
    display_instruction_stream(bf, idx);
    printf("\n\n");
    display_instructions();
    printf("\n\n");
    display_error_messages();
    printf("\n");
}

void set_max_digits(int cell_count)
{
    MAX_DIGITS = snprintf(NULL, 0, "%d", cell_count);
    MAX_DIGITS++; // for additional - character
}

int byte_modify(uint8_t* arr, size_t ptr, int n)
{  
    if (arr == NULL)
    {
        printf("Data array NULL\n");
    }

    arr[ptr] = n;
    return 0;
}

int ptr_modify(size_t* ptr, int n, size_t cell_count)
{  
    if (n < 0 || n >= cell_count)
    {
        ERROR_MESSAGE = INVALID_PTR_MSG;
        return -1;
    }

    (*ptr) = (size_t)n;

    return 0;
}

int offset_modify(int n, size_t cell_count)
{
    int new_offset = n % (int)cell_count;
    OFFSET = new_offset;
    return 0;
}

int run_command(char* command, int n, uint8_t* array, size_t* ptr, size_t cell_count)
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
        exit_code = ptr_modify(ptr, n, cell_count);
    }

    else if (strcmp(command, OFFSET_CMD) == 0)
    {
        exit_code = offset_modify(n, cell_count);
    }

    else 
    {   
        ERROR_MESSAGE = INVALID_CMD_MSG;
    }

    return exit_code;
}

int get_command(uint8_t* array, size_t* ptr, size_t cell_count)
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

    int exit_code = run_command(command, n, array, ptr, cell_count);
    if (exit_code == 1)
    {
        printf("Error running command\n");
        return 1;
    }

    return 0;
}

int debug(uint8_t* array, char* bf, size_t* ptr, size_t* idx, int cell_count)
{
    if (MAX_DIGITS == -1)
    {
        set_max_digits(cell_count);
    }

    display(bf, array, (*ptr), (*idx), cell_count);
    
    while (get_command(array, ptr, cell_count) != -1)
    {
        display(bf, array, (*ptr), (*idx), cell_count);
    }

    return 0;
}
