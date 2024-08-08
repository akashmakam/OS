#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* calculate_sum (void *arg) {
        int n = *(int *)arg;
        int sum = 0;
        for (int i = 0; i <= n; i++) {
                sum += i;
        }
        printf("Sum of natural numbers up to %d: %d\n", n, sum);
        pthread_exit(NULL);
}

void* calculate_factorial (void *arg) {
        int n = *(int *)arg;
        int factorial = 1;
        for (int i = 1; i <= n; i++) {
                factorial *= i;
        }
        printf("factorial of natural numbers up to %d: %d\n", n, factorial);
        pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
        if (argc != 2) {
                printf("Usage: %s N\n", argv[0]);
                exit(1);
        }
        int N = atoi(argv[1]);
        if (N < 0) {
                printf("N must be a non-negative integer!\n");
                exit(1);
        }
        pthread_t sum_thread, factorial_thread;
        if ((pthread_create(&sum_thread, NULL, calculate_sum, &N) != 0)) {
                printf("Sum thread could not be created!\n");
                exit(1);
        }
        if ((pthread_create(&factorial_thread, NULL, calculate_factorial, &N) != 0)) {
                printf("factorial thread could not be created!\n");
                exit(1);
        }
        pthread_join(sum_thread, NULL);
        pthread_join(factorial_thread, NULL);
        return 0;
}