#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../../headers/bf_config.h"
#include "../headers/c_templates.h"


int find_matching(char* arr, size_t block_length, size_t idx)
{   
    // Finds a matching LOOP_END for LOOP_START at index size_t idx inside char* arr
    // returns index of match
    // -1 if not found or LOOP_STARTs and LOOP_ENDs are invalid
    if (arr[idx] != LOOP_START)
    {   
        printf("Instruction %c is not a loop start\n", arr[idx]);
        return -1;
    }

    int depth = 1;
    idx++;

    while (idx < block_length)
    {
        if (arr[idx] == LOOP_START)
        {
            depth++;
        }

        if (arr[idx] == LOOP_END)
        {
            depth--;
        }

        if (depth < 0)
        {   
            printf("Bracket mismatch caught\n");
            return -1;
        }

        if (depth == 0)
        {
            return idx;
        }

        idx++;
    }

    return -1;
}

size_t count_consecutive(char* bf, size_t idx)
{
    // Counts instructions of same type starting from size_t idx
    // returns size_t
    Instruction first = bf[idx];
    size_t bf_length = strlen(bf);
    size_t count = 0;
    while (bf[idx] == first && idx < bf_length)
    {
        count++;
        idx++;
    }
    return count;
}

char* make_loop(char* block)
{   
    // Turns char* block into a loop by adding it to wrapper template WHILE_STR
    // Mallocates char* loop_block according to size_t template_length and size_t block_length
    // Does NOT free parameters or return value
    // Returns char*
    // NULL if errors
    size_t block_length = strlen(block);
    size_t template_length = strlen(WHILE_STR);
    size_t space_needed = block_length + template_length + 1;

    char* loop_block = malloc(space_needed);

    if (loop_block == NULL)
    {
        printf("Couldn't mallocate for loop\n");
        return NULL;
    }

    snprintf(loop_block, space_needed, WHILE_STR, block);
    return loop_block; // Caller must free
}

// introducing here for recursion purposes
char* transpile_block(char* bf, size_t length, size_t* idx);

char* get_inner(char* bf, size_t end, size_t idx)
{
    // Wrapper for transpile_block when called recursively
    // Calls transpile_block for a new block and turns it into a loop with make_loop
    // Returns char*
    // NULL if errors
    char* inner_block = transpile_block(bf, end, &idx);

    if (inner_block == NULL)
    {   
        printf("Couldn't get inner block\n");
        return NULL;
    }

    char* loop_block = make_loop(inner_block);

    if (loop_block == NULL)
    {   
        printf("Couldn't mke loop\n");
        free(inner_block);
        return NULL;
    }
    free(inner_block);
    return loop_block; //Caller must free
}

char* match_template(Instruction instruction)
{
    // Matches instruction to function template
    // returns char* 
    // NULL if did not match
    char* template;
    switch (instruction) 
    {
        case BYTE_INCR:
            template = BYTE_INCR_STR;
            break;
        case BYTE_DECR:
            template = BYTE_DECR_STR;
            break;
        case PTR_INCR:
            template = PTR_INCR_STR;
            break;
        case PTR_DECR:
            template = PTR_DECR_STR;
            break;
        case INPUT:
            template = INPUT_STR;
            break;
        case OUTPUT: 
            template = OUTPUT_STR;
            break;
        default:
            printf("Instruction %c did not match any function template\n", instruction);
            template = NULL;
            break;
    }

    return template;
}

char* build_function(Instruction instruction, size_t n)
{
    // Builds a function call for instructions other than LOOP_START and LOOP_END
    // Mallocs memory for but does NOT free
    // Returns char*
    // NULL if errors
    char* template = match_template(instruction);
    if (template == NULL)
    {
        printf("Couldn't get template for function\n");
    }

    size_t template_length = strlen(template);
    size_t n_digits = snprintf(NULL, 0, "%d", (int)n);
    size_t space_needed = template_length + n_digits + 1;

    char* function = malloc(space_needed);

    if (function == NULL)
    {
        printf("Couldn't mallocate for function\n");
        return NULL;
    }

    snprintf(function, space_needed, template, n);
    return function; // Caller must free
}

char* handle_instruction(char* bf, Instruction instruction, size_t block_length, size_t* idx)
{   
    // Decides what steps are taken based on instruction type
    // On LOOP_START recursively calls transpile_block through wrapper get_inner
    // does not mallocate of free anything
    // returns char* temp with transpiled code 
    // NULL on error
    char* temp;

    if (instruction == LOOP_START)
    {   
        int end = find_matching(bf, block_length, (*idx)); 
        char* inner_block = get_inner(bf, end, ((*idx) + 1));

        if (inner_block == NULL)
        {   
            printf("Couldn't get inner block\n");
            return NULL;
        }

        temp = inner_block;
        (*idx) = end + 1;
    }   
    else
    {
        size_t same_in_row = count_consecutive(bf, (*idx));
        temp = build_function(instruction, same_in_row);
        (*idx) += same_in_row;
    }

    return temp; // Caller must free
}

char* block_append(char* block, char* new_part)
{
    // Mallocates char* temp according to lengths of char* block and char* new_part
    // Appends both parameters to char* temp and returns it
    // NULL if errors
    // Does NOT free any parameter or return value
    size_t block_length = strlen(block);
    size_t new_part_length = strlen(new_part);
    size_t space_needed = block_length + new_part_length + 1;

    char* temp = malloc(space_needed);
    if (temp == NULL)
    {
        printf("Couldn't mallocate memory while appending\n");
        return NULL;
    }

    sprintf(temp, "%s%s", block, new_part);
    return temp; // Caller must free
}

char* get_block(char* bf, size_t block_length, size_t* idx)
{   
    // Logic for transpile_block 
    // These two need to be refactored
    size_t capacity = 1;
    char* block = malloc(capacity);
    if (block == NULL) 
    {   
        printf("Error mallocating for new block\n");
        return NULL;
    }
    block[0] = '\0';

    while ((*idx) < block_length)
    {
        Instruction instruction = bf[(*idx)];

        if (instruction == LOOP_END)
        {
            (*idx)++;
            continue;
        }
        
        char* temp = handle_instruction(bf, instruction, block_length, idx);

        if (temp == NULL)
        {
            printf("Error handling instruction\n");
            free(block);
            return NULL;
        }

        char* new_block = block_append(block, temp);

        if (new_block == NULL)
        {   
            printf("Error appending to block\n");
            free(temp);
            free(block);
            return NULL;
        }

        free(temp);
        free(block);
        block = new_block;
    }

    return block; // Caller must free
}

char* transpile_block(char* bf, size_t length, size_t* idx)
{   
    // Transpiles a block from size_t* idx to size_t length
    // returns char* with allocated size N
    // NULL if errors 
    char* block = NULL;

    while ((*idx) < length)
    {
        block = get_block(bf, length, idx);
    }
    
    return block; // Caller must free;
}

char* transpile(char* bf_arr)
{   
    size_t idx = 0;
    size_t bf_length = strlen(bf_arr);
    char* transpiled_code = transpile_block(bf_arr, bf_length, &idx);

    if (transpiled_code == NULL)
    {
        printf("Error transpiling code\n");
        return NULL;
    }

    return transpiled_code; // Caller must free
}
