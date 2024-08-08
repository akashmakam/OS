#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]) {
        if (argc != 2) {
                fprintf(stderr, "Insufficient arguements!\n Usage: %s N\n", argv[0]);
                exit(1);
        }

        int N = atoi(argv[1]);

        int shm_fd = shm_open("ARM", O_CREAT | O_RDWR, 0666);
        if (shm_fd == -1) {
                perror("Shared memory failed!\n");
                exit(1);
        }
        if (ftruncate(shm_fd, 4096) == -1) {
                perror("Shared memory could not be truncated!\n");
                exit(1);
        }
        void *ptr = mmap(NULL, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if (ptr == MAP_FAILED) {
                perror("Mapping failed!\n");
                exit(1);
        }
        char* shm_ptr = (char *)ptr;
        shm_ptr[0] = '\0';
        int n1 = 0;
        int n2 = 1;
        int n3 = 0;
        sprintf(shm_ptr + strlen(shm_ptr), "%s\t%s\t", "0", "1");
        for (int i = 2; i < N; i++) {
                n3 = n1 + n2;
                n1 = n2;
                n2 = n3;
                sprintf(shm_ptr + strlen(shm_ptr), "%d\t", n3);
        }
        munmap(ptr, 4096);
        close(shm_fd);
        return 0;
}