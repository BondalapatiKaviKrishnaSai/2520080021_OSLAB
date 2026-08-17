#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_ARGS 100

int main()
{
    char input[MAX_INPUT];
    char *args[MAX_ARGS];

    printf("========== Mini Shell ==========\n");
    printf("Type 'exit' to quit.\n\n");

    while (1)
    {
        printf("MiniShell> ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0)
            continue;

        if (strcmp(input, "exit") == 0)
            break;

        int argc = 0;
        char *token = strtok(input, " ");

        while (token != NULL && argc < MAX_ARGS - 1)
        {
            args[argc++] = token;
            token = strtok(NULL, " ");
        }

        args[argc] = NULL;

        /* Display PATH variable */
        char *path = getenv("PATH");
        if (path != NULL)
        {
            printf("PATH = %s\n", path);
        }

        pid_t pid = fork();

        if (pid < 0)
        {
            perror("Fork Failed");
            continue;
        }

        if (pid == 0)
        {
            execvp(args[0], args);

            perror("Command Not Found");
            exit(EXIT_FAILURE);
        }
        else
        {
            int status;

            waitpid(pid, &status, 0);

            if (WIFEXITED(status))
            {
                printf("Child exited with status %d\n",
                       WEXITSTATUS(status));
            }
            else
            {
                printf("Child terminated abnormally.\n");
            }
        }
    }

    printf("Shell Closed.\n");

    return 0;
}
