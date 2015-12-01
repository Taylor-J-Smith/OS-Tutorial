#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>

#define MASTER 0
#define MATRIX_SIZE 100

void master(int n_proc)
{

	/*0*/ //Initialize
	/*0*/ MPI_Status status;
	/*0*/ int n_sent = 0;
	/*0*/ int n_recieved = 0;
	/*0*/ int A[MATRIX_SIZE][MATRIX_SIZE] = {0};
	/*0*/ int B[MATRIX_SIZE][MATRIX_SIZE] = {0};
	/*0*/ int C[MATRIX_SIZE][MATRIX_SIZE] = {0};
	/*0*/
	/*0*/ for(int i = 0; i < MATRIX_SIZE; i++)
	/*0*/ {
	/*0*/ 	for(int j = 0; j < MATRIX_SIZE; j++)
	/*0*/ 	{
	/*0*/ 		A[i][j] = ;
	/*0*/			B[i][j] = ;
	/*0*/ 	}
	/*0*/ }



	/*1*/ //Send arrays
	/*1*/ for(int i = 1; i < n_proc; ++i)
	/*1*/ {
	/*1*/ 	MPI_Send(A[n_sent],MATRIX_SIZE,MPI_Int,i,n_sent,MPI_COMM_WORLD);
	/*1*/ 	n_sent++;
	/*1*/ }

	/*2*/ //Return answers
}

void slave(int proc_id)
{
	int recieved[MATRIX_SIZE];

	MPI_Recv(,10,MPI_Int,MASTER,MPI_ANY_TAG,MPI_COMM_WORLD, &status);
}

int main(void)
{
	int proc_id;            // Process rank
	int n_proc;             // Number of processes

	// Initialize MPI
	MPI_Init(&argc, &argv);

	// Get the current process id
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

	// Get the current number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &n_proc);

	if (proc_id == MASTER)
	{
			master(n_proc);
	}
	else
	{
			slave(proc_id);
	}

	// Required to terminate all MPI processes
	MPI_Finalize();
	return 0;
}
