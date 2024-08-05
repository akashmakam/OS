// FCFS Scheduling Algorithm

#include <stdio.h>
#include <stdlib.h>

typedef struct process {
    int pid, at, bt, ct, tat, wt, rt;
} process;

process *createProcesses(int n) {
    process *p = (process *) malloc(sizeof(process) * n);
    if (p == NULL) {
        printf("\nMemory could not be dynamically allocated for the processes!\n");
        exit(0);
    }
    printf("\nEnter the arrival times and burst times for the processes:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nFor Process %d:\n", i+1);
        printf("Arrival time: ");
        scanf("%d", &p[i].at);
        printf("Burst time: ");
        scanf("%d", &p[i].bt);
    }
    return p;
}

void sortProcesses(process *p, int n) {
    int flag = 0;
    for (int i = 0; i < n; i++) {
        flag = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (p[j].at > p[j + 1].at) {
                process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
                flag = 1;
            }
        }
        if (flag == 0) {
            break;
        }
    }
}

void findTimes(process *p, int n) {
    int et = 0, temp = 0;
    float avgtat = 0, avgwt = 0, avgrt = 0;
    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++) {
        if (et < p[i].at) {
            et = p[i].at;
        }
        temp = et;
        et += p[i].bt;
        p[i].ct = et;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        p[i].rt = p[i].wt;
        avgtat += p[i].tat;
        avgwt += p[i].wt;
        avgrt += p[i].rt;
        printf("|(%d) P%d (%d)|", temp, p[i].pid, et);
    }
    printf("\n\nResults:\nAverage Response Time: %.2f ms.\n", avgrt / n);
    printf("Average Waiting Time: %.2f ms.\n", avgwt / n);
    printf("Average Turnaround Time: %.2f ms.\n", avgtat / n);
}

void displayTimes(process *p, int n) {
    printf("\nObservation Table:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    process *p = createProcesses(n);
    sortProcesses(p, n);
    findTimes(p, n);
    displayTimes(p, n);
    free(p);
    return 0;
}