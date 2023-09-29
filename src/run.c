#include "run.h"

#include "stdio.h"
#include "string.h"

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
        return 1;
    }

    /* get file size */
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (base_address + size > 0x10000) {
        printf("LoadROM: ROM file (%d bytes) is too large for the base address selected.\n", size);
        return 1;
    }

    size_t bytes_read = fread(cpu->memory + base_address, size, 1, file);
    if (bytes_read != 1) {
        perror("LoadROM: Error reading from ROM file,\n");
        return 1;
    }

    printf("LoadROM: %s (%d bytes) successfully loaded at address 0x%04x.\n", filename, size, base_address);

    /* program counter initializiation */
    cpu->registers.program_counter = *(uint16_t*)(cpu->memory + 0xfffc);
    printf("CPU: Program counter initialized to 0x%04x\n", cpu->registers.program_counter);

    return 0;
}