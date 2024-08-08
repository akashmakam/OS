// Simulation of grep command using system calls
// To compile: cc my_grep.c -o grep
// To execute: ./grep <filename> <pattern>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
        if (argc < 3) {
                printf("Insufficient number of arguements!\nUsage: ./grep <filename> <pattern>\n");
                exit(1);
        }
        FILE *fp = fopen(argv[1], "r");
        if (fp == NULL) {
                printf("Specified file does not exist!\n");
                exit(1);
        }
        char buffer[200];
        int flag = 0;
        while (!feof(fp)) {
                fgets(buffer, 100, fp);
                if (strstr(buffer, argv[2])) {
                        printf("%s", buffer);
                        flag = 1;
                }
        }
        if (flag == 0) {
                printf("Pattern not found in file!\n");
        }
        fclose(fp);
        return 0;
}