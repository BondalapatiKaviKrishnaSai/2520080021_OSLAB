#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define SERVER_FIFO "/tmp/server_fifo"
#define BUFFER_SIZE 256

int main() {

    char message[BUFFER_SIZE];

    printf("Enter message: ");
    fgets(message, BUFFER_SIZE, stdin);

    // Remove newline
    message[strcspn(message, "\n")] = '\0';

    // Open server FIFO for writing
    int fd = open(SERVER_FIFO, O_WRONLY);

    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Send message to server
    write(fd, message, strlen(message) + 1);

    printf("Message sent to server.\n");

    close(fd);

    return 0;
}
