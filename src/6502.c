#include "6502.h"

inline uint8_t CheckPageCross(uint16_t base, uint8_t offset) {
    if (((base + offset) & 0xff) < (base & 0xff))
        return 1;
    return 0;
}

uint16_t GetImplied(CPU* cpu, Instruction* instruction) {
    return 0;
}

uint16_t GetAccumulator(CPU* cpu, Instruction* instruction) {
    return 0;
}

uint16_t GetImmediate(CPU* cpu, Instruction* instruction) {
    return instruction->base_address + 1;
}

uint16_t GetAbsolute(CPU* cpu, Instruction* instruction) {  // not sure
    return *(uint16_t*)(cpu->memory + instruction->base_address + 1);
}

uint16_t GetXAbsolute(CPU* cpu, Instruction* instruction) {
    uint16_t address =
        *(uint16_t*)(cpu->memory + instruction->base_address + 1);

    instruction->page_cross = CheckPageCross(address, cpu->registers.x);
    return address + cpu->registers.x;
}

uint16_t GetYAbsolute(CPU* cpu, Instruction* instruction) {
    uint16_t address =
        *(uint16_t*)(cpu->memory + instruction->base_address + 1);

    instruction->page_cross = CheckPageCross(address, cpu->registers.y);
    return address + cpu->registers.y;
}

uint16_t GetAbsoluteIndirect(CPU* cpu, Instruction* instruction) {
    uint16_t pointer =
        *(uint16_t*)(cpu->memory + instruction->base_address + 1);
    return *(uint16_t*)(cpu->memory + pointer);
}

uint16_t GetZeroPage(CPU* cpu, Instruction* instruction) {
    return *(uint8_t*)(cpu->memory + instruction->base_address + 1);
}

uint16_t GetXZeroPage(CPU* cpu, Instruction* instruction) {
    uint16_t address = *(uint8_t*)(cpu->memory + instruction->base_address + 1);
    return (address + cpu->registers.x) % 0xff;
}

uint16_t GetYZeroPage(CPU* cpu, Instruction* instruction) {
    uint16_t address = *(uint8_t*)(cpu->memory + instruction->base_address + 1);
    return (address + cpu->registers.x) % 0xff;
}

uint16_t GetXZeroPageIndirect(CPU* cpu, Instruction* instruction) {
    uint16_t pointer = *(uint8_t*)(cpu->memory + instruction->base_address + 1);
    pointer += cpu->registers.x;
    return *(uint16_t*)(cpu->memory + pointer);
}

uint16_t GetZeroPageIndirectY(CPU* cpu, Instruction* instruction) {
    uint16_t pointer = *(uint8_t*)(cpu->memory + instruction->base_address + 1);
    uint16_t address = *(uint16_t*)(cpu->memory + pointer);

    instruction->page_cross = CheckPageCross(address, cpu->registers.y);
    return address + cpu->registers.y;
}

uint16_t GetRelative(CPU* cpu, Instruction* instruction) {
    // make sure pc is set right
    uint16_t offset = *(uint8_t*)(cpu->memory + instruction->base_address + 1);
    return cpu->registers.program_counter + offset;
}

void ExecuteLDA(CPU* cpu, uint16_t address) {
    cpu->registers.accumulator = cpu->memory[address];

    /* flags */
    cpu->registers.status.negative = (cpu->registers.accumulator >> 7) & 1;
    cpu->registers.status.zero = !(cpu->registers.accumulator);
}

void ExecuteLDX(CPU* cpu, uint16_t address) {
    cpu->registers.x = cpu->memory[address];

    /* flags */
    cpu->registers.status.negative = (cpu->registers.x >> 7) & 1;
    cpu->registers.status.zero = !(cpu->registers.x);
}

void ExecuteLDY(CPU* cpu, uint16_t address) {
    cpu->registers.y = cpu->memory[address];

    /* flags */
    cpu->registers.status.negative = (cpu->registers.y >> 7) & 1;
    cpu->registers.status.zero = !(cpu->registers.y);
}

void ExecuteSTA(CPU* cpu, uint16_t address) {
    cpu->memory[address] = cpu->registers.accumulator;

    /* flags */
    cpu->registers.status.negative = (cpu->registers.accumulator >> 7) & 1;
    cpu->registers.status.zero = !(cpu->registers.accumulator);
}

void ExecuteSTX(CPU* cpu, uint16_t address) {
    cpu->memory[address] = cpu->registers.x;

    /* flags */
    cpu->registers.status.negative = (cpu->registers.x >> 7) & 1;
    cpu->registers.status.zero = !(cpu->registers.x);
}

void ExecuteSTY(CPU* cpu, uint16_t address) {
    cpu->memory[address] = cpu->registers.y;

    /* flags */
    cpu->registers.status.negative = (cpu->registers.y >> 7) & 1;
    cpu->registers.status.zero = !(cpu->registers.y);
}

