#include <stdio.h>
#include <stdlib.h>

void cleanup() {
    printf("Cleanup function called!\n");
}

int main() {
    atexit(cleanup);
    printf("Program started.\n");
    // Perform some work...
    printf("Program finished.\n");
    return 0;
}

