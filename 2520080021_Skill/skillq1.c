#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT 1024

int main()
{
    char input[MAX_INPUT];

    printf("=========================================\n");
    printf("        Mini Shell Started\n");
    printf("Type 'exit' to quit.\n");
    printf("=========================================\n");

    while (1)
    {
        printf("MiniShell> ");

        if (fgets(input, MAX_INPUT, stdin) == NULL)
        {
            printf("\nExiting Shell...\n");
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0)
        {
            continue;
        }

        if (strcmp(input, "exit") == 0)
        {
            printf("Goodbye!\n");
            break;
        }

        printf("You entered: %s\n", input);
    }

    return 0;
}
