#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "os_simulator.h"

int cpu_registers[8]; // Simulating CPU registers
int cpu_pc;

void context_switch(struct PCB* old_proc, struct PCB* new_proc) {
    // 1. Safety Check: Don't switch if the process is already running
    if (old_proc!=NULL &&old_proc == new_proc) {
        printf("[Context Switch] Process %d is already on the CPU. Skipping switch.\n", old_proc->pid);
        return;
    }


    // 2. SAVE STATE (CPU -> Old PCB)
    if (old_proc != NULL && old_proc->state == RUNNING) {
        old_proc->state = READY;
        for(int i=0; i<8; i++) old_proc->registers[i] = cpu_registers[i];
        old_proc->program_counter = cpu_pc;
        printf("[Save] PID %d state saved. PC was: %d\n", old_proc->pid, old_proc->program_counter);
    }

    // 3. DISPATCHER OVERHEAD (Simulate work)
    printf("[Context Switch] Swapping page tables");
    usleep(500000); // 0.5 seconds of overhead

    // 4. RESTORE STATE (New PCB -> CPU)
    new_proc->state = RUNNING;
    for(int i=0; i<8; i++) cpu_registers[i] = new_proc->registers[i];
    cpu_pc = new_proc->program_counter;
    printf("[Restore] PID %d loaded. Resuming at PC: %d\n", new_proc->pid, new_proc->program_counter);
}

void print_pcb(struct PCB* pcb) {
    printf("PID: %d, PC: %d, State: %d, Remaining Time: %d\n", 
           pcb->pid, pcb->program_counter, pcb->state, pcb->remaining_time);
}

void fcfs_scheduler(struct PCB* processes, int num_processes) {

    int time = 0;
    struct PCB* last_process = NULL;

    for(int i = 0; i < num_processes; i++) {

        if(processes[i].remaining_time <= 0)
            continue;

        // Context Switch
        context_switch(last_process, &processes[i]);

        last_process = &processes[i];

        printf("[Time %d] PID %d started execution\n",
               time,
               processes[i].pid);

        // Execute FULL burst time
        while(processes[i].remaining_time > 0) {

            cpu_pc++;

            processes[i].program_counter = cpu_pc;

            processes[i].remaining_time--;

            time++;

            usleep(200000); // simulation delay
        }

        // Process completed
        processes[i].state = TERMINATED;

        processes[i].completion_time = time;

        printf("[Time %d] PID %d completed execution\n",
               time,
               processes[i].pid);
    }

    printf("\nAll processes have completed execution.\n");
}