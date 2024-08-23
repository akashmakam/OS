// Priority Non-preemptive Scheduling Algorithm
#include <stdio.h>
#include <stdlib.h>

typedef struct process {
    int pid, at, bt, ct, tat, wt, pr, finished;
} process;

process *createProcesses(int n) {
    process *p = (process *) malloc(sizeof(process) * n);
    if (p == NULL) {
        printf("\nMemory could not be dynamically allocated for the new processes!\n");
        exit(0);
    }
    printf("Enter the arrival times, burst times, and priorities for the processes:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nFor Process %d:\n", i + 1);
        printf("Arrival time: ");
        scanf("%d", &p[i].at);
        printf("Burst time: ");
        scanf("%d", &p[i].bt);
        printf("Priority: ");
        scanf("%d", &p[i].pr);
        p[i].finished = 0;
    }
    return p;
}

void findTimes(process *p, int n) {
    int et = 0, completed_processes = 0, min_pr, selected;
    float avgwt = 0, avgtat = 0;
    printf("\nGantt Chart:\n");
    while (completed_processes != n) {
        selected = -1;
        min_pr = 9999;
        for (int i = 0; i < n; i++) {
            if ((p[i].at <= et) && (!p[i].finished) && (p[i].pr < min_pr)) {
                selected = i;
                min_pr = p[i].pr;
            }
        }
        if (selected != -1) {
            p[selected].finished = 1;
            completed_processes++;
            p[selected].ct = et + p[selected].bt;
            p[selected].tat = p[selected].ct - p[selected].at;
            p[selected].wt = p[selected].tat - p[selected].bt;
            et += p[selected].bt;
            avgwt += p[selected].wt;
            avgtat += p[selected].tat;
            printf("|(%d) P%d (%d)|", et, p[selected].pid, p[selected].ct);
        } else {
            printf("|(%d) *** (%d)|", et, et + 1);
            et++;
        }
    }
    printf("\n\nResults:\n");
    printf("Average Waiting Time: %.2f ms.\n", avgwt / n);
    printf("Average Turnaround Time: %.2f ms.\n", avgtat / n);
}

void displayTimes(process *p, int n) {
    printf("\nObservation Table:\n");
    printf("PID\tAT\tBT\tPT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].pr, p[i].ct, p[i].tat, p[i].wt);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    process *p = createProcesses(n);
    findTimes(p, n);
    displayTimes(p, n);
    free(p);
    return 0;
}