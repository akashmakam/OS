// Priority Non-preemptive Scheduling Algorithm

#include <stdio.h>
#include <stdlib.h>

typedef struct process {
    int pid, at, bt, ct, tat, wt, rt, pt, finished;
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
        printf("Enter arrival time: ");
        scanf("%d", &p[i].at);
        printf("Enter burst time: ");
        scanf("%d", &p[i].bt);
        printf("Enter priority: ");
        scanf("%d", &p[i].pt);
        p[i].finished = 0;
    }
    return p;
}

void sortProcesses(process *p, int n) {
    int flag;
    for (int i = 0; i < n - 1; i++) {
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
    int et = 0, completed = 0, min_pt, index;
    float avgwt = 0, avgrt = 0, avgtat = 0;
    
    printf("\nGantt Chart:\n");

    while (completed != n) {
        index = -1;
        min_pt = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= et && !p[i].finished && p[i].pt < min_pt) {
                index = i;
                min_pt = p[i].pt;
            }
        }
        if (index != -1) {
            p[index].ct = et + p[index].bt;
            p[index].tat = p[index].ct - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;
            p[index].rt = et - p[index].at;
            p[index].finished = 1;
            completed++;
            printf("|(%d) P%d (%d)|", et, p[index].pid, p[index].ct);
            et += p[index].bt;
            avgwt += p[index].wt;
            avgrt += p[index].rt;
            avgtat += p[index].tat;
        } else {
            printf("|(%d) *** (%d)|", et, et + 1);
            et++;
        }
    }
    printf("\n\nResults:\n");
    printf("Average Response Time: %.2f ms.\n", avgrt / n);
    printf("Average Waiting Time: %.2f ms.\n", avgwt / n);
    printf("Average Turnaround Time: %.2f ms.\n", avgtat / n);
}

void displayTimes(process *p, int n) {
    printf("\nObservation Table:\n");
    printf("PID\tAT\tBT\tPT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].pt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
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