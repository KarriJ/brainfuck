#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


time_t current_unix_time(); 
char* make_temp(char* destination);
int write_to_temp(char* path, char* code);
int delete_file(char* path);
int compile_code(char* source, char* destination);
int output_program(char* transpiled_code, char* destination);

