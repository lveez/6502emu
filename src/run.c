#include "run.h"

#include "string.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

/* instruction look up table */
Instruction instruction_table[0x100] = {
    {BRK, Implied, 0, 0},            // 00
    {ORA, XZeroPageIndirect, 0, 0},  // 01
    {0, 0, 0, 0},                    // 02
    {0, 0, 0, 0},                    // 03
    {0, 0, 0, 0},                    // 04
    {ORA, ZeroPage, 0, 0},           // 05
    {ASL, ZeroPage, 0, 0},           // 06
    {0, 0, 0, 0},                    // 07
    {PHP, Implied, 0, 0},            // 08
    {ORA, Immediate, 0, 0},          // 09
    {ASL, Accumulator, 0, 0},        // 0a
    {0, 0, 0, 0},                    // 0b
    {0, 0, 0, 0},                    // 0c
    {ORA, Absolute, 0, 0},           // 0d
    {ASL, Absolute, 0, 0},           // 0e
    {0, 0, 0, 0},                    // 0f
    {BPL, Relative, 0, 0},           // 10
    {ORA, ZeroPageIndirectY, 0, 0},  // 11
    {0, 0, 0, 0},                    // 12
    {0, 0, 0, 0},                    // 13
    {0, 0, 0, 0},                    // 14
    {ORA, XZeroPage, 0, 0},          // 15
    {ASL, XZeroPage, 0, 0},          // 16
    {0, 0, 0, 0},                    // 17
    {CLC, Implied, 0, 0},            // 18
    {ORA, YAbsolute, 0, 0},          // 19
    {0, 0, 0, 0},                    // 1a
    {0, 0, 0, 0},                    // 1b
    {0, 0, 0, 0},                    // 1c
    {ORA, XAbsolute, 0, 0},          // 1d
    {ASL, XAbsolute, 0, 0},          // 1e
    {0, 0, 0, 0},                    // 1f
    {JSR, Absolute, 0, 0},           // 20
    {AND, XZeroPageIndirect, 0, 0},  // 21
    {0, 0, 0, 0},                    // 22
    {0, 0, 0, 0},                    // 23
    {BIT, ZeroPage, 0, 0},           // 24
    {AND, ZeroPage, 0, 0},           // 25
    {ROL, ZeroPage, 0, 0},           // 26
    {0, 0, 0, 0},                    // 27
    {PLP, Implied, 0, 0},            // 28
    {AND, Immediate, 0, 0},          // 29
    {ROL, Accumulator, 0, 0},        // 2a
    {0, 0, 0, 0},                    // 2b
    {BIT, Absolute, 0, 0},           // 2c
    {AND, Absolute, 0, 0},           // 2d
    {ROL, Absolute, 0, 0},           // 2e
    {0, 0, 0, 0},                    // 2f
    {BMI, Relative, 0, 0},           // 30
    {AND, ZeroPageIndirectY, 0, 0},  // 31
    {0, 0, 0, 0},                    // 32
    {0, 0, 0, 0},                    // 33
    {0, 0, 0, 0},                    // 34
    {AND, XZeroPage, 0, 0},          // 35
    {ROL, XZeroPage, 0, 0},          // 36
    {0, 0, 0, 0},                    // 37
    {SEC, Implied, 0, 0},            // 38
    {AND, YAbsolute, 0, 0},          // 39
    {0, 0, 0, 0},                    // 3a
    {0, 0, 0, 0},                    // 3b
    {0, 0, 0, 0},                    // 3c
    {AND, XAbsolute, 0, 0},          // 3d
    {ROL, XAbsolute, 0, 0},          // 3e
    {0, 0, 0, 0},                    // 3f
    {RTI, Implied, 0, 0},            // 40
    {EOR, XZeroPageIndirect, 0, 0},  // 41
    {0, 0, 0, 0},                    // 42
    {0, 0, 0, 0},                    // 43
    {0, 0, 0, 0},                    // 44
    {EOR, ZeroPage, 0, 0},           // 45
    {LSR, ZeroPage, 0, 0},           // 46
    {0, 0, 0, 0},                    // 47
    {PHA, Implied, 0, 0},            // 48
    {EOR, Immediate, 0, 0},          // 49
    {LSR, Accumulator, 0, 0},        // 4a
    {0, 0, 0, 0},                    // 4b
    {JMP, Absolute, 0, 0},           // 4c
    {EOR, Absolute, 0, 0},           // 4d
    {LSR, Absolute, 0, 0},           // 4e
    {0, 0, 0, 0},                    // 4f
    {BVC, Relative, 0, 0},           // 50
    {EOR, ZeroPageIndirectY, 0, 0},  // 51
    {0, 0, 0, 0},                    // 52
    {0, 0, 0, 0},                    // 53
    {0, 0, 0, 0},                    // 54
    {EOR, XZeroPage, 0, 0},          // 55
    {LSR, XZeroPage, 0, 0},          // 56
    {0, 0, 0, 0},                    // 57
    {CLI, Implied, 0, 0},            // 58
    {EOR, YAbsolute, 0, 0},          // 59
    {0, 0, 0, 0},                    // 5a
    {0, 0, 0, 0},                    // 5b
    {0, 0, 0, 0},                    // 5c
    {EOR, XAbsolute, 0, 0},          // 5d
    {LSR, XAbsolute, 0, 0},          // 5e
    {0, 0, 0, 0},                    // 5f
    {RTS, Implied, 0, 0},            // 60
    {ADC, XZeroPageIndirect, 0, 0},  // 61
    {0, 0, 0, 0},                    // 62
    {0, 0, 0, 0},                    // 63
    {0, 0, 0, 0},                    // 64
    {ADC, ZeroPage, 0, 0},           // 65
    {ROR, ZeroPage, 0, 0},           // 66
    {0, 0, 0, 0},                    // 67
    {PLA, Implied, 0, 0},            // 68
    {ADC, Immediate, 0, 0},          // 69
    {ROR, Accumulator, 0, 0},        // 6a
    {0, 0, 0, 0},                    // 6b
    {JMP, AbsoluteIndirect, 0, 0},   // 6c
    {ADC, Absolute, 0, 0},           // 6d
    {ROR, Absolute, 0, 0},           // 6e
    {0, 0, 0, 0},                    // 6f
    {BVS, Relative, 0, 0},           // 70
    {ADC, ZeroPageIndirectY, 0, 0},  // 71
    {0, 0, 0, 0},                    // 72
    {0, 0, 0, 0},                    // 73
    {0, 0, 0, 0},                    // 74
    {ADC, XZeroPage, 0, 0},          // 75
    {ROR, XZeroPage, 0, 0},          // 76
    {0, 0, 0, 0},                    // 77
    {SEI, Implied, 0, 0},            // 78
    {ADC, YAbsolute, 0, 0},          // 79
    {0, 0, 0, 0},                    // 7a
    {0, 0, 0, 0},                    // 7b
    {0, 0, 0, 0},                    // 7c
    {ADC, XAbsolute, 0, 0},          // 7d
    {ROR, XAbsolute, 0, 0},          // 7e
    {0, 0, 0, 0},                    // 7f
    {0, 0, 0, 0},                    // 80
    {STA, XZeroPageIndirect, 0, 0},  // 81
    {0, 0, 0, 0},                    // 82
    {0, 0, 0, 0},                    // 83
    {STY, ZeroPage, 0, 0},           // 84
    {STA, ZeroPage, 0, 0},           // 85
    {STX, ZeroPage, 0, 0},           // 86
    {0, 0, 0, 0},                    // 87
    {DEY, Implied, 0, 0},            // 88
    {0, 0, 0, 0},                    // 89
    {TXA, Implied, 0, 0},            // 8a
    {0, 0, 0, 0},                    // 8b
    {STY, Absolute, 0, 0},           // 8c
    {STA, Absolute, 0, 0},           // 8d
    {STX, Absolute, 0, 0},           // 8e
    {0, 0, 0, 0},                    // 8f
    {BCC, Relative, 0, 0},           // 90
    {STA, ZeroPageIndirectY, 0, 0},  // 91
    {0, 0, 0, 0},                    // 92
    {0, 0, 0, 0},                    // 93
    {STY, XZeroPage, 0, 0},          // 94
    {STA, XZeroPage, 0, 0},          // 95
    {STX, YZeroPage, 0, 0},          // 96
    {0, 0, 0, 0},                    // 97
    {TYA, Implied, 0, 0},            // 98
    {STA, YAbsolute, 0, 0},          // 99
    {TXS, Implied, 0, 0},            // 9a
    {0, 0, 0, 0},                    // 9b
    {0, 0, 0, 0},                    // 9c
    {STA, XAbsolute, 0, 0},          // 9d
    {0, 0, 0, 0},                    // 9e
    {0, 0, 0, 0},                    // 9f
    {LDY, Immediate, 0, 0},          // a0
    {LDA, XZeroPageIndirect, 0, 0},  // a1
    {LDX, Immediate, 0, 0},          // a2
    {0, 0, 0, 0},                    // a3
    {LDY, ZeroPage, 0, 0},           // a4
    {LDA, ZeroPage, 0, 0},           // a5
    {LDX, ZeroPage, 0, 0},           // a6
    {0, 0, 0, 0},                    // a7
    {TAY, Implied, 0, 0},            // a8
    {LDA, Immediate, 0, 0},          // a9
    {TAX, Implied, 0, 0},            // aa
    {0, 0, 0, 0},                    // ab
    {LDY, Absolute, 0, 0},           // ac
    {LDA, Absolute, 0, 0},           // ad
    {LDX, Absolute, 0, 0},           // ae
    {0, 0, 0, 0},                    // af
    {BCS, Relative, 0, 0},           // b0
    {LDA, ZeroPageIndirectY, 0, 0},  // b1
    {0, 0, 0, 0},                    // b2
    {0, 0, 0, 0},                    // b3
    {LDY, XZeroPage, 0, 0},          // b4
    {LDA, XZeroPage, 0, 0},          // b5
    {LDX, YZeroPage, 0, 0},          // b6
    {0, 0, 0, 0},                    // b7
    {CLV, Implied, 0, 0},            // b8
    {LDA, YAbsolute, 0, 0},          // b9
    {TSX, Implied, 0, 0},            // ba
    {0, 0, 0, 0},                    // bb
    {LDY, XAbsolute, 0, 0},          // bc
    {LDA, XAbsolute, 0, 0},          // bd
    {LDX, YAbsolute, 0, 0},          // be
    {0, 0, 0, 0},                    // bf
    {CPY, Immediate, 0, 0},          // c0
    {CMP, XZeroPageIndirect, 0, 0},  // c1
    {0, 0, 0, 0},                    // c2
    {0, 0, 0, 0},                    // c3
    {CPY, ZeroPage, 0, 0},           // c4
    {CMP, ZeroPage, 0, 0},           // c5
    {DEC, ZeroPage, 0, 0},           // c6
    {0, 0, 0, 0},                    // c7
    {INY, Implied, 0, 0},            // c8
    {CMP, Immediate, 0, 0},          // c9
    {DEX, Implied, 0, 0},            // ca
    {0, 0, 0, 0},                    // cb
    {CPY, Absolute, 0, 0},           // cc
    {CMP, Absolute, 0, 0},           // cd
    {DEC, Absolute, 0, 0},           // ce
    {0, 0, 0, 0},                    // cf
    {BNE, Relative, 0, 0},           // d0
    {CMP, ZeroPageIndirectY, 0, 0},  // d1
    {0, 0, 0, 0},                    // d2
    {0, 0, 0, 0},                    // d3
    {0, 0, 0, 0},                    // d4
    {CMP, XZeroPage, 0, 0},          // d5
    {DEC, XZeroPage, 0, 0},          // d6
    {0, 0, 0, 0},                    // d7
    {CLD, Implied, 0, 0},            // d8
    {CMP, YAbsolute, 0, 0},          // d9
    {0, 0, 0, 0},                    // da
    {0, 0, 0, 0},                    // db
    {0, 0, 0, 0},                    // dc
    {CMP, XAbsolute, 0, 0},          // dd
    {DEC, XAbsolute, 0, 0},          // de
    {0, 0, 0, 0},                    // df
    {CPX, Immediate, 0, 0},          // e0
    {SBC, XZeroPageIndirect, 0, 0},  // e1
    {0, 0, 0, 0},                    // e2
    {0, 0, 0, 0},                    // e3
    {CPX, ZeroPage, 0, 0},           // e4
    {SBC, ZeroPage, 0, 0},           // e5
    {INC, ZeroPage, 0, 0},           // e6
    {0, 0, 0, 0},                    // e7
    {INX, Implied, 0, 0},            // e8
    {SBC, Immediate, 0, 0},          // e9
    {NOP, Implied, 0, 0},            // ea
    {0, 0, 0, 0},                    // eb
    {CPX, Absolute, 0, 0},           // ec
    {SBC, Absolute, 0, 0},           // ed
    {INC, Absolute, 0, 0},           // ee
    {0, 0, 0, 0},                    // ef
    {BEQ, Relative, 0, 0},           // f0
    {SBC, ZeroPageIndirectY, 0, 0},  // f1
    {0, 0, 0, 0},                    // f2
    {0, 0, 0, 0},                    // f3
    {0, 0, 0, 0},                    // f4
    {SBC, XZeroPage, 0, 0},          // f5
    {INC, XZeroPage, 0, 0},          // f6
    {0, 0, 0, 0},                    // f7
    {SED, Implied, 0, 0},            // f8
    {SBC, YAbsolute, 0, 0},          // f9
    {0, 0, 0, 0},                    // fa
    {0, 0, 0, 0},                    // fb
    {0, 0, 0, 0},                    // fc
    {SBC, XAbsolute, 0, 0},          // fd
    {INC, XAbsolute, 0, 0},          // fe
    {0, 0, 0, 0},                    // ff
};

