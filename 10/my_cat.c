// Simulation of cat command using system calls
// To compile: cc my_cat.c -o cat
// To execute: ./cat <filename>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("File name not entered!\nUsage: ./cat <filename>\n");
		exit(1);
	}
	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("Specified file does not exist!\n");
		exit(1);
	}
	char ch;
	while ((ch = fgetc(fp)) != EOF) {
		printf("%c", ch);
	}
	fclose(fp);
	return 0;
}