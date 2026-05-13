#include <stdio.h>
#include <unistd.h>
#include "os_simulator.h"

// Reference the unified hardware state defined in your system
extern struct CPU hardware_cpu;

void dispatcher(struct PCB* next_proc) {
    if (next_proc == NULL) {
        printf("[Dispatcher] Idle Task: No process to dispatch.\n");
        return;
    }

    // 1. Simulate Kernel Overhead
    // In a real OS, this involves switching page tables and kernel stacks
    printf("[Dispatcher] Switching context to PID %d...\n", next_proc->pid);
    printf("[Dispatcher] Loading page tables and flushing TLB...\n");
    usleep(500000); // 0.5s simulated overhead

    // 2. Map the PCB state to the Hardware registers
    // This is the "Restore" phase of the context switch
    hardware_cpu.pc = next_proc->program_counter;
    for (int i = 0; i < 8; i++) {
        hardware_cpu.registers[i] = next_proc->registers[i];
    }

    // 3. Finalize State
    next_proc->state = RUNNING;
    hardware_cpu.running_process = next_proc;

    printf("[Dispatcher] CPU is now executing PID %d at PC: %d\n", 
           next_proc->pid, hardware_cpu.pc);
}x