#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pid_t pid;
    char buffer[100];

    // Create pipe
    if (pipe(fd) == -1) {
        perror("Pipe");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork");
        exit(1);
    }

    if (pid == 0) {
        // Child - Consumer
        close(fd[1]);  // Close write end

        read(fd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);

        close(fd[0]);
    }
    else {
        // Parent - Producer
        close(fd[0]);  // Close read end

        char message[] = "Hello from Parent using Pipe!";
        write(fd[1], message, strlen(message) + 1);

        close(fd[1]);

        wait(NULL);
    }

    return 0;
}
