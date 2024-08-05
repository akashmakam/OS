// Non-preemptive Priority Scheduling Algorithm

#include <stdio.h>
#include <stdlib.h>

typedef struct process {
    int pid, at, bt, ct, tat, wt, rt, finished;
} process;

process *createProcesses(int n) {
    process *p = (process *) malloc(sizeof(process) * n);
    
}