#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int parent_to_child[2]; // Pipe for parent to child
    int child_to_parent[2]; // Pipe for child to parent

    if (pipe(parent_to_child) == -1 || pipe(child_to_parent) == -1) {
        perror("Error creating pipes");
        exit(EXIT_FAILURE);
    }

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Error creating child process");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        // Child process
        close(parent_to_child[1]); // Close write end of parent-to-child pipe
        close(child_to_parent[0]); // Close read end of child-to-parent pipe

        // Read data from parent
        char message_from_parent[100];
        read(parent_to_child[0], message_from_parent, sizeof(message_from_parent));
        printf("Child received: %s\n", message_from_parent);

        // Write data to parent
        char message_to_parent[] = "Hello from the child!";
        write(child_to_parent[1], message_to_parent, sizeof(message_to_parent));

        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        close(parent_to_child[0]); // Close read end of parent-to-child pipe
        close(child_to_parent[1]); // Close write end of child-to-parent pipe

        // Write data to child
        char message_to_child[] = "Hello from the parent!";
        write(parent_to_child[1], message_to_child, sizeof(message_to_child));

        // Read data from child
        char message_from_child[100];
        read(child_to_parent[0], message_from_child, sizeof(message_from_child));
        printf("Parent received: %s\n", message_from_child);
    }

    return 0;
}