/* function pointers to addressing mode functions */
uint16_t (*AddressingFunctions[13])(CPU* cpu) = {
    GetImplied,
    GetAccumulator,
    GetImmediate,
    GetAbsolute,
    GetXAbsolute,
    GetYAbsolute,
    GetAbsoluteIndirect,
    GetZeroPage,
    GetXZeroPage,
    GetYZeroPage,
    GetXZeroPageIndirect,
    GetZeroPageIndirectY,
    GetRelative,
};

/* function pointers to execute instructions */
void (*InstructionFunctions[56])(CPU* cpu, uint16_t address) = {
    ExecuteLDA,
    ExecuteLDX,
    ExecuteLDY,
    ExecuteSTA,
    ExecuteSTX,
    ExecuteSTY,
    ExecuteTAX,
    ExecuteTAY,
    ExecuteTSX,
    ExecuteTXA,
    ExecuteTXS,
    ExecuteTYA,
    ExecutePHA,
    ExecutePHP,
    ExecutePLA,
    ExecutePLP,
    ExecuteASL,
    ExecuteLSR,
    ExecuteROL,
    ExecuteROR,
    ExecuteAND,
    ExecuteBIT,
    ExecuteEOR,
    ExecuteORA,
    ExecuteADC,
    ExecuteCMP,
    ExecuteCPX,
    ExecuteCPY,
    ExecuteSBC,
    ExecuteDEC,
    ExecuteDEX,
    ExecuteDEY,
    ExecuteINC,
    ExecuteINX,
    ExecuteINY,
    ExecuteBRK,
    ExecuteJMP,
    ExecuteJSR,
    ExecuteRTI,
    ExecuteRTS,
    ExecuteBCC,
    ExecuteBCS,
    ExecuteBEQ,
    ExecuteBMI,
    ExecuteBNE,
    ExecuteBPL,
    ExecuteBVC,
    ExecuteBVS,
    ExecuteCLC,
    ExecuteCLD,
    ExecuteCLI,
    ExecuteCLV,
    ExecuteSEC,
    ExecuteSED,
    ExecuteSEI,
    ExecuteNOP,
};

