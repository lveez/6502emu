#ifndef RUN_H
#define RUN_H

#include "stdio.h"
#include "structure.h"

void Init(CPU* cpu);
uint8_t LoadROM(CPU* cpu, const char* filename, uint16_t base_address);
void Step(CPU* cpu, uint8_t print_debug, FILE* debug_file);
void Steps(CPU* cpu, uint32_t num_steps, uint8_t print_debug, FILE* debug_file);
void Run(CPU* cpu, uint8_t print_debug, FILE* debug_file);

#endif /* RUN_H */