#include "structure.h"

/* utility functions */

uint8_t CheckPageCross(uint16_t base, uint8_t offset) {
    if (((base + offset) & 0xff) < (base & 0xff))
        return 1;
    return 0;
}

uint8_t StatusToInt(Status* status, uint8_t brk) {
    return (status->negative << 7) | (status->overflow << 6) |
           (1 << 5) | (brk << 4) | (status->decimal << 3) |
           (status->interrupt << 2) | (status->zero << 1) | (status->carry);
}

void StatusFromInt(Status* status, uint8_t status_int) {
    status->negative = (status_int >> 7) & 1;
    status->overflow = (status_int >> 6) & 1;
    status->brk = 0;
    status->decimal = (status_int >> 3) & 1;
    status->interrupt = (status_int >> 2) & 1;
    status->zero = (status_int >> 1) & 1;
    status->carry = status_int & 1;
}

uint8_t ConvertBCD(uint8_t byte) {
    return ((byte >> 4) * 10) + (byte & 0xf);
}

/* addressing */

uint16_t GetImplied(CPU* cpu) {
    cpu->registers.program_counter += 1;
    return 0;
}

uint16_t GetAccumulator(CPU* cpu) {
    cpu->registers.program_counter += 1;
    return 0;
}

uint16_t GetImmediate(CPU* cpu) {
    cpu->registers.program_counter += 2;
    return cpu->instruction.base_address + 1;
}

uint16_t GetAbsolute(CPU* cpu) {  // not sure
    cpu->registers.program_counter += 3;
    return *(uint16_t*)(cpu->memory + cpu->instruction.base_address + 1);
}

uint16_t GetXAbsolute(CPU* cpu) {
    cpu->registers.program_counter += 3;
    uint16_t address =
        *(uint16_t*)(cpu->memory + cpu->instruction.base_address + 1);

    cpu->instruction.page_cross = CheckPageCross(address, cpu->registers.x);
    return address + cpu->registers.x;
}

uint16_t GetYAbsolute(CPU* cpu) {
    cpu->registers.program_counter += 3;
    uint16_t address =
        *(uint16_t*)(cpu->memory + cpu->instruction.base_address + 1);

    cpu->instruction.page_cross = CheckPageCross(address, cpu->registers.y);
    return address + cpu->registers.y;
}

uint16_t GetAbsoluteIndirect(CPU* cpu) {
    cpu->registers.program_counter += 3;
    uint16_t pointer =
        *(uint16_t*)(cpu->memory + cpu->instruction.base_address + 1);
    return *(uint16_t*)(cpu->memory + pointer);
}

uint16_t GetZeroPage(CPU* cpu) {
    cpu->registers.program_counter += 2;
    return *(uint8_t*)(cpu->memory + cpu->instruction.base_address + 1);
}

uint16_t GetXZeroPage(CPU* cpu) {
    cpu->registers.program_counter += 2;
    uint8_t address = *(uint8_t*)(cpu->memory + cpu->instruction.base_address + 1);
    address += cpu->registers.x;
    return address;
}

uint16_t GetYZeroPage(CPU* cpu) {
    cpu->registers.program_counter += 2;
    uint8_t address = *(uint8_t*)(cpu->memory + cpu->instruction.base_address + 1);
    address += cpu->registers.y;
    return address;
}

uint16_t GetXZeroPageIndirect(CPU* cpu) {
    cpu->registers.program_counter += 2;
    uint8_t pointer = *(uint8_t*)(cpu->memory + cpu->instruction.base_address + 1);
    pointer += cpu->registers.x;
    return *(uint16_t*)(cpu->memory + pointer);
}

uint16_t GetZeroPageIndirectY(CPU* cpu) {
    cpu->registers.program_counter += 2;
    uint8_t pointer = *(uint8_t*)(cpu->memory + cpu->instruction.base_address + 1);
    uint16_t address = *(uint16_t*)(cpu->memory + pointer);

    cpu->instruction.page_cross = CheckPageCross(address, cpu->registers.y);
    return address + cpu->registers.y;
}

