#include <stdio.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <signal.h> 

void SIGUSR1 (int); 
void SIGUSR2 (int)

pid = fork();

int main() {  
    printf ("waiting...\n");  

    signal (SIGINT, SIGUSR1);  
    pause();  
    return 0;  
} 
void SIGUSR1 (int sigNum) {  
    printf (" That's it, I'm shutting you down.\n");  
    // this is where shutdown code would be inserted  
    sleep (1);  
    printf ("time to exit\n");  
    exit(0);  
} 

 if(pid == 0)
 { // Child process
    pause(5)
    write(fd[1], "SIGUSR1 OR 2 USE RANDOM FUNCTION", sizeof(int));
    printf("Child wrote [%d]\n", signem);
 }
else
 {
    read(fd[0], "SIGUSR1 OR 2 USE RANDOM FUNCTION", sizeof(int));
    printf("Parent received [%d] from child process\n", signum);
 }


