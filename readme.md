# Some Brainfuck tools

## What
* Compiler
* Interpreter
* Debugger

### Flags
```bash
-c = compile
-i = interpret
-d = debug
```
### How to
* Source has to always be right after mode flag
* Output can be anywhere but should only exist when compiling
```
bfc -c <source.b> <output>
bfc -i <source.b>
bfc -d <source.b>
```

## Requirements
* Compiling requires ```./boilerplate/BASEPROGRAM.c``` to exist relative to root dir
* [GCC](https://gcc.gnu.org/) of some modern standard (Modes other than compile work without)
* [CMake](https://cmake.org/) and [Make](https://www.gnu.org/software/make/) recommended

## Debugger
* Displays data array 5 cells to each side from data pointer
* Displays current instruction stream 10 instructions ahead
* Allows moving pointer around and assigning new values to cells
### Debugger commands
```
<byte> <n>      = Assign value <n> to byte at current data pointer location
<ptr> <n>       = Assign value <n> to data pointer (Move pointer)
<offset> <n>    = Assign offset <n> to data array display without moving pointer
<empty>         = Run next instruction in instruction stream
```
