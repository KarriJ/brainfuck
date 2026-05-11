#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/bf_config.h"


int validate_source_code(char* source_code)
{   
    // Checks if source code was correctly loaded
    // Returns 1 if errors occured or source code empty
    // 0 if no issues
    if (source_code == NULL)
    {
        printf("Error reading source code\n");
        return 1;
    }

    if (source_code[0] == '\0')
    {
        printf("Source code empty\n");
        free(source_code);
        return 1;
    }

    return 0;
}

char* re_size(char* arr, size_t size)
{   
    // reallocs memory to char* arr, return char* new
    // if failed, return NULL

    char* temp = realloc(arr, size * sizeof(char));

    if (temp == NULL)
    {   
        printf("Couldn't realloc in re_size\n");
        return arr;
    }

    arr = temp;
    return arr;
}

int add_char_to_string(char** arr_ptr, char ch, size_t arr_size, size_t idx)
{   
    // double arr_size until enough allocated
    int need_more_memory = 0;
    while (arr_size < idx + 1)
    {
        arr_size *= 2;
        need_more_memory = 1;
    }

    if (need_more_memory == 1)
    {
        (*arr_ptr) = re_size((*arr_ptr), arr_size);
    }

    (*arr_ptr)[idx] = ch;

    return arr_size; // Return size after adding
}

char* read_file(const char *source_path)
{
    // returns an char*
    // NULL if something went wrong

    size_t arr_size = 1;
    size_t idx = 0;
    char* arr = malloc(arr_size * sizeof(char));
    char **arr_ptr = &arr;
    FILE* fptr = fopen(source_path, "r");

    // Return NULL if memory allocation failed
    if (arr == NULL)
    {
        printf("Memory couldn't be allocated in read_file\n");
        return NULL;
    }

    // Return NULL if file wasn't opened successfully
    if (fptr == NULL)
    {   
        printf("Source '%s' couldn't be read.\n", source_path);
        free(arr);
        return NULL;
    }

    int ch;
    while ((ch = fgetc(fptr)) != EOF) 
    {
        if (is_instruction((char)ch) == 0)
        {
            continue;
        }

        arr_size = add_char_to_string(arr_ptr, (char)ch, arr_size, idx);
        idx++;
    }

    fclose(fptr);

    char* temp = re_size((*arr_ptr), idx + 1);

    if (temp == NULL)
    {
        free((*arr_ptr));
        return NULL;
    }

    temp[idx] = '\0';
    return temp; // Caller must free
}