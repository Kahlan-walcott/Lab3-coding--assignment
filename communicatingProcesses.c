#include <stdio.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <signal.h> 
#include <sys/types.h>
#include <string.h>

#define READ 0
#define WRITE 1

void sigHandler (int); 

int main() {  
    pid_t pid;
    pid = fork();
    signal (SIGINT, sigHandler);  
    printf ("waiting...\n");  
    pause();  
    if(pid == 0) { // Child process
        pause(5);
        write(fd[1], "SIGUSR1 OR 2 USE RANDOM FUNCTION", sizeof(int));
        printf("Child wrote [%d]\n", signum);
    }
    else {
        read(fd[0], "SIGUSR1 OR 2 USE RANDOM FUNCTION", sizeof(int));
        printf("Parent received [%d] from child process\n", signum);
    }
    return 0;  
} 

void sigHandler (int sigNum) {  
    if (sigNum == SIGUSR1) {
        printf("received a SIGUSR1 signal\n");
    }
    else if (sigNum == SIGUSR2) {
        printf("received a SIGUSR2 signal\n");
    }
    else if (singNum == SIGINT) { // To find Ctrl c
        printf (" That's it, I'm shutting you down.\n");  
        // this is where shutdown code would be inserted  
        sleep (1);  
        printf ("time to exit\n");  
        exit(0);  
    }
} 