uint16_t GetRelative(CPU* cpu) {
    cpu->registers.program_counter += 2;
    // not sure offset can maybe be negative?
    int8_t offset = *(int8_t*)(cpu->memory + cpu->instruction.base_address + 1);
    return cpu->instruction.base_address + 2 + offset;
}

/* executing */

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
}

void ExecuteSTX(CPU* cpu, uint16_t address) {
    cpu->memory[address] = cpu->registers.x;
}

void ExecuteSTY(CPU* cpu, uint16_t address) {
    cpu->memory[address] = cpu->registers.y;
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
}

void ExecuteTYA(CPU* cpu, uint16_t address) {
    cpu->registers.accumulator = cpu->registers.y;

    /* flags */
    cpu->registers.status.negative = (cpu->registers.accumulator >> 7) & 1;
    cpu->registers.status.zero = !(cpu->registers.accumulator);
}

void ExecutePHA(CPU* cpu, uint16_t address) {
    cpu->memory[0x100 + cpu->registers.stack_pointer] =
        cpu->registers.accumulator;
    cpu->registers.stack_pointer -= 1;
}

void ExecutePHP(CPU* cpu, uint16_t address) {
    // not sure if brk flag is set? -> done in status to int function
    cpu->memory[0x100 + cpu->registers.stack_pointer] =
        StatusToInt(&cpu->registers.status, 1);
    cpu->registers.stack_pointer -= 1;
}

void ExecutePLA(CPU* cpu, uint16_t address) {
    cpu->registers.stack_pointer += 1;
    cpu->registers.accumulator =
        cpu->memory[0x100 + cpu->registers.stack_pointer];

    /* flags */
    cpu->registers.status.negative = (cpu->registers.accumulator >> 7) & 1;
    cpu->registers.status.zero = !(cpu->registers.accumulator);
}

void ExecutePLP(CPU* cpu, uint16_t address) {
    cpu->registers.stack_pointer += 1;
    StatusFromInt(&cpu->registers.status,
                  cpu->memory[0x100 + cpu->registers.stack_pointer]);
}

void ExecuteASL(CPU* cpu, uint16_t address) {
    if (cpu->instruction.addressing_mode == Accumulator) {
        cpu->registers.status.carry = (cpu->registers.accumulator >> 7) & 1;
        cpu->registers.accumulator = cpu->registers.accumulator << 1;

        /* flags */
        cpu->registers.status.negative = (cpu->registers.accumulator >> 7) & 1;
        cpu->registers.status.zero = !(cpu->registers.accumulator);

        return;
    }

    uint8_t value = cpu->memory[address];
    cpu->registers.status.carry = (value >> 7) & 1;
    value = value << 1;
    cpu->memory[address] = value;

    /* flags */
    cpu->registers.status.negative = (value >> 7) & 1;
    cpu->registers.status.zero = !(value);
}

void ExecuteLSR(CPU* cpu, uint16_t address) {
    if (cpu->instruction.addressing_mode == Accumulator) {
        cpu->registers.status.carry = (cpu->registers.accumulator) & 1;
        cpu->registers.accumulator = cpu->registers.accumulator >> 1;
        cpu->registers.accumulator &= 0b01111111;

        /* flags */
        cpu->registers.status.negative = 0;
        cpu->registers.status.zero = !(cpu->registers.accumulator);

        return;
    }

    uint8_t value = cpu->memory[address];
    cpu->registers.status.carry = value & 1;
    value = value >> 1;
    cpu->memory[address] = value;

    /* flags */
    cpu->registers.status.negative = 0;
    cpu->registers.status.zero = !(value);
}

void ExecuteROL(CPU* cpu, uint16_t address) {
    if (cpu->instruction.addressing_mode == Accumulator) {
        uint8_t old_carry = cpu->registers.status.carry;
        cpu->registers.status.carry = (cpu->registers.accumulator >> 7) & 1;
        cpu->registers.accumulator = cpu->registers.accumulator << 1;
        cpu->registers.accumulator |= old_carry;

        /* flags */
        cpu->registers.status.negative = (cpu->registers.accumulator >> 7) & 1;
        cpu->registers.status.zero = !(cpu->registers.accumulator);

        return;
    }

    uint8_t old_carry = cpu->registers.status.carry;
    uint8_t value = cpu->memory[address];
    cpu->registers.status.carry = (value >> 7) & 1;
    cpu->memory[address] = value << 1;
    cpu->memory[address] |= old_carry;

    /* flags */
    cpu->registers.status.negative = (cpu->memory[address] >> 7) & 1;
    cpu->registers.status.zero = !(cpu->memory[address]);
}

