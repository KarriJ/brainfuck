#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


typedef struct 
{
    uint8_t* array;
    size_t capacity;
    size_t first;
    size_t count;
} Stdout_tracker;

#define TRACKER_CAPACITY 25

extern bool TRACKING_STARTED;
extern Stdout_tracker STDOUT_TRACKER;

void tracker_push(Stdout_tracker* tracker, uint8_t val);
void tracker_print(Stdout_tracker* tracker);
Stdout_tracker make_tracker();
void track_output(uint8_t val);