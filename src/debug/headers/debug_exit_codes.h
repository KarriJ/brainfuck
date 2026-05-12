#pragma once


// The logic for the debugger requires more exit codes
// 1 -> errors that require a crash
// 0 -> No errors
// -1 Error that can be handled without a crash
// -2 Empty return / nothing was done

typedef enum
{
    EMPTY = -2,
    ERR = -1,
    NO_ERR = 0,
    FATAL_ERR = 1
} Debugger_exit;
