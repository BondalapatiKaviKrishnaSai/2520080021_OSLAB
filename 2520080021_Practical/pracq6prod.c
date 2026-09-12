#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#define SERVER_FIFO "/tmp/server_fifo"
#define BUFFER_SIZE 256

int main() {
    char buffer[BUFFER_SIZE];

    // Remove old FIFO if it exists
    unlink(SERVER_FIFO);

    // Create named pipe
    if (mkfifo(SERVER_FIFO, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    printf("Server started...\n");
    printf("Waiting for clients...\n");

    while (1) {

        // Open FIFO for reading
        int fd = open(SERVER_FIFO, O_RDONLY);

        if (fd == -1) {
            perror("open");
            continue;
        }

        // Read message from client
        ssize_t bytesRead = read(fd, buffer, BUFFER_SIZE - 1);

        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';

            printf("Client message: %s\n", buffer);

            // Process the message
            char response[BUFFER_SIZE];

            snprintf(response, BUFFER_SIZE,
                     "Server received: %s", buffer);

            printf("Response: %s\n", response);

            /*
             * In a simple FIFO example, print the response.
             * A production client-server design would use
             * a separate FIFO for each client's response.
             */

            printf("--------------------------------\n");
        }

        close(fd);
    }

    unlink(SERVER_FIFO);

    return 0;
}


