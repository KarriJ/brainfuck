#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/bf_config.h"


char* re_size(char* arr, size_t size);
int add_char_to_string(char** arr_ptr, char ch, size_t arr_size, size_t idx);
char* read_file(const char *source_path);