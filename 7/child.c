#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
        if (argc != 2) {
                printf("Insufficient arguments!\nUsage: %s N\n", argv[0]);
                exit(1);
        }

        int N = atoi(argv[1]);

        if (N <= 0) {
                printf("N must be a positive integer!\n");
                exit(1);
        }
        int key = ftok("shmfile", 65);
        int shmid = shmget(key, 4096, 0666 | IPC_CREAT);
        if (shmid == -1) {
                printf("shmget failed!\n");
                exit(1);
        }
        char *shm_ptr = (char *) shmat(shmid, NULL, 0);
        if (shm_ptr == (char *)-1) {
                printf("shmat failed!\n");
                exit(1);
        }
        shm_ptr[0] = '\0';
        int n1 = 0, n2 = 1, n3 = 0;
        sprintf(shm_ptr + strlen(shm_ptr), "%d\t", n1);
        if (N > 1) {
                sprintf(shm_ptr + strlen(shm_ptr), "%d\t", n2);
        }
        for (int i = 2; i < N; i++) {
                n3 = n1 + n2;
                n1 = n2;
                n2 = n3;
                sprintf(shm_ptr + strlen(shm_ptr), "%d\t", n3);
        }
        shmdt(shm_ptr);
        return 0;
}