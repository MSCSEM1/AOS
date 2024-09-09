#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>

// Function to get the current time in microseconds
long long get_microseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)tv.tv_sec * 1000000 + tv.tv_usec;
}

int main() {
    int n = 5; // Number of child processes to create
    pid_t child_pid;
    long long start_time, end_time;
    long long user_time = 0, kernel_time = 0;

    for (int i = 0; i < n; i++) {
        child_pid = fork();
        if (child_pid == -1) {
            perror("Error creating child process");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {
            // Child process
            start_time = get_microseconds();
            // Perform some work (e.g., sleep for demonstration)
            usleep(100000); // Sleep for 100 milliseconds
            end_time = get_microseconds();
            user_time += end_time - start_time;
            exit(EXIT_SUCCESS);
        }
    }

    // Wait for all child processes to terminate
    for (int i = 0; i < n; i++) {
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Child %d exited normally\n", i + 1);
        }
    }

    printf("Total cumulative user time: %lld microseconds\n", user_time);
    printf("Total cumulative kernel time: %lld microseconds\n", kernel_time);

    return 0;
}

