#pragma once


#define BYTE_INCR_STR "increment_byte(array, ptr, %d);\n" 
#define BYTE_DECR_STR "decrement_byte(array, ptr, %d);\n"
#define PTR_INCR_STR "increment_ptr(&ptr, %d);\n"
#define PTR_DECR_STR "decrement_ptr(&ptr, %d);\n"
#define OUTPUT_STR "byte_out(array, ptr, %d);\n"
#define INPUT_STR "byte_in(array, ptr, %d);\n"
#define WHILE_STR "while(array[ptr] != 0)\n{\n%s\n}\n"
#define PROGRAM_PLACEHOLDER "/*PROGRAM HERE*/"
