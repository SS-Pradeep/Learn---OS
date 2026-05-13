#include <stdio.h>
#include <stdlib.h>
#include "os_simulator.h"

void print_pcb(struct PCB* pcb);

// Simulation components
void context_switch(struct PCB* old_proc, struct PCB* new_proc);
void dispatcher(struct PCB* old_proc, struct PCB* new_proc);

int main () {

    // Process List
    struct PCB processes[3] = {
        {1, 1, 0, {0}, READY, 10, 10, 0},
        {2, 1, 0, {0}, READY, 15, 15, 0},
        {3, 1, 0, {0}, READY, 20, 20, 0}
    };

    printf("Initial Process Table:\n");

    for(int i = 0; i < 3; i++) {
        print_pcb(&processes[i]);
    }

    struct PCB* current_process = NULL;

    // FCFS Scheduling
    for(int i = 0; i < 3; i++) {

        struct PCB* next_process = &processes[i];

        // Context Switch
        context_switch(current_process, next_process);

        dispatcher(current_process, next_process);

        current_process = next_process;

        printf("\n[FCFS] Running PID %d\n",
               next_process->pid);

        // Execute FULL burst time
        while(next_process->remaining_time > 0) {

            next_process->program_counter++;

            next_process->remaining_time--;

            printf("PID %d executing... Remaining: %d\n",
                   next_process->pid,
                   next_process->remaining_time);
        }

        // Terminate Process
        next_process->state = TERMINATED;

        printf("Process %d Finished.\n",
               next_process->pid);
    }

    printf("\nAll processes have completed execution.\n");

    return 0;
}