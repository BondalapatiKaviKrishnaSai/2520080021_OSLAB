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

        /* Replace escaped spaces (\ ) with a temporary character */
        for (int i = 0; input[i] != '\0'; i++)
        {
            if (input[i] == '\\' && input[i + 1] == ' ')
            {
                input[i] = 1;      // Temporary marker
                memmove(&input[i + 1], &input[i + 2], strlen(&input[i + 
2]) + 1);
            }
        }

        int argc = 0;
        char *token = strtok(input, " ");

        while (token != NULL && argc < MAX_ARGS - 1)
        {
            for (int i = 0; token[i] != '\0'; i++)
            {
                if (token[i] == 1)
                    token[i] = ' ';
            }

            args[argc++] = token;
            token = strtok(NULL, " ");
        }

        args[argc] = NULL;

        pid_t pid = fork();

        if (pid < 0)
        {
            perror("Fork Failed");
        }
        else if (pid == 0)
        {
            execvp(args[0], args);
            perror("Execution Failed");
            exit(EXIT_FAILURE);
        }
        else
        {
            wait(NULL);
        }
    }

    printf("Shell Closed.\n");

    return 0;
}
