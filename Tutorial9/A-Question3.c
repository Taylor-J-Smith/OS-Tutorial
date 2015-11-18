#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <time.h>

#define ARRAY_SIZE 100000000

int main (int argc, char *argv[])
{

	int num_array[ARRAY_SIZE];
	int serial_norm = 0;
	int parallel_norm = 0;

	//Initialization of array to random numbers.
	for(int i = 0; i < ARRAY_SIZE; i++)
	{
		num_array[i] = rand() % 100;
	}

	//Serial loop to calculate norm.
	clock_t serial_start = clock();
	for(int j = 0; j < ARRAY_SIZE; j++)
	{
		serial_norm += fabs(num_array[j]);
	}
	clock_t serial_end = clock();

	//Parallel loop to calculate norm.
	clock_t parallel_start = clock();
	#pragma omp parallel for reduction(+:parallel_norm)
	for(int k = 0; k < ARRAY_SIZE; k++)
	{
		parallel_norm += fabs(num_array[k]);
	}
	clock_t parallel_end = clock();

	//Assert the two values are the same
	if(serial_norm != parallel_norm)
		fprintf(stderr, "Error!: serial and parallel norms different. S: %d P: %d \n", serial_norm, parallel_norm);

	//Print results
	printf("Serial time: %f\n", (double)(serial_end - serial_start)/ CLOCKS_PER_SEC);
	printf("Parallel time: %f\n", (double)(parallel_end - parallel_start)/ CLOCKS_PER_SEC);
}
