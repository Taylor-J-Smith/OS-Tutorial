#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <time.h>

#define ARRAY_SIZE 100000000

int main (void)
{
	int num_array[ARRAY_SIZE];
	double serial_norm = 0;
	double parallel_norm = 0;

	//Initialization of array to random numbers.
	for(int i = 0; i < ARRAY_SIZE; i++)
	{
		num_array[i] = rand() % 100;
	}

	//Serial loop to calculate norm.
	double serial_start = omp_get_wtime();
	for(int j = 0; j < ARRAY_SIZE; j++)
	{
		serial_norm += fabs(num_array[j]);
	}
	double serial_end = omp_get_wtime();

	//Parallel loop to calculate norm.
	double parallel_start = omp_get_wtime();
	#pragma omp parallel for reduction(+: parallel_norm)
	for(int k = 0; k < ARRAY_SIZE; k++)
	{
		parallel_norm += fabs(num_array[k]);
	}
	double parallel_end = omp_get_wtime();

	//Assert the two values are the same
	if(serial_norm != parallel_norm)
		fprintf(stderr, "Error!: serial and parallel norms different. S: %f P: %f \n", serial_norm, parallel_norm);

	//Print results
	printf("Serial time: %f\n", (double)(serial_end - serial_start));
	printf("Parallel time: %f\n", (double)(parallel_end - parallel_start));
}
