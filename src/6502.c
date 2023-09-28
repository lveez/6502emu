#include "6502.h"

uint16_t GetImplied(uint8_t* memory) {
    return 0;
}

uint16_t GetAccumulator(uint8_t* memory) {
    return 0;
}

uint16_t GetImmediate(uint8_t* memory) {
    return instruction_address + 1;
}

uint16_t GetAbsolute(uint8_t* memory) {  // not sure
    return *(uint16_t*)(memory + instruction_address + 1);
}

uint16_t GetXAbsolute(uint8_t* memory) {
    uint16_t address = *(uint16_t*)(memory + instruction_address + 1);
    return address + x_register;
}

uint16_t GetYAbsolute(uint8_t* memory) {
    uint16_t address = *(uint16_t*)(memory + instruction_address + 1);
    return address + y_register;
}

uint16_t GetAbsoluteIndirect(uint8_t* memory) {
    uint16_t pointer = *(uint16_t*)(memory + instruction_address + 1);
    return *(uint16_t*)(memory + pointer);
}

uint16_t GetZeroPage(uint8_t* memory) {
    return *(uint8_t*)(memory + instruction_address + 1);
}

uint16_t GetXZeroPage(uint8_t* memory) {
    // what happens if goes out of zero page?
    uint16_t address = *(uint8_t*)(memory + instruction_address + 1);
    return address + x_register;
}

uint16_t GetYZeroPage(uint8_t* memory) {
    uint16_t address = *(uint8_t*)(memory + instruction_address + 1);
    return address + y_register;
}

uint16_t GetXZeroPageIndirect(uint8_t* memory) {
    uint16_t pointer = *(uint8_t*)(memory + instruction_address + 1);
    pointer += x_register;
    return *(uint16_t*)(memory + pointer);
}

uint16_t GetZeroPageIndirectY(uint8_t* memory) {
    uint16_t pointer = *(uint8_t*)(memory + instruction_address + 1);
    uint16_t address = *(uint16_t*)(memory + pointer);
    return address + y_register;
}

uint16_t GetRelative(uint8_t* memory) {
    uint16_t offset = *(uint8_t*)(memory + instruction_address + 1);
    return program_counter + offset;
}
