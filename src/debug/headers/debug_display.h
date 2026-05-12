#pragma once 

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "../../interpret/headers/interpreter_config.h"
#include "../headers/debug_commands.h"


#define INSTRUCTIONS "COMMANDS:\n| <empty> = execute instruction | <offset> <n> = change ptr view offset|\n| <byte> <n> = change byte value | <ptr> <n> = move ptr |\n"

extern int MAX_DIGITS;
void set_max_digits();
void clear_screen();
int cell_index_fix(int cell);
void display_cell_number(int cell);
void display_cell_numbers(uint8_t* array, int ptr);
void display_cell_value(uint8_t* array, int cell);
void display_cell_values(uint8_t* array, int ptr);
void display_ascii_value(uint8_t* array, int cell);
void display_ascii_values(uint8_t* array, int ptr);
void display_modifiers(size_t ptr);
void display_instructions();
void display_error_messages();
void display_instruction_stream(char* bf, size_t idx);
void display_stdout();
void display(char* bf, uint8_t* array, size_t ptr, size_t idx);