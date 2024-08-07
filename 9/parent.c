#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Insufficient arguements!\nUsage: %s N\n", argv[0]);
		exit(1);
	}
	
	int N  = atoi(argv[1]);
	
	if (N <= 0) {
		printf("N should be a positive integer!\n");
		exit(1);
	}
	
	int key = ftok("shmfile", 65);
	int shmid = shmget(key, 4096, 0666 | IPC_CREAT);
	if (shmid == -1) {
		printf("shmget failed!\n");
		exit(1);
	}
	
	int pid = fork();
	if (pid < 0) {
		printf("fork failed!\n");
		exit(1);
	}
	if (pid == 0) {
		execl("./child3", "child", argv[1], NULL);
		printf("file does not exist!\n");
		exit(1);
	} else if (pid > 0) {
		wait(NULL);
		char* shm_ptr = (char *) shmat(shmid, NULL, 0);
		if (shm_ptr == (char *)-1) {
			printf("shmat failed!\n");
			exit(1);
		}
		printf("The first %d odd numbers are:\n%s\n", N, shm_ptr);
		shmdt(shm_ptr);
		shmctl(shmid, IPC_RMID, NULL);
	}
	return 0;
}