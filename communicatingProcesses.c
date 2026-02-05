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
    int fd[2]; 
    int pid;
    int pipeCreationResult;
    pipeCreationResult = pipe(fd);
    if(pipeCreationResult < 0){
        perror("Failed pipe creation\n");
        exit(1);
    }

    pid = fork(); 
    if(pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    

    signal(SIGUSR1, sigHandler);
    signal(SIGUSR2, sigHandler);
    signal(SIGINT, sigHandler); 

    srand(time(NULL));

    if(pid == 0) { // Child process  
        printf("spawned child PID# %d\n", getpid());
        close(fd[0]);
        while(1) {
            int output = (rand() % 2) + 1; // 1 or 2 
            if (output == 1) {
                kill(getppid(), SIGUSR1);
            }
            else {
                kill(getppid(), SIGUSR2);
            }
            sleep(1);
        }
    }
    else {
        close(fd[1]);
        while(1) {
            printf("waiting...\t");
            pause();
        }
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
        printf ("^C received.  That's it, I'm shutting you down.\n");  
        // this is where shutdown code would be inserted  
        sleep(1);    
        exit(0);  
    }
} 

