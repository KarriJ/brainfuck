#pragma once 

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

extern bool DEBUG_ENABLED;

typedef struct 
{
    uint8_t* array;
    size_t capacity;
    size_t first;
} Stdout_tracker;

#define TRACKER_CAPACITY 10

extern bool TRACKING_STARTED;
extern Stdout_tracker STDOUT_TRACKER;

void tracker_push(Stdout_tracker* tracker, uint8_t ch);
void tracker_print(Stdout_tracker* tracker);
Stdout_tracker make_tracker();
void track_output(char ch);
int debug_enabled();
int debug_enable();
int debug_disable();
int debug(uint8_t* array, char* bf, size_t* ptr, size_t* idx, int cell_count);