void ExecuteROR(CPU* cpu, uint16_t address) {
    if (cpu->instruction.addressing_mode == Accumulator) {
        uint8_t old_carry = cpu->registers.status.carry;
        cpu->registers.status.carry = (cpu->registers.accumulator) & 1;
        cpu->registers.accumulator = cpu->registers.accumulator >> 1;
        cpu->registers.accumulator |= (old_carry << 7);

        /* flags */
        cpu->registers.status.negative = (cpu->registers.accumulator >> 7) & 1;
        cpu->registers.status.zero = !(cpu->registers.accumulator);

        return;
    }

    uint8_t old_carry = cpu->registers.status.carry;
    uint8_t value = cpu->memory[address];
    cpu->registers.status.carry = value & 1;
    cpu->memory[address] = value >> 1;
    cpu->memory[address] |= (old_carry << 7);

    /* flags */
    cpu->registers.status.negative = (cpu->memory[address] >> 7) & 1;
    cpu->registers.status.zero = !(cpu->memory[address]);
}

void ExecuteAND(CPU* cpu, uint16_t address) {
    cpu->registers.accumulator = cpu->registers.accumulator & cpu->memory[address];
    cpu->registers.status.negative = (cpu->registers.accumulator >> 7) & 1;
    cpu->registers.status.zero = !(cpu->registers.accumulator);
}

void ExecuteBIT(CPU* cpu, uint16_t address) {
    cpu->registers.status.negative = (cpu->memory[address] >> 7) & 1;
    cpu->registers.status.overflow = (cpu->memory[address] >> 6) & 1;
    cpu->registers.status.zero = !(cpu->registers.accumulator & cpu->memory[address]);
}

void ExecuteEOR(CPU* cpu, uint16_t address) {
    cpu->registers.accumulator = cpu->registers.accumulator ^ cpu->memory[address];
    cpu->registers.status.negative = (cpu->registers.accumulator >> 7) & 1;
    cpu->registers.status.zero = !(cpu->registers.accumulator);
}

void ExecuteORA(CPU* cpu, uint16_t address) {
    cpu->registers.accumulator = cpu->registers.accumulator | cpu->memory[address];
    cpu->registers.status.negative = (cpu->registers.accumulator >> 7) & 1;
    cpu->registers.status.zero = !(cpu->registers.accumulator);
}

void ExecuteADC(CPU* cpu, uint16_t address) {
    uint8_t old_accumulator = cpu->registers.accumulator;

    if (cpu->registers.status.decimal) {
        cpu->registers.accumulator = ConvertBCD(cpu->registers.accumulator) +
                                     ConvertBCD(cpu->memory[address]) +
                                     cpu->registers.status.carry;
    } else {
        cpu->registers.accumulator = cpu->registers.accumulator +
                                     cpu->memory[address] +
                                     cpu->registers.status.carry;
    }

    uint16_t carry_check = old_accumulator + cpu->memory[address] + cpu->registers.status.carry;
    /* flags */
    if (cpu->registers.status.decimal)
        cpu->registers.status.carry = (carry_check > 0x99);
    else
        cpu->registers.status.carry = (carry_check > 0xff);
    cpu->registers.status.overflow = (!((old_accumulator ^ cpu->memory[address]) & 0x80) && ((old_accumulator ^ cpu->registers.accumulator) & 0x80));
    cpu->registers.status.negative = (cpu->registers.accumulator >> 7) & 1;
    cpu->registers.status.zero = !(cpu->registers.accumulator);
}

void ExecuteCMP(CPU* cpu, uint16_t address) {
    uint8_t result = cpu->registers.accumulator - cpu->memory[address];

    /* flags */
    cpu->registers.status.carry = (cpu->memory[address] <= cpu->registers.accumulator);
    cpu->registers.status.negative = (result >> 7) & 1;
    cpu->registers.status.zero = !(result);
}

