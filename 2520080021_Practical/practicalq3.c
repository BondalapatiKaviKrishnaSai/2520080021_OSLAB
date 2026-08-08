#include <stdio.h> 

#include <stdlib.h> 

#include <unistd.h> 

#include <sys/types.h> 

#include <sys/wait.h> 

int main() { 

    pid_t pid; 

    printf("Parent process started\n"); 

    printf("Parent PID  : %d\n", getpid()); 

    printf("Parent PPID : %d\n\n", getppid()); 

    pid = fork(); 

    if (pid < 0) { 

        perror("fork failed"); 

        return 1; 

    } 

    if (pid == 0) { 

        printf("----- Child Process -----\n"); 

        printf("Child PID  : %d\n", getpid()); 

        printf("Child PPID : %d\n", getppid()); 

        printf("Child is running...\n"); 

        sleep(5); 

        printf("Child process terminated.\n"); 

        exit(0); 

    } 

    else { 

        printf("----- Parent Process -----\n"); 

        printf("Parent PID : %d\n", getpid()); 

        printf("Child PID  : %d\n", pid); 

        printf("Parent is waiting for child...\n"); 

        wait(NULL); 

        printf("Child process has terminated.\n"); 

        printf("Parent process terminated.\n"); 

    } 

    return 0; 

} 