void ExecuteTAX(CPU* cpu, uint16_t address) {
    cpu->registers.x = cpu->registers.accumulator;

    /* flags */
    cpu->registers.status.negative = (cpu->registers.x >> 7) & 1;
    cpu->registers.status.zero = !(cpu->registers.x);
}

void ExecuteTAY(CPU* cpu, uint16_t address) {
    cpu->registers.y = cpu->registers.accumulator;

    /* flags */
    cpu->registers.status.negative = (cpu->registers.y >> 7) & 1;
    cpu->registers.status.zero = !(cpu->registers.y);
}

void ExecuteTSX(CPU* cpu, uint16_t address) {
    cpu->registers.x = cpu->registers.stack_pointer;

    /* flags */
    cpu->registers.status.negative = (cpu->registers.x >> 7) & 1;
    cpu->registers.status.zero = !(cpu->registers.x);
}

void ExecuteTXA(CPU* cpu, uint16_t address) {
    cpu->registers.accumulator = cpu->registers.x;

    /* flags */
    cpu->registers.status.negative = (cpu->registers.accumulator >> 7) & 1;
    cpu->registers.status.zero = !(cpu->registers.accumulator);
}

void ExecuteTXS(CPU* cpu, uint16_t address) {
    cpu->registers.stack_pointer = cpu->registers.x;

    /* flags */
    cpu->registers.status.negative = (cpu->registers.stack_pointer >> 7) & 1;
    cpu->registers.status.zero = !(cpu->registers.stack_pointer);
}

void ExecuteTYA(CPU* cpu, uint16_t address) {
    cpu->registers.accumulator = cpu->registers.y;

    /* flags */
    cpu->registers.status.negative = (cpu->registers.accumulator >> 7) & 1;
    cpu->registers.status.zero = !(cpu->registers.accumulator);
}

void ExecutePHA(CPU* cpu, uint16_t address) {}

void ExecutePHP(CPU* cpu, uint16_t address) {}

void ExecutePLA(CPU* cpu, uint16_t address) {}

void ExecutePLP(CPU* cpu, uint16_t address) {}

void ExecuteASL(CPU* cpu, uint16_t address) {}

void ExecuteLSR(CPU* cpu, uint16_t address) {}

void ExecuteROL(CPU* cpu, uint16_t address) {}

void ExecuteROR(CPU* cpu, uint16_t address) {}

void ExecuteAND(CPU* cpu, uint16_t address) {}

void ExecuteBIT(CPU* cpu, uint16_t address) {}

void ExecuteEOR(CPU* cpu, uint16_t address) {}

void ExecuteORA(CPU* cpu, uint16_t address) {}

void ExecuteADC(CPU* cpu, uint16_t address) {}

void ExecuteCMP(CPU* cpu, uint16_t address) {}

void ExecuteCPX(CPU* cpu, uint16_t address) {}

void ExecuteCPY(CPU* cpu, uint16_t address) {}

void ExecuteSBC(CPU* cpu, uint16_t address) {}

void ExecuteDEC(CPU* cpu, uint16_t address) {}

void ExecuteDEX(CPU* cpu, uint16_t address) {}

void ExecuteDEY(CPU* cpu, uint16_t address) {}

void ExecuteINC(CPU* cpu, uint16_t address) {}

void ExecuteINX(CPU* cpu, uint16_t address) {}

void ExecuteINY(CPU* cpu, uint16_t address) {}

void ExecuteBRK(CPU* cpu, uint16_t address) {}

void ExecuteJMP(CPU* cpu, uint16_t address) {}

void ExecuteJSR(CPU* cpu, uint16_t address) {}

void ExecuteRTI(CPU* cpu, uint16_t address) {}

void ExecuteRTS(CPU* cpu, uint16_t address) {}

void ExecuteBCC(CPU* cpu, uint16_t address) {}

void ExecuteBCS(CPU* cpu, uint16_t address) {}

void ExecuteBEQ(CPU* cpu, uint16_t address) {}

void ExecuteBMI(CPU* cpu, uint16_t address) {}

void ExecuteBNE(CPU* cpu, uint16_t address) {}

void ExecuteBPL(CPU* cpu, uint16_t address) {}

void ExecuteBVC(CPU* cpu, uint16_t address) {}

void ExecuteBVS(CPU* cpu, uint16_t address) {}

void ExecuteCLC(CPU* cpu, uint16_t address) {}

void ExecuteCLD(CPU* cpu, uint16_t address) {}

void ExecuteCLI(CPU* cpu, uint16_t address) {}

void ExecuteCLV(CPU* cpu, uint16_t address) {}

void ExecuteSEC(CPU* cpu, uint16_t address) {}

void ExecuteSED(CPU* cpu, uint16_t address) {}

void ExecuteSEI(CPU* cpu, uint16_t address) {}

void ExecuteNOP(CPU* cpu, uint16_t address) {}
