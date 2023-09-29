#include "run.h"

int main(int argc, char** argv) {
    CPU cpu;
    Init(&cpu);
    if (!LoadROM(&cpu, "bin/6502_functional_test.bin", 0))
        return -1;
    return 0;
}