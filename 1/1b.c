// SJF Pre-emptive Scheduling Algorithm
#include <stdio.h>
#include <stdlib.h>

typedef struct process {
	int pid, at, bt, ct, tat, wt, remaining_bt;
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
    }
    return p;
}

void findTimes(process *p, int n) {
	int completed_processes = 0, lowest_bt = 9999, selected = -1, check = 0, et = 0;
	float avg_tat = 0, avg_wt = 0;
	printf("\nGantt Chart:\n");
	while (completed_processes != n) {
		for (int i = 0; i < n; i++) {
			if ((p[i].at <= et) && (p[i].remaining_bt > 0) && (p[i].remaining_bt < lowest_bt)) {
				lowest_bt = p[i].bt;
				selected = i;
				check = 1;
			}
		}
		if (check == 0) {
			printf("|(%d) *** (%d)|", et, et + 1);
            et++;
            continue;
		}
		p[selected].remaining_bt--;
		printf("|(%d) P%d (%d)|", et, p[selected].pid, et + 1);
		if (p[selected].remaining_bt == 0) {
		    completed_processes++;
		    check = 0;
		    lowest_bt = 9999;
		    p[selected].ct = et + 1;
		    p[selected].tat = p[selected].ct - p[selected].at;
		    p[selected].wt = p[selected].tat - p[selected].bt;
		    avg_tat += p[selected].tat;
		    avg_wt += p[selected].wt;
		}
		et++;
	}
	printf("\n\nResults:\n");
    printf("Average Waiting Time: %.2f ms.\n", avg_wt / n);
    printf("Average Turnaround Time: %.2f ms.\n", avg_tat / n);
}

void displayTimes(process *p, int n) {
    printf("\nObservation Table:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
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