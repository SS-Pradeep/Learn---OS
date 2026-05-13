// os_simulator.h improvements
#ifndef OS_SIMULATOR_H
#define OS_SIMULATOR_H

typedef enum { NEW, READY, RUNNING, WAITING, TERMINATED } ProcessState;

struct PCB {
    int pid;
    int priority;
    int program_counter;
    int registers[8];
    ProcessState state;
    int burst_time;
    int remaining_time;
    
};

// Represents the actual physical CPU
struct CPU {
    int pc;
    int registers[8];
    struct PCB* running_process; 
};

// Function prototypes - use pointers everywhere!
void context_switch(struct PCB* old_proc, struct PCB* new_proc);
void dispatcher(struct PCB* new_proc);
const char* state_to_string(ProcessState state);

#endif