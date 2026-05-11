#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../../../headers/bf_config.h"


#define CELL_COUNT 30000

int bounds_check(size_t ptr)
{
    // Checks if 0 <= ptr < CELL_COUNT
    if (ptr < 0 || ptr >= CELL_COUNT)
    {
        printf("Pointer out of bounds from previous actions\n");
        return 1;
    }

    return 0;
}

int increment_byte(uint8_t* array, size_t ptr)
{
    // instruction '+'
    // increments byte at data(array) pointer(ptr) by one
    if (array == NULL)
    {
        printf("Data array NULL\n");
        return 1;
    }
    
    if (bounds_check(ptr) == 1)
    {
        return 1;
    }
    
    array[ptr]++;
    return 0;
}   

int decrement_byte(uint8_t* array, size_t ptr)
{
    // instruction '-'
    // decrements byte at data(array) pointer(ptr) by one
    if (array == NULL)
    {
        printf("Data array NULL\n");
        return 1;
    }
    
    if (bounds_check(ptr) == 1)
    {
        return 1;
    }

    array[ptr]--;
    return 0;
}  

int increment_ptr(size_t* ptr)
{
    // instruction '>'
    // increments pointer (ptr) by one
    // wraps to 0 if past CELL_COUNT
    if (bounds_check((*ptr)) == 1)
    {
        return 1;
    }

    if ((*ptr) == CELL_COUNT - 1)
    {
        (*ptr) = 1;
        return 0;
    }

    (*ptr)++;
    return 0;
}

int decrement_ptr(size_t* ptr)
{
    // instruction '<'
    // decrements pointer (ptr) by one
    // wraps to CELL_COUNT -1 if < 0
    if (bounds_check((*ptr)) == 1)
    {
        return 1;
    }

    if ((*ptr) == 0)
    {
        (*ptr) = CELL_COUNT - 1;
        return 0;
    }

    (*ptr)--;
    return 0;
}

int input(uint8_t* array, size_t ptr)
{   
    // instruction ','
    // reads byte from stdin to data(array) pointer(ptr)
    if (array == NULL)
    {   
        printf("Data array is NULL\n");
        return 1;
    }

    if (bounds_check(ptr) == 1)
    {
        return 1;
    }
    
    int value = getchar();
    array[ptr] = (value == EOF) ? (uint8_t)0 : (uint8_t)value;

    return 0;
}

int output(uint8_t* array, size_t ptr)
{   
    // instruction '.'
    // outputs byte from data(array) pointer(ptr)
    if (array == NULL)
    {   
        printf("Data array is NULL\n");
        return 1;
    }

    if (bounds_check(ptr) == 1)
    {
        return 1;
    }

    putchar(array[ptr]);    
    return 0;
}

int jump_fwd(uint8_t* arr, size_t ptr, char* bf, size_t* idx)
{   
    // instruction '['
    // Checks if value at data(arr) pointer(ptr) is 0
    // if yes, do nothing
    // if not, move to matching ']'
    if (arr == NULL)
    {
        printf("Data array is NULL\n");
        return 1;
    }
    
    if (bounds_check(ptr) == 1)
    {
        return 1;
    }

    if (arr[ptr] != 0)
    {
        return 0;
    }

    int depth = 1;
    while(depth != 0)
    {
        (*idx)++;
        char instruction = bf[(*idx)];

        if (instruction == LOOP_START)
        {
            depth++;
        }
        if (instruction == LOOP_END)
        {
            depth--;
        }

    }

    return 0;
}

int jump_bwd(uint8_t* arr, size_t ptr, char* bf, size_t* idx)
{   
    // instruction ']'
    // Checks if value at data(arr) pointer(ptr) is 0
    // if yes, do nothing
    // if not, move to matching '['
    if (arr == NULL)
    {
        printf("Data array is NULL\n");
        return 1;
    }
    
    if (bounds_check(ptr) == 1)
    {
        return 1;
    }

    if (arr[ptr] == 0)
    {   
        return 0;
    }

    int depth = 1;
    while(depth != 0)
    {
        (*idx)--;
        char instruction = bf[(*idx)];

        if (instruction == LOOP_START)
        {
            depth--;
        }
        if (instruction == LOOP_END)
        {
            depth++;
        }

    }
    
    return 0;
}

int run_instruction(char instruction, uint8_t* array, char* bf, size_t* ptr, size_t* idx)
{   
    // matches one instruction to a function and runs it
    // returns 1 if something went wrong
    // 0 if no errors
    int result = 0;

    switch(instruction)
    {
        case BYTE_INCR:
            result = increment_byte(array, (*ptr));
            break;
        case BYTE_DECR:
            result = decrement_byte(array, (*ptr));
            break;
        case PTR_INCR:
            result = increment_ptr(ptr);
            break;
        case PTR_DECR:
            result = decrement_ptr(ptr);
            break;
        case LOOP_START:
            result = jump_fwd(array, (*ptr), bf, idx);
            break;
        case LOOP_END:
            result = jump_bwd(array, (*ptr), bf, idx);
            break;
        case INPUT:
            result = input(array, (*ptr));
            break;
        case OUTPUT:
            result = output(array, (*ptr));
            break;
        default:
            printf("Instruction %d not recognized\n", instruction);
            result = 1;
    }

    (*idx)++;
    return result;
}
