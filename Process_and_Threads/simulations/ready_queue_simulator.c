#include <stdio.h>
#include <stdlib.h>
#include "os_simulator.h"

// The queue now stores pointers to PCB structures
#define MAX_QUEUE_SIZE 10
struct PCB* ready_queue[MAX_QUEUE_SIZE];

int front = -1;
int rear = -1;

int is_empty() {
    return front == -1;
}

int is_full() {
    return (rear + 1) % MAX_QUEUE_SIZE == front;
}

// Enqueue now takes a pointer to an existing PCB
void enqueue(struct PCB* process) {
    if (process == NULL) return;

    if (is_full()) {
        printf("[Queue Error] Ready queue is full. Cannot enqueue PID %d\n", process->pid);
        return;
    }

    if (is_empty()) {
        front = 0;
    }

    rear = (rear + 1) % MAX_QUEUE_SIZE;
    ready_queue[rear] = process;
    
    // Crucial: Update the state to READY when it enters the queue
    process->state = READY;
    printf("[Queue] Enqueued PID %d. (State: %s)\n", process->pid, state_to_string(process->state));
}

// Dequeue now returns a pointer to a PCB
struct PCB* dequeue() {
    if (is_empty()) {
        return NULL;
    }

    struct PCB* process = ready_queue[front];

    if (front == rear) {
        front = -1;
        rear = -1;
    } else {
        front = (front + 1) % MAX_QUEUE_SIZE;
    }

    printf("[Queue] Dequeued PID %d for execution.\n", process->pid);
    return process;
}

void display_ready_queue() {
    if (is_empty()) {
        printf("[Queue] Ready Queue is empty.\n");
        return;
    }

    printf("[Queue] Current Ready Queue: ");
    int i = front;
    while (1) {
        printf("[PID: %d] ", ready_queue[i]->pid);
        if (i == rear) break;
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
    printf("\n");
}