void ExecuteCPX(CPU* cpu, uint16_t address) {
    uint8_t result = cpu->registers.x - cpu->memory[address];

    /* flags */
    cpu->registers.status.carry = (cpu->memory[address] <= cpu->registers.x);
    cpu->registers.status.negative = (result >> 7) & 1;
    cpu->registers.status.zero = !(result);
}

void ExecuteCPY(CPU* cpu, uint16_t address) {
    uint8_t result = cpu->registers.y - cpu->memory[address];

    /* flags */
    cpu->registers.status.carry = (cpu->memory[address] <= cpu->registers.y);
    cpu->registers.status.negative = (result >> 7) & 1;
    cpu->registers.status.zero = !(result);
}

void ExecuteSBC(CPU* cpu, uint16_t address) {
    uint8_t old_accumulator = cpu->registers.accumulator;

    if (cpu->registers.status.decimal) {
        cpu->registers.accumulator = ConvertBCD(cpu->registers.accumulator) -
                                     ConvertBCD(cpu->memory[address]) -
                                     !(cpu->registers.status.carry);
    } else {
        cpu->registers.accumulator = cpu->registers.accumulator -
                                     cpu->memory[address] -
                                     !(cpu->registers.status.carry);
    }

    uint16_t carry_check = old_accumulator - cpu->memory[address] - !(cpu->registers.status.carry);
    /* flags */
    cpu->registers.status.carry = (carry_check < 0x100);
    cpu->registers.status.overflow = (!((old_accumulator ^ ~(cpu->memory[address])) & 0x80) && ((old_accumulator ^ cpu->registers.accumulator) & 0x80));
    cpu->registers.status.negative = (cpu->registers.accumulator >> 7) & 1;
    cpu->registers.status.zero = !(cpu->registers.accumulator);
}

void ExecuteDEC(CPU* cpu, uint16_t address) {
    cpu->memory[address] -= 1;

    /* flags */
    cpu->registers.status.negative = (cpu->memory[address] >> 7) & 1;
    cpu->registers.status.zero = !(cpu->memory[address]);
}

void ExecuteDEX(CPU* cpu, uint16_t address) {
    cpu->registers.x -= 1;

    /* flags */
    cpu->registers.status.negative = (cpu->registers.x >> 7) & 1;
    cpu->registers.status.zero = !(cpu->registers.x);
}

void ExecuteDEY(CPU* cpu, uint16_t address) {
    cpu->registers.y -= 1;

    /* flags */
    cpu->registers.status.negative = (cpu->registers.y >> 7) & 1;
    cpu->registers.status.zero = !(cpu->registers.y);
}

void ExecuteINC(CPU* cpu, uint16_t address) {
    cpu->memory[address] += 1;

    /* flags */
    cpu->registers.status.negative = (cpu->memory[address] >> 7) & 1;
    cpu->registers.status.zero = !(cpu->memory[address]);
}

void ExecuteINX(CPU* cpu, uint16_t address) {
    cpu->registers.x += 1;

    /* flags */
    cpu->registers.status.negative = (cpu->registers.x >> 7) & 1;
    cpu->registers.status.zero = !(cpu->registers.x);
}

void ExecuteINY(CPU* cpu, uint16_t address) {
    cpu->registers.y += 1;

    /* flags */
    cpu->registers.status.negative = (cpu->registers.y >> 7) & 1;
    cpu->registers.status.zero = !(cpu->registers.y);
}

void ExecuteBRK(CPU* cpu, uint16_t address) {
    // need to increment program counter one more as brk has 1 extra byte for debug
    cpu->registers.program_counter += 1;
    cpu->memory[0x100 + cpu->registers.stack_pointer] = (cpu->instruction.base_address + 2) >> 8 & 0xff;
    cpu->registers.stack_pointer -= 1;
    cpu->memory[0x100 + cpu->registers.stack_pointer] = (cpu->instruction.base_address + 2) & 0xff;
    cpu->registers.stack_pointer -= 1;
    // cpu->registers.status.interrupt = 1;
    // not sure if interrupt is actually set?
    cpu->memory[0x100 + cpu->registers.stack_pointer] = StatusToInt(&cpu->registers.status, 1);
    cpu->registers.stack_pointer -= 1;

    cpu->registers.status.interrupt = 1;

    cpu->registers.program_counter = *(uint16_t*)(cpu->memory + 0xfffe);
}

