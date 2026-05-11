#include <stdio.h>
#include <stdint.h>


#define CELL_COUNT 30000

void increment_ptr(size_t* ptr, int n)
{
    (*ptr) += (size_t)n;
    if ((*ptr) >= CELL_COUNT)
    {
        (*ptr) = (*ptr) % CELL_COUNT;
    }
}

void decrement_ptr(size_t* ptr, int n)
{
    (*ptr) = ((*ptr) + CELL_COUNT - ((size_t)n % CELL_COUNT)) % CELL_COUNT;
}

void increment_byte(uint8_t* array, size_t ptr, int n)
{
    for (size_t idx = 0; idx < n; idx++)
    {
        array[ptr]++;
    }
}

void decrement_byte(uint8_t* array, size_t ptr, int n)
{   
    for (size_t idx = 0; idx < n; idx++)
    {
        array[ptr]--;
    }
}

void byte_out(uint8_t* array, size_t ptr, int n)
{
    for (size_t idx = 0; idx < n; idx++)
    {
        putchar(array[ptr]);
    }
}

void byte_in(unsigned char* array, size_t ptr, int n)
{
    for (size_t idx = 0; idx < n; idx++)
    {
        int value = getchar();
        array[ptr] = (value == EOF) ? (uint8_t)0 : (uint8_t)value;
    }
}

int main()
{
    uint8_t array[CELL_COUNT] = {(uint8_t)0};
    size_t ptr = 0;
    size_t idx = 0;
/*PROGRAM HERE*/
    return 0;
}


// Loopit sisältyy väärin