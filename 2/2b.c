#include <stdio.h>
#include <stdlib.h>

typedef struct process {
	int pid, at, bt, ct, tat, wt, pr, remaining_bt;
} process;

process *createProcesses(int n) {
	process *p = (process *) malloc(n * sizeof(process));
	if (p == NULL) {
		printf("Memory could not be dynamically allocated for the new processes!\n");
		exit(1);
	}
	printf("\nEnter the arrival times, burst times and priorities for the processes:\n");
	for (int i = 0; i < n; i++) {
		p[i].pid = i + 1;
		printf("\nFor process %d:\n", i + 1);
		printf("Enter arrival time: ");
		scanf("%d", &p[i].at);
		printf("Enter burst time: ");
		scanf("%d", &p[i].bt);
		printf("Enter priority: ");
		scanf("%d", &p[i].pr);
		p[i].remaining_bt = p[i].bt;
	}
	return p;
}

void findTimes(process *p, int n) {
	int completed_processes = 0, check = 0, lowest_pr = 9999, selected = -1, et = 0;
	float avg_tat = 0, avg_wt = 0;
	printf("\nGantt Chart:\n");
	while (completed_processes != n) {
		for (int i = 0; i < n; i++) {
			if ((p[i].at <= et) && (p[i].pr < lowest_pr) && (p[i].remaining_bt > 0)) {
				selected = i;
				check = 1;
				lowest_pr = p[i].pr;
			}
		}
		
		if (check == 0) {
			printf("|(%d) *** (%d)|", et, et + 1);
			et++;
            continue;
		}
		
		p[selected].remaining_bt--;
		printf("|(%d) P%d (%d)|", et, p[selected].remaining_bt, et + 1);
		
		if (p[selected].remaining_bt == 0) {
			completed_processes++;
			lowest_pr = 9999;
			check = 0;
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
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
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