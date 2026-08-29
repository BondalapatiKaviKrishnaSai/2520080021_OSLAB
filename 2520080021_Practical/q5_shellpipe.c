#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("Pipe");
        exit(1);
    }

    pid_t pid1 = fork();

    if (pid1 == 0) {
        // First child: ls -l
        close(fd[0]);              // Close read end

        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        execlp("ls", "ls", "-l", NULL);

        perror("execlp");
        exit(1);
    }

    pid_t pid2 = fork();

    if (pid2 == 0) {
        // Second child: grep ".c"
        close(fd[1]);              // Close write end

        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        execlp("grep", "grep", ".c", NULL);

        perror("execlp");
        exit(1);
    }

    // Parent
    close(fd[0]);
    close(fd[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}
