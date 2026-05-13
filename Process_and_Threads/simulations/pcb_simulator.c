#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include "os_simulator.h"

const char* state_to_string(ProcessState state) {
    switch(state) {
        case NEW: return "NEW";
        case READY: return "READY";
        case RUNNING: return "RUNNING";
        case WAITING: return "WAITING";
        case TERMINATED: return "TERMINATED";
        default: return "UNKNOWN";
    }
    
}

void print_pcb(struct PCB* pcb) {
    printf("PID: %d, Priority: %d, Program Counter: %d, State: %s\n", 
           pcb->pid, pcb->priority, pcb->program_counter, state_to_string(pcb->state));
}


