#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <semaphore.h>

#define NUMBERS 10
#define BUFFER_LEN 32

int buffer[5] = {0};

void *producer(void *arg[]){

	int *input = (int *)arg;
	for (int i = 0; i < NUMBERS; i++)
	{
		printf("%d\n", input[i] );
	}
}

void *consumer(void *arg){

}

int main(void)
{
	char inputbuffer[BUFFER_LEN];
	int *numbersArray= (int*)malloc(NUMBERS*sizeof(int));
	
	for (int i = 0; i < NUMBERS; i++)
	{
		//prompt for input
		printf("Enter a number\n");
		fgets(inputbuffer, BUFFER_LEN,stdin);
		inputbuffer[strlen(inputbuffer)-1]=0;

		char *end;
		
		numbersArray[i] = strtol(inputbuffer, &end, 10);
		printf("%d\n",numbersArray[i]);
	}

	pthread_t Tprod;
	pthread_t Tcon;

	// Create the thread.
	pthread_create(&Tprod, 0, producer, (void *) inputbuffer);
	pthread_create(&Tcon, 0, consumer, NULL);

	printf("Hello World\n");
	return 0;
}
