#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../../headers/bf_config.h"
#include "../headers/c_templates.h"


int find_matching(char* arr, size_t block_length, size_t idx);
size_t count_consecutive(char* bf, size_t idx);
char* make_loop(char* block);
char* get_inner(char* bf, size_t end, size_t idx);
char* match_template(Instruction instruction);
char* build_function(Instruction instruction, size_t n);
char* handle_instruction(char* bf, Instruction instruction, size_t block_length, size_t* idx);
char* block_append(char* block, char* new_part);
char* get_block(char* bf, size_t block_length, size_t* idx);
char* transpile_block(char* bf, size_t length, size_t* idx);
char* transpile(char* bf_arr);
