#include <stdio.h>
#include <stdlib.h>

typedef struct process {
        int pid, at, bt, ct, tat, wt, rt, finished;
} process;

process* createProcesses(int n) {
        process *p = (process *) malloc(sizeof(process)*n);
        if (p == NULL) {
                printf("Memory could not be dynamically allocated for the new processes!\n");
                exit(1);
        }
        printf("\nEnter the arrival and burst times for each process:\n");
        for (int i = 0; i < n; i++) {
                p[i].pid = i+1;
                printf("\nFor process %d\n",p[i].pid);
                printf("Enter arrival time:");
                scanf("%d", &p[i].at);
                printf("Enter burst time:");
                scanf("%d", &p[i].bt);
                p[i].finished = 0;
        }
        return p;
}

void findTimes(process *p, int n) {
        int et=0, temp, completed = 0, min_at;
        float avg_tat = 0, avg_wt = 0, avg_rt = 0;
        printf("\nGantt chart:\n");
        while (n != completed) {
                int index = -1;
                min_at = 9999;
                for (int i = 0; i < n; i++) {
                        if (p[i].at <= et && !p[i].finished && p[i].at < min_at) {
                                min_at = p[i].at;
                                index = i;
                        }
                }
                if (index != -1) {
                        temp = et;
                        et += p[index].bt;
                        p[index].ct = et;
                        p[index].tat = p[index].ct - p[index].at;
                        p[index].wt = p[index].tat - p[index].bt;
                        p[index].rt = p[index].wt;
                        avg_tat += p[index].tat;
                        avg_wt += p[index].wt;
                        avg_rt += p[index].rt;
                        p[index].finished = 1;
                        completed++;
                        printf("|(%d) P%d (%d)|", temp, p[index].pid, et);
                } else {
                        printf("|(%d) *** (%d)|", et, et+1);
                        et++;
                }
        }
        printf("\n\nResults:\n"
        "Average TAT: %.2f ms.\n"
        "Average WT: %.2f ms.\n"
        "Average RT: %.2f ms.\n", avg_tat/n, avg_wt/n, avg_rt/n);
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
        findTimes(p, n);
        displayTimes(p, n);
        free(p);
        return 0;
}