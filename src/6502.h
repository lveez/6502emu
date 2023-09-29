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
    uint8_t page_cross;
} Instruction;

typedef struct CPU {
    Registers registers;
    uint8_t memory[0xffff];
    Instruction instruction;
} CPU;

/* functions */

/* get the addresses*/

uint16_t GetImplied(CPU* cpu);
uint16_t GetAccumulator(CPU* cpu);
uint16_t GetImmediate(CPU* cpu);
uint16_t GetAbsolute(CPU* cpu);
uint16_t GetXAbsolute(CPU* cpu);
uint16_t GetYAbsolute(CPU* cpu);
uint16_t GetAbsoluteIndirect(CPU* cpu);
uint16_t GetZeroPage(CPU* cpu);
uint16_t GetXZeroPage(CPU* cpu);
uint16_t GetYZeroPage(CPU* cpu);
uint16_t GetXZeroPageIndirect(CPU* cpu);
uint16_t GetZeroPageIndirectY(CPU* cpu);
uint16_t GetRelative(CPU* cpu);

/* instructions */
void ExecuteLDA(CPU* cpu, uint16_t address);
void ExecuteLDX(CPU* cpu, uint16_t address);
void ExecuteLDY(CPU* cpu, uint16_t address);
void ExecuteSTA(CPU* cpu, uint16_t address);
void ExecuteSTX(CPU* cpu, uint16_t address);
void ExecuteSTY(CPU* cpu, uint16_t address);
void ExecuteTAX(CPU* cpu, uint16_t address);
void ExecuteTAY(CPU* cpu, uint16_t address);
void ExecuteTSX(CPU* cpu, uint16_t address);
void ExecuteTXA(CPU* cpu, uint16_t address);
void ExecuteTXS(CPU* cpu, uint16_t address);
void ExecuteTYA(CPU* cpu, uint16_t address);
void ExecutePHA(CPU* cpu, uint16_t address);
void ExecutePHP(CPU* cpu, uint16_t address);
void ExecutePLA(CPU* cpu, uint16_t address);
void ExecutePLP(CPU* cpu, uint16_t address);
void ExecuteASL(CPU* cpu, uint16_t address, Instruction* instruction);
void ExecuteLSR(CPU* cpu, uint16_t address, Instruction* instruction);
void ExecuteROL(CPU* cpu, uint16_t address, Instruction* instruction);
void ExecuteROR(CPU* cpu, uint16_t address, Instruction* instruction);
void ExecuteAND(CPU* cpu, uint16_t address);
void ExecuteBIT(CPU* cpu, uint16_t address);
void ExecuteEOR(CPU* cpu, uint16_t address);
void ExecuteORA(CPU* cpu, uint16_t address);
void ExecuteADC(CPU* cpu, uint16_t address);
void ExecuteCMP(CPU* cpu, uint16_t address);
void ExecuteCPX(CPU* cpu, uint16_t address);
void ExecuteCPY(CPU* cpu, uint16_t address);
void ExecuteSBC(CPU* cpu, uint16_t address);
void ExecuteDEC(CPU* cpu, uint16_t address);
void ExecuteDEX(CPU* cpu, uint16_t address);
void ExecuteDEY(CPU* cpu, uint16_t address);
void ExecuteINC(CPU* cpu, uint16_t address);
void ExecuteINX(CPU* cpu, uint16_t address);
void ExecuteINY(CPU* cpu, uint16_t address);
void ExecuteBRK(CPU* cpu, uint16_t address);
void ExecuteJMP(CPU* cpu, uint16_t address);
void ExecuteJSR(CPU* cpu, uint16_t address);
void ExecuteRTI(CPU* cpu, uint16_t address);
void ExecuteRTS(CPU* cpu, uint16_t address);
void ExecuteBCC(CPU* cpu, uint16_t address);
void ExecuteBCS(CPU* cpu, uint16_t address);
void ExecuteBEQ(CPU* cpu, uint16_t address);
void ExecuteBMI(CPU* cpu, uint16_t address);
void ExecuteBNE(CPU* cpu, uint16_t address);
void ExecuteBPL(CPU* cpu, uint16_t address);
void ExecuteBVC(CPU* cpu, uint16_t address);
void ExecuteBVS(CPU* cpu, uint16_t address);
void ExecuteCLC(CPU* cpu, uint16_t address);
void ExecuteCLD(CPU* cpu, uint16_t address);
void ExecuteCLI(CPU* cpu, uint16_t address);
void ExecuteCLV(CPU* cpu, uint16_t address);
void ExecuteSEC(CPU* cpu, uint16_t address);
void ExecuteSED(CPU* cpu, uint16_t address);
void ExecuteSEI(CPU* cpu, uint16_t address);
void ExecuteNOP(CPU* cpu, uint16_t address);

// #endif /* 6502_H */