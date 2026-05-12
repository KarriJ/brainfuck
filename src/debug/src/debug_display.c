#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "../../interpret/headers/interpreter_config.h"
#include "../headers/debug_commands.h"
#include "../headers/stdout_tracker.h"

#define INSTRUCTIONS "COMMANDS:\n| <empty> = execute instruction | <offset> <n> = change ptr view offset|\n| <byte> <n> = change byte value | <ptr> <n> = move ptr |\n"

int MAX_DIGITS = -1;

void set_max_digits()
{
    MAX_DIGITS = snprintf(NULL, 0, "%d", CELL_COUNT);
    MAX_DIGITS++; // for additional - character
}

void clear_screen()
{
    printf("\033[2J\033[H");
}

int cell_index_fix(int cell)
{
    // helps wrap cell index if below 0 or above CELL_COUNT - 1
    if (cell < 0)
    {
        cell = CELL_COUNT + cell;
    }

    if (cell >= CELL_COUNT)
    {
        cell = cell % CELL_COUNT;
    }

    return cell;
}

void display_cell_number(int cell)
{
    // displays the index of given cell
    cell = cell_index_fix(cell);
    printf(" %*d  ", MAX_DIGITS,  cell);
}

void display_cell_numbers(uint8_t* array, int ptr)
{   
    // displays 11 cells
    // 5 on both sides of ptr
    printf("CELL : ...");
    int cell = (int)ptr + OFFSET - 5;
    
    for (int ii = 0; ii < 11; ii++, cell++)
    {
        display_cell_number(cell);
    }
    printf("...\n");
}

void display_cell_value(uint8_t* array, int cell)
{
    // displays value of byte in data array
    cell = cell_index_fix(cell);
    printf("[%*u] ", MAX_DIGITS,  array[cell]);
}

void display_cell_values(uint8_t* array, int ptr)
{
    // displays 11 values from data array
    // 5 from both sides of ptr
    printf("VAL  : ...");
    int cell = (int)ptr + OFFSET - 5;
    
    for (int ii = 0; ii < 11; ii++, cell++)
    {
        display_cell_value(array, cell);
    }
    printf("...\n");

}

void display_ascii_value(uint8_t* array, int cell)
{
    // displays ascii representation for byte in data array
    cell = cell_index_fix(cell);
    char ch = ( isprint(array[cell]) ) ? (char)array[cell] : ' ';
    printf("[%*c] ", MAX_DIGITS, ch);
}

void display_ascii_values(uint8_t* array, int ptr)
{
    // displays ascii representations for 11 values from data array
    // 5 from both sides of ptr
    printf("ASCII: ...");
    int cell = (int)ptr + OFFSET - 5;
    
    for (int ii = 0; ii < 11; ii++, cell++)
    {
        display_ascii_value(array, cell);
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

    printf("Stream  : ");

    for (int ii = idx; ii < idx + 10; ii++)
    {
        if (ii >= program_length)
        {
            break;
        }

        printf("%c ", bf[ii]);
    }

    printf("\n");
}

void display_stdout()
{
    printf("__STDOUT__\n");
    
    if (TRACKING_STARTED == true)
    {
        tracker_print(&STDOUT_TRACKER);
    }

    printf("\n____");
}

void display(char* bf, uint8_t* array, size_t ptr, size_t idx)
{
    clear_screen();
    printf("\n\n");
    display_cell_numbers(array, ptr);
    display_cell_values(array, ptr);
    display_ascii_values(array, ptr);
    printf("\n\n");
    display_modifiers(ptr);
    display_instruction_stream(bf, idx);
    printf("\n");
    display_stdout();
    printf("\n\n");
    display_instructions();
    printf("\n\n");
    
    display_error_messages();
    printf("\n");
}
