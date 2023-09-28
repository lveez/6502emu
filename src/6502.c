#include "6502.h"

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
    return address + cpu->registers.x;
}

uint16_t GetYAbsolute(CPU* cpu, Instruction* instruction) {
    uint16_t address =
        *(uint16_t*)(cpu->memory + instruction->base_address + 1);
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
    return address + cpu->registers.y;
}

uint16_t GetRelative(CPU* cpu, Instruction* instruction) {
    // make sure pc is set right
    uint16_t offset = *(uint8_t*)(cpu->memory + instruction->base_address + 1);
    return cpu->registers.program_counter + offset;
}

void ExecuteLDA() {}
void ExecuteLDX() {}
void ExecuteLDY() {}
void ExecuteSTA() {}
void ExecuteSTX() {}
void ExecuteSTY() {}
void ExecuteTAX() {}
void ExecuteTAY() {}
void ExecuteTSX() {}
void ExecuteTXA() {}
void ExecuteTXS() {}
void ExecuteTYA() {}
void ExecutePHA() {}
void ExecutePHP() {}
void ExecutePLA() {}
void ExecutePLP() {}
void ExecuteASL() {}
void ExecuteLSR() {}
void ExecuteROL() {}
void ExecuteROR() {}
void ExecuteAND() {}
void ExecuteBIT() {}
void ExecuteEOR() {}
void ExecuteORA() {}
void ExecuteADC() {}
void ExecuteCMP() {}
void ExecuteCPX() {}
void ExecuteCPY() {}
void ExecuteSBC() {}
void ExecuteDEC() {}
void ExecuteDEX() {}
void ExecuteDEY() {}
void ExecuteINC() {}
void ExecuteINX() {}
void ExecuteINY() {}
void ExecuteBRK() {}
void ExecuteJMP() {}
void ExecuteJSR() {}
void ExecuteRTI() {}
void ExecuteRTS() {}
void ExecuteBCC() {}
void ExecuteBCS() {}
void ExecuteBEQ() {}
void ExecuteBMI() {}
void ExecuteBNE() {}
void ExecuteBPL() {}
void ExecuteBVC() {}
void ExecuteBVS() {}
void ExecuteCLC() {}
void ExecuteCLD() {}
void ExecuteCLI() {}
void ExecuteCLV() {}
void ExecuteSEC() {}
void ExecuteSED() {}
void ExecuteSEI() {}
void ExecuteNOP() {}
