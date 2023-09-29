#ifndef RUN_H
#define RUN_H

#include "structure.h"

void Init(CPU* cpu);
uint8_t LoadROM(CPU* cpu, const char* filename, uint16_t base_address);
void Step(CPU* cpu, uint8_t print_debug);
void Steps(CPU* cpu, uint32_t num_steps, uint32_t clock_speed, uint8_t print_debug);
void Run(CPU* cpu, uint32_t clock_speed);

#endif /* RUN_H */