#include "run.h"

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