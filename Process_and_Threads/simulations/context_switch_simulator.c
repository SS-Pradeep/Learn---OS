#include <stdio.h>
#include <unistd.h>
#include "os_simulator.h"

// We use 'extern' to reference the hardware defined in our header
// This ensures we aren't creating a 'fake' CPU inside this file
extern struct CPU hardware_cpu; 

void context_switch(struct PCB* old_process, struct PCB* new_process) {
    // 1. Safety Check
    if (new_process == NULL) return;
    
    // 2. Save the OLD process state (CPU -> PCB)
    if (old_process != NULL) {
        printf("[Context Switch] Saving state for PID: %d\n", old_process->pid);
        
        old_process->program_counter = hardware_cpu.pc;
        for(int i = 0; i < 8; i++) {
            old_process->registers[i] = hardware_cpu.registers[i];
        }
        
        // Mark as READY so it can be scheduled again later
        old_process->state = READY; 
    }

    // 3. Load the NEW process state (PCB -> CPU)
    printf("[Context Switch] Loading state for PID: %d\n", new_process->pid);
    
    hardware_cpu.pc = new_process->program_counter;
    for(int i = 0; i < 8; i++) {
        hardware_cpu.registers[i] = new_process->registers[i];
    }
    
    // Update the hardware's pointer to the currently running process
    hardware_cpu.running_process = new_process;
    new_process->state = RUNNING;

    printf("[Context Switch] Switch complete. PC is now at %d\n", hardware_cpu.pc);
}