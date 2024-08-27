// Round Robin Scheduling Algorithm
#include <stdio.h>
#include <stdlib.h>

typedef struct process {
	int pid, at, bt, ct, tat, wt, rt, remaining_bt, enqueued;
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
        printf("\nFor Process %d:\n", i + 1);
        printf("Arrival time: ");
        scanf("%d", &p[i].at);
        printf("Burst time: ");
        scanf("%d", &p[i].bt);
        p[i].remaining_bt = p[i].bt;
        p[i].enqueued = 0;
        p[i].rt = -1;
    }
    return p;
}

void sortProcesses(process *p, int n) {
    for (int i = 0; i < n; i++) {
        int flag = 0;
        for (int j = 0; j < n - i - 1; j++) {
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

void findTimes(process *p, int n, int time_quantum) {
	int completed_processes = 0, selected = -1, et = 0;
	float avg_tat = 0, avg_wt = 0, avg_rt = 0;
    int queue[n], front = 0, rear = 0;
    queue[rear++] = 0;
    p[0].enqueued = 1;
	printf("\nGantt Chart:\n");
	while (completed_processes != n) {
        selected = queue[front++];
        if (p[selected].rt == -1) {
            p[selected].rt = et - p[selected].at;
        }
        if (p[selected].remaining_bt > time_quantum) {
            p[selected].remaining_bt -= time_quantum;
            printf("|(%d) P%d (%d)", et, p[selected].pid, et + time_quantum);
            et += time_quantum;
        } else {
            printf("|(%d) P%d (%d)", et, p[selected].pid, et + p[selected].remaining_bt);
            et += p[selected].remaining_bt;
            p[selected].remaining_bt = 0;
            p[selected].ct = et;
            p[selected].tat = p[selected].ct - p[selected].at;
            p[selected].wt = p[selected].tat - p[selected].bt;
            avg_rt += p[selected].rt;
            avg_tat += p[selected].tat;
            avg_wt += p[selected].wt;
            completed_processes++;
        }
        for (int i = 0; i < n; i++) {
            if (!p[i].enqueued && p[i].remaining_bt > 0 && p[i].at <= et) {
                queue[rear++] = i;
                p[i].enqueued = 1;
            }
        }
        if (p[selected].remaining_bt > 0) {
            queue[rear++] = selected;
        }
    }
	printf("\n\nResults:\n");
    printf("Average Waiting Time: %.2f ms.\n", avg_wt / n);
    printf("Average Turnaround Time: %.2f ms.\n", avg_tat / n);
    printf("Average Response Time: %.2f ms.\n", avg_rt / n);
}

void displayTimes(process *p, int n) {
    printf("\nObservation Table:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }
}

int main() {
    int n, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    process *p = createProcesses(n);
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);
    sortProcesses(p, n);
    findTimes(p, n, time_quantum);
    displayTimes(p, n);
    free(p);
    return 0;
}