/* addressing mode string look up table */
const char* addressing_mode_name[13] = {
    "Implied",
    "Accumulator",
    "Immediate",
    "Absolute",
    "XAbsolute",
    "YAbsolute",
    "AbsoluteIndirect",
    "ZeroPage",
    "XZeroPage",
    "YZeroPage",
    "XZeroPageIndirect",
    "ZeroPageIndirectY",
    "Relative",
};

const char* instruction_name[56] = {
    "LDA",
    "LDX",
    "LDY",
    "STA",
    "STX",
    "STY",
    "TAX",
    "TAY",
    "TSX",
    "TXA",
    "TXS",
    "TYA",
    "PHA",
    "PHP",
    "PLA",
    "PLP",
    "ASL",
    "LSR",
    "ROL",
    "ROR",
    "AND",
    "BIT",
    "EOR",
    "ORA",
    "ADC",
    "CMP",
    "CPX",
    "CPY",
    "SBC",
    "DEC",
    "DEX",
    "DEY",
    "INC",
    "INX",
    "INY",
    "BRK",
    "JMP",
    "JSR",
    "RTI",
    "RTS",
    "BCC",
    "BCS",
    "BEQ",
    "BMI",
    "BNE",
    "BPL",
    "BVC",
    "BVS",
    "CLC",
    "CLD",
    "CLI",
    "CLV",
    "SEC",
    "SED",
    "SEI",
    "NOP",
};

