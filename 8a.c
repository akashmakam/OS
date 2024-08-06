#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("You are not passing a directory!\nUsage: ./ls <directory_name>\n");
		exit(1);
	}
	DIR *dp;
	if ((dp = opendir(argv[1])) == NULL) {
		printf("The specified directory does not exist!\n");
		exit(1);
	}
	struct dirent *dirp;
	while ((dirp = readdir(dp)) != NULL) {
		printf("%s\n", dirp->d_name);
	}
	closedir(dp);
	return 0;
}