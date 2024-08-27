#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Insufficient arguements!\nUsage: %s <N>\n", argv[0]);
		exit(1);
	}
	
	int N = atoi(argv[1]);
	
	pid_t pid = fork();
	if (pid < 0) {
		perror("Fork failed!\n");
	}
	if (pid == 0) {
		execl("./child1", "child1", argv[1], NULL);
		perror("Execl failed!\n");
		exit(0);
	} else {
		wait(NULL);
		int shm_fd = shm_open("ARM", O_RDONLY, 0666);
		if (shm_fd == -1) {
			perror("Shared memory could not be opened!\n");
			exit(1);
		}
		void *ptr = mmap(NULL, 4096, PROT_READ, MAP_SHARED, shm_fd, 0);
		if (ptr == MAP_FAILED) {
			perror("Map failed!\n");
			exit(1);
		}
		printf("The fibonacci series of first %d terms are:\n%s\n", N, (char *)ptr);
		shm_unlink("ARM");
		close(shm_fd);
	}
	return 0;
}