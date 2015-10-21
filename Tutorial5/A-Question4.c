#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 10
#define BUFFER_LEN 32

pthread_mutex_t mutex;

int total_grade = 0;

void *class_total(void *currGrade){


	// Wait the main thead to lock
    // usleep(10);
    // printf("about to lock\n");

	// request lock
	pthread_mutex_lock (&mutex);
    // printf("%d says in critical section\n",(int)currGrade);

	// int grade;
	// grade = (int)currGrade;

	// printf("currGrade\n");
	// printf("%d\n",(int)currGrade );
	// printf("grade:\n");
	// printf("%d\n", grade );
	total_grade += (int)currGrade;
	// printf("total_grade\n");
	// printf("%d\n", total_grade);

	// printf("unlocking\n");
	// unlock lock
	pthread_mutex_unlock (&mutex);
    // printf("%d OUT of critical section\n",(int)currGrade);

	return NULL;
}

int main(void)
{	
	int currGrade = 0;
	pthread_t threads[NUM_THREADS];
	char buffer[BUFFER_LEN];

	//init mutex
	pthread_mutex_init(&mutex,NULL);

	for (int i = 0; i < 10; i++)
	{
		//prompt for input
		printf("Enter a student grade\n");
		fgets(buffer, BUFFER_LEN,stdin);
		buffer[strlen(buffer)-1]=0;

		// printf("%s\n",buffer);
	    char *end;

		currGrade = strtol(buffer, &end, 10);

		pthread_create(&threads[i], NULL, &class_total, currGrade);

	}

	for (int i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(&threads[i],NULL);	
	}

	// printf("Done join\n");

	pthread_mutex_lock (&mutex);
    // printf("main says in critical section\n");

	printf("Total Grade:%d\n", total_grade);
	pthread_mutex_unlock (&mutex);

	// pthread_mutex_destroy(&mutex);
	// free(currGrade);
	return 0;
}