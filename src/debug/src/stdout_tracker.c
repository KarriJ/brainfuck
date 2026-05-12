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

bool TRACKING_STARTED = false;
Stdout_tracker STDOUT_TRACKER;

void tracker_push(Stdout_tracker* tracker, uint8_t val)
{   
    if (tracker->count < tracker->capacity)
    {
        tracker->array[tracker->count] = val; 
        tracker->count++;
    }
    else  
    {
        tracker->array[tracker->first] = val;
        tracker->first = (tracker->first + 1) % tracker->capacity;
    }
}

void tracker_print(Stdout_tracker* tracker)
{
    for (int ii = 0; ii < tracker->capacity; ii++)
    {
        int idx = (tracker->first + ii) % tracker->capacity;
        putchar(tracker->array[idx]);
    }
}

Stdout_tracker make_tracker()
{
    static uint8_t array[TRACKER_CAPACITY + 1];
    array[TRACKER_CAPACITY] = '\0';

    return (Stdout_tracker) {
        array,
        TRACKER_CAPACITY,
        0
    };
}

void track_output(uint8_t val)
{
    if (TRACKING_STARTED == false)
    {
        STDOUT_TRACKER = make_tracker();
        TRACKING_STARTED = true;
    }

    tracker_push(&STDOUT_TRACKER, val);
}
