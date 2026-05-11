#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

// Defining the process states
typedef enum {
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
} ProcessState;

struct PCB {
    int pid; // Process ID
    int priority; // Process priority
    int program_counter; // Program counter to keep track of the next instruction
    int registers[8]; // Simulating 8 general-purpose registers
    ProcessState state; // Current state of the process
};

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

int main() {
    struct PCB process_table[3];

    // Initializing the process table with some processes
    process_table[0].pid = 1;
    process_table[0].priority = 5;
    process_table[0].program_counter = 0;
    process_table[0].state = NEW;
    memset(process_table[0].registers, 0, sizeof(process_table[0].registers));
    print_pcb(&process_table[0]);

    process_table[1].pid = 2;
    process_table[1].priority = 3;
    process_table[1].program_counter = 0;
    process_table[1].state = READY;
    memset(process_table[1].registers, 0, sizeof(process_table[1].registers));
    print_pcb(&process_table[1]);

    process_table[2].pid = 3;
    process_table[2].priority = 1;
    process_table[2].program_counter = 0;
    process_table[2].state = WAITING;
    memset(process_table[2].registers, 0, sizeof(process_table[2].registers));
    print_pcb(&process_table[2]);

    return 0;
}

