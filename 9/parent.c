#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Invalid usage!\nCorrect usage: %s N\n", argv[0]);
        exit(1);
    }
    int N = atoi(argv[1]);
    if (N <= 0) {
        fprintf(stderr, "N must be a positive integer!\n");
        exit(1);
    }
    key_t key = ftok("shmfile", 65);
    if (key == -1) {
        perror("key failed");
        exit(1);
    }
    int shmid = shmget(key, 4096, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        execl("./child", "child", argv[1], NULL);
        perror("execl failed");
        exit(1);
    } else {
        wait(NULL);
        char *shmptr = (char *) shmat(shmid, NULL, 0);
        if (shmptr == (char *) -1) {
            perror("shmat failed");
            exit(1);
        }
        printf("\nThe first %d odd numbers are:\n%s\n", N, shmptr);
        if (shmdt(shmptr) == -1) {
            perror("shmdt failed");
            exit(1);
        }
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl failed");
            exit(1);
        }
    }
    return 0;
}