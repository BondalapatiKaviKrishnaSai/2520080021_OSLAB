#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid[3];
    int i, status;

    for (i = 0; i < 3; i++) {
        pid[i] = fork();

        if (pid[i] == 0) {
            printf("Child %d : PID = %d\n", i + 1, getpid());
            sleep(i + 2);
            printf("Child %d finished\n", i + 1);
            exit(0);
        }
    }

    printf("\nParent waiting using waitpid()\n\n");

    for (i = 0; i < 3; i++) {
        waitpid(pid[i], &status, 0);
        printf("Child with PID %d terminated.\n", pid[i]);
    }

    printf("\nAll child processes completed using waitpid().\n");

    return 0;
}
