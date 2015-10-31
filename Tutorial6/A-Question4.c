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
sem_t sem;

void *producer(void *arg[]){
	//loop until production = 10
	int production = 0;

	int *input = (int *)arg;
	while (production < 10){
		//wait for a random time
		int r = rand() % 5000 + 1000;
		usleep(r);
		// printf("%d\n", input[production]);
		int full = 1;
		sem_wait(&sem);
		for (int j = 0; j < 5; j++)
		{
			// printf("Entering Producer Semaphore\n");
			if (buffer[j] == 0)
			{
				printf("Produced:%d\n",input[production]);
				buffer[j] = input[production];
				full = 0;
				production++;
				// sem_post(&sem);
				// printf("Exiting Producer Semaphore\n");
				break;
			}
			// printf("Exiting Producer Semaphore\n");
		}
		sem_post(&sem);
		// printf("Full:%d\n",full);
		//critical section
	}
}

void *consumer(void *arg){
	//loop until consumption = 10
	int consumption = 0;

	while(consumption <10){
		int r = rand() % 5000 + 1000;
		//add random delay
		usleep(r);

		int empty = 1;
		sem_wait(&sem);
		for (int i = 0; i < 5; ++i)
		{
			// printf("Entering Consumer Semaphore\n");
			if (buffer[i] != 0)
			{
				printf("Consumed:%d\n", buffer[i]);
				buffer[i] = 0;
				consumption++;
			}
			// printf("Exiting Consumer Semaphore\n");
		}
		sem_post(&sem);
	}
}

int main(void)
{
	srand(time(NULL));
	char inputbuffer[BUFFER_LEN];
	int *numbersArray= (int*)malloc(NUMBERS*sizeof(int));
	sem_init(&sem, 0, 1);

	for (int i = 0; i < NUMBERS; i++)
	{
		//prompt for input
		printf("Enter a number\n");
		fgets(inputbuffer, BUFFER_LEN,stdin);
		inputbuffer[strlen(inputbuffer)-1]=0;

		char *end;
		
		numbersArray[i] = strtol(inputbuffer, &end, 10);
		// printf("%d\n",numbersArray[i]);
	}

	pthread_t Tprod;
	pthread_t Tcon;

	// Create the thread.
	pthread_create(&Tprod, 0, producer, (void *) numbersArray);
	pthread_create(&Tcon, 0, consumer, NULL);

	pthread_join(Tprod,0);
	pthread_join(Tcon,0);
	sem_destroy(&sem);
	return 0;
}
