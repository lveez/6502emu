// #ifndef 6502_H
// #define 6502_H

#include <stdint.h>

/* datatypes */

typedef struct Status {
    uint8_t negative;
    uint8_t overflow;
    uint8_t brk;
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

typedef enum {
    /* load*/
    LDA,
    LDX,
    LDY,
    STA,
    STX,
    STY,

    /* transfer */
    TAX,
    TAY,
    TSX,
    TXA,
    TXS,
    TYA,

    /* stack */
    PHA,
    PHP,
    PLA,
    PLP,

    /* shift */
    ASL,
    LSR,
    ROL,
    ROR,

    /* logical */
    AND,
    BIT,
    EOR,
    ORA,

    /* arithmetic */
    ADC,
    CMP,
    CPX,
    CPY,
    SBC,

    /* increment */
    DEC,
    DEX,
    DEY,
    INC,
    INX,
    INY,

    /* control */
    BRK,
    JMP,
    JSR,
    RTI,
    RTS,

    /* branch */
    BCC,
    BCS,
    BEQ,
    BMI,
    BNE,
    BPL,
    BVC,
    BVS,

    /* flags */
    CLC,
    CLD,
    CLI,
    CLV,
    SEC,
    SED,
    SEI,

    NOP,
} Operation;

typedef enum {
    Implied,
    Accumulator,
    Immediate,
    Absolute,
    XAbsolute,
    YAbsolute,
    AbsoluteIndirect,
    ZeroPage,
    XZeroPage,
    YZeroPage,
    XZeroPageIndirect,
    ZeroPageIndirectY,
} AddressingMode;

typedef struct Instruction {
    Operation operation;
    AddressingMode addressing_mode;
} Instruction;

/* functions */

// #endif /* 6502_H */