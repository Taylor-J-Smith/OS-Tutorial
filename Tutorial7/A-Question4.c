#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){    
  pid_t pid = fork();
  if (pid == 0){
    //child process
    puts("entering child:");
    execlp("./process",NULL);
    exit(0);
  }else if (pid > 0){
    //parent process
    puts("parent process...waiting 5 sec...");
    sleep(5);
    puts("[parent] Sending SIGTSTP...");
    kill(pid,SIGTSTP);
    puts("[parent] Sleeping for 10sec...");
    sleep(10);
    puts("[parent] Sending SIGCONT...");
    kill(pid,SIGCONT);
    //    wait(NULL);
    waitpid(pid,0,0);
    puts("[parent] Parent Exiting!");
  }else{
    //fork failed
  }

  
  return 0;
}
