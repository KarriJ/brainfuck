#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../../../headers/gcc_templates.h"
#include "../headers/c_templates.h"

time_t current_unix_time() 
{
    time_t now = time(NULL);
    return now;
}

char* make_temp(char* path)
{
    int timestamp = current_unix_time();
    size_t timestamp_buffer = 23; // This is not great
    size_t path_length = strlen(path);
    size_t size_needed = strlen(TEMP_FILE) + path_length + timestamp_buffer + 1;
    
    char* buffer = malloc(size_needed * sizeof(char));

    if (buffer == NULL)
    {
        printf("Couldn't malloc in make_temp\n");
        return NULL;
    }

    snprintf(buffer, size_needed, TEMP_FILE, path, timestamp);

    return buffer; // Caller must free
}

int write_to_temp(char* path, char* code)
{
    FILE *fptr = fopen(path, "w");
    if (fptr == NULL)
    {
        printf("Couldn't open temp file");
        return 1;
    }

    FILE* boilerplate = fopen(BOILERPLATE_PATH, "r");
    if (boilerplate == NULL)
    {
        fclose(fptr);
        printf("Couldn't read boilerplate\n");
        return 1;
    }
    
    size_t row_buffer = 128;
    char row[row_buffer];
    char temp[row_buffer];

    while (fgets(row, row_buffer, boilerplate))
    {
        strcpy(temp, row);

        if (row[0] == '/')
        {
            temp[strcspn(temp, "\r\n")] = '\0';
        }

        if (strcmp(temp, PROGRAM_PLACEHOLDER) == 0)
        {  
            fprintf(fptr, "%s", code);
        }

        else
        {
            fprintf(fptr, "%s", row);
        }
    }
    fclose(boilerplate);
    fclose(fptr);
    return 0;
}

int delete_file(char* path)
{
    if (remove(path) == 1)
    {
        printf("Error deleting temp file\n");
        return 1;
    }

    return 0;
}

int compile_code(char* source, char* destination)
{   
    size_t command_length = strlen(COMPILE_COMMAND);
    size_t source_length = strlen(source);
    size_t destination_length = strlen(destination);
    size_t buffer_needed = destination_length + source_length + command_length + 1;
    char* command = malloc(buffer_needed * sizeof(char));
    
    snprintf(command, buffer_needed, COMPILE_COMMAND, destination, source);

    if (system(command) != 0)
    {
        printf("Error calling gcc\n");
        free(command);
        return 1;
    }

    free(command);
    return 0;
}

int output_program(char* transpiled_code, char* destination)
{
    char* temp_path = make_temp(destination);

    if (temp_path == NULL)
    {   
        printf("Error making temp file\n");
        return 1;
    }

    if (write_to_temp(temp_path, transpiled_code) == 1)
    {   
        printf("Error writing to temp files\n");
        free(temp_path);
        delete_file(temp_path);
        return 1;
    }

    if (compile_code(temp_path, destination) == 1)
    {
        printf("Error compiling code\n");
        delete_file(temp_path);
        free(temp_path);
        return 1;
    }

    delete_file(temp_path);
    free(temp_path);

    return 0;
}
