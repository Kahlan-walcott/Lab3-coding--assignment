#include <stdio.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <signal.h> 
#include <sys/types.h>
#include <string.h>
#include <time.h>

#define READ 0
#define WRITE 1

void sigHandler (int); 

int main() {  
    int fd[2]; // would there need to be a loop somewhere to resend a different signal?
    int pid;
    int pipeCreationResult;
    pid = fork(); 
    
    if(pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    
    pipeCreationResult = pipe(fd);
    if(pipeCreationResult < 0){
        perror("Failed pipe creation\n");
        exit(1);
    }
    srand(time(NULL));
    int output = (rand() % 2) + 1; // 1 or 2 
    int input;
    printf("%d", output);
    if (output == 1) { // might have to move these if statements arround
        signal(SIGUSR1, sigHandler);
    }
    else if (output == 2) { // these two don't do anything yet 
        signal(SIGUSR2, sigHandler);
    }
    signal(SIGINT, sigHandler); // works

    printf("waiting...\n");  
    pause();  

    if(pid == 0) { // Child process  
        //pause();
        printf("spawned child PID# %d\n", pid);
        write(fd[1], &output, sizeof(int));
        printf("Child wrote [%d]\n", output);
    }
    else {
        read(fd[0], &input, sizeof(int)); // SIGUSR1 OR 2 USE RANDOM FUNCTION
        printf("Parent received [%d] from child process\n", input);
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
    else if (sigNum == SIGINT) { // To find Ctrl c
        printf (" That's it, I'm shutting you down.\n");  
        // this is where shutdown code would be inserted  
        sleep(1);  
        printf("time to exit\n");  
        exit(0);  
    }
} 

