#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Insufficient arguments!\nUsage: %s N", argv[0]);
		exit(1);
	}
	
	int N = atoi(argv[1]);
	
	if (N <= 0) {
		printf("N must be a positive integer!");
		exit(1);
	}
	
	int key = ftok("shmfile", 65);
	int shmid = shmget(key, 4096, 0666 | IPC_CREAT);
	if (shmid == -1) {
		printf("shmget failed!\n");
		exit(1);
	}
	
	char* shm_ptr = (char*) shmat(shmid, NULL, 0);
	if (shm_ptr == (char*)-1) {
		printf("shmat failed!\n");
		exit(1);
	}

	for (int i = 0; i < N; i++) {
		sprintf(shm_ptr + strlen(shm_ptr), "%d\t", 2*i+1);
	}
	shmdt(shm_ptr);
	return 0;
}