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
    Relative,
} AddressingMode;

typedef struct Instruction {
    Operation operation;
    AddressingMode addressing_mode;
    uint16_t base_address;
} Instruction;

/* functions */

/* get the addresses*/

uint16_t GetImplied(CPU* cpu, Instruction* instruction);
uint16_t GetAccumulator(CPU* cpu, Instruction* instruction);
uint16_t GetImmediate(CPU* cpu, Instruction* instruction);
uint16_t GetAbsolute(CPU* cpu, Instruction* instruction);
uint16_t GetXAbsolute(CPU* cpu, Instruction* instruction);
uint16_t GetYAbsolute(CPU* cpu, Instruction* instruction);
uint16_t GetAbsoluteIndirect(CPU* cpu, Instruction* instruction);
uint16_t GetZeroPage(CPU* cpu, Instruction* instruction);
uint16_t GetXZeroPage(CPU* cpu, Instruction* instruction);
uint16_t GetYZeroPage(CPU* cpu, Instruction* instruction);
uint16_t GetXZeroPageIndirect(CPU* cpu, Instruction* instruction);
uint16_t GetZeroPageIndirectY(CPU* cpu, Instruction* instruction);
uint16_t GetRelative(CPU* cpu, Instruction* instruction);

/* instructions */
void ExecuteLDA();
void ExecuteLDX();
void ExecuteLDY();
void ExecuteSTA();
void ExecuteSTX();
void ExecuteSTY();
void ExecuteTAX();
void ExecuteTAY();
void ExecuteTSX();
void ExecuteTXA();
void ExecuteTXS();
void ExecuteTYA();
void ExecutePHA();
void ExecutePHP();
void ExecutePLA();
void ExecutePLP();
void ExecuteASL();
void ExecuteLSR();
void ExecuteROL();
void ExecuteROR();
void ExecuteAND();
void ExecuteBIT();
void ExecuteEOR();
void ExecuteORA();
void ExecuteADC();
void ExecuteCMP();
void ExecuteCPX();
void ExecuteCPY();
void ExecuteSBC();
void ExecuteDEC();
void ExecuteDEX();
void ExecuteDEY();
void ExecuteINC();
void ExecuteINX();
void ExecuteINY();
void ExecuteBRK();
void ExecuteJMP();
void ExecuteJSR();
void ExecuteRTI();
void ExecuteRTS();
void ExecuteBCC();
void ExecuteBCS();
void ExecuteBEQ();
void ExecuteBMI();
void ExecuteBNE();
void ExecuteBPL();
void ExecuteBVC();
void ExecuteBVS();
void ExecuteCLC();
void ExecuteCLD();
void ExecuteCLI();
void ExecuteCLV();
void ExecuteSEC();
void ExecuteSED();
void ExecuteSEI();
void ExecuteNOP();

// #endif /* 6502_H */