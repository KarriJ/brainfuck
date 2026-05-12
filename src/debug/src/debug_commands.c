#include <stdio.h>
#include <stdint.h>
#include "../../interpret/headers/interpreter_config.h"


#define BYTE_CMD "byte"
#define PTR_CMD "ptr"
#define OFFSET_CMD "offset"
#define INVALID_CMD_MSG "Command not recognized\n"
#define INVALID_PTR_MSG "Pointer value invalid\n"


int OFFSET = 0;
char* ERROR_MESSAGE;

int byte_modify(uint8_t* arr, size_t ptr, int n)
{  
    if (arr == NULL)
    {
        printf("Data array NULL\n");
    }

    arr[ptr] = n;
    return 0;
}

int ptr_modify(size_t* ptr, int n)
{  
    if (n < 0 || n >= CELL_COUNT)
    {
        ERROR_MESSAGE = INVALID_PTR_MSG;
        return -1;
    }

    (*ptr) = (size_t)n;

    return 0;
}

int offset_modify(int n)
{
    int new_offset = n % (int)CELL_COUNT;
    OFFSET = new_offset;
    return 0;
}
