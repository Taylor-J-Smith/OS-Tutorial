#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int main(void)
{
	int PID = 0;

	PID = fork();

	if(PID==-1){
		printf("Error forking.\n");
		return 0;
	}

	if(PID==0){
		sleep(1);
		printf("Child process.\n");

		exit(0);
	} else {
		int status;
		wait(&status);
		printf("Parent process.\nReturn status: %d\n",status);
	}

	return 0;
}
