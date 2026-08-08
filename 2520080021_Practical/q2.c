#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    char source[100], destination[100];
    char buffer[BUFFER_SIZE];
    int sourceFile, destFile;
    ssize_t bytesRead;

    printf("Enter source file name: ");
    scanf("%99s", source);

    printf("Enter destination file name: ");
    scanf("%99s", destination);

    sourceFile = open(source, O_RDONLY);

    if (sourceFile < 0) {
        perror("Error opening source file");
        return 1;
    }

    destFile = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (destFile < 0) {
        perror("Error creating destination file");
        close(sourceFile);
        return 1;
    }

    while ((bytesRead = read(sourceFile, buffer, BUFFER_SIZE)) > 0) {
        write(destFile, buffer, bytesRead);
    }

    close(sourceFile);
    close(destFile);

    printf("File copied successfully!\n");

    return 0;
}