void ExecuteJMP(CPU* cpu, uint16_t address) {
    cpu->registers.program_counter = address;
}

void ExecuteJSR(CPU* cpu, uint16_t address) {
    cpu->memory[0x100 + cpu->registers.stack_pointer] = (cpu->instruction.base_address + 2) >> 8 & 0xff;
    cpu->registers.stack_pointer -= 1;
    cpu->memory[0x100 + cpu->registers.stack_pointer] = (cpu->instruction.base_address + 2) & 0xff;
    cpu->registers.stack_pointer -= 1;

    cpu->registers.program_counter = address;
}

void ExecuteRTI(CPU* cpu, uint16_t address) {
    cpu->registers.stack_pointer += 1;
    StatusFromInt(&cpu->registers.status, cpu->memory[0x100 + cpu->registers.stack_pointer]);
    cpu->registers.stack_pointer += 1;
    uint16_t lo = cpu->memory[0x100 + cpu->registers.stack_pointer];
    cpu->registers.stack_pointer += 1;
    uint16_t hi = cpu->memory[0x100 + cpu->registers.stack_pointer];
    cpu->registers.program_counter = (hi << 8) | lo;
}

void ExecuteRTS(CPU* cpu, uint16_t address) {
    cpu->registers.stack_pointer += 1;
    uint16_t lo = cpu->memory[0x100 + cpu->registers.stack_pointer];
    cpu->registers.stack_pointer += 1;
    uint16_t hi = cpu->memory[0x100 + cpu->registers.stack_pointer];
    cpu->registers.program_counter = (hi << 8) | lo;
    cpu->registers.program_counter += 1;
}

void ExecuteBCC(CPU* cpu, uint16_t address) {
    if (cpu->registers.status.carry == 0)
        cpu->registers.program_counter = address;
}

void ExecuteBCS(CPU* cpu, uint16_t address) {
    if (cpu->registers.status.carry == 1)
        cpu->registers.program_counter = address;
}

void ExecuteBEQ(CPU* cpu, uint16_t address) {
    if (cpu->registers.status.zero == 1)
        cpu->registers.program_counter = address;
}

void ExecuteBMI(CPU* cpu, uint16_t address) {
    if (cpu->registers.status.negative == 1)
        cpu->registers.program_counter = address;
}

void ExecuteBNE(CPU* cpu, uint16_t address) {
    if (cpu->registers.status.zero == 0)
        cpu->registers.program_counter = address;
}

void ExecuteBPL(CPU* cpu, uint16_t address) {
    if (cpu->registers.status.negative == 0)
        cpu->registers.program_counter = address;
}

void ExecuteBVC(CPU* cpu, uint16_t address) {
    if (cpu->registers.status.overflow == 0)
        cpu->registers.program_counter = address;
}

void ExecuteBVS(CPU* cpu, uint16_t address) {
    if (cpu->registers.status.overflow == 1)
        cpu->registers.program_counter = address;
}

void ExecuteCLC(CPU* cpu, uint16_t address) {
    cpu->registers.status.carry = 0;
}

void ExecuteCLD(CPU* cpu, uint16_t address) {
    cpu->registers.status.decimal = 0;
}

void ExecuteCLI(CPU* cpu, uint16_t address) {
    cpu->registers.status.interrupt = 0;
}

void ExecuteCLV(CPU* cpu, uint16_t address) {
    cpu->registers.status.overflow = 0;
}

void ExecuteSEC(CPU* cpu, uint16_t address) {
    cpu->registers.status.carry = 1;
}

void ExecuteSED(CPU* cpu, uint16_t address) {
    cpu->registers.status.decimal = 1;
}

void ExecuteSEI(CPU* cpu, uint16_t address) {
    cpu->registers.status.interrupt = 1;
}

void ExecuteNOP(CPU* cpu, uint16_t address) {
    return;
}
