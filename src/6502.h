#ifndef 6502_H
#define 6502_H

#include <stdint.h>

/* datatypes */

typedef struct Status {
    uint8_t negative;
    uint8_t overflow;
    uint8_t break;
    uint8_t decimal;
    uint8_t interrupt;
    uint8_t zero;
    uint8_t carry;
} Status;

typedef struct Registers {
    uint8_t accumulator;
    uint8_t x;
    uint8_t y;
    uint16_t program_counter;
    uint8_t stack_pointer;
    Status status;
} Registers;

typedef struct CPU {
    Registers registers;
    uint8_t memory[0xffff];
} CPU;

/* functions */

#endif /* 6502_H */