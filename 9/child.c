#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char *argv[]) {
        if (argc != 2) {
                printf("Invalid usage!\nCorrect usage: %s N\n", argv[0]);
                exit(1);
        }
        int N = atoi(argv[1]);
        if (N <= 0) {
                printf("N must be a positive integer!\n");
                exit(1);
        }
        key_t key = ftok("shmfile", 65);
        if (key == -1) {
                printf("ftok failed!\n");
                exit(1);
        }
        int shmid = shmget(key, 4096, 0666 | IPC_CREAT);
        if (shmid == -1) {
                printf("shmget failed!\n");
                exit(1);
        }
        char *shmptr = (char *) shmat(shmid, NULL, 0);
        if (shmptr == (char *) -1) {
                printf("shmat failed!\n");
                exit(1);
        }
        shmptr[0] = '\0';
        for (int i = 0; i < N; i++) {
                sprintf(shmptr + strlen(shmptr), "%d\t", 2*i+1);
        }
        shmdt(shmptr);
        return 0;
}