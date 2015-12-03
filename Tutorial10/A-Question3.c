#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>

#define MASTER 0
#define MATRIX_SIZE 100

void print_array(int array[MATRIX_SIZE][MATRIX_SIZE]);

void master(int n_proc)
{
	/*0*/ //Initialize
	/*0*/ MPI_Status status;
	/*0*/ int n_sent = 0;
	/*0*/ int n_recieved = 0;
	/*0*/ int A[MATRIX_SIZE][MATRIX_SIZE];
	/*0*/ int C[MATRIX_SIZE][MATRIX_SIZE];
	/*0*/ int returned_row[MATRIX_SIZE];
	/*0*/ int row_num;
	/*0*/
	/*0*/ for(int i = 0; i < MATRIX_SIZE; i++)
	/*0*/ {
	/*0*/ 	for(int j = 0; j < MATRIX_SIZE; j++)
	/*0*/ 	{
	/*0*/ 		A[i][j] = ((i+j) + 1) % 2;
	/*0*/			C[i][j] = 0;
	/*0*/ 	}
	/*0*/ }

	while(n_sent < MATRIX_SIZE)
	{
			MPI_Send(A[n_sent],MATRIX_SIZE,MPI_INT,((n_sent % (n_proc-1)) + 1),n_sent,MPI_COMM_WORLD);
			n_sent++;

			MPI_Recv(returned_row,MATRIX_SIZE,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD, &status);
			n_recieved++;

			row_num = status.MPI_TAG;

			for(int k = 0; k < MATRIX_SIZE; k++)
			{
				C[row_num][k] = returned_row[k];
			}
	}

	for(int i = 1; i < n_proc; ++i)
	{
		MPI_Send(A[0],MATRIX_SIZE,MPI_INT,i,MATRIX_SIZE,MPI_COMM_WORLD);
	}

	print_array(C);
}

void slave(int proc_id)
{
	int B[MATRIX_SIZE][MATRIX_SIZE];
	int row[MATRIX_SIZE];
	int return_row[MATRIX_SIZE];
	int row_num;
	MPI_Status status;

	for(int i = 0; i < MATRIX_SIZE; i++)
	{
		for(int j = 0; j < MATRIX_SIZE; j++)
		{
			B[i][j] = ((i+j) + 1) % 2;
		}
	}

	MPI_Recv(row,MATRIX_SIZE,MPI_INT,MASTER,MPI_ANY_TAG,MPI_COMM_WORLD, &status);
	row_num = status.MPI_TAG;

	while(row_num < MATRIX_SIZE)
	{
		for(int i = 0; i < MATRIX_SIZE; i++)
		{
			return_row[i] = 0;

			for(int j = 0; j < MATRIX_SIZE; j++)
			{
				return_row[i] += (row[j]*B[j][i]);
			}
		}

		MPI_Send(return_row,MATRIX_SIZE,MPI_INT,MASTER,row_num,MPI_COMM_WORLD);

		MPI_Recv(row,MATRIX_SIZE,MPI_INT,MASTER,MPI_ANY_TAG,MPI_COMM_WORLD, &status);
		row_num = status.MPI_TAG;
	}
}

int main(int argc, char* argv[])
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

void print_array(int array[MATRIX_SIZE][MATRIX_SIZE])
{
	for(int i = 0; i < MATRIX_SIZE; i++)
  {
  	 for(int j = 0; j < MATRIX_SIZE; j++)
  	 {
  	 	 printf("%d ", array[i][j]);
  	 }
		 printf("\n");
  }
}