void Init(CPU* cpu) {
    memset(cpu->memory, 0, 0xffff);
    cpu->registers.accumulator = 0;
    cpu->registers.stack_pointer = 0;

    cpu->registers.status.brk = 0;
    cpu->registers.status.carry = 0;
    cpu->registers.status.decimal = 0;
    cpu->registers.status.interrupt = 0;
    cpu->registers.status.negative = 0;
    cpu->registers.status.overflow = 0;
    cpu->registers.status.zero = 0;

    cpu->registers.x = 0;
    cpu->registers.y = 0;
    cpu->registers.program_counter = 0;
}

uint8_t LoadROM(CPU* cpu, const char* filename, uint16_t base_address) {
    FILE* file;
    file = fopen(filename, "rb");

    if (file == NULL) {
        perror("LoadROM: Error opening ROM file.\n");
        return 0;
    }

    /* get file size */
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (base_address + size > 0x10000) {
        printf("LoadROM: ROM file (%d bytes) is too large for the base address selected.\n", size);
        return 0;
    }

    size_t bytes_read = fread(cpu->memory + base_address, size, 1, file);
    if (bytes_read != 1) {
        perror("LoadROM: Error reading from ROM file,\n");
        return 0;
    }

    printf("LoadROM: %s (%d bytes) successfully loaded at address 0x%04x.\n", filename, size, base_address);

    /* program counter initializiation */
    cpu->registers.program_counter = *(uint16_t*)(cpu->memory + 0xfffc);
    printf("CPU: Program counter initialized to 0x%04x\n", cpu->registers.program_counter);

    return 1;
}

