#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT 1024
#define MAX_ARGS 100

/* ---------- Built-in Commands ---------- */

void builtin_help()
{
    printf("\nAvailable Built-in Commands:\n");
    printf("help   - Show available commands\n");
    printf("pwd    - Print current directory\n");
    printf("clear  - Clear screen\n");
    printf("exit   - Exit shell\n\n");
}

void builtin_pwd()
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("pwd");
}

void builtin_clear()
{
    system("clear");
}

/* ---------- Dispatch Table ---------- */

typedef struct
{
    char *name;
    void (*function)();
} BuiltIn;

BuiltIn commands[] =
{
    {"help", builtin_help},
    {"pwd", builtin_pwd},
    {"clear", builtin_clear}
};

int totalBuiltins = sizeof(commands) / sizeof(commands[0]);

int main()
{
    char input[MAX_INPUT];

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

        /* Variable Expansion */

        if (input[0] == '$')
        {
            char *value = getenv(input + 1);

            if (value != NULL)
                printf("%s\n", value);
            else
                printf("Undefined Variable\n");

            continue;
        }

        /* Built-in Dispatch */

        int found = 0;

        for (int i = 0; i < totalBuiltins; i++)
        {
            if (strcmp(input, commands[i].name) == 0)
            {
                commands[i].function();
                found = 1;
                break;
            }
        }

        if (!found)
        {
            printf("Invalid Built-in Command: %s\n", input);
        }
    }

    printf("Shell Closed.\n");

    return 0;
}
