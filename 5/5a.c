#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Invalid usage!\nCorrect usage: %s <filename>\n", argv[0]);
		exit(1);
	}

	int fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		printf("The specified file does not exist!\n");
		exit(1);
	}

	char buffer[10];
	int bytesRead = read(fd, buffer, 10);
	if (bytesRead == 0) {
		printf("The specified file exists, but is empty!\n");
		close(fd);
		exit(1);
	}

	// Display first 10 characters
	printf("5. a). i). Reading first 10 characters from file:\n");
	for (int i = 0; i < bytesRead; i++) {
		printf("%c", buffer[i]);
	}
	printf("\n");

	// Skip 5 characters from the current position
	int offset = lseek(fd, 5, SEEK_CUR);
	if (offset == -1) {
		printf("lseek failed!\n");
		close(fd);
		exit(1);
	}

	bytesRead = read(fd, buffer, 10);
	if (bytesRead > 0) {
		printf("\n5. a). ii). Skipping 5 characters from current position in the file:\n");
		for (int i = 0; i < bytesRead; i++) {
			printf("%c", buffer[i]);
		}
	} else {
		printf("Reached end of file while skipping 5 characters.\n");
	}

	// Move to the 5th last character in the file
	offset = lseek(fd, -5, SEEK_END);
	if (offset == -1) {
		printf("lseek failed!\n");
		close(fd);
		exit(1);
	}

	bytesRead = read(fd, buffer, 1);
	if (bytesRead > 0) {
		printf("\n5. a). iii). Going to 5th last character in the file:\n");
		printf("%c\n", buffer[0]);
	} else {
		printf("Failed to read the 5th last character.\n");
	}

	// Move to the 3rd character from the start of the file
	offset = lseek(fd, 2, SEEK_SET);
	if (offset == -1) {
		printf("lseek failed!\n");
		close(fd);
		exit(1);
	}

	bytesRead = read(fd, buffer, 1);
	if (bytesRead > 0) {
		printf("\n5. a). iv). Going to 3rd character in the file:\n");
		printf("%c\n", buffer[0]);
	} else {
		printf("Failed to read the 3rd character in the file.\n");
	}

	close(fd);
	return 0;
}