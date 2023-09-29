#include "run.h"

int main(int argc, char** argv) {
    CPU cpu;
    Init(&cpu);
    if (!LoadROM(&cpu, "bin/6502_functional_test.bin", 0))
        return -1;
    cpu.registers.program_counter = 0x400;
    Run(&cpu, 0);
    return 0;
}