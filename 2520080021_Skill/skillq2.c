#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HISTORY 100
#define MAX_INPUT 1024

int main()
{
    char **history;
    char *input;
    int count = 0;

    history = (char **)malloc(MAX_HISTORY * sizeof(char *));
    if (history == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    input = (char *)malloc(MAX_INPUT * sizeof(char));
    if (input == NULL)
    {
        printf("Memory allocation failed!\n");
        free(history);
        return 1;
    }

    printf("========== Mini Shell ==========\n");
    printf("Type 'history' to view history.\n");
    printf("Type '!!' to execute last command.\n");
    printf("Type '!n' to execute command number n.\n");
    printf("Type 'exit' to quit.\n\n");

    while (1)
    {
        printf("MiniShell> ");

        if (fgets(input, MAX_INPUT, stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0)
            continue;

        if (strcmp(input, "exit") == 0)
            break;

        if (strcmp(input, "history") == 0)
        {
            printf("\nCommand History:\n");
            for (int i = 0; i < count; i++)
                printf("%d : %s\n", i + 1, history[i]);
            printf("\n");
            continue;
        }

        if (strcmp(input, "!!") == 0)
        {
            if (count == 0)
                printf("No commands in history.\n");
            else
                printf("Previous Command: %s\n", history[count - 1]);
            continue;
        }

        if (input[0] == '!' && strlen(input) > 1)
        {
            int num = atoi(&input[1]);

            if (num >= 1 && num <= count)
                printf("Command %d: %s\n", num, history[num - 1]);
            else
                printf("Invalid history number.\n");

            continue;
        }

        if (count < MAX_HISTORY)
        {
            history[count] = (char *)malloc(strlen(input) + 1);
            strcpy(history[count], input);
            count++;
        }

        printf("Executed: %s\n", input);
    }
	
    for (int i = 0; i < count; i++)
        free(history[i]);

    free(history);
    free(input);

    printf("Memory released successfully.\n");

    return 0;
}