void Step(CPU* cpu, uint8_t print_debug, FILE* debug_file) {
    cpu->instruction = instruction_table[cpu->memory[cpu->registers.program_counter]];
    cpu->instruction.base_address = cpu->registers.program_counter;

    if (ftell(debug_file) > 100000)
        fseek(debug_file, 0, SEEK_SET);

    if (print_debug) {
        fprintf(debug_file, "PC: 0x%04x, Ins: %s, AM: %s\n", cpu->registers.program_counter, instruction_name[cpu->instruction.operation], addressing_mode_name[cpu->instruction.addressing_mode]);
    }

    uint16_t effective_address = (*AddressingFunctions[cpu->instruction.addressing_mode])(cpu);

    if (print_debug) {
        fprintf(debug_file, "---\n");
        fprintf(debug_file, "Address: 0x%04x, Value: 0x%02x\n", effective_address, cpu->memory[effective_address]);
    }

    (*InstructionFunctions[cpu->instruction.operation])(cpu, effective_address);

    if (print_debug) {
        fprintf(debug_file, "---\n");
        fprintf(debug_file, "N | V | B | D | I | Z | C\n");
        fprintf(debug_file, "%d | %d | %d | %d | %d | %d | %d\n",
                cpu->registers.status.negative,
                cpu->registers.status.overflow,
                cpu->registers.status.brk,
                cpu->registers.status.decimal,
                cpu->registers.status.interrupt,
                cpu->registers.status.zero,
                cpu->registers.status.carry);
        fprintf(debug_file, "---\n");
        fprintf(debug_file, "X | Y | A | S\n");
        fprintf(debug_file, "%x | %x | %x | %x\n", cpu->registers.x, cpu->registers.y, cpu->registers.accumulator, cpu->registers.stack_pointer);
        fprintf(debug_file, "\n\n");
    }
}

void Steps(CPU* cpu, uint32_t num_steps, uint32_t clock_speed, uint8_t print_debug, FILE* debug_file) {
    for (uint64_t i = 0; i < num_steps; i++) {
        Step(cpu, print_debug, debug_file);
        Sleep(100);
    }
}

void Run(CPU* cpu, uint32_t clock_speed, uint8_t print_debug, FILE* debug_file) {
    uint16_t old_program_counter = 0;
    while (1) {
        old_program_counter = cpu->registers.program_counter;

        Step(cpu, print_debug, debug_file);

        if (cpu->registers.program_counter == old_program_counter) {
            /* dump stack */
            if (print_debug) {
                fprintf(debug_file, "STACK---\n");
                for (int i = cpu->registers.stack_pointer + 1; i < 0x100; i++) {
                    fprintf(debug_file, "%02x: %02x\n", i, cpu->memory[0x100 + i]);
                }
                fprintf(debug_file, "0x%04x\n", cpu->registers.program_counter);
            }
            printf("ERROR: Program counter stuck at 0x%04x.\nExiting...", cpu->registers.program_counter);
            return;
        }
    }
}
